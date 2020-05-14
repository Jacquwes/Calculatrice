//
// Editor.xaml.h
// Declaration of the Editor class
//

#pragma once

#include "Editor.g.h"

namespace GUIV2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Editor sealed
	{
	public:
		Editor();
	private:
		void navigationView_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args);
		void saveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void executeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void openButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void documentationButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void addFunction_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void closeAlgorithm_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		void closeAlgorithmFunctions(Windows::UI::Popups::IUICommand^ command);
		void saveAlgorithm(Windows::UI::Popups::IUICommand^ command);
	};
}
