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

#include "stdafx.h"
#include "Form1.h"

using namespace CCDLAB;

[STAThreadAttribute]
int main(array<System::String ^>^ startargs)
{
	/*try
	{*/
		// Enabling Windows XP visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		// Create the main window and run it


		if (startargs->Length == 0)
			Application::Run(gcnew Form1());
		else
			Application::Run(gcnew Form1(startargs));
		
		return 0;

	/*}
	catch (::Exception^ e)
	{
		::MessageBox::Show(String::Concat(e->Message,":  ",e->Data,":  ",e->StackTrace,"  ",e->Source,"  ",e->TargetSite));
		return 0;
	}*/
	return 0;
}

void Form1::InitializeVars(array<String^>^ startargs)
{
	AUTOLOADIMAGESFILES = startargs;
	IWLCK = true;//fix cursor box
	FILELISTINDEX = 0;
	OLD_INDEX = 0;
	SUBRANGE = gcnew array<int,1>{-1,0,0,0};
	LOADSUBRANGE = false;
	SUBIMAGE = gcnew array<double,2>(21,21);
	XSUBRANGE = gcnew array<int,1>(21);
	YSUBRANGE = gcnew array<int,1>(21);
	XPOS_CURSOR = 0;
	YPOS_CURSOR = 0;//zero based position in image window(s)
	PRVXPOS_CURSOR = 0;
	PRVYPOS_CURSOR = 0;
	SUBIMAGE_HWX = 10;
	SUBIMAGE_HWY = 10;
	DIMCLIM = gcnew array<double,1>(2);// min/max contrast limits
	IMSTDLIM = gcnew array<double,1>(2);
	CTSperPERCENT = 100;
	PREVMINCONTRASTVALUE = 0;
	PREVMAXCONTRASTVALUE = 100;
	FIRSTLOAD = true;
	FILESAVEPREC = TypeCode::Double;
	IMAGEWINDOWPEN = gcnew Pen(::Color::Yellow);
	BATCHVIEWINDEX = -1;
	UVPCMODEPADOFFSET = 0;
	UVLISTTOIMAGEPREC = 1;
	UVPARCELTIME = 0;
	UVDRIFTSTACKTIME = 0;
	UVPLOTDRIFTLISTNOW = false;
	UVAPPLYDRIFTNOW = false;
	UVCREATEIMAGENOW = false;
	UVDRIFTAUTORUN = false;
	UVDRIFTBATCH = false;
	UVDRIFTBATCHFILESINDEX = 0;
	UVREGISTRATION = false;
	UVREGISTRATION_TOUCHPOINT = false;
	UVNUVTOFUV = false;
	axis1 = false;
	axis2 = false;
	DOMANREG = false;
	MANREG_CONTINUE = false;
	MANREGCOORDS = gcnew array<int,2>(0,0);
	MANREGCOORDRECTS = gcnew array<Rectangle,1>(0);
	UVITMANREG_CONTINUE = false;
	UVITMANREGDIRLISTINDEX = 0;
	DOUVITMANREG = false;
	DO_UVITDRIFTFILES = false;
	COG_CURSOR = false;
	COG_PLOT = gcnew JPPlot();
	RAD_PLOT = gcnew JPPlot();
	XDRIFT_PLOT = gcnew JPPlot();
	YDRIFT_PLOT = gcnew JPPlot();
	AUTOLOADIMAGES = false;
	WCSMANUALRAD = false;
	WCSMANUALRAD_CONTINUE = false;
	SHOW_WCSCOORDS = false;
	OPTIMGVIEWINVERTY = false;

	FNDCOORDS = gcnew array<int,2>(1,2);
	FNDCOORDRECTS = gcnew array<Rectangle,1>(1);

	PSERECTCOLOURS = gcnew array<Color>(11) { Color::OrangeRed, Color::Cyan, Color::LawnGreen, Color::BlueViolet, Color::DeepPink, Color::Aqua, Color::Crimson, Color::DarkGoldenrod, Color::Red, Color::Chartreuse, Color::HotPink };

	RADIALLINEBOXPOINTS = gcnew array<Drawing::Point>(4);
	RADIALPLOT_SETPHI = false;

	ROWplot = gcnew JPPlot();
	ROWplot->Text = "Row Plot";
	ROWplot->JPPlotMainMenu->Visible = true;
	COLplot = gcnew JPPlot();
	COLplot->Text = "Column Plot";
	COLplot->JPPlotMainMenu->Visible = true;
}

void Form1::Form1_Load(System::Object ^  sender, System::EventArgs ^  e)
{
	bool license = ::Convert::ToBoolean(GetReg("CCDLAB", "LicenseAgree"));
	if (!license)
	{
		/*String^ agree = "This software is distributed under Creative Commons license 'Attribution-NonCommercial-NoDerivatives 4.0 International' (CC BY-NC-ND 4.0).  ";
		agree += "By clicking Yes you agree to the terms of that license agreement.  See:  https://creativecommons.org/licenses/by-nc-nd/4.0/";*/

		String^ agree = "This software is released under GNU Public General License v 3.0 (GPLv3).  ";
		agree += "By clicking Yes you agree to the terms of that license agreement.  See:  http://www.gnu.org/licenses/";

		::DialogResult res = ::MessageBox::Show(agree, "License Agreement", ::MessageBoxButtons::YesNo);
		if (res == ::DialogResult::No)
			::Application::Exit();
		else
			SetReg("CCDLAB", "LicenseAgree", true);
	}

	//CCDLABPATH = "C:\\Program Files\\Astrowerks\\CCDLABx64\\";
	if (!::Directory::Exists(CCDLABPATH))
		::Directory::CreateDirectory(CCDLABPATH);

	IMAGESET = gcnew FITSImageSet();
	//IWLC = 0;
	IMAGEWINDOWGRFX = ImageWindow->CreateGraphics();
	IMSTDLIM[0] = -1;
	IMSTDLIM[1] =  2;

	PSEFitStatsTypeDrop->SelectedIndex = Convert::ToInt32(GetReg("CCDLAB", "PSEFitStatsTypeDrop"));
	ROIFitStatsTypeDrop->SelectedIndex = Convert::ToInt32(GetReg("CCDLAB", "ROIFitStatsTypeDrop"));

	try
	{
		InfoStatic1->Text = (String^)GetReg("CCDLAB", "InfoStatic1");
		InfoStatic2->Text = (String^)GetReg("CCDLAB", "InfoStatic2");
		InfoStatic3->Text = (String^)GetReg("CCDLAB", "InfoStatic3");
		InfoStatic4->Text = (String^)GetReg("CCDLAB", "InfoStatic4");
		InfoStatic5->Text = (String^)GetReg("CCDLAB", "InfoStatic5");
		MainTab->SelectedIndex = ::Convert::ToInt32(GetReg("CCDLAB", "MainTabIndex"));
		BatchOperationTab->SelectedIndex = ::Convert::ToInt32(GetReg("CCDLAB", "BatchOperationTabIndex"));
		StackUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "StackUpDValue"));
		BatchRunningNumUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "RunningUpDValue"));
		RadialPlotMedianBackgroundChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "RadialMedianBG"));
		XBinUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "XBinUpD"));
		YBinUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "YBinUpD"));
		BackgroundCountsPixelFrameTxt->Text = (String^)GetReg("CCDLAB", "BackgroundCountsPixelFrameTxt");
		/*OptInvertImageView->Checked = Convert::ToBoolean(GetReg("CCDLAB","OPTIMGVIEWINVERTY"));
		OPTIMGVIEWINVERTY = OptInvertImageView->Checked;*/

		PSEPixelMinUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "PSEPixValMin"));
		PSESaturationUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "PSEPixSaturation"));
		PSEKernelMinUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "PSECountValMin"));
		PSEPixelMaxUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "PSEPixValMax"));
		PSEKernelMaxUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "PSECountValMax"));
		PSEKernelRadUpD->Value = ::Convert::ToDecimal(GetReg("CCDLAB", "PSEWidth"));
		PSESeparationUpD->Value = Convert::ToDecimal(GetReg("CCDLAB", "PSESeparation"));
		PSEAutoBackgroundChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "PSE_AUTOBGCHCK"));
		ROIX0 = Convert::ToInt32(GetReg("CCDLAB", "ROIX0"));
		ROIY0 = Convert::ToInt32(GetReg("CCDLAB", "ROIY0"));
		ROIXRad = Convert::ToInt32(GetReg("CCDLAB", "ROIXRad"));
		ROIYRad = Convert::ToInt32(GetReg("CCDLAB", "ROIYRad"));

		UVPixelMinThresh->Value = ::Convert::ToInt32(GetReg("CCDLAB", "UVPixelMinThresh"));
		UVPixelMaxThresh->Value = ::Convert::ToInt32(GetReg("CCDLAB", "UVPixelMaxThresh"));
		UVShapeMinThresh->Value = ::Convert::ToInt32(GetReg("CCDLAB", "UVShapeMinThresh"));
		UVShapeMaxThresh->Value = ::Convert::ToInt32(GetReg("CCDLAB", "UVShapeMaxThresh"));
		StackingDirectoryTxt->Text = (String^)GetReg("CCDLAB", "StackingFilesPath");

		ImageFingerSortKeyValueTxt->Text = (String^)GetReg("CCDLAB", "ImageFingerSortKeyTxt");
	}
	catch (...) {}
	
	UVActiveBGChck->Checked = true;
	UVGeneralRegistrationResolutionDrop->SelectedIndex = 2;
	FindPtsDrop->SelectedIndex = 0;
	ScalarOpStyleDrop->SelectedIndex = 0;
	ReplaceImagePtsDrop->SelectedIndex = 0;
	ContrastScaleDrop->SelectedIndex = 0;
	ColourMapDrop->SelectedIndex = 0;
	Chart1->SendToBack();

	if (AUTOLOADIMAGESFILES->Length >= 1)
	{
		int ind = AUTOLOADIMAGESFILES[0]->LastIndexOf("\\");
		String^ dir = AUTOLOADIMAGESFILES[0]->Substring(0,ind);
		SetReg("CCDLAB", "OpenFilesPath",dir);

		AddToImageSet(AUTOLOADIMAGESFILES, true);
		AUTOLOADIMAGESFILES = gcnew array<String^>(0);
	}

	/*HalfWidthXUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "SubImageHWX"));
	HalfWidthYUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "SubImageHWY"));*/
	SubImageSizeTxt->Text = "Size: " + ((int)HalfWidthXUpD->Value * 2 + 1).ToString() + " x " + ((int)HalfWidthYUpD->Value * 2 + 1).ToString();
	
	try
	{
		RecentFilesUpD();
	}
	catch (...)
	{
		//CCDLABPATH = "C:\\Program Files\\Astrowerks\\CCDLABx64\\";
		array<String^>^ files = Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
		for (int i = 0; i < files->Length; i++)
			File::Delete(files[i]);
		RecentFilesUpD();
	}

	TBZipCopyChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "TBZipCopyChck"));
	TBZipMoveChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "TBZipMoveChck"));

	//AUTOVISDRIFTAPPLY = false;
}

void Form1::Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (PSEEllipticalROI->Checked)
	{
		SUBIMAGE_HWX = SUBIMAGE_HWX_OLD;
		SUBIMAGE_HWY = SUBIMAGE_HWY_OLD;
		SubImageSlideX->Value = SUBIMAGEX0OLD + 1;
		SubImageSlideY->Value = SUBIMAGEY0OLD + 1;
	}

	SetReg("CCDLAB", "SubImageHWX", SUBIMAGE_HWX.ToString());
	SetReg("CCDLAB", "SubImageHWY", SUBIMAGE_HWY.ToString());
	SetReg("CCDLAB", "XPOS_CURSOR", (SubImageSlideX->Value - 1).ToString());
	SetReg("CCDLAB", "YPOS_CURSOR", (SubImageSlideY->Value - 1).ToString());
	SetReg("CCDLAB", "PSE_AUTOBGCHCK", PSEAutoBackgroundChck->Checked);

	::File::Delete(CCDLABPATH + "ccdlabfoundfilelist.CFL");
}

void Form1::TBZipMoveChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "TBZipMoveChck", TBZipMoveChck->Checked);

	if (TBZipMoveChck->Checked)
	{
		TBZipCopyChck->Checked = false;
		SetReg("CCDLAB", "TBZipCopyChck", TBZipCopyChck->Checked);
	}
	if (!TBZipMoveChck->Checked)
		TBZipMoveChck->Checked = true;

	TBZipAllBtn->ShowDropDown();
}

void Form1::TBZipCopyChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "TBZipCopyChck", TBZipCopyChck->Checked);

	if (TBZipCopyChck->Checked)
	{
		TBZipMoveChck->Checked = false;
		SetReg("CCDLAB", "TBZipMoveChck", TBZipMoveChck->Checked);
	}
	if (!TBZipCopyChck->Checked)
		TBZipCopyChck->Checked = true;

	TBZipAllBtn->ShowDropDown();
}

void Form1::FormLoadBGW_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{

}

void Form1::TEST_TEXT_BOX_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	CHECKTEXTBOXTONUM((Windows::Forms::ToolStripTextBox^)sender);
}

void Form1::TEST_TEXT_BOX_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	TEXTBOXENTER((Windows::Forms::ToolStripTextBox^)sender);
}

void Form1::TEXTBOXENTER(Windows::Forms::ToolStripTextBox^ textbox)
{
	LASTTEXT = textbox->Text;
}

void Form1::CHECKTEXTBOXTONUM(Windows::Forms::ToolStripTextBox^ textbox)
{
	if (textbox->Text == "-" || textbox->Text == "-." || textbox->Text == "." || textbox->Text == "+" || textbox->Text == "+." || textbox->Text == "")
		return;

	if (textbox->Text->Length > 0)
		if (textbox->Text->Substring(textbox->Text->Length - 1)->ToLower() == "e")
			return;
	if (textbox->Text->Length > 1)
		if (textbox->Text->Substring(textbox->Text->Length - 2)->ToLower() == "e+" || textbox->Text->Substring(textbox->Text->Length - 2)->ToLower() == "e-")
			return;
	try
	{
		Convert::ToDouble(textbox->Text);
	}
	catch (...)
	{
		textbox->Text = LASTTEXT;
	}

	LASTTEXT = textbox->Text;
	SetReg("CCDLAB", textbox->Name, textbox->Text);
}

void Form1::OptInvertImageView_Click(System::Object^  sender, System::EventArgs^  e)
{
	/*SetReg("CCDLAB","OPTIMGVIEWINVERTY",OptInvertImageView->Checked.ToString());
	OPTIMGVIEWINVERTY = OptInvertImageView->Checked;
	IMAGEBMP->RotateFlip(::Drawing::RotateFlipType::RotateNoneFlipY);
	ImageWindow->Refresh();*/
}

void Form1::OptViewImage_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (OptViewImage->Checked == false && OptViewSpectrum->Checked == false)
	{
		OptViewImage->Checked = true;
		ViewImageTog->Checked = true;
	}

	OptViewSpectrum->Checked = false;
	ViewSpectrumTog->Checked = false;

	Chart1->SendToBack();
	Chart1->Visible = false;

	ImageWindow->BringToFront();
	ImageWindow->Visible = true;
}

void Form1::OptViewSpectrum_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET[FILELISTINDEX]->Height > 512)
		if (::MessageBox::Show("Plotting more than 512 lines can slow performance, are you sure?", "Warning...", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;

	if (IMAGESET[FILELISTINDEX]->Width == 1)
	{
		MessageBox::Show("Plot vector has unit width...can't plot.", "Error...", ::MessageBoxButtons::YesNo);
		return;
	}

	if (OptViewImage->Checked == false && OptViewSpectrum->Checked == false)
	{
		OptViewSpectrum->Checked = true;
		ViewSpectrumTog->Checked = true;
	}

	OptViewImage->Checked = false;
	ViewImageTog->Checked = false;

	ImageWindow->SendToBack();
	ImageWindow->Visible = false;

	Chart1->BringToFront();
	Chart1->Visible = true;

	SpAxesUpD();
}

void Form1::ViewImageTog_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptViewImage_Click(sender,e);
}

void Form1::ViewSpectrumTog_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptViewSpectrum_Click(sender,e);
}

void Form1::HalfWidthXUpD_ValueChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	SubImageSizeTxt->Text = "Size: " + ((int)HalfWidthXUpD->Value * 2 + 1).ToString() + " x " + ((int)HalfWidthYUpD->Value * 2 + 1).ToString();

	if (HalfWidthXUpD->Tag->ToString()->Equals("YUpD"))
	{
		HalfWidthXUpD->Tag = "";
		return;
	}

	SUBIMAGE_HWX = int(HalfWidthXUpD->Value);
	if (EqualHWChck->Checked)
	{
		SUBIMAGE_HWY = SUBIMAGE_HWX;
		HalfWidthYUpD->Tag = "XUpD";
		HalfWidthYUpD->Value = SUBIMAGE_HWY;
	}

	if (IMAGESET->Count > 0)
	{	
		int width = IMAGESET[FILELISTINDEX]->Width;
		if (SUBIMAGE_HWX > (width-1)/2)
		{
			HalfWidthXUpD->Value = int((width-1)/2);
			SUBIMAGE_HWX = (int)HalfWidthXUpD->Value;
			return;
		}
	}

	XSUBRANGE = gcnew array<int,1>(SUBIMAGE_HWX*2+1);
	YSUBRANGE = gcnew array<int,1>(SUBIMAGE_HWY*2+1);
	SUBIMAGE = gcnew array<double,2>(SUBIMAGE_HWX*2+1,SUBIMAGE_HWY*2+1);
	SUBIMAGEBMP = gcnew Bitmap(SUBIMAGE_HWX*2+1,SUBIMAGE_HWY*2+1,PixelFormat::Format24bppRgb);

	if (IMAGESET->Count > 0)
	{
		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();
	}

	if (ImageWndwCntxtPlotRow->Checked && ImageWndwCntxtPlotRowSubOnly->Checked)
		ROWplotUpD(false);

	if (PLOTRADIALLINE)
		RADIALLINE_PLOTUpD();
}

void Form1::HalfWidthYUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	SubImageSizeTxt->Text = "Size: " + ((int)HalfWidthXUpD->Value * 2 + 1).ToString() + " x " + ((int)HalfWidthYUpD->Value * 2 + 1).ToString();

	if (HalfWidthYUpD->Tag->ToString()->Equals("XUpD"))
	{
		if (ImageWndwCntxtPlotCol->Checked && ImageWndwCntxtPlotColSubOnly->Checked)
			COLplotUpD(false);
		HalfWidthYUpD->Tag = "";
		return;
	}

	SUBIMAGE_HWY = int(HalfWidthYUpD->Value);
	if (EqualHWChck->Checked || HalfWidthXUpD->Value == HalfWidthYUpD->Value)
	{
		SUBIMAGE_HWX = SUBIMAGE_HWY;
		HalfWidthXUpD->Tag = "YUpD";
		HalfWidthXUpD->Value = SUBIMAGE_HWX;
	}

	if (IMAGESET->Count > 0)
	{
		int height = IMAGESET[FILELISTINDEX]->Height;
		if (SUBIMAGE_HWY > (height-1)/2)
		{
			HalfWidthYUpD->Value = int((height-1)/2);
			SUBIMAGE_HWY = (int)HalfWidthYUpD->Value;
			return;
		}
	}

	XSUBRANGE = gcnew array<int,1>(SUBIMAGE_HWX*2+1);
	YSUBRANGE = gcnew array<int,1>(SUBIMAGE_HWY*2+1);
	SUBIMAGE = gcnew array<double,2>(SUBIMAGE_HWX*2+1,SUBIMAGE_HWY*2+1);
	SUBIMAGEBMP = gcnew Bitmap(SUBIMAGE_HWX*2+1,SUBIMAGE_HWY*2+1,PixelFormat::Format24bppRgb);

	if (IMAGESET->Count > 0)
	{
		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();
	}

	if (ImageWndwCntxtPlotCol->Checked && ImageWndwCntxtPlotColSubOnly->Checked)
		COLplotUpD(false);

	if (PLOTRADIALLINE)
		RADIALLINE_PLOTUpD();
}

void Form1::EqualHWChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (EqualHWChck->Checked)
	{
		int HWx = (int)HalfWidthXUpD->Value;
		int HWy = (int)HalfWidthYUpD->Value;
		int w = Math::Min(HWx,IMAGESET[FILELISTINDEX]->Height);
		int h = Math::Min(HWy,IMAGESET[FILELISTINDEX]->Width);
		if (w < h)
			HalfWidthYUpD->Value = w;
		else if (h < w)
			HalfWidthXUpD->Value = h;
	}
	else
	{
	}
}

void Form1::ImageEditBoxSetSubRangeCntxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "XStart",XSUBRANGE[0].ToString());
	SetReg("CCDLAB", "XEnd",XSUBRANGE[XSUBRANGE->Length-1].ToString());
	SetReg("CCDLAB", "YStart",YSUBRANGE[0].ToString());
	SetReg("CCDLAB", "YEnd",YSUBRANGE[YSUBRANGE->Length-1].ToString());
	MessageBox::Show(String::Concat("XStart = ",XSUBRANGE[0],"; XEnd = ",XSUBRANGE[XSUBRANGE->Length-1],"; YStart = ",YSUBRANGE[0], "; YEnd = ",YSUBRANGE[YSUBRANGE->Length-1]),"Image Loading Sub-Ranges Set");
}

void Form1::FMViewExtensionTable_Click(System::Object^  sender, System::EventArgs^  e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFilesPath");
	ofd->Filter = "FITS|*.fits;*.fit;*.fts;*.drift|All|*.*";
	ofd->Multiselect = false;
	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	SetReg("CCDLAB", "OpenFilesPath", ofd->FileName->Substring(0, ofd->FileName->LastIndexOf("\\")));
	JPFITS::FitsExtensionTableViewer^ view = gcnew FitsExtensionTableViewer(ofd->FileName);
}

void Form1::FMLoadSubFrame_Click(System::Object^  sender, System::EventArgs^  e)
{
	RangeDlg^ dlg = gcnew RangeDlg();
	dlg->XStartUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "XStart"));
	dlg->XEndUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "XEnd"));
	dlg->YStartUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "YStart"));
	dlg->YEndUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "YEnd"));
	dlg->ShowDialog();

	if (dlg->DialogResult == ::DialogResult::OK)
	{
		LOADSUBRANGE = true;
		SUBRANGE[0] = (int)dlg->XStartUpD->Value;
		SUBRANGE[1] = (int)dlg->XEndUpD->Value;
		SUBRANGE[2] = (int)dlg->YStartUpD->Value;
		SUBRANGE[3] = (int)dlg->YEndUpD->Value;
		SetReg("CCDLAB", "XStart",SUBRANGE[0].ToString());
		SetReg("CCDLAB", "XEnd",SUBRANGE[1].ToString());
		SetReg("CCDLAB", "YStart",SUBRANGE[2].ToString());
		SetReg("CCDLAB", "YEnd",SUBRANGE[3].ToString());
		FMLoad_Click(sender,e);
	}
	else
	{
		LOADSUBRANGE = false;
		SUBRANGE[0] = -1;
	}
}

void Form1::FMQuit_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	::DialogResult ans = MessageBox::Show("Are you sure you would like to Exit?","Program Exit Warning...",MessageBoxButtons::OKCancel);
	if (ans == ::DialogResult::OK)
		Application::Exit();

}

void Form1::FMReload_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	if (::MessageBox::Show( "Are you sure you want to reload the files and discard all/any changes?","Proceed?",::MessageBoxButtons::OKCancel) == ::DialogResult::OK)
	{
		AUTOLOADIMAGES = true;
		AUTOLOADIMAGESFILES = gcnew array<String^>(IMAGESET->Count);

		for (int i = 0; i < FileListDrop->Items->Count; i++)
			AUTOLOADIMAGESFILES[i] = IMAGESET[i]->FullFileName;

		IMAGESET = gcnew FITSImageSet();
		FMLoad_Click(sender, e);
		//FMLoad->PerformClick();
	}
}

void Form1::SaveFileDialog_FileOk(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e)
{
	String^ fullfile = SaveFileDlg->FileName;
	int q = fullfile->LastIndexOf("\\");
	String^ file = fullfile->Substring(q+1);
	FileListDrop->Items[FILELISTINDEX] = file;
	String^ ext = Path::GetExtension(fullfile);

	if (ext == ".fts" || ext == ".fit" || ext == ".fits")
		IMAGESET[FILELISTINDEX]->WriteImage(fullfile, FILESAVEPREC, true);
	if (ext == ".raw")//.raw
		IMAGESET[FILELISTINDEX]->WriteImage(fullfile, TypeCode::Int16, true);
	if (ext == ".jpg" || ext == ".jpeg")
	{
		if (IMAGESET[FILELISTINDEX]->Width < 256 || IMAGESET[FILELISTINDEX]->Height < 256)
		{
			System::Drawing::Bitmap^ bmp1 = gcnew System::Drawing::Bitmap(ImageWindow->Width, ImageWindow->Height);
			ImageWindow->DrawToBitmap(bmp1, ImageWindow->DisplayRectangle);
			bmp1->Save(fullfile,::Imaging::ImageFormat::Jpeg);
		}
		else
		{
			System::Drawing::Bitmap^ bmp1 = JPBitMap::ArrayToBmp(IMAGESET[FILELISTINDEX]->Image, ContrastScaleDrop->SelectedIndex, ColourMapDrop->SelectedIndex, InvertContrastChck->Checked, DIMCLIM, IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height, OPTIMGVIEWINVERTY);
			bmp1->Save(fullfile,::Imaging::ImageFormat::Jpeg);
		}
	}
	if (ext == ".zip")
	{
		String^ ziplist = CCDLABPATH + "tozip.txt";
		StreamWriter^ sw = gcnew StreamWriter(ziplist);
		sw->WriteLine(IMAGESET[FILELISTINDEX]->FullFileName);
		sw->Close();

		::Diagnostics::Process^ p = gcnew ::Diagnostics::Process();
		p->StartInfo->FileName = "c:\\Program Files\\7-Zip\\7z.exe";
		p->StartInfo->Arguments = "\"a\" " + "\"-tzip\" " + "\"" + fullfile + "\" " + "\"@" + ziplist;
		p->Start();
		p->WaitForExit();
		if (p->ExitCode != 0)
		{
			File::Delete(fullfile);
			return;
		}
	}

	SetReg("CCDLAB", "SaveFileDlgIndex", SaveFileDlg->FilterIndex.ToString());
}

void Form1::ViewNextBtn_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	int i = FILELISTINDEX;
	if (i == FileListDrop->Items->Count-1)
		i = 0;
	else
		i++;
	FileListDrop->SelectedIndex = i;
}

void Form1::ViewLastbtn_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	int i = FILELISTINDEX;
	if (i == 0)
		i = FileListDrop->Items->Count-1;
	else
		i--;
	FileListDrop->SelectedIndex = i;
}

void Form1::BlinkTimer_Tick(System::Object ^  sender, System::EventArgs ^  e)
{
	BlinkTimer->Interval = int(System::Convert::ToDouble(BlinkTime->Value)*1000) + 1;//+1 to avoid 0, 1 = 1ms
	ViewNextBtn_Click(sender,e);
}

void Form1::ContrastScaleDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (IMAGESET->Count == 0)
		return;

	int width = IMAGESET[FILELISTINDEX]->Width;
	int height = IMAGESET[FILELISTINDEX]->Height;
	SubImageSlideX->Maximum = width;
	SubImageSlideY->Maximum = height;
	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	FileTxtsUpD();
	StatTxtsUpD();
	SubImageStatsUpD();
	SubImageUpD();
}

void Form1::FMSave_Click(System::Object^  sender, System::EventArgs^  e) 
{
	SaveFileDlg->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFilesPath");
	SaveFileDlg->FilterIndex = ::Convert::ToInt32(GetReg("CCDLAB", "SaveFileDlgIndex"));
	SaveFileDlg->ShowDialog();
}

void Form1::InvertContrastChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (IMAGESET->Count == 0)
		return;

	int width = IMAGESET[FILELISTINDEX]->Width;
	int height = IMAGESET[FILELISTINDEX]->Height;
	SubImageSlideX->Maximum = width;
	SubImageSlideY->Maximum = height;
	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	FileTxtsUpD();
	StatTxtsUpD();
	SubImageStatsUpD();
	SubImageUpD();
}

void Form1::ScaleContrastChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (IMAGESET->Count == 0)
		return;
	
	SubImageStatsUpD();
	SubImageUpD();
}

void Form1::TBSaveBatch_Click(System::Object^  sender, System::EventArgs^  e) 
{
	WriteImageSet();
}

void Form1::TBZipAllBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ sfd = gcnew SaveFileDialog();
	sfd->Filter = "ZIP|*.zip";
	sfd->InitialDirectory = IMAGESET->GetCommonDirectory();
	sfd->FileName = sfd->InitialDirectory->Remove(sfd->InitialDirectory->LastIndexOf("\\"));
	sfd->FileName = sfd->FileName->Substring(sfd->FileName->LastIndexOf("\\") + 1);
	if (sfd->ShowDialog() == ::DialogResult::Cancel)
		return;

	String^ ziplist = CCDLABPATH + "tozip.txt";
	StreamWriter^ sw = gcnew StreamWriter(ziplist);
	for (int i = 0; i < IMAGESET->Count; i++)
		sw->WriteLine(IMAGESET[i]->FullFileName);
	sw->Close();

	::Diagnostics::Process^ p = gcnew ::Diagnostics::Process();
	p->StartInfo->FileName = "c:\\Program Files\\7-Zip\\7z.exe";
	p->StartInfo->Arguments = "\"a\" " + "\"-tzip\" " + "\"" + sfd->FileName + "\" " + "\"@" + ziplist;
	p->Start();
	p->WaitForExit();
	if (p->ExitCode != 0)
	{
		File::Delete(sfd->FileName);
		return;
	}

	if (TBZipMoveChck->Checked)
		for (int i = 0; i < IMAGESET->Count; i++)
			File::Delete(IMAGESET[i]->FullFileName);

	String^ pardir = Directory::GetParent(sfd->FileName)->FullName;
	if (Directory::Exists(pardir + "\\VIS") && Directory::Exists(pardir + "\\archive"))
		if (MessageBox::Show("Delete all intermediate UVIT reduction folders (excluding archive) under \r'" + pardir + "' ?", "Delete UVIT?", ::MessageBoxButtons::OKCancel) == ::DialogResult::OK)
		{
			array<String^>^ folds = Directory::GetDirectories(pardir);
			for (int i = 0; i < folds->Length; i++)
				if (!folds[i]->Contains("archive"))
					Directory::Delete(folds[i], true);
		}
}

