#include <math.h>

namespace Calculatrice::Operations {
	double addition(double firstMember, double secondMember)
	{
		return firstMember + secondMember;
	}

	double subsraction(double firstMember, double secondMember)
	{
		return firstMember + (-secondMember);
	}

	double multiplication(double firstMember, double secondMember)
	{
		double result{};
		for (int i = 0; i < secondMember; i++)
			result += firstMember;

		return result;
	}

	/*double division(double firstMember, double secondMember)
	{
		double& diviser = firstMember;
		double& dividende = secondMember;

		double intermediaire = 0;
		
	}

	double exponentiation(double firstMember, double secondMember)
	{

	}*/
}