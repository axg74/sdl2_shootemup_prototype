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
    delta_time = (current_time - delta_time_last) / 1000.0f;
    delta_time_last = current_time;
}
