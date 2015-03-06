#ifndef POWERS_H
#define POWERS_H

#include "boardstat.h"

//holds the name and stars required
struct power_info
{
	const string name;
	const unsigned int stars_required;
	//determines whether the power can be used after placing token
	const bool after_placing;
	power_info(string name_para, unsigned int int_para, bool bool_para):
		name(name_para),stars_required(int_para), after_placing(bool_para)
	{
	}
};
//holds all the info about powers, only 1 object shall be created
class Powers
{
private:
	//This is a constant after initializing
	vector<power_info> list;
	//board that it is dealing with
	boardstat* target_board;
public:
	Powers(boardstat* board_para)
	{
		//put all information about the powers
		list.push_back( power_info("replace power", 1, true) );
		list.push_back( power_info("relocate power", 1, true) );
		list.push_back( power_info("reverse power", 2, false) );
		list.push_back( power_info("retaliate power", 2, false) );
		list.push_back( power_info("reject power", 2, true) );
		
		target_board = board_para;
	}
	string get_name(int num)
	{
		if( 0 <= num && num < list.size()-1)
		{
			return list[num]->name;
		}
		else
		{
			//error
		}
	}
	//test whether stars is sufficient to use a power, power_type starts from 1
	bool test_sufficient_stars(int num_stars, int power_type)
	{
		if( list[power_type-1]->stars_required <= num_stars)
			return true;
		else
			return false;
	}

	
	//color = user's color
	void replace_power(Player* player_ptr);
	void relocate_power1(Player* player_ptr);
	void relocate_power2(Player* player_ptr);
	//fromplayer = true if player is the one who call this function
	//player does not pass argument for x and y
	void reverse_power(Player* player_ptr, bool fromplayer, int y = 0, int x = 0);
	void retaliate_power(Player* player_ptr);
	void reject_power(Player* player_ptr);
};

//oy, ox = opponent's choice
void boardstat::replace_power(Player* player_ptr, int y, int x, int o_y, int o_x)
{
	side other_side;
	if(player_ptr->get_side() == O)
		other_side = X;
	else
		other_side = O;

	//decrease player's power
	player_ptr->change_stars( -1 );

	target_board->change_mark(y, x, player_ptr->get_side());
	target_board->change_mark(o_y, o_x, other_side); 
}
void boardstat::relocate_power1(Player* player_ptr)
{
	int x, y;
	int choice;
	side othercolor;

	//subtract a power from the user
	if(color == O)
		Opower -= 1;
	else if(color == X)
		Xpower -= 1;
	
	if(color == O)
		othercolor = X;
	else if(color == X)
		othercolor = O;
	
	
	testline(y, x, color, false, false);
	//remove mark from tile
	tile[y-1][x-1] = N;

	testline(y, x, color, true, false);
	tile[y-1][x-1] = color;
}

void boardstat::relocate_power2(Player* player_ptr)
{
	int x, y;
	int choice;
	side othercolor;

	//subtract a power from the user
	if(color == O)
		Opower -= 1;
	else if(color == X)
		Xpower -= 1;
	
	
	if(color == O)
		othercolor = X;
	else if(color == X)
		othercolor = O;

	testline(y, x, othercolor, false, false);
	tile[y-1][x-1] = color;
	testline(y, x, color, true, false); 

	//ask opponent to place token
	testline(y, x, othercolor, true, false);
	tile[y-1][x-1] = othercolor;
}
void boardstat::reverse_power(Player* player_ptr, int y, int x)
{
	//subtract 2 power from the user
	player_ptr->change_stars( -2 );

	if( 1 <= get_num_mark_around(y, x, player_ptr->get_side()) )
	{
		target_board->change_mark(y, x, player_ptr->get_side());
	}
	else
		throw "Error!";
}
void boardstat::retaliate_power(Player* player_ptr, int y1, int x1, int y2, int x2)
{
	//subtract 2 power from the user
	player_ptr->change_stars( -2 );

	if( 1 <= get_num_mark_4_around(y1, x1, player_ptr->get_side()) &&
		1 <= get_num_mark_4_around(y2, x2, player_ptr->get_side())
	  )
	{
		//remove the 2 marks
		target_board->change_mark(y1, x1, N);
		target_board->change_mark(y2, x2, N);
	}
	else
		throw "Error!";
}


//reject power: complete but untested
void boardstat::reject_power(Player* player_ptr)
{
	//set: Opower, Xpower, tile

	//coordinates for opponent's token
	int x, y;
	side othercolor;

	if(color == O)
		othercolor = X;
	else if(color == X)
		othercolor = O;

	//subtract 2 power from the user
	if(color == O)
		Opower -= 2;
	else if(color == X)
		Xpower -= 2;
	

	
	testline(y, x, othercolor, false, false);
	tile[y-1][x-1] = N;
}
#endif