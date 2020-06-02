#pragma once

#include "pch.h"

namespace Ethyfier
{
	// Types supportés par Ethyfier
	enum class types
	{
		STR,
		INT,
		BOOL,
	};

	// Représente une variable
	struct variable {
		std::string name;
		// Variable pouvant avoir plusieurs types
		std::variant<std::string, int, bool> value;
	};

	//Convertit une liste de variables en payload Ethyfier
	std::vector<int> serialize(std::vector<variable> variables);

	// Permet d'utiliser un payload Ethyfier
	class Payload
	{
	public:
		// Constructeur, à partir d'un payload Ethyfier
		Payload(std::vector<int> rawPayload);


		std::vector<std::string> rawPayload();
		std::vector<struct variable> variables();

	private:
		std::vector<std::string> rawPayload_m;
		std::vector<struct variable> variables_m;
	};
}
