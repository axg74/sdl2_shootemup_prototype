#include <stdbool.h>

#include "player.h"
#include "main.h"
#include "sprite.h"
#include "delta_time.h"
#include "gfx.h"

float player_shot_delay;
Sprite spr_player;
Sprite spr_player_shots[PLAYER_MAX_SHOTS];

void player_init_shots(SDL_Texture *texture)
{
    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        sprite_set_size(&spr_player_shots[i], 16, 7);
        sprite_set_source(&spr_player_shots[i], 48, 0);
        sprite_set_sprite_sheet(&spr_player_shots[i], texture);
        sprite_disable(&spr_player_shots[i]);
    }
 //    sprite_set_speed(&spr_player_shots[0], initial_speed, initial_speed);
}

int player_get_shot()
{
     for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
     {
         if (!sprite_is_enabled(&spr_player_shots[i]))
         {
             return i;
         }
     }

     return -1;
}

void player_init(SDL_Texture *texture)
{
    float initial_speed = 60.0f;

    sprite_set_pos(&spr_player, 24.0f, 64.0f);
    sprite_set_size(&spr_player, 24, 16);
    sprite_set_source(&spr_player, 48, 16);
    sprite_set_sprite_sheet(&spr_player, texture);
    sprite_set_speed(&spr_player, initial_speed, initial_speed);
    sprite_enable(&spr_player);

    player_init_shots(texture);
}

void player_update()
{
    float x = sprite_get_x(&spr_player);
    float y = sprite_get_y(&spr_player);
    int width = sprite_get_width(&spr_player);
    int height = sprite_get_height(&spr_player);

    int dir_x = 0;
    int dir_y = 0;

    if (key_left) dir_x = -1;
    if (key_right) dir_x = 1;
    if (key_up) dir_y= -1;
    if (key_down) dir_y= 1;

    x += dir_x * sprite_get_speed_x(&spr_player) * delta_time;
    y += dir_y * sprite_get_speed_y(&spr_player) * delta_time;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > GAME_WIDTH) x = GAME_WIDTH - width;
    if (y + height > GAME_HEIGHT) y = GAME_HEIGHT - height;

    sprite_set_pos(&spr_player, x, y);

    if (key_fire1 && player_shot_delay < 0)
    {
        int i = player_get_shot();
        if (i >= 0)
        {
            player_init_shot1(i);
            player_shot_delay = 4;
        }
    }

    player_shot_delay -= 40 * delta_time;
}

void player_init_shot1(int i)
{
    sprite_set_pos(&spr_player_shots[i], sprite_get_x(&spr_player) + 16, sprite_get_y(&spr_player) + 6);
    sprite_set_size(&spr_player_shots[i], 16, 7);
    sprite_set_source(&spr_player_shots[i], 48, 0);
    sprite_set_sprite_sheet(&spr_player_shots[i], sprite_sheets[0]);
    sprite_enable(&spr_player_shots[i]);
    sprite_set_speed(&spr_player_shots[i], 400, 0);
}

void player_update_shots()
{
    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (sprite_is_enabled(&spr_player_shots[i]))
        {
            float x = sprite_get_x(&spr_player_shots[i]);
            float y = sprite_get_y(&spr_player_shots[i]);
            x += sprite_get_speed_x(&spr_player_shots[i]) * delta_time;

            if (x > GAME_WIDTH)
            {
                sprite_disable(&spr_player_shots[i]);
                continue;
            }

            sprite_set_pos(&spr_player_shots[i], x, y);
        }
    }
}

void player_draw_sprites()
{
    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        if (sprite_is_enabled(&spr_player_shots[i]))
        {
            sprite_draw(&spr_player_shots[i]);
        }
    }

    sprite_draw(&spr_player_shots[0]);
    sprite_draw(&spr_player);
}
