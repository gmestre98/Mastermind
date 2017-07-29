#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"
#include "Play.h"
#include "Menus&Stats.h"

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
    TTF_Font *QueenBig = NULL;                                          // Font Queen in a bigger size
    TTF_Font *Targa = NULL;                                             // Font Targa
    int delay = 100;                                                    // Delay for the renderer
    int quit = 0;                                                       // Quit Flag
    int boardsize = 0;                                                  // Number of colors per play
    int selecolor = 0;                                                  // Integer for the selected color
    int xmouse = 0;                                                     // X Coordinate of the mouse
    int ymouse = 0;                                                     // Y Coordinate of the mouse
    int nplays = 0;                                                     // Number of plays already made
    int game [MAXPLAYS][MAXBOARD] = {{0}};                              // Matrix with the plays for the current game
    int *combination = NULL;                                            // Random Generated combination
    int blacks[MAXAVALARRS] = {0};                                      // Array with the number of correct pieces in the right places per play
    int whites[MAXAVALARRS] = {0};                                      // Array with the number of correct pieces in the wrong places per play
    int gamestate = 0;                                                  // Current menu (0-Home, 1 - Current Game, 2 New Game, 3 Statistics)


    printf("Introduza o tamanho do tabuleiro!\n");
    scanf("%d", &boardsize);

    combination = Generate(boardsize);
    InitEverything(WIDTH, HEIGHT,&serif, &Demonized, &Queen, &QueenBig, &Targa, &window, &renderer);
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
                        BottomSelect(event, &gamestate);
                        switch(gamestate)
                        {
                            case 0:
                                HomeSelect(event, &gamestate);
                                break;
                            case 1:
                                if(Loss(renderer, nplays) != 1 && Win(renderer, nplays, blacks, boardsize) != 1)
                                {
                                    ChooseColor(event, Avaluations, &selecolor, boardsize);
                                    PutPiece(event, nplays, boardsize, selecolor, game);
                                    if(CompleteLine(nplays, boardsize, game) == 1)
                                    {
                                        Avaluate(combination, game, nplays, boardsize, whites, blacks);
                                        nplays ++;
                                    }
                                }
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        switch(gamestate)
        {
            case 0:
                RenderHome(renderer, Queen, QueenBig);
                break;
            case 1:
                RenderBoard(renderer, boardsize, Avaluations);
                SDL_GetMouseState(&xmouse, &ymouse);
                if(selecolor != 0)
                {
                    RenderFromArray(renderer, Colors, selecolor - 1, xmouse - COLORCORR, ymouse - COLORCORR);
                }
                RenderPlay(renderer, nplays, boardsize);
                RenderPieces(renderer, Colors, game, boardsize);
                RenderAval(renderer, boardsize, blacks, whites, nplays);
                Loss(renderer, nplays);
                Win(renderer, nplays, blacks, boardsize);
                break;
            case 2:
                RenderNewGame(renderer, Queen, QueenBig);
                break;
            case 3:
                break;
            default:
                break;
        }
        RenderImage(renderer, "Preto.bmp", XMENU, YMENU);
        RenderMenu(renderer, Queen);
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
