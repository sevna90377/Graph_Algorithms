#include "AdjacencyList.h"
#include <fstream>
#include "Heap.h"
#include "DisjointSet.h"
#include "List.h"

using namespace std;
 



AdjacencyList::AdjacencyList() {
	graph_size = 0;
	adjList = nullptr;
}
AdjacencyList::~AdjacencyList() {
	delete[] adjList;
}

void AdjacencyList::display() {

	cout << endl << "Graf w reprezentacji listowej: " << endl;

	for (int i = 0; i < graph_size; i++) {
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

void AdjacencyList::addEdge(int v1, int v2, int value) {

	//dla grafów nieskierowanych

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

void AdjacencyList::makeGraph(int size) {

	if (graph_size != 0) {
		delete[] adjList;
	}

	graph_size = size;

	adjList = new ListNode[graph_size];
	for (int i = 0; i < graph_size; i++) {
		adjList[i].node = i;
		adjList[i].weight = 0;
		adjList[i].next = nullptr;
	}
}

void AdjacencyList::loadFromFile(string fileName, bool moreParam) {

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
				addEdge(v1, v2, weight);
			}
		}
		myFile.close();
	}
	else {
		cout << "Nie uda³o siê otworzyæ pliku" << endl;
	}
}

void AdjacencyList::generateRandom(int node_size, int density, bool directed) {
	srand((unsigned int)time(0));
	if (node_size >= 2) {
		
		makeGraph(node_size);

		if (density == 100) {
			int weight;
			for (int i = 0; i < node_size; i++) {
				for (int j = i + 1; j < node_size; j++) {
					weight = rand() % 9 + 1;
					addEdge(i, j, weight);
				}
			}
		}
		else if(density == 99) {
			generateRandom(node_size, 100, false);
			int edge_percent = (int)round((float)node_size * (node_size - 1) / 200);
			
			int v1, v2;
			bool alreadyDeleted;
			ListNode* holder;
			
			for (int i = 0; i < edge_percent; i++) {
				do {
					alreadyDeleted = true;
					v1 = rand() % node_size;
					while ((v2 = rand() % node_size) == v1);

					holder = &adjList[v1];
					while (holder->next != nullptr) {
						if (holder->next->node == v2) {
							alreadyDeleted = false;
							holder->next = holder->next->next;
							holder = &adjList[v2];
							while ((holder = holder->next)->next->node != v1);
							holder->next = holder->next->next;
						}
						else {
							holder = holder->next;
						}
					}
				} while (alreadyDeleted);
			}
		}
		else {
			int edge_size = (int)round(density * node_size * (node_size - 1) / 200);

			int v1, v2, weight;
			bool alreadyExists;
			ListNode* holder;

			for (int i = 0; i < edge_size; i++) {
				do {
					alreadyExists = false;
					v1 = rand() % node_size;
					while ((v2 = rand() % node_size) == v1);

					holder = &adjList[v1];
					while (holder->next != nullptr) {
						holder = holder->next;
						if (holder->node == v2) {
							alreadyExists = true;
						}
					}
				} while (alreadyExists);

				weight = rand() % 9 + 1;
				addEdge(v2, v1, weight);
			}
		}

	}

}

void AdjacencyList::mst_kruskal() {

	List resultList;

	//utworzenie kolejek priorytetowych zawieraj¹cych krawêdzie grafu
	Edge e;

	Heap priorityHeap;
	ListNode* holder;
	for (int i = 0; i < graph_size; i++) {
		holder = &adjList[i];
		while (holder->next != nullptr) {
			holder = holder->next;
			if (holder->node > i) {
				e.v1 = i;
				e.v2 = holder->node;
				e.weight = holder->weight;
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

	resultList.display(0);
}

void AdjacencyList::mst_prim() {

	Heap heap;
	Edge edge;
	bool* visited = new bool[graph_size];
	for (int i = 1; i < graph_size; i++) {
		visited[i] = false;
	}
	List resultList;

	ListNode* holder;
	int currentNode = 0;

	visited[currentNode] = true;

	for (int i = 0; i < graph_size - 1; i++) {
		holder = &adjList[currentNode];
		while (holder->next != nullptr) {
			holder = holder->next;
			if (!visited[holder->node]) {
				edge.v1 = currentNode;
				edge.v2 = holder->node;
				edge.weight = holder->weight;
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

	resultList.display(0);
}