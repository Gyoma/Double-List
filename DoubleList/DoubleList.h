#pragma once
#include <iostream>
#include <cstdarg>
#include <fstream>

class Node
{
public:
	Node(int Val = 0, Node* Prev = nullptr, Node* Next = nullptr, Node* ptrForThis = nullptr, bool toTheEnd = true);
	Node(const Node& object);

	int get_value();

	Node* get_next();

	Node* get_previous();

	void set_value(int Value);

	void set_next(Node* Next);

	void set_previous(Node* Previous);

	Node& operator=(const Node& object);

private:
	int value;
	Node* previous;
	Node* next;
};

class DoubleList
{
public:

	DoubleList();
	DoubleList(int num, ...);
	DoubleList(const DoubleList& object);

	void push_front(int value);

	void push_back(int value);

	void push_key(int key, int value);

	void push_index(int index, int value);

	void pop_front();

	void pop_back();

	void pop_key(int key);

	void pop_index(int index);

	Node& find(int key);

	void copy();

	void clear();

	void print();

	int size();

	void add(int num, ...);

	void del(int num, ...);

	void set(int size, int limit = 100);

	void set(int* mas, int size);

	void set(const char *name);

	DoubleList& operator=(const DoubleList& object);

	DoubleList& operator+=(const DoubleList& object);

	DoubleList& operator-=(const DoubleList& object);

	Node& operator[](int ind);

	DoubleList operator+(const DoubleList& object);

	DoubleList operator-(const DoubleList& object);

	friend std::istream& operator >> (std::istream &s, DoubleList &object);

	friend std::ostream& operator << (std::ostream &s, DoubleList &object);

	~DoubleList();


private:

	int Size;
	Node* head;
	Node* tail;
};