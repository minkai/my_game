#include "math function.h"
//#include "Box.h"
//#include "Minkai_Algorithm.h"

//accept a string of a math equation and calculate the result
//complete only up to + and -
/*
double calculate_value(string str_para)
{
	//scan for ^
	for(int index = 0; index <= int(str_para.size())-1; index++)
	{
		if( str_para[index] == '^' )
		{
			calculate_value_operation(str_para, index);
		}
	}

	//scan for * and /
	for(int index = 0; index <= int(str_para.size())-1; index++)
	{
		if( str_para[index] == '*' || str_para[index] == '/' )
		{
			calculate_value_operation(str_para, index);
		}
	}

	//scan for + and -
	for(int index = 0; index <= int(str_para.size())-1; index++)
	{

		if( str_para[index] == '+' || str_para[index] == '-' )
		{
			calculate_value_operation(str_para, index);
		}
		
	}

	return atof( str_para.c_str() );
}*/
//accept a string of a math equation and perform the operation at index
//called by calculate_value function
//precondition: character at index must be '+', '-', '*', '/', or '^'
//postcondition: str_para will be modified accordingly and index will point to the last character of the answer
/*
void calculate_value_operation(string& str_para, int& index)
{
	string left_operand = cut_right_number( str_para.substr(0, index) );
	int left_operand_starting_index = index - left_operand.size();
	string right_operand = cut_left_number( str_para.substr(index+1, str_para.size()-(index+1)) );
	int right_operand_ending_index = index + right_operand.size();
	string answer = "";

	double left_operand_n = atof( left_operand.c_str() );
	double right_operand_n = atof( right_operand.c_str() );

	if( str_para[index] == '+' )
	{
		answer = convert_to_str( left_operand_n + right_operand_n );
	}
	else if( str_para[index] == '-' )
	{
		answer = convert_to_str( left_operand_n - right_operand_n );
	}
	else if( str_para[index] == '*' )
	{
		answer = convert_to_str( left_operand_n * right_operand_n );
	}
	else if( str_para[index] == '/' )
	{
		answer = convert_to_str( left_operand_n / right_operand_n );
	}
	else if( str_para[index] == '^' )
	{
		answer = convert_to_str( pow( left_operand_n, right_operand_n ) );
	}

	//replace with the answer
	str_para.replace( left_operand_starting_index, right_operand_ending_index-left_operand_starting_index+1, answer );

	index = left_operand_starting_index + answer.size()-1;
}*/
//generate prime numbers. first parameter determines the number of prime num the function will generate. 
//The list of prime num will be stored in vect
//precondition: number_of_prime must be 1 or more
void generate_prime_number(int number_of_prime, vector<int>& vect)
{
	if( number_of_prime < 1 )
		throw "Error!";

	//clear the vect
	vect.clear();

	//store the first prime number(2)
	vect.push_back(2);
	
	//since the first prime number is already stored, count starts from 2
	for(int count = 2; count <= number_of_prime; count++)
	{
		get_next_prime_number(vect);
	}

}
//assumes that vect has prime numbers starting from the first one
//and insert the next prime number
//if vect is empty, 2 will be inserted
void get_next_prime_number(vector<int>& vect)
{
	if(vect.empty())
	{
		vect.push_back(2);
	}
	else
	{
		int num = vect.back()+1; 
		bool num_is_prime;

		do
		{
			//check if num is a prime
			for(unsigned int element = 1; element <= vect.size(); element++)
			{
				//if num is divisible by the current element
				if( num % vect[element-1] == 0 )
				{
					num_is_prime = false;
					break;
				}

				//if reached the last element
				if( element == vect.size() )
					num_is_prime = true;
			}

			//if num is a prime, add num to the vector
			if( num_is_prime )
				vect.push_back( num );

			num++;

		}while( !num_is_prime ); //if num is not a prime, loop again to check the next num
	}
}
//breaks down num into prime numbers and store it in vect
//precondition: 2 <= num
void break_to_prime_numbers(int num, vector<int>& vect)
{
	if(num < 2)
		throw "Error!";

	//a list of prime numbers. Initialized to first prime number(2)
	vector<int> prime(1, 2);
	int current_prime_number;

	//clear vect
	vect.clear();

	do
	{
		current_prime_number = prime.back();

		//if current_prime_number is a factor of num
		if(num%current_prime_number == 0)
		{
			vect.push_back( current_prime_number );
			num /= current_prime_number;
		}
		else
			get_next_prime_number(prime);

	}while(num != 1);

}
//count the number of order by randomly picking p cards out of n cards
//precondition: p <= n, 0 <= p, 0 <= n
int count_number_of_order(int p, int n)
{
	if( p <= n && 0 <= p && 0 <= n )
	{
		return factorial(n)/factorial(n-p);
	}
	else
	{
		throw "Error!";
	}
}
//count the number of combination by randomly picking p cards out of n cards
//precondition: p <= n, 0 <= p, 0 <= n
int count_number_of_combination(int p, int n)
{
	if( p <= n && 0 <= p && 0 <= n )
	{
		return count_number_of_order(p, n)/factorial(p);
	}
	else
	{
		throw "Error!";
	}
}
//compute n!
//precondition: 0 <= n
int factorial(int n)
{
	if( n < 0 )
		throw "Error";

	int answer = 1;

	//if n = 0, then the loop will not iterate and 1 will be returned
	for(int count = 1; count <= n; count++)
	{
		answer *= count;
	}

	return answer;
}

