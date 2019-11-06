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
void Cube::addInterval(Interval interval)
{
	this->intervals.push_back(interval);
	if (!(interval.isDegenerate()))
	{
		++dimension;
	}
}


int Cube::Dimension() const
{
	return this->dimension;
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
}
