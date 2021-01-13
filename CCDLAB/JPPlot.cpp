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

#include "StdAfx.h"
#include "JPPlot.h"
#include "Form1.h"

//save location and size, use title or something for registry entry identification
void CCDLAB::JPPlot::JPPlot_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (this->Text == "Row Plot")
	{
		SetReg("CCDLAB","ROWplotPOSX",this->Location.X);
		SetReg("CCDLAB","ROWplotPOSY",this->Location.Y);
		SetReg("CCDLAB","ROWplotWIDTH",this->Size.Width);
		SetReg("CCDLAB","ROWplotHEIGHT",this->Size.Height);
	}
	if (this->Text == "Column Plot")
	{
		SetReg("CCDLAB","COLplotPOSX",this->Location.X);
		SetReg("CCDLAB","COLplotPOSY",this->Location.Y);
		SetReg("CCDLAB","COLplotWIDTH",this->Size.Width);
		SetReg("CCDLAB","COLplotHEIGHT",this->Size.Height);
	}
	if (this->Text == "Radial Profile Plot")
	{
		SetReg("CCDLAB","RADplotPOSX", this->Left);
		SetReg("CCDLAB","RADplotPOSY", this->Top);
		SetReg("CCDLAB","RADplotWIDTH", this->Width);
		SetReg("CCDLAB","RADplotHEIGHT", this->Height);
	}
	if (this->Text == "X-Drift")
	{
		SetReg("CCDLAB","XDriftplotPOSX",this->Location.X);
		SetReg("CCDLAB","XDriftplotPOSY",this->Location.Y);
		SetReg("CCDLAB","XDriftplotWIDTH",this->Size.Width);
		SetReg("CCDLAB","XDriftplotHEIGHT",this->Size.Height);
	}
	if (this->Text == "Y-Drift")
	{
		SetReg("CCDLAB","YDriftplotPOSX",this->Location.X);
		SetReg("CCDLAB","YDriftplotPOSY",this->Location.Y);
		SetReg("CCDLAB","YDriftplotWIDTH",this->Size.Width);
		SetReg("CCDLAB","YDriftplotHEIGHT",this->Size.Height);
	}
	if (this->Text == "Radial Line Plot")
	{
		SetReg("CCDLAB", "RadialLinePlotPOSX", this->Location.X);
		SetReg("CCDLAB", "RadialLinePlotPOSY", this->Location.Y);
		SetReg("CCDLAB", "RadialLinePlotWIDTH", this->Size.Width);
		SetReg("CCDLAB", "RadialLinePlotHEIGHT", this->Size.Height);
	}

	if (FIT_RESIDUALS_PLOT != nullptr)
		FIT_RESIDUALS_PLOT->Close();
}

//apply location and size, use title or something for registry entry identification
void CCDLAB::JPPlot::JPPlot_Load(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		if (this->Text == "Row Plot")
		{
			this->Left		= (int)GetReg("CCDLAB","ROWplotPOSX");
			this->Top		= (int)GetReg("CCDLAB","ROWplotPOSY");
			this->Width		= (int)GetReg("CCDLAB","ROWplotWIDTH");
			this->Height	= (int)GetReg("CCDLAB","ROWplotHEIGHT");
		}
		if (this->Text == "Column Plot")
		{
			this->Left		= (int)GetReg("CCDLAB","COLplotPOSX");
			this->Top		= (int)GetReg("CCDLAB","COLplotPOSY");
			this->Width		= (int)GetReg("CCDLAB","COLplotWIDTH");
			this->Height	= (int)GetReg("CCDLAB","COLplotHEIGHT");
		}
		if (this->Text == "Radial Profile Plot")
		{
			this->Left		= (int)GetReg("CCDLAB","RADplotPOSX");
			this->Top		= (int)GetReg("CCDLAB","RADplotPOSY");
			this->Width		= (int)GetReg("CCDLAB","RADplotWIDTH");
			this->Height	= (int)GetReg("CCDLAB","RADplotHEIGHT");
		}
		if (this->Text == "X-Drift")
		{
			this->Left		= (int)GetReg("CCDLAB","XDriftplotPOSX");
			this->Top		= (int)GetReg("CCDLAB","XDriftplotPOSY");
			this->Width		= (int)GetReg("CCDLAB","XDriftplotWIDTH");
			this->Height	= (int)GetReg("CCDLAB","XDriftplotHEIGHT");
		}
		if (this->Text == "Y-Drift")
		{
			this->Left		= (int)GetReg("CCDLAB","YDriftplotPOSX");
			this->Top		= (int)GetReg("CCDLAB","YDriftplotPOSY");
			this->Width		= (int)GetReg("CCDLAB","YDriftplotWIDTH");
			this->Height	= (int)GetReg("CCDLAB","YDriftplotHEIGHT");
		}
		if (this->Text == "Radial Line Plot")
		{
			this->Left		= (int)GetReg("CCDLAB", "RadialLinePlotPOSX");
			this->Top		= (int)GetReg("CCDLAB", "RadialLinePlotPOSY");
			this->Width		= (int)GetReg("CCDLAB", "RadialLinePlotWIDTH");
			this->Height	= (int)GetReg("CCDLAB", "RadialLinePlotHEIGHT");
		}
		if (this->Text->Contains("Residuals"))
		{
			this->Left = (int)GetReg("CCDLAB", "RADplotPOSX");
			this->Top = (int)GetReg("CCDLAB", "RADplotPOSY") + (int)GetReg("CCDLAB", "RADplotHEIGHT");
			this->Width = (int)GetReg("CCDLAB", "RADplotWIDTH");
			this->Height = ((int)GetReg("CCDLAB", "RADplotHEIGHT"))/2;
		}

		PixelScaleTxtBox->Text = (String^)GetReg("CCDLAB", "PixelScaleTxt");
		FitMenuPlotResidualsChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "JPPlotResiduals"));
	}
	catch (...) {}
}

