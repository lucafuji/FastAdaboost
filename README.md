[![Build Status](https://travis-ci.com/lucafuji/FastAdaboost.svg?branch=master)](https://travis-ci.com/lucafuji/FastAdaboost)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Flucafuji%2FFastAdaboost.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Flucafuji%2FFastAdaboost?ref=badge_shield)
[![Gitter chat](https://badges.gitter.im/FastAdaboost/community.png)](https://gitter.im/FastAdaboost/community)

Fast Adaboost 
===============================================

Fast Adaboost is a AdaBoost library for classification task implemented in C++. AdaBoost, short for Adaptive Boosting, is a meta machine learning algorithm that can be used in conjunction with many other learning algorithms to improve their performance. Its main idea is to use weak learner to create strong learners and subsequent classifiers builtare tweaked in favor of those instances misclassified by previous classifier. One kind of weak classifiers is decision tree that uses some heuristics to find suboptimal trees such as using information gain or gini impurity. However most of those heuristics are too slow. This library aims at implementing a fast ada-boost library based on decision tree classifiers. Also, I will use feature hashing trick to deal with high dimension sparse data

Build
===============================================
To compile and build the program, you need to meet following prerequisites:

* cmake >= 3.9.2
* g++ >= 4.9.2
* boost lib >= 1.54.0

You can install boost library from http://www.boost.org/users/download/

Then you can use following commands to build and run the program
```$bash
cmake CMakeLists.txt
make
./FastAdaboost
```


Fast Heuristic Decision Tree
===============================================

Preprocessing the data by clustering data points with same label and data points with close value along each feature.
Try to find the best value threshold along each feature.

Feature Hashing
===============================================

Feature hashing is an effective strategy for dimensionality reduction and practical nonparametric estimation.Feature Hashing for Large Scale Multitask Learning show that interaction between random subspaces is negligible with high probability.
In this library I apply feature hashing to the data to further speed up the learning and predicting phase.


## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Flucafuji%2FFastAdaboost.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Flucafuji%2FFastAdaboost?ref=badge_large)
