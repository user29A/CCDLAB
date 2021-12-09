using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;
using JPFITS;

namespace CCDLAB
{
	public partial class Form1 : Form
	{
		#region PROGRAM VARIABLES
		static public string CCDLABPATH = "C:\\ProgramData\\Astrowerks\\CCDLAB\\";
		public FITSImageSet IMAGESET;// = new FITSImageSet();
		int FILELISTINDEX, OLD_INDEX;//image index for the FileListDrop
		bool IWLCK;     //Image Window Left (mouse) Clicks
		bool SHOWIMGTOOLTIP = false;
		int[] SUBRANGE;
		int[] PADDING;
		int[] CROPPING;
		bool LOADSUBRANGE;
		double[,] SUBIMAGE;
		double SUBIMAGESUM, SUBIMAGEMIN, SUBIMAGEMAX, SUBIMAGEMEAN, SUBIMAGEMEDIAN, SUBIMAGESTD;
		int[] XSUBRANGE;
		int[] YSUBRANGE;
		int XPOS_CURSOR, YPOS_CURSOR, PRVXPOS_CURSOR, PRVYPOS_CURSOR;//zero based position in image window(s)
		double XPOS_CURSOR_RADEG, YPOS_CURSOR_DECDEG;//WCS position in image window(s)
		string XPOS_CURSOR_RAHMS;
		string YPOS_CURSOR_DECDMS;//WCS position in image window(s)
		int SUBIMAGE_HWX, SUBIMAGE_HWY, SUBIMAGE_HWX_OLD, SUBIMAGE_HWY_OLD, ROIX0, ROIY0, ROIXRad, ROIYRad, SUBIMAGEX0OLD, SUBIMAGEY0OLD;
		double[] DIMCLIM;// min/max contrast limits
		double[] IMSTDLIM;
		double CTSperPERCENT;
		int PREVMINCONTRASTVALUE, PREVMAXCONTRASTVALUE;
		int[] FNDCOORDS_X;
		int[] FNDCOORDS_Y;
		Rectangle[] FNDCOORDRECTS;
		double[,] MARKCOORDS;
		Rectangle[] MARKCOORDRECTS;
		JPMath.PointD[] MARKCOORDRECTDPTS;
		bool FIRSTLOAD;
		Bitmap SUBIMAGEBMP;
		public Bitmap IMAGEBMP;
		UVIT UVIT_Data;
		ushort[,] UVBGArray;
		string NORMKEY;

		PointSourceExtractor[] PSES;
		int PSESINDEX = -1;
		Rectangle[][] PSESRECTS;
		Color[] PSERECTCOLOURS;
		bool PSESPLOTALL = false;
		int PSECOUNT = 0;
		bool PSEDRAWGROUPREGIONS = false;

		TypeCode FILESAVEPREC;
		Graphics IMAGEWINDOWGRFX;
		Pen IMAGEWINDOWPEN;
		SolidBrush IMAGEWINDOWBRUSH = new SolidBrush(Color.Red);
		string[] BATCHLIST;
		FITSImage BATCHMULTIMG;
		FITSImage BATCHBIASIMG;
		FITSImage BATCHFLATIMG;
		FITSImage BATCHADDIMG;
		int BATCHVIEWINDEX;
		System.DateTime DATE;
		bool OPTIMGVIEWINVERTY;
		string[] CLIPBRDHEADERKEYS;
		string[] CLIPBRDHEADERVALS;
		string[] CLIPBRDHEADERCOMS;
		int[] CLIPBRDHEADERINDS;

		int UVITINTDRIFT_MAXDEV_INDEX = 0;
		Point[,] UVITINTMODEDRIFTPOLYPOINTS;
		Point[] POLYPOINTS;
		Point[] POLYPOINTS2;
		Point[] POLYPOINTSb;
		Point[] POLYPOINTS2b;
		Color POLYPOINTSCOLOR = Color.Yellow;
		Color POLYPOINTS2COLOR = Color.Red;

		string DIVMULTADDSUB_FILE;

		int RADIALPTX1, RADIALPTY1, RADIALPTX2, RADIALPTY2;
		double RADIALPTX1_CENT, RADIALPTY1_CENT, RADIALPTX2_CENT, RADIALPTY2_CENT;
		JPPlot RADIALLINE_PLOT;
		bool PLOTRADIALLINE;
		Point[] RADIALLINEBOXPOINTS;

		FITSFinder FITSFINDER;
		string[] FITSFINDERFILES;
		FITSFound FITSFOUND;

		bool DRAW_ROI_PATH = false;
		bool DRAW_ROI_PATH_START = false;
		double[,] ROI_PATH_COORDS;
		Point[] ROI_PATH_POINTS;
		//Rectangle[] ROI_PATH_RECTS;
		bool[,] ROI_REGION;

