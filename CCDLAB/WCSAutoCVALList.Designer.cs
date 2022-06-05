namespace CCDLAB
{
	partial class WCSAutoCVALList
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
			this.SearchTxtBox = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.WCDrop = new System.Windows.Forms.ComboBox();
			this.CancelBtn = new System.Windows.Forms.Button();
			this.OKBtn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// SearchTxtBox
			// 
			this.SearchTxtBox.Location = new System.Drawing.Point(62, 14);
			this.SearchTxtBox.Name = "SearchTxtBox";
			this.SearchTxtBox.Size = new System.Drawing.Size(100, 20);
			this.SearchTxtBox.TabIndex = 9;
			this.SearchTxtBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.SearchTxtBox_MouseClick);
			this.SearchTxtBox.TextChanged += new System.EventHandler(this.SearchTxtBox_TextChanged);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(18, 17);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(44, 13);
			this.label1.TabIndex = 8;
			this.label1.Text = "Search:";
			// 
			// WCDrop
			// 
			this.WCDrop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.WCDrop.FormattingEnabled = true;
			this.WCDrop.Location = new System.Drawing.Point(21, 39);
			this.WCDrop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.WCDrop.Name = "WCDrop";
			this.WCDrop.Size = new System.Drawing.Size(180, 21);
			this.WCDrop.TabIndex = 5;
			this.WCDrop.SelectedIndexChanged += new System.EventHandler(this.WCDrop_SelectedIndexChanged);
			// 
			// CancelBtn
			// 
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(137, 43);
			this.CancelBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(52, 18);
			this.CancelBtn.TabIndex = 7;
			this.CancelBtn.Text = "Cancel";
			this.CancelBtn.UseVisualStyleBackColor = true;
			this.CancelBtn.Click += new System.EventHandler(this.CancelBtn_Click);
			// 
			// OKBtn
			// 
			this.OKBtn.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.OKBtn.Location = new System.Drawing.Point(37, 43);
			this.OKBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.OKBtn.Name = "OKBtn";
			this.OKBtn.Size = new System.Drawing.Size(58, 18);
			this.OKBtn.TabIndex = 6;
			this.OKBtn.Text = "OK";
			this.OKBtn.UseVisualStyleBackColor = true;
			this.OKBtn.Click += new System.EventHandler(this.OKBtn_Click);
			// 
			// WCSAutoCVALList1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(219, 75);
			this.ControlBox = false;
			this.Controls.Add(this.WCDrop);
			this.Controls.Add(this.SearchTxtBox);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.CancelBtn);
			this.Controls.Add(this.OKBtn);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "WCSAutoCVALList1";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Select WC";
			this.Shown += new System.EventHandler(this.WCSAutoCVALList1_Shown);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox SearchTxtBox;
		private System.Windows.Forms.Label label1;
		public System.Windows.Forms.ComboBox WCDrop;
		private System.Windows.Forms.Button CancelBtn;
		private System.Windows.Forms.Button OKBtn;
	}
}