/*****************************************************************************************
 * View.cpp - Class for handling drawing, it uses SDL2 for the rendering.
/*****************************************************************************************/

#include "View.h"

static TTF_Font *font;
static SDL_Window  *win;
static SDL_Renderer *ren;
static SDL_Surface  *surface;
static SDL_Surface  *imgSurface;
static SDL_Texture *background_tx;										    // Screen
static Uint32 mColors [COLOR_MAX][4] = {  {0   , 0   , 0   , 0   },
                                          {0x00, 0x00, 0x00, 0xff},					// Colors
                                          {0xff, 0x00, 0x00, 0xff},
                                          {0x00, 0xff, 0x00, 0xff},
                                          {0x00, 0x00, 0xff, 0xff},
                                          {0x00, 0xff, 0xff, 0xff},
                                          {0xff, 0x00, 0xff, 0xff},
                                          {0xff, 0xff, 0x00, 0xff},
                                          {0xff, 0xff, 0xff, 0xff} };

int View::messageBox ()
{
    const SDL_MessageBoxButtonData buttons[] = {
          { /* .flags, .buttonid, .text */        0, 0, "NO" },
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "YES" },
      };
    const SDL_MessageBoxColorScheme colorScheme = {
          { /* .colors (.r, .g, .b) */
              /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
              {   0,   0,   0 },
              /* [SDL_MESSAGEBOX_COLOR_TEXT] */
              {   0, 255,   0 },
              /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
              { 255, 255,   0 },
              /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
              { 205, 205, 205 },
              /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
              { 255,   0, 255 }
          }
      };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "GAME OVER!", /* .title */
            "Would you like to play again?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
        };

     int buttonid;
     if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
     }
     if (buttonid == -1) {
         SDL_Log("no selection");
     } else {
         return buttonid;
     }
     return 0;
}
/*
======================================
Init
======================================
*/
View::View()
{
    initGraph();
}

int View::initGraph ()
{
    // const SDL_RendererInfo *info;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0)
    {
    	fprintf(stderr, "TTF_Init Error: %s", TTF_GetError());
        return 1;
    }

    //win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    win = SDL_CreateWindow("Tetris",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          1024, 550,
                          SDL_WINDOW_OPENGL);

    if (win == NULL){
        fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError()) ;
        SDL_Quit();
        return 1;
    }

    SDL_RaiseWindow(win);

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    font = TTF_OpenFont("arial.ttf", 12);

    //surface = SDL_GetWindowSurface(win);
    imgSurface = SDL_LoadBMP("orange.bmp");
    background_tx = SDL_CreateTextureFromSurface (ren, imgSurface);
    SDL_FreeSurface( imgSurface );
    SDL_RenderCopy(ren, background_tx, NULL, NULL);

    updateScreen();

    return 1;
}

/*
=================================================================
drawBlock - Draws the rectangle blocks in the game
=================================================================
*/
void View::drawBlock  (int pX1, int pY1, int pX2, int pY2, enum color pC)
{
    SDL_Rect r = {pX1, pY1, pX2, pY2};
    SDL_SetRenderDrawColor(ren, mColors[pC][0], mColors[pC][1], mColors[pC][2], mColors[pC][3]);
    SDL_RenderFillRect(ren, &r);

}

/*
======================================
Clear the screen to black
======================================
*/
void View::clearScreen ()
{
    color pC = BLACK;
    SDL_SetRenderDrawColor(ren, mColors[pC][0], mColors[pC][1], mColors[pC][2], mColors[pC][3]);
    SDL_RenderClear(ren);
}

// returns screenHeight
int View::getScreenHeight ()
{
    return SDL_GetWindowSurface(win)->h;
}

// updates screen to show all the renderings
void View::updateScreen ()
{
    SDL_RenderPresent(ren);
}

// Loads Background image
void View::loadBackGround()
{
    SDL_RenderCopy(ren, background_tx, NULL, NULL);
}

// Loads score
void View::showScore (unsigned int score)
{
    char str[20];
    SDL_Surface* textSurface = NULL;
    SDL_Color foregroundColor = {255,255,255};
    SDL_Color backgroundColor = {0,0,255};

    sprintf(str,"Score: %d", score);

    textSurface = TTF_RenderText_Solid(font, str, foregroundColor);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(ren, textSurface);

    SDL_Rect Message_rect;
    Message_rect.x = 750;    
    Message_rect.y = 100;
    Message_rect.w = 100;
    Message_rect.h = 30;

    SDL_RenderCopy(ren, Message, NULL, &Message_rect);

}

void View::cleanUp()
{
    SDL_DestroyTexture(background_tx);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
