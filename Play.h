#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"

typedef struct{
    int *colors;
}Play;

void ChooseColor(SDL_Event, SDL_Surface **, int *, int);
void PutPiece(SDL_Event, int, int);
