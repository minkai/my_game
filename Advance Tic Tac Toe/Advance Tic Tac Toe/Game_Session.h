#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "convert to str.h"
#include "Minkai_Multiset.h"
#include "GUI component/Textbox.h"
#include "GUI component/Button.h"
#include "player.h"
#include <map>

enum game_state
{
	title_screen, loading_screen, battle_screen_single, battle_screen_multi, quit_game
};

class Game_Session
{
private:
	map<side, Player> players;
	side PLAYER1_ID;
	side PLAYER2_ID;
	//the player that is currently taking turn
	side current_player;
	
	twoDVector<int> last_move;
	bool game_ended = false;

	Board the_board;

	const int MARK_COUNT_FOR_LINE = 4;
	//number of lines required to win the game
	const int LINE_COUNT_FOR_WIN = 2;

	//count the number of line area that covers p and has at least m tiles with mark s
	//if no_other_mark, then the line area cannot have another mark_type
	int count_line_area_with_mark(twoDVector<int> p, side s, int m, bool no_other_mark)
	{
		int numlines = 0;
		Line_Area a;
		a.length = MARK_COUNT_FOR_LINE;

		for (a.direction = 0; a.direction <= 3; a.direction++)
		{
			a.start_position = twoDVector<int>(p.x - MARK_COUNT_FOR_LINE + 1, p.y);
			twoDVector<int> inc(1, 0);

			if (a.direction == 0) //test for horizontal (from left to right)
			{			
				a.start_position.y = p.y;
				inc.y = 0;
			}
			else if (a.direction == 2) //test for diagonal (upper left to lower right)
			{
				a.start_position.y = p.y - MARK_COUNT_FOR_LINE + 1;
				inc.y = 1;
			}
			else if (a.direction == 3) //test for diagonal (lower left to upper right)
			{
				a.start_position.y = p.y + MARK_COUNT_FOR_LINE - 1;
				inc.y = -1;
			}
			else
			{
				a.start_position.x = p.x;
				a.start_position.y = p.y - MARK_COUNT_FOR_LINE + 1;
				inc.x = 0;
				inc.y = 1;
			}

			//loop through the line areas until starting position has passed (x, y)
			while (a.start_position.x < p.x + 1 && a.start_position != twoDVector<int>(p.x, p.y + 1))
			{
				if (the_board.in_valid_range(a))
				{
					if (m <= the_board.get_mark_count(a, s))
					{
						if (!no_other_mark || !the_board.has_another_mark_type(a, s))
						{
							numlines++;
						}
					}
				}
				a.start_position += inc;
			}
		}//end for loop for direction

		return numlines;
	}

	//find an empty location in which get_num_potential_line returns the highest number
	pair<twoDVector<int>, int> find_max_potential_line(side color, int n)
	{
		pair<twoDVector<int>, int> answer;
		answer.first = twoDVector<int>(-1, -1);
		answer.second = -1;

		for(int y = 0; y < the_board.get_rows(); y++)
		{
			for(int x = 0; x < the_board.get_columns(); x++)
			{
				twoDVector<int> current_p(x, y);
				//if this tile is empty
				if (the_board.get_mark_type(current_p) == N)
				{
					int temp = count_line_area_with_mark(current_p, color, n, true);
					if( answer.second < temp )
					{
						answer.second = temp;
						answer.first = current_p;
					}
				}
			}
		}

		return answer;
	}
	
