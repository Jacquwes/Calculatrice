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
		std::vector<std::string> indentationSymbols = { "\n", "\r", "\t", ";" };
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
			// Sépare chaque mot de la ligne
			std::vector<std::string> line = Calculatrice::Utils::splitString(rawLine, { " " });
			// Supprime les espaces
			while (Calculatrice::Utils::vectorIncludes(line, std::string(" ")))
			{
				int index = Calculatrice::Utils::firstIndexInVector(line, std::string(" "));
				line.erase(line.begin() + index);
			}

			// Détermine l'instruction entrée, puis l'ajoute à l'algorithme si elle existe
			if (line[0] == "set")
			{
				Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::ASSIGN, {line[1], line[2]});
				finalAlgorithm->currentFunction->instructionManager->add(instruction);
			}
			else if (line[0] == "display")
			{
				Instruction* instruction = new Instruction(*finalAlgorithm, InstructionType::DISPLAY, {line[1]});
				finalAlgorithm->currentFunction->instructionManager->add(instruction);
			}
			// Si aucune intruction n'est détectée, et que la ligne ne fait qu'un mot, alors c'est une déclaration de fonction
			else if (line.size() == 1)
			{
				finalAlgorithm->currentFunction = new Function(line[0]);
				finalAlgorithm->functionManager->add(finalAlgorithm->currentFunction);
			}
			else
				throw(Calculatrice::Utils::Error{ "Instruction inconnue.", "L'instruction \"" + line[0] + "\" que vous avez entrée n'est pas reconnu par le lecteur d'algorithme. Veuillez entrer \"?\" ou \"aide\" pour plus d'informations." });
		}

		if (!finalAlgorithm->functionManager->get("main"))
			throw(Calculatrice::Utils::Error{ "Point d'entrée du programme introuvable.", "Aucun point d'entrée n'a été trouvé dans votre programme. Vous devez créer une fonction du nom de \"main\"" });

		return *finalAlgorithm;
	}

	void Instruction::execute()
	{
		switch (m_type)
		{
		case Calculatrice::Algorithm::InstructionType::ASSIGN:
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
		case Calculatrice::Algorithm::InstructionType::DISPLAY:
		{
			// Idem qu'au dessus
			std::vector<std::string> expression = Calculatrice::Core::serialize(m_args[0]);
			for (auto& i : expression)
			{
				Variable* variable = m_algorithm.variableManager->get(i);
				if (variable)
				{
					int indexInExpression = Calculatrice::Utils::firstIndexInVector(expression, variable->name());
					expression[indexInExpression] = variable->value();
				}
			}
			// Affiche le résultat
			std::cout << Calculatrice::Core::solve(expression);
			break;
		}
		default:
			break;
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
}