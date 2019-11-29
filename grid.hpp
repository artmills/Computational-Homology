#pragma once
#include <iostream>
#include <vector>

// a grid of bools that represents a cubical complex.
// true for an activated square, false for deactivated.
struct Grid
{

public:

	// constructors/destructor:
	Grid(int rows, int columns); // zero matrix
	~Grid();

	// initializing a matrix row by row or column by column:
	void setRow(int row, std::vector<bool> data);
	void setColumn(int column, std::vector<bool> data);

	// getters/setters for rows/columns/elements:
	int getRows();
	int getColumns();
	bool getElement(int row, int column);
	void setElement(int row, int column, bool data);
	void Flip(int row, int column);

	// utility:
	void Print();

private:

	// data: the actual entries of the matrix are stored here.
	std::vector<std::vector<bool>> grid;

};

// an array of grids.
struct Grid3D
{

public:

	// constructors/destructor:
	Grid3D(int rows, int columns, int steps); // zero matrix
	~Grid3D();

	// initializing a matrix row by row or column by column:
	void setRow(int row, int step, std::vector<bool> data);
	void setColumn(int column, int step, std::vector<bool> data);
	void setStep(int row, int column, std::vector<bool> data);

	// getters/setters for rows/columns/elements:
	int getRows();
	int getColumns();
	int getSteps();
	bool getElement(int row, int column, int step);
	void setElement(int row, int column, int step, bool data);
	void Flip(int row, int column, int step);

	// utility:
	void PrintCrossSection(int step);
	void Print();

private:

	// data: the actual entries of the matrix are stored here.
	std::vector<Grid> block;

};
