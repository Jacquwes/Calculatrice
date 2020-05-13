//
// FunctionEditor.xaml.cpp
// Implementation of the FunctionEditor class
//

#include "pch.h"
#include "FunctionEditor.xaml.h"

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

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

FunctionEditor::FunctionEditor()
{
	InitializeComponent();
}

void GUIV2::FunctionEditor::functionName(String^ value)
{
	name->Text = value;
}

void GUIV2::FunctionEditor::functionInstructions(String^ value)
{
	instructions->Text = value;
}

