#include "quotient.hpp"


Quotient::Quotient(IntMat& U, IntMat& B, int s)
{
	this->matrices.push_back(U);
	this->matrices.push_back(B);
	this->s = s;
}
Quotient::~Quotient()
{

}


IntMat& Quotient::getU()
{
	return matrices[0];
}
IntMat& Quotient::getB()
{
	return matrices[1];
}
int& Quotient::getS()
{
	return this->s;
}
