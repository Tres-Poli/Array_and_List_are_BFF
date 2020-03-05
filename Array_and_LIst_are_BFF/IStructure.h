#pragma once
#include <string>

// Interface for list and array
class IStructure
{
public:
	virtual void create_and_fill(int size) = 0;
	virtual void create_from_file(std::string path) = 0;
	virtual void set(int size, int* values) = 0;
	virtual void insert(int id, int value) = 0;
	virtual void remove(int id) = 0;
	virtual void removevalue(int value) = 0;
	virtual int find(int id) = 0;
	virtual void findvalue(int value) = 0;
	virtual void print() = 0;
	virtual void sort() = 0;
};