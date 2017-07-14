#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"
#include "Grafica.h"
#include "Play.h"

int main(void)
{
    SDL_Window *window = NULL;                                          // Window
    SDL_Renderer *renderer = NULL;                                      // Renderer
    SDL_Event event;                                                    // Event
    SDL_Surface *Avaluations[MAX_LEVELS];                               // Array of the avaluation images
    SDL_Surface *Colors[NMBRCOLORS];                                    // Array of the color images
    TTF_Font *serif = NULL;                                             // Font serif
    TTF_Font *Demonized = NULL;                                         // Font Demonized
    TTF_Font *Queen = NULL;                                             // Font Queen
    int delay = 100;                                                    // Delay for the renderer
    int quit = 0;                                                       // Quit Flag
    int boardsize = 0;                                                  // Number of colors per play
    int selecolor = 0;                                                  // Integer for the selected color
    int xmouse = 0;                                                     // X Coordinate of the mouse
    int ymouse = 0;                                                     // Y Coordinate of the mouse
    int nplays = 0;                                                     // Number of plays already made


    printf("Introduza o tamanho do tabuleiro!\n");
    scanf("%d", &boardsize);

    InitEverything(WIDTH, HEIGHT,&serif, &Demonized, &Queen, &window, &renderer);
    LoadAvaluations(Avaluations);
    LoadColors(Colors);
    while(quit == 0)
    {
        while(SDL_PollEvent (&event))
        {
            if( event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if( event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_q:
                        quit = 1;
                        break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        ChooseColor(event, Avaluations, &selecolor, boardsize);
                        PutPiece(event, nplays, boardsize);
                        break;
                    default:
                        break;
                }
            }
        }
        RenderBoard(renderer, boardsize, Avaluations);
        SDL_GetMouseState(&xmouse, &ymouse);
        if(selecolor != 0)
        {
            RenderFromArray(renderer, Colors, selecolor - 1, xmouse - COLORCORR, ymouse - COLORCORR);
        }
        RenderPlay(renderer, nplays, boardsize);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }
    TTF_CloseFont(serif);
    TTF_CloseFont(Demonized);
    TTF_CloseFont(Queen);
    UnloadColors(Colors);
    UnloadAvaluations(Avaluations);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
