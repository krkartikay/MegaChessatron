# MegaChessatron
Megachessatron being built by students of CSE NITH 1st year

## Project Structure

This is a chess engine being written in C. The code uses the MINIMAX
algorithm to evaluate the best move in a given position. The state of
the game is stored in structs in C.

The various files are:

  * common.h -- contains all definitions (game state, functions etc).
                Included by all files.
  * board.c -- contains code for getting various info about board,
                finding possible moves, prining board, etc etc.
  * evaluate.c -- contains evaluation function which calculates
                chances of winning/losing
  * main.c -- contains the user interface, input/output etc.
  * bestmove.c -- contains commands to find best move according
                to minimax algorithm.
  * Makefile -- config file for automatic building/compiling.
