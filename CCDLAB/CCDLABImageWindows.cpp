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


void Form1::SubImageWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
{
	if (FIRSTLOAD)
		return;

	if (PSEEllipticalROI->Checked)
		return;

	e->Graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	e->Graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	e->Graphics->DrawImage(SUBIMAGEBMP,Rectangle(0, 0, SubImageWindow->Size.Width, SubImageWindow->Size.Height));

	float subxsc = (float(SubImageWindow->Size.Width)/(float)XSUBRANGE->Length);
	float subysc = (float(SubImageWindow->Size.Height)/(float)YSUBRANGE->Length);

	if (ShowFoundCoordsChck->Checked)
	{
		IMAGEWINDOWPEN->Color = Color::Red;
		for (int i = 0; i < FNDCOORDS->GetLength(0); i++)
			if (FNDCOORDS[i,0] >= XSUBRANGE[0] && FNDCOORDS[i,0] <= XSUBRANGE[XSUBRANGE->Length-1] && FNDCOORDS[i,1] >= YSUBRANGE[0] && FNDCOORDS[i,1] <= YSUBRANGE[YSUBRANGE->Length-1])
				e->Graphics->FillRectangle(IMAGEWINDOWPEN->Brush,(float)((float(FNDCOORDS[i,0])-float(XSUBRANGE[0])+0.5)*subxsc-3.0),(float)((float(FNDCOORDS[i,1])-float(YSUBRANGE[0])+0.5)*subysc-3.0),7.0,7.0);
	}

	if (ShowPSEChck->Checked && PSESRECTS != nullptr && PSES[PSESINDEX] != nullptr)
	{
		IMAGEWINDOWPEN->Width = 2;
		int rem = 0;

		if (!PSESPLOTALL)
		{
			Math::DivRem(PSESINDEX, PSERECTCOLOURS->Length, rem);
			IMAGEWINDOWPEN->Color = PSERECTCOLOURS[rem];
			for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
				if (PSES[PSESINDEX]->Centroids_X[i] + 1 >= XSUBRANGE[0] && PSES[PSESINDEX]->Centroids_X[i] - 1 <= XSUBRANGE[XSUBRANGE->Length - 1] && PSES[PSESINDEX]->Centroids_Y[i] + 1 >= YSUBRANGE[0] && PSES[PSESINDEX]->Centroids_Y[i] - 1 <= YSUBRANGE[YSUBRANGE->Length - 1])
					e->Graphics->DrawRectangle(IMAGEWINDOWPEN, (float)((float(PSES[PSESINDEX]->Centroids_X[i]) - float(XSUBRANGE[0]) + 0.5)*subxsc - 3.0), (float)((float(PSES[PSESINDEX]->Centroids_Y[i]) - float(YSUBRANGE[0]) + 0.5)*subysc - 3.0), 7.0, 7.0);
		}
		else
		{
			for (int k = 0; k < PSES->Length; k++)
			{
				Math::DivRem(k, PSERECTCOLOURS->Length, rem);
				IMAGEWINDOWPEN->Color = PSERECTCOLOURS[rem];
				for (int i = 0; i < PSES[k]->N_Sources; i++)
					if (PSES[k]->Centroids_X[i] + 1 >= XSUBRANGE[0] && PSES[k]->Centroids_X[i] - 1 <= XSUBRANGE[XSUBRANGE->Length - 1] && PSES[k]->Centroids_Y[i] + 1 >= YSUBRANGE[0] && PSES[k]->Centroids_Y[i] - 1 <= YSUBRANGE[YSUBRANGE->Length - 1])
						e->Graphics->DrawRectangle(IMAGEWINDOWPEN, (float)((float(PSES[k]->Centroids_X[i]) - float(XSUBRANGE[0]) + 0.5)*subxsc - 3.0), (float)((float(PSES[k]->Centroids_Y[i]) - float(YSUBRANGE[0]) + 0.5)*subysc - 3.0), 7.0, 7.0);
			}
		}

		IMAGEWINDOWPEN->Width = 1;

		/*IMAGEWINDOWPEN->Color = Color::Cyan;
		for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
			if (PSES[PSESINDEX]->Centroids_X[i] + 1 >= XSUBRANGE[0] && PSES[PSESINDEX]->Centroids_X[i] - 1 <= XSUBRANGE[XSUBRANGE->Length - 1] && PSES[PSESINDEX]->Centroids_Y[i] + 1 >= YSUBRANGE[0] && PSES[PSESINDEX]->Centroids_Y[i] - 1 <= YSUBRANGE[YSUBRANGE->Length - 1])
				e->Graphics->FillRectangle(IMAGEWINDOWPEN->Brush, (float)((float(PSES[PSESINDEX]->Centroids_X[i]) - float(XSUBRANGE[0]) + 0.5)*subxsc - 3.0), (float)((float(PSES[PSESINDEX]->Centroids_Y[i]) - float(YSUBRANGE[0]) + 0.5)*subysc - 3.0), 7.0, 7.0);*/
	}

	if (MARKCOORDS != nullptr && MARKCOORDRECTS != nullptr)
	{
		IMAGEWINDOWPEN->Color = Color::Violet;
		IMAGEWINDOWPEN->Width = 2;
		for (int i = 0; i < MARKCOORDRECTS->Length; i++)
			if (MARKCOORDS[0,i] >= XSUBRANGE[0] && MARKCOORDS[0,i] <= XSUBRANGE[XSUBRANGE->Length-1] && MARKCOORDS[1,i] >= YSUBRANGE[0] && MARKCOORDS[1,i] <= YSUBRANGE[YSUBRANGE->Length-1])
				e->Graphics->DrawEllipse(IMAGEWINDOWPEN,(float)((float(MARKCOORDS[0,i])-float(XSUBRANGE[0])+0.5)*subxsc-6.0),(float)((float(MARKCOORDS[1,i])-float(YSUBRANGE[0])+0.5)*subysc-6.0),13.0,13.0);
		IMAGEWINDOWPEN->Width = 1;
	}

	if (COG_CURSOR)
	{
		e->Graphics->DrawEllipse(IMAGEWINDOWPEN,0.0,0.0,float(SubImageWindow->Size.Width),float(SubImageWindow->Size.Height));
	}

	if (DOMANREG && MANREGCOORDRECTS->Length > 0 || UVREGISTRATION && MANREGCOORDRECTS->Length > 0 || WCSMANUALRAD && MANREGCOORDRECTS->Length > 0)
	{
		IMAGEWINDOWPEN->Color = Color::Chartreuse;
		if (UVREGISTRATION_TOUCHPOINT)
			IMAGEWINDOWPEN->Width = 3;
		else
			IMAGEWINDOWPEN->Width = 2;

		for (int i = 0; i < MANREGCOORDS->GetLength(0); i++)
			if (MANREGCOORDS[i, 0] >= XSUBRANGE[0] && MANREGCOORDS[i, 0] <= XSUBRANGE[XSUBRANGE->Length - 1] && MANREGCOORDS[i, 1] >= YSUBRANGE[0] && MANREGCOORDS[i, 1] <= YSUBRANGE[YSUBRANGE->Length - 1])
				e->Graphics->DrawRectangle(IMAGEWINDOWPEN, (float)((float(MANREGCOORDS[i, 0]) - float(XSUBRANGE[0]) + 0.5) * subxsc - 6.0), (float)((float(MANREGCOORDS[i, 1]) - float(YSUBRANGE[0]) + 0.5) * subysc - 6.0), 13.0, 13.0);
	}

	/*if (toolStripMenuItem1->Checked)
	{
		MWNumericArray^ x = gcnew MWNumericArray(1, XSUBRANGE->Length, XSUBRANGE);
		MWNumericArray^ y = gcnew MWNumericArray(1, YSUBRANGE->Length, YSUBRANGE);
		MWNumericArray^ z = gcnew MWNumericArray(SUBIMAGE);
		MLSURF->Surf_Facet(x, y, z);
	}*/
}

