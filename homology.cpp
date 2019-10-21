#include "homology.hpp"

std::vector<IntMat> Homology::KernelImage(IntMat& B)
{
	int lastRow = B.getRows() - 1;
	int lastColumn = B.getColumns() - 1;
	IntMat Bt = MatSystem::Transpose(B);
	RowEchelonForm ref = MatSystem::GetRowEchelon(Bt);
	
	IntMat resultBt = MatSystem::Transpose(ref.getB());
	IntMat resultPt = MatSystem::Transpose(ref.getQ());

	std::vector<IntMat> kernel_image;
	
	IntMat kernel = resultPt.getSubMatrix(0, resultPt.getRows() - 1, ref.getK() + 1, resultPt.getColumns() - 1);
	IntMat image = resultBt.getSubMatrix(0, resultBt.getRows() - 1, 0, ref.getK());

	kernel_image.push_back(kernel);
	kernel_image.push_back(image);
	return kernel_image;
}

IntMat Homology::Solve(IntMat& A, IntMat& b)
{
	int lastRow = A.getRows() - 1;
	Smith snf = MatSystem::GetSmithForm(A);
	IntMat c = Qinv * b;

	for (int i = 0; i <= t; ++i)
	{
			
	}
}

