#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

enum master_type
{
	human, computer
};

class Player
{
private:
	master_type master;
	//number of lines formed by player
	int lines;
	//amount of stars
	int stars;

public:
	Player(master_type master_para = human)
	{
		lines = 0;
		stars = 0;
		master = master_para;
	}


	void set_master(master_type m)
	{
		master = m;
	}

	master_type get_master() const
	{
		return master;
	}

	int get_lines() const
	{
		return lines;
	}
	void change_stars(int v)
	{
		stars += v;
	}
	void add_line(int v)
	{
		lines += v;
		stars += v;
	}
	void subtract_line(int v)
	{
		if( 1 <= v )
		{
			lines -= v;
		}
		else
			throw "Error!";
	}
};

#endif
	