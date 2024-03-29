#pragma once

#include <vector>
#include "interval.hpp"

// an array of elementary intervals.
class Cube
{

public:

	Cube(std::vector<Interval> intervals);
	Cube();
	~Cube();

	const Interval& operator[](int i) const;
	Interval& operator[](int i);
	void addInterval(Interval interval);


	// the dimension of a cube is the number of non-degenerate intervals
	// that constitute the cube.
	// we will keep track of this whenever we add a new interval.
	int Dimension() const;
	
	// the embedding number is the number of intervals constituting the
	// cube.
	int EmbeddingNumber() const;
	int size() const;

	void Print() const;

private:

	int Dimension(std::vector<Interval> intervals);

	int dimension = 0;
	std::vector<Interval> intervals;

};

bool operator==(const Cube& left, const Cube& right);
