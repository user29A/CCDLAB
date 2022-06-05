using System;
using System.IO;
using System.Collections;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace CCDLAB
{
	public partial class GSEExtractImg : Form
	{
		public static string[] FULLFILELIST;
		public static string[] FILELIST;
		string FILEPATH;
		public static string SENDER = " ";
		public static int NIMAGE = 0;//just a counter for having different filenames when intserting into the IMAGESET
		public static uint IMFRCNT = 0;//image frame count: reset to zero in GSE when imaging mode changed or power up
		public static uint IMTIME = 0;//millisec
		public static int XSIZE = 0;//these next 4 are all zero based
		public static int YSIZE = 0;
		public static int XOFFSET = 0;
		public static int YOFFSET = 0;
		public static int PIXTHRSH = 0;
		public static int ENGTHRSH = 0;
		public static double ROWGAPT = 0;//usec
		public static int GAIN = 0;
		public static int STACKING = 0;
		public static int NORMLZN = 0;
		public static int BODL = 0;
		public static int BODH = 0;
		public static int BODF = 0;
		public static int ANDVOLTS_CMD = 0;
		public static int MCPVOLTS_CMD = 0;
		public static int PCVOLTS_CMD = 0;
		public static int ANDVOLTS_TEL = 0;
		public static int MCPVOLTS_TEL = 0;
		public static int CATVOLTS_TEL = 0;
		public static double HVUCURRENT_TEL = 0;
		public static double REAp5V = 0;
		public static double REAp5VpDN = 2.93; //mV
		public static double REAp3p3V = 0;
		public static double REAp3p3VpDN = 2.93;//		mV
		public static double REAp12V = 0;
		public static double REAm12V = 0;
		public static double REA12VpDN = 16.1; //mV
		public static double HVUp30V = 0;
		public static double HVU30VpDN = 16.1;//		mV
		public static double HVUp15V = 0;
		public static double HVUm15V = 0;
		public static double HVU15VpDN = 16.1;//		mV
		public static double CPUp12V = 0;
		public static double CPUm12V = 0;
		public static double CPU12VpDN = 16.1;//	mV
		public static double ZEROVREF = 0;
		public static double ZEROVREFVpDN = 1.46;  //mV
		public static double REAp5VCUR = 0;
		public static double REA5VApDN = 3.08; //mA
		public static double REAp3p3VCUR = 0;
		public static double REA3p3VApDN = 2.93;   //mA
		public static double REAm12VCUR = 0;
		public static double REAp12VCUR = 0;
		public static double REA12VApDN = 0.185;   //mA
		public static double HVUp30VCUR = 0;
		public static double HVU30VApDN = 0.432;   //mA
		public static double HVUp15VCUR = 0;
		public static double HVUm15VCUR = 0;
		public static double HVU15VApDN = 0.185;   //mA
		public static double CPUm12VCUR = 0;
		public static double CPUp12VCUR = 0;
		public static double CPU12VApDM = 0.185;   //mA
		public static double ANDCMDVpDN = 1.954;
		public static double MCPCMDVpDN = 0.977;
		public static double PCCMDVpDN = -0.195;
		public static double ANDTELVpDN = 9.4172;
		public static double MCPTELVpDN = 4.7086;
		public static double CATTELVpDN = -0.4709;
		public static double HVUTELApDN = 0.04709;  //uA 
		public static double RSETBIAS = 0;//V
		public static double RAMPTIME = 0;//sec
		public static double RAMPTTOT = 0;//total ramp time
		public static double TOTTIME = 0;
		public static double TOTFRAMS = 0;
		public static double GLOBRATE = 0;//count rate
		public static double SPOTRATE = 0;//count rate
		public static double RATEPSEC = 0;//count rate per second
		public static double FRAMPSEC = 0;
		public static string CHANNEL = "";
		public static int EXTRCN_CHANNEL = 0;//14, 15, 16 = FUV, NUV, VIS
		public static string MODE = "";
		public static string SOURCE = "";
		public static string ALGRTHM = "";
		JPFITS.WaitBar wb;
		public static int[] SUBRANGE = new int[] { 0, 511, 0, 511 };//zero-based subrange for extraction
		public static bool ISSYNCHED = false;
		public static bool ISFRAMESYNCH = false;
		public static byte[] ARR = new byte[1024 * 1024 * 500];
		public static uint FILENAMETIME = 0;
		static bool ISAC_Chunked = false;
		int NSplits;
		string[] delete_chunks = null;
		string orignonchunkfile = "";

		public GSEExtractImg()
		{
			InitializeComponent();
		}

		private void eXITToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void exitCCDLABToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		private void GSEExtractImg_Load(object sender, EventArgs e)
		{
			try
			{
				ChannelDrop.SelectedIndex = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "CentroidChannel"));//0 = FUV, 1 = NUV, 2 = VIS;
				ExtParityChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "ExtParityChck"));
				ExtractListChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "ExtractListChck"));
				AugFilesChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "AugFilesChck"));
				GSEApplyDistortionCorrectionChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "GSEApplyDist"));
				GSEApplyFPNCorrectionChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "GSEApplyFPN"));
				centroidListImageCorrectionsToolStripMenuItem.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "centroidListImageCorrect"));
				FixBadTimesHighValuesChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "FixBadTimesHigh"));
				FixBadTimesLowValuesChck.Checked = Convert.ToBoolean(JPFITS.REG.GetReg("CCDLAB", "FixBadTimesLow"));
			}
			catch
			{
			}
		}

		private void GSEExtractImg_FormClosed(object sender, FormClosedEventArgs e)
		{

		}

		private void OpenImgBtn_Click(object sender, EventArgs e)
		{
			GC.Collect();
			GC.WaitForFullGCApproach();
			GC.WaitForFullGCComplete();
			GC.WaitForPendingFinalizers();

			OpenImgFileDlg.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath");
			OpenImgFileDlg.Filter = "GSE or L0-RAW File (*.img; *.raw;)|*.img; *.raw|IMG File (*.img)|*.img|L0-RAW File (*.raw)|*.raw|All Files (*.*)|*.*";

			OpenImgFileDlg.ShowDialog();
		}

		private void OpenImgFileDlg_FileOk(object sender, CancelEventArgs e)
		{
			FULLFILELIST = OpenImgFileDlg.FileNames;
			Array.Sort(FULLFILELIST);
			FILELIST = new string[FULLFILELIST.Length];
			int j = 0;
			for (int i = 0; i < FULLFILELIST.Length; i++)
			{
				j = FULLFILELIST[i].LastIndexOf("\\");
				FILELIST[i] = FULLFILELIST[i].Substring(j + 1);
			}
			FILEPATH = FULLFILELIST[0].Substring(0, j + 1);
			FileListDrop.Items.Clear();
			FileListDrop.Items.AddRange(FILELIST);
			FileListDrop.Enabled = true;
			FileListDrop.SelectedIndex = 0;
			ExtractPanel.Enabled = true;
			JPFITS.REG.SetReg("CCDLAB", "GSEOpenFilesPath", FILEPATH);
		}

		private void FileListDropDown_SelectedIndexChanged(object sender, EventArgs e)
		{
			ExtractImagesBtn.Enabled = false;
			int Nfile = FileListDrop.SelectedIndex;
			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			long Nbytes = fs.Length;
			fs.Close();
			long Nwords = Nbytes / 2;//word is uint16 = 2 bytes
			long Nsegments = Nwords / 1024;//segment is 1024 words = 2048 bytes
			StartSegmentUpD.Maximum = Nsegments;
			StartWordUpD.Maximum = Nwords - 1024 + 1;
			ViewWordsBtn_Click(sender, e);
		}

		private void NWordsUpD_ValueChanged(object sender, EventArgs e)
		{
			ViewWordsBtn_Click(sender, e);
		}

		private void StartSegmentUpD_ValueChanged(object sender, EventArgs e)
		{
			int Nfile = FileListDrop.SelectedIndex;
			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			long Nbytes = fs.Length;
			fs.Close();
			int Nsegment = (int)StartSegmentUpD.Value;
			int Nstartword = (int)StartWordUpD.Value;
			int Nwords = (Nsegment - 1) * 1024 + 1;
			if (!SENDER.Equals("StartWordUpD"))
			{
				fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
				Nbytes = fs.Length;
				fs.Close();
				NWordsUpD.Maximum = Nbytes / 2 - Nstartword + 1;
				StartWordUpD.Value = Nwords;
				ViewWordsBtn_Click(sender, e);
			}
			SENDER = "StartSegmentUpD";
		}

		private void StartWordUpD_ValueChanged(object sender, EventArgs e)
		{

			SENDER = "StartWordUpD";
			int Nfile = FileListDrop.SelectedIndex;
			int Nstartword = (int)StartWordUpD.Value;
			int Nsegment = (Nstartword - 1) / 1024 + 1;
			StartSegmentUpD.Value = Nsegment;
			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			long Nbytes = fs.Length;
			fs.Close();
			NWordsUpD.Maximum = Nbytes / 2 - Nstartword + 1;
			ViewWordsBtn_Click(sender, e);
		}

		private void ViewWordsBtn_Click(object sender, EventArgs e)
		{

			int Nwords = (int)NWordsUpD.Value;
			int Nstartword = (int)StartWordUpD.Value;//1-based
			int Nfile = FileListDrop.SelectedIndex;
			ushort word = 0;
			string bits = "";
			string hex = "";
			WordListGrid.RowCount = 0;
			WordListGrid.RowCount = Nwords;

			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			BinaryReader br = new BinaryReader(fs);

			if (Nstartword * 2 > fs.Length)
			{
				MessageBox.Show(string.Concat("Start Word exceeds file size. File is ", fs.Length / 2, " words long.  Setting start position for you, to eof - #Words."), "Error");
				StartWordUpD.Value = fs.Length / 2 - Nwords + 1;
				br.Close();
				fs.Close();
				return;
			}
			if ((Nstartword + Nwords - 1) * 2 > fs.Length)
			{
				int n = -((int)fs.Length - (Nstartword + Nwords - 1) * 2) / 2;
				MessageBox.Show(string.Concat("#Words exceeds file size from Start Word by ", n, " words. File is ", fs.Length / 2, " words long.  Setting start position for you, to eof-#Words."), "Error");
				StartWordUpD.Value = fs.Length / 2 - Nwords + 1;
				br.Close();
				fs.Close();
				return;
			}

			fs.Position = (long)((Nstartword - 1) * 2);/*to zero based, and found in bytes not words*/
			//bs.Read(arr,0,NWords*2);
			for (int i = 0; i < Nwords; i++)
			{
				word = (ushort)(ReadWord(br));//little endian word
				bits = new System.Collections.Specialized.BitVector32(word).ToString();
				bits = bits.Substring(28, 16);
				hex = string.Format("{0:X}", word);
				WordListGrid[0, i].Value = string.Concat(Nstartword + i, " (", i + 1, ")");
				WordListGrid[1, i].Value = hex;
				WordListGrid[2, i].Value = bits;
				WordListGrid[3, i].Value = word;
			}
			br.Close();
			fs.Close();
			PopulateSegmentInfo(sender, e);
		}

		private void PopulateSegmentInfo(object sender, EventArgs e)
		{
			int Nfile = FileListDrop.SelectedIndex;
			ushort word = 0;
			ushort test = 0;
			//string bits = "";
			//string hex = "";
			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			BinaryReader br = new BinaryReader(fs);
			int Nsegment = (int)StartSegmentUpD.Value;//1-based
			int Nwords = (int)NWordsUpD.Value;
			int Nstartword = (int)StartWordUpD.Value;//1-based
			int n = -1;

			SegmentInfoGrid.RowCount = 0;
			SegmentInfoGrid.RowCount = 100;

			//Assuming Nstartword is synched to first segment of image...if not use the button to do that
			fs.Position = (long)((Nstartword - 1) * 2);/*to zero based, and found in bytes not words, sets to position just before first word of segment*/
			//i.e., readUInt16 would read the first word

			//Packet Identification - Application Process ID (UVIT Channel)
			fs.Position = fs.Position + (2) * 2;//skip sync
			word = (ushort)(ReadWord(br));
			n++;
			SegmentInfoGrid[0, n].Value = "Channel";
			test = (ushort)(word & 0x1F);//zero irrelevant bits so logic below can work always, no shifting needed
			if (test == 0x0E)
			{
				CHANNEL = "FUV";
				EXTRCN_CHANNEL = 14;
				//ChannelDrop.SelectedIndex = 0;
			}
			else if (test == 0x0F)
			{
				CHANNEL = "NUV";
				EXTRCN_CHANNEL = 15;
				//ChannelDrop.SelectedIndex = 1;
			}
			else if (test == 0x10)
			{
				CHANNEL = "VIS";
				EXTRCN_CHANNEL = 16;
				//ChannelDrop.SelectedIndex = 2;
			}
			else
			{
				CHANNEL = "Error";
				EXTRCN_CHANNEL = 0;
			}
			SegmentInfoGrid[1, n].Value = CHANNEL;

			//Packet Sequence Control - Segment Type (first 2 bits) and Source Sequence Count (remaining bits)
			word = (ushort)(ReadWord(br));
			n++;
			SegmentInfoGrid[0, n].Value = "Segment Type";
			test = (ushort)((word & 0xC000) >> 14);//zero irrelevant bits so logic below can work always, and shift first 2 relevant bits to bottom
			if (test == 0)
			{
				SegmentInfoGrid[1, n].Value = "Continuation";
				ISFRAMESYNCH = false;
			}
			else if (test == 1)
			{
				SegmentInfoGrid[1, n].Value = "First";
				ISFRAMESYNCH = true;
			}
			else if (test == 2)
			{
				SegmentInfoGrid[1, n].Value = "Last";
				ISFRAMESYNCH = false;
			}
			else if (test == 3)
			{
				SegmentInfoGrid[1, n].Value = "Unsegmented";
				ISFRAMESYNCH = false;
			}
			else
			{
				SegmentInfoGrid[1, n].Value = "Error";
				ISFRAMESYNCH = false;
			}

			test = (ushort)(word & 0x3FFF);//zero first 2 bits to get numeric value of count
			n++;
			SegmentInfoGrid[0, n].Value = "Segment Number";
			SegmentInfoGrid[1, n].Value = test;

			//Image Frame Count (all bits)
			fs.Position = fs.Position + (2) * 2;
			IMFRCNT = ReadWord(br);
			n++;
			SegmentInfoGrid[0, n].Value = "Image Number";
			SegmentInfoGrid[1, n].Value = IMFRCNT;

			//Image Frame Time - next 2 16bit lines to make 32bit value MSW first then LSW second.
			ushort msw16 = ReadWord(br);
			ushort lsw16 = ReadWord(br);
			uint msw32 = (uint)msw16;
			msw32 = (msw32 << 16) | (uint)lsw16;
			n++;
			SegmentInfoGrid[0, n].Value = "Image Time";
			SegmentInfoGrid[1, n].Value = msw32;
			IMTIME = msw32;

			//Row Gap Time
			fs.Position = fs.Position + (4) * 2;
			word = (ushort)(ReadWord(br) & 0x1FF);
			n++;
			SegmentInfoGrid[0, n].Value = "Gap Time";
			ROWGAPT = (double)(word);//*6.39;//usec
			SegmentInfoGrid[1, n].Value = ROWGAPT;


			//First segment telem ends
			if (!ISFRAMESYNCH)
				goto skipnontelem;


			//Gain
			word = (ushort)(ReadWord(br) & 0x3);
			n++;
			GAIN = (int)Math.Pow(2, word);
			SegmentInfoGrid[0, n].Value = "Gain";
			SegmentInfoGrid[1, n].Value = GAIN;

			//Reset Bias
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			SegmentInfoGrid[0, n].Value = "Reset Bias";
			RSETBIAS = (double)(word) * .001950;//V
			SegmentInfoGrid[1, n].Value = RSETBIAS;

			//Image Configuration (size)
			//X Offset
			word = (ushort)(ReadWord(br) & 0x1FF);
			n++;
			SegmentInfoGrid[0, n].Value = "X Offset";
			SegmentInfoGrid[1, n].Value = word;
			XOFFSET = word;
			//Y Offset
			word = (ushort)(ReadWord(br) & 0x1FF);
			n++;
			SegmentInfoGrid[0, n].Value = "Y Offset";
			SegmentInfoGrid[1, n].Value = word;
			YOFFSET = word;
			//X Size
			word = (ushort)(ReadWord(br) & 0x1FF);
			n++;
			SegmentInfoGrid[0, n].Value = "X Size";
			SegmentInfoGrid[1, n].Value = word;
			XSIZE = word;
			//Y Size
			word = (ushort)(ReadWord(br) & 0x1FF);
			n++;
			SegmentInfoGrid[0, n].Value = "Y Size";
			SegmentInfoGrid[1, n].Value = word;
			YSIZE = word;
			StartSegmentUpD.Increment = (int)((XSIZE + 1) * (YSIZE + 1) / 1008 + 1) + 1;//number of segments per image

			//Timing Master Select
			//Channel, Mode, and Source
			word = (ushort)(ReadWord(br));
			n++;
			SegmentInfoGrid[0, n].Value = "Mode";//do mode first
			test = (ushort)((word & 0xC) >> 2);
			if (test == 1)
			{
				MODE = "Centroiding";
				ExtractImagesBtn.Enabled = false;
				ViewImageBtn.Enabled = true;
				ExtCentPanel.Enabled = true;
				SubImChck.Enabled = true;
				EveryNUpD.Enabled = true;
				StatsOnlyChck.Enabled = false;
				StatsOnlyChck.Checked = false;
				ChannelDrop.Enabled = true;
			}
			else if (test == 2)
			{
				MODE = "Integration";
				ExtractImagesBtn.Enabled = true;
				ViewImageBtn.Enabled = true;
				ExtCentPanel.Enabled = false;
				SubImChck.Enabled = true;
				EveryNUpD.Enabled = true;
				StatsOnlyChck.Enabled = true;
				ChannelDrop.Enabled = true;
			}
			else
			{
				MODE = "Error";
				ExtractImagesBtn.Enabled = false;
				ViewImageBtn.Enabled = false;
				ExtCentPanel.Enabled = false;
				SubImChck.Enabled = false;
				EveryNUpD.Enabled = false;
				StatsOnlyChck.Checked = false;
				StatsOnlyChck.Enabled = false;
			}
			SegmentInfoGrid[1, n].Value = MODE;

			n++;
			SegmentInfoGrid[0, n].Value = "Source";//do source now
			test = (ushort)(word & 0x3);
			if (test == 0)
				SOURCE = "Electrcl Cntrd";
			else if (test == 1)
				SOURCE = "Electrcl Thruput";
			else if (test == 2)
				SOURCE = "Intensifier";
			else
				SOURCE = "Error";
			SegmentInfoGrid[1, n].Value = SOURCE;

			//Centroid Algorithm
			n++;
			SegmentInfoGrid[0, n].Value = "Algorithm";
			test = (ushort)((ReadWord(br) & 0xC0) >> 6);
			if (test == 0)
				ALGRTHM = "3x3 Cross";
			else if (test == 1)
				ALGRTHM = "3x3 Square";
			else if (test == 2)
				ALGRTHM = "5x5 Square";
			else
				ALGRTHM = "Error";
			SegmentInfoGrid[1, n].Value = ALGRTHM;

			//Stacking & Normlization
			word = (ushort)(ReadWord(br) & 0x3F);
			STACKING = (int)Math.Pow(2, (word & 0x38) >> 3);
			NORMLZN = (int)Math.Pow(2, (word & 0x7));
			n++;
			SegmentInfoGrid[0, n].Value = "Stacking";
			SegmentInfoGrid[1, n].Value = STACKING;
			n++;
			SegmentInfoGrid[0, n].Value = "Normalization";
			SegmentInfoGrid[1, n].Value = NORMLZN;

			//Ramp Up Time
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			SegmentInfoGrid[0, n].Value = "Ramp Time";
			RAMPTIME = (double)(word) * 0.0001;//sec
			SegmentInfoGrid[1, n].Value = RAMPTIME;

			//Pixel Thresh
			word = (ushort)(ReadWord(br) & 0x3FFF);
			n++;
			SegmentInfoGrid[0, n].Value = "Pixel Thresh";
			SegmentInfoGrid[1, n].Value = word;
			PIXTHRSH = word;

			//Energy Thresh
			word = (ushort)(ReadWord(br) & 0x3FFF);
			n++;
			SegmentInfoGrid[0, n].Value = "Energy Thresh";
			ENGTHRSH = word * 32;
			SegmentInfoGrid[1, n].Value = ENGTHRSH;

			//Bright Object Length
			word = (ushort)(ReadWord(br));
			n++;
			SegmentInfoGrid[0, n].Value = "BOD Length";
			SegmentInfoGrid[1, n].Value = word;
			BODL = word;

			//Bright Object Height
			word = (ushort)(ReadWord(br));
			n++;
			SegmentInfoGrid[0, n].Value = "BOD Height";
			SegmentInfoGrid[1, n].Value = word;
			BODH = word;

			//Bright Object Frames
			word = (ushort)(ReadWord(br));
			n++;
			SegmentInfoGrid[0, n].Value = "BOD Frames";
			SegmentInfoGrid[1, n].Value = word;
			BODF = word;

			//Anode Volts, CMD Value
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			SegmentInfoGrid[0, n].Value = "Anode V (CMD)";
			ANDVOLTS_CMD = (int)((double)(word) * ANDCMDVpDN);
			SegmentInfoGrid[1, n].Value = ANDVOLTS_CMD;

			//MCP Volts, CMD Value
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			SegmentInfoGrid[0, n].Value = "MCP V (CMD)";
			MCPVOLTS_CMD = (int)((double)(word) * MCPCMDVpDN);
			SegmentInfoGrid[1, n].Value = MCPVOLTS_CMD;

			//Photocathode Volts, CMD Value
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			SegmentInfoGrid[0, n].Value = "Photocathode V (CMD)";
			PCVOLTS_CMD = (int)((double)(word) * PCCMDVpDN);
			SegmentInfoGrid[1, n].Value = PCVOLTS_CMD;

			//REA, CPU, HVU voltage and current telemetries:
			br.BaseStream.Position += 5 * 2;

			//REA +5V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAp5V = (double)(word) * REAp5VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "REAp5V (TEL V)";
			SegmentInfoGrid[1, n].Value = REAp5V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//REA +3.3V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAp3p3V = (double)(word) * REAp3p3VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "REA+3.3V (TEL V)";
			SegmentInfoGrid[1, n].Value = REAp3p3V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//REA+12V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAp12V = (double)(word) * REA12VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "REA+12V (TEL V)";
			SegmentInfoGrid[1, n].Value = REAp12V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//REA-12V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAm12V = -(double)(word) * REA12VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "REA-12V (TEL V)";
			SegmentInfoGrid[1, n].Value = REAm12V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//HVU+30V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUp30V = (double)(word) * HVU30VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "HVU+30V (TEL V)";
			SegmentInfoGrid[1, n].Value = HVUp30V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;

			//HVU+15V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUp15V = (double)(word) * HVU15VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "HVU+15V (TEL V)";
			SegmentInfoGrid[1, n].Value = HVUp15V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;

			//HVU-15V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUm15V = -(double)(word) * HVU15VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "HVU-15V (TEL V)";
			SegmentInfoGrid[1, n].Value = HVUm15V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;

			//CPU +12V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			CPUp12V = (double)(word) * CPU12VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "CPU+12V (TEL V)";
			SegmentInfoGrid[1, n].Value = CPUp12V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;

			//CPU -12V
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			CPUm12V = -(double)(word) * CPU12VpDN / 1000;
			SegmentInfoGrid[0, n].Value = "CPU-12V (TEL V)";
			SegmentInfoGrid[1, n].Value = CPUm12V;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;

			//Zero Volt Reference
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			ZEROVREF = (double)(word) * ZEROVREFVpDN / 1000;
			SegmentInfoGrid[0, n].Value = "Zero V Ref. (TEL V)";
			SegmentInfoGrid[1, n].Value = ZEROVREF;

			//REA +5V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAp5VCUR = (double)(word) * REA5VApDN;
			SegmentInfoGrid[0, n].Value = "REA+5V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = REAp5VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//REA +3.3V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAp3p3VCUR = (double)(word) * REA3p3VApDN;
			SegmentInfoGrid[0, n].Value = "REA+3.3V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = REAp3p3VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//REA +12V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAp12VCUR = (double)(word) * REA12VApDN;
			SegmentInfoGrid[0, n].Value = "REA+12V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = REAp12VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//REA -12V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			REAm12VCUR = -(double)(word) * REA12VApDN;
			SegmentInfoGrid[0, n].Value = "REA-12V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = REAm12VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BlueViolet;

			//HVU +30V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUp30VCUR = (double)(word) * HVU30VApDN;
			SegmentInfoGrid[0, n].Value = "HVU+30V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = HVUp30VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;

			//HVU +15V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUp15VCUR = (double)(word) * HVU15VApDN;
			SegmentInfoGrid[0, n].Value = "HVU+15V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = HVUp15VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;

			//HVU -15V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUm15VCUR = -(double)(word) * HVU15VApDN;
			SegmentInfoGrid[0, n].Value = "HVU-15V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = HVUm15VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.BurlyWood;

			//CPU +12V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			CPUp12VCUR = (double)(word) * CPU12VApDM;
			SegmentInfoGrid[0, n].Value = "CPU+12V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = CPUp12VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;

			//CPU -12V Current
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			CPUm12VCUR = -(double)(word) * CPU12VApDM;
			SegmentInfoGrid[0, n].Value = "CPU-12V Cur. (TEL mA)";
			SegmentInfoGrid[1, n].Value = CPUm12VCUR;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;
			SegmentInfoGrid[0, n].Style.BackColor = System.Drawing.Color.Green;

			//Anode Volts, Current Value
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			ANDVOLTS_TEL = (int)((double)(word) * ANDTELVpDN);
			SegmentInfoGrid[0, n].Value = "Anode V (TEL)";
			SegmentInfoGrid[1, n].Value = ANDVOLTS_TEL;

			//MCP Volts, Current Value
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			MCPVOLTS_TEL = (int)((double)(word) * MCPTELVpDN);
			SegmentInfoGrid[0, n].Value = "MCP V (TEL)";
			SegmentInfoGrid[1, n].Value = MCPVOLTS_TEL;

			//ANDVOLTS_TEL += MCPVOLTS_TEL;//anode is wrt to MCP
			//SegmentInfoGrid[1,n-1].Value = ANDVOLTS_TEL;

			//Photocathode Volts, Current Value
			CATVOLTS_TEL = (int)(ReadWord(br) & 0xFFF);
			n++;
			if (CATVOLTS_TEL > 2048)
				CATVOLTS_TEL = Math.Abs(CATVOLTS_TEL - 4096);
			CATVOLTS_TEL = (int)((double)(CATVOLTS_TEL) * CATTELVpDN);
			SegmentInfoGrid[0, n].Value = "Photocathode V (TEL)";
			SegmentInfoGrid[1, n].Value = CATVOLTS_TEL;

			//HVU Current, Current Value (telemetry)
			word = (ushort)(ReadWord(br) & 0xFFF);
			n++;
			if (word > 2048)
				word = (ushort)Math.Abs(word - 4096);
			HVUCURRENT_TEL = (double)(word) * HVUTELApDN;
			SegmentInfoGrid[0, n].Value = "HVU Current uA (TEL)";
			SegmentInfoGrid[1, n].Value = HVUCURRENT_TEL;

			//SegmentInfoGrid.RowCount.set(
			//Total Ramp time
			//RAMPTTOT = Math.Round(((double)(ANDVOLTS)/50.0 + (double)(MCPVOLTS)/10.0 + (double)(PCVOLTS)/-2.0) * RAMPTIME,3);
			RAMPTTOT = Math.Max((double)(ANDVOLTS_CMD) / 50.0, (double)(MCPVOLTS_CMD) / 10.0);
			RAMPTTOT = Math.Max(RAMPTTOT, (double)(PCVOLTS_CMD) / -2.0);
			RAMPTTOT *= RAMPTIME;
			n++;
			SegmentInfoGrid[0, n].Value = "Total Ramp Time";
			SegmentInfoGrid[1, n].Value = RAMPTTOT;

		skipnontelem:

			br.Close();
			fs.Close();
			SegmentInfoGrid.Focus();
		}

		private void SyncImageBtn_Click(object sender, EventArgs e)
		{
			int Nfile = FileListDrop.SelectedIndex;
			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			BinaryReader br = new BinaryReader(fs);
			long Nstartword = (long)StartWordUpD.Value;
			ushort word = 0;
			ushort test = 0;
			ushort chan = 0;

			fs.Seek((Nstartword - 1) * 2, SeekOrigin.Begin);//seek to the current position of the file we're looking at

			//if we are sitting at an image sync already, then want the button to go to the next image for us
			//if we are sitting at an image sync, we want it to move, so increment the seek position up by one word
			//then start the search
			fs.Seek(2, SeekOrigin.Current);

			while (word != 0x1ACF)
			{
				try
				{
					word = (ushort)(ReadWord(br));
					if (word != 0x1ACF)
						continue;//i.e. exit this loop and start over, reading next word (above line)

					recheck:;
					word = (ushort)(ReadWord(br));
					if (word == 0x1ACF)
						goto recheck;//because TWO 1ACF's in a row, one from CRC, one from segment sync, or other possibility
					if (word != 0xFC1D)
						continue;//i.e. exit this loop and start over - found 1ACF but it wasnt followed by FC1D, so not a sync

					//if got to here then found 1ACF followed by FC1D, so this is a segment header but need to determine if it is a "first" segment
					chan = (ushort)(ReadWord(br) & 0x1F);//packet identification
					word = (ushort)(ReadWord(br));//this should be packet sequence control...first 2 bits indicate segment type
					test = (ushort)((word & 0xC000) >> 14);//zero irrelevant bits so logic below can work always, and shift first 2 relevant bits to bottom
					if (test == 1 && (int)chan == ChannelDrop.SelectedIndex + 14)//then this is a "first" segment on the correct channel, we've found what we're looking for
					{
						long Nword = fs.Position / 2;//word (line) number (zero based)
						br.Close();
						fs.Close();
						StartWordUpD.Value = Nword - 3;//back up to first sync word
						ISSYNCHED = true;
						if (ViewSyncImgChck.Checked)
							ViewImageBtn.PerformClick();//view the image - adds it to the list

						break;
					}
				}
				catch (EndOfStreamException)
				{
					MessageBox.Show("Found end of file before finding Image Sync.  Click down on the Segment Scroll to back up.", "Error");
					br.Close();
					fs.Close();
					ISSYNCHED = false;
					return;
				}
			}
		}

		private void SyncToDecBtn_Click(object sender, EventArgs e)
		{

			int Nfile = FileListDrop.SelectedIndex;
			long Nstartword = (long)StartWordUpD.Value;
			int word = -2;
			int val1 = Convert.ToInt32(DecSyncVal1.Value);
			int val2 = Convert.ToInt32(DecSyncVal2.Value);
			if (val1 == -1)
			{
				MessageBox.Show("Invalid Val1 Value.", "Error");
				return;
			}

			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			BinaryReader br = new BinaryReader(fs);
			fs.Seek((Nstartword - 1) * 2, SeekOrigin.Begin);//seek to the current position of the file we're looking at
			while (word != val1)
			{
				try
				{
					word = Convert.ToInt32(ReadWord(br));
					if (word != val1)
						continue;//i.e. exit this loop and start over, reading next word (above line)
					if (word == val1 && val2 == -1)
					{
						long Nword1 = fs.Position / 2;//word (line) number (zero based)
						br.Close();
						fs.Close();
						StartWordUpD.Value = Nword1;//back up to first sync word
						break;
					}
					word = Convert.ToInt32(ReadWord(br));
					if (word != val2)
						continue;//i.e. exit this loop and start over - found val1 but it wasnt followed by val2, so not a sync
								 //if got to here then found val1 followed by val2, so this is synced
					long Nword = fs.Position / 2;//word (line) number (zero based)
					br.Close();
					fs.Close();
					StartWordUpD.Value = Nword - 1;//back up to first sync word
					break;
				}
				catch (EndOfStreamException)
				{
					MessageBox.Show("Found end of file before finding requested decimal value sync sequence.  Please play again!.", "Error");
					br.Close();
					fs.Close();
					return;
				}
			}
		}

		private void SkipNChck_CheckedChanged(object  sender, EventArgs  e)
		{
			if (SkipToChck.Checked)
				SkipToUpD.Enabled = true;
			else
				SkipToUpD.Enabled = false;
		}

		private void ViewImageBtn_Click(object sender, EventArgs e)
		{

			int Nfile = FileListDrop.SelectedIndex;
			long Nstartword = (long)StartWordUpD.Value;
			FileStream fs = new FileStream(FULLFILELIST[Nfile], FileMode.Open);
			BinaryReader br = new BinaryReader(fs);
			//BufferedStream^ bs = new BufferedStream(fs,StartSegmentUpD.Increment*2048);

			br.BaseStream.Position = (long)((Nstartword - 1) * 2);//go to selected word position
																  //set the channel drop to the channel displayed
			ChannelDrop.SelectedIndex = EXTRCN_CHANNEL - 14;

			//write the image
			string fullfile = string.Concat(Form1.CCDLABPATH, IMFRCNT.ToString("0000000"), ".raw");
			bool success = WriteImage(fullfile, br);
			br.Close();
			fs.Close();

			if (success)
			{
				string[] file = new string[] { fullfile };

				Form1 f = (Form1)Owner;
				NIMAGE++;
				JPFITS.REG.SetReg("CCDLAB", "FilterIndex", 2);
				f.AddToImageSet(file, true);
				f.Focus();
			}
			File.Delete(fullfile);
		}

		private bool WriteImage(string fullfilename, BinaryReader br)
		{
			int elN = 0;
			ushort word = 0;
			ushort word1 = 0;
			ushort word2 = 0;
			ushort test = 0;

			//Need to check if we're at a first segment...if not tell the user to sync it
			word1 = ReadWord(br);
			word2 = ReadWord(br);
			if (word1 != 0x1ACF || word2 != 0xFC1D)
			{
				MessageBox.Show(string.Concat("Not currently synced to first segment of an image...please do that by clicking 'Sync to Image'.", br.BaseStream.Position - 4, " ", word1, " ", word2), "Error");
				return false;
			}
			else
			{
				br.BaseStream.Position = br.BaseStream.Position + (1) * 2;
				word = (ushort)(ReadWord(br));
				test = (ushort)((word & 0xC000) >> 14);//zero irrelevant bits so logic below can work always
				if (test != 1)//not equal to a first segment
				{
					MessageBox.Show(string.Concat("Not currently synced to a First Segment of an image...please do that by clicking 'Sync to Image'.", br.BaseStream.Position - 4, " ", word1, " ", word2), "Error");
					return false;
				}
			}
			//if we've gotten to here we are at a first segment of an image, so go ahead

			br.BaseStream.Position = br.BaseStream.Position - (4) * 2;//go back to image sync
			int imsize = (XSIZE + 1) * (YSIZE + 1);
			ushort[] image = new ushort[imsize];//just 1-D is fine cause we're just gonna write it
			int xsize = XSIZE;//zero-based
			int ysize = YSIZE;//zero-based
			if (SubImChck.Checked)
			{
				xsize = SUBRANGE[1] - SUBRANGE[0];//zero-based
				ysize = SUBRANGE[3] - SUBRANGE[2];//zero-based
			}

			br.BaseStream.Seek(1024 * 2, SeekOrigin.Current);//skip first segment of this image entirely - telemetry segment
			if (MODE.Equals("Integration"))
			{
				while (elN < imsize)
				{
					try
					{
						//check for proper channel
						br.BaseStream.Seek(2 * 2, SeekOrigin.Current);//skip synch
						word = (ushort)(ReadWord(br) & 0x1F);//this is the channel; 14 = FUV, 15 = NUV, 16 = VIS
						if (word != EXTRCN_CHANNEL)
						{
							br.BaseStream.Seek(1024 * 2 - 3 * 2, SeekOrigin.Current);//skip rest of segment - it is from another channel
							continue;
						}

						br.BaseStream.Seek(12 * 2, SeekOrigin.Current);//skip rest of continuation segment header
						for (int i = 16; i < 1024; i++)//read up to & including line 1023 of segment
						{
							if (elN >= imsize)
								break;
							word = (ushort)(ReadWord(br));
							image[elN] = word;
							elN++;
						}
						word = (ushort)(ReadWord(br));//just read this to advance past line 1024.
					}
					catch (EndOfStreamException)
					{
						MessageBox.Show("Found end of file before finishing image.  Image data likely divided between 2 files.  No image transferred.", "Error");
						return false;//failed
					}
				}
				ushort[,] d2im = new ushort[xsize + 1, ysize + 1];
				for (int j = 0; j < ysize + 1; j++)
					for (int i = 0; i < xsize + 1; i++)
						d2im[i, j] = image[(j + SUBRANGE[2]) * (XSIZE + 1) + i + SUBRANGE[0]];
				JPFITS.FITSImage fit = new JPFITS.FITSImage(fullfilename, d2im, false, true);
				AddImageInfoKeys(fit);
				fit.WriteImage(TypeCode.UInt16, true);
			}

			else if (MODE.Equals("Centroiding"))
			{
				bool subim = SubImChck.Checked;
				long cur_pos = br.BaseStream.Position;//already skipped first segment
				bool seek = SeekNextImage(br);
				long next_pos = br.BaseStream.Position;
				br.BaseStream.Position = cur_pos;

				xsize = XSIZE;//zero-based
				ysize = YSIZE;//zero-based
				if (subim)
				{
					xsize = SUBRANGE[1] - SUBRANGE[0];//zero-based
					ysize = SUBRANGE[3] - SUBRANGE[2];//zero-based
				}
				ushort dMm = (ushort)dMmUpD.Value;
				int resln = (int)CentroidResolutionUpD.Value;
				uint[,] img = new uint[resln * (xsize + 1), resln * (ysize + 1)];

				int NSegs = (int)((int)(next_pos - cur_pos + 10) / 2048);//already skipped first segment

				byte[] arr = new byte[(int)(next_pos - cur_pos)];
				br.Read(arr, 0, (int)(next_pos - cur_pos));

				for (int j = 0; j < NSegs; j++)
				{
					int SegNumBytes = j * 2048;
					int NHeadBytes = 15 * 2;

					/////////check channel here, continue if wrong channel
					if (arr[j * 2048 + 5] != EXTRCN_CHANNEL)
					{
						continue;
					}

					int nbytes = 2048 - NHeadBytes - 2;
					int nstart = (SegNumBytes + 15 * 2);
					int ncentrds = nbytes / 6;
					for (int i = nstart; i < nstart + ncentrds; i++)
					{
						int cc = nstart + (i - nstart) * 6;
						ushort xword = (ushort)((arr[cc] << 8) | arr[cc + 1]);
						ushort yword = (ushort)((arr[cc + 2] << 8) | arr[cc + 3]);
						ushort sword = (ushort)((arr[cc + 4] << 8) | arr[cc + 5]);
						if (xword == 0 && sword == 0)
							break;
						ushort ixpos = (ushort)(((xword & 0xFF80) >> 7) * 32);
						short fxpos = (short)((xword & 0x7F) >> 1);
						if (fxpos >= 32)
							fxpos = (short)(fxpos - 64);
						ushort iypos = (ushort)(((yword & 0xFF80) >> 7) * 32);
						short fypos = (short)((yword & 0x7F) >> 1);
						if (fypos >= 32)
							fypos = (short)(fypos - 64);

						int mc = ((sword & 0x1FF) >> 1) * 16;
						ushort dmm = (ushort)((sword >> 9) * 16);
						if (dmm > dMm)
							continue;
						int xpos, ypos;
						if (subim)
						{
							if (((int)ixpos + (int)fxpos) < SUBRANGE[0] * 32 || ((int)ixpos + (int)fxpos) >= (SUBRANGE[1] + 1) * 32 || ((int)iypos + (int)fypos) < SUBRANGE[2] * 32 || ((int)iypos + (int)fypos) >= (SUBRANGE[3] + 1) * 32)
								continue;
							xpos = ((int)ixpos + (int)fxpos - SUBRANGE[0] * 32 + 16) * resln / 32;
							ypos = ((int)iypos + (int)fypos - SUBRANGE[2] * 32 + 16) * resln / 32;
						}
						else
						{
							xpos = ((int)ixpos + (int)fxpos - XOFFSET * 32 + 16) * resln / 32;
							ypos = ((int)iypos + (int)fypos - YOFFSET * 32 + 16) * resln / 32;
						}
						img[xpos, ypos]++;

						IMFRCNT = (uint)((arr[SegNumBytes + 12] << 8) | arr[SegNumBytes + 13]);
						IMTIME = (uint)((arr[SegNumBytes + 14] << 24) | (arr[SegNumBytes + 15] << 16) | (arr[SegNumBytes + 16] << 8) | arr[SegNumBytes + 17]);

					}
				}
				JPFITS.FITSImage fit = new JPFITS.FITSImage(fullfilename, img, false, true);
				AddImageInfoKeys(fit);
				fit.WriteImage(TypeCode.UInt16, true);
			}

			return true;//succeeded
		}

		private void ExtractImagesBtn_Click(object sender, EventArgs e)
		{

			FolderBrowserDlg.SelectedPath = (string)JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath");
			if (FolderBrowserDlg.ShowDialog() == DialogResult.Cancel)
				return;

			JPFITS.REG.SetReg("CCDLAB", "OpenFilesPath", FolderBrowserDlg.SelectedPath + "\\");
			JPFITS.REG.SetReg("CCDLAB", "GSEOpenFilesPath", FolderBrowserDlg.SelectedPath);

			System.GC.Collect();
			if (MessageBox.Show("Are you sure you'd like to proceed with image extraction?", "Proceed?", MessageBoxButtons.OKCancel) == DialogResult.OK)
			{
				EXTRCN_CHANNEL = ChannelDrop.SelectedIndex + 14;
				wb = new JPFITS.WaitBar();
				wb.ProgressBar.Maximum = 100;
				wb.Text = "Extraction";
				wb.CancelBtn.Text = "Stop";
				wb.TopMost = true;
				ExtractImgWrkr.RunWorkerAsync();
				wb.ShowDialog();
			}
		}

		private void ExtractImgWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{

			long StartWord = (long)StartWordUpD.Value;
			int Seg_Num = 0;//this param will control everything
			int Seg_Type = 0;
			bool SkipRamp = SkipRampChck.Checked;
			bool StatsOnly = StatsOnlyChck.Checked;
			uint SkipTo = 0;
			if (SkipToChck.Checked)
			{
				SkipTo = (uint)SkipToUpD.Value;//i.e., image number
			}
			int Nfiles = FileListDrop.Items.Count;
			int Every_N = (int)EveryNUpD.Value;
			int Every_N_Count = 0;

			int IMSIZE = (XSIZE + 1) * (YSIZE + 1);
			int xsize = XSIZE;//zero-based
			int ysize = YSIZE;//zero-based
			if (SubImChck.Checked)
			{
				xsize = SUBRANGE[1] - SUBRANGE[0];//zero-based
				ysize = SUBRANGE[3] - SUBRANGE[2];//zero-based
			}
			//byte[] arr = new byte[524288000);
			int arr_length = 0;
			ushort[] image = new ushort[IMSIZE];//just 1-D is fine cause we're just gonna write it
			double[,] d2im = new double[xsize + 1, ysize + 1];
			double[,] fitsdum = new double[1, 1];
			JPFITS.FITSImage fits = new JPFITS.FITSImage("dummy", fitsdum, false, true);
			string fullfile;

			int Pix_Num = 0;//this will need to be reset inside
			string filepath = (string)JPFITS.REG.GetReg("CCDLAB", "OpenFilesPath");

			try
			{
				for (int k = 0; k < Nfiles; k++)
				{
					FileStream fs = new FileStream(FULLFILELIST[k], FileMode.Open);
					wb.TextMsg.Text = "Please Wait, Reading *.img File from Disk...";
					ExtractImgWrkr.ReportProgress(0, k);
					wb.CancelBtn.Enabled = false;
					BufferedStream bs = new BufferedStream(fs);

					if (k == 0 && SkipToSgmtChck.Checked)//skip to viewing position...assists in skipping pre-pended data or 2ndry files, manually done
					{
						fs.Position = ((StartWord - 1) * 2);
						arr_length = (int)fs.Length - (int)fs.Position;
					}
					else//assume file and param info is fine
					{
						arr_length = (int)fs.Length;
					}
					bs.Read(ARR, 0, arr_length);
					bs.Close();
					fs.Close();
					wb.CancelBtn.Enabled = true;

					Seg_Num = -1;//this param will control everything, including your life...

					if (FULLFILELIST[k].Substring(FULLFILELIST[k].Length - 5, 1).Equals("1"))//i.e., should happen when k = 0
					{
						if (SkipRamp)//skip ramp time first...find position of post-ramp image, assume param info correct and synched to image
						{
							uint StartTime = (uint)((ARR[14] << 24) | (ARR[15] << 16) | (ARR[16] << 8) | ARR[17]);
							uint CurTime = StartTime;
							while ((CurTime - StartTime) <= (RAMPTTOT * 1000 + 5000))//add 5 more seconds for good measure
							{
								Seg_Num++;
								if ((Seg_Num + 1) * 2048 > arr_length)
								{
									throw new Exception("Exceeded buffer array length (1).");
								}
								int losynch1 = (ARR[Seg_Num * 2048] << 8) | ARR[Seg_Num * 2048 + 1];
								int losynch2 = (ARR[Seg_Num * 2048 + 2] << 8) | ARR[Seg_Num * 2048 + 3];
								if (losynch1 != 0x1ACF || losynch2 != 0xFC1D)
								{
									MessageBox.Show(string.Concat("Lost Sync...sitting at Seg_Num ", Seg_Num, ". (Section 1)"));
									return;
								}
								CurTime = (uint)((ARR[Seg_Num * 2048 + 14] << 24) | (ARR[Seg_Num * 2048 + 15] << 16) | (ARR[Seg_Num * 2048 + 16] << 8) | ARR[Seg_Num * 2048 + 17]);
							}
							//MessageBox.Show(Seg_Num.ToString(),"Ramp Finsihed at Segment Number (+5 seconds)");
							//MessageBox.Show((CurTime - StartTime - 5000).ToString(),"Computed Ramp Time");
						}
						if (SkipToChck.Checked)//skip to image next
						{
							if (Seg_Num < 0)
								Seg_Num = 0;
							uint CurImage = (uint)((ARR[Seg_Num * 2048 + 12] << 8) | ARR[Seg_Num * 2048 + 13]);
							while (CurImage < SkipTo)
							{
								Seg_Num++;
								if (Seg_Num * 2048 >= arr_length)
								{
									throw new Exception("Exceeded buffer array length (Section 2).");
								}
								int losynch1 = (ARR[Seg_Num * 2048] << 8) | ARR[Seg_Num * 2048 + 1];
								int losynch2 = (ARR[Seg_Num * 2048 + 2] << 8) | ARR[Seg_Num * 2048 + 3];
								if (losynch1 != 0x1ACF || losynch2 != 0xFC1D)
								{
									MessageBox.Show(string.Concat("Lost Sync...sitting at Seg_Num ", Seg_Num, " (zero-based). (Section 3)"));
									return;
								}
								CurImage = (uint)((ARR[Seg_Num * 2048 + 12] << 8) | ARR[Seg_Num * 2048 + 13]);
							}
						}
					}
					//so now the Seg_Num is set, or reset to -1 for a 2ndry file, so, can begin extracting
					//image size params and all that should be set already, so, know how many segments each frame is
					if (Seg_Num < 0)
						Seg_Num = 0;
					int synch1 = (ARR[Seg_Num * 2048] << 8) | ARR[Seg_Num * 2048 + 1];
					int synch2 = (ARR[Seg_Num * 2048 + 2] << 8) | ARR[Seg_Num * 2048 + 3];
					Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) | ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;
					if (synch1 != 0x1ACF || synch2 != 0xFC1D || Seg_Type != 1 && k == 0)
					{
						MessageBox.Show(string.Concat("Not at Image Sync!  Sitting at Seg_Num ", Seg_Num, " (zero-based). (Section 4)"));
						return;
					}

					int prog = 0;
					while ((Seg_Num + 1) * 2048 < arr_length)
					{
						/////////check channel here, Seg_Num++ and continue if wrong channel
						if ((int)(ARR[Seg_Num * 2048 + 5]) != EXTRCN_CHANNEL)
						{
							Seg_Num++;
							continue;
						}

						Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) | ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;
						if (Seg_Type == 1)//first segment of image
						{
							Every_N_Count++;
							if (Every_N_Count < Every_N)
							{
								Seg_Num++;
								continue;
							}
							else
							{
								Every_N_Count = 0;//reset
							}
							IMTIME = (uint)((ARR[Seg_Num * 2048 + 14] << 24) | (ARR[Seg_Num * 2048 + 15] << 16) | (ARR[Seg_Num * 2048 + 16] << 8) | ARR[Seg_Num * 2048 + 17]);
							IMFRCNT = (uint)((ARR[Seg_Num * 2048 + 12] << 8) | ARR[Seg_Num * 2048 + 13]);
							UpDateTELVolts(ARR, Seg_Num);

							Seg_Num++; //to skip first segment telem
							Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) | ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;

							Pix_Num = 0;//reset pixel number

							string imgsess;
							try
							{
								//s_0404_i_0145_q_0001
								int ijk = FILELIST[0].LastIndexOf("q");
								imgsess = FILELIST[0].Substring(ijk - 5, 4);
							}
							catch
							{
								int ijk = FILELIST[0].LastIndexOf(".");
								imgsess = FILELIST[0].Substring(0, ijk);
							}

							string channn = "";
							if (EXTRCN_CHANNEL == 14)
								channn = "FUV";
							if (EXTRCN_CHANNEL == 15)
								channn = "NUV";
							if (EXTRCN_CHANNEL == 16)
								channn = "VIS";
							//write image with segment number as file name
							//fullfile = filepath + channn + "_" + imgsess + "_" + (Seg_Num + k*256000).ToString("0000000000000") + ".fits";
							fullfile = filepath + channn + "_" + imgsess + "_" + IMTIME.ToString("0000000000000") + ".fits";
							//write image with frame number as file name
							//fullfile = string.Concat(filepath,IMFRCNT.ToString("0000000"),"_",channn,".fits");
							fits.FullFileName = fullfile;
							fits.SetImage(fitsdum, false, true);
							fits.Header.RemoveAllKeys(fitsdum);
							AddImageInfoKeys(fits);
						}
						if (Every_N_Count != 0)
						{
							Seg_Num++;
							continue;
						}

						bool imageDone = false;
						while (Seg_Type != 1 && (Seg_Num + 1) * 2048 < arr_length && (int)(ARR[Seg_Num * 2048 + 5]) == EXTRCN_CHANNEL)//not the last segment of the whole file
						{
							for (int i = 15; i < 1023; i++)
							{
								if (Pix_Num >= IMSIZE)//image is done
								{
									imageDone = true;
									break;
								}
								image[Pix_Num] = (ushort)((ARR[Seg_Num * 2048 + i * 2] << 8) | ARR[Seg_Num * 2048 + i * 2 + 1]);
								Pix_Num++;//0 based
							}
							Seg_Num++;
							Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) | ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;
						}
						if (imageDone)//make d2im and save...
						{
							for (int j = 0; j < ysize + 1; j++)
								for (int i = 0; i < xsize + 1; i++)
									d2im[i, j] = (double)(image[(j + SUBRANGE[2]) * (XSIZE + 1) + i + SUBRANGE[0]]);
							fits.SetImage(d2im, StatsOnly, true);
							if (StatsOnly)
							{
								fits.Header.AddKey("MIN", fits.Min.ToString(), "For Quick Extraction Only", -1);
								fits.Header.AddKey("MAX", fits.Max.ToString(), "For Quick Extraction Only", -1);
								fits.Header.AddKey("MEAN", fits.Mean.ToString(), "For Quick Extraction Only", -1);
								fits.Header.AddKey("MEDIAN", fits.Median.ToString(), "For Quick Extraction Only", -1);
								fits.Header.AddKey("STDV", fits.Std.ToString(), "For Quick Extraction Only", -1);
								fits.Header.AddKey("SUM", fits.Sum.ToString(), "For Quick Extraction Only", -1);
								fits.SetImage(fitsdum, false, true);//don't record the actual image in this mode (time saver)
							}

							fits.WriteImage(TypeCode.UInt16, true);
						}


						//PBar. do progress bar accounting and check for cancel
						double dprog = ((double)((Seg_Num + 1) * 2048) / (double)(arr_length)) * 100;
						if (dprog - (double)(prog) >= 1)
						{
							prog++;
							ExtractImgWrkr.ReportProgress(prog, k);
						}
						if (wb.DialogResult == DialogResult.Cancel)
						{
							return;
						}//done PBar.
					}
				}
			}
			catch (Exception ee)
			{
				MessageBox.Show(string.Concat(ee.StackTrace, "   ", StartWord, "   ", Seg_Type, "   ", Seg_Num, "   ", Pix_Num), ee.Message);
			}
		}

		private void ExtractImgWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{

			int intprog = e.ProgressPercentage;
			int k = (int)e.UserState;
			wb.ProgressBar.Value = intprog;
			wb.TextMsg.Text = string.Concat("Completed: ", intprog.ToString(), "%");
			wb.Text = string.Concat("File ", k + 1, " of ", FULLFILELIST.Length, ": ", intprog.ToString(), "%");
		}

		private void ExtractImgWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (wb.DialogResult == DialogResult.Cancel)
				MessageBox.Show("Cancelled extracting images.  Images were written until this time");
			else
				MessageBox.Show("Finsihed extracting images...");
			wb.Close();
		}

		public uint GetImageTime(BinaryReader br)//this assumes you're synced
		{

			long orpos = br.BaseStream.Position;
			br.BaseStream.Position = br.BaseStream.Position + (7) * 2;
			ushort msw16 = ReadWord(br);
			ushort lsw16 = ReadWord(br);
			uint msw32 = (uint)msw16;
			msw32 = (msw32 << 16) | (uint)lsw16;
			IMTIME = (uint)msw32;
			br.BaseStream.Position = orpos;
			return IMTIME;
		}

		public uint GetImageCount(BinaryReader br)//this assumes you're synced
		{

			long orpos = br.BaseStream.Position;
			br.BaseStream.Position = br.BaseStream.Position + (6) * 2;
			IMFRCNT = (uint)ReadWord(br);
			br.BaseStream.Position = orpos;
			return IMFRCNT;
		}

		private bool SeekNextImage(BinaryReader br)
		{

			ushort word = 0;
			ushort test = 0;
			ushort chan = 0;

			while (word != 0x1ACF)
			{
				try
				{
					word = (ushort)(ReadWord(br));
					if (word != 0x1ACF)
						continue;//i.e. exit this loop and start over, reading next word (above line)
					if (((byte)(br.PeekChar()) - 1) != 0xFC)
						continue;//i.e. exit loop and start over - this check is so that CRC of '1ACF' doesn't cause the whole segment to be skipped
								 //note.NotifyTxt.Text = string.Concat(word,(unsigned __int8(br.PeekChar())-1).ToString());
								 //note.ShowDialog();
					word = (ushort)(ReadWord(br));
					if (word != 0xFC1D)
						continue;//i.e. exit this loop and start over - found 1ACF but it wasnt followed by FC1D, so not a sync
								 //if got to here then found 1ACF followed by FC1D, so this is a segment header but need to determine if it is a "first" segment
					chan = (ushort)(ReadWord(br) & 0x1F);//packet identification
					word = (ushort)(ReadWord(br));//this should be packet sequence control...first 2 bits indicate segment type
					test = (ushort)((word & 0xC000) >> 14);//zero irrelevant bits so logic below can work always, and shift first 2 relevant bits to bottom
					if (test == 1 && (int)chan == ChannelDrop.SelectedIndex + 14)//then this is a "first" segment on the correct channel, we've found what we're looking for
					{
						br.BaseStream.Position = br.BaseStream.Position - 8;//back up to sync word
						break;
					}
				}
				catch (EndOfStreamException)
				{
					MessageBox.Show("Found end of file before finding Image Sync.", "Error");
					return false;
				}
			}
			return true;
		}

		private void ExtractCentroidsBtn_Click(object sender, EventArgs e)
		{
			System.GC.Collect();
			GC.WaitForFullGCComplete();
			GC.WaitForPendingFinalizers();

			EXTRCN_CHANNEL = ChannelDrop.SelectedIndex + 14;
			int resln = (int)CentroidResolutionUpD.Value;
			int xsize = XSIZE;//zero-based
			int ysize = YSIZE;//zero-based
			if (SubImChck.Checked)
			{
				xsize = SUBRANGE[1] - SUBRANGE[0];//zero-based
				ysize = SUBRANGE[3] - SUBRANGE[2];//zero-based
			}
			DialogResult ans = MessageBox.Show(string.Concat("Image will be ", Math.Round((double)((xsize + 1) * (ysize + 1)) * (double)(resln * resln) * 4.0 / 1024.0 / 1024.0, 6), " MB at UInt32 Bit Precision.  Do You Wish to Continue?"), "File Size Warning...", MessageBoxButtons.YesNo);
			if (ans == DialogResult.No)
				return;

			wb = new JPFITS.WaitBar();
			wb.ProgressBar.Maximum = 100;
			ExtractCtrdWrkr.RunWorkerAsync();
			wb.ShowDialog();
		}

		private void ExtractCtrdWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			try
			{
				long StartWord = (long)StartWordUpD.Value;
				int Seg_Num = 0;//this param will control everything
				int Seg_Type = 0;
				bool SkipRamp = SkipRampChck.Checked;
				uint SkipTo = 0;
				if (SkipToChck.Checked)
				{
					SkipTo = (uint)SkipToUpD.Value;//i.e., image number
				}
				int Nfiles = FileListDrop.Items.Count;
				int Every_N = (int)EveryNUpD.Value;
				int Every_N_Count = 0;

				int resln = (int)CentroidResolutionUpD.Value;
				int dMm = (int)dMmUpD.Value;
				//bool first = true;
				bool subim = SubImChck.Checked;
				int xsize = XSIZE;//zero-based
				int ysize = YSIZE;//zero-based
				if (subim)
				{
					xsize = SUBRANGE[1] - SUBRANGE[0];//zero-based
					ysize = SUBRANGE[3] - SUBRANGE[2];//zero-based
				}
				uint[,] img = new uint[resln * (xsize + 1), resln * (ysize + 1)];
				double[,] darkimg = new double[(xsize + 1), (ysize + 1)];
				double[,] dMmimg = new double[(xsize + 1), (ysize + 1)];
				double[,] darkimgcounter = new double[(xsize + 1), (ysize + 1)];
				IMTIME = 0;//reset it
				//uint imtime = 0;//IMTIME change tracker
				//bool newim = false;

				//for making fits photometry list of number of events in each frame (number of events, time)
				int fr_phot = 0;
				int fr_count = 0;
				uint[,] phot_buffer = new uint[8388608, 2];//allows for 8,388,608 frames, 64MB memory usage, 3.88hours imaging at 600Hz.

				//parity
				bool extparity = ExtParityChck.Checked;
				int parity_events = 0;
				int NumParityEvents = 786432;
				FileStream parity_fs = null;
				MemoryStream parity_ms = null;
				byte[] parity_temp = null;
				if (extparity)
				{
					parity_fs = new FileStream(Form1.CCDLABPATH + "templeton_parity.tmp", FileMode.Create);
					parity_ms = new MemoryStream(NumParityEvents * 16);//12MB = 786,432 parity errors, expected to be small number
					parity_temp = new byte[16];//[UInt32_EventNumber_1based , UInt32_DataType (1,2 or 3 = xword,yword or cornerword) , UInt32_FileWordNumber_1based , UInt32_DataValue]
				}

				//for making fits list of all centroids
				bool makefitslist = ExtractListChck.Checked;
				bool distortioncorrectlist = GSEApplyDistortionCorrectionChck.Checked;
				bool FPNcorrectlist = GSEApplyFPNCorrectionChck.Checked;
				int buff_events = 0;
				int tot_events = 0;
				FileStream centlist_fs_ixy = null;
				FileStream centlist_fs_fxy = null;
				FileStream centlist_fs_mxy = null;
				MemoryStream centlist_ms_ixy = null;
				MemoryStream centlist_ms_fxy = null;
				MemoryStream centlist_ms_mxy = null;
				byte[] centlist_temp_ixy = null;
				byte[] centlist_temp_fxy = null;
				byte[] centlist_temp_mxy = null;
				FileStream timelist_fs = null;
				MemoryStream timelist_ms = null;
				byte[] timelist_temp = null;
				FileStream framelist_fs = null;
				MemoryStream framelist_ms = null;
				byte[] framelist_temp = null;
				int NumBuffEvents = 8388608;

				if (makefitslist)
				{
					centlist_fs_ixy = new FileStream(Form1.CCDLABPATH + "templeton_cent_ixy.tmp", FileMode.Create);
					centlist_fs_fxy = new FileStream(Form1.CCDLABPATH + "templeton_cent_fxy.tmp", FileMode.Create);
					centlist_fs_mxy = new FileStream(Form1.CCDLABPATH + "templeton_cent_mxy.tmp", FileMode.Create);
					centlist_ms_ixy = new MemoryStream(NumBuffEvents * 2);//16MB
					centlist_ms_fxy = new MemoryStream(NumBuffEvents * 1);//8MB
					centlist_ms_mxy = new MemoryStream(NumBuffEvents * 2);//16MB
					centlist_temp_ixy = new byte[4];//uint16 ints: xint,yint,xint,yint...
					centlist_temp_fxy = new byte[2];//uint8 fracs: xfrac,yfrac,xfrac,yfrac...
					centlist_temp_mxy = new byte[4];//uint16 corners: ...

					timelist_fs = new FileStream(Form1.CCDLABPATH + "templeton_time.tmp", FileMode.Create);
					timelist_ms = new MemoryStream(NumBuffEvents * 2);//16MB
					timelist_temp = new byte[4];//uint32 times

					framelist_fs = new FileStream(Form1.CCDLABPATH + "templeton_frame.tmp", FileMode.Create);
					framelist_ms = new MemoryStream(NumBuffEvents * 2);//16MB
					framelist_temp = new byte[4];//uint32 times
				}

				string CPUXDistFile = "";
				string CPUYDistFile = "";
				JPFITS.FITSImage CPUXDistFits = new JPFITS.FITSImage("c:\\test", false);
				JPFITS.FITSImage CPUYDistFits = new JPFITS.FITSImage("c:\\test", false);
				if (distortioncorrectlist)
				{
					if (EXTRCN_CHANNEL == 14)
					{
						if (File.Exists("C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits"))
						{
							CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits";
							CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dY.fits";
						}
					}
					else if (EXTRCN_CHANNEL == 15)
					{
						if (File.Exists("C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits"))
						{
							CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits";
							CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dY.fits";
						}
					}
					else if (EXTRCN_CHANNEL == 16)
					{
						if (File.Exists("C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits"))
						{
							CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits";
							CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dY.fits";
						}
					}
					else
					{
						OpenFileDialog dlg = new OpenFileDialog();
						dlg.Filter = "FITS (*.fits)|*.fits";
						dlg.Multiselect = false;
						//get the CPU *X* correction image
						dlg.Title = "Select CPU *X* Correction FITS Image File";
						if (dlg.ShowDialog() != DialogResult.OK)
							return;
						CPUXDistFile = dlg.FileName;

						//get the CPU *Y* correction image
						dlg.Title = "Select CPU *Y* Correction FITS Image File";
						if (dlg.ShowDialog() != DialogResult.OK)
							return;
						CPUYDistFile = dlg.FileName;
					}
					CPUXDistFits = new JPFITS.FITSImage(CPUXDistFile, null, true, true, false, true);
					CPUYDistFits = new JPFITS.FITSImage(CPUYDistFile, null, true, true, false, true);
				}

				string FPNFile = "";
				JPFITS.FITSImage FPNFits = new JPFITS.FITSImage("c:\\test", false);
				if (FPNcorrectlist)
				{
					if (EXTRCN_CHANNEL == 14)
					{
						if (ALGRTHM == "3x3 Square")
						{
							if (File.Exists("C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits"))
								FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits";
						}
						if (ALGRTHM == "5x5 Square")
						{
							if (File.Exists("C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits"))
								FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits";
						}
					}
					else if (EXTRCN_CHANNEL == 15)
					{
						if (ALGRTHM == "3x3 Square")
						{
							if (File.Exists("C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits"))
								FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits";
						}
						if (ALGRTHM == "5x5 Square")
						{
							if (File.Exists("C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits"))
								FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits";
						}
					}
					else if (EXTRCN_CHANNEL == 16)
					{
						if (ALGRTHM == "3x3 Square")
						{
							if (File.Exists("C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits"))
								FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits";
						}
						if (ALGRTHM == "5x5 Square")
						{
							if (File.Exists("C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits"))
								FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits";
						}
					}
					else
					{
						//get the FPN correction table
						OpenFileDialog dlg = new OpenFileDialog();
						dlg.Filter = "FITS (*.fits)|*.fits";
						dlg.Multiselect = false;
						dlg.Title = "Select FPN Correction FITS Image File";
						if (dlg.ShowDialog() != DialogResult.OK)
							return;
						FPNFile = dlg.FileName;
					}
					FPNFits = new JPFITS.FITSImage(FPNFile, null, true, true, false, true);
				}
				Random rand = new Random();

				bool firstframe = true;
				uint firstframetime = 0;
				uint lastframetime = 0;
				uint firstframenum = 0;
				uint lastframenum = 0;

				GC.Collect();
				GC.WaitForFullGCApproach();
				GC.WaitForFullGCComplete();
				GC.WaitForPendingFinalizers();
				//array for reading in .img files Byte-wise (each up to 512MB)
				//byte[] arr = new byte[1024*1024*512);
				try
				{
					for (int k = 0; k < Nfiles; k++)
					{
						FileStream fs = new FileStream(FULLFILELIST[k], FileMode.Open);
						ExtractCtrdWrkr.ReportProgress(-1, "Please wait while I read the *.img file from disk...");
						ExtractCtrdWrkr.ReportProgress(-2);//cancel button disabled
						BufferedStream bs = new BufferedStream(fs, 1024 * 1024 * 32);

						int img_length;
						if (k == 0 && SkipToSgmtChck.Checked)//skip to viewing position...assists in skipping pre-pended data or 2ndry files, manually done
						{
							fs.Position = ((StartWord - 1) * 2);
							img_length = (int)fs.Length - (int)fs.Position;
						}
						else//assume file and param info is fine
						{
							img_length = (int)fs.Length;
						}
						bs.Read(ARR, 0, img_length);
						bs.Close();
						fs.Close();
						ExtractCtrdWrkr.ReportProgress(-3);//cancel button enabled

						Seg_Num = -1;//this param will control everything, including your life...it controls where in the array "arr" you are looking

						if (FULLFILELIST[k].Substring(FULLFILELIST[k].Length - 5, 1).Equals("1"))//i.e., should happen when k = 0
						{
							if (SkipRamp)//skip ramp time first...find position of post-ramp image, assume param info correct and synched to image
							{
								uint StartTime = (uint)((ARR[14] << 24) | (ARR[15] << 16) | (ARR[16] << 8) | ARR[17]);
								uint CurTime = StartTime;
								while ((CurTime - StartTime) <= (RAMPTTOT * 1000 + 5000))//add 5 more seconds for good measure
								{
									Seg_Num++;
									if ((Seg_Num + 1) * 2048 > img_length)
									{
										throw new Exception("Exceeded buffer array length (1).");
									}
									int losynch1 = (ARR[Seg_Num * 2048] << 8) | ARR[Seg_Num * 2048 + 1];
									int losynch2 = (ARR[Seg_Num * 2048 + 2] << 8) | ARR[Seg_Num * 2048 + 3];
									if (losynch1 != 0x1ACF || losynch2 != 0xFC1D)
									{
										MessageBox.Show(string.Concat("Lost Sync...sitting at Seg_Num ", Seg_Num, ". (Section 1)"));
										return;
									}
									CurTime = (uint)((ARR[Seg_Num * 2048 + 14] << 24) | (ARR[Seg_Num * 2048 + 15] << 16) | (ARR[Seg_Num * 2048 + 16] << 8) | ARR[Seg_Num * 2048 + 17]);
								}
								//MessageBox.Show(Seg_Num.ToString(),"Ramp Finsihed at Segment Number (+5 seconds)");
								//MessageBox.Show((CurTime - StartTime - 5000).ToString(),"Computed Ramp Time");
							}
							if (SkipToChck.Checked)//skip N images next
							{
								if (Seg_Num < 0)
									Seg_Num = 0;
								uint StartImage = (uint)((ARR[Seg_Num * 2048 + 12] << 8) + ARR[Seg_Num * 2048 + 13]);
								uint CurImage = StartImage;
								while (CurImage < SkipTo)
								{
									Seg_Num++;
									if (Seg_Num * 2048 >= img_length)
									{
										throw new Exception("Exceeded buffer array length (Section 2).");
									}
									int losynch1 = (ARR[Seg_Num * 2048] << 8) + ARR[Seg_Num * 2048 + 1];
									int losynch2 = (ARR[Seg_Num * 2048 + 2] << 8) + ARR[Seg_Num * 2048 + 3];
									if (losynch1 != 0x1ACF || losynch2 != 0xFC1D)
									{
										MessageBox.Show(string.Concat("Lost Sync...sitting at Seg_Num ", Seg_Num, ". (Section 3)"));
										return;
									}
									CurImage = (uint)((ARR[Seg_Num * 2048 + 12] << 8) + ARR[Seg_Num * 2048 + 13]);
								}
							}
						}
						//so now the Seg_Num is set, or reset to -1 for a 2ndry file, so, can begin extracting
						//image size params and all that should be set already, so, know how many segments each frame is

						if (Seg_Num < 0)
							Seg_Num = 0;
						int synch1 = (ARR[Seg_Num * 2048] << 8) + ARR[Seg_Num * 2048 + 1];
						int synch2 = (ARR[Seg_Num * 2048 + 2] << 8) + ARR[Seg_Num * 2048 + 3];
						Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) + ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;
						if (synch1 != 0x1ACF || synch2 != 0xFC1D || Seg_Type != 1 && k == 0)
						{
							MessageBox.Show(string.Concat("Not at Image Sync!  Sitting at Seg_Num ", Seg_Num, ". (Section 4)"));
							return;
						}

						int prog = 0;
						while ((Seg_Num + 1) * 2048 < img_length)
						{
							/////////check channel here, Seg_Num++ and continue if wrong channel
							if (ARR[Seg_Num * 2048 + 5] != EXTRCN_CHANNEL)
							{
								Seg_Num++;
								continue;
							}

							Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) + ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;
							if (Seg_Type == 1)//first segment of image
							{
								Every_N_Count++;
								if (Every_N_Count < Every_N)
								{
									Seg_Num++;
									continue;
								}
								else
								{
									Every_N_Count = 0;//reset
								}
								IMTIME = (uint)((ARR[Seg_Num * 2048 + 14] << 24) | (ARR[Seg_Num * 2048 + 15] << 16) | (ARR[Seg_Num * 2048 + 16] << 8) | ARR[Seg_Num * 2048 + 17]);
								IMFRCNT = (uint)((ARR[Seg_Num * 2048 + 12] << 8) | ARR[Seg_Num * 2048 + 13]);
								UpDateTELVolts(ARR, Seg_Num);

								Seg_Num++; //to skip first segment telem
								Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) + ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;

								if (firstframe)
								{
									firstframetime = IMTIME;
									firstframenum = /*IMFRCNT*/ 1;
									firstframe = false;
								}
								lastframetime = IMTIME;
								lastframenum = /*IMFRCNT*/ lastframenum + 1;
							}
							if (Every_N_Count != 0)
							{
								Seg_Num++;
								continue;
							}

							while (Seg_Type != 1 && (Seg_Num + 1) * 2048 <= img_length && (int)(ARR[Seg_Num * 2048 + 5]) == EXTRCN_CHANNEL)//not the last segment of the whole file
							{
								for (int i = 15; i < 1023; i += 3)
								{
									int cc = Seg_Num * 2048;
									ushort xword = (ushort)((ARR[cc + i * 2] << 8) | ARR[cc + i * 2 + 1]);
									ushort yword = (ushort)((ARR[cc + i * 2 + 2] << 8) | ARR[cc + i * 2 + 3]);
									ushort sword = (ushort)((ARR[cc + i * 2 + 4] << 8) | ARR[cc + i * 2 + 5]);

									if (xword == 0 && yword == 0 && sword == 0)
										break;

									ushort ixpos = (ushort)(((xword) >> 7) * 32);

									short fxpos = (short)((xword & 0x7F) >> 1);
									if (fxpos >= 32)
										fxpos = (short)(fxpos - 64);

									ushort iypos = (ushort)(((yword) >> 7) * 32);

									short fypos = (short)((yword & 0x7F) >> 1);
									if (fypos >= 32)
										fypos = (short)(fypos - 64);

									short mc = (short)(((sword & 0x1FF) >> 1) * 16);
									short dmm = (short)((sword >> 9) * 16);
									if (dmm > dMm)
										continue;

									int xcorr, ycorr;
									if (distortioncorrectlist)
									{
										xcorr = (int)(32 * CPUXDistFits[ixpos / 32, iypos / 32]);
										ycorr = (int)(32 * CPUYDistFits[ixpos / 32, iypos / 32]);

										ixpos -= (ushort)xcorr;
										iypos -= (ushort)ycorr;
									}

									if (FPNcorrectlist)
									{
										if (fxpos < -16)//X
										{
											ixpos -= 32;//adjust integer
											fxpos += 32;//adjust fractional
										}
										if (fypos < -16)//Y
										{
											iypos -= 32;//adjust integer
											fypos += 32;//adjust fractional
										}
										if (fxpos > 15)//X
										{
											ixpos += 32;//adjust integer
											fxpos -= 32;//adjust fractional
										}
										if (fypos > 15)//Y
										{
											iypos += 32;//adjust integer
											fypos -= 32;//adjust fractional
										}

										fxpos += 16;
										fypos += 16;

										double fx = (double)(fxpos);
										double fy = (double)(fypos);

										fx += rand.NextDouble();
										fy += rand.NextDouble();

										fx *= FPNFits[1, (int)(fx * 4096 / 32)];
										fy *= FPNFits[2, (int)(fy * 4096 / 32)];

										fxpos = (short)fx;
										fypos = (short)fy;

										fxpos -= 16;//x
										fypos -= 16;//y
									}


									int xpos, ypos;
									if (subim)
									{
										//MessageBox.Show(   ((int)ixpos + (int)fxpos + 16).ToString()   ,    ((SubRange[1]+1 + XOFFSET)*32).ToString()   );
										if (((int)ixpos + (int)fxpos + 16) < (SUBRANGE[0] + XOFFSET) * 32 || ((int)ixpos + (int)fxpos + 16) >= (SUBRANGE[1] + 1 + XOFFSET) * 32 || ((int)iypos + (int)fypos + 16) < (SUBRANGE[2] + YOFFSET) * 32 || ((int)iypos + (int)fypos + 16) >= (SUBRANGE[3] + 1 + YOFFSET) * 32)
											continue;
										//MessageBox.Show("test","test");
										xpos = ((int)ixpos + (int)fxpos - SUBRANGE[0] * 32 - XOFFSET * 32 + 16) * resln / 32;
										ypos = ((int)iypos + (int)fypos - SUBRANGE[2] * 32 - YOFFSET * 32 + 16) * resln / 32;
									}
									else
									{
										xpos = ((int)ixpos + (int)fxpos - XOFFSET * 32 + 16) * resln / 32;
										ypos = ((int)iypos + (int)fypos - YOFFSET * 32 + 16) * resln / 32;
									}
									try
									{
										//MessageBox.Show(xpos.ToString(),xpos.ToString());
										img[xpos, ypos]++;
										darkimg[xpos / resln, ypos / resln] += mc;
										dMmimg[xpos / resln, ypos / resln] += dmm;
										darkimgcounter[xpos / resln, ypos / resln]++;
									}
									catch
									{   //ZULU ZULU ZULU ZULU ZULU ZULU ZULU ZULU ZULU ZULU ZULU
										/*MessageBox.Show(string.Concat(e.StackTrace,"/r","Centroid possibly out of bounds (Code Section Zulu)"),e.Message);
										MessageBox.Show(xcorr.ToString() + "	" + ycorr.ToString());
										MessageBox.Show(ixpos.ToString() + "	" + iypos.ToString());
										MessageBox.Show(xpos.ToString() + "	" + ypos.ToString());*/


										//arr = new byte[1);//try to prevent out of memory error
										//GC.ReRegisterForFinalize(arr);
										/*GC.Collect();
										GC.WaitForFullGCApproach();
										GC.WaitForFullGCComplete();
										GC.WaitForPendingFinalizers();*/
									}

									//parity check
									//[UInt32_EventNumber_1based , UInt32_DataType (1,2 or 3 = xword,yword or cornerword) , UInt32_FileWordNumber_1based]
									if (extparity)
									{
										if (Check_Even_Parity_Flag(xword))
										{
											if (parity_events >= NumParityEvents)
											{
												ExtractCtrdWrkr.ReportProgress(-1, "Please wait a moment while I write Parity Event List buffers to disk...");
												parity_ms.WriteTo(parity_fs);
												parity_ms.Position = 0;
												parity_events = 0;
											}
											parity_temp[0] = (byte)(((tot_events + 1 - 2147483648) >> 24) & 0xFF);//tot_events+1 = event number 1 based
											parity_temp[1] = (byte)(((tot_events + 1 - 2147483648) >> 16) & 0xFF);
											parity_temp[2] = (byte)(((tot_events + 1 - 2147483648) >> 8) & 0xFF);
											parity_temp[3] = (byte)((tot_events + 1 - 2147483648) & 0xFF);
											parity_temp[4] = unchecked((byte)((((int)1 - 2147483648) >> 24) & 0xFF));
											parity_temp[5] = unchecked((byte)((((int)1 - 2147483648) >> 16) & 0xFF));
											parity_temp[6] = unchecked((byte)((((int)1 - 2147483648) >> 8) & 0xFF));
											parity_temp[7] = unchecked((byte)(((int)1 - 2147483648) & 0xFF));
											parity_temp[8] = (byte)((((int)((cc + i * 2) / 2 + 1) - 2147483648) >> 24) & 0xFF);
											parity_temp[9] = (byte)((((int)((cc + i * 2) / 2 + 1) - 2147483648) >> 16) & 0xFF);
											parity_temp[10] = (byte)((((int)((cc + i * 2) / 2 + 1) - 2147483648) >> 8) & 0xFF);
											parity_temp[11] = (byte)(((int)((cc + i * 2) / 2 + 1) - 2147483648) & 0xFF);
											parity_temp[12] = (byte)((((int)xword - 2147483648) >> 24) & 0xFF);
											parity_temp[13] = (byte)((((int)xword - 2147483648) >> 16) & 0xFF);
											parity_temp[14] = (byte)((((int)xword - 2147483648) >> 8) & 0xFF);
											parity_temp[15] = (byte)(((int)xword - 2147483648) & 0xFF);
											parity_ms.Write(parity_temp, 0, 16);
											parity_events++;
										}
										if (Check_Even_Parity_Flag(yword))
										{
											if (parity_events >= NumParityEvents)
											{
												ExtractCtrdWrkr.ReportProgress(-1, "Please wait a moment while I write Parity Event List buffers to disk...");
												parity_ms.WriteTo(parity_fs);
												parity_ms.Position = 0;
												parity_events = 0;
											}
											parity_temp[0] = (byte)(((tot_events + 1 - 2147483648) >> 24) & 0xFF);//tot_events+1 = event number 1 based
											parity_temp[1] = (byte)(((tot_events + 1 - 2147483648) >> 16) & 0xFF);
											parity_temp[2] = (byte)(((tot_events + 1 - 2147483648) >> 8) & 0xFF);
											parity_temp[3] = (byte)((tot_events + 1 - 2147483648) & 0xFF);
											parity_temp[4] = unchecked((byte)((((int)2 - 2147483648) >> 24) & 0xFF));
											parity_temp[5] = unchecked((byte)((((int)2 - 2147483648) >> 16) & 0xFF));
											parity_temp[6] = unchecked((byte)((((int)2 - 2147483648) >> 8) & 0xFF));
											parity_temp[7] = unchecked((byte)(((int)2 - 2147483648) & 0xFF));
											parity_temp[8] = (byte)((((int)((cc + i * 2 + 2) / 2 + 1) - 2147483648) >> 24) & 0xFF);
											parity_temp[9] = (byte)((((int)((cc + i * 2 + 2) / 2 + 1) - 2147483648) >> 16) & 0xFF);
											parity_temp[10] = (byte)((((int)((cc + i * 2 + 2) / 2 + 1) - 2147483648) >> 8) & 0xFF);
											parity_temp[11] = (byte)(((int)((cc + i * 2 + 2) / 2 + 1) - 2147483648) & 0xFF);
											parity_temp[12] = (byte)((((int)yword - 2147483648) >> 24) & 0xFF);
											parity_temp[13] = (byte)((((int)yword - 2147483648) >> 16) & 0xFF);
											parity_temp[14] = (byte)((((int)yword - 2147483648) >> 8) & 0xFF);
											parity_temp[15] = (byte)(((int)yword - 2147483648) & 0xFF);
											parity_ms.Write(parity_temp, 0, 16);
											parity_events++;
										}
										if (Check_Even_Parity_Flag(sword))
										{
											if (parity_events >= NumParityEvents)
											{
												ExtractCtrdWrkr.ReportProgress(-1, "Please wait a moment while I write Parity Event List buffers to disk...");
												parity_ms.WriteTo(parity_fs);
												parity_ms.Position = 0;
												parity_events = 0;
											}
											parity_temp[0] = (byte)(((tot_events + 1 - 2147483648) >> 24) & 0xFF);//tot_events+1 = event number 1 based
											parity_temp[1] = (byte)(((tot_events + 1 - 2147483648) >> 16) & 0xFF);
											parity_temp[2] = (byte)(((tot_events + 1 - 2147483648) >> 8) & 0xFF);
											parity_temp[3] = (byte)((tot_events + 1 - 2147483648) & 0xFF);
											parity_temp[4] = unchecked((byte)((((int)3 - 2147483648) >> 24) & 0xFF));
											parity_temp[5] = unchecked((byte)((((int)3 - 2147483648) >> 16) & 0xFF));
											parity_temp[6] = unchecked((byte)((((int)3 - 2147483648) >> 8) & 0xFF));
											parity_temp[7] = unchecked((byte)(((int)3 - 2147483648) & 0xFF));
											parity_temp[8] = (byte)((((int)((cc + i * 2 + 4) / 2 + 1) - 2147483648) >> 24) & 0xFF);
											parity_temp[9] = (byte)((((int)((cc + i * 2 + 4) / 2 + 1) - 2147483648) >> 16) & 0xFF);
											parity_temp[10] = (byte)((((int)((cc + i * 2 + 4) / 2 + 1) - 2147483648) >> 8) & 0xFF);
											parity_temp[11] = (byte)(((int)((cc + i * 2 + 4) / 2 + 1) - 2147483648) & 0xFF);
											parity_temp[12] = (byte)((((int)sword - 2147483648) >> 24) & 0xFF);
											parity_temp[13] = (byte)((((int)sword - 2147483648) >> 16) & 0xFF);
											parity_temp[14] = (byte)((((int)sword - 2147483648) >> 8) & 0xFF);
											parity_temp[15] = (byte)(((int)sword - 2147483648) & 0xFF);
											parity_ms.Write(parity_temp, 0, 16);
											parity_events++;
										}
									}

									//makefitslist
									if (makefitslist)
									{
										if (buff_events >= NumBuffEvents)
										{
											ExtractCtrdWrkr.ReportProgress(-1, "Please wait a moment while I write Centroid List buffers to disk...");
											centlist_ms_ixy.WriteTo(centlist_fs_ixy);
											centlist_ms_fxy.WriteTo(centlist_fs_fxy);
											centlist_ms_mxy.WriteTo(centlist_fs_mxy);
											timelist_ms.WriteTo(timelist_fs);
											framelist_ms.WriteTo(framelist_fs);
											centlist_ms_ixy.Position = 0;
											centlist_ms_fxy.Position = 0;
											centlist_ms_mxy.Position = 0;
											timelist_ms.Position = 0;
											framelist_ms.Position = 0;
											buff_events = 0;
										}

										centlist_temp_ixy[0] = (byte)((ixpos/*-32768*/) >> 8);
										centlist_temp_ixy[1] = (byte)((ixpos/*-32768*/) & 0xFF);
										centlist_temp_ixy[2] = (byte)((iypos/*-32768*/) >> 8);
										centlist_temp_ixy[3] = (byte)((iypos/*-32768*/) & 0xFF);
										centlist_temp_fxy[0] = (byte)((fxpos + 128) & 0xFF);
										centlist_temp_fxy[1] = (byte)((fypos + 128) & 0xFF);
										centlist_temp_mxy[0] = (byte)((mc - 32768) >> 8);
										centlist_temp_mxy[1] = (byte)((mc - 32768) & 0xFF);
										centlist_temp_mxy[2] = (byte)((dmm - 32768) >> 8);
										centlist_temp_mxy[3] = (byte)((dmm - 32768) & 0xFF);
										centlist_ms_ixy.Write(centlist_temp_ixy, 0, 4);
										centlist_ms_fxy.Write(centlist_temp_fxy, 0, 2);
										centlist_ms_mxy.Write(centlist_temp_mxy, 0, 4);

										timelist_temp[0] = (byte)(((IMTIME - 2147483648) >> 24) & 0xFF);
										timelist_temp[1] = (byte)(((IMTIME - 2147483648) >> 16) & 0xFF);
										timelist_temp[2] = (byte)(((IMTIME - 2147483648) >> 8) & 0xFF);
										timelist_temp[3] = (byte)((IMTIME - 2147483648) & 0xFF);
										timelist_ms.Write(timelist_temp, 0, 4);

										framelist_temp[0] = (byte)(((IMFRCNT - 2147483648) >> 24) & 0xFF);
										framelist_temp[1] = (byte)(((IMFRCNT - 2147483648) >> 16) & 0xFF);
										framelist_temp[2] = (byte)(((IMFRCNT - 2147483648) >> 8) & 0xFF);
										framelist_temp[3] = (byte)((IMFRCNT - 2147483648) & 0xFF);
										framelist_ms.Write(framelist_temp, 0, 4);

										buff_events++;
									}
									fr_phot++;//number of events in current frame
									tot_events++;//total number of centroids
								}
								Seg_Num++;

								if (Seg_Num * 2048 >= img_length)
									continue;

								Seg_Type = (((ARR[Seg_Num * 2048 + 6] << 8) + ARR[Seg_Num * 2048 + 7]) & 0xC000) >> 14;
								if (Seg_Type == 1)
								{
									phot_buffer[fr_count, 0] = IMTIME;
									phot_buffer[fr_count, 1] = (uint)fr_phot;
									fr_phot = 0;
									fr_count++;//frame number
								}
							}
							//PBar. do progress bar accounting and check for cancel, close files etc...
							double dprog = (100 * (double)((Seg_Num + 1) * 2048)) / (double)(img_length);
							if (dprog - (double)prog >= 1)
							{
								prog++;
								ExtractCtrdWrkr.ReportProgress(prog, k);
							}
							if (wb.DialogResult == DialogResult.Cancel)
							{
								e.Result = null;
								if (makefitslist)
								{
									centlist_fs_ixy.Close();
									centlist_fs_fxy.Close();
									centlist_fs_mxy.Close();
									centlist_ms_ixy.Close();
									centlist_ms_fxy.Close();
									centlist_ms_mxy.Close();
									timelist_fs.Close();
									timelist_ms.Close();
									framelist_fs.Close();
									framelist_ms.Close();
									File.Delete(Form1.CCDLABPATH + "templeton_cent_ixy.tmp");
									File.Delete(Form1.CCDLABPATH + "templeton_cent_fxy.tmp");
									File.Delete(Form1.CCDLABPATH + "templeton_cent_mxy.tmp");
									File.Delete(Form1.CCDLABPATH + "templeton_time.tmp");
									File.Delete(Form1.CCDLABPATH + "templeton_frame.tmp");
									File.Delete(Form1.CCDLABPATH + "templeton_parity.tmp");
								}

								GC.Collect();
								GC.WaitForFullGCApproach();
								GC.WaitForFullGCComplete();
								GC.WaitForPendingFinalizers();
								wb.Close();
								return;
							}
						}
					}
				}
				catch (Exception ee)
				{
					MessageBox.Show(string.Concat(ee.StackTrace, "\r", StartWord, "\r", Seg_Type, "\r", Seg_Num, "\r"), ee.Message);

					GC.Collect();
					GC.WaitForFullGCApproach();
					GC.WaitForFullGCComplete();
					GC.WaitForPendingFinalizers();
				}

				for (int i = 0; i <= xsize; i++)
					for (int j = 0; j <= ysize; j++)
					{
						if (darkimgcounter[i, j] <= 1)
							continue;
						darkimg[i, j] /= darkimgcounter[i, j];
						dMmimg[i, j] /= darkimgcounter[i, j];
					}
				darkimg = JPFITS.JPMath.Round(darkimg, 0, true);
				dMmimg = JPFITS.JPMath.Round(dMmimg, 0, true);

				uint[,] phot = new uint[fr_count, 2];
				for (int i = 0; i < fr_count; i++)
				{
					phot[i, 0] = phot_buffer[i, 0];
					phot[i, 1] = phot_buffer[i, 1];
				}
				phot_buffer = null;

				//parity
				if (extparity)
				{
					parity_ms.SetLength(parity_events * 12);
					parity_ms.WriteTo(parity_fs);
					parity_fs.Close();
					parity_ms.Close();
				}

				if (makefitslist)
				{
					ExtractCtrdWrkr.ReportProgress(-1, "Please wait a moment while I finish writing buffers to disk...");
					centlist_ms_ixy.SetLength(buff_events * 4);
					centlist_ms_fxy.SetLength(buff_events * 2);
					centlist_ms_mxy.SetLength(buff_events * 4);
					timelist_ms.SetLength(buff_events * 4);
					framelist_ms.SetLength(buff_events * 4);
					centlist_ms_ixy.WriteTo(centlist_fs_ixy);
					centlist_ms_fxy.WriteTo(centlist_fs_fxy);
					centlist_ms_mxy.WriteTo(centlist_fs_mxy);
					timelist_ms.WriteTo(timelist_fs);
					framelist_ms.WriteTo(framelist_fs);

					centlist_fs_ixy.Close();
					centlist_fs_fxy.Close();
					centlist_fs_mxy.Close();
					centlist_ms_ixy.Close();
					centlist_ms_fxy.Close();
					centlist_ms_mxy.Close();
					timelist_fs.Close();
					timelist_ms.Close();
					framelist_fs.Close();
					framelist_ms.Close();
				}
				FILENAMETIME = firstframetime;
				TOTTIME = (double)(lastframetime - firstframetime) / 1000.0; //seconds
				TOTFRAMS = (double)(lastframenum - firstframenum /*+ 1*/); //frames
				FRAMPSEC = TOTFRAMS / TOTTIME;
				GLOBRATE = (double)(tot_events) / TOTFRAMS;
				int indx, indy;
				SPOTRATE = TOTFRAMS / JPFITS.JPMath.Max(JPFITS.JPMath.Bin(img, resln, resln, true), out indx, out indy, true);
				RATEPSEC = (double)(tot_events) / TOTTIME;
				object[] result = new object[] { img, darkimg, dMmimg, phot, "" };
				e.Result = result;
				if (tot_events == 0)
				{
					e.Result = null;
					wb.Close();
					MessageBox.Show("No Data Found to Extract...", "Warning");
				}

				//arr = new byte[1);//try to prevent out of memory error
				//delete arr;
				//GC.ReRegisterForFinalize(arr);
				GC.Collect();
				GC.WaitForFullGCApproach();
				GC.WaitForFullGCComplete();
				GC.WaitForPendingFinalizers();
			}
			catch (OutOfMemoryException ee)
			{
				MessageBox.Show(string.Concat("I seem to have run out of memory for the moment.  Try again in a few seconds.  Close and restart if problem persists.\r\r", ee.StackTrace), "Memory Exception");
				wb.Close();

				GC.Collect();
				GC.WaitForFullGCApproach();
				GC.WaitForFullGCComplete();
				GC.WaitForPendingFinalizers();
			}
			catch (Exception ee)
			{
				MessageBox.Show(string.Concat("Inexplicitly caught exception caught...\r\r", ee.StackTrace), "Unknown Exception");
				wb.Close();

				GC.Collect();
				GC.WaitForFullGCApproach();
				GC.WaitForFullGCComplete();
				GC.WaitForPendingFinalizers();
			}
		}

		private void ExtractCtrdWrkr_ProgressChanged(object sender, ProgressChangedEventArgs e)
		{
			int intprog = e.ProgressPercentage;
			if (intprog >= 0)
			{
				int k = (int)e.UserState;
				wb.ProgressBar.Value = intprog;
				wb.TextMsg.Text = string.Concat("Completed: ", intprog.ToString(), "%");
				wb.Text = string.Concat("File ", k + 1, " of ", FULLFILELIST.Length, ": ", intprog.ToString(), "%");
			}
			else if (intprog == -1)
			{
				wb.TextMsg.Text = (string)e.UserState;
			}
			else if (intprog == -2)
			{
				wb.CancelBtn.Enabled = false;
			}
			else if (intprog == -3)
			{
				wb.CancelBtn.Enabled = true;
			}
		}

		private void ExtractCtrdWrkr_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
		{
			if (e.Result != null)
			{
				object[] result = (object[])e.Result;
				SaveFileDialog fd = new SaveFileDialog();
				//fd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "SaveFilesPath");
				fd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath");
				fd.Title = "Please Save the Generated Fits Files";
				fd.Filter = "Fits File (*.fits)|*.fits";

				try
				{
					//s_0404_i_0145_q_0001
					int i = FILELIST[0].LastIndexOf("q");
					fd.FileName = FILELIST[0].Substring(i - 5, 4);
					Clipboard.SetText(fd.FileName);
				}
				catch
				{
					int i = FILELIST[0].LastIndexOf(".");
					fd.FileName = FILELIST[0].Substring(0, i);
					Clipboard.SetText(fd.FileName);
				}

				wb.Close();

				if (fd.ShowDialog() == DialogResult.OK)
				{
					JPFITS.REG.SetReg("CCDLAB", "SaveFilesPath", fd.FileName.Substring(0, fd.FileName.LastIndexOf("\\")));
					JPFITS.REG.SetReg("CCDLAB", "OpenFilesPath", fd.FileName.Substring(0, fd.FileName.LastIndexOf("\\")));
					string fullfilename = fd.FileName;
					result[4] = fullfilename;
					wb = new JPFITS.WaitBar();
					wb.ProgressBar.Maximum = 100;
					wb.CancelBtn.Enabled = false;
					FitsResultsWriteWrkr.RunWorkerAsync(result);
					wb.ShowDialog();
				}
			}
			GC.Collect();
			GC.WaitForFullGCApproach();
			GC.WaitForFullGCComplete();
			GC.WaitForPendingFinalizers();
		}

		private void FitsResultsWriteWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			FitsResultsWriteWrkr.ReportProgress(-1, "Please wait a moment while I write the FITS Images to disk...");

			object[] result = (object[])e.Argument;
			string fullfilename = (string)result[4];

			JPFITS.FITSImage img = new JPFITS.FITSImage(fullfilename, (uint[,])result[0], true, true);
			AddImageInfoKeys(img);

			//disabled
			/*if (CorrectCoordsChck.Checked)
			{
				//correct the image coordinates to align with telescope axes
				//this is a unique correction for each of FUV, NUV, and VIS, so need to check the channel
				//requires flipping &/or rotating the images
				//implement in JPFITS...DONE
				//here might need to correct the XOFFSET, XSIZE (&Y) header values...
				//all of this will also need to appear identically for integrate mode extraxtion
				///also will need to apply it into the sub-range checkchanged fcn to de-transform back into read-out coords for when extracting data
				//i.e., if looking at transformed images, and want to extract a subrange, then that subrange needs transformed back into readout coords
				if (img.Header.GetKeyValue("CHANNEL") == "VIS")
				{
					img.RotateCW(true);
					img.FlipHorizontal();

					int xoffset = Convert.ToInt32(img.Header.GetKeyValue("XOFFSET"));
					int yoffset = Convert.ToInt32(img.Header.GetKeyValue("YOFFSET"));
					int xsize = Convert.ToInt32(img.Header.GetKeyValue("XSIZE"));
					int ysize = Convert.ToInt32(img.Header.GetKeyValue("YSIZE"));
					//rot'n
					img.Header.SetKey("XOFFSET",(511 - yoffset - ysize).ToString(),false,-1);
					img.Header.SetKey("YOFFSET",xoffset.ToString(),false,-1);
					img.Header.SetKey("XSIZE",ysize.ToString(),false,-1);
					img.Header.SetKey("YSIZE",xsize.ToString(),false,-1);
					xoffset = Convert.ToInt32(img.Header.GetKeyValue("XOFFSET"));
					yoffset = Convert.ToInt32(img.Header.GetKeyValue("YOFFSET"));
					xsize = Convert.ToInt32(img.Header.GetKeyValue("XSIZE"));
					ysize = Convert.ToInt32(img.Header.GetKeyValue("YSIZE"));
					//Horz flip
					img.Header.SetKey("XOFFSET",(511 - xoffset - xsize).ToString(),false,-1);//no change in size or in y coords
				}
				if (img.Header.GetKeyValue("CHANNEL") == "NUV")
				{
					img.RotateCW(false);
					//img.FlipVertical();
				}
				//if (fits.Header.GetKeyValue("CHANNEL") == "FUV")
				//{
				//	fits.RotateCW(true);
				//}
			}*/

			img.WriteImage(TypeCode.UInt32, true);
			int tot_events = (int)JPFITS.JPMath.Sum(img.Image, true);

			if (AugFilesChck.Checked)
			{
				string darkname = string.Concat(fullfilename.Substring(0, fullfilename.LastIndexOf(".")), "_MinCorners", fullfilename.Substring(fullfilename.LastIndexOf(".")));
				JPFITS.FITSImage darkimg = new JPFITS.FITSImage(darkname, (double[,])result[1], false, true);
				AddImageInfoKeys(darkimg);
				darkimg.WriteImage(TypeCode.UInt16, true);

				string dMmname = string.Concat(fullfilename.Substring(0, fullfilename.LastIndexOf(".")), "_deltaMaxMinCorners", fullfilename.Substring(fullfilename.LastIndexOf(".")));
				JPFITS.FITSImage dMmimg = new JPFITS.FITSImage(dMmname, (double[,])result[2], false, true);
				AddImageInfoKeys(dMmimg);
				dMmimg.WriteImage(TypeCode.UInt16, true);

				string imphotname = string.Concat(fullfilename.Substring(0, fullfilename.LastIndexOf(".")), "_PerImageCounts", fullfilename.Substring(fullfilename.LastIndexOf(".")));
				JPFITS.FITSImage imphot = new JPFITS.FITSImage(imphotname, (uint[,])result[3], false, true);
				imphot.Header.AddKey("ROW1", "Image Frame Time", "Milliseconds", -1);
				imphot.Header.AddKey("ROW2", "Total Count", "In Single Frame", -1);
				AddImageInfoKeys(imphot);
				imphot.WriteImage(TypeCode.UInt32, true);
			}

			if (ExtParityChck.Checked == true)
			{
				int tot_parevents = (int)((new System.IO.FileInfo(Form1.CCDLABPATH + "templeton_parity.tmp").Length) / 16);
				if (tot_parevents != 0)
				{
					double parody_rate = (double)(tot_parevents) / (double)(tot_events);
					string fitsparityname = string.Concat(fullfilename.Substring(0, fullfilename.LastIndexOf(".")), "_Parity", fullfilename.Substring(fullfilename.LastIndexOf(".")));
					JPFITS.FITSImage parity_fits = new JPFITS.FITSImage(fitsparityname, Form1.CCDLABPATH + "templeton_parity.tmp", TypeCode.UInt32, 4, tot_parevents);
					parity_fits.Header.AddKey("PRTYRATE", Math.Round(parody_rate * 100, 4).ToString(), "Percent Rate of Parity Errors per Centroid", -1);
					parity_fits.Header.AddKey("FILEINF0", "Parity Errors", "[EventNum DataFlag WordNumber DataValue]", -1);
					parity_fits.Header.AddKey("FILEINF1", "DataFlag INFO", "1,2,or,3=xword,yword,cornerword", -1);
					AddImageInfoKeys(parity_fits);
					parity_fits.WriteFileFromDiskBuffer(true);
					MessageBox.Show(String.Concat(tot_parevents, " parity errors detected!"), "Parity Check...");
				}
				else
				{
					MessageBox.Show("No parity errors detected, no parity file written", "Parity Check...");
				}
			}

			if (ExtractListChck.Checked == true)
			{
				bool FPNcorrectlist = GSEApplyFPNCorrectionChck.Checked;
				bool distortioncorrectlist = GSEApplyDistortionCorrectionChck.Checked;

				string fitstimename = string.Concat(fullfilename.Substring(0, fullfilename.LastIndexOf(".")), "_TimeList", fullfilename.Substring(fullfilename.LastIndexOf(".")));
				FitsResultsWriteWrkr.ReportProgress(-1, string.Concat("Please wait a moment while I write: ", fitstimename.Substring(1 + fitstimename.LastIndexOf("\\"))));
				JPFITS.FITSImage time_fits = new JPFITS.FITSImage(fitstimename, Form1.CCDLABPATH + "templeton_time.tmp", TypeCode.UInt32, 1, tot_events);
				time_fits.FileName = time_fits.FileName.Replace("_TimeList", "_" + FILENAMETIME.ToString("0000000000000") + "_TimeList");
				fitstimename = time_fits.FullFileName;
				time_fits.Header.AddKey("FILEINFO", "Time List", "Centroid Image Time (millisec)", -1);
				AddImageInfoKeys(time_fits);
				time_fits.WriteFileFromDiskBuffer(true);

				string fitsframename = fitstimename.Replace("TimeList", "FrameList");//string.Concat(fullfilename.Substring(0, fullfilename.LastIndexOf(".")), "_FrameList", fullfilename.Substring(fullfilename.LastIndexOf(".")));
				FitsResultsWriteWrkr.ReportProgress(-1, string.Concat("Please wait a moment while I write: ", fitsframename.Substring(1 + fitsframename.LastIndexOf("\\"))));
				JPFITS.FITSImage frame_fits = new JPFITS.FITSImage(fitsframename, Form1.CCDLABPATH + "templeton_frame.tmp", TypeCode.UInt32, 1, tot_events);
				frame_fits.Header.AddKey("FILEINFO", "Frame List", "Frame Count Number", -1);
				AddImageInfoKeys(frame_fits);
				frame_fits.WriteFileFromDiskBuffer(true);

				string xyintslistname = fitstimename.Replace("TimeList", "XYInts_List");//string.Concat(fullfilename.Substring(0, img.FullFileName.LastIndexOf(".")), "_XYInts_List", fullfilename.Substring(img.FullFileName.LastIndexOf(".")));
				if (distortioncorrectlist)
					xyintslistname = xyintslistname.Replace("XYInts_List", "XYInts_List_deDIST");
				if (FPNcorrectlist)
					xyintslistname = xyintslistname.Replace("XYInts_List", "XYInts_List_deFPN");
				FitsResultsWriteWrkr.ReportProgress(-1, string.Concat("Please wait a moment while I write: ", xyintslistname.Substring(1 + xyintslistname.LastIndexOf("\\"))));
				JPFITS.FITSImage xy_ints_fits = new JPFITS.FITSImage(xyintslistname, Form1.CCDLABPATH + "templeton_cent_ixy.tmp", TypeCode.Int16, 2, tot_events);
				xy_ints_fits.Header.AddKey("FILEINFO", "Centroid List", "Centroid [X Y] Integers (*32)", -1);
				AddImageInfoKeys(xy_ints_fits);
				xy_ints_fits.WriteFileFromDiskBuffer(true);

				string xyfraclistname = fitstimename.Replace("TimeList", "XYFrac_List");//string.Concat(fullfilename.Substring(0, img.FullFileName.LastIndexOf(".")), "_XYFrac_List", fullfilename.Substring(img.FullFileName.LastIndexOf(".")));
				if (distortioncorrectlist)
					xyfraclistname = xyfraclistname.Replace("XYFrac_List", "XYFrac_List_deDIST");
				if (FPNcorrectlist)
					xyfraclistname = xyfraclistname.Replace("XYFrac_List", "XYFrac_List_deFPN");
				FitsResultsWriteWrkr.ReportProgress(-1, string.Concat("Please wait a moment while I write: ", xyfraclistname.Substring(1 + xyfraclistname.LastIndexOf("\\"))));
				JPFITS.FITSImage xy_frac_fits = new JPFITS.FITSImage(xyfraclistname, Form1.CCDLABPATH + "templeton_cent_fxy.tmp", TypeCode.Byte, 2, tot_events);
				xy_frac_fits.Header.AddKey("FILEINFO", "Centroid List", "Centroid [X Y] Fractions (*32)", -1);
				AddImageInfoKeys(xy_frac_fits);
				xy_frac_fits.WriteFileFromDiskBuffer(true);

				string xymdmmlistname = fitstimename.Replace("TimeList", "XYmdMm_List");//string.Concat(fullfilename.Substring(0,img.FullFileName.LastIndexOf(".")),"_XYmdMm_List",fullfilename.Substring(img.FullFileName.LastIndexOf(".")));
				FitsResultsWriteWrkr.ReportProgress(-1, string.Concat("Please wait a moment while I write: ", xymdmmlistname.Substring(1 + xymdmmlistname.LastIndexOf("\\"))));
				JPFITS.FITSImage xy_mdmm_fits = new JPFITS.FITSImage(xymdmmlistname, Form1.CCDLABPATH + "templeton_cent_mxy.tmp", TypeCode.UInt16, 2, tot_events);
				xy_mdmm_fits.Header.AddKey("FILEINFO", "Centroid List", "Centroid [Max  Max-min]", -1);
				AddImageInfoKeys(xy_mdmm_fits);
				xy_mdmm_fits.WriteFileFromDiskBuffer(true);
			}
		}

		private void FitsResultsWriteWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			int intprog = e.ProgressPercentage;
			if (intprog >= 0)
			{
				int k = (int)e.UserState;
				wb.ProgressBar.Value = intprog;
				wb.TextMsg.Text = string.Concat("Completed: ", intprog.ToString(), "%");
				wb.Text = string.Concat("File ", k + 1, " of ", FULLFILELIST.Length, ": ", intprog.ToString(), "%");
			}
			else if (intprog == -1)
			{
				wb.TextMsg.Text = (string)e.UserState;
			}
			else if (intprog == -2)
			{
				wb.CancelBtn.Enabled = false;
			}
			else if (intprog == -3)
			{
				wb.CancelBtn.Enabled = true;
			}
		}

		private void FitsResultsWriteWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			wb.Close();
			GC.Collect();
			GC.WaitForFullGCApproach();
			GC.WaitForFullGCComplete();
			GC.WaitForPendingFinalizers();
		}

		private void AddImageInfoKeys(JPFITS.FITSImage fit)
		{
			fit.Header.AddKey("SRCFILE", FILELIST[0].Substring(2, 18), "Source Data *.img File Name", -1);
			fit.Header.AddKey("TOTTIME", TOTTIME.ToString(), "Total Imaging Time (seconds)", -1);
			fit.Header.AddKey("TOTFRAMS", TOTFRAMS.ToString(), "Total Number of Frames", -1);
			fit.Header.AddKey("FRAMPSEC", Math.Round(FRAMPSEC, 4).ToString(), "Frames per Second", -1);
			fit.Header.AddKey("GLOBRATE", Math.Round(GLOBRATE, 1).ToString(), "Global Count Rate (c/f)", -1);
			fit.Header.AddKey("SPOTRATE", Math.Round(SPOTRATE, 1).ToString(), "Max Spot Count Rate (f/c)", -1);
			fit.Header.AddKey("RATEPSEC", Math.Round(RATEPSEC, 2).ToString(), "Global Count Rate per Second", -1);
			fit.Header.AddKey("EXTRDATE", System.DateTime.Now.ToString(), "*.raw File Extraction Date", -1);
			fit.Header.AddKey("CNTDRSLN", CentroidResolutionUpD.Value.ToString(), "Centroid Resolution; Fractional Pixel", -1);
			fit.Header.AddKey("IMFRCNT", IMFRCNT.ToString(), "Image Frame Count", -1);
			fit.Header.AddKey("FRMTIME", ((double)(IMTIME) / 1000.0).ToString(), "Image Frame Time (sec)", -1);
			fit.Header.AddKey("DETECTOR", CHANNEL, "UVIT Channel", -1);
			fit.Header.AddKey("MODE", MODE, "Data Collection Mode", -1);
			fit.Header.AddKey("SOURCE", SOURCE, "Data Source", -1);
			fit.Header.AddKey("ALGRITHM", ALGRTHM, "Centroiding Algorithm", -1);
			fit.Header.AddKey("GAPTIME",/*Math.Round(*/ROWGAPT/*,3)*/.ToString(), "Row Gap Time (0-511)", -1);
			fit.Header.AddKey("GAIN", GAIN.ToString(), "Gain (1,2,4,8)", -1);
			fit.Header.AddKey("NO_FRMS", STACKING.ToString(), "Stacking (1,2,4,8,16)", -1);
			fit.Header.AddKey("NORMLZN", NORMLZN.ToString(), "Normalization (1,2,4,8,16)", -1);
			fit.Header.AddKey("RSETBIAS", Math.Round(RSETBIAS, 3).ToString(), "Reset Bias (V); Using DN~1.95mV", -1);
			fit.Header.AddKey("XOFFSET", XOFFSET.ToString(), "Zero-Based X Off-Set", -1);
			fit.Header.AddKey("XSIZE", XSIZE.ToString(), "Zero-Based X Size: #Columns - 1", -1);
			fit.Header.AddKey("YOFFSET", YOFFSET.ToString(), "Zero-Based Y Off-Set", -1);
			fit.Header.AddKey("YSIZE", YSIZE.ToString(), "Zero-Based Y Size: #Rows - 1", -1);
			if (SubImChck.Checked)
			{
				fit.Header.AddKey("EXTXRNG", string.Concat(Convert.ToString(JPFITS.REG.GetReg("CCDLAB", "XStart")), ":", Convert.ToString(JPFITS.REG.GetReg("CCDLAB", "XEnd"))), "Extracted X-Range: Zero-Based", -1);
				fit.Header.AddKey("EXTYRNG", string.Concat(Convert.ToString(JPFITS.REG.GetReg("CCDLAB", "YStart")), ":", Convert.ToString(JPFITS.REG.GetReg("CCDLAB", "YEnd"))), "Extracted Y-Range: Zero-Based", -1);
			}
			else
			{
				fit.Header.AddKey("EXTXRNG", "0:511", "Extracted X-Range: Zero-Based", -1);
				fit.Header.AddKey("EXTYRNG", "0:511", "Extracted Y-Range: Zero-Based", -1);
			}
			fit.Header.AddKey("RAMPTIME", Math.Round(RAMPTIME, 5).ToString(), "Ramp Time (sec); Using DN~0.1msec", -1);
			fit.Header.AddKey("RAMPTTOT", RAMPTTOT.ToString(), "Total Ramp Time (s)", -1);
			fit.Header.AddKey("PIXTHRSH", PIXTHRSH.ToString(), "Pixel Threshold", -1);
			fit.Header.AddKey("ENGTHRSH", ENGTHRSH.ToString(), "Energy Threshold (*32 value)", -1);
			fit.Header.AddKey("BODL", BODL.ToString(), "Bright Object Length (pixels)", -1);
			fit.Header.AddKey("BODH", BODH.ToString(), "Bright Object Height (counts)", -1);
			fit.Header.AddKey("BODF", BODF.ToString(), "Bright Object Frames (frames)", -1);
			fit.Header.AddKey("AND_CMD", ANDVOLTS_CMD.ToString(), "ANODE Command Voltage; Using DN~1.95V", -1);
			fit.Header.AddKey("MCP_CMD", MCPVOLTS_CMD.ToString(), "MCP Command Voltage; Using DN~0.98V", -1);
			fit.Header.AddKey("CAT_CMD", PCVOLTS_CMD.ToString(), "CATHODE Command Voltage; Using DN~-0.20V", -1);
			fit.Header.AddKey("AND_TEL", ANDVOLTS_TEL.ToString(), "ANODE Telemetry Voltage; Using DN~9.4172V", -1);
			fit.Header.AddKey("MCP_TEL", MCPVOLTS_TEL.ToString(), "MCP Telemetry Voltage; Using DN~4.7086V", -1);
			fit.Header.AddKey("CAT_TEL", CATVOLTS_TEL.ToString(), "CATHODE Telemetry Voltage; Using DN~-0.4709V", -1);
			fit.Header.AddKey("HVU_TEL", HVUCURRENT_TEL.ToString(), "HVU Telemetry Current; Using DN~0.04709uA", -1);
			fit.Header.AddKey("REA+5V", REAp5V.ToString(), "REA+5V; Using DN~2.93mV", -1);
			fit.Header.AddKey("REA3p3V", REAp3p3V.ToString(), "REA+3.3V; Using DN~2.93mV", -1);
			fit.Header.AddKey("REA+12V", REAp12V.ToString(), "REA+12V; Using DN~16.1mV", -1);
			fit.Header.AddKey("REA-12V", REAm12V.ToString(), "REA-12V; Using DN~16.1mV", -1);
			fit.Header.AddKey("HVU+30V", HVUp30V.ToString(), "HVU+30V; Using DN~16.1mV", -1);
			fit.Header.AddKey("HVU+15V", HVUp15V.ToString(), "HVU+15V; Using DN~16.1mV", -1);
			fit.Header.AddKey("HVU-15V", HVUm15V.ToString(), "HVU-15V; Using DN~16.1mV", -1);
			fit.Header.AddKey("CPU+12V", CPUp12V.ToString(), "CPU+12V; Using DN~16.1mV", -1);
			fit.Header.AddKey("CPU-12V", CPUm12V.ToString(), "CPU-12V; Using DN~16.1mV", -1);
			fit.Header.AddKey("ZEROVREF", ZEROVREF.ToString(), "Zero Volt Ref.; Using DN~1.46mV", -1);
			fit.Header.AddKey("REA+5VC", REAp5VCUR.ToString(), "REA+5V Current; Using DN~3.08mA", -1);
			fit.Header.AddKey("REA3p3VC", REAp3p3VCUR.ToString(), "REA+3.3V Current; Using DN~2.93mA", -1);
			fit.Header.AddKey("REA+12VC", REAp12VCUR.ToString(), "REA+12V Current; Using DN~0.185mA", -1);
			fit.Header.AddKey("REA-12VC", REAm12VCUR.ToString(), "REA-12V Current; Using DN~0.185mA", -1);
			fit.Header.AddKey("HVU+30VC", HVUp15VCUR.ToString(), "HVU+30V Current; Using DN~0.432mA", -1);
			fit.Header.AddKey("HVU+15VC", HVUp15VCUR.ToString(), "HVU+15V Current; Using DN~0.185mA", -1);
			fit.Header.AddKey("HVU-15VC", HVUm15VCUR.ToString(), "HVU-15V Current; Using DN~0.185mA", -1);
			fit.Header.AddKey("CPU+12VC", CPUp12VCUR.ToString(), "CPU+12V Current; Using DN~0.185mA", -1);
			fit.Header.AddKey("CPU-12VC", CPUm12VCUR.ToString(), "CPU-12V Current; Using DN~0.185mA", -1);
		}

		private void UpDateTELVolts(byte[] arr, int Seg_Num)//assuming arr starts at a synch
		{
			int word;

			//REA +5V
			word = (int)((((arr[Seg_Num * 2048 + 37 * 2] << 8) | arr[Seg_Num * 2048 + 37 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAp5V = (double)(word) * REAp5VpDN / 1000;

			//REA +3.3V
			word = (int)((((arr[Seg_Num * 2048 + 38 * 2] << 8) | arr[Seg_Num * 2048 + 38 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAp3p3V = (double)(word) * REAp3p3VpDN / 1000;

			//REA+12V
			word = (int)((((arr[Seg_Num * 2048 + 39 * 2] << 8) | arr[Seg_Num * 2048 + 39 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAp12V = (double)(word) * REA12VpDN / 1000;

			//REA-12V
			word = (int)((((arr[Seg_Num * 2048 + 40 * 2] << 8) | arr[Seg_Num * 2048 + 40 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAm12V = -(double)(word) * REA12VpDN / 1000;

			//HVU+30V
			word = (int)((((arr[Seg_Num * 2048 + 41 * 2] << 8) | arr[Seg_Num * 2048 + 41 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUp30V = (double)(word) * HVU30VpDN / 1000;

			//HVU+15V
			word = (int)((((arr[Seg_Num * 2048 + 42 * 2] << 8) | arr[Seg_Num * 2048 + 42 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUp15V = (double)(word) * HVU15VpDN / 1000;

			//HVU-15V
			word = (int)((((arr[Seg_Num * 2048 + 43 * 2] << 8) | arr[Seg_Num * 2048 + 43 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUm15V = -(double)(word) * HVU15VpDN / 1000;

			//CPU +12V
			word = (int)((((arr[Seg_Num * 2048 + 44 * 2] << 8) | arr[Seg_Num * 2048 + 44 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			CPUp12V = (double)(word) * CPU12VpDN / 1000;

			//CPU -12V
			word = (int)((((arr[Seg_Num * 2048 + 45 * 2] << 8) | arr[Seg_Num * 2048 + 45 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			CPUm12V = -(double)(word) * CPU12VpDN / 1000;

			//Zero Volt Reference
			word = (int)((((arr[Seg_Num * 2048 + 46 * 2] << 8) | arr[Seg_Num * 2048 + 46 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			ZEROVREF = (double)(word) * ZEROVREFVpDN / 1000;

			//REA +5V Current
			word = (int)((((arr[Seg_Num * 2048 + 47 * 2] << 8) | arr[Seg_Num * 2048 + 47 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAp5VCUR = (double)(word) * REA5VApDN;

			//REA +3.3V Current
			word = (int)((((arr[Seg_Num * 2048 + 48 * 2] << 8) | arr[Seg_Num * 2048 + 48 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAp3p3VCUR = (double)(word) * REA3p3VApDN;

			//REA +12V Current
			word = (int)((((arr[Seg_Num * 2048 + 49 * 2] << 8) | arr[Seg_Num * 2048 + 49 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAp12VCUR = (double)(word) * REA12VApDN;

			//REA -12V Current
			word = (int)((((arr[Seg_Num * 2048 + 50 * 2] << 8) | arr[Seg_Num * 2048 + 50 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			REAm12VCUR = -(double)(word) * REA12VApDN;

			//HVU +30V Current
			word = (int)((((arr[Seg_Num * 2048 + 51 * 2] << 8) | arr[Seg_Num * 2048 + 51 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUp30VCUR = (double)(word) * HVU30VApDN;

			//HVU +15V Current
			word = (int)((((arr[Seg_Num * 2048 + 52 * 2] << 8) | arr[Seg_Num * 2048 + 52 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUp15VCUR = (double)(word) * HVU15VApDN;

			//HVU -15V Current
			word = (int)((((arr[Seg_Num * 2048 + 53 * 2] << 8) | arr[Seg_Num * 2048 + 53 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUm15VCUR = -(double)(word) * HVU15VApDN;

			//CPU +12V Current
			word = (int)((((arr[Seg_Num * 2048 + 54 * 2] << 8) | arr[Seg_Num * 2048 + 54 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			CPUp12VCUR = (double)(word) * CPU12VApDM;

			//CPU -12V Current
			word = (int)((((arr[Seg_Num * 2048 + 55 * 2] << 8) | arr[Seg_Num * 2048 + 55 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			CPUm12VCUR = -(double)(word) * CPU12VApDM;

			//update HVU telem 
			word = (int)((((arr[Seg_Num * 2048 + 56 * 2] << 8) | arr[Seg_Num * 2048 + 56 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			ANDVOLTS_TEL = (int)((double)(word) * ANDTELVpDN);

			word = (int)((((arr[Seg_Num * 2048 + 57 * 2] << 8) | arr[Seg_Num * 2048 + 57 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			MCPVOLTS_TEL = (int)((double)(word) * MCPTELVpDN);

			word = (int)((((arr[Seg_Num * 2048 + 58 * 2] << 8) | arr[Seg_Num * 2048 + 58 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			CATVOLTS_TEL = (int)((double)(word) * CATTELVpDN);

			word = (int)((((arr[Seg_Num * 2048 + 59 * 2] << 8) | arr[Seg_Num * 2048 + 59 * 2 + 1]) & 0xFFF));
			if (word > 2048)
				word = Math.Abs(word - 4096);
			HVUCURRENT_TEL = (double)(word) * HVUTELApDN;  //uA
		}

		private void SubImChck_CheckedChanged(object sender, EventArgs e)
		{
			if (SubImChck.Checked == true)
			{
				ExtractPanel.Size = new System.Drawing.Size(99, ExtractPanel.Height + 29);
				ExtCentPanel.Location = new System.Drawing.Point(0, ExtCentPanel.Location.Y + 29);
				RangeDlg dlg = new RangeDlg();
				dlg.XStartUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "XStart"));
				dlg.XEndUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "XEnd"));
				dlg.YStartUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "YStart"));
				dlg.YEndUpD.Value = Convert.ToInt32(JPFITS.REG.GetReg("CCDLAB", "YEnd"));
				dlg.ShowDialog();

				if (dlg.DialogResult == DialogResult.OK)
				{
					SUBRANGE[0] = (int)dlg.XStartUpD.Value;
					SUBRANGE[1] = (int)dlg.XEndUpD.Value;
					SUBRANGE[2] = (int)dlg.YStartUpD.Value;
					SUBRANGE[3] = (int)dlg.YEndUpD.Value;
					JPFITS.REG.SetReg("CCDLAB", "XStart", dlg.XStartUpD.Value.ToString());
					JPFITS.REG.SetReg("CCDLAB", "XEnd", dlg.XEndUpD.Value.ToString());
					JPFITS.REG.SetReg("CCDLAB", "YStart", dlg.YStartUpD.Value.ToString());
					JPFITS.REG.SetReg("CCDLAB", "YEnd", dlg.YEndUpD.Value.ToString());
					XLabel.Text = string.Concat("X = ", SUBRANGE[0], ":", SUBRANGE[1]);
					YLabel.Text = string.Concat("Y = ", SUBRANGE[2], ":", SUBRANGE[3]);

					//disabled
					/*
					//if VIS, NUV, or FUV, check if telescope coordinate transform is checked and de-transform the SUBRANGE into read-out coordinates
					//how to find channel . the least which is done here is having opened an .img file.
					//use EXTRCN_CHANNEL . 14, 15, 16 = FUV, NUV, VIS
					//then just de-transform SUBRANGE, keeping the process hidden from the user
					//must do the de-transform in the REVERSE order that it was done originally!
					if (CorrectCoordsChck.Checked)
					{
						int xstart = SUBRANGE[0];
						int xend   = SUBRANGE[1];
						int ystart = SUBRANGE[2];
						int yend   = SUBRANGE[3];

						if (EXTRCN_CHANNEL == 16)//VIS .de-flip hosizontal & de-rotate CW (i.e., flip horizontal & rotate CCW)
						{
							//img.RotateCW(true);
							//img.FlipHorizontal();
							//horz flip
							SUBRANGE[0] = 511 - xend;	//new xstart
							SUBRANGE[1] = 511 - xstart;	//new xend
							xstart = SUBRANGE[0];
							xend = SUBRANGE[1];
							//CCW rotn
							SUBRANGE[0] =		ystart;	//new xstart
							SUBRANGE[1] =		yend;	//new xend
							SUBRANGE[2] = 511 -	xend;	//new ystart
							SUBRANGE[3] = 511 - xstart;	//new yend

						}
						if (EXTRCN_CHANNEL == 15)//NUV
						{
						}
						if (EXTRCN_CHANNEL == 14)//FUV
						{
						}
					}*/
				}
				else
				{
					SubImChck.Checked = false;
				}
			}
			else
			{
				SUBRANGE[0] = 0;
				SUBRANGE[1] = 511;
				SUBRANGE[2] = 0;
				SUBRANGE[3] = 511;
				XLabel.Text = string.Concat("X = ", SUBRANGE[0], ":", SUBRANGE[1]);
				YLabel.Text = string.Concat("Y = ", SUBRANGE[2], ":", SUBRANGE[3]);
				ExtractPanel.Size = new System.Drawing.Size(99, ExtractPanel.Height - 29);
				ExtCentPanel.Location = new System.Drawing.Point(0, ExtCentPanel.Location.Y - 29);
			}
		}

		private void CentroidResolutionUpD_ValueChanged(object sender, EventArgs e)
		{
			if (CentroidResolutionUpD.Value == 16)
				CentroidResolutionUpD.Increment = 8;
			if (CentroidResolutionUpD.Value == 24)
			{
				CentroidResolutionUpD.Value = 32;
				CentroidResolutionUpD.Increment = 16;
			}
			if (CentroidResolutionUpD.Value == 8)
				CentroidResolutionUpD.Increment = 4;
			if (CentroidResolutionUpD.Value == 12)
				CentroidResolutionUpD.Value = 16;
			if (CentroidResolutionUpD.Value == 4)
				CentroidResolutionUpD.Increment = 2;
			if (CentroidResolutionUpD.Value == 6)
				CentroidResolutionUpD.Value = 8;
			if (CentroidResolutionUpD.Value == 2)
				CentroidResolutionUpD.Increment = 1;
			if (CentroidResolutionUpD.Value == 3)
				CentroidResolutionUpD.Value = 4;
		}

		private ushort ReadWord(BinaryReader br)
		{
			ushort LEWord = 0;
			ushort BEWord = 0;
			LEWord = br.ReadUInt16();//little endian word - first word of segment
			BEWord = (ushort)(((LEWord & 0xff) << 8) | (LEWord & 0xff00) >> 8);//convert to big endian word
			return BEWord;
		}

		private ushort ReadWord_FromArr(byte[] arr, int byte_pos)
		{
			return ((ushort)((arr[byte_pos] << 8) | arr[byte_pos + 1]));
		}

		private void xDecs_Click(object sender, EventArgs e)
		{
			OpenFileDialog fd = new OpenFileDialog();
			fd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "SaveFilesPath");
			fd.Title = "Please Open the FRACTIONALS ('XYFrac_List') File...";
			fd.Filter = "Fits File (*.fits)|*.fits";

			if (fd.ShowDialog() == DialogResult.OK)
			{
				string filename = fd.FileName;
				JPFITS.FITSImage fits = new JPFITS.FITSImage(filename, null, true, false, false, true);
				int[] rx = new int[] { 0, 0, 0, fits.Height - 1 };
				int[] ry = new int[] { 1, 1, 0, fits.Height - 1 };
				double[] X = JPFITS.FITSImage.ReadImageVectorOnly(filename, rx, true);
				double[] Y = JPFITS.FITSImage.ReadImageVectorOnly(filename, ry, true);

				string algorithm = fits.Header.GetKeyValue("ALGRITHM");

				JPPlot Xhist = new JPPlot();
				double[] x;
				double[] y;
				y = JPFITS.JPMath.Histogram_IntegerStep(X, 1, out x);
				Xhist.Text = string.Concat(algorithm, " X Decimal Centroids");
				Xhist.PlotLine(x, y, "X Decimal Centroid Position (*32)", "Number of Centroids", String.Concat(algorithm, " X Decimal Centroids"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "XDecimals");

				JPPlot Yhist = new JPPlot();
				y = JPFITS.JPMath.Histogram_IntegerStep(Y, 1, out x);
				Yhist.Text = string.Concat(algorithm, " Y Decimal Centroids");
				Yhist.PlotLine(x, y, "Y Decimal Centroid Position (*32)", "Number of Centroids", String.Concat(algorithm, " Y Decimal Centroids"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "XDecimals");
			}
		}

		private void xInts_Click(object sender, EventArgs e)
		{
			OpenFileDialog fd = new OpenFileDialog();
			fd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "SaveFilesPath");
			fd.Title = "Please Open the INTEGERS ('XYInts_List') File...";
			fd.Filter = "Fits File (*.fits)|*.fits";

			if (fd.ShowDialog() == DialogResult.OK)
			{
				string filename = fd.FileName;
				JPFITS.FITSImage fits = new JPFITS.FITSImage(filename, null, true, false, false, true);
				int[] rx = new int[] { 0, 0, 0, fits.Height - 1 };
				int[] ry = new int[] { 1, 1, 0, fits.Height - 1 };
				double[] X = (double[])JPFITS.FITSImage.ReadImageVectorOnly(filename, rx, true);
				double[] Y = (double[])JPFITS.FITSImage.ReadImageVectorOnly(filename, ry, true);

				string algorithm = fits.Header.GetKeyValue("ALGRITHM");

				JPPlot Xhist = new JPPlot();
				double[] x;
				double[] y;
				y = JPFITS.JPMath.Histogram_IntegerStep(X, 1, out x);
				Xhist.Text = string.Concat(algorithm, " X Integer Centroids");
				Xhist.PlotLine(x, y, "X Integer Centroid Position (*32)", "Number of Centroids", string.Concat(algorithm, " X Integer Centroids"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "XInts");

				JPPlot Yhist = new JPPlot();
				y = JPFITS.JPMath.Histogram_IntegerStep(Y, 1, out x);
				Yhist.Text = string.Concat(algorithm, " Y Integer Centroids");
				Yhist.PlotLine(x, y, "Y Integer Centroid Position (*32)", "Number of Centroids", string.Concat(algorithm, " Y Integer Centroids"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "YInts");
			}
		}

		private void max_Click(object sender, EventArgs e)
		{
			OpenFileDialog fd = new OpenFileDialog();
			fd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "SaveFilesPath");
			fd.Title = "Please Open the Max, delta Max-Min ('MdMm_List') File...";
			fd.Filter = "Fits File (*.fits)|*.fits";

			if (fd.ShowDialog() == DialogResult.OK)
			{
				string filename = fd.FileName;
				JPFITS.FITSImage fits = new JPFITS.FITSImage(filename, null, true, false, false, true);
				int h = fits.Height;
				double[,] a = JPFITS.FITSImage.ReadImageArrayOnly(filename, null, true);
				double[] a1 = new double[h * 2];
				for (int j = 0; j < 2; j++)
					for (int i = 0; i < h; i++)
						a1[i + j * h] = a[j, i];

				string algorithm = fits.Header.GetKeyValue("ALGRITHM");
				JPPlot jpplot = new JPPlot();
				double[] x;
				double[] y;
				y = JPFITS.JPMath.Histogram_IntegerStep(a1, 1, out x);
				jpplot.Text = string.Concat(algorithm, "Corner Max & Corner Max-Min");
				jpplot.PlotLine(x, y, "Corner Max & Corner Max-Min(/16)", "Number of Centroids", string.Concat(algorithm, "Corner Max & Corner Max-Min"), System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column, "Max-Min");
			}
		}

		public static bool Check_Even_Parity_Flag(ushort word)
		{
			ushort x = (ushort)(word >> 1);//first fifteen bits are data, 16'th bit is parity
			x = (ushort)(x ^ (x >> 8));
			x = (ushort)(x ^ (x >> 4));
			x = (ushort)(x ^ (x >> 2));
			x = (ushort)(x ^ (x >> 1));
			x = (ushort)(x & 1);
			return !(x == (word & 1));//return true flag if problem, false flag if no problem, i.e., returns true flag if "Parity Error Event"
		}

		private void ChannelDrop_SelectedIndexChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "CentroidChannel", ChannelDrop.SelectedIndex.ToString());
			EXTRCN_CHANNEL = ChannelDrop.SelectedIndex + 14;
		}

		private void ExtParityChck_CheckedChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "ExtParityChck", ExtParityChck.Checked);
			ExtOptsMenu.ShowDropDown();
			ExtParityChck.Select();
		}

		private void ExtractListChck_CheckedChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "ExtractListChck", ExtractListChck.Checked);
			ExtOptsMenu.ShowDropDown();
			ExtractListChck.Select();

			if (ExtractListChck.Checked)
				ExtOptsMenu.BackColor = Color.LightGray;
			else
				ExtOptsMenu.BackColor = analysisToolStripMenuItem.BackColor;
		}

		private void centroidListImageCorrectionsToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ExtOptsMenu.ShowDropDown();
			centroidListImageCorrectionsToolStripMenuItem.ShowDropDown();

			if (centroidListImageCorrectionsToolStripMenuItem.Checked)
			{
				if (!GSEApplyDistortionCorrectionChck.Checked)
					GSEApplyDistortionCorrectionChck.PerformClick();
				if (!GSEApplyFPNCorrectionChck.Checked)
					GSEApplyFPNCorrectionChck.PerformClick();
			}
			else
			{
				if (GSEApplyDistortionCorrectionChck.Checked)
					GSEApplyDistortionCorrectionChck.PerformClick();
				if (GSEApplyFPNCorrectionChck.Checked)
					GSEApplyFPNCorrectionChck.PerformClick();
			}

			JPFITS.REG.SetReg("CCDLAB", "centroidListImageCorrect", centroidListImageCorrectionsToolStripMenuItem.Checked);
		}

		private void GSEApplyDistortionCorrectionChck_Click(object sender, EventArgs e)
		{
			ExtOptsMenu.ShowDropDown();
			centroidListImageCorrectionsToolStripMenuItem.ShowDropDown();
			JPFITS.REG.SetReg("CCDLAB", "GSEApplyDist", GSEApplyDistortionCorrectionChck.Checked);

			if (!GSEApplyDistortionCorrectionChck.Checked && !GSEApplyFPNCorrectionChck.Checked)
				centroidListImageCorrectionsToolStripMenuItem.Checked = false;
			if (GSEApplyDistortionCorrectionChck.Checked || GSEApplyFPNCorrectionChck.Checked)
				centroidListImageCorrectionsToolStripMenuItem.Checked = true;
			JPFITS.REG.SetReg("CCDLAB", "centroidListImageCorrect", centroidListImageCorrectionsToolStripMenuItem.Checked);
		}

		private void GSEApplyFPNCorrectionChck_Click(object sender, EventArgs e)
		{
			ExtOptsMenu.ShowDropDown();
			centroidListImageCorrectionsToolStripMenuItem.ShowDropDown();
			JPFITS.REG.SetReg("CCDLAB", "GSEApplyFPN", GSEApplyFPNCorrectionChck.Checked);

			if (!GSEApplyDistortionCorrectionChck.Checked && !GSEApplyFPNCorrectionChck.Checked)
				centroidListImageCorrectionsToolStripMenuItem.Checked = false;
			if (GSEApplyDistortionCorrectionChck.Checked || GSEApplyFPNCorrectionChck.Checked)
				centroidListImageCorrectionsToolStripMenuItem.Checked = true;
			JPFITS.REG.SetReg("CCDLAB", "centroidListImageCorrect", centroidListImageCorrectionsToolStripMenuItem.Checked);
		}

		private void AugFilesChck_CheckedChanged(object sender, EventArgs e)
		{
			JPFITS.REG.SetReg("CCDLAB", "AugFilesChck", AugFilesChck.Checked);
			ExtOptsMenu.ShowDropDown();
			AugFilesChck.Select();
		}

		private void AnalCRCBtn_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you Sure You'd Like to Proceed with CRC Verification?", "Proceed?", MessageBoxButtons.OKCancel) == DialogResult.OK)
			{
				wb = new JPFITS.WaitBar();
				wb.ProgressBar.Maximum = 100;
				wb.Text = "CRC";
				wb.CancelBtn.Text = "Stop";
				CRCWrkr.RunWorkerAsync();
				wb.ShowDialog();
			}
		}

		private void CRCWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			Calc_img_CRC();
		}

		private void CRCWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			int intprog = e.ProgressPercentage;
			if (intprog >= 0)
			{
				int k = (int)e.UserState;
				wb.ProgressBar.Value = intprog;
				wb.TextMsg.Text = string.Concat("Completed: ", intprog.ToString(), "%");
				wb.Text = string.Concat("File ", k + 1, " of ", FULLFILELIST.Length, ": ", intprog.ToString(), "%");
			}
			else if (intprog == -1)
			{
				wb.TextMsg.Text = (string)e.UserState;
			}
			else if (intprog == -2)
			{
				wb.CancelBtn.Enabled = false;
			}
			else if (intprog == -3)
			{
				wb.CancelBtn.Enabled = true;
			}
		}

		private void CRCWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			wb.Close();
		}

		private void Calc_img_CRC()
		{
			int Nfiles = FileListDrop.Items.Count;
			long StartWord = (long)StartWordUpD.Value;
			byte[] arr = new byte[1024 * 1024 * 512];
			try
			{
				for (int k = 0; k < Nfiles; k++)
				{
					FileStream fs = new FileStream(FULLFILELIST[k], FileMode.Open);
					BufferedStream bs = new BufferedStream(fs, 1024 * 1024 * 16);
					CRCWrkr.ReportProgress(-2);
					CRCWrkr.ReportProgress(-1, "Please wait while I read the file from disk...");

					int img_length;
					if (k == 0 && SkipToSgmtChck.Checked)//skip to viewing position...assists in skipping pre-pended data or 2ndry files, manually done
					{
						fs.Position = ((StartWord - 1) * 2);
						img_length = (int)fs.Length - (int)fs.Position;
					}
					else//assume file and param info is fine

					{
						img_length = (int)fs.Length;
					}
					bs.Read(arr, 0, img_length);
					bs.Close();
					fs.Close();
					CRCWrkr.ReportProgress(-3);

					//now check CRC
					int NSegments = img_length / 2048;
					for (int i = 0; i < NSegments; i++)
					{
						if (wb.DialogResult == DialogResult.Cancel)
							continue;//all threads continue to end of omp loop...must be checked first

						ushort crc = Calc_Segment_CRC(arr, i);

						if (crc != (ushort)((arr[i * 2048 + 2046] << 8) + arr[i * 2048 + 2047]))
						{
							MessageBox.Show(string.Concat("Segment: ", i, ".  Recorded CRC: ", ((arr[i * 2048 + 2046] << 8) + arr[i * 2048 + 2047]).ToString(), ".  Calculated CRC: ", crc.ToString()), "CRC Error...");
						}

						//progress bar updating
						if (i * 100 / NSegments > wb.ProgressBar.Value)
							CRCWrkr.ReportProgress(i * 100 / NSegments, k);
					}
					//bool stopped = false;
					if (wb.DialogResult == DialogResult.Cancel)
					{
						//stopped = true;
					}
				}
			}
			catch (Exception e)
			{
				MessageBox.Show(e.Message, "Darn sakes!");
			}
		}

		private ushort Calc_Segment_CRC(byte[] arr, int Segment_Num)
		{
			BitArray D;//data
			BitArray C = new BitArray(16, true);//old (starting) CRC
			BitArray C_new = new BitArray(16, false);//new calculated CRC
			byte[] locbyte = new byte[1];
			byte[] r = new byte[2];//output

			for (int i = 4; i < 2046; i++)//skip 1ACF FC1D synch words and don't compure 1024'th word since that is where CRC goes
			{
				locbyte[0] = arr[Segment_Num * 2048 + i];
				D = new BitArray(locbyte);




				//C.CopyTo(r,0);
				//MessageBox.Show(string.Concat("Segment: ",Segment_Num,".  Byte: ",byte[0],".  Calculated CRC: ",((ushort)( (r[1]<<8) | r[0] )).ToString() ),"Byte-Sequential CRC");

				//for (int t = 0; t < 16; t++)
				//{
				//	MessageBox.Show(C_new[t].ToString(),t.ToString());
				//	MessageBox.Show(C[t].ToString(),t.ToString());
				//}



				C_new[0] = D[4] ^ D[0] ^ C[8] ^ C[12];
				C_new[1] = D[5] ^ D[1] ^ C[9] ^ C[13];
				C_new[2] = D[6] ^ D[2] ^ C[10] ^ C[14];
				C_new[3] = D[7] ^ D[3] ^ C[11] ^ C[15];
				C_new[4] = D[4] ^ C[12];
				C_new[5] = D[5] ^ D[4] ^ D[0] ^ C[8] ^ C[12] ^ C[13];
				C_new[6] = D[6] ^ D[5] ^ D[1] ^ C[9] ^ C[13] ^ C[14];
				C_new[7] = D[7] ^ D[6] ^ D[2] ^ C[10] ^ C[14] ^ C[15];
				C_new[8] = D[7] ^ D[3] ^ C[0] ^ C[11] ^ C[15];
				C_new[9] = D[4] ^ C[1] ^ C[12];
				C_new[10] = D[5] ^ C[2] ^ C[13];
				C_new[11] = D[6] ^ C[3] ^ C[14];
				C_new[12] = D[7] ^ D[4] ^ D[0] ^ C[4] ^ C[8] ^ C[12] ^ C[15];
				C_new[13] = D[5] ^ D[1] ^ C[5] ^ C[9] ^ C[13];
				C_new[14] = D[6] ^ D[2] ^ C[6] ^ C[10] ^ C[14];
				C_new[15] = D[7] ^ D[3] ^ C[7] ^ C[11] ^ C[15];

				//for (int t = 0; t < 16; t++)
				//{
				//	MessageBox.Show(C_new[t].ToString(),t.ToString());
				//	MessageBox.Show(C[t].ToString(),t.ToString());
				//}

				/*C_new[8]  = D[4]^D[0]^C[0]^C[4];
				C_new[9]  = D[5]^D[1]^C[1]^C[5];
				C_new[10]  = D[6]^D[2]^C[2]^C[6];
				C_new[11]  = D[7]^D[3]^C[3]^C[7];
				C_new[12]  = D[4]^C[4];
				C_new[13]  = D[5]^D[4]^D[0]^C[0]^C[4]^C[5];
				C_new[14]  = D[6]^D[5]^D[1]^C[1]^C[5]^C[6];
				C_new[15]  = D[7]^D[6]^D[2]^C[2]^C[6]^C[7];
				C_new[0]  = D[7]^D[3]^C[8]^C[3]^C[7];
				C_new[1]  = D[4]^C[9]^C[4];
				C_new[2] = D[5]^C[10]^C[5];
				C_new[3] = D[6]^C[11]^C[6];
				C_new[4] = D[7]^D[4]^D[0]^C[12]^C[0]^C[4]^C[7];
				C_new[5] = D[5]^D[1]^C[13]^C[1]^C[5];
				C_new[6] = D[6]^D[2]^C[14]^C[2]^C[6];
				C_new[7] = D[7]^D[3]^C[15]^C[3]^C[7];*/

				//C = C_new;
				for (int j = 0; j < 16; j++)
					C.Set(j, C_new[j]);

			}
			C.CopyTo(r, 0);
			return (ushort)((r[1] << 8) | r[0]);
		}

		private void StripBtn_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you'd like to proceed with data file strip and split?", "Proceed?", MessageBoxButtons.OKCancel) != DialogResult.OK)
				return;

			wb = new JPFITS.WaitBar();
			wb.ProgressBar.Maximum = 100;
			wb.Text = "File Split";
			wb.CancelBtn.Text = "Stop";
			StripWrkr.RunWorkerAsync();
			wb.ShowDialog();
		}

		private void StripWrkr_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
		{
			int Nfiles = FULLFILELIST.Length;

			bool FUVinitflag = false;//indicates if channel is present
			bool NUVinitflag = false;
			bool VISinitflag = false;
			int FUVsess = 0;//this is the image session number
			int NUVsess = 0;
			int VISsess = 0;
			int FUVfileNum = 1;//this is the image session file number (increments if file > 500MB)
			int NUVfileNum = 1;
			int VISfileNum = 1;
			int[] FUVchcksum = new int[20];
			int[] NUVchcksum = new int[20];
			int[] VISchcksum = new int[20];
			int[] dummysum = new int[20];
			bool newFUVflag = false;//indicates if new sequence started
			bool newNUVflag = false;
			bool newVISflag = false;
			int Seg_Type = 0;
			int chan = 0;
			int SYNCH1 = 0;
			int SYNCH2 = 0;
			int SYNCHPOS = -2048;
			int Seg_Num;
			FileStream FUV_fs = null;
			FileStream NUV_fs = null;
			FileStream VIS_fs = null;
			//int arr_length = 0;
			long StartWord = (long)StartWordUpD.Value;
			NSplits = 0;
			string fullfile = "";
			string VISpath = "";
			string NUVpath = "";
			string FUVpath = "";
			bool raw_flag = false;
			uint imfrcnt_cur;
			uint VISimfrcnt_prev = UInt32.MaxValue;
			uint NUVimfrcnt_prev = UInt32.MaxValue;
			uint FUVimfrcnt_prev = UInt32.MaxValue;
			uint imfrtime_cur;
			uint VISimfrtime_prev = UInt32.MaxValue;
			uint NUVimfrtime_prev = UInt32.MaxValue;
			uint FUVimfrtime_prev = UInt32.MaxValue;

			try
			{
				for (int k = 0; k < Nfiles; k++)
				{
					if (FULLFILELIST[k].Substring(FULLFILELIST[k].LastIndexOf(".")) == ".raw")
					{
						raw_flag = true;//must write the stripped data even if only one channel..i.e. this was removing the BDH padding
						FUVchcksum = new int[20];
						NUVchcksum = new int[20];
						VISchcksum = new int[20];
					}

					string FileName = FILELIST[k].Substring(0, FILELIST[k].LastIndexOf(".")) + "_";

					FileStream fs = new FileStream(FULLFILELIST[k], FileMode.Open);
					long img_length = fs.Length;
					int N = (int)(img_length / 500 / 1024 / 1024);//number of 500MB segments
					BufferedStream bs = new BufferedStream(fs, 1024 * 1024 * 25);

					long tracker = 0;
					long tracker2 = 0;
					double prog = 0;

					for (int f = 0; f < N + 1; f++)
					{
						StripWrkr.ReportProgress(-1, "Please wait while I read the file from disk...");
						StripWrkr.ReportProgress(-2);//cancel button disabled

						int L = 0;
						if (f == N)
							L = (int)(img_length - (long)(f * 500 * 1024 * 1024));
						else
							L = 500 * 1024 * 1024;

						bs.Read(ARR, 0, L);

						StripWrkr.ReportProgress(-3);//cancel button enabled

						Seg_Num = -1;
						SYNCHPOS = -2048;
						while (SYNCHPOS + 2048 <= L)
						{
							double cprog = (100 * (double)(tracker2 + 2048)) / (double)(img_length);
							if (cprog - prog >= 1)
							{
								prog++;
								StripWrkr.ReportProgress((int)prog, k);
							}
							if (wb.DialogResult == DialogResult.Cancel)
							{
								e.Result = null;
								GC.Collect();
								GC.WaitForFullGCApproach();
								GC.WaitForFullGCComplete();
								GC.WaitForPendingFinalizers();
								wb.Close();
								if (FUVinitflag)
									FUV_fs.Close();
								if (NUVinitflag)
									NUV_fs.Close();
								if (VISinitflag)
									VIS_fs.Close();
								return;
							}

							tracker++;
							Seg_Num++;
							SYNCHPOS += 2048;
							tracker2 += 2048;

							SYNCH1 = (ARR[SYNCHPOS] << 8) | ARR[SYNCHPOS + 1];
							SYNCH2 = (ARR[SYNCHPOS + 2] << 8) | ARR[SYNCHPOS + 3];
							while (SYNCH1 != 0x1ACF && SYNCH2 != 0xFC1D && SYNCHPOS < L - 4)//then not synched...find the sync position
							{
								SYNCHPOS++;
								SYNCH1 = (ARR[SYNCHPOS] << 8) | ARR[SYNCHPOS + 1];
								SYNCH2 = (ARR[SYNCHPOS + 2] << 8) | ARR[SYNCHPOS + 3];
							}
							//shouldn't the above stop at L-4???????????????????????????????????????????????????????????
							//should now be at synch position, i.e. SYNCHPOS is the byte synch position
							if (SYNCHPOS == L - 4)//why ...and shouldn't this be max L-4 or whatever?????????????????????????????
								continue;

							if (SYNCHPOS + 2048 > L)
								continue;

							chan = ARR[SYNCHPOS + 5];//14 = FUV, 15 = NUV, 16 + VIS
							Seg_Type = (((ARR[SYNCHPOS + 6] << 8) | ARR[SYNCHPOS + 7]) & 0xC000) >> 14;
							imfrcnt_cur = (uint)((ARR[SYNCHPOS + 12] << 8) | ARR[SYNCHPOS + 13]);
							imfrtime_cur = (uint)((ARR[SYNCHPOS + 14] << 24) | (ARR[SYNCHPOS + 15] << 16) | (ARR[SYNCHPOS + 16] << 8) | ARR[SYNCHPOS + 17]);

							//MessageBox.Show("Time = " + (imfrtime_cur).ToString() + "; NUVTime = " + NUVimfrtime_prev.ToString());

							if (chan == 14)//FUV
							{
								if (Seg_Type == 1)//then possibly a new image session started, check checksum
								{
									dummysum = ImageParms(ARR, SYNCHPOS);
									if (!CheckSum(FUVchcksum, dummysum) || /*Math.Abs((double)(FUVimfrtime_prev) - (double)(imfrtime_cur)) > 2000*/ Math.Abs((double)(FUVimfrcnt_prev) - (double)(imfrcnt_cur)) > 16)//then it is a new image session
									{
										FUVchcksum = dummysum;
										newFUVflag = true;
										NSplits++;
									}
									FUVimfrcnt_prev = imfrcnt_cur;
									FUVimfrtime_prev = imfrtime_cur;
								}
								if (newFUVflag)
								{
									if (FUVinitflag == true)//then close off existing filestream and initilize a new one, and write this segment to it
										FUV_fs.Close();
									FUVinitflag = true;
									newFUVflag = false;
									FUVsess++;
									FUVfileNum = 1;
									FUVpath = FILEPATH + "\\" + "FUV_" + FUVsess.ToString("0000") + "_" + imfrtime_cur.ToString("0000000000000") + "\\";
									Directory.CreateDirectory(FUVpath);
									fullfile = FUVpath + "\\" + FileName + "FUV_SPLIT_i_" + FUVsess.ToString("0000") + "_q_" + FUVfileNum.ToString("0000") + ".img";
									FUV_fs = new FileStream(fullfile, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite, 1024 * 1024 * 32);
									FUV_fs.Write(ARR, SYNCHPOS, 2048);
								}
								else if (FUVinitflag)//the if will cause skip over prepended data
								{
									FUV_fs.Write(ARR, SYNCHPOS, 2048);
									if (FUV_fs.Length == 1024 * 1024 * 500)//500MB, close off file and start new increment
									{
										FUV_fs.Close();
										FUVfileNum++;
										fullfile = FUVpath + "\\" + FileName + "FUV_SPLIT_i_" + FUVsess.ToString("0000") + "_q_" + FUVfileNum.ToString("0000") + ".img";
										FUV_fs = new FileStream(fullfile, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite, 1024 * 1024 * 32);
									}
								}
							}

							if (chan == 15)//NUV
							{
								if (Seg_Type == 1)//then possibly a new image session started, check checksum
								{
									dummysum = ImageParms(ARR, SYNCHPOS);
									if (!CheckSum(NUVchcksum, dummysum) || /*Math.Abs((double)(NUVimfrtime_prev) - (double)(imfrtime_cur)) > 2000*/ Math.Abs((double)(NUVimfrcnt_prev) - (double)(imfrcnt_cur)) > 16)//then it is a new image session
									{
										NUVchcksum = dummysum;
										newNUVflag = true;
										NSplits++;
									}
									NUVimfrcnt_prev = imfrcnt_cur;
									NUVimfrtime_prev = imfrtime_cur;
								}
								if (newNUVflag)
								{
									if (NUVinitflag == true)//then close off existing filestream and initilize a new one, and write this segment to it
										NUV_fs.Close();
									NUVinitflag = true;
									newNUVflag = false;
									NUVsess++;
									NUVfileNum = 1;
									NUVpath = FILEPATH + "\\" + "NUV_" + NUVsess.ToString("0000") + "_" + imfrtime_cur.ToString("0000000000000") + "\\";
									Directory.CreateDirectory(NUVpath);
									fullfile = NUVpath + FileName + "NUV_SPLIT_i_" + NUVsess.ToString("0000") + "_q_" + NUVfileNum.ToString("0000") + ".img";
									NUV_fs = new FileStream(fullfile, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite, 1024 * 1024 * 32);
									NUV_fs.Write(ARR, SYNCHPOS, 2048);
								}
								else if (NUVinitflag)//the if will cause skip over prepended data
								{
									NUV_fs.Write(ARR, SYNCHPOS, 2048);
									if (NUV_fs.Length == 1024 * 1024 * 500)//500MB, close off file and start new increment
									{
										NUV_fs.Close();
										NUVfileNum++;
										fullfile = NUVpath + "\\" + FileName + "NUV_SPLIT_i_" + NUVsess.ToString("0000") + "_q_" + NUVfileNum.ToString("0000") + ".img";
										NUV_fs = new FileStream(fullfile, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite, 1024 * 1024 * 32);
									}
								}
							}

							if (chan == 16)//VIS
							{
								if (Seg_Type == 1)//then possibly a new image session started, check checksum
								{
									dummysum = ImageParms(ARR, SYNCHPOS);
									if (!CheckSum(VISchcksum, dummysum) || /*Math.Abs((double)(VISimfrtime_prev) - (double)(imfrtime_cur)) > 2000*/ Math.Abs((double)(VISimfrcnt_prev) - (double)(imfrcnt_cur)) > 16)//then it is a new image session
									{
										VISchcksum = dummysum;
										newVISflag = true;
										NSplits++;
									}
									VISimfrcnt_prev = imfrcnt_cur;
									VISimfrtime_prev = imfrtime_cur;
								}
								if (newVISflag)
								{
									if (VISinitflag == true)//then close off existing filestream and initilize a new one, and write this segment to it
										VIS_fs.Close();
									VISinitflag = true;
									newVISflag = false;
									VISsess++;
									VISfileNum = 1;
									VISpath = FILEPATH + "\\" + "VIS_" + VISsess.ToString("0000") + "_" + imfrtime_cur.ToString("0000000000000") + "\\";
									Directory.CreateDirectory(VISpath);
									fullfile = VISpath + FileName + "VIS_SPLIT_i_" + VISsess.ToString("0000") + "_q_" + VISfileNum.ToString("0000") + ".img";
									VIS_fs = new FileStream(fullfile, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite, 1024 * 1024 * 32);
									VIS_fs.Write(ARR, SYNCHPOS, 2048);
								}
								else if (VISinitflag)//the if will cause skip over prepended data
								{
									VIS_fs.Write(ARR, SYNCHPOS, 2048);
									if (VIS_fs.Length == 1024 * 1024 * 500)//500MB, close off file and start new increment
									{
										VIS_fs.Close();
										VISfileNum++;
										fullfile = VISpath + FileName + "VIS_SPLIT_i_" + VISsess.ToString("0000") + "_q_" + VISfileNum.ToString("0000") + ".img";
										VIS_fs = new FileStream(fullfile, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite, 1024 * 1024 * 32);
									}
								}
							}
						}
					}
					bs.Close();
					fs.Close();
				}//end of files is done, so may have file streams to close off

				if (FUVinitflag == true)
					FUV_fs.Close();
				if (NUVinitflag == true)
					NUV_fs.Close();
				if (VISinitflag == true)
					VIS_fs.Close();

				if (!(raw_flag || FUVsess > 1 || NUVsess > 1 || VISsess > 1 || FUVinitflag && NUVinitflag || FUVinitflag && VISinitflag || NUVinitflag && VISinitflag))//then no split needed
				{
					MessageBox.Show("No splitting was needed!");
					File.Delete(fullfile);
					wb.DialogResult = DialogResult.Abort;
				}
			}
			catch (Exception ee)
			{
				if (FUVinitflag == true)
					FUV_fs.Close();
				if (NUVinitflag == true)
					NUV_fs.Close();
				if (VISinitflag == true)
					VIS_fs.Close();
				MessageBox.Show(string.Concat(ee.Message, ":  ", ee.Data, ":  ", ee.StackTrace, "  ", ee.Source, "  ", ee.TargetSite));
			}
		}

		private void StripWrkr_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
		{
			int intprog = e.ProgressPercentage;
			if (intprog >= 0)
			{
				int k = (int)e.UserState;
				wb.ProgressBar.Value = intprog;
				wb.TextMsg.Text = string.Concat("Completed: ", intprog.ToString(), "%");
				wb.Text = string.Concat("File ", k + 1, " of ", FULLFILELIST.Length, ": ", intprog.ToString(), "%");
			}
			else if (intprog == -1)
			{
				wb.TextMsg.Text = (string)e.UserState;
			}
			else if (intprog == -2)
			{
				wb.CancelBtn.Enabled = false;
			}
			else if (intprog == -3)
			{
				wb.CancelBtn.Enabled = true;
			}
		}

		private void StripWrkr_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
		{
			if (wb.DialogResult == DialogResult.Cancel)
				MessageBox.Show("Cancelled splitting files.  Files may have been split & written up to this point...");
			else if (wb.DialogResult == DialogResult.Abort)
			{
			}
			else
				MessageBox.Show(NSplits.ToString() + " unique image sessions split out.  Finished.");
			wb.Close();

			if (ISAC_Chunked)
			{
				MessageBox.Show("test");
				ISAC_Chunked = false;

				FULLFILELIST = new string[1] { orignonchunkfile };
				FILELIST = new string[1];
				int j = FULLFILELIST[0].LastIndexOf("\\");
				FILELIST[0] = FULLFILELIST[0].Substring(j + 1);
				FILEPATH = FULLFILELIST[0].Substring(0, j + 1);
				FileListDrop.Items.Clear();
				FileListDrop.Items.AddRange(FILELIST);
				FileListDrop.SelectedIndex = 0;

				for (int i = 0; i < delete_chunks.Length; i++)
					File.Delete(delete_chunks[i]);
			}
		}

		private int[] ImageParms(byte[] arr, int POSTN)
		{
			int sum = 0;

			int[] checksum = new int[20];

			//row gaptime
			sum += (int)((((arr[POSTN + 26] << 8) | arr[POSTN + 27]) & 0x1FF));
			checksum[0] = (int)((((arr[POSTN + 26] << 8) | arr[POSTN + 27]) & 0x1FF));
			//MessageBox.Show(checksum[0].ToString());

			//gain
			sum += (int)((((arr[POSTN + 28] << 8) | arr[POSTN + 29]) & 0x3));
			checksum[1] = (int)((((arr[POSTN + 28] << 8) | arr[POSTN + 29]) & 0x3));

			//reset bias
			sum += (int)((((arr[POSTN + 30] << 8) | arr[POSTN + 31]) & 0xFFF));
			checksum[2] = (int)((((arr[POSTN + 30] << 8) | arr[POSTN + 31]) & 0xFFF));

			//x offset
			sum += (int)((((arr[POSTN + 32] << 8) | arr[POSTN + 33]) & 0x1FF));
			checksum[3] = (int)((((arr[POSTN + 32] << 8) | arr[POSTN + 33]) & 0x1FF));
			//MessageBox.Show(checksum[3].ToString());

			//y offset
			sum += (int)((((arr[POSTN + 34] << 8) | arr[POSTN + 35]) & 0x1FF));
			checksum[4] = (int)((((arr[POSTN + 34] << 8) | arr[POSTN + 35]) & 0x1FF));
			//MessageBox.Show(checksum[4].ToString());

			//x size
			sum += (int)((((arr[POSTN + 36] << 8) | arr[POSTN + 37]) & 0x1FF));
			checksum[5] = (int)((((arr[POSTN + 36] << 8) | arr[POSTN + 37]) & 0x1FF));
			//MessageBox.Show(checksum[5].ToString());

			//y size
			sum += (int)((((arr[POSTN + 38] << 8) | arr[POSTN + 39]) & 0x1FF));
			checksum[6] = (int)((((arr[POSTN + 38] << 8) | arr[POSTN + 39]) & 0x1FF));
			//MessageBox.Show(checksum[6].ToString());

			//timing master
			sum += (int)((((arr[POSTN + 40] << 8) | arr[POSTN + 41]) & 0x3F));
			checksum[7] = (int)((((arr[POSTN + 40] << 8) | arr[POSTN + 41]) & 0x3F));

			//centroid bits
			sum += (int)((((arr[POSTN + 42] << 8) | arr[POSTN + 43]) & 0xFF));
			checksum[8] = (int)((((arr[POSTN + 42] << 8) | arr[POSTN + 43]) & 0xFF));

			//stacking and normalization
			sum += (int)((((arr[POSTN + 44] << 8) | arr[POSTN + 45]) & 0x3F));
			checksum[9] = (int)((((arr[POSTN + 44] << 8) | arr[POSTN + 45]) & 0x3F));

			//ramp time
			sum += (int)((((arr[POSTN + 46] << 8) | arr[POSTN + 47]) & 0xFFF));
			checksum[10] = (int)((((arr[POSTN + 46] << 8) | arr[POSTN + 47]) & 0xFFF));

			//event threshold
			sum += (int)((((arr[POSTN + 48] << 8) | arr[POSTN + 49]) & 0x3FFF));
			checksum[11] = (int)((((arr[POSTN + 48] << 8) | arr[POSTN + 49]) & 0x3FFF));

			//event energy
			sum += (int)((((arr[POSTN + 50] << 8) | arr[POSTN + 51]) & 0x3FFF));
			checksum[12] = (int)((((arr[POSTN + 50] << 8) | arr[POSTN + 51]) & 0x3FFF));

			//BOD length
			sum += (int)((((arr[POSTN + 52] << 8) | arr[POSTN + 53]) & 0xFFFF));
			checksum[13] = (int)((((arr[POSTN + 52] << 8) | arr[POSTN + 53]) & 0xFFFF));

			//BOD height
			sum += (int)((((arr[POSTN + 54] << 8) | arr[POSTN + 55]) & 0xFFFF));
			checksum[14] = (int)((((arr[POSTN + 54] << 8) | arr[POSTN + 55]) & 0xFFFF));

			//BOD frames
			sum += (int)((((arr[POSTN + 56] << 8) | arr[POSTN + 57]) & 0xFFFF));
			checksum[15] = (int)((((arr[POSTN + 56] << 8) | arr[POSTN + 57]) & 0xFFFF));

			//Anode V
			sum += (int)((((arr[POSTN + 58] << 8) | arr[POSTN + 59]) & 0xFFF));
			checksum[16] = (int)((((arr[POSTN + 58] << 8) | arr[POSTN + 59]) & 0xFFF));

			//MCP V
			sum += (int)((((arr[POSTN + 60] << 8) | arr[POSTN + 61]) & 0xFFF));
			checksum[17] = (int)((((arr[POSTN + 60] << 8) | arr[POSTN + 61]) & 0xFFF));

			//PC V
			sum += (int)((((arr[POSTN + 62] << 8) | arr[POSTN + 63]) & 0xFFF));
			checksum[18] = (int)((((arr[POSTN + 62] << 8) | arr[POSTN + 63]) & 0xFFF));

			//HVU OC
			sum += (int)((((arr[POSTN + 68] << 8) | arr[POSTN + 69]) & 0xFFF));
			checksum[19] = (int)((((arr[POSTN + 68] << 8) | arr[POSTN + 69]) & 0xFFF));

			return checksum;
		}

		private bool CheckSum(int[] arr1, int[] arr2)
		{
			bool test = true;

			for (int i = 0; i < arr1.Length; i++)
				if (arr1[i] != arr2[i])
				{
					test = false;
					return test;
				}
			return test;
		}

		private void OBTvsUVITClocksMenuItem_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = false;
			ofd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath");
			ofd.Filter = "L0-RAW File (*.raw)|*.raw";
			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;
			JPFITS.REG.SetReg("CCDLAB", "GSEOpenFilesPath", ofd.FileName.Substring(0, ofd.FileName.LastIndexOf("\\")));


			FileStream fs = new FileStream(ofd.FileName, FileMode.Open);
			int img_length = 1024 * 1024 * 500;
			if (fs.Length < img_length)
				img_length = (int)fs.Length;
			fs.Read(ARR, 0, img_length);
			fs.Close();

			int LOC = -1;
			int SYNCH1 = 0;
			int SYNCH2 = 0;
			int initSYNCHcount = 0;

			//scan to 2nd sync
			while (initSYNCHcount < 2)
			{
				LOC++;
				SYNCH1 = ((ARR[LOC]) << 8) | ARR[LOC + 1];
				SYNCH2 = ((ARR[LOC + 2]) << 8) | ARR[LOC + 3];

				if (SYNCH1 == 0x1ACF && SYNCH2 == 0xFC1D)
					initSYNCHcount++;
			}
			//so now at 2nd synch at byte number LOC

			int nDIFEPsegments = (img_length - LOC) / 2160;

			double[,] result = new double[5, nDIFEPsegments];

			uint OBTTME = 0;//can't do 64 bit shift anyway below
			ushort FRMCNT = 0;
			uint FRMTME = 0;
			uint TCKTME = 0;
			uint TCKCNT = 0;

			for (int i = 0; i < nDIFEPsegments; i++)
			{
				OBTTME = /*((ARR[LOC - 16])<<40) + ((ARR[LOC - 15])<<32) +*/ (uint)((ARR[LOC - 14] << 24) | (ARR[LOC - 13] << 16) | (ARR[LOC - 12] << 8) | ARR[LOC - 11]);
				FRMCNT = (ushort)((ARR[LOC + 12] << 8) | ARR[LOC + 13]);
				FRMTME = (uint)((ARR[LOC + 14] << 24) | (ARR[LOC + 15] << 16) | (ARR[LOC + 16] << 8) | ARR[LOC + 17]);
				TCKTME = (uint)((ARR[LOC + 18] << 24) | (ARR[LOC + 19] << 16) | (ARR[LOC + 20] << 8) | ARR[LOC + 21]);
				TCKCNT = (uint)((ARR[LOC + 22] << 24) | (ARR[LOC + 23] << 16) | (ARR[LOC + 24] << 8) | ARR[LOC + 25]);

				LOC += 2160;

				result[0, i] = OBTTME;
				result[1, i] = FRMCNT;
				result[2, i] = FRMTME;
				result[3, i] = TCKTME;
				result[4, i] = TCKCNT;
			}

			SaveFileDialog sfd = new SaveFileDialog();
			sfd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath");
			sfd.Filter = "FITS File (*.fits)|*.fits";
			if (sfd.ShowDialog() == DialogResult.Cancel)
				return;

			JPFITS.FITSImage f = new JPFITS.FITSImage(sfd.FileName, result, false, true);
			f.Header.AddKey("COL1", "OBT TIME", "", -1);
			f.Header.AddKey("COL2", "FRAME COUNT", "", -1);
			f.Header.AddKey("COL3", "FRAME TIME", "", -1);
			f.Header.AddKey("COL4", "TICK TIME", "", -1);
			f.Header.AddKey("COL5", "TICK COUNT", "", -1);

			f.WriteImage(TypeCode.Double, true);

			JPFITS.REG.SetReg("CCDLAB", "OpenFilesPath", JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath"));


		}

		private void FixBadTimesHighValuesChck_Click(object sender, System.EventArgs e)
		{
			if (FixBadTimesHighValuesChck.Checked)
				FixBadTimesLowValuesChck.Checked = false;
			else
				FixBadTimesLowValuesChck.Checked = true;

			JPFITS.REG.SetReg("CCDLAB", "FixBadTimesHigh", FixBadTimesHighValuesChck.Checked);
			JPFITS.REG.SetReg("CCDLAB", "FixBadTimesLow", FixBadTimesLowValuesChck.Checked);

			analysisToolStripMenuItem.ShowDropDown();
			FixBadTimeListsMenuItem.ShowDropDown();
		}

		private void FixBadTimesLowValuesChck_Click(object sender, System.EventArgs e)
		{
			if (FixBadTimesLowValuesChck.Checked)
				FixBadTimesHighValuesChck.Checked = false;
			else
				FixBadTimesHighValuesChck.Checked = true;

			JPFITS.REG.SetReg("CCDLAB", "FixBadTimesHigh", FixBadTimesHighValuesChck.Checked);
			JPFITS.REG.SetReg("CCDLAB", "FixBadTimesLow", FixBadTimesLowValuesChck.Checked);

			analysisToolStripMenuItem.ShowDropDown();
			FixBadTimeListsMenuItem.ShowDropDown();
		}

		private void FixBadTimeListsMenuItem_Click(object sender, System.EventArgs e)
		{
			analysisToolStripMenuItem.HideDropDown();
			FixBadTimeListsMenuItem.HideDropDown();

		reget:
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.InitialDirectory = (string)JPFITS.REG.GetReg("CCDLAB", "GSEOpenFilesPath");
			ofd.Multiselect = true;
			ofd.Title = "Please select the TimeList file(s)...";
			ofd.Filter = "FITS File (*.fits)|*.fits";

			if (ofd.ShowDialog() == DialogResult.Cancel)
				return;

			for (int i = 0; i < ofd.FileNames.Length; i++)
				if (!ofd.FileNames[i].Contains("TimeList"))
				{
					MessageBox.Show("Looks like you didn't select the TimeList file(s)...Exiting", "Error");
					goto reget;
				}

			bool maxvalues = FixBadTimesHighValuesChck.Checked;

			for (int i = 0; i < ofd.FileNames.Length; i++)
			{
				JPFITS.FITSImage oldtimefits = new JPFITS.FITSImage(ofd.FileNames[i], null, true, false, false, true);
				double[] times = JPFITS.FITSImage.ReadImageVectorOnly(ofd.FileNames[i], null, true);
				double[] frames = JPFITS.FITSImage.ReadImageVectorOnly(ofd.FileNames[i].Replace("TimeList", "FrameList"), null, true);

				//this assume that the good times are the higher values...could put it an option for if the good times were the lower values
				double starttime;
				double endtime;
				int startind, endin;
				if (maxvalues)
				{
					starttime = JPFITS.JPMath.Max(times, 0, times.Length / 20, out startind, false);
					endtime = JPFITS.JPMath.Max(times, times.Length - times.Length / 20, times.Length - 1, out endin, false);
				}
				else
				{
					starttime = JPFITS.JPMath.Min(times, 0, times.Length / 20, out startind, false);
					endtime = JPFITS.JPMath.Min(times, times.Length - times.Length / 20, times.Length - 1, out endin, false);
				}

				double startframe = frames[startind];
				double endframe = frames[endin];

				double timeperframe = (endtime - starttime) / (endframe - startframe);

				//#pragma omp parallel for
				for (int j = 0; j < times.Length; j++)
					times[j] = (frames[j] - startframe) * timeperframe + starttime;

				JPFITS.FITSImage newtimefits = new JPFITS.FITSImage(ofd.FileNames[i], times, false, true);
				newtimefits.Header.CopyHeaderFrom(oldtimefits.Header);// CopyHeader(oldtimefits);
				newtimefits.WriteImage(TypeCode.UInt32, true);
			}

			MessageBox.Show("Complete...");
		}

	}
}
