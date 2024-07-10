#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>

#include <givaro/givinteger.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/matrix/sparse-formats.h>

#include "cube.hpp"
#include "keyhasher.hpp"
#include "cubicalset.hpp"
#include "intmat.hpp"
#include "homology.hpp"
#include "grid.hpp"

typedef std::vector<std::vector<Cube>> ChainComplex;
typedef std::unordered_map<Cube, int, KeyHasher> Chain;
typedef std::unordered_map<Cube, Chain, KeyHasher> Boundary;
typedef std::vector<Boundary> BoundaryMap;

// Linbox typedefs for convenience.
typedef Givaro::ZRing<Givaro::Integer> Integers;
typedef LinBox::SparseMatrix<Integers> Matrix;
//typedef LinBox::SparseMatrix<Integers, LinBox::SparseMatrixFormat::COO> Matrix;

// responsible for performing operations on cubes.
namespace CubeSystem
{
	// LinBox: global variable for the ring of integers.
	Integers ZZ;

	// LinBox:: print method to help debug matrix.
	void Print(Matrix& m);

	// 3.66: convert a chain to a coordinate vector.
	std::vector<int> CanonicalCoordinates(Chain& c, std::vector<Cube>& cubes);

	// 3.68: convert a coordinate vector to a chain.
	Chain ChainFromCanonicalCoordinates(std::vector<int>& v, std::vector<Cube>& cubes);	

	// 3.70: compute the primary faces of a given cube.
	std::unordered_map<Cube, int, KeyHasher> PrimaryFaces(Cube& Q);

	// 3.71: compute the generators of C_k(X) for a cubical
	// set X and for each integer k up to the dimension of X.
	std::vector<std::unordered_map<Cube, int, KeyHasher>> CubicalChainGroups(CubicalSet& K);

	// we have been using unordered maps up to this point. at some point
	// we need to fix a coordinate system so we can create matrices.
	// this function simply converts an unordered map into an array.
	std::vector<Cube> GetCoordinates(std::unordered_map<Cube, int, KeyHasher>& map);
	
	// 3.73: compute the boundary of a cube as a chain.
	// the next algorithm will put this chain into the form of a matrix.
	Chain BoundaryOperator(Cube& Q);

	// testing: get an array of boundary operators to use for the
	// reduction algorithm.
	BoundaryMap Boundaries(ChainComplex& E);

	// 3.75: translate the output of the previous function into a matrix.
	std::vector<IntMat> BoundaryOperatorMatrix(std::vector<std::vector<Cube>>& E);
	std::vector<IntMat> BoundaryOperatorMatrix(std::vector<std::vector<Cube>>& E, BoundaryMap& bd);

	// LinBox versions.
	std::vector<Matrix> BoundaryOperatorMatrixLinBox(std::vector<std::vector<Cube>>& E);
	std::vector<Matrix> BoundaryOperatorMatrixLinBox(std::vector<std::vector<Cube>>& E, BoundaryMap& bd);


	// THE GRAND FINALE!
	// 3.78: we won't bother with algorithm 3.77 at the moment.
	// we're only interested in the orders of the homology groups, not 
	// the chain bases.
	std::vector<std::vector<int>> GetHomology(CubicalSet& K, bool CCR); 

	// LinBox version.
	std::vector<std::vector<int>> GetHomologyLinBox(CubicalSet& K, bool CCR); 

	void Homology(CubicalSet& K, bool CCR); 
	
	// utility.
	void RemoveElementFromVector(std::vector<Cube>& v, Cube& e);

	// 4.30: one step of the chain reduction algorithm.
	// given a reduction pair (a, b) of cubes of dimension (i-1, i).
	void Reduce(ChainComplex& E, BoundaryMap& Bd, int i, Cube& a, Cube& b); 
	// 4.32: perform chain reduction.
	void ReduceChainComplex(ChainComplex& E, BoundaryMap& bd);
	
	int ScalarProduct(Chain& c1, Chain& c2);


	// given a grid create an array of cubes representing the cubical set.
	CubicalSet GetCubicalSet(Grid& grid);
	CubicalSet GetCubicalSet(Grid3D& block);
}
