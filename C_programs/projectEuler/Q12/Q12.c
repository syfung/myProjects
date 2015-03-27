#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef NUMDIV
  #define NUMDIV 5
#endif

int gen_tri_num (int num);
int num_div (int triNum);

int main (void) {
  int i, triNum = 1;
  for (i = 0;  num_div(triNum) < NUMDIV; i++) {
    triNum = gen_tri_num(i);
  }
  printf("ans: %d", triNum);
  return 0;
}


int gen_tri_num (int num) {
  return ((num * (num + 1)) / 2);
}


int num_div (int n) {
  int counter = 1,i = 2;
  
  while (i < sqrt(n)) {

    if (n % i == 0) {
      counter++;
      if (i != n / i) {
	counter++;
      }
    }

    i++;
  }

  if ((i * i) == n) {
    counter++;
  }

  return counter;
}

  
