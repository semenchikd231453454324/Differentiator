#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "read.h"
#include "nodegets.h"

#define FILENAMESIZE 25

//static int ReadBypass(NodeStruct* node, char* Text, size_t* CurrentNum, bool* IsLeft);
//static NodeStruct* ReadBypass(NodeStruct* node, char* Text, size_t* CurrentNum);

NodeStruct* Read()
{
    char FileName[FILENAMESIZE] = {};

    printf("Enter the name of file to load equation\n");
    scanf("%s", FileName);

    FILE* InputText = fopen(FileName, "r");
    if(!InputText)
    {
        printf("Pizdec with InputText Pointer\n");
        return nullptr;
    }

    struct stat FileInf = {};
    stat(FileName, &FileInf);

    size_t BufferSize = FileInf.st_size;

    char* Buffer = (char*) calloc(BufferSize, sizeof(char));
    if(!Buffer)
    {
        printf("Pizdec with pointer in calloc buffer\n");
        return nullptr;
    }
    char* Text = (char*) calloc(BufferSize, sizeof(char));
    if(!Text)
    {
        printf("Pizdec with pointer in calloc buffer\n");
        return nullptr;
    }

    fread(Buffer, sizeof(char), BufferSize, InputText);

    size_t CurrentTextElem = 0;
    for(size_t CurrentElem = 0; CurrentElem < BufferSize; CurrentElem++)
    {
        if(Buffer[CurrentElem] == '\n' || Buffer[CurrentElem] == ' ')
        {}
        else
        {
            Text[CurrentTextElem] = Buffer[CurrentElem];
            CurrentTextElem++;
        }
    }

    for(size_t i = 0; i < CurrentTextElem; i++)
    {
        printf("%c", Text[i]);
    }

    printf("\n");


    return Get(Text);


    return 0;
}

