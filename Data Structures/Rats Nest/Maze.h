#ifndef __MAZE
#define __MAZE

#include <iostream>
#include "Position.h"
#include <stack>
#include <queue>
// Note the use of the STL queue ADT
// Be aware that it uses push instead of enqueue
// and pop instead of dequeue; front is the same as our Queue classes

using namespace std;

typedef enum {OPEN,WALL,VISITED} State;

class Maze
{
  public:
   //start set to s, exit to e, size to n
   Maze(Position s, Position e, int n);

   ~Maze();

   void initialize(); // input start, exit, and open positions from user

   void display(ostream &out) const;

   State getState(const Position &P) const;
   void setState(const Position &P, State s);
   // precondition: P corresponds to a non-hedge position within the maze

   bool findExitPath();
   void printExitPath();

   bool findShortestPath();
   void printShortestPath();

  private:
   int size;
   Position start;
   Position exitpos;
   State **M; // two-dimensional array of state values
   Position **Pred; // Predecessor array used for shortest path

   stack <Position> path;
};

#endif
