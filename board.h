#pragma once

#include "table.h"

class Board
{
private:
	Table<uint> board;
	uint board_size;

public:
	Board(uint n);
	void print() const;
};