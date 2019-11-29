#include "grid.hpp"


/********* constructors/destructors *********/

Grid::Grid(int rows, int columns)
{
	// initialize vectors for the matrix data
	for (int i = 0; i < rows; ++i)
	{
		std::vector<bool> blankColumn(columns);
		grid.push_back(blankColumn);
	}
}
Grid::~Grid(){}





/********* initializing a matrix row by row or column by column *********/

void Grid::setRow(int row, std::vector<bool> data)
{
	grid[row] = data;
}

void Grid::setColumn(int column, std::vector<bool> data)
{
	for (int i = 0; i < getRows(); ++i)
	{
		grid[i][column] = data[i];
	}
}






/********* getters/setters for rows/columns/elements *********/

int Grid::getRows()
{
	return grid.size();
}
int Grid::getColumns()
{
	return grid[0].size();
}

bool Grid::getElement(int row, int column)
{
	return this->grid[row][column];
}
void Grid::setElement(int row, int column, bool data)
{
	this->grid[row][column]=data;
}

void Grid::Flip(int row, int column)
{
	this->grid[row][column] = !grid[row][column];
}



/********* Utility *********/

void Grid::Print()
{
	if (this->grid.size() == 0)
	{
		std::cout << "[ ]" << std::endl;
	}
	else 
	{
		for (int j = getColumns() - 1; j >= 0; --j)
		{
			for (int i = 0; i < getRows(); ++i)
			{
				if (i == 0)
				{
					std::cout << "  ";
				}
				if (grid[i][j])
				{
					std::cout << "&" << " ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}



/********* constructors/destructors *********/

Grid3D::Grid3D(int rows, int columns, int steps)
{
	// initialize grids.
	for (int k = 0; k < steps; ++k)
	{
		Grid blank(rows, columns);
		this->block.push_back(blank);
	}
}
Grid3D::~Grid3D(){}





/********* initializing a matrix row by row or column by column *********/

void Grid3D::setRow(int row, int step, std::vector<bool> data)
{
	block[step].setRow(row, data);
}

void Grid3D::setColumn(int column, int step, std::vector<bool> data)
{
	block[step].setColumn(column, data);
}







/********* getters/setters for rows/columns/elements *********/

int Grid3D::getRows()
{
	return this->block[0].getRows();
}
int Grid3D::getColumns()
{
	return this->block[0].getColumns();
}
int Grid3D::getSteps()
{
	return this->block.size();
}

bool Grid3D::getElement(int row, int column, int step)
{
	return this->block[step].getElement(row, column);
}
void Grid3D::setElement(int row, int column, int step, bool data)
{
	this->block[step].setElement(row, column, data);
}

void Grid3D::Flip(int row, int column, int step)
{
	this->block[step].Flip(row, column);
}



/********* Utility *********/

void Grid3D::PrintCrossSection(int step)
{
	this->block[step].Print();
}

void Grid3D::Print()
{
	for (int z = 0; z < getSteps(); ++z)
	{
		PrintCrossSection(z);
	}
}


