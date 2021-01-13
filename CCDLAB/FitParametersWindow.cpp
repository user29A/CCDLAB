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
#include "FitParametersWindow.h"
#include "Form1.h"

using namespace CCDLAB;

CCDLAB::FitParametersWindow::FitParametersWindow(int function_num, array<double>^ xrange, array<double>^ yrange, array<double, 2>^ roi)
{
	InitializeComponent();

	PITXTARRAY = gcnew array<Windows::Forms::TextBox^>(8);
	PLBTXTARRAY = gcnew array<Windows::Forms::TextBox^>(8);
	PUBTXTARRAY = gcnew array<Windows::Forms::TextBox^>(8);
	for (int i = 0; i < PITXTARRAY->Length; i++)
	{
		PITXTARRAY[i] = (Windows::Forms::TextBox^)(this->Controls->Find("P" + i + "ITxt", true)[0]);
		PLBTXTARRAY[i] = (Windows::Forms::TextBox^)(this->Controls->Find("P" + i + "LBTxt", true)[0]);
		PUBTXTARRAY[i] = (Windows::Forms::TextBox^)(this->Controls->Find("P" + i + "UBTxt", true)[0]);
	}

	Set_Function(function_num, xrange, yrange, roi);
	FUNCTION_SET = true;
	FUNCTION_NUM = function_num;
	FitFcnTxt->Text = FUNCTION;
	for (int i = NPARAMS; i < PITXTARRAY->Length; i++)
	{
		PITXTARRAY[i]->Enabled = false;
		PLBTXTARRAY[i]->Enabled = false;
		PUBTXTARRAY[i]->Enabled = false;
	}
}

void CCDLAB::FitParametersWindow::GetLastBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	for (int i = 0; i < NPARAMS; i++)
	{
		PITXTARRAY[i]->Text = (String^)(GetReg("CCDLAB", "FitP" + i + "I_" + FUNCTION_NUM));
		PLBTXTARRAY[i]->Text = (String^)(GetReg("CCDLAB", "FitP" + i + "LB_" + FUNCTION_NUM));
		PUBTXTARRAY[i]->Text = (String^)(GetReg("CCDLAB", "FitP" + i + "UB_" + FUNCTION_NUM));
	}
}

void CCDLAB::FitParametersWindow::Set_Function(int num, array<double>^ xrange, array<double>^ yrange, array<double, 2>^ roi)
{
	int xind, yind;
	double min = JPMath::Min(roi, false);
	double max = JPMath::Max(roi, xind, yind, false);
	double amp = max - min;
	double x0 = xrange[xind];
	double y0 = yrange[yind];
	double xwidth = xrange[xrange->Length - 1] - xrange[0];
	double ywidth = yrange[yrange->Length - 1] - yrange[0];

	//amplitude
	PITXTARRAY[0]->Text = amp.ToString();
	PLBTXTARRAY[0]->Text = min.ToString();
	PUBTXTARRAY[0]->Text = (max + amp).ToString();

	//x0
	PITXTARRAY[1]->Text = x0.ToString();
	PLBTXTARRAY[1]->Text = (x0 - xwidth * 5).ToString();
	PUBTXTARRAY[1]->Text = (x0 + xwidth * 5).ToString();

	//y0
	PITXTARRAY[2]->Text = y0.ToString();
	PLBTXTARRAY[2]->Text = (y0 - ywidth * 5).ToString();
	PUBTXTARRAY[2]->Text = (y0 + ywidth * 5).ToString();

	if (num == 0)
	{
		FUNCTION = "P(0)*exp(-[(X-P(1))^2 + (Y-P(2))^2]/(2*P(3)^2)) + P(4)";
		label1->Text = "Fit Function: Gaussian (2D Circular)";
		NPARAMS = 5;
		
		PITXTARRAY[3]->Text = "2";
		PLBTXTARRAY[3]->Text = "0";
		PUBTXTARRAY[3]->Text = (xwidth * 5).ToString();

	}

	if (num == 1)
	{
		FUNCTION = "P(0)*exp(-((X-P(1))*cos(P(3)) + (Y-P(2))*sin(P(3)))^2/(2*P(4)^2) - (-(X-P(1))*sin(P(3)) + (Y-P(2))*cos(P(3)))^2/(2*P(5)^2)) + P(6)";
		label1->Text = "Fit Function: Gaussian (2D Elliptical)";
		NPARAMS = 7;

		PITXTARRAY[3]->Text = "0";
		PLBTXTARRAY[3]->Text = (-Math::PI).ToString();
		PUBTXTARRAY[3]->Text = Math::PI.ToString();

		PITXTARRAY[4]->Text = "2";
		PLBTXTARRAY[4]->Text = "0";
		PUBTXTARRAY[4]->Text = (xwidth * 5).ToString();

		PITXTARRAY[5]->Text = "2";
		PLBTXTARRAY[5]->Text = "0";
		PUBTXTARRAY[5]->Text = (ywidth * 5).ToString();

	}

	if (num == 2)
	{
		FUNCTION = "P(0)*(1 + ((X - P(1))^2 + (Y - P(2))^2)/P(3)^2)^(-P(4)) + P(5)";
		label1->Text = "Fit Function: Moffat (2D Circular)";
		NPARAMS = 6;

		PITXTARRAY[3]->Text = "2";
		PLBTXTARRAY[3]->Text = "0";
		PUBTXTARRAY[3]->Text = (xwidth * 5).ToString();

		PITXTARRAY[4]->Text = "2";
		PLBTXTARRAY[4]->Text = "1";
		PUBTXTARRAY[4]->Text = (xwidth * 5).ToString();
	}

	if (num == 3)
	{
		FUNCTION = "P(0)*(1 + (((X-P(1))*cos(P(3)) + (Y-P(2))*sin(P(3)))^2)/P(4)^2 + ((-(X-P(1))*sin(P(3)) + (Y-P(2))*cos(P(3)))^2)/P(5)^2)^(-P(6)) + P(7)";
		label1->Text = "Fit Function: Moffat (2D Elliptical)";
		NPARAMS = 8;

		PITXTARRAY[3]->Text = "0";
		PLBTXTARRAY[3]->Text = (-Math::PI).ToString();
		PUBTXTARRAY[3]->Text = Math::PI.ToString();

		PITXTARRAY[4]->Text = "2";
		PLBTXTARRAY[4]->Text = "0";
		PUBTXTARRAY[4]->Text = (xwidth * 5).ToString();

		PITXTARRAY[5]->Text = "2";
		PLBTXTARRAY[5]->Text = "0";
		PUBTXTARRAY[5]->Text = (ywidth * 5).ToString();

		PITXTARRAY[6]->Text = "2";
		PLBTXTARRAY[6]->Text = "1";
		PUBTXTARRAY[6]->Text = (xwidth * 5).ToString();
	}

	//background
	PITXTARRAY[NPARAMS - 1]->Text = min.ToString();
	PLBTXTARRAY[NPARAMS - 1]->Text = (min - amp).ToString();
	PUBTXTARRAY[NPARAMS - 1]->Text = (min + amp).ToString();
}

