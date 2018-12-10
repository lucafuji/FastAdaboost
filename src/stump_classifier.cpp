//
//  stump_classifier.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/26/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "stump_classifier.h"
#include "matrix_util.h"
#include <numeric>
#include <boost/numeric/ublas/vector_proxy.hpp>

BOOST_CLASS_EXPORT(stump_classifier)

processed_data_ptr stump_classifier::preprocess(matrix_ptr_type data,
                                                long_vector_ptr_type labels,
                                                float eps) {
  processed_data_ptr p_data = processed_data_ptr(new processed_data);
  long nrow = data->size1();
  long ncol = data->size2();
  matrix_ptr_type sorted_data(new umatrix(nrow, ncol));
  long_matrix_ptr_type lab(new longmatrix(nrow, ncol));
  long_matrix_ptr_type index(new longmatrix(nrow, ncol));

  std::pair<long_matrix_ptr_type, matrix_ptr_type>
      sorted_pair = matrix_util::arg_sort(data);
  sorted_data = sorted_pair.second;
  index = sorted_pair.first;

  for (long row = 0; row < nrow; ++row) {
    for (long col = 0; col < ncol; ++col) {
      (*lab)(row, col) = (*labels)[(*index)(row, col)];
    }
  }
  longmatrix diff = ublas::subrange(*lab, 0, lab->size1() - 1, 0, lab->size2())
      - ublas::subrange(*lab, 1, lab->size1(), 0, lab->size2());
  for (long col = 0; col < ncol; ++col) {
    longmatrix_column column = ublas::column(diff, col);
    long_vector_ptr_type lstarts =
        matrix_util::non_zeros<longmatrix_column, longvector>(column.begin(),
                                                              column.end(),
                                                              1);
    (*lstarts) += ublas::scalar_vector<long>(lstarts->size(), 1);
    (*lstarts)(0) = 0;
    long_vector_ptr_type lends(new longvector(lstarts->size()));
    std::copy(lstarts->begin() + 1, lstarts->end(), lends->begin());
    (*lends) += ublas::scalar_vector<long>(lends->size(), -1);
    (*lends)(lends->size() - 1) = nrow - 1;

    long_vector_ptr_type l(new longvector(lstarts->size()));
    long_vector_ptr_type v(new longvector(lstarts->size()));
    for (int i = 0; i < lstarts->size(); ++i) {
      (*l)(i) = (*lab)((*lstarts)(i), col);
      (*v)(i) = (*sorted_data)((*lstarts)(i), col);
    }
    longvector vdiff = ublas::subrange(*v, 0, v->size() - 1)
        - ublas::subrange(*v, 1, v->size());
    long_vector_ptr_type vstarts(new longvector(*(matrix_util::non_zeros<
        longvector,
        longvector>(vdiff.begin(), vdiff.end(), 1, eps))));
    (*vstarts) += ublas::scalar_vector<long>(vstarts->size(), 1);
    (*vstarts)(0) = 0;

    long_vector_ptr_type vends(new longvector((*vstarts).size()));
    std::copy(vstarts->begin() + 1, vstarts->end(), vends->begin());
    (*vends) += ublas::scalar_vector<long>(vends->size(), -1);
    (*vends)(vends->size() - 1) = lends->size() - 1;

    stump_map_ptr map(new stump_map());
    long_vector_ptr_type nv(new longvector(vstarts->size()));
    for (int i = 0; i < vstarts->size(); ++i) {
      (*nv)(i) = (*v)((*vstarts)(i));
    }
    (*map)["lstarts"] = lstarts;
    (*map)["lends"] = lends;
    (*map)["l"] = l;
    (*map)["vstarts"] = vstarts;
    (*map)["vends"] = vends;
    (*map)["v"] = nv;

    p_data->stump_map_vector.push_back(map);
  }
  p_data->ind = index;
  p_data->data = sorted_data;
  p_data->label = lab;
  p_data->tlabel = labels;
  p_data->tdata = data;
  return p_data;
}

std::pair<float, long_vector_ptr_type> stump_classifier::learn(
    processed_data_ptr p_data,
    vector_ptr_type weights) {
  float e = 1.2;
  long nrow = p_data->data->size1();
  long ncol = p_data->data->size2();
  larger_than_zero ltz;
  less_than_or_equal_to_zero ltez;
  for (long col = 0; col < ncol; ++col) {
    stump_map_ptr stump = p_data->stump_map_vector[col];
    uvector dist(weights->size());
    for (int row = 0; row < nrow; ++row) {
      dist(row) = (*weights)((*p_data->ind)(row, col));
    }

    uvector d(ublas::zero_vector<float>((*stump)["l"]->size()));

    for (long j = 0; j < (*stump)["l"]->size(); ++j) {
      for (long k = (*(*stump)["lstarts"])[j]; k < (*(*stump)["lends"])[j] + 1;
           ++k) {
        d[j] = d[j] + dist[k];
      }
    }

    uvector pos((*stump)["l"]->size());
    uvector neg((*stump)["l"]->size());
    float negsum;
    std::pair<long_vector_ptr_type, long_vector_ptr_type> judge_pair =
        matrix_util::judge_vector_pair<longvector,
                                       longvector,
                                       larger_than_zero>((*stump)["l"]->begin(),
                                                         (*stump)["l"]->end(),
                                                         0,
                                                         ltz);

    uvector ltz_vector(ublas::element_prod(*(judge_pair.first), d));
    uvector ltez_vector(ublas::element_prod(*(judge_pair.second), d));
    std::partial_sum(ltz_vector.begin(),
                     ltz_vector.end(),
                     pos.begin(),
                     std::plus<float>());
    std::partial_sum(ltez_vector.begin(),
                     ltez_vector.end(),
                     neg.begin(),
                     std::plus<float>());
    negsum = ublas::sum(ltez_vector);

    float error;
    for (long j = 0; j < (*stump)["v"]->size() - 1; ++j) {
      error =
          pos((*(*stump)["vends"])(j)) + negsum - neg((*(*stump)["vends"])(j));
      if (error < e && fabs(e - error) > 1e-5) {
        e = error;
        v = (*(*stump)["v"])(j + 1);
        f = col;
        c = 1;
      }

      if (1 - error < e && fabs(e + error - 1) > 1e-5) {
        e = 1 - error;
        v = (*(*stump)["v"])(j + 1);
        f = col;
        c = -1;
      }
    }
  }

  long_vector_ptr_type h(new longvector(ublas::scalar_vector<float>(nrow, 1)));
  for (long row = 0; row < nrow; ++row) {
    if ((*p_data->tdata)(row, f) < v) {
      (*h)(row) = -1;
    }
  }

  if (c == -1) {
    (*h) = -(*h);
  }

  return std::make_pair(ublas::sum(ublas::element_prod(*(matrix_util::compare_vector<
      longvector,
      longvector,
      longvector,
      long_not_equal>(p_data->tlabel->begin(),
                      p_data->tlabel->end(),
                      h->begin())), *weights)), h);
}

long_vector_ptr_type stump_classifier::predict(matrix_ptr_type instances) {
  long nrow = instances->size1();
  long_vector_ptr_type h(new longvector(ublas::scalar_vector<long>(nrow, 1)));

  for (long row = 0; row < nrow; ++row) {
    if ((*instances)(row, f) < v) {
      (*h)(row) = -1;
    }
  }

  if (c == -1) {
    (*h) = -(*h);
  }
  return h;
}

long stump_classifier::predict(vector_ptr_type instance) {
  return ((*instance)(f) < v ? -1 : 1) * c;
}