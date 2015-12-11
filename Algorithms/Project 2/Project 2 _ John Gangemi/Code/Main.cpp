#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "Graph.h"


void FindVertices(const int row, const int column, std::ifstream &file, std::vector< std::vector<Vertex> > &maze, Graph &digraph);
void FindEdges(const int row, const int column, std::vector< std::vector<Vertex> > maze, Graph &digraph);
void DFS(Graph digraph, std::stack<int> &path);
void PrintSolution(Graph digraph, std::stack<int> sortedPath);


int main(int argc, char *argv[])
{
	// validate number of arguments
	if (argc != 2)
	{
		std::cerr << "Program expects file path as only command-line argument.\n";
		exit(1);
	}

	// validate file
	std::ifstream file(argv[1]);
	if (!file.is_open())
	{
		std::cerr << "Could not open specified file.\n";
		exit(1);
	}

	// create graph
	Graph digraph;

	// parse size of maze
	int row, column;
	file >> row >> column;

	// create maze
	std::vector< std::vector<Vertex> > maze(row, std::vector<Vertex>(column));

	// add vertices to graph
	FindVertices(row, column, file, maze, digraph);

	// add edges to graph
	FindEdges(row, column, maze, digraph);

	// apply modified, non-recursive DFS algorithm
	std::stack<int> path;
	DFS(digraph, path);

	// reverse path
	std::stack<int> sortedPath;
	while (!path.empty())
	{
		sortedPath.push(path.top());
		path.pop();
	}

	// print solution to terminal
	PrintSolution(digraph, sortedPath);
	
	std::cout << std::endl;
	return 0;
}

void FindVertices(const int row, const int column, std::ifstream &file, std::vector< std::vector<Vertex> > &maze, Graph &digraph)
{
	int id = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			// read text from file
			std::string text;
			file >> text;

			// create Vertex
			Vertex v;
			if (text.length() > 1)
			{
				v.setColor(text[0]);
				v.setDirection(text.substr(2));
			}
			v.setId(id);
			id++;

			maze[i][j] = v;
			digraph.addVertex(v);
		}
	}

	file.close();
}

void FindEdges(const int row, const int column, std::vector< std::vector<Vertex> > maze, Graph &digraph)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			std::string direction = maze[i][j].getDirection();
			int x = i;
			int y = j;
			int distance = 0;

			// if possible, move to next vertex in maze
			while ((x < row && y < column) && (x >= 0 && y >= 0))
			{
				if (direction == "N") x--;
				else if (direction == "S") x++;
				else if (direction == "E") y++;
				else if (direction == "W") y--;
				else if (direction == "NE") { x--; y++; }
				else if (direction == "NW") { x--; y--; }
				else if (direction == "SE") { x++; y++; }
				else if (direction == "SW") { x++; y--; }
				else break;

				distance++;

				// check if maze[x][y] is adjacent to maze[i][j]
				if ((x < row && y < column) && (x >= 0 && y >= 0))
					if (maze[i][j].getColor() != maze[x][y].getColor())
						digraph.addEdge(maze[i][j].getId(), maze[x][y].getId(), distance);
			}
		}
	}
}

void DFS(Graph digraph, std::stack<int> &path)
{
	std::vector<Vertex> vertexList = digraph.getVertexList();
	int id = 0;

	// initialize stack with first vertex
	vertexList[id].setDiscovered(true);
	path.push(id);

	// traverse graph until path is found
	while (!path.empty())
	{
		bool discoveredVertex = false;
		std::vector<int> neighbors = digraph.getNeighbor(id);

		// iterate through all neighbors 
		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			if (vertexList[neighbors[i]].isDiscovered() == false)
			{
				id = neighbors[i];
				vertexList[id].setDiscovered(true);
				path.push(id);
				discoveredVertex = true;
				break;
			}
		}

		// disregard non-path vertex
		if (discoveredVertex == false)
		{
			path.pop();
			id = path.top();
		}

		// path is complete
		if (id == vertexList.size() - 1)
			break;
	}
}

void PrintSolution(Graph digraph, std::stack<int> sortedPath)
{
	std::ofstream file;
	file.open("output.txt", std::ofstream::out);
	if (!file.is_open())
	{
		std::cerr << "Could not write to output file.\n";
		exit(1);
	}

	std::vector<Vertex> vertexList = digraph.getVertexList();
	std::vector<Edge> edgeList = digraph.getEdgeList();

	// pop elements from sorted stack
	while (sortedPath.size() > 1)
	{
		int v = sortedPath.top();
		sortedPath.pop();
		int u = sortedPath.top();

		for (unsigned int i = 0; i < edgeList.size(); i++)
			if (edgeList[i].getV() == v && edgeList[i].getU() == u)
			{
				file << edgeList[i].getDistance() << vertexList[v].getDirection() << " ";
				std::cout << edgeList[i].getDistance() << vertexList[v].getDirection() << " ";
			}
	}

	file.close();
}
