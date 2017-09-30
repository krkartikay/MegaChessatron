#include "common.h"

int main(){
	// code for testing display function
	position* new_position;
	char initboard[8][8]={"pppppppp","........","........","........","........","........","........","PPPPPPPP"};
	new_position = createNewPosition(initboard);
	displayBoard(new_position);
	deletePosition(new_position);
	return 0;
}
