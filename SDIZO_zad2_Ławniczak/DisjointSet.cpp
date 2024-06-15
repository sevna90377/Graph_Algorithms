#include "DisjointSet.h"

using namespace std;

DisjointSet::DisjointSet(int size) {

	set_size = size;
	parent = new int[size];
	rank = new int[size];

	for (int i = 0; i < size; i++) {
		makeSet(i);
	}
}

DisjointSet::~DisjointSet() {

	delete[] parent;
	delete[] rank;

}

void DisjointSet::makeSet(int x) {
	parent[x] = x;
	rank[x] = 0;
}

int DisjointSet::find(int x) {
	if (x != parent[x]) {
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

void DisjointSet::unionSets(int x, int y) {

	int rootX = find(x);
	int rootY = find(y);

	if (rootX == rootY) { return; }

	if (rank[rootX] < rank[rootY]) {
		parent[rootX] = rootY;
	}
	else if(rank[rootX] > rank[rootY]) {
		parent[rootY] = rootX;
	}
	else {
		parent[rootY] = rootX;
		rank[rootX]++;
	}
}

bool DisjointSet::isOneSet(int x, int y) {
	return find(x) == find(y);
}