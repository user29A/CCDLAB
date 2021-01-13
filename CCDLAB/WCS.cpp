#include "stdafx.h"
#include "WCS.h"

WCS::WCS()
{
}

void WCS::SOLVE_WCS(String^ WCS_Type, array<double>^ X_pix, array<double>^ Y_pix, bool zero_based_pixels, array<double>^ RA_deg, array<double>^ Dec_deg, FitsFile^ FITS)
{
	//should first do a check of WCS type to make sure it is valid
	CTYPE1 = "RA---" + WCS_Type;
	CTYPE2 = "DEC--" + WCS_Type;

	WCP1 = gcnew array<double>(X_pix->Length);
	WCP2 = gcnew array<double>(X_pix->Length);
	WCV1 = gcnew array<double>(X_pix->Length);
	WCV2 = gcnew array<double>(X_pix->Length);
	for (int i = 0; i < X_pix->Length; i++)
	{
		WCP1[i] = X_pix[i];
		WCP2[i] = Y_pix[i];
		if (zero_based_pixels)
		{
			WCP1[i]++;
			WCP2[i]++;
		}
		WCV1[i] = RA_deg[i];
		WCV2[i] = Dec_deg[i];
	}
	CRPIX1 = JPMath::Mean(WCP1);//fix this in the fit boundaries? - NO...let it get the best one...but they should be close
	CRPIX2 = JPMath::Mean(WCP2);//fix this in the fit boundaries? - NO...let it get the best one...but they should be close
	CRVAL1 = JPMath::Mean(WCV1);//these are fixed as the coordinate reference value
	CRVAL2 = JPMath::Mean(WCV2);//these are fixed as the coordinate reference value

	array<double>^ X_intrmdt = gcnew array<double>(WCP1->Length);//intermediate coords (degrees)
	array<double>^ Y_intrmdt = gcnew array<double>(WCP1->Length);//intermediate coords (degrees)
	double a0 = CRVAL1 * Math::PI / 180, d0 = CRVAL2 * Math::PI / 180, a, d;
	for (int i = 0; i < RA_deg->Length; i++)
	{
		a = WCV1[i] * Math::PI / 180;//radians
		d = WCV2[i] * Math::PI / 180;//radians

		//for tangent plane Gnomic
		if (WCS_Type == "TAN")
		{
			X_intrmdt[i] = Math::Cos(d)*Math::Sin(a - a0) / (Math::Cos(d0)*Math::Cos(d)*Math::Cos(a - a0) + Math::Sin(d0)*Math::Sin(d));
			Y_intrmdt[i] = (Math::Cos(d0)*Math::Sin(d) - Math::Cos(d)*Math::Sin(d0)*Math::Cos(a - a0)) / (Math::Sin(d0)*Math::Sin(d) + Math::Cos(d0)*Math::Cos(d)*Math::Cos(a - a0));
		}
	}	

	array<double>^ P0 = gcnew array<double>(6) { 0, 0, 0, 0, CRPIX1, CRPIX2 };
	array<double>^ plb = gcnew array<double>(6) { -0.1, -0.1, -0.1, -0.1, JPMath::Min(WCP1), JPMath::Min(WCP2) };
	array<double>^ pub = gcnew array<double>(6) { 0.1, 0.1, 0.1, 0.1, JPMath::Max(WCP1), JPMath::Max(WCP2) };
	JPMath::Fit_Transform2d(X_intrmdt, Y_intrmdt, WCP1, WCP2, P0, plb, pub);

	CDMATRIX = gcnew array<double, 2>(2, 2);
	CDMATRIX[0, 0] = P0[0] * 180 / Math::PI;
	CDMATRIX[1, 0] = P0[1] * 180 / Math::PI;
	CDMATRIX[0, 1] = P0[2] * 180 / Math::PI;
	CDMATRIX[1, 1] = P0[3] * 180 / Math::PI;
	CRPIX1 = P0[4];
	CRPIX2 = P0[5];
	CD1_1 = CDMATRIX[0, 0];
	CD1_2 = CDMATRIX[1, 0];
	CD2_1 = CDMATRIX[0, 1];
	CD2_2 = CDMATRIX[1, 1];
	WCSSCAL1 = Math::Sqrt(CD1_1 * CD1_1 + CD1_2 * CD1_2) * 3600;
	WCSSCAL2 = Math::Sqrt(CD2_1 * CD2_1 + CD2_2 * CD2_2) * 3600;
	WCSROT1 = Math::Atan2(CD1_2, -CD1_1) * 180 / Math::PI;
	WCSROT2 = Math::Atan2(-CD2_1, -CD2_2) * 180 / Math::PI;

	double det = 1 / ((CDMATRIX[0, 0] * CDMATRIX[1, 1] - CDMATRIX[1, 0] * CDMATRIX[0, 1])  * Math::PI / 180);
	CDMATRIXINV = gcnew array<double, 2>(2, 2);
	CDMATRIXINV[0, 0] = det * CDMATRIX[1, 1];
	CDMATRIXINV[1, 0] = -det * CDMATRIX[1, 0];
	CDMATRIXINV[0, 1] = -det * CDMATRIX[0, 1];
	CDMATRIXINV[1, 1] = det * CDMATRIX[0, 0];

	array<double>^ dxpix = gcnew array<double>(WCP1->Length);
	array<double>^ dypix = gcnew array<double>(WCP2->Length);
	double xpix, ypix;
	for (int i = 0; i < WCP1->Length; i++)
	{
		GETPIX(WCV1[i], WCV2[i], "TAN", xpix, ypix, false);
		dxpix[i] = xpix - WCP1[i];
		dypix[i] = ypix - WCP2[i];
	}

	MEANRPX1 = JPMath::Mean(dxpix);
	STDRPX1 = JPMath::Stdv(dxpix);
	MEANRAS1 = JPMath::Mean(dxpix) * WCSSCAL1;
	STDRAS1 = JPMath::Stdv(dxpix) * WCSSCAL1;
	MEANRPX2 = JPMath::Mean(dypix);
	STDRPX2 = JPMath::Stdv(dypix);
	MEANRAS2 = JPMath::Mean(dypix) * WCSSCAL2;
	STDRAS2 = JPMath::Stdv(dypix) * WCSSCAL2;

	if (FITS == nullptr)
		return;

	this->COPYWCS(FITS);
}

