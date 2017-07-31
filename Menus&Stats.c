#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Menus&Stats.h"


/* Function that allows the user to select a different menu in the bottom of the window
    param: the event of the mouse left button press
    param: variable indicating the current menu
    param; the name of the player
    param: auxiliar size of the board
*/
void BottomSelect(SDL_Event event, int *gamestate, char *playername, int *auxsize)
{
    if(event.button.y > 700)
    {
        if(event.button.x > XHOME  &&  event.button.x < (XHOME + XHOMESIZE))
        {
            *gamestate = 0;
        }
        else if(event.button.x > XNEWGAME  &&  event.button.x < (XNEWGAME + XNGAMESIZE))
        {
            *auxsize = 0;
            *gamestate = 2;
        }
        else if(event.button.x > XSTATISTICS  &&  event.button.x < (XSTATISTICS + XSTATISIZE))
        {
            *gamestate = 3;
        }
    }
}


/* Function that allows the user to select an option in the home menu
    param: the event of the mouse left button press
    param: variable indicating the current menu
    param: size of the board
    param: name of the player
    param: variable indicating how many plays have already been made
    param; the generated combination of colors for the current game
    param: auxiliar size of the board
*/
void HomeSelect(SDL_Event event, int *gamestate, int boardsize, char *playername, int nplays, int *combination, int *auxsize)
{
    if(event.button.x > XTEXTBOX  &&  event.button.x < XTEXTBOX + BOXWIDTH  &&
        event.button.y > YTEXTBOX  &&  event.button.y < YTEXTBOX + 3*BOXHEIGHT)
    {
        if(event.button.y > YTEXTBOX  &&  event.button.y < (YTEXTBOX + BOXHEIGHT) &&
            boardsize >= MINLEVEL  &&  boardsize  <= MAXBOARD  &&  playername[0] != 0)
        {
            *gamestate = 1;
        }
        else if(event.button.y > (YTEXTBOX + BOXHEIGHT)  &&  event.button.y < (YTEXTBOX + 2*BOXHEIGHT))
        {
            *auxsize = 0;
            *gamestate = 2;
        }
        else if(event.button.y > (YTEXTBOX + 2*BOXHEIGHT)  &&  event.button.y < (YTEXTBOX + 3*BOXHEIGHT))
        {
            *gamestate = 3;
        }
    }
}


/* Function to select the size of the board
    param: the event of the mouse left button press
    param: size of the board
*/
void SizeSelect(SDL_Event event, int *boardsize)
{
    if(event.button.x > XNUMEROS  &&  event.button.x < XNUMEROS + NUMBERWIDTH &&
        event.button.y > YNUMEROS  &&  event.button.y < YNUMEROS + MAX_LEVELS*NUMBERSIZE)
    {
        if(event.button.y > YNUMEROS  &&  event.button.y < (YNUMEROS + NUMBERSIZE))
        {
            *boardsize = 4;
        }
        else if(event.button.y > (YNUMEROS + NUMBERSIZE)  &&  event.button.y < (YNUMEROS + 2*NUMBERSIZE))
        {
            *boardsize = 5;
        }
        else if(event.button.y > (YNUMEROS + 2*NUMBERSIZE)  &&  event.button.y < (YNUMEROS + 3*NUMBERSIZE))
        {
            *boardsize = 6;
        }
        else if(event.button.y > (YNUMEROS + 3*NUMBERSIZE)  &&  event.button.y < (YNUMEROS + 4*NUMBERSIZE))
        {
            *boardsize = 7;
        }
        else if(event.button.y > (YNUMEROS + 4*NUMBERSIZE)  &&  event.button.y < (YNUMEROS + MAX_LEVELS*NUMBERSIZE))
        {
            *boardsize = 8;
        }
    }
}


