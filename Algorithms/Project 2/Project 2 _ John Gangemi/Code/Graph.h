#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph
{
public:
	Graph();

	void addVertex(Vertex v);
	void addEdge(int v, int u, int distance);

	std::vector<Vertex> getVertexList();
	std::vector<Edge> getEdgeList();
	std::vector<int> getNeighbor(Vertex v);
	std::vector<int> getNeighbor(int id);
	
private:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
};

#endif
