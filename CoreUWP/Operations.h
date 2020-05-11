#pragma once

namespace Calculatrice::Operations {
	// Fonction exponentielle
	// exponential(5) correspond à
	//tex:
	//$$\exp{5}$$
	double exponential(double number);

	// Calculer une puissance d'un nombre
	// exponentiation(5, 10) correspond à
	//tex:
	//$$5^{10}$$
	double exponentiation(double firstMember, double secondMember);

	// Résoud une division comme une division euclidienne.
	// Cependant, la précision des variables double en c++ font que le résultat est inexact
	// Le paramètre precision correspond au nombre de chiffres après la virgule à calculer
	double division(double dividende, double divisor, int precision);

	// Calcule la racine d'un nombre
	double root(double number, double root);
}