//receives a list of int and replaces the zeros in list_obj with numbers
//pushes the answers in list_answer
/*
void fill_blank(list<int>& list_obj, list<int>& numbers, list<list<int>>& list_answer)
{
	int num_of_zero = count(list_obj, 0);
	
	if( num_of_zero == 1 )
	{
		list<int> answer(list_obj);
		list<int>::iterator iter = find(answer, 0);
		*iter = numbers.front();
		list_answer.push_back( answer );
	}
	else
	{
		list<int>::iterator numbers_iter = numbers.begin();
		int index = 0;

		while( numbers_iter != numbers.end() )
		{
			//create a copy
			list<int> answer(list_obj);
			list<int>::iterator iter = find(answer, 0);
			*iter = *numbers_iter;

			list<int> copy_numbers(numbers);
			erase(copy_numbers, index);

			fill_blank(answer, copy_numbers, list_answer);

			numbers_iter++;
			index++;
		}
	}
}*/

//find the first item in the list
//return list_obj.end() if can't find
list<int>::iterator find(list<int>& list_obj, int item)
{
	list<int>::iterator iter = list_obj.begin();

	while(iter != list_obj.end())
	{
		if( *iter == item )
		{
			return iter;
		}
		iter++;
	}

	return list_obj.end();
}
//remove the first item in the list_obj
void remove_element(list<int>& list_obj, int item)
{
	list<int>::iterator iter = list_obj.begin();

	while(iter != list_obj.end())
	{
		if( *iter == item )
		{
			list_obj.erase(iter);
			break;
		}

		iter++;
	}
}
//erase the element in list_obj at the index
void erase(list<int>& list_obj, int index)
{
	list<int>::iterator iter = list_obj.begin();
	int count = 0;

	while(iter != list_obj.end())
	{
		if( count == index )
		{
			list_obj.erase(iter);
			break;
		}

		iter++;
		count++;
	}
}

//calculate the distance using pytogarous theorm
double calculate_distance( long double x1, long double y1, long double x2, long double y2)
{
	long double xDistance = x2 - x1;
	long double yDistance = y2 - y1;
	
	return sqrt( pow(xDistance, 2) + pow(yDistance, 2) );
}

//calculate the gradient of the line passing point1 and point2
//precondition: point1 and point2 must have different x-coordinate (else gradient will be +/-infinity)
double calculate_gradient(const twoDVector<double> &point1, const twoDVector<double> &point2)
{
	if(point1.x == point2.x)
		throw "Error!";

	return (point2.y-point1.y)/(point2.x-point1.x);
}