void Form1::ImageWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
{
	if (FIRSTLOAD || !ImageWindow->Visible)
		return;

	try//need to do this because when loading a new image there is nothing to define ->Width
	{
		e->Graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
		e->Graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
		e->Graphics->DrawImage(IMAGEBMP, Rectangle(0, 0, ImageWindow->Size.Width, ImageWindow->Size.Height));
			 
		float xsc = (float(ImageWindow->Size.Width)/(float)IMAGESET[FILELISTINDEX]->Width);
		float ysc = (float(ImageWindow->Size.Height)/(float)IMAGESET[FILELISTINDEX]->Height);

		if (ShowFoundCoordsChck->Checked)
		{
			IMAGEWINDOWPEN->Color = Color::Red;
			e->Graphics->DrawRectangles(IMAGEWINDOWPEN,FNDCOORDRECTS);
		}

		if (DOMANREG && MANREGCOORDRECTS->Length > 0 || UVREGISTRATION && MANREGCOORDRECTS->Length > 0 || WCSMANUALRAD && MANREGCOORDRECTS->Length > 0)
		{
			IMAGEWINDOWPEN->Color = Color::Chartreuse;
			if (UVREGISTRATION_TOUCHPOINT)
				IMAGEWINDOWPEN->Width = 3;
			else
				IMAGEWINDOWPEN->Width = 1;

			e->Graphics->DrawRectangles(IMAGEWINDOWPEN,MANREGCOORDRECTS);
		}

		if (ShowPSEChck->Checked && PSESRECTS != nullptr && PSES[PSESINDEX] != nullptr)
		{
			IMAGEWINDOWPEN->Width = 2;
			int rem = 0;

			if (!PSESPLOTALL)
			{
				Math::DivRem(PSESINDEX, PSERECTCOLOURS->Length, rem);
				IMAGEWINDOWPEN->Color = PSERECTCOLOURS[rem];
				e->Graphics->DrawRectangles(IMAGEWINDOWPEN, PSESRECTS[PSESINDEX]);
			}
			else
			{
				for (int i = 0; i < PSES->Length; i++)
				{
					Math::DivRem(i, PSERECTCOLOURS->Length, rem);
					IMAGEWINDOWPEN->Color = PSERECTCOLOURS[rem];
					e->Graphics->DrawRectangles(IMAGEWINDOWPEN, PSESRECTS[i]);
				}
				//PSESPLOTALL = false;
			}

			IMAGEWINDOWPEN->Width = 1;
		}

		if (MARKCOORDRECTS != nullptr)
		{
			IMAGEWINDOWPEN->Color = Color::Violet;
			IMAGEWINDOWPEN->Width = 2;
			for (int i = 0; i < MARKCOORDRECTS->Length; i++)
				e->Graphics->DrawEllipse(IMAGEWINDOWPEN,MARKCOORDRECTS[i]);

			IMAGEWINDOWPEN->Width = 1;
		}

		if (ShowCursorBox->Checked)
		{
			if (!IWLCK)//allow cursor box to move
				IMAGEWINDOWPEN->Color = Color::Yellow;
			else//else fixed
			{
				IMAGEWINDOWPEN->Color = Color::LimeGreen;
				IMAGEWINDOWPEN->Width = 2;
			}
			if (COG_CURSOR || PSEEllipticalROI->Checked)
				e->Graphics->DrawEllipse(IMAGEWINDOWPEN, float(XSUBRANGE[0])*xsc, float(YSUBRANGE[0])*ysc, float(SUBIMAGE_HWX * 2 + 1)*xsc, float(SUBIMAGE_HWY * 2 + 1)*ysc);
			else
				e->Graphics->DrawRectangle(IMAGEWINDOWPEN, float(XSUBRANGE[0])*xsc, float(YSUBRANGE[0])*ysc, float(SUBIMAGE_HWX * 2 + 1)*xsc, float(SUBIMAGE_HWY * 2 + 1)*ysc);
					
			IMAGEWINDOWPEN->Width = 1;//reset for other operations...only set = 2 for cursor box draw
		}

		if (ShowCrosshair->Checked)
		{
			IMAGEWINDOWPEN->Color = Color::Red;
			e->Graphics->DrawLine(IMAGEWINDOWPEN, (float(SubImageSlideX->Value - 1.f) + 0.5f)*xsc, 0.f, (float(SubImageSlideX->Value - 1.f) + 0.5f)*xsc, float(ImageWindow->Size.Height));//vertical
			e->Graphics->DrawLine(IMAGEWINDOWPEN, 0.f, (float(SubImageSlideY->Value - 1.f) + 0.5f)*ysc, float(ImageWindow->Size.Width), (float(SubImageSlideY->Value - 1.f) + 0.5f)*ysc);
		}

		if (ImageWndwPlotRadialVector->Checked && !IWLCK || PLOTRADIALLINE)
		{
			IMAGEWINDOWPEN->Color = Color::Yellow;
			e->Graphics->DrawPolygon(IMAGEWINDOWPEN, RADIALLINEBOXPOINTS);
		}

		if (SHOW_WCSCOORDS && WCS != nullptr)//plot grid lines of constant RA & dec
		{
			double xt, yt, xb, yb, xl, yl, xr, yr;
			double width = (double)IMAGESET[FILELISTINDEX]->Width * WCS->CDELTn[1] / 7200;
			double height = (double)IMAGESET[FILELISTINDEX]->Height * WCS->CDELTn[2] / 7200;
			WCS->Get_Pixel(WCS->CRVALn[1] + width, WCS->CRVALn[2], "TAN", xl, yl, true);
			WCS->Get_Pixel(WCS->CRVALn[1] - width, WCS->CRVALn[2], "TAN", xr, yr, true);
			WCS->Get_Pixel(WCS->CRVALn[1], WCS->CRVALn[2] + height, "TAN", xt, yt, true);
			WCS->Get_Pixel(WCS->CRVALn[1], WCS->CRVALn[2] - height, "TAN", xb, yb, true);
			IMAGEWINDOWPEN->Color = Color::Red;
			Drawing2D::LinearGradientBrush^ lgb = gcnew Drawing2D::LinearGradientBrush(Drawing::Point(int((float(xb) + 0.5f) * xsc), int((float(yb) + 0.5f) * ysc)), Drawing::Point(int((float(xt) + 0.5f) * xsc), int((float(yt) + 0.5f) * ysc)), Drawing::Color::Red, Drawing::Color::Blue);
			Drawing::Pen^ pn = gcnew Drawing::Pen(lgb);
			pn->Width = 2;
			e->Graphics->DrawLine(pn, (float(xb) + 0.5f) * xsc, (float(yb) + 0.5f) * ysc, (float(xt) + 0.5f) * xsc, (float(yt) + 0.5f) * ysc);
			IMAGEWINDOWPEN->Width = 2;
			e->Graphics->DrawLine(IMAGEWINDOWPEN, (float(xr) + 0.5f) * xsc, (float(yr) + 0.5f) * ysc, (float(xl) + 0.5f) * xsc, (float(yl) + 0.5f) * ysc);
			IMAGEWINDOWPEN->Width = 1;
		}

		if (POLYPOINTS != nullptr)
		{
			IMAGEWINDOWPEN->Color = POLYPOINTSCOLOR;
			e->Graphics->DrawPolygon(IMAGEWINDOWPEN, POLYPOINTS);
		}

		if (UVITINTMODEDRIFTPOLYPOINTS != nullptr)
		{
			IMAGEWINDOWPEN->Width = 1;
			array<Drawing::Color>^ colors = gcnew array<Drawing::Color>(5);
			colors[0] = Drawing::Color::Red;
			colors[1] = Drawing::Color::Yellow;
			colors[2] = Drawing::Color::Green;
			colors[3] = Drawing::Color::BlueViolet;
			colors[4] = Drawing::Color::Orange;
			int colc = 0;

			array<System::Drawing::Point>^ polypoints = gcnew array<System::Drawing::Point>(UVITINTMODEDRIFTPOLYPOINTS->GetLength(1));
			System::Drawing::Point goodpoint;
			for (int j = 0; j < UVITINTMODEDRIFTPOLYPOINTS->GetLength(0); j++)
			{
				for (int i = 0; i < UVITINTMODEDRIFTPOLYPOINTS->GetLength(1); i++)
					if (UVITINTMODEDRIFTPOLYPOINTS[j, i].X != 0)
					{
						polypoints[i] = UVITINTMODEDRIFTPOLYPOINTS[j, i];
						goodpoint = polypoints[i];
					}
					else
						polypoints[i] = goodpoint;

				IMAGEWINDOWPEN->Color = colors[colc];
				colc++;
				if (colc == 5)
					colc = 0;
				if (j == UVITINTDRIFT_MAXDEV_INDEX)
					IMAGEWINDOWPEN->Width = 3;
				else
					IMAGEWINDOWPEN->Width = 1;

				e->Graphics->DrawLines(IMAGEWINDOWPEN, polypoints);
				IMAGEWINDOWPEN->Width = 1;
			}
		}

		if (POLYPOINTS2 != nullptr)
		{
			IMAGEWINDOWPEN->Color = POLYPOINTS2COLOR;
			e->Graphics->DrawPolygon(IMAGEWINDOWPEN, POLYPOINTS2);
		}

		if (ROI_PATH_POINTS != nullptr)
		{
			IMAGEWINDOWPEN->Color = Color::Red;
			if (!DRAW_ROI_PATH_START && !PSEDrawROI->Checked)
				IMAGEWINDOWPEN->Width = 2;
			else
				IMAGEWINDOWPEN->Width = 1;
			e->Graphics->DrawPolygon(IMAGEWINDOWPEN, ROI_PATH_POINTS);

			IMAGEWINDOWBRUSH = gcnew SolidBrush(Color::FromArgb(25, 255, 0, 0));
			e->Graphics->FillPolygon(IMAGEWINDOWBRUSH, ROI_PATH_POINTS);
		}
	}
	catch(...)
	{
	}
}

void Form1::MAKEPSERECTS()
{
	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	PSESRECTS[PSESINDEX] = gcnew array<Rectangle, 1>(PSES[PSESINDEX]->N_Sources);
	for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		PSESRECTS[PSESINDEX][i] = Rectangle(int((float(PSES[PSESINDEX]->Centroids_X[i]) + 0.5) * xsc - 3), int((float(PSES[PSESINDEX]->Centroids_Y[i]) + 0.5) * ysc - 3), 7, 7);
}

void Form1::MAKEMARKCOORDRECTS()
{
	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	MARKCOORDRECTS = gcnew array<Rectangle, 1>(MARKCOORDS->GetLength(1));
	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
		MARKCOORDRECTS[i] = Rectangle(int((float(MARKCOORDS[0, i]) + 1) * xsc - 6), int((float(MARKCOORDS[1, i]) + 1) * ysc - 6), 13, 13);
}

void Form1::MAKEROIPATHPOINTS()
{
	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	ROI_PATH_POINTS = gcnew array<Point>(ROI_PATH_COORDS->GetLength(1));
	for (int i = 0; i < ROI_PATH_POINTS->Length; i++)
		ROI_PATH_POINTS[i] = Point(int((float(ROI_PATH_COORDS[0, i]) + 0.5)*xsc), int((float(ROI_PATH_COORDS[1, i]) + 0.5)*ysc));
}

void Form1::SpAxesUpD()
{
	if (FIRSTLOAD || !Chart1->Visible)
		return;

	Chart1->Series->Clear();
	//Chart1->Series->SuspendUpdates();
	Chart1->ChartAreas[0]->AxisX->Minimum = 1;
	Chart1->ChartAreas[0]->AxisX->Maximum = IMAGESET[FILELISTINDEX]->Width;
	Chart1->ChartAreas[0]->AxisY->Minimum = IMAGESET[FILELISTINDEX]->Min;
	Chart1->ChartAreas[0]->AxisY->Maximum = IMAGESET[FILELISTINDEX]->Max;

	for (int i = 0; i < IMAGESET[FILELISTINDEX]->Height; i++)
	{
		Chart1->Series->Add(i.ToString());
		Chart1->Series[i]->ChartType = Charting::SeriesChartType::FastLine;

		for (int j = 0; j < IMAGESET[FILELISTINDEX]->Width; j++)
			Chart1->Series[i]->Points->AddXY(j+1, IMAGESET[FILELISTINDEX]->Image[j,i]);

	}
	//Chart1->Series->ResumeUpdates();
}

