//
//  Classifier.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/10/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__Classifier__
#define __BoostedDecisionTree__Classifier__

#include <iostream>

//pure virtual base class for defining the classifier
class classifier{
public:
    virtual void preprocess() = 0;
    virtual void learn() = 0;
    virtual int predict() = 0;
};

class stump_classifier: public classifier{
    virtual void preprocess();
    virtual void learn();
    virtual int predict();
};

#endif /* defined(__BoostedDecisionTree__Classifier__) */
