//
//  main.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/4/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include <iostream>
//#include "stringutil.h"
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;
using namespace std;

int main(int argc, const char * argv[])
{
    po::options_description desc("Allowed options");
    //desc.add_options();
    //desc.add_options("help","print help message");
     cout<<"shit"<<endl;
    desc.add_options()
    ("help", "print help message")
    ("trainingfile", po::value<std::string>(), "training file")
    ("testfile", po::value<std::string>(), "test file")
    ("do_feature_hashing","number of hash bits")
    ("num_hashbit", po::value<int>(), "number of hash bits")
    ;
    po::variables_map vm;
    try{
        po::store(po::parse_command_line(argc, argv, desc),vm);
        po::notify(vm);
    }catch(exception e){
        cout<<desc<<"\n";
        return 0;
    }
   
    
    if(vm.count("help")){
        cout<<desc<<"\n";
        return 0;
    }
    
    if(!vm.count("trainingfile")){
        cout<<"no training file"<<endl;
        cout<<desc<<"\n";
        return 0;
    }
    
    if(!vm.count("testfile")){
        cout<<"no test file"<<endl;
        cout<<desc<<"\n";
        return 0;
    }
    
    if(!vm.count("do_feature_hashing")){
        cout<<"do feature hashing"<<endl;
    }
    cout<<"shit"<<endl;
    return 0;
}

