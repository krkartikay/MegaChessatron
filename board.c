#include "common.h"

/*
 * Note about representation of board in memory
 * --------------------------------------------
 *
 * The variable position->board is a 2D array and hence starts like
 * board [0][0], [0][1], [0][2], ....
 *       [1][0], [1][1], [1][2], ....
 *       ....
 *
 * but the chess board has coordinates like
 *
 * 	a8 b8 c8 d8 e8 f8 g8 h8
 * 	a7 b7 c7 d7 e7 f7 g7 h7
 * 	.....
 *
 * so board[j][i] actually in chess corresponds to coordinates
 * ('a'+i,'0'+8-j).
 *
 */

position* createNewPosition(char a[BOARD_SIZE][BOARD_SIZE]){
	position* newPos = (position*) malloc(sizeof(position));
	newPos->last_pos=NULL;
	newPos->turn = 'W';
	for(int j=0; j<BOARD_SIZE; j++){
		for(int i=0; i<BOARD_SIZE; i++){
			newPos->board[j][i] = a[j][i];
		}
	}
	return newPos;
}

void deletePosition(position* pos){
	free(pos);
}

void displayBoard(position* pos){
	char line[]="+-+-+-+-+-+-+-+-+";
	for(int j=0; j<BOARD_SIZE; j++){
		printf("%s\n",line);
		for(int i=0; i<BOARD_SIZE; i++){
			printf("|%c",pos->board[j][i]);
		}
		printf("|\n");
	}
	printf("%s\n",line);
}
