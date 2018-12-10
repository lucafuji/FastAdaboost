//
//  stump_classifier.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/26/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__stump_classifier__
#define __BoostedDecisionTree__stump_classifier__

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "typeredef.h"
#include "classifier.h"
#include "boost_classifier.h"

class stump_classifier : public classifier {
 public:
  friend class boost::serialization::access;

  stump_classifier() {
    v = 0;
    f = 0;
    c = 0;
  };

  stump_classifier(const stump_classifier &another) {
    v = another.v;
    f = another.f;
    c = another.c;
  };

  processed_data_ptr preprocess(matrix_ptr_type data,
                                long_vector_ptr_type labels,
                                float eps);
  std::pair<float,
            long_vector_ptr_type> learn(processed_data_ptr processed_data,
                                        vector_ptr_type weights);
  long_vector_ptr_type predict(matrix_ptr_type instances);
  long predict(vector_ptr_type instances);
 private:
  long v;
  long f;
  long c;

  template<class Ar>
  void serialize(Ar &ar, const unsigned int version) {
    ar & boost::serialization::base_object<classifier>(*this);
    ar & v;
    ar & f;
    ar & c;
  }
};

#endif /* defined(__BoostedDecisionTree__stump_classifier__) */