inline void Form1::ImageWindow_MouseMove(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (IMAGESET->Count == 0)
		return;

	float xsc = (float(ImageWindow->Size.Width)/(float)IMAGESET[FILELISTINDEX]->Width);//image window size per data image pixel
	float ysc = (float(ImageWindow->Size.Height)/(float)IMAGESET[FILELISTINDEX]->Height);

	if (e->Button == ::MouseButtons::Middle)
	{
		if (DOMANREG || DOUVITMANREG || UVREGISTRATION || WCSMANUALRAD)
			return;

		try
		{
			XPOS_CURSOR = int(float(e->X)/xsc);
			YPOS_CURSOR = int(float(e->Y)/ysc);
			double val = (double)IMAGESET[FILELISTINDEX]->Image[XPOS_CURSOR,YPOS_CURSOR];
			XPositionTxt->Text = (XPOS_CURSOR+1).ToString();
			YPositionTxt->Text = (YPOS_CURSOR+1).ToString();
			XYImageValueTxt->Text = val.ToString();

			MidBtnMouseMoveXCurrent = int(float(e->X)/xsc);
			MidBtnMouseMoveYCurrent = int(float(e->Y)/ysc);
			if (MidBtnMouseMoveXPrev != MidBtnMouseMoveXCurrent || MidBtnMouseMoveYPrev != MidBtnMouseMoveYCurrent)
			{
				MidBtnMouseMoveXPrev = MidBtnMouseMoveXCurrent;
				MidBtnMouseMoveYPrev = MidBtnMouseMoveYCurrent;

				HalfWidthXUpD->Value = Math::Abs(MidBtnMouseMoveXCurrent - MidBtnMouseMoveXInit);
				HalfWidthYUpD->Value = Math::Abs(MidBtnMouseMoveYCurrent - MidBtnMouseMoveYInit);
			
			}
		}
		catch (...)
		{}
	}

	if (e->Button == ::MouseButtons::None)
	{
		int xpos = int(float(e->X)/xsc);
		int ypos = int(float(e->Y)/ysc);

		if (xpos != XPOS_CURSOR || ypos != YPOS_CURSOR)
		{
			XPOS_CURSOR = xpos;
			YPOS_CURSOR = ypos;
			if (XPOS_CURSOR < 0 || YPOS_CURSOR < 0 || XPOS_CURSOR > IMAGESET[FILELISTINDEX]->Width - 1 || YPOS_CURSOR > IMAGESET[FILELISTINDEX]->Height - 1)
				return;
			double val = (double)IMAGESET[FILELISTINDEX]->Image[XPOS_CURSOR,YPOS_CURSOR];
			XYImageValueTxt->Text = val.ToString("n5");
			if (!SHOW_WCSCOORDS)
			{
				XPositionTxt->Text = (XPOS_CURSOR+1).ToString();
				YPositionTxt->Text = (YPOS_CURSOR+1).ToString();
			}
			else//convert image coords to WCS coords
			{
				try
				{
					double a, d;
					String^ asx;
					String^ dsx;
					WCS->Get_Coordinate((double)XPOS_CURSOR, (double)YPOS_CURSOR, true, "TAN", a, d, asx, dsx);
					XPOS_CURSOR_RADEG = a;
					YPOS_CURSOR_DECDEG = d;
					XPOS_CURSOR_RAHMS = asx;
					YPOS_CURSOR_DECDMS = dsx;

					XPositionTxt->Text = XPOS_CURSOR_RAHMS;
					YPositionTxt->Text = YPOS_CURSOR_DECDMS;
				}
				catch (...)
				{
					XPositionTxt->Text = (XPOS_CURSOR + 1).ToString();
					YPositionTxt->Text = (YPOS_CURSOR + 1).ToString();
				}
			}
			XYImageValueTxt->Refresh();
			XPositionTxt->Refresh();
			YPositionTxt->Refresh();
		}

		if (!IWLCK)//allow cursor box to move, then move sub image sliders around, and SubImage too, update PRVX/YPOS values
		{
			if (PRVXPOS_CURSOR != XPOS_CURSOR || PRVYPOS_CURSOR != YPOS_CURSOR)
			{
				SubImageSlideX->Value = XPOS_CURSOR+1;
				SubImageSlideY->Value = YPOS_CURSOR+1;
				PRVXPOS_CURSOR = XPOS_CURSOR;
				PRVYPOS_CURSOR = YPOS_CURSOR;

				if (ImageWndwCntxtPlotRow->Checked)
					ROWplotUpD(false);
				if (ImageWndwCntxtPlotCol->Checked)
					COLplotUpD(false);

				if (DOMANREG || UVREGISTRATION && UVREGISTRATIONFILESINDEX == 0 || WCSMANUALRAD)
				{
					int xind, yind;
					double max = JPMath::Max(SUBIMAGE, xind, yind, false);
					array<int, 2>^ coords = JPMath::Find(SUBIMAGE, max, "==", false);
					FNDCOORDS[0,0] = coords[0,0] + XSUBRANGE[0];
					FNDCOORDS[0,1] = coords[0,1] + YSUBRANGE[0];
					FNDCOORDRECTS[0] = Rectangle(int((float(FNDCOORDS[0,0]+1))*xsc-3),int((float(FNDCOORDS[0,1]+1))*ysc-3),7,7);
				}

				if (UVREGISTRATION && UVREGISTRATIONFILESINDEX > 0)//then see if the cursor is near the MANREGCOORS, and if it is, bold their RECTS
				{
					UVREGISTRATION_TOUCHPOINT = false;
					for (int i = 0; i < MANREGCOORDRECTS->Length; i++)
					{
						if (Math::Abs(XPOS_CURSOR - MANREGCOORDS[i,0]) <= 3/xsc && Math::Abs(YPOS_CURSOR - MANREGCOORDS[i,1]) <= 3/ysc)
						{
							UVREGISTRATION_TOUCHPOINT = true;
							break;
						}
					}
				}

				if (ImageWndwPlotRadialVector->Checked)
					RADIALLINE_PLOTUpD();

				SubImageStatsUpD();
				SubImageUpD();
				ImageWindow->Refresh();
			}
		}
	}

	if (e->Button == ::MouseButtons::Left)
	{
		int xpos = int(float(e->X) / xsc);
		int ypos = int(float(e->Y) / ysc);

		if (UVREGISTRATION && UVREGISTRATIONFILESINDEX > 0 && UVREGISTRATION_TOUCHPOINT)//then move the MANREGCOORDS with the pointer
		{
			ShowFoundCoordsChck->Checked = true;

			if (xpos != XPOS_CURSOR || ypos != YPOS_CURSOR)
			{
				XPOS_CURSOR = xpos;
				YPOS_CURSOR = ypos;
				XPositionTxt->Text = (XPOS_CURSOR+1).ToString();
				YPositionTxt->Text = (YPOS_CURSOR+1).ToString();
				XYImageValueTxt->Text = ((double)IMAGESET[FILELISTINDEX]->Image[XPOS_CURSOR,YPOS_CURSOR]).ToString();
				SubImageSlideX->Value = XPOS_CURSOR+1;
				SubImageSlideY->Value = YPOS_CURSOR+1;

				int xind, yind;
				double max = JPMath::Max(SUBIMAGE, xind, yind, false);
				array<int, 2>^ coords = JPMath::Find(SUBIMAGE, max, "==", false);
				FNDCOORDS[0,0] = coords[0,0] + XSUBRANGE[0];
				FNDCOORDS[0,1] = coords[0,1] + YSUBRANGE[0];
				FNDCOORDRECTS[0] = Rectangle(int((float(FNDCOORDS[0,0]+1))*xsc-3),int((float(FNDCOORDS[0,1]+1))*ysc-3),7,7);

				if (UVREGISTRATION_TRANSLATE)
				{
					for (int i = 0; i < MANREGCOORDRECTS->Length; i++)
					{
						MANREGCOORDS[i,0] += XPOS_CURSOR - PRVXPOS_CURSOR;
						MANREGCOORDS[i,1] += YPOS_CURSOR - PRVYPOS_CURSOR;
						MANREGCOORDRECTS[i] = Rectangle(int((float(MANREGCOORDS[i, 0] + 1)) * xsc - 3), int((float(MANREGCOORDS[i, 1] + 1)) * ysc - 3), 7, 7);
					}
				}
				else//rotation
				{
					double dx_prev = double(PRVXPOS_CURSOR - MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,0]);
					double dy_prev = double(PRVYPOS_CURSOR - MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,1]);
					double theta_prev = JPMath::aTanAbsoluteAngle(dx_prev, dy_prev);
					
					double dx_curr = double(XPOS_CURSOR - MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,0]);
					double dy_curr = double(YPOS_CURSOR - MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,1]);
					double theta_curr = JPMath::aTanAbsoluteAngle(dx_curr, dy_curr);
										
					UVREGISTRATION_ROTATION_PHI += theta_curr - theta_prev;

					double xcenter = double(UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,0]);
					double ycenter = double(UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,1]);

					for (int j = 0; j < MANREGCOORDRECTS->Length; j++)
					{
						if (j == UVREGISTRATION_ANCHOR_INDEX)
							continue;

						double x = UVREGISTRATION_ROTATION_CENTROIDS[j,0];
						double y = UVREGISTRATION_ROTATION_CENTROIDS[j,1];

						int xprime = int((x - xcenter)*::Math::Cos(UVREGISTRATION_ROTATION_PHI) - (y - ycenter)*::Math::Sin(UVREGISTRATION_ROTATION_PHI) + xcenter);
						int yprime = int((x - xcenter)*::Math::Sin(UVREGISTRATION_ROTATION_PHI) + (y - ycenter)*::Math::Cos(UVREGISTRATION_ROTATION_PHI) + ycenter);

						MANREGCOORDS[j,0] = xprime;
						MANREGCOORDS[j,1] = yprime;
						MANREGCOORDRECTS[j] = Rectangle(int((float(MANREGCOORDS[j,0]+1))*xsc-3),int((float(MANREGCOORDS[j,1]+1))*ysc-3),7,7);
					}
				}

				PRVXPOS_CURSOR = XPOS_CURSOR;
				PRVYPOS_CURSOR = YPOS_CURSOR;
				SubImageStatsUpD();
				SubImageUpD();
				ImageWindow->Refresh();
			}
			return;
		}

		if (DRAW_ROI_PATH)
		{
			if (xpos != XPOS_CURSOR || ypos != YPOS_CURSOR)
			{
				XPOS_CURSOR = xpos;
				YPOS_CURSOR = ypos;
				PRVXPOS_CURSOR = XPOS_CURSOR;
				PRVYPOS_CURSOR = YPOS_CURSOR;

				if (ROI_PATH_COORDS == nullptr)
					ROI_PATH_COORDS = gcnew array<double, 2>(2, 0);
				array<double, 2>^ temp = gcnew array<double, 2>(2, ROI_PATH_COORDS->GetLength(1) + 1);
				for (int i = 0; i < ROI_PATH_COORDS->GetLength(1); i++)
				{
					temp[0, i] = ROI_PATH_COORDS[0, i];
					temp[1, i] = ROI_PATH_COORDS[1, i];
				}
				temp[0, ROI_PATH_COORDS->GetLength(1)] = (double)xpos;
				temp[1, ROI_PATH_COORDS->GetLength(1)] = (double)ypos;
				ROI_PATH_COORDS = gcnew array<double, 2>(2, temp->GetLength(1));
				for (int i = 0; i < ROI_PATH_COORDS->GetLength(1); i++)
				{
					ROI_PATH_COORDS[0, i] = temp[0, i];
					ROI_PATH_COORDS[1, i] = temp[1, i];
				}

				if (!DRAW_ROI_PATH_START && Math::Abs(xpos - ROI_PATH_COORDS[0, 0]) < SUBIMAGE_HWX && Math::Abs(ypos - ROI_PATH_COORDS[1, 0]) < SUBIMAGE_HWY)
				{
					DRAW_ROI_PATH = false;//finished drawing
					ImageWindow->Refresh();
					ROI_PATH_FILLREGION();
					return;
				}
				if (DRAW_ROI_PATH_START && Math::Abs(xpos - ROI_PATH_COORDS[0, 0]) > SUBIMAGE_HWX && Math::Abs(ypos - ROI_PATH_COORDS[1, 0]) > SUBIMAGE_HWY)
					DRAW_ROI_PATH_START = false;

				MAKEROIPATHPOINTS();
				SubImageStatsUpD();
				SubImageUpD();
				ImageWindow->Refresh();
			}
		}
	}
}

void Form1::ImageWindow_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e)
{
	if (IMAGESET->Count == 0)
		return;

	float xsc = (float(ImageWindow->Size.Width)/(float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height)/(float)IMAGESET[FILELISTINDEX]->Height);
	XPOS_CURSOR = int(float(e->X)/xsc);
	YPOS_CURSOR = int(float(e->Y)/ysc);

	if (e->Button == ::MouseButtons::Middle)
	{
		if (DOMANREG || DOUVITMANREG || UVREGISTRATION || WCSMANUALRAD)
			return;

		IWLCK = true;//fix cursor box
		EqualHWChck->Checked = false;
		MidBtnMouseMoveXInit = int(float(e->X)/xsc);
		MidBtnMouseMoveYInit = int(float(e->Y)/ysc);
		MidBtnMouseMoveXPrev = MidBtnMouseMoveXInit;
		MidBtnMouseMoveYPrev = MidBtnMouseMoveYInit;
		double val = (double)IMAGESET[FILELISTINDEX]->Image[XPOS_CURSOR,YPOS_CURSOR];
		XPositionTxt->Text = (XPOS_CURSOR+1).ToString();
		YPositionTxt->Text = (YPOS_CURSOR+1).ToString();
		XYImageValueTxt->Text = val.ToString();
		SubImageSlideX->Value = XPOS_CURSOR+1;
		SubImageSlideY->Value = YPOS_CURSOR+1;
		PRVXPOS_CURSOR = XPOS_CURSOR;
		PRVYPOS_CURSOR = YPOS_CURSOR;
		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();
	}

	if (e->Button == ::MouseButtons::Left)
	{
		if (!DOMANREG && !DOUVITMANREG && !UVREGISTRATION && !WCSMANUALRAD)
		{
			IWLCK = !IWLCK;  //Image Window Left Click: this (true or false) sets whether to update subimage window

			if (IWLCK)
				ImageWndwPlotRadialVector->Enabled = true;
		}

		if (DOMANREG || DOUVITMANREG || UVREGISTRATION && UVREGISTRATIONFILESINDEX == 0 || WCSMANUALRAD)//gather points
		{
			int N = MANREGCOORDRECTS->Length + 1;

			array<int,2>^ tempcoords = gcnew array<int,2>(N,2);
			array<Rectangle,1>^ temprects = gcnew array<Rectangle,1>(N);

			for (int i = 0; i < MANREGCOORDRECTS->Length; i++)
			{
				if (MANREGCOORDS[i,0] == FNDCOORDS[0,0] && MANREGCOORDS[i,1] == FNDCOORDS[0,1])//pressed on src already selected
				{
					WCSNEWPOINT = false;
					return;
				}
				tempcoords[i, 0] = MANREGCOORDS[i, 0];
				tempcoords[i, 1] = MANREGCOORDS[i, 1];
				temprects[i] = MANREGCOORDRECTS[i];
			}
			tempcoords[N - 1, 0] = FNDCOORDS[0, 0];
			tempcoords[N - 1, 1] = FNDCOORDS[0, 1];
			temprects[N - 1] = FNDCOORDRECTS[0];

			MANREGCOORDS = tempcoords;
			MANREGCOORDRECTS = temprects;

			WCSNEWPOINT = true;

			SubImageWindow->Refresh();
		}

		if (UVREGISTRATION && UVREGISTRATIONFILESINDEX > 0 && UVREGISTRATION_TOUCHPOINT)//touching a previously selected point for UVregistration, decide how to handle mouse move
		{
			int index;
			for (index = 0; index < MANREGCOORDRECTS->Length; index++)
				if (Math::Abs(XPOS_CURSOR - MANREGCOORDS[index,0]) <= 3/xsc && Math::Abs(YPOS_CURSOR - MANREGCOORDS[index,1]) <= 3/ysc)
					break;

			if (index == UVREGISTRATION_ANCHOR_INDEX || UVREGISTRATION_ANCHOR_INDEX == ::Int32::MaxValue)//then it is a first selection of the anchor index or translation of the anchor
			{
				UVREGISTRATION_TRANSLATE = true;
				UVREGISTRATION_ANCHOR_INDEX = index;//this sets the anchor index but keeps it the same for all fields too
			}
			else if (index != UVREGISTRATION_ANCHOR_INDEX)
			{
				UVREGISTRATION_TRANSLATE = false;
				UVREGISTRATION_ROTATION_INDEX = index;//this is the point which is being touched for the purpose of rotating about the ANCHOR_INDEX point
			}
		}

		ImageWindow->Refresh();

		if (COG_CURSOR)
			SubImageWindow->Refresh();
	}

	if (UVREGISTRATION && e->Button == ::MouseButtons::Right)
		if (MARKCOORDS != nullptr && MANREGCOORDRECTS->Length == 0 && UVREGISTRATIONFILESINDEX == 0)//have marked coordinates which may possibly optionally be used
		{
			::DialogResult res = MessageBox::Show("Should I use the marked coordinates for registration?", "Use Marked Coords???", MessageBoxButtons::YesNoCancel);
			if (res == ::DialogResult::Yes)//use MARKCOORDS to create registration pts
			{
				MANREGCOORDS = gcnew array<int, 2>(MARKCOORDS->GetLength(1), MARKCOORDS->GetLength(0));
				MANREGCOORDRECTS = gcnew array<::Drawing::Rectangle>(MARKCOORDRECTS->Length);
				for (int i = 0; i < MARKCOORDRECTS->Length; i++)
				{
					MANREGCOORDS[i, 0] = int(float(MARKCOORDRECTDPTS[i]->X + 6) / xsc + 0);
					MANREGCOORDS[i, 1] = int(float(MARKCOORDRECTDPTS[i]->Y + 6) / ysc + 0);
					MANREGCOORDRECTS[i] = Rectangle(int((float(MANREGCOORDS[i, 0] + 1)) * xsc - 3), int((float(MANREGCOORDS[i, 1] + 1)) * ysc - 3), 7, 7);
				}
				ImageWindow->Refresh();
				SubImageWindow->Refresh();

				ImageWindow_MouseUp(sender, e);
			}
			if (res == ::DialogResult::Cancel)
			{
				UVREGISTRATION = false;
				UVREGISTRATIONFILES = nullptr;
			}
		}
}

