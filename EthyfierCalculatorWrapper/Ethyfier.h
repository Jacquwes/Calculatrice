#pragma once

#include "pch.h"

namespace Ethyfier
{
	enum class types
	{
		STR,
		INT,
		BOOL,
	};

	struct variable {
		std::string name;
		std::variant<std::string, int, bool> value;
	};

	std::vector<int> serialize(std::vector<struct variable> variables);

	class Payload
	{
	public:
		Payload(std::vector<int> rawPayload);


		std::vector<std::string> rawPayload();
		std::vector<struct variable> variables();

	private:
		std::vector<std::string> rawPayload_m;
		std::vector<struct variable> variables_m;
	};
}
