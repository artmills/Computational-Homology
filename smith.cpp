#include "smithform.hpp"


Smith::Smith(IntMat& B, IntMat& Q, IntMat& Qinv, IntMat& R, IntMat& Rinv, int s, int t)
{
	matrices.push_back(B);
	matrices.push_back(Q);
	matrices.push_back(Qinv);
	matrices.push_back(R);
	matrices.push_back(Rinv);
	this->s = s;
	this->t = t;
}
Smith::~Smith(){}

IntMat Smith::getB()
{
	return matrices[0];
}
IntMat Smith::getQ()
{
	return matrices[1];
}
IntMat Smith::getQinv()
{
	return matrices[2];
}
IntMat Smith::getR()
{
	return matrices[3];
}
IntMat Smith::getRinv()
{
	return matrices[4];
}
int Smith::getS()
{
	return s;
}
int Smith::getT()
{
	return t;
}
