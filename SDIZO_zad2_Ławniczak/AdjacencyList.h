#pragma once

#include <iostream>

struct ListNode {
	int node;
	int weight;
	ListNode* next;
};

class AdjacencyList {
public:

	int graph_size;

	ListNode* adjList;

	AdjacencyList();
	~AdjacencyList();

	void display();
	void addEdge(int v1, int v2, int value);
	void makeGraph(int size);	//zmieniæ nazwê?? na init albo update
	void loadFromFile(std::string filename, bool moreParam);
	void generateRandom(int node_size, int density, bool directed);

	void mst_kruskal();
	void mst_prim();
};



