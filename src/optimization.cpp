#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "optimization.h"
#include "graphicdump.h"

#define REPLACE(op_enum, sign)                                          \
op_enum:                                                                \
            {                                                           \
                node->type = Number;                                    \
                                                                        \
                node->value = node->Left->value sign node->Right->value;\
                                                                        \
                free(node->Left);                                       \
                free(node->Right);                                      \
                                                                        \
                node->Left = nullptr;                                   \
                node->Right = nullptr;                                  \
                                                                        \
                return 1;                                               \
                                                                        \
                break;                                                  \
            }

int Optimizations(NodeStruct* Root)
{
    if(!Root)
    {
        printf("Bad root given to Optimizations\n");

        return 1;
    }

    int OptimizationsQuantity = 1;

    while(OptimizationsQuantity)
    {
        OptimizationsQuantity = 0;

        int temp = ConstantFolding(Root);

        //printf("temp0 = %d\n", temp);

        temp += TrivialOperations(&Root);        

        OptimizationsQuantity += temp;

        //printf("temp1 = %d\n", temp);

    }

    GraphicDump(Root);
    
    return 0;
}

int ConstantFolding(NodeStruct* node)
{
    if(node->type == Operation && node->Left && node->Right && node->Left->type == Number && node->Right->type == Number)
    {
        switch (node->value)
        {
        case REPLACE(Add, +)
        case REPLACE(subtr, -)
        case REPLACE(mul, *)
        case REPLACE(divis, /)
        
        default:
            printf("Unknown operation in folding\n");
            break;
        }
    }
    else
    {    
        if(node->Left)
        {
            if(node->Left->type == Operation)
            {
                return ConstantFolding(node->Left);
            }
        }
        if(node->Right)
        {
            if(node->Right->type == Operation)
            {
                return ConstantFolding(node->Right);
            }
        }
    }

    return 0;
}

int TrivialOperations(NodeStruct** node)
{
    if((*node)->type == Operation)
    {
        switch ((*node)->value)
        {
        case Add:
            {
                if((*node)->Left->type == Number && (*node)->Left->value == 0)
                {
                    (*node) = (*node)->Right;

                    return 1;
                }
                if((*node)->Right->type == Number && (*node)->Right->value == 0)
                {
                    (*node) = (*node)->Right;

                    return 1;
                }

                break;
            }

        case subtr:
            {
                if((*node)->Right->type == Number && (*node)->Right->value == 0)
                {
                    (*node) = (*node)->Right;

                    return 1;
                }

                break;
            }

        case mul:
            {
                if(((*node)->Left->type == Number && (*node)->Left->value == 0) || ((*node)->Right->type == Number && (*node)->Right->value == 0))
                {
                    (*node)->type = Number;
                    (*node)->value = 0;

                    free((*node)->Right);
                    free((*node)->Left);

                    (*node)->Right = nullptr;
                    (*node)->Left = nullptr;

                    return 1;
                }

                if((*node)->Left->type == Number && (*node)->Left->value == 1)
                {
                    (*node) = (*node)->Right;

                    return 1;
                }

                if((*node)->Right->type == Number && (*node)->Right->value == 1)
                {
                    (*node) = (*node)->Left;

                    return 1;
                }

                break;
            }

        case divis:
            {
                if((*node)->Left->type == Number && (*node)->Left->value == 0)
                {
                    (*node)->type = Number;
                    (*node)->value = 0;

                    free((*node)->Right);
                    free((*node)->Left);

                    (*node)->Right = nullptr;
                    (*node)->Left = nullptr;

                    return 1;
                }
                
                if((*node)->Right->type == Number &&  (*node)->Right->value == 1)
                {
                    (*node) = (*node)->Left;

                    return 1;
                }
    

                break;
            }

        
        default:
            break;
        }
    }

    if((*node)->Left)
    {
        if((*node)->Left->type == Operation)
        {
            return TrivialOperations(&((*node)->Left));
        }
    }
    if((*node)->Right)
    {
        if((*node)->Right->type == Operation)
        {
            return TrivialOperations(&((*node)->Right));
        }
    }

    return 0;
}