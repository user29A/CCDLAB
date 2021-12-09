using System;
using System.IO;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.Threading;
using System.Collections.Concurrent;
using JPFITS;

namespace CCDLAB
{
	public partial class Form1
	{
		private void BatchMakeListBtn_Click(object sender, EventArgs e)
		{
			FITSFINDER = new JPFITS.FITSFinder();
			if (FITSFINDER.ShowDialog() == DialogResult.Cancel)//search was cancelled
				return;

			if (FITSFINDER.DialogResult == DialogResult.OK)
			{
				int numfilesfound = FITSFINDER.FoundFiles.Length;
				if (numfilesfound == 0)//no files found
				{
					MessageBox.Show("No Files Found Matching File Extension or Search Criteria...", "Warning");
					BatchMakeListBtn.PerformClick();
				}
				else//found some files, so now make string array of just file names for showing in FO list below
				{
					FITSFINDERFILES = FITSFINDER.FoundFiles;

					FITSFOUND = new JPFITS.FITSFound(FITSFINDERFILES);
					FITSFOUND.LoadImageSetBtn.Text = "Use Selected for Batch List";
					FITSFOUND.AddImageSetBtn.Enabled = false;
					FITSFOUND.NumFilesTxt.Text = "Please Choose File(s) to Save...";
					FITSFOUND.Text = System.String.Concat("Found ", numfilesfound.ToString(), " files...");
					FITSFOUND.ShowDialog();
					int Ninds = FITSFOUND.FileListTxt.SelectedIndices.Count;
					if (Ninds == 0 && FITSFOUND.DialogResult != System.Windows.Forms.DialogResult.Cancel)//no files selected but asked to load files (!cancel)
					{
						MessageBox.Show("No Files Selected!...", "Error");
						BatchMakeListBtn.PerformClick();
					}
					else
					{
						string[] selectfiles = new string[Ninds];
						for (int j = 0; j < Ninds; j++)
						{
							selectfiles[j] = FITSFINDERFILES[FITSFOUND.FileListTxt.SelectedIndices[j]];
						}
						if (FITSFOUND.DialogResult == System.Windows.Forms.DialogResult.Cancel)
						{
							BatchMakeListBtn.PerformClick();
							return;
						}
						if (FITSFOUND.DialogResult == DialogResult.OK)//then just Use Selected for Batch List
						{
							BATCHLIST = selectfiles;
							BatchListNameTxt.Text = String.Concat("List: ", BATCHLIST.Length.ToString(), " files.");
							BatchListViewPanel.Text = "Quick Viewing: File 0 of " + BATCHLIST.Length.ToString();
							BatchGoToUpD.Maximum = BATCHLIST.Length;
							BatchListViewPanel.Enabled = true;
							BatchComputeBtn.Enabled = true;
						}
						else//the only other option is the list was saved
						{
							string filelist = Convert.ToString(JPFITS.REG.GetReg("CCDLAB", "FoundFileList"));
							FileStream fs = new FileStream(filelist, FileMode.Open);
							StreamReader sr = new StreamReader(fs);
							int NFiles = Convert.ToInt32(sr.ReadLine());
							BATCHLIST = new string[NFiles];
							for (int i = 0; i < NFiles; i++)
								BATCHLIST[i] = sr.ReadLine();
							sr.Close();
							fs.Close();
							BatchListNameTxt.Text = String.Concat("List: ", filelist.Substring(filelist.LastIndexOf("\\") + 1), ", ", NFiles, " files.");
							BatchListViewPanel.Text = "Quick Viewing: File 0 of " + NFiles.ToString();
							BatchGoToUpD.Maximum = NFiles;
							BatchListViewPanel.Enabled = true;
							BatchComputeBtn.Enabled = true;
						}
					}
				}
			}
		}

