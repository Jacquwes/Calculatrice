#include <algorithm>
#include <string>
#include <vector>

#include "Utils.h"

namespace Calculatrice::Utils
{
	//	Retourne un vector constitué de strings créés à partir d'une valeur string scindé en
	//	fonction de séparateur(s). Cette fonction sera utilisée pour séparer les nombres des
	//	opérateurs d'un calcul donné.
	//
	//
	//	Params :
	//		string text					: String à scinder
	//		vector<string>	delimiters	: Liste de délimiteurs
	//
	//
	//	Exemple d'utilisation :
	//		Pour transformer la valeur string :
	//			"(21+45)*98"
	//		En :
	//			{ "(", "21", "+", "45", ")", "*", "98" }		(Représentation sous forme d'array)
	//
	//		On utilise :
	//			utils::splitString("(21+45)*98", vector<string>({"+", "*", "(", ")"}));
	//
	//
	//	Retourne :
	//		Vector constitué de strings créés à partir d'un valeur string scindé en
	//		fonction de séparateur(s).
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
		return std::count(vect.begin(), vect.end(), key);
	}

	//	Indique si un certain vecteur inclut un certain élément.
	//
	//
	bool vectorIncludes(std::vector<std::string> vect, std::string key)
	{
		// Si vect contient key, la fonction renvoie true. Sinon, elle renvoie false.
		return std::count(vect.begin(), vect.end(), key);
	}

	int firstIndexInVector(std::vector<std::string> vect, std::string key)
	{
		int index = 0;
		for (auto& character : vect)
		{
			if (character == key)
				break;
			index++;
		}

		return index;
	}

	std::vector<int> indexesInVector(std::vector<std::string> vect, std::string key)
	{
		std::vector<int> result;

		while (Calculatrice::Utils::vectorIncludes(vect, key))
		{
			int index = firstIndexInVector(vect, key);
			result.push_back(index);
			vect[index] = "";
		}

		return result;
	}

	std::vector<int> findDeepestExpression(std::vector<std::string> expression)
	{
		std::vector<int> openParentheses = indexesInVector(expression, "(");
		std::vector<int> closedParentheses = indexesInVector(expression, ")");

		int openParenthese = openParentheses.back();
		int closedParenthese{};

		for (int i = closedParentheses.back(); i >= openParentheses.back() && i >= closedParentheses.front(); i--)
		{
			if (vectorIncludes(closedParentheses, i))
				closedParenthese = i;
		}

		return { openParenthese, closedParenthese };
	}
}