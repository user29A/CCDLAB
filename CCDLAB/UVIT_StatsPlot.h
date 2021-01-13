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
using namespace JPFITS;


namespace CCDLAB {

	/// <summary>
	/// Summary for UVIT_StatsPlot
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class UVIT_StatsPlot : public System::Windows::Forms::Form
	{
	public:
		UVIT_StatsPlot(void)
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
		~UVIT_StatsPlot()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	public: System::Windows::Forms::GroupBox^  MinPanel;
	public: System::Windows::Forms::Label^  MinMinTxt;
	public: System::Windows::Forms::Label^  MinMaxTxt;
	public: System::Windows::Forms::Label^  MinMeanTxt;
	public: System::Windows::Forms::Label^  MinMedianTxt;
	public: System::Windows::Forms::Label^  MinStdvTxt;




	public: 







	private: System::Windows::Forms::Label^  SubImageMedianStatic;
	private: System::Windows::Forms::Label^  SubImageMeanStatic;
	private: System::Windows::Forms::Label^  SubImageStdvStatic;
	private: System::Windows::Forms::Label^  SubImageMinStatic;
	private: System::Windows::Forms::Label^  SubImageMaxStatic;
	public: System::Windows::Forms::GroupBox^  groupBox1;
	public: System::Windows::Forms::Label^  MaxMinTxt;
	public: System::Windows::Forms::Label^  MaxMaxTxt;
	public: System::Windows::Forms::Label^  MaxMeanTxt;
	private: 



	public: System::Windows::Forms::Label^  MaxMedianTxt;
	public: System::Windows::Forms::Label^  MaxStdvTxt;








	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	public: System::Windows::Forms::GroupBox^  groupBox2;
	public: System::Windows::Forms::Label^  MedMinTxt;
	public: System::Windows::Forms::Label^  MedMaxTxt;
	public: System::Windows::Forms::Label^  MedMeanTxt;
	private: 



	public: System::Windows::Forms::Label^  MedMedianTxt;
	public: System::Windows::Forms::Label^  MedStdvTxt;








	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	public: System::Windows::Forms::GroupBox^  groupBox3;
	public: System::Windows::Forms::Label^  MeanMinTxt;
	public: System::Windows::Forms::Label^  MeanMaxTxt;
	public: System::Windows::Forms::Label^  MeanMeanTxt;
	private: 



	public: System::Windows::Forms::Label^  MeanMedianTxt;
	public: System::Windows::Forms::Label^  MeanStdvTxt;








	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	public: System::Windows::Forms::GroupBox^  groupBox4;
public: System::Windows::Forms::Label^  StdMinTxt;
public: System::Windows::Forms::Label^  StdMaxTxt;
public: System::Windows::Forms::Label^  StdMeanTxt;
	private: 



public: System::Windows::Forms::Label^  StdMedianTxt;
public: System::Windows::Forms::Label^  StdStdvTxt;








	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::Label^  label39;
	private: System::Windows::Forms::Label^  label40;
public: System::ComponentModel::BackgroundWorker^  PlotWrkr;
private: System::Windows::Forms::MenuStrip^  menuStrip1;
public: 
private: System::Windows::Forms::ToolStripMenuItem^  exitThisToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  exitCCDLABToolStripMenuItem;
private: CustomChart::MyChart^  jpChartMin;
private: CustomChart::MyChart^  jpChartMax;
private: CustomChart::MyChart^  jpChartMedian;
private: CustomChart::MyChart^  jpChartMean;
private: CustomChart::MyChart^  jpChartStdv;





private: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(UVIT_StatsPlot::typeid));
			this->MinPanel = (gcnew System::Windows::Forms::GroupBox());
			this->MinMinTxt = (gcnew System::Windows::Forms::Label());
			this->MinMaxTxt = (gcnew System::Windows::Forms::Label());
			this->MinMeanTxt = (gcnew System::Windows::Forms::Label());
			this->MinMedianTxt = (gcnew System::Windows::Forms::Label());
			this->MinStdvTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageMedianStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMeanStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageStdvStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMinStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMaxStatic = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->MaxMinTxt = (gcnew System::Windows::Forms::Label());
			this->MaxMaxTxt = (gcnew System::Windows::Forms::Label());
			this->MaxMeanTxt = (gcnew System::Windows::Forms::Label());
			this->MaxMedianTxt = (gcnew System::Windows::Forms::Label());
			this->MaxStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->MedMinTxt = (gcnew System::Windows::Forms::Label());
			this->MedMaxTxt = (gcnew System::Windows::Forms::Label());
			this->MedMeanTxt = (gcnew System::Windows::Forms::Label());
			this->MedMedianTxt = (gcnew System::Windows::Forms::Label());
			this->MedStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->MeanMinTxt = (gcnew System::Windows::Forms::Label());
			this->MeanMaxTxt = (gcnew System::Windows::Forms::Label());
			this->MeanMeanTxt = (gcnew System::Windows::Forms::Label());
			this->MeanMedianTxt = (gcnew System::Windows::Forms::Label());
			this->MeanStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->StdMinTxt = (gcnew System::Windows::Forms::Label());
			this->StdMaxTxt = (gcnew System::Windows::Forms::Label());
			this->StdMeanTxt = (gcnew System::Windows::Forms::Label());
			this->StdMedianTxt = (gcnew System::Windows::Forms::Label());
			this->StdStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->PlotWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->exitThisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitCCDLABToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->jpChartMin = (gcnew CustomChart::MyChart());
			this->jpChartMax = (gcnew CustomChart::MyChart());
			this->jpChartMedian = (gcnew CustomChart::MyChart());
			this->jpChartMean = (gcnew CustomChart::MyChart());
			this->jpChartStdv = (gcnew CustomChart::MyChart());
			this->MinPanel->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// MinPanel
			// 
			this->MinPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->MinPanel->Controls->Add(this->MinMinTxt);
			this->MinPanel->Controls->Add(this->MinMaxTxt);
			this->MinPanel->Controls->Add(this->MinMeanTxt);
			this->MinPanel->Controls->Add(this->MinMedianTxt);
			this->MinPanel->Controls->Add(this->MinStdvTxt);
			this->MinPanel->Controls->Add(this->SubImageMedianStatic);
			this->MinPanel->Controls->Add(this->SubImageMeanStatic);
			this->MinPanel->Controls->Add(this->SubImageStdvStatic);
			this->MinPanel->Controls->Add(this->SubImageMinStatic);
			this->MinPanel->Controls->Add(this->SubImageMaxStatic);
			this->MinPanel->Location = System::Drawing::Point(12, 31);
			this->MinPanel->Name = L"MinPanel";
			this->MinPanel->Size = System::Drawing::Size(137, 95);
			this->MinPanel->TabIndex = 37;
			this->MinPanel->TabStop = false;
			this->MinPanel->Text = L"Frame Minimum Stats";
			// 
			// MinMinTxt
			// 
			this->MinMinTxt->Location = System::Drawing::Point(61, 17);
			this->MinMinTxt->Name = L"MinMinTxt";
			this->MinMinTxt->Size = System::Drawing::Size(70, 15);
			this->MinMinTxt->TabIndex = 31;
			this->MinMinTxt->Text = L"0";
			this->MinMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MinMaxTxt
			// 
			this->MinMaxTxt->Location = System::Drawing::Point(61, 32);
			this->MinMaxTxt->Name = L"MinMaxTxt";
			this->MinMaxTxt->Size = System::Drawing::Size(70, 15);
			this->MinMaxTxt->TabIndex = 30;
			this->MinMaxTxt->Text = L"0";
			this->MinMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MinMeanTxt
			// 
			this->MinMeanTxt->Location = System::Drawing::Point(61, 62);
			this->MinMeanTxt->Name = L"MinMeanTxt";
			this->MinMeanTxt->Size = System::Drawing::Size(70, 15);
			this->MinMeanTxt->TabIndex = 29;
			this->MinMeanTxt->Text = L"0";
			this->MinMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MinMedianTxt
			// 
			this->MinMedianTxt->Location = System::Drawing::Point(67, 47);
			this->MinMedianTxt->Name = L"MinMedianTxt";
			this->MinMedianTxt->Size = System::Drawing::Size(64, 15);
			this->MinMedianTxt->TabIndex = 28;
			this->MinMedianTxt->Text = L"0";
			this->MinMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MinStdvTxt
			// 
			this->MinStdvTxt->Location = System::Drawing::Point(61, 77);
			this->MinStdvTxt->Name = L"MinStdvTxt";
			this->MinStdvTxt->Size = System::Drawing::Size(70, 15);
			this->MinStdvTxt->TabIndex = 27;
			this->MinStdvTxt->Text = L"0";
			this->MinStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// SubImageMedianStatic
			// 
			this->SubImageMedianStatic->Location = System::Drawing::Point(6, 46);
			this->SubImageMedianStatic->Name = L"SubImageMedianStatic";
			this->SubImageMedianStatic->Size = System::Drawing::Size(55, 15);
			this->SubImageMedianStatic->TabIndex = 24;
			this->SubImageMedianStatic->Text = L"Median:";
			// 
			// SubImageMeanStatic
			// 
			this->SubImageMeanStatic->Location = System::Drawing::Point(6, 61);
			this->SubImageMeanStatic->Name = L"SubImageMeanStatic";
			this->SubImageMeanStatic->Size = System::Drawing::Size(45, 15);
			this->SubImageMeanStatic->TabIndex = 26;
			this->SubImageMeanStatic->Text = L"Mean:";
			// 
			// SubImageStdvStatic
			// 
			this->SubImageStdvStatic->Location = System::Drawing::Point(6, 76);
			this->SubImageStdvStatic->Name = L"SubImageStdvStatic";
			this->SubImageStdvStatic->Size = System::Drawing::Size(45, 15);
			this->SubImageStdvStatic->TabIndex = 25;
			this->SubImageStdvStatic->Text = L"Stdv:";
			// 
			// SubImageMinStatic
			// 
			this->SubImageMinStatic->Location = System::Drawing::Point(6, 16);
			this->SubImageMinStatic->Name = L"SubImageMinStatic";
			this->SubImageMinStatic->Size = System::Drawing::Size(30, 15);
			this->SubImageMinStatic->TabIndex = 22;
			this->SubImageMinStatic->Text = L"Min:";
			// 
			// SubImageMaxStatic
			// 
			this->SubImageMaxStatic->Location = System::Drawing::Point(6, 31);
			this->SubImageMaxStatic->Name = L"SubImageMaxStatic";
			this->SubImageMaxStatic->Size = System::Drawing::Size(30, 15);
			this->SubImageMaxStatic->TabIndex = 23;
			this->SubImageMaxStatic->Text = L"Max:";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox1->Controls->Add(this->MaxMinTxt);
			this->groupBox1->Controls->Add(this->MaxMaxTxt);
			this->groupBox1->Controls->Add(this->MaxMeanTxt);
			this->groupBox1->Controls->Add(this->MaxMedianTxt);
			this->groupBox1->Controls->Add(this->MaxStdvTxt);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Location = System::Drawing::Point(12, 187);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(137, 95);
			this->groupBox1->TabIndex = 38;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Frame Maximum Stats";
			// 
			// MaxMinTxt
			// 
			this->MaxMinTxt->Location = System::Drawing::Point(61, 17);
			this->MaxMinTxt->Name = L"MaxMinTxt";
			this->MaxMinTxt->Size = System::Drawing::Size(70, 15);
			this->MaxMinTxt->TabIndex = 31;
			this->MaxMinTxt->Text = L"0";
			this->MaxMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MaxMaxTxt
			// 
			this->MaxMaxTxt->Location = System::Drawing::Point(61, 32);
			this->MaxMaxTxt->Name = L"MaxMaxTxt";
			this->MaxMaxTxt->Size = System::Drawing::Size(70, 15);
			this->MaxMaxTxt->TabIndex = 30;
			this->MaxMaxTxt->Text = L"0";
			this->MaxMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MaxMeanTxt
			// 
			this->MaxMeanTxt->Location = System::Drawing::Point(61, 62);
			this->MaxMeanTxt->Name = L"MaxMeanTxt";
			this->MaxMeanTxt->Size = System::Drawing::Size(70, 15);
			this->MaxMeanTxt->TabIndex = 29;
			this->MaxMeanTxt->Text = L"0";
			this->MaxMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MaxMedianTxt
			// 
			this->MaxMedianTxt->Location = System::Drawing::Point(67, 47);
			this->MaxMedianTxt->Name = L"MaxMedianTxt";
			this->MaxMedianTxt->Size = System::Drawing::Size(64, 15);
			this->MaxMedianTxt->TabIndex = 28;
			this->MaxMedianTxt->Text = L"0";
			this->MaxMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MaxStdvTxt
			// 
			this->MaxStdvTxt->Location = System::Drawing::Point(61, 77);
			this->MaxStdvTxt->Name = L"MaxStdvTxt";
			this->MaxStdvTxt->Size = System::Drawing::Size(70, 15);
			this->MaxStdvTxt->TabIndex = 27;
			this->MaxStdvTxt->Text = L"0";
			this->MaxStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(6, 46);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(55, 15);
			this->label6->TabIndex = 24;
			this->label6->Text = L"Median:";
			// 
			// label7
			// 
			this->label7->Location = System::Drawing::Point(6, 61);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(45, 15);
			this->label7->TabIndex = 26;
			this->label7->Text = L"Mean:";
			// 
			// label8
			// 
			this->label8->Location = System::Drawing::Point(6, 76);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(45, 15);
			this->label8->TabIndex = 25;
			this->label8->Text = L"Stdv:";
			// 
			// label9
			// 
			this->label9->Location = System::Drawing::Point(6, 16);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(30, 15);
			this->label9->TabIndex = 22;
			this->label9->Text = L"Min:";
			// 
			// label10
			// 
			this->label10->Location = System::Drawing::Point(6, 31);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(30, 15);
			this->label10->TabIndex = 23;
			this->label10->Text = L"Max:";
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox2->Controls->Add(this->MedMinTxt);
			this->groupBox2->Controls->Add(this->MedMaxTxt);
			this->groupBox2->Controls->Add(this->MedMeanTxt);
			this->groupBox2->Controls->Add(this->MedMedianTxt);
			this->groupBox2->Controls->Add(this->MedStdvTxt);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->label19);
			this->groupBox2->Controls->Add(this->label20);
			this->groupBox2->Location = System::Drawing::Point(12, 353);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(137, 95);
			this->groupBox2->TabIndex = 39;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Frame Median Stats";
			// 
			// MedMinTxt
			// 
			this->MedMinTxt->Location = System::Drawing::Point(61, 17);
			this->MedMinTxt->Name = L"MedMinTxt";
			this->MedMinTxt->Size = System::Drawing::Size(70, 15);
			this->MedMinTxt->TabIndex = 31;
			this->MedMinTxt->Text = L"0";
			this->MedMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MedMaxTxt
			// 
			this->MedMaxTxt->Location = System::Drawing::Point(61, 32);
			this->MedMaxTxt->Name = L"MedMaxTxt";
			this->MedMaxTxt->Size = System::Drawing::Size(70, 15);
			this->MedMaxTxt->TabIndex = 30;
			this->MedMaxTxt->Text = L"0";
			this->MedMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MedMeanTxt
			// 
			this->MedMeanTxt->Location = System::Drawing::Point(61, 62);
			this->MedMeanTxt->Name = L"MedMeanTxt";
			this->MedMeanTxt->Size = System::Drawing::Size(70, 15);
			this->MedMeanTxt->TabIndex = 29;
			this->MedMeanTxt->Text = L"0";
			this->MedMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MedMedianTxt
			// 
			this->MedMedianTxt->Location = System::Drawing::Point(67, 47);
			this->MedMedianTxt->Name = L"MedMedianTxt";
			this->MedMedianTxt->Size = System::Drawing::Size(64, 15);
			this->MedMedianTxt->TabIndex = 28;
			this->MedMedianTxt->Text = L"0";
			this->MedMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MedStdvTxt
			// 
			this->MedStdvTxt->Location = System::Drawing::Point(61, 77);
			this->MedStdvTxt->Name = L"MedStdvTxt";
			this->MedStdvTxt->Size = System::Drawing::Size(70, 15);
			this->MedStdvTxt->TabIndex = 27;
			this->MedStdvTxt->Text = L"0";
			this->MedStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label16
			// 
			this->label16->Location = System::Drawing::Point(6, 46);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(55, 15);
			this->label16->TabIndex = 24;
			this->label16->Text = L"Median:";
			// 
			// label17
			// 
			this->label17->Location = System::Drawing::Point(6, 61);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(45, 15);
			this->label17->TabIndex = 26;
			this->label17->Text = L"Mean:";
			// 
			// label18
			// 
			this->label18->Location = System::Drawing::Point(6, 76);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(45, 15);
			this->label18->TabIndex = 25;
			this->label18->Text = L"Stdv:";
			// 
			// label19
			// 
			this->label19->Location = System::Drawing::Point(6, 16);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(30, 15);
			this->label19->TabIndex = 22;
			this->label19->Text = L"Min:";
			// 
			// label20
			// 
			this->label20->Location = System::Drawing::Point(6, 31);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(30, 15);
			this->label20->TabIndex = 23;
			this->label20->Text = L"Max:";
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox3->Controls->Add(this->MeanMinTxt);
			this->groupBox3->Controls->Add(this->MeanMaxTxt);
			this->groupBox3->Controls->Add(this->MeanMeanTxt);
			this->groupBox3->Controls->Add(this->MeanMedianTxt);
			this->groupBox3->Controls->Add(this->MeanStdvTxt);
			this->groupBox3->Controls->Add(this->label26);
			this->groupBox3->Controls->Add(this->label27);
			this->groupBox3->Controls->Add(this->label28);
			this->groupBox3->Controls->Add(this->label29);
			this->groupBox3->Controls->Add(this->label30);
			this->groupBox3->Location = System::Drawing::Point(12, 518);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(137, 95);
			this->groupBox3->TabIndex = 38;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Frame Mean Stats";
			// 
			// MeanMinTxt
			// 
			this->MeanMinTxt->Location = System::Drawing::Point(61, 17);
			this->MeanMinTxt->Name = L"MeanMinTxt";
			this->MeanMinTxt->Size = System::Drawing::Size(70, 15);
			this->MeanMinTxt->TabIndex = 31;
			this->MeanMinTxt->Text = L"0";
			this->MeanMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MeanMaxTxt
			// 
			this->MeanMaxTxt->Location = System::Drawing::Point(61, 32);
			this->MeanMaxTxt->Name = L"MeanMaxTxt";
			this->MeanMaxTxt->Size = System::Drawing::Size(70, 15);
			this->MeanMaxTxt->TabIndex = 30;
			this->MeanMaxTxt->Text = L"0";
			this->MeanMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MeanMeanTxt
			// 
			this->MeanMeanTxt->Location = System::Drawing::Point(61, 62);
			this->MeanMeanTxt->Name = L"MeanMeanTxt";
			this->MeanMeanTxt->Size = System::Drawing::Size(70, 15);
			this->MeanMeanTxt->TabIndex = 29;
			this->MeanMeanTxt->Text = L"0";
			this->MeanMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MeanMedianTxt
			// 
			this->MeanMedianTxt->Location = System::Drawing::Point(67, 47);
			this->MeanMedianTxt->Name = L"MeanMedianTxt";
			this->MeanMedianTxt->Size = System::Drawing::Size(64, 15);
			this->MeanMedianTxt->TabIndex = 28;
			this->MeanMedianTxt->Text = L"0";
			this->MeanMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MeanStdvTxt
			// 
			this->MeanStdvTxt->Location = System::Drawing::Point(61, 77);
			this->MeanStdvTxt->Name = L"MeanStdvTxt";
			this->MeanStdvTxt->Size = System::Drawing::Size(70, 15);
			this->MeanStdvTxt->TabIndex = 27;
			this->MeanStdvTxt->Text = L"0";
			this->MeanStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label26
			// 
			this->label26->Location = System::Drawing::Point(6, 46);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(55, 15);
			this->label26->TabIndex = 24;
			this->label26->Text = L"Median:";
			// 
			// label27
			// 
			this->label27->Location = System::Drawing::Point(6, 61);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(45, 15);
			this->label27->TabIndex = 26;
			this->label27->Text = L"Mean:";
			// 
			// label28
			// 
			this->label28->Location = System::Drawing::Point(6, 76);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(45, 15);
			this->label28->TabIndex = 25;
			this->label28->Text = L"Stdv:";
			// 
			// label29
			// 
			this->label29->Location = System::Drawing::Point(6, 16);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(30, 15);
			this->label29->TabIndex = 22;
			this->label29->Text = L"Min:";
			// 
			// label30
			// 
			this->label30->Location = System::Drawing::Point(6, 31);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(30, 15);
			this->label30->TabIndex = 23;
			this->label30->Text = L"Max:";
			// 
			// groupBox4
			// 
			this->groupBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox4->Controls->Add(this->StdMinTxt);
			this->groupBox4->Controls->Add(this->StdMaxTxt);
			this->groupBox4->Controls->Add(this->StdMeanTxt);
			this->groupBox4->Controls->Add(this->StdMedianTxt);
			this->groupBox4->Controls->Add(this->StdStdvTxt);
			this->groupBox4->Controls->Add(this->label36);
			this->groupBox4->Controls->Add(this->label37);
			this->groupBox4->Controls->Add(this->label38);
			this->groupBox4->Controls->Add(this->label39);
			this->groupBox4->Controls->Add(this->label40);
			this->groupBox4->Location = System::Drawing::Point(12, 684);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(137, 95);
			this->groupBox4->TabIndex = 40;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Frame Stdv Stats";
			// 
			// StdMinTxt
			// 
			this->StdMinTxt->Location = System::Drawing::Point(61, 17);
			this->StdMinTxt->Name = L"StdMinTxt";
			this->StdMinTxt->Size = System::Drawing::Size(70, 15);
			this->StdMinTxt->TabIndex = 31;
			this->StdMinTxt->Text = L"0";
			this->StdMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// StdMaxTxt
			// 
			this->StdMaxTxt->Location = System::Drawing::Point(61, 32);
			this->StdMaxTxt->Name = L"StdMaxTxt";
			this->StdMaxTxt->Size = System::Drawing::Size(70, 15);
			this->StdMaxTxt->TabIndex = 30;
			this->StdMaxTxt->Text = L"0";
			this->StdMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// StdMeanTxt
			// 
			this->StdMeanTxt->Location = System::Drawing::Point(61, 62);
			this->StdMeanTxt->Name = L"StdMeanTxt";
			this->StdMeanTxt->Size = System::Drawing::Size(70, 15);
			this->StdMeanTxt->TabIndex = 29;
			this->StdMeanTxt->Text = L"0";
			this->StdMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// StdMedianTxt
			// 
			this->StdMedianTxt->Location = System::Drawing::Point(67, 47);
			this->StdMedianTxt->Name = L"StdMedianTxt";
			this->StdMedianTxt->Size = System::Drawing::Size(64, 15);
			this->StdMedianTxt->TabIndex = 28;
			this->StdMedianTxt->Text = L"0";
			this->StdMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// StdStdvTxt
			// 
			this->StdStdvTxt->Location = System::Drawing::Point(61, 77);
			this->StdStdvTxt->Name = L"StdStdvTxt";
			this->StdStdvTxt->Size = System::Drawing::Size(70, 15);
			this->StdStdvTxt->TabIndex = 27;
			this->StdStdvTxt->Text = L"0";
			this->StdStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label36
			// 
			this->label36->Location = System::Drawing::Point(6, 46);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(55, 15);
			this->label36->TabIndex = 24;
			this->label36->Text = L"Median:";
			// 
			// label37
			// 
			this->label37->Location = System::Drawing::Point(6, 61);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(45, 15);
			this->label37->TabIndex = 26;
			this->label37->Text = L"Mean:";
			// 
			// label38
			// 
			this->label38->Location = System::Drawing::Point(6, 76);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(45, 15);
			this->label38->TabIndex = 25;
			this->label38->Text = L"Stdv:";
			// 
			// label39
			// 
			this->label39->Location = System::Drawing::Point(6, 16);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(30, 15);
			this->label39->TabIndex = 22;
			this->label39->Text = L"Min:";
			// 
			// label40
			// 
			this->label40->Location = System::Drawing::Point(6, 31);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(30, 15);
			this->label40->TabIndex = 23;
			this->label40->Text = L"Max:";
			// 
			// PlotWrkr
			// 
			this->PlotWrkr->WorkerReportsProgress = true;
			this->PlotWrkr->WorkerSupportsCancellation = true;
			this->PlotWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &UVIT_StatsPlot::PlotWrkr_DoWork);
			this->PlotWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &UVIT_StatsPlot::PlotWrkr_RunWorkerCompleted);
			this->PlotWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &UVIT_StatsPlot::PlotWrkr_ProgressChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->exitThisToolStripMenuItem, 
				this->exitCCDLABToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1099, 24);
			this->menuStrip1->TabIndex = 41;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// exitThisToolStripMenuItem
			// 
			this->exitThisToolStripMenuItem->BackColor = System::Drawing::Color::LightGreen;
			this->exitThisToolStripMenuItem->Name = L"exitThisToolStripMenuItem";
			this->exitThisToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->exitThisToolStripMenuItem->Text = L"Exit This";
			this->exitThisToolStripMenuItem->Click += gcnew System::EventHandler(this, &UVIT_StatsPlot::exitThisToolStripMenuItem_Click);
			// 
			// exitCCDLABToolStripMenuItem
			// 
			this->exitCCDLABToolStripMenuItem->BackColor = System::Drawing::Color::LightCoral;
			this->exitCCDLABToolStripMenuItem->Name = L"exitCCDLABToolStripMenuItem";
			this->exitCCDLABToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->exitCCDLABToolStripMenuItem->Text = L"Exit CCDLAB";
			this->exitCCDLABToolStripMenuItem->Click += gcnew System::EventHandler(this, &UVIT_StatsPlot::exitCCDLABToolStripMenuItem_Click);
			// 
			// jpChartMin
			// 
			this->jpChartMin->Location = System::Drawing::Point(155, 27);
			this->jpChartMin->Name = L"jpChartMin";
			this->jpChartMin->Size = System::Drawing::Size(932, 165);
			this->jpChartMin->TabIndex = 42;
			// 
			// jpChartMax
			// 
			this->jpChartMax->Location = System::Drawing::Point(155, 192);
			this->jpChartMax->Name = L"jpChartMax";
			this->jpChartMax->Size = System::Drawing::Size(932, 165);
			this->jpChartMax->TabIndex = 43;
			// 
			// jpChartMedian
			// 
			this->jpChartMedian->Location = System::Drawing::Point(155, 357);
			this->jpChartMedian->Name = L"jpChartMedian";
			this->jpChartMedian->Size = System::Drawing::Size(932, 165);
			this->jpChartMedian->TabIndex = 44;
			// 
			// jpChartMean
			// 
			this->jpChartMean->Location = System::Drawing::Point(155, 522);
			this->jpChartMean->Name = L"jpChartMean";
			this->jpChartMean->Size = System::Drawing::Size(932, 165);
			this->jpChartMean->TabIndex = 45;
			// 
			// jpChartStdv
			// 
			this->jpChartStdv->Location = System::Drawing::Point(155, 687);
			this->jpChartStdv->Name = L"jpChartStdv";
			this->jpChartStdv->Size = System::Drawing::Size(932, 165);
			this->jpChartStdv->TabIndex = 46;
			// 
			// UVIT_StatsPlot
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1099, 862);
			this->Controls->Add(this->jpChartMin);
			this->Controls->Add(this->jpChartStdv);
			this->Controls->Add(this->jpChartMean);
			this->Controls->Add(this->jpChartMedian);
			this->Controls->Add(this->jpChartMax);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->MinPanel);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"UVIT_StatsPlot";
			this->Text = L"Frame Stats Plot";
			this->TopMost = true;
			this->MinPanel->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public:

