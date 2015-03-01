# include <stdio.h>
# include <stdlib.h>

int main (/*int argc, char **argv*/) {
  int num1, num2, denum1, denum2, ans, deans;
  printf ("Enter two fractions to add seperated with + sign:");
  scanf ("%d/%d+%d/%d", &num1, &denum1, &num2, &denum2);
  ans = num1 * denum2 + num2 * denum1;
  deans = denum1 * denum2;
  printf ("The answer is %d/%d\n", ans, deans);
  return 0;
}
