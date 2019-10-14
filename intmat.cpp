#include "intmat.hpp"


/********* constructors/destructors *********/

IntMat::IntMat(int rows, int columns)
{
	// initialize vectors for the matrix data
	for (int i = 0; i < rows; ++i)
	{
		std::vector<int> blankColumn(columns);
		matrix.push_back(blankColumn);
	}
}
IntMat::IntMat(int a, int b, int c, int d)
{
	std::vector<int> r1 = {a, b};
	std::vector<int> r2 = {c, d};
	matrix.push_back(r1);
	matrix.push_back(r2);
}
IntMat::IntMat(int a11, int a12, int a13,
			   int a21, int a22, int a23,
			   int a31, int a32, int a33) // 3 by 3
{
	std::vector<int> r1 = {a11, a12, a13};	
	std::vector<int> r2 = {a21, a22, a23};	
	std::vector<int> r3 = {a31, a32, a33};	
	matrix.push_back(r1);
	matrix.push_back(r2);
	matrix.push_back(r3);
}

IntMat::~IntMat(){}





/********* initializing a matrix row by row or column by column *********/

void IntMat::setRow(int row, std::vector<int> data)
{
	matrix[row] = data;
}

void IntMat::setColumn(int column, std::vector<int> data)
{
	for (int i = 0; i < getRows(); ++i)
	{
		matrix[i][column] = data[i];
	}
}






/********* getters/setters for rows/columns/elements *********/

int IntMat::getRows()
{
	return matrix.size();
}
int IntMat::getColumns()
{
	return matrix[0].size();
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
std::vector<int> IntMat::getColumn(int column)
{
	std::vector<int> data(getRows());
	for (int i = 0; i < getRows(); ++i)
	{
		data[i] = matrix[i][column];	
	}
	return data;
}





/********* getters/setters for sub{matrices/rows/columns} *********/
std::vector<int> IntMat::getSubRow(int row, int start, int end)
{
	std::vector<int> v;
	
	// check if accessing a valid row:
	if (row > matrix.size() || row < 0)
	{
		std::cout << "DIMENSION ERROR FOR SUBROW!" << std::endl;
		return v;
	}

	// check if accessing the proper columns:
	if (end >= matrix[0].size() || end < start || start < 0)
	{
		std::cout << "DIMENSION ERROR FOR SUBROW!" << std::endl;
		return v;
	}

	// put only the proper elements into the vector v:
	for (int i = start; i <= end; ++i)
	{
		v.push_back(matrix[row][i]);
	}

	return v;
}
std::vector<int> IntMat::getSubColumn(int column, int start, int end)
{
	std::vector<int> v;
	
	// check if accessing a valid column:
	if (column > matrix[0].size() || column < 0)
	{
		std::cout << "DIMENSION ERROR FOR SUBCOLUMN!" << std::endl;
		std::cout << "Column: " << column << std::endl;
		std::cout << "Start: " << start << std::endl;
		std::cout << "End: " << end << std::endl;
		std::cout << std::endl;
		return v;
	}

	// check if accessing the proper columns:
	if (end >= matrix.size() || end < start || start < 0)
	{
		std::cout << "DIMENSION ERROR FOR SUBCOLUMN!" << std::endl;
		std::cout << "Column: " << column << std::endl;
		std::cout << "Start: " << start << std::endl;
		std::cout << "End: " << end << std::endl;
		return v;
	}

	// put only the proper elements into the vector v:
	for (int i = start; i <= end; ++i)
	{
		v.push_back(matrix[i][column]);
	}

	return v;
}

IntMat IntMat::getSubMatrix(int rowStart, int rowEnd, int columnStart, int columnEnd)
{
	int rows = rowEnd - rowStart + 1;
	int columns = columnEnd - columnStart + 1;
	IntMat subMatrix(rows, columns);

	for (int i = rowStart; i <= rowEnd; ++i)
	{
		std::vector<int> subRow = getSubRow(i, columnStart, columnEnd);
		subMatrix.setRow(i - rowStart, subRow);
	}
	return subMatrix;
}




/********* Utility *********/

IntMat IntMat::CreateIdentity(int size)
{
	IntMat id(size, size);
	for (int i = 0; i < size; ++i)
	{
		id.setElement(i, i, 1);
	}
	return id;
}

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

void IntMat::Print()
{
	for (int i = 0; i < getRows(); ++i)
	{
		for (int j = 0; j < getColumns(); ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}





/********* Matrix ring operations *********/

IntMat IntMat::Sum(IntMat& left, IntMat& right)
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

IntMat IntMat::Product(IntMat& left, IntMat& right)
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
