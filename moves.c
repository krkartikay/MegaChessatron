#include "common.h"

bool isMoveValid(move m, position* pos){
	// TODO implement this function
	return false;
}

position* getPositionAfterMove(position* pos, move m){
	// TODO implement this function
	return pos;
}

move* possibleNextMoves(position* pos){
	// TODO implement this function
	// i am assuming here that there can be max. 50 moves
	// possible for each position
	move* movelist = (move*) malloc(50*sizeof(move));
	// do some calculation and then
	return movelist;
	// must end possible moves with NULL
}
