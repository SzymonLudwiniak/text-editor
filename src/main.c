#include "../include/buffer.h"



int main(/*int argc, char* argv[]*/) {
    
    initBuffer();
    for(int i = 0; i < 20; i++)
    {
        writeToBuffer(getchar());
    }
    display();
    destroyBuffer();
    return 0;
}
