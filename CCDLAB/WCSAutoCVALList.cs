using System;
using System.Windows.Forms;

namespace CCDLAB
{
	public partial class WCSAutoCVALList : Form
	{
		public string FILENAME = "";
		public string EXTENSIONNAME = "";
		public string[] ITEMLIST;

		//Creates a drop down control with the list of entries inside a specified binary extension table of a FITS file
		public WCSAutoCVALList(string CatalogueFileName, string ExtensionName)
		{
			InitializeComponent();
			FILENAME = CatalogueFileName;
			EXTENSIONNAME = ExtensionName;

			JPFITS.FITSBinTable bt = new JPFITS.FITSBinTable(CatalogueFileName, ExtensionName);
			string[] ttypes = bt.TableDataLabelTTYPEs;

			WCDrop.Items.AddRange(ttypes);
			ITEMLIST = ttypes;
		}

		//Creates a drop down control with the list of binary table extension names in a FITS file
		public WCSAutoCVALList(string CatalogueFileName)
		{
			InitializeComponent();
			FILENAME = CatalogueFileName;
			string[] extensions = JPFITS.FITSBinTable.GetAllExtensionNames(FILENAME);
			WCDrop.Items.AddRange(extensions);
			ITEMLIST = extensions;
		}

		//Creates a drop down control with the given array of String items
		public WCSAutoCVALList(string[] items)
		{
			InitializeComponent();
			WCDrop.Items.AddRange(items);
			ITEMLIST = items;
		}

		private void WCSAutoCVALList1_Shown(object sender, EventArgs e)
		{
			WCDrop.DroppedDown = true;


		}

		private void SearchTxtBox_MouseClick(object sender, MouseEventArgs e)
		{
			WCDrop.DroppedDown = true;
			SearchTxtBox.Focus();
		}

		private void SearchTxtBox_TextChanged(object sender, EventArgs e)
		{
			WCDrop.Items.Clear();
			WCDrop.DroppedDown = true;
			if (SearchTxtBox.Text == null || SearchTxtBox.Text == "")
			{
				WCDrop.Items.AddRange(ITEMLIST);
				WCDrop.DroppedDown = true;
				return;
			}

			for (int i = 0; i < ITEMLIST.Length; i++)
				if (ITEMLIST[i].ToLower().StartsWith(SearchTxtBox.Text.ToLower()))
					WCDrop.Items.Add(ITEMLIST[i]);

			WCDrop.DroppedDown = true;
		}

		private void WCDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			OKBtn.PerformClick();
		}

		private void OKBtn_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.OK;
			this.Close();
		}

		private void CancelBtn_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.Cancel;
			this.Close();
		}
	}
}
