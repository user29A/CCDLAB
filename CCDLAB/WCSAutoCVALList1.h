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


namespace CCDLAB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for WCSAutoCVALList
	/// </summary>
	public ref class WCSAutoCVALList : public System::Windows::Forms::Form
	{
	public:
		//Creates a drop down control with the list of entries inside a specified binary extension table of a FITS file
		WCSAutoCVALList(String^ CatalogueFileName, String^ ExtensionName)
		{
			InitializeComponent();
			FILENAME = CatalogueFileName;
			EXTENSIONNAME = ExtensionName;
			
			JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(CatalogueFileName, ExtensionName);
			array<String^>^ ttypes = bt->TableDataLabelsTTYPE;
				
			WCDrop->Items->AddRange(ttypes);
			ITEMLIST = ttypes;
		}

		//Creates a drop down control with the list of binary table extension names in a FITS file
		WCSAutoCVALList(String^ CatalogueFileName)
		{
			InitializeComponent();
			FILENAME = CatalogueFileName;
			array<String^>^ extensions = JPFITS::FITSBinTable::GetAllExtensionNames(FILENAME);
			WCDrop->Items->AddRange(extensions);
			ITEMLIST = extensions;
		}

		//Creates a drop down control with the given array of String items
		WCSAutoCVALList(array<String^>^ items)
		{
			InitializeComponent();
			WCDrop->Items->AddRange(items);
			ITEMLIST = items;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WCSAutoCVALList()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ComboBox^  WCDrop;
	private: System::Windows::Forms::Button^  OKBtn;
	private: System::Windows::Forms::Button^  CancelBtn;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  SearchTxtBox;
	public:
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
			this->WCDrop = (gcnew System::Windows::Forms::ComboBox());
			this->OKBtn = (gcnew System::Windows::Forms::Button());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SearchTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// WCDrop
			// 
			this->WCDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->WCDrop->FormattingEnabled = true;
			this->WCDrop->Location = System::Drawing::Point(18, 35);
			this->WCDrop->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->WCDrop->Name = L"WCDrop";
			this->WCDrop->Size = System::Drawing::Size(180, 21);
			this->WCDrop->TabIndex = 0;
			this->WCDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &WCSAutoCVALList::WCDrop_SelectedIndexChanged);
			// 
			// OKBtn
			// 
			this->OKBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKBtn->Location = System::Drawing::Point(34, 39);
			this->OKBtn->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->OKBtn->Name = L"OKBtn";
			this->OKBtn->Size = System::Drawing::Size(58, 18);
			this->OKBtn->TabIndex = 1;
			this->OKBtn->Text = L"OK";
			this->OKBtn->UseVisualStyleBackColor = true;
			this->OKBtn->Click += gcnew System::EventHandler(this, &WCSAutoCVALList::OKBtn_Click);
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(134, 39);
			this->CancelBtn->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(52, 18);
			this->CancelBtn->TabIndex = 2;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			this->CancelBtn->Click += gcnew System::EventHandler(this, &WCSAutoCVALList::CancelBtn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Search:";
			// 
			// SearchTxtBox
			// 
			this->SearchTxtBox->Location = System::Drawing::Point(59, 10);
			this->SearchTxtBox->Name = L"SearchTxtBox";
			this->SearchTxtBox->Size = System::Drawing::Size(100, 20);
			this->SearchTxtBox->TabIndex = 4;
			this->SearchTxtBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &WCSAutoCVALList::SearchTxtBox_MouseClick);
			this->SearchTxtBox->TextChanged += gcnew System::EventHandler(this, &WCSAutoCVALList::SearchTxtBox_TextChanged);
			// 
			// WCSAutoCVALList
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(219, 75);
			this->ControlBox = false;
			this->Controls->Add(this->SearchTxtBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->WCDrop);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->OKBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"WCSAutoCVALList";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Select WC";
			this->Shown += gcnew System::EventHandler(this, &WCSAutoCVALList::WCSAutoCVALList_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		String^ FILENAME = "";
		String^ EXTENSIONNAME = "";
		array<String^>^ ITEMLIST;

private: System::Void WCDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);


private: System::Void WCSAutoCVALList_Shown(System::Object^  sender, System::EventArgs^  e)
{
	WCDrop->DroppedDown = true;
}
private: System::Void OKBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	this->DialogResult = Windows::Forms::DialogResult::OK;
	this->Close();
}
private: System::Void CancelBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	this->Close();
}
private: System::Void SearchTxtBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SearchTxtBox_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	WCDrop->DroppedDown = true;
	SearchTxtBox->Focus();
}
};
}
