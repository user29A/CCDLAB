#include "stdafx.h"
#include "ImageExtensionsSaver.h"

CCDLAB::ImageExtensionsSaver::ImageExtensionsSaver(JPFITS::FITSImageSet^ imageSet, ListBox^ list)
{
	InitializeComponent();

	HEADERLISTBOX = list;

	IMAGESET = imageSet;
	extensionsGridView->RowCount = imageSet->Count;
	String^ extname;
	for (int i = 0; i < extensionsGridView->RowCount; i++)
	{
		extname = imageSet[i]->Header->GetKeyValue("EXTNAME");
		if (extname != "")
			extensionsGridView[0, i]->Value = extname;
		else
			extensionsGridView[0, i]->Value = (i + 1).ToString("000000");
		
		int bzero = 0;
		try
		{
			Convert::ToInt32(imageSet[i]->Header->GetKeyValue("BZERO"));
		}
		catch (...) {}

		extensionsGridView->Rows[i]->Cells[1]->Value = BITPIXtoString(Convert::ToInt32(imageSet[i]->Header->GetKeyValue("BITPIX")), bzero);
	}
}

void CCDLAB::ImageExtensionsSaver::FirstAsPrimaryChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (FirstAsPrimaryChck->Checked)
	{
		AppendIntoFileChck->Enabled = false;
		ViewEditPrimaryHeaderBtn->Enabled = false;
		ViewEditPrimaryHeaderBtn->Checked = false;
		HEADERLISTBOX->Visible = false;
	}
	else
	{
		AppendIntoFileChck->Enabled = true;
		ViewEditPrimaryHeaderBtn->Enabled = true;
	}
}

void CCDLAB::ImageExtensionsSaver::AppendIntoFileChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (AppendIntoFileChck->Checked)
	{
		FirstAsPrimaryChck->Enabled = false;
		ViewEditPrimaryHeaderBtn->Enabled = false;
	}
	else
	{
		FirstAsPrimaryChck->Enabled = true;
		ViewEditPrimaryHeaderBtn->Enabled = true;
	}
}

void CCDLAB::ImageExtensionsSaver::ViewEditPrimaryHeaderBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewEditPrimaryHeaderBtn->Checked)
	{
		if (this->HEADER == nullptr)
			HEADER = gcnew JPFITS::FITSImageHeader(true, nullptr);

		HEADERLISTBOX->Items->Clear();
		HEADERLISTBOX->Items->AddRange(HEADER->GetFormattedHeaderBlock(false, true));
		HEADERLISTBOX->Visible = true;
	}
	else
		HEADERLISTBOX->Visible = false;
}

void CCDLAB::ImageExtensionsSaver::SaveBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ sfd = gcnew SaveFileDialog();
	sfd->Filter = "FITS|*.fits;*.fit;*.fts|All|*.*";
	sfd->InitialDirectory = IMAGESET->GetCommonDirectory();
	if (AppendIntoFileChck->Checked)
		sfd->OverwritePrompt = false;
	if (sfd->ShowDialog() == Windows::Forms::DialogResult::Cancel)
		return;

	FILENAME = sfd->FileName;
	EXTENSIONNAMES = gcnew array<String^>(extensionsGridView->RowCount);
	PRECISIONTYPECODES = gcnew array<TypeCode>(extensionsGridView->RowCount);

	for (int i = 0; i < extensionsGridView->RowCount; i++)
	{
		EXTENSIONNAMES[i] = (String^)extensionsGridView[0, i]->Value;
		PRECISIONTYPECODES[i] = BITPIXStringToTYPECODE((String^)extensionsGridView[1, i]->Value);
	}

	if (ViewEditPrimaryHeaderBtn->Checked)
		HEADERLISTBOX->Visible = false;
	if (FirstAsPrimaryChck->Checked)
		HEADER = nullptr;
	else
	{
		ArrayList^ list = gcnew ArrayList();
		list->AddRange(HEADERLISTBOX->Items);
		HEADER = gcnew JPFITS::FITSImageHeader(list, true);
	}

	this->Close();
}

void CCDLAB::ImageExtensionsSaver::CancelBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewEditPrimaryHeaderBtn->Checked)
		HEADERLISTBOX->Visible = false;

	this->Close();
}

void CCDLAB::ImageExtensionsSaver::ImageExtensionsSaver_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	this->Activate();
}

System::String^ CCDLAB::ImageExtensionsSaver::BITPIXtoString(int bitPix, int bZero)
{
	switch (bitPix)
	{
		case (16):
		{
			if (bZero == 0)
				return "int16";
			else
				return "uint16";
			break;
		}

		case (32):
		{
			if (bZero == 0)
				return "int32";
			else
				return "uint32";
			break;
		}

		case (64):
		{
			if (bZero == 0)
				return "int64";
			else
				return "uint64";
			break;
		}

		case (-32):
		{
			return "float";
			break;
		}

		case (-64):
		{
			return "double";
			break;
		}
	}

	return "double";
}

System::TypeCode CCDLAB::ImageExtensionsSaver::BITPIXStringToTYPECODE(String^ bitpixstr)
{
	if (bitpixstr == "int16")
		return TypeCode::Int16;
	else if (bitpixstr == "uint16")
		return TypeCode::UInt16;
	if (bitpixstr == "int32")
		return TypeCode::Int32;
	else if (bitpixstr == "uint32")
		return TypeCode::UInt32;
	if (bitpixstr == "int64")
		return TypeCode::Int64;
	else if (bitpixstr == "uint64")
		return TypeCode::UInt64;
	else if (bitpixstr == "float")
		return TypeCode::Single;
	else
		return TypeCode::Double;
}