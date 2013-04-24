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
    desc.add_options()
    ("help", "print help message")
    ("trainingfile", po::value<std::string>(), "training file")
    ("testfile", po::value<std::string>(), "test file")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc),vm);
    po::notify(vm);
    
    if(vm.count("help")){
        cout<<desc<<"\n";
        return 0;
    }
    
    string training_file;
    if(!vm.count("trainingfile")){
        cout<<"no training file"<<endl;
        cout<<desc<<"\n";
        return 0;
    }else{
        training_file.assign(vm["trainingfile"].as<std::string>());
        cout<<training_file<<"\n";
    }
    
    string test_file;
    if(!vm.count("testfile")){
        cout<<"no test file"<<endl;
        cout<<desc<<"\n";
        return 0;
    }else{
        test_file.assign(vm["testfile"].as<std::string>());
        cout<<test_file<<"\n";
    }
    return 0;
}

