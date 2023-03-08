using System;
using System.Collections;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using JPFITS;
using MathWorks.MATLAB.NET.Arrays;
using System.Threading.Tasks;
using System.Collections.Concurrent;
using System.Collections.Generic;
using static JPFITS.PointSourceExtractor;

namespace CCDLAB
{
	public partial class Form1
	{
		private void PSEBackgroundSeparationRadiusLabel_MouseEnter(object sender, EventArgs e)
		{
			PSEBackgroundSeparationRadiusLabel.Font = new Font(PSEBackgroundSeparationRadiusLabel.Font, FontStyle.Bold);
			PSEBackgroundSeparationRadiusLabel.Font = new Font(PSEBackgroundSeparationRadiusLabel.Font, FontStyle.Bold);
		}

		private void PSEBackgroundSeparationRadiusLabel_MouseLeave(object sender, EventArgs e)
		{
			PSEBackgroundSeparationRadiusLabel.Font = new Font(PSEBackgroundSeparationRadiusLabel.Font, FontStyle.Regular);
			PSEBackgroundSeparationRadiusLabel.Font = new Font(PSEBackgroundSeparationRadiusLabel.Font, FontStyle.Regular);
		}

		private void PSEBackgroundSeparationRadiusLabel_Click(object sender, EventArgs e)
		{
			if (((Label)sender).Text.Contains("Radius"))
				PSEBackgroundSeparationRadiusLabel.Text = "Src Separation:";
			else
				PSEBackgroundSeparationRadiusLabel.Text = "Bckgrnd Radius:";

			REG.SetReg("CCDLAB", "PSEBackgroundSeparationRadiusLabel", PSEBackgroundSeparationRadiusLabel.Text);
		}

		private void PSEPixelValLbl_MouseHover(object sender, EventArgs e)
		{
			PSEPixelValLbl.Font = new Font(PSEPixelValLbl.Font, FontStyle.Bold);
			PSEPixelCntLbl.Font = new Font(PSEPixelCntLbl.Font, FontStyle.Bold);
		}

		private void PSEPixelValLbl_MouseLeave(object sender, EventArgs e)
		{
			PSEPixelValLbl.Font = new Font(PSEPixelValLbl.Font, FontStyle.Regular);
			PSEPixelCntLbl.Font = new Font(PSEPixelCntLbl.Font, FontStyle.Regular);
		}

		private void PSEPixelValLbl_Click(object sender, EventArgs e)
		{
			if (((Label)sender).Text.Contains("SN"))
			{
				PSEPixelValLbl.Text = "Pixel Value:";
				PSEPixelCntLbl.Text = "Kernel Sum:";
			}
			else
			{
				PSEPixelValLbl.Text = "Pixel SN:";
				PSEPixelCntLbl.Text = "Kernel SN:";
			}
		}

		private void PSEFitChck_CheckedChanged(object sender, EventArgs e)
		{
			if (PSEFitChck.Checked)
			{
				PSEFitTypeChck.Enabled = true;
				PSEFitTypeChck.DroppedDown = true;
				PSEViewFitChck.Enabled = true;
				PSEFitResultListBox.Visible = true;
			}
			else
			{
				PSEFitTypeChck.Enabled = false;
				PSEViewFitChck.Enabled = false;
				PSEFitResultListBox.Visible = false;
			}
		}

		private void PSEFitTypeChck_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (PSESET.Count == 0)
				return;
			if (PSESET[PSESETINDEX].N_Sources <= 0)
				return;

			double[] PLB = null;
			double[] PUB = null;
			double[] P0 = null;
			if (SetParametersChck.Checked)
			{
				P0 = new double[FPW.NPARAMS];
				for (int i = 0; i < FPW.NPARAMS; i++)
					P0[i] = Convert.ToDouble(FPW.PITXTARRAY[i].Text);

				if (FPW.ConstrainBtn.Checked)
				{
					PLB = new double[FPW.NPARAMS];
					PUB = new double[FPW.NPARAMS];
					for (int i = 0; i < FPW.NPARAMS; i++)
					{
						PLB[i] = Convert.ToDouble(FPW.PLBTXTARRAY[i].Text);
						PUB[i] = Convert.ToDouble(FPW.PUBTXTARRAY[i].Text);
					}
				}
			}

			if (PSEFitTypeChck.SelectedIndex == 0)//circular gaussian
				PSESET[PSESETINDEX].Fit_Sources_Gaussian_Circular(P0, PLB, PUB);
			if (PSEFitTypeChck.SelectedIndex == 1)//circular gaussian
				PSESET[PSESETINDEX].Fit_Sources_Gaussian_Elliptical(P0, PLB, PUB);
			if (PSEFitTypeChck.SelectedIndex == 2)//circular moffat
				PSESET[PSESETINDEX].Fit_Sources_Moffat_Circular(P0, PLB, PUB);
			if (PSEFitTypeChck.SelectedIndex == 3)//elliptical moffat
				PSESET[PSESETINDEX].Fit_Sources_Moffat_Elliptical(P0, PLB, PUB);

			if (PSESET[PSESETINDEX].Fitted == false)//cancelled
			{
				ImageWindow.Refresh();
				return;
			}

			double[,] P = PSESET[PSESETINDEX].Fitted_Parameter_List;
			double[] Amp = new double[PSESET[PSESETINDEX].N_Sources];
			double[] X = new double[PSESET[PSESETINDEX].N_Sources];
			double[] Y = new double[PSESET[PSESETINDEX].N_Sources];
			double[] BG = new double[PSESET[PSESETINDEX].N_Sources];
			for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
			{
				Amp[i] = P[0, i];
				X[i] = P[1, i];
				Y[i] = P[2, i];
				BG[i] = P[P.GetLength(0) - 1, i];
			}
			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add("N:  " + PSESET[PSESETINDEX].N_Sources);
			PSEFitResultListBox.Items.Add("Amplitude:  " + Math.Round(JPMath.Mean(Amp, true), 4) + " +- " + Math.Round(JPMath.Stdv(Amp, false), 4));
			PSEFitResultListBox.Items.Add("X:          " + Math.Round(JPMath.Mean(X, true), 4) + " +- " + Math.Round(JPMath.Stdv(X, false), 4));
			PSEFitResultListBox.Items.Add("Y:          " + Math.Round(JPMath.Mean(Y, true), 4) + " +- " + Math.Round(JPMath.Stdv(Y, false), 4));

			if (PSEFitTypeChck.SelectedIndex == 0)//symmetric gaussian
			{
				double[] Sig = new double[PSESET[PSESETINDEX].N_Sources];

				for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
					Sig[i] = P[3, i];

				PSEFitResultListBox.Items.Add(string.Concat("FWHM:       ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Mean(Sig, true), 4), " +- ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Stdv(Sig, false), 4)));
			}

