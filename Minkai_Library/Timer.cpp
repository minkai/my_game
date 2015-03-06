#include "Timer.h"
//constructor
Timer::Timer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	ringing_time = 0;
	paused = false;
	started = false;
	alarm_is_set = false;
}

//stop the timer
void Timer::stop()
{
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if( ( started == true ) && ( paused == false ) )
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	//If the timer is paused
	if( paused )
	{
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

bool Timer::is_started() const
{
	return started;
}

bool Timer::is_paused() const
{
	return paused;
}