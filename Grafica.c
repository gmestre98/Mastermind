#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Grafica.h"


// Function that initializes the SDL library
void InitSDL()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    printf("ERROR initializing the SDL library:%s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}


// Function that initializes the SDL Font Library
void InitFont()
{
  if(TTF_Init() == -1)
  {
    printf("ERROR initializing the SDL Font Library:%s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}


/* Function that creates a window for the application
    param: width of the window
    param: height of the window
    return: pointer to the window
*/
SDL_Window*CreateWindow(int width, int height)
{
  SDL_Window *window = NULL;
  // Inicializing the window
  window = SDL_CreateWindow("Mastermind", WINDOWX, WINDOWY, width, height, 0);
  if(window == NULL)
  {
    printf("Failed to create window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return window;
}


/* Function that creates a renderer for the application
    param: width of the window
    param: height of the window
    param: pointer to the previously created window
    return: pointer to the created renderer
*/
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *window)
{
  SDL_Renderer *renderer;
  renderer = SDL_CreateRenderer(window, -1, 0);
  if(renderer == NULL)
  {
    printf("Failed to create a renderer");
  }

  SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
  return renderer;
}


/* Function that renders some text inside the app window
    param: coordinate x
    param: coordinate y
    param: text string with the text to be written
    param: font used to render the text
    param: color of the text
    param: renderer to handle all the rendering
*/
int RenderText(int x, int y, const char *text, TTF_Font *font, SDL_Color *color,
                SDL_Renderer *renderer)
{
  SDL_Surface *text_surface = NULL;
  SDL_Texture *text_texture = NULL;
  SDL_Rect TextBox;

  TextBox.x=x;
  TextBox.y=y;
  // creating a surface from the string with the defined font
  text_surface = TTF_RenderText_Blended(font, text, *color);
  if(text_surface == NULL)
  {
    printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  // creating the texture
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
  // obtaining the size
  SDL_QueryTexture(text_texture, NULL, NULL, &TextBox.w, &TextBox.h);
  // rendering it
  SDL_RenderCopy(renderer, text_texture, NULL, &TextBox);
  // clearing the memory
  SDL_DestroyTexture(text_texture);
  SDL_FreeSurface(text_surface);
  return TextBox.h;
}


/* Function that renders in the window an image using the name of the image file
    param: renderer to handle all the renderering
    param: string with name of the image file
    param: x coordinate for the left corner of the image
    param: y coordinate for the right corner of the image
*/
void RenderImage(SDL_Renderer *renderer, char string[], int x, int y)
{
  SDL_Texture *Img_Texture = NULL;
  SDL_Surface *Img_Surface = NULL;
  SDL_Rect ImgBox;

  // loads the image from the chosen file
  Img_Surface = SDL_LoadBMP(string);
  if(Img_Surface == NULL)
  {
    printf("It was not possible to load the chosen image:%s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  // choosing the coordinates where to render the image
  ImgBox.x = x;
  ImgBox.y = y;
  ImgBox.w = Img_Surface->w;
  ImgBox.h = Img_Surface->h;

  // creating a texture for the chosen image and rendering it in the window
  Img_Texture = SDL_CreateTextureFromSurface(renderer, Img_Surface);
  SDL_RenderCopy(renderer, Img_Texture, NULL, &ImgBox);

  // clearing the memory
  SDL_DestroyTexture(Img_Texture);
  SDL_FreeSurface(Img_Surface);
}


/* Function that initializes the renderer, the window and all fonts
    param: width of the window
    param: height of the window
    param: font serif
    param: font Demonized
    param: font Queen
    param: the window for the game
    param: the renderer to handle all rendering in the window
*/
void InitEverything(int width, int height, TTF_Font **_font, TTF_Font **_font2, TTF_Font **_font3,
                    TTF_Font **_font4, TTF_Font **_font5, SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    *_font = TTF_OpenFont("FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font2 = TTF_OpenFont("Demonized.ttf", 15);
    if(!* _font2)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font3 = TTF_OpenFont("Queen.ttf", 18);
    if(!* _font3)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font4 = TTF_OpenFont("Queen.ttf", 40);
    if(!* _font4)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font5 = TTF_OpenFont("Targa.ttf", 18);
    if(!* _font5)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/* Function renders the board for the game
    param: the renderer to handle all rendering in the window
    param: size of the board, number of pieces per play
    param: Array of the avaluation images
*/
void RenderBoard(SDL_Renderer *renderer, int boardsize, SDL_Surface **Avaluations)
{
    int i = 0;
    int j = 0;
    int holex = FIRSTPIECEX;
    int holey = FIRSTPIECEY;
    int xcorrect = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX;
    SDL_Rect BoardPos;
    SDL_Texture *AvalTexture;

    // Rendering the background image
    RenderImage(renderer, "Fundo.bmp", BACKGROUNDX, BACKGROUNDY);
    // Rendering the number of each play
    RenderImage(renderer, "Numeros_Jogada.bmp", xcorrect + NUMBERX, NUMBERSY);

    // Rendering the pieces for each play
    for(i=0; i < MAXPLAYS; i++)
    {
        holex = xcorrect;
        for(j=0; j < boardsize; j++)
        {
            RenderImage(renderer, "Hole.bmp", holex, holey);
            holex += PIECESIZE;
        }
        holey += PIECESIZE;
    }
    xcorrect += boardsize*PIECESIZE + EXTRAPOS/2;
    AvalTexture = SDL_CreateTextureFromSurface(renderer, Avaluations[boardsize-MINLEVEL]);
    BoardPos.x = xcorrect;
    BoardPos.y = AVALY;
    BoardPos.w = (Avaluations[boardsize-MINLEVEL])->w + EXTRAPOS;
    BoardPos.h = (Avaluations[boardsize-MINLEVEL])->h + EXTRAPOS;
    for(i=0; i < MAXPLAYS; i++)
    {
        SDL_RenderCopy(renderer, AvalTexture, NULL, &BoardPos);
        BoardPos.y += PIECESIZE;
    }
    SDL_DestroyTexture(AvalTexture);
    xcorrect += (BoardPos.w + EXTRAPOS);
    // Rendering the block of colors
    RenderImage(renderer, "Cores.bmp", xcorrect, COLORSY);
    RenderImage(renderer, "Nome.bmp", XNOME, YNOME);

}


/* Function that initializes the array of the avaluation images
    param: Array of the avaluation images
*/
void LoadAvaluations(SDL_Surface **Avaluations)
{
    int i = 0;
    char filename[MAXSTR] = {0};

    for(i=0; i < MAX_LEVELS; i++)
    {
        // Reading the filename
        sprintf(filename, "Aval_%01d.jpg", i+MINLEVEL);
        // Opening the image
        Avaluations[i] = IMG_Load(filename);
        if(Avaluations[i] == NULL)
        {
            printf("ERROR! It was not possible to load the avaluation image %d\n", i+MINLEVEL);
            exit(EXIT_FAILURE);
        }
    }
}


/* Function that frees the memory for all the avaluation images
    param: Array of the avaluation images
*/
void UnloadAvaluations(SDL_Surface **Avaluations)
{
    int i = 0;

    for(i=0; i < MAX_LEVELS; i++)
    {
        SDL_FreeSurface(Avaluations[i]);
    }
}


/* Function that initializes the array of the color images
    param: Array of the color images
*/
void LoadColors(SDL_Surface **Colors)
{
    int i = 0;
    char filename[MAXSTR] = {0};

    for(i=0; i < NMBRCOLORS; i++)
    {
        // Reading the filename
        sprintf(filename, "Cor%01d.jpg", i+1);
        // Opening the image
        Colors[i] = IMG_Load(filename);
        if(Colors[i] == NULL)
        {
            printf("ERROR! It was not possible to load the color image %d\n", i+1);
            exit(EXIT_FAILURE);
        }
    }
}


/* Function that frees the memory for all the color images
    param: Array of the color images
*/
void UnloadColors(SDL_Surface **Colors)
{
    int i = 0;

    for(i=0; i < NMBRCOLORS; i++)
    {
        SDL_FreeSurface(Colors[i]);
    }
}


/* Function that renders an image from an array of images at the chosen coordinates
    param: the renderer to handle all rendering in the window
    param: Array of images
    param: Index for the image
    param: X coordinate
    param: Y coordinate
*/
void RenderFromArray(SDL_Renderer *renderer, SDL_Surface **Array, int index, int x, int y)
{
    SDL_Rect BoardPos;
    SDL_Texture *ImgTexture;

    ImgTexture = SDL_CreateTextureFromSurface(renderer, Array[index]);
    BoardPos.x = x;
    BoardPos.y = y;
    BoardPos.w = (Array[index])->w;
    BoardPos.h = (Array[index])->h;
    SDL_RenderCopy(renderer, ImgTexture, NULL, &BoardPos);
    SDL_DestroyTexture(ImgTexture);
}


/* Function that renders an arrow indicating the current Play
    param: the renderer to handle all the rendering in the window
    param: variable indicating how many plays have already been made
    param: size of the board, number of pieces per play
*/
void RenderPlay(SDL_Renderer *renderer, int nplays, int boardsize)
{
    int x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + PLAYX;
    int y = FIRSTPIECEY + (MAXNPLAYS - nplays)*YPERPLAY;
    if(nplays < 10)
    {
        y = FIRSTPIECEY + (MAXNPLAYS - nplays)*YPERPLAY;
    }
    else
    {
        y = FIRSTPIECEY;
    }
    RenderImage(renderer, "Play.bmp", x, y);
}


/* Function that renders the pieces chosen by the user to put in the board
    param: the renderer to handle all the rendering in the window
    param: Array of the color images
    param: Matrix with the selected pieces by the user for the current game
    param: size of the board, number of pieces per play
*/
void RenderPieces(SDL_Renderer *renderer, SDL_Surface **Colors, int game[][MAXBOARD], int boardsize)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    int startx = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX;

    for(i=0; i < MAXPLAYS; i++)
    {
        y = FIRSTPIECEY + (MAXNPLAYS - i)*YPERPLAY + YPIECECORR;
        for(j=0; j < boardsize; j++)
        {
            x = startx + j*PIECESIZE + XPIECECORR;
            if(game[i][j] != 0)
            {
                RenderFromArray(renderer, Colors, game[i][j] - 1, x, y);
            }
        }
    }
}


/* Function to render the avaluation for the 4,6,8 boards
    param: the renderer to handle all the renderering in the window
    param: size of the board, number of pieces per play
    param: Array with the number of correct pieces in the right places per play
    param: Array with the number of correct pieces in the wrong places per play
    param: variable indicating how many plays have already been made
*/
void RenderAvalPair(SDL_Renderer *renderer, int boardsize, int blacks[], int whites[], int nplays)
{
    int i = 0;
    int j = 0;
    int x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX;
    int y = FIRSTPIECEY + (MAXNPLAYS - i)*YPERPLAY + YPIECECORR;
    int bl = 0;
    int wh = 0;
    for(j=0; j < nplays; j++)
    {
        bl = blacks[j];
        i=0;
        x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX;
        y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
        while(bl != 0)
        {
            bl --;
            RenderImage(renderer, "Black.bmp", x, y);
            y += AVALPOS;
            i++;
            if(i%2 == 0)
            {
                x += AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
            }
        }
        wh = whites[j];
        while(wh != 0)
        {
            wh --;
            RenderImage(renderer, "White.bmp", x, y);
            y += AVALPOS;
            i++;
            if(i%2 == 0)
            {
                x += AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
            }
        }
    }
}


/* Function to render the avaluation for the 5 board
    param: the renderer to handle all the renderering in the window
    param: size of the board, number of pieces per play
    param: Array with the number of correct pieces in the right places per play
    param: Array with the number of correct pieces in the wrong places per play
    param: variable indicating how many plays have already been made
*/
void RenderAvalFive(SDL_Renderer *renderer, int boardsize, int blacks[], int whites[], int nplays)
{
    int i = 0;
    int j = 0;
    int x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX;
    int y = FIRSTPIECEY + (MAXNPLAYS - i)*YPERPLAY + YPIECECORR;
    int bl = 0;
    int wh = 0;
    for(j=0; j <= nplays; j++)
    {
        bl = blacks[j];
        i=0;
        x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX;
        y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
        while(bl != 0)
        {
            bl --;
            RenderImage(renderer, "Black.bmp", x, y);
            y += AVALPOS;
            i++;
            if(i == 2)
            {
                x += 2*AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
            }
            else if( i == 4)
            {
                x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX + AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY + AVALCORRYF;
            }
        }
        wh = whites[j];
        while(wh != 0)
        {
            wh --;
            RenderImage(renderer, "White.bmp", x, y);
            y += AVALPOS;
            i++;
            if(i == 2)
            {
                x += 2*AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
            }
            else if( i == 4)
            {
                x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX + AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY + AVALCORRYF;
            }
        }
    }
}


/* Function to render the avaluation for the 7 board
    param: the renderer to handle all the renderering in the window
    param: size of the board, number of pieces per play
    param: Array with the number of correct pieces in the right places per play
    param: Array with the number of correct pieces in the wrong places per play
    param: variable indicating how many plays have already been made
*/
void RenderAvalSeven(SDL_Renderer *renderer, int boardsize, int blacks[], int whites[], int nplays)
{
    int i = 0;
    int j = 0;
    int x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX;
    int y = FIRSTPIECEY + (MAXNPLAYS - i)*YPERPLAY + YPIECECORR;
    int bl = 0;
    int wh = 0;
    for(j=0; j <= nplays; j++)
    {
        bl = blacks[j];
        i=0;
        x = (MAXBOARD-boardsize)*BOARDCORR + FIRSTPIECEX + boardsize*PIECESIZE + EXTRAPOS + AVALCORRX;
        y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
        while(bl != 0)
        {
            bl --;
            RenderImage(renderer, "Black.bmp", x, y);
            y += AVALPOS;
            i++;
            if(i%2 == 0)
            {
                x += AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
            }
            if(i == 6)
            {
                y += AVALCORRYS;
            }
        }
        wh = whites[j];
        while(wh != 0)
        {
            wh --;
            RenderImage(renderer, "White.bmp", x, y);
            y += AVALPOS;
            i++;
            if(i%2 == 0)
            {
                x += AVALPOS;
                y = FIRSTPIECEY + (MAXNPLAYS - j)*YPERPLAY + YPIECECORR + AVALCORRY;
            }
            if(i == 6)
            {
                y += AVALCORRYS;
            }
        }
    }
}


/* Function to render the avaluation for each play
    param: the renderer to handle all the renderering in the window
    param: size of the board, number of pieces per play
    param: Array with the number of correct pieces in the right places per play
    param: Array with the number of correct pieces in the wrong places per play
    param: variable indicating how many plays have already been made
*/
void RenderAval(SDL_Renderer *renderer, int boardsize, int blacks[], int whites[], int nplays)
{
    if(boardsize%2 == 0)
    {
        RenderAvalPair(renderer, boardsize, blacks, whites, nplays);
    }
    else if(boardsize == 5)
    {
        RenderAvalFive(renderer, boardsize, blacks, whites, nplays);
    }
    else if(boardsize == 7)
    {
        RenderAvalSeven(renderer, boardsize, blacks, whites, nplays);
    }
}


/* Function to render the menus line in the bottom of the window
    param: the renderer to handle all the rendering in the window
    param: font for the names of each option
*/
void RenderMenu(SDL_Renderer *renderer, TTF_Font *Queen)
{
    SDL_Color white = {255, 255, 255};

    RenderImage(renderer, "Home.bmp", XHOME, YHOME);
    RenderImage(renderer, "New_Game.bmp", XNEWGAME, YNEWGAME);
    RenderImage(renderer, "Statistics.bmp", XSTATISTICS, YSTATISTICS);
    RenderText(XHOMETXT, YHOMETXT, "Home", Queen, &white, renderer);
    RenderText(XNGTXT, YNGTXT, "New Game", Queen, &white, renderer);
    RenderText(XSTATS, YSTATS, "Statistics", Queen, &white, renderer);
}


/* Function to render the home menu
    param: the renderer to handle all the rendering in the window
    param: font for the names of each option
    param: font for the game name in the top
*/
void RenderHome(SDL_Renderer *renderer, TTF_Font *Queen, TTF_Font *QueenBig)
{
    SDL_Color white = {255, 255, 255};

    RenderImage(renderer, "Fundo.bmp", BACKGROUNDX, BACKGROUNDY);
    RenderImage(renderer, "TextBox.bmp", XTEXTBOX, YTEXTBOX);
    RenderImage(renderer, "TextBox.bmp", XTEXTBOX, YTEXTBOX + BOXHEIGHT);
    RenderImage(renderer, "TextBox.bmp", XTEXTBOX, YTEXTBOX + 2*BOXHEIGHT);
    RenderText(XCGAME, YOPTION, "Current Game", Queen, &white, renderer);
    RenderText(XNGAME, YOPTION + BOXHEIGHT, "New Game", Queen, &white, renderer);
    RenderText(XHOMESTATS, YOPTION + 2*BOXHEIGHT, "Statistics", Queen, &white, renderer);
    RenderImage(renderer, "ScreenshotJogo.bmp", XSCREENSHOT, YSCREENSHOT);
    RenderText(XTITLE, YTITLE, "Mastermind", QueenBig, &white, renderer);
}


/* Function to render the new game menu
    param: the renderer to handle all the rendering in the window
    param: font for text of the namee
    param: font for the game name in the top
*/
void RenderNewGame(SDL_Renderer *renderer, TTF_Font *Queen, TTF_Font *QueenBig, char *playername, int boardsize, int nameread)
{
    SDL_Color white = {255, 255, 255};

    RenderImage(renderer, "Fundo.bmp", BACKGROUNDX, BACKGROUNDY);
    RenderImage(renderer, "Numeros.bmp", XNUMEROS, YNUMEROS);
    RenderText(XTITLE, YTITLE, "Mastermind", QueenBig, &white, renderer);
    RenderImage(renderer, "NameBox.bmp", XNAME, YNAME);
    RenderText(XINFNAME, YINFNAME, "Introduza um nome de jogador!", Queen, &white, renderer);
    if(boardsize != 0)
    {
        RenderImage(renderer, "Bordo.bmp", XNUMEROS, YNUMEROS + (boardsize-MINLEVEL)*NUMBERSIZE);
    }
    if(playername[0]  == 0  &&  nameread == 0)
    {
        RenderText(XNAMEBOX + CORRXNAME, YNAMEBOX + CORRYNAME, "Username", Queen, &white, renderer);
    }
    else if(playername[0] != 0)
    {
        RenderText(XNAMEBOX + CORRXNAME, YNAMEBOX + CORRYNAME, playername, Queen, &white, renderer);
    }
}


/* Function that renders the current time of the game
    param: actual time of the game
    param: the renderer to handle all the rendering in the window
    param: font for the time rendering
*/
void RenderTime(time_t actualtime, SDL_Renderer *renderer, TTF_Font *font)
{
    int secs = 0;
    int mins = 0;
    char str[TIMERSIZE] = {0};
    SDL_Color white = {255, 255, 255};

    secs = actualtime%SIZEOFMIN;
    mins = actualtime/SIZEOFMIN;
    if(mins < PROBSIZES)
    {
        str[0] = '0';
        str[1] = '0' + mins;
    }
    else
    {
        str[0] = '0' + mins/PROBSIZES;
        str[1] = '0' + mins%PROBSIZES;
    }
    str[2] = ':';
    if(secs < PROBSIZES)
    {
        str[3] = '0';
        str[4] = '0' + secs;
    }
    else
    {
        str[3] = '0' + secs/PROBSIZES;
        str[4] = '0' + secs%PROBSIZES;
    }
    RenderText(XTIMER, YTIMER - TITLEVAR, "Timer", font, &white, renderer);
    RenderText(XTIMER, YTIMER, str, font, &white, renderer);
}


/* Function that renders all stats for the played games
    param: the renderer to handle all the rendering in the window
    param: the font for the game name
    param: the font for the titles
    param: the font for the info
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
void RenderStats(SDL_Renderer *renderer, TTF_Font *GameFont, TTF_Font *Titlesfont, TTF_Font *font,
                char *bpplayername, int bpplays, int bptime, int bpsize, char *btplayername, int btplays,
                int bttime, int btsize, int ngames, int totaltime, int totalplays, int totalboard)
{
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    char str[STRMAX] = {0};
    float avtime = totaltime/ngames;
    float avplays = totalplays/ngames;
    float avsize = totalboard/ngames;


    RenderImage(renderer, "Fundo.bmp", BACKGROUNDX, BACKGROUNDY);
    RenderText(XTITLE, YTITLE, "Mastermind", GameFont, &white, renderer);
    RenderText(XBESTPLAYS, YBESTPLAYS, "Won game in record plays", Titlesfont, &white, renderer);
    RenderText(XBESTTIME, YBESTTIME, "Won game in record time", Titlesfont, &white, renderer);
    RenderText(XAVARAGES, YAVARAGES, "Statistics for all games played", Titlesfont, &white, renderer);
    RenderText(XBPPLAYER, YBPPLAYER, "Player name :", Titlesfont, &black, renderer);
    RenderText(XBPPLAYS, YBPPLAYS, "Number of plays :", Titlesfont, &black, renderer);
    RenderText(XBPTIME, YBPTIME, "Time of the game :", Titlesfont, &black, renderer);
    RenderText(XBPSIZE, YBPSIZE, "Size of the board :", Titlesfont, &black, renderer);
    RenderText(XBTPLAYER, YBTPLAYER, "Player name :", Titlesfont, &black, renderer);
    RenderText(XBTPLAYS, YBTPLAYS, "Number of plays :", Titlesfont, &black, renderer);
    RenderText(XBTTIME, YBTTIME, "Time of the game :", Titlesfont, &black, renderer);
    RenderText(XBTSIZE, YBTSIZE, "Size of the board :", Titlesfont, &black, renderer);
    RenderText(XNGAMES, YNGAMES, "Number of games played :", Titlesfont, &black, renderer);
    RenderText(XAVTIME, YAVTIME, "Time per game :", Titlesfont, &black, renderer);
    RenderText(XAVPLAYS, YAVPLAYS, "Plays per game :", Titlesfont, &black, renderer);
    RenderText(XAVSIZE, YAVSIZE, "Av. size of the board :", Titlesfont, &black, renderer);


    if(bpplayername[0] != 0)
    {
        RenderText(XBPPLAYERD, YBPPLAYER + STATSCORR, bpplayername, font, &white, renderer);
        sprintf(str, "%d", bpplays);
        RenderText(XBPPLAYSD, YBPPLAYS + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%d", bptime);
        RenderText(XBPTIMED, YBPTIME + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%d", bpsize);
        RenderText(XBPSIZED, YBPSIZE + STATSCORR, str, font, &white, renderer);
    }

    if(btplayername[0] != 0)
    {
        RenderText(XBTPLAYERD, YBTPLAYER + STATSCORR, btplayername, font, &white, renderer);
        sprintf(str, "%d", btplays);
        RenderText(XBTPLAYSD, YBTPLAYS + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%d", bttime);
        RenderText(XBTTIMED, YBTTIME + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%d", btsize);
        RenderText(XBTSIZED, YBTSIZE + STATSCORR, str, font, &white, renderer);
    }

    if(ngames != 0)
    {
        sprintf(str, "%d", ngames);
        RenderText(XNGAMESD, YNGAMES + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%0.2f", avtime);
        RenderText(XAVTIMED, YAVTIME + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%0.2f", avplays);
        RenderText(XAVPLAYSD, YAVPLAYS + STATSCORR, str, font, &white, renderer);
        sprintf(str, "%0.2f", avsize);
        RenderText(XAVSIZED, YAVSIZE + STATSCORR, str, font, &white, renderer);
    }
}
