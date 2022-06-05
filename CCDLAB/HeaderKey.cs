using System;
using System.Windows.Forms;

namespace CCDLAB
{
	public partial class HeaderKey : Form
	{
		public HeaderKey()
		{
			InitializeComponent();
		}

		private void HeaderKey_Load(object sender, EventArgs e)
		{
			textBox1.Text = (string)JPFITS.REG.GetReg("CCDLAB", "NormHeaderKey");
		}

		private void textBox1_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Escape)
			{
				e.SuppressKeyPress = true;
				this.DialogResult = DialogResult.Cancel;
			}

			if (e.KeyCode == Keys.Enter)
			{
				e.SuppressKeyPress = true;
				JPFITS.REG.SetReg("CCDLAB", "NormHeaderKey", textBox1.Text);
				this.DialogResult = DialogResult.OK;
			}
		}
	}
}
