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

int pieceCountValue(char piece){
	// returns piece value, +ve if white, -ve if black
	switch(piece){
		case 'P':
			return +100;
		case 'p':
			return -100;
		case 'R':
			return +500;
		case 'r':
			return -500;
		case 'N':
			return +300;
		case 'n':
			return -300;
		case 'B':
			return +350;
		case 'b':
			return -350;
		case 'Q':
			return +900;
		case 'q':
			return -900;
		case 'K':
			return +100000;
		case 'k':
			return -100000;
		case '.':
			return 0;
	}
}

int evaluate(position* pos){
	// This function always returns who is winning
	// regardless of whose move it is. I.e. the return
	// value is +ve means that white is winning even if
	// it is black's move.
	
	int evaluation = 0;

	if(!isGameRunning(pos)){
		switch(whoWon(pos)){
			case 1:
				return 1000000;
			case -1:
				return -1000000;
			case 0:
				return 0;
		}
	}

	// count pieces ... black and white
	char piece;
	for(int j=0; j<BOARD_SIZE; j++){
		for(int i=0; i<BOARD_SIZE; i++){
			piece = pos->board[j][i];
			evaluation += pieceCountValue(piece);
		}
	}
	
	return evaluation;
}