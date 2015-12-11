#include "Vertex.h"


Vertex::Vertex()
	:id(0), discovered(false), color(' '), direction("")
{}

void Vertex::setId(int num) { this->id = num; }

void Vertex::setDiscovered(bool val) { this->discovered = val; }

void Vertex::setColor(char ch) { this->color = ch; }

void Vertex::setDirection(std::string str) { this->direction = str; }

int Vertex::getId() { return this->id; }

bool Vertex::isDiscovered() { return this->discovered; }

char Vertex::getColor() { return this->color; }

std::string Vertex::getDirection() { return this->direction; }
