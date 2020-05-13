//
// Editor.xaml.cpp
// Implementation of the Editor class
//

#include "pch.h"
#include "Editor.xaml.h"
#include "MainPage.xaml.h"
#include "FunctionEditor.xaml.h"

using namespace GUIV2;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

Editor::Editor()
{
	InitializeComponent();
}

void GUIV2::Editor::navigationView_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args)
{
	Frame->Navigate(Interop::TypeName(MainPage::typeid));
}

void GUIV2::Editor::saveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
}

void GUIV2::Editor::executeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
}

void GUIV2::Editor::openButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ filePicker = ref new FileOpenPicker();
	filePicker->ViewMode = PickerViewMode::List;
	filePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	filePicker->FileTypeFilter->Clear();
	filePicker->FileTypeFilter->Append(".alg");

	IAsyncOperation<StorageFile^>^ pickFileOperation = filePicker->PickSingleFileAsync();
	auto pickFileTask = create_task(pickFileOperation);
	pickFileTask
		.then([](StorageFile^ file) { return FileIO::ReadTextAsync(file, Streams::UnicodeEncoding::Utf8); })
		.then([this](task<String^> fileContent) { 
		FunctionEditor^ fe = ref new FunctionEditor();
		fe->functionName("main");
		fe->functionInstructions("caca\nprout");
		algorithmEditor->Children->Append(fe);
			});

	/*
	concurrency::create_task(filePicker->PickSingleFileAsync()).then([](Windows::Storage::StorageFile^ file) {
		return Windows::Storage::FileIO::ReadTextAsync(file);
		}).then([&](String^ fileContent) {
			algorithmEditor->Text = fileContent;
			});
			*/
}

void GUIV2::Editor::documentationButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
}