void Form1::ImageWindow_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	 if (IMAGESET->Count == 0)
		return;

	 float xsc = (float(ImageWindow->Size.Width)/(float)IMAGESET[FILELISTINDEX]->Width);
	 float ysc = (float(ImageWindow->Size.Height)/(float)IMAGESET[FILELISTINDEX]->Height);

	 if (e->Button == ::MouseButtons::Right)
	 {
		 if (DOMANREG || DOUVITMANREG || WCSMANUALRAD)//end point selection
		 {
			 ImageWindowCntxt->Hide();
			 
			 if (DOMANREG)
			 {
				MANREG_CONTINUE = true;
				UVITMANREG_CONTINUE = false;
				DOMANREG = false;
			 }
			 if (DOUVITMANREG)
			 {
				 DOMANREG = false;
				 MANREG_CONTINUE = false;
				 UVITMANREG_CONTINUE = true;
				 DOUVITMANREG = false;
			 }
			 if (WCSMANUALRAD)
			 {
				 WCSMANUALRAD_CONTINUE = false;
			 }

			 ShowFoundCoordsChck->Checked = false;
			 IWLCK = true;//fix cursor box
			 ImageWindow->Cursor->Show();
			 ImageWindow->Refresh();
			 if (MANREG_CONTINUE || UVITMANREG_CONTINUE)
			 {
				ManRegBtn->PerformClick();
				return;
			 }
			 if (WCSMANUALRAD)
				 WCSRADecManual->PerformClick();
		 }

		 if (UVREGISTRATION)//then continue to next image
		 {
			 ImageWindowCntxt->Hide();
			 ImageWindow->Cursor->Show();

			 try
			 {
				 if (MANREGCOORDRECTS->Length > 0)
				 {
					 if (UVREGISTRATION_CENTROIDS == nullptr)
					 {
						 UVREGISTRATION_CENTROIDS = gcnew array<double, 3>(UVREGISTRATIONFILES->Length, MANREGCOORDRECTS->Length, 2);
						 UVREGISTRATION_ROTATION_CENTROIDS = gcnew array<double, 2>(MANREGCOORDRECTS->Length, 2);

						 //the following are the initial guesses for the rotation/skew fit function
						 UVREGISTRATION_PHIS = gcnew array<double>(UVREGISTRATIONFILES->Length);//@index 0 = 0 (reference)
						 UVREGISTRATION_XSHIFTS = gcnew array<double>(UVREGISTRATIONFILES->Length);//@index 0 = 0 (reference)
						 UVREGISTRATION_YSHIFTS = gcnew array<double>(UVREGISTRATIONFILES->Length);//@index 0 = 0 (reference)
						 UVREGISTRATION_XCENTERS = gcnew array<double>(UVREGISTRATIONFILES->Length);//@index 0 = 0 (reference)
						 UVREGISTRATION_YCENTERS = gcnew array<double>(UVREGISTRATIONFILES->Length);//@index 0 = 0 (reference)
					 }

					 array<double, 2>^ subim = gcnew array<double, 2>(SUBIMAGE_HWX * 2 + 1, SUBIMAGE_HWX * 2 + 1);
					 PSES = gcnew array<JPFITS::SourceExtractor^>(1) { gcnew JPFITS::SourceExtractor() };
					 PSESINDEX = 0;
					 PSESRECTS = gcnew array<array<Rectangle>^>(1);

					 double pad = Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("PADOFSET")) * Convert::ToDouble(IMAGESET[FILELISTINDEX]->GetKeyValue("IMAGPREC"));

					 for (int i = 0; i < MANREGCOORDRECTS->Length; i++)
					 {
						 int xind, yind;
						 subim = IMAGESET[0]->GetSubImage(MANREGCOORDS[i, 0], MANREGCOORDS[i, 1], SUBIMAGE_HWX, SUBIMAGE_HWX);
						 PSES[PSESINDEX]->Extract_Sources(subim, 0, JPMath::Max(subim, xind, yind, false) - 1, JPMath::Max(subim, xind, yind, false) + 1, 0, ::Double::MaxValue, false, 2, 2, false, "", nullptr, false);
						 UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, i, 0] = PSES[PSESINDEX]->Centroids_X[0] + double(MANREGCOORDS[i, 0] - SUBIMAGE_HWX) - pad;
						 UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, i, 1] = PSES[PSESINDEX]->Centroids_Y[0] + double(MANREGCOORDS[i, 1] - SUBIMAGE_HWY) - pad;
						 UVREGISTRATION_ROTATION_CENTROIDS[i, 0] = UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, i, 0] + pad;//copy these for rotating
						 UVREGISTRATION_ROTATION_CENTROIDS[i, 1] = UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, i, 1] + pad;
					 }

					 if (UVREGISTRATIONFILESINDEX > 0)//record the shift, center, and rotation for using as first guesses in rotation tranformation fit
					 {
						 if (UVREGISTRATION_ANCHOR_INDEX == ::Int32::MaxValue)
							 UVREGISTRATION_ANCHOR_INDEX = 0;

						 //the first guess parameters are such that they should move the UVREGISTRATIONFILESINDEX to the position of index 0 when transformed
						 UVREGISTRATION_XSHIFTS[UVREGISTRATIONFILESINDEX] = UVREGISTRATION_CENTROIDS[0, 0, 0] - UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, 0, 0];//at this point all points should be aligned, so the shift is the same for all pts, so just use pt index 0 for current and reference shift
						 UVREGISTRATION_YSHIFTS[UVREGISTRATIONFILESINDEX] = UVREGISTRATION_CENTROIDS[0, 0, 1] - UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, 0, 1];

						 UVREGISTRATION_XCENTERS[UVREGISTRATIONFILESINDEX] = UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, UVREGISTRATION_ANCHOR_INDEX, 0];
						 UVREGISTRATION_YCENTERS[UVREGISTRATIONFILESINDEX] = UVREGISTRATION_CENTROIDS[UVREGISTRATIONFILESINDEX, UVREGISTRATION_ANCHOR_INDEX, 1];

						 UVREGISTRATION_PHIS[UVREGISTRATIONFILESINDEX] = -UVREGISTRATION_ROTATION_PHI + UVREGISTRATION_PHIS[UVREGISTRATIONFILESINDEX - 1];
					 }
				 }
			 }
			 catch (Exception^ e)
			 {
				 //MessageBox::Show(e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite);
				 MessageBox::Show("You must be a little bit misaligned. Please give these points an adjustment.\r\n\r\n " + e->Data + "	" + e->InnerException + "	" + e->Message + "	" + e->Source + "	" + e->StackTrace + "	" + e->TargetSite, "Warning");
				 return;
			 }

			 //use set coordinates for auto run through the rest of the images, if on first image and if imageset is already registered at least once
			 if (UVREGISTRATIONFILESINDEX == 0 && IMAGESET[FILELISTINDEX]->FileName->Contains("RGSTRD"))
				 if (MessageBox::Show("Run through with the registration coordinates for all images?", "Auto Run Through Registration?", MessageBoxButtons::YesNo) == ::DialogResult::Yes)
				 {
					 ProgressBar->Value = 0;
					 ProgressBar->Maximum = UVREGISTRATIONFILES->Length;
					 ProgressBar->Refresh();
					 UVITAUTOREGISTER = true;
				 }

			 //MessageBox::Show("here2");
			 GeneralUVRegistrationMenuItem_Click(sender, e);
		 }
	 }

	 if (e->Button == ::MouseButtons::Left)
	 {
		 if (WCSMANUALRAD)
			WCSRADecManual->PerformClick();

		 if (UVREGISTRATION && UVREGISTRATIONFILESINDEX > 0 && UVREGISTRATION_TOUCHPOINT)
		 {
			if (UVREGISTRATION_TRANSLATE)//snap to FNDCOORD & save the coords for rotating...create centroids list etc
			{
				int dx = FNDCOORDS[0,0] - MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,0];
				int dy = FNDCOORDS[0,1] - MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,1];
				for (int i = 0; i < MANREGCOORDRECTS->Length; i++)
				{
					MANREGCOORDS[i,0] += dx;
					MANREGCOORDS[i,1] += dy;
					MANREGCOORDRECTS[i] = Rectangle(int((float(MANREGCOORDS[i,0]+1))*xsc-3),int((float(MANREGCOORDS[i,1]+1))*ysc-3),7,7);
				}

				double ddx = (double)MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,0] - UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,0];
				double ddy = (double)MANREGCOORDS[UVREGISTRATION_ANCHOR_INDEX,1] - UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,1];
				for (int i = 0; i < MANREGCOORDRECTS->Length; i++)
				{
					UVREGISTRATION_ROTATION_CENTROIDS[i,0] += ddx;
					UVREGISTRATION_ROTATION_CENTROIDS[i,1] += ddy;
				}
			}
			else//rotate to FNDCOORD
			{
				double dx_prev = double(UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ROTATION_INDEX,0] - UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,0]);
				double dy_prev = double(UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ROTATION_INDEX,1] - UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,1]);
				double theta_prev = JPMath::aTanAbsoluteAngle(dx_prev, dy_prev);
				
				double dx_curr = double(FNDCOORDS[0,0] - UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,0]);
				double dy_curr = double(FNDCOORDS[0,1] - UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,1]);
				double theta_curr = JPMath::aTanAbsoluteAngle(dx_curr, dy_curr);
				
				UVREGISTRATION_ROTATION_PHI = theta_curr - theta_prev;

				double xcenter = double(UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,0]);
				double ycenter = double(UVREGISTRATION_ROTATION_CENTROIDS[UVREGISTRATION_ANCHOR_INDEX,1]);

				for (int j = 0; j < MANREGCOORDRECTS->Length; j++)
				{
					if (j == UVREGISTRATION_ANCHOR_INDEX)
						continue;

					double x = UVREGISTRATION_ROTATION_CENTROIDS[j,0];
					double y = UVREGISTRATION_ROTATION_CENTROIDS[j,1];

					int xprime = int((x - xcenter)*::Math::Cos(UVREGISTRATION_ROTATION_PHI) - (y - ycenter)*::Math::Sin(UVREGISTRATION_ROTATION_PHI) + xcenter);
					int yprime = int((x - xcenter)*::Math::Sin(UVREGISTRATION_ROTATION_PHI) + (y - ycenter)*::Math::Cos(UVREGISTRATION_ROTATION_PHI) + ycenter);

					MANREGCOORDS[j,0] = xprime;
					MANREGCOORDS[j,1] = yprime;
					MANREGCOORDRECTS[j] = Rectangle(int((float(MANREGCOORDS[j, 0] + 1)) * xsc - 3), int((float(MANREGCOORDS[j, 1] + 1)) * ysc - 3), 7, 7);
				}
			}

			ShowFoundCoordsChck->Checked = false;
			ImageWindow->Refresh();
		 }

		 if (DRAW_ROI_PATH && !DRAW_ROI_PATH_START)//finished drawing
		 {
			 DRAW_ROI_PATH = false;//finished drawing
			 ImageWindow->Refresh();
			 ROI_PATH_FILLREGION();
			 return;
		 }
	 }

	 if (e->Button == ::MouseButtons::XButton1)
	 {
		 ViewLastbtn->PerformClick();
	 }
	 if (e->Button == ::MouseButtons::XButton2)
	 {
		 ViewNextBtn->PerformClick();
	 }
	 if (e->Button == ::MouseButtons::Middle)
	 {
	 }
}

void Form1::ImageWindow_Click(System::Object^  sender, System::EventArgs^  e)
{	
}

void Form1::ImageWindow_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
}

void Form1::ImageWindow_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Left)
	{
		EqualHWChck->Checked = false;
		EqualHWChck->Checked = true;
	}
}

void Form1::ImageWindow_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::ImageWindow_MouseEnter(System::Object ^  sender, System::EventArgs ^  e)
{
	if (IMAGESET->Count == 0)
		return;

	XPositionTxt->Visible = true;
	YPositionTxt->Visible = true;
	XYImageValueTxt->Visible = true;

	ImageWindow->Focus();
}

void Form1::ImageWindow_MouseLeave(System::Object ^  sender, System::EventArgs ^  e)
{
	XPositionTxt->Visible = false;
	YPositionTxt->Visible = false;
	XYImageValueTxt->Visible = false;

	this->ActiveControl = nullptr;
}

