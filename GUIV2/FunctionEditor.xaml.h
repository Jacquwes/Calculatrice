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
		void functionName(String^ value);
		void functionInstructions(String^ value);
	};
}