#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "IStructure.h"

class Array : public IStructure
{
private:
	int _init_value = 10;
	int* _curr_array;
	int _curr_size;
	int _sign_size;

	// Drop array and resize it with corresponding size value
	void dropresize(int size)
	{
		delete[] _curr_array;
		_curr_array = new int[size];
		_curr_size = size;
		_sign_size = 0;
	}
	// Copies array and resize it 
	void copyresize()
	{
		int* new_arr = new int[_curr_size + 10];
		for (int i = 0; i < _sign_size; ++i)
		{
			new_arr[i] = _curr_array[i];
		}
		delete[] _curr_array;
		_curr_array = new_arr;
		_curr_size += 10;
	}
public:
	Array()
	{
		_curr_array = new int[_init_value];
		_curr_size = _init_value;
		_sign_size = 0;
		srand(time(NULL));
	}
	// Create new array instanse if needed and fill it with random values
	void create_and_fill(int size)
	{
		dropresize(size);
		foreach([](int* p) -> void { *p = rand() % 100; });
		_sign_size = size;
	}
	// Create a new array and fill it with values from file
	void create_from_file(std::string path)
	{
		dropresize(10);
		_curr_size = 10;
		_sign_size = 0;
		std::ifstream* stream = new std::ifstream(path);
		std::string buff;
		int counter = 0;
		while (!stream->eof())
		{
			if (_sign_size == _curr_size) copyresize();
			std::getline(*stream, buff);
			_curr_array[counter] = std::atoi(buff.c_str());
			counter++;
			_sign_size++;
		}
		delete(stream);
	}
	// Setter
	void set(int size, int* values)
	{
		_curr_size = size;
		_sign_size = size;
		_curr_array = values;
	}
	// Insert corresponding value with corresponding id
	void insert(int id, int value)
	{
		if (id > _sign_size) return;
		if (_sign_size == _curr_size) copyresize();
		for (int i = _sign_size; i >= id; --i)
		{
			_curr_array[i + 1] = _curr_array[i];
		}
		_curr_array[id] = value;
		_sign_size++;
	}
	// Removes element with corresponding id
	void remove(int id)
	{
		for (int i = id; i < _sign_size - 1; ++i)
		{
			_curr_array[i] = _curr_array[i + 1];
		}
		_sign_size--;
	}
	// Removes ALL values with corresponding value
	void removevalue(int value)
	{
		for (int i = 0; i < _sign_size; ++i)
		{
			if (_curr_array[i] == value)
				remove(i);
		}
	}
	// Find and return element with corresponding id
	int find(int id)
	{
		if (id <= _sign_size - 1 || id < 0) return _curr_array[id];
		else return INT_MIN;
	}
	// Fing and print all element with corresponding values
	void findvalue(int value)
	{
		for (int i = 0; i < _curr_size; ++i)
		{
			if (_curr_array[i] == value)
			{
				std::cout <<" id - " << i << std::endl;
			}
		}
	}
	// Iterates though array (just for fun)
	void foreach(void(*func)(int*))
	{
		for (int* i = _curr_array; i < _curr_array + _curr_size; ++i)
			func(i);
	}
	// Print whole array
	void print()
	{
		int counter = 0;
		std::cout << "\n";
		for (int i = 0; i < _sign_size; ++i)
		{
			std::cout << counter << ": " << _curr_array[i] << std::endl;
			counter++;
		}
		std::cout << "\n";
	}
	// Sort array in ascending order
	void sort()
	{
		for (int i = 0; i < _sign_size - 1; i++)
		{
			for (int j = 0; j < _sign_size - i - 1; j++)
			{
				if (_curr_array[j] > _curr_array[j + 1])
				{
					Swap(&_curr_array[j], &_curr_array[j + 1]);
				}
			}
		}
	}
	// Swap two values by address
	void Swap(int* a, int* b)
	{
		int buff = *a;
		*a = *b;
		*b = buff;
	}
	// Destructor for cleaning memory
	~Array()
	{
		delete[] _curr_array;
	}
};