#ifndef _GFX_H
#define _GFX_H

#include <SDL2/SDL.h>
#include "sprite.h"

bool init_window(int width, int height, int scale);
void destroy_window(void);
void exit_app(void);

SDL_Texture* load_bmp(const char *filename);
void destroy_bmp(SDL_Texture *texture);

SDL_Texture* get_spritesheet(int index);
bool load_spritesheet(int index, const char *filename);
void unload_spritesheet(int index);

SDL_Texture* get_tilesheet(int index);
bool load_tilesheet(int index, const char *filename);
void unload_tilesheet(int index);

void cls(Uint8 red, Uint8 green, Uint8 blue);
void flip(void);
void enable_backbuffer_rendering(void);
void disable_backbuffer_rendering(void);

void draw_subimage_rect(SDL_Texture *texture, int x, int y, int width, int height, int source_x, int source_y);
void sprite_draw(Sprite *spr);

int get_screen_width(void);
int get_screen_height(void);
#endif
