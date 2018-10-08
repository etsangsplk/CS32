//
//  main.cpp
//  Project 4
//
//  Created by Vanessa Lee on 3/8/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "MyHash.h"
using namespace std;

int main()
{
    double bucket = 100;
    int size = 10;
    double load = size/bucket;
    cout << load << endl;
    
    Translator t;
    t.pushMapping("abc", "dEF");
    t.pushMapping("xejk", "thes");
    t.popMapping();
    
    cout << t.getTranslation("xabsflk e skdfvk jfsv") << endl;
    
    WordList w;
    w.loadWordList("/Users/vlee/Desktop/test.txt");
    assert(w.contains("test"));
}
