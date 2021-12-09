using System;
using System.Drawing;
using System.Windows.Forms;

namespace CCDLAB
{


	public partial class JPPlot : Form
	{
		public double[] jpplotXDATA;
		public double[] jpplotYDATA;
		public JPPlot FIT_RESIDUALS_PLOT;

		public JPPlot()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void JPPlotMenuItem_Fit_Click(object sender, EventArgs e)
		{

		}

		private void FitMenuGaussian_Click(object sender, EventArgs e)
		{
			double pixscale = Convert.ToDouble(PixelScaleTxtBox.Text);
			if (pixscale <= 0)
				pixscale = 1;

			{
				double[] dum = new double[0];
				double[] dum2 = new double[0];
				double[] PFit = new double[4];
				JPFITS.JPMath.Fit_Gaussian1d(jpplotXDATA, jpplotYDATA, ref PFit, null, null, ref dum, ref dum2);
				double[] newX = new double[jpplotXDATA.Length * 10];
				double step = (jpplotXDATA[jpplotXDATA.Length - 1] - jpplotXDATA[0]) / newX.Length;
				for (int i = 0; i < newX.Length; i++)
					newX[i] = jpplotXDATA[0] + (double)i * step;
				double[] newY = new double[newX.Length];
				JPFITS.JPMath.Gaussian1d(newX, ref newY, PFit);

				for (int i = 0; i < newY.Length; i++)
					newX[i] = newX[i] + 0.5;

				JPChart1.AddXYData(newX, newY, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "Gaussian Fit", Color.Red);
				string eq = "A*exp[-(x - B)^2 / (2*C^2)] + D";
				string title = eq + " : A = " + PFit[0].ToString("G5") + "; B = " + PFit[1].ToString("G6") + "; FWHM = " + (pixscale * PFit[2] * 2.355).ToString("G5") + "''" + "; D = " + PFit[3].ToString("G5");
				JPChart1.SetChartTitle(title);

				System.Windows.Forms.Clipboard.SetText(PFit[0].ToString() + "	" + PFit[1].ToString() + "	" + PFit[2].ToString() + "	" + PFit[3].ToString());
			}
		}

		private void FitMenuMoffat_Click(object sender, EventArgs e)
		{
			double pixscale = Convert.ToDouble(PixelScaleTxtBox.Text);
			if (pixscale <= 0)
				pixscale = 1;

			{
				double[] dum = new double[0];
				double[] dum2 = new double[0];
				double[] PFit = new double[5];
				JPFITS.JPMath.Fit_Moffat1d(jpplotXDATA, jpplotYDATA, ref PFit, null, null, ref dum, ref dum2);
				double[] newX = new double[jpplotXDATA.Length * 10];
				double step = (jpplotXDATA[jpplotXDATA.Length - 1] - jpplotXDATA[0]) / newX.Length;
				for (int i = 0; i < newX.Length; i++)
					newX[i] = jpplotXDATA[0] + (double)(i) * step;
				double[] newY = new double[newX.Length];
				JPFITS.JPMath.Moffat1d(newX, ref newY, PFit);

				for (int i = 0; i < newY.Length; i++)
					newX[i] = newX[i] + 0.5;

				JPChart1.AddXYData(newX, newY, System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line, "Moffat Fit", Color.Red);
				string eq = "A*[1 + ((x-B)/C)^2]^(-D) + E";
				string title = eq + " : A = " + PFit[0].ToString("G5") + "; B = " + PFit[1].ToString("G6") + "; C = " + (PFit[2]).ToString("G5") + "; D = " + PFit[3].ToString("G5") + "; E = " + PFit[4].ToString("G5") + "; FWHM = " + (pixscale * 2 * PFit[2] * Math.Sqrt(Math.Pow(2, 1 / PFit[3]) - 1)).ToString("G5") + "''";
				JPChart1.SetChartTitle(title);

				System.Windows.Forms.Clipboard.SetText(PFit[0].ToString() + "	" + PFit[1].ToString() + "	" + PFit[2].ToString() + "	" + PFit[3].ToString());
			}
		}

		private void FitMenuPlotResidualsChck_Click(object sender, EventArgs e)
		{
			JPPlotMenuItem_Fit.ShowDropDown();
			JPFITS.REG.SetReg("CCDLAB", "JPPlotResiduals", FitMenuPlotResidualsChck.Checked);
		}

		private void PixelScaleTxtBox_TextChanged(object sender, EventArgs e)
		{
			if (PixelScaleTxtBox.Text == ".")
			{
				PixelScaleTxtBox.Text = "0.";
				return;
			}

			try
			{
				Convert.ToDouble(PixelScaleTxtBox.Text);
			}
			catch
			{
				PixelScaleTxtBox.Text = (string)JPFITS.REG.GetReg("CCDLAB", "PixelScaleTxt");
				return;
			}
			JPFITS.REG.SetReg("CCDLAB", "PixelScaleTxt", PixelScaleTxtBox.Text);
		}

