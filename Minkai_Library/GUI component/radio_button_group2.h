#ifndef RADIO_BUTTON_GROUP2_H
#define RADIO_BUTTON_GROUP2_H

#include <vector>
#include "Radio_Button.h"

using namespace std;

//this class will act as a group for already created radio buttons. 
//It will not be responsible for destorying the radio buttons
class Radio_Button_Group2
{
private:
	vector<Radio_Button*> button_list;
public:
	Radio_Button_Group2() : button_list(0)
	{
	}
	void add_radio_button(Radio_Button* para)
	{
		button_list.push_back( para );
	}
	Radio_Button* get_pointer_at(int index) const
	{
		//if index is within valid range
		if( 0 <= index && index <= static_cast<int>(button_list.size())-1)
			return button_list[index];
		else
			throw "Error!";
	}
	Radio_Button* get_selected_radio_button() const
	{
		FOR_LOOP_VECTOR( button_list )
		{
			if( const_cast<const Radio_Button* const>(button_list[index])->isSelected() )
			{
				return button_list[index];
			}
		}

		//if non of the radio buttons is selected
		return NULL;
	}
	void set_enable_for_all(bool para)
	{
		FOR_LOOP_VECTOR( button_list )
		{
			button_list[index]->set_enable( para );
		}
	}
	//test if a point is over any of the radio button
	bool point_is_over(int x, int y)
	{
		FOR_LOOP_VECTOR( button_list )
		{
			if(button_list[index]->point_is_over(x, y))
				return true;
		}

		return false;
	}
	//deselect all the radio buttons
	void deselect()
	{
		FOR_LOOP_VECTOR( button_list )
		{
			button_list[index]->set_selected( false );
		}
	}
	void handle_events()
	{
		FOR_LOOP_VECTOR( button_list )
		{
			button_list[index]->handle_events();
		}

		//if mouse button is pressed down
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get the mouse offsets
			unsigned int mouse_x = event.button.x;
			unsigned int mouse_y = event.button.y;

			//If the left mouse button was pressed
			if( event.button.button == SDL_BUTTON_LEFT  )
			{
				Radio_Button* temp_pointer = NULL;
				//find out if the mouse is over any of the radio button
				FOR_LOOP_VECTOR( button_list )
				{
					//if mouse is over the button
					if( button_list[index]->point_is_over(mouse_x, mouse_y) )
					{
						//select the button
						button_list[index]->set_selected( true );
						temp_pointer = button_list[index];
						break;
					}
				}
				
				//if the mouse is over any of the button
				if( temp_pointer != NULL )
				{
					//deselect the other radio buttons
					FOR_LOOP_VECTOR( button_list )
					{
						if( button_list[index] != temp_pointer )
						{
							button_list[index]->set_selected( false );
						}
					}
				}
			}
			else if( event.button.button == SDL_BUTTON_RIGHT  )
			{
				//deselect all radio buttons
				FOR_LOOP_VECTOR( button_list )
				{
					button_list[index]->set_selected( false );
					
				}//end for loop
			}
		}
		
	}//end function handle_events
	//*exactly the same as the one in Radio_Button_Group!!!*
	void show()
	{
		FOR_LOOP_VECTOR( button_list )
		{
			button_list[index]->show();
		}
	}


};

#endif