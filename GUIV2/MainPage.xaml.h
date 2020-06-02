//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace GUIV2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void navigationView_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args);
		void calculatorButton_Clicked(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void solveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void eraseButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void eraseButton_Copy_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};

	// Boutons de la calculatrice
	const std::vector<std::vector<Platform::Object^>> buttonsText
	{
		{"(", ")", "AND", "NOT"},
		{"<<",">>","OR", "XOR"},
		{"e", "exp", "ln", "log"},
		{"rt", "sqrt", "cbrt", "^"},
		{"pi"},
		{"7", "8", "9", "*"},
		{"4", "5", "6", "/"},
		{"1", "2", "3", "+"},
		{".", "0", "", "-"}
	};
}
