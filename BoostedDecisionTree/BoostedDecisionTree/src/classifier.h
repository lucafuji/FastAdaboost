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
#include <boost/unordered_map.hpp>
#include "typeredef.h"

typedef boost::unordered_map<std::string, long_vector_ptr_type> stump_map;
typedef boost::shared_ptr<stump_map> stump_map_ptr;

struct processed_data{
    long_matrix_ptr_type ind;
    matrix_ptr_type data;
    matrix_ptr_type tdata;
    long_matrix_ptr_type label;
    long_vector_ptr_type tlabel;
    std::vector<stump_map_ptr> stump_map_vector;
};

typedef boost::shared_ptr<processed_data> processed_data_ptr;

//pure virtual base class for defining the classifier
class classifier{
public:
    friend class boost::serialization::access;
    /*
     *data : input training data
     *labels : labels of the training data
     *ebs : thresold of the convergence
     */
    
    virtual processed_data_ptr preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps) = 0;
    /*
     *data : processed input training data
     *weights : weight on each training item
     *return error and the classification result
     */
    virtual std::pair<float,long_vector_ptr_type> learn(processed_data_ptr processed_data,vector_ptr_type weights) = 0;
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
