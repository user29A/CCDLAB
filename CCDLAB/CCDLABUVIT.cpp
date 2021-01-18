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

void Form1::UVActiveBGChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVActiveBGChck->Checked == true)
	{
		 UVCornerThreshUpD->Enabled = true;
		 UVBackGroundUpD->Value = 0;
		 UVDarkScalarRad->Checked = true;
		 UVBackGroundUpD->Enabled = false;
	}
	else
	{
		 UVCornerThreshUpD->Enabled = false;
		 UVBackGroundUpD->Value = 45;
		 if (UVDarkImageRad->Checked == false)
			 UVBackGroundUpD->Enabled = true;
	}
}

void Form1::UVDarkScalarRad_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	 if (UVDarkScalarRad->Checked == true)
	 {
		 UVBackGroundUpD->Enabled = true;
		 UVActiveBGChck->Checked = false;
	 }
	 else
	 {
	 }
}

void Form1::UVImageOnlyChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	 if (UVImageOnlyChck->Checked == true)
	 {
		 UVPrecisionUpD->Enabled = true;
	 }
	 else
	 {
		 UVPrecisionUpD->Enabled = false;
	 }
}

void Form1::UVXDecHist_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(1);
}

void Form1::UVYDecHist_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(2);
}

void Form1::UVPixelHist_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(3);
}

void Form1::UVShapeHist_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(4);
}

void Form1::UVFCMinHist_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(5);
}

void Form1::UVFCMaxMinHist_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(6);
}

void Form1::UVFrameHist_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (UVAlgorithmListBox->SelectedIndex == -1)//occurs when no algorithm is selected at all
		return;
	UVAlgorithmContxtFunction(7);
}

void Form1::UVAlgorithmContxtFunction(int type)
{
	 int ind = UVAlgorithmListBox->SelectedIndex + 1;//ind is Algorithm type index
	 int Ndivs = (int)UVPrecisionUpD->Value;
	 array<double,2>^ cent_list;
	 array<double>^ values;
	 JPPlot^ jpplot = gcnew JPPlot();
	 String^ algorithm;
	 String^ chan = IMAGESET[FILELISTINDEX]->GetKeyValue("CHANNEL");
	 if (chan->Length == 0)
		 chan = IMAGESET[FILELISTINDEX]->GetKeyValue("DETECTOR");

	 switch (ind)//ind is Algorithm type index
	 {
	 case(1)://3x3 cross = TBTC
		 {
			 cent_list = UVIT_Data->TBTC_Centroids;
			 if (cent_list == nullptr)
			 {
				 ::MessageBox::Show("No data for this algorithm.","Error");
				 return;
			 }
			 values = gcnew array<double>(UVIT_Data->TBTC_Centroids->GetLength(1));
			 algorithm = "3x3 Cross";
			 break;
		 }
	 case(2)://3x3 Square = TBTS
		 {
			 cent_list = UVIT_Data->TBTS_Centroids;
			 if (cent_list == nullptr)
			 {
				 ::MessageBox::Show("No data for this algorithm.","Error");
				 return;
			 }
			 values = gcnew array<double>(UVIT_Data->TBTS_Centroids->GetLength(1));
			 algorithm = "3x3 Square";
			 break;
		 }
	 case(3)://3x3 cross Gaussian = TBTQ  (Q was for quadratic)
		 {
			 cent_list = UVIT_Data->TBTQ_Centroids;
			 if (cent_list == nullptr)
			 {
				 ::MessageBox::Show("No data for this algorithm.","Error");
				 return;
			 }
			 values = gcnew array<double>(UVIT_Data->TBTQ_Centroids->GetLength(1));
			 algorithm = "3x3 Gaussian";
			 break;
		 }
	 case(4)://5x5 Cross = FBFC
		 {
			 cent_list = UVIT_Data->FBFC_Centroids;
			 if (cent_list == nullptr)
			 {
				 ::MessageBox::Show("No data for this algorithm.","Error");
				 return;
			 }
			 values = gcnew array<double>(UVIT_Data->FBFC_Centroids->GetLength(1));
			 algorithm = "5x5 Cross";
			 break;
		 }
	 case(5)://5x5 Square = FBFS
		 {
			 cent_list = UVIT_Data->FBFS_Centroids;
			 if (cent_list == nullptr)
			 {
				 ::MessageBox::Show("No data for this algorithm.","Error");
				 return;
			 }
			 values = gcnew array<double>(UVIT_Data->FBFS_Centroids->GetLength(1));
			 algorithm = "5x5 Square";
			 break;
		 }
	 }

	 switch (type)
	 {
	 case (1)://x decimal histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = (cent_list[0,i] - Math::Round(cent_list[0,i]))*double(Ndivs);

			array<double,2>^ hist = JPMath::Histogram_IntegerDivisions(values,Ndivs);
			int L = hist->GetLength(0);
			array<double>^ x = gcnew array<double>(L);
			array<double>^ y = gcnew array<double>(L);

			#pragma omp parallel for
			for (int i = 0; i < L; i++)
			{
				x[i] = hist[i,0];
				y[i] = hist[i,1];
			}
			jpplot->Text = String::Concat(chan, " ", algorithm," X Centroids");
			jpplot->PlotLine(x,y,"X Decimal Centroids","Number of Elements",String::Concat(chan, " ", algorithm," X Centroids"), Charting::SeriesChartType::Column, "XCentroids");
			break;
		 }
	 case (2)://y decimal histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = (cent_list[1,i] - Math::Round(cent_list[1,i]))*double(Ndivs);

			 array<double,2>^ hist = JPMath::Histogram_IntegerDivisions(values,Ndivs);
			 int L = hist->GetLength(0);
			 array<double>^ x = gcnew array<double>(L);
			 array<double>^ y = gcnew array<double>(L);

			 #pragma omp parallel for
			 for (int i = 0; i < L; i++)
			 {
				x[i] = hist[i,0];
				y[i] = hist[i,1];
			 }
			 jpplot->Text = String::Concat(chan, " ", algorithm," Y Centroids");
			 jpplot->PlotLine(x,y,"Y Decimal Centroids","Number of Elements",String::Concat(chan, " ", algorithm," Y Centroids"), Charting::SeriesChartType::Column, "YCentroids");
			 break;
		 }
	 case (3)://pixel energy histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = cent_list[2,i];

			 //quick convenience
			double mean = JPMath::Mean(values, false);
			double std = JPMath::Stdv(values, false);
			String^ txt = Math::Round(mean,2).ToString();
			Windows::Forms::Clipboard::SetText(txt);
			//end convenience

			array<double,2>^ hist = JPMath::Histogram_IntegerStep(values,Ndivs);
			int L = hist->GetLength(0);
			array<double>^ x = gcnew array<double>(L);
			array<double>^ y = gcnew array<double>(L);

			#pragma omp parallel for
			for (int i = 0; i < L; i++)
			{
				x[i] = hist[i,0];
				y[i] = hist[i,1];
			}

			jpplot->Text = chan + " " + algorithm + " Pixel Energy";
			jpplot->PlotLine(x,y,"Pixel Energy","Number of Pixels",chan + " " + algorithm + " Pixel Energy; Mean: " + (int(mean)).ToString() + ", Stdv: " + (int(std)).ToString(), Charting::SeriesChartType::Column, "EnergyHist");
			 break;
		 }
	 case (4)://shape energy histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = cent_list[3,i];

			 //quick convenience
			double mean = JPMath::Mean(values, false);
			double std = JPMath::Stdv(values, false);
			String^ txt = Math::Round(mean,2).ToString();
			Windows::Forms::Clipboard::SetText(txt);
			//end convenience

			array<double,2>^ hist = JPMath::Histogram_IntegerStep(values,Ndivs);
			int L = hist->GetLength(0);
			array<double>^ x = gcnew array<double>(L);
			array<double>^ y = gcnew array<double>(L);

			#pragma omp parallel for
			for (int i = 0; i < L; i++)
			{
				x[i] = hist[i,0];
				y[i] = hist[i,1];
			}

			jpplot->Text = chan + " " + algorithm + " Shape Energy";
			jpplot->PlotLine(x,y,"Shape Energy","Number of Pixels",chan + " " + algorithm + " Shape Energy; Mean: " + (int(mean)).ToString() + ", Stdv: " + (int(std)).ToString(), Charting::SeriesChartType::Column, "ShapeHist");
			 break;
		 }
	 case (5)://5x5 Corner Minimum (i.e. background) histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = cent_list[4,i];

			array<double,2>^ hist = JPMath::Histogram_IntegerStep(values,Ndivs);
			int L = hist->GetLength(0);
			array<double>^ x = gcnew array<double>(L);
			array<double>^ y = gcnew array<double>(L);

			#pragma omp parallel for
			for (int i = 0; i < L; i++)
			{
				x[i] = hist[i,0];
				y[i] = hist[i,1];
			}

			jpplot->PlotLine(x,y,"5x5 Corner Minimum","Number of Pixels",String::Concat(chan, " ", algorithm," 5x5 Corner Minimum"), Charting::SeriesChartType::Column, "MinCornerHist");
			break;
		 }
	 case (6)://5x5 Corner Max-Min (i.e. double event?) histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = cent_list[5,i];
			 
			array<double,2>^ hist = JPMath::Histogram_IntegerStep(values,Ndivs);
			int L = hist->GetLength(0);
			array<double>^ x = gcnew array<double>(L);
			array<double>^ y = gcnew array<double>(L);

			#pragma omp parallel for
			for (int i = 0; i < L; i++)
			{
				x[i] = hist[i,0];
				y[i] = hist[i,1];
			}

			jpplot->PlotLine(x,y,"5x5 Corner Max-Min","Number of Pixels",String::Concat(chan, " ", algorithm," 5x5 Corner Max-Min"), Charting::SeriesChartType::Column, "Max-Min Corner Hist");
			break;
		 }
	  case (7)://events per frame histogram
		 {
			 #pragma omp parallel for
			 for (int i = 0; i < values->Length; i++)
				 values[i] = cent_list[6,i];

			array<double,2>^ hist = JPMath::Histogram_IntegerStep(values,Ndivs);
			int L = hist->GetLength(0);
			array<double>^ x = gcnew array<double>(L);
			array<double>^ y = gcnew array<double>(L);

			#pragma omp parallel for
			for (int i = 0; i < L; i++)
			{
				x[i] = hist[i, 0];
				y[i] = hist[i, 1];
			}

			jpplot->PlotLine(x, y, "Frame Number", "Number of Events", String::Concat(chan, " ", algorithm, " Number of Events per Frame"), Charting::SeriesChartType::Point, "EventsperFrame");

			 int nevents = values->Length;
			 double nframes = JPMath::Max(values, true) - JPMath::Min(values, true) + 1;
			 double mean = double(nevents) / double(nframes);
			 String^ txt = Math::Round(mean, 4).ToString();
			 Windows::Forms::Clipboard::SetText(txt);
			 break;
		 }
	 }
}

void Form1::UVHistWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	int type = ::Convert::ToInt32(e->Argument);// type is index of context menu, i.e., xdec, ydec, 
	int ind = UVAlgorithmListBox->SelectedIndex + 1;//ind is Algorithm type index
	int Ndivs = (int)UVPrecisionUpD->Value;
	array<double,2>^ cent_list;
	array<double>^ values;
	MLCCDLAB::MLHistogram^ hist = gcnew MLCCDLAB::MLHistogram;

	switch (ind)//ind is Algorithm type index
	{
		case(1)://3x3 cross = TBTC
		{
			cent_list = UVIT_Data->TBTC_Centroids;
			values = gcnew array<double>(UVIT_Data->TBTC_Centroids->GetLength(1));
			break;
		}
		case(3)://3x3 cross Gaussian = TBTQ  (Q was for quadratic)
		{
			cent_list = UVIT_Data->TBTQ_Centroids;
			values = gcnew array<double>(UVIT_Data->TBTQ_Centroids->GetLength(1));
			break;
		}
		case(2)://3x3 Square = TBTS
		{
			cent_list = UVIT_Data->TBTS_Centroids;
			values = gcnew array<double>(UVIT_Data->TBTS_Centroids->GetLength(1));
			break;
		}
		case(4)://5x5 Cross = FBFC
		{
			cent_list = UVIT_Data->FBFC_Centroids;
			values = gcnew array<double>(UVIT_Data->FBFC_Centroids->GetLength(1));
			break;
		}
		case(5)://5x5 Square = FBFS
		{
			cent_list = UVIT_Data->FBFS_Centroids;
			values = gcnew array<double>(UVIT_Data->FBFS_Centroids->GetLength(1));
			break;
		}
	}

	switch (type)
	{
		case (1)://x decimal histogram
		{
			#pragma omp parallel for
			for (int i = 0; i < values->Length; i++)
			{
				values[i] = cent_list[0,i] - Math::Round(cent_list[0,i]);
			}
			MWNumericArray^ x = gcnew MWNumericArray(values);
			hist->Hist_NDivs(x,Ndivs);
			break;
		}
		case (2)://y decimal histogram
		{
			#pragma omp parallel for
			for (int i = 0; i < values->Length; i++)
			{
				values[i] = cent_list[1,i] - Math::Round(cent_list[1,i]);
			}
			MWNumericArray^ y = gcnew MWNumericArray(values);
			hist->Hist_NDivs(y,Ndivs);
			break;
		}
		case (3)://pixel energy histogram
		{
			#pragma omp parallel for
			for (int i = 0; i < values->Length; i++)
			{
				values[i] = cent_list[2,i];
			}
			MWNumericArray^ x = gcnew MWNumericArray(values);
			hist->Hist_IntStep(x);
			break;
		}
		case (4)://shape energy histogram 
		{
			#pragma omp parallel for
			for (int i = 0; i < values->Length; i++)
			{
				values[i] = cent_list[3,i];
			}
			MWNumericArray^ x = gcnew MWNumericArray(values);
			hist->Hist_IntStep(x);
			break;
		}
		case (5)://5x5 Corner Minimum (i.e. background) histogram
		{
			#pragma omp parallel for
			for (int i = 0; i < values->Length; i++)
			{
				values[i] = cent_list[4,i];
			}
			MWNumericArray^ x = gcnew MWNumericArray(values);
			hist->Hist_IntStep(x);
			break;
		}
		case (6)://5x5 Corner Max-Min (i.e. double event?) histogram
		{
			#pragma omp parallel for
			for (int i = 0; i < values->Length; i++)
			{
				values[i] = cent_list[5,i];
			}
			MWNumericArray^ x = gcnew MWNumericArray(values);
			hist->Hist_IntStep(x);
			break;
		}
	}
}

void Form1::UVHistWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	Form1::Enabled = true;
}

void Form1::UVOpenRawBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	UVOpenRawDlg->ShowDialog();
}

void Form1::UVMovieTimer_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	UVMovieTimer->Interval = int(System::Convert::ToDouble(UVBlinkTimeUpD->Value)*1000) + 1;//+1 to avoid 0, 1 = 1ms
	UVViewNextBtn_Click(sender,e);
}

void Form1::UVViewNextBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	UVIT_Data->Current_File_Number += (int)UVMovieSkipUpD->Value + 1;
	UVViewSelectionStatic->Text = String::Concat("Viewing File ",UVIT_Data->Current_File_Number," of ",UVIT_Data->Number_of_Files.ToString());

	array<String^>^ file = gcnew array<String^>(1){UVIT_Data->Full_File_List[UVIT_Data->Current_File_Number-1]};

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(file);
}

void Form1::UVViewLastBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	UVIT_Data->Current_File_Number -= (int)UVMovieSkipUpD->Value + 1;
	UVViewSelectionStatic->Text = String::Concat("Viewing File ",UVIT_Data->Current_File_Number," of ",UVIT_Data->Number_of_Files.ToString());

	array<String^>^ file = gcnew array<String^>(1){UVIT_Data->Full_File_List[UVIT_Data->Current_File_Number-1]};

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(file);
}

void Form1::UVGoToBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	 int ImNum = int(UVGoToUpD->Value);
	 UVIT_Data->Current_File_Number = ImNum;
	 UVViewSelectionStatic->Text = String::Concat("Viewing File ",UVIT_Data->Current_File_Number," of ",UVIT_Data->Number_of_Files.ToString());

	  array<String^>^ file = gcnew array<String^>(1){UVIT_Data->Full_File_List[UVIT_Data->Current_File_Number-1]};

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(file);
}

void Form1::UVMovieBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (UVMovieBtn->Checked == true)
	{
		UVMovieTimer->Enabled = true;
		UVMovieBtn->BackColor = System::Drawing::Color::Red;
	}
	else
	{
		UVMovieTimer->Enabled = false;
		UVMovieBtn->BackColor = System::Drawing::Color::Gainsboro;
	}
}

void Form1::UVOpenRawDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) 
{
	UVBatchViewPanel->Enabled = true;
	CentroidingPanel->Enabled = true;
	UVIT_Data = gcnew UVIT(UVOpenRawDlg->FileNames);
	UVViewSelectionStatic->Text = String::Concat("Viewing File 0 of ",UVIT_Data->Number_of_Files.ToString());
	UVGoToUpD->Maximum = UVOpenRawDlg->FileNames->Length;
}

void Form1::UVCentroidBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (::MessageBox::Show( "Are you Sure you Would like to Proceed with Centroiding?","Proceed?",::MessageBoxButtons::OKCancel) == ::DialogResult::OK)
	{
		SetReg("CCDLAB", "UVPixelMinThresh",UVPixelMinThresh->Value);
		SetReg("CCDLAB", "UVShapeMinThresh",UVShapeMinThresh->Value);
		SetReg("CCDLAB", "UVPixelMaxThresh",UVPixelMaxThresh->Value);
		SetReg("CCDLAB", "UVShapeMaxThresh",UVShapeMaxThresh->Value);

		ProgressBar->Maximum = UVIT_Data->Number_of_Files;
		Form1::Enabled = false;
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = 100;
		UVCentroidWrkr->RunWorkerAsync();
		WAITBAR->Show();
	}
}

void Form1::UVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat(e->ProgressPercentage,"%");
	WAITBAR->Text = String::Concat("Centroiding...",e->ProgressPercentage,"%");
}

void Form1::UVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::Activate();
}

void Form1::UVSaveCentroidDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	UVSaveCentroidDlg->ShowDialog();
}

void Form1::UVSaveCentroidDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) 
{
	int ind = UVSaveCentroidDrop->SelectedIndex;
	String^ type = UVSaveCentroidDrop->Items[ind]->ToString();
	String^ filename = UVSaveCentroidDlg->FileName;
	String^ bgname = UVDarkImageTxt->Text;
	UVIT_Data->Save_Centroids(filename,type,bgname,UVActiveBGChck->Checked);
}

void Form1::UVCentroidWrkr_DoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	 System::DateTime D = DateTime::Now;
	 BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

	 bool finished = true;
	 int precision = (int)UVPrecisionUpD->Value;
	 int minpix = (int)UVPixelMinThresh->Value;	int maxpix = (int)UVPixelMaxThresh->Value;
	 int minshape = (int)UVShapeMinThresh->Value;	int maxshape = (int)UVShapeMaxThresh->Value;
	 int background = (int)UVBackGroundUpD->Value;
	 int CornerThresh = (int)UVCornerThreshUpD->Value;
	 double BGOffset = (double)UVBGOffset->Value;
	 array<int>^ range = gcnew array<int>(4);
	 range[0] = 0; range[1] = IMAGESET[FILELISTINDEX]->Width-1;	range[2] = 0; range[3] = IMAGESET[FILELISTINDEX]->Height-1;//default, but change next by checked default
	 if (UVSubRangeChck->Checked == true) //then set range to sub window
	 {
		 range[0] = XSUBRANGE[0];	range[1] = XSUBRANGE[XSUBRANGE->Length-1];
		 range[2] = YSUBRANGE[0];	range[3] = YSUBRANGE[YSUBRANGE->Length-1];
	 }
	 UVSaveCentroidDrop->Items->Clear();

	 array<bool,1>^ algors = gcnew array<bool,1>(UVAlgorithmListBox->Items->Count);
	 bool oneselected = false;
	 for (int i = 0; i < UVAlgorithmListBox->Items->Count; i++)
	 {
		 algors[i] = UVAlgorithmListBox->GetItemChecked(i);
		 if (algors[i] == true)
		 {
			 oneselected = true;
			 UVSaveCentroidDrop->Items->Add(UVAlgorithmListBox->Items[i]);
		 }
	 }
	 if (oneselected == false)
	 {
		 ::MessageBox::Show("Please Select Centroid Algorithm","Error");
		 return;
	 }
	 if (UVDarkImageRad->Checked == true)
	 {
		 background = 0;//using array background, has already been made on check
		 finished = UVIT_Data->Centroid(precision,range,minpix,maxpix,minshape,maxshape,background,algors,UVBGArray,worker,
			 UVImageOnlyChck->Checked,UVActiveBGChck->Checked,CornerThresh,BGOffset,WAITBAR);
	 }
	 else//must be using scalar background
	 {
		 finished = UVIT_Data->Centroid(precision,range,minpix,maxpix,minshape,maxshape,background,algors,nullptr,worker,
			 UVImageOnlyChck->Checked,UVActiveBGChck->Checked,CornerThresh,BGOffset,WAITBAR);
	 }
	 if (finished == false)
		 return;

	 if (!UVImageOnlyChck->Checked)//i.e. made centroid lists
	 {
		 UVSaveCentroidDrop->Enabled = true;
		 UVAlgorithmCntxt->Enabled = true;
		 UVTransferImagesBtn->Enabled = true;
		 UVPrecisionUpD->Enabled = true;
	 }
	 else//only made image(s)
	 {
		 UVSaveCentroidDrop->Enabled = false;
		 UVAlgorithmCntxt->Enabled = false;
		 UVTransferImagesBtn->Enabled = true;
	 }
	 TimeSpan TS = DateTime::Now - D;
	 ::MessageBox::Show(String::Concat("Elapsed Time: ",TS.Hours.ToString(),"h",TS.Minutes.ToString(),"m",TS.Seconds.ToString(),"s."),"Time...");
}

void Form1::UVOpenUCFDlg_FileOk(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e)
{
	array<String^>^ dummy = gcnew array<String^>(1);
	dummy[0] = UVOpenUCFDlg->FileName;
	UVIT_Data = gcnew UVIT(dummy);
	array<String^>^ UV = UVIT_Data->Open_CentroidFile(UVOpenUCFDlg->FileName);

	UVSaveCentroidDrop->Items->Clear();
	UVSaveCentroidDrop->Items->Add(UV[0]);
	UVPixelMinThresh->Value = ::Convert::ToInt32(UV[5]);
	UVPixelMaxThresh->Value = ::Convert::ToInt32(UV[6]);
	UVShapeMinThresh->Value = ::Convert::ToInt32(UV[7]);
	UVShapeMaxThresh->Value = ::Convert::ToInt32(UV[8]);
	UVDarkImageTxt->Text = UV[9];
	if (UVIT_Data->Range[0] == 0 && UVIT_Data->Range[2] == 0 &&
		UVIT_Data->Range[1] == 511 && UVIT_Data->Range[3] == 511)
		UVSubRangeChck->Checked = false;
	UVViewSelectionStatic->Text = String::Concat("Number of Files = ",UV[10]);

	CentroidingPanel->Enabled = true;
	UVSaveCentroidDrop->Enabled = true;
	UVTransferImagesBtn->Enabled = true;
	UVPrecisionUpD->Enabled = true;
}

void Form1::UVTransferImagesBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	 String^ type;
	 String^ filepath = IMAGESET[0]->FilePath;
	 String^ fullfile;
	 int precision = (int)UVPrecisionUpD->Value;
	 int count = FileListDrop->Items->Count;
	 UVIT_Data->Precision = precision;
	 for (int i = 0; i < UVSaveCentroidDrop->Items->Count; i++)
	 {
		 type = UVSaveCentroidDrop->Items[i]->ToString();
		 fullfile = String::Concat(filepath,type,"_X",precision,".fts");
		 FileListDrop->Items->Add(String::Concat(type,"_X",precision,".fts"));
		 if (UVImageOnlyChck->Checked == false)
		 {
			 IMAGESET->Add(gcnew FITSImage(fullfile, UVIT_Data->Get_Image(type), true, true));
		 }
		 else
		 {
			 IMAGESET->Add(gcnew FITSImage(fullfile, UVIT_Data->Get_FromOnlyImageMode(type), true, true));
			 UVTransferImagesBtn->Enabled = false;
		 }

	 }

	 FileListDrop->SelectedIndex = count;
	 BatchViewPanel->Enabled = true;
	 TBSaveBatch->Enabled = true;
	 TBSaveBatchOver->Enabled = true;
	 BatchCorrectionChck->Checked = true;
	 BatchCorrectionChck->Enabled = true;
	 ImageBatchRedxnPnl->Enabled = true;
	 EMBatch->Enabled = true;
	 HCInsertBatch->Enabled = true;
	 HCRemoveBatch->Enabled = true;
	 SubBiasChck->Checked = false;
	 MultImgChck->Checked = false;
	 AddImageChck->Checked = false;
	 DivFlatChck->Checked = false;
	 BatchMeanChck->Checked = false;
	 BatchSumChck->Checked = false;
	 BatchQuadratureChck->Checked = false;
	 BatchMedianChck->Checked = false;
	 BatchStdvChck->Checked = false;
}

void Form1::UVOpenDirBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	UVOpenDirDlg->SelectedPath = (String^)GetReg("CCDLAB", "OpenFilesPath");
	System::Windows::Forms::DialogResult result = UVOpenDirDlg->ShowDialog();
	if (result == ::DialogResult::OK)
	{
		UVBatchViewPanel->Enabled = true;
		CentroidingPanel->Enabled = true;
		array<String^>^ filelist;
		if (!UVOpenSubDirChck->Checked)
		{
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.raw",::SearchOption::TopDirectoryOnly);
			if (filelist->Length == 0)
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.fits",::SearchOption::TopDirectoryOnly);
			if (filelist->Length == 0)
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.fit",::SearchOption::TopDirectoryOnly);
			if (filelist->Length == 0)
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.fts",::SearchOption::TopDirectoryOnly);
		}
		else
		{
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.raw",::SearchOption::AllDirectories);
			if (filelist->Length == 0)
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.fits",::SearchOption::AllDirectories);
			if (filelist->Length == 0)
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.fit",::SearchOption::AllDirectories);
			if (filelist->Length == 0)
			filelist = Directory::GetFiles(UVOpenDirDlg->SelectedPath,"*.fts",::SearchOption::AllDirectories);
		}

		if (filelist->Length == 0)
		{
			::MessageBox::Show("No RAW or FITS files found.","No data...");
			return;
		}

		Array::Sort(filelist);
		UVIT_Data = gcnew UVIT(filelist);
		UVViewSelectionStatic->Text = String::Concat("Viewing File 0 of ",UVIT_Data->Number_of_Files.ToString());
		UVGoToUpD->Maximum = UVIT_Data->Number_of_Files;
		SetReg("CCDLAB", "OpenFilesPath",UVOpenDirDlg->SelectedPath);
		UVGoToUpD->Maximum = filelist->Length;
	}
}

void Form1::UVOpenCentroidBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
	UVOpenUCFDlg->ShowDialog();
}

void Form1::UVDarkImageRad_CheckedChanged(System::Object ^sender, System::EventArgs ^e)
{
	if (UVDarkImageRad->Checked == true && !(CentroidingPanel->Enabled == false))
	 {
		 UVBackGroundUpD->Enabled = false;
		 OpenFileDialog^ dlg = gcnew OpenFileDialog();
		 dlg->Filter = "Fits File (*.fts)|*.fts|Fits File (*.fit)|*.fit|Fits File (*.fits)|*.fits";
		 dlg->Title = "Please Select Dark FITS File";
		 System::Windows::Forms::DialogResult result = dlg->ShowDialog();

		 if (result == ::DialogResult::OK)
		 {
			 UVActiveBGChck->Checked = false;
			 UVDarkImageTxt->Text = dlg->FileName->Substring(dlg->FileName->LastIndexOf("\\")+1);
			 FITSImage^ im = gcnew FITSImage(dlg->FileName, nullptr, false, true, false, true);
			 UVBGArray = gcnew array<unsigned __int16,2>(im->Width,im->Height);
			 for (int i = 0; i < im->Width; i++)
				 for (int j = 0; j < im->Height; j++)
					 UVBGArray[i,j] = (int)im[i,j];
		 }
		 else
		 {
			 UVBackGroundUpD->Enabled = true;
			 UVDarkImageTxt->Text = "NA";
			 UVBGArray = nullptr;
			 UVDarkScalarRad->Checked = true;
		 }
	 }
	 else
	 {
		 UVBackGroundUpD->Enabled = true;
		 UVDarkImageTxt->Text = "NA";
		 UVBGArray = nullptr;
		 UVDarkScalarRad->Checked = true;
	 }
 }

void Form1::EMGSE_UnpackImg_Click(System::Object^  sender, System::EventArgs^  e)
{
	GSEExtractImg^ ext = gcnew GSEExtractImg();
	ext->Show(this);
}

void Form1::UVStatsAnalysisBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	::DialogResult res = ::MessageBox::Show("Ready?","Extract Image Stats?",::MessageBoxButtons::OKCancel);

	if (res == ::DialogResult::Cancel)
		return;

	int ind = UVPlotXAxisDrop->SelectedIndex;
	UVIT_StatsPlot^ UVPlot = gcnew UVIT_StatsPlot();
	UVPlot->Plot_Stats(UVIT_Data->Full_File_List, ind);
}

void Form1::UVHVUTelemBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
	::DialogResult res = ::MessageBox::Show("Ready?","Plot HVU Telem?",::MessageBoxButtons::OKCancel);

	if (res == ::DialogResult::Cancel)
		return;

	int ind = UVPlotXAxisDrop->SelectedIndex;
	UVIT_HVUPlot^ UVPlot = gcnew UVIT_HVUPlot();
	UVPlot->Plot_Telem(UVIT_Data->Full_File_List, ind);
}

void Form1::UVIT_ApplyCPUCorrectionMenu_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = false;
	dlg->Title = "Select the Centroid INTEGERS List (_XYInts_List)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;
	String^ IntsFileList = dlg->FileName;
	String^ FracFileList = IntsFileList->Replace("Ints","Frac");
	FITSImage^ IntsFits = gcnew JPFITS::FITSImage(IntsFileList, nullptr, true, true, false, true);
	FITSImage^ FracFits = gcnew JPFITS::FITSImage(FracFileList, nullptr, true, true, false, true);

	int ind = dlg->FileName->LastIndexOf("\\");
	dir = dlg->FileName->Substring(0,ind);
	SetReg("CCDLAB", "L2EventListPath",dir);

	String^ CPUXDistFile;
	String^ CPUYDistFile;
	String^ channel = IntsFits->GetKeyValue("CHANNEL");
	if (channel->Length == 0)
		channel = IntsFits->GetKeyValue("DETECTOR");
	if (channel == "FUV")
	{
		if (::File::Exists("C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits"))
		{
			CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits";
			CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dY.fits";
		}
	}
	else if (channel == "NUV")
	{
		if (::File::Exists("C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits"))
		{
			CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits";
			CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dY.fits";
		}
	}
	else if (channel == "VIS")
	{
		if (::File::Exists("C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits"))
		{
			CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits";
			CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dY.fits";
		}
	}
	else
	{
		//get the CPU *X* correction image
		dlg->Title = "Select CPU *X* Correction FITS Image File";
		dlg->InitialDirectory = (String^)GetReg("CCDLAB", "OpenCPUDistPath");
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		String^ CPUXDistFile = dlg->FileName;
		ind = dlg->FileName->LastIndexOf("\\");
		dir = dlg->FileName->Substring(0,ind);
		SetReg("CCDLAB", "OpenCPUDistPath",dir);

		//get the CPU *Y* correction image
		dlg->Title = "Select CPU *Y* Correction FITS Image File";
		dlg->InitialDirectory = dir;
		res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		String^ CPUYDistFile = dlg->FileName;
	}
	JPFITS::FITSImage^ CPUXDistFits = gcnew JPFITS::FITSImage(CPUXDistFile, nullptr, true, true, false, true);
	JPFITS::FITSImage^ CPUYDistFits = gcnew JPFITS::FITSImage(CPUYDistFile, nullptr, true, true, false, true);
	
	int xcorr, ycorr;
	int NPts = FracFits->Height;
	#pragma omp parallel for private(xcorr, ycorr)
	for(int j = 0; j < NPts; j++)//now apply Distortion correction...just apply it to the integer values which are 1/32 pixel anyway
	{
		xcorr = int(32*CPUXDistFits[int(IntsFits[0,j]/32), int(IntsFits[1,j]/32)]);
	    ycorr = int(32*CPUYDistFits[int(IntsFits[0,j]/32), int(IntsFits[1,j]/32)]);

		IntsFits[0,j] -= xcorr;
		IntsFits[1,j] -= ycorr;
	}

	ind = IntsFileList->LastIndexOf(".");
	IntsFileList = IntsFileList->Insert(ind,"_deDist");
	ind = FracFileList->LastIndexOf(".");
	FracFileList = FracFileList->Insert(ind,"_deDist");
	IntsFits->WriteImage(IntsFileList, TypeCode::Int16, true);
	FracFits->WriteImage(FracFileList, TypeCode::Int16, true);

	::MessageBox::Show("CPU Distortion Correction Completed...","Finished...");
}

void Form1::ApplyUVFPNMenu_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = false;
	dlg->Title = "Select the Centroid INTEGERS List (_XYInts_List)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;
	String^ IntsFileList = dlg->FileName;
	String^ FracFileList = IntsFileList->Replace("Ints","Frac");
	FITSImage^ IntsFits = gcnew JPFITS::FITSImage(IntsFileList, nullptr, true, true, false, true);
	FITSImage^ FracFits = gcnew JPFITS::FITSImage(FracFileList, nullptr, true, true, false, true);

	int ind = dlg->FileName->LastIndexOf("\\");
	dir = dlg->FileName->Substring(0,ind);
	SetReg("CCDLAB", "L2EventListPath",dir);

	String^ FPNFile;
	String^ channel = IntsFits->GetKeyValue("CHANNEL");
	if (channel->Length == 0)
		channel = IntsFits->GetKeyValue("DETECTOR");
	String^ alg = IntsFits->GetKeyValue("CENTROID");
	if (alg->Length == 0)
		alg = IntsFits->GetKeyValue("ALGRITHM");
	bool FPNsuccess = false;
	if (channel == "FUV")
	{
		if (alg == "3S" || alg == "3x3 Square")
		{
			if (::File::Exists("C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits"))
			{
				FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits";
				FPNsuccess = true;
			}
		}
		if (alg == "5S" || alg == "5x5 Square")
		{
			if (::File::Exists("C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits"))
			{
				FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits";
				FPNsuccess = true;
			}
		}
	}
	if (channel == "NUV")
	{
		if (alg == "3S" || alg == "3x3 Square")
		{
			if (::File::Exists("C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits"))
			{
				FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits";
				FPNsuccess = true;
			}
		}
		if (alg == "5S" || alg == "5x5 Square")
		{
			if (::File::Exists("C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits"))
			{
				FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits";
				FPNsuccess = true;
			}
		}
	}	
	if (channel == "VIS")
	{
		if (alg == "3S" || alg == "3x3 Square")
		{
			if (::File::Exists("C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits"))
			{
				FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits";
				FPNsuccess = true;
			}
		}
		if (alg == "5S" || alg == "5x5 Square")
		{
			if (::File::Exists("C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits"))
			{
				FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits";
				FPNsuccess = true;
			}
		}
	}
	if (!FPNsuccess)
	{
		//get the FPN correction table
		dlg->Title = "Select FPN Correction FITS Image File";
		dlg->InitialDirectory = (String^)GetReg("CCDLAB", "OpenFPNPath");
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		FPNFile = dlg->FileName;
		ind = dlg->FileName->LastIndexOf("\\");
		dir = dlg->FileName->Substring(0,ind);
		SetReg("CCDLAB", "OpenFPNPath",dir);
	}
	FITSImage^ FPNFits = gcnew JPFITS::FITSImage(FPNFile, nullptr, true, true, false, true);

	int NPts = FracFits->Height;
	#pragma omp parallel for
	for(int j = 0; j < NPts; j++)
	{
		//this is for doing 5x5 and if centroid are out of bounds for 3x3.
		//find the centroids out of bounds; xdecs < -16, xdecs > 15;
		//then move them to the adjacent pixel they want to be in with centroids in bounds
		if (FracFits[0,j] < -16)//X
		{
			IntsFits[0,j] -= 32;//adjust integer
			FracFits[0,j] += 32;//adjust fractional
		}
		if (FracFits[1,j] < -16)//Y
		{
			IntsFits[1,j] -= 32;//adjust integer
			FracFits[1,j] += 32;//adjust fractional
		}
		if (FracFits[0,j] > 15)//X
		{
			IntsFits[0,j] += 32;//adjust integer
			FracFits[0,j] -= 32;//adjust fractional
		}
		if (FracFits[1,j] > 15)//Y
		{
			IntsFits[1,j] += 32;//adjust integer
			FracFits[1,j] -= 32;//adjust fractional
		}
	}

	#pragma omp parallel for
	for(int j = 0; j < NPts; j++)
	{
		//adjust centroids to range from 0 to +1 (0 - 31), instead of -0.5
		//to correspond to the FPN Table coordinates ::::THIS MUST be UNDONE at end
		FracFits[0,j] += 16;
		FracFits[1,j] += 16;
	}

	Random^ rand = gcnew Random();
	for(int j = 0; j < NPts; j++)
	{
		//redistribute centroids evenly between the posts, so they can be interpolated
		//using Shyam's Way
		FracFits[0,j] += rand->NextDouble();
		FracFits[1,j] += rand->NextDouble();
	}

	#pragma omp parallel for
	for(int j = 0; j < NPts; j++)//now apply FPN correction
	{
		FracFits[0,j] *= (double)int(FPNFits[1,int(FracFits[0,j]*4096/32)]);
		FracFits[1,j] *= (double)int(FPNFits[2,int(FracFits[1,j]*4096/32)]);
	}

	#pragma omp parallel for
	for(int j = 0; j < NPts; j++)//reset the centroids to -16 to +15 range
	{
		FracFits[0,j] -= 16;//x
		FracFits[1,j] -= 16;//y
	}

	ind = IntsFileList->LastIndexOf(".");
	IntsFileList = IntsFileList->Insert(ind,"_deFPN");
	ind = FracFileList->LastIndexOf(".");
	FracFileList = FracFileList->Insert(ind,"_deFPN");
	IntsFits->WriteImage(IntsFileList, TypeCode::Int16, true);
	FracFits->WriteImage(FracFileList, TypeCode::Int16, true);

	::MessageBox::Show("FPN Correction Completed...","Finished...");
}

void Form1::UVITMenu_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Right)
	{
		GSEExtractImg^ ext = gcnew GSEExtractImg();
		ext->Show(this);
	}
}

void Form1::UVITMenu_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu_Click(sender, e);
}

void Form1::UVITMenu_Click(System::Object^ sender, System::EventArgs^ e)
{
	DriftFromPCInterpolateChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PCDriftInterpChck"));
	SmoothINTDriftChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "SmoothINTDrift"));
	TryAutoDeBiasINTDrift->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "deBiasINTDrift"));
	UserXShiftTxt->Text = (String^)GetReg("CCDLAB", "UserXShiftTxt");
	UserYShiftTxt->Text = (String^)GetReg("CCDLAB", "UserYShiftTxt");
	UserRotationTxt->Text = (String^)GetReg("CCDLAB", "UserRotationTxt");
	UserRotationXCenterTxt->Text = (String^)GetReg("CCDLAB", "UserRotationXTxt");
	UserRotationYCenterTxt->Text = (String^)GetReg("CCDLAB", "UserRotationYTxt");
	FlipHorizontalMenuItem->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "FlipHorizontalMenuItem"));
	FlipVerticalMenuItem->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "FlipVerticalMenuItem"));
	PointSrcINTDriftChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcINTDrift"));
	CrossCorrINTDriftChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "CrossCorrINTDrift"));
	TryAutoDeBiasINTDrift->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "AutoDeBiasINTDriftChck"));
	TryAutoDeBiasINTDrift->Enabled = ::Convert::ToBoolean(GetReg("CCDLAB", "AutoDeBiasINTDriftEnab"));
	CosmicRayFilterSigmaMenuTxt->Text = (String^)GetReg("CCDLAB", "UVCRSigmaThreshold");
	CosmicRayFilterSigmaMenuChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVCRSigmaThresholdChck"));
	CosmicRayFilterCountMenuChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVCRNumberThresholdChck"));
	FilterCosmicRaysChckMenuItem->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "FilterCRs"));
	MaxMinThreshTxt->Text = (String^)GetReg("CCDLAB", "MaxMinThreshTxtText");
	MaxMinThreshChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "MaxMinThreshChck"));
	MaxMinThreshTxt->Enabled = ::Convert::ToBoolean(GetReg("CCDLAB", "MaxMinThreshTxtEnab"));
	MaxMinCountTwiceChck->Enabled = ::Convert::ToBoolean(GetReg("CCDLAB", "MaxMinCountTwiceChckEnab"));
	MaxMinCountTwiceChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "MaxMinCountTwiceChck"));
	ApplyFlatListToImageChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVApplyFlatList"));
	ApplyExpArrayToImageChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "ApplyExpArrayToImageChck"));
	L1DigestApplyDISTChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1DigestApplyDIST"));
	if (L1DigestApplyDISTChck->Checked == false)
	{
		L1DigestApplyDISTInterpBiLinChck->Enabled = false;
		L1DigestApplyDISTInterpNearChck->Enabled = false;
	}
	else
	{
		L1DigestApplyDISTInterpBiLinChck->Enabled = true;
		L1DigestApplyDISTInterpNearChck->Enabled = true;
	}
	L1DigestApplyFPNChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1DigestApplyFPN"));
	ApplyDriftCreateExpArrayChc->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "ApplyDriftCreateExpArrayChc"));
	ExposureArrayResolutionDrop->SelectedIndex = (int)GetReg("CCDLAB", "ExposureArrayRes");
	L1TransformNUVtoFUVChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1NUVtoFUVChck"));
	L1DigestApplyDISTInterpNearChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1DigestApplyDISTInterpNearChck"));
	L1DigestApplyDISTInterpBiLinChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1DigestApplyDISTInterpBiLinChck"));
	UVFinalizeDeleteIntrmdtChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "UVFinalizeDeleteIntrmdtChck"));
	UVFinalizeMoveOrCopyZipChck->Text = (String^)(GetReg("CCDLAB", "UVFinalizeMoveOrCopyZipChck"));
	UVFinalizeMoveOrCopyZipChck->Checked = true;
	UVFinalizeIncludeTablesChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "UVFinalizeIncludeTablesChck"));

	L1CentroidPaddingChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1CentroidPaddingChck"));
	PCCentroidPaddingDrop->SelectedIndex = ::Convert::ToInt32(GetReg("CCDLAB", "PCCentroidPaddingDrop"));
	if (PCCentroidPaddingDrop->SelectedIndex == 0)
		UVPCMODEPADOFFSET = 22;
	if (PCCentroidPaddingDrop->SelectedIndex == 1)
		UVPCMODEPADOFFSET = 44;
	if (L1CentroidPaddingChck->Checked)
		PCCentroidPaddingDrop->Enabled = true;
	else
	{
		PCCentroidPaddingDrop->Enabled = false;
		UVPCMODEPADOFFSET = 0;
	}

	PointSrcROIStackDriftDrop->SelectedIndex = (int)GetReg("CCDLAB", "PointSrcROIStackDriftDrop_index");
	PointSrcROIFindNSrcDrop->SelectedIndex = (int)GetReg("CCDLAB", "PointSrcROIFindNSrcDrop_index");
	DriftSmoothNDrop->SelectedIndex = (int)GetReg("CCDLAB", "DriftSmoothNDrop_index");
	if (::Convert::ToBoolean(GetReg("CCDLAB", "PCDriftInterpChck")))
		DriftSmoothNDrop->Enabled = true;
	else
		DriftSmoothNDrop->Enabled = false;
	L1DiscardDataTimeChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1DiscardDataTimeChck"));
	if (L1DiscardDataTimeChck->Checked)
		L1DiscardDataTimeDrop->Enabled = true;
	else
		L1DiscardDataTimeDrop->Enabled = false;
	L1DiscardDataTimeDrop->SelectedIndex = (int)GetReg("CCDLAB", "L1DiscardDataTimeDrop");
	L1DiscardDuplicateChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1DiscardDuplicateChck"));
	L1DigestPCParityChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1DigestPCParityChck"));
	L1DegradientINTMode->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1DegradientINTMode"));
	L1CleanINTMode->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1CleanINTMode"));
	L1SkipINTMode->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1SkipINTMode"));
	if (L1DegradientINTMode->Checked == false)
		L1CleanINTMode->Enabled = false;
	else
		L1CleanINTMode->Enabled = true;
	if (L1SkipINTMode->Checked)
	{
		L1DegradientINTMode->Enabled = false;
		L1CleanINTMode->Enabled = false;
	}
	else
	{
		L1DegradientINTMode->Enabled = true;
		L1CleanINTMode->Enabled = true;
	}

	L1FilterCorrectionChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1FilterCorrectionChck"));
	L1TBCChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1TBCChck"));
	if (::Convert::ToBoolean(GetReg("CCDLAB", "LinearRotationChck")))
	{
		LinearRotationChck->Checked = true;
		GeneralTransformChck->Checked = false;
		FlipHorizontalMenuItem->Enabled = true;
		FlipVerticalMenuItem->Enabled = true;
		UserXShiftTxt->Enabled = true;
		UserYShiftTxt->Enabled = true;
		UserRotationTxt->Enabled = true;
		UserRotationXCenterTxt->Enabled = true;
		UserRotationYCenterTxt->Enabled = true;

		TransformCoefATxt->Enabled = false;
		TransformCoefBTxt->Enabled = false;
		TransformCoefCTxt->Enabled = false;
		TransformCoefDTxt->Enabled = false;
		TransformCenterXTxt->Enabled = false;
		TransformCenterYTxt->Enabled = false;
		TransformShiftXTxt->Enabled = false;
		TransformShiftYTxt->Enabled = false;
	}
	else if (::Convert::ToBoolean(GetReg("CCDLAB", "GeneralTransformChck")))
	{
		LinearRotationChck->Checked = false;
		GeneralTransformChck->Checked = true;

		FlipHorizontalMenuItem->Enabled = false;
		FlipVerticalMenuItem->Enabled = false;
		UserXShiftTxt->Enabled = false;
		UserYShiftTxt->Enabled = false;
		UserRotationTxt->Enabled = false;
		UserRotationXCenterTxt->Enabled = false;
		UserRotationYCenterTxt->Enabled = false;

		TransformCoefATxt->Enabled = true;
		TransformCoefBTxt->Enabled = true;
		TransformCoefCTxt->Enabled = true;
		TransformCoefDTxt->Enabled = true;
		TransformCenterXTxt->Enabled = true;
		TransformCenterYTxt->Enabled = true;
		TransformShiftXTxt->Enabled = true;
		TransformShiftYTxt->Enabled = true;
	}
	else
	{
		LinearRotationChck->Checked = false;
		GeneralTransformChck->Checked = false;

		FlipHorizontalMenuItem->Enabled = false;
		FlipVerticalMenuItem->Enabled = false;
		UserXShiftTxt->Enabled = false;
		UserYShiftTxt->Enabled = false;
		UserRotationTxt->Enabled = false;
		UserRotationXCenterTxt->Enabled = false;
		UserRotationYCenterTxt->Enabled = false;

		TransformCoefATxt->Enabled = false;
		TransformCoefBTxt->Enabled = false;
		TransformCoefCTxt->Enabled = false;
		TransformCoefDTxt->Enabled = false;
		TransformCenterXTxt->Enabled = false;
		TransformCenterYTxt->Enabled = false;
		TransformShiftXTxt->Enabled = false;
		TransformShiftYTxt->Enabled = false;
	}
	TransformCoefATxt->Text = (String^)GetReg("CCDLAB", "TransformCoefATxt");
	TransformCoefBTxt->Text = (String^)GetReg("CCDLAB", "TransformCoefBTxt");
	TransformCoefCTxt->Text = (String^)GetReg("CCDLAB", "TransformCoefCTxt");
	TransformCoefDTxt->Text = (String^)GetReg("CCDLAB", "TransformCoefDTxt");
	TransformCenterXTxt->Text = (String^)GetReg("CCDLAB", "TransformCenterXTxt");
	TransformCenterYTxt->Text = (String^)GetReg("CCDLAB", "TransformCenterYTxt");
	TransformShiftXTxt->Text = (String^)GetReg("CCDLAB", "TransformShiftXTxt");
	TransformShiftYTxt->Text = (String^)GetReg("CCDLAB", "TransformShiftYTxt");
	UVAutoApplyDriftandImageChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVAutoApplyDriftandImageChck"));
	UVAutoDriftImageViewChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVAutoDriftImageViewChck"));
	if (UVAutoApplyDriftandImageChck->Checked)
		UVAutoDriftImageViewChck->Enabled = true;
	else
		UVAutoDriftImageViewChck->Enabled = false;

	L1CleanINTLineThreshold->Text = (String^)GetReg("CCDLAB", "L1CleanINTLineThreshold");
	L1CleanINTNPix->Text = (String^)GetReg("CCDLAB", "L1CleanINTNPix");
	if (L1CleanINTMode->Checked)
	{
		L1CleanINTLineThreshold->Enabled = true;
		L1CleanINTNPix->Enabled = true;
	}
	else
	{
		L1CleanINTLineThreshold->Enabled = false;
		L1CleanINTNPix->Enabled = false;
	}

	PointSrcINTDriftDisplayChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcINTDriftDisplay"));
	PointSrcINTDriftDisplayCadenceDrop->Enabled = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceEnabled"));
	PointSrcINTDriftDisplayCadenceDrop->SelectedIndex = ::Convert::ToInt32(GetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceIndex"));
	masterizeSinglesToolStripMenuItem->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "masterizeSinglesToolStripMenuItem"));
	UVDeleteMergeDirsChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVDeleteMergeDirsChck"));
	UVAutoPSFPostMergeChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "UVAutoPSFPostMergeChck"));
	L1DigestDeleteFileChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "L1DigestDeleteFileChck"));
	ConsolidateDriftFolderChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "ConsolidateDriftFolderChck"));
	ConsolidateTimeListFolderChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "ConsolidateTimeListFolderChck"));
	RegistrationXYIntsListFolderScanChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "RegistrationXYIntsListFolderScanChck"));
	MergeXYIntsListFolderScanChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "MergeXYIntsListFolderScanChck"));
	PointSrcINTDriftNoPSEConfChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcINTDriftNoPSEConfChck"));
	PointSrcINTDriftNoPlotConfChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcINTDriftNoPlotConfChck"));
	PointSrcROIFindSrcChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcROIFindSrcChck"));
	if (PointSrcROIFindSrcChck->Checked)
		PointSrcROIFindNSrcDrop->Enabled = true;
	else
		PointSrcROIFindNSrcDrop->Enabled = false;
	PointSrcROIAutoRunChck->Checked = ::Convert::ToBoolean(GetReg("CCDLAB", "PointSrcROIAutoRunChck"));
	if (PointSrcROIAutoRunChck->Checked)
	{
		PointSrcROIFindSrcChck->Enabled = false;
		PointSrcROIFindNSrcDrop->Enabled = false;
		PointSrcROIStackDriftDrop->Enabled = false;
	}
	else
	{
		PointSrcROIFindNSrcDrop->Enabled = true;
		PointSrcROIFindSrcChck->Enabled = true;
		PointSrcROIStackDriftDrop->Enabled = true;
	}

	UVLISTTOIMAGEPREC = (int)GetReg("CCDLAB", "UVLISTTOIMGPREC");
	if (UVLISTTOIMAGEPREC == 1)
	{
		ListToImage1PixMenuItem->Checked = true;
		ListToImage2PixMenuItem->Checked = false;
		ListToImage4PixMenuItem->Checked = false;
		ListToImage8PixMenuItem->Checked = false;
		ListToImage16PixMenuItem->Checked = false;
	}
	if (UVLISTTOIMAGEPREC == 2)
	{
		ListToImage1PixMenuItem->Checked = false;
		ListToImage2PixMenuItem->Checked = true;
		ListToImage4PixMenuItem->Checked = false;
		ListToImage8PixMenuItem->Checked = false;
		ListToImage16PixMenuItem->Checked = false;
	}
	if (UVLISTTOIMAGEPREC == 4)
	{
		ListToImage1PixMenuItem->Checked = false;
		ListToImage2PixMenuItem->Checked = false;
		ListToImage4PixMenuItem->Checked = true;
		ListToImage8PixMenuItem->Checked = false;
		ListToImage16PixMenuItem->Checked = false;
	}
	if (UVLISTTOIMAGEPREC == 8)
	{
		ListToImage1PixMenuItem->Checked = false;
		ListToImage2PixMenuItem->Checked = false;
		ListToImage4PixMenuItem->Checked = false;
		ListToImage8PixMenuItem->Checked = true;
		ListToImage16PixMenuItem->Checked = false;
	}
	if (UVLISTTOIMAGEPREC == 16)
	{
		ListToImage1PixMenuItem->Checked = false;
		ListToImage2PixMenuItem->Checked = false;
		ListToImage4PixMenuItem->Checked = false;
		ListToImage8PixMenuItem->Checked = false;
		ListToImage16PixMenuItem->Checked = true;
	}

	CosmicRayFilterMenuTxt->Text = (String^)GetReg("CCDLAB", "UVCRNumberThreshold");

	if (FilterCosmicRaysChckMenuItem->Checked)
	{
		CosmicRayFilterCountMenuChck->Enabled = true;
		CosmicRayFilterSigmaMenuChck->Enabled = true;
		CosmicRayFilterSigmaMenuTxt->Enabled = true;
		CosmicRayFilterMenuTxt->Enabled = true;
	}
	else
	{
		CosmicRayFilterCountMenuChck->Enabled = false;
		CosmicRayFilterSigmaMenuChck->Enabled = false;
		CosmicRayFilterSigmaMenuTxt->Enabled = false;
		CosmicRayFilterMenuTxt->Enabled = false;
	}

	L1AutoRunChck->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1AutoRunChck"));
	if (L1AutoRunChck->Checked)
		L1AutoProceedVISBackGround->Enabled = true;
	else
	{
		L1AutoProceedVISBackGround->Enabled = false;
		L1AutoProceedVISTracking->Enabled = false;
		L1AutoApplyVISDrift->Enabled = false;
		L1AutoProceedVISBackGround->Checked = false;
		L1AutoProceedVISTracking->Checked = false;
		L1AutoApplyVISDrift->Checked = false;
	}
	if (L1AutoProceedVISBackGround->Enabled)
		L1AutoProceedVISBackGround->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1AutoProceedVISBackGround"));
	if (L1AutoProceedVISBackGround->Checked)
		L1AutoProceedVISTracking->Enabled = true;
	L1AutoProceedVISTracking->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1AutoProceedVISTracking"));
	if (L1AutoProceedVISTracking->Checked)
		L1AutoApplyVISDrift->Enabled = true;
	L1AutoApplyVISDrift->Checked = Convert::ToBoolean(GetReg("CCDLAB", "L1AutoApplyVISDrift"));
}

void Form1::UVFinalizeDeleteIntrmdtChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "UVFinalizeDeleteIntrmdtChck", UVFinalizeDeleteIntrmdtChck->Checked);

	UVITMenu->ShowDropDown();
	UVFinalizeScienceBtn->ShowDropDown();
}

void Form1::UVFinalizeMoveOrCopyZipChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (UVFinalizeMoveOrCopyZipChck->Text->Contains("Move"))
		UVFinalizeMoveOrCopyZipChck->Text = UVFinalizeMoveOrCopyZipChck->Text->Replace("Move", "Copy");
	else
		UVFinalizeMoveOrCopyZipChck->Text = UVFinalizeMoveOrCopyZipChck->Text->Replace("Copy", "Move");

	SetReg("CCDLAB", "UVFinalizeMoveOrCopyZipChck", UVFinalizeMoveOrCopyZipChck->Text);

	UVITMenu->ShowDropDown();
	UVFinalizeScienceBtn->ShowDropDown();
}

void Form1::UVFinalizeIncludeTablesChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "UVFinalizeIncludeTablesChck", UVFinalizeIncludeTablesChck->Checked);

	UVITMenu->ShowDropDown();
	UVFinalizeScienceBtn->ShowDropDown();
}

void Form1::MergeXYIntsListFolderScanChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "MergeXYIntsListFolderScanChck", MergeXYIntsListFolderScanChck->Checked);

	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UVCombineCentroidListsMenuItem->ShowDropDown();
}

void Form1::RegistrationXYIntsListFolderScanChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "RegistrationXYIntsListFolderScanChck", RegistrationXYIntsListFolderScanChck->Checked);

	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	GeneralUVRegistrationMenuItem->ShowDropDown();
}

void Form1::ConsolidateTimeListFolderChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "ConsolidateTimeListFolderChck", ConsolidateTimeListFolderChck->Checked);

	UVITMenu->ShowDropDown();
	ApplyDriftListMentuItem->ShowDropDown();
	ConsolidateNUVApplyToFUV->ShowDropDown();
}

void Form1::ConsolidateDriftFolderChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "ConsolidateDriftFolderChck", ConsolidateDriftFolderChck->Checked);

	UVITMenu->ShowDropDown();
	ApplyDriftListMentuItem->ShowDropDown();
	ConsolidateNUVApplyToFUV->ShowDropDown();
}

void Form1::L1DigestDeleteFileChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "L1DigestDeleteFileChck", L1DigestDeleteFileChck->Checked);

	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::PointSrcROIFindSrcChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "PointSrcROIFindSrcChck", PointSrcROIFindSrcChck->Checked);

	if (PointSrcROIFindSrcChck->Checked)
		PointSrcROIFindNSrcDrop->Enabled = true;
	else
		PointSrcROIFindNSrcDrop->Enabled = false;

	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromPCMenuItem->ShowDropDown();
	DriftFromPCPSTrackBtn->ShowDropDown();
}

void Form1::PointSrcROIAutoRunChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "PointSrcROIAutoRunChck", PointSrcROIAutoRunChck->Checked);

	if (PointSrcROIAutoRunChck->Checked)
	{
		PointSrcROIFindNSrcDrop->Enabled = false;
		PointSrcROIFindSrcChck->Enabled = false;
		PointSrcROIStackDriftDrop->Enabled = false;
	}
	else
	{
		PointSrcROIFindNSrcDrop->Enabled = true;
		PointSrcROIFindSrcChck->Enabled = true;
		PointSrcROIStackDriftDrop->Enabled = true;
	}

	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromPCMenuItem->ShowDropDown();
	DriftFromPCPSTrackBtn->ShowDropDown();
}

void Form1::masterizeSinglesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "masterizeSinglesToolStripMenuItem", masterizeSinglesToolStripMenuItem->Checked);

	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	GeneralUVRegistrationMenuItem->ShowDropDown();
}

void Form1::UVDeleteMergeDirsChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "UVDeleteMergeDirsChck", UVDeleteMergeDirsChck->Checked);

	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UVCombineCentroidListsMenuItem->ShowDropDown();
}

void Form1::UVAutoPSFPostMergeChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "UVAutoPSFPostMergeChck", UVAutoPSFPostMergeChck->Checked);

	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UVCombineCentroidListsMenuItem->ShowDropDown();
}

void Form1::PointSrcINTDriftDisplayChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (PointSrcINTDriftDisplayChck->Checked)
		PointSrcINTDriftDisplayCadenceDrop->Enabled = true;
	else
		PointSrcINTDriftDisplayCadenceDrop->Enabled = false;

	SetReg("CCDLAB", "PointSrcINTDriftDisplay", PointSrcINTDriftDisplayChck->Checked);
	SetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceEnabled", PointSrcINTDriftDisplayCadenceDrop->Enabled);

	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
	PointSrcINTDriftChck->ShowDropDown();
}

void Form1::PointSrcINTDriftNoPSEConfChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "PointSrcINTDriftNoPSEConfChck", PointSrcINTDriftNoPSEConfChck->Checked);
	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
	PointSrcINTDriftChck->ShowDropDown();
}

void Form1::PointSrcINTDriftNoPlotConfChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "PointSrcINTDriftNoPlotConfChck", PointSrcINTDriftNoPlotConfChck->Checked);
	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
	PointSrcINTDriftChck->ShowDropDown();
}

void Form1::PointSrcINTDriftDisplayCadenceDrop_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "PointSrcINTDriftDisplayCadenceIndex", PointSrcINTDriftDisplayCadenceDrop->SelectedIndex);
}

void Form1::ExposureArrayResolutionDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "ExposureArrayRes", ExposureArrayResolutionDrop->SelectedIndex);
}

void Form1::ExposureArrayResMenuText_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	ApplyDriftListMentuItem->ShowDropDown();
	ApplyDriftCreateExpArrayChc->ShowDropDown();
}

void Form1::DriftPCROIOnly_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromPCMenuItem->ShowDropDown();
}

void Form1::ApplyDriftCreateExpArrayChc_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "ApplyDriftCreateExpArrayChc", ApplyDriftCreateExpArrayChc->Checked);
	UVITMenu->ShowDropDown();
	ApplyDriftListMentuItem->ShowDropDown();
}

void Form1::UVAutoApplyDriftandImageChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "UVAutoApplyDriftandImageChck",UVAutoApplyDriftandImageChck->Checked);
	if (UVAutoApplyDriftandImageChck->Checked)
		UVAutoDriftImageViewChck->Enabled = true;
	else
		UVAutoDriftImageViewChck->Enabled = false;
}

void Form1::UVAutoDriftImageViewChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "UVAutoDriftImageViewChck",UVAutoDriftImageViewChck->Checked);
	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromPCMenuItem->ShowDropDown();
	UVAutoApplyDriftandImageChck->ShowDropDown();
}

void Form1::L1DiscardDuplicateChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1DiscardDuplicateChck", L1DiscardDuplicateChck->Checked);
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1TransformNUVtoFUVChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1NUVtoFUVChck", L1TransformNUVtoFUVChck->Checked);
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1FilterCorrectionChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1FilterCorrectionChck", L1FilterCorrectionChck->Checked);
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1TBCChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1TBCChck", L1TBCChck->Checked);
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1DegradientINTMode_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1DegradientINTMode", L1DegradientINTMode->Checked);

	if (L1DegradientINTMode->Checked)
		L1CleanINTMode->Enabled = true;
	else
		L1CleanINTMode->Enabled = false;

	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1CleanINTMode_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1CleanINTMode", L1CleanINTMode->Checked);

	if (L1CleanINTMode->Checked)
	{
		L1CleanINTLineThreshold->Enabled = true;
		L1CleanINTNPix->Enabled = true;
	}
	else
	{
		L1CleanINTLineThreshold->Enabled = false;
		L1CleanINTNPix->Enabled = false;
	}
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1SkipINTMode_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1SkipINTMode", L1SkipINTMode->Checked);
	if (L1SkipINTMode->Checked)
	{
		L1DegradientINTMode->Enabled = false;
		L1CleanINTMode->Enabled = false;
	}
	else
	{
		L1DegradientINTMode->Enabled = true;
		L1CleanINTMode->Enabled = true;
	}
	SetReg("CCDLAB", "L1SkipINTMode", L1SkipINTMode->Checked);

	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1DiscardDataTimeDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1DiscardDataTimeDrop", L1DiscardDataTimeDrop->SelectedIndex);
}

void Form1::L1CentroidPaddingChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (L1CentroidPaddingChck->Checked)
	{
		PCCentroidPaddingDrop->Enabled = true;
		if (PCCentroidPaddingDrop->SelectedIndex == 0)
			UVPCMODEPADOFFSET = 22;
		if (PCCentroidPaddingDrop->SelectedIndex == 1)
			UVPCMODEPADOFFSET = 44;
	}
	else
	{
		PCCentroidPaddingDrop->Enabled = false;
		UVPCMODEPADOFFSET = 0;
	}
	SetReg("CCDLAB", "L1CentroidPaddingChck", L1CentroidPaddingChck->Checked);
	UVITMenu->ShowDropDown();
}

void Form1::PCCentroidPaddingDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "PCCentroidPaddingDrop", PCCentroidPaddingDrop->SelectedIndex);
	if (PCCentroidPaddingDrop->SelectedIndex == 0)
		UVPCMODEPADOFFSET = 22;
	if (PCCentroidPaddingDrop->SelectedIndex == 1)
		UVPCMODEPADOFFSET = 44;
}

void Form1::L1DiscardDataTimeChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1DiscardDataTimeChck",L1DiscardDataTimeChck->Checked);
	if (L1DiscardDataTimeChck->Checked)
		L1DiscardDataTimeDrop->Enabled = true;
	else
		L1DiscardDataTimeDrop->Enabled = false;
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1DigestApplyFPNChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1DigestApplyFPN", L1DigestApplyFPNChck->Checked);
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1DigestPCParityChck_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "L1DigestPCParityChck", L1DigestPCParityChck->Checked);
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1DigestApplyDISTChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "L1DigestApplyDIST", L1DigestApplyDISTChck->Checked);
	if (L1DigestApplyDISTChck->Checked == false)
	{
		L1DigestApplyDISTInterpBiLinChck->Enabled = false;
		L1DigestApplyDISTInterpNearChck->Enabled = false;
	}
	else
	{
		L1DigestApplyDISTInterpBiLinChck->Enabled = true;
		L1DigestApplyDISTInterpNearChck->Enabled = true;
	}
	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
}

void Form1::L1DigestApplyDISTInterpNearChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	L1DigestApplyDISTInterpBiLinChck->Checked = false;
	L1DigestApplyDISTInterpNearChck->Checked = true;
	SetReg("CCDLAB", "L1DigestApplyDISTInterpNearChck", L1DigestApplyDISTInterpNearChck->Checked);
	SetReg("CCDLAB", "L1DigestApplyDISTInterpBiLinChck", L1DigestApplyDISTInterpBiLinChck->Checked);

	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
	L1DigestApplyDISTChck->ShowDropDown();
}

void Form1::L1DigestApplyDISTInterpBiLinChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	L1DigestApplyDISTInterpBiLinChck->Checked = true;
	L1DigestApplyDISTInterpNearChck->Checked = false;
	SetReg("CCDLAB", "L1DigestApplyDISTInterpNearChck", L1DigestApplyDISTInterpNearChck->Checked);
	SetReg("CCDLAB", "L1DigestApplyDISTInterpBiLinChck", L1DigestApplyDISTInterpBiLinChck->Checked);

	UVITMenu->ShowDropDown();
	DigestL1FITSImageMenuItem->ShowDropDown();
	L1DigestApplyDISTChck->ShowDropDown();
}

void Form1::FilterCosmicRaysChckMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (FilterCosmicRaysChckMenuItem->Checked)
	{
		CosmicRayFilterCountMenuChck->Enabled = true;
		CosmicRayFilterSigmaMenuChck->Enabled = true;
		CosmicRayFilterSigmaMenuTxt->Enabled = true;
		CosmicRayFilterMenuTxt->Enabled = true;
	}
	else
	{
		CosmicRayFilterCountMenuChck->Enabled = false;
		CosmicRayFilterSigmaMenuChck->Enabled = false;
		CosmicRayFilterSigmaMenuTxt->Enabled = false;
		CosmicRayFilterMenuTxt->Enabled = false;
	}
	SetReg("CCDLAB", "FilterCRs", FilterCosmicRaysChckMenuItem->Checked);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::CosmicRayFilterMenuChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (CosmicRayFilterCountMenuChck->Checked == false)
		CosmicRayFilterCountMenuChck->Checked = true;
	CosmicRayFilterSigmaMenuChck->Checked = false;
	SetReg("CCDLAB", "UVCRNumberThresholdChck", CosmicRayFilterCountMenuChck->Checked);
	SetReg("CCDLAB", "UVCRSigmaThresholdChck", CosmicRayFilterSigmaMenuChck->Checked);
	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
	FilterCosmicRaysChckMenuItem->ShowDropDown();
}

void Form1::CosmicRayFilterSigmaMenuChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (CosmicRayFilterSigmaMenuChck->Checked == false)
		CosmicRayFilterSigmaMenuChck->Checked = true;
	CosmicRayFilterCountMenuChck->Checked = false;
	SetReg("CCDLAB", "UVCRNumberThresholdChck", CosmicRayFilterCountMenuChck->Checked);
	SetReg("CCDLAB", "UVCRSigmaThresholdChck", CosmicRayFilterSigmaMenuChck->Checked);
	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
	FilterCosmicRaysChckMenuItem->ShowDropDown();
}

void Form1::CosmicRayFilterSigmaMenuTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(CosmicRayFilterSigmaMenuTxt->Text);
	}
	catch (...)
	{
		if (CosmicRayFilterSigmaMenuTxt->Text == "")
			return;
		else
			CosmicRayFilterSigmaMenuTxt->Text = "0";
	}
	SetReg("CCDLAB", "UVCRSigmaThreshold",CosmicRayFilterSigmaMenuTxt->Text);
}

void Form1::CosmicRayFilterMenuTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(CosmicRayFilterMenuTxt->Text);
	}
	catch (...)
	{
		if (CosmicRayFilterMenuTxt->Text == "")
			return;
		else
			CosmicRayFilterMenuTxt->Text = "0";
	}
	SetReg("CCDLAB", "UVCRNumberThreshold",CosmicRayFilterMenuTxt->Text);
}

void Form1::ApplyFlatListToImageChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "UVApplyFlatList", ApplyFlatListToImageChck->Checked);
	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::ApplyExpArrayToImageChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "ApplyExpArrayToImageChck", ApplyExpArrayToImageChck->Checked);
	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::TryAutoDeBiasINTDrift_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "deBiasINTDrift", TryAutoDeBiasINTDrift->Checked);
	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
}

void Form1::SmoothINTDriftChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "SmoothINTDrift", SmoothINTDriftChck->Checked);
	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
}

void Form1::ListToImage1PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVLISTTOIMAGEPREC = 1;
	ListToImage1PixMenuItem->Checked = true;
	ListToImage2PixMenuItem->Checked = false;
	ListToImage4PixMenuItem->Checked = false;
	ListToImage8PixMenuItem->Checked = false;
	ListToImage16PixMenuItem->Checked = false;
	SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::ListToImage2PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVLISTTOIMAGEPREC = 2;
	ListToImage1PixMenuItem->Checked = false;
	ListToImage2PixMenuItem->Checked = true;
	ListToImage4PixMenuItem->Checked = false;
	ListToImage8PixMenuItem->Checked = false;
	ListToImage16PixMenuItem->Checked = false;
	SetReg("CCDLAB", "UVLISTTOIMGPREC",UVLISTTOIMAGEPREC);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::ListToImage4PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVLISTTOIMAGEPREC = 4;
	ListToImage1PixMenuItem->Checked = false;
	ListToImage2PixMenuItem->Checked = false;
	ListToImage4PixMenuItem->Checked = true;
	ListToImage8PixMenuItem->Checked = false;
	ListToImage16PixMenuItem->Checked = false;
	SetReg("CCDLAB", "UVLISTTOIMGPREC",UVLISTTOIMAGEPREC);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::ListToImage8PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVLISTTOIMAGEPREC = 8;
	ListToImage1PixMenuItem->Checked = false;
	ListToImage2PixMenuItem->Checked = false;
	ListToImage4PixMenuItem->Checked = false;
	ListToImage8PixMenuItem->Checked = true;
	ListToImage16PixMenuItem->Checked = false;
	SetReg("CCDLAB", "UVLISTTOIMGPREC",UVLISTTOIMAGEPREC);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::ListToImage16PixMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVLISTTOIMAGEPREC = 16;
	ListToImage1PixMenuItem->Checked = false;
	ListToImage2PixMenuItem->Checked = false;
	ListToImage4PixMenuItem->Checked = false;
	ListToImage8PixMenuItem->Checked = false;
	ListToImage16PixMenuItem->Checked = true;
	SetReg("CCDLAB", "UVLISTTOIMGPREC", UVLISTTOIMAGEPREC);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
}

void Form1::ConvertListToImgMenu_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	
}

void Form1::UVAutoThreshChck_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ chan = IMAGESET[FILELISTINDEX]->GetKeyValue("CHANNEL");
	if (chan->Length == 0)
		chan = IMAGESET[FILELISTINDEX]->GetKeyValue("DETECTOR");

	if (chan == "VIS")
	{
		UVPixelMinThresh->Value = 400;
		UVShapeMinThresh->Value = 512;

		UVPixelMaxThresh->Value = 65536;
		UVShapeMaxThresh->Value = 1638400;
	}
	else if (chan == "NUV")
	{
		UVPixelMinThresh->Value = 500;
		UVShapeMinThresh->Value = 800;

		UVPixelMaxThresh->Value = 65536;
		UVShapeMaxThresh->Value = 1638400;
	}
	else if (chan == "FUV")
	{
		UVPixelMinThresh->Value = 300;
		UVShapeMinThresh->Value = 384;

		UVPixelMaxThresh->Value = 65536;
		UVShapeMaxThresh->Value = 1638400;
	}
	else
	{
		::MessageBox::Show("UVIT channel not identifiable...","Sorry!");
	}
}

void Form1::MaxMinThreshTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		::Convert::ToDouble(MaxMinThreshTxt->Text);
	}
	catch (...)
	{
		if (MaxMinThreshTxt->Text == "")
			return;
		else
			MaxMinThreshTxt->Text = "";
	}
	SetReg("CCDLAB", "MaxMinThreshTxtText",MaxMinThreshTxt->Text);
}

void Form1::MaxMinThreshChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (MaxMinThreshChck->Checked)
	{
		MaxMinThreshTxt->Enabled = true;
		MaxMinCountTwiceChck->Enabled = true;
	}
	else
	{
		MaxMinThreshTxt->Enabled = false;
		MaxMinCountTwiceChck->Enabled = false;
	}
	SetReg("CCDLAB", "MaxMinThreshChck",MaxMinThreshChck->Checked);
	SetReg("CCDLAB", "MaxMinThreshTxtEnab",MaxMinThreshTxt->Enabled);
	SetReg("CCDLAB", "MaxMinCountTwiceChckEnab",MaxMinCountTwiceChck->Enabled);
}

void Form1::MaxMinCountTwiceChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "MaxMinCountTwiceChck",MaxMinCountTwiceChck->Checked);

	UVITMenu->ShowDropDown();
	ConvertListToImgMenu->ShowDropDown();
	MaxMinThreshChck->ShowDropDown();
}

void Form1::ConvertListToImgMenu_Click(System::Object^  sender, System::EventArgs^  e)
{
	array<String^>^ IntsFileList;
	if (UVCREATEIMAGENOW)
	{
		UVCREATEIMAGENOW = false;
		UVCONVERTLISTTOIMAGEBATCH = false;
		IntsFileList = gcnew array<String^>(1) { UVCREATEIMAGEFILENAME };
		ConvertUVCentroidListToImgWrkr->RunWorkerAsync(IntsFileList);
	}
	else
	{
		UVITMenu->HideDropDown();
		ConvertListToImgMenu->HideDropDown();
		String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		OpenFileDialog^ dlg = gcnew OpenFileDialog();
		dlg->InitialDirectory = dir;
		dlg->Filter = "FITS (*.fits)|*.fits";
		dlg->Multiselect = true;
		dlg->Title = "Select the Centroid INTEGERS List(s) (_XYInts_List)";
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;

		IntsFileList = dlg->FileNames;
		int ind = IntsFileList[0]->LastIndexOf("\\");
		dir = IntsFileList[0]->Substring(0,ind);
		SetReg("CCDLAB", "L2EventListPath",dir);

		UVCONVERTLISTTOIMAGEBATCH = true;
		AUTOLOADIMAGESFILES = gcnew array<String^>(IntsFileList->Length);
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = IntsFileList->Length;
		WAITBAR->Text = "Creating image(s)...";
		Form1::Enabled = false;
		ConvertUVCentroidListToImgWrkr->RunWorkerAsync(IntsFileList);
		WAITBAR->ShowDialog();
	}
}

void Form1::ConvertUVCentroidListToImgWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ IntsFileList = (array<String^>^)e->Argument;

	bool do_parallel = true;
	if (UVIT_DEROTATE_WCS || IntsFileList->Length == 1)
		do_parallel = false;
	int n = 1;
	if (do_parallel)
		n = omp_get_max_threads();
	array<int>^ count = gcnew array<int>(n);
	int prog = 0;

	#pragma omp parallel for if (do_parallel)
	for (int wrkri = 0; wrkri < IntsFileList->Length; wrkri++)
	{
		if (UVCONVERTLISTTOIMAGEBATCH)
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				continue;

			count[omp_get_thread_num()]++;
			#pragma omp critical
			{
				int sum = 0;
				for (int si = 0; si < count->Length; si++)
					sum += count[si];
				if (sum * 100 / IntsFileList->Length > prog)
				{
					ConvertUVCentroidListToImgWrkr->ReportProgress(sum);
					prog = sum * 100 / IntsFileList->Length;
				}
			}
		}

		String^ IntsFile = IntsFileList[wrkri];
		String^ FracFile = IntsFile->Replace("Ints","Frac");

		JPFITS::FITSImage^ IntsFits = gcnew JPFITS::FITSImage(IntsFile, nullptr, true, true, false, !do_parallel);
		JPFITS::FITSImage^ FracFits = gcnew JPFITS::FITSImage(FracFile, nullptr, true, true, false, !do_parallel);
		int NPts = FracFits->Height;

		String^ channel = IntsFits->GetKeyValue("CHANNEL");
		if (channel->Length == 0)
			channel = IntsFits->GetKeyValue("DETECTOR");

		double prec = UVLISTTOIMAGEPREC;

		String^ EXTXRNG = FracFits->GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
		if (EXTXRNG == "")
			EXTXRNG = "0:511";//from L2 data
		String^ EXTYRNG = FracFits->GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
		if (EXTYRNG == "")
			EXTYRNG = "0:511";//from L2 data
		int ix = EXTXRNG->IndexOf(":");
		int iy = EXTYRNG->IndexOf(":");
		double rx1 = ::Convert::ToDouble(EXTXRNG->Substring(0,ix));//range start
		double ry1 = ::Convert::ToDouble(EXTYRNG->Substring(0,iy));
		double rx2 = ::Convert::ToDouble(EXTXRNG->Substring(ix+1));//range end
		double ry2 = ::Convert::ToDouble(EXTYRNG->Substring(iy+1));

		String^ xoffset = FracFits->GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
		if (xoffset == "")
			xoffset = FracFits->GetKeyValue("WIN_XOFF");//from L2 data
		double ox = ::Convert::ToDouble(xoffset);//x offset
		String^ yoffset = FracFits->GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
		if (yoffset == "")
			yoffset = FracFits->GetKeyValue("WIN_YOFF");//from L2 data
		double oy = ::Convert::ToDouble(yoffset);//y offset
		String^ sizex = FracFits->GetKeyValue("XSIZE");
		if (sizex == "")
			sizex = FracFits->GetKeyValue("WIN_X_SZ");
		double szx = ::Convert::ToDouble(sizex);//x size
		String^ sizey = FracFits->GetKeyValue("YSIZE");
		if (sizey == "")
			sizey = FracFits->GetKeyValue("WIN_Y_SZ");
		double szy = ::Convert::ToDouble(sizey);//y size

		if (rx1 != 0 && rx2 != 511)
			szx = rx2-rx1;
		if (ry1 != 0 && ry2 != 511)
			szy = ry2-ry1;

		if (L1CentroidPaddingChck->Checked)
		{
			if (PCCentroidPaddingDrop->SelectedIndex == 0)
				UVPCMODEPADOFFSET = 22;
			if (PCCentroidPaddingDrop->SelectedIndex == 1)
				UVPCMODEPADOFFSET = 44;
		}
		else
			UVPCMODEPADOFFSET = 0;

		szx = (szx + 1 + 2 * UVPCMODEPADOFFSET)*prec;
		szy = (szy + 1 + 2 * UVPCMODEPADOFFSET)*prec;

		array<double>^ times;//need times for total integration time calculation, and also if CR frames are removed
		String^ TimeFileList = IntsFile->Remove(IntsFile->IndexOf("XYInts_List")) + "TimeList.fits";
		String^ deDrift = "_deDrift";
		while (IntsFile->Contains(deDrift))
		{
			TimeFileList = TimeFileList->Replace("TimeList","TimeList_deDrift");
			deDrift += "_deDrift";
		}
		if (!File::Exists(TimeFileList))
		{
			::MessageBox::Show("Problem finding the time list file...","Stopping...");
			WAITBAR->CancelBtn->PerformClick();
			continue;
		}

		String^ BJDFileList = TimeFileList->Replace("TimeList","BJDList");

		String^ FrameFileList = TimeFileList->Replace("Time","Frame");
		array<double>^ frames;
		if (!File::Exists(FrameFileList))
		{
			::MessageBox::Show("Problem finding the frame list file...","Stopping...");
			WAITBAR->CancelBtn->PerformClick();
			continue;
		}

		String^ ExpArrayFileList = TimeFileList->Replace("TimeList", "ExpArrayList");
		bool applyexposureweight = ApplyExpArrayToImageChck->Checked;
		if (UVREGISTRATION)
			applyexposureweight = false;
		array<double>^ expweightlist;
		if (applyexposureweight && !File::Exists(ExpArrayFileList))
		{
			::MessageBox::Show("Problem finding the Exposure Array file...", "Stopping...");
			WAITBAR->CancelBtn->PerformClick();
			continue;
		}
		if (applyexposureweight)
			expweightlist = JPFITS::FITSImage::ReadImageVectorOnly(ExpArrayFileList, nullptr, !do_parallel);

		String^ FlatFileList;
		array<double>^ flats;
		bool applyFlat = ApplyFlatListToImageChck->Checked;
		if (applyFlat)
		{
			FlatFileList = TimeFileList->Replace("Time", "Flat");
			if (!File::Exists(FlatFileList))
			{
				::MessageBox::Show("Problem finding the flat list file...", "Stopping...");
				WAITBAR->CancelBtn->PerformClick();
				continue;
			}

			flats = FITSImage::ReadImageVectorOnly(FlatFileList, nullptr, !do_parallel);
		}

		bool maxminReject = MaxMinThreshChck->Checked;
		bool maxminCountTwice = MaxMinCountTwiceChck->Checked;
		double maxminThresh = ::Convert::ToDouble(MaxMinThreshTxt->Text);
		String^ MaxMinFileList;
		array<double, 2>^ mdMm;
		if (maxminReject)
		{
			MaxMinFileList = TimeFileList->Replace("TimeList", "XYmdMm_List");
			if (!File::Exists(MaxMinFileList))
			{
				::MessageBox::Show("Problem finding the corner stats list file...", "Stopping...");
				WAITBAR->CancelBtn->PerformClick();
				continue;
			}

			mdMm = FITSImage::ReadImageArrayOnly(MaxMinFileList, nullptr, !do_parallel);
		}

		times = FITSImage::ReadImageVectorOnly(TimeFileList, nullptr, !do_parallel);
		frames = FITSImage::ReadImageVectorOnly(FrameFileList, nullptr, !do_parallel);//should be no roll-overs in these
		double time_per_frame = (times[times->Length-1] - times[0]) / 1000 / (frames[times->Length-1] - frames[0]);//need to subtract this from total integration time whenver a CR frame is rejected
		String^ multstr = IntsFits->GetKeyValue("TIMEMULT");
		double mult = 1;
		if (multstr != "")
			mult = ::Convert::ToDouble(multstr);
		double physicaltime = (times[times->Length-1] - times[0] + time_per_frame*mult) / 1000;
		//double datatime = time_per_frame*(mult-1);
		int CRthresh = 0;
		double CRSigmaThresh = 0;
		bool filterCR = FilterCosmicRaysChckMenuItem->Checked;//used in the actual loop accumulating centroids
		bool FilterCRSigma = CosmicRayFilterSigmaMenuChck->Checked;
		bool FilterCRCount = CosmicRayFilterCountMenuChck->Checked;
		if (filterCR)//then load corresponding time list to search for highly repeated times to reject
		{
			//compute CRthresh for use below..it is either from the integer or sigma
			if (FilterCRCount)//integer
				CRthresh = ::Convert::ToInt32(CosmicRayFilterMenuTxt->Text);
			if (FilterCRSigma)//then set CRthresh given the sigma (use CRthresh as integer after computing sigma)
			{
				//find number of unique times
				int c = 1;
				double t0 = times[0];
				for (int i = 0; i < times->Length; i++)
				{
					if (t0 != times[i])
					{
						c++;
						t0 = times[i];
					}
				}

				array<double>^ framecount = gcnew array<double>(c);
				c = 0;
				t0 = times[0];
				int ind = -1;
				for (int i = 0; i < times->Length; i++)
				{
					if (t0 == times[i])
					{
						c++;
					}
					else
					{
						ind++;
						framecount[ind] = double(c);
						c = 1;
						t0 = times[i];
					}
				}
				framecount[ind+1] = double(c);

				double sigma = ::Convert::ToDouble(CosmicRayFilterSigmaMenuTxt->Text);
				double rmean = JPMath::Median(framecount);//JPMath::Mean_RobustClipped(framecount,sigma);
				double std = Math::Sqrt(rmean);

				CRthresh = int(rmean + sigma*std + 1); //+1 in order to ciel it
				CosmicRayFilterMenuTxt->Text = CRthresh.ToString();

			}//end filterCRSgima
		}

		int nCRframes = 0;
		double oldtime = -1;
		array<double, 2>^ img = gcnew array<double, 2>((int)szx, (int)szy);
		int xpos, ypos, el;
		double centroidweight;
		//bool exparrasctspersec = ExpArrayAsCtsperSecMenuChck->Checked;

		/*try
		{*/

			double rx132ox32 = -rx1 * 32 - ox * 32;
			double ry132oy32 = -ry1 * 32 - oy * 32;
			double precB32 = prec / 32;
			int PADOFFPREC = UVPCMODEPADOFFSET * int(prec);

			for (int j = 0; j < NPts; j++)
			{
				if (oldtime != times[j])
				{
					//datatime += time_per_frame;
					if (!filterCR)
						oldtime = times[j];
				}

				el = j;
				if (filterCR && oldtime != times[j])
				{
					oldtime = times[j];
					int c = 0;
					while (times[j] == times[j+c])
					{
						c++;
						if ((j+c) >= NPts)
							break;
					}
					if (c > CRthresh)//CR frame rejected
					{
						j = j + c;
						//datatime -= time_per_frame;
						nCRframes++;
						continue;
					}
				}

				xpos = (int)((IntsFits[0, j] + rx132ox32 + FracFits[0, j] + 16) * precB32) + PADOFFPREC;//reset integers to start at 0
				ypos = (int)((IntsFits[1, j] + ry132oy32 + FracFits[1, j] + 16) * precB32) + PADOFFPREC;//must add 16 to fractionals

				if (xpos < 0 || ypos < 0 || xpos >= szx || ypos >= szy)//ignore out of bounds
					continue;

				//if centroid decimal out of range (edge effect)
				/*if (FracFits[0, j] * FracFits[0, j] + FracFits[1, j] * FracFits[1, j] > 10 * 10)
					continue;*/

				//if max-min threshold - reject
				if (maxminReject && !maxminCountTwice)
					if (mdMm[1,j] > maxminThresh)
						continue;

				centroidweight = 1;

				if (applyexposureweight)
					if (expweightlist[j] < 0.2)//leave out of image if scaling is more than 1/0.2 = 5 times!
						continue;
					else
						centroidweight = 1 / expweightlist[j];//cts per second OR absolute...depending if switch was set during exparray creation time during applydriftseries

				if (applyFlat)
					centroidweight /= flats[j];

				if (maxminReject && maxminCountTwice)
				{
					if (mdMm[1,j] > maxminThresh)//mdMm only loaded if maxminCountTwice and maxminReject
					{
						img[xpos, ypos] += 2 * centroidweight;
					}
				}
				else
					img[xpos, ypos] += centroidweight;
			}
		/*}
		catch (::Exception^ e)
		{
			::MessageBox::Show(e->Message + "   " + xpos.ToString() + "   " + ypos.ToString() + "    "   + el.ToString());// + "   " + FracFits[0,j].ToString() + "   " + FracFits[1,j].ToString() );
			::MessageBox::Show(IntsFits[0,el].ToString() + "	" + IntsFits[1,el].ToString() + "	" + FracFits[0,el].ToString() + "	" + FracFits[1,el].ToString());
			MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
		}*/

		String^ imgname = IntsFile->Replace("_XYInts_List","");
		imgname = imgname->Replace(".fits", "_IMAGE_x" + prec.ToString() + ".fits");
		if (filterCR)
			imgname = imgname->Replace(".fits", "_deCR" + CRthresh.ToString() + ".fits");
		if (applyFlat)
			imgname = imgname->Replace(".fits", "_deFlat.fits");
		if (maxminReject)
			imgname = imgname->Replace(".fits", "_deMm" + maxminThresh.ToString() + ".fits");
		if (applyexposureweight)
			imgname = imgname->Replace(".fits", "_deExp.fits");

		JPFITS::FITSImage^ fitsimg = gcnew FITSImage(imgname, img, false, !do_parallel);
		fitsimg->CopyHeader(FracFits);

		double missingframephotredc = 0, parityphotredc = 0;
		try
		{
			missingframephotredc = Convert::ToDouble(fitsimg->GetKeyValue("FRAMREDC"));
			parityphotredc = Convert::ToDouble(fitsimg->GetKeyValue("PARTREDC"));
		}
		catch (...)
		{
			missingframephotredc = 0;
			parityphotredc = 0;
		}
		double datatime = physicaltime * (1 - missingframephotredc) - nCRframes * time_per_frame;
		double rdcdtime = datatime * (1 - parityphotredc);
		
		fitsimg->AddKey("TIMEPERF", time_per_frame.ToString("#.000000"), "Time per Frame (s)", 14);
		fitsimg->AddKey("FRAMPERS", (1/time_per_frame).ToString("#.000"), "Frames per Second", 14);
		fitsimg->AddKey("NCOSMICF", nCRframes.ToString(), "Number of rejected cosmic ray frames", 14);
		fitsimg->AddKey("PHYSTIME", physicaltime.ToString("#.000"), "Physical Integration Time for Image (s)", 14);
		fitsimg->AddKey("DATATIME", datatime.ToString("#.000"), "PHYSTIME Reduced for Cosmic and Missing Frames (s)", 14);
		fitsimg->AddKey("RDCDTIME", rdcdtime.ToString("#.000"), "DATATIME Reduced for Parity Errors (s)", 14);
		fitsimg->SetKey("EXP_TIME", rdcdtime.ToString("#.000"), "Same as RDCDTIME-Final Science Integration Time(s)", true, 14);

		double bjd0 = 0;
		try
		{
			bjd0 = ::Convert::ToDouble(fitsimg->GetKeyValue("BJD0"));
		}
		catch (...)
		{
			if (::File::Exists(BJDFileList))
			{
				array<double>^ bjd = FITSImage::ReadImageVectorOnly(BJDFileList, nullptr, !do_parallel);
				bjd0 = bjd[0];
			}
		}
		double meanBJD = bjd0 + physicaltime/2/1000/86400;
		fitsimg->AddKey("MEANBJD",meanBJD.ToString("#.0000000"),"Mean Heliocentric Julian Date for Image",12);

		if (filterCR)
		{
			fitsimg->AddKey("CRCUTOFF",CRthresh.ToString(),"Cosmic Ray Cutoff Count per Frame Threshold",13);
			fitsimg->AddKey("CRFRTIME",(double(nCRframes)*time_per_frame/1000).ToString("#.000"),"Cosmic Ray Time Removed from Original List",13);
		}

		if (maxminReject)
		{
			fitsimg->AddKey("MAXMINTH",maxminThresh.ToString(),"Max-Min Threshold",12);
			if (maxminCountTwice)
				fitsimg->AddKey("MAXMINCT","true","Max-Min Threshold Counted Twice",12);
		}

		fitsimg->AddKey("IMAGPREC", prec.ToString(), "Image Pixel Precision",13);
		fitsimg->AddKey("PADOFSET", UVPCMODEPADOFFSET.ToString(), "Image Padding (CMOS pixels)", 13);

		if (UVIT_DEROTATE_WCS)//then re-compute WCS from de-rotated image...need to re-get centroids from image, update their CP1/2_ values in header, then do & update WCS params
		{
			if (wrkri == 0)//get CV's & CP's...CP's will need to be updated with new centroids for the first file only
			{
				int num = 0, key = 0;
				while (key != -1)
				{
					num++;
					key = fitsimg->GetKeyIndex("WCP1_" + num.ToString("000"));
				}
				num--;
				array<double>^ xpix = gcnew array<double>(num);
				array<double>^ ypix = gcnew array<double>(num);
				array<double>^ radeg = gcnew array<double>(num);
				array<double>^ dedeg = gcnew array<double>(num);
				int goodcount = 0;
				for (int j = 1; j <= num; j++)
				{
					xpix[goodcount] = Convert::ToDouble(fitsimg->GetKeyValue("WCP1_" + j.ToString("000")));
					ypix[goodcount] = Convert::ToDouble(fitsimg->GetKeyValue("WCP2_" + j.ToString("000")));
					radeg[goodcount] = Convert::ToDouble(fitsimg->GetKeyValue("WCV1_" + j.ToString("000")));
					dedeg[goodcount] = Convert::ToDouble(fitsimg->GetKeyValue("WCV2_" + j.ToString("000")));

					if (xpix[goodcount] > 0 && ypix[goodcount] > 0 && xpix[goodcount] < szx && ypix[goodcount] < szy)
						goodcount++;
				}
				Array::Resize(xpix, goodcount - 1);
				Array::Resize(ypix, goodcount - 1);
				Array::Resize(radeg, goodcount - 1);
				Array::Resize(dedeg, goodcount - 1);
				//now have CP's and CV's...now need to re-do centroids at CV locations
				PSE = gcnew JPFITS::SourceExtractor();
				PSE->Extract_Sources(fitsimg->Image, xpix, ypix, 2, false, "");
				xpix = PSE->Centroids_X;
				ypix = PSE->Centroids_Y;
				WCS_DEROT = gcnew JPFITS::WorldCoordinateSolution();
				WCS_DEROT->Solve_WCS("TAN", xpix, ypix, true, radeg, dedeg, fitsimg);
			}
			else
				WCS_DEROT->CopyTo(fitsimg);
			//fitsimg is now updated with new WCS for new derotated image
		}

		if (applyFlat || applyexposureweight)
			fitsimg->WriteImage(TypeCode::Double, !do_parallel);
		else
			fitsimg->WriteImage(TypeCode::Int32, !do_parallel);

		if (!do_parallel)
			e->Result = imgname;//used in wrkr complete, for single image modes

		if (UVDRIFTBATCH)
			AUTOLOADIMAGESFILES[UVDRIFTBATCHFILESINDEX] = imgname;

		if (UVCONVERTLISTTOIMAGEBATCH)
			AUTOLOADIMAGESFILES[wrkri] = imgname;
	}
}

void Form1::ConvertUVCentroidListToImgWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = "Converting file " + (e->ProgressPercentage).ToString() + " of " + WAITBAR->ProgressBar->Maximum.ToString() + " to image.";
	WAITBAR->Refresh();
}

void Form1::ConvertUVCentroidListToImgWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (UVIT_DEROTATE_WCS)
		UVIT_DEROTATE_WCS = false;

	if (!UVCONVERTLISTTOIMAGEBATCH)
	{
		String^ imgname = (String^)e->Result;
		if (!UVDRIFTAUTORUN)
		{
			if (!UVREGISTRATION)
				if (::MessageBox::Show("Image Creation Completed.  Would you like to view it?", "Finished...", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
				{
					Form1::Enabled = true;
					Form1::BringToFront();
					return;
				}

			FileListDrop->Items->Clear();
			IMAGESET->Clear();
			array<String^>^ filelist = gcnew array<String^>(1) { imgname };
			AddToImageSet(filelist);
			Form1::Enabled = true;
			Form1::BringToFront();

			if (UVREGISTRATION)
			{
				//update registration points by shifting anchor (and all the rest) to closest local maximum of anchor
				if (UVREGISTRATIONFILESINDEX > 0)
				{
					float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);//image window size per data image pixel
					float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);

					array<double, 2>^ subim = IMAGESET[FILELISTINDEX]->GetSubImage(MANREGCOORDS[0, 0], MANREGCOORDS[0, 1], SUBIMAGE_HWX, SUBIMAGE_HWY);
					int x, y;
					JPMath::Max(subim, x, y, false);
					x -= SUBIMAGE_HWX;
					y -= SUBIMAGE_HWY;
					for (int i = 0; i < MANREGCOORDS->GetLength(0); i++)
					{
						MANREGCOORDS[i, 0] += x;
						MANREGCOORDS[i, 1] += y;
						MANREGCOORDRECTS[i] = Rectangle(int((float(MANREGCOORDS[i, 0] + 1)) * xsc - 3), int((float(MANREGCOORDS[i, 1] + 1)) * ysc - 3), 7, 7);
					}
					ImageUpD(IMAGESET[FILELISTINDEX]->Image);
					SubImageUpD();
				}
				try
				{
					::File::Delete(imgname);
				}
				catch (...){}

				if (UVITAUTOREGISTER)
				{
					//MessageBox::Show("here");
					ProgressBar->Value = UVREGISTRATIONFILESINDEX + 1;
					ProgressBar->Refresh();

					ImageWindow_MouseUp(sender, gcnew ::Windows::Forms::MouseEventArgs(Windows::Forms::MouseButtons::Right, 1, 0, 0, 0));
				}
				else
				{
					ProgressBar->Maximum = 2;
					ProgressBar->Value = 2;
					ProgressBar->Refresh();
				}
			}
		}
		else
		{
			if (UVAutoDriftImageViewChck->Checked)
			{
				WAITBAR->TextMsg->Text = "Loading image...";
				WAITBAR->Text = "Viewing...";
				WAITBAR->Refresh();

				FileListDrop->Items->Clear();
				IMAGESET->Clear();
				array<String^>^ filelist = gcnew array<String^>(1) { imgname };
				AddToImageSet(filelist);
			}
			WAITBAR->CancelBtn->Enabled = true;
			if (!UVDRIFTBATCH)
			{
				WAITBAR->Hide();
				WAITBAR->Close();
				Form1::Enabled = true;
			}
			else
			{
				UVDRIFTBATCHFILESINDEX++;
				if (UVDRIFTBATCHFILESINDEX < UVDRIFTBATCHFILES->Length)//continue batch
				{
					if (!DRIFTFROMPCPSTRACK)
						CreateDriftFromPCMenuItem_DoubleClick(sender, e);
					else
						DriftFromPCPSTrackBtn_Click(sender, e);
				}
				else
				{
					DRIFTFROMPCPSTRACK = false;
					UVDRIFTBATCH = false;
					WAITBAR->Hide();
					WAITBAR->Close();
					Form1::Enabled = true;
					Form1::BringToFront();
					TimeSpan ts = ::DateTime::Now - DATE;
					/*::DialogResult res = MessageBox::Show("Finished the batch of drift corrections in " + ts.Minutes.ToString() + "m" + ts.Seconds.ToString() + "s.  Would you like to view the images?", "Complete. View Images?", ::MessageBoxButtons::YesNo);
					if (res == ::DialogResult::No)
						return;*/
					AUTOLOADIMAGES = true;
					IMAGESET = gcnew FITSImageSet();
					FMLoad_Click(sender, e);
					//FMLoad->PerformClick();
				}
			}
		}
	}
	else
	{
		UVCONVERTLISTTOIMAGEBATCH = false;
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
		{
			Form1::Enabled = true;
			Form1::BringToFront();
			UVITPOSTMERGE = false;
			return;
		}

		WAITBAR->Hide();
		WAITBAR->Close();
		Form1::Enabled = true;
		Form1::BringToFront();

		/*if (MessageBox::Show("Finished converting the list(s) to image(s).  Would you like to load them?","View?",::MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;*/

		AUTOLOADIMAGES = true;

		if (AUTOVISDRIFTAPPLY && FUVDIREXISTS && NUVDIREXISTS)
		{
			FUVDIREXISTS = false;
			IMAGESET = gcnew FITSImageSet();
			FMLoad_Click(sender, e);
			//FMLoad->PerformClick();
			DONUVDRIFTNOW = true;
			ConsolidateNUVApplyToFUV_Click(sender, e);
			return;
		}
		else if (AUTOVISDRIFTAPPLY && !FUVDIREXISTS && NUVDIREXISTS)
		{
			FUVDIREXISTS = false;
			NUVDIREXISTS = false;
			AUTOVISDRIFTAPPLY = false;
			FMLoad_Click(sender, e);
			//FMLoad->PerformClick();
			return;
		}

		IMAGESET = gcnew FITSImageSet();
		FMLoad_Click(sender, e);
		//FMLoad->PerformClick();

		if (UVITPOSTMERGE)
		{
			UVITPOSTMERGE = false;
			if (UVAutoPSFPostMergeChck->Checked)
			{
				PointSrcROIAutoRunChck->Checked = true;
				PointSrcROIFindSrcChck->Checked = true;
				PointSrcROIFindNSrcDrop->SelectedIndex = 2;
				DriftFromPCPSTrackBtn_Click(sender, e);
				return;
			}
		}
	}
}

void Form1::ExtractL1gzsMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	L1AutoRunChck->HideDropDown();
	ExtractL1gzsMenuItem->HideDropDown();
	UVITMenu->HideDropDown();

	if (!Directory::Exists("C:\\Program Files\\7-Zip"))
	{
		MessageBox::Show("7-Zip not installed on this system.  Please download & install the 64-bit version from 7-zip.org to C:\\Program Files\\7-Zip", "Error...");
		return;
	}

	::OpenFileDialog^ ofd = gcnew ::OpenFileDialog();
	ofd->InitialDirectory = (String^)GetReg("CCDLAB", "L2EventListPath");
	ofd->Filter = "GZip or ZIP Archive|*.gz;*.zip";
	ofd->Multiselect = false;// true;//no need to do this//removed from code
	::DialogResult res = ofd->ShowDialog();
	if (res == ::DialogResult::Cancel)
		return;

	String^ dir = DirectoryInfo(ofd->FileName).Parent->FullName;
	SetReg("CCDLAB", "L2EventListPath", dir);

	Form1::Enabled = false;
	ExtractL1ArchiveBGWrkr->RunWorkerAsync(ofd->FileName);
}

void Form1::ExtractL1ArchiveBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	String^ file = (String^)e->Argument;
	String^ extdir = DirectoryInfo(file).Parent->FullName;
	String^ archdir = extdir + "\\archive";
	::Directory::CreateDirectory(archdir);

	Diagnostics::ProcessStartInfo^ psi = gcnew Diagnostics::ProcessStartInfo("c:\\Program Files\\7-Zip\\7zG.exe");
	psi->Arguments = "\"x\" " + "\"" + file + "\" " + "\"-o" + extdir;
	Diagnostics::Process^ proc = Diagnostics::Process::Start(psi);
	proc->WaitForExit();
	if (proc->ExitCode != 0)
	{
		e->Result = ::DialogResult::Cancel;
		return;
	}
	e->Result = ::DialogResult::OK;
	File::Move(file, archdir + "\\" + file->Substring(file->LastIndexOf("\\") + 1));
}

void Form1::ExtractL1ArchiveBGWrkr_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) { ; }

void Form1::ExtractL1ArchiveBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	Form1::Enabled = true;
	Form1::BringToFront();
	if ((::DialogResult)e->Result == ::DialogResult::Cancel)
		return;

	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	array<String^>^ L1FITSImages = Directory::GetFiles(dir, "*level1.fits", ::IO::SearchOption::AllDirectories);
	//remember where the L1 files folder was to delete it after
	array<String^>^ alldirs = Directory::GetDirectories(dir);
	String^ deldir;
	for (int i = 0; i < alldirs->Length; i++)
		if (Directory::GetFiles(alldirs[i], "*level1.fits", ::IO::SearchOption::AllDirectories)->Length > 0)
		{
			deldir = alldirs[i];
			break;
		}

	for (int j = 0; j < L1FITSImages->Length; j++)
	{
		String^ newL1file = dir + "\\" + L1FITSImages[j]->Substring(L1FITSImages[j]->LastIndexOf("\\") + 1);
		while (::File::Exists(newL1file))//then need to add some appendage
		{
			int ind = newL1file->LastIndexOf(".");
			if (newL1file->Substring(ind - 1, 1) == ")")
			{
				int num = ::Convert::ToInt32(newL1file->Substring(newL1file->LastIndexOf("(") + 1, newL1file->LastIndexOf(")") - 1 - newL1file->LastIndexOf("(")));
				newL1file = newL1file->Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
			}
			else
			{
				newL1file = newL1file->Insert(ind, " (1)");
				if (::File::Exists(newL1file))
				{
					int num = ::Convert::ToInt32(newL1file->Substring(newL1file->LastIndexOf("(") + 1, newL1file->LastIndexOf(")") - 1 - newL1file->LastIndexOf("(")));
					newL1file = newL1file->Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
				}
			}
		}
		::File::Move(L1FITSImages[j], newL1file);
	}

	array<String^>^ L1tctfiles = ::Directory::GetFiles(dir, "*level1.tct", ::IO::SearchOption::AllDirectories);
	for (int j = 0; j < L1tctfiles->Length; j++)
	{
		String^ newL1file = dir + "\\" + L1tctfiles[j]->Substring(L1tctfiles[j]->LastIndexOf("\\") + 1);
		while (::File::Exists(newL1file))//then need to add some appendage
		{
			int ind = newL1file->LastIndexOf(".");
			if (newL1file->Substring(ind - 1, 1) == ")")
			{
				int num = ::Convert::ToInt32(newL1file->Substring(newL1file->LastIndexOf("(") + 1, newL1file->LastIndexOf(")") - 1 - newL1file->LastIndexOf("(")));
				newL1file = newL1file->Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
			}
			else
			{
				newL1file = newL1file->Insert(ind, " (1)");
				if (::File::Exists(newL1file))
				{
					int num = ::Convert::ToInt32(newL1file->Substring(newL1file->LastIndexOf("(") + 1, newL1file->LastIndexOf(")") - 1 - newL1file->LastIndexOf("(")));
					newL1file = newL1file->Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
				}
			}
		}
		::File::Move(L1tctfiles[j], newL1file);
	}

	array<String^>^ L1lbtfiles = ::Directory::GetFiles(dir, "*level1.lbt", ::IO::SearchOption::AllDirectories);
	for (int j = 0; j < L1lbtfiles->Length; j++)
	{
		String^ newL1file = dir + "\\" + L1lbtfiles[j]->Substring(L1lbtfiles[j]->LastIndexOf("\\") + 1);
		while (::File::Exists(newL1file))//then need to add some appendage
		{
			int ind = newL1file->LastIndexOf(".");
			if (newL1file->Substring(ind - 1, 1) == ")")
			{
				int num = ::Convert::ToInt32(newL1file->Substring(newL1file->LastIndexOf("(") + 1, newL1file->LastIndexOf(")") - 1 - newL1file->LastIndexOf("(")));
				newL1file = newL1file->Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
			}
			else
			{
				newL1file = newL1file->Insert(ind, " (1)");
				if (::File::Exists(newL1file))
				{
					int num = ::Convert::ToInt32(newL1file->Substring(newL1file->LastIndexOf("(") + 1, newL1file->LastIndexOf(")") - 1 - newL1file->LastIndexOf("(")));
					newL1file = newL1file->Replace("(" + num.ToString() + ").", "(" + (num + 1).ToString() + ").");
				}
			}
		}
		::File::Move(L1lbtfiles[j], newL1file);
	}

	Directory::Delete(deldir, true);

	if (!L1AutoRunChck->Checked)
		if (::MessageBox::Show("Finished processing folders.  Would you like to proceed with file digestion?", "Proceed?", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;

	SPAREFITSImageSet = gcnew FITSImageSet();

	array<String^>^ files = ::Directory::GetFiles(dir, "*level1*.fits");
	DATE = DateTime::Now;
	Form1::Enabled = false;
	WAITBAR = gcnew ::JPWaitBar::WaitBar();
	WAITBAR->Text = "Digesting L1 Files...";
	WAITBAR->ProgressBar->Maximum = files->Length;
	DigestL1Wrkr->RunWorkerAsync(files);
	WAITBAR->ShowDialog();
}

void Form1::DigestL1FITSImageMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->HideDropDown();
	DigestL1FITSImageMenuItem->HideDropDown();
	L1AutoRunChck->Checked = false;

	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "L1 Event List (*.fits)|*.fits";
	dlg->Multiselect = true;
	dlg->Title = "Please select the L1 files...";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;

	dir = dlg->FileNames[0]->Substring(0, dlg->FileNames[0]->LastIndexOf("\\"));
	bool multidir = false;
	for (int i = 0; i < dlg->FileNames->Length; i++)
		if (dir != dlg->FileNames[i]->Substring(0, dlg->FileNames[i]->LastIndexOf("\\")))
		{
			multidir = true;
			dir = dir->Substring(0, dir->LastIndexOf("\\"));
			break;
		}
	SetReg("CCDLAB", "L2EventListPath", dir);
	SetReg("CCDLAB", "L1ExtractMultiDir", multidir);

	if (L1TBCChck->Checked)//must establish reference tickcount to imageframetime
	{
		DO_TBC = true;
		::DialogResult res = TBC_Reference(dlg->FileNames);
		if (res == ::DialogResult::OK)
			MessageBox::Show("Found Reference:  TICKCOUNT = " + TBC_TICKCOUNTREF + "; FRAMETIME = " + TBC_FRAMETIMEREF + "; TIME = " + TBC_TIMEREF);
		if (res == ::DialogResult::Yes)
		{
			try
			{
				TBC_TICKCOUNTREF = Convert::ToInt64(GetReg("CCDLAB", "TBC_TICKCOUNTREF"));
				TBC_FRAMETIMEREF = Convert::ToInt64(GetReg("CCDLAB", "TBC_FRAMETIMEREF"));
				TBC_TIMEREF = Convert::ToDouble(GetReg("CCDLAB", "TBC_TIMEREF"));
			}
			catch (...) {}
			MessageBox::Show("Using Previous Reference:  TICKCOUNT = " + TBC_TICKCOUNTREF + "; FRAMETIME = " + TBC_FRAMETIMEREF + "; TIME = " + TBC_TIMEREF);
		}
		if (res == ::DialogResult::No)
			DO_TBC = false;
		if (res == ::DialogResult::Cancel)
			return;
	}

	SPAREFITSImageSet = gcnew FITSImageSet();

	DATE = DateTime::Now;
	Form1::Enabled = false;
	WAITBAR = gcnew ::JPWaitBar::WaitBar();
	WAITBAR->Text = "Digesting L1 Files...";
	WAITBAR->ProgressBar->Maximum = dlg->FileNames->Length;
	DigestL1Wrkr->RunWorkerAsync(dlg->FileNames);
	WAITBAR->ShowDialog();
}

void Form1::DigestL1Wrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ argfiles = (array<String^>^)e->Argument;

	bool ApplyDIST = L1DigestApplyDISTChck->Checked;
	bool ApplyFPN  = L1DigestApplyFPNChck->Checked;

	::ArrayList^ dir_list = gcnew ArrayList();

	int errorfileindex = 0;

	try
	{
		for (int xi = 0; xi < argfiles->Length; xi++)
		{
			errorfileindex = xi;
			String^ FileName = argfiles[xi];
			String^ dir = FileName->Substring(0,FileName->LastIndexOf("\\"));
			String^ path = dir;
			FITSImage^ source = gcnew FITSImage(FileName, nullptr, true, false, false, false);
			String^ mode = source->GetKeyValue("OBS_MODE");
			if (mode != "PC" && mode != "IM")
			{
				MessageBox::Show("Can't determine observation mode: " + mode, "Error...");
				return;
			}

			FileStream^ fs = gcnew FileStream(FileName,IO::FileMode::Open);
			BufferedStream ^ bs = gcnew BufferedStream(fs);
			array<unsigned char>^ c = gcnew array<unsigned char>(2880);

			int naxis, naxis1, naxis2, bitpix;
			//read past primary header
			bool end = false;
			while (end == false)
			{
				//read 2880 block
				bs->Read(c,0,2880);//stream will be placed at end of header block, so that it can begin reading data values or 2ndry header
				for (int i = 0; i < 36; i++)
				{
					String^ line = System::Text::Encoding::ASCII->GetString(c,i*80,80);

					if (line->Substring(0,5)->Equals("NAXIS"))
						naxis = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("NAXIS1"))
						naxis1 = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("NAXIS2"))
						naxis2 = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("BITPIX"))
						bitpix = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,8)->Equals("END     "))//check if we're at the end of the header keys
					{
						end = true;
						break;
					}
				}
			}
			//now at end of primary header; if primary header has image data, must skip past it
			if (naxis != 0)
			{
				__int64 NBytes = __int64(naxis1)*__int64(naxis2)*__int64(::Math::Abs(bitpix))/8;
				__int64 rem;
				::Math::DivRem(NBytes,2880,rem);
				bs->Seek(NBytes+(2880-rem),::SeekOrigin::Current);
			}
			//should now be at a header extension
			//read it until it is as its end, then skip again to 2nd extension

			end = false;
			while (end == false)
			{
				//read 2880 block
				bs->Read(c,0,2880);//stream will be placed at end of header block, so that it can begin reading data values or 2ndry header
				for (int i = 0; i < 36; i++)
				{
					String^ line = System::Text::Encoding::ASCII->GetString(c,i*80,80);

					if (line->Substring(0,5)->Equals("NAXIS"))
						naxis = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("NAXIS1"))
						naxis1 = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("NAXIS2"))
						naxis2 = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("BITPIX"))
						bitpix = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,8)->Equals("END     "))//check if we're at the end of the header keys
					{
						end = true;
						break;
					}
				}
			}

			//now at end of 1st extension header, skip its data
			if (naxis != 0)
			{
				__int64 Nbytes = __int64(naxis1)*__int64(naxis2)*__int64(::Math::Abs(bitpix))/8;
				__int64 rem;
				::Math::DivRem(Nbytes,2880,rem);
				bs->Seek(Nbytes+(2880-rem),::SeekOrigin::Current);
			}

			//should now be at 2nd extension header
			//read it until it is as its end
			int width = 0;
			end = false;
			while (end == false)
			{
				//read 2880 block
				bs->Read(c,0,2880);//stream will be placed at end of header block, so that it can begin reading data values or 2ndry header
				for (int i = 0; i < 36; i++)
				{
					String^ line = System::Text::Encoding::ASCII->GetString(c,i*80,80);

					if (line->Substring(0,6)->Equals("NAXIS1"))
						naxis1 = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("NAXIS2"))
						naxis2 = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,6)->Equals("BITPIX"))
						bitpix = ::Convert::ToInt32(line->Substring(10,20));
					if (line->Substring(0,7)->Equals("TFORM15"))
					{
						String^ tform15 = line->Substring(11,6);
						tform15 = tform15->Replace("B","");//PC mode
						tform15 = tform15->Replace("I","");//IM mode
						width = ::Convert::ToInt32(tform15);
					}
					if (line->Substring(0,8)->Equals("END     "))//check if we're at the end of the header keys
						end = true;
				}
			}//now ready to get the L1 data
			__int64 file_bspos = bs->Position;

			//TCT get the .tct file, and get the delta between absolute time and detector time from the first element in those tables
			//apply (add) that difference to all detector times in order to get absolute local JD times, then use that to get BJD
			double JD_abs_time_delta_sec;
			String^ tctfile = FileName->Substring(0,FileName->LastIndexOf("uvt")) + "uvt_level1.tct";
			bool tctfileexists = ::File::Exists(tctfile);
			try//sometimes the tct file is empty?
			{
				if (tctfileexists)
				{
					TCTFILELIST->Add(tctfile);

					JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(tctfile, "TCT");
					array<double>^ SPS_TIME_MJD = bt->GetTTYPEEntry("SPS_TIME_MJD");
					array<double>^ LOCAL_TIMEF = bt->GetTTYPEEntry("LOCAL_TIMEF");

					//array<double>^ SPS_TIME_MJD = JPFITS::FITSBinTable::GetExtensionEntry(tctfile, "TCT", "SPS_TIME_MJD");
					double mjdref = SPS_TIME_MJD[0];
					//array<double>^ LOCAL_TIMEF = JPFITS::FITSBinTable::GetExtensionEntry(tctfile, "TCT", "LOCAL_TIMEF");
					double detref = LOCAL_TIMEF[0];
					JD_abs_time_delta_sec = 2455197.5 * 86400 + mjdref - detref;
				}
			}
			catch (...) {}

			//LBT get the lbt file to do filter correction
			String^ lbtfile = FileName->Substring(0, FileName->LastIndexOf("uvt")) + "uvt_level1.lbt";
			bool lbtfileexists = ::File::Exists(lbtfile);
			array<double>^ lbt_times;
			array<double>^ lbt_FUVfwangle;
			array<double>^ lbt_NUVfwangle;
			array<double>^ lbt_VISfwangle;
			double lasttime_mjd_forfilter = Double::MinValue;
			double firsttime_mjd_forfilter = Double::MaxValue;
			bool dofiltercorrection = L1FilterCorrectionChck->Checked;
			if (lbtfileexists)
			{
				LBTFILELIST->Add(lbtfile);

				if (dofiltercorrection)
				{
					JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(lbtfile, "UVIT-LBTHK");
					lbt_times = bt->GetTTYPEEntry("Time");
					lbt_FUVfwangle = bt->GetTTYPEEntry("FilterWheelMotorAngle_FUV");
					lbt_NUVfwangle = bt->GetTTYPEEntry("FilterWheelMotorAngle_NUV");
					lbt_VISfwangle = bt->GetTTYPEEntry("FilterWheelMotorAngle_VIS");

					/*lbt_times = JPFITS::FITSBinTable::GetExtensionEntry(lbtfile, "UVIT-LBTHK", "Time");
					lbt_FUVfwangle = JPFITS::FITSBinTable::GetExtensionEntry(lbtfile, "UVIT-LBTHK", "FilterWheelMotorAngle_FUV");
					lbt_NUVfwangle = JPFITS::FITSBinTable::GetExtensionEntry(lbtfile, "UVIT-LBTHK", "FilterWheelMotorAngle_NUV");
					lbt_VISfwangle = JPFITS::FITSBinTable::GetExtensionEntry(lbtfile, "UVIT-LBTHK", "FilterWheelMotorAngle_VIS");*/
				}
			}
			else
			{
				if (dofiltercorrection && !lbtfileexists)
				{
					MessageBox::Show("Filter correction requested but lbt file not found.  Exiting.", "Error");
					WAITBAR->CancelBtn->PerformClick();
					return;
				}
			}
			
			String^ filterindex = UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER"));
			source->SetKey("FILTERID", filterindex, "Filter type", true, source->GetKeyIndex("FILTER") + 1);
			
			if (mode == "PC")
			{
				try
				{
					if (WAITBAR->DialogResult == ::DialogResult::Cancel)
						return;
					DigestL1Wrkr->ReportProgress(xi + 1, mode + "_" + argfiles->Length);

					int NBytes = naxis1 * naxis2;
					array<unsigned char>^ arr = gcnew array<unsigned char>(NBytes);
					bs->Read(arr, 0, NBytes);
					bs->Close();
					fs->Close();

					if (NBytes < 150000)
						goto skipto;

					if (DO_TBC)
						TBC(arr, naxis1, naxis2);

					bool discardparityerror = L1DigestPCParityChck->Checked;
					bool xword_parity_error = false;
					bool yword_parity_error = false;
					bool sword_parity_error = false;

					bool discardtimebool = L1DiscardDataTimeChck->Checked;
					unsigned int discardtimeint;
					if (discardtimebool)
					{
						String^ discardtimestring = (String^)L1DiscardDataTimeDrop->SelectedItem;
						discardtimestring = discardtimestring->Replace(" Minutes", "");
						discardtimeint = ::Convert::ToInt32(discardtimestring) * 60 * 1000;
					}

					String^ channel = source->GetKeyValue("DETECTOR");
					String^ alg = source->GetKeyValue("CENTROID");
					if (alg != "5S" && alg != "3S")//happened once with some L1 file
						alg = "3S"; //3S is always running in orbit now...so just assume
					String^ FPNFile;
					FITSImage^ FPNFits;
					Random^ rand;
					int N_p_errors = 0;

					if (ApplyFPN)
					{
						if (channel == "FUV")
						{
							if (alg == "3S")
							{
								if (::File::Exists("C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits"))
									FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 3Sq FPN.fits";
							}
							if (alg == "5S")
							{
								if (::File::Exists("C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits"))
									FPNFile = "C:\\UVIT_CalDB\\FPN\\FUV 5Sq FPN.fits";
							}
						}
						else if (channel == "NUV")
						{
							if (alg == "3S")
							{
								if (::File::Exists("C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits"))
									FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 3Sq FPN.fits";
							}
							if (alg == "5S")
							{
								if (::File::Exists("C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits"))
									FPNFile = "C:\\UVIT_CalDB\\FPN\\NUV 5Sq FPN.fits";
							}
						}
						else if (channel == "VIS")
						{
							if (alg == "3S")
							{
								if (::File::Exists("C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits"))
									FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 3Sq FPN.fits";
							}
							if (alg == "5S")
							{
								if (::File::Exists("C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits"))
									FPNFile = "C:\\UVIT_CalDB\\FPN\\VIS 5Sq FPN.fits";
							}
						}
						else
						{
							//get the FPN correction table
							OpenFileDialog^ dlg = gcnew OpenFileDialog();
							dlg->Filter = "FITS (*.fits)|*.fits";
							dlg->Multiselect = false;
							dlg->Title = "Select FPN Correction FITS Image File";
							::DialogResult res = dlg->ShowDialog();
							if (res != ::DialogResult::OK)
								return;
							FPNFile = dlg->FileName;
						}
						FPNFits = gcnew JPFITS::FITSImage(FPNFile, nullptr, true, true, false, true);
						rand = gcnew Random();
					}

					String^ CPUXDistFile;
					String^ CPUYDistFile;
					JPFITS::FITSImage^ CPUXDistFits;
					JPFITS::FITSImage^ CPUYDistFits;
					if (ApplyDIST)
					{
						if (channel == "FUV")
						{
							if (::File::Exists("C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits"))
							{
								CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dX.fits";
								CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\FUV_dist_dY.fits";
							}
						}
						else if (channel == "NUV")
						{
							if (::File::Exists("C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits"))
							{
								CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dX.fits";
								CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\NUV_dist_dY.fits";
							}
						}
						else if (channel == "VIS")
						{
							if (::File::Exists("C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits"))
							{
								CPUXDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dX.fits";
								CPUYDistFile = "C:\\UVIT_CalDB\\Distortion\\VIS_dist_dY.fits";
							}
						}
						else
						{
							OpenFileDialog^ dlg = gcnew OpenFileDialog();
							dlg->Filter = "FITS (*.fits)|*.fits";
							dlg->Multiselect = false;
							//get the CPU *X* correction image
							dlg->Title = "Select CPU *X* Correction FITS Image File";
							::DialogResult res = dlg->ShowDialog();
							if (res != ::DialogResult::OK)
								return;
							String^ CPUXDistFile = dlg->FileName;

							//get the CPU *Y* correction image
							dlg->Title = "Select CPU *Y* Correction FITS Image File";
							res = dlg->ShowDialog();
							if (res != ::DialogResult::OK)
								return;
							String^ CPUYDistFile = dlg->FileName;
						}
						CPUXDistFits = gcnew JPFITS::FITSImage(CPUXDistFile, nullptr, true, true, false, true);
						CPUYDistFits = gcnew JPFITS::FITSImage(CPUYDistFile, nullptr, true, true, false, true);
					}
					bool interpDISTBiLin = L1DigestApplyDISTInterpBiLinChck->Checked;

					int byteindx = 0;
					double bzero = 0;
					double bscale = 1;

					//first thing, get number of sets
					int Nset = 0;
					unsigned __int16 prevframe = UInt16::MaxValue;
					unsigned __int32 prevtime = UInt32::MaxValue;
					for (int i = 0; i < naxis2; i++)
					{
						//frame count - TTYPE11 = 'SecHdrImageFrameCount'
						byteindx = i * naxis1;
						byteindx += 65;
						bzero = 32768;
						unsigned __int16 currframe = int(((arr[byteindx]) << 8) | arr[byteindx + 1]) + (unsigned __int16)bzero;//MUST DO IT THIS WAY

						//frame time - TTYPE12 = 'SecHdrImageFrameTime'
						byteindx = i * naxis1;
						byteindx += 67;
						bzero = 2147483648;
						unsigned __int32 currtime = int(((arr[byteindx]) << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2]) << 8 | arr[byteindx + 3]) + (unsigned __int32)bzero;//MUST DO IT THIS WAY

						//if: then imaging session set has reset, or first set, or frame or time rolled over & start new set on rollover,
						//or erroneous (nonsequential) frame number greater than a CRC frame skip which are only skips of 1 frame (but using 2 here for the extremely rare adjacent-frame CRC skips)
						//- in this case the erroneous frame (which will to extremely high probability always be larger difference than 2) will get singled out as its own list for that single frame
						//and then not get written since it will be so small (single frame)
						if (prevframe > currframe || prevtime > currtime || (Math::Abs(double(currframe) - double(prevframe)) > 2))
							Nset++;

						prevframe = currframe;
						prevtime = currtime;
					}

					//have number of sets, now need number of centroids in each set
					array<int>^ Ncentroids = gcnew array<int>(Nset);
					array<int>^ Nskipped = gcnew array<int>(Nset);//skipped frame numbers...not even with 0's
					int Ncent = 0;
					Nset = 0;
					prevframe = UInt16::MaxValue;
					prevtime = UInt32::MaxValue;
					for (int i = 0; i < naxis2; i++)
					{
						//frame count - TTYPE11 = 'SecHdrImageFrameCount'
						byteindx = i * naxis1;
						byteindx += 65;
						bzero = 32768;
						unsigned __int16 currframe = int(((arr[byteindx]) << 8) | arr[byteindx + 1]) + (unsigned __int16)bzero;//MUST DO IT THIS WAY

						//frame time - TTYPE12 = 'SecHdrImageFrameTime'
						byteindx = i * naxis1;
						byteindx += 67;
						bzero = 2147483648;
						unsigned __int32 currtime = int(((arr[byteindx]) << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2]) << 8 | arr[byteindx + 3]) + (unsigned __int32)bzero;//MUST DO IT THIS WAY

						//if: then imaging session set has reset, or first set, or frame or time rolled over & start new set on rollover,
						//or erroneous (nonsequential) frame number greater than a CRC frame skip which are only skips of 1 frame (but using 2 here for the extremely rare adjacent-frame CRC skips)
						//- in this case the erroneous frame (which will to extremely high probability always be larger difference than 2) will get singled out as its own list for that single frame
						//and then not get written since it will be so small (single frame)
						if (prevframe > currframe || prevtime > currtime || (Math::Abs(double(currframe) - double(prevframe)) > 2))
							Nset++;

						if (Math::Abs(double(currframe) - double(prevframe) > 2))
						{
							prevframe = currframe;
							prevtime = currtime;
						}

						if (currframe - prevframe > 1)
							Nskipped[Nset - 1] += currframe - prevframe - 1;

						/*if (Nskipped[Nset - 1] > 1000)
							MessageBox::Show(Nskipped[Nset - 1] + "	" + currframe + "  " + prevframe);*/

						prevframe = currframe;
						prevtime = currtime;

						//Centroid - TTYPE15 = 'Centroid'
						byteindx = i * naxis1;
						byteindx += 79;
						int j = 0;
						bool checkwidth = false;
						scanwidth:;
						try
						{
							for (j; j < width / 6; j++)
							{
								unsigned __int16 xword = unsigned __int16((arr[byteindx + j * 6] << 8) | arr[byteindx + j * 6 + 1]);
								unsigned __int16 yword = unsigned __int16((arr[byteindx + j * 6 + 2] << 8) | arr[byteindx + j * 6 + 3]);
								unsigned __int16 sword = unsigned __int16((arr[byteindx + j * 6 + 4] << 8) | arr[byteindx + j * 6 + 5]);

								if (xword == 0 && yword == 0 && sword == 0)//end of data for this i'th row
									continue;//break;

								Ncent++;//number of centroids, only incremented if there was more data for this row
								Ncentroids[Nset - 1]++;
							}
						}
						catch (...)
						{
							checkwidth = true;
							width -= 6;
							goto scanwidth;
						}
						if (checkwidth)
						{
							//Ncent--;
							//Ncentroids[Nset - 1]--;
						}
					}

					array<double>^				BJDS;
					array<unsigned __int16>^	frames;
					array<unsigned __int32>^	times;
					array<__int16, 2>^			ints;
					array<__int16, 2>^			decs;
					array<unsigned __int16, 2>^	mdMm;

					Ncent = 0;
					Nset = 0;
					prevframe = UInt16::MaxValue;
					prevtime = UInt32::MaxValue;
					for (int i = 0; i <= naxis2; i++)
					{
						if (i == naxis2)
						{
							prevframe = UInt16::MaxValue;//will force the last set to be written
							prevtime = UInt32::MaxValue;
							goto lastset;
						}

						//frame count - TTYPE11 = 'SecHdrImageFrameCount'
						byteindx = i * naxis1;
						byteindx += 65;
						bzero = 32768;
						unsigned __int16 currframe = int(((arr[byteindx]) << 8) | arr[byteindx + 1]) + (unsigned __int16)bzero;//MUST DO IT THIS WAY

						//frame time - TTYPE12 = 'SecHdrImageFrameTime'
						byteindx = i * naxis1;
						byteindx += 67;
						bzero = 2147483648;
						unsigned __int32 currtime = int(((arr[byteindx]) << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2]) << 8 | arr[byteindx + 3]) + (unsigned __int32)bzero;//MUST DO IT THIS WAY

						double JD;

						/*//MJD_UT - TTYPE23 = 'MJD_UT'
						byteindx = i*naxis1;
						byteindx += 2251;
						bzero = 0;
						array<unsigned char>^ dbl = gcnew array<unsigned char>(8);
						dbl[7] = arr[byteindx];
						dbl[6] = arr[byteindx + 1];
						dbl[5] = arr[byteindx + 2];
						dbl[4] = arr[byteindx + 3];
						dbl[3] = arr[byteindx + 4];
						dbl[2] = arr[byteindx + 5];
						dbl[1] = arr[byteindx + 6];
						dbl[0] = arr[byteindx + 7];
						double JD = BitConverter::ToDouble(dbl, 0) / 86400 + 2455197.5;*/

						//TIME //supposedly mission elapsed time, or something, but perhaps can use with lbt file for aligning filter
						byteindx = i * naxis1;
						byteindx += 0;
						bzero = 0;
						array<unsigned char>^ dbl = gcnew array<unsigned char>(8);
						dbl[7] = arr[byteindx];
						dbl[6] = arr[byteindx + 1];
						dbl[5] = arr[byteindx + 2];
						dbl[4] = arr[byteindx + 3];
						dbl[3] = arr[byteindx + 4];
						dbl[2] = arr[byteindx + 5];
						dbl[1] = arr[byteindx + 6];
						dbl[0] = arr[byteindx + 7];
						double temptime = BitConverter::ToDouble(dbl, 0);
						if (temptime > lasttime_mjd_forfilter)
							lasttime_mjd_forfilter = temptime;
						if (temptime < firsttime_mjd_forfilter)
							firsttime_mjd_forfilter = temptime;
						//double JD = BitConverter::ToDouble(dbl, 0);
						//the above time isn't exact.  Now use the JD_abs_time_delta_sec to get the BJD here

						if (tctfileexists)
							JD = (double(currtime) / 1000 + JD_abs_time_delta_sec) / 86400;//this should be the local JD...it will get used below to get BJD
						else
							JD = 0;

					lastset:

						//if: then imaging session set has reset, or first set, or frame or time rolled over & start new set on rollover,
						//or erroneous (nonsequential) frame number greater than a CRC frame skip which are only skips of 1 frame (but using 2 here for the extremely rare adjacent-frame CRC skips)
						//- in this case the erroneous frame (which will to extremely high probability always be larger difference than 2) will get singled out as its own list for that single frame
						//and then not get written since it will be so small (single frame)
						if (prevframe > currframe || prevtime > currtime || (Math::Abs(double(currframe) - double(prevframe)) > 2))
						{
							if (Nset > 0 || i == naxis2)//then the previous set data needs to be written
							{
								if (times != nullptr)
									if (times->Length > /*0*/1000)//so that short corrupt files dont get written
										if (discardtimebool && (times[times->Length - 1] - times[0]) > discardtimeint || !discardtimebool)
										{
											//do filter correction........do this first for the next below
											if (dofiltercorrection)
											{
												double midtime = (lasttime_mjd_forfilter + firsttime_mjd_forfilter) / 2;
												int lbtcounter = 0;
												while (/*midtime*/ firsttime_mjd_forfilter > lbt_times[lbtcounter])//midtime still wouldn't align when the time-filter alignment was off...first time seems to work better than the last time
													lbtcounter++;
												double fwangle;
												if (source->GetKeyValue("DETECTOR") == "FUV")
													fwangle = lbt_FUVfwangle[lbtcounter];
												if (source->GetKeyValue("DETECTOR") == "NUV")
													fwangle = lbt_NUVfwangle[lbtcounter];
												String^ filterindex = UVITFilter_FWAngle_to_Index(source->GetKeyValue("DETECTOR"), fwangle);

												/*if (L1TBCChck->Checked && filterindex == "F0" || L1TBCChck->Checked && filterindex == "NA")
												{
													lbtcounter = 0;
													firsttime_mjd_forfilter -= 524;
													while (firsttime_mjd_forfilter > lbt_times[lbtcounter])
														lbtcounter++;
													fwangle = lbt_VISfwangle[lbtcounter];
													filterindex = UVITFilter_FWAngle_to_Index(source->GetKeyValue("DETECTOR"), fwangle);
												}*/

												String^ filter = source->GetKeyValue("FILTER");
												if (filterindex != filter)
													source->SetKey("FILTER", filterindex, "Filter index (CORRECTED)", false, -1);
												String^ filtertype = UVITFilter(source->GetKeyValue("DETECTOR"), filterindex);
												source->SetKey("FILTERID", filtertype, "Filter type", true, source->GetKeyIndex("FILTER") + 1);
												lasttime_mjd_forfilter = Double::MinValue;
												firsttime_mjd_forfilter = Double::MaxValue;
											}

											dir = path + "\\" + source->GetKeyValue("DETECTOR") + "\\" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "\\" + (source->GetKeyValue("SOURCEID")->Replace(" ", ""))->Replace("/", "") + "_" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "_" + source->GetKeyValue("ORB_NUM") + "_" + (times[0]).ToString("0000000000000");
											::Directory::CreateDirectory(dir);
											String^ obj_orb_chan;
											obj_orb_chan = dir + "\\" + (source->GetKeyValue("SOURCEID")->Replace(" ",""))->Replace("/", "") + "_" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "_" + source->GetKeyValue("ORB_NUM") + "_" + (times[0]).ToString("0000000000000");
											dir_list->Add(dir);
											e->Result = dir_list;

											String^ BJDfile = obj_orb_chan + "_BJDList.fits";
											if (tctfileexists)//else all 0's
												BJDS = BJDC(BJDS, Convert::ToDouble(source->GetKeyValue("RA_PNT")), Convert::ToDouble(source->GetKeyValue("DEC_PNT")), false);

											if (channel == "NUV" && L1TransformNUVtoFUVChck->Checked)
												source->SetKey("NUVTOFUV", "true", true, -1);
											source->SetKey("SRCFILE", "File Name", source->FileName->Substring(6), true, 12);
											source->SetKey("BJD0", BJDS[0].ToString("#.0000000"), "BJD of start of imaging", true, 13);//now it will get added to all other copyheaders's
											source->SetKey("NPARTERR", N_p_errors.ToString(), "Number of Parity errors", true, 14);
											source->SetKey("NCENTROD", times->Length.ToString(), "Number of Centroids", true, 14);
											source->SetKey("PARTREDC", Math::Round(double(N_p_errors) / double(times->Length), 5).ToString(), "Fractional int-time reduxn due to parity err", true, 14);
											source->SetKey("NMISSFRM", Nskipped[Nset - 1].ToString(), "Number of MISSING frames", true, 14);
											source->RemoveKey("NFRAMES");
											source->SetKey("NFRAMES", (frames[frames->Length - 1] - frames[0] + 1).ToString(), "Number of frames, including missing ones", true, 14);
											source->SetKey("FRAMREDC", Math::Round(double(Nskipped[Nset - 1]) / double(frames[frames->Length - 1] - frames[0] + 1), 5).ToString(), "Fractional int-time reduxn due to lost frames", true, 14);
											N_p_errors = 0;//reset for new set
											JPFITS::FITSImage^ f = gcnew FITSImage(BJDfile, BJDS, false, true);
											f->CopyHeader(source);
											f->WriteImage(::TypeCode::Double, true);

											String^ framefile = obj_orb_chan + "_FrameList.fits";
											f = gcnew FITSImage(framefile, frames, false, true);
											f->CopyHeader(source);
											f->WriteImage(::TypeCode::UInt16, true);

											String^ timefile = obj_orb_chan + "_TimeList.fits";
											f = gcnew FITSImage(timefile, times, false, true);
											f->CopyHeader(source);
											f->WriteImage(::TypeCode::UInt32, true);

											String^ flatid;
											FITSImage^ flat;
											String^ channel = f->GetKeyValue("CHANNEL");
											if (channel->Length == 0)
												channel = f->GetKeyValue("DETECTOR");
											if (channel == "FUV")
											{
												//flatid = "C:\\UVIT_CalDB\\Flats Normalized\\FUV Normalized Flat.fits";

												flatid = "C:\\UVIT_CalDB\\Flats Normalized\\FUVALL_flat_final_sens.fits";
											}
											if (channel == "NUV")
											{
												//flatid = "C:\\UVIT_CalDB\\Flats Normalized\\NUV Normalized Flat.fits";

												String^ filterid = source->GetKeyValue("FILTERID");
												if (filterid->Contains("Silica"))
													flatid = "N242W_flat_final_sens.fits";
												if (filterid == "NUVB15")
													flatid = "N219M_flat_final_sens.fits";
												if (filterid == "NUVB13")
													flatid = "N245M_flat_final_sens.fits";
												if (filterid == "NUVB4")
													flatid = "N263M_flat_final_sens.fits";
												if (filterid == "NUVN2")
													flatid = "N279N_flat_final_sens.fits";
												flatid = "C:\\UVIT_CalDB\\Flats Normalized\\" + flatid;
											}
											if (channel == "VIS")
												flatid = "C:\\UVIT_CalDB\\Flats Normalized\\VIS Normalized Flat.fits";
											if (!File::Exists(flatid))
											{
												::MessageBox::Show("Couldn't find the flat file: '" + flatid + "' in the CalDB...stopping.", "Error");
												WAITBAR->CancelBtn->PerformClick();
												return;
											}
											else
												flat = gcnew FITSImage(flatid, nullptr, true, true, false, true);

											array<double>^ flats = gcnew array<double>(Ncentroids[Nset - 1]);
											int j = 0;
											try
											{
												#pragma omp parallel for
												for (j = 0; j < Ncentroids[Nset - 1]; j++)
												{
													int xpos = int(ints[0, j] / 32);
													int ypos = int(ints[1, j] / 32);
													if (xpos < 0 || xpos > 511 || ypos < 0 || ypos > 511)
														flats[j] = 1;
													else
														flats[j] = flat[xpos, ypos];
												}

												//do NUV to FUV here, after the flat is created...simple!
												if (channel == "NUV" && L1TransformNUVtoFUVChck->Checked)
												{
													::Random^ r = gcnew Random();
													double x, y, xp, yp, center = 255 * 32;
													int intsx, fracx, intsy, fracy;
													array<double>^ Pnuvtofuv = gcnew array<double>(4) { 0.84898, 0.53007, 0.53007, -0.84898 };//from Shyam Feb 2017
													for (j = 0; j < Ncentroids[Nset - 1]; j++)
													{
														x = double(ints[0, j] + decs[0, j] + 16) + r->NextDouble();
														y = double(ints[1, j] + decs[1, j] + 16) + r->NextDouble();

														xp = (x - center) * Pnuvtofuv[0] + (y - center) * Pnuvtofuv[1] + center;
														yp = (x - center) * Pnuvtofuv[2] + (y - center) * Pnuvtofuv[3] + center;

														//now need to split out integer and decimal parts back into their own lists...
														intsx = Math::DivRem(int((xp)), 32, fracx) * 32;
														fracx -= 16;//reset frac to be from -16
														intsy = Math::DivRem(int((yp)), 32, fracy) * 32;
														fracy -= 16;//reset frac to be from -16
														ints[0, j] = intsx;
														ints[1, j] = intsy;
														decs[0, j] = fracx;
														decs[1, j] = fracy;
													}
												}
											}
											catch (...)
											{
												::MessageBox::Show("xint: " + (int(ints[0, j] / 32)).ToString() + ";	yint: " + (int(ints[1, j] / 32)).ToString() + ";	j: " + j.ToString() + ";	lengthj: " + flats->Length.ToString());
											}
											String^ flatfile = obj_orb_chan + "_FlatList.fits";
											FITSImage^ fitsflatlist = gcnew FITSImage(flatfile, flats, false, true);
											fitsflatlist->CopyHeader(source);
											fitsflatlist->WriteImage(::TypeCode::Double, true);

											String^ intsfile = obj_orb_chan + "_XYInts_List.fits";
											if (ApplyFPN)
												intsfile = intsfile->Insert(intsfile->LastIndexOf("."), "_deFPN");
											if (ApplyDIST)
												intsfile = intsfile->Insert(intsfile->LastIndexOf("."), "_deDIST");
											f = gcnew FITSImage(intsfile, ints, false, true);
											f->CopyHeader(source);
											f->WriteImage(::TypeCode::Int16, true);

											String^ fracfile = obj_orb_chan + "_XYFrac_List.fits";
											if (ApplyFPN)
												fracfile = fracfile->Insert(fracfile->LastIndexOf("."), "_deFPN");
											if (ApplyDIST)
												fracfile = fracfile->Insert(fracfile->LastIndexOf("."), "_deDIST");
											f = gcnew FITSImage(fracfile, decs, false, true);
											f->CopyHeader(source);
											f->WriteImage(::TypeCode::Int16, true);

											String^ mdMmfile = obj_orb_chan + "_XYmdMm_List.fits";
											f = gcnew FITSImage(mdMmfile, mdMm, false, true);
											f->CopyHeader(source);
											f->WriteImage(::TypeCode::Int16, true);
										}
							}

							if (i == naxis2)
								goto lastset2;//last set was written so now go end

							//reset everything for new centroids list
							Nset++;
							Ncent = 0;
							BJDS = gcnew array<double>(Ncentroids[Nset - 1]);
							frames = gcnew array<unsigned __int16>(Ncentroids[Nset - 1]);
							times = gcnew array<unsigned __int32>(Ncentroids[Nset - 1]);
							ints = gcnew array<__int16, 2>(2, Ncentroids[Nset - 1]);
							decs = gcnew array<__int16, 2>(2, Ncentroids[Nset - 1]);
							mdMm = gcnew array<unsigned __int16, 2>(2, Ncentroids[Nset - 1]);
						}
						prevframe = currframe;
						prevtime = currtime;

						//Centroid - TTYPE15 = 'Centroid'
						byteindx = i * naxis1;
						byteindx += 79;
						for (int j = 0; j < width / 6; j++)
						{
							unsigned __int16 xword = unsigned __int16((arr[byteindx + j * 6] << 8) | arr[byteindx + j * 6 + 1]);
							unsigned __int16 yword = unsigned __int16((arr[byteindx + j * 6 + 2] << 8) | arr[byteindx + j * 6 + 3]);
							unsigned __int16 sword = unsigned __int16((arr[byteindx + j * 6 + 4] << 8) | arr[byteindx + j * 6 + 5]);

							if (xword == 0 && yword == 0 && sword == 0)//end of data for this i'th row
								continue;//break;

							if (discardparityerror)
							{
								xword_parity_error = CCDLAB::GSEExtractImg::Check_Even_Parity_Flag(xword);
								yword_parity_error = CCDLAB::GSEExtractImg::Check_Even_Parity_Flag(yword);
								sword_parity_error = CCDLAB::GSEExtractImg::Check_Even_Parity_Flag(sword);
							}

							bool p_error = false;
							if (xword_parity_error || yword_parity_error/* || sword_parity_error*/)//lets not worry about a parity error only on the sword because this doesn't affect the centroid photometry position itself, and it can still be used.  If it is a parity error on the x or y, then it does need to be accounted for.
							{
								p_error = true;
								N_p_errors++;
							}

							unsigned __int16 ixpos, iypos, mc, dMm;
							__int16	fxpos, fypos;

							if (!p_error)
							{
								//x
								ixpos = ((xword) >> 7) * 32;
								fxpos = ((xword & 0x7F) >> 1);
								if (fxpos >= 32)
									fxpos = fxpos - 64;

								//y
								iypos = ((yword) >> 7) * 32;
								fypos = ((yword & 0x7F) >> 1);
								if (fypos >= 32)
									fypos = fypos - 64;

								//corner
								mc = ((sword & 0x1FF) >> 1) * 16;
								dMm = (sword >> 9) * 16;

								if (ApplyFPN)
								{
									if (fxpos < -16)//X
									{
										ixpos -= 32;//adjust integer
										fxpos += 32;//adjust fractional
									}
									if (fypos < -16)//Y
									{
										iypos -= 32;//adjust integer
										fypos += 32;//adjust fractional
									}
									if (fxpos > 15)//X
									{
										ixpos += 32;//adjust integer
										fxpos -= 32;//adjust fractional
									}
									if (fypos > 15)//Y
									{
										iypos += 32;//adjust integer
										fypos -= 32;//adjust fractional
									}

									fxpos += 16;
									fypos += 16;

									double fx = double(fxpos);
									double fy = double(fypos);

									fx += rand->NextDouble();
									fy += rand->NextDouble();

									fx *= FPNFits[1, int(fx * 4096 / 32)];
									fy *= FPNFits[2, int(fy * 4096 / 32)];

									fxpos = (__int16)fx;
									fypos = (__int16)fy;

									fxpos -= 16;//x
									fypos -= 16;//y
								}

								int xcorr, ycorr;
								if (ApplyDIST)
								{
									if (ixpos > 0 && iypos > 0 && ixpos / 32 <= 511 && iypos / 32 <= 511)
									{
										if (interpDISTBiLin)
										{
											double x = (double(ixpos) + double(fxpos) + 16) / 32;
											double y = (double(iypos) + double(fypos) + 16) / 32;
											xcorr = int(32 * JPMath::InterpolateBiLinear(CPUXDistFits->Image, 512, 512, x, y));
											ycorr = int(32 * JPMath::InterpolateBiLinear(CPUYDistFits->Image, 512, 512, x, y));
										}
										else
										{
											xcorr = int(32 * CPUXDistFits[ixpos / 32, iypos / 32]);
											ycorr = int(32 * CPUYDistFits[ixpos / 32, iypos / 32]);
										}										

										ixpos -= xcorr;
										iypos -= ycorr;
									}
									else
										p_error = true;//treat this as p_error...it is an odd scenario but now seen to happen with Ashok Pati's data.							
								}
							}

							BJDS[Ncent] = JD;
							frames[Ncent] = currframe;
							times[Ncent] = currtime;

							if (p_error)
							{
								//::MessageBox::Show("p_error");
								ints[0, Ncent] = 0;//these will be seen in a final image as drifting around at the top left corner
								ints[1, Ncent] = 0;
								decs[0, Ncent] = 0;
								decs[1, Ncent] = 0;
								mdMm[0, Ncent] = 0;
								mdMm[1, Ncent] = 0;
							}
							else
							{
								ints[0, Ncent] = ixpos;
								ints[1, Ncent] = iypos;
								decs[0, Ncent] = fxpos;
								decs[1, Ncent] = fypos;
								mdMm[0, Ncent] = mc;
								mdMm[1, Ncent] = dMm;
							}
							Ncent++;//number of centroids, only incremented if there was more data for this row
						}
					}
				lastset2:;
				}
				catch (Exception^ e)
				{
					MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite + "\n\r + \n\r" + "File: " + argfiles[errorfileindex]);
				}
			}//end if PC mode




			if (mode == "IM")
			{
				if (L1SkipINTMode->Checked)
				{
					bs->Close();
					fs->Close();
					goto skipto;
				}

				bool degrade = L1DegradientINTMode->Checked;
				double cleanthreshold = Convert::ToDouble(L1CleanINTLineThreshold->Text);
				int cleanN = Convert::ToInt32(L1CleanINTNPix->Text);

				int byteindx = 0;
				double bzero = 0;
				double bscale = 1;

				int xsize  = ::Convert::ToInt32(source->GetKeyValue("WIN_X_SZ"));//zero-based
				int ysize  = ::Convert::ToInt32(source->GetKeyValue("WIN_Y_SZ"));//zero-based
				int imsize = (xsize+1)*(ysize+1);
				array<double,2>^ d2im = gcnew array<double,2>(xsize+1,ysize+1);
				array<unsigned __int16>^ d1im = gcnew array<unsigned __int16>(imsize);//just 1-D is fine cause we're just gonna write it
				int pixnum = 0;
				int intprog = 0;
				int Nimages = width*naxis2/imsize;
				unsigned __int16 prevframe = UInt16::MaxValue - 1;
				int set = 0;
				array<unsigned char>^ arr = gcnew array<unsigned char>(naxis1 * naxis2);
				bs->Read(arr, 0, naxis1 * naxis2);
				bs->Close();
				fs->Close();

				lasttime_mjd_forfilter = Double::MinValue;
				firsttime_mjd_forfilter = Double::MaxValue;

				if (DO_TBC)
					TBC(arr, naxis1, naxis2);

				try
				{
					for (int i = 0; i < naxis2; i++)
					{
						//frame count
						byteindx = i * naxis1;
						byteindx += 65;
						bzero = 32768;
						unsigned __int16 frame = int(((arr[byteindx]) << 8) | arr[byteindx + 1]) + (unsigned __int16)bzero;

						//frame time
						byteindx = i * naxis1;
						byteindx += 67;
						bzero = 2147483648;
						bscale = 1;
						unsigned __int32 time = int(((arr[byteindx]) << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2]) << 8 | arr[byteindx + 3]) + (unsigned __int32)bzero;

						//TIME //supposedly mission elapsed time, or something, but perhaps can use with lbt file for aligning filter
						byteindx = i * naxis1;
						byteindx += 0;
						bzero = 0;
						array<unsigned char>^ dbl = gcnew array<unsigned char>(8);
						dbl[7] = arr[byteindx];
						dbl[6] = arr[byteindx + 1];
						dbl[5] = arr[byteindx + 2];
						dbl[4] = arr[byteindx + 3];
						dbl[3] = arr[byteindx + 4];
						dbl[2] = arr[byteindx + 5];
						dbl[1] = arr[byteindx + 6];
						dbl[0] = arr[byteindx + 7];
						double temptime = BitConverter::ToDouble(dbl, 0);
						if (temptime > lasttime_mjd_forfilter)
							lasttime_mjd_forfilter = temptime;
						if (temptime < firsttime_mjd_forfilter)
							firsttime_mjd_forfilter = temptime;

						if (prevframe != frame)//then it is a new image; also fires at very beginning.
						{
							if (prevframe > frame && prevframe != UInt16::MaxValue || ((int)frame - (int)prevframe) > 5 * 16)//then frame has reset for some reason, so start a new file name set; also fires at very beginning
							{
								if (dofiltercorrection)
								{
									double midtime = (lasttime_mjd_forfilter + firsttime_mjd_forfilter) / 2;
									int lbtcounter = 0;
									//MessageBox::Show(firsttime_mjd_forfilter + "    " + lbt_times[0] + "    " + lbt_times[lbt_times->Length - 1]);
									while (/*midtime*/ lbtcounter < lbt_times->Length && firsttime_mjd_forfilter > lbt_times[lbtcounter])//midtime still wouldn't align when the time-filter alignment was off...first time seems to work better than the last time
										lbtcounter++;
									if (lbtcounter == lbt_times->Length)
										lbtcounter /= 2;//?????
									double fwangle = lbt_VISfwangle[lbtcounter];
									String^ filterindex = UVITFilter_FWAngle_to_Index(source->GetKeyValue("DETECTOR"), fwangle);

									if (DO_TBC && filterindex == "F0" || DO_TBC && filterindex == "NA")
									{
										lbtcounter = 0;
										firsttime_mjd_forfilter -= 524;
										while (lbtcounter < lbt_times->Length && firsttime_mjd_forfilter > lbt_times[lbtcounter])
											lbtcounter++;
										if (lbtcounter == lbt_times->Length)
											lbtcounter /= 2;//?????
										fwangle = lbt_VISfwangle[lbtcounter];
										filterindex = UVITFilter_FWAngle_to_Index(source->GetKeyValue("DETECTOR"), fwangle);
									}

									String^ filter = source->GetKeyValue("FILTER");
									if (filterindex != filter)
										source->SetKey("FILTER", filterindex, "Filter index (CORRECTED)", false, -1);
									String^ filtertype = UVITFilter(source->GetKeyValue("DETECTOR"), filterindex);
									source->SetKey("FILTERID", filtertype, "Filter type", true, source->GetKeyIndex("FILTER") + 1);
									lasttime_mjd_forfilter = Double::MinValue;
									firsttime_mjd_forfilter = Double::MaxValue;
								}

								set++;//used in file name of image
								if (source->GetKeyValue("DETECTOR") == "VIS")
									dir = path + "\\" + "VIS" + "\\" + (source->GetKeyValue("SOURCEID")->Replace(" ", ""))->Replace("/", "") + "_" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "_" + source->GetKeyValue("ORB_NUM") + "_" + (time).ToString("0000000000000");
								else
									dir = path + "\\" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "\\" + (source->GetKeyValue("SOURCEID")->Replace(" ", ""))->Replace("/", "") + "_" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "_" + source->GetKeyValue("ORB_NUM") + "_" + (time).ToString("0000000000000");
								::Directory::CreateDirectory(dir);
							}
							pixnum = 0;//force restart
							prevframe = frame;
						}

						try
						{
							//Pixel
							byteindx = i * naxis1;
							byteindx += 79;
							bzero = 32768;
							for (int j = 0; j < width; j++)
							{
								if (pixnum >= imsize)//image is done
								{
									if (WAITBAR->DialogResult == ::DialogResult::Cancel)
										return;
									intprog++;
									DigestL1Wrkr->ReportProgress(100 * intprog / Nimages, mode + "_" + (xi + 1).ToString() + "_" + argfiles->Length);

									pixnum = 0;//reset pixel index

									#pragma omp parallel for
									for (int jj = 0; jj < ysize + 1; jj++)
										for (int ii = 0; ii < xsize + 1; ii++)
											d2im[ii, jj] = (double)(d1im[jj*(xsize + 1) + ii]);

									String^ obj_orb_chan;
									obj_orb_chan = dir + "\\" + (source->GetKeyValue("SOURCEID")->Replace(" ", ""))->Replace("/", "") + "_" + source->GetKeyValue("DETECTOR") + "_" + UVITFilter(source->GetKeyValue("DETECTOR"), source->GetKeyValue("FILTER")) + "_" + source->GetKeyValue("ORB_NUM") + "_" + (time).ToString("0000000000000") + ".fits";
									if (degrade)
										d2im = JPMath::DeGradient(d2im, 0, true);
									FITSImage^ fits = gcnew FITSImage(obj_orb_chan, d2im, false, true);
									source->SetKey("SRCFILE", "File Name", source->FileName->Substring(6), true, 12);
									fits->CopyHeader(source);
									fits->AddKey("FRMTIME", (double(time) / 1000).ToString(), "EU Frame Time (s)", 18);
									fits->AddKey("FRAMENO", frame.ToString(), "Frame Number", 18);
									fits->AddKey("FRAMESET", set.ToString(), "Frame Set", 18);
									array<double>^ JD = gcnew array<double>(1) { (double(time) / 1000 + JD_abs_time_delta_sec) / 86400 };
									JD = BJDC(JD, Convert::ToDouble(source->GetKeyValue("RA_PNT")), Convert::ToDouble(source->GetKeyValue("DEC_PNT")), false);
									fits->AddKey("FRAMEBJD", JD[0].ToString(), "Heliocentric Julian Date (days)", 18);
									if (frame > 16)//skip writing first image so that noise images don't come in
									{
										if (L1CleanINTMode->Checked)
											CLEAN_UVITVISIMG(fits, cleanthreshold, cleanN);

										SPAREFITSImageSet->Add(fits);
									}
									d2im = gcnew array<double, 2>(xsize + 1, ysize + 1);
									d1im = gcnew array<unsigned __int16>(imsize);
									break;
								}

								d1im[pixnum] = ((arr[byteindx + j * 2] << 8) | arr[byteindx + j * 2 + 1]) + 32768;
								pixnum++;
							}
						}
						catch (...) {}
					}
				}
				catch (Exception^ e)
				{
					MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
				}
				
				WAITBAR->Tag = path + "\\" + "VIS";//need to sneak in the VIS directory for when no PC files were digested

				if (SPAREFITSImageSet->Count > 0)
				{
					SPAREFITSImageSet->Write(::TypeCode::Int32, true, true, "");
					SPAREFITSImageSet->Clear();
					SPAREFITSImageSet = gcnew FITSImageSet();
				}
			}//end if IM mode

			skipto:;

			if (!L1DigestDeleteFileChck->Checked)
			{
				if (!::Directory::Exists(source->FilePath + "Digested L1\\"))
					::Directory::CreateDirectory(source->FilePath + "Digested L1\\");
				::File::Move(source->FullFileName, source->FilePath + "Digested L1\\" + source->FileName);
			}
			else
				File::Delete(source->FullFileName);

		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite + "\n\r" + "File: " + argfiles[errorfileindex]);
	}
}

void Form1::DigestL1Wrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	String^ mode = (String^)e->UserState;
	if (mode->Substring(0,2) == "PC")
	{
		int first = mode->IndexOf("_");
		WAITBAR->ProgressBar->Maximum = ::Convert::ToInt32(mode->Substring(first+1));
		WAITBAR->Text = "Digesting L1 PC File(s)...";
		WAITBAR->ProgressBar->Value = e->ProgressPercentage;
		WAITBAR->TextMsg->Text = String::Concat("Digesting file: ",e->ProgressPercentage," of ",WAITBAR->ProgressBar->Maximum);
	}
	if (mode->Substring(0,2) == "IM")
	{
		int first = mode->IndexOf("_");
		int last = mode->LastIndexOf("_");
		WAITBAR->Text = "Digesting L1 Files: " + mode->Substring(first+1,last-first-1) + " of " + mode->Substring(last+1);
		WAITBAR->ProgressBar->Maximum = 100;
		WAITBAR->ProgressBar->Value = e->ProgressPercentage;
		WAITBAR->TextMsg->Text = String::Concat("Extracting INT-mode frames: ",e->ProgressPercentage,"%");
	}
	WAITBAR->Refresh();
}

void Form1::DigestL1Wrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		Form1::Enabled = true;
		Form1::BringToFront();
		return;
	}

	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");//may be top-level only of multidirs
	SetReg("CCDLAB", "OpenFilesPath", dir);
	bool multidir = Convert::ToBoolean(GetReg("CCDLAB", "L1ExtractMultiDir"));//if true then dir is multi-level
	array<String^>^ multidirs;
	if (multidir)
		multidirs = Directory::GetDirectories(dir);
	else
		multidirs = gcnew array<String^>(1) { dir };//since dir will be the object session directory done by itself

	//move tct and lbt files
	for (int i = 0; i < TCTFILELIST->Count; i++)
	{
		String^ tctfile = (String^)TCTFILELIST[i];
		if (!File::Exists(tctfile))
			continue;
		if (!L1DigestDeleteFileChck->Checked)
		{
			String^ dir = tctfile->Substring(0, tctfile->LastIndexOf("\\"));
			dir = dir + "\\Digested L1\\";
			File::Move(tctfile, dir + tctfile->Substring(tctfile->LastIndexOf("\\")));
		}
		else
			File::Delete(tctfile);
	}
	for (int i = 0; i < LBTFILELIST->Count; i++)
	{
		String^ lbtfile = (String^)LBTFILELIST[i];
		if (!File::Exists(lbtfile))
			continue;
		if (!L1DigestDeleteFileChck->Checked)
		{
			String^ dir = lbtfile->Substring(0, lbtfile->LastIndexOf("\\"));
			dir = dir + "\\Digested L1\\";
			File::Move(lbtfile, dir + lbtfile->Substring(lbtfile->LastIndexOf("\\")));
		}
		else
			File::Delete(lbtfile);
	}

	if (L1DiscardDuplicateChck->Checked)
	{
		WAITBAR->Text = "Searching for duplicated data...";
		if (e->Result != nullptr)//result = nullptr if only IM done.  Here, VIS directories will be checked for duplicates
		{
			ArrayList^ dir_list = (ArrayList^)e->Result;
			WAITBAR->ProgressBar->Maximum = dir_list->Count - 1;
			DiscardL1DuplicateWrkr->RunWorkerAsync(dir_list);
			//WAITBAR->ShowDialog(); already shown
			return;
		}
		else//then only IM done.  Need to scan the VIS images and dirs for duplicates
		{
			DiscardL1DuplicateWrkr->RunWorkerAsync();
			//WAITBAR->ShowDialog(); already shown...and has VIS dir tag
			return;
		}
	}
	else
		if (L1AutoRunChck->Checked)
			DiscardL1DuplicateWrkr_RunWorkerCompleted(sender, e);

	//finish
	TimeSpan ts = DateTime::Now - DATE;
	::MessageBox::Show("Completed digesting L1 data in " + ts.Minutes.ToString() + "m" + ts.Seconds.ToString() + "s.","Finished...");
	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::BringToFront();	
}

void Form1::autoRunToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
{
	SetReg("CCDLAB", "L1AutoRunChck", L1AutoRunChck->Checked);
	if (L1AutoRunChck->Checked)
		L1AutoProceedVISBackGround->Enabled = true;
	else
	{
		L1AutoProceedVISBackGround->Enabled = false;
		L1AutoProceedVISTracking->Enabled = false;
		L1AutoProceedVISBackGround->Checked = false;
		L1AutoProceedVISTracking->Checked = false;
		L1AutoApplyVISDrift->Enabled = false;
		L1AutoApplyVISDrift->Checked = false;
	}
	SetReg("CCDLAB", "L1AutoProceedVISBackGround", L1AutoProceedVISBackGround->Checked);
	SetReg("CCDLAB", "L1AutoProceedVISTracking", L1AutoProceedVISTracking->Checked);
	SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift->Checked);

	UVITMenu->ShowDropDown();
	ExtractL1gzsMenuItem->ShowDropDown();
}

void Form1::L1AutoProceedVISBackGround_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "L1AutoProceedVISBackGround", L1AutoProceedVISBackGround->Checked);
	if (L1AutoProceedVISBackGround->Checked)
		L1AutoProceedVISTracking->Enabled = true;
	else
	{
		L1AutoProceedVISTracking->Enabled = false;
		L1AutoProceedVISTracking->Checked = false;
		L1AutoApplyVISDrift->Enabled = false;
		L1AutoApplyVISDrift->Checked = false;
	}
	SetReg("CCDLAB", "L1AutoProceedVISTracking", L1AutoProceedVISTracking->Checked);
	SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift->Checked);

	UVITMenu->ShowDropDown();
	ExtractL1gzsMenuItem->ShowDropDown();
}

void Form1::L1AutoProceedVISTracking_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "L1AutoProceedVISTracking", L1AutoProceedVISTracking->Checked);
	if (L1AutoProceedVISTracking->Checked)
		L1AutoApplyVISDrift->Enabled = true;
	else
	{
		L1AutoApplyVISDrift->Enabled = false;
		L1AutoApplyVISDrift->Checked = false;
	}
	SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift->Checked);

	UVITMenu->ShowDropDown();
	ExtractL1gzsMenuItem->ShowDropDown();
}

void Form1::L1AutoApplyVISDrift_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "L1AutoApplyVISDrift", L1AutoApplyVISDrift->Checked);

	UVITMenu->ShowDropDown();
	ExtractL1gzsMenuItem->ShowDropDown();
}

void Form1::DiscardL1DuplicateWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{	
	//how to handle multiple top level dirs...
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	bool multidir = Convert::ToBoolean(GetReg("CCDLAB", "L1ExtractMultiDir"));//if true then dir is multi-level
	array<String^>^ multidirs;
	if (multidir)
		multidirs = Directory::GetDirectories(dir);
	else
		multidirs = gcnew array<String^>(1) { dir };//since dir will be the object session directory done by itself
	
	for (int dirindex = 0; dirindex < multidirs->Length; dirindex++)
	{
		if (e->Argument != nullptr)//will = nullptr if there were no pc files..but if we're in here there must be VIS INT files then
		{
			ArrayList^ delete_dir_list = gcnew ArrayList();
			FITSImage^ fitsi;
			array<double>^ fitsistart;
			array<double>^ fitsiend;
			FITSImage^ fitsj;
			array<double>^ fitsjstart;
			array<double>^ fitsjend;

			array<String^>^ timelists = Directory::GetFiles(multidirs[dirindex], "*TimeList*", IO::SearchOption::AllDirectories);

			for (int i = 0; i < timelists->Length - 1; i++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				DiscardL1DuplicateWrkr->ReportProgress(i + 1, gcnew array<Object^>(4) { delete_dir_list->Count, timelists->Length, multidirs->Length, dirindex + 1});

				String^ filei = timelists[i];
				String^ diri = filei->Substring(0, filei->LastIndexOf("\\"));
				String^ diritime = diri->Substring(diri->Length - 13);
				fitsi = gcnew FITSImage(filei, nullptr, true, false, false, false);
				String^ detectori = fitsi->GetKeyValue("DETECTOR");
				String^ filteri = fitsi->GetKeyValue("FILTER");
				fitsistart = JPFITS::FITSImage::ReadImageVectorOnly(filei, gcnew array<int>(4) { 0, 0, 0, 0 }, true);
				fitsiend = JPFITS::FITSImage::ReadImageVectorOnly(filei, gcnew array<int>(4) { 0, 0, fitsi->Height - 1, fitsi->Height - 1 }, true);

				for (int j = i + 1; j < timelists->Length; j++)
				{
					String^ filej = timelists[j];
					String^ dirj = filej->Substring(0, filej->LastIndexOf("\\"));
					String^ dirjtime = dirj->Substring(dirj->Length - 13);
					fitsj = gcnew FITSImage(filej, nullptr, true, false, false, false);
					String^ detectorj = fitsj->GetKeyValue("DETECTOR");
					String^ filterj = fitsj->GetKeyValue("FILTER");

					if (detectori != detectorj || filteri != filterj)
						continue;

					if (diritime == dirjtime)
						//definitely duplicated data, delete the directory with smaller files...they start at the exact same time so delete the smaller one
						//or if they're the same size, then delete earlier one
					{
						::FileStream^ fs = gcnew FileStream(filei, ::IO::FileMode::Open);
						__int64 fli = fs->Length;
						fs->Close();
						fs = gcnew FileStream(filej, ::IO::FileMode::Open);
						__int64 flj = fs->Length;
						fs->Close();

						if (flj < fli)
						{
							if (!delete_dir_list->Contains(dirj))
								delete_dir_list->Add(dirj);//delete the directory with smaller files
						}
						else
						{
							if (!delete_dir_list->Contains(diri))
								delete_dir_list->Add(diri);//delete the earlier directory
						}
						continue;
					}

					//check if times are overlapping - directory times are not the same, but there may be overlapping data within
					fitsjstart = JPFITS::FITSImage::ReadImageVectorOnly(filej, gcnew array<int>(4) { 0, 0, 0, 0 }, true);
					fitsjend = JPFITS::FITSImage::ReadImageVectorOnly(filej, gcnew array<int>(4) { 0, 0, fitsj->Height - 1, fitsj->Height - 1 }, true);

					if (fitsistart[0] >= fitsjstart[0] && fitsistart[0] <= fitsjend[0])//then i starts within j...delete the directory with smaller files
					{
						::FileStream^ fs = gcnew FileStream(filei, ::IO::FileMode::Open);
						__int64 fli = fs->Length;
						fs->Close();
						fs = gcnew FileStream(filej, ::IO::FileMode::Open);
						__int64 flj = fs->Length;
						fs->Close();

						if (flj < fli)
						{
							if (!delete_dir_list->Contains(dirj))
								delete_dir_list->Add(dirj);//delete the directory with smaller files
						}
						else
						{
							if (!delete_dir_list->Contains(diri))
								delete_dir_list->Add(diri);//delete the earlier directory
						}
						continue;
					}

					if (fitsiend[0] >= fitsjstart[0] && fitsiend[0] <= fitsjend[0])//then i ends within j...delete the directory with smaller files
					{
						::FileStream^ fs = gcnew FileStream(filei, ::IO::FileMode::Open);
						__int64 fli = fs->Length;
						fs->Close();
						fs = gcnew FileStream(filej, ::IO::FileMode::Open);
						__int64 flj = fs->Length;
						fs->Close();

						if (flj < fli)
						{
							if (!delete_dir_list->Contains(dirj))
								delete_dir_list->Add(dirj);//delete the directory with smaller files
						}
						else
						{
							if (!delete_dir_list->Contains(diri))
								delete_dir_list->Add(diri);//delete the earlier directory
						}
						continue;
					}

					if (fitsjstart[0] >= fitsistart[0] && fitsjstart[0] <= fitsiend[0])//then j starts within i...delete the directory with smaller files
					{
						::FileStream^ fs = gcnew FileStream(filei, ::IO::FileMode::Open);
						__int64 fli = fs->Length;
						fs->Close();
						fs = gcnew FileStream(filej, ::IO::FileMode::Open);
						__int64 flj = fs->Length;
						fs->Close();

						if (flj < fli)
						{
							if (!delete_dir_list->Contains(dirj))
								delete_dir_list->Add(dirj);//delete the directory with smaller files
						}
						else
						{
							if (!delete_dir_list->Contains(diri))
								delete_dir_list->Add(diri);//delete the earlier directory
						}
						continue;
					}

					if (fitsjend[0] >= fitsistart[0] && fitsjend[0] <= fitsiend[0])//then j ends within i...delete the directory with smaller files
					{
						::FileStream^ fs = gcnew FileStream(filei, ::IO::FileMode::Open);
						__int64 fli = fs->Length;
						fs->Close();
						fs = gcnew FileStream(filej, ::IO::FileMode::Open);
						__int64 flj = fs->Length;
						fs->Close();

						if (flj < fli)
						{
							if (!delete_dir_list->Contains(dirj))
								delete_dir_list->Add(dirj);//delete the directory with smaller files
						}
						else
						{
							if (!delete_dir_list->Contains(diri))
								delete_dir_list->Add(diri);//delete the earlier directory
						}
						continue;
					}
				}
			}

			for (int w = 0; w < delete_dir_list->Count; w++)
			{
				try
				{
					::Directory::Delete((String^)delete_dir_list[w], true);
				}
				catch (...)
				{
				}
			}
		}

		if (WAITBAR->Tag == nullptr)
			continue;

		String^ objVISdir = multidirs[dirindex] + "\\" + "VIS";
		if (!::Directory::Exists(objVISdir))
			continue;//return;//leave because there is no VIS directory

		ArrayList^ del_file_list = gcnew ArrayList();
		DiscardL1DuplicateWrkr->ReportProgress(-1, /*nullptr*/ gcnew array<Object^>(3) { multidirs->Length, dirindex + 1, del_file_list->Count });
		array<String^>^ VISdirs = ::Directory::GetDirectories(objVISdir, "*VIS*");//there may be multiple VIS directories...go through them and check for repeated VIS files

		//for all VIS files, scan forward and delete the forward/secondary ones...i.e. the repeated files with the exact same time
		int intprog = 1;
		array<String^>^ VISfiles = ::Directory::GetFiles(objVISdir, "*VIS*.fits", ::SearchOption::AllDirectories);
		
		array<unsigned __int32>^ times = gcnew array<unsigned __int32>(VISfiles->Length);

		//#pragma omp parallel for
		for (int i = 0; i < times->Length; i++)
			times[i] = Convert::ToUInt32(VISfiles[i]->Substring(VISfiles[i]->LastIndexOf("_") + 1, 13));

		for (int j = 0; j < VISfiles->Length - 1; j++)
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			if (100 * j / VISfiles->Length > intprog)
			{
				intprog++;
				DiscardL1DuplicateWrkr->ReportProgress(-intprog, gcnew array<Object^>(3) { multidirs->Length, dirindex + 1, del_file_list->Count });
			}

			//String^ Jtime = VISfiles[j]->Substring(VISfiles[j]->LastIndexOf("_") + 1, 13);
			unsigned __int32 Jtime = times[j];
			for (int k = j + 1; k < VISfiles->Length; k++)
			{
				//String^ Ktime = VISfiles[k]->Substring(VISfiles[k]->LastIndexOf("_") + 1, 13);
				unsigned __int32 Ktime = times[k];
				if (Ktime == Jtime)
					del_file_list->Add(VISfiles[k]);
			}
		}
		for (int i = 0; i < del_file_list->Count; i++)
			if (::File::Exists((String^)del_file_list[i]))
				::File::Delete((String^)del_file_list[i]);

		//delete any empty directories
		VISdirs = ::Directory::GetDirectories(objVISdir, "*VIS*");
		for (int j = 0; j < VISdirs->Length; j++)
			if (Directory::GetFiles(VISdirs[j])->Length == 0)
				Directory::Delete(VISdirs[j]);
		VISdirs = ::Directory::GetDirectories(objVISdir, "*VIS*");

		try
		{
			//now must check for directories which have been created but should actually be continuations
			//so sort the directories by time, then for each sorted directory, check the first and last files for continuation
			//if there is, then move the secondary files to the first directory
			array<double>^ VISdirtimes = gcnew array<double>(VISdirs->Length);
			for (int j = 0; j < VISdirs->Length; j++)
				VISdirtimes[j] = ::Convert::ToDouble(VISdirs[j]->Substring(VISdirs[j]->LastIndexOf("_") + 1));
			Array::Sort(VISdirtimes, VISdirs);
			//directories now sorted by start times

			intprog = 1;
			for (int j = 1; j < VISdirs->Length; j++)
			{
				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				if (100 * j / VISdirs->Length > intprog)
				{
					intprog++;
					DiscardL1DuplicateWrkr->ReportProgress(-intprog - 100, gcnew array<Object^>(2) { multidirs->Length, dirindex });//nullptr to tell it to display stuff about VIS
				}

				array<String^>^ jm1files = ::Directory::GetFiles(VISdirs[j - 1], "*VIS*.fits");
				array<String^>^ jfiles = ::Directory::GetFiles(VISdirs[j], "*VIS*.fits");
				if (jm1files->Length == 0)
					continue;
				Array::Sort(jm1files);
				Array::Sort(jfiles);
				double jm1fileendtime = ::Convert::ToDouble(jm1files[jm1files->Length - 1]->Substring(jm1files[jm1files->Length - 1]->LastIndexOf("_") + 1, 13));
				double jfilestartttime = ::Convert::ToDouble(jfiles[0]->Substring(jfiles[0]->LastIndexOf("_") + 1, 13));
				String^ jm1path = jm1files[0]->Substring(0, jm1files[0]->LastIndexOf("\\")) + "\\";

				if (jfilestartttime - jm1fileendtime <= 4 * 1000)//less than 4 seconds they should be the same sequence...1 ideally should be enough of a check
				{
					//then move the j files into j-1
					for (int k = 0; k < jfiles->Length; k++)
					{
						jfilestartttime = ::Convert::ToDouble(jfiles[k]->Substring(jfiles[k]->LastIndexOf("_") + 1, 13));
						if (jfilestartttime - jm1fileendtime <= 4 * 1000)
						{
							String^ jfile = jfiles[k]->Substring(jfiles[k]->LastIndexOf("\\") + 1);
							::File::Move(jfiles[k], jm1path + jfile);
							jm1fileendtime = jfilestartttime;
						}
					}
					//and skip the current directory on next iteration
					//j++;
				}
			}

			//delete any empty directories
			VISdirs = ::Directory::GetDirectories(objVISdir, "*VIS*");
			for (int j = 0; j < VISdirs->Length; j++)
				if (Directory::GetFiles(VISdirs[j])->Length == 0)
					Directory::Delete(VISdirs[j]);

			if (L1DiscardDataTimeChck->Checked)
			{
				String^ discardtimestring = (String^)L1DiscardDataTimeDrop->SelectedItem;
				discardtimestring = discardtimestring->Replace(" Minutes", "");
				int discardtimeint = ::Convert::ToInt32(discardtimestring) * 60;

				VISdirs = ::Directory::GetDirectories(objVISdir, "*VIS*");
				for (int i = 0; i < VISdirs->Length; i++)
					if (::Directory::GetFiles(VISdirs[i])->Length < discardtimeint)
						::Directory::Delete(VISdirs[i], true);
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
		}
	}
}

void Form1::DiscardL1DuplicateWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	if (e->UserState != nullptr && e->ProgressPercentage >= 0)
	{
		array<Object^>^ ustate = (array<Object^>^)e->UserState;
		int dirindex = (int)ustate[3];
		int ndirs = (int)ustate[2];
		int nfiles = (int)ustate[1];
		int nfound = (int)ustate[0];
		WAITBAR->ProgressBar->Maximum = nfiles+1;
		WAITBAR->ProgressBar->Value = e->ProgressPercentage;
		WAITBAR->TextMsg->Text = "Checking centroid list " + e->ProgressPercentage.ToString() + " of " + nfiles.ToString() + ". Found " + nfound.ToString() + " duplicated data sets.";
		WAITBAR->Text = "Processing target session folder " + dirindex.ToString() + " of " + ndirs.ToString();
		WAITBAR->Refresh();
		return;
	}
	if (/*e->UserState == nullptr &&*/ e->ProgressPercentage < 0 && e->ProgressPercentage >= -100)
	{
		array<Object^>^ ustate = (array<Object^>^)e->UserState;
		int dirindex = (int)ustate[1];
		int ndirs = (int)ustate[0];
		int nfils = (int)ustate[2];
		WAITBAR->ProgressBar->Maximum = 100;
		WAITBAR->ProgressBar->Value = -e->ProgressPercentage;
		WAITBAR->Text = "Scanning VIS files for repeated images...";
		WAITBAR->TextMsg->Text = "Processing target session folder " + dirindex.ToString() + " of " + ndirs.ToString() + "; Files Duplicates: " + nfils;
		WAITBAR->Refresh();
	}
	if (/*e->UserState == nullptr &&*/ e->ProgressPercentage < -100)
	{
		array<Object^>^ ustate = (array<Object^>^)e->UserState;
		int dirindex = (int)ustate[1];
		int ndirs = (int)ustate[0];
		WAITBAR->ProgressBar->Maximum = 200;
		WAITBAR->ProgressBar->Value = -e->ProgressPercentage;
		WAITBAR->Text = "Consolidating VIS directories...";
		WAITBAR->TextMsg->Text = "Processing target session folder " + (dirindex + 1).ToString() + " of " + ndirs.ToString();
		WAITBAR->Refresh();
	}
}

void Form1::DiscardL1DuplicateWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult != ::DialogResult::Cancel)
	{
		WAITBAR->ProgressBar->Value = WAITBAR->ProgressBar->Maximum;
		WAITBAR->Refresh();
		TimeSpan ts = DateTime::Now - DATE;
		if (!L1AutoRunChck->Checked)
			::MessageBox::Show("Completed digesting L1 data and discarding duplicated data in " + ts.Minutes.ToString() + "m" + ts.Seconds.ToString() + "s.","Finished...");
	}
	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::BringToFront();

	if (L1AutoRunChck->Checked && !L1SkipINTMode->Checked)
	{
		String^ visparentdir = (String^)GetReg("CCDLAB", "L2EventListPath") + "\\" + "VIS";
		array<String^>^ visdirs = ::Directory::GetDirectories(visparentdir);
		int N = 0, index = 0;
		for (int i = 0; i < visdirs->Length; i++)
			if (::Directory::GetFiles(visdirs[i])->Length > N)
			{
				index = i;
				N = ::Directory::GetFiles(visdirs[i])->Length;
			}

		array<String^>^ files = ::Directory::GetFiles(visdirs[index], "*VIS*.fits");

		FITSImageSet^ medianset = gcnew FITSImageSet();
		medianset->Load(files, nullptr, false, true, true, "");

		FITSImage^ median = FITSImageSet::Median(medianset, false, true, "Median Background");
		median->AddKey("NIMAGES", medianset->Count.ToString(), "Number of images used", -1);
		median->WriteImage(visparentdir + "\\" + "median.fts", TypeCode::Double, true);

		FileListDrop->Items->Clear();
		IMAGESET->Clear();
		array<String^>^ filelist = gcnew array<String^>(1) { median->FullFileName };
		AddToImageSet(filelist);
		Form1::Enabled = true;
		Form1::BringToFront();

		if (!L1AutoProceedVISBackGround->Checked)
			if (MessageBox::Show("OK to proceed with this image for background subtraction?", "Background correction?", MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;

		UVITBATCHOP = true;
		MainTab->SelectTab("BatchTab");
		BatchOperationTab->SelectTab("BatchIndividualTab");
		BatchScanDirectoryBtn->PerformClick();
		BatchFileParallelChck->Checked = true;
		UVITBATCHMESG = "Subtracting Median from " + BATCHLIST->Length + " VIS Images...";
		BatchComputeBtn_Click(sender, e);
		UVITBATCHMESG = "";
		if (UVITBATCHOP_CANCELLED)
		{
			UVITBATCHOP_CANCELLED = false;
			return;
		}

		if (!L1AutoProceedVISTracking->Checked)
			if (MessageBox::Show("Proceed to Drift Series Tracking?", "Proceed with Drift?", MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			{
				AUTOVISDRIFT = false;
				return;
			}

		SetReg("CCDLAB", "L2EventListPath", visparentdir);
		AUTOVISDRIFT = true;
		UVITMANREGDIRLISTINDEX = 0;
		HalfWidthXUpD->Value = 5;
		HalfWidthYUpD->Value = 5;
		ManRegTrkHWUpD->Value = HalfWidthXUpD->Value;
		CreateDriftFromINTMenuItem_Click(sender, e);
		return;
	}
}

void Form1::CreateFlatFieldListMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = true;
	dlg->Title = "Select the Centroid INTEGERS List(s) (_XYInts_List)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;

	dir = dlg->FileNames[0]->Substring(0, dlg->FileNames[0]->LastIndexOf("\\"));
	SetReg("CCDLAB", "L2EventListPath", dir);

	ProgressBar->Maximum = dlg->FileNames->Length;
	ProgressBar->Value = 0;
	
	for (int i = 0; i < dlg->FileNames->Length; i++)
	{
		ProgressBar->Value++;
		ProgressBar->Refresh();

		FITSImage^ intsfits = gcnew JPFITS::FITSImage(dlg->FileNames[i], nullptr, true, true, false, true);
		FITSImage^ flat;
		String^ channel = intsfits->GetKeyValue("CHANNEL");
		if (channel == "")
			channel = intsfits->GetKeyValue("DETECTOR");
		bool flatsuccess = false;
		if (channel == "FUV")
			if (::File::Exists("C:\\UVIT_CalDB\\Flats Normalized\\FUV Normalized Flat.fits"))
			{
				flat = gcnew FITSImage("C:\\UVIT_CalDB\\Flats Normalized\\FUV Normalized Flat.fits", nullptr, true, true, false, true);
				flatsuccess = true;
			}
		if (channel == "NUV")
			if (::File::Exists("C:\\UVIT_CalDB\\Flats Normalized\\NUV Normalized Flat.fits"))
			{
				flat = gcnew FITSImage("C:\\UVIT_CalDB\\Flats Normalized\\NUV Normalized Flat.fits", nullptr, true, true, false, true);
				flatsuccess = true;
			}
		if (channel == "VIS")
			if (::File::Exists("C:\\UVIT_CalDB\\Flats Normalized\\VIS Normalized Flat.fits"))
			{
				flat = gcnew FITSImage("C:\\UVIT_CalDB\\Flats Normalized\\VIS Normalized Flat.fits", nullptr, true, true, false, true);
				flatsuccess = true;
			}
		if (!flatsuccess)
		{
			::MessageBox::Show("Couldn't find the flat file in the CalDB...stopping.", "Error");
			return;
		}

		int NPts = intsfits->Height;
		array<double>^ flatlist = gcnew array<double>(NPts);

		for (int j = 0; j < NPts; j++)
		{
			int xpos = int(intsfits[0, j] / 32);
			int ypos = int(intsfits[1, j] / 32);
			if (xpos < 0 || xpos > 511 || ypos < 0 || ypos > 511)
				flatlist[j] = 1;
			else
				flatlist[j] = flat[xpos, ypos];
		}

		String^ name = dlg->FileNames[i]->Substring(0, dlg->FileNames[i]->IndexOf("XYInts")) + "FlatList.fits";
		FITSImage^ fitsflatlist = gcnew FITSImage(name, flatlist, false, true);
		fitsflatlist->CopyHeader(intsfits);
		fitsflatlist->WriteImage(::TypeCode::Double, true);
	}

	::MessageBox::Show("Completed making the flat field list(s).","Finished...");
	ProgressBar->Value = 0;
	ProgressBar->Refresh();
}

void Form1::ParcelStackmdMmChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	ParcelListAsFramesMenuItem->ShowDropDown();
}

void Form1::ParcelStackTimeDrop_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ time = (String^)ParcelStackTimeDrop->SelectedItem;
	time = time->Remove(time->IndexOf("s"));
	UVPARCELTIME = ::Convert::ToDouble(time);

	if (UVPARCELTIME == 0)
		if (::MessageBox::Show("Parcelling out each frame as a file can create an extremely large number of files. Are you sure?","Warning...",::MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;

	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = false;
	dlg->Title = "Select the Centroid INTEGERS List (_XYInts_List)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;

	String^ intslistfile = dlg->FileName;
	dir = intslistfile->Substring(0, intslistfile->LastIndexOf("\\"));
	SetReg("CCDLAB", "L2EventListPath", dir);

	String^ parceldir = dir + "\\" + UVPARCELTIME.ToString() + "\\";
	if (Directory::Exists(parceldir))
		Directory::Delete(parceldir, true);
	Directory::CreateDirectory(parceldir);

	String^ mindir;
	String^ maxmindir;
	if (ParcelStackmdMmChck->Checked)
	{
		mindir = dir + "\\" + UVPARCELTIME.ToString() + "min" + "\\";
		maxmindir = dir + "\\" + UVPARCELTIME.ToString() + "dMaxmin" + "\\";

		if (Directory::Exists(mindir))
			Directory::Delete(mindir, true);
		Directory::CreateDirectory(mindir);

		if (Directory::Exists(maxmindir))
			Directory::Delete(maxmindir, true);
		Directory::CreateDirectory(maxmindir);
	}
	
	SetReg("CCDLAB", "FolderBrowserPath", parceldir);

	//ok so now send the filenames and dir to the worker arg, load the fits files and arrays there
	array<Object^>^ arg = gcnew array<Object^>(4);
	arg[0] = (Object^)intslistfile;
	arg[1] = (Object^)parceldir;
	if (ParcelStackmdMmChck->Checked)
	{
		arg[2] = mindir;
		arg[3] = maxmindir;
	}
	else
	{
		arg[2] = nullptr;
		arg[3] = nullptr;
	}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->DialogResult = ::DialogResult::OK;
	WAITBAR->Text = "Parcelling List...";
	ParcelUVCentroidWrkr->RunWorkerAsync(arg);
	WAITBAR->Show();
}

void Form1::ParcelUVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<Object^>^ arg = (array<Object^>^)e->Argument;
	String^ intslistfile = (String^)arg[0];
	String^ fraclistfile = intslistfile->Replace("Ints","Frac");
	String^ parceldir = (String^)arg[1];
	String^ mindir = (String^)arg[2];
	String^ maxmindir = (String^)arg[3];
	String^ timeslistfile = intslistfile->Remove(intslistfile->IndexOf("XYInts_List")) + "TimeList.fits";
	String^ deDrift = "_deDrift";
	while (intslistfile->Contains(deDrift))
	{
		timeslistfile = timeslistfile->Replace("TimeList", "TimeList_deDrift");
		deDrift += "_deDrift";
	}
	String^ mdMmfile;
	FITSImage^ mdMmlist;
	array<double, 2>^ mdMms;
	if (mindir != nullptr)
	{
		mdMmfile = timeslistfile->Replace("TimeList", "XYmdMm_List");
		mdMmlist = gcnew JPFITS::FITSImage(mdMmfile, nullptr, true, false, false, false);
		mdMms = FITSImage::ReadImageArrayOnly(mdMmfile, nullptr, true);
	}

	FITSImage^ timeslist = gcnew JPFITS::FITSImage(timeslistfile, nullptr, true, false, false, false);
	array<double>^ times = FITSImage::ReadImageVectorOnly(timeslistfile, nullptr, true);

	FITSImage^ intslist = gcnew JPFITS::FITSImage(intslistfile, nullptr, true, false, false, false);
	array<double,2>^ ints = FITSImage::ReadImageArrayOnly(intslistfile, nullptr, true);
	
	FITSImage^ fraclist = gcnew JPFITS::FITSImage(fraclistfile, nullptr, true, false, false, false);
	array<double,2>^ frac = FITSImage::ReadImageArrayOnly(fraclistfile, nullptr, true);

	String^ EXTXRNG = fraclist->GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
	if (EXTXRNG == "")
		EXTXRNG = "0:511";//from L2 data
	String^ EXTYRNG = fraclist->GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
	if (EXTYRNG == "")
		EXTYRNG = "0:511";//from L2 data
	int ix = EXTXRNG->IndexOf(":");
	int iy = EXTYRNG->IndexOf(":");
	int rx1 = ::Convert::ToInt32(EXTXRNG->Substring(0,ix));//range start
	int ry1 = ::Convert::ToInt32(EXTYRNG->Substring(0,iy));
	int rx2 = ::Convert::ToInt32(EXTXRNG->Substring(ix+1));//range end
	int ry2 = ::Convert::ToInt32(EXTYRNG->Substring(iy+1));

	String^ xoffset = intslist->GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
	if (xoffset == "")
		xoffset = intslist->GetKeyValue("WIN_XOFF");//from L2 data
	double ox = ::Convert::ToDouble(xoffset);//x offset
	String^ yoffset = intslist->GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
	if (yoffset == "")
		yoffset = intslist->GetKeyValue("WIN_YOFF");//from L2 data
	double oy = ::Convert::ToDouble(yoffset);//y offset
	String^ sizex = intslist->GetKeyValue("XSIZE");
	if (sizex == "")
		sizex = intslist->GetKeyValue("WIN_X_SZ");
	int szx = ::Convert::ToInt32(sizex);//x size
	String^ sizey = intslist->GetKeyValue("YSIZE");
	if (sizey == "")
		sizey = intslist->GetKeyValue("WIN_Y_SZ");
	int szy = ::Convert::ToInt32(sizey);//y size

	if (rx1 != 0 && rx2 != 511)
			szx = rx2-rx1;
	if (ry1 != 0 && ry2 != 511)
		szy = ry2-ry1;

	int prec = 1;
	szx = (szx + 1)*prec;
	szy = (szy + 1)*prec;

	ArrayList^ imgfilenames = gcnew ArrayList();
	array<int, 2>^ img;
	array<int, 2>^ minimg;
	array<int, 2>^ maxminimg;
	array<int>^ foundinds;
	int ind = -1;
	int Ntimes = times->Length;
	int Nfound;
	int xpos, ypos;
	FITSImage^ FITSimg;
	FITSImage^ FITSminimg;
	FITSImage^ FITSmaxminimg;
	String^ parcelname;
	String^ minname;
	String^ maxminname;
	int c = 0;
	unsigned __int32 currtime = 0;
	int intprog = 0;
	bool end = false;//the routine will have to tell when it is at the end of the time list
	while (!end)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			break;
		if (100*ind/Ntimes > intprog+1)
		{
			intprog++;
		}
		ParcelUVCentroidWrkr->ReportProgress(intprog, c+1);

		c++;
		currtime = (unsigned __int32)times[ind+1];
		img = gcnew array<int,2>((int)szx,(int)szy);
		minimg = gcnew array<int, 2>((int)szx, (int)szy);
		maxminimg = gcnew array<int, 2>((int)szx, (int)szy);
		foundinds = JPMath::Find(times, times[ind+1]+UVPARCELTIME*1000, "<=", ind+1);
		if (foundinds->Length == 0)
			goto nonefound;
		Nfound = foundinds->Length;
		ind = foundinds[Nfound-1];
		if (ind == Ntimes-1)
			end = true;

		int j;
		for (j = 0; j < Nfound; j++)
		{
			xpos = (int)((ints[0,foundinds[j]] - rx1*32 - ox*32 + frac[0,foundinds[j]] + 16)/32 * prec);//reset integers to start at 0
			ypos = (int)((ints[1,foundinds[j]] - ry1*32 - oy*32 + frac[1,foundinds[j]] + 16)/32 * prec);//must add 16 to fractionals

			if (xpos < 0 || ypos < 0 || xpos > szx-1 || ypos > szy-1)//ignore out of bounds
				continue;

			img[xpos, ypos]++;
			if (mindir != nullptr)
			{
				minimg[xpos, ypos] += (int)mdMms[0, foundinds[j]];
				maxminimg[xpos, ypos] += (int)mdMms[1, foundinds[j]];
			}
		}

	nonefound:;

		if (mindir != nullptr)
		{
			#pragma omp parallel for
			for (int x = 0; x < szx; x++)
				for (int y = 0; y < szy; y++)
					if (img[x, y] != 0)
					{
						minimg[x, y] /= img[x, y];
						maxminimg[x, y] /= img[x, y];
					}
		}

		parcelname = parceldir + currtime.ToString("0000000000000") + ".fits";
		FITSimg = gcnew FITSImage(parcelname, img, false, true);
		FITSimg->CopyHeader(intslist);
		FITSimg->AddKey("PARCTIME", currtime.ToString("0000000000000"), "Parcel time.", 10);
		FITSimg->AddKey("FRMTIME", (double(currtime)/1000).ToString(), "Frame time.", 11);
		FITSimg->WriteImage(::TypeCode::UInt16, true);
		imgfilenames->Add(parcelname);

		if (mindir != nullptr)
		{
			minname = mindir + currtime.ToString("0000000000000") + ".fits";
			maxminname = maxmindir + currtime.ToString("0000000000000") + ".fits";

			FITSminimg = gcnew FITSImage(minname, minimg, false, true);
			FITSmaxminimg = gcnew FITSImage(maxminname, maxminimg, false, true);

			FITSminimg->CopyHeader(intslist);
			FITSmaxminimg->CopyHeader(intslist);

			FITSminimg->AddKey("PARCTIME", currtime.ToString("0000000000000"), "Parcel time.", 10);
			FITSminimg->AddKey("FRMTIME", (double(currtime) / 1000).ToString(), "Frame time.", 11);
			FITSminimg->WriteImage(::TypeCode::UInt16, true);

			FITSmaxminimg->AddKey("PARCTIME", currtime.ToString("0000000000000"), "Parcel time.", 10);
			FITSmaxminimg->AddKey("FRMTIME", (double(currtime) / 1000).ToString(), "Frame time.", 11);
			FITSmaxminimg->WriteImage(::TypeCode::UInt16, true);
		}
	}

	e->Result = imgfilenames;
}

void Form1::ParcelUVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = "Completed: " + e->ProgressPercentage + "%: " + (int)e->UserState + " frames...";
	WAITBAR->Refresh();
}

void Form1::ParcelUVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::BringToFront();
	//if (WAITBAR->DialogResult != ::DialogResult::Cancel)
		if (MessageBox::Show("Parcelling completed or stopped.  Would you like to load the images for viewing?", "Finished...", MessageBoxButtons::YesNo) == ::DialogResult::No)
			return;

	ArrayList^ imgfilenames = (ArrayList^)e->Result;
	array<String^>^ filelist = gcnew array<String^>(imgfilenames->Count);
	for (int i = 0; i < imgfilenames->Count; i++)
		filelist[i] = (String^)imgfilenames[i];

	FileListDrop->Items->Clear();
	IMAGESET->Clear();
	AddToImageSet(filelist);
	Form1::Enabled = true;
	Form1::BringToFront();
}

void Form1::PlotDriftListMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ driftlistfile;
	if (UVPLOTDRIFTLISTNOW)
	{
		//UVPLOTDRIFTLISTNOW = false;***************************************done below with multi-source track plot now
		driftlistfile = UVPLOTDRIFTFILENAME;
	}
	else
	{
		String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		OpenFileDialog^ dlg = gcnew OpenFileDialog();
		dlg->InitialDirectory = dir;
		dlg->Filter = "DRIFT (*.drift)|*.drift";
		dlg->Multiselect = false;
		dlg->Title = "Select the Drift List (_XYDrift_List)";
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		driftlistfile = dlg->FileName;
	}

	FITSImage^ driftfits = gcnew JPFITS::FITSImage(driftlistfile, nullptr, true, true, false, true);

	//only want to plot unique drifts or else 100,000's data to be plotted which is slow
	int unique = 1;
	int xd = (int)driftfits[1, 0], yd = (int)driftfits[2, 0];
	for (int i = 1; i < driftfits->Height; i++)
	{
		if (xd == (int)driftfits[1, i] && yd == (int)driftfits[2, i])
			continue;
		
		unique++;
		xd = (int)driftfits[1, i];
		yd = (int)driftfits[2, i];
	}
	//now unique is how many unique drifts there are, so make arrays for time, x, y

	array<double>^ time	  = gcnew array<double>(unique);
	array<double>^ xdrift = gcnew array<double>(unique);
	array<double>^ ydrift = gcnew array<double>(unique);
	
	unique = 0;//now an index
	time[unique] = driftfits[0, 0]/1000;
	xdrift[unique] = driftfits[1, 0]/32;
	ydrift[unique] = driftfits[2, 0]/32;

	xd = (int)driftfits[1, 0];
	yd = (int)driftfits[2, 0];
	for (int i = 1; i < driftfits->Height; i++)
	{
		if (xd == (int)driftfits[1, i] && yd == (int)driftfits[2, i])
			continue;

		unique++;
		xd = (int)driftfits[1, i];
		yd = (int)driftfits[2, i];

		time[unique]   = driftfits[0, i]/1000;
		xdrift[unique] = driftfits[1, i]/32;
		ydrift[unique] = driftfits[2, i]/32;
	}

	String^ title = "Orbit: " + driftfits->GetKeyValue("ORB_NUM") + "; Source: " + driftfits->GetKeyValue("SOURCEID") + "; Detector:" + driftfits->GetKeyValue("DETECTOR");

	if (XDRIFT_PLOT->IsDisposed)
		XDRIFT_PLOT = gcnew JPPlot();
	if (YDRIFT_PLOT->IsDisposed)
		YDRIFT_PLOT = gcnew JPPlot();

	XDRIFT_PLOT->Text = "X-Drift";
	XDRIFT_PLOT->PlotLine(JPMath::VectorSubScalar(time, time[0], true), xdrift, "Time - " + time[0].ToString() + " (seconds)", "X-Drift (pixels)", title, Charting::SeriesChartType::Line, "XDrift");
	if (XDRIFT_PLOT->plotchart1->AxesGridMenuChck->Checked == false)
		XDRIFT_PLOT->plotchart1->AxesGridMenuChck->PerformClick();
	YDRIFT_PLOT->Text = "Y-Drift";
	YDRIFT_PLOT->PlotLine(JPMath::VectorSubScalar(time, time[0], true), ydrift, "Time - " + time[0].ToString() + " (seconds)", "Y-Drift (pixels)", title, Charting::SeriesChartType::Line, "YDrift");
	if (YDRIFT_PLOT->plotchart1->AxesGridMenuChck->Checked == false)
		YDRIFT_PLOT->plotchart1->AxesGridMenuChck->PerformClick();

	if (UVPLOTDRIFTLISTNOW && MANREGCENTROIDS != nullptr)
	{
		array<double>^ tttime = gcnew array<double>(driftfits->Height);
		array<double>^ xxdrft = gcnew array<double>(driftfits->Height);
		array<double>^ yydrft = gcnew array<double>(driftfits->Height);
		double meanxxd = 0, meanyyd = 0;
		for (int j = 0; j < MANREGCENTROIDS->GetLength(0); j++)
			for (int i = 0; i < driftfits->Height; i++)
			{
				if (j == 0)
					tttime[i] = (driftfits[0, i] - driftfits[0, 0]) / 1000;

				meanxxd += (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]);
				meanyyd += (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]);
			}
		meanxxd /= MANREGCENTROIDS->GetLength(0)*driftfits->Height;
		meanyyd /= MANREGCENTROIDS->GetLength(0)*driftfits->Height;

		for (int j = 0; j < MANREGCENTROIDS->GetLength(0); j++)
		{
			for (int i = 0; i < driftfits->Height; i++)
			{
				xxdrft[i] = (MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0]) - meanxxd;
				yydrft[i] = (MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0]) - meanyyd;
			}
			XDRIFT_PLOT->AddLine(tttime, xxdrft, Charting::SeriesChartType::Line, j.ToString());
			YDRIFT_PLOT->AddLine(tttime, yydrft, Charting::SeriesChartType::Line, j.ToString());
		}
	}
	MANREGCENTROIDS = nullptr;
	UVPLOTDRIFTLISTNOW = false;
}

void Form1::DriftFromPCPSTrackBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	//this function is the initiator and also the revisitor

	//initiator on !UVDRIFTBATCH
	if (!UVDRIFTBATCH)
	{
		if (PointSrcROIFindSrcChck->Checked && !PointSrcROIAutoRunChck->Checked)//should this be done for each image individually?????????????????????????????      could put it below so it always fires if requested
		{
			int Nsrc = Convert::ToInt32(PointSrcROIFindNSrcDrop->SelectedItem);
			PSE = gcnew JPFITS::SourceExtractor();
			PSE->Extract_Attempt_N_Sources(Nsrc, IMAGESET[FILELISTINDEX]->Image, 0, 0, Double::MaxValue, 0, Double::MaxValue, false, 9, 35, true, "", nullptr, false);
			if (PSE->N_Sources > Nsrc)
				PSE->ClipToNBrightest(Nsrc);

			if (PSE->N_Sources == 0)
			{
				MessageBox::Show("No sources found. Please manually select sources.", "Error...");
				return;
			}

			MARKCOORDS = gcnew array<double, 2>(2, PSE->N_Sources);
			for (int i = 0; i < PSE->N_Sources; i++)
			{
				MARKCOORDS[0, i] = PSE->Centroids_X[i];
				MARKCOORDS[1, i] = PSE->Centroids_Y[i];
			}
			MAKEMARKCOORDRECTS();
			PSE = nullptr;

			ImageWindow->Refresh();
			SubImageWindow->Refresh();

			if (MessageBox::Show("Use these sources for optimization?", "Proceed with these sources?", MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
				return;
		}

		if (HalfWidthXUpD->Value >= 15 || HalfWidthYUpD->Value >= 15)
		{
			HalfWidthXUpD->Value = 9;
			HalfWidthYUpD->Value = 9;
		}

		AUTOLOADIMAGESFILES = gcnew array<String^>(IMAGESET->Count);
		UVDRIFTBATCHFILES = gcnew array<String^>(IMAGESET->Count);//must fill these here first with XYInts
		for (int i = 0; i < IMAGESET->Count; i++)
		{
			String^ imgname = IMAGESET[i]->FullFileName;
			String^ dedrift = "";
			while (imgname->Contains(dedrift + "_deDrift"))
				dedrift += "_deDrift";

			String^ intsname = imgname->Substring(0, imgname->IndexOf("_IMAGE"));
			intsname = intsname->Insert(intsname->IndexOf("deFPN"), "XYInts_List_") + ".fits";
			UVDRIFTBATCHFILES[i] = intsname;
		}
		DRIFTFROMPCPSTRACK = true;
		UVDRIFTBATCH = true;
		UVDRIFTAUTORUN = true;
		UVCONVERTLISTTOIMAGEBATCH = false;
		UVAutoApplyDriftandImageChck->Checked = true;
		UVAutoDriftImageViewChck->Checked = false;
		UVDRIFTBATCHFILESINDEX = 0;
	}

	if (PointSrcROIAutoRunChck->Checked)
	{
		FileListDrop->SelectedIndex = UVDRIFTBATCHFILESINDEX;
		int Nsrc = Convert::ToInt32(PointSrcROIFindNSrcDrop->SelectedItem);//or just set to 3???
		PSE = gcnew JPFITS::SourceExtractor();
		PSE->Extract_Attempt_N_Sources(Nsrc, IMAGESET[UVDRIFTBATCHFILESINDEX]->Image, 0, 0, Double::MaxValue, 0, Double::MaxValue, false, 9, 35, true, "", nullptr, false);
		if (PSE->N_Sources > Nsrc)
			PSE->ClipToNBrightest(Nsrc);

		if (PSE->N_Sources == 0)
		{
			MessageBox::Show("No sources found. Please manually select sources.", "Error...");
			AUTOLOADIMAGESFILES = nullptr;
			UVDRIFTBATCHFILES = nullptr;
			DRIFTFROMPCPSTRACK = false;
			UVDRIFTBATCH = false;
			UVDRIFTAUTORUN = false;
			UVCONVERTLISTTOIMAGEBATCH = false;
			UVAutoApplyDriftandImageChck->Checked = false;
			UVAutoDriftImageViewChck->Checked = false;
			UVDRIFTBATCHFILESINDEX = -1;
			return;
		}

		MARKCOORDS = gcnew array<double, 2>(2, PSE->N_Sources);
		for (int i = 0; i < PSE->N_Sources; i++)
		{
			MARKCOORDS[0, i] = PSE->Centroids_X[i];
			MARKCOORDS[1, i] = PSE->Centroids_Y[i];
		}
		MAKEMARKCOORDRECTS();
		PSE = nullptr;

		ImageWindow->Refresh();
		SubImageWindow->Refresh();
	}

	if (UVDRIFTBATCHFILESINDEX == 0)//initiator
	{
		Form1::Enabled = false;
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = 100;
		WAITBAR->Text = "File " + (UVDRIFTBATCHFILESINDEX + 1).ToString() + " of " + UVDRIFTBATCHFILES->Length + ". Optimizing PSF...";
		DriftFromPCPSTrackBGWrkr->RunWorkerAsync();
		WAITBAR->ShowDialog();
	}
	else//revisitor
	{
		WAITBAR->ProgressBar->Value = (UVDRIFTBATCHFILESINDEX + 1) * 100 / UVDRIFTBATCHFILES->Length;
		WAITBAR->Text = "File " + (UVDRIFTBATCHFILESINDEX + 1).ToString() + " of " + UVDRIFTBATCHFILES->Length + ". Optimizing PSF...";
		DriftFromPCPSTrackBGWrkr->RunWorkerAsync();
	}
}

void Form1::DriftFromPCPSTrackBGWrkr_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
		return;

	String^ imgname = IMAGESET[UVDRIFTBATCHFILESINDEX]->FullFileName;
	String^ dedrift = "";
	while (imgname->Contains(dedrift + "_deDrift"))
		dedrift += "_deDrift";

	String^ timesname = imgname->Substring(0, imgname->IndexOf("deFPN")) + "TimeList" + dedrift + ".fits";
	String^ intsname = imgname->Substring(0, imgname->IndexOf("_IMAGE"));
	intsname = intsname->Insert(intsname->IndexOf("deFPN"), "XYInts_List_") + ".fits";
	String^ fracsname = intsname->Replace("Ints", "Frac");

	JPFITS::FITSImage^ IntsFits = gcnew FITSImage(intsname, nullptr, true, false, false, false);
	array<double>^ times = FITSImage::ReadImageVectorOnly(timesname, nullptr, true);
	array<double, 2>^ fracs = FITSImage::ReadImageArrayOnly(fracsname, nullptr, true);
	array<double, 2>^ ints = FITSImage::ReadImageArrayOnly(intsname, nullptr, true);

	String^ FlatFileList;
	array<double>^ flat;
	FlatFileList = timesname->Replace("Time", "Flat");
	flat = FITSImage::ReadImageVectorOnly(FlatFileList, nullptr, true);

	String^ EXTXRNG = IntsFits->GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
	if (EXTXRNG == "")
		EXTXRNG = "0:511";//from L1 data
	String^ EXTYRNG = IntsFits->GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
	if (EXTYRNG == "")
		EXTYRNG = "0:511";//from L1 data
	int ix = EXTXRNG->IndexOf(":");
	int iy = EXTYRNG->IndexOf(":");
	double rx1 = ::Convert::ToDouble(EXTXRNG->Substring(0, ix));//range start
	double ry1 = ::Convert::ToDouble(EXTYRNG->Substring(0, iy));
	double rx132 = rx1 * 32;
	double ry132 = ry1 * 32;
	double rx2 = ::Convert::ToDouble(EXTXRNG->Substring(ix + 1));//range end
	double ry2 = ::Convert::ToDouble(EXTYRNG->Substring(iy + 1));

	String^ xoffset = IntsFits->GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
	if (xoffset == "")
		xoffset = IntsFits->GetKeyValue("WIN_XOFF");//from L1 data
	double ox = ::Convert::ToDouble(xoffset);//x offset
	double ox32 = ox * 32;
	String^ yoffset = IntsFits->GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
	if (yoffset == "")
		yoffset = IntsFits->GetKeyValue("WIN_YOFF");//from L1 data
	double oy = ::Convert::ToDouble(yoffset);//y offset
	double oy32 = oy * 32;

	double rx132ox32 = rx132 + ox32;
	double ry132oy32 = ry132 + oy32;

	double prec = 1;
	String^ strprec = IMAGESET[UVDRIFTBATCHFILESINDEX]->GetKeyValue("IMAGPREC");
	if (strprec != "")
		prec = ::Convert::ToDouble(strprec);
	double precB32 = prec / 32;

	int offset = 0;
	String^ stroffset = IMAGESET[UVDRIFTBATCHFILESINDEX]->GetKeyValue("PADOFSET");
	if (stroffset != "")
		offset = ::Convert::ToInt32(stroffset);

	if (MARKCOORDS == nullptr)//then use current ROI only
		MARKCOORDS = gcnew array<double, 2>(2, 1) { {(double)XSUBRANGE[SUBIMAGE_HWX]}, { (double)YSUBRANGE[SUBIMAGE_HWY] } };

	array<ArrayList^>^ ROIsTRUE = gcnew array<ArrayList^>(MARKCOORDS->GetLength(1));
	array<int>^ XSTARTS = gcnew array<int>(MARKCOORDS->GetLength(1));
	array<int>^ XENDS = gcnew array<int>(MARKCOORDS->GetLength(1));
	array<int>^ YSTARTS = gcnew array<int>(MARKCOORDS->GetLength(1));
	array<int>^ YENDS = gcnew array<int>(MARKCOORDS->GetLength(1));
	for (int i = 0; i < ROIsTRUE->Length; i++)
	{
		array<double, 2>^ bigbox = IMAGESET[UVDRIFTBATCHFILESINDEX]->GetSubImage((int)MARKCOORDS[0, i], (int)MARKCOORDS[1, i], 20, 20);
		int maxx, maxy;
		JPMath::Max(bigbox, maxx, maxy, false);
		int xcent = (int)MARKCOORDS[0, i] - 20 + maxx;
		int ycent = (int)MARKCOORDS[1, i] - 20 + maxy;

		XSTARTS[i] = xcent - SUBIMAGE_HWX - offset * int(prec);
		YSTARTS[i] = ycent - SUBIMAGE_HWY - offset * int(prec);
		XENDS[i] = xcent + SUBIMAGE_HWX - offset * int(prec);
		YENDS[i] = ycent + SUBIMAGE_HWY - offset * int(prec);
		ROIsTRUE[i] = gcnew ArrayList();

		#pragma omp parallel for
		for (int j = 0; j < times->Length; j++)
		{
			int xpos = (int)((ints[0, j] - rx132ox32 + fracs[0, j] + 16) * precB32);
			int ypos = (int)((ints[1, j] - ry132oy32 + fracs[1, j] + 16) * precB32);

			if (xpos >= XSTARTS[i] && ypos >= YSTARTS[i] && xpos <= XENDS[i] && ypos <= YENDS[i])
			{
				#pragma omp critical
				{
					ROIsTRUE[i]->Add(j);
				}
			}
		}
	}
	#pragma omp parallel for
	for (int i = 0; i < ROIsTRUE->Length; i++)
		ROIsTRUE[i]->Sort();

	array<array<double>^>^ ROItlists = gcnew array<array<double>^>(MARKCOORDS->GetLength(1));
	array<array<double>^>^ ROIxcents = gcnew array<array<double>^>(MARKCOORDS->GetLength(1));
	array<array<double>^>^ ROIycents = gcnew array<array<double>^>(MARKCOORDS->GetLength(1));
	array<array<double>^>^ ROIflats = gcnew array<array<double>^>(MARKCOORDS->GetLength(1));
	array<array<int>^>^ ROIindexes = gcnew array<array<int>^>(MARKCOORDS->GetLength(1));
	for (int i = 0; i < ROIsTRUE->Length; i++)
	{
		ROItlists[i] = gcnew array<double>(ROIsTRUE[i]->Count);
		ROIxcents[i] = gcnew array<double>(ROIsTRUE[i]->Count);
		ROIycents[i] = gcnew array<double>(ROIsTRUE[i]->Count);
		ROIflats[i] = gcnew array<double>(ROIsTRUE[i]->Count);
		ROIindexes[i] = gcnew array<int>(ROIsTRUE[i]->Count);
	}
	#pragma omp parallel for
	for (int i = 0; i < ROIsTRUE->Length; i++)
		for (int j = 0; j < ROIsTRUE[i]->Count; j++)
		{
			ROIindexes[i][j] = Convert::ToInt32(ROIsTRUE[i][j]);
			ROItlists[i][j] = times[ROIindexes[i][j]];
			ROIflats[i][j] = flat[ROIindexes[i][j]];
		}

	int index = -1;//only used next if needed
	bool endanalysis = false;
	array<double>^ meanMAXarray = gcnew array<double>(PointSrcROIStackDriftDrop->Items->Count);
	array<double>^ stakMAXarray = gcnew array<double>(PointSrcROIStackDriftDrop->Items->Count);
	bool final_determination = false;
	goagaion:
	if (MARKCOORDS->GetLength(1) > 1 && !final_determination)//then auto run through and find best stack time?
	{
		index++;
		if (index < PointSrcROIStackDriftDrop->Items->Count)
			PointSrcROIStackDriftDrop->SelectedIndex = index;
		if (index == PointSrcROIStackDriftDrop->Items->Count - 1)
			endanalysis = true;
		stakMAXarray[index] = Convert::ToDouble(PointSrcROIStackDriftDrop->SelectedItem);
		DriftFromPCPSTrackBGWrkr->ReportProgress(index);
	}
	if (MARKCOORDS->GetLength(1) == 1)
		index = PointSrcROIStackDriftDrop->SelectedIndex;

	array<double, 2>^ drift = gcnew array<double, 2>(3, times->Length);
	//if multi sources need to loop here on MARKCOORDS
	for (int i = 0; i < MARKCOORDS->GetLength(1); i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;

		for (int j = 0; j < ROIxcents[i]->Length; j++)
		{
			ROIxcents[i][j] = ints[0, ROIindexes[i][j]] - rx132ox32 + fracs[0, ROIindexes[i][j]] + 16;
			ROIycents[i][j] = ints[1, ROIindexes[i][j]] - ry132oy32 + fracs[1, ROIindexes[i][j]] + 16;
		}

		double stackT = Convert::ToDouble(PointSrcROIStackDriftDrop->SelectedItem) * 1000;
		bool end = false;
		double currtime;
		int j = 0;
		double meanx, meany, meanT;
		double stackinstcs;
		ArrayList^ mt = gcnew ArrayList();
		ArrayList^ mx = gcnew ArrayList();
		ArrayList^ my = gcnew ArrayList();

		while (!end)
		{
			meanx = 0;
			meany = 0;
			meanT = 0;
			stackinstcs = 0;
			currtime = ROItlists[i][j];
			while (!end && (ROItlists[i][j] - currtime) <= stackT)
			{
				meanx += ROIxcents[i][j];
				meany += ROIycents[i][j];
				stackinstcs++;
				j++;

				if (j == ROItlists[i]->Length)
				{
					end = true;
					break;
				}
			}
			meanx /= stackinstcs;
			meany /= stackinstcs;
			meanT = (currtime + ROItlists[i][j - 1]) / 2;
			mt->Add(meanT);
			mx->Add(meanx);
			my->Add(meany);
		}

		array<double>^ smx = gcnew array<double>(mt->Count);
		array<double>^ smy = gcnew array<double>(mt->Count);
		array<double>^ smt = gcnew array<double>(mt->Count);
		for (int j = 0; j < mt->Count; j++)
		{
			smx[j] = (double)mx[j];
			smy[j] = (double)my[j];
			smt[j] = (double)mt[j];
		}

		array<double>^ xdrift = JPMath::Interpolate1d(smt, smx, times, "akima", true);
		array<double>^ ydrift = JPMath::Interpolate1d(smt, smy, times, "akima", true);
		xdrift = JPMath::VectorSubScalar(xdrift, JPMath::Mean(xdrift, true), true);
		ydrift = JPMath::VectorSubScalar(ydrift, JPMath::Mean(ydrift, true), true);

		#pragma omp parallel for
		for (int j = 0; j < xdrift->Length; j++)
		{
			drift[1, j] += xdrift[j];
			drift[2, j] += ydrift[j];
		}
	}
	#pragma omp parallel for
	for (int i = 0; i < times->Length; i++)
	{
		drift[0, i] = times[i];
		drift[1, i] /= double(MARKCOORDS->GetLength(1));
		drift[2, i] /= double(MARKCOORDS->GetLength(1));
	}
	
	if (MARKCOORDS->GetLength(1) > 1 && !final_determination)//then auto run through
	{
		double meanMAX = 0;
		//apply drift to each kernel and get the radial plot fit
		for (int i = 0; i < MARKCOORDS->GetLength(1); i++)
		{
			for (int j = 0; j < ROIxcents[i]->Length; j++)
			{
				ROIxcents[i][j] = ((ints[0, ROIindexes[i][j]] - rx132ox32 + fracs[0, ROIindexes[i][j]] + 16 - drift[1, ROIindexes[i][j]] - (double)XSTARTS[i] / precB32) * precB32);
				ROIycents[i][j] = ((ints[1, ROIindexes[i][j]] - ry132oy32 + fracs[1, ROIindexes[i][j]] + 16 - drift[2, ROIindexes[i][j]] - (double)YSTARTS[i] / precB32) * precB32);
			}
			array<double, 2>^ kernel = gcnew array<double, 2>(XENDS[i] - XSTARTS[i] + 1, YENDS[i] - YSTARTS[i] + 1);
			for (int j = 0; j < ROIxcents[i]->Length; j++)
				if (ROIxcents[i][j] >= 0 && ROIxcents[i][j] <= kernel->GetLength(0) && ROIycents[i][j] >= 0 && ROIycents[i][j] <= kernel->GetLength(1))
					kernel[int(ROIxcents[i][j]), int(ROIycents[i][j])] += (1 / ROIflats[i][j]);

			int maxx, maxy;
			meanMAX += JPMath::Max(kernel, maxx, maxy, false);
		}
		meanMAX /= (double)MARKCOORDS->GetLength(1);
		meanMAXarray[index] = meanMAX;
		if (!endanalysis)
			goto goagaion;//do the next stack time
	}
	if (MARKCOORDS->GetLength(1) > 1 && endanalysis && !final_determination)
	{
		/*JPPlot^ plot = gcnew JPPlot();
		plot->plotchart1->PlotXYData(stakMAXarray, meanMAXarray, "test", "test", "test", ::DataVisualization::Charting::SeriesChartType::Point, "test");
		plot->ShowDialog();*/
		int minind = -1;
		JPMath::Max(meanMAXarray, minind, false);
		PointSrcROIStackDriftDrop->SelectedIndex = minind;
		final_determination = true;
		goto goagaion;//solve with the best stack
	}

	String^ driftslistfile;
	driftslistfile = intsname->Replace("XYInts_List", "XYDrift_List" + "_" + "PSTrk" + PointSrcROIStackDriftDrop->SelectedItem);
	driftslistfile = driftslistfile->Replace(".fits", ".drift");

	//get pre-existing earlier iteration dedrifted lists and drift series and delete them
	//this is to keep things cleaner like for creating exposure array from multiple drifts if a drift series is re-calculated from an earlier iteration
	//if redoing an earlier iteration its probably because the later ones were no good anyway
	dedrift = "_deDrift";
	while (intsname->Contains(dedrift))
		dedrift += "_deDrift";
	array<String^>^ delfiles = ::Directory::GetFiles(intsname->Substring(0, intsname->LastIndexOf("\\")), "*" + dedrift + "*");
	for (int i = 0; i < delfiles->Length; i++)
		::File::Delete(delfiles[i]);
	dedrift = dedrift->Remove(0, 8);
	delfiles = ::Directory::GetFiles(intsname->Substring(0, intsname->LastIndexOf("\\")), "*" + dedrift + ".drift");
	for (int i = 0; i < delfiles->Length; i++)
		::File::Delete(delfiles[i]);

	FITSImage^ driftfits = gcnew FITSImage(driftslistfile, drift, false, true);
	driftfits->CopyHeader(IntsFits);
	driftfits->AddKey("PSDSTAKT", PointSrcROIStackDriftDrop->SelectedItem->ToString(), "Point Source Drift Stack Time", 14);
	driftfits->WriteImage(::TypeCode::Double, true);
	UVPLOTDRIFTFILENAME = driftslistfile;
	UVAPPLYDRIFTCENTROIDSFILENAME = intsname;
}

void Form1::DriftFromPCPSTrackBGWrkr_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
{
	WAITBAR->TextMsg->Text = "Determining optimum PSF: Analyzing " + Convert::ToDouble(PointSrcROIStackDriftDrop->Items[e->ProgressPercentage]) + "s stack (" + (e->ProgressPercentage + 1) + " of " + PointSrcROIStackDriftDrop->Items->Count + ")";
	WAITBAR->Refresh();
}

void Form1::DriftFromPCPSTrackBGWrkr_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
{
	if (WAITBAR->DialogResult != ::DialogResult::Cancel)
	{
		/*MARKCOORDS = nullptr;
		MARKCOORDRECTS = nullptr;
		ImageWindow->Refresh();
		SubImageWindow->Refresh();*/

		WAITBAR->Text = "Applying...";
		WAITBAR->TextMsg->Text = "Applying drift to centroid list...";
		WAITBAR->CancelBtn->Enabled = false;
		WAITBAR->Refresh();
		UVAPPLYDRIFTNOW = true;
		PCModeDriftSelfCorrectionMenuItem->PerformClick();
	}
	else
	{
		Form1::Enabled = true;
		Form1::BringToFront();

		DRIFTFROMPCPSTRACK = false;
		UVDRIFTBATCH = false;
		UVDRIFTAUTORUN = false;
		UVCONVERTLISTTOIMAGEBATCH = false;
		UVAutoApplyDriftandImageChck->Checked = false;
		UVAutoDriftImageViewChck->Checked = false;
		UVDRIFTBATCHFILESINDEX = -1;
		AUTOLOADIMAGESFILES = nullptr;
		UVDRIFTBATCHFILES = nullptr;
	}
}

void Form1::DriftFromListTimeTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "DriftFromListTimeTxt", DriftFromListTimeTxt->Text);
}

void Form1::DriftFromListEndTimeTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "DriftFromListEndTimeTxt", DriftFromListEndTimeTxt->Text);
}

void Form1::CreateDriftFromPCMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	DriftFromListTimeTxt->Text = (String^)GetReg("CCDLAB", "DriftFromListTimeTxt");
	DriftFromListEndTimeTxt->Text = (String^)GetReg("CCDLAB", "DriftFromListEndTimeTxt");
	DriftStackTimeDrop->SelectedIndex = ::Convert::ToInt32(GetReg("CCDLAB", "DriftStackTimeDrop_index"));
	String^ time = (String^)DriftStackTimeDrop->Items[DriftStackTimeDrop->SelectedIndex];
	time = time->Replace(" second stacks", "");
	UVDRIFTSTACKTIME = ::Convert::ToDouble(time);
}

void Form1::DriftFromPCInterpolateChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "PCDriftInterpChck",DriftFromPCInterpolateChck->Checked);

	if (DriftFromPCInterpolateChck->Checked)
		DriftSmoothNDrop->Enabled = true;
	else
		DriftSmoothNDrop->Enabled = false;

	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromPCMenuItem->ShowDropDown();
}

void Form1::DriftStackTimeDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ time = (String^)DriftStackTimeDrop->SelectedItem;
	time = time->Replace(" second stacks","");
	UVDRIFTSTACKTIME = ::Convert::ToDouble(time);
	SetReg("CCDLAB", "DriftStackTimeDrop_index", DriftStackTimeDrop->SelectedIndex);
}

void Form1::DriftSmoothNDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "DriftSmoothNDrop_index", DriftSmoothNDrop->SelectedIndex);
}

void Form1::PointSrcROIStackDriftDrop_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	SetReg("CCDLAB", "PointSrcROIStackDriftDrop_index", PointSrcROIStackDriftDrop->SelectedIndex);
}

void Form1::PointSrcROIFindNSrcDrop_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	SetReg("CCDLAB", "PointSrcROIFindNSrcDrop_index", PointSrcROIFindNSrcDrop->SelectedIndex);
}

void Form1::CreateDriftFromPCMenuItem_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	unsigned __int32 starttime = 0;
	String^ startstring = DriftFromListTimeTxt->Text;
	try
	{
		starttime = ::Convert::ToUInt32(startstring);
	}
	catch (...)
	{
		if (startstring->Length == 0)
			starttime = 0;
		else
		{
			::MessageBox::Show("Something wrong with the start time: '" + startstring + "'", "Error...");
			return;
		}
	}

	unsigned __int32 endtime = ::UInt32::MaxValue;
	String^ endstring = DriftFromListEndTimeTxt->Text;
	try
	{
		endtime = ::Convert::ToUInt32(endstring);
	}
	catch (...)
	{
		if (endstring->Length == 0)
			endtime = ::UInt32::MaxValue;
		else
		{
			::MessageBox::Show("Something wrong with the start time: '" + endstring + "'", "Error...");
			return;
		}
	}
	if (endtime < starttime)
	{
		::MessageBox::Show("End time can't be less than start time...", "Error...");
		return;
	}

	UVITMenu->HideDropDown();
	CreateDriftListMenuItem->HideDropDown();
	CreateDriftFromPCMenuItem->HideDropDown();

	OpenFileDialog^ dlg;
	String^ dir;
	String^ intslistfile;

	if (!UVDRIFTBATCH)
	{
		dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		dlg = gcnew OpenFileDialog();
		dlg->InitialDirectory = dir;
		dlg->Filter = "FITS (*.fits)|*.fits";
		dlg->Multiselect = true;
		dlg->Title = "Select the Centroid INTEGERS List(s) (_XYInts_List)";
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;

		intslistfile = dlg->FileNames[0];
		dir = intslistfile->Substring(0,intslistfile->LastIndexOf("\\"));

		UVDRIFTAUTORUN = UVAutoApplyDriftandImageChck->Checked;

		if (dlg->FileNames->Length > 1)//batch, use higher level directory for L1 path
		{
			if (starttime != 0 || endtime != ::UInt32::MaxValue)
			{
				UVITMenu->ShowDropDown();
				CreateDriftListMenuItem->ShowDropDown();
				CreateDriftFromPCMenuItem->ShowDropDown();
				::MessageBox::Show("Doesn't make sense to specify Start and/or End time if doing a batch of files.  I'm going to stop.","Error...");
				return;
			}
			dir = dir->Substring(0,dir->LastIndexOf("\\"));
			UVDRIFTBATCH = true;
			UVDRIFTAUTORUN = true;
			UVCONVERTLISTTOIMAGEBATCH = false;
			UVAutoApplyDriftandImageChck->Checked = true;
			UVAutoDriftImageViewChck->Checked = false;
			UVDRIFTBATCHFILES = dlg->FileNames;
			UVDRIFTBATCHFILESINDEX = 0;
			AUTOLOADIMAGESFILES = gcnew array<String^>(dlg->FileNames->Length);
		}
		SetReg("CCDLAB", "L2EventListPath", dir);
	}
	else
	{
		intslistfile = UVDRIFTBATCHFILES[UVDRIFTBATCHFILESINDEX];
	}

	//ok so now send the filenames and dir to the worker arg, load the fits files and arrays there
	array<Object^>^ arg = gcnew array<Object^>(3);
	arg[0] = (Object^)intslistfile;
	arg[1] = (Object^)starttime;
	arg[2] = (Object^)endtime;

	if (UVDRIFTBATCH)
	{
		if (UVDRIFTBATCHFILESINDEX == 0)
		{
			DATE = ::DateTime::Now;
			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = 100;
			WAITBAR->Text = "File " + (UVDRIFTBATCHFILESINDEX+1).ToString() + " of " + UVDRIFTBATCHFILES->Length + ". Calculating drift...";
			DriftFromPCListWrkr->RunWorkerAsync(arg);
			WAITBAR->ShowDialog();
		}
		else
		{
			WAITBAR->Text = "File " + (UVDRIFTBATCHFILESINDEX+1).ToString() + " of " + UVDRIFTBATCHFILES->Length + ". Calculating drift...";
			DriftFromPCListWrkr->RunWorkerAsync(arg);
		}
	}
	else
	{
		Form1::Enabled = false;
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = 100;
		WAITBAR->Text = "File 1 of 1. Calculating drift...";
		DriftFromPCListWrkr->RunWorkerAsync(arg);
		WAITBAR->ShowDialog();
	}
}

void Form1::DriftFromPCListWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<Object^>^ arg = (array<Object^>^)e->Argument;
	String^ intslistfile = (String^)arg[0];
	unsigned __int32 starttime = (unsigned __int32)arg[1];
	unsigned __int32 endtime = (unsigned __int32)arg[2];

	FITSImage^ intslist = gcnew JPFITS::FITSImage(intslistfile, nullptr, true, false, false, false);
	array<double,2>^ ints = FITSImage::ReadImageArrayOnly(intslistfile, nullptr, true);

	String^ fraclistfile = intslistfile->Replace("Ints","Frac");
	array<double,2>^ frac = FITSImage::ReadImageArrayOnly(fraclistfile, nullptr, true);
	ints = JPMath::MatrixAddMatrix(ints, frac, true);
	ints = JPMath::MatrixAddScalar(ints, 16, true);

	String^ timeslistfile = intslistfile->Remove(intslistfile->IndexOf("XYInts_List")) + "TimeList.fits";
	String^ deDrift = "_deDrift";
	while (intslistfile->Contains(deDrift))
	{
		timeslistfile = timeslistfile->Replace("TimeList","TimeList_deDrift");
		deDrift += "_deDrift";
	}
	if (!::IO::File::Exists(timeslistfile))
	{
		::MessageBox::Show("Error finding the TimeList file...stopping.","Error");
		return;
	}
	FITSImage^ timeslist = gcnew FITSImage(timeslistfile, nullptr, true, false, false, false);
	array<double>^ times = FITSImage::ReadImageVectorOnly(timeslistfile, nullptr, true);

	if (starttime == 0)
	{
		starttime = (unsigned __int32)times[0];
		//auto-skip initial frame with 1000's counts & outside taper active-region
		int ffi = JPMath::Find(times, times[0], ">", true);
		if (ffi > 1000)
			starttime = (unsigned __int32)times[ffi];
	}
	if (endtime == ::UInt32::MaxValue)
		endtime = (unsigned __int32)times[times->Length-1];

	int imageprec, padoffset;
	if (DriftPCROIOnly->Checked)
	{
		if (IMAGESET == nullptr || IMAGESET->Count == 0)
			DriftPCROIOnly->Checked = false;
		else
		{
			String^ prec = IMAGESET[Form1::FILELISTINDEX]->GetKeyValue("IMAGPREC");
			String^ offs = IMAGESET[Form1::FILELISTINDEX]->GetKeyValue("PADOFSET");

			if (prec == "" || offs == "")
				DriftPCROIOnly->Checked = false;
			else
			{
				imageprec = Convert::ToInt32(prec);
				padoffset = Convert::ToInt32(offs);
			}
		}
	}

	String^ xoffset = intslist->GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
	if (xoffset == "")
		xoffset = intslist->GetKeyValue("WIN_XOFF");//from L1 data
	if (xoffset == "")
	{
		::MessageBox::Show("Can't find the image x-offset...stopping.","Error");
		return;
	}
	double ox = ::Convert::ToDouble(xoffset);//x offset
	if (DriftPCROIOnly->Checked)
		ox = (XSUBRANGE[0] - padoffset * imageprec) / imageprec;

	String^ yoffset = intslist->GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
	if (yoffset == "")
		yoffset = intslist->GetKeyValue("WIN_YOFF");//from L1 data
	if (yoffset == "")
	{
		::MessageBox::Show("Can't find the image y-offset...stopping.","Error");
		return;
	}
	double oy = ::Convert::ToDouble(yoffset);//y offset
	if (DriftPCROIOnly->Checked)
		oy = (YSUBRANGE[0] - padoffset * imageprec) / imageprec;

	String^ sizex = intslist->GetKeyValue("XSIZE");
	if (sizex == "")
		sizex = intslist->GetKeyValue("WIN_X_SZ");
	if (sizex == "")
	{
		::MessageBox::Show("Can't find the image x-size...stopping.","Error");
		return;
	}
	int szx = ::Convert::ToInt32(sizex);//x size
	if (DriftPCROIOnly->Checked)
		szx = (XSUBRANGE[XSUBRANGE->Length - 1] - XSUBRANGE[0]) / imageprec;

	String^ sizey = intslist->GetKeyValue("YSIZE");
	if (sizey == "")
		sizey = intslist->GetKeyValue("WIN_Y_SZ");
	if (sizey == "")
	{
		::MessageBox::Show("Can't find the image y-size...stopping.","Error");
		return;
	}
	int szy = ::Convert::ToInt32(sizey);//y size
	if (DriftPCROIOnly->Checked)
		szy = (YSUBRANGE[YSUBRANGE->Length - 1] - YSUBRANGE[0]) / imageprec;

	int prec = 1;
	szx = (szx + 1)*prec;
	szy = (szy + 1)*prec;

	unsigned __int32 dt = (unsigned __int32)(UVDRIFTSTACKTIME * 1000);
	int Ndrifttimes = int((endtime - starttime) / dt);
	endtime = starttime + (unsigned __int32)Ndrifttimes * dt;
	array<double>^ tdr = gcnew array<double>(Ndrifttimes);
	array<double>^ xdr = gcnew array<double>(Ndrifttimes);
	array<double>^ ydr = gcnew array<double>(Ndrifttimes);	
	array<int>^ stackinds = gcnew array<int>(Ndrifttimes + 1);
	stackinds[0] = JPMath::Find(times, starttime, "==", true);
	for (int i = 1; i <= Ndrifttimes; i++)
		for (int j = stackinds[i - 1]; j < times->Length; j++)
			if (times[j] > times[stackinds[0]] + double(dt)*double(i))
			{
				stackinds[i] = j;
				break;
			}

	array<double, 2>^ REFimg = gcnew array<double, 2>(szx, szy);
	for (int i = stackinds[0]; i < stackinds[1]; i++)
	{
		int xpos = (int)((ints[0, i] - ox * 32) / 32);
		int ypos = (int)((ints[1, i] - oy * 32) / 32);

		if (xpos >= 0 && ypos >= 0 && xpos < szx && ypos < szy)
			REFimg[xpos, ypos]++;
	}
	for (int x = 0; x < szx; x++)
		for (int y = 0; y < szy; y++)
			if (REFimg[x, y] == 1)
				REFimg[x, y] = 0;//remove noise
	REFimg = JPMath::Hanning(REFimg, true);
	array<double>^ REFimgvecX = JPMath::Sum(REFimg, 1, true);
	array<double>^ REFimgvecY = JPMath::Sum(REFimg, 0, true);
	tdr[0] = double(starttime) + UVDRIFTSTACKTIME * 1000 / 2;//xdr, ydr = 0

	int prog = 0;

	#pragma omp parallel for
	for (int i = 1; i < Ndrifttimes; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			continue;

		if (i < Ndrifttimes / omp_get_num_threads())
			if (omp_get_num_threads() * 100 * i / Ndrifttimes > prog)
			{
				prog = omp_get_num_threads() * 100 * i / Ndrifttimes;
				DriftFromPCListWrkr->ReportProgress(prog);
			}

		array<double, 2>^ COMimg = gcnew array<double, 2>(szx, szy);
		for (int j = stackinds[i]; j < stackinds[i + 1]; j++)
		{
			int xpos = (int)((ints[0, j] - ox * 32) / 32);
			int ypos = (int)((ints[1, j] - oy * 32) / 32);

			if (xpos >= 0 && ypos >= 0 && xpos < szx && ypos < szy)
				COMimg[xpos, ypos]++;
		}
		for (int x = 0; x < szx; x++)
			for (int y = 0; y < szy; y++)
				if (COMimg[x, y] == 1)
					COMimg[x, y] = 0;//remove noise
		COMimg = JPMath::Hanning(COMimg, false);

		double xshift, yshift;
		JPMath::XCorrImageLagShifts(REFimgvecX, REFimgvecY, COMimg, false, false, false, xshift, yshift, false);

		tdr[i] = times[stackinds[i]] + double(UVDRIFTSTACKTIME * 1000) / 2;
		xdr[i] = xshift * 32;
		ydr[i] = yshift * 32;
	}

	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
		return;

	//correct strange large spikes???.......PC mode here
	for (int i = 2; i < tdr->Length; i++)
	{
		double dxdt = (xdr[i] - xdr[i - 1]) / UVDRIFTSTACKTIME / 32;//pixels per second
		if (Math::Abs(dxdt) > 5)
		{
			dxdt = (xdr[i - 1] - xdr[i - 2]) / UVDRIFTSTACKTIME;
			xdr[i] = xdr[i - 1] + dxdt * (tdr[i] - tdr[i - 1]) / 1000;
		}
		double dydt = (ydr[i] - ydr[i - 1]) / UVDRIFTSTACKTIME / 32;//pixels per second
		if (Math::Abs(dydt) > 5)
		{
			dydt = (ydr[i - 1] - ydr[i - 2]) / UVDRIFTSTACKTIME;
			ydr[i] = ydr[i - 1] + dydt * (tdr[i] - tdr[i - 1]) / 1000;
		}
	}
	//done correction

	xdr = JPMath::VectorSubScalar(xdr, JPMath::Mean(xdr, true), true);
	ydr = JPMath::VectorSubScalar(ydr, JPMath::Mean(ydr, true), true);
	bool smooth = DriftFromPCInterpolateChck->Checked;
	int interpN;
	if (smooth)
	{
		interpN = DriftSmoothNDrop->SelectedIndex;
		if (interpN < 0)
			interpN = 3;
		else
			interpN = 3 + interpN * 2;

		xdr = JPMath::Smooth(xdr, interpN, true);
		ydr = JPMath::Smooth(ydr, interpN, true);
	}

	array<double>^ tdrinterp = gcnew array<double>(stackinds[stackinds->Length - 1] - stackinds[0] + 1);
	array<double>^ xdrinterp = gcnew array<double>(stackinds[stackinds->Length - 1] - stackinds[0] + 1);
	array<double>^ ydrinterp = gcnew array<double>(stackinds[stackinds->Length - 1] - stackinds[0] + 1);
	#pragma omp parallel for
	for (int i = 0; i < tdrinterp->Length; i++)
		tdrinterp[i] = times[stackinds[0] + i];
	xdrinterp = JPMath::Interpolate1d(tdr, xdr, tdrinterp, "mono", true);
	ydrinterp = JPMath::Interpolate1d(tdr, ydr, tdrinterp, "mono", true);

	array<double, 2>^ xyshiftsLIST = gcnew array<double, 2>(3, tdrinterp->Length);
	#pragma omp parallel for
	for (int i = 0; i < tdrinterp->Length; i++)
	{
		xyshiftsLIST[0, i] = tdrinterp[i];
		xyshiftsLIST[1, i] = Math::Round(xdrinterp[i]);
		xyshiftsLIST[2, i] = Math::Round(ydrinterp[i]);
	}

	String^ driftslistfile;
	if (smooth)
		driftslistfile = intslistfile->Replace("XYInts_List", "XYDrift_List" + "_" + UVDRIFTSTACKTIME.ToString() + "s" + "_Sm" + interpN.ToString());
	else
		driftslistfile = intslistfile->Replace("XYInts_List", "XYDrift_List" + "_" + UVDRIFTSTACKTIME.ToString() + "s");
	driftslistfile = driftslistfile->Replace(".fits", ".drift");

	//get pre-existing earlier iteration dedrifted lists and drift series and delete them
	//this is to keep things cleaner like for creating exposure array from multiple drifts if a drift series is re-calculated from an earlier iteration
	//if redoing an earlier iteration its probably because the later ones were no good anyway
	String^ dedrift = "_deDrift";
	while (intslistfile->Contains(dedrift))
		dedrift += "_deDrift";
	array<String^>^ delfiles = ::Directory::GetFiles(intslistfile->Substring(0, intslistfile->LastIndexOf("\\")), "*" + dedrift + "*");
	for (int i = 0; i < delfiles->Length; i++)
		::File::Delete(delfiles[i]);
	dedrift = dedrift->Remove(0, 8);
	delfiles = ::Directory::GetFiles(intslistfile->Substring(0, intslistfile->LastIndexOf("\\")), "*" + dedrift + ".drift");
	for (int i = 0; i < delfiles->Length; i++)
		::File::Delete(delfiles[i]);

	FITSImage^ driftfits = gcnew FITSImage(driftslistfile, xyshiftsLIST, false, true);
	driftfits->CopyHeader(timeslist);
	driftfits->WriteImage(::TypeCode::Double, true);
	UVPLOTDRIFTFILENAME = driftslistfile;
	UVAPPLYDRIFTCENTROIDSFILENAME = intslistfile;

	/*FITSImage^ ff = gcnew FITSImage(driftslistfile + "test");
	ff->CopyHeader(timeslist);
	ff->WriteImage(TypeCode::Int16);
	array<String^>^ labels = gcnew array<String^>(3) {"Time", "XDrift", "YDrift"};
	array<TypeCode>^ types = gcnew array<TypeCode>(3) {TypeCode::UInt32, TypeCode::Int16, TypeCode::Int16};
	array<int>^ instances = gcnew array<int>(3) { 1, 1, 1 };
	array<String^>^ units = gcnew array<String^>(3) { "Milliseconds", "1/32 pixel", "1/32 pixel" };
	JPFITS::FITSImage::WriteBinaryTableExtension(driftslistfile + "test", "DriftList", true, labels, types, instances, units, nullptr, nullptr, nullptr, xyshiftsLIST);*/
	/*try
	{
		array<double, 2>^ test = JPFITS::FITSImage::ReadBinaryTableExtensionEntries(driftslistfile + "test", "DriftList", gcnew array<String^>(3) { "Time", "XDrift", "YDrift" });
		for (int i = 0; i < test->GetLength(1); i++)
			MessageBox::Show(test[0, i] + " " + test[1, i] + " " + test[2, i]);
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}*/
}

void Form1::DriftFromPCListWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat("Completed: ",e->ProgressPercentage,"%");
	WAITBAR->Refresh();
}

void Form1::DriftFromPCListWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult != ::DialogResult::Cancel)
	{
		if (!UVDRIFTAUTORUN)
		{
			::DialogResult res = ::MessageBox::Show("Completed making the drift correction list.  Would you like to plot it?","Finished...",::MessageBoxButtons::OKCancel);
			if (res == ::DialogResult::Cancel)
			{
				WAITBAR->Hide();
				WAITBAR->Close();
				Form1::Enabled = true;
				Form1::BringToFront();
				return;
			}
			if (res == ::DialogResult::OK)
			{
				UVPLOTDRIFTLISTNOW = true;
				PlotDriftListMenuItem->PerformClick();
			}
			res = ::MessageBox::Show("Would you like to apply this drift calculation to the centroid list?","Apply drift...",::MessageBoxButtons::OKCancel);
			if (res == ::DialogResult::Cancel)
			{
				WAITBAR->Hide();
				WAITBAR->Close();
				Form1::Enabled = true;
				Form1::BringToFront();
				return;
			}
			if (res == ::DialogResult::OK)
			{
				XDRIFT_PLOT->Close();
				YDRIFT_PLOT->Close();
				UVAPPLYDRIFTNOW = true;
				PCModeDriftSelfCorrectionMenuItem->PerformClick();//is ApplyDriftListMentuItem_Click
			}
		}
		else
		{
			WAITBAR->Text = "Applying...";
			WAITBAR->TextMsg->Text = "Applying drift to centroid list...";
			WAITBAR->CancelBtn->Enabled = false;
			WAITBAR->Refresh();
			UVAPPLYDRIFTNOW = true;
			PCModeDriftSelfCorrectionMenuItem->PerformClick();//is ApplyDriftListMentuItem_Click 
		}
	}
	else
	{
		UVAPPLYDRIFTNOW = false;
		UVDRIFTBATCH = false;
		WAITBAR->Hide();
		WAITBAR->Close();
		Form1::Enabled = true;
		Form1::BringToFront();
	}
}

void Form1::ApplyDriftListMentuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ driftlistfile;

	OpenFileDialog^ dlg;
	if (UVAPPLYDRIFTNOW)
	{
		//UVAPPLYDRIFTNOW = false;//done below in worker
		driftlistfile = UVPLOTDRIFTFILENAME;
		WAITBAR->ProgressBar->Value = 100;
		WAITBAR->Refresh();
		ApplyDriftListWrkr->RunWorkerAsync(driftlistfile);
	}
	else
	{
		UVAPPLYDRIFTNOW = false;
		String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		dlg = gcnew OpenFileDialog();
		dlg->InitialDirectory = dir;
		dlg->Filter = "FITS (*.fits)|*.fits";
		dlg->Multiselect = false;

		dlg->Title = "Select the DRIFT List (_XYDrift_List)";
		dlg->Filter = "DRIFT (*.drift)|*.drift";
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		driftlistfile = dlg->FileName;
		dir = driftlistfile->Substring(0,driftlistfile->LastIndexOf("\\"));
		SetReg("CCDLAB", "L2EventListPath", dir);

		dlg = gcnew OpenFileDialog();
		dlg->Title = "Select the Centroid INTEGERS List (_XYInts_List)";
		dlg->Filter = "FITS (*.fits)|*.fits";
		dlg->InitialDirectory = dir;
		dlg->Multiselect = false;
		res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		UVAPPLYDRIFTCENTROIDSFILENAME = dlg->FileName;

		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->Text = "Applying Drift";
		WAITBAR->TextMsg->Text = "Please wait...";
		WAITBAR->CancelBtn->Enabled = false;
		ApplyDriftListWrkr->RunWorkerAsync(driftlistfile);
		WAITBAR->ShowDialog();
	}
}

void Form1::ApplyDriftListWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	try
	{
		if (UVAPPLYDRIFTNOW)
			UVAPPLYDRIFTNOW = false;

		String^ driftlistfile = (String^)e->Argument;

		FITSImage^ driftsfits = gcnew JPFITS::FITSImage(driftlistfile, nullptr, true, false, false, false);
		array<double, 2>^ drifts = FITSImage::ReadImageArrayOnly(driftlistfile, nullptr, true);

		String^ timelistfile = driftlistfile->Remove(driftlistfile->IndexOf("XYDrift")) + "TimeList.fits";
		String^ deDrift = "_deDrift";
		while (driftlistfile->Contains(deDrift))
		{
			timelistfile = timelistfile->Replace("TimeList", "TimeList_deDrift");
			deDrift += "_deDrift";
		}

		if (!::IO::File::Exists(timelistfile))
		{
			::MessageBox::Show("Time List not found.  Error & exiting...");
			WAITBAR->CancelBtn->PerformClick();
			return;
		}
		array<double>^ times = FITSImage::ReadImageVectorOnly(timelistfile, nullptr, true);

		String^ framelistfile = timelistfile->Replace("Time", "Frame");
		if (!::File::Exists(framelistfile))
		{
			::MessageBox::Show("Frame List not found.  Error & exiting...");
			WAITBAR->CancelBtn->PerformClick();
			return;
		}
		array<double>^ frames = FITSImage::ReadImageVectorOnly(framelistfile, nullptr, true);

		String^ flatlistfile = timelistfile->Replace("Time", "Flat");
		if (!::File::Exists(flatlistfile))
		{
			::MessageBox::Show("Flat Field List not found.  Error & exiting...");
			WAITBAR->CancelBtn->PerformClick();
			return;
		}
		array<double>^ flats = FITSImage::ReadImageVectorOnly(flatlistfile, nullptr, true);

		String^ mdMmlistfile = timelistfile->Replace("TimeList", "XYmdMm_List");
		if (!::File::Exists(mdMmlistfile))
		{
			::MessageBox::Show("Max Min Corners List not found.  Error & exiting...");
			WAITBAR->CancelBtn->PerformClick();
			return;
		}
		array<double, 2>^ mdMms = FITSImage::ReadImageArrayOnly(mdMmlistfile, nullptr, true);

		String^ BJDlistfile = timelistfile->Replace("TimeList", "BJDList");
		bool BJDexists = true;
		if (!::File::Exists(BJDlistfile))
		{
			BJDexists = false;
			/*::MessageBox::Show("BJDList Time List not found.  Error & exiting...");
			WAITBAR->CancelBtn->PerformClick();
			return;*/
		}
		array<double>^ BJDS;
		if (BJDexists)
			BJDS = FITSImage::ReadImageVectorOnly(BJDlistfile, nullptr, true);

		String^ intslistfile = UVAPPLYDRIFTCENTROIDSFILENAME;
		array<double, 2>^ ints = FITSImage::ReadImageArrayOnly(intslistfile, nullptr, true);

		String^ fraclistfile = intslistfile->Replace("Ints", "Frac");
		array<double, 2>^ frac = FITSImage::ReadImageArrayOnly(fraclistfile, nullptr, true);
		FITSImage^ fracfits = gcnew FITSImage(fraclistfile, nullptr, true, false, false, false);
		bool nuvTOfuv = false;
		if (fracfits->GetKeyValue("DETECTOR") == "NUV")
			if (fracfits->GetKeyIndex("NUVTOFUV") != -1)
				nuvTOfuv = true;

		//make exposure array
		bool createexposurearray = ApplyDriftCreateExpArrayChc->Checked;
		//when working on merged MASTER file {OR PREVIOUSLY DRIFTED FILE}, drift will be so small as to not change the exposure array,
		//so just update the existing merged expsoure array to be same dimension as the new dedrifted lists and name it as such.
		//So here, don't create a new expsoure list, just use the existing merged master one and clip it to match the other lists.
		bool master = intslistfile->Contains("MASTER") || intslistfile->Contains("deDrift");
		if (master)
			createexposurearray = false;

		int res = ExposureArrayResolutionDrop->SelectedIndex + 1;
		double dres = double(res);
		double pixres = 32 / dres;
		if (L1CentroidPaddingChck->Checked)
		{
			if (PCCentroidPaddingDrop->SelectedIndex == 0)
				UVPCMODEPADOFFSET = 22;
			if (PCCentroidPaddingDrop->SelectedIndex == 1)
				UVPCMODEPADOFFSET = 44;
		}
		else
			UVPCMODEPADOFFSET = 0;
		int offset = UVPCMODEPADOFFSET*res;

		int winxsz, szx, winysz, szy, ox, oy;
		try
		{
			winxsz = Convert::ToInt32(driftsfits->GetKeyValue("WIN_X_SZ"));
			szx = (winxsz + 1) * res + offset * 2;
			winysz = Convert::ToInt32(driftsfits->GetKeyValue("WIN_Y_SZ"));
			szy = (winysz + 1) * res + offset * 2;
			ox = Convert::ToInt32(driftsfits->GetKeyValue("WIN_XOFF"));
			oy = Convert::ToInt32(driftsfits->GetKeyValue("WIN_YOFF"));
		}
		catch (...)
		{
			winxsz = 511;
			szx = (winxsz + 1) * res + offset * 2;
			winysz = 511;
			szy = (winysz + 1) * res + offset * 2;
			ox = 0;
			oy = 0;
		}		

		double nframes = 0;
		array<double, 2>^ exposuremap;
		array<double, 2>^ exposuredrifts;
		array<double, 2>^ exposurearray;
		if (createexposurearray)
		{
			ApplyDriftListWrkr->ReportProgress(0);

			//need to check for existing exposure arrays and ...do what with them...
			//in order to create a final _dedrfit_dedrift_etc one...
			//what should be done, then, is to check for existing drift series
			//this assumes that all drift series in the directory are relevent to the current iteration

			//this assumption disrupts re-performing the dift series on an earlier iteration of corrected files from which you wish to start again
			//so you should only use the drift series that are from an earlier time than the current file time...

			//So, get the drift series in the directory, and sum them (xy, not time vector).  Create the exposure array from that.
			//However, that summed series is only for the exposure array, NOT for the current drift correction
			//The current drift correction is only for the current "drifts" series.
			//So, use a new drifts series, called Exparray drift or something...
			//The most recent drift series will be the shortest one

			//*********should also check the t0 index if the drifts dont start at same time???...*********

			exposurearray = gcnew array<double, 2>(szx, szy);

			exposuredrifts = gcnew array<double, 2>(driftsfits->Width, driftsfits->Height);
			array<double, 2>^ prevdrifts;
			//this gets all drifts *including current one, so should always be at least one for the j loop below
			array<String^>^ prevdriftslists = ::Directory::GetFiles(timelistfile->Substring(0, timelistfile->LastIndexOf("\\")), "*.drift");
			for (int j = 0; j < prevdriftslists->Length; j++)
			{
				prevdrifts = FITSImage::ReadImageArrayOnly(prevdriftslists[j], nullptr, true);

				#pragma omp parallel for
				for (int i = 0; i < driftsfits->Height; i++)
				{
					exposuredrifts[0, i] = prevdrifts[0, i];
					exposuredrifts[1, i] += prevdrifts[1, i];
					exposuredrifts[2, i] += prevdrifts[2, i];
				}
			}

			String^ detector = driftsfits->GetKeyValue("DETECTOR");
			String^ FUVexpmapfile;
			String^ NUVexpmapfile;
			if (res == 1)
			{
				FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map.fits";
				NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map.fits";
				if (nuvTOfuv)
					NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map_NUVtoFUV.fits";
			}
			if (res == 2)
			{
				FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map x2.fits";
				NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2.fits";
				if (nuvTOfuv)
					NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2_NUVtoFUV.fits";
			}
			if (detector == "FUV")
			{
				if (!File::Exists(FUVexpmapfile))
				{
					::MessageBox::Show("FUV Exposure Map not found in UVIT_CalDB at " + FUVexpmapfile + ".  Please update your Cal_DB from http://www.ucalgary.ca/uvit/.  Exiting.", "Error...");
					WAITBAR->CancelBtn->PerformClick();
					return;
				}
				if (winxsz == 511 && winysz == 511)
				{
					if (UVPCMODEPADOFFSET == 44)
						exposuremap = FITSImage::ReadImageArrayOnly(FUVexpmapfile, gcnew array<int>(4) { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
					if (UVPCMODEPADOFFSET == 22)
						exposuremap = FITSImage::ReadImageArrayOnly(FUVexpmapfile, gcnew array<int>(4) { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
					if (UVPCMODEPADOFFSET == 0)
						exposuremap = FITSImage::ReadImageArrayOnly(FUVexpmapfile, gcnew array<int>(4) { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
				}
				else
				{
					exposuremap = gcnew array<double, 2>(szx, szy);
					#pragma omp parallel for
					for (int x = UVPCMODEPADOFFSET*res; x < szx - UVPCMODEPADOFFSET*res; x++)
						for (int y = UVPCMODEPADOFFSET*res; y < szy - UVPCMODEPADOFFSET*res; y++)
							exposuremap[x, y] = 1;
				}
			}
			else if (detector == "NUV")
			{
				if (!File::Exists(NUVexpmapfile))
				{
					::MessageBox::Show("NUV Exposure Map not found in UVIT_CalDB at " + NUVexpmapfile + ".  Please update your Cal_DB from http://www.ucalgary.ca/uvit/.  Exiting.", "Error...");
					WAITBAR->CancelBtn->PerformClick();
					return;
				}
				if (winxsz == 511 && winysz == 511)
				{
					if (UVPCMODEPADOFFSET == 44)
						exposuremap = FITSImage::ReadImageArrayOnly(NUVexpmapfile, gcnew array<int>(4) { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
					if (UVPCMODEPADOFFSET == 22)
						exposuremap = FITSImage::ReadImageArrayOnly(NUVexpmapfile, gcnew array<int>(4) { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
					if (UVPCMODEPADOFFSET == 0)
						exposuremap = FITSImage::ReadImageArrayOnly(NUVexpmapfile, gcnew array<int>(4) { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
				}
				else
				{
					exposuremap = gcnew array<double, 2>(szx, szy);
					#pragma omp parallel for
					for (int x = UVPCMODEPADOFFSET*res; x < szx - UVPCMODEPADOFFSET*res; x++)
						for (int y = UVPCMODEPADOFFSET*res; y < szy - UVPCMODEPADOFFSET*res; y++)
							exposuremap[x, y] = 1;
				}
			}
			else
			{
				::MessageBox::Show("Problem determining the correct Exposure Map for the exposure array...", "Error...");
				WAITBAR->CancelBtn->PerformClick();
				return;
			}

			int xstart, xend, ystart, yend, expxstart, expystart;
			exposuredrifts[1, 0] *= -1;
			exposuredrifts[2, 0] *= -1;
			double oldxdrift = exposuredrifts[1, 0];
			double oldydrift = exposuredrifts[2, 0];
			if (exposuredrifts[1, 0] < 0)
			{
				xstart = -int(exposuredrifts[1, 0] / pixres);
				xend = szx;
				expxstart = 0;
			}
			else
			{
				xstart = 0;
				xend = szx - int(exposuredrifts[1, 0] / pixres);
				expxstart = int(exposuredrifts[1, 0] / pixres);
			}
			if (exposuredrifts[2, 0] < 0)
			{
				ystart = -int(exposuredrifts[2, 0] / pixres);
				yend = szy;
				expystart = 0;
			}
			else
			{
				ystart = 0;
				yend = szy - int(exposuredrifts[2, 0] / pixres);
				expystart = int(exposuredrifts[2, 0] / pixres);
			}
			exposuredrifts[1, 0] *= -1;
			exposuredrifts[2, 0] *= -1;

			int intprog = 0;
			double increment = 0;
			double time = -1;
			for (int i = 0; i < driftsfits->Height; i++)
			{
				if (time != exposuredrifts[0, i])//new drift frame time...possibly new drift...also very first frame
				{
					if (100 * i / driftsfits->Height > intprog)
					{
						intprog += 1;
						ApplyDriftListWrkr->ReportProgress(0, intprog);
					}

					time = exposuredrifts[0, i];
					nframes++;

					exposuredrifts[1, i] *= -1;
					exposuredrifts[2, i] *= -1;

					//if it isnt moving then just gather the increments to apply after it does move
					//and it only needs to be applied after it moves by at least one pixel (or res?)
					if (Math::Abs(exposuredrifts[1, i] - oldxdrift) < pixres && Math::Abs(exposuredrifts[2, i] - oldydrift) < pixres)//will trigger for first frame so increment goes to 1 for it
					{
						increment++;//this starts at zero, so if this is the first frame, we get the first increment = 1
						exposuredrifts[1, i] *= -1;//reset
						exposuredrifts[2, i] *= -1;
						continue;
					}

					//then it has moved, so increment out everything from when it wasn't moving at the old positions
					#pragma omp parallel for
					for (int x = xstart; x < xend; x++)
						for (int y = ystart; y < yend; y++)
							if (exposuremap[x, y] == 1)
								exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;

					increment = 1;//increment for current frame

					//update moved position stuff...at least one of the drifts is moved 32 or more...update that one or both only
					if (Math::Abs(exposuredrifts[1, i] - oldxdrift) >= pixres)
					{
						oldxdrift = exposuredrifts[1, i];
						if (exposuredrifts[1, i] < 0)
						{
							xstart = -int(exposuredrifts[1, i] / pixres);
							xend = szx;
							expxstart = 0;
						}
						else
						{
							xstart = 0;
							xend = szx - int(exposuredrifts[1, i] / pixres);
							expxstart = int(exposuredrifts[1, i] / pixres);
						}
					}

					if (Math::Abs(exposuredrifts[2, i] - oldydrift) >= pixres)
					{
						oldydrift = exposuredrifts[2, i];
						if (exposuredrifts[2, i] < 0)
						{
							ystart = -int(exposuredrifts[2, i] / pixres);
							yend = szy;
							expystart = 0;
						}
						else
						{
							ystart = 0;
							yend = szy - int(exposuredrifts[2, i] / pixres);
							expystart = int(exposuredrifts[2, i] / pixres);
						}
					}

					exposuredrifts[1, i] *= -1;//reset
					exposuredrifts[2, i] *= -1;
				}
			}
			//increment out last gathered increments
			#pragma omp parallel for
			for (int x = xstart; x < xend; x++)
				for (int y = ystart; y < yend; y++)
					if (exposuremap[x, y] == 1)
						exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;

			//lastly normalize the array...
			exposurearray = JPMath::MatrixDivScalar(exposurearray, nframes, true);

			driftsfits->SetKey("EXMAPRES", res.ToString(), "Exposure Map Resolution", true, 15);
			driftsfits->SetKey("EXMAPTIM", (exposuredrifts[0, exposuredrifts->GetLength(1) - 1] - exposuredrifts[0, 0]).ToString(), "Exposure Map Time", true, 15);
		}

		ApplyDriftListWrkr->ReportProgress(1);

		//so now use the times from drifts to align on the time from times, and apply onto new ints array and save that array
		double t0 = drifts[0, 0];
		int t0index = JPMath::Find(times, t0, "==", true);

		//MessageBox::Show(t0.ToString() + "	" + t0index.ToString() + "   " + times[t0index].ToString());

		//will need dedrifted ints and fracs so they align...
		array<double, 2>^ dedriftedXYInts = gcnew array<double, 2>(2, driftsfits->Height);
		array<double, 2>^ dedriftedXYFrac = gcnew array<double, 2>(2, driftsfits->Height);
		array<double>^ dedriftedFlat = gcnew array<double>(driftsfits->Height);
		array<double>^ dedriftedTime = gcnew array<double>(driftsfits->Height);
		array<double>^ dedriftedFrame = gcnew array<double>(driftsfits->Height);
		array<double, 2>^ dedriftedXYmdMm = gcnew array<double, 2>(2, driftsfits->Height);
		array<double>^ dedriftedBJD;
		if (BJDexists) 
			dedriftedBJD = gcnew array<double>(driftsfits->Height);
		array<double>^   dedriftedExposure;
		if (createexposurearray)
			dedriftedExposure = gcnew array<double>(driftsfits->Height);
		if (master)
			dedriftedExposure = ::FITSImage::ReadImageVectorOnly(timelistfile->Replace("TimeList", "ExpArrayList"), gcnew array<int>(4) { 0, 0, 0, driftsfits->Height - 1 }, true);

		int counter1 = 0;
		#pragma omp parallel for
		for (int i = 0; i < driftsfits->Height; i++)
		{
			dedriftedXYInts[0, i] = ints[0, t0index + i] - drifts[1, i];
			dedriftedXYInts[1, i] = ints[1, t0index + i] - drifts[2, i];

			dedriftedXYFrac[0, i] = frac[0, t0index + i];
			dedriftedXYFrac[1, i] = frac[1, t0index + i];

			dedriftedFlat[i] = flats[t0index + i];
			dedriftedTime[i] = times[t0index + i];
			dedriftedFrame[i] = frames[t0index + i];

			dedriftedXYmdMm[0, i] = mdMms[0, t0index + i];
			dedriftedXYmdMm[1, i] = mdMms[1, t0index + i];

			if (BJDexists)
				dedriftedBJD[i] = BJDS[t0index + i];

			if (createexposurearray)
			{
				int xpos = (int)(dedriftedXYInts[0, i] / pixres) + offset - ox * res;
				int ypos = (int)(dedriftedXYInts[1, i] / pixres) + offset - oy * res;
				if (xpos < 0 || ypos < 0 || xpos >= szx || ypos >= szy)
					dedriftedExposure[i] = 0;
				else
					dedriftedExposure[i] = exposurearray[xpos, ypos];//applied like the flat...take the inverse at image creation time
			}
		}

		ApplyDriftListWrkr->ReportProgress(2);

		//then save the dedrifted lists
		if (BJDexists)
			driftsfits->SetKey("BJD0", dedriftedBJD[0].ToString("#.0000000"), "BJD of start of imaging", true, 14);//now it will get added to all other copyheaders's

		int ind = intslistfile->LastIndexOf("_deDrift");
		if (ind == -1)
			ind = intslistfile->LastIndexOf(".");
		String^ dedriftedXYIntsFile = intslistfile->Insert(ind, "_deDrift");
		FITSImage^ dedriftedXYIntsFits = gcnew FITSImage(dedriftedXYIntsFile, dedriftedXYInts, false, true);
		dedriftedXYIntsFits->CopyHeader(driftsfits);
		dedriftedXYIntsFits->WriteImage(::TypeCode::Int16, true);

		ind = fraclistfile->LastIndexOf("_deDrift");
		if (ind == -1)
			ind = fraclistfile->LastIndexOf(".");
		String^ dedriftedXYFracFile = fraclistfile->Insert(ind, "_deDrift");
		FITSImage^ dedriftedXYFracFits = gcnew FITSImage(dedriftedXYFracFile, dedriftedXYFrac, false, true);
		dedriftedXYFracFits->CopyHeader(driftsfits);
		dedriftedXYFracFits->WriteImage(::TypeCode::Int16, true);

		ind = flatlistfile->LastIndexOf("_deDrift");
		if (ind == -1)
			ind = flatlistfile->LastIndexOf(".");
		String^ dedriftedFlatFile = flatlistfile->Insert(ind, "_deDrift");
		FITSImage^ dedriftedFlatFits = gcnew FITSImage(dedriftedFlatFile, dedriftedFlat, false, true);
		dedriftedFlatFits->CopyHeader(driftsfits);
		dedriftedFlatFits->WriteImage(::TypeCode::Double, true);

		ind = timelistfile->LastIndexOf("_deDrift");
		if (ind == -1)
			ind = timelistfile->LastIndexOf(".");
		String^ dedriftedTimeFile = timelistfile->Insert(ind, "_deDrift");
		FITSImage^ dedriftedTimeFits = gcnew FITSImage(dedriftedTimeFile, dedriftedTime, false, true);
		dedriftedTimeFits->CopyHeader(driftsfits);
		dedriftedTimeFits->WriteImage(::TypeCode::UInt32, true);

		ind = framelistfile->LastIndexOf("_deDrift");
		if (ind == -1)
			ind = framelistfile->LastIndexOf(".");
		String^ dedriftedFrameFile = framelistfile->Insert(ind, "_deDrift");
		FITSImage^ dedriftedFrameFits = gcnew FITSImage(dedriftedFrameFile, dedriftedFrame, false, true);
		dedriftedFrameFits->CopyHeader(driftsfits);
		dedriftedFrameFits->WriteImage(::TypeCode::UInt32, true);

		ind = mdMmlistfile->LastIndexOf("_deDrift");
		if (ind == -1)
			ind = mdMmlistfile->LastIndexOf(".");
		String^ dedriftedXYmdMmFile = mdMmlistfile->Insert(ind, "_deDrift");
		FITSImage^ dedriftedXYmdMmFits = gcnew FITSImage(dedriftedXYmdMmFile, dedriftedXYmdMm, false, true);
		dedriftedXYmdMmFits->CopyHeader(driftsfits);
		dedriftedXYmdMmFits->WriteImage(::TypeCode::Int16, true);

		if (BJDexists)
		{
			ind = BJDlistfile->LastIndexOf("_deDrift");
			if (ind == -1)
				ind = BJDlistfile->LastIndexOf(".");
			String^ dedriftedBJDFile = BJDlistfile->Insert(ind, "_deDrift");
			FITSImage^ dedriftedBJDFits = gcnew FITSImage(dedriftedBJDFile, dedriftedBJD, false, true);
			dedriftedBJDFits->CopyHeader(driftsfits);
			dedriftedBJDFits->WriteImage(::TypeCode::Double, true);
		}

		if (createexposurearray || master)
		{
			String^ dedriftedExpFile = dedriftedTimeFile->Replace("TimeList", "ExpArrayList");
			FITSImage^ dedriftedExpFits = gcnew FITSImage(dedriftedExpFile, dedriftedExposure, false, true);
			dedriftedExpFits->CopyHeader(driftsfits);
			dedriftedExpFits->WriteImage(::TypeCode::Double, true);

			//if (createexposurearray)
			{
				dedriftedExpFile = dedriftedExpFile->Replace("ExpArrayList", "ExpArrayImg");
				if (master)
					exposurearray = JPFITS::FITSImage::ReadImageArrayOnly(dedriftedExpFile->Replace("_deDrift.fits", ".fits"), nullptr, true);
				FITSImage^ exp = gcnew FITSImage(dedriftedExpFile, exposurearray, false, true);
				exp->CopyHeader(driftsfits);
				exp->WriteImage(::TypeCode::Double, true);
			}
		}

		UVCREATEIMAGEFILENAME = dedriftedXYIntsFile;

		if (UVDRIFTAUTORUN)
		{
			ApplyDriftListWrkr->ReportProgress(3);
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}
}

void Form1::ApplyDriftListWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	if (e->ProgressPercentage == 0)
	{
		WAITBAR->ProgressBar->Maximum = 100;
		WAITBAR->Text = "Exposure Array...";
		WAITBAR->TextMsg->Text = "Creating exposure array...please wait...";
		WAITBAR->ProgressBar->Value = ::Convert::ToInt32(e->UserState);
		WAITBAR->Refresh();
	}

	if (e->ProgressPercentage == 1)
	{
		WAITBAR->Text = "Applying...";
		WAITBAR->TextMsg->Text = "Applying drift...";
		WAITBAR->Refresh();
	}

	if (e->ProgressPercentage == 2)
	{
		WAITBAR->Text = "Saving...";
		WAITBAR->TextMsg->Text = "Saving de-drifted lists...";
		WAITBAR->Refresh();
	}

	if (e->ProgressPercentage == 3)
	{
		WAITBAR->Text = "Image...";
		WAITBAR->TextMsg->Text = "Creating image...";
		WAITBAR->Refresh();
	}
}

void Form1::ApplyDriftListWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		Form1::Enabled = true;
		Form1::BringToFront();
		return;
	}

	if (!UVDRIFTAUTORUN)
	{
		WAITBAR->Hide();
		WAITBAR->Close();
		Form1::BringToFront();
		::DialogResult res = ::MessageBox::Show("Completed applying the drift correction. Would you like to create the image using current image settings?", "Finished...", ::MessageBoxButtons::YesNo);
		if (res == ::DialogResult::No)
		{
			Form1::Enabled = true;
			Form1::BringToFront();
			return;
		}
		if (res == ::DialogResult::Yes)
		{
			UVCREATEIMAGENOW = true;
			ConvertListToImgMenu_DropDownOpened(sender, e);
			ConvertListToImgMenu->HideDropDown();
			ConvertListToImgMenu_Click(sender, e);
		}
	}
	else
	{
		UVCREATEIMAGENOW = true;
		ConvertListToImgMenu_DropDownOpened(sender, e);
		ConvertListToImgMenu->HideDropDown();
		ConvertListToImgMenu_Click(sender, e);
	}
}

void Form1::PlotCountsPerFrameMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = false;

	dlg->Title = "Select the FRAME List (_FrameList)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;
	String^ framelistfile = dlg->FileName;
	dir = framelistfile->Substring(0, framelistfile->LastIndexOf("\\"));
	SetReg("CCDLAB", "L2EventListPath", dir);
	FITSImage^ framefits = gcnew JPFITS::FITSImage(framelistfile, nullptr, true, false, false, false);
	array<double>^ frames = FITSImage::ReadImageVectorOnly(framelistfile, nullptr, true);

	int nframes = int(frames[frames->Length - 1] - frames[0] + 1);

	array<double>^ plotframes = gcnew array<double>(nframes);
	array<double>^ plotcounts = gcnew array<double>(nframes);

	int curr_frame = -1;

	for (int i = 0; i < frames->Length; i++)
		if (curr_frame != (int)frames[i])
		{
			plotframes[int(frames[i] - frames[0])] = frames[i];
			curr_frame = (int)frames[i];

			int j = i;
			while (j < frames->Length && curr_frame == int(frames[j]))
			{
				plotcounts[int(frames[i] - frames[0])]++;
				j++;
			}

		}

	for (int i = 0; i < nframes; i++)
		if (plotframes[i] == 0)
			plotframes[i] = plotframes[i - 1] + 1;

	String^ title = "Orbit: " + framefits->GetKeyValue("ORB_NUM") + "; Source: " + framefits->GetKeyValue("SOURCEID") + "; Detector:" + framefits->GetKeyValue("DETECTOR");

	JPPlot^ jpplot = gcnew JPPlot();
	jpplot->Text = title;
	jpplot->PlotLine(plotframes,plotcounts,"Frame Number","Counts in Frame",title, Charting::SeriesChartType::Point, "CountsperFrame");
}

void Form1::perTimeBinMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	double tbin;
	try
	{
		tbin = ::Convert::ToDouble(((String^)plotPerTimeBinComboBox->SelectedItem)->Replace("s",""));
	}
	catch (...)
	{
		::MessageBox::Show("Please select time bin from the drop down...","Warning");
		return;
	}

	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = false;

	dlg->Title = "Select the TIME List (_TimeList)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;
	String^ timelistfile = dlg->FileName;
	dir = timelistfile->Substring(0,timelistfile->LastIndexOf("\\"));
	SetReg("CCDLAB", "L2EventListPath", dir);
	FITSImage^ timefits = gcnew JPFITS::FITSImage(timelistfile, nullptr, true, false, false, false);
	array<double>^ times = FITSImage::ReadImageVectorOnly(timelistfile, nullptr, true);

	bool goodselection = false;
	if (timelistfile->Contains("TimeList"))
	{
		goodselection = true;
		for (int i = 0; i < times->Length; i++)
			times[i] /= 1000;//convert to seconds
	}
	if (timelistfile->Contains("BJDList"))
	{
		goodselection = true;
		for (int i = 0; i < times->Length; i++)
			times[i] *= 86400;//convert to seconds
	}
	if (!goodselection)
	{
		::MessageBox::Show("Doesn't seem like you selected a time list...","Error");
		return;
	}

	double nbins = Math::Floor((times[times->Length-1] - times[0])/tbin);

	if (nbins <= 1)
	{
		::MessageBox::Show("Time bin is too large for the selected time list...","Error");
		return;
	}

	array<double>^ bintimes = gcnew array<double>((int)nbins);
	array<double>^ bincounts = gcnew array<double>((int)nbins);

	double currtime = times[0];
	int bin = 0;
	int c = 0;
	double count = 0;

	while (bin < nbins)
	{
		while (times[c] < currtime + tbin)
		{
			c++;
			count++;
		}
		bincounts[bin] = count;
		bintimes[bin] = currtime + tbin/2;
		currtime += tbin;
		count = 0;
		bin++;
	}

	String^ title = "Orbit: " + timefits->GetKeyValue("ORB_NUM") + "; Source: " + timefits->GetKeyValue("SOURCEID") + "; Detector:" + timefits->GetKeyValue("DETECTOR");

	JPPlot^ jpplot = gcnew JPPlot();
	jpplot->Text = title;
	jpplot->PlotLine(bintimes,bincounts,"Bin Time (seconds)","Counts in Bin",title, Charting::SeriesChartType::Point, "CountsperBin");

}

void Form1::CrossCorrINTDriftChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (CrossCorrINTDriftChck->Checked == false)
		CrossCorrINTDriftChck->Checked = true;
	SetReg("CCDLAB", "CrossCorrINTDrift",CrossCorrINTDriftChck->Checked);
	if (CrossCorrINTDriftChck->Checked)
		PointSrcINTDriftChck->Checked = false;
	SetReg("CCDLAB", "PointSrcINTDrift",PointSrcINTDriftChck->Checked);
	TryAutoDeBiasINTDrift->Checked = true;
	TryAutoDeBiasINTDrift->Enabled = true;
	SetReg("CCDLAB", "AutoDeBiasINTDriftChck",TryAutoDeBiasINTDrift->Checked);
	SetReg("CCDLAB", "AutoDeBiasINTDriftEnab",TryAutoDeBiasINTDrift->Enabled);

	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
}

void Form1::PointSrcINTDriftChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (PointSrcINTDriftChck->Checked == false)
		PointSrcINTDriftChck->Checked = true;
	SetReg("CCDLAB", "PointSrcINTDrift",PointSrcINTDriftChck->Checked);
	if (PointSrcINTDriftChck->Checked)
		CrossCorrINTDriftChck->Checked = false;
	SetReg("CCDLAB", "CrossCorrINTDrift",CrossCorrINTDriftChck->Checked);
	TryAutoDeBiasINTDrift->Checked = false;
	TryAutoDeBiasINTDrift->Enabled = false;
	SetReg("CCDLAB", "AutoDeBiasINTDriftChck",TryAutoDeBiasINTDrift->Checked);
	SetReg("CCDLAB", "AutoDeBiasINTDriftEnab",TryAutoDeBiasINTDrift->Enabled);

	UVITMenu->ShowDropDown();
	CreateDriftListMenuItem->ShowDropDown();
	CreateDriftFromINTMenuItem->ShowDropDown();
}

void Form1::CreateDriftFromINTMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->DropDown->Close();
	CreateDriftListMenuItem->DropDown->Close();
	CreateDriftFromINTMenuItem->DropDown->Close();
	PointSrcINTDriftChck->DropDown->Close();

	if (!UVITMANREG_CONTINUE)
	{
		::FolderBrowserDialog^ fdlg = gcnew ::FolderBrowserDialog();
		if (UVITMANREGDIRLISTINDEX == 0)
		{
			fdlg->SelectedPath = (String^)GetReg("CCDLAB", "L2EventListPath");
			if (!AUTOVISDRIFT)
			{
				String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
				fdlg->Description = "Select the Folder of INT-Mode Frames...";
				fdlg->SelectedPath = (String^)GetReg("CCDLAB", "L2EventListPath");
				::DialogResult res = fdlg->ShowDialog();
				if (res == ::DialogResult::Cancel)
					return;
				SetReg("CCDLAB", "L2EventListPath", fdlg->SelectedPath);
			}		
			AUTOVISDRIFT = false;
			UVITMANREGDIRLIST = Directory::GetDirectories(fdlg->SelectedPath);
		}

		String^ curdir;
		if (UVITMANREGDIRLIST->Length == 0)
		{
			curdir = fdlg->SelectedPath;
			UVITMANREGDIR_MULTI = false;
		}
		else
		{
			//check if a directory had been removed
			int i = 0;
			for (int j = 0; j < UVITMANREGDIRLIST->Length; j++)
				if (Directory::Exists(UVITMANREGDIRLIST[j]))
				{
					UVITMANREGDIRLIST[i] = UVITMANREGDIRLIST[j];
					i++;
				}
			if (i != UVITMANREGDIRLIST->Length)
				Array::Resize(UVITMANREGDIRLIST, i);

			//check if folders in the directory list already contain a drift series...if they do then increment UVITMANREGDIRLISTINDEX until there isn't one
			i = 0;
			while (i < UVITMANREGDIRLIST->Length && Directory::GetFiles(UVITMANREGDIRLIST[i], "*.drift")->Length > 0)
				i++;

			if (i == UVITMANREGDIRLIST->Length)
			{
				if (::MessageBox::Show("Existing drift series lists found in all subdirectories.  Do you wish to re-process all subdirectories?", "Reprocess?", MessageBoxButtons::YesNo) == ::DialogResult::No)
					return;

				array<String^>^ existinglists = ::Directory::GetFiles(fdlg->SelectedPath, "*.drift", ::SearchOption::AllDirectories);
				for (int kkk = 0; kkk < existinglists->Length; kkk++)
					File::Delete(existinglists[kkk]);
				i = 0;
			}

			UVITMANREGDIRLISTINDEX = i;
			curdir = UVITMANREGDIRLIST[UVITMANREGDIRLISTINDEX];
			UVITMANREGDIR_MULTI = true;
		}

		UVITMANREGFILELIST = Directory::GetFiles(curdir,"*.fits",::SearchOption::TopDirectoryOnly);
		if (UVITMANREGFILELIST->Length == 0)
		{
			::MessageBox::Show("No files found in directory: " + curdir,"Error");
			return;
		}
		Array::Sort(UVITMANREGFILELIST);

		//SetReg("CCDLAB", "FolderBrowserPath", curdir);

		if (CrossCorrINTDriftChck->Checked)
		{
			array<Object^>^ arg = gcnew array<Object^>(2);
			arg[0] = (Object^)UVITMANREGFILELIST;
			arg[1] = (Object^)CrossCorrINTDriftChck->Checked;
			Form1::Enabled = false;
			WAITBAR = gcnew JPWaitBar::WaitBar();
			WAITBAR->ProgressBar->Maximum = 100;
			WAITBAR->DialogResult = ::DialogResult::OK;
			if (UVITMANREGDIRLIST->Length > 0)
				WAITBAR->Text = "Calculating drift for directory " + (UVITMANREGDIRLISTINDEX+1).ToString() + " of " + UVITMANREGDIRLIST->Length.ToString();
			else
				WAITBAR->Text = "Calculating drift...";
			DriftFromINTWrkr->RunWorkerAsync(arg);
			WAITBAR->Show();
			return;
		}
		
		if (PointSrcINTDriftChck->Checked)
		{
			EqualHWChck->Checked = true;
			if (HalfWidthXUpD->Value < 5)
				HalfWidthXUpD->Value = 5;
			ManRegTrkHWUpD->Value = HalfWidthXUpD->Value;
			DOUVITMANREG = true;
			UVITMANREGFILELIST_TIMES = gcnew array<double>(UVITMANREGFILELIST->Length);
			FileListDrop->Items->Clear();
			IMAGESET->Clear();
			array<String^>^ ref = gcnew array<String^>(1){UVITMANREGFILELIST[0]};
			AddToImageSet(ref);
			MainTab->SelectedIndex = 0;
			ImageBatchRedxnPnl->Enabled = true;
			ContrastWideRad->PerformClick();
			UVITMenu->HideDropDown();
			CreateDriftListMenuItem->HideDropDown();
			CreateDriftFromINTMenuItem->HideDropDown();

			array<bool, 2>^ ROI = gcnew array<bool, 2>(512, 512);
			for (int x = 0; x < 512; x++)
				for (int y = 0; y < 512; y++)
					if ((x - 255) * (x - 255) + (y - 255) * (y - 255) < 225 * 225)
						ROI[x, y] = true;
			PSE = gcnew JPFITS::SourceExtractor();
			PSE->Extract_Sources(IMAGESET[0]->Image, 0, 150, 25000, 200, Double::MaxValue, false, 2, 10, PSEAutoBackgroundChck->Checked, "", ROI, false);
			if (PSE->N_Sources > 35)
				PSE->ClipToNBrightest(35);
			if (PSE->N_Sources > 0)
			{
				MAKEPSERECTS();
				ShowPSEChck->Checked = true;
				ImageWindow->Refresh();
				SubImageWindow->Refresh();
			}

			::DialogResult res;
			if (PSE->N_Sources == 0)
				res = ::DialogResult::No;
			else if (PSE->N_Sources > 0 && !PointSrcINTDriftNoPSEConfChck->Checked)
				res = MessageBox::Show("Use " + PSE->N_Sources + " auto-found sources for tracking?", "Track?", MessageBoxButtons::YesNoCancel);
			else if (PSE->N_Sources > 0 && PointSrcINTDriftNoPSEConfChck->Checked)
				res = ::DialogResult::Yes;

			if (res == ::DialogResult::No)
			{
				ManRegBtn->PerformClick();
				return;
			}
			if (res == ::DialogResult::Cancel)
			{
				DOUVITMANREG = false;
				UVITMANREGFILELIST_TIMES = nullptr;
				UVITMANREGFILELIST = nullptr;
				return;
			}
			if (res == ::DialogResult::Yes)
			{
				UVITMANREG_CONTINUE = true;
				MANREGCOORDS = gcnew array<int, 2>(PSE->N_Sources, 2);
				for (int i = 0; i < PSE->N_Sources; i++)
				{
					MANREGCOORDS[i, 0] = (int)PSE->Centroids_X[i];
					MANREGCOORDS[i, 1] = (int)PSE->Centroids_Y[i];
				}
				HalfWidthXUpD->Value = 5;
				HalfWidthYUpD->Value = 5;
				ImageWindow->Refresh();
				SubImageWindow->Refresh();
			}			
		}
	}

	if (UVITMANREG_CONTINUE)
	{
		UVITMANREG_CONTINUE = false;
		MANREG_CONTINUE = false;
		ImageBatchRedxnPnl->Enabled = false;
		ShowFoundCoordsChck->Checked = false;//this is for plotting the local max point in the ROI
		ImageWindow->Refresh();

		DO_UVITDRIFTFILES = true;

		SPAREFITSImageSet = gcnew FITSImageSet();
		SPAREFITSImageSet->Load(UVITMANREGFILELIST, nullptr, false, true, true, "Loading VIS folder");

		Form1::Enabled = false;
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = 100;
		if (UVITMANREGDIRLIST->Length > 0)
			WAITBAR->Text = "Point Source (" + MANREGCOORDS->GetLength(0) + ") Drift Tracking Directory " + (UVITMANREGDIRLISTINDEX+1).ToString() + " of " + UVITMANREGDIRLIST->Length.ToString();
		else
			WAITBAR->Text = "Point Source Drift Tracking...";
		ManRegWrkr->RunWorkerAsync();
		WAITBAR->ShowDialog();
	}
}

void Form1::DriftFromINTWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	try
	{
		array<Object^>^ arg = (array<Object^>^)e->Argument;
		array<String^>^ filelist = (array<String^>^)arg[0];
		bool byxcorr = ::Convert::ToBoolean(arg[1]);

		FITSImage^ reffits = gcnew FITSImage(filelist[0], nullptr, true, false, false, false);
		FITSImage^ RELfits;
		array<double, 2>^ refimg = FITSImage::ReadImageArrayOnly(filelist[0], nullptr, true);
		double lasttime = ::Convert::ToDouble(reffits->GetKeyValue("FRMTIME"))*1000;
		double Nstack = ::Convert::ToDouble(reffits->GetKeyValue("NO_FRMS"));
		array<double,2>^ RELimg;
		//array<double>^ shifts;
		array<double,2>^ xyshiftslist = gcnew array<double,2>(3,filelist->Length);
		double framereadtime, xshift, yshift;

		if (byxcorr)
		{
			bool deBias = TryAutoDeBiasINTDrift->Checked;
			if (deBias)
			{
				refimg = JPMath::DeGradient(refimg, 0, true);
				refimg = JPMath::DeGradient(refimg, 1, true);
			}

			refimg = JPMath::Hanning(refimg, true);
			array<double, 1>^ Href = JPMath::Sum(refimg, 1, true);
			array<double, 1>^ Vref = JPMath::Sum(refimg, 0, true);
			Href = JPMath::VectorSubScalar(Href, JPMath::Mean(Href, true), true);
			Vref = JPMath::VectorSubScalar(Vref, JPMath::Mean(Vref, true), true);

			double currtime, t0, meanxshift = 0, meanyshift = 0;
			int intprog = 0;
			for (int i = 1; i < filelist->Length; i++)
			{

				if (WAITBAR->DialogResult == ::DialogResult::Cancel)
					return;
				if (100*i/filelist->Length > intprog)
				{
					intprog = 100*i/filelist->Length;
					DriftFromINTWrkr->ReportProgress(intprog);
				}

				RELfits = gcnew FITSImage(filelist[i], nullptr, true, false, false, true);
				RELimg = FITSImage::ReadImageArrayOnly(filelist[i], nullptr, true);

				JPMath::XCorrImageLagShifts(Href, Vref, RELimg, deBias, deBias, true, xshift, yshift, true);

				currtime = ::Convert::ToDouble(RELfits->GetKeyValue("FRMTIME"))*1000;
				framereadtime = (currtime - lasttime)/Nstack;
				t0 = lasttime + framereadtime - Nstack*framereadtime/2;

				xyshiftslist[0,i-1] = t0;
				xyshiftslist[1,i] = Math::Round(xshift*32);
				xyshiftslist[2,i] = Math::Round(yshift*32);

				meanxshift += xyshiftslist[1, i];//for average drift
				meanyshift += xyshiftslist[2, i];//for average drift

				if (i == filelist->Length - 1)
					xyshiftslist[0,i] = currtime + framereadtime - Nstack*framereadtime/2;
				
				lasttime = currtime;
			}

			//zero-out drift series to average drift
			meanxshift /= double(filelist->Length);
			meanyshift /= double(filelist->Length);
			#pragma omp parallel for
			for (int i = 0; i < filelist->Length; i++)
			{
				xyshiftslist[1, i] -= meanxshift;
				xyshiftslist[2, i] -= meanyshift;
			}
		}

		if (!byxcorr)//then by point source tracking
		{			
			double meanxshift = 0, meanyshift = 0;
			int NSrc = MANREGCOORDS->GetLength(0);
			framereadtime = (UVITMANREGFILELIST_TIMES[1] - UVITMANREGFILELIST_TIMES[0])/Nstack;
			xyshiftslist[0,0] = UVITMANREGFILELIST_TIMES[0] + framereadtime - Nstack*framereadtime/2;

			array<double>^ xdriftinstance = gcnew array<double>(NSrc);
			array<double>^ ydriftinstance = gcnew array<double>(NSrc);
			double min, max, range = 0;

			for (int i = 1; i < filelist->Length; i++)
			{
				double x_drift = 0;
				double y_drift = 0;
				for (int j = 0; j < NSrc; j++)
				{
					xdriftinstance[j] = MANREGCENTROIDS[j, 0, i] - MANREGCENTROIDS[j, 0, 0];
					ydriftinstance[j] = MANREGCENTROIDS[j, 1, i] - MANREGCENTROIDS[j, 1, 0];
				}

				x_drift = JPMath::Mean_RobustClipped(xdriftinstance, 3);
				y_drift = JPMath::Mean_RobustClipped(ydriftinstance, 3);

				framereadtime = (UVITMANREGFILELIST_TIMES[i] - UVITMANREGFILELIST_TIMES[i - 1]) / Nstack;
				xyshiftslist[0, i] = UVITMANREGFILELIST_TIMES[i] + framereadtime - Nstack * framereadtime / 2;
				xyshiftslist[1, i] = (double)int(x_drift * 32);
				xyshiftslist[2, i] = (double)int(y_drift * 32);

				meanxshift += xyshiftslist[1, i];//for average drift
				meanyshift += xyshiftslist[2, i];//for average drift
 
				int index = 0;
				JPMath::MinMax(xdriftinstance, min, max, false);
				double currrange = max - min;
				if (currrange > range)
				{
					range = currrange;
					double mean = JPMath::Mean(xdriftinstance, true);
					JPMath::Max(JPMath::Abs(JPMath::VectorSubScalar(xdriftinstance, mean, true), false), index, false);
					UVITINTDRIFT_MAXDEV_INDEX = index;
				}
				JPMath::MinMax(ydriftinstance, min, max, false);
				currrange = max - min;
				if (currrange > range)
				{
					range = currrange;
					double mean = JPMath::Mean(ydriftinstance, true);
					JPMath::Max(JPMath::Abs(JPMath::VectorSubScalar(ydriftinstance, mean, true), false), index, false);
					UVITINTDRIFT_MAXDEV_INDEX = index;
				}
			}

			//zero-out drift series to average drift
			meanxshift /= double(filelist->Length);
			meanyshift /= double(filelist->Length);
			#pragma omp parallel for
			for (int i = 0; i < filelist->Length; i++)
			{
				xyshiftslist[1, i] -= meanxshift;
				xyshiftslist[2, i] -= meanyshift;
			}
		}

		if (SmoothINTDriftChck->Checked)
		{
			array<double>^ x = gcnew array<double>(filelist->Length);
			array<double>^ y = gcnew array<double>(filelist->Length);
			for (int i = 0; i < filelist->Length; i++)
			{
				x[i] = xyshiftslist[1, i];
				y[i] = xyshiftslist[2, i];
			}

			x = JPMath::Smooth(x, 5, false);
			y = JPMath::Smooth(y, 5, false);

			for (int i = 0; i < filelist->Length; i++)
			{
				xyshiftslist[1, i] = (double)(int)x[i];
				xyshiftslist[2, i] = (double)(int)y[i];
			}
		}

		int ind = filelist[0]->LastIndexOf("l2");
		String^ driftslistfile = filelist[0];
		if (ind > 0)
			driftslistfile = filelist[0]->Remove(ind+2);
		driftslistfile = driftslistfile->Replace(".fits","");
		if (byxcorr)
			driftslistfile = driftslistfile + "_XYDrift_List_XCorr.drift";
		else
			driftslistfile = driftslistfile + "_XYDrift_List_SrcTrk.drift";
		FITSImage^ driftfits = gcnew FITSImage(driftslistfile, xyshiftslist, false, true);
		driftfits->CopyHeader(reffits);
		driftfits->WriteImage(::TypeCode::Double, true);
		UVPLOTDRIFTFILENAME = driftslistfile;
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}
}

void Form1::DriftFromINTWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat("Completed: ",e->ProgressPercentage,"%");
	WAITBAR->Refresh();
}

void Form1::DriftFromINTWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	::DialogResult waitbar_res = WAITBAR->DialogResult;

	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::BringToFront();
	UVITMANREG_CONTINUE = false;
	DO_UVITDRIFTFILES = false;
	SPAREFITSImageSet->Clear();

	if (waitbar_res == ::DialogResult::Cancel)
	{
		UVITMANREGDIRLISTINDEX = 0;
		return;
	}

	if (waitbar_res != ::DialogResult::Cancel)
	{
		if (!UVITMANREGDIR_MULTI && ::MessageBox::Show("Completed making the drift correction list.  Would you like to plot it?","Finished...",::MessageBoxButtons::YesNo) == ::DialogResult::Yes)
		{
			UVPLOTDRIFTLISTNOW = true;
			PlotDriftListMenuItem->PerformClick();
		}

		if (UVITMANREGDIR_MULTI)
		{
			UVPLOTDRIFTLISTNOW = true;
			PlotDriftListMenuItem->PerformClick();

			::DialogResult dres;
			if (!PointSrcINTDriftNoPlotConfChck->Checked)
				dres = MessageBox::Show("Is the Drift Series OK? (Yes = conintue; No = redo; Cancel = exit)", "Drift Series Check...", ::MessageBoxButtons::YesNoCancel);
			else
				dres = ::DialogResult::Yes;
			
			if (dres == ::DialogResult::Cancel)
			{
				File::Delete(UVPLOTDRIFTFILENAME);
				UVITINTMODEDRIFTPOLYPOINTS = nullptr;
				ImageWindow->Refresh();
				return;
			}

			if (dres == ::DialogResult::No)
			{
				File::Delete(UVPLOTDRIFTFILENAME);
				XDRIFT_PLOT->Close();
				YDRIFT_PLOT->Close();
				CreateDriftFromINTMenuItem_Click(sender, gcnew System::EventArgs);
				return;
			}

			if (dres == ::DialogResult::Yes && UVITMANREGDIRLISTINDEX < UVITMANREGDIRLIST->Length - 1)
			{
				UVITINTMODEDRIFTPOLYPOINTS = nullptr;
				ImageWindow->Refresh();

				UVITMANREGDIRLISTINDEX++;
				XDRIFT_PLOT->Close();
				YDRIFT_PLOT->Close();
				CreateDriftFromINTMenuItem_Click(sender, gcnew System::EventArgs);
			}
			else//finished
			{
				XDRIFT_PLOT->Close();
				YDRIFT_PLOT->Close();
				UVITMANREGDIRLISTINDEX = 0;//complete
				UVITINTMODEDRIFTPOLYPOINTS = nullptr;
				DOUVITMANREG = false;
				UVREGISTRATION = false;
				PSERECTS = nullptr;
				PSE = nullptr;
				ImageWindow->Refresh();

				if (!L1AutoApplyVISDrift->Checked)
					if (MessageBox::Show("Proceed to Application of Drift Series?", "Proceed?", MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
						return;
				AUTOVISDRIFTAPPLY = true;
				ConsolidateNUVApplyToFUV_Click(sender, e);
			}
		}
	}
}

void Form1::UserXShiftTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (UserXShiftTxt->Text == "-" || UserXShiftTxt->Text == "-." || UserXShiftTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(UserXShiftTxt->Text);
	}
	catch (...)
	{
		UserXShiftTxt->Text = "0";
	}
	SetReg("CCDLAB", "UserXShiftTxt",UserXShiftTxt->Text);
}

void Form1::UserYShiftTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (UserYShiftTxt->Text == "-" || UserYShiftTxt->Text == "-." || UserYShiftTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(UserYShiftTxt->Text);
	}
	catch (...)
	{
		UserYShiftTxt->Text = "0";
	}
	SetReg("CCDLAB", "UserYShiftTxt",UserYShiftTxt->Text);
}

void Form1::UserRotationTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (UserRotationTxt->Text == "-" || UserRotationTxt->Text == "-." || UserRotationTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(UserRotationTxt->Text);
	}
	catch (...)
	{
		UserRotationTxt->Text = "0";
	}
	SetReg("CCDLAB", "UserRotationTxt",UserRotationTxt->Text);
}

void Form1::UserRotationXTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (UserRotationXCenterTxt->Text == "-" || UserRotationXCenterTxt->Text == "-." || UserRotationXCenterTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(UserRotationXCenterTxt->Text);
	}
	catch (...)
	{
		UserRotationXCenterTxt->Text = "0";
	}
	SetReg("CCDLAB", "UserRotationXTxt",UserRotationXCenterTxt->Text);
}

void Form1::UserRotationYTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (UserRotationYCenterTxt->Text == "-" || UserRotationYCenterTxt->Text == "-." || UserRotationYCenterTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(UserRotationYCenterTxt->Text);
	}
	catch (...)
	{
		UserRotationYCenterTxt->Text = "0";
	}
	SetReg("CCDLAB", "UserRotationYTxt",UserRotationYCenterTxt->Text);
}

void Form1::FlipHorizontalMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UserDefinedShiftRotateMenuItem->ShowDropDown();
	SetReg("CCDLAB", "FlipHorizontalMenuItem",FlipHorizontalMenuItem->Checked);
}

void Form1::FlipVerticalMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UserDefinedShiftRotateMenuItem->ShowDropDown();
	SetReg("CCDLAB", "FlipVerticalMenuItem",FlipVerticalMenuItem->Checked);
}

void Form1::LinearRotationChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UserDefinedShiftRotateMenuItem->ShowDropDown();
	SetReg("CCDLAB", "LinearRotationChck",LinearRotationChck->Checked);

	if (LinearRotationChck->Checked)
	{
		GeneralTransformChck->Checked = false;

		SetReg("CCDLAB", "GeneralTransformChck",GeneralTransformChck->Checked);

		FlipHorizontalMenuItem->Enabled = true;
		FlipVerticalMenuItem->Enabled = true;
		UserXShiftTxt->Enabled = true;
		UserYShiftTxt->Enabled = true;
		UserRotationTxt->Enabled = true;
		UserRotationXCenterTxt->Enabled = true;
		UserRotationYCenterTxt->Enabled = true;

		TransformCoefATxt->Enabled = false;
		TransformCoefBTxt->Enabled = false;
		TransformCoefCTxt->Enabled = false;
		TransformCoefDTxt->Enabled = false;
		TransformCenterXTxt->Enabled = false;
		TransformCenterYTxt->Enabled = false;
		TransformShiftXTxt->Enabled = false;
		TransformShiftYTxt->Enabled = false;
	}
	else
	{
		FlipHorizontalMenuItem->Enabled = false;
		FlipVerticalMenuItem->Enabled = false;
		UserXShiftTxt->Enabled = false;
		UserYShiftTxt->Enabled = false;
		UserRotationTxt->Enabled = false;
		UserRotationXCenterTxt->Enabled = false;
		UserRotationYCenterTxt->Enabled = false;
	}
}

void Form1::GeneralTransformChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	ShiftAndRotateMenuItem->ShowDropDown();
	UserDefinedShiftRotateMenuItem->ShowDropDown();
	SetReg("CCDLAB", "GeneralTransformChck",GeneralTransformChck->Checked);

	if (GeneralTransformChck->Checked)
	{
		LinearRotationChck->Checked = false;

		SetReg("CCDLAB", "LinearRotationChck",LinearRotationChck->Checked);

		FlipHorizontalMenuItem->Enabled = false;
		FlipVerticalMenuItem->Enabled = false;
		UserXShiftTxt->Enabled = false;
		UserYShiftTxt->Enabled = false;
		UserRotationTxt->Enabled = false;
		UserRotationXCenterTxt->Enabled = false;
		UserRotationYCenterTxt->Enabled = false;

		TransformCoefATxt->Enabled = true;
		TransformCoefBTxt->Enabled = true;
		TransformCoefCTxt->Enabled = true;
		TransformCoefDTxt->Enabled = true;
		TransformCenterXTxt->Enabled = true;
		TransformCenterYTxt->Enabled = true;
		TransformShiftXTxt->Enabled = true;
		TransformShiftYTxt->Enabled = true;
	}
	else
	{
		TransformCoefATxt->Enabled = false;
		TransformCoefBTxt->Enabled = false;
		TransformCoefCTxt->Enabled = false;
		TransformCoefDTxt->Enabled = false;
		TransformCenterXTxt->Enabled = false;
		TransformCenterYTxt->Enabled = false;
		TransformShiftXTxt->Enabled = false;
		TransformShiftYTxt->Enabled = false;
	}
}

void Form1::TransformCoefATxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformCoefATxt->Text == "-" || TransformCoefATxt->Text == "-." || TransformCoefATxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformCoefATxt->Text);
	}
	catch (...)
	{
		TransformCoefATxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformCoefATxt",TransformCoefATxt->Text);
}

void Form1::TransformCoefBTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformCoefBTxt->Text == "-" || TransformCoefBTxt->Text == "-." || TransformCoefBTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformCoefBTxt->Text);
	}
	catch (...)
	{
		TransformCoefBTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformCoefBTxt",TransformCoefBTxt->Text);
}

void Form1::TransformCoefCTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformCoefCTxt->Text == "-" || TransformCoefCTxt->Text == "-." || TransformCoefCTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformCoefCTxt->Text);
	}
	catch (...)
	{
		TransformCoefCTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformCoefCTxt",TransformCoefCTxt->Text);
}

void Form1::TransformCoefDTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformCoefDTxt->Text == "-" || TransformCoefDTxt->Text == "-." || TransformCoefDTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformCoefDTxt->Text);
	}
	catch (...)
	{
		TransformCoefDTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformCoefDTxt",TransformCoefDTxt->Text);
}

void Form1::TransformCenterXTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformCenterXTxt->Text == "-" || TransformCenterXTxt->Text == "-." || TransformCenterXTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformCenterXTxt->Text);
	}
	catch (...)
	{
		TransformCenterXTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformCenterXTxt",TransformCenterXTxt->Text);
}

void Form1::TransformCenterYTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformCenterYTxt->Text == "-" || TransformCenterYTxt->Text == "-." || TransformCenterYTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformCenterYTxt->Text);
	}
	catch (...)
	{
		TransformCenterYTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformCenterYTxt",TransformCenterYTxt->Text);
}

void Form1::TransformShiftXTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformShiftXTxt->Text == "-" || TransformShiftXTxt->Text == "-." || TransformShiftXTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformShiftXTxt->Text);
	}
	catch (...)
	{
		TransformShiftXTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformShiftXTxt",TransformShiftXTxt->Text);
}

void Form1::TransformShiftYTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (TransformShiftYTxt->Text == "-" || TransformShiftYTxt->Text == "-." || TransformShiftYTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(TransformShiftYTxt->Text);
	}
	catch (...)
	{
		TransformShiftYTxt->Text = "0";
	}
	SetReg("CCDLAB", "TransformShiftYTxt",TransformShiftYTxt->Text);
}

void Form1::UserDefinedShiftRotateMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	//done in UVIT_Menu click
}

void Form1::UserDefinedShiftRotateMenuItem_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	array<String^>^ FileNames;
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");

	if (!UVNUVTOFUV)
	{
		if (LinearRotationChck->Checked)
		{
			double xshift, yshift, rotation, xcenter, ycenter;
			try
			{
				xshift = ::Convert::ToDouble(UserXShiftTxt->Text);
				yshift = ::Convert::ToDouble(UserYShiftTxt->Text);
				xcenter = ::Convert::ToDouble(UserRotationXCenterTxt->Text);
				ycenter = ::Convert::ToDouble(UserRotationYCenterTxt->Text);
				rotation = ::Convert::ToDouble(UserRotationTxt->Text)*Math::PI/180;//degrees to radians
			}
			catch (...)
			{
				::MessageBox::Show("There seems to be something wrong with one of the shift/rotate values.  Please check and try again.","Error...");
				return;
			}
		}

		if (GeneralTransformChck->Checked)
		{
			double xshift, yshift, xcenter, ycenter, TCA, TCB, TCC, TCD;
			try
			{
				xshift = ::Convert::ToDouble(TransformShiftXTxt->Text);
				yshift = ::Convert::ToDouble(TransformShiftYTxt->Text);
				xcenter = ::Convert::ToDouble(TransformCenterXTxt->Text);
				ycenter = ::Convert::ToDouble(TransformCenterYTxt->Text);
				TCA = ::Convert::ToDouble(TransformCoefATxt->Text);
				TCB = ::Convert::ToDouble(TransformCoefBTxt->Text);
				TCC = ::Convert::ToDouble(TransformCoefCTxt->Text);
				TCD = ::Convert::ToDouble(TransformCoefDTxt->Text);
			}
			catch (...)
			{
				::MessageBox::Show("There seems to be something wrong with one of the shift/rotate values.  Please check and try again.","Error...");
				return;
			}
		}

		UVITMenu->HideDropDown();
		ShiftAndRotateMenuItem->HideDropDown();
		UserDefinedShiftRotateMenuItem->HideDropDown();

		OpenFileDialog^ dlg = gcnew OpenFileDialog();
		dlg->InitialDirectory = dir;
		dlg->Filter = "FITS (*.fits)|*.fits";
		dlg->Multiselect = true;
		dlg->Title = "Select the Centroid INTEGERS List (_XYInts_List)";
		::DialogResult res = dlg->ShowDialog();
		if (res != ::DialogResult::OK)
			return;

		FileNames = dlg->FileNames;
		UVCONVERTLISTTOIMAGEBATCHFILES = gcnew array<String^>(FileNames->Length);
	}
	else
	{
		FileNames = UVNUVTOFUVFILES;
		UVCONVERTLISTTOIMAGEBATCHFILES = gcnew array<String^>(UVNUVTOFUVFILES->Length);
		UVNUVTOFUV = false;
	}
	
	String^ IntsFile = FileNames[0];
	int ind = IntsFile->LastIndexOf("\\");
	dir = IntsFile->Substring(0,ind);
	SetReg("CCDLAB", "L2EventListPath",dir);

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = FileNames->Length;
	WAITBAR->Text = "Transforming centroid list(s)...";
	RotationUVCentroidWrkr->RunWorkerAsync(FileNames);
	WAITBAR->ShowDialog();
}

void Form1::RotationUVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ IntsFiles = (array<String^>^)e->Argument;

	int n = omp_get_max_threads();
	array<int>^ count = gcnew array<int>(n);
	int prog = 0;

	#pragma omp parallel for
	for (int wrkri = 0; wrkri < IntsFiles->Length; wrkri++)
	{
		try
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				break;

			count[omp_get_thread_num()]++;
			#pragma omp critical
			{
				int sum = 0;
				for (int si = 0; si < count->Length; si++)
					sum += count[si];
				RotationUVCentroidWrkr->ReportProgress(sum);
			}
			//RotationUVCentroidWrkr->ReportProgress(wrkri);

			String^ IntsFile = IntsFiles[wrkri];
			String^ FracFile = IntsFile->Replace("Ints", "Frac");
			JPFITS::FITSImage^ IntsFits = gcnew JPFITS::FITSImage(IntsFile, nullptr, true, true, false, true);
			JPFITS::FITSImage^ FracFits = gcnew JPFITS::FITSImage(FracFile, nullptr, true, true, false, true);
			int NPts = FracFits->Height;
			double x, y, xprime, yprime;
			int fracx, intsx, fracy, intsy;
			::Random^ r = gcnew Random();

			if (LinearRotationChck->Checked)
			{
				double xshift, yshift, rotation, xcenter, ycenter;
				xshift = ::Convert::ToDouble(UserXShiftTxt->Text);
				yshift = ::Convert::ToDouble(UserYShiftTxt->Text);
				xcenter = ::Convert::ToDouble(UserRotationXCenterTxt->Text);
				ycenter = ::Convert::ToDouble(UserRotationYCenterTxt->Text);
				rotation = -1 * ::Convert::ToDouble(UserRotationTxt->Text) * Math::PI / 180;//degrees to radians

				bool horzflip = FlipHorizontalMenuItem->Checked;
				bool vertflip = FlipVerticalMenuItem->Checked;

				for (int j = 0; j < NPts; j++)
				{
					x = (IntsFits[0, j] + FracFits[0, j] + 16) + r->NextDouble();//must add 16 to fractionals
					y = (IntsFits[1, j] + FracFits[1, j] + 16) + r->NextDouble();//and put the centroid somewhere within the 1/32 bin

					if (horzflip)
						x = 511 * 32 - x;
					if (vertflip)
						y = 511 * 32 - y;

					xprime = (x - xcenter * 32) * Math::Cos(rotation) - (y - ycenter * 32) * Math::Sin(rotation) + xcenter * 32 + xshift * 32;
					yprime = (x - xcenter * 32) * Math::Sin(rotation) + (y - ycenter * 32) * Math::Cos(rotation) + ycenter * 32 + yshift * 32;

					//now need to split out integer and decimal parts back into their own lists...
					intsx = Math::DivRem(int((xprime)), 32, fracx) * 32;
					fracx -= 16;//reset frac to be from -16
					intsy = Math::DivRem(int((yprime)), 32, fracy) * 32;
					fracy -= 16;//reset frac to be from -16
					IntsFits[0, j] = intsx;
					IntsFits[1, j] = intsy;
					FracFits[0, j] = fracx;
					FracFits[1, j] = fracy;
				}

				if (horzflip)
				{
					IntsFits->AddKey("HORZFLIP", "true", "Image Flipped Horizontally", -1);
					FracFits->AddKey("HORZFLIP", "true", "Image Flipped Horizontally", -1);
				}
				if (vertflip)
				{
					IntsFits->AddKey("VERTFLIP", "true", "Image Flipped Vertically", -1);
					FracFits->AddKey("VERTFLIP", "true", "Image Flipped Vertically", -1);
				}
				if (xshift != 0)
				{
					IntsFits->AddKey("XSHIFT", xshift.ToString(), "Centroids X-Shift", -1);
					FracFits->AddKey("XSHIFT", xshift.ToString(), "Centroids X-Shift", -1);
				}
				if (yshift != 0)
				{
					IntsFits->AddKey("YSHIFT", yshift.ToString(), "Centroids Y-Shift", -1);
					FracFits->AddKey("YSHIFT", yshift.ToString(), "Centroids Y-Shift", -1);
				}
				if (rotation != 0)
				{
					IntsFits->AddKey("ROTATN", (-rotation).ToString(), "Centroids Rotation Angle", -1);
					FracFits->AddKey("ROTATN", (-rotation).ToString(), "Centroids Rotation Angle", -1);
				}

				if (UVIT_DEROTATE_WCS)//then use WCS coordinates from header to automatically re-do the WCS solution
				{
					WCS_DEROT->CopyTo(IntsFits);
					WCS_DEROT->CopyTo(FracFits);

					//rotate and shift the exposure array image so that it matches the WCS derotated aspect
					String^ dedrift = "_deDrift";
					while (IntsFile->Contains(dedrift + "_deDrift"))
						dedrift += "_deDrift";
					String^ exparrayimagefile = IntsFile->Remove(IntsFile->IndexOf("XYInts")) + "ExpArrayImg";
					exparrayimagefile += dedrift + ".fits";
					FITSImage^ expfitsimg = gcnew FITSImage(exparrayimagefile, nullptr, true, true, false, true);
					array<double, 2>^ exparr = expfitsimg->Image;
					exparr = JPMath::RotateShiftArray(exparr, -rotation, Double::MaxValue, Double::MaxValue, "bilinear", 0, 0, true);
					expfitsimg->SetImage(exparr, false, true);
					expfitsimg->WriteImage(::TypeCode::Double, true);
				}

				IntsFile = IntsFile->Insert(IntsFile->LastIndexOf("."), "_FSRL");
				IntsFits->WriteImage(IntsFile, ::TypeCode::Int16, true);
				FracFile = FracFile->Insert(FracFile->LastIndexOf("."), "_FSRL");
				FracFits->WriteImage(FracFile, ::TypeCode::Int16, true);
			}

			if (GeneralTransformChck->Checked)
			{
				double xshift, yshift, xcenter, ycenter, TCA, TCB, TCC, TCD;
				xshift = ::Convert::ToDouble(TransformShiftXTxt->Text);
				yshift = ::Convert::ToDouble(TransformShiftYTxt->Text);
				xcenter = ::Convert::ToDouble(TransformCenterXTxt->Text);
				ycenter = ::Convert::ToDouble(TransformCenterYTxt->Text);
				TCA = ::Convert::ToDouble(TransformCoefATxt->Text);
				TCB = ::Convert::ToDouble(TransformCoefBTxt->Text);
				TCC = ::Convert::ToDouble(TransformCoefCTxt->Text);
				TCD = ::Convert::ToDouble(TransformCoefDTxt->Text);

				for (int j = 0; j < NPts; j++)
				{
					x = (IntsFits[0, j] + FracFits[0, j] + 16) + r->NextDouble();//must add 16 to fractionals
					y = (IntsFits[1, j] + FracFits[1, j] + 16) + r->NextDouble();//and put the centroid somewhere within the 1/32 bin

					xprime = (x - xcenter * 32) * TCA + (y - ycenter * 32) * TCB + xcenter * 32 + xshift * 32;
					yprime = (x - xcenter * 32) * TCC + (y - ycenter * 32) * TCD + ycenter * 32 + yshift * 32;

					//now need to split out integer and decimal parts back into their own lists...
					intsx = Math::DivRem(int((xprime)), 32, fracx) * 32;
					fracx -= 16;//reset frac to be from -16
					intsy = Math::DivRem(int((yprime)), 32, fracy) * 32;
					fracy -= 16;//reset frac to be from -16
					IntsFits[0, j] = intsx;
					IntsFits[1, j] = intsy;
					FracFits[0, j] = fracx;
					FracFits[1, j] = fracy;
				}

				//now give the shifted/rotated list a new name and save
				IntsFile = IntsFile->Insert(IntsFile->LastIndexOf("."), "_FSRG");
				IntsFits->WriteImage(IntsFile, ::TypeCode::Int16, true);
				FracFile = FracFile->Insert(FracFile->LastIndexOf("."), "_FSRG");
				FracFits->WriteImage(FracFile, ::TypeCode::Int16, true);
			}

			UVCONVERTLISTTOIMAGEBATCHFILES[wrkri] = IntsFile;
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
		}
	}
}

void Form1::RotationUVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->TextMsg->Text = "Transforming file " + (e->ProgressPercentage).ToString() + " of " + WAITBAR->ProgressBar->Maximum.ToString();
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->Refresh();
}

void Form1::RotationUVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		Form1::Enabled = true;
		return;
	}

	if (!UVIT_DEROTATE_WCS && MessageBox::Show("Completed shifting/rotating the centroid list(s).  Would you like to convert to image(s)?", "Images?", MessageBoxButtons::YesNo) == ::DialogResult::No)
	{
		WAITBAR->Hide();
		WAITBAR->Close();
		Form1::Enabled = true;
		return;
	}
	
	//now create the images...automatic if UVIT_DEROTATE_WCS
	ConvertListToImgMenu_DropDownOpened(sender, e);
	ConvertListToImgMenu->HideDropDown();
	UVCONVERTLISTTOIMAGEBATCH = true;
	AUTOLOADIMAGESFILES = gcnew array<String^>(UVCONVERTLISTTOIMAGEBATCHFILES->Length);

	WAITBAR->ProgressBar->Value = 0;
	WAITBAR->ProgressBar->Maximum = UVCONVERTLISTTOIMAGEBATCHFILES->Length;
	WAITBAR->Text = "Creating image(s)...";
	ConvertUVCentroidListToImgWrkr->RunWorkerAsync(UVCONVERTLISTTOIMAGEBATCHFILES);
}

void Form1::DeRotateViaWCS_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (MessageBox::Show("CURRENT image OK to base derotation upon?", "CURRENT IMAGE AS REFERENCE?", MessageBoxButtons::YesNo) == ::DialogResult::No)
	{
		UVIT_DEROTATE_FILES = nullptr;
		return;
	}

	//need to get the most recent/longest filename XYInts files for each image
	UVIT_DEROTATE_FILES = gcnew array<String^>(IMAGESET->Count);
	for (int i = 0; i < UVIT_DEROTATE_FILES->Length; i++)
	{
		array<String^>^ xyintsfiles = Directory::GetFiles(IMAGESET[i]->FilePath, "*XYInts*.fits");
		UVIT_DEROTATE_FILES[i] = xyintsfiles[0];
		for (int j = 1; j < xyintsfiles->Length; j++)
			if (xyintsfiles[j]->Length > UVIT_DEROTATE_FILES[i]->Length)
				UVIT_DEROTATE_FILES[i] = xyintsfiles[j];
	}

	//make the reference file the first, so that when it goes to ConvertUVCentroidListToImgWrkr the first image get re-PSE'd given the CPIX transform below and the new PSE is then used to create the new derotated WCS and for the following images
	if (FILELISTINDEX != 0)
	{
		String^ temp = UVIT_DEROTATE_FILES[0];
		UVIT_DEROTATE_FILES[0] = UVIT_DEROTATE_FILES[FILELISTINDEX];
		UVIT_DEROTATE_FILES[FILELISTINDEX] = temp;
	}

	UVIT_DEROTATE_WCS = true;
	LinearRotationChck->Checked = true;
	FlipHorizontalMenuItem->Checked = false;
	FlipVerticalMenuItem->Checked = false;
	UserXShiftTxt->Text = "0";
	UserYShiftTxt->Text = "0";
	UserRotationXCenterTxt->Text = "255";
	UserRotationYCenterTxt->Text = "255";
	UserRotationTxt->Text = Convert::ToString(-(WCS->CROTAn[1] + WCS->CROTAn[2]) / 2);
	UVCONVERTLISTTOIMAGEBATCHFILES = gcnew array<String^>(UVIT_DEROTATE_FILES->Length);//pre-make

	/////////////////////////////////
	//rotate/shift the WCS values in the header so that the image creator can then use those to determine new PSE on them and make new derotated WCS
	double xshift = ::Convert::ToDouble(UserXShiftTxt->Text);
	double yshift = ::Convert::ToDouble(UserYShiftTxt->Text);
	double xcenter = ::Convert::ToDouble(UserRotationXCenterTxt->Text);
	double ycenter = ::Convert::ToDouble(UserRotationYCenterTxt->Text);
	double rotation = -1 * ::Convert::ToDouble(UserRotationTxt->Text) * Math::PI / 180;//degrees to radians
	WCS_DEROT = gcnew JPFITS::WorldCoordinateSolution();
	WCS_DEROT->Get_WCS(IMAGESET[FILELISTINDEX]);
	double prec = 1;//check for the image precision...
	String^ strprec = IMAGESET[FILELISTINDEX]->GetKeyValue("IMAGPREC");
	if (strprec != "")
	prec = ::Convert::ToDouble(strprec);
	double offset = 0;
	String^ stroffset = IMAGESET[FILELISTINDEX]->GetKeyValue("PADOFSET");
	if (stroffset != "")
	offset = ::Convert::ToDouble(stroffset);
	for (int j = 0; j < WCS_DEROT->Coordinate_Pixels[1]->Length; j++)
	{
		double x = ((array<double>^)WCS_DEROT->Coordinate_Pixels[1])[j];
		double y = ((array<double>^)WCS_DEROT->Coordinate_Pixels[2])[j];
		double xprime = (x / prec * 32 - (xcenter + offset) * 32) * Math::Cos(rotation) - (y / prec * 32 - (ycenter + offset) * 32) * Math::Sin(rotation) + (xcenter + offset) * 32 + xshift * 32;
		double yprime = (x / prec * 32 - (xcenter + offset) * 32) * Math::Sin(rotation) + (y / prec * 32 - (ycenter + offset) * 32) * Math::Cos(rotation) + (ycenter + offset) * 32 + yshift * 32;
		xprime /= (32 / prec);
		yprime /= (32 / prec);
		((array<double>^)WCS_DEROT->Coordinate_Pixels[1])[j] = xprime;
		((array<double>^)WCS_DEROT->Coordinate_Pixels[2])[j] = yprime;
	}
	/////////////////////////////////
	
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = UVIT_DEROTATE_FILES->Length;
	WAITBAR->Text = "de-Rotating centroid list(s)...";
	RotationUVCentroidWrkr->RunWorkerAsync(UVIT_DEROTATE_FILES);
	WAITBAR->ShowDialog();
}

void Form1::INTAtoINTADriftCorrectionMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = false;

	dlg->Title = "Select the DRIFT List (_XYDrift_List)";
	dlg->Filter = "DRIFT (*.drift)|*.drift";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;
	String^ driftlistfile = dlg->FileName;
	dir = driftlistfile->Substring(0,driftlistfile->LastIndexOf("\\"));
	SetReg("CCDLAB", "L2EventListPath", dir);

	::FolderBrowserDialog^ fdlg = gcnew FolderBrowserDialog();
	fdlg->SelectedPath = dir;
	fdlg->Description = "Select the folder of the INT-mode *.fits image files to be drift corrected...";
	res = fdlg->ShowDialog();
	if (res == ::DialogResult::Cancel)
		return;
	array<String^>^ filelist = Directory::GetFiles(fdlg->SelectedPath,"*.fits",::SearchOption::TopDirectoryOnly);
	if (filelist->Length == 0)
	{
		::MessageBox::Show("No files found in that directory.","Error");
		return;
	}
	SetReg("CCDLAB", "FolderBrowserPath",fdlg->SelectedPath);

	array<double, 2>^ drifts = FITSImage::ReadImageArrayOnly(driftlistfile, nullptr, true);
	if (filelist->Length != drifts->GetLength(1))
	{
		MessageBox::Show("Number of drift measurements not equal to number of files in the directory.  Check your work.","Error...");
		return;
	}

	String^ savepath = fdlg->SelectedPath + "\\" + "de-drifted";
	Directory::CreateDirectory(savepath);
	SetReg("CCDLAB", "FolderBrowserPath",savepath);

	array<Object^>^ arg = gcnew array<Object^>(3);
	arg[0] = (Object^)driftlistfile;
	arg[1] = (Object^)fdlg->SelectedPath;
	arg[2] = (Object^)savepath;
	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->DialogResult = ::DialogResult::OK;
	WAITBAR->Text = "Applying Drift Correction...";
	INTAtoINTAapplyDriftWrkr->RunWorkerAsync(arg);
	WAITBAR->Show();
}

void Form1::INTAtoINTAapplyDriftWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<Object^>^ arg = (array<Object^>^)e->Argument;
	String^ driftlistfile = (String^)arg[0];
	String^ driftlistpath = (String^)arg[1];
	String^ savepath      = (String^)arg[2];

	array<double, 2>^ drifts = FITSImage::ReadImageArrayOnly(driftlistfile, nullptr, true);
	array<String^>^ filelist = Directory::GetFiles(driftlistpath, "*.fits", ::SearchOption::TopDirectoryOnly);

	for (int i = 0; i < filelist->Length; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;
		INTAtoINTAapplyDriftWrkr->ReportProgress(100*i/filelist->Length);

		FITSImage^ fits = gcnew FITSImage(filelist[i], nullptr, true, true, false, true);
		fits->SetImage(JPMath::ShiftArrayInt(fits->Image, -int(drifts[1, i]) / 32, -int(drifts[2, i]) / 32, true), false, true);//or round instead of int?
		String^ name = savepath + "\\" + fits->FileName;
		name = name->Replace(".fits","_deDrift.fits");
		fits->WriteImage(name, ::TypeCode::Int16, true);
	}
}

void Form1::INTAtoINTAapplyDriftWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = String::Concat("Completed: ",e->ProgressPercentage,"%");
	WAITBAR->Refresh();//find all Update() and replace with Refresh()
}

void Form1::INTAtoINTAapplyDriftWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;
	Form1::BringToFront();

	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
		return;

	::MessageBox::Show("Completed drift-correcting the INT-mode images.");
}

void Form1::GeneralUVRegistrationMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!UVREGISTRATION)
	{
		UVITMenu->HideDropDown();
		GeneralUVRegistrationMenuItem->HideDropDown();

		array<String^>^ xyintsfiles;

		if (RegistrationXYIntsListFolderScanChck->Checked)
		{
			FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
			fbd->SelectedPath = (String^)GetReg("CCDLAB", "L2EventListPath");
			if (DirectoryInfo(fbd->SelectedPath).Name == "VIS")
				fbd->SelectedPath = Path::GetDirectoryName(fbd->SelectedPath);
			fbd->Description = "Select the folder to scan for the most recent INTEGERS Lists (_XYInts_List)";
			if (fbd->ShowDialog() == ::DialogResult::Cancel)
				return;
			SetReg("CCDLAB", "L2EventListPath", fbd->SelectedPath);
			SetReg("CCDLAB", "OpenFilesPath", fbd->SelectedPath);
			
			//only want to register the most recent xyintsfiles so must go through and sort this out
			//each XYInts file will be in its own directory, and this is where its dupes will be
			//we want only the most recent (longest file name length) dupe from each directory
			//when registering can only do so on deDrift files, so if there are directories that couldn't be deDrift, don't use those files
			xyintsfiles = Directory::GetFiles(fbd->SelectedPath, "*MASTER*XYInts_List*deDrift*.fits", SearchOption::AllDirectories);
			if (xyintsfiles->Length == 0)//only do MASTER if these are available
				xyintsfiles = Directory::GetFiles(fbd->SelectedPath, "*XYInts_List*deDrift*.fits", SearchOption::AllDirectories);
			Array::Sort(xyintsfiles);
			if (xyintsfiles->Length == 0)
			{
				::MessageBox::Show("No files found...", "Error...");
				return;
			}
			int c = 0;
			for (int i = 0; i < xyintsfiles->Length; i++)
			{
				String^ curdir = Path::GetDirectoryName(xyintsfiles[i]);
				array<String^>^ dirxyfiles = Directory::GetFiles(curdir, "*XYInts_List*deDrift*.fits");
				int ind = 0;
				for (int j = 1; j < dirxyfiles->Length; j++)
					if (dirxyfiles[j]->Length > dirxyfiles[ind]->Length)
						ind = j;

				xyintsfiles[c] = dirxyfiles[ind];
				c++;
				i += dirxyfiles->Length - 1;
			}
			Array::Resize(xyintsfiles, c);
		}
		else
		{
			String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
			OpenFileDialog^ dlg = gcnew OpenFileDialog();
			dlg->InitialDirectory = dir;
			dlg->Filter = "FITS (*.fits)|*.fits";
			dlg->Multiselect = true;
			dlg->Title = "Select the Centroid INTEGERS Lists (_XYInts_List)";
			::DialogResult res = dlg->ShowDialog();
			if (res != ::DialogResult::OK)
				return;

			xyintsfiles = dlg->FileNames;

			dir = dlg->FileNames[0]->Substring(0, dlg->FileNames[0]->LastIndexOf("\\"));
			dir = dir->Substring(0, dir->LastIndexOf("\\"));//this is the upper dir containing all sub orbit directories
			SetReg("CCDLAB", "L2EventListPath", dir);
			SetReg("CCDLAB", "OpenFilesPath", dir);
		}

		if (xyintsfiles->Length == 1)
		{
			::MessageBox::Show("Need to select more than 1 file for image registration...", "Error...");
			return;
		}

		if (MessageBox::Show("Please select point sources (LEFT-CLICK) which stay within the field of view for the duration of the image set!  RIGHT-CLICK when done.", "Centroid List Registration...", ::MessageBoxButtons::OKCancel) == ::DialogResult::Cancel)
			return;

		if (UVGeneralRegistrationResolutionDrop->SelectedIndex == 2)
			ListToImage4PixMenuItem->PerformClick();
		if (UVGeneralRegistrationResolutionDrop->SelectedIndex == 1)
			ListToImage2PixMenuItem->PerformClick();
		if (UVGeneralRegistrationResolutionDrop->SelectedIndex == 0)
			ListToImage1PixMenuItem->PerformClick();
		UVITMenu->HideDropDown();
		ConvertListToImgMenu->HideDropDown();

		IWLCK = false;//allow cursor box to move
		//ImageWindow->Cursor->Hide();
		EqualHWChck->Checked = true;
		HalfWidthXUpD->Value = UVLISTTOIMAGEPREC * 10 / 2;
		FNDCOORDS = gcnew array<int, 2>(1, 2);//this is for plotting the local max point in the ROI
		FNDCOORDRECTS = gcnew array<Rectangle, 1>(1);
		ShowFoundCoordsChck->Checked = true;//this is for plotting the local max point in the ROI
		MANREGCOORDS = gcnew array<int, 2>(0, 0);
		MANREGCOORDRECTS = gcnew array<Rectangle, 1>(0);

		UVREGISTRATION = true;
		UVREGISTRATIONFILES = xyintsfiles;
		if (masterizeSinglesToolStripMenuItem->Checked)
			for (int i = 0; i < UVREGISTRATIONFILES->Length; i++)
				if (UVREGISTRATIONFILES[i]->Contains("_MASTER_"))
					continue;
				else
				{
					String^ filedir = Path::GetDirectoryName(UVREGISTRATIONFILES[i]);
					String^ pardir = Directory::GetParent(filedir)->FullName;
					if (Directory::GetDirectories(pardir)->Length == 1)
					{
						int indlast = UVREGISTRATIONFILES[i]->IndexOf("_XYInts");
						String^ test = UVREGISTRATIONFILES[i]->Substring(0, indlast - 1);
						int indfirst = test->LastIndexOf("_");
						test = UVREGISTRATIONFILES[i]->Substring(0, indfirst - 1);
						indfirst = test->LastIndexOf("_") + 1;
						String^ replacestr = UVREGISTRATIONFILES[i]->Substring(indfirst, indlast - indfirst);

						array<String^>^ dirfiles = Directory::GetFiles(filedir);
						for (int j = 0; j < dirfiles->Length; j++)
						{
							String^ newfile = dirfiles[j]->Replace(replacestr, "__MASTER__");
							newfile = pardir + "\\" + newfile->Substring(newfile->LastIndexOf("\\"));
							File::Move(dirfiles[j], newfile);
							if (dirfiles[j] == UVREGISTRATIONFILES[i])
								UVREGISTRATIONFILES[i] = newfile;
						}
						Directory::Delete(filedir, true);
					}
				}
		UVREGISTRATIONFILESINDEX = 0;
		UVREGISTRATION_CENTROIDS = nullptr;
		UVCREATEIMAGEFILENAME = UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX];
		UVAutoDriftImageViewChck->Checked = true;
		UVCREATEIMAGENOW = true;
		UVREGISTRATION_ANCHOR_INDEX = Int32::MaxValue;
		UVREGISTRATION_ROTATION_INDEX = Int32::MaxValue;

		ProgressBar->Value = 0;
		ProgressBar->Maximum = 2;
		ProgressBar->Value = 1;
		ProgressBar->Refresh();
		ConvertListToImgMenu_Click(sender,e);

		return;
	}

	if (UVREGISTRATION && MANREGCOORDRECTS->Length == 0)//clicked out without any point selections
	{		
		UVREGISTRATION = false;
		ShowFoundCoordsChck->Checked = false;
		ImageWindow->Cursor->Show();
		ImageWindow->Refresh();
		ListToImage8PixMenuItem->PerformClick();
		UVITMenu->HideDropDown();
		ConvertListToImgMenu->HideDropDown();
		ProgressBar->Value = 0;
		return;
	}

	if (UVREGISTRATION && UVREGISTRATIONFILESINDEX < UVREGISTRATIONFILES->Length - 1)
	{
		::DialogResult res;
		if (UVITAUTOREGISTER)
			res = ::DialogResult::Yes;
		else
			res = MessageBox::Show("Continue to image " + (UVREGISTRATIONFILESINDEX + 2).ToString() + " of " + (UVREGISTRATIONFILES->Length).ToString() + "?", "Centroid List Registration...", ::MessageBoxButtons::YesNoCancel);
		
		if (res == ::DialogResult::Cancel)//stop registration
		{
			UVREGISTRATION = false;
			UVREGISTRATIONFILES = nullptr;
			ShowFoundCoordsChck->Checked = false;//this is for plotting the local max point in the ROI
			ImageWindow->Cursor->Show();
			ImageWindow->Cursor = ::Cursors::Cross;
			ShowCursorBox->Checked = true;
			ImageWindow->Refresh();

			ListToImage8PixMenuItem->PerformClick();
			UVITMenu->HideDropDown();
			ConvertListToImgMenu->HideDropDown();

			ProgressBar->Value = 0;

			return;
		}

		if (res == ::DialogResult::No)//keep moving points
			return;

		//else it is yes
		ShowFoundCoordsChck->Checked = false;//this is for plotting the local max point in the ROI...the selected MANREGCOORS are still plotted
		//ShowCursorBox->Checked = false;
		ImageWindow->Cursor = ::Cursors::Hand;
		ImageWindow->Cursor->Show();

		UVREGISTRATION_TRANSLATE = true;
		UVREGISTRATION_ROTATION_PHI = 0;

		UVREGISTRATIONFILESINDEX++;
		UVCREATEIMAGEFILENAME = UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX];
		UVCREATEIMAGENOW = true;

		//if re-registering from an earlier registered list, then it means that the last registration (or more) was no good.
		//hence should delete ALL of those files in order to start again from here
		String^ regs = "_RGSTRD";
		while (UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX - 1]->Contains(regs))
			regs += "_RGSTRD";
		//higher iteration registrations must go.  they are given regs
		array<String^>^ delfiles = ::Directory::GetFiles(UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX - 1]->Substring(0, UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX - 1]->LastIndexOf("\\")), "*" + regs + "*");
		for (int i = 0; i < delfiles->Length; i++)
			::File::Delete(delfiles[i]);

		//MessageBox::Show(res.ToString());
		if (!UVITAUTOREGISTER)
		{
			ProgressBar->Value = 0;
			ProgressBar->Maximum = 2;
			ProgressBar->Value = 1;
			ProgressBar->Refresh();
		}
		ConvertListToImgMenu_Click(sender, e);
		
		return;
	}

	if (UVREGISTRATION && UVREGISTRATIONFILESINDEX == UVREGISTRATIONFILES->Length - 1)//now compute the transformations and apply them to the centroid lists
	{
		//if re-registering from an earlier registered list, then it means that the last registration (or more) was no good.
		//hence should delete ALL of those files in order to start again from here
		String^ regs = "_RGSTRD";
		while (UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX]->Contains(regs))
			regs += "_RGSTRD";
		//higher iteration registrations must go.  they are given regs
		array<String^>^ delfiles = ::Directory::GetFiles(UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX]->Substring(0, UVREGISTRATIONFILES[UVREGISTRATIONFILESINDEX]->LastIndexOf("\\")), "*" + regs + "*");
		for (int i = 0; i < delfiles->Length; i++)
			::File::Delete(delfiles[i]);

		UVREGISTRATION = false;
		ShowFoundCoordsChck->Checked = false;
		ShowCursorBox->Checked = true;
		ImageWindow->Cursor = ::Cursors::Cross;
		ProgressBar->Value = 0;
		ImageWindow->Refresh();

		if (!UVITAUTOREGISTER)
			if (::MessageBox::Show("Determine and apply the registration tranformation(s)?", "Centroid Registration...", ::MessageBoxButtons::YesNo) == ::DialogResult::No)
				return;
		UVITAUTOREGISTER = false;

		UVCONVERTLISTTOIMAGEBATCHFILES = gcnew array<String^>(UVREGISTRATIONFILES->Length);
		AUTOLOADIMAGESFILES = gcnew array<String^>(UVREGISTRATIONFILES->Length);

		Form1::Enabled = false;
		WAITBAR = gcnew JPWaitBar::WaitBar();
		WAITBAR->ProgressBar->Maximum = UVREGISTRATIONFILES->Length;
		WAITBAR->Text = "Registration...";
		WAITBAR->ProgressBar->Value = 1;
		WAITBAR->TextMsg->Text = "Wait a sec while I make a copy of the reference file...";
		RegistrationUVCentroidWrkr->RunWorkerAsync();
		WAITBAR->Show();
	}
}

void Form1::RegistrationUVCentroidWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	try
	{
		//update first reference files
		String^ IntsFile = UVREGISTRATIONFILES[0];
		String^ FracFile = UVREGISTRATIONFILES[0]->Replace("Ints","Frac");
		::File::Copy(IntsFile, IntsFile->Insert(IntsFile->LastIndexOf("."),"_RGSTRD"), true);
		::File::SetLastWriteTime(IntsFile->Insert(IntsFile->LastIndexOf("."),"_RGSTRD"),::DateTime::Now);
		::File::Copy(FracFile, FracFile->Insert(FracFile->LastIndexOf("."),"_RGSTRD"), true);
		::File::SetLastWriteTime(FracFile->Insert(FracFile->LastIndexOf("."),"_RGSTRD"),::DateTime::Now);
		UVCONVERTLISTTOIMAGEBATCHFILES[0] = IntsFile->Insert(IntsFile->LastIndexOf("."),"_RGSTRD");

		String^ dedrift = "_deDrift";
		while (IntsFile->Contains(dedrift + "_deDrift"))
			dedrift += "_deDrift";
		String^ exparrayimagefile = IntsFile->Remove(IntsFile->IndexOf("XYInts")) + "ExpArrayImg";
		exparrayimagefile += dedrift + ".fits";
		::File::SetLastWriteTime(exparrayimagefile, ::DateTime::Now);

		//set up arrays
		array<double>^ xref = gcnew array<double>(UVREGISTRATION_CENTROIDS->GetLength(1));
		array<double>^ yref = gcnew array<double>(UVREGISTRATION_CENTROIDS->GetLength(1));
		for (int j = 0; j < UVREGISTRATION_CENTROIDS->GetLength(1); j++)
		{
			xref[j] = UVREGISTRATION_CENTROIDS[0, j, 0];
			yref[j] = UVREGISTRATION_CENTROIDS[0, j, 1];
		}

		int n = omp_get_max_threads();
		array<int>^ count = gcnew array<int>(n);
		int prog = 1;

		#pragma omp parallel for
		for (int i = 1; i < UVREGISTRATIONFILES->Length; i++)
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				break;

			count[omp_get_thread_num()]++;
			#pragma omp critical
			{
				int sum = 0;
				for (int si = 0; si < count->Length; si++)
					sum += count[si];
				if (sum * 100 / UVREGISTRATIONFILES->Length > prog)
				{
					RegistrationUVCentroidWrkr->ReportProgress(sum);
					prog = sum * 100 / UVREGISTRATIONFILES->Length;
				}
			}

			String^ IntsFile = UVREGISTRATIONFILES[i];
			String^ FracFile = IntsFile->Replace("Ints","Frac");
			JPFITS::FITSImage^ IntsFits = gcnew JPFITS::FITSImage(IntsFile, nullptr, true, true, false, false);
			JPFITS::FITSImage^ FracFits = gcnew JPFITS::FITSImage(FracFile, nullptr, true, true, false, false);
			int NPts = FracFits->Height;
			double x, y, xprime, yprime, xshift = 0, yshift = 0, rotation = 0, xcenter = 0, ycenter = 0;
			int fracx, intsx, fracy, intsy;
			::Random^ r = gcnew Random();
			array<double>^ xtran = gcnew array<double>(UVREGISTRATION_CENTROIDS->GetLength(1));
			array<double>^ ytran = gcnew array<double>(UVREGISTRATION_CENTROIDS->GetLength(1));
			array<double>^ P0;
			array<double>^ Plb;
			array<double>^ Pub;
			array<double>^ Psc;

			for (int j = 0; j < UVREGISTRATION_CENTROIDS->GetLength(1); j++)
			{
				xtran[j] = UVREGISTRATION_CENTROIDS[i, j, 0];
				ytran[j] = UVREGISTRATION_CENTROIDS[i, j, 1];
			}

			if (xref->Length == 1)//just single points for shifting
			{
				xshift = -(xtran[0] - xref[0]) * 32 / double(UVLISTTOIMAGEPREC);
				yshift = -(ytran[0] - yref[0]) * 32 / double(UVLISTTOIMAGEPREC);

				//MessageBox::Show("1: " + xshift + " " + yshift);

				for (int j = 0; j < NPts; j++)
				{
					x = (IntsFits[0,j] + FracFits[0,j] + 16) + r->NextDouble();//must add 16 to fractionals
					y = (IntsFits[1,j] + FracFits[1,j] + 16) + r->NextDouble();//and put the centroid somewhere within the 1/32 bin

					xprime = x + xshift;
					yprime = y + yshift;

					//now need to split out integer and decimal parts back into their own lists...
					intsx = Math::DivRem(int((xprime)), 32, fracx) * 32;
					fracx -= 16;//reset frac to be from -16
					intsy = Math::DivRem(int((yprime)), 32, fracy) * 32;
					fracy -= 16;//reset frac to be from -16
					IntsFits[0, j] = intsx;
					IntsFits[1, j] = intsy;
					FracFits[0, j] = fracx;
					FracFits[1, j] = fracy;
				}
			}

			if (xref->Length > 1)//then have 2-D points for rotation tranformation
			{
				//MessageBox::Show("1: " + UVREGISTRATION_THETAS[i] + " " + rotation);

				P0 = gcnew array<double>(6) { 1, UVREGISTRATION_PHIS[i], UVREGISTRATION_XCENTERS[i], UVREGISTRATION_YCENTERS[i], UVREGISTRATION_XSHIFTS[i], UVREGISTRATION_YSHIFTS[i] };
				Plb = gcnew array<double>(6) { 1, UVREGISTRATION_PHIS[i] - Math::PI/8, UVREGISTRATION_XCENTERS[i] - 20, UVREGISTRATION_YCENTERS[i] - 20, UVREGISTRATION_XSHIFTS[i] - 20, UVREGISTRATION_YSHIFTS[i] - 20 };
				Pub = gcnew array<double>(6) { 1, UVREGISTRATION_PHIS[i] + Math::PI/8, UVREGISTRATION_XCENTERS[i] + 20, UVREGISTRATION_YCENTERS[i] + 20, UVREGISTRATION_XSHIFTS[i] + 20, UVREGISTRATION_YSHIFTS[i] + 20 };
				Psc = gcnew array<double>(6) { 1, 1, 1000, 1000, 50, 50 };
				JPMath::Fit_GeneralTransform2d(xref, yref, xtran, ytran, P0, Plb, Pub, Psc);
				rotation = P0[1];
				xcenter = P0[2];
				ycenter = P0[3];
				xshift = P0[4];
				yshift = P0[5];

				//MessageBox::Show("2: " + UVREGISTRATION_PHIS[i]*180/3.14159 + " " + rotation*180/3.14159 + " " + UVREGISTRATION_XSHIFTS[i] + " " + xshift + " " + UVREGISTRATION_YSHIFTS[i] + " " + yshift);
				
				bool general_transformation = false;//can only do rotation above if only 2 points
				if (xref->Length > 2)
					general_transformation = true;

				if (general_transformation)//now do general transformation using the linear transformation results as initial guess
				{
					P0 = gcnew array<double>(8) { Math::Cos(rotation), -Math::Sin(rotation), Math::Sin(rotation), Math::Cos(rotation), xcenter, ycenter, xshift, yshift };
					Plb = gcnew array<double>(8) { -1.1, -1.1, -1.1, -1.1, xcenter - 20, ycenter - 20, xshift - 20, yshift - 20 };
					Pub = gcnew array<double>(8) { 1.1, 1.1, 1.1, 1.1, xcenter + 20, ycenter + 20, xshift + 20, yshift + 20 };
					Psc = gcnew array<double>(8) { 1, 1, 1, 1, 1000, 1000, 50, 50 };
					JPMath::Fit_GeneralTransform2d(xref, yref, xtran, ytran, P0, Plb, Pub, Psc);
					xcenter = P0[4];
					ycenter = P0[5];
					xshift = P0[6];
					yshift = P0[7];
				}

				//MessageBox::Show("2: " + UVREGISTRATION_THETAS[i] * 180 / 3.14159 + " " + rotation * 180 / 3.14159 + " " + UVREGISTRATION_XSHIFTS[i] + " " + xshift + " " + UVREGISTRATION_YSHIFTS[i] + " " + yshift);

				xcenter *= (32 / double(UVLISTTOIMAGEPREC));
				ycenter *= (32 / double(UVLISTTOIMAGEPREC));
				xshift *= (32 / double(UVLISTTOIMAGEPREC));
				yshift *= (32 / double(UVLISTTOIMAGEPREC));

				for (int j = 0; j < NPts; j++)
				{
					x = (IntsFits[0,j] + FracFits[0,j] + 16) + r->NextDouble();//must add 16 to fractionals
					y = (IntsFits[1,j] + FracFits[1,j] + 16) + r->NextDouble();//and put the centroid somewhere within the 1/32 bin

					if (!general_transformation)
					{
						xprime = (x - xcenter)*Math::Cos(rotation) - (y - ycenter)*Math::Sin(rotation) + xcenter + xshift;
						yprime = (x - xcenter)*Math::Sin(rotation) + (y - ycenter)*Math::Cos(rotation) + ycenter + yshift;
					}
					else
					{
						xprime = (x - xcenter)*P0[0] + (y - ycenter)*P0[1] + xcenter + xshift;
						yprime = (x - xcenter)*P0[2] + (y - ycenter)*P0[3] + ycenter + yshift;
					}

					//now need to split out integer and decimal parts back into their own lists...
					intsx = Math::DivRem(int((xprime)), 32, fracx) * 32;
					fracx -= 16;//reset frac to be from -16
					intsy = Math::DivRem(int((yprime)), 32, fracy) * 32;
					fracy -= 16;//reset frac to be from -16
					IntsFits[0,j] = intsx;
					IntsFits[1,j] = intsy;
					FracFits[0,j] = fracx;
					FracFits[1,j] = fracy;
				}
			}

			IntsFile = IntsFile->Insert(IntsFile->LastIndexOf("."),"_RGSTRD");
			IntsFits->WriteImage(IntsFile,::TypeCode::Int16, false);
			FracFile = FracFile->Insert(FracFile->LastIndexOf("."),"_RGSTRD");
			FracFits->WriteImage(FracFile,::TypeCode::Int16, false);

			UVCONVERTLISTTOIMAGEBATCHFILES[i] = IntsFile;

			//rotate and shift the exposure array image so that it can be stacked later with merge
			//can rotate about center...then shift...all in JPMath
			//get the correct exposure map image
			String^ dedrift = "_deDrift";
			while (IntsFile->Contains(dedrift + "_deDrift"))
				dedrift += "_deDrift";
			String^ exparrayimagefile = IntsFile->Remove(IntsFile->IndexOf("XYInts")) + "ExpArrayImg";
			exparrayimagefile += dedrift + ".fits";

			FITSImage^ expfitsimg = gcnew FITSImage(exparrayimagefile, nullptr, true, true, false, false);
			array<double, 2>^ exparr = expfitsimg->Image;
			
			int res = 2;
			if (expfitsimg->GetKeyIndex("EXMAPRES") != -1)
				res = Convert::ToInt32(expfitsimg->GetKeyValue("EXMAPRES"));
			xshift *= (double(res) / 32);
			yshift *= (double(res) / 32);
			xcenter *= (double(res) / 32);
			ycenter *= (double(res) / 32);
			int pad = 44 * res;

			if (Math::Abs(rotation) > 0.000001 / 180 * Math::PI || xshift != 0 || yshift != 0)
				exparr = JPMath::RotateShiftArray(exparr, -rotation, xcenter + pad, ycenter + pad, "bilinear", (int)Math::Round(xshift), (int)Math::Round(yshift), false);
			expfitsimg->SetImage(exparr, false, false);
			expfitsimg->WriteImage(::TypeCode::Double, false);

			//The reason why you need to also shift the exposure array image and THEN create the new exposure list is because, at the edges, there would be differential
			//exposure times for each orbit relative to the combined orbits, just as with drift in a single orbit, for the merged images.
			//The exposure array images should be shifted and rotated as needed.
			//Then when the orbits are merged, the registered versions of the exposure array images should be combined too to get the master exposure list.
			//For example, if for one orbit an edge region was exposed for 0.9 of the total exposure time, this same region may not have been observed at all for all other orbits.
			//Therefore, the centroids there were not oberved for 0.9 of the entire exposure time, but 0.9 weighted for that orbits exposure time relative to the combined exposure time.
			//Even if a region in one orbit was fully exposed, it might not be exposed at all in later orbits.
			//Such a region's centroids have full weight for their own orbit, but for the combined orbits they should likewise be scaled to the total exposure time
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}

	WAITBAR->DialogResult = ::DialogResult::OK;
}

void Form1::RegistrationUVCentroidWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = "Registering file " + e->ProgressPercentage.ToString() + " of " + WAITBAR->ProgressBar->Maximum.ToString();
	WAITBAR->Refresh();//find all Update() and replace with Refresh()
}

void Form1::RegistrationUVCentroidWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	::DialogResult res = WAITBAR->DialogResult;
	Form1::Enabled = true;

	ListToImage8PixMenuItem->PerformClick();
	UVITMenu->HideDropDown();
	ConvertListToImgMenu->HideDropDown();

	WAITBAR->Hide();
	WAITBAR->Close();

	if (res == ::DialogResult::Cancel)
		return;

	/*if (::MessageBox::Show("Completed registration of the centroid lists.  Would you like to convert them to images?","Images?",::MessageBoxButtons::YesNo) == ::DialogResult::No)
		return;*/

	UVCONVERTLISTTOIMAGEBATCH = true;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = UVCONVERTLISTTOIMAGEBATCHFILES->Length;
	WAITBAR->Text = "Creating images...";
	Form1::Enabled = false;
	ConvertUVCentroidListToImgWrkr->RunWorkerAsync(UVCONVERTLISTTOIMAGEBATCHFILES);
	WAITBAR->Show();
}

void Form1::UVLoadAllMerged_Click(System::Object^ sender, System::EventArgs^ e)
{
	FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
	fbd->SelectedPath = (String^)GetReg("CCDLAB", "L2EventListPath");;
	fbd->Description = "Select the folder to scan for ALL most recent MERGED images";
	if (fbd->ShowDialog() == ::DialogResult::Cancel)
		return;
	SetReg("CCDLAB", "L2EventListPath", fbd->SelectedPath);
	SetReg("CCDLAB", "OpenFilesPath", fbd->SelectedPath);

	array<String^>^ mergeimgfiles = Directory::GetFiles(fbd->SelectedPath, "*MASTER*IMAGE*.fits", SearchOption::AllDirectories);
	Array::Sort(mergeimgfiles);
	if (mergeimgfiles->Length == 0)
	{
		::MessageBox::Show("No files found...", "Error...");
		return;
	}
	int c = 0;
	for (int i = 0; i < mergeimgfiles->Length; i++)
	{
		String^ curdir = Path::GetDirectoryName(mergeimgfiles[i]);
		array<String^>^ dirimgfiles = Directory::GetFiles(curdir, "*MASTER*IMAGE*.fits");
		int ind = 0;
		for (int j = 1; j < dirimgfiles->Length; j++)
			if (dirimgfiles[j]->Length > dirimgfiles[ind]->Length)
				ind = j;

		mergeimgfiles[c] = dirimgfiles[ind];
		c++;
		i += dirimgfiles->Length - 1;
	}
	Array::Resize(mergeimgfiles, c);

	AUTOLOADIMAGESFILES = gcnew array<String^>(mergeimgfiles->Length);
	Array::Copy(mergeimgfiles, AUTOLOADIMAGESFILES, mergeimgfiles->Length);
	AUTOLOADIMAGES = true;
	IMAGESET = gcnew FITSImageSet();
	FMLoad_Click(sender, e);
	//FMLoad->PerformClick();
}

void Form1::CombineUVCentroidListsMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->DropDown->Close();
	ShiftAndRotateMenuItem->DropDown->Close();
	UVCombineCentroidListsMenuItem->DropDown->Close();

	array<String^>^ xyintsfiles;

	if (MergeXYIntsListFolderScanChck->Checked)
	{
		if (UVMERGEDIRS_INDEX == -1)
		{
			FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
			fbd->SelectedPath = (String^)GetReg("CCDLAB", "L2EventListPath");;
			fbd->Description = "Select the folder to scan for the most recent INTEGERS Lists (_XYInts_List)";
			if (fbd->ShowDialog() == ::DialogResult::Cancel)
				return;
			SetReg("CCDLAB", "L2EventListPath", fbd->SelectedPath);
			SetReg("CCDLAB", "OpenFilesPath", fbd->SelectedPath);

			//first lets figure out if we've selected only a single channel/filter directory, or, if we've selected FUV/NUV, or, if we've selected the parent directory of FUV/NUV
			//if only a single channel/filter dir, then simply proceed as below
			//if selected FUV/NUV and dir only contains a single channel/filter subdir, then also proceed as below
			//else, multiple channel/filter directories exist and must be processed in sequence, as per the below
			if (Directory::GetParent(fbd->SelectedPath)->Name == "NUV" || Directory::GetParent(fbd->SelectedPath)->Name == "FUV")//must be either of these ones if a single channel/filter has been selected
				UVMERGEDIRS = gcnew array<String^>(1) { fbd->SelectedPath };
			else if (Directory::Exists(fbd->SelectedPath + "\\NUV") || Directory::Exists(fbd->SelectedPath + "\\FUV") || DirectoryInfo(fbd->SelectedPath).Name == "NUV" || DirectoryInfo(fbd->SelectedPath).Name == "FUV")
			{
				//some parent has been selected and need to process the channel/filter subfolders one at a time
				if (DirectoryInfo(fbd->SelectedPath).Name == "NUV" || DirectoryInfo(fbd->SelectedPath).Name == "FUV")//then process the channel subdir filter folders
					UVMERGEDIRS = Directory::GetDirectories(fbd->SelectedPath);//these must be the single channel filter folders
				else//else must be the parent to both NUV and FUV
				{
					array<String^>^ Fuvdirs = gcnew array<String^>(0);
					array<String^>^ Nuvdirs = gcnew array<String^>(0);
					if (Directory::Exists(fbd->SelectedPath + "\\FUV"))
						Fuvdirs	= Directory::GetDirectories(fbd->SelectedPath + "\\FUV");
					if (Directory::Exists(fbd->SelectedPath + "\\NUV"))
						Nuvdirs = Directory::GetDirectories(fbd->SelectedPath + "\\NUV");
					UVMERGEDIRS = gcnew array<String^>(Fuvdirs->Length + Nuvdirs->Length);
					for (int i = 0; i < Fuvdirs->Length; i++)
						UVMERGEDIRS[i] = Fuvdirs[i];
					for (int i = Fuvdirs->Length; i < Fuvdirs->Length + Nuvdirs->Length; i++)
						UVMERGEDIRS[i] = Nuvdirs[i - Fuvdirs->Length];
				}
			}
			else
			{
				MessageBox::Show("I can't determine what to do...so I'm leaving.");//cant tell what to do
				return;
			}

			//might have a masterized single which we want to ignore
			int c = 0;
			for (int i = 0; i < UVMERGEDIRS->Length; i++)
				if (Directory::GetDirectories(UVMERGEDIRS[i])->Length == 0)//then it was a masterized single
				{
					UVMERGEDIRS[i] = "";
					c++;
				}
			if (c != 0)
			{
				c = 0;
				for (int i = 0; i < UVMERGEDIRS->Length; i++)
					if (UVMERGEDIRS[i] != "")
					{
						UVMERGEDIRS[c] = UVMERGEDIRS[i];
						c++;
					}
				Array::Resize(UVMERGEDIRS, UVMERGEDIRS->Length - c);
			}

			AUTOLOADIMAGESFILES = gcnew array<String^>(UVMERGEDIRS->Length);
		}
		
		UVMERGEDIRS_INDEX++;
		//remove previously merged files because might want to start over at merge point
		xyintsfiles = Directory::GetFiles(UVMERGEDIRS[UVMERGEDIRS_INDEX], "*MASTER*");
		for (int i = 0; i < xyintsfiles->Length; i++)
				File::Delete(xyintsfiles[i]);
		//only want to merge the most recent xyintsfiles so must go through and sort this out
		//each XYInts file will be in its own directory, and this is where its dupes will be
		//we want only the most recent (longest file name length) dupe from each directory
		//when merging can only do so on deDrift & RGSTRD files, so if there are directories that couldn't be deDrift or not RGSTRD, don't use those files...
		xyintsfiles = Directory::GetFiles(UVMERGEDIRS[UVMERGEDIRS_INDEX], "*XYInts_List*deDrift*RGSTRD*.fits", SearchOption::AllDirectories);
		if (xyintsfiles->Length == 0)
		{
			UVMERGEDIRS_INDEX = -1;
			UVMERGEDIRS = nullptr;
			AUTOLOADIMAGESFILES = nullptr;
			::MessageBox::Show("No files found...", "Error...");
			CombineUVCentroidListsMenuItem_Click(sender, e);
			return;
		}
		
		int c = 0;
		Array::Sort(xyintsfiles);
		for (int i = 0; i < xyintsfiles->Length; i++)
		{
			String^ curdir = Path::GetDirectoryName(xyintsfiles[i]);
			array<String^>^ dirxyfiles = Directory::GetFiles(curdir, "*XYInts_List*deDrift*RGSTRD*.fits");
			int ind = 0;
			for (int j = 1; j < dirxyfiles->Length; j++)
				if (dirxyfiles[j]->Length > dirxyfiles[ind]->Length)
					ind = j;

			xyintsfiles[c] = dirxyfiles[ind];
			c++;
			i += dirxyfiles->Length - 1;
		}
		Array::Resize(xyintsfiles, c);
	}
	else
	{
		::OpenFileDialog^ ofd = gcnew ::OpenFileDialog();
		ofd->Multiselect = true;
		String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS (*.fits)|*.fits";
		ofd->Title = "Select the Centroid INTEGERS Lists (_XYInts_List)";
		::DialogResult res = ofd->ShowDialog();

		if (res != ::DialogResult::OK)
			return;

		dir = ofd->FileNames[0]->Substring(0, ofd->FileNames[0]->LastIndexOf("\\"));
		dir = dir->Substring(0, dir->LastIndexOf("\\"));
		SetReg("CCDLAB", "L2EventListPath", dir);
		SetReg("CCDLAB", "OpenFilesPath", dir);
		xyintsfiles = ofd->FileNames;
	}

	if (xyintsfiles->Length == 1)
	{
		::MessageBox::Show("Need to select more than 1 file for merging...", "Error...");
		CombineUVCentroidListsMenuItem_Click(sender, e);
		return;
	}

	//check that filters/channels arent' mixed
	if (FITSImageSet::GetCommonDirectory(xyintsfiles) != Directory::GetParent(Directory::GetParent(xyintsfiles[0])->FullName)->FullName)
	{
		::MessageBox::Show("These do not seem to be indentical channel/filter images for merging...", "Error...");
		CombineUVCentroidListsMenuItem_Click(sender, e);
		return;
	}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = xyintsfiles->Length;
	if (UVMERGEDIRS != nullptr)
		WAITBAR->Text = "(" + (UVMERGEDIRS_INDEX + 1) + " of " + UVMERGEDIRS->Length + ") " + "Merging Channel-Filter Directory: " + DirectoryInfo(FITSImageSet::GetCommonDirectory(xyintsfiles)).Name;
	else
		WAITBAR->Text = "Merging Channel-Filter Directory: " + DirectoryInfo(FITSImageSet::GetCommonDirectory(xyintsfiles)).Name;
	WAITBAR->ProgressBar->Value = 0;
	MergeCentroidListsWrkr->RunWorkerAsync(xyintsfiles);
	WAITBAR->ShowDialog();
}

void Form1::MergeCentroidListsWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ filenames = (array<String^>^)e->Argument;

	String^ dir = filenames[0]->Substring(0,filenames[0]->LastIndexOf("\\"));
	dir = dir->Substring(0,dir->LastIndexOf("\\"));

	//array<FITSImage^>^ expmergeset = gcnew array<FITSImage^>(filenames->Length);
	array<array<double, 2>^>^ expmergesetarrays = gcnew array<array<double, 2>^>(filenames->Length);

	//for tracking relative exposure times
	array<double>^ exptimes = gcnew array<double>(filenames->Length);//use physical time i.e. timelist max-min

	//for tracking parity errors and missing frames
	double nparityerr = 0, parityredctn = 0;
	double nmissingframes = 0, missframesredctn = 0;
	int N_centroids = 0, N_frames = 0;
	
	for (int i = 0; i < filenames->Length; i++)
		N_centroids += (gcnew JPFITS::FITSImage(filenames[i], nullptr, true, false, false, false))->Height;
	
	int exparrayres = ExposureArrayResolutionDrop->SelectedIndex + 1;
	double dres = double(exparrayres);
	double pixres = 32 / dres;
	if (L1CentroidPaddingChck->Checked)
	{
		if (PCCentroidPaddingDrop->SelectedIndex == 0)
			UVPCMODEPADOFFSET = 22;
		if (PCCentroidPaddingDrop->SelectedIndex == 1)
			UVPCMODEPADOFFSET = 44;
	}
	else
		UVPCMODEPADOFFSET = 0;
	int offset = UVPCMODEPADOFFSET * exparrayres;
	FITSImage^ ff = gcnew JPFITS::FITSImage(filenames[0], nullptr, true, false, false, false);
	int winxsz = Convert::ToInt32(ff->GetKeyValue("WIN_X_SZ"));
	int szx = (winxsz + 1)*exparrayres + offset * 2;
	int winysz = Convert::ToInt32(ff->GetKeyValue("WIN_Y_SZ"));
	int szy = (winysz + 1)*exparrayres + offset * 2;
	int ox = Convert::ToInt32(ff->GetKeyValue("WIN_XOFF"));
	int oy = Convert::ToInt32(ff->GetKeyValue("WIN_YOFF"));

	//create the arrays for the cenrtoid lists (time list, frame list, flat list, XYInts list, XYFrac list
	array<double>^ newTimeList = gcnew array<double>(N_centroids); //save as unsigned __int32 at writetime
	array<double>^ newFrameList = gcnew array<double>(N_centroids);//now has to be int32 because it won't roll over, save as unsigned __int32 at writetime
	array<double>^ mergedFlatList = gcnew array<double>(N_centroids);
	array<double>^ mergedExpList = gcnew array<double>(N_centroids);
	array<__int16,2>^ mergedXYIntsList = gcnew array<__int16,2>(2,N_centroids);
	array<__int16,2>^ mergedXYFracList = gcnew array<__int16,2>(2,N_centroids);
	array<double>^ mergedBJDList = gcnew array<double>(N_centroids);
	array<__int16,2>^ mergedmdMmList = gcnew array<__int16,2>(2,N_centroids);
	//now run through the files and collect the centroid lists into the big list

	array<double>^ prevendtimes = gcnew array<double>(filenames->Length);
	array<double>^ prevendframs = gcnew array<double>(filenames->Length);
	array<int>^ previndexes = gcnew array<int>(filenames->Length);
	for (int i = 0; i < prevendtimes->Length - 1; i++)
	{
		String^ timefile = filenames[i]->Remove(filenames[i]->IndexOf("XYInts")) + "TimeList.fits";
		String^ deDrift = "_deDrift";
		while (filenames[i]->Contains(deDrift))
		{
			timefile = timefile->Replace("TimeList", "TimeList_deDrift");
			deDrift += "_deDrift";
		}
		String^ framefile = timefile->Replace("Time", "Frame");
		array<double>^ timevec = FITSImage::ReadImageVectorOnly(timefile, nullptr, true);
		array<double>^ framevec = FITSImage::ReadImageVectorOnly(framefile, nullptr, true);

		double time_per_frame = (timevec[timevec->Length - 1] - timevec[0]) / (framevec[framevec->Length - 1] - framevec[0]);

		prevendtimes[i + 1] = timevec[timevec->Length - 1] - timevec[0] + time_per_frame + prevendtimes[i];
		prevendframs[i + 1] = framevec[framevec->Length - 1] - framevec[0] + 1 + prevendframs[i];
		previndexes[i + 1] = timevec->Length + previndexes[i];
	}

	int n = omp_get_max_threads();
	array<int>^ count = gcnew array<int>(n);
	int prog = 0;
	
	#pragma omp parallel for
	for (int i = 0; i < filenames->Length; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			break;

		count[omp_get_thread_num()]++;
		#pragma omp critical
		{
			int sum = 0;
			for (int si = 0; si < count->Length; si++)
				sum += count[si];
			if (sum * 100 / filenames->Length > prog)
			{
				MergeCentroidListsWrkr->ReportProgress(sum);
				prog = sum * 100 / filenames->Length;
			}
		}
		
		String^ intsfile = filenames[i];
		String^ fracfile = intsfile->Replace("Ints","Frac");

		String^ timefile = intsfile->Remove(intsfile->IndexOf("XYInts")) + "TimeList.fits";
		String^ deDrift = "_deDrift";
		while (intsfile->Contains(deDrift))
		{
			timefile = timefile->Replace("TimeList", "TimeList_deDrift");
			deDrift += "_deDrift";
		}

		String^ framefile = timefile->Replace("Time", "Frame");
		String^ flatfile = timefile->Replace("Time", "Flat");
		String^ BJDfile = timefile->Replace("Time", "BJD");
		String^ mdMmfile = timefile->Replace("TimeList", "XYmdMm_List");
		String^ expfile = timefile->Replace("TimeList", "ExpArrayImg");

		JPFITS::FITSImage^ intsfits = gcnew JPFITS::FITSImage(intsfile, nullptr, true, false, false, false);
		array<double, 2>^ intsarray = FITSImage::ReadImageArrayOnly(intsfile, nullptr, false);
		array<double, 2>^ fracarray = FITSImage::ReadImageArrayOnly(fracfile, nullptr, false);
		array<double>^ timevec = FITSImage::ReadImageVectorOnly(timefile, nullptr, false);
		array<double>^ framevec = FITSImage::ReadImageVectorOnly(framefile, nullptr, false);
		array<double>^ flatvec = FITSImage::ReadImageVectorOnly(flatfile, nullptr, false);
		array<double>^ BJDfits = FITSImage::ReadImageVectorOnly(BJDfile, nullptr, false);
		array<double, 2>^ mdMmvec = FITSImage::ReadImageArrayOnly(mdMmfile, nullptr, false);
		expmergesetarrays[i] = FITSImage::ReadImageArrayOnly(expfile, nullptr, false);

		//track the physical exposure times for drift series merge
		exptimes[i] = timevec[timevec->Length - 1] - timevec[0];
		expmergesetarrays[i] = JPMath::MatrixMultScalar(expmergesetarrays[i], exptimes[i], false);

		//track the stuff about parity errors and missing frames
		double npart = Convert::ToDouble(intsfits->GetKeyValue("NPARTERR"));//number of parity errors in original (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
		double ncent = Convert::ToDouble(intsfits->GetKeyValue("NCENTROD"));//number of centroids in original (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
		nparityerr += npart * Convert::ToDouble(intsfits->Height) / ncent;//total number of parity errors proportioned for possibly split files and clipped files

		N_frames += int(framevec[framevec->Length - 1] - framevec[0] + 1);
		double nmiss = Convert::ToDouble(intsfits->GetKeyValue("NMISSFRM"));//number of missing frames in original (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
		double nfram = Convert::ToDouble(intsfits->GetKeyValue("NFRAMES"));//number of frames in original  (unsplit or unclipped) file - (splitting happens in FUV, clipping happens in drift correxn)
		nmissingframes += nmiss * (framevec[framevec->Length - 1] - framevec[0] + 1)/ nfram;//total number of missing frames proportioned for possibly split files and clipped files

		//there should be no roll-overs in the time or frame lists for each set, so do soemthing to gather the total number of frames and time by gathering
		//the start & end time & frame for each set etc
		//then the merged list requires an artificial time & frame list which reproduces the same total time & total frames of the sum of the sets...
		//in this case we dont even need to create a merged time and frame list from the data, just need to gather the total frames & time and then make the lists
		double time_per_frame = (timevec[timevec->Length - 1] - timevec[0]) / (framevec[framevec->Length - 1] - framevec[0]);

		for (int j = 0; j < intsfits->Height; j++)
		{
			mergedXYIntsList[0, previndexes[i] + j] = (__int16)intsarray[0, j];
			mergedXYIntsList[1, previndexes[i] + j] = (__int16)intsarray[1, j];

			mergedXYFracList[0, previndexes[i] + j] = (__int16)fracarray[0, j];
			mergedXYFracList[1, previndexes[i] + j] = (__int16)fracarray[1, j];

			mergedmdMmList[0, previndexes[i] + j] = (__int16)mdMmvec[0, j];
			mergedmdMmList[1, previndexes[i] + j] = (__int16)mdMmvec[1, j];

			mergedFlatList[previndexes[i] + j] = flatvec[j];

			mergedBJDList[previndexes[i] + j] = BJDfits[j];

			/*if (j > 0 && timevec[j] != timevec[j - 1])//frame should change too...
				if (framevec[j] == framevec[j - 1])
					if (MessageBox::Show("Time changed but frame didn't in source data when merging centroid lists.  File: " + framefile + ". Last Frame = " + framevec[j - 1].ToString() + "; Current Frame = " + framevec[j].ToString() + "; Next Frame = " + framevec[j + 1].ToString() + "; Last Time = " + timevec[j - 1].ToString() + "; Current Time = " + timevec[j].ToString() + "; Next Time = " + timevec[j + 1].ToString() + ".  Would you like to stop?", "Warning...", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
					{
						WAITBAR->CancelBtn->PerformClick();
						return;
					}*/

			newTimeList[previndexes[i] + j] = timevec[j] - timevec[0] + time_per_frame + prevendtimes[i];
			newFrameList[previndexes[i] + j] = framevec[j] - framevec[0] + 1 + prevendframs[i];
		}
	}

	array<double, 2>^ expmergesetarraysSUM = gcnew array<double, 2>(expmergesetarrays[0]->GetLength(0), expmergesetarrays[0]->GetLength(1));
	#pragma omp parallel for
	for (int x = 0; x < expmergesetarraysSUM->GetLength(0); x++)
		for (int y = 0; y < expmergesetarraysSUM->GetLength(1); y++)
			for (int z = 0; z < expmergesetarrays->Length; z++)
				expmergesetarraysSUM[x, y] += expmergesetarrays[z][x, y];

	expmergesetarraysSUM = JPMath::MatrixDivScalar(expmergesetarraysSUM, JPMath::Sum(exptimes, false), true);
	#pragma omp parallel for
	for (int j = 0; j < mergedExpList->Length; j++)
	{
		int xpos = (int)((mergedXYIntsList[0, j] - ox * 32 + mergedXYFracList[0, j] + 16) / 32 * dres) + UVPCMODEPADOFFSET * int(dres);//reset integers to start at 0
		int ypos = (int)((mergedXYIntsList[1, j] - oy * 32 + mergedXYFracList[1, j] + 16) / 32 * dres) + UVPCMODEPADOFFSET * int(dres);//must add 16 to fractionals
		if (xpos >= 0 && ypos >= 0 && xpos < szx && ypos < szy)
			mergedExpList[j] = expmergesetarraysSUM[xpos, ypos];
	}

	parityredctn = nparityerr / double(N_centroids);//parity photometric reduction for actual file data after possible splitting and clipping
	missframesredctn = nmissingframes / double(N_frames);//parity photometric reduction for actual file data after possible splitting and clipping

	int indlast = filenames[0]->IndexOf("_XYInts");
	String^ test = filenames[0]->Substring(0, indlast - 1);
	int indfirst = test->LastIndexOf("_");
	test = filenames[0]->Substring(0, indfirst - 1);
	indfirst = test->LastIndexOf("_") + 1;

	String^ intsfile = filenames[0]->Remove(indfirst, indlast - indfirst);
	intsfile = intsfile->Insert(intsfile->IndexOf("_XYInts"),"__MASTER__");
	intsfile = dir + intsfile->Substring(intsfile->LastIndexOf("\\"));
	String^ fracfile = intsfile->Replace("XYInts","XYFrac");

	String^ timefile = intsfile->Remove(intsfile->IndexOf("XYInts")) + "TimeList.fits";
	String^ deDrift = "_deDrift";
	while (intsfile->Contains(deDrift))
	{
		timefile = timefile->Replace("TimeList", "TimeList_deDrift");
		deDrift += "_deDrift";
	}

	String^ framefile = timefile->Replace("Time", "Frame");

	String^ flatfile = timefile->Replace("Time", "Flat");

	String^ expfile = timefile->Replace("TimeList", "ExpArrayList");

	String^ BJDfile = timefile->Replace("Time", "BJD");

	String^ mdMmfile = timefile->Replace("TimeList", "XYmdMm_List");

	WAITBAR->TextMsg->Text = "Writing the merged list...";
	WAITBAR->Refresh();

	JPFITS::FITSImage^ intsfits = gcnew JPFITS::FITSImage(intsfile, mergedXYIntsList, false, true);
	FITSImageSet::GatherHeaders(filenames, intsfits);
	intsfits->AddKey("TIMEMULT", filenames->Length.ToString(), "Multiplier for merged list int. time", -1);
	intsfits->SetKey("PARTREDC", Math::Round(parityredctn, 5).ToString(), "Fractional int-time reduxn due to parity err", true, 14);
	intsfits->SetKey("FRAMREDC", Math::Round(missframesredctn, 5).ToString(), "Fractional int - time reduxn due to lost frames", true, 14);
	intsfits->WriteImage(::TypeCode::Int16, true);

	JPFITS::FITSImage^ fracfits = gcnew JPFITS::FITSImage(fracfile, mergedXYFracList, false, true);
	fracfits->CopyHeader(intsfits);
	fracfits->WriteImage(::TypeCode::Int16, true);

	JPFITS::FITSImage^ timefits = gcnew JPFITS::FITSImage(timefile, newTimeList, false, true);
	timefits->CopyHeader(intsfits);
	timefits->WriteImage(::TypeCode::UInt32, true);

	JPFITS::FITSImage^ framefits = gcnew JPFITS::FITSImage(framefile, newFrameList, false, true);//now has to be int32 because it won't roll over
	framefits->CopyHeader(intsfits);
	framefits->WriteImage(::TypeCode::UInt32, true);

	JPFITS::FITSImage^ flatfits = gcnew JPFITS::FITSImage(flatfile, mergedFlatList, false, true);
	flatfits->CopyHeader(intsfits);
	flatfits->WriteImage(::TypeCode::Double, true);

	FITSImage^ expfits = gcnew FITSImage(expfile->Replace("ExpArrayList", "ExpArrayImg"), expmergesetarraysSUM, false, true);
	expfits->CopyHeader(intsfits);
	expfits->WriteImage(expfile->Replace("ExpArrayList", "ExpArrayImg"), TypeCode::Double, true);

	expfits = gcnew JPFITS::FITSImage(expfile, mergedExpList, false, true);
	expfits->CopyHeader(intsfits);
	expfits->WriteImage(::TypeCode::Double, true);

	JPFITS::FITSImage^ BJDfits = gcnew JPFITS::FITSImage(BJDfile, mergedBJDList, false, true);
	BJDfits->CopyHeader(intsfits);
	BJDfits->WriteImage(::TypeCode::Double, true);

	JPFITS::FITSImage^ mdMmfits = gcnew JPFITS::FITSImage(mdMmfile, mergedmdMmList, false, true);
	mdMmfits->CopyHeader(intsfits);
	mdMmfits->WriteImage(::TypeCode::Int16, true);

	e->Result = intsfile;
}

void Form1::MergeCentroidListsWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = "Merging file " + (e->ProgressPercentage).ToString() + " of " + WAITBAR->ProgressBar->Maximum.ToString();
	WAITBAR->Refresh();
}

void Form1::MergeCentroidListsWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		UVMERGEDIRS_INDEX = -1;
		UVMERGEDIRS = nullptr;
		Form1::Enabled = true;
		return;
	}

	if (UVDeleteMergeDirsChck->Checked)
	{
		String^ dir = Directory::GetParent((String^)e->Result)->FullName;
		array<String^>^ mergedirs = Directory::GetDirectories(dir);
		for (int i = 0; i < mergedirs->Length; i++)
			Directory::Delete(mergedirs[i], true);
	}

	if (UVMERGEDIRS_INDEX == -1)//then create the single image right away
	{
		UVCONVERTLISTTOIMAGEBATCH = true;
		AUTOLOADIMAGESFILES = gcnew array<String^>(1) { (String^)e->Result };
		WAITBAR->ProgressBar->Maximum = AUTOLOADIMAGESFILES->Length;
		WAITBAR->Text = "Creating image(s)...";
		ConvertUVCentroidListToImgWrkr->RunWorkerAsync(AUTOLOADIMAGESFILES);
		return;
	}
	else
	{
		AUTOLOADIMAGESFILES[UVMERGEDIRS_INDEX] = (String^)e->Result;
		if (UVMERGEDIRS_INDEX + 1 < UVMERGEDIRS->Length)//then continue
		{
			WAITBAR->Hide();
			WAITBAR->Close();
			CombineUVCentroidListsMenuItem_Click(sender, e);
			return;
		}
		if (UVMERGEDIRS_INDEX + 1 == UVMERGEDIRS->Length)//then finished
		{
			UVMERGEDIRS_INDEX = -1;
			UVMERGEDIRS = nullptr;
			UVITPOSTMERGE = true;

			UVCONVERTLISTTOIMAGEBATCH = true;
			WAITBAR->ProgressBar->Maximum = AUTOLOADIMAGESFILES->Length;
			WAITBAR->Text = "Creating image(s)...";
			ConvertUVCentroidListToImgWrkr->RunWorkerAsync(AUTOLOADIMAGESFILES);
			return;
		}
	}
}

void Form1::NUVToFUVFrameMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	TransformCoefATxt->Text = "0.84898";
	TransformCoefBTxt->Text = "0.53007";
	TransformCoefCTxt->Text = "0.53007";
	TransformCoefDTxt->Text = "-0.84898";
	TransformShiftXTxt->Text = "0";
	TransformShiftYTxt->Text = "0";
	TransformCenterXTxt->Text = "255";
	TransformCenterYTxt->Text = "255";

	GeneralTransformChck->Checked = false;
	GeneralTransformChck->PerformClick();
	UVITMenu->HideDropDown();
	ShiftAndRotateMenuItem->HideDropDown();
	UserDefinedShiftRotateMenuItem->HideDropDown();

	String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
	OpenFileDialog^ dlg = gcnew OpenFileDialog();
	dlg->InitialDirectory = dir;
	dlg->Filter = "FITS (*.fits)|*.fits";
	dlg->Multiselect = true;
	dlg->Title = "Select the Centroid INTEGERS List (_XYInts_List)";
	::DialogResult res = dlg->ShowDialog();
	if (res != ::DialogResult::OK)
		return;

	UVNUVTOFUVFILES = dlg->FileNames;
	UVNUVTOFUV = true;
	UserDefinedShiftRotateMenuItem_DoubleClick(sender,e);
}

void Form1::BackgroundCountsPixelFrameTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (BackgroundCountsPixelFrameTxt->Text == "-" || BackgroundCountsPixelFrameTxt->Text == "-." || BackgroundCountsPixelFrameTxt->Text == ".")
		return;

	try
	{
		::Convert::ToDouble(BackgroundCountsPixelFrameTxt->Text);
	}
	catch (...)
	{
		BackgroundCountsPixelFrameTxt->Text = "0";
	}
	SetReg("CCDLAB", "BackgroundCountsPixelFrameTxt",BackgroundCountsPixelFrameTxt->Text);
}

void Form1::CorrectBackgroundCountsChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->ShowDropDown();
	DeSaturateROICountsMenuItem->ShowDropDown();

	if (CorrectBackgroundCountsChck->Checked)
		BackgroundCountsPixelFrameTxt->Enabled = true;
	else
		BackgroundCountsPixelFrameTxt->Enabled = false;
}

void Form1::DeSaturateROICountsMenuItem_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->HideDropDown();
	DeSaturateROICountsMenuItem->HideDropDown();

	String^ imgname = IMAGESET[FileListDrop->SelectedIndex]->FullFileName;
	String^ dedrift = "";
	while (imgname->Contains(dedrift + "_deDrift"))
		dedrift += "_deDrift";

	String^ framesname = imgname->Substring(0, imgname->IndexOf("deFPN")) + "FrameList" + dedrift + ".fits";
	String^ timessname = framesname->Replace("Frame","Time");
	String^ flatssname = framesname->Replace("Frame", "Flat");
	String^ expssname = framesname->Replace("Frame", "ExpArray");
	
	String^ intsname = imgname->Substring(0, imgname->IndexOf("_IMAGE"));
	intsname = intsname->Insert(intsname->IndexOf("deFPN"), "XYInts_List_") + ".fits";
	String^ fracsname = intsname->Replace("Ints","Frac");

	array<double>^ frames = JPFITS::FITSImage::ReadImageVectorOnly(framesname, nullptr, true);
	array<double>^ times = JPFITS::FITSImage::ReadImageVectorOnly(timessname, nullptr, true);
	array<double>^ flats = JPFITS::FITSImage::ReadImageVectorOnly(flatssname, nullptr, true);
	array<double>^ exps = JPFITS::FITSImage::ReadImageVectorOnly(expssname, nullptr, true);
	JPFITS::FITSImage^ FracFits = gcnew FITSImage(fracsname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ IntsFits = gcnew FITSImage(intsname, nullptr, true, true, false, true);

	String^ EXTXRNG = FracFits->GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
	if (EXTXRNG == "")
		EXTXRNG = "0:511";//from L2 data
	String^ EXTYRNG = FracFits->GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
	if (EXTYRNG == "")
		EXTYRNG = "0:511";//from L2 data
	int ix = EXTXRNG->IndexOf(":");
	int iy = EXTYRNG->IndexOf(":");
	double rx1 = ::Convert::ToDouble(EXTXRNG->Substring(0,ix));//range start
	double ry1 = ::Convert::ToDouble(EXTYRNG->Substring(0,iy));
	double rx2 = ::Convert::ToDouble(EXTXRNG->Substring(ix+1));//range end
	double ry2 = ::Convert::ToDouble(EXTYRNG->Substring(iy+1));

	String^ xoffset = FracFits->GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
	if (xoffset == "")
		xoffset = FracFits->GetKeyValue("WIN_XOFF");//from L2 data
	double ox = ::Convert::ToDouble(xoffset);//x offset
	String^ yoffset = FracFits->GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
	if (yoffset == "")
		yoffset = FracFits->GetKeyValue("WIN_YOFF");//from L2 data
	double oy = ::Convert::ToDouble(yoffset);//y offset

	double prec = 1;//check for the image precision...
	String^ strprec = IMAGESET[FileListDrop->SelectedIndex]->GetKeyValue("IMAGPREC");
	if (strprec != "")
		prec = ::Convert::ToDouble(strprec);

	int offset = 0;
	String^ stroffset = IMAGESET[FileListDrop->SelectedIndex]->GetKeyValue("PADOFSET");
	if (stroffset != "")
		offset = ::Convert::ToInt32(stroffset);

	int XSTART = XSUBRANGE[0] - offset*int(prec);
	int YSTART = YSUBRANGE[0] - offset*int(prec);
	int XEND = XSUBRANGE[XSUBRANGE->Length - 1] - offset*int(prec);
	int YEND = YSUBRANGE[YSUBRANGE->Length - 1] - offset*int(prec);

	double curframe = -1;//initialize frame number
	double ROIframecount = 0;//frame count
	double ROIrawcount = 0;//raw count - counter for centroids in ROI
	double flateff = 0;
	double expeff = 0;

	for (int i = 0; i < frames->Length; i++)
	{
		int xpos = (int)((IntsFits[0,i] - rx1*32 - ox*32 + FracFits[0,i] + 16)/32 * prec);
		int ypos = (int)((IntsFits[1,i] - ry1*32 - oy*32 + FracFits[1,i] + 16)/32 * prec);

		if (xpos >= XSTART && ypos >= YSTART && xpos <= XEND && ypos <= YEND)
		{
			ROIrawcount++;
			flateff += 1 / flats[i];
			expeff += 1 / exps[i];
			if (curframe != frames[i])
			{
				ROIframecount++;
				curframe = frames[i];
			}
		}
	}

	flateff /= ROIrawcount;
	expeff /= ROIrawcount;
	flateff = 1 / flateff;
	expeff = 1 / expeff;

	double totaltime = Convert::ToDouble(IMAGESET[FileListDrop->SelectedIndex]->GetKeyValue("RDCDTIME"));
	double nframes = (frames[frames->Length - 1] - frames[0] + 1);//number of frames in raw EU data
	double listframecount = (double)int(nframes * (1 - Convert::ToDouble(IMAGESET[FileListDrop->SelectedIndex]->GetKeyValue("FRAMREDC"))));//number of actual existing data frames (nframes adjusted for CRC missing frames)
	double listframeskips = nframes - listframecount;//number of frames which were CRC skipped
	double frames_per_sec = Math::Round(1000*(frames[frames->Length - 1] - frames[0]) / (times[times->Length - 1] - times[0]), 4);
	
	double bg = 0;//background
	if (CorrectBackgroundCountsChck->Checked)
		bg = ::Convert::ToDouble(BackgroundCountsPixelFrameTxt->Text);//total counts per pixel for final image near ROI, user entered from COG analysis
	bg = bg * SUBIMAGE->Length;//total bg counts in ROI - multiply bg counts per pixel by number of pixels in ROI
	bg = bg / listframecount;//rate of bg event in ROI per frame NOT adjusted for exposure array...so get it from good region

	double zeros = listframecount - ROIframecount / expeff;//number of zero count frames adjusted for exposure array
	double Pzero = zeros / listframecount;//probability of zero-count frames per frame
	double correctedcountrate = Math::Log(1/Pzero) - bg;//rate per frame
	double err = Math::Sqrt(ROIrawcount / Math::Exp(-correctedcountrate));
	
	String^ result;
	result += "ROI Window Size:	" + XSUBRANGE->Length.ToString() + "x" + YSUBRANGE->Length.ToString() + "\r\n";
	result += "ROI Window Location:	" + "X: " + (XSUBRANGE[(int)HalfWidthXUpD->Value]+1).ToString() + ", Y: " + (YSUBRANGE[(int)HalfWidthYUpD->Value]+1).ToString() + "\r\n";
	result += "ROI Raw Count:	" + ROIrawcount.ToString() + "\r\n";
	result += "ROI Flat:	" + flateff.ToString() + "\r\n";
	result += "ROI Exposure:	" + expeff.ToString() + "\r\n";
	result += "ROI Raw Exposure Count:	" + (ROIrawcount / expeff).ToString() + "\r\n";
	result += "N Frames in Observation:	" + nframes.ToString() + "\r\n";
	result += "Missing Frames:	" + listframeskips.ToString() + "\r\n";
	result += "Known Frames:	" + listframecount.ToString() + "\r\n";
	result += "Known Time:	" + totaltime.ToString() + "\r\n";
	result += "Frames per Second:	" + frames_per_sec.ToString() + "\r\n";
	result += "ROI Raw Data Frames:	" + ROIframecount.ToString() + "\r\n";
	result += "ROI Exposure Frames:	" + (ROIframecount / expeff).ToString() + "\r\n";
	result += "ROI 0 Count Frames:	" + zeros.ToString() + "\r\n";
	result += "ROI Exp P(0):	" + (Pzero).ToString() + "\r\n";
	result += "ROI Exp Count Rate/f:	" + (ROIrawcount / expeff / listframecount).ToString() + "\r\n";
	result += "ROI Exp Desaturated Rate/f:	" + correctedcountrate.ToString() + "\r\n";
	result += "ROI Exp/Flat Desaturated Rate/f:	" + (correctedcountrate / flateff).ToString() + "\r\n";
	result += "ROI Background Rate/f:	" + bg.ToString() + "\r\n";
	result += "ROI Exp Desaturated Rate/s:	" + (correctedcountrate * listframecount / totaltime).ToString() + "\r\n";
	result += "ROI Exp/Flat Desaturated Rate/s:	" + (correctedcountrate / flateff * listframecount / totaltime).ToString() + "\r\n";
	System::Windows::Forms::Clipboard::SetText(result);

	COG_PLOT->Close();

	result = "";
	result += "ROI Window Size:			" + XSUBRANGE->Length.ToString() + "x" + YSUBRANGE->Length.ToString() + "\r\n";
	result += "ROI Window Location:		" + "X: " + (XSUBRANGE[(int)HalfWidthXUpD->Value] + 1).ToString() + ", Y: " + (YSUBRANGE[(int)HalfWidthYUpD->Value] + 1).ToString() + "\r\n";
	result += "ROI Raw Count:			" + ROIrawcount.ToString() + "\r\n";
	result += "ROI Flat:				" + flateff.ToString() + "\r\n";
	result += "ROI Exposure:			" + expeff.ToString() + "\r\n";
	result += "ROI Raw Exposure Count:		" + (ROIrawcount / expeff).ToString() + "\r\n";
	result += "N Frames in Observation:		" + nframes.ToString() + "\r\n";
	result += "Missing Frames:			" + listframeskips.ToString() + "\r\n";
	result += "Known Frames:			" + listframecount.ToString() + "\r\n";
	result += "Known Time:			" + totaltime.ToString() + "\r\n";
	result += "Frames per Second:			" + frames_per_sec.ToString() + "\r\n";
	result += "ROI Raw Data Frames:		" + ROIframecount.ToString() + "\r\n";
	result += "ROI Exposure Frames:		" + (ROIframecount / expeff).ToString() + "\r\n";
	result += "ROI 0 Count Frames:			" + zeros.ToString() + "\r\n";
	result += "ROI Exp P(0):			" + (Pzero).ToString() + "\r\n";
	result += "ROI Exp Count Rate/f:		" + (ROIrawcount / expeff / listframecount).ToString() + "\r\n";
	result += "ROI Exp Desaturated Rate/f:		" + correctedcountrate.ToString() + "\r\n";
	result += "ROI Exp/Flat Desaturated Rate/f:	" + (correctedcountrate / flateff).ToString() + "\r\n";
	result += "ROI Background Rate/f:		" + bg.ToString() + "\r\n";
	result += "ROI Exp Desaturated Rate/s:		" + (correctedcountrate * listframecount / totaltime).ToString() + "\r\n";
	result += "ROI Exp/Flat Desaturated Rate/s:	" + (correctedcountrate / flateff * listframecount / totaltime).ToString() + "\r\n";
	::MessageBox::Show(result,"This table copied to clipboard...");	
}

void Form1::ExtractROICentroidListMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ imgname = IMAGESET[FileListDrop->SelectedIndex]->FullFileName;
	String^ dedrift = "";
	while (imgname->Contains(dedrift + "_deDrift"))
		dedrift += "_deDrift";

	String^ framesname = imgname->Substring(0, imgname->IndexOf("deFPN")) + "FrameList" + dedrift + ".fits";
	String^ timesname = framesname->Replace("Frame","Time");
	String^ flatsname = framesname->Replace("Frame","Flat");
	String^ expsname = framesname->Replace("FrameList", "ExpArrayList");
	String^ BJDSname = framesname->Replace("Frame","BJD");
	String^ mdMmsname = framesname->Replace("FrameList","XYmdMm_List");
	
	String^ intsname = imgname->Substring(0, imgname->IndexOf("_IMAGE"));
	intsname = intsname->Insert(intsname->IndexOf("deFPN"), "XYInts_List_") + ".fits";
	String^ fracsname = intsname->Replace("Ints","Frac");

	JPFITS::FITSImage^ FrameFits = gcnew FITSImage(framesname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ TimeFits = gcnew FITSImage(timesname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ FracFits = gcnew FITSImage(fracsname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ IntsFits = gcnew FITSImage(intsname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ FlatFits = gcnew FITSImage(flatsname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ ExpFits = gcnew FITSImage(expsname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ BJDFits = gcnew FITSImage(BJDSname, nullptr, true, true, false, true);
	JPFITS::FITSImage^ mdMmFits = gcnew FITSImage(mdMmsname, nullptr, true, true, false, true);

	String^ EXTXRNG = FracFits->GetKeyValue("EXTXRNG");//from GSE CCDLAB processing
	if (EXTXRNG == "")
		EXTXRNG = "0:511";//from L2 data
	String^ EXTYRNG = FracFits->GetKeyValue("EXTYRNG");//from GSE CCDLAB processing
	if (EXTYRNG == "")
		EXTYRNG = "0:511";//from L2 data
	int ix = EXTXRNG->IndexOf(":");
	int iy = EXTYRNG->IndexOf(":");
	double rx1 = ::Convert::ToDouble(EXTXRNG->Substring(0,ix));//range start
	double ry1 = ::Convert::ToDouble(EXTYRNG->Substring(0,iy));
	double rx2 = ::Convert::ToDouble(EXTXRNG->Substring(ix+1));//range end
	double ry2 = ::Convert::ToDouble(EXTYRNG->Substring(iy+1));

	String^ xoffset = FracFits->GetKeyValue("XOFFSET");//from GSE CCCDLAB processing
	if (xoffset == "")
		xoffset = FracFits->GetKeyValue("WIN_XOFF");//from L2 data
	double ox = ::Convert::ToDouble(xoffset);//x offset
	String^ yoffset = FracFits->GetKeyValue("YOFFSET");//from GSE CCCDLAB processing
	if (yoffset == "")
		yoffset = FracFits->GetKeyValue("WIN_YOFF");//from L2 data
	double oy = ::Convert::ToDouble(yoffset);//y offset

	array<bool>^ ROItrue = gcnew array<bool>(FrameFits->Height);
	int c = 0;

	double prec = 1;
	String^ strprec = IMAGESET[FileListDrop->SelectedIndex]->GetKeyValue("IMAGPREC");
	if (strprec != "")
		prec = ::Convert::ToDouble(strprec);
	
	int offset = 0;
	String^ stroffset = IMAGESET[FileListDrop->SelectedIndex]->GetKeyValue("PADOFSET");
	if (stroffset != "")
		offset = ::Convert::ToInt32(stroffset);

	int XSTART = XSUBRANGE[0] - offset*int(prec);
	int YSTART = YSUBRANGE[0] - offset*int(prec);
	int XEND = XSUBRANGE[XSUBRANGE->Length-1] - offset*int(prec);
	int YEND = YSUBRANGE[YSUBRANGE->Length-1] - offset*int(prec);

	for (int i = 0; i < FrameFits->Height; i++)
	{
		int xpos = (int)((IntsFits[0, i] - rx1 * 32 - ox * 32 + FracFits[0, i] + 16) / 32 * prec);
		int ypos = (int)((IntsFits[1, i] - ry1 * 32 - oy * 32 + FracFits[1, i] + 16) / 32 * prec);

		if (xpos >= XSTART && ypos >= YSTART && xpos <= XEND && ypos <= YEND)
		{
			c++;
			ROItrue[i] = true;
		}
		else
			ROItrue[i] = false;
	}

	XSTART /= int(prec);
	YSTART /= int(prec);
	XEND /= int(prec);
	YEND /= int(prec);

	array<double>^ ROItimelist = gcnew array<double>(c);
	array<double>^ ROIframelist = gcnew array<double>(c);
	array<double,2>^ ROIintslist = gcnew array<double,2>(2,c);
	array<double,2>^ ROIfraclist = gcnew array<double,2>(2,c);
	array<double>^ ROIflatlist = gcnew array<double>(c);
	array<double>^ ROIexplist = gcnew array<double>(c);
	array<double>^ ROIBJDlist = gcnew array<double>(c);
	array<double,2>^ ROImdMmlist = gcnew array<double,2>(2,c);

	c = 0;
	for (int i = 0; i < FrameFits->Height; i++)
	{
		if (ROItrue[i])
		{
			ROItimelist[c] = TimeFits[0,i];
			ROIframelist[c] = FrameFits[0,i];
			ROIintslist[0,c] = IntsFits[0,i];
			ROIintslist[1,c] = IntsFits[1,i];
			ROIfraclist[0,c] = FracFits[0,i];
			ROIfraclist[1,c] = FracFits[1,i];
			ROImdMmlist[0,c] = mdMmFits[0,i];
			ROImdMmlist[1,c] = mdMmFits[1,i];
			ROIflatlist[c] = FlatFits[0,i];
			ROIexplist[c] = ExpFits[0, i];
			ROIBJDlist[c] = BJDFits[0,i];
			c++;
		}
	}

	timesname = timesname->Substring(0, timesname->IndexOf(".fits")) + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROItimeFits = gcnew JPFITS::FITSImage(timesname, ROItimelist, false, false);
	ROItimeFits->CopyHeader(FrameFits);
	ROItimeFits->SetKey("EXTXRNG", XSTART.ToString() + ":" +  XEND.ToString(), "Extraction X-Range", true, -1);
	ROItimeFits->SetKey("EXTYRNG", YSTART.ToString() + ":" +  YEND.ToString(), "Extraction Y-Range", true, -1);
	ROItimeFits->WriteImage(::TypeCode::UInt32, false);

	framesname = framesname->Substring(0, framesname->IndexOf(".fits")) + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROIframeFits = gcnew JPFITS::FITSImage(framesname, ROIframelist, false, false);
	ROIframeFits->CopyHeader(ROItimeFits);
	ROIframeFits->WriteImage(::TypeCode::UInt32, false);

	intsname = intsname->Substring(0, intsname->IndexOf(".fits")) + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROIintsFits = gcnew JPFITS::FITSImage(intsname, ROIintslist, false, false);
	ROIintsFits->CopyHeader(ROItimeFits);
	ROIintsFits->WriteImage(::TypeCode::Int16, false);

	fracsname = fracsname->Substring(0, fracsname->IndexOf(".fits")) + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROIfracFits = gcnew JPFITS::FITSImage(fracsname, ROIfraclist, false, false);
	ROIfracFits->CopyHeader(ROItimeFits);
	ROIfracFits->WriteImage(::TypeCode::Int16, false);

	flatsname = flatsname->Substring(0, flatsname->IndexOf(".fits")) + "_ROIx" + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROIflatFits = gcnew JPFITS::FITSImage(flatsname, ROIflatlist, false, false);
	ROIflatFits->CopyHeader(ROItimeFits);
	ROIflatFits->WriteImage(::TypeCode::Double, false);

	expsname = expsname->Substring(0, expsname->IndexOf(".fits")) + "_ROIx" + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROIexpFits = gcnew JPFITS::FITSImage(expsname, ROIexplist, false, false);
	ROIexpFits->CopyHeader(ROItimeFits);
	ROIexpFits->WriteImage(::TypeCode::Double, false);

	BJDSname = BJDSname->Substring(0, BJDSname->IndexOf(".fits")) + "_ROIx" "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROIBJDSFits = gcnew JPFITS::FITSImage(BJDSname, ROIBJDlist, false, false);
	ROIBJDSFits->CopyHeader(ROItimeFits);
	ROIBJDSFits->WriteImage(::TypeCode::Double, false);

	mdMmsname = mdMmsname->Substring(0, mdMmsname->IndexOf(".fits")) + "_ROIx" + XSTART.ToString() + "-" + XEND.ToString() + "y" + YSTART.ToString() + "-" + YEND.ToString() + ".fits";
	JPFITS::FITSImage^ ROImdMmFits = gcnew JPFITS::FITSImage(mdMmsname, ROImdMmlist, false, false);
	ROImdMmFits->CopyHeader(ROItimeFits);
	ROImdMmFits->WriteImage(::TypeCode::Int16, false);

	::MessageBox::Show("ROI centroid list extracted and written in image directory.","Success...");
}

void Form1::ConsolidateNUVApplyToFUV_Click(System::Object^  sender, System::EventArgs^  e)
{
	UVITMenu->DropDown->Close();
	ApplyDriftListMentuItem->DropDown->Close();
	ConsolidateNUVApplyToFUV->DropDown->Close();

	//get the drift series
	array<String^>^ driftFileNames;
	bool driftfolderconsol = ConsolidateDriftFolderChck->Checked;
	if (!driftfolderconsol)
	{
		OpenFileDialog^ ofd = gcnew ::OpenFileDialog();
		ofd->Multiselect = true;
		String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS (*.drift)|*.drift";
		ofd->Title = "Select the MOST RECENT NUV *or* VIS DRIFT Series (*.drift)";
		::DialogResult res = ofd->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		SetReg("CCDLAB", "L2EventListPath", ofd->FileNames[0]->Substring(0, ofd->FileNames[0]->LastIndexOf("\\")));
		driftFileNames = ofd->FileNames;
	}
	else
	{
		if (!AUTOVISDRIFTAPPLY)
		{
			FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
			fbd->SelectedPath = (String^)GetReg("CCDLAB", "L2EventListPath");
			fbd->Description = "Select the MOST RECENT NUV *or* VIS DRIFT Series Folder (*.drift)";
			::DialogResult res = fbd->ShowDialog();
			if (res == ::DialogResult::Cancel)
				return;
			SetReg("CCDLAB", "L2EventListPath", fbd->SelectedPath);
			driftFileNames = Directory::GetFiles(fbd->SelectedPath, "*VIS*.drift", ::SearchOption::AllDirectories);
		}
		else
		{
			driftFileNames = Directory::GetFiles((String^)GetReg("CCDLAB", "L2EventListPath"), "*VIS*.drift", ::SearchOption::AllDirectories);
		}
	}
	//here I will make sure that there are no NUV/VIS drift series repeats....only want the highest order (MOST RECENT) series from each directory
	ArrayList^ files = gcnew ArrayList();
	Array::Sort(driftFileNames);//sorted alphabetically now so same times/directories will be adjacent...not sure though where the last series would be in the filename repeats...
	for (int i = 0; i < driftFileNames->Length; i++)
	{
		String^ driftfiletime_i = driftFileNames[i]->Substring(driftFileNames[i]->IndexOf("_XYDrift") - 13, 13);
		int j = i + 1;

		String^ file_i = driftFileNames[i];
		bool seriesorders = false;
		while (j < driftFileNames->Length && driftfiletime_i == driftFileNames[j]->Substring(driftFileNames[j]->IndexOf("_XYDrift") - 13, 13))//must be in same directory
		{
			seriesorders = true;
			if (driftFileNames[j]->Length > file_i->Length)
				file_i = driftFileNames[j];
			j++;
		}
		if (seriesorders)
		{
			i = j - 1;
		}
		files->Add(file_i);
	}
	array<String^>^ driftfiles = gcnew array<String^>(files->Count);
	for (int i = 0; i < driftfiles->Length; i++)
		driftfiles[i] = (String^)files[i];
	driftFileNames = driftfiles;

	JPFITS::FITSImage^ driftfits = gcnew FITSImage(driftFileNames[0], nullptr, true, false, false, true);
	String^ driftchannel = driftfits->GetKeyValue("DETECTOR");
	if (driftchannel == "")
		driftchannel = driftfits->GetKeyValue("CHANNEL");

	for (int i = 1; i < driftFileNames->Length; i++)
	{
		driftfits = gcnew FITSImage(driftFileNames[i], nullptr, true, false, false, false);
		String^ channel2 = driftfits->GetKeyValue("DETECTOR");
		if (channel2 == "")
			channel2 = driftfits->GetKeyValue("CHANNEL");

		if (driftchannel != channel2)
		{
			::MessageBox::Show("Error: Mixed drift channels detected.  Please select *only* NUV or VIS Drift List files/folders...", "Error...", ::MessageBoxButtons::OK);
			ConsolidateNUVApplyToFUV_Click(sender, e);
			return;
		}
	}

	//need to get the time lists...
	reget:
	array<String^>^ TimeListNames;
	bool timefolderconsol = ConsolidateTimeListFolderChck->Checked;
	if (!timefolderconsol)
	{
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Multiselect = true;
		String^ dir = (String^)GetReg("CCDLAB", "L2EventListPath");
		ofd->InitialDirectory = dir;
		ofd->Filter = "FITS (*.fits)|*.fits";
		ofd->Title = "Select the FUV *or* NUV TIME Series to apply drift to (*TimeList.fits)";
		::DialogResult res = ofd->ShowDialog();
		if (res != ::DialogResult::OK)
			return;
		SetReg("CCDLAB", "L2EventListPath", ofd->FileNames[0]->Substring(0, ofd->FileNames[0]->LastIndexOf("\\")));
		SetReg("CCDLAB", "OpenFilesPath", ofd->FileNames[0]->Substring(0, ofd->FileNames[0]->LastIndexOf("\\")));
		TimeListNames = ofd->FileNames;
		for (int i = 0; i < TimeListNames->Length; i++)
			if (!TimeListNames[i]->Contains("TimeList"))
			{
				::MessageBox::Show("Error: Seems that one of the TimeList files is not what it should be: " + TimeListNames[i], "Error...", ::MessageBoxButtons::OK);
				goto reget;
			}
	}
	else
	{
		if (!AUTOVISDRIFTAPPLY)
		{
			FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
			fbd->SelectedPath = DirectoryInfo((String^)GetReg("CCDLAB", "L2EventListPath")).Parent->FullName;
			fbd->Description = "Select the FUV, or NUV, or FUV/NUV Parent Folder to apply drift to";
			::DialogResult res = fbd->ShowDialog();
			if (res == ::DialogResult::Cancel)
				return;

			if (Directory::Exists(fbd->SelectedPath + "\\FUV") || Directory::Exists(fbd->SelectedPath + "\\NUV"))//then we've selected the parent, so do autoapply
				AUTOVISDRIFTAPPLY = true;
			else
				TimeListNames = Directory::GetFiles(fbd->SelectedPath, "*TimeList.fits", ::SearchOption::AllDirectories);
		}

		if (AUTOVISDRIFTAPPLY)
		{
			String^ FUVdir = Directory::GetParent((String^)GetReg("CCDLAB", "L2EventListPath"))->FullName + "\\FUV";
			String^ NUVdir = Directory::GetParent((String^)GetReg("CCDLAB", "L2EventListPath"))->FullName + "\\NUV";
			FUVDIREXISTS = Directory::Exists(FUVdir);
			NUVDIREXISTS = Directory::Exists(NUVdir);

			if (Directory::Exists(FUVdir) && !DONUVDRIFTNOW)
				TimeListNames = Directory::GetFiles(FUVdir, "*TimeList.fits", ::SearchOption::AllDirectories);
			else
			{
				TimeListNames = Directory::GetFiles(NUVdir, "*TimeList.fits", ::SearchOption::AllDirectories);
				DONUVDRIFTNOW = false;
				FUVDIREXISTS = false;
			}
		}
	}
	JPFITS::FITSImage^ fits = gcnew FITSImage(TimeListNames[0], nullptr, true, false, false, true);
	String^ channel1 = fits->GetKeyValue("DETECTOR");
	if (channel1 == "")
		channel1 = fits->GetKeyValue("CHANNEL");
	for (int i = 1; i < TimeListNames->Length; i++)
	{
		fits = gcnew FITSImage(TimeListNames[i], nullptr, true, false, false, false);
		String^ channel2 = fits->GetKeyValue("DETECTOR");
		if (channel2 == "")
			channel2 = fits->GetKeyValue("CHANNEL");

		if (channel1 != channel2)
		{
			::MessageBox::Show("Error: Mixed channels selected.  Please select *only* FUV or NUV TimeList files/folders...", "Error...", ::MessageBoxButtons::OK);
			goto reget;
		}
	}

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "DeDrift " + TimeListNames->Length + " " + channel1 + " from " + driftFileNames->Length + " " + driftchannel + " Drift Series...";
	WAITBAR->ProgressBar->Value = 0;
	array<Object^>^ arg = gcnew array<Object^>(2);
	arg[0] = driftFileNames;
	arg[1] = TimeListNames;
	DriftNUVtoFUVBGWrkr->RunWorkerAsync(arg);
	WAITBAR->ShowDialog();
}

void Form1::DriftNUVtoFUVBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<Object^>^ arg = (array<Object^>^)e->Argument;
	array<String^>^ driftFileNames = (array<String^>^)arg[0];
	array<String^>^ TimeListNames = (array<String^>^)arg[1];
	String^ driftserieschannel = "";
	bool nuvTOfuv = false;

	//have the most recent drift series, now must search for possible 1st order series to consolidate all orders together first
	//first must sort the directories in sequence
	array<double>^ dirtimes = gcnew array<double>(driftFileNames->Length);
	for (int i = 0; i < driftFileNames->Length; i++)
	{
		String^ path = driftFileNames[i]->Substring(0, driftFileNames[i]->LastIndexOf("\\"));
		String^ dirtime = path->Substring(path->LastIndexOf("_")+1,13);
		dirtimes[i] = ::Convert::ToDouble(dirtime);
	}
	Array::Sort(dirtimes, driftFileNames);
	array<String^>^ FilePaths = gcnew array<String^>(driftFileNames->Length);
	for (int i = 0; i < driftFileNames->Length; i++)
		FilePaths[i] = driftFileNames[i]->Substring(0, driftFileNames[i]->LastIndexOf("\\"));
	//filepaths/names now sorted in time order

	//now go to each path, and do a first consolidation/compactification of the drift series in each path (observation) if there are 1st & 2nd Order etc. series
	//can assume that all series are processed equally, so if only find 1st order, no need to process this step
	array<String^>^ pathcompactseriesFILES = gcnew array<String^>(FilePaths->Length);
	for (int i = 0; i < FilePaths->Length; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;
		DriftNUVtoFUVBGWrkr->ReportProgress((i + 1) * 100 / FilePaths->Length, "Consolidating " + driftserieschannel + " drift series...");

		array<String^>^ pathdriftseries = ::Directory::GetFiles(FilePaths[i],"*.drift");
		array<int>^ pathdriftserieslengths = gcnew array<int>(pathdriftseries->Length);//filename length gives the drift series order
		for (int j = 0; j < pathdriftserieslengths->Length; j++)
			pathdriftserieslengths[j] = pathdriftseries[j]->Length;
		Array::Sort(pathdriftserieslengths,pathdriftseries);//now the driftseries are sorted in order Order..i.e., the last one is the shortest, highest order
		Array::Reverse(pathdriftserieslengths);
		Array::Reverse(pathdriftseries);//now the first one is the shortest

		JPFITS::FITSImage^ pathconsolidatedseries = gcnew FITSImage(pathdriftseries[0], nullptr, true, true, false, true);
		if (i == 0)
		{
			driftserieschannel = pathconsolidatedseries->GetKeyValue("DETECTOR");
			if (driftserieschannel == "")
				driftserieschannel = pathconsolidatedseries->GetKeyValue("CHANNEL");//raw file source or GSE
			if (driftserieschannel == "" || driftserieschannel != "NUV" && driftserieschannel != "VIS")//although FUV COULD be used for NUV...should never need...can do if needed
			{
				::MessageBox::Show("Drift series channel not identifiable or FUV:  DETECTOR = " + driftserieschannel + "; Exiting.","Error");
				WAITBAR->CancelBtn->PerformClick();
				return;
			}
			if (driftserieschannel == "NUV")
				if (pathconsolidatedseries->GetKeyIndex("NUVTOFUV") != -1)
					nuvTOfuv = true;
		}
		for (int j = 1; j < pathdriftseries->Length; j++)
		{
			JPFITS::FITSImage^ pathconsolidatedseries_lowerorder = gcnew FITSImage(pathdriftseries[j], nullptr, true, true, false, true);//lower order is longer length

			#pragma omp parallel for
			for (int m = 1; m < 3; m++)
				for (int k = 0; k < pathconsolidatedseries->Height; k++)
					pathconsolidatedseries[m, k] += pathconsolidatedseries_lowerorder[m, k];
		}
		//pathconsolidatedseries now has all drift correction orders combined for this path
		//now compactify it to unique time elements only
		int c = 0;
		double time = -1;
		for (int j = 0; j < pathconsolidatedseries->Height; j++)
		{
			if (time != pathconsolidatedseries[j])
			{
				c++;
				time = pathconsolidatedseries[j];
			}
		}
		array<double,2>^ pathcompactseries = gcnew array<double,2>(3,c);
		c = 0;
		time = -1;
		for (int j = 0; j < pathconsolidatedseries->Height; j++)
		{
			if (time != pathconsolidatedseries[j])
			{
				pathcompactseries[0,c] = pathconsolidatedseries[0,j];
				pathcompactseries[1,c] = pathconsolidatedseries[1,j];
				pathcompactseries[2,c] = pathconsolidatedseries[2,j];
				c++;
				time = pathconsolidatedseries[j];
			}
		}
		//now have the pathcompactseries...write it in the path to disk as FITS .drift file...will delete later

		String^ pathcompactseriesFILE = driftFileNames[i];
		pathcompactseriesFILE = pathcompactseriesFILE->Insert(pathcompactseriesFILE->IndexOf("_XYDrift_List") + 13,"__COMPACT_");
		pathcompactseriesFILE = pathcompactseriesFILE->Remove(pathcompactseriesFILE->IndexOf("COMPACT") + 8,7);
		JPFITS::FITSImage^ pathcompactseriesFITS = gcnew FITSImage(pathcompactseriesFILE,pathcompactseries,false, true);
		pathcompactseriesFITS->WriteImage(::TypeCode::Double, true);
		pathcompactseriesFILES[i] = pathcompactseriesFILE;
	}

	//String them together
	FITSImage^ fits;
	int c = 0;
	for (int i = 0; i < pathcompactseriesFILES->Length; i++)
	{
		fits = gcnew FITSImage(pathcompactseriesFILES[i], nullptr, true, false, false, true);
		c += fits->Height;
	}
	array<double,2>^ pathcompactseriesconsolidated = gcnew array<double,2>(3,c);
	array<double,2>^ NUVstartendtimes = gcnew array<double,2>(2,pathcompactseriesFILES->Length);//need this for later but good to produce here with this
	c = 0;
	for (int i = 0; i < pathcompactseriesFILES->Length; i++)
	{
		fits = gcnew FITSImage(pathcompactseriesFILES[i], nullptr, true, true, false, true);
		NUVstartendtimes[0,i] = fits[0,0];
		NUVstartendtimes[1,i] = fits[0,fits->Height-1];
		for (int k = 0; k < fits->Height; k++)
		{
			pathcompactseriesconsolidated[0,c] = fits[0,k];
			pathcompactseriesconsolidated[1,c] = fits[1,k];
			pathcompactseriesconsolidated[2,c] = fits[2,k];
			c++;
		}
		::File::Delete(pathcompactseriesFILES[i]);//delete them so that they don't clutter the directories
	}

	//now have consolidated & compactified all selected NUV drift series into a single vector
	//now they must be used for FUV...they will need to be transformed to FUV coordinates
	array<double>^ Pvistonuv = gcnew array<double>(4){1.01075, -0.04301, -0.04301, -1.01075};//from Shyam Feb 2017
	array<double>^ Pnuvtofuv = gcnew array<double>(4){0.84898, 0.53007, 0.53007, -0.84898};//from Shyam Feb 2017
	array<double>^ Pvistofuv = gcnew array<double>(4){0, 0, 0, 0};//???
	double dx, dy, dxp, dyp;
	if (driftserieschannel == "NUV")
	{
		DriftNUVtoFUVBGWrkr->ReportProgress(0,"Transforming NUV drift series to FUV frame...");
		if (!nuvTOfuv)
		{
			#pragma omp parallel for private(dx, dy)
			for (int i = 0; i < c; i++)
			{
				dx = pathcompactseriesconsolidated[1, i];
				dy = pathcompactseriesconsolidated[2, i];

				pathcompactseriesconsolidated[1, i] = Pnuvtofuv[0] * dx + Pnuvtofuv[1] * dy;//NUV to FUV
				pathcompactseriesconsolidated[2, i] = Pnuvtofuv[2] * dx + Pnuvtofuv[3] * dy;
			}
		}
		else//no change, NUV drift already in FUV coordinate frame
		{
			/*#pragma omp parallel for private(dx, dy)
			for (int i = 0; i < c; i++)
			{
				dx = pathcompactseriesconsolidated[1, i];
				dy = pathcompactseriesconsolidated[2, i];

				pathcompactseriesconsolidated[1, i] = pathcompactseriesconsolidated[1, i];
				pathcompactseriesconsolidated[2, i] = pathcompactseriesconsolidated[2, i];
			}*/
		}
	}

	fits = gcnew FITSImage(TimeListNames[0], nullptr, true, false, false, false);
	String^ applyserieschannel = fits->GetKeyValue("DETECTOR");
	if (applyserieschannel == "")
		applyserieschannel = fits->GetKeyValue("CHANNEL");
	if (driftserieschannel == "VIS")
	{
		if (applyserieschannel == "NUV" && fits->GetKeyIndex("NUVTOFUV") != -1)
			nuvTOfuv = true;

		DriftNUVtoFUVBGWrkr->ReportProgress(0,"Transforming VIS drift series to " + applyserieschannel + " frame...");
		if (applyserieschannel == "FUV" || nuvTOfuv)
		{
			#pragma omp parallel for private(dx, dy, dxp, dyp)
			for (int i = 0; i < c; i++)
			{
				dx = pathcompactseriesconsolidated[1,i];
				dy = pathcompactseriesconsolidated[2,i];

				dxp = Pvistonuv[0]*dx + Pvistonuv[1]*dy;//VIS to NUV
				dyp = Pvistonuv[2]*dx + Pvistonuv[3]*dy;

				pathcompactseriesconsolidated[1,i] = Pnuvtofuv[0]*dxp + Pnuvtofuv[1]*dyp;//NUV to FUV
				pathcompactseriesconsolidated[2,i] = Pnuvtofuv[2]*dxp + Pnuvtofuv[3]*dyp;

				/*pathcompactseriesconsolidated[1,i] = Pvistofuv[0]*dx + Pvistofuv[1]*dy;//VIS to FUV
				pathcompactseriesconsolidated[2,i] = Pvistofuv[2]*dx + Pvistofuv[3]*dy;*/
			}
		}
		else if (applyserieschannel == "NUV" && !nuvTOfuv)
		{
			#pragma omp parallel for private(dx, dy)
			for (int i = 0; i < c; i++)
			{
				dx = pathcompactseriesconsolidated[1,i];
				dy = pathcompactseriesconsolidated[2,i];

				pathcompactseriesconsolidated[1,i] = Pvistonuv[0]*dx + Pvistonuv[1]*dy;
				pathcompactseriesconsolidated[2,i] = Pvistonuv[2]*dx + Pvistonuv[3]*dy;
			}
		}
		else
		{
			::MessageBox::Show("Error...section 8");
			return;
		}
	}
	
	//now string together the FUV TimeLists
	c = 0;
	for (int i = 0; i < TimeListNames->Length; i++)
	{
		fits = gcnew FITSImage(TimeListNames[i], nullptr, true, false, false, false);
		c += fits->Height;
	}
	array<double>^ FUVTimeList = gcnew array<double>(c);
	c = 0;
	for (int i = 0; i < TimeListNames->Length; i++)
	{
		fits = gcnew FITSImage(TimeListNames[i], nullptr, true, true, false, true);
		String^ FUVFrameListName = TimeListNames[i]->Replace("TimeList", "FrameList");
		array<double>^ frames = FITSImage::ReadImageVectorOnly(FUVFrameListName, nullptr, true);
		double timeperframeby2 = Math::Round((fits[ fits->Height - 1] - fits[ 0]) / (frames[fits->Height-1] - frames[0]) / 2);
		for (int k = 0; k < fits->Height; k++)
		{
			FUVTimeList[c] = fits[k] + timeperframeby2;//use actual time per frame
			c++;
		}
	}

	//Now interpolate-spline the consolidated series and create FUVTimeList interpolation values
	DriftNUVtoFUVBGWrkr->ReportProgress(50, "Interpolating " + driftserieschannel + " drift series to " + applyserieschannel + "...");
	array<double>^ t = gcnew array<double>(pathcompactseriesconsolidated->GetLength(1));
	array<double>^ xd = gcnew array<double>(pathcompactseriesconsolidated->GetLength(1));
	array<double>^ yd = gcnew array<double>(pathcompactseriesconsolidated->GetLength(1));
	#pragma omp parallel for
	for (int i = 0; i < t->Length; i++)
	{
		t[i] = pathcompactseriesconsolidated[0, i];
		xd[i] = pathcompactseriesconsolidated[1, i];
		yd[i] = pathcompactseriesconsolidated[2, i];
	}
	array<double>^ xdi = JPMath::Interpolate1d(t, xd, FUVTimeList, "akima", true);
	array<double>^ ydi = JPMath::Interpolate1d(t, yd, FUVTimeList, "akima", true);
	DriftNUVtoFUVBGWrkr->ReportProgress(100, "Interpolating " + driftserieschannel + " drift series to " + applyserieschannel + "...");
	array<double, 2>^ FUVinterpdriftseries = gcnew array<double, 2>(2, FUVTimeList->Length);
	#pragma omp parallel for
	for (int i = 0; i < FUVTimeList->Length; i++)
	{
		FUVinterpdriftseries[0, i] = xdi[i];
		FUVinterpdriftseries[1, i] = ydi[i];
	}

	/*JPFITS::FITSImage^ consolidated = gcnew FITSImage("c:\\consolidated.fits", pathcompactseriesconsolidated, false);
	consolidated->WriteImage(TypeCode::Double);
	FITSImage^ fuvt = gcnew FITSImage("c:\\fuvtimes.fits", FUVTimeList, false);
	fuvt->WriteImage(TypeCode::Double);
	FITSImage^ fuvinterp = gcnew FITSImage("c:\\fuvinterpxyd.fits", FUVinterpdriftseries, false);
	fuvinterp->WriteImage(TypeCode::Double);*/

	//Now, for EACH FUVTimeList, see if there is any time overlap of valid interpolation, and make its drift series to save for each one
	//so, need to compare the FUV TimeList with the NUVdriftseries time list to see where valid overlapping FUV times are; FUV times that are not valid can be set = -1
	//use the NUVstartendtimes to check for good FUV times...
	bool brk = false;
	#pragma omp parallel for private(brk)
	for (int i = 0; i < FUVTimeList->Length; i++)
	{
		brk = false;
		for (int j = 0; j < pathcompactseriesFILES->Length; j++)
		{
			if (FUVTimeList[i] >= NUVstartendtimes[0,j] && FUVTimeList[i] <= NUVstartendtimes[1,j])
			{
				brk = true;
				break;
			}
		}
		if (brk)
			continue;
		FUVTimeList[i] = -1;
	}
	
	//so now have FUV times which are from the original FUV lists and which are good times
	//now need to go through the individual FUV lists/directories and create drift series for those good times and save them in those directories
	//then after that or at the same time, would need to apply them to the centroid lists and make new de-drifted centroid lists
	int res = ExposureArrayResolutionDrop->SelectedIndex + 1;
	if (L1CentroidPaddingChck->Checked)
	{
		if (PCCentroidPaddingDrop->SelectedIndex == 0)
			UVPCMODEPADOFFSET = 22;
		if (PCCentroidPaddingDrop->SelectedIndex == 1)
			UVPCMODEPADOFFSET = 44;
	}
	else
		UVPCMODEPADOFFSET = 0;
	int offset = UVPCMODEPADOFFSET * res;
	array<double, 2>^ EXPposureMAP;
	String^ FUVexpmapfile;
	String^ NUVexpmapfile;
	if (res == 1)
	{
		FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map.fits";
		NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map.fits";
		if (nuvTOfuv)
			NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map_NUVtoFUV.fits";
	}
	if (res == 2)
	{
		FUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\FUV Exposure Map x2.fits";
		NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2.fits";
		if (nuvTOfuv)
			NUVexpmapfile = "C:\\UVIT_CalDB\\Exposure Array Map\\NUV Exposure Map x2_NUVtoFUV.fits";
	}
	if (!File::Exists(FUVexpmapfile))
	{
		::MessageBox::Show("FUV Exposure Map not found in UVIT_CalDB at " + FUVexpmapfile + ".  Please update your Cal_DB from http://www.ucalgary.ca/uvit/.  Exiting.", "Error...");
		WAITBAR->CancelBtn->PerformClick();
		return;
	}
	if (!File::Exists(NUVexpmapfile))
	{
		::MessageBox::Show("NUV Exposure Map not found in UVIT_CalDB at " + NUVexpmapfile + ".  Please update your Cal_DB from http://www.ucalgary.ca/uvit/.  Exiting.", "Error...");
		WAITBAR->CancelBtn->PerformClick();
		return;
	}
	if (applyserieschannel == "FUV")
	{
		if (UVPCMODEPADOFFSET == 44)
			EXPposureMAP = FITSImage::ReadImageArrayOnly(FUVexpmapfile, gcnew array<int>(4) { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
		if (UVPCMODEPADOFFSET == 22)
			EXPposureMAP = FITSImage::ReadImageArrayOnly(FUVexpmapfile, gcnew array<int>(4) { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
		if (UVPCMODEPADOFFSET == 0)
			EXPposureMAP = FITSImage::ReadImageArrayOnly(FUVexpmapfile, gcnew array<int>(4) { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
	}
	if (applyserieschannel == "NUV")
	{
		if (UVPCMODEPADOFFSET == 44)
			EXPposureMAP = FITSImage::ReadImageArrayOnly(NUVexpmapfile, gcnew array<int>(4) { 0, 600 * res - 1, 0, 600 * res - 1 }, true);
		if (UVPCMODEPADOFFSET == 22)
			EXPposureMAP = FITSImage::ReadImageArrayOnly(NUVexpmapfile, gcnew array<int>(4) { 22 * res, 600 * res - 1 - 22 * res, 22 * res, 600 * res - 1 - 22 * res }, true);
		if (UVPCMODEPADOFFSET == 0)
			EXPposureMAP = FITSImage::ReadImageArrayOnly(NUVexpmapfile, gcnew array<int>(4) { 44 * res, 600 * res - 1 - 44 * res, 44 * res, 600 * res - 1 - 44 * res }, true);
	}
	ArrayList^ createimagexyintslist = gcnew ArrayList();

	array<int>^ cntr = gcnew array<int>(TimeListNames->Length + 1);
	for (int i = 1; i < cntr->Length; i++)
		cntr[i] = (gcnew FITSImage(TimeListNames[i - 1], nullptr, true, false, false, false))->Height + cntr[i - 1];

	int n = omp_get_max_threads();
	array<int>^ count = gcnew array<int>(n);
	int prog = 0;

	#pragma omp parallel for
	for (int i = 0; i < TimeListNames->Length; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			continue;

		count[omp_get_thread_num()]++;
		#pragma omp critical
		{
			int sum = 0;
			for (int si = 0; si < count->Length; si++)
				sum += count[si];
			if (sum * 100 / TimeListNames->Length > prog)
			{
				prog = sum * 100 / TimeListNames->Length;
				DriftNUVtoFUVBGWrkr->ReportProgress(prog, "Drift-correcting " + applyserieschannel + " centroids...");
			}
		}

		String^ fuvtimelistName = TimeListNames[i];
		String^ fuvxyfraclistName = fuvtimelistName->Replace("TimeList", "XYFrac_List_deFPN_deDIST");
		String^ fuvxyintslistName = fuvtimelistName->Replace("TimeList", "XYInts_List_deFPN_deDIST");
		String^ fuvflatlistName = fuvtimelistName->Replace("TimeList", "FlatList");
		String^ fuvframelistName = fuvtimelistName->Replace("TimeList", "FrameList");
		String^ fuvBJDlistName = fuvtimelistName->Replace("TimeList", "BJDList");
		String^ fuvmdmmlistName = fuvtimelistName->Replace("TimeList", "XYmdMm_List");

		//if using this after trying self-correction, then self-correction files ALL need to be removed from the selected file directories
		//as those directories are drift corrected here.
		String^ dir = fuvtimelistName->Substring(0, fuvtimelistName->LastIndexOf("\\"));
		array<String^>^ olddrifts = ::Directory::GetFiles(dir, "*.drift");
		for (int k = 0; k < olddrifts->Length; k++)
			::File::Delete(olddrifts[k]);
		array<String^>^ olddedrifts = ::Directory::GetFiles(dir, "*deDrift*");
		for (int k = 0; k < olddedrifts->Length; k++)
			::File::Delete(olddedrifts[k]);

		//load the timelist and find out where it is good, if at all
		//they will be loaded in the same order as the string is contructed, so then can just equate them tracking indices
		FITSImage^ fuvtimelistFITS = gcnew FITSImage(fuvtimelistName, nullptr, true, true, false, false);
		int L = 0;//need to know how long the new lists will be...
		for (int j = 0; j < fuvtimelistFITS->Height; j++)
		{
			fuvtimelistFITS[j] = FUVTimeList[cntr[i] + j];
			if (fuvtimelistFITS[j] == -1)
				L++;
		}

		//if there are any good times in this list, not all values will be = -1
		if (L == fuvtimelistFITS->Height)//then no good times
			continue;//go to next interation

		L = fuvtimelistFITS->Height - L;//need to know how long the new lists will be...
		
		//so now there are some good times
		//now make the dedrifted lists for this directory
		array<double>^ fuvtimelistdedrift = gcnew array<double>(L);
		array<double>^ fuvframelistdedrift = gcnew array<double>(L);
		array<double>^ fuvflatlistdedrift = gcnew array<double>(L);
		array<double>^ fuvBJDlistdedrift = gcnew array<double>(L);
		array<double, 2>^ fuvxyintslistdedrift = gcnew array<double, 2>(2, L);
		array<double, 2>^ fuvxyfraclistdedrift = gcnew array<double, 2>(2, L);
		array<double, 2>^ fuvmdmmlistdedrift = gcnew array<double, 2>(2, L);
		array<double,2>^ fuvdriftlist = gcnew array<double,2>(3, L);

		array<double>^ fuvframelist = JPFITS::FITSImage::ReadImageVectorOnly(fuvframelistName, nullptr, false);
		array<double>^ fuvflatlist = JPFITS::FITSImage::ReadImageVectorOnly(fuvflatlistName, nullptr, false);
		array<double>^ fuvBJDlist = JPFITS::FITSImage::ReadImageVectorOnly(fuvBJDlistName, nullptr, false);
		array<double, 2>^ fuvxyintslist = JPFITS::FITSImage::ReadImageArrayOnly(fuvxyintslistName, nullptr, false);
		array<double, 2>^ fuvxyfraclist = JPFITS::FITSImage::ReadImageArrayOnly(fuvxyfraclistName, nullptr, false);
		array<double, 2>^ fuvmdmmlist = JPFITS::FITSImage::ReadImageArrayOnly(fuvmdmmlistName, nullptr, false);

		int counter = 0;
		for (int j = 0; j < fuvtimelistFITS->Height; j++)
		{
			if (fuvtimelistFITS[j] == -1)
				continue;

			fuvtimelistdedrift[counter] = fuvtimelistFITS[j];
			fuvframelistdedrift[counter] = fuvframelist[j];
			fuvflatlistdedrift[counter] = fuvflatlist[j];
			fuvBJDlistdedrift[counter] = fuvBJDlist[j];
			fuvmdmmlistdedrift[0, counter] = fuvmdmmlist[0, j];
			fuvmdmmlistdedrift[1, counter] = fuvmdmmlist[1, j];
			fuvxyintslistdedrift[0, counter] = fuvxyintslist[0, j] - FUVinterpdriftseries[0, j + cntr[i + 1] - fuvtimelistFITS->Height];
			fuvxyintslistdedrift[1, counter] = fuvxyintslist[1, j] - FUVinterpdriftseries[1, j + cntr[i + 1] - fuvtimelistFITS->Height];
			fuvdriftlist[0, counter] = fuvtimelistFITS[j];
			fuvdriftlist[1, counter] = FUVinterpdriftseries[0, j + cntr[i + 1] - fuvtimelistFITS->Height];
			fuvdriftlist[2, counter] = FUVinterpdriftseries[1, j + cntr[i + 1] - fuvtimelistFITS->Height];
			fuvxyfraclistdedrift[0, counter] = fuvxyfraclist[0, j];
			fuvxyfraclistdedrift[1, counter] = fuvxyfraclist[1, j];
			counter++;
		}
		
		//check for initial noise frames in the FUV list...it would only be for the first time in the FUV time list
		counter = 0;
		for (int j = 0; j < fuvtimelistdedrift->Length; j++)
		{
			if (fuvtimelistdedrift[0] == fuvtimelistdedrift[j])
			{
				counter++;
				continue;
			}
			break;
		}
		if (counter >= 1000)//then resize the dedrifted lists and get rid of initial noise
		{
			array<double>^ fuvtimelistdedriftTEMP = gcnew array<double>(L - counter);
			array<double>^ fuvframelistdedriftTEMP = gcnew array<double>(L - counter);
			array<double>^ fuvflatlistdedriftTEMP = gcnew array<double>(L - counter);
			array<double>^ fuvBJDlistdedriftTEMP = gcnew array<double>(L - counter);
			array<double,2>^ fuvxyintslistdedriftTEMP = gcnew array<double,2>(2,L - counter);
			array<double,2>^ fuvxyfraclistdedriftTEMP = gcnew array<double,2>(2,L - counter);
			array<double,2>^ fuvmdmmlistdedriftTEMP = gcnew array<double,2>(2,L - counter);
			array<double, 2>^ fuvdriftlistTEMP = gcnew array<double, 2>(3, L - counter);

			//#pragma omp parallel for
			for (int j = 0; j < L - counter; j++)
			{
				fuvtimelistdedriftTEMP[j] = fuvtimelistdedrift[j + counter];
				fuvframelistdedriftTEMP[j] = fuvframelistdedrift[j + counter];
				fuvflatlistdedriftTEMP[j] = fuvflatlistdedrift[j + counter];
				fuvBJDlistdedriftTEMP[j] = fuvBJDlistdedrift[j + counter];
				fuvmdmmlistdedriftTEMP[0, j] = fuvmdmmlistdedrift[0, j + counter];
				fuvmdmmlistdedriftTEMP[1, j] = fuvmdmmlistdedrift[1, j + counter];
				fuvxyintslistdedriftTEMP[0, j] = fuvxyintslistdedrift[0, j + counter];
				fuvxyintslistdedriftTEMP[1, j] = fuvxyintslistdedrift[1, j + counter];
				fuvxyfraclistdedriftTEMP[0, j] = fuvxyfraclistdedrift[0, j + counter];
				fuvxyfraclistdedriftTEMP[1, j] = fuvxyfraclistdedrift[1, j + counter];
				fuvdriftlistTEMP[0, j] = fuvdriftlist[0, j + counter];
				fuvdriftlistTEMP[1, j] = fuvdriftlist[1, j + counter];
				fuvdriftlistTEMP[2, j] = fuvdriftlist[2, j + counter];
			}

			fuvtimelistdedrift = fuvtimelistdedriftTEMP;
			fuvframelistdedrift = fuvframelistdedriftTEMP;
			fuvflatlistdedrift = fuvflatlistdedriftTEMP;
			fuvBJDlistdedrift = fuvBJDlistdedriftTEMP;
			fuvmdmmlistdedrift = fuvmdmmlistdedriftTEMP;
			fuvxyintslistdedrift = fuvxyintslistdedriftTEMP;
			fuvxyfraclistdedrift = fuvxyfraclistdedriftTEMP;
			fuvdriftlist = fuvdriftlistTEMP;
		}

		//update BJD0
		String^ BJD0 = fuvBJDlistdedrift[0].ToString("#.0000000");
		fuvtimelistFITS->SetKey("BJD0", BJD0, "BJD of start of imaging", true, 14);

		//now create the exposure array if required
		bool createexposurearray = ApplyDriftCreateExpArrayChc->Checked;
		array<double, 2>^ exposurearray;
		double dres = double(res);
		double pixres = 32 / dres;

		int winxsz = Convert::ToInt32(fuvtimelistFITS->GetKeyValue("WIN_X_SZ"));
		int szx = (winxsz + 1)*res + offset * 2;
		int winysz = Convert::ToInt32(fuvtimelistFITS->GetKeyValue("WIN_Y_SZ"));
		int szy = (winysz + 1)*res + offset * 2;
		int ox = Convert::ToInt32(fuvtimelistFITS->GetKeyValue("WIN_XOFF"));
		int oy = Convert::ToInt32(fuvtimelistFITS->GetKeyValue("WIN_YOFF"));

		if (createexposurearray)
		{
			double nframes = 0;
			exposurearray = gcnew array<double, 2>(szx, szy);
			String^ detector = applyserieschannel;
			array<double, 2>^ exposuremap;
			
			if (detector == "FUV")
			{
				if (winxsz == 511 && winysz == 511)
					exposuremap = EXPposureMAP;
				else
				{
					exposuremap = gcnew array<double, 2>(szx, szy);
					#pragma omp parallel for
					for (int x = UVPCMODEPADOFFSET*res; x < szx - UVPCMODEPADOFFSET*res; x++)
						for (int y = UVPCMODEPADOFFSET*res; y < szy - UVPCMODEPADOFFSET*res; y++)
							exposuremap[x, y] = 1;
				}
			}
			if (detector == "NUV")
			{
				if (winxsz == 511 && winysz == 511)
					exposuremap = EXPposureMAP;
				else
				{
					exposuremap = gcnew array<double, 2>(szx, szy);
					#pragma omp parallel for
					for (int x = UVPCMODEPADOFFSET*res; x < szx - UVPCMODEPADOFFSET*res; x++)
						for (int y = UVPCMODEPADOFFSET*res; y < szy - UVPCMODEPADOFFSET*res; y++)
							exposuremap[x, y] = 1;
				}
			}

			int xstart, xend, ystart, yend, expxstart, expystart;
			fuvdriftlist[1, 0] *= -1;//still don't understand why this needs to be done...
			fuvdriftlist[2, 0] *= -1;
			double oldxdrift = fuvdriftlist[1, 0];
			double oldydrift = fuvdriftlist[2, 0];
			if (fuvdriftlist[1, 0] < 0)
			{
				xstart = -int(fuvdriftlist[1, 0] / pixres);
				xend = szx;
				expxstart = 0;
			}
			else
			{
				xstart = 0;
				xend = szx - int(fuvdriftlist[1, 0] / pixres);
				expxstart = int(fuvdriftlist[1, 0] / pixres);
			}
			if (fuvdriftlist[2, 0] < 0)
			{
				ystart = -int(fuvdriftlist[2, 0] / pixres);
				yend = szy;
				expystart = 0;
			}
			else
			{
				ystart = 0;
				yend = szy - int(fuvdriftlist[2, 0] / pixres);
				expystart = int(fuvdriftlist[2, 0] / pixres);
			}
			fuvdriftlist[1, 0] *= -1;//reset
			fuvdriftlist[2, 0] *= -1;

			double increment = 0;
			double time = -1;
			for (int k = 0; k < fuvdriftlist->GetLength(1); k++)
			{
				if (time != fuvdriftlist[0, k])//new drift frame time...possibly new drift...also very first frame
				{
					time = fuvdriftlist[0, k];
					nframes++;

					fuvdriftlist[1, k] *= -1;
					fuvdriftlist[2, k] *= -1;

					//if it isnt moving then just gather the increments to apply after it does move
					//and it only needs to be applied after it moves by at least one pixel (or res?)
					if (Math::Abs(fuvdriftlist[1, k] - oldxdrift) < pixres && Math::Abs(fuvdriftlist[2, k] - oldydrift) < pixres)//will trigger for first frame so increment goes to 1 for it
					{
						increment++;//this starts at zero, so if this is the first frame, we get the first increment = 1
						fuvdriftlist[1, k] *= -1;//reset
						fuvdriftlist[2, k] *= -1;
						continue;
					}

					//then it has moved, so increment out everything from when it wasn't moving at the old positions
					//#pragma omp parallel for
					for (int x = xstart; x < xend; x++)
						for (int y = ystart; y < yend; y++)
							if (exposuremap[x, y] == 1)
								exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;

					increment = 1;//increment for current frame

								  //update moved position stuff...at least one of the drifts is moved 32 or more...update that one or both only
					if (Math::Abs(fuvdriftlist[1, k] - oldxdrift) >= pixres)
					{
						oldxdrift = fuvdriftlist[1, k];
						if (fuvdriftlist[1, k] < 0)
						{
							xstart = -int(fuvdriftlist[1, k] / pixres);
							xend = szx;
							expxstart = 0;
						}
						else
						{
							xstart = 0;
							xend = szx - int(fuvdriftlist[1, k] / pixres);
							expxstart = int(fuvdriftlist[1, k] / pixres);
						}
					}

					if (Math::Abs(fuvdriftlist[2, k] - oldydrift) >= pixres)
					{
						oldydrift = fuvdriftlist[2, k];
						if (fuvdriftlist[2, k] < 0)
						{
							ystart = -int(fuvdriftlist[2, k] / pixres);
							yend = szy;
							expystart = 0;
						}
						else
						{
							ystart = 0;
							yend = szy - int(fuvdriftlist[2, k] / pixres);
							expystart = int(fuvdriftlist[2, k] / pixres);
						}
					}

					fuvdriftlist[1, k] *= -1;//reset
					fuvdriftlist[2, k] *= -1;
				}
			}

			//increment out last gathered increments
			//#pragma omp parallel for
			for (int x = xstart; x < xend; x++)
				for (int y = ystart; y < yend; y++)
					if (exposuremap[x, y] == 1)
						exposurearray[x - xstart + expxstart, y - ystart + expystart] += increment;

			//lastly normalize the array...
			exposurearray = JPMath::MatrixDivScalar(exposurearray, nframes, false);

			array<double>^ dedriftedExposure = gcnew array<double>(fuvdriftlist->GetLength(1));

			//#pragma omp parallel for
			for (int k = 0; k < fuvdriftlist->GetLength(1); k++)
			{
				int xpos = (int)(fuvxyintslistdedrift[0, k] / pixres) + offset - ox*res;
				int ypos = (int)(fuvxyintslistdedrift[1, k] / pixres) + offset - oy*res;
				if (xpos < 0 || ypos < 0 || xpos >= szx || ypos >= szx)
					dedriftedExposure[k] = 0;
				else
					dedriftedExposure[k] = exposurearray[xpos, ypos];//applied like the flat...take the inverse at image creation time
			}

			fuvtimelistFITS->SetKey("EXMAPRES", res.ToString(), "Exposure Map Resolution", true, 15);
			fuvtimelistFITS->SetKey("EXMAPTIM", (fuvdriftlist[0, fuvdriftlist->GetLength(1) - 1] - fuvdriftlist[0, 0]).ToString(), "Exposure Map Time", true, 15);

			//write it
			String^ dedriftedExpFile = fuvtimelistName->Replace("TimeList", "ExpArrayList_deDrift");
			FITSImage^ dedriftedExpFits = gcnew FITSImage(dedriftedExpFile, dedriftedExposure, false, false);
			dedriftedExpFits->CopyHeader(fuvtimelistFITS);
			dedriftedExpFits->WriteImage(::TypeCode::Double, false);

			dedriftedExpFile = fuvtimelistName->Replace("TimeList", "ExpArrayImg_deDrift");
			FITSImage^ exp = gcnew FITSImage(dedriftedExpFile, exposurearray, false, false);
			exp->CopyHeader(fuvtimelistFITS);
			exp->WriteImage(::TypeCode::Double, false);
		}
		//#pragma omp parallel for//need to do this for if self-correction is run after and combining drifts for exp array...haven't been sure why values need sign inversion there or here...
		for (int k = 0; k < fuvdriftlist->GetLength(1); k++)
		{
			fuvdriftlist[1, k] *= -1;
			fuvdriftlist[2, k] *= -1;
		}
		//done exposure array

		//now have the dedrifted (drift corrected) set of lists for this directory
		//need to write them to their directory
		String^ fuvtimelistNamededrift = fuvtimelistName->Replace("TimeList", "TimeList_deDrift");
		String^ fuvframelistNamededrift = fuvtimelistName->Replace("TimeList", "FrameList_deDrift");
		String^ fuvflatlistNamededrift = fuvtimelistName->Replace("TimeList", "FlatList_deDrift");
		String^ fuvBJDlistNamededrift = fuvtimelistName->Replace("TimeList", "BJDList_deDrift");
		String^ fuvxyfraclistNamededrift = fuvtimelistName->Replace("TimeList", "XYFrac_List_deFPN_deDIST_deDrift");
		String^ fuvxyintslistNamededrift = fuvtimelistName->Replace("TimeList", "XYInts_List_deFPN_deDIST_deDrift");
		String^ fuvmdmmlistNamededrift = fuvtimelistName->Replace("TimeList", "XYmdMm_List_deDrift");
		String^ fuvdriftlistname = fuvtimelistName->Replace("TimeList", "XYDrift_List_" + driftserieschannel + "to" + applyserieschannel);
		fuvdriftlistname = fuvdriftlistname->Replace(".fits", ".drift");

		FITSImage^ FITS;
		FITS = gcnew FITSImage(fuvtimelistNamededrift, fuvtimelistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::UInt32, false);
		FITS = gcnew FITSImage(fuvframelistNamededrift, fuvframelistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::UInt32, false);
		FITS = gcnew FITSImage(fuvflatlistNamededrift, fuvflatlistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::Double, false);
		FITS = gcnew FITSImage(fuvBJDlistNamededrift, fuvBJDlistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::Double, false);
		FITS = gcnew FITSImage(fuvmdmmlistNamededrift, fuvmdmmlistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::Int16, false);
		FITS = gcnew FITSImage(fuvxyfraclistNamededrift, fuvxyfraclistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::Int16, false);
		FITS = gcnew FITSImage(fuvxyintslistNamededrift, fuvxyintslistdedrift, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::Int16, false);
		FITS = gcnew FITSImage(fuvdriftlistname, fuvdriftlist, false, false);
		FITS->CopyHeader(fuvtimelistFITS);
		FITS->WriteImage(::TypeCode::Double, false);

		//dedrifted lists now written
		#pragma omp critical
		{
			createimagexyintslist->Add(fuvxyintslistNamededrift);
		}
	}

	if (createimagexyintslist->Count == 0)
	{
		e->Result = gcnew array<String^>(1) { "none" };
		return;
	}

	array<String^>^ xyintslist = gcnew array<String^>(createimagexyintslist->Count);
	for (int i = 0; i < createimagexyintslist->Count; i++)
		xyintslist[i] = (String^)createimagexyintslist[i];
	Array::Sort(xyintslist);
	e->Result = xyintslist;
}

void Form1::DriftNUVtoFUVBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = (String^)e->UserState;
	WAITBAR->Refresh();
}

void Form1::DriftNUVtoFUVBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		Form1::Enabled = true;
		return;
	}

	//now create the images
	ConvertListToImgMenu_DropDownOpened(sender,e);
	ConvertListToImgMenu->HideDropDown();
	UVCONVERTLISTTOIMAGEBATCH = true;
	AUTOLOADIMAGESFILES = (array<String^>^)e->Result;
	if (AUTOLOADIMAGESFILES[0] == "none")
	{
		::MessageBox::Show("No overlap between the drift series and the channel timelist(s)...no image created.", "Warning");
		WAITBAR->Hide();
		WAITBAR->Close();
		Form1::Enabled = true;
		return;
	}
	WAITBAR->ProgressBar->Maximum = AUTOLOADIMAGESFILES->Length;
	WAITBAR->Text = "Creating image(s)...";
	ConvertUVCentroidListToImgWrkr->RunWorkerAsync(AUTOLOADIMAGESFILES);
}

String^ Form1::UVITFilter_FWAngle_to_Index(String^ channel, double angle)
{
	if (channel != "VIS" && channel != "NUV" && channel != "FUV")
	{
		::MessageBox::Show("UVIT Channel '" + channel + "' not identified in UVITFilter...", "Error");
		return "";
	}

	if (channel == "FUV")
	{
		if (angle > 0 && angle < 3)
			return "F0";
		if (angle > 45 && angle < 48)
			return "F1";
		if (angle > 90 && angle < 93)
			return "F2";
		if (angle > 135 && angle < 138)
			return "F3";
		if (angle > 180 && angle < 183)
			return "F4";
		if (angle > 225 && angle < 228)
			return "F5";
		if (angle > 270 && angle < 273)
			return "F6";
		if (angle > 315 && angle < 318)
			return "F7";
	}

	if (channel == "NUV")
	{
		if (angle > 0 && angle < 2)
			return "F0";
		if (angle > 315 && angle < 318)
			return "F1";
		if (angle > 270 && angle < 273)
			return "F2";
		if (angle > 225 && angle < 228)
			return "F3";
		if (angle > 180 && angle < 183)
			return "F4";
		if (angle > 135 && angle < 138)
			return "F5";
		if (angle > 90 && angle < 93)
			return "F6";
		if (angle > 44 && angle < 48)
			return "F7";
	}

	if (channel == "VIS")
	{
		if (angle > 0 && angle < 2)
			return "F0";
		if (angle > 59 && angle < 62)
			return "F1";
		if (angle > 120 && angle < 123)
			return "F2";
		if (angle > 179 && angle < 182)
			return "F3";
		if (angle > 239 && angle < 242)
			return "F4";
		if (angle > 300 && angle < 303)
			return "F5";
	}

	return "NA";
}

String^ Form1::UVITFilter(String^ channel, String^ filterindex)
{
	if (channel != "VIS" && channel != "NUV" && channel != "FUV")
	{
		::MessageBox::Show("UVIT Channel '" + channel + "' not identified in UVITFilter...", "Error");
		return "";
	}

	if (channel == "FUV")
	{
		if (filterindex == "F0")
			return "BLOCK";
		if (filterindex == "F1")
			return "CaF2";
		if (filterindex == "F2")
			return "BaF2";
		if (filterindex == "F3")
			return "Sapphire";
		if (filterindex == "F4")
			return "Grating1";
		if (filterindex == "F5")
			return "Silica";
		if (filterindex == "F6")
			return "Grating2";
		if (filterindex == "F7")
			return "CaF2";
	}

	if (channel == "NUV")
	{
		if (filterindex == "F0")
			return "BLOCK";
		if (filterindex == "F1")
			return "Silica15";
		if (filterindex == "F2")
			return "NUVB15";
		if (filterindex == "F3")
			return "NUVB13";
		if (filterindex == "F4")
			return "Grating";
		if (filterindex == "F5")
			return "NUVB4";
		if (filterindex == "F6")
			return "NUVN2";
		if (filterindex == "F7")
			return "Silica117";
	}

	if (channel == "VIS")
	{
		if (filterindex == "F0")
			return "BLOCK";
		if (filterindex == "F1")
			return "VIS3";
		if (filterindex == "F2")
			return "VIS2";
		if (filterindex == "F3")
			return "VIS1";
		if (filterindex == "F4")
			return "NDF";
		if (filterindex == "F5")
			return "BK7";
	}

	return "NA";
}

void Form1::CleanVISImagesMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();

	fbd->SelectedPath = (String^)GetReg("CCDLAB", "OpenFilesPath");
	fbd->Description = "Please select the VIS directory or subirectory to clean.";
	::DialogResult res = fbd->ShowDialog();
	if (res == ::DialogResult::Cancel)
		return;

	DATE = DateTime::Now;

	Form1::Enabled = false;
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "Cleaning VIS Images";
	WAITBAR->ProgressBar->Value = 0;
	CleanVISBGWrkr->RunWorkerAsync(fbd->SelectedPath);
	WAITBAR->ShowDialog();
}

void Form1::CleanVISBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	String^ maindir = (String^)e->Argument;
	array<String^>^ VISfiles = Directory::GetFiles(maindir, "*_VIS_*.fits", ::IO::SearchOption::AllDirectories);
	Array::Sort(VISfiles);

	double threshold = Convert::ToDouble(L1CleanINTLineThreshold->Text);
	int N = Convert::ToInt32(L1CleanINTNPix->Text);

	bool doparallel = true;

	int intprog = 0;
	#pragma omp parallel for if (doparallel)
	for (int i = 0; i < VISfiles->Length; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			break;

		if (i < VISfiles->Length / omp_get_num_threads())
			if (omp_get_num_threads() * i * 100 / VISfiles->Length > intprog)
			{
				intprog++;
				CleanVISBGWrkr->ReportProgress(intprog, VISfiles->Length);
			}

		FITSImage^ VISfits = gcnew FITSImage(VISfiles[i], nullptr, true, true, false, true);
		
		if (CLEAN_UVITVISIMG(VISfits, threshold, N))
			VISfits->WriteImage(TypeCode::Int32, true);
	}
}

bool Form1::CLEAN_UVITVISIMG(JPFITS::FITSImage^ VISfits, double threshold, int occurences)
{
	double med = 0;//alwys zero if degradiented...which they have to be for this...so make sure... JPMath::Median(VISfits->Image);
	bool cleaned = false;

	#pragma omp parallel for
	for (int y = 1; y < 511; y++)
	{
		//make a horizontal line
		/*array<double>^ row = gcnew array<double>(512);
		for (int x = 0; x < 512; x++)
			row[x] = VISfits[x, y];*/

		//check if there are too many values in the line some range above the median
		int c = 0;
		for (int x = 0; x < 512; x++)
		{
			if (Math::Abs(VISfits[x, y]/* - med*/) >= threshold)
				c++;

			if (c >= occurences)//then a bad line...replace bad pixels with average of previous line and next line pixels
			{
				cleaned = true;
				for (int x = 0; x < 512; x++)
					if (Math::Abs(VISfits[x, y]/* - med*/) >= threshold)
						VISfits[x, y] = (VISfits[x, y - 1] + VISfits[x, y + 1]) / 2;
				break;
			}
		}
	}
	return cleaned;
}

void Form1::CleanVISBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Value = e->ProgressPercentage;
	WAITBAR->TextMsg->Text = "Cleaned " + e->ProgressPercentage + "% of " + Convert::ToInt32(e->UserState).ToString() + " files...";
	WAITBAR->Refresh();
}

void Form1::CleanVISBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	bool cancel = WAITBAR->DialogResult == ::DialogResult::Cancel;

	WAITBAR->Hide();
	WAITBAR->Close();
	Form1::Enabled = true;

	if (!cancel)
	{
		TimeSpan ts = DateTime::Now - DATE;
		MessageBox::Show("Finished cleaning the VIS images in: " + ts.Minutes + "m" + ts.Seconds + "s");
	}
}

void Form1::TBC(array<unsigned char>^ arr, int naxis1, int naxis2)
{
	//make a vector of the frameseqnums and check if they're not monotonic increasing; if not then the list needs a sort
	array<__int64>^ frameseqnums = gcnew array<__int64>(naxis2);
	array<int>^ positions = gcnew array<int>(naxis2);
	__int64 lastframeseqnum = 0;
	bool monotonic = true;
	int byteindx = 0;
	for (int i = 0; i < naxis2; i++)
	{
		//frame sequence number - TTYPE3 = 'FrameSequenceNumber'
		byteindx = i * naxis1 + 36;
		frameseqnums[i] = (__int64(arr[byteindx]) << 56) | (__int64(arr[byteindx + 1]) << 48) | (__int64(arr[byteindx + 2]) << 40) | (__int64(arr[byteindx + 3]) << 32) | (__int64(arr[byteindx + 4]) << 24) | (__int64(arr[byteindx + 5]) << 16) | (__int64(arr[byteindx + 6]) << 8) | __int64(arr[byteindx + 7]);
		positions[i] = i;

		if (monotonic && frameseqnums[i] < lastframeseqnum)
			monotonic = false;

		lastframeseqnum = frameseqnums[i];
	}

	if (!monotonic)//then there was a jump back, so must sort on frameseqnums & their positions
	{
		Array::Sort(frameseqnums, positions);
		array<unsigned char>^ arrcopy = gcnew array<unsigned char>(arr->Length);
		Array::Copy(arr, arrcopy, arr->Length);
		#pragma omp parallel for
		for (int i = 0; i < naxis2; i++)
			for (int j = 0; j < naxis1; j++)
				arr[i * naxis1 + j] = arrcopy[positions[i] * naxis1 + j];
	}

	//now just do a comparison to the reference for each frametime and correct frametime & TIME if needed
	__int64 frametime = 0, tickcount = 0, difftime = 0, difftickms = 0, calcframetime = 0, bzero = 2147483648;
	unsigned __int32 frametimeu32 = 0;
	array<unsigned char>^ dbl = gcnew array<unsigned char>(8);
	double TIME = 0, calcTIME = 0;
	for (int i = 0; i < naxis2; i++)
	{
		//check frametime & tickcount to see if it is true or offset enough from reference
		//frametime
		byteindx = i * naxis1 + 67;
		frametime = __int64(int((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero);
		difftime = frametime - TBC_FRAMETIMEREF;

		//tickcount
		byteindx = i * naxis1 + 75;
		tickcount = __int64(int((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero);
		difftickms = (tickcount - TBC_TICKCOUNTREF) * 1024;

		//now calculate to check for sufficient offset for FRAMETIME
		calcframetime = TBC_FRAMETIMEREF + difftickms;
		__int64 N = (__int64)Math::Floor(double(calcframetime) / 4294967295.0);
		calcframetime = calcframetime - N * 4294967295;
		if (calcframetime < 0)
			calcframetime += 4294967295;

		//if offset less than, say, 350s///jump is 524s, drift was maybe 70s/month...only do seversal day dumps..??......
		if (Math::Abs(calcframetime - frametime) > 70 * 1000)//if then do TBC
		{
			//frametime TBC
			byteindx = i * naxis1 + 67;
			frametime += 524288;
			frametimeu32 = (int)(frametime - bzero);
			arr[byteindx] = ((frametimeu32 >> 24) & 0xff);
			arr[byteindx + 1] = ((frametimeu32 >> 16) & 0xff);
			arr[byteindx + 2] = ((frametimeu32 >> 8) & 0xff);
			arr[byteindx + 3] = (frametimeu32 & 0xff);
		}

		//TIME
		byteindx = i * naxis1 + 0;
		dbl[7] = arr[byteindx];
		dbl[6] = arr[byteindx + 1];
		dbl[5] = arr[byteindx + 2];
		dbl[4] = arr[byteindx + 3];
		dbl[3] = arr[byteindx + 4];
		dbl[2] = arr[byteindx + 5];
		dbl[1] = arr[byteindx + 6];
		dbl[0] = arr[byteindx + 7];
		TIME = BitConverter::ToDouble(dbl, 0);

		calcTIME = TBC_TIMEREF + double(difftickms) / 1000;
		if (Math::Abs(calcTIME - TIME) > 70)//if then do TBC
		{
			//TIME TBC
			byteindx = i * naxis1 + 0;
			TIME += (524288 / 1000);
			dbl = BitConverter::GetBytes(TIME);
			arr[byteindx] = dbl[7];
			arr[byteindx + 1] = dbl[6];
			arr[byteindx + 2] = dbl[5];
			arr[byteindx + 3] = dbl[4];
			arr[byteindx + 4] = dbl[3];
			arr[byteindx + 5] = dbl[2];
			arr[byteindx + 6] = dbl[1];
			arr[byteindx + 7] = dbl[0];
		}
	}
}

::DialogResult Form1::TBC_Reference(array<String^>^ files)
{
	TBC_TICKCOUNTREF = 0;//global int64 variable to be set
	TBC_FRAMETIMEREF = 0;//global int64 variable to be set
	TBC_TIMEREF = 0;//global double variable to be set
	int naxis1, naxis2;
	bool reffound = false;
	int byteindx = 0;
	array<unsigned char>^ arr;
	for (int fi = 0; fi < files->Length; fi++)
	{
		JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable(files[fi], "DETECTOR_DATA");
		//arr = bt->GetTableByteArray();
		arr = bt->BINTABLEByteArray;
		naxis1 = bt->Naxis1;
		naxis2 = bt->Naxis2;
		//arr = FITSBinTable::GetExtensionAsByteArray(files[fi], "DETECTOR_DATA", naxis1, naxis2);
		unsigned __int32 tickcount = 0, frametime = 0, bzero = 2147483648;
		__int64 lastframeseqnum = 0, frameseqnum = 0;
		double TIME = 0;
		array<unsigned char>^ dbl = gcnew array<unsigned char>(8);

		//check if FrameSequenceNumber not monotonic increasing
		//if not then you can make the reference from this file
		for (int i = 0; i < naxis2; i++)
		{
			//frame sequence number - TTYPE3 = 'FrameSequenceNumber'
			byteindx = i * naxis1 + 36;
			frameseqnum = (__int64(arr[byteindx]) << 56) | (__int64(arr[byteindx + 1]) << 48) | (__int64(arr[byteindx + 2]) << 40) | (__int64(arr[byteindx + 3]) << 32) | (__int64(arr[byteindx + 4]) << 24) | (__int64(arr[byteindx + 5]) << 16) | (__int64(arr[byteindx + 6]) << 8) | __int64(arr[byteindx + 7]);

			//tick count - TTYPE14 = 'SecHdrTickCount'
			byteindx = i * naxis1 + 75;
			tickcount = int((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero;//MUST DO IT THIS WAY

			//frame time = 'SecHdrImageFrameTime'
			byteindx = i * naxis1 + 67;
			frametime = int((arr[byteindx] << 24) | (arr[byteindx + 1] << 16) | (arr[byteindx + 2] << 8) | arr[byteindx + 3]) + bzero;//MUST DO IT THIS WAY

			//TIME
			byteindx = i * naxis1 + 0;
			dbl[7] = arr[byteindx];
			dbl[6] = arr[byteindx + 1];
			dbl[5] = arr[byteindx + 2];
			dbl[4] = arr[byteindx + 3];
			dbl[3] = arr[byteindx + 4];
			dbl[2] = arr[byteindx + 5];
			dbl[1] = arr[byteindx + 6];
			dbl[0] = arr[byteindx + 7];
			TIME = BitConverter::ToDouble(dbl, 0);

			if (frameseqnum < lastframeseqnum)//jump back discontinuity...the current frameseqnumber is the good one
			{
				reffound = true;
				TBC_TICKCOUNTREF = (__int64)tickcount;
				TBC_FRAMETIMEREF = (__int64)frametime;
				TBC_TIMEREF = TIME;
				break;
			}

			lastframeseqnum = frameseqnum;
		}

		if (reffound)
			break;
	}
	if (reffound)
	{
		SetReg("CCDLAB", "TBC_TICKCOUNTREF", TBC_TICKCOUNTREF);
		SetReg("CCDLAB", "TBC_FRAMETIMEREF", TBC_FRAMETIMEREF);
		SetReg("CCDLAB", "TBC_TIMEREF", TBC_TIMEREF);
		return ::DialogResult::OK;
	}
	else
	{
		return MessageBox::Show("No reference currently determinable.  Would you like to:" + "\r\n \r\n" + "YES - use last known reference values" + "\r\n" + "NO - proceed without setting reference" + "\r\n" + "CANCEL - exit", "TBC Reference", MessageBoxButtons::YesNoCancel);
	}
}

void Form1::UVFinalizeScienceBtn_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->Text = "Finalize Science Products...";
	WAITBAR->ProgressBar->Maximum = 2 * IMAGESET->Count;
	if (UVFinalizeIncludeTablesChck->Checked)
		WAITBAR->ProgressBar->Maximum = 6 * IMAGESET->Count;	
	UVFinalizeBGWrkr->RunWorkerAsync();
	WAITBAR->ShowDialog();
}

void Form1::UVFinalizeBGWrkr_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	array<String^>^ imagefiles = IMAGESET->FullFileNames;
	if (imagefiles->Length > 1 && !IMAGESET[0]->FileName->Contains("MASTER"))
	{
		::MessageBox::Show("Couldn't make sense of what images to process...", "Error...");
		WAITBAR->CancelBtn->PerformClick();
		return;
	}
	if (imagefiles->Length == 1 && !IMAGESET[0]->FileName->Contains("MASTER"))//perhaps there is only a single orbit image, and hence was never masterized...ex SMC campaign
	{
		//need to masterize the directory
		String^ filedir = Path::GetDirectoryName(imagefiles[0]);
		String^ pardir = Directory::GetParent(filedir)->FullName;
		int indlast = imagefiles[0]->IndexOf("_deFPN");
		String^ test = imagefiles[0]->Substring(0, indlast - 1);
		int indfirst = test->LastIndexOf("_");
		test = imagefiles[0]->Substring(0, indfirst - 1);
		indfirst = test->LastIndexOf("_") + 1;
		String^ replacestr = imagefiles[0]->Substring(indfirst, indlast - indfirst);
		array<String^>^ dirfiles = Directory::GetFiles(filedir);
		for (int j = 0; j < dirfiles->Length; j++)
		{
			String^ newfile = dirfiles[j]->Replace(replacestr, "__MASTER__");
			newfile = pardir + "\\" + newfile->Substring(newfile->LastIndexOf("\\"));
			File::Move(dirfiles[j], newfile);
			if (dirfiles[j] == imagefiles[0])
				imagefiles[0] = newfile;
		}
		Directory::Delete(filedir, true);
	}
	/////////////////////need to get the file path//////////////////////////////
	String^ objdir = Path::GetDirectoryName(imagefiles[0]);
	try
	{
		while (!Directory::Exists(objdir + "\\archive"))
			objdir = Directory::GetParent(objdir)->FullName;
	}
	catch (...)
	{
		FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
		fbd->SelectedPath = IMAGESET->GetCommonDirectory();
		fbd->Description = "Select the parent location to find images to finalize...";
		if (fbd->ShowDialog() == ::DialogResult::Cancel)
		{
			WAITBAR->CancelBtn->PerformClick();
			return;
		}
		objdir = fbd->SelectedPath;
	}

	int N = 2;
	if (UVFinalizeIncludeTablesChck->Checked)
		N = 6;
	array<String^>^ zipfiles = gcnew array<String^>(N * imagefiles->Length);
	//want to get the IMAGE images and their associated exposure maps
	for (int i = 0; i < imagefiles->Length; i++)
	{
		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;

		FITSImage^ image = gcnew FITSImage(imagefiles[i], nullptr, true, false, false, true);

		WAITBAR->Text = "Finalize Science Products: " + image->FileName->Substring(0, image->FileName->IndexOf("___MASTER"));

		String^ dedrift = "_deDrift";
		while (imagefiles[i]->Contains(dedrift + "_deDrift"))
			dedrift += "_deDrift";
		String^ exparrayimagefile = imagefiles[i]->Remove(imagefiles[i]->IndexOf("MASTER")) + "MASTER___ExpArrayImg";
		exparrayimagefile += dedrift + ".fits";
		FITSImage^ expfitsimg = gcnew FITSImage(exparrayimagefile, nullptr, true, true, false, true);
		expfitsimg->CopyHeader(image);

		//need to "debin" the exposure map to be same size as IMAGE
		array<double, 2>^ debinexp = gcnew array<double, 2>(4800, 4800);
		#pragma omp parallel for
		for (int x = 0; x < 4800; x++)
			for (int y = 0; y < 4800; y++)
				debinexp[x, y] = expfitsimg->Image[x / 4, y / 4];

		expfitsimg->SetImage(debinexp, false, true);

		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;
		UVFinalizeBGWrkr->ReportProgress(0, "Writing exposure array");
		expfitsimg->FileName = expfitsimg->FileName->Remove(expfitsimg->FileName->IndexOf("MASTER")) + "MASTER_NORM_EXPARRAY.fits";
		expfitsimg->FilePath = objdir;
		expfitsimg->WriteImage(TypeCode::Double, true);
		zipfiles[i * N] = expfitsimg->FullFileName;
		e->Result = zipfiles;

		if (WAITBAR->DialogResult == ::DialogResult::Cancel)
			return;
		UVFinalizeBGWrkr->ReportProgress(0, "Writing image");
		String^ origfilename = image->FullFileName;
		image->FileName = image->FileName->Remove(image->FileName->IndexOf("MASTER")) + "MASTER_NORMEXP_IMAGE.fits";
		image->FilePath = objdir;
		File::Copy(origfilename, image->FullFileName, true);
		zipfiles[i * N + 1] = image->FullFileName;
		e->Result = zipfiles;

		if (!UVFinalizeIncludeTablesChck->Checked)
			continue;

		try
		{
			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			String^ xyintsname = imagefiles[i]->Remove(imagefiles[i]->IndexOf("_IMAGE")) + ".fits";
			xyintsname = xyintsname->Insert(xyintsname->IndexOf("deFPN_"), "XYInts_List_");
			String^ xydecsname = xyintsname->Replace("XYInts_List", "XYFrac_List");
			array<double, 2>^ xyints = FITSImage::ReadImageArrayOnly(xyintsname, nullptr, true);
			array<double, 2>^ xydecs = FITSImage::ReadImageArrayOnly(xydecsname, nullptr, true);
			array<__int16>^ xcents = gcnew array<__int16>(xyints->GetLength(1));
			array<__int16>^ ycents = gcnew array<__int16>(xyints->GetLength(1));
			#pragma omp parallel for
			for (int j = 0; j < xyints->GetLength(1); j++)
			{
				xcents[j] = __int16(xyints[0, j] + xydecs[0, j] + 16);//use these as the array for the bintable now
				ycents[j] = __int16(xyints[1, j] + xydecs[1, j] + 16);//use these as the array for the bintable now
			}

			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			UVFinalizeBGWrkr->ReportProgress(0, "Writing centroid table");
			String^ binname = objdir + "\\" + image->FileName->Remove(image->FileName->IndexOf("MASTER")) + "MASTER_CENTROIDS_TABLE.fits";
			zipfiles[i * N + 2] = binname;
			e->Result = zipfiles;
			JPFITS::FITSBinTable^ bt = gcnew JPFITS::FITSBinTable();
			bt->SetTTYPEEntries(gcnew array<String^>(2) { "XCENTROID", "YCENTROID" }, gcnew array<String^>(2) { "pix*32", "pix*32" }, gcnew array<Object^>(2) { xcents, ycents });
			bt->AddExtraHeaderKey("COMMENT", "Centroids are at ", "1/32 pixel precision.");
			bt->Write(binname, "CENTROIDS", true);

			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			UVFinalizeBGWrkr->ReportProgress(0, "Writing BJD table");
			String^ bjdname = xyintsname->Remove(xyintsname->IndexOf("XYInts_List")) + "BJDList" + dedrift + ".fits";
			array<double>^ bjds = FITSImage::ReadImageVectorOnly(bjdname, nullptr, true);
			binname = objdir + "\\" + image->FileName->Remove(image->FileName->IndexOf("MASTER")) + "MASTER_BJD_TABLE.fits";
			zipfiles[i * N + 3] = binname;
			e->Result = zipfiles;
			bt = gcnew JPFITS::FITSBinTable();
			bt->AddTTYPEEntry("BaryCenterJD", true, "Day.day", bjds);
			bt->AddExtraHeaderKey("COMMENT", "BaryCenterJD ", "means solar system barycenter.");
			bt->Write(binname, "BJD", true);

			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			UVFinalizeBGWrkr->ReportProgress(0, "Writing flat table");
			String^ flatname = bjdname->Replace("BJDList", "FlatList");
			array<double>^ flats = FITSImage::ReadImageVectorOnly(flatname, nullptr, true);
			binname = objdir + "\\" + image->FileName->Remove(image->FileName->IndexOf("MASTER")) + "MASTER_FLAT_TABLE.fits";
			zipfiles[i * N + 4] = binname;
			e->Result = zipfiles;
			bt = gcnew JPFITS::FITSBinTable();
			bt->AddTTYPEEntry("FlatWeight", true, "unity = 1", flats);
			bt->Write(binname, "FLAT", true);

			if (WAITBAR->DialogResult == ::DialogResult::Cancel)
				return;
			UVFinalizeBGWrkr->ReportProgress(0, "Writing exposure table");
			String^ expname = bjdname->Replace("BJDList", "ExpArrayList");
			array<double>^ exps = FITSImage::ReadImageVectorOnly(expname, nullptr, true);
			binname = objdir + "\\" + image->FileName->Remove(image->FileName->IndexOf("MASTER")) + "MASTER_EXPOSURE_TABLE.fits";
			zipfiles[i * N + 5] = binname;
			e->Result = zipfiles;
			bt = gcnew JPFITS::FITSBinTable();
			bt->AddTTYPEEntry("ExposureMapWeight", true, "unity = 1", exps);
			bt->Write(binname, "EXPOSURE", true);
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
		}
	}

	UVFinalizeBGWrkr->ReportProgress(0, "Please wait while I clean up...");

	String^ ziplist = CCDLABPATH + "tozip.txt";
	StreamWriter^ sw = gcnew StreamWriter(ziplist);
	for (int i = 0; i < zipfiles->Length; i++)
		sw->WriteLine(zipfiles[i]);
	sw->Close();
	String^ fname = FITSImageSet::GetCommonDirectory(zipfiles) + "\\" + DirectoryInfo(FITSImageSet::GetCommonDirectory(zipfiles)).Name;

	::Diagnostics::Process^ p = gcnew ::Diagnostics::Process();
	p->StartInfo->FileName = "c:\\Program Files\\7-Zip\\7zG.exe";
	p->StartInfo->Arguments = "\"a\" " + "\"-tzip\" " + "\"" + fname + "\" " + "\"@" + ziplist;
	p->Start();
	p->WaitForExit();
	if (p->ExitCode != 0)
	{
		for (int j = 0; j < zipfiles->Length; j++)
			if(zipfiles[j] != "" && File::Exists(zipfiles[j]))
				File::Delete(zipfiles[j]);
		File::Delete(fname);
		WAITBAR->CancelBtn->PerformClick();
		return;
	}

	//chck move or copy
	if (UVFinalizeMoveOrCopyZipChck->Text->Contains("Move"))
		for (int i = 0; i < zipfiles->Length; i++)
			File::Delete(zipfiles[i]);

	//chck delete intermdt
	if (UVFinalizeDeleteIntrmdtChck->Checked)
	{
		if (Directory::Exists(objdir + "\\FUV"))
			Directory::Delete(objdir + "\\FUV", true);
		if (Directory::Exists(objdir + "\\NUV"))
			Directory::Delete(objdir + "\\NUV", true);
		if (Directory::Exists(objdir + "\\VIS"))
			Directory::Delete(objdir + "\\VIS", true);
		if (Directory::Exists(objdir + "\\Digested L1"))
			Directory::Delete(objdir + "\\Digested L1", true);
	}

	WAITBAR->Close();
	SetReg("CCDLAB", "UVFINALDIR", objdir);
}

void Form1::UVFinalizeBGWrkr_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	WAITBAR->ProgressBar->Increment(1);
	WAITBAR->TextMsg->Text = (String^)e->UserState;
	WAITBAR->Refresh();
}

void Form1::UVFinalizeBGWrkr_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	if (WAITBAR->DialogResult == ::DialogResult::Cancel)
	{
		array<String^>^ zipfiles = (array<String^>^)e->Result;
		for (int j = 0; j < zipfiles->Length; j++)
			if (zipfiles[j] != "" && File::Exists(zipfiles[j]))
				File::Delete(zipfiles[j]);
	}
	else
	{
		String^ objdir = (String^)GetReg("CCDLAB", "UVFINALDIR");
		if (MessageBox::Show("Open Final Products Directory?", "Open Directory?", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
			System::Diagnostics::Process::Start("Explorer.exe", objdir);
	}
}

void Form1::PSTrackDisplayClearBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	UVITINTMODEDRIFTPOLYPOINTS = nullptr;
	ImageWindow->Refresh();
}

void Form1::invertWCSToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	double CRPIX2 = Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("CRPIX2"));
	double CD1_2 = Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("CD1_2"));
	double CD2_2 = Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("CD2_2"));

	CRPIX2 = 4800 - CRPIX2;
	CD1_2 = -CD1_2;
	CD2_2 = -CD2_2;

	IMAGESET[FILELISTINDEX]->SetKey("CRPIX2", CRPIX2.ToString("F8"), "WCS coordinate reference value on axis 2 (deg)", true, -1);
	IMAGESET[FILELISTINDEX]->SetKey("CD1_2", CD1_2.ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);
	IMAGESET[FILELISTINDEX]->SetKey("CD2_2", CD2_2.ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);

	WCSCopyToLoadedImgs->PerformClick();

	if (WCSRADecShowChck->Checked)
		WCSRADecShowChck->PerformClick();

	WCSRADecShowChck->PerformClick();
}

