#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "main.h"
#include "gfx.h"
#include "sprite.h"
#include "tilemap.h"
#include "delta_time.h"
#include "player.h"
#include "events.h"

bool game_init(void);
void game_quit(void);
void game_draw(void);
void game_update(void);
void game_mainloop(void);

bool load_data(void);
void unload_data(void);

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
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

void game_mainloop()
{
    bool is_running;

    player_init(sprite_sheets[0]);
    tilemap_init();
    delta_time_init();

    is_running = true;

    while(is_running)
    {
        game_update();
        game_draw();
        SDL_Delay(1);

        if (key_back || window_closed) is_running = false;
    }
}

bool load_data()
{
    sprite_sheets[0] = load_bmp("gamedata/spritesheet1.bmp");
    if (sprite_sheets[0] == NULL) return false;

    tilesheets[0] = load_bmp("gamedata/tileset1.bmp");
    if ( tilesheets[0] == NULL) return false;
    return true;
}

void unload_data()
{
    destroy_bmp(sprite_sheets[0]);
    destroy_bmp(tilesheets[0]);
}

void game_draw()
{
    enable_backbuffer_rendering();
    cls(0, 50, 0);

    tilemap_draw(tilesheets[0]);

    player_draw_sprites();
    disable_backbuffer_rendering();

    flip();
}

void game_update()
{
    delta_time_update();
    check_events();

    player_update();
    player_update_shots();
    scroll_level_background();
}

bool game_init()
{
    if (!init_window(GAME_WIDTH, GAME_HEIGHT, GAME_INITIAL_SCALE))
    {
        return false;
    }

    init_events();
    return true;
}

void game_quit()
{
    destroy_window();
    SDL_Quit();
}
