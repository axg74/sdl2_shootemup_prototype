#include "game.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    
    if (!game_init()) {
        game_quit();
        return -1;
    }

    if (!load_data())
    {
        game_quit();
        return -1;
    }

    game_mainloop();

    unload_data();
    game_quit();
    return 0;
}
