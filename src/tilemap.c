#include <stdio.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "gfx.h"
#include "tilemap.h"
#include "delta_time.h"

float scroll_pos_x;
float scroll_speed_x;

int tile_postab[MAX_TILES * 2];

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

void scroll_level_background()
{
    scroll_pos_x += scroll_speed_x * get_delta_time();
}
