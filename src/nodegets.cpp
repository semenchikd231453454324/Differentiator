#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "nodegets.h"

char* s;
int p;

NodeStruct* Get(char* S)
{
    assert(S);

    s = S;

    p = 0;

    return GetG();
}

NodeStruct* GetG()
{
    NodeStruct* val = GetE();

    if(s[p] != '$')
    {
        printf("Syntax Error\n");

        return nullptr;
    }
    p++;

    return val;
}

NodeStruct* GetP()
{
    if(s[p] == '(')
    {
        p++;
        NodeStruct* val = GetE();

    
        if(s[p] != ')')
        {
            printf("Pizdec s GetP\n");
            exit(0);
        }
        p++;
        
        return val;
    }
    else
    {
        return GetN();
    }

}

NodeStruct* GetT()
{
    NodeStruct* val = GetP();

    while(s[p] == '*' || s[p] == '/')
    {
        int op = s[p];
        p++;
        NodeStruct* val2 = GetP();
        if(op == '*')
        {
            val = CreateOp(mul, val, val2);
        }
        else 
        {
            val = CreateOp(divis, val, val2);             //FIXME not sure that right position

        }
    }

    return val;
}

NodeStruct* GetE()
{
    NodeStruct* val = GetT();

    while(s[p] == '+' || s[p] == '-')
    {
        int op = s[p];
        p++;
        NodeStruct* val2 = GetT();
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

NodeStruct* GetN()
{
    int val = 0;
    int old_p = p;

    if(s[p] <= '9'  && '0' <= s[p]) // TODO isdigits
    {
        while ('0' <= s[p] && s[p] <= '9')
        {
            val = val * 10 + s[p] - '0';
            p++;
        }

        if(p == old_p)
        {
            printf("Huynya s GetN\n");
            exit(0);
        }

        return CreateNum(val);
    }
    else if(s[p] == 'x')
    {
        p++;
        return CreateVar(x);
    }
    else
    {
        printf("Huynya s GetN\n");
        exit(0);
    }
    
    //return CreateNum(val);
}