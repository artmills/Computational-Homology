#include "cubicalset.hpp"


CubicalSet::CubicalSet(std::vector<Cube> cubes)
{
	for (int i = 0; i < cubes.size(); ++i)
	{
		std::pair<Cube, int> p = {cubes[i], cubes[i].Dimension()};
		this->cubes.insert(p);
	}
}
CubicalSet::CubicalSet(){}
CubicalSet::~CubicalSet(){}

