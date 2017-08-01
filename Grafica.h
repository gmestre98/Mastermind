#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
void InitEverything(int, int, TTF_Font **, TTF_Font **, TTF_Font **, TTF_Font **, TTF_Font **, SDL_Window **, SDL_Renderer **);
void RenderBoard(SDL_Renderer *, int, SDL_Surface **);
void LoadAvaluations(SDL_Surface **);
void UnloadAvaluations(SDL_Surface **);
void LoadColors(SDL_Surface **);
void UnloadColors(SDL_Surface **);
void RenderFromArray(SDL_Renderer *, SDL_Surface **, int, int, int);
void RenderPlay(SDL_Renderer *, int, int);
void RenderPieces(SDL_Renderer *, SDL_Surface **, int [][MAXBOARD], int);
void RenderAvalPair(SDL_Renderer *, int, int [], int [], int);
void RenderAvalFive(SDL_Renderer *, int, int [], int [], int);
void RenderAvalSeven(SDL_Renderer *, int, int [], int [], int);
void RenderAval(SDL_Renderer *, int, int [], int [], int);
void RenderMenu(SDL_Renderer *, TTF_Font *);
void RenderHome(SDL_Renderer *, TTF_Font *, TTF_Font *);
void RenderNewGame(SDL_Renderer *renderer, TTF_Font *, TTF_Font *, char *, int, int);
void RenderTime(time_t, SDL_Renderer *, TTF_Font *);
void RenderStats(SDL_Renderer *, TTF_Font *, TTF_Font *, TTF_Font *, char *, int, int,
                int, char *, int, int, int, int, int, int, int);
