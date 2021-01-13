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
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace JPFITS;


namespace CCDLAB {

	/// <summary>
	/// Summary for GSEExtractImg
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class GSEExtractImg : public System::Windows::Forms::Form
	{


	public:
		GSEExtractImg(void)
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
		~GSEExtractImg()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FolderBrowserDialog^  FolderBrowserDlg;
	private: System::Windows::Forms::Button^  OpenImgBtn;
	public: System::Windows::Forms::OpenFileDialog^  OpenImgFileDlg;
	private: 


	private: System::Windows::Forms::ComboBox^  FileListDrop;

	private: System::Windows::Forms::ToolTip^  toolTip1;

	private: System::Windows::Forms::Button^  ViewWordsBtn;
	private: System::Windows::Forms::NumericUpDown^  StartWordUpD;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  NWordsUpD;
	private: System::ComponentModel::BackgroundWorker^  ExtractImgWrkr;
	private: System::Windows::Forms::DataGridView^  WordListGrid;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Word;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Hex;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Bin;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Dec;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  eXITToolStripMenuItem;
	private: System::Windows::Forms::Label^  SegmentLabel;

	private: System::Windows::Forms::NumericUpDown^  StartSegmentUpD;
	private: System::Windows::Forms::DataGridView^  SegmentInfoGrid;




	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::ToolStripMenuItem^  exitCCDLABToolStripMenuItem;
	private: System::Windows::Forms::Button^  SyncImageBtn;
	private: System::Windows::Forms::Button^  ExtractImagesBtn;
	private: System::Windows::Forms::Panel^  ExtractPanel;
	private: System::Windows::Forms::Button^  ViewImageBtn;
	private: System::Windows::Forms::Button^  SyncToDecBtn;



	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  ExtractCentroidsBtn;
	private: System::Windows::Forms::NumericUpDown^  CentroidResolutionUpD;


	private: System::Windows::Forms::Label^  label6;
	private: System::ComponentModel::BackgroundWorker^  ExtractCtrdWrkr;
	private: System::Windows::Forms::NumericUpDown^  dMmUpD;

	private: System::Windows::Forms::Label^  label7;


	private: System::Windows::Forms::CheckBox^  SubImChck;
	private: System::Windows::Forms::Label^  YLabel;

	private: System::Windows::Forms::Label^  XLabel;
	private: System::Windows::Forms::Panel^  ExtCentPanel;

	private: System::Windows::Forms::CheckBox^  SkipRampChck;
	private: System::Windows::Forms::NumericUpDown^  SkipToUpD;
	private: System::Windows::Forms::CheckBox^  SkipToChck;


	private: System::Windows::Forms::NumericUpDown^  EveryNUpD;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::CheckBox^  SkipToSgmtChck;
	private: System::Windows::Forms::CheckBox^  StatsOnlyChck;
	private: System::Windows::Forms::NumericUpDown^  DecSyncVal1;
	private: System::Windows::Forms::NumericUpDown^  DecSyncVal2;
private: System::ComponentModel::BackgroundWorker^  FitsResultsWriteWrkr;







private: System::Windows::Forms::ComboBox^  ChannelDrop;
private: System::Windows::Forms::ToolStripMenuItem^  ExtOptsMenu;



private: System::Windows::Forms::ToolStripMenuItem^  ExtractListChck;
private: System::Windows::Forms::Button^  AnalCRCBtn;
private: System::ComponentModel::BackgroundWorker^  CRCWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  ExtParityChck;
private: System::Windows::Forms::ToolStripMenuItem^  analysisToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  xDecs;
private: System::Windows::Forms::ToolStripMenuItem^  xInts;
private: System::Windows::Forms::ToolStripMenuItem^  max;


private: System::Windows::Forms::ToolStripMenuItem^  AugFilesChck;
private: System::Windows::Forms::CheckBox^  ViewSyncImgChck;
private: System::Windows::Forms::Button^  StripBtn;
private: System::ComponentModel::BackgroundWorker^  StripWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  OBTvsUVITClocksMenuItem;


private: System::Windows::Forms::ToolStripMenuItem^  centroidListImageCorrectionsToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  GSEApplyDistortionCorrectionChck;

private: System::Windows::Forms::ToolStripMenuItem^  GSEApplyFPNCorrectionChck;
private: System::Windows::Forms::ToolStripMenuItem^  FixBadTimeListsMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  FixBadTimesHighValuesChck;
private: System::Windows::Forms::ToolStripMenuItem^  FixBadTimesLowValuesChck;




























	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GSEExtractImg::typeid));
			this->FolderBrowserDlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->OpenImgBtn = (gcnew System::Windows::Forms::Button());
			this->OpenImgFileDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->FileListDrop = (gcnew System::Windows::Forms::ComboBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->StartWordUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->NWordsUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->SegmentLabel = (gcnew System::Windows::Forms::Label());
			this->StartSegmentUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->CentroidResolutionUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->dMmUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->SkipToUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->SkipToChck = (gcnew System::Windows::Forms::CheckBox());
			this->EveryNUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->DecSyncVal2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->DecSyncVal1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->ViewWordsBtn = (gcnew System::Windows::Forms::Button());
			this->ExtractImgWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->WordListGrid = (gcnew System::Windows::Forms::DataGridView());
			this->Word = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Hex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Bin = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Dec = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->eXITToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitCCDLABToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->analysisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xDecs = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xInts = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->max = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OBTvsUVITClocksMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FixBadTimeListsMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExtOptsMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExtParityChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AugFilesChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExtractListChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->centroidListImageCorrectionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->GSEApplyDistortionCorrectionChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->GSEApplyFPNCorrectionChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SegmentInfoGrid = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SyncImageBtn = (gcnew System::Windows::Forms::Button());
			this->ExtractImagesBtn = (gcnew System::Windows::Forms::Button());
			this->ExtractPanel = (gcnew System::Windows::Forms::Panel());
			this->StripBtn = (gcnew System::Windows::Forms::Button());
			this->ViewSyncImgChck = (gcnew System::Windows::Forms::CheckBox());
			this->AnalCRCBtn = (gcnew System::Windows::Forms::Button());
			this->ChannelDrop = (gcnew System::Windows::Forms::ComboBox());
			this->StatsOnlyChck = (gcnew System::Windows::Forms::CheckBox());
			this->SkipToSgmtChck = (gcnew System::Windows::Forms::CheckBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->SkipRampChck = (gcnew System::Windows::Forms::CheckBox());
			this->ExtCentPanel = (gcnew System::Windows::Forms::Panel());
			this->ExtractCentroidsBtn = (gcnew System::Windows::Forms::Button());
			this->YLabel = (gcnew System::Windows::Forms::Label());
			this->XLabel = (gcnew System::Windows::Forms::Label());
			this->SubImChck = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ViewImageBtn = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SyncToDecBtn = (gcnew System::Windows::Forms::Button());
			this->ExtractCtrdWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->FitsResultsWriteWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->CRCWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->StripWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->FixBadTimesLowValuesChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FixBadTimesHighValuesChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StartWordUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NWordsUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StartSegmentUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CentroidResolutionUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dMmUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SkipToUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EveryNUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DecSyncVal2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DecSyncVal1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->WordListGrid))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SegmentInfoGrid))->BeginInit();
			this->ExtractPanel->SuspendLayout();
			this->ExtCentPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// FolderBrowserDlg
			// 
			this->FolderBrowserDlg->Description = L"Select Folder to Save Extracted Files (a folder on a different drive than the *im"
				L"g file will speed this up)";
			// 
			// OpenImgBtn
			// 
			this->OpenImgBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OpenImgBtn->Location = System::Drawing::Point(3, 27);
			this->OpenImgBtn->Name = L"OpenImgBtn";
			this->OpenImgBtn->Size = System::Drawing::Size(101, 23);
			this->OpenImgBtn->TabIndex = 0;
			this->OpenImgBtn->Text = L"Open File(s)";
			this->OpenImgBtn->UseVisualStyleBackColor = true;
			this->OpenImgBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::OpenImgBtn_Click);
			// 
			// OpenImgFileDlg
			// 
			this->OpenImgFileDlg->DefaultExt = L"img";
			this->OpenImgFileDlg->Filter = L"GSE CCSDS File (*.img)|*.img|All Files  (*.*)|*.*";
			this->OpenImgFileDlg->Multiselect = true;
			this->OpenImgFileDlg->SupportMultiDottedExtensions = true;
			this->OpenImgFileDlg->Title = L"Select *.img File(s)";
			this->OpenImgFileDlg->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &GSEExtractImg::OpenImgFileDlg_FileOk);
			// 
			// FileListDrop
			// 
			this->FileListDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FileListDrop->Enabled = false;
			this->FileListDrop->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->FileListDrop->FormattingEnabled = true;
			this->FileListDrop->Location = System::Drawing::Point(112, 27);
			this->FileListDrop->MaxDropDownItems = 25;
			this->FileListDrop->Name = L"FileListDrop";
			this->FileListDrop->Size = System::Drawing::Size(607, 21);
			this->FileListDrop->TabIndex = 1;
			this->toolTip1->SetToolTip(this->FileListDrop, L"Ensure Files are Properly Sorted.  If not, re-select in the correct order.");
			this->FileListDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &GSEExtractImg::FileListDropDown_SelectedIndexChanged);
			// 
			// toolTip1
			// 
			this->toolTip1->AutoPopDelay = 8000;
			this->toolTip1->InitialDelay = 500;
			this->toolTip1->ReshowDelay = 500;
			// 
			// StartWordUpD
			// 
			this->StartWordUpD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->StartWordUpD->Location = System::Drawing::Point(2, 59);
			this->StartWordUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 786432000, 0, 0, 0 });
			this->StartWordUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->StartWordUpD->Name = L"StartWordUpD";
			this->StartWordUpD->Size = System::Drawing::Size(92, 20);
			this->StartWordUpD->TabIndex = 4;
			this->toolTip1->SetToolTip(this->StartWordUpD, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			this->StartWordUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->StartWordUpD->ValueChanged += gcnew System::EventHandler(this, &GSEExtractImg::StartWordUpD_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(109, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Segment Info";
			this->toolTip1->SetToolTip(this->label1, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(2, 82);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(45, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"#Words";
			this->toolTip1->SetToolTip(this->label2, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			// 
			// NWordsUpD
			// 
			this->NWordsUpD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->NWordsUpD->Location = System::Drawing::Point(2, 98);
			this->NWordsUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 268288, 0, 0, 0 });
			this->NWordsUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->NWordsUpD->Name = L"NWordsUpD";
			this->NWordsUpD->Size = System::Drawing::Size(92, 20);
			this->NWordsUpD->TabIndex = 7;
			this->toolTip1->SetToolTip(this->NWordsUpD, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			this->NWordsUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->NWordsUpD->ValueChanged += gcnew System::EventHandler(this, &GSEExtractImg::NWordsUpD_ValueChanged);
			// 
			// SegmentLabel
			// 
			this->SegmentLabel->AutoSize = true;
			this->SegmentLabel->Location = System::Drawing::Point(2, 4);
			this->SegmentLabel->Name = L"SegmentLabel";
			this->SegmentLabel->Size = System::Drawing::Size(52, 13);
			this->SegmentLabel->TabIndex = 13;
			this->SegmentLabel->Text = L"Segment:";
			this->SegmentLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolTip1->SetToolTip(this->SegmentLabel, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			// 
			// StartSegmentUpD
			// 
			this->StartSegmentUpD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 262, 0, 0, 0 });
			this->StartSegmentUpD->Location = System::Drawing::Point(2, 20);
			this->StartSegmentUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 768000, 0, 0, 0 });
			this->StartSegmentUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->StartSegmentUpD->Name = L"StartSegmentUpD";
			this->StartSegmentUpD->Size = System::Drawing::Size(92, 20);
			this->StartSegmentUpD->TabIndex = 12;
			this->toolTip1->SetToolTip(this->StartSegmentUpD, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			this->StartSegmentUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->StartSegmentUpD->ValueChanged += gcnew System::EventHandler(this, &GSEExtractImg::StartSegmentUpD_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(2, 43);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"Start Word";
			this->toolTip1->SetToolTip(this->label3, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			// 
			// label6
			// 
			this->label6->Location = System::Drawing::Point(2, 49);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(58, 13);
			this->label6->TabIndex = 27;
			this->label6->Text = L"Resolution";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolTip1->SetToolTip(this->label6, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			// 
			// CentroidResolutionUpD
			// 
			this->CentroidResolutionUpD->Location = System::Drawing::Point(62, 47);
			this->CentroidResolutionUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32, 0, 0, 0 });
			this->CentroidResolutionUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->CentroidResolutionUpD->Name = L"CentroidResolutionUpD";
			this->CentroidResolutionUpD->Size = System::Drawing::Size(32, 20);
			this->CentroidResolutionUpD->TabIndex = 28;
			this->toolTip1->SetToolTip(this->CentroidResolutionUpD, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			this->CentroidResolutionUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->CentroidResolutionUpD->ValueChanged += gcnew System::EventHandler(this, &GSEExtractImg::CentroidResolutionUpD_ValueChanged);
			// 
			// dMmUpD
			// 
			this->dMmUpD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 16, 0, 0, 0 });
			this->dMmUpD->Location = System::Drawing::Point(46, 73);
			this->dMmUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2048, 0, 0, 0 });
			this->dMmUpD->Name = L"dMmUpD";
			this->dMmUpD->Size = System::Drawing::Size(48, 20);
			this->dMmUpD->TabIndex = 30;
			this->toolTip1->SetToolTip(this->dMmUpD, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			this->dMmUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2048, 0, 0, 0 });
			// 
			// label7
			// 
			this->label7->Location = System::Drawing::Point(2, 75);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(45, 13);
			this->label7->TabIndex = 29;
			this->label7->Text = L"dMm <=";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolTip1->SetToolTip(this->label7, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			// 
			// SkipToUpD
			// 
			this->SkipToUpD->Enabled = false;
			this->SkipToUpD->Location = System::Drawing::Point(39, 522);
			this->SkipToUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->SkipToUpD->Name = L"SkipToUpD";
			this->SkipToUpD->Size = System::Drawing::Size(56, 20);
			this->SkipToUpD->TabIndex = 36;
			this->toolTip1->SetToolTip(this->SkipToUpD, L"Skips N Images before extraction.");
			// 
			// SkipToChck
			// 
			this->SkipToChck->AutoSize = true;
			this->SkipToChck->Location = System::Drawing::Point(2, 499);
			this->SkipToChck->Name = L"SkipToChck";
			this->SkipToChck->Size = System::Drawing::Size(92, 17);
			this->SkipToChck->TabIndex = 35;
			this->SkipToChck->Text = L"Start at Frame";
			this->toolTip1->SetToolTip(this->SkipToChck, L"Skips N Images before extraction.");
			this->SkipToChck->UseVisualStyleBackColor = true;
			this->SkipToChck->CheckedChanged += gcnew System::EventHandler(this, &GSEExtractImg::SkipNChck_CheckedChanged);
			// 
			// EveryNUpD
			// 
			this->EveryNUpD->Location = System::Drawing::Point(46, 570);
			this->EveryNUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->EveryNUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->EveryNUpD->Name = L"EveryNUpD";
			this->EveryNUpD->Size = System::Drawing::Size(48, 20);
			this->EveryNUpD->TabIndex = 37;
			this->toolTip1->SetToolTip(this->EveryNUpD, L"1-Based. 1 Word = 1 Line = 2 Bytes = UInt16");
			this->EveryNUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// DecSyncVal2
			// 
			this->DecSyncVal2->Location = System::Drawing::Point(41, 229);
			this->DecSyncVal2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
			this->DecSyncVal2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->DecSyncVal2->Name = L"DecSyncVal2";
			this->DecSyncVal2->Size = System::Drawing::Size(53, 20);
			this->DecSyncVal2->TabIndex = 37;
			this->toolTip1->SetToolTip(this->DecSyncVal2, L"Skips N Images before extraction.");
			this->DecSyncVal2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			// 
			// DecSyncVal1
			// 
			this->DecSyncVal1->Location = System::Drawing::Point(41, 203);
			this->DecSyncVal1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
			this->DecSyncVal1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->DecSyncVal1->Name = L"DecSyncVal1";
			this->DecSyncVal1->Size = System::Drawing::Size(53, 20);
			this->DecSyncVal1->TabIndex = 38;
			this->toolTip1->SetToolTip(this->DecSyncVal1, L"Skips N Images before extraction.");
			this->DecSyncVal1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			// 
			// ViewWordsBtn
			// 
			this->ViewWordsBtn->Location = System::Drawing::Point(346, 127);
			this->ViewWordsBtn->Name = L"ViewWordsBtn";
			this->ViewWordsBtn->Size = System::Drawing::Size(91, 25);
			this->ViewWordsBtn->TabIndex = 3;
			this->ViewWordsBtn->Text = L"View Words";
			this->ViewWordsBtn->UseVisualStyleBackColor = true;
			this->ViewWordsBtn->Visible = false;
			this->ViewWordsBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::ViewWordsBtn_Click);
			// 
			// ExtractImgWrkr
			// 
			this->ExtractImgWrkr->WorkerReportsProgress = true;
			this->ExtractImgWrkr->WorkerSupportsCancellation = true;
			this->ExtractImgWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSEExtractImg::ExtractImgWrkr_DoWork);
			this->ExtractImgWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSEExtractImg::ExtractImgWrkr_ProgressChanged);
			this->ExtractImgWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSEExtractImg::ExtractImgWrkr_RunWorkerCompleted);
			// 
			// WordListGrid
			// 
			this->WordListGrid->AllowUserToAddRows = false;
			this->WordListGrid->AllowUserToDeleteRows = false;
			this->WordListGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->WordListGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->WordListGrid->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableWithoutHeaderText;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->WordListGrid->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->WordListGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->WordListGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Word, this->Hex,
					this->Bin, this->Dec
			});
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->WordListGrid->DefaultCellStyle = dataGridViewCellStyle6;
			this->WordListGrid->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->WordListGrid->Location = System::Drawing::Point(326, 56);
			this->WordListGrid->Name = L"WordListGrid";
			dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle7->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle7->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle7->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle7->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->WordListGrid->RowHeadersDefaultCellStyle = dataGridViewCellStyle7;
			this->WordListGrid->RowHeadersVisible = false;
			this->WordListGrid->RowHeadersWidth = 4;
			this->WordListGrid->Size = System::Drawing::Size(393, 744);
			this->WordListGrid->TabIndex = 9;
			// 
			// Word
			// 
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			dataGridViewCellStyle2->Format = L"N0";
			dataGridViewCellStyle2->NullValue = nullptr;
			this->Word->DefaultCellStyle = dataGridViewCellStyle2;
			this->Word->HeaderText = L"Word #";
			this->Word->Name = L"Word";
			this->Word->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Hex
			// 
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			dataGridViewCellStyle3->NullValue = nullptr;
			this->Hex->DefaultCellStyle = dataGridViewCellStyle3;
			this->Hex->HeaderText = L"Hex";
			this->Hex->MaxInputLength = 4;
			this->Hex->MinimumWidth = 4;
			this->Hex->Name = L"Hex";
			this->Hex->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Bin
			// 
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			dataGridViewCellStyle4->NullValue = nullptr;
			this->Bin->DefaultCellStyle = dataGridViewCellStyle4;
			this->Bin->HeaderText = L"Bin";
			this->Bin->MaxInputLength = 16;
			this->Bin->Name = L"Bin";
			this->Bin->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Dec
			// 
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			dataGridViewCellStyle5->NullValue = nullptr;
			this->Dec->DefaultCellStyle = dataGridViewCellStyle5;
			this->Dec->HeaderText = L"Dec";
			this->Dec->MaxInputLength = 5;
			this->Dec->Name = L"Dec";
			this->Dec->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->eXITToolStripMenuItem,
					this->exitCCDLABToolStripMenuItem, this->analysisToolStripMenuItem, this->ExtOptsMenu
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(731, 24);
			this->menuStrip1->TabIndex = 11;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// eXITToolStripMenuItem
			// 
			this->eXITToolStripMenuItem->BackColor = System::Drawing::Color::LightGreen;
			this->eXITToolStripMenuItem->Name = L"eXITToolStripMenuItem";
			this->eXITToolStripMenuItem->Size = System::Drawing::Size(67, 20);
			this->eXITToolStripMenuItem->Text = L"EXIT This";
			this->eXITToolStripMenuItem->Click += gcnew System::EventHandler(this, &GSEExtractImg::eXITToolStripMenuItem_Click);
			// 
			// exitCCDLABToolStripMenuItem
			// 
			this->exitCCDLABToolStripMenuItem->BackColor = System::Drawing::Color::LightCoral;
			this->exitCCDLABToolStripMenuItem->Name = L"exitCCDLABToolStripMenuItem";
			this->exitCCDLABToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->exitCCDLABToolStripMenuItem->Text = L"Exit CCDLAB";
			this->exitCCDLABToolStripMenuItem->Click += gcnew System::EventHandler(this, &GSEExtractImg::button1_Click);
			// 
			// analysisToolStripMenuItem
			// 
			this->analysisToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->xDecs,
					this->xInts, this->max, this->OBTvsUVITClocksMenuItem, this->FixBadTimeListsMenuItem
			});
			this->analysisToolStripMenuItem->Name = L"analysisToolStripMenuItem";
			this->analysisToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->analysisToolStripMenuItem->Text = L"Analysis";
			// 
			// xDecs
			// 
			this->xDecs->Name = L"xDecs";
			this->xDecs->Size = System::Drawing::Size(175, 22);
			this->xDecs->Text = L"X/Y Fractionals";
			this->xDecs->Click += gcnew System::EventHandler(this, &GSEExtractImg::xDecs_Click);
			// 
			// xInts
			// 
			this->xInts->Name = L"xInts";
			this->xInts->Size = System::Drawing::Size(175, 22);
			this->xInts->Text = L"X/Y Integers";
			this->xInts->Click += gcnew System::EventHandler(this, &GSEExtractImg::xInts_Click);
			// 
			// max
			// 
			this->max->Name = L"max";
			this->max->Size = System::Drawing::Size(175, 22);
			this->max->Text = L"Max, Max-Min";
			this->max->Click += gcnew System::EventHandler(this, &GSEExtractImg::max_Click);
			// 
			// OBTvsUVITClocksMenuItem
			// 
			this->OBTvsUVITClocksMenuItem->Name = L"OBTvsUVITClocksMenuItem";
			this->OBTvsUVITClocksMenuItem->Size = System::Drawing::Size(175, 22);
			this->OBTvsUVITClocksMenuItem->Text = L"OBT && UVIT Clocks";
			this->OBTvsUVITClocksMenuItem->Click += gcnew System::EventHandler(this, &GSEExtractImg::OBTvsUVITClocksMenuItem_Click);
			// 
			// FixBadTimeListsMenuItem
			// 
			this->FixBadTimeListsMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->FixBadTimesHighValuesChck,
					this->FixBadTimesLowValuesChck
			});
			this->FixBadTimeListsMenuItem->Name = L"FixBadTimeListsMenuItem";
			this->FixBadTimeListsMenuItem->Size = System::Drawing::Size(175, 22);
			this->FixBadTimeListsMenuItem->Text = L"Fix Bad Time List(s)";
			this->FixBadTimeListsMenuItem->Click += gcnew System::EventHandler(this, &GSEExtractImg::FixBadTimeListsMenuItem_Click);
			// 
			// ExtOptsMenu
			// 
			this->ExtOptsMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ExtParityChck,
					this->AugFilesChck, this->ExtractListChck, this->centroidListImageCorrectionsToolStripMenuItem
			});
			this->ExtOptsMenu->Name = L"ExtOptsMenu";
			this->ExtOptsMenu->Size = System::Drawing::Size(168, 20);
			this->ExtOptsMenu->Text = L"PC Mode Extraction Options";
			// 
			// ExtParityChck
			// 
			this->ExtParityChck->CheckOnClick = true;
			this->ExtParityChck->Name = L"ExtParityChck";
			this->ExtParityChck->Size = System::Drawing::Size(243, 22);
			this->ExtParityChck->Text = L"Make Parity Error List";
			this->ExtParityChck->CheckedChanged += gcnew System::EventHandler(this, &GSEExtractImg::ExtParityChck_CheckedChanged);
			// 
			// AugFilesChck
			// 
			this->AugFilesChck->CheckOnClick = true;
			this->AugFilesChck->Name = L"AugFilesChck";
			this->AugFilesChck->Size = System::Drawing::Size(243, 22);
			this->AugFilesChck->Text = L"Make Augment Files";
			this->AugFilesChck->CheckedChanged += gcnew System::EventHandler(this, &GSEExtractImg::AugFilesChck_CheckedChanged);
			// 
			// ExtractListChck
			// 
			this->ExtractListChck->CheckOnClick = true;
			this->ExtractListChck->Name = L"ExtractListChck";
			this->ExtractListChck->Size = System::Drawing::Size(243, 22);
			this->ExtractListChck->Text = L"Make Centroid List";
			this->ExtractListChck->CheckedChanged += gcnew System::EventHandler(this, &GSEExtractImg::ExtractListChck_CheckedChanged);
			// 
			// centroidListImageCorrectionsToolStripMenuItem
			// 
			this->centroidListImageCorrectionsToolStripMenuItem->CheckOnClick = true;
			this->centroidListImageCorrectionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->GSEApplyDistortionCorrectionChck,
					this->GSEApplyFPNCorrectionChck
			});
			this->centroidListImageCorrectionsToolStripMenuItem->Name = L"centroidListImageCorrectionsToolStripMenuItem";
			this->centroidListImageCorrectionsToolStripMenuItem->Size = System::Drawing::Size(243, 22);
			this->centroidListImageCorrectionsToolStripMenuItem->Text = L"Centroid List/Image Corrections";
			this->centroidListImageCorrectionsToolStripMenuItem->Click += gcnew System::EventHandler(this, &GSEExtractImg::centroidListImageCorrectionsToolStripMenuItem_Click);
			// 
			// GSEApplyDistortionCorrectionChck
			// 
			this->GSEApplyDistortionCorrectionChck->CheckOnClick = true;
			this->GSEApplyDistortionCorrectionChck->Name = L"GSEApplyDistortionCorrectionChck";
			this->GSEApplyDistortionCorrectionChck->Size = System::Drawing::Size(219, 22);
			this->GSEApplyDistortionCorrectionChck->Text = L"Apply Distortion Correction";
			this->GSEApplyDistortionCorrectionChck->Click += gcnew System::EventHandler(this, &GSEExtractImg::GSEApplyDistortionCorrectionChck_Click);
			// 
			// GSEApplyFPNCorrectionChck
			// 
			this->GSEApplyFPNCorrectionChck->CheckOnClick = true;
			this->GSEApplyFPNCorrectionChck->Name = L"GSEApplyFPNCorrectionChck";
			this->GSEApplyFPNCorrectionChck->Size = System::Drawing::Size(219, 22);
			this->GSEApplyFPNCorrectionChck->Text = L"Apply FPN Correction";
			this->GSEApplyFPNCorrectionChck->Click += gcnew System::EventHandler(this, &GSEExtractImg::GSEApplyFPNCorrectionChck_Click);
			// 
			// SegmentInfoGrid
			// 
			this->SegmentInfoGrid->AllowUserToAddRows = false;
			this->SegmentInfoGrid->AllowUserToDeleteRows = false;
			this->SegmentInfoGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->SegmentInfoGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle8->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle8->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle8->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle8->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle8->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->SegmentInfoGrid->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle8;
			this->SegmentInfoGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->SegmentInfoGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle9->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->SegmentInfoGrid->DefaultCellStyle = dataGridViewCellStyle9;
			this->SegmentInfoGrid->Location = System::Drawing::Point(108, 72);
			this->SegmentInfoGrid->Name = L"SegmentInfoGrid";
			this->SegmentInfoGrid->ReadOnly = true;
			dataGridViewCellStyle10->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle10->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle10->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle10->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle10->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle10->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->SegmentInfoGrid->RowHeadersDefaultCellStyle = dataGridViewCellStyle10;
			this->SegmentInfoGrid->RowHeadersVisible = false;
			this->SegmentInfoGrid->RowHeadersWidth = 4;
			this->SegmentInfoGrid->Size = System::Drawing::Size(212, 728);
			this->SegmentInfoGrid->TabIndex = 16;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->dataGridViewTextBoxColumn1->HeaderText = L"Paramater";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn1->Width = 61;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->dataGridViewTextBoxColumn2->HeaderText = L"Value";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			this->dataGridViewTextBoxColumn2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn2->Width = 40;
			// 
			// SyncImageBtn
			// 
			this->SyncImageBtn->Location = System::Drawing::Point(3, 124);
			this->SyncImageBtn->Name = L"SyncImageBtn";
			this->SyncImageBtn->Size = System::Drawing::Size(91, 23);
			this->SyncImageBtn->TabIndex = 18;
			this->SyncImageBtn->Text = L"Sync to Image";
			this->SyncImageBtn->UseVisualStyleBackColor = true;
			this->SyncImageBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::SyncImageBtn_Click);
			// 
			// ExtractImagesBtn
			// 
			this->ExtractImagesBtn->Enabled = false;
			this->ExtractImagesBtn->Location = System::Drawing::Point(3, 328);
			this->ExtractImagesBtn->Name = L"ExtractImagesBtn";
			this->ExtractImagesBtn->Size = System::Drawing::Size(91, 38);
			this->ExtractImagesBtn->TabIndex = 19;
			this->ExtractImagesBtn->Text = L"Extract Int Mode Images";
			this->ExtractImagesBtn->UseVisualStyleBackColor = true;
			this->ExtractImagesBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::ExtractImagesBtn_Click);
			// 
			// ExtractPanel
			// 
			this->ExtractPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ExtractPanel->Controls->Add(this->StripBtn);
			this->ExtractPanel->Controls->Add(this->EveryNUpD);
			this->ExtractPanel->Controls->Add(this->ViewSyncImgChck);
			this->ExtractPanel->Controls->Add(this->AnalCRCBtn);
			this->ExtractPanel->Controls->Add(this->ChannelDrop);
			this->ExtractPanel->Controls->Add(this->DecSyncVal1);
			this->ExtractPanel->Controls->Add(this->DecSyncVal2);
			this->ExtractPanel->Controls->Add(this->StatsOnlyChck);
			this->ExtractPanel->Controls->Add(this->SkipToSgmtChck);
			this->ExtractPanel->Controls->Add(this->label8);
			this->ExtractPanel->Controls->Add(this->SkipToUpD);
			this->ExtractPanel->Controls->Add(this->SkipToChck);
			this->ExtractPanel->Controls->Add(this->SkipRampChck);
			this->ExtractPanel->Controls->Add(this->ExtCentPanel);
			this->ExtractPanel->Controls->Add(this->YLabel);
			this->ExtractPanel->Controls->Add(this->XLabel);
			this->ExtractPanel->Controls->Add(this->SubImChck);
			this->ExtractPanel->Controls->Add(this->ExtractImagesBtn);
			this->ExtractPanel->Controls->Add(this->label5);
			this->ExtractPanel->Controls->Add(this->ViewImageBtn);
			this->ExtractPanel->Controls->Add(this->SegmentLabel);
			this->ExtractPanel->Controls->Add(this->label4);
			this->ExtractPanel->Controls->Add(this->SyncImageBtn);
			this->ExtractPanel->Controls->Add(this->label3);
			this->ExtractPanel->Controls->Add(this->SyncToDecBtn);
			this->ExtractPanel->Controls->Add(this->StartWordUpD);
			this->ExtractPanel->Controls->Add(this->NWordsUpD);
			this->ExtractPanel->Controls->Add(this->label2);
			this->ExtractPanel->Controls->Add(this->StartSegmentUpD);
			this->ExtractPanel->Enabled = false;
			this->ExtractPanel->Location = System::Drawing::Point(4, 56);
			this->ExtractPanel->Name = L"ExtractPanel";
			this->ExtractPanel->Size = System::Drawing::Size(99, 725);
			this->ExtractPanel->TabIndex = 20;
			// 
			// StripBtn
			// 
			this->StripBtn->Location = System::Drawing::Point(3, 284);
			this->StripBtn->Name = L"StripBtn";
			this->StripBtn->Size = System::Drawing::Size(91, 38);
			this->StripBtn->TabIndex = 42;
			this->StripBtn->Text = L"Strip and Split RAW Files";
			this->StripBtn->UseVisualStyleBackColor = true;
			this->StripBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::StripBtn_Click);
			// 
			// ViewSyncImgChck
			// 
			this->ViewSyncImgChck->AutoSize = true;
			this->ViewSyncImgChck->Location = System::Drawing::Point(39, 153);
			this->ViewSyncImgChck->Name = L"ViewSyncImgChck";
			this->ViewSyncImgChck->Size = System::Drawing::Size(55, 17);
			this->ViewSyncImgChck->TabIndex = 41;
			this->ViewSyncImgChck->Text = L"View\?";
			this->ViewSyncImgChck->UseVisualStyleBackColor = true;
			// 
			// AnalCRCBtn
			// 
			this->AnalCRCBtn->Location = System::Drawing::Point(3, 399);
			this->AnalCRCBtn->Name = L"AnalCRCBtn";
			this->AnalCRCBtn->Size = System::Drawing::Size(88, 23);
			this->AnalCRCBtn->TabIndex = 40;
			this->AnalCRCBtn->Text = L"Analyze CRC\'s";
			this->AnalCRCBtn->UseVisualStyleBackColor = true;
			this->AnalCRCBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::AnalCRCBtn_Click);
			// 
			// ChannelDrop
			// 
			this->ChannelDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ChannelDrop->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->ChannelDrop->FormattingEnabled = true;
			this->ChannelDrop->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"FUV", L"NUV", L"VIS" });
			this->ChannelDrop->Location = System::Drawing::Point(2, 372);
			this->ChannelDrop->MaxDropDownItems = 25;
			this->ChannelDrop->Name = L"ChannelDrop";
			this->ChannelDrop->Size = System::Drawing::Size(74, 21);
			this->ChannelDrop->TabIndex = 21;
			this->ChannelDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &GSEExtractImg::ChannelDrop_SelectedIndexChanged);
			// 
			// StatsOnlyChck
			// 
			this->StatsOnlyChck->AutoSize = true;
			this->StatsOnlyChck->Location = System::Drawing::Point(2, 428);
			this->StatsOnlyChck->Name = L"StatsOnlyChck";
			this->StatsOnlyChck->Size = System::Drawing::Size(74, 17);
			this->StatsOnlyChck->TabIndex = 21;
			this->StatsOnlyChck->Text = L"Stats Only";
			this->StatsOnlyChck->UseVisualStyleBackColor = true;
			// 
			// SkipToSgmtChck
			// 
			this->SkipToSgmtChck->AutoSize = true;
			this->SkipToSgmtChck->Location = System::Drawing::Point(2, 451);
			this->SkipToSgmtChck->Name = L"SkipToSgmtChck";
			this->SkipToSgmtChck->Size = System::Drawing::Size(87, 17);
			this->SkipToSgmtChck->TabIndex = 39;
			this->SkipToSgmtChck->Text = L"Start at Sgmt";
			this->SkipToSgmtChck->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->Location = System::Drawing::Point(4, 548);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(90, 28);
			this->label8->TabIndex = 38;
			this->label8->Text = L"Extract Every N Frames";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// SkipRampChck
			// 
			this->SkipRampChck->Location = System::Drawing::Point(2, 474);
			this->SkipRampChck->Name = L"SkipRampChck";
			this->SkipRampChck->Size = System::Drawing::Size(89, 19);
			this->SkipRampChck->TabIndex = 34;
			this->SkipRampChck->Text = L"Skip Ramp";
			this->SkipRampChck->UseVisualStyleBackColor = true;
			// 
			// ExtCentPanel
			// 
			this->ExtCentPanel->Controls->Add(this->dMmUpD);
			this->ExtCentPanel->Controls->Add(this->ExtractCentroidsBtn);
			this->ExtCentPanel->Controls->Add(this->label7);
			this->ExtCentPanel->Controls->Add(this->label6);
			this->ExtCentPanel->Controls->Add(this->CentroidResolutionUpD);
			this->ExtCentPanel->Enabled = false;
			this->ExtCentPanel->Location = System::Drawing::Point(0, 621);
			this->ExtCentPanel->Name = L"ExtCentPanel";
			this->ExtCentPanel->Size = System::Drawing::Size(99, 98);
			this->ExtCentPanel->TabIndex = 21;
			// 
			// ExtractCentroidsBtn
			// 
			this->ExtractCentroidsBtn->Location = System::Drawing::Point(3, 3);
			this->ExtractCentroidsBtn->Name = L"ExtractCentroidsBtn";
			this->ExtractCentroidsBtn->Size = System::Drawing::Size(91, 38);
			this->ExtractCentroidsBtn->TabIndex = 26;
			this->ExtractCentroidsBtn->Text = L"Extract Centroid Image";
			this->ExtractCentroidsBtn->UseVisualStyleBackColor = true;
			this->ExtractCentroidsBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::ExtractCentroidsBtn_Click);
			// 
			// YLabel
			// 
			this->YLabel->AutoSize = true;
			this->YLabel->Location = System::Drawing::Point(4, 634);
			this->YLabel->Name = L"YLabel";
			this->YLabel->Size = System::Drawing::Size(50, 13);
			this->YLabel->TabIndex = 33;
			this->YLabel->Text = L"Y - 0:511";
			// 
			// XLabel
			// 
			this->XLabel->AutoSize = true;
			this->XLabel->Location = System::Drawing::Point(4, 621);
			this->XLabel->Name = L"XLabel";
			this->XLabel->Size = System::Drawing::Size(50, 13);
			this->XLabel->TabIndex = 32;
			this->XLabel->Text = L"X - 0:511";
			// 
			// SubImChck
			// 
			this->SubImChck->Enabled = false;
			this->SubImChck->Location = System::Drawing::Point(2, 596);
			this->SubImChck->Name = L"SubImChck";
			this->SubImChck->Size = System::Drawing::Size(89, 19);
			this->SubImChck->TabIndex = 31;
			this->SubImChck->Text = L"Sub Image";
			this->SubImChck->UseVisualStyleBackColor = true;
			this->SubImChck->CheckedChanged += gcnew System::EventHandler(this, &GSEExtractImg::SubImChck_CheckedChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(4, 232);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(31, 13);
			this->label5->TabIndex = 25;
			this->label5->Text = L"Val2:";
			// 
			// ViewImageBtn
			// 
			this->ViewImageBtn->Location = System::Drawing::Point(3, 255);
			this->ViewImageBtn->Name = L"ViewImageBtn";
			this->ViewImageBtn->Size = System::Drawing::Size(91, 23);
			this->ViewImageBtn->TabIndex = 21;
			this->ViewImageBtn->Text = L"View Image";
			this->ViewImageBtn->UseVisualStyleBackColor = true;
			this->ViewImageBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::ViewImageBtn_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(4, 206);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 13);
			this->label4->TabIndex = 24;
			this->label4->Text = L"Val1:";
			// 
			// SyncToDecBtn
			// 
			this->SyncToDecBtn->Location = System::Drawing::Point(3, 174);
			this->SyncToDecBtn->Name = L"SyncToDecBtn";
			this->SyncToDecBtn->Size = System::Drawing::Size(91, 23);
			this->SyncToDecBtn->TabIndex = 21;
			this->SyncToDecBtn->Text = L"Sync to dec Val";
			this->SyncToDecBtn->UseVisualStyleBackColor = true;
			this->SyncToDecBtn->Click += gcnew System::EventHandler(this, &GSEExtractImg::SyncToDecBtn_Click);
			// 
			// ExtractCtrdWrkr
			// 
			this->ExtractCtrdWrkr->WorkerReportsProgress = true;
			this->ExtractCtrdWrkr->WorkerSupportsCancellation = true;
			this->ExtractCtrdWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSEExtractImg::ExtractCtrdWrkr_DoWork);
			this->ExtractCtrdWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSEExtractImg::ExtractCtrdWrkr_ProgressChanged);
			this->ExtractCtrdWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSEExtractImg::ExtractCtrdWrkr_RunWorkerCompleted);
			// 
			// FitsResultsWriteWrkr
			// 
			this->FitsResultsWriteWrkr->WorkerReportsProgress = true;
			this->FitsResultsWriteWrkr->WorkerSupportsCancellation = true;
			this->FitsResultsWriteWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSEExtractImg::FitsResultsWriteWrkr_DoWork);
			this->FitsResultsWriteWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSEExtractImg::FitsResultsWriteWrkr_ProgressChanged);
			this->FitsResultsWriteWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSEExtractImg::FitsResultsWriteWrkr_RunWorkerCompleted);
			// 
			// CRCWrkr
			// 
			this->CRCWrkr->WorkerReportsProgress = true;
			this->CRCWrkr->WorkerSupportsCancellation = true;
			this->CRCWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSEExtractImg::CRCWrkr_DoWork);
			this->CRCWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSEExtractImg::CRCWrkr_ProgressChanged);
			this->CRCWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSEExtractImg::CRCWrkr_RunWorkerCompleted);
			// 
			// StripWrkr
			// 
			this->StripWrkr->WorkerReportsProgress = true;
			this->StripWrkr->WorkerSupportsCancellation = true;
			this->StripWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSEExtractImg::StripWrkr_DoWork);
			this->StripWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSEExtractImg::StripWrkr_ProgressChanged);
			this->StripWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSEExtractImg::StripWrkr_RunWorkerCompleted);
			// 
			// FixBadTimesLowValuesChck
			// 
			this->FixBadTimesLowValuesChck->CheckOnClick = true;
			this->FixBadTimesLowValuesChck->Name = L"FixBadTimesLowValuesChck";
			this->FixBadTimesLowValuesChck->Size = System::Drawing::Size(187, 22);
			this->FixBadTimesLowValuesChck->Text = L"Low Values are Good";
			this->FixBadTimesLowValuesChck->Click += gcnew System::EventHandler(this, &GSEExtractImg::FixBadTimesLowValuesChck_Click);
			// 
			// FixBadTimesHighValuesChck
			// 
			this->FixBadTimesHighValuesChck->Checked = true;
			this->FixBadTimesHighValuesChck->CheckOnClick = true;
			this->FixBadTimesHighValuesChck->CheckState = System::Windows::Forms::CheckState::Checked;
			this->FixBadTimesHighValuesChck->Name = L"FixBadTimesHighValuesChck";
			this->FixBadTimesHighValuesChck->Size = System::Drawing::Size(187, 22);
			this->FixBadTimesHighValuesChck->Text = L"High Values are Good";
			this->FixBadTimesHighValuesChck->Click += gcnew System::EventHandler(this, &GSEExtractImg::FixBadTimesHighValuesChck_Click);
			// 
			// GSEExtractImg
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(731, 812);
			this->Controls->Add(this->WordListGrid);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->FileListDrop);
			this->Controls->Add(this->OpenImgBtn);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->ExtractPanel);
			this->Controls->Add(this->SegmentInfoGrid);
			this->Controls->Add(this->ViewWordsBtn);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"GSEExtractImg";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Extract Data from *.img or *.raw File";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &GSEExtractImg::GSEExtractImg_FormClosed);
			this->Load += gcnew System::EventHandler(this, &GSEExtractImg::GSEExtractImg_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StartWordUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NWordsUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StartSegmentUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CentroidResolutionUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dMmUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SkipToUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EveryNUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DecSyncVal2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DecSyncVal1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->WordListGrid))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SegmentInfoGrid))->EndInit();
			this->ExtractPanel->ResumeLayout(false);
			this->ExtractPanel->PerformLayout();
			this->ExtCentPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

