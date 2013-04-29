//
//  stump_classifier.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/26/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "stump_classifier.h"
#include "matrix_util.h"
#include <cmath>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/range.hpp>
#include <limits>
#include <numeric>
#include <cstdlib>

void stump_classifier::preprocess(matrix_ptr_type data,long_vector_ptr_type labels,float eps)
{
    std::cout<<"stump begin preprocessing"<<std::endl;
    p_data = boost::shared_ptr<processed_data>(new processed_data);
    long nrow = data->size1();
    long ncol = data->size2();
    matrix_ptr_type sorted_data(new umatrix(nrow,ncol));
    long_matrix_ptr_type lab(new longmatrix(nrow,ncol));
    long_matrix_ptr_type index(new longmatrix(nrow,ncol));
    
    std::pair<long_matrix_ptr_type,matrix_ptr_type> sorted_pair = matrix_util::arg_sort(data);
    sorted_data = sorted_pair.second;
    index = sorted_pair.first;
    
    for(long row = 0;row < nrow; ++row){
        for(long col = 0;col < ncol;++col){
            (*lab)(row,col) = (*labels)[(*index)(row,col)];
        }
    }
    longmatrix diff = ublas::subrange(*lab,0,lab->size1()-1,0,lab->size2()) - ublas::subrange(*lab,1,lab->size1(),0,lab->size2());
    // std::cout<<diff<<std::endl;
//    std::cout<<"2"<<std::endl;
//    std::cout<<*data<<std::endl;
//    std::cout<<*labels<<std::endl;
//    std::cout<<*sorted_data<<std::endl;
//    std::cout<<*index<<std::endl;
//    std::cout<<*lab<<std::endl;
//    [4,3]((2,3,4),(9,8,3),(6,9,2),(5,6,0))
//    [4](1,-1,1,-1)
//    [4,3]((2,3,0),(5,6,2),(6,8,3),(9,9,4))
//    [4,3]((0,0,3),(3,3,2),(2,1,1),(1,2,0))
//    [4,3]((1,1,-1),(-1,-1,1),(1,-1,-1),(-1,1,1))
    
 //ldiff   [3,3]((2,2,-2),(-2,0,2),(2,-2,-2))
    for(long col = 0; col < ncol; ++col){
//        std::cout<<col<<" iteration"<<std::endl;
        longmatrix_column column = ublas::column(diff,col);
        long_vector_ptr_type lstarts = matrix_util::non_zeros<longmatrix_column,longvector>(column.begin(),column.end(),1);
        (*lstarts)+=ublas::scalar_vector<long>(lstarts->size(),1);
        (*lstarts)(0)=0;
        long_vector_ptr_type lends(new longvector(lstarts->size()));
        std::copy(lstarts->begin()+1,lstarts->end(),lends->begin());
        (*lends)+=ublas::scalar_vector<long>(lends->size(),-1);
        (*lends)(lends->size()-1) = nrow-1;
//        std::cout<<"lstarts "<<*lstarts<<std::endl;
//        std::cout<<"lends "<<*lends<<std::endl;
        long_vector_ptr_type l(new longvector(lstarts->size()));
        long_vector_ptr_type v(new longvector(lstarts->size()));
        for(int i = 0;i < lstarts->size(); ++i){
            (*l)(i) = (*lab)((*lstarts)(i),col);
            (*v)(i) = (*sorted_data)((*lstarts)(i),col);
        }
//        std::cout<<"l "<<*l<<std::endl;
//        std::cout<<"v "<<*v<<std::endl;
        longvector vdiff = ublas::subrange(*v,0,v->size()-1) - ublas::subrange(*v,1,v->size());
        long_vector_ptr_type vstarts(new longvector(*(matrix_util::non_zeros<longvector,longvector>(vdiff.begin(),vdiff.end(),1,eps))));
        (*vstarts)+=ublas::scalar_vector<long>(vstarts->size(),1);
        (*vstarts)(0) = 0;
        
        long_vector_ptr_type vends(new longvector((*vstarts).size()));
        std::copy(vstarts->begin()+1,vstarts->end(),vends->begin());
        (*vends)+=ublas::scalar_vector<long>(vends->size(),-1);
        (*vends)(vends->size()-1) = lends->size()-1;
        
        stump_map_ptr map(new stump_map());
        long_vector_ptr_type nv(new longvector(v->size()));
        for(int i = 0;i < vstarts->size(); ++i){
            (*nv)(i) = (*v)((*vstarts)(i));
        }
//        std::cout<<"vstarts "<<*vstarts<<std::endl;
//        std::cout<<"vends "<<*vends<<std::endl;
//        std::cout<<"v "<<*v<<std::endl;
        (*map)["lstarts"] = lstarts;
        (*map)["lends"] = lends;
        (*map)["l"] = l;
        (*map)["vstarts"] = vstarts;
        (*map)["vends"] = vends;
        (*map)["v"] = nv;
         
        p_data->stump_map_vector.push_back(map);
//        std::cout<<col<<" end"<<std::endl;
    }
    p_data->ind = index;
    p_data->data = sorted_data;
    p_data->label = lab;
    p_data->tlabel = labels;
    p_data->tdata = data;
    std::cout<<"stump end preprocessing"<<std::endl;
}


