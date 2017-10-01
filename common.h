// common.h
// ======================


// ----------------------
// common libraries
// ----------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 8

// ----------------------
// prototypes for board.c
// ----------------------

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
	//struct position* lastPos;
	//no longer required
	int evaluation;
	move currentMove;
} position;

// first fxn creates new position struct and initialises it
// second fxn used to delete it
position* createNewPosition(char a[BOARD_SIZE][BOARD_SIZE]);
void deletePosition(position* pos);

// This function displays the board and prints out move info
void displayBoard(position* pos);

// determines weather given move is valid or not
bool isMoveValid(move, position*);
// determines position after move
position* getPositionAfterMove(position*, move);
// function that returns an array of the next possible moves
move* possibleNextMoves(position*);

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
