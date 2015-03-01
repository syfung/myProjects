#include <stdio.h>
#include <stdlib.h>

int is_prime (long int prime) {
  if (prime == 1) {
    return 0;
  }
  long int i;
  for (i = 2; i < prime; i++) {
    if ((prime % i) == 0) {
      return 0;
    }
  }
  return 1;
}


int main () {
  int prime_num;
  long int num = 0;
  for (prime_num = 0; prime_num < 10001;) {
    num++;
    if (is_prime (num)) {
      
      //printf ("%ld\n", num);
      prime_num++;
    }
  }

  printf ("%ld\n", num);

    return 0;
}
