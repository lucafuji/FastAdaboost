//
//  data_processor.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/10/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "data_processor.h"
tuple_ptr_type data_processor::z_score(matrix_ptr_type data)
{
    long ncol = data->size2();
    long nrow = data->size1();
    uvector mean_vector(ncol);
    uvector std_vector(ncol);
    for (unsigned j = 0; j < ncol; ++ j){
        mean_vector[j]= 0;
        for(unsigned i = 0; i < nrow; ++i){
            mean_vector[j] = (1-1.0/(i+1))*mean_vector(j) + 1.0/(i+1)*((*data)(i,j));
        }
    }
    
    for (unsigned j = 0; j < ncol; ++ j){
        std_vector[j] = 0;
        for(unsigned i = 0; i < nrow; ++i){
            std_vector[j] = (1-1.0/(i+1))*std_vector(j) + 1.0/(i+1)*pow((*data)(i,j) - mean_vector(j),2.0);
        }
    }
    
    umatrix new_matrix(nrow,ncol);
    for(unsigned i = 0; i < nrow; ++i){
        for (unsigned j = 0; j < ncol; ++j){
            new_matrix(i,j) = ((*data)(i,j) - mean_vector(j))/std_vector(j);
        }
    }
    
    bt::tuple<umatrix,uvector,uvector > * ptuple = new bt::tuple<umatrix,uvector,uvector >(new_matrix,mean_vector,std_vector);
    tuple_ptr_type result_pt(ptuple);
    return result_pt;
}


std::pair<matrix_ptr_type,long_vector_ptr_type> data_processor::load_data(std::istream& input_stream) throw (std::exception)
{
    std::vector<std::vector<float> > input_vectors;
    std::vector<long> input_labels;
  
    try{
        for (std::string line; std::getline(input_stream, line); ){
            std::vector<float> row;
            std::stringstream ss(line);
            float value;
            long label;
            bool first_value = true;
            while(!ss.eof()){
                if(first_value){
                    ss>>label;
                    first_value = false;
                    input_labels.push_back(label);
                }else{
                    ss>>value;
                    row.push_back(value);
                }
            }
            input_vectors.push_back(row);
        }
    }catch(std::exception& e){
        throw e;
    }
    long nrow = input_vectors.size();
    long ncol = input_vectors[0].size();
    matrix_ptr_type data(new umatrix(nrow,ncol));
    //copy matrix
    for (unsigned i = 0; i < nrow; ++ i){
        std::copy(input_vectors[i].begin(), input_vectors[i].end(), ublas::row(*data,i).begin());
    }
    long_vector_ptr_type labels(new longvector(input_labels.size()));
    std::copy(input_labels.begin(),input_labels.end(),labels->begin());
    return std::make_pair(data, labels);
}


matrix_ptr_type data_processor::re_zscore(matrix_ptr_type data,const uvector& mean_vector,const uvector& std_vector)
{
    long ncol = data->size2();
    long nrow = data->size1();
    matrix_ptr_type pt(new umatrix(nrow,ncol));
    for(unsigned i = 0; i < nrow; ++i){
        for (unsigned j = 0; j < ncol; ++j){
            (*pt)(i,j) = ((*data)(i,j) - mean_vector(j))/std_vector(j);
        }
    }
    return pt;
}