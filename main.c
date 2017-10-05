#include "common.h"

int main(){
	// Setup intial position
	position *current_position;
	char initboard[8][8]={"pppppppp","........","........",
		"........","........","........","........","PPPPPPPP"};
	current_position = createNewPosition(initboard);
	
	displayBoard(current_position);

	// run the game upto 20 moves

	for (int i = 0; i < 20; ++i)
	{
		// print whose turn it is
		printf("Its is %s's turn\n", (current_position->turn=='w')?"White":"Black");
		current_position = getBestMove(current_position, 3);
		displayBoard(current_position);
	}
	
	deletePosition(current_position);
	return 0;
}
