# MegaChessatron
Megachessatron being built by students of CSE NITH 1st year.

## Project Structure

This is a chess engine being written in C. The code uses the MINIMAX
algorithm to evaluate the best move in a given position. The state of
the game is stored in structs in C.

The various files are:

  * common.h -- contains all definitions (game state, functions etc).
                Included by all files.
  * board.c -- contains code for managing structs having board position
  * moves.c -- contains code for finding possible moves etc
  * evaluate.c -- contains evaluation function which calculates
                chances of winning/losing
  * main.c -- contains the user interface, input/output etc.
  * bestmove.c -- contains commands to find best move according
                to minimax algorithm.
  * Makefile -- config file for automatic building/compiling.

## How to Compile and Run the code
This project is designed to be compiled on linux using gcc.
To compile this code, first download the code and extract it or
clone it with git (using `git clone <url>`). Then move to the directory
having the code (using `cd <path>`). Then to compile it type the
command `make`. If gcc is installed on your system and everything
works properly, the code should compile and an executable file called
`MegaChessatron` will be created in that folder (check it with `ls`).
To run it, simply type `./MegaChessatron`.

On windows you can either try to import the project into DevC++ and
set the custom Makefile using instructions given here:
https://stackoverflow.com/questions/13544684/running-a-project-in-dev-c 
or you may use either the git shell or cygwin to get a linux shell in windows.

## How to contribute to the code
In order to contribute to the code, you have to first fork this repository
on Github. Then clone the repository from your own account (install git and
run `git clone <url>`). Then create a new branch in git, make changes to the
code and commit your changes after testing them. Once a new feature has been
added or a bug has been removed, merge it with the master branch and send a
pull request to the original repository.
