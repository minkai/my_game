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

//generate prime numbers. number_of_prime determines the number of prime num the function will generate. 
//precondition: number_of_prime must be 1 or more
SafeArray<int> generate_prime_number(int number_of_prime)
{
	if( number_of_prime < 1 )
		throw "Error!";

	SafeArray<int> numbers(number_of_prime);

	//store the first prime number
	numbers[0] = 2;
	
	int insert_i = 1;
	int num = numbers[0] + 1;

	while (insert_i < number_of_prime)
	{
		int i = 0;
		//check if num is a prime
		for (i = 0; i < insert_i; i++)
		{
			//if num is divisible by the current element
			if (num % numbers[i] == 0)
			{
				break;
			}
		}

		//if num is a prime, add num to numbers
		if (i == insert_i)
		{
			numbers[insert_i] = num;
			insert_i++;
		}

		num++;
	}

	return numbers;
}
//assumes that num_array has prime numbers starting from the first one
//and insert the next prime number
//if vect is empty, 2 will be inserted
int get_next_prime_number(SafeArray<int>& num_array)
{
	if(num_array.size() == 0)
	{
		 return 2;
	}
	else
	{
		int num = num_array[num_array.size()-1]+1; 

		while( true )
		{
			int i = 0;
			//check if num is a prime
			for (i = 0; i < num_array.size(); i++)
			{
				//if num is divisible by the current element
				if (num % num_array[i] == 0)
				{
					break;
				}
			}

			//if num is a prime
			if (i == num_array.size())
			{
				return num;
			}

			num++;

		}
	}
}
//breaks down num into prime numbers
//precondition: 2 <= num
SafeArray<int> break_to_prime_numbers(int num)
{
	if(num < 2)
		throw "Error!";

	//a list of prime numbers. Initialized to first prime number(2)
	vector<int> prime(1, 2);
	vector<int> answer_vect;

	do
	{
		int current_prime_number = prime.back();

		//if current_prime_number is a factor of num
		if (num % current_prime_number == 0)
		{
			answer_vect.push_back(current_prime_number);
			num /= current_prime_number;
		}
		else
		{
			SafeArray<int> num_array(prime.size());
			for (int i = 0; i < prime.size(); i++)
			{
				num_array[i] = prime[i];
			}
			prime.push_back(get_next_prime_number(num_array));
		}

	} while (num != 1);

	SafeArray<int> answer(answer_vect.size());
	for (int i = 0; i < answer_vect.size(); i++)
	{
		answer[i] = answer_vect[i];
	}

	return answer;
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
//returns an array having size number_of_values and adds up to total_value
SafeArray<int> separate( int total_value, int number_of_values )
{
	if(total_value <= 0 || number_of_values <= 0)
	{
		throw "Error!";
	}

	SafeArray<int> answer(number_of_values);

	int t = total_value;
	int g = 0;

	while( number_of_values <= t )
	{
		g++;
		t -= number_of_values;
	}

	for(int i = 0; i < answer.size(); i++)
	{
		answer[i] = g;
	}

	if (t != 0)
	{
		//will truncate because of int
		int inc = number_of_values / t;
		for (int i = 0; i < t; i++)
		{
			answer[number_of_values-1-i*inc]++;
		}
	}

	return answer;
}

//calculate the distance using pytogarous theorm
double calculate_distance(const twoDVector<double>& point1, const twoDVector<double>& point2)
{
	double xDistance = point2.x - point1.x;
	double yDistance = point2.y - point1.y;
	
	return sqrt( pow(xDistance, 2) + pow(yDistance, 2) );
}

//calculate the gradient of the line passing point1 and point2
//precondition: point1 and point2 must have different x-coordinate (else gradient will be +/-infinity)
double calculate_gradient(const twoDVector<double>& point1, const twoDVector<double>& point2)
{
	if(point1.x == point2.x)
		throw "Error!";

	return (point2.y-point1.y)/(point2.x-point1.x);
}

//calculate the y-intercept of the line passing point1 and point2
//precondition: a y-intercept must exist
double calculate_y_intercept(const twoDVector<double>& point1, const twoDVector<double>& point2)
{
	//if the 2 points have the same x-coordinate, there will no y-intercept
	if(point1.x == point2.x)
		throw "Error!";

	//c = y - mx
	return point1.y - calculate_gradient(point1, point2)*point1.x;
}

twoDVector<double> calculate_direction(const twoDVector<double>& point1, const twoDVector<double>& point2)
{
	long double xDistance = point2.x - point1.x;
	long double yDistance = point2.y - point1.y;
	return twoDVector<double>(xDistance, yDistance);
}

//determine whether point3 is on the line (including the endpoints) passing point1 and point2
bool point_is_on_line(const twoDVector<double>& point1, const twoDVector<double>& point2, const twoDVector<double>& point3)
{
	//if point3 lies on the line that is extended to infinity (assume the line has infinite length on both sides)
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
	}
	
	return false;
}

//find the top left coordinate of a box in which coordinate1 and coordinate2 are opposite edges of the box
twoDVector<double> find_top_left( const twoDVector<double>& coordinate1, const twoDVector<double>& coordinate2 )
{
	twoDVector<double> top_left_coordinate;

	//find the top left coordinate
	if( coordinate1.x < coordinate2.x )
	{
		//if 1 is above 2
		if( coordinate1.y < coordinate2.y ) //1 is at top left, 2 is at lower right
		{
			top_left_coordinate = coordinate1;
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
			top_left_coordinate = coordinate2;
		}
	}

	return top_left_coordinate;
}//end function find_top_left

bool point_is_in_box(const twoDVector<double>& point, const twoDVector<double>& box_top_left_coordinate, const twoDVector<double>& box_dimension)
{
	//coordinate of left and right side of the box
	double box_left = box_top_left_coordinate.x;
	double box_right = box_top_left_coordinate.x + box_dimension.x;
	//coordinate of up and down side of the box
	double box_up = box_top_left_coordinate.y;
	double box_down = box_top_left_coordinate.y + box_dimension.y;

	return ( box_left <= point.x && point.x <= box_right && 
		box_up <= point.y && point.y <= box_down );
}

//checks whether 2 lines collide
bool check_collision(const twoDVector<double>& line1_point1, const twoDVector<double>& line1_point2, const twoDVector<double>& line2_point1, const twoDVector<double>& line2_point2)
{
	double x_a = line1_point2.x - line1_point1.x;
	double y_a = line1_point2.y - line1_point1.y;
	double x_b = line2_point2.x - line2_point1.x;
	double y_b = line2_point2.y - line2_point1.y;

	//if the 2 lines are parallel, 
	if( y_a*x_b == y_b*x_a )
	{
		//only need to check for 3 points
		return( point_is_on_line(line1_point1, line1_point2, line2_point1) ||
			point_is_on_line(line1_point1, line1_point2, line2_point2) ||
			point_is_on_line(line2_point1, line2_point2, line1_point1) );
	}
	
	//first, calculate the point of intersection
	twoDVector<double> intersection_point;
	intersection_point.x = (x_a * x_b * (line2_point1.y-line1_point1.y) - x_a*y_b*line2_point1.x + x_b*y_a*line1_point1.x)/
		(x_b*y_a - x_a*y_b);
	intersection_point.y = (y_a * y_b * (line2_point1.x-line1_point1.x) - x_b*y_a*line2_point1.y + x_a*y_b*line1_point1.y)/
		(x_a*y_b - x_b*y_a);

	//if point of intersection lies on both lines, they collide
	return( point_is_on_line(line1_point1, line1_point2, intersection_point) &&
		point_is_on_line(line2_point1, line2_point2, intersection_point) );
}