//
//  feature_hashing_classifier.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/28/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "feature_hashing_classifier.h"
#include "typeredef.h"

BOOST_CLASS_EXPORT(feature_hashing_classifier)
void feature_hashing_classifier::compute_hash_matrix(long_vector_ptr_type feature_index_vector)
{
    long n_feature = feature_index_vector->size();
    long_matrix_ptr_type hash_matrix(new longmatrix(ublas::zero_matrix<long>(num_hash_bits,n_feature)));
    
    for(longvector::iterator iter = feature_index_vector->begin();iter!= feature_index_vector->end(); ++iter){
        (*hash_matrix)(hash_value(&(*iter)),(*iter)) = hash_sign(*iter);
    }
    this->hash_matrix = hash_matrix;
}

//pre_hashing the data
void feature_hashing_classifier::preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps)
{
    long_vector_ptr_type feature_vector(new longvector(data->size1()));
    
    for(int i = 0;i<feature_vector->size();i++){
        (*feature_vector)(i) = i;
    }
    compute_hash_matrix(feature_vector);
    
    matrix_ptr_type hashed_data(new umatrix(ublas::trans(ublas::prod(*hash_matrix, ublas::trans(*data)))));
    basic_classifier->preprocess(hashed_data, labels,eps);
}

std::pair<float,long_vector_ptr_type> feature_hashing_classifier::learn(vector_ptr_type weights)
{
    return basic_classifier->learn(weights);
}

long feature_hashing_classifier::predict(vector_ptr_type instance)
{
    vector_ptr_type hashed_data(new uvector(ublas::trans(ublas::prod(*hash_matrix, ublas::trans(*instance)))));
    return basic_classifier->predict(hashed_data);
}

long_vector_ptr_type feature_hashing_classifier::predict(matrix_ptr_type instances)
{
    matrix_ptr_type hashed_data(new umatrix(ublas::trans(ublas::prod(*hash_matrix, ublas::trans(*instances)))));
    return basic_classifier->predict(hashed_data);
}