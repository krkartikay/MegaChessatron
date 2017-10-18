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

int main(int argc, char const *argv[]){
	
	#ifdef TESTING
	runTests();
	return 0;
	#endif

	#ifdef XBOARD
	int rn = rand();
	char filename[100];
	#ifdef LOGGING
	sprintf(filename,"logfile%d.txt",rn);
	FILE* logfile = fopen(filename,"w");
	#endif

	// Setup intial position
	position *current_position;
	char initboard[8][8]={"rnbqkbnr","pppppppp","........",
		"........","........","........","PPPPPPPP","RNBQKBNR"};
	setbuf(stdout, NULL);
	#ifdef LOGGING
	setbuf(logfile, NULL);
	#endif
	//displayBoard(current_position);

	int p = 1;
	int depth = 4;
	char inp[100];
	int inputs_to_ignore = 0;

	// run the till someone doesnt win or 100 moves played
	while(1)
	{
		scanf("%s",inp);
		#ifdef LOGGING
		fprintf(logfile, "<<< %s\n", inp);
		#endif
		if(inputs_to_ignore>0){
			inputs_to_ignore--;
		} else if(strcmp(inp,"xboard")==0 
			   || strcmp(inp,"accepted")==0
			   || strcmp(inp,"rejected")==0
			   || strcmp(inp,"force")==0
			   || strcmp(inp,"white")==0
			   || strcmp(inp,"black")==0
			   || strcmp(inp,"draw")==0
			   || strcmp(inp,"hint")==0
			   || strcmp(inp,"bk")==0
			   || strcmp(inp,"undo")==0
			   || strcmp(inp,"remove")==0
			   || strcmp(inp,"hard")==0
			   || strcmp(inp,"easy")==0
			   || strcmp(inp,"post")==0
			   || strcmp(inp,"nopost")==0
			   || strcmp(inp,"analyze")==0
			   || strcmp(inp,"computer")==0
			   || strcmp(inp,"pause")==0
			   || strcmp(inp,"resume")==0
			   ){
			// go ahead
			inputs_to_ignore = 0;
		} else if(strcmp(inp,"protover")==0
			   || strcmp(inp,"variant")==0
			   || strcmp(inp,"st")==0
			   || strcmp(inp,"sd")==0
			   || strcmp(inp,"nps")==0
			   || strcmp(inp,"time")==0
			   || strcmp(inp,"otim")==0
			   || strcmp(inp,"usermove")==0
			   || strcmp(inp,"ping")==0
			   || strcmp(inp,"setboard")==0
			   || strcmp(inp,"edit")==0
			   || strcmp(inp,"name")==0
			   || strcmp(inp,"ics")==0
			   || strcmp(inp,"memory")==0
			   || strcmp(inp,"cores")==0
			   || strcmp(inp,"lift")==0
			   || strcmp(inp,"put")==0
			   || strcmp(inp,"hover")==0
			   || strcmp(inp,"option")==0
			   || strcmp(inp,"exclude")==0
			   || strcmp(inp,"include")==0
			   ){
			// ignore next input
			inputs_to_ignore = 1;
		} else if(strcmp(inp,"rating")==0
			   || strcmp(inp,"egtpath")==0
			   || strcmp(inp,"setscore")==0){
			inputs_to_ignore = 2;
		} else if(strcmp(inp,"level")==0
			   || strcmp(inp,"result")==0) {
			inputs_to_ignore = 3;
		} else if(strcmp(inp,"new")==0) {
			current_position = createNewPosition(initboard);
		} else if(strcmp(inp,"random")==0) {
			// set random mode
			// CODE TODO
		} else if(strcmp(inp,"quit")==0) {
			return 0;
		} else if(strcmp(inp,"go")==0) {
			current_position = getBestMove_threaded(current_position, depth);
			char* c = current_position->currentMove.coordinates;
			printf("move %c%c%c%c\n", c[0],c[1],c[2],c[3]);
			#ifdef LOGGING
			fprintf(logfile, ">>> move %c%c%c%c\n", c[0],c[1],c[2],c[3]);
			#endif
		} else {
			move m;
			m.coordinates[0] = inp[0];
			m.coordinates[1] = inp[1];
			m.coordinates[2] = inp[2];
			m.coordinates[3] = inp[3];
			position* new_pos = getPositionAfterMove(current_position,m);
			deletePosition(current_position);
			current_position = new_pos;
			#ifdef LOGGING
			log_board(logfile, current_position);
			#endif
			// run
			current_position = getBestMove_threaded(current_position, depth);
			char* c = current_position->currentMove.coordinates;
			printf("move %c%c%c%c\n", c[0],c[1],c[2],c[3]);
			#ifdef LOGGING
			fprintf(logfile, ">>> move %c%c%c%c\n", c[0],c[1],c[2],c[3]);
			#endif
			p++;
		}
		#ifdef LOGGING
		log_board(logfile, current_position);
		#endif
	}
	
	deletePosition(current_position);
	return 0;
	#endif

	#ifndef XBOARD
	// TEXT MODE
	//what level you selected
	if(argv[1] != '\0'){
		printf("LEVEL = %s \n",argv[1]);
	}
	else{
		puts("LEVEL = 4 (default)\n");
	}

	// Setup intial position
	position *current_position;
	char initboard[8][8]={"rnbqkbnr","pppppppp","........",
		"........","........","........","PPPPPPPP","RNBQKBNR"};
	current_position = createNewPosition(initboard);
	
	displayBoard(current_position);

	int p = 1;
	// run the till someone doesnt win or 100 moves played
	while(isGameRunning(current_position) && p<200)
	{
		// print whose turn it is
		//printf("Its is %s's turn\n", (current_position->turn=='w')?"White":"Black");
		int depth = 4;
		if (argc == 2)
		{
			depth = atoi(argv[1]);
		}
		current_position = getBestMove_threaded(current_position, depth);
		char* c = moveplayed(current_position).coordinates;
		
		displayBoard(current_position);
		
		if(p%2 == 1){
			// white's turn
			printf("%2d. %s ... \t\t (%d) \n\n",(p+1)/2, c, current_position->evaluation);
		} else {
			// black's turn
			printf("%2d.    ... %s\t\t (%d)\n\n",p/2, c,  current_position->evaluation);
		}
		
		fflush(stdout);
		p++;
	}
	
	deletePosition(current_position);
	return 0;
	#endif
}

// TODO KING SAFETY
// TODO tempo
// TODO pawn structure
// TODO passed pawns
// TODO UCI/xBoard protocol
// TODO 3-fold repetition
// TODO 50 move rule
// TODO PGN mode