			if (PSEFitTypeChck.SelectedIndex == 1)//elliptical gaussian
			{
				double[] Phi = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Xsig = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Ysig = new double[PSESET[PSESETINDEX].N_Sources];

				for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
				{
					Phi[i] = P[3, i];
					Xsig[i] = P[4, i];
					Ysig[i] = P[5, i];
				}

				PSEFitResultListBox.Items.Add(string.Concat("FWHM_X:     ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Mean(Xsig, true), 4), " +- ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Stdv(Xsig, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("FWHM_Y:     ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Mean(Ysig, true), 4), " +- ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Stdv(Ysig, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("Phi:      ", Math.Round(JPMath.Mean(Phi, true), 4), " +- ", Math.Round(JPMath.Stdv(Phi, false), 4)));
			}

			if (PSEFitTypeChck.SelectedIndex == 2)//circular moffat
			{
				double[] Theta = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Beta = new double[PSESET[PSESETINDEX].N_Sources];

				for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
				{
					Theta[i] = P[3, i];
					Beta[i] = P[4, i];
				}

				PSEFitResultListBox.Items.Add(string.Concat("Theta:      ", Math.Round(JPMath.Mean(Theta, true), 4), " +- ", Math.Round(JPMath.Stdv(Theta, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("Beta:       ", Math.Round(JPMath.Mean(Beta, true), 4), " +- ", Math.Round(JPMath.Stdv(Beta, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("FWHM:       ", Math.Round(2 * JPMath.Mean(Theta, true) * Math.Sqrt(Math.Pow(2, 1 / (JPMath.Mean(Beta, true))) - 1), 4), " +- ", Math.Round(2 * JPMath.Stdv(Theta, false) * Math.Sqrt(Math.Pow(2, 1 / (JPMath.Stdv(Beta, false))) - 1), 4)));
			}

			if (PSEFitTypeChck.SelectedIndex == 3)//elliptical moffat
			{
				double[] Phi = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Xtheta = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Ytheta = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Beta = new double[PSESET[PSESETINDEX].N_Sources];

				for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
				{
					Phi[i] = P[3, i];
					Xtheta[i] = P[4, i];
					Ytheta[i] = P[5, i];
					Beta[i] = P[6, i];
				}

				PSEFitResultListBox.Items.Add(string.Concat("Theta_X:    ", Math.Round(JPMath.Mean(Xtheta, true), 4), " +- ", Math.Round(JPMath.Stdv(Xtheta, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("Theta_Y:    ", Math.Round(JPMath.Mean(Ytheta, true), 4), " +- ", Math.Round(JPMath.Stdv(Ytheta, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("Beta:       ", Math.Round(JPMath.Mean(Beta, true), 4), " +- ", Math.Round(JPMath.Stdv(Beta, false), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("FWHM_X:     ", Math.Round(2 * JPMath.Mean(Xtheta, true) * Math.Sqrt(Math.Pow(2, 1 / (JPMath.Mean(Beta, true))) - 1), 4), " +- ", Math.Round(2 * JPMath.Stdv(Xtheta, false) * Math.Sqrt(Math.Pow(2, 1 / (JPMath.Stdv(Beta, false))) - 1), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("FWHM_Y:     ", Math.Round(2 * JPMath.Mean(Ytheta, true) * Math.Sqrt(Math.Pow(2, 1 / (JPMath.Mean(Beta, true))) - 1), 4), " +- ", Math.Round(2 * JPMath.Stdv(Ytheta, false) * Math.Sqrt(Math.Pow(2, 1 / (JPMath.Stdv(Beta, false))) - 1), 4)));
				PSEFitResultListBox.Items.Add(string.Concat("Phi:      ", Math.Round(JPMath.Mean(Phi, true), 4), " +- ", Math.Round(JPMath.Stdv(Phi, false), 4)));
			}

			PSEFitResultListBox.Items.Add("BG:         " + Math.Round(JPMath.Mean(BG, true), 4) + " +- " + Math.Round(JPMath.Stdv(BG, false), 4));
		}

		private void PSEFitTypeChck_MouseClick(object sender, MouseEventArgs e)
		{
		}

		private void PSEKernelRadUpD_ValueChanged(object sender, EventArgs e)
		{
			if (PSEKernelRadUpD.Value == 0)
			{
				PSEKernelMinUpD.Enabled = false;
				PSEKernelMaxUpD.Enabled = false;
				PSEAutoBackgroundChck.Enabled = false;
				PSEFitChck.Enabled = false;
				PSEFitChck.Checked = false;
			}
			else
			{
				PSEKernelMinUpD.Enabled = true;
				PSEKernelMaxUpD.Enabled = true;
				PSEAutoBackgroundChck.Enabled = true;
				PSEFitChck.Enabled = true;
			}

			if (PSEBackgroundRadUpD.Value < PSEKernelRadUpD.Value)
				PSEBackgroundRadUpD.Value = PSEKernelRadUpD.Value;
			PSEBackgroundRadUpD.Minimum = PSEKernelRadUpD.Value;
		}

		private void SaveROIContext_Click(object sender, EventArgs e)
		{
			SaveFileDialog fsd = new SaveFileDialog();

			if (fsd.ShowDialog() == DialogResult.Cancel)
				return;

			JPFITS.FITSImage ff = new FITSImage(fsd.FileName, ROI_PATH_COORDS, false, false);
			ff.WriteImage(DiskPrecision.Double, false);
		}

		private void LoadROIContext_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = false;//possibly true for getting/doing multi-regions

			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			PSEDrawROI.Checked = true;
			DRAW_ROI_PATH = false;
			DRAW_ROI_PATH_START = false;

			ROI_PATH_COORDS = FITSImage.ReadImageArrayOnly(ofd.FileName, null, false);
			MAKEROIPATHPOINTS();
			ROI_PATH_FILLREGION();
		}		

		private void PSESeachROIOnlyChck_CheckedChanged(object sender, EventArgs e)
		{
			if (PSESeachROIOnlyChck.Checked)
			{
				PSEEllipticalROI.Enabled = true;
				PSEDrawROI.Enabled = true;
			}
			else
			{
				PSEEllipticalROI.Checked = false;
				PSEDrawROI.Checked = false;
				PSEEllipticalROI.Enabled = false;
				PSEDrawROI.Enabled = false;
				ROI_PATH_COORDS = null;
				ROI_PATH_POINTS = null;
				ROI_REGION = null;
				ImageWindow.Refresh();
			}
		}

		private void PSEAutoBackgroundChck_CheckedChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PSEAutoBackgroundChck", PSEAutoBackgroundChck.Checked);
		}

		private void PSEDrawROI_CheckedChanged(object sender, EventArgs e)
		{
			if (PSEDrawROI.Checked)
			{
				if (PSEEllipticalROI.Checked)//make an roi path and region from the shown ellipse
				{
					PSEEllipticalROI.Checked = false;
					ROI_PATH_COORDS = new double[2, 91];
					for (int i = 0; i <= 360; i+=4)
					{
						double r = ROIXRad * ROIYRad / Math.Sqrt(ROIXRad * ROIXRad * Math.Sin((double)i * Math.PI / 180) * Math.Sin((double)i * Math.PI / 180) + ROIYRad * ROIYRad * Math.Cos((double)i * Math.PI / 180) * Math.Cos((double)i * Math.PI / 180));
						ROI_PATH_COORDS[0, i / 4] = r * Math.Cos((double)i * Math.PI / 180) + ROIX0;
						ROI_PATH_COORDS[1, i / 4] = r * Math.Sin((double)i * Math.PI / 180) + ROIY0;
					}

					MAKEROIPATHPOINTS();
					ROI_PATH_FILLREGION();
					SubImageStatsUpD();
					SubImageUpD();
					ImageWindow.Refresh();
					return;
				}
				
				DRAW_ROI_PATH = true;
				DRAW_ROI_PATH_START = true;
				ROI_PATH_COORDS = null;
				ROI_PATH_POINTS = null;

				ImageWindow.Refresh();
			}
			else
			{
				ROI_REGION = null;
				DRAW_ROI_PATH = false;
				DRAW_ROI_PATH_START = false;
				ROI_PATH_COORDS = null;
				ROI_PATH_POINTS = null;
				ImageWindow.Refresh();
			}
		}

		private void PSEEllipticalROI_CheckedChanged(object sender, EventArgs e)
		{
			if (PSEEllipticalROI.Checked)
			{
				PSEDrawROI.Checked = false;
				ROI_PATH_COORDS = null;
				ROI_PATH_POINTS = null;
				ShowCrosshair.Checked = false;
				ImageWindow.Refresh();

				ROIX0 = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "ROIX0"));
				ROIY0 = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "ROIY0"));
				ROIXRad = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "ROIXRad"));
				ROIYRad = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "ROIYRad"));				
			}
			else
			{
				ROI_REGION = null;
			}

			ImageWindow.Refresh();
		}

		private void PSEDropContextSave_Click(object sender, EventArgs e)
		{
			SaveFileDialog sf = new SaveFileDialog();
			sf.InitialDirectory = IMAGESET[IMAGESETINDEX].FilePath;
			sf.Filter = "FITS|*.fits;*.fit;*.fts";
			sf.OverwritePrompt = false;
			if (sf.ShowDialog() == DialogResult.Cancel)
				return;

			for (int i = 0; i < PSEDrop.Items.Count; i++)
				PSESET[i].Save(sf.FileName, PSEDrop.Items[i].ToString());
		}

		private void PSEDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			PSESPLOTALL = false;
			PSESPLOTNONE = false;

			PSESETINDEX = PSEDrop.SelectedIndex;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();

			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add("N:  " + PSESET[PSESETINDEX].N_Sources);

			if (PSESET[PSESETINDEX].N_Sources != -1)
			{
				PSESaturationUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].PixelSaturation);
				PSEKernelRadUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].KernelRadius);
				PSEBackgroundRadUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].BackgroundRadius);
				PSEPixelMaxUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].PixelMaximum);
				PSEPixelMinUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].PixelMinimum);
				PSEKernelMinUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].KernelMinimum);
				PSEKernelMaxUpD.Value = Convert.ToDecimal(PSESET[PSESETINDEX].KernelMaximum);
				PSEAutoBackgroundChck.Checked = PSESET[PSESETINDEX].AutoBackground;
				PSESaveKernelsChck.Checked = PSESET[PSESETINDEX].SavePointSources;
				PSESeachROIOnlyChck.Checked = PSESET[PSESETINDEX].SearchROI;
			}
		}

		private void PSEDropContextPlotAll_Click(object sender, EventArgs e)
		{
			PSESPLOTALL = true;
			PSESPLOTNONE = false;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEDropContextPlotNone_Click(object sender, EventArgs e)
		{
			PSESPLOTALL = false;
			PSESPLOTNONE = true;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEDropContextRemove_Click(object sender, EventArgs e)
		{
			PSESPLOTALL = false;
			PSESPLOTNONE = false;

			PSESET.RemoveAt(PSEDrop.SelectedIndex);
			PSEDrop.Items.RemoveAt(PSEDrop.SelectedIndex);

			if (PSESETINDEX >= PSESET.Count)
				PSESETINDEX = PSESET.Count - 1;
			
			if (PSESET.Count == 0)
			{
				PSEDrop.Enabled = false;
				ImageWindow.Refresh();
				SubImageWindow.Refresh();
				return;
			}

			PSEDrop.SelectedIndex = PSESETINDEX;
		}

		private void PSEDropContextClearAll_Click(object sender, EventArgs e)
		{
			PSESET.Clear();
			PSEDrop.Items.Clear();
			PSEDrop.Enabled = false;
			PSESPLOTALL = false;
			PSESPLOTNONE = false;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEDropContextAdd_Click(object sender, EventArgs e)
		{
			PSEDrop.Items.Add("PSE_" + (PSESET.Count + 1).ToString());
			PSESET.Add(new PointSourceExtractor());
			PSESETINDEX = PSESET.Count - 1;
			PSEDrop.SelectedIndex = PSESETINDEX;

			PSESPLOTALL = false;
			PSESPLOTNONE = false;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEFindSrcBtn_MouseUp(object sender, MouseEventArgs e)
		{
			if (FIRSTLOAD)
				return;

			string saveps = "";
			if (PSESAVEKERNELPATH != null)
				saveps = PSESAVEKERNELPATH + "//" + IMAGESET[IMAGESETINDEX].FileName;

			if (e.Button == MouseButtons.Left)
			{
				//Enabled = false;

				double pix_min = (double)PSEPixelMinUpD.Value;
				double pix_max = (double)PSEPixelMaxUpD.Value;
				double pix_sat = (double)PSESaturationUpD.Value;
				double count_min = (double)PSEKernelMinUpD.Value;
				double count_max = (double)PSEKernelMaxUpD.Value;
				bool auto_bg = PSEAutoBackgroundChck.Checked;
				bool sn = PSEPixelValLbl.Text.Contains("SN");
				int kernel_radius = (int)PSEKernelRadUpD.Value;
				int bg_rad = (int)PSEBackgroundRadUpD.Value;

				JPFITS.REG.SetReg("CCDLAB", "PSEPixValMin", pix_min.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEPixSaturation", pix_sat.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSECountValMin", count_min.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEPixValMax", pix_max.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSECountValMax", count_max.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEWidth", PSEKernelRadUpD.Value.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEBackgroundRadUpD", PSEBackgroundRadUpD.Value.ToString());
				if (PSESeachROIOnlyChck.Checked)
				{
					if (PSEEllipticalROI.Checked)
						MakeEllipticalROI_REGION();

					if (!PSEEllipticalROI.Checked && !PSEDrawROI.Checked)//either elliptical nor drawn...so just existing curusor box
					{
						ROI_REGION = new bool[IMAGESET[IMAGESETINDEX].Width, IMAGESET[IMAGESETINDEX].Height];

						for (int x = 0; x < IMAGESET[IMAGESETINDEX].Width; x++)
							for (int y = 0; y < IMAGESET[IMAGESETINDEX].Height; y++)
								if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
									ROI_REGION[x, y] = true;
					}
				}

				if (PSEKernelRadUpD.Value == 0)
				{
					count_min = Double.MinValue;
					count_max = Double.MaxValue;
				}

				if (PSESET.Count == 0)
				{
					PSESET.Add(new PointSourceExtractor());
					PSESETINDEX = 0;
				}

				PSESET[PSESETINDEX].Extract_Sources(IMAGESET[IMAGESETINDEX].Image, pix_sat, pix_min, pix_max, count_min, count_max, sn, kernel_radius, bg_rad, auto_bg, saveps, ROI_REGION, true, IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5, false, PSEBackgroundSeparationRadiusLabel.Text.Contains("Src"));

				if (PSESET[PSESETINDEX].N_Sources == 0)
				{
					MessageBox.Show("Found 0 sources matching search criteria...", "Nothing found...");
					PSETableViewBtn.Enabled = false;
					return;
				}

				if (PSESET[PSESETINDEX].N_Sources == -1)//cancelled
				{
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
					PSETableViewBtn.Enabled = false;
					return;
				}

				PSEDrop.Enabled = true;
				if (PSEDrop.Items.Count == 0)
				{
					PSEDrop.Items.Add("PSE_1");
					PSEDrop.SelectedIndex = 0;
				}
			}

			if (e.Button == MouseButtons.Right)
			{
				if (PSESET.Count == 0 || PSESET[PSESETINDEX].N_Sources < 1)
					return;

				if (MessageBox.Show("Are you sure you want to re-determine the Point Source Extraction with the current cooridnates?", "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					return;

				double[] Xcoords = new double[PSESET[PSESETINDEX].N_Sources];
				double[] Ycoords = new double[PSESET[PSESETINDEX].N_Sources];
				for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
				{
					Xcoords[i] = PSESET[PSESETINDEX].Centroids_X_Pixel[i];
					Ycoords[i] = PSESET[PSESETINDEX].Centroids_Y_Pixel[i];
				}

				PSESET[PSESETINDEX] = new JPFITS.PointSourceExtractor();
				PSESET[PSESETINDEX].Extract_Sources(IMAGESET[IMAGESETINDEX].Image, Xcoords, Ycoords, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, saveps, IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);
			}

			PSESPLOTALL = false;
			PSESPLOTNONE = false;

			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add(string.Concat("N Sources:   ", PSESET[PSESETINDEX].N_Sources));
			PSEFitResultListBox.Visible = true;
			PSETableViewBtn.Enabled = true;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void ShowPSEChck_CheckedChanged(object sender, EventArgs e)
		{
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void ROIFitFcnDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			SetParametersChck.Checked = false;
			if (ROIFitFcnDrop.SelectedIndex == 0)
			{
				ROIFITMODELNAME = PointSourceModel.CircularGaussian;
				ROIFITCOMPOUNDMODELNAME = PointSourceCompoundModel.CircularGaussian;
			}
			else if (ROIFitFcnDrop.SelectedIndex == 1)
			{
				ROIFITMODELNAME = PointSourceModel.EllipticalGaussian;
				ROIFITCOMPOUNDMODELNAME = PointSourceCompoundModel.EllipticalGaussian;
			}
			else if (ROIFitFcnDrop.SelectedIndex == 2)
			{
				ROIFITMODELNAME = PointSourceModel.CircularMoffat;
				ROIFITCOMPOUNDMODELNAME = PointSourceCompoundModel.CircularMoffat;
			}
			else if (ROIFitFcnDrop.SelectedIndex == 3)
			{
				ROIFITMODELNAME = PointSourceModel.EllipticalMoffat;
				ROIFITCOMPOUNDMODELNAME = PointSourceCompoundModel.EllipticalMoffat;
			}
		}

		private void ROIFitStatsTypeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "ROIFitStatsTypeDrop", ROIFitStatsTypeDrop.SelectedIndex);

			if (ROIFitStatsTypeDrop.SelectedIndex == 0)
				ROIFITMINIMIZATIONTYPE = FitMinimizationType.LeastSquares;
			if (ROIFitStatsTypeDrop.SelectedIndex == 1)
				ROIFITMINIMIZATIONTYPE = FitMinimizationType.ChiSquared;
			if (ROIFitStatsTypeDrop.SelectedIndex == 2)
				ROIFITMINIMIZATIONTYPE = FitMinimizationType.Robust;
			if (ROIFitStatsTypeDrop.SelectedIndex == 3)
				ROIFITMINIMIZATIONTYPE = FitMinimizationType.CashStatistic;
		}

		private void SetParametersChck_CheckedChanged(object sender, EventArgs e)
		{
			if (ROIFitFcnDrop.SelectedIndex < 0)
			{
				SetParametersChck.Checked = false;
				return;
			}

			if (SetParametersChck.Checked)
			{
				double[] x = new double[XSUBRANGE.Length];
				double[] y = new double[YSUBRANGE.Length];
				Array.Copy(XSUBRANGE, x, x.Length);
				Array.Copy(YSUBRANGE, y, y.Length);
				FPW = new FitParametersWindow(ROIFitFcnDrop.SelectedIndex, x, y, SUBIMAGE);
				FPW.ShowDialog(this);

				if (FPW.DialogResult == DialogResult.Cancel)
					SetParametersChck.Checked = false;
			}
		}

		private void PSEFitStatsTypeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "PSEFitStatsTypeDrop", PSEFitStatsTypeDrop.SelectedIndex);
		}


		private void ROIFitBtn_Click(object sender, EventArgs e)
		{
			if (FIRSTLOAD)
				return;

			if (ROIFitFcnDrop.SelectedIndex < 0)
				ROIFitFcnDrop.SelectedIndex = 0;

			//check if marked coordinates are all within the ROI...if they are then do compound fit
			int c = 0;
			if (MARKCOORDS != null && MARKCOORDS.Length != 0)//also check if they are inside ROI
				for (int i = 0; i < MARKCOORDS.GetLength(1); i++)
					if ((int)MARKCOORDS[0, i] > XSUBRANGE[0] && (int)MARKCOORDS[0, i] < XSUBRANGE[XSUBRANGE.Length - 1] && (int)MARKCOORDS[1, i] > YSUBRANGE[0] && (int)MARKCOORDS[1, i] < YSUBRANGE[YSUBRANGE.Length - 1])
						c++;
			if (MARKCOORDS != null && MARKCOORDS.Length != 0 && c == MARKCOORDS.GetLength(1))
			{
				ROICompoundFit();//do compound fit
				return;
			}

			//check if multiple PSE coords are within the ROI...if they are then gather them to marked coords and do compound fit
			if (PSESET.Count > 0 && PSESET[PSESETINDEX].N_Sources > 0)
			{
				ArrayList contained = new ArrayList();

				for (int i = 0; i < PSESET[PSESETINDEX].N_Sources; i++)
					if (PSESET[PSESETINDEX].Centroids_X[i] > XSUBRANGE[0] && PSESET[PSESETINDEX].Centroids_X[i] < XSUBRANGE[SUBIMAGE_HWX * 2] && PSESET[PSESETINDEX].Centroids_Y[i] > YSUBRANGE[0] && PSESET[PSESETINDEX].Centroids_Y[i] < YSUBRANGE[SUBIMAGE_HWY * 2])
					{
						contained.Add(PSESET[PSESETINDEX].Centroids_X[i]);
						contained.Add(PSESET[PSESETINDEX].Centroids_Y[i]);
					}

				if (contained.Count > 2)
				{
					MARKCOORDS = new double[2, contained.Count / 2];
					for (int i = 0; i < contained.Count / 2; i++)
					{
						MARKCOORDS[0, i] = Convert.ToDouble(contained[i * 2]);
						MARKCOORDS[1, i] = Convert.ToDouble(contained[i * 2 + 1]);
					}
					ROICompoundFit();//do compound fit
					MARKCOORDS = null;
					return;
				}
			}

			//else just do single fit on the ROI
			//Enabled = false;

			double[] P = null;
			double[] PLB = null;
			double[] PUB = null;

			if (ROIFitFcnDrop.SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
				P = new double[5];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 4, JPMath.Min(SUBIMAGE, false) };
			if (ROIFitFcnDrop.SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
				P = new double[7];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 0, 4, 4, JPMath.Min(SUBIMAGE, false) };
			if (ROIFitFcnDrop.SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) (-p(4)) + p(5)
				P = new double[6];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 4, 4, JPMath.Min(SUBIMAGE, false) };
			if (ROIFitFcnDrop.SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) (-p(6)) + p(7)
				P = new double[8];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 0, 4, 4, 4, JPMath.Min(SUBIMAGE, false) };

			if (SetParametersChck.Checked)
			{
				for (int i = 0; i < P.Length; i++)
					P[i] = Convert.ToDouble(FPW.PITXTARRAY[i].Text);

				if (FPW.ConstrainBtn.Checked)
				{
					PLB = new double[P.Length];
					PUB = new double[P.Length];
					for (int i = 0; i < P.Length; i++)
					{
						PLB[i] = Convert.ToDouble(FPW.PLBTXTARRAY[i].Text);
						PUB[i] = Convert.ToDouble(FPW.PUBTXTARRAY[i].Text);
					}
				}
			}

			JPMath.Fit_PointSource(ROIFITMODELNAME, ROIFITMINIMIZATIONTYPE, XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, out double[] P_err, out _, out double chisq_norm, out string fitmsg);

			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add("Amplitude:     " + Math.Round(P[0], 4) + " +- " + Math.Round(P_err[0], 4));
			PSEFitResultListBox.Items.Add("X0:                " + Math.Round(P[1], 4) + " +- " + Math.Round(P_err[1], 4));
			PSEFitResultListBox.Items.Add("Y0:                " + Math.Round(P[2], 4) + " +- " + Math.Round(P_err[2], 4));
			if (ROIFitFcnDrop.SelectedIndex == 0)//Circular Gaussian
			{
				PSEFitResultListBox.Items.Add("Sigma:           " + Math.Round(P[3], 4) + " +- " + Math.Round(P_err[3], 4));
				PSEFitResultListBox.Items.Add("FWHM:         " + Math.Round(P[3] * 2.3548, 4) + " +- " + Math.Round(P_err[3] * 2.3548, 4));
				PSEFitResultListBox.Items.Add("Bias:              " + Math.Round(P[4], 4) + " +- " + Math.Round(P_err[4], 4));
				PSEFitResultListBox.Items.Add("Volume:         " + Math.Round(2 * Math.PI * P[0] * P[3] * P[3], 4));
			}
			if (ROIFitFcnDrop.SelectedIndex == 1)//Elliptical Gaussian
			{
				PSEFitResultListBox.Items.Add("Phi:               " + Math.Round(P[3], 4) + " +- " + Math.Round(P_err[3], 4));
				PSEFitResultListBox.Items.Add("Sigma_X:       " + Math.Round(P[4], 4) + " +- " + Math.Round(P_err[4], 4));
				PSEFitResultListBox.Items.Add("FWHM_X:     " + Math.Round(P[4] * 2.3548, 4) + " +- " + Math.Round(P_err[4] * 2.3548, 4));
				PSEFitResultListBox.Items.Add("Sigma_Y:       " + Math.Round(P[5], 4) + " +- " + Math.Round(P_err[5], 4));
				PSEFitResultListBox.Items.Add("FWHM_Y:     " + Math.Round(P[5] * 2.3548, 4) + " +- " + Math.Round(P_err[5] * 2.3548, 4));
				PSEFitResultListBox.Items.Add("Bias:              " + Math.Round(P[6], 4) + " +- " + Math.Round(P_err[6], 4));
				PSEFitResultListBox.Items.Add("Volume:         " + Math.Round(2 * Math.PI * P[0] * P[4] * P[5], 4));
			}
			if (ROIFitFcnDrop.SelectedIndex == 2)//Circular Moffat
			{
				PSEFitResultListBox.Items.Add("Theta:           " + Math.Round(P[3], 4) + " +- " + Math.Round(P_err[3], 4));
				PSEFitResultListBox.Items.Add("Beta:             " + Math.Round(P[4], 4) + " +- " + Math.Round(P_err[4], 4));
				PSEFitResultListBox.Items.Add("FWHM:         " + Math.Round(2 * P[3] * Math.Sqrt(Math.Pow(2, 1 / P[4]) - 1), 4));
				PSEFitResultListBox.Items.Add("Bias:              " + Math.Round(P[5], 4) + " +- " + Math.Round(P_err[5], 4));
				PSEFitResultListBox.Items.Add("Volume:         " + Math.Round(Math.PI * P[3] * P[3] * P[0] / (P[4] - 1), 4));
			}
			if (ROIFitFcnDrop.SelectedIndex == 3)//Elliptical Moffat
			{
				PSEFitResultListBox.Items.Add("Phi:               " + Math.Round(P[3], 4) + " +- " + Math.Round(P_err[3], 4));
				PSEFitResultListBox.Items.Add("Theta_X:       " + Math.Round(P[4], 4) + " +- " + Math.Round(P_err[4], 4));
				PSEFitResultListBox.Items.Add("Theta_Y:       " + Math.Round(P[5], 4) + " +- " + Math.Round(P_err[5], 4));
				PSEFitResultListBox.Items.Add("Beta:              " + Math.Round(P[6], 4) + " +- " + Math.Round(P_err[6], 4));
				PSEFitResultListBox.Items.Add("FWHM_X:     " + Math.Round(2 * P[4] * Math.Sqrt(Math.Pow(2, 1 / P[6]) - 1), 4));
				PSEFitResultListBox.Items.Add("FWHM_Y:     " + Math.Round(2 * P[5] * Math.Sqrt(Math.Pow(2, 1 / P[6]) - 1), 4));
				PSEFitResultListBox.Items.Add("Bias:              " + Math.Round(P[7], 4) + " +- " + Math.Round(P_err[7], 4));
				PSEFitResultListBox.Items.Add("Volume:         " + Math.Round(Math.PI * P[4] * P[5] * P[0] / (P[6] - 1), 4));
			}
			PSEFitResultListBox.Items.Add("Chi^2/dof:     " + Math.Round(chisq_norm, 4));
			PSEFitResultListBox.Items.Add(fitmsg);
			PSEFitResultListBox.Visible = true;
			PSEFitResultListBox.Refresh();

			if (ROIViewFitChck.Checked)
			{
				MLCCDLAB.MLSurface surf = new MLCCDLAB.MLSurface();
				double[,] fit;
				if (ROIFitFcnDrop.SelectedIndex <= 1)
					fit = JPMath.Gaussian2d(XSUBRANGE, YSUBRANGE, P, false);
				else
					fit = JPMath.Moffat2d(XSUBRANGE, YSUBRANGE, P, false);
				MWNumericArray mwfit = new MWNumericArray(fit);
				MWNumericArray mwsubim = new MWNumericArray(SUBIMAGE);
				MWCharArray type = new MWCharArray(ROIFitFcnDrop.Text);
				surf.Surf_FitOverlay(mwsubim, mwfit, type);
			}
		}

		private void ROICompoundFit()
		{
			bool view = ROIViewFitChck.Checked;

			int count = MARKCOORDS.GetLength(1), func = 0;
			string funcstr = "";

			if (ROIFitFcnDrop.SelectedIndex == 0)//Circular Gaussian: G(x,y|P) = P(0)*exP(-((x-P(1))^2 + (y - P(2))^2)/(2*P(3)^2)) + P(4)
			{
				func = 5;
				funcstr = "Circular Gaussian: G(x,y|P) = P(0)*exp(-((x-P(1))^2 + (y - P(2))^2)/(2*P(3)^2)) + P(4)";
			}
			if (ROIFitFcnDrop.SelectedIndex == 1)//Elliptical Gaussian: G(x,y|P) = P(0)*exp(-((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 / (2*P(4)^2) - (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3))).^2 / (2*P(5)^2) ) + P(6)
			{
				func = 7;
				funcstr = "Elliptical Gaussian: G(x,y|P) = P(0)*exp(-((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 / (2*P(4)^2) - (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3))).^2 / (2*P(5)^2) ) + P(6)";
			}
			if (ROIFitFcnDrop.SelectedIndex == 2)//Circular Moffat: M(x,y|P) = P(0) * ( 1 + { (x-P(1))^2 + (y-P(2))^2 } / P(3)^2 ) (-P(4)) + P(5)
			{
				func = 6;
				funcstr = "Circular Moffat: M(x,y|P) = P(0) * ( 1 + { (x-P(1))^2 + (y-P(2))^2 } / P(3)^2 ) (-P(4)) + P(5)";
			}
			if (ROIFitFcnDrop.SelectedIndex == 3)//Elliptical Moffat: M(x,y|P) = P(0) * ( 1 + { ((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 } / P(4)^2 + { (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3)))^2 } / P(5)^2 ) (-P(6)) + P(7)
			{
				func = 8;
				funcstr = "Elliptical Moffat: M(x,y|P) = P(0) * ( 1 + { ((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 } / P(4)^2 + { (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3)))^2 } / P(5)^2 ) (-P(6)) + P(7)";
			}

			double[,] P = new double[func, count];
			double[,] PLB = new double[func, count];
			double[,] PUB = new double[func, count];
			double[,] P_err = new double[func, count];
			double[,] fit_resid = new double[SUBIMAGE.GetLength(0), SUBIMAGE.GetLength(1)];

			#region OldCompoundSetParams
			for (int i = 0; i < count; i++)
			{
				P[0, i] = IMAGESET[IMAGESETINDEX][(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] - SUBIMAGEMIN;
				P[1, i] = MARKCOORDS[0, i];
				P[2, i] = MARKCOORDS[1, i];
				P[func - 1, i] = SUBIMAGEMIN;

				PLB[0, i] = P[0, i] / 3;
				PLB[1, i] = MARKCOORDS[0, i] - 1;
				PLB[2, i] = MARKCOORDS[1, i] - 1;
				PLB[func - 1, i] = SUBIMAGEMIN - P[0, i] / 2;

				PUB[0, i] = P[0, i] * 3;
				PUB[1, i] = MARKCOORDS[0, i] + 1;
				PUB[2, i] = MARKCOORDS[1, i] + 1;
				PUB[func - 1, i] = SUBIMAGEMIN + P[0, i] / 2;
			}

			if (ROIFitFcnDrop.SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
				for (int i = 0; i < count; i++)
				{
					P[3, i] = 2;
					PLB[3, i] = 0.1;
					PUB[3, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					if (SetParametersChck.Checked)
					{
						P[3, i] = Convert.ToDouble(FPW.PITXTARRAY[3].Text);

						if (FPW.ConstrainBtn.Checked)
						{
							PLB[3, i] = Convert.ToDouble(FPW.PLBTXTARRAY[3].Text);
							PUB[3, i] = Convert.ToDouble(FPW.PUBTXTARRAY[3].Text);
						}
					}
				}
			if (ROIFitFcnDrop.SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
				for (int i = 0; i < count; i++)
				{
					P[3, i] = 0;
					PLB[3, i] = -Math.PI;
					PUB[3, i] = Math.PI;

					P[4, i] = 2;
					PLB[4, i] = 0.1;
					PUB[4, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					P[5, i] = 2;
					PLB[5, i] = 0.1;
					PUB[5, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					if (SetParametersChck.Checked)
					{
						P[4, i] = Convert.ToDouble(FPW.PITXTARRAY[4].Text);
						P[5, i] = Convert.ToDouble(FPW.PITXTARRAY[5].Text);

						if (FPW.ConstrainBtn.Checked)
						{
							PLB[4, i] = Convert.ToDouble(FPW.PLBTXTARRAY[4].Text);
							PUB[4, i] = Convert.ToDouble(FPW.PUBTXTARRAY[4].Text);

							PLB[5, i] = Convert.ToDouble(FPW.PLBTXTARRAY[5].Text);
							PUB[5, i] = Convert.ToDouble(FPW.PUBTXTARRAY[5].Text);
						}
					}
				}
			if (ROIFitFcnDrop.SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) (-p(4)) + p(5)
				for (int i = 0; i < count; i++)
				{
					P[3, i] = 2;
					PLB[3, i] = 0.1;
					PUB[3, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					P[4, i] = 2;
					PLB[4, i] = 1;
					PUB[4, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					if (SetParametersChck.Checked)
					{
						P[3, i] = Convert.ToDouble(FPW.PITXTARRAY[3].Text);
						P[4, i] = Convert.ToDouble(FPW.PITXTARRAY[4].Text);

						if (FPW.ConstrainBtn.Checked)
						{
							PLB[3, i] = Convert.ToDouble(FPW.PLBTXTARRAY[3].Text);
							PUB[3, i] = Convert.ToDouble(FPW.PUBTXTARRAY[3].Text);

							PLB[4, i] = Convert.ToDouble(FPW.PLBTXTARRAY[4].Text);
							PUB[4, i] = Convert.ToDouble(FPW.PUBTXTARRAY[4].Text);
						}
					}
				}
			if (ROIFitFcnDrop.SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) (-p(6)) + p(7)
				for (int i = 0; i < count; i++)
				{
					P[3, i] = 0;
					PLB[3, i] = -Math.PI;
					PUB[3, i] = Math.PI;

					P[4, i] = 2;
					PLB[4, i] = 0.1;
					PUB[4, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					P[5, i] = 2;
					PLB[5, i] = 0.1;
					PUB[5, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					P[6, i] = 2;
					PLB[6, i] = 1;
					PUB[6, i] = Math.Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

					if (SetParametersChck.Checked)
					{
						P[4, i] = Convert.ToDouble(FPW.PITXTARRAY[4].Text);
						P[5, i] = Convert.ToDouble(FPW.PITXTARRAY[5].Text);
						P[6, i] = Convert.ToDouble(FPW.PITXTARRAY[6].Text);

						if (FPW.ConstrainBtn.Checked)
						{
							PLB[4, i] = Convert.ToDouble(FPW.PLBTXTARRAY[4].Text);
							PUB[4, i] = Convert.ToDouble(FPW.PUBTXTARRAY[4].Text);

							PLB[5, i] = Convert.ToDouble(FPW.PLBTXTARRAY[5].Text);
							PUB[5, i] = Convert.ToDouble(FPW.PUBTXTARRAY[5].Text);

							PLB[6, i] = Convert.ToDouble(FPW.PLBTXTARRAY[6].Text);
							PUB[6, i] = Convert.ToDouble(FPW.PUBTXTARRAY[6].Text);
						}
					}
				}
			#endregion

			double[] xpos = new double[MARKCOORDS.GetLength(1)];
			double[] ypos = new double[MARKCOORDS.GetLength(1)];
			for (int i = 0; i < xpos.Length; i++)
			{
				xpos[i] = MARKCOORDS[0, i];
				ypos[i] = MARKCOORDS[1, i];
			}

			string fitmsg = "";
			if (ROIFitFcnDrop.SelectedIndex <= 1)//Gaussian
			{
				//JPMath.Fit_Gaussian2d_Compound(XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid);

				if (ROIFitStatsTypeDrop.SelectedIndex == 0)
					JPMath.Fit_PointSource_Compound(ROIFITCOMPOUNDMODELNAME, ROIFITMINIMIZATIONTYPE, XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, ref P, ref P_err, ref fit_resid, out fitmsg);
			}
			else//Moffat
			{
				JPMath.Fit_Moffat2d_Compound(XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid);

				/*if (ROIFitStatsTypeDrop.SelectedIndex == 0)
					JPMath.Fit_PointSource_Compound("Moffat", "ls", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 1)
					JPMath.Fit_PointSource_Compound("Moffat", "chisq", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 2)
					JPMath.Fit_PointSource_Compound("Moffat", "robust", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 3)
					JPMath.Fit_PointSource_Compound("Moffat", "cstat", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);*/
			}

			double chisq_norm = 0;
			for (int i = 0; i < SUBIMAGE.GetLength(0); i++)
				for (int j = 0; j < SUBIMAGE.GetLength(1); j++)
				{
					if (SUBIMAGE[i, j] - P[func - 1, count - 1] == 0)
						chisq_norm += fit_resid[i, j] * fit_resid[i, j];
					else
						chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math.Abs(SUBIMAGE[i, j] - P[func - 1, count - 1]);
				}
			chisq_norm /= (SUBIMAGE.Length - P.Length + count - 1);

			PSETableViewer v = new PSETableViewer();
			v.PSETable.ColumnCount = func;
			v.PSETable.RowCount = count;

			for (int i = 0; i < func; i++)
				v.PSETable.Columns[i].HeaderText = "P" + i;

			v.PSETable.ColumnCount += 2;
			if (ROIFitFcnDrop.SelectedIndex == 1 || ROIFitFcnDrop.SelectedIndex == 3)
				v.PSETable.ColumnCount++;
			v.PSETable.Columns[func].HeaderText = "Volume";
			v.PSETable.Columns[func + 1].HeaderText = "FWHM";
			if (ROIFitFcnDrop.SelectedIndex == 1 || ROIFitFcnDrop.SelectedIndex == 3)
			{
				v.PSETable.Columns[func + 1].HeaderText = "FWHMX";
				v.PSETable.Columns[func + 2].HeaderText = "FWHMY";
			}

			for (int i = 0; i < count; i++)
				for (int j = 0; j < func; j++)
					v.PSETable[j, i].Value = P[j, i];

			double volume = 0, FWHM = 0, FWHMX = 0, FWHMY = 0;
			for (int i = 0; i < count; i++)
			{
				if (ROIFitFcnDrop.SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
				{
					volume = Math.Round(2 * Math.PI * P[0, i] * P[3, i] * P[3, i], 4);
					FWHM = Math.Round(P[3, i] * 2.3548, 4);
				}
				if (ROIFitFcnDrop.SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
				{
					volume = Math.Round(2 * Math.PI * P[0, i] * P[4, i] * P[5, i], 4);
					FWHMX = Math.Round(P[4, i] * 2.3548, 4);
					FWHMY = Math.Round(P[5, i] * 2.3548, 4);
				}
				if (ROIFitFcnDrop.SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) (-p(4)) + p(5)
				{
					volume = Math.Round(Math.PI * P[3, i] * P[3, i] * P[0, i] / (P[4, i] - 1), 4);
					FWHM = Math.Round(2 * P[3, i] * Math.Sqrt(Math.Pow(2, 1 / P[4, i]) - 1), 4);
				}
				if (ROIFitFcnDrop.SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) (-p(6)) + p(7)
				{
					volume = Math.Round(Math.PI * P[4, i] * P[5, i] * P[0, i] / (P[6, i] - 1), 4);
					FWHMX = Math.Round(2 * P[4, i] * Math.Sqrt(Math.Pow(2, 1 / P[6, i]) - 1), 4);
					FWHMY = Math.Round(2 * P[5, i] * Math.Sqrt(Math.Pow(2, 1 / P[6, i]) - 1), 4);
				}

				v.PSETable[func, i].Value = volume;
				v.PSETable[func + 1, i].Value = FWHM;

				if (ROIFitFcnDrop.SelectedIndex == 1 || ROIFitFcnDrop.SelectedIndex == 3)
				{
					v.PSETable[func + 1, i].Value = FWHMX;
					v.PSETable[func + 2, i].Value = FWHMY;
				}
			}

			v.Text = funcstr + "; ChiSqNorm: " + Math.Round(chisq_norm, 3) + "; " + fitmsg;
			v.Show(this);

			if (view)
			{
				double[,] fit = new double[SUBIMAGE.GetLength(0), SUBIMAGE.GetLength(1)];
				for (int x = 0; x < SUBIMAGE.GetLength(0); x++)
					for (int y = 0; y < SUBIMAGE.GetLength(1); y++)
						fit[x, y] = SUBIMAGE[x, y] - fit_resid[x, y];

				MLCCDLAB.MLSurface surf = new MLCCDLAB.MLSurface();
				MWNumericArray mwfit = new MWNumericArray(fit);
				MWNumericArray mwsubim = new MWNumericArray(SUBIMAGE);
				MWCharArray type = new MWCharArray(ROIFitFcnDrop.Text);
				surf.Surf_FitOverlay(mwsubim, mwfit, type);
			}
		}

		private void PSESaveKernelsChck_CheckedChanged(object sender, EventArgs e)
		{
			if (PSESaveKernelsChck.Checked)//get folder to save files in
			{
				FolderBrowserDialog fdlg = new FolderBrowserDialog();
				fdlg.SelectedPath = Convert.ToString(JPFITS.REG.GetReg("CCDLAB", "PSFolderPath"));
				if (fdlg.ShowDialog() == DialogResult.OK)
				{
					PSESAVEKERNELPATH = fdlg.SelectedPath;
					JPFITS.REG.SetReg("CCDLAB", "PSFolderPath", fdlg.SelectedPath);
				}
				else
				{
					PSESaveKernelsChck.Checked = false;
					PSESAVEKERNELPATH = null;
				}
			}
			else
				PSESAVEKERNELPATH = null;
		}

		private void COGBtn_Click(object sender, EventArgs e)
		{
			if (FIRSTLOAD)
				return;

			if ((int)COGIgnoreNPtsUpD.Value > (int)HalfWidthXUpD.Value + 1)
				COGIgnoreNPtsUpD.Value = (int)HalfWidthXUpD.Value + 1;
			double[] npts = null;
			double[] cog = null;
			string text = "Source Signal" + "	" + "Background (per pixel)" + "	" + "Index";
			double bg = 0, signal = 0;
			PSEFitResultListBox.Items.Clear();

			int[] inds;
			if (COGBatchChck.Checked)
			{
				inds = new int[IMAGESET.Count];
				for (int i = 0; i < IMAGESET.Count; i++)
					inds[i] = i;
			}
			else
				inds = new int[1] { IMAGESETINDEX };

			double[] RFitBatchIntercept = new double[inds.Length];
			double[] RFitBatchSlope = new double[inds.Length];
			double[] RFitBatchIndex = new double[inds.Length];

			for (int k = 0; k < inds.Length; k++)
			{
				double[,] subimg = IMAGESET[inds[k]].GetSubImage(XSUBRANGE[SUBIMAGE_HWX], YSUBRANGE[SUBIMAGE_HWY], SUBIMAGE_HWX, SUBIMAGE_HWY);
				cog = JPFITS.PointSourceExtractor.COG(subimg, (int)COGIgnoreNPtsUpD.Value, out npts, out bg, out signal);

				RFitBatchIntercept[k] = signal;
				RFitBatchSlope[k] = bg;
				RFitBatchIndex[k] = inds[k];

				PSEFitResultListBox.Items.Add("Image " + inds[k] + ":");
				PSEFitResultListBox.Items.Add("Source Signal: " + signal);
				PSEFitResultListBox.Items.Add("Background (per pixel): " + bg);

				text += "\r\n" + signal + "	" + bg + "	" + inds[k];
			}
			Clipboard.SetText(text);
			PSEFitResultListBox.Items.Add(("(copied to clipboard as table)"));
			PSEFitResultListBox.Visible = true;

			if (COG_PLOT == null || COG_PLOT.IsDisposed)
				COG_PLOT = new Plotter("COG", true, true);
			COG_PLOT.ChartGraph.Series.Clear();

			if (COGViewChck.Checked)
			{
				if (!COGBatchChck.Checked)
				{
					string title = "y = a + b*x : a = " + signal.ToString() + ", b = " + bg.ToString();
					COG_PLOT.ChartGraph.PlotXYData(npts, cog, title, "N Pixels", "Counts", JPChart.SeriesType.Point, "COG");

					double[] yline = new double[2] { signal, signal + bg * npts[npts.Length - 1] };
					double[] xline = new double[2] { 0, npts[npts.Length - 1] };
					COG_PLOT.ChartGraph.AddXYData(xline, yline, JPChart.SeriesType.Line, "COG Fit");

					double[] xdd = new double[1] { npts[cog.Length - (int)COGIgnoreNPtsUpD.Value] };
					double[] ydd = new double[1] { cog[cog.Length - (int)COGIgnoreNPtsUpD.Value] };
					COG_PLOT.ChartGraph.AddXYData(xdd, ydd, JPChart.SeriesType.Point, "COG Fit Start");

					BackgroundCountsPixelFrameTxt.Text = bg.ToString("#.0000");
				}
				else
					COG_PLOT.ChartGraph.PlotXYData(RFitBatchIndex, RFitBatchIntercept, "Source Counts vs. Frame #", "Frame #", "Source Count", JPChart.SeriesType.Point, "COG");

				COG_PLOT.Text = "Curve of Growth Photometry";
				COG_PLOT.TopMost = true;
				COG_PLOT.Show();
			}
		}

		private void PSELoadSrcBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET == null || IMAGESET.Count == 0)
			{
				MessageBox.Show("Please load an image first...", "Error");
				return;
			}

			if (PSELoadSrcDrop.SelectedIndex <= 1 && !WorldCoordinateSolution.Exists(IMAGESET[IMAGESETINDEX].Header, new string[2] { "TAN", "TAN" }))
			{
				MessageBox.Show("CD matrix for WCS not found in current image header. Can not transform [RA, Dec] to [x, y]...", "Error...");
				return;
			}

			if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
				IMAGESET[IMAGESETINDEX].WCS = new JPFITS.WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);

			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = true;
			ofd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "PSESavePath");
			if (PSELoadSrcDrop.SelectedIndex == 3)
				ofd.Filter = "PSE FITS BinTable|*.fits;*.fit;*.fts";
			else
			{
				ofd.Filter = "Tab Delimited Text|*.txt|CSV (Comma Delimited)|*.csv";
				ofd.Title = "NOTE: First TWO columns of a textual file selection are the coordinates...";
				ofd.FilterIndex = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "PSELoadFilterIndex"));
			}
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;
			JPFITS.REG.SetReg("CCDLAB", "PSESavePath", ofd.FileName.Substring(0, ofd.FileName.LastIndexOf("\\")));

			if (PSELoadSrcDrop.SelectedIndex == 0 || PSELoadSrcDrop.SelectedIndex == 2)
			{
				JPFITS.REG.SetReg("CCDLAB", "PSELoadFilterIndex", ofd.FilterIndex);

				for (int i = 0; i < ofd.FileNames.Length; i++)
				{
					string delimit = "\t";
					if (ofd.FilterIndex == 2)
						delimit = ",";
					StreamReader sr;
					string line;

					int Nsrc = 0;
					sr = new StreamReader(ofd.FileNames[i]);
					int j = -1;

					while (!sr.EndOfStream)
					{
						line = sr.ReadLine();
						j++;
						if (j == 0)//check if first line is a header
						{
							int delimitindex = line.IndexOf(delimit);
							if (!JPMath.IsNumeric(line.Substring(0, delimitindex)))
								continue;
						}
						Nsrc++;
					}

					double[] c1 = new double[Nsrc];
					double[] c2 = new double[Nsrc];

					Nsrc = 0;
					sr.Close();
					sr = new StreamReader(ofd.FileNames[i]);
					j = -1;
					while (!sr.EndOfStream)
					{
						line = sr.ReadLine();
						j++;
						int delimitindex = line.IndexOf(delimit);
						if (j == 0)//check if header line
							if (!JPMath.IsNumeric(line.Substring(0, delimitindex)))
								continue;
						c1[Nsrc] = Convert.ToDouble(line.Substring(0, delimitindex));
						int nextdelimitindex = line.IndexOf(delimit, delimitindex + 1);
						if (nextdelimitindex == -1)
							nextdelimitindex = line.Length;
						c2[Nsrc] = Convert.ToDouble(line.Substring(delimitindex + 1, nextdelimitindex - delimitindex - 1));
						Nsrc++;
					}
					sr.Close();

					if (PSELoadSrcDrop.SelectedIndex == 0)//RA, Dec
					{
						PSESET.Add(new PointSourceExtractor());
						PSESETINDEX = PSESET.Count - 1;
						double[] Xcoords = new double[Nsrc];
						double[] Ycoords = new double[Nsrc];
						IMAGESET[IMAGESETINDEX].WCS.Get_Pixels(c1, c2, "TAN", out Xcoords, out Ycoords, true);
						PSESET[PSESETINDEX] = new PointSourceExtractor(IMAGESET[IMAGESETINDEX].Image, Xcoords, Ycoords, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);
						PSESET[PSESETINDEX].Generate_Source_RADec_Coords(IMAGESET[IMAGESETINDEX].WCS);
					}
					else if (PSELoadSrcDrop.SelectedIndex == 1)//X, Y
					{
						PSESET.Add(new PointSourceExtractor());
						PSESETINDEX = PSESET.Count - 1;

						PSESET[PSESETINDEX] = new PointSourceExtractor(IMAGESET[IMAGESETINDEX].Image, c1, c2, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);
					}
					
					PSEDrop.Items.Add(ofd.FileNames[i].Substring(ofd.FileNames[i].LastIndexOf("\\") + 1));
					if (i < ofd.FileNames.Length - 1)
						PSESETINDEX++;
				}
			}
			else if (PSELoadSrcDrop.SelectedIndex == 3)//PSE bintables
			{
				int Nnewpses = 0;
				for (int i = 0; i < ofd.FileNames.Length; i++)
				{
					string[] tables = FITSBinTable.GetAllExtensionNames(ofd.FileNames[i]);
					Nnewpses += tables.Length;
				}
				PSESET.Add(new PointSourceExtractor());
				PSESETINDEX = PSESET.Count - 1;

				//for (int i = 0; i < ofd.FileNames.Length; i++)
				//{
				//	string[] tables = FITSBinTable.GetAllExtensionNames(ofd.FileNames[i]);
				//	for (int j = 0; j < tables.Length; j++)
				//	{
				//		FITSBinTable bt = new FITSBinTable(ofd.FileNames[i], tables[j]);
				//		PSES[PSESINDEX] = new PointSourceExtractor(bt);

				//		PSEDrop.Items.Add(bt.ExtensionNameEXTNAME);
				//		if (j < PSES.Length - 1)
				//			PSESINDEX++;
				//	}
				//}
			}
			else if (PSELoadSrcDrop.SelectedIndex == 1)//RA Dec sexages
			{
				JPFITS.REG.SetReg("CCDLAB", "PSELoadFilterIndex", ofd.FilterIndex);

				for (int i = 0; i < ofd.FileNames.Length; i++)
				{
					double[] c1;
					double[] c2;
					JPFITS.WorldCoordinateSolution.SexagesimalFileToDegreeFile(ofd.FileNames[i], false, out c1, out c2);

					PSESET.Add(new PointSourceExtractor());
					PSESETINDEX = PSESET.Count - 1;

					double[] Xcoords = new double[c1.Length];
					double[] Ycoords = new double[c1.Length];
					IMAGESET[IMAGESETINDEX].WCS.Get_Pixels(c1, c2, "TAN", out Xcoords, out Ycoords, true);
					PSESET[PSESETINDEX] = new JPFITS.PointSourceExtractor(IMAGESET[IMAGESETINDEX].Image, Xcoords, Ycoords, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);
					PSESET[PSESETINDEX].Generate_Source_RADec_Coords(IMAGESET[IMAGESETINDEX].WCS);
					
					PSEDrop.Items.Add(ofd.FileNames[i].Substring(ofd.FileNames[i].LastIndexOf("\\") + 1));
					if (i < ofd.FileNames.Length - 1)
						PSESETINDEX++;
				}
			}

			PSETableViewBtn.Enabled = true;
			PSEDropContextPlotAll.PerformClick();
		}

		private void DisplayMenuSourceRegions_Help_Click(object sender, EventArgs e)
		{
			string str = "Use this to plot circular regions on the current image. \r\n";
			str += "Input is a CSV file with 4 columns: RA, Dec, Radius, Labels  \r\n\r\n";
			str += "Right Ascension and Declination must be in degrees; Radius in arcseconds; Labels are textual.";

			MessageBox.Show(str);
		}

		private void DisplayMenuSourceRegions_Load_Click(object sender, EventArgs e)
		{
			if (IMAGESET == null || IMAGESET.Count == 0)
			{
				MessageBox.Show("Must have an image loaded...", "Error...");
				return;
			}

			if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
				IMAGESET[IMAGESETINDEX].WCS = new WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);
			if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
				throw new Exception("No WCS solution in the image header - cannot draw region coordinates to pixel axes.");

			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = false;
			ofd.InitialDirectory = IMAGESET[IMAGESETINDEX].FilePath;
			ofd.Filter = "CSV (Comma Delimited)|*.csv";
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			StreamReader sr = new StreamReader(ofd.FileName);

			List<double> ras = new List<double>();
			List<double> dec = new List<double>();
			List<double> rad = new List<double>();
			List<string> lab = new List<string>();

			while (!sr.EndOfStream)
			{
				var line = sr.ReadLine();
				var values = line.Split(',');

				ras.Add(Convert.ToDouble(values[0]));
				dec.Add(Convert.ToDouble(values[1]));
				rad.Add(Convert.ToDouble(values[2]));//arcseconds
				lab.Add(values[3]);
			}

			sr.Close();

			DISPREGIONCOORD_X = new double[ras.Count];
			DISPREGIONCOORD_Y = new double[ras.Count];
			DISPREGIONCOORD_R = new double[ras.Count];
			DISPREGIONCOORD_L = new string[ras.Count];

			double x, y;
			for (int i = 0; i < ras.Count; i++)
			{
				IMAGESET[IMAGESETINDEX].WCS.Get_Pixel((double)ras[i], (double)dec[i], "TAN", out x, out y, true);
				DISPREGIONCOORD_X[i] = x;
				DISPREGIONCOORD_Y[i] = y;
				DISPREGIONCOORD_R[i] = rad[i] / IMAGESET[IMAGESETINDEX].WCS.GetCDELTn(1);
				DISPREGIONCOORD_L[i] = lab[i] + String.Format(" ({0})", i + 1);
			}

			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void DisplayMenuSourceRegions_Clear_Click(object sender, EventArgs e)
		{
			DISPREGIONCOORD_X = null;
			DISPREGIONCOORD_Y = null;
			DISPREGIONCOORD_R = null;
			DISPREGIONCOORD_L = null;

			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void DisplayMenuSourceRegions_Click(object sender, EventArgs e)
		{
			
		}		

		private void PSETableViewBtn_Click(object sender, EventArgs e)
		{
			if (PSESET.Count == 0)
				return;

			if (WorldCoordinateSolution.Exists(IMAGESET[IMAGESETINDEX].Header, new string[2] { "TAN", "TAN" }))
			{
				if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
					IMAGESET[IMAGESETINDEX].WCS = new WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);

				PSESET[PSESETINDEX].Generate_Source_RADec_Coords(IMAGESET[IMAGESETINDEX].WCS);
			}
			string[,] table = PSESET[PSESETINDEX].Source_Table;

			PSETableViewer PSETABLEVIEWER = new PSETableViewer(table);			

			PSETABLEVIEWER.Text = PSEDrop.Items[PSESETINDEX] + " " + PSESET[PSESETINDEX].LSFit_Equation;
			PSETABLEVIEWER.Show(this);
		}

		private void PSEFitResultCntxtCopySelected_Click(object sender, EventArgs e)
		{
			Clipboard.SetText(PSEFitResultListBox.Text);
		}

		private void PSEFitResultCntxtCopyAll_Click(object sender, EventArgs e)
		{
			string copy = "";
			bool removedj = false;
			for (int i = 0; i < PSEFitResultListBox.Items.Count; i++)
			{
				string line = (string)PSEFitResultListBox.Items[i];
				for (int j = 0; j < line.Length; j++)
				{
					while (line.Substring(j, 1) == " ")
					{
						line = line.Remove(j, 1);
						removedj = true;
					}
					if (removedj)
						line = line.Insert(j, "	");
					removedj = false;
				}

				copy += line + "\r\n";
			}
			Clipboard.SetText(copy);
		}

		private void PSEFitResultsCntxt_Opening(object sender, System.ComponentModel.CancelEventArgs e)
		{
			if (PSEFitResultListBox.SelectedIndex < 0)
				PSEFitResultCntxtCopySelected.Enabled = false;
			else
				PSEFitResultCntxtCopySelected.Enabled = true;
		}		

		private void PSEGroupizeBtn_Click(object sender, System.EventArgs e)
		{
			if (PSESET.Count == 0)
				return;

			PSESET[PSESETINDEX].GroupizePSE((double)PSEBackgroundRadUpD.Value);

			PSEDRAWGROUPREGIONS = true;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add(string.Concat("N Sources:   ", PSESET[PSESETINDEX].N_Sources));
			PSEFitResultListBox.Items.Add(string.Concat("N Groups:   ", PSESET[PSESETINDEX].NGroups));
		}

	}
}