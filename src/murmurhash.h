//
//  murmurhash.h
//  BoostedDecisionTree
//
//  Created by Ze Wang on 4/28/13.
//  Copyright (c) 2013 Ze Wang. All rights reserved.
//

#ifndef BoostedDecisionTree_murmurhash_h
#define BoostedDecisionTree_murmurhash_h
#include <stdint.h>
// 64-bit hash for 64-bit platforms
uint64_t MurmurHash64A(const void *key, int len, unsigned int seed);

// 64-bit hash for 32-bit platforms
uint64_t MurmurHash64B(const void *key, int len, unsigned int seed);
#endif
