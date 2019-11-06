#pragma once

#include <cstring>
#include <functional>
#include "interval.hpp"

// responsible for hashing custom data types, such as intervals and cubes.
struct KeyHasher
{

public:

	// hash interval:
	std::size_t operator()(const Interval& interval) const
	{
	   return ((std::hash<int>()(interval.getLeft())
				 ^ (std::hash<int>()(interval.getRight()) << 1)) >> 1);
	}

private:



};
