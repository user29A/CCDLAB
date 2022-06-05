namespace CCDLAB
{
	partial class PSETableViewer
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
			this.PSETable = new System.Windows.Forms.DataGridView();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.PSETableViewerSaveBtn = new System.Windows.Forms.ToolStripMenuItem();
			this.PSETableViewerCloseBtn = new System.Windows.Forms.ToolStripMenuItem();
			this.button1 = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.PSETable)).BeginInit();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// PSETable
			// 
			this.PSETable.AllowUserToOrderColumns = true;
			this.PSETable.ClipboardCopyMode = System.Windows.Forms.DataGridViewClipboardCopyMode.EnableWithoutHeaderText;
			this.PSETable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.PSETable.Dock = System.Windows.Forms.DockStyle.Fill;
			this.PSETable.Location = new System.Drawing.Point(0, 24);
			this.PSETable.Name = "PSETable";
			this.PSETable.Size = new System.Drawing.Size(1175, 482);
			this.PSETable.TabIndex = 3;
			this.PSETable.CellMouseDoubleClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.PSETable_CellMouseDoubleClick);
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(1175, 24);
			this.menuStrip1.TabIndex = 4;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.PSETableViewerSaveBtn,
            this.PSETableViewerCloseBtn});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// PSETableViewerSaveBtn
			// 
			this.PSETableViewerSaveBtn.Name = "PSETableViewerSaveBtn";
			this.PSETableViewerSaveBtn.Size = new System.Drawing.Size(180, 22);
			this.PSETableViewerSaveBtn.Text = "Save";
			this.PSETableViewerSaveBtn.Click += new System.EventHandler(this.PSETableViewerSaveBtn_Click);
			// 
			// PSETableViewerCloseBtn
			// 
			this.PSETableViewerCloseBtn.Name = "PSETableViewerCloseBtn";
			this.PSETableViewerCloseBtn.Size = new System.Drawing.Size(103, 22);
			this.PSETableViewerCloseBtn.Text = "Close";
			this.PSETableViewerCloseBtn.Visible = false;
			// 
			// button1
			// 
			this.button1.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.button1.Location = new System.Drawing.Point(12, 27);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 5;
			this.button1.Text = "button1";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// PSETableViewer
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.button1;
			this.ClientSize = new System.Drawing.Size(1175, 506);
			this.Controls.Add(this.PSETable);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.button1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "PSETableViewer";
			((System.ComponentModel.ISupportInitialize)(this.PSETable)).EndInit();
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		public System.Windows.Forms.DataGridView PSETable;
		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem PSETableViewerSaveBtn;
		private System.Windows.Forms.ToolStripMenuItem PSETableViewerCloseBtn;
		private System.Windows.Forms.Button button1;
	}
}