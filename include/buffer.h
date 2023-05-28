#ifndef BUFFER
#define BUFFER

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct sTextBuffer;

void initBuffer();
int readFileToBuffer(FILE * f);
int writeToBuffer(char ch);
void destroyBuffer();


void display();

#endif