#ifndef _GFX_H
#define _GFX_H

#include <SDL2/SDL.h>
#include "sprite.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *backbuffer;
extern SDL_Texture *sprite_sheets[5];
extern SDL_Texture *tilesheets[5];
extern int game_scale;

bool init_window(void);
void destroy_window(void);
void cls(Uint8 red, Uint8 green, Uint8 blue);
void flip(void);
SDL_Texture* load_bmp(const char *filename);
void destroy_bmp(SDL_Texture *texture);
void draw_subimage_rect(SDL_Texture *texture, int x, int y, int width, int height, int source_x, int source_y);
void sprite_draw(Sprite *spr);

#endif
