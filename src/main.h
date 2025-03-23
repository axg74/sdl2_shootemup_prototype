#ifndef _main_h
#define _main_h

#include <SDL2/SDL.h>
#include <stdbool.h>

#define GAME_WIDTH 320
#define GAME_HEIGHT 240
#define GAME_INITIAL_SCALE 3

extern SDL_Texture *sprite_sheets[5];
extern int game_scale;

extern bool key_back;
extern bool key_left;
extern bool key_right;
extern bool key_up;
extern bool key_down;
extern bool key_fire1;
extern bool key_fire2;
#endif
