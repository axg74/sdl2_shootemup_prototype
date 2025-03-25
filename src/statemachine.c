#include "statemachine.h"
#include "game.h"

Gamestate current_game_state = STATE_PLAY;

void handle_game_state()
{
    switch(current_game_state)
    {
        case STATE_TITLE_SCREEN:
            break;

        case STATE_PLAY:
            game_update();
            game_draw();
            break;
        
        case STATE_GAME_OVER:
            break;
        
        case STATE_OPTIONS_MENU:
            break;
    }
}
