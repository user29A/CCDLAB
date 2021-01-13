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
#include "PSETableViewer.h"

void CCDLAB::PSETableViewer::PSETableViewerSaveBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	SaveFileDialog^ sfd = gcnew SaveFileDialog();
	sfd->Filter = "Tab Delimited Text|*.txt|CSV (Comma Delimited)|*.csv";//|FITS Binary Table|*.fits";
	sfd->FilterIndex = Convert::ToInt32(GetReg("CCDLAB", "PSESaveFilter"));
	sfd->InitialDirectory = (String^)GetReg("CCDLAB", "PSESavePath");
	sfd->FileName = "a" + ((CCDLAB::Form1^)(this->Owner))->SubImageRATxt->Text + "d" + ((CCDLAB::Form1^)(this->Owner))->SubImageDecTxt->Text;
	if (sfd->FileName->Contains("a0d0"))
		sfd->FileName = "";
	if (sfd->ShowDialog() == ::DialogResult::Cancel)
		return;
	SetReg("CCDLAB", "PSESavePath", sfd->FileName->Substring(0, sfd->FileName->LastIndexOf("\\")));
	SetReg("CCDLAB", "PSESaveFilter", sfd->FilterIndex);

	if (sfd->FilterIndex < 3)
	{
		String^ delimit;
		if (sfd->FilterIndex == 1)
			delimit = "\t";
		else
			delimit = ",";

		StreamWriter^ sw = gcnew StreamWriter(sfd->FileName);
		String^ str = "";

		for (int i = 0; i < PSETable->ColumnCount; i++)
			str += PSETable->Columns[i]->HeaderText + delimit;
		str = str->Substring(0, str->Length - 1);
		sw->WriteLine(str);

		for (int j = 0; j < PSETable->RowCount; j++)
		{
			str = "";
			for (int i = 0; i < PSETable->ColumnCount; i++)
				str += PSETable[i, j]->Value + delimit;
			str = str->Substring(0, str->Length - 1);
			sw->WriteLine(str);
		}

		sw->Close();
	}
	else//fits bin table
	{
		//can't actually do this because a PSE table has both numeric and text entries...so not all simply binary numbers
		//would need to do an ascii table instead
		//so...need to write ascii table for the JPFITS pkg

		/*array<String^>^ labels = gcnew array<String^>(PSETable->ColumnCount);
		array<TypeCode>^ types = gcnew array<TypeCode>(PSETable->ColumnCount);
		array<int>^ instances = gcnew array<int>(PSETable->ColumnCount);
		array<String^>^ units = gcnew array<String^>(PSETable->ColumnCount);
		array<Object^>^ data = gcnew array<Object^>(PSETable->ColumnCount);

		for (int i = 0; i < PSETable->ColumnCount; i++)
		{
			labels[i] = PSETable->Columns[i]->HeaderText;
			types[i] = 
		}

		JPFITS::FITSBinTable::BinaryTableExtension_Write(sfd->FileName, "", true, labels, types, instances, units, nullptr, nullptr, nullptr, data)*/
	}
}

void CCDLAB::PSETableViewer::PSETable_CellMouseDoubleClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e)
{
	try
	{
		double x, y;
		if (PSETable->Columns[1]->HeaderText == "P1")
		{
			x = Convert::ToDouble(PSETable[1, e->RowIndex]->Value->ToString());
			y = Convert::ToDouble(PSETable[2, e->RowIndex]->Value->ToString());
		}
		else
		{
			x = Convert::ToDouble(PSETable[0, e->RowIndex]->Value->ToString());
			y = Convert::ToDouble(PSETable[1, e->RowIndex]->Value->ToString());
		}

		((CCDLAB::Form1^)(this->Owner))->PSESeachROIOnlyChck->SuspendLayout();
		((CCDLAB::Form1^)(this->Owner))->PSESeachROIOnlyChck->Checked = false;
		((CCDLAB::Form1^)(this->Owner))->PSESeachROIOnlyChck->ResumeLayout();

		((CCDLAB::Form1^)(this->Owner))->SubImageSlideX->Value = (int)x + 1;
		((CCDLAB::Form1^)(this->Owner))->SubImageSlideY->Value = (int)y + 1;
		((CCDLAB::Form1^)(this->Owner))->SubImageStatsUpD();
		((CCDLAB::Form1^)(this->Owner))->SubImageUpD();
		((CCDLAB::Form1^)(this->Owner))->ShowCrosshair->Checked = true;
		((CCDLAB::Form1^)(this->Owner))->ImageWindow->Refresh();
	}
	catch (...) {}
}