void Form1::SubImageSlideX_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e)
{
	SubImageStatsUpD();
	SubImageUpD();
	ImageWindow->Refresh();

	PRVXPOS_CURSOR = SubImageSlideX->Value-1;

	if (ImageWndwCntxtPlotRow->Checked)
		ROWplotUpD(false);
	if (ImageWndwCntxtPlotCol->Checked)
		COLplotUpD(false);

	if (PLOTRADIALLINE)
		RADIALLINE_PLOTUpD();
}

void Form1::SubImageSlideY_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e)
{
	SubImageStatsUpD();
	SubImageUpD();
	ImageWindow->Refresh();

	PRVYPOS_CURSOR = SubImageSlideY->Value-1;

	if (ImageWndwCntxtPlotRow->Checked)
		ROWplotUpD(false);
	if (ImageWndwCntxtPlotCol->Checked)
		COLplotUpD(false);

	if (PLOTRADIALLINE)
		RADIALLINE_PLOTUpD();
}

void Form1::PSEFitResultListBox_MouseEnter(System::Object^  sender, System::EventArgs^  e)
{
	SubImageWindow->SendToBack();
	SubImagePanel->SendToBack();
	SubImageSlideX->SendToBack();
	SubImageSlideY->SendToBack();
}

void Form1::SubImagePanel_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
	SubImageWindow->Focus();
	SubImagePanel->BringToFront();
}

void Form1::FileInfoPanel_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
	SubImageWindow->Focus();
	FileInfoPanel->BringToFront();
}

void Form1::SubImageWindow_MouseEnter(System::Object ^  sender, System::EventArgs ^  e)
{
	if (IMAGESET->Count == 0)
		return;

	XPositionTxt->Visible = true;
	YPositionTxt->Visible = true;
	XYImageValueTxt->Visible = true;

	SubImageWindow->Focus();
	SubImageWindow->BringToFront();
	SubImageSlideX->BringToFront();
	SubImageSlideY->BringToFront();
}

void Form1::SubImageWindow_MouseLeave(System::Object ^  sender, System::EventArgs ^  e)
{
	XPositionTxt->Visible = false;
	YPositionTxt->Visible = false;
	XYImageValueTxt->Visible = false;
	//SubImageWindow->SendToBack();

	this->ActiveControl = nullptr;
}

void Form1::ShowCursorBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	/*int offset = (ImageWindow->Width - ImageWindow->Height) / 2;
	ImageWindow->Width = ImageWindow->Height;
	ImageWindow->Location.X = 200;*/

	ImageWindow->Refresh();
}

void Form1::ShowCrosshair_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindow->Refresh();
}

void Form1::Tooltip_Popup(System::Object^  sender, System::Windows::Forms::PopupEventArgs^  e)
{
	//Tooltip->SetToolTip(this->SubImageWindow,"Hello");
}

void Form1::ImageWindow_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (IMAGESET->Count == 0)
		return;

	Decimal d = 1;
	if (e->Delta < 0)
		d = -1;

	try
	{
		HalfWidthXUpD->Value += d;
		if (!EqualHWChck->Checked)
			HalfWidthYUpD->Value += d;

		if (PLOTRADIALLINE)
			RADIALLINE_PLOTUpD();
	}
	catch (...)//will just be UpD control value errors, so just ignore
	{};

}

void Form1::SubImageWindow_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (IMAGESET->Count > 0)
	{
		Decimal d = 1;
		if (e->Delta < 0)
			d = -1;

		try
		{
			HalfWidthXUpD->Value += d;
			if (!EqualHWChck->Checked)
				HalfWidthYUpD->Value += d;

			if (PLOTRADIALLINE)
				RADIALLINE_PLOTUpD();
		}
		catch (...)//will just be UpD control value errors, so just ignore
		{};
	}
}

void Form1::SubImageWindow_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Left)
	{
		int x, y;
		double max = JPMath::Max(SUBIMAGE, x, y, true);
		SubImageSlideX->Value = x + 1 + XSUBRANGE[0];
		SubImageSlideY->Value = y + 1 + YSUBRANGE[0];
		PRVXPOS_CURSOR = SubImageSlideX->Value - 1;
		PRVYPOS_CURSOR = SubImageSlideY->Value - 1;

		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();

		if (ImageWndwCntxtPlotRow->Checked)
			ROWplotUpD(false);
		if (ImageWndwCntxtPlotCol->Checked)
			COLplotUpD(false);

		if (PLOTRADIALLINE)
			RADIALLINE_PLOTUpD();
	}
}

void Form1::SubImageWindow_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{

}

void Form1::SubImageWindow_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
}

void Form1::SubImageWindow_MouseMove(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (IMAGESET->Count > 0 && e->Button == ::MouseButtons::None)
	{
		double xpos = double(e->X);
		double ypos = double(e->Y);
		double imwidth = (double)SubImageWindow->Width;
		double imheight = (double)SubImageWindow->Height;
		int w = int(HalfWidthXUpD->Value)*2+1;
		int h = int(HalfWidthYUpD->Value)*2+1;
		XPOS_CURSOR = XSUBRANGE[0] + int(Math::Floor((xpos/(imwidth))*double(w))) - 0;
		YPOS_CURSOR = YSUBRANGE[0] + int(Math::Floor((ypos/(imheight))*double(h))) - 0;
		double val = IMAGESET[FILELISTINDEX]->Image[int(XPOS_CURSOR),int(YPOS_CURSOR)];
		XYImageValueTxt->Text = val.ToString("n5");
		if (!SHOW_WCSCOORDS || WCS == nullptr)
		{
			XPositionTxt->Text = (XPOS_CURSOR+1).ToString();
			YPositionTxt->Text = (YPOS_CURSOR+1).ToString();
		}
		else//convert image coords to WCS coords
		{
			double a, d;
			String^ asx;
			String^ dsx;
			WCS->Get_Coordinate((double)XPOS_CURSOR, (double)YPOS_CURSOR, true, "TAN", a, d, asx, dsx);
			XPOS_CURSOR_RADEG = a;
			YPOS_CURSOR_DECDEG = d;
			XPOS_CURSOR_RAHMS = asx;
			YPOS_CURSOR_DECDMS = dsx;

			XPositionTxt->Text = XPOS_CURSOR_RAHMS;
			YPositionTxt->Text = YPOS_CURSOR_DECDMS;
		}
	}
	else if (IMAGESET->Count > 0 && e->Button == ::MouseButtons::Left)
	{
		try
		{
			double xpos = double(e->X);
			double ypos = double(e->Y);
			double imwidth = (double)SubImageWindow->Width;
			double imheight = (double)SubImageWindow->Height;
			double w = double(HalfWidthXUpD->Value)*2+1;
			double h = double(HalfWidthYUpD->Value)*2+1;
			double x = double(XSUBRANGE[0]) + xpos/imwidth*w;
			double y = double(YSUBRANGE[0]) + ypos/imheight*h;

			SubImageSlideX->Value -= int(x - SUBIMLEFTMOUSEDOWNINITX);
			SubImageSlideY->Value -= int(y - SUBIMLEFTMOUSEDOWNINITY);

			SubImageStatsUpD();
			SubImageUpD();
			ImageWindow->Refresh();

			if (ImageWndwCntxtPlotRow->Checked)
				ROWplotUpD(false);
			if (ImageWndwCntxtPlotCol->Checked)
				COLplotUpD(false);

			if (PLOTRADIALLINE)
				RADIALLINE_PLOTUpD();
		}
		catch(...){}//just catching out of bounds stuff
	}
}

void Form1::SubImageWindow_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (e->Button == ::MouseButtons::Left)
	{
		double xpos = double(e->X);
		double ypos = double(e->Y);
		double imwidth = (double)SubImageWindow->Width;
		double imheight = (double)SubImageWindow->Height;
		double w = double(HalfWidthXUpD->Value)*2+1;
		double h = double(HalfWidthYUpD->Value)*2+1;
		SUBIMLEFTMOUSEDOWNINITX = double(XSUBRANGE[0]) + xpos/imwidth*w;
		SUBIMLEFTMOUSEDOWNINITY = double(YSUBRANGE[0]) + ypos/imheight*h;

		SubImageWindow->Cursor = ::Cursors::Hand;
	}
}

void Form1::SubImageWindow_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	//Tooltip->RemoveAll();//this removes the tootip for all of Form1...not right solution

	SubImageWindow->Cursor = ::Cursors::Cross;

	if (e->Button == ::MouseButtons::XButton1)
	{
		ViewLastbtn->PerformClick();
	}
	if (e->Button == ::MouseButtons::XButton2)
	{
		ViewNextBtn->PerformClick();
	}
}

void Form1::ImageWndwCntxtPlotRowSubOnly_Click(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindowCntxt->Show();
	ImageWndwCntxtPlot->ShowDropDown();

	if (ImageWndwCntxtPlotRow->Checked)
		ROWplotUpD(false);
}

void Form1::ImageWndwCntxtPlotColSubOnly_Click(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindowCntxt->Show();
	ImageWndwCntxtPlot->ShowDropDown();

	if (ImageWndwCntxtPlotCol->Checked)
		COLplotUpD(false);
}

