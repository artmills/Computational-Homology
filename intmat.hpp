#pragma once
#include<iostream>
#include<vector>

// Integer matrix implementation.
struct IntMat
{

public:

	IntMat(int rows, int columns);
	~IntMat();

	// initializing a matrix.
	void setRow(int row, std::vector<int> data);
	void setColumn(int column, std::vector<int> data);
	void Print();

	// getters/setters:
	
	int getRows();
	int getColumns();
	int getElement(int row, int column);
	void setElement(int row, int column, int data);
	std::vector<int> getRow(int row);
	std::vector<int> getColumn(int column);

	IntMat getSubMatrix(int rowStart, int rowEnd, int columnStart, int columnEnd);
	std::vector<int> getSubRow(int row, int start, int end);
	std::vector<int> getSubColumn(int column, int start, int end);
	
	static IntMat CreateIdentity(int rows, int columns);

private:

	int rows,columns;
	std::vector<std::vector<int>> matrix;

};

// operator overloads:

// pointwise addition
IntMat operator+(IntMat& left, IntMat& right);

// matrix multiplication
IntMat operator*(IntMat& left, IntMat& right);