void WCS::GETPIX(double RA_deg, double Dec_deg, String^ WCS_Type, double &X_pix, double &Y_pix, bool return_zero_based_pixels)
{
	double a0 = CRVAL1 * Math::PI / 180, d0 = CRVAL2 * Math::PI / 180;
	double a = RA_deg * Math::PI / 180, d = Dec_deg * Math::PI / 180;//radians
	double X_intrmdt = Math::Cos(d)*Math::Sin(a - a0) / (Math::Cos(d0)*Math::Cos(d)*Math::Cos(a - a0) + Math::Sin(d0)*Math::Sin(d));
	double Y_intrmdt = (Math::Cos(d0)*Math::Sin(d) - Math::Cos(d)*Math::Sin(d0)*Math::Cos(a - a0)) / (Math::Sin(d0)*Math::Sin(d) + Math::Cos(d0)*Math::Cos(d)*Math::Cos(a - a0));
	X_pix = CDMATRIXINV[0, 0] * X_intrmdt + CDMATRIXINV[1, 0] * Y_intrmdt + CRPIX1;
	Y_pix = CDMATRIXINV[0, 1] * X_intrmdt + CDMATRIXINV[1, 1] * Y_intrmdt + CRPIX2;
	if (return_zero_based_pixels)
	{
		X_pix--;
		Y_pix--;
	}

	//linear
	//int xpix = int(WCS_CDMATRIX_INV[0, 0] * (RA - WCS_CRVAL1) + WCS_CDMATRIX_INV[1, 0] * (Dec - WCS_CRVAL2) + WCS_CRPIX1);
	//int ypix = int(WCS_CDMATRIX_INV[0, 1] * (RA - WCS_CRVAL1) + WCS_CDMATRIX_INV[1, 1] * (Dec - WCS_CRVAL2) + WCS_CRPIX2);
}

void WCS::GETPIXELS(array<double>^ RA_deg, array<double>^ Dec_deg, String^ WCS_Type, array<double>^ &X_pix, array<double>^ &Y_pix, bool return_zero_based_pixels)
{
	double xpix, ypix;
	for (int i = 0; i < RA_deg->Length; i++)
	{
		this->GETPIX(RA_deg[i], Dec_deg[i], WCS_Type, xpix, ypix, return_zero_based_pixels);
		X_pix[i] = xpix;
		Y_pix[i] = ypix;
	}
}

