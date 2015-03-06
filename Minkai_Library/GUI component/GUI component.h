#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include "SDL basic.h"
#include "math function.h"

//Improvement needed: handle events

//parameter list of the constructor of GUI_Component
#define GUI_PARA int x_para = 0, int y_para = 0

//calls the constructor of GUI_Component. This is used by classes derived from GUI_Component
#define GUI_ARGU x_para, y_para

//status of the mouse relative to the GUI component
enum mouse_stat
{
	out, //mouse is outside the GUI component
	in, //mouse is inside the GUI component but not holding it with left mouse button
	hold //mouse is inside and holding with left mouse button
};

//the abstract base class of GUI components.
//TO DO: fix default constructor
//For this class and all other classes that inherits it, if default constructor is called, it must be initialized by creating a nameless object and assign to it
//then, if the class has SDL components, the appropriate function has to be called
class GUI_Component
{
protected:
	twoDVector<int> position;
	//boundary, minimum is 1
	twoDVector<int> dimension;
	mouse_stat mouse_status;

	//  **Functions**
	//TO DO: remove this and clean up constructor
	//this function can only be called by the non-default constructor. Although it is not virtual, it will be overriden.
	void initialize_non_argument_dependent_member_variable()
	{
		mouse_status = out;
	}
	
	//*these functions will only be called by handle_events() and the regualar virtual ones must be called if overriden.
	virtual void handle_events_for_key_pressed(){}
	virtual void handle_events_for_mouse_moved(twoDVector<int> mouse_position)
	{
		//If the mouse is over the GUI component
		if( point_is_over(mouse_position.x, mouse_position.y) )
		{
			if(mouse_status != hold)
			{
				mouse_status = in;
			}
		}
		else
		{
			mouse_status = out;
		}
	}
	virtual void handle_events_for_left_mouse_pressed(twoDVector<int> mouse_position)
	{
		//If the mouse is over the button
		if( point_is_over(mouse_position.x, mouse_position.y) )
		{
			mouse_status = hold;
		}
	}
	virtual void handle_events_for_right_mouse_pressed(twoDVector<int> mouse_position){}
	virtual void handle_events_for_left_mouse_released(twoDVector<int> mouse_position)
	{
		//If the mouse is over the button
		if( point_is_over(mouse_position.x, mouse_position.y) )
		{
			mouse_status = in;
		}
		else //if the mouse is not over the button
		{
			mouse_status = out;
		}
	}
	virtual void handle_events_for_right_mouse_released(twoDVector<int> mouse_position){}
public:
	GUI_Component(GUI_PARA)
	{
		initialize_non_argument_dependent_member_variable();

		set_position(twoDVector<int>(x_para, y_para));
		set_dimension(twoDVector<int>(1, 1));
	}

	virtual void set_position(twoDVector<int> p)
	{
		position = p;
	}
	
	virtual void change_position(int dx_para, int dy_para)
	{
		position.x += dx_para;
		position.y += dy_para;
	}
	void set_dimension(twoDVector<int> d)
	{
		dimension = d;
	}
	//*get functions*
	int get_Xposition() const
	{
		return position.x;
	}
	int get_Yposition() const
	{
		return position.y;
	}
	unsigned int get_w() const
	{
		return dimension.x;
	}
	unsigned int get_h() const
	{
		return dimension.y;
	}
	int get_rightmost() const
	{
		return position.x + dimension.x - 1;
	}
	int get_bottommost() const
	{
		return position.y + dimension.y - 1;
	}
	//test whether the coordinates is over the component
	bool point_is_over(int point_x, int point_y) const
	{
		twoDVector<int> temp_vector = {point_x, point_y};
		
		//if mouse is over button
		if( point_is_in_box(temp_vector, position, dimension.x, dimension.y) )
		{
			return true;
		}
		else
			return false;
	}

	void handle_events(My_SDL_System& s)
	{
		//If a key was pressed
		if (s.event_is_keydown())
		{
			handle_events_for_key_pressed();
		}
		//If the mouse moved
		else if (s.event_is_mouse_motion())
		{
			handle_events_for_mouse_moved(s.get_mouse_position());
		}
		//If a mouse button was pressed
		else if (s.event_is_left_mouse_down())
		{
			handle_events_for_left_mouse_pressed(s.get_mouse_position());
		}
		else if (s.event_is_middle_mouse_down())
		{
		}
		else if (s.event_is_right_mouse_down())
		{
			handle_events_for_right_mouse_pressed(s.get_mouse_position());
		}
		else if (s.event_is_left_mouse_up())
		{
			handle_events_for_left_mouse_released(s.get_mouse_position());
		}
		else if (s.event_is_middle_mouse_up())
		{
		}
		else if (s.event_is_right_mouse_up())
		{
			handle_events_for_right_mouse_released(s.get_mouse_position());
		}
		
	}
	//pure virtual function
	virtual void show(My_SDL_System& sdl_system) = 0;
};
#endif