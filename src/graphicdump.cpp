#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "graphicdump.h"

struct ArrowStruct
{
    NodeStruct* ParentName;
    NodeStruct* ChildName;
    bool Direction;
};

struct GraphicStruct
{
    ArrowStruct ArrowArray[300];
    size_t ArrowsQuantity;
};

static int GraphicBypass(NodeStruct* node, GraphicStruct* Arrows, FILE* dumppicture);

int GraphicDump(NodeStruct* Root)
{
    if(!Root)
    {
        printf("Bad root given to GraphicDump\n");

        return 1;
    }

    FILE* dumppicture = fopen("dumppicture.gv", "w");
    if(!dumppicture)
    {
        printf("pizdec to dumpicturepointer\n");
    }

    fprintf(dumppicture, "digraph G\n{\nnode [shape=\"record\"];\n");

    GraphicStruct Arrows = {};

    GraphicBypass(Root, &Arrows, dumppicture);

    if(Arrows.ArrowsQuantity)
    {
        for(size_t CurrentArrow = 0; CurrentArrow < Arrows.ArrowsQuantity; CurrentArrow++)
            {
                fprintf(dumppicture, "\"%p\"->\"%p\"\n", Arrows.ArrowArray[CurrentArrow].ParentName, Arrows.ArrowArray[CurrentArrow].ChildName);
            }
    }
    else
    {
        fprintf(dumppicture, "\"%p\"", Root);
    }
    
    fprintf(dumppicture, "}");

    fclose(dumppicture);

    system("dot -Tpng dumppicture.gv -o irpenis.png");

    return 0;
}

static int GraphicBypass(NodeStruct* node, GraphicStruct* Arrows, FILE* dumppicture)
{
    assert(Arrows);
    if(!node)
    {
        printf("Bad pointer given to Bypass\n");
        return 1;
    }

    switch (node->type)
    {

    case Number:
        {
            fprintf(dumppicture, "\"%p\" [color=green, label = \"{%p | Number | %d | {%p | %p}}\" ];\n", node, node, node->value, node->Left, node->Right);
        
            break;
        }

    case Operation:
        {
            switch (node->value)
            {
            case Add:
                {
                    fprintf(dumppicture, "\"%p\" [color=red,label = \"{%p | Operation | + | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }

            case subtr:
                {
                    fprintf(dumppicture, "\"%p\" [color=red,label = \"{%p | Operation | - | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }

            case mul:
                {
                    fprintf(dumppicture, "\"%p\" [color=red,label = \"{%p | Operation | * | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }

            case divis:
                {
                    fprintf(dumppicture, "\"%p\" [color=red,label = \"{%p | Operation | / | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }

            case inv:
                {
                    fprintf(dumppicture, "\"%p\" [color=red,label = \"{%p | Operation | ^ | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }

            case op_log:
                {
                    fprintf(dumppicture, "\"%p\" [color=red,label = \"{%p | Operation | log | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }
            
            default:
                {
                    printf("Unknown operation in graphicdump\n");

                    break;
                }
            }

            break;
        }

    case Variable:
        {
            switch (node->value)
            {
            case x:
                {
                    fprintf(dumppicture, "\"%p\" [color=blue,label = \"{%p | Variable | x | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);
                    break;
                }

            default:
                printf("eeee nu chot ne ponyatno s variable\n");
                break;
            }

            break;
        }

    case MagicNums:
        {
            switch (node->value)
            {
            case mg_pi:
                {
                    fprintf(dumppicture, "\"%p\" [color=yellow,label = \"{%p | Magic Num | pi | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }
            
            case mg_e:
                {
                    fprintf(dumppicture, "\"%p\" [color=yellow,label = \"{%p | Magic Num | e | {%p | %p}}\" ];\n", node, node, node->Left, node->Right);

                    break;
                }

            default:
                break;
            }

            break;
        }

    default:
        {
        printf("eeee nu chot ne ponyatno s tipom\n");
        break;
        }
    }


    if(node->Left)
    {
        Arrows->ArrowArray[Arrows->ArrowsQuantity].ParentName = node;
        Arrows->ArrowArray[Arrows->ArrowsQuantity].ChildName = node->Left;

        Arrows->ArrowArray[Arrows->ArrowsQuantity].Direction = 1;
    
        Arrows->ArrowsQuantity += 1;

        GraphicBypass(node->Left, Arrows, dumppicture);
    }
    if(node->Right)
    {
        Arrows->ArrowArray[Arrows->ArrowsQuantity].ParentName = node;
        Arrows->ArrowArray[Arrows->ArrowsQuantity].ChildName = node->Right;
        Arrows->ArrowArray[Arrows->ArrowsQuantity].Direction = 0;

        Arrows->ArrowsQuantity += 1;

        GraphicBypass(node->Right, Arrows, dumppicture);
    }

    system("dot -Tpng dumppicture.gv -o irpenis.png");

    return 0;
}