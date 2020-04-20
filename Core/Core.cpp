#include "Core.h"
#include "Utils.h"

namespace Calculatrice::Core {
	std::vector<std::string> parse(std::string rawExpression)
	{
		// split expression
		std::vector<std::string> expression = Calculatrice::Utils::splitString(rawExpression, Calculatrice::Utils::Constants::delimiters);
		while (Calculatrice::Utils::vectorIncludes(expression, ""))
			expression.erase(expression.begin() + Calculatrice::Utils::firstIndexInVector(expression, ""));

		// loi de distributivité
		// replace "-1" -> "+(-1)
		while (Calculatrice::Utils::vectorIncludes(expression, "-"))
		{
			int index = Calculatrice::Utils::firstIndexInVector(expression, "-");
			expression[index] = "+";
			expression[static_cast<size_t>(index) + 1] = "-" + expression[static_cast<size_t>(index) + 1];
		}

		// lois de priorités de calcul
		struct priorityLawProperties
		{
			std::vector<int> multiplicationsIndexes;
			std::vector<int> divisionsIndexes;
			std::vector<int> exponentiationsIndexes;
		};

		priorityLawProperties props;

		if (Calculatrice::Utils::vectorIncludes(expression, "*"))
			props.multiplicationsIndexes = Calculatrice::Utils::indexesInVector(expression, "*");
		if (Calculatrice::Utils::vectorIncludes(expression, "/"))
			props.divisionsIndexes = Calculatrice::Utils::indexesInVector(expression, "/");
		if (Calculatrice::Utils::vectorIncludes(expression, "^")) // doit remonter au dessus de * et /
			props.exponentiationsIndexes = Calculatrice::Utils::indexesInVector(expression, "^");
			

		return expression;
	}

	double solve(std::string rawExpression) { return solve(parse(rawExpression)); }

	double solve(std::vector<std::string> expression)
	{
		if (expression.size() == 1) return std::stod(expression[0]);

		while (Calculatrice::Utils::vectorIncludes(expression, "("))
		{
			std::vector<std::string> deepestExpression{};
			std::vector<std::string> newExpression{};
			std::vector<int> bounds = Calculatrice::Utils::findDeepestExpression(expression);

			std::copy(expression.begin() + bounds[0] + 1, expression.begin() + bounds[1], std::back_inserter(deepestExpression));
			std::copy(expression.begin(), expression.begin() + bounds[0], std::back_inserter(newExpression));
			newExpression.push_back(std::to_string(solve(deepestExpression)));
			std::copy(expression.begin() + bounds[1] + 1, expression.end(), std::back_inserter(newExpression));

			expression = newExpression;
		}

		double result = 0;
		if (expression[1] == "+") result = std::stod(expression[0]) + std::stod(expression[2]);
		else if (expression[1] == "*") result = std::stod(expression[0]) * std::stod(expression[2]);
		else if (expression[1] == "/") result = std::stod(expression[0]) / std::stod(expression[2]);
		else if (expression[1] == "^") result = pow(std::stod(expression[0]), std::stod(expression[2]));

		std::vector<std::string> newExpression{ std::to_string(result) };
		std::copy(expression.begin() + 3, expression.end(), std::back_inserter(newExpression));

		return solve(newExpression);
	}
}