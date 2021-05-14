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
#include "Form1.h"

using namespace CCDLAB;


void Form1::BatchMakeListBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	FITSFINDER = gcnew JPFITS::FitsFinder();
	FITSFINDER->ShowDialog();

	if ((::DialogResult)FITSFINDER->Tag == ::DialogResult::Cancel)//search was cancelled
	{
		BatchMakeListBtn->PerformClick();
		return;
	}

	if (FITSFINDER->DialogResult == ::DialogResult::OK)
	{
		int numfilesfound = FITSFINDER->FOUNDFILES->Length;
		if (numfilesfound == 0)//no files found
		{
			::MessageBox::Show("No Files Found Matching File Extension or Search Criteria...","Warning");
			BatchMakeListBtn->PerformClick();
		}
		else//found some files, so now make string array of just file names for showing in FO list below
		{
			FITSFINDERFILES = FITSFINDER->FOUNDFILES;

			FITSFOUND = gcnew JPFITS::FitsFound();
			FITSFOUND->LoadImageSetBtn->Text = "Use Selected for Batch List";
			FITSFOUND->AddImageSetBtn->Enabled = false;
			FITSFOUND->NumFilesTxt->Text = "Please Choose File(s) to Save...";
			FITSFOUND->Text = System::String::Concat("Found ",numfilesfound.ToString()," files...");
			FITSFOUND->FileListTxt->BeginUpdate();
			FITSFOUND->FileListTxt->Items->AddRange(FITSFINDERFILES);
			FITSFOUND->FileListTxt->EndUpdate();
			FITSFOUND->ShowDialog();
			int Ninds = FITSFOUND->FileListTxt->SelectedIndices->Count;
			if (Ninds == 0 && FITSFOUND->DialogResult != System::Windows::Forms::DialogResult::Cancel)//no files selected but asked to load files (!cancel)
			{
				::MessageBox::Show("No Files Selected!...","Error");
				BatchMakeListBtn->PerformClick();
			}
			else
			{
				array<String^>^ selectfiles = gcnew array<String^>(Ninds);
				for (int j = 0; j < Ninds; j++)
				{
					selectfiles[j] = FITSFINDERFILES[FITSFOUND->FileListTxt->SelectedIndices[j]];
				}
				if (FITSFOUND->DialogResult == System::Windows::Forms::DialogResult::Cancel)
				{
					BatchMakeListBtn->PerformClick();
					return;
				}
				if (FITSFOUND->DialogResult == ::DialogResult::OK)//then just Use Selected for Batch List
				{
					BATCHLIST = selectfiles;
					BatchListNameTxt->Text = String::Concat("List: ",BATCHLIST->Length.ToString()," files.");
					BatchListViewPanel->Text = "Quick Viewing: File 0 of " + BATCHLIST->Length.ToString();
					BatchGoToUpD->Maximum = BATCHLIST->Length;
					BatchListViewPanel->Enabled = true;
					BatchComputeBtn->Enabled = true;
				}
				else//the only other option is the list was saved
				{
					String^ filelist = Convert::ToString(GetReg("CCDLAB", "FoundFileList"));
					FileStream^ fs = gcnew FileStream(filelist, ::FileMode::Open);
					StreamReader^ sr = gcnew StreamReader(fs);
					int NFiles = ::Convert::ToInt32(sr->ReadLine());
					BATCHLIST = gcnew array<String^>(NFiles);
					for (int i = 0; i < NFiles; i++)
						BATCHLIST[i] = sr->ReadLine();
					sr->Close();
					fs->Close();
					BatchListNameTxt->Text = String::Concat("List: ",filelist->Substring(filelist->LastIndexOf("\\")+1),", ",NFiles," files.");
					BatchListViewPanel->Text = "Quick Viewing: File 0 of " + NFiles.ToString();
					BatchGoToUpD->Maximum = NFiles;
					BatchListViewPanel->Enabled = true;
					BatchComputeBtn->Enabled = true;
				}
			}
		}
	}
}

