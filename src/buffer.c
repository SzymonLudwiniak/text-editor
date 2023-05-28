#include <stdlib.h>
#include <stdio.h>

#include "../include/buffer.h"

#define BLOCKSIZE 0x04


struct sTextBuffer
{
    char * buffer;
    unsigned int size;
    unsigned int cPos;
};


static struct sTextBuffer textBuffer = {NULL, 0, 0};


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

void display()
{
    for(unsigned int i = 0; i < textBuffer.cPos; i++)
    {
        putchar(textBuffer.buffer[i]);
    }
}