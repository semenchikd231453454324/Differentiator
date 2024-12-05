#ifndef OPTIMIZATIONS_H
#define OPTIMIZATIONS_H

#include "NodeStruct.h"
#include "createnode.h"

int Optimizations(NodeStruct* Root);
int ConstantFolding(NodeStruct* node);
int TrivialOperations(NodeStruct** node);

#endif