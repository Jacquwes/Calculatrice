#include "Ethyfier.h"
#include "pch.h"

namespace Ethyfier
{
	std::vector<int> serialize(std::vector<struct variable> variables)
	{
		// Payload Ethyfier
		std::vector<int> payload{ static_cast<int>(variables.size()) };

		int header_size = 1;
		int body_size = 0;

		// Calculer la taille de l'en-tête
		for (size_t i = 0; i < variables.size(); i++)
			// 4 octets de description de la variable + taille du nom
			header_size += 4 + static_cast<int>(variables[i].name.size());

		// Créer l'en-tête
		for (const variable& var : variables)
		{
			// Taille du nom
			int var_name_size = static_cast<int>(var.name.size());
			// L'adresse de la valeur est située à la fin du corps du payload
			int address = header_size + body_size;

			// Convertit le nom en liste de chiffres
			std::vector<int> var_name;
			for (int character : var.name)
				var_name.push_back(character);

			// Augmente la taille du corps en fonction du type de la variable
			types var_type = (types)var.value.index();
			if (var_type == types::STR)
				body_size += (int)std::get<std::string>(var.value).length();
			else
				body_size++;

			// Ajoute la variable à la fin du payload
			// address & 0xff, (address & 0xff00) >> 8 sert à diviser l'adresse de la valeur sur deux octets,
			// faisant passer l'adresse maximale de 255 à 65535
			payload.insert(payload.end(), { var_name_size, (int)var_type, address & 0xff, (address & 0xff00) >> 8 });
			payload.insert(payload.end(), var_name.begin(), var_name.end());
		}

		// Créer le corps
		for (const struct variable& var : variables)
		{
			// Ajoute la valeur à la fin du payload
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

		// Le premier octect d'une variable est toujours la taille
		bitType bitType = bitType::SIZE;
		// Premier octet du payload
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

		// Lire l'en-tête
		for (size_t cursor = 1; cursor <= rawPayload.size(); cursor++)
		{
			// Si toutes les variables ont été lues
			if (variable_index >= variable_count)
				break;

			// En fonction de la nature de l'octet
			switch (bitType)
			{
			case bitType::SIZE:
			{
				// Créer une nouvelle variable
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
				// Retrouver l'adresse sur deux octets
				int lowerPart = rawPayload[cursor++];
				int higherPart = rawPayload[cursor] << 8;
				var->address = lowerPart | higherPart;
				bitType = bitType::NAME;
				break;
			}
			case bitType::NAME:
			{
				variableExtended* var = variables[variable_index];
				// Retrouver le nom de la variable
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

		// Lire le corps
		for (int i = 0; i < variable_count; i++)
		{
			variableExtended* var = variables[i];
			// Si la variable est la dernière, alors l'adresse suivante est mise à la valeur de la taille du payload
			int next_var = i == variable_count - 1 ? (int)rawPayload.size() : variables[i + 1]->address;


			if (var->type == types::STR)
			{
				std::string value;
				// Copie les caractères du nom dans la variable depuis le payload
				std::transform(rawPayload.begin() + var->address, rawPayload.begin() + next_var, std::back_inserter(value), [&](auto c) { return static_cast<char>(c); });
				var->value = value;
			}
			else
				var->value = rawPayload[var->address];

			this->variables_m.push_back({ var->name, var->value });
		}
	}

	std::vector<std::string> Payload::rawPayload() { return this->rawPayload_m; }
	std::vector<struct variable> Payload::variables() { return this->variables_m; }
}
