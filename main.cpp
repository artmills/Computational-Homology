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
IntMat CreateExample4()
{
	IntMat ex(4, 4);
	std::vector<int> row0 = {-6, 111, -36, 6};
	std::vector<int> row1 = {5, -672, 210, 74};
	std::vector<int> row2 = {0, -255, 81, 24};
	std::vector<int> row3 = {-7, 255, -81, -10};
	ex.setRow(0, row0);
	ex.setRow(1, row1);
	ex.setRow(2, row2);
	ex.setRow(3, row3);
	ex.setRow(0, row0);
	return ex;
}
IntMat CreateExample5()
{
	IntMat A(3, 3);
	std::vector<int> Arow0 = {3, 2, 3};
	std::vector<int> Arow1 = {0, 2, 0};
	std::vector<int> Arow2 = {2, 2, 2};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	return A;
}

int main()
{
	std::cout << std::endl;
	
	IntMat A = CreateExample5();
	IntMat P2(1, 3);
	IntMat P0(3, 1);
	std::vector<IntMat> boundaryMaps;
	boundaryMaps.push_back(P0);
	boundaryMaps.push_back(A);
	boundaryMaps.push_back(P2);

	std::vector<Quotient> homologies = Homology::HomologyGroupOfChainComplex(boundaryMaps);
}







