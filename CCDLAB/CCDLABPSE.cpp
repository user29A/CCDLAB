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

void Form1::PSEFitChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PSEFitChck->Checked)
	{
		PSEFitTypeChck->Enabled = true;
		//PSEFitTypeChck->SelectedIndex = 0;
		PSEFitTypeChck->DroppedDown = true;
		PSEViewFitChck->Enabled = true;
		PSEFitResultListBox->Visible = true;
	}
	else
	{
		PSEFitTypeChck->Enabled = false;
		PSEViewFitChck->Enabled = false;
		PSEFitResultListBox->Visible = false;
	}
}

void Form1::PSEFitTypeChck_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	/*if (MARKCOORDS == nullptr)
		return;

	if (!PSEFitChck->Checked || MARKCOORDS->Length == 0)
		return;*/

	if (PSES == nullptr)
		return;
	if (PSES[PSESINDEX]->N_Sources <= 0)
		return;

	array<double>^ PLB;
	array<double>^ PUB;
	array<double>^ P0;
	if (SetParametersChck->Checked)
	{
		P0 = gcnew array<double>(FPW->NPARAMS);
		for (int i = 0; i < FPW->NPARAMS; i++)
			P0[i] = ::Convert::ToDouble(FPW->PITXTARRAY[i]->Text);

		if (FPW->ConstrainBtn->Checked)
		{
			PLB = gcnew array<double>(FPW->NPARAMS);
			PUB = gcnew array<double>(FPW->NPARAMS);
			for (int i = 0; i < FPW->NPARAMS; i++)
			{
				PLB[i] = ::Convert::ToDouble(FPW->PLBTXTARRAY[i]->Text);
				PUB[i] = ::Convert::ToDouble(FPW->PUBTXTARRAY[i]->Text);
			}
		}
	}

	if (PSEFitTypeChck->SelectedIndex == 0)//circular gaussian
		PSES[PSESINDEX]->Extract_Source_LSFits_Gaussian_Circular(P0, PLB, PUB);
	if (PSEFitTypeChck->SelectedIndex == 1)//circular gaussian
		PSES[PSESINDEX]->Extract_Source_LSFits_Gaussian_Elliptical(P0, PLB, PUB);
	if (PSEFitTypeChck->SelectedIndex == 2)//circular moffat
		PSES[PSESINDEX]->Extract_Source_LSFits_Moffat_Circular(P0, PLB, PUB);
	if (PSEFitTypeChck->SelectedIndex == 3)//elliptical moffat
		PSES[PSESINDEX]->Extract_Source_LSFits_Moffat_Elliptical(P0, PLB, PUB);

	if (PSES[PSESINDEX]->Fitted == false)//cancelled
	{
		ImageWindow->Refresh();
		Form1::Enabled = true;
		return;
	}

	array<double, 2>^ P = PSES[PSESINDEX]->Fitted_Parameter_List;
	array<double>^ Amp = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
	array<double>^ X = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
	array<double>^ Y = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
	array<double>^ BG = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
	for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
	{
		Amp[i] = P[0, i];
		X[i] = P[1, i];
		Y[i] = P[2, i];
		BG[i] = P[P->GetLength(0) - 1, i];
	}
	PSEFitResultListBox->Items->Clear();
	PSEFitResultListBox->Items->Add("N:  " + PSES[PSESINDEX]->N_Sources);
	PSEFitResultListBox->Items->Add("Amplitude:  " + Math::Round(JPMath::Mean(Amp, true), 4) + " +- " + Math::Round(JPMath::Stdv(Amp, false), 4));
	PSEFitResultListBox->Items->Add("X:          " + Math::Round(JPMath::Mean(X, true), 4) + " +- " + Math::Round(JPMath::Stdv(X, false), 4));
	PSEFitResultListBox->Items->Add("Y:          " + Math::Round(JPMath::Mean(Y, true), 4) + " +- " + Math::Round(JPMath::Stdv(Y, false), 4));

	if (PSEFitTypeChck->SelectedIndex == 0)//symmetric gaussian
	{
		array<double>^ Sig = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		
		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
			Sig[i] = P[3, i];
		
		PSEFitResultListBox->Items->Add(String::Concat("FWHM:       ", Math::Round(2 * Math::Sqrt(2 * Math::Log(2))*JPMath::Mean(Sig, true), 4), " +- ", Math::Round(2 * Math::Sqrt(2 * Math::Log(2))*JPMath::Stdv(Sig, false), 4)));
	}

	if (PSEFitTypeChck->SelectedIndex == 1)//elliptical gaussian
	{
		array<double>^ Phi = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Xsig = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Ysig = gcnew array<double>(PSES[PSESINDEX]->N_Sources);

		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		{
			Phi[i] = P[3, i];
			Xsig[i] = P[4, i];
			Ysig[i] = P[5, i];
		}

		PSEFitResultListBox->Items->Add(String::Concat("FWHM_X:     ", Math::Round(2 * Math::Sqrt(2 * Math::Log(2))*JPMath::Mean(Xsig, true), 4), " +- ", Math::Round(2 * Math::Sqrt(2 * Math::Log(2))*JPMath::Stdv(Xsig, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("FWHM_Y:     ", Math::Round(2 * Math::Sqrt(2 * Math::Log(2))*JPMath::Mean(Ysig, true), 4), " +- ", Math::Round(2 * Math::Sqrt(2 * Math::Log(2))*JPMath::Stdv(Ysig, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("Phi:      ", Math::Round(JPMath::Mean(Phi, true), 4), " +- ", Math::Round(JPMath::Stdv(Phi, false), 4)));
	}

	if (PSEFitTypeChck->SelectedIndex == 2)//circular moffat
	{
		array<double>^ Theta = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Beta = gcnew array<double>(PSES[PSESINDEX]->N_Sources);

		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		{
			Theta[i] = P[3, i];
			Beta[i] = P[4, i];
		}

		PSEFitResultListBox->Items->Add(String::Concat("Theta:      ", Math::Round(JPMath::Mean(Theta, true), 4), " +- ", Math::Round(JPMath::Stdv(Theta, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("Beta:       ", Math::Round(JPMath::Mean(Beta, true), 4), " +- ", Math::Round(JPMath::Stdv(Beta, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("FWHM:       ", Math::Round(2 * JPMath::Mean(Theta, true)*Math::Sqrt(Math::Pow(2, 1 / (JPMath::Mean(Beta, true))) - 1), 4), " +- ", Math::Round(2 * JPMath::Stdv(Theta, false)*Math::Sqrt(Math::Pow(2, 1 / (JPMath::Stdv(Beta, false))) - 1), 4)));
	}

	if (PSEFitTypeChck->SelectedIndex == 3)//elliptical moffat
	{
		array<double>^ Phi = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Xtheta = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Ytheta = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Beta = gcnew array<double>(PSES[PSESINDEX]->N_Sources);

		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		{
			Phi[i] = P[3, i];
			Xtheta[i] = P[4, i];
			Ytheta[i] = P[5, i];
			Beta[i] = P[6, i];
		}

		PSEFitResultListBox->Items->Add(String::Concat("Theta_X:    ", Math::Round(JPMath::Mean(Xtheta, true), 4), " +- ", Math::Round(JPMath::Stdv(Xtheta, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("Theta_Y:    ", Math::Round(JPMath::Mean(Ytheta, true), 4), " +- ", Math::Round(JPMath::Stdv(Ytheta, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("Beta:       ", Math::Round(JPMath::Mean(Beta, true), 4), " +- ", Math::Round(JPMath::Stdv(Beta, false), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("FWHM_X:     ", Math::Round(2 * JPMath::Mean(Xtheta, true)*Math::Sqrt(Math::Pow(2, 1 / (JPMath::Mean(Beta, true))) - 1), 4), " +- ", Math::Round(2 * JPMath::Stdv(Xtheta, false)*Math::Sqrt(Math::Pow(2, 1 / (JPMath::Stdv(Beta, false))) - 1), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("FWHM_Y:     ", Math::Round(2 * JPMath::Mean(Ytheta, true)*Math::Sqrt(Math::Pow(2, 1 / (JPMath::Mean(Beta, true))) - 1), 4), " +- ", Math::Round(2 * JPMath::Stdv(Ytheta, false)*Math::Sqrt(Math::Pow(2, 1 / (JPMath::Stdv(Beta, false))) - 1), 4)));
		PSEFitResultListBox->Items->Add(String::Concat("Phi:      ", Math::Round(JPMath::Mean(Phi, true), 4), " +- ", Math::Round(JPMath::Stdv(Phi, false), 4)));
	}

	PSEFitResultListBox->Items->Add("BG:         " + Math::Round(JPMath::Mean(BG, true), 4) + " +- " + Math::Round(JPMath::Stdv(BG, false), 4));
}

void Form1::PSEFitTypeChck_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
}

void Form1::PSEWidthUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PSEKernelRadUpD->Value == 0)
	{
		PSEKernelMinUpD->Enabled = false;
		PSEKernelMaxUpD->Enabled = false;
		PSEAutoBackgroundChck->Enabled = false;
		PSEAutoBackgroundChck->Checked = false;
		PSEFitChck->Enabled = false;
		PSEFitChck->Checked = false;
	}
	else
	{
		PSEKernelMinUpD->Enabled = true;
		PSEKernelMaxUpD->Enabled = true;
		PSEAutoBackgroundChck->Enabled = true;
		PSEFitChck->Enabled = true;
	}

	if (PSESeparationUpD->Value < PSEKernelRadUpD->Value)
		PSESeparationUpD->Value = PSEKernelRadUpD->Value;
	PSESeparationUpD->Minimum = PSEKernelRadUpD->Value;
}

void Form1::SaveROIContext_Click(System::Object^  sender, System::EventArgs^  e)
{
	SaveFileDialog^ fsd = gcnew SaveFileDialog();
	//fsd->InitialDirectory = 
	//fsd->Filter = 

	if (fsd->ShowDialog() == ::DialogResult::Cancel)
		return;

	JPFITS::FITSImage^ ff = gcnew FITSImage(fsd->FileName, ROI_PATH_COORDS, false, false);
	ff->WriteImage(TypeCode::Double, false);
}

void Form1::LoadROIContext_Click(System::Object^  sender, System::EventArgs^  e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	//ofd->InitialDirectory = 
	//ofd->Filter = 
	ofd->Multiselect = false;//possibly true for getting/doing multi-regions

	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	PSEDrawROI->Checked = true;
	DRAW_ROI_PATH = false;
	DRAW_ROI_PATH_START = false;

	ROI_PATH_COORDS = FITSImage::ReadImageArrayOnly(ofd->FileName, nullptr, false);
	MAKEROIPATHPOINTS();
	ROI_PATH_FILLREGION();
}

void Form1::ROI_PATH_FILLREGION()
{
	int xmin = int::MaxValue, xmax = int::MinValue, ymin = int::MaxValue, ymax = int::MinValue;
	array<JPMath::PointD^>^ pts = gcnew array<JPMath::PointD^>(ROI_PATH_COORDS->GetLength(1));
	for (int i = 0; i < pts->Length; i++)
	{
		pts[i] = gcnew JPMath::PointD(ROI_PATH_COORDS[0, i], ROI_PATH_COORDS[1, i], 0);

		if ((int)ROI_PATH_COORDS[0, i] < xmin)
			xmin = (int)ROI_PATH_COORDS[0, i];
		if ((int)ROI_PATH_COORDS[1, i] < ymin)
			ymin = (int)ROI_PATH_COORDS[1, i];
		if ((int)ROI_PATH_COORDS[0, i] > xmax)
			xmax = (int)ROI_PATH_COORDS[0, i];
		if ((int)ROI_PATH_COORDS[1, i] > ymax)
			ymax = (int)ROI_PATH_COORDS[1, i];
	}

	if (pts->Length > 100)
	{
		double skip = double(pts->Length) / 100;

		for (int i = 0; i < 100; i++)
			pts[i] = pts[int(double(i) * skip)];

		Array::Resize(pts, 100);
	}
	pts[pts->Length - 1] = pts[0];

	ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);

	JPMath::PointD::PolygonInteriorPointsRegion(ROI_REGION, pts, xmin, ymin, xmax, ymax);

	ImageUpD(IMAGESET[FILELISTINDEX]->Image);
	ImageWindow->Refresh();
}

void Form1::PSESeachROIOnlyChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PSESeachROIOnlyChck->Checked)
	{
		PSEEllipticalROI->Enabled = true;
		PSEDrawROI->Enabled = true;
	}
	else
	{
		PSEEllipticalROI->Checked = false;
		PSEDrawROI->Checked = false;
		PSEEllipticalROI->Enabled = false;
		PSEDrawROI->Enabled = false;
		ROI_PATH_COORDS = nullptr;
		ROI_PATH_POINTS = nullptr;
		ROI_REGION = nullptr;
		ImageWindow->Refresh();
	}
}

void Form1::PSEDrawROI_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PSEDrawROI->Checked)
	{
		PSEEllipticalROI->Checked = false;
		DRAW_ROI_PATH = true;
		DRAW_ROI_PATH_START = true;
		ROI_PATH_COORDS = nullptr;
		ROI_PATH_POINTS = nullptr;
		
		/*if (File::Exists(CCDLABPATH + "ROI_PATH.FITS"))
		{
			ROI_PATH_COORDS = FITSImage::ReadImageArrayOnly(CCDLABPATH + "ROI_PATH.FITS", nullptr);
			MAKEROIPATHPOINTS();
			ROI_PATH_FILLREGION();
		}*/

		ImageWindow->Refresh();
	}
	else
	{
		DRAW_ROI_PATH = false;
		DRAW_ROI_PATH_START = false;
		ROI_PATH_COORDS = nullptr;
		ROI_PATH_POINTS = nullptr;
		ImageWindow->Refresh();
	}
}

void Form1::PSEEllipticalROI_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PSEEllipticalROI->Checked)
	{
		PSEDrawROI->Checked = false;
		ROI_PATH_COORDS = nullptr;
		ROI_PATH_POINTS = nullptr;
		ImageWindow->Refresh();

		SUBIMAGE_HWX_OLD = SUBIMAGE_HWX;
		SUBIMAGE_HWY_OLD = SUBIMAGE_HWY;
		SUBIMAGEX0OLD = XSUBRANGE[SUBIMAGE_HWX];
		SUBIMAGEY0OLD = YSUBRANGE[SUBIMAGE_HWY];
		ShowCrosshair->Checked = false;

		/*if (ROIX0 != XSUBRANGE[SUBIMAGE_HWX])
		{
			try
			{
				ROIX0 = Convert::ToInt32(GetReg("CCDLAB", "ROIX0"));
				ROIY0 = Convert::ToInt32(GetReg("CCDLAB", "ROIY0"));
				ROIXRad = Convert::ToInt32(GetReg("CCDLAB", "ROIXRad"));
				ROIYRad = Convert::ToInt32(GetReg("CCDLAB", "ROIYRad"));

				SubImageSlideX->Value = ROIX0 + 1;
				SubImageSlideY->Value = ROIY0 + 1;
				SUBIMAGE_HWX = ROIXRad;//need this first
				HalfWidthXUpD->Value = ROIXRad;
				HalfWidthYUpD->Value = ROIYRad;
			}
			catch (...) {}
		}
		else
		{
			SubImageSlideX->Value = ROIX0 + 1;
			SubImageSlideY->Value = ROIY0 + 1;
			SUBIMAGE_HWX = ROIXRad;//need this first
			HalfWidthXUpD->Value = ROIXRad;
			HalfWidthYUpD->Value = ROIYRad;
		}

		SetReg("CCDLAB", "ROIX0", ROIX0);
		SetReg("CCDLAB", "ROIY0", ROIY0);
		SetReg("CCDLAB", "ROIXRad", ROIXRad);
		SetReg("CCDLAB", "ROIYRad", ROIYRad);*/

		ROIX0 = Convert::ToInt32(GetReg("CCDLAB", "ROIX0"));
		ROIY0 = Convert::ToInt32(GetReg("CCDLAB", "ROIY0"));
		ROIXRad = Convert::ToInt32(GetReg("CCDLAB", "ROIXRad"));
		ROIYRad = Convert::ToInt32(GetReg("CCDLAB", "ROIYRad"));
		SubImageSlideX->Value = ROIX0 + 1;
		SubImageSlideY->Value = ROIY0 + 1;
		SUBIMAGE_HWX = ROIXRad;//need this first
		SUBIMAGE_HWY = ROIYRad;//need this first
		HalfWidthXUpD->Value = ROIXRad;
		HalfWidthYUpD->Value = ROIYRad;
	}
	else
	{
		SUBIMAGE_HWX = this->SUBIMAGE_HWX_OLD;
		SUBIMAGE_HWY = this->SUBIMAGE_HWY_OLD;
		SubImageSlideX->Value = this->SUBIMAGEX0OLD + 1;
		SubImageSlideY->Value = this->SUBIMAGEY0OLD + 1;
		HalfWidthXUpD->Value = this->SUBIMAGE_HWX;
		HalfWidthYUpD->Value = this->SUBIMAGE_HWY;
	}
}

void Form1::PSEFindSrcBtn_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	/*PSEFindSrcBtn->Font = gcnew ::Font(PSEFindSrcBtn->Font, ::FontStyle::Bold);
	PSEFindSrcBtn->Refresh();*/
}

void Form1::PSEFindSrcBtn_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	/*PSEFindSrcBtn->Font = gcnew ::Font(PSEFindSrcBtn->Font, ::FontStyle::Regular);
	PSEFindSrcBtn->Refresh();*/
}

void Form1::PSEDropContextSave_Click(System::Object^  sender, System::EventArgs^  e)
{
	SaveFileDialog^ sf = gcnew SaveFileDialog();
	sf->InitialDirectory = IMAGESET[FILELISTINDEX]->FilePath;
	sf->Filter = "FITS|*.fits;*.fit;*.fts";
	sf->OverwritePrompt = false;
	if (sf->ShowDialog() == ::DialogResult::Cancel)
		return;

	for (int i = 0; i < PSEDrop->Items->Count; i++)
	{
		if (WorldCoordinateSolution::Exists(IMAGESET[FILELISTINDEX], gcnew array<String^>(2) { "TAN", "TAN" }))
		{
			WCS = gcnew JPFITS::WorldCoordinateSolution();
			WCS->Get_WCS(IMAGESET[FILELISTINDEX]);
			PSES[i]->Generate_Source_RADec_Coords(WCS);
		}
		array<String^, 2>^ table = PSES[i]->Source_Table;

		array<String^>^ ttypes = gcnew array<String^>(table->GetLength(0));
		for (int j = 0; j < ttypes->Length; j++)
			ttypes[j] = table[j, 0];

		array<Object^>^ entries = gcnew array<Object^>(ttypes->Length);
		for (int j = 0; j < ttypes->Length; j++)
		{
			if (!JPMath::IsNumeric(table[j, 1]))
			{
				entries[j] = gcnew array<String^>(table->GetLength(1) - 1);
				for (int k = 1; k < table->GetLength(1); k++)
					((array<String^>^)entries[j])[k - 1] = table[j, k];
			}
			else
			{
				entries[j] = gcnew array<double>(table->GetLength(1) - 1);
				for (int k = 1; k < table->GetLength(1); k++)
					((array<double>^)entries[j])[k - 1] = Convert::ToDouble(table[j, k]);
			}
		}

		FITSBinTable^ bt = gcnew FITSBinTable();
		bt->AddExtraHeaderKey("PSESET", PSES[i]->PSEParametersSet.ToString(), "PSE parameters available");
		if (PSES[i]->PSEParametersSet)
		{
			bt->AddExtraHeaderKey("PIXSAT", PSES[i]->PixelSaturation.ToString(), "Pixel saturation threshold");
			bt->AddExtraHeaderKey("KERNRAD", PSES[i]->KernelRadius.ToString(), "Pixel kernel radius");
			bt->AddExtraHeaderKey("SRCSEP", PSES[i]->SourceSeparation.ToString(), "Pixel source separation");
			bt->AddExtraHeaderKey("PIXMIN", PSES[i]->PixelMinimum.ToString(), "Pixel minimum threshold");
			bt->AddExtraHeaderKey("PIXMAX", PSES[i]->PixelMaximum.ToString(), "Pixel maximum threshold");
			bt->AddExtraHeaderKey("KERNMIN", PSES[i]->KernelMinimum.ToString(), "Kernel minimum threshold");
			bt->AddExtraHeaderKey("KERNMAX", PSES[i]->KernelMaximum.ToString(), "Kernel maximum threshold");
			bt->AddExtraHeaderKey("AUTOBG", PSES[i]->AutoBackground.ToString(), "Auto background");
			bt->AddExtraHeaderKey("SAVESRC", PSES[i]->SavePointSources.ToString(), "Save sources");
			//bt->AddExtraHeaderKey("SAVESRCF", PSES[i]->SavePointSources.ToString(), "Save sources file name template");
			bt->AddExtraHeaderKey("ROIONLY", PSES[i]->SearchROI.ToString(), "Search ROI only");
		}
		bt->SetTTYPEEntries(ttypes, nullptr, entries);
		bt->Write(sf->FileName, PSEDrop->Items[i]->ToString(), true);
	}
}

void Form1::PSEDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PSESPLOTALL)
	{
		PSESPLOTALL = false;
		//return;
	}

	PSESINDEX = PSEDrop->SelectedIndex;
	if (PSESRECTS == nullptr || PSESRECTS[PSESINDEX] == nullptr)
	{
		ImageWindow->Refresh();
		SubImageWindow->Refresh();
		return;
	}
	ShowPSEChck->Checked = true;
	MAKEPSERECTS();
	ImageWindow->Refresh();
	SubImageWindow->Refresh();

	if (PSES[PSESINDEX]->PSEParametersSet)
	{
		PSESaturationUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->PixelSaturation);
		PSEKernelRadUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->KernelRadius);
		PSESeparationUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->SourceSeparation);
		PSEPixelMaxUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->PixelMaximum);
		PSEPixelMinUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->PixelMinimum);
		PSEKernelMinUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->KernelMinimum);
		PSEKernelMaxUpD->Value = Convert::ToDecimal(PSES[PSESINDEX]->KernelMaximum);
		PSEAutoBackgroundChck->Checked = PSES[PSESINDEX]->AutoBackground;
		SavePSChck->Checked = PSES[PSESINDEX]->SavePointSources;
		PSESeachROIOnlyChck->Checked = PSES[PSESINDEX]->SearchROI;
	}
}

void Form1::PSEDropContextPlotAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	ShowPSEChck->Checked = true;
	PSESPLOTALL = true;
	SubImageWindow->Refresh();
	ImageWindow->Refresh();
}

