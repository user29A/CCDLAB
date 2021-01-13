/*Copyright 2017 Joseph Edwin Postma

Contact email: joepostma@live.ca

This file is part of CCDLAB.

CCDLAB is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CCDLAB is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CCDLAB. If not, see http://www.gnu.org/licenses/. */


#include "StdAfx.h"
#include "PSE.h"

PSE::PSE(void)
{
	this->BGWRKR = gcnew BackgroundWorker();
	this->BGWRKR->WorkerReportsProgress = true;
	this->BGWRKR->WorkerSupportsCancellation = true;
	this->BGWRKR->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &PSE::BGWRKR_DoWork);
	this->BGWRKR->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &PSE::BGWRKR_ProgressChanged);
	this->BGWRKR->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &PSE::BGWRKR_RunWorkerCompleted);
}

PSE::~PSE(void)
{
}

void PSE::Extract(array<double, 2>^ image, double pix_min, double pix_max, double kernel_min, double kernel_max, bool threshholds_as_SN, int kernel_pixwidth, bool auto_background, bool save_sourcekernels, String^ kernel_filename_template, bool elliptical_roi, double roi_x, double roi_x_radius, double roi_y, double roi_y_radius)
{
	KERNEL_PIXWIDTH = kernel_pixwidth;
	PIX_MAX = pix_max;
	PIX_MIN = pix_min;
	N_SRC = 0;
	KERNEL_MIN = kernel_min;
	KERNEL_MAX = kernel_max;
	AUTO_BG = auto_background;
	SAVE_PS = save_sourcekernels;
	SAVE_PS_FILENAME = kernel_filename_template;
	IMAGE = image;
	FITTED = false;
	THRESHHOLDS_AS_SN = threshholds_as_SN;
	ROI_IS_ELLIPTICAL = elliptical_roi;
	ROI_X = roi_x;
	ROI_Y = roi_y;
	ROI_XRAD = roi_x_radius;
	ROI_YRAD = roi_y_radius;

	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "Scanning Image...";
	BGWRKR->RunWorkerAsync(1);
	WAITBAR->ShowDialog();

	if (WAITBAR->DialogResult == DialogResult::Cancel)
		N_SRC = -1;
}

void PSE::Extract(array<double, 2>^ image, array<double>^ XCoords, array<double>^ YCoords, int kernel_pixwidth, bool auto_background, bool save_sourcekernels, String^ kernel_filename_template)
{
	KERNEL_PIXWIDTH = kernel_pixwidth;
	N_SRC = XCoords->Length;
	AUTO_BG = auto_background;
	SAVE_PS = save_sourcekernels;
	SAVE_PS_FILENAME = kernel_filename_template;
	IMAGE = image;
	FITTED = false;
	CENTROIDS_X = gcnew array<double, 1>(N_SRC);
	CENTROIDS_Y = gcnew array<double, 1>(N_SRC);
	FITS_X = gcnew array<double, 1>(N_SRC);
	FITS_Y = gcnew array<double, 1>(N_SRC);
	FITS_FWHM_X = gcnew array<double, 1>(N_SRC);
	FITS_FWHM_Y = gcnew array<double, 1>(N_SRC);
	FITS_PHI = gcnew array<double, 1>(N_SRC);
	CENTROIDS_RADEG = gcnew array<double, 1>(N_SRC);
	CENTROIDS_RAHMS = gcnew array<String^, 1>(N_SRC);
	CENTROIDS_DECDEG = gcnew array<double, 1>(N_SRC);
	CENTROIDS_DECDMS = gcnew array<String^, 1>(N_SRC);
	CENTROIDS_AMPLITUDE = gcnew array<double, 1>(N_SRC);
	CENTROIDS_VOLUME = gcnew array<double, 1>(N_SRC);
	CENTROIDS_BGESTIMATE = gcnew array<double, 1>(N_SRC);
	FITS_AMPLITUDE = gcnew array<double, 1>(N_SRC);
	FITS_VOLUME = gcnew array<double, 1>(N_SRC);
	FITS_BGESTIMATE = gcnew array<double, 1>(N_SRC);
	FITS_RADEG = gcnew array<double, 1>(N_SRC);
	FITS_RAHMS = gcnew array<String^, 1>(N_SRC);
	FITS_DECDEG = gcnew array<double, 1>(N_SRC);
	FITS_DECDMS = gcnew array<String^, 1>(N_SRC);

	int HW = (KERNEL_PIXWIDTH - 1) / 2;
	int intprog = 0;

	for (int i = 0; i < N_SRC; i++)
	{
		double val = IMAGE[(int)XCoords[i] , (int)YCoords[i]];

		double fcmin = 0;//default four-corner minimum
		if (AUTO_BG)
		{
			fcmin = Double::MaxValue;
			if (IMAGE[(int)XCoords[i] - HW, (int)YCoords[i] - HW] < fcmin)
				fcmin = IMAGE[(int)XCoords[i] - HW, (int)YCoords[i] - HW];
			if (IMAGE[(int)XCoords[i] - HW, (int)YCoords[i] + HW] < fcmin)
				fcmin = IMAGE[(int)XCoords[i] - HW, (int)YCoords[i] + HW];
			if (IMAGE[(int)XCoords[i] + HW, (int)YCoords[i] - HW] < fcmin)
				fcmin = IMAGE[(int)XCoords[i] + HW, (int)YCoords[i] - HW];
			if (IMAGE[(int)XCoords[i] + HW, (int)YCoords[i] + HW] < fcmin)
				fcmin = IMAGE[(int)XCoords[i] + HW, (int)YCoords[i] + HW];

			val -= fcmin;
		}

		array<double, 2>^ PSevent = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);// point source event
		array<double, 2>^ PSxcoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);// x coords
		array<double, 2>^ PSycoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);// y coords

		double energy = 0, xweight = 0, yweight = 0;
		int iii = -1;
		for (int ii = (int)XCoords[i] - HW; ii <= (int)XCoords[i] + HW; ii++)
		{
			iii++;
			int jjj = -1;
			for (int jj = (int)YCoords[i] - HW; jj <= (int)YCoords[i] + HW; jj++)
			{
				jjj++;
				PSevent[iii, jjj] = IMAGE[ii, jj] - fcmin;
				PSxcoords[iii, jjj] = (double)ii;
				PSycoords[iii, jjj] = (double)jj;
				energy += PSevent[iii, jjj];
				xweight += PSevent[iii, jjj] * PSxcoords[iii, jjj];
				yweight += PSevent[iii, jjj] * PSycoords[iii, jjj];
			}
		}

		//centroids
		double x = xweight / energy;
		double y = yweight / energy;

		CENTROIDS_X[i] = x;
		CENTROIDS_Y[i] = y;
		CENTROIDS_VOLUME[i] = energy;
		CENTROIDS_AMPLITUDE[i] = val;
		CENTROIDS_BGESTIMATE[i] = fcmin;

		if (SAVE_PS)
		{
			String^ file = SAVE_PS_FILENAME;
			int ind = file->LastIndexOf(".");//for saving PS
			file = String::Concat(file->Substring(0, ind), "_", N_SRC.ToString(), ".fits");

			JPFits::FitsFile^ f = gcnew ::JPFits::FitsFile(file, PSevent, false);
			f->WriteFile(TypeCode::Double);
		}
	}
}

