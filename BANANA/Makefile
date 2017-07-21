SRCS   = $(wildcard *.c)
OBJECT = $(SRCS:.c=.o)

all : banana
banana : $(OBJECT)
	$(CC) -o $@ $^

clean :
	rm *.o banana

