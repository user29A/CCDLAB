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
	/// Summary for FitParametersWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FitParametersWindow : public System::Windows::Forms::Form
	{
	public:
		FitParametersWindow(int function_num, array<double>^ xrange, array<double>^ yrange, array<double, 2>^ roi);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FitParametersWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	public: System::Windows::Forms::Label^  FitFcnTxt;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;












	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  SetParamsBtn;



	private: System::Windows::Forms::Button^  CancelBtn;
	public: System::Windows::Forms::CheckBox^  ConstrainBtn;
	private:

	private: System::Windows::Forms::GroupBox^  BoundsPnl;







	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  P0ITxt;
	private: System::Windows::Forms::TextBox^  P7ITxt;
	private: System::Windows::Forms::TextBox^  P6ITxt;
	private: System::Windows::Forms::TextBox^  P5ITxt;
	private: System::Windows::Forms::TextBox^  P4ITxt;
	private: System::Windows::Forms::TextBox^  P3ITxt;
	private: System::Windows::Forms::TextBox^  P2ITxt;
	private: System::Windows::Forms::TextBox^  P1ITxt;
	private: System::Windows::Forms::TextBox^  P7UBTxt;
	private: System::Windows::Forms::TextBox^  P6UBTxt;
	private: System::Windows::Forms::TextBox^  P5UBTxt;
	private: System::Windows::Forms::TextBox^  P4UBTxt;
	private: System::Windows::Forms::TextBox^  P3UBTxt;
	private: System::Windows::Forms::TextBox^  P2UBTxt;
	private: System::Windows::Forms::TextBox^  P1UBTxt;
	private: System::Windows::Forms::TextBox^  P0UBTxt;
	private: System::Windows::Forms::TextBox^  P7LBTxt;
	private: System::Windows::Forms::TextBox^  P6LBTxt;
	private: System::Windows::Forms::TextBox^  P5LBTxt;
	private: System::Windows::Forms::TextBox^  P4LBTxt;
	private: System::Windows::Forms::TextBox^  P3LBTxt;
	private: System::Windows::Forms::TextBox^  P2LBTxt;
	private: System::Windows::Forms::TextBox^  P1LBTxt;
	private: System::Windows::Forms::TextBox^  P0LBTxt;
	private: System::Windows::Forms::Button^  GetLastBtn;

	public:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->FitFcnTxt = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->SetParamsBtn = (gcnew System::Windows::Forms::Button());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->ConstrainBtn = (gcnew System::Windows::Forms::CheckBox());
			this->BoundsPnl = (gcnew System::Windows::Forms::GroupBox());
			this->P7UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P6UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P5UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P4UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P3UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P2UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P1UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P0UBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P7LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P6LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P5LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P4LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P3LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P2LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P1LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->P0LBTxt = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->P7ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P6ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P5ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P4ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P3ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P2ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P1ITxt = (gcnew System::Windows::Forms::TextBox());
			this->P0ITxt = (gcnew System::Windows::Forms::TextBox());
			this->GetLastBtn = (gcnew System::Windows::Forms::Button());
			this->BoundsPnl->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(5, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Fit Function:";
			// 
			// FitFcnTxt
			// 
			this->FitFcnTxt->AutoSize = true;
			this->FitFcnTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FitFcnTxt->Location = System::Drawing::Point(5, 31);
			this->FitFcnTxt->Name = L"FitFcnTxt";
			this->FitFcnTxt->Size = System::Drawing::Size(594, 13);
			this->FitFcnTxt->TabIndex = 1;
			this->FitFcnTxt->Text = L"P(0)*(1 + (((X-P(1))*cos(P(3)) + (Y-P(2))*sin(P(3)))^2)/P(4)^2 + ((-(X-P(1))*sin("
				L"P(3)) + (Y-P(2))*cos(P(3)))^2)/P(5)^2)^(-P(6)) + P(7)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(131, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(78, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Upper Bounds:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 16);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(78, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Lower Bounds:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(6, 32);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(30, 13);
			this->label5->TabIndex = 20;
			this->label5->Text = L"P(0)";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(6, 58);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 13);
			this->label6->TabIndex = 21;
			this->label6->Text = L"P(1)";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(6, 84);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(30, 13);
			this->label7->TabIndex = 22;
			this->label7->Text = L"P(2)";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(6, 110);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(30, 13);
			this->label8->TabIndex = 23;
			this->label8->Text = L"P(3)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(6, 136);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(30, 13);
			this->label9->TabIndex = 24;
			this->label9->Text = L"P(4)";
			// 
			// SetParamsBtn
			// 
			this->SetParamsBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->SetParamsBtn->Location = System::Drawing::Point(515, 303);
			this->SetParamsBtn->Name = L"SetParamsBtn";
			this->SetParamsBtn->Size = System::Drawing::Size(75, 23);
			this->SetParamsBtn->TabIndex = 25;
			this->SetParamsBtn->Text = L"Set";
			this->SetParamsBtn->UseVisualStyleBackColor = true;
			this->SetParamsBtn->Click += gcnew System::EventHandler(this, &FitParametersWindow::SetParamsBtn_Click);
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(515, 332);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(75, 23);
			this->CancelBtn->TabIndex = 26;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			// 
			// ConstrainBtn
			// 
			this->ConstrainBtn->AutoSize = true;
			this->ConstrainBtn->Location = System::Drawing::Point(183, 326);
			this->ConstrainBtn->Name = L"ConstrainBtn";
			this->ConstrainBtn->Size = System::Drawing::Size(70, 17);
			this->ConstrainBtn->TabIndex = 30;
			this->ConstrainBtn->Text = L"Constrain";
			this->ConstrainBtn->UseVisualStyleBackColor = true;
			this->ConstrainBtn->CheckedChanged += gcnew System::EventHandler(this, &FitParametersWindow::ConstrainBtn_CheckedChanged);
			// 
			// BoundsPnl
			// 
			this->BoundsPnl->Controls->Add(this->P7UBTxt);
			this->BoundsPnl->Controls->Add(this->P6UBTxt);
			this->BoundsPnl->Controls->Add(this->P5UBTxt);
			this->BoundsPnl->Controls->Add(this->P4UBTxt);
			this->BoundsPnl->Controls->Add(this->P3UBTxt);
			this->BoundsPnl->Controls->Add(this->P2UBTxt);
			this->BoundsPnl->Controls->Add(this->P1UBTxt);
			this->BoundsPnl->Controls->Add(this->P0UBTxt);
			this->BoundsPnl->Controls->Add(this->P7LBTxt);
			this->BoundsPnl->Controls->Add(this->P6LBTxt);
			this->BoundsPnl->Controls->Add(this->P5LBTxt);
			this->BoundsPnl->Controls->Add(this->P4LBTxt);
			this->BoundsPnl->Controls->Add(this->P3LBTxt);
			this->BoundsPnl->Controls->Add(this->P2LBTxt);
			this->BoundsPnl->Controls->Add(this->P1LBTxt);
			this->BoundsPnl->Controls->Add(this->P0LBTxt);
			this->BoundsPnl->Controls->Add(this->label4);
			this->BoundsPnl->Controls->Add(this->label3);
			this->BoundsPnl->Enabled = false;
			this->BoundsPnl->Location = System::Drawing::Point(183, 76);
			this->BoundsPnl->Name = L"BoundsPnl";
			this->BoundsPnl->Size = System::Drawing::Size(261, 244);
			this->BoundsPnl->TabIndex = 9;
			this->BoundsPnl->TabStop = false;
			this->BoundsPnl->Text = L"Parameter Constraints";
			// 
			// P7UBTxt
			// 
			this->P7UBTxt->Location = System::Drawing::Point(134, 211);
			this->P7UBTxt->Name = L"P7UBTxt";
			this->P7UBTxt->Size = System::Drawing::Size(120, 20);
			this->P7UBTxt->TabIndex = 24;
			this->P7UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P7UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P6UBTxt
			// 
			this->P6UBTxt->Location = System::Drawing::Point(134, 185);
			this->P6UBTxt->Name = L"P6UBTxt";
			this->P6UBTxt->Size = System::Drawing::Size(120, 20);
			this->P6UBTxt->TabIndex = 22;
			this->P6UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P6UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P5UBTxt
			// 
			this->P5UBTxt->Location = System::Drawing::Point(134, 159);
			this->P5UBTxt->Name = L"P5UBTxt";
			this->P5UBTxt->Size = System::Drawing::Size(120, 20);
			this->P5UBTxt->TabIndex = 20;
			this->P5UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P5UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P4UBTxt
			// 
			this->P4UBTxt->Location = System::Drawing::Point(134, 133);
			this->P4UBTxt->Name = L"P4UBTxt";
			this->P4UBTxt->Size = System::Drawing::Size(120, 20);
			this->P4UBTxt->TabIndex = 18;
			this->P4UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P4UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P3UBTxt
			// 
			this->P3UBTxt->Location = System::Drawing::Point(134, 107);
			this->P3UBTxt->Name = L"P3UBTxt";
			this->P3UBTxt->Size = System::Drawing::Size(120, 20);
			this->P3UBTxt->TabIndex = 16;
			this->P3UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P3UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P2UBTxt
			// 
			this->P2UBTxt->Location = System::Drawing::Point(134, 81);
			this->P2UBTxt->Name = L"P2UBTxt";
			this->P2UBTxt->Size = System::Drawing::Size(120, 20);
			this->P2UBTxt->TabIndex = 14;
			this->P2UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P2UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P1UBTxt
			// 
			this->P1UBTxt->Location = System::Drawing::Point(135, 55);
			this->P1UBTxt->Name = L"P1UBTxt";
			this->P1UBTxt->Size = System::Drawing::Size(120, 20);
			this->P1UBTxt->TabIndex = 12;
			this->P1UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P1UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P0UBTxt
			// 
			this->P0UBTxt->Location = System::Drawing::Point(135, 29);
			this->P0UBTxt->Name = L"P0UBTxt";
			this->P0UBTxt->Size = System::Drawing::Size(120, 20);
			this->P0UBTxt->TabIndex = 10;
			this->P0UBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P0UBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P7LBTxt
			// 
			this->P7LBTxt->Location = System::Drawing::Point(9, 211);
			this->P7LBTxt->Name = L"P7LBTxt";
			this->P7LBTxt->Size = System::Drawing::Size(120, 20);
			this->P7LBTxt->TabIndex = 23;
			this->P7LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P7LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P6LBTxt
			// 
			this->P6LBTxt->Location = System::Drawing::Point(9, 185);
			this->P6LBTxt->Name = L"P6LBTxt";
			this->P6LBTxt->Size = System::Drawing::Size(120, 20);
			this->P6LBTxt->TabIndex = 21;
			this->P6LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P6LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P5LBTxt
			// 
			this->P5LBTxt->Location = System::Drawing::Point(9, 159);
			this->P5LBTxt->Name = L"P5LBTxt";
			this->P5LBTxt->Size = System::Drawing::Size(120, 20);
			this->P5LBTxt->TabIndex = 19;
			this->P5LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P5LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P4LBTxt
			// 
			this->P4LBTxt->Location = System::Drawing::Point(9, 133);
			this->P4LBTxt->Name = L"P4LBTxt";
			this->P4LBTxt->Size = System::Drawing::Size(120, 20);
			this->P4LBTxt->TabIndex = 17;
			this->P4LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P4LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P3LBTxt
			// 
			this->P3LBTxt->Location = System::Drawing::Point(9, 107);
			this->P3LBTxt->Name = L"P3LBTxt";
			this->P3LBTxt->Size = System::Drawing::Size(120, 20);
			this->P3LBTxt->TabIndex = 15;
			this->P3LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P3LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P2LBTxt
			// 
			this->P2LBTxt->Location = System::Drawing::Point(9, 81);
			this->P2LBTxt->Name = L"P2LBTxt";
			this->P2LBTxt->Size = System::Drawing::Size(120, 20);
			this->P2LBTxt->TabIndex = 13;
			this->P2LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P2LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P1LBTxt
			// 
			this->P1LBTxt->Location = System::Drawing::Point(9, 55);
			this->P1LBTxt->Name = L"P1LBTxt";
			this->P1LBTxt->Size = System::Drawing::Size(120, 20);
			this->P1LBTxt->TabIndex = 11;
			this->P1LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P1LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P0LBTxt
			// 
			this->P0LBTxt->Location = System::Drawing::Point(9, 29);
			this->P0LBTxt->Name = L"P0LBTxt";
			this->P0LBTxt->Size = System::Drawing::Size(120, 20);
			this->P0LBTxt->TabIndex = 9;
			this->P0LBTxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P0LBTxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(6, 214);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(30, 13);
			this->label10->TabIndex = 36;
			this->label10->Text = L"P(7)";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(6, 188);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(30, 13);
			this->label11->TabIndex = 35;
			this->label11->Text = L"P(6)";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(6, 162);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(30, 13);
			this->label12->TabIndex = 34;
			this->label12->Text = L"P(5)";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->P7ITxt);
			this->groupBox1->Controls->Add(this->P6ITxt);
			this->groupBox1->Controls->Add(this->P5ITxt);
			this->groupBox1->Controls->Add(this->P4ITxt);
			this->groupBox1->Controls->Add(this->P3ITxt);
			this->groupBox1->Controls->Add(this->P2ITxt);
			this->groupBox1->Controls->Add(this->P1ITxt);
			this->groupBox1->Controls->Add(this->P0ITxt);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Location = System::Drawing::Point(8, 76);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(169, 244);
			this->groupBox1->TabIndex = 47;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Initial Parameters";
			// 
			// P7ITxt
			// 
			this->P7ITxt->Location = System::Drawing::Point(38, 211);
			this->P7ITxt->Name = L"P7ITxt";
			this->P7ITxt->Size = System::Drawing::Size(120, 20);
			this->P7ITxt->TabIndex = 8;
			this->P7ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P7ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P6ITxt
			// 
			this->P6ITxt->Location = System::Drawing::Point(38, 185);
			this->P6ITxt->Name = L"P6ITxt";
			this->P6ITxt->Size = System::Drawing::Size(120, 20);
			this->P6ITxt->TabIndex = 7;
			this->P6ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P6ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P5ITxt
			// 
			this->P5ITxt->Location = System::Drawing::Point(38, 159);
			this->P5ITxt->Name = L"P5ITxt";
			this->P5ITxt->Size = System::Drawing::Size(120, 20);
			this->P5ITxt->TabIndex = 6;
			this->P5ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P5ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P4ITxt
			// 
			this->P4ITxt->Location = System::Drawing::Point(38, 133);
			this->P4ITxt->Name = L"P4ITxt";
			this->P4ITxt->Size = System::Drawing::Size(120, 20);
			this->P4ITxt->TabIndex = 5;
			this->P4ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P4ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P3ITxt
			// 
			this->P3ITxt->Location = System::Drawing::Point(38, 107);
			this->P3ITxt->Name = L"P3ITxt";
			this->P3ITxt->Size = System::Drawing::Size(120, 20);
			this->P3ITxt->TabIndex = 4;
			this->P3ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P3ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P2ITxt
			// 
			this->P2ITxt->Location = System::Drawing::Point(38, 81);
			this->P2ITxt->Name = L"P2ITxt";
			this->P2ITxt->Size = System::Drawing::Size(120, 20);
			this->P2ITxt->TabIndex = 3;
			this->P2ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P2ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P1ITxt
			// 
			this->P1ITxt->Location = System::Drawing::Point(38, 55);
			this->P1ITxt->Name = L"P1ITxt";
			this->P1ITxt->Size = System::Drawing::Size(120, 20);
			this->P1ITxt->TabIndex = 2;
			this->P1ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P1ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// P0ITxt
			// 
			this->P0ITxt->Location = System::Drawing::Point(38, 29);
			this->P0ITxt->Name = L"P0ITxt";
			this->P0ITxt->Size = System::Drawing::Size(120, 20);
			this->P0ITxt->TabIndex = 1;
			this->P0ITxt->TextChanged += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_TextChanged);
			this->P0ITxt->Enter += gcnew System::EventHandler(this, &FitParametersWindow::P0ITxt_Enter);
			// 
			// GetLastBtn
			// 
			this->GetLastBtn->Location = System::Drawing::Point(450, 82);
			this->GetLastBtn->Name = L"GetLastBtn";
			this->GetLastBtn->Size = System::Drawing::Size(75, 23);
			this->GetLastBtn->TabIndex = 48;
			this->GetLastBtn->Text = L"Get Last";
			this->GetLastBtn->UseVisualStyleBackColor = true;
			this->GetLastBtn->Click += gcnew System::EventHandler(this, &FitParametersWindow::GetLastBtn_Click);
			// 
			// FitParametersWindow
			// 
			this->AcceptButton = this->SetParamsBtn;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(602, 367);
			this->ControlBox = false;
			this->Controls->Add(this->GetLastBtn);
			this->Controls->Add(this->ConstrainBtn);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->SetParamsBtn);
			this->Controls->Add(this->FitFcnTxt);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->BoundsPnl);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"FitParametersWindow";
			this->RightToLeftLayout = true;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Fit Parameters Window";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FitParametersWindow::FitParametersWindow_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FitParametersWindow::FitParametersWindow_Load);
			this->BoundsPnl->ResumeLayout(false);
			this->BoundsPnl->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

public: bool FUNCTION_SET = false;
public: int FUNCTION_NUM = -1;
public: int NPARAMS = -1;
public: void Set_Function(int num, array<double>^ xrange, array<double>^ yrange, array<double, 2>^ roi);
public: String^ FUNCTION = "";
array<Windows::Forms::TextBox^>^ PITXTARRAY;
array<Windows::Forms::TextBox^>^ PLBTXTARRAY;
array<Windows::Forms::TextBox^>^ PUBTXTARRAY;

private: String^ LASTTEXT = "";

private: System::Void SetParamsBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FitParametersWindow_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void FitParametersWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
private: System::Void ConstrainBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void P0ITxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void GetLastBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void P0ITxt_Enter(System::Object^  sender, System::EventArgs^  e);

};
}
