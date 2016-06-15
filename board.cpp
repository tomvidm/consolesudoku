#include "board.h"

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