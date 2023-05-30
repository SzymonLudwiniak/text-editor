#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/buffer.h"

#define SCREENWIDTH     800
#define SCREENHEIGHT    600

#define BGCOLOR_RGBA 7, 40, 69, 255


int main(int argc, char* argv[]) 
{

    initBuffer();
    FILE* f = fopen(argv[argc-1], "rw");
    readFileToBuffer(f);
    fclose(f);

    setFirstVisibleLine(0);
    setLastVisibleLine(32);

    //  SDL PART  //
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window * window = SDL_CreateWindow("text-editor", 1600, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, BGCOLOR_RGBA);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    TTF_Font * font = TTF_OpenFont("fonts/Roundman.ttf", 16);
    SDL_Color color = {248, 242, 73, 0};

    SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(font, getVisibleBuffer(), color, SCREENWIDTH);
    SDL_Surface * colorSurface = SDL_CreateRGBSurfaceWithFormat(0, textSurface->w, textSurface->h, 32, textSurface->format->format);

    SDL_FillRect(colorSurface, NULL, SDL_MapRGBA(colorSurface->format, BGCOLOR_RGBA));


    SDL_BlitSurface(textSurface, NULL, colorSurface, NULL);

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, colorSurface);
    SDL_Rect srcRect = {0, 0, colorSurface->w, colorSurface->h};
    SDL_Rect destRect = {10, 0, colorSurface->w, colorSurface->h};
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    SDL_RenderPresent(renderer);

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
