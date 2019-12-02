#include "landscape.hpp"

void Landscape::RandomFill(Grid& grid, int percent)
{
	// seed the random generator.
	//srand(time(0 + seedShift));
	//srand(time(NULL));

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


int Landscape::GetNeighbors(Grid& grid, int x, int y, int neighborScanDistance)
{
	// since tiles are still considered to be path-connected
	// if they are diagonal, we will still consider diagonal
	// tiles as neighbors.
	int count = 0;
	for (int i = x - neighborScanDistance; i <= x + neighborScanDistance; ++i)
	{
		// ignore tiles outside the bounds of the map.
		if (i < 0 || i >= grid.getColumns())
		{
			continue;
		}
		
		for (int j = y - neighborScanDistance; j <= y + neighborScanDistance; ++j)
		{
			// ignore tiles outside the bounds of the map.	
			if (j < 0 || j >= grid.getRows())
			{
				continue;
			}

			// ignore itself.
			if (j == y && i == x)
			{
				continue;
			}

			// now check if (i, j) is an activated square.
			if (grid.getElement(i, j))
			{
				++count;
			}
		}
	}
	return count;
}


Grid Landscape::Smooth(Grid& grid, int neighborTolerance, int neighborScanDistance)
{
	// get a blank grid. this grid will be filled in by
	// scanning the given grid. 
	Grid smoothGrid(grid.getRows(), grid.getColumns());

	for (int x = 0; x < grid.getRows(); ++x)
	{
		for (int y = 0; y < grid.getColumns(); ++y)
		{
			// check if we should convert the grid to its
			// neighbors' orientation.
			if (GetNeighbors(grid, x, y, neighborScanDistance) >= neighborTolerance)
			{
				smoothGrid.setElement(x, y, 1);	
			}
			else
			{
				smoothGrid.setElement(x, y, 0);
			}
		}
	}
	return smoothGrid;
}



Grid3D Landscape::CreateSphere(int radius)
{
	// testing: 3 seems to work well. 2 does not work.
	const int tolerance = 5;

	// odd numbers are easier to work with so we get an exact
	// center for the sphere.
	int diameter = 2 * radius;
	int center = (diameter + 1) / 2;
	int squareRadius = radius * radius;

	Grid3D block(diameter+1, diameter+1, diameter+1);
	for (int z = 0; z < diameter+1; ++z)
	{
		for (int x = 0; x < diameter+1; ++x)
		{
			for (int y = 0; y < diameter+1; ++y)
			{
				int pyth = (x-center)*(x-center) + (y-center)*(y-center) + (z-center)*(z-center);
				if (squareRadius - tolerance <= pyth && pyth <= squareRadius + tolerance)
				{
					block.setElement(x, y, z, 1);
				}
			}
		}
	}

	return block;
}


Grid3D Landscape::CreateBox(int length, int width, int height)
{
	Grid3D box(length, width, height);

	// bottom and top faces:
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			box.setElement(i, j, 0, 1);
			box.setElement(i, j, height - 1, 1);
		}
	}

	// front and back faces:
	// y constant: y = 0 and y = width;	
	for (int i = 0; i < length; ++i)
	{
		for (int k = 0; k < height; ++k)
		{
			box.setElement(i, 0, k, 1);	
			box.setElement(i, width - 1, k, 1);	
		}
	}

	// left and right faces:
	// x constant:  = 0 and x = length;	
	for (int j = 0; j < width; ++j)
	{
		for (int k = 0; k < height; ++k)
		{
			box.setElement(0, j, k, 1);	
			box.setElement(length - 1, j, k, 1);	
		}
	}

	return box;
	
}
