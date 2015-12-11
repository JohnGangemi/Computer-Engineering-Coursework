// John Gangemi
// U6871-4612

#include "Maze.h"
#include "Position.h"
#include <queue>
#include <iostream>
#include <cassert>
#include <iomanip>
#include <cstdlib>

using namespace std;

Maze::Maze(Position s, Position e, int n)
{
    size = n;
    start = s;
    exitpos = e;
    try {
        M = new State *[size];
    }
    catch(bad_alloc) {
        cerr << "Unable to allocate array of state pointers";
        exit(1);
    }
    for(int i = 0; i < size; i++) {
        try {
            M[i] = new State[size];
        }
        catch (bad_alloc) {
            cerr << "Unable to allocate row of state values";
            exit(1);
        }
        for (int j = 0; j < size; j++)
            M[i][j] = WALL;
    }   
    try {
        Pred = new Position *[size];
    }
    catch(bad_alloc) {
        cerr << "Unable to allocate array of predecessor positions";
        exit(1);
    }
    for(int i = 0; i < size; i++) {
        try {
            Pred[i] = new Position[size];
        }
        catch (bad_alloc) {
            cerr << "Unable to allocate row of predecessor positions";
            exit(1);
        }
        for (int j = 0; j < size; j++)
            Pred[i][j] = Position(i, j);
    }   
}

Maze::~Maze()
{
    for(int i = 0; i < size; ++i) {
        delete [] M[i];
        delete [] Pred[i];
    }
    delete [] M;
    delete [] Pred;
}

State
Maze::getState(const Position &P) const
{
    return M[P.getRow()][P.getCol()];
}

void Maze::display(ostream &out) const
{
    out << '\n';
    for (int i=0; i < size;i++) {
        for (int j=0; j < size; j++)
            if (Position(i,j) == start)
                cout << 's';
            else if (Position(i,j) == exitpos)
                cout << 'e';
            else if (M[i][j] == WALL)
                out << '*';
            else
                out << ' ';
        out << '\n';
    }
    out << '\n';
}

void Maze::setState(const Position &P, State s)
{
    int i = P.getRow();
    int j = P.getCol();
    assert(1 <= i && i <= size && 1 <= j && j <= size);
    M[i][j] = s;
}

bool Maze::findExitPath()
{
    // Fill in the missing code
    // Returns true if a start-to-exit path has been found
    // and the contents of the path stack from to bottom 
    // to top will be the exit path

    bool path_exists = false; 
    bool repeat = true;
 
    Position current = start; // make current position the start position
    setState(current, VISITED); // mark the current position (start) as visited
    path.push(current); // push the current position into the stack container

    while (repeat)
    {
        direction d = DOWN; // reset the direction enum to DOWN each loop

        // iterate in all directions
        for (d = DOWN; d != NONE; d++)
        {
            // check state of neighboring cells
            if (getState(current.Neighbor(d)) == OPEN)
            {
                current = current.Neighbor(d); // update the current position in grid
                setState(current, VISITED); // mark the current position as visited
                path.push(current); // push the current position into the stack container

                // exit position reached
                if (current == exitpos)
                {
                    path_exists = true;
                    repeat = false;
                }

                break; // restart iteration in all directions
             }
            else if (getState(current.Neighbor(d)) != OPEN && d == RIGHT && !(current == start))
            {
                path.pop(); // remove top stack element
                current = path.top(); // update the current position in grid
            }
            else if (getState(current.Neighbor(d)) != OPEN && d == RIGHT && current == start)
            {
                path_exists = false;
                repeat = false;
            }
        }
    }

    if (path_exists)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Maze::findShortestPath()
{
    // Fill in the missing code
    // Returns true if a start-to-exit path has been found
    // and this path will be a shortest possible escape path
    // The function will fill in the values of the Pred array,
    // which is used to find the shortest path

    queue<Position> q;
    Position current;

    bool path_exists = false;

    setState(start, VISITED); // mark start as visited
    q.push(start); // enqueue the start position

    while (!q.empty())
    {
        current = q.front(); // assign front element of queue
        q.pop(); // dequeue element

        for (direction d = DOWN; d != NONE; d++)
        {
            // check state of neighboring cells
            if (getState(current.Neighbor(d)) == OPEN)
            {
                setState(current, VISITED); // mark current position as visited
                Pred[current.Neighbor(d).getRow()][current.Neighbor(d).getCol()] = current; // set predecessor position equal to current

                // exit position reached
                if (current.Neighbor(d) == exitpos)
                {
                    path_exists = true;
                    break;
                }
                else
                {
                    q.push(current.Neighbor(d)); // enqueue position of neighboring cell
                }
            }
        }

        // escape loop if exit position reached
        if (path_exists)
        {
            break;
        }
    }

    if (path_exists)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Maze::printExitPath()
{
    if (path.empty())
        return;
    Position hold = path.top();
    path.pop();
    printExitPath();
    cout << hold << endl;
}

void Maze::printShortestPath()
{
    Position P = exitpos;
    while(!(P == start)) {
        path.push(P);
        P = Pred[P.getRow()][P.getCol()];
    }
    path.push(start);

    while(!path.empty()) {
        cout << path.top() << endl;
        path.pop();
    }
}

