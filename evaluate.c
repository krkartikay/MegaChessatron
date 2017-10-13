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

char a[] = "rnbqkbnr";
char b[] = "RNBQKBNR";

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
				/*case 'K':
					evaluation += 1000000;
					break;
				case 'k':
					evaluation -= 1000000;
					break;*/
			}
		}
	}
	for(int j=BOARD_SIZE/2-1; j<BOARD_SIZE/2+1; j++){
		for(int i=BOARD_SIZE/2-1; i<BOARD_SIZE/2+1; i++){
			piece = pos->board[j][i];
			if(isWhiteSymbol(piece))
				evaluation += 30;
			else if (isBlackSymbol(piece))
				evaluation -= 30;
		}
	}
	for(int j=BOARD_SIZE/2-2; j<BOARD_SIZE/2+2; j++){
		for(int i=BOARD_SIZE/2-2; i<BOARD_SIZE/2+2; i++){
			piece = pos->board[j][i];
			if(isWhiteSymbol(piece))
				evaluation += 10;
			else if (isBlackSymbol(piece))
				evaluation -= 10;
		}
	}
	int j;
	j = 0;
	for (int i = 0; i < 8; ++i)
	{
		if (pos->board[j][i] == a[i])
		{
			evaluation += 3;
		}
	}
	j = 1;
	for (int i = 3; i < 5; ++i)
	{
		if (pos->board[j][i] == 'p')
		{
			evaluation += 2;
		}
	}
	j = 7;
	for (int i = 0; i < 8; ++i)
	{
		if (pos->board[j][i] == b[i])
		{
			evaluation -= 3;
		}
	}
	j = 6;
	for (int i = 3; i < 5; ++i)
	{
		if (pos->board[j][i] == 'P')
		{
			evaluation -= 2;
		}
	}
	return evaluation;
}