#pragma once

#include <vector>

class DisjointSet {
public:

    int* parent;
    int* rank;
    int set_size;

    DisjointSet(int n);
    ~DisjointSet();

    void makeSet(int x);
    void unionSets(int x, int y);
    bool isOneSet(int x, int y);
    int find(int x);
};