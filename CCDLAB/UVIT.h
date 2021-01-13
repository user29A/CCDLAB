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

#pragma once
using namespace System;
using namespace System::ComponentModel;
#include "String.h"
#include "omp.h"
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace JPFITS;


public ref class UVIT
{
public:
	UVIT(array<String^>^ FullFileList);
	//this is preliminary intialization of class...will decide what variables to initialize on class init later

	~UVIT(void);

	property int Number_of_Files
	{
		int get()	{return NUM_FILES;}
	}

	property int Current_File_Number//ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		int get() {return CURRENT_FILE;}
		void set(int file_number)
		{
			if (file_number > NUM_FILES)
			{
				CURRENT_FILE = 1;				//ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if (file_number < 1)
			{
				CURRENT_FILE = NUM_FILES;		//ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else
			{
				CURRENT_FILE = file_number;		//ONE Based!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}

	property int Min_Thresh
	{
		int get()	{return MIN_PIXEL;}
		void set(int min)	{MIN_PIXEL = min;}
	}

	property int Max_Thresh
	{
		int get()	{return MAX_PIXEL;}
		void set(int max)	{MAX_PIXEL = max;}
	}

	property int Min_Energy
	{
		int get()	{return MIN_SHAPE;}
		void set(int min)	{MIN_SHAPE = min;}
	}

	property int Max_Energy
	{
		int get()	{return MAX_SHAPE;}
		void set(int max)	{MAX_SHAPE = max;}
	}

	property int Precision
	{
		int get()	{return CENTROID_PRECISION;}
		void set(int precision)	
		{
			if (precision > 64)
			{
				precision = 64;
			}
			else if (precision < 0)
			{
				precision = 0;
			}
			CENTROID_PRECISION = precision;
		}
	}

	property array<String^>^ Full_File_List
	{
		array<String^>^ get() {return FULL_FILE_LIST;}
	}

	property array<String^>^ File_List
	{
		array<String^>^ get() {return FILE_LIST;}
	}

	property array<double,2>^ TBTC_Centroids
	{
		array<double,2>^ get() {return TBTC_CENTROIDS;}
	}

	property array<double,2>^ TBTQ_Centroids
	{
		array<double,2>^ get() {return TBTQ_CENTROIDS;}
	}

	property array<double,2>^ TBTS_Centroids
	{
		array<double,2>^ get() {return TBTS_CENTROIDS;}
	}

	property array<double,2>^ FBFC_Centroids
	{
		array<double,2>^ get() {return FBFC_CENTROIDS;}
	}

	property array<double,2>^ FBFS_Centroids
	{
		array<double,2>^ get() {return FBFS_CENTROIDS;}
	}

	property array<unsigned __int32,2>^ TBTC_Image//see below
	{
		array<unsigned __int32,2>^ get() {return TBTC_IMAGE;}
	}

	property array<unsigned __int32,2>^ TBTS_Image//see below
	{
		array<unsigned __int32,2>^ get() {return TBTS_IMAGE;}
	}

	property array<unsigned __int32,2>^ TBTQ_Image//see below
	{
		array<unsigned __int32,2>^ get() {return TBTQ_IMAGE;}
	}

	property array<unsigned __int32,2>^ FBFC_Image//see below
	{
		array<unsigned __int32,2>^ get() {return FBFC_IMAGE;}
	}

	property array<unsigned __int32,2>^ FBFS_Image//see below
	{
		array<unsigned __int32,2>^ get() {return FBFS_IMAGE;}
	}

	property array<int>^ Range
	{
		array<int>^ get() {return RANGE;}
		void set(array<int>^ Range) {RANGE = Range;}
	}

	property array<bool,1>^ AlgorithmTypes//see below
	{
		array<bool,1>^ get() {return ALGTYPES;}
	}

//	static array<double,2>^ Read_Raw_File(String^ FullFile);//this is for external interface to JPFITSImage file loading in CCDLAB.cpp
//	static array<double,2>^ Read_Raw_File(String^ FullFile, array<int,2>^ Range);//this is for external interface to JPFITSImage file loading in CCDLAB.cpp
//	static void Write_Raw_File(String^ FullFilePath,  array<double,2>^ image);//this is for external interface to JPFITSImage file loading in CCDLAB.cpp

//	array<double,2>^ Read_Raw_File(int filenum);//this is for internal centroiding stuff
//	array<double,2>^ Read_Raw_File(int filenum, array<int,2>^ Range, bool raster/*to separate overload from below*/);//this is for internal centroiding stuff

	array<double,2>^ Read_Raw_File(int filenum, int BackGround);//this is for internal centroiding stuff and subtracting a scalar background
	array<double,2>^ Read_Raw_File(int filenum, int BackGround, array<int,2>^ Range);//this is for internal centroiding stuff and subtracting a scalar background

	array<double,2>^ Read_Raw_File(int filenum, array<int,2>^ ArrayBackGround);//this is for internal centroiding stuff and subtracting an array background
	array<double,2>^ Read_Raw_File(int filenum, array<int,2>^ ArrayBackGround, array<int,2>^ Range);//this is for internal centroiding stuff and subtracting an array background

	bool Centroid(int Precision, array<int>^ Range, int MinPixel, int MaxPixel, int MinShape, int MaxShape,
		int ScalarBackGround, array<bool,1>^ AlgTypes, array<unsigned __int16,2>^ ArrayBackGround, BackgroundWorker^ worker,
		bool imageonly, bool ActiveBG, int  CornerThresh, double BGOffset, JPWaitBar::WaitBar^ wb);
	void Save_Centroids(String^ FullPathName, String^ Type, String^ arraybgname, bool activeBG);
	array<unsigned __int32,2>^ Get_Image(String^ Type);
	array<unsigned __int32,2>^ Get_FromOnlyImageMode(String^ Type);
	array<String^>^ Open_CentroidFile(String^ FullPathName);

private://keep an eye on params in right places as they can be parameters for Centroid(...) etc...

	int BG;						//scalar background to subtract from algorithms
	int MIN_PIXEL;				//minimum threshold of single pixel for centroiding candidate
	int MAX_PIXEL;				//maximum threshold of single pixel for centroiding candidate	
	int MIN_SHAPE;				//minimum threshold of total pixel signal within algorithm shape for central pixel centroiding candidate	
	int MAX_SHAPE;				//maximum threshold of total pixel signal within algorithm shape for central pixel centroiding candidate	
	int CENTROID_PRECISION;		//1 = pixel, 2 = 1/2 pixel (i.e.,2x2 = 1 pixel), 3 = 1/3 pixel, etc
	array<int>^ RANGE;		//this is the ZERO BASED centroiding range on the raw 512x512 image
								//RANGE[0,0] = xstart, RANGE[1,0] = xend, RANGE[0,1] = ystart, RANGE[1,1] = yend,
	array<String^,1>^ FULL_FILE_LIST;		//list of full path/file names of files
	array<String^,1>^ FILE_LIST;			//list of only file names of files
	int NUM_FILES;
	int CURRENT_FILE;

	array<bool,1>^ ALGTYPES;

	//FITSImage^ fits;

	//Will need to use array collections when building centroid arrays, then convert them to these regular arrays
	array<double,2>^ TBTC_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. TBTC = three by three cross.
	array<double,2>^ TBTQ_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. TBTQ = three by three quadratic - now Gaussian
	array<double,2>^ TBTS_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. TBTS = three by three square.
	array<double,2>^ FBFC_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. FBFC = five by five cross.
	array<double,2>^ FBFS_CENTROIDS;//dim(:,0) = x, dim(:,1) = y, dim(:,2) = Centroid Energy, dim(:,3) = Total Shape Energy. FBFS = five by five square.

	//the following are the built-up images of the centroid events, will be 512x512 * CENTROID_PREICISION^2 in size
	// i.e., CENTROID_PRECISION = 8 gives 4096x4096 image
	//Return functions?
	array<unsigned __int32,2>^ TBTC_IMAGE;	//type = 0
	array<unsigned __int32,2>^ TBTS_IMAGE;	//type = 1
	array<unsigned __int32,2>^ TBTQ_IMAGE;	//type = 2
	array<unsigned __int32,2>^ FBFC_IMAGE;	//type = 3
	array<unsigned __int32,2>^ FBFS_IMAGE;	//type = 4
	void InitImages(array<bool>^ types);
};


