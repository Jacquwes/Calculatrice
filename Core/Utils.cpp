#include <algorithm>
#include <string>
#include <vector>

#include "Utils.h"

namespace Calculatrice::Utils
{
	std::vector<std::string> splitString(std::string text, std::vector<std::string> delimiters)
	{
		//définition des objets utilisés par la fonction
		std::vector<std::string> final;   //Variable retournée
		std::string intermediaire;   //<variable permettant de stocker plusieurs caractères, comme un
								//nombre par exemple.

	 // Boucle éxecutée pour chacun des caractéres du texte à scinder
		for (size_t i = 0; i < text.length(); i++)
		{
			// Définition de variables utilisées par la fonction
			char token(text[i]);		// Caractére indiqué par la boucle
			bool isDelimiter(false);	// Indique si le caractère actuel est un délimiteur

			// Execute le code suivant si le caractére actuel n'a pas encore été défini comme
			// délimiteur
			if (!isDelimiter)
			{// Boucle éxécutée pour chacun des délimiteurs
				for (size_t o = 0; o < delimiters.size(); o++)
				{
					// Définition du délimiteur actuel
					std::string delimiter = delimiters[o];

					// Si le caractére actuel fait partie des délimiteurs, alors il est défini
					// comme tel.
					if (Calculatrice::Utils::vectorIncludes(delimiters, std::string(1, token)))
						isDelimiter = true;
				}
			}

			// Ajoute le caractère actuel à la variable intermédiaire si il n'a pas été défini
			// comme un délimiteur dans la boucle précédente
			if (!isDelimiter)
				intermediaire += token;
			// Sinon, la variable intermédiaire est transférée à la fin de la variable finale,
			// tout comme le délimiteur
			else
			{
				final.push_back(intermediaire);
				final.push_back(std::string(1, token));
				intermediaire = "";
			}
		}

		// La dernière valeur intermédiaire est ajoutée la variable finale
		final.push_back(intermediaire);

		//Retourne le résultat final
		return final;
	}

	bool vectorIncludes(std::vector<int> vect, int key)
	{
		// Si le vector contient au moins une fois key, alors la fonction retournera true.
		return std::count(vect.begin(), vect.end(), key);
	}

	bool vectorIncludes(std::vector<std::string> vect, std::string key)
	{
		return std::count(vect.begin(), vect.end(), key);
	}

	int firstIndexInVector(std::vector<std::string> vect, std::string key)
	{
		// Index par défaut.
		int index = 0;
		// S'exécute sur chaque élément du vector.
		for (auto& character : vect)
		{
			// Si la clé est correspondante au caractère actuel, alors on sort de la boucle.
			if (character == key)
				break;
			// Sinon, index est incrémenté.
			index++;
		}

		return index;
	}

	std::vector<int> indexesInVector(std::vector<std::string> vect, std::string key)
	{
		// Vector contenant tous les index.
		std::vector<int> result;

		// S'exécute tant que le vector contient la clé
		while (Calculatrice::Utils::vectorIncludes(vect, key))
		{
			// Ajoute le premier index à la liste
			int index = firstIndexInVector(vect, key);
			result.push_back(index);
			// Puis le supprime du vector
			vect[index] = "";
		}

		return result;
	}

	std::vector<std::string> frameAlignedOperations(std::vector<std::string> expression, std::string operation)
	{
		// Contient tous les index de l'opérateur en question
		std::vector<int> indexes = indexesInVector(expression, operation);
		
		// S'exécute pour chaque opérateur
		for (int i = 0; i < indexes.size(); i++)
		{
			indexes = indexesInVector(expression, operation);
			int index = indexes[i];
			// Si c'est le premier opérateur
			if (i == 0)
				expression.insert(expression.begin() + index - 1, "(");
			// Si celui le précédant était différent
			else if (expression[static_cast<size_t>(index) - 2] != operation)
				expression.insert(expression.begin() + index - 1, "(");

			// Mise à jour des index, car ils peuvent avoir été modifiés juste au dessus.
			indexes = indexesInVector(expression, operation);
			index = indexes[i];
			// Si c'est le dernier opérateur
			if (i == indexes.size() - 1)
				expression.insert(expression.begin() + index + 2, ")");
			// Si le suivant est différent
			else if (expression[static_cast<size_t>(index) + 2] != operation)
					expression.insert(expression.begin() + index + 2, ")");
		}

		return expression;
	}

	std::vector<int> findDeepestExpression(std::vector<std::string> expression)
	{
		std::vector<int> openParentheses = indexesInVector(expression, "(");
		std::vector<int> closedParentheses = indexesInVector(expression, ")");

		// La dernière parenthèse ouverte est forcément la plus intérieure.
		int openParenthese = openParentheses.back();
		int closedParenthese{};

		// S'exécute sur tous les caractères de l'expression en partant de la gauche, jusqu'à la dernière parenthèse ouverte.
		for (int i = closedParentheses.back(); i >= openParenthese && i >= closedParentheses.front(); i--)
		{
			// Si le le caractère est une parenthèse fermante, alors closedParenthese est assigné à son index.
			if (vectorIncludes(closedParentheses, i))
				closedParenthese = i;
		}

		return { openParenthese, closedParenthese };
	}
}