# include <stdio.h>
# include <stdlib.h>

int generate_fibonacci (int lastTerm, int lastLastTerm);

int main () {
  int termA = 1, termB = 1, tempTerm = 0;
  int fibonSum = 0;

  while ((tempTerm = generate_fibonacci(termA, termB)) < 4000000) {
    termA = termB;
    termB = tempTerm;
    printf ("%d\n", termB);
    if (termB % 2 == 0) {
      fibonSum += termB;
    }
  }
  
  printf ("-> %d\n", fibonSum);
  
  return 0;
}

int generate_fibonacci (int lastTerm , int lastLastTerm) {
  return lastTerm + lastLastTerm;
}
  