void Form1::PSEDropContextPlotNone_Click(System::Object^  sender, System::EventArgs^  e)
{
	ShowPSEChck->Checked = false;
	SubImageWindow->Refresh();
	ImageWindow->Refresh();
}

void Form1::PSEDropContextRemove_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (PSES == nullptr || PSES->Length == 0)
		return;

	array<JPFITS::SourceExtractor^>^ temppses = gcnew array<JPFITS::SourceExtractor^>(PSES->Length - 1);
	array<array<Rectangle>^>^ temprecs = gcnew array<array<Rectangle>^>(PSES->Length - 1);

	int c = 0;
	for (int i = 0; i < PSES->Length; i++)
	{
		if (i != PSEDrop->SelectedIndex)
		{
			temppses[c] = PSES[i];
			temprecs[c] = PSESRECTS[i];
			c++;
		}
	}
	PSES = temppses;
	PSESRECTS = temprecs;
	if (PSESINDEX >= PSES->Length)
		PSESINDEX = PSES->Length - 1;

	PSEDrop->Items->RemoveAt(PSEDrop->SelectedIndex);
	PSEDrop->SelectedIndex = PSESINDEX;

	if (PSES->Length == 0)
	{
		PSES = nullptr;
		PSESRECTS = nullptr;
		PSESINDEX = -1;
		PSECOUNT = 0;
		PSEDrop->Enabled = false;
		ImageWindow->Refresh();
		SubImageWindow->Refresh();
	}
}

void Form1::PSEDropContextClearAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	PSES = nullptr;
	PSESRECTS = nullptr;
	PSESINDEX = -1;
	PSECOUNT = 0;
	PSEDrop->Items->Clear();
	PSEDrop->Enabled = false;
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::PSEDropContextAdd_Click(System::Object^  sender, System::EventArgs^  e)
{
	PSECOUNT++;
	array<JPFITS::SourceExtractor^>^ temppses = gcnew array<JPFITS::SourceExtractor^>(PSES->Length + 1);
	array<array<Rectangle>^>^ temprecs = gcnew array<array<Rectangle>^>(PSES->Length + 1);
	for (int i = 0; i < PSES->Length; i++)
	{
		temppses[i] = PSES[i];
		temprecs[i] = PSESRECTS[i];
	}
	PSES = temppses;
	PSESRECTS = temprecs;
	PSESINDEX = PSEDrop->Items->Count - 1;

	PSEDrop->Items->Add("PSE_" + PSECOUNT.ToString());
	PSEDrop->SelectedIndex = PSEDrop->Items->Count - 1;

	ShowPSEChck->Checked = false;
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::PSEFindSrcBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (FIRSTLOAD)
		return;

	String^ saveps;
	if (PSESAVEKERNELPATH != nullptr)
		saveps = PSESAVEKERNELPATH + "//" + IMAGESET[FILELISTINDEX]->FileName;

	if (e->Button == ::MouseButtons::Left)
	{
		//Form1::Enabled = false;

		double pix_min = (double)PSEPixelMinUpD->Value;
		double pix_max = (double)PSEPixelMaxUpD->Value;
		double pix_sat = (double)PSESaturationUpD->Value;
		double count_min = (double)PSEKernelMinUpD->Value;
		double count_max = (double)PSEKernelMaxUpD->Value;
		bool auto_bg = PSEAutoBackgroundChck->Checked;
		bool sn = (PSEPixelValLbl->Text->Contains("SN"));
		int kernel_radius = (int)PSEKernelRadUpD->Value;
		int src_sep = (int)PSESeparationUpD->Value;

		SetReg("CCDLAB", "PSEPixValMin", pix_min.ToString());
		SetReg("CCDLAB", "PSEPixSaturation", pix_sat.ToString());
		SetReg("CCDLAB", "PSECountValMin", count_min.ToString());
		SetReg("CCDLAB", "PSEPixValMax", pix_max.ToString());
		SetReg("CCDLAB", "PSECountValMax", count_max.ToString());
		SetReg("CCDLAB", "PSEWidth", PSEKernelRadUpD->Value.ToString());
		SetReg("CCDLAB", "PSESeparation", PSESeparationUpD->Value.ToString());
		if (PSESeachROIOnlyChck->Checked)
		{
			if (PSEEllipticalROI->Checked)//elliptical ROI
			{
				SetReg("CCDLAB", "ROIX0", XSUBRANGE[SUBIMAGE_HWX]);
				SetReg("CCDLAB", "ROIY0", YSUBRANGE[SUBIMAGE_HWY]);
				SetReg("CCDLAB", "ROIXRad", SUBIMAGE_HWX);
				SetReg("CCDLAB", "ROIYRad", SUBIMAGE_HWY);
				ROIX0 = XSUBRANGE[SUBIMAGE_HWX];
				ROIY0 = YSUBRANGE[SUBIMAGE_HWY];
				ROIXRad = SUBIMAGE_HWX;
				ROIYRad = SUBIMAGE_HWY;

				ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);
				#pragma omp parallel for
				for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
				{
					double dx2 = double(x - ROIX0);
					dx2 *= dx2;
					dx2 /= double(ROIXRad * ROIXRad);
					for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
					{
						double dy2 = double(y - ROIY0);
						dy2 *= dy2;
						dy2 /= double(ROIYRad * ROIYRad);

						if (dx2 + dy2 <= 1)
							ROI_REGION[x, y] = true;
					}
				}
			}

			if (!PSEEllipticalROI->Checked && !PSEDrawROI->Checked)//either elliptical nor drawn...so just existing curusor box
			{
				ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);

				for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
					for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
						if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
							ROI_REGION[x, y] = true;
			}
		}

		if (PSEKernelRadUpD->Value == 0)
		{
			count_min = ::Double::MinValue;
			count_max = ::Double::MaxValue;
		}

		if (PSES == nullptr)
		{
			PSECOUNT++;
			PSES = gcnew array<JPFITS::SourceExtractor^>(1) { gcnew JPFITS::SourceExtractor() };
			PSESINDEX = 0;
		}
		else
			PSES[PSESINDEX] = gcnew JPFITS::SourceExtractor();

		PSES[PSESINDEX]->Extract_Sources(IMAGESET[FILELISTINDEX]->Image, pix_sat, pix_min, pix_max, count_min, count_max, sn, kernel_radius, src_sep, auto_bg, saveps, ROI_REGION, true);

		if (PSES[PSESINDEX]->N_Sources == 0)
		{
			MessageBox::Show("Found 0 sources matching search criteria...", "Nothing found...");
			Form1::Enabled = true;
			PSETableViewBtn->Enabled = false;
			return;
		}

		if (PSES[PSESINDEX]->N_Sources == -1)//cancelled
		{
			ShowPSEChck->Checked = false;
			ImageWindow->Refresh();
			SubImageWindow->Refresh();
			Form1::Enabled = true;
			PSETableViewBtn->Enabled = false;
			return;
		}

		PSEDrop->Enabled = true;
		if (PSEDrop->Items->Count == 0)
		{
			PSEDrop->Items->Add("PSE_1");
			PSEDrop->SelectedIndex = 0;
		}
	}

	if (e->Button == ::MouseButtons::Right)
	{
		if (PSES == nullptr || PSES[PSESINDEX]->N_Sources < 1)
			return;

		if (MessageBox::Show("Are you sure you want to re-determine the Point Source Extraction with the current cooridnates?", "Warning...", MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;

		array<double>^ Xcoords = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		array<double>^ Ycoords = gcnew array<double>(PSES[PSESINDEX]->N_Sources);
		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		{
			Xcoords[i] = PSES[PSESINDEX]->Centroids_X[i];
			Ycoords[i] = PSES[PSESINDEX]->Centroids_Y[i];
		}

		PSES[PSESINDEX] = gcnew JPFITS::SourceExtractor();
		PSES[PSESINDEX]->Extract_Sources(IMAGESET[FILELISTINDEX]->Image, Xcoords, Ycoords, (int)PSEKernelRadUpD->Value, PSEAutoBackgroundChck->Checked, saveps);
	}

	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	if (PSESRECTS == nullptr)
		PSESRECTS = gcnew array<array<Rectangle>^>(1) { gcnew array<Rectangle>(PSES[PSESINDEX]->N_Sources) };
	else
		PSESRECTS[PSESINDEX] = gcnew array<Rectangle>(PSES[PSESINDEX]->N_Sources);

	#pragma omp parallel for
	for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		PSESRECTS[PSESINDEX][i] = Rectangle(int((float(PSES[PSESINDEX]->Centroids_X[i]) + 0.5)*xsc - 3), int((float(PSES[PSESINDEX]->Centroids_Y[i]) + 0.5)*ysc - 3), 7, 7);

	PSEFitResultListBox->Items->Clear();
	PSEFitResultListBox->Items->Add(String::Concat("N:   ", PSES[PSESINDEX]->N_Sources));
	PSEFitResultListBox->Visible = true;
	ShowPSEChck->Checked = true;
	ShowPSEChck->Enabled = true;
	PSETableViewBtn->Enabled = true;
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
	//Form1::Enabled = true;
}

void Form1::PSEFindSrcBtn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){}

void Form1::PSEFindSrcBtn_Click(System::Object^  sender, System::EventArgs^  e){}

void Form1::ShowPSEChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::PSEFitWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	/*int pix_min = (int)PSEPixelMinUpD->Value;
	int pix_max = (int)PSEPixelMaxUpD->Value;
	int count_min = (int)PSECountMinUpD->Value;
	int count_max = (int)PSECountMaxUpD->Value;
	bool auto_bg = PSEAutoBackgroundChck->Checked;
	int src_radius = (int)PSEWidthUpD->Value;
	int ImInd = ::Convert::ToInt32(e->Argument);

	pse = gcnew PSE();
	pse->Extract(IMAGESET[ImInd]->Image,(double)pix_min,(double)pix_max, (double)count_min, (double)count_max, !(PSESigmaCountBtn->Text == "SN"), src_width, auto_bg, false, nullptr, false, 0, 0, 0, 0);//extracts sources and stores them inside class*/
}

void Form1::PSEFitWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
}

void Form1::PSEFitWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	/*Form1::Enabled = true;
	PSEFitResultListBox->Items->Clear();
	PSEFitResultListBox->Items->Add(String::Concat("N:   ",pse->N_Sources));
	PSEFitResultListBox->Visible = true;*/
}

void Form1::ROIFitFcnDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetParametersChck->Checked = false;
}

void Form1::SetParametersChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (ROIFitFcnDrop->SelectedIndex < 0)
	{
		SetParametersChck->Checked = false;
		return;
	}


	if (SetParametersChck->Checked)
	{
		array<double>^ x = gcnew array<double>(XSUBRANGE->Length);
		array<double>^ y = gcnew array<double>(YSUBRANGE->Length);
		Array::Copy(XSUBRANGE, x, x->Length);
		Array::Copy(YSUBRANGE, y, y->Length);
		FPW = gcnew FitParametersWindow(ROIFitFcnDrop->SelectedIndex, x, y, SUBIMAGE);
		FPW->ShowDialog(this);

		if (FPW->DialogResult == ::DialogResult::Cancel)
			SetParametersChck->Checked = false;
	}
}

