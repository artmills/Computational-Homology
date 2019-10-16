#include<iostream>
#include<vector>

#include "intmat.hpp"
#include "matsystem.hpp"


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

	MatSystem system;

	/*
	std::vector<int> Arow0 = {1, 3, 0, 2, 6, 3, 1};
	std::vector<int> Arow1 = {-2, -6, 0, -2, -8, 3, 1};
	std::vector<int> Arow2 = {3, 9, 0, 0, 6, 6, 2};
	std::vector<int> Arow3 = {-1, -3, 0, 1, 0, 9, 3};
	IntMat A(4, 7);
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);

	A.Print();
	*/
	
	std::vector<int> Arow0 = {0, 2, 2};
	std::vector<int> Arow1 = {1, 0, -1};
	std::vector<int> Arow2 = {3, 4, 1};
	std::vector<int> Arow3 = {5, 3, -2};
	
	/*
	std::vector<int> Arow0 = {3, 2, 1, 4};
	std::vector<int> Arow1 = {2, 3, 1, -1};
	std::vector<int> Arow2 = {4, 4, -2, -2};
	//std::vector<int> Arow2 = {0, 0, 0, 0};
	*/

	IntMat A(4, 3);
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);

	/*
	std::vector<int> Arow0 = {0, 2, 0, 7, 3};
	std::vector<int> Arow1 = {0, 0, 1, 0, 11};
	std::vector<int> Arow2 = {0, 0, 0, 0, 7};
	std::vector<int> Arow3 = {0, 0, 0, 0, 0};
	std::vector<int> Arow4 = {0, 0, 0, 0, 0};
	IntMat A(5, 5);
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);
	A.setRow(4, Arow4);
	*/


	//system.RowEchelon(A);
	A.Print();
	
	std::vector<IntMat> kernel_image = system.KernelImage(A);	
	for (int i = 0; i < kernel_image.size(); ++i)
	{
//		kernel_image[i].Print();
	}

	IntMat Q = IntMat::CreateIdentity(A.getRows());
	system.MoveMinNonzero(A, Q, Q, Q, Q, 0);
	A.Print();

	A.setElement(0, 0, 12);
	auto test = system.CheckForDivisibility(A, 0);
	system.PrintVector(test);
}

