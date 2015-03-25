#include <stdio.h>
#include <stdlib.h>

#ifndef NUMDIV
#define NUMDIV 5
#endif

int gen_tri_num (int num);
int num_div (int triNum);

int main (void) {
  int i, j, intr = 100;
  for (i = 1; ; i += intr) {
    printf("\nstill under\n");
    if (num_div(gen_tri_num(i)) >= NUMDIV) {
      printf("over: %d\n", gen_tri_num(i));
      intr /= 2;
      for (j = i; ; j -= intr) {
	if (num_div(gen_tri_num(j)) <= NUMDIV) {
	  printf("under: %d\n", gen_tri_num(j));
	  if (i == j) {
	    printf("ans: %d\n", gen_tri_num(j));
	    exit(0);
	  }
	  i = j;
	  break;
	}
      }
    }
  }
  return 0;
}



int gen_tri_num (int num) {
  return (num * (num + 1)) / 2;
}

int num_div (int x) {
  int limit = x;
  int numberOfDivisors = 0;
  int i;
  for (i = 1; i < limit; ++i) {
    if (x % i == 0) {
      limit = x / i;
      if (limit != i) {
	numberOfDivisors++;
      }
      numberOfDivisors++;
    }
  }

  return numberOfDivisors;
}
