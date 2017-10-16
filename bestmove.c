// ============================
//
//    PROJECT MEGACHESSATRON
//
// ============================

/*
MIT License

Copyright (c) 2017 Team Cos-Inifinity NITH

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "common.h"

typedef struct thd_args
{
	int threadno;
	position* initialPos;
	int plyDepth;
} thd_args;

void* singleThread(void* args){
	thd_args* a = (thd_args*) args;
	position* p = a->initialPos;
	int d = a->plyDepth;
	position* z = getBestMove(p,d);
	#ifdef DEBUG
	printf("called getBestMove(%p,%d)\n",p,d);
	#endif
	pthread_exit(z);
}

position* getBestMove_threaded(position* initialPos, int plyDepth){
	// this fxn must be run at top level
	// i.e. initialPos is not ended and plydepth>1
	move* movelist = possibleNextMoves(initialPos);
	int i=0;
	move x=movelist[i];
	position** nodesList = malloc(MAXMOVES*sizeof(position));
	int noMoves = expandnode(nodesList,movelist,initialPos);
	// CREATE THREADS AND RECURSE
	// MAIN CODE BEGINS HERE
	pthread_t *threads = malloc(noMoves*sizeof(pthread_t));
	thd_args* args = malloc(noMoves*sizeof(thd_args));
	position** returnList = malloc(noMoves*sizeof(position*));
	for (int i = 0; i < noMoves; ++i)
	{
		args[i].initialPos = nodesList[i];
		args[i].plyDepth = plyDepth;
		args[i].threadno = i;
		#ifdef DEBUG
		printf("Calling Singlethread on args[%d] with %p \n", i, initialPos);
		#endif
		if(pthread_create(threads+i,NULL,singleThread,&args[i])){
			printf("Error in creating thread\n");
		}
	}
	for (int i = 0; i < noMoves; ++i)
	{
		pthread_join(threads[i],(void**)&returnList[i]);
		position* best_eval = returnList[i];
		nodesList[i]->evaluation = best_eval->evaluation;
		deletePosition(best_eval);
	}
	// MAIN CODE ENDS HERE
	// CHOOSE BESTMOVE AND RETURN
	position* best_position = findminormax(initialPos, nodesList);
	position* ret = createNewPosition(best_position->board);
	*ret = *best_position;
	deleteAllNodes(nodesList);
	free(nodesList);
	free(movelist);
	return ret;
}

position* getBestMove(position* initialPos, int plyDepth){
	if(!isGameRunning(initialPos)){
		return evaluation_at_end(initialPos);
	}
	
	// first of all find out all possible moves
	move* movelist = possibleNextMoves(initialPos);
	
	// then find what will be the position after these moves

	position** nodesList = malloc(MAXMOVES*sizeof(position));
	// TODO later replace 50 by the actual number
	// write a function to simply count no. of legal moves
	expandnode(nodesList,movelist,initialPos);
	
	// now evaluate all the positions ...
	int i;
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
	position* best_position = findminormax(initialPos, nodesList);

	// ... free nodesList ... but copy bestmove first
	position* ret = createNewPosition(best_position->board);
	*ret = *best_position;
	
	deleteAllNodes(nodesList);
	free(nodesList);
	free(movelist);

	// return best position

	#ifdef DEBUG
		if(plyDepth==4)
			;//printf("Returning position %p with eval = %d \n", ret, ret->evaluation);
	#endif

	return ret;
}
