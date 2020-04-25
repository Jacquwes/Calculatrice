#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Core {
	std::vector<std::string> parse(std::string rawExpression);

	//	Cette fonction sert à génerer une liste de strings compréhensible par le programme à partir d'une
	//		expression sous la forme d'une variable string.
	//	Elle s'occupe de placer des parenthèses là où elles sont nécessaires pour que les lois de priorités
	//		de calcul soient respectées, et transforme aussi les soustraction en additions, pour respecter
	//		les lois de distributivité.
	//
	//
	//	Params :
	//		string rawExpression	: Expression à sérialiser
	//
	//
	//	Exemple d'utilisation :
	//		Pour sérialiser "5+3-5*8*9"
	//		Calculatrice::Core::serialize("5+3-5*8*9");
	std::vector<std::string> serialize(std::string rawExpression);
	
	//	Surcharge de la fonction suivante. Permet de simplifier son utilisation.
	//
	//
	//	Params :
	//		string rawExpression	: Expression à résoudre
	//
	//
	//	Exemple d'utilisation :
	//		Pour résoudre 5+3*8*9
	//		Calculatrice::Core::solve("5+3*8*9");
	double solve(std::string rawExpression);

	//	Cette fonction sert à résoudre une expression faite d'opérations simples.
	//
	//
	//	Params :
	//		vector<string> expression	: Expression à résoudre
	//
	//
	//	Exemple d'utilisation :
	//		Pour résoudre 5+3*8*9
	//		Calculatrice::Core::solve(Calculatrice::Core::serialize("5+3*8*9"));
	double solve(std::vector<std::string> expression);
}