void Form1::ROIFitBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	//SUBIMAGE is the ROI

	if (FIRSTLOAD)
		return;

	if (ROIFitFcnDrop->SelectedIndex < 0)
		ROIFitFcnDrop->SelectedIndex = 0;

	//check if marked coordinates are all within the ROI...if they are then do compound fit
	int c = 0;
	if (MARKCOORDS != nullptr && MARKCOORDS->Length != 0)//also check if they are inside ROI
		for (int i = 0; i < MARKCOORDS->GetLength(1); i++)
			if ((int)MARKCOORDS[0, i] > XSUBRANGE[0] && (int)MARKCOORDS[0, i] < XSUBRANGE[XSUBRANGE->Length - 1] && (int)MARKCOORDS[1, i] > YSUBRANGE[0] && (int)MARKCOORDS[1, i] < YSUBRANGE[YSUBRANGE->Length - 1])
				c++;
	if (MARKCOORDS != nullptr && MARKCOORDS->Length != 0 && c == MARKCOORDS->GetLength(1))
	{
		ROICompoundFit();//do compound fit
		return;
	}

	//check if multiple PSE coords are within the ROI...if they are then gather them to marked coords and do compound fit
	if (PSES != nullptr && PSES[PSESINDEX]->N_Sources > 0)
	{
		ArrayList^ contained = gcnew ArrayList();

		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
			if (PSES[PSESINDEX]->Centroids_X[i] > XSUBRANGE[0] && PSES[PSESINDEX]->Centroids_X[i] < XSUBRANGE[SUBIMAGE_HWX * 2] && PSES[PSESINDEX]->Centroids_Y[i] > YSUBRANGE[0] && PSES[PSESINDEX]->Centroids_Y[i] < YSUBRANGE[SUBIMAGE_HWY * 2])
			{
				contained->Add(PSES[PSESINDEX]->Centroids_X[i]);
				contained->Add(PSES[PSESINDEX]->Centroids_Y[i]);
			}

		if (contained->Count > 2)
		{
			MARKCOORDS = gcnew array<double, 2>(2, contained->Count / 2);
			for (int i = 0; i < contained->Count / 2; i++)
			{
				MARKCOORDS[0, i] = Convert::ToDouble(contained[i * 2]);
				MARKCOORDS[1, i] = Convert::ToDouble(contained[i * 2 + 1]);
			}
			ROICompoundFit();//do compound fit
			MARKCOORDS = nullptr;
			return;
		}
	}

	//else just do single fit on the ROI
	Form1::Enabled = false;
	
	array<double>^ P;
	array<double>^ P_err;
	array<double>^ PLB;
	array<double>^ PUB;
	array<double,2>^ fit_resid = gcnew array<double, 2>(SUBIMAGE->GetLength(0), SUBIMAGE->GetLength(1));
	
	if (ROIFitFcnDrop->SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
		P = gcnew array<double>(5){ JPMath::Max(SUBIMAGE, false) - JPMath::Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 4, JPMath::Min(SUBIMAGE, false) };
	if (ROIFitFcnDrop->SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
		P = gcnew array<double>(7) { JPMath::Max(SUBIMAGE, false) - JPMath::Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 0, 4, 4, JPMath::Min(SUBIMAGE, false) };
	if (ROIFitFcnDrop->SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) ^ (-p(4)) + p(5)
		P = gcnew array<double>(6) { JPMath::Max(SUBIMAGE, false) - JPMath::Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 4, 4, JPMath::Min(SUBIMAGE, false) };
	if (ROIFitFcnDrop->SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) ^ (-p(6)) + p(7)
		P = gcnew array<double>(8) { JPMath::Max(SUBIMAGE, false) - JPMath::Min(SUBIMAGE, false), (double)XSUBRANGE[SUBIMAGE_HWX], (double)YSUBRANGE[SUBIMAGE_HWY], 0, 4, 4, 4, JPMath::Min(SUBIMAGE, false) };

	P_err = gcnew array<double>(P->Length);

	if (SetParametersChck->Checked)
	{
		for (int i = 0; i < P->Length; i++)
			P[i] = ::Convert::ToDouble(FPW->PITXTARRAY[i]->Text);

		if (FPW->ConstrainBtn->Checked)
		{
			PLB = gcnew array<double>(P->Length);
			PUB = gcnew array<double>(P->Length);
			for (int i = 0; i < P->Length; i++)
			{
				PLB[i] = ::Convert::ToDouble(FPW->PLBTXTARRAY[i]->Text);
				PUB[i] = ::Convert::ToDouble(FPW->PUBTXTARRAY[i]->Text);
			}
		}
	}

	if (ROIFitFcnDrop->SelectedIndex == 0 || ROIFitFcnDrop->SelectedIndex == 1)//Gaussian
		JPMath::Fit_Gaussian2d(XSUBRANGE, YSUBRANGE, SUBIMAGE, P, PLB, PUB, P_err, fit_resid);
	if (ROIFitFcnDrop->SelectedIndex == 2 || ROIFitFcnDrop->SelectedIndex == 3)//Moffat
		JPMath::Fit_Moffat2d(XSUBRANGE, YSUBRANGE, SUBIMAGE, P, PLB, PUB, P_err, fit_resid);

	double chisq_norm = 0;
	for (int i = 0; i < SUBIMAGE->GetLength(0); i++)
		for (int j = 0; j < SUBIMAGE->GetLength(1); j++)
		{
			if (SUBIMAGE[i, j] - P[P->Length - 1] == 0)
				chisq_norm += fit_resid[i, j] * fit_resid[i, j];
			else
				chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math::Abs(SUBIMAGE[i, j] - P[P->Length - 1]);
		}
	chisq_norm /= (SUBIMAGE->Length - P->Length);

	/*double xposfit, yposfit;
	try//for UVIT to get position of focused spot
	{
		String^ xrng = IMAGESET[FILELISTINDEX]->GetKeyValue("EXTXRNG");
		int indx = xrng->IndexOf(":");
		double xxrng = ::Convert::ToDouble(xrng->Substring(0,indx));
		String^ yrng = IMAGESET[FILELISTINDEX]->GetKeyValue("EXTYRNG");
		int indy = yrng->IndexOf(":");
		double yyrng = ::Convert::ToDouble(yrng->Substring(0,indy));
		double resln = ::Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("CNTDRSLN"));

		double xxrngsub = 0.0;
		double yyrngsub = 0.0;
		if (SUBRANGE[0] != -1)//then it WAS loaded as a subimage so set value for image coordinate matching; [0] = xstart, [2] = ystart
		{
			double res = ::Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("CNTDRSLN"));
			xxrngsub = ((double)SUBRANGE[0])/res;
			yyrngsub = ((double)SUBRANGE[2])/res;
		}
		
		xposfit = (double(XSUBRANGE[0]) + P[1])/resln + ::Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("XOFFSET")) + xxrng + xxrngsub + 1;
		yposfit = (double(YSUBRANGE[0]) + P[2])/resln + ::Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("YOFFSET")) + yyrng + yyrngsub + 1;
	}
	catch (...)
	{
		xposfit = P[1] + XSUBRANGE[SUBIMAGE_HWX];
		yposfit = P[2] + YSUBRANGE[SUBIMAGE_HWY];
	}*/

	PSEFitResultListBox->Items->Clear();
	PSEFitResultListBox->Items->Add("Amplitude:     " + Math::Round(P[0], 4) + " +- " + Math::Round(P_err[0], 4));
	PSEFitResultListBox->Items->Add("X0:                " + Math::Round(P[1], 4) + " +- " + Math::Round(P_err[1], 4));
	PSEFitResultListBox->Items->Add("Y0:                " + Math::Round(P[2], 4) + " +- " + Math::Round(P_err[2], 4));
	if (ROIFitFcnDrop->SelectedIndex == 0)//Circular Gaussian
	{
		PSEFitResultListBox->Items->Add("Sigma:           " + Math::Round(P[3],4) + " +- " + Math::Round(P_err[3], 4));
		PSEFitResultListBox->Items->Add("FWHM:         " + Math::Round(P[3]*2.3548,4) + " +- " + Math::Round(P_err[3]*2.3548, 4));
		PSEFitResultListBox->Items->Add("Bias:              " + Math::Round(P[4],4) + " +- " + Math::Round(P_err[4], 4));
		PSEFitResultListBox->Items->Add("Volume:         " + Math::Round(2*Math::PI*P[0]*P[3]*P[3],4));
	}
	if (ROIFitFcnDrop->SelectedIndex == 1)//Elliptical Gaussian
	{
		PSEFitResultListBox->Items->Add("Phi:               " + Math::Round(P[3], 4) + " +- " + Math::Round(P_err[3], 4));
		PSEFitResultListBox->Items->Add("Sigma_X:       " + Math::Round(P[4],4) + " +- " + Math::Round(P_err[4], 4));
		PSEFitResultListBox->Items->Add("FWHM_X:     " + Math::Round(P[4]*2.3548,4) + " +- " + Math::Round(P_err[4] * 2.3548, 4));
		PSEFitResultListBox->Items->Add("Sigma_Y:       " + Math::Round(P[5],4) + " +- " + Math::Round(P_err[5], 4));
		PSEFitResultListBox->Items->Add("FWHM_Y:     " + Math::Round(P[5]*2.3548,4) + " +- " + Math::Round(P_err[5] * 2.3548, 4));
		PSEFitResultListBox->Items->Add("Bias:              " + Math::Round(P[6],4) + " +- " + Math::Round(P_err[6], 4));
		PSEFitResultListBox->Items->Add("Volume:         " + Math::Round(2 * Math::PI*P[0] * P[4] * P[5], 4));
	}
	if (ROIFitFcnDrop->SelectedIndex == 2)//Circular Moffat
	{
		PSEFitResultListBox->Items->Add("Theta:           " + Math::Round(P[3],4) + " +- " + Math::Round(P_err[3], 4));
		PSEFitResultListBox->Items->Add("Beta:             " + Math::Round(P[4],4) + " +- " + Math::Round(P_err[4], 4));
		PSEFitResultListBox->Items->Add("FWHM:         " + Math::Round(2* P[3]*Math::Sqrt(Math::Pow(2, 1/P[4])-1),4));
		PSEFitResultListBox->Items->Add("Bias:              " + Math::Round(P[5],4) + " +- " + Math::Round(P_err[5], 4));
		PSEFitResultListBox->Items->Add("Volume:         " + Math::Round(Math::PI * P[3] * P[3] * P[0] / (P[4] - 1), 4));
	}
	if (ROIFitFcnDrop->SelectedIndex == 3)//Elliptical Moffat
	{
		PSEFitResultListBox->Items->Add("Phi:               " + Math::Round(P[3], 4) + " +- " + Math::Round(P_err[3], 4));
		PSEFitResultListBox->Items->Add("Theta_X:       " + Math::Round(P[4],4) + " +- " + Math::Round(P_err[4], 4));
		PSEFitResultListBox->Items->Add("Theta_Y:       " + Math::Round(P[5],4) + " +- " + Math::Round(P_err[5], 4));
		PSEFitResultListBox->Items->Add("Beta:              " + Math::Round(P[6],4) + " +- " + Math::Round(P_err[6], 4));
		PSEFitResultListBox->Items->Add("FWHM_X:     " + Math::Round(2* P[4]*Math::Sqrt(Math::Pow(2,1/ P[6])-1),4));
		PSEFitResultListBox->Items->Add("FWHM_Y:     " + Math::Round(2* P[5]*Math::Sqrt(Math::Pow(2,1/ P[6])-1),4));
		PSEFitResultListBox->Items->Add("Bias:              " + Math::Round(P[7],4) + " +- " + Math::Round(P_err[7], 4));
		PSEFitResultListBox->Items->Add("Volume:         " + Math::Round(Math::PI * P[4] * P[5] * P[0] / (P[6] - 1), 4));
	}
	PSEFitResultListBox->Items->Add("Chi^2/dof:     " + Math::Round(chisq_norm, 4));
	PSEFitResultListBox->Visible = true;
	PSEFitResultListBox->Refresh();

	if (ROIViewFitChck->Checked)
	{
		MLCCDLAB::MLSurface^ surf = gcnew MLCCDLAB::MLSurface();
		array<double, 2>^ fit = gcnew array<double, 2>(SUBIMAGE->GetLength(0), SUBIMAGE->GetLength(1));
		if (ROIFitFcnDrop->SelectedIndex <= 1)
			JPMath::Gaussian2d(XSUBRANGE, YSUBRANGE, fit, P, false);
		else
			JPMath::Moffat2d(XSUBRANGE, YSUBRANGE, fit, P, false);
		MWNumericArray^ mwfit = gcnew MWNumericArray(fit);
		MWNumericArray^ mwsubim = gcnew MWNumericArray(SUBIMAGE);
		MWCharArray^ type = gcnew MWCharArray(ROIFitFcnDrop->Text);
		surf->Surf_FitOverlay(mwsubim, mwfit, type);
		//surf->Surf_FitOverlayBar(mwsubim, mwfit, type);
	}

	Form1::Enabled = true;
}

void Form1::ROICompoundFit()
{
	Form1::Enabled = false;

	bool view = ROIViewFitChck->Checked;

	int count = MARKCOORDS->GetLength(1), func;
	String^ funcstr;
	array<double, 2>^ P;
	array<double, 2>^ P_err;
	array<double, 2>^ PLB;
	array<double, 2>^ PUB;
	array<double, 2>^ fit_resid = gcnew array<double, 2>(SUBIMAGE->GetLength(0), SUBIMAGE->GetLength(1));
	if (ROIFitFcnDrop->SelectedIndex == 0)//Circular Gaussian: G(x,y|P) = P(0)*exP(-((x-P(1))^2 + (y - P(2))^2)/(2*P(3)^2)) + P(4)
	{
		func = 5;
		funcstr = "Circular Gaussian: G(x,y|P) = P(0)*exp(-((x-P(1))^2 + (y - P(2))^2)/(2*P(3)^2)) + P(4)";
	}
	if (ROIFitFcnDrop->SelectedIndex == 1)//Elliptical Gaussian: G(x,y|P) = P(0)*exp(-((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 / (2*P(4)^2) - (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3))).^2 / (2*P(5)^2) ) + P(6)
	{
		func = 7;
		funcstr = "Elliptical Gaussian: G(x,y|P) = P(0)*exp(-((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 / (2*P(4)^2) - (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3))).^2 / (2*P(5)^2) ) + P(6)";
	}
	if (ROIFitFcnDrop->SelectedIndex == 2)//Circular Moffat: M(x,y|P) = P(0) * ( 1 + { (x-P(1))^2 + (y-P(2))^2 } / P(3)^2 ) ^ (-P(4)) + P(5)
	{
		func = 6;
		funcstr = "Circular Moffat: M(x,y|P) = P(0) * ( 1 + { (x-P(1))^2 + (y-P(2))^2 } / P(3)^2 ) ^ (-P(4)) + P(5)";
	}
	if (ROIFitFcnDrop->SelectedIndex == 3)//Elliptical Moffat: M(x,y|P) = P(0) * ( 1 + { ((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 } / P(4)^2 + { (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3)))^2 } / P(5)^2 ) ^ (-P(6)) + P(7)
	{
		func = 8;
		funcstr = "Elliptical Moffat: M(x,y|P) = P(0) * ( 1 + { ((x-P(1))*cos(P(3)) + (y-P(2))*sin(P(3)))^2 } / P(4)^2 + { (-(x-P(1))*sin(P(3)) + (y-P(2))*cos(P(3)))^2 } / P(5)^2 ) ^ (-P(6)) + P(7)";
	}

	P = gcnew array<double, 2>(func, count);
	PLB = gcnew array<double, 2>(func, count);
	PUB = gcnew array<double, 2>(func, count);
	P_err = gcnew array<double, 2>(func, count);

	for (int i = 0; i < count; i++)
	{
		P[0, i] = IMAGESET[FILELISTINDEX]->Image[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] - SUBIMAGEMIN;
		P[1, i] = MARKCOORDS[0, i];
		P[2, i] = MARKCOORDS[1, i];
		P[func - 1, i] = SUBIMAGEMIN;

		PLB[0, i] = P[0, i] / 3;
		PLB[1, i] = MARKCOORDS[0, i] - 1;
		PLB[2, i] = MARKCOORDS[1, i] - 1;
		PLB[func - 1, i] = SUBIMAGEMIN - P[0, i] / 2;

		PUB[0, i] = P[0, i] * 3;
		PUB[1, i] = MARKCOORDS[0, i] + 1;
		PUB[2, i] = MARKCOORDS[1, i] + 1;
		PUB[func - 1, i] = SUBIMAGEMIN + P[0, i] / 2;
	}

	if (ROIFitFcnDrop->SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
		for (int i = 0; i < count; i++)
		{
			P[3, i] = 2;
			PLB[3, i] = 0.1;
			PUB[3, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			if (SetParametersChck->Checked)
			{
				P[3, i] = Convert::ToDouble(FPW->PITXTARRAY[3]->Text);

				if (FPW->ConstrainBtn->Checked)
				{
					PLB[3, i] = Convert::ToDouble(FPW->PLBTXTARRAY[3]->Text);
					PUB[3, i] = Convert::ToDouble(FPW->PUBTXTARRAY[3]->Text);
				}
			}
		}
	if (ROIFitFcnDrop->SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
		for (int i = 0; i < count; i++)
		{
			P[3, i] = 0;
			PLB[3, i] = -Math::PI;
			PUB[3, i] = Math::PI;

			P[4, i] = 2;
			PLB[4, i] = 0.1;
			PUB[4, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			P[5, i] = 2;
			PLB[5, i] = 0.1;
			PUB[5, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			if (SetParametersChck->Checked)
			{
				P[4, i] = Convert::ToDouble(FPW->PITXTARRAY[4]->Text);
				P[5, i] = Convert::ToDouble(FPW->PITXTARRAY[5]->Text);

				if (FPW->ConstrainBtn->Checked)
				{
					PLB[4, i] = Convert::ToDouble(FPW->PLBTXTARRAY[4]->Text);
					PUB[4, i] = Convert::ToDouble(FPW->PUBTXTARRAY[4]->Text);

					PLB[5, i] = Convert::ToDouble(FPW->PLBTXTARRAY[5]->Text);
					PUB[5, i] = Convert::ToDouble(FPW->PUBTXTARRAY[5]->Text);
				}
			}
		}
	if (ROIFitFcnDrop->SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) ^ (-p(4)) + p(5)
		for (int i = 0; i < count; i++)
		{
			P[3, i] = 2;
			PLB[3, i] = 0.1;
			PUB[3, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			P[4, i] = 2;
			PLB[4, i] = 1;
			PUB[4, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			if (SetParametersChck->Checked)
			{
				P[3, i] = Convert::ToDouble(FPW->PITXTARRAY[3]->Text);
				P[4, i] = Convert::ToDouble(FPW->PITXTARRAY[4]->Text);

				if (FPW->ConstrainBtn->Checked)
				{
					PLB[3, i] = Convert::ToDouble(FPW->PLBTXTARRAY[3]->Text);
					PUB[3, i] = Convert::ToDouble(FPW->PUBTXTARRAY[3]->Text);

					PLB[4, i] = Convert::ToDouble(FPW->PLBTXTARRAY[4]->Text);
					PUB[4, i] = Convert::ToDouble(FPW->PUBTXTARRAY[4]->Text);
				}
			}
		}
	if (ROIFitFcnDrop->SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) ^ (-p(6)) + p(7)
		for (int i = 0; i < count; i++)
		{
			P[3, i] = 0;
			PLB[3, i] = -Math::PI;
			PUB[3, i] = Math::PI;

			P[4, i] = 2;
			PLB[4, i] = 0.1;
			PUB[4, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			P[5, i] = 2;
			PLB[5, i] = 0.1;
			PUB[5, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			P[6, i] = 2;
			PLB[6, i] = 1;
			PUB[6, i] = Math::Sqrt(SUBIMAGE_HWX * SUBIMAGE_HWX + SUBIMAGE_HWY * SUBIMAGE_HWY) / 3;

			if (SetParametersChck->Checked)
			{
				P[4, i] = Convert::ToDouble(FPW->PITXTARRAY[4]->Text);
				P[5, i] = Convert::ToDouble(FPW->PITXTARRAY[5]->Text);
				P[6, i] = Convert::ToDouble(FPW->PITXTARRAY[6]->Text);

				if (FPW->ConstrainBtn->Checked)
				{
					PLB[4, i] = Convert::ToDouble(FPW->PLBTXTARRAY[4]->Text);
					PUB[4, i] = Convert::ToDouble(FPW->PUBTXTARRAY[4]->Text);

					PLB[5, i] = Convert::ToDouble(FPW->PLBTXTARRAY[5]->Text);
					PUB[5, i] = Convert::ToDouble(FPW->PUBTXTARRAY[5]->Text);

					PLB[6, i] = Convert::ToDouble(FPW->PLBTXTARRAY[6]->Text);
					PUB[6, i] = Convert::ToDouble(FPW->PUBTXTARRAY[6]->Text);
				}
			}
		}
		
	if (ROIFitFcnDrop->SelectedIndex <= 1)
		JPMath::Fit_Gaussian2d_Compound(XSUBRANGE, YSUBRANGE, SUBIMAGE, P, PLB, PUB, P_err, fit_resid);
	else
		JPMath::Fit_Moffat2d_Compound(XSUBRANGE, YSUBRANGE, SUBIMAGE, P, PLB, PUB, P_err, fit_resid);

	double chisq_norm = 0;
	for (int i = 0; i < SUBIMAGE->GetLength(0); i++)
		for (int j = 0; j < SUBIMAGE->GetLength(1); j++)
		{
			if (SUBIMAGE[i, j] - P[func - 1, count - 1] == 0)
				chisq_norm += fit_resid[i, j] * fit_resid[i, j];
			else
				chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math::Abs(SUBIMAGE[i, j] - P[func - 1, count - 1]);
		}
	chisq_norm /= (SUBIMAGE->Length - P->Length + count - 1);

	PSETableViewer^ v = gcnew PSETableViewer();
	v->PSETable->ColumnCount = func;
	v->PSETable->RowCount = count;

	for (int i = 0; i < func; i++)
		v->PSETable->Columns[i]->HeaderText = "P" + i;

	v->PSETable->ColumnCount += 2;
	if (ROIFitFcnDrop->SelectedIndex == 1 || ROIFitFcnDrop->SelectedIndex == 3)
		v->PSETable->ColumnCount++;	
	v->PSETable->Columns[func]->HeaderText = "Volume";
	v->PSETable->Columns[func + 1]->HeaderText = "FWHM";
	if (ROIFitFcnDrop->SelectedIndex == 1 || ROIFitFcnDrop->SelectedIndex == 3)
	{
		v->PSETable->Columns[func + 1]->HeaderText = "FWHMX";
		v->PSETable->Columns[func + 2]->HeaderText = "FWHMY";
	}

	for (int i = 0; i < count; i++)
		for (int j = 0; j < func; j++)
			v->PSETable[j, i]->Value = P[j, i];

	double volume, FWHM, FWHMX, FWHMY;
	for (int i = 0; i < count; i++)
	{
		if (ROIFitFcnDrop->SelectedIndex == 0)//Circular Gaussian //G(x,y|p) = p(0)*exp(-((x-p(1))^2 + (y - p(2))^2)/(2*p(3)^2)) + p(4)
		{
			volume = Math::Round(2 * Math::PI * P[0, i] * P[3, i] * P[3, i], 4);
			FWHM = Math::Round(P[3, i] * 2.3548, 4);
		}
		if (ROIFitFcnDrop->SelectedIndex == 1)//Elliptical Gaussian  //G(x,y|p) = p(0)*exp(-((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 / (2*p(4)^2) - (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3))).^2 / (2*p(5)^2) ) + p(6)
		{
			volume = Math::Round(2 * Math::PI * P[0, i] * P[4, i] * P[5, i], 4);
			FWHMX = Math::Round(P[4, i] * 2.3548, 4);
			FWHMY = Math::Round(P[5, i] * 2.3548, 4);
		}
		if (ROIFitFcnDrop->SelectedIndex == 2)//Circular Moffat  //M(x,y|p) = p(0) * ( 1 + { (x-p(1))^2 + (y-p(2))^2 } / p(3)^2 ) ^ (-p(4)) + p(5)
		{
			volume = Math::Round(Math::PI * P[3, i] * P[3, i] * P[0, i] / (P[4, i] - 1), 4);
			FWHM = Math::Round(2 * P[3, i] * Math::Sqrt(Math::Pow(2, 1 / P[4, i]) - 1), 4);
		}
		if (ROIFitFcnDrop->SelectedIndex == 3)//Elliptical Moffat  //M(x,y|p) = p(0) * ( 1 + { ((x-p(1))*cos(p(3)) + (y-p(2))*sin(p(3)))^2 } / p(4)^2 + { (-(x-p(1))*sin(p(3)) + (y-p(2))*cos(p(3)))^2 } / p(5)^2 ) ^ (-p(6)) + p(7)
		{
			volume = Math::Round(Math::PI * P[4, i] * P[5, i] * P[0, i] / (P[6, i] - 1), 4);
			FWHMX = Math::Round(2 * P[4, i] * Math::Sqrt(Math::Pow(2, 1 / P[6, i]) - 1), 4);
			FWHMY = Math::Round(2 * P[5, i] * Math::Sqrt(Math::Pow(2, 1 / P[6, i]) - 1), 4);
		}

		v->PSETable[func, i]->Value = volume;
		v->PSETable[func + 1, i]->Value = FWHM;

		if (ROIFitFcnDrop->SelectedIndex == 1 || ROIFitFcnDrop->SelectedIndex == 3)
		{
			v->PSETable[func + 1, i]->Value = FWHMX;
			v->PSETable[func + 2, i]->Value = FWHMY;
		}
	}

	v->Text = funcstr + "; ChiSqNorm: " + chisq_norm.ToString();
	v->Show(this);

	if (view)
	{
		array<double, 2>^ fit = gcnew array<double, 2>(SUBIMAGE->GetLength(0), SUBIMAGE->GetLength(1));
		for (int x = 0; x < SUBIMAGE->GetLength(0); x++)
			for (int y = 0; y < SUBIMAGE->GetLength(1); y++)
				fit[x, y] = SUBIMAGE[x, y] - fit_resid[x, y];

		MLCCDLAB::MLSurface^ surf = gcnew MLCCDLAB::MLSurface();
		MWNumericArray^ mwfit = gcnew MWNumericArray(fit);
		MWNumericArray^ mwsubim = gcnew MWNumericArray(SUBIMAGE);
		MWCharArray^ type = gcnew MWCharArray(ROIFitFcnDrop->Text);
		surf->Surf_FitOverlay(mwsubim, mwfit, type);
		//surf->Surf_FitOverlayBar(mwsubim, mwfit, type);
	}

	Form1::Enabled = true;
}

void Form1::SavePSChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (SavePSChck->Checked)//get folder to save files in
	{
		::FolderBrowserDialog^ fdlg = gcnew FolderBrowserDialog();
		fdlg->SelectedPath = ::Convert::ToString(GetReg("CCDLAB", "PSFolderPath"));
		if (fdlg->ShowDialog() == ::DialogResult::OK)
		{
			PSESAVEKERNELPATH = fdlg->SelectedPath;
			SetReg("CCDLAB", "PSFolderPath", fdlg->SelectedPath);
		}
		else
		{
			SavePSChck->Checked = false;
			PSESAVEKERNELPATH = nullptr;
		}
	}
	else
		PSESAVEKERNELPATH = nullptr;
}

void Form1::COGBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (FIRSTLOAD)
		return;

	Form1::Enabled = false;

	if ((int)COGIgnoreNPtsUpD->Value > (int)HalfWidthXUpD->Value + 1)
		COGIgnoreNPtsUpD->Value = (int)HalfWidthXUpD->Value + 1;
	array<double, 1>^ npts;
	array<double, 1>^ cog;
	String ^ text;
	array<double,1>^ RFitBatchIntercept;
	array<double,1>^ RFitBatchInterceptX;
	double bg, sig;

	array<int>^ inds;
	if (COGBatchChck->Checked)
	{
		inds = gcnew array<int>(IMAGESET->Count);
		for (int i = 0; i < IMAGESET->Count; i++)
			inds[i] = i;

		RFitBatchIntercept = gcnew array<double>(IMAGESET->Count);
		RFitBatchInterceptX = gcnew array<double>(IMAGESET->Count);
	}
	else
	{
		inds = gcnew array<int>(1);
		inds[0] = FILELISTINDEX;
	}

	for (int k = 0; k < inds->Length; k++)
	{
		cog = JPMath::COG(SUBIMAGE, (int)COGIgnoreNPtsUpD->Value, npts, bg, sig);

		if (COGBatchChck->Checked)
		{
			RFitBatchIntercept[k] = sig;
			RFitBatchInterceptX[k] = k+1;
		}

		if (k == 0)
			text += sig.ToString();
		else
			text += "\r\n" + sig.ToString();
	}
	::Clipboard::SetText(text);
	Form1::Enabled = true;

	if (COGViewChck->Checked)
	{
		if (COG_PLOT->IsDisposed)
			COG_PLOT = gcnew JPPlot();

		if (!COGBatchChck->Checked)
		{
			String^ title = "y = a + b*x : a = " + sig.ToString() + ", b = " + bg.ToString();
			COG_PLOT->PlotLine(npts,cog,"N Pixels","Counts",title,::Charting::SeriesChartType::Point, "COG");

			array<double>^ yline = gcnew array<double>(2) { sig, sig + bg * npts[npts->Length - 1] };
			array<double>^ xline = gcnew array<double>(2){0,npts[npts->Length-1]};
			COG_PLOT->AddLine(xline,yline,::Charting::SeriesChartType::Line, "COG Fit");

			array<double>^ xdd = gcnew array<double>(1) { npts[cog->Length - (int)COGIgnoreNPtsUpD->Value] };
			array<double>^ ydd = gcnew array<double>(1) { cog[cog->Length - (int)COGIgnoreNPtsUpD->Value] };
			COG_PLOT->AddLine(xdd, ydd, ::Charting::SeriesChartType::Point, "COG Fit Start");

			BackgroundCountsPixelFrameTxt->Text = bg.ToString("#.0000");
		}
		else
		{
			COG_PLOT->PlotLine(RFitBatchInterceptX,RFitBatchIntercept,"Frame #","Source Count","Source Counts vs. Frame #",::Charting::SeriesChartType::Point, "COG");
		}
		COG_PLOT->Text = "Curve of Growth Photometry";
	}
}

void Form1::PSELoadSrcBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET == nullptr || IMAGESET->Count == 0)
	{
		MessageBox::Show("Please load an image first...", "Error");
		return;
	}

	if (PSELoadSrcDrop->SelectedIndex == 0 && !WorldCoordinateSolution::Exists(IMAGESET[FILELISTINDEX], gcnew array<String^>(2) { "TAN", "TAN" }))
	{
		MessageBox::Show("CD matrix for WCS not found in current image header. Can not transform [RA, Dec] to [x, y]...", "Error...");
		return;
	}

	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Tab Delimited Text|*.txt|CSV (Comma Delimited)|*.csv|FITS BinTable|*.fits;*.fit;*.fts";
	ofd->FilterIndex = Convert::ToInt32(GetReg("CCDLAB", "PSESaveFilter"));
	ofd->Multiselect = true;
	ofd->InitialDirectory = (String^)GetReg("CCDLAB", "PSESavePath");
	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;
	SetReg("CCDLAB", "PSESavePath", ofd->FileName->Substring(0, ofd->FileName->LastIndexOf("\\")));
	SetReg("CCDLAB", "PSESaveFilter", ofd->FilterIndex);

	if (PSELoadSrcDrop->SelectedIndex <= 1)
	{
		if (PSES == nullptr)
		{
			PSES = gcnew array<JPFITS::SourceExtractor^>(ofd->FileNames->Length);
			PSESRECTS = gcnew array<array<Rectangle>^>(ofd->FileNames->Length);
			PSESINDEX = 0;
			PSEDrop->Enabled = true;
		}
		else//add PSES
		{
			array<JPFITS::SourceExtractor^>^ temppses = gcnew array<JPFITS::SourceExtractor^>(PSES->Length + ofd->FileNames->Length);
			array<array<Rectangle>^>^ temprecs = gcnew array<array<Rectangle>^>(PSES->Length + ofd->FileNames->Length);
			for (int i = 0; i < PSES->Length; i++)
			{
				temppses[i] = PSES[i];
				temprecs[i] = PSESRECTS[i];
			}
			PSESINDEX = PSES->Length;
			PSES = temppses;
			PSESRECTS = temprecs;
		}

		for (int i = 0; i < ofd->FileNames->Length; i++)
		{
			String^ delimit = "\t";
			if (ofd->FilterIndex == 2)
				delimit = ",";
			StreamReader^ sr;
			String^ line;

			int Nsrc = 0;
			sr = gcnew StreamReader(ofd->FileNames[i]);
			int j = -1;

			while (!sr->EndOfStream)
			{
				line = sr->ReadLine();
				j++;
				if (j == 0)//check if first line is a header
				{
					int delimitindex = line->IndexOf(delimit);
					if (!JPMath::IsNumeric(line->Substring(0, delimitindex)))
						continue;
				}
				Nsrc++;
			}

			array<double>^ c1 = gcnew array<double>(Nsrc);
			array<double>^ c2 = gcnew array<double>(Nsrc);

			Nsrc = 0;
			sr->BaseStream->Position = 0;
			j = -1;
			while (!sr->EndOfStream)
			{
				line = sr->ReadLine();
				j++;
				int delimitindex = line->IndexOf(delimit);
				if (j == 0)//check if header line
					if (!JPMath::IsNumeric(line->Substring(0, delimitindex)))
						continue;
				c1[Nsrc] = Convert::ToDouble(line->Substring(0, delimitindex));
				int nextdelimitindex = line->IndexOf(delimit, delimitindex + 1);
				if (nextdelimitindex == -1)
					nextdelimitindex = line->Length;
				c2[Nsrc] = Convert::ToDouble(line->Substring(delimitindex + 1, nextdelimitindex - delimitindex - 1));
				Nsrc++;
			}
			sr->Close();

			if (PSELoadSrcDrop->SelectedIndex == 0)//RA, Dec
			{
				WCS = gcnew JPFITS::WorldCoordinateSolution();
				WCS->Get_WCS(IMAGESET[FILELISTINDEX]);
				array<double>^ Xcoords = gcnew array<double>(Nsrc);
				array<double>^ Ycoords = gcnew array<double>(Nsrc);
				WCS->Get_Pixels(c1, c2, "TAN", Xcoords, Ycoords, true);
				PSES[PSESINDEX] = gcnew JPFITS::SourceExtractor(Xcoords, Ycoords);
				PSES[PSESINDEX]->Generate_Source_RADec_Coords(WCS);
			}
			if (PSELoadSrcDrop->SelectedIndex == 1)//X, Y
				PSES[PSESINDEX] = gcnew JPFITS::SourceExtractor(c1, c2);
			MAKEPSERECTS();
			PSECOUNT++;
			PSEDrop->Items->Add(ofd->FileNames[i]->Substring(ofd->FileNames[i]->LastIndexOf("\\") + 1));
			//PSEDrop->SelectedIndex = PSEDrop->Items->Count - 1;
			if (i < ofd->FileNames->Length - 1)
				PSESINDEX++;
		}
	}
	else if (PSELoadSrcDrop->SelectedIndex == 2)//PSE bintables
	{
		int Nnewpses = 0;
		for (int i = 0; i < ofd->FileNames->Length; i++)
		{
			array<String^>^ tables = FITSBinTable::GetAllExtensionNames(ofd->FileNames[i]);
			Nnewpses += tables->Length;
		}
		if (PSES == nullptr)
		{
			PSES = gcnew array<JPFITS::SourceExtractor^>(Nnewpses);
			PSESRECTS = gcnew array<array<Rectangle>^>(Nnewpses);
			PSESINDEX = 0;
			PSEDrop->Enabled = true;
		}
		else//add PSES
		{
			array<JPFITS::SourceExtractor^>^ temppses = gcnew array<JPFITS::SourceExtractor^>(PSES->Length + Nnewpses);
			array<array<Rectangle>^>^ temprecs = gcnew array<array<Rectangle>^>(PSES->Length + Nnewpses);
			for (int i = 0; i < PSES->Length; i++)
			{
				temppses[i] = PSES[i];
				temprecs[i] = PSESRECTS[i];
			}
			PSESINDEX = PSES->Length;
			PSES = temppses;
			PSESRECTS = temprecs;
		}

		for (int i = 0; i < ofd->FileNames->Length; i++)
		{
			array<String^>^ tables = FITSBinTable::GetAllExtensionNames(ofd->FileNames[i]);
			for (int j = 0; j < tables->Length; j++)
			{
				FITSBinTable^ bt = gcnew FITSBinTable(ofd->FileNames[i], tables[j]);
				PSES[PSESINDEX] = gcnew SourceExtractor(bt);
				MAKEPSERECTS();
				PSECOUNT++;
				PSEDrop->Items->Add(bt->ExtensionNameEXTNAME);
				if (j < PSES->Length - 1)
					PSESINDEX++;
			}
		}
	}
	
	PSETableViewBtn->Enabled = true;
	ShowPSEChck->Enabled = true;
	ShowPSEChck->Checked = true;
	PSEDropContextPlotAll->PerformClick();
}

void Form1::PSEPixelValLbl_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
	PSEPixelValLbl->Font = gcnew ::Font(PSEPixelValLbl->Font, ::FontStyle::Bold);
	PSEPixelCntLbl->Font = gcnew ::Font(PSEPixelCntLbl->Font, ::FontStyle::Bold);
}

void Form1::PSEPixelValLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	PSEPixelValLbl->Font = gcnew ::Font(PSEPixelValLbl->Font, ::FontStyle::Regular);
	PSEPixelCntLbl->Font = gcnew ::Font(PSEPixelCntLbl->Font, ::FontStyle::Regular);
}

void Form1::PSEPixelValLbl_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (((Label^)sender)->Text->Contains("SN"))
	{
		PSEPixelValLbl->Text = "Pixel Value:";
		PSEPixelCntLbl->Text = "Kernel Sum:";
	}
	else
	{
		PSEPixelValLbl->Text = "Pixel SN:";
		PSEPixelCntLbl->Text = "Kernel SN:";
	}
}

void Form1::PSETableViewBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (PSES == nullptr)
		return;

	if (WorldCoordinateSolution::Exists(IMAGESET[FILELISTINDEX], gcnew array<String^>(2) { "TAN", "TAN" }))
	{
		WCS = gcnew JPFITS::WorldCoordinateSolution();
		WCS->Get_WCS(IMAGESET[FILELISTINDEX]);
		PSES[PSESINDEX]->Generate_Source_RADec_Coords(WCS);
	}
	array<String^, 2>^ table = PSES[PSESINDEX]->Source_Table;

	PSETableViewer^ PSETABLEVIEWER = gcnew PSETableViewer();
	PSETABLEVIEWER->PSETable->ColumnCount = table->GetLength(0);
	PSETABLEVIEWER->PSETable->RowCount = table->GetLength(1) - 1;
	
	for (int i = 0; i < PSETABLEVIEWER->PSETable->ColumnCount; i++)
		PSETABLEVIEWER->PSETable->Columns[i]->HeaderText = table[i, 0];

	String^ strvalue = "";
	for (int i = 0; i < PSETABLEVIEWER->PSETable->ColumnCount; i++)
		for (int j = 0; j < PSETABLEVIEWER->PSETable->RowCount; j++)
		{
			strvalue = table[i, j + 1];
			if (JPMath::IsNumeric(strvalue))
				if (strvalue == "0")
					PSETABLEVIEWER->PSETable[i, j]->Value = 0.0;
				else
					PSETABLEVIEWER->PSETable[i, j]->Value = /*Convert::ToDouble(*/Convert::ToDouble(strvalue)/*.ToString("#.########"))*/;
			else
				PSETABLEVIEWER->PSETable[i, j]->Value = strvalue;
		}

	for (int j = 0; j < PSETABLEVIEWER->PSETable->RowCount; j++)
		PSETABLEVIEWER->PSETable->Rows[j]->HeaderCell->Value = (j + 1).ToString();

	PSETABLEVIEWER->Text = PSEDrop->Items[PSESINDEX] + " " + PSES[PSESINDEX]->LSFit_Equation;
	PSETABLEVIEWER->Show(this);
}

void Form1::PSEFitResultCntxtCopySelected_Click(System::Object^  sender, System::EventArgs^  e)
{
	Clipboard::SetText(PSEFitResultListBox->Text);
}

void Form1::PSEFitResultCntxtCopyAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ copy = "";
	bool removedj = false;
	for (int i = 0; i < PSEFitResultListBox->Items->Count; i++)
	{
		String^ line = (String^)PSEFitResultListBox->Items[i];
		for (int j = 0; j < line->Length; j++)
		{
			while (line->Substring(j, 1) == " ")
			{
				line = line->Remove(j, 1);
				removedj = true;
			}
			if (removedj)
				line = line->Insert(j, "	");
			removedj = false;
		}

		copy += line + "\r\n";
	}
	Clipboard::SetText(copy);
}

void Form1::PSEFitResultsCntxt_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	if (PSEFitResultListBox->SelectedIndex < 0)
		PSEFitResultCntxtCopySelected->Enabled = false;
	else
		PSEFitResultCntxtCopySelected->Enabled = true;
}

void Form1::WCSPlotSolutionPtsBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	bool cpexists = true;
	int n = 0;
	while (cpexists)
	{
		n++;
		if (IMAGESET[FILELISTINDEX]->GetKeyIndex("WCP1_" + n.ToString("000")) == -1)
			cpexists = false;
	}
	n--;

	if (n == 0)
	{
		MessageBox::Show("No WCS solution points found in header to plot...");
		return;
	}

	MARKCOORDRECTS = gcnew array<Rectangle>(n);
	MARKCOORDS = gcnew array<double, 2>(2, n);
	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	array<double>^ cp1 = gcnew array<double>(n);
	array<double>^ cp2 = gcnew array<double>(n);
	for (int i = 1; i <= n; i++)
	{
		cp1[i - 1] = Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("WCP1_" + i.ToString("000")));
		cp2[i - 1] = Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("WCP2_" + i.ToString("000")));
		MARKCOORDS[0, i - 1] = cp1[i - 1] - 1;
		MARKCOORDS[1, i - 1] = cp2[i - 1] - 1;
	}

	MAKEMARKCOORDRECTS();
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::WCSRefineSolutionBtn_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	
}

void Form1::WCSLoadSimbadAscii_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSRefineSolutionBtn->ShowDropDown();

	GET_CATALOGUE_NPTS((String^)WCSAutoCatalogueTxt->Tag, WCSAutoCatalogueExtensionTxt->Text, WCSAutoCatalogueCVAL1->Text, WCSAutoCatalogueCVAL2->Text, WCSAutoCatalogueMag->Text, Convert::ToInt32(WCSLoadListNPtsTxt->Text));

	WCS = gcnew JPFITS::WorldCoordinateSolution();
	WCS->Get_WCS(IMAGESET[FILELISTINDEX]);
	array<double>^ cp1 = gcnew array<double>(WCS_RA->Length);
	array<double>^ cp2 = gcnew array<double>(WCS_RA->Length);
	WCS->Get_Pixels(WCS_RA, WCS_DEC, "TAN", cp1, cp2, true);

	MARKCOORDS = gcnew array<double, 2>(2, WCS_RA->Length);
	for (int i = 0; i < WCS_RA->Length; i++)
	{
		MARKCOORDS[0, i] = cp1[i];
		MARKCOORDS[1, i] = cp2[i];
	}
	MAKEMARKCOORDRECTS();

	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::WCSListExciseToROI_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	array<bool>^ inside = gcnew array<bool>(MARKCOORDRECTS->Length);
	int n = 0;
	
	if (PSESeachROIOnlyChck->Checked)
	{
		if (PSEEllipticalROI->Checked)//elliptical ROI
		{
			SetReg("CCDLAB", "ROIX0", XSUBRANGE[SUBIMAGE_HWX]);
			SetReg("CCDLAB", "ROIY0", YSUBRANGE[SUBIMAGE_HWY]);
			SetReg("CCDLAB", "ROIXRad", SUBIMAGE_HWX);
			SetReg("CCDLAB", "ROIYRad", SUBIMAGE_HWY);
			ROIX0 = XSUBRANGE[SUBIMAGE_HWX];
			ROIY0 = YSUBRANGE[SUBIMAGE_HWY];
			ROIXRad = SUBIMAGE_HWX;
			ROIYRad = SUBIMAGE_HWY;

			ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);
			#pragma omp parallel for
			for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
			{
				double dx2 = double(x - ROIX0);
				dx2 *= dx2;
				dx2 /= double(ROIXRad * ROIXRad);
				for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
				{
					double dy2 = double(y - ROIY0);
					dy2 *= dy2;
					dy2 /= double(ROIYRad * ROIYRad);

					if (dx2 + dy2 <= 1)
						ROI_REGION[x, y] = true;
				}
			}
		}

		if (!PSEEllipticalROI->Checked && !PSEDrawROI->Checked)//either elliptical nor drawn...so just existing curusor box
		{
			ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);

			for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
				for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
					if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
						ROI_REGION[x, y] = true;
		}
	}

	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
		if (ROI_REGION[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]])
		{
			inside[i] = true;
			n++;
		}

	array<double, 2>^ temp = gcnew array<double, 2>(2, n);
	array<double>^ ratemp = gcnew array<double>(n);
	array<double>^ dectemp = gcnew array<double>(n);
	n = 0;
	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
		if (inside[i])
		{
			temp[0, n] = MARKCOORDS[0, i];
			temp[1, n] = MARKCOORDS[1, i];
			ratemp[n] = WCS_RA[i];
			dectemp[n] = WCS_DEC[i];
			n++;
		}

	WCS_RA = gcnew array<double>(n);
	WCS_DEC = gcnew array<double>(n);
	MARKCOORDS = gcnew array<double, 2>(2, n);
	for (int i = 0; i < n; i++)
	{
		WCS_RA[i] = ratemp[i];
		WCS_DEC[i] = dectemp[i];
		MARKCOORDS[0, i] = temp[0, i];
		MARKCOORDS[1, i] = temp[1, i];
	}
	MAKEMARKCOORDRECTS();

	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::WCSClarifyListSources_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	try
	{
		WCSMenu->ShowDropDown();
		AutoWCSMenuItem->ShowDropDown();
		WCSRefineSolutionBtn->ShowDropDown();

		array<bool>^ match = gcnew array<bool>(MARKCOORDRECTS->Length);
		int n = 0;

		for (int i = 0; i < MARKCOORDRECTS->Length; i++)
			if ((int)MARKCOORDS[0, i] > 0 && (int)MARKCOORDS[0, i] < IMAGESET[FILELISTINDEX]->Width && (int)MARKCOORDS[1, i] > 0 && (int)MARKCOORDS[1, i] < IMAGESET[FILELISTINDEX]->Height)
				if (PSES[PSESINDEX]->SourceBooleanMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] && PSES[PSESINDEX]->SourceIndexMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]] < PSES[PSESINDEX]->N_Sources)
				{
					n++;
					match[i] = true;
				}

		array<double>^ cp1 = gcnew array<double>(n);
		array<double>^ cp2 = gcnew array<double>(n);
		array<double>^ ratemp = gcnew array<double>(n);
		array<double>^ dectemp = gcnew array<double>(n);
		array<double, 2>^ temp = gcnew array<double, 2>(2, n);
		n = 0;
		for (int i = 0; i < MARKCOORDRECTS->Length; i++)
			if (match[i])
			{
				int ind = PSES[PSESINDEX]->SourceIndexMap[(int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i]];
				cp1[n] = PSES[PSESINDEX]->Centroids_X[ind];
				cp2[n] = PSES[PSESINDEX]->Centroids_Y[ind];
				ratemp[n] = WCS_RA[i];
				dectemp[n] = WCS_DEC[i];
				temp[0, n] = MARKCOORDS[0, i];
				temp[1, n] = MARKCOORDS[1, i];
				n++;
			}

		PSES[PSESINDEX] = gcnew JPFITS::SourceExtractor(cp1, cp2);
		PSESRECTS = gcnew array<array<Rectangle>^>(1);
		MAKEPSERECTS();

		WCS_RA = gcnew array<double>(n);
		WCS_DEC = gcnew array<double>(n);
		MARKCOORDS = gcnew array<double, 2>(2, n);
		for (int i = 0; i < n; i++)
		{
			WCS_RA[i] = ratemp[i];
			WCS_DEC[i] = dectemp[i];
			MARKCOORDS[0, i] = temp[0, i];
			MARKCOORDS[1, i] = temp[1, i];
		}
		MAKEMARKCOORDRECTS();

		PSEFitResultListBox->Items->Clear();
		PSEFitResultListBox->Items->Add(String::Concat("N:   ", PSES[PSESINDEX]->N_Sources));
		ImageWindow->Refresh();
		SubImageWindow->Refresh();
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}
}