void Form1::BatchOpenListBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "CCDLAB File List (*.CFL)|*.CFL";
	
	if (dlg->ShowDialog() != ::DialogResult::OK)
		return;

	FileStream^ fs = gcnew FileStream(dlg->FileName, ::FileMode::Open);
	StreamReader^ sr = gcnew StreamReader(fs);
	int NFiles = ::Convert::ToInt32(sr->ReadLine());
	BATCHLIST = gcnew array<String^>(NFiles);
	for (int i = 0; i < NFiles; i++)
	{
		BATCHLIST[i] = sr->ReadLine();
		::FileInfo^ f = gcnew FileInfo(BATCHLIST[i]);
		if (!f->Exists)
		{
			::MessageBox::Show("Some of the files don't exist on the specified path.  The list file may be old.","Error...");
			sr->Close();
			fs->Close();
			return;
		}
	}
	sr->Close();
	fs->Close();
	BatchComputeBtn->Enabled = true;
	BatchListNameTxt->Text = String::Concat("List: ",dlg->FileName->Substring(dlg->FileName->LastIndexOf("\\")+1),", ",NFiles," files.");
	BatchListViewPanel->Text = "Quick Viewing: File 0 of " + NFiles.ToString();
	BatchGoToUpD->Maximum = NFiles;
	BatchListViewPanel->Enabled = true;

}

void Form1::BatchScanDirectoryBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (BatchScanDirectoryFileTypeDrop->SelectedIndex == -1)
		BatchScanDirectoryFileTypeDrop->SelectedIndex = 0;

	::FolderBrowserDialog^ fdlg = gcnew ::FolderBrowserDialog();

	String^ VISdir = (String^)GetReg("CCDLAB", "L2EventListPath") + "\\VIS";
	if (Directory::Exists(VISdir))
	{
		fdlg->SelectedPath = VISdir;
		BatchQuickScanSubDirsChck->Checked = true;

		String^ vismedian = VISdir + "\\median.fts";
		if (File::Exists(vismedian))
		{
			BATCHBIASIMG = gcnew FITSImage(vismedian, nullptr, false, true, false, true);
			BatchSubtractImageChck->Checked = true;
		}
	}
	else
		fdlg->SelectedPath = (String^)GetReg("CCDLAB", "FolderBrowserPath");

	if (!Directory::Exists(VISdir) && fdlg->ShowDialog() == ::DialogResult::Cancel)
		return;
	SetReg("CCDLAB", "FolderBrowserPath", fdlg->SelectedPath);
	
	array<String^>^ filelist;
	
	if (!BatchQuickScanSubDirsChck->Checked)
		filelist = Directory::GetFiles(fdlg->SelectedPath, "*.fits", ::SearchOption::TopDirectoryOnly);
	else
		filelist = Directory::GetFiles(fdlg->SelectedPath, "*.fits", ::SearchOption::AllDirectories);
	if (filelist->Length == 0)
	{
		::MessageBox::Show("No files found in that directory.","Error");
		return;
	}

	BATCHLIST = filelist;
	BatchListNameTxt->Text = String::Concat("List: ",BATCHLIST->Length.ToString()," files.");
	BatchListViewPanel->Text = "Quick Viewing: File 0 of " + BATCHLIST->Length.ToString();
	BatchGoToUpD->Maximum = BATCHLIST->Length;
	BatchListViewPanel->Enabled = true;
	BatchComputeBtn->Enabled = true;
}

void Form1::BatchSubtractImageChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (BatchSubtractImageChck->Checked == false)
	{
		return;
	}

	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS File|*.fits;*.fit;*.fts";

	if (dlg->ShowDialog() != ::DialogResult::OK)
	{
		BatchSubtractImageChck->Checked = false;
		return;
	}

	BATCHBIASIMG = gcnew FITSImage(dlg->FileName, SUBRANGE, true, true, false, true);
}

void Form1::BatchMultiplyImageChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (BatchMultiplyImageChck->Checked == false)
	{
		return;
	}

	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS File|*.fits;*.fit;*.fts";

	if (dlg->ShowDialog() != ::DialogResult::OK)
	{
		BatchMultiplyImageChck->Checked = false;
		return;
	}

	BATCHMULTIMG = gcnew FITSImage(dlg->FileName, SUBRANGE, true, true, false, true);
}

void Form1::BatchAddImageChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (BatchAddImageChck->Checked == false)
	{
		return;
	}

	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS File|*.fits;*.fit;*.fts";

	if (dlg->ShowDialog() != ::DialogResult::OK)
	{
		BatchAddImageChck->Checked = false;
		return;
	}

	BATCHADDIMG = gcnew FITSImage(dlg->FileName, SUBRANGE, true, true, false, true);
}

