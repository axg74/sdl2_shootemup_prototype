#include <SDL2/SDL.h>

#include "gfx.h"
#include "main.h"
#include "config.h"

char window_title[] = "Game-2D SDL2";

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *backbuffer;

SDL_Texture *sprite_sheets[MAX_SPRITE_SHEETS];
SDL_Texture *tilesheets[MAX_TILE_SHEETS];

int game_scale;
int screen_width;
int screen_height;

bool init_window(int width, int height, int scale)
{
    screen_width = width;
    screen_height = height;
    game_scale = scale;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    window = SDL_CreateWindow(window_title,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screen_width * game_scale,
                              screen_height * game_scale,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) return false;

    backbuffer = SDL_CreateTexture(renderer,
                                   SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET,
                                   screen_width, screen_height);
    if (backbuffer == NULL) return false;

    return true;
}

void destroy_window()
{
    if(backbuffer != NULL) SDL_DestroyTexture(backbuffer);
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
}

void exit_app()
{
    SDL_Quit();
}

SDL_Texture* load_bmp(const char *filename)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = SDL_LoadBMP(filename);
    if (surface == NULL) return NULL;

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLORKEY_RED, COLORKEY_GREEN, COLORKEY_BLUE));

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

void unload_spritesheet(int index)
{
    if (sprite_sheets[index] != NULL)
    {
        destroy_bmp(sprite_sheets[index]);
        sprite_sheets[index] = NULL;
    }
}

bool load_spritesheet(int index, const char *filename)
{
    unload_spritesheet(index);
    sprite_sheets[index] = load_bmp(filename);

    if (sprite_sheets[index] == NULL)
    {
        return false;
    }

    return true;
}

void unload_tilesheet(int index)
{
    if (tilesheets[index] != NULL)
    {
        destroy_bmp(tilesheets[index]);
        tilesheets[index] = NULL;
    }
}

bool load_tilesheet(int index, const char *filename)
{
    unload_tilesheet(index);
    tilesheets[index] = load_bmp(filename);

    if (tilesheets[index] == NULL)
    {
        return false;
    }

    return true;
}

SDL_Texture* get_spritesheet(int index)
{
    return sprite_sheets[index];
}

SDL_Texture* get_tilesheet(int index)
{
    return tilesheets[index];
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
    src.w = screen_width;
    src.h = screen_height;

    dest.x = 0;
    dest.y = 0;
    dest.w = screen_width * game_scale;
    dest.h = screen_height * game_scale;
    SDL_RenderCopy(renderer, backbuffer, &src, &dest);
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}

void enable_backbuffer_rendering()
{
    SDL_SetRenderTarget(renderer, backbuffer);
}

void disable_backbuffer_rendering()
{
    SDL_SetRenderTarget(renderer, NULL);
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

void draw_bmp_text(SDL_Texture *texture, int x, int y, int source_x, int source_y, const char *text)
{
    int ascii_start_code = 33;
    int font_width = 8;
    int font_height = 7;

    while (*text != 0)
    {
        int x_offset = ((*text) - ascii_start_code) * font_width;
        draw_subimage_rect(texture, x, y, font_width, font_height, source_x + x_offset, source_y);
        x += font_width;
        text++;
    }
}

int get_screen_width()
{
    return screen_width;
}

int get_screen_height()
{
    return screen_height;
}
