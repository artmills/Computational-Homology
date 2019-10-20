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

	std::vector<int> Arow0 = {0, 2, 2};
	std::vector<int> Arow1 = {1, 0, -1};
	std::vector<int> Arow2 = {3, 4, 1};
	std::vector<int> Arow3 = {5, 3, -2};
	IntMat A(4, 3);
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);

	A.Print();
	auto kernel_image = Homology::KernelImage(A);
	kernel_image[0].Print();
	kernel_image[1].Print();


}