array<double>^ min;
array<double>^ max;
array<double>^ mean;
array<double>^ median;
array<double>^ stdv;
array<double>^ tick;

String^ axisxLabel;


static FITSImage^ MIN;
static FITSImage^ MAX;
static FITSImage^ MEDIAN;
static FITSImage^ MEAN;
static FITSImage^ STDV;
static FITSImage^ TICK;
static JPWaitBar::WaitBar^ wb;
static int IND = 0;


void Plot_Stats(array<String^>^ files, int ind)
{
	IND = ind;
	if (IND == 0)
		axisxLabel = "Frame Time Tick (mins)";
	if (IND == 1)
		axisxLabel = "Time Since Start of Imaging (mins)";
	if (IND == 2)
		axisxLabel = "Frame Count Tick";
	wb = gcnew JPWaitBar::WaitBar();
	PlotWrkr->RunWorkerAsync(files);
	wb->Show();
}



private: System::Void PlotWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ FileList = (array<String^>^)e->Argument;
	int NFiles = FileList->Length;
	mean = gcnew array<double>(NFiles);
	median = gcnew array<double>(NFiles);
	stdv = gcnew array<double>(NFiles);
	min = gcnew array<double>(NFiles);
	max = gcnew array<double>(NFiles);
	tick = gcnew array<double>(NFiles);
	array<double,2>^ dummy = gcnew array<double,2>(1,1);

	FITSImage^ f;
	double time_cur;
	double time_start;
	double time_end;
	double num_start;
	double num_end;
	double num_cur;
	wb->ProgressBar->Maximum = 100;
	int prog = 0;
	for (int i = 0; i < NFiles; i++)
	{
		if (wb->DialogResult == ::DialogResult::Cancel)
		{
			return;
		}
		if (100*i/NFiles > prog)
		{
			prog++;
			PlotWrkr->ReportProgress(prog);
		}


		f = gcnew FITSImage(FileList[i], nullptr, true, false, false, false);
		min[i] = ::Convert::ToDouble(f->GetKeyValue("MIN"));
		max[i] = ::Convert::ToDouble(f->GetKeyValue("MAX"));
		mean[i] = ::Convert::ToDouble(f->GetKeyValue("MEAN"));
		median[i] = ::Convert::ToDouble(f->GetKeyValue("MEDIAN"));
		stdv[i] = ::Convert::ToDouble(f->GetKeyValue("STDV"));

		if (i == 0)
		{
			time_start = ::Convert::ToDouble(f->GetKeyValue("IMFRTIME"))/60;//minutes
			num_start = ::Convert::ToDouble(f->GetKeyValue("IMFRCNT"));//frame number
		}
		if (i == NFiles-1)
		{
			time_end = ::Convert::ToDouble(f->GetKeyValue("IMFRTIME"))/60;//minutes
			num_end = ::Convert::ToDouble(f->GetKeyValue("IMFRCNT"));//frame number
		}
		time_cur = ::Convert::ToDouble(f->GetKeyValue("IMFRTIME"))/60;
		num_cur = ::Convert::ToDouble(f->GetKeyValue("IMFRCNT"));//frame number
		if (IND == 0)
			tick[i] = time_cur;
		else
			tick[i] = num_cur;
		
		f->SetImage(dummy, false, false);
	}
	double rate;
	if (IND == 1)
		rate = (time_end - time_start)/(num_end - num_start);
	else
		rate = 1;
	for (int i = 0; i < NFiles; i++)
		tick[i] = tick[i] * rate;

	MIN = gcnew FITSImage("dummy", min, true, true);
	MAX = gcnew FITSImage("dummy", max, true, true);
	MEDIAN = gcnew FITSImage("dummy", median, true, true);
	MEAN = gcnew FITSImage("dummy", mean, true, true);
	STDV = gcnew FITSImage("dummy", stdv, true, true);
}
private: System::Void PlotWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
		 {
			 wb->ProgressBar->Value = e->ProgressPercentage;
			 wb->Text = String::Concat("Gathering Stats...",e->ProgressPercentage,"%");
			 wb->TextMsg->Text = String::Concat("Completed ",e->ProgressPercentage,"%");
		 }
