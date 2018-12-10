//
//  boost_classifier.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/27/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "boost_classifier.h"
#include "matrix_util.h"
#include <algorithm>

BOOST_CLASS_EXPORT(boost_classifier)

struct expf_op {
  float operator() (float f) const {
    return expf(f);
  }
};

processed_data_ptr boost_classifier::preprocess(matrix_ptr_type data,
                                                long_vector_ptr_type labels,
                                                float eps) {
  std::cout << "boost begin preprocessing" << std::endl;
  basic_classifier =
      boost::shared_ptr<stump_classifier>(new stump_classifier());
  return basic_classifier->preprocess(data, labels, eps);
  std::cout << "boost end preprocessing" << std::endl;
}

std::pair<float, long_vector_ptr_type> boost_classifier::learn(
    processed_data_ptr p_data,
    vector_ptr_type weights) {
  std::cout << "boost begin learn" << std::endl;
  long nrow = p_data->tlabel->size();
  vector_ptr_type d(new uvector(ublas::scalar_vector<float>(nrow, 1.0 / nrow)));
  vector_ptr_type H(new uvector(ublas::zero_vector<float>(nrow)));
  for (int t = 0; t < rounds; t++) {
    boost::shared_ptr<stump_classifier> bc(new stump_classifier());
    basic_classifiers.push_back(bc);

    std::pair<float, long_vector_ptr_type> result_type = bc->learn(p_data, d);
    float error = result_type.first;
    (*bc_weights)(t) = 1.0 / 2 * log((1 - error) / error);

    long_vector_ptr_type h = result_type.second;

    (*H) += (*h) * (*bc_weights)(t);

    float z = 2 * sqrt(error * (1 - error));

    uvector exp_vec(nrow);
    // -a(t)*y(i)*h(xi)
    uvector tmp_vec(-(*bc_weights)(t) * ublas::element_prod(*(p_data->tlabel), *h));
    //exp(-a(t)*y(i)*h(xi))
    std::transform(tmp_vec.begin(), tmp_vec.end(), exp_vec.begin(), std::expf);
    *d = ublas::element_prod(*d, exp_vec) / z;
    std::cout << t + 1 << "/" << rounds << " " << (t + 1) / 1.0 / rounds * 100
              << "% completed" << std::endl;
  }

  long_vector_ptr_type h = matrix_util::judge_vector<uvector,
                                                     longvector,
                                                     larger_than_zero>(H->begin(),
                                                                       H->end());
  return std::make_pair(ublas::sum(*(matrix_util::compare_vector<longvector,
                                                                 longvector,
                                                                 longvector,
                                                                 long_not_equal>(
      p_data->tlabel->begin(),
      p_data->tlabel->end(),
      h->begin()))) / 1.0 / nrow, h);
}

long_vector_ptr_type boost_classifier::predict(matrix_ptr_type instances) {
  long nrow = instances->size1();
  vector_ptr_type H(new uvector(ublas::zero_vector<float>(nrow)));
  for (int i = 0; i < rounds; i++) {
    (*H) += ((*bc_weights)(i)) * (*(basic_classifiers[i])->predict(instances));
  }
  return matrix_util::judge_vector<uvector,
                                   longvector,
                                   larger_than_zero>(H->begin(), H->end(), -1);
}

long boost_classifier::predict(vector_ptr_type instance) {
  long p_label = 0;
  for (int i = 0; i < rounds; i++) {
    p_label += (*bc_weights)(i) * basic_classifiers[i]->predict(instance);
  }
  return p_label > 0 ? 1 : -1;
}