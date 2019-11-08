#pragma once

#include <iostream>
#include <unordered_set>
#include "cube.hpp"
#include "keyhasher.hpp"

// responsible for performing operations on cubes.
namespace CubeSystem
{

	// 3.70: compute the primary faces of a given cube.
	std::unordered_map<Cube, int, KeyHasher> PrimaryFaces(Cube Q);
	







}
