#ifndef PANEL_H
#define PANEL_H

#include "GUI component.h"
#include "for loop macro.h"
#include "draw.h"


//TO DO: remove open containers and use hash table/list for component_list
//Important: Classes that derive from Closed_Container(except for Opened_Container) must have destructors that destroy pointee in component_list
class Closed_Container : public GUI_Component
{
protected:
	//GUI components that it contains
	//For closed container, the pointers will dynamically allocate memory
	//For opened container, the pointers will point to objects already created
	vector<GUI_Component*> component_list;

	//move all of the containing components to a new position
	//recieves change in position of the panel as argument
	void move_components(int dx_para, int dy_para)
	{
		//move GUI components to a new location
		for(int index = 0; index <= static_cast<int>(component_list.size())-1; index++)
		{
			component_list[index]->change_position(dx_para, dy_para);
		}
	}
	virtual void handle_events_for_key_pressed() = 0;
	virtual void handle_events_for_right_mouse_pressed() = 0;
	virtual void handle_events_for_right_mouse_released() = 0;
public:
	//non-default constructor
	Closed_Container(GUI_PARA) : GUI_Component(GUI_ARGU)
	{
	}

	//default constructor
	Closed_Container(){}

	//TO DO: move move_componenets to set_position and remove change_position
	//overides the function
	virtual void set_position(int x_para, int y_para)
	{
		//call the overiden version to adjust the positions of the components
		change_position(x_para-position.x, y_para-position.y);
	}

	//overides the function
	virtual void change_position(int dx_para, int dy_para)
	{
		move_components(dx_para, dy_para);
		//change the position of the container
		GUI_Component::change_position(dx_para, dy_para);
	}

	//TO DO: show components as well
	virtual void show() const = 0;
	
};
class Opened_Container : public Closed_Container
{
protected:
	//adjust the positions of GUI component at the index, called by insert_components
	void adjust_position(int index)
	{
		component_list[index]->change_position( position.x, position.y );
	}
	virtual void handle_events_for_key_pressed() = 0;
	virtual void handle_events_for_right_mouse_pressed() = 0;
	virtual void handle_events_for_right_mouse_released() = 0;
public:
	//non-default constructor
	Opened_Container(GUI_PARA) : Closed_Container(GUI_ARGU){}
	//default constructor
	Opened_Container(){}

	void insert_components( GUI_Component* para )
	{
		component_list.push_back( para );
		adjust_position( static_cast<int>(component_list.size())-1 );
	}

	void insert_components( const vector<GUI_Component*> &list)
	{
		FOR_LOOP_VECTOR( list )
		{
			component_list.push_back( list[index] );
			adjust_position( static_cast<int>(component_list.size())-1 );
		}
	}

	vector<GUI_Component*> get_component_list() const
	{
		return component_list;
	}
};

//TO DO: 1) change this to use closed container 2) have an insert function for each GUI type, with parameters like position... etc
//Panel that contains other GUI components. 
//The position of the GUI components will be set relative to the Panel,
//then they would be added to the Panel where their position will be adjusted relative to the screen
//The Panel is not responsible for destroying the GUI components that it contains
//no function call required if default constructor called
class Panel : public Opened_Container
{
private:
	//color of the border
	SDL_Color border_color;
	SDL_Color background_color;

	//holds the original position of the mouse relative to the panel so that the user can drag the panel
	twoDVector<int> ori_mouse_position;
	
	//  **functions**
	void initialize_non_argument_dependent_member_variable()
	{
		//set the default border color to black
		border_color.r = 0;
		border_color.g = 0;
		border_color.b = 0;

		//set the default background color to white
		set_background_color(255, 255, 255);

		ori_mouse_position.x = 0;
		ori_mouse_position.y = 0;
	}
	void handle_events_for_key_pressed(){}
	void handle_events_for_mouse_moved()
	{
		//if the previous mouse status is hold
		if(mouse_status == hold)
		{
			//change the position of the panel and the components
			set_position(mouse_position.x - ori_mouse_position.x, mouse_position.y - ori_mouse_position.y);
		}

		GUI_Component::handle_events_for_mouse_moved();
	}
	void handle_events_for_left_mouse_pressed()
	{
		//If the mouse is over the component
		if( point_is_over(mouse_position.x, mouse_position.y) )
		{
			ori_mouse_position.x = mouse_position.x - position.x;
			ori_mouse_position.y = mouse_position.y - position.y;
		}

		GUI_Component::handle_events_for_left_mouse_pressed();
	}
	void handle_events_for_right_mouse_pressed(){}
	void handle_events_for_right_mouse_released(){}
public:
	//non-default constructor
	Panel(GUI_PARA) : Opened_Container(GUI_ARGU)
	{
		position.x;
		initialize_non_argument_dependent_member_variable();
	}
	//default constructor
	Panel(){}
	//destructor
	~Panel()
	{
		/*
		for(int index = 0; index <= static_cast<int>(component_list.size())-1; index++)
		{
			component_list[index]->calls_destructor();
		}
		*/
	}
	
	/*
	void calls_destructor()
	{
		delete this;
	}
	*/
	//returns the size of the GUI components it contains
	//*set functions*
	
	//this function automatically adjust the width and height of the panel
	void adjust_wh()
	{
		//holds the rightmost x-coordinate of the GUI components
		int max_x = 0;
		//holds the lowermost y-coordinate of the GUI components
		int max_y = 0;

		//holds the rightmost and lowermost of one component
		int rightmost = 0;
		int lowermost = 0;

		//search for max_x and max_y
		for(int count = 1; count <= static_cast<int>(component_list.size()); count++)
		{
			//get the rightmost coordinate of the component relative to the panel
			rightmost = component_list[count-1]->get_rightmost() - position.x;
			if( max_x < rightmost )
			{
				max_x = rightmost;
			}

			//get the lowermost coordinate of the component relative to the panel
			lowermost = component_list[count-1]->get_bottommost() - position.y;
			if( max_y < lowermost )
			{
				max_y = lowermost;
			}
		}

		width = max_x + 10;
		height = max_y + 10;
	}
	void set_background_color( Uint8 r, Uint8 g, Uint8 b )
	{
		background_color.r = r;
		background_color.g = g;
		background_color.b = b;
	}
	int get_size() const
	{
		return component_list.size();
	}
	/*
	void insert_Labels( vector<Label*> &list)
	{
		for(int index = 0; index <= list.size()-1; index++)
		{
			Label_list.push_back( list[index] );
		}
	}
	void insert_Textfields( vector<Textfield*> &list)
	{
		for(int index = 0; index <= list.size()-1; index++)
		{
			Textfield_list.push_back( list[index] );
		}
	}
	void insert_Buttons( vector<Button*> &list)
	{
		for(int index = 0; index <= list.size()-1; index++)
		{
			Button_list.push_back( list[index] );
		}
	}
	*/
	//show the Panel
	void show() const
	{
		//draw the box
		draw_box(position.x, position.y, width, height, border_color);

		//used to fill the box
		SDL_Rect box = {position.x, position.y, width, height};

		//fill background
		
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0xFF);

		}

		SDL_RenderFillRect(renderer, &box);

		SDL_DestroyRenderer(renderer);
		renderer = NULL;

		//SDL_FillRect(screen, &box, SDL_MapRGB(screen->format, background_color.r, background_color.g, background_color.b));
	}
	
};
#endif