	twoDVector<int> think(side AI_side)
	{
		//suggestion: create test to detect human player with 2 marks with empty space at both end

		//x and y coordinate of the mark that the computer player will place
		pair<twoDVector<int>, int> result;		

		side opponent_side;
		if (AI_side == O)
			opponent_side = X;
		else
			opponent_side = O;
		/*
		if(color == O)
		{	othercolor = X;
		playerline = Xline;
		}
		else if(color == X)
		{
		othercolor = O;
		playerline = Oline;
		}

		//if comp has 2 or more power and human player is one line away from winning
		if((color == O && 2 <= Opower && Xline == winline-1) || (color == X && 2 <= Xpower && Oline == winline-1))
		{
		//Using Reverse power
		for(int count1 = 1; count1 <= 8 && x == 0; count1++)
		{
		for(int count2 = 1; count2 <= 8 && x == 0; count2++)
		{
		if(tile[count1-1][count2-1] == othercolor && 2 <= get_num_line(count1, count2, othercolor) && 1 <= get_num_mark_around(count1, count2, color))
		{

		reverse_power(color, false, count1, count2);
		recentx = count2;
		recenty = count1;
		}
		}
		}
		}
		//if opponent has 3 marks in a row
		else if()
		{
		//Defense system:
		for(int count1 = 1; count1 <= 8 && (x == 0 || playerline == winline-1); count1++)
		{
		for(int count2 = 1; count2 <= 8 && (x == 0 || playerline == winline-1); count2++)
		{
		//calls get_num_line to count the number of lines that could be formed by opponent
		if(tile[count1-1][count2-1] == N && 1 <= get_num_line(count1, count2, othercolor))
		{

		x = count2;
		y = count1;
		}
		}
		}
		}
		//if there is a location that will form a line
		else if()
		{
		for(int count1 =1; count1 <= 8 && x == 0; count1++)
		{
		for(int count2 = 1; count2 <= 8 && x == 0; count2++)
		{
		//if this tile is empty and it can form at least one line
		if(tile[count1-1][count2-1] == N && 1 <= get_num_line(count1, count2, color))
		{

		x = count2;
		y = count1;
		}
		}
		}
		}
		else if()
		{
		//calls get_num_potential_line
		if(x == 0)
		{
		for (int count1 = 1; count1 <= 8; count1++)
		{
		for (int count2 = 1; count2 <= 8; count2++)
		{	if(tile[count1-1][count2-1] == N)
		{
		int potent = get_num_potential_line(count1, count2, color);
		if(maxpotent < potent)
		{
		maxpotent = potent;
		y = count1;
		x = count2;
		}
		else if(maxpotent == potent && potent != 0)
		{

		if(get_num_mark_around(y, x, color) < get_num_mark_around(count1, count2, color))
		{
		y = count1;
		x = count2;
		}
		}
		}
		}
		}

		}
		}
		else if()
		{
		//calls get_num_mark_around, search for a tile that has a maximum number of marks around
		if(x == 0)
		{
		for (int count1 = 1; count1 <= 8; count1++)
		{
		for (int count2 = 1; count2 <= 8; count2++)
		{
		num = get_num_mark_around(count1, count2, color);
		if(maxnum < num)
		{
		maxnum = num;
		y = count1;
		x = count2;
		}
		}
		}
		}
		}
		*/
		result = find_max_potential_line(AI_side, MARK_COUNT_FOR_LINE - 1);		
		if (LINE_COUNT_FOR_WIN <= players[AI_side].get_lines() + result.second)
		{
			return result.first;
		}

		result = find_max_potential_line(opponent_side, MARK_COUNT_FOR_LINE - 1);
		if (LINE_COUNT_FOR_WIN <= players[opponent_side].get_lines() + result.second)
		{
			return result.first;
		}

		result = find_max_potential_line(AI_side, MARK_COUNT_FOR_LINE - 1);
		if (1 <= result.second)
		{
			return result.first;
		}

		result = find_max_potential_line(AI_side, MARK_COUNT_FOR_LINE - 2);
		if (1 <= result.second)
		{
			return result.first;
		}

		//if can find a location that has at least one own mark around it
		result = the_board.find_max_mark_around(AI_side);
		if (1 <= result.second)
		{
			return result.first;
		}

		//give priority to the tiles in the center
		SafeArray<twoDVector<int>> center_tiles(4);
		center_tiles[0] = twoDVector<int>(floor(the_board.get_columns()/2), floor(the_board.get_rows()/2));
		center_tiles[1] = twoDVector<int>(floor(the_board.get_columns()/2), floor(the_board.get_rows()/2)-1);
		center_tiles[2] = twoDVector<int>(floor(the_board.get_columns()/2)-1, floor(the_board.get_rows()/2));
		center_tiles[3] = twoDVector<int>(floor(the_board.get_columns()/2)-1, floor(the_board.get_rows()/2)-1);

		for (int i = 0; i < center_tiles.size(); i++)
		{
			if (the_board.in_valid_range(center_tiles[i]) && the_board.get_mark_type(center_tiles[i]) == N)
			{
				return center_tiles[i];
			}
		}

		return the_board.find_empty_tile();

	}//end think()

