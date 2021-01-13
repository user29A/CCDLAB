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
	/// Summary for UVIT_HVUPlot
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class UVIT_HVUPlot : public System::Windows::Forms::Form
	{
	public:
		UVIT_HVUPlot(void)
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
		~UVIT_HVUPlot()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	public: System::Windows::Forms::GroupBox^  AnodePanel;
	public: System::Windows::Forms::Label^  AndMinTxt;
	public: System::Windows::Forms::Label^  AndMaxTxt;
	public: System::Windows::Forms::Label^  AndMeanTxt;



	public: System::Windows::Forms::Label^  AndMedianTxt;
	public: System::Windows::Forms::Label^  AndStdvTxt;


	private: System::Windows::Forms::Label^  SubImageMedianStatic;
	public: 
	private: System::Windows::Forms::Label^  SubImageMeanStatic;
	private: System::Windows::Forms::Label^  SubImageStdvStatic;
	private: System::Windows::Forms::Label^  SubImageMinStatic;
	private: System::Windows::Forms::Label^  SubImageMaxStatic;
	public: System::Windows::Forms::GroupBox^  groupBox1;
	public: System::Windows::Forms::Label^  CatMinTxt;
	public: System::Windows::Forms::Label^  CatMaxTxt;
	public: System::Windows::Forms::Label^  CatMeanTxt;
	private: 



	public: System::Windows::Forms::Label^  CatMedianTxt;
	public: System::Windows::Forms::Label^  CatStdvTxt;


	private: System::Windows::Forms::Label^  label6;
	public: 
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	public: System::Windows::Forms::GroupBox^  groupBox2;
	public: System::Windows::Forms::Label^  McpMinTxt;
	public: System::Windows::Forms::Label^  McpMaxTxt;
	public: System::Windows::Forms::Label^  McpMeanTxt;
	private: 



	public: System::Windows::Forms::Label^  McpMedianTxt;
	public: System::Windows::Forms::Label^  McpStdvTxt;


	private: System::Windows::Forms::Label^  label16;
	public: 
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitThisToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitCCDLABToolStripMenuItem;
	public: System::ComponentModel::BackgroundWorker^  PlotWrkr;
	public: System::Windows::Forms::GroupBox^  groupBox3;
	public: System::Windows::Forms::Label^  HVUMinTxt;
	public: System::Windows::Forms::Label^  HVUMaxTxt;
	public: System::Windows::Forms::Label^  HVUMeanTxt;
	public: System::Windows::Forms::Label^  HVUMedianTxt;
	public: System::Windows::Forms::Label^  HVUStdvTxt;
	private: System::Windows::Forms::Label^  label11;
	public: 
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	public: System::Windows::Forms::Label^  TitleTxt;
	private: CustomChart::MyChart^  jpChartAnode;
	private: CustomChart::MyChart^  jpChartMCP;
	private: CustomChart::MyChart^  jpChartCathode;
	private: CustomChart::MyChart^  jpChartHVU;
	public: 

	public: 




	public: 


	public: 

	public: 

	private: 
	private: 
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
			this->AnodePanel = (gcnew System::Windows::Forms::GroupBox());
			this->AndMinTxt = (gcnew System::Windows::Forms::Label());
			this->AndMaxTxt = (gcnew System::Windows::Forms::Label());
			this->AndMeanTxt = (gcnew System::Windows::Forms::Label());
			this->AndMedianTxt = (gcnew System::Windows::Forms::Label());
			this->AndStdvTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageMedianStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMeanStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageStdvStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMinStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMaxStatic = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->CatMinTxt = (gcnew System::Windows::Forms::Label());
			this->CatMaxTxt = (gcnew System::Windows::Forms::Label());
			this->CatMeanTxt = (gcnew System::Windows::Forms::Label());
			this->CatMedianTxt = (gcnew System::Windows::Forms::Label());
			this->CatStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->McpMinTxt = (gcnew System::Windows::Forms::Label());
			this->McpMaxTxt = (gcnew System::Windows::Forms::Label());
			this->McpMeanTxt = (gcnew System::Windows::Forms::Label());
			this->McpMedianTxt = (gcnew System::Windows::Forms::Label());
			this->McpStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->exitThisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitCCDLABToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlotWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->HVUMinTxt = (gcnew System::Windows::Forms::Label());
			this->HVUMaxTxt = (gcnew System::Windows::Forms::Label());
			this->HVUMeanTxt = (gcnew System::Windows::Forms::Label());
			this->HVUMedianTxt = (gcnew System::Windows::Forms::Label());
			this->HVUStdvTxt = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->TitleTxt = (gcnew System::Windows::Forms::Label());
			this->jpChartAnode = (gcnew CustomChart::MyChart());
			this->jpChartMCP = (gcnew CustomChart::MyChart());
			this->jpChartCathode = (gcnew CustomChart::MyChart());
			this->jpChartHVU = (gcnew CustomChart::MyChart());
			this->AnodePanel->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// AnodePanel
			// 
			this->AnodePanel->Controls->Add(this->AndMinTxt);
			this->AnodePanel->Controls->Add(this->AndMaxTxt);
			this->AnodePanel->Controls->Add(this->AndMeanTxt);
			this->AnodePanel->Controls->Add(this->AndMedianTxt);
			this->AnodePanel->Controls->Add(this->AndStdvTxt);
			this->AnodePanel->Controls->Add(this->SubImageMedianStatic);
			this->AnodePanel->Controls->Add(this->SubImageMeanStatic);
			this->AnodePanel->Controls->Add(this->SubImageStdvStatic);
			this->AnodePanel->Controls->Add(this->SubImageMinStatic);
			this->AnodePanel->Controls->Add(this->SubImageMaxStatic);
			this->AnodePanel->Location = System::Drawing::Point(12, 93);
			this->AnodePanel->Name = L"AnodePanel";
			this->AnodePanel->Size = System::Drawing::Size(137, 95);
			this->AnodePanel->TabIndex = 38;
			this->AnodePanel->TabStop = false;
			this->AnodePanel->Text = L"Anode Stats";
			// 
			// AndMinTxt
			// 
			this->AndMinTxt->Location = System::Drawing::Point(61, 17);
			this->AndMinTxt->Name = L"AndMinTxt";
			this->AndMinTxt->Size = System::Drawing::Size(70, 15);
			this->AndMinTxt->TabIndex = 31;
			this->AndMinTxt->Text = L"0";
			this->AndMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// AndMaxTxt
			// 
			this->AndMaxTxt->Location = System::Drawing::Point(61, 32);
			this->AndMaxTxt->Name = L"AndMaxTxt";
			this->AndMaxTxt->Size = System::Drawing::Size(70, 15);
			this->AndMaxTxt->TabIndex = 30;
			this->AndMaxTxt->Text = L"0";
			this->AndMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// AndMeanTxt
			// 
			this->AndMeanTxt->Location = System::Drawing::Point(61, 62);
			this->AndMeanTxt->Name = L"AndMeanTxt";
			this->AndMeanTxt->Size = System::Drawing::Size(70, 15);
			this->AndMeanTxt->TabIndex = 29;
			this->AndMeanTxt->Text = L"0";
			this->AndMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// AndMedianTxt
			// 
			this->AndMedianTxt->Location = System::Drawing::Point(67, 47);
			this->AndMedianTxt->Name = L"AndMedianTxt";
			this->AndMedianTxt->Size = System::Drawing::Size(64, 15);
			this->AndMedianTxt->TabIndex = 28;
			this->AndMedianTxt->Text = L"0";
			this->AndMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// AndStdvTxt
			// 
			this->AndStdvTxt->Location = System::Drawing::Point(61, 77);
			this->AndStdvTxt->Name = L"AndStdvTxt";
			this->AndStdvTxt->Size = System::Drawing::Size(70, 15);
			this->AndStdvTxt->TabIndex = 27;
			this->AndStdvTxt->Text = L"0";
			this->AndStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
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
			this->groupBox1->Controls->Add(this->CatMinTxt);
			this->groupBox1->Controls->Add(this->CatMaxTxt);
			this->groupBox1->Controls->Add(this->CatMeanTxt);
			this->groupBox1->Controls->Add(this->CatMedianTxt);
			this->groupBox1->Controls->Add(this->CatStdvTxt);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Location = System::Drawing::Point(12, 482);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(137, 95);
			this->groupBox1->TabIndex = 39;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Cathode Stats";
			// 
			// CatMinTxt
			// 
			this->CatMinTxt->Location = System::Drawing::Point(61, 17);
			this->CatMinTxt->Name = L"CatMinTxt";
			this->CatMinTxt->Size = System::Drawing::Size(70, 15);
			this->CatMinTxt->TabIndex = 31;
			this->CatMinTxt->Text = L"0";
			this->CatMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// CatMaxTxt
			// 
			this->CatMaxTxt->Location = System::Drawing::Point(61, 32);
			this->CatMaxTxt->Name = L"CatMaxTxt";
			this->CatMaxTxt->Size = System::Drawing::Size(70, 15);
			this->CatMaxTxt->TabIndex = 30;
			this->CatMaxTxt->Text = L"0";
			this->CatMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// CatMeanTxt
			// 
			this->CatMeanTxt->Location = System::Drawing::Point(61, 62);
			this->CatMeanTxt->Name = L"CatMeanTxt";
			this->CatMeanTxt->Size = System::Drawing::Size(70, 15);
			this->CatMeanTxt->TabIndex = 29;
			this->CatMeanTxt->Text = L"0";
			this->CatMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// CatMedianTxt
			// 
			this->CatMedianTxt->Location = System::Drawing::Point(67, 47);
			this->CatMedianTxt->Name = L"CatMedianTxt";
			this->CatMedianTxt->Size = System::Drawing::Size(64, 15);
			this->CatMedianTxt->TabIndex = 28;
			this->CatMedianTxt->Text = L"0";
			this->CatMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// CatStdvTxt
			// 
			this->CatStdvTxt->Location = System::Drawing::Point(61, 77);
			this->CatStdvTxt->Name = L"CatStdvTxt";
			this->CatStdvTxt->Size = System::Drawing::Size(70, 15);
			this->CatStdvTxt->TabIndex = 27;
			this->CatStdvTxt->Text = L"0";
			this->CatStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
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
			this->groupBox2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->groupBox2->Controls->Add(this->McpMinTxt);
			this->groupBox2->Controls->Add(this->McpMaxTxt);
			this->groupBox2->Controls->Add(this->McpMeanTxt);
			this->groupBox2->Controls->Add(this->McpMedianTxt);
			this->groupBox2->Controls->Add(this->McpStdvTxt);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->label19);
			this->groupBox2->Controls->Add(this->label20);
			this->groupBox2->Location = System::Drawing::Point(12, 294);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(137, 95);
			this->groupBox2->TabIndex = 40;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"MCP Stats";
			// 
			// McpMinTxt
			// 
			this->McpMinTxt->Location = System::Drawing::Point(61, 17);
			this->McpMinTxt->Name = L"McpMinTxt";
			this->McpMinTxt->Size = System::Drawing::Size(70, 15);
			this->McpMinTxt->TabIndex = 31;
			this->McpMinTxt->Text = L"0";
			this->McpMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// McpMaxTxt
			// 
			this->McpMaxTxt->Location = System::Drawing::Point(61, 32);
			this->McpMaxTxt->Name = L"McpMaxTxt";
			this->McpMaxTxt->Size = System::Drawing::Size(70, 15);
			this->McpMaxTxt->TabIndex = 30;
			this->McpMaxTxt->Text = L"0";
			this->McpMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// McpMeanTxt
			// 
			this->McpMeanTxt->Location = System::Drawing::Point(61, 62);
			this->McpMeanTxt->Name = L"McpMeanTxt";
			this->McpMeanTxt->Size = System::Drawing::Size(70, 15);
			this->McpMeanTxt->TabIndex = 29;
			this->McpMeanTxt->Text = L"0";
			this->McpMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// McpMedianTxt
			// 
			this->McpMedianTxt->Location = System::Drawing::Point(67, 47);
			this->McpMedianTxt->Name = L"McpMedianTxt";
			this->McpMedianTxt->Size = System::Drawing::Size(64, 15);
			this->McpMedianTxt->TabIndex = 28;
			this->McpMedianTxt->Text = L"0";
			this->McpMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// McpStdvTxt
			// 
			this->McpStdvTxt->Location = System::Drawing::Point(61, 77);
			this->McpStdvTxt->Name = L"McpStdvTxt";
			this->McpStdvTxt->Size = System::Drawing::Size(70, 15);
			this->McpStdvTxt->TabIndex = 27;
			this->McpStdvTxt->Text = L"0";
			this->McpStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
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
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->exitThisToolStripMenuItem, 
				this->exitCCDLABToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1180, 24);
			this->menuStrip1->TabIndex = 42;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// exitThisToolStripMenuItem
			// 
			this->exitThisToolStripMenuItem->BackColor = System::Drawing::Color::LightGreen;
			this->exitThisToolStripMenuItem->Name = L"exitThisToolStripMenuItem";
			this->exitThisToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->exitThisToolStripMenuItem->Text = L"Exit This";
			this->exitThisToolStripMenuItem->Click += gcnew System::EventHandler(this, &UVIT_HVUPlot::exitThisToolStripMenuItem_Click);
			// 
			// exitCCDLABToolStripMenuItem
			// 
			this->exitCCDLABToolStripMenuItem->BackColor = System::Drawing::Color::LightCoral;
			this->exitCCDLABToolStripMenuItem->Name = L"exitCCDLABToolStripMenuItem";
			this->exitCCDLABToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->exitCCDLABToolStripMenuItem->Text = L"Exit CCDLAB";
			this->exitCCDLABToolStripMenuItem->Click += gcnew System::EventHandler(this, &UVIT_HVUPlot::exitCCDLABToolStripMenuItem_Click);
			// 
			// PlotWrkr
			// 
			this->PlotWrkr->WorkerReportsProgress = true;
			this->PlotWrkr->WorkerSupportsCancellation = true;
			this->PlotWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &UVIT_HVUPlot::PlotWrkr_DoWork);
			this->PlotWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &UVIT_HVUPlot::PlotWrkr_RunWorkerCompleted);
			this->PlotWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &UVIT_HVUPlot::PlotWrkr_ProgressChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox3->Controls->Add(this->HVUMinTxt);
			this->groupBox3->Controls->Add(this->HVUMaxTxt);
			this->groupBox3->Controls->Add(this->HVUMeanTxt);
			this->groupBox3->Controls->Add(this->HVUMedianTxt);
			this->groupBox3->Controls->Add(this->HVUStdvTxt);
			this->groupBox3->Controls->Add(this->label11);
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Controls->Add(this->label13);
			this->groupBox3->Controls->Add(this->label14);
			this->groupBox3->Controls->Add(this->label15);
			this->groupBox3->Location = System::Drawing::Point(12, 677);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(137, 95);
			this->groupBox3->TabIndex = 43;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"HVU Stats";
			// 
			// HVUMinTxt
			// 
			this->HVUMinTxt->Location = System::Drawing::Point(61, 17);
			this->HVUMinTxt->Name = L"HVUMinTxt";
			this->HVUMinTxt->Size = System::Drawing::Size(70, 15);
			this->HVUMinTxt->TabIndex = 31;
			this->HVUMinTxt->Text = L"0";
			this->HVUMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// HVUMaxTxt
			// 
			this->HVUMaxTxt->Location = System::Drawing::Point(61, 32);
			this->HVUMaxTxt->Name = L"HVUMaxTxt";
			this->HVUMaxTxt->Size = System::Drawing::Size(70, 15);
			this->HVUMaxTxt->TabIndex = 30;
			this->HVUMaxTxt->Text = L"0";
			this->HVUMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// HVUMeanTxt
			// 
			this->HVUMeanTxt->Location = System::Drawing::Point(61, 62);
			this->HVUMeanTxt->Name = L"HVUMeanTxt";
			this->HVUMeanTxt->Size = System::Drawing::Size(70, 15);
			this->HVUMeanTxt->TabIndex = 29;
			this->HVUMeanTxt->Text = L"0";
			this->HVUMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// HVUMedianTxt
			// 
			this->HVUMedianTxt->Location = System::Drawing::Point(67, 47);
			this->HVUMedianTxt->Name = L"HVUMedianTxt";
			this->HVUMedianTxt->Size = System::Drawing::Size(64, 15);
			this->HVUMedianTxt->TabIndex = 28;
			this->HVUMedianTxt->Text = L"0";
			this->HVUMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// HVUStdvTxt
			// 
			this->HVUStdvTxt->Location = System::Drawing::Point(61, 77);
			this->HVUStdvTxt->Name = L"HVUStdvTxt";
			this->HVUStdvTxt->Size = System::Drawing::Size(70, 15);
			this->HVUStdvTxt->TabIndex = 27;
			this->HVUStdvTxt->Text = L"0";
			this->HVUStdvTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label11
			// 
			this->label11->Location = System::Drawing::Point(6, 46);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(55, 15);
			this->label11->TabIndex = 24;
			this->label11->Text = L"Median:";
			// 
			// label12
			// 
			this->label12->Location = System::Drawing::Point(6, 61);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(45, 15);
			this->label12->TabIndex = 26;
			this->label12->Text = L"Mean:";
			// 
			// label13
			// 
			this->label13->Location = System::Drawing::Point(6, 76);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(45, 15);
			this->label13->TabIndex = 25;
			this->label13->Text = L"Stdv:";
			// 
			// label14
			// 
			this->label14->Location = System::Drawing::Point(6, 16);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(30, 15);
			this->label14->TabIndex = 22;
			this->label14->Text = L"Min:";
			// 
			// label15
			// 
			this->label15->Location = System::Drawing::Point(6, 31);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(30, 15);
			this->label15->TabIndex = 23;
			this->label15->Text = L"Max:";
			// 
			// TitleTxt
			// 
			this->TitleTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->TitleTxt->Location = System::Drawing::Point(447, 9);
			this->TitleTxt->Name = L"TitleTxt";
			this->TitleTxt->Size = System::Drawing::Size(360, 15);
			this->TitleTxt->TabIndex = 44;
			this->TitleTxt->Text = L"0";
			this->TitleTxt->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// jpChartAnode
			// 
			this->jpChartAnode->Location = System::Drawing::Point(149, 27);
			this->jpChartAnode->Name = L"jpChartAnode";
			this->jpChartAnode->Size = System::Drawing::Size(1013, 200);
			this->jpChartAnode->TabIndex = 45;
			// 
			// jpChartMCP
			// 
			this->jpChartMCP->Location = System::Drawing::Point(149, 227);
			this->jpChartMCP->Name = L"jpChartMCP";
			this->jpChartMCP->Size = System::Drawing::Size(1013, 200);
			this->jpChartMCP->TabIndex = 46;
			// 
			// jpChartCathode
			// 
			this->jpChartCathode->Location = System::Drawing::Point(149, 427);
			this->jpChartCathode->Name = L"jpChartCathode";
			this->jpChartCathode->Size = System::Drawing::Size(1013, 200);
			this->jpChartCathode->TabIndex = 47;
			// 
			// jpChartHVU
			// 
			this->jpChartHVU->Location = System::Drawing::Point(149, 627);
			this->jpChartHVU->Name = L"jpChartHVU";
			this->jpChartHVU->Size = System::Drawing::Size(1013, 200);
			this->jpChartHVU->TabIndex = 48;
			// 
			// UVIT_HVUPlot
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1180, 837);
			this->Controls->Add(this->jpChartAnode);
			this->Controls->Add(this->jpChartHVU);
			this->Controls->Add(this->jpChartCathode);
			this->Controls->Add(this->jpChartMCP);
			this->Controls->Add(this->TitleTxt);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->AnodePanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"UVIT_HVUPlot";
			this->Text = L"HVU Telemetry Plot";
			this->TopMost = true;
			this->AnodePanel->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



