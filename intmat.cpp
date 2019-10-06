#include "intmat.hpp"


IntMat::IntMat(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	// initialize vectors for the matrix data
	for (int i = 0; i < rows; ++i)
	{
		std::vector<int> blankColumn(columns);
		matrix.push_back(blankColumn);
	}
}
IntMat::~IntMat(){}

IntMat IntMat::CreateIdentity(int rows, int columns)
{
	IntMat id(rows, columns);

	// choose the minimum of the number of rows and columns
	// and assign 1 to those spots.
	int min = (rows <= columns)? rows : columns;

	for (int i = 0; i < min; ++i)
	{
		id.setElement(i, i, 1);
	}
	return id;
}



void IntMat::setRow(int row, std::vector<int> data)
{
	matrix[row] = data;
}

void IntMat::setColumn(int column, std::vector<int> data)
{
	for (int i = 0; i < rows; ++i)
	{
		matrix[i][column] = data[i];
	}
}

/*void IntMat::Print()
{
	for (int i = 0; i < columns; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}*/
void IntMat::Print()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


int IntMat::getRows()
{
	return this->rows;
}
int IntMat::getColumns()
{
	return this->columns;
}

int IntMat::getElement(int row, int column)
{
	return this->matrix[row][column];
}
void IntMat::setElement(int row, int column, int data)
{
	this->matrix[row][column]=data;
}

std::vector<int> IntMat::getRow(int row)
{
	return matrix[row];	
}
std::vector<int> IntMat::getSubRow(int row, int start, int end)
{
	std::vector<int> subRow(end - start);
	for (int i = start; i < end; ++i)
	{
		subRow[i - start] = this->matrix[row][i];
	}
	return subRow;	
}
std::vector<int> IntMat::getSubColumn(int column, int start, int end)
{
	std::vector<int> subColumn(end - start);
	for (int i = start; i < end; ++i)
	{
		subColumn[i - start] = this->matrix[i][column];	
	}
	return subColumn;
}
std::vector<int> IntMat::getColumn(int column)
{
	std::vector<int> data(rows);
	for (int i = 0; i < rows; ++i)
	{
		data[i] = matrix[i][column];	
	}
	return data;
}

IntMat IntMat::getSubMatrix(int rowStart, int rowEnd, int columnStart, int columnEnd)
{
	int rows = rowEnd - rowStart;
	int columns = columnEnd - columnStart;
	IntMat subMatrix(rows, columns);

	for (int i = rowStart; i < rowEnd; ++i)
	{
		std::vector<int> subRow(columns);
		for (int j = columnStart; j < columnEnd; ++j)
		{
			subRow[j-columnStart] = getElement(i, j);
		}
		subMatrix.setRow(i, subRow);
	}
	return subMatrix;
}


IntMat operator+(IntMat& left, IntMat& right)
{
	// these matrices had better be the same dimension
	int rows = left.getRows();
	int columns = right.getColumns();
	IntMat temp(rows, columns);
	if (rows == right.getRows() && columns == right.getColumns())
	{
		for (int i = 0; i < left.getRows(); ++i)
		{
			for (int j = 0; j < left.getColumns(); ++j)
			{
				temp.setElement(i, j, left.getElement(i, j) + right.getElement(i, j));
			}
		}
	}
	else
	{
		std::cout << "DIMENSION ERROR!" << std::endl;
	}
	return temp;
}

IntMat operator*(IntMat& left, IntMat& right)
{
	// the dimensions had better match for multiplication to be well-defined!
	// we need left to be n*p and right to be p*m
	// resulting in a matrix of dimensions n*m
	int leftRows = left.getRows();
	int rows = left.getColumns();	
	int columns = right.getRows();
	int rightColumns = right.getColumns();
	IntMat temp (leftRows, rightColumns);
	if (rows == columns)
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				// this iteration will fill the (i, j) element of temp
				// so we need the dot product of the ith row of left
				// and the jth column of right
				int dotProduct = 0;
				for (int k = 0; k < rows; ++k)
				{
					dotProduct += left.getElement(i, k) * right.getElement(k, j);	
				}
				temp.setElement(i, j, dotProduct);
			}
		}
	}
	else
	{
		std::cout << "DIMENSION ERROR!" << std::endl;
	}
	return temp;
}
