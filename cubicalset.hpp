#pragma once

#include <unordered_map>
#include "keyhasher.hpp"
#include "cube.hpp"

// an unordered map of cubes.
// we use an unordered map so that we can perform set-theoretic unions
class CubicalSet
{

public:

	CubicalSet(std::vector<Cube> cubes);
	CubicalSet();
	~CubicalSet();

	// warning: this method pops a RANDOM element from the
	// cube map!
	Cube Pop();

	// size of the largest cube.
	int Dimension();

	bool isEmpty();
	std::unordered_map<Cube, int, KeyHasher> cubes;

	void Print();

private:

	int dimension = 0;

};
