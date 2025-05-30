#ifndef _PLAYER_H
#define _PLAYER_H

#include <SDL2/SDL.h>

#include "main.h"
#include "sprite.h"

#define PLAYER_MAX_SHOTS 30

extern Sprite spr_player;
extern Sprite spr_player_shots[PLAYER_MAX_SHOTS];

void player_init();
void player_update(void);
void player_draw_sprites(void);

void player_init_shots();
void player_update_shots(void);
int player_get_shot(void);
void player_init_shot1(int i);

#endif
