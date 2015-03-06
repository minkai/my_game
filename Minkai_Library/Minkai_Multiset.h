#ifndef MINKAI_MULTISET
#define MINKAI_MULTISET

#include <map>

using namespace std;

//A multiset in which each object is assigned a unique ID
//this ID starts from 1
template <class T>
class Minkai_Multiset
{
private:
	map<int, T> table;
	int counter;
public:
	Minkai_Multiset()
	{
		counter = 0;
	}
	
	int get_size() const
	{
		return table.size();
	}

	int add(const T& item)
	{
		counter++;
		table[counter] = item;
		return counter;
	}

	void remove(int i)
	{
		table.erase(i);
	}

	T& get_element(int i)
	{
		if( table.find(i) != table.end() )
		{
			return table[i];
		}
		else
		{
			throw "Error!";
		}
	}

	T& operator[](int i)
	{
		return get_element(i);
	}

};

#endif