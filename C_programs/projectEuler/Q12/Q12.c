#include <stdio.h>
#include <stdlib.h>

#ifndef NUMDIV
#define NUMDIV 5
#endif

long int gen_tri_num (int num);
int num_div (long int triNum);

int main (void) {
  int i, j, intr = 100;
  for (i = 1; ; i += intr) {
    printf("\nstill under\n");
    if (num_div(gen_tri_num(i)) >= NUMDIV) {
      printf("over: %ld\n", gen_tri_num(i));
      intr = (intr / 2);
      printf("working\n");
      for (j = i-intr; ; j -= intr) {
	//printf("working\n");
	if ((int)gen_tri_num(i) == (int)gen_tri_num(j)) {
	  printf("ans: %ld\n", gen_tri_num(j));
	  exit(0);
	}
	if (num_div(gen_tri_num(j)) <= NUMDIV) {
	  printf("under: %ld\n", gen_tri_num(j));
	  i = j;
	  break;
	}
      }
    }
  }
  return 0;
}



long int gen_tri_num (int num) {
  return (num * (num + 1)) / 2;
}

int num_div (long int n) {
  int counter,i;
  printf("num %ld", n);
  for(counter=0,i=1;(!(n%i) && (counter++)) || i<=(n/2);i++);
  if (n==2 || n==1) {
      return counter;
    }
  printf("div working numdiv: %d\n", counter);
  return ++counter;
}
  
