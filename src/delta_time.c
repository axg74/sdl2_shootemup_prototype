#include <SDL2/SDL.h>

float delta_time;
Uint32  delta_time_last;

void delta_time_init()
{
    delta_time_last = SDL_GetTicks();
}

void delta_time_update()
{
    Uint32 current_time = SDL_GetTicks();
    delta_time = ( (float) current_time - (float) delta_time_last) / 1000.0f;
    delta_time_last = current_time;
}

float get_delta_time() 
{
    return delta_time;
}