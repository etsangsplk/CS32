//
//  History.hpp
//  Project 1
//
//  Created by Vanessa Lee on 1/12/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include "globals.h"

class Flatulan;

class History {
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows, m_cols;
    char m_grid[MAXROWS][MAXCOLS];
    
};

#endif /* History_hpp */
