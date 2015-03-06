#ifndef CIRCLE_H
#define CIRCLE_H

#include "twoDVector.h"
#include "draw.h"

class Circle
{
public:
	twoDVector<int> center;
	double radius;
	SDL_Color color;
	bool should_show;

	//constructor
	Circle(int x, int y, double radius_para)
	{
		center.x = x;
		center.y = y;

		radius = radius_para;

		color.r = 0;
		color.g = 0;
		color.b = 0;

		should_show = true;
	}
	void show()
	{
		if( should_show )
		{
			draw_circle( center, radius, color ); 
		}
	}
};

#endif