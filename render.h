#pragma once
#include "catan.h"

void render_pieces(SDL_Renderer *renderer, mapInfo *map);
void render_map(SDL_Renderer *renderer, mapInfo *map);
void render_circle(SDL_Renderer *renderer, int x, int y, int rad, int r, int g, int b, int a);