		private void BatchOpenListBtn_Click(object sender, EventArgs e)
		{
			string dir = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "CCDLAB File List (*.CFL)|*.CFL";

			if (dlg.ShowDialog() != DialogResult.OK)
				return;

			FileStream fs = new FileStream(dlg.FileName, FileMode.Open);
			StreamReader sr = new StreamReader(fs);
			int NFiles = Convert.ToInt32(sr.ReadLine());
			BATCHLIST = new string[NFiles];
			for (int i = 0; i < NFiles; i++)
			{
				BATCHLIST[i] = sr.ReadLine();
				FileInfo f = new FileInfo(BATCHLIST[i]);
				if (!f.Exists)
				{
					MessageBox.Show("Some of the files don't exist on the specified path.  The list file may be old.", "Error...");
					sr.Close();
					fs.Close();
					return;
				}
			}
			sr.Close();
			fs.Close();
			BatchComputeBtn.Enabled = true;
			BatchListNameTxt.Text = String.Concat("List: ", dlg.FileName.Substring(dlg.FileName.LastIndexOf("\\") + 1), ", ", NFiles, " files.");
			BatchListViewPanel.Text = "Quick Viewing: File 0 of " + NFiles.ToString();
			BatchGoToUpD.Maximum = NFiles;
			BatchListViewPanel.Enabled = true;

		}

		private void BatchScanDirectoryBtn_Click(object sender, EventArgs e)
		{
			if (BatchScanDirectoryFileTypeDrop.SelectedIndex == -1)
				BatchScanDirectoryFileTypeDrop.SelectedIndex = 0;

			FolderBrowserDialog fdlg = new FolderBrowserDialog();

			string VISdir = (string)JPFITS.REG.GetReg("CCDLAB", "L2EventListPath") + "\\VIS";
			if (Directory.Exists(VISdir))
			{
				fdlg.SelectedPath = VISdir;
				BatchQuickScanSubDirsChck.Checked = true;

				string vismedian = VISdir + "\\median.fts";
				if (File.Exists(vismedian))
				{
					BATCHBIASIMG = new FITSImage(vismedian, null, false, true, false, true);
					BatchSubtractImageChck.Checked = true;
				}
			}
			else
				fdlg.SelectedPath = (string)JPFITS.REG.GetReg("CCDLAB", "FolderBrowserPath");

			if (!Directory.Exists(VISdir) && fdlg.ShowDialog() == DialogResult.Cancel)
				return;
			JPFITS.REG.SetReg("CCDLAB", "FolderBrowserPath", fdlg.SelectedPath);

			string[] filelist;

			if (!BatchQuickScanSubDirsChck.Checked)
				filelist = Directory.GetFiles(fdlg.SelectedPath, "*.fits", SearchOption.TopDirectoryOnly);
			else
				filelist = Directory.GetFiles(fdlg.SelectedPath, "*.fits", SearchOption.AllDirectories);
			if (filelist.Length == 0)
			{
				MessageBox.Show("No files found in that directory.", "Error");
				return;
			}

			BATCHLIST = filelist;
			BatchListNameTxt.Text = String.Concat("List: ", BATCHLIST.Length.ToString(), " files.");
			BatchListViewPanel.Text = "Quick Viewing: File 0 of " + BATCHLIST.Length.ToString();
			BatchGoToUpD.Maximum = BATCHLIST.Length;
			BatchListViewPanel.Enabled = true;
			BatchComputeBtn.Enabled = true;
		}

		private void BatchSubtractImageChck_Click(object sender, EventArgs e)
		{
			if (BatchSubtractImageChck.Checked == false)
			{
				return;
			}

			string dir = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS File|*.fits;*.fit;*.fts";

			if (dlg.ShowDialog() != DialogResult.OK)
			{
				BatchSubtractImageChck.Checked = false;
				return;
			}

			BATCHBIASIMG = new FITSImage(dlg.FileName, SUBRANGE, true, true, false, true);
		}

