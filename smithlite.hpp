#pragma once

#include <iostream>
#include "intmat.hpp"

// container for just the matrix B and integers given by the Smith 
// Normal Form.
struct SmithLite
{

public:

	SmithLite(IntMat& B, int s, int t);
	~SmithLite();

	IntMat& getB();
	int& getS();
	int& getT();

private:

	std::vector<IntMat> B;
	int s;
	int t;

};
