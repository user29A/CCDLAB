using System;
using System.Windows.Forms;

namespace CCDLAB
{
	public partial class FitParametersWindow : Form
	{

		public bool FUNCTION_SET = false;
		public int FUNCTION_NUM = -1;
		public int NPARAMS = -1;
		public string FUNCTION = "";
		private string LASTTEXT = "";
		public TextBox[] PITXTARRAY;
		public TextBox[] PLBTXTARRAY;
		public TextBox[] PUBTXTARRAY;

		public void Set_Function(int num, double[] xrange, double[] yrange, double[,] roi)
		{
			int xind, yind;
			double min = JPFITS.JPMath.Min(roi, false);
			double max = JPFITS.JPMath.Max(roi, out xind, out yind, false);
			double amp = max - min;
			double x0 = xrange[xind];
			double y0 = yrange[yind];
			double xwidth = xrange[xrange.Length - 1] - xrange[0];
			double ywidth = yrange[yrange.Length - 1] - yrange[0];

			//amplitude
			PITXTARRAY[0].Text = amp.ToString();
			PLBTXTARRAY[0].Text = min.ToString();
			PUBTXTARRAY[0].Text = (max + amp).ToString();

			//x0
			PITXTARRAY[1].Text = x0.ToString();
			PLBTXTARRAY[1].Text = (x0 - xwidth * 5).ToString();
			PUBTXTARRAY[1].Text = (x0 + xwidth * 5).ToString();

			//y0
			PITXTARRAY[2].Text = y0.ToString();
			PLBTXTARRAY[2].Text = (y0 - ywidth * 5).ToString();
			PUBTXTARRAY[2].Text = (y0 + ywidth * 5).ToString();

			if (num == 0)
			{
				FUNCTION = "P(0)*exp(-[(X-P(1))^2 + (Y-P(2))^2]/(2*P(3)^2)) + P(4)";
				label1.Text = "Fit Function: Gaussian (2D Circular)";
				NPARAMS = 5;

				PITXTARRAY[3].Text = "2";
				PLBTXTARRAY[3].Text = "0";
				PUBTXTARRAY[3].Text = (xwidth * 5).ToString();

			}

			if (num == 1)
			{
				FUNCTION = "P(0)*exp(-((X-P(1))*cos(P(3)) + (Y-P(2))*sin(P(3)))^2/(2*P(4)^2) - (-(X-P(1))*sin(P(3)) + (Y-P(2))*cos(P(3)))^2/(2*P(5)^2)) + P(6)";
				label1.Text = "Fit Function: Gaussian (2D Elliptical)";
				NPARAMS = 7;

				PITXTARRAY[3].Text = "0";
				PLBTXTARRAY[3].Text = (-Math.PI).ToString();
				PUBTXTARRAY[3].Text = Math.PI.ToString();

				PITXTARRAY[4].Text = "2";
				PLBTXTARRAY[4].Text = "0";
				PUBTXTARRAY[4].Text = (xwidth * 5).ToString();

				PITXTARRAY[5].Text = "2";
				PLBTXTARRAY[5].Text = "0";
				PUBTXTARRAY[5].Text = (ywidth * 5).ToString();

			}

			if (num == 2)
			{
				FUNCTION = "P(0)*(1 + ((X - P(1))^2 + (Y - P(2))^2)/P(3)^2)^(-P(4)) + P(5)";
				label1.Text = "Fit Function: Moffat (2D Circular)";
				NPARAMS = 6;

				PITXTARRAY[3].Text = "2";
				PLBTXTARRAY[3].Text = "0";
				PUBTXTARRAY[3].Text = (xwidth * 5).ToString();

				PITXTARRAY[4].Text = "2";
				PLBTXTARRAY[4].Text = "1";
				PUBTXTARRAY[4].Text = (xwidth * 5).ToString();
			}

			if (num == 3)
			{
				FUNCTION = "P(0)*(1 + (((X-P(1))*cos(P(3)) + (Y-P(2))*sin(P(3)))^2)/P(4)^2 + ((-(X-P(1))*sin(P(3)) + (Y-P(2))*cos(P(3)))^2)/P(5)^2)^(-P(6)) + P(7)";
				label1.Text = "Fit Function: Moffat (2D Elliptical)";
				NPARAMS = 8;

				PITXTARRAY[3].Text = "0";
				PLBTXTARRAY[3].Text = (-Math.PI).ToString();
				PUBTXTARRAY[3].Text = Math.PI.ToString();

				PITXTARRAY[4].Text = "2";
				PLBTXTARRAY[4].Text = "0";
				PUBTXTARRAY[4].Text = (xwidth * 5).ToString();

				PITXTARRAY[5].Text = "2";
				PLBTXTARRAY[5].Text = "0";
				PUBTXTARRAY[5].Text = (ywidth * 5).ToString();

				PITXTARRAY[6].Text = "2";
				PLBTXTARRAY[6].Text = "1";
				PUBTXTARRAY[6].Text = (xwidth * 5).ToString();
			}

			//background
			PITXTARRAY[NPARAMS - 1].Text = min.ToString();
			PLBTXTARRAY[NPARAMS - 1].Text = (min - amp).ToString();
			PUBTXTARRAY[NPARAMS - 1].Text = (min + amp).ToString();
		}

