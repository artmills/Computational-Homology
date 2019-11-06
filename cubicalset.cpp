#include "cubicalset.hpp"


CubicalSet::CubicalSet(std::vector<Cube> cubes)
{
	this->cubes = cubes;
}
CubicalSet::CubicalSet(){}
CubicalSet::~CubicalSet(){}


Cube& CubicalSet::operator[](int i)
{
	return cubes[i];
}
void CubicalSet::addCube(Cube cubes)
{
	this->cubes.push_back(cubes);
}
