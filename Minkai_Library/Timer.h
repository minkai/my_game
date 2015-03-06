#ifndef TIMER_H
#define TIMER_H

#include "SDL basic.h"
//The timer
class Timer
{
private:
	//The clock time when the timer started
	int startTicks;

	//The ticks stored when the timer was paused
	int pausedTicks;

	//determines the amount of time needed to pass after starting the timer before the timer will ring 
	//ringing_time is in milliseconds
	int ringing_time;

	//The timer status
	bool paused;
	bool started;
	bool alarm_is_set;

	//determines when the timer will ring after starting the timer
	//can only be called by start()
	//time is in milliseconds
	void set_ringing_time(int time)
	{
		ringing_time = time;
	}

public:
	//Initializes variables
	Timer();

	//The various clock actions
	//-1 ringing_time means the timer will not ring
	//receives the time until the timer will ring as an argument
	//if default argument is used, timer will not ring
	void start(int ringing_time_para = 0)
	{
		//Start the timer
		started = true;

		//Unpause the timer
		paused = false;

		if( ringing_time_para != 0)
		{
			alarm_is_set = true;
			set_ringing_time( ringing_time_para );
		}
		//Get the current clock time
		startTicks = SDL_GetTicks();
	}
	void stop();
	void stop_alarm()
	{
		alarm_is_set = false;
		ringing_time = 0;
	}
	void pause();
	void unpause();

	//Gets the timer's time in milliseconds
	int get_ticks() const
	{
		//If the timer is running
		if( started )
		{
			//If the timer is paused
			if( paused )
			{
				//Return the number of ticks when the timer was paused
				return pausedTicks;
			}
			else //if the timer is not paused
			{
				//Return the current time minus the start time
				return SDL_GetTicks() - startTicks;
			}
		}

		//If the timer isn't running
		return 0;
	}
	//Gets the timer's time in seconds
	double get_ticks_s() const
	{
		return static_cast<double>(get_ticks())/1000;
	}

	//Checks the status of the timer
	bool is_started() const;
	bool is_paused() const;
	bool is_ringing() const
	{
		if( started )
		{
			if( alarm_is_set and (ringing_time <= get_ticks()) )
				return true;
			else
				return false;
		}
		else
			return false;
	}//end function is_ringing()
};


#endif