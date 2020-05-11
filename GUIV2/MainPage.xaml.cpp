//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Editor.xaml.h"

using namespace GUIV2;

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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	for (size_t y = 0; y < buttonsText.size(); y++)
		for (size_t x = 0; x < buttonsText[y].size(); x++)
		{
			Object^ currentButtonText = buttonsText[y][x];
			if (currentButtonText != "")
			{
				Button^ button = ref new Button;
				button->Content = currentButtonText;
				button->Width = 50;
				button->Style = static_cast<Windows::UI::Xaml::Style^>(Application::Current->Resources->Lookup("ButtonRevealStyle"));
				button->IsDoubleTapEnabled = false;
				button->AddHandler(button->TappedEvent, ref new TappedEventHandler(this, &MainPage::calculatorButton_Clicked), true);

				buttonsGrid->SetRow(button, static_cast<int>(y));
				buttonsGrid->SetColumn(button, static_cast<int>(x));
				buttonsGrid->Children->Append(button);
			}
		}
}

void GUIV2::MainPage::navigationView_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args)
{
	Frame->Navigate(Interop::TypeName(Editor::typeid));
}

void GUIV2::MainPage::calculatorButton_Clicked(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	Button^ button = (Button^)sender;
	expressions->Text = expressions->Text + button->Content;
}

void GUIV2::MainPage::solveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!expressions->Text->IsEmpty())
		expressions->Text = Utils::stdToPlatformString(std::to_string(Calculatrice::Core::solve(Utils::platformToStdString(expressions->Text))));
}

void GUIV2::MainPage::eraseButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	expressions->Text = "";
}


void GUIV2::MainPage::eraseButton_Copy_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	expressions->Text = Utils::stdToPlatformString(Utils::platformToStdString(expressions->Text).substr(0, Utils::platformToStdString(expressions->Text).size() - 1));
}
