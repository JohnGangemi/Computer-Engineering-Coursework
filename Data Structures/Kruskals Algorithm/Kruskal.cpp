/*
 * Name.
 * John Gangemi U6871-4612
 * Description.
 * Implement Kruskal's algorithm
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "Edge.h"
#include "UnionFind.h"

using namespace std;

int num_vertices;
vector<Edge> edges;

// Read the input from the user.
void
read_input()
{
    int tmp;
    int from, to, weight;

    Edge edge(0, 0, 0);

    num_vertices = 0;
    while (num_vertices <= 0) {
        cout << "Enter the number of vertices: ";
        cin >> tmp;
        if (tmp > 0) {
            num_vertices = tmp;
        } else {
            cout << "Please enter a positive number of vertices." << endl << endl;
        }
    }

    cout << "Vertices numbered from 0 to " << num_vertices - 1 << endl << endl;

    cout << "Enter edges:" << endl;
    cout << "Format: <from-vertex> <to-vertex> <weight>" << endl;
    cout << "Example: Edge from 1 to 2, weight 50:  1 2 50" << endl;
    cout << "Enter '-1 -1 -1' to end." << endl;

    while (true) {
        cin >> from;
        cin >> to;
        cin >> weight;

        if (from == -1) {
            break;
        }

        if (from >= num_vertices || from < 0) {
            cout << "Invalid from vertex: " << from << endl;
            continue;
        }

        if (to >= num_vertices || to < 0) {
            cout << "Invalid to vertex: " << to << endl;
            continue;
        }

        if (weight <= 0) {
            cout << "Invalid weight: " << weight << endl;
            continue;
        }

        edge = Edge(from, to, weight);

        edges.push_back(edge);
    }
}

// HINT: to sort a vector:
// sort(vector.begin(), vector.end())

vector<Edge>
kruskal()
{
    // TODO: Complete.

    // edge objects that form a minimum spanning tree
    vector<Edge> mstEdges;

    // check the validity of user defined vector "edges"
    if (!edges.empty())
    {
        // sort user defined vector "edges" by weight
        sort(edges.begin(), edges.end());

        // single-element sets from 0 to num_vertices - 1
        UnionFind sets(num_vertices);

        int num_min_edges = 0; // number of minimum-weight edges that do not create cycles
        int iter = 0; // iterator for vector "edges"

        // loop until condition of n-1 minimum-weight edges from n vertices is satisfied
        while (num_min_edges < num_vertices - 1)
        {
            // check if endpoints of edge belong to same set (avoid cycles)
            if (sets.FindSet(edges[iter].From()) != sets.FindSet(edges[iter].To()))
            {
                ++num_min_edges;
                mstEdges.push_back(edges[iter]); 
                sets.Union(edges[iter].From(), edges[iter].To());
            }
            ++iter;
        }
    }
    else
    {
        cout << "User has not defined edges for the graph : vector<edges> is empty" << endl;
    }

    return mstEdges;
}

int
main(int argc, char **argv)
{
    read_input();

    vector<Edge> kruskal_edges = kruskal();

    sort(kruskal_edges.begin(), kruskal_edges.end());
    for (vector<Edge>::iterator it = kruskal_edges.begin(); it != kruskal_edges.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}

/* vim: set et sw=4 ts=4: */
