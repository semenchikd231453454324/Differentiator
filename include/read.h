#ifndef READ_H
#define READ_H

#include "NodeStruct.h"

struct ReadStruct
{
    NodeStruct* Root;
    size_t depth;
    size_t CurrentNum;
    bool IsRight;
};

NodeStruct* Read();

#endif