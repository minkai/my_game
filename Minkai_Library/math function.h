#ifndef MATH_FUNCTION_H
#define MATH_FUNCTION_H

#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "twoDVector.h"
//#include "Box.h"
#include "SafeArray.h"
//#include "for loop macro.h"
//#include "Good_List.h"

using namespace std;

//double calculate_value(string str_para);
//void calculate_value_operation(string& str_para, int& index);
SafeArray<int> generate_prime_number(int number_of_prime);
int get_next_prime_number(const SafeArray<int>& vect);
void break_to_prime_numbers(int num, vector<int>& vect);
int count_number_of_order(int p, int n);
int count_number_of_combination(int p, int n);
int factorial(int n);
SafeArray<int> separate(int total_value, int number_of_list);

double calculate_distance(const twoDVector<double>& point1, const twoDVector<double>& point2);
double calculate_gradient(const twoDVector<double>& point1, const twoDVector<double>& point2);
double calculate_y_intercept(const twoDVector<double>& point1, const twoDVector<double>& point2);
twoDVector<double> calculate_direction(const twoDVector<double>& point1, const twoDVector<double>& point2);
bool point_is_on_line(const twoDVector<double>& point1, const twoDVector<double>& point2, const twoDVector<double>& point3);
twoDVector<double> find_top_left( const twoDVector<double>& coordinate1, const twoDVector<double>& coordinate2 );
bool point_is_in_box(const twoDVector<double>& point, const twoDVector<double>& box_top_left_coordinate, const twoDVector<double>& box_dimension);

//checks whether 2 lines collide
bool check_collision(const twoDVector<double>& line1_point1, const twoDVector<double>& line1_point2, const twoDVector<double>& line2_point1, const twoDVector<double>& line2_point2);

#endif