void PSE::Gauss_Symmetric(array<double, 1>^ P0, bool view)
{
	//G = P(0) * exp( -((X-P(1)).^2 + (Y-P(2)).^2 ) / (2*P(3)^2)) + P(4);
	FITS_PARAMS = gcnew array<double, 2>(5, N_SRC);
	FITTED = true;
	FIT_EQUATION = "Gaussian (Circular): P(0) * exp( -((X-P(1)).^2 + (Y-P(2)).^2 ) / (2*P(3)^2)) + P(4)";
	VIEWFITS = view;
	P_INIT = P0;

	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "Fitting Sources...";
	BGWRKR->RunWorkerAsync(2);
	WAITBAR->ShowDialog();

	if (WAITBAR->DialogResult == DialogResult::Cancel)
		N_SRC = -1;
}

void PSE::Gauss_Rotated(array<double, 1>^ P0, bool view)
{
	//G = P(0) * exp( -((x-P(1))*cosd(P(3)) + (y-P(2))*sind(P(3))).^2 / (2*P(4)^2) - ( -(x-P(1))*sind(P(3)) + (y-P(2))*cosd(P(3))).^2 / (2*P(5)^2) ) + P(6);
	FITS_PARAMS = gcnew array<double, 2>(7, N_SRC);
	FITTED = true;
	FIT_EQUATION = "Gaussian (Elliptical): P(0) * exp( -((x-P(1))*cosd(P(3)) + (y-P(2))*sind(P(3))).^2 / (2*P(4)^2) - ( -(x-P(1))*sind(P(3)) + (y-P(2))*cosd(P(3))).^2 / (2*P(5)^2) ) + P(6)";
	VIEWFITS = view;
	P_INIT = P0;

	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "Fitting Sources...";
	BGWRKR->RunWorkerAsync(3);
	WAITBAR->ShowDialog();

	if (WAITBAR->DialogResult == DialogResult::Cancel)
		N_SRC = -1;
}

void PSE::Moffat_Symmetric(array<double, 1>^ P0, bool view)// 2-D Moffat
{
	// G = P(0) * ( 1 + { (X-P(1))^2 + (Y-P(2))^2 } / P(3)^2 ) ^ (-P(4)) + P(5)

	FITS_PARAMS = gcnew array<double, 2>(6, N_SRC);
	FITTED = true;
	FIT_EQUATION = "Moffat (Circular): P(0) * ( 1 + { (X-P(1))^2 + (Y-P(2))^2 } / P(3)^2 ) ^ (-P(4)) + P(5)";
	VIEWFITS = view;
	P_INIT = P0;

	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "Fitting Sources...";
	BGWRKR->RunWorkerAsync(4);
	WAITBAR->ShowDialog();

	if (WAITBAR->DialogResult == DialogResult::Cancel)
		N_SRC = -1;
}

void PSE::Moffat_Rotated(array<double, 1>^ P0, bool view)
{
	//G = P(0) * ( 1 + { ((X-P(1))*cosd(P(3)) + (Y-P(2))*sind(P(3)))^2 } / P(4)^2 + { (-(X-P(1))*sind(P(3)) + (Y-P(2))*cosd(P(3)))^2 } / P(5)^2 ) ^ (-P(6)) + P(7);

	FITS_PARAMS = gcnew array<double, 2>(8, N_SRC);
	FITTED = true;
	FIT_EQUATION = "Moffat (Elliptical): P(0) * ( 1 + { ((X-P(1))*cosd(P(3)) + (Y-P(2))*sind(P(3)))^2 } / P(4)^2 + { (-(X-P(1))*sind(P(3)) + (Y-P(2))*cosd(P(3)))^2 } / P(5)^2 ) ^ (-P(6)) + P(7)";
	VIEWFITS = view;
	P_INIT = P0;

	WAITBAR = gcnew JPWaitBar::WaitBar();
	WAITBAR->ProgressBar->Maximum = 100;
	WAITBAR->Text = "Fitting Sources...";
	BGWRKR->RunWorkerAsync(5);
	WAITBAR->ShowDialog();

	if (WAITBAR->DialogResult == DialogResult::Cancel)
		N_SRC = -1;
}

