#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>

bool game_init(void);
void game_update(void);
void game_draw(void);
void game_update_events(void);
void game_mainloop(void);
void game_quit(void);

bool load_data(void);
void unload_data(void);

void scroll_level(void);

#endif