void WCS::GETCOORD(double X_pix, double Y_pix, bool zero_based_pixels, String^ WCS_Type, double &RA_deg, double &Dec_deg, String^ &RA_sxgsml, String^ &Dec_sxgsml)
{
	if (zero_based_pixels)
	{
		X_pix++;
		Y_pix++;
	}
	double X_intrmdt = CDMATRIX[0, 0] * (X_pix - CRPIX1) * Math::PI / 180 + CDMATRIX[1, 0] * (Y_pix - CRPIX2) * Math::PI / 180;
	double Y_intrmdt = CDMATRIX[0, 1] * (X_pix - CRPIX1) * Math::PI / 180 + CDMATRIX[1, 1] * (Y_pix - CRPIX2) * Math::PI / 180;
	double a = CRVAL1 * Math::PI / 180 + Math::Atan(X_intrmdt / (Math::Cos(CRVAL2*Math::PI / 180) - Y_intrmdt * Math::Sin(CRVAL2*Math::PI / 180)));
	double d = Math::Asin((Math::Sin(CRVAL2*Math::PI / 180) + Y_intrmdt * Math::Cos(CRVAL2*Math::PI / 180)) / Math::Sqrt(1 + X_intrmdt * X_intrmdt + Y_intrmdt * Y_intrmdt));
	//double d = Math::Atan((Math::Cos(a - WCS_CRVAL1 * Math::PI / 180) * (Y + Math::Tan(WCS_CRVAL2 * Math::PI / 180))) / (1 - Y / Math::Tan(WCS_CRVAL2 * Math::PI / 180)));
	a = a * 180 / Math::PI;
	d = d * 180 / Math::PI;

	//linear
	//double a = WCS_CDMATRIX[0, 0]*(XPOS_CURSOR - WCS_CRPIX1) + WCS_CDMATRIX[1, 0]*(YPOS_CURSOR - WCS_CRPIX2) + WCS_CRVAL1;
	//double d = WCS_CDMATRIX[0, 1]*(XPOS_CURSOR - WCS_CRPIX1) + WCS_CDMATRIX[1, 1]*(YPOS_CURSOR - WCS_CRPIX2) + WCS_CRVAL2;

	if (a < 0)
		a += 360;

	RA_deg = a;
	Dec_deg = d;

	double h = Math::Floor(a / 360 * 24);
	double m = Math::Floor((a / 360 * 24 - h) * 60);
	double s = Math::Round((a / 360 * 24 - h - m / 60) * 3600, 2);

	double decdeg = Math::Abs(d);
	double deg = Math::Floor(decdeg);
	double am = Math::Floor((decdeg - deg) * 60);
	double as = Math::Round((decdeg - deg - am / 60) * 3600, 2);

	String^ sign = "+";
	if (d < 0)
		sign = "-";

	RA_sxgsml = h + "h " + m + "m " + s + "s";
	Dec_sxgsml = sign + deg + "d " + am + "' " + as + "''";
}

void WCS::GETCOORDINATES(array<double>^ X_pix, array<double>^ Y_pix, bool zero_based_pixels, String^ WCS_Type, array<double>^ &RA_deg, array<double>^ &Dec_deg, array<String^>^ &RA_sxgsml, array<String^>^ &Dec_sxgsml)
{
	double radeg, decdeg;
	String^ rasx;
	String^ decsx;
	for (int i = 0; i < RA_deg->Length; i++)
	{
		this->GETCOORD(X_pix[i], Y_pix[i], zero_based_pixels, WCS_Type, radeg, decdeg, rasx, decsx);
		RA_deg[i] = radeg;
		Dec_deg[i] = decdeg;
		RA_sxgsml[i] = rasx;
		Dec_sxgsml[i] = decsx;
	}
}

