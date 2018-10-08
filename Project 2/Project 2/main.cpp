//
//  main.cpp
//  Project 2
//
//  Created by Vanessa Lee on 1/25/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <type_traits>
#include <string>
#include "Map.h"
using namespace std;

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
              "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
              "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
    CHECKTYPE(&Map::size,           int  (Map::*)() const);
    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
    
    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}

void stringTest ()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v)  &&  v == 42);
    assert(m.get("Fred", v)  &&  v == 123);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&
           ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
           x != x2);
}

/*
void intTest()
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

void test1 () {
    Map m1;
    Map m2;
    
    assert(m1.empty());
    assert(m2.empty());
    
    assert(m1.insert("G-Dragon", 88));
    assert(!m1.insert("G-Dragon", 1988));
    assert(m1.insert("Taeyang", 88));
    assert(m1.insert("TOP", 87));
    assert(m1.insert("Daesung", 89));
    assert(m1.insert("Seungri", 90));
    
    assert(m2.insert("BIGBANG", 2006));
    assert(m2.insert("BTS", 2013));
    
    assert(m1.size() == 5);
    assert(m2.size() == 2);
    
    assert(!m2.contains("SHINee"));
    assert(m1.contains("G-Dragon"));
    
    //m1.print();
    //m2.print();
    
    m2.erase("BTS");
    assert(!m2.contains("BTS"));
    assert(m2.size() == 1);
    
    //m2.print();
    
    m1.swap(m2);
    
    //m1.print();
    //m2.print();
    
    Map m3 = m1;
    
    //m1.print();
    //m3.print();
    
    assert(m3.contains("BIGBANG"));
    assert(!m3.update("NOTHING", 10));
    assert(!m3.erase("bigbang"));
    assert(m3.erase("BIGBANG"));
    assert(m3.empty() && m3.size() == 0);
    
    assert(m2.erase("Seungri"));
    assert(m2.erase("G-Dragon"));
    //m2.print();
    assert(m2.erase("TOP"));
}

void test2 () {
    KeyType bb[5] = {"Daesung", "Seungri", "G-Dragon", "TOP", "Taeyang"};
    Map b;
    for (int i = 0; i < 5; i++)
        assert(b.insert(bb[i], i));
    
    //b.print();
    
    KeyType bangtan[7] = {"Jungkook", "Taehyung", "Yoongi", "Jimin", "Hoseok", "Namjoon", "Seokjin"};
    Map bts;
    for (int i = 0; i < 7; i++)
        assert(bts.insert(bangtan[i], i+10));
    
    //bts.print();
    
    //b = bts;
    
    //b.print();
    
    Map bb2;
    KeyType duo[3] = {"G-Dragon", "TOP", "Taeyang"};
    for (int i = 0; i < 3; i++)
        assert(bb2.insert(duo[i], i));
    
    Map result;
    assert(result.empty());
    assert(!combine(b, bb2, result));
    //result.print();
    
    KeyType maknaes[2] = {"Daesung", "Seungri"};
    Map bb3;
    for (int i = 0; i < 2; i++)
        assert(bb3.insert(maknaes[i], i));
    
    assert(combine(b, bb3, result));
    assert(!result.empty());
    assert(result.contains("G-Dragon") && result.contains("Daesung"));
    assert(result.size() == 5);
    //result.print();
    
    subtract(b, bb2, result);
    //result.print();
}

void testCases() {
    Map m1;		// calls default constructor
    assert(m1.empty() && m1.size() == 0);		// default constructor creates empty map
    assert(!m1.erase("Nothing to erase"));	// can't erase an empty map
    
    assert(m1.insert("G-Dragon", 88));
    assert(m1.insert("Taeyang", 88));
    assert(!m1.insert("G-Dragon", 1988));	// checks against adding two of the same key
    assert(!m1.empty()); // map is no longer empty
    assert(m1.contains("G-Dragon") && m1.contains("Taeyang"));	// checks if keys are inserted properly
    assert(m1.size() == 2);		// insert function properly increases size
    
    ValueType v;
    m1.get("G-Dragon", v);
    assert(v == 88);	// checks that value was not changed when we tried to insert the same key twice
    
    Map m2 = m1;	// calls copy contructor;
    assert(m2.contains("G-Dragon"));
    assert(m2.size() == 2);
    // checks that map was properly copied
    
    Map m3;
    KeyType bangtan[7] = {"Jungkook", "Taehyung", "Yoongi", "Jimin", "Hoseok", "Namjoon", "Seokjin"};
    for (int i = 0; i < 7; i++)
        assert(m3.insert(bangtan[i], i+10));
    
    ValueType v2;
    m3.get("Taehyung", v2);
    assert (v2 == 11);	// checks inserted value
    
    assert(m3.erase("Seokjin") && m3.size() == 6);	// checks that last node can be erased
    assert(!m3.erase("Seokjin")); // can't erase a node that doesn't exist
    assert(m3.erase("Jungkook"));	// checks that first node can be erased
    assert(m3.erase("Jimin")); 	// checks that middle node cna be erased
    assert(m3.insertOrUpdate("Taehyung", 95));	// updates current key in map
    assert(!m3.update("G-Dragon", 88));	// key does not exist in map
    assert(m3.insertOrUpdate("BigHit", 2013) && m3.contains("BigHit") && m3.size() == 5);
    // map does not contain value, so it should insert into map
    
    m3.get("Taehyung", v2);
    assert(v2 == 95);	// value should have been changed with update function
    
    m3 = m1;	// calls assignment operator
    assert(m3.contains("G-Dragon") && m3.size() == 2);
    assert(!m3.insert("Taeyang", 1988));	// key already exists
    assert(m1.contains("G-Dragon") && m1.size() == 2);
    // checks that map was properly assigned
    
    KeyType bb[5] = {"Daesung", "Seungri", "G-Dragon", "TOP", "Taeyang"};
    Map b;
    for (int i = 0; i < 5; i++)
        assert(b.insert(bb[i], i));
    
    Map bb2;
    KeyType duo[3] = {"G-Dragon", "TOP", "Taeyang"};
    for (int i = 0; i < 3; i++)
        assert(bb2.insert(duo[i], i));
    
    Map result;
    assert(result.empty());		// passing in empty result
    assert(!combine(b, bb2, result));
    // values of the keys are different, so returns false
    
    KeyType maknaes[2] = {"Daesung", "Seungri"};
    Map bb3;
    for (int i = 0; i < 2; i++)
        assert(bb3.insert(maknaes[i], i));
    
    assert(combine(b, bb3, result));
    assert(!result.empty());	// result not empty from before
    assert(result.contains("G-Dragon") && result.contains("Daesung"));
    assert(result.size() == 5);
    // checks that combine function works properly
    
    subtract(b, bb2, result);
    // result is not empty anymore, must not contain previous result
    assert(!result.contains("G-Dragon"));
    assert(!result.contains("TOP"));
    assert(result.contains("Seungri") && result.contains("Daesung"));
    assert(result.size() == 2);
    // checks that subtract function works properly
    
    bb2.swap(bb3);
    assert(bb2.contains("Daesung") && bb2.contains("Seungri"));
    assert(bb3.contains("G-Dragon") && bb3.contains("TOP") && bb3.contains("Taeyang"));
    assert(bb2.size() == 2 && bb3.size() == 3);
    // checks swap function
}

int main () {
    //test1();
    //test2();
    testCases();
    //stringTest();
    //intTest();
    cout << "passed" << endl;
}