void Form1::BatchDivideImageChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (BatchDivideImageChck->Checked == false)
	{
		return;
	}

	String^ dir = (String^)GetReg("CCDLAB", "OpenFilesPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS File|*.fits;*.fit;*.fts";
	
	if (dlg->ShowDialog() != ::DialogResult::OK)
	{
		BatchDivideImageChck->Checked = false;
		return;
	}

	BATCHFLATIMG = gcnew FITSImage(dlg->FileName, SUBRANGE, true, true, false, true);
}

void Form1::BatchAddImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e){}
void Form1::BatchMultiplyImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e){}
void Form1::BatchSubtractImageChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e){}

void Form1::BatchSubImageChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (BatchSubImageChck->Checked == true)
	{
		BatchSubImagePanel->BorderStyle = BorderStyle::Fixed3D;
		RangeDlg^ dlg = gcnew RangeDlg();
		dlg->XStartUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "XStart"));
		dlg->XEndUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "XEnd"));
		dlg->YStartUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "YStart"));
		dlg->YEndUpD->Value = ::Convert::ToInt32(GetReg("CCDLAB", "YEnd"));
		dlg->ShowDialog();

		if (dlg->DialogResult == ::DialogResult::OK)
		{
			SUBRANGE[0] = (int)dlg->XStartUpD->Value;
			SUBRANGE[1] = (int)dlg->XEndUpD->Value;
			SUBRANGE[2] = (int)dlg->YStartUpD->Value;
			SUBRANGE[3] = (int)dlg->YEndUpD->Value;
			SetReg("CCDLAB", "XStart", SUBRANGE[0].ToString());
			SetReg("CCDLAB", "XEnd", SUBRANGE[1].ToString());
			SetReg("CCDLAB", "YStart", SUBRANGE[2].ToString());
			SetReg("CCDLAB", "YEnd", SUBRANGE[3].ToString());

			LOADSUBRANGE = true;
			XStartLabel->Text = String::Concat("X Start: ", SUBRANGE[0]);
			XEndLabel->Text = String::Concat("X End: ", SUBRANGE[1]);
			YStartLabel->Text = String::Concat("Y Start: ", SUBRANGE[2]);
			YEndLabel->Text = String::Concat("Y End: ", SUBRANGE[3]);

			BatchDivideImageChck->Checked = false;
			BatchMultiplyImageChck->Checked = false;
			BatchSubtractImageChck->Checked = false;
			BatchAddImageChck->Checked = false;
		}
		else
		{
			BatchSubImageChck->Checked = false;
		}
	}
	else
	{
		LOADSUBRANGE = false;
		SUBRANGE[0] = -1;
		BatchSubImagePanel->BorderStyle = BorderStyle::FixedSingle;
		BatchDivideImageChck->Checked = false;
		BatchMultiplyImageChck->Checked = false;
		BatchSubtractImageChck->Checked = false;
		BatchAddImageChck->Checked = false;
	}
}

void Form1::BatchComputeBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ selectedOP = BatchOperationTab->SelectedTab->Name;

	if (selectedOP == "BatchRunningTab")//running
		if (BatchRunningOpDrop->Text == "")
		{
			::MessageBox::Show("Running style not selected.  Please try again.","Error...");
			return;
		}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	if (UVITBATCHMESG != "")
		WAITBAR->Text = UVITBATCHMESG;
	else
		WAITBAR->Text = "Performing batch operation...";
	BatchBGWrkr->RunWorkerAsync(BatchOperationTab->SelectedTab->Name);
	WAITBAR->ShowDialog();
}

