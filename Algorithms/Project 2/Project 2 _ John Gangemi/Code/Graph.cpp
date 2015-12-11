#include "Graph.h"


Graph::Graph() {}

void Graph::addVertex(Vertex v) { this->vertices.push_back(v); }

void Graph::addEdge(int v, int u, int distance) { this->edges.push_back(Edge(v, u, distance)); }

std::vector<Vertex> Graph::getVertexList() { return this->vertices; }

std::vector<Edge> Graph::getEdgeList() { return this->edges; }

std::vector<int> Graph::getNeighbor(Vertex v)
{
	std::vector<int> neighborIds;

	for (unsigned int i = 0; i < this->edges.size(); i++)
		if (this->edges[i].getV() == v.getId())
			neighborIds.push_back(this->edges[i].getU());

	return neighborIds;
}

std::vector<int> Graph::getNeighbor(int id)
{
	std::vector<int> neighborIds;

	for (unsigned int i = 0; i < this->edges.size(); i++)
		if (this->edges[i].getV() == id)
			neighborIds.push_back(this->edges[i].getU());

	return neighborIds;
}

