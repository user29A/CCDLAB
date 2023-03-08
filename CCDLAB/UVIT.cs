using System;
using System.IO;
using System.ComponentModel;
using System.Collections;
using System.Windows.Forms;


namespace CCDLAB
{
	public class UVIT
	{
		private int BG;                     //scalar background to subtract from algorithms
		private int MIN_PIXEL;              //minimum threshold of single pixel for centroiding candidate
		private int MAX_PIXEL;              //maximum threshold of single pixel for centroiding candidate	
		private int MIN_SHAPE;              //minimum threshold of total pixel signal within algorithm shape for central pixel centroiding candidate	
		private int MAX_SHAPE;              //maximum threshold of total pixel signal within algorithm shape for central pixel centroiding candidate	
		private int CENTROID_PRECISION;     //1 = pixel, 2 = 1/2 pixel (i.e.,2x2 = 1 pixel), 3 = 1/3 pixel, etc
		private int[] RANGE;       //this is the ZERO BASED centroiding range on the raw 512x512 image	RANGE[0,0] = xstart, RANGE[1,0] = xend, RANGE[0,1] = ystart, RANGE[1,1] = yend,
		private string[] FULL_FILE_LIST;        //list of full path/file names of files
		private string[] FILE_LIST;         //list of only file names of files
		private int NUM_FILES;
		private int CURRENT_FILE;
		private bool[] ALGTYPES;

		//Will need to use array collections when building centroid arrays, then convert them to these regular arrays
		private double[,] TBTC_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. TBTC = three by three cross.
		private double[,] TBTQ_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. TBTQ = three by three quadratic - now Gaussian
		private double[,] TBTS_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. TBTS = three by three square.
		private double[,] FBFC_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. FBFC = five by five cross.
		private double[,] FBFS_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. FBFS = five by five square.

		//the following are the built-up images of the centroid events, will be 512x512 * CENTROID_PREICISION2 in size
		// i.e., CENTROID_PRECISION = 8 gives 4096x4096 image
		//Return functions
		private uint[,] TBTC_IMAGE;   //type = 0
		private uint[,] TBTS_IMAGE;   //type = 1
		private uint[,] TBTQ_IMAGE;   //type = 2
		private uint[,] FBFC_IMAGE;   //type = 3
		private uint[,] FBFS_IMAGE;   //type = 4

		public int Number_of_Files
		{
			get { return NUM_FILES; }
		}

