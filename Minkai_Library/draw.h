#ifndef DRAW_H
#define DRAW_H

#include "SDL basic.h"
#include "twoDVector.h"



//prototype
void draw_pixel( twoDVector<int> position, const SDL_Color COLOR );
void draw_box(int x, int y, int width, int height, SDL_Color BOX_COLOR);
void draw_box(const twoDVector<int> &coordinate1, const twoDVector<int> &coordinate2, const SDL_Color BOX_COLOR);
void draw_partial_box(int x, int y, int width, int height, int length_of_corner, const SDL_Color BOX_COLOR);
void draw_circle( twoDVector<int> center, const double RADIUS, const SDL_Color COLOR ); 
SDL_Color create_SDL_Color(Uint8 r, Uint8 g, Uint8 b);

#endif