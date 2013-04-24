//
//  stringutil.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/4/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//
#ifndef BoostedDecisionTree_stringutil_h
#define BoostedDecisionTree_stringutil_h
#include <vector>
#include <iostream>
#include <memory>

class ss{
    
};

using namespace std;

vector<string>& split(const string &s, char delim, vector<std::string> &elems);
vector<string> split(const string &s, char delim);

int strtoint(int &i, char const *s, int base = 0);
#endif
