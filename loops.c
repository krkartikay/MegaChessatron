#include "common.h"

void expandnode(position** nodesList, move* movelist, position* initialPos){
	int i=0;
	move x=movelist[i];
	while(x.move){
		nodesList[i] = getPositionAfterMove(initialPos,x);
		i++;
		x = movelist[i];
	}
	nodesList[i] = NULL;
}

position* findminormax(position* initialPos, position** nodesList){
	int i;
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
	return best_position;
}

void deleteAllNodes(position** nodesList){
	for(int i=0;nodesList[i]!=NULL;i++){
		deletePosition(nodesList[i]);
	}
}

position* evaluation_at_end(position* initialPos){
	int i = 0;
	switch(whoWon(initialPos)){
		case 1:
			i = 1000000;
			break;
		case -1:
			i = -1000000;
			break;
		case 0:
			i = 0;
			break;
	}
	position* ret = createNewPosition(initialPos->board);
	*ret = *initialPos;
	ret->evaluation = i;
	return ret;
}