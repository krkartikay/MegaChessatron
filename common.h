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

// common.h
// ======================


// ----------------------
// common libraries
// ----------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define BOARD_SIZE 8
#define MAXMOVES 100

// ----------------------
// prototypes for board.c
// ----------------------

#define isWhiteSymbol(x) ('A'<x&&x<'Z')
#define isBlackSymbol(x) ('a'<x&&x<'z')

// representation of a move in algebriac notation like "e2e4"
typedef union move{
	int move;
	char coordinates[4];
} move;

// state of the game, includes pointer to last position
typedef struct position {
	char board[BOARD_SIZE][BOARD_SIZE];
	// board position stored like this:
	// rnbqkbnr pppppppp ........ PPPPPPPP RNBQKBNR
	// small letters for black and capital for white
	// dots for blank space
	// board always shown with white at bottom
	char turn; // w for white and b for black
	int evaluation;
	move currentMove;
	unsigned short int moveno;
} position;

// determine weather game has ended or not
bool isGameRunning(position* pos);
// if the game has ended; who won?
int whoWon(position* pos);

// first fxn creates new position struct and initialises it
// second fxn used to delete it
position* createNewPosition(char a[BOARD_SIZE][BOARD_SIZE]);
void deletePosition(position* pos);

// This function displays the board and prints out move info
void displayBoard(position* pos);
void log_board(FILE*,position*);
// ----------------------
// prototypes for loops.c
// ----------------------
int expandnode(position** nodesList, move* movelist, position* initialPos);
position* findminormax(position* initialPos, position** nodesList);
void deleteAllNodes(position** nodesList);
position* evaluation_at_end(position* initialPos);

// ----------------------
// prototypes for moves.c
// ----------------------

// creates new move object
move newMove(int x1, int y1, int x2, int y2);
// determines weather given coordinates are valid or not
bool isValidCoordinates(int i, int j);
// determines position after move
position* getPositionAfterMove(position*, move);
// function that returns an array of the next possible moves
move* possibleNextMoves(position*);

move moveplayed(position* pos);

// ----------------------
// prototypes for evaluate.c
// ----------------------

// evaluation function; returns position evaluation in centipawns
// +100 means white winning and -100 means black winning by 1 pawn
int evaluate(position*);


// ----------------------
// prototypes for bestmove.c
// ----------------------

// gets best move from given position
// searches upto given ply depth
position* getBestMove(position* pos, int plyDepth);
position* getBestMove_threaded(position* initialPos, int plyDepth);

// for testing -- in testing.c
// runs in place of main if building
// with command make testdebug
void runTests();