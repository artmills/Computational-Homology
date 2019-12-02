#include "cubicalset.hpp"


CubicalSet::CubicalSet(std::vector<Cube> cubes)
{
	for (int i = 0; i < cubes.size(); ++i)
	{
		int dim = cubes[i].Dimension();
		if (dim > this->dimension)
		{
			dimension = dim;
		}
		std::pair<Cube, int> p = {cubes[i], dim};
		this->cubes.insert(p);
	}
}
CubicalSet::CubicalSet(){}
CubicalSet::~CubicalSet(){}

int CubicalSet::Dimension()
{
	return this->dimension;
}

Cube CubicalSet::Pop()
{
	auto it = cubes.begin();
	Cube popped = it->first;
	cubes.erase(it);
	return popped;
}

bool CubicalSet::isEmpty()
{
	return (cubes.size() == 0)? true : false;
}

void CubicalSet::Print()
{
	for (auto it : cubes)
	{
		it.first.Print();
	}
}
