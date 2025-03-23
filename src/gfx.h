#ifndef _GFX_H
#define _GFX_H

extern SDL_Renderer *renderer;
extern SDL_Texture *backbuffer;

void cls(Uint8 red, Uint8 green, Uint8 blue);
void flip(void);
SDL_Texture* load_bmp(const char *filename);
void destroy_bmp(SDL_Texture *texture);
void draw_subimage_rect(SDL_Texture *texture, int x, int y, int width, int height, int source_x, int source_y);

#endif