void Form1::BatchBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{		
	String^ selectedOP = (String^)e->Argument;

	if (selectedOP == "BatchIndividualTab")//individual file operation
	{
		int intprog = 0;
		int N = BATCHLIST->Length;
		bool findpts = TabBatchElementalFindPointsChck->Checked;
		String^ searchstyle = TabBatchElementalFindStyleDD->Text;
		array<int,2>^ pts;
		double findval = Convert::ToDouble(TabBatchElementalFindValTxt->Text);
		double replaceval = Convert::ToDouble(TabBatchElementalReplaceValTxt->Text);
		bool overwritefile = BatchFileOvrWrtRad->Checked;
		String^ appendage = BatchIndividualAppendageTxt->Text;
		bool do_parallel = BatchFileParallelChck->Checked;
		bool keepdirs = BatchFileKeepDirectoriesChck->Checked;
		String^ dir = IndividualDirectoryTxt->Text + "\\";

		int n = 1;
		if (do_parallel)
			n = omp_get_max_threads();
		array<int>^ count = gcnew array<int>(n);
		int prog = 0;
		#pragma omp parallel for if(do_parallel)
		for (int i = 0; i < N; i++)
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			{
				if (UVITBATCHOP)
				{
					UVITBATCHOP = false;
					UVITBATCHOP_CANCELLED = true;
				}
				break;
			}

			count[omp_get_thread_num()]++;
			#pragma omp critical
			{
				int sum = 0;
				for (int si = 0; si < count->Length; si++)
					sum += count[si];
				if (sum * 100 / N > prog)
				{
					BatchBGWrkr->ReportProgress(prog);
					prog = sum * 100 / N;
				}
			}

			FITSImage^ temp = gcnew FITSImage(BATCHLIST[i], SUBRANGE, true, true, false, !do_parallel);

			//corrections
			if (BatchSubtractImageChck->Checked)
				temp->SetImage(JPMath::MatrixSubMatrix(temp->Image, BATCHBIASIMG->Image, !do_parallel), false, !do_parallel);
			if (BatchAddImageChck->Checked)
				temp->SetImage(JPMath::MatrixAddMatrix(temp->Image, BATCHADDIMG->Image, !do_parallel), false, !do_parallel);
			if (BatchMultiplyImageChck->Checked)
				temp->SetImage(JPMath::MatrixMultMatrix(temp->Image, BATCHMULTIMG->Image, !do_parallel), false, !do_parallel);
			if (BatchDivideImageChck->Checked)
				temp->SetImage(JPMath::MatrixDivMatrix(temp->Image, BATCHFLATIMG->Image, !do_parallel), false, !do_parallel);

			if (findpts)
			{
				pts = JPMath::Find(temp->Image, findval, searchstyle, !do_parallel);
				temp->Image = JPMath::Replace(temp->Image, pts, replaceval, !do_parallel);
			}

			if (overwritefile)
				temp->WriteImage(FILESAVEPREC, !do_parallel);
			else//append
			{
				if (keepdirs)
					temp->FileName = temp->FileName->Insert(temp->FileName->LastIndexOf("."), appendage);
				else
					temp->FullFileName = dir + temp->FileName->Insert(temp->FileName->LastIndexOf("."), appendage);

				temp->WriteImage(FILESAVEPREC, !do_parallel);
			}
		}

		/*TimeSpan^ ts = ::DateTime::Now - now;
		MessageBox::Show(ts->TotalMinutes + "");*/

		return;
	}

	if (selectedOP == "BatchSetTab")//Set
	{
		FITSImage^ fits_integral;
		FITSImage^ temp;

		for (int i = 0; i < BATCHLIST->Length; i++)
		{
			if(WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			BatchBGWrkr->ReportProgress(i);

			temp = gcnew FITSImage(BATCHLIST[i], SUBRANGE, true, true, false, true);

			//corrections
			if (BatchSubtractImageChck->Checked == true)
				temp->SetImage(temp - BATCHBIASIMG, false, true);
			if (BatchMultiplyImageChck->Checked == true)
				temp->SetImage(temp * BATCHMULTIMG, false, true);
			if (BatchAddImageChck->Checked == true)
				temp->SetImage(temp + BATCHADDIMG, false, true);
			if (BatchDivideImageChck->Checked == true)
				temp->SetImage(temp / BATCHFLATIMG, false, true);

			if (BatchSumRad->Checked || BatchMeanRad->Checked)
			{
				if (i == 0)
					fits_integral = temp;
				else
					fits_integral->SetImage(fits_integral + temp,false, true);
			}
		}

		if (BatchMeanRad->Checked)
			fits_integral->SetImage(fits_integral/BATCHLIST->Length,false, true);
		if (BatchSumRad->Checked || BatchMeanRad->Checked)
		{
			e->Result = fits_integral;
		}
	}//end of Set op

	if (selectedOP == "BatchStackingTab")//stacking
	{
		WAITBAR->ProgressBar->Maximum = 100;
		int intprog = 0;

		int STACK = (int)StackUpD->Value;
		int N = BATCHLIST->Length;
		int iters = (int)::Math::Floor(double(N)/double(STACK));

		FITSImage^ temp1;
		FITSImage^ temp2;
		String^ dir = StackingDirectoryTxt->Text + "\\" ;
		String^ fext;

		for (int i = 0; i < iters; i++)
		{
			if(WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			if (100*i*STACK/N-intprog >= 1)
			{
				intprog = 100*i*STACK/N;
				BatchBGWrkr->ReportProgress(intprog);
			}

			temp1 = gcnew JPFITS::FITSImage(BATCHLIST[i * STACK], SUBRANGE, true, true, false, true);

			//corrections
			if (BatchSubtractImageChck->Checked == true)
				temp1->SetImage(temp1 - BATCHBIASIMG, false, true);
			if (BatchMultiplyImageChck->Checked == true)
				temp1->SetImage(temp1 * BATCHMULTIMG, false, true);
			if (BatchAddImageChck->Checked == true)
				temp1->SetImage(temp1 + BATCHADDIMG, false, true);
			if (BatchDivideImageChck->Checked == true)
				temp1->SetImage(temp1 / BATCHFLATIMG, false, true);

			for (int j = 1; j < STACK; j++)
			{
				temp2 = gcnew JPFITS::FITSImage(BATCHLIST[i * STACK + j], SUBRANGE, true, true, false, true);

				//corrections
				if (BatchSubtractImageChck->Checked == true)
					temp2->SetImage(temp2 - BATCHBIASIMG, false, true);
				if (BatchMultiplyImageChck->Checked == true)
					temp2->SetImage(temp2 * BATCHMULTIMG, false, true);
				if (BatchAddImageChck->Checked == true)
					temp2->SetImage(temp2 + BATCHADDIMG, false, true);
				if (BatchDivideImageChck->Checked == true)
					temp2->SetImage(temp2 / BATCHFLATIMG, false, true);

				temp1->SetImage(temp1 + temp2, false, true);
			}
			fext = temp1->FileName->Substring(temp1->FileName->LastIndexOf("."));

			temp1->WriteImage(dir + (i * STACK + STACK).ToString("000000") + fext, FILESAVEPREC, true);
		}
	}//end of stacking

	if (selectedOP == "BatchRunningTab")//running
	{
		String^ RUN_STYLE = BatchRunningOpDrop->Text;
		String^ dir = RunningDirectoryTxt->Text + "\\" ;
		int RUN = (int)BatchRunningNumUpD->Value;
		int N = BATCHLIST->Length;
		String^ filename = "";

		JPFITS::FITSImageSet^ RUNSET = gcnew JPFITS::FITSImageSet();
		FITSImage^ temp;

		WAITBAR->ProgressBar->Maximum = 100;
		int intprog = 0;

		for (int i = 0; i < N-RUN+1; i++)
		{
			if(WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			if (100*i/N-intprog >= 1)
			{
				intprog = 100*i/N;
				BatchBGWrkr->ReportProgress(intprog);
			}

			RUNSET->Clear();
			for (int j = 0; j < RUN; j++)
			{
				temp = gcnew FITSImage(BATCHLIST[i + j], SUBRANGE, true, true, false, true);

				//corrections
				if (BatchSubtractImageChck->Checked == true)
					temp->SetImage(temp - BATCHBIASIMG, false, true);
				if (BatchMultiplyImageChck->Checked == true)
					temp->SetImage(temp * BATCHMULTIMG, false, true);
				if (BatchAddImageChck->Checked == true)
					temp->SetImage(temp + BATCHADDIMG, false, true);
				if (BatchDivideImageChck->Checked == true)
					temp->SetImage(temp / BATCHFLATIMG, false, true);

				RUNSET->Add(temp);
			}

			bool product = false;
			if (RUN_STYLE == "Median")
			{
				temp->SetImage(RUNSET->Median(RUNSET, false, false, "")->Image, false, true);
				product = true;
			}
			if (RUN_STYLE == "Minimum")
			{
				temp->SetImage(RUNSET->Min(RUNSET,false,false)->Image, false, true);
				product = true;
			}
			if (RUN_STYLE == "Maximum")
			{
				temp->SetImage(RUNSET->Max(RUNSET, false, false)->Image, false, true);
				product = true;
			}
			if (RUN_STYLE == "Mean")
			{
				temp->SetImage(RUNSET->Mean(RUNSET, false, false)->Image, false, true);
				product = true;
			}
			if (RUN_STYLE == "Sum")
			{
				temp->SetImage(RUNSET->Sum(RUNSET, false, false)->Image, false, true);
				product = true;
			}

			if (product)
			{
				filename = dir + "Running" + RUN_STYLE + RUN.ToString() + "_" + i.ToString("000000") + ".fits";
				temp->WriteImage(filename, FILESAVEPREC, true);
			}
		}
	}
}

void Form1::BatchBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	String^ selectedOP = BatchOperationTab->SelectedTab->Name;

	WAITBAR->ProgressBar->Value = e->ProgressPercentage;

	if (selectedOP == "BatchSetTab" || selectedOP == "BatchRunningTab")
		WAITBAR->TextMsg->Text = String::Concat("Completed ",e->ProgressPercentage," of ",BATCHLIST->Length," files.");
	if (selectedOP == "BatchStackingTab"  || selectedOP == "BatchIndividualTab")
		WAITBAR->TextMsg->Text = String::Concat("Completed ",e->ProgressPercentage,"%");
}

void Form1::BatchBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	::DialogResult res = WAITBAR->DialogResult;
	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::BringToFront();
	String^ selectedOP = BatchOperationTab->SelectedTab->Name;

	if (UVITBATCHOP)
	{
		UVITBATCHOP = false;
		if (res == ::DialogResult::Cancel)
			UVITBATCHOP_CANCELLED = true;
		return;
	}

	if (selectedOP == "BatchSetTab" && WAITBAR->DialogResult != ::DialogResult::Cancel)//Set
	{
		FITSImage^ result =  (FITSImage^)e->Result;
		result->WriteImage(BatchOutLabel->Text, FILESAVEPREC, true);
		return;
	}

	if ((String^)e->Result != "-1" && selectedOP != "BatchSetTab")
		::MessageBox::Show("Operation complete...");
}

