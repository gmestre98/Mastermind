#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Play.h"


/* Function that allows the player to choose the color of the next piece to places
    param: the event that happened, being in this case a mouse event
    param: Array of the avaluation images
    param: Number corresponding to the selected color
    param: size of the board, number of pieces per play
*/
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


/* Function that allows the user to place a piece in the board
    param: the event that happened, being in this case a mouse event
    param: variable indicating how many plays have already been made
    param: size of the board, number of pieces per play
    param: Number corresponding to the selected color
    param: Matrix with the selected pieces by the user for the current game
*/
void PutPiece(SDL_Event event, int nplays, int boardsize, int selecolor, int game [][MAXBOARD])
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
        linepos = linepos/2;
        game[nplays][linepos] = selecolor;
    }
}


/* Function that verifies if the current line is already complete
    param: variable indicating how many plays have already been made
    param: size of the board, number of pieces per play
    param: Matrix with the selected pieces by the user for the current game
    return: return 1 if the line is complete, else returns 0
*/
int CompleteLine(int nplays, int boardsize, int game [][MAXBOARD])
{
    int i = 0;
    int a = 1;
    for(i=0; i < boardsize; i++)
    {
        if(game[nplays][i] == 0)
        {
            a = 0;
        }
    }
    return a;
}


/* Function that generates a random combination of colors
    param: size of the board, number of pieces per play
    return: the array with the generated combination
*/
int* Generate(int boardsize)
{
    int *combination = NULL;
    int i = 0;
    srand(time(NULL));
    combination = (int*)calloc(boardsize, sizeof(int));
    if(combination == NULL)
    {
        printf("ERROR! It was not possible to allocate memory for the combination\n");
        exit(EXIT_FAILURE);
    }
    for(i=0; i < boardsize; i++)
    {
        combination[i] = (rand() %NMBRCOLORS + 1);
    }
    return combination;
}


/* Function that avaluates the play upon completion of the line
    param: array with the generated combination
    param: Matrix with the selected pieces by the user for the current game
    param: variable indicating how many plays have already been made
    param: size of the board, number of pieces per play
    param: pointer to the number of correct but misplaced pieces in the last play
    param: pointer to the number of correct placed pieces in the last play
*/
void Avaluate(int *combination, int game[][MAXBOARD], int nplays, int boardsize, int whites [], int blacks[])
{
    int i = 0;
    int j = 0;
    int aux[MAXBOARD] = {0};
    int auxgame[MAXBOARD] = {0};

    for(i=0; i < boardsize; i++)
    {
        aux[i] = combination[i];
        auxgame[i] = game[nplays][i];
    }
    for(i=0; i < boardsize; i++)
    {
        if(auxgame[i] == aux[i])
        {
            aux[i] = 0;
            auxgame[i] = 0;
            blacks[nplays] = blacks[nplays] + 1;
        }
    }
    for(i=0; i < boardsize; i++)
    {
        j = 0;
        while(j < boardsize  &&  game[nplays][i] != aux[j])
        {
            j++;
        }
        if(j < boardsize)
        {
            aux[j] = 0;
            whites[nplays] = whites[nplays] + 1;
        }
    }
}


/* Function to check if the player has lost and to render the correct image
    param: the renderer to handle all the rendering in the window
    param: variable indicating how many plays have already been made
    param: Array with the number of correct pieces in the right places per play
    param: size of the board, number of pieces per play
    param: the correct combination generated
    param: Array of the color images
    param: A font for some text
*/
int Loss(SDL_Renderer *renderer, int nplays, int blacks[], int boardsize, int *combination,
        SDL_Surface **Colors, TTF_Font *font)
{
    SDL_Color white = {255, 255, 255};
    int i = 0;
    int x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + EXTRAPOS;

    if(nplays == 10 && blacks[nplays-1] != boardsize)
    {
        RenderImage(renderer, "Win.bmp", XWIN, YWIN);
        RenderText(x - COMBTXTVAR, YCOMBTXT, "Key :", font, &white, renderer);
        for(i=0; i < boardsize; i++)
        {
            RenderFromArray(renderer, Colors, combination[i] - 1, x, YCOMB);
            x += PIECESIZE;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}


/* Function to check if the player won the game and to render the correct image
    param: the renderer to handle all the rendering in the window
    param: variable indicating how many plays have already been made
    param: Array with the number of correct pieces in the right places per play
    param: size of the board, number of pieces per play
    param: the correct combination generated
    param: Array of the color images
    param: A font for some text
*/
int Win(SDL_Renderer *renderer, int nplays, int blacks[], int boardsize, int * combination,
        SDL_Surface **Colors, TTF_Font *font )
{
    SDL_Color white = {255, 255, 255};
    int i = 0;
    int x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + EXTRAPOS;

    if(blacks[nplays-1] == boardsize)
    {
        RenderImage(renderer, "Win.bmp", XWIN, YWIN);
        RenderText(x - COMBTXTVAR, YCOMBTXT, "Key :", font, &white, renderer);
        for(i=0; i < boardsize; i++)
        {
            RenderFromArray(renderer, Colors, combination[i] - 1, x, YCOMB);
            x += PIECESIZE;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
