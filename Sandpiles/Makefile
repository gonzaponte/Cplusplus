
CC=g++
CFLAGS=-Wall -std=c++1y

all: *.cxx
	$(CC) -c *.cxx $(CFLAGS)
	$(CC) -o topple Topple.o Sandpile.o $(CFLAGS)
	$(CC) -o double Double.o Sandpile.o $(CFLAGS)
	$(CC) -o readback ReadBack.o Sandpile.o $(CFLAGS)
	$(CC) -o finder Finder.o Sandpile.o $(CFLAGS)
	$(CC) -o print_set PrintSet.o Sandpile.o $(CFLAGS)

