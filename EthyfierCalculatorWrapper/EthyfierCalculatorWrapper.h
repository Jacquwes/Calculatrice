#pragma once
namespace Ethyfier::UWP
{
	struct Function
	{
		std::wstring name;
		std::wstring instructions;
	};

	std::vector<Function> getFunctions(std::vector<int> data);
}