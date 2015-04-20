#include <stdio.h>
#include <stdlib.h>

#include "myStack.h"

int main() {
  int temp;
  temp = stack_init();
  printf("%d\n", temp);
  return 0;
}
