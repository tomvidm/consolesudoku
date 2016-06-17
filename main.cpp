#include "table.h"
#include "board.h"
#include <iostream>

using namespace std;

int main()
{
	Board gameboard(3);

	gameboard.open_from_file("test.txt");
	gameboard.print();
	while (!gameboard.isSolved())
	{
		cout << endl << endl;
		gameboard.naiveSolveStep();
		gameboard.print();
		system("pause");
	}
	
	return 0;
}