void PSE::BGWRKR_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	if (::Convert::ToInt32(e->Argument) == 1)//Extract
	{
		ArrayList^ Xs = gcnew ArrayList();// x positions
		ArrayList^ Ys = gcnew ArrayList();// y positions
		ArrayList^ Es = gcnew ArrayList();// energies
		ArrayList^ Vs = gcnew ArrayList();// values
		ArrayList^ Ms = gcnew ArrayList();// 4 corner mins
		int HW = (KERNEL_PIXWIDTH - 1) / 2;
		int intprog = 0;		

		#pragma omp parallel for
		for (int i = HW; i < IMAGE->GetLength(0) - HW; i++)
		{
			if (WAITBAR->DialogResult == DialogResult::Cancel)
				break;

			int nthreads = omp_get_num_threads();
			if (i < IMAGE->GetLength(0) / nthreads)
				if (i * 100 * nthreads / IMAGE->GetLength(0) > intprog)
				{
					intprog = i * 100 * nthreads / IMAGE->GetLength(0);
					BGWRKR->ReportProgress(intprog+1);
				}

			for (int j = HW; j < IMAGE->GetLength(1) - HW; j++)
			{
				if (ROI_IS_ELLIPTICAL)
				{
					double r2 = (double(i) - ROI_X) * (double(i) - ROI_X) / ROI_XRAD / ROI_XRAD + (double(j) - ROI_Y) * (double(j) - ROI_Y) / ROI_YRAD / ROI_YRAD;
					if (r2 > 1)
						goto next1;//pixel outside ROI
				}

				double val = IMAGE[i, j];

				double fcmin = 0;//default four-corner minimum
				if (AUTO_BG)
				{
					/*fcmin = Double::MaxValue;
					if (IMAGE[i - HW, j - HW] < fcmin)
						fcmin = IMAGE[i - HW, j - HW];
					if (IMAGE[i - HW, j + HW] < fcmin)
						fcmin = IMAGE[i - HW, j + HW];
					if (IMAGE[i + HW, j - HW] < fcmin)
						fcmin = IMAGE[i + HW, j - HW];
					if (IMAGE[i + HW, j + HW] < fcmin)
						fcmin = IMAGE[i + HW, j + HW];*/

					array<double>^ cmins = gcnew array<double>(4) { IMAGE[i - HW, j - HW], IMAGE[i - HW, j + HW], IMAGE[i + HW, j - HW], IMAGE[i + HW, j + HW] };
					Array::Sort(cmins);
					fcmin = (cmins[1] /*+ cmins[2]*/)/* / 2*/;

					val -= fcmin;
				}

				if (!THRESHHOLDS_AS_SN)
				{
					if (val < PIX_MIN || val > PIX_MAX)
						goto next1;//pixel value outside threshold bounds
				}
				else//check as S/N
				{
					double Nbg = 0;
					if (fcmin < 1)
						Nbg = 1;
					else
						Nbg = Math::Sqrt(fcmin);
					double SNval = val / Nbg;
					if (SNval < PIX_MIN || SNval > PIX_MAX)
						goto next1;//pixel value outside threshold bounds
				}

				array<double, 2>^ PSevent = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);// point source event
				array<double, 2>^ PSxcoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);// x coords
				array<double, 2>^ PSycoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);// y coords

				double energy = 0, xweight = 0, yweight = 0;
				int iii = -1;
				for (int ii = i - HW; ii <= i + HW; ii++)
				{
					iii++;
					int jjj = -1;
					for (int jj = j - HW; jj <= j + HW; jj++)
					{
						jjj++;

						if (IMAGE[ii, jj] - fcmin > val)
							goto next1;// max check failure, if the pixel isn't the maximum in the kernel, then skip this pixel and keep going, if not, then extract position info

						PSevent[iii, jjj] = IMAGE[ii, jj] - fcmin;
						PSxcoords[iii, jjj] = (double)ii;
						PSycoords[iii, jjj] = (double)jj;
						energy += PSevent[iii, jjj];
						xweight += PSevent[iii, jjj] * PSxcoords[iii, jjj];
						yweight += PSevent[iii, jjj] * PSycoords[iii, jjj];
					}
				}

				if (!THRESHHOLDS_AS_SN)
				{
					if (energy < KERNEL_MIN || energy > KERNEL_MAX)
						goto next1;//pixel value outside threshold bounds
				}
				else//check as S/N
				{
					double Nbg = 0;
					if (fcmin < 1)
						Nbg = Math::Sqrt(double(KERNEL_PIXWIDTH*KERNEL_PIXWIDTH));
					else
						Nbg = Math::Sqrt(fcmin*double(KERNEL_PIXWIDTH*KERNEL_PIXWIDTH));
					double SNenergy = energy / Nbg;
					if (energy < KERNEL_MIN || energy > KERNEL_MAX)
						goto next1;//pixel value outside threshold bounds
				}

			   //centroids
				double x = xweight / energy;
				double y = yweight / energy;
				#pragma omp critical
				{
					Xs->Add(x);
					Ys->Add(y);
					Es->Add(energy);
					Vs->Add(val);
					Ms->Add(fcmin);

					if (SAVE_PS)
					{
						String^ file = SAVE_PS_FILENAME;
						int ind = file->LastIndexOf(".");//for saving PS
						file = String::Concat(file->Substring(0, ind), "_", Xs->Count.ToString(), ".fits");

						JPFits::FitsFile^ f;
						f = gcnew ::JPFits::FitsFile(file, PSevent, false);
						f->WriteFile(TypeCode::Double);
					}
				}
			next1:;
			}
		}

		BGWRKR->ReportProgress(-1);
		for (int i = Xs->Count - 1; i >= 0; i--)//need to go through and exorcise equal adjacent value pairs
		{
			if (WAITBAR->DialogResult == DialogResult::Cancel)
				break;

			if (i * 100 / Xs->Count < intprog)
			{
				intprog--;
				BGWRKR->ReportProgress(-intprog);
			}

			for (int j = i - 1; j >= 0; j--)
				if (((double)Xs[i] - (double)Xs[j])*((double)Xs[i] - (double)Xs[j]) + ((double)Ys[i] - (double)Ys[j])*((double)Ys[i] - (double)Ys[j]) < HW*HW)
				{
					Xs->RemoveAt(j);
					Ys->RemoveAt(j);
					Es->RemoveAt(j);
					Vs->RemoveAt(j);
					Ms->RemoveAt(j);
					i--;
				}
		}

		if (WAITBAR->DialogResult == DialogResult::Cancel)
			return;

		N_SRC = Xs->Count;
		CENTROIDS_X = gcnew array<double, 1>(N_SRC);
		CENTROIDS_Y = gcnew array<double, 1>(N_SRC);
		FITS_X = gcnew array<double, 1>(N_SRC);
		FITS_Y = gcnew array<double, 1>(N_SRC);
		FITS_FWHM_X = gcnew array<double, 1>(N_SRC);
		FITS_FWHM_Y = gcnew array<double, 1>(N_SRC);
		FITS_PHI = gcnew array<double, 1>(N_SRC);
		FITS_CHISQNORM = gcnew array<double, 1>(N_SRC);
		CENTROIDS_RADEG = gcnew array<double, 1>(N_SRC);
		CENTROIDS_RAHMS = gcnew array<String^, 1>(N_SRC);
		CENTROIDS_DECDEG = gcnew array<double, 1>(N_SRC);
		CENTROIDS_DECDMS = gcnew array<String^, 1>(N_SRC);
		CENTROIDS_AMPLITUDE = gcnew array<double, 1>(N_SRC);
		CENTROIDS_VOLUME = gcnew array<double, 1>(N_SRC);
		CENTROIDS_BGESTIMATE = gcnew array<double, 1>(N_SRC);
		FITS_AMPLITUDE = gcnew array<double, 1>(N_SRC);
		FITS_VOLUME = gcnew array<double, 1>(N_SRC);
		FITS_BGESTIMATE = gcnew array<double, 1>(N_SRC);
		FITS_RADEG = gcnew array<double, 1>(N_SRC);
		FITS_RAHMS = gcnew array<String^, 1>(N_SRC);
		FITS_DECDEG = gcnew array<double, 1>(N_SRC);
		FITS_DECDMS = gcnew array<String^, 1>(N_SRC);

		for (int i = 0; i < N_SRC; i++)
		{
			CENTROIDS_X[i] = (double)(Xs[i]);
			CENTROIDS_Y[i] = (double)(Ys[i]);
			CENTROIDS_AMPLITUDE[i] = (double)(Vs[i]);
			CENTROIDS_VOLUME[i] = (double)(Es[i]);
			CENTROIDS_BGESTIMATE[i] = (double)(Ms[i]);
		}
		return;
	}

	MLCCDLAB::MLSurface^ surf;

	if (::Convert::ToInt32(e->Argument) == 2)//Fit symmetric Gaussian
	{
		array<double, 2>^ vals = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width values
		array<double, 2>^ xcoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width x coords
		array<double, 2>^ ycoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width y coords
		int HW = (KERNEL_PIXWIDTH - 1) / 2;

		int intprog = 0;
		for (int k = 0; k < N_SRC; k++)
		{
			if (WAITBAR->DialogResult == DialogResult::Cancel)
				break;
			if (k * 100 / N_SRC > intprog)
			{
				intprog = k * 100 / N_SRC;
				BGWRKR->ReportProgress(intprog + 100);
			}

			int iii = -1;
			for (int ii = int(CENTROIDS_X[k] + .5) - HW; ii <= int(CENTROIDS_X[k] + .5) + HW; ii++)
			{
				iii++;	int jjj = -1;
				for (int jj = int(CENTROIDS_Y[k] + .5) - HW; jj <= int(CENTROIDS_Y[k] + .5) + HW; jj++)
				{
					jjj++;
					vals[iii, jjj] = (double)(IMAGE[ii, jj]);
					xcoords[iii, jjj] = (double)ii;
					ycoords[iii, jjj] = (double)jj;
				}
			}

			array<double, 2>^ fit_resid = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);
			array<double>^ p = gcnew array<double, 1>(5) { JPMath::Max(vals) - JPMath::Min(vals), xcoords[HW, HW], ycoords[HW, HW], 2, JPMath::Min(vals) };
			try
			{
				JPMath::Fit_Gaussian2d(xcoords, ycoords, vals, p, nullptr, fit_resid);
			}
			catch (Exception^ e)
			{
				MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
			}

			FITS_PARAMS[0, k] = p[0];
			FITS_PARAMS[1, k] = p[1];
			FITS_PARAMS[2, k] = p[2];
			FITS_PARAMS[3, k] = p[3];
			FITS_PARAMS[4, k] = p[4];

			FITS_X[k] = p[1];
			FITS_Y[k] = p[2];
			FITS_FWHM_X[k] = 2.355 * p[3];
			FITS_FWHM_Y[k] = FITS_FWHM_X[k];
			FITS_VOLUME[k] = 2 * Math::PI * p[0] * p[3] * p[3];
			FITS_BGESTIMATE[k] = p[4];
			FITS_AMPLITUDE[k] = p[0];

			double chisq_norm = 0;
			for (int i = 0; i < KERNEL_PIXWIDTH; i++)
				for (int j = 0; j < KERNEL_PIXWIDTH; j++)
				{
					if (vals[i, j] - p[p->Length - 1] == 0)
						chisq_norm += fit_resid[i, j] * fit_resid[i, j];
					else
						chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math::Abs(vals[i, j] - p[p->Length - 1]);
				}
			chisq_norm /= (vals->Length - p->Length);
			FITS_CHISQNORM[k] = chisq_norm;

			if (VIEWFITS)
			{
				surf= gcnew MLCCDLAB::MLSurface();
				array<double, 2>^ fit = gcnew array<double, 2>(vals->GetLength(0), vals->GetLength(1));
				JPMath::Gaussian2d(xcoords, ycoords, fit, p);
				MWNumericArray^ mwfit = gcnew MWNumericArray(fit);
				MWNumericArray^ mwsubim = gcnew MWNumericArray(vals);
				MWCharArray^ type = gcnew MWCharArray("Symmetric Gaussian");
				surf->Surf_FitOverlay(mwsubim, mwfit, type);

				String^ disp = "";
				for (int i = 0; i < 5; i++)
					disp += "p[" + i.ToString() + "] = " + p[i] + "    ";
				DialogResult res = ::MessageBox::Show(disp, "Click OK to continue...", MessageBoxButtons::OKCancel);

				if (res == DialogResult::Cancel)
				{
					VIEWFITS = false;
				}
			}
		}
	}

	if (::Convert::ToInt32(e->Argument) == 3)//Fit elliptical Gaussian
	{
		array<double, 2>^ vals = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width values
		array<double, 2>^ xcoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width x coords
		array<double, 2>^ ycoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width y coords
		int HW = (KERNEL_PIXWIDTH - 1) / 2;

		int intprog = 0;
		for (int k = 0; k < N_SRC; k++)
		{
			if (WAITBAR->DialogResult == DialogResult::Cancel)
				break;
			if (k * 100 / N_SRC > intprog)
			{
				intprog = k * 100 / N_SRC;
				BGWRKR->ReportProgress(intprog + 100);
			}

			int iii = -1;
			for (int ii = int(CENTROIDS_X[k] + .5) - (KERNEL_PIXWIDTH - 1) / 2; ii <= int(CENTROIDS_X[k] + .5) + (KERNEL_PIXWIDTH - 1) / 2; ii++)
			{
				iii++;	int jjj = -1;
				for (int jj = int(CENTROIDS_Y[k] + .5) - (KERNEL_PIXWIDTH - 1) / 2; jj <= int(CENTROIDS_Y[k] + .5) + (KERNEL_PIXWIDTH - 1) / 2; jj++)
				{
					jjj++;
					vals[iii, jjj] = (double)(IMAGE[ii, jj]);
					xcoords[iii, jjj] = (double)ii;
					ycoords[iii, jjj] = (double)jj;
				}
			}

			array<double, 2>^ fit_resid = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);
			array<double, 1>^ p = gcnew array<double, 1>(7) { JPMath::Max(vals), xcoords[HW, HW], ycoords[HW, HW], 0, 2, 2, JPMath::Min(vals) };
			JPMath::Fit_Gaussian2d(xcoords, ycoords, vals, p, nullptr, fit_resid);

			FITS_PARAMS[0, k] = p[0];
			FITS_PARAMS[1, k] = p[1];
			FITS_PARAMS[2, k] = p[2];
			FITS_PARAMS[3, k] = p[3];
			FITS_PARAMS[4, k] = p[4];
			FITS_PARAMS[5, k] = p[5];
			FITS_PARAMS[6, k] = p[6];

			FITS_FWHM_X[k] = 2.355 * p[4];
			FITS_FWHM_Y[k] = 2.355 * p[5];
			FITS_PHI[k] = p[3];
			FITS_VOLUME[k] = 2 * Math::PI*p[0] * p[4] * p[5];
			FITS_BGESTIMATE[k] = p[6];
			FITS_AMPLITUDE[k] = p[0];

			double chisq_norm = 0;
			for (int i = 0; i < KERNEL_PIXWIDTH; i++)
				for (int j = 0; j < KERNEL_PIXWIDTH; j++)
				{
					if (vals[i, j] - p[p->Length - 1] == 0)
						chisq_norm += fit_resid[i, j] * fit_resid[i, j];
					else
						chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math::Abs(vals[i, j] - p[p->Length - 1]);
				}
			chisq_norm /= (vals->Length - p->Length);
			FITS_CHISQNORM[k] = chisq_norm;

			if (VIEWFITS)
			{
				surf = gcnew MLCCDLAB::MLSurface();
				array<double, 2>^ fit = gcnew array<double, 2>(vals->GetLength(0), vals->GetLength(1));
				JPMath::Gaussian2d(xcoords, ycoords, fit, p);
				MWNumericArray^ mwfit = gcnew MWNumericArray(fit);
				MWNumericArray^ mwsubim = gcnew MWNumericArray(vals);
				MWCharArray^ type = gcnew MWCharArray("Elliptical Gaussian");
				surf->Surf_FitOverlay(mwsubim, mwfit, type);

				String^ disp = "";
				for (int i = 0; i < 5; i++)
					disp += "p[" + i.ToString() + "] = " + p[i] + "    ";
				DialogResult res = ::MessageBox::Show(disp, "Click OK to continue...", MessageBoxButtons::OKCancel);
				
				if (res == DialogResult::Cancel)
				{
					VIEWFITS = false;
				}
			}
		}
	}

	if (::Convert::ToInt32(e->Argument) == 4)//Fit symmetric Moffat
	{
		array<double, 2>^ vals = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width values
		array<double, 2>^ xcoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width x coords
		array<double, 2>^ ycoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width y coords
		int HW = (KERNEL_PIXWIDTH - 1) / 2;

		int intprog = 0;
		for (int k = 0; k < N_SRC; k++)
		{
			if (WAITBAR->DialogResult == DialogResult::Cancel)
				break;
			if (k * 100 / N_SRC > intprog)
			{
				intprog = k * 100 / N_SRC;
				BGWRKR->ReportProgress(intprog + 100);
			}

			int iii = -1;
			for (int ii = int(CENTROIDS_X[k] + .5) - (KERNEL_PIXWIDTH - 1) / 2; ii <= int(CENTROIDS_X[k] + .5) + (KERNEL_PIXWIDTH - 1) / 2; ii++)
			{
				iii++;	int jjj = -1;
				for (int jj = int(CENTROIDS_Y[k] + .5) - (KERNEL_PIXWIDTH - 1) / 2; jj <= int(CENTROIDS_Y[k] + .5) + (KERNEL_PIXWIDTH - 1) / 2; jj++)
				{
					jjj++;
					vals[iii, jjj] = (double)(IMAGE[ii, jj]);
					xcoords[iii, jjj] = (double)ii;
					ycoords[iii, jjj] = (double)jj;
				}
			}
			
			array<double, 2>^ fit_resid = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);
			array<double, 1>^ p = gcnew array<double, 1>(6) { JPMath::Max(vals), xcoords[HW, HW], ycoords[HW, HW], 2, 2, JPMath::Min(vals) };
			JPMath::Fit_Moffat2d(xcoords, ycoords, vals, p, nullptr, fit_resid);

			FITS_PARAMS[0, k] = p[0];
			FITS_PARAMS[1, k] = p[1];
			FITS_PARAMS[2, k] = p[2];
			FITS_PARAMS[3, k] = p[3];
			FITS_PARAMS[4, k] = p[4];
			FITS_PARAMS[5, k] = p[5];

			FITS_X[k] = p[1];
			FITS_Y[k] = p[2];
			FITS_FWHM_X[k] = 2 * p[3] * Math::Sqrt(Math::Pow(2, 1 / (p[4])) - 1);
			FITS_FWHM_Y[k] = FITS_FWHM_X[k];
			FITS_VOLUME[k] = Math::PI * p[3] * p[3] * p[0] / (p[4] - 1);
			FITS_BGESTIMATE[k] = p[5];
			FITS_AMPLITUDE[k] = p[0];

			double chisq_norm = 0;
			for (int i = 0; i < KERNEL_PIXWIDTH; i++)
				for (int j = 0; j < KERNEL_PIXWIDTH; j++)
				{
					if (vals[i, j] - p[p->Length - 1] == 0)
						chisq_norm += fit_resid[i, j] * fit_resid[i, j];
					else
						chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math::Abs(vals[i, j] - p[p->Length - 1]);
				}
			chisq_norm /= (vals->Length - p->Length);
			FITS_CHISQNORM[k] = chisq_norm;

			if (VIEWFITS)
			{
				surf = gcnew MLCCDLAB::MLSurface();
				array<double, 2>^ fit = gcnew array<double, 2>(vals->GetLength(0), vals->GetLength(1));
				JPMath::Moffat2d(xcoords, ycoords, fit, p);
				MWNumericArray^ mwfit = gcnew MWNumericArray(fit);
				MWNumericArray^ mwsubim = gcnew MWNumericArray(vals);
				MWCharArray^ type = gcnew MWCharArray("Symmetric Moffat");
				surf->Surf_FitOverlay(mwsubim, mwfit, type);

				String^ disp = "";
				for (int i = 0; i < 5; i++)
					disp += "p[" + i.ToString() + "] = " + p[i] + "    ";
				DialogResult res = ::MessageBox::Show(disp, "Click OK to continue...", MessageBoxButtons::OKCancel);

				if (res == DialogResult::Cancel)
				{
					VIEWFITS = false;
				}
			}
		}
	}

	if (::Convert::ToInt32(e->Argument) == 5)//Fit elliptical Moffat
	{
		array<double, 2>^ vals = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width values
		array<double, 2>^ xcoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width x coords
		array<double, 2>^ ycoords = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);//width y coords
		int HW = (KERNEL_PIXWIDTH - 1) / 2;

		int intprog = 0;
		for (int k = 0; k < N_SRC; k++)
		{
			if (WAITBAR->DialogResult == DialogResult::Cancel)
				break;
			if (k * 100 / N_SRC > intprog)
			{
				intprog = k * 100 / N_SRC;
				BGWRKR->ReportProgress(intprog + 100);
			}

			int iii = -1;
			for (int ii = int(CENTROIDS_X[k] + .5) - (KERNEL_PIXWIDTH - 1) / 2; ii <= int(CENTROIDS_X[k] + .5) + (KERNEL_PIXWIDTH - 1) / 2; ii++)
			{
				iii++;	int jjj = -1;
				for (int jj = int(CENTROIDS_Y[k] + .5) - (KERNEL_PIXWIDTH - 1) / 2; jj <= int(CENTROIDS_Y[k] + .5) + (KERNEL_PIXWIDTH - 1) / 2; jj++)
				{
					jjj++;
					vals[iii, jjj] = (double)(IMAGE[ii, jj]);
					xcoords[iii, jjj] = (double)ii;
					ycoords[iii, jjj] = (double)jj;
				}
			}

			array<double, 2>^ fit_resid = gcnew array<double, 2>(KERNEL_PIXWIDTH, KERNEL_PIXWIDTH);
			array<double, 1>^ p = gcnew array<double, 1>(8) { JPMath::Max(vals), xcoords[HW, HW], ycoords[HW, HW], 0, 2, 2, 2, JPMath::Min(vals) };
			JPMath::Fit_Moffat2d(xcoords, ycoords, vals, p, nullptr, fit_resid);

			FITS_PARAMS[0, k] = p[0];
			FITS_PARAMS[1, k] = p[1];
			FITS_PARAMS[2, k] = p[2];
			FITS_PARAMS[3, k] = p[3];
			FITS_PARAMS[4, k] = p[4];
			FITS_PARAMS[5, k] = p[5];
			FITS_PARAMS[6, k] = p[6];
			FITS_PARAMS[7, k] = p[7];

			FITS_X[k] = p[1];
			FITS_Y[k] = p[2];
			FITS_FWHM_X[k] = 2 * p[4] * Math::Sqrt(Math::Pow(2, 1 / (p[6])) - 1);
			FITS_FWHM_Y[k] = 2 * p[5] * Math::Sqrt(Math::Pow(2, 1 / (p[6])) - 1);
			FITS_PHI[k] = p[3];
			FITS_VOLUME[k] = Math::PI * p[4] * p[5] * p[0] / (p[6] - 1);
			FITS_BGESTIMATE[k] = p[7];
			FITS_AMPLITUDE[k] = p[0];

			double chisq_norm = 0;
			for (int i = 0; i < KERNEL_PIXWIDTH; i++)
				for (int j = 0; j < KERNEL_PIXWIDTH; j++)
				{
					if (vals[i, j] - p[p->Length - 1] == 0)
						chisq_norm += fit_resid[i, j] * fit_resid[i, j];
					else
						chisq_norm += fit_resid[i, j] * fit_resid[i, j] / Math::Abs(vals[i, j] - p[p->Length - 1]);
				}
			chisq_norm /= (vals->Length - p->Length);
			FITS_CHISQNORM[k] = chisq_norm;

			if (VIEWFITS)
			{
				surf = gcnew MLCCDLAB::MLSurface();
				array<double, 2>^ fit = gcnew array<double, 2>(vals->GetLength(0), vals->GetLength(1));
				JPMath::Moffat2d(xcoords, ycoords, fit, p);
				MWNumericArray^ mwfit = gcnew MWNumericArray(fit);
				MWNumericArray^ mwsubim = gcnew MWNumericArray(vals);
				MWCharArray^ type = gcnew MWCharArray("Elliptical Moffat");
				surf->Surf_FitOverlay(mwsubim, mwfit, type);

				String^ disp = "";
				for (int i = 0; i < 5; i++)
					disp += "p[" + i.ToString() + "] = " + p[i] + "    ";
				DialogResult res = ::MessageBox::Show(disp, "Click OK to continue...", MessageBoxButtons::OKCancel);

				if (res == DialogResult::Cancel)
				{
					VIEWFITS = false;
				}
			}
		}
	}
}