		bool DOMANREG, MANREG_CONTINUE;
		int[,] MANREGCOORDS;
		Rectangle[] MANREGCOORDRECTS;
		double[,,] MANREGCENTROIDS;

		int UVPCMODEPADOFFSET;

		bool DOUVITMANREG, UVITMANREG_CONTINUE, UVITMANREGDIR_MULTI, DO_UVITDRIFTFILES, UVITBADTRACK = false;
		string[] UVITMANREGFILELIST;
		string[] UVITMANREGDIRLIST;
		int UVITMANREGDIRLISTINDEX;
		double[] UVITMANREGFILELIST_TIMES;

		bool UVREGISTRATION, UVREGISTRATION_TOUCHPOINT, UVREGISTRATION_TRANSLATE, UVNUVTOFUV;
		string[] UVREGISTRATIONFILES;
		int UVREGISTRATIONFILESINDEX, UVREGISTRATION_ANCHOR_INDEX, UVREGISTRATION_ROTATION_INDEX;
		double[,,] UVREGISTRATION_CENTROIDS;
		double UVREGISTRATION_ROTATION_PHI;
		double[,] UVREGISTRATION_ROTATION_CENTROIDS;
		double[] UVREGISTRATION_PHIS;
		double[] UVREGISTRATION_XSHIFTS;
		double[] UVREGISTRATION_YSHIFTS;
		double[] UVREGISTRATION_XCENTERS;
		double[] UVREGISTRATION_YCENTERS;
		string[] UVNUVTOFUVFILES;
		string[] UVMERGEDIRS;
		int UVMERGEDIRS_INDEX = -1;
		bool DRIFTFROMPCPSTRACK = false;
		ArrayList MASTERAUTOLOADADDIN;

		WaitBar WAITBAR;

		int MidBtnMouseMoveXCurrent, MidBtnMouseMoveYCurrent, MidBtnMouseMoveXPrev, MidBtnMouseMoveYPrev, MidBtnMouseMoveXInit, MidBtnMouseMoveYInit;

		double SUBIMLEFTMOUSEDOWNINITX, SUBIMLEFTMOUSEDOWNINITY;

		double[] XSliceX;
		double[] XSliceY;
		double[] YSliceX;
		double[] YSliceY;

		//bool axis1, axis2;

		int UVLISTTOIMAGEPREC;
		double UVPARCELTIME;
		double UVDRIFTSTACKTIME;
		bool UVPLOTDRIFTLISTNOW;
		string UVPLOTDRIFTFILENAME;
		bool UVAPPLYDRIFTNOW;
		string UVAPPLYDRIFTCENTROIDSFILENAME;
		bool UVCREATEIMAGENOW;
		string UVCREATEIMAGEFILENAME;
		bool UVDRIFTAUTORUN;
		bool UVDRIFTBATCH;
		string[] UVDRIFTBATCHFILES;
		int UVDRIFTBATCHFILESINDEX;
		bool UVCONVERTLISTTOIMAGEBATCH;
		string[] UVCONVERTLISTTOIMAGEBATCHFILES;
		JPPlot XDRIFT_PLOT;
		JPPlot YDRIFT_PLOT;
		FITSImageSet SPAREFITSImageSet;
		bool AUTOVISDRIFTAPPLY = false;
		bool FUVDIREXISTS = false;
		bool NUVDIREXISTS = false;
		bool DONUVDRIFTNOW = false;		

		bool UVITBATCHOP = false;
		bool UVITBATCHOP_CANCELLED = false;
		bool AUTOVISDRIFT = false;
		bool UVITAUTOREGISTER = false;
		string UVITBATCHMESG = "";
		bool UVITPOSTMERGE = false;

		bool COG_CURSOR;
		JPPlot COG_PLOT;
		JPPlot RAD_PLOT;

		bool AUTOLOADIMAGES;
		string[] AUTOLOADIMAGESFILES;

		bool WCSMANUALRAD, WCSMANUALRAD_CONTINUE;
		RADecBox RADECBOX;
		double[] WCS_RA;
		double[] WCS_DEC;
		//double[,] WCS_CENTROIDS;
		bool WCSNEWPOINT;
		bool SHOW_WCSCOORDS;
		bool UVIT_DEROTATE_WCS;
		string[] UVIT_DEROTATE_FILES;
		WorldCoordinateSolution WCS_DEROT;
		bool WCSAUTOCANCEL = false;
		double[] RADIALPLOT_R;//radii
		double[] RADIALPLOT_V;//average values at radii
		double[] RADIALPLOT_P;//n pixels at radii
		double RADIALPLOT_PHI;
		bool RADIALPLOT_SETPHI;
		MLCCDLAB.MLSurface MLSURF;
		FitParametersWindow FPW;
		int RECENTFILESLISTLENGTH = 23;
		static string LASTTEXT = "";
		WCSAutoSolver WCSAS;
		string PSESAVEKERNELPATH;

