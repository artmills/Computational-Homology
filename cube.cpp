#include "cube.hpp"


Cube::Cube(std::vector<Interval> intervals)
{
	this->intervals = intervals;
	this->dimension = Dimension(intervals);
}
Cube::Cube(){}
Cube::~Cube(){}


Interval& Cube::operator[](int i) 
{
	return intervals[i];
}
const Interval& Cube::operator[](int i) const
{
	return intervals[i];
}
void Cube::addInterval(Interval interval)
{
	this->intervals.push_back(interval);
	if (!(interval.isDegenerate()))
	{
		++dimension;
	}
}

void Cube::Print() const
{
	for (int i = 0; i < intervals.size() - 1; ++i)
	{
		//intervals[i].Print();
		if (intervals[i].isDegenerate())
		{
			std::cout << "(" << intervals[i].getLeft() << ") x ";
		}
		else
		{
			std::cout << "(" << intervals[i].getLeft() << ", " << intervals[i].getRight() << ") x ";
		}
	}
	if (intervals.size() > 0)
	{
		Interval last = intervals[intervals.size() - 1];
		if (last.isDegenerate())
		{
			std::cout << "(" << last.getLeft() << ")" << std::endl;
		}
		else
		{
			std::cout << "(" << last.getLeft() << ", " << last.getRight() << ")" << std::endl;
		}
	}
}


int Cube::Dimension() const
{
	int dim = 0;
	for (int i = 0; i < intervals.size(); ++i)
	{
		if (!(intervals[i].isDegenerate()))
		{
			++dim;
		}
	}
	return dim;
	//return this->dimension;
}
int Cube::Dimension(std::vector<Interval> intervals)
{
	int dim = 0;
	for (int i = 0; i < intervals.size(); ++i)
	{
		if (!(intervals[i].isDegenerate()))
		{
			++dim;
		}
	}
	return dim;
}
int Cube::EmbeddingNumber() const
{
	return intervals.size();
}
int Cube::size() const
{
	return intervals.size();
}

// equality for when order of intervals assigned to the cube do not matter.
bool operator==(const Cube& left, const Cube& right)
{
	/*
	std::cout << std::endl;
	std::cout << "Comparing: " << std::endl;
	left.Print();
	right.Print();
	std::cout << std::endl;
	*/

	// quick check: needs to have the same embedding number and dimension.
	if (left.EmbeddingNumber() != right.EmbeddingNumber())
	{
		return false;
	}
	if (left.Dimension() != right.Dimension())
	{
		return false;
	}

	// now the tricky bit. two cubes will be equal if all of their 
	// intervals are equal.
	for (int i = 0; i < left.size(); ++i)
	{
		if (left[i] != right[i])
		{
			return false;
		}
	}
	return true;
}
/*
bool operator==(const Cube& left, const Cube& right)
{
	// quick check: needs to have the same embedding number and dimension.
	if (left.EmbeddingNumber() != right.EmbeddingNumber())
	{
		return false;
	}
	if (left.Dimension() != right.Dimension())
	{
		return false;
	}

	// now the tricky bit. two cubes will be equal if all of their 
	// intervals are equal.
	for (int i = 0; i < left.size(); ++i)
	{
		bool flag = false;
		int j = 0;
		while (!flag && j < right.size())
		{
			if (left[i].getLeft() == right[j].getLeft() && left[i].getRight() == right[j].getRight())
			{
				flag = true;
			}
			++j;
		}
		if (flag == false)
		{
			return false;
		}
	}
	return true;
}
*/
