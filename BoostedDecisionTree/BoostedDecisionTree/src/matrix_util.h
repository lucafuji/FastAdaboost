//
//  matrix_util.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/25/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__matrix_util__
#define __BoostedDecisionTree__matrix_util__

#include <iostream>
#include "typeredef.h"
#include "data_processor.h"
#include "math_util.h"
#include <utility>
#include <boost/range/algorithm/sort.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <iostream>
#include <boost/numeric/ublas/storage.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/iterator_range_io.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <iterator>
#include <vector>
class matrix_util{
public:
    template <class Matrix_Type>
        static std::pair<long_matrix_ptr_type,boost::shared_ptr<Matrix_Type> > arg_sort(boost::shared_ptr<Matrix_Type > matrix,int axis = 0);

    template <class InputType,class ReturnType>
        static boost::shared_ptr<ReturnType> non_zeros(typename InputType::iterator begin,typename InputType::iterator end,int extra_dimension = 0,double eps = EPS);
    
    template <class InputType,class ReturnType,class Predicate>
        static boost::shared_ptr<ReturnType> judge_vector(typename InputType::iterator begin,typename InputType::iterator end,int negative_value = 0,Predicate predicate = Predicate());
    
    template <class InputType,class ReturnType,class Predicate>
        static std::pair<boost::shared_ptr<ReturnType>,boost::shared_ptr<ReturnType> > judge_vector_pair(typename InputType::iterator begin,typename InputType::iterator end,int negative_value = 0,Predicate predicate = Predicate());
    
    template <class Type1,class Type2,class ReturnType,class Predicate>
        static boost::shared_ptr<ReturnType> compare_vector(typename Type1::iterator begin1,typename Type1::iterator end1,typename Type2::iterator begin2,Predicate predicate = Predicate());
    
};

template <class Matrix_Type>
    std::pair<long_matrix_ptr_type,boost::shared_ptr<Matrix_Type> > matrix_util::arg_sort(boost::shared_ptr<Matrix_Type> matrix,int axis)
{
    typedef boost::shared_ptr<Matrix_Type> m_ptr_type;
    long nrow = matrix->size1();
    long ncol = matrix->size2();
    long_matrix_ptr_type index(new longmatrix(nrow,ncol));
    m_ptr_type sorted_matrix(new Matrix_Type(nrow,ncol));
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


template <class InputType,class ReturnType>
boost::shared_ptr<ReturnType> matrix_util::non_zeros(typename InputType::iterator begin,typename InputType::iterator end,int extra_dimension,double eps)
{
    is_non_zero<typename InputType::value_type> predicate;
    typedef typename InputType::iterator Iterator;
    int index = 0;
    std::vector<typename ReturnType::value_type> result_vector;
    for(Iterator iter = begin;iter!=end;iter++){
        if(predicate(*iter)){
            result_vector.push_back(index);
        }
        index++;
    }
    boost::shared_ptr<ReturnType> result(new ReturnType(result_vector.size()+extra_dimension));
    std::copy(result_vector.begin(),result_vector.end(),result->begin()+extra_dimension);
    return result;
}


template <class InputType,class ReturnType,class Predicate>
boost::shared_ptr<ReturnType> matrix_util::judge_vector(typename InputType::iterator begin,typename InputType::iterator end,int negative_value,Predicate predicate)
{
    boost::shared_ptr<ReturnType> result(new ReturnType(std::distance(begin, end)));
    typedef typename InputType::iterator Iterator;
    typedef typename ReturnType::iterator ReturnIterator;
    ReturnIterator result_iter = result->begin();
    for(Iterator iter = begin;iter!=end;++iter,++result_iter){
        *result_iter = predicate(*iter)?1:negative_value;
    }
    return result;
}


template <class InputType,class ReturnType,class Predicate>
std::pair<boost::shared_ptr<ReturnType>,boost::shared_ptr<ReturnType> > matrix_util::judge_vector_pair(typename InputType::iterator begin,typename InputType::iterator end,int negative_value,Predicate predicate)
{
    typedef typename InputType::iterator Iterator;
    typedef typename ReturnType::iterator ReturnIterator;
    boost::shared_ptr<ReturnType> result1(new ReturnType(std::distance(begin, end)));
    boost::shared_ptr<ReturnType> result2(new ReturnType(std::distance(begin, end)));
    ReturnIterator result1_iter = result1->begin();
    ReturnIterator result2_iter = result2->begin();
    for(Iterator iter = begin;iter!=end;++iter,++result1_iter,++result2_iter){
        if(predicate(*iter)){
            *result1_iter = 1;
            *result2_iter = negative_value;
        }else{
            *result1_iter = negative_value;
            *result2_iter = 1;
        }
    }
    return std::make_pair(result1, result2);
}


template <class Type1,class Type2,class ReturnType,class Predicate>
boost::shared_ptr<ReturnType> matrix_util::compare_vector(typename Type1::iterator begin1,typename Type1::iterator end1,typename Type2::iterator begin2,Predicate predicate)
{
    typedef typename Type1::iterator Iterator1;
    typedef typename Type2::iterator Iterator2;
    typedef typename ReturnType::iterator ReturnIterator;
    boost::shared_ptr<ReturnType> result(new ReturnType(std::distance(begin1, end1)));
    
    Iterator2 iter2 = begin2;
    ReturnIterator result_iter = result->begin();
    for(Iterator1 iter1 = begin1; iter1!=end1 ; ++iter1,++iter2,++result_iter){
        *result_iter = predicate(*iter1,*iter2)?1:0;
    }
    return result;
}
#endif /* defined(__BoostedDecisionTree__matrix_util__) */
