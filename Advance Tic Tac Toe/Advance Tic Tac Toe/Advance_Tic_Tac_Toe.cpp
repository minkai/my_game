//Advance Tic Tac Toe written by Minkai
//TO DO:
//          1. create a class for powers?
//          2. change power to star

//#include "powers.h"
//#include "player.h"
#include "Game_Session.h"
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cstring>
#include <cmath>

using namespace std;

enum power_choice
{
	replace, relocate, reverse, retaliate, reject
};

game_state run_title_screen(My_SDL_System& sdl_system)
{
	Image_Label ts(sdl_system, 210, 60, "title screen.jpg");
	Button start_single_player(sdl_system, 290, 250, "single_player_button.bmp");
	Button start_multiplayer(sdl_system, 290, 320, "multiplayer_button.bmp");

	game_state state_to_switch = title_screen;

	while (state_to_switch == title_screen)
	{
		while (sdl_system.poll_event())
		{
			if (sdl_system.event_is_quit())
			{
				state_to_switch = quit_game;
			}
			else
			{
				ts.handle_events(sdl_system);
				start_single_player.handle_events(sdl_system);
				start_multiplayer.handle_events(sdl_system);
			}
			
		}

		if (start_single_player.isClicked())
		{
			state_to_switch = battle_screen_single;
		}
		else if(start_multiplayer.isClicked())
		{
			state_to_switch = battle_screen_multi;
		}

		sdl_system.fill_screen(My_Color(0, 0, 0));
		sdl_system.change_cursor("");
		ts.show(sdl_system);
		start_single_player.show(sdl_system);
		start_multiplayer.show(sdl_system);

		sdl_system.update_screen();

		sdl_system.wait(10);
	}

	return state_to_switch;
}

game_state run_loading_screen(My_SDL_System& sdl_system)
{
	return battle_screen_single;
}

game_state run_battle_screen(My_SDL_System& sdl_system, bool single_player)
{
	Game_Session session(sdl_system, twoDVector<int>(6, 6), single_player);
	return session.run(sdl_system);
}

int main(int argc, char* args[])
{
	My_SDL_System sdl_system(900, 600, "Advance Tic Tac Toe");

	try
	{
		//Game_Session::test_count_line_area_with_mark(sdl_system);
		//sdl_system.test_draw_line();
		game_state state;
		state = run_title_screen(sdl_system);
		
		while (state != quit_game)
		{
			if (state == title_screen)
			{
				state = run_title_screen(sdl_system);
			}
			else if (state == loading_screen)
			{
				state = run_loading_screen(sdl_system);
			}
			else if (state == battle_screen_single)
			{
				state = run_battle_screen(sdl_system, true);
			}		
			else if (state == battle_screen_multi)
			{
				state = run_battle_screen(sdl_system, false);
			}
		} //end while user hasn't quit

	} //end try block
	catch (char* str)
	{
		return 1;
	}
	catch (string str)
	{
		return 1;
	}
	
	return 0;
}

/*
void DisplayInstructions()
{
//propasoal: Reinforce, place 3 token on tile that has 1 of own's token
//Reform, move up to 3 of own's token
<< "Advance Tic Tac Toe is a game of strategy. The rules are rather simple. "
<< "Within 8 x 8 tiles, each player take turns to place tokens until one of them have " << winline <<" lines of 4 tokens. \n\n"

<< "Each time a line is formed, the player gets a crystal which can be used to activate skills. "
<< "These skills are known as the 4R. Some skills don't allow you to place token at that turn. If it does, the token must be placed before the skill is used. Players won't get crystal by forming a line using skills. Here is the skills and their functions:" << endl
<< "Replace: Requires 1 crystal. Each player select one of the opponent's mark and the positions are swapped. \n\n"
<< "Relocate: Requires 1 crystal. Can be used on yourself or your opponent. "
<< "Use on yourself: Select one of your token and switch it to another location. "
<< "Use on your opponent: The user can't place token at that turn. The user selects one of the opponent's token and change it to his/her token. The opponent will then place a token. \n\n"
<< "Reject: Requires 2 crystal. The user removes 1 of opponent's mark that is between 2 of the player's mark.\n\n"
<< "Reverse: Requires 2 crystal. The user selects 1 of the opponent's mark that has a player's mark in any 8 adjecent tile and change it to his/her mark. The user can't place a mark at that turn.\n\n"
<< "Retaliate: Requires 2 crystal. The user selects 2 of the opponent's token that has a player's mark in an adjecent tile and remove them. The user can't place the token at that turn." << endl;

}*/