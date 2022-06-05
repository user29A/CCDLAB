namespace CCDLAB
{
	partial class UVIT_StatsPlot
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.MeanMedianTxt = new System.Windows.Forms.Label();
			this.label27 = new System.Windows.Forms.Label();
			this.label28 = new System.Windows.Forms.Label();
			this.label29 = new System.Windows.Forms.Label();
			this.label30 = new System.Windows.Forms.Label();
			this.MedMinTxt = new System.Windows.Forms.Label();
			this.MedMaxTxt = new System.Windows.Forms.Label();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.StdMinTxt = new System.Windows.Forms.Label();
			this.StdMaxTxt = new System.Windows.Forms.Label();
			this.StdMeanTxt = new System.Windows.Forms.Label();
			this.StdMedianTxt = new System.Windows.Forms.Label();
			this.StdStdvTxt = new System.Windows.Forms.Label();
			this.label36 = new System.Windows.Forms.Label();
			this.label37 = new System.Windows.Forms.Label();
			this.label38 = new System.Windows.Forms.Label();
			this.label39 = new System.Windows.Forms.Label();
			this.label40 = new System.Windows.Forms.Label();
			this.MedMeanTxt = new System.Windows.Forms.Label();
			this.MedStdvTxt = new System.Windows.Forms.Label();
			this.label16 = new System.Windows.Forms.Label();
			this.label17 = new System.Windows.Forms.Label();
			this.label18 = new System.Windows.Forms.Label();
			this.MeanStdvTxt = new System.Windows.Forms.Label();
			this.label26 = new System.Windows.Forms.Label();
			this.MedMedianTxt = new System.Windows.Forms.Label();
			this.MeanMeanTxt = new System.Windows.Forms.Label();
			this.jpChartMin = new JPChart.JPChart();
			this.jpChartStdv = new JPChart.JPChart();
			this.jpChartMedian = new JPChart.JPChart();
			this.jpChartMax = new JPChart.JPChart();
			this.exitCCDLABToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.exitThisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.PlotWrkr = new System.ComponentModel.BackgroundWorker();
			this.label19 = new System.Windows.Forms.Label();
			this.MinPanel = new System.Windows.Forms.GroupBox();
			this.MinMinTxt = new System.Windows.Forms.Label();
			this.MinMaxTxt = new System.Windows.Forms.Label();
			this.MinMeanTxt = new System.Windows.Forms.Label();
			this.MinMedianTxt = new System.Windows.Forms.Label();
			this.MinStdvTxt = new System.Windows.Forms.Label();
			this.SubImageMedianStatic = new System.Windows.Forms.Label();
			this.SubImageMeanStatic = new System.Windows.Forms.Label();
			this.SubImageStdvStatic = new System.Windows.Forms.Label();
			this.SubImageMinStatic = new System.Windows.Forms.Label();
			this.SubImageMaxStatic = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.MaxMinTxt = new System.Windows.Forms.Label();
			this.MaxMaxTxt = new System.Windows.Forms.Label();
			this.MaxMeanTxt = new System.Windows.Forms.Label();
			this.MaxMedianTxt = new System.Windows.Forms.Label();
			this.MaxStdvTxt = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.label10 = new System.Windows.Forms.Label();
			this.jpChartMean = new JPChart.JPChart();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.label20 = new System.Windows.Forms.Label();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.MeanMinTxt = new System.Windows.Forms.Label();
			this.MeanMaxTxt = new System.Windows.Forms.Label();
			this.groupBox4.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.jpChartMin)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.jpChartStdv)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.jpChartMedian)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.jpChartMax)).BeginInit();
			this.menuStrip1.SuspendLayout();
			this.MinPanel.SuspendLayout();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.jpChartMean)).BeginInit();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.SuspendLayout();
			// 
			// MeanMedianTxt
			// 
			this.MeanMedianTxt.Location = new System.Drawing.Point(67, 47);
			this.MeanMedianTxt.Name = "MeanMedianTxt";
			this.MeanMedianTxt.Size = new System.Drawing.Size(64, 15);
			this.MeanMedianTxt.TabIndex = 28;
			this.MeanMedianTxt.Text = "0";
			this.MeanMedianTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label27
			// 
			this.label27.Location = new System.Drawing.Point(6, 61);
			this.label27.Name = "label27";
			this.label27.Size = new System.Drawing.Size(45, 15);
			this.label27.TabIndex = 26;
			this.label27.Text = "Mean:";
			// 
			// label28
			// 
			this.label28.Location = new System.Drawing.Point(6, 76);
			this.label28.Name = "label28";
			this.label28.Size = new System.Drawing.Size(45, 15);
			this.label28.TabIndex = 25;
			this.label28.Text = "Stdv:";
			// 
			// label29
			// 
			this.label29.Location = new System.Drawing.Point(6, 16);
			this.label29.Name = "label29";
			this.label29.Size = new System.Drawing.Size(30, 15);
			this.label29.TabIndex = 22;
			this.label29.Text = "Min:";
			// 
			// label30
			// 
			this.label30.Location = new System.Drawing.Point(6, 31);
			this.label30.Name = "label30";
			this.label30.Size = new System.Drawing.Size(30, 15);
			this.label30.TabIndex = 23;
			this.label30.Text = "Max:";
			// 
			// MedMinTxt
			// 
			this.MedMinTxt.Location = new System.Drawing.Point(61, 17);
			this.MedMinTxt.Name = "MedMinTxt";
			this.MedMinTxt.Size = new System.Drawing.Size(70, 15);
			this.MedMinTxt.TabIndex = 31;
			this.MedMinTxt.Text = "0";
			this.MedMinTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MedMaxTxt
			// 
			this.MedMaxTxt.Location = new System.Drawing.Point(61, 32);
			this.MedMaxTxt.Name = "MedMaxTxt";
			this.MedMaxTxt.Size = new System.Drawing.Size(70, 15);
			this.MedMaxTxt.TabIndex = 30;
			this.MedMaxTxt.Text = "0";
			this.MedMaxTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// groupBox4
			// 
			this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox4.Controls.Add(this.StdMinTxt);
			this.groupBox4.Controls.Add(this.StdMaxTxt);
			this.groupBox4.Controls.Add(this.StdMeanTxt);
			this.groupBox4.Controls.Add(this.StdMedianTxt);
			this.groupBox4.Controls.Add(this.StdStdvTxt);
			this.groupBox4.Controls.Add(this.label36);
			this.groupBox4.Controls.Add(this.label37);
			this.groupBox4.Controls.Add(this.label38);
			this.groupBox4.Controls.Add(this.label39);
			this.groupBox4.Controls.Add(this.label40);
			this.groupBox4.Location = new System.Drawing.Point(12, 689);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(137, 95);
			this.groupBox4.TabIndex = 51;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Frame Stdv Stats";
			// 
			// StdMinTxt
			// 
			this.StdMinTxt.Location = new System.Drawing.Point(61, 17);
			this.StdMinTxt.Name = "StdMinTxt";
			this.StdMinTxt.Size = new System.Drawing.Size(70, 15);
			this.StdMinTxt.TabIndex = 31;
			this.StdMinTxt.Text = "0";
			this.StdMinTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// StdMaxTxt
			// 
			this.StdMaxTxt.Location = new System.Drawing.Point(61, 32);
			this.StdMaxTxt.Name = "StdMaxTxt";
			this.StdMaxTxt.Size = new System.Drawing.Size(70, 15);
			this.StdMaxTxt.TabIndex = 30;
			this.StdMaxTxt.Text = "0";
			this.StdMaxTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// StdMeanTxt
			// 
			this.StdMeanTxt.Location = new System.Drawing.Point(61, 62);
			this.StdMeanTxt.Name = "StdMeanTxt";
			this.StdMeanTxt.Size = new System.Drawing.Size(70, 15);
			this.StdMeanTxt.TabIndex = 29;
			this.StdMeanTxt.Text = "0";
			this.StdMeanTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// StdMedianTxt
			// 
			this.StdMedianTxt.Location = new System.Drawing.Point(67, 47);
			this.StdMedianTxt.Name = "StdMedianTxt";
			this.StdMedianTxt.Size = new System.Drawing.Size(64, 15);
			this.StdMedianTxt.TabIndex = 28;
			this.StdMedianTxt.Text = "0";
			this.StdMedianTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// StdStdvTxt
			// 
			this.StdStdvTxt.Location = new System.Drawing.Point(61, 77);
			this.StdStdvTxt.Name = "StdStdvTxt";
			this.StdStdvTxt.Size = new System.Drawing.Size(70, 15);
			this.StdStdvTxt.TabIndex = 27;
			this.StdStdvTxt.Text = "0";
			this.StdStdvTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label36
			// 
			this.label36.Location = new System.Drawing.Point(6, 46);
			this.label36.Name = "label36";
			this.label36.Size = new System.Drawing.Size(55, 15);
			this.label36.TabIndex = 24;
			this.label36.Text = "Median:";
			// 
			// label37
			// 
			this.label37.Location = new System.Drawing.Point(6, 61);
			this.label37.Name = "label37";
			this.label37.Size = new System.Drawing.Size(45, 15);
			this.label37.TabIndex = 26;
			this.label37.Text = "Mean:";
			// 
			// label38
			// 
			this.label38.Location = new System.Drawing.Point(6, 76);
			this.label38.Name = "label38";
			this.label38.Size = new System.Drawing.Size(45, 15);
			this.label38.TabIndex = 25;
			this.label38.Text = "Stdv:";
			// 
			// label39
			// 
			this.label39.Location = new System.Drawing.Point(6, 16);
			this.label39.Name = "label39";
			this.label39.Size = new System.Drawing.Size(30, 15);
			this.label39.TabIndex = 22;
			this.label39.Text = "Min:";
			// 
			// label40
			// 
			this.label40.Location = new System.Drawing.Point(6, 31);
			this.label40.Name = "label40";
			this.label40.Size = new System.Drawing.Size(30, 15);
			this.label40.TabIndex = 23;
			this.label40.Text = "Max:";
			// 
			// MedMeanTxt
			// 
			this.MedMeanTxt.Location = new System.Drawing.Point(61, 62);
			this.MedMeanTxt.Name = "MedMeanTxt";
			this.MedMeanTxt.Size = new System.Drawing.Size(70, 15);
			this.MedMeanTxt.TabIndex = 29;
			this.MedMeanTxt.Text = "0";
			this.MedMeanTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MedStdvTxt
			// 
			this.MedStdvTxt.Location = new System.Drawing.Point(61, 77);
			this.MedStdvTxt.Name = "MedStdvTxt";
			this.MedStdvTxt.Size = new System.Drawing.Size(70, 15);
			this.MedStdvTxt.TabIndex = 27;
			this.MedStdvTxt.Text = "0";
			this.MedStdvTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label16
			// 
			this.label16.Location = new System.Drawing.Point(6, 46);
			this.label16.Name = "label16";
			this.label16.Size = new System.Drawing.Size(55, 15);
			this.label16.TabIndex = 24;
			this.label16.Text = "Median:";
			// 
			// label17
			// 
			this.label17.Location = new System.Drawing.Point(6, 61);
			this.label17.Name = "label17";
			this.label17.Size = new System.Drawing.Size(45, 15);
			this.label17.TabIndex = 26;
			this.label17.Text = "Mean:";
			// 
			// label18
			// 
			this.label18.Location = new System.Drawing.Point(6, 76);
			this.label18.Name = "label18";
			this.label18.Size = new System.Drawing.Size(45, 15);
			this.label18.TabIndex = 25;
			this.label18.Text = "Stdv:";
			// 
			// MeanStdvTxt
			// 
			this.MeanStdvTxt.Location = new System.Drawing.Point(61, 77);
			this.MeanStdvTxt.Name = "MeanStdvTxt";
			this.MeanStdvTxt.Size = new System.Drawing.Size(70, 15);
			this.MeanStdvTxt.TabIndex = 27;
			this.MeanStdvTxt.Text = "0";
			this.MeanStdvTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label26
			// 
			this.label26.Location = new System.Drawing.Point(6, 46);
			this.label26.Name = "label26";
			this.label26.Size = new System.Drawing.Size(55, 15);
			this.label26.TabIndex = 24;
			this.label26.Text = "Median:";
			// 
			// MedMedianTxt
			// 
			this.MedMedianTxt.Location = new System.Drawing.Point(67, 47);
			this.MedMedianTxt.Name = "MedMedianTxt";
			this.MedMedianTxt.Size = new System.Drawing.Size(64, 15);
			this.MedMedianTxt.TabIndex = 28;
			this.MedMedianTxt.Text = "0";
			this.MedMedianTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MeanMeanTxt
			// 
			this.MeanMeanTxt.Location = new System.Drawing.Point(61, 62);
			this.MeanMeanTxt.Name = "MeanMeanTxt";
			this.MeanMeanTxt.Size = new System.Drawing.Size(70, 15);
			this.MeanMeanTxt.TabIndex = 29;
			this.MeanMeanTxt.Text = "0";
			this.MeanMeanTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// jpChartMin
			// 
			this.jpChartMin.Location = new System.Drawing.Point(155, 32);
			this.jpChartMin.Name = "jpChartMin";
			this.jpChartMin.Size = new System.Drawing.Size(932, 165);
			this.jpChartMin.TabIndex = 53;
			// 
			// jpChartStdv
			// 
			this.jpChartStdv.Location = new System.Drawing.Point(155, 692);
			this.jpChartStdv.Name = "jpChartStdv";
			this.jpChartStdv.Size = new System.Drawing.Size(932, 165);
			this.jpChartStdv.TabIndex = 57;
			// 
			// jpChartMedian
			// 
			this.jpChartMedian.Location = new System.Drawing.Point(155, 362);
			this.jpChartMedian.Name = "jpChartMedian";
			this.jpChartMedian.Size = new System.Drawing.Size(932, 165);
			this.jpChartMedian.TabIndex = 55;
			// 
			// jpChartMax
			// 
			this.jpChartMax.Location = new System.Drawing.Point(155, 197);
			this.jpChartMax.Name = "jpChartMax";
			this.jpChartMax.Size = new System.Drawing.Size(932, 165);
			this.jpChartMax.TabIndex = 54;
			// 
			// exitCCDLABToolStripMenuItem
			// 
			this.exitCCDLABToolStripMenuItem.BackColor = System.Drawing.Color.LightCoral;
			this.exitCCDLABToolStripMenuItem.Name = "exitCCDLABToolStripMenuItem";
			this.exitCCDLABToolStripMenuItem.Size = new System.Drawing.Size(86, 20);
			this.exitCCDLABToolStripMenuItem.Text = "Exit CCDLAB";
			this.exitCCDLABToolStripMenuItem.Click += new System.EventHandler(this.exitCCDLABToolStripMenuItem_Click);
			// 
			// exitThisToolStripMenuItem
			// 
			this.exitThisToolStripMenuItem.BackColor = System.Drawing.Color.LightGreen;
			this.exitThisToolStripMenuItem.Name = "exitThisToolStripMenuItem";
			this.exitThisToolStripMenuItem.Size = new System.Drawing.Size(62, 20);
			this.exitThisToolStripMenuItem.Text = "Exit This";
			this.exitThisToolStripMenuItem.Click += new System.EventHandler(this.exitThisToolStripMenuItem_Click);
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitThisToolStripMenuItem,
            this.exitCCDLABToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(1099, 24);
			this.menuStrip1.TabIndex = 52;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// PlotWrkr
			// 
			this.PlotWrkr.WorkerReportsProgress = true;
			this.PlotWrkr.WorkerSupportsCancellation = true;
			this.PlotWrkr.DoWork += new System.ComponentModel.DoWorkEventHandler(this.PlotWrkr_DoWork);
			this.PlotWrkr.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.PlotWrkr_ProgressChanged);
			this.PlotWrkr.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.PlotWrkr_RunWorkerCompleted);
			// 
			// label19
			// 
			this.label19.Location = new System.Drawing.Point(6, 16);
			this.label19.Name = "label19";
			this.label19.Size = new System.Drawing.Size(30, 15);
			this.label19.TabIndex = 22;
			this.label19.Text = "Min:";
			// 
			// MinPanel
			// 
			this.MinPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.MinPanel.Controls.Add(this.MinMinTxt);
			this.MinPanel.Controls.Add(this.MinMaxTxt);
			this.MinPanel.Controls.Add(this.MinMeanTxt);
			this.MinPanel.Controls.Add(this.MinMedianTxt);
			this.MinPanel.Controls.Add(this.MinStdvTxt);
			this.MinPanel.Controls.Add(this.SubImageMedianStatic);
			this.MinPanel.Controls.Add(this.SubImageMeanStatic);
			this.MinPanel.Controls.Add(this.SubImageStdvStatic);
			this.MinPanel.Controls.Add(this.SubImageMinStatic);
			this.MinPanel.Controls.Add(this.SubImageMaxStatic);
			this.MinPanel.Location = new System.Drawing.Point(12, 36);
			this.MinPanel.Name = "MinPanel";
			this.MinPanel.Size = new System.Drawing.Size(137, 95);
			this.MinPanel.TabIndex = 47;
			this.MinPanel.TabStop = false;
			this.MinPanel.Text = "Frame Minimum Stats";
			// 
			// MinMinTxt
			// 
			this.MinMinTxt.Location = new System.Drawing.Point(61, 17);
			this.MinMinTxt.Name = "MinMinTxt";
			this.MinMinTxt.Size = new System.Drawing.Size(70, 15);
			this.MinMinTxt.TabIndex = 31;
			this.MinMinTxt.Text = "0";
			this.MinMinTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MinMaxTxt
			// 
			this.MinMaxTxt.Location = new System.Drawing.Point(61, 32);
			this.MinMaxTxt.Name = "MinMaxTxt";
			this.MinMaxTxt.Size = new System.Drawing.Size(70, 15);
			this.MinMaxTxt.TabIndex = 30;
			this.MinMaxTxt.Text = "0";
			this.MinMaxTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MinMeanTxt
			// 
			this.MinMeanTxt.Location = new System.Drawing.Point(61, 62);
			this.MinMeanTxt.Name = "MinMeanTxt";
			this.MinMeanTxt.Size = new System.Drawing.Size(70, 15);
			this.MinMeanTxt.TabIndex = 29;
			this.MinMeanTxt.Text = "0";
			this.MinMeanTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MinMedianTxt
			// 
			this.MinMedianTxt.Location = new System.Drawing.Point(67, 47);
			this.MinMedianTxt.Name = "MinMedianTxt";
			this.MinMedianTxt.Size = new System.Drawing.Size(64, 15);
			this.MinMedianTxt.TabIndex = 28;
			this.MinMedianTxt.Text = "0";
			this.MinMedianTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MinStdvTxt
			// 
			this.MinStdvTxt.Location = new System.Drawing.Point(61, 77);
			this.MinStdvTxt.Name = "MinStdvTxt";
			this.MinStdvTxt.Size = new System.Drawing.Size(70, 15);
			this.MinStdvTxt.TabIndex = 27;
			this.MinStdvTxt.Text = "0";
			this.MinStdvTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// SubImageMedianStatic
			// 
			this.SubImageMedianStatic.Location = new System.Drawing.Point(6, 46);
			this.SubImageMedianStatic.Name = "SubImageMedianStatic";
			this.SubImageMedianStatic.Size = new System.Drawing.Size(55, 15);
			this.SubImageMedianStatic.TabIndex = 24;
			this.SubImageMedianStatic.Text = "Median:";
			// 
			// SubImageMeanStatic
			// 
			this.SubImageMeanStatic.Location = new System.Drawing.Point(6, 61);
			this.SubImageMeanStatic.Name = "SubImageMeanStatic";
			this.SubImageMeanStatic.Size = new System.Drawing.Size(45, 15);
			this.SubImageMeanStatic.TabIndex = 26;
			this.SubImageMeanStatic.Text = "Mean:";
			// 
			// SubImageStdvStatic
			// 
			this.SubImageStdvStatic.Location = new System.Drawing.Point(6, 76);
			this.SubImageStdvStatic.Name = "SubImageStdvStatic";
			this.SubImageStdvStatic.Size = new System.Drawing.Size(45, 15);
			this.SubImageStdvStatic.TabIndex = 25;
			this.SubImageStdvStatic.Text = "Stdv:";
			// 
			// SubImageMinStatic
			// 
			this.SubImageMinStatic.Location = new System.Drawing.Point(6, 16);
			this.SubImageMinStatic.Name = "SubImageMinStatic";
			this.SubImageMinStatic.Size = new System.Drawing.Size(30, 15);
			this.SubImageMinStatic.TabIndex = 22;
			this.SubImageMinStatic.Text = "Min:";
			// 
			// SubImageMaxStatic
			// 
			this.SubImageMaxStatic.Location = new System.Drawing.Point(6, 31);
			this.SubImageMaxStatic.Name = "SubImageMaxStatic";
			this.SubImageMaxStatic.Size = new System.Drawing.Size(30, 15);
			this.SubImageMaxStatic.TabIndex = 23;
			this.SubImageMaxStatic.Text = "Max:";
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox1.Controls.Add(this.MaxMinTxt);
			this.groupBox1.Controls.Add(this.MaxMaxTxt);
			this.groupBox1.Controls.Add(this.MaxMeanTxt);
			this.groupBox1.Controls.Add(this.MaxMedianTxt);
			this.groupBox1.Controls.Add(this.MaxStdvTxt);
			this.groupBox1.Controls.Add(this.label6);
			this.groupBox1.Controls.Add(this.label7);
			this.groupBox1.Controls.Add(this.label8);
			this.groupBox1.Controls.Add(this.label9);
			this.groupBox1.Controls.Add(this.label10);
			this.groupBox1.Location = new System.Drawing.Point(12, 192);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(137, 95);
			this.groupBox1.TabIndex = 48;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Frame Maximum Stats";
			// 
			// MaxMinTxt
			// 
			this.MaxMinTxt.Location = new System.Drawing.Point(61, 17);
			this.MaxMinTxt.Name = "MaxMinTxt";
			this.MaxMinTxt.Size = new System.Drawing.Size(70, 15);
			this.MaxMinTxt.TabIndex = 31;
			this.MaxMinTxt.Text = "0";
			this.MaxMinTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MaxMaxTxt
			// 
			this.MaxMaxTxt.Location = new System.Drawing.Point(61, 32);
			this.MaxMaxTxt.Name = "MaxMaxTxt";
			this.MaxMaxTxt.Size = new System.Drawing.Size(70, 15);
			this.MaxMaxTxt.TabIndex = 30;
			this.MaxMaxTxt.Text = "0";
			this.MaxMaxTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MaxMeanTxt
			// 
			this.MaxMeanTxt.Location = new System.Drawing.Point(61, 62);
			this.MaxMeanTxt.Name = "MaxMeanTxt";
			this.MaxMeanTxt.Size = new System.Drawing.Size(70, 15);
			this.MaxMeanTxt.TabIndex = 29;
			this.MaxMeanTxt.Text = "0";
			this.MaxMeanTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MaxMedianTxt
			// 
			this.MaxMedianTxt.Location = new System.Drawing.Point(67, 47);
			this.MaxMedianTxt.Name = "MaxMedianTxt";
			this.MaxMedianTxt.Size = new System.Drawing.Size(64, 15);
			this.MaxMedianTxt.TabIndex = 28;
			this.MaxMedianTxt.Text = "0";
			this.MaxMedianTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MaxStdvTxt
			// 
			this.MaxStdvTxt.Location = new System.Drawing.Point(61, 77);
			this.MaxStdvTxt.Name = "MaxStdvTxt";
			this.MaxStdvTxt.Size = new System.Drawing.Size(70, 15);
			this.MaxStdvTxt.TabIndex = 27;
			this.MaxStdvTxt.Text = "0";
			this.MaxStdvTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(6, 46);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(55, 15);
			this.label6.TabIndex = 24;
			this.label6.Text = "Median:";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(6, 61);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(45, 15);
			this.label7.TabIndex = 26;
			this.label7.Text = "Mean:";
			// 
			// label8
			// 
			this.label8.Location = new System.Drawing.Point(6, 76);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(45, 15);
			this.label8.TabIndex = 25;
			this.label8.Text = "Stdv:";
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(6, 16);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(30, 15);
			this.label9.TabIndex = 22;
			this.label9.Text = "Min:";
			// 
			// label10
			// 
			this.label10.Location = new System.Drawing.Point(6, 31);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(30, 15);
			this.label10.TabIndex = 23;
			this.label10.Text = "Max:";
			// 
			// jpChartMean
			// 
			this.jpChartMean.Location = new System.Drawing.Point(155, 527);
			this.jpChartMean.Name = "jpChartMean";
			this.jpChartMean.Size = new System.Drawing.Size(932, 165);
			this.jpChartMean.TabIndex = 56;
			// 
			// groupBox2
			// 
			this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox2.Controls.Add(this.MedMinTxt);
			this.groupBox2.Controls.Add(this.MedMaxTxt);
			this.groupBox2.Controls.Add(this.MedMeanTxt);
			this.groupBox2.Controls.Add(this.MedMedianTxt);
			this.groupBox2.Controls.Add(this.MedStdvTxt);
			this.groupBox2.Controls.Add(this.label16);
			this.groupBox2.Controls.Add(this.label17);
			this.groupBox2.Controls.Add(this.label18);
			this.groupBox2.Controls.Add(this.label19);
			this.groupBox2.Controls.Add(this.label20);
			this.groupBox2.Location = new System.Drawing.Point(12, 358);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(137, 95);
			this.groupBox2.TabIndex = 50;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Frame Median Stats";
			// 
			// label20
			// 
			this.label20.Location = new System.Drawing.Point(6, 31);
			this.label20.Name = "label20";
			this.label20.Size = new System.Drawing.Size(30, 15);
			this.label20.TabIndex = 23;
			this.label20.Text = "Max:";
			// 
			// groupBox3
			// 
			this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox3.Controls.Add(this.MeanMinTxt);
			this.groupBox3.Controls.Add(this.MeanMaxTxt);
			this.groupBox3.Controls.Add(this.MeanMeanTxt);
			this.groupBox3.Controls.Add(this.MeanMedianTxt);
			this.groupBox3.Controls.Add(this.MeanStdvTxt);
			this.groupBox3.Controls.Add(this.label26);
			this.groupBox3.Controls.Add(this.label27);
			this.groupBox3.Controls.Add(this.label28);
			this.groupBox3.Controls.Add(this.label29);
			this.groupBox3.Controls.Add(this.label30);
			this.groupBox3.Location = new System.Drawing.Point(12, 523);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(137, 95);
			this.groupBox3.TabIndex = 49;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Frame Mean Stats";
			// 
			// MeanMinTxt
			// 
			this.MeanMinTxt.Location = new System.Drawing.Point(61, 17);
			this.MeanMinTxt.Name = "MeanMinTxt";
			this.MeanMinTxt.Size = new System.Drawing.Size(70, 15);
			this.MeanMinTxt.TabIndex = 31;
			this.MeanMinTxt.Text = "0";
			this.MeanMinTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// MeanMaxTxt
			// 
			this.MeanMaxTxt.Location = new System.Drawing.Point(61, 32);
			this.MeanMaxTxt.Name = "MeanMaxTxt";
			this.MeanMaxTxt.Size = new System.Drawing.Size(70, 15);
			this.MeanMaxTxt.TabIndex = 30;
			this.MeanMaxTxt.Text = "0";
			this.MeanMaxTxt.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// UVIT_StatsPlot
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1099, 862);
			this.Controls.Add(this.groupBox4);
			this.Controls.Add(this.jpChartMin);
			this.Controls.Add(this.jpChartStdv);
			this.Controls.Add(this.jpChartMedian);
			this.Controls.Add(this.jpChartMax);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.MinPanel);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.jpChartMean);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox3);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "UVIT_StatsPlot";
			this.Text = "Frame Stats Plot";
			this.TopMost = true;
			this.groupBox4.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.jpChartMin)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.jpChartStdv)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.jpChartMedian)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.jpChartMax)).EndInit();
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.MinPanel.ResumeLayout(false);
			this.groupBox1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.jpChartMean)).EndInit();
			this.groupBox2.ResumeLayout(false);
			this.groupBox3.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		public System.Windows.Forms.Label MeanMedianTxt;
		private System.Windows.Forms.Label label27;
		private System.Windows.Forms.Label label28;
		private System.Windows.Forms.Label label29;
		private System.Windows.Forms.Label label30;
		public System.Windows.Forms.Label MedMinTxt;
		public System.Windows.Forms.Label MedMaxTxt;
		public System.Windows.Forms.GroupBox groupBox4;
		public System.Windows.Forms.Label StdMinTxt;
		public System.Windows.Forms.Label StdMaxTxt;
		public System.Windows.Forms.Label StdMeanTxt;
		public System.Windows.Forms.Label StdMedianTxt;
		public System.Windows.Forms.Label StdStdvTxt;
		private System.Windows.Forms.Label label36;
		private System.Windows.Forms.Label label37;
		private System.Windows.Forms.Label label38;
		private System.Windows.Forms.Label label39;
		private System.Windows.Forms.Label label40;
		public System.Windows.Forms.Label MedMeanTxt;
		public System.Windows.Forms.Label MedStdvTxt;
		private System.Windows.Forms.Label label16;
		private System.Windows.Forms.Label label17;
		private System.Windows.Forms.Label label18;
		public System.Windows.Forms.Label MeanStdvTxt;
		private System.Windows.Forms.Label label26;
		public System.Windows.Forms.Label MedMedianTxt;
		public System.Windows.Forms.Label MeanMeanTxt;
		private JPChart.JPChart jpChartMin;
		private JPChart.JPChart jpChartStdv;
		private JPChart.JPChart jpChartMedian;
		private JPChart.JPChart jpChartMax;
		private System.Windows.Forms.ToolStripMenuItem exitCCDLABToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem exitThisToolStripMenuItem;
		private System.Windows.Forms.MenuStrip menuStrip1;
		public System.ComponentModel.BackgroundWorker PlotWrkr;
		private System.Windows.Forms.Label label19;
		public System.Windows.Forms.GroupBox MinPanel;
		public System.Windows.Forms.Label MinMinTxt;
		public System.Windows.Forms.Label MinMaxTxt;
		public System.Windows.Forms.Label MinMeanTxt;
		public System.Windows.Forms.Label MinMedianTxt;
		public System.Windows.Forms.Label MinStdvTxt;
		private System.Windows.Forms.Label SubImageMedianStatic;
		private System.Windows.Forms.Label SubImageMeanStatic;
		private System.Windows.Forms.Label SubImageStdvStatic;
		private System.Windows.Forms.Label SubImageMinStatic;
		private System.Windows.Forms.Label SubImageMaxStatic;
		public System.Windows.Forms.GroupBox groupBox1;
		public System.Windows.Forms.Label MaxMinTxt;
		public System.Windows.Forms.Label MaxMaxTxt;
		public System.Windows.Forms.Label MaxMeanTxt;
		public System.Windows.Forms.Label MaxMedianTxt;
		public System.Windows.Forms.Label MaxStdvTxt;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label10;
		private JPChart.JPChart jpChartMean;
		public System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label label20;
		public System.Windows.Forms.GroupBox groupBox3;
		public System.Windows.Forms.Label MeanMinTxt;
		public System.Windows.Forms.Label MeanMaxTxt;
	}
}