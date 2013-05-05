//
//  main.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/4/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include <iostream>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include "boost_tree_helper.h"

using namespace std;

int main(int argc, const char * argv[])
{
    po::options_description desc("Allowed options");
    //desc.add_options();
    //desc.add_options("help","print help message");
    desc.add_options()
    ("help,h", "print help message")
    ("predictor,p", po::value<std::string>(), "predictor to be called")
    ("final_predictor,f", po::value<std::string>(), "path to store the predictor")
    ("output,o", po::value<std::string>(), "path to store the predicted labels")
    ("do_feature_hashing,d","whether to do feature hashing")
    ("num_hash_bits,n", po::value<long>()->default_value(0), "number of hash bits")
    ("sparse,s", "whether the input data is sparse")
    ("nrounds,r",po::value<long>()->default_value(2), "number of rounds for adaboost")
    ("episilon,e",po::value<float>()->default_value(1e-6), "the difference between values that we accept")
    ("verbose,v", "print verbose report")
    ;
    po::variables_map vm;
    try{
        po::store(po::parse_command_line(argc, argv, desc),vm);
        po::notify(vm);
    }catch(exception e){
        cerr<<desc<<"\n";
        return 0;
    }
   
    
    if(vm.count("help")){
        cout<<desc<<"\n";
        cout<<"Sample usage:"<<endl;
        cout<<"For training: cat inputfile| ./boost_tree -f predictor"<<endl;
        cout<<"For predicting: cat inputfile| ./boost_tree -p predictor -o outputfile"<<endl;
        return 0;
    }
    
    //do training
    if(vm.count("final_predictor")){
        cout<<"do training..."<<endl;
        try{
            train(vm);
        }catch(std::exception& e){
            cerr<<"error training"<<endl;
            cerr<<desc<<"\n";
            return -1;
        }
        return 0;
    }
    
    // do testing 
    if(vm.count("predictor")){
        cout<<"do predicting ..."<<endl;
        try{
            predict(vm);
        }catch(std::exception& e){
            cerr<<"error predicting"<<endl;
            cerr<<desc<<"\n";
            return -1;
        }
        return 0;
    }
    
    cerr<<"Please either provide --final_predictor or --predictor"<<endl;
    cerr<<desc<<"\n";
    return -1;
}

