#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

#include "intmat.hpp"
#include "matsystem.hpp"
#include "homology.hpp"
#include "interval.hpp"
#include "keyhasher.hpp"
#include "cubicalset.hpp"
#include "cubesystem.hpp"
#include "landscape.hpp"


IntMat CreateExample1()
{
	return IntMat(2, 4, 4, -6, 6, 12, 10, -4, -16);	
}
IntMat CreateExample2()
{
	IntMat ex(3, 4);
	std::vector<int> row0 = {1, 6, 8, 8};
	std::vector<int> row1 = {0, 0, 2, 10};
	std::vector<int> row2 = {0, 2, 2, 10};
	ex.setRow(0, row0);
	ex.setRow(1, row1);
	ex.setRow(2, row2);
	return ex;
}
IntMat CreateExample3()
{
	IntMat ex(4, 4);
	std::vector<int> row0 = {1, 8, 8, 7};
	std::vector<int> row1 = {2, 0, 2, 5};
	std::vector<int> row2 = {0, 1, 3, 1};
	std::vector<int> row3 = {3, 2, 3, 9};
	ex.setRow(0, row0);
	ex.setRow(1, row1);
	ex.setRow(2, row2);
	ex.setRow(3, row3);
	return ex;
}
IntMat CreateExample4()
{
	IntMat ex(4, 4);
	std::vector<int> row0 = {-6, 111, -36, 6};
	std::vector<int> row1 = {5, -672, 210, 74};
	std::vector<int> row2 = {0, -255, 81, 24};
	std::vector<int> row3 = {-7, 255, -81, -10};
	ex.setRow(0, row0);
	ex.setRow(1, row1);
	ex.setRow(2, row2);
	ex.setRow(3, row3);
	ex.setRow(0, row0);
	return ex;
}
IntMat CreateExample5()
{
	IntMat A(3, 3);
	std::vector<int> Arow0 = {3, 2, 3};
	std::vector<int> Arow1 = {0, 2, 0};
	std::vector<int> Arow2 = {2, 2, 2};
	A.setRow(0, Arow0);
	A.setRow(1, Arow1);
	A.setRow(2, Arow2);
	return A;
}
std::vector<IntMat> GetRP2()
{
	IntMat P1(2, 3);
	std::vector<int> P1row0 = {1, 1, 0};
	std::vector<int> P1row1 = {-1, -1, 0};
	P1.setRow(0, P1row0);
	P1.setRow(1, P1row1);

	IntMat P2(3, 2);
	std::vector<int> P2row0 = {-1, 1};
	std::vector<int> P2row1 = {1, -1};
	std::vector<int> P2row2 = {1, 1};
	P2.setRow(0, P2row0);
	P2.setRow(1, P2row1);
	P2.setRow(2, P2row2);

	std::vector<IntMat> matrices = {P1, P2};
	return matrices;
}
std::vector<IntMat> GetTorus()
{
	IntMat P1(1, 3);
	std::vector<int> P1row0 = {0, 0, 0};
	P1.setRow(0, P1row0);

	IntMat P2(3, 2);
	std::vector<int> P2row0 = {-1, 1};
	std::vector<int> P2row1 = {-1, 1};
	std::vector<int> P2row2 = {1, -1};
	P2.setRow(0, P2row0);
	P2.setRow(1, P2row1);
	P2.setRow(2, P2row2);

	std::vector<IntMat> matrices = {P1, P2};
	return matrices;
}
std::vector<IntMat> GetKleinBottle()
{
	IntMat P1(1, 3);
	std::vector<int> P1row0 = {0, 0, 0};
	P1.setRow(0, P1row0);

	IntMat P2(3, 2);
	std::vector<int> P2row0 = {1, 1};
	std::vector<int> P2row1 = {1, -1};
	std::vector<int> P2row2 = {-1, 1};
	P2.setRow(0, P2row0);
	P2.setRow(1, P2row1);
	P2.setRow(2, P2row2);

	std::vector<IntMat> matrices = {P1, P2};
	return matrices;
}
std::vector<IntMat> GetMagicalTetrahedron()
{
	IntMat P1(2, 3);
	std::vector<int> P1row0 = {1, 0, 0};
	std::vector<int> P1row1 = {-1, 0, 0};
	P1.setRow(0, P1row0);
	P1.setRow(1, P1row1);

	IntMat P2(3, 2);
	std::vector<int> P2row0 = {0, 0};
	std::vector<int> P2row1 = {1, 0};
	std::vector<int> P2row2 = {0, 1};
	P2.setRow(0, P2row0);
	P2.setRow(1, P2row1);
	P2.setRow(2, P2row2);

	IntMat P3(1, 1);

	std::vector<IntMat> matrices = {P1, P2, P3};
	return matrices;
}
std::vector<IntMat> GetParachute()
{
	IntMat P1(1, 3);
	std::vector<int> P1row0 = {0, 0, 0};
	P1.setRow(0, P1row0);

	IntMat P2(3, 1);
	std::vector<int> P2row0 = {1};
	std::vector<int> P2row1 = {1};
	std::vector<int> P2row2 = {-1};
	P2.setRow(0, P2row0);
	P2.setRow(1, P2row1);
	P2.setRow(2, P2row2);

	std::vector<IntMat> matrices = {P1, P2};
	return matrices;
}

