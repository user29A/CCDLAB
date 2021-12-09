namespace CCDLAB
{
	partial class About
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
			this.AboutTextLabel = new System.Windows.Forms.Label();
			this.DevTextBox = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// AboutTextLabel
			// 
			this.AboutTextLabel.AutoSize = true;
			this.AboutTextLabel.Location = new System.Drawing.Point(12, 9);
			this.AboutTextLabel.MaximumSize = new System.Drawing.Size(500, 0);
			this.AboutTextLabel.Name = "AboutTextLabel";
			this.AboutTextLabel.Size = new System.Drawing.Size(35, 13);
			this.AboutTextLabel.TabIndex = 1;
			this.AboutTextLabel.Text = "label1";
			// 
			// DevTextBox
			// 
			this.DevTextBox.Location = new System.Drawing.Point(131, 404);
			this.DevTextBox.Name = "DevTextBox";
			this.DevTextBox.Size = new System.Drawing.Size(302, 20);
			this.DevTextBox.TabIndex = 2;
			this.DevTextBox.Visible = false;
			this.DevTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.DevTextBox_KeyDown);
			// 
			// About
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(577, 497);
			this.Controls.Add(this.DevTextBox);
			this.Controls.Add(this.AboutTextLabel);
			this.Name = "About";
			this.ShowIcon = false;
			this.Text = "About";
			this.Load += new System.EventHandler(this.About_Load);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.About_KeyDown);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		public System.Windows.Forms.Label AboutTextLabel;
		private System.Windows.Forms.TextBox DevTextBox;
	}
}