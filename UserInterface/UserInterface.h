#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Calculatrice::UI {
	// Enumerateur de toutes les commandes
	enum class Commands
	{
		HELP,
		QUIT,
		SOLVE,
	};

	enum class Colors
	{
		GREEN = 10,
		CYAN = 11,
		RED = 12,
		YELLOW = 14,
		WHITE = 15
	};

	// Strucuture représentant une commande entrée par l'utilisateur
	struct Command
	{
		Commands command{};
		std::vector<std::string> args;
	};

	// Options de l'interface, pas encore implémentées
	struct UserInterfaceOptions
	{

	};

	// Structure représentant une erreur
	struct Error
	{
		std::string name;
		std::string description;
	};

	// Sert à écrire un texte de couleur
	void writeColor(std::string text, Colors color);

	// Interface utilisateur
	class UserInterface
	{
	public:
		UserInterface(UserInterfaceOptions options);

		// Démarrer l'interface dans une console
		void startConsole();

	private:
		// Execute une commande
		void handleCommand(Command command);
		// Demande à l'utilisateur d'entrer une commande
		Command listenCommand();
		UserInterfaceOptions m_options;
	};
}
