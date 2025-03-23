#include <stdio.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "gfx.h"
#include "tilemap.h"
#include "delta_time.h"

float scroll_pos_x;
float scroll_pos_y;

float scroll_speed_x;
float scroll_speed_y;

int tile_postab[MAX_TILES * 2];

void scroll_level_background()
{
    scroll_pos_x += scroll_speed_x * get_delta_time();
}

void tilemap_draw(SDL_Texture *tileset)
{
    int tile_id = 2;
    int soft_scroll_x = (int) scroll_pos_x % TILE_SIZE;

    for (int y = 0; y < GAME_HEIGHT / TILE_SIZE; y++)
    {
        for (int x = 0; x < GAME_WIDTH / TILE_SIZE + 1; x++)
        {
            int tile_source_x = tile_postab[tile_id * 2 + 0];
            int tile_source_y = tile_postab[tile_id * 2 + 1];

            draw_subimage_rect(tileset, (x * TILE_SIZE) - soft_scroll_x, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tile_source_x, tile_source_y);
        }
    }
}

void calc_tilepos_tab()
{
    int c = 0;

    for (int y = 0; y < TILESHEET_HEIGHT / TILE_SIZE; y++)
    {
        for (int x = 0; x < TILESHEET_WIDTH / TILE_SIZE; x++)
        {
           tile_postab[c+0] = x * TILE_SIZE;
           tile_postab[c+1] = y * TILE_SIZE;
           c += 2;
        }
    }
}

void tilemap_init()
{
    calc_tilepos_tab();
}

float tilemap_get_scroll_pos_x()
{
    return scroll_pos_x;
}

float tilemap_get_scroll_pos_y()
{
    return scroll_pos_y;
}

void tilemap_set_scroll_pos_x(float x)
{
    scroll_pos_x = x;
}

void tilemap_set_scroll_pos_y(float y)
{
    scroll_pos_y = y;
}

float tilemap_get_scroll_speed_x()
{
    return scroll_speed_x;
}

float tilemap_get_scroll_speed_y()
{
    return scroll_speed_y;
}

void tilemap_set_scroll_speed_x(float x)
{
    scroll_speed_x = x;
}

void tilemap_set_scroll_speed_y(float y)
{
    scroll_speed_x = y;
}