public:

static array<String^>^ FULLFILELIST;
static array<String^>^ FILELIST;
String^ FILEPATH;
static String^ SENDER = " ";
static int NIMAGE = 0;//just a counter for having different filenames when intserting into the IMAGESET
static unsigned __int32 IMFRCNT = 0;//image frame count: reset to zero in GSE when imaging mode changed or power up
static unsigned __int32 IMTIME = 0;//millisec
static int XSIZE = 0;//these next 4 are all zero based
static int YSIZE = 0;
static int XOFFSET = 0;
static int YOFFSET = 0;
static int PIXTHRSH = 0;
static int ENGTHRSH = 0;
static double ROWGAPT = 0;//usec
static int GAIN = 0;
static int STACKING = 0;
static int NORMLZN = 0;
static int BODL = 0;
static int BODH = 0;
static int BODF = 0;
static int ANDVOLTS_CMD = 0;
static int MCPVOLTS_CMD = 0;
static int PCVOLTS_CMD = 0;
static int ANDVOLTS_TEL = 0;
static int MCPVOLTS_TEL = 0;
static int CATVOLTS_TEL = 0;
static double HVUCURRENT_TEL = 0;

static double REAp5V = 0;
static double REAp5VpDN = 2.93; //mV

static double REAp3p3V = 0;
static double REAp3p3VpDN = 2.93;//		mV

