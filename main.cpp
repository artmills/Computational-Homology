#include<iostream>
#include<vector>

#include "intmat.hpp"
#include "matsystem.hpp"
#include "homology.hpp"


IntMat CreateExample1()
{
	return IntMat(2, 4, 4, -6, 6, 12, 10, -4, -16);	
}
IntMat CreateExample2()
{
	IntMat ex(3, 5);
	std::vector<int> row0 = {1, 6, 3, 7, 2};
	std::vector<int> row1 = {0, 0, 2, 5, 1};
	std::vector<int> row2 = {0, 2, 5, 1, 2};
	ex.setRow(0, row0);
	ex.setRow(1, row1);
	ex.setRow(2, row2);
	return ex;
}
IntMat CreateExample3()
{
	IntMat ex(4, 4);
	std::vector<int> row0 = {1, 8, 8, 7};
	std::vector<int> row1 = {2, 0, 2, 5};
	std::vector<int> row2 = {0, 1, 3, 1};
	std::vector<int> row3 = {3, 2, 3, 9};
	ex.setRow(0, row0);
	ex.setRow(1, row1);
	ex.setRow(2, row2);
	ex.setRow(3, row3);
	return ex;
}


int main()
{
	std::cout << std::endl;
	
	/*IntMat A(3, 3);
	std::vector<int> Arow0 = {3, 2, 3};
	std::vector<int> Arow1 = {0, 2, 0};
	std::vector<int> Arow2 = {2, 2, 2};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);*/
	/*IntMat A(4, 3);
	std::vector<int> Arow0 = {0, 2, 2};
	std::vector<int> Arow1 = {1, 0, -1};
	std::vector<int> Arow2 = {3, 4, 1};
	std::vector<int> Arow3 = {5, 3, -2};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);*/
	//IntMat A = IntMat::CreateIdentity(3);

	IntMat A = CreateExample2();

	A.Print();
	Smith snf = MatSystem::GetSmithForm(A);
	snf.getB().Print();
	snf.getR().Print();
	snf.getQ().Print();
	
	/*
	std::vector<IntMat> ki = Homology::KernelImage(B);
	ki[0].Print();
	ki[1].Print();
	*/
}







