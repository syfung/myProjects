CFLAGS = -w -Wall -O -g

all: testMain

testMain: testMain.c myStack.o
	gcc $(CFLAGS) -o test $^

myStack.o: myStack.c myStack.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o test
