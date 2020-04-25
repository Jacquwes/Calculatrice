#include <math.h>
#include "Utils.h"

namespace Calculatrice::Operations {
	double exponentiation(double firstMember, double secondMember)
	{
		//tex:
		//$$b = e^{\ln{b}}$$
		//$$b^x = e^{x\cdot \ln{b}}$$
		if (firstMember < 0) throw(Calculatrice::Utils::Error{ "Erreur exponentiation", "Le programme n'est pas encore capable d'utiliser cette fonction pour des nombres négatifs" });
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