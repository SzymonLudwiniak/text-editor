#include "../include/cursor.h"


struct sCursor
{
    unsigned int posX;
    unsigned int posY;

    // both should be calculated using font size (will do later)
    unsigned int w;
    unsigned int h;

    unsigned int blinkTime;

    SDL_Texture * texture;

};

static struct sCursor cursor;

#define RMASK 0x00
#define GMASK 0x00
#define BMASK 0x00
#define AMASK 0xFF

void initCursor(SDL_Renderer * r)
{
    cursor.posX = 0;
    cursor.posY = 0;
    cursor.w = 20;
    cursor.h = 20;
    cursor.blinkTime = 0;
    cursor.texture = NULL;

    SDL_Surface * s = SDL_CreateRGBSurface(0, cursor.w, cursor.h, 8, RMASK, GMASK, BMASK, AMASK);
    SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 255, 255, 255, 255));
    cursor.texture = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);
}

#undef RMASK
#undef GMASK
#undef BMASK
#undef AMASK


void destroyCursor()
{
    SDL_DestroyTexture(cursor.texture);
}

// can be underflowed easily now
int moveCursor(int x, int y)
{
    cursor.posX += x;
    cursor.posY += y;
}

void drawCursor(SDL_Renderer * r)
{
    SDL_Rect srcDim = {0, 0, cursor.w, cursor.h};
    SDL_Rect destDim = {cursor.posX * cursor.w, cursor.posY * cursor.h, cursor.w, cursor.h};
    SDL_RenderCopy(r, cursor.texture, &srcDim, &destDim);
}