static double REAp12V = 0;
static double REAm12V = 0;
static double REA12VpDN = 16.1;	//mV

static double HVUp30V = 0;
static double HVU30VpDN = 16.1;//		mV

static double HVUp15V = 0;
static double HVUm15V = 0;
static double HVU15VpDN = 16.1;//		mV

static double CPUp12V = 0;
static double CPUm12V = 0;
static double CPU12VpDN = 16.1;//	mV

static double ZEROVREF = 0;
static double ZEROVREFVpDN = 1.46;	//mV

static double REAp5VCUR = 0;
static double REA5VApDN = 3.08;	//mA

static double REAp3p3VCUR = 0;
static double REA3p3VApDN = 2.93;	//mA

static double REAm12VCUR = 0;
static double REAp12VCUR = 0;
static double REA12VApDN = 0.185;	//mA

static double HVUp30VCUR = 0;
static double HVU30VApDN = 0.432;	//mA

static double HVUp15VCUR = 0;
static double HVUm15VCUR = 0;
static double HVU15VApDN = 0.185;	//mA

static double CPUm12VCUR = 0;
static double CPUp12VCUR = 0;
static double CPU12VApDM = 0.185;   //mA

static double ANDCMDVpDN = 1.954;
static double MCPCMDVpDN = 0.977;
static double PCCMDVpDN = -0.195;
static double ANDTELVpDN = 9.4172;
static double MCPTELVpDN = 4.7086;
static double CATTELVpDN = -0.4709;
static double HVUTELApDN = 0.04709;  //uA 
static double RSETBIAS = 0;//V
static double RAMPTIME = 0;//sec
static double RAMPTTOT = 0;//total ramp time
static double TOTTIME = 0;
static double TOTFRAMS = 0;
static double GLOBRATE = 0;//count rate
static double SPOTRATE = 0;//count rate
static double RATEPSEC = 0;//count rate per second
static double FRAMPSEC = 0;
static String^ CHANNEL = "";
static int EXTRCN_CHANNEL = 0;//14, 15, 16 = FUV, NUV, VIS
static String^ MODE = "";
static String^ SOURCE = "";
static String^ ALGRTHM = "";
JPWaitBar::WaitBar^ wb;
static array<int>^ SUBRANGE = gcnew array<int>{0,511,0,511};//zero-based subrange for extraction
static bool ISSYNCHED = false;
static bool ISFRAMESYNCH = false;

