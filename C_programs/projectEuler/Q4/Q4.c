# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int is_palindromic (int num);

int main () {
  int num, i, j;

  for (i = 999; i > 900; i--) {
    for (j = 999; j > 900; j--) {
      num = i * j;
      if (is_palindromic (num)) {
	printf ("%d\n", num);
	exit (0);
      }
    }
  }  
  return 0;
}


int is_palindromic (int num) {
  printf ("%d\n", num);
  int len, palin;
  char str[21], temp;
  sprintf(str, "%d", num);
  printf ("s%s\n", str);
  len = strlen (str);
  
  printf ("%d\n", len);
  int i, last;
  for (i = 0; i < len / 2; i++) {
    last = len - i - 1;
    temp = str[last];
    printf ("c%c, %c\n", temp, str[last]);
    str[last] = str[i];
    
    printf ("s%s\n", str);
    str[i] = temp;
    printf ("s%s\n", str);
  }
  palin = strtol (str, NULL, 10);
  printf ("%d\n", palin);
  if (palin == num) {
    return 1;
  }
  return 0;
}
