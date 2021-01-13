#pragma once

#include "String.h"
#include "omp.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace JPFits;

public ref class WCS
{
public:

	/// <summary>Instantiates an instance of the WCS class.</summary>
	WCS();

	/// <summary>Solves the tangent-plane or Gnomic projection parameters for a given list of pixel & coordinate values. Pass nullptr for FITS if writing WCS parameters to header not required.</summary>
	void SOLVE_WCS(String^ WCS_Type, array<double>^ X_pix, array<double>^ Y_pix, bool zero_based_pixels, array<double>^ RA_deg, array<double>^ Dec_deg, FitsFile^ FITS);

	/// <summary>Gets the [x, y] pixel position for a given RA & Dec.</summary>
	void GETPIX(double RA_deg, double Dec_deg, String^ WCS_Type, double &X_pix, double &Y_pix, bool return_zero_based_pixels);

	/// <summary>Gets arrays of [x, y] pixel positions for a list of given RA's & Dec's.</summary>
	void GETPIXELS(array<double>^ RA_deg, array<double>^ Dec_deg, String^ WCS_Type, array<double>^ &X_pix, array<double>^ &Y_pix, bool return_zero_based_pixels);

	/// <summary>Gets the RA & Dec coordinate for a given [x, y] pixel position.</summary>
	void GETCOORD(double X_pix, double Y_pix, bool zero_based_pixels, String^ WCS_Type, double &RA_deg, double &Dec_deg, String^ &RA_sxgsml, String^ &Dec_sxgsml);
	
	/// <summary>Gets arrays of RA & Dec coordinates for a list of given [x, y] pixel positions.</summary>
	void GETCOORDINATES(array<double>^ X_pix, array<double>^ Y_pix, bool zero_based_pixels, String^ WCS_Type, array<double>^ &RA_deg, array<double>^ &Dec_deg, array<String^>^ &RA_sxgsml, array<String^>^ &Dec_sxgsml);

	/// <summary>Gets the WCS parameters from the given FITS file primary header, and sets them for this WCS class instance.</summary>
	void GETWCS(FitsFile^ FITS);

	/// <summary>Gets the WCS parameters from the FITS file primary header of the given filename, and sets them for this WCS class instance.</summary>
	void GETWCS(String^ FITS_filename);

	/// <summary>Copies the existing WCS parameters in the current WCS class instance to the given FITS file primary header overwriting any existing values.</summary>
	void COPYWCS(FitsFile^ FITS);

public:
	array<double, 2>^ CDMATRIX;
	array<double, 2>^ CDMATRIXINV;
	array<double>^ WCV1;
	array<double>^ WCV2;
	array<double>^ WCP1;
	array<double>^ WCP2;
	double CRVAL1, CRVAL2, CRPIX1, CRPIX2, WCSSCAL1, WCSSCAL2, WCSROT1, WCSROT2, CD1_1, CD1_2, CD2_1, CD2_2, MEANRPX1, STDRPX1, MEANRAS1, STDRAS1, MEANRPX2, STDRPX2, MEANRAS2, STDRAS2;
	String^ CTYPE1;
	String^ CTYPE2;
};

