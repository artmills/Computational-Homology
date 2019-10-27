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
	
	IntMat A(4, 4);
	std::vector<int> Arow0 = {1, 2, 6, 3};
	std::vector<int> Arow1 = {5, 7, 3, 7};
	std::vector<int> Arow2 = {1, 0, 2, 0};
	std::vector<int> Arow3 = {1, 4, 8, 2};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	A.setRow(3, Arow3);

	A.Print();
	Smith snf = MatSystem::GetSmithForm(A);
	
	std::cout << "B:" << std::endl;
	snf.getB().Print();	

	std::cout << "Q:" << std::endl;
	snf.getQ().Print();	

	std::cout << "Qinv:" << std::endl;
	snf.getQinv().Print();	

	std::cout << "R:" << std::endl;
	snf.getR().Print();	

	std::cout << "Rinv:" << std::endl;
	snf.getRinv().Print();	

	std::cout << "Q * Qinv:" << std::endl;
	IntMat QQinv = snf.getQ() * snf.getQinv();
	QQinv.Print();

	std::cout << "R * Rinv:" << std::endl;
	IntMat RRinv = snf.getR() * snf.getRinv();
	RRinv.Print();

	std::cout << "Qinv * A * R:" << std::endl;
	IntMat temp = A * snf.getR();
	IntMat result = snf.getQinv() * temp;
	result.Print();
}

