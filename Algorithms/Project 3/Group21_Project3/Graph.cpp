#include "Graph.h"


Graph::Graph(int numVertices, int numEdges)
	:numVertices(numVertices), numEdges(numEdges)
{
	this->memo.resize(numVertices, std::vector<int>(numVertices, 0));
}

void Graph::addEdge(int source, int target)
{
	this->edges.push_back(Edge(source, target));
}

void Graph::buildMemo()
{
	// add markers for edges to 2D array memo
	for (unsigned int i = 0; i < this->edges.size(); i++)
	{
		int source = this->edges[i].getSource() - 1;
		int target = this->edges[i].getTarget() - 1;

		memo[source][target] = 1;
	}
}

void Graph::findLongestPath()
{
	unsigned int longestPathSize = 0; // size of longest path

	// iterate all upper-right, diagonal elements of 2D array memo
	for (int i = 0; i < this->numVertices; i++) 
	{
		for (int j = i + 2; j < this->numVertices; j++)
		{
			std::vector<int> path; // temporary path
			int source = i;
			int target = i + 1;
			int count = 0; // number of edges visted

			// iterate through all vertices in path from i to j
			while (target <= j)
			{
				// edge between vertices source and target exists
				if (this->memo[source][target] == 1) 
				{
					path.push_back(source + 1); // add source vertex id to path
					source = target; 
					target = source + 1;
					count += 1;

					// located last vertex in path from i to j 
					if (source == j)
					{
						path.push_back(source + 1); // add source vertex id to path

						// set path as longest path if the number of edges visted is maximum
						if (path.size() > longestPathSize)
						{
							longestPathSize = path.size();
							this->longestPath = path;
						}

						this->memo[i][j] = count; // update number of edges for path from i to j
						break;
					}
				}
				else 
					target += 1;
			}
		}
	}
}

void Graph::printLongestPath()
{
	std::ofstream outputFile;
	outputFile.open("output.txt", std::fstream::app);

	this->buildMemo();
	this->findLongestPath();

	unsigned int pathSize = this->longestPath.size() - 1; 

	std::cout << pathSize << std::endl;
	outputFile << pathSize << std::endl; // write to file number of edges in longest path

	// iterate through all vertices in longest path
	for (unsigned int i = 0; i < pathSize; i++)
	{
		int source = this->longestPath[i];
		int target = this->longestPath[i + 1];

		// find edge id given by vertices source and target
		for (unsigned int j = 0; j < this->edges.size(); j++)
		{
			if (source == this->edges[j].getSource() && target == this->edges[j].getTarget())
			{
				std::cout << j + 1 << " ";
				outputFile << j + 1 << " "; // write to file edge id
				break;
			}
		}
	}

	std::cout << std::endl << std::endl;
	outputFile << std::endl << std::endl;

	outputFile.close();
}

int Graph::getNumVertices() { return this->numVertices; }

int Graph::getNumEdges() { return this->numEdges; }
