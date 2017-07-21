CXX = g++
CC 	= gcc

LDFLAGS = -g
CCFLAGS = -g -c

all : orange orange.o

orange : orange.o
	$(CC) $(LDFLAGS) -o orange orange.o

orange.o : orange.c
	$(CC) $(CCFLAGS) -o orange.o orange.c

clean :
	rm *.o orange

