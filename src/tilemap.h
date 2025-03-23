#ifndef _TILEMAP_H
#define _TILEMAP_H

#define TILE_SIZE 16
#define MAX_TILES 512
#define TILESHEET_WIDTH 256
#define TILESHEET_HEIGHT 256

extern float scroll_pos_x;
extern float scroll_speed_x;

void calc_tilepos_tab(void);
void tilemap_draw(SDL_Texture *tileset);
void scroll_level_background();

#endif
