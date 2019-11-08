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

	std::unordered_map<Cube, int, KeyHasher> cubes;

private:


};
