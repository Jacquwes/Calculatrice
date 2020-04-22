#include <iostream>

#include "Core/Core.h"

int main(int argc, char** argv)
{
	std::cout << Calculatrice::Core::solve("5+6*3+2*2*2") << std::endl;
}