#ifndef NODESTRUCT_H
#define NODESTRUCT_H

enum Types {Number, Operation, Variable};
enum Operations {Add, subtr, mul, divis};
enum Variables {mya, x, y};

struct NodeStruct
{
    int type;
    int value;
    NodeStruct* Left;
    NodeStruct* Right;
    NodeStruct* Parent;
};


#endif