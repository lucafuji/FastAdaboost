//
//  data_processor.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/10/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__data_processor__
#define __BoostedDecisionTree__data_processor__

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <exception>
#include <utility>
#include "typeredef.h"

class data_processor {
 public:
  /**
   * params: filename contains the input data
   * return a smart pointer point to the matrix representation of the input data
   */
  static std::pair<matrix_ptr_type,
                   long_vector_ptr_type> load_data(std::istream &input_stream,
                                                   bool sparse) throw(std::exception);
  /**
   * params: the input data
   * return a tuple (new_data,mean vector,standard deviation vector)
   */
  static tuple_ptr_type z_score(matrix_ptr_type data);

  /**
   * params: data the input data
   * return new data with the resized z score
   */
  static matrix_ptr_type re_zscore(matrix_ptr_type data,
                                   const uvector &mean_vector,
                                   const uvector &std_vector);
};

#endif /* defined(__BoostedDecisionTree__data_processor__) */
