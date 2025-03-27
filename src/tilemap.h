#ifndef _TILEMAP_H
#define _TILEMAP_H

#include <stdbool.h>

void tilemap_init(void);
void tilemap_draw(SDL_Texture *tileset, int tilemap_layer_index);

float tilemap_get_scroll_pos_x(void);
float tilemap_get_scroll_pos_y(void);

void tilemap_set_scroll_pos_x(float x);
void tilemap_set_scroll_pos_y(float y);

float tilemap_get_scroll_speed_x(void);
float tilemap_get_scroll_speed_y(void);

void tilemap_set_scroll_speed_x(float x);
void tilemap_set_scroll_speed_y(float y);

void set_tilemap_width(int width);
void set_tilemap_height(int width);

int get_tilemap_width(void);
int get_tilemap_width(void);

bool alloc_tilemap(int tilemap_layer_index);
void free_tilemap(int tilemap_layer_index);

bool load_tmx_tilemap(const char *filename, int mapdata_index);
void unload_tmx_tilemap(int mapdata_index);
void unload_all_tmx_tilemaps(void);

void get_tilemap_data(int mapdata_index, int tilemap_layer_index, const char *tilelayer_name);
#endif


