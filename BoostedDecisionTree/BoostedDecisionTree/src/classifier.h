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
#include <boost/shared_ptr.hpp>
#include <utility>
#include "typeredef.h"
//pure virtual base class for defining the classifier
class classifier{
public:
    friend class boost::serialization::access;
    /*
     *data : input training data
     *labels : labels of the training data
     *ebs : thresold of the convergence
     */
    virtual void preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps) = 0;
    /*
     *data : processed input training data
     *weights : weight on each training item
     *return error and the classification result
     */
    virtual std::pair<float,long_vector_ptr_type> learn(vector_ptr_type weights) = 0;
    /*
     *instance : instance whose label is to be predicted
     *return label of the instance
     */
    virtual long predict(vector_ptr_type instance) = 0;
    /*
     *instances : set of instances to be tested
     *return error rate
     */
    virtual long_vector_ptr_type predict(matrix_ptr_type instances) = 0;
    
    template <class Ar>
    void serialize(Ar & ar, const unsigned int version){
    }
};
#endif /* defined(__BoostedDecisionTree__Classifier__) */
