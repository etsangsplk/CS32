//
//  main.cpp
//  newMap
//
//  Created by Vanessa Lee on 1/21/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "newMap.h"

//
//  Map.cpp
//  Homework 1
//
//  Created by Vanessa Lee on 1/17/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "newMap.h"

Map::Map()
{
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    data = new mapData[m_max];
}

Map::Map (int max) {
    m_max = max;
    m_size = 0;
    data = new mapData[m_max];
}

Map::Map (const Map &m) {
    m_size = 0;
    m_max = m.m_max;
    data = new mapData[m_max];
    for (int i = 0; i < m.m_size; i++) {
        KeyType k;
        ValueType v;
        m.get(i, k, v);
        insert(k, v);
    }
}

Map& Map::operator=(const Map& src)
{
    delete [] data;
    m_max = src.m_max;
    m_size = 0;
    data = new mapData[m_max];
    
    for (int i = 0; i < m_max; i++) {
        KeyType k;
        ValueType v;
        src.get(i, k, v);
        insert(k, v);
    }
    
    return (*this);
}

Map::~Map()
{
    delete [] data;
}

bool Map::empty() const
{
    if (m_size == 0)
        return true;
    
    return false;
}

int Map::size() const
{
    return m_size;
}

bool Map::insert(const KeyType &key, const ValueType &value)
{
    if (size() >= m_max || contains(key))
        return false;
    
    data[m_size].key = key;
    data[m_size].value = value;
    m_size++;
    
    return true;
}

bool Map:: update(const KeyType &key, const ValueType &value)
{
    for (int i = 0; i < m_size; i++)
    {
        if (data[i].key == key)
        {
            data[i].value = value;
            return true;
        }
    }
    
    return false;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value)
{
    if (update(key, value))
        return true;
    else if (insert(key, value))
        return true;
    
    return false;
}

bool Map::erase(const KeyType &key)
{
    if (m_size == 1 && data[0].key == key)
    {
        m_size--;
        return true;
    }
    else if (m_size == 1 && data[0].key != key)
        return false;
    
    for (int i = 0; i < m_size; i++)
    {
        if (data[i].key == key)
        {
            data[i].key = data[size()-1].key;
            data[i].value = data[size()-1].value;
            m_size--;
            return true;
        }
    }
    
    return false;
}

bool Map::contains(const KeyType &key) const
{
    if (empty())
        return false;
    
    for (int i = 0; i < m_size; i ++)
    {
        if (data[i].key == key)
            return true;
    }
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const
{
    for (int i = 0; i < m_size; i++)
    {
        if (data[i].key == key)
        {
            value = data[i].value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const
{
    if (i >= 0 && i < m_size)
    {
        key = data[i].key;
        value = data[i].value;
        return true;
    }
    
    return false;
}

void Map::swap(Map &other)
{
    Map temp = other; //assignment operator
    other = *this;
    *this = temp;
}

/*
 void Map::print() const {
 KeyType k;
 ValueType v;
 for (int i = 0; i < m_size; i++) {
 get(i, k, v);
 std::cout << k << " " << v << std::endl;
 }
 }
*/


