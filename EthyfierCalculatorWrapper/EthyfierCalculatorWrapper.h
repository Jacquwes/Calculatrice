#pragma once
namespace Ethyfier::UWP
{
	struct Function
	{
		std::wstring name;
		std::wstring instructions;
	};

	// Retourne une liste de fonctions à partir d'un payload Ethyfier
	std::vector<Function> getFunctions(std::vector<int> data);
}