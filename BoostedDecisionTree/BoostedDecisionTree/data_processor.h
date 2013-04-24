//
//  data_processor.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/10/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef __BoostedDecisionTree__data_processor__
#define __BoostedDecisionTree__data_processor__

#include <iostream>
#include <vector>

class data_processor{

public:
    static void tomatrix(std::vector<std::vector<float> > input_data,bool replace_unrecognized_value, float val); 
    static void z_score(std::string data,bool replace_meanbool,bool replace_unrecognized_value, float val);
    static void redo_zero_out(std::string data,std::string mu,std::string ss,bool replace_meanbool,bool replace_unrecognized_value, float val);
};

#endif /* defined(__BoostedDecisionTree__data_processor__) */
