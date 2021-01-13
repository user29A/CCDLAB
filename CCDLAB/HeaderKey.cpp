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
#include "HeaderKey.h"

void CCDLAB::HeaderKey::textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
}

void CCDLAB::HeaderKey::textBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
}

void CCDLAB::HeaderKey::textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyCode == ::Keys::Escape)
	{
		this->DialogResult = ::DialogResult::Cancel;
	}

	if (e->KeyCode == ::Keys::Enter)
	{
		SetReg("CCDLAB", "NormHeaderKey",textBox1->Text);
		this->DialogResult = ::DialogResult::OK;
	}

	//e->SuppressKeyPress = true;
}

void CCDLAB::HeaderKey::HeaderKey_Load(System::Object^  sender, System::EventArgs^  e)
{
	textBox1->Text = (String^)GetReg("CCDLAB", "NormHeaderKey");
}

