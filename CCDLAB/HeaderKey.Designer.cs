namespace CCDLAB
{
	partial class HeaderKey
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
			this.label1 = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(35, 30);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(170, 13);
			this.label1.TabIndex = 3;
			this.label1.Text = "Please Enter the Header Keyword:";
			// 
			// textBox1
			// 
			this.textBox1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBox1.Location = new System.Drawing.Point(86, 52);
			this.textBox1.MaxLength = 8;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(68, 20);
			this.textBox1.TabIndex = 2;
			this.textBox1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox1_KeyDown);
			// 
			// HeaderKey
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(241, 102);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textBox1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MinimizeBox = false;
			this.Name = "HeaderKey";
			this.ShowIcon = false;
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Enter Header Key";
			this.TopMost = true;
			this.Load += new System.EventHandler(this.HeaderKey_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		public System.Windows.Forms.TextBox textBox1;
	}
}