//
//  main.cpp
//  maze
//
//  Created by Vanessa Lee on 2/9/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    if(sr == er && sc == ec)
        return true;
    maze[sr][sc] = '*';
    
    if(maze[sr+1][sc] != '*' && maze[sr+1][sc] != 'X')   // SOUTH
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    
    if(maze[sr-1][sc] != '*' && maze[sr-1][sc] != 'X')   // NORTH
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
           return true;
    
    if(maze[sr][sc+1] != '*' && maze[sr][sc+1] != 'X')   // EAST
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    
    if(maze[sr][sc-1] != '*' && maze[sr][sc-1] != 'X')   // WEST
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    
    return false;
}
