//
//  testnewMap.cpp
//  newMap
//
//  Created by Vanessa Lee on 1/21/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "newMap.h"
#include <iostream>
#include <cassert>

void test()
{
    Map m;
    assert(m.insert("Fred", 2.956));
    assert(m.insert("Ethel", 3.538));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v)  &&  v == 42);
    assert(m.get("Fred", v)  &&  v == 2.956);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 2.956)  ||  (x == "Ethel"  &&  v == 3.538)));
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&
           ((x2 == "Fred"  &&  v == 2.956)  ||  (x2 == "Ethel"  &&  v == 3.538))  &&
           x != x2);
}

void test2 ()
{
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = {"one", "two", "three", "four", "five", "six"};
    ValueType v  = 1;
    
    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));
    
    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));
    
    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));
    
/*
     Map a(3);
     Map b(2);
     KeyType keys[3] = {"one", "two", "three"};
     KeyType moreKeys[2] = {"first", "second"};
     
     for (int i = 0; i < 3; i++) {
     assert(a.insert(keys[i], i));
     }
     for (int i = 0; i < 2; i++) {
     assert(b.insert(moreKeys[i], i));
     }
     std::cout << "MAP A:" << std::endl;
     a.print();
     std::cout << "MAP B:" << std::endl;
     b.print();
     
     Map c = a;
     std::cout << "C = A:" << std::endl;
     c.print();
     std::cout << std::endl;
     
     c.swap(b);
     std::cout << "MAP C:" << std::endl;
     c.print();
     std::cout << "MAP B:" << std::endl;
     b.print();
     std::cout<< "passed" << std::endl;
 
*/
    
}

int main () {
    test();
    std::cout << "Passed all tests" << std::endl;
    return 0;
}
