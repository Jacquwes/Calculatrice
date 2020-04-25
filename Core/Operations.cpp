#include <math.h>

namespace Calculatrice::Operations {
	double exponentiation(double firstMember, double secondMember)
	{
		//tex:
		//$$b = e^{\ln{b}}$$
		//$$b^x = e^{x\cdot \ln{b}}$$
		if (firstMember < 0) throw("Logarithm of negative number");
		return exp(secondMember * log(firstMember));
	}

	double root(double number, double root)
	{
		//tex:
		//$$\sqrt[n]{x}=x^{\frac{1}{n}}$$
		return exponentiation(number, 1. / root);
	}
}