		private void BatchMultiplyImageChck_Click(object sender, EventArgs e)
		{
			if (BatchMultiplyImageChck.Checked == false)
			{
				return;
			}

			string dir = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS File|*.fits;*.fit;*.fts";

			if (dlg.ShowDialog() != DialogResult.OK)
			{
				BatchMultiplyImageChck.Checked = false;
				return;
			}

			BATCHMULTIMG = new FITSImage(dlg.FileName, SUBRANGE, true, true, false, true);
		}

		private void BatchAddImageChck_Click(object sender, EventArgs e)
		{
			if (BatchAddImageChck.Checked == false)
			{
				return;
			}

			string dir = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS File|*.fits;*.fit;*.fts";

			if (dlg.ShowDialog() != DialogResult.OK)
			{
				BatchAddImageChck.Checked = false;
				return;
			}

			BATCHADDIMG = new FITSImage(dlg.FileName, SUBRANGE, true, true, false, true);
		}

		private void BatchDivideImageChck_Click(object sender, EventArgs e)
		{
			if (BatchDivideImageChck.Checked == false)
			{
				return;
			}

			string dir = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.InitialDirectory = dir;
			dlg.Filter = "FITS File|*.fits;*.fit;*.fts";

			if (dlg.ShowDialog() != DialogResult.OK)
			{
				BatchDivideImageChck.Checked = false;
				return;
			}

			BATCHFLATIMG = new FITSImage(dlg.FileName, SUBRANGE, true, true, false, true);
		}

		private void BatchAddImageChck_CheckedChanged(object sender, EventArgs e) { }
		
		private void BatchMultiplyImageChck_CheckedChanged(object sender, EventArgs e) { }
		
		private void BatchSubtractImageChck_CheckedChanged(object sender, EventArgs e) { }

