#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "main.h"
#include "gfx.h"
#include "tilemap.h"

char window_title[] = "Game-2D SDL2";

SDL_Window *window;

SDL_Texture *sprite_sheets[5];
SDL_Texture *tilesheets[5];

bool is_running;
int game_scale;

float delta_time;
Uint32  delta_time_last;

bool key_back;
bool key_left;
bool key_right;
bool key_up;
bool key_down;
bool key_fire1;
bool key_fire2;

typedef struct Sprite
{
    bool active;
    float x, y;
    int width, height;
    int source_x, source_y;
    SDL_Texture *texture;
    int dir_x, dir_y;
    float speed_x, speed_y;
} Sprite;

bool init(void);
void quit(void);
void main_loop(void);

void check_events(void);
void check_keys(SDL_KeyCode key_code, bool flag);

bool load_data(void);
void unload_data(void);

void game_draw(void);
void game_update(void);

void delta_time_init(void);
void delta_time_update(void);

//void tilesheets(Sprite *spr);
void sprite_disable(Sprite *spr);
void sprite_enable(Sprite *spr);
bool sprite_is_enabled(Sprite *spr);
float sprite_get_x(const Sprite *spr);
float sprite_get_y(const Sprite *spr);
int sprite_get_width(const Sprite *spr);
int sprite_get_height(const Sprite *spr);
void sprite_set_pos(Sprite *spr,float x, float y);
void sprite_set_size(Sprite *spr, int width, int height);
void sprite_set_source(Sprite *spr, int source_x, int source_y);
void sprite_set_sprite_sheet(Sprite *spr, SDL_Texture *texture);

float sprite_get_speed_x(Sprite *spr);
float sprite_get_speed_y(Sprite *spr);
void sprite_set_speed(Sprite *spr, float speed_x, float speed_y);

void player_init(void);
void player_update(void);
void player_draw_sprites(void);

void player_init_shots(void);
void player_update_shots(void);
int player_get_shot(void);
void player_init_shot1(int i);

float player_shot_delay;
Sprite spr_player;
Sprite spr_player_shots[PLAYER_MAX_SHOTS];

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    if (!init()) {
        quit();
        return -1;
    }

    if (!load_data())
    {
        quit();
        return -1;
    }

    main_loop();

    unload_data();
    quit();
    return 0;
}

void main_loop()
{
    player_shot_delay = 0.0f;
    player_init();

    delta_time_init();

    scroll_pos_x = 0.0f;
    scroll_speed_x = 20.0f;

    while(is_running)
    {
        delta_time_update();

        check_events();
        if (key_back) is_running = false;

        game_update();
        game_draw();
        SDL_Delay(1);
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
    player_update();
    player_update_shots();
    scroll_level_background(delta_time);
}

void sprite_draw(Sprite *spr)
{
    SDL_Rect src, dest;

    if (spr->active)
    {
        src.x = spr->source_x;
        src.y = spr->source_y;
        src.w = spr->width;
        src.h = spr->height;

        dest.x = (int) spr->x;
        dest.y = (int) spr->y;
        dest.w = src.w;
        dest.h = src.h;

        SDL_RenderCopy(renderer, spr->texture, &src, &dest);
    }
}

SDL_Texture* load_bmp(const char *filename)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = SDL_LoadBMP(filename);
    if (surface == NULL) return NULL;

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        if (surface != NULL) SDL_FreeSurface(surface);
        return NULL;
    }

    if (surface != NULL) SDL_FreeSurface(surface);
    return texture;
}

void destroy_bmp(SDL_Texture *texture)
{
    if (texture != NULL) SDL_DestroyTexture(texture);
}

void check_events()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                is_running = false;
                break;

            case SDL_KEYDOWN:
                check_keys(event.key.keysym.sym, true);
                break;

            case SDL_KEYUP:
                check_keys(event.key.keysym.sym, false);
                break;
        }
    }
}

void check_keys(SDL_KeyCode key_code, bool flag)
{
    switch(key_code)
    {
        case SDLK_ESCAPE:
            key_back = flag;
            break;

        case SDLK_LEFT:
            key_left = flag;
            break;

        case SDLK_RIGHT:
            key_right = flag;
            break;

        case SDLK_UP:
            key_up = flag;
            break;

        case SDLK_DOWN:
            key_down = flag;
            break;

        case SDLK_d:
            key_fire1 = flag;
            break;

       case SDLK_f:
            key_fire2 = flag;
            break;

        default:
            break;
    }
}

bool init()
{
    is_running = true;
    game_scale = GAME_INITIAL_SCALE;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    window = SDL_CreateWindow(window_title,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GAME_WIDTH * game_scale,
                              GAME_HEIGHT * game_scale,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) return false;

    backbuffer = SDL_CreateTexture(renderer,
                                   SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET,
                                   GAME_WIDTH, GAME_HEIGHT);
    if (backbuffer == NULL) return false;

    calc_tilepos_tab();

    return true;
}

void quit()
{
    if(backbuffer != NULL) SDL_DestroyTexture(backbuffer);
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
}

void player_init_shots()
{
    for (int i = 0; i < PLAYER_MAX_SHOTS; i++)
    {
        sprite_set_size(&spr_player_shots[i], 16, 7);
        sprite_set_source(&spr_player_shots[i], 48, 0);
        sprite_set_sprite_sheet(&spr_player_shots[i], sprite_sheets[0]);
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

void player_init()
{
    float initial_speed = 60.0f;

    sprite_set_pos(&spr_player, 24.0f, 64.0f);
    sprite_set_size(&spr_player, 24, 16);
    sprite_set_source(&spr_player, 48, 16);
    sprite_set_sprite_sheet(&spr_player, sprite_sheets[0]);
    sprite_set_speed(&spr_player, initial_speed, initial_speed);
    sprite_enable(&spr_player);

    player_init_shots();
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

void sprite_disable(Sprite *spr)
{
    spr->active = false;
}

void sprite_enable(Sprite *spr)
{
    spr->active = true;
}

bool sprite_is_enabled(Sprite *spr)
{
    return spr->active;
}

float sprite_get_x(const Sprite *spr)
{
    return spr->x;
}

float sprite_get_y(const Sprite *spr)
{
    return spr->y;
}

int sprite_get_width(const Sprite *spr)
{
    return spr->width;
}

int sprite_get_height(const Sprite *spr)
{
    return spr->height;
}

void sprite_set_pos(Sprite *spr,float x, float y)
{
    spr->x = x;
    spr->y = y;
}

void sprite_set_size(Sprite *spr, int width, int height)
{
    spr->width = width;
    spr->height = height;
}

void sprite_set_source(Sprite *spr, int source_x, int source_y)
{
    spr->source_x = source_x;
    spr->source_y = source_y;
}

void sprite_set_sprite_sheet(Sprite *spr, SDL_Texture *texture)
{
    spr->texture = texture;
}

float sprite_get_speed_x(Sprite *spr)
{
    return spr->speed_x;
}

float sprite_get_speed_y(Sprite *spr)
{
    return spr->speed_y;
}

void sprite_set_speed(Sprite *spr, float speed_x, float speed_y)
{
    spr->speed_x = speed_x;
    spr->speed_y = speed_y;
}

void delta_time_init()
{
    delta_time_last = SDL_GetTicks();
}

void delta_time_update()
{
    Uint32 current_time = SDL_GetTicks();
    delta_time = (current_time - delta_time_last) / 1000.0f;
    delta_time_last = current_time;
}

