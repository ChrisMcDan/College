// Sudoku Algorithm.cpp : Defines the entry point for the console application.
// Christopher McDaniel

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <stdlib.h>
#include <windows.h>

using std::cout;
using std::endl;

#define DIM 9
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

void usleep(unsigned long nanosec);

// Prints the Sudoku grid
void print_grid(int grid[DIM][DIM])
{
	for (int i = 0; i < DIM; i++)
	{
		cout << SPACE << SPACE << SPACE << SPACE << endl;
		cout << NEW_ROW << endl;
		for (int j = 0; j < DIM; j++)
		{
			cout << SPACE;
			if (BLANK == grid[i][j])
			{
				cout << SPACE;
			}
			else
			{
				cout << grid[i][j];
			}
			cout << SPACE;
			cout << LINE;
		}
	}
	cout << endl << NEW_ROW << endl << endl;;
}

bool used_in_row(int grid[DIM][DIM], int row, int num)
{
	for (int col = 0; col < DIM; col++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

bool used_in_col(int grid[DIM][DIM], int col, int num)
{
	for (int row = 0; row < DIM; row++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

bool used_in_box(int grid[DIM][DIM], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col] == num)
			{
				return true;
			}
	return false;
}

bool is_safe(int grid[DIM][DIM], int row, int col, int num)
{
	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

std::pair<int, int> get_unassigned_location(int grid[DIM][DIM])
{
	for (int row = 0; row < DIM; row++)
		for (int col = 0; col < DIM; col++)
			if (grid[row][col] == BLANK)
			{
				return std::make_pair(row, col);
			}
	return GRID_FULL;
}

bool solve_sudoku(int grid[DIM][DIM])
{
	if (GRID_FULL == get_unassigned_location(grid))
	{
		return true;
	}

	std::pair<int, int> row_and_col = get_unassigned_location(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;

	for (int num = 1; num <= 9; num++)
	{
		if (is_safe(grid, row, col, num))
		{
			grid[row][col] = num;

			if (solve_sudoku(grid))
			{
				return true;
			}

			grid[row][col] = BLANK;
		}
		
	}

	return 0;
}

int main()
{
	cout << "                               \n\n\tSudoku Solver\n\n                             " << endl << endl;

	int grid[DIM][DIM] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

	print_grid(grid);

	if (true == solve_sudoku(grid))
	{
		print_grid(grid);
	}
	else
	{
		cout << "No solution exists for the given Sudoku" << endl << endl;
	}
	{
		system("PAUSE");
	}
	return 0;
}