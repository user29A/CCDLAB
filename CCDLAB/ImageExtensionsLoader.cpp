#include "stdafx.h"
#include "ImageExtensionsLoader.h"


CCDLAB::ImageExtensionsLoader::ImageExtensionsLoader(String^ fileName)
{
	InitializeComponent();

	array<String^>^ extlist = JPFITS::FITSImage::GetAllExtensionNames(fileName);

	if (extlist->Length == 0)
	{
		MessageBox::Show("No IMAGE extensions exist in the file...", "Error");
		this->Close();
		return;
	}

	JPFITS::FITSImage^ fi = gcnew JPFITS::FITSImage(fileName, nullptr, true, false, false, false);
	if (fi->Header->GetKeyValue("NAXIS") == "0")
		IncludePrimaryChck->Enabled = false;

	int n = 1;
	for (int i = 0; i < extlist->Length; i++)
		if (extlist[i] == "")
		{
			ExtensionChckdListBox->Items->Add("Unnamed extension: " + n, true);
			n++;
		}
		else
			ExtensionChckdListBox->Items->Add(extlist[i], true);
}

void CCDLAB::ImageExtensionsLoader::ImageExtensionsLoader_Load(System::Object^ sender, System::EventArgs^ e)
{

}

