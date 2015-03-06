//The dot that will move around on the screen
class Dot
{
private:
    //The X and Y offsets of the dot
    twoDVector<unsigned int> position;

    //The velocity of the dot (in pixel per second)
    twoDVector<double> veloctiy;

	//Timer for velocity.x and velocity.y
	Timer timer_for_x;
	Timer timer_for_y;

	void moveInX();
	void moveInY();

public:
    //Initializes the variables
    Dot(int, int, double, double);

    //Takes key presses and adjusts the dot's velocity
    void handle_input();

    //Moves the dot
    void move();
	void move2();
	
	//Shows the dot on the screen
    void show();
};

Dot::Dot(int x_para, int y_para, double xVel_para = 0, double yVel_para = 0)
{
    //Initialize the offsets
    position.x = x_para;
    position.y = y_para;

    //Initialize the velocity
    velocity.x = xVel_para;
    velocity.y = yVel_para;

	//Initialize timers
	timer_for_x.start();
	timer_for_y.start();

}

void Dot::handle_input()
{
	//If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
			/*
            case SDLK_UP: velocity.y -= atoi(y_vel_Textfield.getText().c_str()); break;
            case SDLK_DOWN: velocity.y += atoi(y_vel_Textfield.getText().c_str()); break;
			case SDLK_LEFT: velocity.x -= atoi(x_vel_Textfield.getText().c_str()); break;
            case SDLK_RIGHT: velocity.x += atoi(x_vel_Textfield.getText().c_str()); break;
			*/
			case SDLK_RETURN: //get value from textfield
			
				velocity.x = atoi(x_vel_Textfield.getText().c_str());
				velocity.y = atoi(y_vel_Textfield.getText().c_str());
				break;
        }
    }
	/*
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: velocity.y = 0; break;
            case SDLK_DOWN: velocity.y = 0; break;
            case SDLK_LEFT: velocity.x = 0; break;
            case SDLK_RIGHT: velocity.x = 0; break;
        }
    }
	*/
	

}

void Dot::move()
{
    //Move the dot left or right
    position.x += velocity.x;

    //If the dot went too far to the left or right
    if( ( position.x < 0 ) || ( position.x + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //move back
        position.x -= velocity.x;
    }

    //Move the dot up or down
    position.y += velocity.y;

    //If the dot went too far up or down
    if( ( position.y < 0 ) || ( position.y + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //move back
        position.y -= velocity.y;
    }
}

//check whether if time to move has reached
//may call moveInX() and moveInY()
void Dot::move2()
{
	if(velocity.x != 0)
	{
		//if time taken to move 1 pixel(1/velocity.x) has reached
		if( 1/velocity.x <= timer_for_x.get_ticks()/1000 )
		{
			moveInX();
			//restart timer
			timer_for_x.start();
		}
	}

	if(velocity.y != 0)
	{
		//if time taken to move 1 pixel(1/velocity.y) has reached
		if( 1/velocity.y <= timer_for_y.get_ticks()/1000 )
		{
			moveInY();
			//restart timer
			timer_for_y.start();
		}
	}
}
void Dot::moveInX()
{
	//if velocity.x is positive (moving to the right)
	if( 0 < velocity.x )
	{
		//if has not reached right wall
		if( position.x + DOT_WIDTH < SCREEN_WIDTH )
		{		
			//move to the right, taking the time passed multiply by velocity
			position.x += (timer_for_x.get_ticks()/1000)*velocity.x;
		}
	}
	//if velocity.x is negative (moving to the left)
	else if( velocity.x < 0)
	{
		//if has not reached left wall
		if( 0 < position.x ) 
		{
			//move to the left
			position.x += (timer_for_x.get_ticks()/1000)*velocity.x;
		}
	}
}
void Dot::moveInY()
{
	//if velocity.y is positive (moving down)
	if( 0 < velocity.y )
	{
		//if has not reached bottom wall
		if( position.y + DOT_HEIGHT < SCREEN_HEIGHT )
		{
			//move down
			position.y += (timer_for_y.get_ticks()/1000)*velocity.y;
		}
	}
	//if velocity.y is negative (moving up)
	else if( velocity.y < 0)
	{
		//if has not reached top wall
		if( 0 < position.y )	
		{
			//move up
			position.y += (timer_for_y.get_ticks()/1000)*velocity.y;
		}
	}
}
void Dot::show()
{
    //Show the dot
    apply_surface( position.x, position.y, dot, screen );
}
