#include "common.h"

int main(int argc, char const *argv[]){
	#ifdef DEBUG
	runTests();
	return 0;
	#endif

	// Setup intial position
	position *current_position;
	char initboard[8][8]={"rnbqkbnr","pppppppp","........",
		"........","........","........","PPPPPPPP","RNBQKBNR"};
	current_position = createNewPosition(initboard);
	
	//displayBoard(current_position);

	int p = 1;
	// run the till someone doesnt win
	while(isGameRunning(current_position))
	{
		// print whose turn it is
		//printf("Its is %s's turn\n", (current_position->turn=='w')?"White":"Black");
		int depth = 4;
		if (argc == 2)
		{
			depth = atoi(argv[1]);
		}
		current_position = getBestMove(current_position, depth);
		char* c = moveplayed(current_position).coordinates;
		//displayBoard(current_position);
		//printf("Evaluation of current position: %d\n",current_position->evaluation);
		//printf("Move played: %s \n",moveplayed(current_position).coordinates);
		if(p%2 == 1){
			// white's turn
			printf("%2d. %s\t",(p+1)/2, c);
		} else {
			// black's turn
			printf("%s\n", c);
		}
		fflush(stdout);
		p++;
	}
	
	deletePosition(current_position);
	return 0;
}

// TODO KING SAFETY
// TODO tempo
// TODO pawn structure
// TODO UCI/xBoard protocol
// TODO licence
// TODO 3-fold repetition
// TODO 50 move rule
// TODO PGN mode