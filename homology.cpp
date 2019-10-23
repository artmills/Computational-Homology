#include "homology.hpp"

std::vector<IntMat> Homology::KernelImage(IntMat& B)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;
	IntMat Bt = MatSystem::Transpose(B);

	Bt.Print();
	std::cout << "Computing ref: " << std::endl;
	RowEchelonForm ref = MatSystem::GetRowEchelon(Bt);
	
	IntMat resultBt = MatSystem::Transpose(ref.getB());
	IntMat resultPt = MatSystem::Transpose(ref.getQ());

	resultBt.Print();
	resultPt.Print();

	std::vector<IntMat> kernel_image;
	
	IntMat kernel = resultPt.getSubMatrix(0, resultPt.getRows() - 1, ref.getK() + 1, resultPt.getColumns() - 1);
	IntMat image = resultBt.getSubMatrix(0, resultBt.getRows() - 1, 0, ref.getK());

	kernel_image.push_back(kernel);
	kernel_image.push_back(image);
	return kernel_image;
}

IntMat Homology::Solve(IntMat A, IntMat& b)
{
	int lastRow = A.getRows() - 1;
	Smith snf = MatSystem::GetSmithForm(A);
	IntMat& B = snf.getB();
	IntMat& Qinv = snf.getQinv();
	IntMat& R = snf.getR();
	int& t = snf.getT();	

	IntMat c = Qinv * b;
	IntMat result(lastRow + 1, 1);

	for (int i = 0; i <= t; ++i)
	{
		// check if B(i, i) divides c(i):
		if (c.getElement(i, 0) % B.getElement(i, i) == 0)
		{
			result.setElement(i, 0, c.getElement(i, 0) / B.getElement(i, i));	
		}
		else
		{
			// failure!
			std::cout << "NO SOLUTION!" << std::endl;
			return IntMat(0, 0);
		}
	}

	for (int i = t+1; i <= lastRow; ++i)
	{
		if (c.getElement(i, 0) != 0)
		{
			// failure!
			std::cout << "NO SOLUTION!" << std::endl;
			return IntMat(0, 0);
		}
		else
		{
			result.setElement(i, 0, 0);
		}
	}

	return R * result;
}
IntMat Homology::Solve(IntMat A, std::vector<int>& b)
{
	int lastRow = A.getRows() - 1;
	Smith snf = MatSystem::GetSmithForm(A);
	IntMat& B = snf.getB();
	IntMat& Qinv = snf.getQinv();
	IntMat& R = snf.getR();
	int& t = snf.getT();	

	IntMat bVector(b.size(), 1);
	bVector.setColumn(0, b);

	IntMat c = Qinv * bVector;
	IntMat result(lastRow + 1, 1);

	for (int i = 0; i <= t; ++i)
	{
		// check if B(i, i) divides c(i):
		if (c.getElement(i, 0) % B.getElement(i, i) == 0)
		{
			result.setElement(i, 0, c.getElement(i, 0) / B.getElement(i, i));	
		}
		else
		{
			// failure!
			std::cout << "NO SOLUTION!" << std::endl;
			return IntMat(0, 0);
		}
	}

	for (int i = t+1; i <= lastRow; ++i)
	{
		if (c.getElement(i, 0) != 0)
		{
			// failure!
			std::cout << "NO SOLUTION!" << std::endl;
			return IntMat(0, 0);
		}
		else
		{
			result.setElement(i, 0, 0);
		}
	}

	return R * result;
}

Quotient Homology::QuotientGroup(IntMat& W, IntMat& V)
{
	int columns = V.getColumns();
	
	// rows of A is the rows of V.
	// each iteration of the loop below adds a new column to A.
	IntMat A(W.getColumns(), V.getColumns()); // n*m matrix.

	for (int i = 0; i < columns; ++i)
	{
		std::vector<int> b = V.getColumn(i);
		IntMat soln = Solve(W, b);
		A.setColumn(i, soln.getColumn(0));
	}

	std::cout << "Computing Smith form: " << std::endl;
	Smith snf = MatSystem::GetSmithForm(A);
	IntMat U = W * snf.getQ();
	Quotient result(U, snf.getB(), snf.getS());
	return result;
}
