#include "matsystem.hpp"


/********** Operations on matrices **********/

IntMat MatSystem::Transpose(IntMat& matrix)
{
	IntMat transpose(matrix.getColumns(), matrix.getRows());	
	for (int i = 0; i < transpose.getRows(); ++i)
	{
		transpose.setRow(i, matrix.getColumn(i));
	}
	return transpose;
}




/********** Elementary row operations **********/

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





/********** Fancy elementary row operations **********/

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

// note: over the ring of integers the only elements
// with multiplicative inverses are -1, 1. 
// therefore we can only consider multiplication by -1
// as an elementary row operation.
// as such we will hardcode the value -1 for the scalar.
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
}
void MatSystem::ColumnAddOperation(IntMat& matrix, IntMat& R, IntMat& Rinverse, int targetColumn, int givenColumn, int scalar)
{
	ColumnAdd(matrix, targetColumn, givenColumn, scalar);
	ColumnAdd(R, targetColumn, givenColumn, scalar);
	RowAdd(Rinverse, givenColumn, targetColumn, -1 * scalar);
}



/********** Preliminaries for row reduction **********/

void MatSystem::PartRowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l)
{
	for (int i = k+1; i < B.getRows(); ++i)
	{
		int q = std::floor(B.getElement(i, l) / B.getElement(k, l));
		RowAddOperation(B, Q, Qinv, i, k, -q);
	}
}
void MatSystem::PartColumnReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l)
{
	for (int j = k+1; j < B.getColumns(); ++j)
	{
		int q = std::floor(B.getElement(k, j) / B.getElement(k, l));
		ColumnAddOperation(B, Q, Qinv, j, l, -q);
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





/********** Row reduction **********/

void MatSystem::RowReduce(IntMat& B, IntMat& Q, IntMat& Qinv, int k, int l)
{
	int lastRow = B.getRows() - 1;
	std::vector<int> subColumn = B.getSubColumn(l, k+1, lastRow);
	std::vector<int> zero(subColumn.size());
	while (!IsZero(subColumn))
	{
		RowPrepare(B, Q, Qinv, k, l);
		PartRowReduce(B, Q, Qinv, k, l);
		subColumn = B.getSubColumn(l, k+1, lastRow);
	}
}

void MatSystem::RowEchelon(IntMat& B)
{
	int rows = B.getRows();
	int columns = B.getColumns();
	IntMat Q = IntMat::CreateIdentity(rows);
	IntMat Qinv = Q;
	int k = -1;
	int l = 0;

	while (k < rows - 2)
	{
		while ((l < columns) && (IsZero(B.getSubColumn(l, k+1, rows - 1))))
		{
			++l;
		}
		if (l == columns)
		{
			break;
		}
		++k;
		//std::cout << k << " " << l << std::endl;
		RowReduce(B, Q, Qinv, k, l);
	}
	//std::cout << k << std::endl;
}

RowEchelonForm MatSystem::GetRowEchelon(IntMat B)
{
	int rows = B.getRows();
	int columns = B.getColumns();
	IntMat Q = IntMat::CreateIdentity(rows);
	IntMat Qinv = Q;
	int k = -1;
	int l = 0;

	while (k < rows - 2)
	{
		//std::cout << k+1 << " " << l << std::endl;
		while ((l < columns) && (IsZero(B.getSubColumn(l, k+1, rows - 1))))
		{
			++l;
		}
		if (l == columns)
		{
			break;
		}
		++k;
		RowReduce(B, Q, Qinv, k, l);
	}

	RowEchelonForm ref(B, Q, Qinv, k);
	return ref;
}


/********** Applications of row echelon form **********/

std::vector<IntMat> MatSystem::KernelImage(IntMat B)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;
	IntMat Bt = Transpose(B);
	RowEchelonForm ref = GetRowEchelon(Bt);
	
	IntMat resultBt = Transpose(ref.getB());
	IntMat resultPt = Transpose(ref.getQ());

	std::vector<IntMat> kernel_image;
	
	IntMat kernel = resultPt.getSubMatrix(0, resultPt.getRows() - 1, ref.getK() + 1, resultPt.getColumns() - 1);
	IntMat image = resultBt.getSubMatrix(0, resultBt.getRows() - 1, 0, ref.getK());

	kernel_image.push_back(kernel);
	kernel_image.push_back(image);
	return kernel_image;
}




/********** Preparing for the Smith Normal Form **********/

std::vector<int> MatSystem::MinNonzero(IntMat& B, int k)
{
	int min = std::numeric_limits<int>::max();
	int row, column;

	// iterate through rows of B.
	for (int i = k; i < B.getRows(); ++i)
	{
		int index = IndexSmallestNonzero(B.getRow(i), k);
		int candidate = std::abs(B.getElement(i, index));
		if (candidate < min && candidate != 0)
		{
			min = candidate;
			row = i;
			column = index;
		}
	}
	std::vector<int> element = {row, column};
	return element;
}

void MatSystem::MoveMinNonzero(IntMat& B, IntMat& Q, IntMat& Qinv, IntMat& R, IntMat& Rinv, int k)
{
	std::vector<int> element = MinNonzero(B, k);
	RowExchangeOperation(B, Q, Qinv, k, element[0]);
	ColumnExchangeOperation(B, R, Rinv, k, element[1]);
}


std::vector<int> MatSystem::CheckForDivisibility(IntMat& B, int k)
{
	std::vector<int> coordinates(2);
	for (int i = k + 1; i < B.getRows(); ++i)
	{
		for (int j = k + 1; j < B.getColumns(); ++j)
		{
			int q = std::floor((float)B.getElement(i, j) / (float)B.getElement(k, k));

			if (q * B.getElement(k, k) != B.getElement(i, j))
			{
				// there is an element that is not divisible by (k, k).
				// return the coordinates of that point.
				coordinates = {i, j};
				return coordinates;
			}
		}
	}
	// the (k, k) element divides all elements in the submatrix.
	// return "true".
	coordinates = {-1, -1};
	return coordinates;
}


void MatSystem::PartSmithForm(IntMat& B, IntMat& Q, IntMat& Qinv, IntMat& R, IntMat& Rinv, int k)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;

	//std::cout << "Initial matrix: " << std::endl;
	//B.Print();
	bool flag = false;

	do
	{
		MoveMinNonzero(B, Q, Qinv, R, Rinv, k);
		//std::cout << "MoveMinNonzero" << std::endl;
		//B.Print();

		PartRowReduce(B, Q, Qinv, k, k);
		//std::cout << "PartRowReduce" << std::endl;
		//B.Print();

		if (k < lastRow && !IsZero(B.getSubColumn(k, k+1, lastRow)))
		{
			//std::cout << "Continue: B.getSubColumn(k, k+1, lastRow) != 0 for k = "<< k << std::endl;
			continue;
		}
		
		PartColumnReduce(B, R, Rinv, k, k);
		//std::cout << "PartColumnReduce" << std::endl;
		//B.Print();

		if (k < lastColumn && !IsZero(B.getSubRow(k, k+1, lastColumn)))
		{
			//std::cout << "Continue: B.getSubRow(k, k+1, lastColumn) != 0 for k = "<< k << std::endl;
			continue;
		}

		std::vector<int> divisibilityCheck = CheckForDivisibility(B, k);
		if (divisibilityCheck[0] != -1)
		{
			//std::cout << "Fail divisibility for k = "<< k << std::endl;
			int i = divisibilityCheck[0];
			int j = divisibilityCheck[1];

			RowAddOperation(B, Q, Qinv, i, k, 0);
			//std::cout << "RowAdd" << std::endl;
			//B.Print();

			ColumnAddOperation(B, R, Rinv, k, j, -B.getElement(i, j));
			//std::cout << "ColumnAdd" << std::endl;
			//B.Print();
		}
		else
		{
			flag = true;
		}
	} while (!flag);
	/*while (CheckForDivisibility(B, k)[0] != -1);*/
	//std::cout << "Pass divisibility" << std::endl;
	//B.Print();
}

