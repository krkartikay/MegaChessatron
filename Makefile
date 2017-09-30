OBJS = board.o evaluate.o main.o bestmove.o
FLAGS = -O1

all: MegaChessatron

MegaChessatron: $(OBJS)
	gcc -o MegaChessatron $(FLAGS) $(OBJS)

%.o: %.cpp common.h
	gcc $(FLAGS) -c $< -o $@

clean:
	rm *.o
	rm MegaChessatron
