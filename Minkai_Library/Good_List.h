//last update: 18th July 2010

#ifndef GOOD_LIST_H
#define GOOD_LIST_H

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

//inherits from list and adds the [] operator.
//Not recommended as it would take a long time to compile
template <class T>
class Good_List : public list<T>
{
public:
	//default constructor
	Good_List(int size_para = 1) : list<T>(size_para)
	{
	}
	T &operator[](const int &index)
	{
		if( index + 1 <= static_cast<int>(size()) )
		{
			list<T>::iterator iter = begin();
			for(int count = 1; count <= index; count++)
			{
				iter++;
			}
			return *iter;
		}
		else
			throw "Error";
	}
};


//acts like the [] operator
//precondition: 1 <= index+1 <= list_obj.size() 
template<class T>
T& get_element(list<T>& list_obj, unsigned int index)
{
	//if index is out of range
	if( index < 0 || list_obj.size() < index+1 )
		throw "Error!";

	//create an iterator that starts at the beginning
	list<T>::iterator iter = list_obj.begin();

	//move forward by index
	for(unsigned int count = 1; count <= index; count++)
		iter++;

	return *iter;
}

//remove duplicates in the list
template <class T>
void remove_duplicates(list<T>& list_obj, T& item)
{
	for( list<T>::iterator iter = list_obj.begin(); iter != list_obj.end(); iter++)
	{
		list<T>::iterator iter_next = iter;
		iter_next++;
		//iter2 will scan the elements after iter
		for( list<T>::iterator iter2 = iter_next; iter2 != list_obj.end(); iter2++)
		{
			//if the 2 elements are the same
			if( *iter == *iter2 )
			{
				//remove it
				list<T>::iterator temp = iter2;
				iter2--;
				list_obj.erase(temp);
			}
		}
	}
}

//count the number of item in the list
template <class T>
int count(const list<T>& list_obj, const T& item)
{
	int answer = 0;
	list<T>::const_iterator iter;
	
	//loop through the list
	for(iter = list_obj.begin(); iter != list_obj.end(); iter++)
	{
		//if the current element is the item
		if( *iter == item )
		{
			answer++;
		}
		
	}
	
	return answer;
}

//check whether the list has duplicates
template <class T>
bool has_duplicates(const list<T>& list_obj)
{
	list<int>::const_iterator iter1;
	list<int>::const_iterator iter2;

	for(iter1 = list_obj.begin(); iter1 != list_obj.end(); iter1++)
	{
		//iterator used to point to next element after iter1
		list<int>::const_iterator temp = iter1;
		temp++;
		for(iter2 = temp; iter2 != list_obj.end(); iter2++)
		{
			//if duplicates are found
			if(*iter1 == *iter2)
			{
				return true;
			}
		}
	}

	return false;
}

//merge second list to first list
template <class T>
void merge( list<T>& first_list, const list<T>& second_list )
{
	for( list<T>::iterator iter = second.begin(); iter != second.end(); iter++ )
	{
		first_list.push_back( *iter );
	}
}

template <class T>
void display(const list<T>& list_obj)
{
	list<T>::iterator iter;

	for( iter = list_obj.begin(); iter != list_obj.end(); iter++ )
		cout << *iter;
}
#endif