#ifndef SDL_BASIC_H
#define SDL_BASIC_H

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "convert to str.h"
#include "twoDVector.h"
#include "math function.h"
#include <set>
#include <map>
#include <cmath>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iso646.h>

using namespace std;

class My_Color
{
public:
	Uint8 r;
	Uint8 g;
	Uint8 b;

	My_Color(Uint8 r_para = 0, Uint8 g_para = 0, Uint8 b_para = 0)
	{
		r = r_para;
		g = g_para;
		b = b_para;
	}

	bool operator==(const My_Color& obj)
	{
		if( r == obj.r && g == obj.g && b == obj.b )
		{
			return true;
		}
		else
			return false;
	}
	bool operator!=(const My_Color& obj)
	{
		if( r == obj.r && g == obj.g && b == obj.b )
		{
			return false;
		}
		else
			return true;
	}
};

class My_SDL_System
{
private:
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Event event;

	//image for the cursor, if null, use normal cursor
	SDL_Surface* cursor = NULL;

	//cache the image
	//map<string, SDL_Surface*> image_cache;

	static void destroy_surface(SDL_Surface* &surface)
	{
		//Free surface
		SDL_FreeSurface(surface);
		surface = NULL;
	}

	static void destroy_font(TTF_Font* &f)
	{
		// close the font
		TTF_CloseFont(f);
		f = NULL;
	}
	
	SDL_Surface* set_image_surface(string image_file_location)
	{
		//The image that's loaded
		SDL_Surface* loadedSurface = NULL;
		SDL_Surface* optimizedSurface = NULL;
		string error = "";

		//Load the image
		loadedSurface = IMG_Load(image_file_location.c_str());

		//If the image loaded
		if (loadedSurface != NULL)
		{
			optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, NULL);
			if (optimizedSurface != NULL)
			{
				//Color key surface
				SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(optimizedSurface->format, 255, 255, 255));
			}
			else
			{
				error = "Error in function set_image_surface. ";
				error += SDL_GetError();
			}
			destroy_surface(loadedSurface);
		}
		else
		{
			error = "Error in function set_image_surface. ";
			error += SDL_GetError();
		}

		if(error != "")
		{
			throw error;
		}

		return optimizedSurface;
	}
	
	TTF_Font* set_TTF_Font(string font_file_location, int font_size)
	{
		const string ERROR_MESSAGE = "Error in function set_TTF_Font! " __FILE__ " ";
		TTF_Font* font;

		if (font_file_location != "")
		{
			//Open the font
			font = TTF_OpenFont(font_file_location.c_str(), font_size);

			//If there was an error in loading the font
			if (font == NULL)
			{
				throw ERROR_MESSAGE + " " + convert_to_str(__LINE__);
			}
		}
		else
		{
			throw ERROR_MESSAGE + " " + convert_to_str(__LINE__);
		}

		return font;

	}

	static SDL_Color convert_to_SDL_Color(My_Color c)
	{
		SDL_Color answer;
		answer.r = c.r;
		answer.g = c.g;
		answer.b = c.b;

		return answer;
	}
