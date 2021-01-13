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

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


namespace CCDLAB {

	/// <summary>
	/// Summary for BatchSaveDlg
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class BatchSaveDlg : public System::Windows::Forms::Form
	{
	public:
		BatchSaveDlg(void)
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
		~BatchSaveDlg()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  DirectoryTxt;
	protected: 
	public: System::Windows::Forms::TextBox^  AppendTxt;
	private: System::Windows::Forms::Button^  CancelBtn;
	public: 
	private: System::Windows::Forms::FolderBrowserDialog^  FolderDlg;
	private: System::Windows::Forms::Button^  OverwriteBtn;
	public: System::Windows::Forms::Button^  AppendBtn;
	private:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	public: System::Windows::Forms::ComboBox^  FileExtension;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	public: System::Windows::Forms::CheckBox^  UseOrigDirChck;
	private: System::Windows::Forms::Button^  AppendBtnChangeBtn;
	private: System::Windows::Forms::Button^ GetCommonDirectoryBtn;

	public:

	public:

	public:
	private:

	public: 
	private: System::ComponentModel::IContainer^  components;

	public: 





	public: 
	private: 



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->DirectoryTxt = (gcnew System::Windows::Forms::RichTextBox());
			this->AppendTxt = (gcnew System::Windows::Forms::TextBox());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->FolderDlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->OverwriteBtn = (gcnew System::Windows::Forms::Button());
			this->AppendBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->FileExtension = (gcnew System::Windows::Forms::ComboBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->UseOrigDirChck = (gcnew System::Windows::Forms::CheckBox());
			this->AppendBtnChangeBtn = (gcnew System::Windows::Forms::Button());
			this->GetCommonDirectoryBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// DirectoryTxt
			// 
			this->DirectoryTxt->DetectUrls = false;
			this->DirectoryTxt->Location = System::Drawing::Point(20, 30);
			this->DirectoryTxt->Name = L"DirectoryTxt";
			this->DirectoryTxt->ReadOnly = true;
			this->DirectoryTxt->Size = System::Drawing::Size(328, 69);
			this->DirectoryTxt->TabIndex = 11;
			this->DirectoryTxt->Text = L"Click Here to Choose Alternate Directory, or Leave to Use Current File Directory";
			this->toolTip1->SetToolTip(this->DirectoryTxt, L"Click to Select Directory");
			this->DirectoryTxt->Click += gcnew System::EventHandler(this, &BatchSaveDlg::DirectoryTxt_Click);
			// 
			// AppendTxt
			// 
			this->AppendTxt->Location = System::Drawing::Point(21, 151);
			this->AppendTxt->MaxLength = 20;
			this->AppendTxt->Name = L"AppendTxt";
			this->AppendTxt->Size = System::Drawing::Size(73, 20);
			this->AppendTxt->TabIndex = 10;
			this->AppendTxt->Text = L"_red";
			this->AppendTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->toolTip1->SetToolTip(this->AppendTxt, L"Enter * to auto-increment appendage.");
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(273, 128);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(75, 23);
			this->CancelBtn->TabIndex = 9;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			// 
			// OverwriteBtn
			// 
			this->OverwriteBtn->DialogResult = System::Windows::Forms::DialogResult::Ignore;
			this->OverwriteBtn->Location = System::Drawing::Point(101, 128);
			this->OverwriteBtn->Name = L"OverwriteBtn";
			this->OverwriteBtn->Size = System::Drawing::Size(75, 44);
			this->OverwriteBtn->TabIndex = 8;
			this->OverwriteBtn->Text = L"Write/Overwrite";
			this->toolTip1->SetToolTip(this->OverwriteBtn, L"\"Overwrite\" will use the existing filenames; if a different directory or file ext"
				L"ension is selected, the original files will not be changed, otherwise they will "
				L"be overwritten.");
			this->OverwriteBtn->UseVisualStyleBackColor = true;
			this->OverwriteBtn->Click += gcnew System::EventHandler(this, &BatchSaveDlg::OverwriteBtn_Click);
			// 
			// AppendBtn
			// 
			this->AppendBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->AppendBtn->Location = System::Drawing::Point(20, 128);
			this->AppendBtn->Name = L"AppendBtn";
			this->AppendBtn->Size = System::Drawing::Size(75, 23);
			this->AppendBtn->TabIndex = 7;
			this->AppendBtn->Text = L"Append";
			this->toolTip1->SetToolTip(this->AppendBtn, L"This will append the text below to the file name, thus, the original files will n"
				L"ot be overwritten.  If no text is entered, you will receive an error notificatio"
				L"n. ");
			this->AppendBtn->UseVisualStyleBackColor = true;
			this->AppendBtn->Click += gcnew System::EventHandler(this, &BatchSaveDlg::AppendBtn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(90, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(193, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"How would you like to save these files\?";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(196, 133);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(34, 13);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Type:";
			// 
			// FileExtension
			// 
			this->FileExtension->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FileExtension->FormattingEnabled = true;
			this->FileExtension->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L".fts", L".fit", L".fits", L".jpg", L".zip" });
			this->FileExtension->Location = System::Drawing::Point(199, 151);
			this->FileExtension->Name = L"FileExtension";
			this->FileExtension->Size = System::Drawing::Size(50, 21);
			this->FileExtension->TabIndex = 13;
			// 
			// toolTip1
			// 
			this->toolTip1->AutomaticDelay = 50;
			this->toolTip1->AutoPopDelay = 8000;
			this->toolTip1->InitialDelay = 50;
			this->toolTip1->ReshowDelay = 10;
			// 
			// UseOrigDirChck
			// 
			this->UseOrigDirChck->AutoSize = true;
			this->UseOrigDirChck->Location = System::Drawing::Point(20, 105);
			this->UseOrigDirChck->Name = L"UseOrigDirChck";
			this->UseOrigDirChck->Size = System::Drawing::Size(139, 17);
			this->UseOrigDirChck->TabIndex = 14;
			this->UseOrigDirChck->Text = L"Use Original Directory(s)";
			this->UseOrigDirChck->UseVisualStyleBackColor = true;
			this->UseOrigDirChck->CheckedChanged += gcnew System::EventHandler(this, &BatchSaveDlg::UseOrigDirChck_CheckedChanged);
			// 
			// AppendBtnChangeBtn
			// 
			this->AppendBtnChangeBtn->Location = System::Drawing::Point(1, 128);
			this->AppendBtnChangeBtn->Name = L"AppendBtnChangeBtn";
			this->AppendBtnChangeBtn->Size = System::Drawing::Size(19, 23);
			this->AppendBtnChangeBtn->TabIndex = 15;
			this->AppendBtnChangeBtn->Text = L"X";
			this->AppendBtnChangeBtn->UseVisualStyleBackColor = true;
			this->AppendBtnChangeBtn->Click += gcnew System::EventHandler(this, &BatchSaveDlg::AppendBtnChangeBtn_Click);
			// 
			// GetCommonDirectoryBtn
			// 
			this->GetCommonDirectoryBtn->Location = System::Drawing::Point(165, 101);
			this->GetCommonDirectoryBtn->Name = L"GetCommonDirectoryBtn";
			this->GetCommonDirectoryBtn->Size = System::Drawing::Size(127, 23);
			this->GetCommonDirectoryBtn->TabIndex = 16;
			this->GetCommonDirectoryBtn->Text = L"Get Common Directory";
			this->GetCommonDirectoryBtn->UseVisualStyleBackColor = true;
			this->GetCommonDirectoryBtn->Click += gcnew System::EventHandler(this, &BatchSaveDlg::GetCommonDirectoryBtn_Click);
			// 
			// BatchSaveDlg
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(373, 179);
			this->ControlBox = false;
			this->Controls->Add(this->GetCommonDirectoryBtn);
			this->Controls->Add(this->AppendBtnChangeBtn);
			this->Controls->Add(this->UseOrigDirChck);
			this->Controls->Add(this->FileExtension);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->AppendTxt);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->OverwriteBtn);
			this->Controls->Add(this->AppendBtn);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->DirectoryTxt);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"BatchSaveDlg";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Batch Save...";
			this->Shown += gcnew System::EventHandler(this, &BatchSaveDlg::BatchSaveDlg_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void DirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchSaveDlg_Shown(System::Object^  sender, System::EventArgs^  e);
private: System::Void AppendBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OverwriteBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UseOrigDirChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void AppendBtnChangeBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void GetCommonDirectoryBtn_Click(System::Object^ sender, System::EventArgs^ e);
};
}
