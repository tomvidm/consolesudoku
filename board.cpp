#include "board.h"

#include <iostream>

using namespace std;

void Board::print() const
{
	for (uint r = 0; r < board_size*board_size; r++)
	{
		if (r % board_size == 0 && r > 0)
		{
			cout << "\t---------------------" << endl;
		}

		cout << r << "\t";

		for (uint c = 0; c < board_size*board_size; c++)
		{
			if ((c == board_size || c == 2 * board_size))
			{
				cout << "| ";
			}
			if (board.get(r, c) == 0)
			{
				cout << ". ";
				continue;
			}
			else
			{
				cout << board.get(r, c) << " ";
			}
			
		}
		
		cout << endl;
	}
}

void Board::derp() const
{
	cout << "================================" << endl;
	cout << "== Allowed in rows =============" << endl << endl;
	cout << "          1 2 3 4 5 6 7 8 9" << endl << endl;
	uint counter = 1;
	for (auto i : r_nums)
	{
		cout << "row " << counter << "     ";
		counter++;

		for (auto j : i)
		{
			cout << (int)j << " ";
		}
		cout << endl;
	}
	cout << "================================" << endl;
	cout << "== Allowed in columns ==========" << endl << endl;
	cout << "         1 2 3 4 5 6 7 8 9" << endl << endl;
	counter = 1;
	for (auto i : c_nums)
	{
		cout << "column " << counter << "  ";
		counter++;

		for (auto j : i)
		{
			cout << (int)j << " ";
		}
		cout << endl;
	}
	cout << "================================" << endl;
	cout << "== Allowed in boxes ============" << endl << endl;
	cout << "          1 2 3 4 5 6 7 8 9" << endl << endl;
	counter = 1;
	for (auto i : s_nums)
	{
		cout << "square " << counter << "  ";
		counter++;

		for (auto j : i)
		{
			cout << (int)j << " ";
		}
		cout << endl;
	}
}

/*	open_from_file
Read a sudoku board from a formatted .txt file. The loaded file should contain
a single digit number on the first line, followed by N lines with N single digits each.
*/

void Board::open_from_file(std::string fname)
{
	cout << "Loading board from file " << fname << endl;

	std::ifstream file(fname);
	std::string line; getline(file, line);
	uint new_size = (uint)line[0] - 48;
	

	if (file.is_open() && new_size != 0)
	{
		if (board_size != new_size)
		{
			this->board_size = new_size;
			board.clear();
			board.setDim(board_size*board_size, board_size*board_size);
			board.init();
		}

		uint counter = 0;
		while (getline(file, line) && counter < board_size*board_size)
		{
			for (uint i = 0; i < board_size*board_size; i++)
			{
				uint new_val = (uint)line[i] - 48;
				board.edit(counter, i, new_val);
				if (new_val > 0)
				{
					flip(counter, i, new_val);
				}
			}
			counter++;
		}
		file.close();

		cout << "Successfully loaded game from " << fname << endl << endl;
		return;
	}
	cout << "Could not open " << fname << endl << endl;
}

void Board::place(uint row, uint col, uint val)
{
	board.edit(row, col, val);

	if (val > 0)
	{
		flip(row, col, val);
	}
}

void Board::flip(uint row, uint col, uint val)
{
	r_nums[row][val - 1] = r_nums[row][val - 1] != 1;
	c_nums[col][val - 1] = c_nums[col][val - 1] != 1;
	s_nums[rc_to_box(row, col, board_size)][val - 1] = s_nums[rc_to_box(row, col, board_size)][val - 1] != 1;
}

Board::Board(uint n)
	: board_size(n)
{
	board.setDim(n*n, n*n);
	board.init();

	for (uint r = 0; r < n*n; r++)
	{
		std::vector<bool> emptyBoolVector;
		r_nums.push_back(emptyBoolVector);
		c_nums.push_back(emptyBoolVector);
		s_nums.push_back(emptyBoolVector);

		for (uint c = 0; c < n*n; c++)
		{
			board.edit(r, c, 0);

			r_nums[r].push_back(true);
			c_nums[r].push_back(true);
			s_nums[r].push_back(true);
		}
	}
}

uint rc_to_box(uint r, uint c, uint n)
{
	return (((r) - (r) % n)) + ((c) - (c) % n) / n;
}