void CCDLAB::FitParametersWindow::P0ITxt_Enter(System::Object^  sender, System::EventArgs^  e)
{
	Windows::Forms::TextBox^ obj = (Windows::Forms::TextBox^)sender;
	LASTTEXT = obj->Text;
}

void CCDLAB::FitParametersWindow::P0ITxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	Windows::Forms::TextBox^ obj = (Windows::Forms::TextBox^)sender;

	if (obj->Text == "-" || obj->Text == "-." || obj->Text == "." || obj->Text == "+" || obj->Text == "+." || obj->Text == "")
		return;
	if (obj->Text->Length > 0)
		if (obj->Text->Substring(obj->Text->Length - 1)->ToLower() == "e")
			return;
	if (obj->Text->Length > 1)
		if (obj->Text->Substring(obj->Text->Length - 2)->ToLower() == "e+" || obj->Text->Substring(obj->Text->Length - 2)->ToLower() == "e-")
			return;

	try
	{
		Convert::ToDouble(obj->Text);
	}
	catch (...)
	{
		obj->Text = LASTTEXT;
	}

	LASTTEXT = obj->Text;
}

void CCDLAB::FitParametersWindow::FitParametersWindow_Load(System::Object^  sender, System::EventArgs^  e)
{
	if (Convert::ToBoolean(GetReg("CCDLAB", "FitConstrain")))
		ConstrainBtn->Checked = true;
}

void CCDLAB::FitParametersWindow::FitParametersWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
}

void CCDLAB::FitParametersWindow::SetParamsBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	for (int i = 0; i < NPARAMS; i++)
	{
		SetReg("CCDLAB", "FitP" + i + "I_" + FUNCTION_NUM, PITXTARRAY[i]->Text);
		SetReg("CCDLAB", "FitP" + i + "LB_" + FUNCTION_NUM, PLBTXTARRAY[i]->Text);
		SetReg("CCDLAB", "FitP" + i + "UB_" + FUNCTION_NUM, PUBTXTARRAY[i]->Text);
	}
	this->Close();
}

void CCDLAB::FitParametersWindow::ConstrainBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (ConstrainBtn->Checked)
		BoundsPnl->Enabled = true;
	else
		BoundsPnl->Enabled = false;
	
	SetReg("CCDLAB", "FitConstrain", ConstrainBtn->Checked);
}

