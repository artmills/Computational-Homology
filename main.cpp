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
	//A.Print();
	
	/*
	std::vector<IntMat> kernel_image = system.KernelImage(A);	
	for (int i = 0; i < kernel_image.size(); ++i)
	{
		kernel_image[i].Print();
	}
	*/

	/*
	IntMat A1(3, 3);
	std::vector<int> A1row0 = {3, 2, 3};
	std::vector<int> A1row1 = {0, 2, 0};
	std::vector<int> A1row2 = {2, 2, 2};
	A1.setRow(0, A1row0);
	A1.setRow(1, A1row1);
	A1.setRow(2, A1row2);
	std::cout << "Matrix A: " << std::endl;
	A1.Print();

	
	IntMat B(3, 3);
	std::vector<int> Brow0 = {1, 0, 0};
	std::vector<int> Brow1 = {0, 2, 0};
	std::vector<int> Brow2 = {0, 0, 0};
	B.setRow(0, Brow0);
	B.setRow(1, Brow1);
	B.setRow(2, Brow2);
	std::cout << "Matrix B: " << std::endl;
	B.Print();

	IntMat R(3, 3);
	std::vector<int> Rrow0 = {1, -2, -1};
	std::vector<int> Rrow1 = {-1, 3, 0};
	std::vector<int> Rrow2 = {0, 0, 1};
	R.setRow(0, Rrow0);
	R.setRow(1, Rrow1);
	R.setRow(2, Rrow2);
	std::cout << "Matrix R: " << std::endl;
	R.Print();

	IntMat Rinv(3, 3);
	std::vector<int> Rinvrow1 = {3, 2, 3};
	std::vector<int> Rinvrow2 = {1, 1, 1};
	std::vector<int> Rinvrow3 = {0, 0, 1};
	Rinv.setRow(0, Rinvrow1);
	Rinv.setRow(1, Rinvrow2);
	Rinv.setRow(2, Rinvrow3);
	std::cout << "Matrix Rinv: " << std::endl;
	R.Print();

	IntMat Q(3, 3);
	std::vector<int> Qrow0 = {1, 0, 0};
	std::vector<int> Qrow1 = {-2, 3, 1};
	std::vector<int> Qrow2 = {0, 1, 0};
	Q.setRow(0, Qrow0);
	Q.setRow(1, Qrow1);
	Q.setRow(2, Qrow2);
	std::cout << "Matrix Q: " << std::endl;
	Q.Print();
	
	IntMat P(3, 3);
	std::vector<int> Prow0 = {1, 0, 0};
	std::vector<int> Prow1 = {0, 0, 1};
	std::vector<int> Prow2 = {2, 1, -3};
	P.setRow(0, Prow0);
	P.setRow(1, Prow1);
	P.setRow(2, Prow2);
	std::cout << "Matrix P: " << std::endl;
	P.Print();

	IntMat Qinv = P;
	std::cout << "Matrix Qinv: " << std::endl;
	Qinv.Print();

	std::cout << "Smith Normal Form:" << std::endl;
	std::vector<IntMat> smith = system.GetSmithForm(A1);
	for (int i = 0; i < smith.size(); ++i)
	{
		smith[i].Print();
	}
	*/

	IntMat X(4, 4);
	std::vector<int> row0 = {-6, 111, -36, 6};
	std::vector<int> row1 = {5, -672, 210, 74};
	std::vector<int> row2 = {0, -255, 81, 24};
	std::vector<int> row3 = {-7, 255, -81, -10};
	X.setRow(0, row0);
	X.setRow(1, row1);
	X.setRow(2, row2);
	X.setRow(3, row3);
	X.Print();

	system.SmithForm(X);
	std::cout << "Smith form: " << std::endl;
	X.Print();

}

