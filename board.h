#pragma once

#include <string>
#include <fstream>
#include <utility>
#include <algorithm>

#include "table.h"

struct Move
{
	uint row;
	uint col;
	uint val;
	uint old_val;
};

class Board
{
private:
	Table<uint> board;
	std::vector<std::vector<bool>> row_legalMoves;
	std::vector<std::vector<bool>> col_legalMoves;
	std::vector<std::vector<bool>> box_legalMoves;
	uint empty_squares;
	uint board_size;

public:
	Board(uint n);

	void open_from_file(std::string fname);
	void place(uint row, uint col, uint val);
	void flip(uint row, uint col, uint val);

	void print() const;
	void printLegal() const;
	void derp() const;
	void derp(uint r, uint c) const;

	uint num_legal_moves(uint r, uint c) const;

	void simpleSolve();
};

uint rc_to_box(uint r, uint c, uint n);