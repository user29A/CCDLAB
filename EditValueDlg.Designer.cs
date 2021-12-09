namespace CCDLAB
{
	partial class EditValueDlg
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
			this.EditValueTxt = new System.Windows.Forms.MaskedTextBox();
			this.CancelBtn = new System.Windows.Forms.Button();
			this.OkayBtn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(16, 15);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(165, 41);
			this.label1.TabIndex = 7;
			this.label1.Text = "Enter Value [begin with ! to change everything other than selection region of int" +
    "erest]";
			// 
			// EditValueTxt
			// 
			this.EditValueTxt.BeepOnError = true;
			this.EditValueTxt.Location = new System.Drawing.Point(31, 64);
			this.EditValueTxt.Name = "EditValueTxt";
			this.EditValueTxt.Size = new System.Drawing.Size(128, 20);
			this.EditValueTxt.TabIndex = 6;
			// 
			// CancelBtn
			// 
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(111, 90);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(60, 23);
			this.CancelBtn.TabIndex = 5;
			this.CancelBtn.Text = "Cancel";
			this.CancelBtn.UseVisualStyleBackColor = true;
			// 
			// OkayBtn
			// 
			this.OkayBtn.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.OkayBtn.Location = new System.Drawing.Point(19, 90);
			this.OkayBtn.Name = "OkayBtn";
			this.OkayBtn.Size = new System.Drawing.Size(60, 23);
			this.OkayBtn.TabIndex = 4;
			this.OkayBtn.Text = "Okay";
			this.OkayBtn.UseVisualStyleBackColor = true;
			// 
			// EditValueDlg
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(196, 129);
			this.ControlBox = false;
			this.Controls.Add(this.label1);
			this.Controls.Add(this.EditValueTxt);
			this.Controls.Add(this.CancelBtn);
			this.Controls.Add(this.OkayBtn);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "EditValueDlg";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Edit Value";
			this.TopMost = true;
			this.Shown += new System.EventHandler(this.EditValueDlg_Shown);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		public System.Windows.Forms.MaskedTextBox EditValueTxt;
		private System.Windows.Forms.Button CancelBtn;
		private System.Windows.Forms.Button OkayBtn;
	}
}