#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/buffer.h"

#define BLOCKSIZE 0x04
#define VISIBLEBLOCKWIDTH 0xFF


struct sTextBuffer
{
    char * buffer;
    unsigned int size;
    unsigned int cPos;

    unsigned int visIndexStart;
    unsigned int visIndexEnd;
};


static struct sTextBuffer textBuffer = {NULL, 0, 0, 0, 0};


void initBuffer()
{
    textBuffer.buffer = (char*)malloc(sizeof(char)*BLOCKSIZE);
    textBuffer.size = BLOCKSIZE;
}

int readFileToBuffer(FILE * f)
{
    if(f == NULL) return 11;

    char c;
    while((c = fgetc(f)) != EOF)
    {
        writeToBuffer(c);
    }
    return 0;
}

int writeToBuffer(char ch)
{
    int retVal = 0;
    // if true we need to allocate more space
    if(textBuffer.cPos == textBuffer.size)
    {
        char * temp_p = realloc(textBuffer.buffer, sizeof(char)*(textBuffer.size + BLOCKSIZE));
        textBuffer.size += BLOCKSIZE;
        if(temp_p == NULL)
            return -1;

        textBuffer.buffer = temp_p;
        retVal = 1;
    }
    textBuffer.buffer[textBuffer.cPos++] = ch;
    return retVal;
}

void destroyBuffer()
{
    free(textBuffer.buffer);
}

char* getVisibleText(char **ptr)
{
    char * temp = strncpy(*ptr, (textBuffer.buffer + textBuffer.visIndexStart), textBuffer.visIndexEnd-textBuffer.visIndexStart);
    temp[textBuffer.visIndexEnd-textBuffer.visIndexStart] = '\0';

    return 0;
}

int setFirstVisibleLine(unsigned int num)
{
    unsigned int line = 0;
    unsigned int i;
    for(i = 0; i < textBuffer.size; i++)
    {
        if(textBuffer.buffer[i] == '\n')
            line++;
        if(line == num)
            break;
    }
    if(line != 0) 
        i++;
    textBuffer.visIndexStart = i;
    printf("first %d\n", i);
    return i;
}

int setLastVisibleLine(unsigned int num)
{
    unsigned int line = 0;
    unsigned int i;
    for(i = 0; i < textBuffer.size; i++)
    {
        if(textBuffer.buffer[i] == '\n')
            line++;
        if(line == num+1)
            break;
    }
    textBuffer.visIndexEnd = i;
    printf("last %d\n", i);
    return i;
}

void display()
{
    for(unsigned int i = 0; i < textBuffer.cPos; i++)
    {
        putchar(textBuffer.buffer[i]);
    }
}