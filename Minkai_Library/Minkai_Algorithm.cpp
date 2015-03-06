#include "Minkai_Algorithm.h"

//receives a string and check to see if every character is immediately followed by a different character
bool check_no_same_characters_together( string str )
{
	//the for loop will not iterate if the string has 1 or less characters
	//starts from the 2nd character
	for(int element = 2; element <= int(str.size()); element++)
	{
		//if the current element is equal to the previous element
		if( str[element-2] == str[element-1] )
		{
			return false;
		}

	}

	return true;

}

//receive a string and cut out the number on the right
//Note: not designed to get decimal numbers
string cut_right_number( string& str )
{
	string answer = "";

	if( !str.empty() )
	{
		//start from the last character
		int index = str.size()-1;

		//loop until pass the number from the right
		while( index != -1 && isdigit( str[index] ) )
		{
			index--;
		}

		//if index == -1, entire string are digits
		if(index == -1)
		{
			answer = str;
			str.clear();

			return answer;

		}
		//if first character from the right is not a digit
		else if( index == str.size()-1 )
		{
			//return empty string
			return answer;
		}
		else
		{
			//extract the right part that contains the digits
			answer = str.substr(index+1, str.size()-index-1);

			//erase that right part
			str.erase(index+1, str.size()-index-1);

			return answer;
		}
	}
	else //if str is empty
	{
		//return empty string
		return answer;
	}

}

string cut_left_number( string& str )
{
	string answer = "";

	if( !str.empty() )
	{
		int index = 0;

		//loop until pass the number from the left
		while( index != str.size() && isdigit( str[index] ) )
		{
			index++;
		}

		//if index == str.size(), entire string are digits
		if( index == str.size() )
		{
			answer = str;
			str.clear();

			return answer;

		}
		//if first character from the left is not a digit
		else if( index == 0 )
		{
			//return empty string
			return answer;
		}
		else
		{
			//extract the left part that contains the digits
			answer = str.substr(0, index);

			//erase that left part
			str.erase(0, index);

			return answer;
		}
	}
	else //if str is empty
	{
		//return empty string
		return answer;
	}

}