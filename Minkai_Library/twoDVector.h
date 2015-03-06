#ifndef TWODVECTOR_H
#define TWODVECTOR_H

//A 2 dimensional vector
template <class T>
//A 2 dimensional vector
class twoDVector
{
public:
	T x;
	T y;

	twoDVector<T>(){}
	twoDVector<T>(T x_para, T y_para)
	{
		x = x_para;
		y = y_para;
	}

	bool operator==(const twoDVector<T> v) const
	{
		if (x == v.x && y == v.y)
		{
			return true;
		}
		else
			return false;
	}

	bool operator!=(const twoDVector<T> v) const
	{
		if (*this == v)
		{
			return false;
		}
		else
			return true;
	}

	bool operator< (const twoDVector<T> v) const
	{
		if (y < v.y)
		{
			return true;
		}
		else if (y == v.y)
		{
			if (x < v.x)
			{
				return true;
			}
		}

		return false;
	}

	void operator+=(const twoDVector<T> v)
	{
		x += v.x;
		y += v.y;
	}
};
#endif