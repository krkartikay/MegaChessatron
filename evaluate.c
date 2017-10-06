#include "common.h"

int evaluate(position* pos){
	// This function always returns who is winning
	// regardless of whose move it is. I.e. the return
	// value is +ve means that white is winning even if
	// it is black's move.
	
	int evaluation = 0;

	// count pawns ... black and white
	char piece;
	for(int j=0; j<BOARD_SIZE; j++){
		for(int i=0; i<BOARD_SIZE; i++){
			piece = pos->board[j][i];
			switch(piece){
				case 'P':
					evaluation += 100;
					break;
				case 'p':
					evaluation -= 100;
					break;
				case 'R':
					evaluation += 500;
					break;
				case 'r':
					evaluation -= 500;
					break;
				case 'N':
					evaluation += 300;
					break;
				case 'n':
					evaluation -= 300;
					break;
				case 'B':
					evaluation += 350;
					break;
				case 'b':
					evaluation -= 350;
					break;
				case 'Q':
					evaluation += 1000;
					break;
				case 'q':
					evaluation -= 1000;
					break;
				case 'K':
					evaluation += 1000000;
					break;
				case 'k':
					evaluation -= 1000000;
					break;
			}
		}
	}
	return evaluation;
}
