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
	MatSystem system;

	std::vector<int> Arow0 = {3, 2, 1, 4};
	std::vector<int> Arow1 = {2, 3, 1, -1};
	std::vector<int> Arow2 = {4, 4, -2, -2};
	IntMat A(3, 4);
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.Print();
	
	IntMat Q = IntMat::CreateIdentity(3, 3);
	IntMat Qinv = Q;

	system.RowReduce(A, Q, Qinv, 0, 0);
	A.Print();

	system.RowReduce(A, Q, Qinv, 1, 1);
	A.Print();

	//system.RowEchelon(A);
	//A.Print();

	/*auto v = A.getSubColumn(3, 3, 3);
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << std::endl;
		if (v[i] != 0)
		{
			std::cout << "false" << std::endl;
		}
	}*/

	//system.RowReduce(A, Id3, Id3inv, 0, 0);
	//A.Print();
	//Id3.Print();
	//Id3inv.Print();

	/*
	std::vector<int> Arow0 = {3, 2, 3};
	std::vector<int> Arow1 = {0, 2, 0};
	std::vector<int> Arow2 = {2, 2, 2};
	IntMat A(3, 3);
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);

	std::vector<int> Qrow0 = {1, 0, 0};
	std::vector<int> Qrow1 = {-2, 3, 1};
	std::vector<int> Qrow2 = {0, 1, 0};
	IntMat Q(3, 3);
	Q.setRow(0, Qrow0);
	Q.setRow(1, Qrow1);
	Q.setRow(2, Qrow2);

	std::vector<int> Qinvrow0 = {1, 0, 0};
	std::vector<int> Qinvrow1 = {0, 0, 1};
	std::vector<int> Qinvrow2 = {2, 1, -3};
	IntMat Qinv(3, 3);
	Qinv.setRow(0, Qinvrow0);
	Qinv.setRow(1, Qinvrow1);
	Qinv.setRow(2, Qinvrow2);

	std::vector<int> Rrow0 = {1, -2, -1};
	std::vector<int> Rrow1 = {-1, 3, 0};
	std::vector<int> Rrow2 = {0, 0, 1};
	IntMat R(3, 3);
	R.setRow(0, Rrow0);
	R.setRow(1, Rrow1);
	R.setRow(2, Rrow2);

	std::vector<int> Rinvrow0 = {3, 2, 3};
	std::vector<int> Rinvrow1 = {1, 1, 1};
	std::vector<int> Rinvrow2 = {0, 0, 1};
	IntMat Rinv(3, 3);
	Rinv.setRow(0, Rinvrow0);
	Rinv.setRow(1, Rinvrow1);
	Rinv.setRow(2, Rinvrow2);

	IntMat temp = A * R;
	IntMat B = Qinv * temp;
	B.Print();

	system.PartColumnReduce(B, R, Rinv, 0, 0);

	IntMat temp2 = A * R;
	IntMat Bp = Qinv * temp2;
	Bp.Print();
	*/
}

