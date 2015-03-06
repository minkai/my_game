#ifndef BOX_H
#define BOX_H

#include "twoDVector.h"

class Box
{
protected:
	//top left position;
	twoDVector<int> position;
	int width;
	int height;
	bool should_show;
public:
	//constructor
	Box(int x_para, int y_para, int width_para, int height_para, bool should_show_para = true)
	{
		position.x = x_para;
		position.y = y_para;

		width = width_para;
		height = height_para;

		should_show = should_show_para;
	}
	int get_left() const
	{
		return position.x;
	}
	int get_right() const
	{
		return position.x + width - 1;
	}
	int get_top() const
	{
		return position.y;
	}
	int get_bottom() const
	{
		return position.y + height - 1;
	}
	int get_width() const
	{
		return width;
	}
	int get_height() const
	{
		return height;
	}
};

class Selecting_Box : public Box
{
protected:
	bool mouse_dragged_and_released;
public:
	//constructor
	Selecting_Box(int x_para, int y_para, int width_para, int height_para) : Box(x_para, y_para, width_para, height_para, false)
	{
		mouse_dragged_and_released = false;
	}
	bool is_mouse_dragged_and_released()
	{
		if( mouse_dragged_and_released )
		{
			mouse_dragged_and_released = false;
			return true;
		}
		else
			return false;
	}
	void handle_events();
	void show();
};
#endif