#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include "cube.hpp"
#include "chain.hpp"
#include "keyhasher.hpp"
#include "cubicalset.hpp"

// responsible for performing operations on cubes.
namespace CubeSystem
{

	// 3.66: convert a chain to a coordinate vector.
	std::vector<int> CanonicalCoordinates(Chain c, std::vector<Cube> cubes);

	// 3.68: convert a coordinate vector to a chain.
	Chain ChainFromCanonicalCoordinates(std::vector<int> v, std::vector<Cube> cubes);	

	// 3.70: compute the primary faces of a given cube.
	std::unordered_map<Cube, int, KeyHasher> PrimaryFaces(Cube Q);

	// 3.71: compute the generators of C_k(X) for a cubical
	// set X and for each integer k up to the dimension of X.
	std::vector<std::unordered_map<Cube, int, KeyHasher>> CubicalChainGroups(CubicalSet K);
	







}
