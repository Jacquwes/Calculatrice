#include <math.h>
#include "Utils.h"

namespace Calculatrice::Operations {
	double exponential(double number)
	{
		return pow(Calculatrice::Utils::Constants::euler, number);
	}

	double exponentiation(double firstMember, double secondMember)
	{
		//tex:
		//$$b = e^{\ln{b}}$$
		//$$b^x = e^{x\cdot \ln{b}}$$

		// Si le premier membre est négatif
		if (firstMember < 0)
			if (fmod(secondMember, 2) == 0) // Si l'exposant est pair
				return exponential(secondMember * log(-firstMember));
			else // Sinon
				return -exponential(secondMember * log(-firstMember));
		else
			return exp(secondMember * log(firstMember));
	}

	double root(double number, double root)
	{
		//tex:
		//$$\sqrt[n]{x}=x^{\frac{1}{n}}$$
		if (number < 0) throw(Calculatrice::Utils::Error{ "Erreur racine", "Le programme n'est pas encore capable d'utiliser cette fonction pour des nombres négatifs" });
		return exponentiation(number, 1. / root);
	}
}