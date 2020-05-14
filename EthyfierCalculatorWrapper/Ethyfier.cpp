#include "Ethyfier.h"
#include "pch.h"

namespace Ethyfier
{
	std::vector<int> serialize(std::vector<struct variable> variables)
	{
		// Ethyfier payload
		std::vector<int> payload{ static_cast<int>(variables.size()) };

		int header_size = 1;
		int body_size = 0;

		// Calculate the header size
		for (size_t i = 0; i < variables.size(); i++)
			header_size += 3 + static_cast<int>(variables[i].name.size());

		// Create header
		for (const struct variable var : variables)
		{
			int var_name_size = static_cast<int>(var.name.size());
			int address = header_size + body_size;
			std::vector<int> var_name;
			for (int character : var.name)
				var_name.push_back(character);

			types var_type = (types)var.value.index();
			if (var_type == types::STR)
				body_size += (int)std::get<std::string>(var.value).length();
			else
				body_size++;

			payload.insert(payload.end(), { var_name_size, (int)var_type, address });
			payload.insert(payload.end(), var_name.begin(), var_name.end());
		}

		// Add body
		for (const struct variable& var : variables)
		{
			switch (var.value.index())
			{
			case (int)types::BOOL:
				payload.push_back(std::get<bool>(var.value));
				break;
			case (int)types::INT:
				payload.push_back(std::get<int>(var.value));
				break;
			case (int)types::STR:
				payload.insert(payload.end(), std::get<std::string>(var.value).begin(), std::get<std::string>(var.value).end());
				break;
			}
		}

		return payload;
	}


	Payload::Payload(std::vector<int> rawPayload)
	{
		enum class bitType {
			SIZE,
			TYPE,
			ADDR,
			NAME
		};

		bitType bitType = bitType::SIZE;
		int variable_count = rawPayload[0];
		int variable_index = 0;

		struct variableExtended
		{
			int address = 0;
			int nameSize = 0;
			types type = types::BOOL;
			std::string name;
			std::variant<std::string, int, bool> value;
		};

		std::vector<struct variableExtended*> variables{};

		// Read variables properties from the header
		for (size_t cursor = 1; cursor <= rawPayload.size(); cursor++)
		{
			if (variable_index >= variable_count)
				break;

			switch (bitType)
			{
			case bitType::SIZE:
			{
				variableExtended* var = new variableExtended;
				var->nameSize = rawPayload[cursor];
				variables.push_back(var);
				bitType = bitType::TYPE;
				break;
			}
			case bitType::TYPE:
			{
				variableExtended* var = variables[variable_index];
				var->type = (types)rawPayload[cursor];
				bitType = bitType::ADDR;
				break;
			}
			case bitType::ADDR:
			{
				variableExtended* var = variables[variable_index];
				var->address = rawPayload[cursor];
				bitType = bitType::NAME;
				break;
			}
			case bitType::NAME:
			{
				variableExtended* var = variables[variable_index];
				for (int i = 0; i < var->nameSize; i++)
					var->name += (char)rawPayload[i < var->nameSize - 1 ? cursor++ : cursor];
				variable_index++;
				bitType = bitType::SIZE;
				break;
			}
			default:
				break;
			}
		}

		// Read values from body
		for (int i = 0; i < variable_count; i++)
		{
			variableExtended* var = variables[i];
			int next_var = i == variable_count - 1 ? (int)rawPayload.size() : variables[i + 1]->address; // next variable address


			if (var->type == types::STR)
			{
				std::string value;
				std::transform(rawPayload.begin() + var->address, rawPayload.begin() + next_var, std::back_inserter(value), [&](auto c) { return static_cast<char>(c); });
				var->value = value;
			}
			else
				// certainly useless code
				var->value = var->type == types::BOOL ? rawPayload[var->address] == 0 ? false : true : (int)rawPayload[var->address];

			this->variables_m.push_back({ var->name, var->value });
		}
	}

	std::vector<std::string> Payload::rawPayload() { return this->rawPayload_m; }
	std::vector<struct variable> Payload::variables() { return this->variables_m; }
}
