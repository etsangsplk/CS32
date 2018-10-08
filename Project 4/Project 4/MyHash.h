//
//  MyHash.h
//  Project 4
//
//  Created by Vanessa Lee on 3/8/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#ifndef MyHash_h
#define MyHash_h

#include <vector>
#include <string>
#include <functional>
#include "provided.h"

//Class #1: You need to build a map class template named MyHash that implements a
//templated, resizable, open hash-table-based map:
//You need to create a new map class template, based on a resizable open hash table. By
//resizable, we mean if the hash table’s load factor gets too high (because you’ve inserted
//too many items) the hash table will automatically resize itself (that is, allocate a new,
//bigger dynamic array and move all of the entries over to the new table, then delete the old
//dynamic array). Since the hash table is templated, it can be used to map any type of data
//to any other type of data. You must not use any STL container classes to implement your
//MyHash class.

// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
private:
    struct Node {
        Node(KeyType k, ValueType v, Node* n) : key(k), value(v), next(n) { }
        KeyType key;
        ValueType value;
        Node* next;
    };
    
    //    Node* head;
    //    Node* tail;
    
    double m_maxLoadFactor;
    //double m_loadFactor;
    int m_buckets;
    double m_size;
    Node** m_hashTable; // array of node pointers
    
    unsigned int hashFunc(const KeyType &key)
    {
        unsigned int hash(const KeyType& key);
        unsigned int hashBucket = hash(key);
        
        unsigned int bucket = hashBucket % m_buckets;
        return bucket;
    }
};

#endif /* MyHash_h */

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
: m_buckets(100), m_size(0)
{
    // O(B) runtime~
    // empty hash table
    m_hashTable = new Node*[m_buckets];
    for (int i = 0; i < m_buckets; i++)
        m_hashTable[i] = nullptr;
    
    //m_loadFactor = 0.0;

    if(maxLoadFactor <= 0)
        m_maxLoadFactor = 0.5;
    else if(maxLoadFactor > 2)
        m_maxLoadFactor = 2.0;
    else
        m_maxLoadFactor = 0.5;
    
    //    head = nullptr;
    //    tail = nullptr;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    // O(B) runtime
    for(int i = 0; i < m_buckets; i++)
    {
        Node* curr = m_hashTable[i];
        while(curr != nullptr)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete m_hashTable;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    // O(B) runtime!!
    // delete memory in current hash table
    // then make empty map hehe
    for(int i = 0; i < m_buckets; i++)
    {
        Node* curr = m_hashTable[i];
        while(curr != nullptr)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    
    for(int i = 0; i < m_buckets; i++)
        m_hashTable[i] = nullptr;
    
    m_size = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    // O(1) runtime if bucket # is same
    // O(B) runtime if bucket # is changing
    int hashBucket = hashFunc(key);
    
    Node* newNode = new Node(key, value, nullptr);
    
    if(m_hashTable[hashBucket] == nullptr)
        m_hashTable[hashBucket] = newNode;
    else
    {
        Node* temp = m_hashTable[hashBucket];
        while(temp != nullptr)    // traverse to end
        {
            if(temp->key == key)
            {
                temp->value = value;
                return;
            }
            temp = temp->next;
        }
    }
    
    m_size++;
    
    if (getLoadFactor() >= m_maxLoadFactor)
    {
        std::vector<Node*> temp = m_hashTable;
        reset();
        m_buckets = 2*m_buckets;
        for(int i = 0; i < temp.size(); i++)
        {
            associate(temp[i]->key, temp[i]->value);
        }
    }
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    // O(1) runtime
    int hashBucket = hashFunc(key);
    Node* temp = m_hashTable[hashBucket];
    if(temp == nullptr)
        return nullptr;
    while(temp->key != key)
    {
        if(temp == nullptr)
            return nullptr;
        temp = temp->next;
    }
    
    return &temp->value;
}

template <class KeyType, class ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_size;
}

template <class KeyType, class ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return m_size/m_buckets;
}
