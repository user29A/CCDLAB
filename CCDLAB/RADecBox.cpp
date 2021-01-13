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
#include "RADecBox.h"
#include "Form1.h"

void ::CCDLAB::RADecBox::RAToggle_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (RAToggle->Checked)//display as deg.deg
	{
		RADegTxt->Visible = true;
		RADegTxt->BringToFront();
		RAToggle->Text = "RA: h m s";
		double radeg = ::Convert::ToDouble(RAhTxt->Text)/24*360 + ::Convert::ToDouble(RAmTxt->Text)/60/24*360 + ::Convert::ToDouble(RAsTxt->Text)/3600/24*360;
		RADegTxt->Text = Math::Round(radeg,7).ToString();
	}
	else//display as h m s
	{
		RADegTxt->Visible = false;
		RAToggle->Text = "RA: deg.deg";
		double radeg = ::Convert::ToDouble(RADegTxt->Text);

		if (radeg < 0)
			radeg += 360;

		double h = Math::Floor(radeg/360*24);
		double m = Math::Floor((radeg/360*24 - h)*60);
		double s = Math::Round((radeg/360*24 - h - m/60)*3600,2);

		RAhTxt->Text = h.ToString();
		RAmTxt->Text = m.ToString();
		RAsTxt->Text = s.ToString();
	}

	SetReg("CCDLAB","RADecBox_RAToggle",RAToggle->Checked);
}

void ::CCDLAB::RADecBox::DecToggle_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (DecToggle->Checked)//display as deg.deg
	{
		DecDegTxt->Visible = true;
		DecSignBtn->Visible = false;
		DecDegTxt->BringToFront();
		DecToggle->Text = "Dec: d ' ''";
		double decdeg = ::Convert::ToDouble(DecADTxt->Text) + ::Convert::ToDouble(DecAMTxt->Text)/60 + ::Convert::ToDouble(DecASTxt->Text)/3600;
		if (DecSignBtn->Text == "-")
			decdeg *= -1;			
		DecDegTxt->Text = Math::Round(decdeg,7).ToString();
	}
	else//display as d ' ''
	{
		DecDegTxt->Visible = false;
		DecSignBtn->Visible = true;
		DecToggle->Text = "Dec: deg.deg";
		double decdeg = Math::Abs(::Convert::ToDouble(DecDegTxt->Text));

		double d = Math::Floor(decdeg);
		double am = Math::Floor((decdeg - d)*60);
		double as = Math::Round((decdeg - d - am/60)*3600,2);
		if (::Convert::ToDouble(DecDegTxt->Text) < 0)
			DecSignBtn->Text = "-";
		else
			DecSignBtn->Text = "+";

		DecADTxt->Text = d.ToString();
		DecAMTxt->Text = am.ToString();
		DecASTxt->Text = as.ToString();
	}

	SetReg("CCDLAB","RADecBox_DecToggle",DecToggle->Checked);
}

void ::CCDLAB::RADecBox::DecSignBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (DecSignBtn->Text == "+")
		DecSignBtn->Text = "-";
	else
		DecSignBtn->Text = "+";
}

void ::CCDLAB::RADecBox::OKBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (RAToggle->Checked)//is displayed as deg.deg
		RIGHT_ASCENSION = ::Convert::ToDouble(RADegTxt->Text);
	else
		RIGHT_ASCENSION = ::Convert::ToDouble(RAhTxt->Text)/24*360 + ::Convert::ToDouble(RAmTxt->Text)/60/24*360 + ::Convert::ToDouble(RAsTxt->Text)/3600/24*360;

	if (DecToggle->Checked)//is displayed as deg.deg
		DECLINATION = ::Convert::ToDouble(DecDegTxt->Text);
	else
	{
		DECLINATION = ::Convert::ToDouble(DecADTxt->Text) + ::Convert::ToDouble(DecAMTxt->Text) / 60 + ::Convert::ToDouble(DecASTxt->Text) / 3600;
		if (DecSignBtn->Text == "-")
			DECLINATION *= -1;
	}
	
	SetReg("CCDLAB","RADecBox_RA",RIGHT_ASCENSION.ToString());
	SetReg("CCDLAB","RADecBox_Dec",DECLINATION.ToString());
	SetReg("CCDLAB", "RADecBoxLeft", this->Left);
	SetReg("CCDLAB", "RADecBoxTop", this->Top);
	SetReg("CCDLAB", "RADecBoxWidth", this->Width);
	SetReg("CCDLAB", "RADecBoxHeight", this->Height);
}

