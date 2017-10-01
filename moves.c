#include "common.h"

bool isMoveValid(move m, position* pos){
	// TODO implement this function
	int x1=m.coordinates[0]-'a';
	int y1=8-(m.coordinates[1]-'0');
	int x2=m.coordinates[2]-'a';
	int y2=8-(m.coordinates[3]-'0');
	char moving_piece = pos->board[y1][x1];
	char landing_square = pos->board[y2][x2];
	switch(moving_piece){
		case '.':
			// you can't move empty piece
			return false;
		case 'P':
			// white pawn can move only one place forward
			return (x1==x2)&&((y1-y2)==1);
		case 'p':
			return (x1==x2)&&((y2-y1)==1);
	}
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
	move* movelist = malloc(50*sizeof(move));
	// do some calculation and then
	return movelist;
	// must end possible moves with NULL
}
