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
void main_loop(void);

bool load_data(void);
void unload_data(void);

void game_draw(void);
void game_update(void);

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

    main_loop();

    unload_data();
    game_quit();
    return 0;
}

void main_loop()
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
    SDL_SetRenderTarget(renderer, backbuffer);
    cls(0, 50, 0);

    tilemap_draw(tilesheets[0]);

    player_draw_sprites();


    SDL_SetRenderTarget(renderer, NULL);

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
    game_scale = GAME_INITIAL_SCALE;
    if (!init_window())
    {
        return false;
    }

    window_closed = false;
    return true;
}

void game_quit()
{
    destroy_window();
    SDL_Quit();
}
