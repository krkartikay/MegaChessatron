// common.h
// ======================


// ----------------------
// common libraries
// ----------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 8
#define MAXMOVES 100

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
	int evaluation;
	move currentMove;
} position;


#define isWhiteSymbol(x) ('A'<x&&x<'Z')
#define isBlackSymbol(x) ('a'<x&&x<'z')

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

// for testing -- in testing.c
// runs in place of main if building
// with command make testdebug
void runTests();