void Form1::RADIALLINE_PLOTUpD()
{
	if (RADIALLINE_PLOT->IsDisposed)
	{
		ImageWndwPlotRadialVector->Checked = false;
		return;
	}

	double xsc = (float(ImageWindow->Size.Width) / (double)IMAGESET[FILELISTINDEX]->Width);
	double ysc = (float(ImageWindow->Size.Height) / (double)IMAGESET[FILELISTINDEX]->Height);

	double phi;
	int length;

	if (RADIALPLOT_SETPHI)
	{
		phi = RADIALPLOT_PHI;

		//get current length for setting new radial line end coordinates and update subwindow
		length = (int)Math::Sqrt(double((RADIALPTX1 - RADIALPTX2)*(RADIALPTX1 - RADIALPTX2) + (RADIALPTY1 - RADIALPTY2)*(RADIALPTY1 - RADIALPTY2)));

		RADIALPTX2 = RADIALPTX1 + int(double(length) * Math::Cos(phi));
		RADIALPTY2 = RADIALPTY1 - int(double(length) * Math::Sin(phi));

		if (Math::Abs(RADIALPTX1 - RADIALPTX2) < 1 && Math::Abs(RADIALPTY1 - RADIALPTY2) < 1)
			return;

		if (RADIALPTX2 < 0 || RADIALPTX2 > IMAGESET[FILELISTINDEX]->Width || RADIALPTY2 < 0 || RADIALPTY2 > IMAGESET[FILELISTINDEX]->Height)
		{
			MessageBox::Show("The end of the radial vector would be outside of the image array bounds at this angle.", "Error...");
			ImageWndwCntxtPlot->ShowDropDown();
			ImageWindowRadialSetAngle->ShowDropDown();
			return;
		}

		SubImageSlideX->Value = RADIALPTX2 + 1;
		SubImageSlideY->Value = RADIALPTY2 + 1;
		SubImageStatsUpD();
		SubImageUpD();
	}
	else
	{
		RADIALPTX2 = XSUBRANGE[SUBIMAGE_HWX];
		RADIALPTY2 = YSUBRANGE[SUBIMAGE_HWY];

		if (Math::Abs(RADIALPTX1 - RADIALPTX2) < 1 && Math::Abs(RADIALPTY1 - RADIALPTY2) < 1)
			return;

		length = (int)Math::Sqrt(double((RADIALPTX1 - RADIALPTX2)*(RADIALPTX1 - RADIALPTX2) + (RADIALPTY1 - RADIALPTY2)*(RADIALPTY1 - RADIALPTY2)));

		phi = JPMath::aTanAbsoluteAngle(double(RADIALPTX2 - RADIALPTX1), -double(RADIALPTY2 - RADIALPTY1));//minus because origin is upper left
		RADIALPLOT_PHI = phi;
	}

	double double_line_length = Math::Sqrt((RADIALPTX1 - RADIALPTX2)*(RADIALPTX1 - RADIALPTX2) + (RADIALPTY1 - RADIALPTY2)*(RADIALPTY1 - RADIALPTY2));

	if (ImageWindowRadialLockSources->Checked)
	{
		int xind, yind;
		double max = JPMath::Max(SUBIMAGE, xind, yind, false);
		array<int, 2>^ coords = JPMath::Find(SUBIMAGE, max, "==", true);
		int x = coords[0, 0] + XSUBRANGE[0];
		int y = coords[0, 1] + YSUBRANGE[0];

		array<double, 2>^ cent = gcnew array<double, 2>(7, 7);
		array<double, 2>^ xcoords = gcnew array<double, 2>(7, 7);// x coords
		array<double, 2>^ ycoords = gcnew array<double, 2>(7, 7);// y coords

		double fcmin = Double::MaxValue;
		if (IMAGESET[FILELISTINDEX]->Image[x - 3, y - 3] < fcmin)
			fcmin = IMAGESET[FILELISTINDEX]->Image[x - 3, y - 3];
		if (IMAGESET[FILELISTINDEX]->Image[x - 3, y + 3] < fcmin)
			fcmin = IMAGESET[FILELISTINDEX]->Image[x - 3, y + 3];
		if (IMAGESET[FILELISTINDEX]->Image[x + 3, y - 3] < fcmin)
			fcmin = IMAGESET[FILELISTINDEX]->Image[x + 3, y - 3];
		if (IMAGESET[FILELISTINDEX]->Image[x + 3, y + 3] < fcmin)
			fcmin = IMAGESET[FILELISTINDEX]->Image[x + 3, y + 3];

		for (int i = -3; i < 4; i++)
			for (int j = -3; j < 4; j++)
			{
				cent[i + 3, j + 3] = IMAGESET[FILELISTINDEX]->Image[x + i, y + j] - fcmin;
				xcoords[i + 3, j + 3] = double(i);
				ycoords[i + 3, j + 3] = double(j);
			}

		double energy = JPMath::Sum(cent, false);
		RADIALPTX2_CENT = JPMath::Sum(JPMath::MatrixMultMatrix(cent, xcoords, false), false) / energy + double(x);
		RADIALPTY2_CENT = JPMath::Sum(JPMath::MatrixMultMatrix(cent, ycoords, false), false) / energy + double(y);

		double_line_length = Math::Sqrt((RADIALPTX1_CENT - RADIALPTX2_CENT)*(RADIALPTX1_CENT - RADIALPTX2_CENT) + (RADIALPTY1_CENT - RADIALPTY2_CENT)*(RADIALPTY1_CENT - RADIALPTY2_CENT));
	}

	int bin = SUBIMAGE_HWX*2 + 1;
	if (length <= bin)
		length = bin + 1;

	double ptx1 = (double)RADIALPTX1 - double(bin - 1) / 2 * Math::Cos(phi);
	double pty1 = (double)RADIALPTY1 + double(bin - 1) / 2 * Math::Sin(phi);
	double ptx2 = (double)RADIALPTX2 + double(bin - 1) / 2 * Math::Cos(phi);
	double pty2 = (double)RADIALPTY2 - double(bin - 1) / 2 * Math::Sin(phi);

	RADIALLINEBOXPOINTS[0] = Point(int(xsc * (ptx1 + (double)SUBIMAGE_HWY * Math::Cos(phi + Math::PI / 2))), int(ysc * (pty1 - (double)SUBIMAGE_HWY * Math::Sin(phi + Math::PI / 2))));
	RADIALLINEBOXPOINTS[1] = Point(int(xsc * (ptx1 + (double)SUBIMAGE_HWY * Math::Cos(phi - Math::PI / 2))), int(ysc * (pty1 - (double)SUBIMAGE_HWY * Math::Sin(phi - Math::PI / 2))));
	RADIALLINEBOXPOINTS[2] = Point(int(xsc * (ptx2 + (double)SUBIMAGE_HWY * Math::Cos(phi - Math::PI / 2))), int(ysc * (pty2 - (double)SUBIMAGE_HWY * Math::Sin(phi - Math::PI / 2))));
	RADIALLINEBOXPOINTS[3] = Point(int(xsc * (ptx2 + (double)SUBIMAGE_HWY * Math::Cos(phi + Math::PI / 2))), int(ysc * (pty2 - (double)SUBIMAGE_HWY * Math::Sin(phi + Math::PI / 2))));

	if (RADIALPLOT_SETPHI)
	{
		RADIALPLOT_SETPHI = false;
		ImageWindow->Refresh();
	}

	array<bool, 2>^ touched_array = gcnew array<bool, 2>(IMAGESET[FILELISTINDEX]->Width, IMAGESET[FILELISTINDEX]->Height);//check for repeated values
	ArrayList^ rpixlist_unique = gcnew ArrayList();
	ArrayList^ vpixlist_unique = gcnew ArrayList();

	if (SUBIMAGE_HWY > 0)//greater than a line
	{
		//scan at 1/2 pix resolution to help avoid pixel skips - hence * 2 in the loop and /2 in the x,y equation
		for (int i = 0; i < (SUBIMAGE_HWY * 2 + 1) * 2; i++)
			for (int j = 0; j < length * 2; j++)
			{
				int x = int(ptx1 + (double(SUBIMAGE_HWY) - double(i) / 2) * Math::Cos(phi + Math::PI / 2) + double(j) / 2 * Math::Cos(phi));
				int y = int(pty1 - (double(SUBIMAGE_HWY) - double(i) / 2) * Math::Sin(phi + Math::PI / 2) - double(j) / 2 * Math::Sin(phi));//minus because origin is upper left

				//check for repeated values
				if (touched_array[x, y])
					continue;

				touched_array[x, y] = true;

				double r = Math::Sqrt((double(x) - ptx1)*(double(x) - ptx1) + (double(y) - pty1)*(double(y) - pty1));
				double v = IMAGESET[FILELISTINDEX]->Image[x, y];

				rpixlist_unique->Add(r);
				vpixlist_unique->Add(v);

				//IMAGESET[FILELISTINDEX][x, y] = 1;
			}
	}
	else//else a line
	{
		//scan at 1/4 pix resolution to help get more complete pixel-line intersects, hence * 4 in the loop and / 4 in the x,y equation
		for (int j = 0; j < length * 4; j++)
		{
			int x = int(ptx1 + double(j) / 4 * Math::Cos(phi));
			int y = int(pty1 - double(j) / 4 * Math::Sin(phi));//minus because origin is upper left

			//check for repeated values
			if (touched_array[x, y])
				continue;

			touched_array[x, y] = true;		

			double r = Math::Sqrt(double((x - RADIALPTX1)*(x - RADIALPTX1) + (y - RADIALPTY1)*(y - RADIALPTY1)));
			double v = IMAGESET[FILELISTINDEX]->Image[x, y];

			rpixlist_unique->Add(r);
			vpixlist_unique->Add(v);

			//IMAGESET[FILELISTINDEX][x, y] = 1;
		}
	}
	//ImageUpD(IMAGESET[FILELISTINDEX]->Image);

	//ImageWndwPlotRadialVector->Checked = false;

	array<double>^ r_unique = gcnew array<double>(rpixlist_unique->Count);
	array<double>^ v_unique = gcnew array<double>(rpixlist_unique->Count);
	for (int q = 0; q < r_unique->Length; q++)
	{
		r_unique[q] = (double)rpixlist_unique[q];
		v_unique[q] = (double)vpixlist_unique[q];
	}

	Array::Sort(r_unique, v_unique);

	//now need to bin by bin size
	int Nbins = length / bin;
	ArrayList^ r_binnedlist = gcnew ArrayList();
	ArrayList^ v_binnedlist = gcnew ArrayList();
	ArrayList^ p_binnedlist = gcnew ArrayList();

	int c = 0, badbins = 0;
	double dum = 0;
	int post = bin;
	for (int i = 0; i < Nbins; i++)
	{
		if (c == r_unique->Length)
			break;

		r_binnedlist->Add(dum);
		v_binnedlist->Add(dum);
		p_binnedlist->Add(dum);

		double bin_normalization = 0;
		while (r_unique[c] < post)
		{
			r_binnedlist[i - badbins] = double(r_binnedlist[i - badbins]) + r_unique[c];
			v_binnedlist[i - badbins] = double(v_binnedlist[i - badbins]) + v_unique[c];
			c++;
			bin_normalization++;

			if (c == r_unique->Length)
				break;
		}
		//need to know if there were no values at this r bin; if there weren't, then such r bin doesn't exist as a pixel...should be removed...?
		if (bin_normalization >= 1)
		{
			r_binnedlist[i - badbins] = double(r_binnedlist[i - badbins]) / bin_normalization;
			v_binnedlist[i - badbins] = double(v_binnedlist[i - badbins]) / bin_normalization;//v per pixel
			p_binnedlist[i - badbins] = bin_normalization;
		}
		else
		{
			r_binnedlist->RemoveAt(i - badbins);
			v_binnedlist->RemoveAt(i - badbins);
			p_binnedlist->RemoveAt(i - badbins);
			badbins++;
		}
		post = (i + 2) * bin;
	}

	array<double>^ r_binned = gcnew array<double>(r_binnedlist->Count);
	array<double>^ v_binned = gcnew array<double>(r_binnedlist->Count);
	array<double>^ p_binned = gcnew array<double>(r_binnedlist->Count);
	for (int q = 0; q < r_binned->Length; q++)
	{
		r_binned[q] = (double)r_binnedlist[q];
		v_binned[q] = (double)v_binnedlist[q];
		p_binned[q] = (double)p_binnedlist[q];
	}

	RADIALPLOT_R = r_binned;
	RADIALPLOT_V = v_binned;
	RADIALPLOT_P = p_binned;

	double max, min, mean, med, std;
	try
	{
		JPMath::MinMax(v_binned, min, max, false);
		mean = JPMath::Mean(v_binned, false);
		med = JPMath::Median(v_binned);
		std = JPMath::Stdv(v_binned, false);
	}
	catch (...) {}

	String^ title = "Line: Length = " + double_line_length.ToString("N2") + "; Theta = " + (phi*180/Math::PI).ToString("N2") + ";  Min = " + min.ToString("G5") + "; Max = " + max.ToString("G5") + "; Mean = " + mean.ToString("G5") + "; Median = " + med.ToString("G5") + "; Stdv = " + std.ToString("G5");
	RADIALLINE_PLOT->PlotLine(r_binned, v_binned, "Average Radial Bin Distance", "Average Radial Bin Value", title, ::DataVisualization::Charting::SeriesChartType::FastLine, "Radial");
}

void Form1::ImageWndwPlotRadialVector_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (ImageWndwPlotRadialVector->Checked)
	{
		PLOTRADIALLINE = true;
		IWLCK = !IWLCK;

		RADIALPTX1 = XSUBRANGE[SUBIMAGE_HWX];
		RADIALPTY1 = YSUBRANGE[SUBIMAGE_HWY];

		RADIALPTX1_CENT = double(RADIALPTX1);
		RADIALPTY1_CENT = double(RADIALPTY1);

		//do this in case line length by source centroids is needed later
		{
			int xind, yind;
			double max = JPMath::Max(SUBIMAGE, xind, yind, false);
			array<int, 2>^ coords = JPMath::Find(SUBIMAGE, max, "==", false);
			int x = coords[0, 0] + XSUBRANGE[0];
			int y = coords[0, 1] + YSUBRANGE[0];
			
			array<double, 2>^ cent = gcnew array<double, 2>(7, 7);
			array<double, 2>^ xcoords = gcnew array<double, 2>(7, 7);// x coords
			array<double, 2>^ ycoords = gcnew array<double, 2>(7, 7);// y coords

			double fcmin = Double::MaxValue;
			if (IMAGESET[FILELISTINDEX]->Image[x - 3, y - 3] < fcmin)
				fcmin = IMAGESET[FILELISTINDEX]->Image[x - 3, y - 3];
			if (IMAGESET[FILELISTINDEX]->Image[x - 3, y + 3] < fcmin)
				fcmin = IMAGESET[FILELISTINDEX]->Image[x - 3, y + 3];
			if (IMAGESET[FILELISTINDEX]->Image[x + 3, y - 3] < fcmin)
				fcmin = IMAGESET[FILELISTINDEX]->Image[x + 3, y - 3];
			if (IMAGESET[FILELISTINDEX]->Image[x + 3, y + 3] < fcmin)
				fcmin = IMAGESET[FILELISTINDEX]->Image[x + 3, y + 3];

			for (int i = -3; i < 4; i++)
				for (int j = -3; j < 4; j++)
				{
					cent[i + 3, j + 3] = IMAGESET[FILELISTINDEX]->Image[x + i, y + j] - fcmin;
					xcoords[i + 3, j + 3] = double(i);
					ycoords[i + 3, j + 3] = double(j);
				}

			double energy = JPMath::Sum(cent, false);
			RADIALPTX1_CENT = JPMath::Sum(JPMath::MatrixMultMatrix(cent, xcoords, false), false) / energy + double(x);
			RADIALPTY1_CENT = JPMath::Sum(JPMath::MatrixMultMatrix(cent, ycoords, false), false) / energy + double(y);
		}

		RADIALLINE_PLOT = gcnew JPPlot();
		RADIALLINE_PLOT->Text = "Radial Line Plot";
		RADIALLINE_PLOT->JPPlotMainMenu->Visible = true;
		RADIALLINE_PLOT->Show();
		RADIALLINE_PLOTUpD();

		ImageWindowSaveRadialVector->Enabled = true;
		ImageWindowRadialSetAngle->Enabled = true;
		ImageWindowRadialLockSources->Enabled = true;
	}
	else
	{
		ImageWindowSaveRadialVector->Enabled = false;
		ImageWindowRadialSetAngle->Enabled = false;
		ImageWindowRadialLockSources->Enabled = false;
		PLOTRADIALLINE = false;
		ImageWindow->Refresh();
	}
}