		long TBC_TICKCOUNTREF = 0, TBC_FRAMETIMEREF = 0;
		double TBC_TIMEREF = 0;
		bool DO_TBC = false;
		ArrayList TCTFILELIST = new ArrayList();
		ArrayList LBTFILELIST = new ArrayList();
		JPPlot ROWplot;
		JPPlot COLplot;

		#endregion

		#region Form1 CONSTRUCTORS
		public Form1()
		{
			InitializeComponent();

			string[] startargs = new string[0];
			InitializeVars(startargs);
		}

		public Form1(string[] startargs)
		{
			InitializeComponent();

			InitializeVars(startargs);
		}
		#endregion

		private void InitializeVars(string[] startargs)
		{
			AUTOLOADIMAGESFILES = startargs;
			IWLCK = true;//fix cursor box
			FILELISTINDEX = 0;
			OLD_INDEX = 0;
			SUBRANGE = new int[] { -1, 0, 0, 0 };
			LOADSUBRANGE = false;
			SUBIMAGE = new double[21, 21];
			XSUBRANGE = new int[21];
			YSUBRANGE = new int[21];
			XPOS_CURSOR = 0;
			YPOS_CURSOR = 0;//zero based position in image window(s)
			PRVXPOS_CURSOR = 0;
			PRVYPOS_CURSOR = 0;
			SUBIMAGE_HWX = 10;
			SUBIMAGE_HWY = 10;
			DIMCLIM = new double[2];// min/max contrast limits
			IMSTDLIM = new double[2];
			CTSperPERCENT = 100;
			PREVMINCONTRASTVALUE = 0;
			PREVMAXCONTRASTVALUE = 100;
			FIRSTLOAD = true;
			FILESAVEPREC = TypeCode.Double;
			IMAGEWINDOWPEN = new Pen(Color.Yellow);
			BATCHVIEWINDEX = -1;
			UVPCMODEPADOFFSET = 0;
			UVLISTTOIMAGEPREC = 1;
			UVPARCELTIME = 0;
			UVDRIFTSTACKTIME = 0;
			UVPLOTDRIFTLISTNOW = false;
			UVAPPLYDRIFTNOW = false;
			UVCREATEIMAGENOW = false;
			UVDRIFTAUTORUN = false;
			UVDRIFTBATCH = false;
			UVDRIFTBATCHFILESINDEX = 0;
			UVREGISTRATION = false;
			UVREGISTRATION_TOUCHPOINT = false;
			UVNUVTOFUV = false;
			//axis1 = false;
			//axis2 = false;
			DOMANREG = false;
			MANREG_CONTINUE = false;
			MANREGCOORDS = new int[0, 0];
			MANREGCOORDRECTS = new Rectangle[0];
			UVITMANREG_CONTINUE = false;
			UVITMANREGDIRLISTINDEX = 0;
			DOUVITMANREG = false;
			DO_UVITDRIFTFILES = false;
			COG_CURSOR = false;
			COG_PLOT = new JPPlot();
			RAD_PLOT = new JPPlot();
			XDRIFT_PLOT = new JPPlot();
			YDRIFT_PLOT = new JPPlot();
			AUTOLOADIMAGES = false;
			WCSMANUALRAD = false;
			WCSMANUALRAD_CONTINUE = false;
			SHOW_WCSCOORDS = false;
			OPTIMGVIEWINVERTY = false;

			FNDCOORDS_X = new int[1];
			FNDCOORDS_Y = new int[1];
			FNDCOORDRECTS = new Rectangle[1];

			PSERECTCOLOURS = new Color[] { Color.OrangeRed, Color.Cyan, Color.LawnGreen, Color.BlueViolet, Color.DeepPink, Color.Aqua, Color.Crimson, Color.DarkGoldenrod, Color.Red, Color.Chartreuse, Color.HotPink };

			RADIALLINEBOXPOINTS = new Point[4];
			RADIALPLOT_SETPHI = false;

			ROWplot = new JPPlot();
			ROWplot.Text = "Row Plot";
			ROWplot.JPPlotMainMenu.Visible = true;
			COLplot = new JPPlot();
			COLplot.Text = "Column Plot";
			COLplot.JPPlotMainMenu.Visible = true;
		}
		
	}
}