private: System::Void PlotWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
		 {
			wb->Close();
			if (wb->DialogResult == ::DialogResult::Cancel)
				return;
			MinMinTxt->Text = MIN->Min.ToString();
			MinMaxTxt->Text = MIN->Max.ToString();
			MinMedianTxt->Text = MIN->Median.ToString();
			MinMeanTxt->Text = ::Math::Round(MIN->Mean,2).ToString();
			MinStdvTxt->Text = ::Math::Round(MIN->Std,2).ToString();

			MaxMinTxt->Text = MAX->Min.ToString();
			MaxMaxTxt->Text = MAX->Max.ToString();
			MaxMedianTxt->Text = MAX->Median.ToString();
			MaxMeanTxt->Text = ::Math::Round(MAX->Mean,2).ToString();
			MaxStdvTxt->Text = ::Math::Round(MAX->Std,2).ToString();

			MedMinTxt->Text = MEDIAN->Min.ToString();
			MedMaxTxt->Text = MEDIAN->Max.ToString();
			MedMedianTxt->Text = MEDIAN->Median.ToString();
			MedMeanTxt->Text = ::Math::Round(MEDIAN->Mean,2).ToString();
			MedStdvTxt->Text = ::Math::Round(MEDIAN->Std,2).ToString();

			MeanMinTxt->Text = ::Math::Round(MEAN->Min,2).ToString();
			MeanMaxTxt->Text = ::Math::Round(MEAN->Max,2).ToString();
			MeanMedianTxt->Text = ::Math::Round(MEAN->Median,2).ToString();
			MeanMeanTxt->Text = ::Math::Round(MEAN->Mean,2).ToString();
			MeanStdvTxt->Text = ::Math::Round(MEAN->Std,2).ToString();

			StdMinTxt->Text = ::Math::Round(STDV->Min,2).ToString();
			StdMaxTxt->Text = ::Math::Round(STDV->Max,2).ToString();
			StdMedianTxt->Text = ::Math::Round(STDV->Median,2).ToString();
			StdMeanTxt->Text = ::Math::Round(STDV->Mean,2).ToString();
			StdStdvTxt->Text = ::Math::Round(STDV->Std,2).ToString();

			jpChartMin->PlotXYData(tick,min,"",axisxLabel,"", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Min");
			jpChartMax->PlotXYData(tick,max,"",axisxLabel,"", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Max");
			jpChartMean->PlotXYData(tick,mean,"",axisxLabel,"", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Mean");
			jpChartMedian->PlotXYData(tick,median,"",axisxLabel,"", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Median");
			jpChartStdv->PlotXYData(tick,stdv,"",axisxLabel,"", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Stdv");


			UVIT_StatsPlot::Show();
			UVIT_StatsPlot::Focus();
		 }


private: System::Void exitThisToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 /*::DialogResult res = ::MessageBox::Show("Are you sure?","Warning...",::MessageBoxButtons::OKCancel);
			 if (res == ::DialogResult::OK)*/
			 {
				 UVIT_StatsPlot::Close();
			 }
		 }
private: System::Void exitCCDLABToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 /*::DialogResult res = ::MessageBox::Show("Are you sure?","Warning...",::MessageBoxButtons::OKCancel);
			 if (res == ::DialogResult::OK)*/
			 {
				 ::Application::Exit();
			 }
		 }


};
}
