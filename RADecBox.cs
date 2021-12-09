using System;
using System.Windows.Forms;

namespace CCDLAB
{
	public partial class RADecBox : Form
	{
		private double RIGHT_ASCENSION, DECLINATION;

		public double RightAscension
		{
			get { return RIGHT_ASCENSION; }
			set { RIGHT_ASCENSION = value; }
		}

		public double Declination
		{
			get { return DECLINATION; }
			set { DECLINATION = value; }
		}

		public RADecBox()
		{
			InitializeComponent();
		}

		private void RAToggle_CheckedChanged(object sender, EventArgs e)
		{
			if (RAToggle.Checked)//display as deg.deg
			{
				RADegTxt.Visible = true;
				RADegTxt.BringToFront();
				RAToggle.Text = "RA: h m s";
				double radeg = Convert.ToDouble(RAhTxt.Text) / 24 * 360 + Convert.ToDouble(RAmTxt.Text) / 60 / 24 * 360 + Convert.ToDouble(RAsTxt.Text) / 3600 / 24 * 360;
				RADegTxt.Text = Math.Round(radeg, 7).ToString();
			}
			else//display as h m s
			{
				RADegTxt.Visible = false;
				RAToggle.Text = "RA: deg.deg";
				double radeg = Convert.ToDouble(RADegTxt.Text);

				if (radeg < 0)
					radeg += 360;

				double h = Math.Floor(radeg / 360 * 24);
				double m = Math.Floor((radeg / 360 * 24 - h) * 60);
				double s = Math.Round((radeg / 360 * 24 - h - m / 60) * 3600, 2);

				RAhTxt.Text = h.ToString();
				RAmTxt.Text = m.ToString();
				RAsTxt.Text = s.ToString();
			}

			JPFITS.REG.SetReg("CCDLAB", "RADecBox_RAToggle", RAToggle.Checked);
		}

