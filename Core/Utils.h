#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Utils
{
	std::vector<std::string> splitString(std::string text, std::vector<std::string> delimiters);

	bool vectorIncludes(std::vector<int> vector, int key);
	bool vectorIncludes(std::vector<std::string> vector, std::string key);

	int firstIndexInVector(std::vector<std::string> vector, std::string key);

	std::vector<int> indexesInVector(std::vector<std::string> vector, std::string key);

	std::vector<std::string> frameAlignedOperations(std::vector<std::string> expression, std::string operation);
	std::vector<int> findDeepestExpression(std::vector<std::string> exression);

	namespace Constants {
		inline std::vector<std::string> delimiters = {
			"+", "-", "*", "/", "(", ")", "^"
		};
	}
}