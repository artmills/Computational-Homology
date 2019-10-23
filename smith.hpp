#pragma once

#include <iostream>
#include "intmat.hpp"

// container for the matrices and integers given by the Smith Normal Form.
struct Smith
{

public:

	Smith(IntMat& B, IntMat& Q, IntMat& Qinv, IntMat& R, IntMat& Rinv, int s, int t);
	~Smith();

	IntMat& getB();
	IntMat& getQ();
	IntMat& getQinv();
	IntMat& getR();
	IntMat& getRinv();
	int& getS();
	int& getT();

private:

	std::vector<IntMat> matrices;
	int s;
	int t;

};
