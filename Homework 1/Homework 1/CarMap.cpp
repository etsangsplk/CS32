//
//  CarMap.cpp
//  Homework 1
//
//  Created by Vanessa Lee on 1/21/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include "CarMap.h"

CarMap::CarMap() {
    Map m_CarMap;
}

bool CarMap::addCar(KeyType license) {
    if (m_CarMap.size() >= DEFAULT_MAX_ITEMS)
        return false;
    if (!m_CarMap.contains(license)) {
        m_CarMap.insert(license, 0);
        return true;
    }
    return false;
}

double CarMap::gas(KeyType license) const {
    if (!m_CarMap.contains(license))
        return -1;
    ValueType gallons;
    m_CarMap.get(license, gallons);
    return gallons;
}

bool CarMap::addGas(KeyType license, ValueType gallons) {
    if (!m_CarMap.contains(license) || gallons < 0)
        return false;
    ValueType originalGallons;
    m_CarMap.get(license, originalGallons);
    ValueType newGallons = originalGallons + gallons;
    m_CarMap.update(license, newGallons);
    return true;
}

bool CarMap::useGas(KeyType license, ValueType gallons) {
    if (!m_CarMap.contains(license) || gallons < 0 || gallons > gas(license))
        return false;
    ValueType originalGallons;
    m_CarMap.get(license, originalGallons);
    ValueType newGallons = originalGallons - gallons;
    m_CarMap.update(license, newGallons);
    return true;
}

int CarMap::fleetSize() const {
    return m_CarMap.size();
}

void CarMap::print() const {
    KeyType license;
    ValueType gallons;
    for (int i = 0; i < m_CarMap.size(); i++) {
        m_CarMap.get(i, license, gallons);
        std::cout << license << " " << gallons << std::endl;
    }
}
