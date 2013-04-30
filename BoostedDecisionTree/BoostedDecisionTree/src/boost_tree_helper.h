//
//  boost_tree_helper.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/27/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__boost_tree_helper__
#define __BoostedDecisionTree__boost_tree_helper__

#include <iostream>
#include <string>
#include <exception>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;
void train(po::variables_map vm) throw (std::exception);
void predict(po::variables_map vm) throw (std::exception);

#endif /* defined(__BoostedDecisionTree__boost_tree_helper__) */
