# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int main (int argc, char **argv) {
  if (argc == 1){
    printf ("You have no argument\n");
  }
  else {
    printf ("Your first argument is: %s\n",argv[1]);
  }
  extern char *optarg;
  extern int optind, opterr, optopt;
  opterr = 0;
  char opt[] = {"-o:-i"};
  int a;
  while ((a = getopt(argc, argv, opt)) != -1){
    printf ("%c\n",a);
    printf ("\r%d, %d, %d, %s\n", optind, opterr, optopt, optarg);
  }
  
  //  printf("\e[1;1H\e[2J");

  
  printf ("int: Decimal: %d Octal: %o Hexdecimal: %x", (int)sizeof(int), (int)sizeof(int), (int)sizeof(int));
  fflush(stdout);
  sleep (1);
  printf ("\rchar: Decimal: %d Octal: %o Hexdecimal: %x\n", (int)sizeof(char), (int)sizeof(char), (int)sizeof(char));
  //  fflush(stdout);
  printf ("size_t:\nDecimal: %d\nOctal: %o\nHexdecimal: %x\n", (int)sizeof(size_t), (int)sizeof(size_t), (int)sizeof(size_t));
  int i;
  
  for (i = 0; i < 10; i++){ 
    printf ("\rHello%d",i);
    fflush(stdout);
    sleep (1);
    
  }
  return 0;
}
