#include "SDL basic.h"
#include "Box.h"
#include "math function.h"
#include "draw.h"

void Selecting_Box::handle_events()
{
	static bool mouse_dragged = false;
	//original position of the mouse. This will be used if user is dragging the mouse
	static twoDVector<int> original_mouse_position;

	//If the mouse moved
	if( event.type == SDL_MOUSEMOTION )
	{
		//Get the mouse offsets
		twoDVector<int> current_mouse_position;
		current_mouse_position.x = event.button.x;
		current_mouse_position.y = event.button.y;

		//If the left mouse button was pressed
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			mouse_dragged = true;
			should_show = true;

			//adjust position
			position = find_top_left(current_mouse_position, original_mouse_position);

			//adjust dimension
			calculate_width_height(current_mouse_position, original_mouse_position, width, height);				 
		}
	}
	//if mouse button is pressed down
	else if( event.type == SDL_MOUSEBUTTONDOWN )
	{
		//Get the mouse offsets
		original_mouse_position.x = event.button.x;
		original_mouse_position.y = event.button.y;

	}
	//if mouse button is released
	else if( event.type == SDL_MOUSEBUTTONUP )
	{
		if( mouse_dragged )
		{
			mouse_dragged = false;
			should_show = false;
			mouse_dragged_and_released = true;
		}
	}
}//end function
void Selecting_Box::show()
{
	if(should_show)
	{
		//draw a box
		draw_box(position.x, position.y, width, height, create_SDL_Color(0, 0, 0));
	}
}