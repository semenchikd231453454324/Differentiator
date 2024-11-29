#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "graphicdump.h"
#include "createnode.h"
#include "read.h"
#include "difer.h"

int main()
{
     NodeStruct* Root = nullptr;

     //Root.type = Operation;
     //Root.value = Add;

     //Root.Left = CreateNum(3);
     //Root.Right = CreateNum(7);

     Root = Read();

     GraphicDump(Root);

     printf("Your equation was read\nYou want to take the derevativ[y/n]?\n");

     char Answer [1] = {};

     scanf("%s", Answer);

     if(Answer[0] == 'y')
     {
          Root = Differentiator(Root);

          GraphicDump(Root);
     }

     return 0;
}