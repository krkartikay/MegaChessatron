#include "common.h"

int main(){
	// code for testing display function
	position* new_position;
	char initboard[8][8]={"pppppppp","........","........","........","........","........","........","PPPPPPPP"};
	new_position = createNewPosition(initboard);
	displayBoard(new_position);
	getBestMove(new_position, 5);
	move newmove;
	newmove.move = 0x37653865; //e7e8
	bool x = isMoveValid(newmove,new_position);
	printf("move-valid = %d.\n", x);
	deletePosition(new_position);
	return 0;
}