		private void BatchSubImageChck_CheckedChanged(object sender, EventArgs e)
		{
			if (BatchSubImageChck.Checked == true)
			{
				BatchSubImagePanel.BorderStyle = BorderStyle.Fixed3D;
				RangeDlg dlg = new RangeDlg();
				dlg.XStartUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "XStart"));
				dlg.XEndUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "XEnd"));
				dlg.YStartUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "YStart"));
				dlg.YEndUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "YEnd"));
				dlg.ShowDialog();

				if (dlg.DialogResult == DialogResult.OK)
				{
					SUBRANGE[0] = (int)dlg.XStartUpD.Value;
					SUBRANGE[1] = (int)dlg.XEndUpD.Value;
					SUBRANGE[2] = (int)dlg.YStartUpD.Value;
					SUBRANGE[3] = (int)dlg.YEndUpD.Value;
					JPFITS.REG.SetReg("CCDLAB", "XStart", SUBRANGE[0].ToString());
					JPFITS.REG.SetReg("CCDLAB", "XEnd", SUBRANGE[1].ToString());
					JPFITS.REG.SetReg("CCDLAB", "YStart", SUBRANGE[2].ToString());
					JPFITS.REG.SetReg("CCDLAB", "YEnd", SUBRANGE[3].ToString());

					LOADSUBRANGE = true;
					XStartLabel.Text = String.Concat("X Start: ", SUBRANGE[0]);
					XEndLabel.Text = String.Concat("X End: ", SUBRANGE[1]);
					YStartLabel.Text = String.Concat("Y Start: ", SUBRANGE[2]);
					YEndLabel.Text = String.Concat("Y End: ", SUBRANGE[3]);

					BatchDivideImageChck.Checked = false;
					BatchMultiplyImageChck.Checked = false;
					BatchSubtractImageChck.Checked = false;
					BatchAddImageChck.Checked = false;
				}
				else
				{
					BatchSubImageChck.Checked = false;
				}
			}
			else
			{
				LOADSUBRANGE = false;
				SUBRANGE[0] = -1;
				BatchSubImagePanel.BorderStyle = BorderStyle.FixedSingle;
				BatchDivideImageChck.Checked = false;
				BatchMultiplyImageChck.Checked = false;
				BatchSubtractImageChck.Checked = false;
				BatchAddImageChck.Checked = false;
			}
		}

		private void BatchComputeBtn_Click(object sender, EventArgs e)
		{
			string selectedOP = BatchOperationTab.SelectedTab.Name;

			if (selectedOP == "BatchRunningTab")//running
				if (BatchRunningOpDrop.Text == "")
				{
					MessageBox.Show("Running style not selected.  Please try again.", "Error...");
					return;
				}

			Enabled = false;
			WAITBAR = new WaitBar();
			WAITBAR.ProgressBar.Maximum = 100;
			if (UVITBATCHMESG != "")
				WAITBAR.Text = UVITBATCHMESG;
			else
				WAITBAR.Text = "Performing batch operation...";
			BatchBGWrkr.RunWorkerAsync(BatchOperationTab.SelectedTab.Name);
			WAITBAR.ShowDialog();
		}

		private void BatchBGWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			string selectedOP = (string)e.Argument;

			if (selectedOP == "BatchIndividualTab")//individual file operation
			{
				bool findpts = TabBatchElementalFindPointsChck.Checked;
				string searchstyle = TabBatchElementalFindStyleDD.Text;
				double findval = Convert.ToDouble(TabBatchElementalFindValTxt.Text);
				double replaceval = Convert.ToDouble(TabBatchElementalReplaceValTxt.Text);
				bool overwritefile = BatchFileOvrWrtRad.Checked;
				string appendage = BatchIndividualAppendageTxt.Text;
				bool do_parallel = BatchFileParallelChck.Checked;
				bool keepdirs = BatchFileKeepDirectoriesChck.Checked;
				string dir = IndividualDirectoryTxt.Text + "\\";

				ParallelOptions opts = new ParallelOptions();
				if (do_parallel)
					opts.MaxDegreeOfParallelism = System.Environment.ProcessorCount;
				else
					opts.MaxDegreeOfParallelism = 1;
				var rangePartitioner = Partitioner.Create(0, BATCHLIST.Length);
				int count = 0, prog = 0;

				Parallel.ForEach(rangePartitioner, opts, (range, loopState) =>
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						loopState.Stop();

					for (int i = range.Item1; i < range.Item2; i++)
					{
						if (WAITBAR.DialogResult == DialogResult.Cancel)
						{
							if (UVITBATCHOP)
							{
								UVITBATCHOP = false;
								UVITBATCHOP_CANCELLED = true;
							}
							break;
						}

						Interlocked.Increment(ref count);
						lock (BATCHLIST)
						{
							if (count * 100 / BATCHLIST.Length > prog)
							{
								prog = count * 100 / BATCHLIST.Length;
								BatchBGWrkr.ReportProgress(prog);
							}
						}

						FITSImage temp = new FITSImage(BATCHLIST[i], SUBRANGE, true, true, false, !do_parallel);

						//corrections
						if (BatchSubtractImageChck.Checked)
							temp.SetImage(JPMath.MatrixSubMatrix(temp.Image, BATCHBIASIMG.Image, !do_parallel), false, !do_parallel);
						if (BatchAddImageChck.Checked)
							temp.SetImage(JPMath.MatrixAddMatrix(temp.Image, BATCHADDIMG.Image, !do_parallel), false, !do_parallel);
						if (BatchMultiplyImageChck.Checked)
							temp.SetImage(JPMath.MatrixMultMatrix(temp.Image, BATCHMULTIMG.Image, !do_parallel), false, !do_parallel);
						if (BatchDivideImageChck.Checked)
							temp.SetImage(JPMath.MatrixDivMatrix(temp.Image, BATCHFLATIMG.Image, !do_parallel), false, !do_parallel);

						if (findpts)
						{
							JPMath.Find(temp.Image, findval, searchstyle, !do_parallel, out FNDCOORDS_X, out FNDCOORDS_Y);

							temp.Image = JPMath.Replace(temp.Image, FNDCOORDS_X, FNDCOORDS_Y, replaceval, !do_parallel);
						}

						if (overwritefile)
							temp.WriteImage(FILESAVEPREC, !do_parallel);
						else//append
						{
							if (keepdirs)
								temp.FileName = temp.FileName.Insert(temp.FileName.LastIndexOf("."), appendage);
							else
								temp.FullFileName = dir + temp.FileName.Insert(temp.FileName.LastIndexOf("."), appendage);

							temp.WriteImage(FILESAVEPREC, !do_parallel);
						}
					}
				});

				/*TimeSpan^ ts = .DateTime.Now - now;
				MessageBox.Show(ts.TotalMinutes + "");*/

				return;
			}

			if (selectedOP == "BatchSetTab")//Set
			{
				FITSImage fits_integral = null;
				FITSImage temp = null;

				for (int i = 0; i < BATCHLIST.Length; i++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					BatchBGWrkr.ReportProgress(i);

					temp = new FITSImage(BATCHLIST[i], SUBRANGE, true, true, false, true);

					//corrections
					if (BatchSubtractImageChck.Checked == true)
						temp.SetImage(temp - BATCHBIASIMG, false, true);
					if (BatchMultiplyImageChck.Checked == true)
						temp.SetImage(temp * BATCHMULTIMG, false, true);
					if (BatchAddImageChck.Checked == true)
						temp.SetImage(temp + BATCHADDIMG, false, true);
					if (BatchDivideImageChck.Checked == true)
						temp.SetImage(temp / BATCHFLATIMG, false, true);

					if (BatchSumRad.Checked || BatchMeanRad.Checked)
					{
						if (i == 0)
							fits_integral = temp;
						else
							fits_integral.SetImage(fits_integral + temp, false, true);
					}
				}

				if (BatchMeanRad.Checked)
					fits_integral.SetImage(fits_integral / BATCHLIST.Length, false, true);
				if (BatchSumRad.Checked || BatchMeanRad.Checked)
				{
					e.Result = fits_integral;
				}
			}//end of Set op

			if (selectedOP == "BatchStackingTab")//stacking
			{
				WAITBAR.ProgressBar.Maximum = 100;
				int intprog = 0;

				int STACK = (int)StackUpD.Value;
				int N = BATCHLIST.Length;
				int iters = (int)Math.Floor((double)(N) / (double)(STACK));

				FITSImage temp1;
				FITSImage temp2;
				string dir = StackingDirectoryTxt.Text + "\\";
				string fext;

				for (int i = 0; i < iters; i++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					if (100 * i * STACK / N - intprog >= 1)
					{
						intprog = 100 * i * STACK / N;
						BatchBGWrkr.ReportProgress(intprog);
					}

					temp1 = new JPFITS.FITSImage(BATCHLIST[i * STACK], SUBRANGE, true, true, false, true);

					//corrections
					if (BatchSubtractImageChck.Checked == true)
						temp1.SetImage(temp1 - BATCHBIASIMG, false, true);
					if (BatchMultiplyImageChck.Checked == true)
						temp1.SetImage(temp1 * BATCHMULTIMG, false, true);
					if (BatchAddImageChck.Checked == true)
						temp1.SetImage(temp1 + BATCHADDIMG, false, true);
					if (BatchDivideImageChck.Checked == true)
						temp1.SetImage(temp1 / BATCHFLATIMG, false, true);

					for (int j = 1; j < STACK; j++)
					{
						temp2 = new JPFITS.FITSImage(BATCHLIST[i * STACK + j], SUBRANGE, true, true, false, true);

						//corrections
						if (BatchSubtractImageChck.Checked == true)
							temp2.SetImage(temp2 - BATCHBIASIMG, false, true);
						if (BatchMultiplyImageChck.Checked == true)
							temp2.SetImage(temp2 * BATCHMULTIMG, false, true);
						if (BatchAddImageChck.Checked == true)
							temp2.SetImage(temp2 + BATCHADDIMG, false, true);
						if (BatchDivideImageChck.Checked == true)
							temp2.SetImage(temp2 / BATCHFLATIMG, false, true);

						temp1.SetImage(temp1 + temp2, false, true);
					}
					fext = temp1.FileName.Substring(temp1.FileName.LastIndexOf("."));

					temp1.WriteImage(dir + (i * STACK + STACK).ToString("000000") + fext, FILESAVEPREC, true);
				}
			}//end of stacking

			if (selectedOP == "BatchRunningTab")//running
			{
				string RUN_STYLE = BatchRunningOpDrop.Text;
				string dir = RunningDirectoryTxt.Text + "\\";
				int RUN = (int)BatchRunningNumUpD.Value;
				int N = BATCHLIST.Length;
				string filename = "";

				JPFITS.FITSImageSet RUNSET = new JPFITS.FITSImageSet();
				FITSImage temp = null;

				WAITBAR.ProgressBar.Maximum = 100;
				int intprog = 0;

				for (int i = 0; i < N - RUN + 1; i++)
				{
					if (WAITBAR.DialogResult == DialogResult.Cancel)
						return;
					if (100 * i / N - intprog >= 1)
					{
						intprog = 100 * i / N;
						BatchBGWrkr.ReportProgress(intprog);
					}

					RUNSET.Clear();
					for (int j = 0; j < RUN; j++)
					{
						temp = new FITSImage(BATCHLIST[i + j], SUBRANGE, true, true, false, true);

						//corrections
						if (BatchSubtractImageChck.Checked == true)
							temp.SetImage(temp - BATCHBIASIMG, false, true);
						if (BatchMultiplyImageChck.Checked == true)
							temp.SetImage(temp * BATCHMULTIMG, false, true);
						if (BatchAddImageChck.Checked == true)
							temp.SetImage(temp + BATCHADDIMG, false, true);
						if (BatchDivideImageChck.Checked == true)
							temp.SetImage(temp / BATCHFLATIMG, false, true);

						RUNSET.Add(temp);
					}

					bool product = false;
					if (RUN_STYLE == "Median")
					{
						temp.SetImage(FITSImageSet.Median(RUNSET, false, false, "").Image, false, true);
						product = true;
					}
					if (RUN_STYLE == "Minimum")
					{
						temp.SetImage(FITSImageSet.Min(RUNSET, false, false).Image, false, true);
						product = true;
					}
					if (RUN_STYLE == "Maximum")
					{
						temp.SetImage(FITSImageSet.Max(RUNSET, false, false).Image, false, true);
						product = true;
					}
					if (RUN_STYLE == "Mean")
					{
						temp.SetImage(FITSImageSet.Mean(RUNSET, false, false).Image, false, true);
						product = true;
					}
					if (RUN_STYLE == "Sum")
					{
						temp.SetImage(FITSImageSet.Sum(RUNSET, false, false).Image, false, true);
						product = true;
					}

					if (product)
					{
						filename = dir + "Running" + RUN_STYLE + RUN.ToString() + "_" + i.ToString("000000") + ".fits";
						temp.WriteImage(filename, FILESAVEPREC, true);
					}
				}
			}
		}

		private void BatchBGWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			string selectedOP = BatchOperationTab.SelectedTab.Name;

			WAITBAR.ProgressBar.Value = e.ProgressPercentage;

			if (selectedOP == "BatchSetTab" || selectedOP == "BatchRunningTab")
				WAITBAR.TextMsg.Text = String.Concat("Completed ", e.ProgressPercentage, " of ", BATCHLIST.Length, " files.");
			if (selectedOP == "BatchStackingTab" || selectedOP == "BatchIndividualTab")
				WAITBAR.TextMsg.Text = String.Concat("Completed ", e.ProgressPercentage, "%");
		}

		private void BatchBGWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			DialogResult res = WAITBAR.DialogResult;
			WAITBAR.Hide();
			WAITBAR.Close();
			this.Enabled = true;
			BringToFront();
			string selectedOP = BatchOperationTab.SelectedTab.Name;

			if (UVITBATCHOP)
			{
				UVITBATCHOP = false;
				if (res == DialogResult.Cancel)
					UVITBATCHOP_CANCELLED = true;
				return;
			}

			if (res == DialogResult.Cancel)
			{
				MessageBox.Show("Operation cancelled...");
				return;
			}

			if (selectedOP == "BatchSetTab" && WAITBAR.DialogResult != DialogResult.Cancel)//Set
			{
				FITSImage result = (FITSImage)e.Result;
				result.WriteImage(BatchOutLabel.Text, FILESAVEPREC, true);
				return;
			}

			if ((string)e.Result != "-1" && selectedOP != "BatchSetTab")
				MessageBox.Show("Operation complete...");
		}

		private void BatchIntegralTab_SelectedIndexChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "BatchOperationTabIndex", BatchOperationTab.SelectedIndex);
		}

		private void BatchOutFileName_Click(object sender, EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.FileName = BatchOutLabel.Text.Substring(BatchOutLabel.Text.LastIndexOf("\\") + 1);
			try
			{
				sfd.InitialDirectory = BATCHLIST[0].Substring(0, BATCHLIST[0].LastIndexOf("\\"));
			}
			catch
			{
			}

			sfd.Filter = "FITS File (*.fts)|*.fts|FITS File (*.fit)|*.fit|FITS File (*.fits)|*.fits";
			sfd.FilterIndex = 3;

			if (sfd.ShowDialog() == DialogResult.OK)
			{
				BatchOutLabel.Text = sfd.FileName;
				JPFITS.REG.SetReg("CCDLAB", "OpenFilesPath", sfd.FileName.Substring(0, sfd.FileName.LastIndexOf("\\")));
			}
		}

		private void StackingDirectoryTxt_Click(System.Object sender, System.EventArgs e)
		{
			FolderBrowserDialog fb = new FolderBrowserDialog();
			fb.SelectedPath = (string)JPFITS.REG.GetReg("CCDLAB", "StackingFilesPath");
			if (fb.ShowDialog() == DialogResult.Cancel)
				return;
			string dir = fb.SelectedPath;
			StackingDirectoryTxt.Text = dir;
			JPFITS.REG.SetReg("CCDLAB", "StackingFilesPath", dir);
		}

		private void RunningDirectoryTxt_Click(System.Object sender, System.EventArgs e)
		{
			FolderBrowserDialog fb = new FolderBrowserDialog();
			fb.SelectedPath = (string)JPFITS.REG.GetReg("CCDLAB", "RunningFilesPath");
			if (fb.ShowDialog() == DialogResult.Cancel)
				return;
			string dir = fb.SelectedPath;
			RunningDirectoryTxt.Text = dir;
			JPFITS.REG.SetReg("CCDLAB", "RunningFilesPath", dir);
		}

		private void IndividualDirectoryTxt_Click(System.Object sender, System.EventArgs e)
		{
			FolderBrowserDialog fb = new FolderBrowserDialog();
			fb.SelectedPath = (string)JPFITS.REG.GetReg("CCDLAB", "IndividualFilesPath");
			if (fb.ShowDialog() == DialogResult.Cancel)
				return;
			string dir = fb.SelectedPath;
			IndividualDirectoryTxt.Text = dir;
			JPFITS.REG.SetReg("CCDLAB", "IndividualFilesPath", dir);
		}

		private void StackUpD_ValueChanged(System.Object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "StackUpDValue", StackUpD.Value.ToString());
		}

		private void BatchRunningNumUpD_ValueChanged(System.Object sender, System.EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "RunningUpDValue", BatchRunningNumUpD.Value.ToString());
		}

		private void TabBatchElementalFindPointsChck_CheckedChanged(System.Object sender, System.EventArgs e)
		{
			if (TabBatchElementalFindPointsChck.Checked)
			{
				TabBatchElementalFindStyleDD.Enabled = true;
				TabBatchElementalFindValTxt.Enabled = true;
				//TabBatchElementalReplaceStyleDD.Enabled = true;
				TabBatchElementalReplaceValTxt.Enabled = true;
			}
			else
			{
				TabBatchElementalFindStyleDD.Enabled = false;
				TabBatchElementalFindValTxt.Enabled = false;
				//TabBatchElementalReplaceStyleDD.Enabled = false;
				TabBatchElementalReplaceValTxt.Enabled = false;
			}
		}

		private void BatchFileAppRad_CheckedChanged(System.Object sender, System.EventArgs e)
		{
			if (BatchFileAppRad.Checked)
			{
				BatchIndividualAppendageTxt.Enabled = true;
				IndividualDirectoryTxt.Enabled = true;
				BatchFileKeepDirectoriesChck.Enabled = true;
			}
			else
			{
				BatchIndividualAppendageTxt.Enabled = false;
				IndividualDirectoryTxt.Enabled = false;
				BatchFileKeepDirectoriesChck.Enabled = false;
			}
		}

		private void BatchFileKeepDirectoriesChck_CheckedChanged(System.Object sender, System.EventArgs e)
		{
			if (BatchFileKeepDirectoriesChck.Checked)
				IndividualDirectoryTxt.Enabled = false;
			else
				IndividualDirectoryTxt.Enabled = true;
		}

		private void BatchMovieTimer_Tick(System.Object sender, System.EventArgs e)
		{
			BatchMovieTimer.Interval = (int)(Convert.ToDouble(BatchBlinkTime.Value) * 1000) + 1;//+1 to avoid 0, 1 = 1ms
			BatchViewNextBtn_Click(sender, e);
		}

		private void BatchBlinkChck_CheckedChanged(System.Object sender, System.EventArgs e)
		{
			if (BatchBlinkChck.Checked == true)
			{
				BatchMovieTimer.Enabled = true;
				BatchBlinkChck.BackColor = System.Drawing.Color.Red;
			}
			else
			{
				BatchMovieTimer.Enabled = false;
				BatchBlinkChck.BackColor = System.Drawing.Color.Gainsboro;
			}
		}

		private void BatchViewNextBtn_Click(System.Object sender, System.EventArgs e)
		{
			BATCHVIEWINDEX += (int)BatchMovieSkipUpD.Value + 1;

			if (BATCHVIEWINDEX > BATCHLIST.Length - 1)
				BATCHVIEWINDEX = 0;

			BatchListViewPanel.Text = "Quick Viewing: File " + (BATCHVIEWINDEX + 1).ToString() + " of " + BATCHLIST.Length.ToString();

			string[] file = new string[] { BATCHLIST[BATCHVIEWINDEX] };

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(file, false);
		}

		private void BatchViewLastBtn_Click(System.Object sender, System.EventArgs e)
		{
			BATCHVIEWINDEX -= (int)BatchMovieSkipUpD.Value + 1;

			if (BATCHVIEWINDEX < 0)
				BATCHVIEWINDEX = BATCHLIST.Length - 1;

			BatchListViewPanel.Text = "Quick Viewing: File " + (BATCHVIEWINDEX + 1).ToString() + " of " + BATCHLIST.Length.ToString();

			string[] file = new string[] { BATCHLIST[BATCHVIEWINDEX] };

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(file, false);
		}

		private void BatchGoToBtn_Click(System.Object sender, System.EventArgs e)
		{
			BATCHVIEWINDEX = (int)(BatchGoToUpD.Value) - 1;

			BatchListViewPanel.Text = "Quick Viewing: File " + (BATCHVIEWINDEX + 1).ToString() + " of " + BATCHLIST.Length.ToString();

			string[] file = new string[] { BATCHLIST[BATCHVIEWINDEX] };

			FileListDrop.Items.Clear();
			IMAGESET.Clear();
			AddToImageSet(file, false);
		}
	}
}