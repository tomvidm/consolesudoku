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

void Board::printLegal() const
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
			if (board.get(r, c) != 0)
			{
				cout << ". ";
				continue;
			}
			else
			{
				cout << num_legal_moves(r, c) << " ";
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
	for (auto i : row_legalMoves)
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
	for (auto i : col_legalMoves)
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
	for (auto i : box_legalMoves)
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

void Board::derp(uint r, uint c) const
{
	cout << "      1 2 3 4 5 6 7 8 9" << endl;
	cout << "      | | | | | | | | |" << endl;
	cout << "Row " << r << ": ";
	uint s = rc_to_box(r, c, board_size);
	for (uint i = 0; i < board_size*board_size; i++)
	{
		cout << (uint)row_legalMoves[r][i] << " ";
	}
	cout << endl;
	cout << "Col " << c << ": ";
	for (uint i = 0; i < board_size*board_size; i++)
	{
		cout << (uint)col_legalMoves[c][i] << " ";
	}
	cout << endl;
	cout << "Box " << s << ": ";
	for (uint i = 0; i < board_size*board_size; i++)
	{
		cout << (uint)box_legalMoves[s][i] << " ";
	}
	cout << endl << endl;
}

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
					empty_squares--;
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

uint Board::num_legal_moves(uint r, uint c) const
{
	uint counter = 0;
	for (uint i = 0; i < board_size*board_size; i++)
	{
		if (row_legalMoves[r][i]  && col_legalMoves[c][i] && box_legalMoves[rc_to_box(r, c, board_size)][i])
		{
			counter++;
		}
	}
	return counter;
}

void Board::place(uint row, uint col, uint val)
{
	if (num_legal_moves(row, col) > 0)
	{
		cout << "PLACING" << endl;
		if (board.get(row, col) != 0)
		{
			flip(row, col, board.get(row, col));
		}

		board.edit(row, col, val);
		flip(row, col, val);

		if (val == 0)
		{
			empty_squares--;
		}
	}
}

void Board::flip(uint row, uint col, uint val)
{
	row_legalMoves[row][val - 1] = row_legalMoves[row][val - 1] != 1;
	col_legalMoves[col][val - 1] = col_legalMoves[col][val - 1] != 1;
	box_legalMoves[rc_to_box(row, col, board_size)][val - 1] = box_legalMoves[rc_to_box(row, col, board_size)][val - 1] != 1;
}

Board::Board(uint n)
	: board_size(n)
{
	board.setDim(n*n, n*n);
	board.init();
	empty_squares = n * n * n * n;
	for (uint r = 0; r < n*n; r++)
	{
		std::vector<bool> emptyBoolVector;
		row_legalMoves.push_back(emptyBoolVector);
		col_legalMoves.push_back(emptyBoolVector);
		box_legalMoves.push_back(emptyBoolVector);

		for (uint c = 0; c < n*n; c++)
		{
			board.edit(r, c, 0);

			row_legalMoves[r].push_back(true);
			col_legalMoves[r].push_back(true);
			box_legalMoves[r].push_back(true);
		}
	}
}

void Board::simpleSolve()
{
	CandidateList candidates = listCandidates();

	while (candidates.size() > 0)
	{
		for (auto cand : candidates)
		{
			uint r = cand.second.first;
			uint c = cand.second.second;
			uint s = rc_to_box(r, c, board_size);

			for (uint i = 0; i < board_size*board_size; i++)
			{
				if (row_legalMoves[r][i] && col_legalMoves[c][i] && box_legalMoves[s][i])
				{
					place(r, c, i + 1);
				}
			}
		}
		candidates = listCandidates();

		print();
		system("pause");
	}

}

CandidateList Board::listCandidates() const
{
	std::list<pair<uint, pair<uint, uint>>> candidateList;
	for (uint r = 0; r < board_size*board_size; r++)
	{
		for (uint c = 0; c < board_size*board_size; c++)
		{
			if (board.get(r, c) == 0)
			{
				uint n = num_legal_moves(r, c);
				pair<uint, uint> coordinates = make_pair(r, c);
				candidateList.push_back(make_pair(n, coordinates));
			}
		}
	}
	candidateList.sort();
	return candidateList;
}

uint rc_to_box(uint r, uint c, uint n)
{
	return (((r) - (r) % n)) + ((c) - (c) % n) / n;
}