void Print(std::unordered_map<Cube, int, KeyHasher> map)
{
	// how to access both keys and values in the unordered map.
	for (std::pair<Cube, int> element: map)
	{
		element.first.Print();
		//std::cout << element.first.Dimension() << std::endl;;
		//std::cout << element.second << std::endl;
	}
}

std::vector<Cube> Get2DHole(int offset)
{
	std::vector<Cube> cubes;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (i == j)
			{
				continue;
			}
			Cube cube;
			cube.addInterval(offset + i);
			cube.addInterval(offset + j);
			cubes.push_back(cube);
		}
	}
	return cubes;
}

void AnalyzeCellularAutomata(int gridX, int gridY, int fillPercent, int tolerance, int smoothing, int iterations)
{
	srand(time(NULL));
	int progress = (float)iterations / (float)10;

	int sumH0 = 0;
	int sumH1 = 0;

	int minH0 = 100000;
	int minH1 = 100000;
	int maxH0 = 0;
	int maxH1 = 0;

	std::vector<int> H0;
	std::vector<int> H1;

	for (int i = 0; i < iterations; ++i)
	{
		// randomly fill the grid.
		Grid grid(gridX, gridY);
		Landscape::RandomFill(grid, fillPercent);

		// smooth the grid.
		//Grid smooth = Landscape::Smooth(grid, tolerance, 1);
		grid.Print();

		// convert to a cubical set and analyze the homology.
		//CubicalSet K = CubeSystem::GetCubicalSet(smooth);
		CubicalSet K = CubeSystem::GetCubicalSet(grid);

		std::cout << "Computing homology..." << std::endl;
		std::vector<std::vector<int>> homologies = CubeSystem::GetHomologyLinBox(K, true);

		// keep track:
		int& zero = homologies[0][0];
		int& one = homologies[1][0];
		sumH0 += zero;
		sumH1 += one;
		H0.push_back(zero);
		H1.push_back(one);

		// min/max:
		if (zero < minH0)
		{
			minH0 = zero;
		}
		else if (zero > maxH0)
		{
			maxH0 = zero;
		}
		if (one < minH1)
		{
			minH1 = one;
		}
		else if (one > maxH1)
		{
			maxH1 = one;
		}

	}

	// average:
	float averageH0 = (float)sumH0 / (float)iterations;
	float averageH1 = (float)sumH1 / (float)iterations;

	float mSumH0 = 0;
	float mSumH1 = 0;
	for (int i = 0; i < iterations; ++i)
	{
		mSumH0 += (H0[i] - averageH0)*(H0[i] - averageH0);
		mSumH1 += (H1[i] - averageH1)*(H1[i] - averageH1);
	}
	float varianceH0 = (float)1 / (float)(iterations - 1) * mSumH0;
	float varianceH1 = (float)1 / (float)(iterations - 1) * mSumH1;

	std::cout << "Grid size: " << gridX << " by " << gridY << std::endl;
	std::cout << "Random fill: " << fillPercent << std::endl;
	std::cout << "Tolerance: " << tolerance << std::endl;
	std::cout << "Smoothing: " << smoothing << std::endl;
	std::cout << "Total iterations: " << iterations << std::endl;
	std::cout << std::endl;
	std::cout << "Min H0: " << minH0 << std::endl;
	std::cout << "Max H0: " << maxH0 << std::endl;
	std::cout << "Average H0: " << averageH0 << std::endl;
	std::cout << "Standard deviation H0: " << std::sqrt(varianceH0) << std::endl;
	std::cout << std::endl;
	std::cout << "Min H1: " << minH1 << std::endl;
	std::cout << "Max H1: " << maxH1 << std::endl;
	std::cout << "Average H1: " << averageH1 << std::endl;
	std::cout << "Standard deviation H1: " << std::sqrt(varianceH1) << std::endl;
	std::cout << std::endl;
}


int main()
{
	AnalyzeCellularAutomata(50, 50, 40, 3, 0, 1);
	
}



// using CCR, it takes 4599 seconds to do a 20x20 grid, correctly reports H_0 = 1 and H_1 = 18.
