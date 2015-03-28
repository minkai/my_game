#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cstring>
#include <cmath>
#include <time.h>
#include <windows.h>
#include <list>
#include "SafeArray.h"
#include "Minkai_Table.h"
#include "GUI component/Image_Label.h"
using namespace std;

enum side
{
	//N= nothing
	N, O, X
};

SafeArray<side> get_all_mark_type()
{
	SafeArray<side> answer(2);
	answer[0] = O;
	answer[1] = X;

	return answer;
}

class Line_Area
{
public:
	//direction of the line area
	//0 for horizontal, 1 for vertical, 2 for backslash, 3 for foward slash
	int direction;
	//if horizontal, backslash or forward slash, store the left most position
	//if vertical, store the top position
	twoDVector<int> start_position;
	int length;

	//get the position in the line area that starts from p and move towards the other end by index
	twoDVector<int> get_position(int index)
	{
		twoDVector<int> current_position = start_position;

		if (direction == 0)
		{
			current_position.x += index;
		}
		else if (direction == 1)
		{
			current_position.y += index;
		}
		else if (direction == 2)
		{
			current_position.x += index;
			current_position.y += index;
		}
		else
		{
			current_position.x += index;
			current_position.y -= index;
		}

		return current_position;
	}
};

class Board
{
	//top left coordinate of this board;
	twoDVector<int> position;
	//width and height of each tile
	const int TILE_SIZE;
	Minkai_Table<side> tiles;
	map<side, string> mark_images;

	//the tile that has the mouse over it
	twoDVector<int> mouse_over_tile;
	twoDVector<int> tile_clicked;

