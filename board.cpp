#include "board.h"

#include <iostream>

using namespace std;

void Board::print() const
{
	for (uint r = 0; r < board_size*board_size; r++)
	{
		if (r % board_size == 0 && r > 0)
		{
			cout << endl;
		}

		cout << r << "\t";

		for (uint c = 0; c < board_size*board_size; c++)
		{
			if (c % board_size == 0 && c > 0)
			{
				cout << "  ";
			}
			cout << board.get(r, c) << " ";
			
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
				board.edit(counter, i, (uint)line[i] - 48);
			}
			counter++;
		}
		file.close();

		cout << "Successfully loaded game from " << fname << endl << endl;
		return;
	}
	cout << "Could not open " << fname << endl << endl;
}

Board::Board(uint n)
	: board_size(n)
{
	board.setDim(n*n, n*n);
	board.init();

	for (uint r = 0; r < n*n; r++)
	{
		for (uint c = 0; c < n*n; c++)
		{
			board.edit(r, c, 0);
		}
	}
}