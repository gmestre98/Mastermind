#include <stdio.h>
#include <stdlib.h>

void InitSDL();
void InitFont();
SDL_Window *CreateWindow(int , int);
SDL_Renderer *CreateRenderer(int, int, SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
void RenderImage(SDL_Renderer *, char [], int, int);