void Form1::RelativeContrast_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
}

void Form1::FMFind_Click(System::Object ^  sender, System::EventArgs ^  e)
{
	FindFiles();
}

void Form1::FMViewFound_Click(System::Object^  sender, System::EventArgs^  e) 
{
	ViewFoundList();
}

void Form1::HeaderKeyTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	ListBox^ lb = (ListBox^)sender;

	if (e->Control && e->KeyCode == Keys::C)//copy
	{
		e->SuppressKeyPress = true;

		String^ str;
		CLIPBRDHEADERKEYS = gcnew array<String^>(lb->SelectedIndices->Count);
		CLIPBRDHEADERVALS = gcnew array<String^>(lb->SelectedIndices->Count);
		CLIPBRDHEADERCOMS = gcnew array<String^>(lb->SelectedIndices->Count);
		CLIPBRDHEADERINDS = gcnew array<int>(lb->SelectedIndices->Count);

		for (int i = 0; i < HeaderTxt->SelectedIndices->Count; i++)
		{
			str += IMAGESET[FILELISTINDEX]->Header->HeaderLine[lb->SelectedIndices[i]] + "\r\n";
			CLIPBRDHEADERKEYS[i] = IMAGESET[FILELISTINDEX]->Header->GetKeyName(lb->SelectedIndices[i]);
			CLIPBRDHEADERVALS[i] = IMAGESET[FILELISTINDEX]->Header->GetKeyValue(lb->SelectedIndices[i]);
			CLIPBRDHEADERCOMS[i] = IMAGESET[FILELISTINDEX]->Header->GetKeyComment(lb->SelectedIndices[i]);
			CLIPBRDHEADERINDS[i] = lb->SelectedIndices[i];
		}

		Clipboard::SetText(str);
	}

	if (e->Control && e->KeyCode == Keys::V)//paste
	{
		e->SuppressKeyPress = true;

		for (int i = 0; i < CLIPBRDHEADERKEYS->Length; i++)
		{
			//first check to see if the key exists
			int ind = IMAGESET[FILELISTINDEX]->Header->GetKeyIndex(CLIPBRDHEADERKEYS[i], false);
			//if it does then set the key
			if (ind != -1)
			{
				IMAGESET[FILELISTINDEX]->Header->SetKey(CLIPBRDHEADERKEYS[i], CLIPBRDHEADERVALS[i], CLIPBRDHEADERCOMS[i], false, 0);
				CLIPBRDHEADERINDS[i] = ind;
			}
			else
			{
				IMAGESET[FILELISTINDEX]->Header->AddKey(CLIPBRDHEADERKEYS[i], CLIPBRDHEADERVALS[i], CLIPBRDHEADERCOMS[i], CLIPBRDHEADERINDS[i]);
				CLIPBRDHEADERINDS[i] = IMAGESET[FILELISTINDEX]->Header->GetKeyIndex(CLIPBRDHEADERKEYS[i], CLIPBRDHEADERVALS[i], CLIPBRDHEADERCOMS[i]);
			}
		}

		FileTxtsUpD();
		HeaderTxt->SelectedIndices->Clear();

		for (int i = 0; i < CLIPBRDHEADERKEYS->Length; i++)
			HeaderTxt->SelectedIndex = CLIPBRDHEADERINDS[i];
	}

	if (e->Control && e->KeyCode == Keys::A)//select all
	{
		e->SuppressKeyPress = true;

		for (int i = 0; i < HeaderTxt->Items->Count; i++)
			HeaderTxt->SelectedIndex = i;
	}

	if (e->KeyCode == Keys::Delete)
	{
		e->SuppressKeyPress = true;
		/*if (MessageBox::Show("Remove the selected header lines?", "Warning...", MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;*/

		int ind0 = lb->SelectedIndices[0];

		for (int i = lb->SelectedIndices->Count - 1; i >= 0; i--)
		{
			if (!FITSImageHeader::VALIDKEYEDIT(IMAGESET[FILELISTINDEX]->Header->GetKeyName(lb->SelectedIndices[i])))
			{
				if (MessageBox::Show("Sorry, but this is a Restricted Key!  You don't have access.", "FITS Restriction: " + IMAGESET[FILELISTINDEX]->Header->GetKeyName(lb->SelectedIndices[i]), MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
					return;
			}
			else
				IMAGESET[FILELISTINDEX]->Header->RemoveKey(lb->SelectedIndices[i]);
		}

		FileTxtsUpD();
		HeaderTxt->SelectedIndex = ind0;
	}
}

void Form1::HeaderKeyTxt_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	ListBox^ lb = (ListBox^)sender;
	if (lb->SelectedIndices->Count == 0)
		HeaderCntxt->Close();

	if (e->Button == ::MouseButtons::Left)
	{
		array<int>^ inds = gcnew array<int>(lb->SelectedIndices->Count);
		for (int i = 0; i < inds->Length; i++)
			inds[i] = lb->SelectedIndices[i];
		int topi = lb->TopIndex;

		HeaderTxt->BeginUpdate();
		HeaderTxt->SelectedIndices->Clear();

		for (int i = 0; i < inds->Length; i++)
			HeaderTxt->SelectedIndex = inds[i];

		HeaderTxt->TopIndex = topi;
		HeaderTxt->EndUpdate();
	}

	if (e->Button == ::MouseButtons::XButton1)
		ViewLastbtn->PerformClick();
	if (e->Button == ::MouseButtons::XButton2)
		ViewNextBtn->PerformClick();
}

void Form1::HCPlotListValues_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "CCDLAB File List (*.CFL)|*.CFL";
	dlg->Title = "Select File List...";
	
	if (dlg->ShowDialog() == ::DialogResult::OK)
	{
		String^ file = dlg->FileName;
		FileStream^ fs2 = gcnew FileStream(file,System::IO::FileMode::Open,FileAccess::Read);
		StreamReader^ sr2 = gcnew StreamReader(fs2);
		int numlines = System::Convert::ToInt32(sr2->ReadLine());
		array<String^>^ filenames = gcnew array<String^>(numlines);
		for (int i = 0; i < numlines; i++)
			filenames[i] = sr2->ReadLine();

		sr2->Close();
		fs2->Close();

		int headinds = HeaderTxt->SelectedIndices->Count;
		array<String^>^ keys = gcnew array<String^>(headinds);
		for (int i = 0; i < headinds; i++)
			keys[i] = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]];

		PlotKeyList(keys, filenames);
	}
}

void Form1::HCPlotKeyValues_Click(System::Object^  sender, System::EventArgs^  e)
{
	int headinds = HeaderTxt->SelectedIndices->Count;
	array<String^>^ keys = gcnew array<String^>(headinds);
	
	for (int i = 0; i < headinds; i++)
		keys[i] = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]];

	PlotKeyList(keys, IMAGESET->FullFileNames);
}

void Form1::PlotKeyList(array<String^>^ keys, array<String^>^ filenames)
{
	array<double,2>^ allkeyvalues = gcnew array<double,2>(filenames->Length,keys->Length);
	JPFITS::FITSImage^ f;
	int FL = filenames->Length;
	int KL = keys->Length;

	ProgressBar->Maximum = FL;
	for (int i = 0; i < FL; i++)
	{
		f = gcnew FITSImage(filenames[i], nullptr, true, false, false, false);
		ProgressBar->Value = i+1;
		ProgressBar->Refresh();

		for (int j = 0; j < KL; j++)
		{
			try
			{
				allkeyvalues[i,j] = ::Convert::ToDouble(f->Header->GetKeyValue(keys[j]));
			}
			catch (System::FormatException^)
			{
				::MessageBox::Show("Key value not numeric, can not plot...","Error");
				ProgressBar->Value = 0;
				return;
			}
		}
	}
	ProgressBar->Value = 0;

	array<double>^ ydata = gcnew array<double>(FL);
	array<double>^ xdata = gcnew array<double>(FL);
	for (int i = 0; i < FL; i++)
		xdata[i] = i+1;

	for (int j = 0; j < KL; j++)
	{
		for (int i = 0; i < FL; i++)
		{
			ydata[i] = allkeyvalues[i,j];
		}

		JPPlot^ jpplot = gcnew JPPlot();
		jpplot->Text = keys[j];
		jpplot->PlotLine(xdata, ydata, "Image Number", keys[j] + ": " + f->Header->GetKeyComment(keys[j]), keys[j], Charting::SeriesChartType::Line, keys[j]);
	}
}

void Form1::HCCopyKeyValue_Click(System::Object^  sender, System::EventArgs^  e)
{
	int headinds = HeaderTxt->SelectedIndices->Count;
	array<String^>^ keys = gcnew array<String^>(headinds);
	
	for (int i = 0; i < headinds; i++)
		keys[i] = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]];

	CopyKeyList(keys, IMAGESET->FullFileNames);
}

void Form1::HCCopyListValue_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "CCDLAB File List (*.CFL)|*.CFL";
	dlg->Title = "Select File List...";
	
	if (dlg->ShowDialog() == ::DialogResult::OK)
	{
		String^ file = dlg->FileName;
		FileStream^ fs2 = gcnew FileStream(file,System::IO::FileMode::Open,FileAccess::Read);
		StreamReader^ sr2 = gcnew StreamReader(fs2);
		int numlines = System::Convert::ToInt32(sr2->ReadLine());
		array<String^>^ filenames = gcnew array<String^>(numlines);
		for (int i = 0; i < numlines; i++)
			filenames[i] = sr2->ReadLine();

		sr2->Close();
		fs2->Close();

		int headinds = HeaderTxt->SelectedIndices->Count;
		array<String^>^ keys = gcnew array<String^>(headinds);
		for (int i = 0; i < headinds; i++)
			keys[i] = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]];

		CopyKeyList(keys, filenames);
	}
}

void Form1::CopyKeyList(array<String^>^ keys, array<String^>^ filenames)
{
	String^ list = "";
	
	JPFITS::FITSImage^ f;

	for (int j = 0; j < filenames->Length; j++)
	{
		f = gcnew FITSImage(filenames[j],nullptr,true,false,false, false);

		for (int i = 0; i < keys->Length - 1; i++)
			list += f->Header->GetKeyValue(keys[i]) + "	";//tab delimit;

		list += f->Header->GetKeyValue(keys[keys->Length-1]);

		if (j < filenames->Length - 1)
			list += Environment::NewLine;
	}

	::Clipboard::SetText(list);
	::MessageBox::Show("Key value copied to clipboard...","Copy");
}

void Form1::HCExtractKeyValue_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int headinds = HeaderTxt->SelectedIndices->Count;
	array<String^>^ keys = gcnew array<String^>(headinds);
	
	for (int i = 0; i < headinds; i++)
		keys[i] = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]];

	ExtractKeyList(keys, IMAGESET->FullFileNames);
}

void Form1::HCExtractListValues_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "CCDLAB File List (*.CFL)|*.CFL";
	dlg->Title = "Select File List...";
	
	if (dlg->ShowDialog() == ::DialogResult::OK)
	{
		String^ file = dlg->FileName;
		FileStream^ fs2 = gcnew FileStream(file,System::IO::FileMode::Open,FileAccess::Read);
		StreamReader^ sr2 = gcnew StreamReader(fs2);
		int numlines = System::Convert::ToInt32(sr2->ReadLine());
		array<String^>^ filenames = gcnew array<String^>(numlines);
		for (int i = 0; i < numlines; i++)
			filenames[i] = sr2->ReadLine();

		sr2->Close();
		fs2->Close();

		int headinds = HeaderTxt->SelectedIndices->Count;
		array<String^>^ keys = gcnew array<String^>(headinds);
		for (int i = 0; i < headinds; i++)
			keys[i] = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]];

		ExtractKeyList(keys, filenames);
	}
}

void Form1::ExtractKeyList(array<String^>^ keys, array<String^>^ filenames)
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	SaveFileDialog^ dlg = gcnew SaveFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "Tab Delimited Text File (*.txt)|*.txt";
	dlg->Title = "Save Key Values to Text File...";

	if (dlg->ShowDialog() == ::DialogResult::OK)
	{
		array<String^,2>^ list = gcnew array<String^,2>(keys->Length+1,filenames->Length+1);
		list[0,0] = String::Concat("File","	");//tab delimited
		for (int i = 0; i < keys->Length; i++)
			list[i+1,0] = String::Concat(keys[i],"	");//tab delimited

		JPFITS::FITSImage^ f;

		ProgressBar->Maximum = filenames->Length;
		for (int j = 1; j < filenames->Length+1; j++)
		{
			f = gcnew FITSImage(filenames[j - 1], nullptr, true, false, false, false);

			ProgressBar->Value = j;
			ProgressBar->Refresh();

			list[0,j] = String::Concat(f->FileName,"	");//tab delimit
			for (int i = 1; i < keys->Length+1; i++)
			{
				list[i,j] = String::Concat(f->Header->GetKeyValue(keys[i-1]),"	");//tab delimit;
			}
		}
		ProgressBar->Value = 0;

		FileStream^ fs = gcnew FileStream(dlg->FileName,System::IO::FileMode::Create,FileAccess::Write);
		StreamWriter^ sw = gcnew StreamWriter(fs);

		for (int i = 0; i < filenames->Length+1; i++)
		{
			for (int j = 0; j < keys->Length+1; j++)
			{
				sw->Write(list[j,i]);
			}
			sw->WriteLine();
		}
		sw->Flush();
		sw->Close();
		fs->Close();
	}
}

void Form1::HeaderCntxtMenu_Click(System::Object^  sender, System::EventArgs^  e)
{
	//if (sender->Equals(
}

void Form1::EMFileBias_Click(System::Object^  sender, System::EventArgs^  e) 
{
	SubBiasChck->Checked = true;
}

void Form1::EMBatchFlat_Click(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::AutoRegBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	int refim = 0;//(int)(RegRefIndex->Value-1);//reference image
	bool dostats = true;//possibly false if auto-batch

	if (!IMAGESET->CoDimensional)
	{
		::MessageBox::Show("Cannot register non co-dimensional images","Error");
		return;
	}

	IMAGESET->Register(IMAGESET,refim,dostats);
	FileListDrop_SelectedIndexChanged(sender,e);
}

void Form1::HCEdit_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int ind = HeaderTxt->SelectedIndex;
	if (ind >= 0)
	{
		bool valid = FITSImageHeader::VALIDKEYEDIT(IMAGESET[FILELISTINDEX]->Header->HeaderKeys[ind]);
		//ValidKeyChck();
		if (valid == true)
		{
			EditKeyDlg^ ekd = gcnew EditKeyDlg();
			if (IMAGESET[FILELISTINDEX]->Header->HeaderLineIsComment[ind])
			{
				ekd->CommentKeyLineTxt->Visible = true;
				ekd->CommentKeyLineTxt->BringToFront();
				ekd->CommentKeyLineTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeyComments[ind]->Trim();
				ekd->label1->Text = "Comment Line";
				ekd->label2->Visible = false;
				ekd->label3->Visible = false;
			}
			else
			{
				ekd->KeyNameTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[ind];
				ekd->KeyValueTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeyValues[ind];
				ekd->KeyCommentTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeyComments[ind];
			}

			ekd->ShowDialog();

			if (ekd->DialogResult == System::Windows::Forms::DialogResult::OK)
			{
				if (IMAGESET[FILELISTINDEX]->Header->HeaderLineIsComment[ind])
					IMAGESET[FILELISTINDEX]->Header->HeaderKeyComments[ind] = ekd->CommentKeyLineTxt->Text;
				else
				{
					IMAGESET[FILELISTINDEX]->Header->HeaderKeys[ind] = ekd->KeyNameTxt->Text;
					IMAGESET[FILELISTINDEX]->Header->HeaderKeyValues[ind] = ekd->KeyValueTxt->Text;
					IMAGESET[FILELISTINDEX]->Header->HeaderKeyComments[ind] = ekd->KeyCommentTxt->Text;
				}

				int topi = HeaderTxt->TopIndex;
				HeaderTxt->BeginUpdate();
				HeaderTxt->Items->Clear();
				HeaderTxt->Items->AddRange(IMAGESET[FILELISTINDEX]->Header->GetFormattedHeaderBlock(false, true));
				HeaderTxt->SelectedIndex = ind;
				HeaderTxt->TopIndex = topi;
				HeaderTxt->EndUpdate();
			}
		}
		else
		{
			::MessageBox::Show("Sorry, but this is a Restricted Key!  You don't have access.","FITS Restriction...");
		}
	}
}

void Form1::HCEditAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	int ind = HeaderTxt->SelectedIndex;
	if (ind < 0)
		return;
	bool valid = FITSImageHeader::VALIDKEYEDIT(IMAGESET[FILELISTINDEX]->Header->HeaderKeys[ind]);
	if (!valid)
	{
		::MessageBox::Show("Sorry, but this is a Restricted Key!  You don't have access.", "FITS Restriction...");
		return;
	}

	EditKeyDlg^ ekd = gcnew EditKeyDlg();
	ekd->KeyNameTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeys[ind];
	ekd->KeyValueTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeyValues[ind];
	ekd->KeyCommentTxt->Text = IMAGESET[FILELISTINDEX]->Header->HeaderKeyComments[ind];
	ekd->ShowDialog();

	if (ekd->DialogResult == System::Windows::Forms::DialogResult::Cancel)
		return;

	ProgressBar->Maximum = IMAGESET->Count;
	for (int j = 0; j < IMAGESET->Count; j++)
	{
		ProgressBar->Value++;
		ProgressBar->Refresh();
		IMAGESET[j]->Header->HeaderKeys[ind] = ekd->KeyNameTxt->Text;
		IMAGESET[j]->Header->HeaderKeyValues[ind] = ekd->KeyValueTxt->Text;
		IMAGESET[j]->Header->HeaderKeyComments[ind] = ekd->KeyCommentTxt->Text;
	}
	ProgressBar->Value = 0;

	int topi = HeaderTxt->TopIndex;
	HeaderTxt->BeginUpdate();
	HeaderTxt->Items->Clear();
	HeaderTxt->Items->AddRange(IMAGESET[FILELISTINDEX]->Header->GetFormattedHeaderBlock(false, true));
	HeaderTxt->SelectedIndex = ind;
	HeaderTxt->TopIndex = topi;
	HeaderTxt->EndUpdate();
}

void Form1::HCInsertCurrent_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int index = HeaderTxt->SelectedIndex;

	EditKeyDlg^ ekd = gcnew EditKeyDlg();
	ekd->CommentKeyLineChck->Visible = true;
	if (ekd->ShowDialog() == ::DialogResult::Cancel)
		return;
	bool iscommentline = ekd->CommentKeyLineChck->Checked;

	if (iscommentline)
		IMAGESET[FILELISTINDEX]->Header->AddCommentKeyLine(ekd->CommentKeyLineTxt->Text, index);
	else
	{
		if (!FITSImageHeader::VALIDKEYEDIT(ekd->KeyNameTxt->Text) || IMAGESET[FILELISTINDEX]->Header->GetKeyIndex(ekd->KeyNameTxt->Text, false) != -1)
		{
			::MessageBox::Show("Sorry, but this is either a restricted key or it already exists! Can Not Insert.", "FITS Restriction...");
			return;
		}

		IMAGESET[FILELISTINDEX]->Header->AddKey(ekd->KeyNameTxt->Text, ekd->KeyValueTxt->Text, ekd->KeyCommentTxt->Text, index);
	}

	HeaderTxt->Items->Clear();
	HeaderTxt->Items->AddRange(IMAGESET[FILELISTINDEX]->Header->GetFormattedHeaderBlock(false, true));
	HeaderTxt->SelectedIndex = index;
}

void Form1::HCInsertBatch_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int index = HeaderTxt->SelectedIndex;

	EditKeyDlg^ ekd = gcnew EditKeyDlg();
	ekd->CommentKeyLineChck->Visible = true;
	if (ekd->ShowDialog() == ::DialogResult::Cancel)
		return;
	bool iscommentline = ekd->CommentKeyLineChck->Checked;
	
	ProgressBar->Maximum = IMAGESET->Count;
	for (int j = 0; j < IMAGESET->Count; j++)
	{
		ProgressBar->Value++;
		ProgressBar->Refresh();

		if (iscommentline)
			IMAGESET[j]->Header->AddCommentKeyLine(ekd->CommentKeyLineTxt->Text, index);
		else
		{
			if (!FITSImageHeader::VALIDKEYEDIT(ekd->KeyNameTxt->Text) || IMAGESET[j]->Header->GetKeyIndex(ekd->KeyNameTxt->Text, false) != -1)
			{
				::MessageBox::Show("Sorry, but this is either a restricted key or it already exists! Can Not Insert for image " + (j + 1) + ".", "FITS Restriction...");
				continue;
			}

			IMAGESET[j]->Header->AddKey(ekd->KeyNameTxt->Text, ekd->KeyValueTxt->Text, ekd->KeyCommentTxt->Text, index);
		}
		
	}
	ProgressBar->Value = 0;

	HeaderTxt->Items->Clear();
	HeaderTxt->Items->AddRange(IMAGESET[FILELISTINDEX]->Header->GetFormattedHeaderBlock(false, true));
	HeaderTxt->SelectedIndex = index;
}

void Form1::HCInsertSelectedToOthers_Click(System::Object^  sender, System::EventArgs^  e)
{
	for (int j = 0; j < HeaderTxt->SelectedIndices->Count; j++)
		for (int i = 0; i < IMAGESET->Count; i++)
			if (i == FILELISTINDEX)
				continue;
			else
				IMAGESET[i]->Header->SetKey(IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[j]], IMAGESET[FILELISTINDEX]->Header->HeaderKeyValues[HeaderTxt->SelectedIndices[j]], IMAGESET[FILELISTINDEX]->Header->HeaderKeyComments[HeaderTxt->SelectedIndices[j]], true, HeaderTxt->SelectedIndices[j]);
}

void Form1::HCRemoveCurrent_Click(System::Object^  sender, System::EventArgs^  e) 
{
	for (int i = HeaderTxt->SelectedIndices->Count - 1; i >= 0; i--)
		if (FITSImageHeader::VALIDKEYEDIT(IMAGESET[FILELISTINDEX]->Header->HeaderKeys[HeaderTxt->SelectedIndices[i]]))
			IMAGESET[FILELISTINDEX]->Header->RemoveKey(HeaderTxt->SelectedIndices[i]);

	HeaderTxt->Items->Clear();
	HeaderTxt->Items->AddRange(IMAGESET[FILELISTINDEX]->Header->GetFormattedHeaderBlock(false, true));
}

void Form1::HCRemoveBatch_Click(System::Object^  sender, System::EventArgs^  e) 
{
	
}

void Form1::ManRegBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		if (!MANREG_CONTINUE && !UVITMANREG_CONTINUE)
		{
			if (MessageBox::Show("Please select point sources (left-click) which stay within the field of view for the duration of the image set!  RIGHT-CLICK when done.","Know what you're doing...",::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			{
				MANREG_CONTINUE = false;
				UVITMANREG_CONTINUE = false;
				DOMANREG = false;
				DOUVITMANREG = false;
				if (IMAGESET->Count == 1)
					ImageBatchRedxnPnl->Enabled = false;
				return;
			}

			if (XDRIFT_PLOT != nullptr)
				if (!XDRIFT_PLOT->IsDisposed)
					XDRIFT_PLOT->Close();
			if (YDRIFT_PLOT != nullptr)
				if (!YDRIFT_PLOT->IsDisposed)
					YDRIFT_PLOT->Close();

			IWLCK = false;//allow cursor box to move
			DOMANREG = true;
			ImageWindow->Cursor->Hide();

			EqualHWChck->Checked = true;
			HalfWidthXUpD->Value = ManRegTrkHWUpD->Value;

			FNDCOORDS = gcnew array<int,2>(1,2);//this is for plotting the local max point in the ROI
			FNDCOORDRECTS = gcnew array<Rectangle,1>(1);
			MANREGCOORDS = gcnew array<int,2>(0,0);
			MANREGCOORDRECTS = gcnew array<Rectangle,1>(0);

			ShowFoundCoordsChck->Checked = true;//this is for plotting the local max point in the ROI

			FileListDrop->SelectedIndex = 0;

			return;
		}
		if (MANREG_CONTINUE && !UVITMANREG_CONTINUE)
		{
			DOMANREG = false;
			MANREG_CONTINUE = false;
			UVITMANREG_CONTINUE = false;

			if (MANREGCOORDRECTS->Length == 0)//right-clicked out with no point selections, meaning quitting.  Reset swithces
			{
				return;
			}

			if (MessageBox::Show("Continue?","Image Registration...",::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			{
				ShowFoundCoordsChck->Checked = false;//this is for plotting the local max point in the ROI
				ImageWindow->Refresh();
				return;
			}

			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = 100;
			WAITBAR->Text = "Point Source Registration...";
			ManRegWrkr->RunWorkerAsync();
			WAITBAR->ShowDialog();

			return;
		}
		if (!MANREG_CONTINUE && UVITMANREG_CONTINUE)
		{
			ImageBatchRedxnPnl->Enabled = false;
			MANREG_CONTINUE = false;

			if (MANREGCOORDRECTS->Length == 0)//right-clicked out with no point selections, meaning quitting.  Reset swithces
			{
				UVITMANREGDIRLISTINDEX = 0;
				DOUVITMANREG = false;
				UVITMANREG_CONTINUE = false;
				return;
			}

			if (MessageBox::Show("Proceed with drift tracking?", "Drift Registration...", ::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			{	
				DOMANREG = false;
				UVITMANREG_CONTINUE = false;
				ShowFoundCoordsChck->Checked = false;//this is for plotting the local max point in the ROI
				ImageWindow->Refresh();
				return;
			}
			else
			{
				UVITMANREG_CONTINUE = true;
			}

			DOMANREG = false;
			CreateDriftFromINTMenuItem_Click(sender,e);
			return;
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}
}

void Form1::ManRegWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	bool UVITdisplay = PointSrcINTDriftDisplayChck->Checked;
	int UVITdisplaycadence = Convert::ToInt32(PointSrcINTDriftDisplayCadenceDrop->SelectedItem);

	int i;
	try
	{
		int SRC_HW = (int)ManRegSrcHWUpD->Value;
		array<double, 2>^ src = gcnew array<double, 2>(SRC_HW * 2 + 1, SRC_HW * 2 + 1);
		array<double, 2>^ src_X = gcnew array<double, 2>(SRC_HW * 2 + 1, SRC_HW * 2 + 1);
		array<double, 2>^ src_Y = gcnew array<double, 2>(SRC_HW * 2 + 1, SRC_HW * 2 + 1);
		int TRK_HW = (int)ManRegTrkHWUpD->Value;
		array<double, 2>^ box = gcnew array<double, 2>(TRK_HW * 2 + 1, TRK_HW * 2 + 1);
		array<double, 2>^ box_X = gcnew array<double, 2>(TRK_HW * 2 + 1, TRK_HW * 2 + 1);
		array<double, 2>^ box_Y = gcnew array<double, 2>(TRK_HW * 2 + 1, TRK_HW * 2 + 1);

		int NSrc = MANREGCOORDS->GetLength(0);
		int Nim;
		if (DO_UVITDRIFTFILES)
			Nim = UVITMANREGFILELIST->Length;
		else
			Nim = IMAGESET->FullFileNames->Length;

		MANREGCENTROIDS = gcnew array<double, 3>(NSrc, 2, Nim);
		if (DO_UVITDRIFTFILES)
		{
			UVITINTMODEDRIFTPOLYPOINTS = gcnew array<System::Drawing::Point, 2>(MANREGCENTROIDS->GetLength(0), MANREGCENTROIDS->GetLength(2));
			UVITINTDRIFT_MAXDEV_INDEX = -1;
		}

		FITSImage^ img;
		int intprog = 0, ntrackdivergingimgs = 0, ntracksremoved = 0;
		for (i = 0; i < Nim; i++)
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			{
				if (DO_UVITDRIFTFILES)
					UVITBADTRACK = true;
				return;
			}

			if (100*i/Nim > intprog)
			{
				intprog = 100*i/Nim;
				ManRegWrkr->ReportProgress(intprog);
			}

			if (DO_UVITDRIFTFILES)
			{
				img = SPAREFITSImageSet[i];
				UVITMANREGFILELIST_TIMES[i] = ::Convert::ToDouble(img->Header->GetKeyValue("FRMTIME")) * 1000;
			}
			else
				img = IMAGESET[i];//loaded images

			for (int j = 0; j < NSrc; j++)
			{
				//create a box around the coords
				for (int k = -TRK_HW; k <= TRK_HW; k++)
					for (int l = -TRK_HW; l <= TRK_HW; l++)
					{
						box[k + TRK_HW, l + TRK_HW] = img[MANREGCOORDS[j, 0] + k, MANREGCOORDS[j, 1] + l];
						box_X[k + TRK_HW, l + TRK_HW] = double(MANREGCOORDS[j, 0] + k);
						box_Y[k + TRK_HW, l + TRK_HW] = double(MANREGCOORDS[j, 1] + l);
					}

				//do background subtraction here
				if (!DO_UVITDRIFTFILES)//not needed for UVIT VIS files
					box = JPMath::MatrixSubScalar(box, JPMath::Median(box), false);       //= JPMath::MatrixSubScalar(box, JPMath::Min(box, true));//median or min?

				//now make a little centroid box
				int xm = 0, ym = 0;
				JPMath::Max(box, xm, ym, false);
				if (xm - SRC_HW < 0)
					xm = TRK_HW;
				if (ym - SRC_HW < 0)
					ym = TRK_HW;
				if (xm + SRC_HW > TRK_HW * 2)
					xm = TRK_HW;
				if (ym + SRC_HW > TRK_HW * 2)
					ym = TRK_HW;

				for (int k = -SRC_HW; k <= SRC_HW; k++)
					for (int l = -SRC_HW; l <= SRC_HW; l++)
					{
						src[k + SRC_HW, l + SRC_HW] = box[xm + k, ym + l];
						src_X[k + SRC_HW, l + SRC_HW] = box_X[xm + k, ym + l];
						src_Y[k + SRC_HW, l + SRC_HW] = box_Y[xm + k, ym + l];
					}

				double energy = JPMath::Sum(src, false);

				double x = JPMath::Sum(JPMath::MatrixMultMatrix(src, src_X, false), false) / energy;
				double y = JPMath::Sum(JPMath::MatrixMultMatrix(src, src_Y, false), false) / energy;

				if (int(x) < TRK_HW || int(x) > img->Width - TRK_HW)
					x = MANREGCENTROIDS[j, 0, i - 1];
				if (int(y) < TRK_HW || int(y) > img->Height - TRK_HW)
					y = MANREGCENTROIDS[j, 1, i - 1];

				MANREGCOORDS[j, 0] = int(x);//update position for tracking
				MANREGCOORDS[j, 1] = int(y);

				MANREGCENTROIDS[j, 0, i] = x;
				MANREGCENTROIDS[j, 1, i] = y;

				if (DO_UVITDRIFTFILES)
					UVITINTMODEDRIFTPOLYPOINTS[j, i] = System::Drawing::Point(int(MANREGCENTROIDS[j, 0, i] * xsc), int(MANREGCENTROIDS[j, 1, i] * ysc));
			}

			//check for point source tracks which are going divergent and remove them from the tracking arrays...if there are more than a few tracks
			if (NSrc >= 3 && DO_UVITDRIFTFILES)
			{
				array<double>^ currdrifts = gcnew array<double>(NSrc);
				for (int j = 0; j < NSrc; j++)
					currdrifts[j] = Math::Sqrt((MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) * (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) + (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]) * (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]));
				double currdriftmed = JPMath::Median(currdrifts);
				int divergingindex = -1;
				double divergpix = 0.5;
				for (int j = 0; j < NSrc; j++)
					if (Math::Abs(currdrifts[j] - currdriftmed) > divergpix)
					{
						ntrackdivergingimgs++;
						divergingindex = j;//assume this is constant...or if changes will be picked up again anyway
						break;
					}
				if (ntrackdivergingimgs > 5)//then remove the bad one divergingindex
				{
					ntracksremoved++;
					WAITBAR->Text = "Point Source (" + (MANREGCOORDS->GetLength(0) - 1) + ") Drift Tracking Directory " + (UVITMANREGDIRLISTINDEX + 1).ToString() + " of " + UVITMANREGDIRLIST->Length.ToString() + " (Removed " + ntracksremoved + " sources)";
					ntrackdivergingimgs = 0;//reset so doesnt keep firing
					NSrc -= 1;
					array<int, 2>^ tempMANREGCOORDS = gcnew array<int, 2>(NSrc, 2);
					int c = 0;
					for (int j = 0; j <= NSrc; j++)
						if (j != divergingindex)
						{
							tempMANREGCOORDS[c, 0] = MANREGCOORDS[j, 0];
							tempMANREGCOORDS[c, 1] = MANREGCOORDS[j, 1];
							c++;
						}
					MANREGCOORDS = gcnew array<int, 2>(NSrc, 2);
					for (int j = 0; j < NSrc; j++)
					{
						MANREGCOORDS[j, 0] = tempMANREGCOORDS[j, 0];
						MANREGCOORDS[j, 1] = tempMANREGCOORDS[j, 1];
					}

					array<double, 3>^ tempMANREGCENTROIDS = gcnew array<double, 3>(NSrc, 2, Nim);
					array<System::Drawing::Point, 2>^ tempUVITINTMODEDRIFTPOLYPOINTS = gcnew array<System::Drawing::Point, 2>(NSrc, Nim);
					for (int ii = 0; ii <= i; ii++)
					{
						c = 0;
						for (int j = 0; j <= NSrc; j++)
							if (j != divergingindex)
							{
								tempMANREGCENTROIDS[c, 0, ii] = MANREGCENTROIDS[j, 0, ii];
								tempMANREGCENTROIDS[c, 1, ii] = MANREGCENTROIDS[j, 1, ii];
								tempUVITINTMODEDRIFTPOLYPOINTS[c, ii] = UVITINTMODEDRIFTPOLYPOINTS[j, ii];
								c++;
							}
					}
					MANREGCENTROIDS = gcnew array<double, 3>(NSrc, 2, Nim);
					UVITINTMODEDRIFTPOLYPOINTS = gcnew array<System::Drawing::Point, 2>(NSrc, Nim);
					for (int ii = 0; ii <= i; ii++)
						for (int j = 0; j < NSrc; j++)
						{
							MANREGCENTROIDS[j, 0, ii] = tempMANREGCENTROIDS[j, 0, ii];
							MANREGCENTROIDS[j, 1, ii] = tempMANREGCENTROIDS[j, 1, ii];
							UVITINTMODEDRIFTPOLYPOINTS[j, ii] = tempUVITINTMODEDRIFTPOLYPOINTS[j, ii];
						}
				}
			}

			if (DO_UVITDRIFTFILES && UVITdisplay && Math::IEEERemainder((double)i, (double)UVITdisplaycadence) == 0)
				ImageUpD(SPAREFITSImageSet[i]->Image);

			if (i > 0 && !DO_UVITDRIFTFILES)
			{
				double x_drift = 0;
				double y_drift = 0;
				for (int j = 0; j < NSrc; j++)
				{
					x_drift += MANREGCENTROIDS[j,0,i] - MANREGCENTROIDS[j,0,0];
					y_drift += MANREGCENTROIDS[j,1,i] - MANREGCENTROIDS[j,1,0];
				}
				x_drift /= NSrc;
				y_drift /= NSrc;

				IMAGESET[i]->Image = JPMath::ShiftArrayInt(IMAGESET[i]->Image, -(int)Math::Round(x_drift), -(int)Math::Round(y_drift), true);
			}
		}
	}
	catch (Exception^ e)
	{
		if (DO_UVITDRIFTFILES)
		{
			UVITINTDRIFT_MAXDEV_INDEX = -1;
			ImageWindow->Refresh();

			array<String^>^ ref = gcnew array<String^>(1) { UVITMANREGFILELIST[i] };
			AddToImageSet(ref, false);
			MainTab->SelectedIndex = 0;
			ImageBatchRedxnPnl->Enabled = true;
			ContrastWideRad->PerformClick();
			UVITBADTRACK = true;			
		}
		MessageBox::Show("One of the point sources is probably not trackable (too low S/N).  File: " + (i+1).ToString() + "\r\n \r\n \r\n" + e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite, "Error...");
		MessageBox::Show(MANREGCOORDS[0, 0].ToString() + "	" +  MANREGCOORDS[0, 1]);
		WAITBAR->CancelBtn->PerformClick();
	}
}

void Form1::ManRegWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat("Completed: ",e->ProgressPercentage,"%");
	WAITBAR->Refresh();
}

