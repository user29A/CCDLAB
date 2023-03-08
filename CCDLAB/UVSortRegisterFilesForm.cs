using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace CCDLAB
{
	public partial class UVSortRegisterFilesForm : Form
	{
		private string[] XYINTSLIST;
		private string[] FILELIST;

		public UVSortRegisterFilesForm(string[] files)
		{
			InitializeComponent();
			XYINTSLIST = files;
			FILELIST = new string[files.Length];

			for (int i = 0; i < XYINTSLIST.Length; i++)
			{
				FileInfo fileinf = new FileInfo(XYINTSLIST[i]);
				string imgnamepattern = fileinf.Name.Substring(0, fileinf.Name.LastIndexOf(".")) + "_IMAGE";
				imgnamepattern = imgnamepattern.Replace("XYInts_List_", "");
				string imgname = Directory.GetFiles(fileinf.DirectoryName, "*" + imgnamepattern + "*")[0];
				JPFITS.FITSHeader header = new JPFITS.FITSHeader(imgname);
				string time = header.GetKeyValue("RDCDTIME");
				FILELIST[i] = fileinf.Name + " (" + time + "s)";
				FileList.Items.Add(FILELIST[i]);
			}
		}

		public string[] SortedFileList
		{
			get { return XYINTSLIST; }
		}

		private void FileList_MouseUp(object sender, MouseEventArgs e)
		{
			if (FileList.SelectedIndices.Count > 0)
			{
				groupBox1.Enabled = true;

				if (FileList.SelectedIndices.Count > 1)
					for (int i = 1; i < FileList.SelectedIndices.Count; i++)
						if (FileList.SelectedIndices[i] - FileList.SelectedIndices[i - 1] > 1)
						{
							MoveUpBtn.Enabled = false;
							MoveDownBtn.Enabled = false;
							return;
						}
				if (FileList.GetSelected(0))
					MoveUpBtn.Enabled = false;
				else
					MoveUpBtn.Enabled = true;

				if (FileList.GetSelected(FileList.Items.Count - 1))
					MoveDownBtn.Enabled = false;
				else
					MoveDownBtn.Enabled = true;
			}
		}

		private void MoveBottomBtn_Click(object sender, EventArgs e)
		{
			if (FileList.SelectedIndices.Count == 0)
				return;

			string[] tempxyints = new string[XYINTSLIST.Length - FileList.SelectedIndices.Count];
			string[] tempfilelist = new string[XYINTSLIST.Length - FileList.SelectedIndices.Count];
			string[] selecteddxyints = new string[FileList.SelectedIndices.Count];
			string[] selectedfilelist = new string[FileList.SelectedIndices.Count];
			int c = 0, cc = 0;

			for (int i = 0; i < FILELIST.Length; i++)
				if (!FileList.GetSelected(i))
				{
					tempxyints[c] = XYINTSLIST[i];
					tempfilelist[c++] = FILELIST[i];
				}
				else
				{
					selecteddxyints[cc] = XYINTSLIST[i];
					selectedfilelist[cc++] = FILELIST[i];
				}

			c = 0;
			for (int i = 0; i < FILELIST.Length; i++)
				if (i < tempxyints.Length)
				{
					FILELIST[i] = tempfilelist[i];
					XYINTSLIST[i] = tempxyints[i];
				}
				else
				{
					FILELIST[i] = selectedfilelist[c];
					XYINTSLIST[i] = selecteddxyints[c++];
				}

			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);

			for (int i = 0; i < selecteddxyints.Length; i++)
				FileList.SetSelected(XYINTSLIST.Length - selecteddxyints.Length + i, true);

			MoveUpBtn.Enabled = true;
			MoveDownBtn.Enabled = false;
		}

		private void MoveTopBtn_Click(object sender, EventArgs e)
		{
			if (FileList.SelectedIndices.Count == 0)
				return;

			string[] tempxyints = new string[XYINTSLIST.Length - FileList.SelectedIndices.Count];
			string[] tempfilelist = new string[XYINTSLIST.Length - FileList.SelectedIndices.Count];
			string[] selecteddxyints = new string[FileList.SelectedIndices.Count];
			string[] selectedfilelist = new string[FileList.SelectedIndices.Count];
			int c = 0, cc = 0;

			for (int i = 0; i < FILELIST.Length; i++)
				if (!FileList.GetSelected(i))
				{
					tempxyints[c] = XYINTSLIST[i];
					tempfilelist[c++] = FILELIST[i];
				}
				else
				{
					selecteddxyints[cc] = XYINTSLIST[i];
					selectedfilelist[cc++] = FILELIST[i];
				}

			c = 0;
			for (int i = 0; i < FILELIST.Length; i++)
				if (i < selectedfilelist.Length)
				{
					FILELIST[i] = selectedfilelist[i];
					XYINTSLIST[i] = selecteddxyints[i];
				}
				else
				{
					FILELIST[i] = tempfilelist[c];
					XYINTSLIST[i] = tempxyints[c++];
				}


			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);

			for (int i = 0; i < selecteddxyints.Length; i++)
				FileList.SetSelected(i, true);

			MoveUpBtn.Enabled = false;
			MoveDownBtn.Enabled = true;
		}

		private void MoveUpBtn_Click(object sender, EventArgs e)
		{
			if (FileList.SelectedIndices.Count == 0)
				return;
			if (FileList.GetSelected(0))
				return;
			if (FileList.SelectedItems.Count == FILELIST.Length)
				return;

			int[] indslist = new int[FileList.SelectedIndices.Count];
			for (int i = 0; i < indslist.Length; i++)
				indslist[i] = FileList.SelectedIndices[i];

			string tempfilelist = FILELIST[FileList.SelectedIndices[0] - 1];
			string tempxyintslist = XYINTSLIST[FileList.SelectedIndices[0] - 1];

			for (int i = FileList.SelectedIndices[0]; i <= FileList.SelectedIndices[FileList.SelectedIndices.Count - 1]; i++)
			{
				FILELIST[i - 1] = FILELIST[i];
				XYINTSLIST[i - 1] = XYINTSLIST[i];
			}
			FILELIST[FileList.SelectedIndices[FileList.SelectedIndices.Count - 1]] = tempfilelist;
			XYINTSLIST[FileList.SelectedIndices[FileList.SelectedIndices.Count - 1]] = tempxyintslist;

			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);

			for (int i = 0; i < indslist.Length; i++)
				FileList.SetSelected(indslist[i] - 1, true);

			if (FileList.GetSelected(0))
				MoveUpBtn.Enabled = false;

			if (!FileList.GetSelected(FileList.Items.Count - 1))
				MoveDownBtn.Enabled = true;
		}

		private void MoveDownBtn_Click(object sender, EventArgs e)
		{
			if (FileList.SelectedIndices.Count == 0)
				return;
			if (FileList.GetSelected(FileList.Items.Count - 1))
				return;
			if (FileList.SelectedItems.Count == FILELIST.Length)
				return;

			int[] indslist = new int[FileList.SelectedIndices.Count];
			for (int i = 0; i < indslist.Length; i++)
				indslist[i] = FileList.SelectedIndices[i];

			string tempfilelist = FILELIST[FileList.SelectedIndices[FileList.SelectedIndices.Count - 1] + 1];
			string tempxyintslist = XYINTSLIST[FileList.SelectedIndices[FileList.SelectedIndices.Count - 1] + 1];

			for (int i = FileList.SelectedIndices[FileList.SelectedIndices.Count - 1]; i >= FileList.SelectedIndices[0]; i--)
			{
				FILELIST[i + 1] = FILELIST[i];
				XYINTSLIST[i + 1] = XYINTSLIST[i];
			}
			FILELIST[FileList.SelectedIndices[0]] = tempfilelist;
			XYINTSLIST[FileList.SelectedIndices[0]] = tempxyintslist;

			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);

			for (int i = 0; i < indslist.Length; i++)
				FileList.SetSelected(indslist[i] + 1, true);

			if (!FileList.GetSelected(0))
				MoveUpBtn.Enabled = true;

			if (FileList.GetSelected(FileList.Items.Count - 1))
				MoveDownBtn.Enabled = false;
		}

		private void SortAlphabeticalBtn_Click(object sender, EventArgs e)
		{
			Array.Sort(FILELIST, XYINTSLIST);

			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);

			groupBox1.Enabled = false;
		}
		
		private void SortReverseBtn_Click(object sender, EventArgs e)
		{
			Array.Reverse(XYINTSLIST);
			Array.Reverse(FILELIST);

			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);

			groupBox1.Enabled = false;
		}

		private void OKBtn_Click(object sender, EventArgs e)
		{

		}

		private void SortExpTimeBtn_Click(object sender, EventArgs e)
		{
			double[] exptimes = new double[FILELIST.Length];
			for (int i = 0; i < exptimes.Length; i++)
			{
				int fi = FILELIST[i].LastIndexOf("(");
				int li = FILELIST[i].LastIndexOf("s");
				exptimes[i] = Convert.ToDouble(FILELIST[i].Substring(fi + 1, li - fi - 1));
			}

			Array.Sort(exptimes, XYINTSLIST);

			for (int i = 0; i < exptimes.Length; i++)
			{
				int fi = FILELIST[i].LastIndexOf("(");
				int li = FILELIST[i].LastIndexOf("s");
				exptimes[i] = Convert.ToDouble(FILELIST[i].Substring(fi + 1, li - fi - 1));
			}

			Array.Sort(exptimes, FILELIST);
			Array.Reverse(FILELIST);

			FileList.Items.Clear();
			FileList.Items.AddRange(FILELIST);
		}
	}
}
