CC=c99
CFLAGS=-I.

LIBS=-lpthread

DEPS = red_blue.h barrier.h
OBJ = red_blue.o barrier.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

red_blue: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o red_blue

