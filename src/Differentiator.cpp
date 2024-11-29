#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "difer.h"
#include "createnode.h"

NodeStruct* Differentiator(NodeStruct* node)
{
    if(!node)
    {
        printf("Something went wrong in Differentiator\n");
        return nullptr;
    }

    if(node->type == Number)
    {
        return CreateNum(0);
    }

    if(node->type == Variable)
    {
        return CreateNum(1);
    }

    if(node->type == Operation)
    {
        switch(node->value)
        {
        case Add:
        {
            return CreateOp(Add, Differentiator(node->Left), Differentiator(node->Right));

            break;
        }
        
        case subtr:
        {
            return CreateOp(subtr, Differentiator(node->Left), Differentiator(node->Right));

            break;
        }

        case mul:
        {
            NodeStruct* dL = Differentiator(node->Left);
            NodeStruct* dR = Differentiator(node->Right);

            NodeStruct* cL = CopyNode(node->Left);
            NodeStruct* cR = CopyNode(node->Right);

            return CreateOp(Add, CreateOp(mul, dL, cR), CreateOp(mul, dR, cL));

            break;
        }

        case divis:
        {
            NodeStruct* dL = Differentiator(node->Left);
            NodeStruct* dR = Differentiator(node->Right);

            NodeStruct* cL = CopyNode(node->Left);
            NodeStruct* cR = CopyNode(node->Right);

            
        }

        default:
        {
            printf("Unkniwn operation in switch case in Differenciator(mul)");

            break;
        }
        }
    }

    printf("Kinda shit\n");

    return nullptr;
}