		private void JPPlot_FormClosing(object sender, FormClosingEventArgs e)
		{
			if (this.Text == "Row Plot")
			{
				JPFITS.REG.SetReg("CCDLAB", "ROWplotPOSX", this.Location.X);
				JPFITS.REG.SetReg("CCDLAB", "ROWplotPOSY", this.Location.Y);
				JPFITS.REG.SetReg("CCDLAB", "ROWplotWIDTH", this.Size.Width);
				JPFITS.REG.SetReg("CCDLAB", "ROWplotHEIGHT", this.Size.Height);
			}
			if (this.Text == "Column Plot")
			{
				JPFITS.REG.SetReg("CCDLAB", "COLplotPOSX", this.Location.X);
				JPFITS.REG.SetReg("CCDLAB", "COLplotPOSY", this.Location.Y);
				JPFITS.REG.SetReg("CCDLAB", "COLplotWIDTH", this.Size.Width);
				JPFITS.REG.SetReg("CCDLAB", "COLplotHEIGHT", this.Size.Height);
			}
			if (this.Text == "Radial Profile Plot")
			{
				JPFITS.REG.SetReg("CCDLAB", "RADplotPOSX", this.Left);
				JPFITS.REG.SetReg("CCDLAB", "RADplotPOSY", this.Top);
				JPFITS.REG.SetReg("CCDLAB", "RADplotWIDTH", this.Width);
				JPFITS.REG.SetReg("CCDLAB", "RADplotHEIGHT", this.Height);
			}
			if (this.Text == "X-Drift")
			{
				JPFITS.REG.SetReg("CCDLAB", "XDriftplotPOSX", this.Location.X);
				JPFITS.REG.SetReg("CCDLAB", "XDriftplotPOSY", this.Location.Y);
				JPFITS.REG.SetReg("CCDLAB", "XDriftplotWIDTH", this.Size.Width);
				JPFITS.REG.SetReg("CCDLAB", "XDriftplotHEIGHT", this.Size.Height);
			}
			if (this.Text == "Y-Drift")
			{
				JPFITS.REG.SetReg("CCDLAB", "YDriftplotPOSX", this.Location.X);
				JPFITS.REG.SetReg("CCDLAB", "YDriftplotPOSY", this.Location.Y);
				JPFITS.REG.SetReg("CCDLAB", "YDriftplotWIDTH", this.Size.Width);
				JPFITS.REG.SetReg("CCDLAB", "YDriftplotHEIGHT", this.Size.Height);
			}
			if (this.Text == "Radial Line Plot")
			{
				JPFITS.REG.SetReg("CCDLAB", "RadialLinePlotPOSX", this.Location.X);
				JPFITS.REG.SetReg("CCDLAB", "RadialLinePlotPOSY", this.Location.Y);
				JPFITS.REG.SetReg("CCDLAB", "RadialLinePlotWIDTH", this.Size.Width);
				JPFITS.REG.SetReg("CCDLAB", "RadialLinePlotHEIGHT", this.Size.Height);
			}

			if (FIT_RESIDUALS_PLOT != null)
				FIT_RESIDUALS_PLOT.Close();
		}

		private void JPPlot_Load(object sender, EventArgs e)
		{
			try
			{
				if (this.Text == "Row Plot")
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "ROWplotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "ROWplotPOSY");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "ROWplotWIDTH");
					this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "ROWplotHEIGHT");
				}
				if (this.Text == "Column Plot")
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "COLplotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "COLplotPOSY");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "COLplotWIDTH");
					this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "COLplotHEIGHT");
				}
				if (this.Text == "Radial Profile Plot")
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotPOSY");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotWIDTH");
					this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotHEIGHT");
				}
				if (this.Text == "X-Drift")
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "XDriftplotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "XDriftplotPOSY");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "XDriftplotWIDTH");
					this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "XDriftplotHEIGHT");
				}
				if (this.Text == "Y-Drift")
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "YDriftplotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "YDriftplotPOSY");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "YDriftplotWIDTH");
					this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "YDriftplotHEIGHT");
				}
				if (this.Text == "Radial Line Plot")
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "RadialLinePlotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "RadialLinePlotPOSY");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "RadialLinePlotWIDTH");
					this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "RadialLinePlotHEIGHT");
				}
				if (this.Text.Contains("Residuals"))
				{
					this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotPOSX");
					this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotPOSY") + (int)JPFITS.REG.GetReg("CCDLAB", "RADplotHEIGHT");
					this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "RADplotWIDTH");
					this.Height = ((int)JPFITS.REG.GetReg("CCDLAB", "RADplotHEIGHT")) / 2;
				}

				PixelScaleTxtBox.Text = (string)JPFITS.REG.GetReg("CCDLAB", "PixelScaleTxt");
				FitMenuPlotResidualsChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "JPPlotResiduals"));
			}
			catch { }
		}

		private void JPPlot_TextChanged(object sender, EventArgs e)
		{

		}

		public void PlotLine(double[] XData, double[] YData, string XTitle, string YTitle, string ChartTitle, System.Windows.Forms.DataVisualization.Charting.SeriesChartType ChartStyle, string SeriesName)
		{
			jpplotXDATA = new double[XData.Length];
			jpplotYDATA = new double[XData.Length];

			double offset = 0;
			if (ChartStyle == System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine)
				offset = 0.5;

			for (int i = 0; i < XData.Length; i++)
			{
				jpplotXDATA[i] = XData[i] + offset;
				jpplotYDATA[i] = YData[i];
			}
			JPChart1.PlotXYData(jpplotXDATA, jpplotYDATA, ChartTitle, XTitle, YTitle, ChartStyle, SeriesName);
			this.Show();
			//JPPlot.Show();
		}

		public void AddLine(double[] XData, double[] YData, System.Windows.Forms.DataVisualization.Charting.SeriesChartType ChartStyle, string SeriesName)
		{
			JPChart1.AddXYData(XData, YData, ChartStyle, SeriesName, Color.Red);
		}
	}
}
