//
//  Instance.cpp
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/4/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#include "Instance.h"
#include <functional>
#include <algorithm>
#include "stringutil.h"


instance::entry make_pair(double weight,double value){
    return std::make_pair(weight,value);
}

std::auto_ptr<std::vector<instance>> loadInstances(char* filename,char seperator) throw (){
    std::ifstream input(filename);
    if(!input.is_open()){
        throw new std::ifstream::failure("the file cannot be open");
    }
    std::vector<instance>* instances = new std::vector<instance>;
    std::string line;
    while(!input.eof()){
        std::getline(input, line);
        std::vector<std::string> elements;
        split(line, seperator, elements);
        int label;
        int result = strtoint(label,elements[0].c_str());
        if(result<0){
            throw new std::ifstream::failure("Invalid format");
        }
        
        std::vector<instance::entry>* entries = new std::vector<instance::entry>;
        std::pointer_to_binary_function<double,double,instance::entry>  func(&make_pair);
        std::transform(elements.begin()+1,elements.end(),entries->begin(), std::bind1st(func,1.0));
        instance instance(entries);
        instance.setLabel(label);
        instances->push_back(instance);
    }
    
    return std::auto_ptr<std::vector<instance>>(instances);
}