//calculate the y-intercept of the line passing point1 and point2
//precondition: a y-intercept must exist
double calculate_y_intercept(const twoDVector<double> &point1, const twoDVector<double> &point2)
{
	//if the 2 points have the same x-coordinate, there will no y-intercept
	if(point1.x == point2.x)
		throw "Error!";

	//c = y - mx
	return point1.y - calculate_gradient(point1, point2)*point1.x;
}
//determine whether point3 is on the line (including the endpoints) passing point1 and point2
bool point_is_on_line(const twoDVector<double> &point1, const twoDVector<double> &point2, const twoDVector<double> &point3)
{
	//if point3 lies on the line that is extended to infinity
	if( (point2.x-point1.x)*(point3.y-point1.y) == (point2.y-point1.y)*(point3.x - point1.x) )
	{
		double larger_x, smaller_x, larger_y, smaller_y;

		if(point1.x < point2.x)
		{
			larger_x = point2.x;
			smaller_x = point1.x;
		}
		else
		{
			larger_x = point1.x;
			smaller_x = point2.x;
		}
		
		if(point1.y < point2.y)
		{
			larger_y = point2.y;
			smaller_y = point1.y;
		}
		else
		{
			larger_y = point1.y;
			smaller_y = point2.y;
		}

		//if point3 is between point1 and point2
		if( smaller_x <= point3.x && point3.x <= larger_x && 
			smaller_y <= point3.y && point3.y <= larger_y)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}


twoDVector<long double> calculate_direction( long double x1, long double y1, long double x2, long double y2)
{
	long double xDistance = x2 - x1;
	long double yDistance = y2 - y1;
	twoDVector<long double> temp = {xDistance, yDistance};

	return temp;
}

//returns a vector having size number_of_list and adds up to total_value
vector<int> separate( int total_value, int number_of_list)
{
	if(total_value <= 0 || number_of_list <= 0)
	{
		throw "Error!";
	}

	vector<int> list(0);

	//why does floor return double?
	int round_down_value = static_cast<int>(floor(static_cast<double>(total_value)/number_of_list));
	int amount_left = total_value - round_down_value*number_of_list;

	//insert the round_down_value
	for(int count = 1; count <= number_of_list; count++)
	{
		list.push_back( round_down_value );
	}

	for(int index = 0; index < amount_left; index++)
	{
		list[index]++;
	}

	return list;

}



// **functions related to box**
//find the top left coordinate of a box in which coordinate1 and coordinate2 are opposite edges of the box
twoDVector <int> find_top_left( const twoDVector<int> &coordinate1, const twoDVector<int> &coordinate2 )
{
	twoDVector<int> top_left_coordinate;

	//find the top left coordinate
	if( coordinate1.x < coordinate2.x )
	{
		//if 1 is above 2
		if( coordinate1.y < coordinate2.y ) //1 is at top left, 2 is at lower right
		{
			top_left_coordinate.x = coordinate1.x;
			top_left_coordinate.y = coordinate1.y;
		}
		else //1 is at lower left, 2 is at upper right
		{
			top_left_coordinate.x = coordinate1.x;
			top_left_coordinate.y = coordinate2.y;
		}
	}
	else //if coordinate2 is on the left
	{
		if( coordinate1.y < coordinate2.y ) //2 is at lower left, 1 is at upper right
		{
			top_left_coordinate.x = coordinate2.x;
			top_left_coordinate.y = coordinate1.y;
		}
		else
		{
			top_left_coordinate.x = coordinate2.x;
			top_left_coordinate.y = coordinate2.y;
		}
	}

	return top_left_coordinate;
}//end function find_top_left




//coordinate1 and coordinate2 are the opposite edges of a box
void calculate_width_height(const twoDVector<int> &coordinate1, const twoDVector<int> &coordinate2, int &width, int &height)
{
	width = abs(coordinate1.x - coordinate2.x) + 1;
	height = abs(coordinate1.y - coordinate2.y) + 1;
}

//checks whether 2 lines collide
bool check_collision(const twoDVector<double> &line1_point1, const twoDVector<double> &line1_point2, const twoDVector<double> &line2_point1, const twoDVector<double> &line2_point2)
{
	double x_a = line1_point2.x - line1_point1.x;
	double y_a = line1_point2.y - line1_point1.y;
	double x_b = line2_point2.x - line2_point1.x;
	double y_b = line2_point2.y - line2_point1.y;

	//if the 2 lines are parallel, 
	if( y_a*x_b == y_b*x_a )
	{
		//if one line lies on the other
		if( point_is_on_line(line1_point1, line1_point2, line2_point1) ||
			point_is_on_line(line1_point1, line1_point2, line2_point2) ||
			point_is_on_line(line2_point1, line2_point2, line1_point1) ||
			point_is_on_line(line2_point1, line2_point2, line1_point2) )
			return true;
		else
			return false;
	}
	/*
	//calculate the gradient and the y-intercepts of the lines
	double m1 = calculate_gradient(line1_point1, line1_point2);
	double m1 = calculate_gradient(line2_point1, line2_point2);
	double c1 = calculate_y_intercept(line1_point1, line1_point2);
	double c2 = calculate_y_intercept(line2_point1, line2_point2);
	*/
	
	//first, calculate the point of intersection
	twoDVector<double> intersection_point;
	intersection_point.x = (x_a * x_b * (line2_point1.y-line1_point1.y) - x_a*y_b*line2_point1.x + x_b*y_a*line1_point1.x)/
		(x_b*y_a - x_a*y_b)/*(c2 - c1)/(m1 - m2)*/;
	intersection_point.y = (y_a * y_b * (line2_point1.x-line1_point1.x) - x_b*y_a*line2_point1.y + x_a*y_b*line1_point1.y)/
		(x_a*y_b - x_b*y_a)/*m1*intersection_point.x + c1*/;

	//if point of intersection lies on both lines
	if( point_is_on_line(line1_point1, line1_point2, intersection_point) &&
		point_is_on_line(line2_point1, line2_point2, intersection_point) )
	{
		return true;
	}
	else
		return false;
}