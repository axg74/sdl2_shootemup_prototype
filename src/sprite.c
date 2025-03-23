#include <stdbool.h>
#include "sprite.h"

void sprite_disable(Sprite *spr)
{
    spr->active = false;
}

void sprite_enable(Sprite *spr)
{
    spr->active = true;
}

bool sprite_is_enabled(Sprite *spr)
{
    return spr->active;
}

float sprite_get_x(const Sprite *spr)
{
    return spr->x;
}

float sprite_get_y(const Sprite *spr)
{
    return spr->y;
}

int sprite_get_width(const Sprite *spr)
{
    return spr->width;
}

int sprite_get_height(const Sprite *spr)
{
    return spr->height;
}

void sprite_set_pos(Sprite *spr,float x, float y)
{
    spr->x = x;
    spr->y = y;
}

void sprite_set_size(Sprite *spr, int width, int height)
{
    spr->width = width;
    spr->height = height;
}

void sprite_set_source(Sprite *spr, int source_x, int source_y)
{
    spr->source_x = source_x;
    spr->source_y = source_y;
}

void sprite_set_sprite_sheet(Sprite *spr, SDL_Texture *texture)
{
    spr->texture = texture;
}

float sprite_get_speed_x(Sprite *spr)
{
    return spr->speed_x;
}

float sprite_get_speed_y(Sprite *spr)
{
    return spr->speed_y;
}

void sprite_set_speed(Sprite *spr, float speed_x, float speed_y)
{
    spr->speed_x = speed_x;
    spr->speed_y = speed_y;
}
