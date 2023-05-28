#include <stdlib.h>
#include <stdio.h>

#include "../include/buffer.h"

#define BLOCKSIZE 0x04

static struct sTextBuffer
{
    char * buffer;
    unsigned int size;
    unsigned int cPos;
};

static struct sTextBuffer textBuffer = {NULL, 0, 0};


void initBuffer()
{
    textBuffer.buffer = (char*)malloc(sizeof(*textBuffer.buffer)*BLOCKSIZE);
    textBuffer.size = BLOCKSIZE;
}

int readFileToBuffer(FILE * f)
{
    if(f == NULL) return -1;


}

int writeToBuffer(char ch)
{
    // if true we need to allocate more space
    if(textBuffer.cPos == textBuffer.size)
    {
        textBuffer.buffer = realloc(textBuffer.buffer, sizeof(*textBuffer.buffer)*(textBuffer.size + BLOCKSIZE));
        textBuffer.buffer[textBuffer.cPos] = ch;
        textBuffer.cPos++;
        return 1;
    }
    textBuffer.buffer[textBuffer.cPos] = ch;
    textBuffer.cPos++;
    return 0;
}

void destroyBuffer()
{
    free(textBuffer.buffer);
}

void display()
{
    for(int i = 0; i < textBuffer.cPos; i++)
    {
        putchar(textBuffer.buffer[i]);
    }
}