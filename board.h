#pragma once

#include <string>
#include <fstream>

#include "table.h"

class Board
{
private:
	Table<uint> board;
	uint board_size;

	

public:
	Board(uint n);

	void open_from_file(std::string fname);

	void print() const;
};