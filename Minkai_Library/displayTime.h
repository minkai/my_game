#ifndef DISPLAY_TIME_H
#define DISPLAY_TIME_H

void displayTime(int seconds, TTF_Font *time_font, int x_para, int y_para, SDL_Color timeTextColor)
{
	SDL_Surface* time_surface;

	//The timer's time as a string
    stringstream time;

    //Convert the timer's time to a string
    time << seconds;

	//Render the time surface
    time_surface = TTF_RenderText_Solid( time_font, time.str().c_str(), timeTextColor );
	
	//If there was an error in rendering the text
	if( time_surface == NULL )
	{
	   throw "Error!";
	}

	//Apply the time surface
    apply_surface( x_para, y_para, time_surface, screen );

    //Free the time surface
    SDL_FreeSurface( time_surface );
}

#endif