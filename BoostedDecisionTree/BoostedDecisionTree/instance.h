//
//  instance.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/4/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__instance__
#define __BoostedDecisionTree__instance__

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <memory>

class instance{
public:
    typedef std::pair<double,double> entry;
    instance(){
        entries = new std::vector<entry>;
    }
    
    ~instance(){
        delete entries;
    }
    
    instance(std::vector<entry>* entries):entries(entries){
        
    }
    
    float getValue(int n) const{
        return entries->at(n).second;
    }
    
    float getWeight(int n) const{
        return entries->at(n).first;
    }
    
    int getLabel() const{
        return label;
    }
    
    void setValue(int n,float value){
        entries->at(n).second = value;
    }
    
    void setWeight(int n, float value){
        entries->at(n).first = value;
    }
    
    void setLabel(int label){
        this->label = label;
    }
    
    void add_entry(float value,float weight = 1.0f){
        entries->push_back(std::make_pair(value, weight));
    }
    
private:
    std::vector<entry>* entries;
    int label;
};

std::auto_ptr<std::vector<instance> > loadInstances(char* filename,char seperator) throw ()

#endif /* defined(__BoostedDecisionTree__instance__) */
