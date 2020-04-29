#pragma once

#include <string>
#include <vector>

namespace Calculatrice::Algorithm {
	enum class InstructionType
	{
		ASSIGN,
		DISPLAY,
	};

	class Algorithm;
	class Variable
	{
	public:
		inline Variable(std::string name, std::string value) : m_name(name), m_value(value) {}

		inline std::string name() { return m_name; }
		inline std::string value() { return m_value; }
		inline void setValue(std::string newValue) { m_value = newValue; };
	private:
		std::string m_name;
		std::string m_value;
	};
	
	class Instruction
	{
	public:
		Instruction(Algorithm& algorithm, InstructionType type, std::vector<std::string> args) : m_algorithm(algorithm), m_type(type), m_args(args) {}
		void execute();
	private:
		Algorithm& m_algorithm;
		InstructionType m_type;
		std::vector<std::string> m_args;
	};
	
	class Algorithm
	{
	public:
		void execute();
		inline Algorithm* addInstruction(Instruction instruction) { m_instructions.push_back(instruction); return this; }
		inline Algorithm* addVariable(Variable variable) { m_variables.push_back(variable); return this; }
		inline std::vector<Variable> variables() { return m_variables; }
		inline std::vector < std::string> variablesNames() {
			std::vector<std::string> vect;
			for (auto& i : m_variables)
				vect.push_back(i.name());
			return vect;
		}
	private:
		std::vector<Instruction> m_instructions;
		std::vector<Variable> m_variables;
	};


	Algorithm parseAlgorithm(std::string rawAlgorithm);
}