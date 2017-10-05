#include "common.h"

int main(){
	#ifdef DEBUG
		printf("DEBBUGGGING MODE\n");
		// run tests and quit
		runTests();
		return 0;
	#endif

	// Setup intial position
	position *current_position;
	char initboard[8][8]={"........","pppppppp","........",
		"........","........","........","PPPPPPPP","........"};
	current_position = createNewPosition(initboard);
	
	displayBoard(current_position);

	// run the game upto 20 moves

	for (int i = 0; i < 100; ++i)
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

void runTests(){
	position *current_position;
	char initboard[8][8]={"........",".ppppppp","P.......",
		"........","........","........",".PPPPPPP","........"};
	current_position = createNewPosition(initboard);
	current_position->turn='b';
	displayBoard(current_position);
	printf("Its is %s's turn\n", (current_position->turn=='w')?"White":"Black");
	current_position = getBestMove(current_position, 4);
	printf("Evaluation of current position: %d\n",current_position->evaluation);
	displayBoard(current_position);
	deletePosition(current_position);
}