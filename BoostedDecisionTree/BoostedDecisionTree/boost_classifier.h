//
//  boost_classifier.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/27/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__boost_classifier__
#define __BoostedDecisionTree__boost_classifier__

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include "classifier.h"
#include "stump_classifier.h"

class stump_classifier;


class boost_classifier:public classifier{
public:
    friend class boost::serialization::access;
    boost_classifier(long rounds = 20):rounds(rounds),bc_weights(vector_ptr_type(new uvector(rounds))){
    };
    boost_classifier(const boost_classifier& another){
        rounds = another.rounds;
        bc_weights = another.bc_weights;
        basic_classifiers = another.basic_classifiers;
    };
    void preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps);
    std::pair<float,long_vector_ptr_type> learn(vector_ptr_type weights);
    long_vector_ptr_type predict(matrix_ptr_type instances);
    long predict(vector_ptr_type instances);
private:
    long rounds;
    boost::shared_ptr<stump_classifier> basic_classifier;
    std::vector<boost::shared_ptr<stump_classifier> > basic_classifiers;
    matrix_ptr_type data;
    vector_ptr_type bc_weights;
    long_vector_ptr_type label;
    
    template <class Ar>
    void serialize(Ar & ar, const unsigned int version){
        ar & boost::serialization::base_object<classifier>(*this);
        ar & rounds;
        ar & bc_weights;
        ar & basic_classifiers;
    }
};

#endif /* defined(__BoostedDecisionTree__boost_classifier__) */
