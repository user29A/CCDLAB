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


namespace CCDLAB {

	/// <summary>
	/// Summary for EditKeyDlg
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class EditKeyDlg : public System::Windows::Forms::Form
	{
	public:
		EditKeyDlg(void)
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
		~EditKeyDlg()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::TextBox^  KeyNameTxt;
		public: System::Windows::Forms::Label^  label1;
		public: System::Windows::Forms::Label^  label2;


	public: System::Windows::Forms::TextBox^  KeyValueTxt;
	public: System::Windows::Forms::TextBox^  KeyCommentTxt;
		public: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Button^  OKBtn;
	private: System::Windows::Forms::Button^  CancelBtn;
		public: System::Windows::Forms::TextBox^  CommentKeyLineTxt;
		public: System::Windows::Forms::CheckBox^  CommentKeyLineChck;

		public:
		private:

		private:

	private: 





	public: 
	private: 
	public: 
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
			this->KeyNameTxt = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->KeyValueTxt = (gcnew System::Windows::Forms::TextBox());
			this->KeyCommentTxt = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->OKBtn = (gcnew System::Windows::Forms::Button());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->CommentKeyLineTxt = (gcnew System::Windows::Forms::TextBox());
			this->CommentKeyLineChck = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// KeyNameTxt
			// 
			this->KeyNameTxt->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->KeyNameTxt->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->KeyNameTxt->Location = System::Drawing::Point(6, 28);
			this->KeyNameTxt->MaxLength = 8;
			this->KeyNameTxt->Name = L"KeyNameTxt";
			this->KeyNameTxt->Size = System::Drawing::Size(65, 21);
			this->KeyNameTxt->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(3, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 13);
			this->label1->TabIndex = 88;
			this->label1->Text = L"Key Name";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(69, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 13);
			this->label2->TabIndex = 89;
			this->label2->Text = L"Key Value";
			// 
			// KeyValueTxt
			// 
			this->KeyValueTxt->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->KeyValueTxt->Location = System::Drawing::Point(72, 28);
			this->KeyValueTxt->MaxLength = 18;
			this->KeyValueTxt->Name = L"KeyValueTxt";
			this->KeyValueTxt->Size = System::Drawing::Size(136, 21);
			this->KeyValueTxt->TabIndex = 1;
			this->KeyValueTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// KeyCommentTxt
			// 
			this->KeyCommentTxt->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->KeyCommentTxt->Location = System::Drawing::Point(209, 28);
			this->KeyCommentTxt->MaxLength = 48;
			this->KeyCommentTxt->Name = L"KeyCommentTxt";
			this->KeyCommentTxt->Size = System::Drawing::Size(368, 21);
			this->KeyCommentTxt->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(206, 12);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(72, 13);
			this->label3->TabIndex = 90;
			this->label3->Text = L"Key Comment";
			// 
			// OKBtn
			// 
			this->OKBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKBtn->Location = System::Drawing::Point(185, 62);
			this->OKBtn->Name = L"OKBtn";
			this->OKBtn->Size = System::Drawing::Size(75, 23);
			this->OKBtn->TabIndex = 3;
			this->OKBtn->Text = L"OK";
			this->OKBtn->UseVisualStyleBackColor = true;
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(306, 62);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(75, 23);
			this->CancelBtn->TabIndex = 4;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			// 
			// CommentKeyLineTxt
			// 
			this->CommentKeyLineTxt->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CommentKeyLineTxt->Location = System::Drawing::Point(6, 28);
			this->CommentKeyLineTxt->MaxLength = 80;
			this->CommentKeyLineTxt->Name = L"CommentKeyLineTxt";
			this->CommentKeyLineTxt->Size = System::Drawing::Size(571, 21);
			this->CommentKeyLineTxt->TabIndex = 91;
			this->CommentKeyLineTxt->Visible = false;
			// 
			// CommentKeyLineChck
			// 
			this->CommentKeyLineChck->AutoSize = true;
			this->CommentKeyLineChck->Location = System::Drawing::Point(6, 55);
			this->CommentKeyLineChck->Name = L"CommentKeyLineChck";
			this->CommentKeyLineChck->Size = System::Drawing::Size(129, 17);
			this->CommentKeyLineChck->TabIndex = 92;
			this->CommentKeyLineChck->Text = L"Line is Comment Form";
			this->CommentKeyLineChck->UseVisualStyleBackColor = true;
			this->CommentKeyLineChck->Visible = false;
			this->CommentKeyLineChck->CheckedChanged += gcnew System::EventHandler(this, &EditKeyDlg::CommentKeyLineChck_CheckedChanged);
			// 
			// EditKeyDlg
			// 
			this->AcceptButton = this->OKBtn;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(581, 97);
			this->ControlBox = false;
			this->Controls->Add(this->CommentKeyLineChck);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->OKBtn);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->KeyCommentTxt);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->KeyValueTxt);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->KeyNameTxt);
			this->Controls->Add(this->CommentKeyLineTxt);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"EditKeyDlg";
			this->RightToLeftLayout = true;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Edit/Create Key...";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &EditKeyDlg::EditKeyDlg_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void EditKeyDlg_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void CommentKeyLineChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		if (CommentKeyLineChck->Checked)
		{
			this->CommentKeyLineTxt->Visible = true;
			this->CommentKeyLineTxt->BringToFront();
			this->label1->Text = "Comment Line";
			this->label2->Visible = false;
			this->label3->Visible = false;
		}
		else
		{
			this->CommentKeyLineTxt->Visible = false;
			this->CommentKeyLineTxt->SendToBack();
			this->label1->Text = "Key Name";
			this->label2->Visible = true;
			this->label3->Visible = true;
		}
	}
};
}
