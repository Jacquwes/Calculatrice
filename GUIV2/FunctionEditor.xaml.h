//
// FunctionEditor.xaml.h
// Declaration of the FunctionEditor class
//

#pragma once

#include "FunctionEditor.g.h"

using namespace Platform;

namespace GUIV2
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class FunctionEditor sealed
	{
	public:
		FunctionEditor();
		FunctionEditor^ setName(String^ value);
		FunctionEditor^ setInstructions(String^ value);
		inline String^ getName() { return name->Text; }
		inline String^ getInstructions() { return instructions->Text; }
	};
}