void CCDLAB::JPPlot::JPPlot_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
}

void CCDLAB::JPPlot::PlotLine(array<double>^ XData, array<double>^ YData, String^ XTitle, String^ YTitle, String^ ChartTitle, Charting::SeriesChartType ChartStyle, String^ SeriesName)
{
	jpplotXDATA = gcnew array<double>(XData->Length);
	jpplotYDATA = gcnew array<double>(XData->Length);

	double offset = 0;
	if (ChartStyle == Charting::SeriesChartType::StepLine)
		offset = 0.5;

	for (int i = 0; i < XData->Length; i++)
	{
		jpplotXDATA[i] = XData[i] + offset;
		jpplotYDATA[i] = YData[i];
	}
	plotchart1->SuspendDrawing();
	plotchart1->PlotXYData(jpplotXDATA, jpplotYDATA, ChartTitle, XTitle, YTitle, ChartStyle, SeriesName);
	plotchart1->ResumeDrawing();
	this->Show();
	//JPPlot::Show();
}

void CCDLAB::JPPlot::AddLine(cli::array<double,1> ^XData, cli::array<double,1> ^YData, System::Windows::Forms::DataVisualization::Charting::SeriesChartType ChartStyle, String^ SeriesName)
{
	plotchart1->SuspendDrawing();
	plotchart1->AddXYData(XData, YData, ChartStyle, SeriesName);
	plotchart1->ResumeDrawing();
}

