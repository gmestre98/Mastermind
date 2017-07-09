#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"

void InitSDL();
void InitFont();
SDL_Window *CreateWindow(int , int);
SDL_Renderer *CreateRenderer(int, int, SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
void RenderImage(SDL_Renderer *, char [], int, int);
void InitEverything(int, int, TTF_Font **, TTF_Font **, TTF_Font **, SDL_Window **, SDL_Renderer **);
