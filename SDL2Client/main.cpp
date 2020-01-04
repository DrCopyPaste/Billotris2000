#include "SDL.h"

#define stdin  (&__iob_func()[0])
#define stdout (&__iob_func()[1])
#define stderr (&__iob_func()[2])

int main(int argc, char* args[])
{
    //Start SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Quit SDL
    SDL_Quit();

    return 0;
}