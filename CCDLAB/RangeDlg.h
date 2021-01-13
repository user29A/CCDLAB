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
	/// Summary for RangeDlg
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class RangeDlg : public System::Windows::Forms::Form
	{
	public:
		RangeDlg(void)
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
		~RangeDlg()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::NumericUpDown^  XStartUpD;
	public: System::Windows::Forms::NumericUpDown^  XEndUpD;
	public: System::Windows::Forms::NumericUpDown^  YEndUpD;
	protected: 

	protected: 


	public: System::Windows::Forms::NumericUpDown^  YStartUpD;
	private: System::Windows::Forms::Label^  XStartLabel;
	private: System::Windows::Forms::Label^  YEndLabel;
	public:


	protected: 





	private: System::Windows::Forms::Label^  YStartLabel;
	private: System::Windows::Forms::Label^  XEndLabel;


	private: System::Windows::Forms::Button^  OKBtn;
	private: System::Windows::Forms::Button^  CancelBtn;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RangeDlg::typeid));
			this->XStartUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->XEndUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->YEndUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->YStartUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->XStartLabel = (gcnew System::Windows::Forms::Label());
			this->YEndLabel = (gcnew System::Windows::Forms::Label());
			this->YStartLabel = (gcnew System::Windows::Forms::Label());
			this->XEndLabel = (gcnew System::Windows::Forms::Label());
			this->OKBtn = (gcnew System::Windows::Forms::Button());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XStartUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XEndUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YEndUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YStartUpD))->BeginInit();
			this->SuspendLayout();
			// 
			// XStartUpD
			// 
			this->XStartUpD->Location = System::Drawing::Point(59, 22);
			this->XStartUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { System::Int32::MinValue, 0, 0, 0 });
			this->XStartUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->XStartUpD->Name = L"XStartUpD";
			this->XStartUpD->Size = System::Drawing::Size(80, 20);
			this->XStartUpD->TabIndex = 0;
			this->XStartUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			// 
			// XEndUpD
			// 
			this->XEndUpD->Location = System::Drawing::Point(200, 22);
			this->XEndUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { System::Int32::MinValue, 0, 0, 0 });
			this->XEndUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->XEndUpD->Name = L"XEndUpD";
			this->XEndUpD->Size = System::Drawing::Size(80, 20);
			this->XEndUpD->TabIndex = 1;
			this->XEndUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			// 
			// YEndUpD
			// 
			this->YEndUpD->Location = System::Drawing::Point(201, 55);
			this->YEndUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { System::Int32::MinValue, 0, 0, 0 });
			this->YEndUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->YEndUpD->Name = L"YEndUpD";
			this->YEndUpD->Size = System::Drawing::Size(79, 20);
			this->YEndUpD->TabIndex = 2;
			this->YEndUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			// 
			// YStartUpD
			// 
			this->YStartUpD->Location = System::Drawing::Point(59, 55);
			this->YStartUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { System::Int32::MinValue, 0, 0, 0 });
			this->YStartUpD->Name = L"YStartUpD";
			this->YStartUpD->Size = System::Drawing::Size(80, 20);
			this->YStartUpD->TabIndex = 3;
			// 
			// XStartLabel
			// 
			this->XStartLabel->AutoSize = true;
			this->XStartLabel->Location = System::Drawing::Point(17, 26);
			this->XStartLabel->Name = L"XStartLabel";
			this->XStartLabel->Size = System::Drawing::Size(36, 13);
			this->XStartLabel->TabIndex = 4;
			this->XStartLabel->Text = L"XStart";
			// 
			// YEndLabel
			// 
			this->YEndLabel->AutoSize = true;
			this->YEndLabel->Location = System::Drawing::Point(159, 59);
			this->YEndLabel->Name = L"YEndLabel";
			this->YEndLabel->Size = System::Drawing::Size(33, 13);
			this->YEndLabel->TabIndex = 5;
			this->YEndLabel->Text = L"YEnd";
			// 
			// YStartLabel
			// 
			this->YStartLabel->AutoSize = true;
			this->YStartLabel->Location = System::Drawing::Point(17, 57);
			this->YStartLabel->Name = L"YStartLabel";
			this->YStartLabel->Size = System::Drawing::Size(36, 13);
			this->YStartLabel->TabIndex = 6;
			this->YStartLabel->Text = L"YStart";
			// 
			// XEndLabel
			// 
			this->XEndLabel->AutoSize = true;
			this->XEndLabel->Location = System::Drawing::Point(159, 26);
			this->XEndLabel->Name = L"XEndLabel";
			this->XEndLabel->Size = System::Drawing::Size(33, 13);
			this->XEndLabel->TabIndex = 7;
			this->XEndLabel->Text = L"XEnd";
			// 
			// OKBtn
			// 
			this->OKBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKBtn->Location = System::Drawing::Point(320, 22);
			this->OKBtn->Name = L"OKBtn";
			this->OKBtn->Size = System::Drawing::Size(75, 23);
			this->OKBtn->TabIndex = 8;
			this->OKBtn->Text = L"OK";
			this->OKBtn->UseVisualStyleBackColor = true;
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(320, 55);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(75, 23);
			this->CancelBtn->TabIndex = 9;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			// 
			// RangeDlg
			// 
			this->AcceptButton = this->OKBtn;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(419, 99);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->OKBtn);
			this->Controls->Add(this->XEndLabel);
			this->Controls->Add(this->YStartLabel);
			this->Controls->Add(this->YEndLabel);
			this->Controls->Add(this->XStartLabel);
			this->Controls->Add(this->YStartUpD);
			this->Controls->Add(this->YEndUpD);
			this->Controls->Add(this->XEndUpD);
			this->Controls->Add(this->XStartUpD);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->HelpButton = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"RangeDlg";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Specify ZERO-BASED Image Range";
			this->TopMost = true;
			this->HelpButtonClicked += gcnew System::ComponentModel::CancelEventHandler(this, &RangeDlg::RangeDlg_HelpButtonClicked);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XStartUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XEndUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YEndUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YStartUpD))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void RangeDlg_HelpButtonClicked(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);

};
}
