//
//  boost_tree_helper.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/27/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "boost_tree_helper.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "stump_classifier.h"
#include "feature_hashing_classifier.h"
#include "data_processor.h"

void print_verbose_report(long_vector_ptr_type predicted_labels,
                          long_vector_ptr_type original_labels) {
  long tp = 0;
  long fp = 0;
  long fn = 0;
  float precision, recall, error;

  for (long i = 0; i < predicted_labels->size(); i++) {
    if ((*predicted_labels)(i) * (*original_labels)(i)
        > 0) {// correct prediction
      if ((*predicted_labels)(i) > 0) {
        tp++;
      }
    } else {// error prediction
      if ((*predicted_labels)(i) > 0) {
        fp++;
      } else {
        fn++;
      }
    }
  }
  long all_predicted_p = tp + fp;
  long all_p = tp + fn;

  precision = all_p != 0 ? tp / 1.0 / all_p : 0;
  recall = all_predicted_p != 0 ? tp / 1.0 / all_predicted_p : 0;
  error = (fp + fn) / 1.0 / predicted_labels->size();
  std::cout << "Precision is " << precision << std::endl;
  std::cout << "Recall is " << recall << std::endl;
  std::cout << "Error rate is " << error << std::endl;
}

void train(po::variables_map vm) throw(std::exception) {
  std::ofstream ofs;
  try {
    ofs.open(vm["final_predictor"].as<std::string>().c_str());
    std::pair<matrix_ptr_type, long_vector_ptr_type>
        data_pair = data_processor::load_data(std::cin, vm.count("sparse"));
    classifier *classifier_ptr;
    if (vm.count("do_feature_hashing")) {
      std::cout << "do feature hashing" << std::endl;
      classifier_ptr =
          new feature_hashing_classifier(new boost_classifier(vm["nrounds"].as<
              long>()), vm["num_hash_bits"].as<long>());
    } else {
      std::cout << "no feature hashing" << std::endl;
      classifier_ptr = new boost_classifier(vm["nrounds"].as<long>());
    }
    matrix_ptr_type data = data_pair.first;
    long_vector_ptr_type labels = data_pair.second;

    if (vm.count("normalize")) {
      data = data_processor::z_score(data)->get<0>();
    }
    processed_data_ptr p_data =
        classifier_ptr->preprocess(data, labels, vm["episilon"].as<float>());

    vector_ptr_type weights(new uvector(0));//stub weights for boost classifier
    classifier_ptr->learn(p_data, weights);
    {
      boost::archive::text_oarchive oa(ofs);
      std::cout << "storing classifier...." << std::endl;
      oa << classifier_ptr;
      std::cout << "store successfully!" << std::endl;
    }

  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    throw e;
  }

}

void predict(po::variables_map vm) throw(std::exception) {
  if (!vm.count("output")) {
    std::cerr << "please specified the output path for prediction results"
              << std::endl;
    throw std::exception();
  }

  std::ifstream predictor_ifs;
  std::ofstream result_ofs;

  try {
    predictor_ifs.open(vm["predictor"].as<std::string>().c_str());
    result_ofs.open(vm["output"].as<std::string>().c_str());
    std::pair<matrix_ptr_type, long_vector_ptr_type>
        data_pair = data_processor::load_data(std::cin, vm.count("sparse"));

    classifier *classifier;
    {
      boost::archive::text_iarchive ia(predictor_ifs);
      //   register_all_classifier(ia);
      std::cout << "loading classifier...." << std::endl;
      ia >> classifier;
      std::cout << "load successfully!" << std::endl;
    }

    matrix_ptr_type data = data_pair.first;
    long_vector_ptr_type labels = data_pair.second;

    if (vm.count("normalize")) {
      data = data_processor::z_score(data)->get<0>();
    }

    long_vector_ptr_type predicted_labels = classifier->predict(data);
    std::cout << "predicting successfully!" << std::endl;
    std::copy(predicted_labels->begin(),
              predicted_labels->end(),
              std::ostream_iterator<float>(result_ofs, "\n"));

    if (vm.count("verbose")) {//print verbose report
      print_verbose_report(predicted_labels, labels);
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    throw e;
  }
}