std::pair<float,long_vector_ptr_type> stump_classifier::learn(vector_ptr_type weights)
{
    std::cout<<"stump begin learn"<<std::endl;
    float e = std::numeric_limits<float>::infinity();
    long nrow = p_data->data->size1();
    long ncol = p_data->data->size2();
    std::cout<<(*weights)<<std::endl;
    larger_than_zero ltz;
    less_than_or_equal_to_zero ltez;
    for (long col = 0;col < ncol; ++col){
        //std::cout<<col<<" iteration begins "<<std::endl;
        stump_map_ptr stump = p_data->stump_map_vector[col];
        uvector dist(weights->size());
        for(int row = 0; row < nrow; ++row){
            dist(row) = (*weights)((*p_data->ind)(row,col));
        }
        
        uvector d((*stump)["l"]->size());
        
        for(long j = 0; j<(*stump)["l"]->size(); ++j){
            d[j] = 0;
            for(long k = (*(*stump)["lstarts"])[j]; k<(*(*stump)["lstarts"])[j]+1; ++k){
                d[j] = d[j] + dist[k];
            }
        }
        
        uvector pos((*stump)["l"]->size());
        uvector neg((*stump)["l"]->size());
        float negsum;
        std::pair<long_vector_ptr_type,long_vector_ptr_type> judge_pair = matrix_util::judge_vector_pair<longvector,longvector,larger_than_zero>((*stump)["l"]->begin(), (*stump)["l"]->end(),ltz);
        
        uvector ltz_vector(ublas::element_prod(*(judge_pair.first),d));
        uvector ltez_vector(ublas::element_prod(*(judge_pair.second),d));
        std::partial_sum(ltz_vector.begin(), ltz_vector.end(), pos.begin(), std::plus<float>());
        std::partial_sum(ltez_vector.begin(), ltez_vector.end(), neg.begin(), std::plus<float>());
        negsum = ublas::sum(ltez_vector);
        //  std::cout<<"dist"<<dist<<std::endl;
      //  std::cout<<"d"<<dist<<std::endl;
      
//        std::cout<<"pos"<<pos<<std::endl;
//        std::cout<<"neg"<<neg<<std::endl;
//        std::cout<<"negsum"<<negsum<<std::endl;
        float error;
        for(long j = 0;j<(*stump)["v"]->size()-1; ++j){
            error = pos( (*(*stump)["vends"])(j) + negsum - neg((*(*stump)["vends"])(j)));
            if (error<e){
                e = error;
                v = (*(*stump)["v"])(j+1);
                f = col;
                c = 1;
            }
            
            if (1-error<e){
                e = 1-error;
                v = (*(*stump)["v"])(j+1);
                f = col;
                c = 1;
            }
        }

        //std::cout<<col<<" iteration ends "<<std::endl;
    }

    long_vector_ptr_type h(new longvector(ublas::scalar_vector<float>(nrow,1)));
    for(long row = 0; row < nrow; ++row){
        if( (*p_data->tdata)(row,f) < v){
            (*h)(row) = -1;
        }
    }
    
    if (c==-1){
        (*h) = -(*h);
    }
     std::cout<<"stump end learn"<<std::endl;
    return std::make_pair(ublas::sum(ublas::element_prod(*(matrix_util::compare_vector<longvector,longvector,longvector,long_not_equal>(p_data->tlabel->begin(), p_data->tlabel->end(), h->begin())), *weights)), h);
}


long_vector_ptr_type stump_classifier::predict(matrix_ptr_type instances){
    std::cout<<"stump begin predict"<<std::endl;
    long nrow = instances->size1();
    long_vector_ptr_type h(new longvector(ublas::scalar_vector<long>(nrow,1)));
    
    for(long row = 0; row < nrow; ++row){
        if( (*instances)(row,f) < v){
            (*h)(row) = -1;
        }
    }
    
    if (c==-1){
        (*h) = -(*h);
    }
    std::cout<<"stump end predict"<<std::endl;
    return h;
}

long stump_classifier::predict(vector_ptr_type instance)
{
    return ((*instance)(f)<v?-1:1)*c;
}