void PSE::BGWRKR_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	if (e->ProgressPercentage >= 0 && e->ProgressPercentage <= 100)
	{
		WAITBAR->ProgressBar->Value = e->ProgressPercentage;
		WAITBAR->TextMsg->Text = "Scanned " + e->ProgressPercentage.ToString() + "% of the image...";
	}

	if (e->ProgressPercentage < 0)
	{
		WAITBAR->ProgressBar->Value = -e->ProgressPercentage;
		WAITBAR->TextMsg->Text = "Please wait while I remove adjacent sources..." + (-e->ProgressPercentage).ToString() + "%";
	}

	if (e->ProgressPercentage > 100)
	{
		WAITBAR->ProgressBar->Value = e->ProgressPercentage - 100;
		WAITBAR->TextMsg->Text = "Fitted " + (e->ProgressPercentage - 100).ToString() + "% of the sources...";
	}
	
	WAITBAR->Refresh();
}

void PSE::BGWRKR_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	WAITBAR->Close();
}

void PSE::SavePointParameters()
{
	SaveFileDialog^ sfd = gcnew ::SaveFileDialog();
	sfd->Filter = "Comma Delimited Text file (*.txt)|*.txt";
	if (sfd->ShowDialog() == ::DialogResult::Cancel)
		return;

	GeneratePSETable();

	StreamWriter^ sw = gcnew StreamWriter(sfd->FileName);
	for (int j = 0; j < PSE_TABLE->GetLength(1); j++)
	{
		for (int i = 0; i < PSE_TABLE->GetLength(0); i++)
			sw->Write(PSE_TABLE[i, j] + ",");
		sw->WriteLine();
	}
	sw->Close();
}

