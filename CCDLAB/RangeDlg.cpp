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
#include "RangeDlg.h"

void CCDLAB::RangeDlg::RangeDlg_HelpButtonClicked(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		MessageBox::Show("A value of -1 for XStart will cause the full-frame files to load regardless of the other values.\r\rValues of"
			" -1 for XEnd or YEnd or values greater than the actual image size will revert to the actual image size.\r\rValues of XEnd or YEnd"
			" greater(less??) than or equal to XStart or YStart will cause a fits image to be loaded with no image data, likely causing an error.");
	}

