//
//  Map.cpp
//  Project 2
//
//  Created by Vanessa Lee on 1/25/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "Map.h"
#include <iostream>

Map::Map()
: m_size(0)
{
    head = nullptr;
    tail = nullptr;
}

Map::~Map() {
    Node *p = head;
    
    while (p != nullptr) {
        Node *n = p->next;
        delete p;
        p = n;
    }
}

Map::Map(const Map& m) {
    m_size = 0;
    head = nullptr;
    tail = nullptr;
    
    Node *p = m.head;
    
    while (p != nullptr) {
        insert(p->m_pair.m_key, p->m_pair.m_value);
        p = p->next;
    }
    
}

Map& Map::operator=(const Map &src) {
    if (this == &src)
        return *this;
    
    Map temp = src;
    swap(temp);
    
    return (*this);
}

bool Map::empty() const {
    return m_size == 0 && head == nullptr;
}

int Map::size() const {
    return m_size;
}

bool Map::insert(const KeyType &key, const ValueType &value) {
    if (contains(key))
        return false;
    
    Node *newNode = new Node;
    
    newNode->m_pair.m_key = key;
    newNode->m_pair.m_value = value;
    
    if (empty()) {
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }
    else {
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
    }

    m_size++;
    return true;
}

bool Map::update(const KeyType &key, const ValueType &value) {
    if (!contains(key))
        return false;
    
    Node *p = head;
    
    while (p != nullptr) {
        if (p->next != nullptr && p->next->m_pair.m_key == key)
            break;
        p = p->next;
    }
    
    Node *updateMe = p->next;
    updateMe->m_pair.m_value = value;
    return true;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value) {
    if (!contains(key))
        insert(key, value);
    else
        update(key, value);
    
    return true;
}

bool Map::erase(const KeyType &key) {
    if (!contains(key))
        return false;
    
    if (m_size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        m_size--;
        return true;
    }
    
    Node *p = head;
    
    while (p != nullptr) {
        if (p->m_pair.m_key == key)
            break;
        p = p->next;
    }
    
    if (head == p) {
        head = p->next;
        delete p;
        head->prev = nullptr;
    }
    else if (tail == p) {
        tail = p->prev;
        delete p;
        tail->next = nullptr;
    }
    else {
        Node *tempNext = p->next;
        Node *tempPrev = p->prev;
        delete p;
        tempNext->prev = tempPrev;
        tempPrev->next = tempNext;
    }
    
    m_size--;
    
    return true;
}

bool Map::contains(const KeyType &key) const {
    if (head == nullptr)
        return false;
    
    if (head->m_pair.m_key == key)
        return true;
    
    Node *p = head;
    
    while (p != nullptr) {
        if (p->m_pair.m_key == key)
            return true;
        p = p->next;
    }
    
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const {
    if (!contains(key))
        return false;
    
    Node *p = head;
    
    while (p != nullptr) {
        if (p->m_pair.m_key == key)
            break;
        p = p->next;
    }
    
    value = p->m_pair.m_value;
    return true;
}

bool Map::get(int i, KeyType &key, ValueType &value) const {
    if (i < 0 || i >= m_size)
        return false;

    Node *p = head;
    for (int n = 0; n < i; n++)
        p = p->next;
    
    key = p->m_pair.m_key;
    value = p->m_pair.m_value;
    return true;
}

void Map::swap(Map &other) {
    Node *tempHead = other.head;
    Node *tempTail = other.tail;
    
    other.head = head;
    head = tempHead;
    
    other.tail = tail;
    tail = tempTail;
    
    int currentSize = m_size;
    m_size = other.m_size;
    other.m_size = currentSize;
}

// Non-member functions =======================================================================
bool combine(const Map& m1, const Map& m2, Map& result) {
    Map temp1 = m1;
    Map temp2 = m2;
    
    bool sameValue = true;
    
    while (!result.empty()) {
        KeyType k;
        ValueType v;
        result.get(0, k, v);
        result.erase(k);
    }
    
    for (int i = 0; i < temp1.size(); i++) {
        KeyType k;
        ValueType v;
        temp1.get(i, k, v);
        
        if (!m2.contains(k))
            result.insert(k, v);
        else
        {
            ValueType v2;
            temp2.get(k, v2);
            if (v == v2)
                result.insert(k, v);
            else
                sameValue = false;
        }
    }
    
    for (int i = 0 ; i < temp2.size(); i++) {
        KeyType k;
        ValueType v;
        temp2.get(i, k, v);
        
        if (!m1.contains(k))
            result.insert(k, v);
    }
    
    return sameValue;
}

void subtract(const Map& m1, const Map& m2, Map& result) {
    Map temp1 = m1;
    Map temp2 = m2;
    
    while (!result.empty()) {
        KeyType k;
        ValueType v;
        result.get(0, k, v);
        result.erase(k);
    }
    
    for (int i = 0; i < temp1.size(); i++) {
        KeyType k;
        ValueType v;
        temp1.get(i, k, v);
        
        if (!m2.contains(k))
            result.insert(k, v);
    }
}
/*
void Map::print() {
    std::cout << "------------START------------" << std::endl;
    KeyType k;
    ValueType v;
    for (int i = 0; i < m_size; i++) {
        get(i, k, v);
        std::cout << k << " " << v << std::endl;
    }
    
    std::cout << "------------END--------------" << std::endl << std::endl;
}
*/
