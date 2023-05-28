#include "../include/buffer.h"



int main(int argc, char* argv[]) 
{
    FILE * file = fopen(argv[argc-1], "rw");    
    initBuffer();

    readFileToBuffer(file);

    display();
    destroyBuffer();
    return 0;
}
