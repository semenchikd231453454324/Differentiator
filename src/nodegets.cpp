#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "nodegets.h"


NodeStruct* Get(char* S)
{
    assert(S);

    GetStruct Equation = {};

    Equation.String = S;

    return GetG(&Equation);
}

NodeStruct* GetG(GetStruct* Equation)
{
    NodeStruct* val = GetE(Equation);

    if(Equation->String[Equation->ElemNumber] != '$')
    {
        printf("Syntax Error\n");

        return nullptr;
    }
    Equation->ElemNumber++;

    return val;
}

NodeStruct* GetP(GetStruct* Equation)
{
    if(Equation->String[Equation->ElemNumber] == '(')
    {
        Equation->ElemNumber++;
        NodeStruct* val = GetE(Equation);

    
        if(Equation->String[Equation->ElemNumber] != ')')
        {
            printf("Pizdec s GetP\n");
            exit(0);
        }
        Equation->ElemNumber++;
        
        return val;
    }
    else
    {
        return GetN(Equation);
    }

}

NodeStruct* GetT(GetStruct* Equation)
{
    NodeStruct* val = GetI(Equation);

    while(Equation->String[Equation->ElemNumber] == '*' || Equation->String[Equation->ElemNumber] == '/')
    {
        int op = Equation->String[Equation->ElemNumber];
        Equation->ElemNumber++;
        NodeStruct* val2 = GetI(Equation);
        if(op == '*')
        {
            val = CreateOp(mul, val, val2);
        }
        else 
        {
            val = CreateOp(divis, val, val2);

        }
    }

    return val;
}

NodeStruct* GetE(GetStruct* Equation)
{
    NodeStruct* val = GetT(Equation);

    while(Equation->String[Equation->ElemNumber] == '+' || Equation->String[Equation->ElemNumber] == '-')
    {
        int op = Equation->String[Equation->ElemNumber];
        Equation->ElemNumber++;
        NodeStruct* val2 = GetT(Equation);
        if(op == '+')
        {
            val = CreateOp(Add, val, val2);
        }
        else 
        {
            val = CreateOp(subtr, val, val2);
        }
    }

    return val;
}

NodeStruct* GetN(GetStruct* Equation)
{
    int val = 0;
    int old_p = Equation->ElemNumber;

    if(Equation->String[Equation->ElemNumber] <= '9'  && '0' <= Equation->String[Equation->ElemNumber]) // TODO isdigits
    {
        while ('0' <= Equation->String[Equation->ElemNumber] && Equation->String[Equation->ElemNumber] <= '9')
        {
            val = val * 10 + Equation->String[Equation->ElemNumber] - '0';
            Equation->ElemNumber++;
        }

        if(Equation->ElemNumber == old_p)
        {
            printf("Huynya s GetN\n");
            exit(0);
        }

        return CreateNum(val);
    }
    else if(Equation->String[Equation->ElemNumber] == 'x')
    {
        Equation->ElemNumber++;
        return CreateVar(x);
    }
    else if(Equation->String[Equation->ElemNumber] == 'l')
    {
        return GetL(Equation);
    }
    else if(Equation->String[Equation->ElemNumber] == '/')
    {
        Equation->ElemNumber++;

        if(Equation->String[Equation->ElemNumber] == 'p' && Equation->String[Equation->ElemNumber + 1] == 'i')
        {
           Equation->ElemNumber += 2;

           return CreateMagicNum(mg_pi);
        }
        else if(Equation->String[Equation->ElemNumber] == 'e')
        {
            Equation->ElemNumber += 1;

            return CreateMagicNum(mg_e);
        }
        else
        {
            printf("Unknown magic number\n");

            return nullptr;
        }
    }
    else
    {
        printf("Huynya s GetN\n");
        exit(0);
    }

    
    //return CreateNum(val);
}

NodeStruct* GetI(GetStruct* Equation)
{
    NodeStruct* val = GetP(Equation);

    while(Equation->String[Equation->ElemNumber] == '^')
    {
        Equation->ElemNumber++;

        NodeStruct* val2 = GetP(Equation);
        val = CreateOp(inv, val, val2);
    }

    return val;
}

NodeStruct* GetL(GetStruct* Equation)
{
    if(Equation->String[Equation->ElemNumber] == 'l' && Equation->String[Equation->ElemNumber + 1] == 'o' && Equation->String[Equation->ElemNumber + 2] == 'g' && Equation->String[Equation->ElemNumber + 3] == '(')
    {
        Equation->ElemNumber += 3;

        NodeStruct* val = GetP(Equation);
        NodeStruct* val2 = GetP(Equation);

        return CreateOp(op_log, val, val2);
    }

    printf("huynya s logom\n");

    return nullptr;
}