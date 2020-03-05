#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "List.h"
#include "Array.h"
#include "IStructure.h"
#include <ctime>
#include <functional>

typedef void (IStructure::* MethodPtr)(int); // тайпдей на указатель на константный метод класса IStructure

class CommandInterpreter
{
private:
	Array _vector;
	List _linkedList;

	// Commands's values as string
	const char* _array = "array";
	const char* _list = "list";

	const char* _fillRand = "fill_rand";
	const char* _fillHand = "fill_hand";
	const char* _fillFile = "fill_file";

	const char* _insert = "insert";
	const char* _remove = "remove";
	const char* _removevalue = "removevalue";
	const char* _get = "find";
	const char* _getvalue = "findvalue";
	const char* _print = "print";
	const char* _sort = "sort";

	// Commands's values as string as enum's elements
	static enum Commands
	{
		Array,
		List,

		FillRand,
		FillByHand,
		FillByFile,
		Print,

		Insert,
		Remove,
		RemoveValue,
		GetValue,
		Get,
		Sort,

		Unrecognized
	};

	void ErrorMessage(const char* message)
	{
		std::cout << ">>> ERROR " << message << std::endl;
	}
	// Define enum element by string value
	int InterpreteCommand(std::string command)
	{
		if (command == _array)			return Array;
		if (command == _list)			return List;
		if (command == _fillRand)		return FillRand;
		if (command == _fillHand)		return FillByHand;
		if (command == _fillFile)		return FillByFile;
		if (command == _insert)			return Insert;
		if (command == _remove)			return Remove;
		if (command == _get)			return Get;
		if (command == _print)			return Print;
		if (command == _getvalue)		return GetValue;
		if (command == _removevalue)	return RemoveValue;
		if (command == _sort)			return Sort;
		return Unrecognized;
	}

	// Strategy definer
	// command contains commandName[0] and arguments [1], [2], [3], ...
	bool DefineStrategy(std::vector<std::string> command)
	{
		IStructure* structure = nullptr;
		int structChoice = InterpreteCommand(command[0]);
		if (command.size() < 1 || structChoice == Unrecognized)
		{
			ErrorMessage("missed argument");
			return false;
		}

		if (structChoice == Array) structure = &_vector;
		else structure = &_linkedList;

		int strategie = InterpreteCommand(command[1]);
		switch (strategie)
		{
			case FillRand: 
			{	
				if (command.size() < 3) ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					int size = std::atoi(command[2].c_str());
					structure->create_and_fill(size);
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case FillByHand:
			{
				if(command.size() < 4) ErrorMessage("missed argument");
				else
				{
					int* values = new int[command.size() - 3];
					for (int i = 3; i < command.size(); ++i) values[i - 3] = std::atoi(command[i].c_str());
					unsigned int start = clock();
					structure->set(std::atoi(command[2].c_str()), values);
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case FillByFile:
			{
				if(command.size() < 3) ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					structure->create_from_file(command[2]);
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case Insert:
			{
				if(command.size() < 4) ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					structure->insert(std::atoi(command[2].c_str()), std::atoi(command[3].c_str()));
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case Remove:
			{
				if (command.size() < 3)ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					structure->remove(std::atoi(command[2].c_str()));
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case RemoveValue:
			{
				if (command.size() < 3)ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					structure->removevalue(std::atoi(command[2].c_str()));
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case Get:
			{
				if (command.size() < 3)ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					std::cout << ">>> " << structure->find(std::atoi(command[2].c_str())) << std::endl;
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case GetValue:
			{
				if (command.size() < 3)ErrorMessage("missed argument");
				else
				{
					unsigned int start = clock();
					structure->findvalue(std::atoi(command[2].c_str()));
					unsigned int end = clock();
					std::cout << ">>> delay - " << end - start << std::endl;
				}
				break;
			}
			case Sort:
			{
				unsigned int start = clock();
				structure->sort();
				unsigned int end = clock();
				std::cout << ">>> delay - " << end - start << std::endl;
				break;
			}
			case Print:
			{
				structure->print();
				break;
			}
			case Unrecognized:
			{
				ErrorMessage("unrecognized command");
			}
		}
		return false;
	}

public:
	// Start command interpretter
	void Start()
	{
		std::vector<std::string> fullCommand;
		while (true)
		{
			std::cout << ">>> ";

			std::string currCommand;
			std::getline(std::cin, currCommand);
			if (currCommand.size() == 0) std::getline(std::cin, currCommand);

			std::string commandPart;
			for (int i = 0; i < currCommand.length(); ++i)
			{
				if (currCommand[i] == ' ' && !commandPart.empty())
				{
					fullCommand.push_back(commandPart);
					commandPart.clear();
				}
				else
				{
					commandPart.push_back(currCommand[i]);
				}
			}
			fullCommand.push_back(commandPart);
			if (DefineStrategy(fullCommand)) break;

			fullCommand.clear();
		}
	}
	~CommandInterpreter()
	{

	}
};