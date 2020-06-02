#pragma once

#include "pch.h"

namespace Utils {
	// Convertit les différents types de string
	inline Platform::String^ stdToPlatformString(const std::string& string)
	{
		return ref new Platform::String(std::wstring(string.begin(), string.end()).c_str());
	}

	inline std::string platformToStdString(Platform::String^ string)
	{
		std::wstring w_str(string->Begin());
		return std::string(w_str.begin(), w_str.end());
	}
}