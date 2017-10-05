#include "common.h"

int evaluate(position* pos){
	// This function always returns who is winning
	// regardless of whose move it is. I.e. the return
	// value is +ve means that white is winning even if
	// it is black's move.
	
	int evaluation;

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
			}
		}
	}

	return evaluation;
}
