#pragma once

#include <string>
#include <vector>

#include "Manager.hpp"

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
		inline Variable* setValue(std::string newValue) { m_value = newValue; return this; }
		std::string id() { return m_name; }
	private:
		std::string m_name;
		std::string m_value;
	};
	
	class Instruction
	{
	public:
		Instruction(Algorithm& algorithm, InstructionType type, std::vector<std::string> args) : m_algorithm(algorithm), m_type(type), m_args(args) {}
		void execute();
		std::string id;
	private:
		Algorithm& m_algorithm;
		InstructionType m_type;
		std::vector<std::string> m_args;
	};
	
	class Algorithm
	{
	public:
		inline Algorithm() : variableManager(new Manager::Manager<Variable>), instructionManager(new Manager::Manager<Instruction>) {}
		void execute();
		Manager::Manager<Variable>* variableManager;
		Manager::Manager<Instruction>* instructionManager;
	};


	Algorithm parseAlgorithm(std::string rawAlgorithm);
}