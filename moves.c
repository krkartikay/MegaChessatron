#include "common.h"

#define isWhiteSymbol(x) ('A'<x&&x<'Z')
#define isBlackSymbol(x) ('a'<x&&x<'z')

position* getPositionAfterMove(position* pos, move m){
	// if(!isMoveValid(m,pos)) return NULL; 
	// isMoveValid() function was removed
	int x1=m.coordinates[0]-'a';
	int y1=8-(m.coordinates[1]-'0');
	int x2=m.coordinates[2]-'a';
	int y2=8-(m.coordinates[3]-'0');
	char moving_piece = pos->board[y1][x1];
	position* new_pos = createNewPosition(pos->board);
	new_pos->board[y1][x1] = '.';
	new_pos->board[y2][x2] = moving_piece;
	new_pos->turn = (pos->turn=='w')?'b':'w';
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
					if(pos->board[j-1][i]=='.'){
						m = newMove(i,j,i,j-1);
						movelist[l] = m; l++;
					}
					if(isValidCoordinates(i+1,j-1) && isBlackSymbol(pos->board[j-1][i+1])){
						m = newMove(i,j,i+1,j-1);
						movelist[l] = m; l++;
					}
					if(isValidCoordinates(i-1,j-1) && isBlackSymbol(pos->board[j-1][i-1])){
						m = newMove(i,j,i-1,j-1);
						movelist[l] = m; l++;
					}
					break;
				case 'p':
					if(pos->turn=='w') break;
					if(pos->board[j+1][i]=='.'){
						m = newMove(i,j,i,j+1);
						movelist[l] = m; l++;
					}
					if(isValidCoordinates(i+1,j+1) && isWhiteSymbol(pos->board[j+1][i+1])){
						m = newMove(i,j,i+1,j+1);
						movelist[l] = m; l++;
					}
					if(isValidCoordinates(i-1,j+1) && isWhiteSymbol(pos->board[j+1][i-1])){
						m = newMove(i,j,i-1,j+1);
						movelist[l] = m; l++;
					}
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

bool isValidCoordinates(int i, int j){
	if(i<0)
		return false;
	if(j<0)
		return false;
	if(i>BOARD_SIZE-1)
		return false;
	if(j>BOARD_SIZE-1)
		return false;
	return true;
}