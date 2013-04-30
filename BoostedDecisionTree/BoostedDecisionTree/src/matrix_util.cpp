//
//  matrix_util.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/25/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "matrix_util.h"


std::pair<long_matrix_ptr_type,matrix_ptr_type> matrix_util::arg_sort(matrix_ptr_type matrix,int axis)
{
    long nrow = matrix->size1();
    long ncol = matrix->size2();
    long_matrix_ptr_type index(new longmatrix(nrow,ncol));
    matrix_ptr_type sorted_matrix(new umatrix(nrow,ncol));
    // do column sorting
    if(axis == 0){
        for(long j = 0;j < ncol; j++){
            ublas::unbounded_array<std::pair<float,long> > valueIndexVectors(nrow);
            for(long i = 0;i < nrow;i++){
                valueIndexVectors[i] = std::make_pair((*matrix)(i,j),i);
            }
            sort(boost::iterator_range<ublas::unbounded_array<std::pair<float,long> > ::iterator>(valueIndexVectors.begin(),valueIndexVectors.end()));
            for(long i = 0;i<nrow;i++){
                (*index)(i,j) =valueIndexVectors[i].second;
                (*sorted_matrix)(i,j) = valueIndexVectors[i].first;
            }
        }
    }else{// do row sorting
        for(long i = 0;i < nrow; i++){
            ublas::unbounded_array<std::pair<float,long> > valueIndexVectors(ncol);
            for(long j = 0;j<ncol;j++){
                valueIndexVectors[j] = std::make_pair((*matrix)(i,j),j);
            }
            sort(boost::iterator_range<ublas::unbounded_array<std::pair<float,long> > ::iterator>(valueIndexVectors.begin(),valueIndexVectors.end()));
            for(long j = 0;i<ncol;i++){
                (*index)(i,j) = valueIndexVectors[j].second;
                (*sorted_matrix)(i,j) = valueIndexVectors[i].first;
            }
        }
    }
    return std::make_pair(index,sorted_matrix);
}