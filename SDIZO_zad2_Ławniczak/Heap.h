#pragma once

#include <iostream>

struct Edge {
	int v1, v2, weight;
};

class Heap {
public:

	Edge* rootPointer;
	int heap_length;
	

	Heap();
	~Heap();

	void push(Edge e);
	Edge pop();
	void heapifyUp(int i);
	void heapifyDown(int i);

	void display(std::string sp, std::string sn, int from);
};