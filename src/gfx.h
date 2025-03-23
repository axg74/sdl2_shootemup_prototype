#ifndef _GFX_H
#define _GFX_H

#include <SDL2/SDL.h>
#include "sprite.h"

extern SDL_Texture *sprite_sheets[5];
extern SDL_Texture *tilesheets[5];

bool init_window(int width, int height, int scale);
void destroy_window(void);
void cls(Uint8 red, Uint8 green, Uint8 blue);
void flip(void);
void enable_backbuffer_rendering(void);
void disable_backbuffer_rendering(void);
SDL_Texture* load_bmp(const char *filename);
void destroy_bmp(SDL_Texture *texture);
void draw_subimage_rect(SDL_Texture *texture, int x, int y, int width, int height, int source_x, int source_y);
void sprite_draw(Sprite *spr);

#endif
