#pragma once

#include <iostream>
#include "matsystem.hpp"

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
	IntMat Solve(IntMat& A, IntMat& b);





}
