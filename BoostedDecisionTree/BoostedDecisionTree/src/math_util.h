//
//  math_util.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/26/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__math_util__
#define __BoostedDecisionTree__math_util__

#include <iostream>
#include <cmath>

#define EPS (1e-10)

template <typename T>
struct is_zero{
    bool operator()(T x) { return x == 0; }
};

template <>
struct is_zero<float>{
    is_zero(double eps = EPS){}
    bool operator()(float x) { return abs(x)<eps; }
    float eps;
};

template <typename T>
struct is_non_zero{
    bool operator()(T x) { return x != 0; }
};

template <>
struct is_non_zero<float>{
    is_non_zero(double eps = EPS){}
    bool operator()(float x) { return abs(x)>=eps; }
    float eps;
};

struct larger_than_zero{
    larger_than_zero(){}
    bool operator()(float x) { return x>0; }
};

struct less_than_or_equal_to_zero{
    less_than_or_equal_to_zero(){}
    bool operator()(float x) { return x<=0; }
};
        
struct not_equal{
    not_equal(double eps = EPS){}
    bool operator()(float x1,float x2) { return abs(x1-x2)>=eps; }
    float eps;
};
        
struct long_not_equal{
    long_not_equal(double eps = EPS){}
    bool operator()(long x1,long x2) { return x1!=x2; }
};
#endif /* defined(__BoostedDecisionTree__math_util__) */