void Form1::ManRegWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		WAITBAR->Close();
		Form1::Enabled = true;
		Form1::BringToFront();

		if (UVITBADTRACK)
		{
			SPAREFITSImageSet->Clear();
			UVITBADTRACK = false;
			::DialogResult res = MessageBox::Show("Retry point source tracking?", "Error...", MessageBoxButtons::YesNo);
			if (res == ::DialogResult::Yes)
			{
				CreateDriftFromINTMenuItem_Click(sender, gcnew System::EventArgs);
				return;
			}
			else
			{
				UVITINTMODEDRIFTPOLYPOINTS = nullptr;
				ImageWindow->Refresh();
			}
		}

		DOUVITMANREG = false;
		UVITMANREGFILELIST_TIMES = nullptr;
		UVITMANREGFILELIST = nullptr;
		UVITMANREGDIRLISTINDEX = 0;
		return;
	}

	try
	{
		if (!DO_UVITDRIFTFILES)
		{
			WAITBAR->Close();
			Form1::Enabled = true;
		}

		if (DO_UVITDRIFTFILES)
		{
			ImageWindow->Refresh();
			SPAREFITSImageSet->Clear();

			array<Object^>^ arg = gcnew array<Object^>(2);
			arg[0] = (Object^)UVITMANREGFILELIST;
			arg[1] = (Object^)CrossCorrINTDriftChck->Checked;
			DriftFromINTWrkr->RunWorkerAsync(arg);
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}

}

void Form1::ReplaceImagePtsDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (FileListDrop->Items->Count == 0)
		return;

	if (ReplaceImagePtsDrop->SelectedIndex == 0)//manual value
		ReplaceImagePtsTxt->Enabled = true;

	if (ReplaceImagePtsDrop->SelectedIndex == 1)//image min value
	{
		ReplaceImagePtsTxt->Enabled = false;
		ReplaceImagePtsTxt->Text = IMAGESET[FILELISTINDEX]->Min.ToString();
	}
	if (ReplaceImagePtsDrop->SelectedIndex == 2)//image max value
	{
		ReplaceImagePtsTxt->Enabled = false;
		ReplaceImagePtsTxt->Text = IMAGESET[FILELISTINDEX]->Max.ToString();
	}
	if (ReplaceImagePtsDrop->SelectedIndex == 3)//image median value
	{
		ReplaceImagePtsTxt->Enabled = false;
		ReplaceImagePtsTxt->Text = IMAGESET[FILELISTINDEX]->Median.ToString();
	}
	if (ReplaceImagePtsDrop->SelectedIndex == 4)//image mean value
	{
		ReplaceImagePtsTxt->Enabled = false;
		ReplaceImagePtsTxt->Text = IMAGESET[FILELISTINDEX]->Mean.ToString();
	}
}

void Form1::XBinUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	YBinUpD->Value = XBinUpD->Value;
	SetReg("CCDLAB", "XBinUpD", XBinUpD->Value.ToString());
}

void Form1::YBinUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "YBinUpD", YBinUpD->Value.ToString());
}

void Form1::SCMChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if ( SCMChck->Checked == true )
		ScmTxt->Enabled = true;
	else
		ScmTxt->Enabled = false;
}

void Form1::textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) 
{
}

void Form1::Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
}

void Form1::TBDestructTimer_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	if (Form1::BackColor == ::Drawing::Color::Gainsboro)
		Form1::BackColor = ::Drawing::Color::Red;
	else
		Form1::BackColor = ::Drawing::Color::Gainsboro;
}

void Form1::TaskBarCntxtMenu_MouseEnter(System::Object^  sender, System::EventArgs^  e) 
{
	TBDestructTimer->Enabled = true;
}

void Form1::TaskBarCntxtMenu_MouseLeave(System::Object^  sender, System::EventArgs^  e) 
{
	TBDestructTimer->Enabled = false;
}

void Form1::TaskBarCntxtMenu_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
	Application::Exit();
}

void Form1::centerToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	SubImageSlideX->Value = (int)(IMAGESET[FILELISTINDEX]->Width/2);
	SubImageSlideY->Value = (int)(IMAGESET[FILELISTINDEX]->Height/2);
	SubImageStatsUpD();
	SubImageUpD();
	ImageWindow->Refresh();
}

void Form1::SubImageSurfFacet_Click(System::Object^  sender, System::EventArgs^  e)
{
	/*double xstart = (double)XSUBRANGE[0];
	double xend = (double)XSUBRANGE[XSUBRANGE->Length - 1];
	double ystart = (double)YSUBRANGE[0];
	double yend = (double)YSUBRANGE[YSUBRANGE->Length - 1];
	FITSImage^ ff = gcnew FITSImage(CCDLABPATH + "\\surf.fits", SUBIMAGE, false);
	ff->WriteImage(TypeCode::Double);

	String^ pypath = (String^)GetReg("CCDLAB", "PythonExePath");
	::Diagnostics::ProcessStartInfo^ psi = gcnew ::Diagnostics::ProcessStartInfo();
	psi->FileName = pypath;

	String^ script = "D:\\Documents\\Visual Studio 2019\\Projects 2019\\Python Scripts\\Surface Plot matplotlib\\surface.py";
	//psi->Arguments = String::Format("\"" + script + "\"");

	psi->Arguments = String::Format("\"" + script + "\"" + " {0} {1} {2} {3} {4}", "\"" + ff->FullFileName + "\"", xstart, xend, ystart, yend);

	psi->UseShellExecute = false;
	psi->CreateNoWindow = true;
	psi->RedirectStandardError = true;
	psi->RedirectStandardOutput = true;
	String^ errs = "";
	String^ res = "";
	::Diagnostics::Process^ proc = ::Diagnostics::Process::Start(psi);*/
	//proc->WaitForExit();

	/*errs = proc->StandardError->ReadToEnd();
	res = proc->StandardOutput->ReadToEnd();
	MessageBox::Show(errs + "\r\n" + res);*/



	/*if (!toolStripMenuItem1->Checked)
		return;*/

	Form1::Enabled = false;
	SurfWrkr->RunWorkerAsync(1);
}

void Form1::SubImageSurfSmooth_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	SurfWrkr->RunWorkerAsync(2);
}

void Form1::SubImageSurfMetal_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	SurfWrkr->RunWorkerAsync(3);
}

void Form1::SubImageSurfMesh_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	SurfWrkr->RunWorkerAsync(4);
}

void Form1::SubImSurfColumnMenuBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	SurfWrkr->RunWorkerAsync(5);
}

void Form1::SurfWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	try
	{
		int type = ::Convert::ToInt32(e->Argument);
		MLSURF = gcnew MLCCDLAB::MLSurface;

		MWNumericArray^ x = gcnew MWNumericArray(1,XSUBRANGE->Length,XSUBRANGE);
		MWNumericArray^ y = gcnew MWNumericArray(1,YSUBRANGE->Length,YSUBRANGE);
		MWNumericArray^ z = gcnew MWNumericArray(SUBIMAGE);
		switch (type)
		{
			case (1):
			{
				MLSURF->Surf_Facet(x,y,z);
				break;
			}
			case (2):
			{
				MLSURF->Surf_Smooth(x,y,z);
				break;
			}
			case (3):
			{
				MLSURF->Surf_Metal(x,y,z);
				break;
			}
			case (4):
			{
				MLSURF->Surf_Mesh(x,y,z);
				break;
			}
			case (5):
			{
				MLSURF->Surf_Column(x, y, z);
				break;
			}
		}
	}
	catch(::Exception^ e)
	{
		::MessageBox::Show(String::Concat(e->Message,":  ",e->Data,":  ",e->StackTrace,"  ",e->Source,"  ",e->TargetSite));
	}
}

void Form1::SurfWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	Form1::Enabled = true;
}

void Form1::OptFileSavePrecDbl_Click(System::Object^  sender, System::EventArgs^  e) 
{
	OptFileSavePrecDbl->Checked = true;
	OptFileSavePrecInt32->Checked = false;
	OptFileSavePrecUInt16->Checked = false;
	OptFileSavePrecInt16->Checked = false;
	TBOptFileSavePrecDbl->Checked = true;
	TBOptFileSavePrecInt32->Checked = false;
	TBOptFileSavePrecUInt16->Checked = false;
	TBOptFileSavePrecInt16->Checked = false;
	OptsMenu->ForeColor = Color::Black;
	FILESAVEPREC = TypeCode::Double;

	OptsMenu->ShowDropDown();
	fileSavingPrecisionToolStripMenuItem->ShowDropDown();
	OptFileSavePrecDbl->Select();
}

void Form1::TBOptFileSavePrecDbl_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = true;
	OptFileSavePrecInt32->Checked = false;
	OptFileSavePrecUInt16->Checked = false;
	OptFileSavePrecInt16->Checked = false;
	TBOptFileSavePrecDbl->Checked = true;
	TBOptFileSavePrecInt32->Checked = false;
	TBOptFileSavePrecUInt16->Checked = false;
	TBOptFileSavePrecInt16->Checked = false;
	OptsMenu->ForeColor = Color::Black;
	FILESAVEPREC = TypeCode::Double;

	TBFileSavePrecOpts->ShowDropDown();
	TBOptFileSavePrecDbl->Select();
}

void Form1::OptFileSavePrecInt32_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = false;
	OptFileSavePrecInt32->Checked = true;
	OptFileSavePrecUInt16->Checked = false;
	OptFileSavePrecInt16->Checked = false;
	TBOptFileSavePrecDbl->Checked = false;
	TBOptFileSavePrecInt32->Checked = true;
	TBOptFileSavePrecUInt16->Checked = false;
	TBOptFileSavePrecInt16->Checked = false;
	OptsMenu->ForeColor = Color::Blue;
	FILESAVEPREC = TypeCode::Int32;

	OptsMenu->ShowDropDown();
	fileSavingPrecisionToolStripMenuItem->ShowDropDown();
	OptFileSavePrecInt32->Select();
}

void Form1::TBOptFileSavePrecInt32_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = false;
	OptFileSavePrecInt32->Checked = true;
	OptFileSavePrecUInt16->Checked = false;
	OptFileSavePrecInt16->Checked = false;
	TBOptFileSavePrecDbl->Checked = false;
	TBOptFileSavePrecInt32->Checked = true;
	TBOptFileSavePrecUInt16->Checked = false;
	TBOptFileSavePrecInt16->Checked = false;
	OptsMenu->ForeColor = Color::Blue;
	FILESAVEPREC = TypeCode::Int32;

	TBFileSavePrecOpts->ShowDropDown();
	TBOptFileSavePrecInt32->Select();
}

void Form1::OptFileSavePrecInt16_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = false;
	OptFileSavePrecInt32->Checked = false;
	OptFileSavePrecUInt16->Checked = false;
	OptFileSavePrecInt16->Checked = true;
	TBOptFileSavePrecDbl->Checked = false;
	TBOptFileSavePrecInt32->Checked = false;
	TBOptFileSavePrecUInt16->Checked = false;
	TBOptFileSavePrecInt16->Checked = true;
	OptsMenu->ForeColor = Color::Yellow;
	FILESAVEPREC = TypeCode::Int16;

	OptsMenu->ShowDropDown();
	fileSavingPrecisionToolStripMenuItem->ShowDropDown();
	OptFileSavePrecInt16->Select();
}

void Form1::TBOptFileSavePrecInt16_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = false;
	OptFileSavePrecInt32->Checked = false;
	OptFileSavePrecUInt16->Checked = false;
	OptFileSavePrecInt16->Checked = true;
	TBOptFileSavePrecDbl->Checked = false;
	TBOptFileSavePrecInt32->Checked = false;
	TBOptFileSavePrecUInt16->Checked = false;
	TBOptFileSavePrecInt16->Checked = true;
	OptsMenu->ForeColor = Color::Yellow;
	FILESAVEPREC = TypeCode::Int16;

	TBFileSavePrecOpts->ShowDropDown();
	TBOptFileSavePrecInt16->Select();
}

void Form1::OptFileSavePrecUInt16_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = false;
	OptFileSavePrecInt32->Checked = false;
	OptFileSavePrecUInt16->Checked = true;
	OptFileSavePrecInt16->Checked = false;
	TBOptFileSavePrecDbl->Checked = false;
	TBOptFileSavePrecInt32->Checked = false;
	TBOptFileSavePrecUInt16->Checked = true;
	TBOptFileSavePrecInt16->Checked = false;
	OptsMenu->ForeColor = Color::LimeGreen;
	FILESAVEPREC = TypeCode::UInt16;

	OptsMenu->ShowDropDown();
	fileSavingPrecisionToolStripMenuItem->ShowDropDown();
	OptFileSavePrecUInt16->Select();
}

void Form1::TBOptFileSavePrecUInt16_Click(System::Object^  sender, System::EventArgs^  e)
{
	OptFileSavePrecDbl->Checked = false;
	OptFileSavePrecInt32->Checked = false;
	OptFileSavePrecUInt16->Checked = true;
	OptFileSavePrecInt16->Checked = false;
	TBOptFileSavePrecDbl->Checked = false;
	TBOptFileSavePrecInt32->Checked = false;
	TBOptFileSavePrecUInt16->Checked = true;
	TBOptFileSavePrecInt16->Checked = false;
	OptsMenu->ForeColor = Color::LimeGreen;
	FILESAVEPREC = TypeCode::UInt16;

	TBFileSavePrecOpts->ShowDropDown();
	TBOptFileSavePrecUInt16->Select();
}

void Form1::ImageViewHistogram_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (IMAGESET->Count > 1 && BatchCorrectionChck->Checked)
		if (::MessageBox::Show("Histogram entire Image Set?  If you don't want a histogram of the entire Image Set, uncheck the ""Batch"" checkbox in the Image Processing Tab.","Image Set?", 
			::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			return;

	ImageCntxtViewWrkr->RunWorkerAsync(1);//make a histogram of the current image, or of the batch of images if the batch check is selected
}

void Form1::ImageCntxtViewWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	int type = ::Convert::ToInt32(e->Argument);
	array<Object^>^ resultinfo = gcnew array<Object^>(1){-1};//have to set this so runworkercompleted can check for an instance of the instantiation
	e->Result = resultinfo;//which means this also needs set to an instanitation
	switch (type)
	{
	case (1)://make a histogram of the current image or the batch of images
		{
			bool batch = BatchCorrectionChck->Checked;
			int height = IMAGESET[FILELISTINDEX]->Height;
			int width = IMAGESET[FILELISTINDEX]->Width;
			int NBatch = 1;
			if (batch)
				NBatch = IMAGESET->Count;
			array<double>^ values = gcnew array<double>(height*width*NBatch);

			array<int>^ inds = gcnew array<int>(NBatch);
			if (NBatch == 1)
				inds[0] = FILELISTINDEX;
			else
				for (int i = 0; i < NBatch; i++)
					inds[i] = i;

			#pragma omp parallel for
			for (int k = 0; k < NBatch; k++)
				for (int i = 0; i < width; i++)
					for (int j = 0; j < height; j++)
						values[k*width*height + (i*height + j)] = IMAGESET[inds[k]]->Image[i, j];
			
			resultinfo = gcnew array<Object^>(2);
			resultinfo[0] = 1;
			resultinfo[1] = (Object^)values;
			e->Result = resultinfo;
			break;
		}
	case (2):
		{
			break;
		}
	}
}

void Form1::ImageCntxtViewWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	ProgressBar->Value = e->ProgressPercentage;
	ProgressBar->Refresh();
}

void Form1::ImageCntxtViewWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	Form1::Enabled = true;
	ProgressBar->Value = 0;

	array<Object^>^ res = (array<Object^>^)e->Result;
	if (::Convert::ToInt32(res[0]) == 1)//make a histogram of the current image
	{
		//array<double,2>^ hist = JPMath::Histogram_IntegerDivisions((array<double>^)res[1],10000);
		array<double,2>^ hist = JPMath::Histogram_IntegerStep((array<double>^)res[1],1);
		int L = hist->GetLength(0);
		array<double>^ x = gcnew array<double>(L);
		array<double>^ y = gcnew array<double>(L);

		for (int i = 0; i < L; i++)
		{
			x[i] = hist[i,0];
			y[i] = hist[i,1];
		}

		JPPlot^ jpplot = gcnew JPPlot();
		jpplot->Text = "Image Values Histogram";
		jpplot->PlotLine(x,y,"Image Value","Number of Elements","Image Values Histogram", Charting::SeriesChartType::Column, "Histogram");
	} 
}

void Form1::ImageEditValueCntxt_Click(System::Object^  sender, System::EventArgs^  e) 
{
	EditValueCntxt_Click(sender,e);
}

void Form1::EditValueCntxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	//	ImageCntxtViewWrkr->RunWorkerAsync(2);//edit selected pixel value of image, or set of images
	//this doesn't work because with the other thread going, XPOS and YPOS changes are updated and the wrong pixel position then gets modifed
	//yes can code that of course, but whatever, it doesn't NEED to go into a BG worker because there's no need for a "cancel" button option

	EditValueDlg^ dlg = gcnew EditValueDlg();
	double oldval = IMAGESET[FILELISTINDEX]->Image[XPOS_CURSOR,YPOS_CURSOR];
	dlg->EditValueTxt->Text = ::Convert::ToString(oldval);
	dlg->ShowDialog();

	if (dlg->DialogResult == ::DialogResult::OK)
	{
		String^ strval = dlg->EditValueTxt->Text;
		bool outsideROI = strval->StartsWith("!");
		if (outsideROI)
			strval = strval->Substring(1,strval->Length-1);

		double newval = ::Convert::ToDouble(strval);

		array<int,1>^ indeces;
		if (BatchCorrectionChck->Checked)
		{
			::DialogResult dr = ::MessageBox::Show("Are you sure you want to apply this to all images?","Proceed?",::MessageBoxButtons::YesNoCancel);
			if (dr == ::DialogResult::Cancel)
				return;
			if (dr == ::DialogResult::No)
			{
				indeces = gcnew array<int,1>(1){FILELISTINDEX};
				BatchCorrectionChck->Checked = false;
			}
			if (dr == ::DialogResult::Yes)
			{
				indeces = gcnew array<int,1>(IMAGESET->Count);
				for (int i = 0; i < IMAGESET->Count; i++)
					indeces[i] = i;
			}
		}
		else
			indeces = gcnew array<int,1>(1){FILELISTINDEX};

		ProgressBar->Maximum = indeces->Length;
		for (int k = 0; k < indeces->Length; k++)
		{
			ProgressBar->Value = k + 1;
			ProgressBar->Refresh();

			if (!outsideROI)
				IMAGESET[indeces[k]]->Image[XPOS_CURSOR,YPOS_CURSOR] = newval;
			else
			{
				#pragma omp parallel for
				for (int i = 0; i < IMAGESET[indeces[k]]->Width; i++)
					for (int j = 0; j < IMAGESET[indeces[k]]->Height; j++)
						IMAGESET[indeces[k]]->Image[i,j] = newval;

				IMAGESET[indeces[k]]->Image[XPOS_CURSOR,YPOS_CURSOR] = oldval;
			}
			IMAGESET[indeces[k]]->StatsUpD(true);
		}
		ProgressBar->Value = 0;
		FileListDrop_SelectedIndexChanged(sender,e);
	}
	else if (dlg->modecode == -1)//numeric error, try again.
	{
		EditValueCntxt_Click(sender,e);
	}
}

void Form1::EditBoxCntxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	ImageEditBoxCntxt_Click(sender,e);
}

void Form1::ImageEditBoxCntxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	EditValueDlg^ dlg = gcnew EditValueDlg();
	if (dlg->ShowDialog() == ::DialogResult::Cancel)
		return;

	String^ strval = dlg->EditValueTxt->Text;
	bool outsideROI = strval->StartsWith("!");
	if (outsideROI)
		strval = strval->Substring(1,strval->Length-1);
	if (!JPMath::IsNumeric(strval))
	{
		::MessageBox::Show("Enter a number...");
		ImageEditBoxCntxt->PerformClick();
		return;
	}
	double val = ::Convert::ToDouble(strval);

	array<int, 1>^ indeces;
	if (BatchCorrectionChck->Checked)
	{
		::DialogResult dr = ::MessageBox::Show("Are you sure you want to apply this to all images?", "Proceed?", ::MessageBoxButtons::YesNoCancel);
		if (dr == ::DialogResult::Cancel)
			return;
		if (dr == ::DialogResult::No)
		{
			indeces = gcnew array<int, 1>(1) { FILELISTINDEX };
			BatchCorrectionChck->Checked = false;
		}
		if (dr == ::DialogResult::Yes)
		{
			indeces = gcnew array<int, 1>(IMAGESET->Count);
			for (int i = 0; i < IMAGESET->Count; i++)
				indeces[i] = i;
		}
	}
	else
		indeces = gcnew array<int, 1>(1) { FILELISTINDEX };
	ProgressBar->Maximum = indeces->Length;

	if (PSEDrawROI->Checked)
	{
		for (int k = 0; k < indeces->Length; k++)
		{
			ProgressBar->Value = k + 1;
			ProgressBar->Refresh();

			if (!outsideROI)
			{
				#pragma omp parallel for
				for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
					for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
						if (ROI_REGION[x, y])
							IMAGESET[indeces[k]]->Image[x, y] = val;
			}
			else
			{
				#pragma omp parallel for
				for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
					for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
						if (!ROI_REGION[x, y])
							IMAGESET[indeces[k]]->Image[x, y] = val;
			}
		}

		ProgressBar->Value = 0;
		FileListDrop_SelectedIndexChanged(sender, e);
		return;
	}

	if (PSEEllipticalROI->Checked)
	{
		for (int k = 0; k < indeces->Length; k++)
		{
			ProgressBar->Value = k + 1;
			ProgressBar->Refresh();

			ROIX0 = SubImageSlideX->Value - 1;
			ROIY0 = SubImageSlideY->Value - 1;
			ROIXRad = (int)HalfWidthXUpD->Value;
			ROIYRad = (int)HalfWidthYUpD->Value;
			SetReg("CCDLAB", "ROIX0", ROIX0);
			SetReg("CCDLAB", "ROIY0", ROIY0);
			SetReg("CCDLAB", "ROIXRad", ROIXRad);
			SetReg("CCDLAB", "ROIYRad", ROIYRad);
			double roix0 = (double)ROIX0;
			double roiy0 = (double)ROIY0;
			double roixrad2 = (double)ROIXRad * (double)ROIXRad;
			double roiyrad2 = (double)ROIYRad * (double)ROIYRad;

			if (!outsideROI)
			{
				#pragma omp parallel for
				for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
				{
					double dx2 = (double)x - roix0;
					dx2 *= dx2;
					dx2 /= roixrad2;
					for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
					{
						double dy = (double)y;
						if ((dx2 + (dy - roiy0) * (dy - roiy0) / roiyrad2) <= 1)
							IMAGESET[indeces[k]]->Image[x, y] = val;
					}
				}
			}
			else
			{
				#pragma omp parallel for
				for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
				{
					double dx2 = (double)x - roix0;
					dx2 *= dx2;
					dx2 /= roixrad2;
					for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
					{
						double dy = (double)y;
						if ((dx2 + (dy - roiy0) * (dy - roiy0) / roiyrad2) > 1)
							IMAGESET[indeces[k]]->Image[x, y] = val;
					}
				}
			}
		}

		ProgressBar->Value = 0;
		FileListDrop_SelectedIndexChanged(sender, e);
		return;
	}

	for (int k = 0; k < indeces->Length; k++)
	{	
		ProgressBar->Value = k + 1;
		ProgressBar->Refresh();

		if (!outsideROI)
		{
			//only operate on the ROI
			#pragma omp parallel for
			for (int i = 0; i < XSUBRANGE->Length; i++)
				for (int j = 0; j < YSUBRANGE->Length; j++)
					IMAGESET[indeces[k]]->Image[XSUBRANGE[i],YSUBRANGE[j]] = val;
		}
		else
		{
			array<double, 2>^ tempsubim = SUBIMAGE;//to instantiate the dimensions
			//make a temp copy of the subimage
			#pragma omp parallel for
			for (int i = 0; i < XSUBRANGE->Length; i++)
				for (int j = 0; j < YSUBRANGE->Length; j++)
					tempsubim[i,j] = IMAGESET[indeces[k]]->Image[XSUBRANGE[i],YSUBRANGE[j]];

			//obliterate the entire image
			#pragma omp parallel for
			for (int i = 0; i < IMAGESET[indeces[k]]->Width; i++)
				for (int j = 0; j < IMAGESET[indeces[k]]->Height; j++)
					IMAGESET[indeces[k]]->Image[i,j] = val;

			//reinsert the temp unmodifed subimage
			#pragma omp parallel for
			for (int i = 0; i < XSUBRANGE->Length; i++)
				for (int j = 0; j < YSUBRANGE->Length; j++)
					IMAGESET[indeces[k]]->Image[XSUBRANGE[i],YSUBRANGE[j]] = tempsubim[i,j];
		}
		IMAGESET[indeces[k]]->StatsUpD(true);
	}
	ProgressBar->Value = 0;
	FileListDrop_SelectedIndexChanged(sender,e);

}

