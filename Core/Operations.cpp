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

	double division(double dividende, double divisor, int precision)
	{
		// Indique si le résultat est négatif
		bool negative = false;

		// Si le dividende est négatif, negative est inversé
		if (dividende < 0)
		{
			negative = !negative;
			dividende = -dividende;
		}
		// Si le diviseur est négatif, negative est inversé
		if (divisor < 0)
		{
			negative = !negative;
			divisor = -divisor;
		}

		// Est divisé par 10 à chaque itération, indique où le résultat obtenu durant une de celles-ci doit être placé dans le quotient
		long long position = 0;
		// Résultat de la division
		double quotient{};
		// Reste de la division
		double reste = dividende;
		// S'exécute "precision" fois, indique le nombre de chiffres après la virgule à calculer
		for (int iterations = 0; iterations <= precision && reste != 0; iterations++)
		{
			// Nombre par lequel on multiplie le diviseur pour obtenir le reste
			double i{};
			// Calcule la table de multiplication du diviseur pour trouver le résultat le plus élevé qui soit inférieur ou égal au dividende
			while (divisor * (i + 1) <= reste)
				i++;
			// On ajoute i au quotient, multiplié par sa position
			quotient += i * pow(10, -position++);
			// Le reste est calculé
			reste -= (i * divisor);
			// Puis multiplié par 10
			reste *= 10;
		}

		return negative ? -quotient : quotient;
	}

	double root(double number, double root)
	{
		//tex:
		//$$\sqrt[n]{x}=x^{\frac{1}{n}}$$
		if (number < 0) throw(Calculatrice::Utils::Error{ "Erreur racine", "Le programme n'est pas encore capable d'utiliser cette fonction pour des nombres négatifs" });
		return exponentiation(number, 1. / root);
	}
}