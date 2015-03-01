FLAG = -Wall -W -O -g

test: StackStructure.o stackFunction.o
	gcc ${FLAG} -o $@ $^

%.o: %.c stackFunction.h
	gcc ${FLAG} -c $<

clearBuild:
	rm *.o

clear:
	rm test *.o