void CCDLAB::JPPlot::FitMenuGaussian_Click(System::Object^  sender, System::EventArgs^  e)
{
	double pixscale = ::Convert::ToDouble(PixelScaleTxtBox->Text);
	if (pixscale <= 0)
		pixscale = 1;

	if (this->Text == "Radial Profile Plot")
	{
		array<double>^ XDATA = gcnew array<double>(jpplotXDATA->Length);
		for (int i = 0; i < jpplotXDATA->Length; i++)
			XDATA[i] = jpplotXDATA[i]*pixscale;

		array<double>^ PFit = gcnew array<double>(4) { 1, 0, XDATA[XDATA->Length - 1] / 4, 0 };
		array<double>^ PFitL = gcnew array<double>(4) { 1, 0, XDATA[XDATA->Length - 1] / 50, 0 };
		array<double>^ PFitU = gcnew array<double>(4) { 1, 0, XDATA[XDATA->Length - 1], 0 };
		array<double>^ resids;
		if (FitMenuPlotResidualsChck->Checked)
			resids = gcnew array<double>(XDATA->Length);
		JPMath::Fit_Gaussian1d(XDATA, jpplotYDATA, PFit, PFitL, PFitU, nullptr, resids);
		array<double>^ newX = gcnew array<double>(jpplotXDATA->Length * 10);
		double step = (XDATA[jpplotXDATA->Length - 1] - XDATA[0]) / newX->Length;
		for (int i = 0; i < newX->Length; i++)
			newX[i] = XDATA[0] + double(i)*step;
		array<double>^ newY = gcnew array<double>(newX->Length);
		JPMath::Gaussian1d(newX, newY, PFit);

		plotchart1->SuspendDrawing();
		plotchart1->PlotXYData(XDATA, jpplotYDATA, "", "Radius (arcsec)", "Normalized Value at Radius", ::Charting::SeriesChartType::Point, "Radial");
		plotchart1->AddXYData(newX,newY, Charting::SeriesChartType::Line, "Gaussian Fit");
		String^ eq = "exp[-x^2 / (2*sigma^2)]";
		String^ title = eq + " : sigma = " + PFit[2].ToString("G5") + "; FWHM = " + (PFit[2]*2.355).ToString("G5") + "''";
		plotchart1->SetChartTitle(title);
		plotchart1->SetAxesLimits(0,XDATA[jpplotXDATA->Length-1],0,1);
		plotchart1->ResumeDrawing();

		if (FitMenuPlotResidualsChck->Checked)
		{
			if (FIT_RESIDUALS_PLOT == nullptr)
				FIT_RESIDUALS_PLOT = gcnew JPPlot();
			FIT_RESIDUALS_PLOT->Text = "Gaussian Fit Residuals";
			FIT_RESIDUALS_PLOT->plotchart1->PlotXYData(XDATA, resids, "Residuals", "Radius (arcsec)", "Residual", Charting::SeriesChartType::Point, "Residuals");
			FIT_RESIDUALS_PLOT->plotchart1->TightPlotAxes->Checked = true;
			FIT_RESIDUALS_PLOT->Show();
		}
	}
	else
	{
		array<double>^ PFit = gcnew array<double>(4);
		JPMath::Fit_Gaussian1d(jpplotXDATA, jpplotYDATA, PFit, nullptr, nullptr, nullptr, nullptr);
		array<double>^ newX = gcnew array<double>(jpplotXDATA->Length * 10);
		double step = (jpplotXDATA[jpplotXDATA->Length - 1] - jpplotXDATA[0]) / newX->Length;
		for (int i = 0; i < newX->Length; i++)
			newX[i] = jpplotXDATA[0] + double(i)*step;
		array<double>^ newY = gcnew array<double>(newX->Length);
		JPMath::Gaussian1d(newX, newY, PFit);

		for (int i = 0; i < newY->Length; i++)
			newX[i] = newX[i] + 0.5;

		plotchart1->SuspendDrawing();
		plotchart1->AddXYData(newX,newY, Charting::SeriesChartType::Line, "Gaussian Fit");
		String^ eq = "A*exp[-(x - B)^2 / (2*C^2)] + D";
		String^ title = eq + " : A = " + PFit[0].ToString("G5") + "; B = " + PFit[1].ToString("G6") + "; FWHM = " + (pixscale*PFit[2]*2.355).ToString("G5") + "''" + "; D = " + PFit[3].ToString("G5");
		plotchart1->SetChartTitle(title);
		plotchart1->ResumeDrawing();

		System::Windows::Forms::Clipboard::SetText(PFit[0].ToString() + "	" + PFit[1].ToString() + "	" + PFit[2].ToString() + "	" + PFit[3].ToString());
	}
}

