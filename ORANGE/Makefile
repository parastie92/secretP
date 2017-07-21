SRCS   = $(wildcard *.c)
OBJECT = $(SRCS:.c=.o)

all : orange
banana : $(OBJECT)
	$(CC) -g -o $@ $^

clean :
	rm *.o orange

