#ifndef LABEL_H
#define LABEL_H

#include "GUI component.h"

class Text_Label: public GUI_Component
{
protected:
	string text_string;
	string font_file_location;
	int font_size;
	My_Color text_color;
	
	virtual void handle_events_for_key_pressed(){}
	virtual void handle_events_for_right_mouse_pressed(){}
	virtual void handle_events_for_right_mouse_released(){}

public:
	Text_Label(GUI_PARA, string text = "", string file_location_para = "", int size = 12) : GUI_Component(GUI_ARGU)
	{
		text_string = text;
		font_file_location = file_location_para;
		font_size = size;
		text_color.r = 0;
		text_color.g = 0;
		text_color.b = 0;
				
	}

	void set_text(string para)
	{
		text_string = para;
	}
	void set_text(double para)
	{
		set_text( convert_to_str(para) );
	}
	void addText(string str_para)
	{
		text_string += str_para;
	}
	void addText(double str_para)
	{
		addText( convert_to_str(str_para));
	}
	
	void set_font( string file_name, int size)
	{
		font_file_location = file_name;
		font_size = size;
	}
	void setTextColor( My_Color color_para)
	{
		text_color = color_para;
	}
	
	string get_text() const
	{
		return text_string;
	}
	
	virtual void show(My_SDL_System& sdl_system)
	{
		if (text_string != "" && font_file_location != "")
		{
			sdl_system.apply_text(position, text_string, font_file_location, font_size, text_color);
		}
	}
};

#endif