void Form1::BatchIntegralTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "BatchOperationTabIndex",BatchOperationTab->SelectedIndex);
}

void Form1::BatchOutFileName_Click(System::Object^  sender, System::EventArgs^  e)
{
	::SaveFileDialog^ sfd = gcnew ::SaveFileDialog();
	sfd->FileName = BatchOutLabel->Text->Substring(BatchOutLabel->Text->LastIndexOf("\\")+1);
	try
	{
		sfd->InitialDirectory = BATCHLIST[0]->Substring(0,BATCHLIST[0]->LastIndexOf("\\"));
	}
	catch (...)
	{
	}
	
	sfd->Filter = "FITS File (*.fts)|*.fts|FITS File (*.fit)|*.fit|FITS File (*.fits)|*.fits";
	sfd->FilterIndex = 3;

	if (sfd->ShowDialog() == ::DialogResult::OK)
	{
		BatchOutLabel->Text = sfd->FileName;
		SetReg("CCDLAB", "OpenFilesPath",sfd->FileName->Substring(0,sfd->FileName->LastIndexOf("\\")));
	}
}

void Form1::StackingDirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	::FolderBrowserDialog^ fb = gcnew ::FolderBrowserDialog();
	fb->SelectedPath = (String^)GetReg("CCDLAB", "StackingFilesPath");
	if (fb->ShowDialog() == ::DialogResult::Cancel)
		return;
	String^ dir = fb->SelectedPath;
	StackingDirectoryTxt->Text = dir;
	SetReg("CCDLAB", "StackingFilesPath",dir);
}

