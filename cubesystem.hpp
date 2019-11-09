#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include "cube.hpp"
#include "typedef.hpp"
#include "keyhasher.hpp"
#include "cubicalset.hpp"
#include "intmat.hpp"

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

	// we have been using unordered maps up to this point. at some point
	// we need to fix a coordinate system so we can create matrices.
	// this function simply converts an unordered map into an array.
	std::vector<Cube> GetCoordinates(std::unordered_map<Cube, int, KeyHasher> map);
	
	// 3.73: compute the boundary of a cube as a chain.
	// the next algorithm will put this chain into the form of a matrix.
	Chain BoundaryOperator(Cube Q);

	// 3.75: translate the output of the previous function into a matrix.
	std::vector<IntMat> BoundaryOperatorMatrix(std::vector<std::vector<Cube>> E);




}
