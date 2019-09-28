CC=g++
FLAGS=-Wall -O3
LIBS=
BIN=tentomon

all:
	-@mkdir obj
	$(CC) $(FLAGS) -c src/main.cpp -o obj/main.o
	$(CC) obj/main.o -o $(BIN) $(LIBS)
	strip $(BIN)
