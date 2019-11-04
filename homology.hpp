#pragma once

#include <iostream>
#include "matsystem.hpp"
#include "smith.hpp"
#include "quotient.hpp"

// implements algorithms to analyze matrices representing functions
// between finitely generated free abelian groups to compute homology
// groups.
namespace Homology
{


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

}
