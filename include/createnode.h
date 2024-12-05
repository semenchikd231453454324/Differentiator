#ifndef CREATENODE_H
#define CREATENODE_H

#include "NodeStruct.h"

#define CreateNum(value)                    \
CreateNode(Number, value, nullptr, nullptr)

#define CreateOp(Operat, Left, Right)       \
CreateNode(Operation, Operat, Left, Right)

#define CreateVar(Var)                      \
CreateNode(Variable, Var, nullptr, nullptr)

#define CreateMagicNum(MagicNum)                      \
CreateNode(MagicNums, MagicNum, nullptr, nullptr)

NodeStruct* CreateNode(int type, int value, NodeStruct* Left, NodeStruct* Right);

NodeStruct* CopyNode(NodeStruct* node);

#endif