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

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CCDLAB {

	/// <summary>
	/// Summary for HeaderKey
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class HeaderKey : public System::Windows::Forms::Form
	{
	public:
		HeaderKey(void)
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
		~HeaderKey()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::TextBox^  textBox1;
	protected: 

	private: System::Windows::Forms::Label^  label1;
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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBox1->Location = System::Drawing::Point(86, 48);
			this->textBox1->MaxLength = 8;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(68, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &HeaderKey::textBox1_KeyDown);
			this->textBox1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &HeaderKey::textBox1_KeyUp);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &HeaderKey::textBox1_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(35, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(170, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Please Enter the Header Keyword:";
			// 
			// HeaderKey
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(241, 102);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"HeaderKey";
			this->ShowIcon = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Enter Header Key";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &HeaderKey::HeaderKey_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void textBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void HeaderKey_Load(System::Object^  sender, System::EventArgs^  e);
	};
}
