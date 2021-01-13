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

#include "String.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CCDLAB {

	/// <summary>
	/// Summary for EditValueDlg
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class EditValueDlg : public System::Windows::Forms::Form
	{
	public:
		EditValueDlg(void)
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
		~EditValueDlg()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  OkayBtn;
	protected: 
	private: System::Windows::Forms::Button^  CancelBtn;
	public: System::Windows::Forms::MaskedTextBox^  EditValueTxt;
	private: 

	private: System::Windows::Forms::Label^  label1;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(EditValueDlg::typeid));
			this->OkayBtn = (gcnew System::Windows::Forms::Button());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->EditValueTxt = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// OkayBtn
			// 
			this->OkayBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OkayBtn->Location = System::Drawing::Point(22, 94);
			this->OkayBtn->Name = L"OkayBtn";
			this->OkayBtn->Size = System::Drawing::Size(60, 23);
			this->OkayBtn->TabIndex = 0;
			this->OkayBtn->Text = L"Okay";
			this->OkayBtn->UseVisualStyleBackColor = true;
			this->OkayBtn->Click += gcnew System::EventHandler(this, &EditValueDlg::OkayBtn_Click);
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(114, 94);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(60, 23);
			this->CancelBtn->TabIndex = 1;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			// 
			// EditValueTxt
			// 
			this->EditValueTxt->BeepOnError = true;
			this->EditValueTxt->Location = System::Drawing::Point(34, 68);
			this->EditValueTxt->Name = L"EditValueTxt";
			this->EditValueTxt->Size = System::Drawing::Size(128, 20);
			this->EditValueTxt->TabIndex = 2;
			this->EditValueTxt->TextChanged += gcnew System::EventHandler(this, &EditValueDlg::EditValueTxt_TextChanged);
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(19, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(165, 41);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Enter Value [begin with ! to change everything other than selection region of int"
				L"erest]";
			// 
			// EditValueDlg
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(196, 129);
			this->ControlBox = false;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->EditValueTxt);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->OkayBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"EditValueDlg";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Edit Value";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &EditValueDlg::EditValueDlg_Load);
			this->Shown += gcnew System::EventHandler(this, &EditValueDlg::EditValueDlg_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


public: 
static int modecode = 1;//-1 if numeric error



private: System::Void EditValueDlg_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
			 }
private: System::Void EditValueDlg_Shown(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //edittxt = EditValueTxt->Text;
			 EditValueTxt->Focus();
			 EditValueTxt->SelectAll();
		 }
private: System::Void OkayBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {

		 }
private: System::Void EditValueTxt_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 /*if (EditValueTxt->Text == "-" || EditValueTxt->Text == "." || EditValueTxt->Text == "+"  || EditValueTxt->Text == "!")
				 goto end1;
			 try
			 {
				 String^ strval = EditValueTxt->Text;
				 bool notind = strval->StartsWith("!");
				 if (notind)
					 strval = strval->Substring(0,strval->Length-1);
				 double val = ::Convert::ToDouble(strval);
				 edittxt = EditValueTxt->Text;
			 }
			 catch(...)
			 {
				 if (EditValueTxt->Text->Length > 1)
					EditValueTxt->Text = edittxt;
				 try
				 {
					 double val2 = ::Convert::ToDouble(EditValueTxt->Text);
				 }
				 catch(...)
				 {
					 edittxt = "";
					 EditValueTxt->Text = edittxt;
				 }
			 }
			 end1:;*/
		 }
};
}
