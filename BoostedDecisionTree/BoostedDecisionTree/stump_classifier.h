//
//  stump_classifier.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/26/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__stump_classifier__
#define __BoostedDecisionTree__stump_classifier__

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include "typeredef.h"
#include "classifier.h"
#include "boost_classifier.h"

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

class stump_classifier:public classifier{
public:
    friend class boost_classifier;
    friend class boost::serialization::access;
   
    
    stump_classifier(){
        v = 0;
        f = 0;
        c = 0;
    };
    
    stump_classifier(const stump_classifier& another){
        v = 0;
        f = 0;
        c = 0;
        p_data = another.p_data;
    };
    
    void preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps);
    std::pair<float,long_vector_ptr_type> learn(vector_ptr_type weights);
    long_vector_ptr_type predict(matrix_ptr_type instances);
    long predict(vector_ptr_type instances);
private:
    long v;
    long f;
    long c;
    boost::shared_ptr<processed_data> p_data;
    
    template <class Ar>
    void serialize(Ar & ar, const unsigned int version){
        ar & v;
        ar & f;
        ar & c;
    }
};
#endif /* defined(__BoostedDecisionTree__stump_classifier__) */
