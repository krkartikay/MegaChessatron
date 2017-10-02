#include "common.h"

bool isMoveValid(move m, position* pos){
	int x1=m.coordinates[0]-'a';
	int y1=8-(m.coordinates[1]-'0');
	int x2=m.coordinates[2]-'a';
	int y2=8-(m.coordinates[3]-'0');
	char moving_piece = pos->board[y1][x1];
	char landing_square = pos->board[y2][x2];
	if(moving_piece>'a'&&moving_piece<'z'&&pos->turn=='w'){
		// its a black piece and turn is white
		return false;
	}
	if(moving_piece>'A'&&moving_piece<'Z'&&pos->turn=='b'){
		// its a white piece and turn is black
		return false;
	}
	switch(moving_piece){
		case '.':
			// you can't move empty piece
			return false;
		case 'P':
			// white pawn can move only one place forward
			// TODO write code for pawn captures
			return (x1==x2)&&((y1-y2)==1);
		case 'p':
			// black pawn can move only one place backward
			// TODO write code for pawn captures
			return (x1==x2)&&((y2-y1)==1);
	}
	return false;
}

position* getPositionAfterMove(position* pos, move m){
	if(!isMoveValid(m,pos)) return NULL;
	int x1=m.coordinates[0]-'a';
	int y1=8-(m.coordinates[1]-'0');
	int x2=m.coordinates[2]-'a';
	int y2=8-(m.coordinates[3]-'0');
	char moving_piece = pos->board[y1][x1];
	position* new_pos = createNewPosition(pos->board);
	new_pos->board[y1][x1] = '.';
	new_pos->board[y2][x2] = moving_piece;
	new_pos->currentMove = m;
	return new_pos;
}

move* possibleNextMoves(position* pos){
	// i am assuming here that there can be max. 50 moves
	// possible for each position TODO fixit later
	move* movelist = malloc(50*sizeof(move));
	
	char piece;
	move m;
	int l = 0;
	for(int j=0; j<BOARD_SIZE; j++){
		for(int i=0; i<BOARD_SIZE; i++){
			piece = pos->board[j][i];
			switch(piece){
				case '.':
					// no move possible
					break;
				case 'P':
					if(pos->turn=='b') break;
					m = newMove(i,j,i,j-1);
					movelist[l] = m;
					// TODO write code for pawn captures
					l++;
					break;
				case 'p':
					if(pos->turn=='w') break;
					m = newMove(i,j,i,j+1);
					// TODO write code for pawn captures
					movelist[l] = m;
					l++;
					break;
			}
		}
	}
	m.move = 0;
	movelist[l] = m;

	return movelist;
	// must end possible moves with null move
}

move newMove(int x1, int y1, int x2, int y2){
	move m;
	m.coordinates[0] = 'a'+x1;
	m.coordinates[1] = (8-y1)+'0';
	m.coordinates[2] = 'a'+x2;
	m.coordinates[3] = (8-y2)+'0';
	return m;
}
