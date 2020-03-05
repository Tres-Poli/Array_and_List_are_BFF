#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "IStructure.h"

// Node structure as a main element of list
struct Node
{
	int value;
	Node* prev = nullptr;
	Node* next = nullptr;
};

class List : public IStructure
{
private:
	Node* _begin = nullptr;
	Node* _end = nullptr;

	int _size;

	// Drop method: deletes all nodes in list
	void drop()
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			Node* tmp = curr->next;
			delete(curr);
			curr = tmp;
		}
		_begin = _end = nullptr;
	}

public: 
	List()
	{
		_size = 0;
		srand(time(NULL));
	}
	// Add a new node with value from arguments to the back of the list
	void push_back(int value)
	{
		Node* node = new Node();
		node->value = value;
		if (_begin == nullptr && _end == nullptr)
		{
			_end = _begin = node;
		}
		else
		{
			_end->next = node;
			node->prev = _end;
			_end = node;
		}
		_size++;
	}
	// Add a new node with value from arguments to the front of the list
	void push_front(int value)
	{
		Node* node = new Node();
		node->value = value;
		if (_begin == nullptr && _end == nullptr)
		{
			_end = _begin = node;
		}
		else
		{
			_begin->prev = node;
			node->next = _begin;
			node->prev = nullptr;
			_begin = node;
		}
		_size++;
	}
	// Delete one element from the back of the list
	void pop_back()
	{
		if (_begin == nullptr && _end == nullptr)
			return;
		if (_begin == _end && _begin != nullptr)
		{
			delete(_begin);
			_begin = _end = nullptr;
		}
		else
		{
			_end->prev->next = nullptr;
			Node* toDelete = _end;
			_end = _end->prev;

			delete(toDelete);
		}
		_size--;
	}
	// Delete one element from the front of the list
	void pop_front()
	{
		if (_begin == nullptr && _end == nullptr)
			return;
		if (_begin == _end && _begin != nullptr)
		{
			delete(_begin);
			_begin = _end = nullptr;
		}
		else
		{
			_begin->next->prev = nullptr;
			Node* toDelete = _begin;
			_begin = _begin->next;

			delete(toDelete);
		}
		_size--;
	}
	// Inirialize a list with random values
	void create_and_fill(int size)
	{
		if(_begin != nullptr) drop();
		for (int i = 0; i < size; ++i)
			push_back(rand() % 100);
	}
	// Setter for list
	void set(int size, int* values)
	{
		if (_begin != nullptr) drop();
		_size = size;
		for (int i = 0; i < _size; ++i)
			push_back(values[i]);
	}
	// Initialize a list with file, which contain values
	void create_from_file(std::string path)
	{
		if (_begin != nullptr) drop();
		std::ifstream* stream = new std::ifstream(path);
		std::string buff;
		int counter = 0;
		while (!stream->eof())
		{
			std::getline(*stream, buff);
			push_back(std::atoi(buff.c_str()));
			counter++;
		}
		_size = counter;
		delete(stream);
	}
	// Return value of element with corresponding id
	int find(int id)
	{
		if (id > _size || id < 0) return INT_MIN;
		Node* curr = _begin;
		for(int i = 1; i < id; ++i)
		{
			curr = curr->next;
		}
		return curr->value;
	}
	// Find and print all elements with corresponding value
	void findvalue(int value)
	{
		Node* curr = _begin;
		int counter = 0;
		while (curr != nullptr)
		{
			counter++;
			if (curr->value == value)
			{
				std::cout << " id - " << counter << std::endl;
			}
			curr = curr->next;
		}
	}
	// Insert a new element with corresponding id
	void insert(int id, int value)
	{
		if (id > _size) return;
		if (id == 0)
		{
			push_front(value);
			return;
		}
		if (id == _size)
		{
			push_back(value);
			return;
		}
		Node* toInsert = new Node();
		toInsert->value = value;
		Node* curr = _begin;
		for (int i = 1; i < id - 1; ++i)
		{
			curr = curr->next;
		}
		curr->next->prev = toInsert;
		toInsert->next = curr->next;
		toInsert->prev = curr;
		curr->next = toInsert;
		_size++;
	}
	// Remove element with corresponding id
	void remove(int id)
	{
		if (id > _size || id < 0) return;
		if (id == 1)
		{
			pop_front();
			return;
		}
		if (id == _size)
		{
			pop_back();
			return;
		}
		Node* curr = _begin;
		for (int i = 1; i < id - 1; ++i)
		{
			curr = curr->next;
		}
		Node* tmp = curr->next;
		curr->next->next->prev = curr;
		curr->next = curr->next->next;

		delete(tmp);
		_size--;
	}
	// Remove ALL values with corresponding value
	void removevalue(int value)
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->value == value)
			{
				if (curr == _begin)
				{
					curr = curr->next;
					pop_front();
				}
				else if (curr == _end)
				{
					curr = curr->next;
					pop_back();
				}
				else
				{
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
					Node* tmp = curr;
					curr = curr->next;
					delete(tmp);
				}
			}
			else
			{
				curr = curr->next;
			}
		}
	}
	// Sort list in ascending order
	void sort()
	{
		Node* curr = _begin;
		for (int i = 0; i < _size - 1; i++)
		{
			Node* currSecondary = _begin;;
			for (int j = 0; j < _size - i - 1; j++)
			{
				if (currSecondary->value > currSecondary->next->value)
				{
					Swap(&currSecondary->value, &currSecondary->next->value);
				}
				currSecondary = currSecondary->next;
			}
			curr = curr->next;
		}
	}
	// Swap two values by address
	void Swap(int* a, int* b)
	{
		int buff = *a;
		*a = *b;
		*b = buff;
	}
	// Print whole list
	void print()
	{
		Node* curr = _begin;
		int counter = 1;
		std::cout << "\n";
		while (curr != nullptr)
		{
			Node* tmp = curr->next;
			std::cout << counter << ": " << curr->value << std::endl;
			curr = tmp;
			counter++;
		}
		std::cout << "\n";
	}
	// Destructor for cleaning memory
	~List()
	{
		drop();
	}
};