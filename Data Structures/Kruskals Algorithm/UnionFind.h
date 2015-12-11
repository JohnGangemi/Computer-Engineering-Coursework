/*
 * Name.
 * 
 * Description.
 *
 * Copyright (c) 2012 Benjamin Geiger <begeiger@mail.usf.edu>
 */

#pragma once

#ifndef UNIONFIND_H
#define UNIONFIND_H

class UnionFind
{
    public:
        UnionFind(int n);
        UnionFind(const UnionFind &other);
        ~UnionFind();

        UnionFind& operator= (const UnionFind& other);

        int FindSet(int i);
        void Union(int i, int j);

    private:
        int n;
        int *parent;
        int *rank;


};

#endif

/* vim: set et sw=4 ts=4: */
