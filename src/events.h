#ifndef _EVENTS_H
#define _EVENTS_H

#include <SDL2/SDL.h>

extern bool key_back;
extern bool key_left;
extern bool key_right;
extern bool key_up;
extern bool key_down;
extern bool key_fire1;
extern bool key_fire2;
extern bool window_closed;

void init_events(void);
void check_events(void);
void check_keys(SDL_KeyCode key_code, bool flag);

#endif