	bool process_new_move()
	{
		if (!game_ended)
		{
			if (current_player != N)
			{
				twoDVector<int> tile_chosen = twoDVector<int>(-1, -1);
				if (players[current_player].get_master() == human)
				{
					twoDVector<int> tile_clicked = the_board.get_tile_clicked();
					if (tile_clicked != twoDVector<int>(-1, -1) && the_board.get_mark_type(tile_clicked) == N)
					{
						tile_chosen = tile_clicked;
					}
				}
				else
				{
					tile_chosen = think(current_player);
				}

				if (tile_chosen != twoDVector<int>(-1, -1))
				{
					last_move = tile_chosen;
					the_board.change_mark(tile_chosen, current_player);
					int lines_formed = count_line_area_with_mark(tile_chosen, current_player, MARK_COUNT_FOR_LINE, true);
					players[current_player].add_line(lines_formed);

					return true;
				}
			}
			else
			{
				throw "Error!";
			}
		}

		return false;
	}

	void show(My_SDL_System& sdl_system, Text_Label& game_over_message, Button& back_button, Textbox& reporter)
	{
		sdl_system.fill_screen(My_Color(79, 185, 242));
		sdl_system.change_cursor("");
		the_board.show(sdl_system);
		back_button.show(sdl_system);
		reporter.show(sdl_system);

		if (!game_ended)
		{
			if (LINE_COUNT_FOR_WIN <= players[PLAYER1_ID].get_lines())
			{
				game_ended = true;
				game_over_message.set_text("You win!");
			}
			else if (LINE_COUNT_FOR_WIN <= players[PLAYER2_ID].get_lines())
			{
				game_ended = true;
				game_over_message.set_text("You lose!");
			}
		}

		if (game_ended)
		{
			game_over_message.show(sdl_system);
		}
		sdl_system.update_screen();
	}

public:
	Game_Session(My_SDL_System& sdl_system, twoDVector<int> board_dimension, bool single_player) : the_board(sdl_system, board_dimension, "O.bmp", "X.bmp")
	{
		players[X] = Player(human);
		PLAYER1_ID = X;
		players[O] = Player(computer);
		PLAYER2_ID = O;
		
		if( !single_player )
		{
			players[O].set_master(human);
		}
		
		current_player = PLAYER1_ID;
		last_move = twoDVector<int>(-1, -1);
		game_ended = false;
	}

