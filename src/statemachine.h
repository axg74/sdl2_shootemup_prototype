#ifndef _STATEMACHINE_H
#define _SATTEMACHINE_H

typedef enum {
    STATE_TITLE_SCREEN,
    STATE_PLAY,
    STATE_GAME_OVER,
    STATE_OPTIONS_MENU
} Gamestate;

void handle_game_state();

#endif
