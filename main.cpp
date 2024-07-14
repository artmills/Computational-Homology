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
	
	/*
	Grid grid(3, 3);
	grid.setElement(0, 0, 1);
	grid.setElement(0, 1, 1);
	grid.setElement(0, 2, 1);
	grid.setElement(1, 0, 1);
	grid.setElement(1, 1, 1);
	grid.setElement(1, 2, 1);
	grid.setElement(2, 0, 1);
	grid.setElement(2, 1, 1);
	grid.setElement(2, 2, 1);
	grid.Print();
	*/

	/*
	Grid grid(2, 2);
	grid.setElement(0, 0, 1);
	grid.setElement(0, 1, 1);
	grid.setElement(1, 0, 1);
	grid.setElement(1, 1, 1);
	grid.Print();
	*/

	/*
	Grid3D grid(1, 1, 1);
	grid.setElement(0, 0, 0, 1);
	grid.Print();
	*/

	/*
	Grid3D grid(1, 1, 3);
	grid.setElement(0, 0, 0, 1);
	grid.setElement(0, 0, 1, 1);
	grid.setElement(0, 0, 2, 1);
	grid.Print();
	*/
	/*
	Grid3D grid(3, 3, 3);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				grid.setElement(i, j, k, 1);
			}
		}
	}
	grid.setElement(1, 1, 1, 0);
	grid.Print();
	*/
	/*
	Grid3D grid(2, 2, 2);
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				grid.setElement(i, j, k, 1);
			}
		}
	}
	grid.setElement(1, 1, 1, 0);
	*/
	
	/*
	Grid3D grid(2, 2, 1);
	grid.setElement(0, 0, 0, 1);
	grid.setElement(0, 1, 0, 1);
	grid.setElement(1, 0, 0, 1);
	grid.setElement(1, 1, 0, 1);
	grid.Print();
	*/


	/*
	CubicalSet K = CubeSystem::GetCubicalSet(grid);
	std::vector<std::vector<int>> homologies = CubeSystem::GetHomologyLinBox(K, true);
	*/

}
