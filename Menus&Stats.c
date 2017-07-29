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
