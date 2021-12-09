namespace CCDLAB
{
	partial class JPPlot
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
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
			this.JPChart1 = new JPChart.JPChart();
			this.JPPlotMainMenu = new System.Windows.Forms.MenuStrip();
			this.JPPlotMenuItem_Fit = new System.Windows.Forms.ToolStripMenuItem();
			this.FitMenuGaussian = new System.Windows.Forms.ToolStripMenuItem();
			this.FitMenuMoffat = new System.Windows.Forms.ToolStripMenuItem();
			this.FitMenuPlotResidualsChck = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.pixelScalearcsecpixelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.PixelScaleTxtBox = new System.Windows.Forms.ToolStripTextBox();
			this.button1 = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.JPChart1)).BeginInit();
			this.JPPlotMainMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// JPChart1
			// 
			this.JPChart1.BackColor = System.Drawing.Color.Gray;
			this.JPChart1.BackGradientStyle = System.Windows.Forms.DataVisualization.Charting.GradientStyle.TopBottom;
			chartArea1.AxisX.MajorGrid.Enabled = false;
			chartArea1.AxisX.ScrollBar.Enabled = false;
			chartArea1.AxisY.MajorGrid.Enabled = false;
			chartArea1.AxisY.ScrollBar.Enabled = false;
			chartArea1.Name = "ChartArea1";
			this.JPChart1.ChartAreas.Add(chartArea1);
			this.JPChart1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.JPChart1.Location = new System.Drawing.Point(0, 0);
			this.JPChart1.Name = "JPChart1";
			series1.ChartArea = "ChartArea1";
			series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
			series1.Name = "Series1";
			this.JPChart1.Series.Add(series1);
			this.JPChart1.Size = new System.Drawing.Size(672, 609);
			this.JPChart1.TabIndex = 6;
			this.JPChart1.Text = "jpChart1";
			// 
			// JPPlotMainMenu
			// 
			this.JPPlotMainMenu.BackColor = System.Drawing.Color.Gray;
			this.JPPlotMainMenu.ImageScalingSize = new System.Drawing.Size(24, 24);
			this.JPPlotMainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.JPPlotMenuItem_Fit});
			this.JPPlotMainMenu.Location = new System.Drawing.Point(0, 0);
			this.JPPlotMainMenu.Name = "JPPlotMainMenu";
			this.JPPlotMainMenu.Size = new System.Drawing.Size(672, 24);
			this.JPPlotMainMenu.TabIndex = 4;
			this.JPPlotMainMenu.Text = "menuStrip1";
			this.JPPlotMainMenu.Visible = false;
			// 
			// JPPlotMenuItem_Fit
			// 
			this.JPPlotMenuItem_Fit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FitMenuGaussian,
            this.FitMenuMoffat,
            this.FitMenuPlotResidualsChck,
            this.toolStripSeparator1,
            this.pixelScalearcsecpixelToolStripMenuItem});
			this.JPPlotMenuItem_Fit.Name = "JPPlotMenuItem_Fit";
			this.JPPlotMenuItem_Fit.Size = new System.Drawing.Size(32, 20);
			this.JPPlotMenuItem_Fit.Text = "Fit";
			this.JPPlotMenuItem_Fit.Click += new System.EventHandler(this.JPPlotMenuItem_Fit_Click);
			// 
			// FitMenuGaussian
			// 
			this.FitMenuGaussian.Name = "FitMenuGaussian";
			this.FitMenuGaussian.Size = new System.Drawing.Size(203, 22);
			this.FitMenuGaussian.Text = "Gaussian";
			this.FitMenuGaussian.Click += new System.EventHandler(this.FitMenuGaussian_Click);
			// 
			// FitMenuMoffat
			// 
			this.FitMenuMoffat.Name = "FitMenuMoffat";
			this.FitMenuMoffat.Size = new System.Drawing.Size(203, 22);
			this.FitMenuMoffat.Text = "Moffat";
			this.FitMenuMoffat.Click += new System.EventHandler(this.FitMenuMoffat_Click);
			// 
			// FitMenuPlotResidualsChck
			// 
			this.FitMenuPlotResidualsChck.CheckOnClick = true;
			this.FitMenuPlotResidualsChck.Name = "FitMenuPlotResidualsChck";
			this.FitMenuPlotResidualsChck.Size = new System.Drawing.Size(203, 22);
			this.FitMenuPlotResidualsChck.Text = "Plot Residuals";
			this.FitMenuPlotResidualsChck.Visible = false;
			this.FitMenuPlotResidualsChck.Click += new System.EventHandler(this.FitMenuPlotResidualsChck_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(200, 6);
			// 
			// pixelScalearcsecpixelToolStripMenuItem
			// 
			this.pixelScalearcsecpixelToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.PixelScaleTxtBox});
			this.pixelScalearcsecpixelToolStripMenuItem.Name = "pixelScalearcsecpixelToolStripMenuItem";
			this.pixelScalearcsecpixelToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
			this.pixelScalearcsecpixelToolStripMenuItem.Text = "Pixel Scale (arcsec/pixel)";
			// 
			// PixelScaleTxtBox
			// 
			this.PixelScaleTxtBox.Name = "PixelScaleTxtBox";
			this.PixelScaleTxtBox.Size = new System.Drawing.Size(100, 23);
			this.PixelScaleTxtBox.Text = "1";
			this.PixelScaleTxtBox.TextChanged += new System.EventHandler(this.PixelScaleTxtBox_TextChanged);
			// 
			// button1
			// 
			this.button1.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.button1.Location = new System.Drawing.Point(156, 49);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 5;
			this.button1.Text = "button1";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// JPPlot
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.button1;
			this.ClientSize = new System.Drawing.Size(672, 609);
			this.Controls.Add(this.JPChart1);
			this.Controls.Add(this.JPPlotMainMenu);
			this.Controls.Add(this.button1);
			this.MainMenuStrip = this.JPPlotMainMenu;
			this.Name = "JPPlot";
			this.TopMost = true;
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.JPPlot_FormClosing);
			this.Load += new System.EventHandler(this.JPPlot_Load);
			this.TextChanged += new System.EventHandler(this.JPPlot_TextChanged);
			((System.ComponentModel.ISupportInitialize)(this.JPChart1)).EndInit();
			this.JPPlotMainMenu.ResumeLayout(false);
			this.JPPlotMainMenu.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		public JPChart.JPChart JPChart1;
		public System.Windows.Forms.MenuStrip JPPlotMainMenu;
		private System.Windows.Forms.ToolStripMenuItem JPPlotMenuItem_Fit;
		public System.Windows.Forms.ToolStripMenuItem FitMenuGaussian;
		public System.Windows.Forms.ToolStripMenuItem FitMenuMoffat;
		private System.Windows.Forms.ToolStripMenuItem FitMenuPlotResidualsChck;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem pixelScalearcsecpixelToolStripMenuItem;
		public System.Windows.Forms.ToolStripTextBox PixelScaleTxtBox;
		private System.Windows.Forms.Button button1;
	}
}