#include <SDL2/SDL.h>

#include "gfx.h"
#include "main.h"

SDL_Renderer *renderer;
SDL_Texture *backbuffer;

void cls(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderClear(renderer);
}

void flip()
{
    SDL_Rect src, dest;
    src.x = 0;
    src.y = 0;
    src.w = GAME_WIDTH;
    src.h = GAME_HEIGHT;

    dest.x = 0;
    dest.y = 0;
    dest.w = GAME_WIDTH * game_scale;
    dest.h = GAME_HEIGHT * game_scale;
    SDL_RenderCopy(renderer, backbuffer, &src, &dest);

    SDL_RenderPresent(renderer);
}

void draw_subimage_rect(SDL_Texture *texture, int x, int y, int width, int height, int source_x, int source_y)
{
    SDL_Rect src, dest;

    src.x = source_x;
    src.y = source_y;
    src.w = width;
    src.h = height;

    dest.x = x;
    dest.y = y;
    dest.w = width;
    dest.h = height;

    SDL_RenderCopy(renderer, texture, &src, &dest);
}