void Form1::FindFiles()
{
	FITSFINDER = gcnew JPFITS::FitsFinder();
	FITSFINDER->ShowDialog();

	if (FITSFINDER->DialogResult != ::DialogResult::OK)
		return;


	int numfilesfound = FITSFINDER->FOUNDFILES->Length;
	if (numfilesfound == 0)//no files found
	{
		TBViewFound->Enabled = false;
		FMViewFound->Enabled = false;
		::MessageBox::Show("No Files Found Matching File Extension or Search Criteria...","Warning");
		FindFiles();
		return;
	}

	FITSFINDERFILES = FITSFINDER->FOUNDFILES;
	
	TBViewFound->Enabled = true;
	FMViewFound->Enabled = true;
	FITSFOUND = gcnew JPFITS::FitsFound();
	FITSFOUND->SetFoundFiles(FITSFINDERFILES);
	FITSFOUND->ShowDialog();
	
	int Ninds = FITSFOUND->FileListTxt->SelectedIndices->Count;
	if (Ninds == 0 && FITSFOUND->DialogResult != System::Windows::Forms::DialogResult::Cancel)//no files selected but asked to load files (!cancel)
	{
		::MessageBox::Show("No Files Selected!...","Error");
		ViewFoundList();
		return;
	}

	array<String^>^ selectfiles = gcnew array<String^>(Ninds);
	for (int j = 0; j < Ninds; j++)
		selectfiles[j] = FITSFINDERFILES[FITSFOUND->FileListTxt->SelectedIndices[j]];

	switch (FITSFOUND->DialogResult)
	{
	case (System::Windows::Forms::DialogResult::Cancel):
		{
			FindFiles();
			break;
		}
	case (System::Windows::Forms::DialogResult::OK)://for loading NEW IMAGESET
		{
			AUTOLOADIMAGES = true;
			AUTOLOADIMAGESFILES = gcnew array<String^>(selectfiles->Length);
			for (int i = 0; i < selectfiles->Length; i++)
				AUTOLOADIMAGESFILES[i] = selectfiles[i];

			IMAGESET = gcnew FITSImageSet();
			FMLoad_Click(gcnew Object, gcnew EventArgs());
			//FMLoad->PerformClick();
			break;
		}
	case (System::Windows::Forms::DialogResult::Ignore)://for ADDING to existing IMAGESET
		{
			AddToImageSet(selectfiles, true);
			break;
		}
	default://ie no files selected at all
		{	
			break;
		}
	}
}

void Form1::ViewFoundList()
{
	FITSFOUND = gcnew JPFITS::FitsFound();
	int numlines = FITSFINDERFILES->Length;

	if (numlines > 0)
	{
		FITSFOUND->SetFoundFiles(FITSFINDERFILES);
		FITSFOUND->ShowDialog();
		
		int Ninds = FITSFOUND->FileListTxt->SelectedIndices->Count;
		if (Ninds == 0 && FITSFOUND->DialogResult != System::Windows::Forms::DialogResult::Cancel)//no files selected but asked to load files (!cancel)
		{
			::MessageBox::Show("No Files Selected!...","Error");
			ViewFoundList();
			return;
		}

		array<String^>^ selectfiles = gcnew array<String^>(Ninds);
		for (int j = 0; j < Ninds; j++)
		{
			selectfiles[j] = FITSFINDERFILES[FITSFOUND->FileListTxt->SelectedIndices[j]];
			
			if (!::File::Exists(selectfiles[j]))
			{
				::MessageBox::Show("Some of the files don't exist on the specified path.  The list file may be old.","Error...");
				ViewFoundList();
				return;
			}
		}

		switch (FITSFOUND->DialogResult)
		{
		case (System::Windows::Forms::DialogResult::Cancel):
			{
				//FindFiles();
				break;
			}
		case (System::Windows::Forms::DialogResult::OK)://for loading NEW IMAGESET
			{
				AUTOLOADIMAGES = true;
				AUTOLOADIMAGESFILES = gcnew array<String^>(selectfiles->Length);
				for (int i = 0; i < selectfiles->Length; i++)
					AUTOLOADIMAGESFILES[i] = selectfiles[i];

				IMAGESET = gcnew FITSImageSet();
				FMLoad_Click(gcnew Object, gcnew EventArgs());
				//FMLoad->PerformClick();
				break;
			}
		case (System::Windows::Forms::DialogResult::Ignore)://for ADDING to existing IMAGESET
			{
				AddToImageSet(selectfiles, true);
				break;
			}
		default://ie no files selected at all
			{	
				break;
			}
		}
	}
}

void Form1::TBOpenFound_Click(System::Object ^sender, System::EventArgs ^e)
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "CCDLAB File List (*.CFL)|*.CFL";
	if (dlg->ShowDialog() == ::DialogResult::Cancel)
		return;

	String^ file = dlg->FileName;

	FileStream^ fs2 = gcnew FileStream(file,System::IO::FileMode::Open,FileAccess::Read);
	StreamReader^ sr2 = gcnew StreamReader(fs2);
	int numlines = System::Convert::ToInt32(sr2->ReadLine());

	array<String^>^ fullfiles = gcnew array<String^>(numlines);
	for (int i = 0; i < numlines; i++)
		fullfiles[i] = sr2->ReadLine();

	sr2->Close();
	fs2->Close();
	TBViewFound->Enabled = true;
	FMViewFound->Enabled = true;

	FITSFINDERFILES = fullfiles;

	ViewFoundList();
}

void Form1::SingleOutBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	JPFITS::FITSImage^ tmp = IMAGESET[FILELISTINDEX];// gcnew FITSImage(IMAGESET[FILELISTINDEX]->FullFileName, IMAGESET[FILELISTINDEX]->Image, true, true);
	IMAGESET->Clear();
	IMAGESET->Add(tmp);
	AUTOLOADIMAGES = true;
	AUTOLOADIMAGESFILES = gcnew array<String^>(1) { "SingleOut" };
	FMLoad_Click(sender, e);
}

void Form1::FMLoad_Click(System::Object^ sender, System::EventArgs^ e)
{
	FMLoad->HideDropDown();
	FileMenu->HideDropDown();
	if (LOADSUBRANGE == false)
		SUBRANGE[0] = -1;
	else
		LOADSUBRANGE = false;//forget why

	::OpenFileDialog^ ofd;
	array<String^>^ filenames;

	if (!AUTOLOADIMAGES)
	{
		ofd = gcnew ::OpenFileDialog();
		ofd->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFilesPath");
		ofd->FilterIndex = ::Convert::ToInt32(GetReg("CCDLAB", "FilterIndex"));
		ofd->Filter = "FITS|*.fits;*.fit;*.fts;|All|*.*";
		ofd->Multiselect = true;
		if (ofd->ShowDialog() == ::DialogResult::Cancel)
			return;
		filenames = ofd->FileNames;
		SetReg("CCDLAB", "FilterIndex", ofd->FilterIndex.ToString());
		if (filenames->Length == 1)
		{
			FITSImage^ check = gcnew FITSImage(filenames[0], nullptr, true, false, false, false);
			if (Convert::ToInt32(check->Header->GetKeyValue("NAXIS")) == 0)
			{
				JPFITS::FitsExtensionTableViewer^ view = gcnew FitsExtensionTableViewer(ofd->FileName);
				view->BringToFront();
				return;
			}
		}
		IMAGESET = gcnew FITSImageSet();
	}
	else
		filenames = AUTOLOADIMAGESFILES;

	SetReg("CCDLAB", "OpenFilesPath", Path::GetDirectoryName(filenames[0]));

	if (filenames[0] != "SingleOut")
	{
		int ind = filenames[0]->LastIndexOf("\\");
		String^ dir = filenames[0]->Substring(0, ind);
		SetReg("CCDLAB", "OpenFilesPath", dir);
		UVOpenRawDlg->InitialDirectory = dir;
		UVOpenDirDlg->SelectedPath = dir;

		if (!AUTOLOADIMAGES)
			FILELISTINDEX = 0;
		else
		{
			if (IMAGESET == nullptr || IMAGESET->Count == 0)
				FILELISTINDEX = 0;
			else
				FILELISTINDEX = FileListDrop->Items->Count;
			AUTOLOADIMAGES = false;
		}

		if (!IMAGESET->Load(filenames, SUBRANGE, true, true, true, "Loading Images"))
			return;
	}
	else
	{
		FILELISTINDEX = 0;
		AUTOLOADIMAGES = false;
	}

	FileListDrop->Items->Clear();
	FileListDrop->Items->AddRange(IMAGESET->FileNames);

	if (::Convert::ToInt32(GetReg("CCDLAB", "FilterIndex")) == 2)//UVIT *.raw
	{
		UVOpenRawBtn->Enabled = true;
		UVOpenDirBtn->Enabled = true;
		UVOpenSubDirChck->Enabled = true;
	}

	if (IMAGESET->Count > 1)
	{
		BatchViewPanel->Enabled = true;
		TBSaveBatch->Enabled = true;
		TBSaveBatchOver->Enabled = true;
		TBZipAllBtn->Enabled = true;
		BatchCorrectionChck->Checked = true;
		BatchCorrectionChck->Enabled = true;
		ImageBatchRedxnPnl->Enabled = true;
		HCInsertBatch->Enabled = true;
		HCRemoveBatch->Enabled = true;
		HCEditAll->Enabled = true;
	}
	else
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		BatchCorrectionChck->Checked = false;
		BatchCorrectionChck->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
		HCEditAll->Enabled = false;
	}

	//reset processing tab check boxes (and init others)
	MainTab->Enabled = true;
	ContrastPanel->Enabled = true;
	SubImagePanel->Enabled = true;
	FMAdd->Enabled = true;
	TBAdd->Enabled = true;
	FMReload->Enabled = true;
	TBReload->Enabled = true;
	TBSave->Enabled = true;
	TBSaveOver->Enabled = true;
	FMSave->Enabled = true;
	FMSaveBatch->Enabled = true;
	ViewHeaderBtn->Enabled = true;
	SubImageSlideX->Enabled = true;
	SubImageSlideY->Enabled = true;

	ImageWindow->ContextMenuStrip = ImageWindowCntxt;
	SubImageWindow->ContextMenuStrip = SubImageCntxt;

	SubBiasChck->Checked = false;
	MultImgChck->Checked = false;
	AddImageChck->Checked = false;
	DivFlatChck->Checked = false;
	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;
	System::GC::Collect();

	FileListDrop->SelectedIndex = FILELISTINDEX;

	RecentFilesUpD();
}

void Form1::FMAdd_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");

	OpenFileDialog^ afd = gcnew OpenFileDialog();
	afd->InitialDirectory = dir;
	afd->Multiselect = true;
	afd->Filter = "FITS|*.fits;*.fit;*.fts|UVIT FITS|*.raw";
	afd->FilterIndex = ::Convert::ToInt32(GetReg("CCDLAB", "FilterIndex"));
	if (afd->ShowDialog() == ::DialogResult::Cancel)
		return;
	SetReg("CCDLAB", "FilterIndex", afd->FilterIndex.ToString());

	AUTOLOADIMAGES = true;
	AUTOLOADIMAGESFILES = afd->FileNames;
	FMLoad_Click(sender, e);
	//FMLoad->PerformClick();
}

void Form1::RecentFilesUpD()
{
	//check that all files exists and remove if not
	array<String^>^ recentlists = Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
	for (int i = 0; i < recentlists->Length; i++)
	{
		StreamReader^ sr = gcnew StreamReader(recentlists[i]);
		int numlines = System::Convert::ToInt32(sr->ReadLine());
		for (int j = 0; j < numlines; j++)
			if (!File::Exists(sr->ReadLine()))
			{
				sr->Close();
				File::Delete(recentlists[i]);
				break;
			}
		sr->Close();
	}
		
	if (!FIRSTLOAD)
	{
		//first find the recentfileslists and create/modify as needed
		recentlists = Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
		
		for (int i = recentlists->Length - 1; i >= 0; i--)
		{
			String^ file = recentlists[i];
			File::Move(file, file->Replace("_" + i.ToString("00"), "_" + (i + 1).ToString("00")));
		}

		FileStream^ fs = gcnew FileStream(CCDLABPATH + "recentfileslist_00.txt", System::IO::FileMode::Create, FileAccess::Write);
		StreamWriter^ sw = gcnew StreamWriter(fs);
		sw->WriteLine(IMAGESET->Count);
		for (int i = 0; i < IMAGESET->Count; i++)
			sw->WriteLine(IMAGESET[i]->FullFileName);
		sw->Flush();
		fs->Flush();
		sw->Close();
		fs->Close();

		//if there are more lists than RECENTFILESLISTLENGTH, then delete the oldest one and rename/move up the previous ones
		recentlists = Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
		if (recentlists->Length > RECENTFILESLISTLENGTH)
			for (int i = RECENTFILESLISTLENGTH; i < recentlists->Length; i++)
				if (File::Exists(CCDLABPATH + "recentfileslist_" + i.ToString("00") + ".txt"))
					File::Delete(CCDLABPATH + "recentfileslist_" + i.ToString("00") + ".txt");

		//should go through the recent lists and check for duplicates...and delete all older dupes
		recentlists = ::Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
		FileInfo^ fi0 = gcnew FileInfo(recentlists[0]);
		array<unsigned char>^ fc0 = File::ReadAllBytes(recentlists[0]);

		bool dupe = false;
		for (int j = 1; j < recentlists->Length; j++)
		{
			FileInfo^ fij = gcnew FileInfo(recentlists[j]);
			if (fi0->Length != fij->Length)
				continue;
			
			array<unsigned char>^ fcj = File::ReadAllBytes(recentlists[j]);
			int i = 0;
			for (i; i < fcj->Length; i++)
				if (fcj[i] != fc0[i])
					break;
			if (i == fcj->Length)
				i--;
			if (fcj[i] != fc0[i])
				continue;

			File::Delete(recentlists[j]);
			dupe = true;
		}
		
		if (dupe)
		{
			recentlists = ::Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
			for (int i = 0; i < recentlists->Length; i++)
				File::Move(recentlists[i], CCDLABPATH + "recentfileslist_" + i.ToString("00") + ".txt");
		}
	}

	recentlists = ::Directory::GetFiles(CCDLABPATH, "*recentfileslist_*.txt");
	array<Windows::Forms::ToolStripButton^>^ tsbc = gcnew array<Windows::Forms::ToolStripButton^>(recentlists->Length);

	for (int i = 0; i < recentlists->Length; i++)
	{
		StreamReader^ sr2 = gcnew StreamReader(recentlists[i]);
		int numlines = System::Convert::ToInt32(sr2->ReadLine());
		String^ file;

		if (numlines == 1)
		{
			file = sr2->ReadLine();
			tsbc[i] = gcnew Windows::Forms::ToolStripButton("{" + File::GetLastWriteTime(recentlists[i]).ToString() + "}" + " " + file->Substring(1 + file->LastIndexOf("\\")));
			tsbc[i]->ToolTipText = file->Substring(0, file->LastIndexOf("\\") + 1);
		}
		else
		{
			file = sr2->ReadLine();
			String^ dircomparestr = file;
			String^ tooltipstr = file->Substring(1 + file->LastIndexOf("\\")) + "\r\n";
			for (int j = 1; j < numlines; j++)
			{
				file = sr2->ReadLine();
				tooltipstr += file->Substring(1 + file->LastIndexOf("\\")) + "\r\n";
				for (int k = 0; k < dircomparestr->Length; k++)
					if (dircomparestr[k] != file[k])
					{
						dircomparestr = file->Substring(0, k + 1);
						break;
					}
				if (j > 50)
				{
					tooltipstr += "... + " + (numlines - j) + " more...";
					break;
				}
			}
			dircomparestr = dircomparestr->Substring(0, 1 + dircomparestr->LastIndexOf("\\"));
			tsbc[i] = gcnew Windows::Forms::ToolStripButton("{" + File::GetLastWriteTime(recentlists[i]).ToString() + "}" + " " + dircomparestr + " (" + numlines + ")");
			tsbc[i]->ToolTipText = tooltipstr;
		}
		sr2->Close();
		tsbc[i]->Tag = recentlists[i];
		tsbc[i]->Width = tsbc[i]->Text->Length * 6;
		tsbc[i]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::RecentFilesLoadSingle_Click);
	}
	TBRecentFiles->DropDownItems->Clear();
	TBRecentFiles->DropDownItems->AddRange(tsbc);
}

void Form1::RecentFilesLoadAll_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::RecentFilesLoadSingle_Click(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	String^ recentfilelist = (String^)((Windows::Forms::ToolStripButton^)sender)->Tag;
	StreamReader^ sr2 = gcnew StreamReader(recentfilelist);
	int numlines = System::Convert::ToInt32(sr2->ReadLine());
	AUTOLOADIMAGESFILES = gcnew array<String^>(numlines);
	for (int i = 0; i < numlines; i++)
		AUTOLOADIMAGESFILES[i] = sr2->ReadLine();
	sr2->Close();

	for (int i = 0; i < numlines; i++)
		if (!File::Exists(AUTOLOADIMAGESFILES[i]))
		{
			MessageBox::Show("File: " + AUTOLOADIMAGESFILES[i] + " doesn't exist...  Stopping and removing recent file name from recents list.", "Error...", ::MessageBoxButtons::OK);
			File::Delete(recentfilelist);
			RecentFilesUpD();
			return;
		}

	TBRecentFiles->HideDropDown();

	if (e->Button == ::MouseButtons::Left)//load images
	{
		if (AUTOLOADIMAGESFILES->Length == 1)
			if (MessageBox::Show("Are you sure you would like to LOAD " + AUTOLOADIMAGESFILES[0], "Warning...", ::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;
		if (AUTOLOADIMAGESFILES->Length > 1)
			if (MessageBox::Show("Are you sure you would like to LOAD all " + numlines + " images from " + File::GetLastWriteTime(recentfilelist).ToString(), "Warning...", ::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;
		IMAGESET = gcnew FITSImageSet();
		AUTOLOADIMAGES = true;
		FMLoad_Click(sender, e);
		//FMLoad->PerformClick();
	}

	if (e->Button == ::MouseButtons::Right)//add images
	{
		if (AUTOLOADIMAGESFILES->Length == 1)
			if (MessageBox::Show("Are you sure you would like to ADD " + AUTOLOADIMAGESFILES[0], "Warning...", ::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;
		if (AUTOLOADIMAGESFILES->Length > 1)
			if (MessageBox::Show("Are you sure you would like to ADD all " + numlines + " images from " + File::GetLastWriteTime(recentfilelist).ToString(), "Warning...", ::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;
		AUTOLOADIMAGES = true;
		FMLoad_Click(sender, e);
		//FMLoad->PerformClick();
	}
}

void Form1::AddToImageSet(array<String^>^ fullpathlist, bool updateRecent)
{
	FITSImage^ tblcheck = gcnew FITSImage(fullpathlist[0], nullptr, true, false, false, false);
	if (Convert::ToInt32(tblcheck->Header->GetKeyValue("NAXIS")) == 0)
	{
		JPFITS::FitsExtensionTableViewer^ view = gcnew FitsExtensionTableViewer(fullpathlist[0]);
		view->TopMost = true;
		return;
	}

	int c = FileListDrop->Items->Count;
	array<String^>^ files = gcnew array<String^>(fullpathlist->Length + c);

	if (!UVREGISTRATION)
		ProgressBar->Maximum = fullpathlist->Length;

	for (int i = 0; i < fullpathlist->Length;i++)
	{
		if (!UVREGISTRATION)
		{
			ProgressBar->Value++;
			ProgressBar->Refresh();
		}

		JPFITS::FITSImage^ f = gcnew FITSImage(fullpathlist[i], SUBRANGE, true, true, true, true);
		IMAGESET->Add(f);
	}

	if (!UVREGISTRATION)
		ProgressBar->Value = 0;

	FileListDrop->Items->Clear();
	for (int i = 0; i < fullpathlist->Length + c; i++)
		files[i] = IMAGESET[i]->FileName;
	FileListDrop->Items->AddRange(files);

	if (Convert::ToInt32(GetReg("CCDLAB", "FilterIndex")) == 2)//UVIT *.raw
	{
		UVOpenRawBtn->Enabled = true;
		UVOpenDirBtn->Enabled = true;
		UVOpenSubDirChck->Enabled = true;
	}

	if (IMAGESET->Count>1)//needed to add this due to adding image via found file list
	{
		BatchViewPanel->Enabled = true;
		TBSaveBatch->Enabled = true;
		TBSaveBatchOver->Enabled = true;
		TBZipAllBtn->Enabled = true;
		BatchCorrectionChck->Checked = true;
		BatchCorrectionChck->Enabled = true;
		ImageBatchRedxnPnl->Enabled = true;
		HCInsertBatch->Enabled = true;
		HCRemoveBatch->Enabled = true;
	}
	else
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		BatchCorrectionChck->Checked = false;
		BatchCorrectionChck->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
	}

	//reset processing tab check boxes (and init others)
	MainTab->Enabled = true;
	ContrastPanel->Enabled = true;
	SubImagePanel->Enabled = true;
	FMAdd->Enabled = true;
	TBAdd->Enabled = true;
	FMReload->Enabled = true;
	TBReload->Enabled = true;
	TBSave->Enabled = true;
	TBSaveOver->Enabled = true;
	FMSave->Enabled = true;
	FMSaveBatch->Enabled = true;
	ViewHeaderBtn->Enabled = true;
	SubImageSlideX->Enabled = true;
	SubImageSlideY->Enabled = true;
	ImageWindow->ContextMenuStrip = ImageWindowCntxt;
	SubImageWindow->ContextMenuStrip = SubImageCntxt;

	SubBiasChck->Checked = false;
	MultImgChck->Checked = false;
	AddImageChck->Checked = false;
	DivFlatChck->Checked = false;
	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;

	FileListDrop->SelectedIndex = c;
	
	if(updateRecent)
		RecentFilesUpD();

	System::GC::Collect();

	if (UVREGISTRATION)
	{
		try
		{
			::File::Delete(fullpathlist[0]);
		}
		catch (...){}
	}
}

void Form1::ImageUpD(array<double,2>^ image)
{
	int scaling = ContrastScaleDrop->SelectedIndex;
	int colour = ColourMapDrop->SelectedIndex;
	bool invert = InvertContrastChck->Checked;
	SetContrast();
	IMAGEBMP = JPBitMap::ArrayToBmp(image, scaling, colour, invert, DIMCLIM, ImageWindow->Size.Width, ImageWindow->Size.Height, OPTIMGVIEWINVERTY);

	//IMAGEBMP = JPBitMap::ArrayTo16bppGSBmp(image, scaling, colour, invert, DIMCLIM, ImageWindow->Size.Width, ImageWindow->Size.Height, OPTIMGVIEWINVERTY);

	ImageWindow->Refresh();
}

inline void Form1::SubImageUpD()
{
	bool invert = InvertContrastChck->Checked;
	int scaling = ContrastScaleDrop->SelectedIndex;
	int colour = ColourMapDrop->SelectedIndex;
	bool matchscale = ScaleContrastChck->Checked;

	if (PSEEllipticalROI->Checked)
		return;

	if (!matchscale)
	{	
		array<double, 1>^ lims = gcnew array<double, 1>{SUBIMAGEMIN, SUBIMAGEMAX};
		SUBIMAGEBMP = JPBitMap::ArrayToBmp(SUBIMAGE, 0, 0, false, lims, SubImageWindow->Size.Width, SubImageWindow->Size.Height, OPTIMGVIEWINVERTY);
	}
	else
	{
		SUBIMAGEBMP = JPBitMap::ArrayToBmp(SUBIMAGE, scaling, colour, invert, DIMCLIM, SubImageWindow->Size.Width, SubImageWindow->Size.Height, OPTIMGVIEWINVERTY);
	}
	SubImageWindow->Refresh();
}

inline void Form1::SubImageStatsUpD()
{
	int w = IMAGESET[FILELISTINDEX]->Width;
	int h = IMAGESET[FILELISTINDEX]->Height;
	int c = 0;	//counter
	int L = SUBIMAGE->Length;
	double N = double(L);
	SUBIMAGESUM = 0.0;
	SUBIMAGEMIN = 0.0;
	SUBIMAGEMAX = 0.0;
	SUBIMAGEMEDIAN = 0.0;
	SUBIMAGEMEAN = 0.0;
	SUBIMAGESTD = 0.0;

	int x = SubImageSlideX->Value - 1;
	int y = SubImageSlideY->Value - 1;

	if (x < SUBIMAGE_HWX)
		x = SUBIMAGE_HWX;
	if (y < SUBIMAGE_HWY)
		y = SUBIMAGE_HWY;
	if (x > w - SUBIMAGE_HWX - 1)
		x = w - SUBIMAGE_HWX - 1;
	if (y > h - SUBIMAGE_HWY - 1)
		y = h - SUBIMAGE_HWY - 1;

	int sihwt2p1X = SUBIMAGE_HWX * 2 + 1;
	for (int k = 0; k < sihwt2p1X; k++)
		XSUBRANGE[k] = x - SUBIMAGE_HWX + k;

	int sihwt2p1Y = SUBIMAGE_HWY * 2 + 1;
	for (int k = 0; k < sihwt2p1Y; k++)
		YSUBRANGE[k] = y - SUBIMAGE_HWY + k;

	SubImageXTxt->Text = (XSUBRANGE[SUBIMAGE_HWX] + 1).ToString();
	SubImageYTxt->Text = (YSUBRANGE[SUBIMAGE_HWY] + 1).ToString();
	if (IMAGESET[FILELISTINDEX]->WCS->Exists())
	{
		double cval1, cval2;
		String^ sx1;
		String^ sx2;
		IMAGESET[FILELISTINDEX]->WCS->Get_Coordinate((double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], true, "TAN", cval1, cval2, sx1, sx2);
		sx1 = sx1->Replace(" ", "");
		sx2 = sx2->Replace(" ", "");
		if (sx1->Contains("."))
			sx1 = sx1->Substring(0, sx1->LastIndexOf(".") + 2);
		if (sx2->Contains("."))
			sx2 = sx2->Substring(0, sx2->LastIndexOf(".") + 2);
		SubImageRATxt->Text = sx1;
		SubImageDecTxt->Text = sx2;
	}

	if (PSEEllipticalROI->Checked)
		return;

	double sum = 0;
	double mx = System::Double::MinValue;
	double mn = System::Double::MaxValue;
	#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < sihwt2p1X; i++)
		for (int j = 0; j < sihwt2p1Y; j ++)
		{
			SUBIMAGE[i,j] = IMAGESET[FILELISTINDEX]->Image[XSUBRANGE[i],YSUBRANGE[j]];
			sum += SUBIMAGE[i,j];

			if (SUBIMAGE[i, j] < mn)
			{
				#pragma omp critical  
				{
					if (SUBIMAGE[i, j] < mn)
						mn = SUBIMAGE[i, j];
				}
			}
			if (SUBIMAGE[i, j] > mx)
			{
				#pragma omp critical  
				{
					if (SUBIMAGE[i, j] > mx)
						mx = SUBIMAGE[i, j];
				}
			}
		}

	SUBIMAGESUM = sum;
	SUBIMAGEMEAN = SUBIMAGESUM/N;
	SUBIMAGEMIN = mn;
	SUBIMAGEMAX = mx;
	SUBIMAGEMEDIAN = JPMath::Median(SUBIMAGE);

	double std = 0;
	#pragma omp parallel for reduction(+: std)
	for (int i=0; i < sihwt2p1X; i++)
		for (int j=0; j < sihwt2p1Y; j++)
			std += (SUBIMAGE[i,j]-SUBIMAGEMEAN)*(SUBIMAGE[i,j]-SUBIMAGEMEAN);
	SUBIMAGESTD = Math::Sqrt(std/(N-1.0));

	SubImageSumTxt->Text = SUBIMAGESUM.ToString();
	SubImageMinTxt->Text = SUBIMAGEMIN.ToString();
	SubImageMaxTxt->Text = SUBIMAGEMAX.ToString();
	SubImageMeanTxt->Text = SUBIMAGEMEAN.ToString();
	SubImageMedianTxt->Text = SUBIMAGEMEDIAN.ToString();
	SubImageStdTxt->Text = SUBIMAGESTD.ToString();
}

void Form1::StatTxtsUpD()
{
	ImageSumTxt->Text = IMAGESET[FILELISTINDEX]->Sum.ToString();
	ImageMinTxt->Text = IMAGESET[FILELISTINDEX]->Min.ToString();
	ImageMaxTxt->Text = IMAGESET[FILELISTINDEX]->Max.ToString();
	ImageMeanTxt->Text = IMAGESET[FILELISTINDEX]->Mean.ToString();
	ImageMedianTxt->Text = IMAGESET[FILELISTINDEX]->Median.ToString();
	ImageStdTxt->Text = IMAGESET[FILELISTINDEX]->Std.ToString();
	ImageSizeTxt->Text = String::Concat(IMAGESET[FILELISTINDEX]->Width.ToString(),"x",IMAGESET[FILELISTINDEX]->Height.ToString());
}

void Form1::FileTxtsUpD()
{
	
	DirectoryLabel->Text = IMAGESET[FILELISTINDEX]->FullFileName;
	try
	{
		FileDirectoryTxt->Text = ".." + Directory::GetParent(Directory::GetParent(IMAGESET[FILELISTINDEX]->FilePath)->FullName)->Name + "\\" + Directory::GetParent(IMAGESET[FILELISTINDEX]->FullFileName)->Name;
	}
	catch (...) {}
	FileDirectoryTxt->Tag = IMAGESET[FILELISTINDEX]->FilePath;
	Tooltip->SetToolTip(FileDirectoryTxt, IMAGESET[FILELISTINDEX]->FilePath);
	FileNameTxt->Text = IMAGESET[FILELISTINDEX]->FileName;
	InfoTxt1->Text = IMAGESET[FILELISTINDEX]->Header->GetKeyValue(InfoStatic1->Text->Substring(0, InfoStatic1->Text->IndexOf(':')));
	InfoTxt2->Text = IMAGESET[FILELISTINDEX]->Header->GetKeyValue(InfoStatic2->Text->Substring(0, InfoStatic2->Text->IndexOf(':')));
	InfoTxt3->Text = IMAGESET[FILELISTINDEX]->Header->GetKeyValue(InfoStatic3->Text->Substring(0, InfoStatic3->Text->IndexOf(':')));
	InfoTxt4->Text = IMAGESET[FILELISTINDEX]->Header->GetKeyValue(InfoStatic4->Text->Substring(0, InfoStatic4->Text->IndexOf(':')));
	InfoTxt5->Text = IMAGESET[FILELISTINDEX]->Header->GetKeyValue(InfoStatic5->Text->Substring(0, InfoStatic5->Text->IndexOf(':')));

	if (ViewHeaderBtn->Checked)
	{
		int ind = HeaderTxt->TopIndex;
		String^ key = IMAGESET[OLD_INDEX]->Header->GetKeyName(ind);
		int c = HeaderTxt->SelectedIndices->Count;
		array<String^>^ keys = gcnew array<String^>(c);
		for (int i = 0; i < c; i++)
			keys[i] = (String^)HeaderTxt->Items[HeaderTxt->SelectedIndices[i]];

		HeaderTxt->BeginUpdate();
		HeaderTxt->Items->Clear();
		HeaderTxt->Items->AddRange(IMAGESET[FILELISTINDEX]->Header->GetFormattedHeaderBlock(false, true));
		ind = IMAGESET[FILELISTINDEX]->Header->GetKeyIndex(key, false);
		HeaderTxt->TopIndex = ind;

		for (int i = 0; i < c; i++)
		{
			int ind = IMAGESET[FILELISTINDEX]->Header->GetKeyIndex(keys[i], false);
			HeaderTxt->SelectedIndex = ind;
		}

		HeaderTxt->EndUpdate();
	}
}

void Form1::ViewHeaderBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (ViewHeaderBtn->Checked == true)
	{
		FileTxtsUpD();
		HeaderTxt->BringToFront();
		HeaderTxt->Visible = true;
	}
	else
	{
		HeaderTxt->Visible = false;
		ImageWindow->Refresh();
	}
}

void Form1::FileDirectoryTxt_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	System::Diagnostics::Process::Start("Explorer.exe", (String^)FileDirectoryTxt->Tag);
}

void Form1::Form1ProgUpD()
{
	ProgressBar->Value++;
	ProgressBar->Refresh();
}

bool Form1::ValidKeyChck(String^ checkkey)
{
	bool result = true;
	array<String^>^ checks = gcnew array<String^>(9){"SIMPLE","BITPIX","NAXIS","NAXIS1","NAXIS2","BZERO","BSCALE","END","EXTEND"};
	for (int i = 0; i < checks->Length; i++)
	{
		if (checkkey->CompareTo(checks[i]) == 0)
			result = false;
	}
	return result;
}

bool Form1::ValidKeyChck(String ^checkkey, array<String ^,1> ^keys)
{
	bool result = true;
	for (int i = 0; i < keys->Length; i++)
	{
		if (checkkey->CompareTo(keys[i]) == 0)
		{
			result = false;
			if (checkkey->Equals("COMMENT"))
				result = true;
		}
	}
	return result;
}

void Form1::ColourMapDrop_SelectedIndexChanged(System::Object ^sender, System::EventArgs ^e)
{
	if (IMAGESET->Count > 0)
	{
		int width = IMAGESET[FILELISTINDEX]->Width;
		int height = IMAGESET[FILELISTINDEX]->Height;
		SubImageSlideX->Maximum = width;
		SubImageSlideY->Maximum = height;
		ImageUpD(IMAGESET[FILELISTINDEX]->Image);
		FileTxtsUpD();
		StatTxtsUpD();
		SubImageStatsUpD();
		SubImageUpD();
	}
}

void Form1::MinContrastSlider_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	//dont need to put anything here because _Scroll does it already
}

void Form1::MaxContrastSlider_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	//dont need to put anything here because _Scroll does it already
}

void Form1::MinContrastCountTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	e->SuppressKeyPress = true;

	if (e->KeyCode != Windows::Forms::Keys::Enter)
		return;

	try
	{
		double min = Convert::ToDouble(MinContrastCountTxt->Text);
		double max = Convert::ToDouble(MaxContrastCountTxt->Text);
	
		if (min >= max)
		{
			MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],3).ToString();
			return;
		}

		double std = IMAGESET[FILELISTINDEX]->Std;
		double mean = IMAGESET[FILELISTINDEX]->Mean;
		
		DIMCLIM[0]  = min;
		IMSTDLIM[0] = (min - mean)/std;

		CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

		MinContrastSlider->Value = 1;

		ImageUpD(IMAGESET[FILELISTINDEX]->Image);
		SubImageUpD();

		ContrastWideRad->Checked = false;
		ContrastFullRad->Checked = false;
		ContrastNarrowRad->Checked = false;

		MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
		MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
		MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
		MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	}
	catch (...)
	{
	}
}