	game_state run(My_SDL_System& sdl_system)
	{
		Textbox reporter(500, 30, twoDVector<int>(380, 400), false, "Times.ttf", 24);
		reporter.setBackgroundColor(My_Color(206, 253, 160));
		reporter.setText(0, "Make " + convert_to_str(MARK_COUNT_FOR_LINE) + " marks in a row to form a line.");
		reporter.setText(1, "Make " + convert_to_str(LINE_COUNT_FOR_WIN) + " lines to win.");
		Text_Label game_over_message(250, 450, "You lose!", "Times.ttf", 72);
		Button back_button(sdl_system, 90, 520, "back_button.jpg");

		bool quit = false;
		bool switch_to_title_screen = false;

		while (!quit && !switch_to_title_screen)
		{
			while (sdl_system.poll_event())
			{
				if (sdl_system.event_is_quit())
				{
					quit = true;
				}
				else
				{
					the_board.handle_events(sdl_system);
					back_button.handle_events(sdl_system);
				}
			}

			bool should_switch_player = process_new_move();

			if (should_switch_player)
			{
				if (current_player == PLAYER1_ID)
					current_player = PLAYER2_ID;
				else
					current_player = PLAYER1_ID;

				should_switch_player = false;
			}

			if (back_button.isClicked())
			{
				switch_to_title_screen = true;
			}

			string temp1;
			if (current_player == PLAYER1_ID)
				temp1 = "player1";
			else
				temp1 = "player2";
			reporter.setText(2, "Last movement: x: " + convert_to_str(last_move.x) + "  y: " + convert_to_str(last_move.y));
			reporter.setText(3, "Player taking turn: " + temp1);
			reporter.setText(4, "Player 1 lines: " + to_string(players[PLAYER1_ID].get_lines()));
			reporter.setText(5, "Player 2 lines: " + to_string(players[PLAYER2_ID].get_lines()));
			
			show(sdl_system, game_over_message, back_button, reporter);

			sdl_system.wait(10);
		}

		if (quit)
		{
			return quit_game;
		}
		else
		{
			return title_screen;
		}
	}
	
	static void test_count_line_area_with_mark(My_SDL_System& sdl_system)
	{
		//expect 4 marks to form a line
		Game_Session the_game(sdl_system, twoDVector<int>(8, 8), true);
		list<twoDVector<int>> x_positions;
		x_positions.push_back( twoDVector<int>(2, 2) );
		x_positions.push_back( twoDVector<int>(3, 2) );
		x_positions.push_back( twoDVector<int>(4, 2) );

		for(list<twoDVector<int>>::iterator iter = x_positions.begin(); iter != x_positions.end(); iter++)
		{
			the_game.the_board.change_mark(*iter, X);
		}
		the_game.the_board.change_mark(twoDVector<int>(1, 2), O);

		list<int> expect0, expect1, expect2, expect3, expect4, expect5;
		expect0.push_back( the_game.count_line_area_with_mark(twoDVector<int>(2, 5), X, 3, true) );
		expect0.push_back( the_game.count_line_area_with_mark(twoDVector<int>(1, 2), X, 3, true) );
		expect1.push_back( the_game.count_line_area_with_mark(twoDVector<int>(2, 2), X, 3, true) );
		expect1.push_back( the_game.count_line_area_with_mark(twoDVector<int>(1, 2), X, 3, false) );
		expect2.push_back( the_game.count_line_area_with_mark(twoDVector<int>(2, 2), X, 3, false) );
		expect4.push_back( the_game.count_line_area_with_mark(twoDVector<int>(3, 2), X, 2, false) );

		the_game.the_board.reset();
		the_game.the_board.change_mark(twoDVector<int>(2, 1), X);
		the_game.the_board.change_mark(twoDVector<int>(2, 3), X);
		expect1.push_back( the_game.count_line_area_with_mark(twoDVector<int>(2, 0), X, 2, true) );
		expect2.push_back( the_game.count_line_area_with_mark(twoDVector<int>(2, 1), X, 2, true) );
		expect2.push_back( the_game.count_line_area_with_mark(twoDVector<int>(2, 2), X, 2, true) );

		the_game.the_board.change_mark(twoDVector<int>(3, 2), X);
		expect5.push_back( the_game.count_line_area_with_mark(twoDVector<int>(3, 2), X, 2, true) );
		the_game.the_board.change_mark(twoDVector<int>(4, 1), O);
		expect3.push_back( the_game.count_line_area_with_mark(twoDVector<int>(3, 2), X, 2, true) );

		twoDVector<int> blll = the_game.the_board.find_empty_tile();

	}
};

#endif