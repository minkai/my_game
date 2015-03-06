#ifndef MINKAI_TABLE
#define MINKAI_TABLE 

#include "twoDVector.h"
#include <list>
#include <map>

using namespace std;

//A 2D table
template <class T>
class Minkai_Table
{
private:
	map<twoDVector<int>, T> table;

	//number of rows and columns
	int row;
	int column;
	/*
	//called by get_element (both version)
	const T* get_ptr( int row_num, int column_num ) const
	{
		//the position of node in the list
		int list_num = (row_num-1)*column + column_num;

		list<T>::const_iterator iter = value.begin();

		for( int count = 1; count <= list_num-1; count++ )
		{
			iter++;
		}

		return &(*iter);
	}
	*/
public:
	//constructor
	Minkai_Table(twoDVector<int> dimension = twoDVector<int>(0, 0))
	{
		row = dimension.y;
		column = dimension.x;

		for (int x = 0; x < column; x++)
		{
			for (int y = 0; y < row; y++)
			{
				table[twoDVector<int>(x, y)] = T();
			}
		}
	}

	bool is_valid_row_index(int row_index)
	{
		if (0 <= row_index && row_index < row)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool is_valid_column_index(int column_index)
	{
		if (0 <= column_index && column_index < column)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void add_row(int row_index, list<T> l)
	{
		if (!(0 <= row_index && row_index <= row))
		{
			throw "Invalid row index."
		}

		if (l.size() != column)
		{
			throw "Exception."
		}
		
		//adjust y-coordinates of old values
		for (int y = row - 1; row_index <= y; y--)
		{
			for (int x = 0; x < column; x++)
			{
				table[twoDVector(x, y + 1)] = table[twoDVector(x, y)];
			}
		}

		list<T>::iterator it = l.begin();
		//add the new values
		for (int x = 0; x < column; x++)
		{
			table[twoDVector(x, row_index)] = *it;
			it++;
		}

		row++;
	}

	void add_column(int column_index, list<T> l)
	{
		if (!(0 <= column_index && column_index <= column))
		{
			throw "Invalid column index."
		}

		if (l.size() != row)
		{
			throw "Exception."
		}

		//adjust x-coordinates of old values
		for (int x = column - 1; column_index <= x; x--)
		{
			for (int y = 0; y < row; y++)
			{
				table[twoDVector(x+1, y)] = table[twoDVector(x, y)];
			}
		}

		list<T>::iterator it = l.begin();
		//add the new values
		for (int y = 0; y < row; y++)
		{
			table[twoDVector(column_index, y)] = *it;
			it++;
		}

		column++;
	}

	void delete_row(int row_index)
	{
		if (!is_valid_row_index(row_index))
		{
			throw "Invalid row index."
		}

		for (int y = row_index + 1; y < row; y++)
		{
			for (int x = 0; x < column; x++)
			{
				table[twoDVector(x, y - 1)] = table[twoDVector(x, y)];
			}
		}

		for (int x = 0; x < column; x++)
		{
			table.erase(twoDVector(x, row-1));
		}

		row--;
	}
	
	void delete_column(int column_index)
	{
		if (!is_valid_column_index(column_index))
		{
			throw "Invalid column index."
		}

		for (int x = column_index + 1; x < column; x++)
		{
			for (int y = 0; y < row; y++)
			{
				table[twoDVector(x-1, y)] = table[twoDVector(x, y)];
			}
		}

		for (int y = 0; y < row; y++)
		{
			table.erase(twoDVector(column-1, y));
		}

		column--;
	}

	int get_rows() const
	{
		return row;
	}
	
	int get_columns() const
	{
		return column;
	}
	
	bool is_empty() const
	{
		if( get_rows() == 0 || get_columns() == 0 )
		{
			return true;
		}
		else
			return false;
	}

	T& get_element( int row_index, int column_index )
	{
		if( is_valid_row_index(row_index) && is_valid_column_index(column_index) )
		{
			return table[twoDVector<int>(column_index,row_index)];
		}
		else
			throw "Error!";
	}

	T& operator[](twoDVector<int> p)
	{
		return get_element(p.y, p.x);
	}
	
};
/*
template <class T>
void display(const Minkai_Table<T>& table)
{
	int row = table.get_rows();
	int column = table.get_columns();

	for(int row_count = 1; row_count <= row; row_count++)
	{
		for(int column_count = 1; column_count <= column; column_count++)
		{
			cout << table.get_element( row_count, column_count );
			cout << " ";
		}

		cout << endl;
	}
}
*/
#endif