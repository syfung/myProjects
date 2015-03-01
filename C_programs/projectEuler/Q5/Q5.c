# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int main () {
  int num, diviser, found = 0;

  for (num = 1; 1; num++) {
    for (diviser = 1; diviser <= 20; diviser++) {
      if (num % diviser != 0) {
	found = 0;
	break;
      }
      else {
	found = 1;
      }
    }
    if (found) {
      break;
    }
  }
    
  printf ("-> %d\n", num);
  return 0;
}