void Form1::RunningDirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	::FolderBrowserDialog^ fb = gcnew ::FolderBrowserDialog();
	fb->SelectedPath = (String^)GetReg("CCDLAB", "RunningFilesPath");
	if (fb->ShowDialog() == ::DialogResult::Cancel)
		return;
	String^ dir = fb->SelectedPath;
	RunningDirectoryTxt->Text = dir;
	SetReg("CCDLAB", "RunningFilesPath",dir);
}

void Form1::IndividualDirectoryTxt_Click(System::Object^  sender, System::EventArgs^  e)
{
	::FolderBrowserDialog^ fb = gcnew ::FolderBrowserDialog();
	fb->SelectedPath = (String^)GetReg("CCDLAB", "IndividualFilesPath");
	if (fb->ShowDialog() == ::DialogResult::Cancel)
		return;
	String^ dir = fb->SelectedPath;
	IndividualDirectoryTxt->Text = dir;
	SetReg("CCDLAB", "IndividualFilesPath",dir);
}

void Form1::StackUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "StackUpDValue",StackUpD->Value.ToString());
}

void Form1::BatchRunningNumUpD_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "RunningUpDValue",BatchRunningNumUpD->Value.ToString());
}

void Form1::TabBatchElementalFindPointsChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TabBatchElementalFindPointsChck->Checked)
	{
		TabBatchElementalFindStyleDD->Enabled = true;
		TabBatchElementalFindValTxt->Enabled = true;
		//TabBatchElementalReplaceStyleDD->Enabled = true;
		TabBatchElementalReplaceValTxt->Enabled = true;
	}
	else
	{
		TabBatchElementalFindStyleDD->Enabled = false;
		TabBatchElementalFindValTxt->Enabled = false;
		//TabBatchElementalReplaceStyleDD->Enabled = false;
		TabBatchElementalReplaceValTxt->Enabled = false;
	}
}

