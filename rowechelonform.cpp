#include "rowechelonform.hpp"


RowEchelonForm::RowEchelonForm(IntMat& B, IntMat& Q, IntMat& Qinv, int k)
{
	this->matrices.push_back(B);
	this->matrices.push_back(Q);
	this->matrices.push_back(Qinv);
	this->k=k;
}
RowEchelonForm::~RowEchelonForm()
{

}


IntMat& RowEchelonForm::getB()
{
	return matrices[0];
}
IntMat& RowEchelonForm::getQ()
{
	return matrices[1];
}
IntMat& RowEchelonForm::getQinv()
{
	return matrices[2];
}
int& RowEchelonForm::getK()
{
	return k;
}


void RowEchelonForm::Print()
{
	for (int i = 0; i < matrices.size(); ++i)
	{
		matrices[i].Print();
	}
	std::cout << k << std::endl;
}
