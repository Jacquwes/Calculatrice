#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Core {
	std::vector<std::string> parse(std::string rawExpression);
	
	double solve(std::string rawExpression);
	double solve(std::vector<std::string> expression);
}