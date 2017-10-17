// ============================
//
//    PROJECT MEGACHESSATRON
//
// ============================


/*
MIT License

Copyright (c) 2017 Team Cos-Inifinity NITH

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
 * 	a6 b6 c6 d6 e6 f6 g6 h6
 * 	a5 b5 c5 d5 e5 f5 g5 h5
 * 	a4 b4 c4 d4 e4 f4 g4 h4
 * 	a3 b3 c3 d3 e3 f3 g3 h3
 * 	a2 b2 c2 d2 e2 f2 g2 h2
 * 	a1 b1 c1 d1 e1 f1 g1 h1
 *
 * so board[j][i] actually in chess corresponds to coordinates
 * ('a'+i,'0'+8-j).
 *
 */

position* createNewPosition(char a[BOARD_SIZE][BOARD_SIZE]){
	position* newPos = malloc(sizeof(position));
	//newPos->lastPos=NULL;
	newPos->turn = 'w';
	newPos->evaluation = 0;
	newPos->currentMove.move = 0;
	newPos->moveno=1;
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
	char line[]="+---+---+---+---+---+---+---+---+";
	char x = ' ';
	for(int j=0; j<BOARD_SIZE; j++){
		printf("%s\n",line);
		for(int i=0; i<BOARD_SIZE; i++){
			// uncomment these lines to get black and white squares
			// i dont like it so i commented it out
			/*if((i+j)%2 == 1)
				x = '.';
			else 
				x = ' ';*/
			if(pos->board[j][i]!='.')
				printf("|%c%c%c",x,pos->board[j][i],x);
			else
				printf("|%c%c%c",x,x,x);
		}
		printf("|\n");
	}
	printf("%s\n",line);
}

bool isGameRunning(position* pos){
	// true if running
	// false if ended
	bool isThereAWhiteKing = false;
	bool isThereABlackKing = false;
	bool areThereValidMoves = false;
	for(int j=0; j<BOARD_SIZE; j++){
		for(int i=0; i<BOARD_SIZE; i++){
			switch(pos->board[j][i]){
				case 'k':
					isThereABlackKing = true;
					break;
				case 'K':
					isThereAWhiteKing = true;
					break;
			}
		}
	}
	move* movelist = possibleNextMoves(pos);
	if(movelist[0].move){
		areThereValidMoves = true;
		free(movelist);
	}
	return isThereAWhiteKing && isThereABlackKing && areThereValidMoves;
}

int whoWon(position* pos){
	// returns -1 for black won; +1 for white won; 0 for draw;
	// returns 2 for game still running.
	bool isThereAWhiteKing = false;
	bool isThereABlackKing = false;
	bool areThereValidMoves = false;
	for(int j=0; j<BOARD_SIZE; j++){
		for(int i=0; i<BOARD_SIZE; i++){
			switch(pos->board[j][i]){
				case 'k':
					isThereABlackKing = true;
					break;
				case 'K':
					isThereAWhiteKing = true;
					break;
			}
		}
	}
	move* movelist = possibleNextMoves(pos);
	if(movelist[0].move)
		areThereValidMoves = true;
	free(movelist);
	if(!isThereABlackKing) return 1;
	if(!isThereAWhiteKing) return -1;
	if(!areThereValidMoves) return 0;
	return 2;
}