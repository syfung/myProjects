# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int main () {
  long int num = 600851475143;
  //int num = 13195;
  long int i, prime, ans = 0;

  printf (".");
  for (i = 1; i < num; i++ ) {
    if (num % i == 0) {
      num = num / i;
    }
  }
  printf ("-> %ld\n", i);
  return 0;
}
