#include "Core.h"
#include "Utils.h"

namespace Calculatrice::Core {
	std::vector<std::string> serialize(std::string rawExpression)
	{
		// Sépare les nombres des symboles
		std::vector<std::string> expression = Calculatrice::Utils::splitString(rawExpression, Calculatrice::Utils::Constants::delimiters);
		// Supprime les éléments vides de l'expression
		while (Calculatrice::Utils::vectorIncludes(expression, ""))
			expression.erase(expression.begin() + Calculatrice::Utils::firstIndexInVector(expression, ""));

		// Sert à respecter les lois de distributivité.
		// Remplace toutes les soustractions par des additions du nombre opposé.
		while (Calculatrice::Utils::vectorIncludes(expression, "-"))
		{
			int index = Calculatrice::Utils::firstIndexInVector(expression, "-");
			expression[index] = "+";
			// static_cast<size_t>(index) sert à considerer index comme une variable sur 8 octets plutot que 4.
			// Cela permet d'éviter des erreurs sur les très (très) grandes opérations, et le compilateur
			//		considère ça comme une erreur.
			expression[static_cast<size_t>(index) + 1] = "-" + expression[static_cast<size_t>(index) + 1];
		}

		// Sert à respecter les lois de priorités de calcul.
		// Encadre de parenthèses les opérations qui se suivent.
		expression = Calculatrice::Utils::frameAlignedOperations(expression, "^");
		expression = Calculatrice::Utils::frameAlignedOperations(expression, "*");
		expression = Calculatrice::Utils::frameAlignedOperations(expression, "/");

		return expression;
	}

	double solve(std::string rawExpression) { return solve(serialize(rawExpression)); }

	double solve(std::vector<std::string> expression)
	{
		// Retourne l'expression si elle ne comporte plus qu'un seul membre.
		if (expression.size() == 1) return std::stod(expression[0]);

		// Calcule en premier les calculs entre parenthèses.
		while (Calculatrice::Utils::vectorIncludes(expression, "("))
		{
			// Expression entre les parenthèses les plus intérieures.
			std::vector<std::string> deepestExpression{};
			// Nouvelle expression, dont l'expression la plus intérieure à été résolue.
			std::vector<std::string> newExpression{};
			// index des parenthèses de l'expression la plus intérieure.
			std::vector<int> bounds = Calculatrice::Utils::findDeepestExpression(expression);

			// Assigne l'expression la plus intérieure à son vector.
			std::copy(expression.begin() + bounds[0] + 1, expression.begin() + bounds[1], std::back_inserter(deepestExpression));
			// Ajoute la première partie de l'expression au vector de la nouvelle expression.
			std::copy(expression.begin(), expression.begin() + bounds[0], std::back_inserter(newExpression));
			// Ajoute l'expression la plus intérieure à la nouvelle.
			newExpression.push_back(std::to_string(solve(deepestExpression)));
			// Ajoute la fin de l'expression
			std::copy(expression.begin() + bounds[1] + 1, expression.end(), std::back_inserter(newExpression));

			expression = newExpression;
		}

		// Résoud l'opération des deux premiers membres de l'expression.
		double result = 0;
		if (expression[1] == "+") result = std::stod(expression[0]) + std::stod(expression[2]);
		else if (expression[1] == "*") result = std::stod(expression[0]) * std::stod(expression[2]);
		else if (expression[1] == "/") result = std::stod(expression[0]) / std::stod(expression[2]);
		else if (expression[1] == "^") result = pow(std::stod(expression[0]), std::stod(expression[2]));

		// Ajoute le résultat de la première opération de l'expression et son reste à la nouvelle expression.
		std::vector<std::string> newExpression{ std::to_string(result) };
		std::copy(expression.begin() + 3, expression.end(), std::back_inserter(newExpression));

		// Fonctionne par récursivité.
		return solve(newExpression);
	}
}