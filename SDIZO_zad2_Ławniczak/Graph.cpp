#include "Graph.h"
#include <iostream>
#include <fstream>
#include "Heap.h"
#include "DisjointSet.h"

using namespace std;



Graph::Graph() {

	edge_size = 0;
	node_size = 0;	

	adjMatrix = nullptr;
	adjList = nullptr;
}
Graph::~Graph() {
	for (int i = 0; i < node_size; i++) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;

	delete[] adjList;
}

void Graph::displayList() {

	cout << endl << "Graf w reprezentacji listowej: " << endl;

	for (int i = 0; i < node_size; i++) {
		cout << i;

		ListNode* holder = adjList[i].next;

		while (holder != nullptr) {
			cout << " -> " << holder->node << ":" << holder->weight;
			holder = holder->next;
		}
		cout << endl;
	}

	cout << endl;
}

void Graph::displayMatrix() {

	cout << endl << "Graf w reprezentacji macierzowej: " << endl;

	cout << " ";
	for (int i = 0; i < node_size; i++) {
		cout << " " << i;
	}
	cout << endl;
	for (int i = 0; i < node_size; i++) {
		cout << i;
		for (int j = 0; j < node_size; j++) {
			cout << " " << adjMatrix[i][j];
		}
		cout << endl;
	}
}

void Graph::addEdge(int v1, int v2, int value) {

	//dla grafów nieskierowanych
	adjMatrix[v1][v2] = value;
	adjMatrix[v2][v1] = value;

	ListNode* holder = &adjList[v1];
	while (holder->next != nullptr) {
		holder = holder->next;
	}
	holder->next = new ListNode;
	holder = holder->next;
	holder->node = v2;
	holder->weight = value;
	holder->next = nullptr;

	holder = &adjList[v2];
	while (holder->next != nullptr) {
		holder = holder->next;
	}
	holder->next = new ListNode;
	holder = holder->next;
	holder->node = v1;
	holder->weight = value;
	holder->next = nullptr;
}

void Graph::makeGraph(int size) {

	if (node_size != 0) {
		for (int i = 0; i < node_size; i++) {
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;

		delete[] adjList;
	}
	
	node_size = size;

	adjMatrix = new int* [node_size];
	for (int i = 0; i < node_size; i++) {
		adjMatrix[i] = new int[node_size];
		for (int j = 0; j < node_size; j++) {
			adjMatrix[i][j] = 0;
		}
	}

	adjList = new ListNode[node_size];
	for (int i = 0; i < node_size; i++) {
		adjList[i].node = i;
		adjList[i].weight = 0;
		adjList[i].next = nullptr;
	}
}

void Graph::loadFromFile(string fileName, bool moreParam) {

	ifstream myFile;
	int v1,v2, weight;

	myFile.open(fileName);

	if (myFile.is_open())
	{
		if (moreParam) {

		}
		else {
			int size;
			myFile >> edge_size;
			myFile >> size;

			makeGraph(size);

			for (int i = 0; i < edge_size; i++) {
				myFile >> v1 >> v2 >> weight; 
				addEdge(v1, v2, weight);
			}
		}
		myFile.close();
	}
	else {
		cout << "Nie uda³o siê otworzyæ pliku" << endl;
	}

}

void Graph::generateRandom(int node_size, int density) {
	if(node_size >= 2){
		edge_size = (int)round(density * node_size * (node_size - 1) / 200);

		makeGraph(node_size);

		srand((unsigned int)time(0));
		int v1, v2, weight;

		for (int i = 0; i < edge_size; i++) {
			do {
				v1 = rand() % node_size;
				while ((v2 = rand() % node_size) == v1);
			} while (adjMatrix[v1][v2] != 0);
			weight = rand() % 10;
			addEdge(v2, v1, weight);
		}
	}
}

void Graph::MST_kruskal() {

	Graph resultGraph;
	resultGraph.makeGraph(node_size);

	//utworzenie kolejek priorytetowych zawieraj¹cych krawêdzie grafu
	Edge e;

	Heap matrixHeap;
	for (int i = 0; i < node_size; i++) {
		for (int j = 1 + i; j < node_size; j++) {
			if (e.weight = adjMatrix[i][j]) {
				e.v1 = i;
				e.v2 = j;
				matrixHeap.push(e);
			}
		}
	}

	Heap listHeap;
	ListNode* holder;
	for (int i = 0; i < node_size; i++) {
		holder = &adjList[i];
		while (holder->next != nullptr) {
			holder = holder->next;
			if (holder->node > i) {
				e.v1 = i;
				e.v2 = holder->node;
				e.weight = holder->weight;
				listHeap.push(e);
			}
		}
	}

	DisjointSet matrixSet(node_size);
	while(matrixHeap.heap_length > 0) {
		e = matrixHeap.pop();
		if (!matrixSet.isOneSet(e.v1, e.v2)) {
			resultList.addEdge(e);
			matrixSet.unionSets(e.v1, e.v2);
		}
	}

}