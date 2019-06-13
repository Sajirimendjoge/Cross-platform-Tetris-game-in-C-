/**************************************************************************
 * Commands.h - Class that handles inputs (keyboard inputs)
 /**************************************************************************/

#ifndef _COMMANDS_
#define _COMMANDS_

// ------- Includes --------

#include "SDL.h"
#include <stdlib.h>

class Commands {
public:
    int pollkey    (SDL_Event *e);
    int isKeyDown  (int pKey);
};

#endif // _COMMANDS_
