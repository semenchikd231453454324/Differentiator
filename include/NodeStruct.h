#ifndef NODESTRUCT_H
#define NODESTRUCT_H

enum Types {Number, Operation, Variable, MagicNums};
enum Operations {Add, subtr, mul, divis, inv, op_log};
enum Variables {mya, x, y};
enum Constants {mg_pi, mg_e};

struct NodeStruct
{
    int type;
    int value;
    NodeStruct* Left;
    NodeStruct* Right;
    NodeStruct* Parent;
};


#endif