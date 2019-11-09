#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

#include "intmat.hpp"
#include "matsystem.hpp"
#include "homology.hpp"
#include "interval.hpp"
#include "keyhasher.hpp"
#include "cubicalset.hpp"
#include "cubesystem.hpp"
#include "typedef.hpp"


IntMat CreateExample1()
{
	return IntMat(2, 4, 4, -6, 6, 12, 10, -4, -16);	
}
IntMat CreateExample2()
{
	IntMat ex(3, 5);
	std::vector<int> row0 = {1, 6, 3, 7, 2};
	std::vector<int> row1 = {0, 0, 2, 5, 1};
	std::vector<int> row2 = {0, 2, 5, 1, 2};
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
	std::vector<int> P2row0 = {1, 1};
	std::vector<int> P2row1 = {1, 1};
	std::vector<int> P2row2 = {-1, -1};
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

std::vector<Cube> Get2DHole()
{
	std::vector<Cube> cubes;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (i == 1 && j == 1)
			{
				continue;
			}
			Cube cube;
			cube.addInterval(i);
			cube.addInterval(j);
			cubes.push_back(cube);
		}
	}
	return cubes;
}



int main()
{
	std::cout << std::endl;
	
	std::cout << "Testing cubes: " << std::endl;

	/*
	Cube cube1;
	cube1.addInterval(Interval(0, 0));
	cube1.addInterval(Interval(0));
	std::cout << "Cube 1: " << std::endl;
	cube1.Print();
	std::cout << std::endl;

	Cube cube2;
	cube2.addInterval(Interval(1, 1));
	cube2.addInterval(Interval(0));
	std::cout << "Cube 2: " << std::endl;
	cube2.Print();
	std::cout << std::endl;

	Cube cube3;
	cube3.addInterval(Interval(0));
	cube3.addInterval(Interval(0, 0));
	std::cout << "Cube 3: " << std::endl;
	cube3.Print();
	std::cout << std::endl;

	Cube cube4;
	cube4.addInterval(Interval(0));
	cube4.addInterval(Interval(1, 1));
	std::cout << "Cube 4: " << std::endl;
	cube4.Print();
	std::cout << std::endl;
	
	std::vector<Cube> cubes = {cube1, cube2, cube3, cube4};
	*/

	Cube cube1;
	cube1.addInterval(Interval(0));
	cube1.addInterval(Interval(0));
	cube1.addInterval(Interval(0));
	std::cout << "Cube 1: " << std::endl;
	cube1.Print();
	std::cout << std::endl;

	std::vector<Cube> cubes = {cube1};


	CubicalSet K(Get2DHole());

	std::cout << std::endl;

	std::vector<std::unordered_map<Cube, int, KeyHasher>> test = CubeSystem::CubicalChainGroups(K);

	for (int i = 0; i < test.size(); ++i)
	{
		std::cout << "Generators of C_" << i << ": " << std::endl;
		Print(test[i]);
		std::cout << std::endl;
	}

	std::vector<std::vector<Cube>> coordinates;
	for (int i = 0; i < test.size(); ++i)
	{
		coordinates.push_back(CubeSystem::GetCoordinates(test[i]));
	}

	std::vector<IntMat> matrices = CubeSystem::BoundaryOperatorMatrix(coordinates);
	for (int i = 0; i < matrices.size(); ++i)
	{
		matrices[i].Print();
	}

	std::cout << std::endl;

	std::vector<Quotient> homologies = Homology::HomologyGroupOfChainComplex(matrices);

	Homology::AnalyzeHomology(homologies);


	std::vector<Cube> hole = Get2DHole();
	for (int i = 0; i < hole.size(); ++i)
	{
		hole[i].Print();
	}









	std::cout << std::endl;
}







