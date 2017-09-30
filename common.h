// common.h
// ======================


// common libraries
// ----------------------

#include <stdio.h>
#include <stdbool.h>


// prototypes for board.c
// ----------------------

// representation of a move in algebriac notation like "e2e4"
typedef union move{
	int move;
	char coordinates[4];
} move;

// state of the game, includes pointer to last position
typedef struct position {
	char board[8][8];
	// board position stored like this:
	// rnbqkbnr pppppppp ........ PPPPPPPP RNBQKBNR
	// small letters for black and capital for white
	// dots for blank space
	// board always shown with white at bottom
	char turn; // W for white and b for black
	struct position* last_pos;
} position;


// This function displays the board and prints out move info
void displayBoard(position* pos);

// determines weather given move is valid or not
bool isMoveValid(move, position*);
// determines position after move
position* getNextPosition(position*, move);
// function that returns an array of the next possible moves
move* possibleNextMoves(position*);


// prototypes for evaluate.c
// ----------------------

// evaluation function; returns position evaluation in centipawns
// +100 means white winning and -100 means black winning by 1 pawn
int evaluate(position*);

// prototypes for bestmove.c
// ----------------------

// gets best move from given position
// searches upto given ply depth
move getBestMove(position* pos, int plyDepth);