void Form1::MaxContrastCountTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	e->SuppressKeyPress = true;

	if (e->KeyCode != Windows::Forms::Keys::Enter)
		return;

	try
	{
		double min = Convert::ToDouble(MinContrastCountTxt->Text);
		double max = Convert::ToDouble(MaxContrastCountTxt->Text);
	
		if (min >= max)
		{
			MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],3).ToString();
			return;
		}

		double std = IMAGESET[FILELISTINDEX]->Std;
		double mean = IMAGESET[FILELISTINDEX]->Mean;
		
		DIMCLIM[1]  = max;
		IMSTDLIM[1] = (max - mean)/std;

		CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

		MaxContrastSlider->Value = 300;

		ImageUpD(IMAGESET[FILELISTINDEX]->Image);
		SubImageUpD();

		ContrastWideRad->Checked = false;
		ContrastFullRad->Checked = false;
		ContrastNarrowRad->Checked = false;

		MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
		MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
		MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
		MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	}
	catch (...)
	{
	}
}

void Form1::MinContrastStdTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	e->SuppressKeyPress = true;

	if (e->KeyCode != Windows::Forms::Keys::Enter)
		return;

	try
	{
		double min = Convert::ToDouble(MinContrastStdTxt->Text);
		double max = Convert::ToDouble(MaxContrastStdTxt->Text);
	
		if (min >= max)
		{
			MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],3).ToString();
			return;
		}

		double std = IMAGESET[FILELISTINDEX]->Std;
		double mean = IMAGESET[FILELISTINDEX]->Mean;

		IMSTDLIM[0] = min;
		DIMCLIM[0] = mean + min*std; 

		CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

		MinContrastSlider->Value = 1;

		ImageUpD(IMAGESET[FILELISTINDEX]->Image);
		SubImageUpD();

		ContrastWideRad->Checked = false;
		ContrastFullRad->Checked = false;
		ContrastNarrowRad->Checked = false;

		MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
		MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
		MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
		MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	}
	catch (...)
	{
	}
}

void Form1::MaxContrastStdTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	e->SuppressKeyPress = true;

	if (e->KeyCode != Windows::Forms::Keys::Enter)
		return;

	try
	{
		double min = Convert::ToDouble(MinContrastStdTxt->Text);
		double max = Convert::ToDouble(MaxContrastStdTxt->Text);
	
		if (min >= max)
		{
			MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],3).ToString();
			return;
		}

		double std = IMAGESET[FILELISTINDEX]->Std;
		double mean = IMAGESET[FILELISTINDEX]->Mean;

		IMSTDLIM[1] = max;
		DIMCLIM[1] = mean + max*std; 

		CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

		MaxContrastSlider->Value = 300;

		ImageUpD(IMAGESET[FILELISTINDEX]->Image);
		SubImageUpD();

		ContrastWideRad->Checked = false;
		ContrastFullRad->Checked = false;
		ContrastNarrowRad->Checked = false;

		MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
		MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
		MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
		MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	}
	catch (...)
	{
	}
}

void Form1::MinContrastSlider_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) 
{
	int val = MinContrastSlider->Value;
	MaxContrastSlider->Minimum = val;
	double std = IMAGESET[FILELISTINDEX]->Std;
	double mean = IMAGESET[FILELISTINDEX]->Mean;
	double delta = double(val - PREVMINCONTRASTVALUE);
	PREVMINCONTRASTVALUE = val;

	DIMCLIM[0] += delta*CTSperPERCENT;
	IMSTDLIM[0] = (DIMCLIM[0]-mean)/std;

	MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
	MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();	

	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	SubImageUpD();
}

void Form1::MaxContrastSlider_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) 
{
	int val = MaxContrastSlider->Value;
	MinContrastSlider->Maximum = val;
	double std = IMAGESET[FILELISTINDEX]->Std;
	double mean = IMAGESET[FILELISTINDEX]->Mean;
	double delta = double(val - PREVMAXCONTRASTVALUE);
	PREVMAXCONTRASTVALUE = val;

	DIMCLIM[1] += delta*CTSperPERCENT;
	IMSTDLIM[1] = (DIMCLIM[1]-mean)/std;

	MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
	MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();	
	
	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	SubImageUpD();
}

void Form1::ContrastWideRad_Click(System::Object ^sender, System::EventArgs ^e)
{
	double std = IMAGESET[FILELISTINDEX]->Std;
	double mean = IMAGESET[FILELISTINDEX]->Mean;//from image
	IMSTDLIM[0] = -0.5;//-1.0;
	IMSTDLIM[1] =  5.0;//2.0;
	DIMCLIM[0] = mean + IMSTDLIM[0]*std; 
	DIMCLIM[1] = mean + IMSTDLIM[1]*std;

	MaxContrastSlider->Minimum = 1;
	MinContrastSlider->Maximum = 300;
	MaxContrastSlider->Value = 300;
	MinContrastSlider->Value = 1;

	CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

	MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
	MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
	MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
	MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	//FileListDrop_SelectedIndexChanged(sender,e);
	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	SubImageUpD();
}

void Form1::ContrastNarrowRad_Click(System::Object ^sender, System::EventArgs ^e)
{
	double std = IMAGESET[FILELISTINDEX]->Std;
	double mean = IMAGESET[FILELISTINDEX]->Mean;//from image
	IMSTDLIM[0] = -1.0;//-0.333333333;
	IMSTDLIM[1] =  2.0;//0.333333333;
	DIMCLIM[0] = mean + IMSTDLIM[0]*std;
	DIMCLIM[1] = mean + IMSTDLIM[1]*std;

	MaxContrastSlider->Minimum = 1;
	MinContrastSlider->Maximum = 300;
	MaxContrastSlider->Value = 300;
	MinContrastSlider->Value = 1;

	CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

	MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
	MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
	MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
	MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	//FileListDrop_SelectedIndexChanged(sender,e);
	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	SubImageUpD();
}

void Form1::ContrastFullRad_Click(System::Object ^sender, System::EventArgs ^e)
{
	double std = IMAGESET[FILELISTINDEX]->Std;
	double mean = IMAGESET[FILELISTINDEX]->Mean;//from image
	double min = IMAGESET[FILELISTINDEX]->Min;//from image
	double max = IMAGESET[FILELISTINDEX]->Max;//from image
	IMSTDLIM[0] = (min-mean)/std;
	IMSTDLIM[1] =  (max-mean)/std;
	DIMCLIM[0] = mean + IMSTDLIM[0]*std; 
	DIMCLIM[1] = mean + IMSTDLIM[1]*std;

	MaxContrastSlider->Minimum = 1;
	MinContrastSlider->Maximum = 300;
	MaxContrastSlider->Value = 300;
	MinContrastSlider->Value = 1;

	CTSperPERCENT = (DIMCLIM[1] - DIMCLIM[0])/300.0;

	MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
	MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
	MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
	MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
	//FileListDrop_SelectedIndexChanged(sender,e);
	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	SubImageUpD();
}

void Form1::SetContrast()
{
	double std = IMAGESET[FILELISTINDEX]->Std;
	double mean = IMAGESET[FILELISTINDEX]->Mean;//from image
	double min = IMAGESET[FILELISTINDEX]->Min;//from image
	double max = IMAGESET[FILELISTINDEX]->Max;//from image

	if (AutoContrast->Checked)//keep contrast scale fixed, change DIMCLIM/IMCLIM
	{
		if (ContrastFullRad->Checked == true)
		{
			DIMCLIM[0] = min;
			DIMCLIM[1] = max;

			IMSTDLIM[0] = (min-mean)/std;
			IMSTDLIM[1] =  (max-mean)/std;
			
			MinContrastStdTxt->Text = Math::Round(IMSTDLIM[0],4).ToString();
			MaxContrastStdTxt->Text = Math::Round(IMSTDLIM[1],4).ToString();
		}
		else
		{
			DIMCLIM[0] = mean + IMSTDLIM[0]*std; 
			DIMCLIM[1] = mean + IMSTDLIM[1]*std;
		}

		MinContrastCountTxt->Text = Math::Round(DIMCLIM[0],5).ToString();
		MaxContrastCountTxt->Text = Math::Round(DIMCLIM[1],5).ToString();
	}
	else if (RelativeContrast->Checked)//keep DIMCLIM/IMCLIM fixed, change contrast
	{
		double stdmin = (DIMCLIM[0] - mean)/std;
		MinContrastStdTxt->Text = Math::Round(stdmin,4).ToString();
		double stdmax = (DIMCLIM[1] - mean)/std;
		MaxContrastStdTxt->Text = Math::Round(stdmax,4).ToString();
	}
}

void Form1::BlinkChck_CheckedChanged(System::Object ^sender, System::EventArgs ^e)
{
	if (BlinkChck->Checked)
	{
		MainTab->Enabled = false;
		double t = Convert::ToDouble(BlinkTime->Text);
		t = t*1000;		//convert sendonds to milliseconds  (.2*1000 = 200)
		int T;
		T = Convert::ToInt32(Math::Round(t));
		if (T < 1)
		{
			T = 1;
		}
		BlinkChck->Text = "Stop";
		BlinkChck->BackColor = Drawing::Color::Red;
		BlinkTimer->Interval = T;
		BlinkTimer->Enabled = true;
	}
	else
	{
		MainTab->Enabled = true;
		BlinkTimer->Enabled = false;
		BlinkChck->Text = "Blink";
		BlinkChck->BackColor = Drawing::Color::FromName(Control::BackColor.ToString());//Gray;
	}
}

void Form1::FileListDrop_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{

}

void Form1::FileListDrop_SelectedIndexChanged(System::Object ^sender, System::EventArgs ^e)
{
	//ReplaceImagePtsBtn->Enabled = false;
	FILELISTINDEX = FileListDrop->SelectedIndex;
	int width = IMAGESET[FILELISTINDEX]->Width;
	int height = IMAGESET[FILELISTINDEX]->Height;
	if (SUBIMAGE_HWX > (width-1)/2)
	{
		HalfWidthXUpD->Value = int((width-1)/2);
		SUBIMAGE_HWX = (int)HalfWidthXUpD->Value;
	}
	if (SUBIMAGE_HWY > (height-1)/2)
	{
		HalfWidthYUpD->Value = int((height-1)/2);
		SUBIMAGE_HWY = (int)HalfWidthYUpD->Value;
	}
	int C = IMAGESET->Count;
	ViewSelectionStatic->Text = String::Concat("Image: ",(FILELISTINDEX+1).ToString()," of ",C.ToString());

	int xposnew = (int)((double(SubImageSlideX->Value) / double(SubImageSlideX->Maximum)*double(width)));
	int yposnew = (int)((double(SubImageSlideY->Value) / double(SubImageSlideY->Maximum)*double(height)));
	int xhalfwidthnew = (int)((double(HalfWidthXUpD->Value)*double(width) / double(SubImageSlideX->Maximum)));
	int yhalfwidthnew = (int)((double(HalfWidthYUpD->Value)*double(height) / double(SubImageSlideY->Maximum)));

	SubImageSlideX->Maximum = width;
	SubImageSlideY->Maximum = height;
	HalfWidthXUpD->Maximum = (width-1)/2;
	HalfWidthYUpD->Maximum = (height-1)/2;

	if (FIRSTLOAD != true)
	{
		try
		{
			SubImageSlideX->Value = xposnew;
			SubImageSlideY->Value = yposnew;
			HalfWidthXUpD->Value = xhalfwidthnew;
			HalfWidthYUpD->Value = yhalfwidthnew;
		}
		catch (...){}
	}

	if (FIRSTLOAD == true)//first load?...set contrast to wide
	{
		FIRSTLOAD = false;
		ContrastWideRad->PerformClick();
		try
		{
			SUBIMAGE_HWX = Convert::ToInt32(GetReg("CCDLAB", "SubImageHWX"));
			HalfWidthXUpD->Value = SUBIMAGE_HWX;
			SUBIMAGE_HWY = Convert::ToInt32(GetReg("CCDLAB", "SubImageHWY"));
			HalfWidthYUpD->Value = SUBIMAGE_HWY;
			XPOS_CURSOR = Convert::ToInt32(GetReg("CCDLAB", "XPOS_CURSOR"));
			SubImageSlideX->Value = XPOS_CURSOR + 1;
			YPOS_CURSOR = Convert::ToInt32(GetReg("CCDLAB", "YPOS_CURSOR"));
			SubImageSlideY->Value = YPOS_CURSOR + 1;
			SubImageStatsUpD();
		}
		catch (...) {}
	}

	try
	{
		ImageUpD(IMAGESET[FILELISTINDEX]->Image);
		FileTxtsUpD();
		StatTxtsUpD();
		SubImageStatsUpD();
		SubImageUpD();
		SpAxesUpD();
	}
	catch (...) {}

	OLD_INDEX = FILELISTINDEX;
	try
	{
		double val = IMAGESET[FILELISTINDEX]->Image[XPOS_CURSOR, YPOS_CURSOR];
		XYImageValueTxt->Text = val.ToString();
	}
	catch (...) {}

	if (SubImTrackPSChck->Checked)
	{
		int x = 0, y = 0;
		double max = JPMath::Max(SUBIMAGE, x, y, false);
		SubImageSlideX->Value = x + 1 + XSUBRANGE[0];
		SubImageSlideY->Value = y + 1 + YSUBRANGE[0];
		PRVXPOS_CURSOR = SubImageSlideX->Value - 1;
		PRVYPOS_CURSOR = SubImageSlideY->Value - 1;

		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();

		if (ImageWndwCntxtPlotRow->Checked)
			ROWplotUpD(false);
		if (ImageWndwCntxtPlotCol->Checked)
			COLplotUpD(false);
	}

	if (ImageWndwCntxtPlotRow->Checked)
		ROWplotUpD(false);
	if (ImageWndwCntxtPlotCol->Checked)
		COLplotUpD(false);
	if (PLOTRADIALLINE)
		RADIALLINE_PLOTUpD();
}

void Form1::DeleteFileBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		if (::MessageBox::Show("Are you sure you want to delete the file (to Recylce Bin)?","WARNING!",::MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;
		else
			::Microsoft::VisualBasic::FileIO::FileSystem::DeleteFile(IMAGESET[FILELISTINDEX]->FullFileName, ::Microsoft::VisualBasic::FileIO::UIOption::OnlyErrorDialogs, ::Microsoft::VisualBasic::FileIO::RecycleOption::SendToRecycleBin);
	}

	if (e->Button == ::MouseButtons::Right || e->Button == ::MouseButtons::Left)
	{
		int index = FILELISTINDEX;
		IMAGESET->RemoveAt(index);
		FileListDrop->Items->RemoveAt(index);
		int C = FileListDrop->Items->Count;

		if (index == C)
			index = C-1;
		if (C == 1)
		{
			BatchViewPanel->Enabled = false;
			TBSaveBatch->Enabled = false;
			TBSaveBatchOver->Enabled = false;
			TBZipAllBtn->Enabled = false;
			ImageBatchRedxnPnl->Enabled = false;
			BatchCorrectionChck->Enabled = false;
			BatchCorrectionChck->Checked = false;
			HCInsertBatch->Enabled = false;
			HCRemoveBatch->Enabled = false;
			HCExtract->Enabled = false;
			HCExtractKeyValue->Enabled = false;
			index = 0;
		}

		BatchMeanChck->Checked = false;
		BatchSumChck->Checked = false;
		BatchQuadratureChck->Checked = false;
		BatchMedianChck->Checked = false;
		BatchStdvChck->Checked = false;
		BatchMaximumChck->Checked = false;
		BatchMinimumChck->Checked = false;

		FileListDrop->SelectedIndex = index;
	}
}

void Form1::DeleteFileBtn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
}

void Form1::DeleteFileBtn_Click(System::Object ^sender, System::EventArgs ^e)
{
}

void Form1::MoveUpBtn_Click(System::Object ^sender, System::EventArgs ^e)
{
	int index = FILELISTINDEX;
	FITSImage^ img1 = IMAGESET[index];
	int C = FileListDrop->Items->Count;
	array<String^>^ files = gcnew array<String^>(C);

	if (index == 0) //then swap with end of list
	{
		FITSImage^ img2 = IMAGESET[C-1];
		IMAGESET[index] = img2;
		IMAGESET[FileListDrop->Items->Count - 1] = img1;
		index = FileListDrop->Items->Count - 1;
	}
	else
	{
		FITSImage^ img2 = IMAGESET[index-1];
		IMAGESET[index] = img2;
		IMAGESET[index-1] = img1;
		index = index - 1;
	}

	FileListDrop->Items->Clear();
	for (int i=0; i < C;i++)
	{
		files[i] = IMAGESET[i]->FileName;
	}
	FileListDrop->Items->AddRange(files);
	FileListDrop->SelectedIndex = index;
}

void Form1::MoveDownBtn_Click(System::Object ^sender, System::EventArgs ^e)
{
	int index = FILELISTINDEX;
	FITSImage^ img1 = IMAGESET[index];
	int C = FileListDrop->Items->Count;
	array<String^>^ files = gcnew array<String^>(C);

	if (index == FileListDrop->Items->Count-1) //then swap with beginning of list
	{
		FITSImage^ img2 = IMAGESET[0];
		IMAGESET[index] = img2;
		IMAGESET[0] = img1;
		index = 0;
	}
	else
	{
		FITSImage^ img2 = IMAGESET[index+1];
		IMAGESET[index] = img2;
		IMAGESET[index+1] = img1;
		index = index + 1;
	}

	FileListDrop->Items->Clear();
	for (int i=0; i < C;i++)
	{
		files[i] = IMAGESET[i]->FileName;
	}
	FileListDrop->Items->AddRange(files);
	FileListDrop->SelectedIndex = index;
}

void Form1::FindImagePtsBtn_Click(System::Object ^sender, System::EventArgs ^e)
{
	double val = Convert::ToDouble(FindImagePtsTxt->Text);
	ReplaceImagePtsTxt->Text = FindImagePtsTxt->Text;

	String^ style = FindPtsDrop->Items[FindPtsDrop->SelectedIndex]->ToString();
	FNDCOORDS = JPMath::Find(IMAGESET[FILELISTINDEX]->Image, val, style, true);
	if (FNDCOORDS->Length == 0)
	{
		::MessageBox::Show("No Points Found Matching Search Parameters...", "Warning");
		return;
	}

	float xsc = (float(ImageWindow->Size.Width)/(float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height)/(float)IMAGESET[FILELISTINDEX]->Height);
	FNDCOORDRECTS = gcnew array<Rectangle,1>(FNDCOORDS->GetLength(0));
	#pragma omp parallel for
	for (int i = 0; i < FNDCOORDS->GetLength(0); i++)
		FNDCOORDRECTS[i] = Rectangle(int((float(FNDCOORDS[i, 0]) + 0.5) * xsc - 3), int((float(FNDCOORDS[i, 1]) + 0.5) * ysc - 3), 7, 7);

	System::Windows::Forms::DialogResult q = ::MessageBox::Show(String::Concat("Found ", FNDCOORDS->GetLength(0).ToString(), " points matching seach criteria.  Would you like to plot them?"), "Plot Points?", ::MessageBoxButtons::YesNoCancel);
	switch (q)
	{
	case (System::Windows::Forms::DialogResult::Yes)://then plot the points...easy! :)
		{
			ReplaceImagePtsBtn->Enabled = true;//give access to control...and plot
			ReplaceImagePtsDrop->Enabled = true;
			ReplaceImagePtsDrop_SelectedIndexChanged(sender ,e);
			ShowFoundCoordsChck->Enabled = true;
			ShowFoundCoordsChck->Checked = true;
			break;
		}
	case (System::Windows::Forms::DialogResult::No)://need to do anything other cases?
		{
			ReplaceImagePtsBtn->Enabled = true;//give access to control...no plotting
			ReplaceImagePtsDrop->Enabled = true;
			ReplaceImagePtsDrop_SelectedIndexChanged(sender ,e);
			ShowFoundCoordsChck->Enabled = true;
			ShowFoundCoordsChck->Checked = false;
			break;
		}
	case (System::Windows::Forms::DialogResult::Cancel)://need to do anything other cases?
		{
			ReplaceImagePtsBtn->Enabled = false;//give access to control
			ReplaceImagePtsDrop->Enabled = false;
			break;
		}
	}
	ImageWindow->Refresh();

	if (q != ::DialogResult::Cancel)//ask to save point coordinates to file
	{
		if (::MessageBox::Show("Save point values & coordinates to file?","Save Points?",::MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;

		array<double>^ radeg = gcnew array<double>(FNDCOORDS->GetLength(0));
		array<double>^ decdeg = gcnew array<double>(FNDCOORDS->GetLength(0));

		if (SHOW_WCSCOORDS && IMAGESET[FILELISTINDEX]->WCS->Exists())
			for (int i = 0; i < FNDCOORDS->GetLength(0); i++)
			{
				double ra, dec;
				String^ r;
				String^ d;
				IMAGESET[FILELISTINDEX]->WCS->Get_Coordinate(FNDCOORDS[i, 0], FNDCOORDS[i, 1], true, "TAN", ra, dec, r, d);
				radeg[i] = ra;
				decdeg[i] = dec;
			}

		::SaveFileDialog^ sf = gcnew ::SaveFileDialog();
		sf->Filter = "Tab Delimited Text file (*.txt)|*.txt";
		if (sf->ShowDialog() == ::DialogResult::Cancel)
			return;

		FileStream^ fs = gcnew FileStream(sf->FileName,System::IO::FileMode::Create,FileAccess::Write);
		StreamWriter^ sw = gcnew StreamWriter(fs);
		String^ line = "Pixel Value" + "	" + "X" + "	" + "Y" + "	" + "Right Ascension (deg)" + "	" + "Declination (deg)";
		sw->WriteLine(line);

		for (int i = 0; i < FNDCOORDS->GetLength(0); i++)
		{
			line = IMAGESET[FILELISTINDEX]->Image[FNDCOORDS[i,0],FNDCOORDS[i,1]].ToString() + "	" + FNDCOORDS[i,0].ToString() + "	" + FNDCOORDS[i,1].ToString() + "	" + radeg[i].ToString() + "	" + decdeg[i].ToString();
			sw->WriteLine(line);
		}

		sw->Close();
		fs->Close();
	}
}

void Form1::ShowFoundCoordsChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::ReplaceImagePtsBtn_Click(System::Object ^sender, System::EventArgs ^e)
{

	int style = ReplaceImagePtsDrop->SelectedIndex;//zero <=, one ==, two >=
	if (style < 0)
	{
		::MessageBox::Show("Please Select Replacement Style from Adjacent DropDown Box...","Error...");
	}
	else
	{
		System::Windows::Forms::DialogResult q = ::MessageBox::Show("Are you really sure you would like to replace the Found Data Points?","Proceed?",::MessageBoxButtons::YesNo);

		if (q == System::Windows::Forms::DialogResult::Yes)
		{
			switch (ReplaceImagePtsDrop->SelectedIndex)
		 {
			case (0):	//value replacement
			 {
				 double val = Convert::ToDouble(ReplaceImagePtsTxt->Text);
				 IMAGESET[FILELISTINDEX]->Image = JPMath::Replace(IMAGESET[FILELISTINDEX]->Image, FNDCOORDS, val, true);
				 FileListDrop_SelectedIndexChanged(sender,e);
				 break;
			 }
			case (1):	//image min replacement
			 {
				 double val = Convert::ToDouble(ReplaceImagePtsTxt->Text);
				 IMAGESET[FILELISTINDEX]->Image = JPMath::Replace(IMAGESET[FILELISTINDEX]->Image, FNDCOORDS, IMAGESET[FILELISTINDEX]->Min, true);
				 FileListDrop_SelectedIndexChanged(sender,e);
				 break;
			 }
			case (2):	//image max replacement
			 {
				 double val = Convert::ToDouble(ReplaceImagePtsTxt->Text);
				 IMAGESET[FILELISTINDEX]->Image = JPMath::Replace(IMAGESET[FILELISTINDEX]->Image, FNDCOORDS, IMAGESET[FILELISTINDEX]->Max, true);
				 FileListDrop_SelectedIndexChanged(sender,e);
				 break;
			 }
			case (3):	//image median replacement
			 {
				 double val = Convert::ToDouble(ReplaceImagePtsTxt->Text);
				 IMAGESET[FILELISTINDEX]->Image = JPMath::Replace(IMAGESET[FILELISTINDEX]->Image, FNDCOORDS, IMAGESET[FILELISTINDEX]->Median, true);
				 FileListDrop_SelectedIndexChanged(sender,e);
				 break;
			 }
			case (4):	//image mean replacement
			 {
				 double val = Convert::ToDouble(ReplaceImagePtsTxt->Text);
				 IMAGESET[FILELISTINDEX]->Image = JPMath::Replace(IMAGESET[FILELISTINDEX]->Image, FNDCOORDS, IMAGESET[FILELISTINDEX]->Mean, true);
				 FileListDrop_SelectedIndexChanged(sender,e);
				 break;
			 }
		 }
		}
		else if (q == System::Windows::Forms::DialogResult::No)
		{
			/*ReplaceImagePtsBtn->Enabled = false;
			ReplaceImagePtsTxt->Enabled = false;
			ReplaceImagePtsDrop->Enabled = false;*/
		}
	}
}

void Form1::BatchMeanChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if (BatchMeanChck->Checked == true)
	{
		FITSImage^ f;
		double sigma = (double)ScmTxt->Value;
		if (SCMChck->Checked == true)
			f = FITSImageSet::MeanClipped(IMAGESET, true, sigma);
		else
			f = FITSImageSet::Mean(IMAGESET, true, true);
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count-1;
		}
		else
			BatchMeanChck->Checked = false;
	}
}

