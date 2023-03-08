using System.ComponentModel;
using System.Windows.Forms;
using System;

namespace CCDLAB
{
	public partial class RangeDlg : Form
	{
		private int[] RANGE;

		public int[] Range
		{
			get { return RANGE; }
			set 
			{ 
				RANGE = value;

				XStartUpD.Value = RANGE[0];
				XEndUpD.Value = RANGE[1];
				YStartUpD.Value = RANGE[2];
				YEndUpD.Value = RANGE[3];
			}
		}

		public int XStart
		{
			get { return (int)XStartUpD.Value; }
			set 
			{ 
				XStartUpD.Value = value; 
				RANGE = new int[] { (int)XStartUpD.Value, (int)XEndUpD.Value, (int)YStartUpD.Value, (int)YEndUpD.Value };
			}
		}

		public int YStart
		{
			get { return (int)YStartUpD.Value; }
			set 
			{ 
				YStartUpD.Value = value;
				RANGE = new int[] { (int)XStartUpD.Value, (int)XEndUpD.Value, (int)YStartUpD.Value, (int)YEndUpD.Value };
			}
		}

		public int XEnd
		{
			get { return (int) XEndUpD.Value; }
			set 
			{ 
				XEndUpD.Value= value;
				RANGE = new int[] { (int)XStartUpD.Value, (int)XEndUpD.Value, (int)YStartUpD.Value, (int)YEndUpD.Value };
			}
		}

		public int YEnd
		{
			get { return (int) YEndUpD.Value; }
			set 
			{ 
				YEndUpD.Value= value;
				RANGE = new int[] { (int)XStartUpD.Value, (int)XEndUpD.Value, (int)YStartUpD.Value, (int)YEndUpD.Value };
			}
		}

		public RangeDlg()
		{
			InitializeComponent();

			RANGE = null;
		}

		public RangeDlg(int[] range)
		{
			InitializeComponent();

			this.Range = RANGE;
		}

		private void RangeDlg_HelpButtonClicked(object sender, CancelEventArgs e)
		{
			MessageBox.Show(@"A value of -1 for XStart will cause the full-frame files to load regardless of the other values. Values of XEnd or YEnd,
				 less than or equal to XStart or YStart will likely cause an error.");
		}

		private void OKBtn_Click(object sender, System.EventArgs e)
		{
			RANGE = new int[] { (int)XStartUpD.Value, (int)XEndUpD.Value, (int)YStartUpD.Value, (int)YEndUpD.Value };

			JPFITS.REG.SetReg("CCDLAB", "XStart", XStartUpD.Value);
			JPFITS.REG.SetReg("CCDLAB", "XEnd", XEndUpD.Value);
			JPFITS.REG.SetReg("CCDLAB", "YStart", YStartUpD.Value);
			JPFITS.REG.SetReg("CCDLAB", "YEnd", YEndUpD.Value);
		}

		private void RangeDlg_Load(object sender, System.EventArgs e)
		{
			XStartUpD.Value = Convert.ToDecimal(JPFITS.REG.GetReg("CCDLAB", "XStart"));
			XEndUpD.Value = Convert.ToDecimal(JPFITS.REG.GetReg("CCDLAB", "XEnd"));
			YStartUpD.Value = Convert.ToDecimal(JPFITS.REG.GetReg("CCDLAB", "YStart"));
			YEndUpD.Value = Convert.ToDecimal(JPFITS.REG.GetReg("CCDLAB", "YEnd"));

			RANGE = new int[] { (int)XStartUpD.Value, (int)XEndUpD.Value, (int)YStartUpD.Value, (int)YEndUpD.Value };
		}

		private void XStartUpD_ValueChanged(object sender, EventArgs e)
		{

		}

		private void YStartUpD_ValueChanged(object sender, EventArgs e)
		{

		}

		private void XEndUpD_ValueChanged(object sender, EventArgs e)
		{

		}

		private void YEndUpD_ValueChanged(object sender, EventArgs e)
		{

		}
	}
}
