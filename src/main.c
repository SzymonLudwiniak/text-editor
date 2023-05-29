#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/buffer.h"


int main(int argc, char* argv[]) 
{

    initBuffer();
    FILE* f = fopen(argv[argc-1], "rw");
    readFileToBuffer(f);
    fclose(f);

    //  SDL PART  //
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window * window = SDL_CreateWindow("text-editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Font * font = TTF_OpenFont("fonts/Roundman.ttf", 8);
    SDL_Color color = {255, 255, 255, 0};
    SDL_Surface * surface = TTF_RenderText_Blended(font, "TEXT text", color);
    SDL_BlitSurface(surface, NULL, SDL_GetWindowSurface(window), NULL);
    if(font == NULL)
    {
        printf("couldn't load font\n");
        exit(1);
    }

    int quit = 0;
    SDL_Event event;

    while(!quit)
    {
        // event handling
        while(SDL_PollEvent(&event) != 0)
        {
            if( event.type == SDL_QUIT)
                quit = 1;
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();
    ///////////////////////////////////////
    char *ptr = (char*)malloc(sizeof(char)*2048);
    getVisibleText(&ptr);

    printf("%s", ptr);

    free(ptr);

    destroyBuffer();
    return 0;
}
