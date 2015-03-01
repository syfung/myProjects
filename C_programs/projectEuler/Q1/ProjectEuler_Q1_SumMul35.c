# include <stdio.h>
# include <stdlib.h>

int main () {
  int i = 1;
  long long runMul = 0;
  for (i = 1; i < 1000; i++) {
    if ((i % 3) == 0) {
      printf ("%d\n", i);
      runMul = runMul + i;
    }
    else if ((i % 5) == 0) {
      printf ("%d\n", i);
      runMul = runMul + i;
    }
  }
  
  printf ("-> %lld", runMul);
  
  return 0;
}
