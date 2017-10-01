#include "common.h"

position* getBestMove(position* initialPos, int plyDepth){
	
	// first of all find out all possible moves
	move* movelist = possibleNextMoves(initialPos);
	
	// then find what will be the position after these moves
	int i=0;
	move x=movelist[i];
	position** nodesList = malloc(50*sizeof(position));
	// TODO later replace 50 by the actual number
	// write a function to simply count no. of legal moves
	while(x.move){
		nodesList[i] = getPositionAfterMove(initialPos,x);
		i++;
		x = movelist[i];
	}
	nodesList[i] = NULL;
	
	// now evaluate all the positions ...
	position* pos;
	if(plyDepth==1){
		// direct evaluation
		for(i=0;nodesList[i]!=NULL;i++){
			pos = nodesList[i];
			pos->evaluation = evaluate(pos);
		}
	} else {
		for(i=0;nodesList[i]!=NULL;i++){
			// recurse
			position* best_eval = getBestMove(nodesList[i],
					plyDepth-1);
			nodesList[i]->evaluation = best_eval->evaluation;
		}
	}
	
	// ... and now choose the best one
	int max_eval;
	position* best_position;
	best_position = nodesList[0];
	for(i=0;nodesList[i]!=NULL;i++){
		if(max_eval<nodesList[i]->evaluation){
			max_eval = nodesList[i]->evaluation;
			best_position = nodesList[i];
		}
	}

	// ... free nodesList ... but copy bestmove first TODO

	// return best position
	return best_position;
}
