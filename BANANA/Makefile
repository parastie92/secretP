CXX = g++
CC 	= gcc

LDFLAGS = -g
CXXFLAGS = -g -c

all : banana banana.o

banana : banana.o
	$(CC) $(LDFLAGS) -o banana banana.o

banana.o : banana.c
	$(CC) $(CXXFLAGS) -o banana.o banana.c

clean :
	rm *.o banana

