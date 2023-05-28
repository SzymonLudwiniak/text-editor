#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/buffer.h"


int main(int argc, char* argv[]) 
{

    initBuffer();
    FILE* f = fopen(argv[argc-1], "rw");
    readFileToBuffer(f);
    fclose(f);
    setFirstVisibleLine(1);
    setLastVisibleLine(2);
    char *ptr = (char*)malloc(sizeof(char)*256);
    getVisibleText(&ptr);

    printf("%s", ptr);

    free(ptr);

    destroyBuffer();
    return 0;
}
