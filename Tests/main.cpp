#include <iostream>

#include "UserInterface/UserInterface.h"

int main(int argc, char** argv)
{
	Calculatrice::UI::UserInterface* ui = new Calculatrice::UI::UserInterface(Calculatrice::UI::UserInterfaceOptions{});
	ui->startConsole();
}