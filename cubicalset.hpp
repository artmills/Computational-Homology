#pragma once

#include <vector>
#include "cube.hpp"

// an array of cubes.
class CubicalSet
{

public:

	CubicalSet(std::vector<Cube> cubes);
	CubicalSet();
	~CubicalSet();

	Cube& operator[](int i);
	void addCube(Cube cubes);

private:

	int Dimension(std::vector<Cube> cubes);

	std::vector<Cube> cubes;

};
