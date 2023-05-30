#ifndef CURSOR
#define CURSOR

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct sCursor;


void initCursor(SDL_Renderer * r);
void destroyCursor();

int moveCursor(int x, int y);
void drawCursor(SDL_Renderer * r);

#endif