#pragma once

#include <iostream>

class AdjacencyMatrix {
public:

	int graph_size;

	int** adjMatrix;

	AdjacencyMatrix();
	~AdjacencyMatrix();

	void display();
	void addEdge(int v1, int v2, int value, bool directed);
	void makeGraph(int size);	//zmieniæ nazwê?? na init albo update
	void loadFromFile(std::string filename, bool moreParam);
	void generateRandom(int node_size, int density, bool directed);

	void mst_kruskal();
	void mst_prim();
};