#include <iostream>

#include "UserInterface/UserInterface.h"

int main(int argc, char** argv)
{
	Calculatrice::UI::UserInterfaceOptions options{};
	Calculatrice::UI::UserInterface ui(options);
	ui.startConsole();
}