void PSE::GeneratePSETable()
{
	if (!FITTED)
		PSE_TABLE = gcnew array<String^, 2>(9, N_SRC + 1);
	else
		PSE_TABLE = gcnew array<String^, 2>(22, N_SRC + 1);

	PSE_TABLE[0, 0] = "Pixel Amplitude";
	PSE_TABLE[1, 0] = "Pixel Volume";
	PSE_TABLE[2, 0] = "Pixel Background";
	PSE_TABLE[3, 0] = "Pixel X-Centroid";
	PSE_TABLE[4, 0] = "Pixel Y-Centroid";
	PSE_TABLE[5, 0] = "Pixel Right Ascension (deg)";
	PSE_TABLE[6, 0] = "Pixel Declination (deg)";
	PSE_TABLE[7, 0] = "Pixel Right Ascension (hms)";
	PSE_TABLE[8, 0] = "Pixel Declination (d ' '')";

	if (FITTED)
	{
		PSE_TABLE[9, 0] = "Fit Amplitude";
		PSE_TABLE[10, 0] = "Fit Volume";
		PSE_TABLE[11, 0] = "Fit Background";
		PSE_TABLE[12, 0] = "Fit X-Centroid";
		PSE_TABLE[13, 0] = "Fit Y-Centroid";
		PSE_TABLE[14, 0] = "Fit Right Ascension (deg)";
		PSE_TABLE[15, 0] = "Fit Declination (deg)";
		PSE_TABLE[16, 0] = "Fit Right Ascension (hms)";
		PSE_TABLE[17, 0] = "Fit Declination (d ' '')";
		PSE_TABLE[18, 0] = "Fit FWHM_X";
		PSE_TABLE[19, 0] = "Fit FWHM_Y";
		PSE_TABLE[20, 0] = "Fit Phi";
		PSE_TABLE[21, 0] = "Fit ChiSqNorm";
	}

	for (int i = 0; i < N_SRC; i++)
	{
		PSE_TABLE[0, i + 1] = CENTROIDS_AMPLITUDE[i].ToString();
		PSE_TABLE[1, i + 1] = CENTROIDS_VOLUME[i].ToString();
		PSE_TABLE[2, i + 1] = CENTROIDS_BGESTIMATE[i].ToString();
		PSE_TABLE[3, i + 1] = CENTROIDS_X[i].ToString();
		PSE_TABLE[4, i + 1] = CENTROIDS_Y[i].ToString();
		PSE_TABLE[5, i + 1] = CENTROIDS_RADEG[i].ToString();
		PSE_TABLE[6, i + 1] = CENTROIDS_DECDEG[i].ToString();
		PSE_TABLE[7, i + 1] = CENTROIDS_RAHMS[i];
		PSE_TABLE[8, i + 1] = CENTROIDS_DECDMS[i];

		if (FITTED)
		{
			PSE_TABLE[9, i + 1] = FITS_AMPLITUDE[i].ToString();
			PSE_TABLE[10, i + 1] = FITS_VOLUME[i].ToString();
			PSE_TABLE[11, i + 1] = FITS_BGESTIMATE[i].ToString();
			PSE_TABLE[12, i + 1] = FITS_X[i].ToString();
			PSE_TABLE[13, i + 1] = FITS_Y[i].ToString();
			PSE_TABLE[14, i + 1] = FITS_RADEG[i].ToString();
			PSE_TABLE[15, i + 1] = FITS_DECDEG[i].ToString();
			PSE_TABLE[16, i + 1] = FITS_RAHMS[i];
			PSE_TABLE[17, i + 1] = FITS_DECDMS[i];
			PSE_TABLE[18, i + 1] = FITS_FWHM_X[i].ToString();
			PSE_TABLE[19, i + 1] = FITS_FWHM_Y[i].ToString();
			PSE_TABLE[20, i + 1] = FITS_PHI[i].ToString();
			PSE_TABLE[21, i + 1] = FITS_CHISQNORM[i].ToString();
		}
	}
}

