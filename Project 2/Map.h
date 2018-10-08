//
//  Map.hpp
//  Project 2
//
//  Created by Vanessa Lee on 1/25/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    
    ~Map();        // When a Map is destroyed, the nodes in the linked list must be deallocated.
    
    Map (const Map& m);
    // When a brand new Map is created as a copy of an existing Map, enough new nodes
    // must be allocated to hold a duplicate of the original list.
    
    Map& operator=(const Map& src);
    // When an existing Map (the left-hand side) is assigned the value of
    // another Map (the right-hand side), the result must be that the left-hand
    // side object is a duplicate of the right-hand side object, with no memory
    // leak of list nodes (i.e. no list node from the old value of the left-hand
    // side should be still allocated yet inaccessible).
    
    bool empty() const;  // Return true if the map is empty, otherwise false.
    
    int size() const;    // Return the number of key/value pairs in the map.
    
    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    
    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
    
    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    
    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    
    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    
    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)
    
    void swap(Map& other);
    // Exchange the contents of this map with the other one.
    
    //void print();
    
private:
    int m_size;
    
    struct Pair {
        KeyType m_key;
        ValueType m_value;
    };
    
    struct Node {
        Pair m_pair;
        
        Node *next;
        Node *prev;
    };
    
    Node *head;
    Node *tail;
};

// Non-member functions
bool combine(const Map& m1, const Map& m2, Map& result);
// When this function returns, result must consist of pairs determined
// by these rules:
//  - If a key appears in exactly one of m1 and m2, then result must contain
//  a pair consisting of that key and its corresponding value.
//  - If a key appears in both m1 and m2, with the same corresponding value in
//  both, then result must contain exactly one pair with that key and value.
// When this function returns, result must contain no pairs other than those
// required by these rules. (You must not assume result is empty when it is
// passed in to this function; it might not be.)

// If there exists a key that appears in both m1 and m2, but with different
// corresponding values, then this function returns false; if there is no key
// like this, the function returns true. Even if the function returns false,
// result must be constituted as defined by the above rules.

void subtract(const Map& m1, const Map& m2, Map& result);
// When this function returns, result must contain one copy of all the pairs
// in m1 whose keys don't appear in m2; it must not contain any other pairs.
// (You must not assume result is empty when it is passed in to this function;
// it may not be.)

#endif /* Map_hpp */
