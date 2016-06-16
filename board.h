#pragma once

#include <string>
#include <fstream>

#include "table.h"

class Board
{
private:
	Table<uint> board;
	std::vector<std::vector<bool>> r_nums;
	std::vector<std::vector<bool>> c_nums;
	std::vector<std::vector<bool>> s_nums;
	uint board_size;

public:
	Board(uint n);

	void open_from_file(std::string fname);
	void place(uint row, uint col, uint val);
	void flip(uint row, uint col, uint val);

	void print() const;
	void printLegal() const;
	void derp() const;

	uint num_legal_moves(uint r, uint c) const;
};

uint rc_to_box(uint r, uint c, uint n);