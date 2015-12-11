#include "Edge.h"


Edge::Edge(int source, int target)
	:source(source), target(target)
{}

int Edge::getSource() { return this->source; }

int Edge::getTarget() { return this->target; }
