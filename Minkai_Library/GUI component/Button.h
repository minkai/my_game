#ifndef BUTTON_H
#define BUTTON_H

//#include "Textbox.h"
#include "Image_Label.h"

//call set_normal_image() if default constructor called
class Button : public Image_Label
{
protected:
	//determines whether the button can be clicked
	bool enabled;
	//this variable is changed to true when left mouse button is clicked on the button
	bool clicked;

	void initialize_non_argument_dependent_member_variable()
	{
		enabled = true;
		clicked = false;
	}

	//overides the function in GUI_Component
	virtual void handle_events_for_left_mouse_released(twoDVector<int> mouse_position)
	{
		//If the mouse is over the button
		if (point_is_over(mouse_position.x, mouse_position.y))
		{
			//if the mouse was holding the button
			if (mouse_status == hold)
			{
				clicked = true;
			}
		}

		//calls the base class version (this must be called after the testing above
		GUI_Component::handle_events_for_left_mouse_released(mouse_position);
	}
public:
	//non-default constructor
	Button(My_SDL_System& sdl_system, GUI_PARA, string normal_image_file_location = "") : Image_Label(sdl_system, GUI_ARGU, normal_image_file_location)
	{
		initialize_non_argument_dependent_member_variable();

	} //end constructor
	
	~Button(){}

	/*void calls_destructor()
	{
		delete this;
	}
	*/
	//sends a signal that the button is clicked
    bool isClicked()
	{
		//if the button is clicked by the user
		if( clicked )
		{
			clicked = false;
			return true;
		}
		else
			return false;
	}

	void set_enable(bool para)
	{
		enabled = para;
	}

	virtual void show(My_SDL_System& sdl_system)
	{
		Image_Label::show(sdl_system);
		if (mouse_status == in or mouse_status == hold)
		{
			sdl_system.change_cursor("hand-pointer-icon2.bmp");
		}
	}
};



#endif