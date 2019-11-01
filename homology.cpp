#include "homology.hpp"

std::vector<IntMat> Homology::KernelImage(IntMat& B)
{
	int lastColumn = B.getColumns() - 1;
	// we will use the Smith normal form to compute the kernel/image,
	// rather than just the row echelon form, as suggested by the book.
	std::vector<IntMat> kernelImage;

	Smith snf = MatSystem::GetSmithForm(B);
	int t = snf.getT();
	IntMat& R = snf.getR();
	IntMat& Q = snf.getQ();

	// recall that the variable "t" in the Smith form refers to the last
	// index where the Smith matrix is nonzero.
	// the columns that are zero after "t" tell us that those last 
	// columns in the matrix R form a basis for the kernel.

	// in this case, the matrix is full rank and so has trivial kernel.
	if (t == lastColumn)
	{
		//snf.getB().Print();
		kernelImage.push_back(IntMat::CreateEmpty());
		for (int i = 0; i <= t; ++i)
		{
			Q.MultiplyColumn(i, snf.getB().getElement(i, i));
		}
		kernelImage.push_back(Q.getSubMatrix(0, Q.getRows() - 1, 0, t));
	}
	// the matrix is the zero matrix so the kernel is all of the matrix R.
	else if (t == -1)
	{
		kernelImage.push_back(R);
		kernelImage.push_back(IntMat::CreateEmpty());
	}
	// kernel/image is proper and nontrivial:
	else
	{
		IntMat kernel = R.getSubMatrix(0, R.getRows() - 1, t + 1, lastColumn);
		IntMat image = Q.getSubMatrix(0, Q.getRows() - 1, 0, t);
		for (int j = 0; j < image.getColumns(); ++j)
		{
			image.MultiplyColumn(j, snf.getB().getElement(j, j));
		}

		kernelImage.push_back(kernel);
		kernelImage.push_back(image);
	}

	/*
	std::cout << "Given the matrix: " << std::endl;
	B.Print();
	std::cout << "Whose Smith form is: " << std::endl;
	snf.getB().Print();
	std::cout << "Where Q = " << std::endl;
	snf.getQ().Print();
	std::cout << "And where R = " << std::endl;
	snf.getR().Print();
	std::cout << "Kernel: " << std::endl;
	kernelImage[0].Print();
	std::cout << "Image: " << std::endl;
	kernelImage[1].Print();
	*/

	return kernelImage;
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
	IntMat result(A.getColumns(), 1);

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

	for (int i = t+1; i < lastRow; ++i)
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
	// if V is empty then V is a map from the trivial group.
	// in this case, the quotient group G/H is just G.
	if (V.isEmpty())
	{
		IntMat empty = IntMat::CreateEmpty();
		Quotient result(W, empty, 0);
		return result;
	}

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

	Smith snf = MatSystem::GetSmithForm(A);
	IntMat U = W * snf.getQ();
	Quotient result(U, snf.getB(), snf.getS());
	return result;
}

// matrices[] is an array of matrix representations of the boundary
// operator.
//
// we will assume that the first matrix is \partial_1 and the last matrix
// is \partial_n, where \partial_{n+1}: {0} \to C_n is the empty matrix.
//
// to compute the nth homology group, we need 
// Ker(\partial_n) / \Im(\partial_{n+1})
// the result of this function is an array of homologies.
// homology[0] = H_0.
std::vector<Quotient> Homology::HomologyGroupOfChainComplex(std::vector<IntMat>& matrices)
{
	// the ith element of the following arrays contains the corresponding
	// basis for the ith boundary operator.
	std::vector<IntMat> kernels;
	std::vector<IntMat> images;

	// get kernel of d0:
	IntMat kernel_d0 = MatSystem::GetSmithForm(matrices[0]).getQ();
	kernels.push_back(kernel_d0);

	// next, get the kernels and images:
	for (int i = 0; i < matrices.size(); ++i)
	{
		std::vector<IntMat> kernel_image = KernelImage(matrices[i]);
		kernels.push_back(kernel_image[0]);
		images.push_back(kernel_image[1]);
	}

	// get image of d_{n+1}, which is empty.
	IntMat empty = IntMat::CreateEmpty();
	images.push_back(empty);

	// this array contains the homologies of the space.
	std::vector<Quotient> homologies;
	
	// there are at most matrices.size nontrivial homology groups.
	for (int i = 0; i < kernels.size(); ++i)
	{
		// compute H_i = Ker_i / Im_{i+1}:
		homologies.push_back(QuotientGroup(kernels[i], images[i]));
	}

	return homologies;
}
