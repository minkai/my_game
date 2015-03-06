#ifndef MATH_FUNCTION_H
#define MATH_FUNCTION_H

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include "twoDVector.h"
//#include "Box.h"
#include "SafeArray.h"
//#include "for loop macro.h"
//#include "Good_List.h"

using namespace std;

//double calculate_value(string str_para);
//void calculate_value_operation(string& str_para, int& index);
void generate_prime_number(int number_of_prime, vector<int>& vect);
void get_next_prime_number(vector<int>& vect);
void break_to_prime_numbers(int num, vector<int>& vect);
int count_number_of_order(int p, int n);
int count_number_of_combination(int p, int n);
int factorial(int n);
//void fill_blank(list<int>& list_obj, list<int>& numbers, list<list<int>>& list_answer);
list<int>::iterator find(list<int>& list_obj, int item);
void erase(list<int>& list_obj, int index);


void calculate_width_height(const twoDVector<int> &coordinate1, const twoDVector<int> &coordinate2, int &width, int &height);
double calculate_distance( long double x1, long double y1, long double x2, long double y2);
double calculate_gradient(const twoDVector<double> &point1, const twoDVector<double> &point2);
double calculate_y_intercept(const twoDVector<double> &point1, const twoDVector<double> &point2);
bool point_is_on_line(const twoDVector<double> &point1, const twoDVector<double> &point2, const twoDVector<double> &point3);

template <class T1, class T2>
double calculate_distance(twoDVector<T1> coordinate1, twoDVector<T2> coordinate2)
{
	return calculate_distance(coordinate1.x, coordinate1.y, coordinate2.x, coordinate2.y);
}
vector<int> separate(int total_value, int number_of_list);
twoDVector <int> calculate_direction( int x1, int y1, int x2, int y2);
twoDVector <int> find_top_left( const twoDVector<int> &coordinate1, const twoDVector<int> &coordinate2 );

//find the min or max of the list of numbers, also stores the index at at_index
template <class T>
T find_min_max( vector<T> &number_list, bool find_max, int &at_index)
{
	//if the list is empty
	if(number_list.empty())
	{
		throw "Error in find_min_max()";
	}

	//take the first number and assign it to min and max
	T min = number_list[0];
	int index_of_min = 0;
	T max = number_list[0];
	int index_of_max = 0;

	for(int count = 1; count <= static_cast<int>(number_list.size()); count++)
	{
		if(max < number_list[count-1])
		{
			max = number_list[count-1];
			index_of_max = count-1;
		}

		if( number_list[count-1] < min )
		{
			min = number_list[count-1];
			index_of_min = count-1;
		}
	}//end for

	//if the function should find the max
	if(find_max)
	{
		at_index = index_of_max;
		return max;
	}
	else //if the function should find the min
	{
		at_index = index_of_min;
		return min;
	}
}

//checks whether 2 vectors has the same direction
template <class T1, class T2>
bool has_same_direction( const twoDVector<T1> v1, const twoDVector<T2> v2)
{
	long double xRatio = v2.x/v1.x;
	long double yRatio = v2.y/v1.y;

	if(xRatio == yRatio)
		return true;
	else
		return false;
}


// **functions related to box**
//check if a point is inside a box
/*
template <class T> //this version is less useful since the box must have int dimensions
bool point_is_in_box(const twoDVector<T> &point, const Box* box_ptr)
{
	twoDVector<int> box_top_left_coordinate = {box_ptr->get_left(), box_ptr->get_top()};

	return point_is_in_box( point, box_top_left_coordinate, box_ptr->get_width(), box_ptr->get_height() );
	
}*/
template <class T1, class T2> //more useful version
bool point_is_in_box(const twoDVector<T1> &point, const twoDVector<T2> box_top_left_coordinate, long double width, long double height)
{
	//coordinate of left and right side of the box
	long double box_left = box_top_left_coordinate.x;
	long double box_right = box_top_left_coordinate.x + width;
	//coordinate of up and down side of the box
	long double box_up = box_top_left_coordinate.y;
	long double box_down = box_top_left_coordinate.y + height;

	if( box_left < point.x && point.x < box_right && 
		box_up < point.y && point.y < box_down )
		return true;
	else
		return false;
}

//checks whether 2 lines collide
bool check_collision(const twoDVector<double> &line1_point1, const twoDVector<double> &line1_point2, const twoDVector<double> &line2_point1, const twoDVector<double> &line2_point2);


#endif