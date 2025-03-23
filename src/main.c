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
void game_update(void);
void game_draw(void);
void game_mainloop(void);
void game_quit(void);

bool load_data(void);
void unload_data(void);

void scroll_level(void);

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

void game_mainloop()
{
    bool is_running = true;

    player_init();
    tilemap_init();
    delta_time_init();

    tilemap_set_scroll_pos_x(0.0f);
    tilemap_set_scroll_speed_x(20.0f);

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
    if (!load_spritesheet(0, "gamedata/spritesheet1.bmp"))
    {
        return false;
    }

    if (!load_tilesheet(0, "gamedata/tileset1.bmp"))
    {
        return false;
    }

    return true;
}

void unload_data()
{
    unload_spritesheet(0);
    unload_tilesheet(0);
}

void game_draw()
{
    enable_backbuffer_rendering();
    cls(0, 50, 0);

    tilemap_draw(get_tilesheet(0));

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
    scroll_level();
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

void scroll_level()
{
    float level_pos_x = tilemap_get_scroll_pos_x();
    level_pos_x += tilemap_get_scroll_speed_x() * get_delta_time();
    tilemap_set_scroll_pos_x(level_pos_x);
}