//
//  test.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/25/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//
#include <boost/range/algorithm/sort.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/iterator.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <iostream>
#include <iterator>
#include "data_processor.h"
#include "matrix_util.h"
#include <utility>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

#include <boost/unordered_map.hpp>
using namespace std;

int main(){
    using namespace boost::numeric::ublas;
    ublas::vector<float> v (5);
    for(int i = 0 ; i<v.size();i++){
        v(i)=i-3;
    }
    std::cout << - v << std::endl;
    std::cout << conj (v) << std::endl;
    std::cout << real (v) << std::endl;
    std::cout << imag (v) << std::endl;
    std::cout <<"trans"<< trans (v) << std::endl;
    std::cout << herm (v) << std::endl;
     cout<<"vector element_prod"<<element_prod(v,v)<<endl;
    
    cout<<"*******************************"<<endl;
    matrix<double> m (5, 5);
    for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m (i, j) = 5 * i + j;
    
    matrix<double> m2 (5, 5);
    for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m2 (i, j) = 5 * i + j;
    cout<<m<<" "<<m2<<endl;
    cout<<"matrix product"<<prod(m,m2)<<endl;
    cout<<"matrix element prod"<<element_prod(m,m2)<<endl;
    matrix_range<matrix<double> > mr (m, range (1, 3), range (1, 3));
    std::cout << mr << std::endl;

    cout<<"*******************************"<<endl;
    typedef uvector::iterator basic_iterator;
    is_non_zero<float> predicate;
    typedef boost::filter_iterator<is_non_zero<float>,basic_iterator> filter_iter;
    
    filter_iter first(predicate,v.begin(),v.end());
    filter_iter last(predicate,v.end(),v.end());
    uvector non_zero_vector(std::distance(first,last));
    std::copy(first, last,non_zero_vector.begin());
    cout<<non_zero_vector<<endl;
    cout<<"*************unit vector***************"<<endl;
    unit_vector<double> unit_vector (5);
    cout<<unit_vector<<endl;
    cout<<"*******************************"<<endl;
    boost::unordered_map<string, string> map;
    map["shit"]= "fuck";
    cout<<map["shit"]<<endl;
    cout<<"*******************************"<<endl;
    ublas::vector<float> v2 (6);
    ublas::zero_vector<float> z2 (6);
    cout<<v2<<endl;
    v2=z2;
    cout<<v2<<endl;
    cout<<"*******************************"<<endl;
    
    matrix<float> m1(5,5);
    for(int i = 0 ; i<m1.size1();i++){
        for(int j = 0 ; j<m1.size2();j++){
            m1(i,j)=i*5+j+1;
        }
    }
    umatrix range = subrange(m1, 0, 3, 0, 3) - subrange(m1, 1, 4, 1, 4);
    cout<<range<<endl;
    cout<<"*******************************"<<endl;
    ublas::vector<float> cumsum(5);
    std::partial_sum(v.begin(), v.end(), cumsum.begin(), std::plus<float>());
    cout<<cumsum<<endl;
    cout<<"*******************************"<<endl;
    ublas::vector<double> v1 (3), v3 (3);
    for (unsigned i = 0; i < std::min (v1.size (), v3.size ()); ++ i)
        v1 (i) = v3 (i) = i;
    
    std::cout << element_prod(v1,v3) << std::endl;
    cout<<"*******************************"<<endl;
    ublas::vector<double> v4(ublas::scalar_vector<double>(3,1));
    cout<<"*******************************"<<endl;
    v*=3;
    cout<<v<<endl;
    cout<<v*3<<endl;
    cout<<"*******************************"<<endl;
    cout<<(*matrix_util::arg_sort(matrix_ptr_type(new umatrix(3,3))).first)<<endl;
    cout<<"*********matrix time vector*******************"<<endl;
    scalar_matrix<long> scalar_matrix(3,5,2);
    scalar_vector<long> scalar_vector(5,1);
    cout<<prod(scalar_matrix,scalar_vector)<<endl;
    cout<<"*******************************"<<endl;
    return 0;
}