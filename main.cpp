#include "table.h"
#include "board.h"

int main()
{
	Board gameboard(3);
	gameboard.open_from_file("test.txt");
	gameboard.print();
	gameboard.derp();
	return 0;
}