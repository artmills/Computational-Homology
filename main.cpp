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
		//std::cout << element.second << std::endl;
	}
}




int main()
{
	std::cout << std::endl;
	
	std::cout << "Testing cubes: " << std::endl;

	Cube cube1;
	cube1.addInterval(Interval(1));
	cube1.addInterval(Interval(6));
	cube1.addInterval(Interval(8));
	cube1.addInterval(Interval(9));
	std::cout << "Cube 1: " << std::endl;
	cube1.Print();
	std::cout << std::endl;

	Cube cube2;
	cube2.addInterval(Interval(1));
	cube2.addInterval(Interval(3));
	cube2.addInterval(Interval(8));
	cube2.addInterval(Interval(9));
	//std::cout << "Cube 2: " << std::endl;
	//cube2.Print();
	//std::cout << std::endl;

	
	std::vector<Cube> cubes = {cube1, cube2};
	CubicalSet K(cubes);


	std::unordered_map<Cube, int, KeyHasher> faces = CubeSystem::PrimaryFaces(cube1);
	std::cout << std::endl;
	Print(faces);

	/*
	std::unordered_map<Cube, int, KeyHasher> test = { {cube1, 1}, {cube2, 2} };
	// how to update the value of a key in the unordered map.
	test[cube2] = 7;

	*/


	std::cout << std::endl;
}







