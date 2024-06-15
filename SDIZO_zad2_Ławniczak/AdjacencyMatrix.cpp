#include "AdjacencyMatrix.h"
#include <fstream>
#include "Heap.h"
#include "DisjointSet.h"
#include "List.h"

using namespace std;

#define BIG_WEIGHT = 11;

AdjacencyMatrix::AdjacencyMatrix() {
	graph_size = 0;
	adjMatrix = nullptr;
}
AdjacencyMatrix::~AdjacencyMatrix() {
	for (int i = 0; i < graph_size; i++) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
}


void AdjacencyMatrix::display() {

	cout << endl << "Graf w reprezentacji macierzowej: " << endl;

	cout << " ";
	for (int i = 0; i < graph_size; i++) {
		cout << " " << i;
	}
	cout << endl;
	for (int i = 0; i < graph_size; i++) {
		cout << i;
		for (int j = 0; j < graph_size; j++) {
			cout << " " << adjMatrix[i][j];
		}
		cout << endl;
	}
}

void AdjacencyMatrix::addEdge(int v1, int v2, int value, bool directed) {

	adjMatrix[v1][v2] = value;
	//dla grafów nieskierowanych
	if(!directed) adjMatrix[v2][v1] = value;
}

void AdjacencyMatrix::makeGraph(int size) {

	if (graph_size != 0) {
		for (int i = 0; i < graph_size; i++) {
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
	}

	graph_size = size;

	adjMatrix = new int* [graph_size];
	for (int i = 0; i < graph_size; i++) {
		adjMatrix[i] = new int[graph_size];
		for (int j = 0; j < graph_size; j++) {
			adjMatrix[i][j] = 0;
		}
	}
}

void AdjacencyMatrix::loadFromFile(string fileName, bool moreParam) {

	if(!moreParam){
		ifstream myFile;
		int edge_size, node_size, v1, v2, weight;

		myFile.open(fileName);

		if (myFile.is_open())
		{
			if (moreParam) {

			}
			else {
				myFile >> edge_size;
				myFile >> node_size;

				makeGraph(node_size);

				for (int i = 0; i < edge_size; i++) {
					myFile >> v1 >> v2 >> weight;
					addEdge(v1, v2, weight, false);
				}
			}
			myFile.close();
		}
		else {
			cout << "Nie uda³o siê otworzyæ pliku" << endl;
		}
	}

}
/*
void AdjacencyMatrix::generateRandom(int node_size, int density, bool directed) {
	srand((unsigned int)time(0));

	if (node_size >= 2) {

		makeGraph(node_size);

		if (density == 100) {
			int weight;
			for (int i = 0; i < node_size; i++) {
				for (int j = i + 1; j < node_size; j++) {
					weight = rand() % 9 + 1;
					addEdge(i, j, weight, false);
				}
			}
		}
		else if (density == 99) {
			generateRandom(node_size, 100);
			int edge_percent = (int)round((float)node_size * (node_size - 1) / 200);

			int v1, v2;
			bool alreadyDeleted;

			for (int i = 0; i < edge_percent; i++) {
				do {
					alreadyDeleted = true;
					v1 = rand() % node_size;
					while ((v2 = rand() % node_size) == v1);

					if (adjMatrix[v1][v2] != 0) {
						adjMatrix[v1][v2] = 0;
						adjMatrix[v2][v1] = 0;
						alreadyDeleted = false;
					}
				} while (alreadyDeleted);
			}
		}
		else {
			int edge_size = (int)round(density * node_size * (node_size - 1) / 200);

			int v1, v2, weight;

			for (int i = 0; i < edge_size; i++) {
				do {
					v1 = rand() % node_size;
					while ((v2 = rand() % node_size) == v1);
				} while (adjMatrix[v1][v2] != 0);
				weight = rand() % 9 + 1;
				addEdge(v2, v1, weight, false);
			}
		}
	}
}
*/

void AdjacencyMatrix::mst_kruskal() {

	List resultList;

	//utworzenie kolejek priorytetowych zawieraj¹cych krawêdzie grafu
	Edge e;

	Heap priorityHeap;
	for (int i = 0; i < graph_size; i++) {
		for (int j = 1 + i; j < graph_size; j++) {
			if (e.weight = adjMatrix[i][j]) {
				e.v1 = i;
				e.v2 = j;
				priorityHeap.push(e);
			}
		}
	}

	DisjointSet disjointSet(graph_size);
	while (priorityHeap.heap_length > 0) {
		e = priorityHeap.pop();
		if (!disjointSet.isOneSet(e.v1, e.v2)) {
			resultList.addValue(e);
			disjointSet.unionSets(e.v1, e.v2);
		}
	}

	resultList.display(1);
}

void AdjacencyMatrix::mst_prim() {

	Heap heap;
	Edge edge;
	bool* visited = new bool[graph_size];
	for (int i = 1; i < graph_size; i++) {
		visited[i] = false;
	}
	List resultList;

	int currentNode = 0;

	visited[currentNode] = true;

	for (int i = 0; i < graph_size - 1; i++) {
		for (int j = 0; j < graph_size; j++) {
			if (!visited[j] && adjMatrix[currentNode][j] > 0) {
				edge.v1 = currentNode;
				edge.v2 = j;
				edge.weight = adjMatrix[currentNode][j];
				heap.push(edge);
			}
		}

		do {
			edge = heap.pop();
		} while (visited[edge.v2]);

		resultList.addValue(edge);
		visited[edge.v2] = true;
		currentNode = edge.v2;
	}

	resultList.display(1);
}

void AdjacencyMatrix::generateRandom(int node_size, int density, bool directed) {

	if(node_size >= 2) {
		makeGraph(node_size);
		int minDensity = (int)ceil((float)(node_size - 1) / (node_size * (node_size - 1) / 2) * 100);

		if (density == 100) {

		}
		else if (density == 99) {

		}else if(minDensity <= density) {
			// weight 9
			// min edges = node_size - 1
			// max edges = node_size * (node_size - 1) / 2
			int edge_min = node_size - 1;
			int edge_size = (int)round((float)density * node_size * (node_size - 1) / 200);
			bool* visited = new bool[graph_size];
			for (int i = 1; i < graph_size; i++) {
				visited[i] = false;
			}

			int v1, v2, weight;

			int currentNode = 0;
			visited[currentNode] = true;

			for (int i = 0; i < edge_min; i++) {
				do {
					while ((v2 = rand() % node_size) == currentNode);
					} while(visited[v2]);
					weight = rand() % 9 + 1;
					addEdge(currentNode, v2, weight, false);
					currentNode = v2;
			}
		}
		else {
			cout << "Podana liczba krawêdzi jest mniejsza od 2 lub gêstoœæ jest zbyt ma³a by utworzyæ graf spójny." << endl;
			cout << "Minimalna gêstoœæ: " << minDensity << endl;
		} 
	}




}