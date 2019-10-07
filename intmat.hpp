#pragma once
#include <iostream>
#include <vector>

// integer matrix implementation.
// this is only a container for data.
// more complex matrix operations should be implemented elsewhere.
struct IntMat
{

public:

	// constructors/destructor:
	IntMat(int rows, int columns); // zero matrix
	IntMat(int a, int b, int c, int d); // 2 by 2
	IntMat(int a11, int a12, int a13,
		   int a21, int a22, int a23,
		   int a31, int a32, int a33); // 3 by 3
	~IntMat();

	// initializing a matrix row by row or column by column:
	void setRow(int row, std::vector<int> data);
	void setColumn(int column, std::vector<int> data);

	// getters/setters for rows/columns/elements:
	int getRows();
	int getColumns();
	int getElement(int row, int column);
	void setElement(int row, int column, int data);
	std::vector<int> getRow(int row);
	std::vector<int> getColumn(int column);

	// getters for sub{matrix,column,row}:
	IntMat getSubMatrix(int rowStart, int rowEnd, int columnStart, int columnEnd);
	std::vector<int> getSubRow(int row, int start, int end);
	std::vector<int> getSubColumn(int column, int start, int end);
	
	// utility:
	void Print();
	static IntMat CreateIdentity(int size);
	static IntMat CreateIdentity(int rows, int columns);

	// matrix ring operations:
	static IntMat Sum(IntMat& left, IntMat& right);
	static IntMat Product(IntMat& left, IntMat& right);

private:

	// data: the actual entries of the matrix are stored here.
	std::vector<std::vector<int>> matrix;

};

// operator overloads:

// pointwise addition
IntMat operator+(IntMat& left, IntMat& right);

// matrix multiplication
IntMat operator*(IntMat& left, IntMat& right);
