FLAG = -Wall -w -O -g

all: simpletest mytest

tests: simpletest mytest
	./simpletest
	./mytest

simpletest: simpletest.o smalloc.o testhelpers.o
	gcc ${FLAG} -o $@ $^

mytest: mytest.o smalloc.o testhelpers.o
	gcc ${FLAG} -o $@ $^

%.o : %.c smalloc.h testhelpers.h
	gcc ${FLAG} -c $<

clearBiuld:
	rm *.o 

clean: 
	rm simpletest mytest *.o
