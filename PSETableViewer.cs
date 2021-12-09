using System;
using System.IO;
using System.Windows.Forms;

namespace CCDLAB
{
	public partial class PSETableViewer : Form
	{
		public PSETableViewer()
		{
			InitializeComponent();
		}

		private void PSETableViewerSaveBtn_Click(object sender, EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.Filter = "Tab Delimited Text|*.txt|CSV (Comma Delimited)|*.csv";//|FITS Binary Table|*.fits";
			sfd.FilterIndex = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "PSESaveFilter"));
			sfd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "PSESavePath");
			//sfd.FileName = "a" + ((CCDLAB.Form1 ^)(this.Owner)).SubImageRATxt.Text + "d" + ((CCDLAB.Form1 ^)(this.Owner)).SubImageDecTxt.Text;
			if (sfd.FileName.Contains("a0d0"))
				sfd.FileName = "";
			if (sfd.ShowDialog() == DialogResult.Cancel)
				return;
			JPFITS.REG.SetReg("CCDLAB", "PSESavePath", sfd.FileName.Substring(0, sfd.FileName.LastIndexOf("\\")));
			JPFITS.REG.SetReg("CCDLAB", "PSESaveFilter", sfd.FilterIndex);

			if (sfd.FilterIndex < 3)
			{
				string delimit;
				if (sfd.FilterIndex == 1)
					delimit = "\t";
				else
					delimit = ",";

				StreamWriter sw = new StreamWriter(sfd.FileName);
				string str = "";

				for (int i = 0; i < PSETable.ColumnCount; i++)
					str += PSETable.Columns[i].HeaderText + delimit;
				str = str.Substring(0, str.Length - 1);
				sw.WriteLine(str);

				for (int j = 0; j < PSETable.RowCount; j++)
				{
					str = "";
					for (int i = 0; i < PSETable.ColumnCount; i++)
						str += PSETable[i, j].Value + delimit;
					str = str.Substring(0, str.Length - 1);
					sw.WriteLine(str);
				}

				sw.Close();
			}
			else//fits bin table
			{
				//can't actually do this because a PSE table has both numeric and text entries...so not all simply binary numbers
				//would need to do an ascii table instead
				//so...need to write ascii table for the JPFITS pkg

				/*array<String^>^ labels = new array<String^>(PSETable.ColumnCount);
				array<TypeCode>^ types = new array<TypeCode>(PSETable.ColumnCount);
				array<int>^ instances = new array<int>(PSETable.ColumnCount);
				array<String^>^ units = new array<String^>(PSETable.ColumnCount);
				array<Object^>^ data = new array<Object^>(PSETable.ColumnCount);

				for (int i = 0; i < PSETable.ColumnCount; i++)
				{
					labels[i] = PSETable.Columns[i].HeaderText;
					types[i] = 
				}

				JPFITS.FITSBinTable.BinaryTableExtension_Write(sfd.FileName, "", true, labels, types, instances, units, nullptr, nullptr, nullptr, data)*/
			}
		}

		private void PSETable_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			try
			{
				double x, y;
				if (PSETable.Columns[1].HeaderText == "P1")
				{
					x = Convert.ToDouble(PSETable[1, e.RowIndex].Value.ToString());
					y = Convert.ToDouble(PSETable[2, e.RowIndex].Value.ToString());
				}
				else
				{
					x = Convert.ToDouble(PSETable[0, e.RowIndex].Value.ToString());
					y = Convert.ToDouble(PSETable[1, e.RowIndex].Value.ToString());
				}

				/*((CCDLAB.Form1 ^)(this.Owner)).PSESeachROIOnlyChck.SuspendLayout();
				((CCDLAB.Form1 ^)(this.Owner)).PSESeachROIOnlyChck.Checked = false;
				((CCDLAB.Form1 ^)(this.Owner)).PSESeachROIOnlyChck.ResumeLayout();

				((CCDLAB.Form1 ^)(this.Owner)).SubImageSlideX.Value = (int)x + 1;
				((CCDLAB.Form1 ^)(this.Owner)).SubImageSlideY.Value = (int)y + 1;
				((CCDLAB.Form1 ^)(this.Owner)).SubImageStatsUpD();
				((CCDLAB.Form1 ^)(this.Owner)).SubImageUpD();
				((CCDLAB.Form1 ^)(this.Owner)).ShowCrosshair.Checked = true;
				((CCDLAB.Form1 ^)(this.Owner)).ImageWindow.Refresh();*/
			}
			catch { }
		}

		private void button1_Click(object sender, EventArgs e)
		{
			this.Close();
		}
	}
}
