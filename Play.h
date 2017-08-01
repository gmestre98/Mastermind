#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Grafica.h"


void ChooseColor(SDL_Event, SDL_Surface **, int *, int);
void PutPiece(SDL_Event, int, int, int, int [][MAXBOARD]);
int CompleteLine(int, int, int [][MAXBOARD]);
int *Generate(int);
void Avaluate(int *, int [][MAXBOARD], int, int, int [], int []);
int Loss(SDL_Renderer *, int, int [], int, int *, SDL_Surface **, TTF_Font *);
int Win(SDL_Renderer *, int, int [], int, int *, SDL_Surface **, TTF_Font *);
