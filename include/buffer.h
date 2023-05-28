#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void initBuffer();
int readFileToBuffer(FILE * f);
int writeToBuffer(char ch);
void destroyBuffer();


void display();