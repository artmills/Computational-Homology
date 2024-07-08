#include "homology.hpp"
#include <linbox/algorithms/smith-form-adaptive.h>
#include <linbox/field/field-traits.h>
#include <linbox/integer.h>
#include <linbox/linbox-tags.h>
#include <linbox/solutions/solution-tags.h>
#include <linbox/vector/vector.h>

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

	// the matrix is the zero matrix so the kernel is all of the matrix R.
	if (t == -1)
	{
		kernelImage.push_back(R);
		kernelImage.push_back(IntMat::CreateEmpty());
	}
	// in this case, the matrix is full rank and so has trivial kernel.
	else if (t == lastColumn)
	{
		//snf.getB().Print();
		kernelImage.push_back(IntMat::CreateEmpty());
		for (int i = 0; i <= t; ++i)
		{
			Q.MultiplyColumn(i, snf.getB().getElement(i, i));
		}
		kernelImage.push_back(Q.getSubMatrix(0, Q.getRows() - 1, 0, t));
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

	/*
	std::cout << "Attempting to solve the system: " << std::endl;
	A.Print();
	std::cout << "=" << std::endl;
	bVector.Print();
	std::cout << "t = " << t << std::endl;
	*/

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

	for (int i = t+1; i < A.getColumns(); ++i)
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

	// there is a typo in the book:
	// the book ends this loop at A.getRows(), which is definitely wrong.
	for (int i = t+1; i < A.getColumns(); ++i)
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
/*
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

	
	std::cout << "Solving system using the following: " << std::endl;
	std::cout << "B = " << std::endl;
	B.Print();
	std::cout << "Qinv = " << std::endl;
	Qinv.Print();
	std::cout << "R = " << std::endl;
	R.Print();
	std::cout << "c = " << std::endl;
	c.Print();
	std::cout << "Result = " << std::endl;
	result.Print();
	


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
		std::cout << "i = " << i << std::endl;
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
*/

Quotient Homology::QuotientGroup(IntMat& W, IntMat& V)
{
	// if V is empty then V is a map from the trivial group.
	// in this case, the quotient group G/H is just G.
	if (V.isEmpty())
	{
		IntMat empty = IntMat::CreateEmpty();
		Quotient result(W, empty, -1);
		return result;
	}
	// if we mod out by everything then the homology group is trivial.
	if (W == V)
	{
		IntMat empty = IntMat::CreateEmpty();
		Quotient result(empty, empty, -1);
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
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	IntMat kernel_d0 = MatSystem::GetSmithForm(matrices[0]).getQ();
	kernels.push_back(kernel_d0);

	// next, get the kernels and images:
	for (int i = 0; i < matrices.size(); ++i)
	{
		std::vector<IntMat> kernel_image = KernelImage(matrices[i]);
		kernels.push_back(kernel_image[0]);
		images.push_back(kernel_image[1]);
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time to get kernels and images: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0 << " seconds. " << std::endl;

	// get image of d_{n+1}, which is empty.
	IntMat empty = IntMat::CreateEmpty();
	images.push_back(empty);

	// this array contains the homologies of the space.
	std::vector<Quotient> homologies;
	
	// there are at most matrices.size nontrivial homology groups.
	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < kernels.size(); ++i)
	{
		// compute H_i = Ker_i / Im_{i+1}:
		homologies.push_back(QuotientGroup(kernels[i], images[i]));
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Time to take quotients: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0 << " seconds. " << std::endl;

	return homologies;
}

void Homology::AnalyzeHomologyRaw(std::vector<Quotient> groups)
{
	for (int i = 0; i < groups.size(); ++i)
	{
		IntMat& U = groups[i].getU();
		IntMat& B = groups[i].getB();
		int& s = groups[i].getS();

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Matrices to compute H_" << i << ": " << std::endl;
		U.Print();
		B.Print();
		std::cout << s << std::endl;
		std::cout << std::endl;

		bool trivial = true;

		std::cout << "H_" << i << ": ";
		// we only care about the elements after s.
		if (s > -1)
		{
			for (int j = s + 1; j < B.getColumns(); ++j)
			{
				if (B.getElement(j, j) != 0)
				{
					trivial = false;
					std::cout << "Z_" << B.getElement(j, j) << " ";
				}
			}
		}

		if (!U.isEmpty())
		{
			int columns = 0;
			if (!B.isEmpty())
			{
				columns = B.getColumns();
			}

			int Z = U.getColumns() - columns;
			if (Z > 0)
			{
				trivial = false;
				std::cout << "Z^" << Z << ".";
			}
		}

		if (trivial)
		{
			std::cout << "0.";
		}
		std::cout << std::endl;
	}
}
void Homology::AnalyzeHomology(std::vector<Quotient> groups)
{
	for (int i = 0; i < groups.size(); ++i)
	{
		IntMat& U = groups[i].getU();
		IntMat& B = groups[i].getB();
		int& s = groups[i].getS();

		bool trivial = true;

		std::cout << "H_" << i << ": ";
		// we only care about the elements after s.
		if (s > -1)
		{
			for (int j = s + 1; j < B.getColumns(); ++j)
			{
				if (B.getElement(j, j) != 0)
				{
					trivial = false;
					std::cout << "Z_" << B.getElement(j, j) << " ";
				}
			}
		}

		if (!U.isEmpty())
		{
			int columns = 0;
			if (!B.isEmpty())
			{
				columns = B.getColumns();
			}

			int Z = U.getColumns() - columns;
			if (Z > 0)
			{
				trivial = false;
				std::cout << "Z^" << Z << ".";
			}
		}

		if (trivial)
		{
			std::cout << "0.";
		}
		std::cout << std::endl;
	}
}

// LinBox version.
std::vector<std::vector<int>> Homology::GetHomologyLinBox(std::vector<Matrix>& boundaries)
{
	// matrices[i] = d_{i+1}: C_{i+1} -> C_i where matrices[0] = d_1.
	// there is no reason to pass d_0 since it is the zero matrix.
	// similarly, there is no reason to pass d_{n+1}.

	// LinBox: get the info for the Smith normal form and convert to s, t lists.
	std::vector<SmithList> smithLists;
	std::vector<int> sList(boundaries.size(), -1);
	std::vector<int> tList(boundaries.size(), -1);
	std::vector<int> rowList(boundaries.size(), -1); // Number of rows.
	for (int i = 0; i < boundaries.size(); ++i)
	{
		// Compute the Smith normal form.
		SmithList sl;

		std::cout << "Computing smith form of the " << i << "th boundary matrix with size ";
		std::cout << boundaries[i].rowdim() << " x " << boundaries[i].coldim() << std::endl;
		LinBox::RingCategories::IntegerTag a;
		LinBox::Method::Blackbox b;
		//LinBox::smithForm(sl, boundaries[i], a, b);
		LinBox::smithForm(sl, boundaries[i]);
		std::cout << "Completed smith form calculation." << std::endl;
		/*
		LinBox::DenseVector<Integers> v(ZZ, boundaries[i].coldim());
		LinBox::SmithFormAdaptive::smithForm(v, boundaries[i]);
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			std::cout << *it << std::endl;
		}
		*/

		// Convert the SmithList structure from LinBox into arrays that keep track of s, t.
		int t = -1;
		int s = -1;
		for (auto it = sl.begin(); it != sl.end(); ++it)
		{
			std::pair p = *it;
			
			// t counts the number of nonzero diagonal entries minus 1 (which is why we initialize to -1).
			if (p.first != 0)
				t += p.second;
			// s counts the number of diagonal entries equal to 1.
			if (p.first == 1)
				s = p.second;
		}
		// Set into the corresponding arrays.
		smithLists.push_back(sl);
		sList[i] = s;
		tList[i] = t;
		rowList[i] = boundaries[i].rowdim();
	}

	// output will be stored in arrays of integers.
	// the last element of each array is the Betti number.
	// the first elements are the torsion coefficients.
	std::vector<std::vector<int>> homologies;
	
	// handle the H_0 case individually.
	SmithList& sl0 = smithLists[0];
	homologies.push_back(GetIthHomologyLinBox(sl0, sList[0], tList[0], rowList[0], 0));

	// H_1 to H_{n-1}.
	for (int i = 1; i < smithLists.size(); ++i)
	{
		SmithList& sl = smithLists[i];
		homologies.push_back(GetIthHomologyLinBox(sl, sList[i], tList[i], rowList[i], tList[i-1] + 1));
	}

	// handle the H_n case individually:
	SmithList& snfn = smithLists[smithLists.size() - 1];
	//std::vector<int> Hn = {snfn.getB().getColumns() - (snfn.getT() + 1)};
	std::vector<int> Hn = {(int)boundaries[boundaries.size() - 1].coldim() - (tList[smithLists.size() - 1] + 1)};
	//int nColumns = (int)boundaries[boundaries.size() - 1].coldim();
	homologies.push_back(Hn);

	return homologies;
}

std::vector<std::vector<int>> Homology::GetHomology(std::vector<IntMat>& boundaries)
{
	// matrices[i] = d_{i+1}: C_{i+1} -> C_i where matrices[0] = d_1.
	// there is no reason to pass d_0 since it is the zero matrix.
	// similarly, there is no reason to pass d_{n+1}.

	// we will convert all matrices to their Smith forms.
	// we do not need the entire Smith normal form: just B, s, and t.
	std::vector<SmithLite> smithForms;
	for (int i = 0; i < boundaries.size(); ++i)
	{
		SmithLite snf = MatSystem::GetSmithFormLite(boundaries[i]);
		//snf.getB().Print();
		//std::cout << "s = " << snf.getS() << ". t = " << snf.getT() << std::endl;
		//std::cout << std::endl;
		smithForms.push_back(snf);
	}

	// output will be stored in arrays of integers.
	// the last element of each array is the Betti number.
	// the first elements are the torsion coefficients.
	std::vector<std::vector<int>> homologies;
	
	// handle the H_0 case individually.
	SmithLite& snf1 = smithForms[0];
	homologies.push_back(GetIthHomology(snf1, 0));

	for (int i = 1; i < smithForms.size(); ++i)
	{
		SmithLite& snf = smithForms[i];
		IntMat& B = snf.getB();
		int& s = snf.getS();
		int& t = snf.getT();

		homologies.push_back(GetIthHomology(snf, smithForms[i-1].getT() + 1));
	}

	// handle the H_n case individually:
	SmithLite& snfn = smithForms[smithForms.size() - 1];
	std::vector<int> Hn = {snfn.getB().getColumns() - (snfn.getT() + 1)};
	homologies.push_back(Hn);
	

	return homologies;
}

void Homology::AnalyzeHomology(std::vector<std::vector<int>> homologies)
{
	for (int i = 0; i < homologies.size(); ++i)
	{
		for (int j = 0; j < homologies[i].size(); ++j)
		{
			std::cout << homologies[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

// LinBox version.
std::vector<int> Homology::GetIthHomologyLinBox(SmithList& sl, int s, int t, int rows, int rankd)
{
	std::vector<int> homology;

	// get torsion coefficients, which are the nonzero/nonidentity diagonal entries.
	for (auto it = sl.begin(); it != sl.end(); ++it)
	{
		std::pair p = *it;
		int value = p.first;
		if (value != 0 && value != 1)
		{
			// Now add the value the appropriate number of times.
			int count = p.second;
			for (int j = 0; j < count; ++j)
				homology.push_back(value);
		}
	}

	// get betti number r: r = rank(C_i)
	int betti = rows - rankd;
	homology.push_back(betti - (t+1));

	return homology;	
}
std::vector<int> Homology::GetIthHomology(SmithLite& D, int rankd)
{
	IntMat& B = D.getB();
	int& s = D.getS();
	int& t = D.getT();

	std::vector<int> homology;

	// get torsion coefficients:
	for (int j = s+1; j <= t; ++j)
	{
		homology.push_back(B.getElement(j, j));
	}

	// get betti number r: r = rank(C_i)
	int betti = B.getRows() - rankd;
	homology.push_back(betti - (t+1));

	return homology;	
}
