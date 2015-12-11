#include "Edge.h"


Edge::Edge(int v, int u, int distance)
	:v(v), u(u), distance(distance)
{}

int Edge::getV() { return this->v; }

int Edge::getU() { return this->u; }

int Edge::getDistance() { return this->distance; }