	bool mouse_position_in_board(twoDVector<int> mouse_position)
	{	
		if(position.x <= mouse_position.x && mouse_position.x < position.x + get_width() &&
				position.y <= mouse_position.y && mouse_position.y < position.y + get_height())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	//constructor for class, intialize the tile and lines
	Board(My_SDL_System& sdl_system, twoDVector<int> dimension, string o_image_file, string x_image_file) :
		TILE_SIZE(50), tiles(dimension)
	{	
		position = twoDVector<int>(100, 20);

		mark_images[X] = x_image_file;
		mark_images[O] = o_image_file;
	
		mouse_over_tile = twoDVector<int>(-1, -1);
		tile_clicked = twoDVector<int>(-1, -1);
	}

	bool in_valid_range(twoDVector<int> p)
	{
		if( 0 <= p.y && p.y < tiles.get_rows() && 0 <= p.x && p.x < tiles.get_columns() )
			return true;
		else
			return false;
	}

	bool in_valid_range(Line_Area a)
	{
		twoDVector<int> current_position = a.start_position;
		for(int i = 0; i < a.length; i++)
		{
			if( in_valid_range(current_position) )
			{
				if(a.direction == 0)
				{
					current_position.x += 1;
				}
				else if(a.direction == 1)
				{
					current_position.y += 1;
				}
				else if(a.direction == 2)
				{
					current_position.x += 1;
					current_position.y += 1;
				}
				else
				{
					current_position.x += 1;
					current_position.y -= 1;
				}
			}
			else
			{
				return false;
			}
		}

		return true;
	}
	side get_mark_type(twoDVector<int> c)
	{
		if(in_valid_range(c))
		{
			return tiles[c];
		}
		else
		{
			throw "Error";
		}
	}
	
	void change_mark(twoDVector<int> p, side mark_type)
	{
		//if x and y are within valid range
		if( in_valid_range(p))
		{
			tiles[p] = mark_type;
		}
		else
		{
			throw "Error!";
		}
	}

	void reset()
	{
		for(int y = 0; y < tiles.get_rows(); y++)
		{
			for(int x = 0; x < tiles.get_columns(); x++)
			{
				tiles[twoDVector<int>(x, y)] = N;
			}
		}
	}
	int get_rows()
	{
		return tiles.get_rows();
	}
	int get_columns()
	{
		return tiles.get_columns();
	}
	int get_width()
	{
		return tiles.get_columns() * TILE_SIZE;
	}

	int get_height()
	{
		return tiles.get_rows() * TILE_SIZE;
	}
	
	twoDVector<int> find_empty_tile()
	{
		for(int x = 0; x < tiles.get_columns(); x++)
		{
			for(int y = 0; y < tiles.get_rows(); y++)
			{
				if(tiles.get_element(y, x) == N)
				{
					return twoDVector<int>(x, y);
				}
			}
		}

		return twoDVector<int>(-1, -1);
	}
	//Assume a is in valid range
	//return the number of each mark type in the line area, map must contain the keys for each mark type
	map<side, int> get_mark_count(Line_Area a)
	{
		map<side, int> t;
		SafeArray<side> all_mark_type = get_all_mark_type();
		
		for(int i = 0; i < all_mark_type.size(); i++)
		{
			t[all_mark_type[i]] = 0;
		}

		for(int i = 0; i < a.length; i++)
		{
			side s = tiles[a.get_position(i)];
			if( s != N )
			{
				t[s] += 1;
			}
		}
	}
	
	int get_mark_count(Line_Area a, side s)
	{
		int count = 0;
		for(int i = 0; i < a.length; i++)
		{
			side current_mark_type = tiles[a.get_position(i)];
			if( current_mark_type == s )
			{
				count += 1;
			}
		}

		return count;
	}
	bool has_another_mark_type(Line_Area a, side s)
	{
		for(int i = 0; i < a.length; i++)
		{
			side current_mark_type = tiles[a.get_position(i)];
			if( current_mark_type != s && current_mark_type != N )
			{
				return true;
			}
		}

		return false;
	}
	
	int get_num_mark_around(twoDVector<int> p, side side_para)
	{
		int answer = 0;

		for(int c_y = p.y - 1; c_y <= p.y + 1; c_y++)
		{
			for(int c_x = p.x - 1; c_x <= p.x + 1; c_x++)
			{
				twoDVector<int> current_position(c_x, c_y);
				
				if( in_valid_range(current_position) && 
					current_position != p && 
					tiles.get_element(c_y, c_x) == side_para)
				{
					answer++;
				}
			}
		}

		return answer;
	}

	int get_num_mark_4_around(twoDVector<int> p, side side_para)
	{
		if (in_valid_range(p))
		{
			int answer = 0;
			SafeArray<twoDVector<int>> four_positions(4);
			four_positions[0] = twoDVector<int>(p.x, p.y - 1); //up
			four_positions[1] = twoDVector<int>(p.x, p.y + 1); //down
			four_positions[2] = twoDVector<int>(p.x - 1, p.y); //left
			four_positions[3] = twoDVector<int>(p.x + 1, p.y); //right

			for (int i = 0; i < four_positions.size(); i++)
			{
				if (in_valid_range(four_positions[i]) && tiles[four_positions[i]] == side_para)
					answer++;
			}

			return answer;
		}
		else
			throw "Error!";
	}

	//find an empty location in which the 8 tiles around has max marks
	pair<twoDVector<int>, int> find_max_mark_around(side mark_type_para)
	{
		pair<twoDVector<int>, int> answer;
		answer.first = twoDVector<int>(0, 0);
		answer.second = 0;

		for(int y = 0; y < tiles.get_rows(); y++)
		{
			for(int x = 0; x < tiles.get_columns(); x++)
			{
				twoDVector<int> current_position(x, y);
				if (tiles[current_position] == N)
				{
					int temp = get_num_mark_around(current_position, mark_type_para);
					if( answer.second < temp )
					{
						answer.second = temp;
						answer.first = current_position;
					}
				}
			}
		}//end outer for

		return answer;
	}

	//test whether the tile has 2 of color's mark around it that are opposite
	bool has_opposite_marks(twoDVector<int> p, side side_para)
	{
		bool answer = false;
		
		SafeArray<twoDVector<int>> a1(4);
		a1[0] = twoDVector<int>(p.x-1, p.y); //test left and right
		a1[1] = twoDVector<int>(p.x, p.y-1); //test up and down
		a1[2] = twoDVector<int>(p.x-1, p.y-1); //test upper left and lower right
		a1[3] = twoDVector<int>(p.x-1, p.y+1); //test upper right and lower left

		SafeArray<twoDVector<int>> a2(4);
		a2[0] = twoDVector<int>(p.x+1, p.y);
		a2[1] = twoDVector<int>(p.x, p.y+1);
		a2[2] = twoDVector<int>(p.x+1, p.y+1);
		a2[3] = twoDVector<int>(p.x+1, p.y-1);
		
		for(int i = 0; i < a1.size(); i++)
		{
			if(in_valid_range(a1[i]) && tiles[a1[i]] == side_para &&
				in_valid_range(a2[i]) && tiles[a2[i]] == side_para)
			{
				answer = true;
			}
		}

		return answer;
	}

	//return the position of the tile that is clicked
	//or (-1,-1) if there are none
	twoDVector<int> get_tile_clicked()
	{
		twoDVector<int> answer = tile_clicked;
		tile_clicked = twoDVector<int>(-1, -1);
		return answer;
	}
	
	void handle_events(My_SDL_System& sdl_system)
	{
		twoDVector<int> mouse = sdl_system.get_mouse_position();
		mouse_over_tile.x = floor( double((mouse.x - position.x)) / TILE_SIZE );
		mouse_over_tile.y = floor( double((mouse.y - position.y)) / TILE_SIZE );

		if (!in_valid_range(mouse_over_tile))
		{
			mouse_over_tile = twoDVector<int>(-1, -1);
		}

		//If a mouse button was released
		if (sdl_system.event_is_left_mouse_up())
		{
			tile_clicked = mouse_over_tile;
		}
	}

	void show(My_SDL_System& sdl_system)
	{
		My_Color LINE_COLOR(0, 0, 0);
		My_Color HIGHLIGHTED_COLOR(117, 225, 255);

		//show highlighted tile
		if (mouse_over_tile != twoDVector<int>(-1, -1))
		{
			twoDVector<int> highlighted_tile_position;

			highlighted_tile_position.x = position.x + mouse_over_tile.x * TILE_SIZE;
			highlighted_tile_position.y = position.y + mouse_over_tile.y * TILE_SIZE;
			sdl_system.draw_filled_box(highlighted_tile_position, twoDVector<int>(TILE_SIZE, TILE_SIZE), HIGHLIGHTED_COLOR);
		}

		for (int i = 0; i <= tiles.get_columns(); i++)
		{
			int temp = i * TILE_SIZE;
			//draw vertical line
			sdl_system.draw_line(twoDVector<int>(position.x + temp, position.y),
				twoDVector<int>(position.x + temp + 1, position.y + get_height()),
				LINE_COLOR);
		}

		for (int i = 0; i <= tiles.get_rows(); i++)
		{
			int temp = i * TILE_SIZE;
			//draw horizontal line
			sdl_system.draw_line(twoDVector<int>(position.x, position.y + temp),
				twoDVector<int>(position.x + get_width(), position.y + temp + 1),
				LINE_COLOR);
		}
		sdl_system.draw_filled_box(twoDVector<int>(position.x + get_width(), position.y + get_height()), twoDVector<int>(1, 1), LINE_COLOR);
		//draw marks
		for (int y = 0; y < tiles.get_rows(); y++)
		{
			for (int x = 0; x < tiles.get_columns(); x++)
			{
				twoDVector<int> mark_position;
				mark_position.x = position.x + x*TILE_SIZE;
				mark_position.y = position.y + y*TILE_SIZE;
				side mtype = tiles.get_element(y, x);
				if (mtype != N)
				{
					Image_Label label(sdl_system, mark_position.x, mark_position.y, mark_images[mtype]);
					label.show(sdl_system);
				}
			}
		}
	}

};

#endif