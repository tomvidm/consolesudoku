#pragma once

#include <vector>

typedef unsigned int uint;

template <typename T>
class Table
{
private:
	std::vector<std::vector<T>> data;
	uint rows;
	uint cols;

public:
	Table();
	Table(uint r, uint c);
	
	std::vector<T> getRow(uint r);
	std::vector<T> getCol(uint c);
	
	T get(uint r, uint c) const;
	Table cut(uint r0, uint c0, uint r1, uint c1);

	void edit(uint r, uint v, T val);
	void init();
	void setDim(uint r, uint c);
};

template <typename T>
Table<T>::Table()
{
	;
}

template <typename T>
Table<T>::Table(uint r, uint c)
	: rows(r), cols(c)
{
	init();
}

template <typename T>
std::vector<T> Table<T>::getRow(uint r)
{
	return data[r];
}

template <typename T>
std::vector<T> Table<T>::getCol(uint c)
{
	std::vector<T> col;

	for (uint r = 0; r < rows; r++)
	{
		col.push_back(data[r][c]);
	}
}

template <typename T>
T Table<T>::get(uint r, uint c) const
{
	return data[r][c];
}

template <typename T>
void Table<T>::edit(uint r, uint c, T val)
{
	data[r][c] = val;
}

template <typename T>
void Table<T>::init()
{
	std::vector<T> empty_row;
	for (uint c = 0; c < cols; c++)
	{
		empty_row.push_back(T());
	}
	for (uint r = 0; r < rows; r++)
	{
		data.push_back(empty_row);
	}
}

template <typename T>
void Table<T>::setDim(uint r, uint c)
{
	rows = r;
	cols = c;
}

template <typename T>
Table<T> Table<T>::cut(uint r0, uint c0, uint r1, uint c1)
{
	Table new_table(r1 - r0, c1 - c0);
	for (uint r = r0; r < r1; r++)
	{
		for (uint c = c0; c < c1; c++)
		{
			new_table.edit(r - r0, c - c0, get(r, c));
		}
	}
	return new_table;
}