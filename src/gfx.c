#include <SDL2/SDL.h>

#include "gfx.h"
#include "main.h"

char window_title[] = "Game-2D SDL2";

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *backbuffer;

SDL_Texture *sprite_sheets[5];
SDL_Texture *tilesheets[5];

int game_scale;

bool init_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    window = SDL_CreateWindow(window_title,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GAME_WIDTH * game_scale,
                              GAME_HEIGHT * game_scale,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) return false;

    backbuffer = SDL_CreateTexture(renderer,
                                   SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET,
                                   GAME_WIDTH, GAME_HEIGHT);
    if (backbuffer == NULL) return false;

    return true;
}

void destroy_window()
{
    if(backbuffer != NULL) SDL_DestroyTexture(backbuffer);
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
}

SDL_Texture* load_bmp(const char *filename)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = SDL_LoadBMP(filename);
    if (surface == NULL) return NULL;

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        if (surface != NULL) SDL_FreeSurface(surface);
        return NULL;
    }

    if (surface != NULL) SDL_FreeSurface(surface);
    return texture;
}

void destroy_bmp(SDL_Texture *texture)
{
    if (texture != NULL) SDL_DestroyTexture(texture);
}

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

void sprite_draw(Sprite *spr)
{
    SDL_Rect src, dest;

    if (spr->active)
    {
        src.x = spr->source_x;
        src.y = spr->source_y;
        src.w = spr->width;
        src.h = spr->height;

        dest.x = (int) spr->x;
        dest.y = (int) spr->y;
        dest.w = src.w;
        dest.h = src.h;

        SDL_RenderCopy(renderer, spr->texture, &src, &dest);
    }
}