		public FitParametersWindow(int function_num, double[] xrange, double[] yrange, double[,] roi)
		{
			InitializeComponent();

			PITXTARRAY = new TextBox[8];
			PLBTXTARRAY = new TextBox[8];
			PUBTXTARRAY = new TextBox[8];
			for (int i = 0; i < PITXTARRAY.Length; i++)
			{
				PITXTARRAY[i] = (TextBox)(this.Controls.Find("P" + i + "ITxt", true)[0]);
				PLBTXTARRAY[i] = (TextBox)(this.Controls.Find("P" + i + "LBTxt", true)[0]);
				PUBTXTARRAY[i] = (TextBox)(this.Controls.Find("P" + i + "UBTxt", true)[0]);
			}

			Set_Function(function_num, xrange, yrange, roi);
			FUNCTION_SET = true;
			FUNCTION_NUM = function_num;
			FitFcnTxt.Text = FUNCTION;
			for (int i = NPARAMS; i < PITXTARRAY.Length; i++)
			{
				PITXTARRAY[i].Enabled = false;
				PLBTXTARRAY[i].Enabled = false;
				PUBTXTARRAY[i].Enabled = false;
			}
		}

		private void FitParametersWindow_Load(object sender, EventArgs e)
		{
			if (Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "FitConstrain")))
				ConstrainBtn.Checked = true;
		}

		private void GetLastBtn_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < NPARAMS; i++)
			{
				PITXTARRAY[i].Text = (string)(JPFITS.REG.GetReg("CCDLAB", "FitP" + i + "I_" + FUNCTION_NUM));
				PLBTXTARRAY[i].Text = (string)(JPFITS.REG.GetReg("CCDLAB", "FitP" + i + "LB_" + FUNCTION_NUM));
				PUBTXTARRAY[i].Text = (string)(JPFITS.REG.GetReg("CCDLAB", "FitP" + i + "UB_" + FUNCTION_NUM));
			}
		}

		private void P0ITxt_Enter(object sender, EventArgs e)
		{
			TextBox obj = (TextBox)sender;
			LASTTEXT = obj.Text;
		}

		private void P0ITxt_TextChanged(object sender, EventArgs e)
		{
			TextBox obj = (TextBox)sender;

			if (obj.Text == "-" || obj.Text == "-." || obj.Text == "." || obj.Text == "+" || obj.Text == "+." || obj.Text == "")
				return;
			if (obj.Text.Length > 0)
				if (obj.Text.Substring(obj.Text.Length - 1).ToLower() == "e")
					return;
			if (obj.Text.Length > 1)
				if (obj.Text.Substring(obj.Text.Length - 2).ToLower() == "e+" || obj.Text.Substring(obj.Text.Length - 2).ToLower() == "e-")
					return;

			try
			{
				Convert.ToDouble(obj.Text);
			}
			catch
			{
				obj.Text = LASTTEXT;
			}

			LASTTEXT = obj.Text;
		}

		private void SetParamsBtn_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < NPARAMS; i++)
			{
				JPFITS.REG.SetReg("CCDLAB", "FitP" + i + "I_" + FUNCTION_NUM, PITXTARRAY[i].Text);
				JPFITS.REG.SetReg("CCDLAB", "FitP" + i + "LB_" + FUNCTION_NUM, PLBTXTARRAY[i].Text);
				JPFITS.REG.SetReg("CCDLAB", "FitP" + i + "UB_" + FUNCTION_NUM, PUBTXTARRAY[i].Text);
			}
			this.Close();
		}

		private void ConstrainBtn_CheckedChanged(object sender, EventArgs e)
		{
			if (ConstrainBtn.Checked)
				BoundsPnl.Enabled = true;
			else
				BoundsPnl.Enabled = false;

			JPFITS.REG.SetReg("CCDLAB", "FitConstrain", ConstrainBtn.Checked);
		}
	}
}
