OBJS = board.o evaluate.o main.o bestmove.o moves.o
FLAGS =

all: MegaChessatron

debug: FLAGS += -O0 -g
debug: all

testdebug: FLAGS+= -O0 -g -DDEBUG
testdebug: OBJS+= testing.o
testdebug: testing.o all

optimised: FLAGS += -O3
optimised: MegaChessatron

MegaChessatron: $(OBJS)
	gcc -o MegaChessatron $(FLAGS) $(OBJS)

%.o: %.c common.h
	gcc $(FLAGS) -c $< -o $@

clean:
	rm *.o
	rm MegaChessatron
