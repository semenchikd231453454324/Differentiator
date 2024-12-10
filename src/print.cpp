#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "graphicdump.h"
#include "createnode.h"
#include "print.h"

#define PRINT_OP(op_enum, sign)     \
case op_enum:                       \
{                                   \
    printf(sign);                   \
                                    \
    break;                          \
}                                   \

int print(NodeStruct* node)
{
    if(!node)
    {
        printf("Bad root given to print\n");

        return 1;
    }

    printf("(");

    if(node->Left)
    {
        print(node->Left);
    }

    if(node->type == Operation && node->value == op_log)
    {
        printf("log");
        print(node->Left);
        print(node->Right);
    }
    else
    {
        switch (node->type)
        {
            case Operation:
            {
                switch (node->value)
                {
                PRINT_OP(Add, "+")
                PRINT_OP(subtr, "-")
                PRINT_OP(mul, "*")
                PRINT_OP(divis, "/")
                PRINT_OP(inv, "^")

                default:
                    printf("Unknown operation in print\n");

                    exit(1);

                    break;
                }

                break;
            }

            case Number:
            {
                printf("%d", node->value);

                break;
            }

            case MagicNums:
            {
                if(node->value == mg_e)
                {
                    printf("e");
                }
                else
                {
                    printf("pi");
                }

                break;
            }

            case Variable:
            {
                if(node->value == x)
                {
                    printf("x");
                }

                break;
            }
        
        default:
            printf("Unknown operation in print\n");
            return 1;

            break;
        }
    }

    if(node->Right)
    {
        print(node->Right);
    }

    printf(")");

    return 0;
}
