﻿using System;
using System.IO;
using System.Drawing;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using JPFITS;
using MathWorks.MATLAB.NET.Arrays;
using System.Runtime.CompilerServices;
using System.Collections.Concurrent;

namespace CCDLAB
{
	public partial class Form1
	{
		private void Form1_Load(object sender, EventArgs e)
		{
			bool license = Convert.ToBoolean(REG.GetReg("CCDLAB", "LicenseAgree"));
			if (!license)
			{
				/*String^ agree = "This software is distributed under Creative Commons license 'Attribution-NonCommercial-NoDerivatives 4.0 International' (CC BY-NC-ND 4.0).  ";
				agree += "By clicking Yes you agree to the terms of that license agreement.  See:  https://creativecommons.org/licenses/by-nc-nd/4.0/";*/

				string agree = "This software is released under GNU Public General License v 3.0 (GPLv3).  ";
				agree += "By clicking Yes you agree to the terms of that license agreement.  See:  http://www.gnu.org/licenses/";

				DialogResult res = MessageBox.Show(agree, "License Agreement", MessageBoxButtons.YesNo);
				if (res == DialogResult.No)
					Application.Exit();
				else
					REG.SetReg("CCDLAB", "LicenseAgree", true);
			}

			CCDLABPATH_USERAPPDATAROAMING = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Astrowerks", "CCDLAB") + "//";
			if (!Directory.Exists(CCDLABPATH_USERAPPDATAROAMING))
				Directory.CreateDirectory(CCDLABPATH_USERAPPDATAROAMING);

			IMAGESET = new FITSImageSet();

			PSEFitStatsTypeDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "PSEFitStatsTypeDrop"));
			ROIFitStatsTypeDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "ROIFitStatsTypeDrop"));

			ROIX0 = Convert.ToInt32(REG.GetReg("CCDLAB", "ROIX0"));
			ROIY0 = Convert.ToInt32(REG.GetReg("CCDLAB", "ROIY0"));
			ROIXRad = Convert.ToInt32(REG.GetReg("CCDLAB", "ROIXRad"));
			ROIYRad = Convert.ToInt32(REG.GetReg("CCDLAB", "ROIYRad"));

			InfoStatic1.Text = (string)REG.GetReg("CCDLAB", "InfoStatic1");
			InfoStatic2.Text = (string)REG.GetReg("CCDLAB", "InfoStatic2");
			InfoStatic3.Text = (string)REG.GetReg("CCDLAB", "InfoStatic3");
			InfoStatic4.Text = (string)REG.GetReg("CCDLAB", "InfoStatic4");
			InfoStatic5.Text = (string)REG.GetReg("CCDLAB", "InfoStatic5");
			MainTab.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "MainTabIndex"));
			BatchOperationTab.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "BatchOperationTabIndex"));
			StackUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "StackUpDValue"));
			BatchRunningNumUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "RunningUpDValue"));
			RadialPlotMedianBackgroundChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RadialMedianBG"));
			XBinUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "XBinUpD"));
			YBinUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "YBinUpD"));
			BackgroundCountsPixelFrameTxt.Text = (string)REG.GetReg("CCDLAB", "BackgroundCountsPixelFrameTxt");
			/*OptInvertImageView.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB","OPTIMGVIEWINVERTY"));
			OPTIMGVIEWINVERTY = OptInvertImageView.Checked;*/

			PSEPixelMinUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSEPixValMin"));
			PSESaturationUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSEPixSaturation"));
			PSEKernelMinUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSECountValMin"));
			PSEPixelMaxUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSEPixValMax"));
			PSEKernelMaxUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSECountValMax"));
			PSEKernelRadUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSEWidth"));
			PSEBackgroundRadUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "PSEBackgroundRadUpD"));
			PSEAutoBackgroundChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PSEAutoBackgroundChck"));
			SCMUpD.Value = Convert.ToDecimal(REG.GetReg("CCDLAB", "SCMUpD"));

			UVPixelMinThresh.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "UVPixelMinThresh"));
			UVPixelMaxThresh.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "UVPixelMaxThresh"));
			UVShapeMinThresh.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "UVShapeMinThresh"));
			UVShapeMaxThresh.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "UVShapeMaxThresh"));
			StackingDirectoryTxt.Text = (string)REG.GetReg("CCDLAB", "StackingFilesPath");

			ImageFingerSortKeyValueTxt.Text = (string)REG.GetReg("CCDLAB", "ImageFingerSortKeyTxt");

			PSEBackgroundSeparationRadiusLabel.Text = (string)REG.GetReg("CCDLAB", "PSEBackgroundSeparationRadiusLabel");

			UVActiveBGChck.Checked = true;
			UVGeneralRegistrationResolutionDrop.SelectedIndex = 2;
			FindPtsDrop.SelectedIndex = 0;
			ScalarOpStyleDrop.SelectedIndex = 0;
			ReplaceImagePtsDrop.SelectedIndex = 0;
			ContrastScaleDrop.SelectedIndex = 0;
			ColourMapDrop.SelectedIndex = 0;
			Chart1.SendToBack();			

			TBZipCopyChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "TBZipCopyChck"));
			TBZipMoveChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "TBZipMoveChck"));

			SHOWIMGTOOLTIP = Convert.ToBoolean(REG.GetReg("CCDLAB", "ShowImgTooltip"));
			if (SHOWIMGTOOLTIP)
				ImageWndwShowCoordTooltipChck.PerformClick();

			if (Convert.ToBoolean(REG.GetReg("CCDLAB", "DisplayStateMax")) == false)
			{
				OptionsDisplayDefaultNorChck.Checked = true;
				OptionsDisplayDefaultMaxChck.Checked = false;
			}
			else
			{
				OptionsDisplayDefaultNorChck.Checked = false;
				OptionsDisplayDefaultMaxChck.Checked = true;
			}

			WCSPlotResidualScaleTxt.Text = (string)REG.GetReg("CCDLAB", "WCSPlotResidualScaleTxt");
			WCSOptionsVerboseChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "WCSOptionsVerboseChck"));

			OptionsHardDiskPerformanceExtremeChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "OptionsHardDiskPerformanceExtremeChck"));
			OptionsHardDiskPerformanceStandardChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "OptionsHardDiskPerformanceStandardChck"));

			if (ImageWindow.Width > ImageWindow.Height)
			{
				this.Size = new System.Drawing.Size(this.Width - (ImageWindow.Width - ImageWindow.Height), this.Height);
			}
			if (System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height >= 1080 && (SubImageSlideY.Right + SubImagePanel.Width) < (this.Right - 20))
			{
				int diff = this.Right - 20 - SubImageSlideY.Right - SubImagePanel.Width;
				SubImageWindow.Location = new System.Drawing.Point(SubImageWindow.Location.X, SubImageWindow.Location.Y - diff);
				SubImageWindow.Size = new System.Drawing.Size(SubImageWindow.Size.Width + diff, SubImageWindow.Size.Height + diff);

				SubImageSlideX.Location = new System.Drawing.Point(SubImageWindow.Location.X, SubImageWindow.Location.Y - SubImageSlideX.Height);
				SubImageSlideX.Width = SubImageWindow.Width;

				SubImageSlideY.Location = new System.Drawing.Point(SubImageWindow.Right, SubImageWindow.Location.Y);
				SubImageSlideY.Height = SubImageWindow.Height;

				SubImagePanel.Location = new System.Drawing.Point(SubImageSlideY.Right + 10, SubImageWindow.Location.Y);
			}
			if (OptionsDisplayDefaultNorChck.Checked == true)
				this.WindowState = FormWindowState.Normal;
			else
				this.WindowState = FormWindowState.Maximized;

			if (AUTOLOADIMAGESFILES.Length >= 1)
			{
				int ind = AUTOLOADIMAGESFILES[0].LastIndexOf("\\");
				string dir = AUTOLOADIMAGESFILES[0].Substring(0, ind);
				REG.SetReg("CCDLAB", "OpenFilesPath", dir);

				AddToImageSet(AUTOLOADIMAGESFILES, true);
				AUTOLOADIMAGESFILES = new string[0];
			}

			try
			{
				RecentFilesUpD();
			}
			catch
			{
				string[] files = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
				for (int i = 0; i < files.Length; i++)
					File.Delete(files[i]);
				RecentFilesUpD();
			}
		}

		private void Form1_Resize(object sender, EventArgs e)
		{
			if (IMAGESET != null && IMAGESET.Count > 0)
				IMAGESET[IMAGESETINDEX].WCS.Grid_Refresh();
		}

		private void Form1_Shown(object sender, System.EventArgs e)
		{
			//if (ImageWindow.Width > ImageWindow.Height)
			//{
			//	this.Size = new System.Drawing.Size(this.Width - (ImageWindow.Width - ImageWindow.Height), this.Height);
			//}

			//if (System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height >= 1080 && (SubImageSlideY.Right + SubImagePanel.Width) < (this.Right - 20))
			//{
			//	int diff = this.Right - 20 - SubImageSlideY.Right - SubImagePanel.Width;
			//	SubImageWindow.Location = new System.Drawing.Point(SubImageWindow.Location.X, SubImageWindow.Location.Y - diff);
			//	SubImageWindow.Size = new System.Drawing.Size(SubImageWindow.Size.Width + diff, SubImageWindow.Size.Height + diff);

			//	SubImageSlideX.Location = new System.Drawing.Point(SubImageWindow.Location.X, SubImageWindow.Location.Y - SubImageSlideX.Height);
			//	SubImageSlideX.Width = SubImageWindow.Width;

			//	SubImageSlideY.Location = new System.Drawing.Point(SubImageWindow.Right, SubImageWindow.Location.Y);
			//	SubImageSlideY.Height = SubImageWindow.Height;

			//	SubImagePanel.Location = new System.Drawing.Point(SubImageSlideY.Right + 10, SubImageWindow.Location.Y);
			//}

			//if (OptionsDisplayDefaultNorChck.Checked == true)
			//	this.WindowState = FormWindowState.Normal;
			//else
			//	this.WindowState = FormWindowState.Maximized;
		}

		private void Form1_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyValue == 39)//right arrow
			{
				ViewNextBtn.PerformClick();
			}

			if (e.Modifiers == (Keys.Alt | Keys.Control))
				if (e.KeyCode == Keys.U)
					if (UVITMenu.Visible == false)
					{
						MainTab.TabPages.Add(UVITTab);
						UVITMenu.Visible = true;
					}
					else
					{
						MainTab.TabPages.Remove(UVITTab);
						UVITMenu.Visible = false;
					}
		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e)
		{
			if (IMAGESET != null && IMAGESET.Count > 0)
			{
				REG.SetReg("CCDLAB", "LastImageWidth", IMAGESET[IMAGESETINDEX].Width.ToString());
				REG.SetReg("CCDLAB", "LastImageHeight", IMAGESET[IMAGESETINDEX].Height.ToString());
				REG.SetReg("CCDLAB", "SubImageHWX", HalfWidthXUpD.Value.ToString());
				REG.SetReg("CCDLAB", "SubImageHWY", HalfWidthYUpD.Value.ToString());
				REG.SetReg("CCDLAB", "SubImageSlideX", SubImageSlideX.Value.ToString());
				REG.SetReg("CCDLAB", "SubImageSlideY", SubImageSlideY.Value.ToString());
			}

			File.Delete(CCDLABPATH_USERAPPDATAROAMING + "ccdlabfoundfilelist.CFL");
		}

		private void OptionsHardDiskPerformanceExtremeChck_Click(object sender, EventArgs e)
		{
			OptionsHardDiskPerformanceExtremeChck.Checked = true;
			OptionsHardDiskPerformanceStandardChck.Checked = false;

			OptsMenu.ShowDropDown();
			OptionsHardDiskPerformanceMenu.ShowDropDown();
			REG.SetReg("CCDLAB", "OptionsHardDiskPerformanceExtremeChck", true);
			REG.SetReg("CCDLAB", "OptionsHardDiskPerformanceStandardChck", false);
		}

		private void OptionsHardDiskPerformanceStandardChck_Click(object sender, EventArgs e)
		{
			OptionsHardDiskPerformanceExtremeChck.Checked = false;
			OptionsHardDiskPerformanceStandardChck.Checked = true;

			OptsMenu.ShowDropDown();
			OptionsHardDiskPerformanceMenu.ShowDropDown();
			REG.SetReg("CCDLAB", "OptionsHardDiskPerformanceStandardChck", true);
			REG.SetReg("CCDLAB", "OptionsHardDiskPerformanceExtremeChck", false);
		}

		private void EditMenuRGBColorImageCreatorBtn_Click(object sender, EventArgs e)
		{
			if (IMAGESET == null || IMAGESET.Count != 3)
			{
				MessageBox.Show("Requires three images to be loaded in order of red-green-blue channels.", "Error...");
				return;
			}

			ColorImageCreator cic = new ColorImageCreator(this);
			cic.Show();
		}

		private void TBZipMoveChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "TBZipMoveChck", TBZipMoveChck.Checked);

			if (TBZipMoveChck.Checked)
			{
				TBZipCopyChck.Checked = false;
				REG.SetReg("CCDLAB", "TBZipCopyChck", TBZipCopyChck.Checked);
			}
			if (!TBZipMoveChck.Checked)
				TBZipMoveChck.Checked = true;

			TBZipAllBtn.ShowDropDown();
		}

		private void TBZipCopyChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "TBZipCopyChck", TBZipCopyChck.Checked);

			if (TBZipCopyChck.Checked)
			{
				TBZipMoveChck.Checked = false;
				REG.SetReg("CCDLAB", "TBZipMoveChck", TBZipMoveChck.Checked);
			}
			if (!TBZipCopyChck.Checked)
				TBZipCopyChck.Checked = true;

			TBZipAllBtn.ShowDropDown();
		}

		private void NUMERIC_TEXTBOX_TextChanged(object sender, EventArgs e)
		{
			CHECKTEXTBOXTONUM((ToolStripTextBox)sender);
		}

		private void NUMERIC_TEXTBOX_MouseEnter(object sender, EventArgs e)
		{
			NUMERIC_TEXTBOX_ENTER((ToolStripTextBox)sender);
		}

		private void NUMERIC_TEXTBOX_ENTER(ToolStripTextBox textbox)
		{
			LASTTEXT = textbox.Text;
		}

		private void CHECKTEXTBOXTONUM(ToolStripTextBox textbox)
		{
			if (textbox.Text == "-" || textbox.Text == "-." || textbox.Text == "." || textbox.Text == "+" || textbox.Text == "+." || textbox.Text == "")
				return;

			if (textbox.Text.Length > 0)
				if (textbox.Text.Substring(textbox.Text.Length - 1).ToLower() == "e")
					return;
			if (textbox.Text.Length > 1)
				if (textbox.Text.Substring(textbox.Text.Length - 2).ToLower() == "e+" || textbox.Text.Substring(textbox.Text.Length - 2).ToLower() == "e-")
					return;
			try
			{
				Convert.ToDouble(textbox.Text);
			}
			catch
			{
				textbox.Text = LASTTEXT;
			}

			LASTTEXT = textbox.Text;
			REG.SetReg("CCDLAB", textbox.Name, textbox.Text);

			//MessageBox.Show(textbox.Name + "  " + textbox.Text);
		}

		private void OptInvertImageView_Click(object sender, EventArgs e)
		{
			/*REG.SetReg("CCDLAB","OPTIMGVIEWINVERTY",OptInvertImageView.Checked.ToString());
			OPTIMGVIEWINVERTY = OptInvertImageView.Checked;
			IMAGEBMP.RotateFlip(.Drawing.RotateFlipType.RotateNoneFlipY);
			ImageWindow.Refresh();*/
		}

		private void OptViewImage_Click(object sender, EventArgs e)
		{
			if (OptViewImage.Checked == false && OptViewSpectrum.Checked == false)
			{
				OptViewImage.Checked = true;
				ViewImageTog.Checked = true;
			}

			OptViewSpectrum.Checked = false;
			ViewSpectrumTog.Checked = false;

			Chart1.SendToBack();
			Chart1.Visible = false;

			ImageWindow.BringToFront();
			ImageWindow.Visible = true;
		}

		private void OptViewSpectrum_Click(object sender, EventArgs e)
		{
			if (IMAGESET[IMAGESETINDEX].Height > 512)
				if (MessageBox.Show("Plotting more than 512 lines can slow performance, are you sure?", "Warning...", MessageBoxButtons.YesNo) == DialogResult.No)
					return;

			if (IMAGESET[IMAGESETINDEX].Width == 1)
			{
				MessageBox.Show("Plot vector has unit width...can't plot.", "Error...", MessageBoxButtons.YesNo);
				return;
			}

			if (OptViewImage.Checked == false && OptViewSpectrum.Checked == false)
			{
				OptViewSpectrum.Checked = true;
				ViewSpectrumTog.Checked = true;
			}

			OptViewImage.Checked = false;
			ViewImageTog.Checked = false;

			ImageWindow.SendToBack();
			ImageWindow.Visible = false;

			Chart1.BringToFront();
			Chart1.Visible = true;

			SpAxesUpD();
		}

		private void ViewImageTog_Click(object sender, EventArgs e)
		{
			OptViewImage_Click(sender, e);
		}

		private void ViewSpectrumTog_Click(object sender, EventArgs e)
		{
			OptViewSpectrum_Click(sender, e);
		}

		private void HalfWidthXUpD_ValueChanged(object sender, EventArgs e)
		{
			if (FIRSTLOAD)
				return;

			SubImageSizeTxt.Text = "Size: " + ((int)HalfWidthXUpD.Value * 2 + 1).ToString() + " x " + ((int)HalfWidthYUpD.Value * 2 + 1).ToString();

			if (HalfWidthXUpD.Tag.ToString().Equals("YUpD"))
			{
				HalfWidthXUpD.Tag = "";
				return;
			}

			if (EqualHWChck.Checked)
			{
				HalfWidthYUpD.Tag = "XUpD";
				HalfWidthYUpD.Value = HalfWidthXUpD.Value;
			}			

			SubImageStatsUpD();
			SubImageUpD();
			ImageWindow.Refresh();

			if (ImageWndwCntxtPlotRow.Checked && ImageWndwCntxtPlotRowSubOnly.Checked)
				ROWplotUpD(false);

			if (PLOTRADIALLINE)
				RADIALLINE_PLOTUpD();
		}

		private void HalfWidthYUpD_ValueChanged(object sender, EventArgs e)
		{
			if (FIRSTLOAD)
				return;

			SubImageSizeTxt.Text = "Size: " + ((int)HalfWidthXUpD.Value * 2 + 1).ToString() + " x " + ((int)HalfWidthYUpD.Value * 2 + 1).ToString();

			if (HalfWidthYUpD.Tag.ToString().Equals("XUpD"))
			{
				if (ImageWndwCntxtPlotCol.Checked && ImageWndwCntxtPlotColSubOnly.Checked)
					COLplotUpD(false);

				HalfWidthYUpD.Tag = "";
				return;
			}

			if (EqualHWChck.Checked)
			{
				HalfWidthXUpD.Tag = "YUpD";
				HalfWidthXUpD.Value = HalfWidthYUpD.Value;
			}

			SubImageStatsUpD();
			SubImageUpD();
			ImageWindow.Refresh();

			if (ImageWndwCntxtPlotCol.Checked && ImageWndwCntxtPlotColSubOnly.Checked)
				COLplotUpD(false);

			if (PLOTRADIALLINE)
				RADIALLINE_PLOTUpD();
		}

		private void EqualHWChck_CheckedChanged(object sender, EventArgs e)
		{
			if (EqualHWChck.Checked)
			{
				int HWx = (int)HalfWidthXUpD.Value;
				int HWy = (int)HalfWidthYUpD.Value;
				int w = Math.Min(HWx, IMAGESET[IMAGESETINDEX].Height);
				int h = Math.Min(HWy, IMAGESET[IMAGESETINDEX].Width);
				if (w < h)
					HalfWidthYUpD.Value = w;
				else if (h < w)
					HalfWidthXUpD.Value = h;
			}
			else
			{
			}
		}

		private void ImageEditBoxSetSubRangeCntxt_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "XStart", XSUBRANGE[0].ToString());
			REG.SetReg("CCDLAB", "XEnd", XSUBRANGE[XSUBRANGE.Length - 1].ToString());
			REG.SetReg("CCDLAB", "YStart", YSUBRANGE[0].ToString());
			REG.SetReg("CCDLAB", "YEnd", YSUBRANGE[YSUBRANGE.Length - 1].ToString());
			MessageBox.Show(String.Concat("XStart = ", XSUBRANGE[0], "; XEnd = ", XSUBRANGE[XSUBRANGE.Length - 1], "; YStart = ", YSUBRANGE[0], "; YEnd = ", YSUBRANGE[YSUBRANGE.Length - 1]), "Image Loading Sub-Ranges Set");
		}

		private void FMViewExtensionTable_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			ofd.Filter = "FITS|*.fits;*.fit;*.fts;|All|*.*";
			ofd.Multiselect = false;
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			string[] list = FITSBinTable.GetAllExtensionNames(ofd.FileName);

			if (list.Length == 0)
			{
				MessageBox.Show("No BINTABLE extensions exist in the file...", "Error");
				return;
			}

			REG.SetReg("CCDLAB", "OpenFilesPath", ofd.FileName.Substring(0, ofd.FileName.LastIndexOf("\\")));

			JPFITS.FitsBinTableViewer btv = new FitsBinTableViewer(ofd.FileName);
			btv.Show();
		}

		private void FMLoadSubFrame_Click(object sender, EventArgs e)
		{
			RangeDlg dlg = new RangeDlg();
			dlg.XStartUpD.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "XStart"));
			dlg.XEndUpD.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "XEnd"));
			dlg.YStartUpD.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "YStart"));
			dlg.YEndUpD.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "YEnd"));
			dlg.ShowDialog();

			if (dlg.DialogResult == DialogResult.OK)
			{
				LOADSUBRANGE = true;
				SUBRANGE[0] = (int)dlg.XStartUpD.Value;
				SUBRANGE[1] = (int)dlg.XEndUpD.Value;
				SUBRANGE[2] = (int)dlg.YStartUpD.Value;
				SUBRANGE[3] = (int)dlg.YEndUpD.Value;
				REG.SetReg("CCDLAB", "XStart", SUBRANGE[0].ToString());
				REG.SetReg("CCDLAB", "XEnd", SUBRANGE[1].ToString());
				REG.SetReg("CCDLAB", "YStart", SUBRANGE[2].ToString());
				REG.SetReg("CCDLAB", "YEnd", SUBRANGE[3].ToString());
				FMLoad_Click(sender, e);
			}
			else
			{
				LOADSUBRANGE = false;
				SUBRANGE[0] = -1;
			}
		}

		private void FMQuit_Click(object sender, EventArgs e)
		{
			DialogResult ans = MessageBox.Show("Are you sure you would like to Exit?", "Program Exit Warning...", MessageBoxButtons.OKCancel);
			if (ans == DialogResult.OK)
				Application.Exit();
		}

		private void FMReload_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to reload the files and discard all/any changes?", "Proceed?", MessageBoxButtons.OKCancel) == DialogResult.OK)
			{
				AUTOLOADIMAGES = true;

				int c = 0;
				for (int i = 0; i < IMAGESET.Count; i++)
					if (File.Exists(IMAGESET[i].FullFileName))
						c++;
				AUTOLOADIMAGESFILES = new string[c];

				c = 0;
				for (int i = 0; i < IMAGESET.Count; i++)
                    if (File.Exists(IMAGESET[i].FullFileName))
                        AUTOLOADIMAGESFILES[c++] = IMAGESET[i].FullFileName;

				IMAGESET = new FITSImageSet();
				FMLoad_Click(sender, e);
			}
		}

		private void SaveFileDialog_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
		{
			string fullfile = SaveFileDlg.FileName;
			int q = fullfile.LastIndexOf("\\");
			string file = fullfile.Substring(q + 1);
			FileListDrop.Items[IMAGESETINDEX] = file;
			string ext = Path.GetExtension(fullfile);

			if (ext == ".fts" || ext == ".fit" || ext == ".fits")
				IMAGESET[IMAGESETINDEX].WriteImage(fullfile, FILESAVEPREC, true);
			if (ext == ".raw")//.raw
				IMAGESET[IMAGESETINDEX].WriteImage(fullfile, DiskPrecision.Int16, true);
			if (ext == ".jpg" || ext == ".jpeg")
			{
				if (IMAGESET[IMAGESETINDEX].Width < 256 || IMAGESET[IMAGESETINDEX].Height < 256)
				{
					Bitmap bmp1 = new Bitmap(ImageWindow.Width, ImageWindow.Height);
					ImageWindow.DrawToBitmap(bmp1, ImageWindow.DisplayRectangle);
					bmp1.Save(fullfile, System.Drawing.Imaging.ImageFormat.Jpeg);
				}
				else
				{
					Bitmap bmp1 = JPBitMap.ArrayToBmp(IMAGESET[IMAGESETINDEX].Image, ContrastScaleDrop.SelectedIndex, ColourMapDrop.SelectedIndex, InvertContrastChck.Checked, DIMCLIM, IMAGESET[IMAGESETINDEX].Width, IMAGESET[IMAGESETINDEX].Height, OPTIMGVIEWINVERTY);
					bmp1.Save(fullfile, System.Drawing.Imaging.ImageFormat.Jpeg);
				}
			}
			if (ext == ".zip")
			{
				string ziplist = CCDLABPATH_USERAPPDATAROAMING + "tozip.txt";
				StreamWriter sw = new StreamWriter(ziplist);
				sw.WriteLine(IMAGESET[IMAGESETINDEX].FullFileName);
				sw.Close();

				Process p = new Process();
				p.StartInfo.FileName = "c:\\Program Files\\7-Zip\\7z.exe";
				p.StartInfo.Arguments = "\"a\" " + "\"-tzip\" " + "\"" + fullfile + "\" " + "\"@" + ziplist;
				p.Start();
				p.WaitForExit();
				if (p.ExitCode != 0)
				{
					File.Delete(fullfile);
					return;
				}
			}

			REG.SetReg("CCDLAB", "SaveFileDlgIndex", SaveFileDlg.FilterIndex.ToString());
		}

		private void ViewNextBtn_Click(object sender, EventArgs e)
		{
			int i = IMAGESETINDEX;
			if (i == FileListDrop.Items.Count - 1)
				i = 0;
			else
				i++;
			FileListDrop.SelectedIndex = i;			
		}

		private void ViewLastbtn_Click(object sender, EventArgs e)
		{
			int i = IMAGESETINDEX;
			if (i == 0)
				i = FileListDrop.Items.Count - 1;
			else
				i--;
			FileListDrop.SelectedIndex = i;
		}		

		private void ContrastScaleDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			int width = IMAGESET[IMAGESETINDEX].Width;
			int height = IMAGESET[IMAGESETINDEX].Height;
			SubImageSlideX.Maximum = width;
			SubImageSlideY.Maximum = height;			
			FileTxtsUpD();
			StatTxtsUpD();
			SubImageStatsUpD();
			SubImageUpD();
			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
		}

		private void FMSave_Click(object sender, EventArgs e)
		{
			SaveFileDlg.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			SaveFileDlg.FilterIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "SaveFileDlgIndex"));
			SaveFileDlg.ShowDialog();
		}

		private void InvertContrastChck_CheckedChanged(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			int width = IMAGESET[IMAGESETINDEX].Width;
			int height = IMAGESET[IMAGESETINDEX].Height;
			SubImageSlideX.Maximum = width;
			SubImageSlideY.Maximum = height;			
			FileTxtsUpD();
			StatTxtsUpD();
			SubImageStatsUpD();
			SubImageUpD();
			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
		}

		private void ScaleContrastChck_CheckedChanged(object sender, EventArgs e)
		{
			if (IMAGESET.Count == 0)
				return;

			SubImageStatsUpD();
			SubImageUpD();
		}

		private void TBSaveBatch_Click(object sender, EventArgs e)
		{
			JPFITS.FITSImageSetSaver fiss = new JPFITS.FITSImageSetSaver(IMAGESET);
			fiss.ShowDialog();
		}

		private void TBZipAllBtn_Click(object sender, EventArgs e)
		{
			JPFITS.FITSImageSetSaver fiss = new JPFITS.FITSImageSetSaver(IMAGESET);
			fiss.FileExtension.SelectedIndex = 4;
			fiss.ZipInOneChck.Checked = true;
			fiss.ZipContextCopyChck.Checked = TBZipCopyChck.Checked;
			fiss.ZipContextMoveChck.Checked = TBZipMoveChck.Checked;
			fiss.ShowDialog();
		}

		private void RelativeContrast_CheckedChanged(object sender, EventArgs e)
		{
		}

		private void FMFind_Click(object sender, EventArgs e)
		{
			FindFiles();
		}

		private void FMViewFound_Click(object sender, EventArgs e)
		{
			ViewFoundList();
		}

		private void HeaderKeyTxt_KeyDown(object sender, KeyEventArgs e)
		{
			ListBox headerlistbox = (ListBox)sender;

			if (e.Control && e.KeyCode == Keys.C)//copy
			{
				e.SuppressKeyPress = true;

				string str = "";
				CLIPBRDHEADERKEYS = new string[headerlistbox.SelectedIndices.Count];
				CLIPBRDHEADERVALS = new string[headerlistbox.SelectedIndices.Count];
				CLIPBRDHEADERCOMS = new string[headerlistbox.SelectedIndices.Count];
				CLIPBRDHEADERINDS = new int[headerlistbox.SelectedIndices.Count];

				for (int i = 0; i < HeaderTxt.SelectedIndices.Count; i++)
				{
					str += IMAGESET[IMAGESETINDEX].Header[headerlistbox.SelectedIndices[i]].GetFullyFomattedFITSLine() + "\r\n";
					CLIPBRDHEADERKEYS[i] = IMAGESET[IMAGESETINDEX].Header.GetKeyName(headerlistbox.SelectedIndices[i]);
					CLIPBRDHEADERVALS[i] = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(headerlistbox.SelectedIndices[i]);
					CLIPBRDHEADERCOMS[i] = IMAGESET[IMAGESETINDEX].Header.GetKeyComment(headerlistbox.SelectedIndices[i]);
					CLIPBRDHEADERINDS[i] = headerlistbox.SelectedIndices[i];
				}

				Clipboard.SetText(str);
			}

			if (e.Control && e.KeyCode == Keys.V)//paste
			{
				e.SuppressKeyPress = true;

				for (int i = 0; i < CLIPBRDHEADERKEYS.Length; i++)
				{
					//first check to see if the key exists
					int ind = IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(CLIPBRDHEADERKEYS[i], false);
					//if it does then set the key
					if (ind != -1)
					{
						IMAGESET[IMAGESETINDEX].Header.SetKey(CLIPBRDHEADERKEYS[i], CLIPBRDHEADERVALS[i], CLIPBRDHEADERCOMS[i], false, 0);
						CLIPBRDHEADERINDS[i] = ind;
					}
					else
					{
						IMAGESET[IMAGESETINDEX].Header.AddKey(CLIPBRDHEADERKEYS[i], CLIPBRDHEADERVALS[i], CLIPBRDHEADERCOMS[i], CLIPBRDHEADERINDS[i]);
						CLIPBRDHEADERINDS[i] = IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(CLIPBRDHEADERKEYS[i], CLIPBRDHEADERVALS[i], CLIPBRDHEADERCOMS[i]);
					}
				}

				FileTxtsUpD();
				HeaderTxt.SelectedIndices.Clear();

				for (int i = 0; i < CLIPBRDHEADERKEYS.Length; i++)
					HeaderTxt.SelectedIndex = CLIPBRDHEADERINDS[i];
			}

			if (e.Control && e.KeyCode == Keys.A)//select all
			{
				e.SuppressKeyPress = true;

				for (int i = 0; i < HeaderTxt.Items.Count; i++)
					HeaderTxt.SelectedIndex = i;
			}

			if (e.KeyCode == Keys.Delete)
			{
				e.SuppressKeyPress = true;

				int ind0 = headerlistbox.SelectedIndices[0];

				for (int i = headerlistbox.SelectedIndices.Count - 1; i >= 0; i--)
				{
					if (!FITSHeader.ValidKeyEdit(IMAGESET[IMAGESETINDEX].Header.GetKeyName(headerlistbox.SelectedIndices[i]), false))
					{
						if (MessageBox.Show("Sorry, but this is a Restricted Key! You don't have access.", "FITS Restriction: " + IMAGESET[IMAGESETINDEX].Header.GetKeyName(headerlistbox.SelectedIndices[i]), MessageBoxButtons.OKCancel) == DialogResult.Cancel)
							return;
					}
					else
						IMAGESET[IMAGESETINDEX].Header.RemoveKey(headerlistbox.SelectedIndices[i]);
				}

				FileTxtsUpD();
				HeaderTxt.SelectedIndex = ind0;
			}
		}

		private void HeaderKeyTxt_MouseUp(object sender, MouseEventArgs e)
		{
			ListBox lb = (ListBox)sender;
			if (lb.SelectedIndices.Count == 0)
				HeaderCntxt.Close();

			if (e.Button == MouseButtons.Left)
			{
				int[] inds = new int[lb.SelectedIndices.Count];
				for (int i = 0; i < inds.Length; i++)
					inds[i] = lb.SelectedIndices[i];
				int topi = lb.TopIndex;

				HeaderTxt.BeginUpdate();
				HeaderTxt.SelectedIndices.Clear();

				for (int i = 0; i < inds.Length; i++)
					HeaderTxt.SelectedIndex = inds[i];

				HeaderTxt.TopIndex = topi;
				HeaderTxt.EndUpdate();
			}

			if (e.Button == MouseButtons.XButton1)
				ViewLastbtn.PerformClick();
			if (e.Button == MouseButtons.XButton2)
				ViewNextBtn.PerformClick();
		}

		private void HCPlotListValues_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "CCDLAB File List (*.CFL)|*.CFL";
			dlg.Title = "Select File List...";

			if (dlg.ShowDialog() == DialogResult.OK)
			{
				string file = dlg.FileName;
				FileStream fs2 = new FileStream(file, System.IO.FileMode.Open, FileAccess.Read);
				StreamReader sr2 = new StreamReader(fs2);
				int numlines = Convert.ToInt32(sr2.ReadLine());
				string[] filenames = new string[numlines];
				for (int i = 0; i < numlines; i++)
					filenames[i] = sr2.ReadLine();

				sr2.Close();
				fs2.Close();

				int headinds = HeaderTxt.SelectedIndices.Count;
				string[] keys = new string[headinds];
				for (int i = 0; i < headinds; i++)
					keys[i] = IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name;

				PlotKeyList(keys, filenames);
			}
		}

		private void HCPlotKeyValues_Click(object sender, EventArgs e)
		{
			int headinds = HeaderTxt.SelectedIndices.Count;
			string[] keys = new string[headinds];

			for (int i = 0; i < headinds; i++)
				keys[i] = IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name;

			PlotKeyList(keys, IMAGESET.FullFileNames);
		}

		private void PlotKeyList(string[] keys, string[] filenames)
		{
			double[,] allkeyvalues = new double[filenames.Length, keys.Length];
			JPFITS.FITSImage f = null;
			int FL = filenames.Length;
			int KL = keys.Length;

			ProgressBar.Maximum = FL;
			for (int i = 0; i < FL; i++)
			{
				f = new FITSImage(filenames[i], null, true, false, false, false);
				ProgressBar.Value = i + 1;
				ProgressBar.Refresh();

				for (int j = 0; j < KL; j++)
				{
					try
					{
						allkeyvalues[i, j] = Convert.ToDouble(f.Header.GetKeyValue(keys[j]));
					}
					catch (System.FormatException)
					{
						MessageBox.Show("Key value not numeric, can not plot...", "Error");
						ProgressBar.Value = 0;
						return;
					}
				}
			}
			ProgressBar.Value = 0;

			double[] ydata = new double[FL];
			double[] xdata = new double[FL];
			for (int i = 0; i < FL; i++)
				xdata[i] = i + 1;

			for (int j = 0; j < KL; j++)
			{
				for (int i = 0; i < FL; i++)
				{
					ydata[i] = allkeyvalues[i, j];
				}

				Plotter plot = new Plotter("", false, false);
				plot.Text = keys[j];
				plot.ChartGraph.PlotXYData(xdata, ydata, keys[j], "Image Number", keys[j] + ": " + f.Header.GetKeyComment(keys[j]), JPChart.SeriesType.Line, keys[j], null);
			}
		}

		private void HCCopyKeyValue_Click(object sender, EventArgs e)
		{
			int headinds = HeaderTxt.SelectedIndices.Count;
			string[] keys = new string[headinds];

			for (int i = 0; i < headinds; i++)
				keys[i] = IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name;

			CopyKeyList(keys, IMAGESET.FullFileNames);
		}

		private void HCCopyListValue_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "CCDLAB File List (*.CFL)|*.CFL";
			dlg.Title = "Select File List...";

			if (dlg.ShowDialog() == DialogResult.OK)
			{
				string file = dlg.FileName;
				FileStream fs2 = new FileStream(file, System.IO.FileMode.Open, FileAccess.Read);
				StreamReader sr2 = new StreamReader(fs2);
				int numlines = Convert.ToInt32(sr2.ReadLine());
				string[] filenames = new string[numlines];
				for (int i = 0; i < numlines; i++)
					filenames[i] = sr2.ReadLine();

				sr2.Close();
				fs2.Close();

				int headinds = HeaderTxt.SelectedIndices.Count;
				string[] keys = new string[headinds];
				for (int i = 0; i < headinds; i++)
					keys[i] = IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name;

				CopyKeyList(keys, filenames);
			}
		}

		private void CopyKeyList(string[] keys, string[] filenames)
		{
			string list = "";

			JPFITS.FITSImage f;

			for (int j = 0; j < filenames.Length; j++)
			{
				f = new FITSImage(filenames[j], null, true, false, false, false);

				for (int i = 0; i < keys.Length - 1; i++)
					list += f.Header.GetKeyValue(keys[i]) + "	";//tab delimit;

				list += f.Header.GetKeyValue(keys[keys.Length - 1]);

				if (j < filenames.Length - 1)
					list += Environment.NewLine;
			}

			Clipboard.SetText(list);
			MessageBox.Show("Key value copied to clipboard...", "Copy");
		}

		private void HCExtractKeyValue_Click(object sender, EventArgs e)
		{
			int headinds = HeaderTxt.SelectedIndices.Count;
			string[] keys = new string[headinds];

			for (int i = 0; i < headinds; i++)
				keys[i] = IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name;

			ExtractKeyList(keys, IMAGESET.FullFileNames);
		}

		private void HCExtractListValues_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "CCDLAB File List (*.CFL)|*.CFL";
			dlg.Title = "Select File List...";

			if (dlg.ShowDialog() == DialogResult.OK)
			{
				string file = dlg.FileName;
				FileStream fs2 = new FileStream(file, System.IO.FileMode.Open, FileAccess.Read);
				StreamReader sr2 = new StreamReader(fs2);
				int numlines = Convert.ToInt32(sr2.ReadLine());
				string[] filenames = new string[numlines];
				for (int i = 0; i < numlines; i++)
					filenames[i] = sr2.ReadLine();

				sr2.Close();
				fs2.Close();

				int headinds = HeaderTxt.SelectedIndices.Count;
				string[] keys = new string[headinds];
				for (int i = 0; i < headinds; i++)
					keys[i] = IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name;

				ExtractKeyList(keys, filenames);
			}
		}

		private void ExtractKeyList(string[] keys, string[] filenames)
		{
			string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			SaveFileDialog dlg = new SaveFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "Tab Delimited Text File (*.txt)|*.txt";
			dlg.Title = "Save Key Values to Text File...";

			if (dlg.ShowDialog() == DialogResult.OK)
			{
				string[,] list = new string[keys.Length + 1, filenames.Length + 1];
				list[0, 0] = String.Concat("File", "	");//tab delimited
				for (int i = 0; i < keys.Length; i++)
					list[i + 1, 0] = String.Concat(keys[i], "	");//tab delimited

				JPFITS.FITSImage f;

				ProgressBar.Maximum = filenames.Length;
				for (int j = 1; j < filenames.Length + 1; j++)
				{
					f = new FITSImage(filenames[j - 1], null, true, false, false, false);

					ProgressBar.Value = j;
					ProgressBar.Refresh();

					list[0, j] = String.Concat(f.FileName, "	");//tab delimit
					for (int i = 1; i < keys.Length + 1; i++)
					{
						list[i, j] = String.Concat(f.Header.GetKeyValue(keys[i - 1]), "	");//tab delimit;
					}
				}
				ProgressBar.Value = 0;

				FileStream fs = new FileStream(dlg.FileName, System.IO.FileMode.Create, FileAccess.Write);
				StreamWriter sw = new StreamWriter(fs);

				for (int i = 0; i < filenames.Length + 1; i++)
				{
					for (int j = 0; j < keys.Length + 1; j++)
					{
						sw.Write(list[j, i]);
					}
					sw.WriteLine();
				}
				sw.Flush();
				sw.Close();
				fs.Close();
			}
		}

		private void HeaderCntxtMenu_Click(object sender, EventArgs e)
		{
			
		}

		private void EMFileBias_Click(object sender, EventArgs e)
		{
			SubBiasChck.Checked = true;
		}

		private void EMBatchFlat_Click(object sender, EventArgs e)
		{

		}

		private void RegistrationDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (RegistrationDrop.SelectedIndex == 0)
				RegistrationDrop.SelectedIndex = 1;

			if (RegistrationDrop.SelectedIndex == 2)
				EqualHWChck.Checked = true;
		}

		private void RegisterBtn_Click(object sender, EventArgs e)
		{
			if (RegistrationDrop.SelectedIndex == -1)
				RegistrationDrop.SelectedIndex = 1;

			if (RegistrationDrop.SelectedIndex == 1)
				AutoRegBtn_Click(sender, e);
			else if (RegistrationDrop.SelectedIndex == 2)
				ManRegBtn_Click(sender, e);
		}

		private void AutoRegBtn_Click(object sender, EventArgs e)
		{
            RotateBtnCntxtBiLinear.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtBiLinear"));
            RotateBtnCntxtLanczos3.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos3"));
            RotateBtnCntxtLanczos4.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos4"));
            RotateBtnCntxtLanczos5.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos5"));
            RotateBtnCntxtNearest.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtNearest"));

			string interp = "";
            if (RotateBtnCntxtNearest.Checked)
                interp = "nearest";
            if (RotateBtnCntxtBiLinear.Checked)
                interp = "bilinear";
            if (RotateBtnCntxtLanczos3.Checked)
                interp = "lanc_3";
            if (RotateBtnCntxtLanczos4.Checked)
                interp = "lanc_4";
            if (RotateBtnCntxtLanczos5.Checked)
                interp = "lanc_5";

            int refim = 0;//(int)(RegRefIndex.Value-1);//reference image
			bool dostats = true;//possibly false if auto-batch

			if (!IMAGESET.CoDimensional)
			{
				MessageBox.Show("Cannot register non co-dimensional images", "Error");
				return;
			}

			IMAGESET.Register(refim, interp, dostats, true);
			FileListDrop_SelectedIndexChanged(sender, e);
		}

		private void HCEdit_Click(object sender, EventArgs e)
		{
			int ind = HeaderTxt.SelectedIndex;
			if (ind >= 0)
			{
				bool valid = FITSHeader.ValidKeyEdit(IMAGESET[IMAGESETINDEX].Header[ind].Name, false);
				
				if (valid == true)
				{
					FITSHeaderKeyDialog ekd = new FITSHeaderKeyDialog(IMAGESET[IMAGESETINDEX].Header[ind]);
					ekd.ShowDialog();

					if (ekd.DialogResult == DialogResult.OK)
					{
						if (IMAGESET[IMAGESETINDEX].Header[ind].IsCommentKey)
							IMAGESET[IMAGESETINDEX].Header[ind].Comment = ekd.CommentKeyLineTxt.Text;
						else
						{
							IMAGESET[IMAGESETINDEX].Header[ind].Name = ekd.KeyNameTxt.Text;
							IMAGESET[IMAGESETINDEX].Header[ind].Value = ekd.KeyValueTxt.Text;
							IMAGESET[IMAGESETINDEX].Header[ind].Comment = ekd.KeyCommentTxt.Text;
						}

						int topi = HeaderTxt.TopIndex;
						HeaderTxt.BeginUpdate();
						HeaderTxt.Items.Clear();
						HeaderTxt.Items.AddRange(IMAGESET[IMAGESETINDEX].Header.GetFormattedHeaderBlock(FITSHeader.HeaderUnitType.Primary, true));
						HeaderTxt.SelectedIndex = ind;
						HeaderTxt.TopIndex = topi;
						HeaderTxt.EndUpdate();
					}
				}
				else
				{
					MessageBox.Show("Sorry, but this is a Restricted Key! You don't have access.", "FITS Restriction...");
				}
			}
		}

		private void HCEditAll_Click(object sender, EventArgs e)
		{
			int ind = HeaderTxt.SelectedIndex;
			if (ind < 0)
				return;
			bool valid = FITSHeader.ValidKeyEdit(IMAGESET[IMAGESETINDEX].Header[ind].Name, false);
			if (!valid)
			{
				MessageBox.Show("Sorry, but this is a Restricted Key! You don't have access.", "FITS Restriction...");
				return;
			}

			FITSHeaderKeyDialog ekd = new FITSHeaderKeyDialog(IMAGESET[IMAGESETINDEX].Header[ind]);
			ekd.ShowDialog();

			if (ekd.DialogResult == DialogResult.Cancel)
				return;

			ProgressBar.Maximum = IMAGESET.Count;
			for (int j = 0; j < IMAGESET.Count; j++)
			{
				ProgressBar.Value++;
				ProgressBar.Refresh();
				IMAGESET[j].Header[ind].Name = ekd.KeyNameTxt.Text;
				IMAGESET[j].Header[ind].Value = ekd.KeyValueTxt.Text;
				IMAGESET[j].Header[ind].Comment = ekd.KeyCommentTxt.Text;
			}
			ProgressBar.Value = 0;

			int topi = HeaderTxt.TopIndex;
			HeaderTxt.BeginUpdate();
			HeaderTxt.Items.Clear();
			HeaderTxt.Items.AddRange(IMAGESET[IMAGESETINDEX].Header.GetFormattedHeaderBlock(FITSHeader.HeaderUnitType.Primary, true));
			HeaderTxt.SelectedIndex = ind;
			HeaderTxt.TopIndex = topi;
			HeaderTxt.EndUpdate();
		}

		private void HCInsertCurrent_Click(object sender, EventArgs e)
		{
			int index = HeaderTxt.SelectedIndex;

			FITSHeaderKeyDialog ekd = new FITSHeaderKeyDialog();
			ekd.CommentKeyLineChck.Visible = true;
			if (ekd.ShowDialog() == DialogResult.Cancel)
				return;
			bool iscommentline = ekd.CommentKeyLineChck.Checked;

			if (iscommentline)
				IMAGESET[IMAGESETINDEX].Header.AddCommentKeyLine(ekd.CommentKeyLineTxt.Text, index);
			else
			{
				if (!FITSHeader.ValidKeyEdit(ekd.KeyNameTxt.Text, false) || IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(ekd.KeyNameTxt.Text, false) != -1)
				{
					MessageBox.Show("Sorry, but this is either a restricted key or it already exists! Can Not Insert.", "FITS Restriction...");
					return;
				}

				IMAGESET[IMAGESETINDEX].Header.AddKey(ekd.KeyNameTxt.Text, ekd.KeyValueTxt.Text, ekd.KeyCommentTxt.Text, index);
			}

			HeaderTxt.Items.Clear();
			HeaderTxt.Items.AddRange(IMAGESET[IMAGESETINDEX].Header.GetFormattedHeaderBlock(FITSHeader.HeaderUnitType.Primary, true));
			HeaderTxt.SelectedIndex = index;
		}

		private void HCInsertBatch_Click(object sender, EventArgs e)
		{
			int index = HeaderTxt.SelectedIndex;

			FITSHeaderKeyDialog ekd = new FITSHeaderKeyDialog();
			ekd.CommentKeyLineChck.Visible = true;
			if (ekd.ShowDialog() == DialogResult.Cancel)
				return;
			bool iscommentline = ekd.CommentKeyLineChck.Checked;

			ProgressBar.Maximum = IMAGESET.Count;
			for (int j = 0; j < IMAGESET.Count; j++)
			{
				ProgressBar.Value++;
				ProgressBar.Refresh();

				if (iscommentline)
					IMAGESET[j].Header.AddCommentKeyLine(ekd.CommentKeyLineTxt.Text, index);
				else
				{
					if (!FITSHeader.ValidKeyEdit(ekd.KeyNameTxt.Text, false) || IMAGESET[j].Header.GetKeyIndex(ekd.KeyNameTxt.Text, false) != -1)
					{
						MessageBox.Show("Sorry, but this is either a restricted key or it already exists! Can Not Insert for image " + (j + 1) + ".", "FITS Restriction...");
						continue;
					}

					IMAGESET[j].Header.AddKey(ekd.KeyNameTxt.Text, ekd.KeyValueTxt.Text, ekd.KeyCommentTxt.Text, index);
				}

			}
			ProgressBar.Value = 0;

			HeaderTxt.Items.Clear();
			HeaderTxt.Items.AddRange(IMAGESET[IMAGESETINDEX].Header.GetFormattedHeaderBlock(FITSHeader.HeaderUnitType.Primary, true));
			HeaderTxt.SelectedIndex = index;
		}

		private void HCInsertSelectedToOthers_Click(object sender, EventArgs e)
		{
			for (int j = 0; j < HeaderTxt.SelectedIndices.Count; j++)
				for (int i = 0; i < IMAGESET.Count; i++)
					if (i == IMAGESETINDEX)
						continue;
					else
						IMAGESET[i].Header.SetKey(IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[j]].Name, IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[j]].Value, IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[j]].Comment, true, HeaderTxt.SelectedIndices[j]);
		}

		private void HCRemoveCurrent_Click(object sender, EventArgs e)
		{
			for (int i = HeaderTxt.SelectedIndices.Count - 1; i >= 0; i--)
				if (FITSHeader.ValidKeyEdit(IMAGESET[IMAGESETINDEX].Header[HeaderTxt.SelectedIndices[i]].Name, false))
					IMAGESET[IMAGESETINDEX].Header.RemoveKey(HeaderTxt.SelectedIndices[i]);

			HeaderTxt.Items.Clear();
			HeaderTxt.Items.AddRange(IMAGESET[IMAGESETINDEX].Header.GetFormattedHeaderBlock(FITSHeader.HeaderUnitType.Primary, true));
		}

		private void HCRemoveBatch_Click(object sender, EventArgs e)
		{

		}

		private void ManRegBtn_Click(object sender, EventArgs e)
		{
			try
			{
				if (!MANREG_CONTINUE && !UVITMANREG_CONTINUE)
				{
					if (MessageBox.Show("Please select point sources (left-click) which stay within the field of view for the duration of the image set!  RIGHT-CLICK when done.", "Know what you're doing...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					{
						MANREG_CONTINUE = false;
						UVITMANREG_CONTINUE = false;
						DOMANREG = false;
						DOUVITMANREG = false;
						if (IMAGESET.Count == 1)
							ImageBatchRedxnPnl.Enabled = false;
						return;
					}

					if (XDRIFT_PLOT != null)
						if (!XDRIFT_PLOT.IsDisposed)
							XDRIFT_PLOT.Close();
					if (YDRIFT_PLOT != null)
						if (!YDRIFT_PLOT.IsDisposed)
							YDRIFT_PLOT.Close();

					ROIFIXEDCURSOR = false;//allow cursor box to move
					DOMANREG = true;
					Cursor.Hide();

					FNDCOORDS_X = new int[1];//this is for plotting the local max point in the ROI
					FNDCOORDS_Y = new int[1];
					FNDCOORDRECTS = new Rectangle[1];
					MANREGCOORDS = new int[0, 0];
					MANREGCOORDRECTS = new Rectangle[0];

					ShowFoundCoordsChck.Checked = true;//this is for plotting the local max point in the ROI

					FileListDrop.SelectedIndex = 0;

					return;
				}
				if (MANREG_CONTINUE && !UVITMANREG_CONTINUE)
				{
					DOMANREG = false;
					MANREG_CONTINUE = false;
					UVITMANREG_CONTINUE = false;

					if (MANREGCOORDRECTS.Length == 0)//right-clicked out with no point selections, meaning quitting.  Reset swithces
					{
						return;
					}

					if (MessageBox.Show("Continue?", "Image Registration...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					{
						ShowFoundCoordsChck.Checked = false;//this is for plotting the local max point in the ROI
						ImageWindow.Refresh();
						return;
					}

					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = 100;
					WAITBAR.Text = "Point Source Registration...";
					ManRegWrkr.RunWorkerAsync();
					WAITBAR.ShowDialog();

					return;
				}
				if (!MANREG_CONTINUE && UVITMANREG_CONTINUE)
				{
					ImageBatchRedxnPnl.Enabled = false;
					MANREG_CONTINUE = false;

					if (MANREGCOORDRECTS.Length == 0)//right-clicked out with no point selections, meaning quitting.  Reset swithces
					{
						UVITMANREGDIRLISTINDEX = 0;
						DOUVITMANREG = false;
						UVITMANREG_CONTINUE = false;
						return;
					}

					if (MessageBox.Show("Proceed with drift tracking?", "Drift Registration...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					{
						DOMANREG = false;
						UVITMANREG_CONTINUE = false;
						ShowFoundCoordsChck.Checked = false;//this is for plotting the local max point in the ROI
						ImageWindow.Refresh();
						return;
					}
					else
					{
						UVITMANREG_CONTINUE = true;
					}

					DOMANREG = false;
					UVITCreateDriftFromINTMenuItem_Click(sender, e);
					return;
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Data + "	" + ex.InnerException + "	" + ex.Message + "	" + ex.Source + "	" + ex.StackTrace + "	" + ex.TargetSite);
			}
		}

		private void ManRegWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
            RotateBtnCntxtBiLinear.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtBiLinear"));
            RotateBtnCntxtLanczos3.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos3"));
            RotateBtnCntxtLanczos4.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos4"));
            RotateBtnCntxtLanczos5.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos5"));
            RotateBtnCntxtNearest.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtNearest"));
            string interp = "";
            if (RotateBtnCntxtNearest.Checked)
                interp = "nearest";
            if (RotateBtnCntxtBiLinear.Checked)
                interp = "bilinear";
            if (RotateBtnCntxtLanczos3.Checked)
                interp = "lanc_3";
            if (RotateBtnCntxtLanczos4.Checked)
                interp = "lanc_4";
            if (RotateBtnCntxtLanczos5.Checked)
                interp = "lanc_5";

            float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[IMAGESETINDEX].Width);
			float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[IMAGESETINDEX].Height);
			bool UVITdisplay = PointSrcINTDriftDisplayChck.Checked;
			int UVITdisplaycadence = Convert.ToInt32(PointSrcINTDriftDisplayCadenceDrop.SelectedItem);

			int i = 0;
			try
			{
				int SRC_HW = (int)PSEKernelRadUpD.Value;
				if (DO_UVITDRIFTFILES)
					SRC_HW = 2;
				double[,] src = new double[SRC_HW * 2 + 1, SRC_HW * 2 + 1];
				double[,] src_X = new double[SRC_HW * 2 + 1, SRC_HW * 2 + 1];
				double[,] src_Y = new double[SRC_HW * 2 + 1, SRC_HW * 2 + 1];
				int TRK_HW = (int)HalfWidthXUpD.Value;
				double[,] box = new double[TRK_HW * 2 + 1, TRK_HW * 2 + 1];
				double[,] box_X = new double[TRK_HW * 2 + 1, TRK_HW * 2 + 1];
				double[,] box_Y = new double[TRK_HW * 2 + 1, TRK_HW * 2 + 1];

				int NSrc = MANREGCOORDS.GetLength(0);
				int Nim;
				if (DO_UVITDRIFTFILES)
					Nim = UVITMANREGFILELIST.Length;
				else
					Nim = IMAGESET.Count;

				MANREGCENTROIDS = new double[NSrc, 2, Nim];
				if (DO_UVITDRIFTFILES)
				{
					UVITINTMODEDRIFTPOLYPOINTS = new Point[MANREGCENTROIDS.GetLength(0), MANREGCENTROIDS.GetLength(2)];
					UVITINTDRIFT_MAXDEV_INDEX = -1;
				}

				FITSImage img;
				int intprog = 0, ntracksremoved = 0;
				int[] divergcount = new int[NSrc];
				for (i = 0; i < Nim; i++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
					{
						if (DO_UVITDRIFTFILES)
							UVITBADTRACK = true;
						return;
					}

					if (100 * i / Nim > intprog)
					{
						intprog = 100 * i / Nim;
						ManRegWrkr.ReportProgress(intprog);
					}

					if (DO_UVITDRIFTFILES)
					{
						img = SPAREFITSImageSet[i];
						UVITMANREGFILELIST_TIMES[i] = Convert.ToDouble(img.Header.GetKeyValue("FRMTIME")) * 1000;
					}
					else
						img = IMAGESET[i];//loaded images

					for (int j = 0; j < NSrc; j++)
					{
						//create a box around the coords
						for (int k = -TRK_HW; k <= TRK_HW; k++)
							for (int l = -TRK_HW; l <= TRK_HW; l++)
							{
								box[k + TRK_HW, l + TRK_HW] = img[MANREGCOORDS[j, 0] + k, MANREGCOORDS[j, 1] + l];
								box_X[k + TRK_HW, l + TRK_HW] = (double)(MANREGCOORDS[j, 0] + k);
								box_Y[k + TRK_HW, l + TRK_HW] = (double)(MANREGCOORDS[j, 1] + l);
							}

						//do background subtraction here
						if (!DO_UVITDRIFTFILES)//not needed for UVIT VIS files
							box = JPMath.MatrixSubScalar(box, JPMath.Median(box), false);//= JPMath.MatrixSubScalar(box, JPMath.Min(box, true));//median or min?

						//now make a little centroid box
						int xm = 0, ym = 0;
						JPMath.Max(box, out xm, out ym, false);
						if (xm - SRC_HW < 0)
							xm = TRK_HW;
						if (ym - SRC_HW < 0)
							ym = TRK_HW;
						if (xm + SRC_HW > TRK_HW * 2)
							xm = TRK_HW;
						if (ym + SRC_HW > TRK_HW * 2)
							ym = TRK_HW;

						for (int k = -SRC_HW; k <= SRC_HW; k++)
							for (int l = -SRC_HW; l <= SRC_HW; l++)
							{
								src[k + SRC_HW, l + SRC_HW] = box[xm + k, ym + l];
								src_X[k + SRC_HW, l + SRC_HW] = box_X[xm + k, ym + l];
								src_Y[k + SRC_HW, l + SRC_HW] = box_Y[xm + k, ym + l];
							}

						double energy = JPMath.Sum(src, false);

						double x = JPMath.Sum(JPMath.MatrixMultMatrix(src, src_X, false), false) / energy;
						double y = JPMath.Sum(JPMath.MatrixMultMatrix(src, src_Y, false), false) / energy;

						if ((int)(x) < TRK_HW || (int)(x) > img.Width - TRK_HW)
							x = MANREGCENTROIDS[j, 0, i - 1];
						if ((int)(y) < TRK_HW || (int)(y) > img.Height - TRK_HW)
							y = MANREGCENTROIDS[j, 1, i - 1];

						MANREGCOORDS[j, 0] = (int)(x);//update position for tracking
						MANREGCOORDS[j, 1] = (int)(y);

						MANREGCENTROIDS[j, 0, i] = x;
						MANREGCENTROIDS[j, 1, i] = y;

						if (DO_UVITDRIFTFILES)
							UVITINTMODEDRIFTPOLYPOINTS[j, i] = new Point((int)(MANREGCENTROIDS[j, 0, i] * xsc), (int)(MANREGCENTROIDS[j, 1, i] * ysc));
					}

					//check for point source tracks which are going divergent and remove them from the tracking arrays...if there are more than a few tracks
					if (NSrc > 3 && DO_UVITDRIFTFILES && i > 0)
					{
						checkagain:
						double[] currdrifts = new double[NSrc];
						for (int j = 0; j < NSrc; j++)
							currdrifts[j] = Math.Sqrt((MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) * (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) + (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]) * (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]));
						double currdriftmed = JPMath.Median(currdrifts);
						int divergingindex = -1;
						double divergpix = 0.75;
						for (int j = 0; j < NSrc; j++)
							if (Math.Abs(currdrifts[j] - currdriftmed) > divergpix)
								divergcount[j]++;

						for (int k = 0; k < NSrc; k++)
							if (divergcount[k] >= 5)//then remove the bad one divergingindex
							{
								divergingindex = k;
								ntracksremoved++;
								WAITBAR.Text = "Point Source (" + (MANREGCOORDS.GetLength(0) - 1) + ") Drift Tracking Directory " + (UVITMANREGDIRLISTINDEX + 1).ToString() + " of " + UVITMANREGDIRLIST.Length.ToString() + " (Removed " + ntracksremoved + " sources)";
								NSrc -= 1;
								int[,] tempMANREGCOORDS = new int[NSrc, 2];
								int[] tempdivergingcount = new int[NSrc];
								int c = 0;
								for (int j = 0; j <= NSrc; j++)
									if (j != divergingindex)
									{
										tempMANREGCOORDS[c, 0] = MANREGCOORDS[j, 0];
										tempMANREGCOORDS[c, 1] = MANREGCOORDS[j, 1];
										tempdivergingcount[c] = divergcount[j];
										c++;
									}
								MANREGCOORDS = new int[NSrc, 2];
								divergcount = new int[NSrc];
								for (int j = 0; j < NSrc; j++)
								{
									MANREGCOORDS[j, 0] = tempMANREGCOORDS[j, 0];
									MANREGCOORDS[j, 1] = tempMANREGCOORDS[j, 1];
									divergcount[j] = tempdivergingcount[j];
								}

								double[,,] tempMANREGCENTROIDS = new double[NSrc, 2, Nim];
								Point[,] tempUVITINTMODEDRIFTPOLYPOINTS = new Point[NSrc, Nim];
								for (int ii = 0; ii <= i; ii++)
								{
									c = 0;
									for (int j = 0; j <= NSrc; j++)
										if (j != divergingindex)
										{
											tempMANREGCENTROIDS[c, 0, ii] = MANREGCENTROIDS[j, 0, ii];
											tempMANREGCENTROIDS[c, 1, ii] = MANREGCENTROIDS[j, 1, ii];
											tempUVITINTMODEDRIFTPOLYPOINTS[c, ii] = UVITINTMODEDRIFTPOLYPOINTS[j, ii];
											c++;
										}
								}
								MANREGCENTROIDS = new double[NSrc, 2, Nim];
								UVITINTMODEDRIFTPOLYPOINTS = new Point[NSrc, Nim];
								for (int ii = 0; ii <= i; ii++)
									for (int j = 0; j < NSrc; j++)
									{
										MANREGCENTROIDS[j, 0, ii] = tempMANREGCENTROIDS[j, 0, ii];
										MANREGCENTROIDS[j, 1, ii] = tempMANREGCENTROIDS[j, 1, ii];
										UVITINTMODEDRIFTPOLYPOINTS[j, ii] = tempUVITINTMODEDRIFTPOLYPOINTS[j, ii];
									}
								goto checkagain;
							}
					}

					if (NSrc <= 3 && DO_UVITDRIFTFILES && i > 20 && !UVITBADTRACK)
					{
						double[] currdrifts = new double[NSrc];
						for (int j = 0; j < NSrc; j++)
							currdrifts[j] = Math.Sqrt((MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) * (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) + (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]) * (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]));
						double currdriftstd = JPMath.Stdv(currdrifts, false);
						if (currdriftstd > 50)
							UVITBADTRACK = true;
					}

					if (DO_UVITDRIFTFILES && UVITdisplay && Math.IEEERemainder((double)i, (double)UVITdisplaycadence) == 0)
						ImageUpD(SPAREFITSImageSet[i].Image);

					if (i > 0 && !DO_UVITDRIFTFILES)
					{
						double x_drift = 0;
						double y_drift = 0;
						for (int j = 0; j < NSrc; j++)
						{
							x_drift += MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0];
							y_drift += MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0];
						}
						x_drift /= NSrc;
						y_drift /= NSrc;

						IMAGESET[i].SetImage(JPMath.RotateShiftArray(IMAGESET[i].Image, 0, Double.MaxValue, Double.MaxValue, interp, -x_drift, -y_drift, true), true, true);
                    }
				}
			}
			catch (Exception ee)
			{
				if (DO_UVITDRIFTFILES)
				{
					UVITINTDRIFT_MAXDEV_INDEX = -1;
					ImageWindow.Refresh();

					string[] refer = new string[] { UVITMANREGFILELIST[i] };
					AddToImageSet(refer, false);
					MainTab.SelectedIndex = 0;
					ImageBatchRedxnPnl.Enabled = true;
					ContrastWideRad.PerformClick();
					UVITBADTRACK = true;
				}
				MessageBox.Show("One of the point sources is probably not trackable (too low S/N).  File: " + (i + 1).ToString() + "\r\n \r\n \r\n" + ee.Data + "	" + ee.InnerException + "	" + ee.Message + "	" + ee.Source + "	" + ee.StackTrace + "	" + ee.TargetSite, "Error...");
				MessageBox.Show(MANREGCOORDS[0, 0].ToString() + "	" + MANREGCOORDS[0, 1]);
				WAITBAR.CancelBtn.PerformClick();
			}
		}

		private void ManRegWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = String.Concat("Completed: ", e.ProgressPercentage, "%");
			WAITBAR.Refresh();
		}

		private void ManRegWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				WAITBAR.Close();

				if (UVITBADTRACK)
				{
					SPAREFITSImageSet.Clear();
					UVITBADTRACK = false;
					DialogResult res = MessageBox.Show("Retry point source tracking?", "Error...", MessageBoxButtons.YesNo);
					if (res == DialogResult.Yes)
					{
						UVITCreateDriftFromINTMenuItem_Click(sender, new EventArgs());
						return;
					}
					else
					{
						UVITINTMODEDRIFTPOLYPOINTS = null;
						ImageWindow.Refresh();
					}
				}

				DOUVITMANREG = false;
				UVITMANREGFILELIST_TIMES = null;
				UVITMANREGFILELIST = null;
				UVITMANREGDIRLISTINDEX = 0;
				return;
			}

			try
			{
				if (!DO_UVITDRIFTFILES)
					WAITBAR.Close();

				if (DO_UVITDRIFTFILES)
				{
					if (UVITBADTRACK)
					{
						WAITBAR.Close();
						SPAREFITSImageSet.Clear();
						UVITBADTRACK = false;
						DialogResult res = MessageBox.Show("Manually retry point source tracking?", "Bad Track Detected...", MessageBoxButtons.YesNo);
						if (res == DialogResult.Yes)
						{
							PointSrcINTDriftNoPlotConfChck.Checked = false;
							PointSrcINTDriftNoPSEConfChck.Checked = false;
							UVITCreateDriftFromINTMenuItem_Click(sender, new EventArgs());
							return;
						}
					}
					
					ImageWindow.Refresh();
					SPAREFITSImageSet.Clear();

					object[] arg = new object[2];
					arg[0] = (Object)UVITMANREGFILELIST;
					arg[1] = (Object)CrossCorrINTDriftChck.Checked;
					UVITDriftFromINTWrkr.RunWorkerAsync(arg);
				}
			}
			catch (Exception ee)
			{
				MessageBox.Show(ee.Data + "	" + ee.InnerException + "	" + ee.Message + "	" + ee.Source + "	" + ee.StackTrace + "	" + ee.TargetSite);
			}

		}

		private void ReplaceImagePtsDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (FileListDrop.Items.Count == 0)
				return;

			if (ReplaceImagePtsDrop.SelectedIndex == 0)//manual value
				ReplaceImagePtsTxt.Enabled = true;

			if (ReplaceImagePtsDrop.SelectedIndex == 1)//image min value
			{
				ReplaceImagePtsTxt.Enabled = false;
				ReplaceImagePtsTxt.Text = IMAGESET[IMAGESETINDEX].Min.ToString();
			}
			if (ReplaceImagePtsDrop.SelectedIndex == 2)//image max value
			{
				ReplaceImagePtsTxt.Enabled = false;
				ReplaceImagePtsTxt.Text = IMAGESET[IMAGESETINDEX].Max.ToString();
			}
			if (ReplaceImagePtsDrop.SelectedIndex == 3)//image median value
			{
				ReplaceImagePtsTxt.Enabled = false;
				ReplaceImagePtsTxt.Text = IMAGESET[IMAGESETINDEX].Median.ToString();
			}
			if (ReplaceImagePtsDrop.SelectedIndex == 4)//image mean value
			{
				ReplaceImagePtsTxt.Enabled = false;
				ReplaceImagePtsTxt.Text = IMAGESET[IMAGESETINDEX].Mean.ToString();
			}
		}

		private void XBinUpD_ValueChanged(object sender, EventArgs e)
		{
			YBinUpD.Value = XBinUpD.Value;
			REG.SetReg("CCDLAB", "XBinUpD", XBinUpD.Value.ToString());
		}

		private void YBinUpD_ValueChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "YBinUpD", YBinUpD.Value.ToString());
		}

		private void SCMChck_CheckedChanged(object sender, EventArgs e)
		{
			if (SCMChck.Checked == true)
				SCMUpD.Enabled = true;
			else
				SCMUpD.Enabled = false;
		}

		private void textBox1_TextChanged(object sender, EventArgs e)
		{
		}

		private void Form1_MouseUp(object sender, MouseEventArgs e)
		{
		}

		private void TBDestructTimer_Tick(object sender, EventArgs e)
		{
			if (BackColor == Color.Gainsboro)
				BackColor = Color.Red;
			else
				BackColor = Color.Gainsboro;
		}

		private void TaskBarCntxtMenu_MouseEnter(object sender, EventArgs e)
		{
			TBDestructTimer.Enabled = true;
		}

		private void TaskBarCntxtMenu_MouseLeave(object sender, EventArgs e)
		{
			TBDestructTimer.Enabled = false;
		}

		private void TaskBarCntxtMenu_Click(object sender, EventArgs e)
		{
			this.Close();
			Application.Exit();
		}

		private void centerToolStripMenuItem_Click(object sender, EventArgs e)
		{
			SubImageSlideX.Value = (int)(IMAGESET[IMAGESETINDEX].Width / 2);
			SubImageSlideY.Value = (int)(IMAGESET[IMAGESETINDEX].Height / 2);
			SubImageStatsUpD();
			SubImageUpD();
			ImageWindow.Refresh();
		}

		private void SubImageSurfFacet_Click(object sender, EventArgs e)
		{
			SurfWrkr.RunWorkerAsync(1);
		}

		private void SubImageSurfSmooth_Click(object sender, EventArgs e)
		{
			SurfWrkr.RunWorkerAsync(2);
		}

		private void SubImageSurfMetal_Click(object sender, EventArgs e)
		{
			SurfWrkr.RunWorkerAsync(3);
		}

		private void SubImageSurfMesh_Click(object sender, EventArgs e)
		{
			SurfWrkr.RunWorkerAsync(4);
		}

		private void SubImSurfColumnMenuBtn_Click(object sender, EventArgs e)
		{
			SurfWrkr.RunWorkerAsync(5);
		}

		private void SurfWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			try
			{
				int type = Convert.ToInt32(e.Argument);
				MLSURF = new MLCCDLAB.MLSurface();

				MWNumericArray x = new MWNumericArray(1, XSUBRANGE.Length, XSUBRANGE);
				MWNumericArray y = new MWNumericArray(1, YSUBRANGE.Length, YSUBRANGE);
				MWNumericArray z = new MWNumericArray(SUBIMAGE);
				switch (type)
				{
					case (1):
					{
						MLSURF.Surf_Facet(x, y, z);
						break;
					}
					case (2):
					{
						MLSURF.Surf_Smooth(x, y, z);
						break;
					}
					case (3):
					{
						MLSURF.Surf_Metal(x, y, z);
						break;
					}
					case (4):
					{
						MLSURF.Surf_Mesh(x, y, z);
						break;
					}
					case (5):
					{
						MLSURF.Surf_Column(x, y, z);
						break;
					}
				}
			}
			catch (Exception ee)
			{
				MessageBox.Show(String.Concat(ee.Message, ":  ", ee.Data, ":  ", ee.StackTrace, "  ", ee.Source, "  ", ee.TargetSite, "  ", ee.InnerException));
			}
		}

		private void SurfWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			
		}

		private void OptFileSavePrecDbl_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = true;
			OptFileSavePrecInt32.Checked = false;
			OptFileSavePrecUInt16.Checked = false;
			OptFileSavePrecInt16.Checked = false;
			TBOptFileSavePrecDbl.Checked = true;
			TBOptFileSavePrecInt32.Checked = false;
			TBOptFileSavePrecUInt16.Checked = false;
			TBOptFileSavePrecInt16.Checked = false;
			OptsMenu.ForeColor = Color.Black;
			FILESAVEPREC = DiskPrecision.Double;

			OptsMenu.ShowDropDown();
			fileSavingPrecisionToolStripMenuItem.ShowDropDown();
			OptFileSavePrecDbl.Select();
		}

		private void TBOptFileSavePrecDbl_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = true;
			OptFileSavePrecInt32.Checked = false;
			OptFileSavePrecUInt16.Checked = false;
			OptFileSavePrecInt16.Checked = false;
			TBOptFileSavePrecDbl.Checked = true;
			TBOptFileSavePrecInt32.Checked = false;
			TBOptFileSavePrecUInt16.Checked = false;
			TBOptFileSavePrecInt16.Checked = false;
			OptsMenu.ForeColor = Color.Black;
			FILESAVEPREC = DiskPrecision.Double;

			TBFileSavePrecOpts.ShowDropDown();
			TBOptFileSavePrecDbl.Select();
		}

		private void OptFileSavePrecInt32_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = false;
			OptFileSavePrecInt32.Checked = true;
			OptFileSavePrecUInt16.Checked = false;
			OptFileSavePrecInt16.Checked = false;
			TBOptFileSavePrecDbl.Checked = false;
			TBOptFileSavePrecInt32.Checked = true;
			TBOptFileSavePrecUInt16.Checked = false;
			TBOptFileSavePrecInt16.Checked = false;
			OptsMenu.ForeColor = Color.Blue;
			FILESAVEPREC = DiskPrecision.Int32;

			OptsMenu.ShowDropDown();
			fileSavingPrecisionToolStripMenuItem.ShowDropDown();
			OptFileSavePrecInt32.Select();
		}

		private void TBOptFileSavePrecInt32_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = false;
			OptFileSavePrecInt32.Checked = true;
			OptFileSavePrecUInt16.Checked = false;
			OptFileSavePrecInt16.Checked = false;
			TBOptFileSavePrecDbl.Checked = false;
			TBOptFileSavePrecInt32.Checked = true;
			TBOptFileSavePrecUInt16.Checked = false;
			TBOptFileSavePrecInt16.Checked = false;
			OptsMenu.ForeColor = Color.Blue;
			FILESAVEPREC = DiskPrecision.Int32;

			TBFileSavePrecOpts.ShowDropDown();
			TBOptFileSavePrecInt32.Select();
		}

		private void OptFileSavePrecInt16_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = false;
			OptFileSavePrecInt32.Checked = false;
			OptFileSavePrecUInt16.Checked = false;
			OptFileSavePrecInt16.Checked = true;
			TBOptFileSavePrecDbl.Checked = false;
			TBOptFileSavePrecInt32.Checked = false;
			TBOptFileSavePrecUInt16.Checked = false;
			TBOptFileSavePrecInt16.Checked = true;
			OptsMenu.ForeColor = Color.Yellow;
			FILESAVEPREC = DiskPrecision.Int16;

			OptsMenu.ShowDropDown();
			fileSavingPrecisionToolStripMenuItem.ShowDropDown();
			OptFileSavePrecInt16.Select();
		}

		private void TBOptFileSavePrecInt16_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = false;
			OptFileSavePrecInt32.Checked = false;
			OptFileSavePrecUInt16.Checked = false;
			OptFileSavePrecInt16.Checked = true;
			TBOptFileSavePrecDbl.Checked = false;
			TBOptFileSavePrecInt32.Checked = false;
			TBOptFileSavePrecUInt16.Checked = false;
			TBOptFileSavePrecInt16.Checked = true;
			OptsMenu.ForeColor = Color.Yellow;
			FILESAVEPREC = DiskPrecision.Int16;

			TBFileSavePrecOpts.ShowDropDown();
			TBOptFileSavePrecInt16.Select();
		}

		private void OptFileSavePrecUInt16_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = false;
			OptFileSavePrecInt32.Checked = false;
			OptFileSavePrecUInt16.Checked = true;
			OptFileSavePrecInt16.Checked = false;
			TBOptFileSavePrecDbl.Checked = false;
			TBOptFileSavePrecInt32.Checked = false;
			TBOptFileSavePrecUInt16.Checked = true;
			TBOptFileSavePrecInt16.Checked = false;
			OptsMenu.ForeColor = Color.LimeGreen;
			FILESAVEPREC = DiskPrecision.UInt16;

			OptsMenu.ShowDropDown();
			fileSavingPrecisionToolStripMenuItem.ShowDropDown();
			OptFileSavePrecUInt16.Select();
		}

		private void TBOptFileSavePrecUInt16_Click(object sender, EventArgs e)
		{
			OptFileSavePrecDbl.Checked = false;
			OptFileSavePrecInt32.Checked = false;
			OptFileSavePrecUInt16.Checked = true;
			OptFileSavePrecInt16.Checked = false;
			TBOptFileSavePrecDbl.Checked = false;
			TBOptFileSavePrecInt32.Checked = false;
			TBOptFileSavePrecUInt16.Checked = true;
			TBOptFileSavePrecInt16.Checked = false;
			OptsMenu.ForeColor = Color.LimeGreen;
			FILESAVEPREC = DiskPrecision.UInt16;

			TBFileSavePrecOpts.ShowDropDown();
			TBOptFileSavePrecUInt16.Select();
		}

		private void ImageViewHistogram_Click(object sender, EventArgs e)
		{
			ImageCntxtViewWrkr.RunWorkerAsync(1);//make a histogram of the current image, or of the batch of images if the batch check is selected
		}

		private void ImageCntxtViewWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			int type = Convert.ToInt32(e.Argument);
			object[] resultinfo = new object[] { -1 };//have to set this so runworkercompleted can check for an instance of the instantiation
			e.Result = resultinfo;//which means this also needs set to an instanitation
			switch (type)
			{
				case (1)://make a histogram of the current image or the batch of images
				{
					double[] values = new double[IMAGESET[IMAGESETINDEX].Image.Length];

					Parallel.For(0, IMAGESET[IMAGESETINDEX].Width, i =>
					{
						for (int j = 0; j < IMAGESET[IMAGESETINDEX].Height; j++)
							values[i * IMAGESET[IMAGESETINDEX].Height + j] = IMAGESET[IMAGESETINDEX][i, j];
					});

					resultinfo = new object[2];
					resultinfo[0] = 1;
					resultinfo[1] = (object)values;
					e.Result = resultinfo;
					break;
				}
				case (2):
				{
					break;
				}
			}
		}

		private void ImageCntxtViewWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			ProgressBar.Value = e.ProgressPercentage;
			ProgressBar.Refresh();
		}

		private void ImageCntxtViewWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			ProgressBar.Value = 0;

			object[] res = (object[])e.Result;
			if (Convert.ToInt32(res[0]) == 1)//make a histogram of the current image
			{
				double[] x;
				double[] y = JPMath.Histogram_IntegerStep((double[])res[1], 1, out x);

				Plotter jpplot = new Plotter("VHist", true, true);
				jpplot.Text = "Image Values Histogram";
				jpplot.ChartGraph.PlotXYData(x, y, "Image Values Histogram", "Image Value", "Number of Elements", JPChart.SeriesType.Column, "Histogram");
			}
		}

		private void ImageEditValueCntxt_Click(object sender, EventArgs e)
		{
			EditValueCntxt_Click(sender, e);
		}

		private void EditValueCntxt_Click(object sender, EventArgs e)
		{
			//	ImageCntxtViewWrkr.RunWorkerAsync(2);//edit selected pixel value of image, or set of images
			//this doesn't work because with the other thread going, XPOS and YPOS changes are updated and the wrong pixel position then gets modifed
			//yes can code that of course, but whatever, it doesn't NEED to go into a BG worker because there's no need for a "cancel" button option

			EditValueDlg dlg = new EditValueDlg();
			double oldval = IMAGESET[IMAGESETINDEX][XPOS_CURSOR, YPOS_CURSOR];
			dlg.EditValueTxt.Text = Convert.ToString(oldval);
			dlg.ShowDialog();

			if (dlg.DialogResult == DialogResult.OK)
			{
				string strval = dlg.EditValueTxt.Text;
				bool outsideROI = strval.StartsWith("!");
				if (outsideROI)
					strval = strval.Substring(1, strval.Length - 1);

				double newval = Convert.ToDouble(strval);

				int[] indeces = null;
				if (BatchCorrectionChck.Checked)
				{
					DialogResult dr = MessageBox.Show("Are you sure you want to apply this to all images?", "Proceed?", MessageBoxButtons.YesNoCancel);
					if (dr == DialogResult.Cancel)
						return;
					if (dr == DialogResult.No)
					{
						indeces = new int[] { IMAGESETINDEX };
						BatchCorrectionChck.Checked = false;
					}
					if (dr == DialogResult.Yes)
					{
						indeces = new int[IMAGESET.Count];
						for (int i = 0; i < IMAGESET.Count; i++)
							indeces[i] = i;
					}
				}
				else
					indeces = new int[] { IMAGESETINDEX };

				ProgressBar.Maximum = indeces.Length;
				for (int k = 0; k < indeces.Length; k++)
				{
					ProgressBar.Value = k + 1;
					ProgressBar.Refresh();

					if (!outsideROI)
						IMAGESET[indeces[k]][XPOS_CURSOR, YPOS_CURSOR] = newval;
					else
					{
						Parallel.For(0, IMAGESET[indeces[k]].Width, i =>
						{
							for (int j = 0; j < IMAGESET[indeces[k]].Height; j++)
								IMAGESET[indeces[k]][i, j] = newval;
						});

						IMAGESET[indeces[k]][XPOS_CURSOR, YPOS_CURSOR] = oldval;
					}
					IMAGESET[indeces[k]].StatsUpD(true);
				}
				ProgressBar.Value = 0;
				FileListDrop_SelectedIndexChanged(sender, e);
			}
			else
			{
				EditValueCntxt_Click(sender, e);
			}
		}

		private void EditBoxCntxt_Click(object sender, EventArgs e)
		{
			ImageEditBoxCntxt_Click(sender, e);
		}

		private void ImageEditBoxCntxt_Click(object sender, EventArgs e)
		{
			EditValueDlg dlg = new EditValueDlg();
			if (dlg.ShowDialog() == DialogResult.Cancel)
				return;

			string strval = dlg.EditValueTxt.Text;
			bool outsideROI = strval.StartsWith("!");
			if (outsideROI)
				strval = strval.Substring(1, strval.Length - 1);
			if (!JPMath.IsNumeric(strval))
			{
				MessageBox.Show("Enter a number...");
				ImageEditBoxCntxt.PerformClick();
				return;
			}
			double val = Convert.ToDouble(strval);

			int[] indeces = null;
			if (BatchCorrectionChck.Checked)
			{
				DialogResult dr = MessageBox.Show("Are you sure you want to apply this to all images?", "Proceed?", MessageBoxButtons.YesNoCancel);
				if (dr == DialogResult.Cancel)
					return;
				if (dr == DialogResult.No)
				{
					indeces = new int[] { IMAGESETINDEX };
					BatchCorrectionChck.Checked = false;
				}
				if (dr == DialogResult.Yes)
				{
					indeces = new int[IMAGESET.Count];
					for (int i = 0; i < IMAGESET.Count; i++)
						indeces[i] = i;
				}
			}
			else
				indeces = new int[] { IMAGESETINDEX };
			ProgressBar.Maximum = indeces.Length;

			if (PSEDrawROI.Checked)
			{
				for (int k = 0; k < indeces.Length; k++)
				{
					ProgressBar.Value = k + 1;
					ProgressBar.Refresh();

					if (!outsideROI)
					{
						Parallel.For(0, IMAGESET[IMAGESETINDEX].Width, x =>
						{
							for (int y = 0; y < IMAGESET[IMAGESETINDEX].Height; y++)
								if (ROI_REGION[x, y])
									IMAGESET[indeces[k]][x, y] = val;
						});
					}
					else
					{
						Parallel.For(0, IMAGESET[IMAGESETINDEX].Width, x =>
						{
							for (int y = 0; y < IMAGESET[IMAGESETINDEX].Height; y++)
								if (!ROI_REGION[x, y])
									IMAGESET[indeces[k]][x, y] = val;
						});
					}
				}

				ProgressBar.Value = 0;
				FileListDrop_SelectedIndexChanged(sender, e);
				return;
			}

			if (PSEEllipticalROI.Checked)
			{
				for (int k = 0; k < indeces.Length; k++)
				{
					ProgressBar.Value = k + 1;
					ProgressBar.Refresh();

					ROIX0 = SubImageSlideX.Value - 1;
					ROIY0 = SubImageSlideY.Value - 1;
					ROIXRad = (int)HalfWidthXUpD.Value;
					ROIYRad = (int)HalfWidthYUpD.Value;
					REG.SetReg("CCDLAB", "ROIX0", ROIX0);
					REG.SetReg("CCDLAB", "ROIY0", ROIY0);
					REG.SetReg("CCDLAB", "ROIXRad", ROIXRad);
					REG.SetReg("CCDLAB", "ROIYRad", ROIYRad);
					double roix0 = (double)ROIX0;
					double roiy0 = (double)ROIY0;
					double roixrad2 = (double)ROIXRad * (double)ROIXRad;
					double roiyrad2 = (double)ROIYRad * (double)ROIYRad;

					if (!outsideROI)
					{
						Parallel.For(0, IMAGESET[IMAGESETINDEX].Width, x =>
						{
							double dx2 = (double)x - roix0;
							dx2 *= dx2;
							dx2 /= roixrad2;
							for (int y = 0; y < IMAGESET[IMAGESETINDEX].Height; y++)
							{
								double dy = (double)y;
								if ((dx2 + (dy - roiy0) * (dy - roiy0) / roiyrad2) <= 1)
									IMAGESET[indeces[k]][x, y] = val;
							}
						});
					}
					else
					{
						Parallel.For(0, IMAGESET[IMAGESETINDEX].Width, x =>
						{
							double dx2 = (double)x - roix0;
							dx2 *= dx2;
							dx2 /= roixrad2;
							for (int y = 0; y < IMAGESET[IMAGESETINDEX].Height; y++)
							{
								double dy = (double)y;
								if ((dx2 + (dy - roiy0) * (dy - roiy0) / roiyrad2) > 1)
									IMAGESET[indeces[k]][x, y] = val;
							}
						});
					}
				}

				ProgressBar.Value = 0;
				FileListDrop_SelectedIndexChanged(sender, e);
				return;
			}

			for (int k = 0; k < indeces.Length; k++)
			{
				ProgressBar.Value = k + 1;
				ProgressBar.Refresh();

				if (!outsideROI)
				{
					//only operate on the ROI
					Parallel.For(0, XSUBRANGE.Length, i =>
					{
						for (int j = 0; j < YSUBRANGE.Length; j++)
							IMAGESET[indeces[k]][XSUBRANGE[i], YSUBRANGE[j]] = val;
					});
				}
				else
				{
					double[,] tempsubim = SUBIMAGE;//to instantiate the dimensions												   
												   //make a temp copy of the subimage												  
					Parallel.For(0, XSUBRANGE.Length, i =>
					{
						for (int j = 0; j < YSUBRANGE.Length; j++)
							tempsubim[i, j] = IMAGESET[indeces[k]][XSUBRANGE[i], YSUBRANGE[j]];
					});

					//obliterate the entire image
					Parallel.For(0, IMAGESET[indeces[k]].Width, i =>
					{
						for (int j = 0; j < IMAGESET[indeces[k]].Height; j++)
							IMAGESET[indeces[k]][i, j] = val;
					});

					//reinsert the temp unmodifed subimage
					Parallel.For(0, XSUBRANGE.Length, i =>
					{
						for (int j = 0; j < YSUBRANGE.Length; j++)
							IMAGESET[indeces[k]][XSUBRANGE[i], YSUBRANGE[j]] = tempsubim[i, j];
					});
				}
				IMAGESET[indeces[k]].StatsUpD(true);
			}
			ProgressBar.Value = 0;
			FileListDrop_SelectedIndexChanged(sender, e);

		}

		private void FindFiles()
		{
			FITSFINDER = new JPFITS.FITSFinder();
			FITSFINDER.ShowDialog();

			if (FITSFINDER.DialogResult != DialogResult.OK)
				return;

			int numfilesfound = FITSFINDER.FoundFiles.Length;
			if (numfilesfound == 0)//no files found
			{
				TBViewFound.Enabled = false;
				FMViewFound.Enabled = false;
				MessageBox.Show("No Files Found Matching File Extension or Search Criteria...", "Warning");
				FindFiles();
				return;
			}

			FITSFINDERFILES = FITSFINDER.FoundFiles;

			TBViewFound.Enabled = true;
			FMViewFound.Enabled = true;
			FITSFOUND = new JPFITS.FITSFound(FITSFINDERFILES);
			FITSFOUND.ShowDialog();

			int Ninds = FITSFOUND.FileListTxt.SelectedIndices.Count;
			if (Ninds == 0 && FITSFOUND.DialogResult != DialogResult.Cancel)//no files selected but asked to load files (!cancel)
			{
				MessageBox.Show("No Files Selected!...", "Error");
				ViewFoundList();
				return;
			}

			string[] selectfiles = FITSFOUND.SelectedFiles;

            switch (FITSFOUND.DialogResult)
			{
				case (DialogResult.Cancel):
				{
					FindFiles();
					break;
				}
				case (DialogResult.OK)://for loading NEW IMAGESET
				{
					AUTOLOADIMAGES = true;
					AUTOLOADIMAGESFILES = new string[selectfiles.Length];
					for (int i = 0; i < selectfiles.Length; i++)
						AUTOLOADIMAGESFILES[i] = selectfiles[i];

					IMAGESET = new FITSImageSet();
					FMLoad_Click(new object(), new EventArgs());
					break;
				}
				case (DialogResult.Ignore)://for ADDING to existing IMAGESET
				{
					AddToImageSet(selectfiles, true);
					break;
				}
				default://ie no files selected at all
				{
					break;
				}
			}
		}

		private void ViewFoundList()
		{
			FITSFOUND = new JPFITS.FITSFound(FITSFINDERFILES);
			int numlines = FITSFINDERFILES.Length;

			if (numlines > 0)
			{
				FITSFOUND.ShowDialog();

				int Ninds = FITSFOUND.FileListTxt.SelectedIndices.Count;
				if (Ninds == 0 && FITSFOUND.DialogResult != DialogResult.Cancel)//no files selected but asked to load files (!cancel)
				{
					MessageBox.Show("No Files Selected!...", "Error");
					ViewFoundList();
					return;
				}

                string[] selectfiles = FITSFOUND.SelectedFiles;

                for (int j = 0; j < Ninds; j++)
					if (!File.Exists(selectfiles[j]))
					{
						MessageBox.Show("Some of the files don't exist on the specified path. The list file may be old: " + selectfiles[j], "Error...");
						ViewFoundList();
						return;
					}

				switch (FITSFOUND.DialogResult)
				{
					case (DialogResult.Cancel):
					{
						break;
					}
					case (DialogResult.OK)://for loading NEW IMAGESET
					{
						AUTOLOADIMAGES = true;
						AUTOLOADIMAGESFILES = new string[selectfiles.Length];
						for (int i = 0; i < selectfiles.Length; i++)
							AUTOLOADIMAGESFILES[i] = selectfiles[i];

						IMAGESET = new FITSImageSet();
						FMLoad_Click(new object(), new EventArgs());
						break;
					}
					case (DialogResult.Ignore)://for ADDING to existing IMAGESET
					{
						AddToImageSet(selectfiles, true);
						break;
					}
					default://ie no files selected at all
					{
						break;
					}
				}
			}
		}

		private void TBOpenFound_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "CCDLAB File List (*.CFL)|*.CFL";
			if (dlg.ShowDialog() == DialogResult.Cancel)
				return;

			string file = dlg.FileName;

			FileStream fs2 = new FileStream(file, System.IO.FileMode.Open, FileAccess.Read);
			StreamReader sr2 = new StreamReader(fs2);
			int numlines = Convert.ToInt32(sr2.ReadLine());

			string[] fullfiles = new string[numlines];
			for (int i = 0; i < numlines; i++)
				fullfiles[i] = sr2.ReadLine();

			sr2.Close();
			fs2.Close();
			TBViewFound.Enabled = true;
			FMViewFound.Enabled = true;

			FITSFINDERFILES = fullfiles;

			ViewFoundList();
		}

		private void FMExtendizeImageLayerStack_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			ofd.Filter = "FITS|*.fits;*.fit;*.fts;|All|*.*";
			ofd.FilterIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "FilterIndex"));
			ofd.Multiselect = false;
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			FITSImageSet set = FITSImageSet.ReadPrimaryImageCubeAsSet(ofd.FileName);

			FITSImageExtensionsSaver fies = new FITSImageExtensionsSaver(set);
			fies.ShowDialog();
		}

		private void SingleOutBtn_Click(object sender, EventArgs e)
		{
			JPFITS.FITSImage tmp = IMAGESET[IMAGESETINDEX];
			IMAGESET.Clear();
			IMAGESET.Add(tmp);
			AUTOLOADIMAGES = true;
			AUTOLOADIMAGESFILES = new string[1] { "SingleOut" };
			FMLoad_Click(sender, e);
		}

		private void FMLoad_Click(object sender, EventArgs e)
		{
			FMLoad.HideDropDown();
			FileMenu.HideDropDown();
			if (LOADSUBRANGE == false)
				SUBRANGE[0] = -1;
			else
				LOADSUBRANGE = false;//forget why
						
			string[] filenames;

			if (!AUTOLOADIMAGES)
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
				ofd.Filter = "FITS|*.fits;*.fit;*.fts;|All|*.*";
				ofd.FilterIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "FilterIndex"));
				ofd.Multiselect = true;
				if (ofd.ShowDialog() == DialogResult.Cancel)
					return;
				filenames = ofd.FileNames;
				REG.SetReg("CCDLAB", "FilterIndex", ofd.FilterIndex.ToString());

				if (filenames.Length == 1)
				{
					FITSImage check = new FITSImage(filenames[0], null, true, false, false, false);

					if (Convert.ToInt32(check.Header.GetKeyValue("NAXIS")) == 0)
					{
						string[] list = FITSBinTable.GetAllExtensionNames(ofd.FileName);

						if (list.Length > 0)
						{
							JPFITS.FitsBinTableViewer btv = new FitsBinTableViewer(ofd.FileName);
							btv.Show();
							return;
						}
					}

					else if (JPFITS.FITSImage.GetAllExtensionNames(ofd.FileName).Length > 0)
					{
						JPFITS.FITSImageExtensionsLister iel = new FITSImageExtensionsLister(ofd.FileName);

						if (iel.ShowDialog() == DialogResult.Cancel)
							return;

						IMAGESET = new JPFITS.FITSImageSet();

						if (iel.IncludePrimaryChck.Checked)
							IMAGESET.Add(new JPFITS.FITSImage(ofd.FileName, null, true, true, true, true));

						IMAGESET.LoadExtensions(ofd.FileName, iel.ExtensionIndexesOneBased, null, true, "Loading extensions");

						AUTOLOADIMAGES = true;
						AUTOLOADIMAGESFILES = new string[] { "SingleOut" };
						FMLoad_Click(iel, new EventArgs());
						return;
					}

					else if (Convert.ToInt32(check.Header.GetKeyValue("NAXIS")) == 3)
					{
						IMAGESET = FITSImageSet.ReadPrimaryImageCubeAsSet(filenames[0]);
						filenames = new string[1] { "SingleOut" };
					}
				}
				if (filenames[0] != "SingleOut")
					IMAGESET = new FITSImageSet();
			}
			else
				filenames = AUTOLOADIMAGESFILES;

			REG.SetReg("CCDLAB", "OpenFilesPath", Path.GetDirectoryName(filenames[0]));

			if (filenames[0] != "SingleOut")
			{
				int ind = filenames[0].LastIndexOf("\\");
				string dir = filenames[0].Substring(0, ind);
				REG.SetReg("CCDLAB", "OpenFilesPath", dir);
				UVOpenRawDlg.InitialDirectory = dir;
				UVOpenDirDlg.SelectedPath = dir;

				if (!AUTOLOADIMAGES)
					IMAGESETINDEX = 0;
				else
				{
					if (IMAGESET == null || IMAGESET.Count == 0)
						IMAGESETINDEX = 0;
					else
						IMAGESETINDEX = FileListDrop.Items.Count;
					AUTOLOADIMAGES = false;
				}

				if (!IMAGESET.Load(filenames, SUBRANGE, true, OptionsHardDiskPerformanceExtremeChck.Checked, "Loading Images"))
					return;
			}
			else
			{
				IMAGESETINDEX = 0;
				AUTOLOADIMAGES = false;
			}

			FileListDrop.Items.Clear();
			FileListDrop.Items.AddRange(IMAGESET.FileNames);

			if (Convert.ToInt32(REG.GetReg("CCDLAB", "FilterIndex")) == 2)//UVIT *.raw
			{
				UVOpenRawBtn.Enabled = true;
				UVOpenDirBtn.Enabled = true;
				UVOpenSubDirChck.Enabled = true;
			}

			if (IMAGESET.Count > 1)
			{
				BatchViewPanel.Enabled = true;
				TBSaveBatch.Enabled = true;
				TBSaveBatchOver.Enabled = true;
				TBSaveSetExtensions.Enabled = true;
				TBZipAllBtn.Enabled = true;
				BatchCorrectionChck.Checked = true;
				BatchCorrectionChck.Enabled = true;
				ImageBatchRedxnPnl.Enabled = true;
				HCInsertBatch.Enabled = true;
				HCRemoveBatch.Enabled = true;
				HCEditAll.Enabled = true;
			}
			else
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				BatchCorrectionChck.Checked = false;
				BatchCorrectionChck.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
				HCEditAll.Enabled = false;
			}

			//reset processing tab check boxes (and init others)
			MainTab.Enabled = true;
			ContrastPanel.Enabled = true;
			SubImagePanel.Enabled = true;
			FMAdd.Enabled = true;
			TBAdd.Enabled = true;
			FMReload.Enabled = true;
			TBReload.Enabled = true;
			TBSave.Enabled = true;
			TBSaveOver.Enabled = true;
			FMSave.Enabled = true;
			FMSaveBatch.Enabled = true;
			ViewHeaderBtn.Enabled = true;
			SubImageSlideX.Enabled = true;
			SubImageSlideY.Enabled = true;

			ImageWindow.ContextMenuStrip = ImageWindowCntxt;
			SubImageWindow.ContextMenuStrip = SubImageCntxt;

			SubBiasChck.Checked = false;
			MultImgChck.Checked = false;
			AddImageChck.Checked = false;
			DivFlatChck.Checked = false;
			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;
			System.GC.Collect();

			FileListDrop.SelectedIndex = IMAGESETINDEX;
			RecentFilesUpD();
		}

		private void FMAdd_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");

			OpenFileDialog afd = new OpenFileDialog();
			afd.InitialDirectory = dir;
			afd.Multiselect = true;
			afd.Filter = "FITS|*.fits;*.fit;*.fts|UVIT FITS|*.raw";
			afd.FilterIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "FilterIndex"));
			if (afd.ShowDialog() == DialogResult.Cancel)
				return;
			REG.SetReg("CCDLAB", "FilterIndex", afd.FilterIndex.ToString());

			AUTOLOADIMAGES = true;
			AUTOLOADIMAGESFILES = afd.FileNames;
			FMLoad_Click(sender, e);
		}

		private void RecentFilesUpD()
		{
			//check that all files exists and remove if not
			string[] recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
			for (int i = 0; i < recentlists.Length; i++)
			{
				StreamReader sr = new StreamReader(recentlists[i]);
				int numlines = Convert.ToInt32(sr.ReadLine());
				for (int j = 0; j < numlines; j++)
					if (!File.Exists(sr.ReadLine()))
					{
						sr.Close();
						File.Delete(recentlists[i]);
						break;
					}
				sr.Close();
			}

			if (!FIRSTLOAD)
			{
				//first find the recentfileslists and create/modify as needed
				recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");

				for (int i = recentlists.Length - 1; i >= 0; i--)
				{
					string file = recentlists[i];
					File.Move(file, file.Replace("_" + i.ToString("00"), "_" + (i + 1).ToString("00")));
				}

				if (!CLEAREDRECENT)
				{
					FileStream fs = new FileStream(CCDLABPATH_USERAPPDATAROAMING + "recentfileslist_00.txt", System.IO.FileMode.Create, FileAccess.Write);
					StreamWriter sw = new StreamWriter(fs);
					sw.WriteLine(IMAGESET.Count);
					for (int i = 0; i < IMAGESET.Count; i++)
						sw.WriteLine(IMAGESET[i].FullFileName);
					sw.Flush();
					fs.Flush();
					sw.Close();
					fs.Close();				

					//if there are more lists than RECENTFILESLISTLENGTH, then delete the oldest one and rename/move up the previous ones
					recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
					if (recentlists.Length > RECENTFILESLISTLENGTH)
						for (int i = RECENTFILESLISTLENGTH; i < recentlists.Length; i++)
							if (File.Exists(CCDLABPATH_USERAPPDATAROAMING + "recentfileslist_" + i.ToString("00") + ".txt"))
								File.Delete(CCDLABPATH_USERAPPDATAROAMING + "recentfileslist_" + i.ToString("00") + ".txt");

					//should go through the recent lists and check for duplicates...and delete all older dupes
					recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
					FileInfo fi0 = new FileInfo(recentlists[0]);
					byte[] fc0 = File.ReadAllBytes(recentlists[0]);

					bool dupe = false;
					for (int j = 1; j < recentlists.Length; j++)
					{
						FileInfo fij = new FileInfo(recentlists[j]);
						if (fi0.Length != fij.Length)
							continue;

						byte[] fcj = File.ReadAllBytes(recentlists[j]);
						int i = 0;
						for (i = 0; i < fcj.Length; i++)
							if (fcj[i] != fc0[i])
								break;
						if (i == fcj.Length)
							i--;
						if (fcj[i] != fc0[i])
							continue;

						File.Delete(recentlists[j]);
						dupe = true;
					}				

					if (dupe)
					{
						recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
						for (int i = 0; i < recentlists.Length; i++)
							File.Move(recentlists[i], CCDLABPATH_USERAPPDATAROAMING + "recentfileslist_" + i.ToString("00") + ".txt");
					}
				}
			}

			recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
			ToolStripButton[] tsbc = new ToolStripButton[recentlists.Length];

			for (int i = 0; i < recentlists.Length; i++)
			{
				StreamReader sr2 = new StreamReader(recentlists[i]);
				int numlines = Convert.ToInt32(sr2.ReadLine());
				string file;

				if (numlines == 1)
				{
					file = sr2.ReadLine();
					tsbc[i] = new ToolStripButton("{" + File.GetLastWriteTime(recentlists[i]).ToString() + "}" + " " + file.Substring(1 + file.LastIndexOf("\\")));
					tsbc[i].ToolTipText = file.Substring(0, file.LastIndexOf("\\") + 1);
				}
				else
				{
					file = sr2.ReadLine();
					string dircomparestr = file;
					string tooltipstr = file.Substring(1 + file.LastIndexOf("\\")) + "\r\n";
					for (int j = 1; j < numlines; j++)
					{
						file = sr2.ReadLine();
						tooltipstr += file.Substring(1 + file.LastIndexOf("\\")) + "\r\n";
						for (int k = 0; k < dircomparestr.Length; k++)
							if (dircomparestr[k] != file[k])
							{
								dircomparestr = file.Substring(0, k + 1);
								break;
							}
						if (j > 50)
						{
							tooltipstr += "... + " + (numlines - j) + " more...";
							break;
						}
					}
					dircomparestr = dircomparestr.Substring(0, 1 + dircomparestr.LastIndexOf("\\"));
					tsbc[i] = new ToolStripButton("{" + File.GetLastWriteTime(recentlists[i]).ToString() + "}" + " " + dircomparestr + " (" + numlines + ")");
					tsbc[i].ToolTipText = tooltipstr;
				}
				sr2.Close();
				tsbc[i].Tag = recentlists[i];
				tsbc[i].Width = tsbc[i].Text.Length * 6;
				tsbc[i].MouseDown += new MouseEventHandler(RecentFilesLoadSingle_Click);
			}
			TBRecentFiles.DropDownItems.Clear();
			TBRecentFiles.DropDownItems.AddRange(tsbc);

			if (recentlists.Length != 0)
			{
				ToolStripButton clearall = new ToolStripButton("Clear History");
				clearall.Width = clearall.Width * 3;
				clearall.MouseDown += new MouseEventHandler(RecentFilesClear_Click);
				TBRecentFiles.DropDownItems.Add(clearall);
			}
			else
			{
				ToolStripButton empty = new ToolStripButton("No History...");
				empty.Width = empty.Width * 3;
				empty.Enabled = false;
				TBRecentFiles.DropDownItems.Add(empty);
			}
		}

		private void RecentFilesClear_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to clear the file history?", "Warning", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
				return;

			string[] recentlists = Directory.GetFiles(CCDLABPATH_USERAPPDATAROAMING, "*recentfileslist_*.txt");
			foreach (string file in recentlists)
				File.Delete(file);

			CLEAREDRECENT = true;
			RecentFilesUpD();
			CLEAREDRECENT = false;

			TBRecentFiles.HideDropDown();
		}

		private void SCMUpD_ValueChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "SCMUpD", SCMUpD.Value);
		}

		private void RecentFilesLoadAll_DoubleClick(object sender, EventArgs e)
		{
		}

		private void RecentFilesLoadSingle_Click(object sender, MouseEventArgs e)
		{
			string recentfilelist = (string)((ToolStripButton)sender).Tag;
			StreamReader sr2 = new StreamReader(recentfilelist);
			int numlines = Convert.ToInt32(sr2.ReadLine());
			AUTOLOADIMAGESFILES = new string[numlines];
			for (int i = 0; i < numlines; i++)
				AUTOLOADIMAGESFILES[i] = sr2.ReadLine();
			sr2.Close();

			for (int i = 0; i < numlines; i++)
				if (!File.Exists(AUTOLOADIMAGESFILES[i]))
				{
					MessageBox.Show("File: " + AUTOLOADIMAGESFILES[i] + " doesn't exist...  Stopping and removing recent file name from recents list.", "Error...", MessageBoxButtons.OK);
					File.Delete(recentfilelist);
					RecentFilesUpD();
					return;
				}

			TBRecentFiles.HideDropDown();

			if (e.Button == MouseButtons.Left)//load images
			{
				if (AUTOLOADIMAGESFILES.Length == 1)
					if (MessageBox.Show("Are you sure you would like to LOAD " + AUTOLOADIMAGESFILES[0], "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;
				if (AUTOLOADIMAGESFILES.Length > 1)
					if (MessageBox.Show("Are you sure you would like to LOAD all " + numlines + " images from " + File.GetLastWriteTime(recentfilelist).ToString(), "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;
				IMAGESET = new FITSImageSet();
				AUTOLOADIMAGES = true;
				FMLoad_Click(sender, e);
			}

			if (e.Button == MouseButtons.Right)//add images
			{
				if (AUTOLOADIMAGESFILES.Length == 1)
					if (MessageBox.Show("Are you sure you would like to ADD " + AUTOLOADIMAGESFILES[0], "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;
				if (AUTOLOADIMAGESFILES.Length > 1)
					if (MessageBox.Show("Are you sure you would like to ADD all " + numlines + " images from " + File.GetLastWriteTime(recentfilelist).ToString(), "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;
				AUTOLOADIMAGES = true;
				FMLoad_Click(sender, e);
			}
		}

		public void AddToImageSet(string[] fullpathlist, bool updateRecent)
		{
			FITSImage tblcheck = new FITSImage(fullpathlist[0], null, true, false, false, false);
			if (Convert.ToInt32(tblcheck.Header.GetKeyValue("NAXIS")) == 0)
			{
				string[] list = FITSBinTable.GetAllExtensionNames(fullpathlist[0]);

				if (list.Length > 0)
				{
					JPFITS.FitsBinTableViewer btv = new FitsBinTableViewer(fullpathlist[0]);
					btv.Show();
					return;
				}

				if (JPFITS.FITSImage.GetAllExtensionNames(fullpathlist[0]).Length > 0)
				{
					JPFITS.FITSImageExtensionsLister iel = new FITSImageExtensionsLister(fullpathlist[0]);

					if (iel.ShowDialog() == DialogResult.Cancel)
						return;

					IMAGESET = new JPFITS.FITSImageSet();

					if (iel.IncludePrimaryChck.Checked)
						IMAGESET.Add(new JPFITS.FITSImage(fullpathlist[0], null, true, true, true, true));

					IMAGESET.LoadExtensions(fullpathlist[0], iel.ExtensionIndexesOneBased, null, true, "Loading extensions");

					AUTOLOADIMAGES = true;
					AUTOLOADIMAGESFILES = new string[] { "SingleOut" };
					FMLoad_Click(iel, new EventArgs());
					return;
				}
			}
			else if (Convert.ToInt32(tblcheck.Header.GetKeyValue("NAXIS")) == 3)
			{
				IMAGESET = FITSImageSet.ReadPrimaryImageCubeAsSet(fullpathlist[0]);
				fullpathlist = new string[0];
			}

			int c = FileListDrop.Items.Count;

			if (!UVREGISTRATION)
				ProgressBar.Maximum = fullpathlist.Length;

			for (int i = 0; i < fullpathlist.Length; i++)
			{
				if (!UVREGISTRATION)
				{
					ProgressBar.Value++;
					ProgressBar.Refresh();
				}

				JPFITS.FITSImage f = new FITSImage(fullpathlist[i], SUBRANGE, true, true, true, true);
				IMAGESET.Add(f);
			}

			if (!UVREGISTRATION)
				ProgressBar.Value = 0;

			FileListDrop.Items.Clear();
			FileListDrop.Items.AddRange(IMAGESET.FileNames);

			if (Convert.ToInt32(REG.GetReg("CCDLAB", "FilterIndex")) == 2)//UVIT *.raw
			{
				UVOpenRawBtn.Enabled = true;
				UVOpenDirBtn.Enabled = true;
				UVOpenSubDirChck.Enabled = true;
			}

			if (IMAGESET.Count > 1)//needed to add this due to adding image via found file list
			{
				BatchViewPanel.Enabled = true;
				TBSaveBatch.Enabled = true;
				TBSaveBatchOver.Enabled = true;
				TBSaveSetExtensions.Enabled = true;
				TBZipAllBtn.Enabled = true;
				BatchCorrectionChck.Checked = true;
				BatchCorrectionChck.Enabled = true;
				ImageBatchRedxnPnl.Enabled = true;
				HCInsertBatch.Enabled = true;
				HCRemoveBatch.Enabled = true;
			}
			else
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				BatchCorrectionChck.Checked = false;
				BatchCorrectionChck.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
			}

			//reset processing tab check boxes (and init others)
			MainTab.Enabled = true;
			ContrastPanel.Enabled = true;
			SubImagePanel.Enabled = true;
			FMAdd.Enabled = true;
			TBAdd.Enabled = true;
			FMReload.Enabled = true;
			TBReload.Enabled = true;
			TBSave.Enabled = true;
			TBSaveOver.Enabled = true;
			FMSave.Enabled = true;
			FMSaveBatch.Enabled = true;
			ViewHeaderBtn.Enabled = true;
			SubImageSlideX.Enabled = true;
			SubImageSlideY.Enabled = true;
			ImageWindow.ContextMenuStrip = ImageWindowCntxt;
			SubImageWindow.ContextMenuStrip = SubImageCntxt;

			SubBiasChck.Checked = false;
			MultImgChck.Checked = false;
			AddImageChck.Checked = false;
			DivFlatChck.Checked = false;
			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;

			FileListDrop.SelectedIndex = c;

			if (updateRecent)
				RecentFilesUpD();

			System.GC.Collect();

			if (UVREGISTRATION)
			{
				try
				{
					File.Delete(fullpathlist[0]);
				}
				catch { }
			}
		}

		public void ImageUpD(double[,] image)
		{
			int scaling = ContrastScaleDrop.SelectedIndex;
			int colour = ColourMapDrop.SelectedIndex;
			bool invert = InvertContrastChck.Checked;
			SetContrast();
			IMAGEBMP = JPBitMap.ArrayToBmp(image, scaling, colour, invert, DIMCLIM, ImageWindow.Size.Width, ImageWindow.Size.Height, OPTIMGVIEWINVERTY);
			ImageWindow.Refresh();
		}

		[MethodImpl(256)]
		public void SubImageUpD()
		{
			bool invert = InvertContrastChck.Checked;
			int scaling = ContrastScaleDrop.SelectedIndex;
			int colour = ColourMapDrop.SelectedIndex;
			bool matchscale = ScaleContrastChck.Checked;

			if (!matchscale)
			{
				double[] lims = new double[] { SUBIMAGEMIN, SUBIMAGEMAX };
				SUBIMAGEBMP = JPBitMap.ArrayToBmp(SUBIMAGE, 0, 0, false, lims, SubImageWindow.Size.Width, SubImageWindow.Size.Height, OPTIMGVIEWINVERTY);
			}
			else
			{
				SUBIMAGEBMP = JPBitMap.ArrayToBmp(SUBIMAGE, scaling, colour, invert, DIMCLIM, SubImageWindow.Size.Width, SubImageWindow.Size.Height, OPTIMGVIEWINVERTY);
			}
			SubImageWindow.Refresh();
		}

		[MethodImpl(256)]
		public void SubImageStatsUpD()
		{			
			SUBIMAGESUM = 0.0;
			SUBIMAGEMIN = System.Double.MaxValue;
			SUBIMAGEMAX = System.Double.MinValue;
			SUBIMAGEMEDIAN = 0.0;
			SUBIMAGEMEAN = 0.0;
			SUBIMAGESTD = 0.0;

			SUBIMAGE_HWX = (int)HalfWidthXUpD.Value;			
			SUBIMAGE_HWY = (int)HalfWidthYUpD.Value;
			int sihwt2p1X = SUBIMAGE_HWX * 2 + 1;
			int sihwt2p1Y = SUBIMAGE_HWY * 2 + 1;
			if (XSUBRANGE.Length != sihwt2p1X)
				XSUBRANGE = new int[sihwt2p1X];
			if (YSUBRANGE.Length != sihwt2p1Y)
				YSUBRANGE = new int[sihwt2p1Y];
			if (SUBIMAGE == null || SUBIMAGE.GetLength(0) != XSUBRANGE.Length || SUBIMAGE.GetLength(1) != YSUBRANGE.Length)
			{
				SUBIMAGE = new double[sihwt2p1X, sihwt2p1Y];
				SUBIMAGEBMP = new Bitmap(sihwt2p1X, sihwt2p1Y, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
			}

			int x = SubImageSlideX.Value - 1;
			int y = SubImageSlideY.Value - 1;

			if (x < SUBIMAGE_HWX)
				x = SUBIMAGE_HWX;
			if (y < SUBIMAGE_HWY)
				y = SUBIMAGE_HWY;
			if (x > IMAGESET[IMAGESETINDEX].Width - SUBIMAGE_HWX - 1)
				x = IMAGESET[IMAGESETINDEX].Width - SUBIMAGE_HWX - 1;
			if (y > IMAGESET[IMAGESETINDEX].Height - SUBIMAGE_HWY - 1)
				y = IMAGESET[IMAGESETINDEX].Height - SUBIMAGE_HWY - 1;
			
			for (int k = 0; k < sihwt2p1X; k++)
				XSUBRANGE[k] = x - SUBIMAGE_HWX + k;
			
			for (int k = 0; k < sihwt2p1Y; k++)
				YSUBRANGE[k] = y - SUBIMAGE_HWY + k;

			SubImageXTxt.Text = (XSUBRANGE[SUBIMAGE_HWX] + 1).ToString();
			SubImageYTxt.Text = (YSUBRANGE[SUBIMAGE_HWY] + 1).ToString();

			if (IMAGESET[IMAGESETINDEX].WCS.Exists())
			{
				double cval1, cval2;
				string sx1;
				string sx2;
				IMAGESET[IMAGESETINDEX].WCS.Get_Coordinate((double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], true, "TAN", out cval1, out cval2, out sx1, out sx2);
				sx1 = sx1.Replace(" ", "");
				sx2 = sx2.Replace(" ", "");
				if (sx1.Contains("."))
					sx1 = sx1.Substring(0, sx1.LastIndexOf(".") + 2);
				if (sx2.Contains("."))
					sx2 = sx2.Substring(0, sx2.LastIndexOf(".") + 2);
				SubImageRATxt.Text = sx1;
				SubImageDecTxt.Text = sx2;
			}

			var rangePartitioner = Partitioner.Create(0, sihwt2p1X);
			object locker = new object();

			Parallel.ForEach(rangePartitioner, (range, loopState) =>
			{
				double sum = 0;
				double mx = System.Double.MinValue;
				double mn = System.Double.MaxValue;

				for (int i = range.Item1; i < range.Item2; i++)
					for (int j = 0; j < sihwt2p1Y; j++)
					{
						SUBIMAGE[i, j] = IMAGESET[IMAGESETINDEX][XSUBRANGE[i], YSUBRANGE[j]];
						sum += SUBIMAGE[i, j];

						if (SUBIMAGE[i, j] < mn)
						{
							lock (locker)
							{
								if (SUBIMAGE[i, j] < mn)
									mn = SUBIMAGE[i, j];
							}
						}
						if (SUBIMAGE[i, j] > mx)
						{
							lock (locker)
							{
								if (SUBIMAGE[i, j] > mx)
									mx = SUBIMAGE[i, j];
							}
						}
					}

				lock (locker)
				{
					SUBIMAGESUM += sum;
					SUBIMAGEMIN = Math.Min(SUBIMAGEMIN, mn);
					SUBIMAGEMAX = Math.Max(SUBIMAGEMAX, mx);
				}
			});

			SUBIMAGEMEAN = SUBIMAGESUM / (double)(SUBIMAGE.Length);
			SUBIMAGEMEDIAN = JPMath.Median(SUBIMAGE);

			Parallel.ForEach(rangePartitioner, (range, loopState) =>
			{
				double std = 0;

				for (int i = range.Item1; i < range.Item2; i++)
					for (int j = 0; j < sihwt2p1Y; j++)
						std += (SUBIMAGE[i, j] - SUBIMAGEMEAN) * (SUBIMAGE[i, j] - SUBIMAGEMEAN);

				lock (locker)
				{
					SUBIMAGESTD += std;
				}
			});
			SUBIMAGESTD = Math.Sqrt(SUBIMAGESTD / ((double)(SUBIMAGE.Length) - 1.0));

			SubImageSumTxt.Text = SUBIMAGESUM.ToString();
			SubImageMinTxt.Text = SUBIMAGEMIN.ToString();
			SubImageMaxTxt.Text = SUBIMAGEMAX.ToString();
			SubImageMeanTxt.Text = SUBIMAGEMEAN.ToString();
			SubImageMedianTxt.Text = SUBIMAGEMEDIAN.ToString();
			SubImageStdTxt.Text = SUBIMAGESTD.ToString();
		}

		private void StatTxtsUpD()
		{
			ImageSumTxt.Text = IMAGESET[IMAGESETINDEX].Sum.ToString();
			ImageMinTxt.Text = IMAGESET[IMAGESETINDEX].Min.ToString();
			ImageMaxTxt.Text = IMAGESET[IMAGESETINDEX].Max.ToString();
			ImageMeanTxt.Text = IMAGESET[IMAGESETINDEX].Mean.ToString();
			ImageMedianTxt.Text = IMAGESET[IMAGESETINDEX].Median.ToString();
			ImageStdTxt.Text = IMAGESET[IMAGESETINDEX].Stdv.ToString();
			ImageSizeTxt.Text = String.Concat(IMAGESET[IMAGESETINDEX].Width.ToString(), "x", IMAGESET[IMAGESETINDEX].Height.ToString());

			//ImageSumTxt.Text = FormatNumber(IMAGESET[IMAGESETINDEX].Sum);
			//ImageMinTxt.Text = FormatNumber(IMAGESET[IMAGESETINDEX].Min);
			//ImageMaxTxt.Text = FormatNumber(IMAGESET[IMAGESETINDEX].Max);
			//ImageMeanTxt.Text = FormatNumber(IMAGESET[IMAGESETINDEX].Mean);
			//ImageMedianTxt.Text = FormatNumber(IMAGESET[IMAGESETINDEX].Median);
			//ImageStdTxt.Text = FormatNumber(IMAGESET[IMAGESETINDEX].Stdv);
			//ImageSizeTxt.Text = String.Concat(IMAGESET[IMAGESETINDEX].Width.ToString(), "x", IMAGESET[IMAGESETINDEX].Height.ToString());
		}

		private string FormatNumber(double val)
		{
			if (val == 0)
				return "0";

			if (Math.Abs(val) <= 1e-4 || Math.Abs(val) >= 1e4)
				return val.ToString("0.###e+00");
			else
				return val.ToString("0.###");
		}

		private void FileTxtsUpD()
		{
			this.Text = IMAGESET[IMAGESETINDEX].FullFileName;
			
			try
			{
				FileDirectoryTxt.Text = ".." + Directory.GetParent(Directory.GetParent(IMAGESET[IMAGESETINDEX].FilePath).FullName).Name + "\\" + Directory.GetParent(IMAGESET[IMAGESETINDEX].FullFileName).Name;
			}
			catch { }
			FileDirectoryTxt.Tag = IMAGESET[IMAGESETINDEX].FilePath;
			Tooltip.SetToolTip(FileDirectoryTxt, IMAGESET[IMAGESETINDEX].FilePath);
			FileNameTxt.Text = IMAGESET[IMAGESETINDEX].FileName;
			InfoTxt1.Text = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(InfoStatic1.Text.Substring(0, InfoStatic1.Text.IndexOf(':')));
			InfoTxt2.Text = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(InfoStatic2.Text.Substring(0, InfoStatic2.Text.IndexOf(':')));
			InfoTxt3.Text = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(InfoStatic3.Text.Substring(0, InfoStatic3.Text.IndexOf(':')));
			InfoTxt4.Text = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(InfoStatic4.Text.Substring(0, InfoStatic4.Text.IndexOf(':')));
			InfoTxt5.Text = IMAGESET[IMAGESETINDEX].Header.GetKeyValue(InfoStatic5.Text.Substring(0, InfoStatic5.Text.IndexOf(':')));

			if (ViewHeaderBtn.Checked)
			{
				int ind = HeaderTxt.TopIndex;
				string key = IMAGESET[OLD_INDEX].Header.GetKeyName(ind);
				int c = HeaderTxt.SelectedIndices.Count;
				string[] keys = new string[c];
				for (int i = 0; i < c; i++)
					keys[i] = (string)HeaderTxt.Items[HeaderTxt.SelectedIndices[i]];

				HeaderTxt.BeginUpdate();
				HeaderTxt.Items.Clear();
				HeaderTxt.Items.AddRange(IMAGESET[IMAGESETINDEX].Header.GetFormattedHeaderBlock(FITSHeader.HeaderUnitType.Primary, true));
				ind = IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(key, false);
				HeaderTxt.TopIndex = ind;

				for (int i = 0; i < c; i++)
				{
					int indx = IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(keys[i], false);
					HeaderTxt.SelectedIndex = indx;
				}

				HeaderTxt.EndUpdate();
			}
		}

		private void ViewHeaderBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (ViewHeaderBtn.Checked == true)
			{
				FileTxtsUpD();
				HeaderTxt.BringToFront();
				HeaderTxt.Visible = true;

				//JPFITS.FITSHeaderViewer FHV = new FITSHeaderViewer(IMAGESET, FILELISTINDEX);
				//FHV.TopMost = true;
				//FHV.Show();
			}
			else
			{
				HeaderTxt.Visible = false;
				ImageWindow.Refresh();
			}
		}

		private void FileDirectoryTxt_DoubleClick(object sender, EventArgs e)
		{
			Process.Start("Explorer.exe", (string)FileDirectoryTxt.Tag);
		}

		private void Form1ProgUpD()
		{
			ProgressBar.Value++;
			ProgressBar.Refresh();
		}

		private void ColourMapDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (IMAGESET.Count > 0)
			{
				int width = IMAGESET[IMAGESETINDEX].Width;
				int height = IMAGESET[IMAGESETINDEX].Height;
				SubImageSlideX.Maximum = width;
				SubImageSlideY.Maximum = height;				
				FileTxtsUpD();
				StatTxtsUpD();
				SubImageStatsUpD();
				SubImageUpD();
				ImageUpD(IMAGESET[IMAGESETINDEX].Image);
			}
		}

		private void MinContrastSlider_MouseWheel(object sender, MouseEventArgs e)
		{
			//dont need to put anything here because _Scroll does it already
		}

		private void MaxContrastSlider_MouseWheel(object sender, MouseEventArgs e)
		{
			//dont need to put anything here because _Scroll does it already
		}

		private void MinContrastCountTxt_KeyUp(object sender, KeyEventArgs e)
		{
			e.SuppressKeyPress = true;

			if (e.KeyCode != Keys.Enter)
				return;

			try
			{
				double min = Convert.ToDouble(MinContrastCountTxt.Text);
				double max = Convert.ToDouble(MaxContrastCountTxt.Text);

				if (min >= max)
				{
					MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 3).ToString();
					return;
				}

				double std = IMAGESET[IMAGESETINDEX].Stdv;
				double mean = IMAGESET[IMAGESETINDEX].Mean;

				DIMCLIM[0] = min;
				IMSTDLIM[0] = (min - mean) / std;

				CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

				MinContrastSlider.Value = 1;

				ImageUpD(IMAGESET[IMAGESETINDEX].Image);
				SubImageUpD();

				ContrastWideRad.Checked = false;
				ContrastFullRad.Checked = false;
				ContrastNarrowRad.Checked = false;

				MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
				MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
				MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
				MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			}
			catch
			{
			}
		}

		private void MaxContrastCountTxt_KeyUp(object sender, KeyEventArgs e)
		{
			e.SuppressKeyPress = true;

			if (e.KeyCode != Keys.Enter)
				return;

			try
			{
				double min = Convert.ToDouble(MinContrastCountTxt.Text);
				double max = Convert.ToDouble(MaxContrastCountTxt.Text);

				if (min >= max)
				{
					MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 3).ToString();
					return;
				}

				double std = IMAGESET[IMAGESETINDEX].Stdv;
				double mean = IMAGESET[IMAGESETINDEX].Mean;

				DIMCLIM[1] = max;
				IMSTDLIM[1] = (max - mean) / std;

				CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

				MaxContrastSlider.Value = 300;

				ImageUpD(IMAGESET[IMAGESETINDEX].Image);
				SubImageUpD();

				ContrastWideRad.Checked = false;
				ContrastFullRad.Checked = false;
				ContrastNarrowRad.Checked = false;

				MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
				MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
				MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
				MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			}
			catch
			{
			}
		}

		private void MinContrastStdTxt_KeyUp(object sender, KeyEventArgs e)
		{
			e.SuppressKeyPress = true;

			if (e.KeyCode != Keys.Enter)
				return;

			try
			{
				double min = Convert.ToDouble(MinContrastStdTxt.Text);
				double max = Convert.ToDouble(MaxContrastStdTxt.Text);

				if (min >= max)
				{
					MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 3).ToString();
					return;
				}

				double std = IMAGESET[IMAGESETINDEX].Stdv;
				double mean = IMAGESET[IMAGESETINDEX].Mean;

				IMSTDLIM[0] = min;
				DIMCLIM[0] = mean + min * std;

				CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

				MinContrastSlider.Value = 1;

				ImageUpD(IMAGESET[IMAGESETINDEX].Image);
				SubImageUpD();

				ContrastWideRad.Checked = false;
				ContrastFullRad.Checked = false;
				ContrastNarrowRad.Checked = false;

				MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
				MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
				MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
				MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			}
			catch
			{
			}
		}

		private void MaxContrastStdTxt_KeyUp(object sender, KeyEventArgs e)
		{
			e.SuppressKeyPress = true;

			if (e.KeyCode != Keys.Enter)
				return;

			try
			{
				double min = Convert.ToDouble(MinContrastStdTxt.Text);
				double max = Convert.ToDouble(MaxContrastStdTxt.Text);

				if (min >= max)
				{
					MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 3).ToString();
					return;
				}

				double std = IMAGESET[IMAGESETINDEX].Stdv;
				double mean = IMAGESET[IMAGESETINDEX].Mean;

				IMSTDLIM[1] = max;
				DIMCLIM[1] = mean + max * std;

				CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

				MaxContrastSlider.Value = 300;

				ImageUpD(IMAGESET[IMAGESETINDEX].Image);
				SubImageUpD();

				ContrastWideRad.Checked = false;
				ContrastFullRad.Checked = false;
				ContrastNarrowRad.Checked = false;

				MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
				MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
				MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
				MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			}
			catch
			{
			}
		}

		private void MinContrastSlider_Scroll(object sender, ScrollEventArgs e)
		{
			int val = MinContrastSlider.Value;
			MaxContrastSlider.Minimum = val;
			double std = IMAGESET[IMAGESETINDEX].Stdv;
			double mean = IMAGESET[IMAGESETINDEX].Mean;
			double delta = (double)(val - PREVMINCONTRASTVALUE);
			PREVMINCONTRASTVALUE = val;

			DIMCLIM[0] += delta * CTSperPERCENT;
			IMSTDLIM[0] = (DIMCLIM[0] - mean) / std;

			MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
			MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();

			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
			SubImageUpD();
		}

		private void MaxContrastSlider_Scroll(object sender, ScrollEventArgs e)
		{
			int val = MaxContrastSlider.Value;
			MinContrastSlider.Maximum = val;
			double std = IMAGESET[IMAGESETINDEX].Stdv;
			double mean = IMAGESET[IMAGESETINDEX].Mean;
			double delta = (double)(val - PREVMAXCONTRASTVALUE);
			PREVMAXCONTRASTVALUE = val;

			DIMCLIM[1] += delta * CTSperPERCENT;
			IMSTDLIM[1] = (DIMCLIM[1] - mean) / std;

			MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
			MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();

			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
			SubImageUpD();
		}

		private void ContrastWideRad_Click(object sender, EventArgs e)
		{
			double std = IMAGESET[IMAGESETINDEX].Stdv;
			double mean = IMAGESET[IMAGESETINDEX].Mean;//from image
			IMSTDLIM[0] = -0.5;//-1.0;
			IMSTDLIM[1] = 5.0;//2.0;
			DIMCLIM[0] = mean + IMSTDLIM[0] * std;
			DIMCLIM[1] = mean + IMSTDLIM[1] * std;

			MaxContrastSlider.Minimum = 1;
			MinContrastSlider.Maximum = 300;
			MaxContrastSlider.Value = 300;
			MinContrastSlider.Value = 1;

			CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

			MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
			MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
			MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
			MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
			SubImageUpD();
		}

		private void ContrastNarrowRad_Click(object sender, EventArgs e)
		{
			double std = IMAGESET[IMAGESETINDEX].Stdv;
			double mean = IMAGESET[IMAGESETINDEX].Mean;//from image
			IMSTDLIM[0] = -1.0;//-0.333333333;
			IMSTDLIM[1] = 2.0;//0.333333333;
			DIMCLIM[0] = mean + IMSTDLIM[0] * std;
			DIMCLIM[1] = mean + IMSTDLIM[1] * std;

			MaxContrastSlider.Minimum = 1;
			MinContrastSlider.Maximum = 300;
			MaxContrastSlider.Value = 300;
			MinContrastSlider.Value = 1;

			CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

			MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
			MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
			MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
			MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
			SubImageUpD();
		}

		private void ContrastFullRad_Click(object sender, EventArgs e)
		{
			double std = IMAGESET[IMAGESETINDEX].Stdv;
			double mean = IMAGESET[IMAGESETINDEX].Mean;//from image
			double min = IMAGESET[IMAGESETINDEX].Min;//from image
			double max = IMAGESET[IMAGESETINDEX].Max;//from image

			IMSTDLIM[0] = (min - mean) / std;
			IMSTDLIM[1] = (max - mean) / std;
			DIMCLIM[0] = min;
			DIMCLIM[1] = max;

			MaxContrastSlider.Minimum = 1;
			MinContrastSlider.Maximum = 300;
			MaxContrastSlider.Value = 300;
			MinContrastSlider.Value = 1;

			CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0]) / 300.0;

			MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
			MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
			MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
			MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
			ImageUpD(IMAGESET[IMAGESETINDEX].Image);
			SubImageUpD();
		}

		private void SetContrast()
		{
			if (AutoContrast.Checked)//keep contrast stdv limits fixed, change DIMCLIM
			{
				if (ContrastFullRad.Checked == true)
				{
					IMSTDLIM[0] = (IMAGESET[IMAGESETINDEX].Min - IMAGESET[IMAGESETINDEX].Mean) / IMAGESET[IMAGESETINDEX].Stdv;
					IMSTDLIM[1] = (IMAGESET[IMAGESETINDEX].Max - IMAGESET[IMAGESETINDEX].Mean) / IMAGESET[IMAGESETINDEX].Stdv;
					DIMCLIM[0] = IMAGESET[IMAGESETINDEX].Min;
					DIMCLIM[1] = IMAGESET[IMAGESETINDEX].Max;

					MinContrastStdTxt.Text = Math.Round(IMSTDLIM[0], 4).ToString();
					MaxContrastStdTxt.Text = Math.Round(IMSTDLIM[1], 4).ToString();
				}
				else
				{
					DIMCLIM[0] = IMAGESET[IMAGESETINDEX].Mean + IMSTDLIM[0] * IMAGESET[IMAGESETINDEX].Stdv;
					DIMCLIM[1] = IMAGESET[IMAGESETINDEX].Mean + IMSTDLIM[1] * IMAGESET[IMAGESETINDEX].Stdv;
				}

				MinContrastCountTxt.Text = Math.Round(DIMCLIM[0], 5).ToString();
				MaxContrastCountTxt.Text = Math.Round(DIMCLIM[1], 5).ToString();
			}
			else if (RelativeContrast.Checked)//keep DIMCLIM fixed, change contrast stdv limits
			{
				double stdmin = (DIMCLIM[0] - IMAGESET[IMAGESETINDEX].Mean) / IMAGESET[IMAGESETINDEX].Stdv;
				MinContrastStdTxt.Text = Math.Round(stdmin, 4).ToString();
				double stdmax = (DIMCLIM[1] - IMAGESET[IMAGESETINDEX].Mean) / IMAGESET[IMAGESETINDEX].Stdv;
				MaxContrastStdTxt.Text = Math.Round(stdmax, 4).ToString();
			}
		}

		private void ScanBtnContextMakeGifBtn_Click(object sender, EventArgs e)
		{
			BlinkChck.Checked = false;
			GIFFILE = "";

			SaveFileDialog sfd = new SaveFileDialog
			{
				Filter = "GIF|*.gif",
				InitialDirectory = IMAGESET[IMAGESETINDEX].FilePath,
				Title = "Save GIF"
			};

			if (sfd.ShowDialog() == DialogResult.Cancel)
				return;

			GIFFILE = sfd.FileName;
			FileListDrop.SelectedIndex = 0;
			BlinkChck.Checked = true;
		}

		private void BlinkChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BlinkChck.Checked)
			{
				if (GIFFILE != "")
					GIFWRITER = new GifWriter(GIFFILE, 25 , 0);

				MainTab.Enabled = false;
				double t = Convert.ToDouble(BlinkTime.Text);
				t = t * 1000;//convert sendonds to milliseconds  (.2*1000 = 200)
				int T;
				T = Convert.ToInt32(Math.Round(t));
				if (T < 1)
					T = 1;

				BlinkChck.Text = "Stop";
				BlinkChck.BackColor = Color.Red;
				BlinkTimer.Interval = T;
				BlinkTimer.Enabled = true;
			}
			else
			{
				MainTab.Enabled = true;
				BlinkTimer.Enabled = false;
				BlinkChck.Text = "Scan";
				BlinkChck.BackColor = Color.FromName(this.BackColor.ToString());//Gray;

				if (GIFFILE != "")
				{
					DialogResult res = MessageBox.Show("Open GIF file?" + Environment.NewLine + "Yes = Open File" + Environment.NewLine + "No = Open Directory", "View?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);

					if (res == DialogResult.No)
						Process.Start("Explorer.exe", (new DirectoryInfo(GIFFILE)).Parent.FullName);
					else if (res == DialogResult.Yes)
						Process.Start("Explorer.exe", GIFFILE);

					GIFFILE = "";
					GIFWRITER.Dispose();
				}
			}
		}

		private void BlinkTimer_Tick(object sender, EventArgs e)
		{
			if (GIFFILE != "")
			{
				Bitmap bmp = new Bitmap(ImageWindow.Width, ImageWindow.Height);
				ImageWindow.DrawToBitmap(bmp, ImageWindow.DisplayRectangle);
				GIFWRITER.WriteFrame(bmp, 25);

				if (IMAGESETINDEX == IMAGESET.Count - 1)
				{
					BlinkTimer.Enabled = false;
					BlinkChck.Checked = false;
				}
			}

			BlinkTimer.Interval = (int)(Convert.ToDouble(BlinkTime.Value) * 1000) + 1;//+1 to aprivate void 0, 1 = 1ms
			ViewNextBtn_Click(sender, e);
		}

		private void FileListDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			IMAGESETINDEX = FileListDrop.SelectedIndex;
			ViewSelectionStatic.Text = String.Concat("Image: ", (IMAGESETINDEX + 1).ToString(), " of ", IMAGESET.Count);

			int width = IMAGESET[IMAGESETINDEX].Width;
			int height = IMAGESET[IMAGESETINDEX].Height;
			SubImageSlideX.Maximum = width;
			SubImageSlideY.Maximum = height;
			HalfWidthXUpD.Maximum = (width - 1) / 2;
			HalfWidthYUpD.Maximum = (height - 1) / 2;

			if (FIRSTLOAD == true)
			{
				EqualHWChck.Checked = false;

				//check if first loaded image dimenson is identical to last exit and if so then set things there
				if (width == Convert.ToInt32(REG.GetReg("CCDLAB", "LastImageWidth")) && height == Convert.ToInt32(REG.GetReg("CCDLAB", "LastImageHeight")))
				{
					HalfWidthXUpD.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "SubImageHWX"));
					HalfWidthYUpD.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "SubImageHWY"));
					SubImageSlideX.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "SubImageSlideX"));
					SubImageSlideY.Value = Convert.ToInt32(REG.GetReg("CCDLAB", "SubImageSlideY"));
				}
				else
				{
					HalfWidthXUpD.Value = IMAGESET[IMAGESETINDEX].Width / 25;
					HalfWidthYUpD.Value = IMAGESET[IMAGESETINDEX].Height / 25;
					SubImageSlideX.Value = (int)Math.Ceiling((double)IMAGESET[IMAGESETINDEX].Width / 2);
					SubImageSlideY.Value = (int)Math.Ceiling((double)IMAGESET[IMAGESETINDEX].Height / 2);
				}

				if (HalfWidthXUpD.Value == HalfWidthYUpD.Value)
					EqualHWChck.Checked = true;
			}
			else//not a first load but subsequent, so figure out how to handle changes if any
			{
				FIRSTLOAD = true;
				if (OLD_WIDTH != width || OLD_HEIGHT != height)
				{
					SubImageSlideX.Value = (int)Math.Round((((double)(XSUBRANGE[SUBIMAGE_HWX]) / (double)(OLD_WIDTH) * (double)(width)))) + 1;
					SubImageSlideY.Value = (int)Math.Round((((double)(YSUBRANGE[SUBIMAGE_HWY]) / (double)(OLD_HEIGHT) * (double)(height)))) + 1;
					HalfWidthXUpD.Value = (int)Math.Round((((double)(HalfWidthXUpD.Value) / (double)(OLD_WIDTH)) * (double)(width)));
					HalfWidthYUpD.Value = (int)Math.Round((((double)(HalfWidthYUpD.Value) / (double)(OLD_HEIGHT)) * (double)(height)));
				}
			}

			if (SubImTrackPSChck.Checked)
			{
				int x = 0, y = 0;
				double max = JPMath.Max(SUBIMAGE, out x, out y, false);
				SubImageSlideX.Value = x + 1 + XSUBRANGE[0];
				SubImageSlideY.Value = y + 1 + YSUBRANGE[0];
				PRVXPOS_CURSOR = SubImageSlideX.Value - 1;
				PRVYPOS_CURSOR = SubImageSlideY.Value - 1;

				if (ImageWndwCntxtPlotRow.Checked)
					ROWplotUpD(false);
				if (ImageWndwCntxtPlotCol.Checked)
					COLplotUpD(false);
			}

			FIRSTLOAD = false;
			OLD_INDEX = IMAGESETINDEX;
			OLD_WIDTH = width;
			OLD_HEIGHT = height;

			FileTxtsUpD();
			StatTxtsUpD();
			SubImageStatsUpD();
			SubImageUpD();
			SpAxesUpD();
			ImageUpD(IMAGESET[IMAGESETINDEX].Image);

			if (ImageWndwCntxtPlotRow.Checked)
				ROWplotUpD(false);
			if (ImageWndwCntxtPlotCol.Checked)
				COLplotUpD(false);
			if (PLOTRADIALLINE)
				RADIALLINE_PLOTUpD();
		}

		private void DeleteFileBtn_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				if (MessageBox.Show("Are you sure you want to delete the file (to Recylce Bin)?", "WARNING!", MessageBoxButtons.YesNo) == DialogResult.No)
					return;
				else
					Microsoft.VisualBasic.FileIO.FileSystem.DeleteFile(IMAGESET[IMAGESETINDEX].FullFileName, Microsoft.VisualBasic.FileIO.UIOption.OnlyErrorDialogs, Microsoft.VisualBasic.FileIO.RecycleOption.SendToRecycleBin);
			}

			if (e.Button == MouseButtons.Right || e.Button == MouseButtons.Left)
			{
				int index = IMAGESETINDEX;
				IMAGESET.RemoveAt(index);
				FileListDrop.Items.RemoveAt(index);
				int C = FileListDrop.Items.Count;

				if (index == C)
					index = C - 1;
				if (C == 1)
				{
					BatchViewPanel.Enabled = false;
					TBSaveBatch.Enabled = false;
					TBSaveBatchOver.Enabled = false;
					TBSaveSetExtensions.Enabled = false;
					TBZipAllBtn.Enabled = false;
					ImageBatchRedxnPnl.Enabled = false;
					BatchCorrectionChck.Enabled = false;
					BatchCorrectionChck.Checked = false;
					HCInsertBatch.Enabled = false;
					HCRemoveBatch.Enabled = false;
					HCExtractKeyValue.Enabled = false;
					index = 0;
				}

				BatchMeanChck.Checked = false;
				BatchSumChck.Checked = false;
				BatchQuadratureChck.Checked = false;
				BatchMedianChck.Checked = false;
				BatchStdvChck.Checked = false;
				BatchMaximumChck.Checked = false;
				BatchMinimumChck.Checked = false;

				FileListDrop.SelectedIndex = index;
			}
		}

		private void DeleteFileBtn_MouseClick(object sender, MouseEventArgs e)
		{
		}

		private void DeleteFileBtn_Click(object sender, EventArgs e)
		{
		}

		private void MoveUpBtn_Click(object sender, EventArgs e)
		{
			int index = IMAGESETINDEX;
			FITSImage img1 = IMAGESET[index];
			int C = FileListDrop.Items.Count;
			string[] files = new string[C];

			if (index == 0) //then swap with end of list
			{
				FITSImage img2 = IMAGESET[C - 1];
				IMAGESET[index] = img2;
				IMAGESET[FileListDrop.Items.Count - 1] = img1;
				index = FileListDrop.Items.Count - 1;
			}
			else
			{
				FITSImage img2 = IMAGESET[index - 1];
				IMAGESET[index] = img2;
				IMAGESET[index - 1] = img1;
				index = index - 1;
			}

			FileListDrop.Items.Clear();
			for (int i = 0; i < C; i++)
			{
				files[i] = IMAGESET[i].FileName;
			}
			FileListDrop.Items.AddRange(files);
			FileListDrop.SelectedIndex = index;
		}

		private void MoveDownBtn_Click(object sender, EventArgs e)
		{
			int index = IMAGESETINDEX;
			FITSImage img1 = IMAGESET[index];
			int C = FileListDrop.Items.Count;
			string[] files = new string[C];

			if (index == FileListDrop.Items.Count - 1) //then swap with beginning of list
			{
				FITSImage img2 = IMAGESET[0];
				IMAGESET[index] = img2;
				IMAGESET[0] = img1;
				index = 0;
			}
			else
			{
				FITSImage img2 = IMAGESET[index + 1];
				IMAGESET[index] = img2;
				IMAGESET[index + 1] = img1;
				index = index + 1;
			}

			FileListDrop.Items.Clear();
			for (int i = 0; i < C; i++)
			{
				files[i] = IMAGESET[i].FileName;
			}
			FileListDrop.Items.AddRange(files);
			FileListDrop.SelectedIndex = index;
		}

		private void FindImagePtsBtn_Click(object sender, EventArgs e)
		{
			double val = Convert.ToDouble(FindImagePtsTxt.Text);
			ReplaceImagePtsTxt.Text = FindImagePtsTxt.Text;

			string style = FindPtsDrop.Items[FindPtsDrop.SelectedIndex].ToString();
			JPMath.Find(IMAGESET[IMAGESETINDEX].Image, val, style, true, out FNDCOORDS_X, out FNDCOORDS_Y);
			if (FNDCOORDS_X.Length == 0)
			{
				MessageBox.Show("No Points Found Matching Search Parameters...", "Warning");
				return;
			}

			float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[IMAGESETINDEX].Width);
			float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[IMAGESETINDEX].Height);
			FNDCOORDRECTS = new Rectangle[FNDCOORDS_X.Length];
			Parallel.For(0, FNDCOORDS_X.Length, i =>
			{
				FNDCOORDRECTS[i] = new Rectangle((int)(((float)(FNDCOORDS_X[i]) + 0.5) * xsc - 3), (int)(((float)(FNDCOORDS_Y[i]) + 0.5) * ysc - 3), 7, 7);
			});

			DialogResult q = MessageBox.Show(String.Concat("Found ", FNDCOORDS_X.Length.ToString(), " points matching seach criteria.  Would you like to plot them?"), "Plot Points?", MessageBoxButtons.YesNoCancel);
			switch (q)
			{
				case (DialogResult.Yes)://then plot the points...easy! :)
				{
					ReplaceImagePtsBtn.Enabled = true;//give access to control...and plot
					ReplaceImagePtsDrop.Enabled = true;
					ReplaceImagePtsDrop_SelectedIndexChanged(sender, e);
					ShowFoundCoordsChck.Enabled = true;
					ShowFoundCoordsChck.Checked = true;
					break;
				}
				case (DialogResult.No)://need to do anything other cases?
				{
					ReplaceImagePtsBtn.Enabled = true;//give access to control...no plotting
					ReplaceImagePtsDrop.Enabled = true;
					ReplaceImagePtsDrop_SelectedIndexChanged(sender, e);
					ShowFoundCoordsChck.Enabled = true;
					ShowFoundCoordsChck.Checked = false;
					break;
				}
				case (DialogResult.Cancel)://need to do anything other cases?
				{
					ReplaceImagePtsBtn.Enabled = false;//give access to control
					ReplaceImagePtsDrop.Enabled = false;
					break;
				}
			}
			ImageWindow.Refresh();

			if (q != DialogResult.Cancel)//ask to save point coordinates to file
			{
				if (MessageBox.Show("Save point values & coordinates to file?", "Save Points?", MessageBoxButtons.YesNo) == DialogResult.No)
					return;

				double[] radeg = new double[FNDCOORDS_X.Length];
				double[] decdeg = new double[FNDCOORDS_X.Length];

				if (SHOW_WCSCOORDS && IMAGESET[IMAGESETINDEX].WCS.Exists())
					for (int i = 0; i < FNDCOORDS_X.Length; i++)
					{
						double ra, dec;
						string r;
						string d;
						IMAGESET[IMAGESETINDEX].WCS.Get_Coordinate(FNDCOORDS_X[i], FNDCOORDS_Y[i], true, "TAN", out ra, out dec, out r, out d);
						radeg[i] = ra;
						decdeg[i] = dec;
					}

				SaveFileDialog sf = new SaveFileDialog();
				sf.Filter = "Tab Delimited Text file (*.txt)|*.txt";
				if (sf.ShowDialog() == DialogResult.Cancel)
					return;

				FileStream fs = new FileStream(sf.FileName, System.IO.FileMode.Create, FileAccess.Write);
				StreamWriter sw = new StreamWriter(fs);
				string line = "Pixel Value" + "	" + "X" + "	" + "Y" + "	" + "Right Ascension (deg)" + "	" + "Declination (deg)";
				sw.WriteLine(line);

				for (int i = 0; i < FNDCOORDS_X.Length; i++)
				{
					line = IMAGESET[IMAGESETINDEX][FNDCOORDS_X[i], FNDCOORDS_Y[i]].ToString() + "	" + FNDCOORDS_X[i].ToString() + "	" + FNDCOORDS_Y[i].ToString() + "	" + radeg[i].ToString() + "	" + decdeg[i].ToString();
					sw.WriteLine(line);
				}

				sw.Close();
				fs.Close();
			}
		}

		private void ShowFoundCoordsChck_CheckedChanged(object sender, EventArgs e)
		{
			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void ReplaceImagePtsBtn_Click(object sender, EventArgs e)
		{

			int style = ReplaceImagePtsDrop.SelectedIndex;//zero <=, one ==, two >=
			if (style < 0)
			{
				MessageBox.Show("Please Select Replacement Style from Adjacent DropDown Box...", "Error...");
			}
			else
			{
				DialogResult q = MessageBox.Show("Are you really sure you would like to replace the Found Data Points?", "Proceed?", MessageBoxButtons.YesNo);

				if (q == DialogResult.Yes)
				{
					switch (ReplaceImagePtsDrop.SelectedIndex)
					{
						case (0):   //value replacement
						{
							double val = Convert.ToDouble(ReplaceImagePtsTxt.Text);
							IMAGESET[IMAGESETINDEX].SetImage(JPMath.Replace(IMAGESET[IMAGESETINDEX].Image, FNDCOORDS_X, FNDCOORDS_Y, val, true), true, true);
							FileListDrop_SelectedIndexChanged(sender, e);
							break;
						}
						case (1):   //image min replacement
						{
							double val = Convert.ToDouble(ReplaceImagePtsTxt.Text);
							IMAGESET[IMAGESETINDEX].SetImage(JPMath.Replace(IMAGESET[IMAGESETINDEX].Image, FNDCOORDS_X, FNDCOORDS_Y, IMAGESET[IMAGESETINDEX].Min, true), true, true);
							FileListDrop_SelectedIndexChanged(sender, e);
							break;
						}
						case (2):   //image max replacement
						{
							double val = Convert.ToDouble(ReplaceImagePtsTxt.Text);
							IMAGESET[IMAGESETINDEX].SetImage(JPMath.Replace(IMAGESET[IMAGESETINDEX].Image, FNDCOORDS_X, FNDCOORDS_Y, IMAGESET[IMAGESETINDEX].Max, true), true, true);
							FileListDrop_SelectedIndexChanged(sender, e);
							break;
						}
						case (3):   //image median replacement
						{
							double val = Convert.ToDouble(ReplaceImagePtsTxt.Text);
							IMAGESET[IMAGESETINDEX].SetImage(JPMath.Replace(IMAGESET[IMAGESETINDEX].Image, FNDCOORDS_X, FNDCOORDS_Y, IMAGESET[IMAGESETINDEX].Median, true), true, true);
							FileListDrop_SelectedIndexChanged(sender, e);
							break;
						}
						case (4):   //image mean replacement
						{
							double val = Convert.ToDouble(ReplaceImagePtsTxt.Text);
							IMAGESET[IMAGESETINDEX].SetImage(JPMath.Replace(IMAGESET[IMAGESETINDEX].Image, FNDCOORDS_X, FNDCOORDS_Y, IMAGESET[IMAGESETINDEX].Mean, true), true, true);
							FileListDrop_SelectedIndexChanged(sender, e);
							break;
						}
					}
				}
				else if (q == DialogResult.No)
				{
					/*ReplaceImagePtsBtn.Enabled = false;
					ReplaceImagePtsTxt.Enabled = false;
					ReplaceImagePtsDrop.Enabled = false;*/
				}
			}
		}

		private void BatchMeanChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchMeanChck.Checked == true)
			{
				FITSImage f;
				if (SCMChck.Checked == true)
					f = IMAGESET.MeanClipped(true, (double)SCMUpD.Value, true);
				else
					f = IMAGESET.Mean(true, true);

				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchMeanChck.Checked = false;
			}
		}

		private void BatchMedianChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchMedianChck.Checked == true)
			{
				FITSImage f = IMAGESET.Median(true, true, "Computing Median");
				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchMedianChck.Checked = false;
			}
		}

		private void BatchStdvChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchStdvChck.Checked == true)
			{
				FITSImage f = IMAGESET.Stdv(true, true);
				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchStdvChck.Checked = false;
			}
		}

		private void BatchSumChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchSumChck.Checked == true)
			{
				FITSImage f = IMAGESET.Sum(true, true);
				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchSumChck.Checked = false;
			}
		}

		private void BatchQuadratureChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchQuadratureChck.Checked == true)
			{
				FITSImage f = IMAGESET.Quadrature(true, true);
				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchQuadratureChck.Checked = false;
			}
		}

		private void BatchMinimumChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchMinimumChck.Checked == true)
			{
				FITSImage f = IMAGESET.Min(true, true);
				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchMinimumChck.Checked = false;
			}
		}

		private void BatchMaximumChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchMaximumChck.Checked == true)
			{
				FITSImage f = IMAGESET.Max(true, true);
				if (f != null)
				{
					IMAGESET.GatherHeaders(f);
					IMAGESET.Add(f);
					FileListDrop.Items.Add(IMAGESET[IMAGESET.Count - 1].FileName);
					FileListDrop.SelectedIndex = FileListDrop.Items.Count - 1;
				}
				else
					BatchMaximumChck.Checked = false;
			}
		}

		private void SubBiasChck_CheckedChanged(object sender, EventArgs e)
		{
			if (SubBiasChck.Checked == true)
			{
				string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = false;
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS|*.fits;*.fit;*.fts";
				ofd.Title = "Subtract file data...";

				if (ofd.ShowDialog() == DialogResult.OK)
				{
					DIVMULTADDSUB_FILE = ofd.FileName;
					//Enabled = false;
					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
					ImageOpsWrkr.RunWorkerAsync(1);
					WAITBAR.ShowDialog();
				}
				else
				{
					SubBiasChck.Checked = false;
				}
			}
		}

		private void SubDarkChck_CheckedChanged(object sender, EventArgs e)
		{

		}

		private void AddImageChck_CheckedChanged(object sender, EventArgs e)
		{
			if (AddImageChck.Checked == true)
			{
				string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = false;
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS|*.fits;*.fit;*.fts";
				ofd.Title = "Add file data...";

				if (ofd.ShowDialog() == DialogResult.OK)
				{
					DIVMULTADDSUB_FILE = ofd.FileName;
					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
					ImageOpsWrkr.RunWorkerAsync(3);
					WAITBAR.ShowDialog();
				}
				else
				{
					AddImageChck.Checked = false;
				}
			}
		}

		private void DivFlatChck_CheckedChanged(object sender, EventArgs e)
		{
			if (DivFlatChck.Checked == true)
			{
				string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = false;
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS|*.fits;*.fit;*.fts";
				ofd.Title = "Divide file data...";

				if (ofd.ShowDialog() == DialogResult.OK)
				{
					DIVMULTADDSUB_FILE = ofd.FileName;
					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
					ImageOpsWrkr.RunWorkerAsync(2);
					WAITBAR.ShowDialog();
				}
				else
				{
					DivFlatChck.Checked = false;
				}
			}
		}

		private void MultImgChck_CheckedChanged(object sender, EventArgs e)
		{
			if (MultImgChck.Checked == true)
			{
				string dir = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = false;
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS|*.fits;*.fit;*.fts";
				ofd.Title = "Multiply file data...";

				if (ofd.ShowDialog() == DialogResult.OK)
				{
					DIVMULTADDSUB_FILE = ofd.FileName;
					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
					ImageOpsWrkr.RunWorkerAsync(4);
					WAITBAR.ShowDialog();
				}
				else
				{
					MultImgChck.Checked = false;
				}
			}
		}

		private void FlipHorzBtn_Click(object sender, EventArgs e)
		{
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Horizontal Flip...";
			ImageOpsWrkr.RunWorkerAsync(16);
			WAITBAR.ShowDialog();
		}

		private void FlipVertBtn_Click(object sender, EventArgs e)
		{
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Vertical Flip...";
			ImageOpsWrkr.RunWorkerAsync(17);
			WAITBAR.ShowDialog();
		}

		private void FlipInvertBtn_Click(object sender, EventArgs e)
		{
			
		}

		private void RotCCWBtn_Click(object sender, EventArgs e)
		{
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "CCW Rotation...";
			ImageOpsWrkr.RunWorkerAsync(19);
			WAITBAR.ShowDialog();
		}

		private void RotCWBtn_Click(object sender, EventArgs e)
		{
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "CW Rotation...";
			ImageOpsWrkr.RunWorkerAsync(20);
			WAITBAR.ShowDialog();
		}

		private void CutSubImBtn_Click(object sender, EventArgs e)
		{
			CROPPING = new int[] { XSUBRANGE[0], XSUBRANGE[XSUBRANGE.Length - 1], YSUBRANGE[0], YSUBRANGE[YSUBRANGE.Length - 1] };

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Cropping to sub-image...";
			ImageOpsWrkr.RunWorkerAsync(7);
			WAITBAR.ShowDialog();
		}

		private void CutSubImBtn_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button != MouseButtons.Right)
				return;

			RangeDlg rdlg = new RangeDlg();
			rdlg.HelpButton = false;
			rdlg.Text = "Set Image Range...";
			rdlg.XStartUpD.Minimum = 1;
			rdlg.XEndUpD.Minimum = 1;
			rdlg.YStartUpD.Minimum = 1;
			rdlg.YEndUpD.Minimum = 1;
			try
			{
				rdlg.XStartUpD.Value = (int)REG.GetReg("CCDLAB", "CROPXSTART");
				rdlg.XEndUpD.Value = (int)REG.GetReg("CCDLAB", "CROPXEND");
				rdlg.YStartUpD.Value = (int)REG.GetReg("CCDLAB", "CROPYSTART");
				rdlg.YEndUpD.Value = (int)REG.GetReg("CCDLAB", "CROPYEND");
			}
			catch { };

			if (rdlg.ShowDialog() == DialogResult.Cancel)
				return;

			int xstart = (int)rdlg.XStartUpD.Value;
			int xend = (int)rdlg.XEndUpD.Value;
			int ystart = (int)rdlg.YStartUpD.Value;
			int yend = (int)rdlg.YEndUpD.Value;

			if (xstart == 0 && ystart == 0 && xend == 0 && yend == 0)
				return;

			REG.SetReg("CCDLAB", "CROPXSTART", xstart);
			REG.SetReg("CCDLAB", "CROPXEND", xend);
			REG.SetReg("CCDLAB", "CROPYSTART", ystart);
			REG.SetReg("CCDLAB", "CROPYEND", yend);

			CROPPING = new int[] { xstart, xend, ystart, yend };

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Image Cropping...";
			ImageOpsWrkr.RunWorkerAsync(7);
			WAITBAR.ShowDialog();
		}

		private void ScalarOpBtn_Click(object sender, EventArgs e)
		{
			int style = ScalarOpStyleDrop.SelectedIndex;
			double scalar;
			try
			{
				scalar = Convert.ToDouble(ScalarOpValTxt.Text);
			}
			catch
			{
				MessageBox.Show(String.Concat("Scalar value: ' ", ScalarOpValTxt.Text, " ' not numeric.  Try again."), "Error");
				return;
			}
			if (scalar == 0)
			{
				MessageBox.Show(String.Concat("Scalar value of ZERO doesn't make sense.  Try again."), "Warning...");
				return;
			}
			if (style == -1)
			{
				MessageBox.Show(String.Concat("Please select operation style from adjacent drop-down menu."), "Error...");
				return;
			}
			if (style == 2 && scalar == 1 || style == 3 && scalar == 1 || style == 4 && scalar == 1)
			{
				MessageBox.Show(String.Concat("Multiplication, Division, or Power by ONE has no effect.  Try again."), "Warning...");
				return;
			}
			//finally go ahead

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Scalar Operation...";
			ImageOpsWrkr.RunWorkerAsync(10);
			WAITBAR.ShowDialog();
		}

		private void MathOpBtn_Click(object sender, EventArgs e)
		{
			int style = MathOpDrop.SelectedIndex;
			if (style == -1)
			{
				MessageBox.Show(String.Concat("Please select operation from adjacent drop-down menu."), "Error...");
				return;
			}

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;

			if (MathOpDrop.SelectedIndex == 5)
			{
				WAITBAR.Text = "Normalizing...";
				ImageOpsWrkr.RunWorkerAsync(21);//21 = normalize
			}
			else if (MathOpDrop.SelectedIndex == 11)
			{
				WAITBAR.Text = "Degradient-X...";
				ImageOpsWrkr.RunWorkerAsync(25);//degradientX
			}
			else if (MathOpDrop.SelectedIndex == 12)
			{
				WAITBAR.Text = "Degradient-Y...";
				ImageOpsWrkr.RunWorkerAsync(26);//degradientY
			}
			else if (MathOpDrop.SelectedIndex == 13)//Hanning
			{
				WAITBAR.Text = "Applying Hanning Window...";
				ImageOpsWrkr.RunWorkerAsync(28);
			}
			else if (MathOpDrop.SelectedIndex == 15)
			{
				WAITBAR.Text = "Replaciong NaN's with 0...";
				ImageOpsWrkr.RunWorkerAsync(29);
			}
			else if (MathOpDrop.SelectedIndex == 16)
			{
				WAITBAR.Text = "Replacing Inf's with 0...";
				ImageOpsWrkr.RunWorkerAsync(30);
			}
			else
				ImageOpsWrkr.RunWorkerAsync(11);//the other ones...they should be separated out here

			WAITBAR.ShowDialog();
		}

		private void BinBtn_Click(object sender, EventArgs e)
		{
			int xbin = (int)XBinUpD.Value;
			int ybin = (int)YBinUpD.Value;

			if (xbin > IMAGESET[0].Width || ybin > IMAGESET[0].Height)
			{
				MessageBox.Show("Error: Binning kernel larger than image dimenions.", "Error...");
				return;
			}
			if (xbin == 1 && ybin == 1)
				return;

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Binning...";
			ImageOpsWrkr.RunWorkerAsync(6);
			WAITBAR.ShowDialog();
		}

		private void KeyValNormBtn_Click(object sender, EventArgs e)
		{
			HeaderKey hk = new HeaderKey();
			if (hk.ShowDialog() == DialogResult.Cancel)
				return;

			NORMKEY = hk.textBox1.Text;

			for (int i = 0; i < IMAGESET.Count; i++)
			{
				int jj = IMAGESET[i].Header.GetKeyIndex(NORMKEY, false);
				if (jj == -1)
				{
					MessageBox.Show("Key '" + NORMKEY + "' doesn't exist at file: " + (i + 1).ToString(), "Error...");
					return;
				}
				try
				{
					double val = Convert.ToDouble(IMAGESET[i].Header.GetKeyValue(NORMKEY));
				}
				catch
				{
					MessageBox.Show("Key value for '" + NORMKEY + "' = '" + IMAGESET[i].Header.GetKeyValue(NORMKEY) + "'  doesn't convert to numeric value at file: " + (i + 1).ToString(), "Error...");
					return;
				}
			}

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Normalizing to Key: " + NORMKEY;
			ImageOpsWrkr.RunWorkerAsync(27);
			WAITBAR.ShowDialog();
		}

		private void ImageOpFilterTypeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (ImageOpFilterTypeDrop.SelectedIndex == 0)//median filter...set UpD minimum to 3, value to sometihng sensible, no decimals
			{
				ImageOpFilterWidthUpD.DecimalPlaces = 0;
				if (ImageOpFilterWidthUpD.Value < 3)
					ImageOpFilterWidthUpD.Value = 3;
				ImageOpFilterWidthUpD.Minimum = 3;
				ImageOpFilterWidthUpD.Increment = 2;
				Tooltip.SetToolTip(ImageOpFilterWidthUpD, "Unit pixels");
				ImageOpFilterLabel.Text = "Filter Width";
			}

			if (ImageOpFilterTypeDrop.SelectedIndex == 1)//Gaussian convolution...change the UpD to allow decimals and more values for FWHM
			{
				ImageOpFilterWidthUpD.DecimalPlaces = 1;
				ImageOpFilterWidthUpD.Minimum = Convert.ToDecimal(0.1);
				ImageOpFilterWidthUpD.Increment = Convert.ToDecimal(0.1);
				Tooltip.SetToolTip(ImageOpFilterWidthUpD, "FWHM (pixels)");
				ImageOpFilterLabel.Text = "Filter Width";
			}

			if (ImageOpFilterTypeDrop.SelectedIndex == 2)//Hot pixel filter
			{
				ImageOpFilterWidthUpD.DecimalPlaces = 0;
				ImageOpFilterWidthUpD.Minimum = 1;
				ImageOpFilterWidthUpD.Maximum = 100000;
				ImageOpFilterWidthUpD.Increment = 50;
				ImageOpFilterWidthUpD.Value = 1000;
				Tooltip.SetToolTip(ImageOpFilterWidthUpD, "Count");
				ImageOpFilterLabel.Text = "Threshold:";
			}
		}

		private void ImageOpFilterBtn_Click(object sender, EventArgs e)
		{
			int type = ImageOpFilterTypeDrop.SelectedIndex;
			if (type >= 0)//if a type is selected
			{
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;

				if (type == 0)//median filter
				{
					WAITBAR.Text = "Median Filter";
					ImageOpsWrkr.RunWorkerAsync(12);
				}
				if (type == 1)//convolution
				{
					WAITBAR.Text = "Convolution Filter";
					ImageOpsWrkr.RunWorkerAsync(13);
				}
				if (type == 2)//hot pixel
				{
					ImageOpsWrkr.RunWorkerAsync(14);
				}
				if (type == 3)//wiener deconv filter
				{
					ImageOpsWrkr.RunWorkerAsync(15);
				}

				WAITBAR.ShowDialog();
			}
		}

		private void ImageOpsWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			int[] inds;
			if (BatchCorrectionChck.Checked == false)
			{
				inds = new int[] { IMAGESETINDEX };
				WAITBAR.ProgressBar.Maximum = 1;
			}
			else
			{
				inds = new int[IMAGESET.Count];
				for (int i = 0; i < IMAGESET.Count; i++)
					inds[i] = i;
			}

			switch (Convert.ToInt32(e.Argument))
			{
				case (1):// subtract image
				{
					FITSImage simg = new FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, false, true, false, true);
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] - simg, true, false);
					}
					break;
				}
				case (2):// divide image
				{
					FITSImage dimg = new FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, false, true, false, true);
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] / dimg, true, true);
					}
					break;
				}
				case (3)://add image
				{
					FITSImage aimg = new FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, false, true, false, true);

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] + aimg, true, true);
					}
					break;
				}
				case (4):// multiply image
				{
					FITSImage mimg = new FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, false, true, false, true);

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] * mimg, true, true);
					}
					break;
				}
				case (5):
				{
					break;
				}
				case (6):// Binning
				{
					int xbin = (int)XBinUpD.Value;
					int ybin = (int)YBinUpD.Value;

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.Bin(IMAGESET[inds[i]].Image, xbin, ybin, true), true, true);

						if (xbin == ybin)
							if (WorldCoordinateSolution.Exists(IMAGESET[inds[i]].Header, WorldCoordinateSolution.WCSType.TAN))
							{
								IMAGESET[inds[i]].WCS = new WorldCoordinateSolution(IMAGESET[inds[i]].Header);
								IMAGESET[inds[i]].WCS.Bin(xbin, IMAGESET[inds[i]].Header);
							}
					}
					break;
				}
				case (7):// Cut Sub Image
				{
					ProgressBar.Maximum = IMAGESET.Count;

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i);

						IMAGESET[inds[i]].SetImage(JPMath.Crop(IMAGESET[inds[i]].Image, CROPPING, true), true, true);
						IMAGESET[inds[i]].Header.AddKey("XCROPSTT", CROPPING[0].ToString(), "Cropped image x-start index (0-based)", -1);
						IMAGESET[inds[i]].Header.AddKey("XCROPEND", CROPPING[1].ToString(), "Cropped image x-end index (0-based)", -1);
						IMAGESET[inds[i]].Header.AddKey("YCROPSTT", CROPPING[2].ToString(), "Cropped image y-start index (0-based)", -1);
						IMAGESET[inds[i]].Header.AddKey("YCROPEND", CROPPING[3].ToString(), "Cropped image y-end index (0-based)", -1);

						if (WorldCoordinateSolution.Exists(IMAGESET[inds[i]].Header, WorldCoordinateSolution.WCSType.TAN))
						{
							IMAGESET[inds[i]].WCS = new WorldCoordinateSolution(IMAGESET[inds[i]].Header);
							IMAGESET[inds[i]].WCS.Cut((double)CROPPING[0], (double)CROPPING[2], IMAGESET[inds[i]].Header);
						}
					}

					break;
				}
				case (8)://padding
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i);

						IMAGESET[inds[i]].SetImage(JPMath.Pad(IMAGESET[inds[i]].Image, PADDING, true), true, true);
					}
					break;
				}
				case (9)://excising
				{
					int x0 = -1;
					int hw = -1;
					if (ExciseBtnContxtColumnsChck.Checked)
					{
						x0 = XSUBRANGE[SUBIMAGE_HWX];
						hw = SUBIMAGE_HWX;
					}
					else
					{
						x0 = YSUBRANGE[SUBIMAGE_HWY];
						hw = SUBIMAGE_HWY;
					}

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i);

						IMAGESET[inds[i]].SetImage(JPMath.Excise(IMAGESET[inds[i]].Image, ExciseBtnContxtColumnsChck.Checked, x0, hw, true), true, true);
					}
					break;
				}
				case (10)://scalar ops
				{
					double scalar = Convert.ToDouble(ScalarOpValTxt.Text);
					int style = ScalarOpStyleDrop.SelectedIndex;

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i);

						switch (style)
						{
							case (0):// +
							{
								IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] + scalar, true, true);
								break;
							}
							case (1):// -
							{
								IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] - scalar, true, true);
								break;
							}
							case (2):// *
							{
								IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] * scalar, true, true);
								break;
							}
							case (3):// /
							{
								IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] / scalar, true, true);
								break;
							}
							case (4):// 
							{
								IMAGESET[inds[i]].SetImage(IMAGESET[inds[i]] ^ scalar, true, true);
								break;
							}
						}
					}
					break;
				}
				case (11)://Math Ops
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i);

						int style = MathOpDrop.SelectedIndex;
						switch (style)
						{
							case (0)://round
							{
								IMAGESET[inds[i]].SetImage(JPMath.Round(IMAGESET[inds[i]].Image, 0, true), true, true);
								break;
							}
							case (1)://floor
							{
								IMAGESET[inds[i]].SetImage(JPMath.Floor(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (2)://ceil
							{
								IMAGESET[inds[i]].SetImage(JPMath.Ceil(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (3)://abs
							{
								IMAGESET[inds[i]].SetImage(JPMath.Abs(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (4)://below one (changes < 1 to 1)
							{
								IMAGESET[inds[i]].SetImage(JPMath.Floor(IMAGESET[inds[i]].Image, 1, true), true, true);
								break;
							}
							case (6)://sqrt
							{
								IMAGESET[inds[i]].SetImage(JPMath.Sqrt(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (7)://Log
							{
								IMAGESET[inds[i]].SetImage(JPMath.Log(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (8)://10^
							{
								IMAGESET[inds[i]].SetImage(JPMath.Exp(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (9)://Ln
							{
								IMAGESET[inds[i]].SetImage(JPMath.Ln(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
							case (10)://e^
							{
								IMAGESET[inds[i]].SetImage(JPMath.Exp(IMAGESET[inds[i]].Image, true), true, true);
								break;
							}
						}
					}
					break;
				}
				case (12)://Median Filter
				{
					int size = (int)ImageOpFilterWidthUpD.Value;

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.MedianFilter(IMAGESET[inds[i]].Image, (size - 1) / 2, true), true, true);
					}
					break;
				}
				case (13)://convolution filter
				{
					double FWHM = (double)ImageOpFilterWidthUpD.Value;
					double sig = FWHM / (2 * Math.Sqrt(2 * Math.Log(2)));
					double[,] g = JPMath.Gaussian(1, FWHM, (int)Math.Ceiling(sig * 5), false);
					g = JPMath.MatrixDivScalar(g, JPMath.Sum(g, true), false);

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.MatrixConvolveMatrix(IMAGESET[inds[i]].Image, g, true), true, true);
					}
					break;
				}
				case (14)://de hot pixel
				{
					double thresh = (double)ImageOpFilterWidthUpD.Value;
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.DeSpeckle(IMAGESET[inds[i]].Image, thresh, 3, true), true, true);
					}
					break;
				}
				case (15)://Wiener Deconv Filter
				{
					MWNumericArray FWHM = new MWNumericArray((double)ImageOpFilterWidthUpD.Value);
					MLCCDLAB.ImageFilter IF = new MLCCDLAB.ImageFilter();

					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						MWNumericArray z = new MWNumericArray(IMAGESET[inds[i]].Image);
						MWNumericArray z2 = (MWNumericArray)IF.WienerDeconv(z, FWHM);

						IMAGESET[inds[i]].SetImage((double[,])z2.ToArray(MWArrayComponent.Real), true, true);
					}
					break;
				}
				case (16)://flip horizontal
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].FlipHorizontal();
					}
					break;
				}
				case (17)://flip vertical
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].FlipVertical();
					}
					break;
				}
				case (18)://invert (horiz + vertical)
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].FlipHorizontal();
						IMAGESET[inds[i]].FlipVertical();
					}
					break;
				}
				case (19)://rotate CCW
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].RotateCW(false);
					}
					break;
				}
				case (20)://rotate CW
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].RotateCW(true);
					}
					break;
				}
				case (21)://normalize
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.MatrixDivScalar(IMAGESET[inds[i]].Image, IMAGESET[inds[i]].Mean, true), true, true);
					}
					break;
				}
				case (22)://rotate
				{
					try
					{
						for (int i = 0; i < inds.Length; i++)
						{
							if (WAITBAR.DialogResult == DialogResult.Cancel)
								return;
							ImageOpsWrkr.ReportProgress(i + 1);

							if (RotateBtnCntxtNearest.Checked)
								IMAGESET[inds[i]].SetImage(JPMath.RotateShiftArray(IMAGESET[inds[i]].Image, (double)RotateAngleUpD.Value * Math.PI / 180, Double.MaxValue, Double.MaxValue, "nearest", 0, 0, true), true, true);
							if (RotateBtnCntxtBiLinear.Checked)
								IMAGESET[inds[i]].SetImage(JPMath.RotateShiftArray(IMAGESET[inds[i]].Image, (double)RotateAngleUpD.Value * Math.PI / 180, Double.MaxValue, Double.MaxValue, "bilinear", 0, 0, true), true, true);
							if (RotateBtnCntxtLanczos3.Checked)
								IMAGESET[inds[i]].SetImage(JPMath.RotateShiftArray(IMAGESET[inds[i]].Image, (double)RotateAngleUpD.Value * Math.PI / 180, Double.MaxValue, Double.MaxValue, "lanc3", 0, 0, true), true, true);
							if (RotateBtnCntxtLanczos4.Checked)
								IMAGESET[inds[i]].SetImage(JPMath.RotateShiftArray(IMAGESET[inds[i]].Image, (double)RotateAngleUpD.Value * Math.PI / 180, Double.MaxValue, Double.MaxValue, "lanc4", 0, 0, true), true, true);
							if (RotateBtnCntxtLanczos5.Checked)
								IMAGESET[inds[i]].SetImage(JPMath.RotateShiftArray(IMAGESET[inds[i]].Image, (double)RotateAngleUpD.Value * Math.PI / 180, Double.MaxValue, Double.MaxValue, "lanc5", 0, 0, true), true, true);
						}
					}
					catch (Exception ee)
					{
						MessageBox.Show(ee.Message + "  " + ee.Data + "    " + ee.TargetSite + "   " + ee.Source + "   " + ee.StackTrace);
					}
					break;
				}
				case (23)://horz shift
				{
					int shift = (int)NShiftHorzUpD.Value;

					for (int ii = 0; ii < inds.Length; ii++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(ii + 1);
						IMAGESET[inds[ii]].SetImage(JPMath.ShiftArrayInt(IMAGESET[inds[ii]].Image, shift, 0, true), true, true);
					}
					break;
				}
				case (24)://vert shift
				{
					int shift = (int)NShiftVertUpD.Value;

					for (int ii = 0; ii < inds.Length; ii++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(ii + 1);
						IMAGESET[inds[ii]].SetImage(JPMath.ShiftArrayInt(IMAGESET[inds[ii]].Image, 0, shift, true), true, true);
					}
					break;
				}
				case (25)://degradientX
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.DeGradient(IMAGESET[inds[i]].Image, 0, true), true, true);
					}
					break;
				}
				case (26)://degradientY
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.DeGradient(IMAGESET[inds[i]].Image, 1, true), true, true);
					}
					break;
				}
				case (27)://Normalize to key
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						double val = Convert.ToDouble(IMAGESET[inds[i]].Header.GetKeyValue(NORMKEY));

						IMAGESET[inds[i]].SetImage(JPMath.MatrixDivScalar(IMAGESET[inds[i]].Image, val, true), true, true);
						IMAGESET[inds[i]].Header.AddKey("KEYNORM", "true", "Image Normalized to: " + NORMKEY, -1);
					}
					break;
				}
				case (28)://Hanning Window
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						IMAGESET[inds[i]].SetImage(JPMath.Hanning(IMAGESET[inds[i]].Image, true), true, true);
					}
					break;
				}
				case (29)://de-NaN
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						JPMath.Find(IMAGESET[inds[i]].Image, Double.NaN, "==", true, out FNDCOORDS_X, out FNDCOORDS_Y);
						IMAGESET[inds[i]].SetImage(JPMath.Replace(IMAGESET[inds[i]].Image, FNDCOORDS_X, FNDCOORDS_Y, 0, true), true, true);
					}
					break;
				}
				case (30)://de-Inf
				{
					for (int i = 0; i < inds.Length; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						ImageOpsWrkr.ReportProgress(i + 1);

						JPMath.Find(IMAGESET[inds[i]].Image, Double.PositiveInfinity, "==", true, out FNDCOORDS_X, out FNDCOORDS_Y);
						IMAGESET[inds[i]].SetImage(JPMath.Replace(IMAGESET[inds[i]].Image, FNDCOORDS_X, FNDCOORDS_Y, 0, true), true, true);

						JPMath.Find(IMAGESET[inds[i]].Image, Double.NegativeInfinity, "==", true, out FNDCOORDS_X, out FNDCOORDS_Y);
						IMAGESET[inds[i]].SetImage(JPMath.Replace(IMAGESET[inds[i]].Image, FNDCOORDS_X, FNDCOORDS_Y, 0, true), true, true);
					}
					break;
				}
			}
		}

		private void ImageOpsWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = String.Concat("Processing file: ", e.ProgressPercentage, " of ", WAITBAR.ProgressBar.Maximum);
			WAITBAR.Refresh();
		}

		private void ImageOpsWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WAITBAR.Close();
			FileListDrop_SelectedIndexChanged(sender, e);
			GC.Collect();
		}

		private void RotateBtn_Click(object sender, EventArgs e)
		{
			if ((double)(RotateAngleUpD.Value) == 0.0)
				return;

			RotateBtnCntxtBiLinear.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtBiLinear"));
			RotateBtnCntxtLanczos3.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos3"));
			RotateBtnCntxtLanczos4.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos4"));
			RotateBtnCntxtLanczos5.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos5"));
			RotateBtnCntxtNearest.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtNearest"));

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Rotating...";
			ImageOpsWrkr.RunWorkerAsync(22);
			WAITBAR.ShowDialog();
		}

		private void RotateBtnCntxt_Opening(object sender, System.ComponentModel.CancelEventArgs e)
		{
			RotateBtnCntxtBiLinear.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtBiLinear"));
			RotateBtnCntxtLanczos3.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos3"));
			RotateBtnCntxtLanczos4.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos4"));
			RotateBtnCntxtLanczos5.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtLanczos5"));
			RotateBtnCntxtNearest.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RotateBtnCntxtNearest"));
		}

		private void RotateBtnCntxtBiLinear_Click(object sender, EventArgs e)
		{
			if (RotateBtnCntxtBiLinear.Checked)
			{
				RotateBtnCntxtLanczos3.Checked = false;
				RotateBtnCntxtLanczos4.Checked = false;
				RotateBtnCntxtLanczos5.Checked = false;
				RotateBtnCntxtNearest.Checked = false;
			}

			REG.SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest.Checked);

			RotateBtnCntxt.Show();
		}

		private void RotateBtnCntxtLanczos3_Click(object sender, EventArgs e)
		{
			if (RotateBtnCntxtLanczos3.Checked)
			{
				RotateBtnCntxtBiLinear.Checked = false;
				RotateBtnCntxtLanczos4.Checked = false;
				RotateBtnCntxtLanczos5.Checked = false;
				RotateBtnCntxtNearest.Checked = false;
			}

			REG.SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest.Checked);

			RotateBtnCntxt.Show();
		}

		private void RotateBtnCntxtLanczos4_Click(object sender, EventArgs e)
		{
			if (RotateBtnCntxtLanczos4.Checked)
			{
				RotateBtnCntxtLanczos3.Checked = false;
				RotateBtnCntxtBiLinear.Checked = false;
				RotateBtnCntxtLanczos5.Checked = false;
				RotateBtnCntxtNearest.Checked = false;
			}

			REG.SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest.Checked);

			RotateBtnCntxt.Show();
		}

		private void RotateBtnCntxtLanczos5_Click(object sender, EventArgs e)
		{
			if (RotateBtnCntxtLanczos5.Checked)
			{
				RotateBtnCntxtLanczos3.Checked = false;
				RotateBtnCntxtLanczos4.Checked = false;
				RotateBtnCntxtBiLinear.Checked = false;
				RotateBtnCntxtNearest.Checked = false;
			}

			REG.SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest.Checked);

			RotateBtnCntxt.Show();
		}

		private void RotateBtnCntxtNearest_Click(object sender, EventArgs e)
		{
			if (RotateBtnCntxtNearest.Checked)
			{
				RotateBtnCntxtLanczos3.Checked = false;
				RotateBtnCntxtLanczos4.Checked = false;
				RotateBtnCntxtLanczos5.Checked = false;
				RotateBtnCntxtBiLinear.Checked = false;
			}

			REG.SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5.Checked);
			REG.SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest.Checked);

			RotateBtnCntxt.Show();
		}

		private void InfoStatic1_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			if (FIRSTLOAD)
				return;

			Label keylabel = (Label)sender;
			string key = keylabel.Text.Substring(0, keylabel.Text.Length - 1);
			int keyindex = IMAGESET[IMAGESETINDEX].Header.GetKeyIndex(key, false);
			if (keyindex == -1)
			{
				HeaderTxt.ClearSelected();
				return;
			}
			ViewHeaderBtn.Checked = true;
			HeaderTxt.ClearSelected();
			HeaderTxt.SelectedIndex = keyindex;
		}

		private void InfoStatic1_MouseEnter(object sender, EventArgs e)
		{
			if (FIRSTLOAD)
				return;

			Label label = (Label)sender;
			label.Font = new Font(label.Font, FontStyle.Bold | FontStyle.Underline);
			label.Refresh();

			InfoCntxt.SuspendLayout();
			InfoCntxt.Items.Clear();
			for (int i = 0; i < IMAGESET[IMAGESETINDEX].Header.Length; i++)
			{
				InfoCntxt.Items.Add(IMAGESET[IMAGESETINDEX].Header[i].Name);
				InfoCntxt.Items[i].Click += new EventHandler(InfoCntxt_ItemClicked);
			}
			InfoCntxt.ResumeLayout();
			InfoCntxt.Tag = sender;
			label.Refresh();
		}

		private void InfoStatic1_MouseLeave(object sender, EventArgs e)
		{
			Label label = (Label)sender;
			label.Font = new Font(label.Font, FontStyle.Regular | FontStyle.Underline);
			label.Refresh();
		}

		private void InfoCntxt_ItemClicked(object sender, EventArgs e)
		{
			Label label = (Label)InfoCntxt.Tag;
			string s = sender.ToString();
			label.Text = s + ":";
			FileTxtsUpD();
			REG.SetReg("CCDLAB", "InfoStatic1", InfoStatic1.Text);
			REG.SetReg("CCDLAB", "InfoStatic2", InfoStatic2.Text);
			REG.SetReg("CCDLAB", "InfoStatic3", InfoStatic3.Text);
			REG.SetReg("CCDLAB", "InfoStatic4", InfoStatic4.Text);
			REG.SetReg("CCDLAB", "InfoStatic5", InfoStatic5.Text);
		}

		private void ImageSumStatic_MouseEnter(object sender, EventArgs e)
		{
			StatsCopyClipBrdCntxt.Tag = sender;
			Label label = (Label)sender;
			label.Font = new Font(label.Font, FontStyle.Underline);
			label.Refresh();
		}

		private void ImageSumStatic_MouseLeave(object sender, EventArgs e)
		{
			Label label = (Label)sender;
			label.Font = new Font(label.Font, FontStyle.Regular);
			Tooltip.SetToolTip(label, "");
			label.Refresh();
		}

		private void StatsCopyClipBrdCntxt_Click(object sender, EventArgs e)
		{
			Label label = (Label)StatsCopyClipBrdCntxt.Tag;
			string labelname = label.Name;

			StringBuilder clipboarddata = new StringBuilder();

			int oldfilelistindex = IMAGESETINDEX;

			for (int i = 0; i < IMAGESET.Count; i++)
			{
				if (labelname.Equals("ImageMaxStatic"))
					clipboarddata.AppendLine(IMAGESET[i].Max.ToString());
				if (labelname.Equals("ImageMinStatic"))
					clipboarddata.AppendLine(IMAGESET[i].Min.ToString());
				if (labelname.Equals("ImageMeanStatic"))
					clipboarddata.AppendLine(IMAGESET[i].Mean.ToString());
				if (labelname.Equals("ImageMedianStatic"))
					clipboarddata.AppendLine(IMAGESET[i].Median.ToString());
				if (labelname.Equals("ImageSumStatic"))
					clipboarddata.AppendLine(IMAGESET[i].Sum.ToString());
				if (labelname.Equals("ImageStdvStatic"))
					clipboarddata.AppendLine(IMAGESET[i].Stdv.ToString());

				if (!labelname.Contains("SubImage"))
					continue;

				IMAGESETINDEX = i;
				SubImageStatsUpD();
				if (labelname.Equals("SubImageMaxStatic"))
					clipboarddata.AppendLine(SUBIMAGEMAX.ToString());
				if (labelname.Equals("SubImageMinStatic"))
					clipboarddata.AppendLine(SUBIMAGEMIN.ToString());
				if (labelname.Equals("SubImageMeanStatic"))
					clipboarddata.AppendLine(SUBIMAGEMEAN.ToString());
				if (labelname.Equals("SubImageMedianStatic"))
					clipboarddata.AppendLine(SUBIMAGEMEDIAN.ToString());
				if (labelname.Equals("SubImageSumStatic"))
					clipboarddata.AppendLine(SUBIMAGESUM.ToString());
				if (labelname.Equals("SubImageStdvStatic"))
					clipboarddata.AppendLine(SUBIMAGESTD.ToString());
			}
			Clipboard.SetText(clipboarddata.ToString());

			IMAGESETINDEX = oldfilelistindex;
			SubImageStatsUpD();
		}

		private void listBox1_MouseEnter(object sender, EventArgs e)
		{
			FileListDrop.Size = new Size((int)FileListDrop.Width, 20 * (int)FileListDrop.Items.Count);
		}

		private void listBox1_MouseLeave(object sender, EventArgs e)
		{
			FileListDrop.Size = new Size((int)FileListDrop.Width, 28);
		}

		private void FileListDrop_MouseMove(object sender, MouseEventArgs e)
		{

		}

		private void MainTab_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "MainTabIndex", MainTab.SelectedIndex);
		}

		private void ConvertFromTextMenu_Click(object sender, EventArgs e)
		{
			FileMenu.HideDropDown();
			ConvertFromTextMenu.HideDropDown();
			ConvertFromTextMenu.DropDown.Close();

			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenTextDataPath");
			dlg.Filter = "Text Files|*.txt|All Files|*.*";
			dlg.Multiselect = true;
			dlg.Title = "Open tab-delimited or white-space-delimited Text Data File(s)";
			DialogResult res = dlg.ShowDialog();

			if (res == DialogResult.OK)
			{
				int ind;
				string dir;
				double[,] arr;
				string filename;
				ind = dlg.FileNames[0].LastIndexOf("\\");
				dir = dlg.FileNames[0].Substring(0, ind);
				REG.SetReg("CCDLAB", "OpenTextDataPath", dir);
				for (int i = 0; i < dlg.FileNames.Length; i++)
				{
					arr = FITSImage.ConvertTxtToDblArray(dlg.FileNames[i], ConvertFromTextDelimitTxtBox.Text);
					ind = dlg.FileNames[i].LastIndexOf(".");
					filename = dlg.FileNames[i].Substring(0, ind);
					filename = String.Concat(filename, ".fits");

					JPFITS.FITSImage f = new FITSImage(filename, arr, false, true);
					f.WriteImage(DiskPrecision.Double, true);
				}
				MessageBox.Show("Conversion Successful", "Done!");
			}
		}		

		private void ClipToContrastBtn_Click(object sender, EventArgs e)
		{
			Parallel.For(0, IMAGESET[IMAGESETINDEX].Width, x =>
			{
				for (int y = 0; y < IMAGESET[IMAGESETINDEX].Height; y++)
				{
					if (IMAGESET[IMAGESETINDEX][x, y] < DIMCLIM[0])
						IMAGESET[IMAGESETINDEX][x, y] = DIMCLIM[0];
					else if (IMAGESET[IMAGESETINDEX][x, y] > DIMCLIM[1])
						IMAGESET[IMAGESETINDEX][x, y] = DIMCLIM[1];

					IMAGESET[IMAGESETINDEX][x, y] -= DIMCLIM[0];
					IMAGESET[IMAGESETINDEX][x, y] /= ((DIMCLIM[1] - DIMCLIM[0]) / 255);
				}
			});

			IMAGESET[IMAGESETINDEX].StatsUpD(true);

			ContrastFullRad.Checked = true;
			FileListDrop_SelectedIndexChanged(sender, e);
		}

		private void CombineRGBBtn_Click(object sender, EventArgs e)
		{
			IMAGEBMP = JPBitMap.RGBBitMap(IMAGESET[0].Image, IMAGESET[1].Image, IMAGESET[2].Image);
			ImageWindow.Refresh();
		}

		private void RGBSaveBtn_Click(object sender, EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			sfd.Filter = "JPEG|*.jpeg";
			sfd.AddExtension = true;
			if (sfd.ShowDialog() == DialogResult.Cancel)
				return;

			IMAGEBMP.Save(sfd.FileName, System.Drawing.Imaging.ImageFormat.Jpeg);
		}

		private void InfoTxt1_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button != MouseButtons.Right)
				return;

			try
			{
				Label infotxtlabel = (Label)sender;
				string infotxt = infotxtlabel.Text;
				Clipboard.SetText(infotxt);
				Tooltip.SetToolTip(infotxtlabel, infotxt + " copied to clipboard.");
			}
			catch
			{

			}
		}

		private void InfoTxt1_MouseEnter(object sender, EventArgs e)
		{
			Label label = (Label)sender;
			label.Font = new Font(label.Font, FontStyle.Underline | FontStyle.Bold);
			label.Refresh();
		}

		private void InfoTxt1_MouseLeave(object sender, EventArgs e)
		{
			Label label = (Label)sender;
			label.Font = new Font(label.Font, FontStyle.Regular | FontStyle.Bold);
			Tooltip.SetToolTip(label, "");
			label.Refresh();
		}

		private void ImageSumTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].Sum.ToString());
				Tooltip.SetToolTip(ImageSumTxt, "Sum copied to clipboard.");
			}
		}

		private void ImageMinTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].Min.ToString());
				Tooltip.SetToolTip(ImageMinTxt, "Minimum copied to clipboard.");
			}
		}

		private void ImageMaxTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].Max.ToString());
				Tooltip.SetToolTip(ImageMaxTxt, "Maximum copied to clipboard.");
			}
		}

		private void ImageMedianTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].Median.ToString());
				Tooltip.SetToolTip(ImageMedianTxt, "Median copied to clipboard.");
			}
		}

		private void ImageMeanTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].Mean.ToString());
				Tooltip.SetToolTip(ImageMeanTxt, "Mean copied to clipboard.");
			}
		}

		private void ImageStdTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].Stdv.ToString());
				Tooltip.SetToolTip(ImageStdTxt, "Standard Deviation copied to clipboard.");
			}
		}

		private void FileNameTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(IMAGESET[IMAGESETINDEX].FileName);
				Tooltip.SetToolTip(FileNameTxt, "File name copied to clipboard.");
			}
		}

		private void FileNameTxt_MouseLeave(object sender, EventArgs e)
		{
			Tooltip.SetToolTip(FileNameTxt, "");
		}

		private void SubImageRATxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				double cval1, cval2;
				IMAGESET[IMAGESETINDEX].WCS.Get_Coordinate((double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], true, "TAN", out cval1, out cval2);

				string str = cval1 + " " + cval2;
				Clipboard.SetText(str);
				Tooltip.SetToolTip((Label)sender, "World Coordinate " + str + " copied to clipboard.");
			}
		}

		private void SubImageSumTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(SUBIMAGESUM.ToString());
				Tooltip.SetToolTip(SubImageSumTxt, "Subimage Sum copied to clipboard.");
			}
		}

		private void SubImageMinTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(SUBIMAGEMIN.ToString());
				Tooltip.SetToolTip(SubImageMinTxt, "Subimage Min copied to clipboard.");
			}
		}

		private void SubImageMaxTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(SUBIMAGEMAX.ToString());
				Tooltip.SetToolTip(SubImageMaxTxt, "Subimage Max copied to clipboard.");
			}
		}

		private void SubImageMedianTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(SUBIMAGEMEDIAN.ToString());
				Tooltip.SetToolTip(SubImageMedianTxt, "Subimage Median copied to clipboard.");
			}
		}

		private void SubImageMeanTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(SUBIMAGEMEAN.ToString());
				Tooltip.SetToolTip(SubImageMeanTxt, "Subimage Mean copied to clipboard.");
			}
		}

		private void SubImageStdTxt_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				Clipboard.SetText(SUBIMAGESTD.ToString());
				Tooltip.SetToolTip(SubImageStdTxt, "Subimage Stdv copied to clipboard.");
			}
		}

		private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
		{
			About abt = new About(this);
			abt.ShowDialog(this);
		}

		private void TBSaveOver_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to overwrite the current file?", "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
				return;

			IMAGESET[IMAGESETINDEX].WriteImage(FILESAVEPREC, true);
		}

		private void TBSaveBatchOver_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to overwrite all of the files?", "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
				return;

			IMAGESET.Write(FILESAVEPREC, true, "Overwriting files ");
		}

		private void RotateAngleUpD_ValueChanged(object sender, EventArgs e)
		{
		}

		private void NShiftHorzUpD_ValueChanged(object sender, EventArgs e)
		{
		}

		private void NShiftVertUpD_ValueChanged(object sender, EventArgs e)
		{
		}

		private void ShiftHorzBtn_Click(object sender, EventArgs e)
		{
			if ((double)(NShiftHorzUpD.Value) == 0.0)
				return;

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Horizontal Shift...";
			ImageOpsWrkr.RunWorkerAsync(23);
			WAITBAR.ShowDialog();
		}

		private void ShiftVertBtn_Click(object sender, EventArgs e)
		{
			if ((double)(NShiftVertUpD.Value) == 0.0)
				return;

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Vertical Shift...";
			ImageOpsWrkr.RunWorkerAsync(24);
			WAITBAR.ShowDialog();
		}

		private void EMCopyHeader_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "FITS File|*.fts; *.fit; *.fits|All|*.*";
			ofd.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			ofd.Multiselect = false;
			ofd.Title = "Please select the source FITS file FROM which to copy the header.";

			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			FITSImage source = new FITSImage(ofd.FileName, null, true, false, false, false);

			ofd.Multiselect = true;
			ofd.Title = "Please now select the FITS file(s) TO which to copy the header.";

			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			FITSImage dest;
			for (int i = 0; i < ofd.FileNames.Length; i++)
			{
				dest = new FITSImage(ofd.FileNames[i], null, true, true, false, true);
				dest.Header.CopyHeaderFrom(source.Header);
				dest.WriteImage(DiskPrecision.Double, true);
			}

			MessageBox.Show("Completed copying the source header over to the destination file(s).");
		}

		private void FileListDrop_DropDown(object sender, EventArgs e)
		{
			double txtscale = 130 / 18;//pixels per character

			if (IMAGESET[0].FileName.Length > 18)
				FileListDrop.Width = (int)(IMAGESET[0].FileName.Length * (int)txtscale);
		}

		private void FileListDrop_DropDownClosed(object sender, EventArgs e)
		{
			FileListDrop.Width = 130;
		}

		private void SubImgROITab_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (SubImgROITab.SelectedIndex == 1)//COGTab
				COG_CURSOR = true;
			else
				COG_CURSOR = false;

			ImageWindow.Refresh();
			SubImageWindow.Refresh();
		}

		private void RadialPlotInterpolateROIChck_Click(object sender, EventArgs e)
		{
			SubImageCntxt.Show();
			SubImgRadialPlotMenuBtn.ShowDropDown();
		}

		private void RadialPlotMedianBackgroundChck_Click(object sender, EventArgs e)
		{
			SubImageCntxt.Show();
			SubImgRadialPlotMenuBtn.ShowDropDown();
			REG.SetReg("CCDLAB", "RadialMedianBG", RadialPlotMedianBackgroundChck.Checked);
		}

		private void SubImgRadialPlotMenuBtn_DropDownOpening(object sender, EventArgs e)
		{
			RadialPlotFitMoffatChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RadialPlotFitGaussChck"));
			RadialPlotFitMoffatChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RadialPlotFitMoffatChck"));
			if (IMAGESET[IMAGESETINDEX].Header.GetKeyValue("CDELT1") != "" && IMAGESET[IMAGESETINDEX].Header.GetKeyValue("CDELT2") != "")
			{
				double cdelt1 = Convert.ToDouble(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("CDELT1"));
				double cdelt2 = Convert.ToDouble(IMAGESET[IMAGESETINDEX].Header.GetKeyValue("CDELT2"));
				double cdelt = (cdelt1 + cdelt2) / 2;
				RadialPlotFitScaleTextBox.Text = cdelt.ToString();
			}
			else
				RadialPlotFitScaleTextBox.Text = (string)REG.GetReg("CCDLAB", "RadialPlotFitScaleTextBox");
		}

		private void RadialPlotFitGaussChck_Click(object sender, EventArgs e)
		{
			if (RadialPlotFitMoffatChck.Checked)
				RadialPlotFitMoffatChck.Checked = false;

			REG.SetReg("CCDLAB", "RadialPlotFitGaussChck", RadialPlotFitMoffatChck.Checked);
			REG.SetReg("CCDLAB", "RadialPlotFitMoffatChck", RadialPlotFitMoffatChck.Checked);
			SubImageCntxt.Show();
			SubImgRadialPlotMenuBtn.ShowDropDown();
		}

		private void RadialPlotFitMoffatChck_Click(object sender, EventArgs e)
		{
			if (RadialPlotFitGaussChck.Checked)
				RadialPlotFitGaussChck.Checked = false;

			REG.SetReg("CCDLAB", "RadialPlotFitGaussChck", RadialPlotFitMoffatChck.Checked);
			REG.SetReg("CCDLAB", "RadialPlotFitMoffatChck", RadialPlotFitMoffatChck.Checked);
			SubImageCntxt.Show();
			SubImgRadialPlotMenuBtn.ShowDropDown();
		}

		private void SubImgRadialPlotMenuBtn_Click(object sender, EventArgs e)
		{
			SubImageCntxt.Hide();
			SubImgRadialPlotMenuBtn.HideDropDown();

			MouseEventArgs me = new MouseEventArgs(MouseButtons.Left, 2, 1, 1, 0);
			SubImageWindow_MouseDoubleClick(sender, me);

			if (SUBIMAGE_HWX != SUBIMAGE_HWY)
			{
				MessageBox.Show("Error:  Region of Interest SubWindow must be square.  Double-click the main window to make the SubWindow square...", "Error...");
				return;
			}
			if (SUBIMAGE_HWX < 2)
			{
				MessageBox.Show("Error:  Region of interest SubWindow must be at least 5x5 pixels...", "Error...");
				return;
			}

			double bg = 0;
			if (RadialPlotMedianBackgroundChck.Checked)
				bg = JPMath.Median(SUBIMAGE);
			else
				bg = JPMath.Min(SUBIMAGE, false);

			double pixscale = Convert.ToDouble(RadialPlotFitScaleTextBox.Text);
			if (pixscale <= 0)
				pixscale = 1;

			double[,] SUBIMAGE_radplot = JPMath.MatrixSubScalar(SUBIMAGE, bg, false);
			double[] r_binned;
			double[] v_binned;
			JPMath.Radial_Profile_Normalized(SUBIMAGE_radplot, XSUBRANGE, YSUBRANGE, pixscale, out r_binned, out v_binned);

			if (RAD_PLOT == null || RAD_PLOT.IsDisposed)
				RAD_PLOT = new Plotter("RadialPSF", true, true);
			RAD_PLOT.Text = "Radial Profile Plot";
			string xlabel = "Radius (pixels)";
			if (pixscale != 1)
				xlabel = "Radius (arcsec)";
			RAD_PLOT.ChartGraph.PlotXYData(r_binned, v_binned, "Radial Plot", xlabel, "Normalized Value at Radius", JPChart.SeriesType.Point, "Radial PSF", Color.Blue);
			RAD_PLOT.ChartGraph.SetAxesLimits(0, r_binned[r_binned.Length - 1], 0, 1);
			RAD_PLOT.TopMost = true;
			RAD_PLOT.Show();

			if (RadialPlotFitGaussChck.Checked)
			{
				double[] PFit = new double[] { 1, 0, r_binned[r_binned.Length - 1] / 4, 0 };
				double[] PFitL = new double[] { 1, 0, r_binned[r_binned.Length - 1] / 50, 0 };
				double[] PFitU = new double[] { 1, 0, r_binned[r_binned.Length - 1], 0 };
				double[] dum = null;
				JPMath.Fit_Gaussian1d(r_binned, v_binned, ref PFit, PFitL, PFitU, ref dum, ref dum);

				double[] interpX = new double[v_binned.Length * 10];
				double step = (r_binned[v_binned.Length - 1] - r_binned[0]) / interpX.Length;
				for (int i = 0; i < interpX.Length; i++)
					interpX[i] = r_binned[0] + (double)(i) * step;
				double[] interpY = new double[interpX.Length];
				JPMath.Gaussian1d(interpX, ref interpY, PFit);

				RAD_PLOT.ChartGraph.AddXYData(interpX, interpY, JPChart.SeriesType.Line, "Gaussian Fit", Color.Red);
				string eq = "exp[-x^2 / (2*sigma^2)]";
				string title = eq + " : sigma = " + PFit[2].ToString("G5") + "; FWHM = " + (PFit[2] * 2.355).ToString("G5") + "''";
				RAD_PLOT.ChartGraph.SetTitle(title);
				RAD_PLOT.ChartGraph.SetAxesLimits(0, r_binned[r_binned.Length - 1], 0, 1);
			}
			else if (RadialPlotFitMoffatChck.Checked)
			{
				double[] PFit = new double[] { 1, 0, 1, 1, 0 };
				double[] PFitL = new double[] { 1, 0, r_binned[r_binned.Length - 1] / 50, r_binned[r_binned.Length - 1] / 50, 0 };
				double[] PFitU = new double[] { 1, 0, r_binned[r_binned.Length - 1], r_binned[r_binned.Length - 1], 0 };
				double[] dum = null;
				JPMath.Fit_Moffat1d(r_binned, v_binned, ref PFit, PFitL, PFitU, ref dum, ref dum);

				double[] interpX = new double[v_binned.Length * 10];
				double step = (r_binned[v_binned.Length - 1] - r_binned[0]) / interpX.Length;
				for (int i = 0; i < interpX.Length; i++)
					interpX[i] = r_binned[0] + (double)(i) * step;
				double[] interpY = new double[interpX.Length];
				JPMath.Moffat1d(interpX, ref interpY, PFit);

				RAD_PLOT.ChartGraph.AddXYData(interpX, interpY, JPChart.SeriesType.Line, "Moffat Fit", Color.Red);
				string eq = "[1 + (x/alpha)^2]^(-beta)";
				string title = eq + " : alpha = " + PFit[2].ToString("G5") + "; beta = " + PFit[3].ToString("G5") + "; FWHM = " + (2 * PFit[2] * Math.Sqrt(Math.Pow(2, 1 / PFit[3]) - 1)).ToString("G5") + "''";
				RAD_PLOT.ChartGraph.SetTitle(title);
				RAD_PLOT.ChartGraph.SetAxesLimits(0, r_binned[r_binned.Length - 1], 0, 1);
			}
		}

		private void ImageFingerRmvToHere_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < IMAGESETINDEX; i++)
			{
				IMAGESET.RemoveAt(0);
				FileListDrop.Items.RemoveAt(0);
			}

			IMAGESETINDEX = 0;

			ViewSelectionStatic.Text = String.Concat("Image: ", (IMAGESETINDEX + 1).ToString(), " of ", IMAGESET.Count.ToString());

			if (FileListDrop.Items.Count == 1)
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				BatchCorrectionChck.Enabled = false;
				BatchCorrectionChck.Checked = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
				HCExtractKeyValue.Enabled = false;
			}

			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;
		}

		private void ImageFingerRecToHere_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to delete the file(s) to Recylce Bin?", "WARNING!", MessageBoxButtons.YesNo) == DialogResult.No)
				return;

			int intprog = 0;
			ProgressBar.Maximum = 100;
			for (int i = 0; i < IMAGESETINDEX; i++)
			{
				if (100 * i / IMAGESETINDEX > intprog)
				{
					intprog++;
					ProgressBar.Value = intprog;
					ProgressBar.Refresh();
				}

				Microsoft.VisualBasic.FileIO.FileSystem.DeleteFile(IMAGESET[0].FullFileName, Microsoft.VisualBasic.FileIO.UIOption.OnlyErrorDialogs, Microsoft.VisualBasic.FileIO.RecycleOption.SendToRecycleBin);
				IMAGESET.RemoveAt(0);
				FileListDrop.Items.RemoveAt(0);
			}

			ProgressBar.Value = 0;
			ProgressBar.Refresh();

			IMAGESETINDEX = 0;

			ViewSelectionStatic.Text = String.Concat("Image: ", (IMAGESETINDEX + 1).ToString(), " of ", IMAGESET.Count.ToString());

			if (FileListDrop.Items.Count == 1)
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				BatchCorrectionChck.Enabled = false;
				BatchCorrectionChck.Checked = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
				HCExtractKeyValue.Enabled = false;
			}

			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;
		}

		private void ImageFingerRmvFromHere_Click(object sender, EventArgs e)
		{
			int N = FileListDrop.Items.Count;
			for (int i = IMAGESETINDEX + 1; i < N; i++)
			{
				IMAGESET.RemoveAt(IMAGESETINDEX + 1);
				FileListDrop.Items.RemoveAt(IMAGESETINDEX + 1);
			}

			IMAGESETINDEX = FileListDrop.Items.Count - 1;

			int C = IMAGESET.Count;
			ViewSelectionStatic.Text = String.Concat("Image: ", (IMAGESETINDEX + 1).ToString(), " of ", IMAGESET.Count.ToString());

			if (FileListDrop.Items.Count == 1)
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				BatchCorrectionChck.Enabled = false;
				BatchCorrectionChck.Checked = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
				HCExtractKeyValue.Enabled = false;
			}

			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;
		}

		private void ImageFingerRecFromHere_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to delete the file(s) to Recylce Bin?", "WARNING!", MessageBoxButtons.YesNo) == DialogResult.No)
				return;

			int intprog = 0;
			ProgressBar.Maximum = 100;
			int N = FileListDrop.Items.Count;
			for (int i = IMAGESETINDEX + 1; i < N; i++)
			{
				if (100 * (i - IMAGESETINDEX - 1) / (N - IMAGESETINDEX - 1) > intprog)
				{
					intprog++;
					ProgressBar.Value = intprog;
					ProgressBar.Refresh();
				}

				Microsoft.VisualBasic.FileIO.FileSystem.DeleteFile(IMAGESET[IMAGESETINDEX + 1].FullFileName, Microsoft.VisualBasic.FileIO.UIOption.OnlyErrorDialogs, Microsoft.VisualBasic.FileIO.RecycleOption.SendToRecycleBin);
				IMAGESET.RemoveAt(IMAGESETINDEX + 1);
				FileListDrop.Items.RemoveAt(IMAGESETINDEX + 1);
			}

			ProgressBar.Value = 0;
			ProgressBar.Refresh();

			IMAGESETINDEX = FileListDrop.Items.Count - 1;

			int C = IMAGESET.Count;
			ViewSelectionStatic.Text = String.Concat("Image: ", (IMAGESETINDEX + 1).ToString(), " of ", IMAGESET.Count.ToString());

			if (FileListDrop.Items.Count == 1)
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				BatchCorrectionChck.Enabled = false;
				BatchCorrectionChck.Checked = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
				HCExtractKeyValue.Enabled = false;
			}

			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;
		}

		private void ImageFingerSortFileName_Click(object sender, EventArgs e)
		{
			IMAGESET.Sort("filename");

			string[] files = new string[IMAGESET.Count];
			for (int i = 0; i < IMAGESET.Count; i++)
				files[i] = IMAGESET[i].FileName;

			FileListDrop.Items.Clear();
			FileListDrop.Items.AddRange(files);
			FileListDrop.SelectedIndex = 0;
		}

		private void ImageFingerSortKeyValue_Click(object sender, EventArgs e)
		{
			string key = ImageFingerSortKeyValueTxt.Text;
			if (key.Length == 0)
			{
				MessageBox.Show("No header key defined...", "Error");
				ImageFingerPointContext.Show();
				ImageFingerSortBy.ShowDropDown();
				return;
			}
			REG.SetReg("CCDLAB", "ImageFingerSortKeyTxt", key);

			if (IMAGESET.Sort(key) == -1)
				return;

			string[] files = new string[IMAGESET.Count];
			for (int i = 0; i < IMAGESET.Count; i++)
				files[i] = IMAGESET[i].FileName;

			FileListDrop.Items.Clear();
			FileListDrop.Items.AddRange(files);
			FileListDrop.SelectedIndex = 0;
		}

		private void ScanContextGoToBtn_Click(object sender, EventArgs e)
		{
			int N = Convert.ToInt32(ScanContextGoToTxt.Text) - 1;
			if (N >= 0 && N < FileListDrop.Items.Count)
				FileListDrop.SelectedIndex = N;
		}

		private void ScanContextGoToTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToInt32(ScanContextGoToTxt.Text);
			}
			catch
			{
				ScanContextGoToTxt.Text = "1";
			}
		}

		private void ScanContextGoToTxt_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				//e.SuppressKeyPress = true;
				ScanContextGoToBtn.PerformClick();
			}
		}

		private void SIZECntxtBatchChck_Click(object sender, EventArgs e)
		{
			SIZECntxtMenu.Show();
			SIZECntxtEditImgDim.ShowDropDown();
		}

		private void SIZECntxtEditImgDim_DoubleClick(object sender, EventArgs e)
		{
			SIZECntxtMenu.Hide();

			if (FIRSTLOAD)
				return;

			WAITBAR = new WaitBar();
			if (!SIZECntxtBatchChck.Checked)
				WAITBAR.ProgressBar.Maximum = 1;
			if (SIZECntxtBatchChck.Checked)
				WAITBAR.ProgressBar.Maximum = IMAGESET.Count;

			SIZECntxtBGWrkr.RunWorkerAsync();
			WAITBAR.ShowDialog();
		}

		private void SIZECntxtBGWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string Xedittxt = SIZECntxtEditTxtX.Text;
			string Yedittxt = SIZECntxtEditTxtY.Text;
			int Xstart, Xend, Ystart, Yend;
			int[] inds = new int[IMAGESET.Count];
			if (SIZECntxtBatchChck.Checked)
				for (int i = 0; i < IMAGESET.Count; i++)
					inds[i] = i;
			else
				inds = new int[1] { IMAGESETINDEX };

			double[,] newimg;

			for (int i = 0; i < inds.Length; i++)
			{
				if (Xedittxt == "")
				{
					Xstart = 0;
					Xend = IMAGESET[inds[i]].Width - 1;
				}
				else
				{
					int col = Xedittxt.IndexOf(":");
					if (col == -1)
					{
						MessageBox.Show("Problem with the X range: " + Xedittxt);
						WAITBAR.CancelBtn.PerformClick();
						return;
					}

					Xstart = Convert.ToInt32(Xedittxt.Substring(0, col)) - 1;
					Xend = Convert.ToInt32(Xedittxt.Substring(col + 1)) - 1;

					if (Xstart < 0 || Xend > IMAGESET[inds[i]].Width - 1)
					{
						MessageBox.Show("Problem with the X range: " + Xedittxt + ", for file: " + (i + 1).ToString());
						WAITBAR.CancelBtn.PerformClick();
						return;
					}
				}
				if (Yedittxt == "")
				{
					Ystart = 0;
					Yend = IMAGESET[inds[i]].Height - 1;
				}
				else
				{
					int col = Yedittxt.IndexOf(":");
					if (col == -1)
					{
						MessageBox.Show("Problem with the Y range: " + Yedittxt);
						WAITBAR.CancelBtn.PerformClick();
						return;
					}

					Ystart = Convert.ToInt32(Yedittxt.Substring(0, col)) - 1;
					Yend = Convert.ToInt32(Yedittxt.Substring(col + 1)) - 1;

					if (Ystart < 0 || Yend > IMAGESET[inds[i]].Height - 1)
					{
						MessageBox.Show("Problem with the Y range: " + Yedittxt + ", for file: " + (i + 1).ToString());
						WAITBAR.CancelBtn.PerformClick();
						return;
					}
				}

				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;
				SIZECntxtBGWrkr.ReportProgress(i + 1);

				newimg = new double[Xend - Xstart + 1, Yend - Ystart + 1];
				Parallel.For(0, newimg.GetLength(0), x =>
				{
					for (int y = 0; y < newimg.GetLength(1); y++)
						newimg[x, y] = IMAGESET[inds[i]][Xstart + x, Ystart + y];
				});

				IMAGESET[inds[i]].SetImage(newimg, true, true);
			}
		}

		private void SIZECntxtBGWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Processing file " + e.ProgressPercentage.ToString() + " of " + WAITBAR.ProgressBar.Maximum.ToString();
			WAITBAR.Refresh();
		}

		private void SIZECntxtBGWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WAITBAR.Close();
			FileListDrop_SelectedIndexChanged(sender, e);
		}

		private void PadImageBtn_Click(object sender, EventArgs e)
		{
			RangeDlg rdlg = new RangeDlg();
			rdlg.HelpButton = false;
			rdlg.Text = "Set the Padding Around the Image Edges...";
			rdlg.XStartUpD.Minimum = 0;
			rdlg.XEndUpD.Minimum = 0;
			rdlg.YStartUpD.Minimum = 0;
			rdlg.YEndUpD.Minimum = 0;
			try
			{
				rdlg.XStartUpD.Value = (int)REG.GetReg("CCDLAB", "PADXSTART");
				rdlg.XEndUpD.Value = (int)REG.GetReg("CCDLAB", "PADXEND");
				rdlg.YStartUpD.Value = (int)REG.GetReg("CCDLAB", "PADYSTART");
				rdlg.YEndUpD.Value = (int)REG.GetReg("CCDLAB", "PADYEND");
			}
			catch { };

			if (rdlg.ShowDialog() == DialogResult.Cancel)
				return;

			int xstart = (int)rdlg.XStartUpD.Value;
			int xend = (int)rdlg.XEndUpD.Value;
			int ystart = (int)rdlg.YStartUpD.Value;
			int yend = (int)rdlg.YEndUpD.Value;

			if (xstart == 0 && ystart == 0 && xend == 0 && yend == 0)
			{
				MessageBox.Show("Padding of zeros around the edges doesn't make sense...", "Error...");
				PadImageBtn.PerformClick();
				return;
			}

			REG.SetReg("CCDLAB", "PADXSTART", xstart);
			REG.SetReg("CCDLAB", "PADYSTART", ystart);
			REG.SetReg("CCDLAB", "PADXEND", xend);
			REG.SetReg("CCDLAB", "PADYEND", yend);

			PADDING = new int[] { xstart, xend, ystart, yend };

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Image Padding...";
			ImageOpsWrkr.RunWorkerAsync(8);
			WAITBAR.ShowDialog();
		}

		private void ExciseBtnContxtColumnsChck_Click(object sender, EventArgs e)
		{
			if (ExciseBtnContxtColumnsChck.Checked)
				ExciseBtnContxtRowsChck.Checked = false;
			else
				ExciseBtnContxtColumnsChck.Checked = true;

			ExciseBtnContxt.Show();
		}

		private void ExciseBtnContxtRowsChck_Click(object sender, EventArgs e)
		{
			if (ExciseBtnContxtRowsChck.Checked)
				ExciseBtnContxtColumnsChck.Checked = false;
			else
				ExciseBtnContxtRowsChck.Checked = true;

			ExciseBtnContxt.Show();
		}

		private void ExciseImageBtn_Click(object sender, EventArgs e)
		{
			if (!ExciseBtnContxtRowsChck.Checked && !ExciseBtnContxtColumnsChck.Checked)
			{
				MessageBox.Show("Please select rows or columns excise with right-click context menu on Excise button...", "Error...");
				return;
			}

			if (MessageBox.Show("Are you sure that you want to exise the indicated rows or columns from the image(s)?", "Ready?", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
				return;

			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileListDrop.Items.Count;
			WAITBAR.Text = "Excising region...";
			ImageOpsWrkr.RunWorkerAsync(9);
			WAITBAR.ShowDialog();
		}

		private void SIZECntxtMenu_Opened(object sender, EventArgs e)
		{
			SIZECntxtEditTxtX.Text = "1:" + IMAGESET[IMAGESETINDEX].Width.ToString();
			SIZECntxtEditTxtY.Text = "1:" + IMAGESET[IMAGESETINDEX].Height.ToString();
		}

		private void FileDirectoryTxtContextMenuDelDirRmImg_Click(object sender, EventArgs e)
		{
			if (FIRSTLOAD)
				return;

			if (MessageBox.Show("Are you sure you want to delete the directory and remove the image?", "Confirmation...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
				return;

			Microsoft.VisualBasic.FileIO.FileSystem.DeleteDirectory(IMAGESET[IMAGESETINDEX].FilePath, Microsoft.VisualBasic.FileIO.UIOption.OnlyErrorDialogs, Microsoft.VisualBasic.FileIO.RecycleOption.SendToRecycleBin, Microsoft.VisualBasic.FileIO.UICancelOption.DoNothing);

			IMAGESET.RemoveAt(IMAGESETINDEX);
			FileListDrop.Items.RemoveAt(IMAGESETINDEX);

			if (IMAGESETINDEX == IMAGESET.Count)
				IMAGESETINDEX--;
			FileListDrop.SelectedIndex = IMAGESETINDEX;

			ViewSelectionStatic.Text = String.Concat("Image: ", (IMAGESETINDEX + 1).ToString(), " of ", IMAGESET.Count.ToString());

			if (FileListDrop.Items.Count == 1)
			{
				BatchViewPanel.Enabled = false;
				TBSaveBatch.Enabled = false;
				TBSaveBatchOver.Enabled = false;
				TBSaveSetExtensions.Enabled = false;
				TBZipAllBtn.Enabled = false;
				ImageBatchRedxnPnl.Enabled = false;
				BatchCorrectionChck.Enabled = false;
				BatchCorrectionChck.Checked = false;
				HCInsertBatch.Enabled = false;
				HCRemoveBatch.Enabled = false;
				HCExtractKeyValue.Enabled = false;
			}

			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
			BatchMaximumChck.Checked = false;
			BatchMinimumChck.Checked = false;
		}

		private void ImageSizeTxt_MouseEnter(object sender, EventArgs e)
		{
			ImageSizeTxt.Font = new Font(ImageSizeTxt.Font, FontStyle.Underline | FontStyle.Bold);
		}

		private void ImageSizeTxt_MouseLeave(object sender, EventArgs e)
		{
			ImageSizeTxt.Font = new Font(ImageSizeTxt.Font, FontStyle.Bold);
		}

		private void ResetPlotPositions_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "RADplotPOSX", 10);
			REG.SetReg("CCDLAB", "RADplotPOSY", 10);
			REG.SetReg("CCDLAB", "RADplotWIDTH", 500);
			REG.SetReg("CCDLAB", "RADplotHEIGHT", 500);

			REG.SetReg("CCDLAB", "XDriftplotPOSX", 10);
			REG.SetReg("CCDLAB", "XDriftplotPOSY", 10);
			REG.SetReg("CCDLAB", "XDriftplotHEIGHT", 500);
			REG.SetReg("CCDLAB", "XDriftplotWIDTH", 500);

			REG.SetReg("CCDLAB", "YDriftplotPOSX", 10);
			REG.SetReg("CCDLAB", "YDriftplotPOSY", 10);
			REG.SetReg("CCDLAB", "YDriftplotHEIGHT", 500);
			REG.SetReg("CCDLAB", "YDriftplotWIDTH", 500);
		}

		private void ImageMaxStatic_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			int x, y;
			JPMath.Max(IMAGESET[IMAGESETINDEX].Image, out x, out y, true);
			SubImageSlideX.Value = x;
			SubImageSlideY.Value = y;

			SubImageStatsUpD();
			SubImageUpD();
			ImageWindow.Refresh();
		}

		private void FMOpenImageExtensions_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = false;
			ofd.Filter = "FITS|*.fits;*.fit;*.fts|All|*.*";
			ofd.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			FITSImageExtensionsLister iel = new FITSImageExtensionsLister(ofd.FileName);

			if (iel.ShowDialog() == DialogResult.Cancel)
				return;

			IMAGESET = new JPFITS.FITSImageSet();

			if (iel.IncludePrimaryChck.Checked)
				IMAGESET.Add(new JPFITS.FITSImage(ofd.FileName, null, true, true, true, true));

			IMAGESET.LoadExtensions(ofd.FileName, iel.ExtensionIndexesOneBased, null, true, "Loading extensions ");

			AUTOLOADIMAGES = true;
			AUTOLOADIMAGESFILES = new string[] { "SingleOut" };
			FMLoad_Click(sender, e);
		}

		private void TBSaveSetExtensions_Click(object sender, EventArgs e)
		{
			JPFITS.FITSImageExtensionsSaver fies = new JPFITS.FITSImageExtensionsSaver(IMAGESET);
			fies.ShowDialog();
		}

		private void OptionsDisplayDefaultMaxChck_Click(object sender, EventArgs e)
		{
			OptionsDisplayDefaultMaxChck.Checked = true;
			OptionsDisplayDefaultNorChck.Checked = false;

			this.WindowState = FormWindowState.Maximized;
			REG.SetReg("CCDLAB", "DisplayStateMax", true);

			OptsMenu.ShowDropDown();
			OptionsDisplayDefaultMenu.ShowDropDown();
		}

		private void OptionsDisplayDefaultNorChck_Click(object sender, EventArgs e)
		{
			OptionsDisplayDefaultMaxChck.Checked = false;
			OptionsDisplayDefaultNorChck.Checked = true;

			this.WindowState = FormWindowState.Normal;
			REG.SetReg("CCDLAB", "DisplayStateMax", false);

			OptsMenu.ShowDropDown();
			OptionsDisplayDefaultMenu.ShowDropDown();
		}


	}
}

