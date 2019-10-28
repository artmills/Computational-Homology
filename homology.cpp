#include "homology.hpp"

std::vector<IntMat> Homology::KernelImage(IntMat& B)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;
	IntMat Bt = MatSystem::Transpose(B);

	Bt.Print();
	//std::cout << "Computing ref: " << std::endl;
	RowEchelonForm ref = MatSystem::GetRowEchelon(Bt);
	
	IntMat resultBt = MatSystem::Transpose(ref.getB());
	IntMat resultPt = MatSystem::Transpose(ref.getQ());

	//resultBt.Print();
	//resultPt.Print();

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

	//std::cout << "Computing Smith form: " << std::endl;
	Smith snf = MatSystem::GetSmithForm(A);
	IntMat U = W * snf.getQ();
	Quotient result(U, snf.getB(), snf.getS());
	return result;
}


// matrices[] is an array of matrix representations of the boundary
// operator.
//
// we will assume that both the first and last elements are the proper
// zero matrix, representing \partial_0 = 0 and \partial_{n+1} = 0.
// this means that matrices[size - 1] = \partial_{n+1}.
// so the last (potentially) nontrivial homology group will be
// H_n where n = size - 2.
//
// to compute the nth homology group, we need 
// Ker(\partial_n) / \Im(\partial_{n+1})
// the result of this function is an array of homologies.
// homology[0] = H_0.
std::vector<Quotient> Homology::HomologyGroupOfChainComplex(std::vector<IntMat>& matrices)
{
	// the last homology group to consider: H_n.
	int n = matrices.size() - 2;

	// the ith element of the following arrays contains the corresponding
	// basis for the ith boundary operator.
	std::vector<IntMat> kernels;
	std::vector<IntMat> images;

	// handle the cases for the zero matrices separately:

	// first, get the kernels and images of all boundary operators:
	for (int i = 0; i < n; ++i)
	{
		std::vector<IntMat> kernel_image = KernelImage(matrices[i]);
		kernels.push_back(kernel_image[0]);
		images.push_back(kernel_image[1]);
	}

	// this array contains the homologies of the space.
	std::vector<Quotient> homologies;

	// there are at most matrices.size nontrivial homology groups.
	for (int i = 0; i < n; ++i)
	{
		// compute H_i = Ker_i / Im_{i+1}:
		homologies.push_back(QuotientGroup(kernels[i], images[i+1]));

	}
}
