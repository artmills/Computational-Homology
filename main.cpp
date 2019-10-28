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
	
	/*IntMat A(3, 3);
	std::vector<int> Arow0 = {3, 2, 3};
	std::vector<int> Arow1 = {0, 2, 0};
	std::vector<int> Arow2 = {2, 2, 2};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);*/
	IntMat A(4, 3);
	std::vector<int> Arow0 = {0, 0, 0};
	std::vector<int> Arow1 = {0, 0, 0};
	std::vector<int> Arow2 = {0, 0, 0};
	std::vector<int> Arow3 = {0, 0, 0};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);

	A.Print();
	Smith snf = MatSystem::GetSmithForm(A);

	std::vector<IntMat> ki = Homology::KernelImage(A);
	ki[0].Print();
	ki[1].Print();
	
}

