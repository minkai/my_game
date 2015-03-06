#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "Textbox.h"

class Textarea : public Textbox
{
protected:
	//the maximum number of lines
	int max_size;
	
	
	/*
	vector<string> text_string;
	vector<SDL_Surface*> text_surface;
	*/

	//*functions*
	//make sures that text_surface is large enough 
	/*
	void regulate_text_surface()
	{
		if( text_surface.size() < text_string.size() )
		{
			//push back text_surface
			for(int count = 1; count <= (static_cast<int>(text_string.size())-text_surface.size()); count++)
			{
				text_surface.push_back( NULL );
			}
		}
	}
	*/
	
	/*
	bool is_within_range_of_text_string(int index)
	{
		if( 0 <= index and index <= static_cast<int>(text_string.size())-1 )
			return true;
		else
			return false;
	}
	bool is_within_range_of_text_surface(int index)
	{
		if( 0 <= index and index <= static_cast<int>(text_surface.size())-1 )
			return true;
		else
			return false;
	}
	*/
	void initialize_non_argument_dependent_member_variable()
	{
		max_size = 20;
		
	}
	virtual void handle_events_for_key_pressed()
	{
		//handle_events_to_recieve_text_input();
	}
	virtual void handle_events_for_left_mouse_pressed()
	{
		// if within textfield's box
		if( point_is_over(mouse_position.x, mouse_position.y) )
		{
			isSelected = true;
		}
		else //if it is outside the textfield's box
		{
			isSelected = false;
		}
	}
	virtual void handle_events_for_right_mouse_pressed(){}
	virtual void handle_events_for_left_mouse_released(){}
	virtual void handle_events_for_right_mouse_released(){}
public:
	
	

	virtual void show() const
	{
		//used to fill box for textfield
		SDL_Rect box = {position.x, position.y, width, height};
		//smaller box
		SDL_Rect smaller_box = {position.x+1, position.y+1, width-2, height-2};

		if( !isSelected )
		{
			//fill background
			SDL_FillRect(screen, &box, SDL_MapRGB(screen->format, backgroundColor.r, backgroundColor.g, backgroundColor.b));
		}
		else
		{
			//fill outerline
			SDL_FillRect(screen, &box, SDL_MapRGB(screen->format, 0, 0, 0));
			//fill background
			SDL_FillRect(screen, &smaller_box, SDL_MapRGB(screen->format, backgroundColor.r, backgroundColor.g, backgroundColor.b));
		}

		FOR_LOOP_VECTOR( component_list )
		{
			component_list[index]->show();
		}
	}

};
	
#endif