void Form1::WCSSolveList_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	WCS = gcnew JPFITS::WorldCoordinateSolution();
	WCS->Solve_WCS("TAN", PSES[PSESINDEX]->Centroids_X, PSES[PSESINDEX]->Centroids_Y, true, WCS_RA, WCS_DEC, IMAGESET[FILELISTINDEX]);
	FileTxtsUpD();
	array<double>^ x = gcnew array<double>(MARKCOORDRECTS->Length);
	array<double>^ y = gcnew array<double>(MARKCOORDRECTS->Length);
	WCS->Get_Pixels(WCS_RA, WCS_DEC, "TAN", x, y, true);

	MARKCOORDS = gcnew array<double, 2>(2, x->Length);
	for (int i = 0; i < x->Length; i++)
	{
		MARKCOORDS[0, i] = x[i];
		MARKCOORDS[1, i] = y[i];
	}
	MAKEMARKCOORDRECTS();

	SHOW_WCSCOORDS = true;
	WCSRADecShowChck->Checked = true;
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::testbtnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){}

void Form1::WCSAutoSolveBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	WCSMenu->HideDropDown();
	AutoWCSMenuItem->HideDropDown();

	SetReg("CCDLAB", "PSEWidth", PSEKernelRadUpD->Value.ToString());
	SetReg("CCDLAB", "PSESeparation", PSESeparationUpD->Value.ToString());

	if (Convert::ToDouble(WCSScaleInitLB->Text) > Convert::ToDouble(WCSScaleInit->Text) || Convert::ToDouble(WCSScaleInitUB->Text) < Convert::ToDouble(WCSScaleInit->Text))
	{
		WCSMenu->ShowDropDown();
		AutoWCSMenuItem->ShowDropDown();
		MessageBox::Show("Problem with your initial scale settings...", "Error...");
		return;
	}

	if (Convert::ToDouble(WCSRotationInitLB->Text) > Convert::ToDouble(WCSRotationInit->Text) || Convert::ToDouble(WCSRotationInitUB->Text) < Convert::ToDouble(WCSRotationInit->Text))
	{
		WCSMenu->ShowDropDown();
		AutoWCSMenuItem->ShowDropDown();
		MessageBox::Show("Problem with your initial rotation settings...", "Error...");
		return;
	}

	if (PSESeachROIOnlyChck->Checked)
	{
		if (PSEEllipticalROI->Checked)//elliptical ROI
		{
			SetReg("CCDLAB", "ROIX0", XSUBRANGE[SUBIMAGE_HWX]);
			SetReg("CCDLAB", "ROIY0", YSUBRANGE[SUBIMAGE_HWY]);
			SetReg("CCDLAB", "ROIXRad", SUBIMAGE_HWX);
			SetReg("CCDLAB", "ROIYRad", SUBIMAGE_HWY);
			ROIX0 = XSUBRANGE[SUBIMAGE_HWX];
			ROIY0 = YSUBRANGE[SUBIMAGE_HWY];
			ROIXRad = SUBIMAGE_HWX;
			ROIYRad = SUBIMAGE_HWY;

			ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);
			#pragma omp parallel for
			for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
			{
				double dx2 = double(x - ROIX0);
				dx2 *= dx2;
				dx2 /= double(ROIXRad * ROIXRad);
				for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
				{
					double dy2 = double(y - ROIY0);
					dy2 *= dy2;
					dy2 /= double(ROIYRad * ROIYRad);

					if (dx2 + dy2 <= 1)
						ROI_REGION[x, y] = true;
				}
			}
		}

		if (!PSEEllipticalROI->Checked && !PSEDrawROI->Checked)//either elliptical nor drawn...so just existing curusor box
		{
			ROI_REGION = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);

			for (int x = 0; x < IMAGESET[FILELISTINDEX]->Width; x++)
				for (int y = 0; y < IMAGESET[FILELISTINDEX]->Height; y++)
					if (x >= XSUBRANGE[0] && x <= XSUBRANGE[SUBIMAGE_HWX * 2] && y >= YSUBRANGE[0] && y <= YSUBRANGE[SUBIMAGE_HWY * 2])
						ROI_REGION[x, y] = true;
		}
	}

	if (!WCSAutoExternalDLLChck->Checked)
	{
		if (Convert::ToInt32(WCSAutoNCatPtsTxt->Text) > 18 && WCSAutoDisplayChck->Checked)
		{
			if (MessageBox::Show("Too many points for serial display process. \r\r" + "Proceed without display?", "Warning", MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;

			//else yes
			WCSAutoDisplayChck->Checked = false;
			WCSAutoSolveBtn->PerformClick();
			return;
		}

		if (WCSAutoSolveBtn->Text == "Cancel")
		{
			WCSAUTOCANCEL = true;
			WCSAutoSolveBtn->Text = "Solve";
			return;
		}
		WCSAutoSolveBtn->Text = "Cancel";
		WCSAUTOCANCEL = false;
		ProgressBar->Maximum = 100;

		WCSAutoBGWrkr->RunWorkerAsync();
	}
	else//use external DLL
	{
		WCSAS = gcnew JPFITS::WCS_AutoSolver("TAN", Convert::ToInt32(WCSAutoNCatPtsTxt->Text), IMAGESET[FILELISTINDEX], ROI_REGION, (double)PSESaturationUpD->Value, PSEAutoBackgroundChck->Checked, (int)PSEKernelRadUpD->Value, (int)PSESeparationUpD->Value, (String^)WCSAutoCatalogueTxt->Tag, WCSAutoCatalogueExtensionTxt->Text, WCSAutoCatalogueCVAL1->Text, WCSAutoCatalogueCVAL2->Text, WCSAutoCatalogueMag->Text, WCSAutoRefineChck->Checked);
		WCSAS->SolveAsync(Convert::ToDouble(WCSScaleInit->Text), Convert::ToDouble(WCSScaleInitLB->Text), Convert::ToDouble(WCSScaleInitUB->Text), Convert::ToDouble(WCSRotationInit->Text), Convert::ToDouble(WCSRotationInitLB->Text), Convert::ToDouble(WCSRotationInitUB->Text), 0.25, Convert::ToInt32(WCSAutoStopNMatchesText->Text), Convert::ToInt32(WCSAutoStopPercMatchesText->Text), WCSAutoConditionArraysChck->Checked, true);

		if (!WCSAS->Cancelled && WCSAS->Solved)
		{
			FileTxtsUpD();
			WCSRADecShowChck->Checked = false;
			WCSRADecShowChck->PerformClick();
		}
	}
}

void Form1::WCSAutoBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	POLYPOINTS = nullptr;
	POLYPOINTS2 = nullptr;
	PSESRECTS = nullptr;
	MARKCOORDRECTS = nullptr;
	WCSRADecShowChck->Checked = false;
	SHOW_WCSCOORDS = false;
	ImageWindow->Refresh();

	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	int nCATpts = Convert::ToInt32(WCSAutoNCatPtsTxt->Text);
	int nPSEpts_min = nCATpts - 1, nPSEpts_max = nCATpts;
	double scale_init = Convert::ToDouble(WCSScaleInit->Text) / 3600 * Math::PI / 180;
	double scale_lb = Convert::ToDouble(WCSScaleInitLB->Text) / 3600 * Math::PI / 180;
	double scale_ub = Convert::ToDouble(WCSScaleInitUB->Text) / 3600 * Math::PI / 180;
	double rotat_init = Convert::ToDouble(WCSRotationInit->Text) * Math::PI / 180;
	double rotat_lb = Convert::ToDouble(WCSRotationInitLB->Text) * Math::PI / 180;
	double rotat_ub = Convert::ToDouble(WCSRotationInitUB->Text) * Math::PI / 180;
	double vertextol = Convert::ToDouble(WCSAutoVertexToleranceTxt->Text) * Math::PI / 180;
	bool do_parallel = !WCSAutoDisplayChck->Checked;
	String^ catfilename = (String^)WCSAutoCatalogueTxt->Tag;
	String^ catCVAL1 = WCSAutoCatalogueCVAL1->Text;
	String^ catCVAL2 = WCSAutoCatalogueCVAL2->Text;
	String^ catExtension = WCSAutoCatalogueExtensionTxt->Text;
	String^ catMag = WCSAutoCatalogueMag->Text;
	int stopNpts = Convert::ToInt32(WCSAutoStopNMatchesText->Text);
	int stopPercpts = Convert::ToInt32(WCSAutoStopPercMatchesText->Text);

	//get catalogue RA, Dec, and mag's, and sort by mags
	if (!File::Exists(catfilename))
	{
		MessageBox::Show("Cannot find catalogue file:\r\r" + catfilename + "\r\rDoes not exist.", "Error...");
		return;
	}
	
	array<double>^ ra;
	array<double>^ dec;
	array<double>^ mag;
	try
	{
		JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(catfilename, catExtension);
		ra = bt->GetTTYPEEntry(catCVAL1);
		dec = bt->GetTTYPEEntry(catCVAL2);
		mag = bt->GetTTYPEEntry(catMag);
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Message);
	}

	/*array<double>^ ra = JPFITS::FITSBinTable::GetExtensionEntry(catfilename, catExtension, catCVAL1);
	array<double>^ dec = JPFITS::FITSBinTable::GetExtensionEntry(catfilename, catExtension, catCVAL2);
	array<double>^ mag = JPFITS::FITSBinTable::GetExtensionEntry(catfilename, catExtension, catMag);*/

	//need to check mag for NaN's and re-form ra dec mag
	ArrayList^ ralist = gcnew ArrayList(ra->Length);
	ArrayList^ declist = gcnew ArrayList(ra->Length);
	ArrayList^ maglist = gcnew ArrayList(ra->Length);
	#pragma omp parallel for
	for (int i = 0; i < mag->Length; i++)
	{
		if (Double::IsNaN(mag[i]))
			continue;

		#pragma omp critical
		{
			ralist->Add(ra[i]);
			declist->Add(dec[i]);
			maglist->Add(mag[i]);
		}
	}
	#pragma omp parallel for
	for (int i = 0; i < ralist->Count; i++)
	{
		ra[i] = (double)ralist[i];
		dec[i] = (double)declist[i];
		mag[i] = (double)maglist[i];
	}
	Array::Resize(ra, ralist->Count);
	Array::Resize(dec, ralist->Count);
	Array::Resize(mag, ralist->Count);

	//sort the catalogue list by magnitude
	array<double>^ keysref = gcnew array<double>(mag->Length);
	Array::Copy(mag, keysref, mag->Length);
	Array::Sort(mag, ra);
	Array::Copy(keysref, mag, mag->Length);
	Array::Sort(mag, dec);

	//get the brightest few catlaogue points
	array<JPMath::PointD^>^ CATpts = gcnew array<JPMath::PointD^>(nCATpts);
	double crval1 = 0, crval2 = 0;
	for (int i = 0; i < CATpts->Length; i++)
	{
		CATpts[i] = gcnew JPMath::PointD(ra[i], dec[i], mag[i]);
		crval1 += CATpts[i]->X;
		crval2 += CATpts[i]->Y;
	}
	crval1 /= (double)CATpts->Length;//the reference value can be the mean
	crval2 /= (double)CATpts->Length;//the reference value can be the mean

	//convert the catalogue points to intermediate points
	array<JPMath::PointD^>^ CATpts_intrmdt = gcnew array<JPMath::PointD^>(nCATpts);
	double a0 = crval1 * Math::PI / 180, d0 = crval2 * Math::PI / 180;
	for (int i = 0; i < CATpts_intrmdt->Length; i++)
	{
		double a = CATpts[i]->X * Math::PI / 180;//radians
		double d = CATpts[i]->Y * Math::PI / 180;//radians

		//for tangent plane Gnomic
		double xint = Math::Cos(d)*Math::Sin(a - a0) / (Math::Cos(d0)*Math::Cos(d)*Math::Cos(a - a0) + Math::Sin(d0)*Math::Sin(d));
		double yint = (Math::Cos(d0)*Math::Sin(d) - Math::Cos(d)*Math::Sin(d0)*Math::Cos(a - a0)) / (Math::Sin(d0)*Math::Sin(d) + Math::Cos(d0)*Math::Cos(d)*Math::Cos(a - a0));

		CATpts_intrmdt[i] = gcnew JPMath::PointD(xint, yint, CATpts[i]->Value);
	}

	//make intermediate coordinate triangles
	int nCATtriangles = CATpts_intrmdt->Length * (CATpts_intrmdt->Length - 1) * (CATpts_intrmdt->Length - 2) / 6;
	array<JPMath::Triangle^>^ CATtriangles_intrmdt = gcnew array<JPMath::Triangle^>(nCATtriangles);
	int c = 0;
	for (int i = 0; i < CATpts_intrmdt->Length - 2; i++)
		for (int j = i + 1; j < CATpts_intrmdt->Length - 1; j++)
			for (int k = j + 1; k < CATpts_intrmdt->Length; k++)
			{
				CATtriangles_intrmdt[c] = gcnew JPMath::Triangle(CATpts_intrmdt[i], CATpts_intrmdt[j], CATpts_intrmdt[k]);
				c++;
			}

	//get PSE image sources
	ShowPSEChck->Checked = true;
	ShowPSEChck->Enabled = true;
	PSES = gcnew array<JPFITS::SourceExtractor^>(1) { gcnew JPFITS::SourceExtractor() };
	PSESINDEX = 0;
	PSESRECTS = gcnew array<array<Rectangle>^>(1);
	double immax = IMAGESET[FILELISTINDEX]->Max;//assume bg subtracted
	double pixthresh = immax / 32;
	double div = 2;
	double amp = pixthresh;
	int PSEiters = 0;
	int maxPSEiters = 15;
	double pix_sat = (double)PSESaturationUpD->Value;
	while (PSES[PSESINDEX]->N_Sources < nPSEpts_min || PSES[PSESINDEX]->N_Sources > nPSEpts_max)
	{
		PSEiters++;
		if (PSEiters > maxPSEiters)
			break;

		if (PSES[PSESINDEX]->N_SaturatedSources >= nPSEpts_max || PSES[PSESINDEX]->N_Sources >= nPSEpts_max)
			break;

		PSES[PSESINDEX]->Extract_Sources(IMAGESET[FILELISTINDEX]->Image, pix_sat, pixthresh, Double::MaxValue, 0, Double::MaxValue, false, (int)PSEKernelRadUpD->Value, (int)PSESeparationUpD->Value, PSEAutoBackgroundChck->Checked, nullptr, ROI_REGION, false);
		MAKEPSERECTS();
		ImageWindow->Refresh();
		SubImageWindow->Refresh();

		if (PSES[PSESINDEX]->N_Sources < nPSEpts_min)
			pixthresh -= amp / div;
		if (PSES[PSESINDEX]->N_Sources > nPSEpts_max)
			pixthresh += amp / div;
		div *= 2;
	}
	if (PSES[PSESINDEX]->N_Sources > nPSEpts_max)
	{
		PSES[PSESINDEX]->ClipToNBrightest(nPSEpts_max);
		MAKEPSERECTS();
		ImageWindow->Refresh();
		SubImageWindow->Refresh();
	}

	//turn the PSE results into points
	array<JPMath::PointD^>^ PSEpts = gcnew array<JPMath::PointD^>(PSES[PSESINDEX]->N_Sources);
	double crpix1_init = 0, crpix2_init = 0, crpix1_lb = Double::MaxValue, crpix1_ub = Double::MinValue, crpix2_lb = Double::MaxValue, crpix2_ub = Double::MinValue;
	for (int i = 0; i < PSEpts->Length; i++)
	{
		PSEpts[i] = gcnew JPMath::PointD(IMAGESET[FILELISTINDEX]->Width - 1 - PSES[PSESINDEX]->Centroids_X[i], IMAGESET[FILELISTINDEX]->Height - 1 - PSES[PSESINDEX]->Centroids_Y[i], PSES[PSESINDEX]->Centroids_Volume[i]);
		crpix1_init += PSEpts[i]->X;
		crpix2_init += PSEpts[i]->Y;
		if (crpix1_ub < PSEpts[i]->X)
			crpix1_ub = PSEpts[i]->X;
		if (crpix1_lb > PSEpts[i]->X)
			crpix1_lb = PSEpts[i]->X;
		if (crpix2_ub < PSEpts[i]->Y)
			crpix2_ub = PSEpts[i]->Y;
		if (crpix2_lb > PSEpts[i]->Y)
			crpix2_lb = PSEpts[i]->Y;
	}
	crpix1_init /= (double)PSEpts->Length;//the reference value initial guesses can be the means
	crpix2_init /= (double)PSEpts->Length;

	//make PSE triangles
	int nPSEtriangles = PSEpts->Length * (PSEpts->Length - 1) * (PSEpts->Length - 2) / 6;
	array<JPMath::Triangle^>^ PSEtriangles = gcnew array<JPMath::Triangle^>(nPSEtriangles);
	c = 0;
	for (int i = 0; i < PSEpts->Length - 2; i++)
		for (int j = i + 1; j < PSEpts->Length - 1; j++)
			for (int k = j + 1; k < PSEpts->Length; k++)
			{
				PSEtriangles[c] = gcnew JPMath::Triangle(PSEpts[i], PSEpts[j], PSEpts[k]);

				if (!do_parallel)
				{
					if (WCSAUTOCANCEL)
						break;
					POLYPOINTS = gcnew array<System::Drawing::Point>(3);
					POLYPOINTS[0] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - PSEtriangles[c]->Vertex[0]->X - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - PSEtriangles[c]->Vertex[0]->Y - 0.5) * ysc));
					POLYPOINTS[1] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - PSEtriangles[c]->Vertex[1]->X - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - PSEtriangles[c]->Vertex[1]->Y - 0.5) * ysc));
					POLYPOINTS[2] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - PSEtriangles[c]->Vertex[2]->X - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - PSEtriangles[c]->Vertex[2]->Y - 0.5) * ysc));
					ImageWindow->Refresh();
				}
				c++;
			}

	POLYPOINTS = nullptr;
	if (!do_parallel)
		ImageWindow->Refresh();

	if (WCSAUTOCANCEL)
		return;

	if (do_parallel)
		if (WCSAutoConditionArraysChck->Checked)
		{
			PSEtriangles = JPFITS::WCS_AutoSolver::ConditionTriangleArrayBrightnessThreads(PSEtriangles, omp_get_max_threads(), false);
			CATtriangles_intrmdt = JPFITS::WCS_AutoSolver::ConditionTriangleArrayBrightnessThreads(CATtriangles_intrmdt, 1, true);
		}

	//for each PSE triangle, fit it to a CAT intermediate triangle, and then check if this fit satisfies the other CAT points to the PSE points
	//rotation transformation p[0] = scale; p[1] = phi (radians); p[2] = x-axis coordinate reference; p[3] = y-axis coordinate reference;
	array<double>^ plb = gcnew array<double>(4) { scale_lb, rotat_lb, crpix1_lb, crpix2_lb };
	array<double>^ pub = gcnew array<double>(4) { scale_ub, rotat_ub, crpix1_ub, crpix2_ub };
	array<double>^ psc = gcnew array<double>(4) { scale_init, 1, Math::Abs(crpix1_init), Math::Abs(crpix2_init) };
	POLYPOINTS = gcnew array<System::Drawing::Point>(3);
	POLYPOINTS2 = gcnew array<System::Drawing::Point>(3);

	double kern_diam = double(2 * PSEKernelRadUpD->Value) + 1;
	double p00, p01, p02, p03;
	int total_pt_matches;
	DATE = DateTime::Now;
	TimeSpan ts;
	bool solution = false;
	int prog = 0, threadnum = 0;
	unsigned __int64 ncompares = 0, nfalse_sols = 0;
	bool compare_fieldvectors = rotat_lb != -Math::PI && rotat_ub != Math::PI;

	#pragma omp parallel for reduction(+:ncompares, nfalse_sols) if(do_parallel)
	for (int i = 0; i < PSEtriangles->Length; i++)
	{
		if (solution)
			break;
		if (WCSAUTOCANCEL)
			break;

		if (i < PSEtriangles->Length / omp_get_num_threads())
			if (omp_get_num_threads() * i * 100 / PSEtriangles->Length > prog)
			{
				prog++;
				WCSAutoBGWrkr->ReportProgress(1);
			}

		//create these here so that each thread when parallel has own copy
		array<double>^ xpix_triplet = gcnew array<double>(3);
		array<double>^ ypix_triplet = gcnew array<double>(3);
		xpix_triplet[0] = PSEtriangles[i]->Vertex[0]->X;
		ypix_triplet[0] = PSEtriangles[i]->Vertex[0]->Y;
		xpix_triplet[1] = PSEtriangles[i]->Vertex[1]->X;
		ypix_triplet[1] = PSEtriangles[i]->Vertex[1]->Y;
		xpix_triplet[2] = PSEtriangles[i]->Vertex[2]->X;
		ypix_triplet[2] = PSEtriangles[i]->Vertex[2]->Y;

		if (!do_parallel)
		{
			POLYPOINTS[0] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - xpix_triplet[0] - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - ypix_triplet[0] - 0.5) * ysc));
			POLYPOINTS[1] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - xpix_triplet[1] - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - ypix_triplet[1] - 0.5) * ysc));
			POLYPOINTS[2] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - xpix_triplet[2] - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - ypix_triplet[2] - 0.5) * ysc));
			ImageWindow->Refresh();
		}

		//create these here so that each thread when parallel has own copy
		array<double>^ Xintrmdt_triplet = gcnew array<double>(3);
		array<double>^ Yintrmdt_triplet = gcnew array<double>(3);
		array<double>^ P0 = gcnew array<double>(4);
		//double minlength0 = scale_lb * (PSEtriangles[i]->SideLength[0] - kern_diam);//redundant as per below
		//double maxlength0 = scale_ub * (PSEtriangles[i]->SideLength[0] + kern_diam);//redundant as per below
		//double minlength1 = scale_lb * (PSEtriangles[i]->SideLength[1] - kern_diam);//redundant as per below
		//double maxlength1 = scale_ub * (PSEtriangles[i]->SideLength[1] + kern_diam);//redundant as per below
		double minlength2 = scale_lb * (PSEtriangles[i]->SideLength[2] - kern_diam);
		double maxlength2 = scale_ub * (PSEtriangles[i]->SideLength[2] + kern_diam);

		for (int j = 0; j < CATtriangles_intrmdt->Length; j++)
		{
			if (solution)
				break;
			if (WCSAUTOCANCEL)
				break;

			ncompares++;

			if (Math::Abs(PSEtriangles[i]->VertexAngle[0] - CATtriangles_intrmdt[j]->VertexAngle[0]) > vertextol)
				continue;
			if (Math::Abs(PSEtriangles[i]->VertexAngle[1] - CATtriangles_intrmdt[j]->VertexAngle[1]) > vertextol)
				continue;
			/*if (Math::Abs(PSEtriangles[i]->VertexAngle[2] - CATtriangles_intrmdt[j]->VertexAngle[2]) > vertextol)
				continue;

				these are redundant

			if (CATtriangles_intrmdt[j]->SideLength[0] <  minlength0 || CATtriangles_intrmdt[j]->SideLength[0] > maxlength0)
				continue;
			if (CATtriangles_intrmdt[j]->SideLength[1] < minlength1 || CATtriangles_intrmdt[j]->SideLength[1] > maxlength1)
				continue;*/
			if (CATtriangles_intrmdt[j]->SideLength[2] < minlength2 || CATtriangles_intrmdt[j]->SideLength[2] > maxlength2)
				continue;

			if (compare_fieldvectors)
			{
				double theta = Math::Atan2(PSEtriangles[i]->FieldVector->X * CATtriangles_intrmdt[j]->FieldVector->Y - PSEtriangles[i]->FieldVector->Y * CATtriangles_intrmdt[j]->FieldVector->X, PSEtriangles[i]->FieldVector->X * CATtriangles_intrmdt[j]->FieldVector->X + PSEtriangles[i]->FieldVector->Y * CATtriangles_intrmdt[j]->FieldVector->Y);
				
				if (theta > rotat_ub || theta < rotat_lb)
					continue;
			}

			Xintrmdt_triplet[0] = CATtriangles_intrmdt[j]->Vertex[0]->X;
			Yintrmdt_triplet[0] = CATtriangles_intrmdt[j]->Vertex[0]->Y;
			Xintrmdt_triplet[1] = CATtriangles_intrmdt[j]->Vertex[1]->X;
			Yintrmdt_triplet[1] = CATtriangles_intrmdt[j]->Vertex[1]->Y;
			Xintrmdt_triplet[2] = CATtriangles_intrmdt[j]->Vertex[2]->X;
			Yintrmdt_triplet[2] = CATtriangles_intrmdt[j]->Vertex[2]->Y;

			//made it here, now do a fit
			//reset P0 for j'th iteration
			P0[0] = scale_init;
			P0[1] = rotat_init;
			P0[2] = crpix1_init;
			P0[3] = crpix2_init;
			JPMath::Fit_WCSTransform2d(Xintrmdt_triplet, Yintrmdt_triplet, xpix_triplet, ypix_triplet, P0, plb, pub, psc);

			int N_pt_matches = 0;
			for (int k = 0; k < 3; k++)
			{
				int x = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / P0[0] * (Math::Cos(-P0[1]) * Xintrmdt_triplet[k] - Math::Sin(-P0[1]) * Yintrmdt_triplet[k]) + P0[2]));
				int y = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / P0[0] * (Math::Sin(-P0[1]) * Xintrmdt_triplet[k] + Math::Cos(-P0[1]) * Yintrmdt_triplet[k]) + P0[3]));
				if (!do_parallel)
					POLYPOINTS2[k] = System::Drawing::Point(int((x + 0.5) * xsc), int((y + 0.5) * ysc));

				if (x > 0 && y > 0 && x < IMAGESET[FILELISTINDEX]->Width && y < IMAGESET[FILELISTINDEX]->Height && PSES[PSESINDEX]->SourceIndexMap[x, y] == PSES[PSESINDEX]->SourceIndexMap[IMAGESET[FILELISTINDEX]->Width - 1 - (int)Math::Round(xpix_triplet[k]), IMAGESET[FILELISTINDEX]->Height - 1 - (int)Math::Round(ypix_triplet[k])])
					N_pt_matches++;
			}
			if (!do_parallel)
				ImageWindow->Refresh();

			if (N_pt_matches != 3)//not a possible solution
				continue;

			//if (!solution)
			{
				//#pragma omp critical
				{
					if (!solution)
					{
						if (do_parallel)
						{
							for (int k = 0; k < 3; k++)
							{
								double x = (double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / P0[0] * (Math::Cos(-P0[1]) * Xintrmdt_triplet[k] - Math::Sin(-P0[1]) * Yintrmdt_triplet[k]) + P0[2]);
								double y = (double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / P0[0] * (Math::Sin(-P0[1]) * Xintrmdt_triplet[k] + Math::Cos(-P0[1]) * Yintrmdt_triplet[k]) + P0[3]);
								POLYPOINTS2[k] = System::Drawing::Point(int((x + 0.5) * xsc), int((y + 0.5) * ysc));
								POLYPOINTS[k] = System::Drawing::Point(int((IMAGESET[FILELISTINDEX]->Width - 1 - xpix_triplet[k] - 0.5) * xsc), int((IMAGESET[FILELISTINDEX]->Height - 1 - ypix_triplet[k] - 0.5) * ysc));
							}
							ImageWindow->Refresh();
						}
						else
						{
							POLYPOINTSb = gcnew array<Drawing::Point>(POLYPOINTS->Length);
							POLYPOINTS2b = gcnew array<Drawing::Point>(POLYPOINTS2->Length);
							Array::Copy(POLYPOINTS, POLYPOINTSb, POLYPOINTS->Length);
							Array::Copy(POLYPOINTS2, POLYPOINTS2b, POLYPOINTS2->Length);
						}

						//need to check if the other CAT points match the PSE pts
						N_pt_matches = 0;
						for (int k = 0; k < CATpts_intrmdt->Length; k++)
						{
							double x_int = CATpts_intrmdt[k]->X;
							double y_int = CATpts_intrmdt[k]->Y;

							int x_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / P0[0] * (Math::Cos(-P0[1]) * x_int - Math::Sin(-P0[1]) * y_int) + P0[2]));
							int y_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / P0[0] * (Math::Sin(-P0[1]) * x_int + Math::Cos(-P0[1]) * y_int) + P0[3]));

							if (x_pix > 0 && y_pix > 0 && x_pix < IMAGESET[FILELISTINDEX]->Width && y_pix < IMAGESET[FILELISTINDEX]->Height && PSES[PSESINDEX]->SourceBooleanMap[x_pix, y_pix])
								N_pt_matches++;
						}

						if (N_pt_matches >= stopNpts || N_pt_matches * 100 / CATpts_intrmdt->Length >= stopPercpts)
						{
							solution = true;
							ts = DateTime::Now - DATE;
							total_pt_matches = N_pt_matches;
							p00 = P0[0];
							p01 = P0[1];
							p02 = P0[2];
							p03 = P0[3];
							threadnum = omp_get_thread_num();
						}
						else
							nfalse_sols++;
					}
				}
			}
		}
	}
	if (!do_parallel)
	{
		POLYPOINTS = POLYPOINTSb;
		POLYPOINTS2 = POLYPOINTS2b;
	}

	if (!solution || WCSAUTOCANCEL)
	{
		POLYPOINTS = nullptr;
		POLYPOINTS2 = nullptr;
		PSESRECTS = nullptr;
		MARKCOORDRECTS = nullptr;
		ImageWindow->Refresh();
		if (WCSAUTOCANCEL)
			MessageBox::Show("Cancelled...");
		else if (!solution)
			MessageBox::Show("No solution...");
		return;
	}

	MARKCOORDS = gcnew array<double, 2>(2, total_pt_matches);
	WCS_RA = gcnew array<double>(total_pt_matches);
	WCS_DEC = gcnew array<double>(total_pt_matches);
	array<double>^ xpix_matches = gcnew array<double>(total_pt_matches);
	array<double>^ ypix_matches = gcnew array<double>(total_pt_matches);
	c = 0;
	for (int k = 0; k < CATpts_intrmdt->Length; k++)
	{
		double x_intrmdt = CATpts_intrmdt[k]->X;
		double y_intrmdt = CATpts_intrmdt[k]->Y;

		int x_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / p00 * (Math::Cos(-p01) * x_intrmdt - Math::Sin(-p01) * y_intrmdt) + p02));
		int y_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / p00 * (Math::Sin(-p01) * x_intrmdt + Math::Cos(-p01) * y_intrmdt) + p03));

		if (x_pix > 0 && y_pix > 0 && x_pix < IMAGESET[FILELISTINDEX]->Width && y_pix < IMAGESET[FILELISTINDEX]->Height && PSES[PSESINDEX]->SourceBooleanMap[x_pix, y_pix])
		{
			int index = PSES[PSESINDEX]->SourceIndexMap[x_pix, y_pix];
			xpix_matches[c] = PSES[PSESINDEX]->Centroids_X[index];
			ypix_matches[c] = PSES[PSESINDEX]->Centroids_Y[index];
			WCS_RA[c] = CATpts[k]->X;
			WCS_DEC[c] = CATpts[k]->Y;
			MARKCOORDS[0, c] = x_pix;
			MARKCOORDS[1, c] = y_pix;
			c++;
		}
	}

	MAKEMARKCOORDRECTS();
	PSES[PSESINDEX] = gcnew JPFITS::SourceExtractor(xpix_matches, ypix_matches);
	MAKEPSERECTS();
	WCSSolveList->PerformClick();

	::DialogResult res = MessageBox::Show("Scale: " + Math::Round(p00 * 180 / Math::PI * 3600, 4) + ";\rRotation: " + Math::Round(p01 * 180 / Math::PI, 3) + ";\rN Pt. Matches: " + total_pt_matches + " (" + (total_pt_matches * 100 / CATpts_intrmdt->Length).ToString("00.0") + "%)" + ";\rN_Comparisons: " + ncompares.ToString("0.00e00") + " (" + Math::Round(double(ncompares * 100) / double(PSEtriangles->Length) / double(CATtriangles_intrmdt->Length), 1) + "%)" + ";\rN_False: " + nfalse_sols + ";\rThread: " + threadnum + ";\rCompleted in: " + ts.Minutes.ToString() + "m" + (double(ts.Seconds) + (double)ts.Milliseconds / 1000).ToString() + "s" + ";\rComparison per Second: " + (ncompares / ts.TotalSeconds).ToString("0.00e00") + ";\r\rClear Solution Points?", "Finished...", MessageBoxButtons::YesNo);
	if (res == ::DialogResult::Yes)
	{
		POLYPOINTS = nullptr;
		POLYPOINTS2 = nullptr;
		PSESRECTS = nullptr;
		MARKCOORDRECTS = nullptr;
		ImageWindow->Refresh();
	}

	POLYPOINTS = nullptr;
	POLYPOINTS2 = nullptr;
	ImageWindow->Refresh();
	
	if (WCSAutoRefineChck->Checked)
	{
		PSES = gcnew array<JPFITS::SourceExtractor^>(1) { gcnew JPFITS::SourceExtractor() };
		PSESINDEX = 0;
		immax = IMAGESET[FILELISTINDEX]->Max;//assume bg subtracted
		pixthresh = immax / 32;
		div = 2;
		amp = pixthresh;
		nPSEpts_min = Convert::ToInt32(WCSAutoRefineNPtsTxt->Text) - 1;
		nPSEpts_max = Convert::ToInt32(WCSAutoRefineNPtsTxt->Text);
		WCSLoadListNPtsTxt->Text = (nPSEpts_max * 2).ToString();
		PSEiters = 0;

		while (PSES[PSESINDEX]->N_Sources < nPSEpts_min || PSES[PSESINDEX]->N_Sources > nPSEpts_max)
		{
			PSEiters++;
			if (PSEiters > maxPSEiters)
				break;

			if (PSES[PSESINDEX]->N_SaturatedSources >= nPSEpts_max || PSES[PSESINDEX]->N_Sources >= nPSEpts_max)
				break;

			PSES = gcnew array<JPFITS::SourceExtractor^>(1) { gcnew JPFITS::SourceExtractor() };
			PSES[PSESINDEX]->Extract_Sources(IMAGESET[FILELISTINDEX]->Image, pix_sat, pixthresh, Double::MaxValue, 0, Double::MaxValue, false, (int)PSEKernelRadUpD->Value, (int)PSESeparationUpD->Value, PSEAutoBackgroundChck->Checked, "", ROI_REGION, false);
			PSESRECTS = gcnew array<array<Rectangle>^>(1);
			MAKEPSERECTS();
			ImageWindow->Refresh();
			SubImageWindow->Refresh();

			if (PSES[PSESINDEX]->N_Sources < nPSEpts_min)
				pixthresh -= amp / div;
			if (PSES[PSESINDEX]->N_Sources > nPSEpts_max)
				pixthresh += amp / div;
			div *= 2;
		}
		if (PSES[PSESINDEX]->N_Sources > nPSEpts_max)
		{
			PSES[PSESINDEX]->ClipToNBrightest(nPSEpts_max);
			PSESRECTS = gcnew array<array<Rectangle>^>(1);
			MAKEPSERECTS();
			ImageWindow->Refresh();
			SubImageWindow->Refresh();
		}
		WCSLoadSimbadAscii_Click(sender, e);
		WCSClarifyListSources->PerformClick();
		WCSSolveList->PerformClick();
		::DialogResult res = MessageBox::Show(PSES[PSESINDEX]->N_Sources + " sources of " + WCSAutoRefineNPtsTxt->Text + " were able to be used for WCS refinement. \r\n\r\nClear Solution points?", "Finished...", MessageBoxButtons::YesNo);
		if (res == ::DialogResult::Yes)
		{
			POLYPOINTS = nullptr;
			POLYPOINTS2 = nullptr;
			PSESRECTS = nullptr;
			MARKCOORDRECTS = nullptr;
			ImageWindow->Refresh();
		}
	}
}

