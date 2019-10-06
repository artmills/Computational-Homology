#pragma once
#include <cmath>
#include <limits>
#include "intmat.hpp"


// responsible for performing operations on matrices. these include:
// * row operations
// * inversion
// * ultimately, computing the Smith normal form
class MatSystem
{

public:

	MatSystem();
	~MatSystem();

	// operations on matrices:
	IntMat Add(IntMat& left, IntMat& right);
	IntMat Multiply(IntMat& left, IntMat& right);
	void ScalarMultiple(IntMat& matrix, int scalar);
	IntMat Transpose(IntMat& matrix);

	// elementary row operations:
	void RowExchange(IntMat& matrix, int row1, int row2);
	void ColumnExchange(IntMat& matrix, int column1, int column2);

	void RowMultiply(IntMat& matrix, int row, int scalar);
	void ColumnMultiply(IntMat& matrix, int column, int scalar);

	void RowAdd(IntMat& matrix, int targetRow, int givenRow, int scalar);
	void ColumnAdd(IntMat& matrix, int targetColumn, int givenColumn, int scalar);

	// algorithms 3.15, 3.16, 3.17
	// these perform row/column operations on a matrix B = Qinverse*A*R
	// while keeping track of the bases
	void RowExchangeOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int row1, int row2);
	void ColumnExchangeOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int column1, int column2);
	
	// quick note: 
	// we can only consider multiplication by \pm 1 as an elementary
	// row or column operation. this is because in the integers,
	// \pm 1 are the only numbers with multiplicative inverses.
	// we will therefore hardcode these values in the definitions of
	// the row/column multiply operations.
	void RowMultiplyOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int row);
	void ColumnMultiplyOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int column);

	void RowAddOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int targetRow, int givenRow, int scalar);
	void ColumnAddOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int targetColumn, int givenColumn, int scalar);


	// row reduction algorithms:
	
	// partial row reduction: algorithm 3.29
	// for a matrix B that satisfies the (k-1, l-1) criterion of
	// row echelon form and B[k, l] != 0.
	void PartRowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l);

	// algorithm 3.32: find smallest nonzero entry of a vector
	// returning the INDEX of where that min value is located
	int IndexSmallestNonzero(std::vector<int> v, int start);

	// algorithm 3.33: find the smallest entry in the given
	// row piece and swap it
	// l is the column where we find the smallest nonzero entry.
	// k is the row where we start looking for the smallest
	// entry, as well as the row number that we will swap the 
	// smallest entry to.
	void RowPrepare(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l);

	// utility algorithm to check if an std::vector is zero:
	bool IsZero(std::vector<int> a);

	// algorithm 3.36: row reduce the first column
	void RowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l);
	
	// algorithm 3.39: put a matrix into row echelon form
	void RowEchelon(IntMat& B);
	std::vector<IntMat> GetRowEchelon(IntMat B);


private:
	
	void PrintVector(std::vector<int> vector);

};
