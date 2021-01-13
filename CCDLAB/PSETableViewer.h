/*Copyright 2021 Joseph Edwin Postma

Contact email: joepostma@live.ca

This file is part of JPFITS.

JPFITS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

JPFITS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

See http://www.gnu.org/licenses/. */

#pragma once
#include "Form1.h"

namespace CCDLAB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PSETableViewer
	/// </summary>
	public ref class PSETableViewer : public System::Windows::Forms::Form
	{
	public:
		PSETableViewer(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PSETableViewer()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::DataGridView^  PSETable;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	public:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  PSETableViewerSaveBtn;
	private: System::Windows::Forms::ToolStripMenuItem^  PSETableViewerCloseBtn;
	private: System::Windows::Forms::Button^  button1;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PSETableViewer::typeid));
			this->PSETable = (gcnew System::Windows::Forms::DataGridView());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSETableViewerSaveBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSETableViewerCloseBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSETable))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PSETable
			// 
			this->PSETable->AllowUserToOrderColumns = true;
			this->PSETable->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableWithoutHeaderText;
			this->PSETable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->PSETable->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PSETable->Location = System::Drawing::Point(0, 24);
			this->PSETable->Name = L"PSETable";
			this->PSETable->Size = System::Drawing::Size(1175, 482);
			this->PSETable->TabIndex = 0;
			this->PSETable->CellMouseDoubleClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &PSETableViewer::PSETable_CellMouseDoubleClick);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1175, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->PSETableViewerSaveBtn,
					this->PSETableViewerCloseBtn
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// PSETableViewerSaveBtn
			// 
			this->PSETableViewerSaveBtn->Name = L"PSETableViewerSaveBtn";
			this->PSETableViewerSaveBtn->Size = System::Drawing::Size(103, 22);
			this->PSETableViewerSaveBtn->Text = L"Save";
			this->PSETableViewerSaveBtn->Click += gcnew System::EventHandler(this, &PSETableViewer::PSETableViewerSaveBtn_Click);
			// 
			// PSETableViewerCloseBtn
			// 
			this->PSETableViewerCloseBtn->Name = L"PSETableViewerCloseBtn";
			this->PSETableViewerCloseBtn->Size = System::Drawing::Size(103, 22);
			this->PSETableViewerCloseBtn->Text = L"Close";
			this->PSETableViewerCloseBtn->Visible = false;
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(12, 27);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &PSETableViewer::button1_Click);
			// 
			// PSETableViewer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->button1;
			this->ClientSize = System::Drawing::Size(1175, 506);
			this->Controls->Add(this->PSETable);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->button1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"PSETableViewer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSETable))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion




	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
private: System::Void PSETableViewerSaveBtn_Click(System::Object^  sender, System::EventArgs^  e);



private: System::Void PSETable_CellMouseDoubleClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e);
};
}
