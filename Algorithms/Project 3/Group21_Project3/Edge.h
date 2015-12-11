#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	Edge(int source, int target);
	int getSource();
	int getTarget();

private:
	int source;
	int target;
};

#endif