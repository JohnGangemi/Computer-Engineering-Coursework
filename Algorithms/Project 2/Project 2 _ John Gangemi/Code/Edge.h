#ifndef _EDGE_H
#define _EDGE_H

class Edge
{
public:
	Edge(int v, int u, int distance);

	int getV();
	int getU();
	int getDistance();

private:
	int v;
	int u;
	int distance;
};

#endif
