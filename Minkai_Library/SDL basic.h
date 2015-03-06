#ifndef SDL_BASIC_H
#define SDL_BASIC_H

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "convert to str.h"
#include "twoDVector.h"
#include "math function.h"
#include <vector>
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
	
	SDL_Surface* load_image(string filename)
	{
		//The image that's loaded
		SDL_Surface* loadedSurface = NULL;
		SDL_Surface* optimizedSurface = NULL;

		//Load the image
		loadedSurface = IMG_Load(filename.c_str());

		//If the image loaded
		if (loadedSurface != NULL)
		{
			optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, NULL); 
			if (optimizedSurface == NULL) 
			{ 
				throw "Error!";
			}
			destroy_surface(loadedSurface);

			//Color key surface
			SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(optimizedSurface->format, 255, 255, 255));
		}
		else
		{
			string s = "Error in function load_image. ";
			s += SDL_GetError();
			throw s;
		}

		return optimizedSurface;
	}

	SDL_Surface* set_image_surface(string image_file_location)
	{
		SDL_Surface* image_surface = NULL;
		
		image_surface = load_image(image_file_location);
		
		//If there was an problem loading the sprite map
		if (image_surface == NULL)
		{
			throw "Error in function set_image_surface!";
		}

		return image_surface;
	}
	
	void set_TTF_Font(TTF_Font* &font, string font_file_location, int font_size)
	{
		const string ERROR_MESSAGE = "Error in function set_TTF_Font! " __FILE__ " ";

		if (font_file_location != "")
		{
			//if font in not null
			if (font != NULL)
			{
				destroy_font(font);
			}

			//Open the font
			font = TTF_OpenFont(font_file_location.c_str(), font_size);

			//If there was an error in loading the font
			if (font == NULL)
			{
				throw ERROR_MESSAGE + " " + convert_to_str(__LINE__);
			}
		}
		else
			throw ERROR_MESSAGE + " " + convert_to_str(__LINE__);

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

		//Set the window caption
		//SDL_WM_SetCaption( str_para.c_str(), NULL );
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
		SDL_Rect temp = { x1, y, x2 + 1 - x1, 1 };
		SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
	}
	void draw_vertical_line(int x, int y1, int y2, const My_Color LINE_COLOR)
	{
		SDL_Rect temp = { x, y1, 1, y2 + 1 - y1 };
		SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
	}

	//draw a 45 degree digonal line starting from left
	void draw_diagonal_line(int x1, int y1, int y2, const My_Color LINE_COLOR)
	{
		if (y1 < y2)
		{
			for (int count = 1; count <= y2 - y1 + 1; count++)
			{
				SDL_Rect temp = { x1 + count - 1, y1 + count - 1, 1, 1 };
				SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
			}
		}
		else
		{
			for (int count = 1; count <= y1 - y2 + 1; count++)
			{
				SDL_Rect temp = { x1 + count - 1, y1 - count + 1, 1, 1 };
				SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));
			}
		}
	}
	void draw_line(twoDVector<int> endpoint1, twoDVector<int> endpoint2, const My_Color LINE_COLOR)
	{
		int dx = endpoint2.x - endpoint1.x;
		int dy = endpoint2.y - endpoint1.y;
		double gradient = static_cast<double>(dy) / dx;
		int x_pixel = abs(dx) + 1;
		int y_pixel = abs(dy) + 1;

		if (dy == 0)
		{
			draw_horizontal_line(endpoint1.x, endpoint2.x, endpoint1.y, LINE_COLOR);
		}
		else if (dx == 0)
		{
			draw_vertical_line(endpoint1.x, endpoint1.y, endpoint2.y, LINE_COLOR);
		}
		else if (gradient == 1 or gradient == -1)
		{
			draw_diagonal_line(endpoint1.x, endpoint1.y, endpoint2.y, LINE_COLOR);
		}
		//if the line is from lower left to upper right and closer to vertical line
		else if (gradient < -1)
		{
			vector<int> y_list(0);
			y_list = separate(y_pixel, x_pixel);

			int current_x = endpoint2.x;
			int current_y = endpoint2.y;

			//show the line from top right to lower left
			for (int index = 0; index <= x_pixel - 1; index++)
			{
				SDL_Rect temp = { current_x, current_y, 1, y_list[index] };
				SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));

				//if not the last one
				if (index != x_pixel - 1)
				{
					current_x--;
					current_y += y_list[index];
				}
			}
		}
		//if the line is from upper left to lower right and closer to vertical line
		else if (1 < gradient)
		{
			vector<int> y_list(0);
			y_list = separate(y_pixel, x_pixel);

			int current_x = endpoint2.x;
			int current_y = endpoint2.y + 1 - y_list[0];

			//show the line from bottom right to top left
			for (int index = 0; index <= x_pixel - 1; index++)
			{
				SDL_Rect temp = { current_x, current_y, 1, y_list[index] };
				SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));

				//if not the last one
				if (index != x_pixel - 1)
				{
					current_x--;
					current_y -= y_list[index + 1];
				}
			}//end for
		}
		//if the line is from lower left to upper right and closer to horizontal line
		else if (-1 < gradient and gradient < 0)
		{
			vector<int> x_list(0);
			x_list = separate(x_pixel, y_pixel);

			int current_x = endpoint2.x + 1 - x_list[0];
			int current_y = endpoint2.y;

			//show the line from top right to lower left
			for (int index = 0; index <= y_pixel - 1; index++)
			{
				SDL_Rect temp = { current_x, current_y, x_list[index], 1 };
				SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));

				//if not the last one
				if (index != y_pixel - 1)
				{
					current_x -= x_list[index + 1];
					current_y++;
				}
			}//end for
		}
		//if the line is from upper left to lower right and closer to horizontal line
		else
		{
			vector<int> x_list(0);
			x_list = separate(x_pixel, y_pixel);

			int current_x = endpoint2.x + 1 - x_list[0];
			int current_y = endpoint2.y;

			//show the line from top right to lower left
			for (int index = 0; index <= y_pixel - 1; index++)
			{
				SDL_Rect temp = { current_x, current_y, x_list[index], 1 };
				SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b));

				//if not the last one
				if (index != y_pixel - 1)
				{
					current_x -= x_list[index + 1];
					current_y--;
				}
			}//end for
		}

	}//end function draw_line
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

		try
		{
			SDL_BlitSurface(source, NULL, screen, &rect);
		}
		catch (...)
		{
			printf(SDL_GetError());
		}
	}
	
	void apply_text(twoDVector<int> position, string text, string font_file_location, int font_size, My_Color c)
	{
		string error = "";
		SDL_Surface* text_surface;
		TTF_Font* font = NULL;
		set_TTF_Font(font, font_file_location, font_size);
		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;

		if (font != NULL and !text.empty())
		{
			//Render a new text surface
			text_surface = TTF_RenderText_Solid(font, text.c_str(), convert_to_SDL_Color(c));
			if (text_surface != NULL)
			{
				SDL_BlitSurface(text_surface, NULL, screen, &rect);			
			}
			else
			{
				error = "Error in function set_text_surface!";
			}		
		}
		else
		{
			error = "Error in function set_text_surface!";
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