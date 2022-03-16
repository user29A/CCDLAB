using System;
using System.Collections;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using JPFITS;
using MathWorks.MATLAB.NET.Arrays;
using System.Threading.Tasks;
using System.Threading;
using System.Collections.Concurrent;

namespace CCDLAB
{
	public partial class Form1
	{
		private void PSEFitChck_CheckedChanged(object sender, EventArgs e)
		{
			if (PSEFitChck.Checked)
			{
				PSEFitTypeChck.Enabled = true;
				//PSEFitTypeChck.SelectedIndex = 0;
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
			/*if (MARKCOORDS == null)
				return;

			if (!PSEFitChck.Checked || MARKCOORDS.Length == 0)
				return;*/

			if (PSES == null)
				return;
			if (PSES[PSESINDEX].N_Sources <= 0)
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
				PSES[PSESINDEX].Fit_Sources_Gaussian_Circular(P0, PLB, PUB);
			if (PSEFitTypeChck.SelectedIndex == 1)//circular gaussian
				PSES[PSESINDEX].Fit_Sources_Gaussian_Elliptical(P0, PLB, PUB);
			if (PSEFitTypeChck.SelectedIndex == 2)//circular moffat
				PSES[PSESINDEX].Fit_Sources_Moffat_Circular(P0, PLB, PUB);
			if (PSEFitTypeChck.SelectedIndex == 3)//elliptical moffat
				PSES[PSESINDEX].Fit_Sources_Moffat_Elliptical(P0, PLB, PUB);

			if (PSES[PSESINDEX].Fitted == false)//cancelled
			{
				ImageWindow.Refresh();
				Enabled = true;
				return;
			}

			double[,] P = PSES[PSESINDEX].Fitted_Parameter_List;
			double[] Amp = new double[PSES[PSESINDEX].N_Sources];
			double[] X = new double[PSES[PSESINDEX].N_Sources];
			double[] Y = new double[PSES[PSESINDEX].N_Sources];
			double[] BG = new double[PSES[PSESINDEX].N_Sources];
			for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
			{
				Amp[i] = P[0, i];
				X[i] = P[1, i];
				Y[i] = P[2, i];
				BG[i] = P[P.GetLength(0) - 1, i];
			}
			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add("N:  " + PSES[PSESINDEX].N_Sources);
			PSEFitResultListBox.Items.Add("Amplitude:  " + Math.Round(JPMath.Mean(Amp, true), 4) + " +- " + Math.Round(JPMath.Stdv(Amp, false), 4));
			PSEFitResultListBox.Items.Add("X:          " + Math.Round(JPMath.Mean(X, true), 4) + " +- " + Math.Round(JPMath.Stdv(X, false), 4));
			PSEFitResultListBox.Items.Add("Y:          " + Math.Round(JPMath.Mean(Y, true), 4) + " +- " + Math.Round(JPMath.Stdv(Y, false), 4));

			if (PSEFitTypeChck.SelectedIndex == 0)//symmetric gaussian
			{
				double[] Sig = new double[PSES[PSESINDEX].N_Sources];

				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
					Sig[i] = P[3, i];

				PSEFitResultListBox.Items.Add(string.Concat("FWHM:       ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Mean(Sig, true), 4), " +- ", Math.Round(2 * Math.Sqrt(2 * Math.Log(2)) * JPMath.Stdv(Sig, false), 4)));
			}

			if (PSEFitTypeChck.SelectedIndex == 1)//elliptical gaussian
			{
				double[] Phi = new double[PSES[PSESINDEX].N_Sources];
				double[] Xsig = new double[PSES[PSESINDEX].N_Sources];
				double[] Ysig = new double[PSES[PSESINDEX].N_Sources];

				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
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
				double[] Theta = new double[PSES[PSESINDEX].N_Sources];
				double[] Beta = new double[PSES[PSESINDEX].N_Sources];

				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
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
				double[] Phi = new double[PSES[PSESINDEX].N_Sources];
				double[] Xtheta = new double[PSES[PSESINDEX].N_Sources];
				double[] Ytheta = new double[PSES[PSESINDEX].N_Sources];
				double[] Beta = new double[PSES[PSESINDEX].N_Sources];

				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
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

		private void PSEWidthUpD_ValueChanged(object sender, EventArgs e)
		{
			if (PSEKernelRadUpD.Value == 0)
			{
				PSEKernelMinUpD.Enabled = false;
				PSEKernelMaxUpD.Enabled = false;
				PSEAutoBackgroundChck.Enabled = false;
				PSEAutoBackgroundChck.Checked = false;
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

			if (PSESeparationUpD.Value < PSEKernelRadUpD.Value)
				PSESeparationUpD.Value = PSEKernelRadUpD.Value;
			PSESeparationUpD.Minimum = PSEKernelRadUpD.Value;
		}

		private void SaveROIContext_Click(object sender, EventArgs e)
		{
			SaveFileDialog fsd = new SaveFileDialog();
			//fsd.InitialDirectory = 
			//fsd.Filter = 

			if (fsd.ShowDialog() == DialogResult.Cancel)
				return;

			JPFITS.FITSImage ff = new FITSImage(fsd.FileName, ROI_PATH_COORDS, false, false);
			ff.WriteImage(TypeCode.Double, false);
		}

		private void LoadROIContext_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			//ofd.InitialDirectory = 
			//ofd.Filter = 
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

		private void ROI_PATH_FILLREGION()
		{
			int xmin = int.MaxValue, xmax = int.MinValue, ymin = int.MaxValue, ymax = int.MinValue;
			JPMath.PointD[] pts = new JPMath.PointD[(ROI_PATH_COORDS.GetLength(1))];
			for (int i = 0; i < pts.Length; i++)
			{
				pts[i] = new JPMath.PointD(ROI_PATH_COORDS[0, i], ROI_PATH_COORDS[1, i], 0);

				if ((int)ROI_PATH_COORDS[0, i] < xmin)
					xmin = (int)ROI_PATH_COORDS[0, i];
				if ((int)ROI_PATH_COORDS[1, i] < ymin)
					ymin = (int)ROI_PATH_COORDS[1, i];
				if ((int)ROI_PATH_COORDS[0, i] > xmax)
					xmax = (int)ROI_PATH_COORDS[0, i];
				if ((int)ROI_PATH_COORDS[1, i] > ymax)
					ymax = (int)ROI_PATH_COORDS[1, i];
			}

			if (pts.Length > 200)
			{
				double skip = (double)(pts.Length) / 200;

				for (int i = 0; i < 200; i++)
					pts[i] = pts[(int)((double)(i) * skip)];

				Array.Resize(ref pts, 200);
			}
			pts[pts.Length - 1] = pts[0];

			ROI_REGION = new bool[IMAGESET[FILELISTINDEX].Width, IMAGESET[FILELISTINDEX].Height];

			JPMath.PointD.PolygonInteriorPointsRegion(ROI_REGION, pts, xmin, ymin, xmax, ymax);

			ImageUpD(IMAGESET[FILELISTINDEX].Image);
			ImageWindow.Refresh();
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

		private void PSEDrawROI_CheckedChanged(object sender, EventArgs e)
		{
			if (PSEDrawROI.Checked)
			{
				PSEEllipticalROI.Checked = false;
				DRAW_ROI_PATH = true;
				DRAW_ROI_PATH_START = true;
				ROI_PATH_COORDS = null;
				ROI_PATH_POINTS = null;

				/*if (File.Exists(CCDLABPATH + "ROI_PATH.FITS"))
				{
					ROI_PATH_COORDS = FITSImage.ReadImageArrayOnly(CCDLABPATH + "ROI_PATH.FITS", null);
					MAKEROIPATHPOINTS();
					ROI_PATH_FILLREGION();
				}*/

				ImageWindow.Refresh();
			}
			else
			{
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
				ImageWindow.Refresh();

				SUBIMAGE_HWX_OLD = SUBIMAGE_HWX;
				SUBIMAGE_HWY_OLD = SUBIMAGE_HWY;
				SUBIMAGEX0OLD = XSUBRANGE[SUBIMAGE_HWX];
				SUBIMAGEY0OLD = YSUBRANGE[SUBIMAGE_HWY];
				ShowCrosshair.Checked = false;

				SubImageSlideX.Value = ROIX0 + 1;
				SubImageSlideY.Value = ROIY0 + 1;
				SUBIMAGE_HWX = ROIXRad;//need this first
				SUBIMAGE_HWY = ROIYRad;//need this first
				HalfWidthXUpD.Value = ROIXRad;
				HalfWidthYUpD.Value = ROIYRad;
			}
			else
			{
				SUBIMAGE_HWX = this.SUBIMAGE_HWX_OLD;
				SUBIMAGE_HWY = this.SUBIMAGE_HWY_OLD;
				SubImageSlideX.Value = this.SUBIMAGEX0OLD + 1;
				SubImageSlideY.Value = this.SUBIMAGEY0OLD + 1;
				HalfWidthXUpD.Value = this.SUBIMAGE_HWX;
				HalfWidthYUpD.Value = this.SUBIMAGE_HWY;
				ROI_REGION = null;
			}
		}

		private void MakeEllipticalROI_REGION(int x0, int y0, int xradius, int yradius)
		{
			ROIX0 = x0;// SubImageSlideX.Value - 1;
			ROIY0 = y0;// SubImageSlideY.Value - 1;
			ROIXRad = xradius;// (int)HalfWidthXUpD.Value;
			ROIYRad = yradius;// (int)HalfWidthYUpD.Value;

			JPFITS.REG.SetReg("CCDLAB", "ROIX0", ROIX0);
			JPFITS.REG.SetReg("CCDLAB", "ROIY0", ROIY0);
			JPFITS.REG.SetReg("CCDLAB", "ROIXRad", ROIXRad);
			JPFITS.REG.SetReg("CCDLAB", "ROIYRad", ROIYRad);

			ROI_REGION = new bool[IMAGESET[FILELISTINDEX].Width, IMAGESET[FILELISTINDEX].Height];

			Parallel.For(0, IMAGESET[FILELISTINDEX].Width, x =>
			{
				double dx2 = (double)(x - ROIX0);
				dx2 *= dx2;
				dx2 /= (double)(ROIXRad * ROIXRad);
				for (int y = 0; y < IMAGESET[FILELISTINDEX].Height; y++)
				{
					double dy2 = (double)(y - ROIY0);
					dy2 *= dy2;
					dy2 /= (double)(ROIYRad * ROIYRad);

					if (dx2 + dy2 <= 1)
						ROI_REGION[x, y] = true;
				}
			});
		}

		private void PSEFindSrcBtn_MouseEnter(object sender, EventArgs e)
		{
			/*PSEFindSrcBtn.Font = new .Font(PSEFindSrcBtn.Font, FontStyle.Bold);
			PSEFindSrcBtn.Refresh();*/
		}

		private void PSEFindSrcBtn_MouseLeave(object sender, EventArgs e)
		{
			/*PSEFindSrcBtn.Font = new .Font(PSEFindSrcBtn.Font, FontStyle.Regular);
			PSEFindSrcBtn.Refresh();*/
		}

		private void PSEDropContextSave_Click(object sender, EventArgs e)
		{
			SaveFileDialog sf = new SaveFileDialog();
			sf.InitialDirectory = IMAGESET[FILELISTINDEX].FilePath;
			sf.Filter = "FITS|*.fits;*.fit;*.fts";
			sf.OverwritePrompt = false;
			if (sf.ShowDialog() == DialogResult.Cancel)
				return;

			for (int i = 0; i < PSEDrop.Items.Count; i++)
			{
				if (WorldCoordinateSolution.Exists(IMAGESET[FILELISTINDEX].Header, new string[] { "TAN", "TAN" }))
				{
					if (!IMAGESET[FILELISTINDEX].WCS.Exists())
						IMAGESET[FILELISTINDEX].WCS = new WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);

					PSES[i].Generate_Source_RADec_Coords(IMAGESET[FILELISTINDEX].WCS);
				}
				string[,] table = PSES[i].Source_Table;

				string[] ttypes = new string[table.GetLength(0)];
				for (int j = 0; j < ttypes.Length; j++)
					ttypes[j] = table[j, 0];

				object[] entries = new object[ttypes.Length];
				for (int j = 0; j < ttypes.Length; j++)
				{
					if (!JPMath.IsNumeric(table[j, 1]))
					{
						entries[j] = new string[table.GetLength(1) - 1];
						for (int k = 1; k < table.GetLength(1); k++)
							((string[])entries[j])[k - 1] = table[j, k];
					}
					else
					{
						entries[j] = new double[table.GetLength(1) - 1];
						for (int k = 1; k < table.GetLength(1); k++)
							((double[])entries[j])[k - 1] = Convert.ToDouble(table[j, k]);
					}
				}

				FITSBinTable bt = new FITSBinTable();
				bt.AddExtraHeaderKey("PSESET", PSES[i].PSEParametersSet.ToString(), "PSE parameters available");
				if (PSES[i].PSEParametersSet)
				{
					bt.AddExtraHeaderKey("PIXSAT", PSES[i].PixelSaturation.ToString(), "Pixel saturation threshold");
					bt.AddExtraHeaderKey("KERNRAD", PSES[i].KernelRadius.ToString(), "Pixel kernel radius");
					bt.AddExtraHeaderKey("SRCSEP", PSES[i].SourceSeparation.ToString(), "Pixel source separation");
					bt.AddExtraHeaderKey("PIXMIN", PSES[i].PixelMinimum.ToString(), "Pixel minimum threshold");
					bt.AddExtraHeaderKey("PIXMAX", PSES[i].PixelMaximum.ToString(), "Pixel maximum threshold");
					bt.AddExtraHeaderKey("KERNMIN", PSES[i].KernelMinimum.ToString(), "Kernel minimum threshold");
					bt.AddExtraHeaderKey("KERNMAX", PSES[i].KernelMaximum.ToString(), "Kernel maximum threshold");
					bt.AddExtraHeaderKey("AUTOBG", PSES[i].AutoBackground.ToString(), "Auto background");
					bt.AddExtraHeaderKey("SAVESRC", PSES[i].SavePointSources.ToString(), "Save sources");
					//bt.AddExtraHeaderKey("SAVESRCF", PSES[i].SavePointSources.ToString(), "Save sources file name template");
					bt.AddExtraHeaderKey("ROIONLY", PSES[i].SearchROI.ToString(), "Search ROI only");
				}
				bt.SetTTYPEEntries(ttypes, null, entries);
				bt.Write(sf.FileName, PSEDrop.Items[i].ToString(), true);
			}
		}

		private void PSEDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (PSESPLOTALL)
			{
				PSESPLOTALL = false;
				//return;
			}

			PSESINDEX = PSEDrop.SelectedIndex;
			if (PSESRECTS == null || PSESRECTS[PSESINDEX] == null)
			{
				ImageWindow.Refresh();
				SubImageWindow.Refresh();
				return;
			}
			ShowPSEChck.Checked = true;
			MAKEPSERECTS();
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add("N:  " + PSES[PSESINDEX].N_Sources);

			if (PSES[PSESINDEX].PSEParametersSet)
			{
				PSESaturationUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].PixelSaturation);
				PSEKernelRadUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].KernelRadius);
				PSESeparationUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].SourceSeparation);
				PSEPixelMaxUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].PixelMaximum);
				PSEPixelMinUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].PixelMinimum);
				PSEKernelMinUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].KernelMinimum);
				PSEKernelMaxUpD.Value = Convert.ToDecimal(PSES[PSESINDEX].KernelMaximum);
				PSEAutoBackgroundChck.Checked = PSES[PSESINDEX].AutoBackground;
				SavePSChck.Checked = PSES[PSESINDEX].SavePointSources;
				PSESeachROIOnlyChck.Checked = PSES[PSESINDEX].SearchROI;
			}
		}

		private void PSEDropContextPlotAll_Click(object sender, EventArgs e)
		{
			ShowPSEChck.Checked = true;
			PSESPLOTALL = true;
			SubImageWindow.Refresh();
			ImageWindow.Refresh();
		}

		private void PSEDropContextPlotNone_Click(object sender, EventArgs e)
		{
			ShowPSEChck.Checked = false;
			SubImageWindow.Refresh();
			ImageWindow.Refresh();
		}

		private void PSEDropContextRemove_Click(object sender, EventArgs e)
		{
			if (PSES == null || PSES.Length == 0)
				return;

			PointSourceExtractor[] temppses = new PointSourceExtractor[PSES.Length - 1];
			Rectangle[][] temprecs = new Rectangle[(PSES.Length - 1)][];

			int c = 0;
			for (int i = 0; i < PSES.Length; i++)
			{
				if (i != PSEDrop.SelectedIndex)
				{
					temppses[c] = PSES[i];
					temprecs[c] = PSESRECTS[i];
					c++;
				}
			}
			PSES = temppses;
			PSESRECTS = temprecs;
			if (PSESINDEX >= PSES.Length)
				PSESINDEX = PSES.Length - 1;

			PSEDrop.Items.RemoveAt(PSEDrop.SelectedIndex);
			PSEDrop.SelectedIndex = PSESINDEX;

			if (PSES.Length == 0)
			{
				PSES = null;
				PSESRECTS = null;
				PSESINDEX = -1;
				PSECOUNT = 0;
				PSEDrop.Enabled = false;
				ImageWindow.Refresh();
				SubImageWindow.Refresh();
			}
		}

		private void PSEDropContextClearAll_Click(object sender, EventArgs e)
		{
			PSES = null;
			PSESRECTS = null;
			PSESINDEX = -1;
			PSECOUNT = 0;
			PSEDrop.Items.Clear();
			PSEDrop.Enabled = false;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEDropContextAdd_Click(object sender, EventArgs e)
		{
			PSECOUNT++;
			PointSourceExtractor[] temppses = new PointSourceExtractor[PSES.Length + 1];
			Rectangle[][] temprecs = new Rectangle[(PSES.Length + 1)][];
			for (int i = 0; i < PSES.Length; i++)
			{
				temppses[i] = PSES[i];
				temprecs[i] = PSESRECTS[i];
			}
			PSES = temppses;
			PSESRECTS = temprecs;
			PSESINDEX = PSEDrop.Items.Count - 1;

			PSEDrop.Items.Add("PSE_" + PSECOUNT.ToString());
			PSEDrop.SelectedIndex = PSEDrop.Items.Count - 1;

			ShowPSEChck.Checked = false;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEFindSrcBtn_MouseUp(object sender, MouseEventArgs e)
		{
			if (FIRSTLOAD)
				return;

			string saveps = "";
			if (PSESAVEKERNELPATH != null)
				saveps = PSESAVEKERNELPATH + "//" + IMAGESET[FILELISTINDEX].FileName;

			if (e.Button == MouseButtons.Left)
			{
				//Enabled = false;

				double pix_min = (double)PSEPixelMinUpD.Value;
				double pix_max = (double)PSEPixelMaxUpD.Value;
				double pix_sat = (double)PSESaturationUpD.Value;
				double count_min = (double)PSEKernelMinUpD.Value;
				double count_max = (double)PSEKernelMaxUpD.Value;
				bool auto_bg = PSEAutoBackgroundChck.Checked;
				bool sn = (PSEPixelValLbl.Text.Contains("SN"));
				int kernel_radius = (int)PSEKernelRadUpD.Value;
				int src_sep = (int)PSESeparationUpD.Value;

				JPFITS.REG.SetReg("CCDLAB", "PSEPixValMin", pix_min.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEPixSaturation", pix_sat.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSECountValMin", count_min.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEPixValMax", pix_max.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSECountValMax", count_max.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSEWidth", PSEKernelRadUpD.Value.ToString());
				JPFITS.REG.SetReg("CCDLAB", "PSESeparation", PSESeparationUpD.Value.ToString());
				if (PSESeachROIOnlyChck.Checked)
				{
					if (PSEEllipticalROI.Checked)//elliptical ROI
						MakeEllipticalROI_REGION(SubImageSlideX.Value - 1, SubImageSlideY.Value - 1, (int)HalfWidthXUpD.Value, (int)HalfWidthYUpD.Value);

					if (!PSEEllipticalROI.Checked && !PSEDrawROI.Checked)//either elliptical nor drawn...so just existing curusor box
					{
						ROI_REGION = new bool[IMAGESET[FILELISTINDEX].Width, IMAGESET[FILELISTINDEX].Height];

						for (int x = 0; x < IMAGESET[FILELISTINDEX].Width; x++)
							for (int y = 0; y < IMAGESET[FILELISTINDEX].Height; y++)
								if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
									ROI_REGION[x, y] = true;
					}
				}

				if (PSEKernelRadUpD.Value == 0)
				{
					count_min = Double.MinValue;
					count_max = Double.MaxValue;
				}

				if (PSES == null)
				{
					PSECOUNT++;
					PSES = new PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
					PSESINDEX = 0;
				}
				else
					PSES[PSESINDEX] = new JPFITS.PointSourceExtractor();

				PSES[PSESINDEX].Extract_Sources(IMAGESET[FILELISTINDEX].Image, pix_sat, pix_min, pix_max, count_min, count_max, sn, kernel_radius, src_sep, auto_bg, saveps, ROI_REGION, true);

				if (PSES[PSESINDEX].N_Sources == 0)
				{
					MessageBox.Show("Found 0 sources matching search criteria...", "Nothing found...");
					Enabled = true;
					PSETableViewBtn.Enabled = false;
					return;
				}

				if (PSES[PSESINDEX].N_Sources == -1)//cancelled
				{
					ShowPSEChck.Checked = false;
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
					Enabled = true;
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
				if (PSES == null || PSES[PSESINDEX].N_Sources < 1)
					return;

				if (MessageBox.Show("Are you sure you want to re-determine the Point Source Extraction with the current cooridnates?", "Warning...", MessageBoxButtons.YesNo) == DialogResult.No)
					return;

				double[] Xcoords = new double[PSES[PSESINDEX].N_Sources];
				double[] Ycoords = new double[PSES[PSESINDEX].N_Sources];
				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
				{
					Xcoords[i] = PSES[PSESINDEX].Centroids_X[i];
					Ycoords[i] = PSES[PSESINDEX].Centroids_Y[i];
				}

				PSES[PSESINDEX] = new JPFITS.PointSourceExtractor();
				PSES[PSESINDEX].Extract_Sources(IMAGESET[FILELISTINDEX].Image, Xcoords, Ycoords, (int)PSEKernelRadUpD.Value, PSEAutoBackgroundChck.Checked, saveps);
			}

			float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[FILELISTINDEX].Width);
			float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[FILELISTINDEX].Height);
			if (PSESRECTS == null)
				PSESRECTS = new Rectangle[1][] { new Rectangle[PSES[PSESINDEX].N_Sources] };
			else
				PSESRECTS[PSESINDEX] = new Rectangle[PSES[PSESINDEX].N_Sources];

			Parallel.For(0, PSES[PSESINDEX].N_Sources, i =>
			{
				PSESRECTS[PSESINDEX][i] = new Rectangle((int)(((float)(PSES[PSESINDEX].Centroids_X[i]) + 0.5) * xsc - 3), (int)(((float)(PSES[PSESINDEX].Centroids_Y[i]) + 0.5) * ysc - 3), 7, 7);
				});

			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add(string.Concat("N Sources:   ", PSES[PSESINDEX].N_Sources));
			PSEFitResultListBox.Visible = true;
			ShowPSEChck.Checked = true;
			ShowPSEChck.Enabled = true;
			PSETableViewBtn.Enabled = true;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
			//Enabled = true;
		}

		private void PSEFindSrcBtn_MouseClick(object sender, MouseEventArgs e) { }

		private void PSEFindSrcBtn_Click(object sender, EventArgs e) { }

		private void ShowPSEChck_CheckedChanged(object sender, EventArgs e)
		{
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void PSEFitWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			/*int pix_min = (int)PSEPixelMinUpD.Value;
			int pix_max = (int)PSEPixelMaxUpD.Value;
			int count_min = (int)PSECountMinUpD.Value;
			int count_max = (int)PSECountMaxUpD.Value;
			bool auto_bg = PSEAutoBackgroundChck.Checked;
			int src_radius = (int)PSEWidthUpD.Value;
			int ImInd = Convert.ToInt32(e.Argument);

			pse = new PSE();
			pse.Extract(IMAGESET[ImInd].Image,(double)pix_min,(double)pix_max, (double)count_min, (double)count_max, !(PSESigmaCountBtn.Text == "SN"), src_width, auto_bg, false, null, false, 0, 0, 0, 0);//extracts sources and stores them inside class*/
		}

		private void PSEFitWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
		}

		private void PSEFitWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			/*Enabled = true;
			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add(string.Concat("N:   ",pse.N_Sources]);
			PSEFitResultListBox.Visible = true;*/
		}

		private void ROIFitFcnDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			SetParametersChck.Checked = false;
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

		private void ROIFitStatsTypeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "ROIFitStatsTypeDrop", ROIFitStatsTypeDrop.SelectedIndex);
		}

		private void ROIFitBtn_Click(object sender, EventArgs e)
		{
			//SUBIMAGE is the ROI

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
			if (PSES != null && PSES[PSESINDEX].N_Sources > 0)
			{
				ArrayList contained = new ArrayList();

				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
					if (PSES[PSESINDEX].Centroids_X[i] > XSUBRANGE[0] && PSES[PSESINDEX].Centroids_X[i] < XSUBRANGE[SUBIMAGE_HWX * 2] && PSES[PSESINDEX].Centroids_Y[i] > YSUBRANGE[0] && PSES[PSESINDEX].Centroids_Y[i] < YSUBRANGE[SUBIMAGE_HWY * 2])
					{
						contained.Add(PSES[PSESINDEX].Centroids_X[i]);
						contained.Add(PSES[PSESINDEX].Centroids_Y[i]);
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
			Enabled = false;

			double[] P = null;
			double[] P_err = null;
			double[] PLB = null;
			double[] PUB = null;
			double[,] fit_resid = new double[SUBIMAGE.GetLength(0), SUBIMAGE.GetLength(1)];

			if (ROIFitFcnDrop.SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
				P = new double[5];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 4, JPMath.Min(SUBIMAGE, false) };
			if (ROIFitFcnDrop.SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
				P = new double[7];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 0, 4, 4, JPMath.Min(SUBIMAGE, false) };
			if (ROIFitFcnDrop.SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) (-p(4)) + p(5)
				P = new double[6];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 4, 4, JPMath.Min(SUBIMAGE, false) };
			if (ROIFitFcnDrop.SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) (-p(6)) + p(7)
				P = new double[8];// { JPMath.Max(SUBIMAGE, false) - JPMath.Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 0, 4, 4, 4, JPMath.Min(SUBIMAGE, false) };
			P_err = new double[P.Length];

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

			string fitmsg = "";
			if (ROIFitFcnDrop.SelectedIndex == 0 || ROIFitFcnDrop.SelectedIndex == 1)//Gaussian
			{
				//JPMath.Fit_Gaussian2d(XSUBRANGE, YSUBRANGE, SUBIMAGE, P, PLB, PUB, P_err, fit_resid);

				if (ROIFitStatsTypeDrop.SelectedIndex == 0)
					JPMath.Fit_PointSource("Gaussian", "ls", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 1)
					JPMath.Fit_PointSource("Gaussian", "chisq", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 2)
					JPMath.Fit_PointSource("Gaussian", "robust", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 3)
					JPMath.Fit_PointSource("Gaussian", "cstat", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
			}
			if (ROIFitFcnDrop.SelectedIndex == 2 || ROIFitFcnDrop.SelectedIndex == 3)//Moffat
			{
				//JPMath.Fit_Moffat2d(XSUBRANGE, YSUBRANGE, SUBIMAGE, P, PLB, PUB, P_err, fit_resid);

				if (ROIFitStatsTypeDrop.SelectedIndex == 0)
					JPMath.Fit_PointSource("Moffat", "ls", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 1)
					JPMath.Fit_PointSource("Moffat", "chisq", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 2)
					JPMath.Fit_PointSource("Moffat", "robust", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 3)
					JPMath.Fit_PointSource("Moffat", "cstat", XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid, ref fitmsg);
			}

			double chisq_norm = 0;
			for (int i = 0; i < SUBIMAGE.GetLength(0); i++)
				for (int j = 0; j < SUBIMAGE.GetLength(1); j++)
				{
					if (SUBIMAGE[i, j] - P[P.Length - 1] == 0)
						chisq_norm += fit_resid[i, j] * fit_resid[i, j];
					else
						chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math.Abs(SUBIMAGE[i, j] - P[P.Length - 1]);
				}
			chisq_norm /= (SUBIMAGE.Length - P.Length);

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
				//.Screen.PrimaryScreen.Bounds.

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
				//surf.Surf_FitOverlayBar(mwsubim, mwfit, type);
			}

			Enabled = true;
		}

		private void ROICompoundFit()
		{
			Enabled = false;

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
				P[0, i] = IMAGESET[FILELISTINDEX].Image[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] - SUBIMAGEMIN;
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
				JPMath.Fit_Gaussian2d_Compound(XSUBRANGE, YSUBRANGE, SUBIMAGE, ref P, PLB, PUB, ref P_err, ref fit_resid);

				/*if (ROIFitStatsTypeDrop.SelectedIndex == 0)
					JPMath.Fit_PointSource_Compound("Gaussian", "ls", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 1)
					JPMath.Fit_PointSource_Compound("Gaussian", "chisq", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 2)
					JPMath.Fit_PointSource_Compound("Gaussian", "robust", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);
				else if (ROIFitStatsTypeDrop.SelectedIndex == 3)
					JPMath.Fit_PointSource_Compound("Gaussian", "cstat", XSUBRANGE, YSUBRANGE, SUBIMAGE, xpos, ypos, 1.0, P, P_err, fit_resid, fitmsg);*/
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
				//surf.Surf_FitOverlayBar(mwsubim, mwfit, type);
			}

			Enabled = true;
		}

		private void SavePSChck_CheckedChanged(object sender, EventArgs e)
		{
			if (SavePSChck.Checked)//get folder to save files in
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
					SavePSChck.Checked = false;
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
			double[] RFitBatchIntercept = null;
			double[] RFitBatchSlope = null;
			double[] RFitBatchIndex = null;
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
			{
				inds = new int[1];
				inds[0] = FILELISTINDEX;
			}
			RFitBatchIntercept = new double[inds.Length];
			RFitBatchSlope = new double[inds.Length];
			RFitBatchIndex = new double[inds.Length];

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

			if (COGViewChck.Checked)
			{
				if (COG_PLOT.IsDisposed)
					COG_PLOT = new JPPlot();

				if (!COGBatchChck.Checked)
				{
					string title = "y = a + b*x : a = " + signal.ToString() + ", b = " + bg.ToString();
					COG_PLOT.PlotLine(npts, cog, "N Pixels", "Counts", title, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "COG");

					double[] yline = new double[2] { signal, signal + bg * npts[npts.Length - 1] };
					double[] xline = new double[2] { 0, npts[npts.Length - 1] };
					COG_PLOT.AddLine(xline, yline, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "COG Fit");

					double[] xdd = new double[1] { npts[cog.Length - (int)COGIgnoreNPtsUpD.Value] };
					double[] ydd = new double[1] { cog[cog.Length - (int)COGIgnoreNPtsUpD.Value] };
					COG_PLOT.AddLine(xdd, ydd, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "COG Fit Start");

					BackgroundCountsPixelFrameTxt.Text = bg.ToString("#.0000");
				}
				else
					COG_PLOT.PlotLine(RFitBatchIndex, RFitBatchIntercept, "Frame #", "Source Count", "Source Counts vs. Frame #", System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "COG");

				COG_PLOT.Text = "Curve of Growth Photometry";
			}
		}

		private void PSELoadSrcBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET == null || IMAGESET.Count == 0)
			{
				MessageBox.Show("Please load an image first...", "Error");
				return;
			}

			if (PSELoadSrcDrop.SelectedIndex == 0 && !WorldCoordinateSolution.Exists(IMAGESET[FILELISTINDEX].Header, new string[2] { "TAN", "TAN" }))
			{
				MessageBox.Show("CD matrix for WCS not found in current image header. Can not transform [RA, Dec] to [x, y]...", "Error...");
				return;
			}

			if (!IMAGESET[FILELISTINDEX].WCS.Exists())
				IMAGESET[FILELISTINDEX].WCS = new JPFITS.WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);

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
					//sr.BaseStream.Position = 0;
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
						if (JPMath.Max(c1, false) > 24 || JPMath.Max(c2, false) > 90)
						{
							MessageBox.Show("The 'RA, Dec' values seem like they're actually pixel coordinates. The first two columns of the file must be 'RA, Dec'.", "Error...");
							return;
						}

						if (PSES == null)
						{
							PSES = new PointSourceExtractor[ofd.FileNames.Length];
							PSESRECTS = new Rectangle[ofd.FileNames.Length][];
							PSESINDEX = 0;
							PSEDrop.Enabled = true;
						}
						else//add PSES
						{
							PointSourceExtractor[] temppses = new PointSourceExtractor[PSES.Length + ofd.FileNames.Length];
							Rectangle[][] temprecs = new Rectangle[PSES.Length + ofd.FileNames.Length][];
							for (int ii = 0; ii < PSES.Length; ii++)
							{
								temppses[ii] = PSES[ii];
								temprecs[ii] = PSESRECTS[ii];
							}
							PSESINDEX = PSES.Length;
							PSES = temppses;
							PSESRECTS = temprecs;
						}

						double[] Xcoords = new double[Nsrc];
						double[] Ycoords = new double[Nsrc];
						IMAGESET[FILELISTINDEX].WCS.Get_Pixels(c1, c2, "TAN", out Xcoords, out Ycoords, true);
						PSES[PSESINDEX] = new JPFITS.PointSourceExtractor(Xcoords, Ycoords);
						PSES[PSESINDEX].Generate_Source_RADec_Coords(IMAGESET[FILELISTINDEX].WCS);
					}
					else if (PSELoadSrcDrop.SelectedIndex == 1)//X, Y
					{
						if (PSES == null)
						{
							PSES = new PointSourceExtractor[ofd.FileNames.Length];
							PSESRECTS = new Rectangle[ofd.FileNames.Length][];
							PSESINDEX = 0;
							PSEDrop.Enabled = true;
						}
						else//add PSES
						{
							PointSourceExtractor[] temppses = new PointSourceExtractor[PSES.Length + ofd.FileNames.Length];
							Rectangle[][] temprecs = new Rectangle[PSES.Length + ofd.FileNames.Length][];
							for (int ii = 0; ii < PSES.Length; ii++)
							{
								temppses[ii] = PSES[ii];
								temprecs[ii] = PSESRECTS[ii];
							}
							PSESINDEX = PSES.Length;
							PSES = temppses;
							PSESRECTS = temprecs;
						}

						PSES[PSESINDEX] = new JPFITS.PointSourceExtractor(c1, c2);
					}
					MAKEPSERECTS();
					PSECOUNT++;
					PSEDrop.Items.Add(ofd.FileNames[i].Substring(ofd.FileNames[i].LastIndexOf("\\") + 1));
					if (i < ofd.FileNames.Length - 1)
						PSESINDEX++;
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
				if (PSES == null)
				{
					PSES = new PointSourceExtractor[Nnewpses];
					PSESRECTS = new Rectangle[Nnewpses][];
					PSESINDEX = 0;
					PSEDrop.Enabled = true;
				}
				else//add PSES
				{
					PointSourceExtractor[] temppses = new PointSourceExtractor[PSES.Length + Nnewpses];
					Rectangle[][] temprecs = new Rectangle[PSES.Length + Nnewpses][];
					for (int i = 0; i < PSES.Length; i++)
					{
						temppses[i] = PSES[i];
						temprecs[i] = PSESRECTS[i];
					}
					PSESINDEX = PSES.Length;
					PSES = temppses;
					PSESRECTS = temprecs;
				}

				for (int i = 0; i < ofd.FileNames.Length; i++)
				{
					string[] tables = FITSBinTable.GetAllExtensionNames(ofd.FileNames[i]);
					for (int j = 0; j < tables.Length; j++)
					{
						FITSBinTable bt = new FITSBinTable(ofd.FileNames[i], tables[j]);
						PSES[PSESINDEX] = new PointSourceExtractor(bt);
						MAKEPSERECTS();
						PSECOUNT++;
						PSEDrop.Items.Add(bt.ExtensionNameEXTNAME);
						if (j < PSES.Length - 1)
							PSESINDEX++;
					}
				}
			}
			else if (PSELoadSrcDrop.SelectedIndex == 1)//RA Dec hexages
			{
				JPFITS.REG.SetReg("CCDLAB", "PSELoadFilterIndex", ofd.FilterIndex);

				for (int i = 0; i < ofd.FileNames.Length; i++)
				{
					double[] c1;
					double[] c2;
					JPFITS.WorldCoordinateSolution.SexagesimalFileToDegreeFile(ofd.FileNames[i], false, out c1, out c2);

					if (PSES == null)
					{
						PSES = new PointSourceExtractor[ofd.FileNames.Length];
						PSESRECTS = new Rectangle[ofd.FileNames.Length][];
						PSESINDEX = 0;
						PSEDrop.Enabled = true;
					}
					else//add PSES
					{
						PointSourceExtractor[] temppses = new PointSourceExtractor[PSES.Length + ofd.FileNames.Length];
						Rectangle[][] temprecs = new Rectangle[PSES.Length + ofd.FileNames.Length][];
						for (int ii = 0; ii < PSES.Length; ii++)
						{
							temppses[ii] = PSES[ii];
							temprecs[ii] = PSESRECTS[ii];
						}
						PSESINDEX = PSES.Length;
						PSES = temppses;
						PSESRECTS = temprecs;
					}

					double[] Xcoords = new double[c1.Length];
					double[] Ycoords = new double[c1.Length];
					IMAGESET[FILELISTINDEX].WCS.Get_Pixels(c1, c2, "TAN", out Xcoords, out Ycoords, true);
					PSES[PSESINDEX] = new JPFITS.PointSourceExtractor(Xcoords, Ycoords);
					PSES[PSESINDEX].Generate_Source_RADec_Coords(IMAGESET[FILELISTINDEX].WCS);

					MAKEPSERECTS();
					PSECOUNT++;
					PSEDrop.Items.Add(ofd.FileNames[i].Substring(ofd.FileNames[i].LastIndexOf("\\") + 1));
					if (i < ofd.FileNames.Length - 1)
						PSESINDEX++;
				}
			}

			PSETableViewBtn.Enabled = true;
			ShowPSEChck.Enabled = true;
			ShowPSEChck.Checked = true;
			PSEDropContextPlotAll.PerformClick();
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

		private void PSETableViewBtn_Click(object sender, EventArgs e)
		{
			if (PSES == null)
				return;

			if (WorldCoordinateSolution.Exists(IMAGESET[FILELISTINDEX].Header, new string[2] { "TAN", "TAN" }))
			{
				if (!IMAGESET[FILELISTINDEX].WCS.Exists())
					IMAGESET[FILELISTINDEX].WCS = new WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);

				PSES[PSESINDEX].Generate_Source_RADec_Coords(IMAGESET[FILELISTINDEX].WCS);
			}
			string[,] table = PSES[PSESINDEX].Source_Table;

			PSETableViewer PSETABLEVIEWER = new PSETableViewer();
			PSETABLEVIEWER.PSETable.ColumnCount = table.GetLength(0);
			PSETABLEVIEWER.PSETable.RowCount = table.GetLength(1) - 1;

			for (int i = 0; i < PSETABLEVIEWER.PSETable.ColumnCount; i++)
				PSETABLEVIEWER.PSETable.Columns[i].HeaderText = table[i, 0];

			string strvalue = "";
			for (int i = 0; i < PSETABLEVIEWER.PSETable.ColumnCount; i++)
				for (int j = 0; j < PSETABLEVIEWER.PSETable.RowCount; j++)
				{
					strvalue = table[i, j + 1];
					if (JPMath.IsNumeric(strvalue))
						if (strvalue == "0")
							PSETABLEVIEWER.PSETable[i, j].Value = 0.0;
						else
							PSETABLEVIEWER.PSETable[i, j].Value = Convert.ToDouble(strvalue);
					else
						PSETABLEVIEWER.PSETable[i, j].Value = strvalue;
				}

			for (int j = 0; j < PSETABLEVIEWER.PSETable.RowCount; j++)
				PSETABLEVIEWER.PSETable.Rows[j].HeaderCell.Value = (j + 1).ToString();

			PSETABLEVIEWER.Text = PSEDrop.Items[PSESINDEX] + " " + PSES[PSESINDEX].LSFit_Equation;
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

		private void WCSSolutionPtsCopyTableBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			bool cpexists = true;
			int n = 0;
			while (cpexists)
			{
				n++;
				if (IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCP1_" + n.ToString("000"), false) == -1)
					cpexists = false;
			}
			n--;

			if (n == 0)
			{
				MessageBox.Show("No WCS solution points found in header...");
				return;
			}

			double[] cp1 = new double[n];
			double[] cp2 = new double[n];
			double[] cv1 = new double[n];
			double[] cv2 = new double[n];
			double[] cd1 = new double[n];
			double[] cd2 = new double[n];

			for (int i = 1; i <= n; i++)
			{
				int index = IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCP1_" + i.ToString("000"), false);
				if (index != -1)
					cp1[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue(index));

				index = IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCP2_" + i.ToString("000"), false);
				if (index != -1)
					cp2[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue(index));

				index = IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCV1_" + i.ToString("000"), false);
				if (index != -1)
					cv1[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue(index));

				index = IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCV2_" + i.ToString("000"), false);
				if (index != -1)
					cv2[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue(index));

				index = IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCD1_" + i.ToString("000"), false);
				if (index != -1)
					cd1[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue(index));
				else
					cd1[i - 1] = Double.NaN;

				index = IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCD2_" + i.ToString("000"), false);
				if (index != -1)
					cd2[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue(index));
				else
					cd2[i - 1] = Double.NaN;
			}

			string clipbrd = "Source Pixel X-Centroid (pixels)" + "\t" + "Source Pixel Y-Centroid (pixels)" + "\t" + "Source Catalogue RA (degrees)" + "\t" + "Source Catalogue Decl (degrees)" + "\t" + "WCS RA Residual (arcsec)" + "\t" + "WCS Decl Residual (arcsec)";
			for (int i = 1; i <= n; i++)
				clipbrd += "\r\n" + cp1[i - 1] + "\t" + cp2[i - 1] + "\t" + cv1[i - 1] + "\t" + cv2[i - 1] + "\t" + cd1[i - 1] + "\t" + cd2[i - 1];

			Clipboard.SetText(clipbrd);

			MessageBox.Show("WCS Coordinates Table copied to clipboard...");
		}

		private void WCSAstroQueryLimitLLengthDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "WCSAstroQueryLimitLLength", WCSAstroQueryLimitLLengthDrop.SelectedIndex);
		}

		private void WCSPlotSolutionPtsBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			bool cpexists = true;
			int n = 0;
			while (cpexists)
			{
				n++;
				if (IMAGESET[FILELISTINDEX].Header.GetKeyIndex("WCP1_" + n.ToString("000"), false) == -1)
					cpexists = false;
			}
			n--;

			if (n == 0)
			{
				MessageBox.Show("No WCS solution points found in header to plot...");
				return;
			}

			MARKCOORDRECTS = new Rectangle[n];
			MARKCOORDS = new double[2, n];
			float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[FILELISTINDEX].Width);
			float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[FILELISTINDEX].Height);
			double[] cp1 = new double[n];
			double[] cp2 = new double[n];
			for (int i = 1; i <= n; i++)
			{
				cp1[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue("WCP1_" + i.ToString("000")));
				cp2[i - 1] = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue("WCP2_" + i.ToString("000")));
				MARKCOORDS[0, i - 1] = cp1[i - 1] - 1;
				MARKCOORDS[1, i - 1] = cp2[i - 1] - 1;
			}

			MAKEMARKCOORDRECTS();
			ImageWindow.Refresh();
			SubImageWindow.Refresh();

			WCSMenu.ShowDropDown();
			WCSSolutionPtsBtn.ShowDropDown();
		}

		private void WCSClearPlotSolutionPtsBtn_Click(object sender, EventArgs e)
		{
			MarkCoordClear.PerformClick();

			WCSMenu.ShowDropDown();
			WCSSolutionPtsBtn.ShowDropDown();
		}

		private void WCSRefineSolutionBtn_DropDownOpened(object sender, EventArgs e)
		{

		}

		private void WCSLoadSimbadAscii_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSRefineSolutionBtn.ShowDropDown();

			GET_CATALOGUE_NPTS((string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text, WCSAutoCatalogueCVAL1.Text, WCSAutoCatalogueCVAL2.Text, WCSAutoCatalogueMag.Text, Convert.ToInt32(WCSLoadListNPtsTxt.Text));

			//WCS = new JPFITS.WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);
			//WCS.Get_WCS(IMAGESET[FILELISTINDEX]);
			double[] cp1 = new double[WCS_RA.Length];
			double[] cp2 = new double[WCS_RA.Length];
			IMAGESET[FILELISTINDEX].WCS.Get_Pixels(WCS_RA, WCS_DEC, "TAN", out cp1, out cp2, true);

			MARKCOORDS = new double[2, WCS_RA.Length];
			for (int i = 0; i < WCS_RA.Length; i++)
			{
				MARKCOORDS[0, i] = cp1[i];
				MARKCOORDS[1, i] = cp2[i];
			}
			MAKEMARKCOORDRECTS();

			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void WCSListExciseToROI_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			bool[] inside = new bool[MARKCOORDRECTS.Length];
			int n = 0;

			if (PSESeachROIOnlyChck.Checked)
			{
				if (PSEEllipticalROI.Checked)//elliptical ROI
					MakeEllipticalROI_REGION(SubImageSlideX.Value - 1, SubImageSlideY.Value - 1, (int)HalfWidthXUpD.Value, (int)HalfWidthYUpD.Value);

				if (!PSEEllipticalROI.Checked && !PSEDrawROI.Checked)//either elliptical nor drawn...so just existing curusor box
				{
					ROI_REGION = new bool[IMAGESET[FILELISTINDEX].Width, IMAGESET[FILELISTINDEX].Height];

					for (int x = 0; x < IMAGESET[FILELISTINDEX].Width; x++)
						for (int y = 0; y < IMAGESET[FILELISTINDEX].Height; y++)
							if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
								ROI_REGION[x, y] = true;
				}
			}

			for (int i = 0; i < MARKCOORDRECTS.Length; i++)
				if (ROI_REGION[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]])
				{
					inside[i] = true;
					n++;
				}

			double[,] temp = new double[2, n];
			double[] ratemp = new double[n];
			double[] dectemp = new double[n];
			n = 0;
			for (int i = 0; i < MARKCOORDRECTS.Length; i++)
				if (inside[i])
				{
					temp[0, n] = MARKCOORDS[0, i];
					temp[1, n] = MARKCOORDS[1, i];
					ratemp[n] = WCS_RA[i];
					dectemp[n] = WCS_DEC[i];
					n++;
				}

			WCS_RA = new double[n];
			WCS_DEC = new double[n];
			MARKCOORDS = new double[2, n];
			for (int i = 0; i < n; i++)
			{
				WCS_RA[i] = ratemp[i];
				WCS_DEC[i] = dectemp[i];
				MARKCOORDS[0, i] = temp[0, i];
				MARKCOORDS[1, i] = temp[1, i];
			}
			MAKEMARKCOORDRECTS();

			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void WCSClarifyListSources_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			try
			{
				WCSMenu.ShowDropDown();
				AutoWCSMenuItem.ShowDropDown();
				WCSRefineSolutionBtn.ShowDropDown();

				bool[] match = new bool[MARKCOORDRECTS.Length];
				int n = 0;

				for (int i = 0; i < MARKCOORDRECTS.Length; i++)
					if ((int)MARKCOORDS[0, i] > 0 && (int)MARKCOORDS[0, i] < IMAGESET[FILELISTINDEX].Width && (int)MARKCOORDS[1, i] > 0 && (int)MARKCOORDS[1, i] < IMAGESET[FILELISTINDEX].Height)
						if (PSES[PSESINDEX].SourceBooleanMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] /*&& PSES[PSESINDEX].SourceIndexMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] < PSES[PSESINDEX].N_Sources*/)
						{
							n++;
							match[i] = true;
						}

				double[] cp1 = new double[n];
				double[] cp2 = new double[n];
				double[] ratemp = new double[n];
				double[] dectemp = new double[n];
				double[,] temp = new double[2, n];
				n = 0;
				for (int i = 0; i < MARKCOORDRECTS.Length; i++)
					if (match[i])
					{
						int ind = PSES[PSESINDEX].SourceIndexMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]];
						cp1[n] = PSES[PSESINDEX].Centroids_X[ind];
						cp2[n] = PSES[PSESINDEX].Centroids_Y[ind];
						ratemp[n] = WCS_RA[i];
						dectemp[n] = WCS_DEC[i];
						temp[0, n] = MARKCOORDS[0, i];
						temp[1, n] = MARKCOORDS[1, i];
						n++;
					}

				PSES[PSESINDEX] = new JPFITS.PointSourceExtractor(cp1, cp2);
				PSESRECTS = new Rectangle[1][];
				MAKEPSERECTS();

				WCS_RA = new double[n];
				WCS_DEC = new double[n];
				MARKCOORDS = new double[2, n];
				for (int i = 0; i < n; i++)
				{
					WCS_RA[i] = ratemp[i];
					WCS_DEC[i] = dectemp[i];
					MARKCOORDS[0, i] = temp[0, i];
					MARKCOORDS[1, i] = temp[1, i];
				}
				MAKEMARKCOORDRECTS();

				PSEFitResultListBox.Items.Clear();
				PSEFitResultListBox.Items.Add(string.Concat("N:   ", PSES[PSESINDEX].N_Sources));
				ImageWindow.Refresh();
				SubImageWindow.Refresh();
			}
			catch (Exception ee)
			{
				MessageBox.Show(ee.Data + "	" + ee.InnerException + "	" + ee.Message + "	" + ee.Source + "	" + ee.StackTrace + "	" + ee.TargetSite);
			}
		}

		private void WCSSolveList_Click(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			//WCS = new JPFITS.WorldCoordinateSolution();
			IMAGESET[FILELISTINDEX].WCS.Solve_WCS("TAN", PSES[PSESINDEX].Centroids_X, PSES[PSESINDEX].Centroids_Y, true, WCS_RA, WCS_DEC, IMAGESET[FILELISTINDEX].Header);
			FileTxtsUpD();
			double[] x = new double[MARKCOORDRECTS.Length];
			double[] y = new double[MARKCOORDRECTS.Length];
			IMAGESET[FILELISTINDEX].WCS.Get_Pixels(WCS_RA, WCS_DEC, "TAN", out x, out y, true);

			MARKCOORDS = new double[2, x.Length];
			for (int i = 0; i < x.Length; i++)
			{
				MARKCOORDS[0, i] = x[i];
				MARKCOORDS[1, i] = y[i];
			}
			MAKEMARKCOORDRECTS();

			SHOW_WCSCOORDS = true;
			WCSRADecShowChck.Checked = true;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void testbtnToolStripMenuItem_Click(object sender, System.EventArgs e) { }

		private void WCSAutoSolveBtn_Click(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.HideDropDown();
			AutoWCSMenuItem.HideDropDown();

			JPFITS.REG.SetReg("CCDLAB", "PSEWidth", PSEKernelRadUpD.Value.ToString());
			JPFITS.REG.SetReg("CCDLAB", "PSESeparation", PSESeparationUpD.Value.ToString());

			if (Convert.ToDouble(WCSScaleInitLB.Text) > Convert.ToDouble(WCSScaleInit.Text) || Convert.ToDouble(WCSScaleInitUB.Text) < Convert.ToDouble(WCSScaleInit.Text))
			{
				WCSMenu.ShowDropDown();
				AutoWCSMenuItem.ShowDropDown();
				MessageBox.Show("Problem with your initial scale settings...", "Error...");
				return;
			}

			if (Convert.ToDouble(WCSRotationInitLB.Text) > Convert.ToDouble(WCSRotationInit.Text) || Convert.ToDouble(WCSRotationInitUB.Text) < Convert.ToDouble(WCSRotationInit.Text))
			{
				WCSMenu.ShowDropDown();
				AutoWCSMenuItem.ShowDropDown();
				MessageBox.Show("Problem with your initial rotation settings...", "Error...");
				return;
			}

			if (PSESeachROIOnlyChck.Checked)
			{
				if (PSEEllipticalROI.Checked)//elliptical ROI
					MakeEllipticalROI_REGION(SubImageSlideX.Value - 1, SubImageSlideY.Value - 1, (int)HalfWidthXUpD.Value, (int)HalfWidthYUpD.Value);

				if (!PSEEllipticalROI.Checked && !PSEDrawROI.Checked)//either elliptical nor drawn...so just existing curusor box
				{
					ROI_REGION = new bool[IMAGESET[FILELISTINDEX].Width, IMAGESET[FILELISTINDEX].Height];

					for (int x = 0; x < IMAGESET[FILELISTINDEX].Width; x++)
						for (int y = 0; y < IMAGESET[FILELISTINDEX].Height; y++)
							if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
								ROI_REGION[x, y] = true;
				}
			}

			if (!WCSAutoExternalDLLChck.Checked)
			{
				if (Convert.ToInt32(WCSAutoNCatPtsTxt.Text) > 18 && WCSAutoDisplayChck.Checked)
				{
					if (MessageBox.Show("Too many points for serial display process. \r\r" + "Proceed without display?", "Warning", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;

					//else yes
					WCSAutoDisplayChck.Checked = false;
					WCSAutoSolveBtn.PerformClick();
					return;
				}

				if (WCSAutoSolveBtn.Text == "Cancel")
				{
					WCSAUTOCANCEL = true;
					WCSAutoSolveBtn.Text = "Solve";
					return;
				}
				WCSAutoSolveBtn.Text = "Cancel";
				WCSAUTOCANCEL = false;
				ProgressBar.Maximum = 100;

				WCSAutoBGWrkr.RunWorkerAsync();
			}
			else//use external DLL
			{
				WCSAS = new JPFITS.WCSAutoSolver("TAN", Convert.ToInt32(WCSAutoNCatPtsTxt.Text), IMAGESET[FILELISTINDEX], ROI_REGION, (double)PSESaturationUpD.Value, PSEAutoBackgroundChck.Checked, (int)PSEKernelRadUpD.Value, (int)PSESeparationUpD.Value, (string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text, WCSAutoCatalogueCVAL1.Text, WCSAutoCatalogueCVAL2.Text, WCSAutoCatalogueMag.Text, WCSAutoRefineChck.Checked);
				WCSAS.SolveAsync(Convert.ToDouble(WCSScaleInit.Text), Convert.ToDouble(WCSScaleInitLB.Text), Convert.ToDouble(WCSScaleInitUB.Text), Convert.ToDouble(WCSRotationInit.Text), Convert.ToDouble(WCSRotationInitLB.Text), Convert.ToDouble(WCSRotationInitUB.Text), 0.25, Convert.ToInt32(WCSAutoStopNMatchesText.Text), Convert.ToInt32(WCSAutoStopPercMatchesText.Text), WCSAutoConditionArraysChck.Checked, true);

				if (!WCSAS.Cancelled && WCSAS.Solved)
				{
					FileTxtsUpD();
					WCSRADecShowChck.Checked = false;
					WCSRADecShowChck.PerformClick();
				}
			}
		}

		private void WCSAutoBGWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			POLYPOINTS = null;
			POLYPOINTS2 = null;
			PSESRECTS = null;
			MARKCOORDRECTS = null;
			WCSRADecShowChck.Checked = false;
			SHOW_WCSCOORDS = false;
			ImageWindow.Refresh();

			float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[FILELISTINDEX].Width);
			float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[FILELISTINDEX].Height);
			int nCATpts = Convert.ToInt32(WCSAutoNCatPtsTxt.Text);
			int nPSEpts_min = nCATpts - 1, nPSEpts_max = nCATpts;
			double scale_init = Convert.ToDouble(WCSScaleInit.Text) / 3600 * Math.PI / 180;
			double scale_lb = Convert.ToDouble(WCSScaleInitLB.Text) / 3600 * Math.PI / 180;
			double scale_ub = Convert.ToDouble(WCSScaleInitUB.Text) / 3600 * Math.PI / 180;
			double rotat_init = Convert.ToDouble(WCSRotationInit.Text) * Math.PI / 180;
			double rotat_lb = Convert.ToDouble(WCSRotationInitLB.Text) * Math.PI / 180;
			double rotat_ub = Convert.ToDouble(WCSRotationInitUB.Text) * Math.PI / 180;
			double vertextol = Convert.ToDouble(WCSAutoVertexToleranceTxt.Text) * Math.PI / 180;
			bool do_parallel = !WCSAutoDisplayChck.Checked;
			string catfilename = (string)WCSAutoCatalogueTxt.Tag;
			string catCVAL1 = WCSAutoCatalogueCVAL1.Text;
			string catCVAL2 = WCSAutoCatalogueCVAL2.Text;
			string catExtension = WCSAutoCatalogueExtensionTxt.Text;
			string catMag = WCSAutoCatalogueMag.Text;
			int stopNpts = Convert.ToInt32(WCSAutoStopNMatchesText.Text);
			int stopPercpts = Convert.ToInt32(WCSAutoStopPercMatchesText.Text);

			//get catalogue RA, Dec, and mag's, and sort by mags
			if (!File.Exists(catfilename))
			{
				MessageBox.Show("Cannot find catalogue file:\r\r" + catfilename + "\r\rDoes not exist.", "Error...");
				return;
			}

			JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(catfilename, catExtension);
			double[] ra = bt.GetTTYPEEntry(catCVAL1);
			double[] dec = bt.GetTTYPEEntry(catCVAL2);
			double[] mag = bt.GetTTYPEEntry(catMag);

			//need to check mag for NaN's and re-form ra dec mag
			int catcnt = 0;
			for (int i = 0; i < ra.Length; i++)
			{
				if (Double.IsNaN(mag[i]))
					continue;

				ra[catcnt] = ra[i];
				dec[catcnt] = dec[i];
				mag[catcnt] = mag[i];
				catcnt++;
			}
			Array.Resize(ref ra, catcnt);
			Array.Resize(ref dec, catcnt);
			Array.Resize(ref mag, catcnt);

			//sort the catalogue list by magnitude
			double[] keysref = new double[mag.Length];
			Array.Copy(mag, keysref, mag.Length);
			Array.Sort(mag, ra);
			Array.Copy(keysref, mag, mag.Length);
			Array.Sort(mag, dec);

			//get the brightest few catlaogue points
			JPMath.PointD[] CATpts = new JPMath.PointD[nCATpts];
			double crval1 = 0, crval2 = 0;
			for (int i = 0; i < CATpts.Length; i++)
			{
				CATpts[i] = new JPMath.PointD(ra[i], dec[i], mag[i]);
				crval1 += CATpts[i].X;
				crval2 += CATpts[i].Y;
			}
			crval1 /= (double)CATpts.Length;//the reference value can be the mean
			crval2 /= (double)CATpts.Length;//the reference value can be the mean

			//convert the catalogue points to intermediate points
			JPMath.PointD[] CATpts_intrmdt = new JPMath.PointD[nCATpts];
			double a0 = crval1 * Math.PI / 180, d0 = crval2 * Math.PI / 180;
			for (int i = 0; i < CATpts_intrmdt.Length; i++)
			{
				double a = CATpts[i].X * Math.PI / 180;//radians
				double d = CATpts[i].Y * Math.PI / 180;//radians

				//for tangent plane Gnomic
				double xint = Math.Cos(d) * Math.Sin(a - a0) / (Math.Cos(d0) * Math.Cos(d) * Math.Cos(a - a0) + Math.Sin(d0) * Math.Sin(d));
				double yint = (Math.Cos(d0) * Math.Sin(d) - Math.Cos(d) * Math.Sin(d0) * Math.Cos(a - a0)) / (Math.Sin(d0) * Math.Sin(d) + Math.Cos(d0) * Math.Cos(d) * Math.Cos(a - a0));

				CATpts_intrmdt[i] = new JPMath.PointD(xint, yint, CATpts[i].Value);
			}

			//make intermediate coordinate triangles
			int nCATtriangles = CATpts_intrmdt.Length * (CATpts_intrmdt.Length - 1) * (CATpts_intrmdt.Length - 2) / 6;
			JPMath.Triangle[] CATtriangles_intrmdt = new JPMath.Triangle[nCATtriangles];
			int c = 0;
			for (int i = 0; i < CATpts_intrmdt.Length - 2; i++)
				for (int j = i + 1; j < CATpts_intrmdt.Length - 1; j++)
					for (int k = j + 1; k < CATpts_intrmdt.Length; k++)
					{
						CATtriangles_intrmdt[c] = new JPMath.Triangle(CATpts_intrmdt[i], CATpts_intrmdt[j], CATpts_intrmdt[k]);
						c++;
					}

			//get PSE image sources
			ShowPSEChck.Checked = true;
			ShowPSEChck.Enabled = true;
			PSES = new PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
			PSESINDEX = 0;
			PSESRECTS = new Rectangle[1][];
			double immax = IMAGESET[FILELISTINDEX].Max;//assume bg subtracted
			double pixthresh = immax / 32;
			double div = 2;
			double amp = pixthresh;
			int PSEiters = 0;
			int maxPSEiters = 15;
			double pix_sat = (double)PSESaturationUpD.Value;
			while (PSES[PSESINDEX].N_Sources < nPSEpts_min || PSES[PSESINDEX].N_Sources > nPSEpts_max)
			{
				PSEiters++;
				if (PSEiters > maxPSEiters)
					break;

				if (PSES[PSESINDEX].N_SaturatedSources >= nPSEpts_max || PSES[PSESINDEX].N_Sources >= nPSEpts_max)
					break;

				PSES[PSESINDEX].Extract_Sources(IMAGESET[FILELISTINDEX].Image, pix_sat, pixthresh, Double.MaxValue, 0, Double.MaxValue, false, (int)PSEKernelRadUpD.Value, (int)PSESeparationUpD.Value, PSEAutoBackgroundChck.Checked, "", ROI_REGION, false);
				MAKEPSERECTS();
				ImageWindow.Refresh();
				SubImageWindow.Refresh();

				if (PSES[PSESINDEX].N_Sources < nPSEpts_min)
					pixthresh -= amp / div;
				if (PSES[PSESINDEX].N_Sources > nPSEpts_max)
					pixthresh += amp / div;
				div *= 2;
			}
			if (PSES[PSESINDEX].N_Sources > nPSEpts_max)
			{
				PSES[PSESINDEX].ClipToNBrightest(nPSEpts_max);
				MAKEPSERECTS();
				ImageWindow.Refresh();
				SubImageWindow.Refresh();
			}

			//turn the PSE results into points
			JPMath.PointD[] PSEpts = new JPMath.PointD[PSES[PSESINDEX].N_Sources];
			double crpix1_init = 0, crpix2_init = 0, crpix1_lb = Double.MaxValue, crpix1_ub = Double.MinValue, crpix2_lb = Double.MaxValue, crpix2_ub = Double.MinValue;
			for (int i = 0; i < PSEpts.Length; i++)
			{
				PSEpts[i] = new JPMath.PointD(IMAGESET[FILELISTINDEX].Width - 1 - PSES[PSESINDEX].Centroids_X[i], IMAGESET[FILELISTINDEX].Height - 1 - PSES[PSESINDEX].Centroids_Y[i], PSES[PSESINDEX].Centroids_Volume[i]);
				crpix1_init += PSEpts[i].X;
				crpix2_init += PSEpts[i].Y;
				if (crpix1_ub < PSEpts[i].X)
					crpix1_ub = PSEpts[i].X;
				if (crpix1_lb > PSEpts[i].X)
					crpix1_lb = PSEpts[i].X;
				if (crpix2_ub < PSEpts[i].Y)
					crpix2_ub = PSEpts[i].Y;
				if (crpix2_lb > PSEpts[i].Y)
					crpix2_lb = PSEpts[i].Y;
			}
			crpix1_init /= (double)PSEpts.Length;//the reference value initial guesses can be the means
			crpix2_init /= (double)PSEpts.Length;

			//make PSE triangles
			int nPSEtriangles = PSEpts.Length * (PSEpts.Length - 1) * (PSEpts.Length - 2) / 6;
			JPMath.Triangle[] PSEtriangles = new JPMath.Triangle[nPSEtriangles];
			c = 0;
			for (int i = 0; i < PSEpts.Length - 2; i++)
				for (int j = i + 1; j < PSEpts.Length - 1; j++)
					for (int k = j + 1; k < PSEpts.Length; k++)
					{
						PSEtriangles[c] = new JPMath.Triangle(PSEpts[i], PSEpts[j], PSEpts[k]);

						if (!do_parallel)
						{
							if (WCSAUTOCANCEL)
								break;
							POLYPOINTS = new Point[3];
							POLYPOINTS[0] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - PSEtriangles[c].GetVertex(0).X - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - PSEtriangles[c].GetVertex(0).Y - 0.5) * ysc));
							POLYPOINTS[1] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - PSEtriangles[c].GetVertex(1).X - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - PSEtriangles[c].GetVertex(1).Y - 0.5) * ysc));
							POLYPOINTS[2] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - PSEtriangles[c].GetVertex(2).X - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - PSEtriangles[c].GetVertex(2).Y - 0.5) * ysc));
							ImageWindow.Refresh();
						}
						c++;
					}

			POLYPOINTS = null;
			if (!do_parallel)
				ImageWindow.Refresh();

			if (WCSAUTOCANCEL)
				return;

			if (do_parallel)
				if (WCSAutoConditionArraysChck.Checked)
				{
					PSEtriangles = JPFITS.WCSAutoSolver.ConditionTriangleArrayBrightnessThreads(PSEtriangles, Environment.ProcessorCount, false);
					CATtriangles_intrmdt = JPFITS.WCSAutoSolver.ConditionTriangleArrayBrightnessThreads(CATtriangles_intrmdt, 1, true);
				}

			//for each PSE triangle, fit it to a CAT intermediate triangle, and then check if this fit satisfies the other CAT points to the PSE points
			//rotation transformation p[0] = scale; p[1] = phi (radians); p[2] = x-axis coordinate reference; p[3] = y-axis coordinate reference;
			double[] plb = new double[4] { scale_lb, rotat_lb, crpix1_lb, crpix2_lb };
			double[] pub = new double[4] { scale_ub, rotat_ub, crpix1_ub, crpix2_ub };
			double[] psc = new double[4] { scale_init, 1, Math.Abs(crpix1_init), Math.Abs(crpix2_init) };
			POLYPOINTS = new System.Drawing.Point[3];
			POLYPOINTS2 = new System.Drawing.Point[3];

			double kern_diam = (double)(2 * PSEKernelRadUpD.Value) + 1;
			double p00 = 0, p01 = 0, p02 = 0, p03 = 0;
			int total_pt_matches = 0;
			DATE = DateTime.Now;
			TimeSpan ts = new TimeSpan();
			bool solution = false;
			int prog = 0, threadnum = 0;
			ulong ncompares = 0, nfalse_sols = 0;
			bool compare_fieldvectors = rotat_lb != -Math.PI && rotat_ub != Math.PI;			

			ParallelOptions opts = new ParallelOptions();
			if (do_parallel)
				opts.MaxDegreeOfParallelism = Environment.ProcessorCount;
			else
				opts.MaxDegreeOfParallelism = 1;
			var rangePartitioner = Partitioner.Create(0, PSEtriangles.Length);
			object locker = new object();
			int thrgrpsz = PSEtriangles.Length / opts.MaxDegreeOfParallelism;
			double mdpT100ovrlen = (double)(opts.MaxDegreeOfParallelism * 100) / (double)PSEtriangles.Length;

			Parallel.ForEach(rangePartitioner, opts, (range, loopState) =>
			{
				if (solution || WCSAUTOCANCEL)
					loopState.Stop();

				ulong ncompareslocal = 0;
				ulong nfalse_solslocal = 0;
				//create these here so that each thread when parallel has own copy
				double[] xpix_triplet = new double[3];
				double[] ypix_triplet = new double[3];
				double[] Xintrmdt_triplet = new double[3];
				double[] Yintrmdt_triplet = new double[3];
				double[] P0 = new double[4];
				double[] PLB = plb;
				double[] PUB = pub;
				double minlength2, maxlength2;

				for (int i = range.Item1; i < range.Item2; i++)
				{
					if (solution)
						break;
					if (WCSAUTOCANCEL)
						break;

					if (i < thrgrpsz)
						if ((double)i * mdpT100ovrlen > prog)
							WCSAutoBGWrkr.ReportProgress(1);

					xpix_triplet[0] = PSEtriangles[i].GetVertex(0).X;
					ypix_triplet[0] = PSEtriangles[i].GetVertex(0).Y;
					xpix_triplet[1] = PSEtriangles[i].GetVertex(1).X;
					ypix_triplet[1] = PSEtriangles[i].GetVertex(1).Y;
					xpix_triplet[2] = PSEtriangles[i].GetVertex(2).X;
					ypix_triplet[2] = PSEtriangles[i].GetVertex(2).Y;
					minlength2 = scale_lb * (PSEtriangles[i].GetSideLength(2) - kern_diam);
					maxlength2 = scale_ub * (PSEtriangles[i].GetSideLength(2) + kern_diam);

					if (!do_parallel)
					{
						POLYPOINTS[0] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - xpix_triplet[0] - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - ypix_triplet[0] - 0.5) * ysc));
						POLYPOINTS[1] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - xpix_triplet[1] - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - ypix_triplet[1] - 0.5) * ysc));
						POLYPOINTS[2] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - xpix_triplet[2] - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - ypix_triplet[2] - 0.5) * ysc));
						ImageWindow.Refresh();
					}

					for (int j = 0; j < CATtriangles_intrmdt.Length; j++)
					{
						if (solution)
							break;
						if (WCSAUTOCANCEL)
							break;

						ncompareslocal++;

						//compare AAS (vertex0, vertex1, longest side)
						if (Math.Abs(PSEtriangles[i].GetVertexAngle(0) - CATtriangles_intrmdt[j].GetVertexAngle(0)) > vertextol)
							continue;
						if (Math.Abs(PSEtriangles[i].GetVertexAngle(1) - CATtriangles_intrmdt[j].GetVertexAngle(1)) > vertextol)
							continue;
						if (CATtriangles_intrmdt[j].GetSideLength(2) < minlength2 || CATtriangles_intrmdt[j].GetSideLength(2) > maxlength2)
							continue;

						if (compare_fieldvectors)
						{
							double theta = Math.Atan2(PSEtriangles[i].FieldVector.X * CATtriangles_intrmdt[j].FieldVector.Y - PSEtriangles[i].FieldVector.Y * CATtriangles_intrmdt[j].FieldVector.X, PSEtriangles[i].FieldVector.X * CATtriangles_intrmdt[j].FieldVector.X + PSEtriangles[i].FieldVector.Y * CATtriangles_intrmdt[j].FieldVector.Y);

							if (theta > rotat_ub || theta < rotat_lb)
								continue;
						}
						else
						{
							double theta = Math.Atan2(PSEtriangles[i].FieldVector.X * CATtriangles_intrmdt[j].FieldVector.Y - PSEtriangles[i].FieldVector.Y * CATtriangles_intrmdt[j].FieldVector.X, PSEtriangles[i].FieldVector.X * CATtriangles_intrmdt[j].FieldVector.X + PSEtriangles[i].FieldVector.Y * CATtriangles_intrmdt[j].FieldVector.Y);

							PLB[1] = theta - 2;
							PUB[1] = theta + 2;
						}

						Xintrmdt_triplet[0] = CATtriangles_intrmdt[j].GetVertex(0).X;
						Yintrmdt_triplet[0] = CATtriangles_intrmdt[j].GetVertex(0).Y;
						Xintrmdt_triplet[1] = CATtriangles_intrmdt[j].GetVertex(1).X;
						Yintrmdt_triplet[1] = CATtriangles_intrmdt[j].GetVertex(1).Y;
						Xintrmdt_triplet[2] = CATtriangles_intrmdt[j].GetVertex(2).X;
						Yintrmdt_triplet[2] = CATtriangles_intrmdt[j].GetVertex(2).Y;

						//made it here, now do a fit
						//reset P0 for j'th iteration
						P0[0] = scale_init;
						P0[1] = rotat_init;
						P0[2] = crpix1_init;
						P0[3] = crpix2_init;
						JPMath.Fit_WCSTransform2d(Xintrmdt_triplet, Yintrmdt_triplet, xpix_triplet, ypix_triplet, ref P0, PLB, PUB, psc);

						int N_pt_matches = 0;
						for (int k = 0; k < 3; k++)
						{
							int x = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / P0[0] * (Math.Cos(-P0[1]) * Xintrmdt_triplet[k] - Math.Sin(-P0[1]) * Yintrmdt_triplet[k]) + P0[2]));
							int y = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / P0[0] * (Math.Sin(-P0[1]) * Xintrmdt_triplet[k] + Math.Cos(-P0[1]) * Yintrmdt_triplet[k]) + P0[3]));
							if (!do_parallel)
								POLYPOINTS2[k] = new System.Drawing.Point((int)((x + 0.5) * xsc), (int)((y + 0.5) * ysc));

							if (x > 0 && y > 0 && x < IMAGESET[FILELISTINDEX].Width && y < IMAGESET[FILELISTINDEX].Height && PSES[PSESINDEX].SourceIndexMap[x, y] == PSES[PSESINDEX].SourceIndexMap[IMAGESET[FILELISTINDEX].Width - 1 - (int)Math.Round(xpix_triplet[k]), IMAGESET[FILELISTINDEX].Height - 1 - (int)Math.Round(ypix_triplet[k])])
								N_pt_matches++;
						}
						if (!do_parallel)
							ImageWindow.Refresh();

						if (N_pt_matches != 3)//not a possible solution
							continue;

						if (do_parallel)
						{
							for (int k = 0; k < 3; k++)
							{
								double x = (double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / P0[0] * (Math.Cos(-P0[1]) * Xintrmdt_triplet[k] - Math.Sin(-P0[1]) * Yintrmdt_triplet[k]) + P0[2]);
								double y = (double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / P0[0] * (Math.Sin(-P0[1]) * Xintrmdt_triplet[k] + Math.Cos(-P0[1]) * Yintrmdt_triplet[k]) + P0[3]);
								POLYPOINTS2[k] = new System.Drawing.Point((int)((x + 0.5) * xsc), (int)((y + 0.5) * ysc));
								POLYPOINTS[k] = new System.Drawing.Point((int)((IMAGESET[FILELISTINDEX].Width - 1 - xpix_triplet[k] - 0.5) * xsc), (int)((IMAGESET[FILELISTINDEX].Height - 1 - ypix_triplet[k] - 0.5) * ysc));
							}
							ImageWindow.Refresh();
						}
						else
						{
							POLYPOINTSb = new Point[POLYPOINTS.Length];
							POLYPOINTS2b = new Point[POLYPOINTS2.Length];
							Array.Copy(POLYPOINTS, POLYPOINTSb, POLYPOINTS.Length);
							Array.Copy(POLYPOINTS2, POLYPOINTS2b, POLYPOINTS2.Length);
						}

						//need to check if the other CAT points match the PSE pts
						N_pt_matches = 0;
						for (int k = 0; k < CATpts_intrmdt.Length; k++)
						{
							double x_int = CATpts_intrmdt[k].X;
							double y_int = CATpts_intrmdt[k].Y;

							int x_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / P0[0] * (Math.Cos(-P0[1]) * x_int - Math.Sin(-P0[1]) * y_int) + P0[2]));
							int y_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / P0[0] * (Math.Sin(-P0[1]) * x_int + Math.Cos(-P0[1]) * y_int) + P0[3]));

							if (x_pix > 0 && y_pix > 0 && x_pix < IMAGESET[FILELISTINDEX].Width && y_pix < IMAGESET[FILELISTINDEX].Height && PSES[PSESINDEX].SourceBooleanMap[x_pix, y_pix] /* && PSES[PSESINDEX].SourceIndexMap[x_pix, y_pix] < PSES[PSESINDEX].N_Sources*/)
								N_pt_matches++;
						}

						if (N_pt_matches >= stopNpts || N_pt_matches * 100 / CATpts_intrmdt.Length >= stopPercpts)
						{
							solution = true;
							ts = DateTime.Now - DATE;
							total_pt_matches = N_pt_matches;
							p00 = P0[0];
							p01 = P0[1];
							p02 = P0[2];
							p03 = P0[3];
							threadnum = Thread.CurrentThread.ManagedThreadId;
						}
						else
							nfalse_solslocal++;
					}
				}
				lock (locker)
				{
					ncompares += ncompareslocal;
					nfalse_sols += nfalse_solslocal;
				}
			});

			if (!do_parallel)
			{
				POLYPOINTS = POLYPOINTSb;
				POLYPOINTS2 = POLYPOINTS2b;
			}

			if (!solution || WCSAUTOCANCEL)
			{
				POLYPOINTS = null;
				POLYPOINTS2 = null;
				PSESRECTS = null;
				MARKCOORDRECTS = null;
				ImageWindow.Refresh();
				if (WCSAUTOCANCEL)
					MessageBox.Show("Cancelled...");
				else if (!solution)
					MessageBox.Show("No solution...");
				return;
			}

			MARKCOORDS = new double[2, total_pt_matches];
			WCS_RA = new double[total_pt_matches];
			WCS_DEC = new double[total_pt_matches];
			double[] xpix_matches = new double[total_pt_matches];
			double[] ypix_matches = new double[total_pt_matches];
			c = 0;

			for (int k = 0; k < CATpts_intrmdt.Length; k++)
			{
				double x_intrmdt = CATpts_intrmdt[k].X;
				double y_intrmdt = CATpts_intrmdt[k].Y;

				int x_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / p00 * (Math.Cos(-p01) * x_intrmdt - Math.Sin(-p01) * y_intrmdt) + p02));
				int y_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / p00 * (Math.Sin(-p01) * x_intrmdt + Math.Cos(-p01) * y_intrmdt) + p03));

				if (x_pix > 0 && y_pix > 0 && x_pix < IMAGESET[FILELISTINDEX].Width && y_pix < IMAGESET[FILELISTINDEX].Height && PSES[PSESINDEX].SourceBooleanMap[x_pix, y_pix]/* && PSES[PSESINDEX].SourceIndexMap[x_pix, y_pix] < PSES[PSESINDEX].N_Sources*/)
				{
					int index = PSES[PSESINDEX].SourceIndexMap[x_pix, y_pix];
					xpix_matches[c] = PSES[PSESINDEX].Centroids_X[index];
					ypix_matches[c] = PSES[PSESINDEX].Centroids_Y[index];
					WCS_RA[c] = CATpts[k].X;
					WCS_DEC[c] = CATpts[k].Y;
					MARKCOORDS[0, c] = x_pix;
					MARKCOORDS[1, c] = y_pix;
					c++;
				}
			}

			MAKEMARKCOORDRECTS();
			PSES[PSESINDEX] = new JPFITS.PointSourceExtractor(xpix_matches, ypix_matches);
			MAKEPSERECTS();
			WCSSolveList.PerformClick();

			DialogResult res = MessageBox.Show("Scale: " + Math.Round(p00 * 180 / Math.PI * 3600, 4) + ";\rRotation: " + Math.Round(p01 * 180 / Math.PI, 3) + ";\rN Pt. Matches: " + total_pt_matches + " (" + (total_pt_matches * 100 / CATpts_intrmdt.Length).ToString("00.0") + "%)" + ";\rN_Comparisons: " + ncompares.ToString("0.00e00") + " (" + Math.Round((double)(ncompares * 100) / (double)(PSEtriangles.Length) / (double)(CATtriangles_intrmdt.Length), 1) + "%)" + ";\rN_False: " + nfalse_sols + ";\rThread: " + threadnum + ";\rCompleted in: " + ts.Minutes.ToString() + "m" + ((double)(ts.Seconds) + (double)ts.Milliseconds / 1000).ToString() + "s" + ";\rComparison per Second: " + (ncompares / ts.TotalSeconds).ToString("0.00e00") + ";\r\rClear Solution Points?", "Finished...", MessageBoxButtons.YesNo);
			if (res == DialogResult.Yes)
			{
				POLYPOINTS = null;
				POLYPOINTS2 = null;
				PSESRECTS = null;
				MARKCOORDRECTS = null;
				ImageWindow.Refresh();
			}

			POLYPOINTS = null;
			POLYPOINTS2 = null;
			ImageWindow.Refresh();

			if (WCSAutoRefineChck.Checked)
			{
				PSES = new PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
				PSESINDEX = 0;
				immax = IMAGESET[FILELISTINDEX].Max;//assume bg subtracted
				pixthresh = immax / 32;
				div = 2;
				amp = pixthresh;
				nPSEpts_min = Convert.ToInt32(WCSAutoRefineNPtsTxt.Text) - 1;
				nPSEpts_max = Convert.ToInt32(WCSAutoRefineNPtsTxt.Text);
				WCSLoadListNPtsTxt.Text = (nPSEpts_max * 2).ToString();
				PSEiters = 0;

				while (PSES[PSESINDEX].N_Sources < nPSEpts_min || PSES[PSESINDEX].N_Sources > nPSEpts_max)
				{
					PSEiters++;
					if (PSEiters > maxPSEiters)
						break;

					if (PSES[PSESINDEX].N_SaturatedSources >= nPSEpts_max || PSES[PSESINDEX].N_Sources >= nPSEpts_max)
						break;

					PSES = new PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
					PSES[PSESINDEX].Extract_Sources(IMAGESET[FILELISTINDEX].Image, pix_sat, pixthresh, Double.MaxValue, 0, Double.MaxValue, false, (int)PSEKernelRadUpD.Value, (int)PSESeparationUpD.Value, PSEAutoBackgroundChck.Checked, "", ROI_REGION, false);
					PSESRECTS = new Rectangle[1][];
					MAKEPSERECTS();
					ImageWindow.Refresh();
					SubImageWindow.Refresh();

					if (PSES[PSESINDEX].N_Sources < nPSEpts_min)
						pixthresh -= amp / div;
					if (PSES[PSESINDEX].N_Sources > nPSEpts_max)
						pixthresh += amp / div;
					div *= 2;
				}
				if (PSES[PSESINDEX].N_Sources > nPSEpts_max)
				{
					PSES[PSESINDEX].ClipToNBrightest(nPSEpts_max);
					PSESRECTS = new Rectangle[1][];
					MAKEPSERECTS();
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
				}
				WCSLoadSimbadAscii_Click(sender, e);
				WCSClarifyListSources.PerformClick();
				IMAGESET[FILELISTINDEX].WCS.Grid_Invalidate();
				WCSSolveList.PerformClick();
				if (MessageBox.Show(PSES[PSESINDEX].N_Sources + " sources of " + WCSAutoRefineNPtsTxt.Text + " were able to be used for WCS refinement. \r\n\r\nClear Solution points?", "Finished...", MessageBoxButtons.YesNo) == DialogResult.Yes)
				{
					POLYPOINTS = null;
					POLYPOINTS2 = null;
					PSESRECTS = null;
					MARKCOORDRECTS = null;
					ImageWindow.Refresh();
				}
			}
		}

		private void WCSAutoBGWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			ProgressBar.PerformStep();
		}

		private void WCSAutoBGWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WCSAutoSolveBtn.Text = "Solve";
			ProgressBar.Value = 0;
		}

		private void toolStripMenuItem15_CheckedChanged(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoDisplayChck", WCSAutoDisplayChck.Checked);
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void WCSAutoRefineChck_CheckedChanged(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoRefineChck", WCSAutoRefineChck.Checked);
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void WCSScaleInit_Enter(object sender, System.EventArgs e)
		{
			TEXTBOXENTER((ToolStripTextBox)sender);
		}

		private void WCSScaleInit_TextChanged(object sender, System.EventArgs e)
		{
			CHECKTEXTBOXTONUM((ToolStripTextBox)sender);
		}

		private void AutoWCSMenuItem_DropDownOpening(object sender, System.EventArgs e)
		{
			string chckstt = (string)JPFITS.REG.GetReg("CCDLAB", "WCSXParity");
			if (chckstt == "Unchecked")
				WCSAutoXAxisParityChck.CheckState = CheckState.Unchecked;
			if (chckstt == "Checked")
				WCSAutoXAxisParityChck.CheckState = CheckState.Checked;
			if (chckstt == "Indeterminate")
				WCSAutoXAxisParityChck.CheckState = CheckState.Indeterminate;
			chckstt = (string)JPFITS.REG.GetReg("CCDLAB", "WCSYParity");
			if (chckstt == "Unchecked")
				WCSAutoYAxisParityChck.CheckState = CheckState.Unchecked;
			if (chckstt == "Checked")
				WCSAutoYAxisParityChck.CheckState = CheckState.Checked;
			if (chckstt == "Indeterminate")
				WCSAutoYAxisParityChck.CheckState = CheckState.Indeterminate;
		}

		private void AutoWCSMenuItem_DropDownOpened(object sender, System.EventArgs e)
		{
			WCSScaleInit.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSScaleInit");
			WCSScaleInitLB.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSScaleInitLB");
			WCSScaleInitUB.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSScaleInitUB");
			WCSRotationInit.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSRotationInit");
			WCSRotationInitLB.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSRotationInitLB");
			WCSRotationInitUB.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSRotationInitUB");
			WCSAutoVertexToleranceTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoVertexToleranceTxt");
			WCSAutoNCatPtsTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoNCatPtsTxt");
			WCSAutoDisplayChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSAutoDisplayChck"));
			WCSAutoCatalogueTxt.Tag = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueTxt");
			WCSAutoCatalogueTxt.Text = ((string)WCSAutoCatalogueTxt.Tag).Substring(((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.ToolTipText = ((string)WCSAutoCatalogueTxt.Tag).Substring(0, ((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.BackColor = Color.Gainsboro;
			WCSAutoCatalogueCVAL1.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueCVAL1");
			WCSAutoCatalogueCVAL2.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueCVAL2");
			WCSAutoQueryCVAL1.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoQueryCVAL1");
			WCSAutoQueryCVAL2.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoQueryCVAL2");
			WCSAutoResolveRadiusTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoResolveRadiusTxt");
			WCSAutoCatalogueExtensionTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt");
			WCSAutoCatalogueMag.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueMag");
			WCSAutoRefineChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSAutoRefineChck"));
			WCSAutoRefineNPtsTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoRefineNPtsTxt");
			WCSAutoStopNMatchesText.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoStopNMatchesText");
			WCSAutoStopPercMatchesText.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoStopPercMatchesText");
			WCSLoadListNPtsTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSLoadListNPtsTxt");
			WCSQuerySaveFileChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySaveFileChck"));
			WCSAutoConditionArraysChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSAutoConditionArrays"));
			WCSQuerySquareRegionChck.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSQuerySquareRegion");
			WCSQuerySolveAfter.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySolveAfter"));
			WCSQuerySaveFileChooseDirBtn.Enabled = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtn"));
			WCSQuerySaveFileChooseDirBtn.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtnChck"));
			WCSAstroQueryLimitLLengthDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "WCSAstroQueryLimitLLength"));
		}

		private void WCSAutoQueryBtn_DropDownOpening(object sender, System.EventArgs e)
		{
			AstroQueryCatalogueNameDrop.SelectedIndex = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "AstroQueryCatalogueNameDrop"));
		}

		private void WCSAutoExternalDLLChck_Click(object sender, System.EventArgs e)
		{
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoSolveBtn.ShowDropDown();
		}

		private void WCSAutoConditionArraysChck_Click(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoConditionArrays", WCSAutoConditionArraysChck.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void WCSAutoCatalogueTxt_Click(object sender, System.EventArgs e)
		{
			//get the catalogue list and triangles of the brightest few sources
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "FITS|*.fits;*.fit;*.fts";
			ofd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			WCSAutoCatalogueTxt.Text = ofd.FileName.Substring(ofd.FileName.LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.Tag = ofd.FileName;

			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCATDir", ofd.FileName.Substring(0, ofd.FileName.LastIndexOf("\\")));
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueTxt", ofd.FileName);




			/*WCSAutoCatalogueExtensionTxt.Text = "";
			WCSAutoCatalogueCVAL1.Text = "ra";
			WCSAutoCatalogueCVAL2.Text = "dec";
			WCSAutoCatalogueMag.Text = "phot_bp_mean_mag";
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL1", WCSAutoCatalogueCVAL1.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL2", WCSAutoCatalogueCVAL2.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueMag", WCSAutoCatalogueMag.Text);*/




			WCSAutoCatalogueMenuBtn.ShowDropDown();
		}

		private void WCSAutoCatalogueTxt_MouseHover(object sender, System.EventArgs e)
		{
			WCSAutoCatalogueTxt.ToolTipText = ((string)WCSAutoCatalogueTxt.Tag).Substring(0, ((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
		}

		private void WCSAutoCatalogueExtensionTxt_Click(object sender, System.EventArgs e)
		{
			string[] exts = JPFITS.FITSBinTable.GetAllExtensionNames((string)WCSAutoCatalogueTxt.Tag);

			if (exts.Length == 1)
			{
				MessageBox.Show("Only one extension to choose from: '" + exts[0] + "'");
				WCSAutoCatalogueExtensionTxt.Text = exts[0].Trim();
				JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt.Text);
			}
			else
			{
				WCSAutoCVALList list = new WCSAutoCVALList((string)WCSAutoCatalogueTxt.Tag);
				list.Text = "Select Extension";
				list.ShowDialog();

				WCSMenu.ShowDropDown();
				AutoWCSMenuItem.ShowDropDown();
				WCSAutoCatalogueMenuBtn.ShowDropDown();

				if (list.DialogResult == DialogResult.Cancel)
					return;

				WCSAutoCatalogueExtensionTxt.Text = ((string)list.WCDrop.SelectedItem).Trim();
				JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt.Text);
			}
		}

		private void WCSAutoCatalogueCVAL1_Click(object sender, System.EventArgs e)
		{
			WCSMenu.DropDown.AutoClose = false;
			AutoWCSMenuItem.DropDown.AutoClose = false;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = false;

			WCSAutoCVALList list = new WCSAutoCVALList((string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text);
			list.Text = "Select CVAL1";
			list.TopMost = true;
			list.ShowDialog();

			if (list.DialogResult == DialogResult.Cancel)
			{
				WCSMenu.DropDown.AutoClose = true;
				AutoWCSMenuItem.DropDown.AutoClose = true;
				WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
				return;
			}

			WCSAutoCatalogueCVAL1.Text = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL1", WCSAutoCatalogueCVAL1.Text);

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
		}

		private void WCSAutoCatalogueCVAL2_Click(object sender, System.EventArgs e)
		{
			WCSMenu.DropDown.AutoClose = false;
			AutoWCSMenuItem.DropDown.AutoClose = false;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = false;

			WCSAutoCVALList list = new WCSAutoCVALList((string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text);
			list.Text = "Select CVAL2";
			list.TopMost = true;
			list.ShowDialog();

			if (list.DialogResult == DialogResult.Cancel)
			{
				WCSMenu.DropDown.AutoClose = true;
				AutoWCSMenuItem.DropDown.AutoClose = true;
				WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
				return;
			}

			WCSAutoCatalogueCVAL2.Text = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL2", WCSAutoCatalogueCVAL2.Text);

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
		}

		private void WCSAutoCatalogueMag_Click(object sender, System.EventArgs e)
		{
			WCSMenu.DropDown.AutoClose = false;
			AutoWCSMenuItem.DropDown.AutoClose = false;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = false;

			WCSAutoCVALList list = new WCSAutoCVALList((string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text);
			list.Text = "Select Magnitude";
			list.TopMost = true;
			list.ShowDialog();

			if (list.DialogResult == DialogResult.Cancel)
			{
				WCSMenu.DropDown.AutoClose = true;
				AutoWCSMenuItem.DropDown.AutoClose = true;
				WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
				return;
			}

			WCSAutoCatalogueMag.Text = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueMag", WCSAutoCatalogueMag.Text);

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
		}

		private void WCSAutoQueryCVAL1_Click(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.DropDown.AutoClose = false;
			AutoWCSMenuItem.DropDown.AutoClose = false;
			WCSAutoQueryBtn.DropDown.AutoClose = false;

			WCSAutoCVALList list = new WCSAutoCVALList(IMAGESET[FILELISTINDEX].Header.GetAllKeyNames());
			list.Text = "Select the CVALn";
			list.TopMost = true;
			list.ShowDialog();

			if (list.DialogResult == DialogResult.Cancel)
			{
				WCSMenu.DropDown.AutoClose = true;
				AutoWCSMenuItem.DropDown.AutoClose = true;
				WCSAutoQueryBtn.DropDown.AutoClose = true;
				return;
			}

			string hkey = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", ((ToolStripTextBox)sender).Name, hkey);
			((ToolStripTextBox)sender).Text = hkey;

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoQueryBtn.DropDown.AutoClose = true;
		}

		private void WCSAutoQueryBtn_DoubleClick(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			string catalogue = (string)AstroQueryCatalogueNameDrop.SelectedItem;
			catalogue = catalogue.Substring(0, catalogue.IndexOf("(") - 1);

			string cval1 = IMAGESET[FILELISTINDEX].Header.GetKeyValue(WCSAutoQueryCVAL1.Text);
			string cval2 = IMAGESET[FILELISTINDEX].Header.GetKeyValue(WCSAutoQueryCVAL2.Text);
			try
			{
				Convert.ToDouble(cval1);
			}
			catch
			{
				double ra, dec;
				JPFITS.WorldCoordinateSolution.SexagesimalElementsToDegreeElements(cval1, cval2, "", out ra, out dec);
				cval1 = ra.ToString();
				cval2 = dec.ToString();
			}

			string filename = "";
			if (WCSQuerySaveFileChck.Checked)
				if (!WCSQuerySaveFileChooseDirBtn.Checked)
					filename = IMAGESET[FILELISTINDEX].FullFileName.Substring(0, IMAGESET[FILELISTINDEX].FullFileName.LastIndexOf(".")) + "_queryCatalog.fit";
				else
				{
					FolderBrowserDialog fbd = new FolderBrowserDialog();
					fbd.SelectedPath = IMAGESET[FILELISTINDEX].FilePath;
					fbd.Description = "Select directpry to save catalogue";
					if (fbd.ShowDialog() == DialogResult.Cancel)
						return;
					filename = fbd.SelectedPath + "\\" + new DirectoryInfo(fbd.SelectedPath).Name + "_queryCatalog.fit";
				}

			string radius = WCSAutoResolveRadiusTxt.Text;

			string square = "0";
			if (WCSQuerySquareRegionChck.Text.Contains("Square"))
				square = "1";

			string Nlimit = "0";
			if (WCSAstroQueryLimitLLengthDrop.SelectedIndex > 0)
				Nlimit = WCSAstroQueryLimitLLengthDrop.SelectedItem.ToString();

			WCSMenu.HideDropDown();
			AutoWCSMenuItem.HideDropDown();
			WCSAutoQueryBtn.HideDropDown();

			int res = JPFITS.WCSAutoSolver.AstroQuery(catalogue, cval1, cval2, ref filename, radius, square/*, Nlimit*/);
			if (res != 0)
			{
				MessageBox.Show("Query failed with exit code: " + res);
				return;
			}

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoQueryBtn.ShowDropDown();

			WCSAutoCatalogueTxt.Tag = filename;
			WCSAutoCatalogueTxt.Text = ((string)WCSAutoCatalogueTxt.Tag).Substring(((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.ToolTipText = ((string)WCSAutoCatalogueTxt.Tag).Substring(0, ((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCATDir", filename.Substring(0, filename.LastIndexOf("\\")));
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueTxt", filename);
			WCSAutoCatalogueTxt.BackColor = Color.LightGreen;
			WCSAutoCatalogueExtensionTxt.Text = "";
			WCSAutoCatalogueCVAL1.Text = "ra";
			WCSAutoCatalogueCVAL2.Text = "dec";
			WCSAutoCatalogueMag.Text = "phot_bp_mean_mag";
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL1", WCSAutoCatalogueCVAL1.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL2", WCSAutoCatalogueCVAL2.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueMag", WCSAutoCatalogueMag.Text);

			if (WCSQuerySolveAfter.Checked)
				WCSAutoSolveBtn.PerformClick();
		}

		private void WCSQuerySaveFileChck_Click(object sender, System.EventArgs e)
		{
			if (WCSQuerySaveFileChck.Checked)
				WCSQuerySaveFileChooseDirBtn.Enabled = true;
			else
				WCSQuerySaveFileChooseDirBtn.Enabled = false;

			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySaveFileChck", WCSQuerySaveFileChck.Checked);
			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtn", WCSQuerySaveFileChooseDirBtn.Enabled);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoQueryBtn.ShowDropDown();
		}

		private void WCSQuerySaveFileChooseDirBtn_Click(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtnChck", WCSQuerySaveFileChooseDirBtn.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoQueryBtn.ShowDropDown();
			WCSQuerySaveFileChck.ShowDropDown();
		}

		private void WCSQuerySquareRegionChck_Click(object sender, System.EventArgs e)
		{
			if (WCSQuerySquareRegionChck.Text.Contains("Square"))
				WCSQuerySquareRegionChck.Text = "Circular Region";
			else
				WCSQuerySquareRegionChck.Text = "Square Region";

			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySquareRegion", WCSQuerySquareRegionChck.Text);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoQueryBtn.ShowDropDown();
		}

		private void WCSQuerySolveAfter_Click(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySolveAfter", WCSQuerySolveAfter.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoQueryBtn.ShowDropDown();
		}

		private void AstroQueryCatalogueNameDrop_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "AstroQueryCatalogueNameDrop", AstroQueryCatalogueNameDrop.SelectedIndex);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAutoQueryBtn.ShowDropDown();
		}

		private void WCSAutoSolveBtn_MouseEnter(object sender, System.EventArgs e)
		{
			WCSAutoSolveBtn.BackColor = Color.LightGray;
		}

		private void WCSAutoSolveBtn_MouseLeave(object sender, System.EventArgs e)
		{
			WCSAutoSolveBtn.BackColor = System.Drawing.SystemColors.Control;
		}

		private void AutoWCSScaleMenuBtn_Click(object sender, System.EventArgs e)
		{
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void AutoWCSScaleMenuBtn_DropDownOpening(object sender, System.EventArgs e)
		{
			string wcparamsfile = CCDLABPATH + "WCSparams.fits";
			if (!File.Exists(wcparamsfile))
				return;

			string[] wcsnames = JPFITS.FITSBinTable.GetAllExtensionNames(wcparamsfile);

			ToolStripButton[] tsbcs = new ToolStripButton[wcsnames.Length];

			ToolStripItem svbtn = AutoWCSScaleMenuBtn.DropDownItems[0];
			AutoWCSScaleMenuBtn.DropDownItems.Clear();
			AutoWCSScaleMenuBtn.DropDownItems.Add(svbtn);

			for (int i = 0; i < wcsnames.Length; i++)
			{
				tsbcs[i] = new ToolStripButton(wcsnames[i]);
				tsbcs[i].Width = tsbcs[i].Text.Length * 6;
				tsbcs[i].MouseDown += new MouseEventHandler(WCSParamMenuBtn_MouseDown);
				tsbcs[i].MouseUp += new MouseEventHandler(WCSParamMenuBtn_MouseUp);
				tsbcs[i].Tag = i + 1;
			}

			AutoWCSScaleMenuBtn.DropDownItems.AddRange(tsbcs);
		}

		private void AutoWCSScaleSaveBtn_Click(object sender, System.EventArgs e)
		{
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void WSCSaveScaleTxtBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode != Keys.Enter)
				return;

			e.SuppressKeyPress = true;

			string extname = WSCSaveScaleTxtBox.Text;

			if (JPMath.IsNumeric(extname.Substring(0, 1)))
			{
				extname = "";
				WSCSaveScaleTxtBox.Text = extname;
			}

			if (extname == "")
				return;

			string wcsparamsfile = CCDLABPATH + "WCSparams.fits";
			string[] entrylabels = new string[6] { "WCSScaleInit", "WCSScaleInitLB", "WCSScaleInitUB", "WCSRotationInit", "WCSRotationInitLB", "WCSRotationInitUB" };
			TypeCode[] types = new TypeCode[6] { TypeCode.Double, TypeCode.Double, TypeCode.Double, TypeCode.Double, TypeCode.Double, TypeCode.Double };
			string[] units = new string[6] { "arcsec per pixel", "arcsec per pixel", "arcsec per pixel", "Degrees", "Degrees", "Degrees" };
			object[] objarray = new object[6];
			objarray[0] = new double[1] { Convert.ToDouble(WCSScaleInit.Text) };
			objarray[1] = new double[1] { Convert.ToDouble(WCSScaleInitLB.Text) };
			objarray[2] = new double[1] { Convert.ToDouble(WCSScaleInitUB.Text) };
			objarray[3] = new double[1] { Convert.ToDouble(WCSRotationInit.Text) };
			objarray[4] = new double[1] { Convert.ToDouble(WCSRotationInitLB.Text) };
			objarray[5] = new double[1] { Convert.ToDouble(WCSRotationInitUB.Text) };
			//FITSBinTable.WriteExtension(wcsparamsfile, extname, true, entrylabels, units, null, null, null, objarray);
			FITSBinTable bt = new FITSBinTable();
			bt.SetTTYPEEntries(entrylabels, units, objarray);
			bt.Write(wcsparamsfile, extname, true);

			AutoWCSScaleMenuBtn.HideDropDown();
			AutoWCSScaleMenuBtn.ShowDropDown();
		}

		private void WCSParamMenuBtn_MouseDown(object sender, MouseEventArgs e)
		{
			string wcsparamsfile = CCDLABPATH + "WCSparams.fits";

			if (e.Button == MouseButtons.Right)
			{
				if (MessageBox.Show("Remove '" + ((ToolStripItem)sender).Text + "'?", "Remove?", MessageBoxButtons.OKCancel) == DialogResult.OK)
				{
					FITSBinTable.RemoveExtension(wcsparamsfile, ((ToolStripItem)sender).Text);
					AutoWCSScaleMenuBtn.HideDropDown();
					AutoWCSScaleMenuBtn.ShowDropDown();
				}
				return;
			}

			try
			{
				JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(wcsparamsfile, ((ToolStripItem)sender).Text);
				WCSScaleInit.Text = bt.GetTTYPEEntry("WCSScaleInit")[0].ToString();
				WCSScaleInitLB.Text = bt.GetTTYPEEntry("WCSScaleInitLB")[0].ToString();
				WCSScaleInitUB.Text = bt.GetTTYPEEntry("WCSScaleInitUB")[0].ToString();
				WCSRotationInit.Text = bt.GetTTYPEEntry("WCSRotationInit")[0].ToString();
				WCSRotationInitLB.Text = bt.GetTTYPEEntry("WCSRotationInitLB")[0].ToString();
				WCSRotationInitUB.Text = bt.GetTTYPEEntry("WCSRotationInitUB")[0].ToString();
			}
			catch
			{

			}
		}

		private void WCSParamMenuBtn_MouseUp(object sender, MouseEventArgs e)
		{
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			AutoWCSScaleMenuBtn.ShowDropDown();
		}

		private void WCSAutoXAxisParityChck_Click(object sender, System.EventArgs e)
		{
			if (WCSAutoXAxisParityChck.CheckState == CheckState.Unchecked)
				WCSAutoXAxisParityChck.CheckState = CheckState.Checked;
			else if (WCSAutoXAxisParityChck.CheckState == CheckState.Checked)
				WCSAutoXAxisParityChck.CheckState = CheckState.Indeterminate;
			else if (WCSAutoXAxisParityChck.CheckState == CheckState.Indeterminate)
				WCSAutoXAxisParityChck.CheckState = CheckState.Unchecked;

			JPFITS.REG.SetReg("CCDLAB", "WCSXParity", WCSAutoXAxisParityChck.CheckState.ToString());

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void WCSAutoYAxisParityChck_Click(object sender, System.EventArgs e)
		{
			if (WCSAutoYAxisParityChck.CheckState == CheckState.Unchecked)
				WCSAutoYAxisParityChck.CheckState = CheckState.Checked;
			else if (WCSAutoYAxisParityChck.CheckState == CheckState.Checked)
				WCSAutoYAxisParityChck.CheckState = CheckState.Indeterminate;
			else if (WCSAutoYAxisParityChck.CheckState == CheckState.Indeterminate)
				WCSAutoYAxisParityChck.CheckState = CheckState.Unchecked;

			JPFITS.REG.SetReg("CCDLAB", "WCSYParity", WCSAutoYAxisParityChck.CheckState.ToString());

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void GET_CATALOGUE_NPTS(string filename, string catExtension, string catCVAL1, string catCVAL2, string catMag, int N_bright)
		{
			JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(filename, catExtension);
			WCS_RA = bt.GetTTYPEEntry(catCVAL1);
			WCS_DEC = bt.GetTTYPEEntry(catCVAL2);
			double[] mag = bt.GetTTYPEEntry(catMag);

			//need to check mag for NaN's and re-form ra dec mag
			ArrayList ralist = new ArrayList(WCS_RA.Length);
			ArrayList declist = new ArrayList(WCS_RA.Length);
			ArrayList maglist = new ArrayList(WCS_RA.Length);
			for (int i = 0; i < mag.Length; i++)
			{
				if (Double.IsNaN(mag[i]))
					continue;

				ralist.Add(WCS_RA[i]);
				declist.Add(WCS_DEC[i]);
				maglist.Add(mag[i]);
			}
			for (int i = 0; i < ralist.Count; i++)
			{
				WCS_RA[i] = Convert.ToDouble(ralist[i]);
				WCS_DEC[i] = Convert.ToDouble(declist[i]);
				mag[i] = Convert.ToDouble(maglist[i]);
			}
			Array.Resize(ref WCS_RA, ralist.Count);
			Array.Resize(ref WCS_DEC, ralist.Count);
			Array.Resize(ref mag, ralist.Count);

			//sort the catalogue list by magnitude
			double[] keysref = new double[mag.Length];
			Array.Copy(mag, keysref, mag.Length);
			Array.Sort(mag, WCS_RA);
			Array.Copy(keysref, mag, mag.Length);
			Array.Sort(mag, WCS_DEC);

			if (N_bright > 0 && N_bright < WCS_RA.Length)
			{
				Array.Resize(ref WCS_RA, N_bright);
				Array.Resize(ref WCS_DEC, N_bright);
			}
		}

		private void PSEGroupizeBtn_Click(object sender, System.EventArgs e)
		{
			if (PSES == null)
				return;

			PSES[PSESINDEX].GroupizePSE((double)PSESeparationUpD.Value);

			PSEDRAWGROUPREGIONS = true;
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
			PSEFitResultListBox.Items.Clear();
			PSEFitResultListBox.Items.Add(string.Concat("N Sources:   ", PSES[PSESINDEX].N_Sources));
			PSEFitResultListBox.Items.Add(string.Concat("N Groups:   ", PSES[PSESINDEX].NGroups));
		}

		private void WCSRADecManual_Click(object sender, System.EventArgs e)
		{
			if (!WCSMANUALRAD_CONTINUE && !WCSMANUALRAD)//then start selecting points and set things up
			{
				if (MessageBox.Show("Please begin selecting at least 3 point sources (LEFT-CLICK).  RIGHT-CLICK when done.", "Manual WCS RA & Dec...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					return;

				IWLCK = false;//allow cursor box to move
				WCSMANUALRAD = true;
				WCSMANUALRAD_CONTINUE = true;
				EqualHWChck.Checked = true;
				FNDCOORDS_X = new int[1];//this is for plotting the local max point in the ROI
				FNDCOORDS_Y = new int[1];
				FNDCOORDRECTS = new Rectangle[(1)];
				ShowFoundCoordsChck.Checked = true;//this is for plotting the local max point in the ROI
				MANREGCOORDS = new int[0, 0];
				MANREGCOORDRECTS = new Rectangle[(0)];
				WCS_RA = new double[0];
				WCS_DEC = new double[0];
				return;
			}

			if (WCSMANUALRAD && MANREGCOORDRECTS.Length == 0)//right clicked out without any point selections, so end everything (well...not everything)
			{
				WCSMANUALRAD = false;
				WCSMANUALRAD_CONTINUE = false;
				ShowFoundCoordsChck.Checked = false;
				ImageWindow.Refresh();
				return;
			}

			if (WCSMANUALRAD && MANREGCOORDRECTS.Length > 0 && WCSMANUALRAD_CONTINUE && WCSNEWPOINT)//then enter RA & Dec for the last selection & store etc.  Also make corresponding centroid list here?
			{
				RADECBOX = new RADecBox();

				DialogResult dres = RADECBOX.ShowDialog();

				if (dres == DialogResult.Cancel)
				{
					WCSMANUALRAD = false;
					WCSMANUALRAD_CONTINUE = false;
					ShowFoundCoordsChck.Checked = false;
					ImageWindow.Refresh();
					return;
				}

				double[] tempRA = new double[WCS_RA.Length + 1];
				double[] tempDEC = new double[WCS_DEC.Length + 1];

				for (int i = 0; i < WCS_RA.Length; i++)
				{
					tempRA[i] = WCS_RA[i];
					tempDEC[i] = WCS_DEC[i];
				}

				tempRA[WCS_RA.Length] = RADECBOX.RightAscension;
				tempDEC[WCS_DEC.Length] = RADECBOX.Declination;

				WCS_RA = tempRA;
				WCS_DEC = tempDEC;
			}

			if (WCSMANUALRAD && !WCSMANUALRAD_CONTINUE)//finished.  then ask and solve WCS solution
			{
				DialogResult diares = MessageBox.Show("Proceed with WCS solution?", "Manual WCS RA & Dec...", MessageBoxButtons.YesNoCancel);
				if (diares == DialogResult.Cancel)
				{
					WCSMANUALRAD = false;
					ShowFoundCoordsChck.Checked = false;
					ImageWindow.Refresh();
					return;
				}
				if (diares == DialogResult.No)
					return;

				WCSMANUALRAD = false;
				ShowFoundCoordsChck.Checked = false;
				ImageWindow.Refresh();

				PSES = new PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
				PSESINDEX = 0;
				double[] x = new double[WCS_RA.Length];//centroid (pixels)
				double[] y = new double[WCS_RA.Length];//centroid (pixels)
				for (int i = 0; i < WCS_RA.Length; i++)
				{
					x[i] = (double)MANREGCOORDS[i, 0];
					y[i] = (double)MANREGCOORDS[i, 1];
				}
				PSES[PSESINDEX].Extract_Sources(IMAGESET[FILELISTINDEX].Image, x, y, 2, false, "");
				x = PSES[PSESINDEX].Centroids_X;
				y = PSES[PSESINDEX].Centroids_Y;

				IMAGESET[FILELISTINDEX].WCS.Solve_WCS("TAN", x, y, true, WCS_RA, WCS_DEC, IMAGESET[FILELISTINDEX].Header);
				SHOW_WCSCOORDS = true;
				WCSRADecShowChck.Checked = true;

				if (WCS_RA.Length >= 3)
				{
					float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[FILELISTINDEX].Width);
					float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[FILELISTINDEX].Height);
					MARKCOORDRECTS = new Rectangle[(WCS_RA.Length)];
					MARKCOORDS = new double[2, WCS_RA.Length];
					double xpix, ypix;
					for (int i = 0; i < WCS_RA.Length; i++)
					{
						IMAGESET[FILELISTINDEX].WCS.Get_Pixel(WCS_RA[i], WCS_DEC[i], "TAN", out xpix, out ypix, true);
						MARKCOORDRECTS[i] = new Rectangle((int)(((float)(xpix) + 0.5) * xsc - 3), (int)(((float)(ypix) + 0.5) * ysc - 3), 7, 7);
						MARKCOORDS[0, i] = xpix;
						MARKCOORDS[1, i] = ypix;
					}

					ImageWindow.Refresh();
					SubImageWindow.Refresh();

					string message = "If the WCS solution used more than 3 points then the solution is least-squares, and an error in the selection of points will show as a displacement of the selected points from the point sources.  Clear Marked Coordinate to clear points.";
					MessageBox.Show(message);
				}

				FileTxtsUpD();
			}
		}

		private void WCSCopyToLoadedImgs_Click(object sender, System.EventArgs e)
		{
			if (!IMAGESET[FILELISTINDEX].WCS.Exists())
				if (JPFITS.WorldCoordinateSolution.Exists(IMAGESET[FILELISTINDEX].Header, new string[] { "RA---TAN" }))
					IMAGESET[FILELISTINDEX].WCS = new JPFITS.WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);
				else
				{
					MessageBox.Show("No WCS found in current image header...", "Error");
					return;
				}

			for (int i = 0; i < IMAGESET.Count; i++)
			{
				if (i == FILELISTINDEX)
					continue;
				IMAGESET[FILELISTINDEX].WCS.CopyTo(IMAGESET[i].Header);
			}
			MessageBox.Show("WCS copied to " + (IMAGESET.Count - 1) + " other headers...", "Success");
		}

		private void WCSCopyFromDiskFile_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "FITS|*.fits;*.fits;*.fit|All Files|*.*";
			ofd.InitialDirectory = IMAGESET[FILELISTINDEX].FilePath;
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			WorldCoordinateSolution wcs = new WorldCoordinateSolution(new FITSHeader(ofd.FileName));
			if (!wcs.Exists())
			{
				MessageBox.Show("No World Coordinate Solution found in the selected file.", "Error...");
				return;
			}

			wcs.CopyTo(IMAGESET[FILELISTINDEX].Header);
			FileTxtsUpD();
		}

		private void WCSClearAllChck_Click(object sender, System.EventArgs e)
		{
			WCSMenu.ShowDropDown();
			WCSClearMenuBtn.ShowDropDown();
		}

		private void WCSClearMenuBtn_Click(object sender, System.EventArgs e)
		{
			if (MessageBox.Show("Are you sure you would like to clear the WCS for the image(s)?", "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
				return;

			if (WCSClearAllChck.Checked)
			{
				for (int i = 0; i < IMAGESET.Count; i++)
				{
					WorldCoordinateSolution.Clear(IMAGESET[i].Header);
					IMAGESET[i].WCS.Clear();
				}
			}
			else
			{
				WorldCoordinateSolution.Clear(IMAGESET[FILELISTINDEX].Header);
				IMAGESET[FILELISTINDEX].WCS.Clear();
			}

			FileTxtsUpD();
		}

		private void WCSRADecShowChck_Click(object sender, System.EventArgs e)
		{
			if (WCSRADecShowChck.Checked)
			{
				SHOW_WCSCOORDS = true;
				label40.Text = "a:";
				label41.Text = "d:";

				if (IMAGESET != null && IMAGESET.Count > 0)
					IMAGESET[FILELISTINDEX].WCS.Grid_Invalidate();
			}
			else
			{
				SHOW_WCSCOORDS = false;
				label40.Text = "X:";
				label41.Text = "Y:";
			}
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void WCSToolsConvertSexaFiletoDegFile_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "Any Textual File|*.*";
			ofd.Multiselect = false;
			ofd.Title = "Select a textual file of sexagesimal coordinate pairs...";
			//ofd.InitialDirectory = (string^)JPFITS.REG.GetReg("WCS", "WCSSexaToDegFileOpen");
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			double[] dum1;
			double[] dum2;
			JPFITS.WorldCoordinateSolution.SexagesimalFileToDegreeFile(ofd.FileName, true, out dum1, out dum2);
		}

		private void WCSToolsConvertDegFiletoSexaFile_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "Any Textual File|*.*";
			ofd.Multiselect = false;
			ofd.Title = "Select a textual file of degree coordinate pairs...";
			//ofd.InitialDirectory = (string^)JPFITS.REG.GetReg("WCS", "WCSSexaToDegFileOpen");
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			string[] dum1;
			string[] dum2;
			JPFITS.WorldCoordinateSolution.DegreeFileToSexagesimalFile(ofd.FileName, true, out dum1, out dum2, ":", 4);
		}

		private void WCSToolsConvertRATxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode != Keys.Enter)
				return;

			e.SuppressKeyPress = true;
			e.Handled = true;

			if (WCSToolsConvertRATxt.Text == "" && WCSToolsConvertDecTxt.Text == "")
				return;

			try
			{
				if (WCSToolsConvertRATxt.Text == "")
					WCSToolsConvertRATxt.Text = "0";
				if (WCSToolsConvertDecTxt.Text == "")
					WCSToolsConvertDecTxt.Text = "0";

				string rasex;
				string decsex;
				JPFITS.WorldCoordinateSolution.DegreeElementstoSexagesimalElements(Convert.ToDouble(WCSToolsConvertRATxt.Text), Convert.ToDouble(WCSToolsConvertDecTxt.Text), out rasex, out decsex, ":", 4);
				Clipboard.SetText(rasex + "\t" + decsex);
				WCSToolsConvertRATxt.Text = rasex;
				WCSToolsConvertDecTxt.Text = decsex;
				MessageBox.Show("Copied \r\n\r\nRA: " + rasex + "\r\n" + "Dec: " + decsex + "\r\n\r\n" + "to clipboard.", "Success!");
			}
			catch
			{
				try
				{
					if (WCSToolsConvertRATxt.Text == "")
						WCSToolsConvertRATxt.Text = "00:00:00";
					if (WCSToolsConvertDecTxt.Text == "")
						WCSToolsConvertDecTxt.Text = "00:00:00";

					double ra, dec;
					JPFITS.WorldCoordinateSolution.SexagesimalElementsToDegreeElements(WCSToolsConvertRATxt.Text, WCSToolsConvertDecTxt.Text, "", out ra, out dec);
					Clipboard.SetText(ra.ToString() + "\t" + dec.ToString());
					WCSToolsConvertRATxt.Text = ra.ToString();
					WCSToolsConvertDecTxt.Text = dec.ToString();
					MessageBox.Show("Copied \r\n\r\nRA: " + ra.ToString() + "\r\n" + "Dec: " + dec.ToString() + "\r\n\r\n" + "to clipboard.", "Success!");
				}
				catch
				{
					MessageBox.Show("Tried converting \r\n\r\nRA: " + WCSToolsConvertRATxt.Text + "\r\nDec: " + WCSToolsConvertDecTxt.Text + "\r\n\r\nto other format, but couldn't figure it out. Try again!", "Error");
				}
			}
		}


		private void AutoWCSXCorr_Click(object sender, System.EventArgs e)
		{
			//if (IMAGESET.Count == 0)
			//	return;



			////********************************assume PSE is done and available with some N pts**************************
			//int kernelradius = 1;
			//double[] x_pix_hist_vec = new double[IMAGESET[FILELISTINDEX].Width / kernelradius];
			//double[] y_pix_hist_vec = new double[IMAGESET[FILELISTINDEX].Height / kernelradius];
			//for (int k = 0; k < PSES[PSESINDEX].N_Sources; k++)
			//{
			//	x_pix_hist_vec[(int)Math.Round(PSES[PSESINDEX].Centroids_X[k] / (double)kernelradius)]++;
			//	y_pix_hist_vec[(int)Math.Round(PSES[PSESINDEX].Centroids_Y[k] / (double)kernelradius)]++;
			//}
			////x_pix_hist_vec = JPMath.VectorSubScalar(x_pix_hist_vec, JPMath.Mean(x_pix_hist_vec));
			////y_pix_hist_vec = JPMath.VectorSubScalar(y_pix_hist_vec, JPMath.Mean(y_pix_hist_vec));
			///*array<double>^ axis = new double[x_pix_hist_vec.Length);
			//for (int k = 0; k < axis.Length; k++)
			//	axis[k] = (double)k;
			//JPPlot^ xplot = new JPPlot();
			//xplot.PlotLine(axis, x_pix_hist_vec, "", "", "", System.DataVisualization.Charting.SeriesChartType.Line, "test");
			//JPPlot^ yplot = new JPPlot();
			//yplot.PlotLine(axis, y_pix_hist_vec, "", "", "", System.DataVisualization.Charting.SeriesChartType.Line, "test");
			//return;*/






			//GET_CATALOGUE_NPTS((string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text, WCSAutoCatalogueCVAL1.Text, WCSAutoCatalogueCVAL2.Text, WCSAutoCatalogueMag.Text, /*N*/200);








			//JPMath.PointD[] CATpts = new JPMath.PointD[WCS_RA.Length];
			//double crval1 = 0, crval2 = 0;
			//for (int i = 0; i < CATpts.Length; i++)
			//{
			//	CATpts[i] = new JPMath.PointD(WCS_RA[i], WCS_DEC[i], 0);
			//	crval1 += CATpts[i].X;
			//	crval2 += CATpts[i].Y;
			//}
			//crval1 /= (double)CATpts.Length;//the reference value can be the mean
			//crval2 /= (double)CATpts.Length;//the reference value can be the mean

			////convert the catalogue points to intermediate points
			//JPMath.PointD[] CATpts_intrmdt = new JPMath.PointD[WCS_RA.Length];
			//double a0 = crval1 * Math.PI / 180, d0 = crval2 * Math.PI / 180;
			//for (int i = 0; i < CATpts_intrmdt.Length; i++)
			//{
			//	double a = CATpts[i].X * Math.PI / 180;//radians
			//	double d = CATpts[i].Y * Math.PI / 180;//radians

			//	//for tangent plane Gnomic
			//	double x_intrmdt = Math.Cos(d) * Math.Sin(a - a0) / (Math.Cos(d0) * Math.Cos(d) * Math.Cos(a - a0) + Math.Sin(d0) * Math.Sin(d));
			//	double y_intrmdt = (Math.Cos(d0) * Math.Sin(d) - Math.Cos(d) * Math.Sin(d0) * Math.Cos(a - a0)) / (Math.Sin(d0) * Math.Sin(d) + Math.Cos(d0) * Math.Cos(d) * Math.Cos(a - a0));

			//	CATpts_intrmdt[i] = new JPMath.PointD(x_intrmdt, y_intrmdt, 0);
			//}

			//double crpix1 = JPMath.Mean(PSES[PSESINDEX].Centroids_X, true);
			//double crpix2 = JPMath.Mean(PSES[PSESINDEX].Centroids_Y, true);

			//double minangle = -2 * Math.PI / 180;
			//double maxangle = 2 * Math.PI / 180;

			//double anglestep = Math.Atan(/*(double)(kernelradius)*/2 / (double)(IMAGESET[FILELISTINDEX].Width)) / 3;//radians
			//int totalangles = (int)Math.Round((maxangle - minangle) / anglestep);
			//anglestep = (maxangle - minangle) / (double)totalangles;//radians

			////MessageBox.Show(totalangles + " total angles; " + anglestep * 180 / Math.PI + " angle step degrees");
			////return;

			//double S = 0.41581283;//scale ''/pix
			//S *= Math.PI / 180 / 3600;// rad/pix

			//JPPlot xplot = new JPPlot();
			//JPPlot yplot = new JPPlot();

			////parallel if
			//for (int i = 0; i < totalangles; i++)
			//{
			//	double phi = minangle + (double)i * anglestep;
			//	JPMath.PointD[] CATpts_intrmdt_pix = new JPMath.PointD[CATpts_intrmdt.Length];
			//	//phi = -phi;

			//	//transform rotate the intermediate coordinates to pixel coordinates using fixed scale and current rotation phi and given crpix references
			//	for (int k = 0; k < CATpts_intrmdt.Length; k++)
			//	{
			//		double x_intrmdt_pix = ((double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / S * (Math.Cos(-phi) * CATpts_intrmdt[k].X - Math.Sin(-phi) * CATpts_intrmdt[k].Y) + crpix1));
			//		double y_intrmdt_pix = ((double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / S * (Math.Sin(-phi) * CATpts_intrmdt[k].X + Math.Cos(-phi) * CATpts_intrmdt[k].Y) + crpix2));
			//		CATpts_intrmdt_pix[k] = new JPMath.PointD(x_intrmdt_pix, y_intrmdt_pix, 0);
			//	}

			//	//create binned/histogram x/y vectors from current CATpts_intrmdt_pix
			//	double[] X_intrmdt_pix_hist_vec = new double[IMAGESET[FILELISTINDEX].Width / kernelradius];
			//	double[] Y_intrmdt_pix_hist_vec = new double[IMAGESET[FILELISTINDEX].Height / kernelradius];
			//	for (int k = 0; k < CATpts_intrmdt_pix.Length; k++)
			//	{
			//		int x = (int)Math.Round(CATpts_intrmdt_pix[k].X / (double)kernelradius);
			//		int y = (int)Math.Round(CATpts_intrmdt_pix[k].Y / (double)kernelradius);

			//		if (x >= 0 && y >= 0 && x < X_intrmdt_pix_hist_vec.Length && y < Y_intrmdt_pix_hist_vec.Length)
			//		{
			//			X_intrmdt_pix_hist_vec[x]++;
			//			Y_intrmdt_pix_hist_vec[y]++;
			//		}
			//	}
			//	//X_intrmdt_pix_hist_vec = JPMath.VectorSubScalar(X_intrmdt_pix_hist_vec, JPMath.Mean(X_intrmdt_pix_hist_vec));
			//	//Y_intrmdt_pix_hist_vec = JPMath.VectorSubScalar(Y_intrmdt_pix_hist_vec, JPMath.Mean(Y_intrmdt_pix_hist_vec));

			//	/*array<double>^ axis = new double[X_intrmdt_pix_hist_vec.Length);
			//	for (int k = 0; k < axis.Length; k++)
			//		axis[k] = (double)k;
			//	JPPlot^ xplot = new JPPlot();
			//	xplot.PlotLine(axis, X_intrmdt_pix_hist_vec, "", "", "", System.DataVisualization.Charting.SeriesChartType.Line, "test");
			//	JPPlot^ yplot = new JPPlot();
			//	yplot.PlotLine(axis, Y_intrmdt_pix_hist_vec, "", "", "", System.DataVisualization.Charting.SeriesChartType.Line, "test");
			//	return;*/

			//	int[] x_lags = new int[X_intrmdt_pix_hist_vec.Length * 2 - 1];
			//	int[] y_lags = new int[Y_intrmdt_pix_hist_vec.Length * 2 - 1];

			//	double[] x_xcorr = JPMath.XCorr(x_pix_hist_vec, X_intrmdt_pix_hist_vec, out x_lags, false);
			//	double[] y_xcorr = JPMath.XCorr(y_pix_hist_vec, Y_intrmdt_pix_hist_vec, out y_lags, false);

			//	double[] d_xlags = new double[x_lags.Length];
			//	for (int k = 0; k < d_xlags.Length; k++)
			//		d_xlags[k] = (double)x_lags[k];
			//	xplot.PlotLine(d_xlags, x_xcorr, "", "", "", System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "test");
			//	//yplot.PlotLine(d_xlags, y_xcorr, "", "", "", System.DataVisualization.Charting.SeriesChartType.Line, "test");
			//	//return;
			//	if (MessageBox.Show(i + " " + totalangles + " " + phi * 180 / Math.PI, "", MessageBoxButtons.OKCancel) == DialogResult.OK)
			//		continue;
			//	else
			//		return;





			//	bool x_check_soltn = false;
			//	bool y_check_soltn = false;

			//	int n_matches = 10;

			//	int x_lag = 0, y_lag = 0;
			//	for (int k = 0; k < x_xcorr.Length; k++)
			//		if (x_xcorr[k] >= n_matches)
			//		{
			//			x_check_soltn = true;
			//			x_lag = x_lags[k] * kernelradius;
			//			break;
			//		}
			//	for (int k = 0; k < y_xcorr.Length; k++)
			//		if (y_xcorr[k] >= n_matches)
			//		{
			//			y_check_soltn = true;
			//			y_lag = y_lags[k] * kernelradius;
			//			break;
			//		}

			//	if (!x_check_soltn || !y_check_soltn)
			//		continue;

			//	//now check for a solution
			//	//critical here when parallel

			//	//have rotation, update crpix based on lags...plus or minus????????............I think -ve due to parity inversion of interm CAT coords wrt PSE coords inside transformation
			//	crpix1 -= x_lag;
			//	crpix2 -= y_lag;

			//	int c = 0;
			//	for (int k = 0; k < CATpts_intrmdt.Length; k++)
			//	{
			//		int x_intrmdt_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / S * (Math.Cos(-phi) * CATpts_intrmdt[k].X - Math.Sin(-phi) * CATpts_intrmdt[k].Y) + crpix1));
			//		int y_intrmdt_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / S * (Math.Sin(-phi) * CATpts_intrmdt[k].X + Math.Cos(-phi) * CATpts_intrmdt[k].Y) + crpix2));

			//		if (x_intrmdt_pix > 0 && y_intrmdt_pix > 0 && x_intrmdt_pix < IMAGESET[FILELISTINDEX].Width && y_intrmdt_pix < IMAGESET[FILELISTINDEX].Height && PSES[PSESINDEX].SourceBooleanMap[x_intrmdt_pix, y_intrmdt_pix])
			//			c++;
			//	}
			//	//c should be >= n_matches........*******************************
			//	MessageBox.Show(c + " n_matches after transformation w lags result");

			//	double[] xpix_pse_matches = new double[c];
			//	double[] ypix_pse_matches = new double[c];
			//	WCS_RA = new double[c];
			//	WCS_DEC = new double[c];
			//	MARKCOORDS = new double[2, c];
			//	c = 0;
			//	for (int k = 0; k < CATpts_intrmdt.Length; k++)
			//	{
			//		int x_intrmdt_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Width - 1 - (1 / S * (Math.Cos(-phi) * CATpts_intrmdt[k].X - Math.Sin(-phi) * CATpts_intrmdt[k].Y) + crpix1));
			//		int y_intrmdt_pix = (int)Math.Round((double)IMAGESET[FILELISTINDEX].Height - 1 - (1 / S * (Math.Sin(-phi) * CATpts_intrmdt[k].X + Math.Cos(-phi) * CATpts_intrmdt[k].Y) + crpix2));

			//		if (x_intrmdt_pix > 0 && y_intrmdt_pix > 0 && x_intrmdt_pix < IMAGESET[FILELISTINDEX].Width && y_intrmdt_pix < IMAGESET[FILELISTINDEX].Height && PSES[PSESINDEX].SourceBooleanMap[x_intrmdt_pix, y_intrmdt_pix])
			//		{
			//			int index = PSES[PSESINDEX].SourceIndexMap[x_intrmdt_pix, y_intrmdt_pix];
			//			xpix_pse_matches[c] = PSES[PSESINDEX].Centroids_X[index];
			//			ypix_pse_matches[c] = PSES[PSESINDEX].Centroids_Y[index];
			//			WCS_RA[c] = CATpts[k].X;
			//			WCS_DEC[c] = CATpts[k].Y;
			//			MARKCOORDS[0, c] = x_intrmdt_pix;
			//			MARKCOORDS[1, c] = y_intrmdt_pix;
			//			c++;
			//		}
			//	}


			//}
		}
	}
}