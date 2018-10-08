//
//  Game.hpp
//  Project 1
//
//  Created by Vanessa Lee on 1/10/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

#endif /* Game_hpp */
