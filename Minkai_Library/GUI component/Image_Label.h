#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include "GUI component.h"
#include <string>

using namespace std;
/*
class Image
{
protected:
	SDL_Surface* image;

	void initialize_non_argument_dependent_member_variable()
	{
		image = NULL;
	}
public:
	//constructor
	Image(string image_file_location = "")
	{
		initialize_non_argument_dependent_member_variable();

		if( image_file_location != "" )
			set_image(image_file_location);
	}
	~Image()
	{
		destroy_surface( image );
	}
	void set_image(string image_file_location)
	{
		set_image_surface(image, image_file_location);
	}
	int get_image_w() const
	{
		if(image != NULL)
			return image->w;
		else
			throw "Error!";
	}
	int get_image_h() const
	{
		if(image != NULL)
			return image->h;
		else
			throw "Error!";
	}

	void show_image(int x, int y) const
	{
		apply_surface( x, y, image, screen );
	}
};
*/
class Image_Label : public GUI_Component
{
protected:
	//the normal image that will be used for appearance
	string normal_image;
	string mouse_over_image;
	string mouseButton_down_image;

	//*functions*
	void initialize_non_argument_dependent_member_variable()
	{
		normal_image = "";
		mouseButton_down_image = "";
		mouse_over_image = "";
	}
	virtual void handle_events_for_key_pressed(){}
	virtual void handle_events_for_right_mouse_pressed(){}
	virtual void handle_events_for_right_mouse_released(){}
public:
	//constructor
	Image_Label(My_SDL_System& sdl_system, GUI_PARA, string normal_image_file_location = "") : GUI_Component(GUI_ARGU)
	{
		initialize_non_argument_dependent_member_variable();

		normal_image = normal_image_file_location;
		
		set_dimension(sdl_system.get_image_dimension(normal_image_file_location));
	}
	
	//destructor
	~Image_Label()
	{
	}
	void set_normal_image(string image_file_location)
	{
		normal_image = image_file_location;
	}

	void set_mouse_over_image(string image_file_location)
	{
		mouse_over_image = image_file_location;
	}

	void set_mouseButton_down_image(string image_file_location)
	{
		mouseButton_down_image = image_file_location;
	}

	//determine which image should be used
	string determine_image_using() const
	{
		//Chart:
		//holded = true, mouseIsOver = true, use holded
		//holded = true, mouseIsOver = false, error!!!
		//holded = false, mouseIsOver = true, use mouseIsOver
		//holded = false, mouseIsOver = false, use normal

		string image_using = "";

		//if button is holded
		if( mouse_status == hold )
		{
			if(mouseButton_down_image != "")
			{
				image_using = mouseButton_down_image;
			}
			else if(normal_image != "")
			{
				image_using = normal_image;
			}
		}
		//if button is not holded
		else
		{
			if( mouse_status == in )
			{
				if(mouse_over_image != "")
				{
					image_using = mouse_over_image;
				}
				else if(normal_image != "")
				{
					image_using = normal_image;
				}
			}
			else
			{
				if(normal_image != "")
				{
					image_using = normal_image;
				}
			}
		}

		return image_using;
	}

	//overrides the pure virtual function
	virtual void show(My_SDL_System& s)
	{
		//make sure that there's a normal image
		if( normal_image == "" )
			throw "Error!";

		string temp = determine_image_using();

		if( temp == "" )
		{
			temp = normal_image;
		}

		//display using the correct image
		s.apply_surface( position, temp);
	}
	
};

#endif