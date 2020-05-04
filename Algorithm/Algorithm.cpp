#include "Algorithm.h"
#include "Core/Core.h"
#include "Core/Utils.h"

#include <iostream>
#include <string>
#include <vector>

namespace Calculatrice::Algorithm {
	Algorithm parseAlgorithm(std::string rawAlgorithm)
	{
		// Algorithme retourné par la fonction
		Algorithm* finalAlgorithm = new Algorithm();
		// Symboles servant à indenter le texte, permettant une souplesse de la syntaxe
		std::vector<std::string> indentationSymbols = { "\n", "\r", "\t" };
		// Liste de toutes les lignes

		std::vector<std::string> algorithm = Calculatrice::Utils::splitString(rawAlgorithm, indentationSymbols);
		// Supprimer les symboles d'indentation
		for (auto& i : indentationSymbols)
			while (Calculatrice::Utils::vectorIncludes(algorithm, i))
				algorithm.erase(algorithm.begin() + Calculatrice::Utils::firstIndexInVector(algorithm, i));
		// Et les lignes vides
		while (Calculatrice::Utils::vectorIncludes(algorithm, std::string("")))
			algorithm.erase(algorithm.begin() + Calculatrice::Utils::firstIndexInVector(algorithm, std::string("")));

		// S'exécute sur chaque ligne de l'algorithme
		for (auto& rawLine : algorithm)
		{
			// Commentaires
			if (rawLine[0] != ';')
			{
				// Sépare chaque mot de la ligne
				std::vector<std::string> line = Calculatrice::Utils::splitString(rawLine, { " " });

				// Supprime les espaces
				while (Calculatrice::Utils::vectorIncludes(line, std::string(" ")))
				{
					int index = Calculatrice::Utils::firstIndexInVector(line, std::string(" "));
					line.erase(line.begin() + index);
				}

				// Détermine l'instruction entrée, puis l'ajoute à l'algorithme si elle existe
				if (line[0] == "compare")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::COMPARE, { line[1], line[2] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "display")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::DISPLAY, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "displaytext")
				{
					std::vector<std::string> args;
					line.erase(line.begin());
					for (auto& word : line)
						args.push_back(word);
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::DISPLAYTEXT, args);
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "get")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::GET, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jump")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMP, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jumpeq")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMPEQ, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jumpdi")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMPDI, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jumpgt")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMPGT, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jumplt")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMPLT, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jumpge")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMPGE, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "jumple")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::JUMPLE, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "pop")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::POP, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "push")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::PUSH, { line[1] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				else if (line[0] == "set")
				{
					Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::SET, { line[1], line[2] });
					finalAlgorithm->currentFunction->instructionManager->add(instruction);
				}
				// Si aucune intruction n'est détectée, et que la ligne ne fait qu'un mot, alors c'est une déclaration de fonction
				else if (line.size() == 1)
				{
					finalAlgorithm->currentFunction = new Function(line[0]);
					finalAlgorithm->functionManager->add(finalAlgorithm->currentFunction);
				}
				else if (line.size() != 0)
					throw(Calculatrice::Utils::Error{ "Instruction inconnue.", "L'instruction \"" + line[0] + "\" que vous avez entrée n'est pas reconnu par le lecteur d'algorithme. Veuillez entrer \"?\" ou \"aide\" pour plus d'informations." });
			}
		}

		if (!finalAlgorithm->functionManager->get("main"))
			throw(Calculatrice::Utils::Error{ "Point d'entrée du programme introuvable.", "Aucun point d'entrée n'a été trouvé dans votre programme. Vous devez créer une fonction du nom de \"main\"" });

		return *finalAlgorithm;
	}

	void Instruction::execute()
	{
		switch (m_type)
		{
		case InstructionType::DISPLAY:
		{
			// S'exécute sur chaque membre de l'expression entrée. Sert à remplacer les noms de variables par leur valeur.
			std::vector<std::string> expression = Calculatrice::Core::serialize(m_args[0]);
			for (auto& i : expression)
			{
				// Si l'algorithme comporte une variable du nom du membre actuel
				Variable* variable = m_algorithm.variableManager->get(i);
				if (variable)
				{
					// Remplace ce membre par sa valeur
					int indexInExpression = Calculatrice::Utils::firstIndexInVector(expression, variable->name());
					expression[indexInExpression] = variable->value();
				}
			}
			// Affiche le résultat
			std::cout << Calculatrice::Core::solve(expression) << std::endl;
			break;
		}
		case InstructionType::DISPLAYTEXT:
		{
			for (auto& word : m_args)
				std::cout << word << " ";
			std::cout << std::endl;
			break;
		}
		case InstructionType::GET:
		{
			std::string value;
			std::cin >> value;
			m_algorithm.variableManager->set(m_args[0], new Variable(m_args[0], value));
			break;
		}
		case InstructionType::SET:
		{
			std::vector<std::string> expression = Calculatrice::Core::serialize(m_args[1]);
			// S'exécute sur chaque membre de l'expression entrée. Sert à remplacer les noms de variables par leur valeur.
			for (auto& i : expression)
			{
				// Si l'algorithme comporte une variable du nom du membre actuel
				Variable* variable = m_algorithm.variableManager->get(i);
				if (variable)
				{
					// Remplace ce membre par sa valeur
					int indexInExpression = Calculatrice::Utils::firstIndexInVector(expression, variable->name());
					expression[indexInExpression] = variable->value();
				}
			}
			// Si la variable existe, alors elle mise à jour, sinon, elle est mise à jour.
			m_algorithm.variableManager->set(m_args[0], new Variable(m_args[0], std::to_string(Calculatrice::Core::solve(expression))));
			break;
		}
		case InstructionType::COMPARE:
		{
			std::vector<double> members{};
			for (auto& arg : m_args)
			{
				std::vector<std::string> expression = Calculatrice::Core::serialize(arg);
				// S'exécute sur chaque membre de l'expression entrée. Sert à remplacer les noms de variables par leur valeur.
				for (auto& i : expression)
				{
					// Si l'algorithme comporte une variable du nom du membre actuel
					Variable* variable = m_algorithm.variableManager->get(i);
					if (variable)
					{
						// Remplace ce membre par sa valeur
						int indexInExpression = Calculatrice::Utils::firstIndexInVector(expression, variable->name());
						expression[indexInExpression] = variable->value();
					}
				}
				members.push_back(Calculatrice::Core::solve(expression));
			}
			m_algorithm.compare(members[0], members[1]);
			break;
		}
		case InstructionType::JUMP:
		{
			Function* function = m_algorithm.functionManager->get(m_args[0]);
			if (function)
				function->execute();
			else
				throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			break;
		}
		case InstructionType::JUMPEQ:
		{
			if ((m_algorithm.lastComparison() & ComparisonResult::EQUAL) == 0b1)
			{
				Function* function = m_algorithm.functionManager->get(m_args[0]);
				if (function)
					function->execute();
				else
					throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			}
			break;
		}
		case InstructionType::JUMPDI:
		{
			if ((m_algorithm.lastComparison() & ComparisonResult::DIFFERENT) == 0b10)
			{
				Function* function = m_algorithm.functionManager->get(m_args[0]);
				if (function)
					function->execute();
				else
					throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			}
			break;
		}
		case InstructionType::JUMPGE:
		{
			if (((m_algorithm.lastComparison() & ComparisonResult::EQUAL) == 0b1) || ((m_algorithm.lastComparison() & ComparisonResult::GREATER) == 0b100))
			{
				Function* function = m_algorithm.functionManager->get(m_args[0]);
				if (function)
					function->execute();
				else
					throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			}
			break;
		}
		case InstructionType::JUMPGT:
		{
			if ((m_algorithm.lastComparison() & ComparisonResult::GREATER) == 0b100)
			{
				Function* function = m_algorithm.functionManager->get(m_args[0]);
				if (function)
					function->execute();
				else
					throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			}
			break;
		}
		case InstructionType::JUMPLE:
		{
			if (((m_algorithm.lastComparison() & ComparisonResult::EQUAL) == 0b1) || ((m_algorithm.lastComparison() & ComparisonResult::SMALLER) == 0b1000))
			{
				Function* function = m_algorithm.functionManager->get(m_args[0]);
				if (function)
					function->execute();
				else
					throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			}
			break;
		}
		case InstructionType::JUMPLT:
		{
			if ((m_algorithm.lastComparison() & ComparisonResult::SMALLER) == 0b1000)
			{
				Function* function = m_algorithm.functionManager->get(m_args[0]);
				if (function)
					function->execute();
				else
					throw(Utils::Error{ "Fonction introuvable", "La fonction \"" + m_args[0] + "\" n'existe pas." });
			}
			break;
		}
		case InstructionType::POP:
		{
			m_algorithm.variableManager->set(m_args[0], new Variable(m_args[0], m_algorithm.pop()));
			break;
		}
		case InstructionType::PUSH:
		{
			std::vector<std::string> expression = Calculatrice::Core::serialize(m_args[0]);
			// S'exécute sur chaque membre de l'expression entrée. Sert à remplacer les noms de variables par leur valeur.
			for (auto& i : expression)
			{
				// Si l'algorithme comporte une variable du nom du membre actuel
				Variable* variable = m_algorithm.variableManager->get(i);
				if (variable)
				{
					// Remplace ce membre par sa valeur
					int indexInExpression = Calculatrice::Utils::firstIndexInVector(expression, variable->name());
					expression[indexInExpression] = variable->value();
				}
			}
			m_algorithm.push(std::to_string(Calculatrice::Core::solve(expression)));
			break;
		}
		}
	}

	void Function::execute()
	{
		for (auto& instruction : instructionManager->items())
		{
			instruction->execute();
		}
	}

	void Algorithm::execute()
	{
		functionManager->get("main")->execute();
	}

	std::string Algorithm::pop()
	{
		if (m_stack.size() == 0)
			throw(Utils::Error{ "Pile d'arguments vide.", "Vous avez tenté d'utiliser l'instruction \"pop\" alors que la pile était vide." });
		std::string value = m_stack.back();
		m_stack.pop_back();
		return value;
	}

	Algorithm* Algorithm::push(std::string value)
	{
		m_stack.push_back(value);
		return this;
	}

	int Algorithm::compare(double first, double second)
	{
		int result = 0;
		if (first == second)
			result |= ComparisonResult::EQUAL;
		if (first != second)
			result |= ComparisonResult::DIFFERENT;
		if (first < second)
			result |= ComparisonResult::SMALLER;
		if (first > second)
			result |= ComparisonResult::GREATER;
		m_lastComparison = result;
		return result;
	}
}