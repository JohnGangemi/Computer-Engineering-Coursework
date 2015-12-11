#
#
#
#
# $Id: skel.make,v 1.1 2004/09/15 09:20:45 bgeiger Exp $
# Copyright (c) 2004 Benjamin Geiger <copyright@bgeiger.net>

# Default compiler
CXX = g++

# Default compiler flags
CXXFLAGS = -Wall -g -O

# Default libraries
LIBS = # none needed

# Objects to link
OBJS = Prim.o Kruskal.o Edge.o UnionFind.o

# Cleanup objects
CLEANUP = Prim.dSYM Kruskal.dSYM core

#####################################################################
# Rules
#####################################################################

Kruskal: Kruskal.o Edge.o UnionFind.o
	$(CXX) $(CXXFLAGS) -o Kruskal Kruskal.o Edge.o UnionFind.o $(LIBS)

Prim: Prim.o Edge.o UnionFind.o
	$(CXX) $(CXXFLAGS) -o Prim Prim.o Edge.o UnionFind.o $(LIBS)

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) Kruskal Prim $(CLEANUP)