		private void RAhTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void RAhTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(RAhTxt.Text);
			}
			catch
			{
				RAhTxt.Text = "0";
			}
		}

		private void RAmTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void RAmTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(RAmTxt.Text);
			}
			catch
			{
				RAmTxt.Text = "0";
			}
		}

		private void RAsTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void RAsTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(RAsTxt.Text);
			}
			catch
			{
				RAsTxt.Text = "0";
			}
		}

		private void OKBtn_Click(object sender, EventArgs e)
		{
			if (RAToggle.Checked)//is displayed as deg.deg
				RIGHT_ASCENSION = Convert.ToDouble(RADegTxt.Text);
			else
				RIGHT_ASCENSION = Convert.ToDouble(RAhTxt.Text) / 24 * 360 + Convert.ToDouble(RAmTxt.Text) / 60 / 24 * 360 + Convert.ToDouble(RAsTxt.Text) / 3600 / 24 * 360;

			if (DecToggle.Checked)//is displayed as deg.deg
				DECLINATION = Convert.ToDouble(DecDegTxt.Text);
			else
			{
				DECLINATION = Convert.ToDouble(DecADTxt.Text) + Convert.ToDouble(DecAMTxt.Text) / 60 + Convert.ToDouble(DecASTxt.Text) / 3600;
				if (DecSignBtn.Text == "-")
					DECLINATION *= -1;
			}

			JPFITS.REG.SetReg("CCDLAB", "RADecBox_RA", RIGHT_ASCENSION.ToString());
			JPFITS.REG.SetReg("CCDLAB", "RADecBox_Dec", DECLINATION.ToString());
			JPFITS.REG.SetReg("CCDLAB", "RADecBoxLeft", this.Left);
			JPFITS.REG.SetReg("CCDLAB", "RADecBoxTop", this.Top);
			JPFITS.REG.SetReg("CCDLAB", "RADecBoxWidth", this.Width);
			JPFITS.REG.SetReg("CCDLAB", "RADecBoxHeight", this.Height);
		}

		private void DecToggle_CheckedChanged(object sender, EventArgs e)
		{
			if (DecToggle.Checked)//display as deg.deg
			{
				DecDegTxt.Visible = true;
				DecSignBtn.Visible = false;
				DecDegTxt.BringToFront();
				DecToggle.Text = "Dec: d ' ''";
				double decdeg = Convert.ToDouble(DecADTxt.Text) + Convert.ToDouble(DecAMTxt.Text) / 60 + Convert.ToDouble(DecASTxt.Text) / 3600;
				if (DecSignBtn.Text == "-")
					decdeg *= -1;
				DecDegTxt.Text = Math.Round(decdeg, 7).ToString();
			}
			else//display as d ' ''
			{
				DecDegTxt.Visible = false;
				DecSignBtn.Visible = true;
				DecToggle.Text = "Dec: deg.deg";
				double decdeg = Math.Abs(Convert.ToDouble(DecDegTxt.Text));

				double d = Math.Floor(decdeg);
				double am = Math.Floor((decdeg - d) * 60);
				double ars = Math.Round((decdeg - d - am / 60) * 3600, 2);
				if (Convert.ToDouble(DecDegTxt.Text) < 0)
					DecSignBtn.Text = "-";
				else
					DecSignBtn.Text = "+";

				DecADTxt.Text = d.ToString();
				DecAMTxt.Text = am.ToString();
				DecASTxt.Text = ars.ToString();
			}

			JPFITS.REG.SetReg("CCDLAB", "RADecBox_DecToggle", DecToggle.Checked);
		}

		private void DecSignBtn_Click(object sender, EventArgs e)
		{
			if (DecSignBtn.Text == "+")
				DecSignBtn.Text = "-";
			else
				DecSignBtn.Text = "+";
		}

		private void DecADTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void DecADTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(DecADTxt.Text);
			}
			catch
			{
				DecADTxt.Text = "0";
			}
		}

		private void DecAMTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void DecAMTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(DecAMTxt.Text);
			}
			catch
			{
				DecAMTxt.Text = "0";
			}
		}

		private void DecASTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void RADegTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void RADegTxt_TextChanged(object sender, EventArgs e)
		{
			if (RADegTxt.Text == "-" || RADegTxt.Text == "-." || RADegTxt.Text == ".")
				return;

			if (RADegTxt.Text.Contains(" "))//for full hms, damas////convert and enter into txtboxes
			{
				double h, m, s, d, am, ars;
				int lastind = 0;
				int nextind = RADegTxt.Text.IndexOf(" ", lastind);
				h = Convert.ToDouble(RADegTxt.Text.Substring(lastind, nextind - lastind));
				lastind = nextind + 1;
				nextind = RADegTxt.Text.IndexOf(" ", lastind);
				m = Convert.ToDouble(RADegTxt.Text.Substring(lastind, nextind - lastind));
				lastind = nextind + 1;
				nextind = RADegTxt.Text.IndexOf(" ", lastind);
				s = Convert.ToDouble(RADegTxt.Text.Substring(lastind, nextind - lastind));
				lastind = nextind + 1;
				nextind = RADegTxt.Text.IndexOf(" ", lastind);
				d = Convert.ToDouble(RADegTxt.Text.Substring(lastind, nextind - lastind));
				lastind = nextind + 1;
				nextind = RADegTxt.Text.IndexOf(" ", lastind);
				am = Convert.ToDouble(RADegTxt.Text.Substring(lastind, nextind - lastind));
				lastind = nextind + 1;
				ars = Convert.ToDouble(RADegTxt.Text.Substring(lastind));

				double radeg = h / 24 * 360 + m / 60 / 24 * 360 + s / 3600 / 24 * 360;
				RADegTxt.Text = Math.Round(radeg, 9).ToString();

				double decdeg = Math.Abs(d) + am / 60 + ars / 3600;
				if (d < 0)
					decdeg *= -1;
				DecDegTxt.Text = Math.Round(decdeg, 9).ToString();
				if (decdeg < 0)
					DecSignBtn.Text = "-";
				else
					DecSignBtn.Text = "+";
			}

			try
			{
				Convert.ToDouble(RADegTxt.Text);
			}
			catch
			{
				RADegTxt.Text = "0";
			}
		}

		private void DecDegTxt_TextChanged(object sender, EventArgs e)
		{
			if (DecDegTxt.Text == "-" || DecDegTxt.Text == "-." || DecDegTxt.Text == ".")
				return;

			try
			{
				Convert.ToDouble(DecDegTxt.Text);
			}
			catch
			{
				DecDegTxt.Text = "0";
			}
		}

		private void RADecBox_Load(object sender, EventArgs e)
		{
			try
			{
				this.Left = (int)JPFITS.REG.GetReg("CCDLAB", "RADecBoxLeft");
				this.Top = (int)JPFITS.REG.GetReg("CCDLAB", "RADecBoxTop");
				this.Width = (int)JPFITS.REG.GetReg("CCDLAB", "RADecBoxWidth");
				this.Height = (int)JPFITS.REG.GetReg("CCDLAB", "RADecBoxHeight");
			}
			catch { }

			RIGHT_ASCENSION = Convert.ToDouble(JPFITS.REG.GetReg("CCDLAB", "RADecBox_RA"));
			RADegTxt.Text = RIGHT_ASCENSION.ToString();
			double h = Math.Floor(RIGHT_ASCENSION / 360 * 24);
			double m = Math.Floor((RIGHT_ASCENSION / 360 * 24 - h) * 60);
			double s = Math.Round((RIGHT_ASCENSION / 360 * 24 - h - m / 60) * 3600, 2);
			RAhTxt.Text = h.ToString();
			RAmTxt.Text = m.ToString();
			RAsTxt.Text = s.ToString();
			RAToggle.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "RADecBox_RAToggle"));

			DECLINATION = Convert.ToDouble(JPFITS.REG.GetReg("CCDLAB", "RADecBox_Dec"));
			DecDegTxt.Text = DECLINATION.ToString();
			double decdeg = Math.Abs(Convert.ToDouble(DecDegTxt.Text));
			double d = Math.Floor(decdeg);
			double am = Math.Floor((decdeg - d) * 60);
			double ars = Math.Round((decdeg - d - am / 60) * 3600, 2);
			if (DECLINATION < 0)
				DecSignBtn.Text = "-";
			else
				DecSignBtn.Text = "+";
			DecADTxt.Text = d.ToString();
			DecAMTxt.Text = am.ToString();
			DecASTxt.Text = ars.ToString();
			DecToggle.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "RADecBox_DecToggle"));
		}

		private void RADecBox_KeyUp(object sender, KeyEventArgs e)
		{

		}

		private void DecDegTxt_KeyPress(object sender, KeyPressEventArgs e)
		{

		}

		private void DecDegTxt_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
				OKBtn.PerformClick();
		}

		private void DecASTxt_TextChanged(object sender, EventArgs e)
		{
			try
			{
				Convert.ToDouble(DecASTxt.Text);
			}
			catch
			{
				DecASTxt.Text = "0";
			}
		}
	}
}
