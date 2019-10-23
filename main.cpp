#include<iostream>
#include<vector>

#include "intmat.hpp"
#include "matsystem.hpp"
#include "homology.hpp"


void PrintMatrix(std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[0].size(); ++j)
		{
			std::cout << matrix[i][j] << std::endl;
		}
	}
}



int main()
{
	std::cout << std::endl;
	
	IntMat A(4, 8);
	std::vector<int> Arow0 = {1, 2, 6, 3, 8, 9, 3, 8};
	std::vector<int> Arow1 = {6, 3, 7, 4, 7, 9, 2, 16};
	std::vector<int> Arow2 = {6, 8, 0, 3, 21, 5, 7, 9};
	std::vector<int> Arow3 = {6, 8, 4, 2, 4, 65, 7, 1};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);

	IntMat B = MatSystem::Transpose(A);

	B.Print();
	Smith snf = MatSystem::GetSmithForm(B);
	snf.getB().Print();	
	snf.getQ().Print();	
	snf.getQinv().Print();	
	snf.getR().Print();	
	snf.getRinv().Print();	

	IntMat temp = B * snf.getR();
	IntMat s = snf.getQinv() * temp;
	s.Print();
}

