using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CCDLAB
{
	public partial class UVIT_StatsPlot : Form
	{
		public double[] min;
		public double[] max;
		public double[] mean;
		public double[] median;
		public double[] stdv;
		public double[] tick;
		public string axisxLabel;
		public static JPFITS.FITSImage MIN;
		public static JPFITS.FITSImage MAX;
		public static JPFITS.FITSImage MEDIAN;
		public static JPFITS.FITSImage MEAN;
		public static JPFITS.FITSImage STDV;
		public static JPFITS.FITSImage TICK;
		public static JPFITS.WaitBar wb;
		public static int IND = 0;

		public UVIT_StatsPlot()
		{
			InitializeComponent();
		}

		public void Plot_Stats(string[] files, int ind)
		{
			IND = ind;
			if (IND == 0)
				axisxLabel = "Frame Time Tick (mins)";
			if (IND == 1)
				axisxLabel = "Time Since Start of Imaging (mins)";
			if (IND == 2)
				axisxLabel = "Frame Count Tick";
			wb = new JPFITS.WaitBar();
			PlotWrkr.RunWorkerAsync(files);
			wb.Show();
		}

		private void exitThisToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void exitCCDLABToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		private void PlotWrkr_DoWork(object sender, DoWorkEventArgs e)
		{
			string[] FileList = (string[])e.Argument;
			int NFiles = FileList.Length;
			mean = new double[NFiles];
			median = new double[NFiles];
			stdv = new double[NFiles];
			min = new double[NFiles];
			max = new double[NFiles];
			tick = new double[NFiles];
			double[,] dummy = new double[1, 1];

			JPFITS.FITSImage f;
			double time_cur = 0;
			double time_start = 0;
			double time_end = 0;
			double num_start = 0;
			double num_end = 0;
			double num_cur = 0;
			wb.ProgressBar.Maximum = 100;
			int prog = 0;
			for (int i = 0; i < NFiles; i++)
			{
				if (wb.DialogResult == DialogResult.Cancel)
				{
					return;
				}
				if (100 * i / NFiles > prog)
				{
					prog++;
					PlotWrkr.ReportProgress(prog);
				}


				f = new JPFITS.FITSImage(FileList[i], null, true, false, false, false);
				min[i] = Convert.ToDouble(f.Header.GetKeyValue("MIN"));
				max[i] = Convert.ToDouble(f.Header.GetKeyValue("MAX"));
				mean[i] = Convert.ToDouble(f.Header.GetKeyValue("MEAN"));
				median[i] = Convert.ToDouble(f.Header.GetKeyValue("MEDIAN"));
				stdv[i] = Convert.ToDouble(f.Header.GetKeyValue("STDV"));

				if (i == 0)
				{
					time_start = Convert.ToDouble(f.Header.GetKeyValue("IMFRTIME")) / 60;//minutes
					num_start = Convert.ToDouble(f.Header.GetKeyValue("IMFRCNT"));//frame number
				}
				if (i == NFiles - 1)
				{
					time_end = Convert.ToDouble(f.Header.GetKeyValue("IMFRTIME")) / 60;//minutes
					num_end = Convert.ToDouble(f.Header.GetKeyValue("IMFRCNT"));//frame number
				}
				time_cur = Convert.ToDouble(f.Header.GetKeyValue("IMFRTIME")) / 60;
				num_cur = Convert.ToDouble(f.Header.GetKeyValue("IMFRCNT"));//frame number
				if (IND == 0)
					tick[i] = time_cur;
				else
					tick[i] = num_cur;

				f.SetImage(dummy, false, false);
			}
			double rate;
			if (IND == 1)
				rate = (time_end - time_start) / (num_end - num_start);
			else
				rate = 1;
			for (int i = 0; i < NFiles; i++)
				tick[i] = tick[i] * rate;

			MIN = new JPFITS.FITSImage("dummy", min, true, true);
			MAX = new JPFITS.FITSImage("dummy", max, true, true);
			MEDIAN = new JPFITS.FITSImage("dummy", median, true, true);
			MEAN = new JPFITS.FITSImage("dummy", mean, true, true);
			STDV = new JPFITS.FITSImage("dummy", stdv, true, true);
		}

		private void PlotWrkr_ProgressChanged(object sender, ProgressChangedEventArgs e)
		{
			wb.ProgressBar.Value = e.ProgressPercentage;
			wb.Text = String.Concat("Gathering Stats...", e.ProgressPercentage, "%");
			wb.TextMsg.Text = String.Concat("Completed ", e.ProgressPercentage, "%");

		}

		private void PlotWrkr_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
		{
			wb.Close();
			if (wb.DialogResult == DialogResult.Cancel)
				return;
			MinMinTxt.Text = MIN.Min.ToString();
			MinMaxTxt.Text = MIN.Max.ToString();
			MinMedianTxt.Text = MIN.Median.ToString();
			MinMeanTxt.Text = Math.Round(MIN.Mean, 2).ToString();
			MinStdvTxt.Text = Math.Round(MIN.Stdv, 2).ToString();

			MaxMinTxt.Text = MAX.Min.ToString();
			MaxMaxTxt.Text = MAX.Max.ToString();
			MaxMedianTxt.Text = MAX.Median.ToString();
			MaxMeanTxt.Text = Math.Round(MAX.Mean, 2).ToString();
			MaxStdvTxt.Text = Math.Round(MAX.Stdv, 2).ToString();

			MedMinTxt.Text = MEDIAN.Min.ToString();
			MedMaxTxt.Text = MEDIAN.Max.ToString();
			MedMedianTxt.Text = MEDIAN.Median.ToString();
			MedMeanTxt.Text = Math.Round(MEDIAN.Mean, 2).ToString();
			MedStdvTxt.Text = Math.Round(MEDIAN.Stdv, 2).ToString();

			MeanMinTxt.Text = Math.Round(MEAN.Min, 2).ToString();
			MeanMaxTxt.Text = Math.Round(MEAN.Max, 2).ToString();
			MeanMedianTxt.Text = Math.Round(MEAN.Median, 2).ToString();
			MeanMeanTxt.Text = Math.Round(MEAN.Mean, 2).ToString();
			MeanStdvTxt.Text = Math.Round(MEAN.Stdv, 2).ToString();

			StdMinTxt.Text = Math.Round(STDV.Min, 2).ToString();
			StdMaxTxt.Text = Math.Round(STDV.Max, 2).ToString();
			StdMedianTxt.Text = Math.Round(STDV.Median, 2).ToString();
			StdMeanTxt.Text = Math.Round(STDV.Mean, 2).ToString();
			StdStdvTxt.Text = Math.Round(STDV.Stdv, 2).ToString();

			jpChartMin.PlotXYData(tick, min, "", axisxLabel, "", JPChart.SeriesType.Line, "Min", null);
			jpChartMax.PlotXYData(tick, max, "", axisxLabel, "", JPChart.SeriesType.Line, "Max", null);
			jpChartMean.PlotXYData(tick, mean, "", axisxLabel, "", JPChart.SeriesType.Line, "Mean", null);
			jpChartMedian.PlotXYData(tick, median, "", axisxLabel, "", JPChart.SeriesType.Line, "Median", null);
			jpChartStdv.PlotXYData(tick, stdv, "", axisxLabel, "", JPChart.SeriesType.Line, "Stdv", null);


			this.Show();
			this.Focus();
		}
	}
}
