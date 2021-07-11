#pragma once

namespace CCDLAB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FMImageExtensionsLoader
	/// </summary>
	public ref class ImageExtensionsLoader : public System::Windows::Forms::Form
	{
	public:
	ImageExtensionsLoader(String^ fileName);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ImageExtensionsLoader()
		{
			if (components)
			{
				delete components;
			}
		}
		public: System::Windows::Forms::CheckedListBox^ ExtensionChckdListBox;
		protected:

		protected:

		private: System::Windows::Forms::Button^ CancelBtn;
		private: System::Windows::Forms::Button^ SelectAllBtn;
		private: System::Windows::Forms::Button^ ClearSelectionBtn;
		private: System::Windows::Forms::Button^ LoadSelectionBtn;
		public: System::Windows::Forms::CheckBox^ IncludePrimaryChck;
		private:




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
			this->ExtensionChckdListBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->CancelBtn = (gcnew System::Windows::Forms::Button());
			this->SelectAllBtn = (gcnew System::Windows::Forms::Button());
			this->ClearSelectionBtn = (gcnew System::Windows::Forms::Button());
			this->LoadSelectionBtn = (gcnew System::Windows::Forms::Button());
			this->IncludePrimaryChck = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// ExtensionChckdListBox
			// 
			this->ExtensionChckdListBox->Dock = System::Windows::Forms::DockStyle::Left;
			this->ExtensionChckdListBox->FormattingEnabled = true;
			this->ExtensionChckdListBox->Location = System::Drawing::Point(0, 0);
			this->ExtensionChckdListBox->Name = L"ExtensionChckdListBox";
			this->ExtensionChckdListBox->ScrollAlwaysVisible = true;
			this->ExtensionChckdListBox->Size = System::Drawing::Size(171, 222);
			this->ExtensionChckdListBox->TabIndex = 0;
			// 
			// CancelBtn
			// 
			this->CancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelBtn->Location = System::Drawing::Point(177, 191);
			this->CancelBtn->Name = L"CancelBtn";
			this->CancelBtn->Size = System::Drawing::Size(99, 23);
			this->CancelBtn->TabIndex = 1;
			this->CancelBtn->Text = L"Cancel";
			this->CancelBtn->UseVisualStyleBackColor = true;
			this->CancelBtn->Click += gcnew System::EventHandler(this, &ImageExtensionsLoader::CancelBtn_Click);
			// 
			// SelectAllBtn
			// 
			this->SelectAllBtn->Location = System::Drawing::Point(177, 12);
			this->SelectAllBtn->Name = L"SelectAllBtn";
			this->SelectAllBtn->Size = System::Drawing::Size(99, 23);
			this->SelectAllBtn->TabIndex = 2;
			this->SelectAllBtn->Text = L"Select All";
			this->SelectAllBtn->UseVisualStyleBackColor = true;
			this->SelectAllBtn->Click += gcnew System::EventHandler(this, &ImageExtensionsLoader::SelectAllBtn_Click);
			// 
			// ClearSelectionBtn
			// 
			this->ClearSelectionBtn->Location = System::Drawing::Point(177, 41);
			this->ClearSelectionBtn->Name = L"ClearSelectionBtn";
			this->ClearSelectionBtn->Size = System::Drawing::Size(99, 23);
			this->ClearSelectionBtn->TabIndex = 3;
			this->ClearSelectionBtn->Text = L"Clear Selection";
			this->ClearSelectionBtn->UseVisualStyleBackColor = true;
			this->ClearSelectionBtn->Click += gcnew System::EventHandler(this, &ImageExtensionsLoader::ClearSelectionBtn_Click);
			// 
			// LoadSelectionBtn
			// 
			this->LoadSelectionBtn->Location = System::Drawing::Point(177, 162);
			this->LoadSelectionBtn->Name = L"LoadSelectionBtn";
			this->LoadSelectionBtn->Size = System::Drawing::Size(99, 23);
			this->LoadSelectionBtn->TabIndex = 4;
			this->LoadSelectionBtn->Text = L"Load Selection";
			this->LoadSelectionBtn->UseVisualStyleBackColor = true;
			this->LoadSelectionBtn->Click += gcnew System::EventHandler(this, &ImageExtensionsLoader::LoadSelectionBtn_Click);
			// 
			// IncludePrimaryChck
			// 
			this->IncludePrimaryChck->Location = System::Drawing::Point(177, 70);
			this->IncludePrimaryChck->Name = L"IncludePrimaryChck";
			this->IncludePrimaryChck->Size = System::Drawing::Size(99, 36);
			this->IncludePrimaryChck->TabIndex = 5;
			this->IncludePrimaryChck->Text = L"Include Primary in Load";
			this->IncludePrimaryChck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->IncludePrimaryChck->UseVisualStyleBackColor = true;
			// 
			// ImageExtensionsLoader
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->CancelBtn;
			this->ClientSize = System::Drawing::Size(281, 222);
			this->ControlBox = false;
			this->Controls->Add(this->IncludePrimaryChck);
			this->Controls->Add(this->LoadSelectionBtn);
			this->Controls->Add(this->ClearSelectionBtn);
			this->Controls->Add(this->SelectAllBtn);
			this->Controls->Add(this->CancelBtn);
			this->Controls->Add(this->ExtensionChckdListBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"ImageExtensionsLoader";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Image Extensions Loader";
			this->Load += gcnew System::EventHandler(this, &ImageExtensionsLoader::ImageExtensionsLoader_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void CancelBtn_Click(System::Object^ sender, System::EventArgs^ e) { }
	private: System::Void ImageExtensionsLoader_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SelectAllBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < ExtensionChckdListBox->Items->Count; i++)
			ExtensionChckdListBox->SetItemChecked(i, true);
	}
	private: System::Void ClearSelectionBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < ExtensionChckdListBox->Items->Count; i++)
			ExtensionChckdListBox->SetItemChecked(i, false);
	}
	private: System::Void LoadSelectionBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < ExtensionChckdListBox->Items->Count; i++)
			if (ExtensionChckdListBox->GetItemChecked(i))
			{
				this->DialogResult = Windows::Forms::DialogResult::OK;
				this->Close();
				return;
			}
	}
};
}
