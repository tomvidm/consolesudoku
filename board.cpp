#include "board.h"

#include <iostream>

using namespace std;

void Board::print() const
{
	cout << "===========================" << endl;
	for (uint r = 0; r < board_size*board_size; r++)
	{
		cout << r << " | ";
		for (uint c = 0; c < board_size*board_size; c++)
		{
			cout << board.get(r, c) << " ";
			if ((c + 1) % board_size == 0)
			{
				cout << "| ";
			}
		}
		cout << endl;
	}
	cout << "===========================" << endl;
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