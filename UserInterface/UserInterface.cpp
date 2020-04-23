#include "UserInterface.h"

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "Core/Core.h"
#include "Core/Utils.h"

namespace Calculatrice::UI {
	UserInterface::UserInterface(UserInterfaceOptions options) : m_options(options) {}

	void UserInterface::handleCommand(Command command)
	{
		// Agit différemment en fonction de la commande choisie
		switch (command.command)
		{
		case Commands::HELP:
			// Affiche toutes les commandes disponibles
			std::cout
				<< " Aide :" << std::endl;
			writeColor("     help ", Colors::CYAN);
			std::cout << "ou";
			writeColor(" ?", Colors::CYAN);
			std::cout << std::endl
				<< "         Affiche cette page." << std::endl << std::endl;
			writeColor("     quit", Colors::CYAN);
			std::cout << std::endl
				<< "         Quitte le programme." << std::endl << std::endl;
			writeColor("     solve ", Colors::CYAN);
			std::cout << "<";
			writeColor("expression", Colors::GREEN); 
			std::cout << ">" << std::endl
				<< "         Permet de résoudre une expression mathématique." << std::endl
				<< "         Exemple : \"";
			writeColor("solve 5+4*2", Colors::CYAN);
			std::cout << "\" retournera \"13\"" << std::endl << std::endl;
			break;
		case Commands::QUIT:
			// Quitte le programme
			exit(0);
		case Commands::SOLVE:
			// Vérifie le nombre d'arguments
			if (command.args.size() != 1)
				throw(Error{ "Nombre d'arguments incorrect", "Cette commande ne peut prendre qu'un seul argument. Pour plus d'informations, entrez \"?\" ou \"help\"." });
			// Résoud l'expression et affiche son résultat
			else
				std::cout << " " << Calculatrice::Core::solve(command.args[0]) << std::endl;
		default:
			break;
		}
	}

	Command UserInterface::listenCommand()
	{
		// Récupère l'entrée de l'utilisateur
		std::cout << std::endl;
		writeColor(" calculatrice", Colors::GREEN);
		std::cout << "> ";
		std::string entry;
		std::getline(std::cin, entry);

		// Assigne le premier mot entré au nom de la commande
		std::string commandName = Calculatrice::Utils::splitString(entry, { " " })[0];

		// Détermine la commande utilisée, et génère une exception si elle est introuvable
		Command command;
		if (commandName == "help" || commandName == "?")
			command.command = Commands::HELP;
		else if (commandName == "quit")
			command.command = Commands::QUIT;
		else if (commandName == "solve")
			command.command = Commands::SOLVE;
		else
			throw(Error{ "Commande introuvable", "Cette commande n'existe pas. Pour obtenir une liste des commandes utilisables, entrez \"?\" ou \"help\"." });

		// Récupère une liste d'arguments
		std::vector<std::string> args = Calculatrice::Utils::splitString(entry, { " " });
		// Retire le nom de la commande
		args.erase(args.begin());
		// Retire tous les espaces
		while (Calculatrice::Utils::vectorIncludes(args, " "))
			args.erase(args.begin() + Calculatrice::Utils::firstIndexInVector(args, " "));
		command.args = args;

		return command;
	}

	void UserInterface::startConsole()
	{
		writeColor(" Calculatrice", Colors::GREEN);
		std::cout << std::endl << " Pour obtenir une liste des commandes utilisables, entrez \"?\" ou \"help\"." << std::endl;

		while (true)
		{
			try
			{
				// Ecoute les commandes entrées
				Command command = listenCommand();
				// Et les exécute
				handleCommand(command);
			}
			catch (const Error& e)
			{
				// Si une erreur a été générée, elle est traitée ici
				writeColor(" Une erreur est survenue : ", Colors::RED);
				std::cout << e.name << std::endl;
				writeColor("     Description : ", Colors::YELLOW);
				std::cout << e.description << std::endl;
			}
		}
	}

	void writeColor(std::string text, Colors color)
	{
		// Récupère le stream de la sortie de console, et lui assigne un attribut, conformément à https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
		std::cout << text;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(Colors::WHITE));
	}
}