bool MatSystem::IsZero(IntMat B)
{
	for (int i = 0; i < B.getRows(); ++i)
	{
		if (!IsZero(B.getRow(i)))
		{
			return false;
		}
	}
	return true;
}
bool MatSystem::IsZero(IntMat& B)
{
	for (int i = 0; i < B.getRows(); ++i)
	{
		if (!IsZero(B.getRow(i)))
		{
			return false;
		}
	}
	return true;
}

void MatSystem::SmithForm(IntMat& B)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;

	IntMat Q = IntMat::CreateIdentity(lastRow + 1);
	IntMat Qinv = Q;
	IntMat R = IntMat::CreateIdentity(lastColumn + 1);
	IntMat Rinv = R;
	int s = 0;
	int t = -1;

	while (t <= lastRow - 1 && t <= lastColumn - 1 && !IsZero(B.getSubMatrix(t + 1, lastRow, t + 1, lastColumn)))	
	{
		++t;
		//std::cout << t << std::endl;
		PartSmithForm(B, Q, Qinv, R, Rinv, t);

		if (B.getElement(t, t) < 0)
		{
			RowMultiplyOperation(B, Q, Qinv, t);
		}

		if (B.getElement(t, t) == 1)
		{
			++s;
		}
	} 
}
Smith MatSystem::GetSmithForm(IntMat& B)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;

	IntMat Q = IntMat::CreateIdentity(lastRow + 1);
	IntMat Qinv = Q;
	IntMat R = IntMat::CreateIdentity(lastColumn + 1);
	IntMat Rinv = R;
	int s = 0;
	int t = -1;

	while (t <= lastRow - 1 && t <= lastColumn - 1 && !IsZero(B.getSubMatrix(t + 1, lastRow, t + 1, lastColumn)))	
	{
		++t;
		PartSmithForm(B, Q, Qinv, R, Rinv, t);

		if (B.getElement(t, t) < 0)
		{
			RowMultiplyOperation(B, Q, Qinv, t);
		}

		if (B.getElement(t, t) == 1)
		{
			++s;
		}
	}

	Smith snf(B, Q, Qinv, R, Rinv, s, t);
	return snf;
}







/********** Utility **********/

void MatSystem::PrintVector(std::vector<int> vector)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

