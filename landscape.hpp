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
	//int GetNeighbors(int x, int y, int neighborScanDistance);

	// apply cellular automata ruleset to smooth the map.
	//Grid Smooth(Grid grid, int neighborTolerance, int neighborScanDistance);


	


















}
