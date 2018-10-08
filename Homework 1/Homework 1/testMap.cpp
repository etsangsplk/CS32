//
//  testMap.cpp
//  Homework 1
//
//  Created by Vanessa Lee on 1/17/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "Map.h"
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


/*
 void test2()
{
    Map m;
    assert(m.insert(10, "diez"));
    assert(m.insert(20, "veinte"));
    assert(m.size() == 2);
    ValueType v = "cuarenta y dos";
    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
    assert(m.get(10, v)  &&  v == "diez");
    v = "cuarenta y dos";
    KeyType x = 30;
    assert(m.get(0, x, v)  &&
           ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
    KeyType x2 = 40;
    assert(m.get(1, x2, v)  &&
           ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
           x != x2);
}
*/

int main()
{
    //std::cout << "FIRST MAP" << std::endl;
    Map m;
    assert(m.empty() && m.size() == 0);
    m.insert("key1", 10);
    m.insert("key2", 20);
    m.insert("key3", 30);
    m.insert("key4", 40);
    m.insert("key5", 50);
    assert(m.size() == 5);
    m.erase("key4");
    assert(m.size() == 4);
    m.update("key1", 100);
    m.insertOrUpdate("key3", 300);
    //m.print();
    
    /*
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
    m.print();
    */
    
    //std::cout << "SECOND MAP" << std:: endl;

    Map m2;
    m2.insert("key", 0);
    assert(m2.size() == 1);
    m2.erase("key");
    assert(m2.size() == 0);
    assert(!m2.erase("key"));
    assert(m2.insertOrUpdate("key", 1));
    assert(m2.size() == 1);
    assert(m2.insert("k", 0));
    //m2.print();
    
    m.swap(m2);
    
    //std::cout << "SWAPPED MAPS" << std::endl;
    
    //m.print();
    //std::cout << std::endl;
    //m2.print();
    
    /*
    Map m;  // maps ints to strings
    assert(m.empty());
    ValueType v = "Ouch";
    assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
    m.insert(123456789, "Wow!");
    assert(m.size() == 1);
    KeyType k = 9876543;
    assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
    cout << "Passed all tests" << endl; 
    */
    
    test();
    //test2();
    
    std::cout << "Passed all tests" << std::endl;
}

