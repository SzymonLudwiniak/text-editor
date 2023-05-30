#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/buffer.h"

#define SCREENWIDTH     800
#define SCREENHEIGHT    600


int main(int argc, char* argv[]) 
{

    initBuffer();
    FILE* f = fopen(argv[argc-1], "rw");
    readFileToBuffer(f);
    fclose(f);

    setFirstVisibleLine(0);
    setLastVisibleLine(64);

    //  SDL PART  //
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window * window = SDL_CreateWindow("text-editor", 1600, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font * font = TTF_OpenFont("fonts/Roundman.ttf", 16);
    SDL_Color color = {255, 255, 255, 0};

    SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(font, getVisibleBuffer(), color, SCREENWIDTH);
    SDL_Surface * colorSurface = SDL_CreateRGBSurfaceWithFormat(0, textSurface->w, textSurface->h, 32, textSurface->format->format);

    SDL_FillRect(colorSurface, NULL, SDL_MapRGBA(colorSurface->format, 127, 127, 127, 127));


    SDL_BlitSurface(textSurface, NULL, colorSurface, NULL);

    SDL_BlitSurface(colorSurface, NULL, SDL_GetWindowSurface(window), NULL);

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

    SDL_FreeSurface(colorSurface);
    SDL_FreeSurface(textSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();
    ///////////////////////////////////////

    destroyBuffer();
    return 0;
}
