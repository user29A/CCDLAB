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


#pragma once

#include "String.h"
#include "omp.h"
#include "WCS.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace MathWorks::MATLAB::NET::Arrays;
using namespace MathWorks::MATLAB::NET::Utility;
using namespace System::Windows::Forms;


public ref class PSE
{
public:
	PSE(void);
	~PSE(void);
	
	void Extract(array<double,2>^ image, double pix_min, double pix_max, double kernel_min, double kernel_max, bool threshholds_as_SN, int kernel_pixwidth, bool auto_background, bool save_sourcekernels, String^ kernel_filename_template, bool elliptical_roi, double roi_x, double roi_x_radius, double roi_y, double roi_y_radius);
	
	void Extract(array<double, 2>^ image, array<double>^ XCoords, array<double>^ YCoords, int kernel_pixwidth, bool auto_background, bool save_sourcekernels, String^ kernel_filename_template);
	
	void Gauss_Symmetric(array<double,1>^ P0, bool view);//2-D Symmetric Gaussian
	void Gauss_Rotated(array<double,1>^ P0, bool view);// 2-D Rotated Gaussian
	void Moffat_Symmetric(array<double,1>^ P0, bool view);// 2-D Symmetric Moffat
	void Moffat_Rotated(array<double,1>^ P0, bool view);// 2-D Rotated Moffat

	void SavePointParameters();

	void GenerateRADecCoords(WCS^ wcs);

	void GeneratePSETable();

	//array<double,2>^ MatchPoints(array<double>^ xref, array<double>^ yref, array<double>^ xcom, array<double>^ ycom);


public:
	int N_SRC;								// number of sources found
	int KERNEL_PIXWIDTH;					// source widths for centroiding
	double PIX_MIN;							// source min pixel thresh
	double PIX_MAX;							// source max pixel thresh
	double KERNEL_MIN;						// total source min count thresh
	double KERNEL_MAX;						// total source max count thresh
	bool AUTO_BG;							//automatic background determination (corner min method)
	bool SAVE_PS;
	bool THRESHHOLDS_AS_SN;					//interpret pixel value and total count thresholds as SN
	bool ROI_IS_ELLIPTICAL;
	double ROI_X, ROI_Y, ROI_XRAD, ROI_YRAD;
	String^ SAVE_PS_FILENAME;
	array<double, 2>^ IMAGE;
	
	array<double>^ CENTROIDS_X;				// x centroid positions of sources
	array<double>^ CENTROIDS_Y;				// y centroid positions of sources
	array<double>^ CENTROIDS_RADEG;			// right ascension centroid positions of sources - if available
	array<String^>^ CENTROIDS_RAHMS;		// right ascension centroid positions of sources - if available
	array<double>^ CENTROIDS_DECDEG;		// declination centroid positions of sources - if available
	array<String^>^ CENTROIDS_DECDMS;		// declination centroid positions of sources - if available
	array<double>^ CENTROIDS_AMPLITUDE;		// sources values (above fcmin)
	array<double>^ CENTROIDS_VOLUME;		// sources energies (above fcmin)
	array<double>^ CENTROIDS_BGESTIMATE;	// corner minimum - estimate of background

	array<double>^ FITS_X;					// x fitted positions of sources
	array<double>^ FITS_Y;					// y fitted positions of sources
	array<double>^ FITS_FWHM_X;				// FWHM of sources
	array<double>^ FITS_FWHM_Y;				// FWHM of sources
	array<double>^ FITS_PHI;				// rotation theta of rotated fits
	array<double>^ FITS_RADEG;				// right ascension centroid positions of sources - if available
	array<String^>^ FITS_RAHMS;				// right ascension centroid positions of sources - if available
	array<double>^ FITS_DECDEG;				// declination centroid positions of sources - if available
	array<String^>^ FITS_DECDMS;			// declination centroid positions of sources - if available
	array<double,2>^ FITS_PARAMS;			// fitted paramaters of sources - 2d because multiple parameters per source
	array<double>^ FITS_AMPLITUDE;			// 
	array<double>^ FITS_VOLUME;				// 
	array<double>^ FITS_BGESTIMATE;			// 
	array<double>^ FITS_CHISQNORM;			// 

	array<String^, 2>^ PSE_TABLE;

private:
	bool FITTED = false;
	String^ FIT_EQUATION;
	bool WCS_GENERATED = false;
	bool VIEWFITS = false;
	array<double>^ P_INIT;

	static JPWaitBar::WaitBar^ WAITBAR;
	static BackgroundWorker^ BGWRKR;
	static Object^ BGWRKR_RESULT;
	void BGWRKR_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
	void BGWRKR_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
	void BGWRKR_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);

};