void Form1::WCSAutoBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	ProgressBar->PerformStep();
}

void Form1::WCSAutoBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	WCSAutoSolveBtn->Text = "Solve";
	ProgressBar->Value = 0;
}

void Form1::toolStripMenuItem15_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "WCSAutoDisplayChck", WCSAutoDisplayChck->Checked);
	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::WCSAutoRefineChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "WCSAutoRefineChck", WCSAutoRefineChck->Checked);
	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::WCSScaleInit_Enter(System::Object^  sender, System::EventArgs^  e)
{
	TEXTBOXENTER((Windows::Forms::ToolStripTextBox^)sender);
}

void Form1::WCSScaleInit_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	CHECKTEXTBOXTONUM((Windows::Forms::ToolStripTextBox^)sender);
}

void Form1::AutoWCSMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
{
	String^ chckstt = (String^)GetReg("CCDLAB", "WCSXParity");
	if (chckstt == "Unchecked")
		WCSAutoXAxisParityChck->CheckState = ::CheckState::Unchecked;
	if (chckstt == "Checked")
		WCSAutoXAxisParityChck->CheckState = ::CheckState::Checked;
	if (chckstt == "Indeterminate")
		WCSAutoXAxisParityChck->CheckState = ::CheckState::Indeterminate;
	chckstt = (String^)GetReg("CCDLAB", "WCSYParity");
	if (chckstt == "Unchecked")
		WCSAutoYAxisParityChck->CheckState = ::CheckState::Unchecked;
	if (chckstt == "Checked")
		WCSAutoYAxisParityChck->CheckState = ::CheckState::Checked;
	if (chckstt == "Indeterminate")
		WCSAutoYAxisParityChck->CheckState = ::CheckState::Indeterminate;
}

