namespace CCDLAB
{
	partial class UVSortRegisterFilesForm
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
			this.FileList = new System.Windows.Forms.ListBox();
			this.SortAlphabeticalBtn = new System.Windows.Forms.Button();
			this.SortReverseBtn = new System.Windows.Forms.Button();
			this.MoveTopBtn = new System.Windows.Forms.Button();
			this.MoveBottomBtn = new System.Windows.Forms.Button();
			this.MoveDownBtn = new System.Windows.Forms.Button();
			this.MoveUpBtn = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.CancelBtn = new System.Windows.Forms.Button();
			this.OKBtn = new System.Windows.Forms.Button();
			this.SortExpTimeBtn = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// FileList
			// 
			this.FileList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.FileList.BackColor = System.Drawing.Color.LightGray;
			this.FileList.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.FileList.FormattingEnabled = true;
			this.FileList.HorizontalScrollbar = true;
			this.FileList.ItemHeight = 15;
			this.FileList.Location = new System.Drawing.Point(0, -1);
			this.FileList.Name = "FileList";
			this.FileList.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
			this.FileList.Size = new System.Drawing.Size(901, 529);
			this.FileList.TabIndex = 60;
			this.FileList.MouseUp += new System.Windows.Forms.MouseEventHandler(this.FileList_MouseUp);
			// 
			// SortAlphabeticalBtn
			// 
			this.SortAlphabeticalBtn.Location = new System.Drawing.Point(907, 12);
			this.SortAlphabeticalBtn.Name = "SortAlphabeticalBtn";
			this.SortAlphabeticalBtn.Size = new System.Drawing.Size(78, 23);
			this.SortAlphabeticalBtn.TabIndex = 61;
			this.SortAlphabeticalBtn.Text = "Alphabetical";
			this.SortAlphabeticalBtn.UseVisualStyleBackColor = true;
			this.SortAlphabeticalBtn.Click += new System.EventHandler(this.SortAlphabeticalBtn_Click);
			// 
			// SortReverseBtn
			// 
			this.SortReverseBtn.Location = new System.Drawing.Point(907, 70);
			this.SortReverseBtn.Name = "SortReverseBtn";
			this.SortReverseBtn.Size = new System.Drawing.Size(78, 23);
			this.SortReverseBtn.TabIndex = 62;
			this.SortReverseBtn.Text = "Reverse";
			this.SortReverseBtn.UseVisualStyleBackColor = true;
			this.SortReverseBtn.Click += new System.EventHandler(this.SortReverseBtn_Click);
			// 
			// MoveTopBtn
			// 
			this.MoveTopBtn.Location = new System.Drawing.Point(2, 11);
			this.MoveTopBtn.Name = "MoveTopBtn";
			this.MoveTopBtn.Size = new System.Drawing.Size(78, 23);
			this.MoveTopBtn.TabIndex = 63;
			this.MoveTopBtn.Text = "Move Top";
			this.MoveTopBtn.UseVisualStyleBackColor = true;
			this.MoveTopBtn.Click += new System.EventHandler(this.MoveTopBtn_Click);
			// 
			// MoveBottomBtn
			// 
			this.MoveBottomBtn.Location = new System.Drawing.Point(2, 40);
			this.MoveBottomBtn.Name = "MoveBottomBtn";
			this.MoveBottomBtn.Size = new System.Drawing.Size(78, 23);
			this.MoveBottomBtn.TabIndex = 64;
			this.MoveBottomBtn.Text = "Move Bottom";
			this.MoveBottomBtn.UseVisualStyleBackColor = true;
			this.MoveBottomBtn.Click += new System.EventHandler(this.MoveBottomBtn_Click);
			// 
			// MoveDownBtn
			// 
			this.MoveDownBtn.Location = new System.Drawing.Point(2, 98);
			this.MoveDownBtn.Name = "MoveDownBtn";
			this.MoveDownBtn.Size = new System.Drawing.Size(78, 23);
			this.MoveDownBtn.TabIndex = 66;
			this.MoveDownBtn.Text = "Move Down";
			this.MoveDownBtn.UseVisualStyleBackColor = true;
			this.MoveDownBtn.Click += new System.EventHandler(this.MoveDownBtn_Click);
			// 
			// MoveUpBtn
			// 
			this.MoveUpBtn.Location = new System.Drawing.Point(2, 69);
			this.MoveUpBtn.Name = "MoveUpBtn";
			this.MoveUpBtn.Size = new System.Drawing.Size(78, 23);
			this.MoveUpBtn.TabIndex = 65;
			this.MoveUpBtn.Text = "Move Up";
			this.MoveUpBtn.UseVisualStyleBackColor = true;
			this.MoveUpBtn.Click += new System.EventHandler(this.MoveUpBtn_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.MoveDownBtn);
			this.groupBox1.Controls.Add(this.MoveTopBtn);
			this.groupBox1.Controls.Add(this.MoveUpBtn);
			this.groupBox1.Controls.Add(this.MoveBottomBtn);
			this.groupBox1.Enabled = false;
			this.groupBox1.Location = new System.Drawing.Point(907, 99);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(86, 126);
			this.groupBox1.TabIndex = 67;
			this.groupBox1.TabStop = false;
			// 
			// CancelBtn
			// 
			this.CancelBtn.BackColor = System.Drawing.Color.LightCoral;
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(907, 239);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(78, 23);
			this.CancelBtn.TabIndex = 68;
			this.CancelBtn.Text = "Cancel";
			this.CancelBtn.UseVisualStyleBackColor = false;
			// 
			// OKBtn
			// 
			this.OKBtn.BackColor = System.Drawing.Color.LightGreen;
			this.OKBtn.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.OKBtn.Location = new System.Drawing.Point(907, 268);
			this.OKBtn.Name = "OKBtn";
			this.OKBtn.Size = new System.Drawing.Size(78, 23);
			this.OKBtn.TabIndex = 69;
			this.OKBtn.Text = "OK";
			this.OKBtn.UseVisualStyleBackColor = false;
			this.OKBtn.Click += new System.EventHandler(this.OKBtn_Click);
			// 
			// SortExpTimeBtn
			// 
			this.SortExpTimeBtn.Location = new System.Drawing.Point(907, 41);
			this.SortExpTimeBtn.Name = "SortExpTimeBtn";
			this.SortExpTimeBtn.Size = new System.Drawing.Size(78, 23);
			this.SortExpTimeBtn.TabIndex = 70;
			this.SortExpTimeBtn.Text = "Exp Time";
			this.SortExpTimeBtn.UseVisualStyleBackColor = true;
			this.SortExpTimeBtn.Click += new System.EventHandler(this.SortExpTimeBtn_Click);
			// 
			// UVSortRegisterFilesForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(994, 536);
			this.Controls.Add(this.SortExpTimeBtn);
			this.Controls.Add(this.OKBtn);
			this.Controls.Add(this.CancelBtn);
			this.Controls.Add(this.SortReverseBtn);
			this.Controls.Add(this.SortAlphabeticalBtn);
			this.Controls.Add(this.FileList);
			this.Controls.Add(this.groupBox1);
			this.Name = "UVSortRegisterFilesForm";
			this.ShowIcon = false;
			this.Text = "UVIT Sort Registration Files";
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		public System.Windows.Forms.ListBox FileList;
		private System.Windows.Forms.Button SortAlphabeticalBtn;
		private System.Windows.Forms.Button SortReverseBtn;
		private System.Windows.Forms.Button MoveTopBtn;
		private System.Windows.Forms.Button MoveBottomBtn;
		private System.Windows.Forms.Button MoveDownBtn;
		private System.Windows.Forms.Button MoveUpBtn;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Button CancelBtn;
		private System.Windows.Forms.Button OKBtn;
		private System.Windows.Forms.Button SortExpTimeBtn;
	}
}