void Form1::BatchMedianChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if (BatchMedianChck->Checked == true)
	{
		FITSImage^ f = FITSImageSet::Median(IMAGESET, true, true, "Computing Median");
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count-1;
		}
		else
			BatchMedianChck->Checked = false;
	}
}

void Form1::BatchStdvChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if (BatchStdvChck->Checked == true)
	{
		FITSImage^ f = FITSImageSet::Stdv(IMAGESET,true,true);
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count-1;
		}
		else
			BatchStdvChck->Checked = false;
	}
}

void Form1::BatchSumChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (BatchSumChck->Checked == true)
	{
		FITSImage^ f = FITSImageSet::Sum(IMAGESET,true,true);
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count-1;
		}
		else
			BatchSumChck->Checked = false;
	}
}

void Form1::BatchQuadratureChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (BatchQuadratureChck->Checked == true)
	{
		FITSImage^ f = FITSImageSet::Quadrature(IMAGESET, true, true);
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count - 1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count - 1;
		}
		else
			BatchQuadratureChck->Checked = false;
	}
}

void Form1::BatchMinimumChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (BatchMinimumChck->Checked == true)
	{
		FITSImage^ f = FITSImageSet::Min(IMAGESET,true,true);
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count-1;
		}
		else
			BatchMinimumChck->Checked = false;
	}
}

void Form1::BatchMaximumChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (BatchMaximumChck->Checked == true)
	{
		FITSImage^ f = FITSImageSet::Max(IMAGESET,true,true);
		if (f != nullptr)
		{
			FITSImageSet::GatherHeaders(IMAGESET, f);
			IMAGESET->Add(f);
			FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FullFileName);
			FileListDrop->SelectedIndex = FileListDrop->Items->Count-1;
		}
		else
			BatchMaximumChck->Checked = false;
	}
}

void Form1::SubBiasChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if (SubBiasChck->Checked == true)
	{
		String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Multiselect = false;
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS|*.fits;*.fit;*.fts";
		ofd->Title = "Subtract file data...";

		if (ofd->ShowDialog() == ::DialogResult::OK)
		{
			DIVMULTADDSUB_FILE = ofd->FileName;
			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
			ImageOpsWrkr->RunWorkerAsync(1);
			WAITBAR->ShowDialog();
		}
		else
		{
			SubBiasChck->Checked = false;
		}
	}
}

void Form1::SubDarkChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{

}

void Form1::AddImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (AddImageChck->Checked == true)
	{
		String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Multiselect = false;
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS|*.fits;*.fit;*.fts";
		ofd->Title = "Add file data...";

		if (ofd->ShowDialog() == ::DialogResult::OK)
		{
			DIVMULTADDSUB_FILE = ofd->FileName;
			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
			ImageOpsWrkr->RunWorkerAsync(3);
			WAITBAR->ShowDialog();
		}
		else
		{
			AddImageChck->Checked = false;
		}
	}
}

void Form1::DivFlatChck_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
{
	if (DivFlatChck->Checked == true)
	{
		String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Multiselect = false;
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS|*.fits;*.fit;*.fts";
		ofd->Title = "Divide file data...";

		if (ofd->ShowDialog() == ::DialogResult::OK)
		{
			DIVMULTADDSUB_FILE = ofd->FileName;
			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
			ImageOpsWrkr->RunWorkerAsync(2);
			WAITBAR->ShowDialog();
		}
		else
		{
			DivFlatChck->Checked = false;
		}
	}
}

void Form1::MultImgChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (MultImgChck->Checked == true)
	{
		String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Multiselect = false;
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS|*.fits;*.fit;*.fts";
		ofd->Title = "Multiply file data...";

		if (ofd->ShowDialog() == ::DialogResult::OK)
		{
			DIVMULTADDSUB_FILE = ofd->FileName;
			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
			ImageOpsWrkr->RunWorkerAsync(4);
			WAITBAR->ShowDialog();
		}
		else
		{
			MultImgChck->Checked = false;
		}
	}
}

void Form1::FlipHorzBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Horizontal Flip...";
	ImageOpsWrkr->RunWorkerAsync(16);
	WAITBAR->ShowDialog();
}

void Form1::FlipVertBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Vertical Flip...";
	ImageOpsWrkr->RunWorkerAsync(17);
	WAITBAR->ShowDialog();
}

void Form1::FlipInvertBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	/*Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	ImageOpsWrkr->RunWorkerAsync(18);
	WAITBAR->ShowDialog();*/
}

void Form1::RotCCWBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "CCW Rotation...";
	ImageOpsWrkr->RunWorkerAsync(19);
	WAITBAR->ShowDialog();
}

void Form1::RotCWBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "CW Rotation...";
	ImageOpsWrkr->RunWorkerAsync(20);
	WAITBAR->ShowDialog();
}

void Form1::CutSubImBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Cropping to sub-image...";
	ImageOpsWrkr->RunWorkerAsync(7);
	WAITBAR->ShowDialog();
}

void Form1::ScalarOpBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int style = ScalarOpStyleDrop->SelectedIndex;
	double scalar;
	try
	{
		scalar =  ::Convert::ToDouble(ScalarOpValTxt->Text);
	}
	catch(...)
	{
		::MessageBox::Show(String::Concat("Scalar value: ' ",ScalarOpValTxt->Text," ' not numeric.  Try again."),"Error");
		return;
	}
	if (scalar == 0)
	{
		::MessageBox::Show(String::Concat("Scalar value of ZERO doesn't make sense.  Try again."),"Warning...");
		return;
	}
	if (style == -1)
	{
		::MessageBox::Show(String::Concat("Please select operation style from adjacent drop-down menu."),"Error...");
		return;
	}
	if (style == 2 && scalar == 1 || style == 3 && scalar == 1 || style == 4 && scalar == 1)
	{
		::MessageBox::Show(String::Concat("Multiplication, Division, or Power by ONE has no effect.  Try again."),"Warning...");
		return;
	}
	//finally go ahead

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Scalar Operation...";
	ImageOpsWrkr->RunWorkerAsync(10);
	WAITBAR->ShowDialog();
}

void Form1::MathOpBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	int style = MathOpDrop->SelectedIndex;
	if (style == -1)
	{
		::MessageBox::Show(String::Concat("Please select operation from adjacent drop-down menu."),"Error...");
		return;
	}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;

	if (MathOpDrop->SelectedIndex == 5)
	{
		WAITBAR->Text = "Normalizing...";
		ImageOpsWrkr->RunWorkerAsync(21);//21 = normalize
	}
	else if (MathOpDrop->SelectedIndex == 11)
	{
		WAITBAR->Text = "Degradient-X...";
		ImageOpsWrkr->RunWorkerAsync(25);//degradientX
	}
	else if (MathOpDrop->SelectedIndex == 12)
	{
		WAITBAR->Text = "Degradient-Y...";
		ImageOpsWrkr->RunWorkerAsync(26);//degradientY
	}
	else if (MathOpDrop->SelectedIndex == 13)//Hanning
	{
		WAITBAR->Text = "Applying Hanning Window...";
		ImageOpsWrkr->RunWorkerAsync(28);
	}
	else
		ImageOpsWrkr->RunWorkerAsync(11);//the other ones...they should be separated out here

	WAITBAR->ShowDialog();
}

void Form1::BinBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int xbin = (int)XBinUpD->Value;
	int ybin = (int)YBinUpD->Value;

	if (xbin > IMAGESET[0]->Width || ybin > IMAGESET[0]->Height)
	{
		::MessageBox::Show("Error: Binning kernel larger than image dimenions.","Error...");
		return;
	}
	if (xbin == 1 && ybin == 1)
		return;

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Binning...";
	ImageOpsWrkr->RunWorkerAsync(6);
	WAITBAR->ShowDialog();
}

void Form1::KeyValNormBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	HeaderKey^ hk = gcnew HeaderKey();
	if (hk->ShowDialog() == ::DialogResult::Cancel)
		return;
	String^ key = hk->textBox1->Text;

	for (int i = 0; i < IMAGESET->Count; i++)
	{
		int jj = IMAGESET[i]->Header->GetKeyIndex(key, false);
		if (jj == -1)
		{
			::MessageBox::Show("Key doesn't exist at file: " + (i+1).ToString(),"Error...");
			return;
		}
		try
		{
			double val = ::Convert::ToDouble(IMAGESET[i]->Header->GetKeyValue(key));
		}
		catch (...)
		{
			::MessageBox::Show("Key value doesn't convert to numeric value at file: " + (i+1).ToString(),"Error...");
			return;
		}
	}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Normalizing to Key: " + key;
	ImageOpsWrkr->RunWorkerAsync(27);
	WAITBAR->ShowDialog();
}

void Form1::ImageOpFilterTypeDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (ImageOpFilterTypeDrop->SelectedIndex == 0)//median filter...set UpD minimum to 3, value to sometihng sensible, no decimals
	{
		ImageOpFilterWidthUpD->DecimalPlaces = 0;
		if (ImageOpFilterWidthUpD->Value < 3)
			ImageOpFilterWidthUpD->Value = 3;
		ImageOpFilterWidthUpD->Minimum = 3;
		ImageOpFilterWidthUpD->Increment = 2;
		Tooltip->SetToolTip(ImageOpFilterWidthUpD, "Unit pixels");
	}

	if (ImageOpFilterTypeDrop->SelectedIndex == 1)//Gaussian convolution...change the UpD to allow decimals and more values for FWHM
	{
		ImageOpFilterWidthUpD->DecimalPlaces = 1;
		ImageOpFilterWidthUpD->Minimum = ::Convert::ToDecimal(0.1);
		ImageOpFilterWidthUpD->Increment = ::Convert::ToDecimal(0.1);
		Tooltip->SetToolTip(ImageOpFilterWidthUpD, "FWHM (pixels)");
	}
}

void Form1::ImageOpFilterBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	int type = ImageOpFilterTypeDrop->SelectedIndex;
	if (type >= 0)//if a type is selected
	{
		Form1::Enabled = false;
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;

		if (type == 0)//median filter
		{
			WAITBAR->Text = "Median Filter";
			ImageOpsWrkr->RunWorkerAsync(12);
		}
		if (type == 1)//convolution
		{
			WAITBAR->Text = "Convolution Filter";
			ImageOpsWrkr->RunWorkerAsync(13);
		}
		if (type == 2)//wiener linear filter
		{	
			ImageOpsWrkr->RunWorkerAsync(14);
		}
		if (type == 3)//wiener deconv filter
		{	
			ImageOpsWrkr->RunWorkerAsync(15);
		}

		WAITBAR->ShowDialog();
	}
}

void Form1::ImageOpsWrkr_DoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	array<int,1>^ inds;
	if (BatchCorrectionChck->Checked == false)
	{
		inds = gcnew array<int,1>(1){FILELISTINDEX};
		WAITBAR->ProgressBar->Maximum = 1;
	}
	else
	{
		inds = gcnew array<int,1>(IMAGESET->Count);
		for (int i = 0; i<IMAGESET->Count; i++)
			inds[i] = i;
	}

	switch (::Convert::ToInt32(e->Argument))
	{
	case (1):// subtract background image
		{
		FITSImage^ simg = gcnew FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, true, true, true, true);
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] - simg, true, true);
			}
			break;
		}
	case(2):// divide background image
		{
		FITSImage^ dimg = gcnew FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, true, true, false, true);
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] / dimg, true, true);
			}
			break;
		}
	case(3)://add image
		{
		FITSImage^ aimg = gcnew FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, false, true, false, true);

			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] + aimg, true, true);
			}
			break;
		}
	case(4):// multiply background image
		{
		FITSImage^ mimg = gcnew FITSImage(DIVMULTADDSUB_FILE, SUBRANGE, false, true, false, true);

			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] * mimg, true, true);
			}
			break;
		}
	case(5):
		{
			break;
		}
	case(6):// Binning
		{
			int xbin = (int)XBinUpD->Value;
			int ybin = (int)YBinUpD->Value;

			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(JPMath::Bin(IMAGESET[inds[i]]->Image, xbin, ybin, true), true, true);
			}
			break;
		}
	case(7):// Cut Sub Image
		{
			int C = IMAGESET->Count;
			ProgressBar->Maximum = C;
			int w = XSUBRANGE->Length;
			int h = YSUBRANGE->Length;
			array<double,2>^ subarray = gcnew array<double,2>(w,h);

			for (int i = 0; i < inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i);

				for (int k = 0; k < w; k++)
					for (int j = 0; j < h; j++)
						subarray[k,j] = IMAGESET[inds[i]]->Image[XSUBRANGE[k], YSUBRANGE[j]];

				String^ fname = IMAGESET[inds[i]]->FileName;
				int pind = fname->LastIndexOf(".");
				fname = fname->Substring(0,pind);
				fname = fname->Concat(fname,"_Sub_",XSUBRANGE[0].ToString(),"-",XSUBRANGE[w-1].ToString(),"_",YSUBRANGE[0].ToString(),"-",YSUBRANGE[h-1].ToString(),".fits");
				/*IMAGESET->Add(gcnew FITSImage(String::Concat(IMAGESET[i]->FilePath,fname),subarray,true));
				IMAGESET[IMAGESET->Count-1]->CopyHeader(IMAGESET[i]);
				FileListDrop->Items->Add(fname);*/
				IMAGESET[inds[i]]->SetImage(subarray, true, true);
				IMAGESET[inds[i]]->Header->AddKey("XCROPSTT", XSUBRANGE[0].ToString(),"Cropped image x-start index (0-based)",-1);
				IMAGESET[inds[i]]->Header->AddKey("XCROPEND",(XSUBRANGE[w - 1]).ToString(),"Cropped image x-end index (0-based)",-1);
				IMAGESET[inds[i]]->Header->AddKey("YCROPSTT", YSUBRANGE[0].ToString(),"Cropped image y-start index (0-based)",-1);
				IMAGESET[inds[i]]->Header->AddKey("YCROPEND",(YSUBRANGE[h - 1]).ToString(),"Cropped image y-end index (0-based)",-1);
				//IMAGESET[inds[i]]->FileName = fname;
				//FileListDrop->Items[inds[i]] = fname;

				if (IMAGESET[inds[i]]->Header->GetKeyValue("CRPIX1") != "")//then the key exists and has a value...must adjust CRPIX1&2 to the new pixel axes placements
				{
					double crpix1 = ::Convert::ToDouble(IMAGESET[inds[i]]->Header->GetKeyValue("CRPIX1")) - XSUBRANGE[0];
					double crpix2 = ::Convert::ToDouble(IMAGESET[inds[i]]->Header->GetKeyValue("CRPIX2")) - YSUBRANGE[0];

					IMAGESET[inds[i]]->Header->SetKey("CRPIX1",crpix1.ToString(),false,0);
					IMAGESET[inds[i]]->Header->SetKey("CRPIX2",crpix2.ToString(),false,0);
				}


			}
			/*FileListDrop->SelectedIndex = C;*/

			/*BatchViewPanel->Enabled = true;
			TBSaveBatch->Enabled = true;
			TBSaveBatchOver->Enabled = true;
			TBZipAllBtn->Enabled = true;
			BatchCorrectionChck->Checked = true;
			BatchCorrectionChck->Enabled = true;
			ImageBatchRedxnPnl->Enabled = true;
			EMBatch->Enabled = true;
			HCInsertBatch->Enabled = true;
			HCRemoveBatch->Enabled = true;

			SubBiasChck->Checked = false;
			MultImgChck->Checked = false;
			AddImageChck->Checked = false;
			DivFlatChck->Checked = false;
			BatchMeanChck->Checked = false;
			BatchSumChck->Checked = false;
			BatchQuadratureChck->Checked = false;
			BatchMedianChck->Checked = false;
			BatchStdvChck->Checked = false;
			BatchMaximumChck->Checked = false;
			BatchMinimumChck->Checked = false;*/
			break;
		}
	case(8):
		{	
			//array<double, 2>^ newimg;
			for (int i = 0; i < inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i);

				//newimg = gcnew array<double, 2>(IMAGESET[inds[i]]->Width + PADDING[0] + PADDING[1], IMAGESET[inds[i]]->Height + PADDING[2] + PADDING[3]);

				/*#pragma omp parallel for
				for (int x = 0; x < IMAGESET[inds[i]]->Width; x++)
					for (int y = 0; y < IMAGESET[inds[i]]->Height; y++)
						newimg[x + PADDING[0], y + PADDING[2]] = IMAGESET[inds[i]][x, y];*/

				IMAGESET[inds[i]]->SetImage(JPMath::Pad(IMAGESET[inds[i]]->Image, PADDING, true), true, true);
			}
			break;
		}
	case(9):
		{
			//array<double, 2>^ newimg;
			for (int i = 0; i < inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i);

				/*newimg = gcnew array<double, 2>(CROPPING[1] - CROPPING[0] + 1, CROPPING[3] - CROPPING[2] + 1);

				#pragma omp parallel for
				for (int x = 0; x < newimg->GetLength(0); x++)
					for (int y = 0; y < newimg->GetLength(1); y++)
						newimg[x, y] = IMAGESET[inds[i]][x + CROPPING[0] - 1, y + CROPPING[2] - 1];*/

				IMAGESET[inds[i]]->SetImage(JPMath::Crop(IMAGESET[inds[i]]->Image, CROPPING, true), true, true);
			}
			break;
		}
	case(10)://scalar ops
		{
			double scalar = ::Convert::ToDouble(ScalarOpValTxt->Text);
			int style = ScalarOpStyleDrop->SelectedIndex;

			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i);

				switch (style)
				{
				case(0):// +
					{
						IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] + scalar, true, true);
						break;
					}
				case(1):// -
					{
						IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] - scalar, true, true);
						break;
					}
				case(2):// *
					{
						IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] * scalar, true, true);
						break;
					}
				case(3):// /
					{
						IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] / scalar, true, true);
						break;
					}
				case(4):// ^
					{
						IMAGESET[inds[i]]->SetImage(IMAGESET[inds[i]] ^ scalar, true, true);
						break;
					}
				}
			}
			FileListDrop_SelectedIndexChanged(sender,e);
			break;
		}
	case(11)://Math Ops
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i);

				int style = MathOpDrop->SelectedIndex;
				switch (style)
				{
				case(0)://round
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Round(IMAGESET[inds[i]]->Image, 0, true), true, true);
						break;
					}
				case(1)://floor
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Floor(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(2)://ceil
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Ceil(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(3)://abs
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Abs(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(4)://below one (changes < 1 to 1)
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Floor(IMAGESET[inds[i]]->Image, 1), true, true);
						break;
					}
				case(6)://sqrt
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Sqrt(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(7)://Log
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Log(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(8)://10^
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Exp(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(9)://Ln
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Ln(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				case(10)://e^
					{
					IMAGESET[inds[i]]->SetImage(JPMath::Exp(IMAGESET[inds[i]]->Image, true), true, true);
						break;
					}
				}
			}
			FileListDrop_SelectedIndexChanged(sender,e);
			break;
		}
	case(12)://Median Filter
		{
			int size = (int)ImageOpFilterWidthUpD->Value;
			
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);
			
				String^ filename = IMAGESET[inds[i]]->FullFileName;
				filename = filename->Substring(0,filename->LastIndexOf(".")) + "_MEDFILTER_" + ImageOpFilterWidthUpD->Value.ToString() + filename->Substring(filename->LastIndexOf("."));
				FITSImage^ f = gcnew FITSImage(filename, JPMath::MedianFilter(IMAGESET[inds[i]]->Image, (size - 1) / 2, true), true, true);
				f->Header->CopyHeaderFrom(IMAGESET[inds[i]]->Header);//  CopyHeader(IMAGESET[inds[i]]);
				IMAGESET->Add(f);
				FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FileName);
			}
			FileListDrop->SelectedIndex = FileListDrop->Items->Count - 1;
			BatchViewPanel->Enabled = true;
			TBSaveBatch->Enabled = true;
			TBSaveBatchOver->Enabled = true;
			TBZipAllBtn->Enabled = true;
			break;
		}
	case(13)://convolution filter
		{
			double FWHM = (double)ImageOpFilterWidthUpD->Value;
			double sig = FWHM/(2*Math::Sqrt(2*Math::Log(2)));
			array<double,2>^ g = JPMath::Gaussian(1, FWHM, (int)Math::Ceiling(sig*5), false);
			g = JPMath::MatrixDivScalar(g, JPMath::Sum(g, true), false);
			
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				String^ filename = IMAGESET[inds[i]]->FullFileName;
				filename = filename->Substring(0,filename->LastIndexOf(".")) + "_GAUSSFILTER_" + ImageOpFilterWidthUpD->Value.ToString() + filename->Substring(filename->LastIndexOf("."));
				FITSImage^ f = gcnew FITSImage(filename, JPMath::MatrixConvolveMatrix(IMAGESET[inds[i]]->Image, g, true), true, true);
				f->Header->CopyHeaderFrom(IMAGESET[inds[i]]->Header);//  CopyHeader(IMAGESET[inds[i]]);
				IMAGESET->Add(f);
				FileListDrop->Items->Add(IMAGESET[IMAGESET->Count-1]->FileName);
			}
			FileListDrop->SelectedIndex = FileListDrop->Items->Count - 1;
			BatchViewPanel->Enabled = true;
			TBSaveBatch->Enabled = true;
			TBSaveBatchOver->Enabled = true;
			TBZipAllBtn->Enabled = true;
			break;
		}
	case(14)://Wiener Linear Filter
		{
			MWNumericArray^ size = gcnew MWNumericArray((int)ImageOpFilterWidthUpD->Value);
			MLCCDLAB::ImageFilter^ IF = gcnew MLCCDLAB::ImageFilter;
			
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				MWNumericArray^ z = gcnew MWNumericArray(IMAGESET[inds[i]]->Image);
				MWNumericArray^ z2 = (MWNumericArray^)IF->WienerFilter2D(z,size);

				IMAGESET->Add(gcnew FITSImage(String::Concat(IMAGESET[inds[i]]->FilePath,inds[i].ToString()),(array<double,2>^)z2->ToArray(MWArrayComponent::Real),true, true));
				FileListDrop->Items->Add(inds[i].ToString());
			}
			FileListDrop->SelectedIndex = FileListDrop->Items->Count - 1;
			BatchViewPanel->Enabled = true;
			TBSaveBatch->Enabled = true;
			TBSaveBatchOver->Enabled = true;
			TBZipAllBtn->Enabled = true;
			break;
		}
	case(15)://Wiener Deconv Filter
		{
			MWNumericArray^ FWHM = gcnew MWNumericArray((double)ImageOpFilterWidthUpD->Value);
			MLCCDLAB::ImageFilter^ IF = gcnew MLCCDLAB::ImageFilter;

			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				MWNumericArray^ z = gcnew MWNumericArray(IMAGESET[inds[i]]->Image);
				MWNumericArray^ z2 = (MWNumericArray^)IF->WienerDeconv(z,FWHM);

				IMAGESET->Add(gcnew FITSImage(String::Concat(IMAGESET[inds[i]]->FilePath,inds[i].ToString()),(array<double,2>^)z2->ToArray(MWArrayComponent::Real),true, true));
				FileListDrop->Items->Add(inds[i].ToString());
			}
			FileListDrop->SelectedIndex = FileListDrop->Items->Count - 1;
			BatchViewPanel->Enabled = true;
			TBSaveBatch->Enabled = true;
			TBSaveBatchOver->Enabled = true;
			TBZipAllBtn->Enabled = true;
			break;
		}
	case(16)://flip horizontal
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->FlipHorizontal();
			}
			break;
		}
	case(17)://flip vertical
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->FlipVertical();
			}
			break;
		}
	case(18)://invert (horiz + vertical)
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->FlipHorizontal();
				IMAGESET[inds[i]]->FlipVertical();
			}
			break;
		}
	case(19)://rotate CCW
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->RotateCW(false);
			}
			break;
		}
	case(20)://rotate CW
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->RotateCW(true);
			}
			break;
		}
	case(21)://normalize
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(JPMath::MatrixDivScalar(IMAGESET[inds[i]]->Image,IMAGESET[inds[i]]->Mean, true),true, true);
			}
			break;
		}
	case(22)://rotate
		{
			try
			{
				/*MWNumericArray^ angle = gcnew MWNumericArray(-(double)RotateAngleUpD->Value);
				MLCCDLAB::Rotate^ ROT = gcnew MLCCDLAB::Rotate;*/

				for (int i=0; i<inds->Length; i++)
				{
					if (WAITBAR->DialogResult == ::DialogResult::Cancel)
						return;
					ImageOpsWrkr->ReportProgress(i+1);

					//rotate image here
					/*MWNumericArray^ z = gcnew MWNumericArray(IMAGESET[inds[i]]->Image);
					MWNumericArray^ z2 = (MWNumericArray^)ROT->ImageRotate(z, angle);
					IMAGESET[inds[i]]->SetImage((array<double,2>^)z2->ToArray(MWArrayComponent::Real),true);*/

					if (RotateBtnCntxtNearest->Checked)
						IMAGESET[inds[i]]->SetImage(JPMath::RotateShiftArray(IMAGESET[inds[i]]->Image, (double)RotateAngleUpD->Value * Math::PI / 180, Double::MaxValue, Double::MaxValue, "nearest", 0, 0, true), true, true);
					if (RotateBtnCntxtBiLinear->Checked)
						IMAGESET[inds[i]]->SetImage(JPMath::RotateShiftArray(IMAGESET[inds[i]]->Image, (double)RotateAngleUpD->Value * Math::PI / 180, Double::MaxValue, Double::MaxValue, "bilinear", 0, 0, true), true, true);
					if (RotateBtnCntxtLanczos3->Checked)
						IMAGESET[inds[i]]->SetImage(JPMath::RotateShiftArray(IMAGESET[inds[i]]->Image, (double)RotateAngleUpD->Value * Math::PI / 180, Double::MaxValue, Double::MaxValue, "lanc3", 0, 0, true), true, true);
					if (RotateBtnCntxtLanczos4->Checked)
						IMAGESET[inds[i]]->SetImage(JPMath::RotateShiftArray(IMAGESET[inds[i]]->Image, (double)RotateAngleUpD->Value * Math::PI / 180, Double::MaxValue, Double::MaxValue, "lanc4", 0, 0, true), true, true);
					if (RotateBtnCntxtLanczos5->Checked)
						IMAGESET[inds[i]]->SetImage(JPMath::RotateShiftArray(IMAGESET[inds[i]]->Image, (double)RotateAngleUpD->Value * Math::PI / 180, Double::MaxValue, Double::MaxValue, "lanc5", 0, 0, true), true, true);
				}
			}
			catch (Exception^ e)
			{
				::MessageBox::Show(e->Message + "  " + e->Data + "    " + e->TargetSite + "   " + e->Source + "   " + e->StackTrace);
			}
			break;
		}
	case(23)://horz shift
		{
			int shift = (int)NShiftHorzUpD->Value;

			for (int ii=0; ii<inds->Length; ii++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(ii+1);
				IMAGESET[inds[ii]]->SetImage(JPMath::ShiftArrayInt(IMAGESET[inds[ii]]->Image, shift, 0, true),true, true);
			}
			break;
		}
	case(24)://vert shift
		{
			int shift = (int)NShiftVertUpD->Value;
			
			for (int ii=0; ii<inds->Length; ii++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(ii+1);
				IMAGESET[inds[ii]]->SetImage(JPMath::ShiftArrayInt(IMAGESET[inds[ii]]->Image, 0, shift, true),true, true);
			}
			break;
		}
	case (25)://degradientX
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(JPMath::DeGradient(IMAGESET[inds[i]]->Image, 0, true), true, true);
			}
			break;
		}
	case (26)://degradientY
		{
			for (int i=0; i<inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(JPMath::DeGradient(IMAGESET[inds[i]]->Image, 1, true), true, true);
			}
			break;
		}
	case (27)://Normalize to key
		{
			try
			{
				String^ key = (String^)GetReg("CCDLAB", "NormHeaderKey");

				for (int i=0; i<inds->Length; i++)
				{
					if (WAITBAR->DialogResult == ::DialogResult::Cancel)
						return;
					ImageOpsWrkr->ReportProgress(i+1);

					double val = ::Convert::ToDouble(IMAGESET[inds[i]]->Header->GetKeyValue(key));

					IMAGESET[inds[i]]->SetImage(JPMath::MatrixDivScalar(IMAGESET[inds[i]]->Image, val, true), true, true);
					IMAGESET[inds[i]]->Header->AddKey("KEYNORM","true","Image Normalized to: " + key,-1);
				}
			}
			catch (Exception ^e)
			{
				MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
			}
			break;
		}
	case (28)://Hanning Window
		{
			for (int i = 0; i < inds->Length; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				ImageOpsWrkr->ReportProgress(i+1);

				IMAGESET[inds[i]]->SetImage(JPMath::Hanning(IMAGESET[inds[i]]->Image, true), true, true);
			}
			break;
		}
	}
}

void Form1::ImageOpsWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat("Processing file: ",e->ProgressPercentage," of ",WAITBAR->ProgressBar->Maximum);
	WAITBAR->Refresh();
}

void Form1::ImageOpsWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	Form1::Enabled = true;
	WAITBAR->Close();
	FileListDrop_SelectedIndexChanged(sender,e);

	::GC::Collect(3,::GCCollectionMode::Forced);
}

void Form1::RotateBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (double(RotateAngleUpD->Value) == 0.0)
		return;

	RotateBtnCntxtBiLinear->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtBiLinear"));
	RotateBtnCntxtLanczos3->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtLanczos3"));
	RotateBtnCntxtLanczos4->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtLanczos4"));
	RotateBtnCntxtLanczos5->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtLanczos5"));
	RotateBtnCntxtNearest->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtNearest"));

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Rotating...";
	ImageOpsWrkr->RunWorkerAsync(22);
	WAITBAR->ShowDialog();
}

