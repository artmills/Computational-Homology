#pragma once

#include <iostream>
#include "intmat.hpp"

// container for quotient group information.
struct Quotient
{

public:

	Quotient(IntMat& U, IntMat& B, int s);
	~Quotient();

	IntMat& getU();
	IntMat& getB();
	int& getS();

private:

	std::vector<IntMat> matrices;
	int s;

};
