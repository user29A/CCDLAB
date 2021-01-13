#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CCDLAB {

	/// <summary>
	/// Summary for Plot
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Plot : public System::Windows::Forms::Form
	{
	public:
		Plot(void)
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
		~Plot()
		{
			if (components)
			{
				delete components;
			}
		}
	public: ChartFX::WinForms::Chart^  chart1;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			ChartFX::WinForms::SeriesAttributes^  seriesAttributes1 = (gcnew ChartFX::WinForms::SeriesAttributes());
			ChartFX::WinForms::TitleDockable^  titleDockable1 = (gcnew ChartFX::WinForms::TitleDockable());
			this->chart1 = (gcnew ChartFX::WinForms::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			this->chart1->AxisX->Title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->chart1->AxisX->Title->Text = L"X Axis";
			this->chart1->AxisY->ForceZero = false;
			this->chart1->AxisY->LabelsFormat->Format = ChartFX::WinForms::AxisFormat::Number;
			this->chart1->AxisY->Title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->chart1->AxisY->Title->Text = L"YAxis";
			this->chart1->Border = (gcnew ChartFX::WinForms::Adornments::SimpleBorder(ChartFX::WinForms::Adornments::SimpleBorderType::Color, 
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(109)), static_cast<System::Int32>(static_cast<System::Byte>(125)), 
				static_cast<System::Int32>(static_cast<System::Byte>(138)))));
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->LegendBox->Visible = false;
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			this->chart1->RandomData->Series = 1;
			this->chart1->Series->AddRange(gcnew cli::array< ChartFX::WinForms::SeriesAttributes^  >(1) {seriesAttributes1});
			this->chart1->Size = System::Drawing::Size(804, 684);
			this->chart1->TabIndex = 0;
			titleDockable1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			titleDockable1->Text = L"Title";
			this->chart1->Titles->AddRange(gcnew cli::array< ChartFX::WinForms::TitleDockable^  >(1) {titleDockable1});
			this->chart1->ToolBar->Visible = true;
			// 
			// Plot
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(804, 684);
			this->Controls->Add(this->chart1);
			this->Name = L"Plot";
			this->Text = L"Plot";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


public:

void PlotLine(array<double>^ XData, array<double>^ YData, String^ XTitle, String^ YTitle, String^ ChartTitle)
{
	double Xmin, Xmax, Ymin, Ymax;
	int L = XData->Length;

	Xmin = JPMath::Min(XData,true);
	Xmax = JPMath::Max(XData,true);
	Ymin = JPMath::Min(YData,true);
	Ymax = JPMath::Max(YData,true);

	chart1->AxisX->Min = Xmin;
	chart1->AxisX->Max = Xmax;
	chart1->AxisY->Min = Ymin;
	chart1->AxisY->Max = Ymax;

	chart1->AxisX->Title->Text = XTitle;
	chart1->AxisY->Title->Text = YTitle;
	chart1->Titles[0]->Text = ChartTitle;
	chart1->Data->Points = L;

	for (int i = 0; i < L; i++)
	{
		chart1->Data->X[0,i] = XData[i];
		chart1->Data->Y[0,i] = YData[i];
	}
	Plot::Show();
}










	};
}
