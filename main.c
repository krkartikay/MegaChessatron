#include "common.h"

int main(){
	#ifdef DEBUG
	runTests();
	return 0;
	#endif

	// Setup intial position
	position *current_position;
	char initboard[8][8]={"rnbqkbnr","pppppppp","........",
		"........","........","........","PPPPPPPP","RNBQKBNR"};
	current_position = createNewPosition(initboard);
	
	displayBoard(current_position);

	// run the game upto 20 moves

	while(isGameRunning(current_position))
	{
		// print whose turn it is
		printf("Its is %s's turn\n", (current_position->turn=='w')?"White":"Black");
		current_position = getBestMove(current_position, 7);
		printf("Evaluation of current position: %d\n",current_position->evaluation);
		displayBoard(current_position);
	}
	
	deletePosition(current_position);
	return 0;
}