		public int Current_File_Number//ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			get { return CURRENT_FILE; }
			set
			{
				if (value > NUM_FILES)
				{
					CURRENT_FILE = 1;               //ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}
				else if (value < 1)
				{
					CURRENT_FILE = NUM_FILES;       //ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}
				else
				{
					CURRENT_FILE = value;     //ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}
			}
		}

		public int Min_Thresh
		{
			get { return MIN_PIXEL; }
			set { MIN_PIXEL = value; }
		}

		public int Max_Thresh
		{
			get { return MAX_PIXEL; }
			set { MAX_PIXEL = value; }
		}

		public int Min_Energy
		{
			get { return MIN_SHAPE; }
			set { MIN_SHAPE = value; }
		}

		public int Max_Energy
		{
			get { return MAX_SHAPE; }
			set { MAX_SHAPE = value; }
		}

		public int Precision
		{
			get { return CENTROID_PRECISION; }
			set
			{
				if (value > 64)
				{
					CENTROID_PRECISION = 64;
				}
				else if (value < 0)
				{
					CENTROID_PRECISION = 0;
				}
				else
					CENTROID_PRECISION = value;
			}
		}

		public string[] Full_File_List
		{
			get { return FULL_FILE_LIST; }
		}

		public string[] File_List
		{
			get { return FILE_LIST; }
		}

		public double[,] TBTC_Centroids
		{
			get { return TBTC_CENTROIDS; }
		}

		public double[,] TBTQ_Centroids
		{
			get { return TBTQ_CENTROIDS; }
		}

		public double[,] TBTS_Centroids
		{
			get { return TBTS_CENTROIDS; }
		}

		public double[,] FBFC_Centroids
		{
			get { return FBFC_CENTROIDS; }
		}

		public double[,] FBFS_Centroids
		{
			get { return FBFS_CENTROIDS; }
		}

		public uint[,] TBTC_Image//see below
		{
			get { return TBTC_IMAGE; }
		}

		public uint[,] TBTS_Image//see below
		{
			get { return TBTS_IMAGE; }
		}

		public uint[,] TBTQ_Image//see below
		{
			get { return TBTQ_IMAGE; }
		}

		public uint[,] FBFC_Image//see below
		{
			get { return FBFC_IMAGE; }
		}

		public uint[,] FBFS_Image//see below
		{
			get { return FBFS_IMAGE; }
		}

		public int[] Range
		{
			get { return RANGE; }
			set { RANGE = value; }
		}

		public bool[] AlgorithmTypes//see below
		{
			get { return ALGTYPES; }
		}

		public UVIT(string[] FullFileList)
		{
			FULL_FILE_LIST = FullFileList;
			FILE_LIST = new string[FullFileList.Length];
			NUM_FILES = FullFileList.Length;
			CURRENT_FILE = 1;
			int index;
			string fullfile;
			for (int i = 0; i < FullFileList.Length; i++)
			{
				fullfile = FullFileList[i];
				index = fullfile.LastIndexOf("\\");
				FILE_LIST[i] = fullfile.Substring(index + 1);
			}
		}

		public string[] Open_CentroidFile(string FullPathName)
		{
			CENTROID_PRECISION = 1;
			RANGE = new int[4];
			string[] res = new string[12];
			FileStream fs = new FileStream(FullPathName, FileMode.Open, FileAccess.Read);
			StreamReader sr = new StreamReader(fs);
			string str;
			int ind, ind2, ind3, ind4, ind5, ind6;

			//get type
			str = sr.ReadLine();
			res[0] = str.Substring(str.LastIndexOf("	") + 1);

			//get x range
			str = sr.ReadLine();
			ind2 = str.LastIndexOf("	");
			ind = (str.Substring(0, ind2)).LastIndexOf("	");
			res[1] = str.Substring(ind + 1, ind2 - ind - 1);
			RANGE[0] = Convert.ToInt32(res[1]);
			res[2] = str.Substring(ind2 + 1);
			RANGE[1] = Convert.ToInt32(res[2]);

			//get y range
			str = sr.ReadLine();
			ind2 = str.LastIndexOf("	");
			ind = (str.Substring(0, ind2)).LastIndexOf("	");
			res[3] = str.Substring(ind + 1, ind2 - ind - 1);
			RANGE[2] = Convert.ToInt32(res[3]);
			res[4] = str.Substring(ind2 + 1);
			RANGE[3] = Convert.ToInt32(res[4]);

			//get min pixel thresh
			str = sr.ReadLine();
			res[5] = str.Substring(str.LastIndexOf("	") + 1);

			//get max pixel thresh
			str = sr.ReadLine();
			res[6] = str.Substring(str.LastIndexOf("	") + 1);

			//get min shape thresh
			str = sr.ReadLine();
			res[7] = str.Substring(str.LastIndexOf("	") + 1);

			//get max shape thresh
			str = sr.ReadLine();
			res[8] = str.Substring(str.LastIndexOf("	") + 1);

			//get background
			str = sr.ReadLine();
			res[9] = str.Substring(str.LastIndexOf("	") + 1);//might be either a scalar number or name of a file

			//get number of frames
			str = sr.ReadLine();
			res[10] = str.Substring(str.LastIndexOf("	") + 1);

			//get number of centroids
			str = sr.ReadLine();
			res[11] = str.Substring(str.LastIndexOf("	") + 1);

			str = sr.ReadLine();
			str = sr.ReadLine();//last 2 lines not needed

			int N = Convert.ToInt32(res[11]);

			if (res[0] == "3x3_Cross")
			{
				TBTC_CENTROIDS = new double[7, N];
				for (int i = 0; i < N; i++)//for 3x3 Cross
				{
					str = sr.ReadLine();
					ind = str.IndexOf('	');
					TBTC_CENTROIDS[0, i] = Convert.ToDouble(str.Substring(0, ind));
					ind2 = str.IndexOf('	', ind + 1);
					TBTC_CENTROIDS[1, i] = Convert.ToDouble(str.Substring(ind + 1, ind2 - ind - 1));
					ind3 = str.IndexOf('	', ind2 + 1);
					TBTC_CENTROIDS[2, i] = Convert.ToDouble(str.Substring(ind2 + 1, ind3 - ind2 - 1));
					ind4 = str.IndexOf('	', ind3 + 1);
					TBTC_CENTROIDS[3, i] = Convert.ToDouble(str.Substring(ind3 + 1, ind4 - ind3 - 1));
					ind5 = str.IndexOf('	', ind4 + 1);
					TBTC_CENTROIDS[4, i] = Convert.ToDouble(str.Substring(ind4 + 1, ind5 - ind4 - 1));
					ind6 = str.IndexOf('	', ind5 + 1);
					TBTC_CENTROIDS[5, i] = Convert.ToDouble(str.Substring(ind5 + 1, ind6 - ind5 - 1));
					TBTC_CENTROIDS[6, i] = Convert.ToDouble(str.Substring(ind6 + 1));
				}
			}
			if (res[0] == "3x3_Square")
			{
				TBTS_CENTROIDS = new double[7, N];
				for (int i = 0; i < N; i++)//for 3x3 Cross
				{
					str = sr.ReadLine();
					ind = str.IndexOf('	');
					TBTS_CENTROIDS[0, i] = Convert.ToDouble(str.Substring(0, ind));
					ind2 = str.IndexOf('	', ind + 1);
					TBTS_CENTROIDS[1, i] = Convert.ToDouble(str.Substring(ind + 1, ind2 - ind - 1));
					ind3 = str.IndexOf('	', ind2 + 1);
					TBTS_CENTROIDS[2, i] = Convert.ToDouble(str.Substring(ind2 + 1, ind3 - ind2 - 1));
					ind4 = str.IndexOf('	', ind3 + 1);
					TBTS_CENTROIDS[3, i] = Convert.ToDouble(str.Substring(ind3 + 1, ind4 - ind3 - 1));
					ind5 = str.IndexOf('	', ind4 + 1);
					TBTS_CENTROIDS[4, i] = Convert.ToDouble(str.Substring(ind4 + 1, ind5 - ind4 - 1));
					ind6 = str.IndexOf('	', ind5 + 1);
					TBTS_CENTROIDS[5, i] = Convert.ToDouble(str.Substring(ind5 + 1, ind6 - ind5 - 1));
					TBTS_CENTROIDS[6, i] = Convert.ToDouble(str.Substring(ind6 + 1));
				}
			}
			if (res[0] == "3x3_Gaussian")
			{
				TBTQ_CENTROIDS = new double[7, N];
				for (int i = 0; i < N; i++)//for 3x3 Cross
				{
					str = sr.ReadLine();
					ind = str.IndexOf('	');
					TBTQ_CENTROIDS[0, i] = Convert.ToDouble(str.Substring(0, ind));
					ind2 = str.IndexOf('	', ind + 1);
					TBTQ_CENTROIDS[1, i] = Convert.ToDouble(str.Substring(ind + 1, ind2 - ind - 1));
					ind3 = str.IndexOf('	', ind2 + 1);
					TBTQ_CENTROIDS[2, i] = Convert.ToDouble(str.Substring(ind2 + 1, ind3 - ind2 - 1));
					ind4 = str.IndexOf('	', ind3 + 1);
					TBTQ_CENTROIDS[3, i] = Convert.ToDouble(str.Substring(ind3 + 1, ind4 - ind3 - 1));
					ind5 = str.IndexOf('	', ind4 + 1);
					TBTQ_CENTROIDS[4, i] = Convert.ToDouble(str.Substring(ind4 + 1, ind5 - ind4 - 1));
					ind6 = str.IndexOf('	', ind5 + 1);
					TBTQ_CENTROIDS[5, i] = Convert.ToDouble(str.Substring(ind5 + 1, ind6 - ind5 - 1));
					TBTQ_CENTROIDS[6, i] = Convert.ToDouble(str.Substring(ind6 + 1));
				}
			}
			if (res[0] == "5x5_Cross")
			{
				FBFC_CENTROIDS = new double[7, N];
				for (int i = 0; i < N; i++)//for 3x3 Cross
				{
					str = sr.ReadLine();
					ind = str.IndexOf('	');
					FBFC_CENTROIDS[0, i] = Convert.ToDouble(str.Substring(0, ind));
					ind2 = str.IndexOf('	', ind + 1);
					FBFC_CENTROIDS[1, i] = Convert.ToDouble(str.Substring(ind + 1, ind2 - ind - 1));
					ind3 = str.IndexOf('	', ind2 + 1);
					FBFC_CENTROIDS[2, i] = Convert.ToDouble(str.Substring(ind2 + 1, ind3 - ind2 - 1));
					ind4 = str.IndexOf('	', ind3 + 1);
					FBFC_CENTROIDS[3, i] = Convert.ToDouble(str.Substring(ind3 + 1, ind4 - ind3 - 1));
					ind5 = str.IndexOf('	', ind4 + 1);
					FBFC_CENTROIDS[4, i] = Convert.ToDouble(str.Substring(ind4 + 1, ind5 - ind4 - 1));
					ind6 = str.IndexOf('	', ind5 + 1);
					FBFC_CENTROIDS[5, i] = Convert.ToDouble(str.Substring(ind5 + 1, ind6 - ind5 - 1));
					FBFC_CENTROIDS[6, i] = Convert.ToDouble(str.Substring(ind6 + 1));
				}
			}
			if (res[0] == "5x5_Square")
			{
				FBFS_CENTROIDS = new double[7, N];
				for (int i = 0; i < N; i++)//for 3x3 Cross
				{
					str = sr.ReadLine();
					ind = str.IndexOf('	');
					FBFS_CENTROIDS[0, i] = Convert.ToDouble(str.Substring(0, ind));
					ind2 = str.IndexOf('	', ind + 1);
					FBFS_CENTROIDS[1, i] = Convert.ToDouble(str.Substring(ind + 1, ind2 - ind - 1));
					ind3 = str.IndexOf('	', ind2 + 1);
					FBFS_CENTROIDS[2, i] = Convert.ToDouble(str.Substring(ind2 + 1, ind3 - ind2 - 1));
					ind4 = str.IndexOf('	', ind3 + 1);
					FBFS_CENTROIDS[3, i] = Convert.ToDouble(str.Substring(ind3 + 1, ind4 - ind3 - 1));
					ind5 = str.IndexOf('	', ind4 + 1);
					FBFS_CENTROIDS[4, i] = Convert.ToDouble(str.Substring(ind4 + 1, ind5 - ind4 - 1));
					ind6 = str.IndexOf('	', ind5 + 1);
					FBFS_CENTROIDS[5, i] = Convert.ToDouble(str.Substring(ind5 + 1, ind6 - ind5 - 1));
					FBFS_CENTROIDS[6, i] = Convert.ToDouble(str.Substring(ind6 + 1));
				}
			}

			sr.Close();
			fs.Close();
			return res;
		}

		public uint[,] Get_Image(string type)
		{
			double CP = (double)CENTROID_PRECISION;
			if (CP < 1)
			{
				CP = 1;
			}
			uint[,] image = new uint[(RANGE[1] - RANGE[0] + 1) * (int)CP, (RANGE[3] - RANGE[2] + 1) * (int)CP];
			if (type == "3x3_Cross")
			{
				for (int i = 0; i < TBTC_CENTROIDS.GetLength(1); i++)
				{
					try
					{
						image[(int)(((TBTC_CENTROIDS[0, i] + 0.5) * CP)), (int)(((TBTC_CENTROIDS[1, i] + 0.5) * CP))]++;
					}
					catch (System.IndexOutOfRangeException)
					{
						/*CCDLAB.NotifyDlg note = new CCDLAB.NotifyDlg();
						note.NotifyTxt.Text = String.Concat("3x3 Cross:      ","X = ",((TBTC_CENTROIDS[0,i]+0.5)*CP).ToString(),";      Y = ",((TBTC_CENTROIDS[1,i]+0.5)*CP).ToString(),"      Centroid # ",i);
						note.ShowDialog();*/
					}
				}
			}
			if (type == "3x3_Square")
			{
				for (int i = 0; i < TBTS_CENTROIDS.GetLength(1); i++)
				{
					try
					{
						image[(int)(((TBTS_CENTROIDS[0, i] + 0.5) * CP)), (int)(((TBTS_CENTROIDS[1, i] + 0.5) * CP))]++;
					}
					catch (System.IndexOutOfRangeException)
					{
						/*CCDLAB.NotifyDlg note = new CCDLAB.NotifyDlg();
						note.NotifyTxt.Text = String.Concat("3x3 Square:      ","X = ",((TBTS_CENTROIDS[0,i]+0.5)*CP).ToString(),";      Y = ",((TBTS_CENTROIDS[1,i]+0.5)*CP).ToString(),"      Centroid # ",i);
						note.ShowDialog();*/
					}
				}
			}
			if (type == "3x3_Gaussian")
			{
				for (int i = 0; i < TBTQ_CENTROIDS.GetLength(1); i++)
				{
					image[(int)(((TBTQ_CENTROIDS[0, i] + 0.5) * CP)), (int)(((TBTQ_CENTROIDS[1, i] + 0.5) * CP))]++;
				}
			}
			if (type == "5x5_Cross")
			{
				for (int i = 0; i < FBFC_CENTROIDS.GetLength(1); i++)
				{
					image[(int)(((FBFC_CENTROIDS[0, i] + 0.5) * CP)), (int)(((FBFC_CENTROIDS[1, i] + 0.5) * CP))]++;
				}
			}
			if (type == "5x5_Square")
			{
				try
				{
					for (int i = 0; i < FBFS_CENTROIDS.GetLength(1); i++)
					{
						image[(int)(((FBFS_CENTROIDS[0, i] + 0.5) * CP)), (int)(((FBFS_CENTROIDS[1, i] + 0.5) * CP))]++;
					}
				}
				catch (System.IndexOutOfRangeException)
				{
					/*CCDLAB.NotifyDlg note = new CCDLAB.NotifyDlg();
					note.NotifyTxt.Text = String.Concat("5x5 Square:      ","X = ",((FBFS_CENTROIDS[0,i]+0.5)*CP).ToString(),";      Y = ",((FBFS_CENTROIDS[1,i]+0.5)*CP).ToString(),"      Centroid # ",i);
					note.ShowDialog();*/
				}
			}
			return image;
		}

		public uint[,] Get_FromOnlyImageMode(string type)
		{
			if (type == "3x3_Cross")
			{
				return TBTC_IMAGE;
			}
			else if (type == "3x3_Square")
			{
				return TBTS_IMAGE;
			}
			else if (type == "3x3_Gaussian")
			{
				return TBTQ_IMAGE;
			}
			else if (type == "5x5_Cross")
			{
				return FBFC_IMAGE;
			}
			else if (type == "5x5_Square")
			{
				return FBFS_IMAGE;
			}
			else
				return null;
		}

		public void Save_Centroids(String FullPathName, String type, String arraybgname, bool activeBG)
		{
			FileStream fs = new FileStream(FullPathName, FileMode.Create, FileAccess.ReadWrite);
			StreamWriter sw = new StreamWriter(fs);
			string str;
			sw.WriteLine(String.Concat("Algorithm Type:			", type));
			sw.WriteLine(String.Concat("RANGE_X:			", RANGE[0], "	", RANGE[1]));
			sw.WriteLine(String.Concat("RANGE_Y:			", RANGE[2], "	", RANGE[3]));
			sw.WriteLine(String.Concat("Min Pixel Thresh:		", MIN_PIXEL));
			sw.WriteLine(String.Concat("Max Pixel Thresh:		", MAX_PIXEL));
			sw.WriteLine(String.Concat("Min Shape Thresh:		", MIN_SHAPE));
			sw.WriteLine(String.Concat("Max Shape Thresh:		", MAX_SHAPE));
			if (activeBG)
				sw.WriteLine(String.Concat("Background:			", "Min 5x5 Corner"));
			else if (arraybgname == "NA")
				sw.WriteLine(String.Concat("Background:			", BG));
			else
				sw.WriteLine(String.Concat("Background:			", arraybgname));
			sw.WriteLine(String.Concat("NFrames:			", FULL_FILE_LIST.Length));

			if (type == "3x3_Cross")
			{
				sw.WriteLine(String.Concat("Total Number of Centroids:	", TBTC_CENTROIDS.GetLength(1)));
				sw.WriteLine(String.Concat("Column 1 = X; ", "Column 2 = Y; ", "Column 3 = Pixel Energy; ", "Column 4 = Shape Energy; ", "Column 5 = Min Corner; ", "Column 6 = Corner Max-Min; ", "Column 7 = Frame#"));
				sw.WriteLine();
				for (int i = 0; i < TBTC_CENTROIDS.GetLength(1); i++)
				{
					str = String.Concat((TBTC_CENTROIDS[0, i].ToString("N6")), "	", (TBTC_CENTROIDS[1, i].ToString("N6")), "	", TBTC_CENTROIDS[2, i], "	", TBTC_CENTROIDS[3, i], "	", TBTC_CENTROIDS[4, i], "	", TBTC_CENTROIDS[5, i], "	", TBTC_CENTROIDS[6, i]);
					sw.WriteLine(str);
				}
			}
			if (type == "3x3_Square")
			{
				sw.WriteLine(String.Concat("Total Number of Centroids:	", TBTS_CENTROIDS.GetLength(1)));
				sw.WriteLine(String.Concat("Column 1 = X; ", "Column 2 = Y; ", "Column 3 = Pixel Energy; ", "Column 4 = Shape Energy; ", "Column 5 = Min Corner; ", "Column 6 = Corner Max-Min; ", "Column 7 = Frame#"));
				sw.WriteLine();
				for (int i = 0; i < TBTS_CENTROIDS.GetLength(1); i++)
				{
					str = String.Concat((TBTS_CENTROIDS[0, i].ToString("N6")), "	", (TBTS_CENTROIDS[1, i].ToString("N6")), "	", TBTS_CENTROIDS[2, i], "	", TBTS_CENTROIDS[3, i], "	", TBTS_CENTROIDS[4, i], "	", TBTS_CENTROIDS[5, i], "	", TBTS_CENTROIDS[6, i]);
					sw.WriteLine(str);
				}
			}
			if (type == "3x3_Gaussian")
			{
				sw.WriteLine(String.Concat("Total Number of Centroids:	", TBTQ_CENTROIDS.GetLength(1)));
				sw.WriteLine(String.Concat("Column 1 = X; ", "Column 2 = Y; ", "Column 3 = Pixel Energy; ", "Column 4 = Shape Energy; ", "Column 5 = Min Corner; ", "Column 6 = Corner Max-Min; ", "Column 7 = Frame#"));
				sw.WriteLine();
				for (int i = 0; i < TBTQ_CENTROIDS.GetLength(1); i++)
				{
					str = String.Concat((TBTQ_CENTROIDS[0, i].ToString("N6")), "	", (TBTQ_CENTROIDS[1, i].ToString("N6")), "	", TBTQ_CENTROIDS[2, i], "	", TBTQ_CENTROIDS[3, i], "	", TBTQ_CENTROIDS[4, i], "	", TBTQ_CENTROIDS[5, i], "	", TBTQ_CENTROIDS[6, i]);
					sw.WriteLine(str);
				}
			}
			if (type == "5x5_Cross")
			{
				sw.WriteLine(String.Concat("Total Number of Centroids:	", FBFC_CENTROIDS.GetLength(1)));
				sw.WriteLine(String.Concat("Column 1 = X; ", "Column 2 = Y; ", "Column 3 = Pixel Energy; ", "Column 4 = Shape Energy; ", "Column 5 = Min Corner; ", "Column 6 = Corner Max-Min; ", "Column 7 = Frame#"));
				sw.WriteLine();
				for (int i = 0; i < FBFC_CENTROIDS.GetLength(1); i++)
				{
					str = String.Concat((FBFC_CENTROIDS[0, i].ToString("N6")), "	", (FBFC_CENTROIDS[1, i].ToString("N6")), "	", FBFC_CENTROIDS[2, i], "	", FBFC_CENTROIDS[3, i], "	", FBFC_CENTROIDS[4, i], "	", FBFC_CENTROIDS[5, i], "	", FBFC_CENTROIDS[6, i]);
					sw.WriteLine(str);
				}
			}
			if (type == "5x5_Square")
			{
				sw.WriteLine(String.Concat("Total Number of Centroids:	", FBFS_CENTROIDS.GetLength(1)));
				sw.WriteLine(String.Concat("Column 1 = X; ", "Column 2 = Y; ", "Column 3 = Pixel Energy; ", "Column 4 = Shape Energy; ", "Column 5 = Min Corner; ", "Column 6 = Corner Max-Min; ", "Column 7 = Frame#"));
				sw.WriteLine();
				for (int i = 0; i < FBFS_CENTROIDS.GetLength(1); i++)
				{
					str = String.Concat((FBFS_CENTROIDS[0, i].ToString("N6")), "	", (FBFS_CENTROIDS[1, i].ToString("N6")), "	", FBFS_CENTROIDS[2, i], "	", FBFS_CENTROIDS[3, i], "	", FBFS_CENTROIDS[4, i], "	", FBFS_CENTROIDS[5, i], "	", FBFS_CENTROIDS[6, i]);
					sw.WriteLine(str);
				}
			}

			sw.Flush();
			fs.Flush();
			sw.Close();
			fs.Close();
		}

		public bool Centroid(int Precision, int[] Range, int MinPixel, int MaxPixel, int MinShape, int MaxShape, int ScalarBackGround, bool[] AlgTypes, ushort[,] ArrayBackGround, BackgroundWorker worker, bool imageonly, bool ActiveBG, int CornerThresh, double BGOffset, JPFITS.WaitBar wb)
		{
			CENTROID_PRECISION = Precision;
			RANGE = Range;
			MIN_PIXEL = MinPixel;
			MAX_PIXEL = MaxPixel;
			MIN_SHAPE = MinShape;
			MAX_SHAPE = MaxShape;
			BG = ScalarBackGround;
			ALGTYPES = AlgTypes;

			//these are the array lists for the centroid data
			ArrayList tbtc = new ArrayList();
			ArrayList tbts = new ArrayList();
			ArrayList tbtq = new ArrayList();
			ArrayList fbfc = new ArrayList();
			ArrayList fbfs = new ArrayList();

			//imageonly = true;
			if (imageonly == true)//then just keep the array lists as above...they wont be and arent taking any memory, but need to initialize image arrays
			{
				InitImages(AlgTypes);
			}

			int intprog = 0;
			int prog = -1;
			bool cancel = false;

			//omp'ing the full frame disk reads is the best performance booster...actually it helps for any size frame read
			for (int n = 0; n < NUM_FILES; n++)
			{
				int nthreads = 1;
				if (wb.DialogResult == DialogResult.Cancel)
				{
					cancel = true;
					goto cancel_centroid;
				}
				if (n < (int)NUM_FILES / nthreads)//keep the update of progress bar to only one thread of the team...avoids locks
				{
					intprog = n * 100 * nthreads / NUM_FILES;
					if (intprog - prog > 1)//keep the update of progress bar to only one thread of the team...avoids locks
					{
						prog++;
						worker.ReportProgress(intprog);
					}
				}

				double[,] raw;
				double ix, fx, iy, fy, Dx, Dy;
				double fcmin = 0;
				double fcmax = 0;
				double pixval = 0;
				double shape = 0;

				raw = JPFITS.FITSImage.ReadImageArrayOnly(FULL_FILE_LIST[n], RANGE, true);

				for (int i = 2; i < raw.GetLength(0) - 2; i++)
				{
					for (int j = 2; j < raw.GetLength(1) - 2; j++)//loops automatically do the rastering, inside the bounds at 5x5
					{
						pixval = raw[i, j];//pixel value

						fcmin = 0.0;
						fcmax = 0.0;
						shape = 0.0;

						if (ActiveBG == true)
						{
							fcmin = Double.MaxValue;
							if (raw[i - 2, j - 2] < fcmin)
								fcmin = raw[i - 2, j - 2];
							if (raw[i - 2, j + 2] < fcmin)
								fcmin = raw[i - 2, j + 2];
							if (raw[i + 2, j - 2] < fcmin)
								fcmin = raw[i + 2, j - 2];
							if (raw[i + 2, j + 2] < fcmin)
								fcmin = raw[i + 2, j + 2];

							//and also do corner max check for adjacent events
							fcmax = Double.MinValue;
							if (raw[i - 2, j - 2] > fcmax)
								fcmax = raw[i - 2, j - 2];
							if (raw[i - 2, j + 2] > fcmax)
								fcmax = raw[i - 2, j + 2];
							if (raw[i + 2, j - 2] > fcmax)
								fcmax = raw[i + 2, j - 2];
							if (raw[i + 2, j + 2] > fcmax)
								fcmax = raw[i + 2, j + 2];

							// do corner threshold check for ActiveBG case
							if ((fcmax - fcmin) > CornerThresh)
								goto next100;//skip over all algorithms if not inside theshold

						}

						//check pixel threshold using amplitude of event;
						//for ActiveBG case fcmin has been determined
						//for non-ActiveBG case pixval is from raw image which has been "loaded" with background correction already applied, and fcmin = 0;
						if (pixval - fcmin < MIN_PIXEL || pixval - fcmin > MAX_PIXEL)
						{
							goto next100;//skip over all algorithms if pixel not inside theshold
						}

						if (AlgTypes[0] || AlgTypes[2])// this is 3x3 Cross & 3x3 Gaussian (using cross).  
						{
							//singular max check within shape
							if (pixval <= (raw[i - 1, j]) || pixval <= (raw[i + 1, j]) || pixval <= (raw[i, j - 1]) || pixval <= (raw[i, j + 1]))
							{
								goto next02;//skip out these two algorithms only
							}

							//energy threshold check
							shape = raw[i - 1, j] + raw[i, j] + raw[i + 1, j] + raw[i, j - 1] + raw[i, j + 1] - 5 * (fcmin);//fcmin default 0 if not ActiveBG
							if (shape < MIN_SHAPE || shape > MAX_SHAPE)//Sum energy check
							{
								goto next02;//skip out these two algorithms only
							}

							if (AlgTypes[0])//3x3 Cross
							{
								//fcmin and BGOffset default 0 if not being used
								ix = (double)(i);
								iy = (double)(j);
								fx = ((raw[i + 1, j] - raw[i - 1, j])) / ((raw[i - 1, j] + raw[i, j] + raw[i + 1, j] - 3 * (fcmin + BGOffset)));
								fy = ((raw[i, j + 1] - raw[i, j - 1])) / ((raw[i, j - 1] + raw[i, j] + raw[i, j + 1] - 3 * (fcmin + BGOffset)));

								Dx = ix + fx;
								Dy = iy + fy;

								//#pragma omp critical
								{
									if (imageonly == false)
									{
										tbtc.Add((Dx));
										tbtc.Add((Dy));
										tbtc.Add(pixval - fcmin);
										tbtc.Add(shape);
										tbtc.Add(fcmin);
										tbtc.Add(fcmax - fcmin);
										tbtc.Add(n);
									}
									else
									{
										try
										{
											TBTC_IMAGE[(int)((Dx + 0.5) * (double)(CENTROID_PRECISION)), (int)((Dy + 0.5) * (double)(CENTROID_PRECISION))]++;
										}
										catch (System.IndexOutOfRangeException)//usually only happens when thresholds set extremely low
										{
										}
									}
								}
							}

							if (AlgTypes[2])//3x3 gaussian
							{
								//check for zeros to assist logarithm; if non-ActiveBG fcmin = 0
								if (raw[i - 1, j] - (int)(fcmin + BGOffset) < 1)
									raw[i - 1, j] = (int)(fcmin + BGOffset) + 1;
								if (raw[i + 1, j] - (int)(fcmin + BGOffset) < 1)
									raw[i + 1, j] = (int)(fcmin + BGOffset) + 1;
								if (raw[i, j + 1] - (int)(fcmin + BGOffset) < 1)
									raw[i, j + 1] = (int)(fcmin + BGOffset) + 1;
								if (raw[i, j - 1] - (int)(fcmin + BGOffset) < 1)
									raw[i, j - 1] = (int)(fcmin + BGOffset) + 1;

								Dx = (double)(i) + (Math.Log(raw[i + 1, j] - (int)(fcmin + BGOffset)) - Math.Log(raw[i - 1, j] - (int)(fcmin + BGOffset))) / (2 * (2 * Math.Log(raw[i, j] - (int)(fcmin + BGOffset)) - Math.Log(raw[i - 1, j] - (int)(fcmin + BGOffset)) - Math.Log(raw[i + 1, j] - (int)(fcmin + BGOffset))));
								Dy = (double)(j) + (Math.Log(raw[i, j + 1] - (int)(fcmin + BGOffset)) - Math.Log(raw[i, j - 1] - (int)(fcmin + BGOffset))) / (2 * (2 * Math.Log(raw[i, j] - (int)(fcmin + BGOffset)) - Math.Log(raw[i, j - 1] - (int)(fcmin + BGOffset)) - Math.Log(raw[i, j + 1] - (int)(fcmin + BGOffset))));

								//#pragma omp critical
								{
									if (imageonly == false)
									{
										tbtq.Add((Dx));
										tbtq.Add((Dy));
										tbtq.Add(pixval - fcmin);
										tbtq.Add(shape);
										tbtq.Add(fcmin);
										tbtq.Add(fcmax - fcmin);
										tbtq.Add(n);
									}
									else
									{
										TBTQ_IMAGE[(int)((Dx + 0.5) * (double)(CENTROID_PRECISION)), (int)((Dy + 0.5) * (double)(CENTROID_PRECISION))]++;
									}
								}
							}
						next02:;////jump out point for non-singular maximum shape within the 3x3 cross shape
						}

						if (AlgTypes[1])//this is 3x3 Square
						{
							double[,] tbtv = new double[3, 3];//TBT values

							//make 3x3 arrays of pixel values and pixel position
							raw[i, j] -= 1;//so that this doesnt compare to itelf and cause a singular maximum test failure
							int iii = -1;
							for (int ii = i - 1; ii <= i + 1; ii++)
							{
								iii++; int jjj = -1;
								for (int jj = j - 1; jj <= j + 1; jj++)
								{
									jjj++;
									if (raw[ii, jj] >= pixval)
									{
										raw[i, j] += 1;
										goto next1;//singular max check
												   //if the value isn't the singular maximum in the square, then skip this pixel and keep going
									}
									tbtv[iii, jjj] = (raw[ii, jj]);
								}
							}
							raw[i, j] += 1;
							tbtv[1, 1] = raw[i, j];

							shape = JPFITS.JPMath.Sum(JPFITS.JPMath.MatrixSubScalar(tbtv, fcmin, false), false);
							if (shape < MIN_SHAPE || shape > MAX_SHAPE)//Sum energy check
							{
								goto next1;//skip out this algorithms only
							}

							//subtract background from array; fcmin = 0 for non-ActiveBG
							tbtv = JPFITS.JPMath.MatrixSubScalar(tbtv, fcmin + BGOffset, false);//subtract 4 corner min from entire array
																								//Array should now be set so background = -BGOffset

							ix = (double)(i);
							iy = (double)(j);
							fx = (tbtv[2, 0] - tbtv[0, 0] + tbtv[2, 1] - tbtv[0, 1] + tbtv[2, 2] - tbtv[0, 2]) / JPFITS.JPMath.Sum(tbtv, false);
							fy = (tbtv[0, 2] - tbtv[0, 0] + tbtv[1, 2] - tbtv[1, 0] + tbtv[2, 2] - tbtv[2, 0]) / JPFITS.JPMath.Sum(tbtv, false);

							Dx = ix + fx;
							Dy = iy + fy;

							//#pragma omp critical
							{
								if (imageonly == false)
								{
									tbts.Add((Dx));
									tbts.Add((Dy));
									tbts.Add(pixval - fcmin);
									tbts.Add(shape);
									tbts.Add(fcmin);
									tbts.Add(fcmax - fcmin);
									tbts.Add(n);
								}
								else
								{
									try
									{
										TBTS_IMAGE[(int)((Dx + 0.5) * (double)(CENTROID_PRECISION)), (int)((Dy + 0.5) * (double)(CENTROID_PRECISION))]++;
									}
									catch (System.IndexOutOfRangeException)//usuall only happens when thresholds set extremely low
									{
									}
								}
							}
						next1:;//jump out point for non-singular maximum shape for 3x3 square shape
						}

						if (AlgTypes[3])// this is 5x5 Cross
						{
							//singular max check within shape
							if (pixval <= (raw[i - 1, j]) || pixval <= (raw[i + 1, j]) || pixval <= (raw[i, j - 1]) || pixval <= (raw[i, j + 1]) ||
								pixval <= (raw[i - 2, j]) || pixval <= (raw[i + 2, j]) || pixval <= (raw[i, j - 2]) || pixval <= (raw[i, j + 2]))
							{
								goto next000003;//skip out 5cross
							}

							//energy threshold check
							shape = raw[i - 1, j] + raw[i + 1, j] + raw[i, j - 1] + raw[i, j + 1] + raw[i - 2, j] + raw[i + 2, j] + raw[i, j - 2] + raw[i, j + 2] + raw[i, j] - 9 * (fcmin);
							if (shape < MIN_SHAPE || shape > MAX_SHAPE)//Sum energy check
							{
								goto next000003;//skip out 5cross
							}


							ix = (double)(i);
							iy = (double)(j);
							fx = ((2 * raw[i + 2, j] + raw[i + 1, j] - raw[i - 1, j] - 2 * raw[i - 2, j])) / ((raw[i - 2, j] + raw[i - 1, j] + raw[i, j] + raw[i + 1, j] + raw[i + 2, j] - 5 * (fcmin + BGOffset)));
							fy = ((2 * raw[i, j + 2] + raw[i, j + 1] - raw[i, j - 1] - 2 * raw[i, j - 2])) / ((raw[i, j - 2] + raw[i, j - 1] + raw[i, j] + raw[i, j + 1] + raw[i, j + 2] - 5 * (fcmin + BGOffset)));

							Dx = ix + fx;
							Dy = iy + fy;

							//#pragma omp critical
							{
								if (imageonly == false)
								{
									fbfc.Add((Dx));
									fbfc.Add((Dy));
									fbfc.Add(pixval - fcmin);
									fbfc.Add(shape);
									fbfc.Add(fcmin);
									fbfc.Add(fcmax - fcmin);
									fbfc.Add(n);
								}
								else
								{
									try
									{
										FBFC_IMAGE[(int)((Dx + 0.5) * (double)(CENTROID_PRECISION)), (int)((Dy + 0.5) * (double)(CENTROID_PRECISION))]++;
									}
									catch (System.IndexOutOfRangeException)//usually only happens when thresholds set extremely low
									{
									}
								}
							}
						next000003:;
						}

						if (AlgTypes[4]) //this is 5x5 Square
						{
							double[,] fbfv2 = new double[5, 5];//FBF values

							//make 5x5 arrays of pixel values and pixel position
							raw[i, j] -= 1;//so that this doesnt compare to itelf and cause a singular maximum test failure
							int iii = -1;
							for (int ii = i - 2; ii <= i + 2; ii++)
							{
								iii++; int jjj = -1;
								for (int jj = j - 2; jj <= j + 2; jj++)
								{
									jjj++;
									if (raw[ii, jj] >= pixval)
									{
										raw[i, j] += 1;
										goto next5;
										//singular max check, if the value isn't the singular maximum in the square, then skip this pixel and keep going
									}
									fbfv2[iii, jjj] = (raw[ii, jj]);
								}
							}
							raw[i, j] += 1;
							fbfv2[2, 2] = raw[i, j];

							shape = JPFITS.JPMath.Sum(JPFITS.JPMath.MatrixSubScalar(fbfv2, fcmin, false), false);
							if (shape < MIN_SHAPE || shape > MAX_SHAPE)//Sum energy check
							{
								goto next5;//skip out this algorithms only
							}

							fbfv2 = JPFITS.JPMath.MatrixSubScalar(fbfv2, fcmin + BGOffset, false);//subtract 4 corner min from entire array
																								  //Array should now be set so background = -BGOffset

							ix = (double)(i);
							iy = (double)(j);
							fx = (fbfv2[3, 0] + 2 * fbfv2[4, 0] + fbfv2[3, 1] + 2 * fbfv2[4, 1] + fbfv2[3, 2] + 2 * fbfv2[4, 2] + fbfv2[3, 3] + 2 * fbfv2[4, 3] + fbfv2[3, 4] + 2 * fbfv2[4, 4] - (2 * fbfv2[0, 0] + fbfv2[1, 0] + 2 * fbfv2[0, 1] + fbfv2[1, 1] + 2 * fbfv2[0, 2] + fbfv2[1, 2] + 2 * fbfv2[0, 3] + fbfv2[1, 3] + 2 * fbfv2[0, 4] + fbfv2[1, 4])) / JPFITS.JPMath.Sum(fbfv2, false);
							fy = (fbfv2[0, 3] + 2 * fbfv2[0, 4] + fbfv2[1, 3] + 2 * fbfv2[1, 4] + fbfv2[2, 3] + 2 * fbfv2[2, 4] + fbfv2[3, 3] + 2 * fbfv2[3, 4] + fbfv2[4, 3] + 2 * fbfv2[4, 4] - (2 * fbfv2[0, 0] + fbfv2[0, 1] + 2 * fbfv2[1, 0] + fbfv2[1, 1] + 2 * fbfv2[2, 0] + fbfv2[2, 1] + 2 * fbfv2[3, 0] + fbfv2[3, 1] + 2 * fbfv2[4, 0] + fbfv2[4, 1])) / JPFITS.JPMath.Sum(fbfv2, false);

							Dx = ix + fx;
							Dy = iy + fy;

							//#pragma omp critical
							{
								if (imageonly == false)
								{
									fbfs.Add((Dx));
									fbfs.Add((Dy));
									fbfs.Add(pixval - fcmin);
									fbfs.Add(shape); fbfs.Add(fcmin);
									fbfs.Add(fcmax - fcmin);
									fbfs.Add(n);
								}
								else
								{
									try
									{
										FBFS_IMAGE[(int)((Dx + 0.5) * (double)(CENTROID_PRECISION)), (int)((Dy + 0.5) * (double)(CENTROID_PRECISION))]++;
									}
									catch (System.IndexOutOfRangeException)//usuall only happens when thresholds set extremely low
									{
									}
								}
							}
						next5:;
						}
					next100:;
					}
				}
			cancel_centroid:;
			}
			if (cancel == true)
				return !cancel;//return false if cancelled (!cancel = false since cancel = true here)

			//for loop is done going through all images, now must put centroid data into class vectors

			int N;
			N = tbtc.Count / 7;//the array list length
			if (N > 0)
			{
				TBTC_CENTROIDS = new double[7, N];
				
				for (int i = 0; i < N; i++)
				{
					TBTC_CENTROIDS[0, i] = Convert.ToDouble(tbtc[i * 7]);
					TBTC_CENTROIDS[1, i] = Convert.ToDouble(tbtc[i * 7 + 1]);
					TBTC_CENTROIDS[2, i] = Convert.ToDouble(tbtc[i * 7 + 2]);
					TBTC_CENTROIDS[3, i] = Convert.ToDouble(tbtc[i * 7 + 3]);
					TBTC_CENTROIDS[4, i] = Convert.ToDouble(tbtc[i * 7 + 4]);
					TBTC_CENTROIDS[5, i] = Convert.ToDouble(tbtc[i * 7 + 5]);
					TBTC_CENTROIDS[6, i] = Convert.ToDouble(tbtc[i * 7 + 6]);
				}
				tbtc.Clear();
			}
			else
			{
				TBTC_CENTROIDS = null;
			}

			N = tbts.Count / 7;//the array list length
			if (N > 0)
			{
				TBTS_CENTROIDS = new double[7, N];
				
				for (int i = 0; i < N; i++)
				{
					TBTS_CENTROIDS[0, i] = Convert.ToDouble(tbts[i * 7]);
					TBTS_CENTROIDS[1, i] = Convert.ToDouble(tbts[i * 7 + 1]);
					TBTS_CENTROIDS[2, i] = Convert.ToDouble(tbts[i * 7 + 2]);
					TBTS_CENTROIDS[3, i] = Convert.ToDouble(tbts[i * 7 + 3]);
					TBTS_CENTROIDS[4, i] = Convert.ToDouble(tbts[i * 7 + 4]);
					TBTS_CENTROIDS[5, i] = Convert.ToDouble(tbts[i * 7 + 5]);
					TBTS_CENTROIDS[6, i] = Convert.ToDouble(tbts[i * 7 + 6]);
				}
				tbts.Clear();
			}
			else
			{
				TBTS_CENTROIDS = null;
			}

			N = tbtq.Count / 7;//the array list length
			if (N > 0)
			{
				TBTQ_CENTROIDS = new double[7, N];
				
				for (int i = 0; i < N; i++)
				{
					TBTQ_CENTROIDS[0, i] = Convert.ToDouble(tbtq[i * 7]);
					TBTQ_CENTROIDS[1, i] = Convert.ToDouble(tbtq[i * 7 + 1]);
					TBTQ_CENTROIDS[2, i] = Convert.ToDouble(tbtq[i * 7 + 2]);
					TBTQ_CENTROIDS[3, i] = Convert.ToDouble(tbtq[i * 7 + 3]);
					TBTQ_CENTROIDS[4, i] = Convert.ToDouble(tbtq[i * 7 + 4]);
					TBTQ_CENTROIDS[5, i] = Convert.ToDouble(tbtq[i * 7 + 5]);
					TBTQ_CENTROIDS[6, i] = Convert.ToDouble(tbtq[i * 7 + 6]);
				}
				tbtq.Clear();
			}
			else
			{
				TBTQ_CENTROIDS = null;
			}

			N = fbfc.Count / 7;//the array list length
			if (N > 0)
			{
				FBFC_CENTROIDS = new double[7, N];
				
				for (int i = 0; i < N; i++)
				{
					FBFC_CENTROIDS[0, i] = Convert.ToDouble(fbfc[i * 7]);
					FBFC_CENTROIDS[1, i] = Convert.ToDouble(fbfc[i * 7 + 1]);
					FBFC_CENTROIDS[2, i] = Convert.ToDouble(fbfc[i * 7 + 2]);
					FBFC_CENTROIDS[3, i] = Convert.ToDouble(fbfc[i * 7 + 3]);
					FBFC_CENTROIDS[4, i] = Convert.ToDouble(fbfc[i * 7 + 4]);
					FBFC_CENTROIDS[5, i] = Convert.ToDouble(fbfc[i * 7 + 5]);
					FBFC_CENTROIDS[6, i] = Convert.ToDouble(fbfc[i * 7 + 6]);
				}
				fbfc.Clear(); fbfc.TrimToSize();
			}
			else
			{
				FBFC_CENTROIDS = null;
			}

			N = fbfs.Count / 7;//the array list length
			if (N > 0)
			{
				FBFS_CENTROIDS = new double[7, N];
				
				for (int i = 0; i < N; i++)
				{
					FBFS_CENTROIDS[0, i] = Convert.ToDouble(fbfs[i * 7]);
					FBFS_CENTROIDS[1, i] = Convert.ToDouble(fbfs[i * 7 + 1]);
					FBFS_CENTROIDS[2, i] = Convert.ToDouble(fbfs[i * 7 + 2]);
					FBFS_CENTROIDS[3, i] = Convert.ToDouble(fbfs[i * 7 + 3]);
					FBFS_CENTROIDS[4, i] = Convert.ToDouble(fbfs[i * 7 + 4]);
					FBFS_CENTROIDS[5, i] = Convert.ToDouble(fbfs[i * 7 + 5]);
					FBFS_CENTROIDS[6, i] = Convert.ToDouble(fbfs[i * 7 + 6]);
				}
				fbfs.Clear();
			}
			else
			{
				FBFS_CENTROIDS = null;
			}
			return !cancel;//return true if finished (!cancel will = true, since cancel will be false here)
		}

		public double[,] Read_Raw_File(int filenum, int BackGround)
		{
			int[,] result = new int[512, 512];
			FileStream fs = new FileStream(FULL_FILE_LIST[filenum], FileMode.Open, FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			for (int i = 0; i < 512; i++)
			{
				for (int j = 0; j < 512; j++)
				{
					result[j, i] = br.ReadUInt16() - BackGround;
				}
			}
			br.Close();
			fs.Close();
			return null;
		}

		public double[,] Read_Raw_File(int filenum, int BackGround, int[,] Range /*Range is ZERO based!*/)
		{
			FileStream fs = new FileStream(FULL_FILE_LIST[filenum], FileMode.Open, FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			int W = Range[1, 0] - Range[0, 0] + 1;
			int H = Range[1, 1] - Range[0, 1] + 1;
			int[,] result = new int[W, H];
			br.BaseStream.Seek(((Range[0, 1]) * 512 * 2 + (Range[0, 0]) * 2), SeekOrigin.Begin);
			for (int i = 0; i < H; i++)
			{
				for (int j = 0; j < W; j++)
				{
					result[j, i] = br.ReadUInt16() - BackGround;
				}
				br.BaseStream.Seek((512 - Range[1, 0] + Range[0, 0] - 1) * 2, SeekOrigin.Current);
			}
			br.Close();
			fs.Close();
			return null;
		}

		public double[,] Read_Raw_File(int filenum, int[,] ArrayBackGround)
		{
			int[,] result = new int[512, 512];
			FileStream fs = new FileStream(FULL_FILE_LIST[filenum], FileMode.Open, FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			for (int i = 0; i < 512; i++)
			{
				for (int j = 0; j < 512; j++)
				{
					result[j, i] = br.ReadUInt16() - ArrayBackGround[j, i];
				}
			}
			br.Close();
			fs.Close();
			return null;
		}

		public double[,] Read_Raw_File(int filenum, int[,] ArrayBackGround, int[,] Range /*Range is ZERO based!*/)
		{
			FileStream fs = new FileStream(FULL_FILE_LIST[filenum], FileMode.Open, FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			int W = Range[1, 0] - Range[0, 0] + 1;
			int H = Range[1, 1] - Range[0, 1] + 1;
			int[,] result = new int[W, H];
			br.BaseStream.Seek(((Range[0, 1]) * 512 * 2 + (Range[0, 0]) * 2), SeekOrigin.Begin);
			for (int i = 0; i < H; i++)
			{
				for (int j = 0; j < W; j++)
				{
					result[j, i] = br.ReadUInt16() - ArrayBackGround[Range[0, 0] + j, Range[0, 1] + i];
				}
				br.BaseStream.Seek((512 - Range[1, 0] + Range[0, 0] - 1) * 2, SeekOrigin.Current);
			}
			br.Close();
			fs.Close();
			return null;
		}

		public void InitImages(bool[] types)
		{
			int CP = CENTROID_PRECISION;
			if (types[0] == true)
			{
				TBTC_IMAGE = new uint[(RANGE[1] - RANGE[0] + 1) * CP, (RANGE[3] - RANGE[2] + 1) * CP];
			}
			if (types[1] == true)
			{
				TBTS_IMAGE = new uint[(RANGE[1] - RANGE[0] + 1) * CP, (RANGE[3] - RANGE[2] + 1) * CP];
			}
			if (types[2] == true)
			{
				TBTQ_IMAGE = new uint[(RANGE[1] - RANGE[0] + 1) * CP, (RANGE[3] - RANGE[2] + 1) * CP];
			}
			if (types[3] == true)
			{
				FBFC_IMAGE = new uint[(RANGE[1] - RANGE[0] + 1) * CP, (RANGE[3] - RANGE[2] + 1) * CP];
			}
			if (types[4] == true)
			{
				FBFS_IMAGE = new uint[(RANGE[1] - RANGE[0] + 1) * CP, (RANGE[3] - RANGE[2] + 1) * CP];
			}
		}
	}
}
