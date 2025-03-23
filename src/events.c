#include <stdbool.h>
#include <SDL2/SDL.h>

bool key_back;
bool key_left;
bool key_right;
bool key_up;
bool key_down;
bool key_fire1;
bool key_fire2;
bool window_closed;

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

void check_events()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                window_closed = true;
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
