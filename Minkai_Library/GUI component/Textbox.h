#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "SafeArray.h"
#include "Text_Label.h"

//TO DO: 1) remove Textarea, 2) add movable
class Textbox : public GUI_Component
{
protected:
	bool isSelected;
	bool editable;
	//used when editable is true
	//determine whether the textfield should receive digit and the period.
	bool receive_digit_input;
	bool receive_letter_input;
	bool receive_whiteSpace_input;
	//the vertical distance between one line of text and the next
	int vertical_distance;
	SafeArray<Text_Label> text_array;
	string font_file_location;
	int font_size;
	My_Color backgroundColor;
	/*
	void handle_events_to_recieve_text_input(string text_string)
	{
		//if the textfield is selected and editable
		if(isSelected and editable)
		{
			//If the key is a space
			if( event.key.keysym.unicode == (Uint16)' ' )
			{
				if(receive_whiteSpace_input)
				{
					//Append the character
					text_string += (char)event.key.keysym.unicode;
				}
			}
			//If the key is period
			else if( event.key.keysym.unicode == (Uint16)'.' )
			{
				if(receive_digit_input)
				{
					//Append the character
					text_string += (char)event.key.keysym.unicode;
				}
			}
			//If the key is a number
			else if( ( (Uint16)'0' <= event.key.keysym.unicode ) and ( event.key.keysym.unicode <= (Uint16)'9' ) )
			{
				if(receive_digit_input)
				{
					//Append the character
					text_string += (char)event.key.keysym.unicode;
				}
			} 
			//If the key is a lowercase letter
			else if( ( (Uint16)'a' <= event.key.keysym.unicode ) and ( event.key.keysym.unicode <= (Uint16)'z' ) )
			{
				if(receive_letter_input)
				{
					//Append the character
					text_string += (char)event.key.keysym.unicode;
				}
			}
			//If the key is a uppercase letter
			else if( ( (Uint16)'A' <= event.key.keysym.unicode ) and ( event.key.keysym.unicode <= (Uint16)'Z' ) )
			{
				if(receive_letter_input)
				{
					//Append the character
					text_string += (char)event.key.keysym.unicode;
				}
			} 
			//If backspace was pressed and the string isn't blank
			else if( ( event.key.keysym.sym == SDLK_BACKSPACE ) and ( text_string.length() != 0 ) )
			{
				//Remove a character from the end
				text_string.erase( text_string.length()-1 );
			}
		}
	}

	virtual void handle_events_for_key_pressed()
	{
		string temp = text_string;

		handle_events_to_recieve_text_input(text_string);

		
	}
	virtual void handle_events_for_left_mouse_pressed(twoDVector<int> mouse_position)
	{
		// if within textfield's box
		if (point_is_over(mouse_position.x, mouse_position.y))
		{
			isSelected = true;
		}
		else //if it is outside the textfield's box
		{
			isSelected = false;
		}
	}*/
public:
	//constructor
	Textbox(GUI_PARA, twoDVector<int> d= twoDVector<int>(10, 10), bool editable_para = true, string font_file_location_para = "", int font_size_para = 12) : GUI_Component(GUI_ARGU), text_array(20)
	{
		dimension = d;
		isSelected = false;
		editable = editable_para;
		receive_digit_input = true;
		receive_letter_input = true;
		receive_whiteSpace_input = true;
		vertical_distance = 30;
		font_file_location = font_file_location_para;
		font_size = font_size_para;
		setBackgroundColor(255, 255, 255);

		for (int i = 0; i < text_array.size(); i++)
		{
			text_array[i].set_position( twoDVector<int>(position.x + 5, position.y + 5 + vertical_distance*i) );
			text_array[i].set_font(font_file_location, font_size);
		}
		
	}
	
	//set text at a given row
	void setText(int index, string str)
	{
		//if index is in the correct range
		if (0 <= index and index < text_array.size())
		{
			text_array[index].set_text(str);
		}
		else
			throw "Error!";
	}

	string getText(int index)
	{
		//if index is in the correct range
		if (0 <= index and index < text_array.size())
		{
			return text_array[index].get_text();
		}
		else
			throw "Error!";
	}

	void setBackgroundColor( My_Color color_para)
	{
		backgroundColor = color_para;
	}
	void setBackgroundColor( int red, int green, int blue)
	{
		backgroundColor.r = red;
		backgroundColor.g = green;
		backgroundColor.b = blue;
	}
	
	//sets what kind of input should it receive
	void set_receiving_input(bool digit_para, bool letter_para, bool whiteSpace_para)
	{
		receive_digit_input = digit_para;
		receive_letter_input = letter_para;
		receive_whiteSpace_input = whiteSpace_para;
	}

	virtual void show(My_SDL_System& sdl_system)
	{
		twoDVector<int> smaller_box_position(position.x + 1, position.y + 1);
		twoDVector<int> smaller_box_dimension(dimension.x - 2, dimension.y - 2);
		/*if (!isSelected)
		{
			sdl_system.draw_filled_box(position, dimension, backgroundColor);
		}
		else //if select, draw a black border
		{
			*/sdl_system.draw_filled_box(position, dimension, My_Color(0, 0, 0));
			sdl_system.draw_filled_box(smaller_box_position, smaller_box_dimension, backgroundColor);
		//}

		for (int i = 0; i < text_array.size(); i++)
		{
			text_array[i].show(sdl_system);
		}
	}
};

#endif