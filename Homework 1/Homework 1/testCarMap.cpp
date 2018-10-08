//
//  testCarMap.cpp
//  Homework 1
//
//  Created by Vanessa Lee on 1/21/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "CarMap.h"
#include <iostream>
#include <cassert>

int main () {
    CarMap c;
    assert(c.fleetSize() == 0);
    KeyType k = "original car";
    ValueType v1 = 10;
    ValueType v2 = 20;
    c.addCar(k);
    c.addCar("car1");
    c.addCar("car2");
    c.addCar("car3");
    assert(c.fleetSize() == 4);
    assert(!c.addGas("nonexistent car", v1));
    c.addGas("car1", v1);
    assert(!c.useGas("car1", v2));
    assert(c.addGas(k, v1));
    assert(!c.useGas("car4", 50));
    assert(c.useGas(k, 9));
    c.print();
    
    std::cout << "passed" << std::endl;
    return 0;
}