void PSE::GenerateRADecCoords(WCS^ wcs)
{
	for (int i = 0; i < N_SRC; i++)
	{
		double a, d;
		String^ RAhms;
		String^ DECdamas;

		wcs->GETCOORD(CENTROIDS_X[i], CENTROIDS_Y[i], true, "TAN", a, d, RAhms, DECdamas);

		CENTROIDS_RAHMS[i] = RAhms;
		CENTROIDS_RADEG[i] = a;
		CENTROIDS_DECDEG[i] = d;
		CENTROIDS_DECDMS[i] = DECdamas;

		if (FITTED)
		{
			wcs->GETCOORD(FITS_X[i], FITS_Y[i], true, "TAN", a, d, RAhms, DECdamas);

			FITS_RAHMS[i] = RAhms;
			FITS_RADEG[i] = a;
			FITS_DECDEG[i] = d;
			FITS_DECDMS[i] = DECdamas;
		}
	}

	WCS_GENERATED = true;
}

//array<double,2>^ PSE::MatchPoints(array<double>^ xref, array<double>^ yref, array<double>^ xcom, array<double>^ ycom)
//{
//	array<double,2>^ result;
//	//take the reference xy points list, and find the comparison xy points list that match, i.e. that are the same points
//
//	//xy points must be same length for each reference and comparison, but reference and comparison do not need to be same length and in general not
//
//	//xy points lists must have at least 3 elements each
//	if (xref->Length < 3 || xcom->Length < 3)
//	{
//		::MessageBox::Show("Not enough points...","Error");
//		return result;
//	}
//
//	if (xref->Length < xcom->Length)
//	{
//		array<double>^ tempx = xref;
//		array<double>^ tempy = yref;
//	    
//		xref = xcom;
//		yref = ycom;
//		xcom = tempx;
//		ycom = tempy;
//	}
//
//	//for both the reference and comparison list, for each point create a characterization list which lists the distances to other points
//	//depending on length of list, might not need to list distances to every single other point for a given point
//
//	array<double,2>^ refchararray = gcnew array<double,2>(xref->Length - 1, xref->Length);//reference characteristics array
//	#pragma omp parallel for
//	for (int i = 0; i < xref->Length; i++)
//	{
//	   int jc = 0;
//	   for (int j = 0; j < xref->Length; j++)
//	   {
//		   if (j == i)
//			   continue;
//		   jc++;
//		   refchararray[jc,i] = (xref[i] - xref[j])*(xref[i] - xref[j]) + (yref[i] - yref[j])*(yref[i] - yref[j]);//squared distance
//	   }
//	}
//
//	array<double,2>^ comchararray = gcnew array<double,2>(xcom->Length - 1, xcom->Length);//reference characteristics array
//	#pragma omp parallel for
//	for (int i = 0; i < xcom->Length; i++)
//	{
//	   int jc = 0;
//	   for (int j = 0; j < xcom->Length; j++)
//	   {
//		   if (j == i)
//			   continue;
//		   jc++;
//		   comchararray[jc,i] = (xcom[i] - xcom[j])*(xcom[i] - xcom[j]) + (ycom[i] - ycom[j])*(ycom[i] - ycom[j]);//squared distance
//	   }
//	}
//
//	//then for each point in the reference list, find the matching points in the comparison list given the distance characteristics for each point
//	//find the j'th point that matches the i'th point by examing their characteristics
//
//	array<double>^ matches = gcnew array<double>(xref->Length);
//
//	double delta = 8;//arbitrary...this needs set perhaps in the function arguments
//	delta *= delta;//squared distance
//
//	#pragma omp parallel for
//	for (int i = 0; i < xref->Length; i++)
//	{
//		array<double>^ rank = gcnew array<double>(xcom->Length);//need to rank which comparison gives the best match
//		for (int j = 0; j < xcom->Length; j++)
//		{
//			for (int ii = 0; ii < xref->Length - 1; ii++)
//			{
//				for (int jj = 0; jj < xcom->Length-1; jj++)
//				{
//					if (Math::Abs(refchararray[ii,i] - comchararray[jj,j]) < delta)
//					{
//						rank[j]++;
//						break;
//					}
//				}
//			}
//		}
//	    
//		//now have j'ths ranks for i'th...find which one is hihgest rank, or ranked at all...
//	    //highest rank could be maximum of jj = length(xcom)-1
//		int maxrankindex;
//		double maxrank = JPMath::Max(rank, maxrankindex);
//
//		//there does need to be some confidence in the rank, because just one match wouldn't be good enough for ex.
//		double confidence = 0.85;//set in command arguments?
//		if (maxrank <= Math::Min(xcom->Length - 1,xref->Length - 1)*confidence)//no matches or poor match for this i'th point
//			matches[i] = -1;//to indicate no or poor match
//		else
//			matches[i] = maxrankindex;
//	}
//
//	//now have the indices of the comparison points list which match the reference points list
//	//now want to create new point lists which match indices point for point
//
//	array<int>^ f = JPMath::Find(matches,-1,"==");
//	array<double>^ xrefnew = gcnew array<double>(matches->Length - f->Length);
//	array<double>^ yrefnew = gcnew array<double>(matches->Length - f->Length);
//	array<double>^ xcomnew = gcnew array<double>(matches->Length - f->Length);
//	array<double>^ ycomnew = gcnew array<double>(matches->Length - f->Length);
//	result = gcnew array<double, 2>(4, matches->Length - f->Length);
//
//	int c = 0;
//	for (int i = 0; i < matches->Length; i++)
//	{
//		if (matches[i] == -1)
//			continue;
//		c++;
//		xrefnew[c] = xref[i];
//		yrefnew[c] = yref[i];
//		xcomnew[c] = xcom[(int)matches[i]];
//		ycomnew[c] = ycom[(int)matches[i]];
//
//		result[0, c] = xref[i];
//		result[1, c] = yref[i];
//		result[2, c] = xcom[(int)matches[i]];
//		result[3, c] = ycom[(int)matches[i]];
//	}
//
//	//res = [xrefnew(:) yrefnew(:) xcomnew(:) ycomnew(:)];
//
//	return result;
//}

