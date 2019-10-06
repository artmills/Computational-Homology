#include "matsystem.hpp"


MatSystem::MatSystem(){}
MatSystem::~MatSystem(){}


IntMat MatSystem::Add(IntMat& left, IntMat& right)
{
	return left + right;
}
IntMat MatSystem::Multiply(IntMat& left, IntMat& right)
{
	return left * right;
}
void MatSystem::ScalarMultiple(IntMat& matrix, int scalar)
{
	for (int i = 0; i < matrix.getRows(); ++i)
	{
		for (int j = 0; j < matrix.getColumns(); ++j)
		{
			matrix.setElement(i, j, matrix.getElement(i, j) * scalar);
		}
	}
}

IntMat MatSystem::Transpose(IntMat& matrix)
{
	IntMat transpose(matrix.getColumns(), matrix.getRows());	
	for (int i = 0; i < transpose.getRows(); ++i)
	{
		transpose.setRow(i, matrix.getColumn(i));
	}
	return transpose;
}


void MatSystem::RowExchange(IntMat& matrix, int row1, int row2)
{
	std::vector<int> temp = matrix.getRow(row1);
	matrix.setRow(row1, matrix.getRow(row2));
	matrix.setRow(row2, temp);
}
void MatSystem::ColumnExchange(IntMat& matrix, int column1, int column2)
{
	std::vector<int> temp = matrix.getColumn(column1);
	matrix.setColumn(column1, matrix.getColumn(column2));
	matrix.setColumn(column2, temp);
}


void MatSystem::RowMultiply(IntMat& matrix, int row, int scalar)
{
	std::vector<int> tempRow = matrix.getRow(row);
	for (int i = 0; i < tempRow.size(); ++i)
	{
		tempRow[i] *= scalar;
	}
	matrix.setRow(row, tempRow);
}
void MatSystem::ColumnMultiply(IntMat& matrix, int column, int scalar)
{
	std::vector<int> tempColumn = matrix.getColumn(column);
	for (int i = 0; i < tempColumn.size(); ++i)
	{
		tempColumn[i] *= scalar;
	}
	matrix.setColumn(column, tempColumn);
}
void MatSystem::RowAdd(IntMat& matrix, int targetRow, int givenRow, int scalar)
{
	std::vector<int> target = matrix.getRow(targetRow);
	std::vector<int> given = matrix.getRow(givenRow);
	for (int i = 0; i < target.size(); ++i)
	{
		target[i] += scalar * given[i];
	}
	matrix.setRow(targetRow, target);	
}
void MatSystem::ColumnAdd(IntMat& matrix, int targetColumn, int givenColumn, int scalar)
{
	std::vector<int> target = matrix.getColumn(targetColumn);
	std::vector<int> given = matrix.getColumn(givenColumn);
	for (int i = 0; i < target.size(); ++i)
	{
		target[i] += scalar * given[i];
	}
	matrix.setColumn(targetColumn, target);	
}

void MatSystem::RowExchangeOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int row1, int row2)
{
	RowExchange(matrix, row1, row2);
	RowExchange(Qinverse, row1, row2);
	ColumnExchange(Q, row1, row2);
}
void MatSystem::ColumnExchangeOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int column1, int column2)
{
	ColumnExchange(matrix, column1, column2);
	ColumnExchange(R, column1, column2);
	RowExchange(Rinverse, column1, column2);
}

void MatSystem::RowMultiplyOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int row)
{
	RowMultiply(matrix, row, -1);
	RowMultiply(Qinverse, row, -1);
	ColumnMultiply(Q, row, -1);
}
void MatSystem::ColumnMultiplyOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int column)
{
	ColumnMultiply(matrix, column, -1);
	ColumnMultiply(R, column, -1);
	RowMultiply(Rinverse, column, -1);
}

