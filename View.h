/*****************************************************************************************
 * View.h - Class for handling drawing, it uses SDL2 for the rendering.
/*****************************************************************************************/

#ifndef _VIEW_
#define _VIEW_

// ------- Includes --------

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"
#endif

#include <stdio.h>
#include <stdlib.h>

enum color {ZERO, BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; // Colors

class View {
public:

    View                ();

    void drawBlock      (int pX1, int pY1, int pX2, int pY2, enum color pC);
    void clearScreen    ();
    int getScreenHeight ();
    int initGraph       ();
    void updateScreen   ();
    void cleanUp        ();
    void loadBackGround ();
    int messageBox      ();
    void loadText       ();
    void showScore      (unsigned int);
};
