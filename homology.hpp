#pragma once

#include <iostream>
#include <chrono>

#include <givaro/givinteger.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/matrix/sparse-formats.h>
#include <linbox/solutions/smith-form.h>
#include <linbox/solutions/methods.h>
#include <linbox/algorithms/smith-form-adaptive.h>
#include <linbox/algorithms/smith-form-valence.h>
#include <fflas-ffpack/paladin/parallel.h>

#include "matsystem.hpp"
#include "smith.hpp"
#include "smithlite.hpp"
#include "quotient.hpp"

// LinBox typedefs:
typedef Givaro::ZRing<Givaro::Integer> Integers;
//typedef LinBox::SparseMatrix<Integers, LinBox::SparseMatrixFormat::COO> Matrix;
typedef LinBox::SparseMatrix<Integers> Matrix;
typedef LinBox::SmithList<Integers> SmithList;
typedef std::vector<std::pair<int, int>> List;

// implements algorithms to analyze matrices representing functions
// between finitely generated free abelian groups to compute homology
// groups.
namespace Homology
{
	// LinBox: global variable for the ring of integers.
	Integers ZZ;

	// LinBox: valence algorithm for Smith normal form.
	// Found as examples/smithsparce.c in the LinBox Github.
	List GetSmithForm(Matrix& A);	

	// returns the kernel and image of a matrix.
	// these are returned in the form of two matrices: the first
	// corresponds to the kernel and the second corresponds to the image.
	// each column of each matrix is a basis element of the subspace.
	std::vector<IntMat> KernelImage(IntMat& B);

	// solve the system Ax=b for x.
	// solutions do not always exist: return an empty vector if not.
	IntMat Solve(IntMat A, IntMat& b);
	IntMat Solve(IntMat A, std::vector<int>& b);

	// given a subgroup H of G with bases W of H and V of G,
	// get a matrix U that is a basis of G whose first s columns
	// represent trivial classes. the remaining columns have order
	// given by the correponding element in the matrix B.
	Quotient QuotientGroup(IntMat& W, IntMat& V);

	// the grand finale: given an array of matrices representing
	// homomorphisms between finitely generated abelian groups
	// compute the homology groups.
	std::vector<Quotient> HomologyGroupOfChainComplex(std::vector<IntMat>& matrices);

	// parse the information given by HomologyGroupOfChainComplex.
	void AnalyzeHomology(std::vector<Quotient> groups);
	void AnalyzeHomologyRaw(std::vector<Quotient> groups);

	std::vector<std::vector<int>> GetHomology(std::vector<IntMat>& boundaries);

	// LinBox version.
	std::vector<std::vector<int>> GetHomologyLinBox(std::vector<Matrix>& boundaries);
	std::vector<std::vector<int>> GetHomologyValence(std::vector<Matrix>& boundaries);
	
	void AnalyzeHomology(std::vector<std::vector<int>> homologies);

	// D is the boundary map D_{i+1}:C_{i+1} -> C_i.
	// rankd is the rank of the boundary map D_i: C_i -> C_{i-1}.
	std::vector<int> GetIthHomology(SmithLite& D, int rankd);

	// LinBox version.
	std::vector<int> GetIthHomologyLinBox(SmithList& sl, int s, int t, int rows, int rankd);
	std::vector<int> GetIthHomologyLinBox(List& sl, int s, int t, int rows, int rankd);
}
