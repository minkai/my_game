//last complete check: 28th March 2010

#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include "convert to str.h"

//an array that performs boundary checking
template <class T>
class SafeArray
{
private:
	T* ptr;
	int arraySize;

	//copies the content of another SafeArray object
	//called from the copy constructor only
	void copy( const SafeArray<T> &obj )
	{
		arraySize = obj.arraySize;

		if( arraySize == 0 )
			ptr = NULL;
		else
		{
			ptr = new T[arraySize];

			//copy the contents from obj
			for(int count = 1; count <= arraySize; count++)
			{
				ptr[count-1] = (obj.ptr)[count-1];
			}
		}
	}
public:
	//constructor, receives initial size as parameter
	//precondition: arraySize_para must be 0 or more
	SafeArray(int arraySize_para = 0)
	{
		if( arraySize_para < 0)
			throw "Error in SafeArray! " __FILE__ " " + convert_to_str(__LINE__);

		arraySize = arraySize_para;

		if( arraySize_para == 0 )
			ptr = NULL;
		else
			ptr = new T[arraySize_para];
	}
	//copy contructor
	SafeArray(const SafeArray<T>& obj)
	{
		copy( obj );
	}

	//destructor
	~SafeArray()
	{
		if(1 <= arraySize)
			delete [] ptr;

		//is this needed?
		ptr = NULL;
	}

	//overloads the = operator
	//precondition: obj must have the same size as this object
	SafeArray<T> operator=(const SafeArray<T> &obj)
	{
		if(arraySize != obj.arraySize)
			throw "Error!";

		//copy the contents from obj
		for(int count = 1; count <= arraySize; count++)
		{
			ptr[count-1] = (obj.ptr)[count-1];
		}

		//return a copy of itself
		return (*this);
	}
	
	//overloads the [] operator to access elements. 
	//precondition: 1 <= index+1 <= arraySize 
	T &operator[](const int& index)
	{
		//performs bounds checking
		if( index+1 < 1 || arraySize < index+1 )
		{
			throw "Error in SafeArray! " __FILE__ " " + convert_to_str(__LINE__);
		}

		return ptr[index];
	}

	//count the number of item in the array
	int count(const T& item)
	{
		int answer = 0;

		//loop through the array
		for(int count = 1; count <= arraySize; count++)
		{
			//if this element matches the item
			if( ptr[count-1] == item )
			{
				answer++;
			}
		}

		return answer;
	}

	//find the (number)th item in the array and return a pointer to it
	//returns NULL if there are less than number item in the array
	//precondition: 1 <= number
	T* find(const T& item, int number)
	{
		if( 1 <= number )
		{
			//the number of items that is currently found
			int current_number = 0;
			T* returned_value = NULL;

			//loop through the array
			for(int count = 1; count <= arraySize; count++)
			{
				//if this element matches the item
				if( ptr[count-1] == item )
				{
					current_number++;
					if( current_number == number )
					{
						returned_value = &( ptr[count-1] );
						break;
					}
				}
			}

			return returned_value;

		} //end if( 1 <= number )
		else
		{
			throw "Error!";
		}
	}

	//returns the size of the array
	int size() const
	{
		return arraySize;
	}
};

#endif