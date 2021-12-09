namespace CCDLAB
{
	partial class ColorImageCreator
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ColorImageCreator));
			this.CancelBtn = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.RedLogRadioBtn = new System.Windows.Forms.RadioButton();
			this.label9 = new System.Windows.Forms.Label();
			this.RedMaxCutOffLabel = new System.Windows.Forms.Label();
			this.RedMinCutOffLabel = new System.Windows.Forms.Label();
			this.RedSquaredRadioBtn = new System.Windows.Forms.RadioButton();
			this.RedSqrtRadioBtn = new System.Windows.Forms.RadioButton();
			this.RedLinearRadioBtn = new System.Windows.Forms.RadioButton();
			this.RedMaxScrollBar = new System.Windows.Forms.HScrollBar();
			this.RedMinScrollBar = new System.Windows.Forms.HScrollBar();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.GreenLogRadioBtn = new System.Windows.Forms.RadioButton();
			this.label7 = new System.Windows.Forms.Label();
			this.GreenMaxCutOffLabel = new System.Windows.Forms.Label();
			this.GreenMinCutOffLabel = new System.Windows.Forms.Label();
			this.GreenSquaredRadioBtn = new System.Windows.Forms.RadioButton();
			this.GreenSqrtRadioBtn = new System.Windows.Forms.RadioButton();
			this.GreenLinearRadioBtn = new System.Windows.Forms.RadioButton();
			this.GreenMaxScrollBar = new System.Windows.Forms.HScrollBar();
			this.GreenMinScrollBar = new System.Windows.Forms.HScrollBar();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.BlueLogRadioBtn = new System.Windows.Forms.RadioButton();
			this.label19 = new System.Windows.Forms.Label();
			this.BlueMaxCutOffLabel = new System.Windows.Forms.Label();
			this.BlueMinCutOffLabel = new System.Windows.Forms.Label();
			this.BlueSquaredRadioBtn = new System.Windows.Forms.RadioButton();
			this.BlueSqrtRadioBtn = new System.Windows.Forms.RadioButton();
			this.BlueLinearRadioBtn = new System.Windows.Forms.RadioButton();
			this.BlueMaxScrollBar = new System.Windows.Forms.HScrollBar();
			this.BlueMinScrollBar = new System.Windows.Forms.HScrollBar();
			this.SaveImageBtn = new System.Windows.Forms.Button();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.label2 = new System.Windows.Forms.Label();
			this.MinStdvTextBox = new System.Windows.Forms.TextBox();
			this.FullContrastChck = new System.Windows.Forms.RadioButton();
			this.MaxStdvTextBox = new System.Windows.Forms.TextBox();
			this.WideContrastChck = new System.Windows.Forms.RadioButton();
			this.DarkContrastChck = new System.Windows.Forms.RadioButton();
			this.label1 = new System.Windows.Forms.Label();
			this.LoadSaveDropDown = new System.Windows.Forms.ComboBox();
			this.groupBox5 = new System.Windows.Forms.GroupBox();
			this.GlobalLogRadioBtn = new System.Windows.Forms.RadioButton();
			this.GlobalSquaredRadioBtn = new System.Windows.Forms.RadioButton();
			this.GlobalSqrtRadioBtn = new System.Windows.Forms.RadioButton();
			this.GlobalLinearRadioBtn = new System.Windows.Forms.RadioButton();
			this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.groupBox4.SuspendLayout();
			this.groupBox5.SuspendLayout();
			this.SuspendLayout();
			// 
			// CancelBtn
			// 
			this.CancelBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(298, 453);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(55, 23);
			this.CancelBtn.TabIndex = 0;
			this.CancelBtn.Text = "Close";
			this.CancelBtn.UseVisualStyleBackColor = true;
			this.CancelBtn.Click += new System.EventHandler(this.CancelBtn_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.BackColor = System.Drawing.Color.Gainsboro;
			this.groupBox1.Controls.Add(this.RedLogRadioBtn);
			this.groupBox1.Controls.Add(this.label9);
			this.groupBox1.Controls.Add(this.RedMaxCutOffLabel);
			this.groupBox1.Controls.Add(this.RedMinCutOffLabel);
			this.groupBox1.Controls.Add(this.RedSquaredRadioBtn);
			this.groupBox1.Controls.Add(this.RedSqrtRadioBtn);
			this.groupBox1.Controls.Add(this.RedLinearRadioBtn);
			this.groupBox1.Controls.Add(this.RedMaxScrollBar);
			this.groupBox1.Controls.Add(this.RedMinScrollBar);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(340, 116);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Red Channel";
			// 
			// RedLogRadioBtn
			// 
			this.RedLogRadioBtn.AutoSize = true;
			this.RedLogRadioBtn.Location = new System.Drawing.Point(279, 88);
			this.RedLogRadioBtn.Name = "RedLogRadioBtn";
			this.RedLogRadioBtn.Size = new System.Drawing.Size(43, 17);
			this.RedLogRadioBtn.TabIndex = 6;
			this.RedLogRadioBtn.Text = "Log";
			this.RedLogRadioBtn.UseVisualStyleBackColor = true;
			this.RedLogRadioBtn.CheckedChanged += new System.EventHandler(this.RedLogRadioBtn_CheckedChanged);
			// 
			// label9
			// 
			this.label9.AutoSize = true;
			this.label9.Location = new System.Drawing.Point(6, 88);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(45, 13);
			this.label9.TabIndex = 13;
			this.label9.Text = "Scaling:";
			// 
			// RedMaxCutOffLabel
			// 
			this.RedMaxCutOffLabel.AutoSize = true;
			this.RedMaxCutOffLabel.Location = new System.Drawing.Point(141, 46);
			this.RedMaxCutOffLabel.Name = "RedMaxCutOffLabel";
			this.RedMaxCutOffLabel.Size = new System.Drawing.Size(58, 13);
			this.RedMaxCutOffLabel.TabIndex = 7;
			this.RedMaxCutOffLabel.Text = "Max Cutoff";
			// 
			// RedMinCutOffLabel
			// 
			this.RedMinCutOffLabel.AutoSize = true;
			this.RedMinCutOffLabel.Location = new System.Drawing.Point(143, 16);
			this.RedMinCutOffLabel.Name = "RedMinCutOffLabel";
			this.RedMinCutOffLabel.Size = new System.Drawing.Size(55, 13);
			this.RedMinCutOffLabel.TabIndex = 6;
			this.RedMinCutOffLabel.Text = "Min Cutoff";
			// 
			// RedSquaredRadioBtn
			// 
			this.RedSquaredRadioBtn.AutoSize = true;
			this.RedSquaredRadioBtn.Location = new System.Drawing.Point(208, 87);
			this.RedSquaredRadioBtn.Name = "RedSquaredRadioBtn";
			this.RedSquaredRadioBtn.Size = new System.Drawing.Size(65, 17);
			this.RedSquaredRadioBtn.TabIndex = 4;
			this.RedSquaredRadioBtn.Text = "Squared";
			this.RedSquaredRadioBtn.UseVisualStyleBackColor = true;
			this.RedSquaredRadioBtn.CheckedChanged += new System.EventHandler(this.RedSquaredRadioBtn_CheckedChanged);
			// 
			// RedSqrtRadioBtn
			// 
			this.RedSqrtRadioBtn.AutoSize = true;
			this.RedSqrtRadioBtn.Location = new System.Drawing.Point(117, 87);
			this.RedSqrtRadioBtn.Name = "RedSqrtRadioBtn";
			this.RedSqrtRadioBtn.Size = new System.Drawing.Size(85, 17);
			this.RedSqrtRadioBtn.TabIndex = 3;
			this.RedSqrtRadioBtn.Text = "Square Root";
			this.RedSqrtRadioBtn.UseVisualStyleBackColor = true;
			this.RedSqrtRadioBtn.CheckedChanged += new System.EventHandler(this.RedSqrtRadioBtn_CheckedChanged);
			// 
			// RedLinearRadioBtn
			// 
			this.RedLinearRadioBtn.AutoSize = true;
			this.RedLinearRadioBtn.Checked = true;
			this.RedLinearRadioBtn.Location = new System.Drawing.Point(57, 87);
			this.RedLinearRadioBtn.Name = "RedLinearRadioBtn";
			this.RedLinearRadioBtn.Size = new System.Drawing.Size(54, 17);
			this.RedLinearRadioBtn.TabIndex = 2;
			this.RedLinearRadioBtn.TabStop = true;
			this.RedLinearRadioBtn.Text = "Linear";
			this.RedLinearRadioBtn.UseVisualStyleBackColor = true;
			this.RedLinearRadioBtn.CheckedChanged += new System.EventHandler(this.RedLinearRadioBtn_CheckedChanged);
			// 
			// RedMaxScrollBar
			// 
			this.RedMaxScrollBar.Location = new System.Drawing.Point(9, 59);
			this.RedMaxScrollBar.Name = "RedMaxScrollBar";
			this.RedMaxScrollBar.Size = new System.Drawing.Size(322, 17);
			this.RedMaxScrollBar.TabIndex = 1;
			this.RedMaxScrollBar.Value = 100;
			this.RedMaxScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.RedMaxScrollBar_Scroll);
			// 
			// RedMinScrollBar
			// 
			this.RedMinScrollBar.Location = new System.Drawing.Point(9, 29);
			this.RedMinScrollBar.Name = "RedMinScrollBar";
			this.RedMinScrollBar.Size = new System.Drawing.Size(322, 17);
			this.RedMinScrollBar.TabIndex = 0;
			this.RedMinScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.RedMinScrollBar_Scroll);
			// 
			// groupBox2
			// 
			this.groupBox2.BackColor = System.Drawing.Color.Gainsboro;
			this.groupBox2.Controls.Add(this.GreenLogRadioBtn);
			this.groupBox2.Controls.Add(this.label7);
			this.groupBox2.Controls.Add(this.GreenMaxCutOffLabel);
			this.groupBox2.Controls.Add(this.GreenMinCutOffLabel);
			this.groupBox2.Controls.Add(this.GreenSquaredRadioBtn);
			this.groupBox2.Controls.Add(this.GreenSqrtRadioBtn);
			this.groupBox2.Controls.Add(this.GreenLinearRadioBtn);
			this.groupBox2.Controls.Add(this.GreenMaxScrollBar);
			this.groupBox2.Controls.Add(this.GreenMinScrollBar);
			this.groupBox2.Location = new System.Drawing.Point(12, 134);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(340, 116);
			this.groupBox2.TabIndex = 2;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Green Channel";
			// 
			// GreenLogRadioBtn
			// 
			this.GreenLogRadioBtn.AutoSize = true;
			this.GreenLogRadioBtn.Location = new System.Drawing.Point(279, 86);
			this.GreenLogRadioBtn.Name = "GreenLogRadioBtn";
			this.GreenLogRadioBtn.Size = new System.Drawing.Size(43, 17);
			this.GreenLogRadioBtn.TabIndex = 23;
			this.GreenLogRadioBtn.Text = "Log";
			this.GreenLogRadioBtn.UseVisualStyleBackColor = true;
			this.GreenLogRadioBtn.CheckedChanged += new System.EventHandler(this.GreenLogRadioBtn_CheckedChanged);
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(6, 86);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(45, 13);
			this.label7.TabIndex = 26;
			this.label7.Text = "Scaling:";
			// 
			// GreenMaxCutOffLabel
			// 
			this.GreenMaxCutOffLabel.AutoSize = true;
			this.GreenMaxCutOffLabel.Location = new System.Drawing.Point(141, 44);
			this.GreenMaxCutOffLabel.Name = "GreenMaxCutOffLabel";
			this.GreenMaxCutOffLabel.Size = new System.Drawing.Size(58, 13);
			this.GreenMaxCutOffLabel.TabIndex = 25;
			this.GreenMaxCutOffLabel.Text = "Max Cutoff";
			// 
			// GreenMinCutOffLabel
			// 
			this.GreenMinCutOffLabel.AutoSize = true;
			this.GreenMinCutOffLabel.Location = new System.Drawing.Point(143, 14);
			this.GreenMinCutOffLabel.Name = "GreenMinCutOffLabel";
			this.GreenMinCutOffLabel.Size = new System.Drawing.Size(55, 13);
			this.GreenMinCutOffLabel.TabIndex = 24;
			this.GreenMinCutOffLabel.Text = "Min Cutoff";
			// 
			// GreenSquaredRadioBtn
			// 
			this.GreenSquaredRadioBtn.AutoSize = true;
			this.GreenSquaredRadioBtn.Location = new System.Drawing.Point(208, 85);
			this.GreenSquaredRadioBtn.Name = "GreenSquaredRadioBtn";
			this.GreenSquaredRadioBtn.Size = new System.Drawing.Size(65, 17);
			this.GreenSquaredRadioBtn.TabIndex = 22;
			this.GreenSquaredRadioBtn.Text = "Squared";
			this.GreenSquaredRadioBtn.UseVisualStyleBackColor = true;
			this.GreenSquaredRadioBtn.CheckedChanged += new System.EventHandler(this.GreenSquaredRadioBtn_CheckedChanged);
			// 
			// GreenSqrtRadioBtn
			// 
			this.GreenSqrtRadioBtn.AutoSize = true;
			this.GreenSqrtRadioBtn.Location = new System.Drawing.Point(117, 85);
			this.GreenSqrtRadioBtn.Name = "GreenSqrtRadioBtn";
			this.GreenSqrtRadioBtn.Size = new System.Drawing.Size(85, 17);
			this.GreenSqrtRadioBtn.TabIndex = 21;
			this.GreenSqrtRadioBtn.Text = "Square Root";
			this.GreenSqrtRadioBtn.UseVisualStyleBackColor = true;
			this.GreenSqrtRadioBtn.CheckedChanged += new System.EventHandler(this.GreenSqrtRadioBtn_CheckedChanged);
			// 
			// GreenLinearRadioBtn
			// 
			this.GreenLinearRadioBtn.AutoSize = true;
			this.GreenLinearRadioBtn.Checked = true;
			this.GreenLinearRadioBtn.Location = new System.Drawing.Point(57, 85);
			this.GreenLinearRadioBtn.Name = "GreenLinearRadioBtn";
			this.GreenLinearRadioBtn.Size = new System.Drawing.Size(54, 17);
			this.GreenLinearRadioBtn.TabIndex = 20;
			this.GreenLinearRadioBtn.TabStop = true;
			this.GreenLinearRadioBtn.Text = "Linear";
			this.GreenLinearRadioBtn.UseVisualStyleBackColor = true;
			this.GreenLinearRadioBtn.CheckedChanged += new System.EventHandler(this.GreenLinearRadioBtn_CheckedChanged);
			// 
			// GreenMaxScrollBar
			// 
			this.GreenMaxScrollBar.Location = new System.Drawing.Point(9, 57);
			this.GreenMaxScrollBar.Name = "GreenMaxScrollBar";
			this.GreenMaxScrollBar.Size = new System.Drawing.Size(322, 17);
			this.GreenMaxScrollBar.TabIndex = 19;
			this.GreenMaxScrollBar.Value = 100;
			this.GreenMaxScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.GreenMaxScrollBar_Scroll);
			// 
			// GreenMinScrollBar
			// 
			this.GreenMinScrollBar.Location = new System.Drawing.Point(9, 27);
			this.GreenMinScrollBar.Name = "GreenMinScrollBar";
			this.GreenMinScrollBar.Size = new System.Drawing.Size(322, 17);
			this.GreenMinScrollBar.TabIndex = 18;
			this.GreenMinScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.GreenMinScrollBar_Scroll);
			// 
			// groupBox3
			// 
			this.groupBox3.BackColor = System.Drawing.Color.Gainsboro;
			this.groupBox3.Controls.Add(this.BlueLogRadioBtn);
			this.groupBox3.Controls.Add(this.label19);
			this.groupBox3.Controls.Add(this.BlueMaxCutOffLabel);
			this.groupBox3.Controls.Add(this.BlueMinCutOffLabel);
			this.groupBox3.Controls.Add(this.BlueSquaredRadioBtn);
			this.groupBox3.Controls.Add(this.BlueSqrtRadioBtn);
			this.groupBox3.Controls.Add(this.BlueLinearRadioBtn);
			this.groupBox3.Controls.Add(this.BlueMaxScrollBar);
			this.groupBox3.Controls.Add(this.BlueMinScrollBar);
			this.groupBox3.Location = new System.Drawing.Point(12, 256);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(340, 116);
			this.groupBox3.TabIndex = 3;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Blue Channel";
			// 
			// BlueLogRadioBtn
			// 
			this.BlueLogRadioBtn.AutoSize = true;
			this.BlueLogRadioBtn.Location = new System.Drawing.Point(279, 86);
			this.BlueLogRadioBtn.Name = "BlueLogRadioBtn";
			this.BlueLogRadioBtn.Size = new System.Drawing.Size(43, 17);
			this.BlueLogRadioBtn.TabIndex = 23;
			this.BlueLogRadioBtn.Text = "Log";
			this.BlueLogRadioBtn.UseVisualStyleBackColor = true;
			this.BlueLogRadioBtn.CheckedChanged += new System.EventHandler(this.BlueLogRadioBtn_CheckedChanged);
			// 
			// label19
			// 
			this.label19.AutoSize = true;
			this.label19.Location = new System.Drawing.Point(6, 86);
			this.label19.Name = "label19";
			this.label19.Size = new System.Drawing.Size(45, 13);
			this.label19.TabIndex = 26;
			this.label19.Text = "Scaling:";
			// 
			// BlueMaxCutOffLabel
			// 
			this.BlueMaxCutOffLabel.AutoSize = true;
			this.BlueMaxCutOffLabel.Location = new System.Drawing.Point(141, 44);
			this.BlueMaxCutOffLabel.Name = "BlueMaxCutOffLabel";
			this.BlueMaxCutOffLabel.Size = new System.Drawing.Size(58, 13);
			this.BlueMaxCutOffLabel.TabIndex = 25;
			this.BlueMaxCutOffLabel.Text = "Max Cutoff";
			// 
			// BlueMinCutOffLabel
			// 
			this.BlueMinCutOffLabel.AutoSize = true;
			this.BlueMinCutOffLabel.Location = new System.Drawing.Point(143, 14);
			this.BlueMinCutOffLabel.Name = "BlueMinCutOffLabel";
			this.BlueMinCutOffLabel.Size = new System.Drawing.Size(55, 13);
			this.BlueMinCutOffLabel.TabIndex = 24;
			this.BlueMinCutOffLabel.Text = "Min Cutoff";
			// 
			// BlueSquaredRadioBtn
			// 
			this.BlueSquaredRadioBtn.AutoSize = true;
			this.BlueSquaredRadioBtn.Location = new System.Drawing.Point(208, 85);
			this.BlueSquaredRadioBtn.Name = "BlueSquaredRadioBtn";
			this.BlueSquaredRadioBtn.Size = new System.Drawing.Size(65, 17);
			this.BlueSquaredRadioBtn.TabIndex = 22;
			this.BlueSquaredRadioBtn.Text = "Squared";
			this.BlueSquaredRadioBtn.UseVisualStyleBackColor = true;
			this.BlueSquaredRadioBtn.CheckedChanged += new System.EventHandler(this.BlueSquaredRadioBtn_CheckedChanged);
			// 
			// BlueSqrtRadioBtn
			// 
			this.BlueSqrtRadioBtn.AutoSize = true;
			this.BlueSqrtRadioBtn.Location = new System.Drawing.Point(117, 85);
			this.BlueSqrtRadioBtn.Name = "BlueSqrtRadioBtn";
			this.BlueSqrtRadioBtn.Size = new System.Drawing.Size(85, 17);
			this.BlueSqrtRadioBtn.TabIndex = 21;
			this.BlueSqrtRadioBtn.Text = "Square Root";
			this.BlueSqrtRadioBtn.UseVisualStyleBackColor = true;
			this.BlueSqrtRadioBtn.CheckedChanged += new System.EventHandler(this.BlueSqrtRadioBtn_CheckedChanged);
			// 
			// BlueLinearRadioBtn
			// 
			this.BlueLinearRadioBtn.AutoSize = true;
			this.BlueLinearRadioBtn.Checked = true;
			this.BlueLinearRadioBtn.Location = new System.Drawing.Point(57, 85);
			this.BlueLinearRadioBtn.Name = "BlueLinearRadioBtn";
			this.BlueLinearRadioBtn.Size = new System.Drawing.Size(54, 17);
			this.BlueLinearRadioBtn.TabIndex = 20;
			this.BlueLinearRadioBtn.TabStop = true;
			this.BlueLinearRadioBtn.Text = "Linear";
			this.BlueLinearRadioBtn.UseVisualStyleBackColor = true;
			this.BlueLinearRadioBtn.CheckedChanged += new System.EventHandler(this.BlueLinearRadioBtn_CheckedChanged);
			// 
			// BlueMaxScrollBar
			// 
			this.BlueMaxScrollBar.Location = new System.Drawing.Point(9, 57);
			this.BlueMaxScrollBar.Name = "BlueMaxScrollBar";
			this.BlueMaxScrollBar.Size = new System.Drawing.Size(322, 17);
			this.BlueMaxScrollBar.TabIndex = 19;
			this.BlueMaxScrollBar.Value = 100;
			this.BlueMaxScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.BlueMaxScrollBar_Scroll);
			// 
			// BlueMinScrollBar
			// 
			this.BlueMinScrollBar.Location = new System.Drawing.Point(9, 27);
			this.BlueMinScrollBar.Name = "BlueMinScrollBar";
			this.BlueMinScrollBar.Size = new System.Drawing.Size(322, 17);
			this.BlueMinScrollBar.TabIndex = 18;
			this.BlueMinScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.BlueMinScrollBar_Scroll);
			// 
			// SaveImageBtn
			// 
			this.SaveImageBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.SaveImageBtn.Location = new System.Drawing.Point(278, 424);
			this.SaveImageBtn.Name = "SaveImageBtn";
			this.SaveImageBtn.Size = new System.Drawing.Size(75, 23);
			this.SaveImageBtn.TabIndex = 4;
			this.SaveImageBtn.Text = "Save Image";
			this.SaveImageBtn.UseVisualStyleBackColor = true;
			this.SaveImageBtn.Click += new System.EventHandler(this.SaveImageBtn_Click);
			// 
			// groupBox4
			// 
			this.groupBox4.Controls.Add(this.label2);
			this.groupBox4.Controls.Add(this.MinStdvTextBox);
			this.groupBox4.Controls.Add(this.FullContrastChck);
			this.groupBox4.Controls.Add(this.MaxStdvTextBox);
			this.groupBox4.Controls.Add(this.WideContrastChck);
			this.groupBox4.Controls.Add(this.DarkContrastChck);
			this.groupBox4.Controls.Add(this.label1);
			this.groupBox4.Location = new System.Drawing.Point(12, 378);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(126, 102);
			this.groupBox4.TabIndex = 5;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Global Contrast Limits";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(68, 59);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(52, 13);
			this.label2.TabIndex = 24;
			this.label2.Text = "Max Stdv";
			// 
			// MinStdvTextBox
			// 
			this.MinStdvTextBox.Location = new System.Drawing.Point(69, 36);
			this.MinStdvTextBox.Name = "MinStdvTextBox";
			this.MinStdvTextBox.Size = new System.Drawing.Size(48, 20);
			this.MinStdvTextBox.TabIndex = 26;
			this.toolTip1.SetToolTip(this.MinStdvTextBox, "Number of standard deviations BELOW image mean");
			this.MinStdvTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MaxStdvTextBox_KeyDown);
			// 
			// FullContrastChck
			// 
			this.FullContrastChck.AutoSize = true;
			this.FullContrastChck.Location = new System.Drawing.Point(9, 71);
			this.FullContrastChck.Name = "FullContrastChck";
			this.FullContrastChck.Size = new System.Drawing.Size(41, 17);
			this.FullContrastChck.TabIndex = 23;
			this.FullContrastChck.Text = "Full";
			this.FullContrastChck.UseVisualStyleBackColor = true;
			this.FullContrastChck.CheckedChanged += new System.EventHandler(this.FullContrastChck_CheckedChanged);
			// 
			// MaxStdvTextBox
			// 
			this.MaxStdvTextBox.Location = new System.Drawing.Point(69, 75);
			this.MaxStdvTextBox.Name = "MaxStdvTextBox";
			this.MaxStdvTextBox.Size = new System.Drawing.Size(48, 20);
			this.MaxStdvTextBox.TabIndex = 25;
			this.toolTip1.SetToolTip(this.MaxStdvTextBox, "Number of standard deviations ABOVE image mean");
			this.MaxStdvTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MaxStdvTextBox_KeyDown);
			// 
			// WideContrastChck
			// 
			this.WideContrastChck.AutoSize = true;
			this.WideContrastChck.Location = new System.Drawing.Point(9, 48);
			this.WideContrastChck.Name = "WideContrastChck";
			this.WideContrastChck.Size = new System.Drawing.Size(50, 17);
			this.WideContrastChck.TabIndex = 22;
			this.WideContrastChck.Text = "Wide";
			this.WideContrastChck.UseVisualStyleBackColor = true;
			this.WideContrastChck.CheckedChanged += new System.EventHandler(this.WideContrastChck_CheckedChanged);
			// 
			// DarkContrastChck
			// 
			this.DarkContrastChck.AutoSize = true;
			this.DarkContrastChck.Checked = true;
			this.DarkContrastChck.Location = new System.Drawing.Point(9, 25);
			this.DarkContrastChck.Name = "DarkContrastChck";
			this.DarkContrastChck.Size = new System.Drawing.Size(48, 17);
			this.DarkContrastChck.TabIndex = 21;
			this.DarkContrastChck.TabStop = true;
			this.DarkContrastChck.Text = "Dark";
			this.DarkContrastChck.UseVisualStyleBackColor = true;
			this.DarkContrastChck.CheckedChanged += new System.EventHandler(this.DarkContrastChck_CheckedChanged);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(68, 20);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(49, 13);
			this.label1.TabIndex = 23;
			this.label1.Text = "Min Stdv";
			// 
			// LoadSaveDropDown
			// 
			this.LoadSaveDropDown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.LoadSaveDropDown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.LoadSaveDropDown.FormattingEnabled = true;
			this.LoadSaveDropDown.Items.AddRange(new object[] {
            "Load Settings",
            "Save Settings"});
			this.LoadSaveDropDown.Location = new System.Drawing.Point(262, 397);
			this.LoadSaveDropDown.Name = "LoadSaveDropDown";
			this.LoadSaveDropDown.Size = new System.Drawing.Size(90, 21);
			this.LoadSaveDropDown.TabIndex = 6;
			this.LoadSaveDropDown.Visible = false;
			// 
			// groupBox5
			// 
			this.groupBox5.Controls.Add(this.GlobalLogRadioBtn);
			this.groupBox5.Controls.Add(this.GlobalSquaredRadioBtn);
			this.groupBox5.Controls.Add(this.GlobalSqrtRadioBtn);
			this.groupBox5.Controls.Add(this.GlobalLinearRadioBtn);
			this.groupBox5.Location = new System.Drawing.Point(144, 380);
			this.groupBox5.Name = "groupBox5";
			this.groupBox5.Size = new System.Drawing.Size(96, 100);
			this.groupBox5.TabIndex = 7;
			this.groupBox5.TabStop = false;
			this.groupBox5.Text = "Global Scaling";
			// 
			// GlobalLogRadioBtn
			// 
			this.GlobalLogRadioBtn.AutoSize = true;
			this.GlobalLogRadioBtn.Location = new System.Drawing.Point(6, 79);
			this.GlobalLogRadioBtn.Name = "GlobalLogRadioBtn";
			this.GlobalLogRadioBtn.Size = new System.Drawing.Size(43, 17);
			this.GlobalLogRadioBtn.TabIndex = 24;
			this.GlobalLogRadioBtn.Text = "Log";
			this.GlobalLogRadioBtn.UseVisualStyleBackColor = true;
			this.GlobalLogRadioBtn.CheckedChanged += new System.EventHandler(this.GlobalLogRadioBtn_CheckedChanged);
			// 
			// GlobalSquaredRadioBtn
			// 
			this.GlobalSquaredRadioBtn.AutoSize = true;
			this.GlobalSquaredRadioBtn.Location = new System.Drawing.Point(6, 58);
			this.GlobalSquaredRadioBtn.Name = "GlobalSquaredRadioBtn";
			this.GlobalSquaredRadioBtn.Size = new System.Drawing.Size(65, 17);
			this.GlobalSquaredRadioBtn.TabIndex = 23;
			this.GlobalSquaredRadioBtn.Text = "Squared";
			this.GlobalSquaredRadioBtn.UseVisualStyleBackColor = true;
			this.GlobalSquaredRadioBtn.CheckedChanged += new System.EventHandler(this.GlobalSquaredRadioBtn_CheckedChanged);
			// 
			// GlobalSqrtRadioBtn
			// 
			this.GlobalSqrtRadioBtn.AutoSize = true;
			this.GlobalSqrtRadioBtn.Location = new System.Drawing.Point(6, 37);
			this.GlobalSqrtRadioBtn.Name = "GlobalSqrtRadioBtn";
			this.GlobalSqrtRadioBtn.Size = new System.Drawing.Size(85, 17);
			this.GlobalSqrtRadioBtn.TabIndex = 22;
			this.GlobalSqrtRadioBtn.Text = "Square Root";
			this.GlobalSqrtRadioBtn.UseVisualStyleBackColor = true;
			this.GlobalSqrtRadioBtn.CheckedChanged += new System.EventHandler(this.GlobalSqrtRadioBtn_CheckedChanged);
			// 
			// GlobalLinearRadioBtn
			// 
			this.GlobalLinearRadioBtn.AutoSize = true;
			this.GlobalLinearRadioBtn.Location = new System.Drawing.Point(6, 16);
			this.GlobalLinearRadioBtn.Name = "GlobalLinearRadioBtn";
			this.GlobalLinearRadioBtn.Size = new System.Drawing.Size(54, 17);
			this.GlobalLinearRadioBtn.TabIndex = 21;
			this.GlobalLinearRadioBtn.Text = "Linear";
			this.GlobalLinearRadioBtn.UseVisualStyleBackColor = true;
			this.GlobalLinearRadioBtn.CheckedChanged += new System.EventHandler(this.GlobalLinearRadioBtn_CheckedChanged);
			// 
			// ColorImageCreator
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(364, 488);
			this.Controls.Add(this.groupBox5);
			this.Controls.Add(this.LoadSaveDropDown);
			this.Controls.Add(this.groupBox4);
			this.Controls.Add(this.SaveImageBtn);
			this.Controls.Add(this.groupBox3);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.CancelBtn);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "ColorImageCreator";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.Text = "Color Image Creator";
			this.TopMost = true;
			this.Load += new System.EventHandler(this.ColorImageCreator_Load);
			this.Shown += new System.EventHandler(this.ColorImageCreator_Shown);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			this.groupBox4.ResumeLayout(false);
			this.groupBox4.PerformLayout();
			this.groupBox5.ResumeLayout(false);
			this.groupBox5.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button CancelBtn;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.HScrollBar RedMaxScrollBar;
		private System.Windows.Forms.HScrollBar RedMinScrollBar;
		private System.Windows.Forms.RadioButton RedSquaredRadioBtn;
		private System.Windows.Forms.RadioButton RedSqrtRadioBtn;
		private System.Windows.Forms.RadioButton RedLinearRadioBtn;
		private System.Windows.Forms.Button SaveImageBtn;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Label RedMaxCutOffLabel;
		private System.Windows.Forms.Label RedMinCutOffLabel;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.RadioButton RedLogRadioBtn;
		private System.Windows.Forms.RadioButton GreenLogRadioBtn;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label GreenMaxCutOffLabel;
		private System.Windows.Forms.Label GreenMinCutOffLabel;
		private System.Windows.Forms.RadioButton GreenSquaredRadioBtn;
		private System.Windows.Forms.RadioButton GreenSqrtRadioBtn;
		private System.Windows.Forms.RadioButton GreenLinearRadioBtn;
		private System.Windows.Forms.HScrollBar GreenMaxScrollBar;
		private System.Windows.Forms.HScrollBar GreenMinScrollBar;
		private System.Windows.Forms.RadioButton BlueLogRadioBtn;
		private System.Windows.Forms.Label label19;
		private System.Windows.Forms.Label BlueMaxCutOffLabel;
		private System.Windows.Forms.Label BlueMinCutOffLabel;
		private System.Windows.Forms.RadioButton BlueSquaredRadioBtn;
		private System.Windows.Forms.RadioButton BlueSqrtRadioBtn;
		private System.Windows.Forms.RadioButton BlueLinearRadioBtn;
		private System.Windows.Forms.HScrollBar BlueMaxScrollBar;
		private System.Windows.Forms.HScrollBar BlueMinScrollBar;
		private System.Windows.Forms.ComboBox LoadSaveDropDown;
		private System.Windows.Forms.RadioButton WideContrastChck;
		private System.Windows.Forms.RadioButton DarkContrastChck;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox MinStdvTextBox;
		private System.Windows.Forms.TextBox MaxStdvTextBox;
		private System.Windows.Forms.RadioButton FullContrastChck;
		private System.Windows.Forms.GroupBox groupBox5;
		private System.Windows.Forms.RadioButton GlobalLogRadioBtn;
		private System.Windows.Forms.RadioButton GlobalSquaredRadioBtn;
		private System.Windows.Forms.RadioButton GlobalSqrtRadioBtn;
		private System.Windows.Forms.RadioButton GlobalLinearRadioBtn;
		private System.Windows.Forms.ToolTip toolTip1;
	}
}