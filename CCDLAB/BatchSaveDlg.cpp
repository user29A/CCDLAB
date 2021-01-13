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
#include "BatchSaveDlg.h"
#include "Form1.h"


void CCDLAB::BatchSaveDlg::DirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e) 
{
	UseOrigDirChck->Checked = false;

	FolderDlg->SelectedPath = DirectoryTxt->Text;
	FolderDlg->ShowDialog();
	String^ dir = FolderDlg->SelectedPath;
	if (!dir->EndsWith("\\"))
	{
		dir = String::Concat(dir,"\\");
	}
	DirectoryTxt->Text = dir;
}

void CCDLAB::BatchSaveDlg::BatchSaveDlg_Shown(System::Object^  sender, System::EventArgs^  e)
{
	//get appendage
	AppendTxt->Text = (String^)GetReg("CCDLAB", "Appendage");

	//get directory
	DirectoryTxt->Text = (String^)GetReg("CCDLAB", "BatchSavePath");

	//get file extension index
	FileExtension->SelectedIndex = ::Convert::ToInt32(GetReg("CCDLAB", "FileExtensionIndex"));

	//get UseOrigDir state
	UseOrigDirChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "BatchSaveUseOrigDir"));
}

void CCDLAB::BatchSaveDlg::AppendBtnChangeBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (AppendBtn->Text == "Append")
	{
		AppendBtn->Text = "Remove";
		toolTip1->SetToolTip(AppendBtn, "This will remove the text below from the file name, thus, the original files will not be overwritten.  If no text is entered, you will receive an error notification.");
	}
	else if (AppendBtn->Text == "Remove")
	{
		AppendBtn->Text = "Remove Aft";
		toolTip1->SetToolTip(AppendBtn, "This will remove everything after the text below from the file name, thus, the original files will not be overwritten.  If no text is entered, you will receive an error notification.");
	}
	else if (AppendBtn->Text == "Remove Aft")
	{
		AppendBtn->Text = "Append";
		toolTip1->SetToolTip(AppendBtn, "This will append the text below to the file name, thus, the original files will not be overwritten.  If no text is entered, you will receive an error notification.");
	}
}

void CCDLAB::BatchSaveDlg::AppendBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	//write extension index
	SetReg("CCDLAB", "FileExtensionIndex",FileExtension->SelectedIndex.ToString());

	//write appendage
	SetReg("CCDLAB", "Appendage",AppendTxt->Text);

	//write save path
	SetReg("CCDLAB", "BatchSavePath",DirectoryTxt->Text);

	//write UseOrigDir state
	SetReg("CCDLAB", "BatchSaveUseOrigDir",UseOrigDirChck->Checked.ToString());
}

void CCDLAB::BatchSaveDlg::OverwriteBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	//write extension index
	SetReg("CCDLAB", "FileExtensionIndex",FileExtension->SelectedIndex.ToString());

	//write save path
	SetReg("CCDLAB", "BatchSavePath",DirectoryTxt->Text);

	//write UseOrigDir state
	SetReg("CCDLAB", "BatchSaveUseOrigDir",UseOrigDirChck->Checked.ToString());
}

void CCDLAB::BatchSaveDlg::UseOrigDirChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	Form1^ f = (Form1^)this->Owner;

	if (UseOrigDirChck->Checked)
	{
		String^ paths = f->IMAGESET[0]->FilePath + "\r\n";
		String^ currentPath = f->IMAGESET[0]->FilePath;

		for (int i = 1; i < f->IMAGESET->Count; i++)
		{
			if (f->IMAGESET[i]->FilePath != currentPath)
			{
				currentPath = f->IMAGESET[i]->FilePath;
				paths += currentPath + "\r\n";
			}
		}

		DirectoryTxt->Text = paths;
	}
	else
	{
		//get directory
		DirectoryTxt->Text = (String^)GetReg("CCDLAB", "BatchSavePath");
	}
}

void CCDLAB::BatchSaveDlg::GetCommonDirectoryBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	Form1^ f = (Form1^)this->Owner;

	String^ comdir = f->IMAGESET->GetCommonDirectory();
	if (!comdir->EndsWith("\\"))
		comdir = String::Concat(comdir, "\\");
	DirectoryTxt->Text = comdir;
}

