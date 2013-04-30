//
//  feature_hashing_classifier.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/28/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__feature_hashing_classifier__
#define __BoostedDecisionTree__feature_hashing_classifier__

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include "classifier.h"
#include "murmurhash.h"


class feature_hashing_classifier:public classifier{
public:
    friend class boost::serialization::access;
    feature_hashing_classifier(classifier* basic_classifier = NULL,long num_hash_bits = 100):basic_classifier(basic_classifier),num_hash_bits(num_hash_bits){
        seed = time(NULL);
        len = 64;
    }
    feature_hashing_classifier(const feature_hashing_classifier& another){
        basic_classifier = another.basic_classifier;
        num_hash_bits = another.num_hash_bits;
        seed = another.seed;
        len = another.len;
        hash_matrix = another.hash_matrix;
    }
    virtual void preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps);
    virtual std::pair<float,long_vector_ptr_type> learn(vector_ptr_type weights);
    virtual long predict(vector_ptr_type instance);
    virtual long_vector_ptr_type predict(matrix_ptr_type instances);
private:
    boost::shared_ptr<classifier> basic_classifier;
    long num_hash_bits;
    long seed;
    long len;
    long_matrix_ptr_type hash_matrix;
    void compute_hash_matrix(long_vector_ptr_type feature_index_vector);
    long hash_sign(long feature_index){return feature_index%2 == 0 ?1:-1;}
    long hash_value(long* feature_index_ptr){return MurmurHash64A(feature_index_ptr, len, seed);}
    
    template <class Ar>
    void serialize(Ar & ar, const unsigned int version){
        ar & boost::serialization::base_object<classifier>(*this);
        ar & basic_classifier;
        ar & num_hash_bits;
        ar & seed;
        ar & len;
        ar & hash_matrix;
    }
};

#endif /* defined(__BoostedDecisionTree__feature_hashing_classifier__) */
