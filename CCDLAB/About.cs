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
	public partial class About : Form
	{
		Form1 FORM;
		public About(Form1 form1)
		{
			InitializeComponent();

			FORM = form1;
		}

		private void About_Load(object sender, EventArgs e)
		{
			string s = "CCDLAB for Ultra Violet Imaging Telescope support.\r\n\r\n";
			s += "Release Date: " + "2021" + "-" + "11" + "-" + "15" + "\r\n\r\n";
			s += "Developer: Joeseph E Postma.  Copyright.\r\n\r\n";
			s+= "Contact: joepostma@live.ca\r\n\r\n";
			s += "License: This software is released under GNU Public General License v 3.0 (GPLv3).\r\n\r\n";
			s += "License summary and a link to the full license code can be found here:  http://www.gnu.org/licenses/";
			
			AboutTextLabel.Text = s;
		}

		private void About_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Escape)
				this.Close();

			if (e.Modifiers == Keys.Alt)
				if (e.KeyCode == Keys.D)
					if (!DevTextBox.Visible)
						DevTextBox.Visible = true;
					else
						DevTextBox.Visible = false;
		}

		private void DevTextBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
				if (DevTextBox.Text.ToLower() == "deactivate uvit")
				{
					FORM.MainTab.TabPages.Remove(FORM.UVITTab);
					FORM.UVITMenu.Visible = false;
				}
				else if (DevTextBox.Text.ToLower() == "activate uvit")
				{
					FORM.MainTab.TabPages.Add(FORM.UVITTab);
					FORM.UVITMenu.Visible = true;
				}
		}
	}
}