void Form1::ImageWindowSaveRadialVector_Click(System::Object^  sender, System::EventArgs^  e)
{
	FileStream^ fs;
	StreamWriter^ sw;
	String^ line;

	::SaveFileDialog^ sfd = gcnew ::SaveFileDialog();
	sfd->Filter = "Tab Delimited Text file (*.txt)|*.txt";
	if (RADIALPLOT_PHI == -720)//from radial profile
		sfd->FileName = IMAGESET[FILELISTINDEX]->FileName->Substring(0, IMAGESET[FILELISTINDEX]->FileName->LastIndexOf(".")) + "_RadialProfile";
	else
		sfd->FileName = IMAGESET[FILELISTINDEX]->FileName->Substring(0, IMAGESET[FILELISTINDEX]->FileName->LastIndexOf(".")) + "_RadialLine_" + (180/Math::PI*RADIALPLOT_PHI).ToString("N0");

	if (sfd->ShowDialog() == ::DialogResult::Cancel)
		return;

	fs = gcnew FileStream(sfd->FileName, System::IO::FileMode::Create, FileAccess::Write);
	sw = gcnew StreamWriter(fs);

	line = "Average Radial Bin Distance" + "	" + "Average Value of Radial Bin" + "	" + "N-Pixels in Radial Bin";
	sw->WriteLine(line);
	for (int i = 0; i < RADIALPLOT_R->Length; i++)
	{
		line = RADIALPLOT_R[i].ToString() + "	" + RADIALPLOT_V[i].ToString() + "	" + RADIALPLOT_P[i].ToString();
		sw->WriteLine(line);
	}

	sw->Close();
	fs->Close();
}

void Form1::ImageWindowRadialAngleTxt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		if (ImageWindowRadialAngleTxt->Text == "")
			return;

		Convert::ToDouble(ImageWindowRadialAngleTxt->Text);
	}
	catch (...)
	{
		ImageWindowRadialAngleTxt->Text = "0";
	}
}

void Form1::ImageWindowRadialAngleTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyCode == ::Keys::Enter)
	{
		RADIALPLOT_PHI = ::Convert::ToDouble(ImageWindowRadialAngleTxt->Text)*::Math::PI/180;
		RADIALPLOT_SETPHI = true;
		ImageWndwCntxtPlot->ShowDropDown();
		ImageWindowRadialSetAngle->ShowDropDown();
		RADIALLINE_PLOTUpD();
	}
}

void Form1::ImageWindowRadialSetAngle_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindowRadialAngleTxt->Text = (RADIALPLOT_PHI * 180 / Math::PI).ToString("N2");
}

void Form1::ImageWndwCntxtPlotRow_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!ImageWndwCntxtPlotRow->Checked)
	{
		if (!ImageWndwCntxtPlotCol->Checked)
			ShowCrosshair->Checked = false;
		ROWplot->Close();
		return;
	}

	if (ROWplot->IsDisposed)
	{
		ROWplot = gcnew JPPlot();
		ROWplot->Text = "Row Plot";
		ROWplot->JPPlotMainMenu->Visible = true;
	}

	ShowCrosshair->Checked = true;
	ROWplotUpD(true);
}

void Form1::ROWplotUpD(bool show_contxt)
{
	if (ROWplot->IsDisposed)
	{
		ImageWndwCntxtPlotRow->PerformClick();
		return;
	}

	if (ImageWndwCntxtPlotRowSubOnly->Checked)
	{
		XSliceX = gcnew array<double>(XSUBRANGE->Length);
		XSliceY = gcnew array<double>(XSUBRANGE->Length);
		for (int i = 0; i < XSliceX->Length; i++)
		{
			XSliceX[i] = (double)(XSUBRANGE[i]+1);
			XSliceY[i] = IMAGESET[FILELISTINDEX]->Image[XSUBRANGE[i],PRVYPOS_CURSOR];
		}
	}
	else
	{
		XSliceX = gcnew array<double>(IMAGESET[FILELISTINDEX]->Width);
		XSliceY = gcnew array<double>(IMAGESET[FILELISTINDEX]->Width);
		for (int i = 0; i < XSliceX->Length; i++)
		{
			XSliceX[i] = (double)(i+1);
			XSliceY[i] = IMAGESET[FILELISTINDEX]->Image[i,PRVYPOS_CURSOR];
		}
	}

	double min, max;
	JPMath::MinMax(XSliceY, min, max, false);
	double mean = JPMath::Mean(XSliceY, true);
	double med = JPMath::Median(XSliceY);
	double std = JPMath::Stdv(XSliceY, false);

	String^ title = "Row: " + (PRVYPOS_CURSOR+1).ToString() + "; Min = " + min.ToString("G5") + "; Max = " + max.ToString("G5") + "; Mean = " + mean.ToString("G5") + "; Median = " + med.ToString("G5") + "; Stdv = " + std.ToString("G5");
	Charting::SeriesChartType ct = Charting::SeriesChartType::StepLine;
	if (XSliceX->Length > 32768)
		ct = Charting::SeriesChartType::FastLine;
	ROWplot->PlotLine(XSliceX,XSliceY,"Column Number","Row Values",title,ct, "Row");

	if (show_contxt)
	{
		Form1::BringToFront();
		ImageWindowCntxt->Show();
		ImageWndwCntxtPlot->ShowDropDown();
	}
}

void Form1::ImageWndwCntxtPlotCol_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!ImageWndwCntxtPlotCol->Checked)
	{
		if (!ImageWndwCntxtPlotRow->Checked)
			ShowCrosshair->Checked = false;
		COLplot->Close();
		return;
	}

	if (COLplot->IsDisposed)
	{
		COLplot = gcnew JPPlot();
		COLplot->Text = "Column Plot";
		COLplot->JPPlotMainMenu->Visible = true;
	}

	ShowCrosshair->Checked = true;
	COLplotUpD(true);
}

void Form1::COLplotUpD(bool show_contxt)
{
	if (COLplot->IsDisposed)
	{
		ImageWndwCntxtPlotCol->PerformClick();
		return;
	}

	if (ImageWndwCntxtPlotColSubOnly->Checked)
	{
		YSliceX = gcnew array<double>(YSUBRANGE->Length);
		YSliceY = gcnew array<double>(YSUBRANGE->Length);
		for (int i = 0; i < YSliceX->Length; i++)
		{
			YSliceX[i] = double(YSUBRANGE[i]+1);
			YSliceY[i] = IMAGESET[FILELISTINDEX]->Image[PRVXPOS_CURSOR,YSUBRANGE[i]];
		}
	}
	else
	{
		YSliceX = gcnew array<double>(IMAGESET[FILELISTINDEX]->Height);
		YSliceY = gcnew array<double>(IMAGESET[FILELISTINDEX]->Height);
		for (int i = 0; i < YSliceX->Length; i++)
		{
			YSliceX[i] = (double)(i+1);
			YSliceY[i] = IMAGESET[FILELISTINDEX]->Image[PRVXPOS_CURSOR,i];
		}
	}

	double min, max;
	JPMath::MinMax(XSliceY, min, max, false);
	double mean = JPMath::Mean(YSliceY, true);
	double med = JPMath::Median(YSliceY);
	double std = JPMath::Stdv(YSliceY, false);

	String^ title = "Column: " + (PRVXPOS_CURSOR+1).ToString() + "; Min = " + min.ToString("G5") + "; Max = " + max.ToString("G5") + "; Mean = " + mean.ToString("G5") + "; Median = " + med.ToString("G5") + "; Stdv = " + std.ToString("G5");
	Charting::SeriesChartType ct = Charting::SeriesChartType::StepLine;
	if (YSliceX->Length > 32768)
		ct = Charting::SeriesChartType::FastLine;
	COLplot->PlotLine(YSliceX,YSliceY,"Row Number","Column Values",title,ct, "Column");

	if (show_contxt)
	{
		Form1::BringToFront();
		ImageWindowCntxt->Show();
		ImageWndwCntxtPlot->ShowDropDown();
	}
}

void Form1::MarkCoordSave_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (MARKCOORDS == nullptr)
		return;

	SaveFileDialog^ fsd = gcnew SaveFileDialog();
	fsd->Filter = "FITS|*.fits;*.fit;*.fts";

	if (fsd->ShowDialog() == ::DialogResult::Cancel)
		return;

	double xsc = (double(ImageWindow->Size.Width) / (double)IMAGESET[FILELISTINDEX]->Width);
	double ysc = (double(ImageWindow->Size.Height) / (double)IMAGESET[FILELISTINDEX]->Height);
	array<double, 2>^ rects = gcnew array<double, 2>(2, MARKCOORDRECTS->Length);
	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
	{
		rects[0, i] = MARKCOORDRECTDPTS[i]->X;//(MARKCOORDS[0, i] + 1) * xsc - 6;
		rects[1, i] = MARKCOORDRECTDPTS[i]->Y;//(MARKCOORDS[1, i] + 1) * ysc - 6;
	}
	JPFITS::FITSImage^ ff = gcnew FITSImage(fsd->FileName, rects, false, false);
	ff->AddKey("RECWIDTH", MARKCOORDRECTS[0].Width.ToString(), "", -1);
	ff->AddKey("RECHEIGT", MARKCOORDRECTS[0].Height.ToString(), "", -1);
	ff->WriteImage(TypeCode::Double, false);
}