/* Function that makes the reading of the player name
    param: the event of the keyboard press
    param: the name of the player
    param: the position of the next letter
*/
void NameReading(SDL_Event event, char *playername, int *namepos)
{
    int a=0;
    a=*namepos;
    if(event.key.keysym.sym >= SDLK_a  &&  event.key.keysym.sym <= SDLK_z)
    {
        playername[*namepos] = event.key.keysym.sym - SDLK_a + 'a';
        *namepos = *namepos + 1;
    }
    else if(event.key.keysym.sym >= SDLK_0  &&  event.key.keysym.sym <= SDLK_9)
    {
        playername[*namepos] = event.key.keysym.sym - SDLK_0 + '0';
        *namepos = *namepos + 1;
    }
    switch(event.key.keysym.mod)
    {
    case KMOD_CAPS:
        if(playername[a] >= 'a' && playername[a] <= 'z')
        {
            playername[a] = playername[a] - 32;
        }
        break;
    case KMOD_LSHIFT:
        if(playername[a] >= 'a' && playername[a] <= 'z')
        {
            playername[a] = playername[a] - 32;
        }
        break;
    case KMOD_RSHIFT:
        if(playername[a] >= 'a' && playername[a] <= 'z')
        {
            playername[a] = playername[a] - 32;
        }
        break;
    default:
        break;
    }
}


/* Function that allos the user to erase a letter
    param: the event of the keyboard press
    param: the name of the player
    param: the position of the next letter
*/
void LetterErase(SDL_Event event, char *playername, int *namepos)
{
    if(event.key.keysym.sym == SDLK_BACKSPACE)
    {
        *namepos = *namepos - 1;
        playername[*namepos] = 0;
    }
}


/* Function that erases all the user name
    param: the name of the player
*/
void NameCleanse(char *playername)
{
    int i=0;
    for(i=0; i < MAXNAME; i++)
    {
        playername[i] = 0;
    }
}


/* Function that allows the user to change the naem
    param: the event of the keuboardpress
    param: the name of the player
    param: the variable indicating if the reading of the player name is on
    param: position of the next letter in the player name
    param: variable indicating the state of the game
*/
void NameInsert(SDL_Event event, char *playername, int nameread, int *namepos, int gamestate)
{
    if(gamestate == 2  &&  nameread == 1  &&  *namepos < MAXNAME)
    {
        NameReading(event, playername, namepos);
        LetterErase(event, playername, namepos);
    }
}


/* Function that allows the user to select the box for writing the name
    param: the event of the mouse left button press
    param: variable indicating if the reading of the player name is on
*/
void NameSelect(SDL_Event event, int *nameread)
{
    if(event.button.x > XNAMEBOX  &&  event.button.x < XNAMEBOX + NBOXWIDTH  &&
        event.button.y > YNAMEBOX  &&  event.button.y < YNAMEBOX + NBOXHEIGHT)
    {
        *nameread = 1;
    }
    else
    {
        *nameread = 0;
    }
}


/* Function to start the game after pressing "OK"
    param: the event of the mouse left button press
    param: variable indicating the state of the game
    param: name of the player
    param: size of the board
    param: the generated combination for the current game
    param: variable indicating if the name read is on
    param: Matrix with the selected pieces by the user for the current game
    param: Array with the number of correct pieces in the right places per play
    param: Array with the number of correct pieces in the wrong places per play
    param: variable indicating how many plays have already been made
    param: auxilar name that will be copied to the player name
    param: position of the next letter in the player name
    param: auxilar size of the board
    param: initial time of the game
    param: saved time of the game
    param: actual time of the game
    param: name of the player of the game with best number of plays
    param: number of plays for the game with best number of plays
    param: time for the game with best number of plays
    param: size of the board for the game with best number of plays
    param: name of the player of the game with best time
    param: number of plays for the game with best time
    param: time for the game with best time
    param: size of the board for the game with best time
    param: total number of games
    param: total of the time of all games
    param: total of plays for all games
    param: total of the sum of the boardsize of all games
*/
void OKPress(SDL_Event event, int *gamestate, char *playername, int *boardsize, int **combination,
            int *nameread, int game [][MAXBOARD], int blacks[], int whites[], int *nplays,
            char *auxname, int namepos, int auxsize, time_t *initialtime, time_t *savedtime,
            time_t actualtime, char *bpplayername, int *bpplays, int *bptime, int *bpsize,
            char *btplayername, int *btplays, int *bttime, int *btsize, int *ngames, int *totaltime,
            int *totalplays, int *totalboard)
{
    int i = 0;
    int j = 0;

    if(event.button.x > OKX  &&  event.button.x < OKX + OKWIDTH  && event.button.y > OKY  &&
        event.button.y < OKY + OKHEIGHT  &&  auxsize >= MINLEVEL  &&  auxsize <= MAXBOARD
        &&  auxname[0] != 0)
    {
        StatsUpdate(playername, *nplays, actualtime, *boardsize, blacks, bpplayername, bpplays, bptime, bpsize,
                    btplayername, btplays, bttime, btsize, ngames, totaltime, totalplays, totalboard);
        for(i=0; i < MAXPLAYS; i++)
        {
            for(j=0; j < MAXBOARD; j++)
            {
                game[i][j] = 0;
            }
        }
        for(i=0; i < MAXAVALARRS; i++)
        {
            blacks[i] = 0;
            whites[i] = 0;
        }
        for(i=0; i < namepos; i++)
        {
            playername[i] = auxname[i];
        }
        *nplays = 0;
        *nameread = 0;
        *boardsize = auxsize;
        *combination = Generate(*boardsize);
        *gamestate = 1;
        *initialtime = time(NULL);
        *savedtime = 0;
    }
}

