#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "difer.h"
#include "createnode.h"
#include "graphicdump.h"

NodeStruct* Differentiator(NodeStruct* node)
{
    if(!node)
    {
        printf("Something went wrong in Differentiator\n");
        return nullptr;
    }

    if(node->type == Number || node->type == MagicNums)
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

            NodeStruct* cL  = CopyNode(node->Left);
            NodeStruct* cR  = CopyNode(node->Right);
            NodeStruct* cR1 = CopyNode(node->Right);
            NodeStruct* cR2 = CopyNode(node->Right);

            return CreateOp(divis, CreateOp(subtr, CreateOp(mul, dL, cR), CreateOp(mul, cL, dR)), CreateOp(mul, cR1, cR2));

            break;
        }

        // case inv:
        // {
            
        // }

        case op_log:
            {
                if(node->Left->type == MagicNums && node->Left->value == mg_e)
                {
                    NodeStruct* cR = CopyNode(node->Right);

                    return CreateOp(divis, Differentiator(cR), node->Right);
                }
                else
                {
                    NodeStruct* cL = CopyNode(node->Left);
                    NodeStruct* cR = CopyNode(node->Right);

                    NodeStruct* val = CreateOp(divis, CreateOp(op_log, CreateMagicNum(mg_e), cR), CreateOp(op_log, CreateMagicNum(mg_e), cL));

                    // GraphicDump(val);

                    // exit(0);

                    return Differentiator(val);
                }

                break;
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

