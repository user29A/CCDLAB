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
	/// Summary for RADecBox
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class RADecBox : public System::Windows::Forms::Form
	{
	public:
		RADecBox(void)
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
		~RADecBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  OKBtn;
	protected: 
	private: System::Windows::Forms::Button^  CancelBtn;


	private: System::Windows::Forms::CheckBox^  RAToggle;

	public: System::Windows::Forms::TextBox^  RAhTxt;
	private: 

	private: 


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	public: System::Windows::Forms::TextBox^  RAmTxt;
	private: 


	private: System::Windows::Forms::Label^  label4;
	public: System::Windows::Forms::TextBox^  RAsTxt;
	private: 





	private: System::Windows::Forms::TextBox^  RADegTxt;
	private: System::Windows::Forms::CheckBox^  DecToggle;
	public: System::Windows::Forms::TextBox^  DecASTxt;
	public: System::Windows::Forms::TextBox^  DecAMTxt;
	private: 


	private: 

	private: System::Windows::Forms::Label^  label5;
	public: 
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	public: System::Windows::Forms::TextBox^  DecADTxt;
	private: 

	private: System::Windows::Forms::TextBox^  DecDegTxt;
	private: System::Windows::Forms::Button^  DecSignBtn;


	public: 
	private: 

	private: 

	private: 

	public: 


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
			this->OKBtn = (gcnew System::Windows::Forms::Button());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->RAToggle = (gcnew System::Windows::Forms::CheckBox());
			this->RAhTxt = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->RAmTxt = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->RAsTxt = (gcnew System::Windows::Forms::TextBox());
			this->RADegTxt = (gcnew System::Windows::Forms::TextBox());
			this->DecToggle = (gcnew System::Windows::Forms::CheckBox());
			this->DecASTxt = (gcnew System::Windows::Forms::TextBox());
			this->DecAMTxt = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->DecADTxt = (gcnew System::Windows::Forms::TextBox());
			this->DecDegTxt = (gcnew System::Windows::Forms::TextBox());
			this->DecSignBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// OKBtn
			// 
			this->OKBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKBtn->Location = System::Drawing::Point(225, 11);
			this->OKBtn->Name = L"OKBtn";
			this->OKBtn->Size = System::Drawing::Size(75, 23);
			this->OKBtn->TabIndex = 6;
			this->OKBtn->Text = L"Okay";
			this->OKBtn->UseVisualStyleBackColor = true;
			this->OKBtn->Click += gcnew System::EventHandler(this, &RADecBox::OKBtn_Click);
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(225, 40);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(75, 23);
			this->CancelBtn->TabIndex = 7;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			// 
			// RAToggle
			// 
			this->RAToggle->Appearance = System::Windows::Forms::Appearance::Button;
			this->RAToggle->AutoSize = true;
			this->RAToggle->Location = System::Drawing::Point(12, 12);
			this->RAToggle->Name = L"RAToggle";
			this->RAToggle->Size = System::Drawing::Size(77, 23);
			this->RAToggle->TabIndex = 0;
			this->RAToggle->Text = L"RA: deg.deg";
			this->RAToggle->UseVisualStyleBackColor = true;
			this->RAToggle->CheckedChanged += gcnew System::EventHandler(this, &RADecBox::RAToggle_CheckedChanged);
			// 
			// RAhTxt
			// 
			this->RAhTxt->Location = System::Drawing::Point(109, 14);
			this->RAhTxt->Name = L"RAhTxt";
			this->RAhTxt->Size = System::Drawing::Size(19, 20);
			this->RAhTxt->TabIndex = 1;
			this->RAhTxt->Text = L"23";
			this->RAhTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::RAhTxt_TextChanged);
			this->RAhTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::RAhTxt_KeyDown);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(128, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(13, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"h";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(160, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"m";
			// 
			// RAmTxt
			// 
			this->RAmTxt->Location = System::Drawing::Point(142, 14);
			this->RAmTxt->Name = L"RAmTxt";
			this->RAmTxt->Size = System::Drawing::Size(19, 20);
			this->RAmTxt->TabIndex = 2;
			this->RAmTxt->Text = L"45";
			this->RAmTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::RAmTxt_TextChanged);
			this->RAmTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::RAmTxt_KeyDown);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(209, 17);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(12, 13);
			this->label4->TabIndex = 11;
			this->label4->Text = L"s";
			// 
			// RAsTxt
			// 
			this->RAsTxt->Location = System::Drawing::Point(174, 14);
			this->RAsTxt->Name = L"RAsTxt";
			this->RAsTxt->Size = System::Drawing::Size(37, 20);
			this->RAsTxt->TabIndex = 3;
			this->RAsTxt->Text = L"59";
			this->RAsTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::RAsTxt_TextChanged);
			this->RAsTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::RAsTxt_KeyDown);
			// 
			// RADegTxt
			// 
			this->RADegTxt->Location = System::Drawing::Point(109, 14);
			this->RADegTxt->Name = L"RADegTxt";
			this->RADegTxt->Size = System::Drawing::Size(110, 20);
			this->RADegTxt->TabIndex = 1;
			this->RADegTxt->Text = L"180.45678";
			this->RADegTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->RADegTxt->Visible = false;
			this->RADegTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::RADegTxt_TextChanged);
			this->RADegTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::RADegTxt_KeyDown);
			// 
			// DecToggle
			// 
			this->DecToggle->Appearance = System::Windows::Forms::Appearance::Button;
			this->DecToggle->AutoSize = true;
			this->DecToggle->Location = System::Drawing::Point(12, 38);
			this->DecToggle->Name = L"DecToggle";
			this->DecToggle->Size = System::Drawing::Size(82, 23);
			this->DecToggle->TabIndex = 12;
			this->DecToggle->Text = L"Dec: deg.deg";
			this->DecToggle->UseVisualStyleBackColor = true;
			this->DecToggle->CheckedChanged += gcnew System::EventHandler(this, &RADecBox::DecToggle_CheckedChanged);
			// 
			// DecASTxt
			// 
			this->DecASTxt->Location = System::Drawing::Point(174, 40);
			this->DecASTxt->Name = L"DecASTxt";
			this->DecASTxt->Size = System::Drawing::Size(37, 20);
			this->DecASTxt->TabIndex = 16;
			this->DecASTxt->Text = L"59";
			this->DecASTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::DecASTxt_TextChanged);
			this->DecASTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::DecASTxt_KeyDown);
			// 
			// DecAMTxt
			// 
			this->DecAMTxt->Location = System::Drawing::Point(142, 40);
			this->DecAMTxt->Name = L"DecAMTxt";
			this->DecAMTxt->Size = System::Drawing::Size(19, 20);
			this->DecAMTxt->TabIndex = 15;
			this->DecAMTxt->Text = L"45";
			this->DecAMTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::DecAMTxt_TextChanged);
			this->DecAMTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::DecAMTxt_KeyDown);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(211, 43);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(12, 13);
			this->label5->TabIndex = 19;
			this->label5->Text = L"\"";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(165, 43);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(9, 13);
			this->label6->TabIndex = 18;
			this->label6->Text = L"\'";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(128, 43);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(13, 13);
			this->label7->TabIndex = 17;
			this->label7->Text = L"d";
			// 
			// DecADTxt
			// 
			this->DecADTxt->Location = System::Drawing::Point(109, 40);
			this->DecADTxt->Name = L"DecADTxt";
			this->DecADTxt->Size = System::Drawing::Size(19, 20);
			this->DecADTxt->TabIndex = 13;
			this->DecADTxt->Text = L"23";
			this->DecADTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::DecADTxt_TextChanged);
			this->DecADTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::DecADTxt_KeyDown);
			// 
			// DecDegTxt
			// 
			this->DecDegTxt->Location = System::Drawing::Point(109, 40);
			this->DecDegTxt->Name = L"DecDegTxt";
			this->DecDegTxt->Size = System::Drawing::Size(110, 20);
			this->DecDegTxt->TabIndex = 14;
			this->DecDegTxt->Text = L"180.45678";
			this->DecDegTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->DecDegTxt->Visible = false;
			this->DecDegTxt->TextChanged += gcnew System::EventHandler(this, &RADecBox::DecTxt_TextChanged);
			// 
			// DecSignBtn
			// 
			this->DecSignBtn->Location = System::Drawing::Point(94, 39);
			this->DecSignBtn->Name = L"DecSignBtn";
			this->DecSignBtn->Size = System::Drawing::Size(15, 22);
			this->DecSignBtn->TabIndex = 20;
			this->DecSignBtn->Text = L"+";
			this->DecSignBtn->UseVisualStyleBackColor = true;
			this->DecSignBtn->Click += gcnew System::EventHandler(this, &RADecBox::DecSignBtn_Click);
			// 
			// RADecBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(318, 75);
			this->ControlBox = false;
			this->Controls->Add(this->DecADTxt);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->RAsTxt);
			this->Controls->Add(this->DecSignBtn);
			this->Controls->Add(this->DecAMTxt);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->RAmTxt);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->RAToggle);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->OKBtn);
			this->Controls->Add(this->RAhTxt);
			this->Controls->Add(this->DecToggle);
			this->Controls->Add(this->RADegTxt);
			this->Controls->Add(this->DecASTxt);
			this->Controls->Add(this->DecDegTxt);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"RADecBox";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Right Ascension & Declination";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &RADecBox::RADecBox_Load);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &RADecBox::RADecBox_KeyUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

public:

double RIGHT_ASCENSION, DECLINATION;//degrees










private: System::Void RAToggle_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void OKBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RADecBox_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void RAhTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void RAmTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void RAsTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void RADegTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecTxt_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void DecTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void RADegTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void RAhTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void RAmTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void RAsTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void RADecBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void DecToggle_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecSignBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecADTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecAMTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecASTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DecADTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void DecAMTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void DecASTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
};
}
