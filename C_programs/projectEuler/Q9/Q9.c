#include <stdio.h>
#include <stdlib.h>

int sum_equal1000 (int a, int b, int c);
int is_triple (int a, int b, int c);
int answer_we_want (int a, int b, int c);

int main (void) {
  int i, j, k;
  for (i = 0; i < 1000; i++) {
    for (j = 0; j < 1000; j++) {
      for (k = 0; k < 1000; k++) {
	if (answer_we_want(i,j,k)) {
	  printf("a: %d, b: %d, c: %d\n", i, j, k);
	  printf("abc: %d\n", i * j * k);
	}
      }
    }
  }
  return 0;
}

int answer_we_want (int a, int b, int c) {
  if (sum_equal1000(a, b, c)) {
    if(is_triple(a, b, c)) {
      return 1;
    }
  }
  return 0;
}


int sum_equal1000 (int a, int b, int c) {
  return (a + b + c) == 1000;
}

int is_triple (int a, int b, int c) {
  return ((a * a + b * b) == c * c);
}
  