void MatSystem::RowAddOperation(IntMat& matrix, IntMat& Q, IntMat& Qinverse, int targetRow, int givenRow, int scalar)
{
	RowAdd(matrix, targetRow, givenRow, scalar);
	RowAdd(Qinverse, targetRow, givenRow, scalar);
	ColumnAdd(Q, givenRow, targetRow, -1 * scalar);
	// TESTING
}
void MatSystem::ColumnAddOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int targetColumn, int givenColumn, int scalar)
{
	ColumnAdd(matrix, targetColumn, givenColumn, scalar);
	ColumnAdd(R, targetColumn, givenColumn, scalar);
	RowAdd(Rinverse, targetColumn, givenColumn, -1 * scalar);
}


void MatSystem::PartRowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l)
{
	for (int i = k+1; i < B.getRows(); ++i)
	{
		int q = std::floor(B.getElement(i, l) / B.getElement(k, l));
		RowAddOperation(B, Q, Qinv, i, k, -q);
	}
}

int MatSystem::IndexSmallestNonzero(std::vector<int> v, int start)
{
	int min = std::abs(v[start]);
	int index = start;

	// to avoid the annoying case where we happen to choose min = 0
	// we will set min to be the largest possible integer so we would
	// (ideally) always choose an element smaller than it in the following
	// loop.
	//
	// Yes, this is a bit of a hacky solution. I am choosing to do it this
	// way because it seems preferable (for now) to adding in a check
	// in the loop.
	
	if (min == 0)
	{
		min = std::numeric_limits<int>::max();
	}

	// begin at start + 1 since we already have min = v[start].
	for (int i = start + 1; i < v.size(); ++i)
	{
		int element = std::abs(v[i]);
		if (element != 0 && element < min)
		{
			min = element;
			index = i;
		}
	}
	
	return index;
}

void MatSystem::RowPrepare(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l)
{
	int numberOfRows = B.getRows();
	int minIndex = IndexSmallestNonzero(B.getColumn(l), k);
	RowExchangeOperation(B, Q, Qinv, k, minIndex);
}


bool MatSystem::IsZero(std::vector<int> a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] != 0)
		{
			return false;
		}
	}
	return true;
}


void MatSystem::RowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l)
{
	int rows = B.getRows();
	std::vector<int> subColumn = B.getSubColumn(l, k+1, rows);
	std::vector<int> zero(subColumn.size());
	while (!IsZero(subColumn))
	{
		RowPrepare(B, Q, Qinv, k, l);
		PartRowReduce(B, Q, Qinv, k, l);
		subColumn = B.getSubColumn(l, k+1, rows);
	}
}

void MatSystem::RowEchelon(IntMat& B)
{
	int rows = B.getRows();
	int columns = B.getColumns();
	IntMat Q = IntMat::CreateIdentity(rows, rows);
	IntMat Qinv = Q;
	int k = -1;
	int l = 0;

	std::vector<int> zero;
	while (k < rows)
	{
		while ((l <= columns) && (IsZero(B.getSubColumn(l, k+1, rows))))
		{
			++l;
		}
		if (l == columns + 1)
		{
			k = rows;
			break;
		}
		++k;
		RowReduce(B, Q, Qinv, k, l);
	}
}

std::vector<IntMat> MatSystem::GetRowEchelon(IntMat B)
{
	int rows = B.getRows();
	int columns = B.getColumns();
	IntMat Q = IntMat::CreateIdentity(rows, rows);
	IntMat Qinv = Q;
	int k = -1;
	int l = 0;

	std::vector<int> zero;
	while (k < rows)
	{
		while ((l <= columns) && (IsZero(B.getSubColumn(l, k+1, rows))))
		{
			++l;
		}
		if (l == columns + 1)
		{
			k = rows;
			break;
		}
		++k;
		RowReduce(B, Q, Qinv, k, l);
	}

	std::vector<IntMat> result = {B, Q, Qinv};
	return result;
}


void MatSystem::PrintVector(std::vector<int> vector)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

