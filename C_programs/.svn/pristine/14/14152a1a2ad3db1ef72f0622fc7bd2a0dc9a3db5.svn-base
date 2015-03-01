# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {

  if (argc != 3) {
    printf("Usage: removevocal <sourcefile> <destfile>");
    exit (1);
  }
  
  FILE *openFile = NULL;
  FILE *newFile = NULL;
  
  if ( NULL == (openFile = fopen(argv[1], "rb"))) {
      perror ("Cannot open source file");
      exit (1);
    }
  if ((newFile = fopen (argv[2], "wb")) == NULL) {
    perror ("Cannot write/create target file");
    exit (1);
  }

  short *headerBytes;
  headerBytes = malloc (44);
  fread (headerBytes, 44, 1, openFile);
  fwrite (headerBytes, 44, 1, newFile);

  free (headerBytes);
  headerBytes = NULL;

  short testdata[] = {1,2,11,2,3,4,6,7,9,3};
  fwrite (testdata, 14, 1, newFile);
  
  
  fclose (newFile);
  fclose (openFile);
  
  return 0;
}
