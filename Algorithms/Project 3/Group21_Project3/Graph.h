#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <iostream>
#include <fstream>
#include <vector>

class Graph
{
public:
	Graph(int numVertices, int numEdges);

	void addEdge(int source, int target); // add edge to edge list
	void printLongestPath(); // print number of edges and edge IDs in longest path
	int getNumVertices();
	int getNumEdges();

private:
	void buildMemo(); // add initial edges to 2D array memo
	void findLongestPath(); // find longest path in graph using 2D array memo

	int numVertices;
	int numEdges;
	std::vector<Edge> edges; // edge list
	std::vector<int> longestPath; // list of vertices in longest path
	std::vector< std::vector<int> > memo; // 2D array for memoization
};

#endif

