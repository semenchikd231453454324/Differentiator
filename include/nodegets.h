#ifndef NODEGETS_H
#define NODEGETS_H

#include "NodeStruct.h"
#include "createnode.h"

struct GetStruct
{
    char* String;
    int ElemNumber;
};

NodeStruct* Get(char* S);
NodeStruct* GetG(GetStruct* Equation);
NodeStruct* GetE(GetStruct* Equation);
NodeStruct* GetT(GetStruct* Equation);
NodeStruct* GetP(GetStruct* Equation);
NodeStruct* GetN(GetStruct* Equation);
NodeStruct* GetI(GetStruct* Equation);
NodeStruct* GetL(GetStruct* Equation);

#endif