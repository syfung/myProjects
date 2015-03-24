#include <stdio.h>
#include <stdlib.h>

#define MAX 2000000

int is_prime (long long int num);

int main (void) {
  long long int sum = 0, num;
  for (num = 2; num < MAX; num++) {
    if (is_prime(num)) {
      printf("num: %lld\n", num);
      sum = sum + num;
    }
  }
  printf("sum: %lld\n", sum);
  return 0;
}

int is_prime (long long int n) {
  int i;
  if (n <= 3) {
        return n > 1;
    } else if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    } else {
        for ( i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return 0;
            }
        }
        return 1;
    }
}
  
