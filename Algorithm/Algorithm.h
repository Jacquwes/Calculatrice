#pragma once

#include <string>
#include <vector>

#include "Manager.hpp"

namespace Calculatrice::Algorithm {
	enum class InstructionType
	{
		DISPLAY,
		DISPLAYTEXT,
		GET,
		JUMP,
		POP,
		PUSH,
		SET
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
	private:
		Algorithm& m_algorithm;
		InstructionType m_type;
		std::vector<std::string> m_args;
	};

	class Function
	{
	public:
		inline Function(std::string name) : instructionManager(new Manager::Manager<Instruction>), m_name(name) {}
		Manager::Manager<Instruction>* instructionManager;
		void execute();

		std::string id() { return m_name; }
	private:
		std::string m_name;
	};
	
	class Algorithm
	{
	public:
		inline Algorithm() : variableManager(new Manager::Manager<Variable>), functionManager(new Manager::Manager<Function>), currentFunction(nullptr) {}
		void execute();
		Manager::Manager<Variable>* variableManager;
		Manager::Manager<Function>* functionManager;
		Function* currentFunction;

		std::string pop();
		Algorithm* push(std::string value);
	private:
		std::vector<std::string> m_stack;
	};


	Algorithm parseAlgorithm(std::string rawAlgorithm);
}