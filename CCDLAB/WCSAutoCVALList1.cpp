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
#include "WCSAutoCVALList1.h"

void CCDLAB::WCSAutoCVALList::WCDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	OKBtn->PerformClick();
}

void CCDLAB::WCSAutoCVALList::SearchTxtBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	WCDrop->Items->Clear();
	WCDrop->DroppedDown = true;
	if (SearchTxtBox->Text == nullptr || SearchTxtBox->Text == "")
	{
		WCDrop->Items->AddRange(ITEMLIST);
		WCDrop->DroppedDown = true;
		return;
	}

	for (int i = 0; i < ITEMLIST->Length; i++)
		if (ITEMLIST[i]->ToLower()->StartsWith(SearchTxtBox->Text->ToLower()))
			WCDrop->Items->Add(ITEMLIST[i]);

	WCDrop->DroppedDown = true;
}

