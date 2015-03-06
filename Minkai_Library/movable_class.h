#ifndef MOVABLE_CLASS_H
#define MOVABLE_CLASS_H

#include "C:\Users\Minkai\Documents\Visual Studio 2008\Projects\Functions, struct and class (written by Minkai)\GUI component\Image_Label.h"
#include "math function.h"
#include "Timer.h"

class Movable_Class
{
protected:
	//current position. (it will be in the middle of the sprite
	twoDVector<long double> current_position;
	//the original position. Must be changed whenever the velocity changes
	twoDVector<long double> original_position;
	//the moving speed under normal condition in pixel/second
	int normal_moving_speed;
	//the velocity in pixel/second
	twoDVector<double> velocity;

	//the timer used to calculate position. It is started at the original postion.
	Timer moving_timer;

	//*functions*
	//this function is called before setting velocity
	void initialize_non_argument_dependent_member_variable()
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	void preset_velocity()
	{
		//update current_position to prevent error
		move();

		original_position.x = current_position.x;
		original_position.y = current_position.y;

		//restart moving_timer
		moving_timer.start();
	}
	void set_velocity(double xVel, double yVel)
	{
		preset_velocity();
		velocity.x = xVel;
		velocity.y = yVel;
	}

	//set the velocity in the direction toward a location
	template <class T>
	void set_velocity_toward(twoDVector<T> destination)
	{
		double dy = destination.y - current_position.y;
		double dx = destination.x - current_position.x;
		double distance_to_target = calculate_distance(current_position, destination);
		
		preset_velocity();		

		velocity.x = dx*(normal_moving_speed/distance_to_target);
		velocity.y = dy*(normal_moving_speed/distance_to_target);
	}
public:
	//constructor
	Movable_Class(int x_para, int y_para, int normal_moving_speed_para)
	{
		initialize_non_argument_dependent_member_variable();

		current_position.x = original_position.x = x_para;
		current_position.y = original_position.y = y_para;

		normal_moving_speed = normal_moving_speed_para;
	}
	Movable_Class(){}
	virtual ~Movable_Class(){}
	twoDVector<long double> get_position() const
	{
		return current_position;
	}
	long double get_Xposition() const
	{
		return current_position.x;
	}
	long double get_Yposition() const
	{
		return current_position.y;
	}
	double get_Xvelocity() const
	{
		return velocity.x;
	}
	double get_Yvelocity() const
	{
		return velocity.y;
	}
	//update current_position according to velocity and moving_timer
	void move()
	{
		if(moving_timer.is_started())
		{
			//formula: x = mt + c
			current_position.x = velocity.x * moving_timer.get_ticks_s() + original_position.x;
			current_position.y = velocity.y * moving_timer.get_ticks_s() + original_position.y;
		}
		/*
		message += "Xpos: ";
		message += convert_to_str( current_position.x );
		message += ". Ypos: ";
		message += convert_to_str( current_position.y );
		*/
	}
};
class Movable_Image : public Movable_Class, public Image
{
protected:
	//this timer determines whether the image will be shown
	Timer showing_timer;
public:
	//default constructor
	Movable_Image(int x_para = 0, int y_para = 0, int normal_moving_speed_para = 0, string image_file_location = "")
		: Movable_Class(x_para, y_para, normal_moving_speed_para), Image(image_file_location)
	{
	}
	void set_position(long double x_para, long double y_para)
	{
		current_position.x = x_para;
		current_position.y = y_para;
	}
	void set_moving_velocity(double xVel, double yVel)
	{
		 set_velocity(xVel, yVel);
	}
	template <class T>
	void set_moving_velocity_toward(twoDVector<T> destination)
	{
		//calculate the amount of time needed to reach target
		set_timer( int(calculate_distance(current_position, destination)/normal_moving_speed*1000) );

		set_velocity_toward( destination );
	}
	void set_normal_moving_speed(int para)
	{
		normal_moving_speed = para;
	}
	//set how long will the image appear (in milliseconds)
	void set_timer(int millisecond)
	{
		showing_timer.start( millisecond );
	}
	void perform_logic()
	{
		//if the showing timer is ringing
		if( showing_timer.is_ringing() )
		{
			showing_timer.stop();
			//stop moving
			set_velocity(0, 0);
			moving_timer.stop();
		}
		else
			move();
	}
	void show() const
	{
		if( image != NULL )
		{
			//if showing_timer has started and is not ringing
			if( showing_timer.is_started() && !showing_timer.is_ringing() )
			{
				const int IMAGE_X = static_cast<int>(current_position.x-image->w/2);
				const int IMAGE_Y = static_cast<int>(current_position.y-image->h/2);
				apply_surface( IMAGE_X, IMAGE_Y, image, screen );
			}
		}
	}
};
#endif