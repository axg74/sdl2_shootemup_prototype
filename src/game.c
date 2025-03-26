#include "config.h"
#include "gfx.h"
#include "tilemap.h"
#include "delta_time.h"
#include "player.h"
#include "events.h"
#include "statemachine.h"
#include "game.h"
#include "file.h"

extern Gamestate current_game_state;

char *level_data[10];

void game_mainloop()
{
    bool is_running = true;

    player_init();
    tilemap_init();
    delta_time_init();

    tilemap_set_scroll_pos_x(0.0f);
    tilemap_set_scroll_speed_x(20.0f);

    current_game_state = STATE_PLAY;

    while(is_running)
    {
        game_update_events();
        handle_game_state();
        flip();
        if (key_back || window_closed) is_running = false;
    }
}

bool load_data()
{
    level_data[0] = load_textfile("gamedata/level1.tmx");
    if (level_data[0] == NULL)
    {
        return false;
    }

    printf("%s", level_data[0]);

    unload_textfile(level_data[0]);

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

    draw_bmp_text(get_spritesheet(0), 1, 1, 0, 504, "TEST TEXT OUTPUT");

    disable_backbuffer_rendering();
}

void game_update_events()
{
    delta_time_update();
    check_events();
}

void game_update()
{
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
    exit_app();
}

void scroll_level()
{
    float level_pos_x = tilemap_get_scroll_pos_x();
    level_pos_x += tilemap_get_scroll_speed_x() * get_delta_time();
    tilemap_set_scroll_pos_x(level_pos_x);
}