void CCDLAB::JPPlot::FitMenuMoffat_Click(System::Object^  sender, System::EventArgs^  e)
{
	double pixscale = ::Convert::ToDouble(PixelScaleTxtBox->Text);
	if (pixscale <= 0)
		pixscale = 1;

	if (this->Text == "Radial Profile Plot")
	{
		array<double>^ XDATA = gcnew array<double>(jpplotXDATA->Length);
		for (int i = 0; i < jpplotXDATA->Length; i++)
			XDATA[i] = jpplotXDATA[i] * pixscale;

		array<double>^ PFit;// = gcnew array<double>(5) { 1, 0, 1, 1, 0 };
		//array<double>^ PFitL = gcnew array<double>(5) { 1, 0, XDATA[XDATA->Length - 1]/50, XDATA[XDATA->Length - 1]/50, 0 };
		//array<double>^ PFitU = gcnew array<double>(5) { 1, 0, XDATA[XDATA->Length - 1], XDATA[XDATA->Length - 1], 0 };
		array<double>^ resids;
		if (FitMenuPlotResidualsChck->Checked)
			resids = gcnew array<double>(XDATA->Length);
		//JPMath::Fit_Moffat1d(XDATA, jpplotYDATA, PFit, PFitL, PFitU, nullptr, resids);
		array<double>^ newX;// = gcnew array<double>(jpplotXDATA->Length * 10);
		//double step = (XDATA[jpplotXDATA->Length - 1] - XDATA[0]) / newX->Length;
		//for (int i = 0; i < newX->Length; i++)
		//	newX[i] = XDATA[0] + double(i)*step;
		array<double>^ newY;// = gcnew array<double>(newX->Length);
		//JPMath::Moffat1d(newX, newY, PFit);

		double fwhm;
		JPMath::Radial_Profile_Normalized_Fit_Moffat(XDATA, jpplotYDATA, PFit, fwhm, newX, newY);

		plotchart1->SuspendDrawing();
		plotchart1->PlotXYData(XDATA, jpplotYDATA, "", "Radius (arcsec)", "Normalized Value at Radius", ::Charting::SeriesChartType::Point, "Radial");
		plotchart1->AddXYData(newX,newY, Charting::SeriesChartType::Line, "Moffat Fit");
		String^ eq = "[1 + (x/alpha)^2]^(-beta)";
		String^ title = eq + " : alpha = " + PFit[2].ToString("G5") + "; beta = " + PFit[3].ToString("G5") + "; FWHM = " + (2*PFit[2]*Math::Sqrt(Math::Pow(2,1/PFit[3])-1)).ToString("G5") + "''";
		plotchart1->SetChartTitle(title);
		plotchart1->SetAxesLimits(0,XDATA[jpplotXDATA->Length-1],0,1);
		plotchart1->ResumeDrawing();

		if (FitMenuPlotResidualsChck->Checked)
		{
			if (FIT_RESIDUALS_PLOT == nullptr)
				FIT_RESIDUALS_PLOT = gcnew JPPlot();
			FIT_RESIDUALS_PLOT->Text = "Moffat Fit Residuals";
			FIT_RESIDUALS_PLOT->plotchart1->PlotXYData(XDATA, resids, "Residuals", "Radius (arcsec)", "Residual", Charting::SeriesChartType::Point, "Residuals");
			FIT_RESIDUALS_PLOT->plotchart1->TightPlotAxes->Checked = true;
			FIT_RESIDUALS_PLOT->Show();
		}
	}
	else
	{
		array<double>^ PFit = gcnew array<double>(5);
		JPMath::Fit_Moffat1d(jpplotXDATA, jpplotYDATA, PFit, nullptr, nullptr, nullptr, nullptr);
		array<double>^ newX = gcnew array<double>(jpplotXDATA->Length * 10);
		double step = (jpplotXDATA[jpplotXDATA->Length - 1] - jpplotXDATA[0]) / newX->Length;
		for (int i = 0; i < newX->Length; i++)
			newX[i] = jpplotXDATA[0] + double(i)*step;
		array<double>^ newY = gcnew array<double>(newX->Length);
		JPMath::Moffat1d(newX, newY, PFit);

		for (int i = 0; i < newY->Length; i++)
			newX[i] = newX[i] + 0.5;

		plotchart1->SuspendDrawing();
		plotchart1->AddXYData(newX,newY, Charting::SeriesChartType::Line, "Moffat Fit");
		String^ eq = "A*[1 + ((x-B)/C)^2]^(-D) + E";
		String^ title = eq + " : A = " + PFit[0].ToString("G5") + "; B = " + PFit[1].ToString("G6") + "; C = " + (PFit[2]).ToString("G5") + "; D = " + PFit[3].ToString("G5") + "; E = " + PFit[4].ToString("G5") + "; FWHM = " + (pixscale*2*PFit[2]*Math::Sqrt(Math::Pow(2,1/PFit[3])-1)).ToString("G5") + "''";
		plotchart1->SetChartTitle(title);
		plotchart1->ResumeDrawing();

		System::Windows::Forms::Clipboard::SetText(PFit[0].ToString() + "	" + PFit[1].ToString() + "	" + PFit[2].ToString() + "	" + PFit[3].ToString());
	}
}

void CCDLAB::JPPlot::PixelScaleTxtBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (PixelScaleTxtBox->Text == ".")
	{
		PixelScaleTxtBox->Text = "0.";
		return;
	}

	try
	{
		::Convert::ToDouble(PixelScaleTxtBox->Text);
	}
	catch (...)
	{
		PixelScaleTxtBox->Text = (String^)GetReg("CCDLAB","PixelScaleTxt");
		return;
	}
	SetReg("CCDLAB","PixelScaleTxt",PixelScaleTxtBox->Text);
}

void CCDLAB::JPPlot::JPPlotMenuItem_Fit_Click(System::Object^  sender, System::EventArgs^  e)
{
	
}

void CCDLAB::JPPlot::FitMenuPlotResidualsChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	JPPlotMenuItem_Fit->ShowDropDown();
	SetReg("CCDLAB", "JPPlotResiduals", FitMenuPlotResidualsChck->Checked);
}

