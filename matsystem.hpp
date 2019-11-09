#pragma once
#include <cmath>
#include <limits>
#include "intmat.hpp"
#include "rowechelonform.hpp"
#include "smith.hpp"


// responsible for performing operations on matrices. these include:
// * row operations
// * inversion
// * ultimately, computing the Smith normal form
namespace MatSystem
{
	// operations on matrices:
	IntMat Transpose(IntMat& matrix);


	// Fancy elementary row operations that keep track of 
	// the bases of a homomorphism f: X \to Y
	// and how they change on those same row operations.
	// Given by algorithms 3.15, 3.16, 3.17.
	void RowExchangeOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int row1, int row2);
	void ColumnExchangeOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int column1, int column2);
	
	void RowMultiplyOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int row);
	void ColumnMultiplyOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int column);

	void RowAddOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int targetRow, int givenRow, int scalar);
	void ColumnAddOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int targetColumn, int givenColumn, int scalar);


	// Row reduction algorithms:
	
	// partial row reduction: algorithm 3.29
	// for a matrix B that satisfies the (k-1, l-1) criterion of
	// row echelon form and B[k, l] != 0.
	void PartRowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l);
	void PartColumnReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l);

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

	// utility algorithm to check if a matrix is zero:
	bool IsZero(IntMat& B);
	bool IsZero(IntMat B);

	// algorithm 3.36: row reduce the first column
	void RowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l);
	
	// algorithm 3.39: put a matrix into row echelon form
	void RowEchelon(IntMat& B);
	RowEchelonForm GetRowEchelon(IntMat B);


	// applications of the row echelon form.
	std::vector<IntMat> KernelImage(IntMat B);



	/*********** Preparing for the Smith Normal Form **********/

	// get minimal nonzero in submatrix beginning at row/column k.
	std::vector<int> MinNonzero(IntMat& B, int k);

	// move minimal nonzero entry to the (k, k) position.
	void MoveMinNonzero(IntMat& B, IntMat& Q, IntMat& Qinv, IntMat& R, IntMat& Rinv, int k);

	// check whether the (k, k) entry divides all entries in the remaining
	// submatrix. if not, get the coordinates of the entry that sucks.
	std::vector<int> CheckForDivisibility(IntMat& B, int k);

	// step one of the Smith normal form procedure.
	void PartSmithForm(IntMat& B, IntMat& Q, IntMat& Qinv, IntMat& R, IntMat& Rinv, int k);

	// full Smith normal form algorithm.
	void SmithForm(IntMat& B);
	Smith GetSmithForm(IntMat B);











	// utility:	
	void Print(std::vector<int> vector);

	// elementary row operations:
	void RowExchange(IntMat& matrix, int row1, int row2);
	void ColumnExchange(IntMat& matrix, int column1, int column2);

	void RowMultiply(IntMat& matrix, int row, int scalar);
	void ColumnMultiply(IntMat& matrix, int column, int scalar);

	void RowAdd(IntMat& matrix, int targetRow, int givenRow, int scalar);
	void ColumnAdd(IntMat& matrix, int targetColumn, int givenColumn, int scalar);

	
}