void ::CCDLAB::RADecBox::RADecBox_Load(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		this->Left = (int)GetReg("CCDLAB", "RADecBoxLeft");
		this->Top = (int)GetReg("CCDLAB", "RADecBoxTop");
		this->Width = (int)GetReg("CCDLAB", "RADecBoxWidth");
		this->Height = (int)GetReg("CCDLAB", "RADecBoxHeight");
	}
	catch (...) {}

	RIGHT_ASCENSION = ::Convert::ToDouble(GetReg("CCDLAB","RADecBox_RA"));
	RADegTxt->Text = RIGHT_ASCENSION.ToString();
	double h = Math::Floor(RIGHT_ASCENSION/360*24);
	double m = Math::Floor((RIGHT_ASCENSION/360*24 - h)*60);
	double s = Math::Round((RIGHT_ASCENSION/360*24 - h - m/60)*3600,2);
	RAhTxt->Text = h.ToString();
	RAmTxt->Text = m.ToString();
	RAsTxt->Text = s.ToString();
	RAToggle->Checked = ::Convert::ToBoolean(GetReg("CCDLAB","RADecBox_RAToggle"));

	DECLINATION = ::Convert::ToDouble(GetReg("CCDLAB","RADecBox_Dec"));
	DecDegTxt->Text = DECLINATION.ToString();
	double decdeg = Math::Abs(::Convert::ToDouble(DecDegTxt->Text));
	double d = Math::Floor(decdeg);
	double am = Math::Floor((decdeg - d)*60);
	double as = Math::Round((decdeg - d - am/60)*3600,2);
	if (DECLINATION < 0)
		DecSignBtn->Text = "-";
	else
		DecSignBtn->Text = "+";
	DecADTxt->Text = d.ToString();
	DecAMTxt->Text = am.ToString();
	DecASTxt->Text = as.ToString();
	DecToggle->Checked = ::Convert::ToBoolean(GetReg("CCDLAB","RADecBox_DecToggle"));
}

void ::CCDLAB::RADecBox::RADegTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (RADegTxt->Text == "-" || RADegTxt->Text == "-." || RADegTxt->Text == ".")
		return;

	if (RADegTxt->Text->Contains(" "))//for full hms, damas////convert and enter into txtboxes
	{
		double h, m, s, d, am, as;
		int lastind = 0;
		int nextind = RADegTxt->Text->IndexOf(" ", lastind);
		h = Convert::ToDouble(RADegTxt->Text->Substring(lastind, nextind - lastind));
		lastind = nextind + 1;
		nextind = RADegTxt->Text->IndexOf(" ", lastind);
		m = Convert::ToDouble(RADegTxt->Text->Substring(lastind, nextind - lastind));
		lastind = nextind + 1;
		nextind = RADegTxt->Text->IndexOf(" ", lastind);
		s = Convert::ToDouble(RADegTxt->Text->Substring(lastind, nextind - lastind));
		lastind = nextind + 1;
		nextind = RADegTxt->Text->IndexOf(" ", lastind);
		d = Convert::ToDouble(RADegTxt->Text->Substring(lastind, nextind - lastind));
		lastind = nextind + 1;
		nextind = RADegTxt->Text->IndexOf(" ", lastind);
		am = Convert::ToDouble(RADegTxt->Text->Substring(lastind, nextind - lastind));
		lastind = nextind + 1;
		as = Convert::ToDouble(RADegTxt->Text->Substring(lastind));

		double radeg = h / 24 * 360 + m / 60 / 24 * 360 + s / 3600 / 24 * 360;
		RADegTxt->Text = Math::Round(radeg, 9).ToString();

		double decdeg = Math::Abs(d) + am / 60 + as / 3600;
		if (d < 0)
			decdeg *= -1;
		DecDegTxt->Text = Math::Round(decdeg, 9).ToString();
		if (decdeg < 0)
			DecSignBtn->Text = "-";
		else
			DecSignBtn->Text = "+";
	}

	try
	{
		::Convert::ToDouble(RADegTxt->Text);
	}
	catch (...)
	{
		RADegTxt->Text = "0";
	}
}

void ::CCDLAB::RADecBox::DecTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (DecDegTxt->Text == "-" || DecDegTxt->Text == "-." || DecDegTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(DecDegTxt->Text);
	}
	catch (...)
	{
		DecDegTxt->Text = "0";
	}
}

void ::CCDLAB::RADecBox::RAhTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(RAhTxt->Text);
	}
	catch (...)
	{
		RAhTxt->Text = "0";
	}
}

void ::CCDLAB::RADecBox::RAmTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(RAmTxt->Text);
	}
	catch (...)
	{
		RAmTxt->Text = "0";
	}
}

void ::CCDLAB::RADecBox::RAsTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(RAsTxt->Text);
	}
	catch (...)
	{
		RAsTxt->Text = "0";
	}
}


void ::CCDLAB::RADecBox::DecADTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(DecADTxt->Text);
	}
	catch (...)
	{
		DecADTxt->Text = "0";
	}
}

void ::CCDLAB::RADecBox::DecAMTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(DecAMTxt->Text);
	}
	catch (...)
	{
		DecAMTxt->Text = "0";
	}
}

void ::CCDLAB::RADecBox::DecASTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(DecASTxt->Text);
	}
	catch (...)
	{
		DecASTxt->Text = "0";
	}
}

void CCDLAB::RADecBox::DecTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void CCDLAB::RADecBox::RADegTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void CCDLAB::RADecBox::RAhTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void CCDLAB::RADecBox::RAmTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void CCDLAB::RADecBox::RAsTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void ::CCDLAB::RADecBox::DecADTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void ::CCDLAB::RADecBox::DecAMTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void ::CCDLAB::RADecBox::DecASTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyData == Windows::Forms::Keys::Enter)
		OKBtn->PerformClick();
}

void CCDLAB::RADecBox::DecTxt_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
}

void CCDLAB::RADecBox::RADecBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
}

