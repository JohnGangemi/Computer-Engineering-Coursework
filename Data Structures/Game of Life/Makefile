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

# Project name
TARGET = game

# Objects to link
OBJS = main.o Life.o utilities.o

# Cleanup objects
CLEANUP = game.dSYM core

#####################################################################
# Rules
#####################################################################

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) $(CLEANUP)