/* Function that applys the game Timer
    param: actual time
    param: initial time
    param; saved time
    param: the renderer to handle all the rendering in the window
    param: the number of plays of the current game
    param: Array with the number of correct pieces in the right places per play
    param: size of the board
    param: state of the program (1 = current game)
*/
void Timer(time_t *actualtime, time_t initialtime, time_t savedtime, SDL_Renderer * renderer,
            int nplays, int blacks[], int boardsize, int gamestate)
{
    if(gamestate == 1 && Loss(renderer, nplays) != 1 && Win(renderer, nplays, blacks, boardsize) != 1)
    {
        *actualtime = time(NULL) - initialtime + savedtime;
    }
}


/* Function that allocates memory for the player names
    param: the name of the player
    param: auxiliar name
    param: name of the player with the best number of plays
    param: name of the player with the best time
*/
void Memnames(char **playername, char **auxname, char **bpplayername, char **btplayername)
{
    *playername = (char*)malloc(MAXNAME * sizeof(char));
    if(*playername == NULL)
    {
        printf("ERROR! Failed to allocate memory for the name of the player");
    }
    *auxname = (char*)malloc(MAXNAME * sizeof(char));
    if(*auxname == NULL)
    {
        printf("ERROR! Failed to allocate memory for the name of the player");
    }
    *bpplayername = (char*)malloc(MAXNAME * sizeof(char));
    if(*bpplayername == NULL)
    {
        printf("ERROR! Failed to allocate memory for the name of the player");
    }
    *btplayername = (char*)malloc(MAXNAME * sizeof(char));
    if(*btplayername == NULL)
    {
        printf("ERROR! Failed to allocate memory for the name of the player");
    }
    NameCleanse(*playername);
    NameCleanse(*auxname);
    NameCleanse(*bpplayername);
    NameCleanse(*btplayername);
}


/* Function that updates the stats
    param: the name of the player for the current game
    param: number of plays for the current game
    param: time for the current game
    param: size of the board for the current game
    param: Array with the number of correct pieces in the right places per play
    param: name fo the player for the game with less plays
    param: number of plays for the game with less plays
    param: time for the game with less plays
    param: size of the board for the game with less plays
    param: name of the player for the game with best time
    param: number of plays for the game with best time
    param: time of the game with best time
    param: size of the board for the game with best time
    param: total number of games
    param: total of the time of all games
    param: total of plays for all games
    param: total of the sum of the boardsize of all games
*/
void StatsUpdate(char *playername, int nplays, time_t actualtime, int boardsize, int blacks[], char *bpplayername,
                int *bpplays, int *bptime, int *bpsize, char *btplayername, int *btplays, int *bttime, int *btsize,
                int *ngames, int *totaltime, int *totalplays, int *totalboard)
{
    int i = 0;

    if(*bpplays > nplays  &&  blacks[nplays-1] == boardsize)
    {
        for(i=0; i < MAXNAME; i++)
        {
            bpplayername[i] = playername[i];
        }
        *bpplays = nplays;
        *bptime = actualtime;
        *bpsize = boardsize;
    }
    if(*bttime > actualtime  &&  blacks[nplays-1] == boardsize)
    {
        for(i=0; i < MAXNAME; i++)
        {
            btplayername[i] = playername[i];
        }
        *btplays = nplays;
        *bttime = actualtime;
        *btsize = boardsize;
    }
    *ngames = *ngames + 1;
    *totaltime = *totaltime + actualtime;
    *totalplays = *totalplays + nplays;
    *totalboard = *totalboard + boardsize;
}
