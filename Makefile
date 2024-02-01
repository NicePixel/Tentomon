CC=g++
FLAGS=-Wall -O3

all:
	-@mkdir obj
	$(CC) $(FLAGS) -c src/main.cpp -o obj/main.o
	$(CC) obj/main.o -o tentomon
	strip $(BIN)
