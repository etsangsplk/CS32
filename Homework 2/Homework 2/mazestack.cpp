//
//  mazestack.cpp
//  Homework 2
//
//  Created by Vanessa Lee on 1/31/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc)); // Push the starting coordinate (sr,sc) onto the coordinate stack
    
    maze[sr][sc] = '#';
    
    while(!coordStack.empty()) {
        Coord curr = coordStack.top();
        coordStack.pop();
        
        //cerr << "The current coordinates are: (" << curr.r() << ", " << curr.c() << ")" << endl;
        
        if(curr.r() == er && curr.c() == ec)
            return true;
        
        if(maze[curr.r()][curr.c() + 1] == '.') {   // EAST
            coordStack.push(Coord(curr.r(), curr.c() + 1));
            maze[curr.r()][curr.c() + 1] = '#';
        }
        
        if(maze[curr.r() + 1][curr.c()] == '.') {   // SOUTH
            coordStack.push(Coord(curr.r() + 1, curr.c()));
            maze[curr.r() + 1][curr.c()] = '#';
        }
        
        if(maze[curr.r()][curr.c() - 1] == '.') {   // WEST
            coordStack.push(Coord(curr.r(), curr.c() - 1));
            maze[curr.r()][curr.c() - 1] = '#';
        }
        
        if(maze[curr.r() - 1][curr.c()] == '.') {   // NORTH
            coordStack.push(Coord(curr.r() - 1, curr.c()));
            maze[curr.r() - 1][curr.c()] = '#';
        }
    }
    
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}