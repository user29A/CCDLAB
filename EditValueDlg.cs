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
	public partial class EditValueDlg : Form
	{
		public EditValueDlg()
		{
			InitializeComponent();
		}

		private void EditValueDlg_Shown(object sender, EventArgs e)
		{
			EditValueTxt.Focus();
			EditValueTxt.SelectAll();
		}
	}
}
