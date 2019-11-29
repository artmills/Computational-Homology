#pragma once

#include <ctime>
#include <cstdlib>

#include "grid.hpp"

// generates landscapes	so that their homology groups can be computed.
namespace Landscape
{
	// "randomly" fill the map. can specify approximately what percent of
	// the map should be filled.
	void RandomFill(Grid& grid, int percent);

	//
	// cellular automata:
	//
	
	// get the number of neighboring activated tiles.
	int GetNeighbors(Grid& grid, int x, int y, int neighborScanDistance);

	// apply cellular automata ruleset to smooth the map.
	Grid Smooth(Grid& grid, int neighborTolerance, int neighborScanDistance);

	
	// create a 3D sphere.
	Grid3D CreateSphere(int radius);

	// create a 3D box.
	Grid3D CreateBox(int length, int width, int height);
















}