void Form1::RotateBtnCntxt_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	RotateBtnCntxtBiLinear->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtBiLinear"));
	RotateBtnCntxtLanczos3->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtLanczos3"));
	RotateBtnCntxtLanczos4->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtLanczos4"));
	RotateBtnCntxtLanczos5->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtLanczos5"));
	RotateBtnCntxtNearest->Checked = Convert::ToBoolean(GetReg("CCDLAB", "RotateBtnCntxtNearest"));
}

void Form1::RotateBtnCntxtBiLinear_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (RotateBtnCntxtBiLinear->Checked)
	{
		RotateBtnCntxtLanczos3->Checked = false;
		RotateBtnCntxtLanczos4->Checked = false;
		RotateBtnCntxtLanczos5->Checked = false;
		RotateBtnCntxtNearest->Checked = false;
	}

	SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest->Checked);

	RotateBtnCntxt->Show();
}

void Form1::RotateBtnCntxtLanczos3_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (RotateBtnCntxtLanczos3->Checked)
	{
		RotateBtnCntxtBiLinear->Checked = false;
		RotateBtnCntxtLanczos4->Checked = false;
		RotateBtnCntxtLanczos5->Checked = false;
		RotateBtnCntxtNearest->Checked = false;
	}

	SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest->Checked);

	RotateBtnCntxt->Show();
}

void Form1::RotateBtnCntxtLanczos4_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (RotateBtnCntxtLanczos4->Checked)
	{
		RotateBtnCntxtLanczos3->Checked = false;
		RotateBtnCntxtBiLinear->Checked = false;
		RotateBtnCntxtLanczos5->Checked = false;
		RotateBtnCntxtNearest->Checked = false;
	}

	SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest->Checked);

	RotateBtnCntxt->Show();
}

void Form1::RotateBtnCntxtLanczos5_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (RotateBtnCntxtLanczos5->Checked)
	{
		RotateBtnCntxtLanczos3->Checked = false;
		RotateBtnCntxtLanczos4->Checked = false;
		RotateBtnCntxtBiLinear->Checked = false;
		RotateBtnCntxtNearest->Checked = false;
	}

	SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest->Checked);

	RotateBtnCntxt->Show();
}

void Form1::RotateBtnCntxtNearest_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (RotateBtnCntxtNearest->Checked)
	{
		RotateBtnCntxtLanczos3->Checked = false;
		RotateBtnCntxtLanczos4->Checked = false;
		RotateBtnCntxtLanczos5->Checked = false;
		RotateBtnCntxtBiLinear->Checked = false;
	}

	SetReg("CCDLAB", "RotateBtnCntxtBiLinear", RotateBtnCntxtBiLinear->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos3", RotateBtnCntxtLanczos3->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos4", RotateBtnCntxtLanczos4->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtLanczos5", RotateBtnCntxtLanczos5->Checked);
	SetReg("CCDLAB", "RotateBtnCntxtNearest", RotateBtnCntxtNearest->Checked);

	RotateBtnCntxt->Show();
}

void Form1::InfoStatic1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (FIRSTLOAD)
		return;

	Label^ keylabel = (Label^)sender;
	String^ key = keylabel->Text->Substring(0, keylabel->Text->Length - 1);
	int keyindex = IMAGESET[FILELISTINDEX]->Header->GetKeyIndex(key, false);
	if (keyindex == -1)
	{
		HeaderTxt->ClearSelected();
		return;
	}
	ViewHeaderBtn->Checked = true;
	HeaderTxt->ClearSelected();
	HeaderTxt->SelectedIndex = keyindex;
}

void Form1::InfoStatic1_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	if (FIRSTLOAD)
		return;

	Label^ label = (Label^)sender;
	label->Font = gcnew ::Font(label->Font, ::FontStyle::Bold | ::FontStyle::Underline);
	label->Refresh();

	InfoCntxt->SuspendLayout();
	InfoCntxt->Items->Clear();
	for (int i = 0; i < IMAGESET[FILELISTINDEX]->Header->HeaderKeys->Length; i++)
	{
		InfoCntxt->Items->Add(IMAGESET[FILELISTINDEX]->Header->HeaderKeys[i]);
		InfoCntxt->Items[i]->Click += gcnew System::EventHandler(this, &Form1::InfoCntxt_ItemClicked);
	}
	InfoCntxt->ResumeLayout();
	InfoCntxt->Tag =  sender;
	label->Refresh();
}

void Form1::InfoStatic1_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	Label^ label = (Label^)sender;
	label->Font = gcnew ::Font(label->Font, ::FontStyle::Regular | ::FontStyle::Underline);
	label->Refresh();
}

void Form1::InfoCntxt_ItemClicked(System::Object ^sender, System::EventArgs ^e)
{
	Label^ label = (Label^)InfoCntxt->Tag;
	String^ s = sender->ToString();
	label->Text = s + ":";
	FileTxtsUpD();
	SetReg("CCDLAB", "InfoStatic1", InfoStatic1->Text);
	SetReg("CCDLAB", "InfoStatic2", InfoStatic2->Text);
	SetReg("CCDLAB", "InfoStatic3", InfoStatic3->Text);
	SetReg("CCDLAB", "InfoStatic4", InfoStatic4->Text);
	SetReg("CCDLAB", "InfoStatic5", InfoStatic5->Text);
}

void Form1::ImageSumStatic_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	StatsCopyClipBrdCntxt->Tag = sender;
	Label^ label = (Label^)sender;
	label->Font = gcnew ::Font(label->Font, ::FontStyle::Underline);
	label->Refresh();
}

void Form1::ImageSumStatic_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	Label^ label = (Label^)sender;
	label->Font = gcnew ::Font(label->Font, ::FontStyle::Regular);
	Form1::Tooltip->SetToolTip(label, "");
	label->Refresh();
}

void Form1::StatsCopyClipBrdCntxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	Label^ label = (Label^)StatsCopyClipBrdCntxt->Tag;
	String^ labelname = label->Name;

	StringBuilder^ clipboarddata = gcnew StringBuilder();

	int oldfilelistindex = FILELISTINDEX;

	for (int i = 0; i < IMAGESET->Count; i++)
	{
		if (labelname->Equals("ImageMaxStatic"))
			clipboarddata->AppendLine(IMAGESET[i]->Max.ToString());
		if (labelname->Equals("ImageMinStatic"))
			clipboarddata->AppendLine(IMAGESET[i]->Min.ToString());
		if (labelname->Equals("ImageMeanStatic"))
			clipboarddata->AppendLine(IMAGESET[i]->Mean.ToString());
		if (labelname->Equals("ImageMedianStatic"))
			clipboarddata->AppendLine(IMAGESET[i]->Median.ToString());
		if (labelname->Equals("ImageSumStatic"))
			clipboarddata->AppendLine(IMAGESET[i]->Sum.ToString());
		if (labelname->Equals("ImageStdvStatic"))
			clipboarddata->AppendLine(IMAGESET[i]->Std.ToString());

		if (!labelname->Contains("SubImage"))
			continue;
		
		FILELISTINDEX = i;
		SubImageStatsUpD();
		if (labelname->Equals("SubImageMaxStatic"))
			clipboarddata->AppendLine(SUBIMAGEMAX.ToString());
		if (labelname->Equals("SubImageMinStatic"))
			clipboarddata->AppendLine(SUBIMAGEMIN.ToString());
		if (labelname->Equals("SubImageMeanStatic"))
			clipboarddata->AppendLine(SUBIMAGEMEAN.ToString());
		if (labelname->Equals("SubImageMedianStatic"))
			clipboarddata->AppendLine(SUBIMAGEMEDIAN.ToString());
		if (labelname->Equals("SubImageSumStatic"))
			clipboarddata->AppendLine(SUBIMAGESUM.ToString());
		if (labelname->Equals("SubImageStdvStatic"))
			clipboarddata->AppendLine(SUBIMAGESTD.ToString());
	}
	Clipboard::SetText(clipboarddata->ToString());

	FILELISTINDEX = oldfilelistindex;
	SubImageStatsUpD();
}

void Form1::listBox1_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	FileListDrop->Size = ::Size((int)FileListDrop->Width,20*(int)FileListDrop->Items->Count);
}

void Form1::listBox1_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	FileListDrop->Size = ::Size((int)FileListDrop->Width,28);
}

void Form1::FileListDrop_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{

}

void Form1::MainTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "MainTabIndex",MainTab->SelectedIndex);
}

void Form1::ConvertFromTextMenu_Click(System::Object^  sender, System::EventArgs^  e)
{
	Windows::Forms::OpenFileDialog^ dlg = gcnew Windows::Forms::OpenFileDialog();
	dlg->InitialDirectory = (String^)GetReg("CCDLAB", "OpenTextDataPath");
	dlg->Filter = "Text Files (*.txt)|*.txt";
	dlg->Multiselect = true;
	dlg->Title = "Open tab-delimited or white-space-delimited Text Data File(s)";
	::DialogResult res = dlg->ShowDialog();

	if (res == ::DialogResult::OK)
	{
		int ind;
		String^ dir;
		array<double,2>^ arr;
		String^ filename;
		ind = dlg->FileNames[0]->LastIndexOf("\\");
		dir = dlg->FileNames[0]->Substring(0,ind);
		SetReg("CCDLAB", "OpenTextDataPath",dir);
		for (int i = 0; i < dlg->FileNames->Length; i++)
		{
			arr = FITSImage::ConvertTxtToDblArray(dlg->FileNames[i], true);
			ind = dlg->FileNames[i]->LastIndexOf(".");
			filename = dlg->FileNames[i]->Substring(0,ind);
			filename = String::Concat(filename,".fits");

			JPFITS::FITSImage^ f = gcnew FITSImage(filename, arr, false, true);
			f->WriteImage(::TypeCode::Double, true);
		}
		Windows::Forms::MessageBox::Show("Conversion Successful","Done!");
	}
}

void Form1::Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyValue == 39)//right arrow
	{
		ViewNextBtn->PerformClick();
	}
}

void Form1::ClipToContrastBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	#pragma omp parallel for
	for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
	{
		for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
		{
			if (IMAGESET[FILELISTINDEX]->Image[x, y] < DIMCLIM[0])
				IMAGESET[FILELISTINDEX]->Image[x, y] = DIMCLIM[0];
			else if (IMAGESET[FILELISTINDEX]->Image[x, y] > DIMCLIM[1])
				IMAGESET[FILELISTINDEX]->Image[x, y] = DIMCLIM[1];

			IMAGESET[FILELISTINDEX]->Image[x, y] -= DIMCLIM[0];
			IMAGESET[FILELISTINDEX]->Image[x, y] /= ((DIMCLIM[1] - DIMCLIM[0]) / 255);
		}
	}

	IMAGESET[FILELISTINDEX]->StatsUpD(true);

	ContrastFullRad->Checked = true;
	FileListDrop_SelectedIndexChanged(sender,e);
}

void Form1::CombineRGBBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	IMAGEBMP = JPBitMap::RGBBitMap(IMAGESET[0]->Image, IMAGESET[1]->Image, IMAGESET[2]->Image);
	ImageWindow->Refresh();
}

void Form1::RGBSaveBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	::SaveFileDialog^ sfd = gcnew ::SaveFileDialog();
	sfd->InitialDirectory = (String^)::GetReg("CCDLAB","OpenFilesPath");
	sfd->Filter = "JPEG|*.jpeg";
	sfd->AddExtension = true;
	if (sfd->ShowDialog() == ::DialogResult::Cancel)
		return;

	IMAGEBMP->Save(sfd->FileName, ::Drawing::Imaging::ImageFormat::Jpeg);
}

void Form1::InfoTxt1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button != ::MouseButtons::Right)
		return;

	try
	{
		Label^ infotxtlabel = (Label^)sender;
		String^ infotxt = infotxtlabel->Text;
		::Clipboard::SetText(infotxt);
		Form1::Tooltip->SetToolTip(infotxtlabel, infotxt + " copied to clipboard.");
	}
	catch (...)
	{

	}
}

void Form1::InfoTxt1_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	Label^ label = (Label^)sender;
	label->Font = gcnew ::Font(label->Font, ::FontStyle::Underline | ::FontStyle::Bold);
	label->Refresh();
}

void Form1::InfoTxt1_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	Label^ label = (Label^)sender;
	label->Font = gcnew ::Font(label->Font, ::FontStyle::Regular | ::FontStyle::Bold);
	Form1::Tooltip->SetToolTip(label, "");
	label->Refresh();
}

void Form1::ImageSumTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->Sum.ToString());
		Form1::Tooltip->SetToolTip(ImageSumTxt,"Sum copied to clipboard.");
	}
}

void Form1::ImageMinTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->Min.ToString());
		Form1::Tooltip->SetToolTip(ImageMinTxt,"Minimum copied to clipboard.");
	}
}

void Form1::ImageMaxTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->Max.ToString());
		Form1::Tooltip->SetToolTip(ImageMaxTxt,"Maximum copied to clipboard.");
	}
}

void Form1::ImageMedianTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->Median.ToString());
		Form1::Tooltip->SetToolTip(ImageMedianTxt,"Median copied to clipboard.");
	}
}

void Form1::ImageMeanTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->Mean.ToString());
		Form1::Tooltip->SetToolTip(ImageMeanTxt,"Mean copied to clipboard.");
	}
}

void Form1::ImageStdTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->Std.ToString());
		Form1::Tooltip->SetToolTip(ImageStdTxt,"Standard Deviation copied to clipboard.");
	}
}

void Form1::FileNameTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(IMAGESET[FILELISTINDEX]->FileName);
		Form1::Tooltip->SetToolTip(FileNameTxt,"File name copied to clipboard.");
	}
}

void Form1::FileNameTxt_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	Form1::Tooltip->SetToolTip(FileNameTxt,"");
}

void Form1::SubImageRATxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		double cval1, cval2;
		IMAGESET[FILELISTINDEX]->WCS->Get_Coordinate((double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], true, "TAN", cval1, cval2);

		String^ str = cval1 + " " + cval2;
		Clipboard::SetText(str);
		Form1::Tooltip->SetToolTip((Label^)sender, "World Coordinate " + str + " copied to clipboard.");
	}
}

void Form1::SubImageSumTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(SUBIMAGESUM.ToString());
		Form1::Tooltip->SetToolTip(SubImageSumTxt,"Subimage Sum copied to clipboard.");
	}
}

void Form1::SubImageMinTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(SUBIMAGEMIN.ToString());
		Form1::Tooltip->SetToolTip(SubImageMinTxt,"Subimage Min copied to clipboard.");
	}
}

void Form1::SubImageMaxTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(SUBIMAGEMAX.ToString());
		Form1::Tooltip->SetToolTip(SubImageMaxTxt,"Subimage Max copied to clipboard.");
	}
}

void Form1::SubImageMedianTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(SUBIMAGEMEDIAN.ToString());
		Form1::Tooltip->SetToolTip(SubImageMedianTxt,"Subimage Median copied to clipboard.");
	}
}

void Form1::SubImageMeanTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(SUBIMAGEMEAN.ToString());
		Form1::Tooltip->SetToolTip(SubImageMeanTxt,"Subimage Mean copied to clipboard.");
	}
}

void Form1::SubImageStdTxt_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		::Clipboard::SetText(SUBIMAGESTD.ToString());
		Form1::Tooltip->SetToolTip(SubImageStdTxt,"Subimage Stdv copied to clipboard.");
	}
}

void Form1::aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	About^ abt = gcnew About();
	abt->ShowDialog(this);
}

void Form1::WriteImageSet()
{
	BatchSaveDlg^ bsd = gcnew BatchSaveDlg();
	bsd->DirectoryTxt->Text = IMAGESET->GetCommonDirectory();
	bsd->ShowDialog(this);

	if (bsd->DialogResult == System::Windows::Forms::DialogResult::Cancel)//then do nothing
		return;

	String^ dir = bsd->DirectoryTxt->Text;
	bool UseExistingPaths = bsd->UseOrigDirChck->Checked;

	if (!Directory::Exists(dir) && !UseExistingPaths)
	{
		::DialogResult dr = MessageBox::Show("Directory doesn't exist. Do you want to create it?","Directory...",::MessageBoxButtons::OKCancel);

		if (dr == ::DialogResult::Cancel)
		{
			WriteImageSet();
			return;
		}
		if (dr == ::DialogResult::OK)
			Directory::CreateDirectory(dir);
	}

	if (bsd->DialogResult == ::DialogResult::OK)//   append/remove/remove aft btn
	{
		if (bsd->AppendBtn->Text->Contains("Remove") && bsd->AppendTxt->Text == "*")
		{
			MessageBox::Show("Can't auto-increment when removing subtext.", "Error...");
			WriteImageSet();
			return;
		}

		if (bsd->AppendTxt->Text == String::Empty)//then do nothing and notify
		{
			MessageBox::Show("Blank Appendage Entered so NO Files Written...", "Error...");
			WriteImageSet();
			return;
		}
	}

	if (bsd->DialogResult == System::Windows::Forms::DialogResult::OK)//then append
		if (::MessageBox::Show("Are you sure?", "Proceed?", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
		{
			WriteImageSet();
			return;
		}

	if (bsd->DialogResult == System::Windows::Forms::DialogResult::Ignore)//then overwrite, but first confirm
		if (::MessageBox::Show("Are you sure you want to overwrite all of the files?", "Warning...", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
		{
			WriteImageSet();
			return;
		}

	//then go ahead and make the (new?) filenames
	String^ filepath = bsd->DirectoryTxt->Text;
	String^ extension = ::Convert::ToString(bsd->FileExtension->Items[bsd->FileExtension->SelectedIndex]);
	String^ fullfilename;
	bool appendremovebtn = bsd->DialogResult == System::Windows::Forms::DialogResult::OK;//else write/overwrite
	String^ apptxt = bsd->AppendTxt->Text;
	bool autoinc = apptxt == "*";
	bool append = bsd->AppendBtn->Text == "Append";//else remove
	for (int i = 0; i < IMAGESET->Count; i++)
	{
		String^ filename = IMAGESET[i]->FileName;
		int ind = filename->LastIndexOf(".");

		if (appendremovebtn)
		{
			if (append)
			{
				if (autoinc)
					filename = String::Concat(filename->Substring(0, ind), " (", i.ToString(), ")", extension);
				else
					filename = String::Concat(filename->Substring(0, ind), apptxt, extension);
			}
			else//remove or remove aft
			{
				if (bsd->AppendBtn->Text == "Remove")
					filename = filename->Replace(apptxt, "");
				else//remove after
					if (filename->Contains(apptxt))
					{
						int ind1 = filename->IndexOf(apptxt);// +apptxt->Length;
						filename = filename->Remove(ind1) + extension;// , ind - ind1);

					}
			}
		}
		else//write/overwrite
			filename = String::Concat(filename->Substring(0, ind), extension);

		if (UseExistingPaths)
			filepath = IMAGESET[i]->FilePath;

		fullfilename = filepath + filename;
		IMAGESET[i]->FullFileName = fullfilename;
	}
	FileListDrop->Items->Clear();
	FileListDrop->Items->AddRange(IMAGESET->FileNames);

	if (extension == ".fts" || extension == ".fits" || extension == ".fit")
	{
		IMAGESET->Write(FILESAVEPREC, true, true, "");
		return;
	}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Saving...";
	WriteImageSetBGWrkr->RunWorkerAsync(IMAGESET->FullFileNames);
	WAITBAR->ShowDialog();
}

void Form1::WriteImageSetBGWrkr_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
	array<String^>^ fullfilenames = (array<String^>^)e->Argument;
	String^ extension = Path::GetExtension(fullfilenames[0]);

	for (int i = 0; i < IMAGESET->Count; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;
		WriteImageSetBGWrkr->ReportProgress(i + 1);

		if (extension == ".jpg")
		{
			if (IMAGESET[i]->Width < 256 || IMAGESET[i]->Height < 256)
			{
				System::Drawing::Bitmap^ bmp1 = JPBitMap::ArrayToBmp(IMAGESET[i]->Image, ContrastScaleDrop->SelectedIndex, ColourMapDrop->SelectedIndex, InvertContrastChck->Checked, DIMCLIM, ImageWindow->Width, ImageWindow->Height, OPTIMGVIEWINVERTY);
				bmp1->Save(fullfilenames[i], ::Imaging::ImageFormat::Jpeg);
			}
			else
			{
				System::Drawing::Bitmap^ bmp1 = JPBitMap::ArrayToBmp(IMAGESET[i]->Image, ContrastScaleDrop->SelectedIndex, ColourMapDrop->SelectedIndex, InvertContrastChck->Checked, DIMCLIM, IMAGESET[i]->Width, IMAGESET[i]->Height, OPTIMGVIEWINVERTY);
				bmp1->Save(fullfilenames[i], ::Imaging::ImageFormat::Jpeg);
			}
		}

		if (extension == ".zip")//would need to write each file first as a fits, and then zip it, then delete the fits file
		{
			IMAGESET[i]->WriteImage(CCDLABPATH + "tozip.fits", FILESAVEPREC, true);
			IMAGESET[i]->FullFileName = fullfilenames[i];

			String^ ziplist = CCDLABPATH + "tozip.txt";
			StreamWriter^ sw = gcnew StreamWriter(ziplist);
			sw->WriteLine(CCDLABPATH + "tozip.fits");
			sw->Close();

			::Diagnostics::Process^ p = gcnew ::Diagnostics::Process();
			p->StartInfo->FileName = "c:\\Program Files\\7-Zip\\7z.exe";
			p->StartInfo->Arguments = "\"a\" " + "\"-tzip\" " + "\"" + fullfilenames[i] + "\" " + "\"@" + ziplist;
			p->Start();
			p->WaitForExit();
			if (p->ExitCode != 0)
			{
				File::Delete(fullfilenames[i]);
				return;
			}
		}
	}
}

void Form1::WriteImageSetBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat("Writing file: ",e->ProgressPercentage," of ",WAITBAR->ProgressBar->Maximum);
	WAITBAR->Refresh();
}

void Form1::WriteImageSetBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	Form1::Enabled = true;
	WAITBAR->Close();
	FileTxtsUpD();
}

void Form1::TBSaveOver_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (::MessageBox::Show("Are you sure you want to overwrite the current file?","Warning...",::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
		return;

	IMAGESET[FILELISTINDEX]->WriteImage(FILESAVEPREC, true);
}

void Form1::TBSaveBatchOver_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (::MessageBox::Show("Are you sure you want to overwrite all of the files?","Warning...",::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
		return;

	IMAGESET->Write(FILESAVEPREC, true, true, "");
}

void Form1::RotateAngleUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::NShiftHorzUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::NShiftVertUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::ShiftHorzBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (double(NShiftHorzUpD->Value) == 0.0)
		return;

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Horizontal Shift...";
	ImageOpsWrkr->RunWorkerAsync(23);
	WAITBAR->ShowDialog();
}

void Form1::ShiftVertBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (double(NShiftVertUpD->Value) == 0.0)
		return;

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Vertical Shift...";
	ImageOpsWrkr->RunWorkerAsync(24);
	WAITBAR->ShowDialog();
}

void Form1::EMCopyHeader_Click(System::Object^  sender, System::EventArgs^  e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Fits File (*.fts; *.fit; *.fits)|*.fts; *.fit; *.fits";
	ofd->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFilesPath");
	ofd->Multiselect = false;
	ofd->Title = "Please select the source FITS file FROM which to copy the header.";

	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	FITSImage^ source = gcnew FITSImage(ofd->FileName, nullptr, true, false, false, false);

	ofd->Multiselect = true;
	ofd->Title = "Please now select the FITS file(s) TO which to copy the header.";

	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	FITSImage^ dest;
	for (int i = 0; i < ofd->FileNames->Length; i++)
	{
		dest = gcnew FITSImage(ofd->FileNames[i], nullptr, true, true, false, true);
		dest->Header->CopyHeaderFrom(source->Header);            // CopyHeader(source);
		dest->WriteImage(::TypeCode::Double, true);
	}

	::MessageBox::Show("Completed copying the source header over to the destination file(s).");
}

void Form1::ManRegTrkHWUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	EqualHWChck->Checked = true;
	HalfWidthXUpD->Value = ManRegTrkHWUpD->Value;
}

void Form1::FileListDrop_DropDown(System::Object^  sender, System::EventArgs^  e)
{
	double txtscale = 130/18;//pixels per character

	if (IMAGESET[0]->FileName->Length > 18)
		FileListDrop->Width = int(IMAGESET[0]->FileName->Length * (int)txtscale);
}

void Form1::FileListDrop_DropDownClosed(System::Object^  sender, System::EventArgs^  e)
{
	FileListDrop->Width = 130;
}

void Form1::SubImgROITab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (SubImgROITab->SelectedIndex == 1)//COGTab
		COG_CURSOR = true;
	else
		COG_CURSOR = false;
	
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::RadialPlotInterpolateROIChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SubImageCntxt->Show();
	SubImgRadialPlotMenuBtn->ShowDropDown();
}

void Form1::RadialPlotMedianBackgroundChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SubImageCntxt->Show();
	SubImgRadialPlotMenuBtn->ShowDropDown();
	SetReg("CCDLAB", "RadialMedianBG",RadialPlotMedianBackgroundChck->Checked);
}

void Form1::SubImgRadialPlotMenuBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	SubImageCntxt->Hide();
	SubImgRadialPlotMenuBtn->HideDropDown();

	::MouseEventArgs^ me = gcnew ::MouseEventArgs(::MouseButtons::Left, 2, 1, 1, 0);
	SubImageWindow_MouseDoubleClick(sender, me);

	if (SUBIMAGE_HWX != SUBIMAGE_HWY)
	{
		::MessageBox::Show("Error:  Region of Interest SubWindow must be square.  Double-click the main window to make the SubWindow square...","Error...");
		return;
	}
	if (SUBIMAGE_HWX < 2)
	{
		::MessageBox::Show("Error:  Region of interest SubWindow must be at least 5x5 pixels...","Error...");
		return;
	}
	
	double bg = 0;
	if (RadialPlotMedianBackgroundChck->Checked)
		bg = JPMath::Median(SUBIMAGE);
	else
		bg = JPMath::Min(SUBIMAGE, false);

	array<double,2>^ SUBIMAGE_radplot = JPMath::MatrixSubScalar(SUBIMAGE, bg, false);

	/*double center_val = SUBIMAGE_radplot[SUBIMAGE_HWX, SUBIMAGE_HWY];//center value is maximum
	double X0 = (double)XSUBRANGE[SUBIMAGE_HWX];
	double Y0 = (double)YSUBRANGE[SUBIMAGE_HWY];
	int interp_delta = 1;

	array<double>^ XSUBRANGE_radplot;
	array<double>^ YSUBRANGE_radplot;

	if (SUBIMAGE_HWX > 15)
	{
		SubImCntxtSaveRadialProfileMenuBtn->Enabled = true;

		XSUBRANGE_radplot = gcnew array<double>(XSUBRANGE->Length);
		YSUBRANGE_radplot = gcnew array<double>(YSUBRANGE->Length);
		for (int i = 0; i < XSUBRANGE->Length; i++)
			XSUBRANGE_radplot[i] = double(XSUBRANGE[i]);
		for (int i = 0; i < YSUBRANGE->Length; i++)
			YSUBRANGE_radplot[i] = double(YSUBRANGE[i]);
	}
	else
	{
		SubImCntxtSaveRadialProfileMenuBtn->Enabled = false;

		interp_delta = 5;
		XSUBRANGE_radplot = gcnew array<double>(XSUBRANGE->Length*interp_delta);
		YSUBRANGE_radplot = gcnew array<double>(YSUBRANGE->Length*interp_delta);
		array<double>^ xx = gcnew array<double>(XSUBRANGE->Length);
		array<double>^ yy = gcnew array<double>(YSUBRANGE->Length);
		for (int i = 0; i < XSUBRANGE->Length; i++)
			xx[i] = double(XSUBRANGE[i]);
		for (int i = 0; i < YSUBRANGE->Length; i++)
			yy[i] = double(YSUBRANGE[i]);

		SUBIMAGE_radplot = JPMath::Interpolate2d(xx, yy, SUBIMAGE_radplot, interp_delta, interp_delta, XSUBRANGE_radplot, YSUBRANGE_radplot, true);
	}

	ArrayList^ distances_LIST = gcnew ArrayList();
	ArrayList^ values_LIST = gcnew ArrayList();

	for (int x = 0; x < XSUBRANGE_radplot->Length; x++)
		for (int y = 0; y < YSUBRANGE_radplot->Length; y++)
		{
			double d_sq = (XSUBRANGE_radplot[x] - X0)*(XSUBRANGE_radplot[x] - X0) + (YSUBRANGE_radplot[y] - Y0)*(YSUBRANGE_radplot[y] - Y0);
			if (d_sq > double(SUBIMAGE_HWX*SUBIMAGE_HWX))
				continue;

			distances_LIST->Add(d_sq);
			values_LIST->Add(SUBIMAGE_radplot[x, y]);
		}

	array<double>^ distances_sq = gcnew array<double>(distances_LIST->Count);
	array<double>^ values = gcnew array<double>(distances_LIST->Count);
	for (int q = 0; q < distances_sq->Length; q++)
	{
		distances_sq[q] = double(distances_LIST[q]);
		values[q] = (double)values_LIST[q];
	}
	Array::Sort(distances_sq, values);
	values = JPMath::VectorDivScalar(values, center_val, false);//normalize to max count for radial profile plot

	ArrayList^ r_binnedlist = gcnew ArrayList();
	ArrayList^ v_binnedlist = gcnew ArrayList();
	ArrayList^ p_binnedlist = gcnew ArrayList();
	double d0 = distances_sq[0];
	for (int i = 0; i < distances_sq->Length; i++)
	{
		int dcounter = 0;
		double val = 0;
		while ((i + dcounter) < distances_sq->Length && d0 == distances_sq[i + dcounter])
		{
			val += values[i + dcounter];
			dcounter++;
		}
		r_binnedlist->Add(d0);
		v_binnedlist->Add(val / (double(dcounter)));
		p_binnedlist->Add(double(dcounter));
		if ((i + dcounter) < distances_sq->Length)
			d0 = distances_sq[i + dcounter];
		i += dcounter - 1;
	}

	array<double>^ r_binned = gcnew array<double>(r_binnedlist->Count);
	array<double>^ v_binned = gcnew array<double>(r_binnedlist->Count);
	array<double>^ p_binned = gcnew array<double>(r_binnedlist->Count);
	for (int q = 0; q < r_binned->Length; q++)
	{
		r_binned[q] = Math::Sqrt((double)r_binnedlist[q]);
		v_binned[q] = (double)v_binnedlist[q];
		p_binned[q] = (double)p_binnedlist[q];
	}*/

	array<double>^ r_binned;
	array<double>^ v_binned;
	JPMath::Radial_Profile_Normalized(SUBIMAGE_radplot, XSUBRANGE, YSUBRANGE, 1, r_binned, v_binned);

	RADIALPLOT_R = r_binned;
	RADIALPLOT_V = JPMath::VectorMultScalar(v_binned, SUBIMAGE_radplot[SUBIMAGE_HWX, SUBIMAGE_HWY], false);
	RADIALPLOT_P = gcnew array<double>(r_binned->Length); /*p_binned;*/
	RADIALPLOT_PHI = -720;

	if (RAD_PLOT->IsDisposed)
		RAD_PLOT = gcnew JPPlot();

	if (IMAGESET[FILELISTINDEX]->Header->GetKeyValue("CDELT1") != "" && IMAGESET[FILELISTINDEX]->Header->GetKeyValue("CDELT2") != "")
	{
		double cdelt1 = Convert::ToDouble(IMAGESET[FILELISTINDEX]->Header->GetKeyValue("CDELT1"));
		double cdelt2 = Convert::ToDouble(IMAGESET[FILELISTINDEX]->Header->GetKeyValue("CDELT2"));
		double cdelt = (cdelt1 + cdelt2) / 2;
		RAD_PLOT->PixelScaleTxtBox->Text = cdelt.ToString();
	}

	RAD_PLOT->JPPlotMainMenu->Visible = true;
	RAD_PLOT->Text = "Radial Profile Plot";
	RAD_PLOT->PlotLine(r_binned, v_binned, "Radius (pixels)", "Normalized Value at Radius", "Radial Plot", ::Charting::SeriesChartType::Point, "Radial");
	RAD_PLOT->plotchart1->SetAxesLimits(0, r_binned[r_binned->Length - 1], 0, 1);
	RAD_PLOT->FitMenuMoffat->PerformClick();
}

