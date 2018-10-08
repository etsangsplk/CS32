//
//  Player.hpp
//  Project 1
//
//  Created by Vanessa Lee on 1/10/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

class City;

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_health;
    int   m_age;
};

#endif /* Player_hpp */
