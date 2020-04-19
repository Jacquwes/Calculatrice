#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Utils
{
	std::vector<std::string> splitString(std::string text, std::vector<std::string> delimiters);

	bool vectorIncludes(std::vector<std::string> vector, std::string key);
	int firstIndexInVector(std::vector<std::string> vector, std::string key);
	std::vector<int> indexesInVector(std::vector<std::string> vector, std::string key);

	namespace Constants {
		inline std::vector<std::string> delimiters = {
			"+", "-", "*", "/", "(", ")", "^"
		};
	}
}