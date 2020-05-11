#include "pch.h"
#include "Core.h"
#include "Operations.h"
#include "Utils.h"

namespace Calculatrice::Core {
	std::vector<std::string> parse(std::string rawExpression)
	{
		// Génère une liste des nombres de 0 à 9, et l'alphabet
		std::vector<std::string> numbers, alphabet{};
		for (int i = 48; i < 58; i++)
			numbers.push_back(std::string(1, i));
		for (int i = 65; i < 123; i++)
			alphabet.push_back(std::string(1, i));
		numbers.push_back(".");

		std::vector<std::string> expression;
		std::string intermediaire;

		// Pour chaque caractère de l'expression
		for (size_t i = 0; i < rawExpression.size(); i++)
		{
			// Caractère actuel
			std::string currentChar = std::string(1, rawExpression[i]);
			// Si c'est le premier, ou si la valeur intermédiaire est vide
			if (i == 0 || intermediaire == "")
			{
				intermediaire += currentChar;
			}
			else {
				// Si le caractère actuel est un délimiteur
				bool isDelimiter = Calculatrice::Utils::vectorIncludes(Calculatrice::Utils::Constants::delimiters, currentChar);
				if (isDelimiter)
				{
					// On ajoute la valeur intermédiaire
					expression.push_back(intermediaire);
					// Et le délimiteur actuel
					expression.push_back(currentChar);
					// Puis on vide la valeur intermédiaire
					intermediaire = "";
				}
				// Si le caractère actuel ne fait pas partie des délimiteurs
				else
				{
					// Si le caractère actuel est une lettre
					bool isLetter = Calculatrice::Utils::vectorIncludes(alphabet, currentChar);
					if (isLetter)
					{
						// Si le caractère précédent était aussi une lettre, on l'ajoute à la suite
						if (Calculatrice::Utils::vectorIncludes(alphabet, std::string(1, intermediaire.back())))
							intermediaire += currentChar;
						// Sinon, la valeur intermédiaire est ajoutée à l'expression
						else
						{
							expression.push_back(intermediaire);
							intermediaire = currentChar;
						}
					}
					// Idem si le caractère actuel est un chiffre
					else
					{
						if (Calculatrice::Utils::vectorIncludes(numbers, std::string(1, intermediaire.back())))
							intermediaire += currentChar;
						else
						{
							expression.push_back(intermediaire);
							intermediaire = currentChar;
						}
					}
				}
			}
		}

		if (intermediaire != "")
			expression.push_back(intermediaire);

		return expression;
	}

	std::vector<std::string> serialize(std::string rawExpression)
	{
		// Sépare les nombres des symboles
		std::vector<std::string> expression = parse(rawExpression);
		// Supprime les éléments vides de l'expression
		while (Calculatrice::Utils::vectorIncludes(expression, std::string("")))
			expression.erase(expression.begin() + Calculatrice::Utils::firstIndexInVector(expression, std::string("")));

		// Remplacer la constante d'Euler (de la fonction exponentielle) par sa valeur
		while (Calculatrice::Utils::vectorIncludes(expression, std::string("e")))
			expression[Calculatrice::Utils::firstIndexInVector(expression, std::string("e"))] = std::to_string(Calculatrice::Utils::Constants::euler);
		// Remplacer pi par sa valeur
		while (Calculatrice::Utils::vectorIncludes(expression, std::string("pi")))
			expression[Calculatrice::Utils::firstIndexInVector(expression, std::string("pi"))] = std::to_string(Calculatrice::Utils::Constants::pi);

		std::vector<std::string> numbers{ "." };
		for (int i = 48; i < 58; i++)
			numbers.push_back(std::string(1, i));

		// Sert à respecter les lois de distributivité.
		// Remplace toutes les soustractions par des additions du nombre opposé.
		while (Calculatrice::Utils::vectorIncludes(expression, std::string("-")))
		{
			int index = Calculatrice::Utils::firstIndexInVector(expression, std::string("-"));
			expression[index] = "+";

			// static_cast<size_t>(index) sert à considerer index comme une variable sur 8 octets plutot que 4.
			// Cela permet d'éviter des erreurs sur les très (très) grandes opérations, et le compilateur
			//		considère ça comme une erreur.

			// Si - est devant une parenthèse
			if (expression[static_cast<size_t>(index) + 1] == "(")
			{
				// Si - est le premier caractère de l'expression
				if (index == 0)
					expression.erase(expression.begin()); // Supprime le + ajouté
				expression.insert(expression.begin() + (index == 0 ? index : index + 1), { "-1", "*" });
			}
			// Si - est le premier caractère de l'expression
			else if (index == 0)
			{
				expression.erase(expression.begin());
				expression[0] = "-" + expression[0];
			}
			// Si - est derrière un signe
			else if (Calculatrice::Utils::vectorIncludes(Calculatrice::Utils::Constants::delimiters, expression[static_cast<size_t>(index) - 1]))
			{
				expression.erase(expression.begin() + index);
				expression[static_cast<size_t>(index)] = "-" + expression[static_cast<size_t>(index)];
			}
		}

		return expression;
	}

	double solve(std::string rawExpression) { return solve(serialize(rawExpression)); }

