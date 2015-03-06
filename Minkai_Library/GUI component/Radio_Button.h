#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include <vector>
#include "Button.h"
#include "C:\Users\Minkai\Documents\Visual Studio 2008\Projects\Functions, struct and class (written by Minkai)\math function.h"
#include "C:\Users\Minkai\Documents\Visual Studio 2008\Projects\Functions, struct and class (written by Minkai)\twoDVector.h"
#include "C:\Users\Minkai\Documents\Visual Studio 2008\Projects\Functions, struct and class (written by Minkai)\for loop macro.h"
using std::vector;

//call set_normal_image() and set_selected_image() if default constructor called
class Radio_Button : public Button
{
protected:
	bool selected;
	//image used when radio button is selected(normal image is in Button)
	SDL_Surface* selected_image;
	void initialize_non_argument_dependent_member_variable()
	{
		selected = false;
		enabled = true;
		selected_image = NULL;
	}


public:
	//constructor
	Radio_Button(GUI_PARA, string normal_image_file_location = "", string selected_image_file_location = "") : Button(GUI_ARGU, normal_image_file_location) 
	{
		initialize_non_argument_dependent_member_variable();
		
		if( selected_image_file_location != "" )
		{
			set_selected_image(selected_image_file_location);
		}
	}
	//default constructor
	Radio_Button() : Button(){}
	//destructor
	~Radio_Button()
	{
		destroy_surface( selected_image );
	}
	void set_selected( bool para )
	{
		if( enabled )
		{
			selected = para;
		}
	}
	void set_selected_image(string image_file_location)
	{
		set_image_surface(selected_image, image_file_location);
	}
	bool isSelected() const
	{
		return selected;
	}
	virtual void show() const
	{
		//if the radio button is not selected
		if( !selected )
		{
			Image_Label::show();
		}
		else
		{
			if(selected_image == NULL)
				throw "Error!";
			else
				apply_surface( position.x, position.y, selected_image, screen);
		}
	}
};

//this class will create Radio buttons
//note: the class is designed so that all radio buttons will be deselected when the right mouse button is clicked
class Radio_Button_Group
{
private:
	//the pointers will be used to dynamically allocate memory
	vector<Radio_Button*> button_list;
public:
	Radio_Button_Group() : button_list(0)
	{
	}
	//destructor
	~Radio_Button_Group()
	{
		FOR_LOOP_VECTOR( button_list )
		{
			delete button_list[index];
		}
	}
	void create_radio_button(GUI_PARA, string normal_image_file_location, string selected_image_file_location)
	{
		button_list.push_back( new Radio_Button(GUI_ARGU, normal_image_file_location, selected_image_file_location) );
	}
	void set_selected_image(int index, string image_file_location)
	{
		//if index is within valid range
		if( 0 <= index && index <= static_cast<int>(button_list.size())-1)
			button_list[index]->set_selected_image( image_file_location );
		else
			throw "Error!";
	}
	void show()
	{
		FOR_LOOP_VECTOR( button_list )
		{
			button_list[index]->show();
		}
	}
};

#endif