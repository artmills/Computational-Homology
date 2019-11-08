#pragma once

#include <cstring>
#include <functional>
#include "cube.hpp"

// responsible for hashing custom data types, such as intervals and cubes.
struct KeyHasher
{

public:

	// hash interval:
	/*
	std::size_t operator()(const Interval& interval) const
	{
	   return ((std::hash<int>()(interval.getLeft())
				 ^ (std::hash<int>()(interval.getRight()) << 1)) >> 1);
	}
	*/
	
	// hash cube:
	std::size_t operator()(const Cube& cube) const
	{
		size_t res = 17;
		for (int i = 0; i < cube.size(); ++i)
		{
			res = res * 31 + std::hash<int>()(cube[i].getLeft());
		}
		return res;
	}

private:



};
