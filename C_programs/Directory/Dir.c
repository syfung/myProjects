# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include <dirent.h>

# define LINESIZE 20

int main (int argc, char **argv) {
  char *name, line[LINESIZE], *lp; int len;
  DIR *dp; struct dirent *entry; FILE *fp;

  name = argv[1];
  len = strlen(name);
  dp = opendir(".");

  while( (entry = readdir(dp)) != NULL )
    printf ("%s\n", entry->d_name);
  closedir(dp);

  FILE * openFile;

  if ((openFile = fopen ("./ha/ha.txt", "r")) == NULL){
    perror ("Fuck\n");
    exit (1);
  }
  char *str;
  str = malloc (LINESIZE);
  str = fgets(str ,20, openFile);
  //str [LINESIZE -1] = "\0";
  printf("%s", str);
  fclose (openFile);
  char * p;
  p = malloc(100*sizeof(char));
  printf("%ld", sizeof(p));
  return 0;
}
