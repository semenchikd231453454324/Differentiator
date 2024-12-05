#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "createnode.h"

static NodeStruct* CopyBypass(NodeStruct* node);

NodeStruct* CreateNode(int type, int value, NodeStruct* Left, NodeStruct* Right)
{
    NodeStruct* node  = (NodeStruct*) calloc(1, sizeof(NodeStruct));
    if(!node)
    {
        printf("Pizdec wih calloc pointer in CreateNode\n");
        return nullptr;
    }

    node->type = type;
    node->value = value;
    node->Left = Left;
    node->Right = Right;

    return node;
}

NodeStruct* CopyNode(NodeStruct* node)
{
    if(!node)
    {
        printf("Bad node given to copy\n");
        return nullptr;
    }

    return CopyBypass(node);
}

static NodeStruct* CopyBypass(NodeStruct* node)
{
    if(!node)
    {
        printf("Trouble with pointer in copybypass\n");

        return nullptr;
    }

    NodeStruct* CopyofNode = (NodeStruct*) calloc(1, sizeof(NodeStruct));
    if(!CopyofNode)
    {
        printf("Calloc returned nullptr in copynode\n");
        return nullptr;
    }

    CopyofNode->type = node->type;
    CopyofNode->value = node->value;

    if(node->Left)
    {
        CopyofNode->Left = CopyBypass(node->Left);
    }
    if(node->Right)
    {
        CopyofNode->Right = CopyBypass(node->Right);
    }

    return CopyofNode;
}