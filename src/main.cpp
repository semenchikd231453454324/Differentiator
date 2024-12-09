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
#include "optimization.h"
#include "print.h"

int main()
{
     NodeStruct* Root = nullptr;

     //Root.type = Operation;
     //Root.value = Add;

     //Root.Left = CreateNum(3);
     //Root.Right = CreateNum(7);

     Root = Read();

     GraphicDump(Root);

     // Optimizations(Root);

     // GraphicDump(Root);

     printf("Your equation was read\nYou want to take the derevativ[y/n]?\n");

     char Answer[1] = {};

     scanf("%s", Answer);

     if(Answer[0] == 'y')
     {
          Root = Differentiator(Root);

          GraphicDump(Root);
     }

     char Answer2 [1] = {};

     printf("Do you like what you see[y/n]?\n");

     scanf("%s", Answer2);

     if(Answer2[0] == 'n')
     {
          Optimizations(Root);
     }

     print(Root);

     return 0;
}