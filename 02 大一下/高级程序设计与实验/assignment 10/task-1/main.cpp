/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "vector.h"
#include "console.h"
#include "grid.h"
#include "simpio.h"

bool is_valid_maigc_square(const Grid<int> &grid)
{
	auto n = grid.numRows();
	auto sum = -1;

	for (int col = 0; col < n; ++col)
	{
		auto col_sum = 0;
		for (int row = 0; row < n; ++row)
			col_sum += grid[row][col];
		if (sum == -1)
			sum = col_sum;
		else if (sum != col_sum)
			return false;
	}

	for (int row = 0; row < n; ++row)
	{
		auto row_sum = 0;
		for (int col = 0; col < n; ++col)
			row_sum += grid[row][col];
		if (sum != row_sum)
			return false;
	}

	auto diag_sum = 0;
	for (int i = 0; i < n; ++i)
		diag_sum += grid[i][i];
	if (sum != diag_sum)
		return false;

	diag_sum = 0;
	for (int i = 0; i < n; ++i)
		diag_sum += grid[i][n - i - 1];
	if (sum != diag_sum)
		return false;

	return true;
}

void check_square_helper(Grid<int> &grid, int pos_cnt, const Vector<GridLocation> &blank_spaces, bool &result)
{
	if (pos_cnt >= blank_spaces.size())
	{
		if (is_valid_maigc_square(grid))
			result = true;
		return;
	}

	auto n = grid.numCols();

	for (int i = 1; i <= n; ++i)
	{
		grid[blank_spaces[pos_cnt]] = i;
		check_square_helper(grid, pos_cnt + 1, blank_spaces, result);
		if (result)
			return;
	}
	grid[blank_spaces[pos_cnt]] = 0;
}

bool check_square(Grid<int> &grid)
{
	auto n = grid.numRows();
	Vector<GridLocation> blank_spaces{};

	for (auto row = 0; row < n; ++row)
		for (auto col = 0; col < n; ++col)
			if (grid[row][col] == 0)
				blank_spaces += GridLocation(row, col);

	bool result = false;
	check_square_helper(grid, 0, blank_spaces, result);

	return result;
}

int main()
{
	std::ifstream input_file("test.txt");

	Grid<int> grid{};

	input_file >> grid;

	if (grid.numCols() != grid.numRows())
	{
		std::cerr << "This grid is not a square!" << std::endl;
		return EXIT_FAILURE;
	}

	auto result = check_square(grid);

	if (result)
		std::cout << grid.toString2D() << std::endl;
	else
		std::cout << "无解" << std::endl;

	return EXIT_SUCCESS;
}
