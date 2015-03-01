#!/bin/bash

## This a short bash program, that find every *.c file in the directry and create a 
## file of the same name. Then compile two version, the normal version and the debug 
## version.

for file in ./*.c ; do
	path=$(basename "$file" .c);
	name="${path#*.}";
	mkdir ./$name;
	echo "Compilling c program";
	gcc -O -Wall -W -std=c99 -o ./$name/$name  $file;
	echo "Compilling c debug program"
	gcc -O -Wall -W -g -std=c99 -o ./$name/$name.gdb  $file;
done 