static array<unsigned char>^ ARR = gcnew array<unsigned char>(1024*1024*500);

static unsigned __int32 FILENAMETIME = 0;



void PopulateSegmentInfo(System::Object^  sender, System::EventArgs^  e);
bool SeekNextImage(BinaryReader^ br);
unsigned __int16 ReadWord(BinaryReader^ br);
unsigned __int16 ReadWord_FromArr(array<unsigned char>^ arr, int byte_pos);
bool WriteImage(String^ fullfilename,BinaryReader^ br);
unsigned __int32 GetImageTime(BinaryReader^ br);
unsigned __int32 GetImageCount(BinaryReader^ br);
void AddImageInfoKeys(FITSImage^ fit);
void UpDateTELVolts(array<unsigned char>^ arr, int Seg_Num);
static bool Check_Even_Parity_Flag(unsigned __int16 word);
unsigned __int16 Calc_Segment_CRC(array<unsigned char>^ arr, int Segment_Num);
void Calc_img_CRC();

array<int>^ ImageParms(array<unsigned char>^ arr, int POSTN);
bool CheckSum(array<int>^ arr1, array<int>^ arr2);
static bool ISAC_Chunked = false;
int NSplits;
array<String^>^ delete_chunks;
String^ orignonchunkfile;





private: System::Void OpenImgBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OpenImgFileDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
private: System::Void ExtractImgWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ExtractImgWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ExtractImgWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void GSEExtractImg_Load(System::Object^  sender, System::EventArgs^  e);

