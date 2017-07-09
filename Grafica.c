#include <stdio.h>
#include <stdlib.h>

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


// Function that creates a window for the application
/*  param: width of the window
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


// Function that creates a renderer for the application
/*  param: width of the window
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
}


// Function that renders some text inside the app window
/*  param: coordinate x
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
                    SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    *_font = TTF_OpenFont(".//Fontes//FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font2 = TTF_OpenFont(".//Fontes//Demonized.ttf", 24);
    if(!* _font2)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    *_font3 = TTF_OpenFont(".//Fontes//Queen.ttf", 24);
    if(!* _font3)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

//void RenderBoard()
