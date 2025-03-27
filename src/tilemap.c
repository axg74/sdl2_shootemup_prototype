#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "main.h"
#include "gfx.h"
#include "tilemap.h"
#include "delta_time.h"
#include "config.h"
#include "file.h"

float scroll_pos_x;
float scroll_pos_y;

float scroll_speed_x;
float scroll_speed_y;

int map_width;
int map_height;

int tile_postab[MAX_TILES * 2];

char *level_data[MAX_TMX_DATA_FILES];
int *tilemap_layer_data[MAX_TILEMAP_LAYER + 1];

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

void set_tilemap_width(int width)
{
    if (width < 1 || width >= MAX_TILEMAP_WIDTH) return;
    map_width = width;
}

void set_tilemap_height(int height)
{
    if (height < 1 || height >= MAX_TILEMAP_HEIGHT) return;
    map_height = height;
}

int get_tilemap_width()
{
    return map_width;
}

int get_tilemap_height()
{
    return map_height;
}

bool alloc_tilemap(int tilemap_layer_index)
{
    if (tilemap_layer_index < 0 || tilemap_layer_index > MAX_TILEMAP_LAYER) return false;
    if (map_width == 0 || map_width > MAX_TILEMAP_WIDTH || map_height == 0 || map_height > MAX_TILEMAP_HEIGHT) return false;

    tilemap_layer_data[tilemap_layer_index] = (int *) malloc(sizeof(int) + (map_width * map_height * sizeof(int)));
    if ( tilemap_layer_data[tilemap_layer_index] == NULL)
    {
        return false;
    }

    return true;
}

void free_tilemap(int tilemap_layer_index)
{
    if (tilemap_layer_index < 0 || tilemap_layer_index > MAX_TILEMAP_LAYER) return;
    if (tilemap_layer_data[tilemap_layer_index] != NULL)
    {
        free(tilemap_layer_data[tilemap_layer_index]);
    }
}

void unload_tmx_tilemap(int mapdata_index)
{
    if (mapdata_index < 0 || mapdata_index > MAX_TMX_DATA_FILES) return;
    if (level_data[mapdata_index] != NULL)
    {
        unload_textfile(level_data[mapdata_index]);
    }
}

void unload_all_tmx_tilemaps()
{
    for (int i = 0; i < MAX_TMX_DATA_FILES; i++)
    {
        unload_tmx_tilemap(i);
    }
}

bool load_tmx_tilemap(const char *filename, int mapdata_index)
{
    if (mapdata_index < 0 || mapdata_index > MAX_TMX_DATA_FILES) return false;

    level_data[mapdata_index] = load_textfile(filename);

    if (level_data[mapdata_index] == NULL)
    {
        return false;
    }

    return true;
}

int get_string_pos(char *text, const char *search_string)
{
    char *pos;
    pos = strstr(text, search_string);
    return pos - text;
}

void tilemap_draw(SDL_Texture *tileset, int tilemap_layer_index)
{
    int soft_scroll_x = (int) scroll_pos_x % TILE_SIZE;
    int map_pos_x = scroll_pos_x / TILE_SIZE;
    int *data = tilemap_layer_data[tilemap_layer_index] + map_pos_x;

    int mw = get_tilemap_width();
    int w = get_screen_width() / TILE_SIZE;
    int h = get_screen_height() / TILE_SIZE;

    for (int y = 0; y < h ; y++)
    {
        for (int x = 0; x < w + 1; x++)
        {
            int tile_id = *data;

            if (tile_id > 0)
            {
                int tile_source_x = tile_postab[ (tile_id - 1) * 2 + 0];
                int tile_source_y = tile_postab[ (tile_id - 1) * 2 + 1];

                draw_subimage_rect(tileset, (x * TILE_SIZE) - soft_scroll_x, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, tile_source_x, tile_source_y);
            }

            data++;
        }

        data += (mw - w);
    }
}

void get_tilemap_data(int mapdata_index, int tilemap_layer_index, const char *tilelayer_name)
{
    const char tmx_csv_starttag[] = "<data encoding=\"csv\">";
    const char tmx_csv_endtag[] = "</data>";
    char *csv_data;

    int layer_startpos = get_string_pos(level_data[mapdata_index], tilelayer_name);
    int tmx_csv_tag_len = strlen(tmx_csv_starttag);
    int tmx_csv_endtag_len = strlen(tmx_csv_endtag);
    int csv_start_pos = get_string_pos(level_data[mapdata_index] + layer_startpos, tmx_csv_starttag);
    int csv_end_pos = get_string_pos(level_data[mapdata_index] + layer_startpos, tmx_csv_endtag);
    int start_pos = csv_start_pos + layer_startpos + tmx_csv_tag_len + 1;

    char *ptr2 = level_data[mapdata_index] + csv_end_pos + layer_startpos;
    *ptr2 = 0;

    char *ptr = level_data[mapdata_index] + start_pos;
    printf("%s\n", ptr);

    while (*ptr != '\0')
    {
        if (*ptr == '\n') *ptr = ',';
        if (*ptr == '\r') *ptr = ' ';
        ptr++;
    }

    csv_data = strtok(level_data[mapdata_index] + start_pos, ",");
    int *tilemap = tilemap_layer_data[tilemap_layer_index];
    int tilemap_size = get_tilemap_width() * get_tilemap_height();

    for (int i = 0; i < tilemap_size; i++)
    {
        if (csv_data != NULL)
        {
            int tile_id = atoi(csv_data);
            *tilemap = tile_id;
            csv_data = strtok(NULL, ",");
        }
        else 
        {
            fprintf(stderr, "warning: TMX-CSV error at index %d.\n", i);
            break;
        }

        tilemap++;
    }
}