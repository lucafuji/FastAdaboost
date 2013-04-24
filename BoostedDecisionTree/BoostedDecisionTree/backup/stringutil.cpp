//
//  stringutil.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/4/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "stringutil.h"
#include <sstream>
#include <errno.h>

std::vector<std::string> & split(const std::string &s, char delim, std::vector<std::string> &elems){
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item,delim)){
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim){
    std::vector<std::string> elems = split(s,delim,elems);
    return elems;
}


int strtoint(int &i, char const *s, int base){
    char * end;
    long l;
    errno = 0;
    l = strtol(s, &end, base);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
        return -1;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return -1;
    }
    if (*s == '\0' || *end != '\0') {
        return -1;
    }
    i = l;
    return 0;
}