void Form1::MarkCoordLoad_Click(System::Object^  sender, System::EventArgs^  e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	//ofd->InitialDirectory = 
	//ofd->Filter = 
	ofd->Multiselect = false;//possibly true for getting/doing multi-regions

	if (ofd->ShowDialog() == ::DialogResult::Cancel)
		return;

	FITSImage^ recs = gcnew FITSImage(ofd->FileName, nullptr, true, true, false, false);
	MARKCOORDRECTDPTS = gcnew array<JPMath::PointD^>(recs->Height);
	MARKCOORDRECTS = gcnew array<Rectangle>(recs->Height);
	MARKCOORDS = gcnew array<double, 2>(2, recs->Height);

	double xsc = (double(ImageWindow->Size.Width) / (double)IMAGESET[FILELISTINDEX]->Width);
	double ysc = (double(ImageWindow->Size.Height) / (double)IMAGESET[FILELISTINDEX]->Height);
	
	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
	{
		MARKCOORDRECTDPTS[i] = gcnew JPMath::PointD(recs[0, i], recs[1, i], IMAGESET[FILELISTINDEX]->Image[(int)recs[0, i], (int)recs[1, i]]);
		MARKCOORDS[0, i] = (recs[0, i] + 6) / xsc - 1.0;
		MARKCOORDS[1, i] = (recs[1, i] + 6) / ysc - 1.0;
	}
	MAKEMARKCOORDRECTS();
	
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::ImageWndwCntxtMarkCoord_Click(System::Object^  sender, System::EventArgs^  e)
{
	ImageWindowCntxt->Close();

	double xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	double ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);

	if (MARKCOORDRECTS == nullptr)
	{
		MARKCOORDS = gcnew array<double, 2>(0, 0);
		MARKCOORDRECTS = gcnew array<Rectangle>(0);
		MARKCOORDRECTDPTS = gcnew array<JPMath::PointD^>(0);
	}

	array<JPMath::PointD^>^ temprectdpts = gcnew array<JPMath::PointD^>(MARKCOORDRECTS->Length + 1);
	array<Rectangle, 1>^ temprects = gcnew array<Rectangle, 1>(MARKCOORDRECTS->Length + 1);
	array<double, 2>^ tempcoords = gcnew array<double, 2>(2, MARKCOORDRECTS->Length + 1);

	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
	{
		temprectdpts[i] = MARKCOORDRECTDPTS[i];
		temprects[i] = MARKCOORDRECTS[i];
		tempcoords[0, i] = MARKCOORDS[0, i];
		tempcoords[1, i] = MARKCOORDS[1, i];
	}

	int x, y;
	JPMath::Max(SUBIMAGE, x, y, false);
	double x_cent, y_cent;
	array<int>^ xdata = gcnew array<int>(7);
	array<int>^ ydata = gcnew array<int>(7);
	array<double, 2>^ subim = IMAGESET[FILELISTINDEX]->GetSubImage(x + XSUBRANGE[0], y + YSUBRANGE[0], 3, 3, xdata, ydata);
	SourceExtractor::Centroid(xdata, ydata, subim, x_cent, y_cent);

	temprectdpts[temprects->Length - 1] = gcnew JPMath::PointD((x_cent + 1) * xsc - 6, (y_cent + 1) * ysc - 6, IMAGESET[FILELISTINDEX]->Image[(int)x_cent, (int)y_cent]);
	temprects[temprects->Length - 1] = Rectangle(int((x_cent + 1) * xsc - 6), int((y_cent + 1) * ysc - 6), 13, 13);
	tempcoords[0, temprects->Length - 1] = x_cent;
	tempcoords[1, temprects->Length - 1] = y_cent;

	MARKCOORDRECTDPTS = temprectdpts;
	MARKCOORDRECTS = temprects;
	MARKCOORDS = tempcoords;

	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::SubImCntxtMarkCoord_Click(System::Object^  sender, System::EventArgs^  e)
{
	SubImageCntxt->Close();
	ImageWndwCntxtMarkCoord->PerformClick();
}

void Form1::SubImMarkCoordAsCentroidChck_Click(System::Object^  sender, System::EventArgs^  e)
{
	SubImageCntxt->Show();
	SubImCntxtMarkCoord->ShowDropDown();
}

void Form1::MarkCoordClear_Click(System::Object^  sender, System::EventArgs^  e)
{
	MARKCOORDRECTS = nullptr;
	MARKCOORDS = nullptr;
	MARKCOORDRECTDPTS = nullptr;
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::SubImMarkCoordClear_Click(System::Object^  sender, System::EventArgs^  e)
{
	MarkCoordClear->PerformClick();
}

void Form1::SubImMarkCoordClearContained_Click(System::Object^  sender, System::EventArgs^  e)
{
	array<bool>^ inside = gcnew array<bool>(MARKCOORDRECTS->Length);
	int n = 0;
	for (int i = 0; i < inside->Length; i++)
		if (MARKCOORDS[0, i] > XSUBRANGE[0] && MARKCOORDS[0, i] < XSUBRANGE[XSUBRANGE->Length - 1] && MARKCOORDS[1, i] > YSUBRANGE[0] && MARKCOORDS[1, i] < YSUBRANGE[YSUBRANGE->Length - 1])
		{
			inside[i] = true;
			n++;
		}

	n = inside->Length - n;

	array<double, 2>^ temp = gcnew array<double, 2>(2, n);
	n = 0;
	for (int i = 0; i < MARKCOORDRECTS->Length; i++)
		if (!inside[i])
		{
			temp[0, n] = MARKCOORDS[0, i];
			temp[1, n] = MARKCOORDS[1, i];
			n++;
		}
	MARKCOORDS = gcnew array<double, 2>(2, n);
	MARKCOORDRECTS = gcnew array<Rectangle>(n);
	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	for (int i = 0; i < n; i++)
	{
		MARKCOORDS[0, i] = temp[0, i];
		MARKCOORDS[1, i] = temp[1, i];
		MARKCOORDRECTS[i] = Rectangle(int((float(MARKCOORDS[0, i])*xsc) - 6), int((float(MARKCOORDS[1, i])*ysc) - 6), 12, 12);
	}

	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::SubImMarkCoordContainedPSE_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (PSES == nullptr)
		return;

	if (PSES[PSESINDEX]->N_Sources == 0)
		return;

	ArrayList^ contained = gcnew ArrayList();

	for (int i = 0; i < PSES[PSESINDEX]->N_Sources; i++)
		if (PSES[PSESINDEX]->Centroids_X[i] > XSUBRANGE[0] && PSES[PSESINDEX]->Centroids_X[i] < XSUBRANGE[SUBIMAGE_HWX * 2] && PSES[PSESINDEX]->Centroids_Y[i] > YSUBRANGE[0] && PSES[PSESINDEX]->Centroids_Y[i] < YSUBRANGE[SUBIMAGE_HWY * 2])
		{
			contained->Add(PSES[PSESINDEX]->Centroids_X[i]);
			contained->Add(PSES[PSESINDEX]->Centroids_Y[i]);
		}

	if (contained->Count == 0)
		return;

	float xsc = (float(ImageWindow->Size.Width) / (float)IMAGESET[FILELISTINDEX]->Width);
	float ysc = (float(ImageWindow->Size.Height) / (float)IMAGESET[FILELISTINDEX]->Height);
	MARKCOORDRECTS = gcnew array<Rectangle>(contained->Count / 2);
	MARKCOORDS = gcnew array<double, 2>(2, contained->Count / 2);
	double x_cent, y_cent;
	for (int i = 0; i < contained->Count / 2; i++)
	{
		x_cent = Convert::ToDouble(contained[i * 2]);
		y_cent = Convert::ToDouble(contained[i * 2 + 1]);
		MARKCOORDRECTS[i] = Rectangle(int((float(x_cent + 1))*xsc - 6), int((float(y_cent + 1))*ysc - 6), 12, 12);
		MARKCOORDS[0, i] = x_cent;
		MARKCOORDS[1, i] = y_cent;
	}
	ImageWindow->Refresh();
	SubImageWindow->Refresh();
}

void Form1::SubImCntxtCopyPixPoord_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ str;
	if (WCSRADecShowChck->Checked)
		str = (XPOS_CURSOR + 1).ToString() + "	" + XPOS_CURSOR_RADEG.ToString() + "	" + XPOS_CURSOR_RAHMS + "	" + (YPOS_CURSOR + 1).ToString() + "	" + YPOS_CURSOR_DECDEG.ToString() + "	" + YPOS_CURSOR_DECDMS;
	else
		str = (XPOS_CURSOR + 1).ToString() + "	" + (YPOS_CURSOR + 1).ToString();

	::Clipboard::SetText(str);
}

void Form1::SubImCntxtCopyCentroidCoord_Click(System::Object^  sender, System::EventArgs^  e)
{
	double xcent, ycent;
	SourceExtractor::Centroid(XSUBRANGE, YSUBRANGE, SUBIMAGE, xcent, ycent);
	
	String^ str;
	if (WCSRADecShowChck->Checked)
	{
		double a, d;
		String^ asx;
		String^ dsx;
		WCS->Get_Coordinate(xcent, ycent, true, "TAN", a, d, asx, dsx);
		XPOS_CURSOR_RADEG = a;
		YPOS_CURSOR_DECDEG = d;
		XPOS_CURSOR_RAHMS = asx;
		YPOS_CURSOR_DECDMS = dsx;

		str = (xcent).ToString() + "	" + XPOS_CURSOR_RADEG.ToString() + "	" + XPOS_CURSOR_RAHMS + "	" + (ycent).ToString() + "	" + YPOS_CURSOR_DECDEG.ToString() + "	" + YPOS_CURSOR_DECDMS;
	}
	else
	{
		str = (xcent).ToString() + "	" + (ycent).ToString();
	}

	::Clipboard::SetText(str);

	MARKCOORDRECTS = gcnew array<Rectangle>(1);
	MARKCOORDS = gcnew array<double, 2>(2, 1);
	MARKCOORDS[0, 0] = xcent;
	MARKCOORDS[1, 0] = ycent;
	SubImageWindow->Refresh();
	MARKCOORDRECTS = nullptr;
	MARKCOORDS = nullptr;
}

void Form1::SubImCntxtCopyImage_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Drawing::Bitmap^ bmp1 = gcnew System::Drawing::Bitmap(SubImageWindow->Width, SubImageWindow->Height);
	SubImageWindow->DrawToBitmap(bmp1, SubImageWindow->DisplayRectangle);
	::Clipboard::SetImage(bmp1);
}

void Form1::SubImCntxtGoToPixel_DropDownOpened(System::Object^  sender, System::EventArgs^  e)
{
	SubImCntxtGoToPixXTxt->Text = (XSUBRANGE[SUBIMAGE_HWX] + 1).ToString();
	SubImCntxtGoToPixYTxt->Text = (YSUBRANGE[SUBIMAGE_HWY] + 1).ToString();
}

void Form1::SubImCntxtGoToPixXTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyCode == ::Keys::Enter)
	{
		e->SuppressKeyPress = true;
		int xpix, ypix;

		try
		{
			if (SubImCntxtGoToPixXTxt->Text == "")
				return;

			xpix = Convert::ToInt32(SubImCntxtGoToPixXTxt->Text);
		}
		catch (...)
		{
			SubImCntxtGoToPixXTxt->Text = (XSUBRANGE[SUBIMAGE_HWX] + 1).ToString();
			return;
		}

		try
		{
			if (SubImCntxtGoToPixYTxt->Text == "")
				return;

			ypix = Convert::ToInt32(SubImCntxtGoToPixYTxt->Text);
		}
		catch (...)
		{
			SubImCntxtGoToPixYTxt->Text = (YSUBRANGE[SUBIMAGE_HWY] + 1).ToString();
			return;
		}

		SubImageSlideX->Value = xpix;
		SubImageSlideY->Value = ypix;
		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();
	}
}

void Form1::SubImCntxtGoToPixYTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	SubImCntxtGoToPixXTxt_KeyDown(sender, e);
}

void Form1::SubImCntxtGoToRATxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if (e->KeyCode == ::Keys::Enter)
	{
		e->SuppressKeyPress = true;
		double RA, Dec;

		if (SubImCntxtGoToRATxt->Text->Contains("d"))
		{
			int dind = SubImCntxtGoToRATxt->Text->IndexOf("d");
			String^ strRA = SubImCntxtGoToRATxt->Text->Substring(0, dind);
			String^ strDec = SubImCntxtGoToRATxt->Text->Substring(dind + 1);
			strDec = strDec->Substring(0, strDec->Length - 1);

			RA = Convert::ToDouble(strRA);
			Dec = Convert::ToDouble(strDec);

			SubImCntxtGoToRATxt->Text = strRA;
			SubImCntxtGoToDecTxt->Text = strDec;
		}
		else
		{
			try
			{
				if (SubImCntxtGoToRATxt->Text == "")
					return;

				RA = Convert::ToDouble(SubImCntxtGoToRATxt->Text);
			}
			catch (...)
			{
				SubImCntxtGoToRATxt->Text = "";
				return;
			}

			try
			{
				if (SubImCntxtGoToDecTxt->Text == "")
					return;

				Dec = Convert::ToDouble(SubImCntxtGoToDecTxt->Text);
			}
			catch (...)
			{
				SubImCntxtGoToDecTxt->Text = "";
				return;
			}
		}

		if (IMAGESET[FILELISTINDEX]->GetKeyValue("CD1_1") == "")
		{
			MessageBox::Show("CD matrix for WCS not found in current image header.  Can not transform RA-Dec to x-y...", "Error...");
			return;
		}

		WCS = gcnew JPFITS::WorldCoordinateSolution();
		WCS->Get_WCS(IMAGESET[FILELISTINDEX]);
		double xpix, ypix;
		WCS->Get_Pixel(RA, Dec, "TAN", xpix, ypix, true);

		SubImageSlideX->Value = (int)xpix + 1;
		SubImageSlideY->Value = (int)ypix + 1;
		SubImageStatsUpD();
		SubImageUpD();
		ImageWindow->Refresh();
	}
}

void Form1::SubImCntxtGoToDecTxt_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	SubImCntxtGoToRATxt_KeyDown(sender, e);
}

void Form1::ImageWindow_SizeChanged(System::Object^  sender, System::EventArgs^  e)
{
	/*if (ImageWindow->Size.Width > ImageWindow->Size.Height)
		ImageWindow->Size.Width = ImageWindow->Size.Height;*/
}

void Form1::ImageWindowCntxtSquare_Click(System::Object^  sender, System::EventArgs^  e)
{
	/*ImageWindow->Location.X += ImageWindow->Size.Width - ImageWindow->Size.Height;
	ImageWindow->Refresh();
	Form1::Refresh();*/
}

void Form1::WCSClearPlotSolutionPtsBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	MarkCoordClear->PerformClick();
}

void Form1::Form1_Shown(System::Object^  sender, System::EventArgs^  e)
{
	if (SubImageSlideY->Right + SubImagePanel->Width < this->Right - 20)
	{
		int diff = this->Right - 20 - SubImageSlideY->Right - SubImagePanel->Width;
		SubImageWindow->Location = ::Drawing::Point(SubImageWindow->Location.X, SubImageWindow->Location.Y - diff);
		SubImageWindow->Size = ::Drawing::Size(SubImageWindow->Size.Width + diff, SubImageWindow->Size.Height + diff);

		SubImageSlideX->Location = ::Drawing::Point(SubImageWindow->Location.X, SubImageWindow->Location.Y - SubImageSlideX->Height);
		SubImageSlideX->Width = SubImageWindow->Width;

		SubImageSlideY->Location = ::Drawing::Point(SubImageWindow->Right, SubImageWindow->Location.Y);
		SubImageSlideY->Height = SubImageWindow->Height;

		SubImagePanel->Location = ::Drawing::Point(SubImageSlideY->Right + 10, SubImageWindow->Location.Y);
	}

	//if(EXTENSIONTABLEFIRSTLOAD)
		//this->SendToBack();
}