private: System::Void NWordsUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ViewWordsBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //CCDLAB::GSEExtractImg::Close();
			 Application::Exit();
		 }
private: System::Void eXITToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //delete ARR;
			 ::GC::Collect();
			 CCDLAB::GSEExtractImg::Close();
		 }
private: System::Void StartWordUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void StartSegmentUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileListDropDown_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SyncImageBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ViewImageBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtractImagesBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SyncToDecBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtractCentroidsBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CentroidResolutionUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtractCtrdWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ExtractCtrdWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ExtractCtrdWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void GSEExtractImg_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
		 {
			GC::Collect();
			GC::WaitForFullGCApproach();
			GC::WaitForFullGCComplete();
			GC::WaitForPendingFinalizers();
		 }
private: System::Void SubImChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SkipNChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		 {
			 if (SkipToChck->Checked)
				SkipToUpD->Enabled = true;
			 else
				SkipToUpD->Enabled = false;
		 }
private: System::Void FitsResultsWriteWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void FitsResultsWriteWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void FitsResultsWriteWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void xDecs_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void xInts_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void max_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ChannelDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtParityChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtractListChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void AnalCRCBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CRCWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void CRCWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void CRCWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void AugFilesChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void StripWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void StripWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void StripWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void StripBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OBTvsUVITClocksMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void GSEApplyDistortionCorrectionChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void GSEApplyFPNCorrectionChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void centroidListImageCorrectionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FixBadTimeListsMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FixBadTimesHighValuesChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FixBadTimesLowValuesChck_Click(System::Object^  sender, System::EventArgs^  e);




};
}
