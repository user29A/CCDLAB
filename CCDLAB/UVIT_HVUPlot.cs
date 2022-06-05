using System;
using System.ComponentModel;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization;

namespace CCDLAB
{
	public partial class UVIT_HVUPlot : Form
	{
		public double[] anode;
public double[] mcp;
public double[] cathode;
public double[] hvu;
public double[] tick;

public string axisxLabel;


public static JPFITS.FITSImage ANODE;
public static JPFITS.FITSImage MCP;
public static JPFITS.FITSImage CATHODE;
public static JPFITS.FITSImage HVU;
public static JPFITS.FITSImage TICK;
public static JPFITS.WaitBar wb;
public static int IND = 0;

		public UVIT_HVUPlot()
		{
			InitializeComponent();
		}

		private void exitThisToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void exitCCDLABToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		public void Plot_Telem(string[] files, int ind)
		{
			IND = ind;
			if (IND == 0)
				axisxLabel = "Frame Time Tick (mins)";
			if (IND == 1)
				axisxLabel = "Time Since Start of Imaging (mins)";
			if (IND == 2)
				axisxLabel = "Frame Count Tick";

			JPFITS.FITSImage  f = new JPFITS.FITSImage(files[0], null, true, false, false, false);
			TitleTxt.Text = f.Header.GetKeyValue("SRCFILE");

			wb = new JPFITS.WaitBar();
			PlotWrkr.RunWorkerAsync(files);
			wb.Show();
		}

		private void PlotWrkr_DoWork(object sender, DoWorkEventArgs e)
		{
			string[]FileList = (string[])e.Argument;
			int NFiles = FileList.Length;
			anode = new double[NFiles];
			mcp = new double[NFiles];
			cathode = new double[NFiles];
			hvu = new double[NFiles];
			tick = new double[NFiles];
			double[,] dummy = new double[1, 1];

			JPFITS.FITSImage  f;
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
				anode[i] = Convert.ToDouble(f.Header.GetKeyValue("AND_TEL"));
				mcp[i] = Convert.ToDouble(f.Header.GetKeyValue("MCP_TEL"));
				cathode[i] = Convert.ToDouble(f.Header.GetKeyValue("CAT_TEL"));
				hvu[i] = Convert.ToDouble(f.Header.GetKeyValue("HVU_TEL"));

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
					tick[i] = num_cur - 1;
			}

			double rate;
			if (IND == 1)
				rate = (time_end - time_start) / (num_end - num_start);
			else
				rate = 1;
			for (int i = 0; i < NFiles; i++)
				tick[i] = tick[i] * rate;

			ANODE = new JPFITS.FITSImage("dummy", anode, true, true);
			MCP = new JPFITS.FITSImage("dummy", mcp, true, true);
			CATHODE = new JPFITS.FITSImage("dummy", cathode, true, true);
			HVU = new JPFITS.FITSImage("dummy", hvu, true, true);
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

			AndMinTxt.Text = ANODE.Min.ToString();
			AndMaxTxt.Text = ANODE.Max.ToString();
			AndMedianTxt.Text = ANODE.Median.ToString();
			AndMeanTxt.Text = Math.Round(ANODE.Mean, 2).ToString();
			AndStdvTxt.Text = Math.Round(ANODE.Std, 2).ToString();

			McpMinTxt.Text = MCP.Min.ToString();
			McpMaxTxt.Text = MCP.Max.ToString();
			McpMedianTxt.Text = MCP.Median.ToString();
			McpMeanTxt.Text = Math.Round(MCP.Mean, 2).ToString();
			McpStdvTxt.Text = Math.Round(MCP.Std, 2).ToString();

			CatMinTxt.Text = CATHODE.Min.ToString();
			CatMaxTxt.Text = CATHODE.Max.ToString();
			CatMedianTxt.Text = CATHODE.Median.ToString();
			CatMeanTxt.Text = Math.Round(CATHODE.Mean, 2).ToString();
			CatStdvTxt.Text = Math.Round(CATHODE.Std, 2).ToString();

			HVUMinTxt.Text = HVU.Min.ToString();
			HVUMaxTxt.Text = HVU.Max.ToString();
			HVUMedianTxt.Text = HVU.Median.ToString();
			HVUMeanTxt.Text = Math.Round(HVU.Mean, 2).ToString();
			HVUStdvTxt.Text = Math.Round(HVU.Std, 2).ToString();

			jpChartAnode.PlotXYData(tick, anode, "", axisxLabel, "Volts",  System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "Anode");
			jpChartMCP.PlotXYData(tick, mcp, "", axisxLabel, "Volts", System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "MCP");
			jpChartCathode.PlotXYData(tick, cathode, "", axisxLabel, "Volts", System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "Cathode");
			jpChartHVU.PlotXYData(tick, hvu, "", axisxLabel, "Volts", System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "HVU");

			this.Show();
			this.Focus();
		}
	}
}
