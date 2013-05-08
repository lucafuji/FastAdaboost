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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

tuple_ptr_type data_processor::z_score(matrix_ptr_type data)
{
    std::cout<<"Begin normalizing"<<std::endl;
    long ncol = data->size2();
    long nrow = data->size1();
    vector_ptr_type mean_vector(new uvector(ncol));
    vector_ptr_type std_vector(new uvector(ncol));
    for (unsigned j = 0; j < ncol; ++ j){
        (*mean_vector)(j)= 0;
        for(unsigned i = 0; i < nrow; ++i){
            ((*mean_vector)(j)) = (1-1.0/(i+1))*((*mean_vector)(j)) + 1.0/(i+1)*((*data)(i,j));
        }
    }
    
    for (unsigned j = 0; j < ncol; ++ j){
        (*std_vector)(j) = 0;
        for(unsigned i = 0; i < nrow; ++i){
            (*std_vector)(j) = (1-1.0/(i+1))*((*std_vector)(j)) + 1.0/(i+1)*pow((*data)(i,j) - ((*mean_vector)(j)),2.0);
        }
    }
    
    matrix_ptr_type new_matrix(new umatrix(nrow,ncol));
    for(unsigned i = 0; i < nrow; ++i){
        for (unsigned j = 0; j < ncol; ++j){
            (*new_matrix)(i,j) = ((*data)(i,j) - ((*mean_vector)(j)))/((*std_vector)(j));
        }
    }
    
    bt::tuple<matrix_ptr_type,vector_ptr_type,vector_ptr_type > * ptuple = new bt::tuple<matrix_ptr_type,vector_ptr_type,vector_ptr_type >(new_matrix,mean_vector,std_vector);
    tuple_ptr_type result_pt(ptuple);
    std::cout<<"End normalizing"<<std::endl;
    return result_pt;
}


std::pair<matrix_ptr_type,long_vector_ptr_type> data_processor::load_data(std::istream& input_stream,bool sparse) throw (std::exception)
{
    std::vector<std::vector<float> > input_vectors;
    std::vector<std::vector<long> > input_vectors_index;
    std::vector<long> input_labels;
    std::vector<std::string> pair_vector;
    long non_zeros = 0;
    long number_features;
    try{
        std::string line;
        if(sparse){
            //read number of features from first line
            std::getline(input_stream, line);
            std::stringstream ss(line);
            ss>>number_features;
        }
        
        std::vector<float> row;
        std::vector<long> index_row;
        std::vector<std::string> pair_vector;
        for (;std::getline(input_stream, line); ){
            std::stringstream ss(line);
            std::string feature_value_pair;
           
            long label;
            bool first_value = true;
            while(!ss.eof()){
                if(first_value){
                    ss>>label;
                    first_value = false;
                    input_labels.push_back(label);
                }else{
                    
                    ss>>feature_value_pair;
                    boost::split(pair_vector, feature_value_pair,boost::is_any_of(":"));
                    if(pair_vector.size() < 2){
                        std::cerr<<"Invalid input format"<<std::endl;
                        throw std::exception();
                    }
                    row.push_back(::atof(pair_vector[1].c_str()));
                    if(sparse){
                         index_row.push_back(::atoi(pair_vector[0].c_str())-1);
                    }
                    non_zeros++;
                }
            }
            input_vectors.push_back(row);
            row.clear();
            
            if(sparse){
                input_vectors_index.push_back(index_row);
                index_row.clear();
            }
        }
    }catch(std::exception& e){
        throw e;
    }
    long nrow = input_vectors.size();
    long ncol = input_vectors[0].size();
    matrix_ptr_type data;
    if(sparse){
        data =  matrix_ptr_type(new umatrix(ublas::zero_matrix<float>(nrow,number_features)));
        //matrix_ptr_type data((ublas::zero_matrix<float>(nrow,number_features)));
        for (unsigned i = 0; i < nrow; ++ i){
            std::vector<float>::iterator value_iter;
            std::vector<long>::iterator index_iter;
            for(value_iter = input_vectors[i].begin(), index_iter = input_vectors_index[i].begin() ;value_iter != input_vectors[i].end(); ++value_iter,++index_iter){
                (*data)(i,*index_iter) = *value_iter;
            }
        }
    }else{
        data = matrix_ptr_type(new umatrix(nrow,ncol,non_zeros));
        for (unsigned i = 0; i < nrow; ++ i){
            std::copy(input_vectors[i].begin(), input_vectors[i].end(), ublas::row(*data,i).begin());
        }
    }
    //copy matrix
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