void Form1::AutoWCSMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	WCSScaleInit->Text = (String^)GetReg("CCDLAB", "WCSScaleInit");
	WCSScaleInitLB->Text = (String^)GetReg("CCDLAB", "WCSScaleInitLB");
	WCSScaleInitUB->Text = (String^)GetReg("CCDLAB", "WCSScaleInitUB");
	WCSRotationInit->Text = (String^)GetReg("CCDLAB", "WCSRotationInit");
	WCSRotationInitLB->Text = (String^)GetReg("CCDLAB", "WCSRotationInitLB");
	WCSRotationInitUB->Text = (String^)GetReg("CCDLAB", "WCSRotationInitUB");
	WCSAutoVertexToleranceTxt->Text = (String^)GetReg("CCDLAB", "WCSAutoVertexToleranceTxt");
	WCSAutoNCatPtsTxt->Text = (String^)GetReg("CCDLAB", "WCSAutoNCatPtsTxt");
	WCSAutoDisplayChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "WCSAutoDisplayChck"));
	WCSAutoCatalogueTxt->Tag = (String^)GetReg("CCDLAB", "WCSAutoCatalogueTxt");
	WCSAutoCatalogueTxt->Text = ((String^)WCSAutoCatalogueTxt->Tag)->Substring(((String^)WCSAutoCatalogueTxt->Tag)->LastIndexOf("\\") + 1);
	WCSAutoCatalogueTxt->ToolTipText = ((String^)WCSAutoCatalogueTxt->Tag)->Substring(0, ((String^)WCSAutoCatalogueTxt->Tag)->LastIndexOf("\\") + 1);
	WCSAutoCatalogueTxt->BackColor = Drawing::Color::Gainsboro;
	WCSAutoCatalogueCVAL1->Text = (String^)GetReg("CCDLAB", "WCSAutoCatalogueCVAL1");
	WCSAutoCatalogueCVAL2->Text = (String^)GetReg("CCDLAB", "WCSAutoCatalogueCVAL2");
	WCSAutoQueryCVAL1->Text = (String^)GetReg("CCDLAB", "WCSAutoQueryCVAL1");
	WCSAutoQueryCVAL2->Text = (String^)GetReg("CCDLAB", "WCSAutoQueryCVAL2");
	WCSAutoResolveRadiusTxt->Text = (String^)GetReg("CCDLAB", "WCSAutoResolveRadiusTxt");
	WCSAutoCatalogueExtensionTxt->Text = (String^)GetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt");
	WCSAutoCatalogueMag->Text = (String^)GetReg("CCDLAB", "WCSAutoCatalogueMag");
	WCSAutoRefineChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "WCSAutoRefineChck"));
	WCSAutoRefineNPtsTxt->Text = (String^)GetReg("CCDLAB", "WCSAutoRefineNPtsTxt");
	WCSAutoStopNMatchesText->Text = (String^)GetReg("CCDLAB", "WCSAutoStopNMatchesText");
	WCSAutoStopPercMatchesText->Text = (String^)GetReg("CCDLAB", "WCSAutoStopPercMatchesText");
	WCSLoadListNPtsTxt->Text = (String^)GetReg("CCDLAB", "WCSLoadListNPtsTxt");
	WCSQuerySaveFileChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "WCSQuerySaveFileChck"));
	WCSAutoConditionArraysChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "WCSAutoConditionArrays"));
	WCSQuerySquareRegionChck->Text = (String^)GetReg("CCDLAB", "WCSQuerySquareRegion");
	WCSQuerySolveAfter->Checked = Convert::ToBoolean(GetReg("CCDLAB", "WCSQuerySolveAfter"));
	WCSQuerySaveFileChooseDirBtn->Enabled = Convert::ToBoolean(GetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtn"));
	WCSQuerySaveFileChooseDirBtn->Checked = Convert::ToBoolean(GetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtnChck"));
}

void Form1::WCSAutoQueryBtn_DropDownOpening(System::Object^ sender, System::EventArgs^ e)
{
	AstroQueryCatalogueNameDrop->SelectedIndex = Convert::ToInt32(GetReg("CCDLAB", "AstroQueryCatalogueNameDrop"));
}

void Form1::WCSAutoExternalDLLChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoSolveBtn->ShowDropDown();
}

void Form1::WCSAutoConditionArraysChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "WCSAutoConditionArrays", WCSAutoConditionArraysChck->Checked);

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::WCSAutoCatalogueTxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	//get the catalogue list and triangles of the brightest few sources
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "FITS|*.fits;*.fit;*.fts";
	ofd->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFilesPath");
	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	WCSAutoCatalogueTxt->Text = ofd->FileName->Substring(ofd->FileName->LastIndexOf("\\") + 1);
	WCSAutoCatalogueTxt->Tag = ofd->FileName;

	SetReg("CCDLAB", "WCSAutoCATDir", ofd->FileName->Substring(0, ofd->FileName->LastIndexOf("\\")));
	SetReg("CCDLAB", "WCSAutoCatalogueTxt", ofd->FileName);




	/*WCSAutoCatalogueExtensionTxt->Text = "";
	WCSAutoCatalogueCVAL1->Text = "ra";
	WCSAutoCatalogueCVAL2->Text = "dec";
	WCSAutoCatalogueMag->Text = "phot_bp_mean_mag";
	SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt->Text);
	SetReg("CCDLAB", "WCSAutoCatalogueCVAL1", WCSAutoCatalogueCVAL1->Text);
	SetReg("CCDLAB", "WCSAutoCatalogueCVAL2", WCSAutoCatalogueCVAL2->Text);
	SetReg("CCDLAB", "WCSAutoCatalogueMag", WCSAutoCatalogueMag->Text);*/




	WCSAutoCatalogueMenuBtn->ShowDropDown();
}

void Form1::WCSAutoCatalogueTxt_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
	WCSAutoCatalogueTxt->ToolTipText = ((String^)WCSAutoCatalogueTxt->Tag)->Substring(0, ((String^)WCSAutoCatalogueTxt->Tag)->LastIndexOf("\\") + 1);
}

void Form1::WCSAutoCatalogueExtensionTxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	array<String^>^ exts = JPFITS::FITSBinTable::GetAllExtensionNames((String^)WCSAutoCatalogueTxt->Tag);

	if (exts->Length == 1)
	{
		MessageBox::Show("Only one extension to choose from: '" + exts[0] + "'");
		WCSAutoCatalogueExtensionTxt->Text = exts[0]->Trim();
		SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt->Text);
	}
	else
	{
		WCSAutoCVALList^ list = gcnew WCSAutoCVALList((String^)WCSAutoCatalogueTxt->Tag);
		list->Text = "Select Extension";
		list->ShowDialog();

		WCSMenu->ShowDropDown();
		AutoWCSMenuItem->ShowDropDown();
		WCSAutoCatalogueMenuBtn->ShowDropDown();

		if (list->DialogResult == ::DialogResult::Cancel)
			return;

		WCSAutoCatalogueExtensionTxt->Text = ((String^)list->WCDrop->SelectedItem)->Trim();
		SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt->Text);
	}
}

void Form1::WCSAutoCatalogueCVAL1_Click(System::Object^  sender, System::EventArgs^  e)
{
	WCSMenu->DropDown->AutoClose = false;
	AutoWCSMenuItem->DropDown->AutoClose = false;
	WCSAutoCatalogueMenuBtn->DropDown->AutoClose = false;

	WCSAutoCVALList^ list = gcnew WCSAutoCVALList((String^)WCSAutoCatalogueTxt->Tag, WCSAutoCatalogueExtensionTxt->Text);
	list->Text = "Select CVAL1";
	list->TopMost = true;
	list->ShowDialog();

	if (list->DialogResult == ::DialogResult::Cancel)
	{
		WCSMenu->DropDown->AutoClose = true;
		AutoWCSMenuItem->DropDown->AutoClose = true;
		WCSAutoCatalogueMenuBtn->DropDown->AutoClose = true;
		return;
	}

	WCSAutoCatalogueCVAL1->Text = ((String^)list->WCDrop->SelectedItem)->Trim();
	SetReg("CCDLAB", "WCSAutoCatalogueCVAL1", WCSAutoCatalogueCVAL1->Text);

	WCSMenu->DropDown->AutoClose = true;
	AutoWCSMenuItem->DropDown->AutoClose = true;
	WCSAutoCatalogueMenuBtn->DropDown->AutoClose = true;
}

void Form1::WCSAutoCatalogueCVAL2_Click(System::Object^  sender, System::EventArgs^  e)
{
	WCSMenu->DropDown->AutoClose = false;
	AutoWCSMenuItem->DropDown->AutoClose = false;
	WCSAutoCatalogueMenuBtn->DropDown->AutoClose = false;

	WCSAutoCVALList^ list = gcnew WCSAutoCVALList((String^)WCSAutoCatalogueTxt->Tag, WCSAutoCatalogueExtensionTxt->Text);
	list->Text = "Select CVAL2";
	list->TopMost = true;
	list->ShowDialog();

	if (list->DialogResult == ::DialogResult::Cancel)
	{
		WCSMenu->DropDown->AutoClose = true;
		AutoWCSMenuItem->DropDown->AutoClose = true;
		WCSAutoCatalogueMenuBtn->DropDown->AutoClose = true;
		return;
	}

	WCSAutoCatalogueCVAL2->Text = ((String^)list->WCDrop->SelectedItem)->Trim();
	SetReg("CCDLAB", "WCSAutoCatalogueCVAL2", WCSAutoCatalogueCVAL2->Text);

	WCSMenu->DropDown->AutoClose = true;
	AutoWCSMenuItem->DropDown->AutoClose = true;
	WCSAutoCatalogueMenuBtn->DropDown->AutoClose = true;
}

void Form1::WCSAutoCatalogueMag_Click(System::Object^  sender, System::EventArgs^  e)
{
	WCSMenu->DropDown->AutoClose = false;
	AutoWCSMenuItem->DropDown->AutoClose = false;
	WCSAutoCatalogueMenuBtn->DropDown->AutoClose = false;

	WCSAutoCVALList^ list = gcnew WCSAutoCVALList((String^)WCSAutoCatalogueTxt->Tag, WCSAutoCatalogueExtensionTxt->Text);
	list->Text = "Select Magnitude";
	list->TopMost = true;
	list->ShowDialog();

	if (list->DialogResult == ::DialogResult::Cancel)
	{
		WCSMenu->DropDown->AutoClose = true;
		AutoWCSMenuItem->DropDown->AutoClose = true;
		WCSAutoCatalogueMenuBtn->DropDown->AutoClose = true;
		return;
	}

	WCSAutoCatalogueMag->Text = ((String^)list->WCDrop->SelectedItem)->Trim();
	SetReg("CCDLAB", "WCSAutoCatalogueMag", WCSAutoCatalogueMag->Text);

	WCSMenu->DropDown->AutoClose = true;
	AutoWCSMenuItem->DropDown->AutoClose = true;
	WCSAutoCatalogueMenuBtn->DropDown->AutoClose = true;
}

void Form1::WCSAutoQueryCVAL1_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (IMAGESET->Count == 0)
		return;

	WCSMenu->DropDown->AutoClose = false;
	AutoWCSMenuItem->DropDown->AutoClose = false;
	WCSAutoQueryBtn->DropDown->AutoClose = false;

	WCSAutoCVALList^ list = gcnew WCSAutoCVALList(IMAGESET[FILELISTINDEX]->HeaderKeys);
	list->Text = "Select the CVALn";
	list->TopMost = true;
	list->ShowDialog();

	if (list->DialogResult == ::DialogResult::Cancel)
	{
		WCSMenu->DropDown->AutoClose = true;
		AutoWCSMenuItem->DropDown->AutoClose = true;
		WCSAutoQueryBtn->DropDown->AutoClose = true;
		return;
	}

	String^ hkey = ((String^)list->WCDrop->SelectedItem)->Trim();
	SetReg("CCDLAB", ((::Windows::Forms::ToolStripTextBox^)sender)->Name, hkey);
	((::Windows::Forms::ToolStripTextBox^)sender)->Text = hkey;

	WCSMenu->DropDown->AutoClose = true;
	AutoWCSMenuItem->DropDown->AutoClose = true;
	WCSAutoQueryBtn->DropDown->AutoClose = true;
}

void Form1::WCSAutoQueryBtn_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
	if (IMAGESET->Count == 0)
		return;

	String^ catalogue = (String^)AstroQueryCatalogueNameDrop->SelectedItem;
	catalogue = catalogue->Substring(0, catalogue->IndexOf("(") - 1);

	String^ cval1 = IMAGESET[FILELISTINDEX]->GetKeyValue(WCSAutoQueryCVAL1->Text);
	String^ cval2 = IMAGESET[FILELISTINDEX]->GetKeyValue(WCSAutoQueryCVAL2->Text);
	try
	{
		Convert::ToDouble(cval1);
	}
	catch (...)
	{
		double ra, dec;
		JPMath::RADecSexToDegree(cval1, cval2, "", ra, dec);
		cval1 = ra.ToString();
		cval2 = dec.ToString();
	}

	String^ filename = "";
	if (WCSQuerySaveFileChck->Checked)
		if (!WCSQuerySaveFileChooseDirBtn->Checked)
			filename = IMAGESET[FILELISTINDEX]->FullFileName->Substring(0, IMAGESET[FILELISTINDEX]->FullFileName->LastIndexOf(".")) + "_queryCatalog.fit";
		else
		{
			FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
			fbd->SelectedPath = IMAGESET[FILELISTINDEX]->FilePath;
			fbd->Description = "Select directpry to save catalogue";
			if (fbd->ShowDialog() == ::DialogResult::Cancel)
				return;
			filename = fbd->SelectedPath + "\\" + DirectoryInfo(fbd->SelectedPath).Name + "_queryCatalog.fit";
		}
	
	String^ radius = WCSAutoResolveRadiusTxt->Text;

	String^ square = "0";
	if (WCSQuerySquareRegionChck->Text->Contains("Square"))
		square = "1";

	WCSMenu->HideDropDown();
	AutoWCSMenuItem->HideDropDown();
	WCSAutoQueryBtn->HideDropDown();

	int res = JPFITS::WCS_AutoSolver::AstroQuery(catalogue, cval1, cval2, filename, radius, square);
	if (res != 0)
	{
		MessageBox::Show("Query failed with exit code: " + res);
		return;
	}

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoQueryBtn->ShowDropDown();

	WCSAutoCatalogueTxt->Tag = filename;
	WCSAutoCatalogueTxt->Text = ((String^)WCSAutoCatalogueTxt->Tag)->Substring(((String^)WCSAutoCatalogueTxt->Tag)->LastIndexOf("\\") + 1);
	WCSAutoCatalogueTxt->ToolTipText = ((String^)WCSAutoCatalogueTxt->Tag)->Substring(0, ((String^)WCSAutoCatalogueTxt->Tag)->LastIndexOf("\\") + 1);
	SetReg("CCDLAB", "WCSAutoCATDir", filename->Substring(0, filename->LastIndexOf("\\")));
	SetReg("CCDLAB", "WCSAutoCatalogueTxt", filename);
	WCSAutoCatalogueTxt->BackColor = Drawing::Color::LightGreen;
	WCSAutoCatalogueExtensionTxt->Text = "";
	WCSAutoCatalogueCVAL1->Text = "ra";
	WCSAutoCatalogueCVAL2->Text = "dec";
	WCSAutoCatalogueMag->Text = "phot_bp_mean_mag";
	SetReg("CCDLAB", "WCSAutoCatalogueExtensionTxt", WCSAutoCatalogueExtensionTxt->Text);
	SetReg("CCDLAB", "WCSAutoCatalogueCVAL1", WCSAutoCatalogueCVAL1->Text);
	SetReg("CCDLAB", "WCSAutoCatalogueCVAL2", WCSAutoCatalogueCVAL2->Text);
	SetReg("CCDLAB", "WCSAutoCatalogueMag", WCSAutoCatalogueMag->Text);

	if (WCSQuerySolveAfter->Checked)
		WCSAutoSolveBtn->PerformClick();
}

void Form1::WCSQuerySaveFileChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (WCSQuerySaveFileChck->Checked)
		WCSQuerySaveFileChooseDirBtn->Enabled = true;
	else
		WCSQuerySaveFileChooseDirBtn->Enabled = false;

	SetReg("CCDLAB", "WCSQuerySaveFileChck", WCSQuerySaveFileChck->Checked);
	SetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtn", WCSQuerySaveFileChooseDirBtn->Enabled);

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoQueryBtn->ShowDropDown();
}

void Form1::WCSQuerySaveFileChooseDirBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "WCSQuerySaveFileChooseDirBtnChck", WCSQuerySaveFileChooseDirBtn->Checked);

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoQueryBtn->ShowDropDown();
	WCSQuerySaveFileChck->ShowDropDown();
}

void Form1::WCSQuerySquareRegionChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (WCSQuerySquareRegionChck->Text->Contains("Square"))
		WCSQuerySquareRegionChck->Text = "Circular Region";
	else
		WCSQuerySquareRegionChck->Text = "Square Region";

	SetReg("CCDLAB", "WCSQuerySquareRegion", WCSQuerySquareRegionChck->Text);

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoQueryBtn->ShowDropDown();
}

void Form1::WCSQuerySolveAfter_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "WCSQuerySolveAfter", WCSQuerySolveAfter->Checked);

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoQueryBtn->ShowDropDown();
}

void Form1::AstroQueryCatalogueNameDrop_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "AstroQueryCatalogueNameDrop", AstroQueryCatalogueNameDrop->SelectedIndex);

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	WCSAutoQueryBtn->ShowDropDown();
}

void Form1::WCSAutoSolveBtn_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	WCSAutoSolveBtn->BackColor = Color::LightGray;
}

void Form1::WCSAutoSolveBtn_MouseLeave(System::Object^  sender, System::EventArgs^  e)
{
	WCSAutoSolveBtn->BackColor = System::Drawing::SystemColors::Control;
}

void Form1::AutoWCSScaleMenuBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::AutoWCSScaleMenuBtn_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
{
	String^ wcparamsfile = CCDLABPATH + "WCSparams.fits";
	if (!File::Exists(wcparamsfile))
		return;

	array<String^>^ wcsnames = JPFITS::FITSBinTable::GetAllExtensionNames(wcparamsfile);

	array<Windows::Forms::ToolStripButton^>^ tsbcs = gcnew array<Windows::Forms::ToolStripButton^>(wcsnames->Length);

	Windows::Forms::ToolStripItem^ svbtn = AutoWCSScaleMenuBtn->DropDownItems[0];
	AutoWCSScaleMenuBtn->DropDownItems->Clear();
	AutoWCSScaleMenuBtn->DropDownItems->Add(svbtn);

	for (int i = 0; i < wcsnames->Length; i++)
	{
		tsbcs[i] = gcnew Windows::Forms::ToolStripButton(wcsnames[i]);
		tsbcs[i]->Width = tsbcs[i]->Text->Length * 6;
		tsbcs[i]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::WCSParamMenuBtn_MouseDown);
		tsbcs[i]->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::WCSParamMenuBtn_MouseUp);
		tsbcs[i]->Tag = i + 1;
	}
	
	AutoWCSScaleMenuBtn->DropDownItems->AddRange(tsbcs);
}

void Form1::AutoWCSScaleSaveBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::WSCSaveScaleTxtBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyCode != Keys::Enter)
		return;

	e->SuppressKeyPress = true;

	String^ extname = WSCSaveScaleTxtBox->Text;

	if (JPMath::IsNumeric(extname->Substring(0, 1)))
	{
		extname = "";
		WSCSaveScaleTxtBox->Text = extname;
	}

	if (extname == "")
		return;

	String^ wcsparamsfile = CCDLABPATH + "WCSparams.fits";
	array<String^>^ entrylabels = gcnew array<String^>(6) { "WCSScaleInit", "WCSScaleInitLB", "WCSScaleInitUB", "WCSRotationInit", "WCSRotationInitLB", "WCSRotationInitUB" };
	array<TypeCode>^ types = gcnew array<TypeCode>(6) { TypeCode::Double, TypeCode::Double, TypeCode::Double, TypeCode::Double, TypeCode::Double, TypeCode::Double };
	array<String^>^ units = gcnew array<String^>(6) { "arcsec per pixel", "arcsec per pixel", "arcsec per pixel", "Degrees", "Degrees", "Degrees" };
	array<Object^>^ objarray = gcnew array<Object^>(6);
	objarray[0] = gcnew array<double>(1) { Convert::ToDouble(WCSScaleInit->Text) };
	objarray[1] = gcnew array<double>(1) { Convert::ToDouble(WCSScaleInitLB->Text) };
	objarray[2] = gcnew array<double>(1) { Convert::ToDouble(WCSScaleInitUB->Text) };
	objarray[3] = gcnew array<double>(1) { Convert::ToDouble(WCSRotationInit->Text) };
	objarray[4] = gcnew array<double>(1) { Convert::ToDouble(WCSRotationInitLB->Text) };
	objarray[5] = gcnew array<double>(1) { Convert::ToDouble(WCSRotationInitUB->Text) };
	//FITSBinTable::WriteExtension(wcsparamsfile, extname, true, entrylabels, units, nullptr, nullptr, nullptr, objarray);
	FITSBinTable^ bt = gcnew FITSBinTable();
	bt->SetTTYPEEntries(entrylabels, units, objarray);
	bt->Write(wcsparamsfile, extname, true);

	AutoWCSScaleMenuBtn->HideDropDown();
	AutoWCSScaleMenuBtn->ShowDropDown();
}

void Form1::WCSParamMenuBtn_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	String^ wcsparamsfile = CCDLABPATH + "WCSparams.fits";

	if (e->Button == ::MouseButtons::Right)
	{
		if (MessageBox::Show("Remove '" + ((Windows::Forms::ToolStripItem^)sender)->Text + "'?", "Remove?", MessageBoxButtons::OKCancel) == ::DialogResult::OK)
		{
			FITSBinTable::RemoveExtension(wcsparamsfile, ((Windows::Forms::ToolStripItem^)sender)->Text);
			AutoWCSScaleMenuBtn->HideDropDown();
			AutoWCSScaleMenuBtn->ShowDropDown();
		}
		return;
	}

	try
	{
		JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(wcsparamsfile, ((Windows::Forms::ToolStripItem^)sender)->Text);
		WCSScaleInit->Text = bt->GetTTYPEEntry("WCSScaleInit")[0].ToString();
		WCSScaleInitLB->Text = bt->GetTTYPEEntry("WCSScaleInitLB")[0].ToString();
		WCSScaleInitUB->Text = bt->GetTTYPEEntry("WCSScaleInitUB")[0].ToString();
		WCSRotationInit->Text = bt->GetTTYPEEntry("WCSRotationInit")[0].ToString();
		WCSRotationInitLB->Text = bt->GetTTYPEEntry("WCSRotationInitLB")[0].ToString();
		WCSRotationInitUB->Text = bt->GetTTYPEEntry("WCSRotationInitUB")[0].ToString();
	}
	catch (...)
	{

	}
}

void Form1::WCSParamMenuBtn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
	AutoWCSScaleMenuBtn->ShowDropDown();
}

void Form1::WCSAutoXAxisParityChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (WCSAutoXAxisParityChck->CheckState == ::CheckState::Unchecked)
		WCSAutoXAxisParityChck->CheckState = ::CheckState::Checked;
	else if (WCSAutoXAxisParityChck->CheckState == ::CheckState::Checked)
		WCSAutoXAxisParityChck->CheckState = ::CheckState::Indeterminate;
	else if (WCSAutoXAxisParityChck->CheckState == ::CheckState::Indeterminate)
		WCSAutoXAxisParityChck->CheckState = ::CheckState::Unchecked;

	SetReg("CCDLAB", "WCSXParity", WCSAutoXAxisParityChck->CheckState.ToString());

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::WCSAutoYAxisParityChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (WCSAutoYAxisParityChck->CheckState == ::CheckState::Unchecked)
		WCSAutoYAxisParityChck->CheckState = ::CheckState::Checked;
	else if (WCSAutoYAxisParityChck->CheckState == ::CheckState::Checked)
		WCSAutoYAxisParityChck->CheckState = ::CheckState::Indeterminate;
	else if (WCSAutoYAxisParityChck->CheckState == ::CheckState::Indeterminate)
		WCSAutoYAxisParityChck->CheckState = ::CheckState::Unchecked;

	SetReg("CCDLAB", "WCSYParity", WCSAutoYAxisParityChck->CheckState.ToString());

	WCSMenu->ShowDropDown();
	AutoWCSMenuItem->ShowDropDown();
}

void Form1::WCSClearAllChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	WCSMenu->ShowDropDown();
	WCSClearMenuBtn->ShowDropDown();
}

void Form1::GET_CATALOGUE_NPTS(String^ filename, String^ catExtension, String^ catCVAL1, String^ catCVAL2, String^ catMag, int N_bright)
{
	JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(filename, catExtension);
	WCS_RA = bt->GetTTYPEEntry(catCVAL1);
	WCS_DEC = bt->GetTTYPEEntry(catCVAL2);
	array<double>^ mag = bt->GetTTYPEEntry(catMag);

	//need to check mag for NaN's and re-form ra dec mag
	ArrayList^ ralist = gcnew ArrayList(WCS_RA->Length);
	ArrayList^ declist = gcnew ArrayList(WCS_RA->Length);
	ArrayList^ maglist = gcnew ArrayList(WCS_RA->Length);
	for (int i = 0; i < mag->Length; i++)
	{
		if (Double::IsNaN(mag[i]))
			continue;

		ralist->Add(WCS_RA[i]);
		declist->Add(WCS_DEC[i]);
		maglist->Add(mag[i]);
	}
	for (int i = 0; i < ralist->Count; i++)
	{
		WCS_RA[i] = Convert::ToDouble(ralist[i]);
		WCS_DEC[i] = Convert::ToDouble(declist[i]);
		mag[i] = Convert::ToDouble(maglist[i]);
	}
	Array::Resize(WCS_RA, ralist->Count);
	Array::Resize(WCS_DEC, ralist->Count);
	Array::Resize(mag, ralist->Count);

	//sort the catalogue list by magnitude
	array<double>^ keysref = gcnew array<double>(mag->Length);
	Array::Copy(mag, keysref, mag->Length);
	Array::Sort(mag, WCS_RA);
	Array::Copy(keysref, mag, mag->Length);
	Array::Sort(mag, WCS_DEC);

	if (N_bright > 0 && N_bright < WCS_RA->Length)
	{
		Array::Resize(WCS_RA, N_bright);
		Array::Resize(WCS_DEC, N_bright);
	}
}

void Form1::AutoWCSXCorr_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (IMAGESET->Count == 0)
		return;



	//********************************assume PSE is done and available with some N pts**************************
	int kernelradius = 1;
	array<double>^ x_pix_hist_vec = gcnew array<double>(IMAGESET[FILELISTINDEX]->Width / kernelradius);
	array<double>^ y_pix_hist_vec = gcnew array<double>(IMAGESET[FILELISTINDEX]->Height / kernelradius);
	for (int k = 0; k < PSES[PSESINDEX]->N_Sources; k++)
	{
		x_pix_hist_vec[(int)Math::Round(PSES[PSESINDEX]->Centroids_X[k] / (double)kernelradius)] ++;
		y_pix_hist_vec[(int)Math::Round(PSES[PSESINDEX]->Centroids_Y[k] / (double)kernelradius)] ++;
	}
	//x_pix_hist_vec = JPMath::VectorSubScalar(x_pix_hist_vec, JPMath::Mean(x_pix_hist_vec));
	//y_pix_hist_vec = JPMath::VectorSubScalar(y_pix_hist_vec, JPMath::Mean(y_pix_hist_vec));
	/*array<double>^ axis = gcnew array<double>(x_pix_hist_vec->Length);
	for (int k = 0; k < axis->Length; k++)
		axis[k] = (double)k;
	JPPlot^ xplot = gcnew JPPlot();
	xplot->PlotLine(axis, x_pix_hist_vec, "", "", "", ::Charting::SeriesChartType::Line, "test");
	JPPlot^ yplot = gcnew JPPlot();
	yplot->PlotLine(axis, y_pix_hist_vec, "", "", "", ::Charting::SeriesChartType::Line, "test");
	return;*/






	GET_CATALOGUE_NPTS((String^)WCSAutoCatalogueTxt->Tag, WCSAutoCatalogueExtensionTxt->Text, WCSAutoCatalogueCVAL1->Text, WCSAutoCatalogueCVAL2->Text, WCSAutoCatalogueMag->Text, /*N*/200);








	array<JPMath::PointD^>^ CATpts = gcnew array<JPMath::PointD^>(WCS_RA->Length);
	double crval1 = 0, crval2 = 0;
	for (int i = 0; i < CATpts->Length; i++)
	{
		CATpts[i] = gcnew JPMath::PointD(WCS_RA[i], WCS_DEC[i], 0);
		crval1 += CATpts[i]->X;
		crval2 += CATpts[i]->Y;
	}
	crval1 /= (double)CATpts->Length;//the reference value can be the mean
	crval2 /= (double)CATpts->Length;//the reference value can be the mean

	//convert the catalogue points to intermediate points
	array<JPMath::PointD^>^ CATpts_intrmdt = gcnew array<JPMath::PointD^>(WCS_RA->Length);
	double a0 = crval1 * Math::PI / 180, d0 = crval2 * Math::PI / 180;
	for (int i = 0; i < CATpts_intrmdt->Length; i++)
	{
		double a = CATpts[i]->X * Math::PI / 180;//radians
		double d = CATpts[i]->Y * Math::PI / 180;//radians

		//for tangent plane Gnomic
		double x_intrmdt = Math::Cos(d) * Math::Sin(a - a0) / (Math::Cos(d0) * Math::Cos(d) * Math::Cos(a - a0) + Math::Sin(d0) * Math::Sin(d));
		double y_intrmdt = (Math::Cos(d0) * Math::Sin(d) - Math::Cos(d) * Math::Sin(d0) * Math::Cos(a - a0)) / (Math::Sin(d0) * Math::Sin(d) + Math::Cos(d0) * Math::Cos(d) * Math::Cos(a - a0));

		CATpts_intrmdt[i] = gcnew JPMath::PointD(x_intrmdt, y_intrmdt, 0);
	}

	double crpix1 = JPMath::Mean(PSES[PSESINDEX]->Centroids_X, true);
	double crpix2 = JPMath::Mean(PSES[PSESINDEX]->Centroids_Y, true);

	double minangle = -2 * Math::PI / 180;
	double maxangle = 2 * Math::PI / 180;

	double anglestep = Math::Atan(/*double(kernelradius)*/2 / double(IMAGESET[FILELISTINDEX]->Width)) / 3;//radians
	int totalangles = (int)Math::Round((maxangle - minangle) / anglestep);
	anglestep = (maxangle - minangle) / (double)totalangles;//radians

	//MessageBox::Show(totalangles + " total angles; " + anglestep * 180 / Math::PI + " angle step degrees");
	//return;

	double S = 0.41581283;//scale ''/pix
	S *= Math::PI / 180 / 3600;// rad/pix

	JPPlot^ xplot = gcnew JPPlot();
	JPPlot^ yplot = gcnew JPPlot();

	//parallel if
	for (int i = 0; i < totalangles; i++)
	{
		double phi = minangle + (double)i * anglestep;
		array<JPMath::PointD^>^ CATpts_intrmdt_pix = gcnew array<JPMath::PointD^>(CATpts_intrmdt->Length);
		//phi = -phi;

		//transform rotate the intermediate coordinates to pixel coordinates using fixed scale and current rotation phi and given crpix references
		for (int k = 0; k < CATpts_intrmdt->Length; k++)
		{
			double x_intrmdt_pix = ((double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / S * (Math::Cos(-phi) * CATpts_intrmdt[k]->X - Math::Sin(-phi) * CATpts_intrmdt[k]->Y) + crpix1));
			double y_intrmdt_pix = ((double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / S * (Math::Sin(-phi) * CATpts_intrmdt[k]->X + Math::Cos(-phi) * CATpts_intrmdt[k]->Y) + crpix2));
			CATpts_intrmdt_pix[k] = gcnew JPMath::PointD(x_intrmdt_pix, y_intrmdt_pix, 0);
		}

		//create binned/histogram x/y vectors from current CATpts_intrmdt_pix
		array<double>^ X_intrmdt_pix_hist_vec = gcnew array<double>(IMAGESET[FILELISTINDEX]->Width / kernelradius);
		array<double>^ Y_intrmdt_pix_hist_vec = gcnew array<double>(IMAGESET[FILELISTINDEX]->Height / kernelradius);
		for (int k = 0; k < CATpts_intrmdt_pix->Length; k++)
		{
			int x = (int)Math::Round(CATpts_intrmdt_pix[k]->X / (double)kernelradius);
			int y = (int)Math::Round(CATpts_intrmdt_pix[k]->Y / (double)kernelradius);

			if (x >= 0 && y >= 0 && x < X_intrmdt_pix_hist_vec->Length && y < Y_intrmdt_pix_hist_vec->Length)
			{
				X_intrmdt_pix_hist_vec[x] ++;
				Y_intrmdt_pix_hist_vec[y] ++;
			}
		}
		//X_intrmdt_pix_hist_vec = JPMath::VectorSubScalar(X_intrmdt_pix_hist_vec, JPMath::Mean(X_intrmdt_pix_hist_vec));
		//Y_intrmdt_pix_hist_vec = JPMath::VectorSubScalar(Y_intrmdt_pix_hist_vec, JPMath::Mean(Y_intrmdt_pix_hist_vec));

		/*array<double>^ axis = gcnew array<double>(X_intrmdt_pix_hist_vec->Length);
		for (int k = 0; k < axis->Length; k++)
			axis[k] = (double)k;
		JPPlot^ xplot = gcnew JPPlot();
		xplot->PlotLine(axis, X_intrmdt_pix_hist_vec, "", "", "", ::Charting::SeriesChartType::Line, "test");
		JPPlot^ yplot = gcnew JPPlot();
		yplot->PlotLine(axis, Y_intrmdt_pix_hist_vec, "", "", "", ::Charting::SeriesChartType::Line, "test");
		return;*/

		array<int>^ x_lags = gcnew array<int>(X_intrmdt_pix_hist_vec->Length * 2 - 1);
		array<int>^ y_lags = gcnew array<int>(Y_intrmdt_pix_hist_vec->Length * 2 - 1);

		array<double>^ x_xcorr = JPMath::XCorr(x_pix_hist_vec, X_intrmdt_pix_hist_vec, x_lags, false);
		array<double>^ y_xcorr = JPMath::XCorr(y_pix_hist_vec, Y_intrmdt_pix_hist_vec, y_lags, false);

		array<double>^ d_xlags = gcnew array<double>(x_lags->Length);
		for (int k = 0; k < d_xlags->Length; k++)
			d_xlags[k] = (double)x_lags[k];
		xplot->PlotLine(d_xlags, x_xcorr, "", "", "", ::Charting::SeriesChartType::Line, "test");
		//yplot->PlotLine(d_xlags, y_xcorr, "", "", "", ::Charting::SeriesChartType::Line, "test");
		//return;
		if (MessageBox::Show(i + " " + totalangles + " " + phi * 180 / Math::PI, "", MessageBoxButtons::OKCancel) == ::DialogResult::OK)
			continue;
		else
			return;





		bool x_check_soltn = false;
		bool y_check_soltn = false;

		int n_matches = 10;

		int x_lag = 0, y_lag = 0;
		for (int k = 0; k < x_xcorr->Length; k++)
			if (x_xcorr[k] >= n_matches)
			{
				x_check_soltn = true;
				x_lag = x_lags[k] * kernelradius;
				break;
			}
		for (int k = 0; k < y_xcorr->Length; k++)
			if (y_xcorr[k] >= n_matches)
			{
				y_check_soltn = true;
				y_lag = y_lags[k] * kernelradius;
				break;
			}

		if (!x_check_soltn || !y_check_soltn)
			continue;

		//now check for a solution
		//critical here when parallel
		
		//have rotation, update crpix based on lags...plus or minus????????............I think -ve due to parity inversion of interm CAT coords wrt PSE coords inside transformation
		crpix1 -= x_lag;
		crpix2 -= y_lag;

		int c = 0;
		for (int k = 0; k < CATpts_intrmdt->Length; k++)
		{
			int x_intrmdt_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / S * (Math::Cos(-phi) * CATpts_intrmdt[k]->X - Math::Sin(-phi) * CATpts_intrmdt[k]->Y) + crpix1));
			int y_intrmdt_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / S * (Math::Sin(-phi) * CATpts_intrmdt[k]->X + Math::Cos(-phi) * CATpts_intrmdt[k]->Y) + crpix2));

			if (x_intrmdt_pix > 0 && y_intrmdt_pix > 0 && x_intrmdt_pix < IMAGESET[FILELISTINDEX]->Width && y_intrmdt_pix < IMAGESET[FILELISTINDEX]->Height && PSES[PSESINDEX]->SourceBooleanMap[x_intrmdt_pix, y_intrmdt_pix])
				c++;
		}
		//c should be >= n_matches........*******************************
		MessageBox::Show(c + " n_matches after transformation w lags result");

		array<double>^ xpix_pse_matches = gcnew array<double>(c);
		array<double>^ ypix_pse_matches = gcnew array<double>(c);
		WCS_RA = gcnew array<double>(c);
		WCS_DEC = gcnew array<double>(c);
		MARKCOORDS = gcnew array <double, 2>(2, c);
		c = 0;
		for (int k = 0; k < CATpts_intrmdt->Length; k++)
		{
			int x_intrmdt_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Width - 1 - (1 / S * (Math::Cos(-phi) * CATpts_intrmdt[k]->X - Math::Sin(-phi) * CATpts_intrmdt[k]->Y) + crpix1));
			int y_intrmdt_pix = (int)Math::Round((double)IMAGESET[FILELISTINDEX]->Height - 1 - (1 / S * (Math::Sin(-phi) * CATpts_intrmdt[k]->X + Math::Cos(-phi) * CATpts_intrmdt[k]->Y) + crpix2));

			if (x_intrmdt_pix > 0 && y_intrmdt_pix > 0 && x_intrmdt_pix < IMAGESET[FILELISTINDEX]->Width && y_intrmdt_pix < IMAGESET[FILELISTINDEX]->Height && PSES[PSESINDEX]->SourceBooleanMap[x_intrmdt_pix, y_intrmdt_pix])
			{
				int index = PSES[PSESINDEX]->SourceIndexMap[x_intrmdt_pix, y_intrmdt_pix];
				xpix_pse_matches[c] = PSES[PSESINDEX]->Centroids_X[index];
				ypix_pse_matches[c] = PSES[PSESINDEX]->Centroids_Y[index];
				WCS_RA[c] = CATpts[k]->X;
				WCS_DEC[c] = CATpts[k]->Y;
				MARKCOORDS[0, c] = x_intrmdt_pix;
				MARKCOORDS[1, c] = y_intrmdt_pix;
				c++;
			}
		}


	}
}

