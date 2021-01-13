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
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::DataVisualization;
using namespace System::Data;
using namespace System::Drawing;
using namespace MathWorks::MATLAB::NET::Arrays;
using namespace MathWorks::MATLAB::NET::Utility;


namespace CCDLAB {

	/// <summary>
	/// Summary for JPPlot
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class JPPlot : public System::Windows::Forms::Form
	{
	public:
		JPPlot(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~JPPlot()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::Windows::Forms::MenuStrip^  JPPlotMainMenu;
	protected: 



	private: System::Windows::Forms::ToolStripMenuItem^  JPPlotMenuItem_Fit;
	public: System::Windows::Forms::ToolStripMenuItem^  FitMenuGaussian;
	public: System::Windows::Forms::ToolStripMenuItem^  FitMenuMoffat;
	private: System::Windows::Forms::ToolStripMenuItem^  pixelScalearcsecpixelToolStripMenuItem;
	public: System::Windows::Forms::ToolStripTextBox^  PixelScaleTxtBox;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	public: CustomChart::MyChart^  plotchart1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ToolStripMenuItem^  FitMenuPlotResidualsChck;
	public:
	private:

	private: System::ComponentModel::IContainer^  components;





	public: 

	public: 


	public: 

	protected: 

	protected: 

	protected: 

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(JPPlot::typeid));
			this->JPPlotMainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->JPPlotMenuItem_Fit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FitMenuGaussian = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FitMenuMoffat = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->pixelScalearcsecpixelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PixelScaleTxtBox = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->plotchart1 = (gcnew CustomChart::MyChart());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->FitMenuPlotResidualsChck = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->JPPlotMainMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->plotchart1))->BeginInit();
			this->SuspendLayout();
			// 
			// JPPlotMainMenu
			// 
			this->JPPlotMainMenu->BackColor = System::Drawing::Color::DarkGray;
			this->JPPlotMainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->JPPlotMenuItem_Fit });
			this->JPPlotMainMenu->Location = System::Drawing::Point(0, 0);
			this->JPPlotMainMenu->Name = L"JPPlotMainMenu";
			this->JPPlotMainMenu->Size = System::Drawing::Size(672, 24);
			this->JPPlotMainMenu->TabIndex = 1;
			this->JPPlotMainMenu->Text = L"menuStrip1";
			this->JPPlotMainMenu->Visible = false;
			// 
			// JPPlotMenuItem_Fit
			// 
			this->JPPlotMenuItem_Fit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->FitMenuGaussian,
					this->FitMenuMoffat, this->FitMenuPlotResidualsChck, this->toolStripSeparator1, this->pixelScalearcsecpixelToolStripMenuItem
			});
			this->JPPlotMenuItem_Fit->Name = L"JPPlotMenuItem_Fit";
			this->JPPlotMenuItem_Fit->Size = System::Drawing::Size(32, 20);
			this->JPPlotMenuItem_Fit->Text = L"Fit";
			this->JPPlotMenuItem_Fit->Click += gcnew System::EventHandler(this, &JPPlot::JPPlotMenuItem_Fit_Click);
			// 
			// FitMenuGaussian
			// 
			this->FitMenuGaussian->Name = L"FitMenuGaussian";
			this->FitMenuGaussian->Size = System::Drawing::Size(201, 22);
			this->FitMenuGaussian->Text = L"Gaussian";
			this->FitMenuGaussian->Click += gcnew System::EventHandler(this, &JPPlot::FitMenuGaussian_Click);
			// 
			// FitMenuMoffat
			// 
			this->FitMenuMoffat->Name = L"FitMenuMoffat";
			this->FitMenuMoffat->Size = System::Drawing::Size(201, 22);
			this->FitMenuMoffat->Text = L"Moffat";
			this->FitMenuMoffat->Click += gcnew System::EventHandler(this, &JPPlot::FitMenuMoffat_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(198, 6);
			// 
			// pixelScalearcsecpixelToolStripMenuItem
			// 
			this->pixelScalearcsecpixelToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->PixelScaleTxtBox });
			this->pixelScalearcsecpixelToolStripMenuItem->Name = L"pixelScalearcsecpixelToolStripMenuItem";
			this->pixelScalearcsecpixelToolStripMenuItem->Size = System::Drawing::Size(201, 22);
			this->pixelScalearcsecpixelToolStripMenuItem->Text = L"Pixel Scale (arcsec/pixel)";
			// 
			// PixelScaleTxtBox
			// 
			this->PixelScaleTxtBox->Name = L"PixelScaleTxtBox";
			this->PixelScaleTxtBox->Size = System::Drawing::Size(100, 23);
			this->PixelScaleTxtBox->Text = L"1";
			this->PixelScaleTxtBox->TextChanged += gcnew System::EventHandler(this, &JPPlot::PixelScaleTxtBox_TextChanged);
			// 
			// plotchart1
			// 
			this->plotchart1->BackColor = System::Drawing::Color::DarkGray;
			this->plotchart1->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::TopBottom;
			this->plotchart1->BackSecondaryColor = System::Drawing::Color::White;
			chartArea1->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->LabelAutoFitStyle = System::Windows::Forms::DataVisualization::Charting::LabelAutoFitStyles::DecreaseFont;
			chartArea1->AxisX->LabelStyle->Format = L"G6";
			chartArea1->AxisX->LabelStyle->TruncatedLabels = true;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::Gray;
			chartArea1->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->MajorTickMark->Interval = 0;
			chartArea1->AxisX->MajorTickMark->IntervalOffset = 0;
			chartArea1->AxisX->MajorTickMark->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Auto;
			chartArea1->AxisX->MajorTickMark->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Auto;
			chartArea1->AxisX->MajorTickMark->Size = 2;
			chartArea1->AxisX->MinorTickMark->Enabled = true;
			chartArea1->AxisX->MinorTickMark->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->AxisX->ScaleView->Zoomable = false;
			chartArea1->AxisX->ScrollBar->Enabled = false;
			chartArea1->AxisX->Title = L"X Axis";
			chartArea1->AxisX2->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea1->AxisX2->IsStartedFromZero = false;
			chartArea1->AxisX2->MajorTickMark->Interval = 0;
			chartArea1->AxisX2->ScrollBar->Enabled = false;
			chartArea1->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea1->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->LabelAutoFitStyle = System::Windows::Forms::DataVisualization::Charting::LabelAutoFitStyles::DecreaseFont;
			chartArea1->AxisY->LabelStyle->Format = L"G5";
			chartArea1->AxisY->LabelStyle->TruncatedLabels = true;
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gray;
			chartArea1->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisY->MajorTickMark->Interval = 0;
			chartArea1->AxisY->MajorTickMark->IntervalOffset = 0;
			chartArea1->AxisY->MajorTickMark->IntervalOffsetType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Auto;
			chartArea1->AxisY->MajorTickMark->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Auto;
			chartArea1->AxisY->MajorTickMark->Size = 2;
			chartArea1->AxisY->MinorTickMark->Enabled = true;
			chartArea1->AxisY->ScaleView->Zoomable = false;
			chartArea1->AxisY->ScrollBar->Enabled = false;
			chartArea1->AxisY->Title = L"Y Axis";
			chartArea1->AxisY2->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea1->AxisY2->IsStartedFromZero = false;
			chartArea1->AxisY2->ScrollBar->Enabled = false;
			chartArea1->BackColor = System::Drawing::Color::White;
			chartArea1->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea1->CursorX->AutoScroll = false;
			chartArea1->CursorX->Interval = 0.001;
			chartArea1->CursorX->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->CursorX->SelectionColor = System::Drawing::Color::LightGreen;
			chartArea1->CursorY->AutoScroll = false;
			chartArea1->CursorY->Interval = 0.001;
			chartArea1->CursorY->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->CursorY->SelectionColor = System::Drawing::Color::LightGreen;
			chartArea1->Name = L"ChartArea1";
			chartArea1->Position->Auto = false;
			chartArea1->Position->Height = 85;
			chartArea1->Position->Width = 85;
			chartArea1->Position->X = 2;
			chartArea1->Position->Y = 12.64803F;
			this->plotchart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->plotchart1->IsSoftShadows = false;
			this->plotchart1->Location = System::Drawing::Point(0, 24);
			this->plotchart1->Name = L"plotchart1";
			series1->BorderColor = System::Drawing::Color::White;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Teal;
			series1->CustomProperties = L"DrawingStyle=Emboss, PointWidth=1";
			series1->MarkerBorderWidth = 0;
			series1->MarkerColor = System::Drawing::Color::Teal;
			series1->Name = L"Series1";
			this->plotchart1->Size = System::Drawing::Size(672, 585);
			this->plotchart1->TabIndex = 0;
			this->plotchart1->Text = L"myChart1";
			title1->DockedToChartArea = L"ChartArea1";
			title1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			title1->IsDockedInsideChartArea = false;
			title1->Name = L"Title1";
			title1->Position->Auto = false;
			title1->Position->Height = 6.828034F;
			title1->Position->Width = 79.9F;
			title1->Position->X = 10;
			title1->Position->Y = 5.819999F;
			title1->Text = L"Title";
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(156, 49);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// FitMenuPlotResidualsChck
			// 
			this->FitMenuPlotResidualsChck->CheckOnClick = true;
			this->FitMenuPlotResidualsChck->Name = L"FitMenuPlotResidualsChck";
			this->FitMenuPlotResidualsChck->Size = System::Drawing::Size(201, 22);
			this->FitMenuPlotResidualsChck->Text = L"Plot Residuals";
			this->FitMenuPlotResidualsChck->Click += gcnew System::EventHandler(this, &JPPlot::FitMenuPlotResidualsChck_Click);
			// 
			// JPPlot
			// 
			this->CancelButton = this->button1;
			this->ClientSize = System::Drawing::Size(672, 609);
			this->Controls->Add(this->plotchart1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->JPPlotMainMenu);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->JPPlotMainMenu;
			this->Name = L"JPPlot";
			this->TopMost = true;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &JPPlot::JPPlot_FormClosing);
			this->Load += gcnew System::EventHandler(this, &JPPlot::JPPlot_Load);
			this->TextChanged += gcnew System::EventHandler(this, &JPPlot::JPPlot_TextChanged);
			this->JPPlotMainMenu->ResumeLayout(false);
			this->JPPlotMainMenu->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->plotchart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


public:

array<double>^ jpplotXDATA;
array<double>^ jpplotYDATA;

JPPlot^ FIT_RESIDUALS_PLOT;


void PlotLine(array<double>^ XData, array<double>^ YData, String^ XTitle, String^ YTitle, String^ ChartTitle, Charting::SeriesChartType ChartStyle, String^ SeriesName);
void AddLine(array<double>^ XData, array<double>^ YData, Charting::SeriesChartType ChartStyle, String^ SeriesName);
//save location and size, use title or something for registry entry identification
private: System::Void JPPlot_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
//apply location and size, use title or something for registry entry identification
private: System::Void JPPlot_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void JPPlot_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void FitMenuGaussian_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FitMenuMoffat_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void PixelScaleTxtBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void JPPlotMenuItem_Fit_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void FitMenuPlotResidualsChck_Click(System::Object^  sender, System::EventArgs^  e);






};
}
