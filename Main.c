#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"
#include "Grafica.h"

int main(void)
{
    SDL_Window *window = NULL;                                          // Window
    SDL_Renderer *renderer = NULL;                                      // Renderer
    SDL_Event event;                                                    // Event
    SDL_Surface *Avaluations[MAX_LEVELS];                               // Array of the valuation images
    TTF_Font *serif = NULL;                                             // Font serif
    TTF_Font *Demonized = NULL;                                         // Font Demonized
    TTF_Font *Queen = NULL;                                             // Font Queen
    int delay = 100;                                                    // Delay for the renderer
    int quit = 0;                                                       // Quit Flag
    int boardsize = 0;                                                  // Number of colors per play



    printf("Introduza o tamanho do tabuleiro!\n");
    scanf("%d", &boardsize);

    InitEverything(WIDTH, HEIGHT,&serif, &Demonized, &Queen, &window, &renderer);
    LoadAvaluations(Avaluations);
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

                        break;
                    default:
                        break;
                }
            }
        }
        RenderBoard(renderer, boardsize, Avaluations);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }
    TTF_CloseFont(serif);
    TTF_CloseFont(Demonized);
    TTF_CloseFont(Queen);
    UnloadAvaluations(Avaluations);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
