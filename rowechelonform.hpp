#pragma once

#include <iostream>
#include <vector>
#include "intmat.hpp"

// Container for the necessary components of a matrix in row echelon form.
struct RowEchelonForm
{

public:

	RowEchelonForm(IntMat& B, IntMat& Q, IntMat& Qinv, int k);
	~RowEchelonForm();

	IntMat& getB();
	IntMat& getQ();
	IntMat& getQinv();
	int& getK();

	// utility:
	void Print();

private:

	std::vector<IntMat> matrices;
	int k;

};
