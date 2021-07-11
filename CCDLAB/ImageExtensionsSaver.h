#pragma once

namespace CCDLAB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ImageExtensionsSaver
	/// </summary>
	public ref class ImageExtensionsSaver : public System::Windows::Forms::Form
	{
	public:
	ImageExtensionsSaver(JPFITS::FITSImageSet^ imageSet, ListBox^ list);	
	
		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ImageExtensionsSaver()
		{
			if (components)
			{
				delete components;
			}
		}
		private: System::Windows::Forms::Button^ CancelBtn;
		private: System::Windows::Forms::DataGridView^ extensionsGridView;



		private: System::Windows::Forms::Label^ label1;
		public: System::Windows::Forms::CheckBox^ FirstAsPrimaryChck;
		private:





		private: System::Windows::Forms::Button^ SaveBtn;
		private: System::Windows::Forms::CheckBox^ AppendIntoFileChck;




		private: System::Windows::Forms::DataGridViewTextBoxColumn^ EXTNAME;
		private: System::Windows::Forms::DataGridViewComboBoxColumn^ PRECISION;
		private: System::Windows::Forms::CheckBox^ ViewEditPrimaryHeaderBtn;



















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
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->extensionsGridView = (gcnew System::Windows::Forms::DataGridView());
			this->EXTNAME = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PRECISION = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->FirstAsPrimaryChck = (gcnew System::Windows::Forms::CheckBox());
			this->SaveBtn = (gcnew System::Windows::Forms::Button());
			this->AppendIntoFileChck = (gcnew System::Windows::Forms::CheckBox());
			this->ViewEditPrimaryHeaderBtn = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->extensionsGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(177, 249);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(89, 23);
			this->CancelBtn->TabIndex = 0;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			this->CancelBtn->Click += gcnew System::EventHandler(this, &ImageExtensionsSaver::CancelBtn_Click);
			// 
			// extensionsGridView
			// 
			this->extensionsGridView->AllowUserToAddRows = false;
			this->extensionsGridView->AllowUserToDeleteRows = false;
			this->extensionsGridView->AllowUserToResizeRows = false;
			this->extensionsGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->extensionsGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->extensionsGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->EXTNAME,
					this->PRECISION
			});
			this->extensionsGridView->Location = System::Drawing::Point(12, 25);
			this->extensionsGridView->Name = L"extensionsGridView";
			this->extensionsGridView->RowHeadersVisible = false;
			this->extensionsGridView->RowHeadersWidth = 62;
			this->extensionsGridView->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->extensionsGridView->Size = System::Drawing::Size(159, 248);
			this->extensionsGridView->TabIndex = 2;
			// 
			// EXTNAME
			// 
			this->EXTNAME->HeaderText = L"EXTNAME";
			this->EXTNAME->MaxInputLength = 18;
			this->EXTNAME->MinimumWidth = 8;
			this->EXTNAME->Name = L"EXTNAME";
			this->EXTNAME->Width = 84;
			// 
			// PRECISION
			// 
			this->PRECISION->DropDownWidth = 100;
			this->PRECISION->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->PRECISION->HeaderText = L"PRECISION";
			this->PRECISION->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"int16", L"uint16", L"int32", L"uint32", L"int64",
					L"uint64", L"float", L"double"
			});
			this->PRECISION->MinimumWidth = 8;
			this->PRECISION->Name = L"PRECISION";
			this->PRECISION->Width = 71;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Extension Naming";
			// 
			// FirstAsPrimaryChck
			// 
			this->FirstAsPrimaryChck->Location = System::Drawing::Point(177, 25);
			this->FirstAsPrimaryChck->Name = L"FirstAsPrimaryChck";
			this->FirstAsPrimaryChck->Size = System::Drawing::Size(89, 45);
			this->FirstAsPrimaryChck->TabIndex = 5;
			this->FirstAsPrimaryChck->Text = L"First Image as Primary Block";
			this->FirstAsPrimaryChck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FirstAsPrimaryChck->UseVisualStyleBackColor = true;
			this->FirstAsPrimaryChck->CheckedChanged += gcnew System::EventHandler(this, &ImageExtensionsSaver::FirstAsPrimaryChck_CheckedChanged);
			// 
			// SaveBtn
			// 
			this->SaveBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->SaveBtn->Location = System::Drawing::Point(177, 220);
			this->SaveBtn->Name = L"SaveBtn";
			this->SaveBtn->Size = System::Drawing::Size(89, 23);
			this->SaveBtn->TabIndex = 7;
			this->SaveBtn->Text = L"Save";
			this->SaveBtn->UseVisualStyleBackColor = true;
			this->SaveBtn->Click += gcnew System::EventHandler(this, &ImageExtensionsSaver::SaveBtn_Click);
			// 
			// AppendIntoFileChck
			// 
			this->AppendIntoFileChck->Location = System::Drawing::Point(177, 179);
			this->AppendIntoFileChck->Name = L"AppendIntoFileChck";
			this->AppendIntoFileChck->Size = System::Drawing::Size(89, 35);
			this->AppendIntoFileChck->TabIndex = 8;
			this->AppendIntoFileChck->Text = L"Append Onto Existing File";
			this->AppendIntoFileChck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->AppendIntoFileChck->UseVisualStyleBackColor = true;
			this->AppendIntoFileChck->CheckedChanged += gcnew System::EventHandler(this, &ImageExtensionsSaver::AppendIntoFileChck_CheckedChanged);
			// 
			// ViewEditPrimaryHeaderBtn
			// 
			this->ViewEditPrimaryHeaderBtn->Appearance = System::Windows::Forms::Appearance::Button;
			this->ViewEditPrimaryHeaderBtn->Location = System::Drawing::Point(177, 75);
			this->ViewEditPrimaryHeaderBtn->Margin = System::Windows::Forms::Padding(2);
			this->ViewEditPrimaryHeaderBtn->Name = L"ViewEditPrimaryHeaderBtn";
			this->ViewEditPrimaryHeaderBtn->Size = System::Drawing::Size(89, 40);
			this->ViewEditPrimaryHeaderBtn->TabIndex = 9;
			this->ViewEditPrimaryHeaderBtn->Text = L"View/Edit Primary Header";
			this->ViewEditPrimaryHeaderBtn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->ViewEditPrimaryHeaderBtn->UseVisualStyleBackColor = true;
			this->ViewEditPrimaryHeaderBtn->CheckedChanged += gcnew System::EventHandler(this, &ImageExtensionsSaver::ViewEditPrimaryHeaderBtn_Click);
			// 
			// ImageExtensionsSaver
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(273, 285);
			this->Controls->Add(this->ViewEditPrimaryHeaderBtn);
			this->Controls->Add(this->AppendIntoFileChck);
			this->Controls->Add(this->SaveBtn);
			this->Controls->Add(this->FirstAsPrimaryChck);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->extensionsGridView);
			this->Controls->Add(this->CancelBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"ImageExtensionsSaver";
			this->ShowIcon = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Image Extensions Saver";
			this->TopMost = true;
			this->MouseEnter += gcnew System::EventHandler(this, &ImageExtensionsSaver::ImageExtensionsSaver_MouseEnter);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->extensionsGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public:
		String^ BITPIXtoString(int bitPix, int bZero);
		TypeCode BITPIXStringToTYPECODE(String^ bitpixstr);

		JPFITS::FITSImageSet^ IMAGESET;
		String^ FILENAME = "";
		array<String^>^ EXTENSIONNAMES;
		array<TypeCode>^ PRECISIONTYPECODES;
		ListBox^ HEADERLISTBOX;
		JPFITS::FITSImageHeader^ HEADER;

		private: System::Void FirstAsPrimaryChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		private: System::Void AppendIntoFileChck_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		private: System::Void ViewEditPrimaryHeaderBtn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void SaveBtn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void CancelBtn_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void ImageExtensionsSaver_MouseEnter(System::Object^ sender, System::EventArgs^ e);
};
}
