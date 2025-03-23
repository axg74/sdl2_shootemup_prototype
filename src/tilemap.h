#ifndef _TILEMAP_H
#define _TILEMAP_H

#define TILE_SIZE 16
#define MAX_TILES 512
#define TILESHEET_WIDTH 256
#define TILESHEET_HEIGHT 256

void tilemap_init(void);
void tilemap_draw(SDL_Texture *tileset);
void scroll_level_background();

float tilemap_get_scroll_pos_x(void);
float tilemap_get_scroll_pos_y(void);

void tilemap_set_scroll_pos_x(float x);
void tilemap_set_scroll_pos_y(float y);

float tilemap_get_scroll_speed_x(void);
float tilemap_get_scroll_speed_y(void);

void tilemap_set_scroll_speed_x(float x);
void tilemap_set_scroll_speed_y(float y);
#endif
