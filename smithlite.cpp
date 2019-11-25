#include "smithlite.hpp"


SmithLite::SmithLite(IntMat& B, int s, int t)
{
	this->B.push_back(B);
	this->s = s;
	this->t = t;
}
SmithLite::~SmithLite(){}

IntMat& SmithLite::getB()
{
	return B[0];
}
int& SmithLite::getS()
{
	return s;
}
int& SmithLite::getT()
{
	return t;
}
