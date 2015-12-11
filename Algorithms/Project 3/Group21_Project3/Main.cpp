#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.h"

void CreateGraphs(std::ifstream &inputFile, std::vector<Graph> &orderedGraphs);

int main(int argc, char *argv[])
{
	int numberOfGraphs; 
	std::ifstream inputFile;
	std::vector<Graph> orderedGraphs;

	if (argc != 2) //validate number of arguments
	{
		std::cerr << "Program expects file path as only command-line argument.\n";
		exit(1);
	}

	inputFile.open(argv[1], std::fstream::in); //try to open file

	if (!inputFile.is_open()) //validate file 
	{
		std::cerr << "Could not open specified file.\n";
		exit(1);
	}

	inputFile >> numberOfGraphs; //parse number of graphs from file

	CreateGraphs(inputFile, orderedGraphs); //parse data from file

	inputFile.close();

	std::remove("output.txt"); // delete output file if necessary

	// find longest path for each graph
	for (int i = 0; i < numberOfGraphs; i++)
		orderedGraphs[i].printLongestPath();

	std::cout << std::endl;
	return 0;
}

void CreateGraphs(std::ifstream &inputFile, std::vector<Graph> &orderedGraphs)
{
	while (!inputFile.eof())
	{
		int numberOfVertices, numberOfEdges;
		inputFile >> numberOfVertices >> numberOfEdges;

		Graph orderedGraph(numberOfVertices, numberOfEdges); //create a new graph

		for (int i = 0; i < numberOfEdges; i++) //add edges to graph
		{
			int v, u;
			inputFile >> v >> u;

			orderedGraph.addEdge(v, u);
		}

		orderedGraphs.push_back(orderedGraph); //add graph to container
	}
}