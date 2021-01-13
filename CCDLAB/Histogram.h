#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CCDLAB {

	/// <summary>
	/// Summary for Histogram
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Histogram : public System::Windows::Forms::Form
	{
	public:
		Histogram(void)
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
		~Histogram()
		{
			if (components)
			{
				delete components;
			}
		}
	public: ChartFX::WinForms::Chart^  chart1;

	public: 
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Histogram::typeid));
			this->chart1 = (gcnew ChartFX::WinForms::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			this->chart1->AxisX->ForceZero = false;
			this->chart1->AxisX->LabelsFormat->Format = ChartFX::WinForms::AxisFormat::Number;
			this->chart1->AxisX->Max = 0;
			this->chart1->AxisX->Min = 0;
			this->chart1->AxisX->Title->Text = L"Value";
			this->chart1->AxisY->Max = 100;
			this->chart1->AxisY->Min = 0;
			this->chart1->AxisY->Title->Text = L"Count";
			this->chart1->AxisY2->ForceZero = false;
			this->chart1->Border = (gcnew ChartFX::WinForms::Adornments::SimpleBorder(ChartFX::WinForms::Adornments::SimpleBorderType::None, 
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(109)), static_cast<System::Int32>(static_cast<System::Byte>(125)), 
				static_cast<System::Int32>(static_cast<System::Byte>(138)))));
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->LegendBox->Visible = false;
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			this->chart1->RandomData->Series = 1;
			seriesAttributes1->Gallery = ChartFX::WinForms::Gallery::Bar;
			seriesAttributes1->Text = L"";
			seriesAttributes1->Volume = static_cast<System::Int16>(100);
			this->chart1->Series->AddRange(gcnew cli::array< ChartFX::WinForms::SeriesAttributes^  >(1) {seriesAttributes1});
			this->chart1->Size = System::Drawing::Size(684, 664);
			this->chart1->TabIndex = 0;
			titleDockable1->Text = L"";
			this->chart1->Titles->AddRange(gcnew cli::array< ChartFX::WinForms::TitleDockable^  >(1) {titleDockable1});
			this->chart1->ToolBar->Visible = true;
			// 
			// Histogram
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 664);
			this->Controls->Add(this->chart1);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Histogram";
			this->Text = L"Histogram";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

public:

void Hist_NDivs(array<double>^ values, double lo, double hi, int NDivs, String^ XTitle)
{
	Array::Sort(values);
	array<double>^ posts = gcnew array<double>(NDivs + 1);//histogram subsection bounds
	double step = (hi - lo)/(double)NDivs;

	for (int i = 0; i <= NDivs; i++)
	{
		posts[i] = lo + step*double(i);
	}

	array<double>^ histogram = gcnew array<double>(NDivs);

	int ind = 0;
	int skipped = 0;
	for (int j = 0; j < values->Length; j++)
	{
		recheck:;
		if (values[j] < posts[0])
		{
			skipped++;
			continue;
		}
		if (values[j] >= posts[NDivs])
		{
			skipped++;
			continue;
		}
		if (values[j] >= posts[ind] && values[j] < posts[ind+1])
		{
			histogram[ind]++;
		}
		else
		{
			ind++;
			goto recheck;
			/*if (values[j] == posts[NDivs])
			{
				histogram[ind]++;
			}
			else
			{
				ind++;
				goto recheck;
			}*/
		}
	}

	chart1->AxisX->Title->Text = XTitle;
	chart1->AxisY->Title->Text = "Count";
	chart1->Data->AggressiveAllocation = true;
	chart1->AxisX->LabelsFormat->Decimals = 2;
	chart1->AxisY->LabelsFormat->Decimals = 0;
	chart1->AxisX->Min = lo-(hi-lo)/20;
	chart1->AxisX->Max = hi+(hi-lo)/20;
	chart1->AxisY->Max = Math::Round(JPMath::Max(histogram,true)*1.05);
	chart1->Data->Points = histogram->Length;
	//chart1->Titles[0]->Text = String::Concat("Total Number of Elements: ",values->Length,"   /rNumber of elements not within range: ",skipped.ToString());

	for (int i = 0; i < NDivs; i++)
	{
		chart1->Data->X[0,i] = posts[i];
		chart1->Data->Y[0,i] = histogram[i];
	}
	Histogram::Show();
}

void Hist_IntStep(array<double>^ values, int step, int XMin, int XMax, int YMin, int YMax, String^ XTitle, String^ YTitle, String^ ChartTitle)
{
	try
	{
		Array::Sort(values);
		double min = Math::Floor(values[0]);
		double max = Math::Ceiling(values[values->Length-1]);

		if (XMin == System::Int32::MaxValue)
			chart1->AxisX->Min = min-(max-min)/20;
		else
		{
			chart1->AxisX->Min = XMin;
			min = XMin;
		}
		if (XMax == System::Int32::MinValue)
			chart1->AxisX->Max = max+(max-min)/20;
		else
		{
			chart1->AxisX->Max = XMax;
			max = XMax;
		}

		int NDivs = int(Math::Floor((max-min+step)/step));
		array<double>^ posts = gcnew array<double>(NDivs+1);
		for (int i = 0; i < posts->Length; i++)
		{
			posts[i] = min + double(step*i);
		}

		array<double>^ histogram = gcnew array<double>(NDivs);

		int ind = 0;
		for (int j = 0; j < values->Length; j++)
		{
			recheck:;
			if (values[j] >= posts[ind] && values[j] < posts[ind+1])
			{
				histogram[ind]++;
			}
			else
			{
				ind++;
				goto recheck;
				/*if (values[j] == posts[NDivs])
				{
					histogram[ind]++;
				}
				else
				{
					ind++;
					goto recheck;
				}*/
			}
		}

		if (YMin == System::Int32::MaxValue)
			chart1->AxisY->Min = 0;
		else
			chart1->AxisY->Min = YMin;
		if (YMax == System::Int32::MinValue)
			chart1->AxisY->Max = Math::Round(JPMath::Max(histogram,true)*1.05);
		else
			chart1->AxisY->Max = YMax;

		chart1->AxisX->Title->Text = XTitle;
		chart1->AxisY->Title->Text = YTitle;
		chart1->Titles[0]->Text = ChartTitle;
		chart1->AxisX->AutoScale = false;
		chart1->Data->AggressiveAllocation = true;
		chart1->AxisX->LabelsFormat->Decimals = 1;
		chart1->AxisY->LabelsFormat->Decimals = 1;
		chart1->Data->Points = histogram->Length;
		
		for (int i = 0; i < NDivs; i++)
		{
			chart1->Data->X[0,i] = posts[i]-0.5;
			chart1->Data->Y[0,i] = histogram[i];
		}
		Histogram::Show();
		//::MessageBox::Show(histogram[NDivs-1].ToString(),posts[NDivs-1].ToString());
	}
	catch (::Exception^ e)
	{
		::MessageBox::Show(e->Data->ToString(),e->Message);
	}
}



	};
}
