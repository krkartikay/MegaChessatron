#include "common.h"

int main(){
	// code for testing display function
	position *initial_position, *new_position;
	char initboard[8][8]={"pppppppp","........","........",
		"........","........","........","........","PPPPPPPP"};
	initial_position = createNewPosition(initboard);
	new_position = getBestMove(initial_position, 2);
	displayBoard(new_position);
	deletePosition(initial_position);
	deletePosition(new_position);
	return 0;
}
