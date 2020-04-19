#include <iostream>

#include "Core/Core.h"

int main(int argc, char** argv)
{
	std::cout << Calculatrice::Core::solve("5*3*5*5/3/3^8+9-1");
}