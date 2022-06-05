namespace CCDLAB
{
	partial class RangeDlg
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
			this.CancelBtn = new System.Windows.Forms.Button();
			this.OKBtn = new System.Windows.Forms.Button();
			this.XEndLabel = new System.Windows.Forms.Label();
			this.YStartLabel = new System.Windows.Forms.Label();
			this.YEndLabel = new System.Windows.Forms.Label();
			this.XStartLabel = new System.Windows.Forms.Label();
			this.YStartUpD = new System.Windows.Forms.NumericUpDown();
			this.YEndUpD = new System.Windows.Forms.NumericUpDown();
			this.XEndUpD = new System.Windows.Forms.NumericUpDown();
			this.XStartUpD = new System.Windows.Forms.NumericUpDown();
			((System.ComponentModel.ISupportInitialize)(this.YStartUpD)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.YEndUpD)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.XEndUpD)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.XStartUpD)).BeginInit();
			this.SuspendLayout();
			// 
			// CancelBtn
			// 
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(484, 83);
			this.CancelBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(112, 35);
			this.CancelBtn.TabIndex = 19;
			this.CancelBtn.Text = "Cancel";
			this.CancelBtn.UseVisualStyleBackColor = true;
			// 
			// OKBtn
			// 
			this.OKBtn.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.OKBtn.Location = new System.Drawing.Point(484, 32);
			this.OKBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.OKBtn.Name = "OKBtn";
			this.OKBtn.Size = new System.Drawing.Size(112, 35);
			this.OKBtn.TabIndex = 18;
			this.OKBtn.Text = "OK";
			this.OKBtn.UseVisualStyleBackColor = true;
			this.OKBtn.Click += new System.EventHandler(this.OKBtn_Click);
			// 
			// XEndLabel
			// 
			this.XEndLabel.AutoSize = true;
			this.XEndLabel.Location = new System.Drawing.Point(243, 38);
			this.XEndLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.XEndLabel.Name = "XEndLabel";
			this.XEndLabel.Size = new System.Drawing.Size(49, 20);
			this.XEndLabel.TabIndex = 17;
			this.XEndLabel.Text = "XEnd";
			// 
			// YStartLabel
			// 
			this.YStartLabel.AutoSize = true;
			this.YStartLabel.Location = new System.Drawing.Point(30, 86);
			this.YStartLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.YStartLabel.Name = "YStartLabel";
			this.YStartLabel.Size = new System.Drawing.Size(55, 20);
			this.YStartLabel.TabIndex = 16;
			this.YStartLabel.Text = "YStart";
			// 
			// YEndLabel
			// 
			this.YEndLabel.AutoSize = true;
			this.YEndLabel.Location = new System.Drawing.Point(243, 89);
			this.YEndLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.YEndLabel.Name = "YEndLabel";
			this.YEndLabel.Size = new System.Drawing.Size(49, 20);
			this.YEndLabel.TabIndex = 15;
			this.YEndLabel.Text = "YEnd";
			// 
			// XStartLabel
			// 
			this.XStartLabel.AutoSize = true;
			this.XStartLabel.Location = new System.Drawing.Point(30, 38);
			this.XStartLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.XStartLabel.Name = "XStartLabel";
			this.XStartLabel.Size = new System.Drawing.Size(55, 20);
			this.XStartLabel.TabIndex = 14;
			this.XStartLabel.Text = "XStart";
			// 
			// YStartUpD
			// 
			this.YStartUpD.Location = new System.Drawing.Point(93, 83);
			this.YStartUpD.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.YStartUpD.Maximum = new decimal(new int[] {
            -2147483648,
            0,
            0,
            0});
			this.YStartUpD.Name = "YStartUpD";
			this.YStartUpD.Size = new System.Drawing.Size(120, 26);
			this.YStartUpD.TabIndex = 13;
			// 
			// YEndUpD
			// 
			this.YEndUpD.Location = new System.Drawing.Point(306, 83);
			this.YEndUpD.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.YEndUpD.Maximum = new decimal(new int[] {
            -2147483648,
            0,
            0,
            0});
			this.YEndUpD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			this.YEndUpD.Name = "YEndUpD";
			this.YEndUpD.Size = new System.Drawing.Size(118, 26);
			this.YEndUpD.TabIndex = 12;
			this.YEndUpD.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			// 
			// XEndUpD
			// 
			this.XEndUpD.Location = new System.Drawing.Point(304, 32);
			this.XEndUpD.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.XEndUpD.Maximum = new decimal(new int[] {
            -2147483648,
            0,
            0,
            0});
			this.XEndUpD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			this.XEndUpD.Name = "XEndUpD";
			this.XEndUpD.Size = new System.Drawing.Size(120, 26);
			this.XEndUpD.TabIndex = 11;
			this.XEndUpD.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			// 
			// XStartUpD
			// 
			this.XStartUpD.Location = new System.Drawing.Point(93, 32);
			this.XStartUpD.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.XStartUpD.Maximum = new decimal(new int[] {
            -2147483648,
            0,
            0,
            0});
			this.XStartUpD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			this.XStartUpD.Name = "XStartUpD";
			this.XStartUpD.Size = new System.Drawing.Size(120, 26);
			this.XStartUpD.TabIndex = 10;
			this.XStartUpD.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			// 
			// RangeDlg
			// 
			this.AcceptButton = this.OKBtn;
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(628, 152);
			this.Controls.Add(this.CancelBtn);
			this.Controls.Add(this.OKBtn);
			this.Controls.Add(this.XEndLabel);
			this.Controls.Add(this.YStartLabel);
			this.Controls.Add(this.YEndLabel);
			this.Controls.Add(this.XStartLabel);
			this.Controls.Add(this.YStartUpD);
			this.Controls.Add(this.YEndUpD);
			this.Controls.Add(this.XEndUpD);
			this.Controls.Add(this.XStartUpD);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.HelpButton = true;
			this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RangeDlg";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Specify ZERO-BASED Image Range";
			this.TopMost = true;
			this.HelpButtonClicked += new System.ComponentModel.CancelEventHandler(this.RangeDlg_HelpButtonClicked);
			this.Load += new System.EventHandler(this.RangeDlg_Load);
			((System.ComponentModel.ISupportInitialize)(this.YStartUpD)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.YEndUpD)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.XEndUpD)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.XStartUpD)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button CancelBtn;
		private System.Windows.Forms.Button OKBtn;
		private System.Windows.Forms.Label XEndLabel;
		private System.Windows.Forms.Label YStartLabel;
		private System.Windows.Forms.Label YEndLabel;
		private System.Windows.Forms.Label XStartLabel;
		public System.Windows.Forms.NumericUpDown YStartUpD;
		public System.Windows.Forms.NumericUpDown YEndUpD;
		public System.Windows.Forms.NumericUpDown XEndUpD;
		public System.Windows.Forms.NumericUpDown XStartUpD;
	}
}