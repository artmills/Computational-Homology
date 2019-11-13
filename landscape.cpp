#include "landscape.hpp"

void Landscape::RandomFill(Grid& grid, int percent)
{
	// seed the random generator.
	srand(time(0));

	// flip the elements in the grid.
	for (int x = 0; x < grid.getRows(); ++x)
	{
		for (int y = 0; y < grid.getColumns(); ++y)
		{
			int random = rand() % 101;
			if (random < percent)
			{
				grid.Flip(x, y);
			}
		}
	}
}
