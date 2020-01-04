#include "SDL.h"

// not sure if these are needed (helped with some errors when using SDL1 but since this is now SDL2 and it seems to build fine without these...?)
//#define stdin  (&__iob_func()[0])
//#define stdout (&__iob_func()[1])
//#define stderr (&__iob_func()[2])

int main(int argc, char* args[])
{
    //Start SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Quit SDL
    SDL_Quit();

    return 0;
}