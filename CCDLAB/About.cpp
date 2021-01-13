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
#include "About.h"
#include "Form1.h"


void CCDLAB::About::About_Load(System::Object^  sender, System::EventArgs^  e)
{
	//::System::DateTime^ now = ::System::DateTime::Now;

	//::System::DateTime^ now = ::File::GetLastAccessTimeUtc(::Directory::GetCurrentDirectory());

	String^ s = "CCDLAB for Ultra Violet Imaging Telescope support." + "\r\n" + "\r\n" + "Release Date: " +
		/*now->Year.ToString() + "-" +
		now->Month.ToString("00") + "-" +
		now->Day.ToString("00") + " " + now->Hour.ToString("00") + ":" + now->Minute.ToString("00") + ":" + now->Second.ToString("00") + " UTC" +*/
		"2017-10-17 09:00:00 MDT" +
		"\r\n" + "\r\n" +
		"Developer:  Joeseph E Postma.  Copyright." + "\r\n" + "\r\n" +
		"Contact:  joepostma@live.ca" + "\r\n" + "\r\n" +
		/*"License:  This software is distributed under Creative Commons license 'Attribution-NonCommercial-NoDerivatives 4.0 International' (CC BY - NC - ND 4.0).  " + "\r\n" +
		"License summary and a link to the full license code can be found here:  https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.";*/
		"License: This software is released under GNU Public General License v 3.0 (GPLv3)." + "\r\n" +
		"License summary and a link to the full license code can be found here:  http://www.gnu.org/licenses/";
	

	AboutTextLabel->Text = s;
}

