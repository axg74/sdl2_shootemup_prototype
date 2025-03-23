#ifndef _SPRITE_H
#define _SPRITE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct Sprite
{
    bool active;
    float x, y;
    int width, height;
    int source_x, source_y;
    SDL_Texture *texture;
    int dir_x, dir_y;
    float speed_x, speed_y;
} Sprite;

void sprite_disable(Sprite *spr);
void sprite_enable(Sprite *spr);
bool sprite_is_enabled(Sprite *spr);
float sprite_get_x(const Sprite *spr);
float sprite_get_y(const Sprite *spr);
int sprite_get_width(const Sprite *spr);
int sprite_get_height(const Sprite *spr);
void sprite_set_pos(Sprite *spr,float x, float y);
void sprite_set_size(Sprite *spr, int width, int height);
void sprite_set_source(Sprite *spr, int source_x, int source_y);
void sprite_set_sprite_sheet(Sprite *spr, SDL_Texture *texture);

float sprite_get_speed_x(Sprite *spr);
float sprite_get_speed_y(Sprite *spr);
void sprite_set_speed(Sprite *spr, float speed_x, float speed_y);

#endif

