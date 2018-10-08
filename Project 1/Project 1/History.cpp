//
//  History.cpp
//  Project 1
//
//  Created by Vanessa Lee on 1/12/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "History.h"
#include <iostream>

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            m_grid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    if (r <= 0 || r > m_rows || c <= 0 || c > m_cols)
    {
        return false;
    }
    
    if (m_grid[r][c] >= 'Z')
    {
        m_grid[r][c] = 'Z';
    }
    else if (m_grid[r][c] >= 'A' && m_grid[r][c] <= 'Z')
    {
        m_grid[r][c]++;
    }
    else {
        m_grid[r][c] = 'A';
    }
    
    return true;
}

void History::display() const
{
    clearScreen();
    
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            std::cout << m_grid[r][c];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}
