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