	double solve(std::vector<std::string> expression)
	{
		// Retourne l'expression si elle ne comporte plus qu'un seul membre.
		if (expression.size() == 1) return std::stod(expression[0]);

		// Calcule en premier les calculs entre parenthèses.
		while (Calculatrice::Utils::vectorIncludes(expression, std::string("(")))
		{
			// Expression entre les parenthèses les plus intérieures.
			std::vector<std::string> deepestExpression{};
			// Nouvelle expression, dont l'expression la plus intérieure à été résolue.
			std::vector<std::string> newExpression{};
			// index des parenthèses de l'expression la plus intérieure.
			std::vector<int> bounds = Calculatrice::Utils::findDeepestExpression(expression);

			// Assigne l'expression la plus intérieure à son vector.
			std::copy(expression.begin() + bounds[0] + 1, expression.begin() + bounds[1], std::back_inserter(deepestExpression));

			// Sert à respecter les lois de priorités de calcul.
			// Encadre de parenthèses les opérations qui se suivent.
			// Ces instructions ne sont pas situées dans la fonction de sérialisation,
			// car les parenthèses provoqueraient des bugs.
			deepestExpression = Calculatrice::Utils::frameAlignedOperations(deepestExpression, "^");
			deepestExpression = Calculatrice::Utils::frameAlignedOperations(deepestExpression, "rcn");
			deepestExpression = Calculatrice::Utils::frameAlignedOperations(deepestExpression, "*");
			deepestExpression = Calculatrice::Utils::frameAlignedOperations(deepestExpression, "/");

			// Supprime toutes les parenthèses de l'expression la plus intérieure
			for (auto& i : { std::string("("), std::string(")") })
				while (Calculatrice::Utils::vectorIncludes(deepestExpression, i))
					deepestExpression.erase(deepestExpression.begin() + Calculatrice::Utils::firstIndexInVector(deepestExpression, i));

			// Ajoute la première partie de l'expression au vector de la nouvelle expression.
			std::copy(expression.begin(), expression.begin() + bounds[0], std::back_inserter(newExpression));
			// Ajoute l'expression la plus intérieure à la nouvelle.
			newExpression.push_back(std::to_string(solve(deepestExpression)));
			// Ajoute la fin de l'expression
			std::copy(expression.begin() + bounds[1] + 1, expression.end(), std::back_inserter(newExpression));

			expression = newExpression;
		}

		if (expression.size() == 1) return std::stod(expression[0]);

		// Résoud l'opération des deux premiers membres de l'expression.
		double result{};
		int operationSize = 3;
		if (expression[1] == "+") result = std::stod(expression[0]) + std::stod(expression[2]);
		else if (expression[1] == "*") result = std::stod(expression[0]) * std::stod(expression[2]);
		else if (expression[1] == "/") result = Calculatrice::Operations::division(std::stod(expression[0]), std::stod(expression[2]), 107);
		// Exponentiation
		else if (expression[1] == "^") result = Calculatrice::Operations::exponentiation(std::stod(expression[0]), std::stod(expression[2]));
		// Racine
		else if (expression[1] == "rt") result = Calculatrice::Operations::root(std::stod(expression[0]), std::stod(expression[2]));
		// Racine base 2
		else if (expression[0] == "sqrt") {
			result = Calculatrice::Operations::root(std::stod(expression[1]), 2);
			operationSize--;
		}
		// Racine base 3
		else if (expression[0] == "cbrt") {
			result = Calculatrice::Operations::root(std::stod(expression[1]), 3);
			operationSize--;
		}
		// Exponentielle
		else if (expression[0] == "exp") {
			result = Calculatrice::Operations::exponential(std::stod(expression[1]));
			operationSize--;
		}
		// Logarithme base e
		else if (expression[0] == "ln") {
			result = log(std::stod(expression[1]));
			operationSize--;
		}
		// Logarithme base 10
		else if (expression[0] == "log") {
			result = Calculatrice::Operations::division(log(std::stod(expression[1])), log(10), 10);
			operationSize--;
		}
		// Logarithme base x
		else if (expression[1] == "log") result = Calculatrice::Operations::division(log(std::stod(expression[2])), log(std::stod(expression[0])), 10);

		// Opérations sur les bits
		// Arithmetic shift vers la gauche
		else if (expression[1] == "LS") result = static_cast<double>(std::stoll(expression[0]) << std::stoll(expression[2]));
		// Arithmetic shift vers la droite
		else if (expression[1] == "RS") result = static_cast<double>(std::stoll(expression[0]) >> std::stoll(expression[2]));
		// Les Logic shifts demanderaient à ce que l'on change la fonction parse, cette option sera donc considérée dans le futur.
		// OR
		else if (expression[1] == "OR") result = static_cast<double>(std::stoll(expression[0]) | std::stoll(expression[2]));
		// XOR
		else if (expression[1] == "XOR") result = static_cast<double>(std::stoll(expression[0]) ^ std::stoll(expression[2]));
		// AND
		else if (expression[1] == "AND") result = static_cast<double>(std::stoll(expression[0]) & std::stoll(expression[2]));
		// NOT
		else if (expression[0] == "NOT") result = static_cast<double>(~std::stoll(expression[1]));

		// Ajoute le résultat de la première opération de l'expression et son reste à la nouvelle expression.
		std::vector<std::string> newExpression{ std::to_string(result) };
		std::copy(expression.begin() + operationSize, expression.end(), std::back_inserter(newExpression));

		// Fonctionne par récursivité.
		return solve(newExpression);
	}
}