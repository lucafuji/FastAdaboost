//
//  typeredef.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/25/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef BoostedDecisionTree_typeredef_h
#define BoostedDecisionTree_typeredef_h
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/container/list.hpp>

namespace ublas = boost::numeric::ublas;
namespace bt = boost::tuples;
namespace bc = boost::container;

typedef ublas::matrix<float> umatrix;
typedef ublas::matrix<long> longmatrix;
typedef ublas::vector<float> uvector;
typedef ublas::vector<long> longvector;
typedef ublas::matrix_row<umatrix> umatrix_row;
typedef ublas::matrix_column<umatrix> umatrix_column;
typedef ublas::matrix_row<longmatrix> longmatrix_row;
typedef ublas::matrix_column<longmatrix> longmatrix_column;


typedef boost::shared_ptr<bt::tuple<umatrix,uvector,uvector > > tuple_ptr_type;
typedef boost::shared_ptr<umatrix> matrix_ptr_type;
typedef boost::shared_ptr<longmatrix> long_matrix_ptr_type;
typedef boost::shared_ptr<uvector> vector_ptr_type;
typedef boost::shared_ptr<longvector> long_vector_ptr_type;
#endif