void Form1::WCSRADecManual_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!WCSMANUALRAD_CONTINUE && !WCSMANUALRAD)//then start selecting points and set things up
	{
		if (MessageBox::Show("Please begin selecting at least 3 point sources (LEFT-CLICK).  RIGHT-CLICK when done.","Manual WCS RA & Dec...",::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			return;

		IWLCK = false;//allow cursor box to move
		WCSMANUALRAD = true;
		WCSMANUALRAD_CONTINUE = true;
		EqualHWChck->Checked = true;
		FNDCOORDS = gcnew array<int,2>(1,2);//this is for plotting the local max point in the ROI
		FNDCOORDRECTS = gcnew array<Rectangle,1>(1);
		ShowFoundCoordsChck->Checked = true;//this is for plotting the local max point in the ROI
		MANREGCOORDS = gcnew array<int,2>(0,0);
		MANREGCOORDRECTS = gcnew array<Rectangle,1>(0);
		WCS_RA = gcnew array<double>(0);
		WCS_DEC = gcnew array<double>(0);
		return;
	}

	if (WCSMANUALRAD && MANREGCOORDRECTS->Length == 0)//right clicked out without any point selections, so end everything (well...not everything)
	{
		WCSMANUALRAD = false;
		WCSMANUALRAD_CONTINUE = false;
		ShowFoundCoordsChck->Checked = false;
		ImageWindow->Refresh();
		return;
	}

	if (WCSMANUALRAD && MANREGCOORDRECTS->Length > 0 && WCSMANUALRAD_CONTINUE && WCSNEWPOINT)//then enter RA & Dec for the last selection & store etc.  Also make corresponding centroid list here?
	{
		RADECBOX = gcnew RADecBox();

		::DialogResult dres = RADECBOX->ShowDialog();

		if (dres == ::DialogResult::Cancel)
		{
			WCSMANUALRAD = false;
			WCSMANUALRAD_CONTINUE = false;
			ShowFoundCoordsChck->Checked = false;
			ImageWindow->Refresh();
			return;
		}

		array<double>^ tempRA = gcnew array<double>(WCS_RA->Length+1);
		array<double>^ tempDEC = gcnew array<double>(WCS_DEC->Length+1);

		for (int i = 0; i < WCS_RA->Length; i++)
		{
			tempRA[i] = WCS_RA[i];
			tempDEC[i] = WCS_DEC[i];
		}

		tempRA[WCS_RA->Length] = RADECBOX->RIGHT_ASCENSION;
		tempDEC[WCS_DEC->Length] = RADECBOX->DECLINATION;

		WCS_RA = tempRA;
		WCS_DEC = tempDEC;
	}

	if (WCSMANUALRAD && !WCSMANUALRAD_CONTINUE)//finished.  then ask and solve WCS solution
	{
		::DialogResult diares = MessageBox::Show("Proceed with WCS solution?","Manual WCS RA & Dec...",::MessageBoxButtons::YesNoCancel);
		if (diares == ::DialogResult::Cancel)
		{
			WCSMANUALRAD = false;
			ShowFoundCoordsChck->Checked = false;
			ImageWindow->Refresh();
			return;
		}
		if(diares == ::DialogResult::No)
			return;

		WCSMANUALRAD = false;
		ShowFoundCoordsChck->Checked = false;
		ImageWindow->Refresh();

		PSES = gcnew array<JPFITS::SourceExtractor^>(1) {gcnew JPFITS::SourceExtractor() };
		PSESINDEX = 0;
		array<double>^ x = gcnew array<double>(WCS_RA->Length);//centroid (pixels)
		array<double>^ y = gcnew array<double>(WCS_RA->Length);//centroid (pixels)
		for (int i = 0; i < WCS_RA->Length; i++)
		{
			x[i] = (double)MANREGCOORDS[i, 0];
			y[i] = (double)MANREGCOORDS[i, 1];
		}
		PSES[PSESINDEX]->Extract_Sources(IMAGESET[FILELISTINDEX]->Image, x, y, 2, false, "");
		x = PSES[PSESINDEX]->Centroids_X;
		y = PSES[PSESINDEX]->Centroids_Y;

		IMAGESET[FILELISTINDEX]->WCS->Solve_WCS("TAN", x, y, true, WCS_RA, WCS_DEC, IMAGESET[FILELISTINDEX]->Header);
		SHOW_WCSCOORDS = true;
		WCSRADecShowChck->Checked = true;

		if (WCS_RA->Length >= 3)
		{
			float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
			float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
			MARKCOORDRECTS = gcnew array<Rectangle, 1>(WCS_RA->Length);
			MARKCOORDS = gcnew array<double, 2>(2, WCS_RA->Length);
			double xpix, ypix;
			for (int i = 0; i < WCS_RA->Length; i++)
			{
				IMAGESET[FILELISTINDEX]->WCS->Get_Pixel(WCS_RA[i], WCS_DEC[i], "TAN", xpix, ypix, true);
				MARKCOORDRECTS[i] = Rectangle(int((float(xpix) + 0.5)*xsc - 3), int((float(ypix) + 0.5)*ysc - 3), 7, 7);
				MARKCOORDS[0, i] = xpix;
				MARKCOORDS[1, i] = ypix;
			}

			ImageWindow->Refresh();
			SubImageWindow->Refresh();

			String^ message = "If the WCS solution used more than 3 points then the solution is least-squares, and an error in the selection of points will show as a displacement of the selected points from the point sources.  Clear Marked Coordinate to clear points.";
			MessageBox::Show(message);
		}

		FileTxtsUpD();
	}
}

void Form1::WCSCopyToLoadedImgs_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!IMAGESET[FILELISTINDEX]->WCS->Exists())
		if (JPFITS::WorldCoordinateSolution::Exists(IMAGESET[FILELISTINDEX]->Header, gcnew array<String^>(1) { "RA---TAN" }))
			IMAGESET[FILELISTINDEX]->WCS = gcnew JPFITS::WorldCoordinateSolution(IMAGESET[FILELISTINDEX]->Header);
		else
		{
			MessageBox::Show("No WCS found in current image header...", "Error");
			return;
		}

	for (int i = 0; i < IMAGESET->Count; i++)
	{
		if (i == FILELISTINDEX)
			continue;
		IMAGESET[FILELISTINDEX]->WCS->CopyTo(IMAGESET[i]->Header);
	}
	MessageBox::Show("WCS copied to " + (IMAGESET->Count - 1) + " other headers...", "Success");
}

void Form1::WCSClearAllChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	WCSMenu->ShowDropDown();
	WCSClearMenuBtn->ShowDropDown();
}

void Form1::WCSClearMenuBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (WCSClearAllChck->Checked)
	{
		for (int i = 0; i < IMAGESET->Count; i++)
		{
			IMAGESET[i]->WCS->Clear(IMAGESET[i]->Header);
			IMAGESET[i]->WCS->Clear();
		}
	}
	else
	{
		IMAGESET[FILELISTINDEX]->WCS->Clear(IMAGESET[FILELISTINDEX]->Header);
		IMAGESET[FILELISTINDEX]->WCS->Clear();
	}

	FileTxtsUpD();
}

void Form1::WCSRADecShowChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (WCSRADecShowChck->Checked)
	{
		SHOW_WCSCOORDS = true;
		label40->Text = "a:";
		label41->Text = "d:";
	}
	else
	{
		SHOW_WCSCOORDS = false;
		label40->Text = "X:";
		label41->Text = "Y:";
	}
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

array<double>^ Form1::BJDC(array<double>^ JD, double RightAscension_deg, double Declination_deg, bool returnCorrectionOnly)
{
	array<double>^ result = gcnew array<double>(JD->Length);

	double cs = 173.14463348;// speed of light (au/d)
	double n, g, L, lam, eps, R, X, Y, Z, BJDC;

	for (int i = 0; i < JD->Length; i++)
	{
		// exact decimal day number from J2000.0 UT 12hr:
		n = JD[i] - 2451545.0;
		// mean anomaly, in radians, at day number n:
		g = Math::IEEERemainder((357.528 + .9856003*n)*Math::PI/180,2*Math::PI);
		// mean longitude, in radians, at n:
		L = Math::IEEERemainder((280.46 + .9856474*n)*Math::PI/180,2*Math::PI);
		// ecliptic longitude, in radians, at n:
		lam = L + 1.915*Math::PI/180*Math::Sin(g) + .020*Math::PI/180*Math::Sin(2*g);
		// ecliptic obliquity, in radians, at n:
		eps = 23.439*Math::PI/180 - .0000004*Math::PI/180*n;
		// distance of earth from sun in au’s at JD:
		R = 1.00014 - 0.01671*Math::Cos(g) - 0.00014*Math::Cos(2*g);
		// rectangular coordinates of earth wrt solar system barycenter referred to
		// equinox and %equator of J2000.0, in au's:
		X = -R*Math::Cos(lam);
		Y = -R*Math::Cos(eps)*Math::Sin(lam);
		Z = -R*Math::Sin(eps)*Math::Sin(lam);

		BJDC = 1/cs*(X*Math::Cos(RightAscension_deg)*Math::Cos(Declination_deg) + Y*Math::Sin(RightAscension_deg)*Math::Cos(Declination_deg) + Z*Math::Sin(Declination_deg));

		result[i] = BJDC;

		if (!returnCorrectionOnly)
			result[i] += JD[i];
	}

	return result;
}

void Form1::ImageFingerRmvToHere_Click(System::Object^  sender, System::EventArgs^  e)
{
	for (int i = 0; i < FILELISTINDEX; i++)
	{
		IMAGESET->RemoveAt(0);
		FileListDrop->Items->RemoveAt(0);
	}

	FILELISTINDEX = 0;

	ViewSelectionStatic->Text = String::Concat("Image: ",(FILELISTINDEX+1).ToString()," of ",IMAGESET->Count.ToString());

	if (FileListDrop->Items->Count == 1)
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		BatchCorrectionChck->Enabled = false;
		BatchCorrectionChck->Checked = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
		HCExtract->Enabled = false;
		HCExtractKeyValue->Enabled = false;
	}

	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;
}

void Form1::ImageFingerRecToHere_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (::MessageBox::Show("Are you sure you want to delete the file(s) to Recylce Bin?", "WARNING!", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
		return;

	Form1::Enabled = false;
	int intprog = 0;
	ProgressBar->Maximum = 100;
	for (int i = 0; i < FILELISTINDEX; i++)
	{
		if (100 * i / FILELISTINDEX > intprog)
		{
			intprog++;
			ProgressBar->Value = intprog;
			ProgressBar->Refresh();
		}

		Microsoft::VisualBasic::FileIO::FileSystem::DeleteFile(IMAGESET[0]->FullFileName, ::Microsoft::VisualBasic::FileIO::UIOption::OnlyErrorDialogs, ::Microsoft::VisualBasic::FileIO::RecycleOption::SendToRecycleBin);
		IMAGESET->RemoveAt(0);
		FileListDrop->Items->RemoveAt(0);
	}

	Form1::Enabled = true;
	ProgressBar->Value = 0;
	ProgressBar->Refresh();

	FILELISTINDEX = 0;

	ViewSelectionStatic->Text = String::Concat("Image: ", (FILELISTINDEX + 1).ToString(), " of ", IMAGESET->Count.ToString());

	if (FileListDrop->Items->Count == 1)
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		BatchCorrectionChck->Enabled = false;
		BatchCorrectionChck->Checked = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
		HCExtract->Enabled = false;
		HCExtractKeyValue->Enabled = false;
	}

	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;
}

void Form1::ImageFingerRmvFromHere_Click(System::Object^  sender, System::EventArgs^  e)
{
	int N = FileListDrop->Items->Count;
	for (int i = FILELISTINDEX+1; i < N; i++)
	{
		IMAGESET->RemoveAt(FILELISTINDEX+1);
		FileListDrop->Items->RemoveAt(FILELISTINDEX+1);
	}

	FILELISTINDEX = FileListDrop->Items->Count - 1;

	int C = IMAGESET->Count;
	ViewSelectionStatic->Text = String::Concat("Image: ",(FILELISTINDEX+1).ToString()," of ",IMAGESET->Count.ToString());

	if (FileListDrop->Items->Count == 1)
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		BatchCorrectionChck->Enabled = false;
		BatchCorrectionChck->Checked = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
		HCExtract->Enabled = false;
		HCExtractKeyValue->Enabled = false;
	}

	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;
}

void Form1::ImageFingerRecFromHere_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (::MessageBox::Show("Are you sure you want to delete the file(s) to Recylce Bin?", "WARNING!", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
		return;

	Form1::Enabled = false;
	int intprog = 0;
	ProgressBar->Maximum = 100;
	int N = FileListDrop->Items->Count;
	for (int i = FILELISTINDEX + 1; i < N; i++)
	{
		if (100 * (i - FILELISTINDEX - 1) / (N - FILELISTINDEX - 1) > intprog)
		{
			intprog++;
			ProgressBar->Value = intprog;
			ProgressBar->Refresh();
		}

		Microsoft::VisualBasic::FileIO::FileSystem::DeleteFile(IMAGESET[FILELISTINDEX + 1]->FullFileName, ::Microsoft::VisualBasic::FileIO::UIOption::OnlyErrorDialogs, ::Microsoft::VisualBasic::FileIO::RecycleOption::SendToRecycleBin);
		IMAGESET->RemoveAt(FILELISTINDEX + 1);
		FileListDrop->Items->RemoveAt(FILELISTINDEX + 1);
	}

	Form1::Enabled = true;
	ProgressBar->Value = 0;
	ProgressBar->Refresh();

	FILELISTINDEX = FileListDrop->Items->Count - 1;

	int C = IMAGESET->Count;
	ViewSelectionStatic->Text = String::Concat("Image: ", (FILELISTINDEX + 1).ToString(), " of ", IMAGESET->Count.ToString());

	if (FileListDrop->Items->Count == 1)
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		BatchCorrectionChck->Enabled = false;
		BatchCorrectionChck->Checked = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
		HCExtract->Enabled = false;
		HCExtractKeyValue->Enabled = false;
	}

	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;
}

void Form1::ImageFingerSortFileName_Click(System::Object^  sender, System::EventArgs^  e)
{
	IMAGESET->Sort("filename");

	array<String^>^ files = gcnew array<String^>(IMAGESET->Count);
	for (int i = 0; i < IMAGESET->Count; i++)
		files[i] = IMAGESET[i]->FileName;

	FileListDrop->Items->Clear();
	FileListDrop->Items->AddRange(files);
	FileListDrop->SelectedIndex = 0;
}

void Form1::ImageFingerSortKeyValue_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ key = ImageFingerSortKeyValueTxt->Text;
	if (key->Length == 0)
	{
		::MessageBox::Show("No header key defined...", "Error");
		ImageFingerPointContext->Show();
		ImageFingerSortBy->ShowDropDown();
		return;
	}
	SetReg("CCDLAB", "ImageFingerSortKeyTxt", key);

	if (IMAGESET->Sort(key) == -1)
		return;

	array<String^>^ files = gcnew array<String^>(IMAGESET->Count);
	for (int i = 0; i < IMAGESET->Count; i++)
		files[i] = IMAGESET[i]->FileName;

	FileListDrop->Items->Clear();
	FileListDrop->Items->AddRange(files);
	FileListDrop->SelectedIndex = 0;
}

void Form1::ScanContextGoToBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	int N = ::Convert::ToInt32(ScanContextGoToTxt->Text) - 1;
	if (N >= 0 && N < FileListDrop->Items->Count)
		FileListDrop->SelectedIndex = N;
}

void Form1::ScanContextGoToTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToInt32(ScanContextGoToTxt->Text);
	}
	catch (...)
	{
		ScanContextGoToTxt->Text = "1";
	}
}

void Form1::ScanContextGoToTxt_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	e->SuppressKeyPress = true;

	if (e->KeyCode == ::Keys::Enter)
		ScanContextGoToBtn->PerformClick();
}

void Form1::SIZECntxtBatchChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SIZECntxtMenu->Show();
	SIZECntxtEditImgDim->ShowDropDown();
}

void Form1::SIZECntxtEditImgDim_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	/*SIZECntxtEditTxtX
	SIZECntxtEditTxtY
	SIZECntxtBatchChck*/

	SIZECntxtMenu->Hide();

	if (FIRSTLOAD)
		return;

	WAITBAR = gcnew JPWaitBar::WaitBar();
	if (!SIZECntxtBatchChck->Checked)
		WAITBAR->ProgressBar->Maximum = 1;
	if (SIZECntxtBatchChck->Checked)
		WAITBAR->ProgressBar->Maximum = IMAGESET->Count;
	Form1::Enabled = false;
	SIZECntxtBGWrkr->RunWorkerAsync();
	WAITBAR->Show();	
}

void Form1::SIZECntxtBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	String^ Xedittxt = SIZECntxtEditTxtX->Text;
	String^ Yedittxt = SIZECntxtEditTxtY->Text;
	int Xstart, Xend, Ystart, Yend;
	array<int>^ inds = gcnew array<int>(IMAGESET->Count);
	if (SIZECntxtBatchChck->Checked)
		for (int i = 0; i < IMAGESET->Count; i++)
			inds[i] = i;
	else
		inds = gcnew array<int>(1){FILELISTINDEX};

	array<double,2>^ newimg;

	for (int i = inds[0]; i < inds->Length; i++)
	{
		if (Xedittxt == "")
		{
			Xstart = 0;
			Xend = IMAGESET[inds[i]]->Width-1;
		}
		else
		{
			int col = Xedittxt->IndexOf(":");
			if (col == -1)
			{
				::MessageBox::Show("Problem with the X range: " + Xedittxt);
				WAITBAR->CancelBtn->PerformClick();
				return;
			}

			Xstart = ::Convert::ToInt32(Xedittxt->Substring(0,col)) - 1;
			Xend = ::Convert::ToInt32(Xedittxt->Substring(col+1)) - 1;

			if (Xstart < 0 || Xend > IMAGESET[i]->Width-1)
			{
				::MessageBox::Show("Problem with the X range: " + Xedittxt + ", for file: " + (i+1).ToString());
				WAITBAR->CancelBtn->PerformClick();
				return;
			}
		}
		if (Yedittxt == "")
		{
			Ystart = 0;
			Yend = IMAGESET[inds[i]]->Height-1;
		}
		else
		{
			int col = Yedittxt->IndexOf(":");
			if (col == -1)
			{
				::MessageBox::Show("Problem with the Y range: " + Yedittxt);
				WAITBAR->CancelBtn->PerformClick();
				return;
			}

			Ystart = ::Convert::ToInt32(Yedittxt->Substring(0,col)) - 1;
			Yend = ::Convert::ToInt32(Yedittxt->Substring(col+1)) - 1;

			if (Ystart < 0 || Yend > IMAGESET[i]->Height-1)
			{
				::MessageBox::Show("Problem with the Y range: " + Yedittxt + ", for file: " + (i+1).ToString());
				WAITBAR->CancelBtn->PerformClick();
				return;
			}
		}

		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;
		SIZECntxtBGWrkr->ReportProgress(i+1);

		newimg = gcnew array<double,2>(Xend-Xstart+1,Yend-Ystart+1);
		#pragma omp parallel for
		for (int x = 0; x < newimg->GetLength(0); x++)
			for (int y = 0; y < newimg->GetLength(1); y++)
				newimg[x,y] = IMAGESET[i]->Image[Xstart + x, Ystart + y];

		IMAGESET[i]->SetImage(newimg, true, true);
	}
}

void Form1::SIZECntxtBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = "Processing file " + e->ProgressPercentage.ToString() + " of " + WAITBAR->ProgressBar->Maximum.ToString();
	WAITBAR->Refresh();
}

void Form1::SIZECntxtBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	Form1::Enabled = true;
	WAITBAR->Close();
	FileListDrop_SelectedIndexChanged(sender,e);
}

void Form1::PadImageBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	RangeDlg^ rdlg = gcnew RangeDlg();
	rdlg->HelpButton = false;
	rdlg->Text = "Set the Padding Ranges Around the Image Edges...";
	rdlg->XStartUpD->Minimum = 0;
	rdlg->XEndUpD->Minimum = 0;
	rdlg->YStartUpD->Minimum = 0;
	rdlg->YEndUpD->Minimum = 0;
	try
	{
		rdlg->XStartUpD->Value = (int)GetReg("CCDLAB", "PADXSTART");
		rdlg->XEndUpD->Value = (int)GetReg("CCDLAB", "PADXEND");
		rdlg->YStartUpD->Value = (int)GetReg("CCDLAB", "PADYSTART");
		rdlg->YEndUpD->Value = (int)GetReg("CCDLAB", "PADYEND");
	}
	catch (...) {};

	if (rdlg->ShowDialog() == ::DialogResult::Cancel)
		return;

	int xstart = (int)rdlg->XStartUpD->Value;
	int xend = (int)rdlg->XEndUpD->Value;
	int ystart = (int)rdlg->YStartUpD->Value;
	int yend = (int)rdlg->YEndUpD->Value;

	if (xstart == 0 && ystart == 0 && xend == 0 && yend == 0)
		return;

	SetReg("CCDLAB", "PADXSTART", xstart);
	SetReg("CCDLAB", "PADXEND", xend);
	SetReg("CCDLAB", "PADYEND", yend);

	PADDING = gcnew array<int>(4) {xstart , xend, ystart, yend};

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Image Padding...";
	ImageOpsWrkr->RunWorkerAsync(8);
	WAITBAR->ShowDialog();
}

void Form1::CutSubImBtn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{

}

void Form1::CutSubImBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button != ::MouseButtons::Right)
		return;

	RangeDlg^ rdlg = gcnew RangeDlg();
	rdlg->HelpButton = false;
	rdlg->Text = "Set Image Range...";
	rdlg->XStartUpD->Minimum = 1;
	rdlg->XEndUpD->Minimum = 1;
	rdlg->YStartUpD->Minimum = 1;
	rdlg->YEndUpD->Minimum = 1;
	try
	{
		rdlg->XStartUpD->Value = (int)GetReg("CCDLAB", "CROPXSTART");
		rdlg->XEndUpD->Value = (int)GetReg("CCDLAB", "CROPXEND");
		rdlg->YStartUpD->Value = (int)GetReg("CCDLAB", "CROPYSTART");
		rdlg->YEndUpD->Value = (int)GetReg("CCDLAB", "CROPYEND");
	}
	catch (...) {};

	if (rdlg->ShowDialog() == ::DialogResult::Cancel)
		return;

	int xstart = (int)rdlg->XStartUpD->Value;
	int xend = (int)rdlg->XEndUpD->Value;
	int ystart = (int)rdlg->YStartUpD->Value;
	int yend = (int)rdlg->YEndUpD->Value;

	if (xstart == 0 && ystart == 0 && xend == 0 && yend == 0)
		return;

	SetReg("CCDLAB", "CROPXSTART", xstart);
	SetReg("CCDLAB", "CROPXEND", xend);
	SetReg("CCDLAB", "CROPYSTART", ystart);
	SetReg("CCDLAB", "CROPYEND", yend);

	CROPPING = gcnew array<int>(4) { xstart, xend, ystart, yend };

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileListDrop->Items->Count;
	WAITBAR->Text = "Image Cropping...";
	ImageOpsWrkr->RunWorkerAsync(9);
	WAITBAR->ShowDialog();
}

void Form1::SIZECntxtMenu_Opened(System::Object^  sender, System::EventArgs^  e)
{
	SIZECntxtEditTxtX->Text = "1:" + IMAGESET[FILELISTINDEX]->Width.ToString();
	SIZECntxtEditTxtY->Text = "1:" + IMAGESET[FILELISTINDEX]->Height.ToString();
}

void Form1::FileDirectoryTxtContextMenuDelDirRmImg_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (FIRSTLOAD)
		return;

	if (MessageBox::Show("Are you sure you want to delete the directory and remove the image?", "Confirmation...", MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
		return;

	Microsoft::VisualBasic::FileIO::FileSystem::DeleteDirectory(IMAGESET[FILELISTINDEX]->FilePath, ::Microsoft::VisualBasic::FileIO::UIOption::OnlyErrorDialogs, Microsoft::VisualBasic::FileIO::RecycleOption::SendToRecycleBin, Microsoft::VisualBasic::FileIO::UICancelOption::DoNothing);
	
	IMAGESET->RemoveAt(FILELISTINDEX);
	FileListDrop->Items->RemoveAt(FILELISTINDEX);

	if (FILELISTINDEX == IMAGESET->Count)
		FILELISTINDEX--;
	FileListDrop->SelectedIndex = FILELISTINDEX;

	ViewSelectionStatic->Text = String::Concat("Image: ", (FILELISTINDEX + 1).ToString(), " of ", IMAGESET->Count.ToString());

	if (FileListDrop->Items->Count == 1)
	{
		BatchViewPanel->Enabled = false;
		TBSaveBatch->Enabled = false;
		TBSaveBatchOver->Enabled = false;
		TBZipAllBtn->Enabled = false;
		ImageBatchRedxnPnl->Enabled = false;
		BatchCorrectionChck->Enabled = false;
		BatchCorrectionChck->Checked = false;
		HCInsertBatch->Enabled = false;
		HCRemoveBatch->Enabled = false;
		HCExtract->Enabled = false;
		HCExtractKeyValue->Enabled = false;
	}

	BatchMeanChck->Checked = false;
	BatchSumChck->Checked = false;
	BatchQuadratureChck->Checked = false;
	BatchMedianChck->Checked = false;
	BatchStdvChck->Checked = false;
	BatchMaximumChck->Checked = false;
	BatchMinimumChck->Checked = false;
}

void Form1::ImageSizeTxt_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	ImageSizeTxt->Font = gcnew ::Drawing::Font(ImageSizeTxt->Font, ::FontStyle::Underline | ::FontStyle::Bold);
}

void Form1::ImageSizeTxt_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	ImageSizeTxt->Font = gcnew ::Drawing::Font(ImageSizeTxt->Font, ::FontStyle::Bold);
}

void Form1::ResetPlotPositions_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "RADplotPOSX", 10);
	SetReg("CCDLAB", "RADplotPOSY", 10);
	SetReg("CCDLAB", "RADplotWIDTH", 500);
	SetReg("CCDLAB", "RADplotHEIGHT", 500);

	SetReg("CCDLAB", "XDriftplotPOSX", 10);
	SetReg("CCDLAB", "XDriftplotPOSY", 10);
	SetReg("CCDLAB", "XDriftplotHEIGHT", 500);
	SetReg("CCDLAB", "XDriftplotWIDTH", 500);

	SetReg("CCDLAB", "YDriftplotPOSX", 10);
	SetReg("CCDLAB", "YDriftplotPOSY", 10);
	SetReg("CCDLAB", "YDriftplotHEIGHT", 500);
	SetReg("CCDLAB", "YDriftplotWIDTH", 500);
}

void Form1::ImageMaxStatic_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	int x, y;
	JPMath::Max(IMAGESET[FILELISTINDEX]->Image, x, y, true);
	SubImageSlideX->Value = x;
	SubImageSlideY->Value = y;

	SubImageStatsUpD();
	SubImageUpD();
	ImageWindow->Refresh();
}

void Form1::FMOpenImageExtensions_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Multiselect = false;
	ofd->Filter = "FITS|*.fits;*.fit;*.fts|All|*.*";
	ofd->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFilesPath");
	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	array<String^>^ extlist = JPFITS::FITSImage::GetAllExtensionNames(ofd->FileName);

	if (extlist->Length == 0)
	{
		MessageBox::Show("No image extensions found in the file...", "Error");
		return;
	}

	FMImageExtensionsLoader^ iel = gcnew FMImageExtensionsLoader();
	
	int n = 1;
	for (int i = 0; i < extlist->Length; i++)
		if (extlist[i] == "")
		{
			iel->ExtensionChckdListBox->Items->Add("Unnamed extension: " + n, true);
			n++;
		}
		else
			iel->ExtensionChckdListBox->Items->Add(extlist[i], true);
	
	if (iel->ShowDialog() == ::DialogResult::Cancel)
		return;

	IMAGESET = gcnew JPFITS::FITSImageSet();
	for (int i = 0; i < iel->ExtensionChckdListBox->Items->Count; i++)
		if (iel->ExtensionChckdListBox->GetItemChecked(i))
			IMAGESET->Add(gcnew JPFITS::FITSImage(ofd->FileName, i + 1, nullptr, true, true, true, true));

	AUTOLOADIMAGES = true;
	AUTOLOADIMAGESFILES = gcnew array<String^>(1) { "SingleOut" };
	FMLoad_Click(sender, e);
}

