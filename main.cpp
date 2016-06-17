#include "table.h"
#include "board.h"
#include <iostream>

using namespace std;

int main()
{
	Board gameboard(3);

	gameboard.open_from_file("test.txt");
	gameboard.print();
	cout << endl << endl;
	gameboard.simpleSolve();
	gameboard.print();
	return 0;
}