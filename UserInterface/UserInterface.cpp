#include "UserInterface.h"

#include <iostream>
#include <string>
#include <vector>

#include "Core/Core.h"
#include "Core/Utils.h"

namespace Calculatrice::UI {
	UserInterface::UserInterface(UserInterfaceOptions options) : m_options(options) {}

	void UserInterface::handleCommand(Command command)
	{
		switch (command.command)
		{
		case Commands::HELP:
			std::cout
				<< " Aide :" << std::endl
				<< "     help | ?" << std::endl
				<< "         Affiche cette page." << std::endl
				<< "     quit" << std::endl
				<< "         Quitte le programme." << std::endl
				<< "     solve <expression>" << std::endl
				<< "         Permet de résoudre une expression mathématique." << std::endl
				<< "         Exemple : \"solve 5+4*2\" retournera \"13\"" << std::endl;
			break;
		case Commands::QUIT:
			exit(0);
		case Commands::SOLVE:
			if (command.args.size() != 1)
				throw(Error{ "Nombre d'arguments incorrect", "Cette commande ne peut prendre qu'un seul argument. Pour plus d'informations, entrez \"?\" ou \"help\"." });
			std::cout << " " << Calculatrice::Core::solve(command.args[0]) << std::endl;
		default:
			break;
		}
	}

	Command UserInterface::listenCommand()
	{
		std::cout << " > ";
		std::string entry;
		std::getline(std::cin, entry);

		std::string commandName = Calculatrice::Utils::splitString(entry, { " " })[0];

		Command command;
		if (commandName == "help" || commandName == "?")
			command.command = Commands::HELP;
		else if (commandName == "quit")
			command.command = Commands::QUIT;
		else if (commandName == "solve")
			command.command = Commands::SOLVE;
		else
			throw(Error{ "Commande introuvable", "Cette commande n'existe pas. Pour obtenir une liste des commandes utilisables, entrez \"?\" ou \"help\"." });

		std::vector<std::string> args = Calculatrice::Utils::splitString(entry, { " " });
		args.erase(args.begin(), args.size() == 1 ? args.begin() : args.begin() + 2);
		command.args = args;

		return command;
	}

	void UserInterface::startConsole()
	{
		std::cout << "Calculatrice" << std::endl << "";

		while (true)
		{
			try
			{
				Command command = listenCommand();
				handleCommand(command);
			}
			catch (const Error& e)
			{
				std::cout << " Une erreur est survenue : " << e.name << std::endl
					<< "     Description : " << e.description << std::endl;
			}
		}
	}
}