void Form1::BatchFileAppRad_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (BatchFileAppRad->Checked)
	{
		BatchIndividualAppendageTxt->Enabled = true;
		IndividualDirectoryTxt->Enabled = true;
		BatchFileKeepDirectoriesChck->Enabled = true;
	}
	else
	{
		BatchIndividualAppendageTxt->Enabled = false;
		IndividualDirectoryTxt->Enabled = false;
		BatchFileKeepDirectoriesChck->Enabled = false;
	}
}

void Form1::BatchFileKeepDirectoriesChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (BatchFileKeepDirectoriesChck->Checked)
		IndividualDirectoryTxt->Enabled = false;
	else
		IndividualDirectoryTxt->Enabled = true;
}

void Form1::BatchMovieTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
	BatchMovieTimer->Interval = int(System::Convert::ToDouble(BatchBlinkTime->Value)*1000) + 1;//+1 to avoid 0, 1 = 1ms
	BatchViewNextBtn_Click(sender,e);
}

void Form1::BatchBlinkChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (BatchBlinkChck->Checked == true)
	{
		BatchMovieTimer->Enabled = true;
		BatchBlinkChck->BackColor = System::Drawing::Color::Red;
	}
	else
	{
		BatchMovieTimer->Enabled = false;
		BatchBlinkChck->BackColor = System::Drawing::Color::Gainsboro;
	}
}

void Form1::BatchViewNextBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	BATCHVIEWINDEX += (int)BatchMovieSkipUpD->Value + 1;

	if (BATCHVIEWINDEX > BATCHLIST->Length-1)
		BATCHVIEWINDEX = 0;

	BatchListViewPanel->Text = "Quick Viewing: File " + (BATCHVIEWINDEX+1).ToString() + " of " + BATCHLIST->Length.ToString();

	array<String^>^ file = gcnew array<String^>(1){BATCHLIST[BATCHVIEWINDEX]};

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(file, false);
}

void Form1::BatchViewLastBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	BATCHVIEWINDEX -= (int)BatchMovieSkipUpD->Value + 1;

	if (BATCHVIEWINDEX < 0)
		BATCHVIEWINDEX = BATCHLIST->Length-1;

	BatchListViewPanel->Text = "Quick Viewing: File " + (BATCHVIEWINDEX+1).ToString() + " of " + BATCHLIST->Length.ToString();

	array<String^>^ file = gcnew array<String^>(1){BATCHLIST[BATCHVIEWINDEX]};

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(file, false);
}

void Form1::BatchGoToBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	BATCHVIEWINDEX = int(BatchGoToUpD->Value) - 1;

	BatchListViewPanel->Text = "Quick Viewing: File " + (BATCHVIEWINDEX + 1).ToString() + " of " + BATCHLIST->Length.ToString();

	array<String^>^ file = gcnew array<String^>(1){BATCHLIST[BATCHVIEWINDEX]};

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(file, false);
}

