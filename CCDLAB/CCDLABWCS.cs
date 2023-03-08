using System;
using System.Collections;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using JPFITS;
using System.Threading.Tasks;
using System.Collections.Concurrent;

namespace CCDLAB
{
	public partial class Form1
	{
		private void WCSSolutionPtsCopyTableBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			double[] cp1 = IMAGESET[IMAGESETINDEX].WCS.GetCPIXPixels(1, true);
			double[] cp2 = IMAGESET[IMAGESETINDEX].WCS.GetCPIXPixels(2, true);
			double[] cv1 = IMAGESET[IMAGESETINDEX].WCS.GetCVALValues(1, true, true);
			double[] cv2 = IMAGESET[IMAGESETINDEX].WCS.GetCVALValues(2, true, true);
			double[] cd1 = IMAGESET[IMAGESETINDEX].WCS.GetWCSResiduals(1);
			double[] cd2 = IMAGESET[IMAGESETINDEX].WCS.GetWCSResiduals(2);

			string clipbrd = "Source Pixel X-Centroid (pixels)" + "\t" + "Source Pixel Y-Centroid (pixels)" + "\t" + "Source Catalogue RA (degrees)" + "\t" + "Source Catalogue Decl (degrees)" + "\t" + "WCS RA Residual (arcsec)" + "\t" + "WCS Decl Residual (arcsec)";
			for (int i = 1; i <= cp2.Length; i++)
				clipbrd += "\r\n" + cp1[i - 1] + "\t" + cp2[i - 1] + "\t" + cv1[i - 1] + "\t" + cv2[i - 1] + "\t" + cd1[i - 1] + "\t" + cd2[i - 1];

			Clipboard.SetText(clipbrd);

			MessageBox.Show("WCS Coordinates Table copied to clipboard...");
		}

