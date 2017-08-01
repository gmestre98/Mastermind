#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"
#include "Play.h"

void BottomSelect(SDL_Event, int *, char *, int *);
void HomeSelect(SDL_Event, int *, int, char *, int, int *, int *);
void SizeSelect(SDL_Event, int *);
void NameReading(SDL_Event, char *, int *);
void LetterErase(SDL_Event, char *, int *);
void NameCleanse(char *);
void NameInsert(SDL_Event, char *, int, int *, int);
void NameSelect(SDL_Event, int *);
void OKPress(SDL_Event, int *, char *, int*, int **, int *, int [][MAXBOARD],
            int [], int[], int *, char*, int *, int, time_t *, time_t *, time_t,
            char *, int *, int *, int *, char *, int *, int *, int *, int *,
            int *, int *, int *);
void Timer(time_t *, time_t, time_t, SDL_Renderer *, int, int [], int, int,
            int *, SDL_Surface **, TTF_Font *);
void Memnames(char **, char **, char **, char **);
void StatsUpdate(char *, int, time_t, int, int [], char *, int *, int *, int *,
                char *, int *, int *, int *, int *, int *, int *, int *);
void SaveStats(char *, int, int, int, char *, int, int, int, int, int, int, int);
void ReadStats(char *, int *, int *, int *, char *, int *, int *, int *, int *,
                int *, int *, int *);
void SaveGame(int *, int[][MAXBOARD], int, int, int [], int [], char *, time_t);
void OpenGame(int *, int[][MAXBOARD], int *, int *, int [], int [], char *, time_t *);
