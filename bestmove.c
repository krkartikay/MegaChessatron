#include "common.h"

position* getBestMove(position* initialPos, int plyDepth){
	if(!isGameRunning(initialPos)){
		int i = 0;
		switch(whoWon(initialPos)){
			case 1:
				i = 1000000;
			case -1:
				i = -1000000;
			case 0:
				i = 0;
		}
		position* ret = createNewPosition(initialPos->board);
		*ret = *initialPos;
		ret->evaluation = i;
		return ret;
	}
	
	// first of all find out all possible moves
	move* movelist = possibleNextMoves(initialPos);
	
	// then find what will be the position after these moves
	int i=0;
	move x=movelist[i];
	if(!movelist[0].move){
		// NO moves possible -- stalemate -- draw
		position* ret = createNewPosition(initialPos->board);
		*ret = *initialPos;
		ret->evaluation = 0;
		return ret;
	}
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
			deletePosition(best_eval);
		}
	}
	
	// ... and now choose the best one ACCORDING TO THE TURN
	position* best_position = nodesList[0];
	if(initialPos->turn=='w'){
		int max_eval = nodesList[0]->evaluation; // white should choose the position with max_eval
		for(i=0;nodesList[i]!=NULL;i++){
			if(max_eval<nodesList[i]->evaluation){
				max_eval = nodesList[i]->evaluation;
				best_position = nodesList[i];
			}
		}
	} else {
		int min_eval = nodesList[0]->evaluation; // black should go for min_eval
		for(i=0;nodesList[i]!=NULL;i++){
			if(min_eval>nodesList[i]->evaluation){
				min_eval = nodesList[i]->evaluation;
				best_position = nodesList[i];
			}
		}
	}

	// ... free nodesList ... but copy bestmove first
	position* ret = createNewPosition(best_position->board);
	*ret = *best_position;
	for(i=0;nodesList[i]!=NULL;i++){
		deletePosition(nodesList[i]);
	}
	free(nodesList);
	free(movelist);

	// return best position
	return ret;
}
