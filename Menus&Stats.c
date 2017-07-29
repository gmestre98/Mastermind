#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Menus&Stats.h"


/* Function that allows the user to select a different menu in the bottom of the window
    param: the event of the mouse left button press
    param: variable indicating the current menu
*/
void BottomSelect(SDL_Event event, int *gamestate)
{
    if(event.button.y > 700)
    {
        if(event.button.x > XHOME  &&  event.button.x < (XHOME + XHOMESIZE))
        {
            *gamestate = 0;
        }
        else if(event.button.x > XNEWGAME  &&  event.button.x < (XNEWGAME + XNGAMESIZE))
        {
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
*/
void HomeSelect(SDL_Event event, int *gamestate)
{
    if(event.button.x > XTEXTBOX  &&  event.button.x < XTEXTBOX + BOXWIDTH  &&
        event.button.y > YTEXTBOX  &&  event.button.y < YTEXTBOX + 3*BOXHEIGHT)
    {
        if(event.button.y > YTEXTBOX  &&  event.button.y < (YTEXTBOX + BOXHEIGHT))
        {
            *gamestate = 1;
        }
        else if(event.button.x > (YTEXTBOX + BOXHEIGHT)  &&  event.button.x < (YTEXTBOX + 2*BOXHEIGHT))
        {
            *gamestate = 2;
        }
        else if(event.button.x > (YTEXTBOX + 2*BOXHEIGHT)  &&  event.button.x < (YTEXTBOX + 3*BOXHEIGHT))
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
        else if(event.button.x > (YNUMEROS + NUMBERSIZE)  &&  event.button.x < (YNUMEROS + 2*NUMBERSIZE))
        {
            *boardsize = 5;
        }
        else if(event.button.x > (YNUMEROS + 2*NUMBERSIZE)  &&  event.button.x < (YNUMEROS + 3*NUMBERSIZE))
        {
            *boardsize = 6;
        }
        else if(event.button.x > (YNUMEROS + 3*NUMBERSIZE)  &&  event.button.x < (YNUMEROS + 4*NUMBERSIZE))
        {
            *boardsize = 7;
        }
        else if(event.button.x > (YNUMEROS + 4*NUMBERSIZE)  &&  event.button.x < (YNUMEROS + MAX_LEVELS*NUMBERSIZE))
        {
            *boardsize = 8;
        }
    }
}


// Função que faz a leitura do nome de jogador
void LeNome(SDL_Event event, char nome_jogador[MEDIUMSTR], int *posicaonome)
{
    int a=0;
    a=*posicaonome;
    if(event.key.keysym.sym >= SDLK_a  &&  event.key.keysym.sym <= SDLK_z)
    {
        nome_jogador[*posicaonome] = event.key.keysym.sym - SDLK_a + 'a';
        *posicaonome = *posicaonome + 1;
    }
    else if(event.key.keysym.sym >= SDLK_0  &&  event.key.keysym.sym <= SDLK_9)
    {
        nome_jogador[*posicaonome] = event.key.keysym.sym - SDLK_0 + '0';
        *posicaonome = *posicaonome + 1;
    }
    switch(event.key.keysym.mod)
    {
    case KMOD_CAPS:
        if(nome_jogador[a] >= 'a' && nome_jogador[a] <= 'z')
        {
            nome_jogador[a] = nome_jogador[a] - 32;
        }
        break;
    case KMOD_LSHIFT:
        if(nome_jogador[a] >= 'a' && nome_jogador[a] <= 'z')
        {
            nome_jogador[a] = nome_jogador[a] - 32;
        }
        break;
    case KMOD_RSHIFT:
        if(nome_jogador[a] >= 'a' && nome_jogador[a] <= 'z')
        {
            nome_jogador[a] = nome_jogador[a] - 32;
        }
        break;
    default:
        break;
    }
}



// Função que apaga uma letra do nome de jogador
void ApagaLetra(SDL_Event event, char nome_jogador[MEDIUMSTR], int *posicaonome)
{
    if(event.key.keysym.sym == SDLK_BACKSPACE)
    {
        *posicaonome = *posicaonome - 1;
        nome_jogador[*posicaonome] = 0;
    }
}


// Função que apaga o nome de jogador
void LimpaNome(char nome_jogador[MEDIUMSTR])
{
    int i=0;
    for(i=0; i < 8; i++)
    {
        nome_jogador[i] = 0;
    }
}
