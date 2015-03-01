# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
  int number;
  printf ("Please enter a number:");
  scanf ("%d", &number);
  while ((number % 10) != 0){
    printf ("%d", (number % 10));
    number = number / 10;
  }
  printf ("\n");
	return 0;
}
