#include <iostream>

#include "Core/Core.h"

int main(int argc, char** argv)
{
	std::cout << Calculatrice::Core::solve("(5+2)*(6+2)*2+(5^2)") << std::endl;
}