public:

array<double,1>^ anode;
array<double,1>^ mcp;
array<double,1>^ cathode;
array<double,1>^ hvu;
array<double,1>^ tick;

String^ axisxLabel;


static FITSImage^ ANODE;
static FITSImage^ MCP;
static FITSImage^ CATHODE;
static FITSImage^ HVU;
static FITSImage^ TICK;
static JPWaitBar::WaitBar^ wb;
static int IND = 0;



	private: System::Void exitThisToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 /*::DialogResult res = ::MessageBox::Show("Are you sure?","Warning...",::MessageBoxButtons::OKCancel);
				 if (res == ::DialogResult::OK)*/
				 {
					 UVIT_HVUPlot::Close();
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

public:
void Plot_Telem(array<String^>^ files, int ind)
{
	IND = ind;
	if (IND == 0)
		axisxLabel = "Frame Time Tick (mins)";
	if (IND == 1)
		axisxLabel = "Time Since Start of Imaging (mins)";
	if (IND == 2)
		axisxLabel = "Frame Count Tick";

	FITSImage^ f = gcnew FITSImage(files[0], nullptr, true, false, false, false);
	TitleTxt->Text = f->GetKeyValue("SRCFILE");

	wb = gcnew JPWaitBar::WaitBar();
	PlotWrkr->RunWorkerAsync(files);
	wb->Show();
}

private: System::Void PlotWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ FileList = (array<String^>^)e->Argument;
	int NFiles = FileList->Length;
	anode = gcnew array<double,1>(NFiles);
	mcp = gcnew array<double,1>(NFiles);
	cathode = gcnew array<double,1>(NFiles);
	hvu = gcnew array<double,1>(NFiles);
	tick = gcnew array<double,1>(NFiles);
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
		anode[i] = ::Convert::ToDouble(f->GetKeyValue("AND_TEL"));
		mcp[i] = ::Convert::ToDouble(f->GetKeyValue("MCP_TEL"));
		cathode[i] = ::Convert::ToDouble(f->GetKeyValue("CAT_TEL"));
		hvu[i] = ::Convert::ToDouble(f->GetKeyValue("HVU_TEL"));

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
			tick[i] = num_cur - 1;
	}

	double rate;
	if (IND == 1)
		rate = (time_end - time_start)/(num_end - num_start);
	else
		rate = 1;
	for (int i = 0; i < NFiles; i++)
		tick[i] = tick[i] * rate;

	ANODE = gcnew FITSImage("dummy", anode, true, true);
	MCP = gcnew FITSImage("dummy", mcp, true, true);
	CATHODE = gcnew FITSImage("dummy", cathode, true, true);
	HVU = gcnew FITSImage("dummy", hvu, true, true);
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

	AndMinTxt->Text = ANODE->Min.ToString();
	AndMaxTxt->Text = ANODE->Max.ToString();
	AndMedianTxt->Text = ANODE->Median.ToString();
	AndMeanTxt->Text = ::Math::Round(ANODE->Mean,2).ToString();
	AndStdvTxt->Text = ::Math::Round(ANODE->Std,2).ToString();

	McpMinTxt->Text = MCP->Min.ToString();
	McpMaxTxt->Text = MCP->Max.ToString();
	McpMedianTxt->Text = MCP->Median.ToString();
	McpMeanTxt->Text = ::Math::Round(MCP->Mean,2).ToString();
	McpStdvTxt->Text = ::Math::Round(MCP->Std,2).ToString();

	CatMinTxt->Text = CATHODE->Min.ToString();
	CatMaxTxt->Text = CATHODE->Max.ToString();
	CatMedianTxt->Text = CATHODE->Median.ToString();
	CatMeanTxt->Text = ::Math::Round(CATHODE->Mean,2).ToString();
	CatStdvTxt->Text = ::Math::Round(CATHODE->Std,2).ToString();

	HVUMinTxt->Text = HVU->Min.ToString();
	HVUMaxTxt->Text = HVU->Max.ToString();
	HVUMedianTxt->Text = HVU->Median.ToString();
	HVUMeanTxt->Text = ::Math::Round(HVU->Mean,2).ToString();
	HVUStdvTxt->Text = ::Math::Round(HVU->Std,2).ToString();

	jpChartAnode->PlotXYData(tick,anode,"",axisxLabel,"Volts", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Anode");
	jpChartMCP->PlotXYData(tick,mcp,"",axisxLabel,"Volts", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "MCP");
	jpChartCathode->PlotXYData(tick,cathode,"",axisxLabel,"Volts", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "Cathode");
	jpChartHVU->PlotXYData(tick,hvu,"",axisxLabel,"Volts", Windows::Forms::DataVisualization::Charting::SeriesChartType::Line, "HVU");

	UVIT_HVUPlot::Show();
	UVIT_HVUPlot::Focus();

}










};
}
