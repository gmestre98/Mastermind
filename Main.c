#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Defines.h"
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
    char *playername = NULL;                                            // Name of the player
    int nameread = 0;                                                   // Variable that indicates if the reading of the player name is on
    int namepos = 0;                                                    // Position of the next letter in the player name
    int auxsize = 0;                                                    // Auxiliar board size
    char *auxname = NULL;                                               // Auxiliar player name
    time_t actualtime = 0;                                              // Actual time of the game
    time_t initialtime = 0;                                             // Initial time of the game
    time_t savedtime = 0;                                               // Saved time for the current game
    char *bpplayername = NULL;                                          // Name of the player with the best number of plays
    int bpplays = MAXINT;                                               // Number of plays for the best game in numver of plays
    int bptime = 0;                                                     // Time for the game with the best number of plays
    int bpsize = 0;                                                     // Size of the board for the game with the best number of plays
    char *btplayername = NULL;                                          // Name of the player for the game with the best time
    int btplays = 0;                                                    // Number of plays for the game with the best time
    int bttime = MAXINT;                                                // Time for the game with the best time
    int btsize = 0;                                                     // Size of the board for the game with the best time
    int ngames = -1;                                                    // Number of games for statistical purposes
    int totaltime = 0;                                                  // Total time of play
    int totalplays = 0;                                                 // Total number of plays for the games played
    int totalboard = 0;                                                 // Total of all board sizes


    combination = (int*)malloc(10*sizeof(int));
    Memnames(&playername, &auxname, &bpplayername, &btplayername);
    InitEverything(WIDTH, HEIGHT,&serif, &Demonized, &Queen, &QueenBig, &Targa, &window, &renderer);
    LoadAvaluations(Avaluations);
    LoadColors(Colors);
    ReadStats(bpplayername, &bpplays, &bptime, &bpsize, btplayername, &btplays, &bttime, &btsize,
                &ngames, &totaltime, &totalplays, &totalboard);
    OpenGame(combination, game, &nplays, &boardsize, blacks, whites, playername, &savedtime);
    initialtime = time(NULL);
    while(quit == 0)
    {
        Timer(&actualtime, initialtime, savedtime, renderer, nplays, blacks, boardsize,
                gamestate, combination, Colors, Targa);
        while(SDL_PollEvent (&event))
        {
            if( event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if( event.type == SDL_KEYDOWN)
            {
                NameInsert(event, auxname, nameread, &namepos, gamestate);
                switch(event.key.keysym.sym)
                {
                    case SDLK_q:
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
                        BottomSelect(event, &gamestate, playername, &auxsize);
                        switch(gamestate)
                        {
                            case 0:
                                HomeSelect(event, &gamestate, boardsize, playername, nplays, combination, &auxsize);
                                break;
                            case 1:
                                if(Loss(renderer, nplays, blacks, boardsize, combination, Colors, Targa) != 1
                                    && Win(renderer, nplays, blacks, boardsize, combination, Colors, Targa) != 1)
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
                                SizeSelect(event, &auxsize);
                                NameSelect(event, &nameread);
                                OKPress(event, &gamestate, playername, &boardsize, &combination, &nameread, game,
                                        blacks, whites, &nplays, auxname, &namepos, auxsize, &initialtime, &savedtime,
                                        actualtime, bpplayername, &bpplays, &bptime, &bpsize, btplayername, &btplays,
                                        &bttime, &btsize, &ngames, &totalplays, &totaltime, &totalboard);
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
                Loss(renderer, nplays, blacks, boardsize, combination, Colors, Targa);
                Win(renderer, nplays, blacks, boardsize, combination, Colors, Targa);
                RenderTime(actualtime, renderer, Queen);
                break;
            case 2:
                RenderNewGame(renderer, Queen, QueenBig, auxname, auxsize, nameread);
                break;
            case 3:
                RenderStats(renderer, QueenBig, Queen, Demonized, bpplayername, bpplays, bptime, bpsize,
                            btplayername, btplays, bttime, btsize, ngames, totaltime, totalplays, totalboard);
                break;
            default:
                break;
        }
        RenderImage(renderer, "Preto.bmp", XMENU, YMENU);
        RenderMenu(renderer, Queen);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
        SDL_RenderClear(renderer);
    }
    SaveGame(combination, game, nplays, boardsize, blacks, whites, playername, actualtime);
    SaveStats(bpplayername, bpplays, bptime, bpsize, btplayername, btplays, bttime, btsize,
                ngames, totaltime, totalplays, totalboard);
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
