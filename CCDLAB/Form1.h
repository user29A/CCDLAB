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
#include "stdafx.h"
#include "stdio.h"
#include "BatchSaveDlg.h"
#include "EditKeyDlg.h"
#include "EditValueDlg.h"
#include "UVIT.h"
#include "GSEExtractImg.h"
#include "FitParametersWindow.h"
#include "RangeDlg.h"
#include "String.h"
#include "omp.h"
#include "UVIT_StatsPlot.h"
#include "UVIT_HVUPlot.h"
#include "JPPlot.h"
#include "About.h"
#include "HeaderKey.h"
#include "RADecBox.h"
#include "PSETableViewer.h"
#include "WCSAutoCVALList1.h"

namespace CCDLAB {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Windows::Forms::DataVisualization;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Threading;
	using namespace Microsoft::Win32;
	using namespace Microsoft::VisualBasic;

	//referenced
	using namespace MathWorks::MATLAB::NET::Arrays;
	using namespace MathWorks::MATLAB::NET::Utility;
	using namespace MLCCDLAB;
	using namespace JPFITS;

	static void SetReg(System::String^ ProgramName, System::String^ KeyName, System::Object^ KeyValue)
	{
		RegistryKey^ User = Registry::CurrentUser;
		RegistryKey^ SW = User->OpenSubKey("Software", true);
		RegistryKey^ AstroWerks = SW->CreateSubKey("AstroWerks");
		RegistryKey^ SUBKEY = AstroWerks->CreateSubKey(ProgramName);
		SUBKEY->SetValue(KeyName, KeyValue);
	}
	static Object^ GetReg(System::String^ ProgramName, System::String^ KeyName)
	{
		RegistryKey^ User = Registry::CurrentUser;
		RegistryKey^ SW = User->OpenSubKey("Software", true);
		RegistryKey^ AstroWerks = SW->CreateSubKey("AstroWerks");
		RegistryKey^ SUBKEY = AstroWerks->CreateSubKey(ProgramName);
		Object ^ result = SUBKEY->GetValue(KeyName);
		return result;
	}

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			array<String^>^ startargs = gcnew array<String^>(0);
			Form1::InitializeVars(startargs);
		}

		Form1(array<System::String ^>^ startargs)
		{
			InitializeComponent();

			Form1::InitializeVars(startargs);
		}
		
#pragma region Windows Form Objects

	private: System::Windows::Forms::Button^  ManRegBtn;
	private: System::Windows::Forms::Button^  AutoRegBtn;




	private: System::Windows::Forms::ToolStripMenuItem^  HCInsertCurrent;
	private: System::Windows::Forms::ToolStripMenuItem^  HCInsertBatch;
	private: System::Windows::Forms::ToolStripMenuItem^  HCRemove;
	private: System::Windows::Forms::ToolStripMenuItem^  HCRemoveCurrent;
	private: System::Windows::Forms::ToolStripMenuItem^  HCRemoveBatch;

	private: System::Windows::Forms::Button^  BinBtn;
	private: System::Windows::Forms::GroupBox^  ImageOpsPnl;

	private: System::Windows::Forms::Label^  ImageSizeStatic;
	private: System::Windows::Forms::Label^  ImageSizeTxt;
	private: System::Windows::Forms::ComboBox^  ReplaceImagePtsDrop;
	private: System::Windows::Forms::Button^  CutSubImBtn;
	private: System::Windows::Forms::NumericUpDown^  ScmTxt;
	private: System::Windows::Forms::CheckBox^  SCMChck;
	private: System::Windows::Forms::ToolStripMenuItem^  HCExtract;
	private: System::Windows::Forms::ToolStripMenuItem^  HCExtractKeyValue;
    private: System::Windows::Forms::MenuStrip^  MainMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  FMLoad;
	private: System::Windows::Forms::ToolStripMenuItem^  FMAdd;
	private: System::Windows::Forms::ToolStripMenuItem^  FMFind;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  FMViewFound;
	private: System::Windows::Forms::ToolStripMenuItem^  FMReload;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  FMSave;
	private: System::Windows::Forms::ToolStripMenuItem^  FMSaveBatch;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  FMQuit;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
	private: System::Windows::Forms::ToolStripMenuItem^  EditMenu;




	private: System::Windows::Forms::ToolStripMenuItem^  EMBatch;
	private: System::Windows::Forms::ToolStripMenuItem^  EMBatchBias;
	private: System::Windows::Forms::ToolStripMenuItem^  EMBatchDark;
	private: System::Windows::Forms::ToolStripMenuItem^  EMBatchFlat;
	private: System::Windows::Forms::GroupBox^  ImageBatchRedxnPnl;
	private: System::Windows::Forms::ToolStripButton^  TBOpenFound;
	private: System::Windows::Forms::ToolStripMenuItem^  FMOpenFound;
	private: System::Windows::Forms::ListBox^  HeaderKeyValTxt;
	private: System::Windows::Forms::ListBox^  HeaderKeyComTxt;
	private: System::Windows::Forms::ContextMenuStrip^  HeaderCntxt;

	private: System::Windows::Forms::ToolStripMenuItem^  HCInsert;
	private: System::Windows::Forms::ListBox^  HeaderKeyTxt;
	private: System::Windows::Forms::ToolStripMenuItem^  HCEdit;
	private: System::Windows::Forms::ComboBox^  FindPtsDrop;
	private: System::Windows::Forms::TextBox^  ReplaceImagePtsTxt;
	private: System::Windows::Forms::Button^  ReplaceImagePtsBtn;
	private: System::Windows::Forms::Button^  FindImagePtsBtn;
	private: System::Windows::Forms::TextBox^  FindImagePtsTxt;
	private: System::Windows::Forms::CheckBox^  ViewHeaderBtn;
	private: System::Windows::Forms::Label^  ViewSelectionStatic;
	private: System::Windows::Forms::Button^  ViewNextBtn;
	private: System::Windows::Forms::Button^  ViewLastbtn;
	private: System::Windows::Forms::Button^  MoveUpBtn;
	private: System::Windows::Forms::Button^  MoveDownBtn;
	private: System::Windows::Forms::Button^  DeleteFileBtn;
	private: System::Windows::Forms::Button^  SingleOutBtn;

	private: System::Windows::Forms::NumericUpDown^  HalfWidthXUpD;



	private: System::Windows::Forms::RadioButton^  SubImageBtn;
	private: System::Windows::Forms::GroupBox^  SubImagePanel;
	private: System::Windows::Forms::Label^  SubImageYTxt;
	private: System::Windows::Forms::Label^  SubImageXTxt;
	private: System::Windows::Forms::Label^  SubImageYStatic;
	private: System::Windows::Forms::Label^  SubImageXStatic;
	private: System::Windows::Forms::Label^  SubImageMinTxt;
	private: System::Windows::Forms::Label^  SubImageMaxTxt;
	private: System::Windows::Forms::Label^  SubImageMeanTxt;
	private: System::Windows::Forms::Label^  SubImageMedianTxt;
	private: System::Windows::Forms::Label^  SubImageStdTxt;
	private: System::Windows::Forms::Label^  SubImageMedianStatic;
	private: System::Windows::Forms::Label^  SubImageMeanStatic;
	private: System::Windows::Forms::Label^  SubImageStdvStatic;
	private: System::Windows::Forms::Label^  SubImageMinStatic;
	private: System::Windows::Forms::Label^  SubImageMaxStatic;
	private: System::Windows::Forms::CheckBox^  ScaleContrastChck;
private: System::Windows::Forms::ToolTip^  Tooltip;


	private: System::Windows::Forms::Label^  HalfWidthStatic;

	private: System::Windows::Forms::Timer^  BlinkTimer;


	private: System::Windows::Forms::GroupBox^  FileInfoPanel;
private: System::Windows::Forms::Label^  InfoTxt4;

private: System::Windows::Forms::Label^  InfoStatic4;

	private: System::Windows::Forms::Label^  ImageMedianTxt;
	private: System::Windows::Forms::Label^  ImageMinStatic;
private: System::Windows::Forms::Label^  InfoTxt5;

private: System::Windows::Forms::Label^  InfoTxt1;

private: System::Windows::Forms::Label^  InfoStatic1;
private: System::Windows::Forms::Label^  InfoStatic3;
private: System::Windows::Forms::Label^  InfoTxt2;
private: System::Windows::Forms::Label^  InfoTxt3;




private: System::Windows::Forms::Label^  InfoStatic2;

	private: System::Windows::Forms::Label^  FileNameStatic;
private: System::Windows::Forms::Label^  InfoStatic5;

	private: System::Windows::Forms::Label^  ImageMaxStatic;
	private: System::Windows::Forms::Label^  ImageMedianStatic;
	private: System::Windows::Forms::Label^  ImageMeanStatic;
private: System::Windows::Forms::Label^  ImageStdvStatic;

	private: System::Windows::Forms::Label^  ImageMinTxt;
	private: System::Windows::Forms::Label^  ImageMeanTxt;
	private: System::Windows::Forms::Label^  ImageStdTxt;
	private: System::Windows::Forms::Label^  ImageMaxTxt;
	private: System::Windows::Forms::Label^  FileNameTxt;

	private: System::Windows::Forms::Label^  FileDirectoryStatic;
	private: System::Windows::Forms::GroupBox^  ContrastPanel;
	private: System::Windows::Forms::ComboBox^  ContrastScaleDrop;
	private: System::Windows::Forms::RadioButton^  ContrastFullRad;
	private: System::Windows::Forms::GroupBox^  ContrastModePanel;
	private: System::Windows::Forms::CheckBox^  InvertContrastChck;
	private: System::Windows::Forms::RadioButton^  RelativeContrast;
	private: System::Windows::Forms::RadioButton^  AutoContrast;
	private: System::Windows::Forms::RadioButton^  ContrastWideRad;
	private: System::Windows::Forms::RadioButton^  ContrastNarrowRad;
	private: System::Windows::Forms::TextBox^  MinContrastCountTxt;
	private: System::Windows::Forms::TextBox^  MaxContrastStdTxt;
	private: System::Windows::Forms::TextBox^  MaxContrastCountTxt;
	private: System::Windows::Forms::VScrollBar^  MaxContrastSlider;
	private: System::Windows::Forms::VScrollBar^  MinContrastSlider;
	private: System::Windows::Forms::TextBox^  MinContrastStdTxt;
	private: System::Windows::Forms::Label^  MaxContrastStatic;
	private: System::Windows::Forms::Label^  MinContrastStatic;
	private: System::Windows::Forms::CheckBox^  BlinkChck;
	private: System::Windows::Forms::GroupBox^  BatchViewPanel;
public: System::Windows::Forms::VScrollBar^  SubImageSlideY;
private:
public: System::Windows::Forms::HScrollBar^  SubImageSlideX;


	private: System::Windows::Forms::PictureBox^  SubImageWindow;
	private: System::Windows::Forms::ToolStrip^  ToolBar;
	private: System::Windows::Forms::ToolStripButton^  TBLoad;
	private: System::Windows::Forms::ToolStripButton^  TBAdd;
	private: System::Windows::Forms::ToolStripButton^  TBReload;
	private: System::Windows::Forms::ToolStripButton^  TBFind;
	private: System::Windows::Forms::ToolStripButton^  TBViewFound;
	private: System::Windows::Forms::ToolStripButton^  TBSave;
	private: System::Windows::Forms::ToolStripButton^  TBSaveBatch;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripButton^  TBQuit;
	private: System::Windows::Forms::ProgressBar^  ProgressBar;
	private: System::Windows::Forms::CheckBox^  BatchStdvChck;
	private: System::Windows::Forms::CheckBox^  BatchMedianChck;
	private: System::Windows::Forms::CheckBox^  BatchMeanChck;
	private: System::Windows::Forms::CheckBox^  BatchCorrectionChck;

private: 


private: System::Windows::Forms::TabControl^  MainTab;
public: 

public: 
private: 








	private: System::Windows::Forms::TabPage^  ProcessingTab;
	private: System::Windows::Forms::GroupBox^  ImageCorrxnPnl;
	private: System::Windows::Forms::CheckBox^  SubBiasChck;

	private: System::Windows::Forms::CheckBox^  DivFlatChck;
	private: System::Windows::Forms::TabPage^  BatchTab;
	private: System::Windows::Forms::Label^  XYImageValueTxt;
	private: System::Windows::Forms::Label^  YPositionTxt;
	private: System::Windows::Forms::Label^  XPositionTxt;
	private: System::Windows::Forms::ImageList^  ToolBarImageList;

private: 

	private: System::Windows::Forms::SaveFileDialog^  SaveFileDlg;
public: System::Windows::Forms::PictureBox^  ImageWindow;
private: 

private: System::Windows::Forms::TabPage^  UVITTab;
private: System::Windows::Forms::Button^  UVOpenRawBtn;



private: System::Windows::Forms::GroupBox^  UVBatchViewPanel;

private: System::Windows::Forms::CheckBox^  UVMovieBtn;

private: System::Windows::Forms::Label^  UVViewSelectionStatic;



private: System::Windows::Forms::Button^  UVViewNextBtn;
private: System::Windows::Forms::Button^  UVViewLastBtn;

private: System::Windows::Forms::NumericUpDown^  UVBlinkTimeUpD;
private: System::Windows::Forms::Timer^  UVMovieTimer;
private: System::Windows::Forms::FolderBrowserDialog^  UVOpenDirDlg;
private: System::Windows::Forms::OpenFileDialog^  UVOpenRawDlg;

private: System::Windows::Forms::NumericUpDown^  BlinkTime;
private: System::Windows::Forms::GroupBox^  CentroidingPanel;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::NumericUpDown^  UVPrecisionUpD;
private: System::Windows::Forms::CheckedListBox^  UVAlgorithmListBox;


private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::CheckBox^  UVSubRangeChck;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::NumericUpDown^  UVPixelMaxThresh;

private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::NumericUpDown^  UVPixelMinThresh;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::NumericUpDown^  UVShapeMaxThresh;

private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::NumericUpDown^  UVShapeMinThresh;

private: System::Windows::Forms::Button^  UVCentroidBtn;


private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::ComboBox^  UVSaveCentroidDrop;
private: System::Windows::Forms::SaveFileDialog^  UVSaveCentroidDlg;
private: System::Windows::Forms::Button^  UVTransferImagesBtn;
private: System::Windows::Forms::Button^  UVOpenDirBtn;

private: System::Windows::Forms::NumericUpDown^  UVBackGroundUpD;
private: System::Windows::Forms::NotifyIcon^  CCDLABTaskBarIcon;
private: System::Windows::Forms::ContextMenuStrip^  TaskBarCntxt;

private: System::Windows::Forms::ToolStripMenuItem^  TCQuit;
private: System::Windows::Forms::Timer^  TBDestructTimer;
private: System::Windows::Forms::Button^  UVOpenCentroidBtn;
private: System::Windows::Forms::OpenFileDialog^  UVOpenUCFDlg;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::RadioButton^  UVDarkImageRad;

private: System::Windows::Forms::RadioButton^  UVDarkScalarRad;
private: System::Windows::Forms::Label^  UVDarkImageTxt;
private: System::Windows::Forms::ComboBox^  ColourMapDrop;
private: System::ComponentModel::BackgroundWorker^  ImageOpsWrkr;


private: System::ComponentModel::BackgroundWorker^  UVCentroidWrkr;


private: System::Windows::Forms::CheckBox^  AddImageChck;

private: System::Windows::Forms::CheckBox^  BatchSumChck;

private: System::Windows::Forms::ComboBox^  ScalarOpStyleDrop;
private: System::Windows::Forms::TextBox^  ScalarOpValTxt;
private: System::Windows::Forms::Button^  ScalarOpBtn;
private: System::Windows::Forms::Button^  BatchOpenListBtn;

private: System::Windows::Forms::Button^  BatchMakeListBtn;
private: System::Windows::Forms::Label^  BatchListNameTxt;
private: System::Windows::Forms::Button^  BatchComputeBtn;
private: System::Windows::Forms::CheckBox^  BatchSubImageChck;




private: System::Windows::Forms::Label^  YEndLabel;


private: System::Windows::Forms::Label^  YStartLabel;

private: System::Windows::Forms::Label^  XEndLabel;

private: System::Windows::Forms::Label^  XStartLabel;

private: System::Windows::Forms::CheckBox^  UVActiveBGChck;
private: System::Windows::Forms::CheckBox^  UVImageOnlyChck;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::NumericUpDown^  UVCornerThreshUpD;
private: System::Windows::Forms::Label^  ImageSumTxt;
private: System::Windows::Forms::Label^  ImageSumStatic;


private: System::Windows::Forms::Label^  SubImageSumTxt;
private: System::Windows::Forms::Label^  SubImageSumStatic;


private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::NumericUpDown^  UVBGOffset;


private: System::Windows::Forms::ContextMenuStrip^  SubImageCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  SubImageSurfCntxt;








private: System::ComponentModel::BackgroundWorker^  SurfWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  OptsMenu;

private: System::Windows::Forms::ToolStripMenuItem^  fileSavingPrecisionToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  OptFileSavePrecDbl;
private: System::Windows::Forms::ToolStripMenuItem^  OptFileSavePrecInt32;
private: System::ComponentModel::BackgroundWorker^  FormLoadBGW;
private: System::Windows::Forms::CheckBox^  UVOpenSubDirChck;
private: System::Windows::Forms::ContextMenuStrip^  UVAlgorithmCntxt;

private: System::Windows::Forms::ToolStripMenuItem^  UVPixelHist;

private: System::Windows::Forms::ToolStripMenuItem^  UVXDecHist;
private: System::Windows::Forms::ToolStripMenuItem^  UVYDecHist;
private: System::Windows::Forms::ToolStripMenuItem^  UVShapeHist;
private: System::Windows::Forms::ToolStripMenuItem^  UVFCMinHist;
private: System::Windows::Forms::ToolStripMenuItem^  UVFCMaxMinHist;

private: System::ComponentModel::BackgroundWorker^  UVHistWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtAnalysis;




private: System::Windows::Forms::ToolStripMenuItem^  ImageViewHistogram;
private: System::ComponentModel::BackgroundWorker^  ImageCntxtViewWrkr;













private: System::Windows::Forms::TabPage^  PSETab;
private: System::Windows::Forms::GroupBox^  FindSourcesPnl;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::NumericUpDown^  PSEPixelMaxUpD;

private: System::Windows::Forms::NumericUpDown^  PSEPixelMinUpD;
private: System::Windows::Forms::NumericUpDown^  PSEKernelRadUpD;

private: System::Windows::Forms::Label^  label23;









private: System::Windows::Forms::ToolStripMenuItem^  SubImageEditCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  EditValueCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtEdit;



private: System::Windows::Forms::ToolStripMenuItem^  ImageEditValueCntxt;
private: System::Windows::Forms::CheckBox^  PSEFitChck;
private: System::Windows::Forms::Button^  PSEFindSrcBtn;

private: System::Windows::Forms::ListBox^  PSEFitResultListBox;
private: System::Windows::Forms::CheckBox^  PSEViewFitChck;
private: System::ComponentModel::BackgroundWorker^  PSEFitWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  OptFileSavePrecUInt16;
private: System::Windows::Forms::ToolStripMenuItem^  UVITMenu;
private: System::Windows::Forms::ToolStripMenuItem^  UVIT_EMGSEMenu;
private: System::Windows::Forms::ToolStripMenuItem^  EMGSE_UnpackImg;

private: System::Windows::Forms::ContextMenuStrip^  InfoCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  centerToolStripMenuItem;
private: System::Windows::Forms::ComboBox^  MathOpDrop;

private: System::Windows::Forms::Button^  MathOpBtn;
private: System::Windows::Forms::Button^  UVGoToBtn;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtView;




private: System::Windows::Forms::ToolStripMenuItem^  ShowCursorBox;
private: System::Windows::Forms::ToolStripMenuItem^  ShowFoundCoordsChck;
private: System::Windows::Forms::ToolStripMenuItem^  ShowPSEChck;

private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::NumericUpDown^ PSEKernelMinUpD;
private: System::Windows::Forms::NumericUpDown^ PSEKernelMaxUpD;






private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::Label^  PSEPixelCntLbl;

private: System::Windows::Forms::Label^  PSEPixelValLbl;

private: System::Windows::Forms::CheckBox^  PSEAutoBackgroundChck;




private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::NumericUpDown^  YBinUpD;
private: System::Windows::Forms::NumericUpDown^  XBinUpD;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Panel^  panel1;















private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::Panel^  panel4;



private: System::Windows::Forms::Label^  ImageOpFilterLabel;
private: System::Windows::Forms::NumericUpDown^  ImageOpFilterWidthUpD;


private: System::Windows::Forms::Button^  ImageOpFilterBtn;
private: System::Windows::Forms::ComboBox^  ImageOpFilterTypeDrop;
private: System::Windows::Forms::Panel^  panel2;

private: System::Windows::Forms::Label^  FileDirectoryTxt;
private: System::Windows::Forms::NumericUpDown^  UVGoToUpD;
private: System::Windows::Forms::ComboBox^  FileListDrop;
private: System::Windows::Forms::ToolStripMenuItem^  ImageEditBoxCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  EditBoxCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  FMLoadSubFrame;
private: System::Windows::Forms::ToolStripMenuItem^  ImageEditBoxSetSubRangeCntxt;


private: System::Windows::Forms::Panel^  BatchSubImagePanel;
private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::CheckBox^  BatchAddImageChck;
private: System::Windows::Forms::CheckBox^  BatchSubtractImageChck;
private: System::Windows::Forms::CheckBox^  BatchMultiplyImageChck;



private: System::Windows::Forms::CheckBox^  BatchDivideImageChck;

private: System::ComponentModel::BackgroundWorker^  BatchBGWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtCut;
private: System::Windows::Forms::NumericUpDown^  HalfWidthYUpD;


private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::CheckBox^  EqualHWChck;
private: System::Windows::Forms::ToolStripMenuItem^  veiwToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  OptViewImage;
private: System::Windows::Forms::ToolStripMenuItem^  OptViewSpectrum;
private: System::Windows::Forms::CheckBox^  ViewImageTog;
private: System::Windows::Forms::CheckBox^  ViewSpectrumTog;
public: System::Windows::Forms::ToolStripMenuItem^  ShowCrosshair;
private:




private: System::Windows::Forms::NumericUpDown^  UVMovieSkipUpD;


private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::GroupBox^  UVAnalysisPanel;
private: System::Windows::Forms::Button^  UVStatsAnalysisBtn;



private: System::Windows::Forms::Button^  UVHVUTelemBtn;
private: System::Windows::Forms::ComboBox^  UVPlotXAxisDrop;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::TabControl^  BatchOperationTab;


private: System::Windows::Forms::TabPage^  BatchIndividualTab;


private: System::Windows::Forms::TabPage^  BatchSetTab;



private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::RadioButton^  BatchMeanRad;
private: System::Windows::Forms::RadioButton^  BatchSumRad;

private: System::Windows::Forms::RadioButton^  BatchFileAppRad;
private: System::Windows::Forms::RadioButton^  BatchFileOvrWrtRad;
private: System::Windows::Forms::Label^  BatchOutLabel;

private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::GroupBox^  ROIOnlyPnl;
private: System::Windows::Forms::CheckBox^  ROIViewFitChck;
private: System::Windows::Forms::ComboBox^  ROIFitFcnDrop;

private: System::Windows::Forms::Button^  ROIFitBtn;
private: System::Windows::Forms::Label^  ROIFitFcnLabel;
private: System::Windows::Forms::CheckBox^  SetParametersChck;
private: System::Windows::Forms::ToolStripMenuItem^  ApplyUVFPNMenu;


private: System::Windows::Forms::ToolStripMenuItem^  ConvertFromTextMenu;
private: System::Windows::Forms::ToolStripMenuItem^  ConvertListToImgMenu;

private: System::Windows::Forms::ContextMenuStrip^  StatsContxt;
private: System::Windows::Forms::ToolStripMenuItem^  StatsCopyClipBrdCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  StatsWriteFITSCntxt;
private: System::Windows::Forms::ComboBox^  PSEFitTypeChck;
private: System::Windows::Forms::CheckBox^  SavePSChck;
private: System::Windows::Forms::Button^  FlipHorzBtn;
private: System::Windows::Forms::Button^  FlipVertBtn;

private: System::Windows::Forms::Button^  RotCCWBtn;
private: System::Windows::Forms::Button^  RotCWBtn;

private: System::Windows::Forms::ToolStripMenuItem^  HCExtractListValues;
private: System::Windows::Forms::ToolStripMenuItem^  HCPlot;
private: System::Windows::Forms::ToolStripMenuItem^  HCPlotKeyValues;
private: System::Windows::Forms::ToolStripMenuItem^  HCPlotListValues;
private: System::Windows::Forms::TabPage^  BatchStackingTab;
private: System::Windows::Forms::Label^  label18;




public: System::Windows::Forms::RichTextBox^  StackingDirectoryTxt;
private: System::Windows::Forms::NumericUpDown^  StackUpD;
private: System::Windows::Forms::CheckBox^  TabBatchElementalFindPointsChck;
private: System::Windows::Forms::ComboBox^  TabBatchElementalFindStyleDD;
private: System::Windows::Forms::TextBox^  TabBatchElementalFindValTxt;
private: System::Windows::Forms::TextBox^  TabBatchElementalReplaceValTxt;

private: System::Windows::Forms::ComboBox^  TabBatchElementalReplaceStyleDD;

private: System::Windows::Forms::Label^  label31;

private: System::Windows::Forms::ToolStripMenuItem^  OptFileSavePrecInt16;
private: System::Windows::Forms::TabControl^  SubImgROITab;

private: System::Windows::Forms::TabPage^  ROIFitTab;
private: System::Windows::Forms::TabPage^  ROICOGTab;



private: System::Windows::Forms::NumericUpDown^  COGIgnoreNPtsUpD;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Button^  COGBtn;

private: System::Windows::Forms::CheckBox^  COGViewChck;
private: System::Windows::Forms::CheckBox^  COGBatchChck;

private: System::Windows::Forms::Panel^  panel5;
private: System::Windows::Forms::ToolStripButton^  TBLoadSubFrame;
private: System::Windows::Forms::ToolStripDropDownButton^  TBFileSavePrecOpts;

private: System::Windows::Forms::ToolStripMenuItem^  TBOptFileSavePrecDbl;
private: System::Windows::Forms::ToolStripMenuItem^  TBOptFileSavePrecInt32;
private: System::Windows::Forms::ToolStripMenuItem^  TBOptFileSavePrecInt16;
private: System::Windows::Forms::ToolStripMenuItem^  TBOptFileSavePrecUInt16;
private: System::Windows::Forms::Button^  ClipToContrastBtn;
private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
private: System::Windows::Forms::Button^  InvQuitBtn;

private: System::Windows::Forms::ContextMenuStrip^  ImageWindowCntxt;
private: System::Windows::Forms::Button^  UVAutoThreshChck;
private: System::Windows::Forms::ToolStripMenuItem^  UVFrameHist;
private: System::Windows::Forms::ToolStripMenuItem^  UVIT_ApplyCPUCorrectionMenu;

private: System::Windows::Forms::CheckBox^  MultImgChck;
private: System::ComponentModel::BackgroundWorker^  WriteImageSetBGWrkr;
private: System::Windows::Forms::ToolStripButton^  TBSaveOver;
private: System::Windows::Forms::ToolStripButton^  TBSaveBatchOver;

private: System::Windows::Forms::Button^  CutSubImBtn2;
private: System::Windows::Forms::TabPage^  BatchRunningTab;

private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::ComboBox^  BatchRunningOpDrop;

private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::NumericUpDown^  BatchRunningNumUpD;

public: System::Windows::Forms::RichTextBox^  RunningDirectoryTxt;
private: 

private: 

private: System::Windows::Forms::CheckBox^  BatchMaximumChck;
private: System::Windows::Forms::CheckBox^  BatchMinimumChck;
private: System::Windows::Forms::Button^  RotateBtn;
private: System::Windows::Forms::NumericUpDown^  RotateAngleUpD;
private: System::Windows::Forms::Button^  ShiftVertBtn;
private: System::Windows::Forms::Button^  ShiftHorzBtn;


private: System::Windows::Forms::NumericUpDown^  NShiftHorzUpD;
private: System::Windows::Forms::NumericUpDown^  NShiftVertUpD;
private: System::Windows::Forms::TextBox^  BatchIndividualAppendageTxt;

public: System::Windows::Forms::RichTextBox^  IndividualDirectoryTxt;
private: 

private: 

private: System::Windows::Forms::GroupBox^  BatchListViewPanel;
private: System::Windows::Forms::NumericUpDown^  BatchMovieSkipUpD;


private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Button^  BatchGoToBtn;

private: System::Windows::Forms::NumericUpDown^  BatchBlinkTime;

private: System::Windows::Forms::CheckBox^  BatchBlinkChck;

private: System::Windows::Forms::Button^  BatchViewNextBtn;
private: System::Windows::Forms::NumericUpDown^  BatchGoToUpD;


private: System::Windows::Forms::Button^  BatchViewLastBtn;
private: System::Windows::Forms::Timer^  BatchMovieTimer;

private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::ToolStripMenuItem^  CreateFlatFieldListMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  CreateDriftListMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ApplyDriftListMentuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ListToImage1PixMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  ListToImage2PixMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  ListToImage4PixMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  ListToImage8PixMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ParcelListAsFramesMenuItem;

private: System::Windows::Forms::ToolStripComboBox^  ParcelStackTimeDrop;
private: System::ComponentModel::BackgroundWorker^  ParcelUVCentroidWrkr;

private: System::Windows::Forms::ToolStripMenuItem^  CreateDriftFromPCMenuItem;

private: System::Windows::Forms::ToolStripTextBox^  DriftFromListTimeTxt;
private: System::Windows::Forms::ToolStripMenuItem^  CreateDriftFromINTMenuItem;
private: System::Windows::Forms::ToolStripComboBox^  DriftStackTimeDrop;
private: System::Windows::Forms::ToolStripMenuItem^  PlotDriftListMenuItem;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;
private: System::ComponentModel::BackgroundWorker^  DriftFromPCListWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  FilterCosmicRaysChckMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ApplyFlatListToImageChck;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;
private: System::Windows::Forms::ToolStripTextBox^  DriftFromListEndTimeTxt;
private: System::Windows::Forms::ToolStripMenuItem^  PlotCountsPerFrameMenuItem;
private: System::Windows::Forms::ToolStripTextBox^  CosmicRayFilterMenuTxt;
private: System::ComponentModel::BackgroundWorker^  DriftFromINTWrkr;
private: System::Windows::Forms::Button^  BatchScanDirectoryBtn;
private: System::Windows::Forms::ComboBox^  BatchScanDirectoryFileTypeDrop;
private: System::Windows::Forms::ToolStripMenuItem^  TryAutoDeBiasINTDrift;
private: System::Windows::Forms::ToolStripMenuItem^  DriftFromPCInterpolateChck;
private: System::Windows::Forms::ToolStripMenuItem^  SmoothINTDriftChck;
private: System::Windows::Forms::ToolStripMenuItem^  PCModeDriftSelfCorrectionMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  ShiftAndRotateMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  UserDefinedShiftRotateMenuItem;

private: System::Windows::Forms::ToolStripTextBox^  UserXShiftTxt;
private: System::Windows::Forms::ToolStripTextBox^  UserYShiftTxt;
private: System::Windows::Forms::ToolStripTextBox^  UserRotationTxt;
private: System::Windows::Forms::ToolStripMenuItem^  FlipHorizontalMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  FlipVerticalMenuItem;






private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtPlot;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtPlotRow;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtPlotCol;


private: System::Windows::Forms::ToolStripMenuItem^  EMFile;
private: System::Windows::Forms::ToolStripMenuItem^  EMFileBias;
private: System::Windows::Forms::ToolStripMenuItem^  EMFileDark;
private: System::Windows::Forms::ToolStripMenuItem^  EMFileFlat;
private: System::Windows::Forms::ToolStripMenuItem^  EMCopyHeader;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  Chart1;
private: System::ComponentModel::BackgroundWorker^  ManRegWrkr;
private: System::Windows::Forms::NumericUpDown^  ManRegSrcHWUpD;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::NumericUpDown^  ManRegTrkHWUpD;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator10;
private: System::Windows::Forms::ToolStripMenuItem^  CrossCorrINTDriftChck;
private: System::Windows::Forms::ToolStripMenuItem^  PointSrcINTDriftChck;
private: System::Windows::Forms::ToolStripMenuItem^  DigestL1FITSImageMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  INTAtoINTADriftCorrectionMenuItem;
private: System::ComponentModel::BackgroundWorker^  INTAtoINTAapplyDriftWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  CosmicRayFilterCountMenuChck;


private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator11;
private: System::Windows::Forms::ToolStripMenuItem^  CosmicRayFilterSigmaMenuChck;
private: System::Windows::Forms::ToolStripTextBox^  CosmicRayFilterSigmaMenuTxt;
private: System::Windows::Forms::ToolStripMenuItem^  MaxMinThreshChck;
private: System::Windows::Forms::ToolStripTextBox^  MaxMinThreshTxt;
private: System::Windows::Forms::ToolStripMenuItem^  MaxMinCountTwiceChck;
private: System::Windows::Forms::ToolStripMenuItem^  SubImgRadialPlotMenuBtn;


private: System::Windows::Forms::ToolStripComboBox^  DriftSmoothNDrop;
private: System::ComponentModel::BackgroundWorker^  DigestL1Wrkr;

private: System::Windows::Forms::ToolStripMenuItem^  L1DigestApplyFPNChck;
private: System::Windows::Forms::ToolStripMenuItem^  L1DigestApplyDISTChck;
private: System::Windows::Forms::Button^  KeyValNormBtn;
private: System::Windows::Forms::ToolStripMenuItem^  L1DiscardDataTimeChck;
private: System::Windows::Forms::ToolStripComboBox^  L1DiscardDataTimeDrop;
private: System::Windows::Forms::ToolStripMenuItem^  L1DiscardDuplicateChck;
private: System::Windows::Forms::ToolStripTextBox^  UserRotationXCenterTxt;
private: System::Windows::Forms::ToolStripTextBox^  UserRotationYCenterTxt;


private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator8;
private: System::Windows::Forms::ToolStripMenuItem^  LinearRotationChck;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator9;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator13;
private: System::Windows::Forms::ToolStripMenuItem^  GeneralTransformChck;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator14;
private: System::Windows::Forms::ToolStripTextBox^  TransformCoefATxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformCoefBTxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformCoefCTxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformCoefDTxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformCenterXTxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformCenterYTxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformShiftXTxt;
private: System::Windows::Forms::ToolStripTextBox^  TransformShiftYTxt;
private: System::Windows::Forms::ToolStripMenuItem^  UVAutoApplyDriftandImageChck;
private: System::Windows::Forms::ToolStripMenuItem^  GeneralUVRegistrationMenuItem;


private: System::ComponentModel::BackgroundWorker^  DiscardL1DuplicateWrkr;
private: System::ComponentModel::BackgroundWorker^  ConvertUVCentroidListToImgWrkr;


private: System::Windows::Forms::ToolStripMenuItem^  RadialPlotMedianBackgroundChck;
private: System::ComponentModel::BackgroundWorker^  RegistrationUVCentroidWrkr;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator15;
private: System::Windows::Forms::ToolStripMenuItem^  UVCombineCentroidListsMenuItem;
private: System::ComponentModel::BackgroundWorker^  MergeCentroidListsWrkr;




private: System::Windows::Forms::ToolStripMenuItem^  UVAutoDriftImageViewChck;
private: System::Windows::Forms::ToolStripMenuItem^  UVNUVToFUVFrameMenuItem;
private: System::ComponentModel::BackgroundWorker^  RotationUVCentroidWrkr;

private: System::Windows::Forms::Button^  CombineRGBBtn;
private: System::Windows::Forms::Button^  RGBSaveBtn;
private: System::Windows::Forms::Label^  DirectoryLabel;
private: System::Windows::Forms::ToolStripMenuItem^  DeSaturateROICountsMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  CorrectBackgroundCountsChck;
private: System::Windows::Forms::ToolStripTextBox^  BackgroundCountsPixelFrameTxt;
private: System::Windows::Forms::Label^  SubImageSizeTxt;
private: System::Windows::Forms::ToolStripMenuItem^  ExtractROICentroidListMenuItem;



private: System::Windows::Forms::ToolStripMenuItem^  HCCopy;
private: System::Windows::Forms::ToolStripMenuItem^  HCCopyKeyValue;
private: System::Windows::Forms::ToolStripMenuItem^  HCCopyListValue;
private: System::Windows::Forms::ToolStripMenuItem^  OptInvertImageView;
private: System::Windows::Forms::ToolStripMenuItem^  HCInsertSelectedToOthers;
private: System::Windows::Forms::ToolStripMenuItem^  perFrameMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator17;
private: System::Windows::Forms::ToolStripMenuItem^  perTimeBinMenuItem;
private: System::Windows::Forms::ToolStripComboBox^  plotPerTimeBinComboBox;
private: System::Windows::Forms::ContextMenuStrip^  ImageFingerPointContext;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerRmvToHere;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerRmvFromHere;
private: System::Windows::Forms::ContextMenuStrip^  ScanBtnContext;
private: System::Windows::Forms::ToolStripMenuItem^  ScanContextGoToBtn;
private: System::Windows::Forms::ToolStripTextBox^  ScanContextGoToTxt;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator19;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator18;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtCopyPixPoord;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtMarkCoord;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtMarkCoord;
private: System::Windows::Forms::ToolStripMenuItem^  MarkCoordClear;
private: System::Windows::Forms::ToolStripMenuItem^  SubImMarkCoordClear;
private: System::Windows::Forms::ToolStripMenuItem^  ConsolidateNUVApplyToFUV;

private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
private: System::Windows::Forms::ToolStripComboBox^  UVGeneralRegistrationResolutionDrop;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator21;
private: System::ComponentModel::BackgroundWorker^  DriftNUVtoFUVBGWrkr;

private: System::Windows::Forms::ContextMenuStrip^  SIZECntxtMenu;
private: System::Windows::Forms::ToolStripMenuItem^  SIZECntxtEditImgDim;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
private: System::Windows::Forms::ToolStripTextBox^  SIZECntxtEditTxtX;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator22;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem7;
private: System::Windows::Forms::ToolStripTextBox^  SIZECntxtEditTxtY;

private: System::Windows::Forms::ToolStripSeparator^  Sep;
private: System::Windows::Forms::ToolStripMenuItem^  SIZECntxtBatchChck;
private: System::ComponentModel::BackgroundWorker^  SIZECntxtBGWrkr;

private: System::Windows::Forms::ToolStripMenuItem^  ExtractL1gzsMenuItem;
private: System::ComponentModel::BackgroundWorker^  ExtractL1ArchiveBGWrkr;

private: System::Windows::Forms::ToolStripMenuItem^  L1CentroidPaddingChck;
private: System::Windows::Forms::ToolStripComboBox^  PCCentroidPaddingDrop;
private: System::Windows::Forms::ToolStripMenuItem^  ApplyDriftCreateExpArrayChc;
private: System::ComponentModel::BackgroundWorker^  ApplyDriftListWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  ApplyExpArrayToImageChck;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtCopyImage;
private: System::Windows::Forms::Button^  PadImageBtn;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerRecToHere;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerRecFromHere;
private: System::Windows::Forms::ToolStripMenuItem^  ExposureArrayResMenuText;

private: System::Windows::Forms::ToolStripComboBox^  ExposureArrayResolutionDrop;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerSortBy;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerSortFileName;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator23;
private: System::Windows::Forms::ToolStripMenuItem^  ImageFingerSortKeyValue;
private: System::Windows::Forms::ToolStripTextBox^  ImageFingerSortKeyValueTxt;
private: System::Windows::Forms::CheckBox^  SubImTrackPSChck;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwPlotRadialVector;


private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator24;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWindowSaveRadialVector;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWindowRadialSetAngle;
private: System::Windows::Forms::ToolStripTextBox^  ImageWindowRadialAngleTxt;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtGoToPixel;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem8;
private: System::Windows::Forms::ToolStripTextBox^  SubImCntxtGoToPixXTxt;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem9;
private: System::Windows::Forms::ToolStripTextBox^  SubImCntxtGoToPixYTxt;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtPlotRowSubOnly;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWndwCntxtPlotColSubOnly;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator25;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWindowRadialLockSources;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtSaveRadialProfileMenuBtn;


private: System::Windows::Forms::ToolStripMenuItem^  CleanVISImagesMenuItem;
private: System::ComponentModel::BackgroundWorker^  CleanVISBGWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  L1DegradientINTMode;
private: System::Windows::Forms::ToolStripMenuItem^  L1SkipINTMode;
private: System::Windows::Forms::ToolStripMenuItem^  L1FilterCorrectionChck;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtCopyCentroidCoord;

private: System::Windows::Forms::ContextMenuStrip^  FileDirectoryTxtContextMenu;
private: System::Windows::Forms::ToolStripMenuItem^  FileDirectoryTxtContextMenuDelDirRmImg;
private: System::Windows::Forms::ToolStripMenuItem^  HCEditCurrent;
private: System::Windows::Forms::ToolStripMenuItem^  HCEditAll;
private: System::Windows::Forms::ToolStripMenuItem^  ListToImage16PixMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  SubImCntxtGoToRADec;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem10;
private: System::Windows::Forms::ToolStripTextBox^  SubImCntxtGoToRATxt;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem11;
private: System::Windows::Forms::ToolStripTextBox^  SubImCntxtGoToDecTxt;
private: System::Windows::Forms::ToolStripMenuItem^  FMViewExtensionTable;

private: System::Windows::Forms::ToolStripMenuItem^  ParcelStackmdMmChck;
private: System::Windows::Forms::ToolStripMenuItem^  L1TBCChck;
private: System::Windows::Forms::ToolStripMenuItem^  DriftPCROIOnly;
private: System::Windows::Forms::ToolStripMenuItem^  ResetPlotPositions;
private: System::Windows::Forms::ToolStripMenuItem^  ImageWindowCntxtSquare;
private: System::Windows::Forms::ToolStripMenuItem^ DeRotateViaWCSBtn;








private: System::Windows::Forms::ToolStripMenuItem^  FMRecentFiles;
private: System::Windows::Forms::ToolStripDropDownButton^  TBRecentFiles;
private: System::Windows::Forms::Button^  PSESigmaCountBtn;
public: System::Windows::Forms::CheckBox^  PSESeachROIOnlyChck;
private:

private: System::Windows::Forms::Button^  PSETableViewBtn;
private: System::Windows::Forms::ContextMenuStrip^  PSEFitResultsCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  PSEFitResultCntxtCopySelected;
private: System::Windows::Forms::ToolStripMenuItem^  PSEFitResultCntxtCopyAll;
private: System::Windows::Forms::CheckBox^  BatchQuadratureChck;

public: System::Windows::Forms::Label^  SubImageDecTxt;
private:
public: System::Windows::Forms::Label^  SubImageRATxt;
private: System::Windows::Forms::ToolStripMenuItem^  SubImMarkCoordAsCentroidChck;
public: System::Windows::Forms::CheckBox^  PSEEllipticalROI;
private: System::Windows::Forms::ToolStripMenuItem^  SubImMarkCoordContainedPSE;
public:
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator28;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator27;
private: System::Windows::Forms::Button^  PSEClearBtn;
private: System::Windows::Forms::ComboBox^  PSELoadSrcDrop;
private: System::Windows::Forms::Label^  label3;






private: System::Windows::Forms::ToolStripMenuItem^  SubImMarkCoordClearContained;

private: System::Windows::Forms::NumericUpDown^  PSESeparationUpD;

private: System::Windows::Forms::Label^  label20;





















private: System::ComponentModel::BackgroundWorker^  WCSAutoBGWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  WCSMenu;

private: System::Windows::Forms::ToolStripMenuItem^  WCSRADecShowChck;
private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  WCSCopyToLoadedImgs;
private: System::Windows::Forms::ToolStripMenuItem^  WCSCopyToDiskFiles;
private: System::Windows::Forms::ToolStripMenuItem^  WCSPlotSolutionPtsBtn;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator30;
private: System::Windows::Forms::ToolStripMenuItem^  WCSRADecManual;





private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator31;
private: System::Windows::Forms::ToolStripMenuItem^  AutoWCSMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoSolveBtn;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator38;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoCatalogueMenuBtn;

private: System::Windows::Forms::ToolStripTextBox^  WCSAutoCatalogueTxt;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoNCatPtsLabel;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator33;
private: System::Windows::Forms::ToolStripMenuItem^  AutoWCSScaleMenuBtn;

private: System::Windows::Forms::ToolStripTextBox^  WCSScaleInit;
private: System::Windows::Forms::ToolStripTextBox^  WCSScaleInitLB;
private: System::Windows::Forms::ToolStripTextBox^  WCSScaleInitUB;

private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem14;
private: System::Windows::Forms::ToolStripTextBox^  WCSRotationInit;
private: System::Windows::Forms::ToolStripTextBox^  WCSRotationInitLB;
private: System::Windows::Forms::ToolStripTextBox^  WCSRotationInitUB;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator34;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem15;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoVertexToleranceTxt;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator37;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoDisplayChck;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator35;






private: System::Windows::Forms::ToolStripMenuItem^  cVAL1RAToolStripMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  cVAL2DecToolStripMenuItem;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoCatalogueCVAL1;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoCatalogueCVAL2;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem17;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoCatalogueExtensionTxt;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem16;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoCatalogueMag;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoNCatPtsTxt;


private: System::Windows::Forms::TextBox^  TEST_TEXT_BOX;
private: System::Windows::Forms::ToolStripMenuItem^  WCSRefineSolutionBtn;
private: System::Windows::Forms::ToolStripMenuItem^  WCSLoadSimbadList;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem18;
private: System::Windows::Forms::ToolStripTextBox^  WCSLoadListNPtsTxt;
private: System::Windows::Forms::ToolStripMenuItem^  WCSListExciseToROI;
private: System::Windows::Forms::ToolStripMenuItem^  WCSClarifyListSources;
private: System::Windows::Forms::ToolStripMenuItem^  WCSSolveList;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator29;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoRefineChck;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem19;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoRefineNPtsTxt;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoStopCriteriaMenu;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoStopNMatchesBtn;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoStopNMatchesText;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem20;
private: System::Windows::Forms::ToolStripTextBox^  WCSAutoStopPercMatchesText;
private: System::Windows::Forms::ToolStripMenuItem^  L1TransformNUVtoFUVChck;
private: System::Windows::Forms::NumericUpDown^  PSESaturationUpD;

private: System::Windows::Forms::Label^  label24;
public: System::Windows::Forms::CheckBox^  PSEDrawROI;
private: System::Windows::Forms::ContextMenuStrip^  DrawROIContextMenu;
public:
private: System::Windows::Forms::ToolStripMenuItem^  SaveROIContext;
private: System::Windows::Forms::ToolStripMenuItem^  LoadROIContext;
private: System::Windows::Forms::ToolStripMenuItem^  MarkCoordSave;
private: System::Windows::Forms::ToolStripMenuItem^  MarkCoordLoad;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator36;
private: System::Windows::Forms::ToolStripMenuItem^  L1CleanINTMode;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator39;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem13;
private: System::Windows::Forms::ToolStripTextBox^  L1CleanINTLineThreshold;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator40;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem21;
private: System::Windows::Forms::ToolStripTextBox^  L1CleanINTNPix;
private: System::Windows::Forms::ContextMenuStrip^  RotateBtnCntxt;
private: System::Windows::Forms::ToolStripMenuItem^  RotateBtnCntxtNearest;
private: System::Windows::Forms::ToolStripMenuItem^  RotateBtnCntxtBiLinear;
private: System::Windows::Forms::ToolStripMenuItem^  RotateBtnCntxtLanczos3;
private: System::Windows::Forms::ToolStripMenuItem^  RotateBtnCntxtLanczos4;
private: System::Windows::Forms::ToolStripMenuItem^  RotateBtnCntxtLanczos5;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem22;
private: System::Windows::Forms::ToolStripMenuItem^  L1DigestApplyDISTInterpNearChck;
private: System::Windows::Forms::ToolStripMenuItem^  L1DigestApplyDISTInterpBiLinChck;
private: System::Windows::Forms::ToolStripMenuItem^  WCSClearMenuBtn;
private: System::Windows::Forms::ToolStripMenuItem^  WCSClearAllChck;
private: System::Windows::Forms::ToolStripMenuItem^  AutoWCSScaleSaveBtn;
private: System::Windows::Forms::ToolStripTextBox^  WSCSaveScaleTxtBox;


private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator43;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator42;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator41;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoParityMenuBtn;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoXAxisParityChck;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator44;
private: System::Windows::Forms::ToolStripMenuItem^  WCSAutoYAxisParityChck;
private: System::Windows::Forms::ToolStripMenuItem^ WCSAutoExternalDLLChck;

private: System::Windows::Forms::ToolStripMenuItem^ PointSrcINTDriftDisplayChck;
private: System::Windows::Forms::ToolStripComboBox^ PointSrcINTDriftDisplayCadenceDrop;
private: System::Windows::Forms::CheckBox^ BatchFileParallelChck;
private: System::Windows::Forms::CheckBox^ BatchFileKeepDirectoriesChck;
private: System::Windows::Forms::ToolStripMenuItem^ L1AutoRunChck;
private: System::Windows::Forms::CheckBox^ BatchQuickScanSubDirsChck;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem23;
private: System::Windows::Forms::ToolStripMenuItem^ WCSAutoQueryBtn;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem24;
private: System::Windows::Forms::ToolStripTextBox^ WCSAutoQueryCVAL1;

private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem25;
private: System::Windows::Forms::ToolStripTextBox^ WCSAutoQueryCVAL2;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem26;
private: System::Windows::Forms::ToolStripTextBox^ WCSAutoResolveRadiusTxt;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator45;
private: System::Windows::Forms::ToolStripMenuItem^ WCSQuerySaveFileChck;
private: System::Windows::Forms::ToolStripMenuItem^ WCSAutoConditionArraysChck;
private: System::Windows::Forms::ToolStripMenuItem^ WCSQuerySquareRegionChck;
private: System::Windows::Forms::ToolStripMenuItem^ AstroQueryCatalogueNameMenu;

private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator46;
private: System::Windows::Forms::ToolStripComboBox^ AstroQueryCatalogueNameDrop;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator47;
private: System::Windows::Forms::ToolStripMenuItem^ WCSQuerySolveAfter;
private: System::Windows::Forms::ToolStripMenuItem^ SubImSurfColumnMenuBtn;
private: System::Windows::Forms::ToolStripMenuItem^ SubImageSurfMesh;
private: System::Windows::Forms::ToolStripMenuItem^ SubImageSurfSmooth;
private: System::Windows::Forms::ToolStripMenuItem^ SubImageSurfMetal;
private: System::Windows::Forms::ToolStripMenuItem^ SubImageSurfFacet;
private: System::Windows::Forms::ToolStripMenuItem^ masterizeSinglesToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ UVDeleteMergeDirsChck;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator48;
private: System::Windows::Forms::ToolStripMenuItem^ L1DigestDeleteFileChck;



private: System::Windows::Forms::ToolStripMenuItem^ ConsolidateDriftFolderChck;
private: System::Windows::Forms::ToolStripMenuItem^ ConsolidateTimeListFolderChck;
private: System::Windows::Forms::ToolStripSplitButton^ TBZipAllBtn;
private: System::Windows::Forms::ToolStripMenuItem^ TBZipMoveChck;
private: System::Windows::Forms::ToolStripMenuItem^ TBZipCopyChck;
private: System::Windows::Forms::ToolStripMenuItem^ RegistrationXYIntsListFolderScanChck;
private: System::Windows::Forms::ToolStripMenuItem^ MergeXYIntsListFolderScanChck;
private: System::Windows::Forms::ToolStripMenuItem^ UVLoadAllMerged;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator20;
private: System::Windows::Forms::ToolStripMenuItem^ PointSrcINTDriftNoPSEConfChck;
private: System::Windows::Forms::ToolStripMenuItem^ PointSrcINTDriftNoPlotConfChck;
private: System::Windows::Forms::ToolStripMenuItem^ AutoWCSXCorr;
private: System::Windows::Forms::ToolStripMenuItem^ WCSQuerySaveFileChooseDirBtn;
private: System::Windows::Forms::ToolStripMenuItem^ UVFinalizeScienceBtn;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator12;
private: System::Windows::Forms::ToolStripMenuItem^ DriftFromPCPSTrackBtn;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;
private: System::Windows::Forms::ToolStripComboBox^ PointSrcROIStackDriftDrop;
private: System::ComponentModel::BackgroundWorker^ DriftFromPCPSTrackBGWrkr;
private: System::Windows::Forms::ToolStripMenuItem^ PSTrackDisplayClearBtn;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator16;
private: System::Windows::Forms::ToolStripMenuItem^ L1AutoProceedVISBackGround;
private: System::Windows::Forms::ToolStripMenuItem^ L1AutoProceedVISTracking;
private: System::Windows::Forms::ToolStripMenuItem^ L1AutoApplyVISDrift;
private: System::Windows::Forms::ToolStripMenuItem^ WCSClearPlotSolutionPtsBtn;
private: System::Windows::Forms::ToolStripMenuItem^ invertWCSToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ L1DigestPCParityChck;
private: System::Windows::Forms::ToolStripMenuItem^  PointSrcROIFindSrcChck;
private: System::Windows::Forms::ToolStripComboBox^  PointSrcROIFindNSrcDrop;
private: System::Windows::Forms::ToolStripMenuItem^  PointSrcROIAutoRunChck;
private: System::Windows::Forms::ToolStripMenuItem^  UVFinalizeIncludeTablesChck;
private: System::ComponentModel::BackgroundWorker^  UVFinalizeBGWrkr;
private: System::Windows::Forms::ToolStripMenuItem^  UVFinalizeDeleteIntrmdtChck;
private: System::Windows::Forms::ToolStripMenuItem^  UVFinalizeMoveOrCopyZipChck;
private: System::Windows::Forms::ToolStripMenuItem^  UVAutoPSFPostMergeChck;
	private: System::Windows::Forms::ToolStripMenuItem^  UVFinalizeIncludeExpMapChck;
	private: System::Windows::Forms::ComboBox^  PSEDrop;
	private: System::Windows::Forms::ContextMenuStrip^  PSEDropContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  PSEDropContextAdd;
		private: System::Windows::Forms::ToolStripMenuItem^  PSEDropContextRemove;
		private: System::Windows::Forms::ToolStripMenuItem^  PSEDropContextClearAll;
	private: System::Windows::Forms::ToolStripMenuItem^  PSEDropContextPlotAll;






















private:























































private:

private:
public:































































































































public: 












public: 
public: 
private: 

private: 


private: System::ComponentModel::IContainer^  components;

#pragma endregion

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->ImageWindowCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ImageWndwCntxtView = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowCursorBox = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowCrosshair = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowFoundCoordsChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ShowPSEChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWindowCntxtSquare = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtAnalysis = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageViewHistogram = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtEdit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageEditValueCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageEditBoxCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageEditBoxSetSubRangeCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtPlot = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtPlotRow = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtPlotRowSubOnly = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator25 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ImageWndwCntxtPlotCol = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtPlotColSubOnly = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator24 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ImageWndwPlotRadialVector = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWindowRadialLockSources = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWindowRadialSetAngle = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWindowRadialAngleTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->ImageWindowSaveRadialVector = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWndwCntxtMarkCoord = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MarkCoordClear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MarkCoordSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MarkCoordLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ViewSelectionStatic = (gcnew System::Windows::Forms::Label());
			this->ViewNextBtn = (gcnew System::Windows::Forms::Button());
			this->ViewLastbtn = (gcnew System::Windows::Forms::Button());
			this->MoveUpBtn = (gcnew System::Windows::Forms::Button());
			this->MoveDownBtn = (gcnew System::Windows::Forms::Button());
			this->DeleteFileBtn = (gcnew System::Windows::Forms::Button());
			this->SingleOutBtn = (gcnew System::Windows::Forms::Button());
			this->ImageFingerPointContext = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ImageFingerRmvToHere = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageFingerRmvFromHere = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageFingerRecToHere = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageFingerRecFromHere = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageFingerSortBy = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageFingerSortFileName = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator23 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ImageFingerSortKeyValue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageFingerSortKeyValueTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->HalfWidthXUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->SubImageBtn = (gcnew System::Windows::Forms::RadioButton());
			this->SubImagePanel = (gcnew System::Windows::Forms::GroupBox());
			this->SubImageDecTxt = (gcnew System::Windows::Forms::Label());
			this->SubImTrackPSChck = (gcnew System::Windows::Forms::CheckBox());
			this->SubImageRATxt = (gcnew System::Windows::Forms::Label());
			this->SubImageYTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageXTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageSizeTxt = (gcnew System::Windows::Forms::Label());
			this->CutSubImBtn2 = (gcnew System::Windows::Forms::Button());
			this->EqualHWChck = (gcnew System::Windows::Forms::CheckBox());
			this->HalfWidthYUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->SubImageSumTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageSumStatic = (gcnew System::Windows::Forms::Label());
			this->StatsContxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->StatsCopyClipBrdCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->StatsWriteFITSCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageYStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageXStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMinTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageMaxTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageMeanTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageMedianTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageStdTxt = (gcnew System::Windows::Forms::Label());
			this->SubImageMedianStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMeanStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageStdvStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMinStatic = (gcnew System::Windows::Forms::Label());
			this->SubImageMaxStatic = (gcnew System::Windows::Forms::Label());
			this->ScaleContrastChck = (gcnew System::Windows::Forms::CheckBox());
			this->HalfWidthStatic = (gcnew System::Windows::Forms::Label());
			this->BlinkTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->FileInfoPanel = (gcnew System::Windows::Forms::GroupBox());
			this->ImageSumTxt = (gcnew System::Windows::Forms::Label());
			this->ImageSumStatic = (gcnew System::Windows::Forms::Label());
			this->ImageSizeTxt = (gcnew System::Windows::Forms::Label());
			this->SIZECntxtMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->SIZECntxtEditImgDim = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SIZECntxtEditTxtX = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator22 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SIZECntxtEditTxtY = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->Sep = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->SIZECntxtBatchChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageSizeStatic = (gcnew System::Windows::Forms::Label());
			this->InfoTxt4 = (gcnew System::Windows::Forms::Label());
			this->InfoStatic4 = (gcnew System::Windows::Forms::Label());
			this->InfoCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ImageMedianTxt = (gcnew System::Windows::Forms::Label());
			this->ImageMinStatic = (gcnew System::Windows::Forms::Label());
			this->InfoTxt5 = (gcnew System::Windows::Forms::Label());
			this->InfoStatic1 = (gcnew System::Windows::Forms::Label());
			this->InfoTxt1 = (gcnew System::Windows::Forms::Label());
			this->InfoStatic3 = (gcnew System::Windows::Forms::Label());
			this->InfoTxt2 = (gcnew System::Windows::Forms::Label());
			this->InfoTxt3 = (gcnew System::Windows::Forms::Label());
			this->InfoStatic2 = (gcnew System::Windows::Forms::Label());
			this->FileNameStatic = (gcnew System::Windows::Forms::Label());
			this->InfoStatic5 = (gcnew System::Windows::Forms::Label());
			this->ImageMaxStatic = (gcnew System::Windows::Forms::Label());
			this->ImageMedianStatic = (gcnew System::Windows::Forms::Label());
			this->ImageMeanStatic = (gcnew System::Windows::Forms::Label());
			this->ImageStdvStatic = (gcnew System::Windows::Forms::Label());
			this->ImageMinTxt = (gcnew System::Windows::Forms::Label());
			this->ImageMeanTxt = (gcnew System::Windows::Forms::Label());
			this->ImageStdTxt = (gcnew System::Windows::Forms::Label());
			this->ImageMaxTxt = (gcnew System::Windows::Forms::Label());
			this->FileNameTxt = (gcnew System::Windows::Forms::Label());
			this->FileDirectoryTxt = (gcnew System::Windows::Forms::Label());
			this->FileDirectoryTxtContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->FileDirectoryTxtContextMenuDelDirRmImg = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileDirectoryStatic = (gcnew System::Windows::Forms::Label());
			this->ContrastPanel = (gcnew System::Windows::Forms::GroupBox());
			this->MinContrastCountTxt = (gcnew System::Windows::Forms::TextBox());
			this->MinContrastSlider = (gcnew System::Windows::Forms::VScrollBar());
			this->MinContrastStdTxt = (gcnew System::Windows::Forms::TextBox());
			this->MinContrastStatic = (gcnew System::Windows::Forms::Label());
			this->ContrastFullRad = (gcnew System::Windows::Forms::RadioButton());
			this->ContrastModePanel = (gcnew System::Windows::Forms::GroupBox());
			this->ColourMapDrop = (gcnew System::Windows::Forms::ComboBox());
			this->ContrastScaleDrop = (gcnew System::Windows::Forms::ComboBox());
			this->InvertContrastChck = (gcnew System::Windows::Forms::CheckBox());
			this->RelativeContrast = (gcnew System::Windows::Forms::RadioButton());
			this->AutoContrast = (gcnew System::Windows::Forms::RadioButton());
			this->ContrastWideRad = (gcnew System::Windows::Forms::RadioButton());
			this->ContrastNarrowRad = (gcnew System::Windows::Forms::RadioButton());
			this->MaxContrastStdTxt = (gcnew System::Windows::Forms::TextBox());
			this->MaxContrastCountTxt = (gcnew System::Windows::Forms::TextBox());
			this->MaxContrastSlider = (gcnew System::Windows::Forms::VScrollBar());
			this->MaxContrastStatic = (gcnew System::Windows::Forms::Label());
			this->BlinkChck = (gcnew System::Windows::Forms::CheckBox());
			this->ScanBtnContext = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripSeparator19 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ScanContextGoToBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ScanContextGoToTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator18 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->BatchViewPanel = (gcnew System::Windows::Forms::GroupBox());
			this->FileListDrop = (gcnew System::Windows::Forms::ComboBox());
			this->BlinkTime = (gcnew System::Windows::Forms::NumericUpDown());
			this->SubImageSlideY = (gcnew System::Windows::Forms::VScrollBar());
			this->SubImageSlideX = (gcnew System::Windows::Forms::HScrollBar());
			this->SubImageWindow = (gcnew System::Windows::Forms::PictureBox());
			this->SubImageCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->SubImgRadialPlotMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RadialPlotMedianBackgroundChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtSaveRadialProfileMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageSurfCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageSurfFacet = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageSurfMetal = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageSurfSmooth = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageSurfMesh = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImSurfColumnMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImageEditCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EditValueCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EditBoxCntxt = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->centerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtCut = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtGoToRADec = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtGoToRATxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtGoToDecTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->SubImCntxtGoToPixel = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtGoToPixXTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtGoToPixYTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->SubImCntxtCopyPixPoord = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtCopyCentroidCoord = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtMarkCoord = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImMarkCoordContainedPSE = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator28 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->SubImMarkCoordAsCentroidChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator27 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->SubImMarkCoordClear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImMarkCoordClearContained = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SubImCntxtCopyImage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolBar = (gcnew System::Windows::Forms::ToolStrip());
			this->TBLoad = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBLoadSubFrame = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBAdd = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBReload = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TBRecentFiles = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->TBFind = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBViewFound = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBOpenFound = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TBSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBSaveOver = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBSaveBatch = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBSaveBatchOver = (gcnew System::Windows::Forms::ToolStripButton());
			this->TBFileSavePrecOpts = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->TBOptFileSavePrecDbl = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TBOptFileSavePrecInt32 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TBOptFileSavePrecInt16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TBOptFileSavePrecUInt16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TBZipAllBtn = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->TBZipMoveChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TBZipCopyChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TBQuit = (gcnew System::Windows::Forms::ToolStripButton());
			this->ProgressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->Tooltip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->BatchStdvChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchMedianChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchMeanChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchCorrectionChck = (gcnew System::Windows::Forms::CheckBox());
			this->UVViewNextBtn = (gcnew System::Windows::Forms::Button());
			this->UVViewLastBtn = (gcnew System::Windows::Forms::Button());
			this->BatchSumChck = (gcnew System::Windows::Forms::CheckBox());
			this->UVOpenDirBtn = (gcnew System::Windows::Forms::Button());
			this->PSETab = (gcnew System::Windows::Forms::TabPage());
			this->ROIOnlyPnl = (gcnew System::Windows::Forms::GroupBox());
			this->SubImgROITab = (gcnew System::Windows::Forms::TabControl());
			this->ROIFitTab = (gcnew System::Windows::Forms::TabPage());
			this->SetParametersChck = (gcnew System::Windows::Forms::CheckBox());
			this->ROIFitFcnLabel = (gcnew System::Windows::Forms::Label());
			this->ROIFitFcnDrop = (gcnew System::Windows::Forms::ComboBox());
			this->ROIFitBtn = (gcnew System::Windows::Forms::Button());
			this->ROIViewFitChck = (gcnew System::Windows::Forms::CheckBox());
			this->ROICOGTab = (gcnew System::Windows::Forms::TabPage());
			this->COGBatchChck = (gcnew System::Windows::Forms::CheckBox());
			this->COGViewChck = (gcnew System::Windows::Forms::CheckBox());
			this->COGBtn = (gcnew System::Windows::Forms::Button());
			this->COGIgnoreNPtsUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->PSEFitResultListBox = (gcnew System::Windows::Forms::ListBox());
			this->PSEFitResultsCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->PSEFitResultCntxtCopySelected = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSEFitResultCntxtCopyAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FindSourcesPnl = (gcnew System::Windows::Forms::GroupBox());
			this->PSESigmaCountBtn = (gcnew System::Windows::Forms::Button());
			this->PSEDrop = (gcnew System::Windows::Forms::ComboBox());
			this->PSEDropContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->PSEDropContextAdd = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSEDropContextRemove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSEDropContextClearAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSEDrawROI = (gcnew System::Windows::Forms::CheckBox());
			this->DrawROIContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->SaveROIContext = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadROIContext = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PSESaturationUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->PSEClearBtn = (gcnew System::Windows::Forms::Button());
			this->PSETableViewBtn = (gcnew System::Windows::Forms::Button());
			this->PSESeparationUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->PSELoadSrcDrop = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->PSEEllipticalROI = (gcnew System::Windows::Forms::CheckBox());
			this->PSESeachROIOnlyChck = (gcnew System::Windows::Forms::CheckBox());
			this->PSEKernelRadUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->PSEAutoBackgroundChck = (gcnew System::Windows::Forms::CheckBox());
			this->SavePSChck = (gcnew System::Windows::Forms::CheckBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->PSEFitTypeChck = (gcnew System::Windows::Forms::ComboBox());
			this->PSEKernelMinUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->PSEViewFitChck = (gcnew System::Windows::Forms::CheckBox());
			this->PSEKernelMaxUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->PSEFitChck = (gcnew System::Windows::Forms::CheckBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->PSEFindSrcBtn = (gcnew System::Windows::Forms::Button());
			this->PSEPixelCntLbl = (gcnew System::Windows::Forms::Label());
			this->PSEPixelValLbl = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->PSEPixelMaxUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->PSEPixelMinUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->CutSubImBtn = (gcnew System::Windows::Forms::Button());
			this->RotCCWBtn = (gcnew System::Windows::Forms::Button());
			this->RotCWBtn = (gcnew System::Windows::Forms::Button());
			this->FlipHorzBtn = (gcnew System::Windows::Forms::Button());
			this->FlipVertBtn = (gcnew System::Windows::Forms::Button());
			this->BatchMinimumChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchMaximumChck = (gcnew System::Windows::Forms::CheckBox());
			this->RotateBtn = (gcnew System::Windows::Forms::Button());
			this->RotateBtnCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->RotateBtnCntxtNearest = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateBtnCntxtBiLinear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateBtnCntxtLanczos3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateBtnCntxtLanczos4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateBtnCntxtLanczos5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RotateAngleUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->ShiftHorzBtn = (gcnew System::Windows::Forms::Button());
			this->ShiftVertBtn = (gcnew System::Windows::Forms::Button());
			this->NShiftHorzUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->NShiftVertUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->BatchIndividualAppendageTxt = (gcnew System::Windows::Forms::TextBox());
			this->BatchViewNextBtn = (gcnew System::Windows::Forms::Button());
			this->BatchViewLastBtn = (gcnew System::Windows::Forms::Button());
			this->IndividualDirectoryTxt = (gcnew System::Windows::Forms::RichTextBox());
			this->StackingDirectoryTxt = (gcnew System::Windows::Forms::RichTextBox());
			this->RunningDirectoryTxt = (gcnew System::Windows::Forms::RichTextBox());
			this->KeyValNormBtn = (gcnew System::Windows::Forms::Button());
			this->PadImageBtn = (gcnew System::Windows::Forms::Button());
			this->BatchQuadratureChck = (gcnew System::Windows::Forms::CheckBox());
			this->MainTab = (gcnew System::Windows::Forms::TabControl());
			this->ProcessingTab = (gcnew System::Windows::Forms::TabPage());
			this->ImageBatchRedxnPnl = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->ManRegTrkHWUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->AutoRegBtn = (gcnew System::Windows::Forms::Button());
			this->ManRegBtn = (gcnew System::Windows::Forms::Button());
			this->ManRegSrcHWUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->SCMChck = (gcnew System::Windows::Forms::CheckBox());
			this->ScmTxt = (gcnew System::Windows::Forms::NumericUpDown());
			this->ImageCorrxnPnl = (gcnew System::Windows::Forms::GroupBox());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->MultImgChck = (gcnew System::Windows::Forms::CheckBox());
			this->DivFlatChck = (gcnew System::Windows::Forms::CheckBox());
			this->SubBiasChck = (gcnew System::Windows::Forms::CheckBox());
			this->AddImageChck = (gcnew System::Windows::Forms::CheckBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->BinBtn = (gcnew System::Windows::Forms::Button());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->XBinUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->YBinUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->ImageOpFilterLabel = (gcnew System::Windows::Forms::Label());
			this->ImageOpFilterBtn = (gcnew System::Windows::Forms::Button());
			this->ImageOpFilterWidthUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->ImageOpFilterTypeDrop = (gcnew System::Windows::Forms::ComboBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->ScalarOpBtn = (gcnew System::Windows::Forms::Button());
			this->ScalarOpStyleDrop = (gcnew System::Windows::Forms::ComboBox());
			this->ScalarOpValTxt = (gcnew System::Windows::Forms::TextBox());
			this->MathOpBtn = (gcnew System::Windows::Forms::Button());
			this->MathOpDrop = (gcnew System::Windows::Forms::ComboBox());
			this->ImageOpsPnl = (gcnew System::Windows::Forms::GroupBox());
			this->RGBSaveBtn = (gcnew System::Windows::Forms::Button());
			this->CombineRGBBtn = (gcnew System::Windows::Forms::Button());
			this->ClipToContrastBtn = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->FindImagePtsBtn = (gcnew System::Windows::Forms::Button());
			this->FindPtsDrop = (gcnew System::Windows::Forms::ComboBox());
			this->ReplaceImagePtsTxt = (gcnew System::Windows::Forms::TextBox());
			this->FindImagePtsTxt = (gcnew System::Windows::Forms::TextBox());
			this->ReplaceImagePtsBtn = (gcnew System::Windows::Forms::Button());
			this->ReplaceImagePtsDrop = (gcnew System::Windows::Forms::ComboBox());
			this->BatchTab = (gcnew System::Windows::Forms::TabPage());
			this->BatchQuickScanSubDirsChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchScanDirectoryFileTypeDrop = (gcnew System::Windows::Forms::ComboBox());
			this->BatchScanDirectoryBtn = (gcnew System::Windows::Forms::Button());
			this->BatchListViewPanel = (gcnew System::Windows::Forms::GroupBox());
			this->BatchMovieSkipUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->BatchGoToBtn = (gcnew System::Windows::Forms::Button());
			this->BatchBlinkTime = (gcnew System::Windows::Forms::NumericUpDown());
			this->BatchBlinkChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchGoToUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->BatchOperationTab = (gcnew System::Windows::Forms::TabControl());
			this->BatchSetTab = (gcnew System::Windows::Forms::TabPage());
			this->BatchOutLabel = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->BatchMeanRad = (gcnew System::Windows::Forms::RadioButton());
			this->BatchSumRad = (gcnew System::Windows::Forms::RadioButton());
			this->BatchIndividualTab = (gcnew System::Windows::Forms::TabPage());
			this->BatchFileKeepDirectoriesChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchFileParallelChck = (gcnew System::Windows::Forms::CheckBox());
			this->TabBatchElementalFindStyleDD = (gcnew System::Windows::Forms::ComboBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->TabBatchElementalReplaceValTxt = (gcnew System::Windows::Forms::TextBox());
			this->BatchFileAppRad = (gcnew System::Windows::Forms::RadioButton());
			this->TabBatchElementalReplaceStyleDD = (gcnew System::Windows::Forms::ComboBox());
			this->BatchFileOvrWrtRad = (gcnew System::Windows::Forms::RadioButton());
			this->TabBatchElementalFindValTxt = (gcnew System::Windows::Forms::TextBox());
			this->TabBatchElementalFindPointsChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchStackingTab = (gcnew System::Windows::Forms::TabPage());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->StackUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->BatchRunningTab = (gcnew System::Windows::Forms::TabPage());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->BatchRunningNumUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->BatchRunningOpDrop = (gcnew System::Windows::Forms::ComboBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->BatchAddImageChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchSubtractImageChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchMultiplyImageChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchDivideImageChck = (gcnew System::Windows::Forms::CheckBox());
			this->BatchSubImagePanel = (gcnew System::Windows::Forms::Panel());
			this->BatchSubImageChck = (gcnew System::Windows::Forms::CheckBox());
			this->YEndLabel = (gcnew System::Windows::Forms::Label());
			this->XStartLabel = (gcnew System::Windows::Forms::Label());
			this->YStartLabel = (gcnew System::Windows::Forms::Label());
			this->XEndLabel = (gcnew System::Windows::Forms::Label());
			this->BatchComputeBtn = (gcnew System::Windows::Forms::Button());
			this->BatchOpenListBtn = (gcnew System::Windows::Forms::Button());
			this->BatchMakeListBtn = (gcnew System::Windows::Forms::Button());
			this->BatchListNameTxt = (gcnew System::Windows::Forms::Label());
			this->UVITTab = (gcnew System::Windows::Forms::TabPage());
			this->UVAnalysisPanel = (gcnew System::Windows::Forms::GroupBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->UVPlotXAxisDrop = (gcnew System::Windows::Forms::ComboBox());
			this->UVHVUTelemBtn = (gcnew System::Windows::Forms::Button());
			this->UVStatsAnalysisBtn = (gcnew System::Windows::Forms::Button());
			this->UVOpenRawBtn = (gcnew System::Windows::Forms::Button());
			this->UVOpenSubDirChck = (gcnew System::Windows::Forms::CheckBox());
			this->CentroidingPanel = (gcnew System::Windows::Forms::GroupBox());
			this->UVAutoThreshChck = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->UVBGOffset = (gcnew System::Windows::Forms::NumericUpDown());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->UVActiveBGChck = (gcnew System::Windows::Forms::CheckBox());
			this->UVCornerThreshUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->UVDarkImageTxt = (gcnew System::Windows::Forms::Label());
			this->UVDarkImageRad = (gcnew System::Windows::Forms::RadioButton());
			this->UVBackGroundUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->UVDarkScalarRad = (gcnew System::Windows::Forms::RadioButton());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->UVTransferImagesBtn = (gcnew System::Windows::Forms::Button());
			this->UVImageOnlyChck = (gcnew System::Windows::Forms::CheckBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->UVSaveCentroidDrop = (gcnew System::Windows::Forms::ComboBox());
			this->UVCentroidBtn = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->UVShapeMaxThresh = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->UVShapeMinThresh = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->UVPixelMaxThresh = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->UVPixelMinThresh = (gcnew System::Windows::Forms::NumericUpDown());
			this->UVSubRangeChck = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->UVAlgorithmListBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->UVAlgorithmCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->UVXDecHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVYDecHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVPixelHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVShapeHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFCMinHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFCMaxMinHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFrameHist = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVPrecisionUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->UVBatchViewPanel = (gcnew System::Windows::Forms::GroupBox());
			this->UVMovieSkipUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->UVGoToBtn = (gcnew System::Windows::Forms::Button());
			this->UVBlinkTimeUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->UVMovieBtn = (gcnew System::Windows::Forms::CheckBox());
			this->UVViewSelectionStatic = (gcnew System::Windows::Forms::Label());
			this->UVGoToUpD = (gcnew System::Windows::Forms::NumericUpDown());
			this->UVOpenCentroidBtn = (gcnew System::Windows::Forms::Button());
			this->XYImageValueTxt = (gcnew System::Windows::Forms::Label());
			this->YPositionTxt = (gcnew System::Windows::Forms::Label());
			this->XPositionTxt = (gcnew System::Windows::Forms::Label());
			this->ToolBarImageList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->SaveFileDlg = (gcnew System::Windows::Forms::SaveFileDialog());
			this->ImageWindow = (gcnew System::Windows::Forms::PictureBox());
			this->ViewHeaderBtn = (gcnew System::Windows::Forms::CheckBox());
			this->HeaderCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->HCEdit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCEditCurrent = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCEditAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCInsert = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCInsertCurrent = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCInsertBatch = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCInsertSelectedToOthers = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCRemove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCRemoveCurrent = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCRemoveBatch = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCCopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCCopyKeyValue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCCopyListValue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCExtract = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCExtractKeyValue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCExtractListValues = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCPlot = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCPlotKeyValues = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HCPlotListValues = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HeaderKeyValTxt = (gcnew System::Windows::Forms::ListBox());
			this->HeaderKeyComTxt = (gcnew System::Windows::Forms::ListBox());
			this->HeaderKeyTxt = (gcnew System::Windows::Forms::ListBox());
			this->MainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->FileMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMLoadSubFrame = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ConvertFromTextMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMViewExtensionTable = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMAdd = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMReload = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMRecentFiles = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->FMFind = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMViewFound = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMOpenFound = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->FMSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FMSaveBatch = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->FMQuit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EditMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMFileBias = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMFileDark = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMFileFlat = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMBatch = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMBatchBias = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMBatchDark = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMBatchFlat = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMCopyHeader = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptsMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fileSavingPrecisionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptFileSavePrecDbl = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptFileSavePrecInt32 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptFileSavePrecInt16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptFileSavePrecUInt16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->veiwToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptViewImage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptInvertImageView = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OptViewSpectrum = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ResetPlotPositions = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSRADecShowChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSCopyToLoadedImgs = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSCopyToDiskFiles = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSClearMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSClearAllChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSPlotSolutionPtsBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSClearPlotSolutionPtsBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator30 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSRADecManual = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator31 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->AutoWCSMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoSolveBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoExternalDLLChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoStopCriteriaMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoStopNMatchesBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoStopNMatchesText = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem20 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoStopPercMatchesText = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator38 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSAutoCatalogueMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem17 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoCatalogueExtensionTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator43 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->cVAL1RAToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoCatalogueCVAL1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator42 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->cVAL2DecToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoCatalogueCVAL2 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator41 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoCatalogueMag = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem23 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoCatalogueTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSAutoQueryBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AstroQueryCatalogueNameMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AstroQueryCatalogueNameDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->toolStripSeparator46 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem24 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoQueryCVAL1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem25 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoQueryCVAL2 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem26 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoResolveRadiusTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSQuerySquareRegionChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator45 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSQuerySaveFileChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSQuerySaveFileChooseDirBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator47 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSQuerySolveAfter = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoNCatPtsLabel = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoNCatPtsTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator33 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->AutoWCSScaleMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AutoWCSScaleSaveBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WSCSaveScaleTxtBox = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSScaleInit = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSScaleInitLB = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSScaleInitUB = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem14 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSRotationInit = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSRotationInitLB = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSRotationInitUB = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator34 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem15 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoVertexToleranceTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator37 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSAutoParityMenuBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoXAxisParityChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoYAxisParityChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator44 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSAutoDisplayChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoConditionArraysChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoRefineChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem19 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSAutoRefineNPtsTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator35 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->WCSRefineSolutionBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSLoadSimbadList = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem18 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSLoadListNPtsTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->WCSListExciseToROI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSClarifyListSources = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->WCSSolveList = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator29 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->AutoWCSXCorr = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVITMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVIT_EMGSEMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EMGSE_UnpackImg = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExtractL1gzsMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1AutoRunChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1AutoProceedVISBackGround = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1AutoProceedVISTracking = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1AutoApplyVISDrift = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DigestL1FITSImageMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DigestApplyFPNChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DigestApplyDISTChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem22 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DigestApplyDISTInterpNearChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DigestApplyDISTInterpBiLinChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DiscardDuplicateChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1TransformNUVtoFUVChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DigestPCParityChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator36 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->L1SkipINTMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DegradientINTMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1CleanINTMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem13 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1CleanINTLineThreshold = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator40 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem21 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1CleanINTNPix = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator39 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->L1DiscardDataTimeChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1DiscardDataTimeDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->L1FilterCorrectionChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1TBCChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator48 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->L1DigestDeleteFileChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CreateFlatFieldListMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ApplyUVFPNMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVIT_ApplyCPUCorrectionMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ConvertListToImgMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FilterCosmicRaysChckMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CosmicRayFilterCountMenuChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CosmicRayFilterMenuTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator11 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->CosmicRayFilterSigmaMenuChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CosmicRayFilterSigmaMenuTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->MaxMinThreshChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MaxMinThreshTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->MaxMinCountTwiceChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->L1CentroidPaddingChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PCCentroidPaddingDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->ApplyExpArrayToImageChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ApplyFlatListToImageChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ListToImage1PixMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ListToImage2PixMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ListToImage4PixMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ListToImage8PixMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ListToImage16PixMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlotCountsPerFrameMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->perFrameMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator17 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->perTimeBinMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plotPerTimeBinComboBox = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->ParcelListAsFramesMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ParcelStackTimeDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->ParcelStackmdMmChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CreateDriftListMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CreateDriftFromPCMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DriftFromListTimeTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->DriftFromListEndTimeTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->DriftStackTimeDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->DriftPCROIOnly = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DriftFromPCInterpolateChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DriftSmoothNDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->UVAutoApplyDriftandImageChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVAutoDriftImageViewChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator12 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->DriftFromPCPSTrackBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcROIAutoRunChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcROIFindSrcChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcROIFindNSrcDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcROIStackDriftDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->CreateDriftFromINTMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CrossCorrINTDriftChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcINTDriftChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcINTDriftDisplayChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcINTDriftDisplayCadenceDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->PSTrackDisplayClearBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator16 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->PointSrcINTDriftNoPSEConfChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator10 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->SmoothINTDriftChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TryAutoDeBiasINTDrift = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PointSrcINTDriftNoPlotConfChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlotDriftListMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CleanVISImagesMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ApplyDriftListMentuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ConsolidateNUVApplyToFUV = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ConsolidateDriftFolderChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ConsolidateTimeListFolderChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PCModeDriftSelfCorrectionMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->INTAtoINTADriftCorrectionMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ApplyDriftCreateExpArrayChc = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExposureArrayResMenuText = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExposureArrayResolutionDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->ShiftAndRotateMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->GeneralUVRegistrationMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVGeneralRegistrationResolutionDrop = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->toolStripSeparator21 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->masterizeSinglesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RegistrationXYIntsListFolderScanChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UserDefinedShiftRotateMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator8 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->LinearRotationChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator9 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->FlipHorizontalMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FlipVerticalMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UserRotationTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->UserRotationXCenterTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->UserRotationYCenterTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->UserXShiftTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->UserYShiftTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator13 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->GeneralTransformChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator14 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TransformCoefATxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformCoefBTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformCoefCTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformCoefDTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformCenterXTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformCenterYTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformShiftXTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->TransformShiftYTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator15 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->UVCombineCentroidListsMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVDeleteMergeDirsChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MergeXYIntsListFolderScanChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVAutoPSFPostMergeChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVLoadAllMerged = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator20 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->UVNUVToFUVFrameMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DeRotateViaWCSBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->invertWCSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DeSaturateROICountsMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CorrectBackgroundCountsChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->BackgroundCountsPixelFrameTxt = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->ExtractROICentroidListMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFinalizeScienceBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFinalizeIncludeExpMapChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFinalizeIncludeTablesChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFinalizeDeleteIntrmdtChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVFinalizeMoveOrCopyZipChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UVMovieTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->UVOpenDirDlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->UVOpenRawDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->UVSaveCentroidDlg = (gcnew System::Windows::Forms::SaveFileDialog());
			this->CCDLABTaskBarIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->TaskBarCntxt = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->TCQuit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TBDestructTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->UVOpenUCFDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->ImageOpsWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->UVCentroidWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->SurfWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->FormLoadBGW = (gcnew System::ComponentModel::BackgroundWorker());
			this->UVHistWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->ImageCntxtViewWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->PSEFitWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->BatchBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->ViewImageTog = (gcnew System::Windows::Forms::CheckBox());
			this->ViewSpectrumTog = (gcnew System::Windows::Forms::CheckBox());
			this->InvQuitBtn = (gcnew System::Windows::Forms::Button());
			this->WriteImageSetBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->BatchMovieTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->ParcelUVCentroidWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->DriftFromPCListWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->DriftFromINTWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->Chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->ManRegWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->INTAtoINTAapplyDriftWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->DigestL1Wrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->DiscardL1DuplicateWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->ConvertUVCentroidListToImgWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->RegistrationUVCentroidWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->MergeCentroidListsWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->RotationUVCentroidWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->DirectoryLabel = (gcnew System::Windows::Forms::Label());
			this->DriftNUVtoFUVBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->SIZECntxtBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->ExtractL1ArchiveBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->ApplyDriftListWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->CleanVISBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->WCSAutoBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->TEST_TEXT_BOX = (gcnew System::Windows::Forms::TextBox());
			this->DriftFromPCPSTrackBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->UVFinalizeBGWrkr = (gcnew System::ComponentModel::BackgroundWorker());
			this->PSEDropContextPlotAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ImageWindowCntxt->SuspendLayout();
			this->ImageFingerPointContext->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HalfWidthXUpD))->BeginInit();
			this->SubImagePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HalfWidthYUpD))->BeginInit();
			this->StatsContxt->SuspendLayout();
			this->FileInfoPanel->SuspendLayout();
			this->SIZECntxtMenu->SuspendLayout();
			this->FileDirectoryTxtContextMenu->SuspendLayout();
			this->ContrastPanel->SuspendLayout();
			this->ContrastModePanel->SuspendLayout();
			this->ScanBtnContext->SuspendLayout();
			this->BatchViewPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BlinkTime))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubImageWindow))->BeginInit();
			this->SubImageCntxt->SuspendLayout();
			this->ToolBar->SuspendLayout();
			this->PSETab->SuspendLayout();
			this->ROIOnlyPnl->SuspendLayout();
			this->SubImgROITab->SuspendLayout();
			this->ROIFitTab->SuspendLayout();
			this->ROICOGTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->COGIgnoreNPtsUpD))->BeginInit();
			this->PSEFitResultsCntxt->SuspendLayout();
			this->FindSourcesPnl->SuspendLayout();
			this->PSEDropContextMenu->SuspendLayout();
			this->DrawROIContextMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSESaturationUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSESeparationUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEKernelRadUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEKernelMinUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEKernelMaxUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEPixelMaxUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEPixelMinUpD))->BeginInit();
			this->RotateBtnCntxt->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotateAngleUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NShiftHorzUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NShiftVertUpD))->BeginInit();
			this->MainTab->SuspendLayout();
			this->ProcessingTab->SuspendLayout();
			this->ImageBatchRedxnPnl->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ManRegTrkHWUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ManRegSrcHWUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ScmTxt))->BeginInit();
			this->ImageCorrxnPnl->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XBinUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YBinUpD))->BeginInit();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImageOpFilterWidthUpD))->BeginInit();
			this->panel4->SuspendLayout();
			this->ImageOpsPnl->SuspendLayout();
			this->panel1->SuspendLayout();
			this->BatchTab->SuspendLayout();
			this->BatchListViewPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchMovieSkipUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchBlinkTime))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchGoToUpD))->BeginInit();
			this->BatchOperationTab->SuspendLayout();
			this->BatchSetTab->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->BatchIndividualTab->SuspendLayout();
			this->BatchStackingTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StackUpD))->BeginInit();
			this->BatchRunningTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchRunningNumUpD))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->BatchSubImagePanel->SuspendLayout();
			this->UVITTab->SuspendLayout();
			this->UVAnalysisPanel->SuspendLayout();
			this->CentroidingPanel->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVBGOffset))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVCornerThreshUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVBackGroundUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVShapeMaxThresh))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVShapeMinThresh))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVPixelMaxThresh))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVPixelMinThresh))->BeginInit();
			this->UVAlgorithmCntxt->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVPrecisionUpD))->BeginInit();
			this->UVBatchViewPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVMovieSkipUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVBlinkTimeUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVGoToUpD))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImageWindow))->BeginInit();
			this->HeaderCntxt->SuspendLayout();
			this->MainMenu->SuspendLayout();
			this->TaskBarCntxt->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// ImageWindowCntxt
			// 
			this->ImageWindowCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ImageWndwCntxtView,
					this->ImageWndwCntxtAnalysis, this->ImageWndwCntxtEdit, this->ImageWndwCntxtPlot, this->ImageWndwCntxtMarkCoord
			});
			this->ImageWindowCntxt->Name = L"SubImageCntxtMenu";
			this->ImageWindowCntxt->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->ImageWindowCntxt->ShowImageMargin = false;
			this->ImageWindowCntxt->Size = System::Drawing::Size(139, 114);
			// 
			// ImageWndwCntxtView
			// 
			this->ImageWndwCntxtView->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ShowCursorBox,
					this->ShowCrosshair, this->ShowFoundCoordsChck, this->ShowPSEChck, this->ImageWindowCntxtSquare
			});
			this->ImageWndwCntxtView->Name = L"ImageWndwCntxtView";
			this->ImageWndwCntxtView->Size = System::Drawing::Size(138, 22);
			this->ImageWndwCntxtView->Text = L"Image Window";
			// 
			// ShowCursorBox
			// 
			this->ShowCursorBox->Checked = true;
			this->ShowCursorBox->CheckOnClick = true;
			this->ShowCursorBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ShowCursorBox->Name = L"ShowCursorBox";
			this->ShowCursorBox->Size = System::Drawing::Size(178, 22);
			this->ShowCursorBox->Text = L"Show Cursor Box";
			this->ShowCursorBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::ShowCursorBox_CheckedChanged);
			// 
			// ShowCrosshair
			// 
			this->ShowCrosshair->CheckOnClick = true;
			this->ShowCrosshair->Name = L"ShowCrosshair";
			this->ShowCrosshair->Size = System::Drawing::Size(178, 22);
			this->ShowCrosshair->Text = L"Show Crosshair";
			this->ShowCrosshair->CheckedChanged += gcnew System::EventHandler(this, &Form1::ShowCrosshair_CheckedChanged);
			// 
			// ShowFoundCoordsChck
			// 
			this->ShowFoundCoordsChck->CheckOnClick = true;
			this->ShowFoundCoordsChck->Enabled = false;
			this->ShowFoundCoordsChck->Name = L"ShowFoundCoordsChck";
			this->ShowFoundCoordsChck->Size = System::Drawing::Size(178, 22);
			this->ShowFoundCoordsChck->Text = L"Show Found Values";
			this->ShowFoundCoordsChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::ShowFoundCoordsChck_CheckedChanged);
			// 
			// ShowPSEChck
			// 
			this->ShowPSEChck->CheckOnClick = true;
			this->ShowPSEChck->Enabled = false;
			this->ShowPSEChck->Name = L"ShowPSEChck";
			this->ShowPSEChck->Size = System::Drawing::Size(178, 22);
			this->ShowPSEChck->Text = L"Show Point Sources";
			this->ShowPSEChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::ShowPSEChck_CheckedChanged);
			// 
			// ImageWindowCntxtSquare
			// 
			this->ImageWindowCntxtSquare->Name = L"ImageWindowCntxtSquare";
			this->ImageWindowCntxtSquare->Size = System::Drawing::Size(178, 22);
			this->ImageWindowCntxtSquare->Text = L"Square";
			this->ImageWindowCntxtSquare->Visible = false;
			this->ImageWindowCntxtSquare->Click += gcnew System::EventHandler(this, &Form1::ImageWindowCntxtSquare_Click);
			// 
			// ImageWndwCntxtAnalysis
			// 
			this->ImageWndwCntxtAnalysis->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ImageViewHistogram });
			this->ImageWndwCntxtAnalysis->Name = L"ImageWndwCntxtAnalysis";
			this->ImageWndwCntxtAnalysis->Size = System::Drawing::Size(138, 22);
			this->ImageWndwCntxtAnalysis->Text = L"Analysis";
			// 
			// ImageViewHistogram
			// 
			this->ImageViewHistogram->Name = L"ImageViewHistogram";
			this->ImageViewHistogram->Size = System::Drawing::Size(130, 22);
			this->ImageViewHistogram->Text = L"Histogram";
			this->ImageViewHistogram->Click += gcnew System::EventHandler(this, &Form1::ImageViewHistogram_Click);
			// 
			// ImageWndwCntxtEdit
			// 
			this->ImageWndwCntxtEdit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ImageEditValueCntxt,
					this->ImageEditBoxCntxt
			});
			this->ImageWndwCntxtEdit->Name = L"ImageWndwCntxtEdit";
			this->ImageWndwCntxtEdit->Size = System::Drawing::Size(138, 22);
			this->ImageWndwCntxtEdit->Text = L"Edit";
			// 
			// ImageEditValueCntxt
			// 
			this->ImageEditValueCntxt->Name = L"ImageEditValueCntxt";
			this->ImageEditValueCntxt->Size = System::Drawing::Size(132, 22);
			this->ImageEditValueCntxt->Text = L"Value";
			this->ImageEditValueCntxt->Click += gcnew System::EventHandler(this, &Form1::ImageEditValueCntxt_Click);
			// 
			// ImageEditBoxCntxt
			// 
			this->ImageEditBoxCntxt->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ImageEditBoxSetSubRangeCntxt });
			this->ImageEditBoxCntxt->Name = L"ImageEditBoxCntxt";
			this->ImageEditBoxCntxt->Size = System::Drawing::Size(132, 22);
			this->ImageEditBoxCntxt->Text = L"Cursor Box";
			this->ImageEditBoxCntxt->Click += gcnew System::EventHandler(this, &Form1::ImageEditBoxCntxt_Click);
			// 
			// ImageEditBoxSetSubRangeCntxt
			// 
			this->ImageEditBoxSetSubRangeCntxt->Name = L"ImageEditBoxSetSubRangeCntxt";
			this->ImageEditBoxSetSubRangeCntxt->Size = System::Drawing::Size(187, 22);
			this->ImageEditBoxSetSubRangeCntxt->Text = L"Set Sub-Frame Range";
			this->ImageEditBoxSetSubRangeCntxt->Click += gcnew System::EventHandler(this, &Form1::ImageEditBoxSetSubRangeCntxt_Click);
			// 
			// ImageWndwCntxtPlot
			// 
			this->ImageWndwCntxtPlot->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->ImageWndwCntxtPlotRow,
					this->ImageWndwCntxtPlotRowSubOnly, this->toolStripSeparator25, this->ImageWndwCntxtPlotCol, this->ImageWndwCntxtPlotColSubOnly,
					this->toolStripSeparator24, this->ImageWndwPlotRadialVector, this->ImageWindowRadialLockSources, this->ImageWindowRadialSetAngle,
					this->ImageWindowSaveRadialVector
			});
			this->ImageWndwCntxtPlot->Name = L"ImageWndwCntxtPlot";
			this->ImageWndwCntxtPlot->Size = System::Drawing::Size(138, 22);
			this->ImageWndwCntxtPlot->Text = L"Plot";
			// 
			// ImageWndwCntxtPlotRow
			// 
			this->ImageWndwCntxtPlotRow->CheckOnClick = true;
			this->ImageWndwCntxtPlotRow->Name = L"ImageWndwCntxtPlotRow";
			this->ImageWndwCntxtPlotRow->Size = System::Drawing::Size(201, 22);
			this->ImageWndwCntxtPlotRow->Text = L"Current Row";
			this->ImageWndwCntxtPlotRow->Click += gcnew System::EventHandler(this, &Form1::ImageWndwCntxtPlotRow_Click);
			// 
			// ImageWndwCntxtPlotRowSubOnly
			// 
			this->ImageWndwCntxtPlotRowSubOnly->CheckOnClick = true;
			this->ImageWndwCntxtPlotRowSubOnly->Name = L"ImageWndwCntxtPlotRowSubOnly";
			this->ImageWndwCntxtPlotRowSubOnly->Size = System::Drawing::Size(201, 22);
			this->ImageWndwCntxtPlotRowSubOnly->Text = L"Sub-range only";
			this->ImageWndwCntxtPlotRowSubOnly->Click += gcnew System::EventHandler(this, &Form1::ImageWndwCntxtPlotRowSubOnly_Click);
			// 
			// toolStripSeparator25
			// 
			this->toolStripSeparator25->Name = L"toolStripSeparator25";
			this->toolStripSeparator25->Size = System::Drawing::Size(198, 6);
			// 
			// ImageWndwCntxtPlotCol
			// 
			this->ImageWndwCntxtPlotCol->CheckOnClick = true;
			this->ImageWndwCntxtPlotCol->Name = L"ImageWndwCntxtPlotCol";
			this->ImageWndwCntxtPlotCol->Size = System::Drawing::Size(201, 22);
			this->ImageWndwCntxtPlotCol->Text = L"Current Column";
			this->ImageWndwCntxtPlotCol->Click += gcnew System::EventHandler(this, &Form1::ImageWndwCntxtPlotCol_Click);
			// 
			// ImageWndwCntxtPlotColSubOnly
			// 
			this->ImageWndwCntxtPlotColSubOnly->CheckOnClick = true;
			this->ImageWndwCntxtPlotColSubOnly->Name = L"ImageWndwCntxtPlotColSubOnly";
			this->ImageWndwCntxtPlotColSubOnly->Size = System::Drawing::Size(201, 22);
			this->ImageWndwCntxtPlotColSubOnly->Text = L"Sub-range only";
			this->ImageWndwCntxtPlotColSubOnly->Click += gcnew System::EventHandler(this, &Form1::ImageWndwCntxtPlotColSubOnly_Click);
			// 
			// toolStripSeparator24
			// 
			this->toolStripSeparator24->Name = L"toolStripSeparator24";
			this->toolStripSeparator24->Size = System::Drawing::Size(198, 6);
			// 
			// ImageWndwPlotRadialVector
			// 
			this->ImageWndwPlotRadialVector->CheckOnClick = true;
			this->ImageWndwPlotRadialVector->Enabled = false;
			this->ImageWndwPlotRadialVector->Name = L"ImageWndwPlotRadialVector";
			this->ImageWndwPlotRadialVector->Size = System::Drawing::Size(201, 22);
			this->ImageWndwPlotRadialVector->Text = L"Radial Vector";
			this->ImageWndwPlotRadialVector->CheckedChanged += gcnew System::EventHandler(this, &Form1::ImageWndwPlotRadialVector_CheckedChanged);
			// 
			// ImageWindowRadialLockSources
			// 
			this->ImageWindowRadialLockSources->Checked = true;
			this->ImageWindowRadialLockSources->CheckOnClick = true;
			this->ImageWindowRadialLockSources->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ImageWindowRadialLockSources->Enabled = false;
			this->ImageWindowRadialLockSources->Name = L"ImageWindowRadialLockSources";
			this->ImageWindowRadialLockSources->Size = System::Drawing::Size(201, 22);
			this->ImageWindowRadialLockSources->Text = L"Lock Sources for Length";
			// 
			// ImageWindowRadialSetAngle
			// 
			this->ImageWindowRadialSetAngle->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ImageWindowRadialAngleTxt });
			this->ImageWindowRadialSetAngle->Enabled = false;
			this->ImageWindowRadialSetAngle->Name = L"ImageWindowRadialSetAngle";
			this->ImageWindowRadialSetAngle->Size = System::Drawing::Size(201, 22);
			this->ImageWindowRadialSetAngle->Text = L"Set Radial Angle";
			this->ImageWindowRadialSetAngle->DropDownOpened += gcnew System::EventHandler(this, &Form1::ImageWindowRadialSetAngle_DropDownOpened);
			// 
			// ImageWindowRadialAngleTxt
			// 
			this->ImageWindowRadialAngleTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->ImageWindowRadialAngleTxt->Name = L"ImageWindowRadialAngleTxt";
			this->ImageWindowRadialAngleTxt->Size = System::Drawing::Size(100, 23);
			this->ImageWindowRadialAngleTxt->Text = L"0";
			this->ImageWindowRadialAngleTxt->ToolTipText = L"Degrees";
			this->ImageWindowRadialAngleTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::ImageWindowRadialAngleTxt_KeyDown);
			this->ImageWindowRadialAngleTxt->TextChanged += gcnew System::EventHandler(this, &Form1::ImageWindowRadialAngleTxt_TextChanged);
			// 
			// ImageWindowSaveRadialVector
			// 
			this->ImageWindowSaveRadialVector->Enabled = false;
			this->ImageWindowSaveRadialVector->Name = L"ImageWindowSaveRadialVector";
			this->ImageWindowSaveRadialVector->Size = System::Drawing::Size(201, 22);
			this->ImageWindowSaveRadialVector->Text = L"Save Radial Vector";
			this->ImageWindowSaveRadialVector->Click += gcnew System::EventHandler(this, &Form1::ImageWindowSaveRadialVector_Click);
			// 
			// ImageWndwCntxtMarkCoord
			// 
			this->ImageWndwCntxtMarkCoord->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->MarkCoordClear,
					this->MarkCoordSave, this->MarkCoordLoad
			});
			this->ImageWndwCntxtMarkCoord->Name = L"ImageWndwCntxtMarkCoord";
			this->ImageWndwCntxtMarkCoord->Size = System::Drawing::Size(138, 22);
			this->ImageWndwCntxtMarkCoord->Text = L"Mark Coordinate";
			this->ImageWndwCntxtMarkCoord->Click += gcnew System::EventHandler(this, &Form1::ImageWndwCntxtMarkCoord_Click);
			// 
			// MarkCoordClear
			// 
			this->MarkCoordClear->Name = L"MarkCoordClear";
			this->MarkCoordClear->Size = System::Drawing::Size(118, 22);
			this->MarkCoordClear->Text = L"Clear All";
			this->MarkCoordClear->Click += gcnew System::EventHandler(this, &Form1::MarkCoordClear_Click);
			// 
			// MarkCoordSave
			// 
			this->MarkCoordSave->Name = L"MarkCoordSave";
			this->MarkCoordSave->Size = System::Drawing::Size(118, 22);
			this->MarkCoordSave->Text = L"Save";
			this->MarkCoordSave->Click += gcnew System::EventHandler(this, &Form1::MarkCoordSave_Click);
			// 
			// MarkCoordLoad
			// 
			this->MarkCoordLoad->Name = L"MarkCoordLoad";
			this->MarkCoordLoad->Size = System::Drawing::Size(118, 22);
			this->MarkCoordLoad->Text = L"Load";
			this->MarkCoordLoad->Click += gcnew System::EventHandler(this, &Form1::MarkCoordLoad_Click);
			// 
			// ViewSelectionStatic
			// 
			this->ViewSelectionStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ViewSelectionStatic->Location = System::Drawing::Point(5, 15);
			this->ViewSelectionStatic->Name = L"ViewSelectionStatic";
			this->ViewSelectionStatic->Size = System::Drawing::Size(131, 15);
			this->ViewSelectionStatic->TabIndex = 19;
			this->ViewSelectionStatic->Text = L"View Selection ( 0 files )";
			// 
			// ViewNextBtn
			// 
			this->ViewNextBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewNextBtn.BackgroundImage")));
			this->ViewNextBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ViewNextBtn->Cursor = System::Windows::Forms::Cursors::PanEast;
			this->ViewNextBtn->Location = System::Drawing::Point(95, 56);
			this->ViewNextBtn->Name = L"ViewNextBtn";
			this->ViewNextBtn->Size = System::Drawing::Size(40, 38);
			this->ViewNextBtn->TabIndex = 20;
			this->Tooltip->SetToolTip(this->ViewNextBtn, L"View Next Image");
			this->ViewNextBtn->Click += gcnew System::EventHandler(this, &Form1::ViewNextBtn_Click);
			// 
			// ViewLastbtn
			// 
			this->ViewLastbtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ViewLastbtn.BackgroundImage")));
			this->ViewLastbtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ViewLastbtn->Cursor = System::Windows::Forms::Cursors::PanWest;
			this->ViewLastbtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->ViewLastbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ViewLastbtn->Location = System::Drawing::Point(5, 56);
			this->ViewLastbtn->Name = L"ViewLastbtn";
			this->ViewLastbtn->Size = System::Drawing::Size(40, 38);
			this->ViewLastbtn->TabIndex = 21;
			this->Tooltip->SetToolTip(this->ViewLastbtn, L"View Previous Image");
			this->ViewLastbtn->Click += gcnew System::EventHandler(this, &Form1::ViewLastbtn_Click);
			// 
			// MoveUpBtn
			// 
			this->MoveUpBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MoveUpBtn.BackgroundImage")));
			this->MoveUpBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->MoveUpBtn->Cursor = System::Windows::Forms::Cursors::PanNorth;
			this->MoveUpBtn->Location = System::Drawing::Point(139, 15);
			this->MoveUpBtn->Name = L"MoveUpBtn";
			this->MoveUpBtn->Size = System::Drawing::Size(44, 38);
			this->MoveUpBtn->TabIndex = 19;
			this->Tooltip->SetToolTip(this->MoveUpBtn, L"Move Current File Up One Slot");
			this->MoveUpBtn->Click += gcnew System::EventHandler(this, &Form1::MoveUpBtn_Click);
			// 
			// MoveDownBtn
			// 
			this->MoveDownBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MoveDownBtn.BackgroundImage")));
			this->MoveDownBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->MoveDownBtn->Cursor = System::Windows::Forms::Cursors::PanSouth;
			this->MoveDownBtn->Location = System::Drawing::Point(139, 56);
			this->MoveDownBtn->Name = L"MoveDownBtn";
			this->MoveDownBtn->Size = System::Drawing::Size(44, 38);
			this->MoveDownBtn->TabIndex = 20;
			this->Tooltip->SetToolTip(this->MoveDownBtn, L"Move Current File Down One Slot");
			this->MoveDownBtn->Click += gcnew System::EventHandler(this, &Form1::MoveDownBtn_Click);
			// 
			// DeleteFileBtn
			// 
			this->DeleteFileBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DeleteFileBtn.BackgroundImage")));
			this->DeleteFileBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->DeleteFileBtn->Cursor = System::Windows::Forms::Cursors::No;
			this->DeleteFileBtn->Location = System::Drawing::Point(183, 15);
			this->DeleteFileBtn->Name = L"DeleteFileBtn";
			this->DeleteFileBtn->Size = System::Drawing::Size(48, 38);
			this->DeleteFileBtn->TabIndex = 19;
			this->Tooltip->SetToolTip(this->DeleteFileBtn, L"Remove File from Current File Set (Right Click Permanent Delete)");
			this->DeleteFileBtn->Click += gcnew System::EventHandler(this, &Form1::DeleteFileBtn_Click);
			this->DeleteFileBtn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::DeleteFileBtn_MouseClick);
			this->DeleteFileBtn->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::DeleteFileBtn_MouseUp);
			// 
			// SingleOutBtn
			// 
			this->SingleOutBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SingleOutBtn.BackgroundImage")));
			this->SingleOutBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->SingleOutBtn->ContextMenuStrip = this->ImageFingerPointContext;
			this->SingleOutBtn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->SingleOutBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SingleOutBtn->Location = System::Drawing::Point(183, 56);
			this->SingleOutBtn->Name = L"SingleOutBtn";
			this->SingleOutBtn->Size = System::Drawing::Size(48, 37);
			this->SingleOutBtn->TabIndex = 21;
			this->Tooltip->SetToolTip(this->SingleOutBtn, L"Single Out Current Image (Right Click More Options)");
			this->SingleOutBtn->Click += gcnew System::EventHandler(this, &Form1::SingleOutBtn_Click);
			// 
			// ImageFingerPointContext
			// 
			this->ImageFingerPointContext->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ImageFingerRmvToHere,
					this->ImageFingerRmvFromHere, this->ImageFingerRecToHere, this->ImageFingerRecFromHere, this->ImageFingerSortBy
			});
			this->ImageFingerPointContext->Name = L"ImageFingerPointContext";
			this->ImageFingerPointContext->ShowImageMargin = false;
			this->ImageFingerPointContext->Size = System::Drawing::Size(169, 114);
			// 
			// ImageFingerRmvToHere
			// 
			this->ImageFingerRmvToHere->Name = L"ImageFingerRmvToHere";
			this->ImageFingerRmvToHere->Size = System::Drawing::Size(168, 22);
			this->ImageFingerRmvToHere->Text = L"Remove To Here";
			this->ImageFingerRmvToHere->ToolTipText = L"Remove All Image(s) in Set TO Here";
			this->ImageFingerRmvToHere->Click += gcnew System::EventHandler(this, &Form1::ImageFingerRmvToHere_Click);
			// 
			// ImageFingerRmvFromHere
			// 
			this->ImageFingerRmvFromHere->Name = L"ImageFingerRmvFromHere";
			this->ImageFingerRmvFromHere->Size = System::Drawing::Size(168, 22);
			this->ImageFingerRmvFromHere->Text = L"Remove From Here";
			this->ImageFingerRmvFromHere->ToolTipText = L"Remove All Image(s) in Set FROM Here";
			this->ImageFingerRmvFromHere->Click += gcnew System::EventHandler(this, &Form1::ImageFingerRmvFromHere_Click);
			// 
			// ImageFingerRecToHere
			// 
			this->ImageFingerRecToHere->Name = L"ImageFingerRecToHere";
			this->ImageFingerRecToHere->Size = System::Drawing::Size(168, 22);
			this->ImageFingerRecToHere->Text = L"Recycle Bin To Here";
			this->ImageFingerRecToHere->Click += gcnew System::EventHandler(this, &Form1::ImageFingerRecToHere_Click);
			// 
			// ImageFingerRecFromHere
			// 
			this->ImageFingerRecFromHere->Name = L"ImageFingerRecFromHere";
			this->ImageFingerRecFromHere->Size = System::Drawing::Size(168, 22);
			this->ImageFingerRecFromHere->Text = L"Recycle Bin From Here";
			this->ImageFingerRecFromHere->Click += gcnew System::EventHandler(this, &Form1::ImageFingerRecFromHere_Click);
			// 
			// ImageFingerSortBy
			// 
			this->ImageFingerSortBy->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ImageFingerSortFileName,
					this->toolStripSeparator23, this->ImageFingerSortKeyValue, this->ImageFingerSortKeyValueTxt
			});
			this->ImageFingerSortBy->Name = L"ImageFingerSortBy";
			this->ImageFingerSortBy->Size = System::Drawing::Size(168, 22);
			this->ImageFingerSortBy->Text = L"Sort By:";
			// 
			// ImageFingerSortFileName
			// 
			this->ImageFingerSortFileName->Name = L"ImageFingerSortFileName";
			this->ImageFingerSortFileName->Size = System::Drawing::Size(165, 22);
			this->ImageFingerSortFileName->Text = L"File Name";
			this->ImageFingerSortFileName->Click += gcnew System::EventHandler(this, &Form1::ImageFingerSortFileName_Click);
			// 
			// toolStripSeparator23
			// 
			this->toolStripSeparator23->Name = L"toolStripSeparator23";
			this->toolStripSeparator23->Size = System::Drawing::Size(162, 6);
			// 
			// ImageFingerSortKeyValue
			// 
			this->ImageFingerSortKeyValue->Name = L"ImageFingerSortKeyValue";
			this->ImageFingerSortKeyValue->Size = System::Drawing::Size(165, 22);
			this->ImageFingerSortKeyValue->Text = L"Header Key Value";
			this->ImageFingerSortKeyValue->Click += gcnew System::EventHandler(this, &Form1::ImageFingerSortKeyValue_Click);
			// 
			// ImageFingerSortKeyValueTxt
			// 
			this->ImageFingerSortKeyValueTxt->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ImageFingerSortKeyValueTxt->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->ImageFingerSortKeyValueTxt->MaxLength = 8;
			this->ImageFingerSortKeyValueTxt->Name = L"ImageFingerSortKeyValueTxt";
			this->ImageFingerSortKeyValueTxt->Size = System::Drawing::Size(100, 23);
			this->ImageFingerSortKeyValueTxt->Text = L"TIME-OBS";
			this->ImageFingerSortKeyValueTxt->TextBoxTextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// HalfWidthXUpD
			// 
			this->HalfWidthXUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HalfWidthXUpD->Location = System::Drawing::Point(82, 17);
			this->HalfWidthXUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->HalfWidthXUpD->Name = L"HalfWidthXUpD";
			this->HalfWidthXUpD->Size = System::Drawing::Size(49, 20);
			this->HalfWidthXUpD->TabIndex = 20;
			this->HalfWidthXUpD->Tag = L"zz";
			this->HalfWidthXUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->HalfWidthXUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->HalfWidthXUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::HalfWidthXUpD_ValueChanged);
			// 
			// SubImageBtn
			// 
			this->SubImageBtn->Checked = true;
			this->SubImageBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageBtn->Location = System::Drawing::Point(1156, 558);
			this->SubImageBtn->Name = L"SubImageBtn";
			this->SubImageBtn->Size = System::Drawing::Size(85, 20);
			this->SubImageBtn->TabIndex = 0;
			this->SubImageBtn->TabStop = true;
			this->SubImageBtn->Text = L"Sub Image";
			this->SubImageBtn->Visible = false;
			// 
			// SubImagePanel
			// 
			this->SubImagePanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SubImagePanel->Controls->Add(this->SubImageDecTxt);
			this->SubImagePanel->Controls->Add(this->SubImTrackPSChck);
			this->SubImagePanel->Controls->Add(this->SubImageRATxt);
			this->SubImagePanel->Controls->Add(this->SubImageYTxt);
			this->SubImagePanel->Controls->Add(this->SubImageXTxt);
			this->SubImagePanel->Controls->Add(this->SubImageSizeTxt);
			this->SubImagePanel->Controls->Add(this->CutSubImBtn2);
			this->SubImagePanel->Controls->Add(this->EqualHWChck);
			this->SubImagePanel->Controls->Add(this->HalfWidthYUpD);
			this->SubImagePanel->Controls->Add(this->label12);
			this->SubImagePanel->Controls->Add(this->SubImageSumTxt);
			this->SubImagePanel->Controls->Add(this->SubImageSumStatic);
			this->SubImagePanel->Controls->Add(this->SubImageYStatic);
			this->SubImagePanel->Controls->Add(this->SubImageXStatic);
			this->SubImagePanel->Controls->Add(this->SubImageMinTxt);
			this->SubImagePanel->Controls->Add(this->SubImageMaxTxt);
			this->SubImagePanel->Controls->Add(this->SubImageMeanTxt);
			this->SubImagePanel->Controls->Add(this->SubImageMedianTxt);
			this->SubImagePanel->Controls->Add(this->SubImageStdTxt);
			this->SubImagePanel->Controls->Add(this->SubImageMedianStatic);
			this->SubImagePanel->Controls->Add(this->SubImageMeanStatic);
			this->SubImagePanel->Controls->Add(this->SubImageStdvStatic);
			this->SubImagePanel->Controls->Add(this->SubImageMinStatic);
			this->SubImagePanel->Controls->Add(this->SubImageMaxStatic);
			this->SubImagePanel->Controls->Add(this->ScaleContrastChck);
			this->SubImagePanel->Controls->Add(this->HalfWidthXUpD);
			this->SubImagePanel->Controls->Add(this->HalfWidthStatic);
			this->SubImagePanel->Enabled = false;
			this->SubImagePanel->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->SubImagePanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImagePanel->Location = System::Drawing::Point(1150, 583);
			this->SubImagePanel->Name = L"SubImagePanel";
			this->SubImagePanel->Size = System::Drawing::Size(137, 270);
			this->SubImagePanel->TabIndex = 36;
			this->SubImagePanel->TabStop = false;
			this->SubImagePanel->Text = L"Sub Image ROI";
			this->Tooltip->SetToolTip(this->SubImagePanel, L"Region of Interest");
			this->SubImagePanel->MouseHover += gcnew System::EventHandler(this, &Form1::SubImagePanel_MouseHover);
			// 
			// SubImageDecTxt
			// 
			this->SubImageDecTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageDecTxt->Location = System::Drawing::Point(70, 162);
			this->SubImageDecTxt->Name = L"SubImageDecTxt";
			this->SubImageDecTxt->Size = System::Drawing::Size(61, 15);
			this->SubImageDecTxt->TabIndex = 61;
			this->SubImageDecTxt->Text = L"0";
			this->SubImageDecTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageDecTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageRATxt_MouseClick);
			this->SubImageDecTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageDecTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImTrackPSChck
			// 
			this->SubImTrackPSChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImTrackPSChck->Location = System::Drawing::Point(8, 108);
			this->SubImTrackPSChck->Name = L"SubImTrackPSChck";
			this->SubImTrackPSChck->Size = System::Drawing::Size(114, 19);
			this->SubImTrackPSChck->TabIndex = 58;
			this->SubImTrackPSChck->Text = L"Track Source";
			this->SubImTrackPSChck->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->Tooltip->SetToolTip(this->SubImTrackPSChck, L"Track a point source with the subwindow while scanning.");
			// 
			// SubImageRATxt
			// 
			this->SubImageRATxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageRATxt->Location = System::Drawing::Point(9, 162);
			this->SubImageRATxt->Name = L"SubImageRATxt";
			this->SubImageRATxt->Size = System::Drawing::Size(59, 15);
			this->SubImageRATxt->TabIndex = 60;
			this->SubImageRATxt->Text = L"0";
			this->SubImageRATxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageRATxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageRATxt_MouseClick);
			this->SubImageRATxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageRATxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageYTxt
			// 
			this->SubImageYTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageYTxt->Location = System::Drawing::Point(85, 149);
			this->SubImageYTxt->Name = L"SubImageYTxt";
			this->SubImageYTxt->Size = System::Drawing::Size(46, 15);
			this->SubImageYTxt->TabIndex = 35;
			this->SubImageYTxt->Text = L"0";
			this->SubImageYTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// SubImageXTxt
			// 
			this->SubImageXTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageXTxt->Location = System::Drawing::Point(22, 149);
			this->SubImageXTxt->Name = L"SubImageXTxt";
			this->SubImageXTxt->Size = System::Drawing::Size(46, 15);
			this->SubImageXTxt->TabIndex = 34;
			this->SubImageXTxt->Text = L"0";
			this->SubImageXTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// SubImageSizeTxt
			// 
			this->SubImageSizeTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageSizeTxt->Location = System::Drawing::Point(6, 135);
			this->SubImageSizeTxt->Name = L"SubImageSizeTxt";
			this->SubImageSizeTxt->Size = System::Drawing::Size(125, 14);
			this->SubImageSizeTxt->TabIndex = 55;
			this->SubImageSizeTxt->Text = L"Size:";
			// 
			// CutSubImBtn2
			// 
			this->CutSubImBtn2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CutSubImBtn2.BackgroundImage")));
			this->CutSubImBtn2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->CutSubImBtn2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CutSubImBtn2->Location = System::Drawing::Point(6, 57);
			this->CutSubImBtn2->Name = L"CutSubImBtn2";
			this->CutSubImBtn2->Size = System::Drawing::Size(29, 29);
			this->CutSubImBtn2->TabIndex = 54;
			this->Tooltip->SetToolTip(this->CutSubImBtn2, L"Cut out selected region of interest (cursor box).");
			this->CutSubImBtn2->UseVisualStyleBackColor = true;
			this->CutSubImBtn2->Click += gcnew System::EventHandler(this, &Form1::CutSubImBtn_Click);
			// 
			// EqualHWChck
			// 
			this->EqualHWChck->Checked = true;
			this->EqualHWChck->CheckState = System::Windows::Forms::CheckState::Checked;
			this->EqualHWChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EqualHWChck->Location = System::Drawing::Point(78, 63);
			this->EqualHWChck->Name = L"EqualHWChck";
			this->EqualHWChck->Size = System::Drawing::Size(53, 19);
			this->EqualHWChck->TabIndex = 49;
			this->EqualHWChck->Text = L"Equal";
			this->EqualHWChck->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->EqualHWChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::EqualHWChck_CheckedChanged);
			// 
			// HalfWidthYUpD
			// 
			this->HalfWidthYUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HalfWidthYUpD->Location = System::Drawing::Point(82, 37);
			this->HalfWidthYUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->HalfWidthYUpD->Name = L"HalfWidthYUpD";
			this->HalfWidthYUpD->Size = System::Drawing::Size(49, 20);
			this->HalfWidthYUpD->TabIndex = 48;
			this->HalfWidthYUpD->Tag = L"zz";
			this->HalfWidthYUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->HalfWidthYUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->HalfWidthYUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::HalfWidthYUpD_ValueChanged);
			// 
			// label12
			// 
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(5, 37);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(71, 20);
			this->label12->TabIndex = 47;
			this->label12->Text = L"Half Width Y";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// SubImageSumTxt
			// 
			this->SubImageSumTxt->AutoEllipsis = true;
			this->SubImageSumTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageSumTxt->Location = System::Drawing::Point(61, 177);
			this->SubImageSumTxt->Name = L"SubImageSumTxt";
			this->SubImageSumTxt->Size = System::Drawing::Size(70, 15);
			this->SubImageSumTxt->TabIndex = 46;
			this->SubImageSumTxt->Tag = L"Sum";
			this->SubImageSumTxt->Text = L"0";
			this->SubImageSumTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageSumTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageSumTxt_MouseClick);
			this->SubImageSumTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageSumTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageSumStatic
			// 
			this->SubImageSumStatic->ContextMenuStrip = this->StatsContxt;
			this->SubImageSumStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageSumStatic->Location = System::Drawing::Point(6, 176);
			this->SubImageSumStatic->Name = L"SubImageSumStatic";
			this->SubImageSumStatic->Size = System::Drawing::Size(39, 15);
			this->SubImageSumStatic->TabIndex = 45;
			this->SubImageSumStatic->Text = L"Sum:";
			this->SubImageSumStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageSumStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// StatsContxt
			// 
			this->StatsContxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->StatsCopyClipBrdCntxt,
					this->StatsWriteFITSCntxt
			});
			this->StatsContxt->Name = L"StatsContxt";
			this->StatsContxt->Size = System::Drawing::Size(193, 48);
			// 
			// StatsCopyClipBrdCntxt
			// 
			this->StatsCopyClipBrdCntxt->Name = L"StatsCopyClipBrdCntxt";
			this->StatsCopyClipBrdCntxt->Size = System::Drawing::Size(192, 22);
			this->StatsCopyClipBrdCntxt->Text = L"Copy List to Clipboard";
			this->StatsCopyClipBrdCntxt->Click += gcnew System::EventHandler(this, &Form1::StatsCopyClipBrdCntxt_Click);
			// 
			// StatsWriteFITSCntxt
			// 
			this->StatsWriteFITSCntxt->Enabled = false;
			this->StatsWriteFITSCntxt->Name = L"StatsWriteFITSCntxt";
			this->StatsWriteFITSCntxt->Size = System::Drawing::Size(192, 22);
			this->StatsWriteFITSCntxt->Text = L"Write List to FITS File";
			// 
			// SubImageYStatic
			// 
			this->SubImageYStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageYStatic->Location = System::Drawing::Point(71, 150);
			this->SubImageYStatic->Name = L"SubImageYStatic";
			this->SubImageYStatic->Size = System::Drawing::Size(17, 15);
			this->SubImageYStatic->TabIndex = 33;
			this->SubImageYStatic->Text = L"Y:";
			// 
			// SubImageXStatic
			// 
			this->SubImageXStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageXStatic->Location = System::Drawing::Point(6, 150);
			this->SubImageXStatic->Name = L"SubImageXStatic";
			this->SubImageXStatic->Size = System::Drawing::Size(17, 15);
			this->SubImageXStatic->TabIndex = 32;
			this->SubImageXStatic->Text = L"X:";
			// 
			// SubImageMinTxt
			// 
			this->SubImageMinTxt->AutoEllipsis = true;
			this->SubImageMinTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageMinTxt->Location = System::Drawing::Point(61, 192);
			this->SubImageMinTxt->Name = L"SubImageMinTxt";
			this->SubImageMinTxt->Size = System::Drawing::Size(70, 15);
			this->SubImageMinTxt->TabIndex = 31;
			this->SubImageMinTxt->Tag = L"Min";
			this->SubImageMinTxt->Text = L"0";
			this->SubImageMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageMinTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageMinTxt_MouseClick);
			this->SubImageMinTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMinTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMaxTxt
			// 
			this->SubImageMaxTxt->AutoEllipsis = true;
			this->SubImageMaxTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageMaxTxt->Location = System::Drawing::Point(61, 207);
			this->SubImageMaxTxt->Name = L"SubImageMaxTxt";
			this->SubImageMaxTxt->Size = System::Drawing::Size(70, 15);
			this->SubImageMaxTxt->TabIndex = 30;
			this->SubImageMaxTxt->Tag = L"Max";
			this->SubImageMaxTxt->Text = L"0";
			this->SubImageMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageMaxTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageMaxTxt_MouseClick);
			this->SubImageMaxTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMaxTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMeanTxt
			// 
			this->SubImageMeanTxt->AutoEllipsis = true;
			this->SubImageMeanTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageMeanTxt->Location = System::Drawing::Point(61, 237);
			this->SubImageMeanTxt->Name = L"SubImageMeanTxt";
			this->SubImageMeanTxt->Size = System::Drawing::Size(70, 15);
			this->SubImageMeanTxt->TabIndex = 29;
			this->SubImageMeanTxt->Tag = L"Mean";
			this->SubImageMeanTxt->Text = L"0";
			this->SubImageMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageMeanTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageMeanTxt_MouseClick);
			this->SubImageMeanTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMeanTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMedianTxt
			// 
			this->SubImageMedianTxt->AutoEllipsis = true;
			this->SubImageMedianTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageMedianTxt->Location = System::Drawing::Point(67, 222);
			this->SubImageMedianTxt->Name = L"SubImageMedianTxt";
			this->SubImageMedianTxt->Size = System::Drawing::Size(64, 15);
			this->SubImageMedianTxt->TabIndex = 28;
			this->SubImageMedianTxt->Tag = L"Median";
			this->SubImageMedianTxt->Text = L"0";
			this->SubImageMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageMedianTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageMedianTxt_MouseClick);
			this->SubImageMedianTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMedianTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageStdTxt
			// 
			this->SubImageStdTxt->AutoEllipsis = true;
			this->SubImageStdTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImageStdTxt->Location = System::Drawing::Point(61, 252);
			this->SubImageStdTxt->Name = L"SubImageStdTxt";
			this->SubImageStdTxt->Size = System::Drawing::Size(70, 15);
			this->SubImageStdTxt->TabIndex = 27;
			this->SubImageStdTxt->Tag = L"Stdv";
			this->SubImageStdTxt->Text = L"0";
			this->SubImageStdTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->SubImageStdTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageStdTxt_MouseClick);
			this->SubImageStdTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageStdTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMedianStatic
			// 
			this->SubImageMedianStatic->ContextMenuStrip = this->StatsContxt;
			this->SubImageMedianStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageMedianStatic->Location = System::Drawing::Point(6, 221);
			this->SubImageMedianStatic->Name = L"SubImageMedianStatic";
			this->SubImageMedianStatic->Size = System::Drawing::Size(55, 15);
			this->SubImageMedianStatic->TabIndex = 24;
			this->SubImageMedianStatic->Text = L"Median:";
			this->SubImageMedianStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMedianStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMeanStatic
			// 
			this->SubImageMeanStatic->ContextMenuStrip = this->StatsContxt;
			this->SubImageMeanStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageMeanStatic->Location = System::Drawing::Point(6, 236);
			this->SubImageMeanStatic->Name = L"SubImageMeanStatic";
			this->SubImageMeanStatic->Size = System::Drawing::Size(45, 15);
			this->SubImageMeanStatic->TabIndex = 26;
			this->SubImageMeanStatic->Text = L"Mean:";
			this->SubImageMeanStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMeanStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageStdvStatic
			// 
			this->SubImageStdvStatic->ContextMenuStrip = this->StatsContxt;
			this->SubImageStdvStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageStdvStatic->Location = System::Drawing::Point(6, 251);
			this->SubImageStdvStatic->Name = L"SubImageStdvStatic";
			this->SubImageStdvStatic->Size = System::Drawing::Size(45, 15);
			this->SubImageStdvStatic->TabIndex = 25;
			this->SubImageStdvStatic->Text = L"Stdv:";
			this->SubImageStdvStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageStdvStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMinStatic
			// 
			this->SubImageMinStatic->ContextMenuStrip = this->StatsContxt;
			this->SubImageMinStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageMinStatic->Location = System::Drawing::Point(6, 191);
			this->SubImageMinStatic->Name = L"SubImageMinStatic";
			this->SubImageMinStatic->Size = System::Drawing::Size(30, 15);
			this->SubImageMinStatic->TabIndex = 22;
			this->SubImageMinStatic->Text = L"Min:";
			this->SubImageMinStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMinStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// SubImageMaxStatic
			// 
			this->SubImageMaxStatic->ContextMenuStrip = this->StatsContxt;
			this->SubImageMaxStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SubImageMaxStatic->Location = System::Drawing::Point(6, 206);
			this->SubImageMaxStatic->Name = L"SubImageMaxStatic";
			this->SubImageMaxStatic->Size = System::Drawing::Size(30, 15);
			this->SubImageMaxStatic->TabIndex = 23;
			this->SubImageMaxStatic->Text = L"Max:";
			this->SubImageMaxStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->SubImageMaxStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ScaleContrastChck
			// 
			this->ScaleContrastChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ScaleContrastChck->Location = System::Drawing::Point(8, 88);
			this->ScaleContrastChck->Name = L"ScaleContrastChck";
			this->ScaleContrastChck->Size = System::Drawing::Size(114, 19);
			this->ScaleContrastChck->TabIndex = 21;
			this->ScaleContrastChck->Text = L"Match Contrast";
			this->ScaleContrastChck->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->Tooltip->SetToolTip(this->ScaleContrastChck, L"Default is Linear Max/Min of Sub Image.  Check to Match Parent Image Scaling.");
			this->ScaleContrastChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::ScaleContrastChck_CheckedChanged);
			// 
			// HalfWidthStatic
			// 
			this->HalfWidthStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HalfWidthStatic->Location = System::Drawing::Point(5, 17);
			this->HalfWidthStatic->Name = L"HalfWidthStatic";
			this->HalfWidthStatic->Size = System::Drawing::Size(71, 20);
			this->HalfWidthStatic->TabIndex = 1;
			this->HalfWidthStatic->Text = L"Half Width X";
			this->HalfWidthStatic->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// BlinkTimer
			// 
			this->BlinkTimer->Interval = 200;
			this->BlinkTimer->Tick += gcnew System::EventHandler(this, &Form1::BlinkTimer_Tick);
			// 
			// FileInfoPanel
			// 
			this->FileInfoPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->FileInfoPanel->BackColor = System::Drawing::Color::LightGray;
			this->FileInfoPanel->Controls->Add(this->ImageSumTxt);
			this->FileInfoPanel->Controls->Add(this->ImageSumStatic);
			this->FileInfoPanel->Controls->Add(this->ImageSizeTxt);
			this->FileInfoPanel->Controls->Add(this->ImageSizeStatic);
			this->FileInfoPanel->Controls->Add(this->InfoTxt4);
			this->FileInfoPanel->Controls->Add(this->InfoStatic4);
			this->FileInfoPanel->Controls->Add(this->ImageMedianTxt);
			this->FileInfoPanel->Controls->Add(this->ImageMinStatic);
			this->FileInfoPanel->Controls->Add(this->InfoTxt5);
			this->FileInfoPanel->Controls->Add(this->InfoStatic1);
			this->FileInfoPanel->Controls->Add(this->InfoTxt1);
			this->FileInfoPanel->Controls->Add(this->InfoStatic3);
			this->FileInfoPanel->Controls->Add(this->InfoTxt2);
			this->FileInfoPanel->Controls->Add(this->InfoTxt3);
			this->FileInfoPanel->Controls->Add(this->InfoStatic2);
			this->FileInfoPanel->Controls->Add(this->FileNameStatic);
			this->FileInfoPanel->Controls->Add(this->InfoStatic5);
			this->FileInfoPanel->Controls->Add(this->ImageMaxStatic);
			this->FileInfoPanel->Controls->Add(this->ImageMedianStatic);
			this->FileInfoPanel->Controls->Add(this->ImageMeanStatic);
			this->FileInfoPanel->Controls->Add(this->ImageStdvStatic);
			this->FileInfoPanel->Controls->Add(this->ImageMinTxt);
			this->FileInfoPanel->Controls->Add(this->ImageMeanTxt);
			this->FileInfoPanel->Controls->Add(this->ImageStdTxt);
			this->FileInfoPanel->Controls->Add(this->ImageMaxTxt);
			this->FileInfoPanel->Controls->Add(this->FileNameTxt);
			this->FileInfoPanel->Controls->Add(this->FileDirectoryTxt);
			this->FileInfoPanel->Controls->Add(this->FileDirectoryStatic);
			this->FileInfoPanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FileInfoPanel->Location = System::Drawing::Point(855, 359);
			this->FileInfoPanel->Name = L"FileInfoPanel";
			this->FileInfoPanel->Size = System::Drawing::Size(235, 196);
			this->FileInfoPanel->TabIndex = 34;
			this->FileInfoPanel->TabStop = false;
			this->FileInfoPanel->Text = L"File/Image Information";
			this->FileInfoPanel->MouseHover += gcnew System::EventHandler(this, &Form1::FileInfoPanel_MouseHover);
			// 
			// ImageSumTxt
			// 
			this->ImageSumTxt->AutoEllipsis = true;
			this->ImageSumTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageSumTxt->Location = System::Drawing::Point(34, 146);
			this->ImageSumTxt->Name = L"ImageSumTxt";
			this->ImageSumTxt->Size = System::Drawing::Size(75, 14);
			this->ImageSumTxt->TabIndex = 45;
			this->ImageSumTxt->Text = L"0";
			this->ImageSumTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageSumTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageSumTxt_MouseClick);
			this->ImageSumTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageSumTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageSumStatic
			// 
			this->ImageSumStatic->ContextMenuStrip = this->StatsContxt;
			this->ImageSumStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageSumStatic->Location = System::Drawing::Point(5, 146);
			this->ImageSumStatic->Name = L"ImageSumStatic";
			this->ImageSumStatic->Size = System::Drawing::Size(40, 14);
			this->ImageSumStatic->TabIndex = 45;
			this->ImageSumStatic->Text = L"Sum:";
			this->ImageSumStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageSumStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageSizeTxt
			// 
			this->ImageSizeTxt->ContextMenuStrip = this->SIZECntxtMenu;
			this->ImageSizeTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageSizeTxt->Location = System::Drawing::Point(154, 125);
			this->ImageSizeTxt->Name = L"ImageSizeTxt";
			this->ImageSizeTxt->Size = System::Drawing::Size(75, 14);
			this->ImageSizeTxt->TabIndex = 45;
			this->ImageSizeTxt->Text = L"0x0";
			this->ImageSizeTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageSizeTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSizeTxt_MouseEnter);
			this->ImageSizeTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSizeTxt_MouseLeave);
			// 
			// SIZECntxtMenu
			// 
			this->SIZECntxtMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->SIZECntxtEditImgDim });
			this->SIZECntxtMenu->Name = L"SIZECntxtMenu";
			this->SIZECntxtMenu->Size = System::Drawing::Size(196, 26);
			this->SIZECntxtMenu->Opened += gcnew System::EventHandler(this, &Form1::SIZECntxtMenu_Opened);
			// 
			// SIZECntxtEditImgDim
			// 
			this->SIZECntxtEditImgDim->DoubleClickEnabled = true;
			this->SIZECntxtEditImgDim->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->toolStripMenuItem6,
					this->SIZECntxtEditTxtX, this->toolStripSeparator22, this->toolStripMenuItem7, this->SIZECntxtEditTxtY, this->Sep, this->SIZECntxtBatchChck
			});
			this->SIZECntxtEditImgDim->Name = L"SIZECntxtEditImgDim";
			this->SIZECntxtEditImgDim->Size = System::Drawing::Size(195, 22);
			this->SIZECntxtEditImgDim->Text = L"Edit Image Dimensions";
			this->SIZECntxtEditImgDim->DoubleClick += gcnew System::EventHandler(this, &Form1::SIZECntxtEditImgDim_DoubleClick);
			// 
			// toolStripMenuItem6
			// 
			this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
			this->toolStripMenuItem6->Size = System::Drawing::Size(160, 22);
			this->toolStripMenuItem6->Text = L"X";
			// 
			// SIZECntxtEditTxtX
			// 
			this->SIZECntxtEditTxtX->BackColor = System::Drawing::Color::Gainsboro;
			this->SIZECntxtEditTxtX->Name = L"SIZECntxtEditTxtX";
			this->SIZECntxtEditTxtX->Size = System::Drawing::Size(100, 23);
			this->SIZECntxtEditTxtX->ToolTipText = L"Example: 5:21. Leave blank for no change.";
			// 
			// toolStripSeparator22
			// 
			this->toolStripSeparator22->Name = L"toolStripSeparator22";
			this->toolStripSeparator22->Size = System::Drawing::Size(157, 6);
			// 
			// toolStripMenuItem7
			// 
			this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
			this->toolStripMenuItem7->Size = System::Drawing::Size(160, 22);
			this->toolStripMenuItem7->Text = L"Y";
			// 
			// SIZECntxtEditTxtY
			// 
			this->SIZECntxtEditTxtY->BackColor = System::Drawing::Color::Gainsboro;
			this->SIZECntxtEditTxtY->Name = L"SIZECntxtEditTxtY";
			this->SIZECntxtEditTxtY->Size = System::Drawing::Size(100, 23);
			this->SIZECntxtEditTxtY->ToolTipText = L"Example: 5:21. Leave blank for no change.";
			// 
			// Sep
			// 
			this->Sep->Name = L"Sep";
			this->Sep->Size = System::Drawing::Size(157, 6);
			// 
			// SIZECntxtBatchChck
			// 
			this->SIZECntxtBatchChck->CheckOnClick = true;
			this->SIZECntxtBatchChck->Name = L"SIZECntxtBatchChck";
			this->SIZECntxtBatchChck->Size = System::Drawing::Size(160, 22);
			this->SIZECntxtBatchChck->Text = L"Batch";
			this->SIZECntxtBatchChck->Click += gcnew System::EventHandler(this, &Form1::SIZECntxtBatchChck_Click);
			// 
			// ImageSizeStatic
			// 
			this->ImageSizeStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ImageSizeStatic->Location = System::Drawing::Point(5, 126);
			this->ImageSizeStatic->Name = L"ImageSizeStatic";
			this->ImageSizeStatic->Size = System::Drawing::Size(55, 14);
			this->ImageSizeStatic->TabIndex = 24;
			this->ImageSizeStatic->Text = L"SIZE:";
			// 
			// InfoTxt4
			// 
			this->InfoTxt4->AutoEllipsis = true;
			this->InfoTxt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoTxt4->Location = System::Drawing::Point(77, 95);
			this->InfoTxt4->Name = L"InfoTxt4";
			this->InfoTxt4->Size = System::Drawing::Size(154, 15);
			this->InfoTxt4->TabIndex = 23;
			this->InfoTxt4->Text = L"NA";
			this->InfoTxt4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->InfoTxt4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoTxt1_MouseClick);
			this->InfoTxt4->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseEnter);
			this->InfoTxt4->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseLeave);
			// 
			// InfoStatic4
			// 
			this->InfoStatic4->ContextMenuStrip = this->InfoCntxt;
			this->InfoStatic4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoStatic4->Location = System::Drawing::Point(5, 95);
			this->InfoStatic4->Name = L"InfoStatic4";
			this->InfoStatic4->Size = System::Drawing::Size(68, 15);
			this->InfoStatic4->TabIndex = 22;
			this->InfoStatic4->Text = L"CAMTEMP:";
			this->Tooltip->SetToolTip(this->InfoStatic4, L"Right click to select header key");
			this->InfoStatic4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoStatic1_MouseDoubleClick);
			this->InfoStatic4->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseEnter);
			this->InfoStatic4->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseLeave);
			// 
			// InfoCntxt
			// 
			this->InfoCntxt->Name = L"contextMenuStrip1";
			this->InfoCntxt->ShowImageMargin = false;
			this->InfoCntxt->Size = System::Drawing::Size(36, 4);
			// 
			// ImageMedianTxt
			// 
			this->ImageMedianTxt->AutoEllipsis = true;
			this->ImageMedianTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMedianTxt->Location = System::Drawing::Point(154, 146);
			this->ImageMedianTxt->Name = L"ImageMedianTxt";
			this->ImageMedianTxt->Size = System::Drawing::Size(75, 14);
			this->ImageMedianTxt->TabIndex = 21;
			this->ImageMedianTxt->Text = L"0";
			this->ImageMedianTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageMedianTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageMedianTxt_MouseClick);
			this->ImageMedianTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMedianTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageMinStatic
			// 
			this->ImageMinStatic->ContextMenuStrip = this->StatsContxt;
			this->ImageMinStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMinStatic->Location = System::Drawing::Point(5, 160);
			this->ImageMinStatic->Name = L"ImageMinStatic";
			this->ImageMinStatic->Size = System::Drawing::Size(30, 14);
			this->ImageMinStatic->TabIndex = 17;
			this->ImageMinStatic->Text = L"Min:";
			this->ImageMinStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMinStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// InfoTxt5
			// 
			this->InfoTxt5->AutoEllipsis = true;
			this->InfoTxt5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoTxt5->Location = System::Drawing::Point(77, 111);
			this->InfoTxt5->Name = L"InfoTxt5";
			this->InfoTxt5->Size = System::Drawing::Size(154, 15);
			this->InfoTxt5->TabIndex = 14;
			this->InfoTxt5->Text = L"NA";
			this->InfoTxt5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->InfoTxt5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoTxt1_MouseClick);
			this->InfoTxt5->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseEnter);
			this->InfoTxt5->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseLeave);
			// 
			// InfoStatic1
			// 
			this->InfoStatic1->ContextMenuStrip = this->InfoCntxt;
			this->InfoStatic1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoStatic1->Location = System::Drawing::Point(5, 46);
			this->InfoStatic1->Name = L"InfoStatic1";
			this->InfoStatic1->Size = System::Drawing::Size(71, 15);
			this->InfoStatic1->TabIndex = 15;
			this->InfoStatic1->Text = L"DATE-OBS:";
			this->Tooltip->SetToolTip(this->InfoStatic1, L"Right click to select header key");
			this->InfoStatic1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoStatic1_MouseDoubleClick);
			this->InfoStatic1->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseEnter);
			this->InfoStatic1->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseLeave);
			// 
			// InfoTxt1
			// 
			this->InfoTxt1->AutoEllipsis = true;
			this->InfoTxt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoTxt1->Location = System::Drawing::Point(77, 47);
			this->InfoTxt1->Name = L"InfoTxt1";
			this->InfoTxt1->Size = System::Drawing::Size(154, 15);
			this->InfoTxt1->TabIndex = 16;
			this->InfoTxt1->Text = L"NA";
			this->InfoTxt1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->InfoTxt1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoTxt1_MouseClick);
			this->InfoTxt1->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseEnter);
			this->InfoTxt1->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseLeave);
			// 
			// InfoStatic3
			// 
			this->InfoStatic3->ContextMenuStrip = this->InfoCntxt;
			this->InfoStatic3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoStatic3->Location = System::Drawing::Point(5, 79);
			this->InfoStatic3->Name = L"InfoStatic3";
			this->InfoStatic3->Size = System::Drawing::Size(68, 15);
			this->InfoStatic3->TabIndex = 10;
			this->InfoStatic3->Text = L"EXPTIME:";
			this->Tooltip->SetToolTip(this->InfoStatic3, L"Right click to select header key");
			this->InfoStatic3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoStatic1_MouseDoubleClick);
			this->InfoStatic3->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseEnter);
			this->InfoStatic3->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseLeave);
			// 
			// InfoTxt2
			// 
			this->InfoTxt2->AutoEllipsis = true;
			this->InfoTxt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoTxt2->Location = System::Drawing::Point(77, 63);
			this->InfoTxt2->Name = L"InfoTxt2";
			this->InfoTxt2->Size = System::Drawing::Size(154, 15);
			this->InfoTxt2->TabIndex = 12;
			this->InfoTxt2->Text = L"NA";
			this->InfoTxt2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->InfoTxt2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoTxt1_MouseClick);
			this->InfoTxt2->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseEnter);
			this->InfoTxt2->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseLeave);
			// 
			// InfoTxt3
			// 
			this->InfoTxt3->AutoEllipsis = true;
			this->InfoTxt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoTxt3->Location = System::Drawing::Point(77, 79);
			this->InfoTxt3->Name = L"InfoTxt3";
			this->InfoTxt3->Size = System::Drawing::Size(154, 15);
			this->InfoTxt3->TabIndex = 13;
			this->InfoTxt3->Text = L"NA";
			this->InfoTxt3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->InfoTxt3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoTxt1_MouseClick);
			this->InfoTxt3->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseEnter);
			this->InfoTxt3->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoTxt1_MouseLeave);
			// 
			// InfoStatic2
			// 
			this->InfoStatic2->ContextMenuStrip = this->InfoCntxt;
			this->InfoStatic2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoStatic2->Location = System::Drawing::Point(5, 63);
			this->InfoStatic2->Name = L"InfoStatic2";
			this->InfoStatic2->Size = System::Drawing::Size(68, 15);
			this->InfoStatic2->TabIndex = 10;
			this->InfoStatic2->Text = L"OBJECT:";
			this->Tooltip->SetToolTip(this->InfoStatic2, L"Right click to select header key");
			this->InfoStatic2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoStatic1_MouseDoubleClick);
			this->InfoStatic2->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseEnter);
			this->InfoStatic2->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseLeave);
			// 
			// FileNameStatic
			// 
			this->FileNameStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->FileNameStatic->Location = System::Drawing::Point(5, 15);
			this->FileNameStatic->Name = L"FileNameStatic";
			this->FileNameStatic->Size = System::Drawing::Size(60, 15);
			this->FileNameStatic->TabIndex = 0;
			this->FileNameStatic->Text = L"File Name:";
			this->FileNameStatic->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InfoStatic5
			// 
			this->InfoStatic5->ContextMenuStrip = this->InfoCntxt;
			this->InfoStatic5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoStatic5->Location = System::Drawing::Point(5, 111);
			this->InfoStatic5->Name = L"InfoStatic5";
			this->InfoStatic5->Size = System::Drawing::Size(68, 15);
			this->InfoStatic5->TabIndex = 11;
			this->InfoStatic5->Text = L"FILTER:";
			this->Tooltip->SetToolTip(this->InfoStatic5, L"Right click to select header key");
			this->InfoStatic5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::InfoStatic1_MouseDoubleClick);
			this->InfoStatic5->MouseEnter += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseEnter);
			this->InfoStatic5->MouseLeave += gcnew System::EventHandler(this, &Form1::InfoStatic1_MouseLeave);
			// 
			// ImageMaxStatic
			// 
			this->ImageMaxStatic->ContextMenuStrip = this->StatsContxt;
			this->ImageMaxStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMaxStatic->Location = System::Drawing::Point(5, 175);
			this->ImageMaxStatic->Name = L"ImageMaxStatic";
			this->ImageMaxStatic->Size = System::Drawing::Size(30, 14);
			this->ImageMaxStatic->TabIndex = 19;
			this->ImageMaxStatic->Text = L"Max:";
			this->ImageMaxStatic->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageMaxStatic_MouseDoubleClick);
			this->ImageMaxStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMaxStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageMedianStatic
			// 
			this->ImageMedianStatic->ContextMenuStrip = this->StatsContxt;
			this->ImageMedianStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ImageMedianStatic->Location = System::Drawing::Point(109, 146);
			this->ImageMedianStatic->Name = L"ImageMedianStatic";
			this->ImageMedianStatic->Size = System::Drawing::Size(56, 14);
			this->ImageMedianStatic->TabIndex = 19;
			this->ImageMedianStatic->Text = L"Median:";
			this->ImageMedianStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMedianStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageMeanStatic
			// 
			this->ImageMeanStatic->ContextMenuStrip = this->StatsContxt;
			this->ImageMeanStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMeanStatic->Location = System::Drawing::Point(109, 160);
			this->ImageMeanStatic->Name = L"ImageMeanStatic";
			this->ImageMeanStatic->Size = System::Drawing::Size(45, 14);
			this->ImageMeanStatic->TabIndex = 20;
			this->ImageMeanStatic->Text = L"Mean:";
			this->ImageMeanStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMeanStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageStdvStatic
			// 
			this->ImageStdvStatic->ContextMenuStrip = this->StatsContxt;
			this->ImageStdvStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageStdvStatic->Location = System::Drawing::Point(109, 175);
			this->ImageStdvStatic->Name = L"ImageStdvStatic";
			this->ImageStdvStatic->Size = System::Drawing::Size(45, 14);
			this->ImageStdvStatic->TabIndex = 20;
			this->ImageStdvStatic->Text = L"Stdv:";
			this->ImageStdvStatic->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageStdvStatic->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageMinTxt
			// 
			this->ImageMinTxt->AutoEllipsis = true;
			this->ImageMinTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMinTxt->Location = System::Drawing::Point(34, 160);
			this->ImageMinTxt->Name = L"ImageMinTxt";
			this->ImageMinTxt->Size = System::Drawing::Size(75, 14);
			this->ImageMinTxt->TabIndex = 19;
			this->ImageMinTxt->Text = L"0";
			this->ImageMinTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageMinTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageMinTxt_MouseClick);
			this->ImageMinTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMinTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageMeanTxt
			// 
			this->ImageMeanTxt->AutoEllipsis = true;
			this->ImageMeanTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMeanTxt->Location = System::Drawing::Point(154, 160);
			this->ImageMeanTxt->Name = L"ImageMeanTxt";
			this->ImageMeanTxt->Size = System::Drawing::Size(75, 14);
			this->ImageMeanTxt->TabIndex = 21;
			this->ImageMeanTxt->Text = L"0";
			this->ImageMeanTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageMeanTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageMeanTxt_MouseClick);
			this->ImageMeanTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMeanTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageStdTxt
			// 
			this->ImageStdTxt->AutoEllipsis = true;
			this->ImageStdTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageStdTxt->Location = System::Drawing::Point(154, 175);
			this->ImageStdTxt->Name = L"ImageStdTxt";
			this->ImageStdTxt->Size = System::Drawing::Size(75, 14);
			this->ImageStdTxt->TabIndex = 21;
			this->ImageStdTxt->Text = L"0";
			this->ImageStdTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageStdTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageStdTxt_MouseClick);
			this->ImageStdTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageStdTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// ImageMaxTxt
			// 
			this->ImageMaxTxt->AutoEllipsis = true;
			this->ImageMaxTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageMaxTxt->Location = System::Drawing::Point(34, 175);
			this->ImageMaxTxt->Name = L"ImageMaxTxt";
			this->ImageMaxTxt->Size = System::Drawing::Size(75, 14);
			this->ImageMaxTxt->TabIndex = 20;
			this->ImageMaxTxt->Text = L"0";
			this->ImageMaxTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->ImageMaxTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageMaxTxt_MouseClick);
			this->ImageMaxTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseEnter);
			this->ImageMaxTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageSumStatic_MouseLeave);
			// 
			// FileNameTxt
			// 
			this->FileNameTxt->AutoEllipsis = true;
			this->FileNameTxt->BackColor = System::Drawing::Color::LightGray;
			this->FileNameTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FileNameTxt->Location = System::Drawing::Point(66, 15);
			this->FileNameTxt->Name = L"FileNameTxt";
			this->FileNameTxt->Size = System::Drawing::Size(165, 14);
			this->FileNameTxt->TabIndex = 19;
			this->FileNameTxt->Text = L"NA";
			this->FileNameTxt->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->FileNameTxt->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::FileNameTxt_MouseClick);
			this->FileNameTxt->MouseLeave += gcnew System::EventHandler(this, &Form1::FileNameTxt_MouseLeave);
			// 
			// FileDirectoryTxt
			// 
			this->FileDirectoryTxt->AutoEllipsis = true;
			this->FileDirectoryTxt->ContextMenuStrip = this->FileDirectoryTxtContextMenu;
			this->FileDirectoryTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FileDirectoryTxt->Location = System::Drawing::Point(61, 31);
			this->FileDirectoryTxt->Name = L"FileDirectoryTxt";
			this->FileDirectoryTxt->Size = System::Drawing::Size(170, 15);
			this->FileDirectoryTxt->TabIndex = 20;
			this->FileDirectoryTxt->Text = L"NA";
			this->FileDirectoryTxt->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->FileDirectoryTxt->DoubleClick += gcnew System::EventHandler(this, &Form1::FileDirectoryTxt_DoubleClick);
			// 
			// FileDirectoryTxtContextMenu
			// 
			this->FileDirectoryTxtContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FileDirectoryTxtContextMenuDelDirRmImg });
			this->FileDirectoryTxtContextMenu->Name = L"FileDirectoryTxtContextMenu";
			this->FileDirectoryTxtContextMenu->ShowImageMargin = false;
			this->FileDirectoryTxtContextMenu->Size = System::Drawing::Size(239, 26);
			// 
			// FileDirectoryTxtContextMenuDelDirRmImg
			// 
			this->FileDirectoryTxtContextMenuDelDirRmImg->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->FileDirectoryTxtContextMenuDelDirRmImg->Name = L"FileDirectoryTxtContextMenuDelDirRmImg";
			this->FileDirectoryTxtContextMenuDelDirRmImg->Size = System::Drawing::Size(238, 22);
			this->FileDirectoryTxtContextMenuDelDirRmImg->Text = L"Delete Directory and Remove Image";
			this->FileDirectoryTxtContextMenuDelDirRmImg->Click += gcnew System::EventHandler(this, &Form1::FileDirectoryTxtContextMenuDelDirRmImg_Click);
			// 
			// FileDirectoryStatic
			// 
			this->FileDirectoryStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->FileDirectoryStatic->Location = System::Drawing::Point(5, 31);
			this->FileDirectoryStatic->Name = L"FileDirectoryStatic";
			this->FileDirectoryStatic->Size = System::Drawing::Size(55, 15);
			this->FileDirectoryStatic->TabIndex = 19;
			this->FileDirectoryStatic->Text = L"Directory:";
			this->Tooltip->SetToolTip(this->FileDirectoryStatic, L"Double-click directory label to open.");
			// 
			// ContrastPanel
			// 
			this->ContrastPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ContrastPanel->BackColor = System::Drawing::Color::LightGray;
			this->ContrastPanel->Controls->Add(this->MinContrastCountTxt);
			this->ContrastPanel->Controls->Add(this->MinContrastSlider);
			this->ContrastPanel->Controls->Add(this->MinContrastStdTxt);
			this->ContrastPanel->Controls->Add(this->MinContrastStatic);
			this->ContrastPanel->Controls->Add(this->ContrastFullRad);
			this->ContrastPanel->Controls->Add(this->ContrastModePanel);
			this->ContrastPanel->Controls->Add(this->ContrastWideRad);
			this->ContrastPanel->Controls->Add(this->ContrastNarrowRad);
			this->ContrastPanel->Controls->Add(this->MaxContrastStdTxt);
			this->ContrastPanel->Controls->Add(this->MaxContrastCountTxt);
			this->ContrastPanel->Controls->Add(this->MaxContrastSlider);
			this->ContrastPanel->Controls->Add(this->MaxContrastStatic);
			this->ContrastPanel->Enabled = false;
			this->ContrastPanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ContrastPanel->Location = System::Drawing::Point(855, 25);
			this->ContrastPanel->Name = L"ContrastPanel";
			this->ContrastPanel->Size = System::Drawing::Size(235, 216);
			this->ContrastPanel->TabIndex = 33;
			this->ContrastPanel->TabStop = false;
			this->ContrastPanel->Text = L"Contrast";
			// 
			// MinContrastCountTxt
			// 
			this->MinContrastCountTxt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->MinContrastCountTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MinContrastCountTxt->Location = System::Drawing::Point(120, 171);
			this->MinContrastCountTxt->MaxLength = 6;
			this->MinContrastCountTxt->Name = L"MinContrastCountTxt";
			this->MinContrastCountTxt->Size = System::Drawing::Size(56, 20);
			this->MinContrastCountTxt->TabIndex = 3;
			this->MinContrastCountTxt->Text = L"0";
			this->Tooltip->SetToolTip(this->MinContrastCountTxt, L"Min Count");
			this->MinContrastCountTxt->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::MinContrastCountTxt_KeyUp);
			// 
			// MinContrastSlider
			// 
			this->MinContrastSlider->Location = System::Drawing::Point(140, 13);
			this->MinContrastSlider->Maximum = 300;
			this->MinContrastSlider->Name = L"MinContrastSlider";
			this->MinContrastSlider->Size = System::Drawing::Size(16, 137);
			this->MinContrastSlider->TabIndex = 4;
			this->MinContrastSlider->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::MinContrastSlider_Scroll);
			this->MinContrastSlider->MouseEnter += gcnew System::EventHandler(this, &Form1::MinContrastSlider_MouseEnter);
			this->MinContrastSlider->MouseLeave += gcnew System::EventHandler(this, &Form1::MinContrastSlider_MouseLeave);
			this->MinContrastSlider->MouseHover += gcnew System::EventHandler(this, &Form1::MinContrastSlider_MouseHover);
			this->MinContrastSlider->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MinContrastSlider_MouseWheel);
			// 
			// MinContrastStdTxt
			// 
			this->MinContrastStdTxt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->MinContrastStdTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MinContrastStdTxt->Location = System::Drawing::Point(124, 192);
			this->MinContrastStdTxt->MaxLength = 6;
			this->MinContrastStdTxt->Name = L"MinContrastStdTxt";
			this->MinContrastStdTxt->Size = System::Drawing::Size(48, 20);
			this->MinContrastStdTxt->TabIndex = 4;
			this->MinContrastStdTxt->Text = L"-1";
			this->MinContrastStdTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Tooltip->SetToolTip(this->MinContrastStdTxt, L"MIn STD");
			this->MinContrastStdTxt->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::MinContrastStdTxt_KeyUp);
			// 
			// MinContrastStatic
			// 
			this->MinContrastStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MinContrastStatic->Location = System::Drawing::Point(134, 152);
			this->MinContrastStatic->Name = L"MinContrastStatic";
			this->MinContrastStatic->Size = System::Drawing::Size(28, 16);
			this->MinContrastStatic->TabIndex = 10;
			this->MinContrastStatic->Text = L"Min";
			this->MinContrastStatic->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			// 
			// ContrastFullRad
			// 
			this->ContrastFullRad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ContrastFullRad->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ContrastFullRad->Location = System::Drawing::Point(5, 18);
			this->ContrastFullRad->Name = L"ContrastFullRad";
			this->ContrastFullRad->Size = System::Drawing::Size(142, 16);
			this->ContrastFullRad->TabIndex = 0;
			this->ContrastFullRad->Text = L"Full Range (min - max)";
			this->ContrastFullRad->Click += gcnew System::EventHandler(this, &Form1::ContrastFullRad_Click);
			// 
			// ContrastModePanel
			// 
			this->ContrastModePanel->Controls->Add(this->ColourMapDrop);
			this->ContrastModePanel->Controls->Add(this->ContrastScaleDrop);
			this->ContrastModePanel->Controls->Add(this->InvertContrastChck);
			this->ContrastModePanel->Controls->Add(this->RelativeContrast);
			this->ContrastModePanel->Controls->Add(this->AutoContrast);
			this->ContrastModePanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ContrastModePanel->Location = System::Drawing::Point(5, 84);
			this->ContrastModePanel->Name = L"ContrastModePanel";
			this->ContrastModePanel->Size = System::Drawing::Size(105, 128);
			this->ContrastModePanel->TabIndex = 11;
			this->ContrastModePanel->TabStop = false;
			this->ContrastModePanel->Text = L"Contrast Mode";
			// 
			// ColourMapDrop
			// 
			this->ColourMapDrop->DisplayMember = L"1";
			this->ColourMapDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ColourMapDrop->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Grayscale", L"Jet", L"Winter", L"Lines" });
			this->ColourMapDrop->Location = System::Drawing::Point(5, 101);
			this->ColourMapDrop->Name = L"ColourMapDrop";
			this->ColourMapDrop->Size = System::Drawing::Size(95, 21);
			this->ColourMapDrop->TabIndex = 45;
			this->Tooltip->SetToolTip(this->ColourMapDrop, L"Contrast Scaling Transfer Function;  Defualt is Linear");
			this->ColourMapDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ColourMapDrop_SelectedIndexChanged);
			// 
			// ContrastScaleDrop
			// 
			this->ContrastScaleDrop->DisplayMember = L"1";
			this->ContrastScaleDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ContrastScaleDrop->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Linear", L"Square Root", L"Squared",
					L"Log"
			});
			this->ContrastScaleDrop->Location = System::Drawing::Point(5, 78);
			this->ContrastScaleDrop->Name = L"ContrastScaleDrop";
			this->ContrastScaleDrop->Size = System::Drawing::Size(95, 21);
			this->ContrastScaleDrop->TabIndex = 12;
			this->Tooltip->SetToolTip(this->ContrastScaleDrop, L"Colour Transfer Function;  Defualt is Grayscale");
			this->ContrastScaleDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ContrastScaleDrop_SelectedIndexChanged);
			// 
			// InvertContrastChck
			// 
			this->InvertContrastChck->AutoSize = true;
			this->InvertContrastChck->Location = System::Drawing::Point(8, 55);
			this->InvertContrastChck->Name = L"InvertContrastChck";
			this->InvertContrastChck->Size = System::Drawing::Size(53, 17);
			this->InvertContrastChck->TabIndex = 2;
			this->InvertContrastChck->Text = L"Invert";
			this->InvertContrastChck->UseVisualStyleBackColor = true;
			this->InvertContrastChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::InvertContrastChck_CheckedChanged);
			// 
			// RelativeContrast
			// 
			this->RelativeContrast->Location = System::Drawing::Point(8, 34);
			this->RelativeContrast->Name = L"RelativeContrast";
			this->RelativeContrast->Size = System::Drawing::Size(73, 16);
			this->RelativeContrast->TabIndex = 1;
			this->RelativeContrast->Text = L"Relative";
			this->Tooltip->SetToolTip(this->RelativeContrast, L"Scale Contrast of Current Image to Scale of Image which was Current when \'Relativ"
				L"e\' Button was Pressed");
				// 
				// AutoContrast
				// 
			this->AutoContrast->Checked = true;
			this->AutoContrast->Location = System::Drawing::Point(8, 15);
			this->AutoContrast->Name = L"AutoContrast";
			this->AutoContrast->Size = System::Drawing::Size(64, 16);
			this->AutoContrast->TabIndex = 0;
			this->AutoContrast->TabStop = true;
			this->AutoContrast->Text = L"Auto";
			this->Tooltip->SetToolTip(this->AutoContrast, L"Automatically Scale Contrast to Current Image using Current Settings");
			// 
			// ContrastWideRad
			// 
			this->ContrastWideRad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ContrastWideRad->Checked = true;
			this->ContrastWideRad->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ContrastWideRad->Location = System::Drawing::Point(5, 58);
			this->ContrastWideRad->Name = L"ContrastWideRad";
			this->ContrastWideRad->Size = System::Drawing::Size(128, 16);
			this->ContrastWideRad->TabIndex = 2;
			this->ContrastWideRad->TabStop = true;
			this->ContrastWideRad->Text = L"Dark (-0.5std - 5std)";
			this->ContrastWideRad->Click += gcnew System::EventHandler(this, &Form1::ContrastWideRad_Click);
			// 
			// ContrastNarrowRad
			// 
			this->ContrastNarrowRad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ContrastNarrowRad->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ContrastNarrowRad->Location = System::Drawing::Point(5, 38);
			this->ContrastNarrowRad->Name = L"ContrastNarrowRad";
			this->ContrastNarrowRad->Size = System::Drawing::Size(142, 16);
			this->ContrastNarrowRad->TabIndex = 1;
			this->ContrastNarrowRad->Text = L"Wide (-1std - 2std)";
			this->ContrastNarrowRad->Click += gcnew System::EventHandler(this, &Form1::ContrastNarrowRad_Click);
			// 
			// MaxContrastStdTxt
			// 
			this->MaxContrastStdTxt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->MaxContrastStdTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MaxContrastStdTxt->Location = System::Drawing::Point(181, 192);
			this->MaxContrastStdTxt->MaxLength = 6;
			this->MaxContrastStdTxt->Name = L"MaxContrastStdTxt";
			this->MaxContrastStdTxt->Size = System::Drawing::Size(48, 20);
			this->MaxContrastStdTxt->TabIndex = 6;
			this->MaxContrastStdTxt->Text = L"2";
			this->MaxContrastStdTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Tooltip->SetToolTip(this->MaxContrastStdTxt, L"Max STD");
			this->MaxContrastStdTxt->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::MaxContrastStdTxt_KeyUp);
			// 
			// MaxContrastCountTxt
			// 
			this->MaxContrastCountTxt->BackColor = System::Drawing::Color::WhiteSmoke;
			this->MaxContrastCountTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MaxContrastCountTxt->Location = System::Drawing::Point(177, 171);
			this->MaxContrastCountTxt->MaxLength = 6;
			this->MaxContrastCountTxt->Name = L"MaxContrastCountTxt";
			this->MaxContrastCountTxt->Size = System::Drawing::Size(56, 20);
			this->MaxContrastCountTxt->TabIndex = 5;
			this->MaxContrastCountTxt->Text = L"1000";
			this->MaxContrastCountTxt->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->Tooltip->SetToolTip(this->MaxContrastCountTxt, L"Max Count");
			this->MaxContrastCountTxt->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::MaxContrastCountTxt_KeyUp);
			// 
			// MaxContrastSlider
			// 
			this->MaxContrastSlider->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->MaxContrastSlider->Location = System::Drawing::Point(197, 13);
			this->MaxContrastSlider->Maximum = 300;
			this->MaxContrastSlider->Name = L"MaxContrastSlider";
			this->MaxContrastSlider->Size = System::Drawing::Size(16, 137);
			this->MaxContrastSlider->TabIndex = 3;
			this->MaxContrastSlider->Value = 300;
			this->MaxContrastSlider->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::MaxContrastSlider_Scroll);
			this->MaxContrastSlider->MouseEnter += gcnew System::EventHandler(this, &Form1::MaxContrastSlider_MouseEnter);
			this->MaxContrastSlider->MouseLeave += gcnew System::EventHandler(this, &Form1::MaxContrastSlider_MouseLeave);
			this->MaxContrastSlider->MouseHover += gcnew System::EventHandler(this, &Form1::MaxContrastSlider_MouseHover);
			this->MaxContrastSlider->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::MaxContrastSlider_MouseWheel);
			// 
			// MaxContrastStatic
			// 
			this->MaxContrastStatic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MaxContrastStatic->Location = System::Drawing::Point(189, 152);
			this->MaxContrastStatic->Name = L"MaxContrastStatic";
			this->MaxContrastStatic->Size = System::Drawing::Size(32, 15);
			this->MaxContrastStatic->TabIndex = 9;
			this->MaxContrastStatic->Text = L"Max";
			this->MaxContrastStatic->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			// 
			// BlinkChck
			// 
			this->BlinkChck->Appearance = System::Windows::Forms::Appearance::Button;
			this->BlinkChck->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->BlinkChck->ContextMenuStrip = this->ScanBtnContext;
			this->BlinkChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BlinkChck->Location = System::Drawing::Point(46, 52);
			this->BlinkChck->Name = L"BlinkChck";
			this->BlinkChck->Size = System::Drawing::Size(49, 20);
			this->BlinkChck->TabIndex = 22;
			this->BlinkChck->Text = L"Scan";
			this->BlinkChck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Tooltip->SetToolTip(this->BlinkChck, L"Auto-Blink Images (Right-Click More Options)");
			this->BlinkChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BlinkChck_CheckedChanged);
			// 
			// ScanBtnContext
			// 
			this->ScanBtnContext->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->toolStripSeparator19,
					this->ScanContextGoToBtn, this->ScanContextGoToTxt, this->toolStripSeparator18
			});
			this->ScanBtnContext->Name = L"ScanBtnContext";
			this->ScanBtnContext->ShowImageMargin = false;
			this->ScanBtnContext->Size = System::Drawing::Size(136, 63);
			// 
			// toolStripSeparator19
			// 
			this->toolStripSeparator19->Name = L"toolStripSeparator19";
			this->toolStripSeparator19->Size = System::Drawing::Size(132, 6);
			// 
			// ScanContextGoToBtn
			// 
			this->ScanContextGoToBtn->Name = L"ScanContextGoToBtn";
			this->ScanContextGoToBtn->Size = System::Drawing::Size(135, 22);
			this->ScanContextGoToBtn->Text = L"Go To";
			this->ScanContextGoToBtn->Click += gcnew System::EventHandler(this, &Form1::ScanContextGoToBtn_Click);
			// 
			// ScanContextGoToTxt
			// 
			this->ScanContextGoToTxt->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ScanContextGoToTxt->Name = L"ScanContextGoToTxt";
			this->ScanContextGoToTxt->Size = System::Drawing::Size(100, 23);
			this->ScanContextGoToTxt->Text = L"1";
			this->ScanContextGoToTxt->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::ScanContextGoToTxt_KeyUp);
			this->ScanContextGoToTxt->TextChanged += gcnew System::EventHandler(this, &Form1::ScanContextGoToTxt_TextChanged);
			// 
			// toolStripSeparator18
			// 
			this->toolStripSeparator18->Name = L"toolStripSeparator18";
			this->toolStripSeparator18->Size = System::Drawing::Size(132, 6);
			// 
			// BatchViewPanel
			// 
			this->BatchViewPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BatchViewPanel->BackColor = System::Drawing::Color::LightGray;
			this->BatchViewPanel->Controls->Add(this->FileListDrop);
			this->BatchViewPanel->Controls->Add(this->BlinkTime);
			this->BatchViewPanel->Controls->Add(this->BlinkChck);
			this->BatchViewPanel->Controls->Add(this->ViewSelectionStatic);
			this->BatchViewPanel->Controls->Add(this->ViewNextBtn);
			this->BatchViewPanel->Controls->Add(this->ViewLastbtn);
			this->BatchViewPanel->Controls->Add(this->MoveUpBtn);
			this->BatchViewPanel->Controls->Add(this->MoveDownBtn);
			this->BatchViewPanel->Controls->Add(this->DeleteFileBtn);
			this->BatchViewPanel->Controls->Add(this->SingleOutBtn);
			this->BatchViewPanel->Enabled = false;
			this->BatchViewPanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BatchViewPanel->Location = System::Drawing::Point(855, 250);
			this->BatchViewPanel->Name = L"BatchViewPanel";
			this->BatchViewPanel->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->BatchViewPanel->Size = System::Drawing::Size(235, 100);
			this->BatchViewPanel->TabIndex = 35;
			this->BatchViewPanel->TabStop = false;
			this->BatchViewPanel->Text = L"Batch Viewing";
			// 
			// FileListDrop
			// 
			this->FileListDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FileListDrop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FileListDrop->FormattingEnabled = true;
			this->FileListDrop->Location = System::Drawing::Point(5, 29);
			this->FileListDrop->Name = L"FileListDrop";
			this->FileListDrop->Size = System::Drawing::Size(130, 21);
			this->FileListDrop->TabIndex = 45;
			this->FileListDrop->DropDown += gcnew System::EventHandler(this, &Form1::FileListDrop_DropDown);
			this->FileListDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::FileListDrop_SelectedIndexChanged);
			this->FileListDrop->DropDownClosed += gcnew System::EventHandler(this, &Form1::FileListDrop_DropDownClosed);
			this->FileListDrop->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::FileListDrop_MouseClick);
			// 
			// BlinkTime
			// 
			this->BlinkTime->DecimalPlaces = 1;
			this->BlinkTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BlinkTime->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->BlinkTime->Location = System::Drawing::Point(46, 71);
			this->BlinkTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->BlinkTime->Name = L"BlinkTime";
			this->BlinkTime->Size = System::Drawing::Size(49, 20);
			this->BlinkTime->TabIndex = 45;
			this->BlinkTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Tooltip->SetToolTip(this->BlinkTime, L"Seconds");
			this->BlinkTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 65536 });
			// 
			// SubImageSlideY
			// 
			this->SubImageSlideY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SubImageSlideY->Enabled = false;
			this->SubImageSlideY->Location = System::Drawing::Point(1125, 583);
			this->SubImageSlideY->Maximum = 1000;
			this->SubImageSlideY->Minimum = 1;
			this->SubImageSlideY->Name = L"SubImageSlideY";
			this->SubImageSlideY->Size = System::Drawing::Size(15, 270);
			this->SubImageSlideY->TabIndex = 32;
			this->SubImageSlideY->Value = 500;
			this->SubImageSlideY->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::SubImageSlideY_Scroll);
			// 
			// SubImageSlideX
			// 
			this->SubImageSlideX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SubImageSlideX->Enabled = false;
			this->SubImageSlideX->Location = System::Drawing::Point(855, 567);
			this->SubImageSlideX->Maximum = 1000;
			this->SubImageSlideX->Minimum = 1;
			this->SubImageSlideX->Name = L"SubImageSlideX";
			this->SubImageSlideX->Size = System::Drawing::Size(270, 15);
			this->SubImageSlideX->TabIndex = 31;
			this->SubImageSlideX->Value = 500;
			this->SubImageSlideX->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::SubImageSlideX_Scroll);
			// 
			// SubImageWindow
			// 
			this->SubImageWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SubImageWindow->BackColor = System::Drawing::Color::Silver;
			this->SubImageWindow->Cursor = System::Windows::Forms::Cursors::Cross;
			this->SubImageWindow->Location = System::Drawing::Point(855, 583);
			this->SubImageWindow->Margin = System::Windows::Forms::Padding(0);
			this->SubImageWindow->Name = L"SubImageWindow";
			this->SubImageWindow->Size = System::Drawing::Size(270, 270);
			this->SubImageWindow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->SubImageWindow->TabIndex = 30;
			this->SubImageWindow->TabStop = false;
			this->SubImageWindow->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::SubImageWindow_Paint);
			this->SubImageWindow->DoubleClick += gcnew System::EventHandler(this, &Form1::SubImageWindow_DoubleClick);
			this->SubImageWindow->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageWindow_MouseDoubleClick);
			this->SubImageWindow->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageWindow_MouseDown);
			this->SubImageWindow->MouseEnter += gcnew System::EventHandler(this, &Form1::SubImageWindow_MouseEnter);
			this->SubImageWindow->MouseLeave += gcnew System::EventHandler(this, &Form1::SubImageWindow_MouseLeave);
			this->SubImageWindow->MouseHover += gcnew System::EventHandler(this, &Form1::SubImageWindow_MouseHover);
			this->SubImageWindow->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageWindow_MouseMove);
			this->SubImageWindow->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageWindow_MouseUp);
			this->SubImageWindow->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::SubImageWindow_MouseWheel);
			// 
			// SubImageCntxt
			// 
			this->SubImageCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->SubImgRadialPlotMenuBtn,
					this->SubImageSurfCntxt, this->SubImageEditCntxt, this->centerToolStripMenuItem, this->SubImCntxtCut, this->SubImCntxtGoToRADec,
					this->SubImCntxtGoToPixel, this->SubImCntxtCopyPixPoord, this->SubImCntxtCopyCentroidCoord, this->SubImCntxtMarkCoord, this->SubImCntxtCopyImage
			});
			this->SubImageCntxt->Name = L"SubImageCntxtMenu";
			this->SubImageCntxt->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->SubImageCntxt->ShowImageMargin = false;
			this->SubImageCntxt->Size = System::Drawing::Size(189, 246);
			// 
			// SubImgRadialPlotMenuBtn
			// 
			this->SubImgRadialPlotMenuBtn->DoubleClickEnabled = true;
			this->SubImgRadialPlotMenuBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->RadialPlotMedianBackgroundChck,
					this->SubImCntxtSaveRadialProfileMenuBtn
			});
			this->SubImgRadialPlotMenuBtn->Name = L"SubImgRadialPlotMenuBtn";
			this->SubImgRadialPlotMenuBtn->Size = System::Drawing::Size(188, 22);
			this->SubImgRadialPlotMenuBtn->Text = L"Radial Profile Plot";
			this->SubImgRadialPlotMenuBtn->DoubleClick += gcnew System::EventHandler(this, &Form1::SubImgRadialPlotMenuBtn_Click);
			// 
			// RadialPlotMedianBackgroundChck
			// 
			this->RadialPlotMedianBackgroundChck->CheckOnClick = true;
			this->RadialPlotMedianBackgroundChck->Name = L"RadialPlotMedianBackgroundChck";
			this->RadialPlotMedianBackgroundChck->Size = System::Drawing::Size(199, 22);
			this->RadialPlotMedianBackgroundChck->Text = L"Median for Background";
			this->RadialPlotMedianBackgroundChck->ToolTipText = L"Otherwise uses minimum...";
			this->RadialPlotMedianBackgroundChck->Click += gcnew System::EventHandler(this, &Form1::RadialPlotMedianBackgroundChck_Click);
			// 
			// SubImCntxtSaveRadialProfileMenuBtn
			// 
			this->SubImCntxtSaveRadialProfileMenuBtn->Enabled = false;
			this->SubImCntxtSaveRadialProfileMenuBtn->Name = L"SubImCntxtSaveRadialProfileMenuBtn";
			this->SubImCntxtSaveRadialProfileMenuBtn->Size = System::Drawing::Size(199, 22);
			this->SubImCntxtSaveRadialProfileMenuBtn->Text = L"Save Radial Profile";
			this->SubImCntxtSaveRadialProfileMenuBtn->Click += gcnew System::EventHandler(this, &Form1::ImageWindowSaveRadialVector_Click);
			// 
			// SubImageSurfCntxt
			// 
			this->SubImageSurfCntxt->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->SubImageSurfCntxt->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->SubImageSurfFacet,
					this->SubImageSurfMetal, this->SubImageSurfSmooth, this->SubImageSurfMesh, this->SubImSurfColumnMenuBtn
			});
			this->SubImageSurfCntxt->Name = L"SubImageSurfCntxt";
			this->SubImageSurfCntxt->Size = System::Drawing::Size(188, 22);
			this->SubImageSurfCntxt->Text = L"View Surface";
			// 
			// SubImageSurfFacet
			// 
			this->SubImageSurfFacet->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->SubImageSurfFacet->Name = L"SubImageSurfFacet";
			this->SubImageSurfFacet->Size = System::Drawing::Size(117, 22);
			this->SubImageSurfFacet->Text = L"Faceted";
			this->SubImageSurfFacet->Click += gcnew System::EventHandler(this, &Form1::SubImageSurfFacet_Click);
			// 
			// SubImageSurfMetal
			// 
			this->SubImageSurfMetal->Name = L"SubImageSurfMetal";
			this->SubImageSurfMetal->Size = System::Drawing::Size(117, 22);
			this->SubImageSurfMetal->Text = L"Metal";
			this->SubImageSurfMetal->Click += gcnew System::EventHandler(this, &Form1::SubImageSurfMetal_Click);
			// 
			// SubImageSurfSmooth
			// 
			this->SubImageSurfSmooth->Name = L"SubImageSurfSmooth";
			this->SubImageSurfSmooth->Size = System::Drawing::Size(117, 22);
			this->SubImageSurfSmooth->Text = L"Smooth";
			this->SubImageSurfSmooth->Click += gcnew System::EventHandler(this, &Form1::SubImageSurfSmooth_Click);
			// 
			// SubImageSurfMesh
			// 
			this->SubImageSurfMesh->Name = L"SubImageSurfMesh";
			this->SubImageSurfMesh->Size = System::Drawing::Size(117, 22);
			this->SubImageSurfMesh->Text = L"Mesh";
			this->SubImageSurfMesh->Click += gcnew System::EventHandler(this, &Form1::SubImageSurfMesh_Click);
			// 
			// SubImSurfColumnMenuBtn
			// 
			this->SubImSurfColumnMenuBtn->Name = L"SubImSurfColumnMenuBtn";
			this->SubImSurfColumnMenuBtn->Size = System::Drawing::Size(117, 22);
			this->SubImSurfColumnMenuBtn->Text = L"Column";
			this->SubImSurfColumnMenuBtn->Click += gcnew System::EventHandler(this, &Form1::SubImSurfColumnMenuBtn_Click);
			// 
			// SubImageEditCntxt
			// 
			this->SubImageEditCntxt->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->EditValueCntxt,
					this->EditBoxCntxt
			});
			this->SubImageEditCntxt->Name = L"SubImageEditCntxt";
			this->SubImageEditCntxt->Size = System::Drawing::Size(188, 22);
			this->SubImageEditCntxt->Text = L"Edit";
			// 
			// EditValueCntxt
			// 
			this->EditValueCntxt->Name = L"EditValueCntxt";
			this->EditValueCntxt->Size = System::Drawing::Size(132, 22);
			this->EditValueCntxt->Text = L"Value";
			this->EditValueCntxt->Click += gcnew System::EventHandler(this, &Form1::EditValueCntxt_Click);
			// 
			// EditBoxCntxt
			// 
			this->EditBoxCntxt->Name = L"EditBoxCntxt";
			this->EditBoxCntxt->Size = System::Drawing::Size(132, 22);
			this->EditBoxCntxt->Text = L"Cursor Box";
			this->EditBoxCntxt->Click += gcnew System::EventHandler(this, &Form1::EditBoxCntxt_Click);
			// 
			// centerToolStripMenuItem
			// 
			this->centerToolStripMenuItem->Name = L"centerToolStripMenuItem";
			this->centerToolStripMenuItem->Size = System::Drawing::Size(188, 22);
			this->centerToolStripMenuItem->Text = L"Center";
			this->centerToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::centerToolStripMenuItem_Click);
			// 
			// SubImCntxtCut
			// 
			this->SubImCntxtCut->Name = L"SubImCntxtCut";
			this->SubImCntxtCut->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtCut->Text = L"Cut";
			this->SubImCntxtCut->Click += gcnew System::EventHandler(this, &Form1::CutSubImBtn_Click);
			// 
			// SubImCntxtGoToRADec
			// 
			this->SubImCntxtGoToRADec->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->toolStripMenuItem10,
					this->SubImCntxtGoToRATxt, this->toolStripMenuItem11, this->SubImCntxtGoToDecTxt
			});
			this->SubImCntxtGoToRADec->Name = L"SubImCntxtGoToRADec";
			this->SubImCntxtGoToRADec->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtGoToRADec->Text = L"Go to RA-Dec Coordinate";
			// 
			// toolStripMenuItem10
			// 
			this->toolStripMenuItem10->Name = L"toolStripMenuItem10";
			this->toolStripMenuItem10->Size = System::Drawing::Size(160, 22);
			this->toolStripMenuItem10->Text = L"RA";
			// 
			// SubImCntxtGoToRATxt
			// 
			this->SubImCntxtGoToRATxt->BackColor = System::Drawing::Color::Gainsboro;
			this->SubImCntxtGoToRATxt->Name = L"SubImCntxtGoToRATxt";
			this->SubImCntxtGoToRATxt->Size = System::Drawing::Size(100, 23);
			this->SubImCntxtGoToRATxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::SubImCntxtGoToRATxt_KeyDown);
			// 
			// toolStripMenuItem11
			// 
			this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
			this->toolStripMenuItem11->Size = System::Drawing::Size(160, 22);
			this->toolStripMenuItem11->Text = L"Dec";
			// 
			// SubImCntxtGoToDecTxt
			// 
			this->SubImCntxtGoToDecTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->SubImCntxtGoToDecTxt->Name = L"SubImCntxtGoToDecTxt";
			this->SubImCntxtGoToDecTxt->Size = System::Drawing::Size(100, 23);
			this->SubImCntxtGoToDecTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::SubImCntxtGoToDecTxt_KeyDown);
			// 
			// SubImCntxtGoToPixel
			// 
			this->SubImCntxtGoToPixel->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->toolStripMenuItem8,
					this->SubImCntxtGoToPixXTxt, this->toolStripMenuItem9, this->SubImCntxtGoToPixYTxt
			});
			this->SubImCntxtGoToPixel->Name = L"SubImCntxtGoToPixel";
			this->SubImCntxtGoToPixel->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtGoToPixel->Text = L"Go to Pixel Coordinate";
			this->SubImCntxtGoToPixel->DropDownOpened += gcnew System::EventHandler(this, &Form1::SubImCntxtGoToPixel_DropDownOpened);
			// 
			// toolStripMenuItem8
			// 
			this->toolStripMenuItem8->Enabled = false;
			this->toolStripMenuItem8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
			this->toolStripMenuItem8->Size = System::Drawing::Size(160, 22);
			this->toolStripMenuItem8->Text = L"X";
			// 
			// SubImCntxtGoToPixXTxt
			// 
			this->SubImCntxtGoToPixXTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->SubImCntxtGoToPixXTxt->Name = L"SubImCntxtGoToPixXTxt";
			this->SubImCntxtGoToPixXTxt->Size = System::Drawing::Size(100, 23);
			this->SubImCntxtGoToPixXTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::SubImCntxtGoToPixXTxt_KeyDown);
			// 
			// toolStripMenuItem9
			// 
			this->toolStripMenuItem9->Enabled = false;
			this->toolStripMenuItem9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
			this->toolStripMenuItem9->Size = System::Drawing::Size(160, 22);
			this->toolStripMenuItem9->Text = L"Y";
			// 
			// SubImCntxtGoToPixYTxt
			// 
			this->SubImCntxtGoToPixYTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->SubImCntxtGoToPixYTxt->Name = L"SubImCntxtGoToPixYTxt";
			this->SubImCntxtGoToPixYTxt->Size = System::Drawing::Size(100, 23);
			this->SubImCntxtGoToPixYTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::SubImCntxtGoToPixYTxt_KeyDown);
			// 
			// SubImCntxtCopyPixPoord
			// 
			this->SubImCntxtCopyPixPoord->Name = L"SubImCntxtCopyPixPoord";
			this->SubImCntxtCopyPixPoord->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtCopyPixPoord->Text = L"Copy Pixel Coordinate";
			this->SubImCntxtCopyPixPoord->Click += gcnew System::EventHandler(this, &Form1::SubImCntxtCopyPixPoord_Click);
			// 
			// SubImCntxtCopyCentroidCoord
			// 
			this->SubImCntxtCopyCentroidCoord->Name = L"SubImCntxtCopyCentroidCoord";
			this->SubImCntxtCopyCentroidCoord->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtCopyCentroidCoord->Text = L"Copy Centroid Coordinate";
			this->SubImCntxtCopyCentroidCoord->Click += gcnew System::EventHandler(this, &Form1::SubImCntxtCopyCentroidCoord_Click);
			// 
			// SubImCntxtMarkCoord
			// 
			this->SubImCntxtMarkCoord->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->SubImMarkCoordContainedPSE,
					this->toolStripSeparator28, this->SubImMarkCoordAsCentroidChck, this->toolStripSeparator27, this->SubImMarkCoordClear, this->SubImMarkCoordClearContained
			});
			this->SubImCntxtMarkCoord->Name = L"SubImCntxtMarkCoord";
			this->SubImCntxtMarkCoord->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtMarkCoord->Text = L"Mark Coordinate";
			this->SubImCntxtMarkCoord->Click += gcnew System::EventHandler(this, &Form1::SubImCntxtMarkCoord_Click);
			// 
			// SubImMarkCoordContainedPSE
			// 
			this->SubImMarkCoordContainedPSE->Name = L"SubImMarkCoordContainedPSE";
			this->SubImMarkCoordContainedPSE->Size = System::Drawing::Size(159, 22);
			this->SubImMarkCoordContainedPSE->Text = L"Contained PSE\'s";
			this->SubImMarkCoordContainedPSE->Click += gcnew System::EventHandler(this, &Form1::SubImMarkCoordContainedPSE_Click);
			// 
			// toolStripSeparator28
			// 
			this->toolStripSeparator28->Name = L"toolStripSeparator28";
			this->toolStripSeparator28->Size = System::Drawing::Size(156, 6);
			// 
			// SubImMarkCoordAsCentroidChck
			// 
			this->SubImMarkCoordAsCentroidChck->CheckOnClick = true;
			this->SubImMarkCoordAsCentroidChck->Name = L"SubImMarkCoordAsCentroidChck";
			this->SubImMarkCoordAsCentroidChck->Size = System::Drawing::Size(159, 22);
			this->SubImMarkCoordAsCentroidChck->Text = L"As Centroid";
			this->SubImMarkCoordAsCentroidChck->Click += gcnew System::EventHandler(this, &Form1::SubImMarkCoordAsCentroidChck_Click);
			// 
			// toolStripSeparator27
			// 
			this->toolStripSeparator27->Name = L"toolStripSeparator27";
			this->toolStripSeparator27->Size = System::Drawing::Size(156, 6);
			// 
			// SubImMarkCoordClear
			// 
			this->SubImMarkCoordClear->Name = L"SubImMarkCoordClear";
			this->SubImMarkCoordClear->Size = System::Drawing::Size(159, 22);
			this->SubImMarkCoordClear->Text = L"Clear All";
			this->SubImMarkCoordClear->Visible = false;
			this->SubImMarkCoordClear->Click += gcnew System::EventHandler(this, &Form1::SubImMarkCoordClear_Click);
			// 
			// SubImMarkCoordClearContained
			// 
			this->SubImMarkCoordClearContained->Name = L"SubImMarkCoordClearContained";
			this->SubImMarkCoordClearContained->Size = System::Drawing::Size(159, 22);
			this->SubImMarkCoordClearContained->Text = L"Clear Contained";
			this->SubImMarkCoordClearContained->Click += gcnew System::EventHandler(this, &Form1::SubImMarkCoordClearContained_Click);
			// 
			// SubImCntxtCopyImage
			// 
			this->SubImCntxtCopyImage->Name = L"SubImCntxtCopyImage";
			this->SubImCntxtCopyImage->Size = System::Drawing::Size(188, 22);
			this->SubImCntxtCopyImage->Text = L"Copy Image to Clipboard";
			this->SubImCntxtCopyImage->Click += gcnew System::EventHandler(this, &Form1::SubImCntxtCopyImage_Click);
			// 
			// ToolBar
			// 
			this->ToolBar->BackColor = System::Drawing::Color::Gainsboro;
			this->ToolBar->Dock = System::Windows::Forms::DockStyle::None;
			this->ToolBar->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->ToolBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(18) {
				this->TBLoad, this->TBLoadSubFrame,
					this->TBAdd, this->TBReload, this->toolStripSeparator5, this->TBRecentFiles, this->TBFind, this->TBViewFound, this->TBOpenFound,
					this->toolStripSeparator6, this->TBSave, this->TBSaveOver, this->TBSaveBatch, this->TBSaveBatchOver, this->TBFileSavePrecOpts,
					this->TBZipAllBtn, this->toolStripSeparator1, this->TBQuit
			});
			this->ToolBar->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->ToolBar->Location = System::Drawing::Point(0, 24);
			this->ToolBar->Name = L"ToolBar";
			this->ToolBar->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->ToolBar->Size = System::Drawing::Size(33, 365);
			this->ToolBar->TabIndex = 37;
			this->ToolBar->Text = L"toolStrip1";
			// 
			// TBLoad
			// 
			this->TBLoad->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBLoad->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBLoad.Image")));
			this->TBLoad->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBLoad->Name = L"TBLoad";
			this->TBLoad->Size = System::Drawing::Size(31, 20);
			this->TBLoad->Text = L"toolStripButton1";
			this->TBLoad->ToolTipText = L"Open File(s)";
			this->TBLoad->Click += gcnew System::EventHandler(this, &Form1::FMLoad_Click);
			// 
			// TBLoadSubFrame
			// 
			this->TBLoadSubFrame->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBLoadSubFrame->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBLoadSubFrame.Image")));
			this->TBLoadSubFrame->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBLoadSubFrame->Name = L"TBLoadSubFrame";
			this->TBLoadSubFrame->Size = System::Drawing::Size(31, 20);
			this->TBLoadSubFrame->Text = L"toolStripButton1";
			this->TBLoadSubFrame->ToolTipText = L"Open Sub-Image(s)";
			this->TBLoadSubFrame->Click += gcnew System::EventHandler(this, &Form1::FMLoadSubFrame_Click);
			// 
			// TBAdd
			// 
			this->TBAdd->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBAdd->Enabled = false;
			this->TBAdd->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBAdd.Image")));
			this->TBAdd->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBAdd->Name = L"TBAdd";
			this->TBAdd->Size = System::Drawing::Size(31, 20);
			this->TBAdd->Text = L"toolStripButton1";
			this->TBAdd->ToolTipText = L"Add File(s) to Current Set";
			this->TBAdd->Click += gcnew System::EventHandler(this, &Form1::FMAdd_Click);
			// 
			// TBReload
			// 
			this->TBReload->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBReload->Enabled = false;
			this->TBReload->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBReload.Image")));
			this->TBReload->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBReload->Name = L"TBReload";
			this->TBReload->Size = System::Drawing::Size(31, 20);
			this->TBReload->Text = L"toolStripButton1";
			this->TBReload->ToolTipText = L"Reload Files";
			this->TBReload->Click += gcnew System::EventHandler(this, &Form1::FMReload_Click);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(31, 6);
			// 
			// TBRecentFiles
			// 
			this->TBRecentFiles->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBRecentFiles->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBRecentFiles.Image")));
			this->TBRecentFiles->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBRecentFiles->Name = L"TBRecentFiles";
			this->TBRecentFiles->Size = System::Drawing::Size(31, 20);
			this->TBRecentFiles->Text = L"Recent Files";
			// 
			// TBFind
			// 
			this->TBFind->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBFind->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBFind.Image")));
			this->TBFind->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBFind->Name = L"TBFind";
			this->TBFind->Size = System::Drawing::Size(31, 20);
			this->TBFind->Text = L"toolStripButton1";
			this->TBFind->ToolTipText = L"Search Fits Files";
			this->TBFind->Click += gcnew System::EventHandler(this, &Form1::FMFind_Click);
			// 
			// TBViewFound
			// 
			this->TBViewFound->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBViewFound->Enabled = false;
			this->TBViewFound->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBViewFound.Image")));
			this->TBViewFound->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBViewFound->Name = L"TBViewFound";
			this->TBViewFound->Size = System::Drawing::Size(31, 20);
			this->TBViewFound->Text = L"toolStripButton1";
			this->TBViewFound->ToolTipText = L"View Current Found Files List";
			this->TBViewFound->Click += gcnew System::EventHandler(this, &Form1::FMViewFound_Click);
			// 
			// TBOpenFound
			// 
			this->TBOpenFound->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBOpenFound->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBOpenFound.Image")));
			this->TBOpenFound->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBOpenFound->Name = L"TBOpenFound";
			this->TBOpenFound->Size = System::Drawing::Size(31, 20);
			this->TBOpenFound->Text = L"toolStripButton1";
			this->TBOpenFound->ToolTipText = L"Open Found File(s) List";
			this->TBOpenFound->Click += gcnew System::EventHandler(this, &Form1::TBOpenFound_Click);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(31, 6);
			// 
			// TBSave
			// 
			this->TBSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBSave->Enabled = false;
			this->TBSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBSave.Image")));
			this->TBSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBSave->Name = L"TBSave";
			this->TBSave->Size = System::Drawing::Size(31, 20);
			this->TBSave->Text = L"toolStripButton1";
			this->TBSave->ToolTipText = L"Save File As";
			this->TBSave->Click += gcnew System::EventHandler(this, &Form1::FMSave_Click);
			// 
			// TBSaveOver
			// 
			this->TBSaveOver->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBSaveOver->Enabled = false;
			this->TBSaveOver->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBSaveOver.Image")));
			this->TBSaveOver->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBSaveOver->Name = L"TBSaveOver";
			this->TBSaveOver->Size = System::Drawing::Size(31, 20);
			this->TBSaveOver->Text = L"toolStripButton2";
			this->TBSaveOver->ToolTipText = L"Overwrite Current File";
			this->TBSaveOver->Click += gcnew System::EventHandler(this, &Form1::TBSaveOver_Click);
			// 
			// TBSaveBatch
			// 
			this->TBSaveBatch->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBSaveBatch->Enabled = false;
			this->TBSaveBatch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBSaveBatch.Image")));
			this->TBSaveBatch->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBSaveBatch->Name = L"TBSaveBatch";
			this->TBSaveBatch->Size = System::Drawing::Size(31, 20);
			this->TBSaveBatch->Text = L"toolStripButton1";
			this->TBSaveBatch->ToolTipText = L"Save File Batch As";
			this->TBSaveBatch->Click += gcnew System::EventHandler(this, &Form1::TBSaveBatch_Click);
			// 
			// TBSaveBatchOver
			// 
			this->TBSaveBatchOver->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBSaveBatchOver->Enabled = false;
			this->TBSaveBatchOver->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBSaveBatchOver.Image")));
			this->TBSaveBatchOver->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBSaveBatchOver->Name = L"TBSaveBatchOver";
			this->TBSaveBatchOver->Size = System::Drawing::Size(31, 20);
			this->TBSaveBatchOver->Text = L"toolStripButton1";
			this->TBSaveBatchOver->ToolTipText = L"Overwrite All Files";
			this->TBSaveBatchOver->Click += gcnew System::EventHandler(this, &Form1::TBSaveBatchOver_Click);
			// 
			// TBFileSavePrecOpts
			// 
			this->TBFileSavePrecOpts->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBFileSavePrecOpts->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->TBOptFileSavePrecDbl,
					this->TBOptFileSavePrecInt32, this->TBOptFileSavePrecInt16, this->TBOptFileSavePrecUInt16
			});
			this->TBFileSavePrecOpts->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBFileSavePrecOpts.Image")));
			this->TBFileSavePrecOpts->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBFileSavePrecOpts->Name = L"TBFileSavePrecOpts";
			this->TBFileSavePrecOpts->Size = System::Drawing::Size(31, 20);
			this->TBFileSavePrecOpts->Text = L"toolStripDropDownButton1";
			this->TBFileSavePrecOpts->ToolTipText = L"Fits File Save Precision";
			// 
			// TBOptFileSavePrecDbl
			// 
			this->TBOptFileSavePrecDbl->Checked = true;
			this->TBOptFileSavePrecDbl->CheckOnClick = true;
			this->TBOptFileSavePrecDbl->CheckState = System::Windows::Forms::CheckState::Checked;
			this->TBOptFileSavePrecDbl->Name = L"TBOptFileSavePrecDbl";
			this->TBOptFileSavePrecDbl->Size = System::Drawing::Size(112, 22);
			this->TBOptFileSavePrecDbl->Text = L"Double";
			this->TBOptFileSavePrecDbl->Click += gcnew System::EventHandler(this, &Form1::TBOptFileSavePrecDbl_Click);
			// 
			// TBOptFileSavePrecInt32
			// 
			this->TBOptFileSavePrecInt32->CheckOnClick = true;
			this->TBOptFileSavePrecInt32->Name = L"TBOptFileSavePrecInt32";
			this->TBOptFileSavePrecInt32->Size = System::Drawing::Size(112, 22);
			this->TBOptFileSavePrecInt32->Text = L"Int32";
			this->TBOptFileSavePrecInt32->Click += gcnew System::EventHandler(this, &Form1::TBOptFileSavePrecInt32_Click);
			// 
			// TBOptFileSavePrecInt16
			// 
			this->TBOptFileSavePrecInt16->CheckOnClick = true;
			this->TBOptFileSavePrecInt16->Name = L"TBOptFileSavePrecInt16";
			this->TBOptFileSavePrecInt16->Size = System::Drawing::Size(112, 22);
			this->TBOptFileSavePrecInt16->Text = L"Int16";
			this->TBOptFileSavePrecInt16->Click += gcnew System::EventHandler(this, &Form1::TBOptFileSavePrecInt16_Click);
			// 
			// TBOptFileSavePrecUInt16
			// 
			this->TBOptFileSavePrecUInt16->CheckOnClick = true;
			this->TBOptFileSavePrecUInt16->Name = L"TBOptFileSavePrecUInt16";
			this->TBOptFileSavePrecUInt16->Size = System::Drawing::Size(112, 22);
			this->TBOptFileSavePrecUInt16->Text = L"UInt16";
			this->TBOptFileSavePrecUInt16->Click += gcnew System::EventHandler(this, &Form1::TBOptFileSavePrecUInt16_Click);
			// 
			// TBZipAllBtn
			// 
			this->TBZipAllBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBZipAllBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->TBZipMoveChck,
					this->TBZipCopyChck
			});
			this->TBZipAllBtn->Enabled = false;
			this->TBZipAllBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBZipAllBtn.Image")));
			this->TBZipAllBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBZipAllBtn->Name = L"TBZipAllBtn";
			this->TBZipAllBtn->Size = System::Drawing::Size(31, 20);
			this->TBZipAllBtn->Text = L"Save All into Archive";
			this->TBZipAllBtn->ButtonClick += gcnew System::EventHandler(this, &Form1::TBZipAllBtn_Click);
			// 
			// TBZipMoveChck
			// 
			this->TBZipMoveChck->CheckOnClick = true;
			this->TBZipMoveChck->Name = L"TBZipMoveChck";
			this->TBZipMoveChck->Size = System::Drawing::Size(171, 22);
			this->TBZipMoveChck->Text = L"Move into Archive";
			this->TBZipMoveChck->Click += gcnew System::EventHandler(this, &Form1::TBZipMoveChck_Click);
			// 
			// TBZipCopyChck
			// 
			this->TBZipCopyChck->CheckOnClick = true;
			this->TBZipCopyChck->Name = L"TBZipCopyChck";
			this->TBZipCopyChck->Size = System::Drawing::Size(171, 22);
			this->TBZipCopyChck->Text = L"Copy into Archive";
			this->TBZipCopyChck->Click += gcnew System::EventHandler(this, &Form1::TBZipCopyChck_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(31, 6);
			// 
			// TBQuit
			// 
			this->TBQuit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->TBQuit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TBQuit.Image")));
			this->TBQuit->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->TBQuit->Name = L"TBQuit";
			this->TBQuit->Size = System::Drawing::Size(31, 20);
			this->TBQuit->Text = L"Quit!";
			this->TBQuit->Click += gcnew System::EventHandler(this, &Form1::FMQuit_Click);
			// 
			// ProgressBar
			// 
			this->ProgressBar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->ProgressBar->Location = System::Drawing::Point(0, 872);
			this->ProgressBar->Name = L"ProgressBar";
			this->ProgressBar->Size = System::Drawing::Size(1424, 16);
			this->ProgressBar->Step = 1;
			this->ProgressBar->TabIndex = 24;
			// 
			// Tooltip
			// 
			this->Tooltip->AutomaticDelay = 100;
			this->Tooltip->AutoPopDelay = 8500;
			this->Tooltip->InitialDelay = 100;
			this->Tooltip->ReshowDelay = 100;
			this->Tooltip->ShowAlways = true;
			this->Tooltip->UseFading = false;
			this->Tooltip->Popup += gcnew System::Windows::Forms::PopupEventHandler(this, &Form1::Tooltip_Popup);
			// 
			// BatchStdvChck
			// 
			this->BatchStdvChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BatchStdvChck->Location = System::Drawing::Point(6, 70);
			this->BatchStdvChck->Name = L"BatchStdvChck";
			this->BatchStdvChck->Size = System::Drawing::Size(64, 16);
			this->BatchStdvChck->TabIndex = 5;
			this->BatchStdvChck->Text = L"Stdv";
			this->Tooltip->SetToolTip(this->BatchStdvChck, L"Compute the Standard Deviation Image of the Image Set");
			this->BatchStdvChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchStdvChck_CheckedChanged);
			// 
			// BatchMedianChck
			// 
			this->BatchMedianChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BatchMedianChck->Location = System::Drawing::Point(6, 46);
			this->BatchMedianChck->Name = L"BatchMedianChck";
			this->BatchMedianChck->Size = System::Drawing::Size(64, 16);
			this->BatchMedianChck->TabIndex = 4;
			this->BatchMedianChck->Text = L"Median";
			this->Tooltip->SetToolTip(this->BatchMedianChck, L"Compute the Median Image of the Image Set");
			this->BatchMedianChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchMedianChck_CheckedChanged);
			// 
			// BatchMeanChck
			// 
			this->BatchMeanChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BatchMeanChck->Location = System::Drawing::Point(6, 22);
			this->BatchMeanChck->Name = L"BatchMeanChck";
			this->BatchMeanChck->Size = System::Drawing::Size(58, 16);
			this->BatchMeanChck->TabIndex = 3;
			this->BatchMeanChck->Text = L"Mean";
			this->Tooltip->SetToolTip(this->BatchMeanChck, L"Compute the Mean (or Sigma Clipped Mean) Image of the Image Set");
			this->BatchMeanChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchMeanChck_CheckedChanged);
			// 
			// BatchCorrectionChck
			// 
			this->BatchCorrectionChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BatchCorrectionChck->Location = System::Drawing::Point(11, 19);
			this->BatchCorrectionChck->Name = L"BatchCorrectionChck";
			this->BatchCorrectionChck->Size = System::Drawing::Size(64, 16);
			this->BatchCorrectionChck->TabIndex = 0;
			this->BatchCorrectionChck->Text = L"Batch\?";
			this->Tooltip->SetToolTip(this->BatchCorrectionChck, L"Applies Correction to all Images in Set;  Default Checked when more than One Imag"
				L"e Loaded");
				// 
				// UVViewNextBtn
				// 
			this->UVViewNextBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UVViewNextBtn.BackgroundImage")));
			this->UVViewNextBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->UVViewNextBtn->Cursor = System::Windows::Forms::Cursors::PanEast;
			this->UVViewNextBtn->Location = System::Drawing::Point(105, 34);
			this->UVViewNextBtn->Name = L"UVViewNextBtn";
			this->UVViewNextBtn->Size = System::Drawing::Size(40, 38);
			this->UVViewNextBtn->TabIndex = 20;
			this->Tooltip->SetToolTip(this->UVViewNextBtn, L"View Next File");
			this->UVViewNextBtn->Click += gcnew System::EventHandler(this, &Form1::UVViewNextBtn_Click);
			// 
			// UVViewLastBtn
			// 
			this->UVViewLastBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UVViewLastBtn.BackgroundImage")));
			this->UVViewLastBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->UVViewLastBtn->Cursor = System::Windows::Forms::Cursors::PanWest;
			this->UVViewLastBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->UVViewLastBtn->Location = System::Drawing::Point(16, 34);
			this->UVViewLastBtn->Name = L"UVViewLastBtn";
			this->UVViewLastBtn->Size = System::Drawing::Size(40, 38);
			this->UVViewLastBtn->TabIndex = 21;
			this->Tooltip->SetToolTip(this->UVViewLastBtn, L"View Previous File");
			this->UVViewLastBtn->Click += gcnew System::EventHandler(this, &Form1::UVViewLastBtn_Click);
			// 
			// BatchSumChck
			// 
			this->BatchSumChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BatchSumChck->Location = System::Drawing::Point(6, 94);
			this->BatchSumChck->Name = L"BatchSumChck";
			this->BatchSumChck->Size = System::Drawing::Size(64, 16);
			this->BatchSumChck->TabIndex = 45;
			this->BatchSumChck->Text = L"Sum";
			this->Tooltip->SetToolTip(this->BatchSumChck, L"Compute the Sum Image of the Image Set");
			this->BatchSumChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchSumChck_CheckedChanged);
			// 
			// UVOpenDirBtn
			// 
			this->UVOpenDirBtn->AutoSize = true;
			this->UVOpenDirBtn->Location = System::Drawing::Point(7, 40);
			this->UVOpenDirBtn->Name = L"UVOpenDirBtn";
			this->UVOpenDirBtn->Size = System::Drawing::Size(120, 25);
			this->UVOpenDirBtn->TabIndex = 38;
			this->UVOpenDirBtn->Text = L"Select UVIT Directory";
			this->Tooltip->SetToolTip(this->UVOpenDirBtn, L"Open Directory of UVIT Raw Files");
			this->UVOpenDirBtn->UseVisualStyleBackColor = true;
			this->UVOpenDirBtn->Click += gcnew System::EventHandler(this, &Form1::UVOpenDirBtn_Click);
			// 
			// PSETab
			// 
			this->PSETab->BackColor = System::Drawing::Color::Gainsboro;
			this->PSETab->Controls->Add(this->ROIOnlyPnl);
			this->PSETab->Controls->Add(this->PSEFitResultListBox);
			this->PSETab->Controls->Add(this->FindSourcesPnl);
			this->PSETab->Location = System::Drawing::Point(4, 22);
			this->PSETab->Name = L"PSETab";
			this->PSETab->Padding = System::Windows::Forms::Padding(3);
			this->PSETab->Size = System::Drawing::Size(317, 501);
			this->PSETab->TabIndex = 4;
			this->PSETab->Text = L"PSE";
			this->Tooltip->SetToolTip(this->PSETab, L"Point Source Extraction");
			// 
			// ROIOnlyPnl
			// 
			this->ROIOnlyPnl->BackColor = System::Drawing::Color::LightGray;
			this->ROIOnlyPnl->Controls->Add(this->SubImgROITab);
			this->ROIOnlyPnl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ROIOnlyPnl->Location = System::Drawing::Point(6, 198);
			this->ROIOnlyPnl->Name = L"ROIOnlyPnl";
			this->ROIOnlyPnl->Size = System::Drawing::Size(305, 120);
			this->ROIOnlyPnl->TabIndex = 3;
			this->ROIOnlyPnl->TabStop = false;
			this->ROIOnlyPnl->Text = L"Sub Image Region of Interest";
			// 
			// SubImgROITab
			// 
			this->SubImgROITab->Controls->Add(this->ROIFitTab);
			this->SubImgROITab->Controls->Add(this->ROICOGTab);
			this->SubImgROITab->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SubImgROITab->Location = System::Drawing::Point(6, 18);
			this->SubImgROITab->Name = L"SubImgROITab";
			this->SubImgROITab->SelectedIndex = 0;
			this->SubImgROITab->Size = System::Drawing::Size(293, 100);
			this->SubImgROITab->TabIndex = 54;
			this->SubImgROITab->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::SubImgROITab_SelectedIndexChanged);
			// 
			// ROIFitTab
			// 
			this->ROIFitTab->BackColor = System::Drawing::Color::Gainsboro;
			this->ROIFitTab->Controls->Add(this->SetParametersChck);
			this->ROIFitTab->Controls->Add(this->ROIFitFcnLabel);
			this->ROIFitTab->Controls->Add(this->ROIFitFcnDrop);
			this->ROIFitTab->Controls->Add(this->ROIFitBtn);
			this->ROIFitTab->Controls->Add(this->ROIViewFitChck);
			this->ROIFitTab->Location = System::Drawing::Point(4, 22);
			this->ROIFitTab->Name = L"ROIFitTab";
			this->ROIFitTab->Padding = System::Windows::Forms::Padding(3);
			this->ROIFitTab->Size = System::Drawing::Size(285, 74);
			this->ROIFitTab->TabIndex = 0;
			this->ROIFitTab->Text = L"Fit";
			// 
			// SetParametersChck
			// 
			this->SetParametersChck->AutoSize = true;
			this->SetParametersChck->Location = System::Drawing::Point(157, 24);
			this->SetParametersChck->Name = L"SetParametersChck";
			this->SetParametersChck->Size = System::Drawing::Size(112, 17);
			this->SetParametersChck->TabIndex = 4;
			this->SetParametersChck->Text = L"Set Fit Parameters";
			this->SetParametersChck->UseVisualStyleBackColor = true;
			this->SetParametersChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::SetParametersChck_CheckedChanged);
			// 
			// ROIFitFcnLabel
			// 
			this->ROIFitFcnLabel->AutoSize = true;
			this->ROIFitFcnLabel->Location = System::Drawing::Point(6, 6);
			this->ROIFitFcnLabel->Name = L"ROIFitFcnLabel";
			this->ROIFitFcnLabel->Size = System::Drawing::Size(62, 13);
			this->ROIFitFcnLabel->TabIndex = 3;
			this->ROIFitFcnLabel->Text = L"Fit Function";
			// 
			// ROIFitFcnDrop
			// 
			this->ROIFitFcnDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ROIFitFcnDrop->FormattingEnabled = true;
			this->ROIFitFcnDrop->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Gaussian (2-D Circular)", L"Gaussian (2-D Elliptical)",
					L"Moffat (2-D Circular)", L"Moffat (2-D Elliptical)"
			});
			this->ROIFitFcnDrop->Location = System::Drawing::Point(5, 22);
			this->ROIFitFcnDrop->Name = L"ROIFitFcnDrop";
			this->ROIFitFcnDrop->Size = System::Drawing::Size(146, 21);
			this->ROIFitFcnDrop->TabIndex = 0;
			this->ROIFitFcnDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ROIFitFcnDrop_SelectedIndexChanged);
			// 
			// ROIFitBtn
			// 
			this->ROIFitBtn->Location = System::Drawing::Point(188, 47);
			this->ROIFitBtn->Name = L"ROIFitBtn";
			this->ROIFitBtn->Size = System::Drawing::Size(75, 23);
			this->ROIFitBtn->TabIndex = 2;
			this->ROIFitBtn->Text = L"Fit";
			this->ROIFitBtn->UseVisualStyleBackColor = true;
			this->ROIFitBtn->Click += gcnew System::EventHandler(this, &Form1::ROIFitBtn_Click);
			// 
			// ROIViewFitChck
			// 
			this->ROIViewFitChck->AutoSize = true;
			this->ROIViewFitChck->Location = System::Drawing::Point(6, 49);
			this->ROIViewFitChck->Name = L"ROIViewFitChck";
			this->ROIViewFitChck->Size = System::Drawing::Size(69, 17);
			this->ROIViewFitChck->TabIndex = 1;
			this->ROIViewFitChck->Text = L"View Fit\?";
			this->ROIViewFitChck->UseVisualStyleBackColor = true;
			// 
			// ROICOGTab
			// 
			this->ROICOGTab->BackColor = System::Drawing::Color::Gainsboro;
			this->ROICOGTab->Controls->Add(this->COGBatchChck);
			this->ROICOGTab->Controls->Add(this->COGViewChck);
			this->ROICOGTab->Controls->Add(this->COGBtn);
			this->ROICOGTab->Controls->Add(this->COGIgnoreNPtsUpD);
			this->ROICOGTab->Controls->Add(this->label32);
			this->ROICOGTab->Location = System::Drawing::Point(4, 22);
			this->ROICOGTab->Name = L"ROICOGTab";
			this->ROICOGTab->Padding = System::Windows::Forms::Padding(3);
			this->ROICOGTab->Size = System::Drawing::Size(285, 74);
			this->ROICOGTab->TabIndex = 1;
			this->ROICOGTab->Text = L"COG";
			// 
			// COGBatchChck
			// 
			this->COGBatchChck->AutoSize = true;
			this->COGBatchChck->Location = System::Drawing::Point(225, 29);
			this->COGBatchChck->Name = L"COGBatchChck";
			this->COGBatchChck->Size = System::Drawing::Size(54, 17);
			this->COGBatchChck->TabIndex = 4;
			this->COGBatchChck->Text = L"Batch";
			this->COGBatchChck->UseVisualStyleBackColor = true;
			// 
			// COGViewChck
			// 
			this->COGViewChck->AutoSize = true;
			this->COGViewChck->Location = System::Drawing::Point(204, 6);
			this->COGViewChck->Name = L"COGViewChck";
			this->COGViewChck->Size = System::Drawing::Size(75, 17);
			this->COGViewChck->TabIndex = 3;
			this->COGViewChck->Text = L"View COG";
			this->COGViewChck->UseVisualStyleBackColor = true;
			// 
			// COGBtn
			// 
			this->COGBtn->Location = System::Drawing::Point(207, 48);
			this->COGBtn->Name = L"COGBtn";
			this->COGBtn->Size = System::Drawing::Size(75, 23);
			this->COGBtn->TabIndex = 2;
			this->COGBtn->Text = L"Do COG";
			this->COGBtn->UseVisualStyleBackColor = true;
			this->COGBtn->Click += gcnew System::EventHandler(this, &Form1::COGBtn_Click);
			// 
			// COGIgnoreNPtsUpD
			// 
			this->COGIgnoreNPtsUpD->Location = System::Drawing::Point(153, 6);
			this->COGIgnoreNPtsUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->COGIgnoreNPtsUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->COGIgnoreNPtsUpD->Name = L"COGIgnoreNPtsUpD";
			this->COGIgnoreNPtsUpD->Size = System::Drawing::Size(38, 20);
			this->COGIgnoreNPtsUpD->TabIndex = 0;
			this->Tooltip->SetToolTip(this->COGIgnoreNPtsUpD, L"Uses a robust linear fit.");
			this->COGIgnoreNPtsUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(50, 8);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(105, 13);
			this->label32->TabIndex = 1;
			this->label32->Text = L"Fit the Last N Points:";
			// 
			// PSEFitResultListBox
			// 
			this->PSEFitResultListBox->ContextMenuStrip = this->PSEFitResultsCntxt;
			this->PSEFitResultListBox->FormattingEnabled = true;
			this->PSEFitResultListBox->Location = System::Drawing::Point(6, 320);
			this->PSEFitResultListBox->Name = L"PSEFitResultListBox";
			this->PSEFitResultListBox->Size = System::Drawing::Size(305, 173);
			this->PSEFitResultListBox->TabIndex = 2;
			this->PSEFitResultListBox->UseTabStops = false;
			this->PSEFitResultListBox->Visible = false;
			this->PSEFitResultListBox->MouseEnter += gcnew System::EventHandler(this, &Form1::PSEFitResultListBox_MouseEnter);
			// 
			// PSEFitResultsCntxt
			// 
			this->PSEFitResultsCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->PSEFitResultCntxtCopySelected,
					this->PSEFitResultCntxtCopyAll
			});
			this->PSEFitResultsCntxt->Name = L"PSEFitResultsCntxt";
			this->PSEFitResultsCntxt->Size = System::Drawing::Size(150, 48);
			this->PSEFitResultsCntxt->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::PSEFitResultsCntxt_Opening);
			// 
			// PSEFitResultCntxtCopySelected
			// 
			this->PSEFitResultCntxtCopySelected->Name = L"PSEFitResultCntxtCopySelected";
			this->PSEFitResultCntxtCopySelected->Size = System::Drawing::Size(149, 22);
			this->PSEFitResultCntxtCopySelected->Text = L"Copy Selected";
			this->PSEFitResultCntxtCopySelected->Click += gcnew System::EventHandler(this, &Form1::PSEFitResultCntxtCopySelected_Click);
			// 
			// PSEFitResultCntxtCopyAll
			// 
			this->PSEFitResultCntxtCopyAll->Name = L"PSEFitResultCntxtCopyAll";
			this->PSEFitResultCntxtCopyAll->Size = System::Drawing::Size(149, 22);
			this->PSEFitResultCntxtCopyAll->Text = L"Copy All";
			this->PSEFitResultCntxtCopyAll->Click += gcnew System::EventHandler(this, &Form1::PSEFitResultCntxtCopyAll_Click);
			// 
			// FindSourcesPnl
			// 
			this->FindSourcesPnl->BackColor = System::Drawing::Color::LightGray;
			this->FindSourcesPnl->Controls->Add(this->PSESigmaCountBtn);
			this->FindSourcesPnl->Controls->Add(this->PSEDrop);
			this->FindSourcesPnl->Controls->Add(this->PSEDrawROI);
			this->FindSourcesPnl->Controls->Add(this->PSESaturationUpD);
			this->FindSourcesPnl->Controls->Add(this->label24);
			this->FindSourcesPnl->Controls->Add(this->PSEClearBtn);
			this->FindSourcesPnl->Controls->Add(this->PSETableViewBtn);
			this->FindSourcesPnl->Controls->Add(this->PSESeparationUpD);
			this->FindSourcesPnl->Controls->Add(this->label20);
			this->FindSourcesPnl->Controls->Add(this->PSELoadSrcDrop);
			this->FindSourcesPnl->Controls->Add(this->label3);
			this->FindSourcesPnl->Controls->Add(this->PSEEllipticalROI);
			this->FindSourcesPnl->Controls->Add(this->PSESeachROIOnlyChck);
			this->FindSourcesPnl->Controls->Add(this->PSEKernelRadUpD);
			this->FindSourcesPnl->Controls->Add(this->PSEAutoBackgroundChck);
			this->FindSourcesPnl->Controls->Add(this->SavePSChck);
			this->FindSourcesPnl->Controls->Add(this->label26);
			this->FindSourcesPnl->Controls->Add(this->PSEFitTypeChck);
			this->FindSourcesPnl->Controls->Add(this->PSEKernelMinUpD);
			this->FindSourcesPnl->Controls->Add(this->PSEViewFitChck);
			this->FindSourcesPnl->Controls->Add(this->PSEKernelMaxUpD);
			this->FindSourcesPnl->Controls->Add(this->PSEFitChck);
			this->FindSourcesPnl->Controls->Add(this->label27);
			this->FindSourcesPnl->Controls->Add(this->PSEFindSrcBtn);
			this->FindSourcesPnl->Controls->Add(this->PSEPixelCntLbl);
			this->FindSourcesPnl->Controls->Add(this->PSEPixelValLbl);
			this->FindSourcesPnl->Controls->Add(this->label23);
			this->FindSourcesPnl->Controls->Add(this->label22);
			this->FindSourcesPnl->Controls->Add(this->PSEPixelMaxUpD);
			this->FindSourcesPnl->Controls->Add(this->PSEPixelMinUpD);
			this->FindSourcesPnl->Controls->Add(this->label21);
			this->FindSourcesPnl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FindSourcesPnl->Location = System::Drawing::Point(6, 6);
			this->FindSourcesPnl->Name = L"FindSourcesPnl";
			this->FindSourcesPnl->Size = System::Drawing::Size(305, 190);
			this->FindSourcesPnl->TabIndex = 0;
			this->FindSourcesPnl->TabStop = false;
			this->FindSourcesPnl->Text = L"Point Source Extraction";
			// 
			// PSESigmaCountBtn
			// 
			this->PSESigmaCountBtn->Location = System::Drawing::Point(104, 103);
			this->PSESigmaCountBtn->Name = L"PSESigmaCountBtn";
			this->PSESigmaCountBtn->Size = System::Drawing::Size(58, 22);
			this->PSESigmaCountBtn->TabIndex = 14;
			this->PSESigmaCountBtn->Text = L"SN";
			this->PSESigmaCountBtn->UseVisualStyleBackColor = true;
			this->PSESigmaCountBtn->Click += gcnew System::EventHandler(this, &Form1::PSESigmaCountBtn_Click);
			// 
			// PSEDrop
			// 
			this->PSEDrop->ContextMenuStrip = this->PSEDropContextMenu;
			this->PSEDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PSEDrop->Enabled = false;
			this->PSEDrop->FormattingEnabled = true;
			this->PSEDrop->Location = System::Drawing::Point(9, 15);
			this->PSEDrop->Name = L"PSEDrop";
			this->PSEDrop->Size = System::Drawing::Size(85, 21);
			this->PSEDrop->TabIndex = 59;
			this->PSEDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PSEDrop_SelectedIndexChanged);
			// 
			// PSEDropContextMenu
			// 
			this->PSEDropContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->PSEDropContextAdd,
					this->PSEDropContextRemove, this->PSEDropContextPlotAll, this->PSEDropContextClearAll
			});
			this->PSEDropContextMenu->Name = L"PSEDropContextMenu";
			this->PSEDropContextMenu->Size = System::Drawing::Size(181, 114);
			// 
			// PSEDropContextAdd
			// 
			this->PSEDropContextAdd->Name = L"PSEDropContextAdd";
			this->PSEDropContextAdd->Size = System::Drawing::Size(180, 22);
			this->PSEDropContextAdd->Text = L"Add New PSE";
			this->PSEDropContextAdd->Click += gcnew System::EventHandler(this, &Form1::PSEDropContextAdd_Click);
			// 
			// PSEDropContextRemove
			// 
			this->PSEDropContextRemove->Name = L"PSEDropContextRemove";
			this->PSEDropContextRemove->Size = System::Drawing::Size(180, 22);
			this->PSEDropContextRemove->Text = L"Remove PSE";
			this->PSEDropContextRemove->Click += gcnew System::EventHandler(this, &Form1::PSEDropContextRemove_Click);
			// 
			// PSEDropContextClearAll
			// 
			this->PSEDropContextClearAll->Name = L"PSEDropContextClearAll";
			this->PSEDropContextClearAll->Size = System::Drawing::Size(180, 22);
			this->PSEDropContextClearAll->Text = L"Clear All";
			this->PSEDropContextClearAll->Click += gcnew System::EventHandler(this, &Form1::PSEDropContextClearAll_Click);
			// 
			// PSEDrawROI
			// 
			this->PSEDrawROI->AutoSize = true;
			this->PSEDrawROI->ContextMenuStrip = this->DrawROIContextMenu;
			this->PSEDrawROI->Enabled = false;
			this->PSEDrawROI->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEDrawROI->Location = System::Drawing::Point(210, 22);
			this->PSEDrawROI->Name = L"PSEDrawROI";
			this->PSEDrawROI->Size = System::Drawing::Size(73, 17);
			this->PSEDrawROI->TabIndex = 63;
			this->PSEDrawROI->Text = L"Draw ROI";
			this->PSEDrawROI->UseVisualStyleBackColor = true;
			this->PSEDrawROI->CheckedChanged += gcnew System::EventHandler(this, &Form1::PSEDrawROI_CheckedChanged);
			// 
			// DrawROIContextMenu
			// 
			this->DrawROIContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->SaveROIContext,
					this->LoadROIContext
			});
			this->DrawROIContextMenu->Name = L"DrawROIContextMenu";
			this->DrawROIContextMenu->Size = System::Drawing::Size(123, 48);
			// 
			// SaveROIContext
			// 
			this->SaveROIContext->Name = L"SaveROIContext";
			this->SaveROIContext->Size = System::Drawing::Size(122, 22);
			this->SaveROIContext->Text = L"Save ROI";
			this->SaveROIContext->Click += gcnew System::EventHandler(this, &Form1::SaveROIContext_Click);
			// 
			// LoadROIContext
			// 
			this->LoadROIContext->Name = L"LoadROIContext";
			this->LoadROIContext->Size = System::Drawing::Size(122, 22);
			this->LoadROIContext->Text = L"Load ROI";
			this->LoadROIContext->Click += gcnew System::EventHandler(this, &Form1::LoadROIContext_Click);
			// 
			// PSESaturationUpD
			// 
			this->PSESaturationUpD->DecimalPlaces = 3;
			this->PSESaturationUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PSESaturationUpD->Location = System::Drawing::Point(217, 83);
			this->PSESaturationUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1410065407, 2, 0, 196608 });
			this->PSESaturationUpD->Name = L"PSESaturationUpD";
			this->PSESaturationUpD->Size = System::Drawing::Size(84, 20);
			this->PSESaturationUpD->TabIndex = 62;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->Location = System::Drawing::Point(132, 85);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(83, 13);
			this->label24->TabIndex = 61;
			this->label24->Text = L"Pixel Saturation:";
			// 
			// PSEClearBtn
			// 
			this->PSEClearBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEClearBtn->Location = System::Drawing::Point(186, 166);
			this->PSEClearBtn->Name = L"PSEClearBtn";
			this->PSEClearBtn->Size = System::Drawing::Size(46, 23);
			this->PSEClearBtn->TabIndex = 18;
			this->PSEClearBtn->Text = L"Clear";
			this->PSEClearBtn->UseVisualStyleBackColor = true;
			this->PSEClearBtn->Click += gcnew System::EventHandler(this, &Form1::PSEClearBtn_Click);
			// 
			// PSETableViewBtn
			// 
			this->PSETableViewBtn->Enabled = false;
			this->PSETableViewBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSETableViewBtn->Location = System::Drawing::Point(143, 155);
			this->PSETableViewBtn->Name = L"PSETableViewBtn";
			this->PSETableViewBtn->Size = System::Drawing::Size(42, 34);
			this->PSETableViewBtn->TabIndex = 16;
			this->PSETableViewBtn->Text = L"View Table";
			this->PSETableViewBtn->UseVisualStyleBackColor = true;
			this->PSETableViewBtn->Click += gcnew System::EventHandler(this, &Form1::PSETableViewBtn_Click);
			// 
			// PSESeparationUpD
			// 
			this->PSESeparationUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PSESeparationUpD->Location = System::Drawing::Point(261, 105);
			this->PSESeparationUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->PSESeparationUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PSESeparationUpD->Name = L"PSESeparationUpD";
			this->PSESeparationUpD->Size = System::Drawing::Size(40, 20);
			this->PSESeparationUpD->TabIndex = 59;
			this->PSESeparationUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(166, 107);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(98, 13);
			this->label20->TabIndex = 60;
			this->label20->Text = L"Source Separation:";
			// 
			// PSELoadSrcDrop
			// 
			this->PSELoadSrcDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PSELoadSrcDrop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSELoadSrcDrop->FormattingEnabled = true;
			this->PSELoadSrcDrop->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"[RA,Dec ...] list", L"[X, Y ...] list" });
			this->PSELoadSrcDrop->Location = System::Drawing::Point(58, 166);
			this->PSELoadSrcDrop->Name = L"PSELoadSrcDrop";
			this->PSELoadSrcDrop->Size = System::Drawing::Size(82, 21);
			this->PSELoadSrcDrop->TabIndex = 55;
			this->PSELoadSrcDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PSELoadSrcBtn_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(8, 170);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 58;
			this->label3->Text = L"Load List:";
			// 
			// PSEEllipticalROI
			// 
			this->PSEEllipticalROI->AutoSize = true;
			this->PSEEllipticalROI->Enabled = false;
			this->PSEEllipticalROI->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PSEEllipticalROI->Location = System::Drawing::Point(210, 8);
			this->PSEEllipticalROI->Name = L"PSEEllipticalROI";
			this->PSEEllipticalROI->Size = System::Drawing::Size(86, 17);
			this->PSEEllipticalROI->TabIndex = 17;
			this->PSEEllipticalROI->Text = L"Elliptical ROI";
			this->PSEEllipticalROI->UseVisualStyleBackColor = true;
			this->PSEEllipticalROI->CheckedChanged += gcnew System::EventHandler(this, &Form1::PSEEllipticalROI_CheckedChanged);
			// 
			// PSESeachROIOnlyChck
			// 
			this->PSESeachROIOnlyChck->AutoSize = true;
			this->PSESeachROIOnlyChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PSESeachROIOnlyChck->Location = System::Drawing::Point(101, 15);
			this->PSESeachROIOnlyChck->Name = L"PSESeachROIOnlyChck";
			this->PSESeachROIOnlyChck->Size = System::Drawing::Size(106, 17);
			this->PSESeachROIOnlyChck->TabIndex = 15;
			this->PSESeachROIOnlyChck->Text = L"Search ROI Only";
			this->PSESeachROIOnlyChck->UseVisualStyleBackColor = true;
			this->PSESeachROIOnlyChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::PSESeachROIOnlyChck_CheckedChanged);
			// 
			// PSEKernelRadUpD
			// 
			this->PSEKernelRadUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEKernelRadUpD->Location = System::Drawing::Point(261, 128);
			this->PSEKernelRadUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->PSEKernelRadUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->PSEKernelRadUpD->Name = L"PSEKernelRadUpD";
			this->PSEKernelRadUpD->Size = System::Drawing::Size(40, 20);
			this->PSEKernelRadUpD->TabIndex = 4;
			this->PSEKernelRadUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->PSEKernelRadUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::PSEWidthUpD_ValueChanged);
			// 
			// PSEAutoBackgroundChck
			// 
			this->PSEAutoBackgroundChck->AutoSize = true;
			this->PSEAutoBackgroundChck->Checked = true;
			this->PSEAutoBackgroundChck->CheckState = System::Windows::Forms::CheckState::Checked;
			this->PSEAutoBackgroundChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PSEAutoBackgroundChck->Location = System::Drawing::Point(9, 86);
			this->PSEAutoBackgroundChck->Name = L"PSEAutoBackgroundChck";
			this->PSEAutoBackgroundChck->Size = System::Drawing::Size(109, 17);
			this->PSEAutoBackgroundChck->TabIndex = 10;
			this->PSEAutoBackgroundChck->Text = L"Auto Background";
			this->PSEAutoBackgroundChck->UseVisualStyleBackColor = true;
			// 
			// SavePSChck
			// 
			this->SavePSChck->AutoSize = true;
			this->SavePSChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SavePSChck->Location = System::Drawing::Point(9, 106);
			this->SavePSChck->Name = L"SavePSChck";
			this->SavePSChck->Size = System::Drawing::Size(89, 17);
			this->SavePSChck->TabIndex = 12;
			this->SavePSChck->Text = L"Save Kernels";
			this->SavePSChck->UseVisualStyleBackColor = true;
			this->SavePSChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::SavePSChck_CheckedChanged);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->Location = System::Drawing::Point(69, 66);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(27, 13);
			this->label26->TabIndex = 8;
			this->label26->Text = L"Min:";
			// 
			// PSEFitTypeChck
			// 
			this->PSEFitTypeChck->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PSEFitTypeChck->Enabled = false;
			this->PSEFitTypeChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEFitTypeChck->FormattingEnabled = true;
			this->PSEFitTypeChck->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Gaussian (2-D Circular)", L"Gaussian (2-D Elliptical)",
					L"Moffat (2-D Circular)", L"Moffat (2-D Elliptical)"
			});
			this->PSEFitTypeChck->Location = System::Drawing::Point(10, 143);
			this->PSEFitTypeChck->Name = L"PSEFitTypeChck";
			this->PSEFitTypeChck->Size = System::Drawing::Size(127, 21);
			this->PSEFitTypeChck->TabIndex = 11;
			this->PSEFitTypeChck->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PSEFitTypeChck_SelectedIndexChanged);
			this->PSEFitTypeChck->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::PSEFitTypeChck_MouseClick);
			// 
			// PSEKernelMinUpD
			// 
			this->PSEKernelMinUpD->DecimalPlaces = 3;
			this->PSEKernelMinUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEKernelMinUpD->Location = System::Drawing::Point(98, 62);
			this->PSEKernelMinUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000000, 0, 0, 0 });
			this->PSEKernelMinUpD->Name = L"PSEKernelMinUpD";
			this->PSEKernelMinUpD->Size = System::Drawing::Size(84, 20);
			this->PSEKernelMinUpD->TabIndex = 6;
			// 
			// PSEViewFitChck
			// 
			this->PSEViewFitChck->AutoSize = true;
			this->PSEViewFitChck->Enabled = false;
			this->PSEViewFitChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEViewFitChck->Location = System::Drawing::Point(92, 126);
			this->PSEViewFitChck->Name = L"PSEViewFitChck";
			this->PSEViewFitChck->Size = System::Drawing::Size(74, 17);
			this->PSEViewFitChck->TabIndex = 9;
			this->PSEViewFitChck->Text = L"View Fits\?";
			this->PSEViewFitChck->UseVisualStyleBackColor = true;
			// 
			// PSEKernelMaxUpD
			// 
			this->PSEKernelMaxUpD->DecimalPlaces = 3;
			this->PSEKernelMaxUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEKernelMaxUpD->Location = System::Drawing::Point(217, 62);
			this->PSEKernelMaxUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1410065407, 2, 0, 196608 });
			this->PSEKernelMaxUpD->Name = L"PSEKernelMaxUpD";
			this->PSEKernelMaxUpD->Size = System::Drawing::Size(84, 20);
			this->PSEKernelMaxUpD->TabIndex = 7;
			this->PSEKernelMaxUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1410065407, 2, 0, 196608 });
			// 
			// PSEFitChck
			// 
			this->PSEFitChck->AutoSize = true;
			this->PSEFitChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEFitChck->Location = System::Drawing::Point(9, 126);
			this->PSEFitChck->Name = L"PSEFitChck";
			this->PSEFitChck->Size = System::Drawing::Size(85, 17);
			this->PSEFitChck->TabIndex = 7;
			this->PSEFitChck->Text = L"Fit Sources\?";
			this->PSEFitChck->UseVisualStyleBackColor = true;
			this->PSEFitChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::PSEFitChck_CheckedChanged);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->Location = System::Drawing::Point(185, 66);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(30, 13);
			this->label27->TabIndex = 9;
			this->label27->Text = L"Max:";
			// 
			// PSEFindSrcBtn
			// 
			this->PSEFindSrcBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEFindSrcBtn->Location = System::Drawing::Point(233, 166);
			this->PSEFindSrcBtn->Name = L"PSEFindSrcBtn";
			this->PSEFindSrcBtn->Size = System::Drawing::Size(70, 23);
			this->PSEFindSrcBtn->TabIndex = 6;
			this->PSEFindSrcBtn->Text = L"Do PSE!";
			this->Tooltip->SetToolTip(this->PSEFindSrcBtn, L"Right-Click to re-determine pixel metadata (centroids, etc.) for modified image.");
			this->PSEFindSrcBtn->UseVisualStyleBackColor = true;
			this->PSEFindSrcBtn->Click += gcnew System::EventHandler(this, &Form1::PSEFindSrcBtn_Click);
			this->PSEFindSrcBtn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::PSEFindSrcBtn_MouseClick);
			this->PSEFindSrcBtn->MouseEnter += gcnew System::EventHandler(this, &Form1::PSEFindSrcBtn_MouseEnter);
			this->PSEFindSrcBtn->MouseLeave += gcnew System::EventHandler(this, &Form1::PSEFindSrcBtn_MouseLeave);
			this->PSEFindSrcBtn->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::PSEFindSrcBtn_MouseUp);
			// 
			// PSEPixelCntLbl
			// 
			this->PSEPixelCntLbl->AutoSize = true;
			this->PSEPixelCntLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEPixelCntLbl->Location = System::Drawing::Point(6, 66);
			this->PSEPixelCntLbl->Name = L"PSEPixelCntLbl";
			this->PSEPixelCntLbl->Size = System::Drawing::Size(65, 13);
			this->PSEPixelCntLbl->TabIndex = 5;
			this->PSEPixelCntLbl->Text = L"Total Count:";
			// 
			// PSEPixelValLbl
			// 
			this->PSEPixelValLbl->AutoSize = true;
			this->PSEPixelValLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEPixelValLbl->Location = System::Drawing::Point(6, 46);
			this->PSEPixelValLbl->Name = L"PSEPixelValLbl";
			this->PSEPixelValLbl->Size = System::Drawing::Size(62, 13);
			this->PSEPixelValLbl->TabIndex = 4;
			this->PSEPixelValLbl->Text = L"Pixel Value:";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(188, 130);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(76, 13);
			this->label23->TabIndex = 5;
			this->label23->Text = L"Kernel Radius:";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(185, 46);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(30, 13);
			this->label22->TabIndex = 3;
			this->label22->Text = L"Max:";
			// 
			// PSEPixelMaxUpD
			// 
			this->PSEPixelMaxUpD->DecimalPlaces = 3;
			this->PSEPixelMaxUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEPixelMaxUpD->Location = System::Drawing::Point(217, 42);
			this->PSEPixelMaxUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1410065407, 2, 0, 196608 });
			this->PSEPixelMaxUpD->Name = L"PSEPixelMaxUpD";
			this->PSEPixelMaxUpD->Size = System::Drawing::Size(84, 20);
			this->PSEPixelMaxUpD->TabIndex = 1;
			this->PSEPixelMaxUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1410065407, 2, 0, 196608 });
			// 
			// PSEPixelMinUpD
			// 
			this->PSEPixelMinUpD->DecimalPlaces = 3;
			this->PSEPixelMinUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PSEPixelMinUpD->Location = System::Drawing::Point(98, 42);
			this->PSEPixelMinUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000000, 0, 0, 0 });
			this->PSEPixelMinUpD->Name = L"PSEPixelMinUpD";
			this->PSEPixelMinUpD->Size = System::Drawing::Size(84, 20);
			this->PSEPixelMinUpD->TabIndex = 0;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(69, 46);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(27, 13);
			this->label21->TabIndex = 2;
			this->label21->Text = L"Min:";
			// 
			// CutSubImBtn
			// 
			this->CutSubImBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CutSubImBtn.BackgroundImage")));
			this->CutSubImBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->CutSubImBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CutSubImBtn->Location = System::Drawing::Point(71, 122);
			this->CutSubImBtn->Name = L"CutSubImBtn";
			this->CutSubImBtn->Size = System::Drawing::Size(29, 29);
			this->CutSubImBtn->TabIndex = 51;
			this->Tooltip->SetToolTip(this->CutSubImBtn, L"Cut out selected region of interest (cursor box).  RIGHT CLICK to specify range.");
			this->CutSubImBtn->UseVisualStyleBackColor = true;
			this->CutSubImBtn->Click += gcnew System::EventHandler(this, &Form1::CutSubImBtn_Click);
			this->CutSubImBtn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::CutSubImBtn_MouseClick);
			this->CutSubImBtn->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::CutSubImBtn_MouseUp);
			// 
			// RotCCWBtn
			// 
			this->RotCCWBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RotCCWBtn.BackgroundImage")));
			this->RotCCWBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->RotCCWBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RotCCWBtn->Location = System::Drawing::Point(7, 122);
			this->RotCCWBtn->Name = L"RotCCWBtn";
			this->RotCCWBtn->Size = System::Drawing::Size(29, 29);
			this->RotCCWBtn->TabIndex = 50;
			this->Tooltip->SetToolTip(this->RotCCWBtn, L"Rotate image counter-clockwise 90 degrees.");
			this->RotCCWBtn->UseVisualStyleBackColor = true;
			this->RotCCWBtn->Click += gcnew System::EventHandler(this, &Form1::RotCCWBtn_Click);
			// 
			// RotCWBtn
			// 
			this->RotCWBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RotCWBtn.BackgroundImage")));
			this->RotCWBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->RotCWBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RotCWBtn->Location = System::Drawing::Point(7, 92);
			this->RotCWBtn->Name = L"RotCWBtn";
			this->RotCWBtn->Size = System::Drawing::Size(29, 29);
			this->RotCWBtn->TabIndex = 49;
			this->Tooltip->SetToolTip(this->RotCWBtn, L"Rotate image clockwise 90 degrees.");
			this->RotCWBtn->UseVisualStyleBackColor = true;
			this->RotCWBtn->Click += gcnew System::EventHandler(this, &Form1::RotCWBtn_Click);
			// 
			// FlipHorzBtn
			// 
			this->FlipHorzBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FlipHorzBtn.BackgroundImage")));
			this->FlipHorzBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->FlipHorzBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FlipHorzBtn->Location = System::Drawing::Point(39, 92);
			this->FlipHorzBtn->Name = L"FlipHorzBtn";
			this->FlipHorzBtn->Size = System::Drawing::Size(29, 29);
			this->FlipHorzBtn->TabIndex = 47;
			this->Tooltip->SetToolTip(this->FlipHorzBtn, L"Flip image horizontally.");
			this->FlipHorzBtn->UseVisualStyleBackColor = true;
			this->FlipHorzBtn->Click += gcnew System::EventHandler(this, &Form1::FlipHorzBtn_Click);
			// 
			// FlipVertBtn
			// 
			this->FlipVertBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FlipVertBtn.BackgroundImage")));
			this->FlipVertBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->FlipVertBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FlipVertBtn->Location = System::Drawing::Point(39, 122);
			this->FlipVertBtn->Name = L"FlipVertBtn";
			this->FlipVertBtn->Size = System::Drawing::Size(29, 29);
			this->FlipVertBtn->TabIndex = 46;
			this->Tooltip->SetToolTip(this->FlipVertBtn, L"Flip image vertically.");
			this->FlipVertBtn->UseVisualStyleBackColor = true;
			this->FlipVertBtn->Click += gcnew System::EventHandler(this, &Form1::FlipVertBtn_Click);
			// 
			// BatchMinimumChck
			// 
			this->BatchMinimumChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BatchMinimumChck->Location = System::Drawing::Point(71, 46);
			this->BatchMinimumChck->Name = L"BatchMinimumChck";
			this->BatchMinimumChck->Size = System::Drawing::Size(67, 16);
			this->BatchMinimumChck->TabIndex = 46;
			this->BatchMinimumChck->Text = L"Minimum";
			this->Tooltip->SetToolTip(this->BatchMinimumChck, L"Compute the Minimum Image of the Image Set");
			this->BatchMinimumChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchMinimumChck_CheckedChanged);
			// 
			// BatchMaximumChck
			// 
			this->BatchMaximumChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BatchMaximumChck->Location = System::Drawing::Point(71, 70);
			this->BatchMaximumChck->Name = L"BatchMaximumChck";
			this->BatchMaximumChck->Size = System::Drawing::Size(70, 16);
			this->BatchMaximumChck->TabIndex = 47;
			this->BatchMaximumChck->Text = L"Maximum";
			this->Tooltip->SetToolTip(this->BatchMaximumChck, L"Compute the Maximum Image of the Image Set");
			this->BatchMaximumChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchMaximumChck_CheckedChanged);
			// 
			// RotateBtn
			// 
			this->RotateBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RotateBtn.BackgroundImage")));
			this->RotateBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->RotateBtn->ContextMenuStrip = this->RotateBtnCntxt;
			this->RotateBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RotateBtn->Location = System::Drawing::Point(71, 92);
			this->RotateBtn->Name = L"RotateBtn";
			this->RotateBtn->Size = System::Drawing::Size(29, 29);
			this->RotateBtn->TabIndex = 61;
			this->Tooltip->SetToolTip(this->RotateBtn, L"Rotate image by degree angle.");
			this->RotateBtn->UseVisualStyleBackColor = true;
			this->RotateBtn->Click += gcnew System::EventHandler(this, &Form1::RotateBtn_Click);
			// 
			// RotateBtnCntxt
			// 
			this->RotateBtnCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->RotateBtnCntxtNearest,
					this->RotateBtnCntxtBiLinear, this->RotateBtnCntxtLanczos3, this->RotateBtnCntxtLanczos4, this->RotateBtnCntxtLanczos5
			});
			this->RotateBtnCntxt->Name = L"RotateBtnCntxt";
			this->RotateBtnCntxt->Size = System::Drawing::Size(126, 114);
			this->RotateBtnCntxt->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::RotateBtnCntxt_Opening);
			// 
			// RotateBtnCntxtNearest
			// 
			this->RotateBtnCntxtNearest->CheckOnClick = true;
			this->RotateBtnCntxtNearest->Name = L"RotateBtnCntxtNearest";
			this->RotateBtnCntxtNearest->Size = System::Drawing::Size(125, 22);
			this->RotateBtnCntxtNearest->Text = L"Nearest";
			this->RotateBtnCntxtNearest->Click += gcnew System::EventHandler(this, &Form1::RotateBtnCntxtNearest_Click);
			// 
			// RotateBtnCntxtBiLinear
			// 
			this->RotateBtnCntxtBiLinear->CheckOnClick = true;
			this->RotateBtnCntxtBiLinear->Name = L"RotateBtnCntxtBiLinear";
			this->RotateBtnCntxtBiLinear->Size = System::Drawing::Size(125, 22);
			this->RotateBtnCntxtBiLinear->Text = L"BiLinear";
			this->RotateBtnCntxtBiLinear->Click += gcnew System::EventHandler(this, &Form1::RotateBtnCntxtBiLinear_Click);
			// 
			// RotateBtnCntxtLanczos3
			// 
			this->RotateBtnCntxtLanczos3->CheckOnClick = true;
			this->RotateBtnCntxtLanczos3->Name = L"RotateBtnCntxtLanczos3";
			this->RotateBtnCntxtLanczos3->Size = System::Drawing::Size(125, 22);
			this->RotateBtnCntxtLanczos3->Text = L"Lanczos 3";
			this->RotateBtnCntxtLanczos3->Click += gcnew System::EventHandler(this, &Form1::RotateBtnCntxtLanczos3_Click);
			// 
			// RotateBtnCntxtLanczos4
			// 
			this->RotateBtnCntxtLanczos4->CheckOnClick = true;
			this->RotateBtnCntxtLanczos4->Name = L"RotateBtnCntxtLanczos4";
			this->RotateBtnCntxtLanczos4->Size = System::Drawing::Size(125, 22);
			this->RotateBtnCntxtLanczos4->Text = L"Lanczos 4";
			this->RotateBtnCntxtLanczos4->Click += gcnew System::EventHandler(this, &Form1::RotateBtnCntxtLanczos4_Click);
			// 
			// RotateBtnCntxtLanczos5
			// 
			this->RotateBtnCntxtLanczos5->CheckOnClick = true;
			this->RotateBtnCntxtLanczos5->Name = L"RotateBtnCntxtLanczos5";
			this->RotateBtnCntxtLanczos5->Size = System::Drawing::Size(125, 22);
			this->RotateBtnCntxtLanczos5->Text = L"Lanczos 5";
			this->RotateBtnCntxtLanczos5->Click += gcnew System::EventHandler(this, &Form1::RotateBtnCntxtLanczos5_Click);
			// 
			// RotateAngleUpD
			// 
			this->RotateAngleUpD->DecimalPlaces = 2;
			this->RotateAngleUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RotateAngleUpD->Location = System::Drawing::Point(101, 96);
			this->RotateAngleUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 180, 0, 0, 0 });
			this->RotateAngleUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 180, 0, 0, System::Int32::MinValue });
			this->RotateAngleUpD->Name = L"RotateAngleUpD";
			this->RotateAngleUpD->Size = System::Drawing::Size(56, 20);
			this->RotateAngleUpD->TabIndex = 62;
			this->RotateAngleUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->Tooltip->SetToolTip(this->RotateAngleUpD, L"Degrees");
			this->RotateAngleUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::RotateAngleUpD_ValueChanged);
			// 
			// ShiftHorzBtn
			// 
			this->ShiftHorzBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShiftHorzBtn.BackgroundImage")));
			this->ShiftHorzBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ShiftHorzBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ShiftHorzBtn->Location = System::Drawing::Point(163, 92);
			this->ShiftHorzBtn->Name = L"ShiftHorzBtn";
			this->ShiftHorzBtn->Size = System::Drawing::Size(29, 29);
			this->ShiftHorzBtn->TabIndex = 63;
			this->Tooltip->SetToolTip(this->ShiftHorzBtn, L"Shift image horizontally by N pixels.");
			this->ShiftHorzBtn->UseVisualStyleBackColor = true;
			this->ShiftHorzBtn->Click += gcnew System::EventHandler(this, &Form1::ShiftHorzBtn_Click);
			// 
			// ShiftVertBtn
			// 
			this->ShiftVertBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShiftVertBtn.BackgroundImage")));
			this->ShiftVertBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ShiftVertBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ShiftVertBtn->Location = System::Drawing::Point(163, 122);
			this->ShiftVertBtn->Name = L"ShiftVertBtn";
			this->ShiftVertBtn->Size = System::Drawing::Size(29, 29);
			this->ShiftVertBtn->TabIndex = 64;
			this->Tooltip->SetToolTip(this->ShiftVertBtn, L"Shift image vertically by N pixels.");
			this->ShiftVertBtn->UseVisualStyleBackColor = true;
			this->ShiftVertBtn->Click += gcnew System::EventHandler(this, &Form1::ShiftVertBtn_Click);
			// 
			// NShiftHorzUpD
			// 
			this->NShiftHorzUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NShiftHorzUpD->Location = System::Drawing::Point(198, 96);
			this->NShiftHorzUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->NShiftHorzUpD->Name = L"NShiftHorzUpD";
			this->NShiftHorzUpD->Size = System::Drawing::Size(50, 20);
			this->NShiftHorzUpD->TabIndex = 65;
			this->NShiftHorzUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Tooltip->SetToolTip(this->NShiftHorzUpD, L"N Pixels for horizontal shift.");
			this->NShiftHorzUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::NShiftHorzUpD_ValueChanged);
			// 
			// NShiftVertUpD
			// 
			this->NShiftVertUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NShiftVertUpD->Location = System::Drawing::Point(198, 127);
			this->NShiftVertUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->NShiftVertUpD->Name = L"NShiftVertUpD";
			this->NShiftVertUpD->Size = System::Drawing::Size(50, 20);
			this->NShiftVertUpD->TabIndex = 66;
			this->NShiftVertUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Tooltip->SetToolTip(this->NShiftVertUpD, L"N Pixels for vertical shift.");
			this->NShiftVertUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::NShiftVertUpD_ValueChanged);
			// 
			// BatchIndividualAppendageTxt
			// 
			this->BatchIndividualAppendageTxt->Enabled = false;
			this->BatchIndividualAppendageTxt->Location = System::Drawing::Point(74, 28);
			this->BatchIndividualAppendageTxt->Name = L"BatchIndividualAppendageTxt";
			this->BatchIndividualAppendageTxt->Size = System::Drawing::Size(63, 20);
			this->BatchIndividualAppendageTxt->TabIndex = 2;
			this->BatchIndividualAppendageTxt->Text = L"_app";
			this->Tooltip->SetToolTip(this->BatchIndividualAppendageTxt, L"This will be appended on the file names so that new file are written.");
			// 
			// BatchViewNextBtn
			// 
			this->BatchViewNextBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BatchViewNextBtn.BackgroundImage")));
			this->BatchViewNextBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->BatchViewNextBtn->Cursor = System::Windows::Forms::Cursors::PanEast;
			this->BatchViewNextBtn->Location = System::Drawing::Point(95, 19);
			this->BatchViewNextBtn->Name = L"BatchViewNextBtn";
			this->BatchViewNextBtn->Size = System::Drawing::Size(40, 38);
			this->BatchViewNextBtn->TabIndex = 20;
			this->Tooltip->SetToolTip(this->BatchViewNextBtn, L"View Next File");
			this->BatchViewNextBtn->Click += gcnew System::EventHandler(this, &Form1::BatchViewNextBtn_Click);
			// 
			// BatchViewLastBtn
			// 
			this->BatchViewLastBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BatchViewLastBtn.BackgroundImage")));
			this->BatchViewLastBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->BatchViewLastBtn->Cursor = System::Windows::Forms::Cursors::PanWest;
			this->BatchViewLastBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BatchViewLastBtn->Location = System::Drawing::Point(6, 19);
			this->BatchViewLastBtn->Name = L"BatchViewLastBtn";
			this->BatchViewLastBtn->Size = System::Drawing::Size(40, 38);
			this->BatchViewLastBtn->TabIndex = 21;
			this->Tooltip->SetToolTip(this->BatchViewLastBtn, L"View Previous File");
			this->BatchViewLastBtn->Click += gcnew System::EventHandler(this, &Form1::BatchViewLastBtn_Click);
			// 
			// IndividualDirectoryTxt
			// 
			this->IndividualDirectoryTxt->BackColor = System::Drawing::SystemColors::Control;
			this->IndividualDirectoryTxt->DetectUrls = false;
			this->IndividualDirectoryTxt->Enabled = false;
			this->IndividualDirectoryTxt->Location = System::Drawing::Point(6, 51);
			this->IndividualDirectoryTxt->MaxLength = 500;
			this->IndividualDirectoryTxt->Name = L"IndividualDirectoryTxt";
			this->IndividualDirectoryTxt->ReadOnly = true;
			this->IndividualDirectoryTxt->Size = System::Drawing::Size(287, 46);
			this->IndividualDirectoryTxt->TabIndex = 34;
			this->IndividualDirectoryTxt->Text = L"c:\\";
			this->Tooltip->SetToolTip(this->IndividualDirectoryTxt, L"Output Directory");
			this->IndividualDirectoryTxt->Click += gcnew System::EventHandler(this, &Form1::IndividualDirectoryTxt_Click);
			// 
			// StackingDirectoryTxt
			// 
			this->StackingDirectoryTxt->BackColor = System::Drawing::SystemColors::Control;
			this->StackingDirectoryTxt->DetectUrls = false;
			this->StackingDirectoryTxt->Location = System::Drawing::Point(6, 32);
			this->StackingDirectoryTxt->MaxLength = 500;
			this->StackingDirectoryTxt->Name = L"StackingDirectoryTxt";
			this->StackingDirectoryTxt->ReadOnly = true;
			this->StackingDirectoryTxt->Size = System::Drawing::Size(287, 50);
			this->StackingDirectoryTxt->TabIndex = 32;
			this->StackingDirectoryTxt->Text = L"c:\\";
			this->Tooltip->SetToolTip(this->StackingDirectoryTxt, L"Output Directory");
			this->StackingDirectoryTxt->Click += gcnew System::EventHandler(this, &Form1::StackingDirectoryTxt_Click);
			// 
			// RunningDirectoryTxt
			// 
			this->RunningDirectoryTxt->BackColor = System::Drawing::SystemColors::Control;
			this->RunningDirectoryTxt->DetectUrls = false;
			this->RunningDirectoryTxt->Location = System::Drawing::Point(6, 32);
			this->RunningDirectoryTxt->MaxLength = 500;
			this->RunningDirectoryTxt->Name = L"RunningDirectoryTxt";
			this->RunningDirectoryTxt->ReadOnly = true;
			this->RunningDirectoryTxt->Size = System::Drawing::Size(287, 50);
			this->RunningDirectoryTxt->TabIndex = 52;
			this->RunningDirectoryTxt->Text = L"c:\\";
			this->Tooltip->SetToolTip(this->RunningDirectoryTxt, L"Output Directory");
			this->RunningDirectoryTxt->Click += gcnew System::EventHandler(this, &Form1::RunningDirectoryTxt_Click);
			// 
			// KeyValNormBtn
			// 
			this->KeyValNormBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"KeyValNormBtn.BackgroundImage")));
			this->KeyValNormBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->KeyValNormBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->KeyValNormBtn->Location = System::Drawing::Point(253, 95);
			this->KeyValNormBtn->Name = L"KeyValNormBtn";
			this->KeyValNormBtn->Size = System::Drawing::Size(29, 29);
			this->KeyValNormBtn->TabIndex = 67;
			this->Tooltip->SetToolTip(this->KeyValNormBtn, L"Normalize to Header Key Value (ex., INT_TIME)");
			this->KeyValNormBtn->UseVisualStyleBackColor = true;
			this->KeyValNormBtn->Click += gcnew System::EventHandler(this, &Form1::KeyValNormBtn_Click);
			// 
			// PadImageBtn
			// 
			this->PadImageBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PadImageBtn.BackgroundImage")));
			this->PadImageBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->PadImageBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PadImageBtn->Location = System::Drawing::Point(101, 122);
			this->PadImageBtn->Name = L"PadImageBtn";
			this->PadImageBtn->Size = System::Drawing::Size(29, 29);
			this->PadImageBtn->TabIndex = 68;
			this->Tooltip->SetToolTip(this->PadImageBtn, L"Pad Image(s)");
			this->PadImageBtn->UseVisualStyleBackColor = true;
			this->PadImageBtn->Click += gcnew System::EventHandler(this, &Form1::PadImageBtn_Click);
			// 
			// BatchQuadratureChck
			// 
			this->BatchQuadratureChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BatchQuadratureChck->Location = System::Drawing::Point(71, 94);
			this->BatchQuadratureChck->Name = L"BatchQuadratureChck";
			this->BatchQuadratureChck->Size = System::Drawing::Size(82, 16);
			this->BatchQuadratureChck->TabIndex = 58;
			this->BatchQuadratureChck->Text = L"Quadrature";
			this->Tooltip->SetToolTip(this->BatchQuadratureChck, L"Compute the Quadrature Sum Image of the Image Set");
			this->BatchQuadratureChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchQuadratureChck_CheckedChanged);
			// 
			// MainTab
			// 
			this->MainTab->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->MainTab->Controls->Add(this->ProcessingTab);
			this->MainTab->Controls->Add(this->PSETab);
			this->MainTab->Controls->Add(this->BatchTab);
			this->MainTab->Controls->Add(this->UVITTab);
			this->MainTab->Location = System::Drawing::Point(1096, 25);
			this->MainTab->Name = L"MainTab";
			this->MainTab->SelectedIndex = 0;
			this->MainTab->Size = System::Drawing::Size(325, 527);
			this->MainTab->TabIndex = 29;
			this->MainTab->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::MainTab_SelectedIndexChanged);
			// 
			// ProcessingTab
			// 
			this->ProcessingTab->BackColor = System::Drawing::Color::Gainsboro;
			this->ProcessingTab->Controls->Add(this->ImageBatchRedxnPnl);
			this->ProcessingTab->Controls->Add(this->ImageCorrxnPnl);
			this->ProcessingTab->Controls->Add(this->ImageOpsPnl);
			this->ProcessingTab->Location = System::Drawing::Point(4, 22);
			this->ProcessingTab->Name = L"ProcessingTab";
			this->ProcessingTab->Size = System::Drawing::Size(317, 501);
			this->ProcessingTab->TabIndex = 1;
			this->ProcessingTab->Text = L"Processing";
			// 
			// ImageBatchRedxnPnl
			// 
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchQuadratureChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->groupBox4);
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchMaximumChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchMinimumChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchSumChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->SCMChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->ScmTxt);
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchMeanChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchMedianChck);
			this->ImageBatchRedxnPnl->Controls->Add(this->BatchStdvChck);
			this->ImageBatchRedxnPnl->Enabled = false;
			this->ImageBatchRedxnPnl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageBatchRedxnPnl->Location = System::Drawing::Point(8, 237);
			this->ImageBatchRedxnPnl->Name = L"ImageBatchRedxnPnl";
			this->ImageBatchRedxnPnl->Size = System::Drawing::Size(304, 118);
			this->ImageBatchRedxnPnl->TabIndex = 47;
			this->ImageBatchRedxnPnl->TabStop = false;
			this->ImageBatchRedxnPnl->Text = L"Batch Reduction";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->ManRegTrkHWUpD);
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Controls->Add(this->label2);
			this->groupBox4->Controls->Add(this->AutoRegBtn);
			this->groupBox4->Controls->Add(this->ManRegBtn);
			this->groupBox4->Controls->Add(this->ManRegSrcHWUpD);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox4->Location = System::Drawing::Point(154, 8);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(148, 106);
			this->groupBox4->TabIndex = 57;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Registration";
			// 
			// ManRegTrkHWUpD
			// 
			this->ManRegTrkHWUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ManRegTrkHWUpD->Location = System::Drawing::Point(110, 69);
			this->ManRegTrkHWUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->ManRegTrkHWUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->ManRegTrkHWUpD->Name = L"ManRegTrkHWUpD";
			this->ManRegTrkHWUpD->Size = System::Drawing::Size(34, 20);
			this->ManRegTrkHWUpD->TabIndex = 51;
			this->ManRegTrkHWUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->ManRegTrkHWUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::ManRegTrkHWUpD_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(3, 71);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 13);
			this->label1->TabIndex = 50;
			this->label1->Text = L"Track Box HalfWidth:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(3, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(94, 13);
			this->label2->TabIndex = 49;
			this->label2->Text = L"Source HalfWidth:";
			// 
			// AutoRegBtn
			// 
			this->AutoRegBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AutoRegBtn->Location = System::Drawing::Point(6, 19);
			this->AutoRegBtn->Name = L"AutoRegBtn";
			this->AutoRegBtn->Size = System::Drawing::Size(45, 23);
			this->AutoRegBtn->TabIndex = 8;
			this->AutoRegBtn->Text = L"Auto";
			this->AutoRegBtn->UseVisualStyleBackColor = true;
			this->AutoRegBtn->Click += gcnew System::EventHandler(this, &Form1::AutoRegBtn_Click);
			// 
			// ManRegBtn
			// 
			this->ManRegBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->ManRegBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ManRegBtn->Location = System::Drawing::Point(80, 19);
			this->ManRegBtn->Name = L"ManRegBtn";
			this->ManRegBtn->Size = System::Drawing::Size(59, 23);
			this->ManRegBtn->TabIndex = 9;
			this->ManRegBtn->Text = L"Manual";
			this->ManRegBtn->UseVisualStyleBackColor = true;
			this->ManRegBtn->Click += gcnew System::EventHandler(this, &Form1::ManRegBtn_Click);
			// 
			// ManRegSrcHWUpD
			// 
			this->ManRegSrcHWUpD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ManRegSrcHWUpD->Location = System::Drawing::Point(110, 47);
			this->ManRegSrcHWUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->ManRegSrcHWUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ManRegSrcHWUpD->Name = L"ManRegSrcHWUpD";
			this->ManRegSrcHWUpD->Size = System::Drawing::Size(34, 20);
			this->ManRegSrcHWUpD->TabIndex = 48;
			this->ManRegSrcHWUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			// 
			// SCMChck
			// 
			this->SCMChck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SCMChck->Location = System::Drawing::Point(64, 21);
			this->SCMChck->Name = L"SCMChck";
			this->SCMChck->Size = System::Drawing::Size(46, 18);
			this->SCMChck->TabIndex = 45;
			this->SCMChck->Text = L"Clip";
			this->SCMChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::SCMChck_CheckedChanged);
			// 
			// ScmTxt
			// 
			this->ScmTxt->Cursor = System::Windows::Forms::Cursors::Default;
			this->ScmTxt->DecimalPlaces = 1;
			this->ScmTxt->Enabled = false;
			this->ScmTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ScmTxt->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->ScmTxt->Location = System::Drawing::Point(110, 20);
			this->ScmTxt->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->ScmTxt->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->ScmTxt->Name = L"ScmTxt";
			this->ScmTxt->Size = System::Drawing::Size(42, 20);
			this->ScmTxt->TabIndex = 45;
			this->ScmTxt->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// ImageCorrxnPnl
			// 
			this->ImageCorrxnPnl->Controls->Add(this->PadImageBtn);
			this->ImageCorrxnPnl->Controls->Add(this->KeyValNormBtn);
			this->ImageCorrxnPnl->Controls->Add(this->NShiftVertUpD);
			this->ImageCorrxnPnl->Controls->Add(this->NShiftHorzUpD);
			this->ImageCorrxnPnl->Controls->Add(this->ShiftVertBtn);
			this->ImageCorrxnPnl->Controls->Add(this->ShiftHorzBtn);
			this->ImageCorrxnPnl->Controls->Add(this->RotateAngleUpD);
			this->ImageCorrxnPnl->Controls->Add(this->RotateBtn);
			this->ImageCorrxnPnl->Controls->Add(this->panel5);
			this->ImageCorrxnPnl->Controls->Add(this->CutSubImBtn);
			this->ImageCorrxnPnl->Controls->Add(this->panel3);
			this->ImageCorrxnPnl->Controls->Add(this->panel2);
			this->ImageCorrxnPnl->Controls->Add(this->panel4);
			this->ImageCorrxnPnl->Controls->Add(this->RotCCWBtn);
			this->ImageCorrxnPnl->Controls->Add(this->RotCWBtn);
			this->ImageCorrxnPnl->Controls->Add(this->FlipHorzBtn);
			this->ImageCorrxnPnl->Controls->Add(this->FlipVertBtn);
			this->ImageCorrxnPnl->Controls->Add(this->BatchCorrectionChck);
			this->ImageCorrxnPnl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageCorrxnPnl->Location = System::Drawing::Point(8, 4);
			this->ImageCorrxnPnl->Name = L"ImageCorrxnPnl";
			this->ImageCorrxnPnl->Size = System::Drawing::Size(304, 227);
			this->ImageCorrxnPnl->TabIndex = 0;
			this->ImageCorrxnPnl->TabStop = false;
			this->ImageCorrxnPnl->Text = L"Image Operations";
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->MultImgChck);
			this->panel5->Controls->Add(this->DivFlatChck);
			this->panel5->Controls->Add(this->SubBiasChck);
			this->panel5->Controls->Add(this->AddImageChck);
			this->panel5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel5->Location = System::Drawing::Point(5, 40);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(193, 46);
			this->panel5->TabIndex = 60;
			// 
			// MultImgChck
			// 
			this->MultImgChck->Location = System::Drawing::Point(5, 25);
			this->MultImgChck->Name = L"MultImgChck";
			this->MultImgChck->Size = System::Drawing::Size(98, 17);
			this->MultImgChck->TabIndex = 46;
			this->MultImgChck->Text = L"Multiply Image";
			this->MultImgChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::MultImgChck_CheckedChanged);
			// 
			// DivFlatChck
			// 
			this->DivFlatChck->Location = System::Drawing::Point(105, 24);
			this->DivFlatChck->Name = L"DivFlatChck";
			this->DivFlatChck->Size = System::Drawing::Size(88, 19);
			this->DivFlatChck->TabIndex = 19;
			this->DivFlatChck->Text = L"Divide Image";
			this->DivFlatChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::DivFlatChck_CheckedChanged);
			// 
			// SubBiasChck
			// 
			this->SubBiasChck->Location = System::Drawing::Point(5, 4);
			this->SubBiasChck->Name = L"SubBiasChck";
			this->SubBiasChck->Size = System::Drawing::Size(98, 17);
			this->SubBiasChck->TabIndex = 1;
			this->SubBiasChck->Text = L"Subtract Image";
			this->SubBiasChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::SubBiasChck_CheckedChanged);
			// 
			// AddImageChck
			// 
			this->AddImageChck->Location = System::Drawing::Point(105, 3);
			this->AddImageChck->Name = L"AddImageChck";
			this->AddImageChck->Size = System::Drawing::Size(77, 19);
			this->AddImageChck->TabIndex = 45;
			this->AddImageChck->Text = L"Add Image";
			this->AddImageChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::AddImageChck_CheckedChanged);
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->BinBtn);
			this->panel3->Controls->Add(this->label28);
			this->panel3->Controls->Add(this->XBinUpD);
			this->panel3->Controls->Add(this->label29);
			this->panel3->Controls->Add(this->YBinUpD);
			this->panel3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel3->Location = System::Drawing::Point(202, 40);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(98, 46);
			this->panel3->TabIndex = 59;
			// 
			// BinBtn
			// 
			this->BinBtn->Location = System::Drawing::Point(1, 10);
			this->BinBtn->Name = L"BinBtn";
			this->BinBtn->Size = System::Drawing::Size(33, 23);
			this->BinBtn->TabIndex = 48;
			this->BinBtn->Text = L"Bin";
			this->BinBtn->UseVisualStyleBackColor = true;
			this->BinBtn->Click += gcnew System::EventHandler(this, &Form1::BinBtn_Click);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(36, 6);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(17, 13);
			this->label28->TabIndex = 54;
			this->label28->Text = L"X:";
			// 
			// XBinUpD
			// 
			this->XBinUpD->Location = System::Drawing::Point(53, 2);
			this->XBinUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 512, 0, 0, 0 });
			this->XBinUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->XBinUpD->Name = L"XBinUpD";
			this->XBinUpD->Size = System::Drawing::Size(41, 20);
			this->XBinUpD->TabIndex = 55;
			this->XBinUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->XBinUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->XBinUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::XBinUpD_ValueChanged);
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(36, 27);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(17, 13);
			this->label29->TabIndex = 57;
			this->label29->Text = L"Y:";
			// 
			// YBinUpD
			// 
			this->YBinUpD->Location = System::Drawing::Point(53, 23);
			this->YBinUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 512, 0, 0, 0 });
			this->YBinUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->YBinUpD->Name = L"YBinUpD";
			this->YBinUpD->Size = System::Drawing::Size(41, 20);
			this->YBinUpD->TabIndex = 56;
			this->YBinUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->YBinUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->YBinUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::YBinUpD_ValueChanged);
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->ImageOpFilterLabel);
			this->panel2->Controls->Add(this->ImageOpFilterBtn);
			this->panel2->Controls->Add(this->ImageOpFilterWidthUpD);
			this->panel2->Controls->Add(this->ImageOpFilterTypeDrop);
			this->panel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel2->Location = System::Drawing::Point(5, 195);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(295, 26);
			this->panel2->TabIndex = 58;
			// 
			// ImageOpFilterLabel
			// 
			this->ImageOpFilterLabel->Enabled = false;
			this->ImageOpFilterLabel->Location = System::Drawing::Point(172, 6);
			this->ImageOpFilterLabel->Name = L"ImageOpFilterLabel";
			this->ImageOpFilterLabel->Size = System::Drawing::Size(69, 13);
			this->ImageOpFilterLabel->TabIndex = 63;
			this->ImageOpFilterLabel->Text = L"Filter Width:";
			// 
			// ImageOpFilterBtn
			// 
			this->ImageOpFilterBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->ImageOpFilterBtn->Location = System::Drawing::Point(3, 1);
			this->ImageOpFilterBtn->Name = L"ImageOpFilterBtn";
			this->ImageOpFilterBtn->Size = System::Drawing::Size(46, 23);
			this->ImageOpFilterBtn->TabIndex = 22;
			this->ImageOpFilterBtn->Text = L"Filter";
			this->ImageOpFilterBtn->UseVisualStyleBackColor = true;
			this->ImageOpFilterBtn->Click += gcnew System::EventHandler(this, &Form1::ImageOpFilterBtn_Click);
			// 
			// ImageOpFilterWidthUpD
			// 
			this->ImageOpFilterWidthUpD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->ImageOpFilterWidthUpD->Location = System::Drawing::Point(247, 2);
			this->ImageOpFilterWidthUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->ImageOpFilterWidthUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->ImageOpFilterWidthUpD->Name = L"ImageOpFilterWidthUpD";
			this->ImageOpFilterWidthUpD->Size = System::Drawing::Size(44, 20);
			this->ImageOpFilterWidthUpD->TabIndex = 62;
			this->ImageOpFilterWidthUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			// 
			// ImageOpFilterTypeDrop
			// 
			this->ImageOpFilterTypeDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ImageOpFilterTypeDrop->FormattingEnabled = true;
			this->ImageOpFilterTypeDrop->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Median", L"Convltn" });
			this->ImageOpFilterTypeDrop->Location = System::Drawing::Point(55, 2);
			this->ImageOpFilterTypeDrop->Name = L"ImageOpFilterTypeDrop";
			this->ImageOpFilterTypeDrop->Size = System::Drawing::Size(83, 21);
			this->ImageOpFilterTypeDrop->TabIndex = 61;
			this->ImageOpFilterTypeDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ImageOpFilterTypeDrop_SelectedIndexChanged);
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->ScalarOpBtn);
			this->panel4->Controls->Add(this->ScalarOpStyleDrop);
			this->panel4->Controls->Add(this->ScalarOpValTxt);
			this->panel4->Controls->Add(this->MathOpBtn);
			this->panel4->Controls->Add(this->MathOpDrop);
			this->panel4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel4->Location = System::Drawing::Point(5, 161);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(295, 28);
			this->panel4->TabIndex = 60;
			// 
			// ScalarOpBtn
			// 
			this->ScalarOpBtn->Location = System::Drawing::Point(1, 2);
			this->ScalarOpBtn->Name = L"ScalarOpBtn";
			this->ScalarOpBtn->Size = System::Drawing::Size(65, 23);
			this->ScalarOpBtn->TabIndex = 52;
			this->ScalarOpBtn->Text = L"Scalar Op:";
			this->ScalarOpBtn->UseVisualStyleBackColor = true;
			this->ScalarOpBtn->Click += gcnew System::EventHandler(this, &Form1::ScalarOpBtn_Click);
			// 
			// ScalarOpStyleDrop
			// 
			this->ScalarOpStyleDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ScalarOpStyleDrop->FormattingEnabled = true;
			this->ScalarOpStyleDrop->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"+", L"-", L"*", L"/", L"^" });
			this->ScalarOpStyleDrop->Location = System::Drawing::Point(66, 3);
			this->ScalarOpStyleDrop->Name = L"ScalarOpStyleDrop";
			this->ScalarOpStyleDrop->Size = System::Drawing::Size(30, 21);
			this->ScalarOpStyleDrop->TabIndex = 45;
			// 
			// ScalarOpValTxt
			// 
			this->ScalarOpValTxt->Location = System::Drawing::Point(97, 3);
			this->ScalarOpValTxt->MaxLength = 20;
			this->ScalarOpValTxt->Name = L"ScalarOpValTxt";
			this->ScalarOpValTxt->Size = System::Drawing::Size(50, 20);
			this->ScalarOpValTxt->TabIndex = 52;
			this->ScalarOpValTxt->Text = L"0";
			// 
			// MathOpBtn
			// 
			this->MathOpBtn->Location = System::Drawing::Point(147, 2);
			this->MathOpBtn->Name = L"MathOpBtn";
			this->MathOpBtn->Size = System::Drawing::Size(59, 23);
			this->MathOpBtn->TabIndex = 53;
			this->MathOpBtn->Text = L"Math Op:";
			this->MathOpBtn->UseVisualStyleBackColor = true;
			this->MathOpBtn->Click += gcnew System::EventHandler(this, &Form1::MathOpBtn_Click);
			// 
			// MathOpDrop
			// 
			this->MathOpDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->MathOpDrop->FormattingEnabled = true;
			this->MathOpDrop->Items->AddRange(gcnew cli::array< System::Object^  >(15) {
				L"Round", L"Floor", L"Ceil", L"Abs", L"BelowOne",
					L"Normalize", L"Sqrt", L"Log", L"10^", L"Ln", L"e^", L"deGradient-X", L"deGradient-Y", L"Hanning Window", L"Sort (asc.)"
			});
			this->MathOpDrop->Location = System::Drawing::Point(206, 3);
			this->MathOpDrop->Name = L"MathOpDrop";
			this->MathOpDrop->Size = System::Drawing::Size(86, 21);
			this->MathOpDrop->TabIndex = 46;
			// 
			// ImageOpsPnl
			// 
			this->ImageOpsPnl->Controls->Add(this->RGBSaveBtn);
			this->ImageOpsPnl->Controls->Add(this->CombineRGBBtn);
			this->ImageOpsPnl->Controls->Add(this->ClipToContrastBtn);
			this->ImageOpsPnl->Controls->Add(this->panel1);
			this->ImageOpsPnl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ImageOpsPnl->Location = System::Drawing::Point(8, 364);
			this->ImageOpsPnl->Name = L"ImageOpsPnl";
			this->ImageOpsPnl->Size = System::Drawing::Size(304, 111);
			this->ImageOpsPnl->TabIndex = 45;
			this->ImageOpsPnl->TabStop = false;
			this->ImageOpsPnl->Text = L"Current Image";
			// 
			// RGBSaveBtn
			// 
			this->RGBSaveBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RGBSaveBtn->Location = System::Drawing::Point(248, 81);
			this->RGBSaveBtn->Name = L"RGBSaveBtn";
			this->RGBSaveBtn->Size = System::Drawing::Size(45, 23);
			this->RGBSaveBtn->TabIndex = 48;
			this->RGBSaveBtn->Text = L"Save";
			this->RGBSaveBtn->UseVisualStyleBackColor = true;
			this->RGBSaveBtn->Click += gcnew System::EventHandler(this, &Form1::RGBSaveBtn_Click);
			// 
			// CombineRGBBtn
			// 
			this->CombineRGBBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CombineRGBBtn->Location = System::Drawing::Point(158, 81);
			this->CombineRGBBtn->Name = L"CombineRGBBtn";
			this->CombineRGBBtn->Size = System::Drawing::Size(84, 23);
			this->CombineRGBBtn->TabIndex = 47;
			this->CombineRGBBtn->Text = L"Combine RGB";
			this->CombineRGBBtn->UseVisualStyleBackColor = true;
			this->CombineRGBBtn->Click += gcnew System::EventHandler(this, &Form1::CombineRGBBtn_Click);
			// 
			// ClipToContrastBtn
			// 
			this->ClipToContrastBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ClipToContrastBtn->Location = System::Drawing::Point(6, 81);
			this->ClipToContrastBtn->Name = L"ClipToContrastBtn";
			this->ClipToContrastBtn->Size = System::Drawing::Size(146, 23);
			this->ClipToContrastBtn->TabIndex = 46;
			this->ClipToContrastBtn->Text = L"RGB: Normalize to Contrast";
			this->ClipToContrastBtn->UseVisualStyleBackColor = true;
			this->ClipToContrastBtn->Click += gcnew System::EventHandler(this, &Form1::ClipToContrastBtn_Click);
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->FindImagePtsBtn);
			this->panel1->Controls->Add(this->FindPtsDrop);
			this->panel1->Controls->Add(this->ReplaceImagePtsTxt);
			this->panel1->Controls->Add(this->FindImagePtsTxt);
			this->panel1->Controls->Add(this->ReplaceImagePtsBtn);
			this->panel1->Controls->Add(this->ReplaceImagePtsDrop);
			this->panel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel1->Location = System::Drawing::Point(6, 19);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(294, 56);
			this->panel1->TabIndex = 45;
			// 
			// FindImagePtsBtn
			// 
			this->FindImagePtsBtn->Location = System::Drawing::Point(3, 3);
			this->FindImagePtsBtn->Name = L"FindImagePtsBtn";
			this->FindImagePtsBtn->Size = System::Drawing::Size(74, 23);
			this->FindImagePtsBtn->TabIndex = 7;
			this->FindImagePtsBtn->Text = L"Find Points:";
			this->FindImagePtsBtn->UseVisualStyleBackColor = true;
			this->FindImagePtsBtn->Click += gcnew System::EventHandler(this, &Form1::FindImagePtsBtn_Click);
			// 
			// FindPtsDrop
			// 
			this->FindPtsDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FindPtsDrop->FormattingEnabled = true;
			this->FindPtsDrop->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"<", L"<=", L"=", L">=", L">", L"!=" });
			this->FindPtsDrop->Location = System::Drawing::Point(78, 4);
			this->FindPtsDrop->Name = L"FindPtsDrop";
			this->FindPtsDrop->Size = System::Drawing::Size(37, 21);
			this->FindPtsDrop->TabIndex = 44;
			// 
			// ReplaceImagePtsTxt
			// 
			this->ReplaceImagePtsTxt->Enabled = false;
			this->ReplaceImagePtsTxt->Location = System::Drawing::Point(182, 30);
			this->ReplaceImagePtsTxt->MaxLength = 15;
			this->ReplaceImagePtsTxt->Name = L"ReplaceImagePtsTxt";
			this->ReplaceImagePtsTxt->Size = System::Drawing::Size(107, 20);
			this->ReplaceImagePtsTxt->TabIndex = 46;
			this->ReplaceImagePtsTxt->Text = L"0";
			// 
			// FindImagePtsTxt
			// 
			this->FindImagePtsTxt->Location = System::Drawing::Point(10, 30);
			this->FindImagePtsTxt->MaxLength = 15;
			this->FindImagePtsTxt->Name = L"FindImagePtsTxt";
			this->FindImagePtsTxt->Size = System::Drawing::Size(107, 20);
			this->FindImagePtsTxt->TabIndex = 8;
			this->FindImagePtsTxt->Text = L"0";
			// 
			// ReplaceImagePtsBtn
			// 
			this->ReplaceImagePtsBtn->AutoSize = true;
			this->ReplaceImagePtsBtn->Location = System::Drawing::Point(128, 3);
			this->ReplaceImagePtsBtn->Name = L"ReplaceImagePtsBtn";
			this->ReplaceImagePtsBtn->Size = System::Drawing::Size(95, 23);
			this->ReplaceImagePtsBtn->TabIndex = 45;
			this->ReplaceImagePtsBtn->Text = L"Replace with:";
			this->ReplaceImagePtsBtn->UseVisualStyleBackColor = true;
			this->ReplaceImagePtsBtn->Click += gcnew System::EventHandler(this, &Form1::ReplaceImagePtsBtn_Click);
			// 
			// ReplaceImagePtsDrop
			// 
			this->ReplaceImagePtsDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ReplaceImagePtsDrop->Enabled = false;
			this->ReplaceImagePtsDrop->FormattingEnabled = true;
			this->ReplaceImagePtsDrop->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Value", L"Min", L"Max", L"Median",
					L"Mean"
			});
			this->ReplaceImagePtsDrop->Location = System::Drawing::Point(224, 4);
			this->ReplaceImagePtsDrop->Name = L"ReplaceImagePtsDrop";
			this->ReplaceImagePtsDrop->Size = System::Drawing::Size(65, 21);
			this->ReplaceImagePtsDrop->TabIndex = 45;
			this->ReplaceImagePtsDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ReplaceImagePtsDrop_SelectedIndexChanged);
			// 
			// BatchTab
			// 
			this->BatchTab->BackColor = System::Drawing::Color::Gainsboro;
			this->BatchTab->Controls->Add(this->BatchQuickScanSubDirsChck);
			this->BatchTab->Controls->Add(this->BatchScanDirectoryFileTypeDrop);
			this->BatchTab->Controls->Add(this->BatchScanDirectoryBtn);
			this->BatchTab->Controls->Add(this->BatchListViewPanel);
			this->BatchTab->Controls->Add(this->BatchOperationTab);
			this->BatchTab->Controls->Add(this->groupBox2);
			this->BatchTab->Controls->Add(this->BatchSubImagePanel);
			this->BatchTab->Controls->Add(this->BatchComputeBtn);
			this->BatchTab->Controls->Add(this->BatchOpenListBtn);
			this->BatchTab->Controls->Add(this->BatchMakeListBtn);
			this->BatchTab->Controls->Add(this->BatchListNameTxt);
			this->BatchTab->Location = System::Drawing::Point(4, 22);
			this->BatchTab->Name = L"BatchTab";
			this->BatchTab->Size = System::Drawing::Size(317, 501);
			this->BatchTab->TabIndex = 2;
			this->BatchTab->Text = L"Batch";
			// 
			// BatchQuickScanSubDirsChck
			// 
			this->BatchQuickScanSubDirsChck->AutoSize = true;
			this->BatchQuickScanSubDirsChck->Location = System::Drawing::Point(163, 34);
			this->BatchQuickScanSubDirsChck->Name = L"BatchQuickScanSubDirsChck";
			this->BatchQuickScanSubDirsChck->Size = System::Drawing::Size(131, 17);
			this->BatchQuickScanSubDirsChck->TabIndex = 57;
			this->BatchQuickScanSubDirsChck->Text = L"Include Subdirectories";
			this->BatchQuickScanSubDirsChck->UseVisualStyleBackColor = true;
			// 
			// BatchScanDirectoryFileTypeDrop
			// 
			this->BatchScanDirectoryFileTypeDrop->DisplayMember = L"1";
			this->BatchScanDirectoryFileTypeDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->BatchScanDirectoryFileTypeDrop->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"*.fits", L"*.fit", L"*.fts" });
			this->BatchScanDirectoryFileTypeDrop->Location = System::Drawing::Point(92, 32);
			this->BatchScanDirectoryFileTypeDrop->Name = L"BatchScanDirectoryFileTypeDrop";
			this->BatchScanDirectoryFileTypeDrop->Size = System::Drawing::Size(60, 21);
			this->BatchScanDirectoryFileTypeDrop->TabIndex = 56;
			// 
			// BatchScanDirectoryBtn
			// 
			this->BatchScanDirectoryBtn->Location = System::Drawing::Point(3, 32);
			this->BatchScanDirectoryBtn->Name = L"BatchScanDirectoryBtn";
			this->BatchScanDirectoryBtn->Size = System::Drawing::Size(85, 22);
			this->BatchScanDirectoryBtn->TabIndex = 55;
			this->BatchScanDirectoryBtn->Text = L"Quick Scan";
			this->BatchScanDirectoryBtn->UseVisualStyleBackColor = true;
			this->BatchScanDirectoryBtn->Click += gcnew System::EventHandler(this, &Form1::BatchScanDirectoryBtn_Click);
			// 
			// BatchListViewPanel
			// 
			this->BatchListViewPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BatchListViewPanel->Controls->Add(this->BatchMovieSkipUpD);
			this->BatchListViewPanel->Controls->Add(this->label38);
			this->BatchListViewPanel->Controls->Add(this->BatchGoToBtn);
			this->BatchListViewPanel->Controls->Add(this->BatchBlinkTime);
			this->BatchListViewPanel->Controls->Add(this->BatchBlinkChck);
			this->BatchListViewPanel->Controls->Add(this->BatchViewNextBtn);
			this->BatchListViewPanel->Controls->Add(this->BatchGoToUpD);
			this->BatchListViewPanel->Controls->Add(this->BatchViewLastBtn);
			this->BatchListViewPanel->Enabled = false;
			this->BatchListViewPanel->Location = System::Drawing::Point(3, 62);
			this->BatchListViewPanel->Name = L"BatchListViewPanel";
			this->BatchListViewPanel->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->BatchListViewPanel->Size = System::Drawing::Size(306, 63);
			this->BatchListViewPanel->TabIndex = 54;
			this->BatchListViewPanel->TabStop = false;
			this->BatchListViewPanel->Text = L"Quick Viewing: File 0 of 0";
			// 
			// BatchMovieSkipUpD
			// 
			this->BatchMovieSkipUpD->Location = System::Drawing::Point(191, 12);
			this->BatchMovieSkipUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->BatchMovieSkipUpD->Name = L"BatchMovieSkipUpD";
			this->BatchMovieSkipUpD->Size = System::Drawing::Size(73, 20);
			this->BatchMovieSkipUpD->TabIndex = 47;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(159, 14);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(31, 13);
			this->label38->TabIndex = 46;
			this->label38->Text = L"Skip:";
			// 
			// BatchGoToBtn
			// 
			this->BatchGoToBtn->Location = System::Drawing::Point(138, 36);
			this->BatchGoToBtn->Name = L"BatchGoToBtn";
			this->BatchGoToBtn->Size = System::Drawing::Size(52, 21);
			this->BatchGoToBtn->TabIndex = 45;
			this->BatchGoToBtn->Text = L"Go To:";
			this->BatchGoToBtn->UseVisualStyleBackColor = true;
			this->BatchGoToBtn->Click += gcnew System::EventHandler(this, &Form1::BatchGoToBtn_Click);
			// 
			// BatchBlinkTime
			// 
			this->BatchBlinkTime->DecimalPlaces = 1;
			this->BatchBlinkTime->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->BatchBlinkTime->Location = System::Drawing::Point(46, 37);
			this->BatchBlinkTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->BatchBlinkTime->Name = L"BatchBlinkTime";
			this->BatchBlinkTime->Size = System::Drawing::Size(49, 20);
			this->BatchBlinkTime->TabIndex = 37;
			this->BatchBlinkTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->BatchBlinkTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 65536 });
			// 
			// BatchBlinkChck
			// 
			this->BatchBlinkChck->Appearance = System::Windows::Forms::Appearance::Button;
			this->BatchBlinkChck->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->BatchBlinkChck->Location = System::Drawing::Point(46, 17);
			this->BatchBlinkChck->Name = L"BatchBlinkChck";
			this->BatchBlinkChck->Size = System::Drawing::Size(49, 20);
			this->BatchBlinkChck->TabIndex = 22;
			this->BatchBlinkChck->Text = L"Scan";
			this->BatchBlinkChck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->BatchBlinkChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchBlinkChck_CheckedChanged);
			// 
			// BatchGoToUpD
			// 
			this->BatchGoToUpD->Location = System::Drawing::Point(191, 36);
			this->BatchGoToUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->BatchGoToUpD->Name = L"BatchGoToUpD";
			this->BatchGoToUpD->Size = System::Drawing::Size(73, 20);
			this->BatchGoToUpD->TabIndex = 45;
			this->BatchGoToUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// BatchOperationTab
			// 
			this->BatchOperationTab->Controls->Add(this->BatchSetTab);
			this->BatchOperationTab->Controls->Add(this->BatchIndividualTab);
			this->BatchOperationTab->Controls->Add(this->BatchStackingTab);
			this->BatchOperationTab->Controls->Add(this->BatchRunningTab);
			this->BatchOperationTab->Location = System::Drawing::Point(3, 241);
			this->BatchOperationTab->Name = L"BatchOperationTab";
			this->BatchOperationTab->SelectedIndex = 0;
			this->BatchOperationTab->Size = System::Drawing::Size(310, 197);
			this->BatchOperationTab->TabIndex = 15;
			this->BatchOperationTab->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::BatchIntegralTab_SelectedIndexChanged);
			// 
			// BatchSetTab
			// 
			this->BatchSetTab->BackColor = System::Drawing::Color::Gainsboro;
			this->BatchSetTab->Controls->Add(this->BatchOutLabel);
			this->BatchSetTab->Controls->Add(this->label16);
			this->BatchSetTab->Controls->Add(this->groupBox3);
			this->BatchSetTab->Location = System::Drawing::Point(4, 22);
			this->BatchSetTab->Name = L"BatchSetTab";
			this->BatchSetTab->Padding = System::Windows::Forms::Padding(3);
			this->BatchSetTab->Size = System::Drawing::Size(302, 171);
			this->BatchSetTab->TabIndex = 1;
			this->BatchSetTab->Text = L"Set";
			// 
			// BatchOutLabel
			// 
			this->BatchOutLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->BatchOutLabel->Location = System::Drawing::Point(92, 30);
			this->BatchOutLabel->Name = L"BatchOutLabel";
			this->BatchOutLabel->Size = System::Drawing::Size(206, 34);
			this->BatchOutLabel->TabIndex = 3;
			this->BatchOutLabel->Text = L"c:\\setOP.fits";
			this->BatchOutLabel->Click += gcnew System::EventHandler(this, &Form1::BatchOutFileName_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(89, 11);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(92, 13);
			this->label16->TabIndex = 2;
			this->label16->Text = L"Output File Name:";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->BatchMeanRad);
			this->groupBox3->Controls->Add(this->BatchSumRad);
			this->groupBox3->Location = System::Drawing::Point(5, 5);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(80, 66);
			this->groupBox3->TabIndex = 1;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Operation A:";
			// 
			// BatchMeanRad
			// 
			this->BatchMeanRad->AutoSize = true;
			this->BatchMeanRad->Location = System::Drawing::Point(6, 42);
			this->BatchMeanRad->Name = L"BatchMeanRad";
			this->BatchMeanRad->Size = System::Drawing::Size(52, 17);
			this->BatchMeanRad->TabIndex = 1;
			this->BatchMeanRad->Text = L"Mean";
			this->BatchMeanRad->UseVisualStyleBackColor = true;
			// 
			// BatchSumRad
			// 
			this->BatchSumRad->AutoSize = true;
			this->BatchSumRad->Checked = true;
			this->BatchSumRad->Location = System::Drawing::Point(6, 19);
			this->BatchSumRad->Name = L"BatchSumRad";
			this->BatchSumRad->Size = System::Drawing::Size(46, 17);
			this->BatchSumRad->TabIndex = 0;
			this->BatchSumRad->TabStop = true;
			this->BatchSumRad->Text = L"Sum";
			this->BatchSumRad->UseVisualStyleBackColor = true;
			// 
			// BatchIndividualTab
			// 
			this->BatchIndividualTab->BackColor = System::Drawing::Color::Gainsboro;
			this->BatchIndividualTab->Controls->Add(this->BatchFileKeepDirectoriesChck);
			this->BatchIndividualTab->Controls->Add(this->BatchFileParallelChck);
			this->BatchIndividualTab->Controls->Add(this->TabBatchElementalFindStyleDD);
			this->BatchIndividualTab->Controls->Add(this->label31);
			this->BatchIndividualTab->Controls->Add(this->IndividualDirectoryTxt);
			this->BatchIndividualTab->Controls->Add(this->TabBatchElementalReplaceValTxt);
			this->BatchIndividualTab->Controls->Add(this->BatchIndividualAppendageTxt);
			this->BatchIndividualTab->Controls->Add(this->BatchFileAppRad);
			this->BatchIndividualTab->Controls->Add(this->TabBatchElementalReplaceStyleDD);
			this->BatchIndividualTab->Controls->Add(this->BatchFileOvrWrtRad);
			this->BatchIndividualTab->Controls->Add(this->TabBatchElementalFindValTxt);
			this->BatchIndividualTab->Controls->Add(this->TabBatchElementalFindPointsChck);
			this->BatchIndividualTab->Location = System::Drawing::Point(4, 22);
			this->BatchIndividualTab->Name = L"BatchIndividualTab";
			this->BatchIndividualTab->Padding = System::Windows::Forms::Padding(3);
			this->BatchIndividualTab->Size = System::Drawing::Size(302, 171);
			this->BatchIndividualTab->TabIndex = 0;
			this->BatchIndividualTab->Text = L"Individual";
			// 
			// BatchFileKeepDirectoriesChck
			// 
			this->BatchFileKeepDirectoriesChck->AutoSize = true;
			this->BatchFileKeepDirectoriesChck->Enabled = false;
			this->BatchFileKeepDirectoriesChck->Location = System::Drawing::Point(143, 30);
			this->BatchFileKeepDirectoriesChck->Name = L"BatchFileKeepDirectoriesChck";
			this->BatchFileKeepDirectoriesChck->Size = System::Drawing::Size(104, 17);
			this->BatchFileKeepDirectoriesChck->TabIndex = 51;
			this->BatchFileKeepDirectoriesChck->Text = L"Keep Directories";
			this->BatchFileKeepDirectoriesChck->UseVisualStyleBackColor = true;
			this->BatchFileKeepDirectoriesChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchFileKeepDirectoriesChck_CheckedChanged);
			// 
			// BatchFileParallelChck
			// 
			this->BatchFileParallelChck->Location = System::Drawing::Point(6, 124);
			this->BatchFileParallelChck->Name = L"BatchFileParallelChck";
			this->BatchFileParallelChck->Size = System::Drawing::Size(82, 41);
			this->BatchFileParallelChck->TabIndex = 50;
			this->BatchFileParallelChck->Text = L"Compute Parallelized";
			this->BatchFileParallelChck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->BatchFileParallelChck->UseVisualStyleBackColor = true;
			// 
			// TabBatchElementalFindStyleDD
			// 
			this->TabBatchElementalFindStyleDD->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TabBatchElementalFindStyleDD->Enabled = false;
			this->TabBatchElementalFindStyleDD->FormattingEnabled = true;
			this->TabBatchElementalFindStyleDD->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"<", L"<=", L"=", L">=", L">" });
			this->TabBatchElementalFindStyleDD->Location = System::Drawing::Point(182, 101);
			this->TabBatchElementalFindStyleDD->Name = L"TabBatchElementalFindStyleDD";
			this->TabBatchElementalFindStyleDD->Size = System::Drawing::Size(37, 21);
			this->TabBatchElementalFindStyleDD->TabIndex = 45;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(126, 131);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(29, 13);
			this->label31->TabIndex = 49;
			this->label31->Text = L"with:";
			// 
			// TabBatchElementalReplaceValTxt
			// 
			this->TabBatchElementalReplaceValTxt->Enabled = false;
			this->TabBatchElementalReplaceValTxt->Location = System::Drawing::Point(221, 128);
			this->TabBatchElementalReplaceValTxt->MaxLength = 15;
			this->TabBatchElementalReplaceValTxt->Name = L"TabBatchElementalReplaceValTxt";
			this->TabBatchElementalReplaceValTxt->Size = System::Drawing::Size(70, 20);
			this->TabBatchElementalReplaceValTxt->TabIndex = 48;
			this->TabBatchElementalReplaceValTxt->Text = L"0";
			// 
			// BatchFileAppRad
			// 
			this->BatchFileAppRad->AutoSize = true;
			this->BatchFileAppRad->Location = System::Drawing::Point(6, 29);
			this->BatchFileAppRad->Name = L"BatchFileAppRad";
			this->BatchFileAppRad->Size = System::Drawing::Size(62, 17);
			this->BatchFileAppRad->TabIndex = 1;
			this->BatchFileAppRad->Text = L"Append";
			this->BatchFileAppRad->UseVisualStyleBackColor = true;
			this->BatchFileAppRad->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchFileAppRad_CheckedChanged);
			// 
			// TabBatchElementalReplaceStyleDD
			// 
			this->TabBatchElementalReplaceStyleDD->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TabBatchElementalReplaceStyleDD->Enabled = false;
			this->TabBatchElementalReplaceStyleDD->FormattingEnabled = true;
			this->TabBatchElementalReplaceStyleDD->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Value", L"Min", L"Max",
					L"Median", L"Mean"
			});
			this->TabBatchElementalReplaceStyleDD->Location = System::Drawing::Point(156, 128);
			this->TabBatchElementalReplaceStyleDD->Name = L"TabBatchElementalReplaceStyleDD";
			this->TabBatchElementalReplaceStyleDD->Size = System::Drawing::Size(63, 21);
			this->TabBatchElementalReplaceStyleDD->TabIndex = 47;
			// 
			// BatchFileOvrWrtRad
			// 
			this->BatchFileOvrWrtRad->AutoSize = true;
			this->BatchFileOvrWrtRad->Checked = true;
			this->BatchFileOvrWrtRad->Location = System::Drawing::Point(6, 6);
			this->BatchFileOvrWrtRad->Name = L"BatchFileOvrWrtRad";
			this->BatchFileOvrWrtRad->Size = System::Drawing::Size(70, 17);
			this->BatchFileOvrWrtRad->TabIndex = 0;
			this->BatchFileOvrWrtRad->TabStop = true;
			this->BatchFileOvrWrtRad->Text = L"Overwrite";
			this->BatchFileOvrWrtRad->UseVisualStyleBackColor = true;
			// 
			// TabBatchElementalFindValTxt
			// 
			this->TabBatchElementalFindValTxt->Enabled = false;
			this->TabBatchElementalFindValTxt->Location = System::Drawing::Point(221, 101);
			this->TabBatchElementalFindValTxt->MaxLength = 15;
			this->TabBatchElementalFindValTxt->Name = L"TabBatchElementalFindValTxt";
			this->TabBatchElementalFindValTxt->Size = System::Drawing::Size(70, 20);
			this->TabBatchElementalFindValTxt->TabIndex = 46;
			this->TabBatchElementalFindValTxt->Text = L"0";
			// 
			// TabBatchElementalFindPointsChck
			// 
			this->TabBatchElementalFindPointsChck->AutoSize = true;
			this->TabBatchElementalFindPointsChck->Location = System::Drawing::Point(75, 103);
			this->TabBatchElementalFindPointsChck->Name = L"TabBatchElementalFindPointsChck";
			this->TabBatchElementalFindPointsChck->Size = System::Drawing::Size(113, 17);
			this->TabBatchElementalFindPointsChck->TabIndex = 2;
			this->TabBatchElementalFindPointsChck->Text = L"Find and Replace:";
			this->TabBatchElementalFindPointsChck->UseVisualStyleBackColor = true;
			this->TabBatchElementalFindPointsChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::TabBatchElementalFindPointsChck_CheckedChanged);
			// 
			// BatchStackingTab
			// 
			this->BatchStackingTab->BackColor = System::Drawing::Color::Gainsboro;
			this->BatchStackingTab->Controls->Add(this->label39);
			this->BatchStackingTab->Controls->Add(this->StackUpD);
			this->BatchStackingTab->Controls->Add(this->StackingDirectoryTxt);
			this->BatchStackingTab->Controls->Add(this->label18);
			this->BatchStackingTab->Location = System::Drawing::Point(4, 22);
			this->BatchStackingTab->Name = L"BatchStackingTab";
			this->BatchStackingTab->Padding = System::Windows::Forms::Padding(3);
			this->BatchStackingTab->Size = System::Drawing::Size(302, 171);
			this->BatchStackingTab->TabIndex = 2;
			this->BatchStackingTab->Text = L"Stacking";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(169, 8);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(41, 13);
			this->label39->TabIndex = 34;
			this->label39->Text = L"frames.";
			// 
			// StackUpD
			// 
			this->StackUpD->Location = System::Drawing::Point(107, 6);
			this->StackUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->StackUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->StackUpD->Name = L"StackUpD";
			this->StackUpD->Size = System::Drawing::Size(60, 20);
			this->StackUpD->TabIndex = 33;
			this->StackUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->StackUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::StackUpD_ValueChanged);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(6, 8);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(100, 13);
			this->label18->TabIndex = 1;
			this->label18->Text = L"Stack Consecutive:";
			// 
			// BatchRunningTab
			// 
			this->BatchRunningTab->BackColor = System::Drawing::Color::Gainsboro;
			this->BatchRunningTab->Controls->Add(this->RunningDirectoryTxt);
			this->BatchRunningTab->Controls->Add(this->label35);
			this->BatchRunningTab->Controls->Add(this->BatchRunningNumUpD);
			this->BatchRunningTab->Controls->Add(this->label34);
			this->BatchRunningTab->Controls->Add(this->BatchRunningOpDrop);
			this->BatchRunningTab->Controls->Add(this->label33);
			this->BatchRunningTab->Location = System::Drawing::Point(4, 22);
			this->BatchRunningTab->Name = L"BatchRunningTab";
			this->BatchRunningTab->Padding = System::Windows::Forms::Padding(3);
			this->BatchRunningTab->Size = System::Drawing::Size(302, 171);
			this->BatchRunningTab->TabIndex = 3;
			this->BatchRunningTab->Text = L"Running";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(235, 8);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(41, 13);
			this->label35->TabIndex = 50;
			this->label35->Text = L"frames.";
			// 
			// BatchRunningNumUpD
			// 
			this->BatchRunningNumUpD->Location = System::Drawing::Point(169, 6);
			this->BatchRunningNumUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->BatchRunningNumUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->BatchRunningNumUpD->Name = L"BatchRunningNumUpD";
			this->BatchRunningNumUpD->Size = System::Drawing::Size(60, 20);
			this->BatchRunningNumUpD->TabIndex = 49;
			this->BatchRunningNumUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->BatchRunningNumUpD->ValueChanged += gcnew System::EventHandler(this, &Form1::BatchRunningNumUpD_ValueChanged);
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(121, 8);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(45, 13);
			this->label34->TabIndex = 48;
			this->label34->Text = L"of every";
			// 
			// BatchRunningOpDrop
			// 
			this->BatchRunningOpDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->BatchRunningOpDrop->FormattingEnabled = true;
			this->BatchRunningOpDrop->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Minimum", L"Maximum", L"Median", L"Mean",
					L"Sum"
			});
			this->BatchRunningOpDrop->Location = System::Drawing::Point(52, 5);
			this->BatchRunningOpDrop->Name = L"BatchRunningOpDrop";
			this->BatchRunningOpDrop->Size = System::Drawing::Size(67, 21);
			this->BatchRunningOpDrop->TabIndex = 47;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(6, 8);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(47, 13);
			this->label33->TabIndex = 2;
			this->label33->Text = L"Running";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->BatchAddImageChck);
			this->groupBox2->Controls->Add(this->BatchSubtractImageChck);
			this->groupBox2->Controls->Add(this->BatchMultiplyImageChck);
			this->groupBox2->Controls->Add(this->BatchDivideImageChck);
			this->groupBox2->Location = System::Drawing::Point(3, 182);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 56);
			this->groupBox2->TabIndex = 14;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Image Corrections";
			// 
			// BatchAddImageChck
			// 
			this->BatchAddImageChck->Location = System::Drawing::Point(109, 18);
			this->BatchAddImageChck->Name = L"BatchAddImageChck";
			this->BatchAddImageChck->Size = System::Drawing::Size(78, 19);
			this->BatchAddImageChck->TabIndex = 45;
			this->BatchAddImageChck->Text = L"Add Image";
			this->BatchAddImageChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchAddImageChck_CheckedChanged);
			this->BatchAddImageChck->Click += gcnew System::EventHandler(this, &Form1::BatchAddImageChck_Click);
			// 
			// BatchSubtractImageChck
			// 
			this->BatchSubtractImageChck->Location = System::Drawing::Point(7, 18);
			this->BatchSubtractImageChck->Name = L"BatchSubtractImageChck";
			this->BatchSubtractImageChck->Size = System::Drawing::Size(98, 17);
			this->BatchSubtractImageChck->TabIndex = 1;
			this->BatchSubtractImageChck->Text = L"Subtract Image";
			this->BatchSubtractImageChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchSubtractImageChck_CheckedChanged);
			this->BatchSubtractImageChck->Click += gcnew System::EventHandler(this, &Form1::BatchSubtractImageChck_Click);
			// 
			// BatchMultiplyImageChck
			// 
			this->BatchMultiplyImageChck->Location = System::Drawing::Point(7, 36);
			this->BatchMultiplyImageChck->Name = L"BatchMultiplyImageChck";
			this->BatchMultiplyImageChck->Size = System::Drawing::Size(96, 17);
			this->BatchMultiplyImageChck->TabIndex = 19;
			this->BatchMultiplyImageChck->Text = L"Multiply Image";
			this->BatchMultiplyImageChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchMultiplyImageChck_CheckedChanged);
			this->BatchMultiplyImageChck->Click += gcnew System::EventHandler(this, &Form1::BatchMultiplyImageChck_Click);
			// 
			// BatchDivideImageChck
			// 
			this->BatchDivideImageChck->Location = System::Drawing::Point(109, 36);
			this->BatchDivideImageChck->Name = L"BatchDivideImageChck";
			this->BatchDivideImageChck->Size = System::Drawing::Size(88, 17);
			this->BatchDivideImageChck->TabIndex = 19;
			this->BatchDivideImageChck->Text = L"Divide Image";
			this->BatchDivideImageChck->Click += gcnew System::EventHandler(this, &Form1::BatchDivideImageChck_Click);
			// 
			// BatchSubImagePanel
			// 
			this->BatchSubImagePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->BatchSubImagePanel->Controls->Add(this->BatchSubImageChck);
			this->BatchSubImagePanel->Controls->Add(this->YEndLabel);
			this->BatchSubImagePanel->Controls->Add(this->XStartLabel);
			this->BatchSubImagePanel->Controls->Add(this->YStartLabel);
			this->BatchSubImagePanel->Controls->Add(this->XEndLabel);
			this->BatchSubImagePanel->Location = System::Drawing::Point(3, 132);
			this->BatchSubImagePanel->Name = L"BatchSubImagePanel";
			this->BatchSubImagePanel->Size = System::Drawing::Size(310, 44);
			this->BatchSubImagePanel->TabIndex = 13;
			// 
			// BatchSubImageChck
			// 
			this->BatchSubImageChck->AutoSize = true;
			this->BatchSubImageChck->Location = System::Drawing::Point(3, 3);
			this->BatchSubImageChck->Name = L"BatchSubImageChck";
			this->BatchSubImageChck->Size = System::Drawing::Size(132, 17);
			this->BatchSubImageChck->TabIndex = 4;
			this->BatchSubImageChck->Text = L"Sub-Image Processing";
			this->BatchSubImageChck->UseVisualStyleBackColor = true;
			this->BatchSubImageChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::BatchSubImageChck_CheckedChanged);
			// 
			// YEndLabel
			// 
			this->YEndLabel->AutoSize = true;
			this->YEndLabel->Location = System::Drawing::Point(231, 23);
			this->YEndLabel->Name = L"YEndLabel";
			this->YEndLabel->Size = System::Drawing::Size(72, 13);
			this->YEndLabel->TabIndex = 12;
			this->YEndLabel->Text = L"Y End: 00000";
			// 
			// XStartLabel
			// 
			this->XStartLabel->AutoSize = true;
			this->XStartLabel->Location = System::Drawing::Point(3, 23);
			this->XStartLabel->Name = L"XStartLabel";
			this->XStartLabel->Size = System::Drawing::Size(69, 13);
			this->XStartLabel->TabIndex = 9;
			this->XStartLabel->Text = L"X Start: 0000";
			// 
			// YStartLabel
			// 
			this->YStartLabel->AutoSize = true;
			this->YStartLabel->Location = System::Drawing::Point(156, 23);
			this->YStartLabel->Name = L"YStartLabel";
			this->YStartLabel->Size = System::Drawing::Size(69, 13);
			this->YStartLabel->TabIndex = 11;
			this->YStartLabel->Text = L"Y Start: 0000";
			// 
			// XEndLabel
			// 
			this->XEndLabel->AutoSize = true;
			this->XEndLabel->Location = System::Drawing::Point(78, 23);
			this->XEndLabel->Name = L"XEndLabel";
			this->XEndLabel->Size = System::Drawing::Size(72, 13);
			this->XEndLabel->TabIndex = 10;
			this->XEndLabel->Text = L"X End: 00000";
			// 
			// BatchComputeBtn
			// 
			this->BatchComputeBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->BatchComputeBtn->Enabled = false;
			this->BatchComputeBtn->Location = System::Drawing::Point(234, 445);
			this->BatchComputeBtn->Name = L"BatchComputeBtn";
			this->BatchComputeBtn->Size = System::Drawing::Size(75, 23);
			this->BatchComputeBtn->TabIndex = 3;
			this->BatchComputeBtn->Text = L"Compute";
			this->BatchComputeBtn->UseVisualStyleBackColor = true;
			this->BatchComputeBtn->Click += gcnew System::EventHandler(this, &Form1::BatchComputeBtn_Click);
			// 
			// BatchOpenListBtn
			// 
			this->BatchOpenListBtn->Location = System::Drawing::Point(3, 4);
			this->BatchOpenListBtn->Name = L"BatchOpenListBtn";
			this->BatchOpenListBtn->Size = System::Drawing::Size(76, 22);
			this->BatchOpenListBtn->TabIndex = 2;
			this->BatchOpenListBtn->Text = L"Open List";
			this->BatchOpenListBtn->UseVisualStyleBackColor = true;
			this->BatchOpenListBtn->Click += gcnew System::EventHandler(this, &Form1::BatchOpenListBtn_Click);
			// 
			// BatchMakeListBtn
			// 
			this->BatchMakeListBtn->Location = System::Drawing::Point(85, 4);
			this->BatchMakeListBtn->Name = L"BatchMakeListBtn";
			this->BatchMakeListBtn->Size = System::Drawing::Size(76, 22);
			this->BatchMakeListBtn->TabIndex = 1;
			this->BatchMakeListBtn->Text = L"Make List";
			this->BatchMakeListBtn->UseVisualStyleBackColor = true;
			this->BatchMakeListBtn->Click += gcnew System::EventHandler(this, &Form1::BatchMakeListBtn_Click);
			// 
			// BatchListNameTxt
			// 
			this->BatchListNameTxt->AutoSize = true;
			this->BatchListNameTxt->Location = System::Drawing::Point(167, 9);
			this->BatchListNameTxt->Name = L"BatchListNameTxt";
			this->BatchListNameTxt->Size = System::Drawing::Size(119, 13);
			this->BatchListNameTxt->TabIndex = 0;
			this->BatchListNameTxt->Text = L"No Batch List File Open";
			// 
			// UVITTab
			// 
			this->UVITTab->BackColor = System::Drawing::Color::Gainsboro;
			this->UVITTab->Controls->Add(this->UVAnalysisPanel);
			this->UVITTab->Controls->Add(this->UVOpenRawBtn);
			this->UVITTab->Controls->Add(this->UVOpenDirBtn);
			this->UVITTab->Controls->Add(this->UVOpenSubDirChck);
			this->UVITTab->Controls->Add(this->CentroidingPanel);
			this->UVITTab->Controls->Add(this->UVBatchViewPanel);
			this->UVITTab->Controls->Add(this->UVOpenCentroidBtn);
			this->UVITTab->Location = System::Drawing::Point(4, 22);
			this->UVITTab->Name = L"UVITTab";
			this->UVITTab->Padding = System::Windows::Forms::Padding(3);
			this->UVITTab->Size = System::Drawing::Size(317, 501);
			this->UVITTab->TabIndex = 3;
			this->UVITTab->Text = L"UVIT";
			// 
			// UVAnalysisPanel
			// 
			this->UVAnalysisPanel->Controls->Add(this->label15);
			this->UVAnalysisPanel->Controls->Add(this->UVPlotXAxisDrop);
			this->UVAnalysisPanel->Controls->Add(this->UVHVUTelemBtn);
			this->UVAnalysisPanel->Controls->Add(this->UVStatsAnalysisBtn);
			this->UVAnalysisPanel->Location = System::Drawing::Point(7, 426);
			this->UVAnalysisPanel->Name = L"UVAnalysisPanel";
			this->UVAnalysisPanel->Size = System::Drawing::Size(296, 56);
			this->UVAnalysisPanel->TabIndex = 41;
			this->UVAnalysisPanel->TabStop = false;
			this->UVAnalysisPanel->Text = L"Frame Sequence Plot Analyses";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(178, 13);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(39, 13);
			this->label15->TabIndex = 3;
			this->label15->Text = L"X Axis:";
			// 
			// UVPlotXAxisDrop
			// 
			this->UVPlotXAxisDrop->FormattingEnabled = true;
			this->UVPlotXAxisDrop->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"Time Tick (mins)", L"Time Imaging (mins)",
					L"Frame Tick (num)"
			});
			this->UVPlotXAxisDrop->Location = System::Drawing::Point(178, 29);
			this->UVPlotXAxisDrop->Name = L"UVPlotXAxisDrop";
			this->UVPlotXAxisDrop->Size = System::Drawing::Size(107, 21);
			this->UVPlotXAxisDrop->TabIndex = 2;
			// 
			// UVHVUTelemBtn
			// 
			this->UVHVUTelemBtn->Location = System::Drawing::Point(85, 22);
			this->UVHVUTelemBtn->Name = L"UVHVUTelemBtn";
			this->UVHVUTelemBtn->Size = System::Drawing::Size(75, 23);
			this->UVHVUTelemBtn->TabIndex = 1;
			this->UVHVUTelemBtn->Text = L"HVU Telem";
			this->UVHVUTelemBtn->UseVisualStyleBackColor = true;
			this->UVHVUTelemBtn->Click += gcnew System::EventHandler(this, &Form1::UVHVUTelemBtn_Click);
			// 
			// UVStatsAnalysisBtn
			// 
			this->UVStatsAnalysisBtn->Location = System::Drawing::Point(6, 22);
			this->UVStatsAnalysisBtn->Name = L"UVStatsAnalysisBtn";
			this->UVStatsAnalysisBtn->Size = System::Drawing::Size(73, 23);
			this->UVStatsAnalysisBtn->TabIndex = 0;
			this->UVStatsAnalysisBtn->Text = L"Frame Stats";
			this->UVStatsAnalysisBtn->UseVisualStyleBackColor = true;
			this->UVStatsAnalysisBtn->Click += gcnew System::EventHandler(this, &Form1::UVStatsAnalysisBtn_Click);
			// 
			// UVOpenRawBtn
			// 
			this->UVOpenRawBtn->AutoSize = true;
			this->UVOpenRawBtn->Location = System::Drawing::Point(7, 12);
			this->UVOpenRawBtn->Name = L"UVOpenRawBtn";
			this->UVOpenRawBtn->Size = System::Drawing::Size(119, 25);
			this->UVOpenRawBtn->TabIndex = 0;
			this->UVOpenRawBtn->Text = L"Select UVIT File(s)";
			this->UVOpenRawBtn->UseVisualStyleBackColor = true;
			this->UVOpenRawBtn->Click += gcnew System::EventHandler(this, &Form1::UVOpenRawBtn_Click);
			// 
			// UVOpenSubDirChck
			// 
			this->UVOpenSubDirChck->AutoSize = true;
			this->UVOpenSubDirChck->Location = System::Drawing::Point(18, 68);
			this->UVOpenSubDirChck->Name = L"UVOpenSubDirChck";
			this->UVOpenSubDirChck->Size = System::Drawing::Size(113, 17);
			this->UVOpenSubDirChck->TabIndex = 40;
			this->UVOpenSubDirChck->Text = L"Include Sub-Paths";
			this->UVOpenSubDirChck->UseVisualStyleBackColor = true;
			// 
			// CentroidingPanel
			// 
			this->CentroidingPanel->Controls->Add(this->UVAutoThreshChck);
			this->CentroidingPanel->Controls->Add(this->groupBox1);
			this->CentroidingPanel->Controls->Add(this->UVTransferImagesBtn);
			this->CentroidingPanel->Controls->Add(this->UVImageOnlyChck);
			this->CentroidingPanel->Controls->Add(this->label13);
			this->CentroidingPanel->Controls->Add(this->UVSaveCentroidDrop);
			this->CentroidingPanel->Controls->Add(this->UVCentroidBtn);
			this->CentroidingPanel->Controls->Add(this->label9);
			this->CentroidingPanel->Controls->Add(this->UVShapeMaxThresh);
			this->CentroidingPanel->Controls->Add(this->label10);
			this->CentroidingPanel->Controls->Add(this->label11);
			this->CentroidingPanel->Controls->Add(this->UVShapeMinThresh);
			this->CentroidingPanel->Controls->Add(this->label8);
			this->CentroidingPanel->Controls->Add(this->UVPixelMaxThresh);
			this->CentroidingPanel->Controls->Add(this->label7);
			this->CentroidingPanel->Controls->Add(this->label6);
			this->CentroidingPanel->Controls->Add(this->UVPixelMinThresh);
			this->CentroidingPanel->Controls->Add(this->UVSubRangeChck);
			this->CentroidingPanel->Controls->Add(this->label5);
			this->CentroidingPanel->Controls->Add(this->label4);
			this->CentroidingPanel->Controls->Add(this->UVAlgorithmListBox);
			this->CentroidingPanel->Controls->Add(this->UVPrecisionUpD);
			this->CentroidingPanel->Enabled = false;
			this->CentroidingPanel->Location = System::Drawing::Point(7, 142);
			this->CentroidingPanel->Name = L"CentroidingPanel";
			this->CentroidingPanel->Size = System::Drawing::Size(295, 277);
			this->CentroidingPanel->TabIndex = 37;
			this->CentroidingPanel->TabStop = false;
			this->CentroidingPanel->Text = L"Centroiding";
			// 
			// UVAutoThreshChck
			// 
			this->UVAutoThreshChck->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->UVAutoThreshChck->Location = System::Drawing::Point(122, 13);
			this->UVAutoThreshChck->Name = L"UVAutoThreshChck";
			this->UVAutoThreshChck->Size = System::Drawing::Size(43, 23);
			this->UVAutoThreshChck->TabIndex = 46;
			this->UVAutoThreshChck->Text = L"Set";
			this->UVAutoThreshChck->UseVisualStyleBackColor = true;
			this->UVAutoThreshChck->Click += gcnew System::EventHandler(this, &Form1::UVAutoThreshChck_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->UVBGOffset);
			this->groupBox1->Controls->Add(this->label17);
			this->groupBox1->Controls->Add(this->UVActiveBGChck);
			this->groupBox1->Controls->Add(this->UVCornerThreshUpD);
			this->groupBox1->Controls->Add(this->UVDarkImageTxt);
			this->groupBox1->Controls->Add(this->UVDarkImageRad);
			this->groupBox1->Controls->Add(this->UVBackGroundUpD);
			this->groupBox1->Controls->Add(this->UVDarkScalarRad);
			this->groupBox1->Controls->Add(this->label19);
			this->groupBox1->Location = System::Drawing::Point(4, 111);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(144, 130);
			this->groupBox1->TabIndex = 45;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Background Correction";
			// 
			// UVBGOffset
			// 
			this->UVBGOffset->DecimalPlaces = 1;
			this->UVBGOffset->Location = System::Drawing::Point(79, 106);
			this->UVBGOffset->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			this->UVBGOffset->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, System::Int32::MinValue });
			this->UVBGOffset->Name = L"UVBGOffset";
			this->UVBGOffset->Size = System::Drawing::Size(58, 20);
			this->UVBGOffset->TabIndex = 46;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(6, 82);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(61, 13);
			this->label17->TabIndex = 46;
			this->label17->Text = L"Corner Max";
			// 
			// UVActiveBGChck
			// 
			this->UVActiveBGChck->AutoSize = true;
			this->UVActiveBGChck->Location = System::Drawing::Point(6, 62);
			this->UVActiveBGChck->Name = L"UVActiveBGChck";
			this->UVActiveBGChck->Size = System::Drawing::Size(56, 17);
			this->UVActiveBGChck->TabIndex = 45;
			this->UVActiveBGChck->Text = L"Active";
			this->UVActiveBGChck->UseVisualStyleBackColor = true;
			this->UVActiveBGChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::UVActiveBGChck_CheckedChanged);
			// 
			// UVCornerThreshUpD
			// 
			this->UVCornerThreshUpD->Enabled = false;
			this->UVCornerThreshUpD->Location = System::Drawing::Point(79, 80);
			this->UVCornerThreshUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 16384, 0, 0, 0 });
			this->UVCornerThreshUpD->Name = L"UVCornerThreshUpD";
			this->UVCornerThreshUpD->Size = System::Drawing::Size(58, 20);
			this->UVCornerThreshUpD->TabIndex = 45;
			this->UVCornerThreshUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 16383, 0, 0, 0 });
			// 
			// UVDarkImageTxt
			// 
			this->UVDarkImageTxt->Location = System::Drawing::Point(66, 41);
			this->UVDarkImageTxt->Name = L"UVDarkImageTxt";
			this->UVDarkImageTxt->Size = System::Drawing::Size(71, 13);
			this->UVDarkImageTxt->TabIndex = 47;
			this->UVDarkImageTxt->Text = L"NA";
			this->UVDarkImageTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// UVDarkImageRad
			// 
			this->UVDarkImageRad->AutoSize = true;
			this->UVDarkImageRad->Location = System::Drawing::Point(6, 39);
			this->UVDarkImageRad->Name = L"UVDarkImageRad";
			this->UVDarkImageRad->Size = System::Drawing::Size(54, 17);
			this->UVDarkImageRad->TabIndex = 46;
			this->UVDarkImageRad->Text = L"Image";
			this->UVDarkImageRad->UseVisualStyleBackColor = true;
			this->UVDarkImageRad->CheckedChanged += gcnew System::EventHandler(this, &Form1::UVDarkImageRad_CheckedChanged);
			// 
			// UVBackGroundUpD
			// 
			this->UVBackGroundUpD->Location = System::Drawing::Point(86, 18);
			this->UVBackGroundUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->UVBackGroundUpD->Name = L"UVBackGroundUpD";
			this->UVBackGroundUpD->Size = System::Drawing::Size(51, 20);
			this->UVBackGroundUpD->TabIndex = 46;
			this->UVBackGroundUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
			// 
			// UVDarkScalarRad
			// 
			this->UVDarkScalarRad->AutoSize = true;
			this->UVDarkScalarRad->Checked = true;
			this->UVDarkScalarRad->Location = System::Drawing::Point(6, 18);
			this->UVDarkScalarRad->Name = L"UVDarkScalarRad";
			this->UVDarkScalarRad->Size = System::Drawing::Size(55, 17);
			this->UVDarkScalarRad->TabIndex = 0;
			this->UVDarkScalarRad->TabStop = true;
			this->UVDarkScalarRad->Text = L"Scalar";
			this->UVDarkScalarRad->UseVisualStyleBackColor = true;
			this->UVDarkScalarRad->CheckedChanged += gcnew System::EventHandler(this, &Form1::UVDarkScalarRad_CheckedChanged);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(6, 108);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(38, 13);
			this->label19->TabIndex = 47;
			this->label19->Text = L"Offset:";
			// 
			// UVTransferImagesBtn
			// 
			this->UVTransferImagesBtn->Enabled = false;
			this->UVTransferImagesBtn->Location = System::Drawing::Point(185, 181);
			this->UVTransferImagesBtn->Name = L"UVTransferImagesBtn";
			this->UVTransferImagesBtn->Size = System::Drawing::Size(100, 23);
			this->UVTransferImagesBtn->TabIndex = 45;
			this->UVTransferImagesBtn->Text = L"Transfer Images";
			this->UVTransferImagesBtn->UseVisualStyleBackColor = true;
			this->UVTransferImagesBtn->Click += gcnew System::EventHandler(this, &Form1::UVTransferImagesBtn_Click);
			// 
			// UVImageOnlyChck
			// 
			this->UVImageOnlyChck->AutoSize = true;
			this->UVImageOnlyChck->Location = System::Drawing::Point(192, 134);
			this->UVImageOnlyChck->Name = L"UVImageOnlyChck";
			this->UVImageOnlyChck->Size = System::Drawing::Size(79, 17);
			this->UVImageOnlyChck->TabIndex = 45;
			this->UVImageOnlyChck->Text = L"Image Only";
			this->UVImageOnlyChck->UseVisualStyleBackColor = true;
			this->UVImageOnlyChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::UVImageOnlyChck_CheckedChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(183, 208);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(93, 13);
			this->label13->TabIndex = 20;
			this->label13->Text = L"Save Centroid List";
			// 
			// UVSaveCentroidDrop
			// 
			this->UVSaveCentroidDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->UVSaveCentroidDrop->Enabled = false;
			this->UVSaveCentroidDrop->FormattingEnabled = true;
			this->UVSaveCentroidDrop->Location = System::Drawing::Point(186, 224);
			this->UVSaveCentroidDrop->Name = L"UVSaveCentroidDrop";
			this->UVSaveCentroidDrop->Size = System::Drawing::Size(99, 21);
			this->UVSaveCentroidDrop->TabIndex = 19;
			this->UVSaveCentroidDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::UVSaveCentroidDrop_SelectedIndexChanged);
			// 
			// UVCentroidBtn
			// 
			this->UVCentroidBtn->Location = System::Drawing::Point(10, 247);
			this->UVCentroidBtn->Name = L"UVCentroidBtn";
			this->UVCentroidBtn->Size = System::Drawing::Size(62, 23);
			this->UVCentroidBtn->TabIndex = 16;
			this->UVCentroidBtn->Text = L"Centroid!";
			this->UVCentroidBtn->UseVisualStyleBackColor = true;
			this->UVCentroidBtn->Click += gcnew System::EventHandler(this, &Form1::UVCentroidBtn_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(92, 87);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(30, 13);
			this->label9->TabIndex = 14;
			this->label9->Text = L"MAX";
			// 
			// UVShapeMaxThresh
			// 
			this->UVShapeMaxThresh->Location = System::Drawing::Point(122, 83);
			this->UVShapeMaxThresh->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1638400, 0, 0, 0 });
			this->UVShapeMaxThresh->Name = L"UVShapeMaxThresh";
			this->UVShapeMaxThresh->Size = System::Drawing::Size(63, 20);
			this->UVShapeMaxThresh->TabIndex = 13;
			this->UVShapeMaxThresh->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1638400, 0, 0, 0 });
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(6, 87);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(27, 13);
			this->label10->TabIndex = 12;
			this->label10->Text = L"MIN";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(6, 66);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(127, 13);
			this->label11->TabIndex = 11;
			this->label11->Text = L"Shape Event Thresholds:";
			// 
			// UVShapeMinThresh
			// 
			this->UVShapeMinThresh->Location = System::Drawing::Point(34, 83);
			this->UVShapeMinThresh->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25600, 0, 0, 0 });
			this->UVShapeMinThresh->Name = L"UVShapeMinThresh";
			this->UVShapeMinThresh->Size = System::Drawing::Size(58, 20);
			this->UVShapeMinThresh->TabIndex = 10;
			this->UVShapeMinThresh->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 800, 0, 0, 0 });
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(92, 43);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(30, 13);
			this->label8->TabIndex = 9;
			this->label8->Text = L"MAX";
			// 
			// UVPixelMaxThresh
			// 
			this->UVPixelMaxThresh->Location = System::Drawing::Point(122, 39);
			this->UVPixelMaxThresh->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			this->UVPixelMaxThresh->Name = L"UVPixelMaxThresh";
			this->UVPixelMaxThresh->Size = System::Drawing::Size(63, 20);
			this->UVPixelMaxThresh->TabIndex = 8;
			this->UVPixelMaxThresh->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 44);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(27, 13);
			this->label7->TabIndex = 7;
			this->label7->Text = L"MIN";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 18);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(118, 13);
			this->label6->TabIndex = 6;
			this->label6->Text = L"Pixel Event Thresholds:";
			// 
			// UVPixelMinThresh
			// 
			this->UVPixelMinThresh->Location = System::Drawing::Point(34, 40);
			this->UVPixelMinThresh->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 16535, 0, 0, 0 });
			this->UVPixelMinThresh->Name = L"UVPixelMinThresh";
			this->UVPixelMinThresh->Size = System::Drawing::Size(58, 20);
			this->UVPixelMinThresh->TabIndex = 5;
			this->UVPixelMinThresh->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
			// 
			// UVSubRangeChck
			// 
			this->UVSubRangeChck->AutoSize = true;
			this->UVSubRangeChck->Location = System::Drawing::Point(192, 117);
			this->UVSubRangeChck->Name = L"UVSubRangeChck";
			this->UVSubRangeChck->Size = System::Drawing::Size(77, 17);
			this->UVSubRangeChck->TabIndex = 4;
			this->UVSubRangeChck->Text = L"Sub Image";
			this->UVSubRangeChck->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(185, 18);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(108, 13);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Select Agorithm Type";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(199, 157);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(50, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Precision";
			// 
			// UVAlgorithmListBox
			// 
			this->UVAlgorithmListBox->ContextMenuStrip = this->UVAlgorithmCntxt;
			this->UVAlgorithmListBox->FormattingEnabled = true;
			this->UVAlgorithmListBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"3x3_Cross", L"3x3_Square", L"3x3_Gaussian",
					L"5x5_Cross", L"5x5_Square"
			});
			this->UVAlgorithmListBox->Location = System::Drawing::Point(188, 34);
			this->UVAlgorithmListBox->Name = L"UVAlgorithmListBox";
			this->UVAlgorithmListBox->Size = System::Drawing::Size(97, 79);
			this->UVAlgorithmListBox->TabIndex = 2;
			// 
			// UVAlgorithmCntxt
			// 
			this->UVAlgorithmCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->UVXDecHist,
					this->UVYDecHist, this->UVPixelHist, this->UVShapeHist, this->UVFCMinHist, this->UVFCMaxMinHist, this->UVFrameHist
			});
			this->UVAlgorithmCntxt->Name = L"UVAlgorithmCntxtMenu";
			this->UVAlgorithmCntxt->ShowImageMargin = false;
			this->UVAlgorithmCntxt->Size = System::Drawing::Size(197, 158);
			// 
			// UVXDecHist
			// 
			this->UVXDecHist->Name = L"UVXDecHist";
			this->UVXDecHist->Size = System::Drawing::Size(196, 22);
			this->UVXDecHist->Text = L"X-Decimal Histogram";
			this->UVXDecHist->ToolTipText = L"Use \'Precision\' to set number of divisions.";
			this->UVXDecHist->Click += gcnew System::EventHandler(this, &Form1::UVXDecHist_Click);
			// 
			// UVYDecHist
			// 
			this->UVYDecHist->Name = L"UVYDecHist";
			this->UVYDecHist->Size = System::Drawing::Size(196, 22);
			this->UVYDecHist->Text = L"Y-Decimal Histogram";
			this->UVYDecHist->ToolTipText = L"Use \'Precision\' to set number of divisions.";
			this->UVYDecHist->Click += gcnew System::EventHandler(this, &Form1::UVYDecHist_Click);
			// 
			// UVPixelHist
			// 
			this->UVPixelHist->Name = L"UVPixelHist";
			this->UVPixelHist->Size = System::Drawing::Size(196, 22);
			this->UVPixelHist->Text = L"Pixel Energy Histogram";
			this->UVPixelHist->Click += gcnew System::EventHandler(this, &Form1::UVPixelHist_Click);
			// 
			// UVShapeHist
			// 
			this->UVShapeHist->Name = L"UVShapeHist";
			this->UVShapeHist->Size = System::Drawing::Size(196, 22);
			this->UVShapeHist->Text = L"Shape Energy Histogram";
			this->UVShapeHist->Click += gcnew System::EventHandler(this, &Form1::UVShapeHist_Click);
			// 
			// UVFCMinHist
			// 
			this->UVFCMinHist->Name = L"UVFCMinHist";
			this->UVFCMinHist->Size = System::Drawing::Size(196, 22);
			this->UVFCMinHist->Text = L"Corner Min Histogram";
			this->UVFCMinHist->Click += gcnew System::EventHandler(this, &Form1::UVFCMinHist_Click);
			// 
			// UVFCMaxMinHist
			// 
			this->UVFCMaxMinHist->Name = L"UVFCMaxMinHist";
			this->UVFCMaxMinHist->Size = System::Drawing::Size(196, 22);
			this->UVFCMaxMinHist->Text = L"Corner Max-Min Histogram";
			this->UVFCMaxMinHist->Click += gcnew System::EventHandler(this, &Form1::UVFCMaxMinHist_Click);
			// 
			// UVFrameHist
			// 
			this->UVFrameHist->Name = L"UVFrameHist";
			this->UVFrameHist->Size = System::Drawing::Size(196, 22);
			this->UVFrameHist->Text = L"Frame # Histogram";
			this->UVFrameHist->Click += gcnew System::EventHandler(this, &Form1::UVFrameHist_Click);
			// 
			// UVPrecisionUpD
			// 
			this->UVPrecisionUpD->Enabled = false;
			this->UVPrecisionUpD->Location = System::Drawing::Point(251, 155);
			this->UVPrecisionUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32, 0, 0, 0 });
			this->UVPrecisionUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->UVPrecisionUpD->Name = L"UVPrecisionUpD";
			this->UVPrecisionUpD->Size = System::Drawing::Size(34, 20);
			this->UVPrecisionUpD->TabIndex = 0;
			this->UVPrecisionUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// UVBatchViewPanel
			// 
			this->UVBatchViewPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->UVBatchViewPanel->Controls->Add(this->UVMovieSkipUpD);
			this->UVBatchViewPanel->Controls->Add(this->label14);
			this->UVBatchViewPanel->Controls->Add(this->UVGoToBtn);
			this->UVBatchViewPanel->Controls->Add(this->UVBlinkTimeUpD);
			this->UVBatchViewPanel->Controls->Add(this->UVMovieBtn);
			this->UVBatchViewPanel->Controls->Add(this->UVViewSelectionStatic);
			this->UVBatchViewPanel->Controls->Add(this->UVViewNextBtn);
			this->UVBatchViewPanel->Controls->Add(this->UVGoToUpD);
			this->UVBatchViewPanel->Controls->Add(this->UVViewLastBtn);
			this->UVBatchViewPanel->Enabled = false;
			this->UVBatchViewPanel->Location = System::Drawing::Point(144, 14);
			this->UVBatchViewPanel->Name = L"UVBatchViewPanel";
			this->UVBatchViewPanel->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->UVBatchViewPanel->Size = System::Drawing::Size(157, 128);
			this->UVBatchViewPanel->TabIndex = 36;
			this->UVBatchViewPanel->TabStop = false;
			this->UVBatchViewPanel->Text = L"Quick Viewing";
			// 
			// UVMovieSkipUpD
			// 
			this->UVMovieSkipUpD->Location = System::Drawing::Point(73, 78);
			this->UVMovieSkipUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->UVMovieSkipUpD->Name = L"UVMovieSkipUpD";
			this->UVMovieSkipUpD->Size = System::Drawing::Size(73, 20);
			this->UVMovieSkipUpD->TabIndex = 47;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(36, 78);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(31, 13);
			this->label14->TabIndex = 46;
			this->label14->Text = L"Skip:";
			// 
			// UVGoToBtn
			// 
			this->UVGoToBtn->Location = System::Drawing::Point(15, 102);
			this->UVGoToBtn->Name = L"UVGoToBtn";
			this->UVGoToBtn->Size = System::Drawing::Size(52, 21);
			this->UVGoToBtn->TabIndex = 45;
			this->UVGoToBtn->Text = L"Go To:";
			this->UVGoToBtn->UseVisualStyleBackColor = true;
			this->UVGoToBtn->Click += gcnew System::EventHandler(this, &Form1::UVGoToBtn_Click);
			// 
			// UVBlinkTimeUpD
			// 
			this->UVBlinkTimeUpD->DecimalPlaces = 1;
			this->UVBlinkTimeUpD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->UVBlinkTimeUpD->Location = System::Drawing::Point(56, 52);
			this->UVBlinkTimeUpD->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->UVBlinkTimeUpD->Name = L"UVBlinkTimeUpD";
			this->UVBlinkTimeUpD->Size = System::Drawing::Size(49, 20);
			this->UVBlinkTimeUpD->TabIndex = 37;
			this->UVBlinkTimeUpD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->UVBlinkTimeUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 65536 });
			// 
			// UVMovieBtn
			// 
			this->UVMovieBtn->Appearance = System::Windows::Forms::Appearance::Button;
			this->UVMovieBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->UVMovieBtn->Location = System::Drawing::Point(56, 32);
			this->UVMovieBtn->Name = L"UVMovieBtn";
			this->UVMovieBtn->Size = System::Drawing::Size(49, 20);
			this->UVMovieBtn->TabIndex = 22;
			this->UVMovieBtn->Text = L"Scan";
			this->UVMovieBtn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->UVMovieBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::UVMovieBtn_CheckedChanged);
			// 
			// UVViewSelectionStatic
			// 
			this->UVViewSelectionStatic->Location = System::Drawing::Point(9, 16);
			this->UVViewSelectionStatic->Name = L"UVViewSelectionStatic";
			this->UVViewSelectionStatic->Size = System::Drawing::Size(144, 15);
			this->UVViewSelectionStatic->TabIndex = 19;
			this->UVViewSelectionStatic->Text = L"Viewing File 0 of 0";
			// 
			// UVGoToUpD
			// 
			this->UVGoToUpD->Location = System::Drawing::Point(74, 102);
			this->UVGoToUpD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->UVGoToUpD->Name = L"UVGoToUpD";
			this->UVGoToUpD->Size = System::Drawing::Size(73, 20);
			this->UVGoToUpD->TabIndex = 45;
			this->UVGoToUpD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// UVOpenCentroidBtn
			// 
			this->UVOpenCentroidBtn->Location = System::Drawing::Point(7, 92);
			this->UVOpenCentroidBtn->Name = L"UVOpenCentroidBtn";
			this->UVOpenCentroidBtn->Size = System::Drawing::Size(108, 25);
			this->UVOpenCentroidBtn->TabIndex = 39;
			this->UVOpenCentroidBtn->Text = L"Open Centroid File";
			this->UVOpenCentroidBtn->UseVisualStyleBackColor = true;
			this->UVOpenCentroidBtn->Click += gcnew System::EventHandler(this, &Form1::UVOpenCentroidBtn_Click);
			// 
			// XYImageValueTxt
			// 
			this->XYImageValueTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->XYImageValueTxt->BackColor = System::Drawing::Color::DodgerBlue;
			this->XYImageValueTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->XYImageValueTxt->Location = System::Drawing::Point(280, 853);
			this->XYImageValueTxt->Name = L"XYImageValueTxt";
			this->XYImageValueTxt->Size = System::Drawing::Size(120, 15);
			this->XYImageValueTxt->TabIndex = 28;
			this->XYImageValueTxt->Text = L"xyVal";
			this->XYImageValueTxt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->XYImageValueTxt->Visible = false;
			// 
			// YPositionTxt
			// 
			this->YPositionTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->YPositionTxt->BackColor = System::Drawing::Color::DodgerBlue;
			this->YPositionTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->YPositionTxt->Location = System::Drawing::Point(178, 853);
			this->YPositionTxt->Margin = System::Windows::Forms::Padding(0);
			this->YPositionTxt->Name = L"YPositionTxt";
			this->YPositionTxt->Size = System::Drawing::Size(99, 15);
			this->YPositionTxt->TabIndex = 27;
			this->YPositionTxt->Text = L"yPos";
			this->YPositionTxt->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->YPositionTxt->Visible = false;
			// 
			// XPositionTxt
			// 
			this->XPositionTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->XPositionTxt->BackColor = System::Drawing::Color::DodgerBlue;
			this->XPositionTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->XPositionTxt->Location = System::Drawing::Point(56, 853);
			this->XPositionTxt->Margin = System::Windows::Forms::Padding(0);
			this->XPositionTxt->Name = L"XPositionTxt";
			this->XPositionTxt->Size = System::Drawing::Size(99, 15);
			this->XPositionTxt->TabIndex = 26;
			this->XPositionTxt->Text = L"xPos";
			this->XPositionTxt->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->XPositionTxt->Visible = false;
			// 
			// ToolBarImageList
			// 
			this->ToolBarImageList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"ToolBarImageList.ImageStream")));
			this->ToolBarImageList->TransparentColor = System::Drawing::Color::Transparent;
			this->ToolBarImageList->Images->SetKeyName(0, L"");
			this->ToolBarImageList->Images->SetKeyName(1, L"openadd.bmp");
			this->ToolBarImageList->Images->SetKeyName(2, L"");
			this->ToolBarImageList->Images->SetKeyName(3, L"");
			this->ToolBarImageList->Images->SetKeyName(4, L"");
			this->ToolBarImageList->Images->SetKeyName(5, L"");
			this->ToolBarImageList->Images->SetKeyName(6, L"");
			this->ToolBarImageList->Images->SetKeyName(7, L"");
			// 
			// SaveFileDlg
			// 
			this->SaveFileDlg->Filter = L"Fits File (*.fts)|*.fts|Fits File (*.fit)|*.fit|Fits File (*.fits)|*.fits|UVIT *."
				L"raw File (*.raw)|*.raw|JPEG (*.jpg)|*.jpg|ZIP (*.zip)|*.zip";
			this->SaveFileDlg->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::SaveFileDialog_FileOk);
			// 
			// ImageWindow
			// 
			this->ImageWindow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ImageWindow->BackColor = System::Drawing::Color::Silver;
			this->ImageWindow->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ImageWindow->Cursor = System::Windows::Forms::Cursors::Cross;
			this->ImageWindow->Location = System::Drawing::Point(35, 41);
			this->ImageWindow->Name = L"ImageWindow";
			this->ImageWindow->Size = System::Drawing::Size(812, 812);
			this->ImageWindow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->ImageWindow->TabIndex = 25;
			this->ImageWindow->TabStop = false;
			this->ImageWindow->SizeChanged += gcnew System::EventHandler(this, &Form1::ImageWindow_SizeChanged);
			this->ImageWindow->Click += gcnew System::EventHandler(this, &Form1::ImageWindow_Click);
			this->ImageWindow->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::ImageWindow_Paint);
			this->ImageWindow->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageWindow_MouseClick);
			this->ImageWindow->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageWindow_MouseDoubleClick);
			this->ImageWindow->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageWindow_MouseDown);
			this->ImageWindow->MouseEnter += gcnew System::EventHandler(this, &Form1::ImageWindow_MouseEnter);
			this->ImageWindow->MouseLeave += gcnew System::EventHandler(this, &Form1::ImageWindow_MouseLeave);
			this->ImageWindow->MouseHover += gcnew System::EventHandler(this, &Form1::ImageWindow_MouseHover);
			this->ImageWindow->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageWindow_MouseMove);
			this->ImageWindow->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageWindow_MouseUp);
			this->ImageWindow->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::ImageWindow_MouseWheel);
			// 
			// ViewHeaderBtn
			// 
			this->ViewHeaderBtn->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->ViewHeaderBtn->Appearance = System::Windows::Forms::Appearance::Button;
			this->ViewHeaderBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ViewHeaderBtn->Enabled = false;
			this->ViewHeaderBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ViewHeaderBtn->Location = System::Drawing::Point(406, 24);
			this->ViewHeaderBtn->Name = L"ViewHeaderBtn";
			this->ViewHeaderBtn->Size = System::Drawing::Size(70, 17);
			this->ViewHeaderBtn->TabIndex = 39;
			this->ViewHeaderBtn->Text = L"HEADER";
			this->ViewHeaderBtn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->ViewHeaderBtn->UseVisualStyleBackColor = true;
			this->ViewHeaderBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::ViewHeaderBtn_CheckedChanged);
			// 
			// HeaderCntxt
			// 
			this->HeaderCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->HCEdit, this->HCInsert,
					this->HCRemove, this->HCCopy, this->HCExtract, this->HCPlot
			});
			this->HeaderCntxt->Name = L"HeaderCntxtMenu";
			this->HeaderCntxt->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->HeaderCntxt->ShowImageMargin = false;
			this->HeaderCntxt->Size = System::Drawing::Size(205, 136);
			this->HeaderCntxt->Click += gcnew System::EventHandler(this, &Form1::HeaderCntxtMenu_Click);
			// 
			// HCEdit
			// 
			this->HCEdit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->HCEditCurrent,
					this->HCEditAll
			});
			this->HCEdit->Name = L"HCEdit";
			this->HCEdit->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::E));
			this->HCEdit->ShowShortcutKeys = false;
			this->HCEdit->Size = System::Drawing::Size(204, 22);
			this->HCEdit->Text = L"Edit Key";
			this->HCEdit->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// HCEditCurrent
			// 
			this->HCEditCurrent->Name = L"HCEditCurrent";
			this->HCEditCurrent->Size = System::Drawing::Size(237, 22);
			this->HCEditCurrent->Text = L"Selected Key in Current Header";
			this->HCEditCurrent->Click += gcnew System::EventHandler(this, &Form1::HCEdit_Click);
			// 
			// HCEditAll
			// 
			this->HCEditAll->Name = L"HCEditAll";
			this->HCEditAll->Size = System::Drawing::Size(237, 22);
			this->HCEditAll->Text = L"Selected Key in All Headers";
			this->HCEditAll->Click += gcnew System::EventHandler(this, &Form1::HCEditAll_Click);
			// 
			// HCInsert
			// 
			this->HCInsert->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->HCInsertCurrent,
					this->HCInsertBatch, this->HCInsertSelectedToOthers
			});
			this->HCInsert->Name = L"HCInsert";
			this->HCInsert->Size = System::Drawing::Size(204, 22);
			this->HCInsert->Text = L"Insert";
			this->HCInsert->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// HCInsertCurrent
			// 
			this->HCInsertCurrent->Name = L"HCInsertCurrent";
			this->HCInsertCurrent->Size = System::Drawing::Size(263, 22);
			this->HCInsertCurrent->Text = L"New Key to Current Header";
			this->HCInsertCurrent->Click += gcnew System::EventHandler(this, &Form1::HCInsertCurrent_Click);
			// 
			// HCInsertBatch
			// 
			this->HCInsertBatch->Enabled = false;
			this->HCInsertBatch->Name = L"HCInsertBatch";
			this->HCInsertBatch->Size = System::Drawing::Size(263, 22);
			this->HCInsertBatch->Text = L"New Key to All Headers";
			this->HCInsertBatch->Click += gcnew System::EventHandler(this, &Form1::HCInsertBatch_Click);
			// 
			// HCInsertSelectedToOthers
			// 
			this->HCInsertSelectedToOthers->Name = L"HCInsertSelectedToOthers";
			this->HCInsertSelectedToOthers->Size = System::Drawing::Size(263, 22);
			this->HCInsertSelectedToOthers->Text = L"Selected Key(s) to All Other Headers";
			this->HCInsertSelectedToOthers->Click += gcnew System::EventHandler(this, &Form1::HCInsertSelectedToOthers_Click);
			// 
			// HCRemove
			// 
			this->HCRemove->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->HCRemoveCurrent,
					this->HCRemoveBatch
			});
			this->HCRemove->Name = L"HCRemove";
			this->HCRemove->Size = System::Drawing::Size(204, 22);
			this->HCRemove->Text = L"Remove";
			// 
			// HCRemoveCurrent
			// 
			this->HCRemoveCurrent->Name = L"HCRemoveCurrent";
			this->HCRemoveCurrent->Size = System::Drawing::Size(266, 22);
			this->HCRemoveCurrent->Text = L"Selected Key(s) from Current Header";
			this->HCRemoveCurrent->Click += gcnew System::EventHandler(this, &Form1::HCRemoveCurrent_Click);
			// 
			// HCRemoveBatch
			// 
			this->HCRemoveBatch->Enabled = false;
			this->HCRemoveBatch->Name = L"HCRemoveBatch";
			this->HCRemoveBatch->Size = System::Drawing::Size(266, 22);
			this->HCRemoveBatch->Text = L"Selected Key(s) from All Headers";
			this->HCRemoveBatch->Click += gcnew System::EventHandler(this, &Form1::HCRemoveBatch_Click);
			// 
			// HCCopy
			// 
			this->HCCopy->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->HCCopyKeyValue,
					this->HCCopyListValue
			});
			this->HCCopy->Name = L"HCCopy";
			this->HCCopy->Size = System::Drawing::Size(204, 22);
			this->HCCopy->Text = L"Copy Key Values to Clipboard";
			// 
			// HCCopyKeyValue
			// 
			this->HCCopyKeyValue->Name = L"HCCopyKeyValue";
			this->HCCopyKeyValue->Size = System::Drawing::Size(212, 22);
			this->HCCopyKeyValue->Text = L"Loaded Images Key Values";
			this->HCCopyKeyValue->Click += gcnew System::EventHandler(this, &Form1::HCCopyKeyValue_Click);
			// 
			// HCCopyListValue
			// 
			this->HCCopyListValue->Name = L"HCCopyListValue";
			this->HCCopyListValue->Size = System::Drawing::Size(212, 22);
			this->HCCopyListValue->Text = L"Found File List Key Values";
			this->HCCopyListValue->Click += gcnew System::EventHandler(this, &Form1::HCCopyListValue_Click);
			// 
			// HCExtract
			// 
			this->HCExtract->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->HCExtractKeyValue,
					this->HCExtractListValues
			});
			this->HCExtract->Name = L"HCExtract";
			this->HCExtract->Size = System::Drawing::Size(204, 22);
			this->HCExtract->Text = L"Extract Key Values to File";
			// 
			// HCExtractKeyValue
			// 
			this->HCExtractKeyValue->Name = L"HCExtractKeyValue";
			this->HCExtractKeyValue->Size = System::Drawing::Size(212, 22);
			this->HCExtractKeyValue->Text = L"Loaded Images Key Values";
			this->HCExtractKeyValue->Click += gcnew System::EventHandler(this, &Form1::HCExtractKeyValue_Click);
			// 
			// HCExtractListValues
			// 
			this->HCExtractListValues->Name = L"HCExtractListValues";
			this->HCExtractListValues->Size = System::Drawing::Size(212, 22);
			this->HCExtractListValues->Text = L"Found File List Key Values";
			this->HCExtractListValues->Click += gcnew System::EventHandler(this, &Form1::HCExtractListValues_Click);
			// 
			// HCPlot
			// 
			this->HCPlot->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->HCPlotKeyValues,
					this->HCPlotListValues
			});
			this->HCPlot->Name = L"HCPlot";
			this->HCPlot->Size = System::Drawing::Size(204, 22);
			this->HCPlot->Text = L"Plot Key Values";
			// 
			// HCPlotKeyValues
			// 
			this->HCPlotKeyValues->Name = L"HCPlotKeyValues";
			this->HCPlotKeyValues->Size = System::Drawing::Size(212, 22);
			this->HCPlotKeyValues->Text = L"Loaded Images Key Values";
			this->HCPlotKeyValues->Click += gcnew System::EventHandler(this, &Form1::HCPlotKeyValues_Click);
			// 
			// HCPlotListValues
			// 
			this->HCPlotListValues->Name = L"HCPlotListValues";
			this->HCPlotListValues->Size = System::Drawing::Size(212, 22);
			this->HCPlotListValues->Text = L"Found File List Key Values";
			this->HCPlotListValues->Click += gcnew System::EventHandler(this, &Form1::HCPlotListValues_Click);
			// 
			// HeaderKeyValTxt
			// 
			this->HeaderKeyValTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->HeaderKeyValTxt->BackColor = System::Drawing::Color::LightGray;
			this->HeaderKeyValTxt->ContextMenuStrip = this->HeaderCntxt;
			this->HeaderKeyValTxt->FormattingEnabled = true;
			this->HeaderKeyValTxt->HorizontalScrollbar = true;
			this->HeaderKeyValTxt->Location = System::Drawing::Point(258, 41);
			this->HeaderKeyValTxt->Name = L"HeaderKeyValTxt";
			this->HeaderKeyValTxt->ScrollAlwaysVisible = true;
			this->HeaderKeyValTxt->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->HeaderKeyValTxt->Size = System::Drawing::Size(186, 797);
			this->HeaderKeyValTxt->TabIndex = 41;
			this->HeaderKeyValTxt->Visible = false;
			this->HeaderKeyValTxt->DoubleClick += gcnew System::EventHandler(this, &Form1::HCEdit_Click);
			this->HeaderKeyValTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::HeaderKeyTxt_KeyDown);
			this->HeaderKeyValTxt->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::HeaderKeyTxt_MouseUp);
			// 
			// HeaderKeyComTxt
			// 
			this->HeaderKeyComTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->HeaderKeyComTxt->BackColor = System::Drawing::Color::LightGray;
			this->HeaderKeyComTxt->ContextMenuStrip = this->HeaderCntxt;
			this->HeaderKeyComTxt->FormattingEnabled = true;
			this->HeaderKeyComTxt->HorizontalScrollbar = true;
			this->HeaderKeyComTxt->Location = System::Drawing::Point(444, 41);
			this->HeaderKeyComTxt->Name = L"HeaderKeyComTxt";
			this->HeaderKeyComTxt->ScrollAlwaysVisible = true;
			this->HeaderKeyComTxt->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->HeaderKeyComTxt->Size = System::Drawing::Size(306, 797);
			this->HeaderKeyComTxt->TabIndex = 42;
			this->HeaderKeyComTxt->Visible = false;
			this->HeaderKeyComTxt->DoubleClick += gcnew System::EventHandler(this, &Form1::HCEdit_Click);
			this->HeaderKeyComTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::HeaderKeyTxt_KeyDown);
			this->HeaderKeyComTxt->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::HeaderKeyTxt_MouseUp);
			// 
			// HeaderKeyTxt
			// 
			this->HeaderKeyTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->HeaderKeyTxt->BackColor = System::Drawing::Color::LightGray;
			this->HeaderKeyTxt->ContextMenuStrip = this->HeaderCntxt;
			this->HeaderKeyTxt->FormattingEnabled = true;
			this->HeaderKeyTxt->HorizontalScrollbar = true;
			this->HeaderKeyTxt->Location = System::Drawing::Point(159, 41);
			this->HeaderKeyTxt->Name = L"HeaderKeyTxt";
			this->HeaderKeyTxt->ScrollAlwaysVisible = true;
			this->HeaderKeyTxt->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->HeaderKeyTxt->Size = System::Drawing::Size(99, 797);
			this->HeaderKeyTxt->TabIndex = 43;
			this->HeaderKeyTxt->Visible = false;
			this->HeaderKeyTxt->DoubleClick += gcnew System::EventHandler(this, &Form1::HCEdit_Click);
			this->HeaderKeyTxt->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::HeaderKeyTxt_KeyDown);
			this->HeaderKeyTxt->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::HeaderKeyTxt_MouseUp);
			// 
			// MainMenu
			// 
			this->MainMenu->BackColor = System::Drawing::Color::Gainsboro;
			this->MainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->FileMenu, this->EditMenu,
					this->OptsMenu, this->WCSMenu, this->UVITMenu, this->aboutToolStripMenuItem
			});
			this->MainMenu->Location = System::Drawing::Point(0, 0);
			this->MainMenu->Name = L"MainMenu";
			this->MainMenu->Size = System::Drawing::Size(1424, 24);
			this->MainMenu->TabIndex = 44;
			this->MainMenu->Text = L"menuStrip1";
			// 
			// FileMenu
			// 
			this->FileMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(13) {
				this->FMLoad, this->FMAdd,
					this->FMReload, this->FMRecentFiles, this->toolStripSeparator2, this->FMFind, this->FMViewFound, this->FMOpenFound, this->toolStripSeparator3,
					this->FMSave, this->FMSaveBatch, this->toolStripSeparator4, this->FMQuit
			});
			this->FileMenu->Name = L"FileMenu";
			this->FileMenu->Size = System::Drawing::Size(37, 20);
			this->FileMenu->Text = L"&File";
			// 
			// FMLoad
			// 
			this->FMLoad->DoubleClickEnabled = true;
			this->FMLoad->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->FMLoadSubFrame,
					this->ConvertFromTextMenu, this->FMViewExtensionTable
			});
			this->FMLoad->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMLoad.Image")));
			this->FMLoad->Name = L"FMLoad";
			this->FMLoad->Size = System::Drawing::Size(152, 22);
			this->FMLoad->Text = L"&Open File(s)";
			this->FMLoad->DoubleClick += gcnew System::EventHandler(this, &Form1::FMLoad_Click);
			// 
			// FMLoadSubFrame
			// 
			this->FMLoadSubFrame->Name = L"FMLoadSubFrame";
			this->FMLoadSubFrame->Size = System::Drawing::Size(198, 22);
			this->FMLoadSubFrame->Text = L"Open File Sub-Frame(s)";
			this->FMLoadSubFrame->Click += gcnew System::EventHandler(this, &Form1::FMLoadSubFrame_Click);
			// 
			// ConvertFromTextMenu
			// 
			this->ConvertFromTextMenu->Name = L"ConvertFromTextMenu";
			this->ConvertFromTextMenu->Size = System::Drawing::Size(198, 22);
			this->ConvertFromTextMenu->Text = L"Convert From Text";
			this->ConvertFromTextMenu->Click += gcnew System::EventHandler(this, &Form1::ConvertFromTextMenu_Click);
			// 
			// FMViewExtensionTable
			// 
			this->FMViewExtensionTable->Name = L"FMViewExtensionTable";
			this->FMViewExtensionTable->Size = System::Drawing::Size(198, 22);
			this->FMViewExtensionTable->Text = L"View Extension Table";
			this->FMViewExtensionTable->Click += gcnew System::EventHandler(this, &Form1::FMViewExtensionTable_Click);
			// 
			// FMAdd
			// 
			this->FMAdd->Enabled = false;
			this->FMAdd->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMAdd.Image")));
			this->FMAdd->Name = L"FMAdd";
			this->FMAdd->Size = System::Drawing::Size(152, 22);
			this->FMAdd->Text = L"&Add File(s)";
			this->FMAdd->Click += gcnew System::EventHandler(this, &Form1::FMAdd_Click);
			// 
			// FMReload
			// 
			this->FMReload->Enabled = false;
			this->FMReload->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMReload.Image")));
			this->FMReload->Name = L"FMReload";
			this->FMReload->Size = System::Drawing::Size(152, 22);
			this->FMReload->Text = L"&Reload File(s)";
			this->FMReload->Click += gcnew System::EventHandler(this, &Form1::FMReload_Click);
			// 
			// FMRecentFiles
			// 
			this->FMRecentFiles->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMRecentFiles.Image")));
			this->FMRecentFiles->Name = L"FMRecentFiles";
			this->FMRecentFiles->Size = System::Drawing::Size(152, 22);
			this->FMRecentFiles->Text = L"Recent Files";
			this->FMRecentFiles->Visible = false;
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(149, 6);
			// 
			// FMFind
			// 
			this->FMFind->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMFind.Image")));
			this->FMFind->Name = L"FMFind";
			this->FMFind->Size = System::Drawing::Size(152, 22);
			this->FMFind->Text = L"&Find File(s)";
			this->FMFind->Click += gcnew System::EventHandler(this, &Form1::FMFind_Click);
			// 
			// FMViewFound
			// 
			this->FMViewFound->Enabled = false;
			this->FMViewFound->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMViewFound.Image")));
			this->FMViewFound->Name = L"FMViewFound";
			this->FMViewFound->Size = System::Drawing::Size(152, 22);
			this->FMViewFound->Text = L"&View List";
			this->FMViewFound->Click += gcnew System::EventHandler(this, &Form1::FMViewFound_Click);
			// 
			// FMOpenFound
			// 
			this->FMOpenFound->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMOpenFound.Image")));
			this->FMOpenFound->Name = L"FMOpenFound";
			this->FMOpenFound->Size = System::Drawing::Size(152, 22);
			this->FMOpenFound->Text = L"Open &List";
			this->FMOpenFound->Click += gcnew System::EventHandler(this, &Form1::TBOpenFound_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(149, 6);
			// 
			// FMSave
			// 
			this->FMSave->Enabled = false;
			this->FMSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMSave.Image")));
			this->FMSave->Name = L"FMSave";
			this->FMSave->Size = System::Drawing::Size(152, 22);
			this->FMSave->Text = L"&Save File";
			this->FMSave->Click += gcnew System::EventHandler(this, &Form1::FMSave_Click);
			// 
			// FMSaveBatch
			// 
			this->FMSaveBatch->Enabled = false;
			this->FMSaveBatch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMSaveBatch.Image")));
			this->FMSaveBatch->Name = L"FMSaveBatch";
			this->FMSaveBatch->Size = System::Drawing::Size(152, 22);
			this->FMSaveBatch->Text = L"Save File &Batch";
			this->FMSaveBatch->Click += gcnew System::EventHandler(this, &Form1::TBSaveBatch_Click);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(149, 6);
			// 
			// FMQuit
			// 
			this->FMQuit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"FMQuit.Image")));
			this->FMQuit->Name = L"FMQuit";
			this->FMQuit->Size = System::Drawing::Size(152, 22);
			this->FMQuit->Text = L"&QUIT";
			this->FMQuit->Click += gcnew System::EventHandler(this, &Form1::FMQuit_Click);
			// 
			// EditMenu
			// 
			this->EditMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->EMFile, this->EMBatch,
					this->EMCopyHeader
			});
			this->EditMenu->Name = L"EditMenu";
			this->EditMenu->Size = System::Drawing::Size(39, 20);
			this->EditMenu->Text = L"&Edit";
			// 
			// EMFile
			// 
			this->EMFile->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->EMFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->EMFileBias, this->EMFileDark,
					this->EMFileFlat
			});
			this->EMFile->Enabled = false;
			this->EMFile->Name = L"EMFile";
			this->EMFile->Size = System::Drawing::Size(143, 22);
			this->EMFile->Text = L"Current &File";
			// 
			// EMFileBias
			// 
			this->EMFileBias->Name = L"EMFileBias";
			this->EMFileBias->Size = System::Drawing::Size(145, 22);
			this->EMFileBias->Text = L"Subtract &Bias";
			this->EMFileBias->Click += gcnew System::EventHandler(this, &Form1::EMFileBias_Click);
			// 
			// EMFileDark
			// 
			this->EMFileDark->Name = L"EMFileDark";
			this->EMFileDark->Size = System::Drawing::Size(145, 22);
			this->EMFileDark->Text = L"Subtract &Dark";
			// 
			// EMFileFlat
			// 
			this->EMFileFlat->Name = L"EMFileFlat";
			this->EMFileFlat->Size = System::Drawing::Size(145, 22);
			this->EMFileFlat->Text = L"Divide &Flat";
			// 
			// EMBatch
			// 
			this->EMBatch->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->EMBatch->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->EMBatchBias,
					this->EMBatchDark, this->EMBatchFlat
			});
			this->EMBatch->Enabled = false;
			this->EMBatch->Name = L"EMBatch";
			this->EMBatch->Size = System::Drawing::Size(143, 22);
			this->EMBatch->Text = L"&Batch";
			// 
			// EMBatchBias
			// 
			this->EMBatchBias->Name = L"EMBatchBias";
			this->EMBatchBias->Size = System::Drawing::Size(145, 22);
			this->EMBatchBias->Text = L"Subtract &Bias";
			// 
			// EMBatchDark
			// 
			this->EMBatchDark->Name = L"EMBatchDark";
			this->EMBatchDark->Size = System::Drawing::Size(145, 22);
			this->EMBatchDark->Text = L"Subtract &Dark";
			// 
			// EMBatchFlat
			// 
			this->EMBatchFlat->Name = L"EMBatchFlat";
			this->EMBatchFlat->Size = System::Drawing::Size(145, 22);
			this->EMBatchFlat->Text = L"Divide &Flat";
			this->EMBatchFlat->Click += gcnew System::EventHandler(this, &Form1::EMBatchFlat_Click);
			// 
			// EMCopyHeader
			// 
			this->EMCopyHeader->Name = L"EMCopyHeader";
			this->EMCopyHeader->Size = System::Drawing::Size(143, 22);
			this->EMCopyHeader->Text = L"Copy Header";
			this->EMCopyHeader->Click += gcnew System::EventHandler(this, &Form1::EMCopyHeader_Click);
			// 
			// OptsMenu
			// 
			this->OptsMenu->BackColor = System::Drawing::Color::Gainsboro;
			this->OptsMenu->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->OptsMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileSavingPrecisionToolStripMenuItem,
					this->veiwToolStripMenuItem, this->ResetPlotPositions
			});
			this->OptsMenu->ForeColor = System::Drawing::SystemColors::ControlText;
			this->OptsMenu->Name = L"OptsMenu";
			this->OptsMenu->Size = System::Drawing::Size(61, 20);
			this->OptsMenu->Text = L"Options";
			// 
			// fileSavingPrecisionToolStripMenuItem
			// 
			this->fileSavingPrecisionToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->fileSavingPrecisionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->OptFileSavePrecDbl,
					this->OptFileSavePrecInt32, this->OptFileSavePrecInt16, this->OptFileSavePrecUInt16
			});
			this->fileSavingPrecisionToolStripMenuItem->Name = L"fileSavingPrecisionToolStripMenuItem";
			this->fileSavingPrecisionToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->fileSavingPrecisionToolStripMenuItem->Text = L"File Saving Precision";
			// 
			// OptFileSavePrecDbl
			// 
			this->OptFileSavePrecDbl->Checked = true;
			this->OptFileSavePrecDbl->CheckOnClick = true;
			this->OptFileSavePrecDbl->CheckState = System::Windows::Forms::CheckState::Checked;
			this->OptFileSavePrecDbl->Name = L"OptFileSavePrecDbl";
			this->OptFileSavePrecDbl->Size = System::Drawing::Size(112, 22);
			this->OptFileSavePrecDbl->Text = L"Double";
			this->OptFileSavePrecDbl->Click += gcnew System::EventHandler(this, &Form1::OptFileSavePrecDbl_Click);
			// 
			// OptFileSavePrecInt32
			// 
			this->OptFileSavePrecInt32->CheckOnClick = true;
			this->OptFileSavePrecInt32->Name = L"OptFileSavePrecInt32";
			this->OptFileSavePrecInt32->Size = System::Drawing::Size(112, 22);
			this->OptFileSavePrecInt32->Text = L"Int32";
			this->OptFileSavePrecInt32->Click += gcnew System::EventHandler(this, &Form1::OptFileSavePrecInt32_Click);
			// 
			// OptFileSavePrecInt16
			// 
			this->OptFileSavePrecInt16->CheckOnClick = true;
			this->OptFileSavePrecInt16->Name = L"OptFileSavePrecInt16";
			this->OptFileSavePrecInt16->Size = System::Drawing::Size(112, 22);
			this->OptFileSavePrecInt16->Text = L"Int16";
			this->OptFileSavePrecInt16->Click += gcnew System::EventHandler(this, &Form1::OptFileSavePrecInt16_Click);
			// 
			// OptFileSavePrecUInt16
			// 
			this->OptFileSavePrecUInt16->CheckOnClick = true;
			this->OptFileSavePrecUInt16->Name = L"OptFileSavePrecUInt16";
			this->OptFileSavePrecUInt16->Size = System::Drawing::Size(112, 22);
			this->OptFileSavePrecUInt16->Text = L"UInt16";
			this->OptFileSavePrecUInt16->Click += gcnew System::EventHandler(this, &Form1::OptFileSavePrecUInt16_Click);
			// 
			// veiwToolStripMenuItem
			// 
			this->veiwToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->OptViewImage,
					this->OptViewSpectrum
			});
			this->veiwToolStripMenuItem->Name = L"veiwToolStripMenuItem";
			this->veiwToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->veiwToolStripMenuItem->Text = L"View";
			// 
			// OptViewImage
			// 
			this->OptViewImage->Checked = true;
			this->OptViewImage->CheckOnClick = true;
			this->OptViewImage->CheckState = System::Windows::Forms::CheckState::Checked;
			this->OptViewImage->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->OptInvertImageView });
			this->OptViewImage->Name = L"OptViewImage";
			this->OptViewImage->Size = System::Drawing::Size(125, 22);
			this->OptViewImage->Text = L"Image";
			this->OptViewImage->Click += gcnew System::EventHandler(this, &Form1::OptViewImage_Click);
			// 
			// OptInvertImageView
			// 
			this->OptInvertImageView->CheckOnClick = true;
			this->OptInvertImageView->Name = L"OptInvertImageView";
			this->OptInvertImageView->Size = System::Drawing::Size(141, 22);
			this->OptInvertImageView->Text = L"Invert Y-Axis";
			this->OptInvertImageView->Visible = false;
			this->OptInvertImageView->Click += gcnew System::EventHandler(this, &Form1::OptInvertImageView_Click);
			// 
			// OptViewSpectrum
			// 
			this->OptViewSpectrum->CheckOnClick = true;
			this->OptViewSpectrum->Name = L"OptViewSpectrum";
			this->OptViewSpectrum->Size = System::Drawing::Size(125, 22);
			this->OptViewSpectrum->Text = L"Spectrum";
			this->OptViewSpectrum->Click += gcnew System::EventHandler(this, &Form1::OptViewSpectrum_Click);
			// 
			// ResetPlotPositions
			// 
			this->ResetPlotPositions->Name = L"ResetPlotPositions";
			this->ResetPlotPositions->Size = System::Drawing::Size(181, 22);
			this->ResetPlotPositions->Text = L"Reset Plot Positions";
			this->ResetPlotPositions->Click += gcnew System::EventHandler(this, &Form1::ResetPlotPositions_Click);
			// 
			// WCSMenu
			// 
			this->WCSMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->WCSRADecShowChck,
					this->copyToolStripMenuItem, this->WCSClearMenuBtn, this->WCSPlotSolutionPtsBtn, this->toolStripSeparator30, this->WCSRADecManual,
					this->toolStripSeparator31, this->AutoWCSMenuItem, this->AutoWCSXCorr
			});
			this->WCSMenu->Name = L"WCSMenu";
			this->WCSMenu->Size = System::Drawing::Size(44, 20);
			this->WCSMenu->Text = L"WCS";
			// 
			// WCSRADecShowChck
			// 
			this->WCSRADecShowChck->CheckOnClick = true;
			this->WCSRADecShowChck->Name = L"WCSRADecShowChck";
			this->WCSRADecShowChck->Size = System::Drawing::Size(178, 22);
			this->WCSRADecShowChck->Text = L"Show";
			this->WCSRADecShowChck->Click += gcnew System::EventHandler(this, &Form1::WCSRADecShowChck_Click);
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->WCSCopyToLoadedImgs,
					this->WCSCopyToDiskFiles
			});
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->Size = System::Drawing::Size(178, 22);
			this->copyToolStripMenuItem->Text = L"Copy";
			// 
			// WCSCopyToLoadedImgs
			// 
			this->WCSCopyToLoadedImgs->Name = L"WCSCopyToLoadedImgs";
			this->WCSCopyToLoadedImgs->Size = System::Drawing::Size(202, 22);
			this->WCSCopyToLoadedImgs->Text = L"To Other Loaded Images";
			this->WCSCopyToLoadedImgs->Click += gcnew System::EventHandler(this, &Form1::WCSCopyToLoadedImgs_Click);
			// 
			// WCSCopyToDiskFiles
			// 
			this->WCSCopyToDiskFiles->Enabled = false;
			this->WCSCopyToDiskFiles->Name = L"WCSCopyToDiskFiles";
			this->WCSCopyToDiskFiles->Size = System::Drawing::Size(202, 22);
			this->WCSCopyToDiskFiles->Text = L"To Other Disk Files";
			// 
			// WCSClearMenuBtn
			// 
			this->WCSClearMenuBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->WCSClearAllChck });
			this->WCSClearMenuBtn->Name = L"WCSClearMenuBtn";
			this->WCSClearMenuBtn->Size = System::Drawing::Size(178, 22);
			this->WCSClearMenuBtn->Text = L"Clear WCS";
			this->WCSClearMenuBtn->Click += gcnew System::EventHandler(this, &Form1::WCSClearMenuBtn_Click);
			// 
			// WCSClearAllChck
			// 
			this->WCSClearAllChck->CheckOnClick = true;
			this->WCSClearAllChck->Name = L"WCSClearAllChck";
			this->WCSClearAllChck->Size = System::Drawing::Size(171, 22);
			this->WCSClearAllChck->Text = L"All Loaded Images";
			this->WCSClearAllChck->Click += gcnew System::EventHandler(this, &Form1::WCSClearAllChck_Click);
			// 
			// WCSPlotSolutionPtsBtn
			// 
			this->WCSPlotSolutionPtsBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->WCSClearPlotSolutionPtsBtn });
			this->WCSPlotSolutionPtsBtn->Name = L"WCSPlotSolutionPtsBtn";
			this->WCSPlotSolutionPtsBtn->Size = System::Drawing::Size(178, 22);
			this->WCSPlotSolutionPtsBtn->Text = L"Plot Solution Points";
			this->WCSPlotSolutionPtsBtn->Click += gcnew System::EventHandler(this, &Form1::WCSPlotSolutionPtsBtn_Click);
			// 
			// WCSClearPlotSolutionPtsBtn
			// 
			this->WCSClearPlotSolutionPtsBtn->Name = L"WCSClearPlotSolutionPtsBtn";
			this->WCSClearPlotSolutionPtsBtn->Size = System::Drawing::Size(101, 22);
			this->WCSClearPlotSolutionPtsBtn->Text = L"Clear";
			this->WCSClearPlotSolutionPtsBtn->Click += gcnew System::EventHandler(this, &Form1::WCSClearPlotSolutionPtsBtn_Click);
			// 
			// toolStripSeparator30
			// 
			this->toolStripSeparator30->Name = L"toolStripSeparator30";
			this->toolStripSeparator30->Size = System::Drawing::Size(175, 6);
			// 
			// WCSRADecManual
			// 
			this->WCSRADecManual->Name = L"WCSRADecManual";
			this->WCSRADecManual->Size = System::Drawing::Size(178, 22);
			this->WCSRADecManual->Text = L"Manual Solution";
			this->WCSRADecManual->Click += gcnew System::EventHandler(this, &Form1::WCSRADecManual_Click);
			// 
			// toolStripSeparator31
			// 
			this->toolStripSeparator31->Name = L"toolStripSeparator31";
			this->toolStripSeparator31->Size = System::Drawing::Size(175, 6);
			// 
			// AutoWCSMenuItem
			// 
			this->AutoWCSMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(32) {
				this->WCSAutoSolveBtn,
					this->WCSAutoStopCriteriaMenu, this->toolStripSeparator38, this->WCSAutoCatalogueMenuBtn, this->toolStripMenuItem23, this->WCSAutoCatalogueTxt,
					this->WCSAutoQueryBtn, this->WCSAutoNCatPtsLabel, this->WCSAutoNCatPtsTxt, this->toolStripSeparator33, this->AutoWCSScaleMenuBtn,
					this->WCSScaleInit, this->WCSScaleInitLB, this->WCSScaleInitUB, this->toolStripMenuItem14, this->WCSRotationInit, this->WCSRotationInitLB,
					this->WCSRotationInitUB, this->toolStripSeparator34, this->toolStripMenuItem15, this->WCSAutoVertexToleranceTxt, this->toolStripSeparator37,
					this->WCSAutoParityMenuBtn, this->WCSAutoXAxisParityChck, this->WCSAutoYAxisParityChck, this->toolStripSeparator44, this->WCSAutoDisplayChck,
					this->WCSAutoConditionArraysChck, this->WCSAutoRefineChck, this->toolStripSeparator35, this->WCSRefineSolutionBtn, this->toolStripSeparator29
			});
			this->AutoWCSMenuItem->Name = L"AutoWCSMenuItem";
			this->AutoWCSMenuItem->Size = System::Drawing::Size(178, 22);
			this->AutoWCSMenuItem->Text = L"Auto WCS";
			this->AutoWCSMenuItem->DropDownOpening += gcnew System::EventHandler(this, &Form1::AutoWCSMenuItem_DropDownOpening);
			this->AutoWCSMenuItem->DropDownOpened += gcnew System::EventHandler(this, &Form1::AutoWCSMenuItem_DropDownOpened);
			// 
			// WCSAutoSolveBtn
			// 
			this->WCSAutoSolveBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->WCSAutoExternalDLLChck });
			this->WCSAutoSolveBtn->Name = L"WCSAutoSolveBtn";
			this->WCSAutoSolveBtn->Size = System::Drawing::Size(233, 22);
			this->WCSAutoSolveBtn->Text = L"Solve";
			this->WCSAutoSolveBtn->Click += gcnew System::EventHandler(this, &Form1::WCSAutoSolveBtn_Click);
			this->WCSAutoSolveBtn->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSAutoSolveBtn_MouseEnter);
			this->WCSAutoSolveBtn->MouseLeave += gcnew System::EventHandler(this, &Form1::WCSAutoSolveBtn_MouseLeave);
			// 
			// WCSAutoExternalDLLChck
			// 
			this->WCSAutoExternalDLLChck->CheckOnClick = true;
			this->WCSAutoExternalDLLChck->Name = L"WCSAutoExternalDLLChck";
			this->WCSAutoExternalDLLChck->Size = System::Drawing::Size(161, 22);
			this->WCSAutoExternalDLLChck->Text = L"Use External DLL";
			this->WCSAutoExternalDLLChck->Click += gcnew System::EventHandler(this, &Form1::WCSAutoExternalDLLChck_Click);
			// 
			// WCSAutoStopCriteriaMenu
			// 
			this->WCSAutoStopCriteriaMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->WCSAutoStopNMatchesBtn,
					this->WCSAutoStopNMatchesText, this->toolStripMenuItem20, this->WCSAutoStopPercMatchesText
			});
			this->WCSAutoStopCriteriaMenu->Name = L"WCSAutoStopCriteriaMenu";
			this->WCSAutoStopCriteriaMenu->Size = System::Drawing::Size(233, 22);
			this->WCSAutoStopCriteriaMenu->Text = L"Stopping Criteria";
			// 
			// WCSAutoStopNMatchesBtn
			// 
			this->WCSAutoStopNMatchesBtn->Enabled = false;
			this->WCSAutoStopNMatchesBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->WCSAutoStopNMatchesBtn->Name = L"WCSAutoStopNMatchesBtn";
			this->WCSAutoStopNMatchesBtn->Size = System::Drawing::Size(227, 22);
			this->WCSAutoStopNMatchesBtn->Text = L"Number of Matching Points";
			// 
			// WCSAutoStopNMatchesText
			// 
			this->WCSAutoStopNMatchesText->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoStopNMatchesText->Name = L"WCSAutoStopNMatchesText";
			this->WCSAutoStopNMatchesText->Size = System::Drawing::Size(100, 23);
			this->WCSAutoStopNMatchesText->ToolTipText = L"Stop and solve solution when N matches are found between image and catalogue coor"
				L"dinates. Greater than or equal to 4. Suggest 6. Solution likely requires confirm"
				L"ation at 4.";
			this->WCSAutoStopNMatchesText->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->WCSAutoStopNMatchesText->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// toolStripMenuItem20
			// 
			this->toolStripMenuItem20->Enabled = false;
			this->toolStripMenuItem20->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem20->Name = L"toolStripMenuItem20";
			this->toolStripMenuItem20->Size = System::Drawing::Size(227, 22);
			this->toolStripMenuItem20->Text = L"Percent of Point Matches";
			// 
			// WCSAutoStopPercMatchesText
			// 
			this->WCSAutoStopPercMatchesText->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoStopPercMatchesText->Name = L"WCSAutoStopPercMatchesText";
			this->WCSAutoStopPercMatchesText->Size = System::Drawing::Size(100, 23);
			this->WCSAutoStopPercMatchesText->ToolTipText = L"Stop and solve solution when Percentage matches are found between image and catal"
				L"ogue coordinates. Suggest 25.";
			this->WCSAutoStopPercMatchesText->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->WCSAutoStopPercMatchesText->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// toolStripSeparator38
			// 
			this->toolStripSeparator38->Name = L"toolStripSeparator38";
			this->toolStripSeparator38->Size = System::Drawing::Size(230, 6);
			// 
			// WCSAutoCatalogueMenuBtn
			// 
			this->WCSAutoCatalogueMenuBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->toolStripMenuItem17,
					this->WCSAutoCatalogueExtensionTxt, this->toolStripSeparator43, this->cVAL1RAToolStripMenuItem, this->WCSAutoCatalogueCVAL1,
					this->toolStripSeparator42, this->cVAL2DecToolStripMenuItem, this->WCSAutoCatalogueCVAL2, this->toolStripSeparator41, this->toolStripMenuItem16,
					this->WCSAutoCatalogueMag
			});
			this->WCSAutoCatalogueMenuBtn->Name = L"WCSAutoCatalogueMenuBtn";
			this->WCSAutoCatalogueMenuBtn->Size = System::Drawing::Size(233, 22);
			this->WCSAutoCatalogueMenuBtn->Text = L"Catalogue:";
			// 
			// toolStripMenuItem17
			// 
			this->toolStripMenuItem17->Enabled = false;
			this->toolStripMenuItem17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem17->Name = L"toolStripMenuItem17";
			this->toolStripMenuItem17->Size = System::Drawing::Size(181, 22);
			this->toolStripMenuItem17->Text = L"Extension Name";
			// 
			// WCSAutoCatalogueExtensionTxt
			// 
			this->WCSAutoCatalogueExtensionTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoCatalogueExtensionTxt->Name = L"WCSAutoCatalogueExtensionTxt";
			this->WCSAutoCatalogueExtensionTxt->Size = System::Drawing::Size(100, 23);
			this->WCSAutoCatalogueExtensionTxt->Click += gcnew System::EventHandler(this, &Form1::WCSAutoCatalogueExtensionTxt_Click);
			// 
			// toolStripSeparator43
			// 
			this->toolStripSeparator43->Name = L"toolStripSeparator43";
			this->toolStripSeparator43->Size = System::Drawing::Size(178, 6);
			// 
			// cVAL1RAToolStripMenuItem
			// 
			this->cVAL1RAToolStripMenuItem->Enabled = false;
			this->cVAL1RAToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->cVAL1RAToolStripMenuItem->Name = L"cVAL1RAToolStripMenuItem";
			this->cVAL1RAToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->cVAL1RAToolStripMenuItem->Text = L"CVAL1 (RA)";
			// 
			// WCSAutoCatalogueCVAL1
			// 
			this->WCSAutoCatalogueCVAL1->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoCatalogueCVAL1->Name = L"WCSAutoCatalogueCVAL1";
			this->WCSAutoCatalogueCVAL1->ReadOnly = true;
			this->WCSAutoCatalogueCVAL1->Size = System::Drawing::Size(121, 23);
			this->WCSAutoCatalogueCVAL1->Click += gcnew System::EventHandler(this, &Form1::WCSAutoCatalogueCVAL1_Click);
			// 
			// toolStripSeparator42
			// 
			this->toolStripSeparator42->Name = L"toolStripSeparator42";
			this->toolStripSeparator42->Size = System::Drawing::Size(178, 6);
			// 
			// cVAL2DecToolStripMenuItem
			// 
			this->cVAL2DecToolStripMenuItem->Enabled = false;
			this->cVAL2DecToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->cVAL2DecToolStripMenuItem->Name = L"cVAL2DecToolStripMenuItem";
			this->cVAL2DecToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->cVAL2DecToolStripMenuItem->Text = L"CVAL2 (Dec)";
			// 
			// WCSAutoCatalogueCVAL2
			// 
			this->WCSAutoCatalogueCVAL2->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoCatalogueCVAL2->Name = L"WCSAutoCatalogueCVAL2";
			this->WCSAutoCatalogueCVAL2->ReadOnly = true;
			this->WCSAutoCatalogueCVAL2->Size = System::Drawing::Size(121, 23);
			this->WCSAutoCatalogueCVAL2->Click += gcnew System::EventHandler(this, &Form1::WCSAutoCatalogueCVAL2_Click);
			// 
			// toolStripSeparator41
			// 
			this->toolStripSeparator41->Name = L"toolStripSeparator41";
			this->toolStripSeparator41->Size = System::Drawing::Size(178, 6);
			// 
			// toolStripMenuItem16
			// 
			this->toolStripMenuItem16->Enabled = false;
			this->toolStripMenuItem16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem16->Name = L"toolStripMenuItem16";
			this->toolStripMenuItem16->Size = System::Drawing::Size(181, 22);
			this->toolStripMenuItem16->Text = L"Magnitude";
			// 
			// WCSAutoCatalogueMag
			// 
			this->WCSAutoCatalogueMag->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoCatalogueMag->Name = L"WCSAutoCatalogueMag";
			this->WCSAutoCatalogueMag->ReadOnly = true;
			this->WCSAutoCatalogueMag->Size = System::Drawing::Size(100, 23);
			this->WCSAutoCatalogueMag->Click += gcnew System::EventHandler(this, &Form1::WCSAutoCatalogueMag_Click);
			// 
			// toolStripMenuItem23
			// 
			this->toolStripMenuItem23->Enabled = false;
			this->toolStripMenuItem23->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem23->Name = L"toolStripMenuItem23";
			this->toolStripMenuItem23->Size = System::Drawing::Size(233, 22);
			this->toolStripMenuItem23->Text = L"File:";
			// 
			// WCSAutoCatalogueTxt
			// 
			this->WCSAutoCatalogueTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoCatalogueTxt->Name = L"WCSAutoCatalogueTxt";
			this->WCSAutoCatalogueTxt->ReadOnly = true;
			this->WCSAutoCatalogueTxt->Size = System::Drawing::Size(100, 23);
			this->WCSAutoCatalogueTxt->Click += gcnew System::EventHandler(this, &Form1::WCSAutoCatalogueTxt_Click);
			this->WCSAutoCatalogueTxt->MouseHover += gcnew System::EventHandler(this, &Form1::WCSAutoCatalogueTxt_MouseHover);
			// 
			// WCSAutoQueryBtn
			// 
			this->WCSAutoQueryBtn->DoubleClickEnabled = true;
			this->WCSAutoQueryBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(14) {
				this->AstroQueryCatalogueNameMenu,
					this->AstroQueryCatalogueNameDrop, this->toolStripSeparator46, this->toolStripMenuItem24, this->WCSAutoQueryCVAL1, this->toolStripMenuItem25,
					this->WCSAutoQueryCVAL2, this->toolStripMenuItem26, this->WCSAutoResolveRadiusTxt, this->WCSQuerySquareRegionChck, this->toolStripSeparator45,
					this->WCSQuerySaveFileChck, this->toolStripSeparator47, this->WCSQuerySolveAfter
			});
			this->WCSAutoQueryBtn->Name = L"WCSAutoQueryBtn";
			this->WCSAutoQueryBtn->Size = System::Drawing::Size(233, 22);
			this->WCSAutoQueryBtn->Text = L"AstroQuery:";
			this->WCSAutoQueryBtn->DropDownOpening += gcnew System::EventHandler(this, &Form1::WCSAutoQueryBtn_DropDownOpening);
			this->WCSAutoQueryBtn->DoubleClick += gcnew System::EventHandler(this, &Form1::WCSAutoQueryBtn_DoubleClick);
			// 
			// AstroQueryCatalogueNameMenu
			// 
			this->AstroQueryCatalogueNameMenu->Enabled = false;
			this->AstroQueryCatalogueNameMenu->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->AstroQueryCatalogueNameMenu->Name = L"AstroQueryCatalogueNameMenu";
			this->AstroQueryCatalogueNameMenu->Size = System::Drawing::Size(194, 22);
			this->AstroQueryCatalogueNameMenu->Text = L"Catalogue Name";
			// 
			// AstroQueryCatalogueNameDrop
			// 
			this->AstroQueryCatalogueNameDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->AstroQueryCatalogueNameDrop->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Gaia (DR2)" });
			this->AstroQueryCatalogueNameDrop->Name = L"AstroQueryCatalogueNameDrop";
			this->AstroQueryCatalogueNameDrop->Size = System::Drawing::Size(121, 23);
			this->AstroQueryCatalogueNameDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::AstroQueryCatalogueNameDrop_SelectedIndexChanged);
			// 
			// toolStripSeparator46
			// 
			this->toolStripSeparator46->Name = L"toolStripSeparator46";
			this->toolStripSeparator46->Size = System::Drawing::Size(191, 6);
			// 
			// toolStripMenuItem24
			// 
			this->toolStripMenuItem24->Enabled = false;
			this->toolStripMenuItem24->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem24->Name = L"toolStripMenuItem24";
			this->toolStripMenuItem24->Size = System::Drawing::Size(194, 22);
			this->toolStripMenuItem24->Text = L"CVAL1 (RA)";
			// 
			// WCSAutoQueryCVAL1
			// 
			this->WCSAutoQueryCVAL1->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoQueryCVAL1->Name = L"WCSAutoQueryCVAL1";
			this->WCSAutoQueryCVAL1->ReadOnly = true;
			this->WCSAutoQueryCVAL1->Size = System::Drawing::Size(121, 23);
			this->WCSAutoQueryCVAL1->Click += gcnew System::EventHandler(this, &Form1::WCSAutoQueryCVAL1_Click);
			// 
			// toolStripMenuItem25
			// 
			this->toolStripMenuItem25->Enabled = false;
			this->toolStripMenuItem25->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem25->Name = L"toolStripMenuItem25";
			this->toolStripMenuItem25->Size = System::Drawing::Size(194, 22);
			this->toolStripMenuItem25->Text = L"CVAL2 (Dec)";
			// 
			// WCSAutoQueryCVAL2
			// 
			this->WCSAutoQueryCVAL2->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoQueryCVAL2->Name = L"WCSAutoQueryCVAL2";
			this->WCSAutoQueryCVAL2->ReadOnly = true;
			this->WCSAutoQueryCVAL2->Size = System::Drawing::Size(121, 23);
			this->WCSAutoQueryCVAL2->Click += gcnew System::EventHandler(this, &Form1::WCSAutoQueryCVAL1_Click);
			// 
			// toolStripMenuItem26
			// 
			this->toolStripMenuItem26->Enabled = false;
			this->toolStripMenuItem26->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem26->Name = L"toolStripMenuItem26";
			this->toolStripMenuItem26->Size = System::Drawing::Size(194, 22);
			this->toolStripMenuItem26->Text = L"Radius (arc minutes)";
			// 
			// WCSAutoResolveRadiusTxt
			// 
			this->WCSAutoResolveRadiusTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoResolveRadiusTxt->Name = L"WCSAutoResolveRadiusTxt";
			this->WCSAutoResolveRadiusTxt->Size = System::Drawing::Size(100, 23);
			this->WCSAutoResolveRadiusTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->WCSAutoResolveRadiusTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// WCSQuerySquareRegionChck
			// 
			this->WCSQuerySquareRegionChck->Checked = true;
			this->WCSQuerySquareRegionChck->CheckState = System::Windows::Forms::CheckState::Checked;
			this->WCSQuerySquareRegionChck->Name = L"WCSQuerySquareRegionChck";
			this->WCSQuerySquareRegionChck->Size = System::Drawing::Size(194, 22);
			this->WCSQuerySquareRegionChck->Text = L"Square Region";
			this->WCSQuerySquareRegionChck->Click += gcnew System::EventHandler(this, &Form1::WCSQuerySquareRegionChck_Click);
			// 
			// toolStripSeparator45
			// 
			this->toolStripSeparator45->Name = L"toolStripSeparator45";
			this->toolStripSeparator45->Size = System::Drawing::Size(191, 6);
			// 
			// WCSQuerySaveFileChck
			// 
			this->WCSQuerySaveFileChck->CheckOnClick = true;
			this->WCSQuerySaveFileChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->WCSQuerySaveFileChooseDirBtn });
			this->WCSQuerySaveFileChck->Name = L"WCSQuerySaveFileChck";
			this->WCSQuerySaveFileChck->Size = System::Drawing::Size(194, 22);
			this->WCSQuerySaveFileChck->Text = L"Save file in image Dir\?";
			this->WCSQuerySaveFileChck->Click += gcnew System::EventHandler(this, &Form1::WCSQuerySaveFileChck_Click);
			// 
			// WCSQuerySaveFileChooseDirBtn
			// 
			this->WCSQuerySaveFileChooseDirBtn->CheckOnClick = true;
			this->WCSQuerySaveFileChooseDirBtn->Name = L"WCSQuerySaveFileChooseDirBtn";
			this->WCSQuerySaveFileChooseDirBtn->Size = System::Drawing::Size(196, 22);
			this->WCSQuerySaveFileChooseDirBtn->Text = L"Choose other Directory";
			this->WCSQuerySaveFileChooseDirBtn->Click += gcnew System::EventHandler(this, &Form1::WCSQuerySaveFileChooseDirBtn_Click);
			// 
			// toolStripSeparator47
			// 
			this->toolStripSeparator47->Name = L"toolStripSeparator47";
			this->toolStripSeparator47->Size = System::Drawing::Size(191, 6);
			// 
			// WCSQuerySolveAfter
			// 
			this->WCSQuerySolveAfter->CheckOnClick = true;
			this->WCSQuerySolveAfter->Name = L"WCSQuerySolveAfter";
			this->WCSQuerySolveAfter->Size = System::Drawing::Size(194, 22);
			this->WCSQuerySolveAfter->Text = L"Solve WCS After Query";
			this->WCSQuerySolveAfter->Click += gcnew System::EventHandler(this, &Form1::WCSQuerySolveAfter_Click);
			// 
			// WCSAutoNCatPtsLabel
			// 
			this->WCSAutoNCatPtsLabel->Enabled = false;
			this->WCSAutoNCatPtsLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->WCSAutoNCatPtsLabel->Name = L"WCSAutoNCatPtsLabel";
			this->WCSAutoNCatPtsLabel->Size = System::Drawing::Size(233, 22);
			this->WCSAutoNCatPtsLabel->Text = L"Number of Catalogue Points:";
			this->WCSAutoNCatPtsLabel->ToolTipText = L"(Brightest)";
			// 
			// WCSAutoNCatPtsTxt
			// 
			this->WCSAutoNCatPtsTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoNCatPtsTxt->Name = L"WCSAutoNCatPtsTxt";
			this->WCSAutoNCatPtsTxt->Size = System::Drawing::Size(100, 23);
			this->WCSAutoNCatPtsTxt->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSAutoNCatPtsTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSAutoNCatPtsTxt->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// toolStripSeparator33
			// 
			this->toolStripSeparator33->Name = L"toolStripSeparator33";
			this->toolStripSeparator33->Size = System::Drawing::Size(230, 6);
			// 
			// AutoWCSScaleMenuBtn
			// 
			this->AutoWCSScaleMenuBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->AutoWCSScaleSaveBtn });
			this->AutoWCSScaleMenuBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->AutoWCSScaleMenuBtn->Name = L"AutoWCSScaleMenuBtn";
			this->AutoWCSScaleMenuBtn->Size = System::Drawing::Size(233, 22);
			this->AutoWCSScaleMenuBtn->Text = L"Scale:";
			this->AutoWCSScaleMenuBtn->ToolTipText = L"arcsec/pixel";
			this->AutoWCSScaleMenuBtn->DropDownOpening += gcnew System::EventHandler(this, &Form1::AutoWCSScaleMenuBtn_DropDownOpening);
			this->AutoWCSScaleMenuBtn->Click += gcnew System::EventHandler(this, &Form1::AutoWCSScaleMenuBtn_Click);
			// 
			// AutoWCSScaleSaveBtn
			// 
			this->AutoWCSScaleSaveBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->WSCSaveScaleTxtBox });
			this->AutoWCSScaleSaveBtn->Name = L"AutoWCSScaleSaveBtn";
			this->AutoWCSScaleSaveBtn->Size = System::Drawing::Size(98, 22);
			this->AutoWCSScaleSaveBtn->Text = L"Save";
			this->AutoWCSScaleSaveBtn->Click += gcnew System::EventHandler(this, &Form1::AutoWCSScaleSaveBtn_Click);
			// 
			// WSCSaveScaleTxtBox
			// 
			this->WSCSaveScaleTxtBox->BackColor = System::Drawing::Color::Gainsboro;
			this->WSCSaveScaleTxtBox->MaxLength = 15;
			this->WSCSaveScaleTxtBox->Name = L"WSCSaveScaleTxtBox";
			this->WSCSaveScaleTxtBox->Size = System::Drawing::Size(100, 23);
			this->WSCSaveScaleTxtBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::WSCSaveScaleTxtBox_KeyDown);
			// 
			// WCSScaleInit
			// 
			this->WCSScaleInit->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSScaleInit->Name = L"WCSScaleInit";
			this->WCSScaleInit->Size = System::Drawing::Size(100, 23);
			this->WCSScaleInit->ToolTipText = L"Initial Scale (arcsec/pixel)";
			this->WCSScaleInit->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSScaleInit->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSScaleInit->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// WCSScaleInitLB
			// 
			this->WCSScaleInitLB->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSScaleInitLB->Name = L"WCSScaleInitLB";
			this->WCSScaleInitLB->Size = System::Drawing::Size(100, 23);
			this->WCSScaleInitLB->ToolTipText = L"Scale Lower Bound (arcsec/pixel)";
			this->WCSScaleInitLB->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSScaleInitLB->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSScaleInitLB->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// WCSScaleInitUB
			// 
			this->WCSScaleInitUB->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSScaleInitUB->Name = L"WCSScaleInitUB";
			this->WCSScaleInitUB->Size = System::Drawing::Size(100, 23);
			this->WCSScaleInitUB->ToolTipText = L"Scale Upper Bound (arcsec/pixel)";
			this->WCSScaleInitUB->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSScaleInitUB->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSScaleInitUB->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// toolStripMenuItem14
			// 
			this->toolStripMenuItem14->Enabled = false;
			this->toolStripMenuItem14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem14->Name = L"toolStripMenuItem14";
			this->toolStripMenuItem14->Size = System::Drawing::Size(233, 22);
			this->toolStripMenuItem14->Text = L"Rotation:";
			this->toolStripMenuItem14->ToolTipText = L"degrees";
			// 
			// WCSRotationInit
			// 
			this->WCSRotationInit->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSRotationInit->Name = L"WCSRotationInit";
			this->WCSRotationInit->Size = System::Drawing::Size(100, 23);
			this->WCSRotationInit->ToolTipText = L"Initial Rotation (degrees)";
			this->WCSRotationInit->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSRotationInit->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSRotationInit->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// WCSRotationInitLB
			// 
			this->WCSRotationInitLB->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSRotationInitLB->Name = L"WCSRotationInitLB";
			this->WCSRotationInitLB->Size = System::Drawing::Size(100, 23);
			this->WCSRotationInitLB->ToolTipText = L"Rotation Lower Bound (degrees)";
			this->WCSRotationInitLB->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSRotationInitLB->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSRotationInitLB->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// WCSRotationInitUB
			// 
			this->WCSRotationInitUB->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSRotationInitUB->Name = L"WCSRotationInitUB";
			this->WCSRotationInitUB->Size = System::Drawing::Size(100, 23);
			this->WCSRotationInitUB->ToolTipText = L"Rotation Upper Bound (degrees)";
			this->WCSRotationInitUB->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSRotationInitUB->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSRotationInitUB->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// toolStripSeparator34
			// 
			this->toolStripSeparator34->Name = L"toolStripSeparator34";
			this->toolStripSeparator34->Size = System::Drawing::Size(230, 6);
			// 
			// toolStripMenuItem15
			// 
			this->toolStripMenuItem15->Enabled = false;
			this->toolStripMenuItem15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem15->Name = L"toolStripMenuItem15";
			this->toolStripMenuItem15->Size = System::Drawing::Size(233, 22);
			this->toolStripMenuItem15->Text = L"Vertex Angle Tolerance:";
			// 
			// WCSAutoVertexToleranceTxt
			// 
			this->WCSAutoVertexToleranceTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoVertexToleranceTxt->Name = L"WCSAutoVertexToleranceTxt";
			this->WCSAutoVertexToleranceTxt->Size = System::Drawing::Size(100, 23);
			this->WCSAutoVertexToleranceTxt->ToolTipText = L"The tolerance of the vertex angles when comparing triangles, in degrees. Suggest "
				L"0.25.";
			this->WCSAutoVertexToleranceTxt->Enter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSAutoVertexToleranceTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::WCSScaleInit_Enter);
			this->WCSAutoVertexToleranceTxt->TextChanged += gcnew System::EventHandler(this, &Form1::WCSScaleInit_TextChanged);
			// 
			// toolStripSeparator37
			// 
			this->toolStripSeparator37->Name = L"toolStripSeparator37";
			this->toolStripSeparator37->Size = System::Drawing::Size(230, 6);
			// 
			// WCSAutoParityMenuBtn
			// 
			this->WCSAutoParityMenuBtn->Enabled = false;
			this->WCSAutoParityMenuBtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->WCSAutoParityMenuBtn->Name = L"WCSAutoParityMenuBtn";
			this->WCSAutoParityMenuBtn->Size = System::Drawing::Size(233, 22);
			this->WCSAutoParityMenuBtn->Text = L"Image Parity";
			this->WCSAutoParityMenuBtn->Visible = false;
			// 
			// WCSAutoXAxisParityChck
			// 
			this->WCSAutoXAxisParityChck->Enabled = false;
			this->WCSAutoXAxisParityChck->Name = L"WCSAutoXAxisParityChck";
			this->WCSAutoXAxisParityChck->Size = System::Drawing::Size(233, 22);
			this->WCSAutoXAxisParityChck->Text = L"X-Axis Inverted";
			this->WCSAutoXAxisParityChck->ToolTipText = L"Unchecked = No; Checked = Yes; Dot = Unsure";
			this->WCSAutoXAxisParityChck->Visible = false;
			this->WCSAutoXAxisParityChck->Click += gcnew System::EventHandler(this, &Form1::WCSAutoXAxisParityChck_Click);
			// 
			// WCSAutoYAxisParityChck
			// 
			this->WCSAutoYAxisParityChck->Enabled = false;
			this->WCSAutoYAxisParityChck->Name = L"WCSAutoYAxisParityChck";
			this->WCSAutoYAxisParityChck->Size = System::Drawing::Size(233, 22);
			this->WCSAutoYAxisParityChck->Text = L"Y-Axis Inverted";
			this->WCSAutoYAxisParityChck->ToolTipText = L"Unchecked = No; Checked = Yes; Dot = Unsure";
			this->WCSAutoYAxisParityChck->Visible = false;
			this->WCSAutoYAxisParityChck->Click += gcnew System::EventHandler(this, &Form1::WCSAutoYAxisParityChck_Click);
			// 
			// toolStripSeparator44
			// 
			this->toolStripSeparator44->Name = L"toolStripSeparator44";
			this->toolStripSeparator44->Size = System::Drawing::Size(230, 6);
			// 
			// WCSAutoDisplayChck
			// 
			this->WCSAutoDisplayChck->CheckOnClick = true;
			this->WCSAutoDisplayChck->Name = L"WCSAutoDisplayChck";
			this->WCSAutoDisplayChck->Size = System::Drawing::Size(233, 22);
			this->WCSAutoDisplayChck->Text = L"Display (serial processor)";
			this->WCSAutoDisplayChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::toolStripMenuItem15_CheckedChanged);
			// 
			// WCSAutoConditionArraysChck
			// 
			this->WCSAutoConditionArraysChck->CheckOnClick = true;
			this->WCSAutoConditionArraysChck->Name = L"WCSAutoConditionArraysChck";
			this->WCSAutoConditionArraysChck->Size = System::Drawing::Size(233, 22);
			this->WCSAutoConditionArraysChck->Text = L"Condition Triangle Arrays";
			this->WCSAutoConditionArraysChck->Click += gcnew System::EventHandler(this, &Form1::WCSAutoConditionArraysChck_Click);
			// 
			// WCSAutoRefineChck
			// 
			this->WCSAutoRefineChck->CheckOnClick = true;
			this->WCSAutoRefineChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem19,
					this->WCSAutoRefineNPtsTxt
			});
			this->WCSAutoRefineChck->Name = L"WCSAutoRefineChck";
			this->WCSAutoRefineChck->Size = System::Drawing::Size(233, 22);
			this->WCSAutoRefineChck->Text = L"Auto Refine";
			this->WCSAutoRefineChck->CheckedChanged += gcnew System::EventHandler(this, &Form1::WCSAutoRefineChck_CheckedChanged);
			// 
			// toolStripMenuItem19
			// 
			this->toolStripMenuItem19->Name = L"toolStripMenuItem19";
			this->toolStripMenuItem19->Size = System::Drawing::Size(207, 22);
			this->toolStripMenuItem19->Text = L"Number of Source Points";
			// 
			// WCSAutoRefineNPtsTxt
			// 
			this->WCSAutoRefineNPtsTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSAutoRefineNPtsTxt->Name = L"WCSAutoRefineNPtsTxt";
			this->WCSAutoRefineNPtsTxt->Size = System::Drawing::Size(100, 23);
			this->WCSAutoRefineNPtsTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->WCSAutoRefineNPtsTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// toolStripSeparator35
			// 
			this->toolStripSeparator35->Name = L"toolStripSeparator35";
			this->toolStripSeparator35->Size = System::Drawing::Size(230, 6);
			// 
			// WCSRefineSolutionBtn
			// 
			this->WCSRefineSolutionBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->WCSLoadSimbadList,
					this->WCSListExciseToROI, this->WCSClarifyListSources, this->WCSSolveList
			});
			this->WCSRefineSolutionBtn->Name = L"WCSRefineSolutionBtn";
			this->WCSRefineSolutionBtn->Size = System::Drawing::Size(233, 22);
			this->WCSRefineSolutionBtn->Text = L"Refine Solution";
			this->WCSRefineSolutionBtn->DropDownOpened += gcnew System::EventHandler(this, &Form1::WCSRefineSolutionBtn_DropDownOpened);
			// 
			// WCSLoadSimbadList
			// 
			this->WCSLoadSimbadList->DoubleClickEnabled = true;
			this->WCSLoadSimbadList->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem18,
					this->WCSLoadListNPtsTxt
			});
			this->WCSLoadSimbadList->Name = L"WCSLoadSimbadList";
			this->WCSLoadSimbadList->Size = System::Drawing::Size(188, 22);
			this->WCSLoadSimbadList->Text = L"Load Catalogue";
			this->WCSLoadSimbadList->DoubleClick += gcnew System::EventHandler(this, &Form1::WCSLoadSimbadAscii_Click);
			// 
			// toolStripMenuItem18
			// 
			this->toolStripMenuItem18->Enabled = false;
			this->toolStripMenuItem18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem18->Name = L"toolStripMenuItem18";
			this->toolStripMenuItem18->Size = System::Drawing::Size(220, 22);
			this->toolStripMenuItem18->Text = L"Number of Bright Sources";
			this->toolStripMenuItem18->ToolTipText = L"0 for all sources";
			// 
			// WCSLoadListNPtsTxt
			// 
			this->WCSLoadListNPtsTxt->BackColor = System::Drawing::Color::Gainsboro;
			this->WCSLoadListNPtsTxt->Name = L"WCSLoadListNPtsTxt";
			this->WCSLoadListNPtsTxt->Size = System::Drawing::Size(100, 23);
			this->WCSLoadListNPtsTxt->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->WCSLoadListNPtsTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// WCSListExciseToROI
			// 
			this->WCSListExciseToROI->Name = L"WCSListExciseToROI";
			this->WCSListExciseToROI->Size = System::Drawing::Size(188, 22);
			this->WCSListExciseToROI->Text = L"Excise List to ROI";
			this->WCSListExciseToROI->Visible = false;
			this->WCSListExciseToROI->Click += gcnew System::EventHandler(this, &Form1::WCSListExciseToROI_Click);
			// 
			// WCSClarifyListSources
			// 
			this->WCSClarifyListSources->Name = L"WCSClarifyListSources";
			this->WCSClarifyListSources->Size = System::Drawing::Size(188, 22);
			this->WCSClarifyListSources->Text = L"Clarify Sources to PSE";
			this->WCSClarifyListSources->Click += gcnew System::EventHandler(this, &Form1::WCSClarifyListSources_Click);
			// 
			// WCSSolveList
			// 
			this->WCSSolveList->Name = L"WCSSolveList";
			this->WCSSolveList->Size = System::Drawing::Size(188, 22);
			this->WCSSolveList->Text = L"Refine";
			this->WCSSolveList->Click += gcnew System::EventHandler(this, &Form1::WCSSolveList_Click);
			// 
			// toolStripSeparator29
			// 
			this->toolStripSeparator29->Name = L"toolStripSeparator29";
			this->toolStripSeparator29->Size = System::Drawing::Size(230, 6);
			// 
			// AutoWCSXCorr
			// 
			this->AutoWCSXCorr->Name = L"AutoWCSXCorr";
			this->AutoWCSXCorr->Size = System::Drawing::Size(178, 22);
			this->AutoWCSXCorr->Text = L"Auto WCS XCorr";
			this->AutoWCSXCorr->Visible = false;
			this->AutoWCSXCorr->Click += gcnew System::EventHandler(this, &Form1::AutoWCSXCorr_Click);
			// 
			// UVITMenu
			// 
			this->UVITMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(15) {
				this->UVIT_EMGSEMenu,
					this->ExtractL1gzsMenuItem, this->DigestL1FITSImageMenuItem, this->CreateFlatFieldListMenuItem, this->ApplyUVFPNMenu, this->UVIT_ApplyCPUCorrectionMenu,
					this->ConvertListToImgMenu, this->PlotCountsPerFrameMenuItem, this->ParcelListAsFramesMenuItem, this->CreateDriftListMenuItem,
					this->ApplyDriftListMentuItem, this->ShiftAndRotateMenuItem, this->DeSaturateROICountsMenuItem, this->ExtractROICentroidListMenuItem,
					this->UVFinalizeScienceBtn
			});
			this->UVITMenu->ForeColor = System::Drawing::Color::Purple;
			this->UVITMenu->Name = L"UVITMenu";
			this->UVITMenu->Size = System::Drawing::Size(43, 20);
			this->UVITMenu->Text = L"UVIT";
			this->UVITMenu->DropDownOpened += gcnew System::EventHandler(this, &Form1::UVITMenu_DropDownOpened);
			this->UVITMenu->Click += gcnew System::EventHandler(this, &Form1::UVITMenu_Click);
			this->UVITMenu->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::UVITMenu_MouseDown);
			// 
			// UVIT_EMGSEMenu
			// 
			this->UVIT_EMGSEMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->EMGSE_UnpackImg });
			this->UVIT_EMGSEMenu->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UVIT_EMGSEMenu.Image")));
			this->UVIT_EMGSEMenu->Name = L"UVIT_EMGSEMenu";
			this->UVIT_EMGSEMenu->Size = System::Drawing::Size(274, 22);
			this->UVIT_EMGSEMenu->Text = L"Level0 && GSE Data";
			// 
			// EMGSE_UnpackImg
			// 
			this->EMGSE_UnpackImg->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EMGSE_UnpackImg.Image")));
			this->EMGSE_UnpackImg->Name = L"EMGSE_UnpackImg";
			this->EMGSE_UnpackImg->Size = System::Drawing::Size(148, 22);
			this->EMGSE_UnpackImg->Text = L"Unpack File(s)";
			this->EMGSE_UnpackImg->Click += gcnew System::EventHandler(this, &Form1::EMGSE_UnpackImg_Click);
			// 
			// ExtractL1gzsMenuItem
			// 
			this->ExtractL1gzsMenuItem->DoubleClickEnabled = true;
			this->ExtractL1gzsMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->L1AutoRunChck,
					this->L1AutoProceedVISBackGround, this->L1AutoProceedVISTracking, this->L1AutoApplyVISDrift
			});
			this->ExtractL1gzsMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ExtractL1gzsMenuItem.Image")));
			this->ExtractL1gzsMenuItem->Name = L"ExtractL1gzsMenuItem";
			this->ExtractL1gzsMenuItem->Size = System::Drawing::Size(274, 22);
			this->ExtractL1gzsMenuItem->Text = L"Extract L1 gz or zip Archives";
			this->ExtractL1gzsMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::ExtractL1gzsMenuItem_Click);
			// 
			// L1AutoRunChck
			// 
			this->L1AutoRunChck->CheckOnClick = true;
			this->L1AutoRunChck->Name = L"L1AutoRunChck";
			this->L1AutoRunChck->Size = System::Drawing::Size(258, 22);
			this->L1AutoRunChck->Text = L"Auto Run to VIS Background";
			this->L1AutoRunChck->Click += gcnew System::EventHandler(this, &Form1::autoRunToolStripMenuItem_Click);
			// 
			// L1AutoProceedVISBackGround
			// 
			this->L1AutoProceedVISBackGround->CheckOnClick = true;
			this->L1AutoProceedVISBackGround->Name = L"L1AutoProceedVISBackGround";
			this->L1AutoProceedVISBackGround->Size = System::Drawing::Size(258, 22);
			this->L1AutoProceedVISBackGround->Text = L"Auto Proceed with VIS Background";
			this->L1AutoProceedVISBackGround->Click += gcnew System::EventHandler(this, &Form1::L1AutoProceedVISBackGround_Click);
			// 
			// L1AutoProceedVISTracking
			// 
			this->L1AutoProceedVISTracking->CheckOnClick = true;
			this->L1AutoProceedVISTracking->Name = L"L1AutoProceedVISTracking";
			this->L1AutoProceedVISTracking->Size = System::Drawing::Size(258, 22);
			this->L1AutoProceedVISTracking->Text = L"Auto Proceed with VIS Tracking";
			this->L1AutoProceedVISTracking->Click += gcnew System::EventHandler(this, &Form1::L1AutoProceedVISTracking_Click);
			// 
			// L1AutoApplyVISDrift
			// 
			this->L1AutoApplyVISDrift->CheckOnClick = true;
			this->L1AutoApplyVISDrift->Name = L"L1AutoApplyVISDrift";
			this->L1AutoApplyVISDrift->Size = System::Drawing::Size(258, 22);
			this->L1AutoApplyVISDrift->Text = L"Auto Apply VIS Drift";
			this->L1AutoApplyVISDrift->Click += gcnew System::EventHandler(this, &Form1::L1AutoApplyVISDrift_Click);
			// 
			// DigestL1FITSImageMenuItem
			// 
			this->DigestL1FITSImageMenuItem->DoubleClickEnabled = true;
			this->DigestL1FITSImageMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(15) {
				this->L1DigestApplyFPNChck,
					this->L1DigestApplyDISTChck, this->L1DiscardDuplicateChck, this->L1TransformNUVtoFUVChck, this->L1DigestPCParityChck, this->toolStripSeparator36,
					this->L1SkipINTMode, this->L1DegradientINTMode, this->L1CleanINTMode, this->toolStripSeparator39, this->L1DiscardDataTimeChck,
					this->L1FilterCorrectionChck, this->L1TBCChck, this->toolStripSeparator48, this->L1DigestDeleteFileChck
			});
			this->DigestL1FITSImageMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DigestL1FITSImageMenuItem.Image")));
			this->DigestL1FITSImageMenuItem->Name = L"DigestL1FITSImageMenuItem";
			this->DigestL1FITSImageMenuItem->Size = System::Drawing::Size(274, 22);
			this->DigestL1FITSImageMenuItem->Text = L"Digest L1 Fits File(s)";
			this->DigestL1FITSImageMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::DigestL1FITSImageMenuItem_Click);
			// 
			// L1DigestApplyFPNChck
			// 
			this->L1DigestApplyFPNChck->CheckOnClick = true;
			this->L1DigestApplyFPNChck->Name = L"L1DigestApplyFPNChck";
			this->L1DigestApplyFPNChck->Size = System::Drawing::Size(305, 22);
			this->L1DigestApplyFPNChck->Text = L"PC Mode: Apply FPN Correction";
			this->L1DigestApplyFPNChck->Click += gcnew System::EventHandler(this, &Form1::L1DigestApplyFPNChck_Click);
			// 
			// L1DigestApplyDISTChck
			// 
			this->L1DigestApplyDISTChck->CheckOnClick = true;
			this->L1DigestApplyDISTChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem22,
					this->L1DigestApplyDISTInterpNearChck, this->L1DigestApplyDISTInterpBiLinChck
			});
			this->L1DigestApplyDISTChck->Name = L"L1DigestApplyDISTChck";
			this->L1DigestApplyDISTChck->Size = System::Drawing::Size(305, 22);
			this->L1DigestApplyDISTChck->Text = L"PC Mode: Apply CPU Distortion Correction";
			this->L1DigestApplyDISTChck->Click += gcnew System::EventHandler(this, &Form1::L1DigestApplyDISTChck_Click);
			// 
			// toolStripMenuItem22
			// 
			this->toolStripMenuItem22->Enabled = false;
			this->toolStripMenuItem22->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->toolStripMenuItem22->Name = L"toolStripMenuItem22";
			this->toolStripMenuItem22->Size = System::Drawing::Size(152, 22);
			this->toolStripMenuItem22->Text = L"Interpolation";
			// 
			// L1DigestApplyDISTInterpNearChck
			// 
			this->L1DigestApplyDISTInterpNearChck->CheckOnClick = true;
			this->L1DigestApplyDISTInterpNearChck->Name = L"L1DigestApplyDISTInterpNearChck";
			this->L1DigestApplyDISTInterpNearChck->Size = System::Drawing::Size(152, 22);
			this->L1DigestApplyDISTInterpNearChck->Text = L"None (nearest)";
			this->L1DigestApplyDISTInterpNearChck->Click += gcnew System::EventHandler(this, &Form1::L1DigestApplyDISTInterpNearChck_Click);
			// 
			// L1DigestApplyDISTInterpBiLinChck
			// 
			this->L1DigestApplyDISTInterpBiLinChck->CheckOnClick = true;
			this->L1DigestApplyDISTInterpBiLinChck->Name = L"L1DigestApplyDISTInterpBiLinChck";
			this->L1DigestApplyDISTInterpBiLinChck->Size = System::Drawing::Size(152, 22);
			this->L1DigestApplyDISTInterpBiLinChck->Text = L"BiLinear";
			this->L1DigestApplyDISTInterpBiLinChck->Click += gcnew System::EventHandler(this, &Form1::L1DigestApplyDISTInterpBiLinChck_Click);
			// 
			// L1DiscardDuplicateChck
			// 
			this->L1DiscardDuplicateChck->CheckOnClick = true;
			this->L1DiscardDuplicateChck->Name = L"L1DiscardDuplicateChck";
			this->L1DiscardDuplicateChck->Size = System::Drawing::Size(305, 22);
			this->L1DiscardDuplicateChck->Text = L"PC Mode: Discard Duplicate Data Sets";
			this->L1DiscardDuplicateChck->Click += gcnew System::EventHandler(this, &Form1::L1DiscardDuplicateChck_Click);
			// 
			// L1TransformNUVtoFUVChck
			// 
			this->L1TransformNUVtoFUVChck->CheckOnClick = true;
			this->L1TransformNUVtoFUVChck->Name = L"L1TransformNUVtoFUVChck";
			this->L1TransformNUVtoFUVChck->Size = System::Drawing::Size(305, 22);
			this->L1TransformNUVtoFUVChck->Text = L"PC Mode NUV: Tranform NUV to FUV Frame";
			this->L1TransformNUVtoFUVChck->Click += gcnew System::EventHandler(this, &Form1::L1TransformNUVtoFUVChck_Click);
			// 
			// L1DigestPCParityChck
			// 
			this->L1DigestPCParityChck->CheckOnClick = true;
			this->L1DigestPCParityChck->Name = L"L1DigestPCParityChck";
			this->L1DigestPCParityChck->Size = System::Drawing::Size(305, 22);
			this->L1DigestPCParityChck->Text = L"PC Mode: Discard Word Parity Errors";
			this->L1DigestPCParityChck->Click += gcnew System::EventHandler(this, &Form1::L1DigestPCParityChck_Click);
			// 
			// toolStripSeparator36
			// 
			this->toolStripSeparator36->Name = L"toolStripSeparator36";
			this->toolStripSeparator36->Size = System::Drawing::Size(302, 6);
			// 
			// L1SkipINTMode
			// 
			this->L1SkipINTMode->CheckOnClick = true;
			this->L1SkipINTMode->Name = L"L1SkipINTMode";
			this->L1SkipINTMode->Size = System::Drawing::Size(305, 22);
			this->L1SkipINTMode->Text = L"INT Mode: Skip";
			this->L1SkipINTMode->Click += gcnew System::EventHandler(this, &Form1::L1SkipINTMode_Click);
			// 
			// L1DegradientINTMode
			// 
			this->L1DegradientINTMode->CheckOnClick = true;
			this->L1DegradientINTMode->Name = L"L1DegradientINTMode";
			this->L1DegradientINTMode->Size = System::Drawing::Size(305, 22);
			this->L1DegradientINTMode->Text = L"INT Mode: Degradient Images";
			this->L1DegradientINTMode->Click += gcnew System::EventHandler(this, &Form1::L1DegradientINTMode_Click);
			// 
			// L1CleanINTMode
			// 
			this->L1CleanINTMode->CheckOnClick = true;
			this->L1CleanINTMode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->toolStripMenuItem13,
					this->L1CleanINTLineThreshold, this->toolStripSeparator40, this->toolStripMenuItem21, this->L1CleanINTNPix
			});
			this->L1CleanINTMode->Name = L"L1CleanINTMode";
			this->L1CleanINTMode->Size = System::Drawing::Size(305, 22);
			this->L1CleanINTMode->Text = L"INT Mode: Clean Images";
			this->L1CleanINTMode->Click += gcnew System::EventHandler(this, &Form1::L1CleanINTMode_Click);
			// 
			// toolStripMenuItem13
			// 
			this->toolStripMenuItem13->Enabled = false;
			this->toolStripMenuItem13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->toolStripMenuItem13->Name = L"toolStripMenuItem13";
			this->toolStripMenuItem13->Size = System::Drawing::Size(170, 22);
			this->toolStripMenuItem13->Text = L"Line Threshold";
			// 
			// L1CleanINTLineThreshold
			// 
			this->L1CleanINTLineThreshold->BackColor = System::Drawing::Color::Violet;
			this->L1CleanINTLineThreshold->Name = L"L1CleanINTLineThreshold";
			this->L1CleanINTLineThreshold->Size = System::Drawing::Size(100, 23);
			this->L1CleanINTLineThreshold->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->L1CleanINTLineThreshold->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// toolStripSeparator40
			// 
			this->toolStripSeparator40->Name = L"toolStripSeparator40";
			this->toolStripSeparator40->Size = System::Drawing::Size(167, 6);
			// 
			// toolStripMenuItem21
			// 
			this->toolStripMenuItem21->Enabled = false;
			this->toolStripMenuItem21->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->toolStripMenuItem21->Name = L"toolStripMenuItem21";
			this->toolStripMenuItem21->Size = System::Drawing::Size(170, 22);
			this->toolStripMenuItem21->Text = L"Number of Pixels";
			// 
			// L1CleanINTNPix
			// 
			this->L1CleanINTNPix->BackColor = System::Drawing::Color::Violet;
			this->L1CleanINTNPix->Name = L"L1CleanINTNPix";
			this->L1CleanINTNPix->Size = System::Drawing::Size(100, 23);
			this->L1CleanINTNPix->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			this->L1CleanINTNPix->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			// 
			// toolStripSeparator39
			// 
			this->toolStripSeparator39->Name = L"toolStripSeparator39";
			this->toolStripSeparator39->Size = System::Drawing::Size(302, 6);
			// 
			// L1DiscardDataTimeChck
			// 
			this->L1DiscardDataTimeChck->CheckOnClick = true;
			this->L1DiscardDataTimeChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->L1DiscardDataTimeDrop });
			this->L1DiscardDataTimeChck->Name = L"L1DiscardDataTimeChck";
			this->L1DiscardDataTimeChck->Size = System::Drawing::Size(305, 22);
			this->L1DiscardDataTimeChck->Text = L"Discard Data Sets Less Than:";
			this->L1DiscardDataTimeChck->Click += gcnew System::EventHandler(this, &Form1::L1DiscardDataTimeChck_Click);
			// 
			// L1DiscardDataTimeDrop
			// 
			this->L1DiscardDataTimeDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->L1DiscardDataTimeDrop->Enabled = false;
			this->L1DiscardDataTimeDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->L1DiscardDataTimeDrop->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"1 Minutes", L"2 Minutes", L"5 Minutes",
					L"10 Minutes"
			});
			this->L1DiscardDataTimeDrop->Name = L"L1DiscardDataTimeDrop";
			this->L1DiscardDataTimeDrop->Size = System::Drawing::Size(121, 23);
			this->L1DiscardDataTimeDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::L1DiscardDataTimeDrop_SelectedIndexChanged);
			// 
			// L1FilterCorrectionChck
			// 
			this->L1FilterCorrectionChck->CheckOnClick = true;
			this->L1FilterCorrectionChck->Name = L"L1FilterCorrectionChck";
			this->L1FilterCorrectionChck->Size = System::Drawing::Size(305, 22);
			this->L1FilterCorrectionChck->Text = L"Filter Correction";
			this->L1FilterCorrectionChck->Click += gcnew System::EventHandler(this, &Form1::L1FilterCorrectionChck_Click);
			// 
			// L1TBCChck
			// 
			this->L1TBCChck->CheckOnClick = true;
			this->L1TBCChck->Name = L"L1TBCChck";
			this->L1TBCChck->Size = System::Drawing::Size(305, 22);
			this->L1TBCChck->Text = L"TBC";
			this->L1TBCChck->Click += gcnew System::EventHandler(this, &Form1::L1TBCChck_Click);
			// 
			// toolStripSeparator48
			// 
			this->toolStripSeparator48->Name = L"toolStripSeparator48";
			this->toolStripSeparator48->Size = System::Drawing::Size(302, 6);
			// 
			// L1DigestDeleteFileChck
			// 
			this->L1DigestDeleteFileChck->CheckOnClick = true;
			this->L1DigestDeleteFileChck->Name = L"L1DigestDeleteFileChck";
			this->L1DigestDeleteFileChck->Size = System::Drawing::Size(305, 22);
			this->L1DigestDeleteFileChck->Text = L"Delete File(s) After Digestion";
			this->L1DigestDeleteFileChck->Click += gcnew System::EventHandler(this, &Form1::L1DigestDeleteFileChck_Click);
			// 
			// CreateFlatFieldListMenuItem
			// 
			this->CreateFlatFieldListMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CreateFlatFieldListMenuItem.Image")));
			this->CreateFlatFieldListMenuItem->Name = L"CreateFlatFieldListMenuItem";
			this->CreateFlatFieldListMenuItem->Size = System::Drawing::Size(274, 22);
			this->CreateFlatFieldListMenuItem->Text = L"Create Flat Field List";
			this->CreateFlatFieldListMenuItem->Visible = false;
			this->CreateFlatFieldListMenuItem->Click += gcnew System::EventHandler(this, &Form1::CreateFlatFieldListMenuItem_Click);
			// 
			// ApplyUVFPNMenu
			// 
			this->ApplyUVFPNMenu->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ApplyUVFPNMenu.Image")));
			this->ApplyUVFPNMenu->Name = L"ApplyUVFPNMenu";
			this->ApplyUVFPNMenu->Size = System::Drawing::Size(274, 22);
			this->ApplyUVFPNMenu->Text = L"Apply FPN Correction";
			this->ApplyUVFPNMenu->Visible = false;
			this->ApplyUVFPNMenu->Click += gcnew System::EventHandler(this, &Form1::ApplyUVFPNMenu_Click);
			// 
			// UVIT_ApplyCPUCorrectionMenu
			// 
			this->UVIT_ApplyCPUCorrectionMenu->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UVIT_ApplyCPUCorrectionMenu.Image")));
			this->UVIT_ApplyCPUCorrectionMenu->Name = L"UVIT_ApplyCPUCorrectionMenu";
			this->UVIT_ApplyCPUCorrectionMenu->Size = System::Drawing::Size(274, 22);
			this->UVIT_ApplyCPUCorrectionMenu->Text = L"Apply CPU Distortion Correction";
			this->UVIT_ApplyCPUCorrectionMenu->Visible = false;
			this->UVIT_ApplyCPUCorrectionMenu->Click += gcnew System::EventHandler(this, &Form1::UVIT_ApplyCPUCorrectionMenu_Click);
			// 
			// ConvertListToImgMenu
			// 
			this->ConvertListToImgMenu->DoubleClickEnabled = true;
			this->ConvertListToImgMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->FilterCosmicRaysChckMenuItem,
					this->MaxMinThreshChck, this->L1CentroidPaddingChck, this->ApplyExpArrayToImageChck, this->ApplyFlatListToImageChck, this->toolStripSeparator7,
					this->ListToImage1PixMenuItem, this->ListToImage2PixMenuItem, this->ListToImage4PixMenuItem, this->ListToImage8PixMenuItem, this->ListToImage16PixMenuItem
			});
			this->ConvertListToImgMenu->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ConvertListToImgMenu.Image")));
			this->ConvertListToImgMenu->Name = L"ConvertListToImgMenu";
			this->ConvertListToImgMenu->Size = System::Drawing::Size(274, 22);
			this->ConvertListToImgMenu->Text = L"Convert Event List to Image";
			this->ConvertListToImgMenu->DropDownOpened += gcnew System::EventHandler(this, &Form1::ConvertListToImgMenu_DropDownOpened);
			this->ConvertListToImgMenu->DoubleClick += gcnew System::EventHandler(this, &Form1::ConvertListToImgMenu_Click);
			// 
			// FilterCosmicRaysChckMenuItem
			// 
			this->FilterCosmicRaysChckMenuItem->CheckOnClick = true;
			this->FilterCosmicRaysChckMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->CosmicRayFilterCountMenuChck,
					this->CosmicRayFilterMenuTxt, this->toolStripSeparator11, this->CosmicRayFilterSigmaMenuChck, this->CosmicRayFilterSigmaMenuTxt
			});
			this->FilterCosmicRaysChckMenuItem->Name = L"FilterCosmicRaysChckMenuItem";
			this->FilterCosmicRaysChckMenuItem->Size = System::Drawing::Size(245, 22);
			this->FilterCosmicRaysChckMenuItem->Text = L"Filter Cosmic Ray Frames";
			this->FilterCosmicRaysChckMenuItem->Click += gcnew System::EventHandler(this, &Form1::FilterCosmicRaysChckMenuItem_Click);
			// 
			// CosmicRayFilterCountMenuChck
			// 
			this->CosmicRayFilterCountMenuChck->Checked = true;
			this->CosmicRayFilterCountMenuChck->CheckOnClick = true;
			this->CosmicRayFilterCountMenuChck->CheckState = System::Windows::Forms::CheckState::Checked;
			this->CosmicRayFilterCountMenuChck->Enabled = false;
			this->CosmicRayFilterCountMenuChck->Name = L"CosmicRayFilterCountMenuChck";
			this->CosmicRayFilterCountMenuChck->Size = System::Drawing::Size(214, 22);
			this->CosmicRayFilterCountMenuChck->Text = L"Count Rejection Threshold";
			this->CosmicRayFilterCountMenuChck->Click += gcnew System::EventHandler(this, &Form1::CosmicRayFilterMenuChck_Click);
			// 
			// CosmicRayFilterMenuTxt
			// 
			this->CosmicRayFilterMenuTxt->BackColor = System::Drawing::Color::Violet;
			this->CosmicRayFilterMenuTxt->Enabled = false;
			this->CosmicRayFilterMenuTxt->Name = L"CosmicRayFilterMenuTxt";
			this->CosmicRayFilterMenuTxt->Size = System::Drawing::Size(100, 23);
			this->CosmicRayFilterMenuTxt->Text = L"0";
			this->CosmicRayFilterMenuTxt->ToolTipText = L"Enter count per frame cut-off for CR rejection (integer).";
			this->CosmicRayFilterMenuTxt->TextChanged += gcnew System::EventHandler(this, &Form1::CosmicRayFilterMenuTxt_TextChanged);
			// 
			// toolStripSeparator11
			// 
			this->toolStripSeparator11->Name = L"toolStripSeparator11";
			this->toolStripSeparator11->Size = System::Drawing::Size(211, 6);
			// 
			// CosmicRayFilterSigmaMenuChck
			// 
			this->CosmicRayFilterSigmaMenuChck->CheckOnClick = true;
			this->CosmicRayFilterSigmaMenuChck->Enabled = false;
			this->CosmicRayFilterSigmaMenuChck->Name = L"CosmicRayFilterSigmaMenuChck";
			this->CosmicRayFilterSigmaMenuChck->Size = System::Drawing::Size(214, 22);
			this->CosmicRayFilterSigmaMenuChck->Text = L"Sigma Rejection Threshold";
			this->CosmicRayFilterSigmaMenuChck->Click += gcnew System::EventHandler(this, &Form1::CosmicRayFilterSigmaMenuChck_Click);
			// 
			// CosmicRayFilterSigmaMenuTxt
			// 
			this->CosmicRayFilterSigmaMenuTxt->BackColor = System::Drawing::Color::Violet;
			this->CosmicRayFilterSigmaMenuTxt->Enabled = false;
			this->CosmicRayFilterSigmaMenuTxt->Name = L"CosmicRayFilterSigmaMenuTxt";
			this->CosmicRayFilterSigmaMenuTxt->Size = System::Drawing::Size(100, 23);
			this->CosmicRayFilterSigmaMenuTxt->Text = L"0";
			this->CosmicRayFilterSigmaMenuTxt->ToolTipText = L"Enter count sigma cut-off for CR rejection (integer or decimal).";
			this->CosmicRayFilterSigmaMenuTxt->TextChanged += gcnew System::EventHandler(this, &Form1::CosmicRayFilterSigmaMenuTxt_TextChanged);
			// 
			// MaxMinThreshChck
			// 
			this->MaxMinThreshChck->CheckOnClick = true;
			this->MaxMinThreshChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->MaxMinThreshTxt,
					this->MaxMinCountTwiceChck
			});
			this->MaxMinThreshChck->Name = L"MaxMinThreshChck";
			this->MaxMinThreshChck->Size = System::Drawing::Size(245, 22);
			this->MaxMinThreshChck->Text = L"Apply Max-Min Threshold";
			this->MaxMinThreshChck->Click += gcnew System::EventHandler(this, &Form1::MaxMinThreshChck_Click);
			// 
			// MaxMinThreshTxt
			// 
			this->MaxMinThreshTxt->BackColor = System::Drawing::Color::Violet;
			this->MaxMinThreshTxt->Enabled = false;
			this->MaxMinThreshTxt->Name = L"MaxMinThreshTxt";
			this->MaxMinThreshTxt->Size = System::Drawing::Size(100, 23);
			this->MaxMinThreshTxt->ToolTipText = L"Enter rejection threshold value; range 0 to 16384";
			this->MaxMinThreshTxt->TextChanged += gcnew System::EventHandler(this, &Form1::MaxMinThreshTxt_TextChanged);
			// 
			// MaxMinCountTwiceChck
			// 
			this->MaxMinCountTwiceChck->CheckOnClick = true;
			this->MaxMinCountTwiceChck->Enabled = false;
			this->MaxMinCountTwiceChck->Name = L"MaxMinCountTwiceChck";
			this->MaxMinCountTwiceChck->Size = System::Drawing::Size(160, 22);
			this->MaxMinCountTwiceChck->Text = L"Count Twice";
			this->MaxMinCountTwiceChck->Click += gcnew System::EventHandler(this, &Form1::MaxMinCountTwiceChck_Click);
			// 
			// L1CentroidPaddingChck
			// 
			this->L1CentroidPaddingChck->CheckOnClick = true;
			this->L1CentroidPaddingChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->PCCentroidPaddingDrop });
			this->L1CentroidPaddingChck->Name = L"L1CentroidPaddingChck";
			this->L1CentroidPaddingChck->Size = System::Drawing::Size(245, 22);
			this->L1CentroidPaddingChck->Text = L"Centroid Image Padding";
			this->L1CentroidPaddingChck->Click += gcnew System::EventHandler(this, &Form1::L1CentroidPaddingChck_Click);
			// 
			// PCCentroidPaddingDrop
			// 
			this->PCCentroidPaddingDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PCCentroidPaddingDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->PCCentroidPaddingDrop->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"22", L"44" });
			this->PCCentroidPaddingDrop->Name = L"PCCentroidPaddingDrop";
			this->PCCentroidPaddingDrop->Size = System::Drawing::Size(121, 23);
			this->PCCentroidPaddingDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PCCentroidPaddingDrop_SelectedIndexChanged);
			// 
			// ApplyExpArrayToImageChck
			// 
			this->ApplyExpArrayToImageChck->CheckOnClick = true;
			this->ApplyExpArrayToImageChck->Name = L"ApplyExpArrayToImageChck";
			this->ApplyExpArrayToImageChck->Size = System::Drawing::Size(245, 22);
			this->ApplyExpArrayToImageChck->Text = L"Apply Exposure Array Weighting";
			this->ApplyExpArrayToImageChck->Click += gcnew System::EventHandler(this, &Form1::ApplyExpArrayToImageChck_Click);
			// 
			// ApplyFlatListToImageChck
			// 
			this->ApplyFlatListToImageChck->CheckOnClick = true;
			this->ApplyFlatListToImageChck->Name = L"ApplyFlatListToImageChck";
			this->ApplyFlatListToImageChck->Size = System::Drawing::Size(245, 22);
			this->ApplyFlatListToImageChck->Text = L"Apply Flat Field Weighting";
			this->ApplyFlatListToImageChck->Click += gcnew System::EventHandler(this, &Form1::ApplyFlatListToImageChck_Click);
			// 
			// toolStripSeparator7
			// 
			this->toolStripSeparator7->Name = L"toolStripSeparator7";
			this->toolStripSeparator7->Size = System::Drawing::Size(242, 6);
			// 
			// ListToImage1PixMenuItem
			// 
			this->ListToImage1PixMenuItem->Checked = true;
			this->ListToImage1PixMenuItem->CheckOnClick = true;
			this->ListToImage1PixMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ListToImage1PixMenuItem->Name = L"ListToImage1PixMenuItem";
			this->ListToImage1PixMenuItem->Size = System::Drawing::Size(245, 22);
			this->ListToImage1PixMenuItem->Text = L"1 Pixel Resolution";
			this->ListToImage1PixMenuItem->Click += gcnew System::EventHandler(this, &Form1::ListToImage1PixMenuItem_Click);
			// 
			// ListToImage2PixMenuItem
			// 
			this->ListToImage2PixMenuItem->CheckOnClick = true;
			this->ListToImage2PixMenuItem->Name = L"ListToImage2PixMenuItem";
			this->ListToImage2PixMenuItem->Size = System::Drawing::Size(245, 22);
			this->ListToImage2PixMenuItem->Text = L"1/2 Pixel Resolution";
			this->ListToImage2PixMenuItem->Click += gcnew System::EventHandler(this, &Form1::ListToImage2PixMenuItem_Click);
			// 
			// ListToImage4PixMenuItem
			// 
			this->ListToImage4PixMenuItem->CheckOnClick = true;
			this->ListToImage4PixMenuItem->Name = L"ListToImage4PixMenuItem";
			this->ListToImage4PixMenuItem->Size = System::Drawing::Size(245, 22);
			this->ListToImage4PixMenuItem->Text = L"1/4 Pixel Resolution";
			this->ListToImage4PixMenuItem->Click += gcnew System::EventHandler(this, &Form1::ListToImage4PixMenuItem_Click);
			// 
			// ListToImage8PixMenuItem
			// 
			this->ListToImage8PixMenuItem->CheckOnClick = true;
			this->ListToImage8PixMenuItem->Name = L"ListToImage8PixMenuItem";
			this->ListToImage8PixMenuItem->Size = System::Drawing::Size(245, 22);
			this->ListToImage8PixMenuItem->Text = L"1/8 Pixel Resolution";
			this->ListToImage8PixMenuItem->Click += gcnew System::EventHandler(this, &Form1::ListToImage8PixMenuItem_Click);
			// 
			// ListToImage16PixMenuItem
			// 
			this->ListToImage16PixMenuItem->CheckOnClick = true;
			this->ListToImage16PixMenuItem->Name = L"ListToImage16PixMenuItem";
			this->ListToImage16PixMenuItem->Size = System::Drawing::Size(245, 22);
			this->ListToImage16PixMenuItem->Text = L"1/16 Pixel Resolution";
			this->ListToImage16PixMenuItem->Click += gcnew System::EventHandler(this, &Form1::ListToImage16PixMenuItem_Click);
			// 
			// PlotCountsPerFrameMenuItem
			// 
			this->PlotCountsPerFrameMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->perFrameMenuItem,
					this->toolStripSeparator17, this->perTimeBinMenuItem, this->plotPerTimeBinComboBox
			});
			this->PlotCountsPerFrameMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PlotCountsPerFrameMenuItem.Image")));
			this->PlotCountsPerFrameMenuItem->Name = L"PlotCountsPerFrameMenuItem";
			this->PlotCountsPerFrameMenuItem->Size = System::Drawing::Size(274, 22);
			this->PlotCountsPerFrameMenuItem->Text = L"Plot Counts";
			// 
			// perFrameMenuItem
			// 
			this->perFrameMenuItem->Name = L"perFrameMenuItem";
			this->perFrameMenuItem->Size = System::Drawing::Size(181, 22);
			this->perFrameMenuItem->Text = L"Per Frame";
			this->perFrameMenuItem->Click += gcnew System::EventHandler(this, &Form1::PlotCountsPerFrameMenuItem_Click);
			// 
			// toolStripSeparator17
			// 
			this->toolStripSeparator17->Name = L"toolStripSeparator17";
			this->toolStripSeparator17->Size = System::Drawing::Size(178, 6);
			// 
			// perTimeBinMenuItem
			// 
			this->perTimeBinMenuItem->Name = L"perTimeBinMenuItem";
			this->perTimeBinMenuItem->Size = System::Drawing::Size(181, 22);
			this->perTimeBinMenuItem->Text = L"Per Time Bin";
			this->perTimeBinMenuItem->Click += gcnew System::EventHandler(this, &Form1::perTimeBinMenuItem_Click);
			// 
			// plotPerTimeBinComboBox
			// 
			this->plotPerTimeBinComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->plotPerTimeBinComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->plotPerTimeBinComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"1s", L"2s", L"5s", L"10s", L"30s",
					L"60s", L"120s", L"300s"
			});
			this->plotPerTimeBinComboBox->Name = L"plotPerTimeBinComboBox";
			this->plotPerTimeBinComboBox->Size = System::Drawing::Size(121, 23);
			// 
			// ParcelListAsFramesMenuItem
			// 
			this->ParcelListAsFramesMenuItem->DoubleClickEnabled = true;
			this->ParcelListAsFramesMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ParcelStackTimeDrop,
					this->ParcelStackmdMmChck
			});
			this->ParcelListAsFramesMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ParcelListAsFramesMenuItem.Image")));
			this->ParcelListAsFramesMenuItem->Name = L"ParcelListAsFramesMenuItem";
			this->ParcelListAsFramesMenuItem->Size = System::Drawing::Size(274, 22);
			this->ParcelListAsFramesMenuItem->Text = L"Parcel Out List as Frames";
			// 
			// ParcelStackTimeDrop
			// 
			this->ParcelStackTimeDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ParcelStackTimeDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->ParcelStackTimeDrop->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"0 second stacks", L"1 second stacks",
					L"2 second stacks", L"5 second stacks", L"10 second stacks", L"20 second stacks"
			});
			this->ParcelStackTimeDrop->Name = L"ParcelStackTimeDrop";
			this->ParcelStackTimeDrop->Size = System::Drawing::Size(121, 23);
			this->ParcelStackTimeDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ParcelStackTimeDrop_Click);
			// 
			// ParcelStackmdMmChck
			// 
			this->ParcelStackmdMmChck->CheckOnClick = true;
			this->ParcelStackmdMmChck->Name = L"ParcelStackmdMmChck";
			this->ParcelStackmdMmChck->Size = System::Drawing::Size(231, 22);
			this->ParcelStackmdMmChck->Text = L"Make min && Max-min frames";
			this->ParcelStackmdMmChck->Click += gcnew System::EventHandler(this, &Form1::ParcelStackmdMmChck_Click);
			// 
			// CreateDriftListMenuItem
			// 
			this->CreateDriftListMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->CreateDriftFromPCMenuItem,
					this->CreateDriftFromINTMenuItem, this->PlotDriftListMenuItem, this->CleanVISImagesMenuItem
			});
			this->CreateDriftListMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CreateDriftListMenuItem.Image")));
			this->CreateDriftListMenuItem->Name = L"CreateDriftListMenuItem";
			this->CreateDriftListMenuItem->Size = System::Drawing::Size(274, 22);
			this->CreateDriftListMenuItem->Text = L"Create Drift Correction List";
			// 
			// CreateDriftFromPCMenuItem
			// 
			this->CreateDriftFromPCMenuItem->DoubleClickEnabled = true;
			this->CreateDriftFromPCMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->DriftFromListTimeTxt,
					this->DriftFromListEndTimeTxt, this->DriftStackTimeDrop, this->DriftPCROIOnly, this->DriftFromPCInterpolateChck, this->DriftSmoothNDrop,
					this->UVAutoApplyDriftandImageChck, this->toolStripSeparator12, this->DriftFromPCPSTrackBtn
			});
			this->CreateDriftFromPCMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CreateDriftFromPCMenuItem.Image")));
			this->CreateDriftFromPCMenuItem->Name = L"CreateDriftFromPCMenuItem";
			this->CreateDriftFromPCMenuItem->Size = System::Drawing::Size(201, 22);
			this->CreateDriftFromPCMenuItem->Text = L"From PC Mode List";
			this->CreateDriftFromPCMenuItem->DropDownOpened += gcnew System::EventHandler(this, &Form1::CreateDriftFromPCMenuItem_DropDownOpened);
			this->CreateDriftFromPCMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::CreateDriftFromPCMenuItem_DoubleClick);
			// 
			// DriftFromListTimeTxt
			// 
			this->DriftFromListTimeTxt->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->DriftFromListTimeTxt->BackColor = System::Drawing::Color::Violet;
			this->DriftFromListTimeTxt->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->DriftFromListTimeTxt->Name = L"DriftFromListTimeTxt";
			this->DriftFromListTimeTxt->Size = System::Drawing::Size(100, 23);
			this->DriftFromListTimeTxt->ToolTipText = L"Enter start frame time. Leave blank if not needed. (milliseconds)";
			this->DriftFromListTimeTxt->TextChanged += gcnew System::EventHandler(this, &Form1::DriftFromListTimeTxt_TextChanged);
			// 
			// DriftFromListEndTimeTxt
			// 
			this->DriftFromListEndTimeTxt->BackColor = System::Drawing::Color::Violet;
			this->DriftFromListEndTimeTxt->Name = L"DriftFromListEndTimeTxt";
			this->DriftFromListEndTimeTxt->Size = System::Drawing::Size(100, 23);
			this->DriftFromListEndTimeTxt->ToolTipText = L"Enter end frame time. Leave blank if not needed. (milliseconds)";
			this->DriftFromListEndTimeTxt->TextChanged += gcnew System::EventHandler(this, &Form1::DriftFromListEndTimeTxt_TextChanged);
			// 
			// DriftStackTimeDrop
			// 
			this->DriftStackTimeDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DriftStackTimeDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->DriftStackTimeDrop->Items->AddRange(gcnew cli::array< System::Object^  >(15) {
				L"0.5 second stacks", L"1 second stacks",
					L"2 second stacks", L"3 second stacks", L"4 second stacks", L"5 second stacks", L"7 second stacks", L"10 second stacks", L"20 second stacks",
					L"30 second stacks", L"40 second stacks", L"50 second stacks", L"60 second stacks", L"90 second stacks", L"120 second stacks"
			});
			this->DriftStackTimeDrop->Name = L"DriftStackTimeDrop";
			this->DriftStackTimeDrop->Size = System::Drawing::Size(121, 23);
			this->DriftStackTimeDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::DriftStackTimeDrop_SelectedIndexChanged);
			// 
			// DriftPCROIOnly
			// 
			this->DriftPCROIOnly->CheckOnClick = true;
			this->DriftPCROIOnly->Name = L"DriftPCROIOnly";
			this->DriftPCROIOnly->Size = System::Drawing::Size(246, 22);
			this->DriftPCROIOnly->Text = L"Use Current ROI Only";
			this->DriftPCROIOnly->Click += gcnew System::EventHandler(this, &Form1::DriftPCROIOnly_Click);
			// 
			// DriftFromPCInterpolateChck
			// 
			this->DriftFromPCInterpolateChck->CheckOnClick = true;
			this->DriftFromPCInterpolateChck->Name = L"DriftFromPCInterpolateChck";
			this->DriftFromPCInterpolateChck->Size = System::Drawing::Size(246, 22);
			this->DriftFromPCInterpolateChck->Text = L"Interpolate && Smooth";
			this->DriftFromPCInterpolateChck->Click += gcnew System::EventHandler(this, &Form1::DriftFromPCInterpolateChck_Click);
			// 
			// DriftSmoothNDrop
			// 
			this->DriftSmoothNDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DriftSmoothNDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->DriftSmoothNDrop->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"3", L"5", L"7", L"9", L"11", L"13", L"15" });
			this->DriftSmoothNDrop->Name = L"DriftSmoothNDrop";
			this->DriftSmoothNDrop->Size = System::Drawing::Size(121, 23);
			this->DriftSmoothNDrop->ToolTipText = L"Smoothing Range (higher number = more smoothing)";
			this->DriftSmoothNDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::DriftSmoothNDrop_SelectedIndexChanged);
			// 
			// UVAutoApplyDriftandImageChck
			// 
			this->UVAutoApplyDriftandImageChck->CheckOnClick = true;
			this->UVAutoApplyDriftandImageChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->UVAutoDriftImageViewChck });
			this->UVAutoApplyDriftandImageChck->Name = L"UVAutoApplyDriftandImageChck";
			this->UVAutoApplyDriftandImageChck->Size = System::Drawing::Size(246, 22);
			this->UVAutoApplyDriftandImageChck->Text = L"Auto Apply Drift && Create Image";
			this->UVAutoApplyDriftandImageChck->Visible = false;
			this->UVAutoApplyDriftandImageChck->Click += gcnew System::EventHandler(this, &Form1::UVAutoApplyDriftandImageChck_Click);
			// 
			// UVAutoDriftImageViewChck
			// 
			this->UVAutoDriftImageViewChck->CheckOnClick = true;
			this->UVAutoDriftImageViewChck->Name = L"UVAutoDriftImageViewChck";
			this->UVAutoDriftImageViewChck->Size = System::Drawing::Size(135, 22);
			this->UVAutoDriftImageViewChck->Text = L"View Image";
			this->UVAutoDriftImageViewChck->Click += gcnew System::EventHandler(this, &Form1::UVAutoDriftImageViewChck_Click);
			// 
			// toolStripSeparator12
			// 
			this->toolStripSeparator12->Name = L"toolStripSeparator12";
			this->toolStripSeparator12->Size = System::Drawing::Size(243, 6);
			// 
			// DriftFromPCPSTrackBtn
			// 
			this->DriftFromPCPSTrackBtn->DoubleClickEnabled = true;
			this->DriftFromPCPSTrackBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->PointSrcROIAutoRunChck,
					this->PointSrcROIFindSrcChck, this->PointSrcROIFindNSrcDrop, this->toolStripMenuItem1, this->PointSrcROIStackDriftDrop
			});
			this->DriftFromPCPSTrackBtn->Name = L"DriftFromPCPSTrackBtn";
			this->DriftFromPCPSTrackBtn->Size = System::Drawing::Size(246, 22);
			this->DriftFromPCPSTrackBtn->Text = L"Optimize Point Source ROI";
			this->DriftFromPCPSTrackBtn->DoubleClick += gcnew System::EventHandler(this, &Form1::DriftFromPCPSTrackBtn_Click);
			// 
			// PointSrcROIAutoRunChck
			// 
			this->PointSrcROIAutoRunChck->CheckOnClick = true;
			this->PointSrcROIAutoRunChck->Name = L"PointSrcROIAutoRunChck";
			this->PointSrcROIAutoRunChck->Size = System::Drawing::Size(181, 22);
			this->PointSrcROIAutoRunChck->Text = L"Auto Run";
			this->PointSrcROIAutoRunChck->Click += gcnew System::EventHandler(this, &Form1::PointSrcROIAutoRunChck_Click);
			// 
			// PointSrcROIFindSrcChck
			// 
			this->PointSrcROIFindSrcChck->CheckOnClick = true;
			this->PointSrcROIFindSrcChck->Name = L"PointSrcROIFindSrcChck";
			this->PointSrcROIFindSrcChck->Size = System::Drawing::Size(181, 22);
			this->PointSrcROIFindSrcChck->Text = L"Auto Detect Sources";
			this->PointSrcROIFindSrcChck->Click += gcnew System::EventHandler(this, &Form1::PointSrcROIFindSrcChck_Click);
			// 
			// PointSrcROIFindNSrcDrop
			// 
			this->PointSrcROIFindNSrcDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PointSrcROIFindNSrcDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->PointSrcROIFindNSrcDrop->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"2", L"3", L"4", L"5", L"6", L"7" });
			this->PointSrcROIFindNSrcDrop->Name = L"PointSrcROIFindNSrcDrop";
			this->PointSrcROIFindNSrcDrop->Size = System::Drawing::Size(121, 23);
			this->PointSrcROIFindNSrcDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PointSrcROIFindNSrcDrop_SelectedIndexChanged);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Enabled = false;
			this->toolStripMenuItem1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(181, 22);
			this->toolStripMenuItem1->Text = L"Stack Time (s)";
			// 
			// PointSrcROIStackDriftDrop
			// 
			this->PointSrcROIStackDriftDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PointSrcROIStackDriftDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->PointSrcROIStackDriftDrop->Items->AddRange(gcnew cli::array< System::Object^  >(14) {
				L"1", L"2", L"3", L"5", L"7", L"10",
					L"15", L"20", L"25", L"30", L"40", L"50", L"75", L"100"
			});
			this->PointSrcROIStackDriftDrop->Name = L"PointSrcROIStackDriftDrop";
			this->PointSrcROIStackDriftDrop->Size = System::Drawing::Size(121, 23);
			this->PointSrcROIStackDriftDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PointSrcROIStackDriftDrop_SelectedIndexChanged);
			// 
			// CreateDriftFromINTMenuItem
			// 
			this->CreateDriftFromINTMenuItem->DoubleClickEnabled = true;
			this->CreateDriftFromINTMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->CrossCorrINTDriftChck,
					this->PointSrcINTDriftChck, this->toolStripSeparator10, this->SmoothINTDriftChck, this->TryAutoDeBiasINTDrift, this->PointSrcINTDriftNoPlotConfChck
			});
			this->CreateDriftFromINTMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CreateDriftFromINTMenuItem.Image")));
			this->CreateDriftFromINTMenuItem->Name = L"CreateDriftFromINTMenuItem";
			this->CreateDriftFromINTMenuItem->Size = System::Drawing::Size(201, 22);
			this->CreateDriftFromINTMenuItem->Text = L"From INT Mode Frames";
			this->CreateDriftFromINTMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::CreateDriftFromINTMenuItem_Click);
			// 
			// CrossCorrINTDriftChck
			// 
			this->CrossCorrINTDriftChck->Checked = true;
			this->CrossCorrINTDriftChck->CheckOnClick = true;
			this->CrossCorrINTDriftChck->CheckState = System::Windows::Forms::CheckState::Checked;
			this->CrossCorrINTDriftChck->Name = L"CrossCorrINTDriftChck";
			this->CrossCorrINTDriftChck->Size = System::Drawing::Size(247, 22);
			this->CrossCorrINTDriftChck->Text = L"Cross-Correlation";
			this->CrossCorrINTDriftChck->Click += gcnew System::EventHandler(this, &Form1::CrossCorrINTDriftChck_Click);
			// 
			// PointSrcINTDriftChck
			// 
			this->PointSrcINTDriftChck->CheckOnClick = true;
			this->PointSrcINTDriftChck->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->PointSrcINTDriftDisplayChck,
					this->PointSrcINTDriftDisplayCadenceDrop, this->PSTrackDisplayClearBtn, this->toolStripSeparator16, this->PointSrcINTDriftNoPSEConfChck
			});
			this->PointSrcINTDriftChck->Name = L"PointSrcINTDriftChck";
			this->PointSrcINTDriftChck->Size = System::Drawing::Size(247, 22);
			this->PointSrcINTDriftChck->Text = L"Point-Source Track";
			this->PointSrcINTDriftChck->Click += gcnew System::EventHandler(this, &Form1::PointSrcINTDriftChck_Click);
			// 
			// PointSrcINTDriftDisplayChck
			// 
			this->PointSrcINTDriftDisplayChck->CheckOnClick = true;
			this->PointSrcINTDriftDisplayChck->Name = L"PointSrcINTDriftDisplayChck";
			this->PointSrcINTDriftDisplayChck->Size = System::Drawing::Size(186, 22);
			this->PointSrcINTDriftDisplayChck->Text = L"Display Track";
			this->PointSrcINTDriftDisplayChck->Click += gcnew System::EventHandler(this, &Form1::PointSrcINTDriftDisplayChck_Click);
			// 
			// PointSrcINTDriftDisplayCadenceDrop
			// 
			this->PointSrcINTDriftDisplayCadenceDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PointSrcINTDriftDisplayCadenceDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->PointSrcINTDriftDisplayCadenceDrop->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"1", L"2", L"5", L"10",
					L"15", L"20"
			});
			this->PointSrcINTDriftDisplayCadenceDrop->Name = L"PointSrcINTDriftDisplayCadenceDrop";
			this->PointSrcINTDriftDisplayCadenceDrop->Size = System::Drawing::Size(121, 23);
			this->PointSrcINTDriftDisplayCadenceDrop->ToolTipText = L"Update Display Every N Frames";
			this->PointSrcINTDriftDisplayCadenceDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::PointSrcINTDriftDisplayCadenceDrop_SelectedIndexChanged);
			// 
			// PSTrackDisplayClearBtn
			// 
			this->PSTrackDisplayClearBtn->Name = L"PSTrackDisplayClearBtn";
			this->PSTrackDisplayClearBtn->Size = System::Drawing::Size(186, 22);
			this->PSTrackDisplayClearBtn->Text = L"Clear Display Track";
			this->PSTrackDisplayClearBtn->Click += gcnew System::EventHandler(this, &Form1::PSTrackDisplayClearBtn_Click);
			// 
			// toolStripSeparator16
			// 
			this->toolStripSeparator16->Name = L"toolStripSeparator16";
			this->toolStripSeparator16->Size = System::Drawing::Size(183, 6);
			// 
			// PointSrcINTDriftNoPSEConfChck
			// 
			this->PointSrcINTDriftNoPSEConfChck->CheckOnClick = true;
			this->PointSrcINTDriftNoPSEConfChck->Name = L"PointSrcINTDriftNoPSEConfChck";
			this->PointSrcINTDriftNoPSEConfChck->Size = System::Drawing::Size(186, 22);
			this->PointSrcINTDriftNoPSEConfChck->Text = L"No PSE Confirmation";
			this->PointSrcINTDriftNoPSEConfChck->Click += gcnew System::EventHandler(this, &Form1::PointSrcINTDriftNoPSEConfChck_Click);
			// 
			// toolStripSeparator10
			// 
			this->toolStripSeparator10->Name = L"toolStripSeparator10";
			this->toolStripSeparator10->Size = System::Drawing::Size(244, 6);
			// 
			// SmoothINTDriftChck
			// 
			this->SmoothINTDriftChck->CheckOnClick = true;
			this->SmoothINTDriftChck->Name = L"SmoothINTDriftChck";
			this->SmoothINTDriftChck->Size = System::Drawing::Size(247, 22);
			this->SmoothINTDriftChck->Text = L"Smooth";
			this->SmoothINTDriftChck->Click += gcnew System::EventHandler(this, &Form1::SmoothINTDriftChck_Click);
			// 
			// TryAutoDeBiasINTDrift
			// 
			this->TryAutoDeBiasINTDrift->CheckOnClick = true;
			this->TryAutoDeBiasINTDrift->Name = L"TryAutoDeBiasINTDrift";
			this->TryAutoDeBiasINTDrift->Size = System::Drawing::Size(247, 22);
			this->TryAutoDeBiasINTDrift->Text = L"Auto De-Bias";
			this->TryAutoDeBiasINTDrift->Click += gcnew System::EventHandler(this, &Form1::TryAutoDeBiasINTDrift_Click);
			// 
			// PointSrcINTDriftNoPlotConfChck
			// 
			this->PointSrcINTDriftNoPlotConfChck->CheckOnClick = true;
			this->PointSrcINTDriftNoPlotConfChck->Name = L"PointSrcINTDriftNoPlotConfChck";
			this->PointSrcINTDriftNoPlotConfChck->Size = System::Drawing::Size(247, 22);
			this->PointSrcINTDriftNoPlotConfChck->Text = L"No Drift Series Plot Confirmation";
			this->PointSrcINTDriftNoPlotConfChck->Click += gcnew System::EventHandler(this, &Form1::PointSrcINTDriftNoPlotConfChck_Click);
			// 
			// PlotDriftListMenuItem
			// 
			this->PlotDriftListMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PlotDriftListMenuItem.Image")));
			this->PlotDriftListMenuItem->Name = L"PlotDriftListMenuItem";
			this->PlotDriftListMenuItem->Size = System::Drawing::Size(201, 22);
			this->PlotDriftListMenuItem->Text = L"Plot Drift Correction List";
			this->PlotDriftListMenuItem->Click += gcnew System::EventHandler(this, &Form1::PlotDriftListMenuItem_Click);
			// 
			// CleanVISImagesMenuItem
			// 
			this->CleanVISImagesMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"CleanVISImagesMenuItem.Image")));
			this->CleanVISImagesMenuItem->Name = L"CleanVISImagesMenuItem";
			this->CleanVISImagesMenuItem->Size = System::Drawing::Size(201, 22);
			this->CleanVISImagesMenuItem->Text = L"Clean VIS Images";
			this->CleanVISImagesMenuItem->Click += gcnew System::EventHandler(this, &Form1::CleanVISImagesMenuItem_Click);
			// 
			// ApplyDriftListMentuItem
			// 
			this->ApplyDriftListMentuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ConsolidateNUVApplyToFUV,
					this->PCModeDriftSelfCorrectionMenuItem, this->INTAtoINTADriftCorrectionMenuItem, this->ApplyDriftCreateExpArrayChc
			});
			this->ApplyDriftListMentuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ApplyDriftListMentuItem.Image")));
			this->ApplyDriftListMentuItem->Name = L"ApplyDriftListMentuItem";
			this->ApplyDriftListMentuItem->Size = System::Drawing::Size(274, 22);
			this->ApplyDriftListMentuItem->Text = L"Apply Drift Correction";
			// 
			// ConsolidateNUVApplyToFUV
			// 
			this->ConsolidateNUVApplyToFUV->DoubleClickEnabled = true;
			this->ConsolidateNUVApplyToFUV->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ConsolidateDriftFolderChck,
					this->ConsolidateTimeListFolderChck
			});
			this->ConsolidateNUVApplyToFUV->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ConsolidateNUVApplyToFUV.Image")));
			this->ConsolidateNUVApplyToFUV->Name = L"ConsolidateNUVApplyToFUV";
			this->ConsolidateNUVApplyToFUV->Size = System::Drawing::Size(382, 22);
			this->ConsolidateNUVApplyToFUV->Text = L"Consolidate NUV or VIS Drift Series && Apply to NUV or FUV";
			this->ConsolidateNUVApplyToFUV->DoubleClick += gcnew System::EventHandler(this, &Form1::ConsolidateNUVApplyToFUV_Click);
			// 
			// ConsolidateDriftFolderChck
			// 
			this->ConsolidateDriftFolderChck->CheckOnClick = true;
			this->ConsolidateDriftFolderChck->Name = L"ConsolidateDriftFolderChck";
			this->ConsolidateDriftFolderChck->Size = System::Drawing::Size(253, 22);
			this->ConsolidateDriftFolderChck->Text = L"Folder Browse Scan for Drift Series";
			this->ConsolidateDriftFolderChck->Click += gcnew System::EventHandler(this, &Form1::ConsolidateDriftFolderChck_Click);
			// 
			// ConsolidateTimeListFolderChck
			// 
			this->ConsolidateTimeListFolderChck->CheckOnClick = true;
			this->ConsolidateTimeListFolderChck->Name = L"ConsolidateTimeListFolderChck";
			this->ConsolidateTimeListFolderChck->Size = System::Drawing::Size(253, 22);
			this->ConsolidateTimeListFolderChck->Text = L"Folder Browse Scan for TimeLists";
			this->ConsolidateTimeListFolderChck->Click += gcnew System::EventHandler(this, &Form1::ConsolidateTimeListFolderChck_Click);
			// 
			// PCModeDriftSelfCorrectionMenuItem
			// 
			this->PCModeDriftSelfCorrectionMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PCModeDriftSelfCorrectionMenuItem.Image")));
			this->PCModeDriftSelfCorrectionMenuItem->Name = L"PCModeDriftSelfCorrectionMenuItem";
			this->PCModeDriftSelfCorrectionMenuItem->Size = System::Drawing::Size(382, 22);
			this->PCModeDriftSelfCorrectionMenuItem->Text = L"From PC Mode for Self-Correction";
			this->PCModeDriftSelfCorrectionMenuItem->Click += gcnew System::EventHandler(this, &Form1::ApplyDriftListMentuItem_Click);
			// 
			// INTAtoINTADriftCorrectionMenuItem
			// 
			this->INTAtoINTADriftCorrectionMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"INTAtoINTADriftCorrectionMenuItem.Image")));
			this->INTAtoINTADriftCorrectionMenuItem->Name = L"INTAtoINTADriftCorrectionMenuItem";
			this->INTAtoINTADriftCorrectionMenuItem->Size = System::Drawing::Size(382, 22);
			this->INTAtoINTADriftCorrectionMenuItem->Text = L"From INT Channel Drift to INT Channel Images";
			this->INTAtoINTADriftCorrectionMenuItem->Click += gcnew System::EventHandler(this, &Form1::INTAtoINTADriftCorrectionMenuItem_Click);
			// 
			// ApplyDriftCreateExpArrayChc
			// 
			this->ApplyDriftCreateExpArrayChc->Checked = true;
			this->ApplyDriftCreateExpArrayChc->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ApplyDriftCreateExpArrayChc->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ExposureArrayResMenuText,
					this->ExposureArrayResolutionDrop
			});
			this->ApplyDriftCreateExpArrayChc->Name = L"ApplyDriftCreateExpArrayChc";
			this->ApplyDriftCreateExpArrayChc->Size = System::Drawing::Size(382, 22);
			this->ApplyDriftCreateExpArrayChc->Text = L"Create Exposure Array";
			this->ApplyDriftCreateExpArrayChc->Click += gcnew System::EventHandler(this, &Form1::ApplyDriftCreateExpArrayChc_Click);
			// 
			// ExposureArrayResMenuText
			// 
			this->ExposureArrayResMenuText->Enabled = false;
			this->ExposureArrayResMenuText->Name = L"ExposureArrayResMenuText";
			this->ExposureArrayResMenuText->Size = System::Drawing::Size(212, 22);
			this->ExposureArrayResMenuText->Text = L"Exposure Array Resolution";
			this->ExposureArrayResMenuText->Click += gcnew System::EventHandler(this, &Form1::ExposureArrayResMenuText_Click);
			// 
			// ExposureArrayResolutionDrop
			// 
			this->ExposureArrayResolutionDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ExposureArrayResolutionDrop->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"1", L"2" });
			this->ExposureArrayResolutionDrop->Name = L"ExposureArrayResolutionDrop";
			this->ExposureArrayResolutionDrop->Size = System::Drawing::Size(121, 23);
			this->ExposureArrayResolutionDrop->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::ExposureArrayResolutionDrop_SelectedIndexChanged);
			// 
			// ShiftAndRotateMenuItem
			// 
			this->ShiftAndRotateMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->GeneralUVRegistrationMenuItem,
					this->UserDefinedShiftRotateMenuItem, this->toolStripSeparator15, this->UVCombineCentroidListsMenuItem, this->UVLoadAllMerged,
					this->toolStripSeparator20, this->UVNUVToFUVFrameMenuItem, this->DeRotateViaWCSBtn, this->invertWCSToolStripMenuItem
			});
			this->ShiftAndRotateMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShiftAndRotateMenuItem.Image")));
			this->ShiftAndRotateMenuItem->Name = L"ShiftAndRotateMenuItem";
			this->ShiftAndRotateMenuItem->Size = System::Drawing::Size(274, 22);
			this->ShiftAndRotateMenuItem->Text = L"Registration, Rotation, Transformation";
			// 
			// GeneralUVRegistrationMenuItem
			// 
			this->GeneralUVRegistrationMenuItem->DoubleClickEnabled = true;
			this->GeneralUVRegistrationMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->toolStripMenuItem5,
					this->UVGeneralRegistrationResolutionDrop, this->toolStripSeparator21, this->masterizeSinglesToolStripMenuItem, this->RegistrationXYIntsListFolderScanChck
			});
			this->GeneralUVRegistrationMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"GeneralUVRegistrationMenuItem.Image")));
			this->GeneralUVRegistrationMenuItem->Name = L"GeneralUVRegistrationMenuItem";
			this->GeneralUVRegistrationMenuItem->Size = System::Drawing::Size(256, 22);
			this->GeneralUVRegistrationMenuItem->Text = L"General Registration";
			this->GeneralUVRegistrationMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::GeneralUVRegistrationMenuItem_Click);
			// 
			// toolStripMenuItem5
			// 
			this->toolStripMenuItem5->Enabled = false;
			this->toolStripMenuItem5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
			this->toolStripMenuItem5->Size = System::Drawing::Size(325, 22);
			this->toolStripMenuItem5->Text = L"Registration Image Resolution";
			// 
			// UVGeneralRegistrationResolutionDrop
			// 
			this->UVGeneralRegistrationResolutionDrop->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->UVGeneralRegistrationResolutionDrop->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
			this->UVGeneralRegistrationResolutionDrop->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1", L"2", L"4" });
			this->UVGeneralRegistrationResolutionDrop->Name = L"UVGeneralRegistrationResolutionDrop";
			this->UVGeneralRegistrationResolutionDrop->Size = System::Drawing::Size(121, 23);
			// 
			// toolStripSeparator21
			// 
			this->toolStripSeparator21->Name = L"toolStripSeparator21";
			this->toolStripSeparator21->Size = System::Drawing::Size(322, 6);
			// 
			// masterizeSinglesToolStripMenuItem
			// 
			this->masterizeSinglesToolStripMenuItem->CheckOnClick = true;
			this->masterizeSinglesToolStripMenuItem->Name = L"masterizeSinglesToolStripMenuItem";
			this->masterizeSinglesToolStripMenuItem->Size = System::Drawing::Size(325, 22);
			this->masterizeSinglesToolStripMenuItem->Text = L"Masterize Singles";
			this->masterizeSinglesToolStripMenuItem->ToolTipText = L"Functions when registering batch containing MASTER files...will rename and move s"
				L"ingle filter instances as MASTER files.";
			this->masterizeSinglesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::masterizeSinglesToolStripMenuItem_Click);
			// 
			// RegistrationXYIntsListFolderScanChck
			// 
			this->RegistrationXYIntsListFolderScanChck->CheckOnClick = true;
			this->RegistrationXYIntsListFolderScanChck->Name = L"RegistrationXYIntsListFolderScanChck";
			this->RegistrationXYIntsListFolderScanChck->Size = System::Drawing::Size(325, 22);
			this->RegistrationXYIntsListFolderScanChck->Text = L"Folder Browse Scan for Most Recent XYInts Lists";
			this->RegistrationXYIntsListFolderScanChck->Click += gcnew System::EventHandler(this, &Form1::RegistrationXYIntsListFolderScanChck_Click);
			// 
			// UserDefinedShiftRotateMenuItem
			// 
			this->UserDefinedShiftRotateMenuItem->DoubleClickEnabled = true;
			this->UserDefinedShiftRotateMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(21) {
				this->toolStripSeparator8,
					this->LinearRotationChck, this->toolStripSeparator9, this->FlipHorizontalMenuItem, this->FlipVerticalMenuItem, this->UserRotationTxt,
					this->UserRotationXCenterTxt, this->UserRotationYCenterTxt, this->UserXShiftTxt, this->UserYShiftTxt, this->toolStripSeparator13,
					this->GeneralTransformChck, this->toolStripSeparator14, this->TransformCoefATxt, this->TransformCoefBTxt, this->TransformCoefCTxt,
					this->TransformCoefDTxt, this->TransformCenterXTxt, this->TransformCenterYTxt, this->TransformShiftXTxt, this->TransformShiftYTxt
			});
			this->UserDefinedShiftRotateMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UserDefinedShiftRotateMenuItem.Image")));
			this->UserDefinedShiftRotateMenuItem->Name = L"UserDefinedShiftRotateMenuItem";
			this->UserDefinedShiftRotateMenuItem->Size = System::Drawing::Size(256, 22);
			this->UserDefinedShiftRotateMenuItem->Text = L"User Defined:";
			this->UserDefinedShiftRotateMenuItem->ToolTipText = L"Operations are done in order.";
			this->UserDefinedShiftRotateMenuItem->DropDownOpened += gcnew System::EventHandler(this, &Form1::UserDefinedShiftRotateMenuItem_DropDownOpened);
			this->UserDefinedShiftRotateMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::UserDefinedShiftRotateMenuItem_DoubleClick);
			// 
			// toolStripSeparator8
			// 
			this->toolStripSeparator8->Name = L"toolStripSeparator8";
			this->toolStripSeparator8->Size = System::Drawing::Size(194, 6);
			// 
			// LinearRotationChck
			// 
			this->LinearRotationChck->CheckOnClick = true;
			this->LinearRotationChck->Name = L"LinearRotationChck";
			this->LinearRotationChck->Size = System::Drawing::Size(197, 22);
			this->LinearRotationChck->Text = L"Linear Rotation";
			this->LinearRotationChck->Click += gcnew System::EventHandler(this, &Form1::LinearRotationChck_Click);
			// 
			// toolStripSeparator9
			// 
			this->toolStripSeparator9->Name = L"toolStripSeparator9";
			this->toolStripSeparator9->Size = System::Drawing::Size(194, 6);
			// 
			// FlipHorizontalMenuItem
			// 
			this->FlipHorizontalMenuItem->CheckOnClick = true;
			this->FlipHorizontalMenuItem->Enabled = false;
			this->FlipHorizontalMenuItem->Name = L"FlipHorizontalMenuItem";
			this->FlipHorizontalMenuItem->Size = System::Drawing::Size(197, 22);
			this->FlipHorizontalMenuItem->Text = L"Horizontal Flip";
			this->FlipHorizontalMenuItem->Click += gcnew System::EventHandler(this, &Form1::FlipHorizontalMenuItem_Click);
			// 
			// FlipVerticalMenuItem
			// 
			this->FlipVerticalMenuItem->CheckOnClick = true;
			this->FlipVerticalMenuItem->Enabled = false;
			this->FlipVerticalMenuItem->Name = L"FlipVerticalMenuItem";
			this->FlipVerticalMenuItem->Size = System::Drawing::Size(197, 22);
			this->FlipVerticalMenuItem->Text = L"Vertical Flip";
			this->FlipVerticalMenuItem->Click += gcnew System::EventHandler(this, &Form1::FlipVerticalMenuItem_Click);
			// 
			// UserRotationTxt
			// 
			this->UserRotationTxt->BackColor = System::Drawing::Color::Violet;
			this->UserRotationTxt->Enabled = false;
			this->UserRotationTxt->Name = L"UserRotationTxt";
			this->UserRotationTxt->Size = System::Drawing::Size(100, 23);
			this->UserRotationTxt->Text = L"0";
			this->UserRotationTxt->ToolTipText = L"Rotation Angle (degrees)";
			this->UserRotationTxt->TextChanged += gcnew System::EventHandler(this, &Form1::UserRotationTxt_TextChanged);
			// 
			// UserRotationXCenterTxt
			// 
			this->UserRotationXCenterTxt->BackColor = System::Drawing::Color::Violet;
			this->UserRotationXCenterTxt->Enabled = false;
			this->UserRotationXCenterTxt->Name = L"UserRotationXCenterTxt";
			this->UserRotationXCenterTxt->Size = System::Drawing::Size(100, 23);
			this->UserRotationXCenterTxt->Text = L"0";
			this->UserRotationXCenterTxt->ToolTipText = L"Rotation Center-X (pixels)";
			this->UserRotationXCenterTxt->TextChanged += gcnew System::EventHandler(this, &Form1::UserRotationXTxt_TextChanged);
			// 
			// UserRotationYCenterTxt
			// 
			this->UserRotationYCenterTxt->BackColor = System::Drawing::Color::Violet;
			this->UserRotationYCenterTxt->Enabled = false;
			this->UserRotationYCenterTxt->Name = L"UserRotationYCenterTxt";
			this->UserRotationYCenterTxt->Size = System::Drawing::Size(100, 23);
			this->UserRotationYCenterTxt->Text = L"0";
			this->UserRotationYCenterTxt->ToolTipText = L"Rotation Center-Y (pixels)";
			this->UserRotationYCenterTxt->TextChanged += gcnew System::EventHandler(this, &Form1::UserRotationYTxt_TextChanged);
			// 
			// UserXShiftTxt
			// 
			this->UserXShiftTxt->BackColor = System::Drawing::Color::Violet;
			this->UserXShiftTxt->Enabled = false;
			this->UserXShiftTxt->Name = L"UserXShiftTxt";
			this->UserXShiftTxt->Size = System::Drawing::Size(100, 23);
			this->UserXShiftTxt->Text = L"0";
			this->UserXShiftTxt->ToolTipText = L"X-Shift (pixels)";
			this->UserXShiftTxt->TextChanged += gcnew System::EventHandler(this, &Form1::UserXShiftTxt_TextChanged);
			// 
			// UserYShiftTxt
			// 
			this->UserYShiftTxt->BackColor = System::Drawing::Color::Violet;
			this->UserYShiftTxt->Enabled = false;
			this->UserYShiftTxt->Name = L"UserYShiftTxt";
			this->UserYShiftTxt->Size = System::Drawing::Size(100, 23);
			this->UserYShiftTxt->Text = L"0";
			this->UserYShiftTxt->ToolTipText = L"Y-Shift (pixels)";
			this->UserYShiftTxt->TextChanged += gcnew System::EventHandler(this, &Form1::UserYShiftTxt_TextChanged);
			// 
			// toolStripSeparator13
			// 
			this->toolStripSeparator13->Name = L"toolStripSeparator13";
			this->toolStripSeparator13->Size = System::Drawing::Size(194, 6);
			// 
			// GeneralTransformChck
			// 
			this->GeneralTransformChck->CheckOnClick = true;
			this->GeneralTransformChck->Name = L"GeneralTransformChck";
			this->GeneralTransformChck->Size = System::Drawing::Size(197, 22);
			this->GeneralTransformChck->Text = L"General Transformation";
			this->GeneralTransformChck->Click += gcnew System::EventHandler(this, &Form1::GeneralTransformChck_Click);
			// 
			// toolStripSeparator14
			// 
			this->toolStripSeparator14->Name = L"toolStripSeparator14";
			this->toolStripSeparator14->Size = System::Drawing::Size(194, 6);
			// 
			// TransformCoefATxt
			// 
			this->TransformCoefATxt->BackColor = System::Drawing::Color::Violet;
			this->TransformCoefATxt->Enabled = false;
			this->TransformCoefATxt->Name = L"TransformCoefATxt";
			this->TransformCoefATxt->Size = System::Drawing::Size(100, 23);
			this->TransformCoefATxt->Text = L"0";
			this->TransformCoefATxt->ToolTipText = L"Transformation Coefficient A";
			this->TransformCoefATxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformCoefATxt_TextChanged);
			// 
			// TransformCoefBTxt
			// 
			this->TransformCoefBTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformCoefBTxt->Enabled = false;
			this->TransformCoefBTxt->Name = L"TransformCoefBTxt";
			this->TransformCoefBTxt->Size = System::Drawing::Size(100, 23);
			this->TransformCoefBTxt->Text = L"0";
			this->TransformCoefBTxt->ToolTipText = L"Transformation Coefficient B";
			this->TransformCoefBTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformCoefBTxt_TextChanged);
			// 
			// TransformCoefCTxt
			// 
			this->TransformCoefCTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformCoefCTxt->Enabled = false;
			this->TransformCoefCTxt->Name = L"TransformCoefCTxt";
			this->TransformCoefCTxt->Size = System::Drawing::Size(100, 23);
			this->TransformCoefCTxt->Text = L"0";
			this->TransformCoefCTxt->ToolTipText = L"Transformation Coefficient C";
			this->TransformCoefCTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformCoefCTxt_TextChanged);
			// 
			// TransformCoefDTxt
			// 
			this->TransformCoefDTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformCoefDTxt->Enabled = false;
			this->TransformCoefDTxt->Name = L"TransformCoefDTxt";
			this->TransformCoefDTxt->Size = System::Drawing::Size(100, 23);
			this->TransformCoefDTxt->Text = L"0";
			this->TransformCoefDTxt->ToolTipText = L"Transformation Coefficient D";
			this->TransformCoefDTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformCoefDTxt_TextChanged);
			// 
			// TransformCenterXTxt
			// 
			this->TransformCenterXTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformCenterXTxt->Enabled = false;
			this->TransformCenterXTxt->Name = L"TransformCenterXTxt";
			this->TransformCenterXTxt->Size = System::Drawing::Size(100, 23);
			this->TransformCenterXTxt->Text = L"0";
			this->TransformCenterXTxt->ToolTipText = L"Transformation Center X";
			this->TransformCenterXTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformCenterXTxt_TextChanged);
			// 
			// TransformCenterYTxt
			// 
			this->TransformCenterYTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformCenterYTxt->Enabled = false;
			this->TransformCenterYTxt->Name = L"TransformCenterYTxt";
			this->TransformCenterYTxt->Size = System::Drawing::Size(100, 23);
			this->TransformCenterYTxt->Text = L"0";
			this->TransformCenterYTxt->ToolTipText = L"Transformation Center Y";
			this->TransformCenterYTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformCenterYTxt_TextChanged);
			// 
			// TransformShiftXTxt
			// 
			this->TransformShiftXTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformShiftXTxt->Enabled = false;
			this->TransformShiftXTxt->Name = L"TransformShiftXTxt";
			this->TransformShiftXTxt->Size = System::Drawing::Size(100, 23);
			this->TransformShiftXTxt->Text = L"0";
			this->TransformShiftXTxt->ToolTipText = L"Transformation Shift X";
			this->TransformShiftXTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformShiftXTxt_TextChanged);
			// 
			// TransformShiftYTxt
			// 
			this->TransformShiftYTxt->BackColor = System::Drawing::Color::Violet;
			this->TransformShiftYTxt->Enabled = false;
			this->TransformShiftYTxt->Name = L"TransformShiftYTxt";
			this->TransformShiftYTxt->Size = System::Drawing::Size(100, 23);
			this->TransformShiftYTxt->Text = L"0";
			this->TransformShiftYTxt->ToolTipText = L"Transformation Shift Y";
			this->TransformShiftYTxt->TextChanged += gcnew System::EventHandler(this, &Form1::TransformShiftYTxt_TextChanged);
			// 
			// toolStripSeparator15
			// 
			this->toolStripSeparator15->Name = L"toolStripSeparator15";
			this->toolStripSeparator15->Size = System::Drawing::Size(253, 6);
			// 
			// UVCombineCentroidListsMenuItem
			// 
			this->UVCombineCentroidListsMenuItem->DoubleClickEnabled = true;
			this->UVCombineCentroidListsMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->UVDeleteMergeDirsChck,
					this->MergeXYIntsListFolderScanChck, this->UVAutoPSFPostMergeChck
			});
			this->UVCombineCentroidListsMenuItem->Name = L"UVCombineCentroidListsMenuItem";
			this->UVCombineCentroidListsMenuItem->Size = System::Drawing::Size(256, 22);
			this->UVCombineCentroidListsMenuItem->Text = L"Merge Centroid Lists";
			this->UVCombineCentroidListsMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::CombineUVCentroidListsMenuItem_Click);
			// 
			// UVDeleteMergeDirsChck
			// 
			this->UVDeleteMergeDirsChck->CheckOnClick = true;
			this->UVDeleteMergeDirsChck->Name = L"UVDeleteMergeDirsChck";
			this->UVDeleteMergeDirsChck->Size = System::Drawing::Size(329, 22);
			this->UVDeleteMergeDirsChck->Text = L"Delete Contributing Directories";
			this->UVDeleteMergeDirsChck->Visible = false;
			this->UVDeleteMergeDirsChck->Click += gcnew System::EventHandler(this, &Form1::UVDeleteMergeDirsChck_Click);
			// 
			// MergeXYIntsListFolderScanChck
			// 
			this->MergeXYIntsListFolderScanChck->CheckOnClick = true;
			this->MergeXYIntsListFolderScanChck->Name = L"MergeXYIntsListFolderScanChck";
			this->MergeXYIntsListFolderScanChck->Size = System::Drawing::Size(329, 22);
			this->MergeXYIntsListFolderScanChck->Text = L"Folder Browse Scan for Most Recent XYInts Lists";
			this->MergeXYIntsListFolderScanChck->Click += gcnew System::EventHandler(this, &Form1::MergeXYIntsListFolderScanChck_Click);
			// 
			// UVAutoPSFPostMergeChck
			// 
			this->UVAutoPSFPostMergeChck->CheckOnClick = true;
			this->UVAutoPSFPostMergeChck->Name = L"UVAutoPSFPostMergeChck";
			this->UVAutoPSFPostMergeChck->Size = System::Drawing::Size(329, 22);
			this->UVAutoPSFPostMergeChck->Text = L"Auto Proceed with PSF Optimization Post Merge";
			this->UVAutoPSFPostMergeChck->Click += gcnew System::EventHandler(this, &Form1::UVAutoPSFPostMergeChck_Click);
			// 
			// UVLoadAllMerged
			// 
			this->UVLoadAllMerged->Name = L"UVLoadAllMerged";
			this->UVLoadAllMerged->Size = System::Drawing::Size(256, 22);
			this->UVLoadAllMerged->Text = L"Load All Recent Merged Images";
			this->UVLoadAllMerged->Click += gcnew System::EventHandler(this, &Form1::UVLoadAllMerged_Click);
			// 
			// toolStripSeparator20
			// 
			this->toolStripSeparator20->Name = L"toolStripSeparator20";
			this->toolStripSeparator20->Size = System::Drawing::Size(253, 6);
			// 
			// UVNUVToFUVFrameMenuItem
			// 
			this->UVNUVToFUVFrameMenuItem->Name = L"UVNUVToFUVFrameMenuItem";
			this->UVNUVToFUVFrameMenuItem->Size = System::Drawing::Size(256, 22);
			this->UVNUVToFUVFrameMenuItem->Text = L"Transform NUV to FUV Frame";
			this->UVNUVToFUVFrameMenuItem->Visible = false;
			this->UVNUVToFUVFrameMenuItem->Click += gcnew System::EventHandler(this, &Form1::NUVToFUVFrameMenuItem_Click);
			// 
			// DeRotateViaWCSBtn
			// 
			this->DeRotateViaWCSBtn->DoubleClickEnabled = true;
			this->DeRotateViaWCSBtn->Name = L"DeRotateViaWCSBtn";
			this->DeRotateViaWCSBtn->Size = System::Drawing::Size(256, 22);
			this->DeRotateViaWCSBtn->Text = L"De-Rotate Loaded Images via WCS";
			this->DeRotateViaWCSBtn->Click += gcnew System::EventHandler(this, &Form1::DeRotateViaWCS_Click);
			// 
			// invertWCSToolStripMenuItem
			// 
			this->invertWCSToolStripMenuItem->Name = L"invertWCSToolStripMenuItem";
			this->invertWCSToolStripMenuItem->Size = System::Drawing::Size(256, 22);
			this->invertWCSToolStripMenuItem->Text = L"Invert WCS";
			this->invertWCSToolStripMenuItem->ToolTipText = L"Needed for other programs which invert the image display relative to CCDLAB displ"
				L"ay";
			this->invertWCSToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::invertWCSToolStripMenuItem_Click);
			// 
			// DeSaturateROICountsMenuItem
			// 
			this->DeSaturateROICountsMenuItem->DoubleClickEnabled = true;
			this->DeSaturateROICountsMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->CorrectBackgroundCountsChck,
					this->BackgroundCountsPixelFrameTxt
			});
			this->DeSaturateROICountsMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DeSaturateROICountsMenuItem.Image")));
			this->DeSaturateROICountsMenuItem->Name = L"DeSaturateROICountsMenuItem";
			this->DeSaturateROICountsMenuItem->Size = System::Drawing::Size(274, 22);
			this->DeSaturateROICountsMenuItem->Text = L"DeSaturate ROI Counts";
			this->DeSaturateROICountsMenuItem->DoubleClick += gcnew System::EventHandler(this, &Form1::DeSaturateROICountsMenuItem_DoubleClick);
			// 
			// CorrectBackgroundCountsChck
			// 
			this->CorrectBackgroundCountsChck->CheckOnClick = true;
			this->CorrectBackgroundCountsChck->Name = L"CorrectBackgroundCountsChck";
			this->CorrectBackgroundCountsChck->Size = System::Drawing::Size(180, 22);
			this->CorrectBackgroundCountsChck->Text = L"Correct Background";
			this->CorrectBackgroundCountsChck->Click += gcnew System::EventHandler(this, &Form1::CorrectBackgroundCountsChck_Click);
			// 
			// BackgroundCountsPixelFrameTxt
			// 
			this->BackgroundCountsPixelFrameTxt->BackColor = System::Drawing::Color::Violet;
			this->BackgroundCountsPixelFrameTxt->Enabled = false;
			this->BackgroundCountsPixelFrameTxt->Name = L"BackgroundCountsPixelFrameTxt";
			this->BackgroundCountsPixelFrameTxt->Size = System::Drawing::Size(100, 23);
			this->BackgroundCountsPixelFrameTxt->Text = L"0";
			this->BackgroundCountsPixelFrameTxt->ToolTipText = L"Total counts/pixel";
			this->BackgroundCountsPixelFrameTxt->TextChanged += gcnew System::EventHandler(this, &Form1::BackgroundCountsPixelFrameTxt_TextChanged);
			// 
			// ExtractROICentroidListMenuItem
			// 
			this->ExtractROICentroidListMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ExtractROICentroidListMenuItem.Image")));
			this->ExtractROICentroidListMenuItem->Name = L"ExtractROICentroidListMenuItem";
			this->ExtractROICentroidListMenuItem->Size = System::Drawing::Size(274, 22);
			this->ExtractROICentroidListMenuItem->Text = L"Extract ROI Centroid List";
			this->ExtractROICentroidListMenuItem->Click += gcnew System::EventHandler(this, &Form1::ExtractROICentroidListMenuItem_Click);
			// 
			// UVFinalizeScienceBtn
			// 
			this->UVFinalizeScienceBtn->DoubleClickEnabled = true;
			this->UVFinalizeScienceBtn->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->UVFinalizeIncludeExpMapChck,
					this->UVFinalizeIncludeTablesChck, this->UVFinalizeDeleteIntrmdtChck, this->UVFinalizeMoveOrCopyZipChck
			});
			this->UVFinalizeScienceBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"UVFinalizeScienceBtn.Image")));
			this->UVFinalizeScienceBtn->Name = L"UVFinalizeScienceBtn";
			this->UVFinalizeScienceBtn->Size = System::Drawing::Size(274, 22);
			this->UVFinalizeScienceBtn->Text = L"Finalize Science Products";
			this->UVFinalizeScienceBtn->DoubleClick += gcnew System::EventHandler(this, &Form1::UVFinalizeScienceBtn_DoubleClick);
			// 
			// UVFinalizeIncludeExpMapChck
			// 
			this->UVFinalizeIncludeExpMapChck->CheckOnClick = true;
			this->UVFinalizeIncludeExpMapChck->Name = L"UVFinalizeIncludeExpMapChck";
			this->UVFinalizeIncludeExpMapChck->Size = System::Drawing::Size(238, 22);
			this->UVFinalizeIncludeExpMapChck->Text = L"Include Exposure Maps";
			this->UVFinalizeIncludeExpMapChck->Click += gcnew System::EventHandler(this, &Form1::UVFinalizeIncludeExpMapChck_Click);
			// 
			// UVFinalizeIncludeTablesChck
			// 
			this->UVFinalizeIncludeTablesChck->CheckOnClick = true;
			this->UVFinalizeIncludeTablesChck->Name = L"UVFinalizeIncludeTablesChck";
			this->UVFinalizeIncludeTablesChck->Size = System::Drawing::Size(238, 22);
			this->UVFinalizeIncludeTablesChck->Text = L"Include Centroid FITS BinTables";
			this->UVFinalizeIncludeTablesChck->Click += gcnew System::EventHandler(this, &Form1::UVFinalizeIncludeTablesChck_Click);
			// 
			// UVFinalizeDeleteIntrmdtChck
			// 
			this->UVFinalizeDeleteIntrmdtChck->CheckOnClick = true;
			this->UVFinalizeDeleteIntrmdtChck->Name = L"UVFinalizeDeleteIntrmdtChck";
			this->UVFinalizeDeleteIntrmdtChck->Size = System::Drawing::Size(238, 22);
			this->UVFinalizeDeleteIntrmdtChck->Text = L"Delete Intermediate Directories";
			this->UVFinalizeDeleteIntrmdtChck->Click += gcnew System::EventHandler(this, &Form1::UVFinalizeDeleteIntrmdtChck_Click);
			// 
			// UVFinalizeMoveOrCopyZipChck
			// 
			this->UVFinalizeMoveOrCopyZipChck->CheckOnClick = true;
			this->UVFinalizeMoveOrCopyZipChck->Name = L"UVFinalizeMoveOrCopyZipChck";
			this->UVFinalizeMoveOrCopyZipChck->Size = System::Drawing::Size(238, 22);
			this->UVFinalizeMoveOrCopyZipChck->Text = L"Move Products to ZIP Archive";
			this->UVFinalizeMoveOrCopyZipChck->Click += gcnew System::EventHandler(this, &Form1::UVFinalizeMoveOrCopyZipChck_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// UVMovieTimer
			// 
			this->UVMovieTimer->Interval = 200;
			this->UVMovieTimer->Tick += gcnew System::EventHandler(this, &Form1::UVMovieTimer_Tick);
			// 
			// UVOpenDirDlg
			// 
			this->UVOpenDirDlg->Description = L"Select Directory of *.raw Files";
			this->UVOpenDirDlg->ShowNewFolderButton = false;
			// 
			// UVOpenRawDlg
			// 
			this->UVOpenRawDlg->Filter = L"UVIT File (*.raw)|*.raw|Fits File (*.fts; *.fit; *.fits)|*.fts; *.fit; *.fits";
			this->UVOpenRawDlg->Multiselect = true;
			this->UVOpenRawDlg->RestoreDirectory = true;
			this->UVOpenRawDlg->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::UVOpenRawDlg_FileOk);
			// 
			// UVSaveCentroidDlg
			// 
			this->UVSaveCentroidDlg->Filter = L"UVIT Centroid File (*.ucf)|*.ucf";
			this->UVSaveCentroidDlg->RestoreDirectory = true;
			this->UVSaveCentroidDlg->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::UVSaveCentroidDlg_FileOk);
			// 
			// CCDLABTaskBarIcon
			// 
			this->CCDLABTaskBarIcon->ContextMenuStrip = this->TaskBarCntxt;
			this->CCDLABTaskBarIcon->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"CCDLABTaskBarIcon.Icon")));
			this->CCDLABTaskBarIcon->Text = L"CCDLAB";
			this->CCDLABTaskBarIcon->Visible = true;
			// 
			// TaskBarCntxt
			// 
			this->TaskBarCntxt->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->TCQuit });
			this->TaskBarCntxt->Name = L"TaskBarCntxtMenu";
			this->TaskBarCntxt->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->TaskBarCntxt->ShowImageMargin = false;
			this->TaskBarCntxt->Size = System::Drawing::Size(129, 26);
			this->TaskBarCntxt->Click += gcnew System::EventHandler(this, &Form1::TaskBarCntxtMenu_Click);
			this->TaskBarCntxt->MouseEnter += gcnew System::EventHandler(this, &Form1::TaskBarCntxtMenu_MouseEnter);
			this->TaskBarCntxt->MouseLeave += gcnew System::EventHandler(this, &Form1::TaskBarCntxtMenu_MouseLeave);
			// 
			// TCQuit
			// 
			this->TCQuit->Name = L"TCQuit";
			this->TCQuit->Size = System::Drawing::Size(128, 22);
			this->TCQuit->Text = L"SELFDESTRUCT";
			// 
			// TBDestructTimer
			// 
			this->TBDestructTimer->Interval = 200;
			this->TBDestructTimer->Tick += gcnew System::EventHandler(this, &Form1::TBDestructTimer_Tick);
			// 
			// UVOpenUCFDlg
			// 
			this->UVOpenUCFDlg->Filter = L"UVIT Centroid File (*.ucf)|*.ucf";
			this->UVOpenUCFDlg->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::UVOpenUCFDlg_FileOk);
			// 
			// ImageOpsWrkr
			// 
			this->ImageOpsWrkr->WorkerReportsProgress = true;
			this->ImageOpsWrkr->WorkerSupportsCancellation = true;
			this->ImageOpsWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ImageOpsWrkr_DoWork);
			this->ImageOpsWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ImageOpsWrkr_ProgressChanged);
			this->ImageOpsWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ImageOpsWrkr_RunWorkerCompleted);
			// 
			// UVCentroidWrkr
			// 
			this->UVCentroidWrkr->WorkerReportsProgress = true;
			this->UVCentroidWrkr->WorkerSupportsCancellation = true;
			this->UVCentroidWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::UVCentroidWrkr_DoWork);
			this->UVCentroidWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::UVCentroidWrkr_ProgressChanged);
			this->UVCentroidWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::UVCentroidWrkr_RunWorkerCompleted);
			// 
			// SurfWrkr
			// 
			this->SurfWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::SurfWrkr_DoWork);
			this->SurfWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::SurfWrkr_RunWorkerCompleted);
			// 
			// FormLoadBGW
			// 
			this->FormLoadBGW->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::FormLoadBGW_DoWork);
			// 
			// UVHistWrkr
			// 
			this->UVHistWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::UVHistWrkr_DoWork);
			this->UVHistWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::UVHistWrkr_RunWorkerCompleted);
			// 
			// ImageCntxtViewWrkr
			// 
			this->ImageCntxtViewWrkr->WorkerReportsProgress = true;
			this->ImageCntxtViewWrkr->WorkerSupportsCancellation = true;
			this->ImageCntxtViewWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ImageCntxtViewWrkr_DoWork);
			this->ImageCntxtViewWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ImageCntxtViewWrkr_ProgressChanged);
			this->ImageCntxtViewWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ImageCntxtViewWrkr_RunWorkerCompleted);
			// 
			// PSEFitWrkr
			// 
			this->PSEFitWrkr->WorkerReportsProgress = true;
			this->PSEFitWrkr->WorkerSupportsCancellation = true;
			this->PSEFitWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::PSEFitWrkr_DoWork);
			this->PSEFitWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::PSEFitWrkr_ProgressChanged);
			this->PSEFitWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::PSEFitWrkr_RunWorkerCompleted);
			// 
			// BatchBGWrkr
			// 
			this->BatchBGWrkr->WorkerReportsProgress = true;
			this->BatchBGWrkr->WorkerSupportsCancellation = true;
			this->BatchBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::BatchBGWrkr_DoWork);
			this->BatchBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::BatchBGWrkr_ProgressChanged);
			this->BatchBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::BatchBGWrkr_RunWorkerCompleted);
			// 
			// ViewImageTog
			// 
			this->ViewImageTog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ViewImageTog->Appearance = System::Windows::Forms::Appearance::Button;
			this->ViewImageTog->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ViewImageTog->Checked = true;
			this->ViewImageTog->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ViewImageTog->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ViewImageTog->Location = System::Drawing::Point(707, 24);
			this->ViewImageTog->Name = L"ViewImageTog";
			this->ViewImageTog->Size = System::Drawing::Size(70, 17);
			this->ViewImageTog->TabIndex = 47;
			this->ViewImageTog->Text = L"IMAGE";
			this->ViewImageTog->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->ViewImageTog->UseVisualStyleBackColor = true;
			this->ViewImageTog->Click += gcnew System::EventHandler(this, &Form1::ViewImageTog_Click);
			// 
			// ViewSpectrumTog
			// 
			this->ViewSpectrumTog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ViewSpectrumTog->Appearance = System::Windows::Forms::Appearance::Button;
			this->ViewSpectrumTog->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ViewSpectrumTog->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ViewSpectrumTog->Location = System::Drawing::Point(777, 24);
			this->ViewSpectrumTog->Name = L"ViewSpectrumTog";
			this->ViewSpectrumTog->Size = System::Drawing::Size(70, 17);
			this->ViewSpectrumTog->TabIndex = 48;
			this->ViewSpectrumTog->Text = L"Spectrum";
			this->ViewSpectrumTog->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->ViewSpectrumTog->UseVisualStyleBackColor = true;
			this->ViewSpectrumTog->Click += gcnew System::EventHandler(this, &Form1::ViewSpectrumTog_Click);
			// 
			// InvQuitBtn
			// 
			this->InvQuitBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->InvQuitBtn->Location = System::Drawing::Point(59, 98);
			this->InvQuitBtn->Name = L"InvQuitBtn";
			this->InvQuitBtn->Size = System::Drawing::Size(75, 45);
			this->InvQuitBtn->TabIndex = 53;
			this->InvQuitBtn->Text = L"InvQuitBtn";
			this->InvQuitBtn->UseVisualStyleBackColor = true;
			this->InvQuitBtn->Click += gcnew System::EventHandler(this, &Form1::FMQuit_Click);
			// 
			// WriteImageSetBGWrkr
			// 
			this->WriteImageSetBGWrkr->WorkerReportsProgress = true;
			this->WriteImageSetBGWrkr->WorkerSupportsCancellation = true;
			this->WriteImageSetBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::WriteImageSetBGWrkr_DoWork);
			this->WriteImageSetBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::WriteImageSetBGWrkr_ProgressChanged);
			this->WriteImageSetBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::WriteImageSetBGWrkr_RunWorkerCompleted);
			// 
			// BatchMovieTimer
			// 
			this->BatchMovieTimer->Interval = 200;
			this->BatchMovieTimer->Tick += gcnew System::EventHandler(this, &Form1::BatchMovieTimer_Tick);
			// 
			// ParcelUVCentroidWrkr
			// 
			this->ParcelUVCentroidWrkr->WorkerReportsProgress = true;
			this->ParcelUVCentroidWrkr->WorkerSupportsCancellation = true;
			this->ParcelUVCentroidWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ParcelUVCentroidWrkr_DoWork);
			this->ParcelUVCentroidWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ParcelUVCentroidWrkr_ProgressChanged);
			this->ParcelUVCentroidWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ParcelUVCentroidWrkr_RunWorkerCompleted);
			// 
			// label40
			// 
			this->label40->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label40->BackColor = System::Drawing::Color::DodgerBlue;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label40->Location = System::Drawing::Point(35, 853);
			this->label40->Margin = System::Windows::Forms::Padding(0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(21, 15);
			this->label40->TabIndex = 54;
			this->label40->Text = L"X:";
			this->label40->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label41
			// 
			this->label41->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label41->BackColor = System::Drawing::Color::DodgerBlue;
			this->label41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label41->Location = System::Drawing::Point(158, 853);
			this->label41->Margin = System::Windows::Forms::Padding(0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(20, 15);
			this->label41->TabIndex = 55;
			this->label41->Text = L"Y:";
			this->label41->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// DriftFromPCListWrkr
			// 
			this->DriftFromPCListWrkr->WorkerReportsProgress = true;
			this->DriftFromPCListWrkr->WorkerSupportsCancellation = true;
			this->DriftFromPCListWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::DriftFromPCListWrkr_DoWork);
			this->DriftFromPCListWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::DriftFromPCListWrkr_ProgressChanged);
			this->DriftFromPCListWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::DriftFromPCListWrkr_RunWorkerCompleted);
			// 
			// DriftFromINTWrkr
			// 
			this->DriftFromINTWrkr->WorkerReportsProgress = true;
			this->DriftFromINTWrkr->WorkerSupportsCancellation = true;
			this->DriftFromINTWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::DriftFromINTWrkr_DoWork);
			this->DriftFromINTWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::DriftFromINTWrkr_ProgressChanged);
			this->DriftFromINTWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::DriftFromINTWrkr_RunWorkerCompleted);
			// 
			// Chart1
			// 
			this->Chart1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea2->AxisX->MajorGrid->Enabled = false;
			chartArea2->AxisY->MajorGrid->Enabled = false;
			chartArea2->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea2->Name = L"ChartArea1";
			this->Chart1->ChartAreas->Add(chartArea2);
			this->Chart1->Location = System::Drawing::Point(35, 41);
			this->Chart1->Name = L"Chart1";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series2->Name = L"Series1";
			this->Chart1->Series->Add(series2);
			this->Chart1->Size = System::Drawing::Size(812, 812);
			this->Chart1->TabIndex = 56;
			this->Chart1->Text = L"chart1";
			this->Chart1->Visible = false;
			// 
			// ManRegWrkr
			// 
			this->ManRegWrkr->WorkerReportsProgress = true;
			this->ManRegWrkr->WorkerSupportsCancellation = true;
			this->ManRegWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ManRegWrkr_DoWork);
			this->ManRegWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ManRegWrkr_ProgressChanged);
			this->ManRegWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ManRegWrkr_RunWorkerCompleted);
			// 
			// INTAtoINTAapplyDriftWrkr
			// 
			this->INTAtoINTAapplyDriftWrkr->WorkerReportsProgress = true;
			this->INTAtoINTAapplyDriftWrkr->WorkerSupportsCancellation = true;
			this->INTAtoINTAapplyDriftWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::INTAtoINTAapplyDriftWrkr_DoWork);
			this->INTAtoINTAapplyDriftWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::INTAtoINTAapplyDriftWrkr_ProgressChanged);
			this->INTAtoINTAapplyDriftWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::INTAtoINTAapplyDriftWrkr_RunWorkerCompleted);
			// 
			// DigestL1Wrkr
			// 
			this->DigestL1Wrkr->WorkerReportsProgress = true;
			this->DigestL1Wrkr->WorkerSupportsCancellation = true;
			this->DigestL1Wrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::DigestL1Wrkr_DoWork);
			this->DigestL1Wrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::DigestL1Wrkr_ProgressChanged);
			this->DigestL1Wrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::DigestL1Wrkr_RunWorkerCompleted);
			// 
			// DiscardL1DuplicateWrkr
			// 
			this->DiscardL1DuplicateWrkr->WorkerReportsProgress = true;
			this->DiscardL1DuplicateWrkr->WorkerSupportsCancellation = true;
			this->DiscardL1DuplicateWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::DiscardL1DuplicateWrkr_DoWork);
			this->DiscardL1DuplicateWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::DiscardL1DuplicateWrkr_ProgressChanged);
			this->DiscardL1DuplicateWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::DiscardL1DuplicateWrkr_RunWorkerCompleted);
			// 
			// ConvertUVCentroidListToImgWrkr
			// 
			this->ConvertUVCentroidListToImgWrkr->WorkerReportsProgress = true;
			this->ConvertUVCentroidListToImgWrkr->WorkerSupportsCancellation = true;
			this->ConvertUVCentroidListToImgWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ConvertUVCentroidListToImgWrkr_DoWork);
			this->ConvertUVCentroidListToImgWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ConvertUVCentroidListToImgWrkr_ProgressChanged);
			this->ConvertUVCentroidListToImgWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ConvertUVCentroidListToImgWrkr_RunWorkerCompleted);
			// 
			// RegistrationUVCentroidWrkr
			// 
			this->RegistrationUVCentroidWrkr->WorkerReportsProgress = true;
			this->RegistrationUVCentroidWrkr->WorkerSupportsCancellation = true;
			this->RegistrationUVCentroidWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::RegistrationUVCentroidWrkr_DoWork);
			this->RegistrationUVCentroidWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::RegistrationUVCentroidWrkr_ProgressChanged);
			this->RegistrationUVCentroidWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::RegistrationUVCentroidWrkr_RunWorkerCompleted);
			// 
			// MergeCentroidListsWrkr
			// 
			this->MergeCentroidListsWrkr->WorkerReportsProgress = true;
			this->MergeCentroidListsWrkr->WorkerSupportsCancellation = true;
			this->MergeCentroidListsWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::MergeCentroidListsWrkr_DoWork);
			this->MergeCentroidListsWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::MergeCentroidListsWrkr_ProgressChanged);
			this->MergeCentroidListsWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::MergeCentroidListsWrkr_RunWorkerCompleted);
			// 
			// RotationUVCentroidWrkr
			// 
			this->RotationUVCentroidWrkr->WorkerReportsProgress = true;
			this->RotationUVCentroidWrkr->WorkerSupportsCancellation = true;
			this->RotationUVCentroidWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::RotationUVCentroidWrkr_DoWork);
			this->RotationUVCentroidWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::RotationUVCentroidWrkr_ProgressChanged);
			this->RotationUVCentroidWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::RotationUVCentroidWrkr_RunWorkerCompleted);
			// 
			// DirectoryLabel
			// 
			this->DirectoryLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->DirectoryLabel->AutoSize = true;
			this->DirectoryLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DirectoryLabel->Location = System::Drawing::Point(403, 856);
			this->DirectoryLabel->Name = L"DirectoryLabel";
			this->DirectoryLabel->Size = System::Drawing::Size(26, 13);
			this->DirectoryLabel->TabIndex = 57;
			this->DirectoryLabel->Text = L"File:";
			this->DirectoryLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// DriftNUVtoFUVBGWrkr
			// 
			this->DriftNUVtoFUVBGWrkr->WorkerReportsProgress = true;
			this->DriftNUVtoFUVBGWrkr->WorkerSupportsCancellation = true;
			this->DriftNUVtoFUVBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::DriftNUVtoFUVBGWrkr_DoWork);
			this->DriftNUVtoFUVBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::DriftNUVtoFUVBGWrkr_ProgressChanged);
			this->DriftNUVtoFUVBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::DriftNUVtoFUVBGWrkr_RunWorkerCompleted);
			// 
			// SIZECntxtBGWrkr
			// 
			this->SIZECntxtBGWrkr->WorkerReportsProgress = true;
			this->SIZECntxtBGWrkr->WorkerSupportsCancellation = true;
			this->SIZECntxtBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::SIZECntxtBGWrkr_DoWork);
			this->SIZECntxtBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::SIZECntxtBGWrkr_ProgressChanged);
			this->SIZECntxtBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::SIZECntxtBGWrkr_RunWorkerCompleted);
			// 
			// ExtractL1ArchiveBGWrkr
			// 
			this->ExtractL1ArchiveBGWrkr->WorkerReportsProgress = true;
			this->ExtractL1ArchiveBGWrkr->WorkerSupportsCancellation = true;
			this->ExtractL1ArchiveBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ExtractL1ArchiveBGWrkr_DoWork);
			this->ExtractL1ArchiveBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ExtractL1ArchiveBGWrkr_ProgressChanged);
			this->ExtractL1ArchiveBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ExtractL1ArchiveBGWrkr_RunWorkerCompleted);
			// 
			// ApplyDriftListWrkr
			// 
			this->ApplyDriftListWrkr->WorkerReportsProgress = true;
			this->ApplyDriftListWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ApplyDriftListWrkr_DoWork);
			this->ApplyDriftListWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::ApplyDriftListWrkr_ProgressChanged);
			this->ApplyDriftListWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::ApplyDriftListWrkr_RunWorkerCompleted);
			// 
			// CleanVISBGWrkr
			// 
			this->CleanVISBGWrkr->WorkerReportsProgress = true;
			this->CleanVISBGWrkr->WorkerSupportsCancellation = true;
			this->CleanVISBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::CleanVISBGWrkr_DoWork);
			this->CleanVISBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::CleanVISBGWrkr_ProgressChanged);
			this->CleanVISBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::CleanVISBGWrkr_RunWorkerCompleted);
			// 
			// WCSAutoBGWrkr
			// 
			this->WCSAutoBGWrkr->WorkerReportsProgress = true;
			this->WCSAutoBGWrkr->WorkerSupportsCancellation = true;
			this->WCSAutoBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::WCSAutoBGWrkr_DoWork);
			this->WCSAutoBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::WCSAutoBGWrkr_ProgressChanged);
			this->WCSAutoBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::WCSAutoBGWrkr_RunWorkerCompleted);
			// 
			// TEST_TEXT_BOX
			// 
			this->TEST_TEXT_BOX->Location = System::Drawing::Point(297, 303);
			this->TEST_TEXT_BOX->Name = L"TEST_TEXT_BOX";
			this->TEST_TEXT_BOX->Size = System::Drawing::Size(100, 20);
			this->TEST_TEXT_BOX->TabIndex = 58;
			this->TEST_TEXT_BOX->TextChanged += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_TextChanged);
			this->TEST_TEXT_BOX->MouseEnter += gcnew System::EventHandler(this, &Form1::TEST_TEXT_BOX_MouseEnter);
			// 
			// DriftFromPCPSTrackBGWrkr
			// 
			this->DriftFromPCPSTrackBGWrkr->WorkerReportsProgress = true;
			this->DriftFromPCPSTrackBGWrkr->WorkerSupportsCancellation = true;
			this->DriftFromPCPSTrackBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::DriftFromPCPSTrackBGWrkr_DoWork);
			this->DriftFromPCPSTrackBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::DriftFromPCPSTrackBGWrkr_ProgressChanged);
			this->DriftFromPCPSTrackBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::DriftFromPCPSTrackBGWrkr_RunWorkerCompleted);
			// 
			// UVFinalizeBGWrkr
			// 
			this->UVFinalizeBGWrkr->WorkerReportsProgress = true;
			this->UVFinalizeBGWrkr->WorkerSupportsCancellation = true;
			this->UVFinalizeBGWrkr->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::UVFinalizeBGWrkr_DoWork);
			this->UVFinalizeBGWrkr->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::UVFinalizeBGWrkr_ProgressChanged);
			this->UVFinalizeBGWrkr->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::UVFinalizeBGWrkr_RunWorkerCompleted);
			// 
			// PSEDropContextPlotAll
			// 
			this->PSEDropContextPlotAll->Name = L"PSEDropContextPlotAll";
			this->PSEDropContextPlotAll->Size = System::Drawing::Size(180, 22);
			this->PSEDropContextPlotAll->Text = L"Plot All";
			this->PSEDropContextPlotAll->Click += gcnew System::EventHandler(this, &Form1::PSEDropContextPlotAll_Click);
			// 
			// Form1
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Application;
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::Gainsboro;
			this->CancelButton = this->InvQuitBtn;
			this->ClientSize = System::Drawing::Size(1424, 888);
			this->Controls->Add(this->SubImageWindow);
			this->Controls->Add(this->DirectoryLabel);
			this->Controls->Add(this->label41);
			this->Controls->Add(this->XPositionTxt);
			this->Controls->Add(this->label40);
			this->Controls->Add(this->ViewSpectrumTog);
			this->Controls->Add(this->ViewImageTog);
			this->Controls->Add(this->ViewHeaderBtn);
			this->Controls->Add(this->BatchViewPanel);
			this->Controls->Add(this->MainMenu);
			this->Controls->Add(this->ContrastPanel);
			this->Controls->Add(this->ProgressBar);
			this->Controls->Add(this->ToolBar);
			this->Controls->Add(this->FileInfoPanel);
			this->Controls->Add(this->XYImageValueTxt);
			this->Controls->Add(this->SubImagePanel);
			this->Controls->Add(this->SubImageSlideX);
			this->Controls->Add(this->SubImageSlideY);
			this->Controls->Add(this->MainTab);
			this->Controls->Add(this->YPositionTxt);
			this->Controls->Add(this->HeaderKeyTxt);
			this->Controls->Add(this->SubImageBtn);
			this->Controls->Add(this->HeaderKeyValTxt);
			this->Controls->Add(this->HeaderKeyComTxt);
			this->Controls->Add(this->Chart1);
			this->Controls->Add(this->ImageWindow);
			this->Controls->Add(this->InvQuitBtn);
			this->Controls->Add(this->TEST_TEXT_BOX);
			this->DoubleBuffered = true;
			this->HelpButton = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->MainMenu;
			this->MinimumSize = System::Drawing::Size(200, 200);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CCDLAB";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->ImageWindowCntxt->ResumeLayout(false);
			this->ImageFingerPointContext->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HalfWidthXUpD))->EndInit();
			this->SubImagePanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HalfWidthYUpD))->EndInit();
			this->StatsContxt->ResumeLayout(false);
			this->FileInfoPanel->ResumeLayout(false);
			this->SIZECntxtMenu->ResumeLayout(false);
			this->FileDirectoryTxtContextMenu->ResumeLayout(false);
			this->ContrastPanel->ResumeLayout(false);
			this->ContrastPanel->PerformLayout();
			this->ContrastModePanel->ResumeLayout(false);
			this->ContrastModePanel->PerformLayout();
			this->ScanBtnContext->ResumeLayout(false);
			this->ScanBtnContext->PerformLayout();
			this->BatchViewPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BlinkTime))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubImageWindow))->EndInit();
			this->SubImageCntxt->ResumeLayout(false);
			this->ToolBar->ResumeLayout(false);
			this->ToolBar->PerformLayout();
			this->PSETab->ResumeLayout(false);
			this->ROIOnlyPnl->ResumeLayout(false);
			this->SubImgROITab->ResumeLayout(false);
			this->ROIFitTab->ResumeLayout(false);
			this->ROIFitTab->PerformLayout();
			this->ROICOGTab->ResumeLayout(false);
			this->ROICOGTab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->COGIgnoreNPtsUpD))->EndInit();
			this->PSEFitResultsCntxt->ResumeLayout(false);
			this->FindSourcesPnl->ResumeLayout(false);
			this->FindSourcesPnl->PerformLayout();
			this->PSEDropContextMenu->ResumeLayout(false);
			this->DrawROIContextMenu->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSESaturationUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSESeparationUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEKernelRadUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEKernelMinUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEKernelMaxUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEPixelMaxUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PSEPixelMinUpD))->EndInit();
			this->RotateBtnCntxt->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotateAngleUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NShiftHorzUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NShiftVertUpD))->EndInit();
			this->MainTab->ResumeLayout(false);
			this->ProcessingTab->ResumeLayout(false);
			this->ImageBatchRedxnPnl->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ManRegTrkHWUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ManRegSrcHWUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ScmTxt))->EndInit();
			this->ImageCorrxnPnl->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XBinUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YBinUpD))->EndInit();
			this->panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImageOpFilterWidthUpD))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->ImageOpsPnl->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->BatchTab->ResumeLayout(false);
			this->BatchTab->PerformLayout();
			this->BatchListViewPanel->ResumeLayout(false);
			this->BatchListViewPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchMovieSkipUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchBlinkTime))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchGoToUpD))->EndInit();
			this->BatchOperationTab->ResumeLayout(false);
			this->BatchSetTab->ResumeLayout(false);
			this->BatchSetTab->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->BatchIndividualTab->ResumeLayout(false);
			this->BatchIndividualTab->PerformLayout();
			this->BatchStackingTab->ResumeLayout(false);
			this->BatchStackingTab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StackUpD))->EndInit();
			this->BatchRunningTab->ResumeLayout(false);
			this->BatchRunningTab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BatchRunningNumUpD))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->BatchSubImagePanel->ResumeLayout(false);
			this->BatchSubImagePanel->PerformLayout();
			this->UVITTab->ResumeLayout(false);
			this->UVITTab->PerformLayout();
			this->UVAnalysisPanel->ResumeLayout(false);
			this->UVAnalysisPanel->PerformLayout();
			this->CentroidingPanel->ResumeLayout(false);
			this->CentroidingPanel->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVBGOffset))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVCornerThreshUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVBackGroundUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVShapeMaxThresh))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVShapeMinThresh))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVPixelMaxThresh))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVPixelMinThresh))->EndInit();
			this->UVAlgorithmCntxt->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVPrecisionUpD))->EndInit();
			this->UVBatchViewPanel->ResumeLayout(false);
			this->UVBatchViewPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVMovieSkipUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVBlinkTimeUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UVGoToUpD))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImageWindow))->EndInit();
			this->HeaderCntxt->ResumeLayout(false);
			this->MainMenu->ResumeLayout(false);
			this->MainMenu->PerformLayout();
			this->TaskBarCntxt->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

/*
catch (Exception^ e)
{
	MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
}
*/
//->Filter = "FITS|*.fits;*.fit;*.fts|UVIT FITS|*.raw";

public:

//custom program function definitions
//void InitializeVars();
void InitializeVars(array<String^>^ startargs);
void StatTxtsUpD();//function to update the stats txts
void FileTxtsUpD();
void SubImageStatsUpD();
void SetContrast();
void ViewFoundList();
void ImageUpD(array<double,2>^ image);
void SubImageUpD();
void Form1ProgUpD();
void ExtractKeyList(array<String^>^ keys, array<String^>^ filenames);
void CopyKeyList(array<String^>^ keys, array<String^>^ filenames);
void PlotKeyList(array<String^>^ keys, array<String^>^ filenames);
void AddToImageSet(array<String^>^ fullpathlist);
void WriteImageSet();
void FindFiles();
bool ValidKeyChck(String^ checkkey);//check for restricted key
bool ValidKeyChck(String^ checkkey,array<String^>^ keys);//check for exisitng key
void SpAxesUpD();
void UVAlgorithmContxtFunction(int type);//for UVIT algorithm list context selection
String^ UVITFilter(String^ channel, String^ filterindex);
String^ UVITFilter_FWAngle_to_Index(String^ channel, double angle);
void RecentFilesUpD();
void ROICompoundFit();
bool CLEAN_UVITVISIMG(JPFITS::FITSImage^ VISfits, double threshold, int occurences);
void GET_CATALOGUE_NPTS(String^ filename, String^ catExtension, String^ catCVAL1, String^ catCVAL2, String^ catMag, int N_bright);

JPPlot^ ROWplot;
void ROWplotUpD(bool show_contxt);
JPPlot^ COLplot;
void COLplotUpD(bool show_contxt);

array<double>^ BJDC(array<double>^ JD, double RightAscension_deg, double Declination_deg, bool returnCorrectionOnly);
void TBC(array<unsigned char>^ arr, int naxis1, int naxis2);//twentieth bit correction
::DialogResult TBC_Reference(array<String^>^ files);
__int64 TBC_TICKCOUNTREF = 0, TBC_FRAMETIMEREF = 0;
double TBC_TIMEREF = 0;
bool DO_TBC = false;
ArrayList^ TCTFILELIST = gcnew ArrayList();
ArrayList^ LBTFILELIST = gcnew ArrayList();

//program variables
static String^ CCDLABPATH = "C:\\ProgramData\\Astrowerks\\CCDLABx64\\";//static since declared
JPFITS::FITSImageSet^ IMAGESET;// = gcnew JPFITS::FITSImageSet();
int FILELISTINDEX, OLD_INDEX;//image index for the FileListDrop
bool IWLCK;		//Image Window Left (mouse) Clicks
array<int,1>^ SUBRANGE;
array<int, 1>^ PADDING;
array<int, 1>^ CROPPING;
bool LOADSUBRANGE;
array<double,2>^ SUBIMAGE;
double SUBIMAGESUM, SUBIMAGEMIN, SUBIMAGEMAX, SUBIMAGEMEAN, SUBIMAGEMEDIAN, SUBIMAGESTD;
array<int,1>^ XSUBRANGE;
array<int,1>^ YSUBRANGE;
int XPOS_CURSOR, YPOS_CURSOR, PRVXPOS_CURSOR, PRVYPOS_CURSOR;//zero based position in image window(s)
double XPOS_CURSOR_RADEG, YPOS_CURSOR_DECDEG;//WCS position in image window(s)
String^ XPOS_CURSOR_RAHMS;
String^ YPOS_CURSOR_DECDMS;//WCS position in image window(s)
int SUBIMAGE_HWX, SUBIMAGE_HWY, SUBIMAGE_HWX_OLD, SUBIMAGE_HWY_OLD, ROIX0, ROIY0, ROIXRad, ROIYRad, SUBIMAGEX0OLD, SUBIMAGEY0OLD;
array<double,1>^ DIMCLIM;// min/max contrast limits
array<double,1>^ IMSTDLIM;
double CTSperPERCENT;
int PREVMINCONTRASTVALUE, PREVMAXCONTRASTVALUE;
array<int, 2>^ FNDCOORDS;
array<Rectangle, 1>^ FNDCOORDRECTS;
array<double, 2>^ MARKCOORDS;
array<Rectangle, 1>^ MARKCOORDRECTS;
array<JPFITS::JPMath::PointD^, 1>^ MARKCOORDRECTDPTS;
bool FIRSTLOAD;
Bitmap^ SUBIMAGEBMP;
Bitmap^ IMAGEBMP;
UVIT^ UVIT_Data;
array<unsigned __int16,2>^ UVBGArray;

array<JPFITS::SourceExtractor^>^ PSES;
int PSESINDEX = -1;
array<array<Rectangle>^>^ PSESRECTS;
//array<Rectangle>^ PSERECTS;
array<Color>^ PSERECTCOLOURS;
void MAKEPSERECTS();
void MAKEMARKCOORDRECTS();
bool PSESPLOTALL = false;
int PSECOUNT = 0;

//PSETableViewer^ PSETABLEVIEWER;
TypeCode FILESAVEPREC;
Graphics^ IMAGEWINDOWGRFX;
Pen^ IMAGEWINDOWPEN;
SolidBrush^ IMAGEWINDOWBRUSH = gcnew SolidBrush(Color::Red);
array<String^>^ BATCHLIST;
JPFITS::FITSImage^ BATCHMULTIMG;
JPFITS::FITSImage^ BATCHBIASIMG;
JPFITS::FITSImage^ BATCHFLATIMG;
JPFITS::FITSImage^ BATCHADDIMG;
int BATCHVIEWINDEX;
System::DateTime DATE;
bool OPTIMGVIEWINVERTY;
array<String^>^ CLIPBRDHEADERKEYS;
array<String^>^ CLIPBRDHEADERVALS;
array<String^>^ CLIPBRDHEADERCOMS;
array<int>^ CLIPBRDHEADERINDS;

int UVITINTDRIFT_MAXDEV_INDEX = 0;
array<System::Drawing::Point, 2>^ UVITINTMODEDRIFTPOLYPOINTS;
array<System::Drawing::Point>^ POLYPOINTS;
array<System::Drawing::Point>^ POLYPOINTS2;
array<System::Drawing::Point>^ POLYPOINTSb;
array<System::Drawing::Point>^ POLYPOINTS2b;
Drawing::Color POLYPOINTSCOLOR = Color::Yellow;
Drawing::Color POLYPOINTS2COLOR = Color::Red;

String^ DIVMULTADDSUB_FILE;

int RADIALPTX1, RADIALPTY1, RADIALPTX2, RADIALPTY2;
double RADIALPTX1_CENT, RADIALPTY1_CENT, RADIALPTX2_CENT, RADIALPTY2_CENT;
JPPlot^ RADIALLINE_PLOT;
void RADIALLINE_PLOTUpD();
bool PLOTRADIALLINE;
array<Drawing::Point>^ RADIALLINEBOXPOINTS;

JPFITS::FitsFinder^ FITSFINDER;
array<String^>^ FITSFINDERFILES;
JPFITS::FitsFound^ FITSFOUND;

bool DRAW_ROI_PATH = false;
bool DRAW_ROI_PATH_START = false;
array<double, 2>^ ROI_PATH_COORDS;
array<Point>^ ROI_PATH_POINTS;
array<Rectangle>^ ROI_PATH_RECTS;
void MAKEROIPATHPOINTS();
void ROI_PATH_FILLREGION();
array<bool, 2>^ ROI_REGION;

bool DOMANREG, MANREG_CONTINUE;
array<int,2>^ MANREGCOORDS;
array<Rectangle,1>^ MANREGCOORDRECTS;
array<double,3>^ MANREGCENTROIDS;

int UVPCMODEPADOFFSET;

bool DOUVITMANREG, UVITMANREG_CONTINUE, UVITMANREGDIR_MULTI, DO_UVITDRIFTFILES, UVITBADTRACK = false;
array<String^>^ UVITMANREGFILELIST;
array<String^>^ UVITMANREGDIRLIST;
int UVITMANREGDIRLISTINDEX;
array<double>^ UVITMANREGFILELIST_TIMES;

bool UVREGISTRATION, UVREGISTRATION_TOUCHPOINT, UVREGISTRATION_TRANSLATE, UVNUVTOFUV;
array<String^>^ UVREGISTRATIONFILES;
int UVREGISTRATIONFILESINDEX, UVREGISTRATION_ANCHOR_INDEX, UVREGISTRATION_ROTATION_INDEX;
array<double,3>^ UVREGISTRATION_CENTROIDS;
double UVREGISTRATION_ROTATION_PHI;
array<double,2>^ UVREGISTRATION_ROTATION_CENTROIDS;
array<double>^ UVREGISTRATION_PHIS;
array<double>^ UVREGISTRATION_XSHIFTS;
array<double>^ UVREGISTRATION_YSHIFTS;
array<double>^ UVREGISTRATION_XCENTERS;
array<double>^ UVREGISTRATION_YCENTERS;
array<String^>^ UVNUVTOFUVFILES;
array<String^>^ UVMERGEDIRS;
int UVMERGEDIRS_INDEX = -1;
bool DRIFTFROMPCPSTRACK = false;

JPWaitBar::WaitBar^ WAITBAR;

int MidBtnMouseMoveXCurrent, MidBtnMouseMoveYCurrent, MidBtnMouseMoveXPrev, MidBtnMouseMoveYPrev, MidBtnMouseMoveXInit, MidBtnMouseMoveYInit;

double SUBIMLEFTMOUSEDOWNINITX, SUBIMLEFTMOUSEDOWNINITY;

array<double>^ XSliceX;
array<double>^ XSliceY;
array<double>^ YSliceX;
array<double>^ YSliceY;

bool axis1, axis2;

//array<String^>^ STARTARGS;

int UVLISTTOIMAGEPREC;
double UVPARCELTIME;
double UVDRIFTSTACKTIME;
bool UVPLOTDRIFTLISTNOW;
String^ UVPLOTDRIFTFILENAME;
bool UVAPPLYDRIFTNOW;
String^ UVAPPLYDRIFTCENTROIDSFILENAME;
bool UVCREATEIMAGENOW;
String^ UVCREATEIMAGEFILENAME;
bool UVDRIFTAUTORUN;
bool UVDRIFTBATCH;
array<String^>^ UVDRIFTBATCHFILES;
int UVDRIFTBATCHFILESINDEX;
bool UVCONVERTLISTTOIMAGEBATCH;
array<String^>^ UVCONVERTLISTTOIMAGEBATCHFILES;
JPPlot^ XDRIFT_PLOT;
JPPlot^ YDRIFT_PLOT;
FITSImageSet^ SPAREFITSImageSet;
bool AUTOVISDRIFTAPPLY = false;
bool FUVDIREXISTS = false;
bool NUVDIREXISTS = false;
bool DONUVDRIFTNOW = false;
bool UVITBATCHOP = false;
bool UVITBATCHOP_CANCELLED = false;
bool AUTOVISDRIFT = false;
bool UVITAUTOREGISTER = false;
String^ UVITBATCHMESG = "";
bool UVITPOSTMERGE = false;

bool COG_CURSOR;
JPPlot^ COG_PLOT;
JPPlot^ RAD_PLOT;

bool AUTOLOADIMAGES;
array<String^>^ AUTOLOADIMAGESFILES;

bool WCSMANUALRAD, WCSMANUALRAD_CONTINUE;
RADecBox^ RADECBOX;
array<double>^ WCS_RA;
array<double>^ WCS_DEC;
array<double,2>^ WCS_CENTROIDS;
bool WCSNEWPOINT;
JPFITS::WorldCoordinateSolution^ WCS;
//WCS^ wcs;
bool SHOW_WCSCOORDS;
bool UVIT_DEROTATE_WCS;
array<String^>^ UVIT_DEROTATE_FILES;
JPFITS::WorldCoordinateSolution^ WCS_DEROT;
bool WCSAUTOCANCEL = false;

array<double>^ RADIALPLOT_R;//radii
array<double>^ RADIALPLOT_V;//average values at radii
array<double>^ RADIALPLOT_P;//n pixels at radii
double RADIALPLOT_PHI;
bool RADIALPLOT_SETPHI;

MLCCDLAB::MLSurface^ MLSURF;

FitParametersWindow^ FPW;

int RECENTFILESLISTLENGTH = 15;

static String^ LASTTEXT = "";
void TEXTBOXENTER(Windows::Forms::ToolStripTextBox^ textbox);
void CHECKTEXTBOXTONUM(Windows::Forms::ToolStripTextBox^ textbox);

WCS_AutoSolver^ WCSAS;

String^ PSESAVEKERNELPATH;


private: System::Void Form1_Load(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void ImageWindow_MouseEnter(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void ImageWindow_MouseLeave(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void ContrastWideRad_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ContrastNarrowRad_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ContrastFullRad_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HalfWidthXUpD_ValueChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void FMLoad_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void FMAdd_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FMQuit_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void FMReload_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void SaveFileDialog_FileOk(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e);
private: System::Void MaxContrastSlider_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
private: System::Void MinContrastSlider_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
private: System::Void ImageWindow_MouseMove(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);
private: System::Void SubImageWindow_MouseEnter(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void SubImageWindow_MouseLeave(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void SubImageWindow_MouseMove(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);
private: System::Void ImageWindow_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);
private: System::Void BlinkChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void DeleteFileBtn_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void MoveUpBtn_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void MoveDownBtn_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void FileListDrop_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void ViewNextBtn_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void ViewLastbtn_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void BlinkTimer_Tick(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void SingleOutBtn_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void SubBiasChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void SubDarkChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void AddImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DivFlatChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void BatchMeanChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void BatchMedianChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void BatchStdvChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void BatchSumChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ContrastScaleDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FMSave_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void InvertContrastChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ScaleContrastChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TBSaveBatch_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RelativeContrast_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FMFind_Click(System::Object ^  sender, System::EventArgs ^  e);
private: System::Void FMViewFound_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ViewHeaderBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void HeaderCntxtMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FindImagePtsBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ReplaceImagePtsBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TBOpenFound_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EMFileBias_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EMBatchFlat_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void AutoRegBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCEdit_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCInsertCurrent_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCInsertBatch_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCRemoveCurrent_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCRemoveBatch_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ManRegBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ReplaceImagePtsDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BinBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CutSubImBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ScalarOpBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SCMChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCExtractKeyValue_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVOpenRawBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVMovieTimer_Tick(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVViewNextBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVViewLastBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVMovieBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVOpenRawDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
private: System::Void UVCentroidBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void UVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void UVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void UVSaveCentroidDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVSaveCentroidDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
private: System::Void SubImageWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
private: System::Void ImageWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
private: System::Void UVTransferImagesBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVOpenDirBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageWindow_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void TBDestructTimer_Tick(System::Object^  sender, System::EventArgs^  e);
private: System::Void TaskBarCntxtMenu_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void TaskBarCntxtMenu_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void TaskBarCntxtMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVOpenCentroidBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVOpenUCFDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
private: System::Void UVDarkImageRad_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ColourMapDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageOpsWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void BatchSubImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchMakeListBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchOpenListBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVImageOnlyChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVActiveBGChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVDarkScalarRad_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageOpsWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ImageOpsWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void SubImageSurfFacet_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageSurfSmooth_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageSurfMetal_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageSurfMesh_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SurfWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void SurfWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void OptFileSavePrecDbl_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OptFileSavePrecInt32_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FormLoadBGW_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void UVXDecHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVYDecHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVPixelHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVShapeHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFCMinHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFCMaxMinHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVHistWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void UVHistWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void ImageViewHistogram_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageCntxtViewWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ImageCntxtViewWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ImageCntxtViewWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void PSEFindSrcBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EditValueCntxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageEditValueCntxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFitChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFitWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void PSEFitWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void PSEFitWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void OptFileSavePrecUInt16_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EMGSE_UnpackImg_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void InfoStatic1_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void InfoCntxt_ItemClicked(System::Object^  sender, System::EventArgs^  e);
private: System::Void centerToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageSlideX_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
private: System::Void SubImageSlideY_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
private: System::Void MathOpBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVGoToBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ShowCursorBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ShowFoundCoordsChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ShowPSEChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageOpFilterBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageOpFilterTypeDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void listBox1_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void listBox1_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileListDrop_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageEditBoxCntxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EditBoxCntxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FMLoadSubFrame_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageEditBoxSetSubRangeCntxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchComputeBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchDivideImageChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchAddImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchMultiplyImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchSubtractImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void BatchBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void BatchBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void EqualHWChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void HalfWidthYUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindow_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindow_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void FileListDrop_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageWindow_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void OptViewImage_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OptViewSpectrum_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ViewImageTog_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ViewSpectrumTog_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ShowCrosshair_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVStatsAnalysisBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVHVUTelemBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MainTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchIntegralTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchOutFileName_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void XBinUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void Tooltip_Popup(System::Object^  sender, System::Windows::Forms::PopupEventArgs^  e);
private: System::Void SubImageWindow_MouseHover(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageWindow_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ROIFitBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ROIFitFcnDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SetParametersChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ApplyUVFPNMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ConvertFromTextMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ConvertListToImgMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
private: System::Void StatsCopyClipBrdCntxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageSumStatic_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void SavePSChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVITMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVITMenu_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void FlipInvertBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FlipHorzBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FlipVertBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotCCWBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotCWBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HeaderKeyTxt_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void HCExtractListValues_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCPlotKeyValues_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCPlotListValues_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void StackingDirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TabBatchElementalFindPointsChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void OptFileSavePrecInt16_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void COGBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MinContrastSlider_MouseHover(System::Object^  sender, System::EventArgs^  e){}
private: System::Void MaxContrastSlider_MouseHover(System::Object^  sender, System::EventArgs^  e){}
private: System::Void MinContrastSlider_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void MaxContrastSlider_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void MinContrastSlider_MouseEnter(System::Object^  sender, System::EventArgs^  e) {MinContrastSlider->Focus();}
private: System::Void MinContrastSlider_MouseLeave(System::Object^  sender, System::EventArgs^  e) {this->ActiveControl = MinContrastStatic;}
private: System::Void MaxContrastSlider_MouseEnter(System::Object^  sender, System::EventArgs^  e) {MaxContrastSlider->Focus();}
private: System::Void MaxContrastSlider_MouseLeave(System::Object^  sender, System::EventArgs^  e) {this->ActiveControl = MinContrastStatic;}
private: System::Void TBOptFileSavePrecDbl_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TBOptFileSavePrecInt32_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TBOptFileSavePrecInt16_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TBOptFileSavePrecUInt16_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ClipToContrastBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageSumTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageMinTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageMaxTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageMedianTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageMeanTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageStdTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVAutoThreshChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFrameHist_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVIT_ApplyCPUCorrectionMenu_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MultImgChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindow_MouseHover(System::Object^  sender, System::EventArgs^  e);
private: System::Void WriteImageSetBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void WriteImageSetBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void WriteImageSetBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void TBSaveOver_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TBSaveBatchOver_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RunningDirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileNameTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void FileNameTxt_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindow_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageWindow_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void BatchMinimumChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchMaximumChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);		 
private: System::Void ImageWindow_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void RotateAngleUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void NShiftHorzUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void NShiftVertUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ShiftHorzBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ShiftVertBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchFileAppRad_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void IndividualDirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void StackUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchRunningNumUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchMovieTimer_Tick(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchGoToBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchViewNextBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchViewLastBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void BatchBlinkChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void CreateFlatFieldListMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ListToImage1PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ListToImage2PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ListToImage4PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ListToImage8PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ParcelStackTimeDrop_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ParcelUVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ParcelUVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ParcelUVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void CreateDriftFromPCMenuItem_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void CreateDriftFromINTMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftStackTimeDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftFromListTimeTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void CreateDriftFromPCMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void PlotDriftListMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ApplyDriftListMentuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftFromPCListWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void DriftFromPCListWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void DriftFromPCListWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void FilterCosmicRaysChckMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ConvertListToImgMenu_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void ApplyFlatListToImageChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftFromListEndTimeTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void PlotCountsPerFrameMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CosmicRayFilterMenuTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftFromINTWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void DriftFromINTWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void DriftFromINTWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void BatchScanDirectoryBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TryAutoDeBiasINTDrift_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftFromPCInterpolateChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SmoothINTDriftChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageWindow_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserDefinedShiftRotateMenuItem_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserXShiftTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserYShiftTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserRotationTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserDefinedShiftRotateMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void FlipHorizontalMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FlipVerticalMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWndwCntxtPlotRow_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWndwCntxtPlotCol_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWndwCntxtPlotRowSubOnly_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWndwCntxtPlotColSubOnly_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EMCopyHeader_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ManRegWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ManRegWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ManRegWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void CrossCorrINTDriftChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PointSrcINTDriftChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ManRegTrkHWUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DigestL1FITSImageMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void INTAtoINTADriftCorrectionMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void INTAtoINTAapplyDriftWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void INTAtoINTAapplyDriftWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void INTAtoINTAapplyDriftWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void CosmicRayFilterMenuChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CosmicRayFilterSigmaMenuChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CosmicRayFilterSigmaMenuTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileListDrop_DropDown(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileListDrop_DropDownClosed(System::Object^  sender, System::EventArgs^  e);
private: System::Void MaxMinThreshTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void MaxMinThreshChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MaxMinCountTwiceChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImgROITab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImgRadialPlotMenuBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RadialPlotInterpolateROIChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DigestL1Wrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void DigestL1Wrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void DigestL1Wrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void L1DigestApplyFPNChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1DigestApplyDISTChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftSmoothNDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void KeyValNormBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1DiscardDataTimeDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1DiscardDataTimeChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1DiscardDuplicateChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserRotationXTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UserRotationYTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void LinearRotationChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void GeneralTransformChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformCoefATxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformCoefBTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformCoefCTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformCoefDTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformCenterXTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformCenterYTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformShiftXTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TransformShiftYTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVAutoApplyDriftandImageChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVAutoDriftImageViewChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void GeneralUVRegistrationMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DiscardL1DuplicateWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void DiscardL1DuplicateWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void DiscardL1DuplicateWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void ConvertUVCentroidListToImgWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ConvertUVCentroidListToImgWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ConvertUVCentroidListToImgWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void RadialPlotMedianBackgroundChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RegistrationUVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void RegistrationUVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void RegistrationUVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void CombineUVCentroidListsMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MergeCentroidListsWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void MergeCentroidListsWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void MergeCentroidListsWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void NUVToFUVFrameMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotationUVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void RotationUVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void RotationUVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void MinContrastCountTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void MaxContrastCountTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void MinContrastStdTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void MaxContrastStdTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void CombineRGBBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RGBSaveBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileDirectoryTxt_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void DeSaturateROICountsMenuItem_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void YBinUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BackgroundCountsPixelFrameTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void CorrectBackgroundCountsChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtractROICentroidListMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSRADecManual_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageSumTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageMinTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageMaxTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageMedianTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageMeanTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImageStdTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void WCSRADecShowChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCCopyKeyValue_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCCopyListValue_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OptInvertImageView_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCInsertSelectedToOthers_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void perTimeBinMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DeleteFileBtn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void DeleteFileBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageFingerRmvToHere_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageFingerRmvFromHere_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ScanContextGoToBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ScanContextGoToTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ScanContextGoToTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void SubImCntxtCopyPixPoord_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWndwCntxtMarkCoord_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImCntxtMarkCoord_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MarkCoordClear_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImMarkCoordClear_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ConsolidateNUVApplyToFUV_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftNUVtoFUVBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void DriftNUVtoFUVBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void DriftNUVtoFUVBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void SIZECntxtEditImgDim_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void SIZECntxtBatchChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SIZECntxtBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void SIZECntxtBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void SIZECntxtBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void ExtractL1gzsMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExtractL1ArchiveBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ExtractL1ArchiveBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ExtractL1ArchiveBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void PSEWidthUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileInfoPanel_MouseHover(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1CentroidPaddingChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PCCentroidPaddingDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ApplyDriftCreateExpArrayChc_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ApplyDriftListWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void ApplyDriftListWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void ApplyDriftListWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void ApplyExpArrayToImageChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImCntxtCopyImage_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageWindow_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void PadImageBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CutSubImBtn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void CutSubImBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void ImageSizeTxt_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageSizeTxt_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void SIZECntxtMenu_Opened(System::Object^  sender, System::EventArgs^  e);
private: System::Void InfoStatic1_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageFingerRecToHere_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageFingerRecFromHere_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExposureArrayResolutionDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ExposureArrayResMenuText_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageSumStatic_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageFingerSortFileName_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageFingerSortKeyValue_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWndwPlotRadialVector_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindowSaveRadialVector_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindowRadialAngleTxt_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindowRadialAngleTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void ImageWindowRadialSetAngle_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImCntxtGoToPixel_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImCntxtGoToPixXTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void SubImCntxtGoToPixYTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void ImageWindow_SizeChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void CleanVISImagesMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void CleanVISBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void CleanVISBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void CleanVISBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void L1DegradientINTMode_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1SkipINTMode_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1FilterCorrectionChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImCntxtCopyCentroidCoord_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void InfoStatic1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void InfoTxt1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void InfoTxt1_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void InfoTxt1_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImagePanel_MouseHover(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFitResultListBox_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void FileDirectoryTxtContextMenuDelDirRmImg_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HCEditAll_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ListToImage16PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImCntxtGoToRATxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void SubImCntxtGoToDecTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void PSEFitTypeChck_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void PSEFitTypeChck_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FMViewExtensionTable_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSELoadSrcBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ParcelStackmdMmChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1TBCChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DriftPCROIOnly_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ResetPlotPositions_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ImageWindowCntxtSquare_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void DeRotateViaWCS_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSCopyToLoadedImgs_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RecentFilesLoadAll_DoubleClick(System::Object^  sender, System::EventArgs^  e);
private: System::Void RecentFilesLoadSingle_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void PSESigmaCountBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSESeachROIOnlyChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSETableViewBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFitResultCntxtCopySelected_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFitResultCntxtCopyAll_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFitResultsCntxt_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
private: System::Void BatchQuadratureChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFindSrcBtn_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFindSrcBtn_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEFindSrcBtn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void PSEFindSrcBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImSurfColumnMenuBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImageRATxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void SubImMarkCoordAsCentroidChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEEllipticalROI_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImMarkCoordContainedPSE_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEClearBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void HeaderKeyTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void WCSPlotSolutionPtsBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSLoadSimbadAscii_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSListExciseToROI_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSClarifyListSources_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void SubImMarkCoordClearContained_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSSolveList_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void testbtnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void toolStripMenuItem15_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSScaleInit_Enter(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSScaleInit_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void AutoWCSMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
private: System::Void AutoWCSMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void WCSAutoBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void WCSAutoBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void WCSAutoCatalogueTxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoSolveBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoSolveBtn_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoSolveBtn_MouseLeave(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoCatalogueCVAL1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoCatalogueCVAL2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoCatalogueExtensionTxt_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoCatalogueMag_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void TEST_TEXT_BOX_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void TEST_TEXT_BOX_MouseEnter(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSRefineSolutionBtn_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoRefineChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1TransformNUVtoFUVChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEDrawROI_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void SaveROIContext_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void LoadROIContext_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MarkCoordSave_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void MarkCoordLoad_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1CleanINTMode_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVITMenu_DropDownOpened(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoCatalogueTxt_MouseHover(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtnCntxtBiLinear_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtnCntxtLanczos3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtnCntxtLanczos4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtnCntxtLanczos5_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtnCntxtNearest_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void RotateBtnCntxt_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
private: System::Void L1DigestApplyDISTInterpNearChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void L1DigestApplyDISTInterpBiLinChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSClearMenuBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void AutoWCSScaleMenuBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void AutoWCSScaleMenuBtn_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
private: System::Void AutoWCSScaleSaveBtn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WSCSaveScaleTxtBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
private: System::Void WCSParamMenuBtn_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void WCSParamMenuBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void WCSAutoXAxisParityChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoYAxisParityChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void WCSAutoExternalDLLChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ImageMaxStatic_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void PointSrcINTDriftDisplayChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void PointSrcINTDriftDisplayCadenceDrop_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void BatchFileKeepDirectoriesChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void autoRunToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSAutoQueryBtn_DoubleClick(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSAutoQueryCVAL1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSQuerySaveFileChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSAutoConditionArraysChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSQuerySquareRegionChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void AstroQueryCatalogueNameDrop_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSAutoQueryBtn_DropDownOpening(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSQuerySolveAfter_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void masterizeSinglesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void UVDeleteMergeDirsChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void L1DigestDeleteFileChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BatchSubtractImageChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BatchMultiplyImageChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BatchAddImageChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void TBZipAllBtn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSClearAllChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ConsolidateDriftFolderChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ConsolidateTimeListFolderChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void TBZipMoveChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void TBZipCopyChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void RegistrationXYIntsListFolderScanChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void MergeXYIntsListFolderScanChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void UVLoadAllMerged_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void PointSrcINTDriftNoPSEConfChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void PointSrcINTDriftNoPlotConfChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void AutoWCSXCorr_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSQuerySaveFileChooseDirBtn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void UVFinalizeScienceBtn_DoubleClick(System::Object^ sender, System::EventArgs^ e);
private: System::Void DriftFromPCPSTrackBtn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void PointSrcROIStackDriftDrop_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void DriftFromPCPSTrackBGWrkr_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
private: System::Void DriftFromPCPSTrackBGWrkr_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);
private: System::Void DriftFromPCPSTrackBGWrkr_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
private: System::Void PSTrackDisplayClearBtn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void L1AutoProceedVISBackGround_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void L1AutoProceedVISTracking_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void L1AutoApplyVISDrift_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void WCSClearPlotSolutionPtsBtn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void invertWCSToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void L1DigestPCParityChck_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void PointSrcROIFindSrcChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PointSrcROIFindNSrcDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void PointSrcROIAutoRunChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFinalizeIncludeTablesChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFinalizeBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void UVFinalizeBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void UVFinalizeBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void UVFinalizeDeleteIntrmdtChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFinalizeMoveOrCopyZipChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVAutoPSFPostMergeChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e);
private: System::Void UVFinalizeIncludeExpMapChck_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEDropContextAdd_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEDropContextRemove_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEDropContextClearAll_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PSEDropContextPlotAll_Click(System::Object^  sender, System::EventArgs^  e);

		
		
		
};
}