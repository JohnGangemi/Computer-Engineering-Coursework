/*
 * Name.
 * 
 * Description.
 *
 * Copyright (c) 2012 Benjamin Geiger <begeiger@mail.usf.edu>
 */


#pragma once

#ifndef EDGE_H
#define EDGE_H

#include <iostream>

using namespace std;

class Edge
{
    public:
        Edge(int from, int to, int weight);
        Edge(const Edge &other);

        int From();
        int To();
        int Weight();

    private:
        int from;
        int to;
        int weight;

    friend bool operator== (const Edge& e1, const Edge& e2);
    friend bool operator<= (const Edge& e1, const Edge& e2);
    friend bool operator>= (const Edge& e1, const Edge& e2);
    friend bool operator< (const Edge& e1, const Edge& e2);
    friend bool operator> (const Edge& e1, const Edge& e2);
    friend ostream& operator<<(std::ostream &strm, const Edge &e);
};

#endif

/* vim: set et sw=4 ts=4: */