public:
	//initialize the SDL things
	My_SDL_System(int screen_width = 1000, int screen_height = 700, string window_title = "")
	{
		const string ERROR_MESSAGE = "Error in function init! " __FILE__ " ";

		//Initialize all SDL subsystems
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		{
			throw ERROR_MESSAGE + convert_to_str(__LINE__);
		}

		//Set up the screen
		window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);

		//If there was an error in setting up the screen
		if (window == NULL)
		{
			throw ERROR_MESSAGE + convert_to_str(__LINE__);
		}
		else
		{
			//Get window surface
			screen = SDL_GetWindowSurface(window);
		}

		cursor = NULL;

		int imgFlags = IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}

		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			throw ERROR_MESSAGE + convert_to_str(__LINE__);
		}

		SDL_StartTextInput();
	}
	
	~My_SDL_System()
	{
		destroy_surface(screen);
		destroy_surface(cursor);
		/*
		for (map<string, SDL_Surface*>::iterator iter = image_cache.begin(); iter != image_cache.end(); iter++)
		{
			destroy_surface(iter->second);
		}
		*/
		
		SDL_DestroyWindow(window);
		window = NULL;

		SDL_StopTextInput();

		//Quit SDL_ttf
		TTF_Quit();

		//Quit SDL
		SDL_Quit();
	}
	twoDVector<int> get_image_dimension(string image_file_location)
	{
		twoDVector<int> d;
		SDL_Surface* source = set_image_surface(image_file_location);
		d.x = source->w;
		d.y = source->h;
		destroy_surface(source);

		return d;
	}

	void fill_screen(My_Color c)
	{
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, c.r, c.g, c.b));
	}

	void draw_filled_box(twoDVector<int> position, twoDVector<int> dimension, My_Color c)
	{
		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.w = dimension.x;
		rect.h = dimension.y;
		SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, c.r, c.g, c.b));
	}

	void draw_horizontal_line(int x1, int x2, int y, const My_Color LINE_COLOR)
	{
		SDL_Rect temp = { x1, y, x2 - x1, 1 };
		SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
	}
	void draw_vertical_line(int x, int y1, int y2, const My_Color LINE_COLOR)
	{
		SDL_Rect temp = { x, y1, 1, y2 - y1 };
		SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
	}

	//draw a 45 degree digonal line starting from left
	void draw_diagonal_line(int x1, int y1, int y2, const My_Color LINE_COLOR)
	{
		int y_move = 1;
		if (y2 < y1)
		{
			y_move = -1;
		}

		for (int i = 0; i < abs(y2 - y1); i++)
		{
			SDL_Rect temp = { x1 + i, y1 + i*y_move, 1, 1 };
			SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
		}
	}

	void draw_line(twoDVector<int> endpoint1, twoDVector<int> endpoint2, const My_Color LINE_COLOR)
	{
		int dx = endpoint2.x - endpoint1.x;
		int dy = endpoint2.y - endpoint1.y;

		//start from the top
		int start_x = endpoint1.x;
		int start_y = endpoint1.y;
		int inc_x = 1;

		if (dx < 0)
		{
			inc_x = -1;
		}

		if (dy < 0)
		{
			twoDVector<int> reverse_endpoint1 = endpoint2;
			twoDVector<int> reverse_endpoint2 = endpoint1;

			if (dx < 0)
			{
				reverse_endpoint1.x += 1;
				reverse_endpoint2.x += 1;
			}
			else
			{
				reverse_endpoint1.x -= 1;
				reverse_endpoint2.x -= 1;
			}

			if (dy < 0)
			{
				reverse_endpoint1.y += 1;
				reverse_endpoint2.y += 1;
			}
			else
			{
				reverse_endpoint1.y -= 1;
				reverse_endpoint2.y -= 1;
			}

			start_x = reverse_endpoint1.x;
			start_y = reverse_endpoint1.y;
			inc_x = -inc_x;
		}

		int ry = 0;
		//for (int index = 0; index < y_list.size(); index++)
		for (int rx = 0; rx < abs(dx); rx++)
		{
			SDL_Rect temp = { start_x + inc_x*rx, start_y + ry, 1, abs(dy) - ry };

			//if this is not the last iteration
			if (rx != abs(dx) - 1)
			{
				int new_ry = ((rx + 1)*abs(dy)) / abs(dx);
				temp.h = 1;
				if (ry < new_ry)
				{
					temp.h = new_ry - ry;
				}

				ry = new_ry;
			}

			SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
		}
	}//end function draw_line

	void test_draw_line(twoDVector<int> ep1, twoDVector<int> ep2, set<twoDVector<int>> line_location)
	{
		const My_Color LINE_COLOR(255, 255, 255);
		My_Color actual_color;
		My_Color expected_color;
		
		fill_screen(My_Color(0, 0, 0));
		draw_line(ep1, ep2, LINE_COLOR);

		update_screen();

		SDL_LockSurface(screen);
		Uint32 *pixels = (Uint32 *)screen->pixels;
		for (int x = 0; x < screen->w; x++)
		{
			for (int y = 0; y < screen->h; y++)
			{
				SDL_GetRGB(pixels[(y * screen->w) + x], screen->format, &actual_color.r, &actual_color.g, &actual_color.b);
				if (line_location.find(twoDVector<int>(x, y)) != line_location.end())
				{
					expected_color = LINE_COLOR;
				}
				else
				{
					expected_color = My_Color(0, 0, 0);
				}

				if (actual_color != expected_color)
				{
					throw "Error at x: " + convert_to_str(x) + ", y: " + convert_to_str(y);
				}
			}
		}

		SDL_UnlockSurface(screen);
	}

	void test_draw_line()
	{
		for (int test_case = 1; test_case <= 7; test_case++)
		{
			twoDVector<int> ep1;
			twoDVector<int> ep2;
			set<twoDVector<int>> line_location;

			if (test_case == 1)
			{
				ep1 = twoDVector<int>(1, 1);
				ep2 = twoDVector<int>(5, 2);

				line_location.insert(twoDVector<int>(1, 1));
				line_location.insert(twoDVector<int>(2, 1));
				line_location.insert(twoDVector<int>(3, 1));
				line_location.insert(twoDVector<int>(4, 1));
			}
			else if (test_case == 2)
			{
				ep1 = twoDVector<int>(0, 0);
				ep2 = twoDVector<int>(4, -1);

				line_location.insert(twoDVector<int>(0, 0));
				line_location.insert(twoDVector<int>(1, 0));
				line_location.insert(twoDVector<int>(2, 0));
				line_location.insert(twoDVector<int>(3, 0));
			}
			else if (test_case == 3)
			{
				ep1 = twoDVector<int>(1, 1);
				ep2 = twoDVector<int>(2, 7);

				line_location.insert(twoDVector<int>(1, 1));
				line_location.insert(twoDVector<int>(1, 2));
				line_location.insert(twoDVector<int>(1, 3));
				line_location.insert(twoDVector<int>(1, 4));
				line_location.insert(twoDVector<int>(1, 5));
				line_location.insert(twoDVector<int>(1, 6));
			}
			else if (test_case == 4)
			{
				ep1 = twoDVector<int>(6, 2);
				ep2 = twoDVector<int>(0, 8);

				line_location.insert(twoDVector<int>(6, 2));
				line_location.insert(twoDVector<int>(5, 3));
				line_location.insert(twoDVector<int>(4, 4));
				line_location.insert(twoDVector<int>(3, 5));
				line_location.insert(twoDVector<int>(2, 6));
				line_location.insert(twoDVector<int>(1, 7));
			}
			else if (test_case == 5)
			{
				ep1 = twoDVector<int>(2, 2);
				ep2 = twoDVector<int>(10, 5);

				line_location.insert(twoDVector<int>(2, 2));
				line_location.insert(twoDVector<int>(3, 2));
				line_location.insert(twoDVector<int>(4, 2));
				line_location.insert(twoDVector<int>(5, 3));
				line_location.insert(twoDVector<int>(6, 3));
				line_location.insert(twoDVector<int>(7, 3));
				line_location.insert(twoDVector<int>(8, 4));
				line_location.insert(twoDVector<int>(9, 4));
			}
			else if (test_case == 6)
			{
				ep1 = twoDVector<int>(10, 10);
				ep2 = twoDVector<int>(20, 8);

				line_location.insert(twoDVector<int>(10, 10));
				line_location.insert(twoDVector<int>(11, 10));
				line_location.insert(twoDVector<int>(12, 10));
				line_location.insert(twoDVector<int>(13, 10));
				line_location.insert(twoDVector<int>(14, 10));
				line_location.insert(twoDVector<int>(15, 9));
				line_location.insert(twoDVector<int>(16, 9));
				line_location.insert(twoDVector<int>(17, 9));
				line_location.insert(twoDVector<int>(18, 9));
				line_location.insert(twoDVector<int>(19, 9));
			}
			else
			{
				ep1 = twoDVector<int>(11, 19);
				ep2 = twoDVector<int>(7, 4);

				line_location.insert(twoDVector<int>(8, 5));
				line_location.insert(twoDVector<int>(8, 6));
				line_location.insert(twoDVector<int>(8, 7));
				line_location.insert(twoDVector<int>(9, 8));
				line_location.insert(twoDVector<int>(9, 9));
				line_location.insert(twoDVector<int>(9, 10));
				line_location.insert(twoDVector<int>(9, 11));
				line_location.insert(twoDVector<int>(10, 12));
				line_location.insert(twoDVector<int>(10, 13));
				line_location.insert(twoDVector<int>(10, 14));
				line_location.insert(twoDVector<int>(10, 15));
				line_location.insert(twoDVector<int>(11, 16));
				line_location.insert(twoDVector<int>(11, 17));
				line_location.insert(twoDVector<int>(11, 18));
				line_location.insert(twoDVector<int>(11, 19));
			}
			
			test_draw_line(ep1, ep2, line_location);
		}

	}
	//changes the cursor to the image at file_location
	//if file_location is empty, change back to normal cursor
	void change_cursor(string file_location)
	{
		if (file_location == "")
		{		
			destroy_surface(cursor);
		}
		else
		{			
			cursor = set_image_surface(file_location);
		}
	}

	void apply_surface(twoDVector<int> position, string image_file_location)
	{
		SDL_Surface* source = set_image_surface(image_file_location);

		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;

		int returned_value = SDL_BlitSurface(source, NULL, screen, &rect);
		destroy_surface( source );
		
		if( returned_value < 0 )
		{
			throw SDL_GetError();
		}
	}
	
	void apply_text(twoDVector<int> position, string text, string font_file_location, int font_size, My_Color c)
	{
		string error = "";
		SDL_Surface* text_surface;
		TTF_Font* font = set_TTF_Font(font_file_location, font_size);
		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;

		if (font != NULL and !text.empty())
		{
			//Render a new text surface
			text_surface = TTF_RenderText_Solid(font, text.c_str(), convert_to_SDL_Color(c));
			if (text_surface != NULL)
			{
				int returned_value = SDL_BlitSurface(text_surface, NULL, screen, &rect);
				if (returned_value < 0)
				{
					error = "Error in function apply_text!";
					error += SDL_GetError();
				}
			}
			else
			{
				error = "Error in function apply_text!";
				error += SDL_GetError();
			}
		}
		else
		{
			error = "Error in function apply_text!";
		}

		destroy_surface(text_surface);
		destroy_font(font);

		if (error != "")
		{
			throw error;
		}
	}
	/*
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
	{
		//Holds offsets
		SDL_Rect offset;

		//Get offsets
		offset.x = x;
		offset.y = y;

		//Blit
		SDL_BlitSurface(source, clip, destination, &offset);
	}
	*/
	void wait(int milliseconds)
	{
		SDL_Delay(milliseconds);
	}

	void update_screen()
	{
		if(cursor == NULL)
		{
			SDL_ShowCursor(1);
		}
		else
		{
			SDL_ShowCursor(0);
			twoDVector<int> m = get_mouse_position();
			SDL_Rect rect;
			rect.x = m.x;
			rect.y = m.y;

			SDL_BlitSurface(cursor, NULL, screen, &rect);
		}

		SDL_UpdateWindowSurface(window);
	}

	int poll_event()
	{
		return SDL_PollEvent(&event);
	}

	bool event_is_keydown()
	{
		return event.type == SDL_KEYDOWN;
	}

	bool event_is_mouse_motion()
	{
		return event.type == SDL_MOUSEMOTION;
	}

	bool event_is_left_mouse_up()
	{
		return event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP;
	}

	bool event_is_middle_mouse_up()
	{
		return event.button.button == SDL_BUTTON_MIDDLE && event.type == SDL_MOUSEBUTTONUP;
	}

	bool event_is_right_mouse_up()
	{
		return event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONUP;
	}

	bool event_is_left_mouse_down()
	{
		return event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN;
	}

	bool event_is_middle_mouse_down()
	{
		return event.button.button == SDL_BUTTON_MIDDLE && event.type == SDL_MOUSEBUTTONDOWN;
	}

	bool event_is_right_mouse_down()
	{
		return event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONDOWN;
	}

	bool event_is_quit()
	{
		return event.type == SDL_QUIT;
	}
	twoDVector<int> get_mouse_position()
	{
		return twoDVector<int>(event.button.x, event.button.y);
	}
	
	char get_key_pressed()
	{
		string s = SDL_GetKeyName(event.key.keysym.sym);
		if (s.size() == 1)
		{
			return s[0];
		}
		else
		{
			throw "Error";
		}
	}
};
/*
extern SDL_Surface* screen;
extern SDL_Window* window;
extern SDL_Event event;
*/
//The screen attributes
//const int SCREEN_WIDTH = 1000;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP = 32;

/*
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
SDL_Surface *load_image( string filename );
void clean_up();
void destroy_font(TTF_Font* &font);
void set_TTF_Font( TTF_Font* &font, string file_name, int font_size);
void destroy_surface(SDL_Surface* &surface);
void set_text_surface(SDL_Surface* &text_surface, TTF_Font* font, const string text_str, const SDL_Color textColor);
void set_image_surface(SDL_Surface* &image_surface, string image_file_location);
*/
#endif