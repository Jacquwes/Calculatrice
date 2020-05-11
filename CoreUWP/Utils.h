#pragma once

#include "pch.h"

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
	std::vector<std::string> splitString(std::string text, std::vector<std::string> delimiters);

	//	Indique si un vector donné contient ou non une certaine valeur.
	//
	//
	//	Params :
	//		vector<...> vector	: Vector à inspecter
	//		...	key				: Valeur à trouver
	template<class T>
	bool vectorIncludes(std::vector<T> vector, T key);

	//	Retourne l'index de la première fois qu'une valeur apparaît dans un vector.
	//
	//
	//	Params :
	//		vector<...> vector	: Vector à inspecter
	//		... key				: Valeur à trouver
	template<class T>
	int firstIndexInVector(std::vector<T> vector, T key);

	//	Retourne une liste de tous les index d'une valeur dans un vector.
	//
	//
	//  Params :
	//		vector<string> vector	: Vector à inspecter
	//		string key				: Valeur à trouver
	std::vector<int> indexesInVector(std::vector<std::string> vector, std::string key);

	//	Permet d'encadrer des suites d'opérations du même type entre parenthèses.
	//		Exemple : 5+9*5*7 -> 5+(9*5*7)
	//
	//
	//	Params :
	//		vector<string> expression	: Expression à manipuler
	//		string operation			: Opérations à encadrer
	std::vector<std::string> frameAlignedOperations(std::vector<std::string> expression, std::string operation);

	//	Retourne les index des parenthèses ouvrantes et fermantes les plus intérieures d'un expression.
	//
	//
	//  Params :
	//		vector<string> expression	: Expression à évaluer
	std::vector<int> findDeepestExpression(std::vector<std::string> exression);

	namespace Constants {
		//	Délimiteurs utilisés pour sérialiser les expressions.
		inline std::vector<std::string> delimiters = {
			"+", "-",
			"*", "/",
			"(", ")",
			"^",
			">", "<", "|", "\\", "&", "~",
		};

		//tex:
		//$$e=\frac{2+2}{\frac{2+3}{\frac{3+4}{\frac{4+5}{etc...}}}}$$
		inline double euler = 2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746;

		inline double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480;
	}

	// Structure représentant une erreur
	struct Error
	{
		std::string name;
		std::string description;
	};
}