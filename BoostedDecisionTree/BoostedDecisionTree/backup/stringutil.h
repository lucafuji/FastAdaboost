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
#include <string>

std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

int strtoint(int &i, char const *s, int base = 0);

#endif