void WCS::GETWCS(FitsFile^ FITS)
{
	if (FITS->GetKeyValue("CD1_1") == "")
		throw gcnew Exception("Error: CD matrix not found...");

	CDMATRIX = gcnew array<double, 2>(2, 2);
	CDMATRIXINV = gcnew array<double, 2>(2, 2);

	CTYPE1 = FITS->GetKeyValue("CTYPE1");
	CTYPE2 = FITS->GetKeyValue("CTYPE2");
	CRPIX1 = Convert::ToDouble(FITS->GetKeyValue("CRPIX1"));
	CRPIX2 = Convert::ToDouble(FITS->GetKeyValue("CRPIX2"));
	CRVAL1 = Convert::ToDouble(FITS->GetKeyValue("CRVAL1"));
	CRVAL2 = Convert::ToDouble(FITS->GetKeyValue("CRVAL2"));

	CDMATRIX[0, 0] = Convert::ToDouble(FITS->GetKeyValue("CD1_1"));
	CDMATRIX[1, 0] = Convert::ToDouble(FITS->GetKeyValue("CD1_2"));
	CDMATRIX[0, 1] = Convert::ToDouble(FITS->GetKeyValue("CD2_1"));
	CDMATRIX[1, 1] = Convert::ToDouble(FITS->GetKeyValue("CD2_2"));

	CD1_1 = CDMATRIX[0, 0];
	CD1_2 = CDMATRIX[1, 0];
	CD2_1 = CDMATRIX[0, 1];
	CD2_2 = CDMATRIX[1, 1];

	WCSSCAL1 = Math::Sqrt(CD1_1 * CD1_1 + CD1_2 * CD1_2) * 3600;
	WCSSCAL2 = Math::Sqrt(CD2_1 * CD2_1 + CD2_2 * CD2_2) * 3600;
	WCSROT1 = Math::Atan2(CD1_2, -CD1_1) * 180 / Math::PI;
	WCSROT2 = Math::Atan2(-CD2_1, -CD2_2) * 180 / Math::PI;

	double det = 1 / ((CDMATRIX[0, 0] * CDMATRIX[1, 1] - CDMATRIX[1, 0] * CDMATRIX[0, 1])  * Math::PI / 180);
	CDMATRIXINV[0, 0] = det * CDMATRIX[1, 1];
	CDMATRIXINV[1, 0] = -det * CDMATRIX[1, 0];
	CDMATRIXINV[0, 1] = -det * CDMATRIX[0, 1];
	CDMATRIXINV[1, 1] = det * CDMATRIX[0, 0];

	try
	{
		WCSSCAL1 = Convert::ToDouble(FITS->GetKeyValue("WCSSCAL1"));
		WCSSCAL2 = Convert::ToDouble(FITS->GetKeyValue("WCSSCAL2"));
		WCSROT1 = Convert::ToDouble(FITS->GetKeyValue("WCSROT1"));
		WCSROT2 = Convert::ToDouble(FITS->GetKeyValue("WCSROT2"));
		MEANRPX1 = Convert::ToDouble(FITS->GetKeyValue("MEANRPX1"));
		STDRPX1 = Convert::ToDouble(FITS->GetKeyValue("STDRPX1"));
		MEANRAS1 = Convert::ToDouble(FITS->GetKeyValue("MEANRAS1"));
		STDRAS1 = Convert::ToDouble(FITS->GetKeyValue("STDRAS1"));
		MEANRPX2 = Convert::ToDouble(FITS->GetKeyValue("MEANRPX2"));
		STDRPX2 = Convert::ToDouble(FITS->GetKeyValue("STDRPX2"));
		MEANRAS2 = Convert::ToDouble(FITS->GetKeyValue("MEANRAS2"));
		STDRAS2 = Convert::ToDouble(FITS->GetKeyValue("STDRAS2"));

		int num = 0, key = 0;
		while (key != -1)
		{
			num++;
			key = FITS->GetKeyIndex("WCP1_" + num.ToString("000"));
		}
		num--;
		WCP1 = gcnew array<double>(num);
		WCP2 = gcnew array<double>(num);
		WCV1 = gcnew array<double>(num);
		WCV2 = gcnew array<double>(num);
		num = 1;
		for (int i = 0; i < WCP1->Length; i++)
		{
			WCP1[i] = Convert::ToDouble(FITS->GetKeyValue("WCP1_" + num.ToString("000")));
			WCP2[i] = Convert::ToDouble(FITS->GetKeyValue("WCP2_" + num.ToString("000")));
			WCV1[i] = Convert::ToDouble(FITS->GetKeyValue("WCV1_" + num.ToString("000")));
			WCV2[i] = Convert::ToDouble(FITS->GetKeyValue("WCV2_" + num.ToString("000")));
			num++;
		}
	}
	catch ( ... /*Exception^ e*/) 
	{
		//MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}
}

void WCS::GETWCS(String^ FITS_filename)
{
	FitsFile^ FITS = gcnew FitsFile(FITS_filename, nullptr, true, false, false);
	this->GETWCS(FITS);
}

void WCS::COPYWCS(FitsFile^ FITS)
{
	FITS->SetKey("CTYPE1", CTYPE1, "WCS type of horizontal coordinate transformation", true, -1);
	FITS->SetKey("CTYPE2", CTYPE2, "WCS type of vertical coordinate transformation", true, -1);
	FITS->SetKey("CRPIX1", CRPIX1.ToString("F5"), "WCS coordinate reference pixel on axis 1", true, -1);
	FITS->SetKey("CRPIX2", CRPIX2.ToString("F5"), "WCS coordinate reference pixel on axis 2", true, -1);
	FITS->SetKey("CRVAL1", CRVAL1.ToString("F8"), "WCS coordinate reference value on axis 1 (deg)", true, -1);
	FITS->SetKey("CRVAL2", CRVAL2.ToString("F8"), "WCS coordinate reference value on axis 2 (deg)", true, -1);
	FITS->SetKey("CD1_1", CDMATRIX[0, 0].ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);
	FITS->SetKey("CD1_2", CDMATRIX[1, 0].ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);
	FITS->SetKey("CD2_1", CDMATRIX[0, 1].ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);
	FITS->SetKey("CD2_2", CDMATRIX[1, 1].ToString("0.0#######e+00"), "WCS rotation and scaling matrix", true, -1);

	try
	{
		FITS->SetKey("WCSSCAL1", WCSSCAL1.ToString("F8"), "WCS plate scale on axis 1 (arcsec per pixel)", true, -1);
		FITS->SetKey("WCSSCAL2", WCSSCAL2.ToString("F8"), "WCS plate Scale on axis 2 (arcsec per pixel)", true, -1);
		FITS->SetKey("WCSROT1", WCSROT1.ToString("F8"), "WCS field rotation angle on axis 1 (degrees)", true, -1);
		FITS->SetKey("WCSROT2", WCSROT2.ToString("F8"), "WCS field rotation angle on axis 2 (degrees)", true, -1);
		FITS->SetKey("MEANRPX1", MEANRPX1.ToString("G"), "Mean of WCS residuals on axis 1 (pixels)", true, -1);
		FITS->SetKey("STDRPX1", STDRPX1.ToString("G"), "Standard dev of WCS residuals on axis 1 (pixels)", true, -1);
		FITS->SetKey("MEANRAS1", MEANRAS1.ToString("G"), "Mean of WCS residuals on axis 1 (arcsec)", true, -1);
		FITS->SetKey("STDRAS1", STDRAS1.ToString("G"), "Standard dev of WCS residuals on axis 1 (arcsec)", true, -1);
		FITS->SetKey("MEANRPX2", MEANRPX2.ToString("G"), "Mean of WCS residuals on axis 2 (pixels)", true, -1);
		FITS->SetKey("STDRPX2", STDRPX2.ToString("G"), "Standard dev of WCS residuals on axis 2 (pixels)", true, -1);
		FITS->SetKey("MEANRAS2", MEANRAS2.ToString("G"), "Mean of WCS residuals on axis 2 (arcsec)", true, -1);
		FITS->SetKey("STDRAS2", STDRAS2.ToString("G"), "Standard dev of WCS residuals on axis 2 (arcsec)", true, -1);

		int key = 0, num = 1;
		while (key != -1)
		{
			key = FITS->GetKeyIndex("WCP1_" + num.ToString("000"));
			FITS->RemoveKey(key);
			key = FITS->GetKeyIndex("WCP2_" + num.ToString("000"));
			FITS->RemoveKey(key);
			key = FITS->GetKeyIndex("WCV1_" + num.ToString("000"));
			FITS->RemoveKey(key);
			key = FITS->GetKeyIndex("WCV2_" + num.ToString("000"));
			FITS->RemoveKey(key);
			num++;
		}

		num = 1;
		for (int i = 0; i < WCP1->Length; i++)
		{
			FITS->SetKey("WCP1_" + num.ToString("000"), WCP1[i].ToString("F5"), "WCS coordinate pixel on axis 1", true, -1);
			FITS->SetKey("WCP2_" + num.ToString("000"), WCP2[i].ToString("F5"), "WCS coordinate pixel on axis 2", true, -1);
			FITS->SetKey("WCV1_" + num.ToString("000"), WCV1[i].ToString("F8"), "WCS coordinate value on axis 1 (degrees)", true, -1);
			FITS->SetKey("WCV2_" + num.ToString("000"), WCV2[i].ToString("F8"), "WCS coordinate value on axis 2 (degrees)", true, -1);
			num++;
		}
	}
	catch (Exception^ e) 
	{
		MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
	}
}

