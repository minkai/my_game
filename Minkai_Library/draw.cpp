#include "draw.h"
#include "math function.h"
#include "SDL basic.h"

#define LINE_COLOR_RGB LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b
#define BOX_COLOR_RGB BOX_COLOR.r, BOX_COLOR.g, BOX_COLOR.b

void draw_pixel( twoDVector<int> position, const SDL_Color COLOR )
{
	SDL_Rect temp_rect = {position.x, position.y, 1, 1};
	SDL_FillRect(screen, & temp_rect, SDL_MapRGB(screen->format, COLOR.r, COLOR.g, COLOR.b));
}
void draw_box(int x, int y, int width, int height, const SDL_Color BOX_COLOR)
{
	//define the rects
	SDL_Rect left = {x, y, 1, height};
	SDL_Rect right = {x+width-1, y, 1, height};
	SDL_Rect top = {x, y, width, 1};
	SDL_Rect bottom = {x, y + height - 1, width, 1};

	Uint32 mapped_box_color = SDL_MapRGB(screen->format, BOX_COLOR_RGB);

	//draw the lines
	SDL_FillRect(screen, &left, mapped_box_color);
	SDL_FillRect(screen, &right, mapped_box_color);
	SDL_FillRect(screen, &top, mapped_box_color);
	SDL_FillRect(screen, &bottom, mapped_box_color);
}

void draw_box(const twoDVector<int> &coordinate1, const twoDVector<int> &coordinate2, const SDL_Color BOX_COLOR)
{
	twoDVector<int> top_left_coordinate = find_top_left(coordinate1, coordinate2);
	
	int width;
	int height;
	calculate_width_height(coordinate1, coordinate2, width, height);

	//draw the box
	draw_box(top_left_coordinate.x, top_left_coordinate.y, width, height, BOX_COLOR);
}
void draw_partial_box(int x, int y, int width, int height, int length_of_corner, const SDL_Color BOX_COLOR)
{
	int index_plus = 0;
	SDL_Rect* ptr[8];

	SDL_Rect left_up = {x, y, 1, length_of_corner};
	SDL_Rect left_down = {x, y+height-length_of_corner, 1, length_of_corner};
	SDL_Rect right_up = {x+width-1, y, 1, length_of_corner};
	SDL_Rect right_down = {x+width-1, y+height-length_of_corner, 1, length_of_corner};
	SDL_Rect top_left = {x, y, length_of_corner, 1};
	SDL_Rect top_right = {x+width-length_of_corner, y, length_of_corner, 1};
	SDL_Rect bottom_left = {x, y+height-1, length_of_corner, 1};
	SDL_Rect bottom_right = {x+width-length_of_corner, y+height-1, length_of_corner, 1};

	ptr[index_plus++] = &left_up;
	ptr[index_plus++] = &left_down;
	ptr[index_plus++] = &right_up;
	ptr[index_plus++] = &right_down;
	ptr[index_plus++] = &top_left;
	ptr[index_plus++] = &top_right;
	ptr[index_plus++] = &bottom_left;
	ptr[index_plus++] = &bottom_right;

	for(int index=0; index <= 7; index++)
	{
		SDL_FillRect(screen, ptr[index], SDL_MapRGB(screen->format, BOX_COLOR_RGB));
	}
}


void draw_circle( twoDVector<int> center, const double RADIUS, const SDL_Color COLOR )
{
	if( RADIUS <= 0 )
	{
		throw "Error!";
	}

	twoDVector<int> pixel_position;

	//use parametric equations, t goes from 0 to 2 pi
	for(double t = 0; t <= 6.283185; t += 3/RADIUS)
	{
		pixel_position.x = static_cast<int>(RADIUS*cos(t) + center.x);
		pixel_position.y = static_cast<int>(RADIUS*sin(t) + center.y);

		//display the pixel
		draw_pixel( pixel_position, COLOR );
	}
}
SDL_Color create_SDL_Color(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color temp = {r, g, b};
	return temp;
}
