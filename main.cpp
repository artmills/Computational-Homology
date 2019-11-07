#include <iostream>
#include <vector>
#include <unordered_map>

#include "intmat.hpp"
#include "matsystem.hpp"
#include "homology.hpp"
#include "interval.hpp"
#include "keyhasher.hpp"


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




int main()
{
	std::cout << std::endl;
	
	std::vector<IntMat> matrices = GetRP2();	
	std::vector<Quotient> homologies = Homology::HomologyGroupOfChainComplex(matrices);
	std::cout << "Homology groups of RP2: " << std::endl;
	for (int i = 0; i < homologies.size(); ++i)
	{
		std::cout << "Homology group H_" << i << std::endl;
		std::cout << "U = " << std::endl;
		homologies[i].getU().Print();
		std::cout << "B = " << std::endl; 
		homologies[i].getB().Print();
		std::cout << "s = " << homologies[i].getS() << std::endl;
		std::cout << std::endl;
	}
	Homology::AnalyzeHomology(homologies);
	std::cout << std::endl;
	std::cout << std::endl;

	matrices = GetTorus();	
	homologies = Homology::HomologyGroupOfChainComplex(matrices);
	std::cout << "Homology groups of the torus: " << std::endl;
	for (int i = 0; i < homologies.size(); ++i)
	{
		std::cout << "Homology group H_" << i << std::endl;
		std::cout << "U = " << std::endl;
		homologies[i].getU().Print();
		std::cout << "B = " << std::endl; 
		homologies[i].getB().Print();
		std::cout << "s = " << homologies[i].getS() << std::endl;
		std::cout << std::endl;
	}
	Homology::AnalyzeHomology(homologies);
	std::cout << std::endl;
	std::cout << std::endl;

	matrices = GetKleinBottle();	
	homologies = Homology::HomologyGroupOfChainComplex(matrices);
	std::cout << "Homology groups of the Klein bottle: " << std::endl;
	for (int i = 0; i < homologies.size(); ++i)
	{
		std::cout << "Homology group H_" << i << std::endl;
		std::cout << "U = " << std::endl;
		homologies[i].getU().Print();
		std::cout << "B = " << std::endl; 
		homologies[i].getB().Print();
		std::cout << "s = " << homologies[i].getS() << std::endl;
		std::cout << std::endl;
	}
	Homology::AnalyzeHomology(homologies);
	std::cout << std::endl;
	std::cout << std::endl;

	matrices = GetMagicalTetrahedron();	
	homologies = Homology::HomologyGroupOfChainComplex(matrices);
	std::cout << "Homology groups of the identified tetrahedron: " << std::endl;
	for (int i = 0; i < homologies.size(); ++i)
	{
		std::cout << "Homology group H_" << i << std::endl;
		std::cout << "U = " << std::endl;
		homologies[i].getU().Print();
		std::cout << "B = " << std::endl; 
		homologies[i].getB().Print();
		std::cout << "s = " << homologies[i].getS() << std::endl;
		std::cout << std::endl;
	}
	Homology::AnalyzeHomology(homologies);
	std::cout << std::endl;
	std::cout << std::endl;

	matrices = GetParachute();	
	homologies = Homology::HomologyGroupOfChainComplex(matrices);
	std::cout << "Homology groups of the parachute: " << std::endl;
	for (int i = 0; i < homologies.size(); ++i)
	{
		std::cout << "Homology group H_" << i << std::endl;
		std::cout << "U = " << std::endl;
		homologies[i].getU().Print();
		std::cout << "B = " << std::endl; 
		homologies[i].getB().Print();
		std::cout << "s = " << homologies[i].getS() << std::endl;
		std::cout << std::endl;
	}
	Homology::AnalyzeHomology(homologies);
	std::cout << std::endl;
	std::cout << std::endl;

	/*
	std::cout << "Testing cubes: " << std::endl;
	Interval i1(1);
	Interval i2(2);
	Interval i3(1);
	
	std::unordered_map<Interval, int, KeyHasher> test = { {i1, 1}, {i2, 2} };
	test.insert( {i2, 9} );
	std::cout << test[i2] << std::endl;
	*/
}







