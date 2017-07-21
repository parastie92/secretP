SRCS   = $(wildcard *.c)
OBJECT = $(SRCS:.c=.o)

all : orange
banana : $(OBJECT)
	$(CC) -o $@ $^

clean :
	rm *.o orange

