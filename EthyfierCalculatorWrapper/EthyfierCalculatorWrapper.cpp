#include "pch.h"
#include "Ethyfier.h"
#include "EthyfierCalculatorWrapper.h"

namespace Ethyfier::UWP
{
	std::vector<Function> getFunctions(std::vector<int> data)
	{
		std::vector<Function> functions;
		for (auto& function : Payload(data).variables())
		{
			std::wstring name(function.name.begin(), function.name.end());
			std::wstring instructions(std::get<std::string>(function.value).begin(), std::get<std::string>(function.value).end());
			functions.push_back({ name, instructions });
		}
		return functions;
	}
}