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
	
	IntMat P1(2, 3);
	std::vector<int> P1row0 = {1, 1, 0};
	std::vector<int> P1row1 = {-1, -1, 0};
	P1.setRow(0, P1row0);
	P1.setRow(1, P1row1);

	IntMat P2(3, 2);
	std::vector<int> P2row0 = {-1, 1};
	std::vector<int> P2row1 = {1, -1};
	std::vector<int> P2row2 = {1, 1};
	P2.setRow(0, P2row0);
	P2.setRow(1, P2row1);
	P2.setRow(2, P2row2);

	P1.Print();
	P2.Print();

	std::vector<IntMat> matrices = {P1, P2};
	
	std::vector<IntMat> ki1 = Homology::KernelImage(P1);
	std::vector<IntMat> ki2 = Homology::KernelImage(P2);

	/*std::cout << "Partial 1: " << std::endl;
	ki1[0].Print();
	ki1[1].Print();
	std::cout << "Partial 2: " << std::endl;
	ki2[0].Print();
	ki2[1].Print();*/

	/*
	Quotient q = Homology::QuotientGroup(ki1[0], ki2[1]);
	q.getU().Print();
	q.getB().Print();
	std::cout << q.getS() << std::endl;
	*/
	std::vector<Quotient> homologies = Homology::HomologyGroupOfChainComplex(matrices);
	for (int i = 0; i < homologies.size(); ++i)
	{
		std::cout << "Homology group H_" << i << std::endl;
		homologies[i].getU().Print();
		homologies[i].getB().Print();
		std::cout << homologies[i].getS() << std::endl;
		std::cout << std::endl;
	}
}







