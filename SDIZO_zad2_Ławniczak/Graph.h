#pragma once

#include <iostream>

struct ListNode {
	int node;
	int weight;
	ListNode* next;
};

class Graph {
public:

	int edge_size;
	int node_size;

	int** adjMatrix;
	ListNode* adjList;
	
	Graph();
	~Graph();

	void displayList();
	void displayMatrix();
	void addEdge(int v1, int v2, int value);
	void makeGraph(int size);	//zmieniæ nazwê?? na init albo update
	void loadFromFile(std::string filename, bool moreParam);
	void generateRandom(int node_size, int density);

	void MST_kruskal();
};



