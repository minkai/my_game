#include <iostream>
#include "Random_Number.h"

using namespace std;

//the function that will not return 0
long double fluctuation_function(long double x)
{
	long double y = 52100*sin(0.03*x)*sin(0.05*x)*sin(0.6*x) + 86400*sin(0.012*x);
	if( int(x)%2 == 0 )
		y += 148500;
	else
		y -= 148500;

	return y;
}

//generate a random integer with lower and upper limit
//precondition: upper limit must be greater than lower limit
int generate_random_number(int lower_limit, int upper_limit)
{
	if( upper_limit <= lower_limit )
		throw "Error!";

	//the value to be returned
	static int static_var = 1;
	long current_time = long(time(NULL));
	long double reduced_time = current_time - 1272200100;
	long double x;

	x = (reduced_time + static_var)*0.5;
	x += fluctuation_function(x);
	//long double seed1 = 14*pow(x, 7) - 45*pow(x, 6) + 95*pow(x, 4) - 15*pow(x, 3) + static_var;
	//long double seed2 = 186*pow(x, 8) - 25*pow(x, 7) + 28*pow(x, 4) - 15*pow(x, 3) + static_var;
	//srand( int(x) + static_var );

	if( abs( int(x) ) != static_var )
	{
		x += fluctuation_function(x);
	}

	//absolute value is needed to prevent errors
	static_var = abs( int(x) ); //rand();
	
	return static_var%(upper_limit-lower_limit+1)+lower_limit;
}


