#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Play.h"

void ChooseColor(SDL_Event event, SDL_Surface **Avaluations, int *selecolor, int boardsize)
{
    int NumbersX = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX +
                    boardsize*PIECESIZE + EXTRAPOS*(11/2) + (Avaluations[boardsize-MINLEVEL])->w;
    int color = 0;

    if(event.button.x > NumbersX && event.button.x < NumbersX + COLORSXSIZE && event.button.y > COLORSY - EXTRAPOS
        &&  event.button.y < COLORSY+COLORSYSIZE)
    {
        color = event.button.y - COLORSY + COLORSYCORR;
        color = color*NCOLORS/COLORSYSIZE;
        switch (color)
        {
            case 1:
                *selecolor = 1;
                break;
            case 3:
                *selecolor = 2;
                break;
            case 5:
                *selecolor = 3;
                break;
            case 7:
                *selecolor = 4;
                break;
            case 9:
                *selecolor = 5;
                break;
            case 11:
                *selecolor = 6;
                break;
            case 13:
                *selecolor = 7;
                break;
            case 15:
                *selecolor = 8;
                break;
            default:
                break;
        }
    }
}

void PutPiece(SDL_Event event, int nplays, int boardsize)
{
    int startx = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX;
    int endx = startx + boardsize*PIECESIZE;
    int starty = FIRSTPIECEY + (MAXNPLAYS - nplays)*YPERPLAY;
    int endy = starty + YPERPLAY;
    int linepos = 0;

    if(event.button.x > startx && event.button.x < endx && event.button.y > starty
       && event.button.y < endy)
    {
        linepos = event.button.x - startx;
        linepos = linepos*2*boardsize/(endx-startx);
        switch (linepos) {
            case 0:
                printf("Pos1\n");
                break;
            case 2:
                printf("Pos2\n");
                break;
            case 4:
                printf("Pos3\n");
                break;
            case 6:
                printf("Pos4\n");
                break;
            case 8:
                printf("Pos5\n");
                break;
            case 10:
                printf("Pos6\n");
                break;
            case 12:
                printf("Pos7\n");
                break;
            case 14:
                printf("Pos8\n");
                break;
            default:
                break;
        }
    }
}
