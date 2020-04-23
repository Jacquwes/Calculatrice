#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Calculatrice::UI {
	enum class Commands
	{
		HELP,
		QUIT,
		SOLVE,
	};

	struct Command
	{
		Commands command{};
		std::vector<std::string> args;
	};

	struct UserInterfaceOptions
	{

	};

	class UserInterface
	{
	public:
		UserInterface(UserInterfaceOptions options);

		void startConsole();

	private:
		void handleCommand(Command command);
		Command listenCommand();
		UserInterfaceOptions m_options;
	};

	struct Error
	{
		std::string name;
		std::string description;
	};
}