		private void WCSAstraCartaQueryLimitLengthDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "WCSAstroQueryLimitLLength", WCSAstraCartaLimitLLengthDrop.SelectedIndex);
		}

		private void WCSPlotSolutionPtsBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.ShowDropDown();
			WCSSolutionPtsBtn.ShowDropDown();

			if (WCSPlotSolutionPtnBtn.Checked == true)
			{
				SHOW_WCSSOLUTIONPOINTS = true;
				PSESPLOTALL = false;
				PSESPLOTNONE = false;
				PSEDrop.Enabled = true;
			}
			else
			{
				SHOW_WCSSOLUTIONPOINTS = false;
				PSESPLOTALL = false;
				PSESPLOTNONE = false;
				MarkCoordClear.PerformClick();
			}

			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void WCSPlotSolutionResidsOnlyBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.ShowDropDown();
			WCSSolutionPtsBtn.ShowDropDown();
			WCSPlotSolutionPtnBtn.ShowDropDown();

			WCSPlotSolutionPtsBtn_Click(sender, e);
		}

		private void WCSPlotSolutionViewTableBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			if (WorldCoordinateSolution.Exists(IMAGESET[IMAGESETINDEX].Header, new string[2] { "TAN", "TAN" }))
				if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
					IMAGESET[IMAGESETINDEX].WCS = new WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);

			if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
				return;

			string[,] table = IMAGESET[IMAGESETINDEX].WCS.WCS_Table;

			PSETableViewer PSETABLEVIEWER = new PSETableViewer(table);

			PSETABLEVIEWER.Show(this);
		}

		private void WCSPlotResidualScaleTxt_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				double[] cd1 = IMAGESET[IMAGESETINDEX].WCS.GetWCSResiduals(1);
				double[] cd2 = IMAGESET[IMAGESETINDEX].WCS.GetWCSResiduals(2);

				double maxv = 0;
				for (int i = 0; i < cd1.Length; i++)
					if (cd1[i] * cd1[i] + cd2[i] * cd2[i] > maxv)
						maxv = cd1[i] * cd1[i] + cd2[i] * cd2[i];

				maxv = Math.Sqrt(maxv);
				maxv = maxv / IMAGESET[IMAGESETINDEX].WCS.GetCDELTn(1);

				WCSPlotResidualScaleTxt.Text = (IMAGESET[IMAGESETINDEX].Width / 5 / maxv).ToString();
			}
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

			GET_CATALOGUE_NPTS((string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text, WCSAutoCatalogueCVAL1Txt.Text, WCSAutoCatalogueCVAL2Txt.Text, WCSAutoCatalogueMagTxt.Text, Convert.ToInt32(WCSLoadListNPtsTxt.Text));

			double[] cp1 = new double[WCS_RA.Length];
			double[] cp2 = new double[WCS_RA.Length];
			IMAGESET[IMAGESETINDEX].WCS.Get_Pixels(WCS_RA, WCS_DEC, "TAN", out cp1, out cp2, true);

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
					if ((int)MARKCOORDS[0, i] > 0 && (int)MARKCOORDS[0, i] < IMAGESET[IMAGESETINDEX].Width && (int)MARKCOORDS[1, i] > 0 && (int)MARKCOORDS[1, i] < IMAGESET[IMAGESETINDEX].Height)
						try
						{
							if (PSESET[PSESETINDEX].SourceBooleanMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]])
							{
								n++;
								match[i] = true;
							}
						}
						catch(Exception ex)
						{
							MessageBox.Show(ex.Data + "	" + ex.InnerException + "	" + ex.Message + "	" + ex.Source + "	" + ex.StackTrace + "	" + ex.TargetSite);
						}						

				double[] cp1 = new double[n];
				double[] cp2 = new double[n];
				double[] ratemp = new double[n];
				double[] dectemp = new double[n];
				double[,] temp = new double[2, n];
				n = 0;
				for (int i = 0; i < MARKCOORDRECTS.Length; i++)
					try
					{
						if (match[i])
						{
							int ind = PSESET[PSESETINDEX].SourceIndexMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]];
							cp1[n] = PSESET[PSESETINDEX].Centroids_X_Pixel[ind];
							cp2[n] = PSESET[PSESETINDEX].Centroids_Y_Pixel[ind];
							ratemp[n] = WCS_RA[i];
							dectemp[n] = WCS_DEC[i];
							temp[0, n] = MARKCOORDS[0, i];
							temp[1, n] = MARKCOORDS[1, i];
							n++;
						}
					}
					catch (Exception ex)
					{
						MessageBox.Show(ex.Data + "	" + ex.InnerException + "	" + ex.Message + "	" + ex.Source + "	" + ex.StackTrace + "	" + ex.TargetSite);
					}

				//PSESET[PSESETINDEX] = new PointSourceExtractor(IMAGESET[IMAGESETINDEX].Image, cp1, cp2, PSESET[PSESETINDEX].KernelRadius, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "");
				PSESET[PSESETINDEX] = new JPFITS.PointSourceExtractor();
				PSESET[PSESETINDEX].Extract_Sources(IMAGESET[IMAGESETINDEX].Image, cp1, cp2, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);

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
				PSEFitResultListBox.Items.Add(string.Concat("N:   ", PSESET[PSESETINDEX].N_Sources));
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

			IMAGESET[IMAGESETINDEX].WCS.Solve_WCS(WorldCoordinateSolution.WCSType.TAN, PSESET[PSESETINDEX].Centroids_X, PSESET[PSESETINDEX].Centroids_Y, true, WCS_RA, WCS_DEC, IMAGESET[IMAGESETINDEX].Header, WCSOptionsVerboseChck.Checked/*, WCS_INIT*/);
			FileTxtsUpD();
			IMAGESET[IMAGESETINDEX].WCS.Get_Pixels(WCS_RA, WCS_DEC, "TAN", out double[] x, out double[] y, true);

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

		private void WCSAutoBatch()
		{
			if (MessageBox.Show("Read to proceed with batch WCS?", "Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.Cancel)
				return;

			WAITBAR = new WaitBar();
			WAITBAR.Text = "Batch WCS";
			WAITBAR.ProgressBar.Maximum = IMAGESET.Count;
			WCSAutoBatchBGWrkr.RunWorkerAsync();
			WAITBAR.ShowDialog();
		}

		private void WCSAutoBatchBGWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			WCSAutoSolver wcsas;
			ArrayList keys = new ArrayList();

			if (IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(WCSAstraCartaCVAL1Txt.Text, false) == -1 || IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(WCSAstraCartaCVAL2Txt.Text, false) == -1)
			{
				MessageBox.Show(string.Format("The CVAL1 '{0}' or CVAL2 '{1}' terms don't exist in the header.", WCSAstraCartaCVAL1Txt.Text, WCSAstraCartaCVAL2Txt.Text), "Error");
				return;
			}

			string cval1 = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(WCSAstraCartaCVAL1Txt.Text);
			string cval2 = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(WCSAstraCartaCVAL2Txt.Text);
			double ra = 0, dec = 0;
			try
			{
				ra = Convert.ToDouble(cval1);//value is degree format
				dec = Convert.ToDouble(cval2);
			}
			catch//must be sexagesimal
			{
				WorldCoordinateSolution.SexagesimalElementsToDegreeElements(cval1, cval2, "", out ra, out dec);
			}
			if (WCSAstraCartaSquareRegionChck.Text.Contains("Circular"))
			{
				keys.Add("-shape");
				keys.Add("circle");
			}
			double buffer = 0;
			if (WCSAstraCartaBufferTxt.Text != "")
				buffer = Convert.ToDouble(WCSAstraCartaBufferTxt.Text);
			if (buffer != 0)
			{
				keys.Add("-buffer");
				keys.Add(buffer);
			}
			double pmepoch = 0;
			if (WCSAstraCartaPMEpochTxt.Text != "")
			{
				if (JPMath.IsNumeric(WCSAstraCartaPMEpochTxt.Text))
				{
					pmepoch = Convert.ToDouble(WCSAstraCartaPMEpochTxt.Text);
					REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", "");
				}
				else if (JPMath.IsNumeric(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("YEARDATE")))
					pmepoch = Convert.ToDouble(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("YEARDATE"));
			}
			if (pmepoch != 0)
			{
				keys.Add("-pmepoch");
				keys.Add(pmepoch);

				if (!JPMath.IsNumeric(WCSAstraCartaPMEpochTxt.Text))
					REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", WCSAstraCartaPMEpochTxt.Text);
				else
					REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", "");
			}
			else
				REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", "");
			keys.Add("-nquery");
			keys.Add(Convert.ToInt32(WCSAstraCartaLimitLLengthDrop.SelectedItem.ToString()));
			string catalogue = WCSAstraCartaCatalogueNameDrop.SelectedItem.ToString();
			keys.Add("-catalogue");
			keys.Add(catalogue.Trim());
			string filter = WCSAstraCartaFilterDrop.SelectedItem.ToString();
			keys.Add("-filter");
			keys.Add(filter);
			keys.Add("-fitsout");
			keys.Add("-overwrite");

			double scale = Convert.ToDouble(WCSAutoScaleInitTxt.Text);
			double scalB = Convert.ToDouble(WCSAutoScaleInitLBTxt.Text);
			double scalU = Convert.ToDouble(WCSAutoScaleInitUBTxt.Text);
			double rotn = Convert.ToDouble(WCSAutoRotationInitTxt.Text);
			double rotnL = Convert.ToDouble(WCSAutoRotationInitLBTxt.Text);
			double rotnU = Convert.ToDouble(WCSAutoRotationInitUBTxt.Text);
			double tol = Convert.ToDouble(WCSAutoVertexToleranceTxt.Text);
			int stopNpts = Convert.ToInt32(WCSAutoStopNMatchesText.Text);
			int stopPercpts = Convert.ToInt32(WCSAutoStopPercMatchesText.Text);
			bool condtriars = false;// WCSAutoConditionArraysChck.Checked;

			int catchredocounter = 0;

			for (int i = 0; i < IMAGESET.Count; i++)
			{
			redo:
				if (catchredocounter > 5)
				{
					catchredocounter = 0;
					continue;
				}

				try
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;

					WCSAutoBatchBGWrkr.ReportProgress(i + 1, new object[] { "AstraCarta is running...", catchredocounter });
					string catlg = AstraCarta.Query(ra, dec, scale, IMAGESET[i].Width, IMAGESET[i].Height, keys);

					WCSAutoBatchBGWrkr.ReportProgress(i + 1, new object[] { "WCSAutoSolver is running...", catchredocounter });
					wcsas = new WCSAutoSolver("TAN", 75, IMAGESET[i], ROI_REGION, (double)PSESaturationUpD.Value, PSEAutoBackgroundChck.Checked, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, catlg, "GaiaDR3", "ra", "dec", WCSAutoCatalogueMagTxt.Text, Convert.ToInt32(WCSAutoRefineNPtsTxt.Text));
					wcsas.SolveAsync(scale, scalB, scalU, rotn, rotnL, rotnU, tol, stopNpts, stopPercpts, condtriars, false);
					if (wcsas.Solved)
					{
						IMAGESET[i].WCS = wcsas.WCS_Solution;
						wcsas.WCS_Solution.CopyTo(IMAGESET[i].Header, true);
					}
					catchredocounter = 0;
				}
				catch
				{
					catchredocounter++;
					goto redo;
				}
			}
		}

		private void WCSAutoBatchBGWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.Text = "Processing image " + e.ProgressPercentage + "(" + ((int)((object[])e.UserState)[1] + 1).ToString() + ") of " + IMAGESET.Count;
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = (string)((object[])e.UserState)[0];
		}

		private void WCSAutoBatchBGWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WAITBAR.Close();
		}

		private void WCSAutoSolveBtn_Click(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.HideDropDown();
			AutoWCSMenuItem.HideDropDown();
			//WCS_INIT = null;

			JPFITS.REG.SetReg("CCDLAB", "PSEWidth", PSEKernelRadUpD.Value.ToString());
			JPFITS.REG.SetReg("CCDLAB", "PSEBackgroundRadUpD", PSEBackgroundRadUpD.Value.ToString());

			if (Convert.ToDouble(WCSAutoScaleInitLBTxt.Text) > Convert.ToDouble(WCSAutoScaleInitTxt.Text) || Convert.ToDouble(WCSAutoScaleInitUBTxt.Text) < Convert.ToDouble(WCSAutoScaleInitTxt.Text))
			{
				WCSMenu.ShowDropDown();
				AutoWCSMenuItem.ShowDropDown();
				MessageBox.Show("Problem with your initial scale settings...", "Error...");
				return;
			}

			if (Convert.ToDouble(WCSAutoRotationInitLBTxt.Text) > Convert.ToDouble(WCSAutoRotationInitTxt.Text) || Convert.ToDouble(WCSAutoRotationInitUBTxt.Text) < Convert.ToDouble(WCSAutoRotationInitTxt.Text))
			{
				WCSMenu.ShowDropDown();
				AutoWCSMenuItem.ShowDropDown();
				MessageBox.Show("Problem with your initial rotation settings...", "Error...");
				return;
			}

			if (PSESeachROIOnlyChck.Checked)
			{
				if (PSEEllipticalROI.Checked)//elliptical ROI
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

			if (WCSOptionsBatch.Checked)
			{
				WCSAutoBatch();
				return;
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

				PSEDrop.Items.Clear();
				PSEDrop.Items.Add("WCSAutoPSE");
				PSEDrop.Enabled = true;
				PSESPLOTALL = false;
				PSESPLOTNONE = false;
				PSESET.Clear();
				PSESET.Add(new JPFITS.PointSourceExtractor());
				PSESETINDEX = 0;

				WCSAutoSolveBtn.Text = "Cancel";
				WCSAUTOCANCEL = false;
				ProgressBar.Maximum = 100;
				WCSAutoBGWrkr.RunWorkerAsync();
			}
			else//use external DLL
			{
				WCSAS = new JPFITS.WCSAutoSolver("TAN", Convert.ToInt32(WCSAutoNCatPtsTxt.Text), IMAGESET[IMAGESETINDEX], ROI_REGION, (double)PSESaturationUpD.Value, PSEAutoBackgroundChck.Checked, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, (string)WCSAutoCatalogueTxt.Tag, WCSAutoCatalogueExtensionTxt.Text, WCSAutoCatalogueCVAL1Txt.Text, WCSAutoCatalogueCVAL2Txt.Text, WCSAutoCatalogueMagTxt.Text, Convert.ToInt32(WCSAutoRefineNPtsTxt.Text));
				WCSAS.SolveAsync(Convert.ToDouble(WCSAutoScaleInitTxt.Text), Convert.ToDouble(WCSAutoScaleInitLBTxt.Text), Convert.ToDouble(WCSAutoScaleInitUBTxt.Text), Convert.ToDouble(WCSAutoRotationInitTxt.Text), Convert.ToDouble(WCSAutoRotationInitLBTxt.Text), Convert.ToDouble(WCSAutoRotationInitUBTxt.Text), 0.25, Convert.ToInt32(WCSAutoStopNMatchesText.Text), Convert.ToInt32(WCSAutoStopPercMatchesText.Text), WCSAutoConditionArraysChck.Checked, true);

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
			try
			{
				POLYPOINTS = null;
				POLYPOINTS2 = null;
				MARKCOORDRECTS = null;
				WCSRADecShowChck.Checked = false;
				SHOW_WCSCOORDS = false;				

				float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[IMAGESETINDEX].Width);
				float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[IMAGESETINDEX].Height);
				int nCATpts = Convert.ToInt32(WCSAutoNCatPtsTxt.Text);
				double scale_init = Convert.ToDouble(WCSAutoScaleInitTxt.Text) / 3600 * Math.PI / 180;
				double scale_lb = Convert.ToDouble(WCSAutoScaleInitLBTxt.Text) / 3600 * Math.PI / 180;
				double scale_ub = Convert.ToDouble(WCSAutoScaleInitUBTxt.Text) / 3600 * Math.PI / 180;
				double rotat_init = Convert.ToDouble(WCSAutoRotationInitTxt.Text) * Math.PI / 180;
				double rotat_lb = Convert.ToDouble(WCSAutoRotationInitLBTxt.Text) * Math.PI / 180;
				double rotat_ub = Convert.ToDouble(WCSAutoRotationInitUBTxt.Text) * Math.PI / 180;
				double vertextol = Convert.ToDouble(WCSAutoVertexToleranceTxt.Text) * Math.PI / 180;
				bool do_parallel = !WCSAutoDisplayChck.Checked;
				string catfilename = (string)WCSAutoCatalogueTxt.Tag;
				string catCVAL1 = WCSAutoCatalogueCVAL1Txt.Text;
				string catCVAL2 = WCSAutoCatalogueCVAL2Txt.Text;
				string catExtension = WCSAutoCatalogueExtensionTxt.Text;
				string catMag = WCSAutoCatalogueMagTxt.Text;
				int stopNpts = Convert.ToInt32(WCSAutoStopNMatchesText.Text);
				int stopPercpts = Convert.ToInt32(WCSAutoStopPercMatchesText.Text);

				//get catalogue RA, Dec, and mag's, and sort by mags
				if (!File.Exists(catfilename))
				{
					MessageBox.Show("Cannot find catalogue file:\r\r" + catfilename + "\r\rDoes not exist.", "Error...");
					return;
				}

				JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(catfilename, catExtension);
				double[] ra = (double[])bt.GetTTYPEEntry(catCVAL1, out _, out _);
				double[] dec = (double[])bt.GetTTYPEEntry(catCVAL2, out _, out _);
				double[] mag = (double[])bt.GetTTYPEEntry(catMag, out _, out _, FITSBinTable.TTYPEReturn.AsDouble);

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
				double div = 8;
				int niters = 0;
				int maxiters = 11;
				double immax = IMAGESET[IMAGESETINDEX].Max;
				double immed = IMAGESET[IMAGESETINDEX].Median;
				double imamp = immax - immed;
				double pixthresh = imamp / div + immed;
				double pix_sat = (double)PSESaturationUpD.Value;
				while (niters <= maxiters)
				{
					niters++;

					PSESET[PSESETINDEX] = new PointSourceExtractor();
					PSESET[PSESETINDEX].Extract_Sources(IMAGESET[IMAGESETINDEX].Image, pix_sat, pixthresh, Double.MaxValue, 0, Double.MaxValue, false, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", ROI_REGION, false, IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5, false, PSEBackgroundSeparationRadiusLabel.Text.Contains("Src"));
					ImageWindow.Refresh();
					SubImageWindow.Refresh();

					if (PSESET[PSESETINDEX].N_Sources >= nCATpts)
						break;

					div *= 2;
					pixthresh = imamp / div + immed;
				}
				if (PSESET[PSESETINDEX].N_Sources > nCATpts)
				{
					PSESET[PSESETINDEX].ClipToNBrightest(nCATpts);
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
				}				

				//turn the PSE results into points
				JPMath.PointD[] PSEpts = new JPMath.PointD[PSESET[PSESETINDEX].N_Sources];
				double crpix1_init = 0, crpix2_init = 0, crpix1_lb = Double.MaxValue, crpix1_ub = Double.MinValue, crpix2_lb = Double.MaxValue, crpix2_ub = Double.MinValue;
				for (int i = 0; i < PSEpts.Length; i++)
				{
					PSEpts[i] = new JPMath.PointD(IMAGESET[IMAGESETINDEX].Width - 1 - PSESET[PSESETINDEX].Centroids_X[i], IMAGESET[IMAGESETINDEX].Height - 1 - PSESET[PSESETINDEX].Centroids_Y[i], PSESET[PSESETINDEX].Centroids_Volume[i]);
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
				crpix1_init /= (double)PSEpts.Length;//the reference pixel initial guesses can be the means
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
								POLYPOINTS[0] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - PSEtriangles[c].GetVertex(0).X - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - PSEtriangles[c].GetVertex(0).Y - 0.5) * ysc));
								POLYPOINTS[1] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - PSEtriangles[c].GetVertex(1).X - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - PSEtriangles[c].GetVertex(1).Y - 0.5) * ysc));
								POLYPOINTS[2] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - PSEtriangles[c].GetVertex(2).X - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - PSEtriangles[c].GetVertex(2).Y - 0.5) * ysc));
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
				TimeSpan ts = new TimeSpan();
				bool solution = false;
				int prog = 0, threadnum = 0;
				ulong ncompares = 0, nfalsepositives = 0, nfalsenegatives = 0, similartriangles = 0;
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
				DATE = DateTime.Now;

				Parallel.ForEach(rangePartitioner, opts, (range, loopState) =>
				{
					if (solution || WCSAUTOCANCEL)
						loopState.Stop();

					ulong ncompareslocal = 0, nfalsepositiveslocal = 0, nfalsenegatives_local = 0, similartriangleslocal = 0;
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
							if ((int)((double)i * mdpT100ovrlen) > prog)
								WCSAutoBGWrkr.ReportProgress(++prog);

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
							POLYPOINTS[0] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - xpix_triplet[0] - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - ypix_triplet[0] - 0.5) * ysc));
							POLYPOINTS[1] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - xpix_triplet[1] - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - ypix_triplet[1] - 0.5) * ysc));
							POLYPOINTS[2] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - xpix_triplet[2] - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - ypix_triplet[2] - 0.5) * ysc));
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

							//this is the angle subtended between the two field vectors of the PSE and intermediate triangles...in the correct direction
							double theta = Math.Atan2(PSEtriangles[i].FieldVector.X * CATtriangles_intrmdt[j].FieldVector.Y - PSEtriangles[i].FieldVector.Y * CATtriangles_intrmdt[j].FieldVector.X, PSEtriangles[i].FieldVector.X * CATtriangles_intrmdt[j].FieldVector.X + PSEtriangles[i].FieldVector.Y * CATtriangles_intrmdt[j].FieldVector.Y);

							if (compare_fieldvectors)//if a rotation estimate has been provided
							{
								//if the angle between the field vectors is smaller/larger than the estimate and bounds, then continue – not the correct triangles to fit given the rotation bounds estimate
								if (theta > (rotat_ub + vertextol) || theta < (rotat_lb - vertextol))//+- WCS_VERTEX_TOL to bounds to provide tolerance when bounds are equal
									continue;

								P0[1] = rotat_init;//if here, then reset the fitter’s rotation parameter to initial estimate provided (others reset below)
							}
							else//no rotation estimate provided, so we can make our own
							{
								P0[1] = theta;//set the initial rotation to the angle between the field vectors
								PLB[1] = theta - vertextol;// provide some tolerance bounds
								PUB[1] = theta + vertextol;// provide some tolerance bounds
							}

							similartriangleslocal++;

							Xintrmdt_triplet[0] = CATtriangles_intrmdt[j].GetVertex(0).X;
							Yintrmdt_triplet[0] = CATtriangles_intrmdt[j].GetVertex(0).Y;
							Xintrmdt_triplet[1] = CATtriangles_intrmdt[j].GetVertex(1).X;
							Yintrmdt_triplet[1] = CATtriangles_intrmdt[j].GetVertex(1).Y;
							Xintrmdt_triplet[2] = CATtriangles_intrmdt[j].GetVertex(2).X;
							Yintrmdt_triplet[2] = CATtriangles_intrmdt[j].GetVertex(2).Y;

							//reset P0 for j'th iteration
							P0[0] = scale_init;
							//P0[1] = rotat_init;//done above in if (compare_fieldvectors)
							P0[2] = crpix1_init;
							P0[3] = crpix2_init;

							//try a fit
							JPMath.Fit_WCSTransform2d(Xintrmdt_triplet, Yintrmdt_triplet, xpix_triplet, ypix_triplet, ref P0, PLB, PUB, psc);

							int N_pt_matches = 0;
							for (int k = 0; k < 3; k++)
							{
								int x = (int)Math.Round((double)IMAGESET[IMAGESETINDEX].Width - 1 - (1 / P0[0] * (Math.Cos(-P0[1]) * Xintrmdt_triplet[k] - Math.Sin(-P0[1]) * Yintrmdt_triplet[k]) + P0[2]));
								int y = (int)Math.Round((double)IMAGESET[IMAGESETINDEX].Height - 1 - (1 / P0[0] * (Math.Sin(-P0[1]) * Xintrmdt_triplet[k] + Math.Cos(-P0[1]) * Yintrmdt_triplet[k]) + P0[3]));
								if (!do_parallel)
									POLYPOINTS2[k] = new System.Drawing.Point((int)((x + 0.5) * xsc), (int)((y + 0.5) * ysc));

								if (x > 0 && y > 0 && x < IMAGESET[IMAGESETINDEX].Width && y < IMAGESET[IMAGESETINDEX].Height && PSESET[PSESETINDEX].SourceIndexMap[x, y] == PSESET[PSESETINDEX].SourceIndexMap[IMAGESET[IMAGESETINDEX].Width - 1 - (int)Math.Round(xpix_triplet[k]), IMAGESET[IMAGESETINDEX].Height - 1 - (int)Math.Round(ypix_triplet[k])])
									N_pt_matches++;
							}
							if (!do_parallel)
								ImageWindow.Refresh();

							if (N_pt_matches != 3)//not a possible solution
							{
								nfalsenegatives_local++;
								continue;
							}

							if (do_parallel)
							{
								for (int k = 0; k < 3; k++)
								{
									double x = (double)IMAGESET[IMAGESETINDEX].Width - 1 - (1 / P0[0] * (Math.Cos(-P0[1]) * Xintrmdt_triplet[k] - Math.Sin(-P0[1]) * Yintrmdt_triplet[k]) + P0[2]);
									double y = (double)IMAGESET[IMAGESETINDEX].Height - 1 - (1 / P0[0] * (Math.Sin(-P0[1]) * Xintrmdt_triplet[k] + Math.Cos(-P0[1]) * Yintrmdt_triplet[k]) + P0[3]);
									POLYPOINTS2[k] = new System.Drawing.Point((int)((x + 0.5) * xsc), (int)((y + 0.5) * ysc));
									POLYPOINTS[k] = new System.Drawing.Point((int)((IMAGESET[IMAGESETINDEX].Width - 1 - xpix_triplet[k] - 0.5) * xsc), (int)((IMAGESET[IMAGESETINDEX].Height - 1 - ypix_triplet[k] - 0.5) * ysc));
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

								int x_pix = (int)Math.Round((double)IMAGESET[IMAGESETINDEX].Width - 1 - (1 / P0[0] * (Math.Cos(-P0[1]) * x_int - Math.Sin(-P0[1]) * y_int) + P0[2]));
								int y_pix = (int)Math.Round((double)IMAGESET[IMAGESETINDEX].Height - 1 - (1 / P0[0] * (Math.Sin(-P0[1]) * x_int + Math.Cos(-P0[1]) * y_int) + P0[3]));

								if (x_pix > 0 && y_pix > 0 && x_pix < IMAGESET[IMAGESETINDEX].Width && y_pix < IMAGESET[IMAGESETINDEX].Height && PSESET[PSESETINDEX].SourceBooleanMap[x_pix, y_pix])
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
								threadnum = i / thrgrpsz;
							}
							else
								nfalsepositiveslocal++;
						}
					}
					lock (locker)
					{
						similartriangles += similartriangleslocal;
						ncompares += ncompareslocal;
						nfalsepositives += nfalsepositiveslocal;
						nfalsenegatives += nfalsenegatives_local;
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

					int x_pix = (int)Math.Round((double)IMAGESET[IMAGESETINDEX].Width - 1 - (1 / p00 * (Math.Cos(-p01) * x_intrmdt - Math.Sin(-p01) * y_intrmdt) + p02));
					int y_pix = (int)Math.Round((double)IMAGESET[IMAGESETINDEX].Height - 1 - (1 / p00 * (Math.Sin(-p01) * x_intrmdt + Math.Cos(-p01) * y_intrmdt) + p03));

					if (x_pix > 0 && y_pix > 0 && x_pix < IMAGESET[IMAGESETINDEX].Width && y_pix < IMAGESET[IMAGESETINDEX].Height && PSESET[PSESETINDEX].SourceBooleanMap[x_pix, y_pix])
					{
						int index = PSESET[PSESETINDEX].SourceIndexMap[x_pix, y_pix];
						xpix_matches[c] = PSESET[PSESETINDEX].Centroids_X[index];
						ypix_matches[c] = PSESET[PSESETINDEX].Centroids_Y[index];
						WCS_RA[c] = CATpts[k].X;
						WCS_DEC[c] = CATpts[k].Y;
						MARKCOORDS[0, c] = x_pix;
						MARKCOORDS[1, c] = y_pix;
						c++;
					}
				}

				MAKEMARKCOORDRECTS();
				PSESET[PSESETINDEX] = new JPFITS.PointSourceExtractor(IMAGESET[IMAGESETINDEX].Image, xpix_matches, ypix_matches, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);
				WCSSolveList.PerformClick();

				string initsolmess = "Scale: " + Math.Round(p00 * 180 / Math.PI * 3600, 4) + ";\r";
				initsolmess += "Rotation: " + Math.Round(p01 * 180 / Math.PI, 3) + ";\r";
				initsolmess += "N Pt. Matches: " + total_pt_matches + " (" + (total_pt_matches * 100 / CATpts_intrmdt.Length).ToString("00.0") + "%)" + ";\r";
				initsolmess += "N_Comparisons: " + ncompares.ToString("0.00e00") + " (" + Math.Round((double)(ncompares * 100) / (double)(PSEtriangles.Length) / (double)(CATtriangles_intrmdt.Length), 1) + "%)" + ";\r";
				initsolmess += "Similar Triangles: " + similartriangles.ToString() + ";\r";
				initsolmess += "N_False Negatives: " + nfalsenegatives + ";\r";
				initsolmess += "N_False Positives: " + nfalsepositives + ";\r";
				initsolmess += "Thread: " + threadnum + ";\r";
				initsolmess += "Completed in: " + ts.Minutes.ToString() + "m" + ((double)(ts.Seconds) + (double)ts.Milliseconds / 1000).ToString() + "s" + ";\r";
				initsolmess += "Comparison per Second: " + (ncompares / ts.TotalSeconds).ToString("0.00e00") + ";\r\r";
				if (WCSAutoRefineChck.Checked)
					initsolmess += "Continue with Refining the Solution?";
				else
					initsolmess += "Clear Solution Points?";

				DialogResult res = MessageBox.Show(initsolmess, "Finished...", MessageBoxButtons.YesNo);

				if (!WCSAutoRefineChck.Checked)
					if (res == DialogResult.Yes)
					{
						PSESET.Clear();
						POLYPOINTS = null;
						POLYPOINTS2 = null;
						MARKCOORDRECTS = null;
						PSEDrop.Items.Clear();
						PSEDrop.Enabled = false;
						PSESPLOTALL = false;
						PSESPLOTNONE = false;
						ImageWindow.Refresh();
						SubImageWindow.Refresh();
						return;
					}
					else
						return;

				POLYPOINTS = null;
				POLYPOINTS2 = null;				

				if (res == DialogResult.No)
				{
					PSEDrop.Items.Clear();
					PSEDrop.Enabled = false;
					PSESPLOTALL = false;
					PSESPLOTNONE = false;
					MARKCOORDRECTS = null;
					PSESET.Clear();
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
					return;
				}

				PSESET.Clear();
				PSESET.Add(new JPFITS.PointSourceExtractor());
				PSESETINDEX = 0;
				ImageWindow.Refresh();
				SubImageWindow.Refresh();
				
				nCATpts = Convert.ToInt32(WCSAutoRefineNPtsTxt.Text);
				WCSLoadListNPtsTxt.Text = nCATpts.ToString();
				niters = 0;
				while (niters <= maxiters)
				{
					niters++;

					PSESET[PSESETINDEX].Extract_Sources(IMAGESET[IMAGESETINDEX].Image, pix_sat, pixthresh, Double.MaxValue, 0, Double.MaxValue, false, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, PSEAutoBackgroundChck.Checked, "", ROI_REGION, false, IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5, false, PSEBackgroundSeparationRadiusLabel.Text.Contains("Src"));
					ImageWindow.Refresh();
					SubImageWindow.Refresh();

					if (PSESET[PSESETINDEX].N_Sources >= nCATpts)
						break;

					div *= 2;
					pixthresh = imamp / div + immed;
				}
				if (PSESET[PSESETINDEX].N_Sources > nCATpts)
				{
					PSESET[PSESETINDEX].ClipToNBrightest(nCATpts);
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
				}
				WCSLoadSimbadAscii_Click(sender, e);
				WCSClarifyListSources.PerformClick();
				//WCS_INIT = new WorldCoordinateSolution(IMAGESET[FILELISTINDEX].WCS.GetCDELTn(1), IMAGESET[FILELISTINDEX].WCS.GetCRPIXn(1), IMAGESET[FILELISTINDEX].WCS.GetCRPIXn(2), false, IMAGESET[FILELISTINDEX].WCS.GetCRVALn(1), IMAGESET[FILELISTINDEX].WCS.GetCRVALn(2), IMAGESET[FILELISTINDEX].WCS.GetCROTAn(1));
				WCSSolveList.PerformClick();

				if (MessageBox.Show(PSESET[PSESETINDEX].N_Sources + " sources of " + WCSAutoRefineNPtsTxt.Text + " were able to be used for WCS refinement. \r\n\r\nClear Solution points?", "Finished...", MessageBoxButtons.YesNo) == DialogResult.Yes)
				{
					PSEDrop.Items.Clear();
					PSEDrop.Enabled = false;
					PSESPLOTALL = false;
					PSESPLOTNONE = false;
					PSESET.Clear();
					POLYPOINTS = null;
					POLYPOINTS2 = null;
					MARKCOORDRECTS = null;
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
					return;
				}

				ImageWindow.Refresh();
				SubImageWindow.Refresh();
			}
			catch (Exception ee)
			{
				MessageBox.Show(ee.Data + "	" + ee.InnerException + "	" + ee.Message + "	" + ee.Source + "	" + ee.StackTrace + "	" + ee.TargetSite);
			}
		}

		private void WCSAutoBGWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			ProgressBar.Value = e.ProgressPercentage;
		}

		private void WCSAutoBGWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WCSAutoSolveBtn.Text = "Solve";
			ProgressBar.Value = 0;

			if (IMAGESET[IMAGESETINDEX].WCS.Exists())
				if (AutoDeRotateOnWCSChck.Checked)
					if (IMAGESET[IMAGESETINDEX].Header.GetKeyValue("INSTRUME").Trim() == "UVIT")
						UVITDeRotateViaWCSBtn_Click(sender, new EventArgs());
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

		private void WCSAutoScaleInitTxt_Enter(object sender, System.EventArgs e)
		{
			NUMERIC_TEXTBOX_ENTER((ToolStripTextBox)sender);
		}

		private void WCSAutoScaleInitTxt_TextChanged(object sender, System.EventArgs e)
		{
			CHECKTEXTBOXTONUM((ToolStripTextBox)sender);
		}

		private void WCSAstraCartaBtn_DropDownOpening(object sender, EventArgs e)
		{
			WCSAstraCartaCVAL1Txt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAstraCartaCVAL1Txt");
			WCSAstraCartaCVAL2Txt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAstraCartaCVAL2Txt");
			WCSAstraCartaBufferTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAstraCartaBufferTxt");
			WCSAstraCartaSaveFileChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySaveFileChck"));
			WCSAstraCartaSquareRegionChck.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSQuerySquareRegion");
			WCSAstraCartaSolveAfter.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySolveAfter"));
			WCSAstraCartaSaveFileChooseDirBtn.Enabled = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtn"));
			WCSAstraCartaSaveFileChooseDirBtn.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtnChck"));
			WCSAstraCartaLimitLLengthDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "WCSAstroQueryLimitLLength"));
			WCSAstraCartaFilterDrop.SelectedIndex = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "WCSAstroQueryFilterDrop"));
			WCSAstraCartaImageShowChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "AstraCartaImageShowChck"));
			WCSAstraCartaForceNew.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "AstraCartaForceNew"));
			WCSAstraCartaPMEpochTxt.Text = (string)REG.GetReg("CCDLAB", "WCSAstraCartaPMEpochTxt");
			WCSAstraCartaCatalogueNameDrop.SelectedIndex = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "AstroQueryCatalogueNameDrop"));
		}

		private void AutoWCSMenuItem_DropDownOpening(object sender, System.EventArgs e)
		{
			WCSAutoScaleInitTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoScaleInitTxt");
			WCSAutoScaleInitLBTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoScaleInitLBTxt");
			WCSAutoScaleInitUBTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoScaleInitUBTxt");
			WCSAutoRotationInitTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoRotationInitTxt");
			WCSAutoRotationInitLBTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoRotationInitLBTxt");
			WCSAutoRotationInitUBTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoRotationInitUBTxt");
			WCSAutoVertexToleranceTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoVertexToleranceTxt");
			WCSAutoNCatPtsTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoNCatPtsTxt");
			WCSAutoDisplayChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSAutoDisplayChck"));
			WCSAutoCatalogueTxt.Tag = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueTxt");
			WCSAutoCatalogueTxt.Text = ((string)WCSAutoCatalogueTxt.Tag).Substring(((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.ToolTipText = ((string)WCSAutoCatalogueTxt.Tag).Substring(0, ((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.BackColor = Color.Gainsboro;
			WCSAutoCatalogueCVAL1Txt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueCVAL1Txt");
			WCSAutoCatalogueCVAL2Txt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueCVAL2Txt");
			WCSAutoCatalogueExtensionTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt");
			WCSAutoCatalogueMagTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoCatalogueMagTxt");
			WCSAutoRefineChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSAutoRefineChck"));
			WCSAutoRefineNPtsTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoRefineNPtsTxt");
			WCSAutoStopNMatchesText.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoStopNMatchesText");
			WCSAutoStopPercMatchesText.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSAutoStopPercMatchesText");
			WCSAutoConditionArraysChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "WCSAutoConditionArrays"));
			WCSLoadListNPtsTxt.Text = (string)JPFITS.REG.GetReg("CCDLAB", "WCSLoadListNPtsTxt");

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

		private void WCSMenu_DropDownOpening(object sender, EventArgs e)
		{
			WCSOptionsVerboseChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "WCSOptionsVerboseChck"));			
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

		private void WCSAutoCatalogueCVAL1Txt_Click(object sender, System.EventArgs e)
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

			WCSAutoCatalogueCVAL1Txt.Text = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL1Txt", WCSAutoCatalogueCVAL1Txt.Text);

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
		}

		private void WCSAutoCatalogueCVAL2Txt_Click(object sender, System.EventArgs e)
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

			WCSAutoCatalogueCVAL2Txt.Text = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL2Txt", WCSAutoCatalogueCVAL2Txt.Text);

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
		}

		private void WCSAutoCatalogueMagTxt_Click(object sender, System.EventArgs e)
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

			WCSAutoCatalogueMagTxt.Text = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueMagTxt", WCSAutoCatalogueMagTxt.Text);

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAutoCatalogueMenuBtn.DropDown.AutoClose = true;
		}

		private void WCSAstraCartaCVAL1_Click(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.DropDown.AutoClose = false;
			AutoWCSMenuItem.DropDown.AutoClose = false;
			WCSAstraCartaBtn.DropDown.AutoClose = false;

			WCSAutoCVALList list = new WCSAutoCVALList(IMAGESET[IMAGESETINDEX].Header.GetAllKeyNames());
			list.Text = "Select the CVALn";
			list.TopMost = true;
			list.ShowDialog();

			if (list.DialogResult == DialogResult.Cancel)
			{
				WCSMenu.DropDown.AutoClose = true;
				AutoWCSMenuItem.DropDown.AutoClose = true;
				WCSAstraCartaBtn.DropDown.AutoClose = true;
				return;
			}

			string hkey = ((string)list.WCDrop.SelectedItem).Trim();
			JPFITS.REG.SetReg("CCDLAB", ((ToolStripTextBox)sender).Name, hkey);
			((ToolStripTextBox)sender).Text = hkey;

			WCSMenu.DropDown.AutoClose = true;
			AutoWCSMenuItem.DropDown.AutoClose = true;
			WCSAstraCartaBtn.DropDown.AutoClose = true;
		}

		private void WCSAstraCartaBtn_DoubleClick(object sender, System.EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			WCSMenu.HideDropDown();
			AutoWCSMenuItem.HideDropDown();
			WCSAstraCartaBtn.HideDropDown();

			if (IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(WCSAstraCartaCVAL1Txt.Text, false) == -1 || IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(WCSAstraCartaCVAL2Txt.Text, false) == -1)
			{
				MessageBox.Show(string.Format("The CVAL1 '{0}' or CVAL2 '{1}' terms don't exist in the header.", WCSAstraCartaCVAL1Txt.Text, WCSAstraCartaCVAL2Txt.Text), "Error");
				return;
			}

			string cval1 = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(WCSAstraCartaCVAL1Txt.Text);
			string cval2 = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(WCSAstraCartaCVAL2Txt.Text);
			double ra = 0, dec = 0;
			try
			{
				ra = Convert.ToDouble(cval1);//value is degree format
				dec = Convert.ToDouble(cval2);
			}
			catch//must be sexagesimal
			{
				WorldCoordinateSolution.SexagesimalElementsToDegreeElements(cval1, cval2, "", out ra, out dec);
			}

			ArrayList keys = new ArrayList();
			if (WCSAstraCartaSquareRegionChck.Text.Contains("Circular"))
			{
				keys.Add("-shape");
				keys.Add("circle");
			}

			double buffer = 0;
			if (WCSAstraCartaBufferTxt.Text != "")
				buffer = Convert.ToDouble(WCSAstraCartaBufferTxt.Text);
			if (buffer != 0)
			{
				keys.Add("-buffer");
				keys.Add(buffer);
			}

			double pmepoch = 0;
			if (WCSAstraCartaPMEpochTxt.Text != "")
			{
				if (JPMath.IsNumeric(WCSAstraCartaPMEpochTxt.Text))
				{
					pmepoch = Convert.ToDouble(WCSAstraCartaPMEpochTxt.Text);
					REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", "");
				}
				else if (JPMath.IsNumeric(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("YEARDATE")))
					pmepoch = Convert.ToDouble(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("YEARDATE"));
			}
			if (pmepoch != 0)
			{
				keys.Add("-pmepoch");
				keys.Add(pmepoch);

				if (!JPMath.IsNumeric(WCSAstraCartaPMEpochTxt.Text))
					REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", WCSAstraCartaPMEpochTxt.Text);
				else
					REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", "");
			}
			else
				REG.SetReg("CCDLAB", "WCSAstraCartaPMEpochTxt", "");

			string outpath = CCDLABPATH_USERAPPDATAROAMING;
			if (WCSAstraCartaSaveFileChck.Checked)
				if (!WCSAstraCartaSaveFileChooseDirBtn.Checked)
					outpath = IMAGESET[IMAGESETINDEX].FilePath;
				else
				{
					FolderBrowserDialog fbd = new FolderBrowserDialog();
					fbd.SelectedPath = IMAGESET[IMAGESETINDEX].FilePath;
					fbd.Description = "Select directory to save catalogue";
					if (fbd.ShowDialog() == DialogResult.Cancel)
						return;
					outpath = fbd.SelectedPath;
				}
			keys.Add("-outdir");
			keys.Add(outpath);

			keys.Add("-nquery");
			keys.Add(Convert.ToInt32(WCSAstraCartaLimitLLengthDrop.SelectedItem.ToString()));

			string catalogue = WCSAstraCartaCatalogueNameDrop.SelectedItem.ToString();
			keys.Add("-catalogue");
			keys.Add(catalogue.Trim());

			string filter = WCSAstraCartaFilterDrop.SelectedItem.ToString();
			keys.Add("-filter");
			keys.Add(filter);

			if (WCSAstraCartaImageShowChck.Checked)
				keys.Add("-imageshow");

			if (WCSAstraCartaForceNew.Checked)
				keys.Add("-forcenew");

			keys.Add("-fitsout");

			keys.Add("-overwrite");

			if (IMAGESET[IMAGESETINDEX].Header.GetKeyValue("OBJECT") != "")
			{
				keys.Add("-outname");
				keys.Add(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("OBJECT"));
			}

			JPFITS.AstraCarta ac = new AstraCarta(ra, dec, Convert.ToDouble(WCSAutoScaleInitTxt.Text), IMAGESET[IMAGESETINDEX].Width, IMAGESET[IMAGESETINDEX].Height, keys);
			ac.CloseOnComplete = true;
			ac.ExecuteOnShow = true;
			ac.ShowDialog();
			string queryfilename = ac.Result_Filename;

			if (queryfilename == "")
				throw new Exception("AstraCarta query returned with no data.");

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();

			WCSAutoCatalogueTxt.Tag = queryfilename;
			WCSAutoCatalogueTxt.Text = ((string)WCSAutoCatalogueTxt.Tag).Substring(((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			WCSAutoCatalogueTxt.ToolTipText = ((string)WCSAutoCatalogueTxt.Tag).Substring(0, ((string)WCSAutoCatalogueTxt.Tag).LastIndexOf("\\") + 1);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCATDir", queryfilename.Substring(0, queryfilename.LastIndexOf("\\")));  
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueTxt", queryfilename);
			WCSAutoCatalogueTxt.BackColor = Color.LightGreen;
			WCSAutoCatalogueExtensionTxt.Text = "GaiaDR3";
			WCSAutoCatalogueCVAL1Txt.Text = "ra";
			WCSAutoCatalogueCVAL2Txt.Text = "dec";
			if (filter == "bp")
				WCSAutoCatalogueMagTxt.Text = "phot_bp_mean_mag";
			else if (filter == "g")
				WCSAutoCatalogueMagTxt.Text = "phot_g_mean_mag";
			else
				WCSAutoCatalogueMagTxt.Text = "phot_rp_mean_mag";

			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL1Txt", WCSAutoCatalogueCVAL1Txt.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueCVAL2Txt", WCSAutoCatalogueCVAL2Txt.Text);
			JPFITS.REG.SetReg("CCDLAB", "WCSAutoCatalogueMagTxt", WCSAutoCatalogueMagTxt.Text);

			if (WCSAstraCartaSolveAfter.Checked)
				WCSAutoSolveBtn.PerformClick();
		}

		private void WCSAstraCartaSaveFileChck_Click(object sender, System.EventArgs e)
		{
			if (WCSAstraCartaSaveFileChck.Checked)
				WCSAstraCartaSaveFileChooseDirBtn.Enabled = true;
			else
				WCSAstraCartaSaveFileChooseDirBtn.Enabled = false;

			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySaveFileChck", WCSAstraCartaSaveFileChck.Checked);
			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtn", WCSAstraCartaSaveFileChooseDirBtn.Enabled);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAstraCartaSaveFileChooseDirBtn_Click(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtnChck", WCSAstraCartaSaveFileChooseDirBtn.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
			WCSAstraCartaSaveFileChck.ShowDropDown();
		}

		private void WCSAstraCartaSquareRegionChck_Click(object sender, System.EventArgs e)
		{
			if (WCSAstraCartaSquareRegionChck.Text.Contains("Square"))
				WCSAstraCartaSquareRegionChck.Text = "Circular Region";
			else
				WCSAstraCartaSquareRegionChck.Text = "Square Region";

			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySquareRegion", WCSAstraCartaSquareRegionChck.Text);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAstraCartaSolveAfter_Click(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "WCSQuerySolveAfter", WCSAstraCartaSolveAfter.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAstraCartaImageShowChck_Click(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "AstraCartaImageShowChck", WCSAstraCartaImageShowChck.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAstraCartaForceNew_Click(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "AstraCartaForceNew", WCSAstraCartaForceNew.Checked);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAstraCartaCatalogueNameDrop_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "AstroQueryCatalogueNameDrop", WCSAstraCartaCatalogueNameDrop.SelectedIndex);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAstraCartaFilterDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "WCSAstroQueryFilterDrop", WCSAstraCartaFilterDrop.SelectedIndex);

			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
			WCSAstraCartaBtn.ShowDropDown();
		}

		private void WCSAutoSolveBtn_MouseEnter(object sender, System.EventArgs e)
		{
			WCSAutoSolveBtn.BackColor = Color.LightGray;
		}

		private void WCSAutoSolveBtn_MouseLeave(object sender, System.EventArgs e)
		{
			WCSAutoSolveBtn.BackColor = System.Drawing.SystemColors.Control;
		}

		private void WCSScaleMenuBtn_Click(object sender, System.EventArgs e)
		{
			WCSMenu.ShowDropDown();
			AutoWCSMenuItem.ShowDropDown();
		}

		private void WCSScaleMenuBtn_DropDownOpening(object sender, System.EventArgs e)
		{
			string wcparamsfile = CCDLABPATH_USERAPPDATAROAMING + "WCSparams.fits";
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

		private void WCSScaleSaveBtn_Click(object sender, System.EventArgs e)
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

			string wcsparamsfile = CCDLABPATH_USERAPPDATAROAMING + "WCSparams.fits";
			string[] entrylabels = new string[6] { "WCSScaleInit", "WCSScaleInitLB", "WCSScaleInitUB", "WCSRotationInit", "WCSRotationInitLB", "WCSRotationInitUB" };
			TypeCode[] types = new TypeCode[6] { TypeCode.Double, TypeCode.Double, TypeCode.Double, TypeCode.Double, TypeCode.Double, TypeCode.Double };
			string[] units = new string[6] { "arcsec per pixel", "arcsec per pixel", "arcsec per pixel", "Degrees", "Degrees", "Degrees" };
			Array[] objarray = new Array[6];
			objarray[0] = new double[1] { Convert.ToDouble(WCSAutoScaleInitTxt.Text) };
			objarray[1] = new double[1] { Convert.ToDouble(WCSAutoScaleInitLBTxt.Text) };
			objarray[2] = new double[1] { Convert.ToDouble(WCSAutoScaleInitUBTxt.Text) };
			objarray[3] = new double[1] { Convert.ToDouble(WCSAutoRotationInitTxt.Text) };
			objarray[4] = new double[1] { Convert.ToDouble(WCSAutoRotationInitLBTxt.Text) };
			objarray[5] = new double[1] { Convert.ToDouble(WCSAutoRotationInitUBTxt.Text) };
			FITSBinTable bt = new FITSBinTable(extname);
			bt.SetTTYPEEntries(entrylabels, units, objarray);
			bt.Write(wcsparamsfile, true);

			AutoWCSScaleMenuBtn.HideDropDown();
			AutoWCSScaleMenuBtn.ShowDropDown();
		}

		private void WCSParamMenuBtn_MouseDown(object sender, MouseEventArgs e)
		{
			string wcsparamsfile = CCDLABPATH_USERAPPDATAROAMING + "WCSparams.fits";

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
				WCSAutoScaleInitTxt.Text = ((double[])bt.GetTTYPEEntry("WCSScaleInit", out _, out _))[0].ToString();
				WCSAutoScaleInitLBTxt.Text = ((double[])bt.GetTTYPEEntry("WCSScaleInitLB", out _, out _))[0].ToString();
				WCSAutoScaleInitUBTxt.Text = ((double[])bt.GetTTYPEEntry("WCSScaleInitUB", out _, out _))[0].ToString();
				WCSAutoRotationInitTxt.Text = ((double[])bt.GetTTYPEEntry("WCSRotationInit", out _, out _))[0].ToString();
				WCSAutoRotationInitLBTxt.Text = ((double[])bt.GetTTYPEEntry("WCSRotationInitLB", out _, out _))[0].ToString();
				WCSAutoRotationInitUBTxt.Text = ((double[])bt.GetTTYPEEntry("WCSRotationInitUB", out _, out _))[0].ToString();
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
			WCS_RA = (double[])bt.GetTTYPEEntry(catCVAL1, out _, out _);
			WCS_DEC = (double[])bt.GetTTYPEEntry(catCVAL2, out _, out _);
			double[] mag = (double[])bt.GetTTYPEEntry(catMag, out _, out _, FITSBinTable.TTYPEReturn.AsDouble);

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

		private void WCSRADecManual_Click(object sender, System.EventArgs e)
		{
			if (!WCSMANUALRAD_CONTINUE && !WCSMANUALRAD)//then start selecting points and set things up
			{
				if (MessageBox.Show("Please begin selecting at least 3 point sources (LEFT-CLICK).  RIGHT-CLICK when done.", "Manual WCS RA & Dec...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					return;

				ROIFIXEDCURSOR = false;//allow cursor box to move
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

				PSESET.Clear();
				PSESET.Add(new JPFITS.PointSourceExtractor());
				PSESETINDEX = 0;
				double[] x = new double[WCS_RA.Length];//centroid (pixels)
				double[] y = new double[WCS_RA.Length];//centroid (pixels)
				for (int i = 0; i < WCS_RA.Length; i++)
				{
					x[i] = (double)MANREGCOORDS[i, 0];
					y[i] = (double)MANREGCOORDS[i, 1];
				}
				PSESET[PSESETINDEX].Extract_Sources(IMAGESET[IMAGESETINDEX].Image, x, y, (double)PSESaturationUpD.Value, (int)PSEKernelRadUpD.Value, (int)PSEBackgroundRadUpD.Value, false, "", IMAGESET[IMAGESETINDEX].Median + IMAGESET[IMAGESETINDEX].Stdv * 2.5);
				x = PSESET[PSESETINDEX].Centroids_X;
				y = PSESET[PSESETINDEX].Centroids_Y;

				IMAGESET[IMAGESETINDEX].WCS.Solve_WCS(WorldCoordinateSolution.WCSType.TAN, x, y, true, WCS_RA, WCS_DEC, IMAGESET[IMAGESETINDEX].Header);
				SHOW_WCSCOORDS = true;
				WCSRADecShowChck.Checked = true;

				if (WCS_RA.Length >= 3)
				{
					float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[IMAGESETINDEX].Width);
					float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[IMAGESETINDEX].Height);
					MARKCOORDRECTS = new Rectangle[(WCS_RA.Length)];
					MARKCOORDS = new double[2, WCS_RA.Length];
					double xpix, ypix;
					for (int i = 0; i < WCS_RA.Length; i++)
					{
						IMAGESET[IMAGESETINDEX].WCS.Get_Pixel(WCS_RA[i], WCS_DEC[i], "TAN", out xpix, out ypix, true);
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
			if (!IMAGESET[IMAGESETINDEX].WCS.Exists())
				if (JPFITS.WorldCoordinateSolution.Exists(IMAGESET[IMAGESETINDEX].Header, new string[] { "RA---TAN" }))
					IMAGESET[IMAGESETINDEX].WCS = new JPFITS.WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);
				else
				{
					MessageBox.Show("No WCS found in current image header...", "Error");
					return;
				}

			for (int i = 0; i < IMAGESET.Count; i++)
			{
				if (i == IMAGESETINDEX)
					continue;
				IMAGESET[IMAGESETINDEX].WCS.CopyTo(IMAGESET[i].Header, WCSOptionsVerboseChck.Checked);
			}
			MessageBox.Show("WCS copied to " + (IMAGESET.Count - 1) + " other headers...", "Success");
		}

		private void WCSCopyFromDiskFile_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "FITS|*.fits;*.fits;*.fit|All Files|*.*";
			ofd.InitialDirectory = IMAGESET[IMAGESETINDEX].FilePath;
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			WorldCoordinateSolution wcs = new WorldCoordinateSolution(new FITSHeader(ofd.FileName));
			if (!wcs.Exists())
			{
				MessageBox.Show("No World Coordinate Solution found in the selected file.", "Error...");
				return;
			}

			wcs.CopyTo(IMAGESET[IMAGESETINDEX].Header, WCSOptionsVerboseChck.Checked);
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
					WorldCoordinateSolution.ClearWCS(IMAGESET[i].Header);
					IMAGESET[i].WCS.ClearWCS();
				}
			}
			else
			{
				WorldCoordinateSolution.ClearWCS(IMAGESET[IMAGESETINDEX].Header);
				IMAGESET[IMAGESETINDEX].WCS.ClearWCS();
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
					IMAGESET[IMAGESETINDEX].WCS.Grid_Refresh();
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

		private void WCSToolsConvertRATxt_TextChanged(object sender, EventArgs e)
		{
			string[] onelinepaste = WCSToolsConvertRATxt.Text.Split(new string[] { ":", " " }, StringSplitOptions.RemoveEmptyEntries);

			if (onelinepaste.Length == 6)
			{
				WCSToolsConvertRATxt.Text = onelinepaste[0] + ":" + onelinepaste[1] + ":" + onelinepaste[2];
				WCSToolsConvertDecTxt.Text = onelinepaste[3] + ":" + onelinepaste[4] + ":" + onelinepaste[5];
			}
		}

		private void WCSToolsAstraCartaBtn_Click(object sender, EventArgs e)
		{
			JPFITS.AstraCarta ac = new AstraCarta();
			ac.CloseOnCompleteChck.Checked = false;
			ac.Show();
		}

		private void WCSEditBinningText_KeyDown(object sender, KeyEventArgs e)
		{
			if (FIRSTLOAD)
				return;

			if (e.KeyCode != Keys.Enter)
				return;

			e.SuppressKeyPress = e.Handled = true;

			if (WorldCoordinateSolution.Exists(IMAGESET[IMAGESETINDEX].Header, new string[2] { "TAN", "TAN" }))
			{
				if (!JPMath.IsNumeric(WCSEditBinningText.Text))
					throw new Exception("Binning factor: '" + WCSEditBinningText.Text + "' is not a number.");
				if (!JPMath.IsInteger(Convert.ToDouble(WCSEditBinningText.Text)))
					throw new Exception("Binning factor: '" + WCSEditBinningText.Text + "' is not an integer.");

				int bin = Convert.ToInt32(WCSEditBinningText.Text.ToString());

				IMAGESET[IMAGESETINDEX].WCS = new WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);
				IMAGESET[IMAGESETINDEX].WCS.Bin(bin, IMAGESET[IMAGESETINDEX].Header);

				FileTxtsUpD();

				MessageBox.Show("Successfuly binned the WCS parameters.", "Success...");
			}
		}

		private void WCSEditCutRegionText_KeyDown(object sender, KeyEventArgs e)
		{
			if (FIRSTLOAD)
				return;

			if (e.KeyCode != Keys.Enter)
				return;

			e.SuppressKeyPress = e.Handled = true;

			if (WorldCoordinateSolution.Exists(IMAGESET[IMAGESETINDEX].Header, new string[2] { "TAN", "TAN" }))
			{
				string[] vals = WCSEditCutRegionText.Text.Split(new string[1] { ";" }, StringSplitOptions.RemoveEmptyEntries);

				if (vals.Length != 2)
					throw new Exception("Cut region values must be formatted as: '#; #', ex: 500; 500. Entered value is: '" + WCSEditCutRegionText.Text + "' and gave " + vals.Length + " possible results.");
				if (!JPMath.IsNumeric(vals[0]))
					throw new Exception("Cut region X-minimun is not a number: '" + vals[0] + "'.");
				if (!JPMath.IsNumeric(vals[1]))
					throw new Exception("Cut region Y-minimun is not a number: '" + vals[1] + "'.");
				if (!JPMath.IsInteger(vals[0]))
					throw new Exception("Cut region X-minimun is not an integer: '" + vals[0] + "'.");
				if (!JPMath.IsInteger(vals[1]))
					throw new Exception("Cut region Y-minimun is not an integer: '" + vals[1] + "'.");

				IMAGESET[IMAGESETINDEX].WCS = new WorldCoordinateSolution(IMAGESET[IMAGESETINDEX].Header);
				IMAGESET[IMAGESETINDEX].WCS.Cut(Convert.ToDouble(vals[0]), Convert.ToDouble(vals[1]), IMAGESET[IMAGESETINDEX].Header);

				FileTxtsUpD();

				MessageBox.Show("Successfuly cut-snipped the WCS parameters to a new region.", "Success...");
			}
		}

		private void WCSOptionsVerboseChck_Click(object sender, EventArgs e)
		{
			WCSMenu.ShowDropDown();
			WCSOptionsMenu.ShowDropDown();

			REG.SetReg("CCDLAB", "WCSOptionsVerboseChck", WCSOptionsVerboseChck.Checked);
		}

		private void WCSOptionsBatch_Click(object sender, EventArgs e)
		{
			WCSMenu.ShowDropDown();
			WCSOptionsMenu.ShowDropDown();
		}

		private void WCSEditBinning_DoubleClick(object sender, EventArgs e)
		{

		}

		private void WCSEditCutRegion_DoubleClick(object sender, EventArgs e)
		{

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