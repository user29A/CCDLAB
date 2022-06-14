using System;
using System.Collections;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using JPFITS;
using MathWorks.MATLAB.NET.Arrays;
using System.ComponentModel;
using System.Diagnostics;
using System.Threading.Tasks;


namespace CCDLAB
{
	public partial class Form1
	{
		private void UVActiveBGChck_CheckedChanged(object sender, EventArgs e)
		{
			if (UVActiveBGChck.Checked == true)
			{
				UVCornerThreshUpD.Enabled = true;
				UVBackGroundUpD.Value = 0;
				UVDarkScalarRad.Checked = true;
				UVBackGroundUpD.Enabled = false;
			}
			else
			{
				UVCornerThreshUpD.Enabled = false;
				UVBackGroundUpD.Value = 45;
				if (UVDarkImageRad.Checked == false)
					UVBackGroundUpD.Enabled = true;
			}
		}

		private void UVDarkScalarRad_CheckedChanged(object sender, EventArgs e)
		{
			if (UVDarkScalarRad.Checked == true)
			{
				UVBackGroundUpD.Enabled = true;
				UVActiveBGChck.Checked = false;
			}
			else
			{
			}
		}

		private void UVImageOnlyChck_CheckedChanged(object sender, EventArgs e)
		{
			if (UVImageOnlyChck.Checked == true)
			{
				UVPrecisionUpD.Enabled = true;
			}
			else
			{
				UVPrecisionUpD.Enabled = false;
			}
		}

		private void UVXDecHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(1);
		}

		private void UVYDecHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(2);
		}

		private void UVPixelHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(3);
		}

		private void UVShapeHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(4);
		}

		private void UVFCMinHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(5);
		}

		private void UVFCMaxMinHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(6);
		}

		private void UVFrameHist_Click(object sender, EventArgs e)
		{
			if (UVAlgorithmListBox.SelectedIndex == -1)//occurs when no algorithm is selected at all
				return;
			UVAlgorithmContxtFunction(7);
		}

		private void UVAlgorithmContxtFunction(int type)
		{
			int ind = UVAlgorithmListBox.SelectedIndex + 1;//ind is Algorithm type index
			int Ndivs = (int)UVPrecisionUpD.Value;
			double[,] cent_list = null;
			double[] values = null;
			JPPlot jpplot = new JPPlot();
			string algorithm = "";
			string chan = IMAGESET[FILELISTINDEX].Header.GetKeyValue("CHANNEL");
			if (chan.Length == 0)
				chan = IMAGESET[FILELISTINDEX].Header.GetKeyValue("DETECTOR");

			switch (ind)//ind is Algorithm type index
			{
				case (1)://3x3 cross = TBTC
				{
					cent_list = UVIT_Data.TBTC_Centroids;
					if (cent_list == null)
					{
						MessageBox.Show("No data for this algorithm.", "Error");
						return;
					}
					values = new double[UVIT_Data.TBTC_Centroids.GetLength(1)];
					algorithm = "3x3 Cross";
					break;
				}
				case (2)://3x3 Square = TBTS
				{
					cent_list = UVIT_Data.TBTS_Centroids;
					if (cent_list == null)
					{
						MessageBox.Show("No data for this algorithm.", "Error");
						return;
					}
					values = new double[UVIT_Data.TBTS_Centroids.GetLength(1)];
					algorithm = "3x3 Square";
					break;
				}
				case (3)://3x3 cross Gaussian = TBTQ  (Q was for quadratic)
				{
					cent_list = UVIT_Data.TBTQ_Centroids;
					if (cent_list == null)
					{
						MessageBox.Show("No data for this algorithm.", "Error");
						return;
					}
					values = new double[UVIT_Data.TBTQ_Centroids.GetLength(1)];
					algorithm = "3x3 Gaussian";
					break;
				}
				case (4)://5x5 Cross = FBFC
				{
					cent_list = UVIT_Data.FBFC_Centroids;
					if (cent_list == null)
					{
						MessageBox.Show("No data for this algorithm.", "Error");
						return;
					}
					values = new double[UVIT_Data.FBFC_Centroids.GetLength(1)];
					algorithm = "5x5 Cross";
					break;
				}
				case (5)://5x5 Square = FBFS
				{
					cent_list = UVIT_Data.FBFS_Centroids;
					if (cent_list == null)
					{
						MessageBox.Show("No data for this algorithm.", "Error");
						return;
					}
					values = new double[UVIT_Data.FBFS_Centroids.GetLength(1)];
					algorithm = "5x5 Square";
					break;
				}
			}

			switch (type)
			{
				case (1)://x decimal histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = (cent_list[0, i] - Math.Round(cent_list[0, i])) * (double)(Ndivs);
					});

					double[] x;
					double[] y;
					y = JPMath.Histogram_IntegerDivisions(values, Ndivs, out x);

					jpplot.Text = String.Concat(chan, " ", algorithm, " X Centroids");
					jpplot.PlotLine(x, y, "X Decimal Centroids", "Number of Elements", String.Concat(chan, " ", algorithm, " X Centroids"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "XCentroids");
					break;
				}
				case (2)://y decimal histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = (cent_list[1, i] - Math.Round(cent_list[1, i])) * (double)(Ndivs);
					});

					double[] x;
					double[] y;

					y = JPMath.Histogram_IntegerDivisions(values, Ndivs, out x);
					jpplot.Text = String.Concat(chan, " ", algorithm, " Y Centroids");
					jpplot.PlotLine(x, y, "Y Decimal Centroids", "Number of Elements", String.Concat(chan, " ", algorithm, " Y Centroids"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "YCentroids");
					break;
				}
				case (3)://pixel energy histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[2, i];
					});

					//quick convenience
					double mean = JPMath.Mean(values, false);
					double std = JPMath.Stdv(values, false);
					string txt = Math.Round(mean, 2).ToString();
					Clipboard.SetText(txt);
					//end convenience

					double[] x;
					double[] y;
					y = JPMath.Histogram_IntegerStep(values, Ndivs, out x);

					jpplot.Text = chan + " " + algorithm + " Pixel Energy";
					jpplot.PlotLine(x, y, "Pixel Energy", "Number of Pixels", chan + " " + algorithm + " Pixel Energy; Mean: " + ((int)(mean)).ToString() + ", Stdv: " + ((int)(std)).ToString(), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "EnergyHist");
					break;
				}
				case (4)://shape energy histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[3, i];
					});

					//quick convenience
					double mean = JPMath.Mean(values, false);
					double std = JPMath.Stdv(values, false);
					string txt = Math.Round(mean, 2).ToString();
					Clipboard.SetText(txt);
					//end convenience

					double[] x;
					double[] y;
					y = JPMath.Histogram_IntegerStep(values, Ndivs, out x);

					jpplot.Text = chan + " " + algorithm + " Shape Energy";
					jpplot.PlotLine(x, y, "Shape Energy", "Number of Pixels", chan + " " + algorithm + " Shape Energy; Mean: " + ((int)(mean)).ToString() + ", Stdv: " + ((int)(std)).ToString(), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "ShapeHist");
					break;
				}
				case (5)://5x5 Corner Minimum (i.e. background) histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[4, i];
					});

					double[] x;
					double[] y;
					y = JPMath.Histogram_IntegerStep(values, Ndivs, out x);

					jpplot.PlotLine(x, y, "5x5 Corner Minimum", "Number of Pixels", String.Concat(chan, " ", algorithm, " 5x5 Corner Minimum"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "MinCornerHist");
					break;
				}
				case (6)://5x5 Corner Max-Min (i.e. double event?) histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[5, i];
					});

					double[] x;
					double[] y;
					y = JPMath.Histogram_IntegerStep(values, Ndivs, out x);

					jpplot.PlotLine(x, y, "5x5 Corner Max-Min", "Number of Pixels", String.Concat(chan, " ", algorithm, " 5x5 Corner Max-Min"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "Max-Min Corner Hist");
					break;
				}
				case (7)://events per frame histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[6, i];
					});

					double[] x;
					double[] y;
					y = JPMath.Histogram_IntegerStep(values, Ndivs, out x);

					jpplot.PlotLine(x, y, "Frame Number", "Number of Events", String.Concat(chan, " ", algorithm, " Number of Events per Frame"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "EventsperFrame");

					int nevents = values.Length;
					double nframes = JPMath.Max(values, true) - JPMath.Min(values, true) + 1;
					double mean = (double)(nevents) / (double)(nframes);
					string txt = Math.Round(mean, 4).ToString();
					Clipboard.SetText(txt);
					break;
				}
			}
		}

		private void UVHistWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			int type = Convert.ToInt32(e.Argument);// type is index of context menu, i.e., xdec, ydec, 
			int ind = UVAlgorithmListBox.SelectedIndex + 1;//ind is Algorithm type index
			int Ndivs = (int)UVPrecisionUpD.Value;
			double[,] cent_list = null;
			double[] values = null;
			MLCCDLAB.MLHistogram hist = new MLCCDLAB.MLHistogram();

			switch (ind)//ind is Algorithm type index
			{
				case (1)://3x3 cross = TBTC
				{
					cent_list = UVIT_Data.TBTC_Centroids;
					values = new double[UVIT_Data.TBTC_Centroids.GetLength(1)];
					break;
				}
				case (3)://3x3 cross Gaussian = TBTQ  (Q was for quadratic)
				{
					cent_list = UVIT_Data.TBTQ_Centroids;
					values = new double[UVIT_Data.TBTQ_Centroids.GetLength(1)];
					break;
				}
				case (2)://3x3 Square = TBTS
				{
					cent_list = UVIT_Data.TBTS_Centroids;
					values = new double[UVIT_Data.TBTS_Centroids.GetLength(1)];
					break;
				}
				case (4)://5x5 Cross = FBFC
				{
					cent_list = UVIT_Data.FBFC_Centroids;
					values = new double[UVIT_Data.FBFC_Centroids.GetLength(1)];
					break;
				}
				case (5)://5x5 Square = FBFS
				{
					cent_list = UVIT_Data.FBFS_Centroids;
					values = new double[UVIT_Data.FBFS_Centroids.GetLength(1)];
					break;
				}
			}

			switch (type)
			{
				case (1)://x decimal histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[0, i] - Math.Round(cent_list[0, i]);
					});
					MWNumericArray x = new MWNumericArray(values);
					hist.Hist_NDivs(x, Ndivs);
					break;
				}
				case (2)://y decimal histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[1, i] - Math.Round(cent_list[1, i]);
					});
					MWNumericArray y = new MWNumericArray(values);
					hist.Hist_NDivs(y, Ndivs);
					break;
				}
				case (3)://pixel energy histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[2, i];
					});
					MWNumericArray x = new MWNumericArray(values);
					hist.Hist_IntStep(x);
					break;
				}
				case (4)://shape energy histogram 
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[3, i];
					});
					MWNumericArray x = new MWNumericArray(values);
					hist.Hist_IntStep(x);
					break;
				}
				case (5)://5x5 Corner Minimum (i.e. background) histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[4, i];
					});
					MWNumericArray x = new MWNumericArray(values);
					hist.Hist_IntStep(x);
					break;
				}
				case (6)://5x5 Corner Max-Min (i.e. double event?) histogram
				{
					Parallel.For(0, values.Length, i =>
					{
						values[i] = cent_list[5, i];
					});
					MWNumericArray x = new MWNumericArray(values);
					hist.Hist_IntStep(x);
					break;
				}
			}
		}

		private void UVHistWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			this.Enabled = true;
		}

		private void UVOpenRawBtn_Click(object sender, EventArgs e)
		{
			UVOpenRawDlg.ShowDialog();
		}

		private void UVMovieTimer_Tick(object sender, EventArgs e)
		{
			UVMovieTimer.Interval = (int)(Convert.ToDouble(UVBlinkTimeUpD.Value) * 1000) + 1;//+1 to avoid 0, 1 = 1ms
			UVViewNextBtn_Click(sender, e);
		}

		private void UVViewNextBtn_Click(object sender, EventArgs e)
		{
			UVIT_Data.Current_File_Number += (int)UVMovieSkipUpD.Value + 1;
			UVViewSelectionStatic.Text = String.Concat("Viewing File ", UVIT_Data.Current_File_Number, " of ", UVIT_Data.Number_of_Files.ToString());

			string[] file = new string[] { UVIT_Data.Full_File_List[UVIT_Data.Current_File_Number - 1] };

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(file, false);
		}

		private void UVViewLastBtn_Click(object sender, EventArgs e)
		{
			UVIT_Data.Current_File_Number -= (int)UVMovieSkipUpD.Value + 1;
			UVViewSelectionStatic.Text = String.Concat("Viewing File ", UVIT_Data.Current_File_Number, " of ", UVIT_Data.Number_of_Files.ToString());

			string[] file = new string[] { UVIT_Data.Full_File_List[UVIT_Data.Current_File_Number - 1] };

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(file, false);
		}

		private void UVGoToBtn_Click(object sender, EventArgs e)
		{
			int ImNum = (int)(UVGoToUpD.Value);
			UVIT_Data.Current_File_Number = ImNum;
			UVViewSelectionStatic.Text = String.Concat("Viewing File ", UVIT_Data.Current_File_Number, " of ", UVIT_Data.Number_of_Files.ToString());

			string[] file = new string[] { UVIT_Data.Full_File_List[UVIT_Data.Current_File_Number - 1] };

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(file, false);
		}

		private void UVMovieBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (UVMovieBtn.Checked == true)
			{
				UVMovieTimer.Enabled = true;
				UVMovieBtn.BackColor = System.Drawing.Color.Red;
			}
			else
			{
				UVMovieTimer.Enabled = false;
				UVMovieBtn.BackColor = System.Drawing.Color.Gainsboro;
			}
		}

		private void UVOpenRawDlg_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
		{
			UVBatchViewPanel.Enabled = true;
			CentroidingPanel.Enabled = true;
			UVIT_Data = new UVIT(UVOpenRawDlg.FileNames);
			UVViewSelectionStatic.Text = String.Concat("Viewing File 0 of ", UVIT_Data.Number_of_Files.ToString());
			UVGoToUpD.Maximum = UVOpenRawDlg.FileNames.Length;
		}

		private void UVCentroidBtn_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you Sure you Would like to Proceed with Centroiding?", "Proceed?", MessageBoxButtons.OKCancel) == DialogResult.OK)
			{
				REG.SetReg("CCDLAB", "UVPixelMinThresh", UVPixelMinThresh.Value);
				REG.SetReg("CCDLAB", "UVShapeMinThresh", UVShapeMinThresh.Value);
				REG.SetReg("CCDLAB", "UVPixelMaxThresh", UVPixelMaxThresh.Value);
				REG.SetReg("CCDLAB", "UVShapeMaxThresh", UVShapeMaxThresh.Value);

				ProgressBar.Maximum = UVIT_Data.Number_of_Files;
				this.Enabled = false;
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = 100;
				UVCentroidWrkr.RunWorkerAsync();
				WAITBAR.Show();
			}
		}

		private void UVCentroidWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = String.Concat(e.ProgressPercentage, "%");
			WAITBAR.Text = String.Concat("Centroiding...", e.ProgressPercentage, "%");
		}

		private void UVCentroidWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WAITBAR.Close();
			this.Enabled = true;
			this.Activate();
		}

		private void UVSaveCentroidDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			UVSaveCentroidDlg.ShowDialog();
		}

		private void UVSaveCentroidDlg_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
		{
			int ind = UVSaveCentroidDrop.SelectedIndex;
			string type = UVSaveCentroidDrop.Items[ind].ToString();
			string filename = UVSaveCentroidDlg.FileName;
			string bgname = UVDarkImageTxt.Text;
			UVIT_Data.Save_Centroids(filename, type, bgname, UVActiveBGChck.Checked);
		}

		private void UVCentroidWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			System.DateTime D = DateTime.Now;
			BackgroundWorker worker = (BackgroundWorker)(sender);

			bool finished = true;
			int precision = (int)UVPrecisionUpD.Value;
			int minpix = (int)UVPixelMinThresh.Value; int maxpix = (int)UVPixelMaxThresh.Value;
			int minshape = (int)UVShapeMinThresh.Value; int maxshape = (int)UVShapeMaxThresh.Value;
			int background = (int)UVBackGroundUpD.Value;
			int CornerThresh = (int)UVCornerThreshUpD.Value;
			double BGOffset = (double)UVBGOffset.Value;
			int[] range = new int[4];
			range[0] = 0; range[1] = IMAGESET[FILELISTINDEX].Width - 1; range[2] = 0; range[3] = IMAGESET[FILELISTINDEX].Height - 1;//default, but change next by checked default
			if (UVSubRangeChck.Checked == true) //then set range to sub window
			{
				range[0] = XSUBRANGE[0]; range[1] = XSUBRANGE[XSUBRANGE.Length - 1];
				range[2] = YSUBRANGE[0]; range[3] = YSUBRANGE[YSUBRANGE.Length - 1];
			}
			UVSaveCentroidDrop.Items.Clear();

			bool[] algors = new bool[UVAlgorithmListBox.Items.Count];
			bool oneselected = false;
			for (int i = 0; i < UVAlgorithmListBox.Items.Count; i++)
			{
				algors[i] = UVAlgorithmListBox.GetItemChecked(i);
				if (algors[i] == true)
				{
					oneselected = true;
					UVSaveCentroidDrop.Items.Add(UVAlgorithmListBox.Items[i]);
				}
			}
			if (oneselected == false)
			{
				MessageBox.Show("Please Select Centroid Algorithm", "Error");
				return;
			}
			if (UVDarkImageRad.Checked == true)
			{
				background = 0;//using array background, has already been made on check
				finished = UVIT_Data.Centroid(precision, range, minpix, maxpix, minshape, maxshape, background, algors, UVBGArray, worker,
					UVImageOnlyChck.Checked, UVActiveBGChck.Checked, CornerThresh, BGOffset, WAITBAR);
			}
			else//must be using scalar background
			{
				finished = UVIT_Data.Centroid(precision, range, minpix, maxpix, minshape, maxshape, background, algors, null, worker,
					UVImageOnlyChck.Checked, UVActiveBGChck.Checked, CornerThresh, BGOffset, WAITBAR);
			}
			if (finished == false)
				return;

			if (!UVImageOnlyChck.Checked)//i.e. made centroid lists
			{
				UVSaveCentroidDrop.Enabled = true;
				UVAlgorithmCntxt.Enabled = true;
				UVTransferImagesBtn.Enabled = true;
				UVPrecisionUpD.Enabled = true;
			}
			else//only made image(s)
			{
				UVSaveCentroidDrop.Enabled = false;
				UVAlgorithmCntxt.Enabled = false;
				UVTransferImagesBtn.Enabled = true;
			}
			TimeSpan TS = DateTime.Now - D;
			MessageBox.Show(String.Concat("Elapsed Time: ", TS.Hours.ToString(), "h", TS.Minutes.ToString(), "m", TS.Seconds.ToString(), "s."), "Time...");
		}

		private void UVOpenUCFDlg_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
		{
			string[] dummy = new string[1];
			dummy[0] = UVOpenUCFDlg.FileName;
			UVIT_Data = new UVIT(dummy);
			string[] UV = UVIT_Data.Open_CentroidFile(UVOpenUCFDlg.FileName);

			UVSaveCentroidDrop.Items.Clear();
			UVSaveCentroidDrop.Items.Add(UV[0]);
			UVPixelMinThresh.Value = Convert.ToInt32(UV[5]);
			UVPixelMaxThresh.Value = Convert.ToInt32(UV[6]);
			UVShapeMinThresh.Value = Convert.ToInt32(UV[7]);
			UVShapeMaxThresh.Value = Convert.ToInt32(UV[8]);
			UVDarkImageTxt.Text = UV[9];
			if (UVIT_Data.Range[0] == 0 && UVIT_Data.Range[2] == 0 &&
				UVIT_Data.Range[1] == 511 && UVIT_Data.Range[3] == 511)
				UVSubRangeChck.Checked = false;
			UVViewSelectionStatic.Text = String.Concat("Number of Files = ", UV[10]);

			CentroidingPanel.Enabled = true;
			UVSaveCentroidDrop.Enabled = true;
			UVTransferImagesBtn.Enabled = true;
			UVPrecisionUpD.Enabled = true;
		}

		private void UVTransferImagesBtn_Click(object sender, EventArgs e)
		{
			string type;
			string filepath = IMAGESET[0].FilePath;
			string fullfile;
			int precision = (int)UVPrecisionUpD.Value;
			int count = FileListDrop.Items.Count;
			UVIT_Data.Precision = precision;
			for (int i = 0; i < UVSaveCentroidDrop.Items.Count; i++)
			{
				type = UVSaveCentroidDrop.Items[i].ToString();
				fullfile = String.Concat(filepath, type, "_X", precision, ".fts");
				FileListDrop.Items.Add(String.Concat(type, "_X", precision, ".fts"));
				if (UVImageOnlyChck.Checked == false)
				{
					IMAGESET.Add(new FITSImage(fullfile, UVIT_Data.Get_Image(type), true, true));
				}
				else
				{
					IMAGESET.Add(new FITSImage(fullfile, UVIT_Data.Get_FromOnlyImageMode(type), true, true));
					UVTransferImagesBtn.Enabled = false;
				}

			}

			FileListDrop.SelectedIndex = count;
			BatchViewPanel.Enabled = true;
			TBSaveBatch.Enabled = true;
			TBSaveBatchOver.Enabled = true;
			BatchCorrectionChck.Checked = true;
			BatchCorrectionChck.Enabled = true;
			ImageBatchRedxnPnl.Enabled = true;
			HCInsertBatch.Enabled = true;
			HCRemoveBatch.Enabled = true;
			SubBiasChck.Checked = false;
			MultImgChck.Checked = false;
			AddImageChck.Checked = false;
			DivFlatChck.Checked = false;
			BatchMeanChck.Checked = false;
			BatchSumChck.Checked = false;
			BatchQuadratureChck.Checked = false;
			BatchMedianChck.Checked = false;
			BatchStdvChck.Checked = false;
		}

		private void UVOpenDirBtn_Click(object sender, EventArgs e)
		{
			UVOpenDirDlg.SelectedPath = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			DialogResult result = UVOpenDirDlg.ShowDialog();
			if (result == DialogResult.OK)
			{
				UVBatchViewPanel.Enabled = true;
				CentroidingPanel.Enabled = true;
				string[] filelist;
				if (!UVOpenSubDirChck.Checked)
				{
					filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.raw", SearchOption.TopDirectoryOnly);
					if (filelist.Length == 0)
						filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.fits", SearchOption.TopDirectoryOnly);
					if (filelist.Length == 0)
						filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.fit", SearchOption.TopDirectoryOnly);
					if (filelist.Length == 0)
						filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.fts", SearchOption.TopDirectoryOnly);
				}
				else
				{
					filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.raw", SearchOption.AllDirectories);
					if (filelist.Length == 0)
						filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.fits", SearchOption.AllDirectories);
					if (filelist.Length == 0)
						filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.fit", SearchOption.AllDirectories);
					if (filelist.Length == 0)
						filelist = Directory.GetFiles(UVOpenDirDlg.SelectedPath, "*.fts", SearchOption.AllDirectories);
				}

				if (filelist.Length == 0)
				{
					MessageBox.Show("No RAW or FITS files found.", "No data...");
					return;
				}

				Array.Sort(filelist);
				UVIT_Data = new UVIT(filelist);
				UVViewSelectionStatic.Text = String.Concat("Viewing File 0 of ", UVIT_Data.Number_of_Files.ToString());
				UVGoToUpD.Maximum = UVIT_Data.Number_of_Files;
				REG.SetReg("CCDLAB", "OpenFilesPath", UVOpenDirDlg.SelectedPath);
				UVGoToUpD.Maximum = filelist.Length;
			}
		}

		private void UVOpenCentroidBtn_Click(object sender, EventArgs e)
		{
			UVOpenUCFDlg.ShowDialog();
		}

		private void UVDarkImageRad_CheckedChanged(object sender, EventArgs e)
		{
			if (UVDarkImageRad.Checked == true && !(CentroidingPanel.Enabled == false))
			{
				UVBackGroundUpD.Enabled = false;
				OpenFileDialog dlg = new OpenFileDialog();
				dlg.Filter = "Fits File (*.fts)|*.fts|Fits File (*.fit)|*.fit|Fits File (*.fits)|*.fits";
				dlg.Title = "Please Select Dark FITS File";
				DialogResult result = dlg.ShowDialog();

				if (result == DialogResult.OK)
				{
					UVActiveBGChck.Checked = false;
					UVDarkImageTxt.Text = dlg.FileName.Substring(dlg.FileName.LastIndexOf("\\") + 1);
					FITSImage im = new FITSImage(dlg.FileName, null, false, true, false, true);
					UVBGArray = new ushort[im.Width, im.Height];
					for (int i = 0; i < im.Width; i++)
						for (int j = 0; j < im.Height; j++)
							UVBGArray[i, j] = (ushort)im[i, j];
				}
				else
				{
					UVBackGroundUpD.Enabled = true;
					UVDarkImageTxt.Text = "NA";
					UVBGArray = null;
					UVDarkScalarRad.Checked = true;
				}
			}
			else
			{
				UVBackGroundUpD.Enabled = true;
				UVDarkImageTxt.Text = "NA";
				UVBGArray = null;
				UVDarkScalarRad.Checked = true;
			}
		}

		private void EMGSE_UnpackImg_Click(object sender, EventArgs e)
		{
			GSEExtractImg ext = new GSEExtractImg();
			ext.Show(this);
		}

		private void UVStatsAnalysisBtn_Click(object sender, EventArgs e)
		{
			DialogResult res = MessageBox.Show("Ready?", "Extract Image Stats?", MessageBoxButtons.OKCancel);

			if (res == DialogResult.Cancel)
				return;

			int ind = UVPlotXAxisDrop.SelectedIndex;
			UVIT_StatsPlot UVPlot = new UVIT_StatsPlot();
			UVPlot.Plot_Stats(UVIT_Data.Full_File_List, ind);
		}

		private void UVHVUTelemBtn_Click(object sender, EventArgs e)
		{
			DialogResult res = MessageBox.Show("Ready?", "Plot HVU Telem?", MessageBoxButtons.OKCancel);

			if (res == DialogResult.Cancel)
				return;

			int ind = UVPlotXAxisDrop.SelectedIndex;
			UVIT_HVUPlot UVPlot = new UVIT_HVUPlot();
			UVPlot.Plot_Telem(UVIT_Data.Full_File_List, ind);
		}

		private void UVIT_ApplyCPUCorrectionMenu_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = false;
			dlg.Title = "Select the Centroid INTEGERS List (_XYInts_List)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;
			string IntsFileList = dlg.FileName;
			string FracFileList = IntsFileList.Replace("Ints", "Frac");
			FITSImage IntsFits = new JPFITS.FITSImage(IntsFileList, null, true, true, false, true);
			FITSImage FracFits = new JPFITS.FITSImage(FracFileList, null, true, true, false, true);

			int ind = dlg.FileName.LastIndexOf("\\");
			dir = dlg.FileName.Substring(0, ind);
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			string CPUXDistFile = "";
			string CPUYDistFile = "";
			string channel = IntsFits.Header.GetKeyValue("CHANNEL");
			if (channel.Length == 0)
				channel = IntsFits.Header.GetKeyValue("DETECTOR");
			if (channel == "FUV")
			{
				if (File.Exists("C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits"))
				{
					CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits";
					CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dY.fits";
				}
			}
			else if (channel == "NUV")
			{
				if (File.Exists("C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits"))
				{
					CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits";
					CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dY.fits";
				}
			}
			else if (channel == "VIS")
			{
				if (File.Exists("C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits"))
				{
					CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits";
					CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dY.fits";
				}
			}
			else
			{
				//get the CPU *X* correction image
				dlg.Title = "Select CPU *X* Correction FITS Image File";
				dlg.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenCPUDistPath");
				DialogResult resl = dlg.ShowDialog();
				if (resl != DialogResult.OK)
					return;
				CPUXDistFile = dlg.FileName;
				ind = dlg.FileName.LastIndexOf("\\");
				dir = dlg.FileName.Substring(0, ind);
				REG.SetReg("CCDLAB", "OpenCPUDistPath", dir);

				//get the CPU *Y* correction image
				dlg.Title = "Select CPU *Y* Correction FITS Image File";
				dlg.InitialDirectory = dir;
				res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;
				CPUYDistFile = dlg.FileName;
			}
			JPFITS.FITSImage CPUXDistFits = new JPFITS.FITSImage(CPUXDistFile, null, true, true, false, true);
			JPFITS.FITSImage CPUYDistFits = new JPFITS.FITSImage(CPUYDistFile, null, true, true, false, true);

			int NPts = FracFits.Height;
			Parallel.For(0, NPts, j =>
			{
				int xcorr = (int)(32 * CPUXDistFits[(int)(IntsFits[0, j] / 32), (int)(IntsFits[1, j] / 32)]);
				int ycorr = (int)(32 * CPUYDistFits[(int)(IntsFits[0, j] / 32), (int)(IntsFits[1, j] / 32)]);

				IntsFits[0, j] -= xcorr;
				IntsFits[1, j] -= ycorr;
			});

			ind = IntsFileList.LastIndexOf(".");
			IntsFileList = IntsFileList.Insert(ind, "_deDist");
			ind = FracFileList.LastIndexOf(".");
			FracFileList = FracFileList.Insert(ind, "_deDist");
			IntsFits.WriteImage(IntsFileList, TypeCode.Int16, true);
			FracFits.WriteImage(FracFileList, TypeCode.Int16, true);

			MessageBox.Show("CPU Distortion Correction Completed...", "Finished...");
		}

		private void ApplyUVFPNMenu_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = false;
			dlg.Title = "Select the Centroid INTEGERS List (_XYInts_List)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;
			string IntsFileList = dlg.FileName;
			string FracFileList = IntsFileList.Replace("Ints", "Frac");
			FITSImage IntsFits = new JPFITS.FITSImage(IntsFileList, null, true, true, false, true);
			FITSImage FracFits = new JPFITS.FITSImage(FracFileList, null, true, true, false, true);

			int ind = dlg.FileName.LastIndexOf("\\");
			dir = dlg.FileName.Substring(0, ind);
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			string FPNFile = "";
			string channel = IntsFits.Header.GetKeyValue("CHANNEL");
			if (channel.Length == 0)
				channel = IntsFits.Header.GetKeyValue("DETECTOR");
			string alg = IntsFits.Header.GetKeyValue("CENTROID");
			if (alg.Length == 0)
				alg = IntsFits.Header.GetKeyValue("ALGRITHM");
			bool FPNsuccess = false;
			if (channel == "FUV")
			{
				if (alg == "3S" || alg == "3x3 Square")
				{
					if (File.Exists("C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits"))
					{
						FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits";
						FPNsuccess = true;
					}
				}
				if (alg == "5S" || alg == "5x5 Square")
				{
					if (File.Exists("C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits"))
					{
						FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits";
						FPNsuccess = true;
					}
				}
			}
			if (channel == "NUV")
			{
				if (alg == "3S" || alg == "3x3 Square")
				{
					if (File.Exists("C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits"))
					{
						FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits";
						FPNsuccess = true;
					}
				}
				if (alg == "5S" || alg == "5x5 Square")
				{
					if (File.Exists("C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits"))
					{
						FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits";
						FPNsuccess = true;
					}
				}
			}
			if (channel == "VIS")
			{
				if (alg == "3S" || alg == "3x3 Square")
				{
					if (File.Exists("C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits"))
					{
						FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits";
						FPNsuccess = true;
					}
				}
				if (alg == "5S" || alg == "5x5 Square")
				{
					if (File.Exists("C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits"))
					{
						FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits";
						FPNsuccess = true;
					}
				}
			}
			if (!FPNsuccess)
			{
				//get the FPN correction table
				dlg.Title = "Select FPN Correction FITS Image File";
				dlg.InitialDirectory = (string)REG.GetReg("CCDLAB", "OpenFPNPath");
				DialogResult resl = dlg.ShowDialog();
				if (resl != DialogResult.OK)
					return;
				FPNFile = dlg.FileName;
				ind = dlg.FileName.LastIndexOf("\\");
				dir = dlg.FileName.Substring(0, ind);
				REG.SetReg("CCDLAB", "OpenFPNPath", dir);
			}
			FITSImage FPNFits = new JPFITS.FITSImage(FPNFile, null, true, true, false, true);

			int NPts = FracFits.Height;
			for (int j = 0; j < NPts; j++)
			{
				//this is for doing 5x5 and if centroid are out of bounds for 3x3.
				//find the centroids out of bounds; xdecs < -16, xdecs > 15;
				//then move them to the adjacent pixel they want to be in with centroids in bounds
				if (FracFits[0, j] < -16)//X
				{
					IntsFits[0, j] -= 32;//adjust integer
					FracFits[0, j] += 32;//adjust fractional
				}
				if (FracFits[1, j] < -16)//Y
				{
					IntsFits[1, j] -= 32;//adjust integer
					FracFits[1, j] += 32;//adjust fractional
				}
				if (FracFits[0, j] > 15)//X
				{
					IntsFits[0, j] += 32;//adjust integer
					FracFits[0, j] -= 32;//adjust fractional
				}
				if (FracFits[1, j] > 15)//Y
				{
					IntsFits[1, j] += 32;//adjust integer
					FracFits[1, j] -= 32;//adjust fractional
				}
			}

			for (int j = 0; j < NPts; j++)
			{
				//adjust centroids to range from 0 to +1 (0 - 31), instead of -0.5
				//to correspond to the FPN Table coordinates ..THIS MUST be UNDONE at end
				FracFits[0, j] += 16;
				FracFits[1, j] += 16;
			}

			Random rand = new Random();
			for (int j = 0; j < NPts; j++)
			{
				//redistribute centroids evenly between the posts, so they can be interpolated
				//using Shyam's Way
				FracFits[0, j] += rand.NextDouble();
				FracFits[1, j] += rand.NextDouble();
			}

			for (int j = 0; j < NPts; j++)//now apply FPN correction
			{
				FracFits[0, j] *= (double)(int)(FPNFits[1, (int)(FracFits[0, j] * 4096 / 32)]);
				FracFits[1, j] *= (double)(int)(FPNFits[2, (int)(FracFits[1, j] * 4096 / 32)]);
			}

			for (int j = 0; j < NPts; j++)//reset the centroids to -16 to +15 range
			{
				FracFits[0, j] -= 16;//x
				FracFits[1, j] -= 16;//y
			}

			ind = IntsFileList.LastIndexOf(".");
			IntsFileList = IntsFileList.Insert(ind, "_deFPN");
			ind = FracFileList.LastIndexOf(".");
			FracFileList = FracFileList.Insert(ind, "_deFPN");
			IntsFits.WriteImage(IntsFileList, TypeCode.Int16, true);
			FracFits.WriteImage(FracFileList, TypeCode.Int16, true);

			MessageBox.Show("FPN Correction Completed...", "Finished...");
		}

		private void UVITMenu_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				GSEExtractImg ext = new GSEExtractImg();
				ext.Show(this);
			}
		}

		private void UVITMenu_DropDownOpened(object sender, EventArgs e)
		{
			UVITMenu_Click(sender, e);
		}

		private void UVITMenu_Click(System.Object sender, EventArgs e)
		{
			DriftFromPCInterpolateChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PCDriftInterpChck"));
			SmoothINTDriftChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "SmoothINTDrift"));
			if (SmoothINTDriftChck.Checked)
				SmoothINTDriftTimeDrop.Enabled = true;
			else
				SmoothINTDriftTimeDrop.Enabled = false;
			SmoothINTDriftTimeDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "SmoothINTDriftTimeDrop"));
			TryAutoDeBiasINTDrift.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "deBiasINTDrift"));
			UserXShiftTxt.Text = (string)REG.GetReg("CCDLAB", "UserXShiftTxt");
			UserYShiftTxt.Text = (string)REG.GetReg("CCDLAB", "UserYShiftTxt");
			UserRotationTxt.Text = (string)REG.GetReg("CCDLAB", "UserRotationTxt");
			UserRotationXCenterTxt.Text = (string)REG.GetReg("CCDLAB", "UserRotationXTxt");
			UserRotationYCenterTxt.Text = (string)REG.GetReg("CCDLAB", "UserRotationYTxt");
			FlipHorizontalMenuItem.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "FlipHorizontalMenuItem"));
			FlipVerticalMenuItem.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "FlipVerticalMenuItem"));
			PointSrcINTDriftChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcINTDrift"));
			CrossCorrINTDriftChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "CrossCorrINTDrift"));
			TryAutoDeBiasINTDrift.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "AutoDeBiasINTDriftChck"));
			TryAutoDeBiasINTDrift.Enabled = Convert.ToBoolean(REG.GetReg("CCDLAB", "AutoDeBiasINTDriftEnab"));
			CosmicRayFilterSigmaMenuTxt.Text = (string)REG.GetReg("CCDLAB", "UVCRSigmaThreshold");
			CosmicRayFilterSigmaMenuChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVCRSigmaThresholdChck"));
			CosmicRayFilterCountMenuChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVCRNumberThresholdChck"));
			FilterCosmicRaysChckMenuItem.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "FilterCRs"));
			MaxMinThreshTxt.Text = (string)REG.GetReg("CCDLAB", "MaxMinThreshTxtText");
			MaxMinThreshChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "MaxMinThreshChck"));
			MaxMinThreshTxt.Enabled = Convert.ToBoolean(REG.GetReg("CCDLAB", "MaxMinThreshTxtEnab"));
			MaxMinCountTwiceChck.Enabled = Convert.ToBoolean(REG.GetReg("CCDLAB", "MaxMinCountTwiceChckEnab"));
			MaxMinCountTwiceChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "MaxMinCountTwiceChck"));
			ApplyFlatListToImageChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVApplyFlatList"));
			ApplyExpArrayToImageChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "ApplyExpArrayToImageChck"));
			if (ApplyExpArrayToImageChck.Checked)
				ListToImageExpMapCutOffDrop.Enabled = true;
			else
				ListToImageExpMapCutOffDrop.Enabled = false;
			ListToImageExpMapCutOffDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "ListToImageExpMapCutOffDrop"));
			L1DigestApplyDISTChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DigestApplyDIST"));
			if (L1DigestApplyDISTChck.Checked == false)
			{
				L1DigestApplyDISTInterpBiLinChck.Enabled = false;
				L1DigestApplyDISTInterpNearChck.Enabled = false;
			}
			else
			{
				L1DigestApplyDISTInterpBiLinChck.Enabled = true;
				L1DigestApplyDISTInterpNearChck.Enabled = true;
			}
			L1DigestApplyFPNChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DigestApplyFPN"));
			ApplyDriftCreateExpArrayChc.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "ApplyDriftCreateExpArrayChc"));
			ExposureArrayResolutionDrop.SelectedIndex = (int)REG.GetReg("CCDLAB", "ExposureArrayRes");
			L1TransformNUVtoFUVChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1NUVtoFUVChck"));
			L1DigestApplyDISTInterpNearChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DigestApplyDISTInterpNearChck"));
			L1DigestApplyDISTInterpBiLinChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DigestApplyDISTInterpBiLinChck"));
			UVFinalizeDeleteIntrmdtChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVFinalizeDeleteIntrmdtChck"));
			UVFinalizeMoveOrCopyZipChck.Text = (string)(REG.GetReg("CCDLAB", "UVFinalizeMoveOrCopyZipChck"));
			UVFinalizeMoveOrCopyZipChck.Checked = true;
			UVFinalizeIncludeTablesChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVFinalizeIncludeTablesChck"));
			UVFinalizeIncludeExpMapChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVFinalizeIncludeExpMapChck"));

			L1CentroidPaddingChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1CentroidPaddingChck"));
			PCCentroidPaddingDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "PCCentroidPaddingDrop"));
			if (PCCentroidPaddingDrop.SelectedIndex == 0)
				UVPCMODEPADOFFSET = 22;
			if (PCCentroidPaddingDrop.SelectedIndex == 1)
				UVPCMODEPADOFFSET = 44;
			if (L1CentroidPaddingChck.Checked)
				PCCentroidPaddingDrop.Enabled = true;
			else
			{
				PCCentroidPaddingDrop.Enabled = false;
				UVPCMODEPADOFFSET = 0;
			}

			PointSrcROIStackDriftDrop.SelectedIndex = (int)REG.GetReg("CCDLAB", "PointSrcROIStackDriftDrop_index");
			PointSrcROIFindNSrcDrop.SelectedIndex = (int)REG.GetReg("CCDLAB", "PointSrcROIFindNSrcDrop_index");
			DriftSmoothNDrop.SelectedIndex = (int)REG.GetReg("CCDLAB", "DriftSmoothNDrop_index");
			if (Convert.ToBoolean(REG.GetReg("CCDLAB", "PCDriftInterpChck")))
				DriftSmoothNDrop.Enabled = true;
			else
				DriftSmoothNDrop.Enabled = false;
			L1DiscardDataTimeChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DiscardDataTimeChck"));
			if (L1DiscardDataTimeChck.Checked)
				L1DiscardDataTimeDrop.Enabled = true;
			else
				L1DiscardDataTimeDrop.Enabled = false;
			L1DiscardDataTimeDrop.SelectedIndex = (int)REG.GetReg("CCDLAB", "L1DiscardDataTimeDrop");
			L1DiscardDuplicateChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DiscardDuplicateChck"));
			L1DigestPCParityChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DigestPCParityChck"));
			L1DegradientINTMode.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DegradientINTMode"));
			L1CleanINTMode.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1CleanINTMode"));
			L1SkipINTMode.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1SkipINTMode"));
			if (L1DegradientINTMode.Checked == false)
				L1CleanINTMode.Enabled = false;
			else
				L1CleanINTMode.Enabled = true;
			if (L1SkipINTMode.Checked)
			{
				L1DegradientINTMode.Enabled = false;
				L1CleanINTMode.Enabled = false;
			}
			else
			{
				L1DegradientINTMode.Enabled = true;
				L1CleanINTMode.Enabled = true;
			}

			L1FilterCorrectionChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1FilterCorrectionChck"));
			L1TBCChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1TBCChck"));
			if (Convert.ToBoolean(REG.GetReg("CCDLAB", "LinearRotationChck")))
			{
				LinearRotationChck.Checked = true;
				GeneralTransformChck.Checked = false;
				FlipHorizontalMenuItem.Enabled = true;
				FlipVerticalMenuItem.Enabled = true;
				UserXShiftTxt.Enabled = true;
				UserYShiftTxt.Enabled = true;
				UserRotationTxt.Enabled = true;
				UserRotationXCenterTxt.Enabled = true;
				UserRotationYCenterTxt.Enabled = true;

				TransformCoefATxt.Enabled = false;
				TransformCoefBTxt.Enabled = false;
				TransformCoefCTxt.Enabled = false;
				TransformCoefDTxt.Enabled = false;
				TransformCenterXTxt.Enabled = false;
				TransformCenterYTxt.Enabled = false;
				TransformShiftXTxt.Enabled = false;
				TransformShiftYTxt.Enabled = false;
			}
			else if (Convert.ToBoolean(REG.GetReg("CCDLAB", "GeneralTransformChck")))
			{
				LinearRotationChck.Checked = false;
				GeneralTransformChck.Checked = true;

				FlipHorizontalMenuItem.Enabled = false;
				FlipVerticalMenuItem.Enabled = false;
				UserXShiftTxt.Enabled = false;
				UserYShiftTxt.Enabled = false;
				UserRotationTxt.Enabled = false;
				UserRotationXCenterTxt.Enabled = false;
				UserRotationYCenterTxt.Enabled = false;

				TransformCoefATxt.Enabled = true;
				TransformCoefBTxt.Enabled = true;
				TransformCoefCTxt.Enabled = true;
				TransformCoefDTxt.Enabled = true;
				TransformCenterXTxt.Enabled = true;
				TransformCenterYTxt.Enabled = true;
				TransformShiftXTxt.Enabled = true;
				TransformShiftYTxt.Enabled = true;
			}
			else
			{
				LinearRotationChck.Checked = false;
				GeneralTransformChck.Checked = false;

				FlipHorizontalMenuItem.Enabled = false;
				FlipVerticalMenuItem.Enabled = false;
				UserXShiftTxt.Enabled = false;
				UserYShiftTxt.Enabled = false;
				UserRotationTxt.Enabled = false;
				UserRotationXCenterTxt.Enabled = false;
				UserRotationYCenterTxt.Enabled = false;

				TransformCoefATxt.Enabled = false;
				TransformCoefBTxt.Enabled = false;
				TransformCoefCTxt.Enabled = false;
				TransformCoefDTxt.Enabled = false;
				TransformCenterXTxt.Enabled = false;
				TransformCenterYTxt.Enabled = false;
				TransformShiftXTxt.Enabled = false;
				TransformShiftYTxt.Enabled = false;
			}
			TransformCoefATxt.Text = (string)REG.GetReg("CCDLAB", "TransformCoefATxt");
			TransformCoefBTxt.Text = (string)REG.GetReg("CCDLAB", "TransformCoefBTxt");
			TransformCoefCTxt.Text = (string)REG.GetReg("CCDLAB", "TransformCoefCTxt");
			TransformCoefDTxt.Text = (string)REG.GetReg("CCDLAB", "TransformCoefDTxt");
			TransformCenterXTxt.Text = (string)REG.GetReg("CCDLAB", "TransformCenterXTxt");
			TransformCenterYTxt.Text = (string)REG.GetReg("CCDLAB", "TransformCenterYTxt");
			TransformShiftXTxt.Text = (string)REG.GetReg("CCDLAB", "TransformShiftXTxt");
			TransformShiftYTxt.Text = (string)REG.GetReg("CCDLAB", "TransformShiftYTxt");
			UVAutoApplyDriftandImageChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVAutoApplyDriftandImageChck"));
			UVAutoDriftImageViewChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVAutoDriftImageViewChck"));
			if (UVAutoApplyDriftandImageChck.Checked)
				UVAutoDriftImageViewChck.Enabled = true;
			else
				UVAutoDriftImageViewChck.Enabled = false;

			L1CleanINTLineThreshold.Text = (string)REG.GetReg("CCDLAB", "L1CleanINTLineThreshold");
			L1CleanINTNPix.Text = (string)REG.GetReg("CCDLAB", "L1CleanINTNPix");
			if (L1CleanINTMode.Checked)
			{
				L1CleanINTLineThreshold.Enabled = true;
				L1CleanINTNPix.Enabled = true;
			}
			else
			{
				L1CleanINTLineThreshold.Enabled = false;
				L1CleanINTNPix.Enabled = false;
			}

			PointSrcINTDriftDisplayChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcINTDriftDisplay"));
			PointSrcINTDriftDisplayCadenceDrop.Enabled = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceEnabled"));
			PointSrcINTDriftDisplayCadenceDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceIndex"));
			masterizeSinglesToolStripMenuItem.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "masterizeSinglesToolStripMenuItem"));
			UVDeleteMergeDirsChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVDeleteMergeDirsChck"));
			UVAutoPSFPostMergeChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "UVAutoPSFPostMergeChck"));
			L1DigestDeleteFileChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1DigestDeleteFileChck"));
			ConsolidateDriftFolderChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "ConsolidateDriftFolderChck"));
			ConsolidateTimeListFolderChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "ConsolidateTimeListFolderChck"));
			RegistrationXYIntsListFolderScanChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "RegistrationXYIntsListFolderScanChck"));
			MergeXYIntsListFolderScanChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "MergeXYIntsListFolderScanChck"));
			PointSrcINTDriftNoPSEConfChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcINTDriftNoPSEConfChck"));
			PointSrcINTDriftNoPlotConfChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcINTDriftNoPlotConfChck"));
			PointSrcROIFindSrcChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcROIFindSrcChck"));
			if (PointSrcROIFindSrcChck.Checked)
				PointSrcROIFindNSrcDrop.Enabled = true;
			else
				PointSrcROIFindNSrcDrop.Enabled = false;
			PointSrcROIAutoRunChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "PointSrcROIAutoRunChck"));
			if (PointSrcROIAutoRunChck.Checked)
			{
				//PointSrcROIFindSrcChck.Enabled = false;
				//PointSrcROIFindNSrcDrop.Enabled = false;
				PointSrcROIStackDriftDrop.Enabled = false;
			}
			else
			{
				//PointSrcROIFindNSrcDrop.Enabled = true;
				//PointSrcROIFindSrcChck.Enabled = true;
				PointSrcROIStackDriftDrop.Enabled = true;
			}

			UVLISTTOIMAGEPREC = (int)REG.GetReg("CCDLAB", "UVLISTTOIMGPREC");
			if (UVLISTTOIMAGEPREC == 1)
			{
				ListToImage1PixMenuItem.Checked = true;
				ListToImage2PixMenuItem.Checked = false;
				ListToImage4PixMenuItem.Checked = false;
				ListToImage8PixMenuItem.Checked = false;
				ListToImage16PixMenuItem.Checked = false;
			}
			if (UVLISTTOIMAGEPREC == 2)
			{
				ListToImage1PixMenuItem.Checked = false;
				ListToImage2PixMenuItem.Checked = true;
				ListToImage4PixMenuItem.Checked = false;
				ListToImage8PixMenuItem.Checked = false;
				ListToImage16PixMenuItem.Checked = false;
			}
			if (UVLISTTOIMAGEPREC == 4)
			{
				ListToImage1PixMenuItem.Checked = false;
				ListToImage2PixMenuItem.Checked = false;
				ListToImage4PixMenuItem.Checked = true;
				ListToImage8PixMenuItem.Checked = false;
				ListToImage16PixMenuItem.Checked = false;
			}
			if (UVLISTTOIMAGEPREC == 8)
			{
				ListToImage1PixMenuItem.Checked = false;
				ListToImage2PixMenuItem.Checked = false;
				ListToImage4PixMenuItem.Checked = false;
				ListToImage8PixMenuItem.Checked = true;
				ListToImage16PixMenuItem.Checked = false;
			}
			if (UVLISTTOIMAGEPREC == 16)
			{
				ListToImage1PixMenuItem.Checked = false;
				ListToImage2PixMenuItem.Checked = false;
				ListToImage4PixMenuItem.Checked = false;
				ListToImage8PixMenuItem.Checked = false;
				ListToImage16PixMenuItem.Checked = true;
			}

			CosmicRayFilterMenuTxt.Text = (string)REG.GetReg("CCDLAB", "UVCRNumberThreshold");

			if (FilterCosmicRaysChckMenuItem.Checked)
			{
				CosmicRayFilterCountMenuChck.Enabled = true;
				CosmicRayFilterSigmaMenuChck.Enabled = true;
				CosmicRayFilterSigmaMenuTxt.Enabled = true;
				CosmicRayFilterMenuTxt.Enabled = true;
			}
			else
			{
				CosmicRayFilterCountMenuChck.Enabled = false;
				CosmicRayFilterSigmaMenuChck.Enabled = false;
				CosmicRayFilterSigmaMenuTxt.Enabled = false;
				CosmicRayFilterMenuTxt.Enabled = false;
			}

			L1AutoRunChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1AutoRunChck"));
			if (L1AutoRunChck.Checked)
				L1AutoProceedVISBackGround.Enabled = true;
			else
			{
				L1AutoProceedVISBackGround.Enabled = false;
				L1AutoProceedVISTracking.Enabled = false;
				L1AutoApplyVISDrift.Enabled = false;
				L1AutoProceedVISBackGround.Checked = false;
				L1AutoProceedVISTracking.Checked = false;
				L1AutoApplyVISDrift.Checked = false;
			}
			if (L1AutoProceedVISBackGround.Enabled)
				L1AutoProceedVISBackGround.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1AutoProceedVISBackGround"));
			if (L1AutoProceedVISBackGround.Checked)
				L1AutoProceedVISTracking.Enabled = true;
			L1AutoProceedVISTracking.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1AutoProceedVISTracking"));
			if (L1AutoProceedVISTracking.Checked)
				L1AutoApplyVISDrift.Enabled = true;
			L1AutoApplyVISDrift.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1AutoApplyVISDrift"));

			L1MachineStandardChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1MachineStandardChck"));
			L1MachineExtremeChck.Checked = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1MachineExtremeChck"));
		}

		private void L1MachineStandardChck_Click(System.Object sender, EventArgs e)
		{
			L1MachineStandardChck.Checked = true;
			L1MachineExtremeChck.Checked = false;

			REG.SetReg("CCDLAB", "L1MachineStandardChck", L1MachineStandardChck.Checked);
			REG.SetReg("CCDLAB", "L1MachineExtremeChck", L1MachineExtremeChck.Checked);

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
			machinePerformanceToolStripMenuItem.ShowDropDown();
		}

		private void L1MachineExtremeChck_Click(System.Object sender, EventArgs e)
		{
			L1MachineStandardChck.Checked = false;
			L1MachineExtremeChck.Checked = true;

			REG.SetReg("CCDLAB", "L1MachineStandardChck", L1MachineStandardChck.Checked);
			REG.SetReg("CCDLAB", "L1MachineExtremeChck", L1MachineExtremeChck.Checked);

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
			machinePerformanceToolStripMenuItem.ShowDropDown();
		}

		private void UVFinalizeDeleteIntrmdtChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVFinalizeDeleteIntrmdtChck", UVFinalizeDeleteIntrmdtChck.Checked);

			UVITMenu.ShowDropDown();
			UVFinalizeScienceBtn.ShowDropDown();
		}

		private void UVFinalizeMoveOrCopyZipChck_Click(object sender, EventArgs e)
		{
			if (UVFinalizeMoveOrCopyZipChck.Text.Contains("Move"))
				UVFinalizeMoveOrCopyZipChck.Text = UVFinalizeMoveOrCopyZipChck.Text.Replace("Move", "Copy");
			else
				UVFinalizeMoveOrCopyZipChck.Text = UVFinalizeMoveOrCopyZipChck.Text.Replace("Copy", "Move");

			REG.SetReg("CCDLAB", "UVFinalizeMoveOrCopyZipChck", UVFinalizeMoveOrCopyZipChck.Text);

			UVITMenu.ShowDropDown();
			UVFinalizeScienceBtn.ShowDropDown();
		}

		private void UVFinalizeIncludeExpMapChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVFinalizeIncludeExpMapChck", UVFinalizeIncludeExpMapChck.Checked);

			UVITMenu.ShowDropDown();
			UVFinalizeScienceBtn.ShowDropDown();
		}

		private void UVFinalizeIncludeTablesChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVFinalizeIncludeTablesChck", UVFinalizeIncludeTablesChck.Checked);

			UVITMenu.ShowDropDown();
			UVFinalizeScienceBtn.ShowDropDown();
		}

		private void MergeXYIntsListFolderScanChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "MergeXYIntsListFolderScanChck", MergeXYIntsListFolderScanChck.Checked);

			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UVCombineCentroidListsMenuItem.ShowDropDown();
		}

		private void RegistrationXYIntsListFolderScanChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "RegistrationXYIntsListFolderScanChck", RegistrationXYIntsListFolderScanChck.Checked);

			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			GeneralUVRegistrationMenuItem.ShowDropDown();
		}

		private void ConsolidateTimeListFolderChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "ConsolidateTimeListFolderChck", ConsolidateTimeListFolderChck.Checked);

			UVITMenu.ShowDropDown();
			ApplyDriftListMentuItem.ShowDropDown();
			ConsolidateNUVApplyToFUV.ShowDropDown();
		}

		private void ConsolidateDriftFolderChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "ConsolidateDriftFolderChck", ConsolidateDriftFolderChck.Checked);

			UVITMenu.ShowDropDown();
			ApplyDriftListMentuItem.ShowDropDown();
			ConsolidateNUVApplyToFUV.ShowDropDown();
		}

		private void L1DigestDeleteFileChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DigestDeleteFileChck", L1DigestDeleteFileChck.Checked);

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void PointSrcROIFindSrcChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcROIFindSrcChck", PointSrcROIFindSrcChck.Checked);

			if (PointSrcROIFindSrcChck.Checked)
				PointSrcROIFindNSrcDrop.Enabled = true;
			else
				PointSrcROIFindNSrcDrop.Enabled = false;

			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromPCMenuItem.ShowDropDown();
			DriftFromPCPSTrackBtn.ShowDropDown();
		}

		private void PointSrcROIAutoRunChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcROIAutoRunChck", PointSrcROIAutoRunChck.Checked);

			if (PointSrcROIAutoRunChck.Checked)
			{
				//PointSrcROIFindNSrcDrop.Enabled = false;
				//PointSrcROIFindSrcChck.Enabled = false;
				PointSrcROIStackDriftDrop.Enabled = false;
			}
			else
			{
				//PointSrcROIFindNSrcDrop.Enabled = true;
				//PointSrcROIFindSrcChck.Enabled = true;
				PointSrcROIStackDriftDrop.Enabled = true;
			}

			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromPCMenuItem.ShowDropDown();
			DriftFromPCPSTrackBtn.ShowDropDown();
		}

		private void masterizeSinglesToolStripMenuItem_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "masterizeSinglesToolStripMenuItem", masterizeSinglesToolStripMenuItem.Checked);

			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			GeneralUVRegistrationMenuItem.ShowDropDown();
		}

		private void UVDeleteMergeDirsChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVDeleteMergeDirsChck", UVDeleteMergeDirsChck.Checked);

			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UVCombineCentroidListsMenuItem.ShowDropDown();
		}

		private void UVAutoPSFPostMergeChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVAutoPSFPostMergeChck", UVAutoPSFPostMergeChck.Checked);

			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UVCombineCentroidListsMenuItem.ShowDropDown();
		}

		private void PointSrcINTDriftDisplayChck_Click(System.Object sender, EventArgs e)
		{
			if (PointSrcINTDriftDisplayChck.Checked)
				PointSrcINTDriftDisplayCadenceDrop.Enabled = true;
			else
				PointSrcINTDriftDisplayCadenceDrop.Enabled = false;

			REG.SetReg("CCDLAB", "PointSrcINTDriftDisplay", PointSrcINTDriftDisplayChck.Checked);
			REG.SetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceEnabled", PointSrcINTDriftDisplayCadenceDrop.Enabled);

			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
			PointSrcINTDriftChck.ShowDropDown();
		}

		private void PointSrcINTDriftNoPSEConfChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcINTDriftNoPSEConfChck", PointSrcINTDriftNoPSEConfChck.Checked);
			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
			PointSrcINTDriftChck.ShowDropDown();
		}

		private void PointSrcINTDriftNoPlotConfChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcINTDriftNoPlotConfChck", PointSrcINTDriftNoPlotConfChck.Checked);
			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
			PointSrcINTDriftChck.ShowDropDown();
		}

		private void PointSrcINTDriftDisplayCadenceDrop_SelectedIndexChanged(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceIndex", PointSrcINTDriftDisplayCadenceDrop.SelectedIndex);
		}

		private void ExposureArrayResolutionDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "ExposureArrayRes", ExposureArrayResolutionDrop.SelectedIndex);
		}

		private void ExposureArrayResMenuText_Click(object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			ApplyDriftListMentuItem.ShowDropDown();
			ApplyDriftCreateExpArrayChc.ShowDropDown();
		}

		private void DriftPCROIOnly_Click(object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromPCMenuItem.ShowDropDown();
		}

		private void ApplyDriftCreateExpArrayChc_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "ApplyDriftCreateExpArrayChc", ApplyDriftCreateExpArrayChc.Checked);
			UVITMenu.ShowDropDown();
			ApplyDriftListMentuItem.ShowDropDown();
		}

		private void UVAutoApplyDriftandImageChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVAutoApplyDriftandImageChck", UVAutoApplyDriftandImageChck.Checked);
			if (UVAutoApplyDriftandImageChck.Checked)
				UVAutoDriftImageViewChck.Enabled = true;
			else
				UVAutoDriftImageViewChck.Enabled = false;
		}

		private void UVAutoDriftImageViewChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVAutoDriftImageViewChck", UVAutoDriftImageViewChck.Checked);
			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromPCMenuItem.ShowDropDown();
			UVAutoApplyDriftandImageChck.ShowDropDown();
		}

		private void L1DiscardDuplicateChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DiscardDuplicateChck", L1DiscardDuplicateChck.Checked);
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1TransformNUVtoFUVChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1NUVtoFUVChck", L1TransformNUVtoFUVChck.Checked);
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1FilterCorrectionChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1FilterCorrectionChck", L1FilterCorrectionChck.Checked);
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1TBCChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1TBCChck", L1TBCChck.Checked);
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1DegradientINTMode_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DegradientINTMode", L1DegradientINTMode.Checked);

			if (L1DegradientINTMode.Checked)
				L1CleanINTMode.Enabled = true;
			else
				L1CleanINTMode.Enabled = false;

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1SpecifySourceNameChck_Click(System.Object sender, EventArgs e)
		{
			//REG.SetReg("CCDLAB", "L1SpecifySourceNameChck", L1SpecifySourceNameChck.Checked);

			if (L1SpecifySourceNameChck.Checked)
				L1SourceNameTxt.Enabled = true;
			else
				L1SourceNameTxt.Enabled = false;

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1CleanINTMode_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1CleanINTMode", L1CleanINTMode.Checked);

			if (L1CleanINTMode.Checked)
			{
				L1CleanINTLineThreshold.Enabled = true;
				L1CleanINTNPix.Enabled = true;
			}
			else
			{
				L1CleanINTLineThreshold.Enabled = false;
				L1CleanINTNPix.Enabled = false;
			}
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1SkipINTMode_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1SkipINTMode", L1SkipINTMode.Checked);
			if (L1SkipINTMode.Checked)
			{
				L1DegradientINTMode.Enabled = false;
				L1CleanINTMode.Enabled = false;
			}
			else
			{
				L1DegradientINTMode.Enabled = true;
				L1CleanINTMode.Enabled = true;
			}
			REG.SetReg("CCDLAB", "L1SkipINTMode", L1SkipINTMode.Checked);

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1DiscardDataTimeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DiscardDataTimeDrop", L1DiscardDataTimeDrop.SelectedIndex);
		}

		private void L1CentroidPaddingChck_Click(object sender, EventArgs e)
		{
			if (L1CentroidPaddingChck.Checked)
			{
				PCCentroidPaddingDrop.Enabled = true;
				if (PCCentroidPaddingDrop.SelectedIndex == 0)
					UVPCMODEPADOFFSET = 22;
				if (PCCentroidPaddingDrop.SelectedIndex == 1)
					UVPCMODEPADOFFSET = 44;
			}
			else
			{
				PCCentroidPaddingDrop.Enabled = false;
				UVPCMODEPADOFFSET = 0;
			}
			REG.SetReg("CCDLAB", "L1CentroidPaddingChck", L1CentroidPaddingChck.Checked);
			UVITMenu.ShowDropDown();
		}

		private void PCCentroidPaddingDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PCCentroidPaddingDrop", PCCentroidPaddingDrop.SelectedIndex);
			if (PCCentroidPaddingDrop.SelectedIndex == 0)
				UVPCMODEPADOFFSET = 22;
			if (PCCentroidPaddingDrop.SelectedIndex == 1)
				UVPCMODEPADOFFSET = 44;
		}

		private void L1DiscardDataTimeChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DiscardDataTimeChck", L1DiscardDataTimeChck.Checked);
			if (L1DiscardDataTimeChck.Checked)
				L1DiscardDataTimeDrop.Enabled = true;
			else
				L1DiscardDataTimeDrop.Enabled = false;
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1DigestApplyFPNChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DigestApplyFPN", L1DigestApplyFPNChck.Checked);
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1DigestPCParityChck_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DigestPCParityChck", L1DigestPCParityChck.Checked);
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1DigestApplyDISTChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1DigestApplyDIST", L1DigestApplyDISTChck.Checked);
			if (L1DigestApplyDISTChck.Checked == false)
			{
				L1DigestApplyDISTInterpBiLinChck.Enabled = false;
				L1DigestApplyDISTInterpNearChck.Enabled = false;
			}
			else
			{
				L1DigestApplyDISTInterpBiLinChck.Enabled = true;
				L1DigestApplyDISTInterpNearChck.Enabled = true;
			}
			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
		}

		private void L1DigestApplyDISTInterpNearChck_Click(object sender, EventArgs e)
		{
			L1DigestApplyDISTInterpBiLinChck.Checked = false;
			L1DigestApplyDISTInterpNearChck.Checked = true;
			REG.SetReg("CCDLAB", "L1DigestApplyDISTInterpNearChck", L1DigestApplyDISTInterpNearChck.Checked);
			REG.SetReg("CCDLAB", "L1DigestApplyDISTInterpBiLinChck", L1DigestApplyDISTInterpBiLinChck.Checked);

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
			L1DigestApplyDISTChck.ShowDropDown();
		}

		private void L1DigestApplyDISTInterpBiLinChck_Click(object sender, EventArgs e)
		{
			L1DigestApplyDISTInterpBiLinChck.Checked = true;
			L1DigestApplyDISTInterpNearChck.Checked = false;
			REG.SetReg("CCDLAB", "L1DigestApplyDISTInterpNearChck", L1DigestApplyDISTInterpNearChck.Checked);
			REG.SetReg("CCDLAB", "L1DigestApplyDISTInterpBiLinChck", L1DigestApplyDISTInterpBiLinChck.Checked);

			UVITMenu.ShowDropDown();
			DigestL1FITSImageMenuItem.ShowDropDown();
			L1DigestApplyDISTChck.ShowDropDown();
		}

		private void FilterCosmicRaysChckMenuItem_Click(object sender, EventArgs e)
		{
			if (FilterCosmicRaysChckMenuItem.Checked)
			{
				CosmicRayFilterCountMenuChck.Enabled = true;
				CosmicRayFilterSigmaMenuChck.Enabled = true;
				CosmicRayFilterSigmaMenuTxt.Enabled = true;
				CosmicRayFilterMenuTxt.Enabled = true;
			}
			else
			{
				CosmicRayFilterCountMenuChck.Enabled = false;
				CosmicRayFilterSigmaMenuChck.Enabled = false;
				CosmicRayFilterSigmaMenuTxt.Enabled = false;
				CosmicRayFilterMenuTxt.Enabled = false;
			}
			REG.SetReg("CCDLAB", "FilterCRs", FilterCosmicRaysChckMenuItem.Checked);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void CosmicRayFilterMenuChck_Click(object sender, EventArgs e)
		{
			if (CosmicRayFilterCountMenuChck.Checked == false)
				CosmicRayFilterCountMenuChck.Checked = true;
			CosmicRayFilterSigmaMenuChck.Checked = false;
			REG.SetReg("CCDLAB", "UVCRNumberThresholdChck", CosmicRayFilterCountMenuChck.Checked);
			REG.SetReg("CCDLAB", "UVCRSigmaThresholdChck", CosmicRayFilterSigmaMenuChck.Checked);
			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
			FilterCosmicRaysChckMenuItem.ShowDropDown();
		}

		private void CosmicRayFilterSigmaMenuChck_Click(object sender, EventArgs e)
		{
			if (CosmicRayFilterSigmaMenuChck.Checked == false)
				CosmicRayFilterSigmaMenuChck.Checked = true;
			CosmicRayFilterCountMenuChck.Checked = false;
			REG.SetReg("CCDLAB", "UVCRNumberThresholdChck", CosmicRayFilterCountMenuChck.Checked);
			REG.SetReg("CCDLAB", "UVCRSigmaThresholdChck", CosmicRayFilterSigmaMenuChck.Checked);
			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
			FilterCosmicRaysChckMenuItem.ShowDropDown();
		}

		private void CosmicRayFilterSigmaMenuTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(CosmicRayFilterSigmaMenuTxt.Text);
			}
			catch
			{
				if (CosmicRayFilterSigmaMenuTxt.Text == "")
					return;
				else
					CosmicRayFilterSigmaMenuTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UVCRSigmaThreshold", CosmicRayFilterSigmaMenuTxt.Text);
		}

		private void CosmicRayFilterMenuTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(CosmicRayFilterMenuTxt.Text);
			}
			catch
			{
				if (CosmicRayFilterMenuTxt.Text == "")
					return;
				else
					CosmicRayFilterMenuTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UVCRNumberThreshold", CosmicRayFilterMenuTxt.Text);
		}

		private void ApplyFlatListToImageChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "UVApplyFlatList", ApplyFlatListToImageChck.Checked);
			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ApplyExpArrayToImageChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "ApplyExpArrayToImageChck", ApplyExpArrayToImageChck.Checked);

			if (ApplyExpArrayToImageChck.Checked)
				ListToImageExpMapCutOffDrop.Enabled = true;
			else
				ListToImageExpMapCutOffDrop.Enabled = false;

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ListToImageExpMapCutOffDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "ListToImageExpMapCutOffDrop", ListToImageExpMapCutOffDrop.SelectedIndex);
		}

		private void TryAutoDeBiasINTDrift_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "deBiasINTDrift", TryAutoDeBiasINTDrift.Checked);
			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
		}

		private void SmoothINTDriftChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "SmoothINTDrift", SmoothINTDriftChck.Checked);
			if (SmoothINTDriftChck.Checked)
				SmoothINTDriftTimeDrop.Enabled = true;
			else
				SmoothINTDriftTimeDrop.Enabled = false;
			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
		}

		private void SmoothINTDriftTimeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "SmoothINTDriftTimeDrop", SmoothINTDriftTimeDrop.SelectedIndex);
		}

		private void ListToImage1PixMenuItem_Click(object sender, EventArgs e)
		{
			UVLISTTOIMAGEPREC = 1;
			ListToImage1PixMenuItem.Checked = true;
			ListToImage2PixMenuItem.Checked = false;
			ListToImage4PixMenuItem.Checked = false;
			ListToImage8PixMenuItem.Checked = false;
			ListToImage16PixMenuItem.Checked = false;
			REG.SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ListToImage2PixMenuItem_Click(object sender, EventArgs e)
		{
			UVLISTTOIMAGEPREC = 2;
			ListToImage1PixMenuItem.Checked = false;
			ListToImage2PixMenuItem.Checked = true;
			ListToImage4PixMenuItem.Checked = false;
			ListToImage8PixMenuItem.Checked = false;
			ListToImage16PixMenuItem.Checked = false;
			REG.SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ListToImage4PixMenuItem_Click(object sender, EventArgs e)
		{
			UVLISTTOIMAGEPREC = 4;
			ListToImage1PixMenuItem.Checked = false;
			ListToImage2PixMenuItem.Checked = false;
			ListToImage4PixMenuItem.Checked = true;
			ListToImage8PixMenuItem.Checked = false;
			ListToImage16PixMenuItem.Checked = false;
			REG.SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ListToImage8PixMenuItem_Click(object sender, EventArgs e)
		{
			UVLISTTOIMAGEPREC = 8;
			ListToImage1PixMenuItem.Checked = false;
			ListToImage2PixMenuItem.Checked = false;
			ListToImage4PixMenuItem.Checked = false;
			ListToImage8PixMenuItem.Checked = true;
			ListToImage16PixMenuItem.Checked = false;
			REG.SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ListToImage16PixMenuItem_Click(object sender, EventArgs e)
		{
			UVLISTTOIMAGEPREC = 16;
			ListToImage1PixMenuItem.Checked = false;
			ListToImage2PixMenuItem.Checked = false;
			ListToImage4PixMenuItem.Checked = false;
			ListToImage8PixMenuItem.Checked = false;
			ListToImage16PixMenuItem.Checked = true;
			REG.SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
		}

		private void ConvertListToImgMenu_DropDownOpened(object sender, EventArgs e)
		{

		}

		private void UVAutoThreshChck_CheckedChanged(object sender, EventArgs e)
		{
			string chan = IMAGESET[FILELISTINDEX].Header.GetKeyValue("CHANNEL");
			if (chan.Length == 0)
				chan = IMAGESET[FILELISTINDEX].Header.GetKeyValue("DETECTOR");

			if (chan == "VIS")
			{
				UVPixelMinThresh.Value = 400;
				UVShapeMinThresh.Value = 512;

				UVPixelMaxThresh.Value = 65536;
				UVShapeMaxThresh.Value = 1638400;
			}
			else if (chan == "NUV")
			{
				UVPixelMinThresh.Value = 500;
				UVShapeMinThresh.Value = 800;

				UVPixelMaxThresh.Value = 65536;
				UVShapeMaxThresh.Value = 1638400;
			}
			else if (chan == "FUV")
			{
				UVPixelMinThresh.Value = 300;
				UVShapeMinThresh.Value = 384;

				UVPixelMaxThresh.Value = 65536;
				UVShapeMaxThresh.Value = 1638400;
			}
			else
			{
				MessageBox.Show("UVIT channel not identifiable...", "Sorry!");
			}
		}

		private void MaxMinThreshTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(MaxMinThreshTxt.Text);
			}
			catch
			{
				if (MaxMinThreshTxt.Text == "")
					return;
				else
					MaxMinThreshTxt.Text = "";
			}
			REG.SetReg("CCDLAB", "MaxMinThreshTxtText", MaxMinThreshTxt.Text);
		}

		private void MaxMinThreshChck_Click(object sender, EventArgs e)
		{
			if (MaxMinThreshChck.Checked)
			{
				MaxMinThreshTxt.Enabled = true;
				MaxMinCountTwiceChck.Enabled = true;
			}
			else
			{
				MaxMinThreshTxt.Enabled = false;
				MaxMinCountTwiceChck.Enabled = false;
			}
			REG.SetReg("CCDLAB", "MaxMinThreshChck", MaxMinThreshChck.Checked);
			REG.SetReg("CCDLAB", "MaxMinThreshTxtEnab", MaxMinThreshTxt.Enabled);
			REG.SetReg("CCDLAB", "MaxMinCountTwiceChckEnab", MaxMinCountTwiceChck.Enabled);
		}

		private void MaxMinCountTwiceChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "MaxMinCountTwiceChck", MaxMinCountTwiceChck.Checked);

			UVITMenu.ShowDropDown();
			ConvertListToImgMenu.ShowDropDown();
			MaxMinThreshChck.ShowDropDown();
		}

		private void ConvertListToImgMenu_Click(object sender, EventArgs e)
		{
			string[] IntsFileList;
			if (UVCREATEIMAGENOW)
			{
				UVCREATEIMAGENOW = false;
				UVCONVERTLISTTOIMAGEBATCH = false;
				IntsFileList = new string[] { UVCREATEIMAGEFILENAME };
				ConvertUVCentroidListToImgWrkr.RunWorkerAsync(IntsFileList);
			}
			else
			{
				UVITMenu.HideDropDown();
				ConvertListToImgMenu.HideDropDown();
				string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				OpenFileDialog dlg = new OpenFileDialog();
				dlg.InitialDirectory = dir;
				dlg.Filter = "FITS (*.fits)|*.fits";
				dlg.Multiselect = true;
				dlg.Title = "Select the Centroid INTEGERS List(s) (_XYInts_List)";
				DialogResult res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;

				IntsFileList = dlg.FileNames;
				int ind = IntsFileList[0].LastIndexOf("\\");
				dir = IntsFileList[0].Substring(0, ind);
				REG.SetReg("CCDLAB", "L2EventListPath", dir);

				UVCONVERTLISTTOIMAGEBATCH = true;
				AUTOLOADIMAGESFILES = new string[IntsFileList.Length];
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = IntsFileList.Length;
				WAITBAR.Text = "Creating image(s)...";
				this.Enabled = false;
				ConvertUVCentroidListToImgWrkr.RunWorkerAsync(IntsFileList);
				WAITBAR.ShowDialog();
			}
		}

		private void ConvertUVCentroidListToImgWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string[] IntsFileList = (string[])e.Argument;
			double exp_cutoff = Convert.ToDouble(ListToImageExpMapCutOffDrop.SelectedItem.ToString()) / 100;

			bool do_parallel = true;
			if (UVIT_DEROTATE_WCS || IntsFileList.Length == 1 || L1MachineStandardChck.Checked)
				do_parallel = false;
			ParallelOptions opts = new ParallelOptions();
			if (do_parallel)
				opts.MaxDegreeOfParallelism = Environment.ProcessorCount;
			else
				opts.MaxDegreeOfParallelism = 1;
			int count = 0;			

			Parallel.For(0, IntsFileList.Length, opts, (wrkri, loopstate) =>
			{
				if (UVCONVERTLISTTOIMAGEBATCH)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						loopstate.Stop(); //continue;

					lock (opts)
					{
						count++;
						ConvertUVCentroidListToImgWrkr.ReportProgress(count);
					}
				}

				string IntsFile = IntsFileList[wrkri];
				string FracFile = IntsFile.Replace("Ints", "Frac");

				JPFITS.FITSImage IntsFits = new JPFITS.FITSImage(IntsFile, null, true, true, false, !do_parallel);
				JPFITS.FITSImage FracFits = new JPFITS.FITSImage(FracFile, null, true, true, false, !do_parallel);
				int NPts = FracFits.Height;

				string channel = IntsFits.Header.GetKeyValue("CHANNEL");
				if (channel.Length == 0)
					channel = IntsFits.Header.GetKeyValue("DETECTOR");

				double prec = UVLISTTOIMAGEPREC;

				string EXTXRNG = FracFits.Header.GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
				if (EXTXRNG == "")
					EXTXRNG = "0:511";//from L2 data
				string EXTYRNG = FracFits.Header.GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
				if (EXTYRNG == "")
					EXTYRNG = "0:511";//from L2 data
				int ix = EXTXRNG.IndexOf(":");
				int iy = EXTYRNG.IndexOf(":");
				double rx1 = Convert.ToDouble(EXTXRNG.Substring(0, ix));//range start
				double ry1 = Convert.ToDouble(EXTYRNG.Substring(0, iy));
				double rx2 = Convert.ToDouble(EXTXRNG.Substring(ix + 1));//range end
				double ry2 = Convert.ToDouble(EXTYRNG.Substring(iy + 1));

				string xoffset = FracFits.Header.GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
				if (xoffset == "")
					xoffset = FracFits.Header.GetKeyValue("WIN_XOFF");//from L2 data
				double ox = Convert.ToDouble(xoffset);//x offset
				string yoffset = FracFits.Header.GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
				if (yoffset == "")
					yoffset = FracFits.Header.GetKeyValue("WIN_YOFF");//from L2 data
				double oy = Convert.ToDouble(yoffset);//y offset
				string sizex = FracFits.Header.GetKeyValue("XSIZE");
				if (sizex == "")
					sizex = FracFits.Header.GetKeyValue("WIN_X_SZ");
				double szx = Convert.ToDouble(sizex);//x size
				string sizey = FracFits.Header.GetKeyValue("YSIZE");
				if (sizey == "")
					sizey = FracFits.Header.GetKeyValue("WIN_Y_SZ");
				double szy = Convert.ToDouble(sizey);//y size

				if (rx1 != 0 || rx2 != 511)
					szx = rx2 - rx1;
				if (ry1 != 0 || ry2 != 511)
					szy = ry2 - ry1;

				if (L1CentroidPaddingChck.Checked)
				{
					if (PCCentroidPaddingDrop.SelectedIndex == 0)
						UVPCMODEPADOFFSET = 22;
					if (PCCentroidPaddingDrop.SelectedIndex == 1)
						UVPCMODEPADOFFSET = 44;
				}
				else
					UVPCMODEPADOFFSET = 0;

				szx = (szx + 1 + 2 * UVPCMODEPADOFFSET) * prec;
				szy = (szy + 1 + 2 * UVPCMODEPADOFFSET) * prec;

				double[] times;//need times for total integration time calculation, and also if CR frames are removed
				string TimeFileList = IntsFile.Remove(IntsFile.IndexOf("XYInts_List")) + "TimeList.fits";
				string deDrift = "_deDrift";
				while (IntsFile.Contains(deDrift))
				{
					TimeFileList = TimeFileList.Replace("TimeList", "TimeList_deDrift");
					deDrift += "_deDrift";
				}
				if (IntsFile.Contains("_ROIx"))
					TimeFileList = TimeFileList.Replace(".fits", "") + IntsFile.Substring(IntsFile.IndexOf("_ROIx"));
				if (!File.Exists(TimeFileList))
				{
					MessageBox.Show("Problem finding the time list file...", "Stopping...");
					WAITBAR.CancelBtn.PerformClick();
					loopstate.Stop(); //continue;
				}

				string BJDFileList = TimeFileList.Replace("TimeList", "BJDList");

				string FrameFileList = TimeFileList.Replace("Time", "Frame");
				double[] frames;
				if (!File.Exists(FrameFileList))
				{
					MessageBox.Show("Problem finding the frame list file...", "Stopping...");
					WAITBAR.CancelBtn.PerformClick();
					loopstate.Stop(); //continue;
				}

				string ExpArrayFileList = TimeFileList.Replace("TimeList", "ExpArrayList");
				bool applyexposureweight = ApplyExpArrayToImageChck.Checked;
				if (UVREGISTRATION)
					applyexposureweight = false;
				double[] expweightlist = null;
				if (applyexposureweight && !File.Exists(ExpArrayFileList))
				{
					MessageBox.Show("Problem finding the Exposure Array file...", "Stopping...");
					WAITBAR.CancelBtn.PerformClick();
					loopstate.Stop(); //continue;
				}
				if (applyexposureweight)
					expweightlist = JPFITS.FITSImage.ReadImageVectorOnly(ExpArrayFileList, null, !do_parallel);

				string FlatFileList;
				double[] flats = null;
				bool applyFlat = ApplyFlatListToImageChck.Checked;
				if (applyFlat)
				{
					FlatFileList = TimeFileList.Replace("Time", "Flat");
					if (!File.Exists(FlatFileList))
					{
						MessageBox.Show("Problem finding the flat list file...", "Stopping...");
						WAITBAR.CancelBtn.PerformClick();
						loopstate.Stop(); //continue;
					}

					flats = FITSImage.ReadImageVectorOnly(FlatFileList, null, !do_parallel);
				}

				bool maxminReject = MaxMinThreshChck.Checked;
				bool maxminCountTwice = MaxMinCountTwiceChck.Checked;
				double maxminThresh = Convert.ToDouble(MaxMinThreshTxt.Text);
				string MaxMinFileList;
				double[,] mdMm = null;
				if (maxminReject)
				{
					MaxMinFileList = TimeFileList.Replace("TimeList", "XYmdMm_List");
					if (!File.Exists(MaxMinFileList))
					{
						MessageBox.Show("Problem finding the corner stats list file...", "Stopping...");
						WAITBAR.CancelBtn.PerformClick();
						loopstate.Stop(); //continue;
					}

					mdMm = FITSImage.ReadImageArrayOnly(MaxMinFileList, null, !do_parallel);
				}

				times = FITSImage.ReadImageVectorOnly(TimeFileList, null, !do_parallel);
				frames = FITSImage.ReadImageVectorOnly(FrameFileList, null, !do_parallel);//should be no roll-overs in these
				double time_per_frame = (times[times.Length - 1] - times[0]) / 1000 / (frames[times.Length - 1] - frames[0]);//need to subtract this from total integration time whenver a CR frame is rejected
				string multstr = IntsFits.Header.GetKeyValue("TIMEMULT");
				double mult = 1;
				if (multstr != "")
					mult = Convert.ToDouble(multstr);
				double physicaltime = (times[times.Length - 1] - times[0] + time_per_frame * mult) / 1000;
				//double datatime = time_per_frame*(mult-1);
				int CRthresh = 0;
				//double CRSigmaThresh = 0;
				bool filterCR = FilterCosmicRaysChckMenuItem.Checked;//used in the actual loop accumulating centroids
				bool FilterCRSigma = CosmicRayFilterSigmaMenuChck.Checked;
				bool FilterCRCount = CosmicRayFilterCountMenuChck.Checked;
				if (filterCR)//then load corresponding time list to search for highly repeated times to reject
				{
					//compute CRthresh for use below..it is either from the integer or sigma
					if (FilterCRCount)//integer
						CRthresh = Convert.ToInt32(CosmicRayFilterMenuTxt.Text);
					if (FilterCRSigma)//then set CRthresh given the sigma (use CRthresh as integer after computing sigma)
					{
						//find number of unique times
						int c = 1;
						double t0 = times[0];
						for (int i = 0; i < times.Length; i++)
						{
							if (t0 != times[i])
							{
								c++;
								t0 = times[i];
							}
						}

						double[] framecount = new double[c];
						c = 0;
						t0 = times[0];
						int ind = -1;
						for (int i = 0; i < times.Length; i++)
						{
							if (t0 == times[i])
							{
								c++;
							}
							else
							{
								ind++;
								framecount[ind] = (double)(c);
								c = 1;
								t0 = times[i];
							}
						}
						framecount[ind + 1] = (double)(c);

						double sigma = Convert.ToDouble(CosmicRayFilterSigmaMenuTxt.Text);
						double rmean = JPMath.Median(framecount);//JPMath.Mean_RobustClipped(framecount,sigma);
						double std = Math.Sqrt(rmean);

						CRthresh = (int)(rmean + sigma * std + 1); //+1 in order to ciel it
						CosmicRayFilterMenuTxt.Text = CRthresh.ToString();

					}//end filterCRSgima
				}

				int nCRframes = 0;
				double oldtime = -1;
				double[,] img = new double[(int)szx, (int)szy];
				int xpos, ypos, el;
				double centroidweight;
				//bool exparrasctspersec = ExpArrayAsCtsperSecMenuChck.Checked;

				/*try
				{*/

				double rx132ox32 = -rx1 * 32 - ox * 32;
				double ry132oy32 = -ry1 * 32 - oy * 32;
				double precB32 = prec / 32;
				int PADOFFPREC = UVPCMODEPADOFFSET * (int)(prec);

				for (int j = 0; j < NPts; j++)
				{
					if (oldtime != times[j])
					{
						//datatime += time_per_frame;
						if (!filterCR)
							oldtime = times[j];
					}

					el = j;
					if (filterCR && oldtime != times[j])
					{
						oldtime = times[j];
						int c = 0;
						while (times[j] == times[j + c])
						{
							c++;
							if ((j + c) >= NPts)
								break;
						}
						if (c > CRthresh)//CR frame rejected
						{
							j = j + c;
							//datatime -= time_per_frame;
							nCRframes++;
							continue;
						}
					}

					xpos = (int)((IntsFits[0, j] + rx132ox32 + FracFits[0, j] + 16) * precB32) + PADOFFPREC;//reset integers to start at 0
					ypos = (int)((IntsFits[1, j] + ry132oy32 + FracFits[1, j] + 16) * precB32) + PADOFFPREC;//must add 16 to fractionals

					if (xpos < 0 || ypos < 0 || xpos >= szx || ypos >= szy)//ignore out of bounds
						continue;

					//if centroid decimal out of range (edge effect)
					/*if (FracFits[0, j] * FracFits[0, j] + FracFits[1, j] * FracFits[1, j] > 10 * 10)
						continue;*/

					//if max-min threshold - reject
					if (maxminReject && !maxminCountTwice)
						if (mdMm[1, j] > maxminThresh)
							continue;

					centroidweight = 1;

					if (applyexposureweight)
						if (expweightlist[j] < exp_cutoff)//leave out of image if scaling is more than 1/0.2 = 5 times!
							continue;
						else
							centroidweight = 1 / expweightlist[j];//cts per second OR absolute...depending if switch was set during exparray creation time during applydriftseries

					if (applyFlat)
						centroidweight /= flats[j];

					if (maxminReject && maxminCountTwice)
					{
						if (mdMm[1, j] > maxminThresh)//mdMm only loaded if maxminCountTwice and maxminReject
						{
							img[xpos, ypos] += 2 * centroidweight;
						}
					}
					else
						img[xpos, ypos] += centroidweight;
				}
				/*}
				catch (.Exception e)
				{
					MessageBox.Show(e.Message + "   " + xpos.ToString() + "   " + ypos.ToString() + "    "   + el.ToString());// + "   " + FracFits[0,j].ToString() + "   " + FracFits[1,j].ToString() );
					MessageBox.Show(IntsFits[0,el].ToString() + "	" + IntsFits[1,el].ToString() + "	" + FracFits[0,el].ToString() + "	" + FracFits[1,el].ToString());
					MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
				}*/

				string imgname = IntsFile.Replace("_XYInts_List", "");
				imgname = imgname.Replace(".fits", "_IMAGE_x" + prec.ToString() + ".fits");
				if (filterCR)
					imgname = imgname.Replace(".fits", "_deCR" + CRthresh.ToString() + ".fits");
				if (applyFlat)
					imgname = imgname.Replace(".fits", "_deFlat.fits");
				if (maxminReject)
					imgname = imgname.Replace(".fits", "_deMm" + maxminThresh.ToString() + ".fits");
				if (applyexposureweight)
					imgname = imgname.Replace(".fits", "_deExp" + ListToImageExpMapCutOffDrop.SelectedItem.ToString() + ".fits");

				JPFITS.FITSImage fitsimg = new FITSImage(imgname, img, false, !do_parallel);
				fitsimg.Header.CopyHeaderFrom(FracFits.Header);//  CopyHeader(FracFits);

				double missingframephotredc = 0, parityphotredc = 0;
				try
				{
					missingframephotredc = Convert.ToDouble(fitsimg.Header.GetKeyValue("FRAMREDC"));
					parityphotredc = Convert.ToDouble(fitsimg.Header.GetKeyValue("PARTREDC"));
				}
				catch
				{
					missingframephotredc = 0;
					parityphotredc = 0;
				}
				double datatime = physicaltime * (1 - missingframephotredc) - nCRframes * time_per_frame;
				double rdcdtime = datatime * (1 - parityphotredc);

				fitsimg.Header.AddKey("TIMEPERF", time_per_frame.ToString("#.000000"), "Time per Frame (s)", 14);
				fitsimg.Header.AddKey("FRAMPERS", (1 / time_per_frame).ToString("#.000"), "Frames per Second", 14);
				fitsimg.Header.AddKey("NCOSMICF", nCRframes.ToString(), "Number of rejected cosmic ray frames", 14);
				fitsimg.Header.AddKey("PHYSTIME", physicaltime.ToString("#.000"), "Physical Integration Time for Image (s)", 14);
				fitsimg.Header.AddKey("DATATIME", datatime.ToString("#.000"), "PHYSTIME Reduced for Cosmic and Missing Frames", 14);
				fitsimg.Header.AddKey("RDCDTIME", rdcdtime.ToString("#.000"), "DATATIME Reduced for Parity Errors (s)", 14);
				fitsimg.Header.SetKey("EXP_TIME", rdcdtime.ToString("#.000"), "Same as RDCDTIME-Final Science Integration Time", true, 14);
				if (applyexposureweight)
					fitsimg.Header.SetKey("EXPMAPCO", (exp_cutoff * 100).ToString(), "Exposure Map CutOff (PERCENT of RDCDTIME)", true, 14);
				else
					fitsimg.Header.SetKey("EXPMAPCO", "0", "No cut-off - all centroids included.", true, 14);

				double bjd0 = 0;
				try
				{
					bjd0 = Convert.ToDouble(fitsimg.Header.GetKeyValue("BJD0"));
				}
				catch
				{
					if (File.Exists(BJDFileList))
					{
						double[] bjd = FITSImage.ReadImageVectorOnly(BJDFileList, null, !do_parallel);
						bjd0 = bjd[0];
					}
				}
				double meanBJD = bjd0 + physicaltime / 2 / 1000 / 86400;
				fitsimg.Header.AddKey("MEANBJD", meanBJD.ToString("#.0000000"), "Mean Barycentric Julian Date for Image", 12);

				if (filterCR)
				{
					fitsimg.Header.AddKey("CRCUTOFF", CRthresh.ToString(), "Cosmic Ray Cutoff Count per Frame Threshold", 13);
					fitsimg.Header.AddKey("CRFRTIME", ((double)(nCRframes) * time_per_frame / 1000).ToString("#.000"), "Cosmic Ray Time Removed from Original List", 13);
				}

				if (maxminReject)
				{
					fitsimg.Header.AddKey("MAXMINTH", maxminThresh.ToString(), "Max-Min Threshold", 12);
					if (maxminCountTwice)
						fitsimg.Header.AddKey("MAXMINCT", "true", "Max-Min Threshold Counted Twice", 12);
				}

				fitsimg.Header.AddKey("IMAGPREC", prec.ToString(), "Image Pixel Precision", 13);
				fitsimg.Header.AddKey("PADOFSET", UVPCMODEPADOFFSET.ToString(), "Image Padding (CMOS pixels)", 13);

				if (UVIT_DEROTATE_WCS)//then re-compute WCS from de-rotated image...need to re-get centroids from image, update their CP1/2_ values in header, then do & update WCS params
				{
					if (wrkri == 0)//get CV's & CP's...CP's will need to be updated with new centroids for the first file only
					{
						int num = 0, key = 0;
						while (key != -1)
						{
							num++;
							key = fitsimg.Header.GetKeyIndex("WCP1_" + num.ToString("000"), false);
						}
						num--;
						double[] xpix = new double[num];
						double[] ypix = new double[num];
						double[] radeg = new double[num];
						double[] dedeg = new double[num];
						int goodcount = 0;
						for (int j = 1; j <= num; j++)
						{
							xpix[goodcount] = Convert.ToDouble(fitsimg.Header.GetKeyValue("WCP1_" + j.ToString("000")));
							ypix[goodcount] = Convert.ToDouble(fitsimg.Header.GetKeyValue("WCP2_" + j.ToString("000")));
							radeg[goodcount] = Convert.ToDouble(fitsimg.Header.GetKeyValue("WCV1_" + j.ToString("000")));
							dedeg[goodcount] = Convert.ToDouble(fitsimg.Header.GetKeyValue("WCV2_" + j.ToString("000")));

							if (xpix[goodcount] > 0 && ypix[goodcount] > 0 && xpix[goodcount] < szx && ypix[goodcount] < szy)
								goodcount++;
						}
						Array.Resize(ref xpix, goodcount - 1);
						Array.Resize(ref ypix, goodcount - 1);
						Array.Resize(ref radeg, goodcount - 1);
						Array.Resize(ref dedeg, goodcount - 1);
						//now have CP's and CV's...now need to re-do centroids at CV locations
						PSES = new PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
						PSESINDEX = 0;
						PSES[PSESINDEX].Extract_Sources(fitsimg.Image, xpix, ypix, 2, false, "");
						xpix = PSES[PSESINDEX].Centroids_X;
						ypix = PSES[PSESINDEX].Centroids_Y;
						WCS_DEROT = new JPFITS.WorldCoordinateSolution();
						WCS_DEROT.Solve_WCS("TAN", xpix, ypix, true, radeg, dedeg, fitsimg.Header);
					}
					else
						WCS_DEROT.CopyTo(fitsimg.Header);
					//fitsimg is now updated with new WCS for new derotated image
				}

				if (applyFlat || applyexposureweight)
					fitsimg.WriteImage(TypeCode.Double, !do_parallel);
				else
					fitsimg.WriteImage(TypeCode.Int32, !do_parallel);

				if (!do_parallel)
					e.Result = imgname;//used in wrkr complete, for single image modes

				if (UVDRIFTBATCH)
					AUTOLOADIMAGESFILES[UVDRIFTBATCHFILESINDEX] = imgname;

				if (UVCONVERTLISTTOIMAGEBATCH)
					AUTOLOADIMAGESFILES[wrkri] = imgname;
			});
		}

		private void ConvertUVCentroidListToImgWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Converting file " + (e.ProgressPercentage).ToString() + " of " + WAITBAR.ProgressBar.Maximum.ToString() + " to image.";
			WAITBAR.Refresh();
		}

		private void ConvertUVCentroidListToImgWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (UVIT_DEROTATE_WCS)
				UVIT_DEROTATE_WCS = false;

			if (!UVCONVERTLISTTOIMAGEBATCH)
			{
				string imgname = (string)e.Result;
				if (!UVDRIFTAUTORUN)
				{
					if (!UVREGISTRATION)
						if (MessageBox.Show("Image Creation Completed.  Would you like to view it?", "Finished...", MessageBoxButtons.YesNo) == DialogResult.No)
						{
							this.Enabled = true;
							this.BringToFront();
							return;
						}

					FileListDrop.Items.Clear();
					IMAGESET.Clear();
					string[] filelist = new string[] { imgname };
					AddToImageSet(filelist, true);
					this.Enabled = true;
					this.BringToFront();

					if (UVREGISTRATION)
					{
						//update registration points by shifting anchor (and all the rest) to closest local maximum of anchor
						if (UVREGISTRATIONFILESINDEX > 0)
						{
							float xsc = ((float)(ImageWindow.Size.Width) / (float)IMAGESET[FILELISTINDEX].Width);//image window size per data image pixel
							float ysc = ((float)(ImageWindow.Size.Height) / (float)IMAGESET[FILELISTINDEX].Height);

							double[,] subim = IMAGESET[FILELISTINDEX].GetSubImage(MANREGCOORDS[0, 0], MANREGCOORDS[0, 1], SUBIMAGE_HWX, SUBIMAGE_HWY);
							int x, y;
							JPMath.Max(subim, out x, out y, false);
							x -= SUBIMAGE_HWX;
							y -= SUBIMAGE_HWY;
							for (int i = 0; i < MANREGCOORDS.GetLength(0); i++)
							{
								MANREGCOORDS[i, 0] += x;
								MANREGCOORDS[i, 1] += y;
								MANREGCOORDRECTS[i] = new Rectangle((int)(((float)(MANREGCOORDS[i, 0] + 1)) * xsc - 3), (int)(((float)(MANREGCOORDS[i, 1] + 1)) * ysc - 3), 7, 7);
							}
							ImageUpD(IMAGESET[FILELISTINDEX].Image);
							SubImageUpD();
						}
						try
						{
							File.Delete(imgname);
						}
						catch { }

						if (UVITAUTOREGISTER)
						{
							ProgressBar.Value = UVREGISTRATIONFILESINDEX + 1;
							ProgressBar.Refresh();

							ImageWindow_MouseUp(sender, new MouseEventArgs(MouseButtons.Right, 1, 0, 0, 0));
						}
						else
						{
							ProgressBar.Maximum = 2;
							ProgressBar.Value = 2;
							ProgressBar.Refresh();
						}
					}
				}
				else
				{
					if (UVAutoDriftImageViewChck.Checked)
					{
						WAITBAR.TextMsg.Text = "Loading image...";
						WAITBAR.Text = "Viewing...";
						WAITBAR.Refresh();

						FileListDrop.Items.Clear();
						IMAGESET.Clear();
						string[] filelist = new string[] { imgname };
						AddToImageSet(filelist, true);
					}
					WAITBAR.CancelBtn.Enabled = true;
					if (!UVDRIFTBATCH)
					{
						WAITBAR.Hide();
						WAITBAR.Close();
						this.Enabled = true;
					}
					else
					{
						UVDRIFTBATCHFILESINDEX++;
						if (UVDRIFTBATCHFILESINDEX < UVDRIFTBATCHFILES.Length)//continue batch
						{
							if (!DRIFTFROMPCPSTRACK)
								CreateDriftFromPCMenuItem_DoubleClick(sender, e);
							else
								DriftFromPCPSTrackBtn_Click(sender, e);
						}
						else
						{
							DRIFTFROMPCPSTRACK = false;
							UVDRIFTBATCH = false;
							UVDRIFTAUTORUN = false;
							WAITBAR.Hide();
							WAITBAR.Close();
							this.Enabled = true;
							this.BringToFront();
							TimeSpan ts = DateTime.Now - DATE;
							/*DialogResult res = MessageBox.Show("Finished the batch of drift corrections in " + ts.Minutes.ToString() + "m" + ts.Seconds.ToString() + "s.  Would you like to view the images?", "Complete. View Images?", MessageBoxButtons.YesNo);
							if (res == DialogResult.No)
								return;*/
							AUTOLOADIMAGES = true;
							IMAGESET = new FITSImageSet();
							FMLoad_Click(sender, e);
							//FMLoad.PerformClick();
						}
					}
				}
			}
			else
			{
				UVCONVERTLISTTOIMAGEBATCH = false;
				if (WAITBAR.DialogResult == DialogResult.Cancel)
				{
					this.Enabled = true;
					this.BringToFront();
					UVITPOSTMERGE = false;
					return;
				}

				WAITBAR.Hide();
				WAITBAR.Close();
				this.Enabled = true;
				this.BringToFront();

				/*if (MessageBox.Show("Finished converting the list(s) to image(s).  Would you like to load them?","View?",MessageBoxButtons.YesNo) == DialogResult.No)
					return;*/

				AUTOLOADIMAGES = true;

				if (AUTOVISDRIFTAPPLY && FUVDIREXISTS && NUVDIREXISTS)
				{
					FUVDIREXISTS = false;
					IMAGESET = new FITSImageSet();
					FMLoad_Click(sender, e);
					DONUVDRIFTNOW = true;
					ConsolidateNUVApplyToFUV_Click(sender, e);
					return;
				}
				else if (AUTOVISDRIFTAPPLY && !FUVDIREXISTS && NUVDIREXISTS)
				{
					FUVDIREXISTS = false;
					NUVDIREXISTS = false;
					AUTOVISDRIFTAPPLY = false;
					FMLoad_Click(sender, e);
					return;
				}

				if (MASTERAUTOLOADADDIN != null)
				{
					//int c = 0;
					Array.Resize(ref AUTOLOADIMAGESFILES, AUTOLOADIMAGESFILES.Length + MASTERAUTOLOADADDIN.Count);
					for (int i = AUTOLOADIMAGESFILES.Length - MASTERAUTOLOADADDIN.Count; i < AUTOLOADIMAGESFILES.Length; i++)
						AUTOLOADIMAGESFILES[i] = (string)MASTERAUTOLOADADDIN[i - AUTOLOADIMAGESFILES.Length + MASTERAUTOLOADADDIN.Count];
					MASTERAUTOLOADADDIN = null;
				}

				IMAGESET = new FITSImageSet();
				FMLoad_Click(sender, e);

				if (UVITPOSTMERGE)
				{
					UVITPOSTMERGE = false;
					if (UVAutoPSFPostMergeChck.Checked)
					{
						PointSrcROIAutoRunChck.Checked = true;
						PointSrcROIFindSrcChck.Checked = true;
						PointSrcROIFindNSrcDrop.SelectedIndex = 2;
						DriftFromPCPSTrackBtn_Click(sender, e);
						return;
					}
				}
			}
		}

		private void ExtractL1gzsMenuItem_Click(object sender, EventArgs e)
		{
			L1AutoRunChck.HideDropDown();
			ExtractL1gzsMenuItem.HideDropDown();
			UVITMenu.HideDropDown();

			if (!Directory.Exists("C:\\UVIT_CalDB"))
			{
				MessageBox.Show("UVIT Calibration Database not present at C:\\UVIT_CalDB\\  \r\n\r\nPlease gather it from: \r\r https://github.com/user29A/UVITCalDB/releases", "Error...");
				return;
			}

			if (!Directory.Exists("C:\\Program Files\\7-Zip"))
			{
				MessageBox.Show("7-Zip not installed on this system.  Please download & install the 64-bit version from 7-zip.org to C:\\Program Files\\7-Zip", "Error...");
				return;
			}

			OpenFileDialog ofd = new OpenFileDialog();
			ofd.InitialDirectory = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			ofd.Filter = "GZip or ZIP Archive|*.gz;*.zip";
			ofd.Multiselect = false;// true;//no need to do this//removed from code
			DialogResult res = ofd.ShowDialog();
			if (res == DialogResult.Cancel)
				return;

			string dir = new DirectoryInfo(ofd.FileName).Parent.FullName;
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			//this.Enabled = false;
			ExtractL1ArchiveBGWrkr.RunWorkerAsync(ofd.FileName);
		}

		private void ExtractL1ArchiveBGWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string file = (string)e.Argument;
			string extdir = new DirectoryInfo(file).Parent.FullName;
			string archdir = extdir + "\\archive";
			Directory.CreateDirectory(archdir);

			ProcessStartInfo psi = new ProcessStartInfo("c:\\Program Files\\7-Zip\\7zG.exe");
			psi.Arguments = "\"x\" " + "\"" + file + "\" " + "\"-o" + extdir;
			Process proc = Process.Start(psi);
			proc.WaitForExit();
			if (proc.ExitCode != 0)
			{
				e.Result = DialogResult.Cancel;
				return;
			}
			e.Result = DialogResult.OK;
			File.Move(file, archdir + "\\" + file.Substring(file.LastIndexOf("\\") + 1));
		}

		private void ExtractL1ArchiveBGWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e) {; }

		private void ExtractL1ArchiveBGWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			//this.Enabled = true;
			this.BringToFront();
			if ((DialogResult)e.Result == DialogResult.Cancel)
				return;

			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			string[] L1FITSImages = Directory.GetFiles(dir, "*level1.fits", SearchOption.AllDirectories);
			//remember where the L1 files folder was to delete it after
			string[] alldirs = Directory.GetDirectories(dir);
			string deldir = "";
			for (int i = 0; i < alldirs.Length; i++)
				if (Directory.GetFiles(alldirs[i], "*level1.fits", SearchOption.AllDirectories).Length > 0)
				{
					deldir = alldirs[i];
					break;
				}

			for (int j = 0; j < L1FITSImages.Length; j++)
			{
				string newL1file = dir + "\\" + L1FITSImages[j].Substring(L1FITSImages[j].LastIndexOf("\\") + 1);
				while (File.Exists(newL1file))//then need to add some appendage
				{
					int ind = newL1file.LastIndexOf(".");
					if (newL1file.Substring(ind - 1, 1) == ")")
					{
						int num = Convert.ToInt32(newL1file.Substring(newL1file.LastIndexOf("(") + 1, newL1file.LastIndexOf(")") - 1 - newL1file.LastIndexOf("(")));
						newL1file = newL1file.Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
					}
					else
					{
						newL1file = newL1file.Insert(ind, " (1)");
						if (File.Exists(newL1file))
						{
							int num = Convert.ToInt32(newL1file.Substring(newL1file.LastIndexOf("(") + 1, newL1file.LastIndexOf(")") - 1 - newL1file.LastIndexOf("(")));
							newL1file = newL1file.Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
						}
					}
				}
				File.Move(L1FITSImages[j], newL1file);
			}

			string[] L1tctfiles = Directory.GetFiles(dir, "*level1.tct", SearchOption.AllDirectories);
			for (int j = 0; j < L1tctfiles.Length; j++)
			{
				string newL1file = dir + "\\" + L1tctfiles[j].Substring(L1tctfiles[j].LastIndexOf("\\") + 1);
				while (File.Exists(newL1file))//then need to add some appendage
				{
					int ind = newL1file.LastIndexOf(".");
					if (newL1file.Substring(ind - 1, 1) == ")")
					{
						int num = Convert.ToInt32(newL1file.Substring(newL1file.LastIndexOf("(") + 1, newL1file.LastIndexOf(")") - 1 - newL1file.LastIndexOf("(")));
						newL1file = newL1file.Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
					}
					else
					{
						newL1file = newL1file.Insert(ind, " (1)");
						if (File.Exists(newL1file))
						{
							int num = Convert.ToInt32(newL1file.Substring(newL1file.LastIndexOf("(") + 1, newL1file.LastIndexOf(")") - 1 - newL1file.LastIndexOf("(")));
							newL1file = newL1file.Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
						}
					}
				}
				File.Move(L1tctfiles[j], newL1file);
			}

			string[] L1lbtfiles = Directory.GetFiles(dir, "*level1.lbt", SearchOption.AllDirectories);
			for (int j = 0; j < L1lbtfiles.Length; j++)
			{
				string newL1file = dir + "\\" + L1lbtfiles[j].Substring(L1lbtfiles[j].LastIndexOf("\\") + 1);
				while (File.Exists(newL1file))//then need to add some appendage
				{
					int ind = newL1file.LastIndexOf(".");
					if (newL1file.Substring(ind - 1, 1) == ")")
					{
						int num = Convert.ToInt32(newL1file.Substring(newL1file.LastIndexOf("(") + 1, newL1file.LastIndexOf(")") - 1 - newL1file.LastIndexOf("(")));
						newL1file = newL1file.Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
					}
					else
					{
						newL1file = newL1file.Insert(ind, " (1)");
						if (File.Exists(newL1file))
						{
							int num = Convert.ToInt32(newL1file.Substring(newL1file.LastIndexOf("(") + 1, newL1file.LastIndexOf(")") - 1 - newL1file.LastIndexOf("(")));
							newL1file = newL1file.Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
						}
					}
				}
				File.Move(L1lbtfiles[j], newL1file);
			}

			Directory.Delete(deldir, true);

			if (!L1AutoRunChck.Checked)
				if (MessageBox.Show("Finished processing folders.  Would you like to proceed with file digestion?", "Proceed?", MessageBoxButtons.YesNo) == DialogResult.No)
					return;

			SPAREFITSImageSet = new FITSImageSet();

			string[] files = Directory.GetFiles(dir, "*level1*.fits");
			DATE = DateTime.Now;
			//this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.Text = "Digesting L1 Files...";
			WAITBAR.ProgressBar.Maximum = files.Length;
			DigestL1Wrkr.RunWorkerAsync(files);
			WAITBAR.ShowDialog();
		}

		private void DigestL1FITSImageMenuItem_Click(object sender, EventArgs e)
		{
			UVITMenu.HideDropDown();
			DigestL1FITSImageMenuItem.HideDropDown();
			L1AutoRunChck.Checked = false;

			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "L1 Event List (*.fits)|*.fits";
			dlg.Multiselect = true;
			dlg.Title = "Please select the L1 files...";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;

			dir = dlg.FileNames[0].Substring(0, dlg.FileNames[0].LastIndexOf("\\"));
			bool multidir = false;
			for (int i = 0; i < dlg.FileNames.Length; i++)
				if (dir != dlg.FileNames[i].Substring(0, dlg.FileNames[i].LastIndexOf("\\")))
				{
					multidir = true;
					dir = dir.Substring(0, dir.LastIndexOf("\\"));
					break;
				}
			REG.SetReg("CCDLAB", "L2EventListPath", dir);
			REG.SetReg("CCDLAB", "L1ExtractMultiDir", multidir);

			if (L1TBCChck.Checked)//must establish reference tickcount to imageframetime
			{
				DO_TBC = true;
				DialogResult resl = TBC_Reference(dlg.FileNames);
				if (resl == DialogResult.OK)
					MessageBox.Show("Found Reference:  TICKCOUNT = " + TBC_TICKCOUNTREF + "; FRAMETIME = " + TBC_FRAMETIMEREF + "; TIME = " + TBC_TIMEREF);
				if (resl == DialogResult.Yes)
				{
					try
					{
						TBC_TICKCOUNTREF = Convert.ToInt64(REG.GetReg("CCDLAB", "TBC_TICKCOUNTREF"));
						TBC_FRAMETIMEREF = Convert.ToInt64(REG.GetReg("CCDLAB", "TBC_FRAMETIMEREF"));
						TBC_TIMEREF = Convert.ToDouble(REG.GetReg("CCDLAB", "TBC_TIMEREF"));
					}
					catch { }
					MessageBox.Show("Using Previous Reference:  TICKCOUNT = " + TBC_TICKCOUNTREF + "; FRAMETIME = " + TBC_FRAMETIMEREF + "; TIME = " + TBC_TIMEREF);
				}
				if (resl == DialogResult.No)
					DO_TBC = false;
				if (resl == DialogResult.Cancel)
					return;
			}

			SPAREFITSImageSet = new FITSImageSet();

			DATE = DateTime.Now;
			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.Text = "Digesting L1 Files...";
			WAITBAR.ProgressBar.Maximum = dlg.FileNames.Length;
			DigestL1Wrkr.RunWorkerAsync(dlg.FileNames);
			WAITBAR.ShowDialog();
		}

		private void DigestL1Wrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string[] argfiles = (string[])e.Argument;
			ArrayList dir_list = new ArrayList();
			bool ApplyDIST = L1DigestApplyDISTChck.Checked;
			bool ApplyFPN = L1DigestApplyFPNChck.Checked;
			bool discardparityerror = L1DigestPCParityChck.Checked;
			bool discardtimebool = L1DiscardDataTimeChck.Checked;
			bool interpDISTBiLin = L1DigestApplyDISTInterpBiLinChck.Checked;
			bool do_parallel_L1 = L1MachineExtremeChck.Checked;

			//TCT get the .tct file, and get the delta between absolute time and detector time from the first element in those tables
			//apply (add) that difference to all detector times in order to get absolute local JD times, then use that to get BJD
			double JD_abs_time_delta_sec = Double.MinValue;
			string tctfile = argfiles[0].Substring(0, argfiles[0].LastIndexOf("uvt")) + "uvt_level1.tct";
			bool tctfileexists = File.Exists(tctfile);
			if (tctfileexists)
			{
				TCTFILELIST.Add(tctfile);

				JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(tctfile, "TCT");
				double[] SPS_TIME_MJD = bt.GetTTYPEEntry("SPS_TIME_MJD");
				double[] LOCAL_TIMEF = bt.GetTTYPEEntry("LOCAL_TIMEF");

				double mjdref = SPS_TIME_MJD[0];
				double detref = LOCAL_TIMEF[0];
				JD_abs_time_delta_sec = 2455197.5 * 86400 + mjdref - detref;
			}
			else
			{
				if (MessageBox.Show("Can't find TCT file: proceed without correct BJD reference?", "Warning...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					return;
			}

			//LBT get the lbt file to do filter correction
			string lbtfile = argfiles[0].Substring(0, argfiles[0].LastIndexOf("uvt")) + "uvt_level1.lbt";
			bool lbtfileexists = File.Exists(lbtfile);
			double[] lbt_times = null;
			double[] lbt_FUVfwangle = null;
			double[] lbt_NUVfwangle = null;
			double[] lbt_VISfwangle = null;
			double lasttime_mjd_forfilter = Double.MinValue;
			double firsttime_mjd_forfilter = Double.MaxValue;
			bool dofiltercorrection = L1FilterCorrectionChck.Checked;
			if (lbtfileexists)
			{
				LBTFILELIST.Add(lbtfile);								

				if (dofiltercorrection)
				{
					JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(lbtfile, "UVIT-LBTHK");
					lbt_times = bt.GetTTYPEEntry("Time");
					lbt_FUVfwangle = bt.GetTTYPEEntry("FilterWheelMotorAngle_FUV");
					lbt_NUVfwangle = bt.GetTTYPEEntry("FilterWheelMotorAngle_NUV");
					lbt_VISfwangle = bt.GetTTYPEEntry("FilterWheelMotorAngle_VIS");
				}
			}
			else
			{
				if (dofiltercorrection && !lbtfileexists)
				{
					MessageBox.Show("Filter correction requested but lbt file not found.  Exiting.", "Error");
					WAITBAR.CancelBtn.PerformClick();
					return;
				}
			}

			ArrayList pcfiles = new ArrayList();
			ArrayList imfiles = new ArrayList();
			FITSImage src = null;
			for (int i = 0; i < argfiles.Length; i++)
			{
				src = new FITSImage(argfiles[i], null, true, false, false, false);
				string mode = src.Header.GetKeyValue("OBS_MODE");
				if (mode == "PC")
					pcfiles.Add(argfiles[i]);
				else if (mode == "IM")
					imfiles.Add(argfiles[i]);
				else
				{
					MessageBox.Show("Can't determine observation mode: '" + mode + "' on file: " + src.FileName, "Error...");
					return;
				}
			}

			if (!L1DigestDeleteFileChck.Checked)
				if (!Directory.Exists(src.FilePath + "Digested L1\\"))
					Directory.CreateDirectory(src.FilePath + "Digested L1\\");

			ParallelOptions opts = new ParallelOptions();
			if (do_parallel_L1)
				opts.MaxDegreeOfParallelism = (int)((double)Environment.ProcessorCount / Math.PI);
			else
				opts.MaxDegreeOfParallelism = 1;

			//int errorfileindex = 0;
			int wbcounter = 0;
			//try
			{
				Parallel.For(0, pcfiles.Count, opts, (xi, loopstate) =>
				//for (int xi = 0; xi < pcfiles.Count; xi++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						loopstate.Stop();// break;// continue;

					//errorfileindex = xi;
					string FileName = (string)pcfiles[xi];
					string dir = FileName.Substring(0, FileName.LastIndexOf("\\"));
					string path = dir;
					FITSImage source = new FITSImage(FileName, null, true, false, false, false);
					//source.Header.RemoveKeys(new array<String^>(22) { });
					source.Header.AddCommentKeyLine("SRCFILE " + source.FileName, 12);
					string detector = source.Header.GetKeyValue("DETECTOR");
					string filter = source.Header.GetKeyValue("FILTER");
					string filterID = UVITFilter(detector, filter);
					source.Header.SetKey("FILTERID", filterID, "Filter type", true, source.Header.GetKeyIndex("FILTER", false) + 1);
					string orbnum = source.Header.GetKeyValue("ORB_NUM");
					string sourceID;
					if (!L1SpecifySourceNameChck.Checked)
					{
						sourceID = (source.Header.GetKeyValue("SOURCEID").Replace(" ", "")).Replace("/", "");
						if (sourceID.Length > 17)
							sourceID = sourceID.Substring(0, 17);
					}
					else
						sourceID = L1SourceNameTxt.Text;

					//try
					{
						FITSBinTable detdata = new JPFITS.FITSBinTable(source.FullFileName, "DETECTOR_DATA");
						int width = 0;
						for (int h = 0; h < detdata.Header.Length; h++)
							if (detdata.Header[h].Substring(0, 7) == "TFORM15")
							{
								string tform15 = detdata.Header[h].Substring(11, 6);
								tform15 = tform15.Replace("B", "");//PC mode
								tform15 = tform15.Replace("I", "");//IM mode
								width = Convert.ToInt32(tform15);
								break;
							}

						if (DO_TBC)
						{
							lock (argfiles)
							{
								TBC(detdata.BINTABLEByteArray, detdata.Naxis1, detdata.Naxis2);
							}
						}

						bool xword_parity_error = false;
						bool yword_parity_error = false;
						bool sword_parity_error = false;

						uint discardtimeint = 0;
						if (discardtimebool)
						{
							string discardtimestring = (string)L1DiscardDataTimeDrop.SelectedItem;
							discardtimestring = discardtimestring.Replace(" Minutes", "");
							discardtimeint = Convert.ToUInt32(discardtimestring) * 60 * 1000;
						}

						string alg = source.Header.GetKeyValue("CENTROID");
						if (alg != "5S" && alg != "3S")//happened once with some L1 file
							alg = "3S"; //3S is always running in orbit now...so just assume
						string FPNFile = "";
						FITSImage FPNFits = null;
						Random rand = null;
						int N_p_errors = 0;

						if (ApplyFPN)
						{
							rand = new Random();
							if (detector == "FUV")
							{
								if (alg == "3S")
								{
									if (File.Exists("C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits"))
										FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits";
								}
								if (alg == "5S")
								{
									if (File.Exists("C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits"))
										FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits";
								}
							}
							else if (detector == "NUV")
							{
								if (alg == "3S")
								{
									if (File.Exists("C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits"))
										FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits";
								}
								if (alg == "5S")
								{
									if (File.Exists("C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits"))
										FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits";
								}
							}
							else if (detector == "VIS")
							{
								if (alg == "3S")
								{
									if (File.Exists("C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits"))
										FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits";
								}
								if (alg == "5S")
								{
									if (File.Exists("C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits"))
										FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits";
								}
							}
							else
							{
								MessageBox.Show("Cannot find FPN File for channel '" + detector + "' and algorithm '" + alg + "' for file: " + FileName);
								loopstate.Stop();//continue;
							}
							lock (FPNFile)
							{
								FPNFits = new JPFITS.FITSImage(FPNFile, null, false, true, false, false);
							}
						}

						string CPUXDistFile = "";
						string CPUYDistFile = "";
						JPFITS.FITSImage CPUXDistFits = null;
						JPFITS.FITSImage CPUYDistFits = null;
						if (ApplyDIST)
						{
							if (detector == "FUV")
							{
								if (File.Exists("C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits"))
								{
									CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits";
									CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dY.fits";
								}
							}
							else if (detector == "NUV")
							{
								if (File.Exists("C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits"))
								{
									CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits";
									CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dY.fits";
								}
							}
							else if (detector == "VIS")
							{
								if (File.Exists("C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits"))
								{
									CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits";
									CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dY.fits";
								}
							}
							else
							{
								MessageBox.Show("Cannot find Distortion File for channel '" + detector + "' for file: " + FileName);
								loopstate.Stop();//continue;
							}
							lock (CPUXDistFile)
							{
								CPUXDistFits = new JPFITS.FITSImage(CPUXDistFile, null, false, true, false, false);								
							}
							lock (CPUYDistFile)
							{
								CPUYDistFits = new JPFITS.FITSImage(CPUYDistFile, null, false, true, false, false);
							}
						}

						int byteindx = 0;
						double bzero = 0;
						//double bscale = 1;

						//first thing, get number of sets
						int Nset = 0;
						ushort prevframe = UInt16.MaxValue;
						uint prevtime = UInt32.MaxValue;
						for (int i = 0; i < detdata.Naxis2; i++)
						{
							//frame count - TTYPE11 = 'SecHdrImageFrameCount'
							byteindx = i * detdata.Naxis1;
							byteindx += 65;
							bzero = 32768;
							ushort currframe = (ushort)((int)(((detdata.BINTABLEByteArray[byteindx]) << 8) | detdata.BINTABLEByteArray[byteindx + 1]) + (ushort)bzero);//MUST DO IT THIS WAY

							//frame time - TTYPE12 = 'SecHdrImageFrameTime'
							byteindx = i * detdata.Naxis1;
							byteindx += 67;
							bzero = 2147483648;
							uint currtime = (uint)((int)(((detdata.BINTABLEByteArray[byteindx]) << 24) | (detdata.BINTABLEByteArray[byteindx + 1] << 16) | (detdata.BINTABLEByteArray[byteindx + 2]) << 8 | detdata.BINTABLEByteArray[byteindx + 3]) + (uint)bzero);//MUST DO IT THIS WAY

							//if: then imaging session set has reset, or first set, or frame or time rolled over & start new set on rollover,
							//or erroneous (nonsequential) frame number greater than a CRC frame skip which are only skips of 1 frame (but using 2 here for the extremely rare adjacent-frame CRC skips)
							//- in this case the erroneous frame (which will to extremely high probability always be larger difference than 2) will get singled out as its own list for that single frame
							//and then not get written since it will be so small (single frame)
							if (prevframe > currframe || prevtime > currtime || (Math.Abs((double)(currframe) - (double)(prevframe)) > 2))
								Nset++;

							prevframe = currframe;
							prevtime = currtime;
						}

						//have number of sets, now need number of centroids in each set
						int[] Ncentroids = new int[Nset];
						int[] Nskipped = new int[Nset];//skipped frame numbers...not even with 0's
						int Ncent = 0;
						Nset = 0;
						prevframe = UInt16.MaxValue;
						prevtime = UInt32.MaxValue;
						for (int i = 0; i < detdata.Naxis2; i++)
						{
							//frame count - TTYPE11 = 'SecHdrImageFrameCount'
							byteindx = i * detdata.Naxis1;
							byteindx += 65;
							bzero = 32768;
							ushort currframe = (ushort)((int)(((detdata.BINTABLEByteArray[byteindx]) << 8) | detdata.BINTABLEByteArray[byteindx + 1]) + (ushort)bzero);//MUST DO IT THIS WAY

							//frame time - TTYPE12 = 'SecHdrImageFrameTime'
							byteindx = i * detdata.Naxis1;
							byteindx += 67;
							bzero = 2147483648;
							uint currtime = (uint)((int)(((detdata.BINTABLEByteArray[byteindx]) << 24) | (detdata.BINTABLEByteArray[byteindx + 1] << 16) | (detdata.BINTABLEByteArray[byteindx + 2]) << 8 | detdata.BINTABLEByteArray[byteindx + 3]) + (uint)bzero);//MUST DO IT THIS WAY

							//if: then imaging session set has reset, or first set, or frame or time rolled over & start new set on rollover,
							//or erroneous (nonsequential) frame number greater than a CRC frame skip which are only skips of 1 frame (but using 2 here for the extremely rare adjacent-frame CRC skips)
							//- in this case the erroneous frame (which will to extremely high probability always be larger difference than 2) will get singled out as its own list for that single frame
							//and then not get written since it will be so small (single frame)
							if (prevframe > currframe || prevtime > currtime || (Math.Abs((double)(currframe) - (double)(prevframe)) > 2))
								Nset++;

							if (Math.Abs((double)(currframe) - (double)(prevframe)) > 2)
							{
								prevframe = currframe;
								prevtime = currtime;
							}

							if (currframe - prevframe > 1)
								Nskipped[Nset - 1] += currframe - prevframe - 1;

							prevframe = currframe;
							prevtime = currtime;

							//Centroid - TTYPE15 = 'Centroid'
							byteindx = i * detdata.Naxis1;
							byteindx += 79;
							int j = 0;
							//bool checkwidth = false;
							//scanwidth:;
							//try
							{
								for (j = 0; j < width / 6; j++)
								{
									ushort xword = (ushort)((detdata.BINTABLEByteArray[byteindx + j * 6] << 8) | detdata.BINTABLEByteArray[byteindx + j * 6 + 1]);
									ushort yword = (ushort)((detdata.BINTABLEByteArray[byteindx + j * 6 + 2] << 8) | detdata.BINTABLEByteArray[byteindx + j * 6 + 3]);
									ushort sword = (ushort)((detdata.BINTABLEByteArray[byteindx + j * 6 + 4] << 8) | detdata.BINTABLEByteArray[byteindx + j * 6 + 5]);

									if (xword == 0 && yword == 0 && sword == 0)//end of data for this i'th row
										/*continue;*/
										break;

									Ncent++;//number of centroids, only incremented if there was more data for this row
									Ncentroids[Nset - 1]++;
								}
							}
							/*catch
							{
								//checkwidth = true;
								width -= 6;
								goto scanwidth;
							}*/
							/*if (checkwidth)
							{
								//Ncent--;
								//Ncentroids[Nset - 1]--;
							}*/
						}

						double[] BJDS = null;
						ushort[] frames = null;
						uint[] times = null;
						short[,] ints = null;
						short[,] decs = null;
						ushort[,] mdMm = null;

						Ncent = 0;
						Nset = 0;
						prevframe = UInt16.MaxValue;
						prevtime = UInt32.MaxValue;
						for (int i = 0; i <= detdata.Naxis2; i++)
						{
							double JD = 0;
							ushort currframe = 0;
							uint currtime = 0;

							if (i == detdata.Naxis2)
							{
								prevframe = UInt16.MaxValue;//will force the last set to be written
								prevtime = UInt32.MaxValue;
								goto lastset;
							}

							//frame count - TTYPE11 = 'SecHdrImageFrameCount'
							byteindx = i * detdata.Naxis1;
							byteindx += 65;
							bzero = 32768;
							currframe = (ushort)((int)(((detdata.BINTABLEByteArray[byteindx]) << 8) | detdata.BINTABLEByteArray[byteindx + 1]) + (ushort)bzero);//MUST DO IT THIS WAY

							//frame time - TTYPE12 = 'SecHdrImageFrameTime'
							byteindx = i * detdata.Naxis1;
							byteindx += 67;
							bzero = 2147483648;
							currtime = (uint)((int)(((detdata.BINTABLEByteArray[byteindx]) << 24) | (detdata.BINTABLEByteArray[byteindx + 1] << 16) | (detdata.BINTABLEByteArray[byteindx + 2]) << 8 | detdata.BINTABLEByteArray[byteindx + 3]) + (uint)bzero);//MUST DO IT THIS WAY

							//TIME //supposedly mission elapsed time, or something, but perhaps can use with lbt file for aligning filter
							byteindx = i * detdata.Naxis1;
							byteindx += 0;
							bzero = 0;
							byte[] dbl = new byte[8];
							dbl[7] = detdata.BINTABLEByteArray[byteindx];
							dbl[6] = detdata.BINTABLEByteArray[byteindx + 1];
							dbl[5] = detdata.BINTABLEByteArray[byteindx + 2];
							dbl[4] = detdata.BINTABLEByteArray[byteindx + 3];
							dbl[3] = detdata.BINTABLEByteArray[byteindx + 4];
							dbl[2] = detdata.BINTABLEByteArray[byteindx + 5];
							dbl[1] = detdata.BINTABLEByteArray[byteindx + 6];
							dbl[0] = detdata.BINTABLEByteArray[byteindx + 7];
							double temptime = BitConverter.ToDouble(dbl, 0);
							if (temptime > lasttime_mjd_forfilter)
								lasttime_mjd_forfilter = temptime;
							if (temptime < firsttime_mjd_forfilter)
								firsttime_mjd_forfilter = temptime;
							//double JD = BitConverter.ToDouble(dbl, 0);
							//the above time isn't exact.  Now use the JD_abs_time_delta_sec to get the BJD here

							if (tctfileexists)
								JD = ((double)(currtime) / 1000 + JD_abs_time_delta_sec) / 86400;//this should be the local JD...it will get used below to get BJD
							else
								JD = 0;

							lastset:

							//if: then imaging session set has reset, or first set, or frame or time rolled over & start new set on rollover,
							//or erroneous (nonsequential) frame number greater than a CRC frame skip which are only skips of 1 frame (but using 2 here for the extremely rare adjacent-frame CRC skips)
							//- in this case the erroneous frame (which will to extremely high probability always be larger difference than 2) will get singled out as its own list for that single frame
							//and then not get written since it will be so small (single frame)
							if (prevframe > currframe || prevtime > currtime || (Math.Abs((double)(currframe) - (double)(prevframe)) > 2))
							{
								if (Nset > 0 || i == detdata.Naxis2)//then the previous set data needs to be written
								{
									if (times != null)
										if (times.Length > /*0*/1000)//so that short corrupt files dont get written
											if (discardtimebool && (times[times.Length - 1] - times[0]) > discardtimeint || !discardtimebool)
											{
												//do filter correction........do this first for the next below
												if (dofiltercorrection)
												{
													double midtime = (lasttime_mjd_forfilter + firsttime_mjd_forfilter) / 2;
													int lbtcounter = 0;
													while (/*midtime*/ firsttime_mjd_forfilter > lbt_times[lbtcounter])//midtime still wouldn't align when the time-filter alignment was off...first time seems to work better than the last time
														lbtcounter++;
													double fwangle = 0;
													if (detector == "FUV")
														fwangle = lbt_FUVfwangle[lbtcounter];
													if (detector == "NUV")
														fwangle = lbt_NUVfwangle[lbtcounter];
													string filterindex = UVITFilter_FWAngle_to_Index(source.Header.GetKeyValue("DETECTOR"), fwangle);

													string filt = source.Header.GetKeyValue("FILTER");
													if (filterindex != filt)
													{
														filt = filterindex;
														source.Header.SetKey("FILTER", filterindex, "Filter index (CORRECTED)", false, -1);
													}
													filterID = UVITFilter(detector, filterindex);
													source.Header.SetKey("FILTERID", filterID, "Filter type", true, source.Header.GetKeyIndex("FILTER", false) + 1);
													lasttime_mjd_forfilter = Double.MinValue;
													firsttime_mjd_forfilter = Double.MaxValue;
												}

												dir = path + "\\" + detector + "\\" + detector + "_" + filterID + "\\" + sourceID + "_" + detector + "_" + filterID + "_" + orbnum + "_" + (times[0]).ToString("0000000000000");
												lock (argfiles)
												{
													Directory.CreateDirectory(dir);
												}
												string obj_orb_chan;
												obj_orb_chan = dir + "\\" + sourceID + "_" + detector + "_" + filterID + "_" + orbnum + "_" + (times[0]).ToString("0000000000000");
												lock (argfiles)
												{
													dir_list.Add(dir);
													e.Result = dir_list;
												}

												string BJDfile = obj_orb_chan + "_BJDList.fits";
												if (tctfileexists)//else all 0's
													BJDS = JPMath.BJDC(BJDS, Convert.ToDouble(source.Header.GetKeyValue("RA_PNT")), Convert.ToDouble(source.Header.GetKeyValue("DEC_PNT")), false);

												if (detector == "NUV" && L1TransformNUVtoFUVChck.Checked)
													source.Header.SetKey("NUVTOFUV", "true", true, -1);
												source.Header.SetKey("BJD0", BJDS[0].ToString("#.0000000"), "BJD of start of imaging", true, 13);//now it will get added to all other copyheaders's
												source.Header.SetKey("NPARTERR", N_p_errors.ToString(), "Number of Parity errors", true, 14);
												source.Header.SetKey("NCENTROD", times.Length.ToString(), "Number of Centroids", true, 14);
												source.Header.SetKey("PARTREDC", Math.Round((double)(N_p_errors) / (double)(times.Length), 5).ToString(), "Fractional int-time reduxn due to parity err", true, 14);
												source.Header.SetKey("NMISSFRM", Nskipped[Nset - 1].ToString(), "Number of MISSING frames", true, 14);
												source.Header.RemoveKey("NFRAMES");
												source.Header.SetKey("NFRAMES", (frames[frames.Length - 1] - frames[0] + 1).ToString(), "Number of frames, including missing ones", true, 14);
												source.Header.SetKey("FRAMREDC", Math.Round((double)(Nskipped[Nset - 1]) / (double)(frames[frames.Length - 1] - frames[0] + 1), 5).ToString(), "Fractional int-time reduxn due to lost frames", true, 14);
												N_p_errors = 0;//reset for new set
												JPFITS.FITSImage f = new FITSImage(BJDfile, BJDS, false, false);
												f.Header.CopyHeaderFrom(source.Header);
												f.WriteImage(TypeCode.Double, false);

												string framefile = obj_orb_chan + "_FrameList.fits";
												f = new FITSImage(framefile, frames, false, false);
												f.Header.CopyHeaderFrom(source.Header);
												f.WriteImage(TypeCode.UInt16, false);

												string timefile = obj_orb_chan + "_TimeList.fits";
												f = new FITSImage(timefile, times, false, false);
												f.Header.CopyHeaderFrom(source.Header);
												f.WriteImage(TypeCode.UInt32, false);

												string flatid = "";
												FITSImage flat = null;
												string channel = f.Header.GetKeyValue("CHANNEL");
												if (channel.Length == 0)
													channel = detector;
												if (channel == "FUV")
												{
													//flatid = "C:\\UVIT_CalDB\\Flats Normalized\\FUV Normalized Flat.fits";

													flatid = "C:\\UVIT_CalDB\\Flats Normalized\\FUVALL_flat_final_sens.fits";
												}
												if (channel == "NUV")
												{
													//flatid = "C:\\UVIT_CalDB\\Flats Normalized\\NUV Normalized Flat.fits";

													string filterid = source.Header.GetKeyValue("FILTERID");
													if (filterid.Contains("Silica"))
														flatid = "N242W_flat_final_sens.fits";
													else if (filterid == "NUVB15")
														flatid = "N219M_flat_final_sens.fits";
													else if (filterid == "NUVB13")
														flatid = "N245M_flat_final_sens.fits";
													else if (filterid == "NUVB4")
														flatid = "N263M_flat_final_sens.fits";
													else if (filterid == "NUVN2")
														flatid = "N279N_flat_final_sens.fits";
													else
														flatid = "NUV Normalized Flat.fits";
													flatid = "C:\\UVIT_CalDB\\Flats Normalized\\" + flatid;
												}
												if (channel == "VIS")
													flatid = "C:\\UVIT_CalDB\\Flats Normalized\\VIS Normalized Flat.fits";
												if (!File.Exists(flatid))
												{
													MessageBox.Show("Couldn't find the flat file: '" + flatid + "' in the CalDB...stopping.", "Error");
													WAITBAR.CancelBtn.PerformClick();
													continue;
												}
												lock (argfiles)
												{
													flat = new FITSImage(flatid, null, false, true, false, false);
												}

												double[] flats = new double[Ncentroids[Nset - 1]];
												int j = 0;
												//try
												{
													for (j = 0; j < Ncentroids[Nset - 1]; j++)
													{
														int xpos = (int)(ints[0, j] / 32);
														int ypos = (int)(ints[1, j] / 32);
														if (xpos < 0 || xpos > 511 || ypos < 0 || ypos > 511)
															flats[j] = 1;
														else
															flats[j] = flat[xpos, ypos];
													}

													//do NUV to FUV here, after the flat is created...simple!
													if (channel == "NUV" && L1TransformNUVtoFUVChck.Checked)
													{
														Random r = new Random();
														double x, y, xp, yp, center = 255 * 32;
														int intsx, fracx, intsy, fracy;
														double[] Pnuvtofuv = new double[] { 0.84898, 0.53007, 0.53007, -0.84898 };//from Shyam Feb 2017
														for (j = 0; j < Ncentroids[Nset - 1]; j++)
														{
															x = (double)(ints[0, j] + decs[0, j] + 16) + r.NextDouble();
															y = (double)(ints[1, j] + decs[1, j] + 16) + r.NextDouble();

															xp = (x - center) * Pnuvtofuv[0] + (y - center) * Pnuvtofuv[1] + center;
															yp = (x - center) * Pnuvtofuv[2] + (y - center) * Pnuvtofuv[3] + center;

															//now need to split out integer and decimal parts back into their own lists...
															intsx = Math.DivRem((int)((xp)), 32, out fracx) * 32;
															fracx -= 16;//reset frac to be from -16
															intsy = Math.DivRem((int)((yp)), 32, out fracy) * 32;
															fracy -= 16;//reset frac to be from -16
															ints[0, j] = (short)intsx;
															ints[1, j] = (short)intsy;
															decs[0, j] = (short)fracx;
															decs[1, j] = (short)fracy;
														}
													}
												}
												/*catch
												{
													MessageBox.Show("xint: " + ((int)(ints[0, j] / 32)).ToString() + ";	yint: " + ((int)(ints[1, j] / 32)).ToString() + ";	j: " + j.ToString() + ";	lengthj: " + flats.Length.ToString());
												}*/
												string flatfile = obj_orb_chan + "_FlatList.fits";
												FITSImage fitsflatlist = new FITSImage(flatfile, flats, false, false);
												fitsflatlist.Header.CopyHeaderFrom(source.Header);
												fitsflatlist.WriteImage(TypeCode.Double, false);

												string intsfile = obj_orb_chan + "_XYInts_List.fits";
												if (ApplyFPN)
													intsfile = intsfile.Insert(intsfile.LastIndexOf("."), "_deFPN");
												if (ApplyDIST)
													intsfile = intsfile.Insert(intsfile.LastIndexOf("."), "_deDIST");
												f = new FITSImage(intsfile, ints, false, false);
												f.Header.CopyHeaderFrom(source.Header);
												f.WriteImage(TypeCode.Int16, false);

												string fracfile = obj_orb_chan + "_XYFrac_List.fits";
												if (ApplyFPN)
													fracfile = fracfile.Insert(fracfile.LastIndexOf("."), "_deFPN");
												if (ApplyDIST)
													fracfile = fracfile.Insert(fracfile.LastIndexOf("."), "_deDIST");
												f = new FITSImage(fracfile, decs, false, false);
												f.Header.CopyHeaderFrom(source.Header);
												f.WriteImage(TypeCode.Int16, false);

												string mdMmfile = obj_orb_chan + "_XYmdMm_List.fits";
												f = new FITSImage(mdMmfile, mdMm, false, false);
												f.Header.CopyHeaderFrom(source.Header);
												f.WriteImage(TypeCode.Int16, false);
											}
								}

								if (i == detdata.Naxis2)
									goto lastset2;//last set was written so now go end

								//reset everything for new centroids list
								Nset++;
								Ncent = 0;
								BJDS = new double[Ncentroids[Nset - 1]];
								frames = new ushort[Ncentroids[Nset - 1]];
								times = new uint[Ncentroids[Nset - 1]];
								ints = new short[2, Ncentroids[Nset - 1]];
								decs = new short[2, Ncentroids[Nset - 1]];
								mdMm = new ushort[2, Ncentroids[Nset - 1]];
							}
							prevframe = currframe;
							prevtime = currtime;

							//Centroid - TTYPE15 = 'Centroid'
							byteindx = i * detdata.Naxis1;
							byteindx += 79;
							for (int j = 0; j < width / 6; j++)
							{
								ushort xword = (ushort)((detdata.BINTABLEByteArray[byteindx + j * 6] << 8) | detdata.BINTABLEByteArray[byteindx + j * 6 + 1]);
								ushort yword = (ushort)((detdata.BINTABLEByteArray[byteindx + j * 6 + 2] << 8) | detdata.BINTABLEByteArray[byteindx + j * 6 + 3]);
								ushort sword = (ushort)((detdata.BINTABLEByteArray[byteindx + j * 6 + 4] << 8) | detdata.BINTABLEByteArray[byteindx + j * 6 + 5]);

								if (xword == 0 && yword == 0 && sword == 0)//end of data for this i'th row
									/*continue;*/
									break;

								if (discardparityerror)
								{
									xword_parity_error = GSEExtractImg.Check_Even_Parity_Flag(xword);
									yword_parity_error = GSEExtractImg.Check_Even_Parity_Flag(yword);
									sword_parity_error = GSEExtractImg.Check_Even_Parity_Flag(sword);
								}

								bool p_error = false;
								if (xword_parity_error || yword_parity_error/* || sword_parity_error*/)//lets not worry about a parity error only on the sword because this doesn't affect the centroid photometry position itself, and it can still be used.  If it is a parity error on the x or y, then it does need to be accounted for.
								{
									p_error = true;
									N_p_errors++;
								}

								ushort ixpos = 0, iypos = 0, mc = 0, dMm = 0;
								short fxpos = 0, fypos = 0;

								if (!p_error)
								{
									//x
									ixpos = (ushort)(((xword) >> 7) * 32);
									fxpos = (short)((xword & 0x7F) >> 1);
									if (fxpos >= 32)
										fxpos = (short)(fxpos - 64);

									//y
									iypos = (ushort)(((yword) >> 7) * 32);
									fypos = (short)((yword & 0x7F) >> 1);
									if (fypos >= 32)
										fypos = (short)(fypos - 64);

									//corner
									mc = (ushort)(((sword & 0x1FF) >> 1) * 16);
									dMm = (ushort)((sword >> 9) * 16);

									if (ApplyFPN)
									{
										if (fxpos < -16)//X
										{
											ixpos -= 32;//adjust integer
											fxpos += 32;//adjust fractional
										}
										if (fypos < -16)//Y
										{
											iypos -= 32;//adjust integer
											fypos += 32;//adjust fractional
										}
										if (fxpos > 15)//X
										{
											ixpos += 32;//adjust integer
											fxpos -= 32;//adjust fractional
										}
										if (fypos > 15)//Y
										{
											iypos += 32;//adjust integer
											fypos -= 32;//adjust fractional
										}

										fxpos += 16;
										fypos += 16;

										double fx = (double)(fxpos);
										double fy = (double)(fypos);

										fx += rand.NextDouble();
										fy += rand.NextDouble();

										fx *= FPNFits[1, (int)(fx * 4096 / 32)];
										fy *= FPNFits[2, (int)(fy * 4096 / 32)];

										fxpos = (short)fx;
										fypos = (short)fy;

										fxpos -= 16;//x
										fypos -= 16;//y
									}

									int xcorr, ycorr;
									if (ApplyDIST)
									{
										if (ixpos > 0 && iypos > 0 && ixpos / 32 <= 511 && iypos / 32 <= 511)
										{
											if (interpDISTBiLin)
											{
												double x = ((double)(ixpos) + (double)(fxpos) + 16) / 32;
												double y = ((double)(iypos) + (double)(fypos) + 16) / 32;
												xcorr = (int)(32 * JPMath.InterpolateBiLinear(CPUXDistFits.Image, 512, 512, x, y));
												ycorr = (int)(32 * JPMath.InterpolateBiLinear(CPUYDistFits.Image, 512, 512, x, y));
											}
											else
											{
												xcorr = (int)(32 * CPUXDistFits[ixpos / 32, iypos / 32]);
												ycorr = (int)(32 * CPUYDistFits[ixpos / 32, iypos / 32]);
											}

											ixpos -= (ushort)xcorr;
											iypos -= (ushort)ycorr;
										}
										else
											p_error = true;//treat this as p_error...it is an odd scenario but now seen to happen with Ashok Pati's data.							
									}
								}

								BJDS[Ncent] = JD;
								frames[Ncent] = currframe;
								times[Ncent] = currtime;

								if (p_error)
								{
									//MessageBox.Show("p_error");
									ints[0, Ncent] = 0;//these will be seen in a final image as drifting around at the top left corner
									ints[1, Ncent] = 0;
									decs[0, Ncent] = 0;
									decs[1, Ncent] = 0;
									mdMm[0, Ncent] = 0;
									mdMm[1, Ncent] = 0;
								}
								else
								{
									ints[0, Ncent] = (short)ixpos;
									ints[1, Ncent] = (short)iypos;
									decs[0, Ncent] = (short)fxpos;
									decs[1, Ncent] = (short)fypos;
									mdMm[0, Ncent] = mc;
									mdMm[1, Ncent] = dMm;
								}
								Ncent++;//number of centroids, only incremented if there was more data for this row
							}
						}
					lastset2:;
					}
					/*catch (Exception e)
					{
						MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite + "\n\r + \n\r" + "File: " + argfiles[errorfileindex]);
					}*/

					lock(argfiles)
					{
						wbcounter++;
						DigestL1Wrkr.ReportProgress(wbcounter/*xi + 1*/, /*mode*/"PC" + "_" + argfiles.Length);
					}

					if (WAITBAR.DialogResult == DialogResult.Cancel)
						loopstate.Stop();//break;// continue;

					if (!L1DigestDeleteFileChck.Checked)
						File.Move(source.FullFileName, source.FilePath + "Digested L1\\" + source.FileName);
					else
						File.Delete(source.FullFileName);
				});//end PC mode





				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;





				bool degrade = L1DegradientINTMode.Checked;
				double cleanthreshold = Convert.ToDouble(L1CleanINTLineThreshold.Text);
				int cleanN = Convert.ToInt32(L1CleanINTNPix.Text);
				for (int xi = 0; xi < imfiles.Count; xi++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						break;

					//errorfileindex = xi;
					string FileName = (string)imfiles[xi];
					string dir = FileName.Substring(0, FileName.LastIndexOf("\\"));
					string path = dir;
					FITSImage source = new FITSImage(FileName, null, true, false, false, false);
					source.Header.AddCommentKeyLine("SRCFILE " + source.FileName, 12);
					string detector = source.Header.GetKeyValue("DETECTOR");
					string filter = source.Header.GetKeyValue("FILTER");
					string filterindex = UVITFilter(detector, filter);
					source.Header.SetKey("FILTERID", filterindex, "Filter type", true, source.Header.GetKeyIndex("FILTER", false) + 1);
					string orbnum = source.Header.GetKeyValue("ORB_NUM");
					string sourceID;
					if (!L1SpecifySourceNameChck.Checked)
					{
						sourceID = (source.Header.GetKeyValue("SOURCEID").Replace(" ", "")).Replace("/", "");
						if (sourceID.Length > 17)
							sourceID = sourceID.Substring(0, 17);
					}
					else
						sourceID = L1SourceNameTxt.Text;

					FITSBinTable detdata = null;
					int width = 0;
					if (!L1SkipINTMode.Checked)
					{
						detdata = new JPFITS.FITSBinTable(source.FullFileName, "DETECTOR_DATA");
						for (int h = 0; h < detdata.Header.Length; h++)
							if (detdata.Header[h].Substring(0, 7) == "TFORM15")
							{
								string tform15 = detdata.Header[h].Substring(11, 6);
								tform15 = tform15.Replace("B", "");//PC mode
								tform15 = tform15.Replace("I", "");//IM mode
								width = Convert.ToInt32(tform15);
								break;
							}
					}

					if (!L1DigestDeleteFileChck.Checked)
						File.Move(source.FullFileName, source.FilePath + "Digested L1\\" + source.FileName);
					else
						File.Delete(source.FullFileName);

					if (L1SkipINTMode.Checked)
						continue;

					int xsize = Convert.ToInt32(source.Header.GetKeyValue("WIN_X_SZ"));//zero-based
					int ysize = Convert.ToInt32(source.Header.GetKeyValue("WIN_Y_SZ"));//zero-based
					int imsize = (xsize + 1) * (ysize + 1);
					double[,] d2im = new double[xsize + 1, ysize + 1];
					ushort[] d1im = new ushort[imsize];//just 1-D is fine cause we're just gonna write it
					int pixnum = 0;
					int intprog = 0;
					int Nimages = width * detdata.Naxis2 / imsize;
					ushort prevframe = UInt16.MaxValue - 1;
					//int set = 0;				

					lasttime_mjd_forfilter = Double.MinValue;
					firsttime_mjd_forfilter = Double.MaxValue;

					if (DO_TBC)
					{
						lock (argfiles)
						{
							TBC(detdata.BINTABLEByteArray, detdata.Naxis1, detdata.Naxis2);
						}
					}











					//ArrayList framelist = new ArrayList();
					//ArrayList dirlist = new ArrayList();
					//int nfrm = 0;
					//for (int i = 0; i < detdata.Naxis2; i++)
					//{
					//	int byteindx;
					//	double bzero;
					//	double bscale;

					//	//frame count
					//	byteindx = i * detdata.Naxis1;
					//	byteindx += 65;
					//	bzero = 32768;
					//	ushort frame = (int)(((detdata.BINTABLEByteArray[byteindx]) << 8) | detdata.BINTABLEByteArray[byteindx + 1]) + (ushort)bzero;

					//	//frame time
					//	byteindx = i * detdata.Naxis1;
					//	byteindx += 67;
					//	bzero = 2147483648;
					//	bscale = 1;
					//	uint time = (int)(((detdata.BINTABLEByteArray[byteindx]) << 24) | (detdata.BINTABLEByteArray[byteindx + 1] << 16) | (detdata.BINTABLEByteArray[byteindx + 2]) << 8 | detdata.BINTABLEByteArray[byteindx + 3]) + (uint)bzero;

					//	if (prevframe != frame)//then it is a new image; also fires at very beginning.
					//	{					
					//		if (prevframe > frame && prevframe != UInt16.MaxValue || ((int)frame - (int)prevframe) > 5 * 16)//then frame has reset for some reason, so start a new file name set; also fires at very beginning
					//		{
					//			dir = path + "\\" + detector + "\\" + sourceID + "_" + detector + "_" + UVITFilter(detector, filter) + "_" + orbnum + "_" + (time).ToString("0000000000000");
					//			Directory.CreateDirectory(dir);
					//		}
					//		prevframe = frame;
					//		framelist.Add(frame);
					//		dirlist.Add(dir);
					//		nfrm++;
					//	}
					//}
















					//try
					{
						for (int i = 0; i < detdata.Naxis2; i++)
						{
							int byteindx;
							double bzero;
							//double bscale;

							//frame count
							byteindx = i * detdata.Naxis1;
							byteindx += 65;
							bzero = 32768;
							ushort frame = (ushort)((int)(((detdata.BINTABLEByteArray[byteindx]) << 8) | detdata.BINTABLEByteArray[byteindx + 1]) + (ushort)bzero);

							//frame time
							byteindx = i * detdata.Naxis1;
							byteindx += 67;
							bzero = 2147483648;
							//bscale = 1;
							uint time = (uint)((int)(((detdata.BINTABLEByteArray[byteindx]) << 24) | (detdata.BINTABLEByteArray[byteindx + 1] << 16) | (detdata.BINTABLEByteArray[byteindx + 2]) << 8 | detdata.BINTABLEByteArray[byteindx + 3]) + (uint)bzero);

							//TIME //supposedly mission elapsed time, or something, but perhaps can use with lbt file for aligning filter
							byteindx = i * detdata.Naxis1;
							byteindx += 0;
							bzero = 0;
							byte[] dbl = new byte[8];
							dbl[7] = detdata.BINTABLEByteArray[byteindx];
							dbl[6] = detdata.BINTABLEByteArray[byteindx + 1];
							dbl[5] = detdata.BINTABLEByteArray[byteindx + 2];
							dbl[4] = detdata.BINTABLEByteArray[byteindx + 3];
							dbl[3] = detdata.BINTABLEByteArray[byteindx + 4];
							dbl[2] = detdata.BINTABLEByteArray[byteindx + 5];
							dbl[1] = detdata.BINTABLEByteArray[byteindx + 6];
							dbl[0] = detdata.BINTABLEByteArray[byteindx + 7];
							double temptime = BitConverter.ToDouble(dbl, 0);
							if (temptime > lasttime_mjd_forfilter)
								lasttime_mjd_forfilter = temptime;
							if (temptime < firsttime_mjd_forfilter)
								firsttime_mjd_forfilter = temptime;

							if (prevframe != frame)//then it is a new image; also fires at very beginning.
							{
								if (WAITBAR.DialogResult == DialogResult.Cancel)
									break;

								if (prevframe > frame && prevframe != UInt16.MaxValue || ((int)frame - (int)prevframe) > 5 * 16)//then frame has reset for some reason, so start a new file name set; also fires at very beginning
								{
									if (dofiltercorrection)
									{
										double midtime = (lasttime_mjd_forfilter + firsttime_mjd_forfilter) / 2;
										int lbtcounter = 0;
										//MessageBox.Show(firsttime_mjd_forfilter + "    " + lbt_times[0] + "    " + lbt_times[lbt_times.Length - 1]);
										while (/*midtime*/ lbtcounter < lbt_times.Length && firsttime_mjd_forfilter > lbt_times[lbtcounter])//midtime still wouldn't align when the time-filter alignment was off...first time seems to work better than the last time
											lbtcounter++;
										if (lbtcounter == lbt_times.Length)
											lbtcounter /= 2;//?????
										double fwangle = lbt_VISfwangle[lbtcounter];
										string filterind = UVITFilter_FWAngle_to_Index(detector, fwangle);

										if (DO_TBC && filterind == "F0" || DO_TBC && filterind == "NA")
										{
											lbtcounter = 0;
											firsttime_mjd_forfilter -= 524;
											while (lbtcounter < lbt_times.Length && firsttime_mjd_forfilter > lbt_times[lbtcounter])
												lbtcounter++;
											if (lbtcounter == lbt_times.Length)
												lbtcounter /= 2;//?????
											fwangle = lbt_VISfwangle[lbtcounter];
											filterind = UVITFilter_FWAngle_to_Index(detector, fwangle);
										}

										if (filterind != filter)
											source.Header.SetKey("FILTER", filterind, "Filter index (CORRECTED)", false, -1);
										string filtertype = UVITFilter(detector, filterind);
										source.Header.SetKey("FILTERID", filtertype, "Filter type", true, source.Header.GetKeyIndex("FILTER", false) + 1);
										lasttime_mjd_forfilter = Double.MinValue;
										firsttime_mjd_forfilter = Double.MaxValue;
									}

									//set++;//used in file name of image
									dir = path + "\\" + detector + "\\" + sourceID + "_" + detector + "_" + UVITFilter(detector, filter) + "_" + orbnum + "_" + (time).ToString("0000000000000");
									Directory.CreateDirectory(dir);
								}
								pixnum = 0;//force restart
								prevframe = frame;
							}

							try
							{
								//Pixel
								byteindx = i * detdata.Naxis1;
								byteindx += 79;
								bzero = 32768;
								for (int j = 0; j < width; j++)
								{
									if (pixnum >= imsize)//image is done
									{
										if (WAITBAR.DialogResult == DialogResult.Cancel)
											break;

										intprog++;
										DigestL1Wrkr.ReportProgress(100 * intprog / Nimages, "IM" + "_" + (xi + 1 + pcfiles.Count).ToString() + "_" + (pcfiles.Count + imfiles.Count));

										pixnum = 0;//reset pixel index

										for (int jj = 0; jj < ysize + 1; jj++)
											for (int ii = 0; ii < xsize + 1; ii++)
												d2im[ii, jj] = (double)(d1im[jj * (xsize + 1) + ii]);

										string obj_orb_chan;
										obj_orb_chan = dir + "\\" + sourceID + "_" + detector + "_" + UVITFilter(detector, filter) + "_" + orbnum + "_" + (time).ToString("0000000000000") + ".fits";
										if (degrade)
											d2im = JPMath.DeGradient(d2im, 0, true);
										FITSImage fits = new FITSImage(obj_orb_chan, d2im, false, true);
										fits.Header.CopyHeaderFrom(source.Header);
										fits.Header.AddKey("FRMTIME", ((double)(time) / 1000).ToString(), "EU Frame Time (s)", 18);
										fits.Header.AddKey("FRAMENO", frame.ToString(), "Frame Number", 18);
										//fits.Header.AddKey("FRAMESET", set.ToString(), "Frame Set", 18);
										double[] JD = new double[1] { ((double)(time) / 1000 + JD_abs_time_delta_sec) / 86400 };
										JD = JPMath.BJDC(JD, Convert.ToDouble(source.Header.GetKeyValue("RA_PNT")), Convert.ToDouble(source.Header.GetKeyValue("DEC_PNT")), false);
										fits.Header.AddKey("FRAMEBJD", JD[0].ToString(), "Heliocentric Julian Date (days)", 18);
										if (frame > 16)//skip writing first image so that noise images don't come in
										{
											if (L1CleanINTMode.Checked)
												CLEAN_UVITVISIMG(fits, cleanthreshold, cleanN, true);

											if (do_parallel_L1)
												SPAREFITSImageSet.Add(fits);
											else
												fits.WriteImage(TypeCode.Int32, false);

										}
										d2im = new double[xsize + 1, ysize + 1];
										d1im = new ushort[imsize];
										break;
									}

									d1im[pixnum] = (ushort)(((detdata.BINTABLEByteArray[byteindx + j * 2] << 8) | detdata.BINTABLEByteArray[byteindx + j * 2 + 1]) + 32768);
									pixnum++;
								}
							}
							catch { /*MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);*/ }
						}
					}
					/*catch (Exception e)
					{
						MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
					}*/

					WAITBAR.Tag = path + "\\" + "VIS";//need to sneak in the VIS directory for when no PC files were digested

					if (do_parallel_L1 && SPAREFITSImageSet.Count > 0 && WAITBAR.DialogResult != DialogResult.Cancel)
					{
						SPAREFITSImageSet.Write(TypeCode.Int32, true, true, "Saving Orbit VIS Images to Disk");
						SPAREFITSImageSet.Clear();
						SPAREFITSImageSet = new FITSImageSet();
					}
				}//end IM mode
			}
			/*catch (Exception e)
			{
				MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite + "\n\r" + "File: " + argfiles[errorfileindex]);
			}*/
		}

		private void DigestL1Wrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			string mode = (string)e.UserState;
			if (mode.Substring(0, 2) == "PC")
			{
				int first = mode.IndexOf("_");
				WAITBAR.ProgressBar.Maximum = Convert.ToInt32(mode.Substring(first + 1));
				WAITBAR.Text = "Digesting L1 PC File(s)...";
				WAITBAR.ProgressBar.Value = e.ProgressPercentage;
				WAITBAR.TextMsg.Text = String.Concat("Digesting file: ", e.ProgressPercentage, " of ", WAITBAR.ProgressBar.Maximum);
			}
			if (mode.Substring(0, 2) == "IM")
			{
				int first = mode.IndexOf("_");
				int last = mode.LastIndexOf("_");
				WAITBAR.Text = "Digesting L1 Files: " + mode.Substring(first + 1, last - first - 1) + " of " + mode.Substring(last + 1);
				WAITBAR.ProgressBar.Maximum = 100;
				WAITBAR.ProgressBar.Value = e.ProgressPercentage;
				WAITBAR.TextMsg.Text = String.Concat("Extracting INT-mode frames: ", e.ProgressPercentage, "%");
			}
			WAITBAR.Refresh();
		}

		private void DigestL1Wrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				this.Enabled = true;
				this.BringToFront();
				return;
			}

			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");//may be top-level only of multidirs
			REG.SetReg("CCDLAB", "OpenFilesPath", dir);
			bool multidir = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1ExtractMultiDir"));//if true then dir is multi-level
			string[] multidirs;
			if (multidir)
				multidirs = Directory.GetDirectories(dir);
			else
				multidirs = new string[] { dir };//since dir will be the object session directory done by itself

			//move tct and lbt files
			for (int i = 0; i < TCTFILELIST.Count; i++)
			{
				string tctfile = (string)TCTFILELIST[i];
				if (!File.Exists(tctfile))
					continue;
				if (!L1DigestDeleteFileChck.Checked)
				{
					string dir2 = tctfile.Substring(0, tctfile.LastIndexOf("\\"));
					dir2 = dir2 + "\\Digested L1\\";
					File.Move(tctfile, dir2 + tctfile.Substring(tctfile.LastIndexOf("\\")));
				}
				else
					File.Delete(tctfile);
			}
			for (int i = 0; i < LBTFILELIST.Count; i++)
			{
				string lbtfile = (string)LBTFILELIST[i];
				if (!File.Exists(lbtfile))
					continue;
				if (!L1DigestDeleteFileChck.Checked)
				{
					string dir2 = lbtfile.Substring(0, lbtfile.LastIndexOf("\\"));
					dir2 = dir2 + "\\Digested L1\\";
					File.Move(lbtfile, dir2 + lbtfile.Substring(lbtfile.LastIndexOf("\\")));
				}
				else
					File.Delete(lbtfile);
			}

			if (L1DiscardDuplicateChck.Checked)
			{
				WAITBAR.Text = "Searching for duplicated data...";
				if (e.Result != null)//result = null if only IM done.  Here, VIS directories will be checked for duplicates
				{
					ArrayList dir_list = (ArrayList)e.Result;
					WAITBAR.ProgressBar.Maximum = dir_list.Count - 1;
					DiscardL1DuplicateWrkr.RunWorkerAsync(dir_list);
					//WAITBAR.ShowDialog(); already shown
					return;
				}
				else//then only IM done.  Need to scan the VIS images and dirs for duplicates
				{
					DiscardL1DuplicateWrkr.RunWorkerAsync();
					//WAITBAR.ShowDialog(); already shown...and has VIS dir tag
					return;
				}
			}
			else
				if (L1AutoRunChck.Checked)
				DiscardL1DuplicateWrkr_RunWorkerCompleted(sender, e);

			//finish
			TimeSpan ts = DateTime.Now - DATE;
			MessageBox.Show("Completed digesting L1 data in " + ts.Minutes.ToString() + "m" + ts.Seconds.ToString() + "s.", "Finished...");
			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;
			this.BringToFront();
		}

		private void autoRunToolStripMenuItem_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1AutoRunChck", L1AutoRunChck.Checked);
			if (L1AutoRunChck.Checked)
				L1AutoProceedVISBackGround.Enabled = true;
			else
			{
				L1AutoProceedVISBackGround.Enabled = false;
				L1AutoProceedVISTracking.Enabled = false;
				L1AutoProceedVISBackGround.Checked = false;
				L1AutoProceedVISTracking.Checked = false;
				L1AutoApplyVISDrift.Enabled = false;
				L1AutoApplyVISDrift.Checked = false;
			}
			REG.SetReg("CCDLAB", "L1AutoProceedVISBackGround", L1AutoProceedVISBackGround.Checked);
			REG.SetReg("CCDLAB", "L1AutoProceedVISTracking", L1AutoProceedVISTracking.Checked);
			REG.SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift.Checked);

			UVITMenu.ShowDropDown();
			ExtractL1gzsMenuItem.ShowDropDown();
		}

		private void L1AutoProceedVISBackGround_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1AutoProceedVISBackGround", L1AutoProceedVISBackGround.Checked);
			if (L1AutoProceedVISBackGround.Checked)
				L1AutoProceedVISTracking.Enabled = true;
			else
			{
				L1AutoProceedVISTracking.Enabled = false;
				L1AutoProceedVISTracking.Checked = false;
				L1AutoApplyVISDrift.Enabled = false;
				L1AutoApplyVISDrift.Checked = false;
			}
			REG.SetReg("CCDLAB", "L1AutoProceedVISTracking", L1AutoProceedVISTracking.Checked);
			REG.SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift.Checked);

			UVITMenu.ShowDropDown();
			ExtractL1gzsMenuItem.ShowDropDown();
		}

		private void L1AutoProceedVISTracking_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1AutoProceedVISTracking", L1AutoProceedVISTracking.Checked);
			if (L1AutoProceedVISTracking.Checked)
				L1AutoApplyVISDrift.Enabled = true;
			else
			{
				L1AutoApplyVISDrift.Enabled = false;
				L1AutoApplyVISDrift.Checked = false;
			}
			REG.SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift.Checked);

			UVITMenu.ShowDropDown();
			ExtractL1gzsMenuItem.ShowDropDown();
		}

		private void L1AutoApplyVISDrift_Click(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift.Checked);

			UVITMenu.ShowDropDown();
			ExtractL1gzsMenuItem.ShowDropDown();
		}

		private void DiscardL1DuplicateWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			//how to handle multiple top level dirs...
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			bool multidir = Convert.ToBoolean(REG.GetReg("CCDLAB", "L1ExtractMultiDir"));//if true then dir is multi-level
			string[] multidirs;
			if (multidir)
				multidirs = Directory.GetDirectories(dir);
			else
				multidirs = new string[] { dir };//since dir will be the object session directory done by itself

			for (int dirindex = 0; dirindex < multidirs.Length; dirindex++)
			{
				if (e.Argument != null)//will = null if there were no pc files..but if we're in here there must be VIS INT files then
				{
					ArrayList delete_dir_list = new ArrayList();
					FITSImage fitsi;
					double[] fitsistart;
					double[] fitsiend;
					FITSImage fitsj;
					double[] fitsjstart;
					double[] fitsjend;

					string[] timelists = Directory.GetFiles(multidirs[dirindex], "*TimeList*", SearchOption.AllDirectories);

					for (int i = 0; i < timelists.Length - 1; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						DiscardL1DuplicateWrkr.ReportProgress(i + 1, new object[] { delete_dir_list.Count, timelists.Length, multidirs.Length, dirindex + 1 });

						string filei = timelists[i];
						string diri = filei.Substring(0, filei.LastIndexOf("\\"));
						string diritime = diri.Substring(diri.Length - 13);
						fitsi = new FITSImage(filei, null, true, false, false, false);
						string detectori = fitsi.Header.GetKeyValue("DETECTOR");
						string filteri = fitsi.Header.GetKeyValue("FILTER");
						fitsistart = JPFITS.FITSImage.ReadImageVectorOnly(filei, new int[] { 0, 0, 0, 0 }, true);
						fitsiend = JPFITS.FITSImage.ReadImageVectorOnly(filei, new int[] { 0, 0, fitsi.Height - 1, fitsi.Height - 1 }, true);

						for (int j = i + 1; j < timelists.Length; j++)
						{
							string filej = timelists[j];
							string dirj = filej.Substring(0, filej.LastIndexOf("\\"));
							string dirjtime = dirj.Substring(dirj.Length - 13);
							fitsj = new FITSImage(filej, null, true, false, false, false);
							string detectorj = fitsj.Header.GetKeyValue("DETECTOR");
							string filterj = fitsj.Header.GetKeyValue("FILTER");

							if (detectori != detectorj || filteri != filterj)
								continue;

							if (diritime == dirjtime)
							//definitely duplicated data, delete the directory with smaller files...they start at the exact same time so delete the smaller one
							//or if they're the same size, then delete earlier one
							{
								FileStream fs = new FileStream(filei, FileMode.Open);
								long fli = fs.Length;
								fs.Close();
								fs = new FileStream(filej, FileMode.Open);
								long flj = fs.Length;
								fs.Close();

								if (flj < fli)
								{
									if (!delete_dir_list.Contains(dirj))
										delete_dir_list.Add(dirj);//delete the directory with smaller files
								}
								else
								{
									if (!delete_dir_list.Contains(diri))
										delete_dir_list.Add(diri);//delete the earlier directory
								}
								continue;
							}

							//check if times are overlapping - directory times are not the same, but there may be overlapping data within
							fitsjstart = JPFITS.FITSImage.ReadImageVectorOnly(filej, new int[] { 0, 0, 0, 0 }, true);
							fitsjend = JPFITS.FITSImage.ReadImageVectorOnly(filej, new int[] { 0, 0, fitsj.Height - 1, fitsj.Height - 1 }, true);

							if (fitsistart[0] >= fitsjstart[0] && fitsistart[0] <= fitsjend[0])//then i starts within j...delete the directory with smaller files
							{
								FileStream fs = new FileStream(filei, FileMode.Open);
								long fli = fs.Length;
								fs.Close();
								fs = new FileStream(filej, FileMode.Open);
								long flj = fs.Length;
								fs.Close();

								if (flj < fli)
								{
									if (!delete_dir_list.Contains(dirj))
										delete_dir_list.Add(dirj);//delete the directory with smaller files
								}
								else
								{
									if (!delete_dir_list.Contains(diri))
										delete_dir_list.Add(diri);//delete the earlier directory
								}
								continue;
							}

							if (fitsiend[0] >= fitsjstart[0] && fitsiend[0] <= fitsjend[0])//then i ends within j...delete the directory with smaller files
							{
								FileStream fs = new FileStream(filei, FileMode.Open);
								long fli = fs.Length;
								fs.Close();
								fs = new FileStream(filej, FileMode.Open);
								long flj = fs.Length;
								fs.Close();

								if (flj < fli)
								{
									if (!delete_dir_list.Contains(dirj))
										delete_dir_list.Add(dirj);//delete the directory with smaller files
								}
								else
								{
									if (!delete_dir_list.Contains(diri))
										delete_dir_list.Add(diri);//delete the earlier directory
								}
								continue;
							}

							if (fitsjstart[0] >= fitsistart[0] && fitsjstart[0] <= fitsiend[0])//then j starts within i...delete the directory with smaller files
							{
								FileStream fs = new FileStream(filei, FileMode.Open);
								long fli = fs.Length;
								fs.Close();
								fs = new FileStream(filej, FileMode.Open);
								long flj = fs.Length;
								fs.Close();

								if (flj < fli)
								{
									if (!delete_dir_list.Contains(dirj))
										delete_dir_list.Add(dirj);//delete the directory with smaller files
								}
								else
								{
									if (!delete_dir_list.Contains(diri))
										delete_dir_list.Add(diri);//delete the earlier directory
								}
								continue;
							}

							if (fitsjend[0] >= fitsistart[0] && fitsjend[0] <= fitsiend[0])//then j ends within i...delete the directory with smaller files
							{
								FileStream fs = new FileStream(filei, FileMode.Open);
								long fli = fs.Length;
								fs.Close();
								fs = new FileStream(filej, FileMode.Open);
								long flj = fs.Length;
								fs.Close();

								if (flj < fli)
								{
									if (!delete_dir_list.Contains(dirj))
										delete_dir_list.Add(dirj);//delete the directory with smaller files
								}
								else
								{
									if (!delete_dir_list.Contains(diri))
										delete_dir_list.Add(diri);//delete the earlier directory
								}
								continue;
							}
						}
					}

					for (int w = 0; w < delete_dir_list.Count; w++)
					{
						try
						{
							Directory.Delete((string)delete_dir_list[w], true);
						}
						catch
						{
						}
					}
				}

				if (WAITBAR.Tag == null)
					continue;

				string objVISdir = multidirs[dirindex] + "\\" + "VIS";
				if (!Directory.Exists(objVISdir))
					continue;//return;//leave because there is no VIS directory

				ArrayList del_file_list = new ArrayList();
				DiscardL1DuplicateWrkr.ReportProgress(-1, /*null*/ new object[] { multidirs.Length, dirindex + 1, del_file_list.Count });
				string[] VISdirs = Directory.GetDirectories(objVISdir, "*VIS*");//there may be multiple VIS directories...go through them and check for repeated VIS files

				//for all VIS files, scan forward and delete the forward/secondary ones...i.e. the repeated files with the exact same time
				int intprog = 1;
				string[] VISfiles = Directory.GetFiles(objVISdir, "*VIS*.fits", SearchOption.AllDirectories);

				uint[] times = new uint[VISfiles.Length];

				for (int i = 0; i < times.Length; i++)
					times[i] = Convert.ToUInt32(VISfiles[i].Substring(VISfiles[i].LastIndexOf("_") + 1, 13));

				for (int j = 0; j < VISfiles.Length - 1; j++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					if (100 * j / VISfiles.Length > intprog)
					{
						intprog++;
						DiscardL1DuplicateWrkr.ReportProgress(-intprog, new object[] { multidirs.Length, dirindex + 1, del_file_list.Count });
					}

					//String Jtime = VISfiles[j].Substring(VISfiles[j].LastIndexOf("_") + 1, 13);
					uint Jtime = times[j];
					for (int k = j + 1; k < VISfiles.Length; k++)
					{
						//String Ktime = VISfiles[k].Substring(VISfiles[k].LastIndexOf("_") + 1, 13);
						uint Ktime = times[k];
						if (Ktime == Jtime)
							del_file_list.Add(VISfiles[k]);
					}
				}
				for (int i = 0; i < del_file_list.Count; i++)
					if (File.Exists((string)del_file_list[i]))
						File.Delete((string)del_file_list[i]);

				//delete any empty directories
				VISdirs = Directory.GetDirectories(objVISdir, "*VIS*");
				for (int j = 0; j < VISdirs.Length; j++)
					if (Directory.GetFiles(VISdirs[j]).Length == 0)
						Directory.Delete(VISdirs[j]);
				VISdirs = Directory.GetDirectories(objVISdir, "*VIS*");

				try
				{
					//now must check for directories which have been created but should actually be continuations
					//so sort the directories by time, then for each sorted directory, check the first and last files for continuation
					//if there is, then move the secondary files to the first directory
					double[] VISdirtimes = new double[VISdirs.Length];
					for (int j = 0; j < VISdirs.Length; j++)
						VISdirtimes[j] = Convert.ToDouble(VISdirs[j].Substring(VISdirs[j].LastIndexOf("_") + 1));
					Array.Sort(VISdirtimes, VISdirs);
					//directories now sorted by start times

					intprog = 1;
					for (int j = 1; j < VISdirs.Length; j++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						if (100 * j / VISdirs.Length > intprog)
						{
							intprog++;
							DiscardL1DuplicateWrkr.ReportProgress(-intprog - 100, new object[] { multidirs.Length, dirindex });//null to tell it to display stuff about VIS
						}

						string[] jm1files = Directory.GetFiles(VISdirs[j - 1], "*VIS*.fits");
						string[] jfiles = Directory.GetFiles(VISdirs[j], "*VIS*.fits");
						if (jm1files.Length == 0)
							continue;
						Array.Sort(jm1files);
						Array.Sort(jfiles);
						double jm1fileendtime = Convert.ToDouble(jm1files[jm1files.Length - 1].Substring(jm1files[jm1files.Length - 1].LastIndexOf("_") + 1, 13));
						double jfilestartttime = Convert.ToDouble(jfiles[0].Substring(jfiles[0].LastIndexOf("_") + 1, 13));
						string jm1path = jm1files[0].Substring(0, jm1files[0].LastIndexOf("\\")) + "\\";

						if (jfilestartttime - jm1fileendtime <= 4 * 1000)//less than 4 seconds they should be the same sequence...1 ideally should be enough of a check
						{
							//then move the j files into j-1
							for (int k = 0; k < jfiles.Length; k++)
							{
								jfilestartttime = Convert.ToDouble(jfiles[k].Substring(jfiles[k].LastIndexOf("_") + 1, 13));
								if (jfilestartttime - jm1fileendtime <= 4 * 1000)
								{
									string jfile = jfiles[k].Substring(jfiles[k].LastIndexOf("\\") + 1);
									File.Move(jfiles[k], jm1path + jfile);
									jm1fileendtime = jfilestartttime;
								}
							}
							//and skip the current directory on next iteration
							//j++;
						}
					}

					//delete any empty directories
					VISdirs = Directory.GetDirectories(objVISdir, "*VIS*");
					for (int j = 0; j < VISdirs.Length; j++)
						if (Directory.GetFiles(VISdirs[j]).Length == 0)
							Directory.Delete(VISdirs[j]);

					if (L1DiscardDataTimeChck.Checked)
					{
						string discardtimestring = (string)L1DiscardDataTimeDrop.SelectedItem;
						discardtimestring = discardtimestring.Replace(" Minutes", "");
						int discardtimeint = Convert.ToInt32(discardtimestring) * 60;

						VISdirs = Directory.GetDirectories(objVISdir, "*VIS*");
						for (int i = 0; i < VISdirs.Length; i++)
							if (Directory.GetFiles(VISdirs[i]).Length < discardtimeint)
								Directory.Delete(VISdirs[i], true);
					}
				}
				catch (Exception ex)
				{
					MessageBox.Show(ex.Data + "	" + ex.InnerException + "	" + ex.Message + "	" + ex.Source + "	" + ex.StackTrace + "	" + ex.TargetSite);
				}
			}
		}

		private void DiscardL1DuplicateWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			if (e.UserState != null && e.ProgressPercentage >= 0)
			{
				object[] ustate = (object[])e.UserState;
				int dirindex = (int)ustate[3];
				int ndirs = (int)ustate[2];
				int nfiles = (int)ustate[1];
				int nfound = (int)ustate[0];
				WAITBAR.ProgressBar.Maximum = nfiles + 1;
				WAITBAR.ProgressBar.Value = e.ProgressPercentage;
				WAITBAR.TextMsg.Text = "Checking centroid list " + e.ProgressPercentage.ToString() + " of " + nfiles.ToString() + ". Found " + nfound.ToString() + " duplicated data sets.";
				WAITBAR.Text = "Processing target session folder " + dirindex.ToString() + " of " + ndirs.ToString();
				WAITBAR.Refresh();
				return;
			}
			if (/*e.UserState == null &&*/ e.ProgressPercentage < 0 && e.ProgressPercentage >= -100)
			{
				object[] ustate = (object[])e.UserState;
				int dirindex = (int)ustate[1];
				int ndirs = (int)ustate[0];
				int nfils = (int)ustate[2];
				WAITBAR.ProgressBar.Maximum = 100;
				WAITBAR.ProgressBar.Value = -e.ProgressPercentage;
				WAITBAR.Text = "Scanning VIS files for repeated images...";
				WAITBAR.TextMsg.Text = "Processing target session folder " + dirindex.ToString() + " of " + ndirs.ToString() + "; Files Duplicates: " + nfils;
				WAITBAR.Refresh();
			}
			if (/*e.UserState == null &&*/ e.ProgressPercentage < -100)
			{
				object[] ustate = (object[])e.UserState;
				int dirindex = (int)ustate[1];
				int ndirs = (int)ustate[0];
				WAITBAR.ProgressBar.Maximum = 200;
				WAITBAR.ProgressBar.Value = -e.ProgressPercentage;
				WAITBAR.Text = "Consolidating VIS directories...";
				WAITBAR.TextMsg.Text = "Processing target session folder " + (dirindex + 1).ToString() + " of " + ndirs.ToString();
				WAITBAR.Refresh();
			}
		}

		private void DiscardL1DuplicateWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult != DialogResult.Cancel)
			{
				WAITBAR.ProgressBar.Value = WAITBAR.ProgressBar.Maximum;
				WAITBAR.Refresh();
				TimeSpan ts = DateTime.Now - DATE;
				if (!L1AutoRunChck.Checked)
					MessageBox.Show("Completed digesting L1 data and discarding duplicated data in " + ts.Minutes.ToString() + "m" + ts.Seconds.ToString() + "s.", "Finished...");
			}
			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;
			this.BringToFront();

			if (L1AutoRunChck.Checked && !L1SkipINTMode.Checked)
			{
				string visparentdir = (string)REG.GetReg("CCDLAB", "L2EventListPath") + "\\" + "VIS";
				string[] visdirs = Directory.GetDirectories(visparentdir);
				int N = 0, index = 0;
				for (int i = 0; i < visdirs.Length; i++)
					if (Directory.GetFiles(visdirs[i]).Length > N)
					{
						index = i;
						N = Directory.GetFiles(visdirs[i]).Length;
					}

				string[] files = Directory.GetFiles(visdirs[index], "*VIS*.fits");

				FITSImageSet medianset = new FITSImageSet();
				medianset.Load(files, null, false, true, true, "");

				FITSImage median = FITSImageSet.Median(medianset, false, true, "Median Background");
				median.Header.AddKey("NIMAGES", medianset.Count.ToString(), "Number of images used", -1);
				median.WriteImage(visparentdir + "\\" + "median.fts", TypeCode.Double, true);

				FileListDrop.Items.Clear();
				IMAGESET.Clear();
				string[] filelist = new string[] { median.FullFileName };
				AddToImageSet(filelist, true);
				this.Enabled = true;
				this.BringToFront();

				if (!L1AutoProceedVISBackGround.Checked)
					if (MessageBox.Show("OK to proceed with this image for background subtraction?", "Background correction?", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;

				UVITBATCHOP = true;
				MainTab.SelectTab("BatchTab");
				BatchOperationTab.SelectTab("BatchIndividualTab");
				BatchScanDirectoryBtn.PerformClick();
				BatchFileParallelChck.Checked = L1MachineExtremeChck.Checked;
				UVITBATCHMESG = "Subtracting Median from " + BATCHLIST.Length + " VIS Images...";
				FILESAVEPREC = TypeCode.Int32;
				BatchComputeBtn_Click(sender, e);
				FILESAVEPREC = TypeCode.Double;
				UVITBATCHMESG = "";
				if (UVITBATCHOP_CANCELLED)
				{
					UVITBATCHOP_CANCELLED = false;
					return;
				}

				if (!L1AutoProceedVISTracking.Checked)
					if (MessageBox.Show("Proceed to Drift Series Tracking?", "Proceed with Drift?", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					{
						AUTOVISDRIFT = false;
						return;
					}

				REG.SetReg("CCDLAB", "L2EventListPath", visparentdir);
				AUTOVISDRIFT = true;
				UVITMANREGDIRLISTINDEX = 0;
				HalfWidthXUpD.Value = 5;
				HalfWidthYUpD.Value = 5;
				ManRegTrkHWUpD.Value = HalfWidthXUpD.Value;
				CreateDriftFromINTMenuItem_Click(sender, e);
				return;
			}
		}

		private void CreateFlatFieldListMenuItem_Click(object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = true;
			dlg.Title = "Select the Centroid INTEGERS List(s) (_XYInts_List)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;

			dir = dlg.FileNames[0].Substring(0, dlg.FileNames[0].LastIndexOf("\\"));
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			ProgressBar.Maximum = dlg.FileNames.Length;
			ProgressBar.Value = 0;

			for (int i = 0; i < dlg.FileNames.Length; i++)
			{
				ProgressBar.Value++;
				ProgressBar.Refresh();

				FITSImage intsfits = new JPFITS.FITSImage(dlg.FileNames[i], null, true, true, false, true);
				FITSImage flat = null;
				string channel = intsfits.Header.GetKeyValue("CHANNEL");
				if (channel == "")
					channel = intsfits.Header.GetKeyValue("DETECTOR");
				bool flatsuccess = false;
				if (channel == "FUV")
					if (File.Exists("C:\\UVIT_CalDB\\Flats Normalized\\FUV Normalized Flat.fits"))
					{
						flat = new FITSImage("C:\\UVIT_CalDB\\Flats Normalized\\FUV Normalized Flat.fits", null, true, true, false, true);
						flatsuccess = true;
					}
				if (channel == "NUV")
					if (File.Exists("C:\\UVIT_CalDB\\Flats Normalized\\NUV Normalized Flat.fits"))
					{
						flat = new FITSImage("C:\\UVIT_CalDB\\Flats Normalized\\NUV Normalized Flat.fits", null, true, true, false, true);
						flatsuccess = true;
					}
				if (channel == "VIS")
					if (File.Exists("C:\\UVIT_CalDB\\Flats Normalized\\VIS Normalized Flat.fits"))
					{
						flat = new FITSImage("C:\\UVIT_CalDB\\Flats Normalized\\VIS Normalized Flat.fits", null, true, true, false, true);
						flatsuccess = true;
					}
				if (!flatsuccess)
				{
					MessageBox.Show("Couldn't find the flat file in the CalDB...stopping.", "Error");
					return;
				}

				int NPts = intsfits.Height;
				double[] flatlist = new double[NPts];

				for (int j = 0; j < NPts; j++)
				{
					int xpos = (int)(intsfits[0, j] / 32);
					int ypos = (int)(intsfits[1, j] / 32);
					if (xpos < 0 || xpos > 511 || ypos < 0 || ypos > 511)
						flatlist[j] = 1;
					else
						flatlist[j] = flat[xpos, ypos];
				}

				string name = dlg.FileNames[i].Substring(0, dlg.FileNames[i].IndexOf("XYInts")) + "FlatList.fits";
				FITSImage fitsflatlist = new FITSImage(name, flatlist, false, true);
				fitsflatlist.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
				fitsflatlist.WriteImage(TypeCode.Double, true);
			}

			MessageBox.Show("Completed making the flat field list(s).", "Finished...");
			ProgressBar.Value = 0;
			ProgressBar.Refresh();
		}

		private void ParcelStackmdMmChck_Click(object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			ParcelListAsFramesMenuItem.ShowDropDown();
		}

		private void ParcelStackTimeDrop_Click(object sender, EventArgs e)
		{
			string time = (string)ParcelStackTimeDrop.SelectedItem;
			time = time.Remove(time.IndexOf("s"));
			UVPARCELTIME = Convert.ToDouble(time);

			if (UVPARCELTIME == 0)
				if (MessageBox.Show("Parcelling out each frame as a file can create an extremely large number of files. Are you sure?", "Warning...", MessageBoxButtons.YesNo) == DialogResult.No)
					return;

			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = false;
			dlg.Title = "Select the Centroid INTEGERS List (_XYInts_List)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;

			string intslistfile = dlg.FileName;
			dir = intslistfile.Substring(0, intslistfile.LastIndexOf("\\"));
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			string parceldir = dir + "\\" + UVPARCELTIME.ToString() + "\\";
			if (Directory.Exists(parceldir))
				Directory.Delete(parceldir, true);
			Directory.CreateDirectory(parceldir);

			string mindir = "";
			string maxmindir = "";
			if (ParcelStackmdMmChck.Checked)
			{
				mindir = dir + "\\" + UVPARCELTIME.ToString() + "min" + "\\";
				maxmindir = dir + "\\" + UVPARCELTIME.ToString() + "dMaxmin" + "\\";

				if (Directory.Exists(mindir))
					Directory.Delete(mindir, true);
				Directory.CreateDirectory(mindir);

				if (Directory.Exists(maxmindir))
					Directory.Delete(maxmindir, true);
				Directory.CreateDirectory(maxmindir);
			}

			REG.SetReg("CCDLAB", "FolderBrowserPath", parceldir);

			//ok so now send the filenames and dir to the worker arg, load the fits files and arrays there
			object[] arg = new object[4];
			arg[0] = (object)intslistfile;
			arg[1] = (object)parceldir;
			if (ParcelStackmdMmChck.Checked)
			{
				arg[2] = mindir;
				arg[3] = maxmindir;
			}
			else
			{
				arg[2] = null;
				arg[3] = null;
			}

			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = 100;
			WAITBAR.DialogResult = DialogResult.OK;
			WAITBAR.Text = "Parcelling List...";
			ParcelUVCentroidWrkr.RunWorkerAsync(arg);
			WAITBAR.Show();
		}

		private void ParcelUVCentroidWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			object[] arg = (object[])e.Argument;
			string intslistfile = (string)arg[0];
			string fraclistfile = intslistfile.Replace("Ints", "Frac");
			string parceldir = (string)arg[1];
			string mindir = (string)arg[2];
			string maxmindir = (string)arg[3];
			string timeslistfile = intslistfile.Remove(intslistfile.IndexOf("XYInts_List")) + "TimeList.fits";
			string deDrift = "_deDrift";
			while (intslistfile.Contains(deDrift))
			{
				timeslistfile = timeslistfile.Replace("TimeList", "TimeList_deDrift");
				deDrift += "_deDrift";
			}
			string mdMmfile = "";
			FITSImage mdMmlist = null;
			double[,] mdMms = null;
			if (mindir != null)
			{
				mdMmfile = timeslistfile.Replace("TimeList", "XYmdMm_List");
				mdMmlist = new JPFITS.FITSImage(mdMmfile, null, true, false, false, false);
				mdMms = FITSImage.ReadImageArrayOnly(mdMmfile, null, true);
			}

			FITSImage timeslist = new JPFITS.FITSImage(timeslistfile, null, true, false, false, false);
			double[] times = FITSImage.ReadImageVectorOnly(timeslistfile, null, true);

			FITSImage intslist = new JPFITS.FITSImage(intslistfile, null, true, false, false, false);
			double[,] ints = FITSImage.ReadImageArrayOnly(intslistfile, null, true);

			FITSImage fraclist = new JPFITS.FITSImage(fraclistfile, null, true, false, false, false);
			double[,] frac = FITSImage.ReadImageArrayOnly(fraclistfile, null, true);

			string EXTXRNG = fraclist.Header.GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
			if (EXTXRNG == "")
				EXTXRNG = "0:511";//from L2 data
			string EXTYRNG = fraclist.Header.GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
			if (EXTYRNG == "")
				EXTYRNG = "0:511";//from L2 data
			int ix = EXTXRNG.IndexOf(":");
			int iy = EXTYRNG.IndexOf(":");
			int rx1 = Convert.ToInt32(EXTXRNG.Substring(0, ix));//range start
			int ry1 = Convert.ToInt32(EXTYRNG.Substring(0, iy));
			int rx2 = Convert.ToInt32(EXTXRNG.Substring(ix + 1));//range end
			int ry2 = Convert.ToInt32(EXTYRNG.Substring(iy + 1));

			string xoffset = intslist.Header.GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
			if (xoffset == "")
				xoffset = intslist.Header.GetKeyValue("WIN_XOFF");//from L2 data
			double ox = Convert.ToDouble(xoffset);//x offset
			string yoffset = intslist.Header.GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
			if (yoffset == "")
				yoffset = intslist.Header.GetKeyValue("WIN_YOFF");//from L2 data
			double oy = Convert.ToDouble(yoffset);//y offset
			string sizex = intslist.Header.GetKeyValue("XSIZE");
			if (sizex == "")
				sizex = intslist.Header.GetKeyValue("WIN_X_SZ");
			int szx = Convert.ToInt32(sizex);//x size
			string sizey = intslist.Header.GetKeyValue("YSIZE");
			if (sizey == "")
				sizey = intslist.Header.GetKeyValue("WIN_Y_SZ");
			int szy = Convert.ToInt32(sizey);//y size

			if (rx1 != 0 && rx2 != 511)
				szx = rx2 - rx1;
			if (ry1 != 0 && ry2 != 511)
				szy = ry2 - ry1;

			int prec = 1;
			szx = (szx + 1) * prec;
			szy = (szy + 1) * prec;

			ArrayList imgfilenames = new ArrayList();
			int[,] img = null;
			int[,] minimg = null;
			int[,] maxminimg = null;
			int[] foundinds = null;
			int ind = -1;
			int Ntimes = times.Length;
			int Nfound;
			int xpos, ypos;
			FITSImage FITSimg;
			FITSImage FITSminimg;
			FITSImage FITSmaxminimg;
			string parcelname;
			string minname;
			string maxminname;
			int c = 0;
			uint currtime = 0;
			int intprog = 0;
			bool end = false;//the routine will have to tell when it is at the end of the time list
			while (!end)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					break;
				if (100 * ind / Ntimes > intprog + 1)
				{
					intprog++;
				}
				ParcelUVCentroidWrkr.ReportProgress(intprog, c + 1);

				c++;
				currtime = (uint)times[ind + 1];
				img = new int[(int)szx, (int)szy];
				minimg = new int[(int)szx, (int)szy];
				maxminimg = new int[(int)szx, (int)szy];
				foundinds = JPMath.Find(times, times[ind + 1] + UVPARCELTIME * 1000, "<=", ind + 1);
				if (foundinds.Length == 0)
					goto nonefound;
				Nfound = foundinds.Length;
				ind = foundinds[Nfound - 1];
				if (ind == Ntimes - 1)
					end = true;

				int j;
				for (j = 0; j < Nfound; j++)
				{
					xpos = (int)((ints[0, foundinds[j]] - rx1 * 32 - ox * 32 + frac[0, foundinds[j]] + 16) / 32 * prec);//reset integers to start at 0
					ypos = (int)((ints[1, foundinds[j]] - ry1 * 32 - oy * 32 + frac[1, foundinds[j]] + 16) / 32 * prec);//must add 16 to fractionals

					if (xpos < 0 || ypos < 0 || xpos > szx - 1 || ypos > szy - 1)//ignore out of bounds
						continue;

					img[xpos, ypos]++;
					if (mindir != null)
					{
						minimg[xpos, ypos] += (int)mdMms[0, foundinds[j]];
						maxminimg[xpos, ypos] += (int)mdMms[1, foundinds[j]];
					}
				}

			nonefound:;

				if (mindir != null)
				{
					for (int x = 0; x < szx; x++)
						for (int y = 0; y < szy; y++)
							if (img[x, y] != 0)
							{
								minimg[x, y] /= img[x, y];
								maxminimg[x, y] /= img[x, y];
							}
				}

				parcelname = parceldir + currtime.ToString("0000000000000") + ".fits";
				FITSimg = new FITSImage(parcelname, img, false, true);
				FITSimg.Header.CopyHeaderFrom(intslist.Header);// CopyHeader(intslist);
				FITSimg.Header.AddKey("PARCTIME", currtime.ToString("0000000000000"), "Parcel time.", 10);
				FITSimg.Header.AddKey("FRMTIME", ((double)(currtime) / 1000).ToString(), "Frame time.", 11);
				FITSimg.WriteImage(TypeCode.UInt16, true);
				imgfilenames.Add(parcelname);

				if (mindir != null)
				{
					minname = mindir + currtime.ToString("0000000000000") + ".fits";
					maxminname = maxmindir + currtime.ToString("0000000000000") + ".fits";

					FITSminimg = new FITSImage(minname, minimg, false, true);
					FITSmaxminimg = new FITSImage(maxminname, maxminimg, false, true);

					FITSminimg.Header.CopyHeaderFrom(intslist.Header);// CopyHeader(intslist);
					FITSmaxminimg.Header.CopyHeaderFrom(intslist.Header);// CopyHeader(intslist);

					FITSminimg.Header.AddKey("PARCTIME", currtime.ToString("0000000000000"), "Parcel time.", 10);
					FITSminimg.Header.AddKey("FRMTIME", ((double)(currtime) / 1000).ToString(), "Frame time.", 11);
					FITSminimg.WriteImage(TypeCode.UInt16, true);

					FITSmaxminimg.Header.AddKey("PARCTIME", currtime.ToString("0000000000000"), "Parcel time.", 10);
					FITSmaxminimg.Header.AddKey("FRMTIME", ((double)(currtime) / 1000).ToString(), "Frame time.", 11);
					FITSmaxminimg.WriteImage(TypeCode.UInt16, true);
				}
			}

			e.Result = imgfilenames;
		}

		private void ParcelUVCentroidWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Completed: " + e.ProgressPercentage + "%: " + (int)e.UserState + " frames...";
			WAITBAR.Refresh();
		}

		private void ParcelUVCentroidWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;
			this.BringToFront();
			//if (WAITBAR.DialogResult != DialogResult.Cancel)
			if (MessageBox.Show("Parcelling completed or stopped.  Would you like to load the images for viewing?", "Finished...", MessageBoxButtons.YesNo) == DialogResult.No)
				return;

			ArrayList imgfilenames = (ArrayList)e.Result;
			string[] filelist = new string[imgfilenames.Count];
			for (int i = 0; i < imgfilenames.Count; i++)
				filelist[i] = (string)imgfilenames[i];

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(filelist, true);
			this.Enabled = true;
			this.BringToFront();
		}

		private void PlotDriftListMenuItem_Click(object sender, EventArgs e)
		{
			string driftlistfile;
			if (UVPLOTDRIFTLISTNOW)
			{
				//UVPLOTDRIFTLISTNOW = false;***************************************done below with multi-source track plot now
				driftlistfile = UVPLOTDRIFTFILENAME;
			}
			else
			{
				string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				OpenFileDialog dlg = new OpenFileDialog();
				dlg.InitialDirectory = dir;
				dlg.Filter = "DRIFT (*.drift)|*.drift";
				dlg.Multiselect = false;
				dlg.Title = "Select the Drift List (_XYDrift_List)";
				DialogResult res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;
				driftlistfile = dlg.FileName;
			}

			FITSImage driftfits = new JPFITS.FITSImage(driftlistfile, null, true, true, false, true);

			//only want to plot unique drifts or else 100,000's data to be plotted which is slow
			int unique = 1;
			int xd = (int)driftfits[1, 0], yd = (int)driftfits[2, 0];
			for (int i = 1; i < driftfits.Height; i++)
			{
				if (xd == (int)driftfits[1, i] && yd == (int)driftfits[2, i])
					continue;

				unique++;
				xd = (int)driftfits[1, i];
				yd = (int)driftfits[2, i];
			}
			//now unique is how many unique drifts there are, so make arrays for time, x, y

			double[] time = new double[unique];
			double[] xdrift = new double[unique];
			double[] ydrift = new double[unique];

			unique = 0;//now an index
			time[unique] = driftfits[0, 0] / 1000;
			xdrift[unique] = driftfits[1, 0] / 32;
			ydrift[unique] = driftfits[2, 0] / 32;

			xd = (int)driftfits[1, 0];
			yd = (int)driftfits[2, 0];
			for (int i = 1; i < driftfits.Height; i++)
			{
				if (xd == (int)driftfits[1, i] && yd == (int)driftfits[2, i])
					continue;

				unique++;
				xd = (int)driftfits[1, i];
				yd = (int)driftfits[2, i];

				time[unique] = driftfits[0, i] / 1000;
				xdrift[unique] = driftfits[1, i] / 32;
				ydrift[unique] = driftfits[2, i] / 32;
			}

			string title = "Orbit: " + driftfits.Header.GetKeyValue("ORB_NUM") + "; Source: " + driftfits.Header.GetKeyValue("SOURCEID") + "; Detector:" + driftfits.Header.GetKeyValue("DETECTOR");

			if (XDRIFT_PLOT.IsDisposed)
				XDRIFT_PLOT = new JPPlot();
			if (YDRIFT_PLOT.IsDisposed)
				YDRIFT_PLOT = new JPPlot();

			XDRIFT_PLOT.Text = "X-Drift";
			XDRIFT_PLOT.PlotLine(JPMath.VectorSubScalar(time, time[0], true), xdrift, "Time - " + time[0].ToString() + " (seconds)", "X-Drift (pixels)", title, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "XDrift");
			if (XDRIFT_PLOT.JPChart1.ChartContextGridChck.Checked == false)
				XDRIFT_PLOT.JPChart1.ChartContextGridChck.PerformClick();
			YDRIFT_PLOT.Text = "Y-Drift";
			YDRIFT_PLOT.PlotLine(JPMath.VectorSubScalar(time, time[0], true), ydrift, "Time - " + time[0].ToString() + " (seconds)", "Y-Drift (pixels)", title, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "YDrift");
			if (YDRIFT_PLOT.JPChart1.ChartContextGridChck.Checked == false)
				YDRIFT_PLOT.JPChart1.ChartContextGridChck.PerformClick();

			if (UVPLOTDRIFTLISTNOW && MANREGCENTROIDS != null)
			{
				double[] tttime = new double[driftfits.Height];
				double[] xxdrft = new double[driftfits.Height];
				double[] yydrft = new double[driftfits.Height];
				double meanxxd = 0, meanyyd = 0;
				for (int j = 0; j < MANREGCENTROIDS.GetLength(0); j++)
					for (int i = 0; i < driftfits.Height; i++)
					{
						if (j == 0)
							tttime[i] = (driftfits[0, i] - driftfits[0, 0]) / 1000;

						meanxxd += (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]);
						meanyyd += (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]);
					}
				meanxxd /= MANREGCENTROIDS.GetLength(0) * driftfits.Height;
				meanyyd /= MANREGCENTROIDS.GetLength(0) * driftfits.Height;

				for (int j = 0; j < MANREGCENTROIDS.GetLength(0); j++)
				{
					for (int i = 0; i < driftfits.Height; i++)
					{
						xxdrft[i] = (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) - meanxxd;
						yydrft[i] = (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]) - meanyyd;
					}
					XDRIFT_PLOT.AddLine(tttime, xxdrft, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, j.ToString());
					YDRIFT_PLOT.AddLine(tttime, yydrft, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, j.ToString());
				}
			}
			MANREGCENTROIDS = null;
			UVPLOTDRIFTLISTNOW = false;
		}

		private void DriftFromPCPSTrackBtn_Click(System.Object sender, EventArgs e)
		{
			//this function is the initiator and also the revisitor

			//initiator on !UVDRIFTBATCH
			if (!UVDRIFTBATCH)
			{
				if (PSEEllipticalROI.Checked)
					MakeEllipticalROI_REGION(SubImageSlideX.Value - 1, SubImageSlideY.Value - 1, (int)HalfWidthXUpD.Value, (int)HalfWidthYUpD.Value);

				if (PointSrcROIFindSrcChck.Checked && !PointSrcROIAutoRunChck.Checked)
				{
					int Nsrc = Convert.ToInt32(PointSrcROIFindNSrcDrop.SelectedItem);
					PSES = new JPFITS.PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
					PSESINDEX = 0;
					/*PSES[PSESINDEX].Extract_Attempt_N_Sources(Nsrc, IMAGESET[FILELISTINDEX].Image, 0, 0, Double.MaxValue, 0, Double.MaxValue, false, 2, 35, true, "", ROI_REGION, false);
					if (PSES[PSESINDEX].N_Sources > Nsrc)
						PSES[PSESINDEX].ClipToNBrightest(Nsrc);*/
					int niters;
					PSES[PSESINDEX].Extract_Attempt_NBrightestSources(Nsrc, IMAGESET[FILELISTINDEX].Image, 0, 2, 35, true, "", ROI_REGION, false, out niters);

					if (PSES[PSESINDEX].N_Sources == 0)
					{
						MessageBox.Show("No sources found. Please manually select sources.", "Error...");
						return;
					}

					MARKCOORDS = new double[2, PSES[PSESINDEX].N_Sources];
					for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
					{
						MARKCOORDS[0, i] = PSES[PSESINDEX].Centroids_X[i];
						MARKCOORDS[1, i] = PSES[PSESINDEX].Centroids_Y[i];
					}
					MAKEMARKCOORDRECTS();
					PSES = null;

					ImageWindow.Refresh();
					SubImageWindow.Refresh();

					if (MessageBox.Show("Use these sources for optimization?", "Proceed with these sources?", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
						return;
				}

				if (PointSrcROIAutoRunChck.Checked)
					if (HalfWidthXUpD.Value > 9 || HalfWidthYUpD.Value > 9)
					{
						HalfWidthXUpD.Value = /*SUBIMAGE_HWX_OLD;*/9;
						HalfWidthYUpD.Value = /*SUBIMAGE_HWY_OLD;*/9;
					}
				/*if (HalfWidthXUpD.Value == 0 || HalfWidthYUpD.Value == 0)
				{
					HalfWidthXUpD.Value = 9;
					HalfWidthYUpD.Value = 9;
				}*/

				AUTOLOADIMAGESFILES = new string[IMAGESET.Count];
				UVDRIFTBATCHFILES = new string[IMAGESET.Count];//must fill these here first with XYInts
				for (int i = 0; i < IMAGESET.Count; i++)
				{
					string imgname = IMAGESET[i].FullFileName;
					string dedrift = "";
					while (imgname.Contains(dedrift + "_deDrift"))
						dedrift += "_deDrift";

					string intsname = imgname.Substring(0, imgname.IndexOf("_IMAGE"));
					intsname = intsname.Insert(intsname.IndexOf("deFPN"), "XYInts_List_") + ".fits";
					UVDRIFTBATCHFILES[i] = intsname;
				}
				DRIFTFROMPCPSTRACK = true;
				UVDRIFTBATCH = true;
				UVDRIFTAUTORUN = true;
				UVCONVERTLISTTOIMAGEBATCH = false;
				UVAutoApplyDriftandImageChck.Checked = true;
				UVAutoDriftImageViewChck.Checked = false;
				UVDRIFTBATCHFILESINDEX = 0;
			}

			if (PointSrcROIAutoRunChck.Checked)
			{
				FileListDrop.SelectedIndex = UVDRIFTBATCHFILESINDEX;
				int Nsrc = Convert.ToInt32(PointSrcROIFindNSrcDrop.SelectedItem);//or just set to 3???
				PSES = new JPFITS.PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
				PSESINDEX = 0;
				/*PSES[PSESINDEX].Extract_Attempt_N_Sources(Nsrc, IMAGESET[UVDRIFTBATCHFILESINDEX].Image, 0, 0, Double.MaxValue, 0, Double.MaxValue, false, 9, 35, true, "", ROI_REGION, false);
				if (PSES[PSESINDEX].N_Sources > Nsrc)
					PSES[PSESINDEX].ClipToNBrightest(Nsrc);*/
				int iters;
				PSES[PSESINDEX].Extract_Attempt_NBrightestSources(Nsrc, IMAGESET[UVDRIFTBATCHFILESINDEX].Image, 0, 2, 35, true, "", ROI_REGION, false, out iters);//why was it 9 instead of 2 above?

				if (PSES[PSESINDEX].N_Sources == 0)
				{
					MessageBox.Show("No sources found. Please manually select sources.", "Error...");
					AUTOLOADIMAGESFILES = null;
					UVDRIFTBATCHFILES = null;
					DRIFTFROMPCPSTRACK = false;
					UVDRIFTBATCH = false;
					UVDRIFTAUTORUN = false;
					UVCONVERTLISTTOIMAGEBATCH = false;
					UVAutoApplyDriftandImageChck.Checked = false;
					UVAutoDriftImageViewChck.Checked = false;
					UVDRIFTBATCHFILESINDEX = -1;
					return;
				}

				MARKCOORDS = new double[2, PSES[PSESINDEX].N_Sources];
				for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
				{
					MARKCOORDS[0, i] = PSES[PSESINDEX].Centroids_X[i];
					MARKCOORDS[1, i] = PSES[PSESINDEX].Centroids_Y[i];
				}
				MAKEMARKCOORDRECTS();
				PSES = null;

				ImageWindow.Refresh();
				SubImageWindow.Refresh();
			}

			if (UVDRIFTBATCHFILESINDEX == 0)//initiator
			{
				//DATE = DateTime.Now;

				this.Enabled = false;
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = 100;
				WAITBAR.Text = "File " + (UVDRIFTBATCHFILESINDEX + 1).ToString() + " of " + UVDRIFTBATCHFILES.Length + ". Optimizing PSF...";
				DriftFromPCPSTrackBGWrkr.RunWorkerAsync();
				WAITBAR.ShowDialog();
			}
			else//revisitor
			{
				WAITBAR.ProgressBar.Value = (UVDRIFTBATCHFILESINDEX + 1) * 100 / UVDRIFTBATCHFILES.Length;
				WAITBAR.Text = "File " + (UVDRIFTBATCHFILESINDEX + 1).ToString() + " of " + UVDRIFTBATCHFILES.Length + ". Optimizing PSF...";
				DriftFromPCPSTrackBGWrkr.RunWorkerAsync();
			}
		}

		private void DriftFromPCPSTrackBGWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
				return;

			string imgname = IMAGESET[UVDRIFTBATCHFILESINDEX].FullFileName;
			string dedrift = "";
			while (imgname.Contains(dedrift + "_deDrift"))
				dedrift += "_deDrift";

			string timesname = imgname.Substring(0, imgname.IndexOf("deFPN")) + "TimeList" + dedrift + ".fits";
			string intsname = imgname.Substring(0, imgname.IndexOf("_IMAGE"));
			intsname = intsname.Insert(intsname.IndexOf("deFPN"), "XYInts_List_") + ".fits";
			string fracsname = intsname.Replace("Ints", "Frac");

			JPFITS.FITSImage IntsFits = new FITSImage(intsname, null, true, false, false, false);
			double[] times = FITSImage.ReadImageVectorOnly(timesname, null, true);
			double[,] fracs = FITSImage.ReadImageArrayOnly(fracsname, null, true);
			double[,] ints = FITSImage.ReadImageArrayOnly(intsname, null, true);

			string FlatFileList;
			double[] flat;
			FlatFileList = timesname.Replace("Time", "Flat");
			flat = FITSImage.ReadImageVectorOnly(FlatFileList, null, true);

			string EXTXRNG = IntsFits.Header.GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
			if (EXTXRNG == "")
				EXTXRNG = "0:511";//from L1 data
			string EXTYRNG = IntsFits.Header.GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
			if (EXTYRNG == "")
				EXTYRNG = "0:511";//from L1 data
			int ix = EXTXRNG.IndexOf(":");
			int iy = EXTYRNG.IndexOf(":");
			double rx1 = Convert.ToDouble(EXTXRNG.Substring(0, ix));//range start
			double ry1 = Convert.ToDouble(EXTYRNG.Substring(0, iy));
			double rx132 = rx1 * 32;
			double ry132 = ry1 * 32;
			double rx2 = Convert.ToDouble(EXTXRNG.Substring(ix + 1));//range end
			double ry2 = Convert.ToDouble(EXTYRNG.Substring(iy + 1));

			string xoffset = IntsFits.Header.GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
			if (xoffset == "")
				xoffset = IntsFits.Header.GetKeyValue("WIN_XOFF");//from L1 data
			double ox = Convert.ToDouble(xoffset);//x offset
			double ox32 = ox * 32;
			string yoffset = IntsFits.Header.GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
			if (yoffset == "")
				yoffset = IntsFits.Header.GetKeyValue("WIN_YOFF");//from L1 data
			double oy = Convert.ToDouble(yoffset);//y offset
			double oy32 = oy * 32;

			double rx132ox32 = rx132 + ox32;
			double ry132oy32 = ry132 + oy32;

			double prec = 1;
			string strprec = IMAGESET[UVDRIFTBATCHFILESINDEX].Header.GetKeyValue("IMAGPREC");
			if (strprec != "")
				prec = Convert.ToDouble(strprec);
			double precB32 = prec / 32;

			int offset = 0;
			string stroffset = IMAGESET[UVDRIFTBATCHFILESINDEX].Header.GetKeyValue("PADOFSET");
			if (stroffset != "")
				offset = Convert.ToInt32(stroffset);

			if (MARKCOORDS == null)//then use current ROI only
				MARKCOORDS = new double[2, 1] { { (double)XSUBRANGE[SUBIMAGE_HWX] }, { (double)YSUBRANGE[SUBIMAGE_HWY] } };

			ArrayList[] ROIsTRUE = new ArrayList[MARKCOORDS.GetLength(1)];
			int[] XSTARTS = new int[MARKCOORDS.GetLength(1)];
			int[] XENDS = new int[MARKCOORDS.GetLength(1)];
			int[] YSTARTS = new int[MARKCOORDS.GetLength(1)];
			int[] YENDS = new int[MARKCOORDS.GetLength(1)];

			Parallel.For(0, ROIsTRUE.Length, i =>
			//for (int i = 0; i < ROIsTRUE.Length; i++)
			{
				double[,] bigbox = IMAGESET[UVDRIFTBATCHFILESINDEX].GetSubImage((int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i], 20, 20);
				int maxx, maxy;
				JPMath.Max(bigbox, out maxx, out maxy, false);
				int xcent = (int)MARKCOORDS[0, i] - 20 + maxx;
				int ycent = (int)MARKCOORDS[1, i] - 20 + maxy;

				XSTARTS[i] = xcent - SUBIMAGE_HWX - offset * (int)(prec);
				YSTARTS[i] = ycent - SUBIMAGE_HWY - offset * (int)(prec);
				XENDS[i] = xcent + SUBIMAGE_HWX + 1 - offset * (int)(prec);
				YENDS[i] = ycent + SUBIMAGE_HWY + 1 - offset * (int)(prec);
				ROIsTRUE[i] = new ArrayList();

				//MessageBox.Show((XENDS[i] - XSTARTS[i]) + " "  + (YENDS[i] - YSTARTS[i]));

				for (int j = 0; j < times.Length; j++)
				{
					int xpos = (int)((ints[0, j] - rx132ox32 + fracs[0, j] + 16) * precB32);
					int ypos = (int)((ints[1, j] - ry132oy32 + fracs[1, j] + 16) * precB32);

					if (xpos >= XSTARTS[i] && ypos >= YSTARTS[i] && xpos <= XENDS[i] && ypos <= YENDS[i])
							ROIsTRUE[i].Add(j);
				}
			});

			Parallel.For(0, ROIsTRUE.Length, i =>
			{
				//for (int i = 0; i < ROIsTRUE.Length; i++)
				ROIsTRUE[i].Sort();
			});

			double[][] ROItlists = new double[MARKCOORDS.GetLength(1)][];
			double[][] ROIxcents = new double[MARKCOORDS.GetLength(1)][];
			double[][] ROIycents = new double[MARKCOORDS.GetLength(1)][];
			double[][] ROIflats = new double[MARKCOORDS.GetLength(1)][];
			int[][] ROIindexes = new int[MARKCOORDS.GetLength(1)][];
			for (int i = 0; i < ROIsTRUE.Length; i++)
			{
				ROItlists[i] = new double[ROIsTRUE[i].Count];
				ROIxcents[i] = new double[ROIsTRUE[i].Count];
				ROIycents[i] = new double[ROIsTRUE[i].Count];
				ROIflats[i] = new double[ROIsTRUE[i].Count];
				ROIindexes[i] = new int[ROIsTRUE[i].Count];
			}

			Parallel.For(0, ROIsTRUE.Length, i =>
			{
				//for (int i = 0; i < ROIsTRUE.Length; i++)
				for (int j = 0; j < ROIsTRUE[i].Count; j++)
				{
					ROIindexes[i][j] = Convert.ToInt32(ROIsTRUE[i][j]);
					ROItlists[i][j] = times[ROIindexes[i][j]];
					ROIflats[i][j] = flat[ROIindexes[i][j]];
				}
			});

			int index = -1;//only used next if needed
			bool endanalysis = false;
			double[] meanMAXarray = new double[PointSrcROIStackDriftDrop.Items.Count];
			double[] stakMAXarray = new double[PointSrcROIStackDriftDrop.Items.Count];
			bool final_determination = false;

		goagaion:
			if (PointSrcROIAutoRunChck.Checked/*MARKCOORDS.GetLength(1) > 1*/ && !final_determination)//then auto run through and find best stack time?
			{
				index++;
				if (index < PointSrcROIStackDriftDrop.Items.Count)
					PointSrcROIStackDriftDrop.SelectedIndex = index;
				if (index == PointSrcROIStackDriftDrop.Items.Count - 1)
					endanalysis = true;
				stakMAXarray[index] = Convert.ToDouble(PointSrcROIStackDriftDrop.SelectedItem);
				DriftFromPCPSTrackBGWrkr.ReportProgress(index);
			}
			if (/*MARKCOORDS.GetLength(1) == 1*/!PointSrcROIAutoRunChck.Checked)
			{
				index = PointSrcROIStackDriftDrop.SelectedIndex;
				endanalysis = true;
			}

			double[,] drift = new double[3, times.Length];

			for (int i = 0; i < MARKCOORDS.GetLength(1); i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;

				Parallel.For(0, ROIxcents[i].Length, jj =>
				//for (int jj = 0; jj < ROIxcents[i].Length; jj++)
				{
					ROIxcents[i][jj] = ints[0, ROIindexes[i][jj]] - rx132ox32 + fracs[0, ROIindexes[i][jj]] + 16;
					ROIycents[i][jj] = ints[1, ROIindexes[i][jj]] - ry132oy32 + fracs[1, ROIindexes[i][jj]] + 16;
				});

				double stackT = Convert.ToDouble(PointSrcROIStackDriftDrop.SelectedItem) * 1000;
				bool end = false;
				double currtime;
				int j = 0;
				double meanx, meany, meanT;
				double stackinstcs;
				ArrayList mt = new ArrayList();
				ArrayList mx = new ArrayList();
				ArrayList my = new ArrayList();

				while (!end)
				{
					meanx = 0;
					meany = 0;
					meanT = 0;
					stackinstcs = 0;
					currtime = ROItlists[i][j];
					while (!end && (ROItlists[i][j] - currtime) <= stackT)
					{
						meanx += ROIxcents[i][j];
						meany += ROIycents[i][j];
						stackinstcs++;
						j++;

						if (j == ROItlists[i].Length)
						{
							end = true;
							break;
						}
					}
					meanx /= stackinstcs;
					meany /= stackinstcs;
					meanT = (currtime + ROItlists[i][j - 1]) / 2;
					mt.Add(meanT);
					mx.Add(meanx);
					my.Add(meany);
				}

				double[] smx = new double[mt.Count];
				double[] smy = new double[mt.Count];
				double[] smt = new double[mt.Count];

				Parallel.For(0, mt.Count, jj =>
				//for (int jj = 0; jj < mt.Count; jj++)
				{
					smx[jj] = (double)mx[jj];
					smy[jj] = (double)my[jj];
					smt[jj] = (double)mt[jj];
				});

				smx = JPMath.VectorSubScalar(smx, JPMath.Mean(smx, true), true);//essential
				smy = JPMath.VectorSubScalar(smy, JPMath.Mean(smy, true), true);//essential
				double[] xdrift = JPMath.Interpolate1d(smt, smx, times, "akima", true);
				double[] ydrift = JPMath.Interpolate1d(smt, smy, times, "akima", true);
				/*xdrift = JPMath.VectorSubScalar(xdrift, JPMath.Mean(xdrift, true), true);
				ydrift = JPMath.VectorSubScalar(ydrift, JPMath.Mean(ydrift, true), true);*/

				Parallel.For(0, xdrift.Length, jj =>
				//for (int jj = 0; jj < xdrift.Length; jj++)
				{
					drift[1, jj] += xdrift[jj];
					drift[2, jj] += ydrift[jj];
				});
			}

			Parallel.For(0, times.Length, i =>
			//for (int i = 0; i < times.Length; i++)
			{
				drift[0, i] = times[i];
				drift[1, i] /= (double)(MARKCOORDS.GetLength(1));
				drift[2, i] /= (double)(MARKCOORDS.GetLength(1));
			});

			if (/*MARKCOORDS.GetLength(1) > 1*/PointSrcROIAutoRunChck.Checked && !final_determination)//then auto run through
			{
				double meanMAX = 0;
				//apply drift to each kernel and get the radial plot fit
				for (int i = 0; i < MARKCOORDS.GetLength(1); i++)
				{
					Parallel.For(0, ROIxcents[i].Length, j =>
					//for (int j = 0; j < ROIxcents[i].Length; j++)
					{
						ROIxcents[i][j] = ((ints[0, ROIindexes[i][j]] - rx132ox32 + fracs[0, ROIindexes[i][j]] + 16 - drift[1, ROIindexes[i][j]] - (double)XSTARTS[i] / precB32) * precB32);
						ROIycents[i][j] = ((ints[1, ROIindexes[i][j]] - ry132oy32 + fracs[1, ROIindexes[i][j]] + 16 - drift[2, ROIindexes[i][j]] - (double)YSTARTS[i] / precB32) * precB32);
					});
					double[,] kernel = new double[XENDS[i] - XSTARTS[i] + 1, YENDS[i] - YSTARTS[i] + 1];
					for (int j = 0; j < ROIxcents[i].Length; j++)
						if (ROIxcents[i][j] >= 0 && ROIxcents[i][j] <= kernel.GetLength(0) && ROIycents[i][j] >= 0 && ROIycents[i][j] <= kernel.GetLength(1))
							kernel[(int)(ROIxcents[i][j]), (int)(ROIycents[i][j])] += (1 / ROIflats[i][j]);

					int maxx, maxy;
					meanMAX += JPMath.Max(kernel, out maxx, out maxy, false);
				}
				meanMAX /= (double)MARKCOORDS.GetLength(1);
				meanMAXarray[index] = meanMAX;
				if (!endanalysis)
					goto goagaion;//do the next stack time
			}
			if (/*MARKCOORDS.GetLength(1) > 1*/PointSrcROIAutoRunChck.Checked && endanalysis && !final_determination)
			{
				/*JPPlot plot = new JPPlot();
				plot.plotchart1.PlotXYData(stakMAXarray, meanMAXarray, "test", "test", "test", .DataVisualization.System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "test");
				plot.ShowDialog();*/
				int minind = -1;
				JPMath.Max(meanMAXarray, out minind, false);
				PointSrcROIStackDriftDrop.SelectedIndex = minind;
				final_determination = true;
				goto goagaion;//solve with the best stack
			}

			string driftslistfile;
			driftslistfile = intsname.Replace("XYInts_List", "XYDrift_List" + "_" + "PSTrk" + PointSrcROIStackDriftDrop.SelectedItem);
			driftslistfile = driftslistfile.Replace(".fits", ".drift");

			//get pre-existing earlier iteration dedrifted lists and drift series and delete them
			//this is to keep things cleaner like for creating exposure array from multiple drifts if a drift series is re-calculated from an earlier iteration
			//if redoing an earlier iteration its probably because the later ones were no good anyway
			dedrift = "_deDrift";
			while (intsname.Contains(dedrift))
				dedrift += "_deDrift";
			string[] delfiles = Directory.GetFiles(intsname.Substring(0, intsname.LastIndexOf("\\")), "*" + dedrift + "*");
			for (int i = 0; i < delfiles.Length; i++)
				File.Delete(delfiles[i]);
			dedrift = dedrift.Remove(0, 8);
			delfiles = Directory.GetFiles(intsname.Substring(0, intsname.LastIndexOf("\\")), "*" + dedrift + ".drift");
			for (int i = 0; i < delfiles.Length; i++)
				File.Delete(delfiles[i]);

			FITSImage driftfits = new FITSImage(driftslistfile, drift, false, true);
			driftfits.Header.CopyHeaderFrom(IntsFits.Header);
			driftfits.Header.AddKey("PSDSTAKT", PointSrcROIStackDriftDrop.SelectedItem.ToString(), "Point Source Drift Stack Time", 14);
			driftfits.WriteImage(TypeCode.Double, false);
			UVPLOTDRIFTFILENAME = driftslistfile;
			UVAPPLYDRIFTCENTROIDSFILENAME = intsname;
		}

		private void DriftFromPCPSTrackBGWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.TextMsg.Text = "Determining optimum PSF: Analyzing " + Convert.ToDouble(PointSrcROIStackDriftDrop.Items[e.ProgressPercentage]) + "s stack (" + (e.ProgressPercentage + 1) + " of " + PointSrcROIStackDriftDrop.Items.Count + ")";
			WAITBAR.Refresh();
		}

		private void DriftFromPCPSTrackBGWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (UVDRIFTBATCHFILESINDEX + 1 == UVDRIFTBATCHFILES.Length)
				PSESeachROIOnlyChck.Checked = false;

			if (WAITBAR.DialogResult != DialogResult.Cancel)
			{
				if (PointSrcROIAutoRunChck.Checked)
				{
					MARKCOORDS = null;
					MARKCOORDRECTS = null;
					ImageWindow.Refresh();
					SubImageWindow.Refresh();
				}

				WAITBAR.Text = "Applying...";
				WAITBAR.TextMsg.Text = "Applying drift to centroid list...";
				WAITBAR.CancelBtn.Enabled = false;
				WAITBAR.Refresh();
				UVAPPLYDRIFTNOW = true;
				PCModeDriftSelfCorrectionMenuItem.PerformClick();//ApplyDriftListMentuItem_Click(sender, e);
			}
			else
			{
				this.Enabled = true;
				this.BringToFront();

				DRIFTFROMPCPSTRACK = false;
				UVDRIFTBATCH = false;
				UVDRIFTAUTORUN = false;
				UVCONVERTLISTTOIMAGEBATCH = false;
				UVAutoApplyDriftandImageChck.Checked = false;
				UVAutoDriftImageViewChck.Checked = false;
				UVDRIFTBATCHFILESINDEX = -1;
				AUTOLOADIMAGESFILES = null;
				UVDRIFTBATCHFILES = null;
			}
		}

		private void DriftFromListTimeTxt_TextChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "DriftFromListTimeTxt", DriftFromListTimeTxt.Text);
		}

		private void DriftFromListEndTimeTxt_TextChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "DriftFromListEndTimeTxt", DriftFromListEndTimeTxt.Text);
		}

		private void CreateDriftFromPCMenuItem_DropDownOpened(object sender, EventArgs e)
		{
			DriftFromListTimeTxt.Text = (string)REG.GetReg("CCDLAB", "DriftFromListTimeTxt");
			DriftFromListEndTimeTxt.Text = (string)REG.GetReg("CCDLAB", "DriftFromListEndTimeTxt");
			DriftStackTimeDrop.SelectedIndex = Convert.ToInt32(REG.GetReg("CCDLAB", "DriftStackTimeDrop_index"));
			string time = (string)DriftStackTimeDrop.Items[DriftStackTimeDrop.SelectedIndex];
			time = time.Replace(" second stacks", "");
			UVDRIFTSTACKTIME = Convert.ToDouble(time);
		}

		private void DriftFromPCInterpolateChck_Click(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PCDriftInterpChck", DriftFromPCInterpolateChck.Checked);

			if (DriftFromPCInterpolateChck.Checked)
				DriftSmoothNDrop.Enabled = true;
			else
				DriftSmoothNDrop.Enabled = false;

			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromPCMenuItem.ShowDropDown();
		}

		private void DriftStackTimeDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			string time = (string)DriftStackTimeDrop.SelectedItem;
			time = time.Replace(" second stacks", "");
			UVDRIFTSTACKTIME = Convert.ToDouble(time);
			REG.SetReg("CCDLAB", "DriftStackTimeDrop_index", DriftStackTimeDrop.SelectedIndex);
		}

		private void DriftSmoothNDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "DriftSmoothNDrop_index", DriftSmoothNDrop.SelectedIndex);
		}

		private void PointSrcROIStackDriftDrop_SelectedIndexChanged(System.Object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcROIStackDriftDrop_index", PointSrcROIStackDriftDrop.SelectedIndex);
		}

		private void PointSrcROIFindNSrcDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			REG.SetReg("CCDLAB", "PointSrcROIFindNSrcDrop_index", PointSrcROIFindNSrcDrop.SelectedIndex);
		}

		private void CreateDriftFromPCMenuItem_DoubleClick(object sender, EventArgs e)
		{
			uint starttime = 0;
			string startstring = DriftFromListTimeTxt.Text;
			try
			{
				starttime = Convert.ToUInt32(startstring);
			}
			catch
			{
				if (startstring.Length == 0)
					starttime = 0;
				else
				{
					MessageBox.Show("Something wrong with the start time: '" + startstring + "'", "Error...");
					return;
				}
			}

			uint endtime = UInt32.MaxValue;
			string endstring = DriftFromListEndTimeTxt.Text;
			try
			{
				endtime = Convert.ToUInt32(endstring);
			}
			catch
			{
				if (endstring.Length == 0)
					endtime = UInt32.MaxValue;
				else
				{
					MessageBox.Show("Something wrong with the start time: '" + endstring + "'", "Error...");
					return;
				}
			}
			if (endtime < starttime)
			{
				MessageBox.Show("End time can't be less than start time...", "Error...");
				return;
			}

			UVITMenu.HideDropDown();
			CreateDriftListMenuItem.HideDropDown();
			CreateDriftFromPCMenuItem.HideDropDown();

			OpenFileDialog dlg;
			string dir;
			string intslistfile;

			if (!UVDRIFTBATCH)
			{
				dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				dlg = new OpenFileDialog();
				dlg.InitialDirectory = dir;
				dlg.Filter = "FITS (*.fits)|*.fits";
				dlg.Multiselect = true;
				dlg.Title = "Select the Centroid INTEGERS List(s) (_XYInts_List)";
				DialogResult res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;

				intslistfile = dlg.FileNames[0];
				dir = intslistfile.Substring(0, intslistfile.LastIndexOf("\\"));

				UVDRIFTAUTORUN = UVAutoApplyDriftandImageChck.Checked;

				if (dlg.FileNames.Length > 1)//batch, use higher level directory for L1 path
				{
					if (starttime != 0 || endtime != UInt32.MaxValue)
					{
						UVITMenu.ShowDropDown();
						CreateDriftListMenuItem.ShowDropDown();
						CreateDriftFromPCMenuItem.ShowDropDown();
						MessageBox.Show("Doesn't make sense to specify Start and/or End time if doing a batch of files.  I'm going to stop.", "Error...");
						return;
					}
					dir = dir.Substring(0, dir.LastIndexOf("\\"));
					UVDRIFTBATCH = true;
					UVDRIFTAUTORUN = true;
					UVCONVERTLISTTOIMAGEBATCH = false;
					UVAutoApplyDriftandImageChck.Checked = true;
					UVAutoDriftImageViewChck.Checked = false;
					UVDRIFTBATCHFILES = dlg.FileNames;
					UVDRIFTBATCHFILESINDEX = 0;
					AUTOLOADIMAGESFILES = new string[dlg.FileNames.Length];
				}
				REG.SetReg("CCDLAB", "L2EventListPath", dir);
			}
			else
			{
				intslistfile = UVDRIFTBATCHFILES[UVDRIFTBATCHFILESINDEX];
			}

			//ok so now send the filenames and dir to the worker arg, load the fits files and arrays there
			object[] arg = new object[3];
			arg[0] = (object)intslistfile;
			arg[1] = (object)starttime;
			arg[2] = (object)endtime;

			if (UVDRIFTBATCH)
			{
				if (UVDRIFTBATCHFILESINDEX == 0)
				{
					DATE = DateTime.Now;
					this.Enabled = false;
					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = 100;
					WAITBAR.Text = "File " + (UVDRIFTBATCHFILESINDEX + 1).ToString() + " of " + UVDRIFTBATCHFILES.Length + ". Calculating drift...";
					DriftFromPCListWrkr.RunWorkerAsync(arg);
					WAITBAR.ShowDialog();
				}
				else
				{
					WAITBAR.Text = "File " + (UVDRIFTBATCHFILESINDEX + 1).ToString() + " of " + UVDRIFTBATCHFILES.Length + ". Calculating drift...";
					DriftFromPCListWrkr.RunWorkerAsync(arg);
				}
			}
			else
			{
				this.Enabled = false;
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = 100;
				WAITBAR.Text = "File 1 of 1. Calculating drift...";
				DriftFromPCListWrkr.RunWorkerAsync(arg);
				WAITBAR.ShowDialog();
			}
		}

		private void DriftFromPCListWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			object[] arg = (object[])e.Argument;
			string intslistfile = (string)arg[0];
			uint starttime = (uint)arg[1];
			uint endtime = (uint)arg[2];

			FITSImage intslist = new JPFITS.FITSImage(intslistfile, null, true, false, false, false);
			double[,] ints = FITSImage.ReadImageArrayOnly(intslistfile, null, true);

			string fraclistfile = intslistfile.Replace("Ints", "Frac");
			double[,] frac = FITSImage.ReadImageArrayOnly(fraclistfile, null, true);
			ints = JPMath.MatrixAddMatrix(ints, frac, true);
			ints = JPMath.MatrixAddScalar(ints, 16, true);

			string timeslistfile = intslistfile.Remove(intslistfile.IndexOf("XYInts_List")) + "TimeList.fits";
			string deDrift = "_deDrift";
			while (intslistfile.Contains(deDrift))
			{
				timeslistfile = timeslistfile.Replace("TimeList", "TimeList_deDrift");
				deDrift += "_deDrift";
			}
			if (!File.Exists(timeslistfile))
			{
				MessageBox.Show("Error finding the TimeList file...stopping.", "Error");
				return;
			}
			FITSImage timeslist = new FITSImage(timeslistfile, null, true, false, false, false);
			double[] times = FITSImage.ReadImageVectorOnly(timeslistfile, null, true);

			if (starttime == 0)
			{
				starttime = (uint)times[0];
				//auto-skip initial frame with 1000's counts & outside taper active-region
				int ffi = JPMath.Find(times, times[0], ">", true);
				if (ffi > 1000)
					starttime = (uint)times[ffi];
			}
			if (endtime == UInt32.MaxValue)
				endtime = (uint)times[times.Length - 1];

			int imageprec = 0, padoffset = 0;
			if (DriftPCROIOnly.Checked)
			{
				if (IMAGESET == null || IMAGESET.Count == 0)
					DriftPCROIOnly.Checked = false;
				else
				{
					string sprec = IMAGESET[FILELISTINDEX].Header.GetKeyValue("IMAGPREC");
					string offs = IMAGESET[FILELISTINDEX].Header.GetKeyValue("PADOFSET");

					if (sprec == "" || offs == "")
						DriftPCROIOnly.Checked = false;
					else
					{
						imageprec = Convert.ToInt32(sprec);
						padoffset = Convert.ToInt32(offs);
					}
				}
			}

			string xoffset = intslist.Header.GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
			if (xoffset == "")
				xoffset = intslist.Header.GetKeyValue("WIN_XOFF");//from L1 data
			if (xoffset == "")
			{
				MessageBox.Show("Can't find the image x-offset...stopping.", "Error");
				return;
			}
			double ox = Convert.ToDouble(xoffset);//x offset
			if (DriftPCROIOnly.Checked)
				ox = (XSUBRANGE[0] - padoffset * imageprec) / imageprec;

			string yoffset = intslist.Header.GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
			if (yoffset == "")
				yoffset = intslist.Header.GetKeyValue("WIN_YOFF");//from L1 data
			if (yoffset == "")
			{
				MessageBox.Show("Can't find the image y-offset...stopping.", "Error");
				return;
			}
			double oy = Convert.ToDouble(yoffset);//y offset
			if (DriftPCROIOnly.Checked)
				oy = (YSUBRANGE[0] - padoffset * imageprec) / imageprec;

			string sizex = intslist.Header.GetKeyValue("XSIZE");
			if (sizex == "")
				sizex = intslist.Header.GetKeyValue("WIN_X_SZ");
			if (sizex == "")
			{
				MessageBox.Show("Can't find the image x-size...stopping.", "Error");
				return;
			}
			int szx = Convert.ToInt32(sizex);//x size
			if (DriftPCROIOnly.Checked)
				szx = (XSUBRANGE[XSUBRANGE.Length - 1] - XSUBRANGE[0]) / imageprec;

			string sizey = intslist.Header.GetKeyValue("YSIZE");
			if (sizey == "")
				sizey = intslist.Header.GetKeyValue("WIN_Y_SZ");
			if (sizey == "")
			{
				MessageBox.Show("Can't find the image y-size...stopping.", "Error");
				return;
			}
			int szy = Convert.ToInt32(sizey);//y size
			if (DriftPCROIOnly.Checked)
				szy = (YSUBRANGE[YSUBRANGE.Length - 1] - YSUBRANGE[0]) / imageprec;

			int prec = 1;
			szx = (szx + 1) * prec;
			szy = (szy + 1) * prec;

			uint dt = (uint)(UVDRIFTSTACKTIME * 1000);
			int Ndrifttimes = (int)((endtime - starttime) / dt);
			endtime = starttime + (uint)Ndrifttimes * dt;
			double[] tdr = new double[Ndrifttimes];
			double[] xdr = new double[Ndrifttimes];
			double[] ydr = new double[Ndrifttimes];
			int[] stackinds = new int[Ndrifttimes + 1];
			stackinds[0] = JPMath.Find(times, starttime, "==", true);
			for (int i = 1; i <= Ndrifttimes; i++)
				for (int j = stackinds[i - 1]; j < times.Length; j++)
					if (times[j] > times[stackinds[0]] + (double)(dt) * (double)(i))
					{
						stackinds[i] = j;
						break;
					}

			double[,] REFimg = new double[szx, szy];
			for (int i = stackinds[0]; i < stackinds[1]; i++)
			{
				int xpos = (int)((ints[0, i] - ox * 32) / 32);
				int ypos = (int)((ints[1, i] - oy * 32) / 32);

				if (xpos >= 0 && ypos >= 0 && xpos < szx && ypos < szy)
					REFimg[xpos, ypos]++;
			}
			for (int x = 0; x < szx; x++)
				for (int y = 0; y < szy; y++)
					if (REFimg[x, y] == 1)
						REFimg[x, y] = 0;//remove noise
			REFimg = JPMath.Hanning(REFimg, true);
			double[] REFimgvecX = JPMath.Sum(REFimg, 1, true);
			double[] REFimgvecY = JPMath.Sum(REFimg, 0, true);
			tdr[0] = (double)(starttime) + UVDRIFTSTACKTIME * 1000 / 2;//xdr, ydr = 0

			int prog = 0;

			Parallel.For(1, Ndrifttimes, (i, loopstate) =>
			//for (int i = 1; i < Ndrifttimes; i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					loopstate.Stop();// continue;

				if (i < Ndrifttimes / Environment.ProcessorCount /*/ omp_get_num_threads()*/)
					if (Environment.ProcessorCount * 100 * i / Ndrifttimes > prog)
					{
						prog = Environment.ProcessorCount * 100 * i / Ndrifttimes;
						DriftFromPCListWrkr.ReportProgress(prog);
					}

				double[,] COMimg = new double[szx, szy];
				for (int j = stackinds[i]; j < stackinds[i + 1]; j++)
				{
					int xpos = (int)((ints[0, j] - ox * 32) / 32);
					int ypos = (int)((ints[1, j] - oy * 32) / 32);

					if (xpos >= 0 && ypos >= 0 && xpos < szx && ypos < szy)
						COMimg[xpos, ypos]++;
				}
				for (int x = 0; x < szx; x++)
					for (int y = 0; y < szy; y++)
						if (COMimg[x, y] == 1)
							COMimg[x, y] = 0;//remove noise
				COMimg = JPMath.Hanning(COMimg, false);

				double xshift, yshift;
				JPMath.XCorrImageLagShifts(REFimgvecX, REFimgvecY, COMimg, false, false, false, out xshift, out yshift, false);

				tdr[i] = times[stackinds[i]] + (double)(UVDRIFTSTACKTIME * 1000) / 2;
				xdr[i] = xshift * 32;
				ydr[i] = yshift * 32;
			});

			if (WAITBAR.DialogResult == DialogResult.Cancel)
				return;

			//correct strange large spikes???.......PC mode here
			for (int i = 2; i < tdr.Length; i++)
			{
				double dxdt = (xdr[i] - xdr[i - 1]) / UVDRIFTSTACKTIME / 32;//pixels per second
				if (Math.Abs(dxdt) > 5)
				{
					dxdt = (xdr[i - 1] - xdr[i - 2]) / UVDRIFTSTACKTIME;
					xdr[i] = xdr[i - 1] + dxdt * (tdr[i] - tdr[i - 1]) / 1000;
				}
				double dydt = (ydr[i] - ydr[i - 1]) / UVDRIFTSTACKTIME / 32;//pixels per second
				if (Math.Abs(dydt) > 5)
				{
					dydt = (ydr[i - 1] - ydr[i - 2]) / UVDRIFTSTACKTIME;
					ydr[i] = ydr[i - 1] + dydt * (tdr[i] - tdr[i - 1]) / 1000;
				}
			}
			//done correction

			xdr = JPMath.VectorSubScalar(xdr, JPMath.Mean(xdr, true), true);
			ydr = JPMath.VectorSubScalar(ydr, JPMath.Mean(ydr, true), true);
			bool smooth = DriftFromPCInterpolateChck.Checked;
			int interpN = 0;
			if (smooth)
			{
				interpN = DriftSmoothNDrop.SelectedIndex;
				if (interpN < 0)
					interpN = 3;
				else
					interpN = 3 + interpN * 2;

				xdr = JPMath.Smooth(xdr, interpN, true, "centered");
				ydr = JPMath.Smooth(ydr, interpN, true, "centered");
			}

			double[] tdrinterp = new double[stackinds[stackinds.Length - 1] - stackinds[0] + 1];
			double[] xdrinterp = new double[stackinds[stackinds.Length - 1] - stackinds[0] + 1];
			double[] ydrinterp = new double[stackinds[stackinds.Length - 1] - stackinds[0] + 1];
			
			for (int i = 0; i < tdrinterp.Length; i++)
				tdrinterp[i] = times[stackinds[0] + i];
			xdrinterp = JPMath.Interpolate1d(tdr, xdr, tdrinterp, "mono", true);
			ydrinterp = JPMath.Interpolate1d(tdr, ydr, tdrinterp, "mono", true);

			double[,] xyshiftsLIST = new double[3, tdrinterp.Length];
			for (int i = 0; i < tdrinterp.Length; i++)
			{
				xyshiftsLIST[0, i] = tdrinterp[i];
				xyshiftsLIST[1, i] = Math.Round(xdrinterp[i]);
				xyshiftsLIST[2, i] = Math.Round(ydrinterp[i]);
			}

			string driftslistfile;
			if (smooth)
				driftslistfile = intslistfile.Replace("XYInts_List", "XYDrift_List" + "_" + UVDRIFTSTACKTIME.ToString() + "s" + "_Sm" + interpN.ToString());
			else
				driftslistfile = intslistfile.Replace("XYInts_List", "XYDrift_List" + "_" + UVDRIFTSTACKTIME.ToString() + "s");
			driftslistfile = driftslistfile.Replace(".fits", ".drift");

			//get pre-existing earlier iteration dedrifted lists and drift series and delete them
			//this is to keep things cleaner like for creating exposure array from multiple drifts if a drift series is re-calculated from an earlier iteration
			//if redoing an earlier iteration its probably because the later ones were no good anyway
			string dedrift = "_deDrift";
			while (intslistfile.Contains(dedrift))
				dedrift += "_deDrift";
			string[] delfiles = Directory.GetFiles(intslistfile.Substring(0, intslistfile.LastIndexOf("\\")), "*" + dedrift + "*");
			for (int i = 0; i < delfiles.Length; i++)
				File.Delete(delfiles[i]);
			dedrift = dedrift.Remove(0, 8);
			delfiles = Directory.GetFiles(intslistfile.Substring(0, intslistfile.LastIndexOf("\\")), "*" + dedrift + ".drift");
			for (int i = 0; i < delfiles.Length; i++)
				File.Delete(delfiles[i]);

			FITSImage driftfits = new FITSImage(driftslistfile, xyshiftsLIST, false, true);
			driftfits.Header.CopyHeaderFrom(timeslist.Header);// CopyHeader(timeslist);
			driftfits.WriteImage(TypeCode.Double, true);
			UVPLOTDRIFTFILENAME = driftslistfile;
			UVAPPLYDRIFTCENTROIDSFILENAME = intslistfile;

			/*FITSImage ff = new FITSImage(driftslistfile + "test");
			ff.CopyHeader(timeslist);
			ff.WriteImage(TypeCode.Int16);
			array<String^> labels = new array<String^>(3) {"Time", "XDrift", "YDrift"};
			array<TypeCode> types = new array<TypeCode>(3) {TypeCode.UInt32, TypeCode.Int16, TypeCode.Int16};
			int[] instances = new int[3) { 1, 1, 1 };
			array<String^> units = new array<String^>(3) { "Milliseconds", "1/32 pixel", "1/32 pixel" };
			JPFITS.FITSImage.WriteBinaryTableExtension(driftslistfile + "test", "DriftList", true, labels, types, instances, units, null, null, null, xyshiftsLIST);*/
			/*try
			{
				array<double, 2> test = JPFITS.FITSImage.ReadBinaryTableExtensionEntries(driftslistfile + "test", "DriftList", new array<String^>(3) { "Time", "XDrift", "YDrift" });
				for (int i = 0; i < test.GetLength(1); i++)
					MessageBox.Show(test[0, i] + " " + test[1, i] + " " + test[2, i]);
			}
			catch (Exception e)
			{
				MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
			}*/
		}

		private void DriftFromPCListWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = String.Concat("Completed: ", e.ProgressPercentage, "%");
			WAITBAR.Refresh();
		}

		private void DriftFromPCListWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult != DialogResult.Cancel)
			{
				if (!UVDRIFTAUTORUN)
				{
					DialogResult res = MessageBox.Show("Completed making the drift correction list.  Would you like to plot it?", "Finished...", MessageBoxButtons.OKCancel);
					if (res == DialogResult.Cancel)
					{
						WAITBAR.Hide();
						WAITBAR.Close();
						this.Enabled = true;
						this.BringToFront();
						return;
					}
					if (res == DialogResult.OK)
					{
						UVPLOTDRIFTLISTNOW = true;
						PlotDriftListMenuItem.PerformClick();
					}
					res = MessageBox.Show("Would you like to apply this drift calculation to the centroid list?", "Apply drift...", MessageBoxButtons.OKCancel);
					if (res == DialogResult.Cancel)
					{
						WAITBAR.Hide();
						WAITBAR.Close();
						this.Enabled = true;
						this.BringToFront();
						return;
					}
					if (res == DialogResult.OK)
					{
						XDRIFT_PLOT.Close();
						YDRIFT_PLOT.Close();
						UVAPPLYDRIFTNOW = true;
						PCModeDriftSelfCorrectionMenuItem.PerformClick();//is ApplyDriftListMentuItem_Click
					}
				}
				else
				{
					WAITBAR.Text = "Applying...";
					WAITBAR.TextMsg.Text = "Applying drift to centroid list...";
					WAITBAR.CancelBtn.Enabled = false;
					WAITBAR.Refresh();
					UVAPPLYDRIFTNOW = true;
					PCModeDriftSelfCorrectionMenuItem.PerformClick();//is ApplyDriftListMentuItem_Click 
				}
			}
			else
			{
				UVAPPLYDRIFTNOW = false;
				UVDRIFTBATCH = false;
				WAITBAR.Hide();
				WAITBAR.Close();
				this.Enabled = true;
				this.BringToFront();
			}
		}

		private void ApplyDriftListMentuItem_Click(System.Object sender, EventArgs e)
		{
			string driftlistfile;

			OpenFileDialog dlg;
			if (UVAPPLYDRIFTNOW)
			{
				//UVAPPLYDRIFTNOW = false;//done below in worker
				driftlistfile = UVPLOTDRIFTFILENAME;
				WAITBAR.ProgressBar.Value = 100;
				WAITBAR.Refresh();
				ApplyDriftListWrkr.RunWorkerAsync(driftlistfile);
			}
			else
			{
				UVAPPLYDRIFTNOW = false;
				string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				dlg = new OpenFileDialog();
				dlg.InitialDirectory = dir;
				dlg.Filter = "FITS (*.fits)|*.fits";
				dlg.Multiselect = false;

				dlg.Title = "Select the DRIFT List (_XYDrift_List)";
				dlg.Filter = "DRIFT (*.drift)|*.drift";
				DialogResult res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;
				driftlistfile = dlg.FileName;
				dir = driftlistfile.Substring(0, driftlistfile.LastIndexOf("\\"));
				REG.SetReg("CCDLAB", "L2EventListPath", dir);

				dlg = new OpenFileDialog();
				dlg.Title = "Select the Centroid INTEGERS List (_XYInts_List)";
				dlg.Filter = "FITS (*.fits)|*.fits";
				dlg.InitialDirectory = dir;
				dlg.Multiselect = false;
				res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;
				UVAPPLYDRIFTCENTROIDSFILENAME = dlg.FileName;

				WAITBAR = new WaitBar();
				WAITBAR.Text = "Applying Drift";
				WAITBAR.TextMsg.Text = "Please wait...";
				WAITBAR.CancelBtn.Enabled = false;
				ApplyDriftListWrkr.RunWorkerAsync(driftlistfile);
				WAITBAR.ShowDialog();
			}
		}

		private void ApplyDriftListWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			//try
			{
				if (UVAPPLYDRIFTNOW)
					UVAPPLYDRIFTNOW = false;

				string driftlistfile = (string)e.Argument;

				FITSImage driftsfits = new JPFITS.FITSImage(driftlistfile, null, true, false, false, false);
				double[,] drifts = FITSImage.ReadImageArrayOnly(driftlistfile, null, true);

				string timelistfile = driftlistfile.Remove(driftlistfile.IndexOf("XYDrift")) + "TimeList.fits";
				string deDrift = "_deDrift";
				while (driftlistfile.Contains(deDrift))
				{
					timelistfile = timelistfile.Replace("TimeList", "TimeList_deDrift");
					deDrift += "_deDrift";
				}

				if (!File.Exists(timelistfile))
				{
					MessageBox.Show("Time List not found.  Error & exiting...");
					WAITBAR.CancelBtn.PerformClick();
					return;
				}
				double[] times = FITSImage.ReadImageVectorOnly(timelistfile, null, true);

				string framelistfile = timelistfile.Replace("Time", "Frame");
				if (!File.Exists(framelistfile))
				{
					MessageBox.Show("Frame List not found.  Error & exiting...");
					WAITBAR.CancelBtn.PerformClick();
					return;
				}
				double[] frames = FITSImage.ReadImageVectorOnly(framelistfile, null, true);

				string flatlistfile = timelistfile.Replace("Time", "Flat");
				if (!File.Exists(flatlistfile))
				{
					MessageBox.Show("Flat Field List not found.  Error & exiting...");
					WAITBAR.CancelBtn.PerformClick();
					return;
				}
				double[] flats = FITSImage.ReadImageVectorOnly(flatlistfile, null, true);

				string mdMmlistfile = timelistfile.Replace("TimeList", "XYmdMm_List");
				if (!File.Exists(mdMmlistfile))
				{
					MessageBox.Show("Max Min Corners List not found.  Error & exiting...");
					WAITBAR.CancelBtn.PerformClick();
					return;
				}
				double[,] mdMms = FITSImage.ReadImageArrayOnly(mdMmlistfile, null, true);

				string BJDlistfile = timelistfile.Replace("TimeList", "BJDList");
				bool BJDexists = true;
				if (!File.Exists(BJDlistfile))
				{
					BJDexists = false;
					/*MessageBox.Show("BJDList Time List not found.  Error & exiting...");
					WAITBAR.CancelBtn.PerformClick();
					return;*/
				}
				double[] BJDS = null;
				if (BJDexists)
					BJDS = FITSImage.ReadImageVectorOnly(BJDlistfile, null, true);

				string intslistfile = UVAPPLYDRIFTCENTROIDSFILENAME;
				double[,] ints = FITSImage.ReadImageArrayOnly(intslistfile, null, true);

				string fraclistfile = intslistfile.Replace("Ints", "Frac");
				double[,] frac = FITSImage.ReadImageArrayOnly(fraclistfile, null, true);
				FITSImage fracfits = new FITSImage(fraclistfile, null, true, false, false, false);
				bool nuvTOfuv = false;
				if (fracfits.Header.GetKeyValue("DETECTOR") == "NUV")
					if (fracfits.Header.GetKeyIndex("NUVTOFUV", false) != -1)
						nuvTOfuv = true;

				//make exposure array
				bool createexposurearray = ApplyDriftCreateExpArrayChc.Checked;
				//when working on merged MASTER file {OR PREVIOUSLY DRIFTED FILE}, drift will be so small as to not change the exposure array,
				//so just update the existing merged expsoure array to be same dimension as the new dedrifted lists and name it as such.
				//So here, don't create a new expsoure list, just use the existing merged master one and clip it to match the other lists.
				bool master = intslistfile.Contains("MASTER") || intslistfile.Contains("deDrift");
				if (master)
					createexposurearray = false;

				int res = ExposureArrayResolutionDrop.SelectedIndex + 1;
				double dres = (double)(res);
				double pixres = 32 / dres;
				if (L1CentroidPaddingChck.Checked)
				{
					if (PCCentroidPaddingDrop.SelectedIndex == 0)
						UVPCMODEPADOFFSET = 22;
					if (PCCentroidPaddingDrop.SelectedIndex == 1)
						UVPCMODEPADOFFSET = 44;
				}
				else
					UVPCMODEPADOFFSET = 0;
				int offset = UVPCMODEPADOFFSET * res;

				int winxsz, szx, winysz, szy, ox, oy;
				try
				{
					winxsz = Convert.ToInt32(driftsfits.Header.GetKeyValue("WIN_X_SZ"));
					szx = (winxsz + 1) * res + offset * 2;
					winysz = Convert.ToInt32(driftsfits.Header.GetKeyValue("WIN_Y_SZ"));
					szy = (winysz + 1) * res + offset * 2;
					ox = Convert.ToInt32(driftsfits.Header.GetKeyValue("WIN_XOFF"));
					oy = Convert.ToInt32(driftsfits.Header.GetKeyValue("WIN_YOFF"));
				}
				catch
				{
					winxsz = 511;
					szx = (winxsz + 1) * res + offset * 2;
					winysz = 511;
					szy = (winysz + 1) * res + offset * 2;
					ox = 0;
					oy = 0;
				}

				double nframes = 0;
				double[,] exposuremap = null;
				double[,] exposuredrifts = null;
				double[,] exposurearray = null;
				if (createexposurearray)
				{
					ApplyDriftListWrkr.ReportProgress(0);

					//need to check for existing exposure arrays and ...do what with them...
					//in order to create a final _dedrfit_dedrift_etc one...
					//what should be done, then, is to check for existing drift series
					//this assumes that all drift series in the directory are relevent to the current iteration

					//this assumption disrupts re-performing the dift series on an earlier iteration of corrected files from which you wish to start again
					//so you should only use the drift series that are from an earlier time than the current file time...

					//So, get the drift series in the directory, and sum them (xy, not time vector).  Create the exposure array from that.
					//However, that summed series is only for the exposure array, NOT for the current drift correction
					//The current drift correction is only for the current "drifts" series.
					//So, use a new drifts series, called Exparray drift or something...
					//The most recent drift series will be the shortest one

					//*********should also check the t0 index if the drifts dont start at same time???...*********

					exposurearray = new double[szx, szy];

					exposuredrifts = new double[driftsfits.Width, driftsfits.Height];
					double[,] prevdrifts;
					//this gets all drifts *including current one, so should always be at least one for the j loop below
					string[] prevdriftslists = Directory.GetFiles(timelistfile.Substring(0, timelistfile.LastIndexOf("\\")), "*.drift");
					for (int j = 0; j < prevdriftslists.Length; j++)
					{
						prevdrifts = FITSImage.ReadImageArrayOnly(prevdriftslists[j], null, true);

						Parallel.For(0, driftsfits.Height, i =>
						{
							exposuredrifts[0, i] = prevdrifts[0, i];
							exposuredrifts[1, i] += prevdrifts[1, i];
							exposuredrifts[2, i] += prevdrifts[2, i];
						});
					}

					string detector = driftsfits.Header.GetKeyValue("DETECTOR");
					string FUVexpmapfile = "";
					string NUVexpmapfile = "";
					if (res == 1)
					{
						FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map.fits";
						NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map.fits";
						if (nuvTOfuv)
							NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map_NUVtoFUV.fits";
					}
					if (res == 2)
					{
						FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map x2.fits";
						NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2.fits";
						if (nuvTOfuv)
							NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2_NUVtoFUV.fits";
					}
					if (detector == "FUV")
					{
						if (!File.Exists(FUVexpmapfile))
						{
							MessageBox.Show("FUV Exposure Map not found in UVIT_CalDB at " + FUVexpmapfile + ".  Please update your Cal_DB from http://www.ucalgary.ca/uvit/.  Exiting.", "Error...");
							WAITBAR.CancelBtn.PerformClick();
							return;
						}
						if (winxsz == 511 && winysz == 511)
						{
							if (UVPCMODEPADOFFSET == 44)
								exposuremap = FITSImage.ReadImageArrayOnly(FUVexpmapfile, new int[] { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
							if (UVPCMODEPADOFFSET == 22)
								exposuremap = FITSImage.ReadImageArrayOnly(FUVexpmapfile, new int[] { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
							if (UVPCMODEPADOFFSET == 0)
								exposuremap = FITSImage.ReadImageArrayOnly(FUVexpmapfile, new int[] { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
						}
						else
						{
							exposuremap = new double[szx, szy];
							Parallel.For(UVPCMODEPADOFFSET * res, szx - UVPCMODEPADOFFSET * res, x =>
							{
								for (int y = UVPCMODEPADOFFSET * res; y < szy - UVPCMODEPADOFFSET * res; y++)
									exposuremap[x, y] = 1;
							});
						}
					}
					else if (detector == "NUV")
					{
						if (!File.Exists(NUVexpmapfile))
						{
							MessageBox.Show("NUV Exposure Map not found in UVIT_CalDB at " + NUVexpmapfile + ".  Please update your Cal_DB from http://www.ucalgary.ca/uvit/.  Exiting.", "Error...");
							WAITBAR.CancelBtn.PerformClick();
							return;
						}
						if (winxsz == 511 && winysz == 511)
						{
							if (UVPCMODEPADOFFSET == 44)
								exposuremap = FITSImage.ReadImageArrayOnly(NUVexpmapfile, new int[] { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
							if (UVPCMODEPADOFFSET == 22)
								exposuremap = FITSImage.ReadImageArrayOnly(NUVexpmapfile, new int[] { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
							if (UVPCMODEPADOFFSET == 0)
								exposuremap = FITSImage.ReadImageArrayOnly(NUVexpmapfile, new int[] { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
						}
						else
						{
							exposuremap = new double[szx, szy];
							Parallel.For(UVPCMODEPADOFFSET * res, szx - UVPCMODEPADOFFSET * res, x =>
							{
								for (int y = UVPCMODEPADOFFSET * res; y < szy - UVPCMODEPADOFFSET * res; y++)
									exposuremap[x, y] = 1;
							});
						}
					}
					else
					{
						MessageBox.Show("Problem determining the correct Exposure Map for the exposure array...", "Error...");
						WAITBAR.CancelBtn.PerformClick();
						return;
					}

					int xstart, xend, ystart, yend, expxstart, expystart;
					exposuredrifts[1, 0] *= -1;
					exposuredrifts[2, 0] *= -1;
					double oldxdrift = exposuredrifts[1, 0];
					double oldydrift = exposuredrifts[2, 0];
					if (exposuredrifts[1, 0] < 0)
					{
						xstart = -(int)(exposuredrifts[1, 0] / pixres);
						xend = szx;
						expxstart = 0;
					}
					else
					{
						xstart = 0;
						xend = szx - (int)(exposuredrifts[1, 0] / pixres);
						expxstart = (int)(exposuredrifts[1, 0] / pixres);
					}
					if (exposuredrifts[2, 0] < 0)
					{
						ystart = -(int)(exposuredrifts[2, 0] / pixres);
						yend = szy;
						expystart = 0;
					}
					else
					{
						ystart = 0;
						yend = szy - (int)(exposuredrifts[2, 0] / pixres);
						expystart = (int)(exposuredrifts[2, 0] / pixres);
					}
					exposuredrifts[1, 0] *= -1;
					exposuredrifts[2, 0] *= -1;

					int intprog = 0;
					double increment = 0;
					double time = -1;
					for (int i = 0; i < driftsfits.Height; i++)
					{
						if (time != exposuredrifts[0, i])//new drift frame time...possibly new drift...also very first frame
						{
							if (100 * i / driftsfits.Height > intprog)
							{
								intprog += 1;
								ApplyDriftListWrkr.ReportProgress(0, intprog);
							}

							time = exposuredrifts[0, i];
							nframes++;

							exposuredrifts[1, i] *= -1;
							exposuredrifts[2, i] *= -1;

							//if it isnt moving then just gather the increments to apply after it does move
							//and it only needs to be applied after it moves by at least one pixel (or res?)
							if (Math.Abs(exposuredrifts[1, i] - oldxdrift) < pixres && Math.Abs(exposuredrifts[2, i] - oldydrift) < pixres)//will trigger for first frame so increment goes to 1 for it
							{
								increment++;//this starts at zero, so if this is the first frame, we get the first increment = 1
								exposuredrifts[1, i] *= -1;//reset
								exposuredrifts[2, i] *= -1;
								continue;
							}

							//then it has moved, so increment out everything from when it wasn't moving at the old positions
							Parallel.For(xstart, xend, x =>
							{
								for (int y = ystart; y < yend; y++)
									if (exposuremap[x, y] == 1)
										exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;
							});

							increment = 1;//increment for current frame

							//update moved position stuff...at least one of the drifts is moved 32 or more...update that one or both only
							if (Math.Abs(exposuredrifts[1, i] - oldxdrift) >= pixres)
							{
								oldxdrift = exposuredrifts[1, i];
								if (exposuredrifts[1, i] < 0)
								{
									xstart = -(int)(exposuredrifts[1, i] / pixres);
									xend = szx;
									expxstart = 0;
								}
								else
								{
									xstart = 0;
									xend = szx - (int)(exposuredrifts[1, i] / pixres);
									expxstart = (int)(exposuredrifts[1, i] / pixres);
								}
							}

							if (Math.Abs(exposuredrifts[2, i] - oldydrift) >= pixres)
							{
								oldydrift = exposuredrifts[2, i];
								if (exposuredrifts[2, i] < 0)
								{
									ystart = -(int)(exposuredrifts[2, i] / pixres);
									yend = szy;
									expystart = 0;
								}
								else
								{
									ystart = 0;
									yend = szy - (int)(exposuredrifts[2, i] / pixres);
									expystart = (int)(exposuredrifts[2, i] / pixres);
								}
							}

							exposuredrifts[1, i] *= -1;//reset
							exposuredrifts[2, i] *= -1;
						}
					}
					//increment out last gathered increments

					Parallel.For(xstart, xend, x =>
					{
						for (int y = ystart; y < yend; y++)
							if (exposuremap[x, y] == 1)
								exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;
					});

					//lastly normalize the array...
					exposurearray = JPMath.MatrixDivScalar(exposurearray, nframes, true);

					driftsfits.Header.SetKey("EXMAPRES", res.ToString(), "Exposure Map Resolution", true, 15);
					driftsfits.Header.SetKey("EXMAPTIM", (exposuredrifts[0, exposuredrifts.GetLength(1) - 1] - exposuredrifts[0, 0]).ToString(), "Exposure Map Time", true, 15);
				}

				ApplyDriftListWrkr.ReportProgress(1);

				//so now use the times from drifts to align on the time from times, and apply onto new ints array and save that array
				double t0 = drifts[0, 0];
				int t0index = JPMath.Find(times, t0, "==", true);

				//MessageBox.Show(t0.ToString() + "	" + t0index.ToString());
				//MessageBox.Show(t0.ToString() + "	" + t0index.ToString() + "   " + times[t0index].ToString());

				//will need dedrifted ints and fracs so they align...
				double[,] dedriftedXYInts = new double[2, driftsfits.Height];
				double[,] dedriftedXYFrac = new double[2, driftsfits.Height];
				double[] dedriftedFlat = new double[driftsfits.Height];
				double[] dedriftedTime = new double[driftsfits.Height];
				double[] dedriftedFrame = new double[driftsfits.Height];
				double[,] dedriftedXYmdMm = new double[2, driftsfits.Height];
				double[] dedriftedBJD = null;
				if (BJDexists)
					dedriftedBJD = new double[driftsfits.Height];
				double[] dedriftedExposure = null;
				if (createexposurearray)
					dedriftedExposure = new double[driftsfits.Height];
				if (master)
					dedriftedExposure = FITSImage.ReadImageVectorOnly(timelistfile.Replace("TimeList", "ExpArrayList"), new int[] { 0, 0, 0, driftsfits.Height - 1 }, true);

				//int counter1 = 0;
				Parallel.For(0, driftsfits.Height, i =>
				//for (int i = 0; i < driftsfits.Height; i++)
				{
					dedriftedXYInts[0, i] = ints[0, t0index + i] - drifts[1, i];
					dedriftedXYInts[1, i] = ints[1, t0index + i] - drifts[2, i];

					dedriftedXYFrac[0, i] = frac[0, t0index + i];
					dedriftedXYFrac[1, i] = frac[1, t0index + i];

					dedriftedFlat[i] = flats[t0index + i];
					dedriftedTime[i] = times[t0index + i];
					dedriftedFrame[i] = frames[t0index + i];

					dedriftedXYmdMm[0, i] = mdMms[0, t0index + i];
					dedriftedXYmdMm[1, i] = mdMms[1, t0index + i];

					if (BJDexists)
						dedriftedBJD[i] = BJDS[t0index + i];

					if (createexposurearray)
					{
						int xpos = (int)(dedriftedXYInts[0, i] / pixres) + offset - ox * res;
						int ypos = (int)(dedriftedXYInts[1, i] / pixres) + offset - oy * res;
						if (xpos < 0 || ypos < 0 || xpos >= szx || ypos >= szy)
							dedriftedExposure[i] = 0;
						else
							dedriftedExposure[i] = exposurearray[xpos, ypos];//applied like the flat...take the inverse at image creation time
					}
				});

				ApplyDriftListWrkr.ReportProgress(2);

				//then save the dedrifted lists
				if (BJDexists)
					driftsfits.Header.SetKey("BJD0", dedriftedBJD[0].ToString("#.0000000"), "BJD of start of imaging", true, 14);//now it will get added to all other copyheaders's

				int ind = intslistfile.LastIndexOf("_deDrift");
				if (ind == -1)
					ind = intslistfile.LastIndexOf(".");
				string dedriftedXYIntsFile = intslistfile.Insert(ind, "_deDrift");
				FITSImage dedriftedXYIntsFits = new FITSImage(dedriftedXYIntsFile, dedriftedXYInts, false, true);
				dedriftedXYIntsFits.Header.CopyHeaderFrom(driftsfits.Header);
				dedriftedXYIntsFits.WriteImage(TypeCode.Int16, true);

				ind = fraclistfile.LastIndexOf("_deDrift");
				if (ind == -1)
					ind = fraclistfile.LastIndexOf(".");
				string dedriftedXYFracFile = fraclistfile.Insert(ind, "_deDrift");
				FITSImage dedriftedXYFracFits = new FITSImage(dedriftedXYFracFile, dedriftedXYFrac, false, true);
				dedriftedXYFracFits.Header.CopyHeaderFrom(driftsfits.Header);
				dedriftedXYFracFits.WriteImage(TypeCode.Int16, true);

				ind = flatlistfile.LastIndexOf("_deDrift");
				if (ind == -1)
					ind = flatlistfile.LastIndexOf(".");
				string dedriftedFlatFile = flatlistfile.Insert(ind, "_deDrift");
				FITSImage dedriftedFlatFits = new FITSImage(dedriftedFlatFile, dedriftedFlat, false, true);
				dedriftedFlatFits.Header.CopyHeaderFrom(driftsfits.Header);
				dedriftedFlatFits.WriteImage(TypeCode.Double, true);

				ind = timelistfile.LastIndexOf("_deDrift");
				if (ind == -1)
					ind = timelistfile.LastIndexOf(".");
				string dedriftedTimeFile = timelistfile.Insert(ind, "_deDrift");
				FITSImage dedriftedTimeFits = new FITSImage(dedriftedTimeFile, dedriftedTime, false, true);
				dedriftedTimeFits.Header.CopyHeaderFrom(driftsfits.Header);
				dedriftedTimeFits.WriteImage(TypeCode.UInt32, true);

				ind = framelistfile.LastIndexOf("_deDrift");
				if (ind == -1)
					ind = framelistfile.LastIndexOf(".");
				string dedriftedFrameFile = framelistfile.Insert(ind, "_deDrift");
				FITSImage dedriftedFrameFits = new FITSImage(dedriftedFrameFile, dedriftedFrame, false, true);
				dedriftedFrameFits.Header.CopyHeaderFrom(driftsfits.Header);
				dedriftedFrameFits.WriteImage(TypeCode.UInt32, true);

				ind = mdMmlistfile.LastIndexOf("_deDrift");
				if (ind == -1)
					ind = mdMmlistfile.LastIndexOf(".");
				string dedriftedXYmdMmFile = mdMmlistfile.Insert(ind, "_deDrift");
				FITSImage dedriftedXYmdMmFits = new FITSImage(dedriftedXYmdMmFile, dedriftedXYmdMm, false, true);
				dedriftedXYmdMmFits.Header.CopyHeaderFrom(driftsfits.Header);
				dedriftedXYmdMmFits.WriteImage(TypeCode.Int16, true);

				if (BJDexists)
				{
					ind = BJDlistfile.LastIndexOf("_deDrift");
					if (ind == -1)
						ind = BJDlistfile.LastIndexOf(".");
					string dedriftedBJDFile = BJDlistfile.Insert(ind, "_deDrift");
					FITSImage dedriftedBJDFits = new FITSImage(dedriftedBJDFile, dedriftedBJD, false, true);
					dedriftedBJDFits.Header.CopyHeaderFrom(driftsfits.Header);
					dedriftedBJDFits.WriteImage(TypeCode.Double, true);
				}

				if (createexposurearray || master)
				{
					string dedriftedExpFile = dedriftedTimeFile.Replace("TimeList", "ExpArrayList");
					FITSImage dedriftedExpFits = new FITSImage(dedriftedExpFile, dedriftedExposure, false, true);
					dedriftedExpFits.Header.CopyHeaderFrom(driftsfits.Header);
					dedriftedExpFits.WriteImage(TypeCode.Double, true);

					//if (createexposurearray)
					{
						dedriftedExpFile = dedriftedExpFile.Replace("ExpArrayList", "ExpArrayImg");
						if (master)
							exposurearray = JPFITS.FITSImage.ReadImageArrayOnly(dedriftedExpFile.Replace("_deDrift.fits", ".fits"), null, true);
						FITSImage exp = new FITSImage(dedriftedExpFile, exposurearray, false, true);
						exp.Header.CopyHeaderFrom(driftsfits.Header);
						exp.WriteImage(TypeCode.Double, true);
					}
				}

				UVCREATEIMAGEFILENAME = dedriftedXYIntsFile;

				if (UVDRIFTAUTORUN)
				{
					ApplyDriftListWrkr.ReportProgress(3);
				}
			}
			/*catch (Exception e)
			{
				MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
			}*/
		}

		private void ApplyDriftListWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			if (e.ProgressPercentage == 0)
			{
				WAITBAR.ProgressBar.Maximum = 100;
				WAITBAR.Text = "Exposure Array...";
				WAITBAR.TextMsg.Text = "Creating exposure array...please wait...";
				WAITBAR.ProgressBar.Value = Convert.ToInt32(e.UserState);
				WAITBAR.Refresh();
			}

			if (e.ProgressPercentage == 1)
			{
				WAITBAR.Text = "Applying...";
				WAITBAR.TextMsg.Text = "Applying drift...";
				WAITBAR.Refresh();
			}

			if (e.ProgressPercentage == 2)
			{
				WAITBAR.Text = "Saving...";
				WAITBAR.TextMsg.Text = "Saving de-drifted lists...";
				WAITBAR.Refresh();
			}

			if (e.ProgressPercentage == 3)
			{
				WAITBAR.Text = "Image...";
				WAITBAR.TextMsg.Text = "Creating image...";
				WAITBAR.Refresh();
			}
		}

		private void ApplyDriftListWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				this.Enabled = true;
				this.BringToFront();
				return;
			}

			if (!UVDRIFTAUTORUN)
			{
				WAITBAR.Hide();
				WAITBAR.Close();
				this.BringToFront();
				DialogResult res = MessageBox.Show("Completed applying the drift correction. Would you like to create the image using current image settings?", "Finished...", MessageBoxButtons.YesNo);
				if (res == DialogResult.No)
				{
					this.Enabled = true;
					this.BringToFront();
					return;
				}
				if (res == DialogResult.Yes)
				{
					UVCREATEIMAGENOW = true;
					ConvertListToImgMenu_DropDownOpened(sender, e);
					ConvertListToImgMenu.HideDropDown();
					ConvertListToImgMenu_Click(sender, e);
				}
			}
			else
			{
				UVCREATEIMAGENOW = true;
				ConvertListToImgMenu_DropDownOpened(sender, e);
				ConvertListToImgMenu.HideDropDown();
				ConvertListToImgMenu_Click(sender, e);
			}
		}

		private void PlotCountsPerFrameMenuItem_Click(System.Object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = false;

			dlg.Title = "Select the FRAME List (_FrameList)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;
			string framelistfile = dlg.FileName;
			dir = framelistfile.Substring(0, framelistfile.LastIndexOf("\\"));
			REG.SetReg("CCDLAB", "L2EventListPath", dir);
			FITSImage framefits = new JPFITS.FITSImage(framelistfile, null, true, false, false, false);
			double[] frames = FITSImage.ReadImageVectorOnly(framelistfile, null, true);

			int nframes = (int)(frames[frames.Length - 1] - frames[0] + 1);

			double[] plotframes = new double[nframes];
			double[] plotcounts = new double[nframes];

			int curr_frame = -1;

			for (int i = 0; i < frames.Length; i++)
				if (curr_frame != (int)frames[i])
				{
					plotframes[(int)(frames[i] - frames[0])] = frames[i];
					curr_frame = (int)frames[i];

					int j = i;
					while (j < frames.Length && curr_frame == (int)(frames[j]))
					{
						plotcounts[(int)(frames[i] - frames[0])]++;
						j++;
					}

				}

			for (int i = 0; i < nframes; i++)
				if (plotframes[i] == 0)
					plotframes[i] = plotframes[i - 1] + 1;

			string title = "Orbit: " + framefits.Header.GetKeyValue("ORB_NUM") + "; Source: " + framefits.Header.GetKeyValue("SOURCEID") + "; Detector:" + framefits.Header.GetKeyValue("DETECTOR");

			JPPlot jpplot = new JPPlot();
			jpplot.Text = title;
			jpplot.PlotLine(plotframes, plotcounts, "Frame Number", "Counts in Frame", title, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "CountsperFrame");
		}

		private void perTimeBinMenuItem_Click(System.Object sender, EventArgs e)
		{
			double tbin;
			try
			{
				tbin = Convert.ToDouble(((string)plotPerTimeBinComboBox.SelectedItem).Replace("s", ""));
			}
			catch
			{
				MessageBox.Show("Please select time bin from the drop down...", "Warning");
				return;
			}

			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = false;

			dlg.Title = "Select the TIME List (_TimeList)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;
			string timelistfile = dlg.FileName;
			dir = timelistfile.Substring(0, timelistfile.LastIndexOf("\\"));
			REG.SetReg("CCDLAB", "L2EventListPath", dir);
			FITSImage timefits = new JPFITS.FITSImage(timelistfile, null, true, false, false, false);
			double[] times = FITSImage.ReadImageVectorOnly(timelistfile, null, true);

			bool goodselection = false;
			if (timelistfile.Contains("TimeList"))
			{
				goodselection = true;
				for (int i = 0; i < times.Length; i++)
					times[i] /= 1000;//convert to seconds
			}
			if (timelistfile.Contains("BJDList"))
			{
				goodselection = true;
				for (int i = 0; i < times.Length; i++)
					times[i] *= 86400;//convert to seconds
			}
			if (!goodselection)
			{
				MessageBox.Show("Doesn't seem like you selected a time list...", "Error");
				return;
			}

			double nbins = Math.Floor((times[times.Length - 1] - times[0]) / tbin);

			if (nbins <= 1)
			{
				MessageBox.Show("Time bin is too large for the selected time list...", "Error");
				return;
			}

			double[] bintimes = new double[(int)nbins];
			double[] bincounts = new double[(int)nbins];

			double currtime = times[0];
			int bin = 0;
			int c = 0;
			double count = 0;

			while (bin < nbins)
			{
				while (times[c] < currtime + tbin)
				{
					c++;
					count++;
				}
				bincounts[bin] = count;
				bintimes[bin] = currtime + tbin / 2;
				currtime += tbin;
				count = 0;
				bin++;
			}

			string title = "Orbit: " + timefits.Header.GetKeyValue("ORB_NUM") + "; Source: " + timefits.Header.GetKeyValue("SOURCEID") + "; Detector:" + timefits.Header.GetKeyValue("DETECTOR");

			JPPlot jpplot = new JPPlot();
			jpplot.Text = title;
			jpplot.PlotLine(bintimes, bincounts, "Bin Time (seconds)", "Counts in Bin", title, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point, "CountsperBin");

		}

		private void CrossCorrINTDriftChck_Click(System.Object sender, EventArgs e)
		{
			if (CrossCorrINTDriftChck.Checked == false)
				CrossCorrINTDriftChck.Checked = true;
			REG.SetReg("CCDLAB", "CrossCorrINTDrift", CrossCorrINTDriftChck.Checked);
			if (CrossCorrINTDriftChck.Checked)
				PointSrcINTDriftChck.Checked = false;
			REG.SetReg("CCDLAB", "PointSrcINTDrift", PointSrcINTDriftChck.Checked);
			TryAutoDeBiasINTDrift.Checked = true;
			TryAutoDeBiasINTDrift.Enabled = true;
			REG.SetReg("CCDLAB", "AutoDeBiasINTDriftChck", TryAutoDeBiasINTDrift.Checked);
			REG.SetReg("CCDLAB", "AutoDeBiasINTDriftEnab", TryAutoDeBiasINTDrift.Enabled);

			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
		}

		private void PointSrcINTDriftChck_Click(System.Object sender, EventArgs e)
		{
			if (PointSrcINTDriftChck.Checked == false)
				PointSrcINTDriftChck.Checked = true;
			REG.SetReg("CCDLAB", "PointSrcINTDrift", PointSrcINTDriftChck.Checked);
			if (PointSrcINTDriftChck.Checked)
				CrossCorrINTDriftChck.Checked = false;
			REG.SetReg("CCDLAB", "CrossCorrINTDrift", CrossCorrINTDriftChck.Checked);
			TryAutoDeBiasINTDrift.Checked = false;
			TryAutoDeBiasINTDrift.Enabled = false;
			REG.SetReg("CCDLAB", "AutoDeBiasINTDriftChck", TryAutoDeBiasINTDrift.Checked);
			REG.SetReg("CCDLAB", "AutoDeBiasINTDriftEnab", TryAutoDeBiasINTDrift.Enabled);

			UVITMenu.ShowDropDown();
			CreateDriftListMenuItem.ShowDropDown();
			CreateDriftFromINTMenuItem.ShowDropDown();
		}

		private void CreateDriftFromINTMenuItem_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.DropDown.Close();
			CreateDriftListMenuItem.DropDown.Close();
			CreateDriftFromINTMenuItem.DropDown.Close();
			PointSrcINTDriftChck.DropDown.Close();

			if (!UVITMANREG_CONTINUE)
			{
				FolderBrowserDialog fdlg = new FolderBrowserDialog();
				if (UVITMANREGDIRLISTINDEX == 0)
				{
					fdlg.SelectedPath = (string)REG.GetReg("CCDLAB", "L2EventListPath");
					if (!AUTOVISDRIFT)
					{
						string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
						fdlg.Description = "Select the Folder of INT-Mode Frames...";
						fdlg.SelectedPath = (string)REG.GetReg("CCDLAB", "L2EventListPath");
						DialogResult res = fdlg.ShowDialog();
						if (res == DialogResult.Cancel)
							return;
						REG.SetReg("CCDLAB", "L2EventListPath", fdlg.SelectedPath);
					}
					AUTOVISDRIFT = false;
					UVITMANREGDIRLIST = Directory.GetDirectories(fdlg.SelectedPath);
				}

				string curdir;
				if (UVITMANREGDIRLIST.Length == 0)
				{
					curdir = fdlg.SelectedPath;
					UVITMANREGDIR_MULTI = false;
				}
				else
				{
					//check if a directory had been removed
					int i = 0;
					for (int j = 0; j < UVITMANREGDIRLIST.Length; j++)
						if (Directory.Exists(UVITMANREGDIRLIST[j]))
						{
							UVITMANREGDIRLIST[i] = UVITMANREGDIRLIST[j];
							i++;
						}
					if (i != UVITMANREGDIRLIST.Length)
						Array.Resize(ref UVITMANREGDIRLIST, i);

					//check if folders in the directory list already contain a drift series...if they do then increment UVITMANREGDIRLISTINDEX until there isn't one
					i = 0;
					while (i < UVITMANREGDIRLIST.Length && Directory.GetFiles(UVITMANREGDIRLIST[i], "*.drift").Length > 0)
						i++;

					if (i == UVITMANREGDIRLIST.Length)
					{
						if (MessageBox.Show("Existing drift series lists found in all subdirectories.  Do you wish to re-process all subdirectories?", "Reprocess?", MessageBoxButtons.YesNo) == DialogResult.No)
							return;

						string[] existinglists = Directory.GetFiles(fdlg.SelectedPath, "*.drift", SearchOption.AllDirectories);
						for (int kkk = 0; kkk < existinglists.Length; kkk++)
							File.Delete(existinglists[kkk]);
						i = 0;
					}

					UVITMANREGDIRLISTINDEX = i;
					curdir = UVITMANREGDIRLIST[UVITMANREGDIRLISTINDEX];
					UVITMANREGDIR_MULTI = true;
				}

				UVITMANREGFILELIST = Directory.GetFiles(curdir, "*.fits", SearchOption.TopDirectoryOnly);
				if (UVITMANREGFILELIST.Length == 0)
				{
					MessageBox.Show("No files found in directory: " + curdir, "Error");
					return;
				}
				Array.Sort(UVITMANREGFILELIST);

				//REG.SetReg("CCDLAB", "FolderBrowserPath", curdir);

				if (CrossCorrINTDriftChck.Checked)
				{
					object[] arg = new object[2];
					arg[0] = (object)UVITMANREGFILELIST;
					arg[1] = (object)CrossCorrINTDriftChck.Checked;
					this.Enabled = false;
					WAITBAR = new WaitBar();
					WAITBAR.ProgressBar.Maximum = 100;
					WAITBAR.DialogResult = DialogResult.OK;
					if (UVITMANREGDIRLIST.Length > 0)
						WAITBAR.Text = "Calculating drift for directory " + (UVITMANREGDIRLISTINDEX + 1).ToString() + " of " + UVITMANREGDIRLIST.Length.ToString();
					else
						WAITBAR.Text = "Calculating drift...";
					DriftFromINTWrkr.RunWorkerAsync(arg);
					WAITBAR.Show();
					return;
				}

				if (PointSrcINTDriftChck.Checked)
				{
					EqualHWChck.Checked = true;
					if (HalfWidthXUpD.Value < 5)
						HalfWidthXUpD.Value = 5;
					ManRegTrkHWUpD.Value = HalfWidthXUpD.Value;
					DOUVITMANREG = true;
					UVITMANREGFILELIST_TIMES = new double[UVITMANREGFILELIST.Length];
					FileListDrop.Items.Clear();
					IMAGESET.Clear();
					string[] refs = new string[] { UVITMANREGFILELIST[0] };
					AddToImageSet(refs, false);
					MainTab.SelectedIndex = 0;
					ImageBatchRedxnPnl.Enabled = true;
					ContrastWideRad.PerformClick();
					UVITMenu.HideDropDown();
					CreateDriftListMenuItem.HideDropDown();
					CreateDriftFromINTMenuItem.HideDropDown();

					bool[,] ROI = new bool[512, 512];
					for (int x = 0; x < 512; x++)
						for (int y = 0; y < 512; y++)
							if ((x - 255) * (x - 255) + (y - 255) * (y - 255) < 235 * 235)
								ROI[x, y] = true;
					PSES = new JPFITS.PointSourceExtractor[] { new JPFITS.PointSourceExtractor() };
					PSESINDEX = 0;
					PSESRECTS = new Rectangle[1][];
					PSES[PSESINDEX].Extract_Sources(IMAGESET[0].Image, 0, 150, 65000, 175, Double.MaxValue, false, 2, 10, true, "", ROI, false);
					if (PSES[PSESINDEX].N_Sources > 35)
						PSES[PSESINDEX].ClipToNBrightest(35);
					if (PSES[PSESINDEX].N_Sources > 0)
					{
						MAKEPSERECTS();
						ShowPSEChck.Checked = true;
						ImageWindow.Refresh();
						SubImageWindow.Refresh();
					}

					DialogResult res = DialogResult.Abort;
					if (PSES[PSESINDEX].N_Sources <= 2)
					{
						res = DialogResult.No;
						PointSrcINTDriftNoPlotConfChck.Checked = false;
					}
					else if (PSES[PSESINDEX].N_Sources > 2 && !PointSrcINTDriftNoPSEConfChck.Checked)
						res = MessageBox.Show("Use " + PSES[PSESINDEX].N_Sources + " auto-found sources for tracking?", "Track?", MessageBoxButtons.YesNoCancel);
					else if (PSES[PSESINDEX].N_Sources > 2 && PointSrcINTDriftNoPSEConfChck.Checked)
						res = DialogResult.Yes;

					if (res == DialogResult.No)
					{
						ManRegBtn.PerformClick();
						return;
					}
					if (res == DialogResult.Cancel)
					{
						DOUVITMANREG = false;
						UVITMANREGFILELIST_TIMES = null;
						UVITMANREGFILELIST = null;
						return;
					}
					if (res == DialogResult.Yes)
					{
						UVITMANREG_CONTINUE = true;
						MANREGCOORDS = new int[PSES[PSESINDEX].N_Sources, 2];
						for (int i = 0; i < PSES[PSESINDEX].N_Sources; i++)
						{
							MANREGCOORDS[i, 0] = (int)PSES[PSESINDEX].Centroids_X[i];
							MANREGCOORDS[i, 1] = (int)PSES[PSESINDEX].Centroids_Y[i];
						}
						HalfWidthXUpD.Value = 5;
						HalfWidthYUpD.Value = 5;
						ImageWindow.Refresh();
						SubImageWindow.Refresh();
					}
				}
			}

			if (UVITMANREG_CONTINUE)
			{
				UVITMANREG_CONTINUE = false;
				MANREG_CONTINUE = false;
				ImageBatchRedxnPnl.Enabled = false;
				ShowFoundCoordsChck.Checked = false;//this is for plotting the local max point in the ROI
				ImageWindow.Refresh();

				DO_UVITDRIFTFILES = true;

				SPAREFITSImageSet = new FITSImageSet();
				SPAREFITSImageSet.Load(UVITMANREGFILELIST, null, false, true, true, "Loading VIS folder");

				this.Enabled = false;
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = 100;
				if (UVITMANREGDIRLIST.Length > 0)
					WAITBAR.Text = "Point Source (" + MANREGCOORDS.GetLength(0) + ") Drift Tracking Directory " + (UVITMANREGDIRLISTINDEX + 1).ToString() + " of " + UVITMANREGDIRLIST.Length.ToString();
				else
					WAITBAR.Text = "Point Source Drift Tracking...";
				ManRegWrkr.RunWorkerAsync();
				WAITBAR.ShowDialog();
			}
		}

		private void DriftFromINTWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			//try
			{
				object[] arg = (object[])e.Argument;
				string[] filelist = (string[])arg[0];
				bool byxcorr = Convert.ToBoolean(arg[1]);

				FITSImage reffits = new FITSImage(filelist[0], null, true, false, false, false);
				FITSImage RELfits;
				double[,] refimg = FITSImage.ReadImageArrayOnly(filelist[0], null, true);
				double lasttime = Convert.ToDouble(reffits.Header.GetKeyValue("FRMTIME")) * 1000;
				double Nstack = Convert.ToDouble(reffits.Header.GetKeyValue("NO_FRMS"));
				double[,] RELimg;
				//array<double> shifts;
				double[,] xyshiftslist = new double[3, filelist.Length];
				double framereadtime, xshift, yshift;

				if (byxcorr)
				{
					bool deBias = TryAutoDeBiasINTDrift.Checked;
					if (deBias)
					{
						refimg = JPMath.DeGradient(refimg, 0, true);
						refimg = JPMath.DeGradient(refimg, 1, true);
					}

					refimg = JPMath.Hanning(refimg, true);
					double[] Href = JPMath.Sum(refimg, 1, true);
					double[] Vref = JPMath.Sum(refimg, 0, true);
					Href = JPMath.VectorSubScalar(Href, JPMath.Mean(Href, true), true);
					Vref = JPMath.VectorSubScalar(Vref, JPMath.Mean(Vref, true), true);

					double currtime, t0, meanxshift = 0, meanyshift = 0;
					int intprog = 0;
					for (int i = 1; i < filelist.Length; i++)
					{

						if (WAITBAR.DialogResult == DialogResult.Cancel)
							return;
						if (100 * i / filelist.Length > intprog)
						{
							intprog = 100 * i / filelist.Length;
							DriftFromINTWrkr.ReportProgress(intprog);
						}

						RELfits = new FITSImage(filelist[i], null, true, false, false, true);
						RELimg = FITSImage.ReadImageArrayOnly(filelist[i], null, true);

						JPMath.XCorrImageLagShifts(Href, Vref, RELimg, deBias, deBias, true, out xshift, out yshift, true);

						currtime = Convert.ToDouble(RELfits.Header.GetKeyValue("FRMTIME")) * 1000;
						framereadtime = (currtime - lasttime) / Nstack;
						t0 = lasttime + framereadtime - Nstack * framereadtime / 2;

						xyshiftslist[0, i - 1] = t0;
						xyshiftslist[1, i] = Math.Round(xshift * 32);
						xyshiftslist[2, i] = Math.Round(yshift * 32);

						meanxshift += xyshiftslist[1, i];//for average drift
						meanyshift += xyshiftslist[2, i];//for average drift

						if (i == filelist.Length - 1)
							xyshiftslist[0, i] = currtime + framereadtime - Nstack * framereadtime / 2;

						lasttime = currtime;
					}

					//zero-out drift series to average drift
					meanxshift /= (double)(filelist.Length);
					meanyshift /= (double)(filelist.Length);

					Parallel.For(0, filelist.Length, i =>
					{
						xyshiftslist[1, i] -= meanxshift;
						xyshiftslist[2, i] -= meanyshift;
					});
				}

				if (!byxcorr)//then by point source tracking
				{
					double meanxshift = 0, meanyshift = 0;
					int NSrc = MANREGCOORDS.GetLength(0);
					framereadtime = (UVITMANREGFILELIST_TIMES[1] - UVITMANREGFILELIST_TIMES[0]) / Nstack;
					xyshiftslist[0, 0] = UVITMANREGFILELIST_TIMES[0] + framereadtime - Nstack * framereadtime / 2;

					double[] xdriftinstance = new double[NSrc];
					double[] ydriftinstance = new double[NSrc];
					double min, max, range = 0;

					for (int i = 1; i < filelist.Length; i++)
					{
						double x_drift = 0;
						double y_drift = 0;
						for (int j = 0; j < NSrc; j++)
						{
							xdriftinstance[j] = MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0];
							ydriftinstance[j] = MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0];
						}

						x_drift = JPMath.Mean_RobustClipped(xdriftinstance, 3);
						y_drift = JPMath.Mean_RobustClipped(ydriftinstance, 3);

						framereadtime = (UVITMANREGFILELIST_TIMES[i] - UVITMANREGFILELIST_TIMES[i - 1]) / Nstack;
						xyshiftslist[0, i] = UVITMANREGFILELIST_TIMES[i] + framereadtime - Nstack * framereadtime / 2;
						xyshiftslist[1, i] = (x_drift * 32);
						xyshiftslist[2, i] = (y_drift * 32);

						meanxshift += xyshiftslist[1, i];//for average drift
						meanyshift += xyshiftslist[2, i];//for average drift

						int index = 0;
						JPMath.MinMax(xdriftinstance, out min, out max, false);
						double currrange = max - min;
						if (currrange > range)
						{
							range = currrange;
							double mean = JPMath.Mean(xdriftinstance, true);
							JPMath.Max(JPMath.Abs(JPMath.VectorSubScalar(xdriftinstance, mean, true), false), out index, false);
							UVITINTDRIFT_MAXDEV_INDEX = index;
						}
						JPMath.MinMax(ydriftinstance, out min, out max, false);
						currrange = max - min;
						if (currrange > range)
						{
							range = currrange;
							double mean = JPMath.Mean(ydriftinstance, true);
							JPMath.Max(JPMath.Abs(JPMath.VectorSubScalar(ydriftinstance, mean, true), false), out index, false);
							UVITINTDRIFT_MAXDEV_INDEX = index;
						}
					}

					//zero-out drift series to average drift
					meanxshift /= (double)(filelist.Length);
					meanyshift /= (double)(filelist.Length);

					Parallel.For(0, filelist.Length, i =>
					{
						xyshiftslist[1, i] -= meanxshift;
						xyshiftslist[2, i] -= meanyshift;
					});
				}

				if (SmoothINTDriftChck.Checked)
				{
					double[] x = new double[filelist.Length];
					double[] y = new double[filelist.Length];
					for (int i = 0; i < filelist.Length; i++)
					{
						x[i] = xyshiftslist[1, i];
						y[i] = xyshiftslist[2, i];
					}

					x = JPMath.Smooth(x, Convert.ToInt32(SmoothINTDriftTimeDrop.SelectedItem), false, "centered");
					y = JPMath.Smooth(y, Convert.ToInt32(SmoothINTDriftTimeDrop.SelectedItem), false, "centered");

					for (int i = 0; i < filelist.Length; i++)
					{
						xyshiftslist[1, i] = x[i];
						xyshiftslist[2, i] = y[i];
					}
				}

				int ind = filelist[0].LastIndexOf("l2");
				string driftslistfile = filelist[0];
				if (ind > 0)
					driftslistfile = filelist[0].Remove(ind + 2);
				driftslistfile = driftslistfile.Replace(".fits", "");
				if (byxcorr)
					driftslistfile = driftslistfile + "_XYDrift_List_XCorr.drift";
				else
					driftslistfile = driftslistfile + "_XYDrift_List_SrcTrk.drift";
				FITSImage driftfits = new FITSImage(driftslistfile, xyshiftslist, false, true);
				driftfits.Header.CopyHeaderFrom(reffits.Header);
				driftfits.WriteImage(TypeCode.Double, true);
				UVPLOTDRIFTFILENAME = driftslistfile;
			}
			/*catch (Exception e)
			{
				MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
			}*/
		}

		private void DriftFromINTWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = String.Concat("Completed: ", e.ProgressPercentage, "%");
			WAITBAR.Refresh();
		}

		private void DriftFromINTWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			DialogResult waitbar_res = WAITBAR.DialogResult;

			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;
			this.BringToFront();
			UVITMANREG_CONTINUE = false;
			DO_UVITDRIFTFILES = false;
			SPAREFITSImageSet.Clear();

			if (waitbar_res == DialogResult.Cancel)
			{
				UVITMANREGDIRLISTINDEX = 0;
				return;
			}

			if (waitbar_res != DialogResult.Cancel)
			{
				if (!UVITMANREGDIR_MULTI && MessageBox.Show("Completed making the drift correction list.  Would you like to plot it?", "Finished...", MessageBoxButtons.YesNo) == DialogResult.Yes)
				{
					UVPLOTDRIFTLISTNOW = true;
					PlotDriftListMenuItem.PerformClick();
				}

				if (UVITMANREGDIR_MULTI)
				{
					UVPLOTDRIFTLISTNOW = true;
					PlotDriftListMenuItem.PerformClick();

					DialogResult dres;
					if (!PointSrcINTDriftNoPlotConfChck.Checked)
						dres = MessageBox.Show("Is the Drift Series OK? (Yes = conintue; No = redo; Cancel = exit)", "Drift Series Check...", MessageBoxButtons.YesNoCancel);
					else
						dres = DialogResult.Yes;

					if (dres == DialogResult.Cancel)
					{
						File.Delete(UVPLOTDRIFTFILENAME);
						UVITINTMODEDRIFTPOLYPOINTS = null;
						ImageWindow.Refresh();
						return;
					}

					if (dres == DialogResult.No)
					{
						File.Delete(UVPLOTDRIFTFILENAME);
						XDRIFT_PLOT.Close();
						YDRIFT_PLOT.Close();
						CreateDriftFromINTMenuItem_Click(sender, new EventArgs());
						return;
					}

					if (dres == DialogResult.Yes && UVITMANREGDIRLISTINDEX < UVITMANREGDIRLIST.Length - 1)
					{
						UVITINTMODEDRIFTPOLYPOINTS = null;
						ImageWindow.Refresh();

						UVITMANREGDIRLISTINDEX++;
						XDRIFT_PLOT.Close();
						YDRIFT_PLOT.Close();
						CreateDriftFromINTMenuItem_Click(sender, new EventArgs());
					}
					else//finished
					{
						XDRIFT_PLOT.Close();
						YDRIFT_PLOT.Close();
						UVITMANREGDIRLISTINDEX = 0;//complete
						UVITINTMODEDRIFTPOLYPOINTS = null;
						DOUVITMANREG = false;
						UVREGISTRATION = false;
						PSESRECTS = null;
						PSES = null;
						ImageWindow.Refresh();

						if (!L1AutoApplyVISDrift.Checked)
							if (MessageBox.Show("Proceed to Application of Drift Series?", "Proceed?", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
								return;
						AUTOVISDRIFTAPPLY = true;
						ConsolidateNUVApplyToFUV_Click(sender, e);
					}
				}
			}
		}

		private void UserXShiftTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (UserXShiftTxt.Text == "-" || UserXShiftTxt.Text == "-." || UserXShiftTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(UserXShiftTxt.Text);
			}
			catch
			{
				UserXShiftTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UserXShiftTxt", UserXShiftTxt.Text);
		}

		private void UserYShiftTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (UserYShiftTxt.Text == "-" || UserYShiftTxt.Text == "-." || UserYShiftTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(UserYShiftTxt.Text);
			}
			catch
			{
				UserYShiftTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UserYShiftTxt", UserYShiftTxt.Text);
		}

		private void UserRotationTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (UserRotationTxt.Text == "-" || UserRotationTxt.Text == "-." || UserRotationTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(UserRotationTxt.Text);
			}
			catch
			{
				UserRotationTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UserRotationTxt", UserRotationTxt.Text);
		}

		private void UserRotationXTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (UserRotationXCenterTxt.Text == "-" || UserRotationXCenterTxt.Text == "-." || UserRotationXCenterTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(UserRotationXCenterTxt.Text);
			}
			catch
			{
				UserRotationXCenterTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UserRotationXTxt", UserRotationXCenterTxt.Text);
		}

		private void UserRotationYTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (UserRotationYCenterTxt.Text == "-" || UserRotationYCenterTxt.Text == "-." || UserRotationYCenterTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(UserRotationYCenterTxt.Text);
			}
			catch
			{
				UserRotationYCenterTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "UserRotationYTxt", UserRotationYCenterTxt.Text);
		}

		private void FlipHorizontalMenuItem_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UserDefinedShiftRotateMenuItem.ShowDropDown();
			REG.SetReg("CCDLAB", "FlipHorizontalMenuItem", FlipHorizontalMenuItem.Checked);
		}

		private void FlipVerticalMenuItem_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UserDefinedShiftRotateMenuItem.ShowDropDown();
			REG.SetReg("CCDLAB", "FlipVerticalMenuItem", FlipVerticalMenuItem.Checked);
		}

		private void LinearRotationChck_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UserDefinedShiftRotateMenuItem.ShowDropDown();
			REG.SetReg("CCDLAB", "LinearRotationChck", LinearRotationChck.Checked);

			if (LinearRotationChck.Checked)
			{
				GeneralTransformChck.Checked = false;

				REG.SetReg("CCDLAB", "GeneralTransformChck", GeneralTransformChck.Checked);

				FlipHorizontalMenuItem.Enabled = true;
				FlipVerticalMenuItem.Enabled = true;
				UserXShiftTxt.Enabled = true;
				UserYShiftTxt.Enabled = true;
				UserRotationTxt.Enabled = true;
				UserRotationXCenterTxt.Enabled = true;
				UserRotationYCenterTxt.Enabled = true;

				TransformCoefATxt.Enabled = false;
				TransformCoefBTxt.Enabled = false;
				TransformCoefCTxt.Enabled = false;
				TransformCoefDTxt.Enabled = false;
				TransformCenterXTxt.Enabled = false;
				TransformCenterYTxt.Enabled = false;
				TransformShiftXTxt.Enabled = false;
				TransformShiftYTxt.Enabled = false;
			}
			else
			{
				FlipHorizontalMenuItem.Enabled = false;
				FlipVerticalMenuItem.Enabled = false;
				UserXShiftTxt.Enabled = false;
				UserYShiftTxt.Enabled = false;
				UserRotationTxt.Enabled = false;
				UserRotationXCenterTxt.Enabled = false;
				UserRotationYCenterTxt.Enabled = false;
			}
		}

		private void GeneralTransformChck_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			ShiftAndRotateMenuItem.ShowDropDown();
			UserDefinedShiftRotateMenuItem.ShowDropDown();
			REG.SetReg("CCDLAB", "GeneralTransformChck", GeneralTransformChck.Checked);

			if (GeneralTransformChck.Checked)
			{
				LinearRotationChck.Checked = false;

				REG.SetReg("CCDLAB", "LinearRotationChck", LinearRotationChck.Checked);

				FlipHorizontalMenuItem.Enabled = false;
				FlipVerticalMenuItem.Enabled = false;
				UserXShiftTxt.Enabled = false;
				UserYShiftTxt.Enabled = false;
				UserRotationTxt.Enabled = false;
				UserRotationXCenterTxt.Enabled = false;
				UserRotationYCenterTxt.Enabled = false;

				TransformCoefATxt.Enabled = true;
				TransformCoefBTxt.Enabled = true;
				TransformCoefCTxt.Enabled = true;
				TransformCoefDTxt.Enabled = true;
				TransformCenterXTxt.Enabled = true;
				TransformCenterYTxt.Enabled = true;
				TransformShiftXTxt.Enabled = true;
				TransformShiftYTxt.Enabled = true;
			}
			else
			{
				TransformCoefATxt.Enabled = false;
				TransformCoefBTxt.Enabled = false;
				TransformCoefCTxt.Enabled = false;
				TransformCoefDTxt.Enabled = false;
				TransformCenterXTxt.Enabled = false;
				TransformCenterYTxt.Enabled = false;
				TransformShiftXTxt.Enabled = false;
				TransformShiftYTxt.Enabled = false;
			}
		}

		private void TransformCoefATxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformCoefATxt.Text == "-" || TransformCoefATxt.Text == "-." || TransformCoefATxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformCoefATxt.Text);
			}
			catch
			{
				TransformCoefATxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformCoefATxt", TransformCoefATxt.Text);
		}

		private void TransformCoefBTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformCoefBTxt.Text == "-" || TransformCoefBTxt.Text == "-." || TransformCoefBTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformCoefBTxt.Text);
			}
			catch
			{
				TransformCoefBTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformCoefBTxt", TransformCoefBTxt.Text);
		}

		private void TransformCoefCTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformCoefCTxt.Text == "-" || TransformCoefCTxt.Text == "-." || TransformCoefCTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformCoefCTxt.Text);
			}
			catch
			{
				TransformCoefCTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformCoefCTxt", TransformCoefCTxt.Text);
		}

		private void TransformCoefDTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformCoefDTxt.Text == "-" || TransformCoefDTxt.Text == "-." || TransformCoefDTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformCoefDTxt.Text);
			}
			catch
			{
				TransformCoefDTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformCoefDTxt", TransformCoefDTxt.Text);
		}

		private void TransformCenterXTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformCenterXTxt.Text == "-" || TransformCenterXTxt.Text == "-." || TransformCenterXTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformCenterXTxt.Text);
			}
			catch
			{
				TransformCenterXTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformCenterXTxt", TransformCenterXTxt.Text);
		}

		private void TransformCenterYTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformCenterYTxt.Text == "-" || TransformCenterYTxt.Text == "-." || TransformCenterYTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformCenterYTxt.Text);
			}
			catch
			{
				TransformCenterYTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformCenterYTxt", TransformCenterYTxt.Text);
		}

		private void TransformShiftXTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformShiftXTxt.Text == "-" || TransformShiftXTxt.Text == "-." || TransformShiftXTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformShiftXTxt.Text);
			}
			catch
			{
				TransformShiftXTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformShiftXTxt", TransformShiftXTxt.Text);
		}

		private void TransformShiftYTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (TransformShiftYTxt.Text == "-" || TransformShiftYTxt.Text == "-." || TransformShiftYTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(TransformShiftYTxt.Text);
			}
			catch
			{
				TransformShiftYTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "TransformShiftYTxt", TransformShiftYTxt.Text);
		}

		private void UserDefinedShiftRotateMenuItem_DropDownOpened(System.Object sender, EventArgs e)
		{
			//done in UVIT_Menu click
		}

		private void UserDefinedShiftRotateMenuItem_DoubleClick(System.Object sender, EventArgs e)
		{
			string[] FileNames;
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");

			if (!UVNUVTOFUV)
			{
				if (LinearRotationChck.Checked)
				{
					double xshift, yshift, rotation, xcenter, ycenter;
					try
					{
						xshift = Convert.ToDouble(UserXShiftTxt.Text);
						yshift = Convert.ToDouble(UserYShiftTxt.Text);
						xcenter = Convert.ToDouble(UserRotationXCenterTxt.Text);
						ycenter = Convert.ToDouble(UserRotationYCenterTxt.Text);
						rotation = Convert.ToDouble(UserRotationTxt.Text) * Math.PI / 180;//degrees to radians
					}
					catch
					{
						MessageBox.Show("There seems to be something wrong with one of the shift/rotate values.  Please check and try again.", "Error...");
						return;
					}
				}

				if (GeneralTransformChck.Checked)
				{
					double xshift, yshift, xcenter, ycenter, TCA, TCB, TCC, TCD;
					try
					{
						xshift = Convert.ToDouble(TransformShiftXTxt.Text);
						yshift = Convert.ToDouble(TransformShiftYTxt.Text);
						xcenter = Convert.ToDouble(TransformCenterXTxt.Text);
						ycenter = Convert.ToDouble(TransformCenterYTxt.Text);
						TCA = Convert.ToDouble(TransformCoefATxt.Text);
						TCB = Convert.ToDouble(TransformCoefBTxt.Text);
						TCC = Convert.ToDouble(TransformCoefCTxt.Text);
						TCD = Convert.ToDouble(TransformCoefDTxt.Text);
					}
					catch
					{
						MessageBox.Show("There seems to be something wrong with one of the shift/rotate values.  Please check and try again.", "Error...");
						return;
					}
				}

				UVITMenu.HideDropDown();
				ShiftAndRotateMenuItem.HideDropDown();
				UserDefinedShiftRotateMenuItem.HideDropDown();

				OpenFileDialog dlg = new OpenFileDialog();
				dlg.InitialDirectory = dir;
				dlg.Filter = "FITS (*.fits)|*.fits";
				dlg.Multiselect = true;
				dlg.Title = "Select the Centroid INTEGERS List (_XYInts_List)";
				DialogResult res = dlg.ShowDialog();
				if (res != DialogResult.OK)
					return;

				FileNames = dlg.FileNames;
				UVCONVERTLISTTOIMAGEBATCHFILES = new string[FileNames.Length];
			}
			else
			{
				FileNames = UVNUVTOFUVFILES;
				UVCONVERTLISTTOIMAGEBATCHFILES = new string[UVNUVTOFUVFILES.Length];
				UVNUVTOFUV = false;
			}

			string IntsFile = FileNames[0];
			int ind = IntsFile.LastIndexOf("\\");
			dir = IntsFile.Substring(0, ind);
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = FileNames.Length;
			WAITBAR.Text = "Transforming centroid list(s)...";
			RotationUVCentroidWrkr.RunWorkerAsync(FileNames);
			WAITBAR.ShowDialog();
		}

		private void RotationUVCentroidWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string[] IntsFiles = (string[])e.Argument;

			ParallelOptions opts = new ParallelOptions();
			if (L1MachineExtremeChck.Checked)
				opts.MaxDegreeOfParallelism = (int)((double)Environment.ProcessorCount / Math.PI);
			else
				opts.MaxDegreeOfParallelism = 1;
			int count = 0;
			object lockobj = new object();

			Parallel.For(0, IntsFiles.Length, opts, (wrkri, loopstate) =>
			{
				//try
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						loopstate.Stop();// break;

					lock (lockobj)
					{
						count++;
						RotationUVCentroidWrkr.ReportProgress(count);
					}

					string IntsFile = IntsFiles[wrkri];
					string FracFile = IntsFile.Replace("Ints", "Frac");
					JPFITS.FITSImage IntsFits = new JPFITS.FITSImage(IntsFile, null, true, true, false, true);
					JPFITS.FITSImage FracFits = new JPFITS.FITSImage(FracFile, null, true, true, false, true);
					int NPts = FracFits.Height;
					double x, y, xprime, yprime;
					int fracx, intsx, fracy, intsy;
					Random r = new Random();

					if (LinearRotationChck.Checked)
					{
						double xshift, yshift, rotation, xcenter, ycenter;
						xshift = Convert.ToDouble(UserXShiftTxt.Text);
						yshift = Convert.ToDouble(UserYShiftTxt.Text);
						xcenter = Convert.ToDouble(UserRotationXCenterTxt.Text);
						ycenter = Convert.ToDouble(UserRotationYCenterTxt.Text);
						rotation = -1 * Convert.ToDouble(UserRotationTxt.Text) * Math.PI / 180;//degrees to radians

						bool horzflip = FlipHorizontalMenuItem.Checked;
						bool vertflip = FlipVerticalMenuItem.Checked;

						for (int j = 0; j < NPts; j++)
						{
							x = (IntsFits[0, j] + FracFits[0, j] + 16) + r.NextDouble();//must add 16 to fractionals
							y = (IntsFits[1, j] + FracFits[1, j] + 16) + r.NextDouble();//and put the centroid somewhere within the 1/32 bin

							if (horzflip)
								x = 511 * 32 - x;
							if (vertflip)
								y = 511 * 32 - y;

							xprime = (x - xcenter * 32) * Math.Cos(rotation) - (y - ycenter * 32) * Math.Sin(rotation) + xcenter * 32 + xshift * 32;
							yprime = (x - xcenter * 32) * Math.Sin(rotation) + (y - ycenter * 32) * Math.Cos(rotation) + ycenter * 32 + yshift * 32;

							//now need to split out integer and decimal parts back into their own lists...
							intsx = Math.DivRem((int)((xprime)), 32, out fracx) * 32;
							fracx -= 16;//reset frac to be from -16
							intsy = Math.DivRem((int)((yprime)), 32, out fracy) * 32;
							fracy -= 16;//reset frac to be from -16
							IntsFits[0, j] = intsx;
							IntsFits[1, j] = intsy;
							FracFits[0, j] = fracx;
							FracFits[1, j] = fracy;
						}

						if (horzflip)
						{
							IntsFits.Header.AddKey("HORZFLIP", "true", "Image Flipped Horizontally", -1);
							FracFits.Header.AddKey("HORZFLIP", "true", "Image Flipped Horizontally", -1);
						}
						if (vertflip)
						{
							IntsFits.Header.AddKey("VERTFLIP", "true", "Image Flipped Vertically", -1);
							FracFits.Header.AddKey("VERTFLIP", "true", "Image Flipped Vertically", -1);
						}
						if (xshift != 0)
						{
							IntsFits.Header.AddKey("XSHIFT", xshift.ToString(), "Centroids X-Shift", -1);
							FracFits.Header.AddKey("XSHIFT", xshift.ToString(), "Centroids X-Shift", -1);
						}
						if (yshift != 0)
						{
							IntsFits.Header.AddKey("YSHIFT", yshift.ToString(), "Centroids Y-Shift", -1);
							FracFits.Header.AddKey("YSHIFT", yshift.ToString(), "Centroids Y-Shift", -1);
						}
						if (rotation != 0)
						{
							IntsFits.Header.AddKey("ROTATN", (-rotation).ToString(), "Centroids Rotation Angle", -1);
							FracFits.Header.AddKey("ROTATN", (-rotation).ToString(), "Centroids Rotation Angle", -1);
						}

						if (UVIT_DEROTATE_WCS)//then use WCS coordinates from header to automatically re-do the WCS solution
						{
							WCS_DEROT.CopyTo(IntsFits.Header);
							WCS_DEROT.CopyTo(FracFits.Header);

							//rotate and shift the exposure array image so that it matches the WCS derotated aspect
							string dedrift = "_deDrift";
							while (IntsFile.Contains(dedrift + "_deDrift"))
								dedrift += "_deDrift";
							string exparrayimagefile = IntsFile.Remove(IntsFile.IndexOf("XYInts")) + "ExpArrayImg";
							exparrayimagefile += dedrift + ".fits";
							FITSImage expfitsimg = new FITSImage(exparrayimagefile, null, true, true, false, true);
							double[,] exparr = expfitsimg.Image;
							exparr = JPMath.RotateShiftArray(exparr, -rotation, Double.MaxValue, Double.MaxValue, "bilinear", 0, 0, true);
							expfitsimg.SetImage(exparr, false, true);
							expfitsimg.WriteImage(TypeCode.Double, true);
						}

						IntsFile = IntsFile.Insert(IntsFile.LastIndexOf("."), "_FSRL");
						IntsFits.WriteImage(IntsFile, TypeCode.Int16, true);
						FracFile = FracFile.Insert(FracFile.LastIndexOf("."), "_FSRL");
						FracFits.WriteImage(FracFile, TypeCode.Int16, true);
					}

					if (GeneralTransformChck.Checked)
					{
						double xshift, yshift, xcenter, ycenter, TCA, TCB, TCC, TCD;
						xshift = Convert.ToDouble(TransformShiftXTxt.Text);
						yshift = Convert.ToDouble(TransformShiftYTxt.Text);
						xcenter = Convert.ToDouble(TransformCenterXTxt.Text);
						ycenter = Convert.ToDouble(TransformCenterYTxt.Text);
						TCA = Convert.ToDouble(TransformCoefATxt.Text);
						TCB = Convert.ToDouble(TransformCoefBTxt.Text);
						TCC = Convert.ToDouble(TransformCoefCTxt.Text);
						TCD = Convert.ToDouble(TransformCoefDTxt.Text);

						for (int j = 0; j < NPts; j++)
						{
							x = (IntsFits[0, j] + FracFits[0, j] + 16) + r.NextDouble();//must add 16 to fractionals
							y = (IntsFits[1, j] + FracFits[1, j] + 16) + r.NextDouble();//and put the centroid somewhere within the 1/32 bin

							xprime = (x - xcenter * 32) * TCA + (y - ycenter * 32) * TCB + xcenter * 32 + xshift * 32;
							yprime = (x - xcenter * 32) * TCC + (y - ycenter * 32) * TCD + ycenter * 32 + yshift * 32;

							//now need to split out integer and decimal parts back into their own lists...
							intsx = Math.DivRem((int)((xprime)), 32, out fracx) * 32;
							fracx -= 16;//reset frac to be from -16
							intsy = Math.DivRem((int)((yprime)), 32, out fracy) * 32;
							fracy -= 16;//reset frac to be from -16
							IntsFits[0, j] = intsx;
							IntsFits[1, j] = intsy;
							FracFits[0, j] = fracx;
							FracFits[1, j] = fracy;
						}

						//now give the shifted/rotated list a new name and save
						IntsFile = IntsFile.Insert(IntsFile.LastIndexOf("."), "_FSRG");
						IntsFits.WriteImage(IntsFile, TypeCode.Int16, true);
						FracFile = FracFile.Insert(FracFile.LastIndexOf("."), "_FSRG");
						FracFits.WriteImage(FracFile, TypeCode.Int16, true);
					}

					UVCONVERTLISTTOIMAGEBATCHFILES[wrkri] = IntsFile;
				}
				/*catch (Exception e)
				{
					MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
				}*/
			});
		}

		private void RotationUVCentroidWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.TextMsg.Text = "Transforming file " + (e.ProgressPercentage).ToString() + " of " + WAITBAR.ProgressBar.Maximum.ToString();
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.Refresh();
		}

		private void RotationUVCentroidWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				this.Enabled = true;
				return;
			}

			if (!UVIT_DEROTATE_WCS && MessageBox.Show("Completed shifting/rotating the centroid list(s).  Would you like to convert to image(s)?", "Images?", MessageBoxButtons.YesNo) == DialogResult.No)
			{
				WAITBAR.Hide();
				WAITBAR.Close();
				this.Enabled = true;
				return;
			}

			//now create the images...automatic if UVIT_DEROTATE_WCS
			ConvertListToImgMenu_DropDownOpened(sender, e);
			ConvertListToImgMenu.HideDropDown();
			UVCONVERTLISTTOIMAGEBATCH = true;
			AUTOLOADIMAGESFILES = new string[UVCONVERTLISTTOIMAGEBATCHFILES.Length];

			WAITBAR.ProgressBar.Value = 0;
			WAITBAR.ProgressBar.Maximum = UVCONVERTLISTTOIMAGEBATCHFILES.Length;
			WAITBAR.Text = "Creating image(s)...";
			ConvertUVCentroidListToImgWrkr.RunWorkerAsync(UVCONVERTLISTTOIMAGEBATCHFILES);
		}

		private void DeRotateViaWCS_Click(System.Object sender, EventArgs e)
		{
			if (MessageBox.Show("CURRENT image OK to base derotation upon?", "CURRENT IMAGE AS REFERENCE?", MessageBoxButtons.YesNo) == DialogResult.No)
			{
				UVIT_DEROTATE_FILES = null;
				return;
			}

			//need to get the most recent/longest filename XYInts files for each image
			UVIT_DEROTATE_FILES = new string[IMAGESET.Count];
			for (int i = 0; i < UVIT_DEROTATE_FILES.Length; i++)
			{
				string[] xyintsfiles = Directory.GetFiles(IMAGESET[i].FilePath, "*XYInts*.fits");
				UVIT_DEROTATE_FILES[i] = xyintsfiles[0];
				for (int j = 1; j < xyintsfiles.Length; j++)
					if (xyintsfiles[j].Length > UVIT_DEROTATE_FILES[i].Length)
						UVIT_DEROTATE_FILES[i] = xyintsfiles[j];
			}

			//make the reference file the first, so that when it goes to ConvertUVCentroidListToImgWrkr the first image get re-PSE'd given the CPIX transform below and the new PSE is then used to create the new derotated WCS and for the following images
			if (FILELISTINDEX != 0)
			{
				string temp = UVIT_DEROTATE_FILES[0];
				UVIT_DEROTATE_FILES[0] = UVIT_DEROTATE_FILES[FILELISTINDEX];
				UVIT_DEROTATE_FILES[FILELISTINDEX] = temp;
			}

			UVIT_DEROTATE_WCS = true;
			LinearRotationChck.Checked = true;
			FlipHorizontalMenuItem.Checked = false;
			FlipVerticalMenuItem.Checked = false;
			UserXShiftTxt.Text = "0";
			UserYShiftTxt.Text = "0";
			UserRotationXCenterTxt.Text = "255";
			UserRotationYCenterTxt.Text = "255";
			UserRotationTxt.Text = Convert.ToString(-(IMAGESET[FILELISTINDEX].WCS.GetCROTAn(1) + IMAGESET[FILELISTINDEX].WCS.GetCROTAn(2)) / 2);
			UVCONVERTLISTTOIMAGEBATCHFILES = new string[UVIT_DEROTATE_FILES.Length];//pre-make

			/////////////////////////////////
			//rotate/shift the WCS values in the header so that the image creator can then use those to determine new PSE on them and make new derotated WCS
			double xshift = Convert.ToDouble(UserXShiftTxt.Text);
			double yshift = Convert.ToDouble(UserYShiftTxt.Text);
			double xcenter = Convert.ToDouble(UserRotationXCenterTxt.Text);
			double ycenter = Convert.ToDouble(UserRotationYCenterTxt.Text);
			double rotation = -1 * Convert.ToDouble(UserRotationTxt.Text) * Math.PI / 180;//degrees to radians
			WCS_DEROT = new JPFITS.WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);
			double prec = 1;//check for the image precision...
			string strprec = IMAGESET[FILELISTINDEX].Header.GetKeyValue("IMAGPREC");
			if (strprec != "")
				prec = Convert.ToDouble(strprec);
			double offset = 0;
			string stroffset = IMAGESET[FILELISTINDEX].Header.GetKeyValue("PADOFSET");
			if (stroffset != "")
				offset = Convert.ToDouble(stroffset);
			for (int j = 0; j < WCS_DEROT.GetCPIXPixels(1).Length; j++)
			{
				double x = ((double[])WCS_DEROT.GetCPIXPixels(1))[j];
				double y = ((double[])WCS_DEROT.GetCPIXPixels(2))[j];
				double xprime = (x / prec * 32 - (xcenter + offset) * 32) * Math.Cos(rotation) - (y / prec * 32 - (ycenter + offset) * 32) * Math.Sin(rotation) + (xcenter + offset) * 32 + xshift * 32;
				double yprime = (x / prec * 32 - (xcenter + offset) * 32) * Math.Sin(rotation) + (y / prec * 32 - (ycenter + offset) * 32) * Math.Cos(rotation) + (ycenter + offset) * 32 + yshift * 32;
				xprime /= (32 / prec);
				yprime /= (32 / prec);
				((double[])WCS_DEROT.GetCPIXPixels(1))[j] = xprime;
				((double[])WCS_DEROT.GetCPIXPixels(2))[j] = yprime;
			}
			/////////////////////////////////

			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = UVIT_DEROTATE_FILES.Length;
			WAITBAR.Text = "de-Rotating centroid list(s)...";
			RotationUVCentroidWrkr.RunWorkerAsync(UVIT_DEROTATE_FILES);
			WAITBAR.ShowDialog();
		}

		private void INTAtoINTADriftCorrectionMenuItem_Click(System.Object sender, EventArgs e)
		{
			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = false;

			dlg.Title = "Select the DRIFT List (_XYDrift_List)";
			dlg.Filter = "DRIFT (*.drift)|*.drift";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;
			string driftlistfile = dlg.FileName;
			dir = driftlistfile.Substring(0, driftlistfile.LastIndexOf("\\"));
			REG.SetReg("CCDLAB", "L2EventListPath", dir);

			FolderBrowserDialog fdlg = new FolderBrowserDialog();
			fdlg.SelectedPath = dir;
			fdlg.Description = "Select the folder of the INT-mode *.fits image files to be drift corrected...";
			res = fdlg.ShowDialog();
			if (res == DialogResult.Cancel)
				return;
			string[] filelist = Directory.GetFiles(fdlg.SelectedPath, "*.fits", SearchOption.TopDirectoryOnly);
			if (filelist.Length == 0)
			{
				MessageBox.Show("No files found in that directory.", "Error");
				return;
			}
			REG.SetReg("CCDLAB", "FolderBrowserPath", fdlg.SelectedPath);

			double[,] drifts = FITSImage.ReadImageArrayOnly(driftlistfile, null, true);
			if (filelist.Length != drifts.GetLength(1))
			{
				MessageBox.Show("Number of drift measurements not equal to number of files in the directory.  Check your work.", "Error...");
				return;
			}

			string savepath = fdlg.SelectedPath + "\\" + "de-drifted";
			Directory.CreateDirectory(savepath);
			REG.SetReg("CCDLAB", "FolderBrowserPath", savepath);

			object[] arg = new object[3];
			arg[0] = (object)driftlistfile;
			arg[1] = (object)fdlg.SelectedPath;
			arg[2] = (object)savepath;
			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = 100;
			WAITBAR.DialogResult = DialogResult.OK;
			WAITBAR.Text = "Applying Drift Correction...";
			INTAtoINTAapplyDriftWrkr.RunWorkerAsync(arg);
			WAITBAR.Show();
		}

		private void INTAtoINTAapplyDriftWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			object[] arg = (object[])e.Argument;
			string driftlistfile = (string)arg[0];
			string driftlistpath = (string)arg[1];
			string savepath = (string)arg[2];

			double[,] drifts = FITSImage.ReadImageArrayOnly(driftlistfile, null, true);
			string[] filelist = Directory.GetFiles(driftlistpath, "*.fits", SearchOption.TopDirectoryOnly);

			for (int i = 0; i < filelist.Length; i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;
				INTAtoINTAapplyDriftWrkr.ReportProgress(100 * i / filelist.Length);

				FITSImage fits = new FITSImage(filelist[i], null, true, true, false, true);
				fits.SetImage(JPMath.ShiftArrayInt(fits.Image, -(int)(drifts[1, i]) / 32, -(int)(drifts[2, i]) / 32, true), false, true);//or round instead of int?
				string name = savepath + "\\" + fits.FileName;
				name = name.Replace(".fits", "_deDrift.fits");
				fits.WriteImage(name, TypeCode.Int16, true);
			}
		}

		private void INTAtoINTAapplyDriftWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = String.Concat("Completed: ", e.ProgressPercentage, "%");
			WAITBAR.Refresh();//find all Update() and replace with Refresh()
		}

		private void INTAtoINTAapplyDriftWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;
			this.BringToFront();

			if (WAITBAR.DialogResult == DialogResult.Cancel)
				return;

			MessageBox.Show("Completed drift-correcting the INT-mode images.");
		}

		private void GeneralUVRegistrationMenuItem_Click(System.Object sender, EventArgs e)
		{
			if (!UVREGISTRATION)
			{
				ProgressBar.Value = 0;
				ProgressBar.Refresh();
				ProgressBar.Maximum = 2;

				UVITMenu.HideDropDown();
				GeneralUVRegistrationMenuItem.HideDropDown();

				string[] xyintsfiles;

				if (RegistrationXYIntsListFolderScanChck.Checked)
				{
					FolderBrowserDialog fbd = new FolderBrowserDialog();
					fbd.SelectedPath = (string)REG.GetReg("CCDLAB", "L2EventListPath");
					if (new DirectoryInfo(fbd.SelectedPath).Name == "VIS")
						fbd.SelectedPath = Path.GetDirectoryName(fbd.SelectedPath);
					fbd.Description = "Select the folder to scan for the most recent INTEGERS Lists (_XYInts_List)";
					if (fbd.ShowDialog() == DialogResult.Cancel)
						return;
					REG.SetReg("CCDLAB", "L2EventListPath", fbd.SelectedPath);
					REG.SetReg("CCDLAB", "OpenFilesPath", fbd.SelectedPath);

					//only want to register the most recent xyintsfiles so must go through and sort this out
					//each XYInts file will be in its own directory, and this is where its dupes will be
					//we want only the most recent (longest file name length) dupe from each directory
					//when registering can only do so on deDrift files, so if there are directories that couldn't be deDrift, don't use those files

					//xyintsfiles = Directory.GetFiles(fbd.SelectedPath, "*MASTER*XYInts_List*deDrift*.fits", SearchOption.AllDirectories);
					//if (xyintsfiles.Length == 0)//then just doing filter directories with multiobs
					//	xyintsfiles = Directory.GetFiles(fbd.SelectedPath, "*XYInts_List*deDrift*.fits", SearchOption.AllDirectories);
					xyintsfiles = Directory.GetFiles(fbd.SelectedPath, "*XYInts_List*deDrift*.fits", SearchOption.AllDirectories);
					for (int i = 0; i < xyintsfiles.Length; i++)
					{
						string dir = Path.GetDirectoryName(Path.GetDirectoryName(xyintsfiles[i]));
						if (Directory.GetFiles(dir, "*MASTER*XYInts_List*deDrift*.fits").Length != 0)//then use only master files, ignore unmerged files
							xyintsfiles[i] = "";
					}
					int c = 0;
					for (int i = 0; i < xyintsfiles.Length; i++)
						if (xyintsfiles[i] != "")
						{
							xyintsfiles[c] = xyintsfiles[i];
							c++;
						}
					Array.Resize(ref xyintsfiles, c);

					Array.Sort(xyintsfiles);
					if (xyintsfiles.Length == 0)
					{
						MessageBox.Show("No files found...", "Error...");
						return;
					}
					/*int */
					c = 0;
					for (int i = 0; i < xyintsfiles.Length; i++)
					{
						string curdir = Path.GetDirectoryName(xyintsfiles[i]);
						string[] dirxyfiles = Directory.GetFiles(curdir, "*XYInts_List*deDrift*.fits");
						int ind = 0;
						for (int j = 1; j < dirxyfiles.Length; j++)
							if (dirxyfiles[j].Length > dirxyfiles[ind].Length)
								ind = j;

						xyintsfiles[c] = dirxyfiles[ind];
						c++;
						i += dirxyfiles.Length - 1;
					}
					Array.Resize(ref xyintsfiles, c);
				}
				else
				{
					string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
					OpenFileDialog dlg = new OpenFileDialog();
					dlg.InitialDirectory = dir;
					dlg.Filter = "FITS (*.fits)|*.fits";
					dlg.Multiselect = true;
					dlg.Title = "Select the Centroid INTEGERS Lists (_XYInts_List)";
					DialogResult res = dlg.ShowDialog();
					if (res != DialogResult.OK)
						return;

					xyintsfiles = dlg.FileNames;

					dir = dlg.FileNames[0].Substring(0, dlg.FileNames[0].LastIndexOf("\\"));
					dir = dir.Substring(0, dir.LastIndexOf("\\"));//this is the upper dir containing all sub orbit directories
					REG.SetReg("CCDLAB", "L2EventListPath", dir);
					REG.SetReg("CCDLAB", "OpenFilesPath", dir);
				}

				if (xyintsfiles.Length == 1)
				{
					MessageBox.Show("Need to select more than 1 file for image registration...", "Error...");
					return;
				}

				if (MessageBox.Show("Please select point sources (LEFT-CLICK) which stay within the field of view for the duration of the image set!  RIGHT-CLICK when done.", "Centroid List Registration...", MessageBoxButtons.OKCancel) == DialogResult.Cancel)
					return;

				if (UVGeneralRegistrationResolutionDrop.SelectedIndex == 2)
					ListToImage4PixMenuItem.PerformClick();
				if (UVGeneralRegistrationResolutionDrop.SelectedIndex == 1)
					ListToImage2PixMenuItem.PerformClick();
				if (UVGeneralRegistrationResolutionDrop.SelectedIndex == 0)
					ListToImage1PixMenuItem.PerformClick();
				UVITMenu.HideDropDown();
				ConvertListToImgMenu.HideDropDown();

				IWLCK = false;//allow cursor box to move
							  //ImageWindow.Cursor.Hide();
				EqualHWChck.Checked = true;
				HalfWidthXUpD.Value = UVLISTTOIMAGEPREC * 10 / 2;
				FNDCOORDS_X = new int[1];//this is for plotting the local max point in the ROI
				FNDCOORDS_Y = new int[1];
				FNDCOORDRECTS = new Rectangle[1];
				ShowFoundCoordsChck.Checked = true;//this is for plotting the local max point in the ROI
				MANREGCOORDS = new int[0, 0];
				MANREGCOORDRECTS = new Rectangle[0];

				UVREGISTRATION = true;
				UVREGISTRATIONFILES = xyintsfiles;
				if (masterizeSinglesToolStripMenuItem.Checked)
					for (int i = 0; i < UVREGISTRATIONFILES.Length; i++)
						if (UVREGISTRATIONFILES[i].Contains("_MASTER_"))
							continue;
						else
						{
							string filedir = Path.GetDirectoryName(UVREGISTRATIONFILES[i]);
							string pardir = Directory.GetParent(filedir).FullName;
							if (Directory.GetDirectories(pardir).Length == 1)
							{
								int indlast = UVREGISTRATIONFILES[i].IndexOf("_XYInts");
								string test = UVREGISTRATIONFILES[i].Substring(0, indlast - 1);
								int indfirst = test.LastIndexOf("_");
								test = UVREGISTRATIONFILES[i].Substring(0, indfirst - 1);
								indfirst = test.LastIndexOf("_") + 1;
								string replacestr = UVREGISTRATIONFILES[i].Substring(indfirst, indlast - indfirst);

								string[] dirfiles = Directory.GetFiles(filedir);
								for (int j = 0; j < dirfiles.Length; j++)
								{
									string newfile = dirfiles[j].Replace(replacestr, "__MASTER__");
									newfile = pardir + "\\" + newfile.Substring(newfile.LastIndexOf("\\"));
									File.Move(dirfiles[j], newfile);
									if (dirfiles[j] == UVREGISTRATIONFILES[i])
										UVREGISTRATIONFILES[i] = newfile;
								}
								Directory.Delete(filedir, true);
							}
						}
				UVREGISTRATIONFILESINDEX = 0;
				UVREGISTRATION_CENTROIDS = null;
				UVCREATEIMAGEFILENAME = UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX];
				UVAutoDriftImageViewChck.Checked = true;
				UVCREATEIMAGENOW = true;
				UVREGISTRATION_ANCHOR_INDEX = Int32.MaxValue;
				UVREGISTRATION_ROTATION_INDEX = Int32.MaxValue;

				ProgressBar.Value = 1;
				ProgressBar.Refresh();

				ConvertListToImgMenu_Click(sender, e);

				return;
			}

			if (UVREGISTRATION && MANREGCOORDRECTS.Length == 0)//clicked out without any point selections
			{
				UVREGISTRATION = false;
				ShowFoundCoordsChck.Checked = false;
				Cursor.Show();
				ImageWindow.Refresh();
				ListToImage8PixMenuItem.PerformClick();
				UVITMenu.HideDropDown();
				ConvertListToImgMenu.HideDropDown();
				ProgressBar.Value = 0;
				return;
			}

			if (UVREGISTRATION && UVREGISTRATIONFILESINDEX < UVREGISTRATIONFILES.Length - 1)
			{
				DialogResult res;
				if (UVITAUTOREGISTER)
					res = DialogResult.Yes;
				else
				{
					ProgressBar.Value = 0;
					ProgressBar.Refresh();
					res = MessageBox.Show("Continue to image " + (UVREGISTRATIONFILESINDEX + 2).ToString() + " of " + (UVREGISTRATIONFILES.Length).ToString() + "?", "Centroid List Registration...", MessageBoxButtons.YesNoCancel);
				}

				if (res == DialogResult.Cancel)//stop registration
				{
					UVREGISTRATION = false;
					UVREGISTRATIONFILES = null;
					ShowFoundCoordsChck.Checked = false;//this is for plotting the local max point in the ROI
					Cursor.Show();
					ImageWindow.Cursor = Cursors.Cross;
					ShowCursorBox.Checked = true;
					ImageWindow.Refresh();

					ListToImage8PixMenuItem.PerformClick();
					UVITMenu.HideDropDown();
					ConvertListToImgMenu.HideDropDown();

					ProgressBar.Value = 0;

					return;
				}

				if (res == DialogResult.No)//keep moving points
					return;

				//else it is yes
				ShowFoundCoordsChck.Checked = false;//this is for plotting the local max point in the ROI...the selected MANREGCOORS are still plotted
													//ShowCursorBox.Checked = false;
				ImageWindow.Cursor = Cursors.Hand;
				Cursor.Show();

				UVREGISTRATION_TRANSLATE = true;
				UVREGISTRATION_ROTATION_PHI = 0;

				UVREGISTRATIONFILESINDEX++;
				UVCREATEIMAGEFILENAME = UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX];
				UVCREATEIMAGENOW = true;

				//if re-registering from an earlier registered list, then it means that the last registration (or more) was no good.
				//hence should delete ALL of those files in order to start again from here
				string regs = "_RGSTRD";
				while (UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX - 1].Contains(regs))
					regs += "_RGSTRD";
				//higher iteration registrations must go.  they are given regs
				string[] delfiles = Directory.GetFiles(UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX - 1].Substring(0, UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX - 1].LastIndexOf("\\")), "*" + regs + "*");
				for (int i = 0; i < delfiles.Length; i++)
					File.Delete(delfiles[i]);

				if (!UVITAUTOREGISTER)
				{
					ProgressBar.Value = 1;
					ProgressBar.Refresh();
				}

				ConvertListToImgMenu_Click(sender, e);
				return;
			}

			if (UVREGISTRATION && UVREGISTRATIONFILESINDEX == UVREGISTRATIONFILES.Length - 1)//now compute the transformations and apply them to the centroid lists
			{
				//if re-registering from an earlier registered list, then it means that the last registration (or more) was no good.
				//hence should delete ALL of those files in order to start again from here
				string regs = "_RGSTRD";
				while (UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX].Contains(regs))
					regs += "_RGSTRD";
				//higher iteration registrations must go.  they are given regs
				string[] delfiles = Directory.GetFiles(UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX].Substring(0, UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX].LastIndexOf("\\")), "*" + regs + "*");
				for (int i = 0; i < delfiles.Length; i++)
					File.Delete(delfiles[i]);

				UVREGISTRATION = false;
				ShowFoundCoordsChck.Checked = false;
				ShowCursorBox.Checked = true;
				ImageWindow.Cursor = Cursors.Cross;
				ProgressBar.Value = 0;
				ImageWindow.Refresh();

				if (!UVITAUTOREGISTER)
					if (MessageBox.Show("Determine and apply the registration tranformation(s)?", "Centroid Registration...", MessageBoxButtons.YesNo) == DialogResult.No)
						return;
				UVITAUTOREGISTER = false;

				UVCONVERTLISTTOIMAGEBATCHFILES = new string[UVREGISTRATIONFILES.Length];
				AUTOLOADIMAGESFILES = new string[UVREGISTRATIONFILES.Length];

				this.Enabled = false;
				WAITBAR = new WaitBar();
				WAITBAR.ProgressBar.Maximum = UVREGISTRATIONFILES.Length;
				WAITBAR.Text = "Registration...";
				WAITBAR.ProgressBar.Value = 1;
				WAITBAR.TextMsg.Text = "Wait a sec while I make a copy of the reference file...";
				RegistrationUVCentroidWrkr.RunWorkerAsync();
				WAITBAR.Show();
			}
		}

		private void RegistrationUVCentroidWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			//try
			{
				//update first reference files
				string intsFile = UVREGISTRATIONFILES[0];
				string fracFile = UVREGISTRATIONFILES[0].Replace("Ints", "Frac");
				File.Copy(intsFile, intsFile.Insert(intsFile.LastIndexOf("."), "_RGSTRD"), true);
				File.SetLastWriteTime(intsFile.Insert(intsFile.LastIndexOf("."), "_RGSTRD"), DateTime.Now);
				UVCONVERTLISTTOIMAGEBATCHFILES[0] = intsFile.Insert(intsFile.LastIndexOf("."), "_RGSTRD");
				File.Copy(fracFile, fracFile.Insert(fracFile.LastIndexOf("."), "_RGSTRD"), true);
				File.SetLastWriteTime(fracFile.Insert(fracFile.LastIndexOf("."), "_RGSTRD"), DateTime.Now);				

				string drift = "_deDrift";
				while (intsFile.Contains(drift + "_deDrift"))
					drift += "_deDrift";
				string exparraagefile = intsFile.Remove(intsFile.IndexOf("XYInts")) + "ExpArrayImg";
				exparraagefile += drift + ".fits";
				File.SetLastWriteTime(exparraagefile, DateTime.Now);

				//set up arrays
				double[] xref = new double[UVREGISTRATION_CENTROIDS.GetLength(1)];
				double[] yref = new double[UVREGISTRATION_CENTROIDS.GetLength(1)];
				for (int j = 0; j < UVREGISTRATION_CENTROIDS.GetLength(1); j++)
				{
					xref[j] = UVREGISTRATION_CENTROIDS[0, j, 0];
					yref[j] = UVREGISTRATION_CENTROIDS[0, j, 1];
				}

				ParallelOptions opts = new ParallelOptions();
				if (L1MachineExtremeChck.Checked)
					opts.MaxDegreeOfParallelism = (int)((double)Environment.ProcessorCount / Math.PI);
				else
					opts.MaxDegreeOfParallelism = 1;
				object lockob = new object();
				int count = 1;

				Parallel.For(1, UVREGISTRATIONFILES.Length, opts, (i, loopstate) =>
				//for (int i = 1; i < UVREGISTRATIONFILES.Length; i++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						loopstate.Stop();// break;

					lock (lockob)
					{
						count++;
						RegistrationUVCentroidWrkr.ReportProgress(count);
					}

					string IntsFile = UVREGISTRATIONFILES[i];
					string FracFile = IntsFile.Replace("Ints", "Frac");
					JPFITS.FITSImage IntsFits = new JPFITS.FITSImage(IntsFile, null, true, true, false, false);
					JPFITS.FITSImage FracFits = new JPFITS.FITSImage(FracFile, null, true, true, false, false);
					int NPts = FracFits.Height;
					double x, y, xprime, yprime, xshift = 0, yshift = 0, rotation = 0, xcenter = 0, ycenter = 0;
					int fracx, intsx, fracy, intsy;
					Random r = new Random();
					double[] xtran = new double[UVREGISTRATION_CENTROIDS.GetLength(1)];
					double[] ytran = new double[UVREGISTRATION_CENTROIDS.GetLength(1)];
					double[] P0;
					double[] Plb;
					double[] Pub;
					double[] Psc;

					for (int j = 0; j < UVREGISTRATION_CENTROIDS.GetLength(1); j++)
					{
						xtran[j] = UVREGISTRATION_CENTROIDS[i, j, 0];
						ytran[j] = UVREGISTRATION_CENTROIDS[i, j, 1];
					}

					if (xref.Length == 1)//just single points for shifting
					{
						xshift = -(xtran[0] - xref[0]) * 32 / (double)(UVLISTTOIMAGEPREC);
						yshift = -(ytran[0] - yref[0]) * 32 / (double)(UVLISTTOIMAGEPREC);

						//MessageBox.Show("1: " + xshift + " " + yshift);

						for (int j = 0; j < NPts; j++)
						{
							x = (IntsFits[0, j] + FracFits[0, j] + 16) + r.NextDouble();//must add 16 to fractionals
							y = (IntsFits[1, j] + FracFits[1, j] + 16) + r.NextDouble();//and put the centroid somewhere within the 1/32 bin

							xprime = x + xshift;
							yprime = y + yshift;

							//now need to split out integer and decimal parts back into their own lists...
							intsx = Math.DivRem((int)((xprime)), 32, out fracx) * 32;
							fracx -= 16;//reset frac to be from -16
							intsy = Math.DivRem((int)((yprime)), 32, out fracy) * 32;
							fracy -= 16;//reset frac to be from -16
							IntsFits[0, j] = intsx;
							IntsFits[1, j] = intsy;
							FracFits[0, j] = fracx;
							FracFits[1, j] = fracy;
						}
					}

					if (xref.Length > 1)//then have 2-D points for rotation tranformation
					{
						//MessageBox.Show("1: " + UVREGISTRATION_THETAS[i] + " " + rotation);

						P0 = new double[] { 1, UVREGISTRATION_PHIS[i], UVREGISTRATION_XCENTERS[i], UVREGISTRATION_YCENTERS[i], UVREGISTRATION_XSHIFTS[i], UVREGISTRATION_YSHIFTS[i] };
						Plb = new double[] { 1, UVREGISTRATION_PHIS[i] - Math.PI / 8, UVREGISTRATION_XCENTERS[i] - 20, UVREGISTRATION_YCENTERS[i] - 20, UVREGISTRATION_XSHIFTS[i] - 20, UVREGISTRATION_YSHIFTS[i] - 20 };
						Pub = new double[] { 1, UVREGISTRATION_PHIS[i] + Math.PI / 8, UVREGISTRATION_XCENTERS[i] + 20, UVREGISTRATION_YCENTERS[i] + 20, UVREGISTRATION_XSHIFTS[i] + 20, UVREGISTRATION_YSHIFTS[i] + 20 };
						Psc = new double[] { 1, 1, 1000, 1000, 50, 50 };
						JPMath.Fit_GeneralTransform2d(xref, yref, xtran, ytran, ref P0, Plb, Pub, Psc);
						rotation = P0[1];
						xcenter = P0[2];
						ycenter = P0[3];
						xshift = P0[4];
						yshift = P0[5];

						//MessageBox.Show("2: " + UVREGISTRATION_PHIS[i]*180/3.14159 + " " + rotation*180/3.14159 + " " + UVREGISTRATION_XSHIFTS[i] + " " + xshift + " " + UVREGISTRATION_YSHIFTS[i] + " " + yshift);

						bool general_transformation = false;//can only do rotation above if only 2 points
						if (xref.Length > 2)
							general_transformation = true;

						if (general_transformation)//now do general transformation using the linear transformation results as initial guess
						{
							P0 = new double[] { Math.Cos(rotation), -Math.Sin(rotation), Math.Sin(rotation), Math.Cos(rotation), xcenter, ycenter, xshift, yshift };
							Plb = new double[] { -1.1, -1.1, -1.1, -1.1, xcenter - 20, ycenter - 20, xshift - 20, yshift - 20 };
							Pub = new double[] { 1.1, 1.1, 1.1, 1.1, xcenter + 20, ycenter + 20, xshift + 20, yshift + 20 };
							Psc = new double[] { 1, 1, 1, 1, 1000, 1000, 50, 50 };
							JPMath.Fit_GeneralTransform2d(xref, yref, xtran, ytran, ref P0, Plb, Pub, Psc);
							xcenter = P0[4];
							ycenter = P0[5];
							xshift = P0[6];
							yshift = P0[7];
						}

						//MessageBox.Show("2: " + UVREGISTRATION_THETAS[i] * 180 / 3.14159 + " " + rotation * 180 / 3.14159 + " " + UVREGISTRATION_XSHIFTS[i] + " " + xshift + " " + UVREGISTRATION_YSHIFTS[i] + " " + yshift);

						xcenter *= (32 / (double)(UVLISTTOIMAGEPREC));
						ycenter *= (32 / (double)(UVLISTTOIMAGEPREC));
						xshift *= (32 / (double)(UVLISTTOIMAGEPREC));
						yshift *= (32 / (double)(UVLISTTOIMAGEPREC));

						for (int j = 0; j < NPts; j++)
						{
							x = (IntsFits[0, j] + FracFits[0, j] + 16) + r.NextDouble();//must add 16 to fractionals
							y = (IntsFits[1, j] + FracFits[1, j] + 16) + r.NextDouble();//and put the centroid somewhere within the 1/32 bin

							if (!general_transformation)
							{
								xprime = (x - xcenter) * Math.Cos(rotation) - (y - ycenter) * Math.Sin(rotation) + xcenter + xshift;
								yprime = (x - xcenter) * Math.Sin(rotation) + (y - ycenter) * Math.Cos(rotation) + ycenter + yshift;
							}
							else
							{
								xprime = (x - xcenter) * P0[0] + (y - ycenter) * P0[1] + xcenter + xshift;
								yprime = (x - xcenter) * P0[2] + (y - ycenter) * P0[3] + ycenter + yshift;
							}

							//now need to split out integer and decimal parts back into their own lists...
							intsx = Math.DivRem((int)((xprime)), 32, out fracx) * 32;
							fracx -= 16;//reset frac to be from -16
							intsy = Math.DivRem((int)((yprime)), 32, out fracy) * 32;
							fracy -= 16;//reset frac to be from -16
							IntsFits[0, j] = intsx;
							IntsFits[1, j] = intsy;
							FracFits[0, j] = fracx;
							FracFits[1, j] = fracy;
						}
					}

					IntsFile = IntsFile.Insert(IntsFile.LastIndexOf("."), "_RGSTRD");
					IntsFits.WriteImage(IntsFile, TypeCode.Int16, false);
					FracFile = FracFile.Insert(FracFile.LastIndexOf("."), "_RGSTRD");
					FracFits.WriteImage(FracFile, TypeCode.Int16, false);

					UVCONVERTLISTTOIMAGEBATCHFILES[i] = IntsFile;

					//rotate and shift the exposure array image so that it can be stacked later with merge
					//can rotate about center...then shift...all in JPMath
					//get the correct exposure map image
					string dedrift = "_deDrift";
					while (IntsFile.Contains(dedrift + "_deDrift"))
						dedrift += "_deDrift";
					string exparrayimagefile = IntsFile.Remove(IntsFile.IndexOf("XYInts")) + "ExpArrayImg";
					exparrayimagefile += dedrift + ".fits";

					FITSImage expfitsimg = new FITSImage(exparrayimagefile, null, true, true, false, false);
					double[,] exparr = expfitsimg.Image;

					int res = 2;
					if (expfitsimg.Header.GetKeyIndex("EXMAPRES", false) != -1)
						res = Convert.ToInt32(expfitsimg.Header.GetKeyValue("EXMAPRES"));
					xshift *= ((double)(res) / 32);
					yshift *= ((double)(res) / 32);
					xcenter *= ((double)(res) / 32);
					ycenter *= ((double)(res) / 32);
					int pad = 44 * res;

					if (Math.Abs(rotation) > 0.000001 / 180 * Math.PI || xshift != 0 || yshift != 0)
						exparr = JPMath.RotateShiftArray(exparr, -rotation, xcenter + pad, ycenter + pad, "bilinear", (int)Math.Round(xshift), (int)Math.Round(yshift), false);
					expfitsimg.SetImage(exparr, false, false);
					expfitsimg.WriteImage(TypeCode.Double, false);

					//The reason why you need to also shift the exposure array image and THEN create the new exposure list is because, at the edges, there would be differential
					//exposure times for each orbit relative to the combined orbits, just as with drift in a single orbit, for the merged images.
					//The exposure array images should be shifted and rotated as needed.
					//Then when the orbits are merged, the registered versions of the exposure array images should be combined too to get the master exposure list.
					//For example, if for one orbit an edge region was exposed for 0.9 of the total exposure time, this same region may not have been observed at all for all other orbits.
					//Therefore, the centroids there were not oberved for 0.9 of the entire exposure time, but 0.9 weighted for that orbits exposure time relative to the combined exposure time.
					//Even if a region in one orbit was fully exposed, it might not be exposed at all in later orbits.
					//Such a region's centroids have full weight for their own orbit, but for the combined orbits they should likewise be scaled to the total exposure time
				});
			}
			/*catch (Exception e)
			{
				MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
			}*/

			WAITBAR.DialogResult = DialogResult.OK;
		}

		private void RegistrationUVCentroidWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Registering file " + e.ProgressPercentage.ToString() + " of " + WAITBAR.ProgressBar.Maximum.ToString();
			WAITBAR.Refresh();//find all Update() and replace with Refresh()
		}

		private void RegistrationUVCentroidWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			DialogResult res = WAITBAR.DialogResult;
			this.Enabled = true;

			ListToImage8PixMenuItem.PerformClick();
			UVITMenu.HideDropDown();
			ConvertListToImgMenu.HideDropDown();

			WAITBAR.Hide();
			WAITBAR.Close();

			if (res == DialogResult.Cancel)
				return;

			/*if (MessageBox.Show("Completed registration of the centroid lists.  Would you like to convert them to images?","Images?",MessageBoxButtons.YesNo) == DialogResult.No)
				return;*/

			//for (int i = 0; i < UVCONVERTLISTTOIMAGEBATCHFILES.Length; i++)
			//	MessageBox.Show(UVCONVERTLISTTOIMAGEBATCHFILES[i]);

			UVCONVERTLISTTOIMAGEBATCH = true;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = UVCONVERTLISTTOIMAGEBATCHFILES.Length;
			WAITBAR.Text = "Creating images...";
			this.Enabled = false;
			ConvertUVCentroidListToImgWrkr.RunWorkerAsync(UVCONVERTLISTTOIMAGEBATCHFILES);
			WAITBAR.Show();
		}

		private void UVLoadAllMerged_Click(System.Object sender, EventArgs e)
		{
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.SelectedPath = (string)REG.GetReg("CCDLAB", "L2EventListPath"); ;
			fbd.Description = "Select the folder to scan for ALL most recent MERGED images";
			if (fbd.ShowDialog() == DialogResult.Cancel)
				return;
			REG.SetReg("CCDLAB", "L2EventListPath", fbd.SelectedPath);
			REG.SetReg("CCDLAB", "OpenFilesPath", fbd.SelectedPath);

			string[] mergeimgfiles = Directory.GetFiles(fbd.SelectedPath, "*MASTER*IMAGE*.fits", SearchOption.AllDirectories);
			Array.Sort(mergeimgfiles);
			if (mergeimgfiles.Length == 0)
			{
				MessageBox.Show("No files found...", "Error...");
				return;
			}
			int c = 0;
			for (int i = 0; i < mergeimgfiles.Length; i++)
			{
				string curdir = Path.GetDirectoryName(mergeimgfiles[i]);
				string[] dirimgfiles = Directory.GetFiles(curdir, "*MASTER*IMAGE*.fits");
				int ind = 0;
				for (int j = 1; j < dirimgfiles.Length; j++)
					if (dirimgfiles[j].Length > dirimgfiles[ind].Length)
						ind = j;

				mergeimgfiles[c] = dirimgfiles[ind];
				c++;
				i += dirimgfiles.Length - 1;
			}
			Array.Resize(ref mergeimgfiles, c);

			AUTOLOADIMAGESFILES = new string[mergeimgfiles.Length];
			Array.Copy(mergeimgfiles, AUTOLOADIMAGESFILES, mergeimgfiles.Length);
			AUTOLOADIMAGES = true;
			IMAGESET = new FITSImageSet();
			FMLoad_Click(sender, e);
			//FMLoad.PerformClick();
		}

		private void CombineUVCentroidListsMenuItem_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.DropDown.Close();
			ShiftAndRotateMenuItem.DropDown.Close();
			UVCombineCentroidListsMenuItem.DropDown.Close();

			string[] xyintsfiles;

			if (MergeXYIntsListFolderScanChck.Checked)
			{
				if (UVMERGEDIRS_INDEX == -1)
				{
					FolderBrowserDialog fbd = new FolderBrowserDialog();
					fbd.SelectedPath = (string)REG.GetReg("CCDLAB", "L2EventListPath"); ;
					fbd.Description = "Select the folder to scan for the most recent INTEGERS Lists (_XYInts_List)";
					if (fbd.ShowDialog() == DialogResult.Cancel)
						return;
					REG.SetReg("CCDLAB", "L2EventListPath", fbd.SelectedPath);
					REG.SetReg("CCDLAB", "OpenFilesPath", fbd.SelectedPath);

					//first lets figure out if we've selected only a single channel/filter directory, or, if we've selected FUV/NUV, or, if we've selected the parent directory of FUV/NUV
					//if only a single channel/filter dir, then simply proceed as below
					//if selected FUV/NUV and dir only contains a single channel/filter subdir, then also proceed as below
					//else, multiple channel/filter directories exist and must be processed in sequence, as per the below
					if (Directory.GetParent(fbd.SelectedPath).Name == "NUV" || Directory.GetParent(fbd.SelectedPath).Name == "FUV")//must be either of these ones if a single channel/filter has been selected
						UVMERGEDIRS = new string[] { fbd.SelectedPath };
					else if (Directory.Exists(fbd.SelectedPath + "\\NUV") || Directory.Exists(fbd.SelectedPath + "\\FUV") || new DirectoryInfo(fbd.SelectedPath).Name == "NUV" || new DirectoryInfo(fbd.SelectedPath).Name == "FUV")
					{
						//some parent has been selected and need to process the channel/filter subfolders one at a time
						if (new DirectoryInfo(fbd.SelectedPath).Name == "NUV" || new DirectoryInfo(fbd.SelectedPath).Name == "FUV")//then process the channel subdir filter folders
							UVMERGEDIRS = Directory.GetDirectories(fbd.SelectedPath);//these must be the single channel filter folders
						else//else must be the parent to both NUV and FUV
						{
							string[] Fuvdirs = new string[0];
							string[] Nuvdirs = new string[0];
							if (Directory.Exists(fbd.SelectedPath + "\\FUV"))
								Fuvdirs = Directory.GetDirectories(fbd.SelectedPath + "\\FUV");
							if (Directory.Exists(fbd.SelectedPath + "\\NUV"))
								Nuvdirs = Directory.GetDirectories(fbd.SelectedPath + "\\NUV");
							UVMERGEDIRS = new string[Fuvdirs.Length + Nuvdirs.Length];
							for (int i = 0; i < Fuvdirs.Length; i++)
								UVMERGEDIRS[i] = Fuvdirs[i];
							for (int i = Fuvdirs.Length; i < Fuvdirs.Length + Nuvdirs.Length; i++)
								UVMERGEDIRS[i] = Nuvdirs[i - Fuvdirs.Length];
						}
					}
					else if (Directory.GetDirectories(fbd.SelectedPath, "NUV", SearchOption.AllDirectories).Length > 0 || Directory.GetDirectories(fbd.SelectedPath, "FUV", SearchOption.AllDirectories).Length > 0)//typically when processing multiple epochs
					{
						string[] NUVdirs = Directory.GetDirectories(fbd.SelectedPath, "NUV", SearchOption.AllDirectories);
						string[] FUVdirs = Directory.GetDirectories(fbd.SelectedPath, "FUV", SearchOption.AllDirectories);

						ArrayList mergedirs = new ArrayList();
						for (int i = 0; i < NUVdirs.Length; i++)
							mergedirs.AddRange(Directory.GetDirectories(NUVdirs[i]));
						for (int i = 0; i < FUVdirs.Length; i++)
							mergedirs.AddRange(Directory.GetDirectories(FUVdirs[i]));

						if (mergedirs.Count == 0)
						{
							MessageBox.Show("I can't determine what to do...so I'm leaving. (A)");//cant tell what to do
							return;
						}

						UVMERGEDIRS = new string[mergedirs.Count];
						for (int i = 0; i < mergedirs.Count; i++)
							UVMERGEDIRS[i] = (string)mergedirs[i];
					}
					else
					{
						MessageBox.Show("I can't determine what to do...so I'm leaving. (B)");//cant tell what to do
						return;
					}

					//might have a directory where only one file is dedrifted but there are others without dedrift...
					//one option is to masterize the single and get rid of the other directories
					//another is that I can dedrift by other means and come back
					for (int i = 0; i < UVMERGEDIRS.Length; i++)
					{
						xyintsfiles = Directory.GetFiles(UVMERGEDIRS[i], "*XYInts_List*deDrift*RGSTRD*.fits", SearchOption.AllDirectories);
						if (xyintsfiles.Length == 1 && !xyintsfiles[0].Contains("MASTER"))
						{
							DialogResult res = MessageBox.Show("Error: A channel-filter directory was found which contains only a single de-drifted and registered image, but there are other folders with uncorrected centroid lists.\r\r 'Retry' to masterize the single and delete the other uncorrected directories.\r\r 'Cancel' to exit.\r\r Directory: " + UVMERGEDIRS[i], "Warning", MessageBoxButtons.RetryCancel);

							if (res == DialogResult.Cancel)
								return;

							int indlast = xyintsfiles[0].IndexOf("_XYInts");
							string test = xyintsfiles[0].Substring(0, indlast - 1);
							int indfirst = test.LastIndexOf("_");
							test = xyintsfiles[0].Substring(0, indfirst - 1);
							indfirst = test.LastIndexOf("_") + 1;
							string replacestr = xyintsfiles[0].Substring(indfirst, indlast - indfirst);

							string[] dirfiles = Directory.GetFiles(Path.GetDirectoryName(xyintsfiles[0]));
							for (int j = 0; j < dirfiles.Length; j++)
							{
								string newfile = dirfiles[j].Replace(replacestr, "__MASTER__");
								newfile = UVMERGEDIRS[i] + "\\" + newfile.Substring(newfile.LastIndexOf("\\"));
								File.Move(dirfiles[j], newfile);
							}
							string[] dirs = Directory.GetDirectories(UVMERGEDIRS[i]);
							for (int j = 0; j < dirs.Length; j++)
								Directory.Delete(dirs[j], true);
						}
					}

					//might have a masterized single which we want to ignore
					MASTERAUTOLOADADDIN = new ArrayList();
					int c = 0;
					for (int i = 0; i < UVMERGEDIRS.Length; i++)
						if (Directory.GetDirectories(UVMERGEDIRS[i]).Length == 0)//then it was a masterized single
						{
							string[] fils = Directory.GetFiles(UVMERGEDIRS[i], "*MASTER*RGSTRD*IMAGE*");
							int len = 0;
							int lenindex = -1;
							for (int a = 0; a < fils.Length; a++)
								if (fils[a].Length > len)
								{
									len = fils[a].Length;
									lenindex = a;
								}
							MASTERAUTOLOADADDIN.Add(fils[lenindex]);
							UVMERGEDIRS[i] = "";
							c++;
						}
					if (c != 0)
					{
						c = 0;
						for (int i = 0; i < UVMERGEDIRS.Length; i++)
							if (UVMERGEDIRS[i] != "")
							{
								UVMERGEDIRS[c] = UVMERGEDIRS[i];
								c++;
							}
						Array.Resize(ref UVMERGEDIRS, c);
					}
					else
						MASTERAUTOLOADADDIN = null;
					AUTOLOADIMAGESFILES = new string[UVMERGEDIRS.Length];
				}

				UVMERGEDIRS_INDEX++;
				//remove previously merged files because might want to start over at merge point
				xyintsfiles = Directory.GetFiles(UVMERGEDIRS[UVMERGEDIRS_INDEX], "*MASTER*");
				for (int i = 0; i < xyintsfiles.Length; i++)
					File.Delete(xyintsfiles[i]);
				//only want to merge the most recent xyintsfiles so must go through and sort this out
				//each XYInts file will be in its own directory, and this is where its dupes will be
				//we want only the most recent (longest file name length) dupe from each directory
				//when merging can only do so on deDrift & RGSTRD files, so if there are directories that couldn't be deDrift or not RGSTRD, don't use those files...
				xyintsfiles = Directory.GetFiles(UVMERGEDIRS[UVMERGEDIRS_INDEX], "*XYInts_List*deDrift*RGSTRD*.fits", SearchOption.AllDirectories);
				if (xyintsfiles.Length == 0)
				{
					UVMERGEDIRS_INDEX = -1;
					UVMERGEDIRS = null;
					AUTOLOADIMAGESFILES = null;
					MessageBox.Show("No files found...", "Error...");
					CombineUVCentroidListsMenuItem_Click(sender, e);
					return;
				}

				int cc = 0;
				Array.Sort(xyintsfiles);
				for (int i = 0; i < xyintsfiles.Length; i++)
				{
					string curdir = Path.GetDirectoryName(xyintsfiles[i]);
					string[] dirxyfiles = Directory.GetFiles(curdir, "*XYInts_List*deDrift*RGSTRD*.fits");
					int ind = 0;
					for (int j = 1; j < dirxyfiles.Length; j++)
						if (dirxyfiles[j].Length > dirxyfiles[ind].Length)
							ind = j;

					xyintsfiles[cc] = dirxyfiles[ind];
					cc++;
					i += dirxyfiles.Length - 1;
				}
				Array.Resize(ref xyintsfiles, cc);
			}
			else
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = true;
				string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS (*.fits)|*.fits";
				ofd.Title = "Select the Centroid INTEGERS Lists (_XYInts_List)";
				DialogResult res = ofd.ShowDialog();

				if (res != DialogResult.OK)
					return;

				dir = ofd.FileNames[0].Substring(0, ofd.FileNames[0].LastIndexOf("\\"));
				dir = dir.Substring(0, dir.LastIndexOf("\\"));
				REG.SetReg("CCDLAB", "L2EventListPath", dir);
				REG.SetReg("CCDLAB", "OpenFilesPath", dir);
				xyintsfiles = ofd.FileNames;
			}

			if (xyintsfiles.Length == 1)
			{
				MessageBox.Show("Need to select more than 1 file for merging...", "Error...");

				//SystemProcess.Start("Explorer.exe", DirectoryInfo(xyintsfiles[0]).Parent.FullName);

				//CombineUVCentroidListsMenuItem_Click(sender, e);
				return;
			}

			//check that filters/channels arent' mixed
			if (FITSImageSet.GetCommonDirectory(xyintsfiles) != Directory.GetParent(Directory.GetParent(xyintsfiles[0]).FullName).FullName)
			{
				MessageBox.Show("These do not seem to be indentical channel/filter images for merging...", "Error...");
				CombineUVCentroidListsMenuItem_Click(sender, e);
				return;
			}

			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = xyintsfiles.Length;
			if (UVMERGEDIRS != null)
				WAITBAR.Text = "(" + (UVMERGEDIRS_INDEX + 1) + " of " + UVMERGEDIRS.Length + ") " + "Merging Channel-Filter Directory: " + new DirectoryInfo(FITSImageSet.GetCommonDirectory(xyintsfiles)).Name;
			else
				WAITBAR.Text = "Merging Channel-Filter Directory: " + new DirectoryInfo(FITSImageSet.GetCommonDirectory(xyintsfiles)).Name;
			WAITBAR.ProgressBar.Value = 0;
			MergeCentroidListsWrkr.RunWorkerAsync(xyintsfiles);
			WAITBAR.ShowDialog();
		}

		private void MergeCentroidListsWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string[] filenames = (string[])e.Argument;
			string dir = filenames[0].Substring(0, filenames[0].LastIndexOf("\\"));
			dir = dir.Substring(0, dir.LastIndexOf("\\"));

			//array<FITSImage^> expmergeset = new array<FITSImage^>(filenames.Length);
			double[][,] expmergesetarrays = new double[filenames.Length][,];

			//for tracking relative exposure times
			double[] exptimes = new double[filenames.Length];//use physical time i.e. timelist max-min

			//for tracking parity errors and missing frames
			double[] nparityerr = new double[filenames.Length];
			double[] nmissingframes = new double[filenames.Length];
			int[] N_frames = new int[filenames.Length];
			int N_centroids = 0;

			for (int i = 0; i < filenames.Length; i++)
				N_centroids += (new FITSImage(filenames[i], null, true, false, false, false)).Height;

			int exparrayres = ExposureArrayResolutionDrop.SelectedIndex + 1;
			double dres = (double)(exparrayres);
			double pixres = 32 / dres;
			if (L1CentroidPaddingChck.Checked)
			{
				if (PCCentroidPaddingDrop.SelectedIndex == 0)
					UVPCMODEPADOFFSET = 22;
				if (PCCentroidPaddingDrop.SelectedIndex == 1)
					UVPCMODEPADOFFSET = 44;
			}
			else
				UVPCMODEPADOFFSET = 0;
			int offset = UVPCMODEPADOFFSET * exparrayres;
			FITSImage ff = new FITSImage(filenames[0], null, true, false, false, false);
			int winxsz = Convert.ToInt32(ff.Header.GetKeyValue("WIN_X_SZ"));
			int szx = (winxsz + 1) * exparrayres + offset * 2;
			int winysz = Convert.ToInt32(ff.Header.GetKeyValue("WIN_Y_SZ"));
			int szy = (winysz + 1) * exparrayres + offset * 2;
			int ox = Convert.ToInt32(ff.Header.GetKeyValue("WIN_XOFF"));
			int oy = Convert.ToInt32(ff.Header.GetKeyValue("WIN_YOFF"));

			//create the arrays for the cenrtoid lists (time list, frame list, flat list, XYInts list, XYFrac list
			double[] newTimeList = new double[N_centroids]; //save as uint at writetime
			double[] newFrameList = new double[N_centroids];//now has to be int32 because it won't roll over, save as uint at writetime
			double[] mergedFlatList = new double[N_centroids];
			double[] mergedExpList = new double[N_centroids];
			short[,] mergedXYIntsList = new short[2, N_centroids];
			short[,] mergedXYFracList = new short[2, N_centroids];
			double[] mergedBJDList = new double[N_centroids];
			short[,] mergedmdMmList = new short[2, N_centroids];
			//now run through the files and collect the centroid lists into the big list

			double[] prevendtimes = new double[filenames.Length];
			double[] prevendframs = new double[filenames.Length];
			int[] previndexes = new int[filenames.Length];
			for (int i = 0; i < prevendtimes.Length - 1; i++)
			{
				string tmefile = filenames[i].Remove(filenames[i].IndexOf("XYInts")) + "TimeList.fits";
				string Drift = "_deDrift";
				while (filenames[i].Contains(Drift))
				{
					tmefile = tmefile.Replace("TimeList", "TimeList_deDrift");
					Drift += "_deDrift";
				}
				string fmefile = tmefile.Replace("Time", "Frame");
				double[] timevec = FITSImage.ReadImageVectorOnly(tmefile, null, true);
				double[] framevec = FITSImage.ReadImageVectorOnly(fmefile, null, true);

				double time_per_frame = (timevec[timevec.Length - 1] - timevec[0]) / (framevec[framevec.Length - 1] - framevec[0]);

				prevendtimes[i + 1] = timevec[timevec.Length - 1] - timevec[0] + time_per_frame + prevendtimes[i];
				prevendframs[i + 1] = framevec[framevec.Length - 1] - framevec[0] + 1 + prevendframs[i];
				previndexes[i + 1] = timevec.Length + previndexes[i];
			}

			ParallelOptions opts = new ParallelOptions();
			if (L1MachineExtremeChck.Checked)
				opts.MaxDegreeOfParallelism = Environment.ProcessorCount;
			else
				opts.MaxDegreeOfParallelism = 1;
			int count = 0;
			object lockob = new object();

			Parallel.For(0, filenames.Length, (i, loopstate) =>
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					loopstate.Stop();// break;

				lock (lockob)
				{
					count++;
					MergeCentroidListsWrkr.ReportProgress(count);
				}

				string intfile = filenames[i];
				string frcfile = intfile.Replace("Ints", "Frac");

				string timfile = intfile.Remove(intfile.IndexOf("XYInts")) + "TimeList.fits";
				string dDrift = "_deDrift";
				while (intfile.Contains(dDrift))
				{
					timfile = timfile.Replace("TimeList", "TimeList_deDrift");
					dDrift += "_deDrift";
				}

				string frmefile = timfile.Replace("Time", "Frame");
				string fltfile = timfile.Replace("Time", "Flat");
				string BJDfle = timfile.Replace("Time", "BJD");
				string mdMmfle = timfile.Replace("TimeList", "XYmdMm_List");
				string expfle = timfile.Replace("TimeList", "ExpArrayImg");

				FITSImage intsfts = new FITSImage(intfile, null, true, false, false, false);
				double[,] intsarray = FITSImage.ReadImageArrayOnly(intfile, null, false);
				double[,] fracarray = FITSImage.ReadImageArrayOnly(frcfile, null, false);
				double[] timevec = FITSImage.ReadImageVectorOnly(timfile, null, false);
				double[] framevec = FITSImage.ReadImageVectorOnly(frmefile, null, false);
				double[] flatvec = FITSImage.ReadImageVectorOnly(fltfile, null, false);
				double[] BJDfits = FITSImage.ReadImageVectorOnly(BJDfle, null, false);
				double[,] mdMmvec = FITSImage.ReadImageArrayOnly(mdMmfle, null, false);
				expmergesetarrays[i] = FITSImage.ReadImageArrayOnly(expfle, null, false);

				//track the physical exposure times for drift series merge
				exptimes[i] = timevec[timevec.Length - 1] - timevec[0];
				expmergesetarrays[i] = JPMath.MatrixMultScalar(expmergesetarrays[i], exptimes[i], false);

				//track the stuff about parity errors and missing frames
				double npart = Convert.ToDouble(intsfts.Header.GetKeyValue("NPARTERR"));//number of parity errors in original (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
				double ncent = Convert.ToDouble(intsfts.Header.GetKeyValue("NCENTROD"));//number of centroids in original (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
				nparityerr[i] = npart * Convert.ToDouble(intsfts.Height) / ncent;//total number of parity errors proportioned for possibly split files and clipped files

				N_frames[i] = (int)(framevec[framevec.Length - 1] - framevec[0] + 1);
				double nmiss = Convert.ToDouble(intsfts.Header.GetKeyValue("NMISSFRM"));//number of missing frames in original (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
				double nfram = Convert.ToDouble(intsfts.Header.GetKeyValue("NFRAMES"));//number of frames in original  (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
				nmissingframes[i] += nmiss * (framevec[framevec.Length - 1] - framevec[0] + 1) / nfram;//total number of missing frames proportioned for possibly split files and clipped files

				//there should be no roll-overs in the time or frame lists for each set, so do soemthing to gather the total number of frames and time by gathering
				//the start & end time & frame for each set etc
				//then the merged list requires an artificial time & frame list which reproduces the same total time & total frames of the sum of the sets...
				//in this case we dont even need to create a merged time and frame list from the data, just need to gather the total frames & time and then make the lists
				double time_per_frame = (timevec[timevec.Length - 1] - timevec[0]) / (framevec[framevec.Length - 1] - framevec[0]);

				for (int j = 0; j < intsfts.Height; j++)
				{
					mergedXYIntsList[0, previndexes[i] + j] = (short)intsarray[0, j];
					mergedXYIntsList[1, previndexes[i] + j] = (short)intsarray[1, j];

					mergedXYFracList[0, previndexes[i] + j] = (short)fracarray[0, j];
					mergedXYFracList[1, previndexes[i] + j] = (short)fracarray[1, j];

					mergedmdMmList[0, previndexes[i] + j] = (short)mdMmvec[0, j];
					mergedmdMmList[1, previndexes[i] + j] = (short)mdMmvec[1, j];

					mergedFlatList[previndexes[i] + j] = flatvec[j];

					mergedBJDList[previndexes[i] + j] = BJDfits[j];

					/*if (j > 0 && timevec[j] != timevec[j - 1])//frame should change too...
						if (framevec[j] == framevec[j - 1])
							if (MessageBox.Show("Time changed but frame didn't in source data when merging centroid lists.  File: " + framefile + ". Last Frame = " + framevec[j - 1].ToString() + "; Current Frame = " + framevec[j].ToString() + "; Next Frame = " + framevec[j + 1].ToString() + "; Last Time = " + timevec[j - 1].ToString() + "; Current Time = " + timevec[j].ToString() + "; Next Time = " + timevec[j + 1].ToString() + ".  Would you like to stop?", "Warning...", MessageBoxButtons.YesNo) == DialogResult.Yes)
							{
								WAITBAR.CancelBtn.PerformClick();
								return;
							}*/

					newTimeList[previndexes[i] + j] = timevec[j] - timevec[0] + time_per_frame + prevendtimes[i];
					newFrameList[previndexes[i] + j] = framevec[j] - framevec[0] + 1 + prevendframs[i];
				}
			});

			double[,] expmergesetarraysSUM = new double[expmergesetarrays[0].GetLength(0), expmergesetarrays[0].GetLength(1)];

			Parallel.For(0, expmergesetarraysSUM.GetLength(0), x =>
			{
				for (int y = 0; y < expmergesetarraysSUM.GetLength(1); y++)
					for (int z = 0; z < expmergesetarrays.Length; z++)
						expmergesetarraysSUM[x, y] += expmergesetarrays[z][x, y];
			});

			expmergesetarraysSUM = JPMath.MatrixDivScalar(expmergesetarraysSUM, JPMath.Sum(exptimes, false), true);

			Parallel.For(0, mergedExpList.Length, j =>
			{
				int xpos = (int)((mergedXYIntsList[0, j] - ox * 32 + mergedXYFracList[0, j] + 16) / 32 * dres) + UVPCMODEPADOFFSET * (int)(dres);//reset integers to start at 0
				int ypos = (int)((mergedXYIntsList[1, j] - oy * 32 + mergedXYFracList[1, j] + 16) / 32 * dres) + UVPCMODEPADOFFSET * (int)(dres);//must add 16 to fractionals
				if (xpos >= 0 && ypos >= 0 && xpos < szx && ypos < szy)
					mergedExpList[j] = expmergesetarraysSUM[xpos, ypos];
			});

			double totframes = JPMath.Sum(N_frames, false);
			double parityredctn = JPMath.Sum(nparityerr, false) / (double)(N_centroids);//parity photometric reduction for actual file data after possible splitting and clipping
			double missframesredctn = JPMath.Sum(nmissingframes, false) / totframes;//parity photometric reduction for actual file data after possible splitting and clipping

			int indlast = filenames[0].IndexOf("_XYInts");
			string test = filenames[0].Substring(0, indlast - 1);
			int indfirst = test.LastIndexOf("_");
			test = filenames[0].Substring(0, indfirst - 1);
			indfirst = test.LastIndexOf("_") + 1;

			string intsfile = filenames[0].Remove(indfirst, indlast - indfirst);
			intsfile = intsfile.Insert(intsfile.IndexOf("_XYInts"), "__MASTER__");
			intsfile = dir + intsfile.Substring(intsfile.LastIndexOf("\\"));
			string fracfile = intsfile.Replace("XYInts", "XYFrac");

			string timefile = intsfile.Remove(intsfile.IndexOf("XYInts")) + "TimeList.fits";
			string deDrift = "_deDrift";
			while (intsfile.Contains(deDrift))
			{
				timefile = timefile.Replace("TimeList", "TimeList_deDrift");
				deDrift += "_deDrift";
			}

			string framefile = timefile.Replace("Time", "Frame");

			string flatfile = timefile.Replace("Time", "Flat");

			string expfile = timefile.Replace("TimeList", "ExpArrayList");

			string BJDfile = timefile.Replace("Time", "BJD");

			string mdMmfile = timefile.Replace("TimeList", "XYmdMm_List");

			WAITBAR.TextMsg.Text = "Writing the merged list...";
			WAITBAR.Refresh();

			FITSImage intsfits = new JPFITS.FITSImage(intsfile, mergedXYIntsList, false, true);
			FITSImageSet.GatherHeaders(filenames, intsfits);
			intsfits.Header.AddKey("TIMEMULT", filenames.Length.ToString(), "Multiplier for merged list int. time", -1);
			intsfits.Header.SetKey("PARTREDC", Math.Round(parityredctn, 5).ToString(), "Fractional int-time reduxn due to parity err", true, 14);
			intsfits.Header.SetKey("FRAMREDC", Math.Round(missframesredctn, 5).ToString(), "Fractional int - time reduxn due to lost frames", true, 14);
			intsfits.WriteImage(TypeCode.Int16, true);

			JPFITS.FITSImage fracfits = new JPFITS.FITSImage(fracfile, mergedXYFracList, false, true);
			fracfits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			fracfits.WriteImage(TypeCode.Int16, true);

			JPFITS.FITSImage timefits = new JPFITS.FITSImage(timefile, newTimeList, false, true);
			timefits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			timefits.WriteImage(TypeCode.UInt32, true);

			JPFITS.FITSImage framefits = new JPFITS.FITSImage(framefile, newFrameList, false, true);//now has to be int32 because it won't roll over
			framefits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			framefits.WriteImage(TypeCode.UInt32, true);

			JPFITS.FITSImage flatfits = new JPFITS.FITSImage(flatfile, mergedFlatList, false, true);
			flatfits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			flatfits.WriteImage(TypeCode.Double, true);

			FITSImage expfits = new FITSImage(expfile.Replace("ExpArrayList", "ExpArrayImg"), expmergesetarraysSUM, false, true);
			expfits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			expfits.WriteImage(expfile.Replace("ExpArrayList", "ExpArrayImg"), TypeCode.Double, true);

			expfits = new JPFITS.FITSImage(expfile, mergedExpList, false, true);
			expfits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			expfits.WriteImage(TypeCode.Double, true);

			JPFITS.FITSImage bjdfits = new JPFITS.FITSImage(BJDfile, mergedBJDList, false, true);
			bjdfits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			bjdfits.WriteImage(TypeCode.Double, true);

			JPFITS.FITSImage mdMmfits = new JPFITS.FITSImage(mdMmfile, mergedmdMmList, false, true);
			mdMmfits.Header.CopyHeaderFrom(intsfits.Header);// CopyHeader(intsfits);
			mdMmfits.WriteImage(TypeCode.Int16, true);

			e.Result = intsfile;
		}

		private void MergeCentroidListsWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Merging file " + (e.ProgressPercentage).ToString() + " of " + WAITBAR.ProgressBar.Maximum.ToString();
			WAITBAR.Refresh();
		}

		private void MergeCentroidListsWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				UVMERGEDIRS_INDEX = -1;
				UVMERGEDIRS = null;
				this.Enabled = true;
				return;
			}

			if (UVDeleteMergeDirsChck.Checked)
			{
				string dir = Directory.GetParent((string)e.Result).FullName;
				string[] mergedirs = Directory.GetDirectories(dir);
				for (int i = 0; i < mergedirs.Length; i++)
					Directory.Delete(mergedirs[i], true);
			}

			if (UVMERGEDIRS_INDEX == -1)//then create the single image right away
			{
				UVCONVERTLISTTOIMAGEBATCH = true;
				AUTOLOADIMAGESFILES = new string[] { (string)e.Result };
				WAITBAR.ProgressBar.Maximum = AUTOLOADIMAGESFILES.Length;
				WAITBAR.Text = "Creating image(s)...";
				ConvertUVCentroidListToImgWrkr.RunWorkerAsync(AUTOLOADIMAGESFILES);
				return;
			}
			else
			{
				AUTOLOADIMAGESFILES[UVMERGEDIRS_INDEX] = (string)e.Result;
				if (UVMERGEDIRS_INDEX + 1 < UVMERGEDIRS.Length)//then continue
				{
					WAITBAR.Hide();
					WAITBAR.Close();
					CombineUVCentroidListsMenuItem_Click(sender, e);
					return;
				}
				if (UVMERGEDIRS_INDEX + 1 == UVMERGEDIRS.Length)//then finished
				{
					UVMERGEDIRS_INDEX = -1;
					UVMERGEDIRS = null;
					UVITPOSTMERGE = true;

					UVCONVERTLISTTOIMAGEBATCH = true;
					WAITBAR.ProgressBar.Maximum = AUTOLOADIMAGESFILES.Length;
					WAITBAR.Text = "Creating image(s)...";
					ConvertUVCentroidListToImgWrkr.RunWorkerAsync(AUTOLOADIMAGESFILES);
					return;
				}
			}
		}

		private void NUVToFUVFrameMenuItem_Click(System.Object sender, EventArgs e)
		{
			TransformCoefATxt.Text = "0.84898";
			TransformCoefBTxt.Text = "0.53007";
			TransformCoefCTxt.Text = "0.53007";
			TransformCoefDTxt.Text = "-0.84898";
			TransformShiftXTxt.Text = "0";
			TransformShiftYTxt.Text = "0";
			TransformCenterXTxt.Text = "255";
			TransformCenterYTxt.Text = "255";

			GeneralTransformChck.Checked = false;
			GeneralTransformChck.PerformClick();
			UVITMenu.HideDropDown();
			ShiftAndRotateMenuItem.HideDropDown();
			UserDefinedShiftRotateMenuItem.HideDropDown();

			string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS (*.fits)|*.fits";
			dlg.Multiselect = true;
			dlg.Title = "Select the Centroid INTEGERS List (_XYInts_List)";
			DialogResult res = dlg.ShowDialog();
			if (res != DialogResult.OK)
				return;

			UVNUVTOFUVFILES = dlg.FileNames;
			UVNUVTOFUV = true;
			UserDefinedShiftRotateMenuItem_DoubleClick(sender, e);
		}

		private void BackgroundCountsPixelFrameTxt_TextChanged(System.Object sender, EventArgs e)
		{
			if (BackgroundCountsPixelFrameTxt.Text == "-" || BackgroundCountsPixelFrameTxt.Text == "-." || BackgroundCountsPixelFrameTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(BackgroundCountsPixelFrameTxt.Text);
			}
			catch
			{
				BackgroundCountsPixelFrameTxt.Text = "0";
			}
			REG.SetReg("CCDLAB", "BackgroundCountsPixelFrameTxt", BackgroundCountsPixelFrameTxt.Text);
		}

		private void CorrectBackgroundCountsChck_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.ShowDropDown();
			DeSaturateROICountsMenuItem.ShowDropDown();

			if (CorrectBackgroundCountsChck.Checked)
				BackgroundCountsPixelFrameTxt.Enabled = true;
			else
				BackgroundCountsPixelFrameTxt.Enabled = false;
		}

		private void DeSaturateROICountsMenuItem_DoubleClick(System.Object sender, EventArgs e)
		{
			UVITMenu.HideDropDown();
			DeSaturateROICountsMenuItem.HideDropDown();
			COG_PLOT.Close();

			int[] inds;
			if (DeSaturateCurrentImageChck.Text != "Current Image")
			{
				inds = new int[IMAGESET.Count];
				for (int i = 0; i < IMAGESET.Count; i++)
					inds[i] = i;
			}
			else
				inds = new int[] { FILELISTINDEX };

			double bg = 0, signal;
			double[] npts;
			double[] cog;
			double[] desatsounts = new double[inds.Length];
			double[] desatsounts_expt = new double[inds.Length];
			double[] desatsounts_meanBJD = new double[inds.Length];
			string[] desatsounts_filter = new string[inds.Length];
			string result = "";

			if (inds.Length > 1)
			{
				ProgressBar.Maximum = inds.Length;
				ProgressBar.Value = 0;
			}

			for (int i = 0; i < inds.Length; i++)
			{
				if (inds.Length > 1)
				{
					ProgressBar.Value++;
					ProgressBar.Refresh();
				}

				string imgname = IMAGESET[inds[i]].FullFileName;
				string dedrift = "";
				while (imgname.Contains(dedrift + "_deDrift"))
					dedrift += "_deDrift";

				string framesname = imgname.Substring(0, imgname.IndexOf("deFPN")) + "FrameList" + dedrift + ".fits";
				string timessname = framesname.Replace("Frame", "Time");
				string flatssname = framesname.Replace("Frame", "Flat");
				string expssname = framesname.Replace("Frame", "ExpArray");

				string intsname = imgname.Substring(0, imgname.IndexOf("_IMAGE"));
				intsname = intsname.Insert(intsname.IndexOf("deFPN"), "XYInts_List_") + ".fits";
				string fracsname = intsname.Replace("Ints", "Frac");

				double[] frames = JPFITS.FITSImage.ReadImageVectorOnly(framesname, null, true);
				double[] times = JPFITS.FITSImage.ReadImageVectorOnly(timessname, null, true);
				double[] flats = JPFITS.FITSImage.ReadImageVectorOnly(flatssname, null, true);
				double[] exps = JPFITS.FITSImage.ReadImageVectorOnly(expssname, null, true);
				JPFITS.FITSImage FracFits = new FITSImage(fracsname, null, true, true, false, true);
				JPFITS.FITSImage IntsFits = new FITSImage(intsname, null, true, true, false, true);

				string EXTXRNG = FracFits.Header.GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
				if (EXTXRNG == "")
					EXTXRNG = "0:511";//from L2 data
				string EXTYRNG = FracFits.Header.GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
				if (EXTYRNG == "")
					EXTYRNG = "0:511";//from L2 data
				int ix = EXTXRNG.IndexOf(":");
				int iy = EXTYRNG.IndexOf(":");
				double rx1 = Convert.ToDouble(EXTXRNG.Substring(0, ix));//range start
				double ry1 = Convert.ToDouble(EXTYRNG.Substring(0, iy));
				double rx2 = Convert.ToDouble(EXTXRNG.Substring(ix + 1));//range end
				double ry2 = Convert.ToDouble(EXTYRNG.Substring(iy + 1));

				string xoffset = FracFits.Header.GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
				if (xoffset == "")
					xoffset = FracFits.Header.GetKeyValue("WIN_XOFF");//from L2 data
				double ox = Convert.ToDouble(xoffset);//x offset
				string yoffset = FracFits.Header.GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
				if (yoffset == "")
					yoffset = FracFits.Header.GetKeyValue("WIN_YOFF");//from L2 data
				double oy = Convert.ToDouble(yoffset);//y offset

				double prec = 1;//check for the image precision...
				string strprec = IMAGESET[inds[i]].Header.GetKeyValue("IMAGPREC");
				if (strprec != "")
					prec = Convert.ToDouble(strprec);

				int offset = 0;
				string stroffset = IMAGESET[inds[i]].Header.GetKeyValue("PADOFSET");
				if (stroffset != "")
					offset = Convert.ToInt32(stroffset);

				int XSTART = XSUBRANGE[0] - offset * (int)(prec);
				int YSTART = YSUBRANGE[0] - offset * (int)(prec);
				int XEND = XSUBRANGE[XSUBRANGE.Length - 1] - offset * (int)(prec);
				int YEND = YSUBRANGE[YSUBRANGE.Length - 1] - offset * (int)(prec);

				double curframe = -1;//initialize frame number
				double ROIframecount = 0;//frame count
				double ROIrawcount = 0;//raw count - counter for centroids in ROI
				double flateff = 0;
				double expeff = 0;

				for (int k = 0; k < frames.Length; k++)
				{
					int xpos = (int)((IntsFits[0, k] - rx1 * 32 - ox * 32 + FracFits[0, k] + 16) / 32 * prec);
					int ypos = (int)((IntsFits[1, k] - ry1 * 32 - oy * 32 + FracFits[1, k] + 16) / 32 * prec);

					if (xpos >= XSTART && ypos >= YSTART && xpos <= XEND && ypos <= YEND)
					{
						ROIrawcount++;
						flateff += 1 / flats[k];
						expeff += 1 / exps[k];
						if (curframe != frames[k])
						{
							ROIframecount++;
							curframe = frames[k];
						}
					}
				}

				flateff /= ROIrawcount;
				expeff /= ROIrawcount;
				flateff = 1 / flateff;
				expeff = 1 / expeff;

				double totaltime = Convert.ToDouble(IMAGESET[inds[i]].Header.GetKeyValue("RDCDTIME"));
				double nframes = (frames[frames.Length - 1] - frames[0] + 1);//number of frames in raw EU data
				double listframecount = (double)(int)(nframes * (1 - Convert.ToDouble(IMAGESET[inds[i]].Header.GetKeyValue("FRAMREDC"))));//number of actual existing data frames (nframes adjusted for CRC missing frames)
				double listframeskips = nframes - listframecount;//number of frames which were CRC skipped
				double frames_per_sec = Math.Round(1000 * (frames[frames.Length - 1] - frames[0]) / (times[times.Length - 1] - times[0]), 4);

				//get the background counts
				if (CorrectBackgroundCountsChck.Checked)
				{
					if (inds.Length > 1)
						cog = JPFITS.PointSourceExtractor.COG(IMAGESET[inds[i]].GetSubImage(XSUBRANGE[SUBIMAGE_HWX], YSUBRANGE[SUBIMAGE_HWY], SUBIMAGE_HWX, SUBIMAGE_HWY), (int)COGIgnoreNPtsUpD.Value, out npts, out bg, out signal);
					else
						bg = Convert.ToDouble(BackgroundCountsPixelFrameTxt.Text);//total counts per pixel for final image near ROI, user entered from COG analysis
					bg = bg * SUBIMAGE.Length;//total bg counts in ROI - multiply bg counts per pixel by number of pixels in ROI
					bg = bg / listframecount;//rate of bg event in ROI per frame NOT adjusted for exposure array...so get it from good region
				}

				double zeros = listframecount - ROIframecount / expeff;//number of zero count frames adjusted for exposure array
				double Pzero = zeros / listframecount;//probability of zero-count frames per frame
				double correctedcountrate = Math.Log(1 / Pzero) - bg;//rate per frame
				double err = Math.Sqrt(ROIrawcount / Math.Exp(-correctedcountrate));

				desatsounts[i] = correctedcountrate / flateff * listframecount / totaltime;
				desatsounts_expt[i] = Convert.ToDouble(IMAGESET[inds[i]].Header.GetKeyValue("RDCDTIME"));
				desatsounts_meanBJD[i] = Convert.ToDouble(IMAGESET[inds[i]].Header.GetKeyValue("MEANBJD"));
				desatsounts_filter[i] = IMAGESET[inds[i]].Header.GetKeyValue("FILTERID");

				if (inds.Length == 1)
				{
					result += "ROI Window Size:	" + XSUBRANGE.Length.ToString() + "x" + YSUBRANGE.Length.ToString() + "\r\n";
					result += "ROI Window Location:	" + "X: " + (XSUBRANGE[(int)HalfWidthXUpD.Value] + 1).ToString() + ", Y: " + (YSUBRANGE[(int)HalfWidthYUpD.Value] + 1).ToString() + "\r\n";
					result += "ROI Raw Count:	" + ROIrawcount.ToString() + "\r\n";
					result += "ROI Flat:	" + flateff.ToString() + "\r\n";
					result += "ROI Exposure:	" + expeff.ToString() + "\r\n";
					result += "ROI Raw Exposure Count:	" + (ROIrawcount / expeff).ToString() + "\r\n";
					result += "N Frames in Observation:	" + nframes.ToString() + "\r\n";
					result += "Missing Frames:	" + listframeskips.ToString() + "\r\n";
					result += "Known Frames:	" + listframecount.ToString() + "\r\n";
					result += "Known Time:	" + totaltime.ToString() + "\r\n";
					result += "Frames per Second:	" + frames_per_sec.ToString() + "\r\n";
					result += "ROI Raw Data Frames:	" + ROIframecount.ToString() + "\r\n";
					result += "ROI Exposure Frames:	" + (ROIframecount / expeff).ToString() + "\r\n";
					result += "ROI 0 Count Frames:	" + zeros.ToString() + "\r\n";
					result += "ROI Exp P(0):	" + (Pzero).ToString() + "\r\n";
					result += "ROI Exp Count Rate/f:	" + (ROIrawcount / expeff / listframecount).ToString() + "\r\n";
					result += "ROI Exp Desaturated Rate/f:	" + correctedcountrate.ToString() + "\r\n";
					result += "ROI Exp/Flat Desaturated Rate/f:	" + (correctedcountrate / flateff).ToString() + "\r\n";
					result += "ROI Background Rate/f:	" + bg.ToString() + "\r\n";
					result += "ROI Exp Desaturated Rate/s:	" + (correctedcountrate * listframecount / totaltime).ToString() + "\r\n";
					result += "ROI Exp/Flat Desaturated Rate/s:	" + (correctedcountrate / flateff * listframecount / totaltime).ToString() + "\r\n";
					Clipboard.SetText(result);

					result = "";
					result += "ROI Window Size:			" + XSUBRANGE.Length.ToString() + "x" + YSUBRANGE.Length.ToString() + "\r\n";
					result += "ROI Window Location:		" + "X: " + (XSUBRANGE[(int)HalfWidthXUpD.Value] + 1).ToString() + ", Y: " + (YSUBRANGE[(int)HalfWidthYUpD.Value] + 1).ToString() + "\r\n";
					result += "ROI Raw Count:			" + ROIrawcount.ToString() + "\r\n";
					result += "ROI Flat:				" + flateff.ToString() + "\r\n";
					result += "ROI Exposure:			" + expeff.ToString() + "\r\n";
					result += "ROI Raw Exposure Count:		" + (ROIrawcount / expeff).ToString() + "\r\n";
					result += "N Frames in Observation:		" + nframes.ToString() + "\r\n";
					result += "Missing Frames:			" + listframeskips.ToString() + "\r\n";
					result += "Known Frames:			" + listframecount.ToString() + "\r\n";
					result += "Known Time:			" + totaltime.ToString() + "\r\n";
					result += "Frames per Second:			" + frames_per_sec.ToString() + "\r\n";
					result += "ROI Raw Data Frames:		" + ROIframecount.ToString() + "\r\n";
					result += "ROI Exposure Frames:		" + (ROIframecount / expeff).ToString() + "\r\n";
					result += "ROI 0 Count Frames:			" + zeros.ToString() + "\r\n";
					result += "ROI Exp P(0):			" + (Pzero).ToString() + "\r\n";
					result += "ROI Exp Count Rate/f:		" + (ROIrawcount / expeff / listframecount).ToString() + "\r\n";
					result += "ROI Exp Desaturated Rate/f:		" + correctedcountrate.ToString() + "\r\n";
					result += "ROI Exp/Flat Desaturated Rate/f:	" + (correctedcountrate / flateff).ToString() + "\r\n";
					result += "ROI Background Rate/f:		" + bg.ToString() + "\r\n";
					result += "ROI Exp Desaturated Rate/s:		" + (correctedcountrate * listframecount / totaltime).ToString() + "\r\n";
					result += "ROI Exp/Flat Desaturated Rate/s:	" + (correctedcountrate / flateff * listframecount / totaltime).ToString() + "\r\n";
					MessageBox.Show(result, "This table copied to clipboard...");
					return;
				}
				else
					result += desatsounts_meanBJD[i] + "	" + Math.Round(desatsounts[i], 4) + "			" + desatsounts_filter[i] + "	" + desatsounts_expt[i] + "\r\n";
			}
			ProgressBar.Value = 0;
			ProgressBar.Refresh();

			Clipboard.SetText(result);
			result = "MeanDBJ		Desaturated Count	Filter		Exposure Time" + "\r\n" + result;
			MessageBox.Show(result, "This table copied to clipboard...");
		}

		private void DeSaturateCurrentImageChck_Click(System.Object sender, EventArgs e)
		{
			if (DeSaturateCurrentImageChck.Text == "Current Image")
				DeSaturateCurrentImageChck.Text = "All Images";
			else
				DeSaturateCurrentImageChck.Text = "Current Image";

			DeSaturateCurrentImageChck.Checked = true;

			UVITMenu.ShowDropDown();
			DeSaturateROICountsMenuItem.ShowDropDown();
		}

		private void ExtractROICentroidListROIChck_Click(System.Object sender, EventArgs e)
		{
			ExtractROICentroidListROIChck.Checked = true;
			ExtractROICentroidListPSEChck.Checked = false;
			UVITMenu.ShowDropDown();
			ExtractROICentroidListMenuItem.ShowDropDown();
		}

		private void ExtractROICentroidListPSEChck_Click(System.Object sender, EventArgs e)
		{
			ExtractROICentroidListROIChck.Checked = false;
			ExtractROICentroidListPSEChck.Checked = true;
			UVITMenu.ShowDropDown();
			ExtractROICentroidListMenuItem.ShowDropDown();
		}

		private void ExtractROICentroidListMenuItem_Click(System.Object sender, EventArgs e)
		{
			if (ExtractROICentroidListPSEChck.Checked && PSES == null)
			{
				MessageBox.Show("No PSE found to use for extracting sources...try again.", "Error");
				return;
			}
			else if (!ExtractROICentroidListPSEChck.Checked && !ExtractROICentroidListROIChck.Checked)
			{
				MessageBox.Show("Please select either ROI or PSE source extraction...try again.", "Error");
				return;
			}

			if (!Directory.Exists(IMAGESET[FileListDrop.SelectedIndex].FilePath + "\\ROIExtractedLists\\"))
				Directory.CreateDirectory(IMAGESET[FileListDrop.SelectedIndex].FilePath + "\\ROIExtractedLists\\");
			else
				if (MessageBox.Show("Clear ROI list subdirectory directory and write new?", "Warning...", MessageBoxButtons.OKCancel) == DialogResult.OK)
			{
				Directory.Delete(IMAGESET[FileListDrop.SelectedIndex].FilePath + "\\ROIExtractedLists\\", true);
				Directory.CreateDirectory(IMAGESET[FileListDrop.SelectedIndex].FilePath + "\\ROIExtractedLists\\");
			}
			else
				return;

			WAITBAR = new WaitBar();
			if (ExtractROICentroidListPSEChck.Checked)
				WAITBAR.ProgressBar.Maximum = PSES[PSESINDEX].N_Sources;
			else
				WAITBAR.ProgressBar.Maximum = 1;
			WAITBAR.Text = "Extracting Centroid List(s)...";
			this.Enabled = false;
			ExtractROICentroidsWrkr.RunWorkerAsync();
			WAITBAR.ShowDialog();
		}

		private void ExtractROICentroidsWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string imgname = IMAGESET[FileListDrop.SelectedIndex].FullFileName;
			string dedrift = "";
			while (imgname.Contains(dedrift + "_deDrift"))
				dedrift += "_deDrift";

			string framesname = imgname.Substring(0, imgname.IndexOf("deFPN")) + "FrameList" + dedrift + ".fits";
			string timesname = framesname.Replace("Frame", "Time");
			string flatsname = framesname.Replace("Frame", "Flat");
			string expsname = framesname.Replace("FrameList", "ExpArrayList");
			string BJDSname = framesname.Replace("Frame", "BJD");
			string mdMmsname = framesname.Replace("FrameList", "XYmdMm_List");

			string intsname = imgname.Substring(0, imgname.IndexOf("_IMAGE"));
			intsname = intsname.Insert(intsname.IndexOf("deFPN"), "XYInts_List_") + ".fits";
			string fracsname = intsname.Replace("Ints", "Frac");

			JPFITS.FITSImage FrameFits = new FITSImage(framesname, null, true, true, false, true);
			JPFITS.FITSImage TimeFits = new FITSImage(timesname, null, true, true, false, true);
			JPFITS.FITSImage FracFits = new FITSImage(fracsname, null, true, true, false, true);
			JPFITS.FITSImage IntsFits = new FITSImage(intsname, null, true, true, false, true);
			JPFITS.FITSImage FlatFits = new FITSImage(flatsname, null, true, true, false, true);
			JPFITS.FITSImage ExpFits = new FITSImage(expsname, null, true, true, false, true);
			JPFITS.FITSImage BJDFits = new FITSImage(BJDSname, null, true, true, false, true);
			JPFITS.FITSImage mdMmFits = new FITSImage(mdMmsname, null, true, true, false, true);

			string EXTXRNG = FracFits.Header.GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
			if (EXTXRNG == "")
				EXTXRNG = "0:511";//from L2 data
			string EXTYRNG = FracFits.Header.GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
			if (EXTYRNG == "")
				EXTYRNG = "0:511";//from L2 data
			int ix = EXTXRNG.IndexOf(":");
			int iy = EXTYRNG.IndexOf(":");
			double rx1 = Convert.ToDouble(EXTXRNG.Substring(0, ix));//range start
			double ry1 = Convert.ToDouble(EXTYRNG.Substring(0, iy));
			double rx2 = Convert.ToDouble(EXTXRNG.Substring(ix + 1));//range end
			double ry2 = Convert.ToDouble(EXTYRNG.Substring(iy + 1));

			string xoffset = FracFits.Header.GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
			if (xoffset == "")
				xoffset = FracFits.Header.GetKeyValue("WIN_XOFF");//from L2 data
			double ox = Convert.ToDouble(xoffset);//x offset
			string yoffset = FracFits.Header.GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
			if (yoffset == "")
				yoffset = FracFits.Header.GetKeyValue("WIN_YOFF");//from L2 data
			double oy = Convert.ToDouble(yoffset);//y offset		

			double prec = 1;
			string strprec = IMAGESET[FileListDrop.SelectedIndex].Header.GetKeyValue("IMAGPREC");
			if (strprec != "")
				prec = Convert.ToDouble(strprec);

			int offset = 0;
			string stroffset = IMAGESET[FileListDrop.SelectedIndex].Header.GetKeyValue("PADOFSET");
			if (stroffset != "")
				offset = Convert.ToInt32(stroffset);

			int nsources = 1;
			if (ExtractROICentroidListPSEChck.Checked)
				nsources = PSES[PSESINDEX].N_Sources;

			for (int ei = 0; ei < nsources; ei++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;
				if (ei + 1 - WAITBAR.ProgressBar.Value >= nsources / 100)
					ExtractROICentroidsWrkr.ReportProgress(ei + 1);

				int XSTART, YSTART, XEND, YEND;

				if (ExtractROICentroidListROIChck.Checked)
				{
					XSTART = (XSUBRANGE[0] - offset * (int)(prec)) * 32 / (int)prec;
					YSTART = (YSUBRANGE[0] - offset * (int)(prec)) * 32 / (int)prec;
					XEND = (XSUBRANGE[XSUBRANGE.Length - 1] + 1 - offset * (int)(prec)) * 32 / (int)prec;
					YEND = (YSUBRANGE[YSUBRANGE.Length - 1] + 1 - offset * (int)(prec)) * 32 / (int)prec;
				}
				else
				{
					XSTART = ((int)(Math.Round(PSES[PSESINDEX].Centroids_X[ei])) - (int)PSES[PSESINDEX].KernelRadius - offset * (int)(prec)) * 32 / (int)prec;
					YSTART = ((int)(Math.Round(PSES[PSESINDEX].Centroids_Y[ei])) - (int)PSES[PSESINDEX].KernelRadius - offset * (int)(prec)) * 32 / (int)prec;
					XEND = ((int)(Math.Round(PSES[PSESINDEX].Centroids_X[ei])) + (int)PSES[PSESINDEX].KernelRadius + 1 - offset * (int)(prec)) * 32 / (int)prec;
					YEND = ((int)(Math.Round(PSES[PSESINDEX].Centroids_Y[ei])) + (int)PSES[PSESINDEX].KernelRadius + 1 - offset * (int)(prec)) * 32 / (int)prec;
				}

				int c = 0;
				bool[] ROItrue = new bool[FrameFits.Height];

				for (int i = 0; i < FrameFits.Height; i++)
				{
					int xpos = (int)(IntsFits[0, i] - rx1 * 32 - ox * 32 + FracFits[0, i] + 16.0);
					int ypos = (int)(IntsFits[1, i] - ry1 * 32 - oy * 32 + FracFits[1, i] + 16.0);

					if (xpos >= XSTART && ypos >= YSTART && xpos <= XEND && ypos <= YEND)
					{
						c++;
						ROItrue[i] = true;
					}
				}

				double[] ROItimelist = new double[c];
				double[] ROIframelist = new double[c];
				double[,] ROIintslist = new double[2, c];
				double[,] ROIfraclist = new double[2, c];
				double[] ROIflatlist = new double[c];
				double[] ROIexplist = new double[c];
				double[] ROIBJDlist = new double[c];
				double[,] ROImdMmlist = new double[2, c];

				c = 0;
				for (int i = 0; i < FrameFits.Height; i++)
				{
					if (ROItrue[i])
					{
						ROItimelist[c] = TimeFits[0, i];
						ROIframelist[c] = FrameFits[0, i];
						ROIintslist[0, c] = IntsFits[0, i];
						ROIintslist[1, c] = IntsFits[1, i];
						ROIfraclist[0, c] = FracFits[0, i];
						ROIfraclist[1, c] = FracFits[1, i];
						ROImdMmlist[0, c] = mdMmFits[0, i];
						ROImdMmlist[1, c] = mdMmFits[1, i];
						ROIflatlist[c] = FlatFits[0, i];
						ROIexplist[c] = ExpFits[0, i];
						ROIBJDlist[c] = BJDFits[0, i];
						c++;
					}
				}

				string appnd = "_ROIx" + (XSTART / (int)(prec)).ToString() + "-" + (XEND / (int)(prec)).ToString() + "y" + (YSTART / (int)(prec)).ToString() + "-" + (YEND / (int)(prec)).ToString() + ".fits";
				string timename = timesname.Substring(0, timesname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROItimeFits = new JPFITS.FITSImage(timename, ROItimelist, false, false);
				ROItimeFits.FilePath += "\\ROIExtractedLists\\";
				ROItimeFits.Header.CopyHeaderFrom(FrameFits.Header);
				ROItimeFits.Header.SetKey("EXTXRNG", ((double)(XSTART) / 32.0).ToString() + ":" + ((double)(XEND) / 32.0 - 1).ToString(), "Extraction X-Range", true, -1);
				ROItimeFits.Header.SetKey("EXTYRNG", ((double)(YSTART) / 32.0).ToString() + ":" + ((double)(YEND) / 32.0 - 1).ToString(), "Extraction Y-Range", true, -1);
				ROItimeFits.WriteImage(TypeCode.UInt32, false);

				string framename = framesname.Substring(0, framesname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROIframeFits = new JPFITS.FITSImage(framename, ROIframelist, false, false);
				ROIframeFits.FilePath += "\\ROIExtractedLists\\";
				ROIframeFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROIframeFits.WriteImage(TypeCode.UInt32, false);

				string intname = intsname.Substring(0, intsname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROIintsFits = new JPFITS.FITSImage(intname, ROIintslist, false, false);
				ROIintsFits.FilePath += "\\ROIExtractedLists\\";
				ROIintsFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROIintsFits.WriteImage(TypeCode.Int16, false);

				string fracname = fracsname.Substring(0, fracsname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROIfracFits = new JPFITS.FITSImage(fracname, ROIfraclist, false, false);
				ROIfracFits.FilePath += "\\ROIExtractedLists\\";
				ROIfracFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROIfracFits.WriteImage(TypeCode.Int16, false);

				string flatname = flatsname.Substring(0, flatsname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROIflatFits = new JPFITS.FITSImage(flatname, ROIflatlist, false, false);
				ROIflatFits.FilePath += "\\ROIExtractedLists\\";
				ROIflatFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROIflatFits.WriteImage(TypeCode.Double, false);

				string expname = expsname.Substring(0, expsname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROIexpFits = new JPFITS.FITSImage(expname, ROIexplist, false, false);
				ROIexpFits.FilePath += "\\ROIExtractedLists\\";
				ROIexpFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROIexpFits.WriteImage(TypeCode.Double, false);

				string BJDname = BJDSname.Substring(0, BJDSname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROIBJDSFits = new JPFITS.FITSImage(BJDname, ROIBJDlist, false, false);
				ROIBJDSFits.FilePath += "\\ROIExtractedLists\\";
				ROIBJDSFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROIBJDSFits.WriteImage(TypeCode.Double, false);

				string mdMmname = mdMmsname.Substring(0, mdMmsname.IndexOf(".fits")) + appnd;
				JPFITS.FITSImage ROImdMmFits = new JPFITS.FITSImage(mdMmname, ROImdMmlist, false, false);
				ROImdMmFits.FilePath += "\\ROIExtractedLists\\";
				ROImdMmFits.Header.CopyHeaderFrom(ROItimeFits.Header);
				ROImdMmFits.WriteImage(TypeCode.Int16, false);
			}
		}

		private void ExtractROICentroidsWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Extracted " + WAITBAR.ProgressBar.Value + " of " + WAITBAR.ProgressBar.Maximum + " (" + (100 * WAITBAR.ProgressBar.Value / WAITBAR.ProgressBar.Maximum + 1) + "%)";
			//WAITBAR.Refresh();
		}

		private void ExtractROICentroidsWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult != DialogResult.Cancel)
			{
				WAITBAR.Close();
				MessageBox.Show("ROI centroid list(s) extracted and written in image directory.", "Success...");
			}
			else
				if (MessageBox.Show("Delete partially completed extracted lists of sources?", "Delete?", MessageBoxButtons.YesNo) == DialogResult.Yes)
				Directory.Delete(IMAGESET[FileListDrop.SelectedIndex].FilePath + "\\ROIExtractedLists\\", true);

			this.Enabled = true;
		}

		private void ConsolidateNUVApplyToFUV_Click(System.Object sender, EventArgs e)
		{
			UVITMenu.DropDown.Close();
			ApplyDriftListMentuItem.DropDown.Close();
			ConsolidateNUVApplyToFUV.DropDown.Close();

			//get the drift series
			string[] driftFileNames;
			bool driftfolderconsol = ConsolidateDriftFolderChck.Checked;
			if (!driftfolderconsol)
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = true;
				string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS (*.drift)|*.drift";
				ofd.Title = "Select the MOST RECENT NUV *or* VIS DRIFT Series (*.drift)";
				DialogResult res = ofd.ShowDialog();
				if (res != DialogResult.OK)
					return;
				REG.SetReg("CCDLAB", "L2EventListPath", ofd.FileNames[0].Substring(0, ofd.FileNames[0].LastIndexOf("\\")));
				driftFileNames = ofd.FileNames;
			}
			else
			{
				if (!AUTOVISDRIFTAPPLY)
				{
					FolderBrowserDialog fbd = new FolderBrowserDialog();
					fbd.SelectedPath = (string)REG.GetReg("CCDLAB", "L2EventListPath");
					fbd.Description = "Select the MOST RECENT NUV *or* VIS DRIFT Series Folder (*.drift)";
					DialogResult res = fbd.ShowDialog();
					if (res == DialogResult.Cancel)
						return;
					REG.SetReg("CCDLAB", "L2EventListPath", fbd.SelectedPath);
					driftFileNames = Directory.GetFiles(fbd.SelectedPath, "*VIS*.drift", SearchOption.AllDirectories);
				}
				else
				{
					driftFileNames = Directory.GetFiles((string)REG.GetReg("CCDLAB", "L2EventListPath"), "*VIS*.drift", SearchOption.AllDirectories);
				}
			}
			//here I will make sure that there are no NUV/VIS drift series repeats....only want the highest order (MOST RECENT) series from each directory
			ArrayList files = new ArrayList();
			Array.Sort(driftFileNames);//sorted alphabetically now so same times/directories will be adjacent...not sure though where the last series would be in the filename repeats...
			for (int i = 0; i < driftFileNames.Length; i++)
			{
				string driftfiletime_i = driftFileNames[i].Substring(driftFileNames[i].IndexOf("_XYDrift") - 13, 13);
				int j = i + 1;

				string file_i = driftFileNames[i];
				bool seriesorders = false;
				while (j < driftFileNames.Length && driftfiletime_i == driftFileNames[j].Substring(driftFileNames[j].IndexOf("_XYDrift") - 13, 13))//must be in same directory
				{
					seriesorders = true;
					if (driftFileNames[j].Length > file_i.Length)
						file_i = driftFileNames[j];
					j++;
				}
				if (seriesorders)
				{
					i = j - 1;
				}
				files.Add(file_i);
			}
			string[] driftfiles = new string[files.Count];
			for (int i = 0; i < driftfiles.Length; i++)
				driftfiles[i] = (string)files[i];
			driftFileNames = driftfiles;

			JPFITS.FITSImage driftfits = new FITSImage(driftFileNames[0], null, true, false, false, true);
			string driftchannel = driftfits.Header.GetKeyValue("DETECTOR");
			if (driftchannel == "")
				driftchannel = driftfits.Header.GetKeyValue("CHANNEL");

			for (int i = 1; i < driftFileNames.Length; i++)
			{
				driftfits = new FITSImage(driftFileNames[i], null, true, false, false, false);
				string channel2 = driftfits.Header.GetKeyValue("DETECTOR");
				if (channel2 == "")
					channel2 = driftfits.Header.GetKeyValue("CHANNEL");

				if (driftchannel != channel2)
				{
					MessageBox.Show("Error: Mixed drift channels detected.  Please select *only* NUV or VIS Drift List files/folders...", "Error...", MessageBoxButtons.OK);
					ConsolidateNUVApplyToFUV_Click(sender, e);
					return;
				}
			}

		//need to get the time lists...
		reget:
			string[] TimeListNames = null;
			bool timefolderconsol = ConsolidateTimeListFolderChck.Checked;
			if (!timefolderconsol)
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Multiselect = true;
				string dir = (string)REG.GetReg("CCDLAB", "L2EventListPath");
				ofd.InitialDirectory = dir;
				ofd.Filter = "FITS (*.fits)|*.fits";
				ofd.Title = "Select the FUV *or* NUV TIME Series to apply drift to (*TimeList.fits)";
				DialogResult res = ofd.ShowDialog();
				if (res != DialogResult.OK)
					return;
				REG.SetReg("CCDLAB", "L2EventListPath", ofd.FileNames[0].Substring(0, ofd.FileNames[0].LastIndexOf("\\")));
				REG.SetReg("CCDLAB", "OpenFilesPath", ofd.FileNames[0].Substring(0, ofd.FileNames[0].LastIndexOf("\\")));
				TimeListNames = ofd.FileNames;
				for (int i = 0; i < TimeListNames.Length; i++)
					if (!TimeListNames[i].Contains("TimeList"))
					{
						MessageBox.Show("Error: Seems that one of the TimeList files is not what it should be: " + TimeListNames[i], "Error...", MessageBoxButtons.OK);
						goto reget;
					}
			}
			else
			{
				if (!AUTOVISDRIFTAPPLY)
				{
					FolderBrowserDialog fbd = new FolderBrowserDialog();
					fbd.SelectedPath = new DirectoryInfo((string)REG.GetReg("CCDLAB", "L2EventListPath")).Parent.FullName;
					fbd.Description = "Select the FUV, or NUV, or FUV/NUV Parent Folder to apply drift to";
					DialogResult res = fbd.ShowDialog();
					if (res == DialogResult.Cancel)
						return;

					if (Directory.Exists(fbd.SelectedPath + "\\FUV") || Directory.Exists(fbd.SelectedPath + "\\NUV"))//then we've selected the parent, so do autoapply
						AUTOVISDRIFTAPPLY = true;
					else
						TimeListNames = Directory.GetFiles(fbd.SelectedPath, "*TimeList.fits", SearchOption.AllDirectories);
				}

				if (AUTOVISDRIFTAPPLY)
				{
					string FUVdir = Directory.GetParent((string)REG.GetReg("CCDLAB", "L2EventListPath")).FullName + "\\FUV";
					string NUVdir = Directory.GetParent((string)REG.GetReg("CCDLAB", "L2EventListPath")).FullName + "\\NUV";
					FUVDIREXISTS = Directory.Exists(FUVdir);
					NUVDIREXISTS = Directory.Exists(NUVdir);

					if (Directory.Exists(FUVdir) && !DONUVDRIFTNOW)
						TimeListNames = Directory.GetFiles(FUVdir, "*TimeList.fits", SearchOption.AllDirectories);
					else
					{
						TimeListNames = Directory.GetFiles(NUVdir, "*TimeList.fits", SearchOption.AllDirectories);
						DONUVDRIFTNOW = false;
						FUVDIREXISTS = false;
					}
				}
			}
			JPFITS.FITSImage fits = new FITSImage(TimeListNames[0], null, true, false, false, true);
			string channel1 = fits.Header.GetKeyValue("DETECTOR");
			if (channel1 == "")
				channel1 = fits.Header.GetKeyValue("CHANNEL");
			for (int i = 1; i < TimeListNames.Length; i++)
			{
				fits = new FITSImage(TimeListNames[i], null, true, false, false, false);
				string channel2 = fits.Header.GetKeyValue("DETECTOR");
				if (channel2 == "")
					channel2 = fits.Header.GetKeyValue("CHANNEL");

				if (channel1 != channel2)
				{
					MessageBox.Show("Error: Mixed channels selected.  Please select *only* FUV or NUV TimeList files/folders...", "Error...", MessageBoxButtons.OK);
					goto reget;
				}
			}

			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = 100;
			WAITBAR.Text = "DeDrift " + TimeListNames.Length + " " + channel1 + " from " + driftFileNames.Length + " " + driftchannel + " Drift Series...";
			WAITBAR.ProgressBar.Value = 0;
			object[] arg = new object[2];
			arg[0] = driftFileNames;
			arg[1] = TimeListNames;
			DriftNUVtoFUVBGWrkr.RunWorkerAsync(arg);
			WAITBAR.ShowDialog();
		}

		private void DriftNUVtoFUVBGWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			object[] arg = (object[])e.Argument;
			string[] driftFileNames = (string[])arg[0];
			string[] TimeListNames = (string[])arg[1];
			string driftserieschannel = "";
			bool nuvTOfuv = false;

			//have the most recent drift series, now must search for possible 1st order series to consolidate all orders together first
			//first must sort the directories in sequence
			double[] dirtimes = new double[driftFileNames.Length];
			for (int i = 0; i < driftFileNames.Length; i++)
			{
				string path = driftFileNames[i].Substring(0, driftFileNames[i].LastIndexOf("\\"));
				string dirtime = path.Substring(path.LastIndexOf("_") + 1, 13);
				dirtimes[i] = Convert.ToDouble(dirtime);
			}
			Array.Sort(dirtimes, driftFileNames);
			string[] FilePaths = new string[driftFileNames.Length];
			for (int i = 0; i < driftFileNames.Length; i++)
				FilePaths[i] = driftFileNames[i].Substring(0, driftFileNames[i].LastIndexOf("\\"));
			//filepaths/names now sorted in time order

			//now go to each path, and do a first consolidation/compactification of the drift series in each path (observation) if there are 1st & 2nd Order etc. series
			//can assume that all series are processed equally, so if only find 1st order, no need to process this step
			string[] pathcompactseriesFILES = new string[FilePaths.Length];
			for (int i = 0; i < FilePaths.Length; i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;
				DriftNUVtoFUVBGWrkr.ReportProgress((i + 1) * 100 / FilePaths.Length, "Consolidating " + driftserieschannel + " drift series...");

				string[] pathdriftseries = Directory.GetFiles(FilePaths[i], "*.drift");
				int[] pathdriftserieslengths = new int[pathdriftseries.Length];//filename length gives the drift series order
				for (int j = 0; j < pathdriftserieslengths.Length; j++)
					pathdriftserieslengths[j] = pathdriftseries[j].Length;
				Array.Sort(pathdriftserieslengths, pathdriftseries);//now the driftseries are sorted in order Order..i.e., the last one is the shortest, highest order
				Array.Reverse(pathdriftserieslengths);
				Array.Reverse(pathdriftseries);//now the first one is the shortest

				JPFITS.FITSImage pathconsolidatedseries = new FITSImage(pathdriftseries[0], null, true, true, false, true);
				if (i == 0)
				{
					driftserieschannel = pathconsolidatedseries.Header.GetKeyValue("DETECTOR");
					if (driftserieschannel == "")
						driftserieschannel = pathconsolidatedseries.Header.GetKeyValue("CHANNEL");//raw file source or GSE
					if (driftserieschannel == "" || driftserieschannel != "NUV" && driftserieschannel != "VIS")//although FUV COULD be used for NUV...should never need...can do if needed
					{
						MessageBox.Show("Drift series channel not identifiable or FUV:  DETECTOR = " + driftserieschannel + "; Exiting.", "Error");
						WAITBAR.CancelBtn.PerformClick();
						return;
					}
					if (driftserieschannel == "NUV")
						if (pathconsolidatedseries.Header.GetKeyIndex("NUVTOFUV", false) != -1)
							nuvTOfuv = true;
				}
				for (int j = 1; j < pathdriftseries.Length; j++)
				{
					JPFITS.FITSImage pathconsolidatedseries_lowerorder = new FITSImage(pathdriftseries[j], null, true, true, false, true);//lower order is longer length

					Parallel.For(1, 3, m =>
					//for (int m = 1; m < 3; m++)
					{
						for (int k = 0; k < pathconsolidatedseries.Height; k++)
							pathconsolidatedseries[m, k] += pathconsolidatedseries_lowerorder[m, k];
					});
				}
				//pathconsolidatedseries now has all drift correction orders combined for this path
				//now compactify it to unique time elements only
				int cc = 0;
				double time = -1;
				for (int j = 0; j < pathconsolidatedseries.Height; j++)
				{
					if (time != pathconsolidatedseries[j])
					{
						cc++;
						time = pathconsolidatedseries[j];
					}
				}
				double[,] pathcompactseries = new double[3, cc];
				cc = 0;
				time = -1;
				for (int j = 0; j < pathconsolidatedseries.Height; j++)
				{
					if (time != pathconsolidatedseries[j])
					{
						pathcompactseries[0, cc] = pathconsolidatedseries[0, j];
						pathcompactseries[1, cc] = pathconsolidatedseries[1, j];
						pathcompactseries[2, cc] = pathconsolidatedseries[2, j];
						cc++;
						time = pathconsolidatedseries[j];
					}
				}
				//now have the pathcompactseries...write it in the path to disk as FITS .drift file...will delete later

				string pathcompactseriesFILE = driftFileNames[i];
				pathcompactseriesFILE = pathcompactseriesFILE.Insert(pathcompactseriesFILE.IndexOf("_XYDrift_List") + 13, "__COMPACT_");
				pathcompactseriesFILE = pathcompactseriesFILE.Remove(pathcompactseriesFILE.IndexOf("COMPACT") + 8, 7);
				JPFITS.FITSImage pathcompactseriesFITS = new FITSImage(pathcompactseriesFILE, pathcompactseries, false, true);
				pathcompactseriesFITS.WriteImage(TypeCode.Double, true);
				pathcompactseriesFILES[i] = pathcompactseriesFILE;
			}

			//String them together
			FITSImage fits;
			int c = 0;
			for (int i = 0; i < pathcompactseriesFILES.Length; i++)
			{
				fits = new FITSImage(pathcompactseriesFILES[i], null, true, false, false, true);
				c += fits.Height;
			}
			double[,] pathcompactseriesconsolidated = new double[3, c];
			double[,] NUVstartendtimes = new double[2, pathcompactseriesFILES.Length];//need this for later but good to produce here with this
			c = 0;
			for (int i = 0; i < pathcompactseriesFILES.Length; i++)
			{
				fits = new FITSImage(pathcompactseriesFILES[i], null, true, true, false, true);
				NUVstartendtimes[0, i] = fits[0, 0];
				NUVstartendtimes[1, i] = fits[0, fits.Height - 1];
				for (int k = 0; k < fits.Height; k++)
				{
					pathcompactseriesconsolidated[0, c] = fits[0, k];
					pathcompactseriesconsolidated[1, c] = fits[1, k];
					pathcompactseriesconsolidated[2, c] = fits[2, k];
					c++;
				}
				File.Delete(pathcompactseriesFILES[i]);//delete them so that they don't clutter the directories
			}

			//now have consolidated & compactified all selected NUV drift series into a single vector
			//now they must be used for FUV...they will need to be transformed to FUV coordinates
			double[] Pvistonuv = new double[] { 1.01075, -0.04301, -0.04301, -1.01075 };//from Shyam Feb 2017
			double[] Pnuvtofuv = new double[] { 0.84898, 0.53007, 0.53007, -0.84898 };//from Shyam Feb 2017
			double[] Pvistofuv = new double[] { 0, 0, 0, 0 };//???
			if (driftserieschannel == "NUV")
			{
				DriftNUVtoFUVBGWrkr.ReportProgress(0, "Transforming NUV drift series to FUV frame...");
				if (!nuvTOfuv)
				{
					Parallel.For(0, c, i=>
					//for (int i = 0; i < c; i++)
					{
						double dx = pathcompactseriesconsolidated[1, i];
						double dy = pathcompactseriesconsolidated[2, i];

						pathcompactseriesconsolidated[1, i] = Pnuvtofuv[0] * dx + Pnuvtofuv[1] * dy;//NUV to FUV
						pathcompactseriesconsolidated[2, i] = Pnuvtofuv[2] * dx + Pnuvtofuv[3] * dy;
					});
				}
				else//no change, NUV drift already in FUV coordinate frame
				{
					/*
					for (int i = 0; i < c; i++)
					{
						dx = pathcompactseriesconsolidated[1, i];
						dy = pathcompactseriesconsolidated[2, i];

						pathcompactseriesconsolidated[1, i] = pathcompactseriesconsolidated[1, i];
						pathcompactseriesconsolidated[2, i] = pathcompactseriesconsolidated[2, i];
					}*/
				}
			}

			fits = new FITSImage(TimeListNames[0], null, true, false, false, false);
			string applyserieschannel = fits.Header.GetKeyValue("DETECTOR");
			if (applyserieschannel == "")
				applyserieschannel = fits.Header.GetKeyValue("CHANNEL");
			if (driftserieschannel == "VIS")
			{
				if (applyserieschannel == "NUV" && fits.Header.GetKeyIndex("NUVTOFUV", false) != -1)
					nuvTOfuv = true;

				DriftNUVtoFUVBGWrkr.ReportProgress(0, "Transforming VIS drift series to " + applyserieschannel + " frame...");
				if (applyserieschannel == "FUV" || nuvTOfuv)
				{
					Parallel.For(0, c, i =>
					//for (int i = 0; i < c; i++)
					{
						double dx = pathcompactseriesconsolidated[1, i];
						double dy = pathcompactseriesconsolidated[2, i];

						double dxp = Pvistonuv[0] * dx + Pvistonuv[1] * dy;//VIS to NUV
						double dyp = Pvistonuv[2] * dx + Pvistonuv[3] * dy;

						pathcompactseriesconsolidated[1, i] = Pnuvtofuv[0] * dxp + Pnuvtofuv[1] * dyp;//NUV to FUV
						pathcompactseriesconsolidated[2, i] = Pnuvtofuv[2] * dxp + Pnuvtofuv[3] * dyp;

						/*pathcompactseriesconsolidated[1,i] = Pvistofuv[0]*dx + Pvistofuv[1]*dy;//VIS to FUV
						pathcompactseriesconsolidated[2,i] = Pvistofuv[2]*dx + Pvistofuv[3]*dy;*/
					});
				}
				else if (applyserieschannel == "NUV" && !nuvTOfuv)
				{
					Parallel.For(0, c, i =>
					//for (int i = 0; i < c; i++)
					{
						double dx = pathcompactseriesconsolidated[1, i];
						double dy = pathcompactseriesconsolidated[2, i];

						pathcompactseriesconsolidated[1, i] = Pvistonuv[0] * dx + Pvistonuv[1] * dy;
						pathcompactseriesconsolidated[2, i] = Pvistonuv[2] * dx + Pvistonuv[3] * dy;
					});
				}
				else
				{
					MessageBox.Show("Error...section 8");
					return;
				}
			}

			//now string together the FUV TimeLists
			c = 0;
			for (int i = 0; i < TimeListNames.Length; i++)
			{
				fits = new FITSImage(TimeListNames[i], null, true, false, false, false);
				c += fits.Height;
			}
			double[] FUVTimeList = new double[c];
			c = 0;
			for (int i = 0; i < TimeListNames.Length; i++)
			{
				fits = new FITSImage(TimeListNames[i], null, true, true, false, true);
				string FUVFrameListName = TimeListNames[i].Replace("TimeList", "FrameList");
				double[] frames = FITSImage.ReadImageVectorOnly(FUVFrameListName, null, true);
				double timeperframeby2 = Math.Round((fits[fits.Height - 1] - fits[0]) / (frames[fits.Height - 1] - frames[0]) / 2);
				for (int k = 0; k < fits.Height; k++)
				{
					FUVTimeList[c] = fits[k] + timeperframeby2;//use actual time per frame
					c++;
				}
			}

			//Now interpolate-spline the consolidated series and create FUVTimeList interpolation values
			DriftNUVtoFUVBGWrkr.ReportProgress(50, "Interpolating " + driftserieschannel + " drift series to " + applyserieschannel + "...");
			double[] t = new double[pathcompactseriesconsolidated.GetLength(1)];
			double[] xd = new double[pathcompactseriesconsolidated.GetLength(1)];
			double[] yd = new double[pathcompactseriesconsolidated.GetLength(1)];

			Parallel.For(0, t.Length, i =>
			//for (int i = 0; i < t.Length; i++)
			{
				t[i] = pathcompactseriesconsolidated[0, i];
				xd[i] = pathcompactseriesconsolidated[1, i];
				yd[i] = pathcompactseriesconsolidated[2, i];
			});

			double[] xdi = JPMath.Interpolate1d(t, xd, FUVTimeList, "akima", true);
			double[] ydi = JPMath.Interpolate1d(t, yd, FUVTimeList, "akima", true);
			DriftNUVtoFUVBGWrkr.ReportProgress(100, "Interpolating " + driftserieschannel + " drift series to " + applyserieschannel + "...");
			double[,] FUVinterpdriftseries = new double[2, FUVTimeList.Length];

			Parallel.For(0, FUVTimeList.Length, i =>
			//for (int i = 0; i < FUVTimeList.Length; i++)
			{
				FUVinterpdriftseries[0, i] = xdi[i];
				FUVinterpdriftseries[1, i] = ydi[i];
			});

			/*JPFITS.FITSImage consolidated = new FITSImage("c:\\consolidated.fits", pathcompactseriesconsolidated, false);
			consolidated.WriteImage(TypeCode.Double);
			FITSImage fuvt = new FITSImage("c:\\fuvtimes.fits", FUVTimeList, false);
			fuvt.WriteImage(TypeCode.Double);
			FITSImage fuvinterp = new FITSImage("c:\\fuvinterpxyd.fits", FUVinterpdriftseries, false);
			fuvinterp.WriteImage(TypeCode.Double);*/

			//Now, for EACH FUVTimeList, see if there is any time overlap of valid interpolation, and make its drift series to save for each one
			//so, need to compare the FUV TimeList with the NUVdriftseries time list to see where valid overlapping FUV times are; FUV times that are not valid can be set = -1
			//use the NUVstartendtimes to check for good FUV times...
			Parallel.For(0, FUVTimeList.Length, i =>
			//for (int i = 0; i < FUVTimeList.Length; i++)
			{
				bool brk = false;
				for (int j = 0; j < pathcompactseriesFILES.Length; j++)
					if (FUVTimeList[i] >= NUVstartendtimes[0, j] && FUVTimeList[i] <= NUVstartendtimes[1, j])
					{
						brk = true;
						break;
					}

				if (brk)
					return;// continue;apparently return is what you use for Parallel.For loops to continue...
				FUVTimeList[i] = -1;
			});

			//so now have FUV times which are from the original FUV lists and which are good times
			//now need to go through the individual FUV lists/directories and create drift series for those good times and save them in those directories
			//then after that or at the same time, would need to apply them to the centroid lists and make new de-drifted centroid lists
			int res = ExposureArrayResolutionDrop.SelectedIndex + 1;
			if (L1CentroidPaddingChck.Checked)
			{
				if (PCCentroidPaddingDrop.SelectedIndex == 0)
					UVPCMODEPADOFFSET = 22;
				if (PCCentroidPaddingDrop.SelectedIndex == 1)
					UVPCMODEPADOFFSET = 44;
			}
			else
				UVPCMODEPADOFFSET = 0;
			int offset = UVPCMODEPADOFFSET * res;
			double[,] EXPposureMAP = null;
			string FUVexpmapfile = null;
			string NUVexpmapfile = null;
			if (res == 1)
			{
				FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map.fits";
				NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map.fits";
				if (nuvTOfuv)
					NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map_NUVtoFUV.fits";
			}
			if (res == 2)
			{
				FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map x2.fits";
				NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2.fits";
				if (nuvTOfuv)
					NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2_NUVtoFUV.fits";
			}
			if (!File.Exists(FUVexpmapfile))
			{
				MessageBox.Show("FUV Exposure Map not found in UVIT_CalDB at " + FUVexpmapfile + ".  Please update your Cal_DB from jpostma@ucalgary.ca.  Exiting.", "Error...");
				WAITBAR.CancelBtn.PerformClick();
				return;
			}
			if (!File.Exists(NUVexpmapfile))
			{
				MessageBox.Show("NUV Exposure Map not found in UVIT_CalDB at " + NUVexpmapfile + ".  Please update your Cal_DB from jpostma@ucalgary.ca.  Exiting.", "Error...");
				WAITBAR.CancelBtn.PerformClick();
				return;
			}
			if (applyserieschannel == "FUV")
			{
				if (UVPCMODEPADOFFSET == 44)
					EXPposureMAP = FITSImage.ReadImageArrayOnly(FUVexpmapfile, new int[] { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
				if (UVPCMODEPADOFFSET == 22)
					EXPposureMAP = FITSImage.ReadImageArrayOnly(FUVexpmapfile, new int[] { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
				if (UVPCMODEPADOFFSET == 0)
					EXPposureMAP = FITSImage.ReadImageArrayOnly(FUVexpmapfile, new int[] { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
			}
			if (applyserieschannel == "NUV")
			{
				if (UVPCMODEPADOFFSET == 44)
					EXPposureMAP = FITSImage.ReadImageArrayOnly(NUVexpmapfile, new int[] { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
				if (UVPCMODEPADOFFSET == 22)
					EXPposureMAP = FITSImage.ReadImageArrayOnly(NUVexpmapfile, new int[] { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
				if (UVPCMODEPADOFFSET == 0)
					EXPposureMAP = FITSImage.ReadImageArrayOnly(NUVexpmapfile, new int[] { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
			}
			ArrayList createimagexyintslist = new ArrayList();

			int[] cntr = new int[TimeListNames.Length + 1];
			for (int i = 1; i < cntr.Length; i++)
				cntr[i] = (new FITSImage(TimeListNames[i - 1], null, true, false, false, false)).Height + cntr[i - 1];

			ParallelOptions opts = new ParallelOptions();
			if (L1MachineExtremeChck.Checked)
				opts.MaxDegreeOfParallelism = (int)((double)Environment.ProcessorCount / Math.PI);
			else
				opts.MaxDegreeOfParallelism = 1;
			object lockob = new object();
			int count = 0;

			Parallel.For(0, TimeListNames.Length, opts, (i, loopstate) =>
			//for (int i = 0; i < TimeListNames.Length; i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					loopstate.Stop();// continue;

				lock (lockob)
				{
					count++;
					DriftNUVtoFUVBGWrkr.ReportProgress(count * 100 / TimeListNames.Length, "Drift-correcting " + applyserieschannel + " centroids...");
				}

				string fuvtimelistName = TimeListNames[i];
				string fuvxyfraclistName = fuvtimelistName.Replace("TimeList", "XYFrac_List_deFPN_deDIST");
				string fuvxyintslistName = fuvtimelistName.Replace("TimeList", "XYInts_List_deFPN_deDIST");
				string fuvflatlistName = fuvtimelistName.Replace("TimeList", "FlatList");
				string fuvframelistName = fuvtimelistName.Replace("TimeList", "FrameList");
				string fuvBJDlistName = fuvtimelistName.Replace("TimeList", "BJDList");
				string fuvmdmmlistName = fuvtimelistName.Replace("TimeList", "XYmdMm_List");

				//if using this after trying self-correction, then self-correction files ALL need to be removed from the selected file directories
				//as those directories are drift corrected here.
				string dir = fuvtimelistName.Substring(0, fuvtimelistName.LastIndexOf("\\"));
				string[] olddrifts = Directory.GetFiles(dir, "*.drift");
				for (int k = 0; k < olddrifts.Length; k++)
					File.Delete(olddrifts[k]);
				string[] olddedrifts = Directory.GetFiles(dir, "*deDrift*");
				for (int k = 0; k < olddedrifts.Length; k++)
					File.Delete(olddedrifts[k]);

				//load the timelist and find out where it is good, if at all
				//they will be loaded in the same order as the string is contructed, so then can just equate them tracking indices
				FITSImage fuvtimelistFITS = new FITSImage(fuvtimelistName, null, true, true, false, false);
				int L = 0;//need to know how long the new lists will be...
				for (int j = 0; j < fuvtimelistFITS.Height; j++)
				{
					fuvtimelistFITS[j] = FUVTimeList[cntr[i] + j];
					if (fuvtimelistFITS[j] == -1)
						L++;
				}

				//if there are any good times in this list, not all values will be = -1
				if (L == fuvtimelistFITS.Height)//then no good times
					return;// continue;//go to next interationapparently return is equivalent to continue inside Parallel.For

				L = fuvtimelistFITS.Height - L;//need to know how long the new lists will be...

				//so now there are some good times
				//now make the dedrifted lists for this directory
				double[] fuvtimelistdedrift = new double[L];
				double[] fuvframelistdedrift = new double[L];
				double[] fuvflatlistdedrift = new double[L];
				double[] fuvBJDlistdedrift = new double[L];
				double[,] fuvxyintslistdedrift = new double[2, L];
				double[,] fuvxyfraclistdedrift = new double[2, L];
				double[,] fuvmdmmlistdedrift = new double[2, L];
				double[,] fuvdriftlist = new double[3, L];

				double[] fuvframelist = JPFITS.FITSImage.ReadImageVectorOnly(fuvframelistName, null, false);
				double[] fuvflatlist = JPFITS.FITSImage.ReadImageVectorOnly(fuvflatlistName, null, false);
				double[] fuvBJDlist = JPFITS.FITSImage.ReadImageVectorOnly(fuvBJDlistName, null, false);
				double[,] fuvxyintslist = JPFITS.FITSImage.ReadImageArrayOnly(fuvxyintslistName, null, false);
				double[,] fuvxyfraclist = JPFITS.FITSImage.ReadImageArrayOnly(fuvxyfraclistName, null, false);
				double[,] fuvmdmmlist = JPFITS.FITSImage.ReadImageArrayOnly(fuvmdmmlistName, null, false);

				int counter = 0;
				for (int j = 0; j < fuvtimelistFITS.Height; j++)
				{
					if (fuvtimelistFITS[j] == -1)
						continue;

					fuvtimelistdedrift[counter] = fuvtimelistFITS[j];
					fuvframelistdedrift[counter] = fuvframelist[j];
					fuvflatlistdedrift[counter] = fuvflatlist[j];
					fuvBJDlistdedrift[counter] = fuvBJDlist[j];
					fuvmdmmlistdedrift[0, counter] = fuvmdmmlist[0, j];
					fuvmdmmlistdedrift[1, counter] = fuvmdmmlist[1, j];
					fuvxyintslistdedrift[0, counter] = fuvxyintslist[0, j] - FUVinterpdriftseries[0, j + cntr[i + 1] - fuvtimelistFITS.Height];
					fuvxyintslistdedrift[1, counter] = fuvxyintslist[1, j] - FUVinterpdriftseries[1, j + cntr[i + 1] - fuvtimelistFITS.Height];
					fuvdriftlist[0, counter] = fuvtimelistFITS[j];
					fuvdriftlist[1, counter] = FUVinterpdriftseries[0, j + cntr[i + 1] - fuvtimelistFITS.Height];
					fuvdriftlist[2, counter] = FUVinterpdriftseries[1, j + cntr[i + 1] - fuvtimelistFITS.Height];
					fuvxyfraclistdedrift[0, counter] = fuvxyfraclist[0, j];
					fuvxyfraclistdedrift[1, counter] = fuvxyfraclist[1, j];
					counter++;
				}

				//check for initial noise frames in the FUV list...it would only be for the first time in the FUV time list
				counter = 0;
				for (int j = 0; j < fuvtimelistdedrift.Length; j++)
				{
					if (fuvtimelistdedrift[0] == fuvtimelistdedrift[j])
					{
						counter++;
						continue;
					}
					break;
				}
				if (counter >= 1000)//then resize the dedrifted lists and get rid of initial noise
				{
					double[] fuvtimelistdedriftTEMP = new double[L - counter];
					double[] fuvframelistdedriftTEMP = new double[L - counter];
					double[] fuvflatlistdedriftTEMP = new double[L - counter];
					double[] fuvBJDlistdedriftTEMP = new double[L - counter];
					double[,] fuvxyintslistdedriftTEMP = new double[2, L - counter];
					double[,] fuvxyfraclistdedriftTEMP = new double[2, L - counter];
					double[,] fuvmdmmlistdedriftTEMP = new double[2, L - counter];
					double[,] fuvdriftlistTEMP = new double[3, L - counter];

					for (int j = 0; j < L - counter; j++)
					{
						fuvtimelistdedriftTEMP[j] = fuvtimelistdedrift[j + counter];
						fuvframelistdedriftTEMP[j] = fuvframelistdedrift[j + counter];
						fuvflatlistdedriftTEMP[j] = fuvflatlistdedrift[j + counter];
						fuvBJDlistdedriftTEMP[j] = fuvBJDlistdedrift[j + counter];
						fuvmdmmlistdedriftTEMP[0, j] = fuvmdmmlistdedrift[0, j + counter];
						fuvmdmmlistdedriftTEMP[1, j] = fuvmdmmlistdedrift[1, j + counter];
						fuvxyintslistdedriftTEMP[0, j] = fuvxyintslistdedrift[0, j + counter];
						fuvxyintslistdedriftTEMP[1, j] = fuvxyintslistdedrift[1, j + counter];
						fuvxyfraclistdedriftTEMP[0, j] = fuvxyfraclistdedrift[0, j + counter];
						fuvxyfraclistdedriftTEMP[1, j] = fuvxyfraclistdedrift[1, j + counter];
						fuvdriftlistTEMP[0, j] = fuvdriftlist[0, j + counter];
						fuvdriftlistTEMP[1, j] = fuvdriftlist[1, j + counter];
						fuvdriftlistTEMP[2, j] = fuvdriftlist[2, j + counter];
					}

					fuvtimelistdedrift = fuvtimelistdedriftTEMP;
					fuvframelistdedrift = fuvframelistdedriftTEMP;
					fuvflatlistdedrift = fuvflatlistdedriftTEMP;
					fuvBJDlistdedrift = fuvBJDlistdedriftTEMP;
					fuvmdmmlistdedrift = fuvmdmmlistdedriftTEMP;
					fuvxyintslistdedrift = fuvxyintslistdedriftTEMP;
					fuvxyfraclistdedrift = fuvxyfraclistdedriftTEMP;
					fuvdriftlist = fuvdriftlistTEMP;
				}

				//update BJD0
				string BJD0 = fuvBJDlistdedrift[0].ToString("#.0000000");
				fuvtimelistFITS.Header.SetKey("BJD0", BJD0, "BJD of start of imaging", true, 14);

				//now create the exposure array if required
				bool createexposurearray = ApplyDriftCreateExpArrayChc.Checked;
				double[,] exposurearray;
				double dres = (double)(res);
				double pixres = 32 / dres;

				int winxsz = Convert.ToInt32(fuvtimelistFITS.Header.GetKeyValue("WIN_X_SZ"));
				int szx = (winxsz + 1) * res + offset * 2;
				int winysz = Convert.ToInt32(fuvtimelistFITS.Header.GetKeyValue("WIN_Y_SZ"));
				int szy = (winysz + 1) * res + offset * 2;
				int ox = Convert.ToInt32(fuvtimelistFITS.Header.GetKeyValue("WIN_XOFF"));
				int oy = Convert.ToInt32(fuvtimelistFITS.Header.GetKeyValue("WIN_YOFF"));

				if (createexposurearray)
				{
					double nframes = 0;
					exposurearray = new double[szx, szy];
					string detector = applyserieschannel;
					double[,] exposuremap = null;

					if (detector == "FUV")
					{
						if (winxsz == 511 && winysz == 511)
							exposuremap = EXPposureMAP;
						else
						{
							exposuremap = new double[szx, szy];

							for (int x = UVPCMODEPADOFFSET * res; x < szx - UVPCMODEPADOFFSET * res; x++)
								for (int y = UVPCMODEPADOFFSET * res; y < szy - UVPCMODEPADOFFSET * res; y++)
									exposuremap[x, y] = 1;
						}
					}
					if (detector == "NUV")
					{
						if (winxsz == 511 && winysz == 511)
							exposuremap = EXPposureMAP;
						else
						{
							exposuremap = new double[szx, szy];

							for (int x = UVPCMODEPADOFFSET * res; x < szx - UVPCMODEPADOFFSET * res; x++)
								for (int y = UVPCMODEPADOFFSET * res; y < szy - UVPCMODEPADOFFSET * res; y++)
									exposuremap[x, y] = 1;
						}
					}

					int xstart, xend, ystart, yend, expxstart, expystart;
					fuvdriftlist[1, 0] *= -1;//still don't understand why this needs to be done...
					fuvdriftlist[2, 0] *= -1;
					double oldxdrift = fuvdriftlist[1, 0];
					double oldydrift = fuvdriftlist[2, 0];
					if (fuvdriftlist[1, 0] < 0)
					{
						xstart = -(int)(fuvdriftlist[1, 0] / pixres);
						xend = szx;
						expxstart = 0;
					}
					else
					{
						xstart = 0;
						xend = szx - (int)(fuvdriftlist[1, 0] / pixres);
						expxstart = (int)(fuvdriftlist[1, 0] / pixres);
					}
					if (fuvdriftlist[2, 0] < 0)
					{
						ystart = -(int)(fuvdriftlist[2, 0] / pixres);
						yend = szy;
						expystart = 0;
					}
					else
					{
						ystart = 0;
						yend = szy - (int)(fuvdriftlist[2, 0] / pixres);
						expystart = (int)(fuvdriftlist[2, 0] / pixres);
					}
					fuvdriftlist[1, 0] *= -1;//reset
					fuvdriftlist[2, 0] *= -1;

					double increment = 0;
					double time = -1;
					for (int k = 0; k < fuvdriftlist.GetLength(1); k++)
					{
						if (time != fuvdriftlist[0, k])//new drift frame time...possibly new drift...also very first frame
						{
							time = fuvdriftlist[0, k];
							nframes++;

							fuvdriftlist[1, k] *= -1;
							fuvdriftlist[2, k] *= -1;

							//if it isnt moving then just gather the increments to apply after it does move
							//and it only needs to be applied after it moves by at least one pixel (or res?)
							if (Math.Abs(fuvdriftlist[1, k] - oldxdrift) < pixres && Math.Abs(fuvdriftlist[2, k] - oldydrift) < pixres)//will trigger for first frame so increment goes to 1 for it
							{
								increment++;//this starts at zero, so if this is the first frame, we get the first increment = 1
								fuvdriftlist[1, k] *= -1;//reset
								fuvdriftlist[2, k] *= -1;
								continue;
							}

							//then it has moved, so increment out everything from when it wasn't moving at the old positions

							for (int x = xstart; x < xend; x++)
								for (int y = ystart; y < yend; y++)
									if (exposuremap[x, y] == 1)
										exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;

							increment = 1;//increment for current frame

							//update moved position stuff...at least one of the drifts is moved 32 or more...update that one or both only
							if (Math.Abs(fuvdriftlist[1, k] - oldxdrift) >= pixres)
							{
								oldxdrift = fuvdriftlist[1, k];
								if (fuvdriftlist[1, k] < 0)
								{
									xstart = -(int)(fuvdriftlist[1, k] / pixres);
									xend = szx;
									expxstart = 0;
								}
								else
								{
									xstart = 0;
									xend = szx - (int)(fuvdriftlist[1, k] / pixres);
									expxstart = (int)(fuvdriftlist[1, k] / pixres);
								}
							}

							if (Math.Abs(fuvdriftlist[2, k] - oldydrift) >= pixres)
							{
								oldydrift = fuvdriftlist[2, k];
								if (fuvdriftlist[2, k] < 0)
								{
									ystart = -(int)(fuvdriftlist[2, k] / pixres);
									yend = szy;
									expystart = 0;
								}
								else
								{
									ystart = 0;
									yend = szy - (int)(fuvdriftlist[2, k] / pixres);
									expystart = (int)(fuvdriftlist[2, k] / pixres);
								}
							}

							fuvdriftlist[1, k] *= -1;//reset
							fuvdriftlist[2, k] *= -1;
						}
					}

					//increment out last gathered increments
					for (int x = xstart; x < xend; x++)
						for (int y = ystart; y < yend; y++)
							if (exposuremap[x, y] == 1)
								exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;

					//lastly normalize the array...
					exposurearray = JPMath.MatrixDivScalar(exposurearray, nframes, false);

					double[] dedriftedExposure = new double[fuvdriftlist.GetLength(1)];

					for (int k = 0; k < fuvdriftlist.GetLength(1); k++)
					{
						int xpos = (int)(fuvxyintslistdedrift[0, k] / pixres) + offset - ox * res;
						int ypos = (int)(fuvxyintslistdedrift[1, k] / pixres) + offset - oy * res;
						if (xpos < 0 || ypos < 0 || xpos >= szx || ypos >= szx)
							dedriftedExposure[k] = 0;
						else
							dedriftedExposure[k] = exposurearray[xpos, ypos];//applied like the flat...take the inverse at image creation time
					}

					fuvtimelistFITS.Header.SetKey("EXMAPRES", res.ToString(), "Exposure Map Resolution", true, 15);
					fuvtimelistFITS.Header.SetKey("EXMAPTIM", (fuvdriftlist[0, fuvdriftlist.GetLength(1) - 1] - fuvdriftlist[0, 0]).ToString(), "Exposure Map Time", true, 15);

					//write it
					string dedriftedExpFile = fuvtimelistName.Replace("TimeList", "ExpArrayList_deDrift");
					FITSImage dedriftedExpFits = new FITSImage(dedriftedExpFile, dedriftedExposure, false, false);
					dedriftedExpFits.Header.CopyHeaderFrom(fuvtimelistFITS.Header);//  CopyHeader(fuvtimelistFITS);
					dedriftedExpFits.WriteImage(TypeCode.Double, false);

					dedriftedExpFile = fuvtimelistName.Replace("TimeList", "ExpArrayImg_deDrift");
					FITSImage exp = new FITSImage(dedriftedExpFile, exposurearray, false, false);
					exp.Header.CopyHeaderFrom(fuvtimelistFITS.Header);//  CopyHeader(fuvtimelistFITS);
					exp.WriteImage(TypeCode.Double, false);
				}

				for (int k = 0; k < fuvdriftlist.GetLength(1); k++)
				{
					fuvdriftlist[1, k] *= -1;
					fuvdriftlist[2, k] *= -1;
				}
				//done exposure array

				//now have the dedrifted (drift corrected) set of lists for this directory
				//need to write them to their directory
				string fuvtimelistNamededrift = fuvtimelistName.Replace("TimeList", "TimeList_deDrift");
				string fuvframelistNamededrift = fuvtimelistName.Replace("TimeList", "FrameList_deDrift");
				string fuvflatlistNamededrift = fuvtimelistName.Replace("TimeList", "FlatList_deDrift");
				string fuvBJDlistNamededrift = fuvtimelistName.Replace("TimeList", "BJDList_deDrift");
				string fuvxyfraclistNamededrift = fuvtimelistName.Replace("TimeList", "XYFrac_List_deFPN_deDIST_deDrift");
				string fuvxyintslistNamededrift = fuvtimelistName.Replace("TimeList", "XYInts_List_deFPN_deDIST_deDrift");
				string fuvmdmmlistNamededrift = fuvtimelistName.Replace("TimeList", "XYmdMm_List_deDrift");
				string fuvdriftlistname = fuvtimelistName.Replace("TimeList", "XYDrift_List_" + driftserieschannel + "to" + applyserieschannel);
				fuvdriftlistname = fuvdriftlistname.Replace(".fits", ".drift");

				FITSImage FITS;
				FITS = new FITSImage(fuvtimelistNamededrift, fuvtimelistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.UInt32, false);
				FITS = new FITSImage(fuvframelistNamededrift, fuvframelistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.UInt32, false);
				FITS = new FITSImage(fuvflatlistNamededrift, fuvflatlistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.Double, false);
				FITS = new FITSImage(fuvBJDlistNamededrift, fuvBJDlistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.Double, false);
				FITS = new FITSImage(fuvmdmmlistNamededrift, fuvmdmmlistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.Int16, false);
				FITS = new FITSImage(fuvxyfraclistNamededrift, fuvxyfraclistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.Int16, false);
				FITS = new FITSImage(fuvxyintslistNamededrift, fuvxyintslistdedrift, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.Int16, false);
				FITS = new FITSImage(fuvdriftlistname, fuvdriftlist, false, false);
				FITS.Header.CopyHeaderFrom(fuvtimelistFITS.Header);// CopyHeader(fuvtimelistFITS);
				FITS.WriteImage(TypeCode.Double, false);

				//dedrifted lists now written
				lock (lockob)
				{
					createimagexyintslist.Add(fuvxyintslistNamededrift);
				}
			});

			if (createimagexyintslist.Count == 0)
			{
				e.Result = new string[] { "none" };
				return;
			}

			string[] xyintslist = new string[createimagexyintslist.Count];
			for (int i = 0; i < createimagexyintslist.Count; i++)
				xyintslist[i] = (string)createimagexyintslist[i];
			Array.Sort(xyintslist);
			e.Result = xyintslist;
		}

		private void DriftNUVtoFUVBGWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = (string)e.UserState;
			WAITBAR.Refresh();
		}

		private void DriftNUVtoFUVBGWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				this.Enabled = true;
				return;
			}

			//now create the images
			ConvertListToImgMenu_DropDownOpened(sender, e);
			ConvertListToImgMenu.HideDropDown();
			UVCONVERTLISTTOIMAGEBATCH = true;
			AUTOLOADIMAGESFILES = (string[])e.Result;
			if (AUTOLOADIMAGESFILES[0] == "none")
			{
				MessageBox.Show("No overlap between the drift series and the channel timelist(s)...no image created.", "Warning");
				WAITBAR.Hide();
				WAITBAR.Close();
				this.Enabled = true;
				return;
			}
			WAITBAR.ProgressBar.Maximum = AUTOLOADIMAGESFILES.Length;
			WAITBAR.Text = "Creating image(s)...";
			ConvertUVCentroidListToImgWrkr.RunWorkerAsync(AUTOLOADIMAGESFILES);
		}

		string UVITFilter_FWAngle_to_Index(string channel, double angle)
		{
			if (channel != "VIS" && channel != "NUV" && channel != "FUV")
			{
				MessageBox.Show("UVIT Channel '" + channel + "' not identified in UVITFilter...", "Error");
				return "";
			}

			if (channel == "FUV")
			{
				if (angle > 0 && angle < 3)
					return "F0";
				if (angle > 45 && angle < 48)
					return "F1";
				if (angle > 90 && angle < 93)
					return "F2";
				if (angle > 135 && angle < 138)
					return "F3";
				if (angle > 180 && angle < 183)
					return "F4";
				if (angle > 225 && angle < 228)
					return "F5";
				if (angle > 270 && angle < 273)
					return "F6";
				if (angle > 315 && angle < 318)
					return "F7";
			}

			if (channel == "NUV")
			{
				if (angle > 0 && angle < 2)
					return "F0";
				if (angle > 315 && angle < 318)
					return "F1";
				if (angle > 270 && angle < 273)
					return "F2";
				if (angle > 225 && angle < 228)
					return "F3";
				if (angle > 180 && angle < 183)
					return "F4";
				if (angle > 135 && angle < 138)
					return "F5";
				if (angle > 90 && angle < 93)
					return "F6";
				if (angle > 44 && angle < 48)
					return "F7";
			}

			if (channel == "VIS")
			{
				if (angle > 0 && angle < 2)
					return "F0";
				if (angle > 59 && angle < 62)
					return "F1";
				if (angle > 120 && angle < 123)
					return "F2";
				if (angle > 179 && angle < 182)
					return "F3";
				if (angle > 239 && angle < 242)
					return "F4";
				if (angle > 300 && angle < 303)
					return "F5";
			}

			return "NA";
		}

		string UVITFilter(string channel, string filterindex)
		{
			if (channel != "VIS" && channel != "NUV" && channel != "FUV")
			{
				MessageBox.Show("UVIT Channel '" + channel + "' not identified in UVITFilter...", "Error");
				return "";
			}

			if (channel == "FUV")
			{
				if (filterindex == "F0")
					return "BLOCK";
				if (filterindex == "F1")
					return "CaF2";
				if (filterindex == "F2")
					return "BaF2";
				if (filterindex == "F3")
					return "Sapphire";
				if (filterindex == "F4")
					return "Grating1";
				if (filterindex == "F5")
					return "Silica";
				if (filterindex == "F6")
					return "Grating2";
				if (filterindex == "F7")
					return "CaF2";
			}

			if (channel == "NUV")
			{
				if (filterindex == "F0")
					return "BLOCK";
				if (filterindex == "F1")
					return "Silica15";
				if (filterindex == "F2")
					return "NUVB15";
				if (filterindex == "F3")
					return "NUVB13";
				if (filterindex == "F4")
					return "Grating";
				if (filterindex == "F5")
					return "NUVB4";
				if (filterindex == "F6")
					return "NUVN2";
				if (filterindex == "F7")
					return "Silica117";
			}

			if (channel == "VIS")
			{
				if (filterindex == "F0")
					return "BLOCK";
				if (filterindex == "F1")
					return "VIS3";
				if (filterindex == "F2")
					return "VIS2";
				if (filterindex == "F3")
					return "VIS1";
				if (filterindex == "F4")
					return "NDF";
				if (filterindex == "F5")
					return "BK7";
			}

			return "NA";
		}

		private void CleanVISImagesMenuItem_Click(System.Object sender, EventArgs e)
		{
			FolderBrowserDialog fbd = new FolderBrowserDialog();

			fbd.SelectedPath = (string)REG.GetReg("CCDLAB", "OpenFilesPath");
			fbd.Description = "Please select the VIS directory or subirectory to clean.";
			DialogResult res = fbd.ShowDialog();
			if (res == DialogResult.Cancel)
				return;

			DATE = DateTime.Now;

			this.Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = 100;
			WAITBAR.Text = "Cleaning VIS Images";
			WAITBAR.ProgressBar.Value = 0;
			CleanVISBGWrkr.RunWorkerAsync(fbd.SelectedPath);
			WAITBAR.ShowDialog();
		}

		private void CleanVISBGWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string maindir = (string)e.Argument;
			string[] VISfiles = Directory.GetFiles(maindir, "*_VIS_*.fits", SearchOption.AllDirectories);
			Array.Sort(VISfiles);

			double threshold = Convert.ToDouble(L1CleanINTLineThreshold.Text);
			int N = Convert.ToInt32(L1CleanINTNPix.Text);

			bool doparallel = true;
			int intprog = 0;

			Parallel.For(0, VISfiles.Length, (i, loopstate) =>
			//for (int i = 0; i < VISfiles.Length; i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					loopstate.Stop();// break;

				if (i < VISfiles.Length / Environment.ProcessorCount)
					if (Environment.ProcessorCount * i * 100 / VISfiles.Length > intprog)
					{
						intprog++;
						CleanVISBGWrkr.ReportProgress(intprog, VISfiles.Length);
					}

				FITSImage VISfits = new FITSImage(VISfiles[i], null, true, true, false, true);

				if (CLEAN_UVITVISIMG(VISfits, threshold, N, !doparallel))
					VISfits.WriteImage(TypeCode.Int32, true);
			});
		}

		bool CLEAN_UVITVISIMG(JPFITS.FITSImage VISfits, double threshold, int occurences, bool do_parallel)
		{
			//double med = 0;//alwys zero if degradiented...which they have to be for this...so make sure... JPMath.Median(VISfits.Image);
			bool cleaned = false;

			ParallelOptions opts = new ParallelOptions();
			if (do_parallel)
				opts.MaxDegreeOfParallelism = Environment.ProcessorCount;
			else
				opts.MaxDegreeOfParallelism = 1;

			Parallel.For(1, 511, opts, y =>
			//for (int y = 1; y < 511; y++)
			{
				//check if there are too many values in the line some range above the median
				int c = 0;
				for (int x = 0; x < 512; x++)
				{
					if (Math.Abs(VISfits[x, y]) >= threshold)
						c++;

					if (c >= occurences)//then a bad line...replace bad pixels with average of previous line and next line pixels
					{
						cleaned = true;
						for (int xx = 0; xx < 512; xx++)
							if (Math.Abs(VISfits[xx, y]) >= threshold)
								VISfits[xx, y] = (VISfits[xx, y - 1] + VISfits[xx, y + 1]) / 2;
						break;
					}
				}
			});
			return cleaned;
		}

		private void CleanVISBGWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Value = e.ProgressPercentage;
			WAITBAR.TextMsg.Text = "Cleaned " + e.ProgressPercentage + "% of " + Convert.ToInt32(e.UserState).ToString() + " files...";
			WAITBAR.Refresh();
		}

		private void CleanVISBGWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			bool cancel = WAITBAR.DialogResult == DialogResult.Cancel;

			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;

			if (!cancel)
			{
				TimeSpan ts = DateTime.Now - DATE;
				MessageBox.Show("Finished cleaning the VIS images in: " + ts.Minutes + "m" + ts.Seconds + "s");
			}
		}

		private void TBC(byte[] arr, int naxis1, int naxis2)
		{
			//make a vector of the frameseqnums and check if they're not monotonic increasing; if not then the list needs a sort
			long[] frameseqnums = new long[naxis2];
			int[] positions = new int[naxis2];
			long lastframeseqnum = 0;
			bool monotonic = true;
			int byteindx = 0;
			for (int i = 0; i < naxis2; i++)
			{
				//frame sequence number - TTYPE3 = 'FrameSequenceNumber'
				byteindx = i * naxis1 + 36;
				frameseqnums[i] = ((long)(arr[byteindx]) << 56) | ((long)(arr[byteindx + 1]) << 48) | ((long)(arr[byteindx + 2]) << 40) | ((long)(arr[byteindx + 3]) << 32) | ((long)(arr[byteindx + 4]) << 24) | ((long)(arr[byteindx + 5]) << 16) | ((long)(arr[byteindx + 6]) << 8) | (long)(arr[byteindx + 7]);
				positions[i] = i;

				if (monotonic && frameseqnums[i] < lastframeseqnum)
					monotonic = false;

				lastframeseqnum = frameseqnums[i];
			}

			if (!monotonic)//then there was a jump back, so must sort on frameseqnums & their positions
			{
				Array.Sort(frameseqnums, positions);
				byte[] arrcopy = new byte[arr.Length];
				Array.Copy(arr, arrcopy, arr.Length);
				
				for (int i = 0; i < naxis2; i++)
					for (int j = 0; j < naxis1; j++)
						arr[i * naxis1 + j] = arrcopy[positions[i] * naxis1 + j];
			}

			//now just do a comparison to the reference for each frametime and correct frametime & TIME if needed
			long frametime = 0, tickcount = 0, difftime = 0, difftickms = 0, calcframetime = 0, bzero = 2147483648;
			uint frametimeu32 = 0;
			byte[] dbl = new byte[8];
			double TIME = 0, calcTIME = 0;
			for (int i = 0; i < naxis2; i++)
			{
				//check frametime & tickcount to see if it is true or offset enough from reference
				//frametime
				byteindx = i * naxis1 + 67;
				frametime = (long)((int)((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero);
				difftime = frametime - TBC_FRAMETIMEREF;

				//tickcount
				byteindx = i * naxis1 + 75;
				tickcount = (long)((int)((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero);
				difftickms = (tickcount - TBC_TICKCOUNTREF) * 1024;

				//now calculate to check for sufficient offset for FRAMETIME
				calcframetime = TBC_FRAMETIMEREF + difftickms;
				long N = (long)Math.Floor((double)(calcframetime) / 4294967295.0);
				calcframetime = calcframetime - N * 4294967295;
				if (calcframetime < 0)
					calcframetime += 4294967295;

				//if offset less than, say, 350s///jump is 524s, drift was maybe 70s/month...only do seversal day dumps..??......
				if (Math.Abs(calcframetime - frametime) > 70 * 1000)//if then do TBC
				{
					//frametime TBC
					byteindx = i * naxis1 + 67;
					frametime += 524288;
					frametimeu32 = (uint)((int)(frametime - bzero));
					arr[byteindx] = (byte)((frametimeu32 >> 24) & 0xff);
					arr[byteindx + 1] = (byte)((frametimeu32 >> 16) & 0xff);
					arr[byteindx + 2] = (byte)((frametimeu32 >> 8) & 0xff);
					arr[byteindx + 3] = (byte)(frametimeu32 & 0xff);
				}

				//TIME
				byteindx = i * naxis1 + 0;
				dbl[7] = arr[byteindx];
				dbl[6] = arr[byteindx + 1];
				dbl[5] = arr[byteindx + 2];
				dbl[4] = arr[byteindx + 3];
				dbl[3] = arr[byteindx + 4];
				dbl[2] = arr[byteindx + 5];
				dbl[1] = arr[byteindx + 6];
				dbl[0] = arr[byteindx + 7];
				TIME = BitConverter.ToDouble(dbl, 0);

				calcTIME = TBC_TIMEREF + (double)(difftickms) / 1000;
				if (Math.Abs(calcTIME - TIME) > 70)//if then do TBC
				{
					//TIME TBC
					byteindx = i * naxis1 + 0;
					TIME += (524288 / 1000);
					dbl = BitConverter.GetBytes(TIME);
					arr[byteindx] = dbl[7];
					arr[byteindx + 1] = dbl[6];
					arr[byteindx + 2] = dbl[5];
					arr[byteindx + 3] = dbl[4];
					arr[byteindx + 4] = dbl[3];
					arr[byteindx + 5] = dbl[2];
					arr[byteindx + 6] = dbl[1];
					arr[byteindx + 7] = dbl[0];
				}
			}
		}

		DialogResult TBC_Reference(string[] files)
		{
			TBC_TICKCOUNTREF = 0;//global int64 variable to be set
			TBC_FRAMETIMEREF = 0;//global int64 variable to be set
			TBC_TIMEREF = 0;//global double variable to be set
			int naxis1, naxis2;
			bool reffound = false;
			int byteindx = 0;
			byte[] arr;
			for (int fi = 0; fi < files.Length; fi++)
			{
				JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(files[fi], "DETECTOR_DATA");
				//arr = bt.GetTableByteArray();
				arr = bt.BINTABLEByteArray;
				naxis1 = bt.Naxis1;
				naxis2 = bt.Naxis2;
				//arr = FITSBinTable.GetExtensionAsByteArray(files[fi], "DETECTOR_DATA", naxis1, naxis2);
				uint tickcount = 0, frametime = 0, bzero = 2147483648;
				long lastframeseqnum = 0, frameseqnum = 0;
				double TIME = 0;
				byte[] dbl = new byte[8];

				//check if FrameSequenceNumber not monotonic increasing
				//if not then you can make the reference from this file
				for (int i = 0; i < naxis2; i++)
				{
					//frame sequence number - TTYPE3 = 'FrameSequenceNumber'
					byteindx = i * naxis1 + 36;
					frameseqnum = ((long)(arr[byteindx]) << 56) | ((long)(arr[byteindx + 1]) << 48) | ((long)(arr[byteindx + 2]) << 40) | ((long)(arr[byteindx + 3]) << 32) | ((long)(arr[byteindx + 4]) << 24) | ((long)(arr[byteindx + 5]) << 16) | ((long)(arr[byteindx + 6]) << 8) | (long)(arr[byteindx + 7]);

					//tick count - TTYPE14 = 'SecHdrTickCount'
					byteindx = i * naxis1 + 75;
					tickcount = (uint)((int)((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero);//MUST DO IT THIS WAY

					//frame time = 'SecHdrImageFrameTime'
					byteindx = i * naxis1 + 67;
					frametime = (uint)((int)((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero);//MUST DO IT THIS WAY

					//TIME
					byteindx = i * naxis1 + 0;
					dbl[7] = arr[byteindx];
					dbl[6] = arr[byteindx + 1];
					dbl[5] = arr[byteindx + 2];
					dbl[4] = arr[byteindx + 3];
					dbl[3] = arr[byteindx + 4];
					dbl[2] = arr[byteindx + 5];
					dbl[1] = arr[byteindx + 6];
					dbl[0] = arr[byteindx + 7];
					TIME = BitConverter.ToDouble(dbl, 0);

					if (frameseqnum < lastframeseqnum)//jump back discontinuity...the current frameseqnumber is the good one
					{
						reffound = true;
						TBC_TICKCOUNTREF = (long)tickcount;
						TBC_FRAMETIMEREF = (long)frametime;
						TBC_TIMEREF = TIME;
						break;
					}

					lastframeseqnum = frameseqnum;
				}

				if (reffound)
					break;
			}
			if (reffound)
			{
				REG.SetReg("CCDLAB", "TBC_TICKCOUNTREF", TBC_TICKCOUNTREF);
				REG.SetReg("CCDLAB", "TBC_FRAMETIMEREF", TBC_FRAMETIMEREF);
				REG.SetReg("CCDLAB", "TBC_TIMEREF", TBC_TIMEREF);
				return DialogResult.OK;
			}
			else
			{
				return MessageBox.Show("No reference currently determinable.  Would you like to:" + "\r\n \r\n" + "YES - use last known reference values" + "\r\n" + "NO - proceed without setting reference" + "\r\n" + "CANCEL - exit", "TBC Reference", MessageBoxButtons.YesNoCancel);
			}
		}

		private void UVFinalizeScienceBtn_DoubleClick(System.Object sender, EventArgs e)
		{
			WAITBAR = new WaitBar();
			WAITBAR.Text = "Finalize Science Products...";
			WAITBAR.ProgressBar.Maximum = 2 * IMAGESET.Count;
			if (UVFinalizeIncludeTablesChck.Checked)
				WAITBAR.ProgressBar.Maximum = 6 * IMAGESET.Count;
			UVFinalizeBGWrkr.RunWorkerAsync();
			WAITBAR.ShowDialog();
		}

		private void UVFinalizeBGWrkr_DoWork(System.Object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string[] imagefiles = IMAGESET.FullFileNames;
			if (imagefiles.Length > 1 && !IMAGESET[0].FileName.Contains("MASTER"))
			{
				MessageBox.Show("Couldn't make sense of what images to process...", "Error...");
				WAITBAR.CancelBtn.PerformClick();
				return;
			}

			if (imagefiles.Length == 1 && !IMAGESET[0].FileName.Contains("MASTER"))//perhaps there is only a single orbit image, and hence was never masterized...ex SMC campaign
			{
				//need to masterize the directory
				string filedir = Path.GetDirectoryName(imagefiles[0]);
				string pardir = Directory.GetParent(filedir).FullName;
				int indlast = imagefiles[0].IndexOf("_deFPN");
				string test = imagefiles[0].Substring(0, indlast - 1);
				int indfirst = test.LastIndexOf("_");
				test = imagefiles[0].Substring(0, indfirst - 1);
				indfirst = test.LastIndexOf("_") + 1;
				string replacestr = imagefiles[0].Substring(indfirst, indlast - indfirst);
				string[] dirfiles = Directory.GetFiles(filedir);
				for (int j = 0; j < dirfiles.Length; j++)
				{
					string newfile = dirfiles[j].Replace(replacestr, "__MASTER__");
					newfile = pardir + "\\" + newfile.Substring(newfile.LastIndexOf("\\"));
					File.Move(dirfiles[j], newfile);
					if (dirfiles[j] == imagefiles[0])
						imagefiles[0] = newfile;
				}
				Directory.Delete(filedir, true);
			}

			ArrayList allobjdirs = new ArrayList();
			//want to get the IMAGE images and their associated exposure maps
			for (int i = 0; i < imagefiles.Length; i++)
			{
				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;

				string objdir = Path.GetDirectoryName(Path.GetDirectoryName((Path.GetDirectoryName(imagefiles[i]))));

				if (allobjdirs.Count == 0)
					allobjdirs.Add(objdir);
				else
				{
					bool exists = false;
					for (int k = 0; k < allobjdirs.Count; k++)
						if (objdir == (string)allobjdirs[k])
						{
							exists = true;
							break;
						}
					if (!exists)
						allobjdirs.Add(objdir);
				}

				FITSImage image = new FITSImage(imagefiles[i], null, true, false, false, true);

				WAITBAR.Text = "Finalize Science Products: " + image.FileName.Substring(0, image.FileName.IndexOf("___MASTER"));

				string dedrift = "_deDrift";
				while (imagefiles[i].Contains(dedrift + "_deDrift"))
					dedrift += "_deDrift";
				string exparrayimagefile = imagefiles[i].Remove(imagefiles[i].IndexOf("MASTER")) + "MASTER___ExpArrayImg";
				exparrayimagefile += dedrift + ".fits";

				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;
				if (UVFinalizeIncludeExpMapChck.Checked)
				{
					FITSImage expfitsimg = new FITSImage(exparrayimagefile, null, true, true, false, true);
					expfitsimg.Header.CopyHeaderFrom(image.Header);// CopyHeader(image);

					//need to "debin" the exposure map to be same size as IMAGE
					double[,] debinexp = new double[4800, 4800];
					Parallel.For(0, 4800, x =>
					{
						for (int y = 0; y < 4800; y++)
							debinexp[x, y] = expfitsimg.Image[x / 4, y / 4];
					});

					expfitsimg.SetImage(debinexp, false, true);

					UVFinalizeBGWrkr.ReportProgress(0, "Writing exposure array");
					expfitsimg.FileName = expfitsimg.FileName.Remove(expfitsimg.FileName.IndexOf("MASTER")) + "MASTER_EXPARRAY_" + new DirectoryInfo(objdir).Name + ".fits";
					expfitsimg.FilePath = objdir;
					expfitsimg.WriteImage(TypeCode.Double, true);
					/*zipfiles.Add(expfitsimg.FullFileName);
					e.Result = zipfiles;*/
				}

				if (WAITBAR.DialogResult == DialogResult.Cancel)
					return;
				UVFinalizeBGWrkr.ReportProgress(0, "Writing image");
				string origfilename = image.FullFileName;
				image.FileName = image.FileName.Remove(image.FileName.IndexOf("MASTER")) + "MASTER_IMAGE_" + new DirectoryInfo(objdir).Name + ".fits";
				image.FilePath = objdir;
				File.Copy(origfilename, image.FullFileName, true);
				/*zipfiles.Add(image.FullFileName);
				e.Result = zipfiles;*/

				if (!UVFinalizeIncludeTablesChck.Checked)
					continue;

				//try
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					string xyintsname = imagefiles[i].Remove(imagefiles[i].IndexOf("_IMAGE")) + ".fits";
					xyintsname = xyintsname.Insert(xyintsname.IndexOf("deFPN_"), "XYInts_List_");
					string xydecsname = xyintsname.Replace("XYInts_List", "XYFrac_List");
					double[,] xyints = FITSImage.ReadImageArrayOnly(xyintsname, null, true);
					double[,] xydecs = FITSImage.ReadImageArrayOnly(xydecsname, null, true);
					short[] xcents = new short[xyints.GetLength(1)];
					short[] ycents = new short[xyints.GetLength(1)];

					Parallel.For(0, xyints.GetLength(1), j =>
					{
						xcents[j] = (short)(xyints[0, j] + xydecs[0, j] + 16);//use these as the array for the bintable now
						ycents[j] = (short)(xyints[1, j] + xydecs[1, j] + 16);//use these as the array for the bintable now
					});

					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					UVFinalizeBGWrkr.ReportProgress(0, "Writing centroid table");
					string binname = objdir + "\\" + image.FileName.Remove(image.FileName.IndexOf("MASTER")) + "MASTER_CENTROIDS_TABLE_" + new DirectoryInfo(objdir).Name + ".fits";
					/*zipfiles.Add(binname);
					e.Result = zipfiles;*/
					JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable();
					bt.SetTTYPEEntries(new string[] { "XCENTROID", "YCENTROID" }, new string[] { "pix*32", "pix*32" }, new object[] { xcents, ycents });
					bt.AddExtraHeaderKey("COMMENT", "Centroids are at ", "1/32 pixel precision.");
					bt.Write(binname, "CENTROIDS", true);

					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					UVFinalizeBGWrkr.ReportProgress(0, "Writing BJD table");
					string bjdname = xyintsname.Remove(xyintsname.IndexOf("XYInts_List")) + "BJDList" + dedrift + ".fits";
					double[] bjds = FITSImage.ReadImageVectorOnly(bjdname, null, true);
					binname = objdir + "\\" + image.FileName.Remove(image.FileName.IndexOf("MASTER")) + "MASTER_BJD_TABLE_" + new DirectoryInfo(objdir).Name + ".fits";
					/*zipfiles.Add(binname);
					e.Result = zipfiles;*/
					bt = new JPFITS.FITSBinTable();
					bt.AddTTYPEEntry("BaryCenterJD", true, "Day.day", bjds);
					bt.AddExtraHeaderKey("COMMENT", "BaryCenterJD ", "means solar system barycenter.");
					bt.Write(binname, "BJD", true);

					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					UVFinalizeBGWrkr.ReportProgress(0, "Writing flat table");
					string flatname = bjdname.Replace("BJDList", "FlatList");
					double[] flats = FITSImage.ReadImageVectorOnly(flatname, null, true);
					binname = objdir + "\\" + image.FileName.Remove(image.FileName.IndexOf("MASTER")) + "MASTER_FLAT_TABLE_" + new DirectoryInfo(objdir).Name + ".fits";
					/*zipfiles.Add(binname);
					e.Result = zipfiles;*/
					bt = new JPFITS.FITSBinTable();
					bt.AddTTYPEEntry("FlatWeight", true, "unity = 1", flats);
					bt.Write(binname, "FLAT", true);

					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					UVFinalizeBGWrkr.ReportProgress(0, "Writing exposure table");
					string expname = bjdname.Replace("BJDList", "ExpArrayList");
					double[] exps = FITSImage.ReadImageVectorOnly(expname, null, true);
					binname = objdir + "\\" + image.FileName.Remove(image.FileName.IndexOf("MASTER")) + "MASTER_EXPOSURE_TABLE_" + new DirectoryInfo(objdir).Name + ".fits";
					/*zipfiles.Add(binname);
					e.Result = zipfiles;*/
					bt = new JPFITS.FITSBinTable();
					bt.AddTTYPEEntry("ExposureMapWeight", true, "unity = 1", exps);
					bt.Write(binname, "EXPOSURE", true);
				}
				/*catch (Exception e)
				{
					MessageBox.Show(e.Data + "	" + e.InnerException + "	" + e.Message + "	" + e.Source + "	" + e.StackTrace + "	" + e.TargetSite);
				}*/
			}

			//chck delete intermdt
			if (UVFinalizeDeleteIntrmdtChck.Checked)
			{
				for (int i = 0; i < allobjdirs.Count; i++)
				{
					if (Directory.Exists((string)allobjdirs[i] + "\\FUV"))
					{
						UVFinalizeBGWrkr.ReportProgress(0, "Cleaning up FUV files in folder " + (i + 1) + " of " + allobjdirs.Count);
						Directory.Delete((string)allobjdirs[i] + "\\FUV", true);
					}
					if (Directory.Exists((string)allobjdirs[i] + "\\NUV"))
					{
						UVFinalizeBGWrkr.ReportProgress(0, "Cleaning up NUV files in folder " + (i + 1) + " of " + allobjdirs.Count);
						Directory.Delete((string)allobjdirs[i] + "\\NUV", true);
					}
					if (Directory.Exists((string)allobjdirs[i] + "\\VIS"))
					{
						UVFinalizeBGWrkr.ReportProgress(0, "Cleaning up VIS files in folder " + (i + 1) + " of " + allobjdirs.Count);
						Directory.Delete((string)allobjdirs[i] + "\\VIS", true);
					}
					if (Directory.Exists((string)allobjdirs[i] + "\\Digested L1"))
					{
						UVFinalizeBGWrkr.ReportProgress(0, "Cleaning up L1 files in folder " + (i + 1) + " of " + allobjdirs.Count);
						Directory.Delete((string)allobjdirs[i] + "\\Digested L1", true);
					}
				}
			}

			UVFinalizeBGWrkr.ReportProgress(0, "Please wait while I finish up...");

			if (allobjdirs.Count > 1)
			{
				string multipardir = Path.GetDirectoryName((string)allobjdirs[0]);
				string[] files = Directory.GetFiles(multipardir, "*MASTER_EXPARRAY*.fits", SearchOption.AllDirectories);
				for (int i = 0; i < files.Length; i++)
				{
					FITSImage fi = new FITSImage(files[i], null, false, false, false, false);
					fi.FilePath = multipardir;
					File.Move(files[i], fi.FullFileName);
				}
				files = Directory.GetFiles(multipardir, "*MASTER_IMAGE*.fits", SearchOption.AllDirectories);
				for (int i = 0; i < files.Length; i++)
				{
					FITSImage fi = new FITSImage(files[i], null, false, false, false, false);
					fi.FilePath = multipardir;
					File.Move(files[i], fi.FullFileName);
				}
				allobjdirs = new ArrayList();
				allobjdirs.Add(multipardir);
			}

			string[] zipfiles = Directory.GetFiles((string)allobjdirs[0], "*.fits");

			string ziplist = CCDLABPATH + "tozip.txt";
			StreamWriter sw = new StreamWriter(ziplist);
			for (int i = 0; i < zipfiles.Length; i++)
				sw.WriteLine((string)zipfiles[i]);
			sw.Close();

			string fname = (string)allobjdirs[0] + "\\" + new DirectoryInfo((string)allobjdirs[0]).Name;

			Process p = new Process();
			p.StartInfo.FileName = "c:\\Program Files\\7-Zip\\7zG.exe";
			p.StartInfo.Arguments = "\"a\" " + "\"-tzip\" " + "\"" + fname + "\" " + "\"@" + ziplist;
			p.Start();
			p.WaitForExit();
			if (p.ExitCode != 0)
			{
				for (int j = 0; j < zipfiles.Length; j++)
					if ((string)zipfiles[j] != "" && File.Exists((string)zipfiles[j]))
						File.Delete((string)zipfiles[j]);
				File.Delete(fname);
				WAITBAR.CancelBtn.PerformClick();
				return;
			}

			//chck move or copy
			if (UVFinalizeMoveOrCopyZipChck.Text.Contains("Move"))
				for (int i = 0; i < zipfiles.Length; i++)
					File.Delete((string)zipfiles[i]);

			WAITBAR.Close();
			REG.SetReg("CCDLAB", "UVFINALDIR", (string)allobjdirs[0]);
		}

		private void UVFinalizeBGWrkr_ProgressChanged(System.Object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			WAITBAR.ProgressBar.Increment(1);
			WAITBAR.TextMsg.Text = (string)e.UserState;
			WAITBAR.Refresh();
		}

		private void UVFinalizeBGWrkr_RunWorkerCompleted(System.Object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (WAITBAR.DialogResult == DialogResult.Cancel)
			{
				/*array<String^> zipfiles = (array<String^>^)e.Result;
				for (int j = 0; j < zipfiles.Length; j++)
					if (zipfiles[j] != "" && File.Exists(zipfiles[j]))
						File.Delete(zipfiles[j]);*/
			}
			else
				if (MessageBox.Show("Open Final Products Directory?", "Open Directory?", MessageBoxButtons.YesNo) == DialogResult.Yes)
					Process.Start("Explorer.exe", (string)REG.GetReg("CCDLAB", "UVFINALDIR"));
		}

		private void PSTrackDisplayClearBtn_Click(System.Object sender, EventArgs e)
		{
			UVITINTMODEDRIFTPOLYPOINTS = null;
			ImageWindow.Refresh();
		}

		private void invertWCSToolStripMenuItem_Click(System.Object sender, EventArgs e)
		{
			double CRPIX2 = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue("CRPIX2"));
			double CD1_2 = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue("CD1_2"));
			double CD2_2 = Convert.ToDouble(IMAGESET[FILELISTINDEX].Header.GetKeyValue("CD2_2"));

			CRPIX2 = 4800 - CRPIX2;
			CD1_2 = -CD1_2;
			CD2_2 = -CD2_2;

			IMAGESET[FILELISTINDEX].Header.SetKey("CRPIX2", CRPIX2.ToString("F8"), "WCS coordinate reference value on axis 2 (deg)", true, -1);
			IMAGESET[FILELISTINDEX].Header.SetKey("CD1_2", CD1_2.ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);
			IMAGESET[FILELISTINDEX].Header.SetKey("CD2_2", CD2_2.ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);

			IMAGESET[FILELISTINDEX].WCS = new JPFITS.WorldCoordinateSolution(IMAGESET[FILELISTINDEX].Header);

			WCSCopyToLoadedImgs.PerformClick();

			if (WCSRADecShowChck.Checked)
				WCSRADecShowChck.PerformClick();

			WCSRADecShowChck.PerformClick();
		}

	}
}