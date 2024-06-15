#pragma once

#include <string>
#include "heap.h"

struct ListElement {
	Edge edge;
	ListElement* next;
	ListElement* previous;
};

class List {

public:

	//zmienne

	ListElement* headPointer;
	ListElement* tailPointer;

	int list_length;

	//metody

	List();
	~List();

	void addValue(Edge e);

	void display(int option);
};