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

  //Check if file is stereo
  int monoOrStereo = 0;
  fseek (openFile, 22, SEEK_SET);
  fread (&monoOrStereo, 2, 1, openFile);
  if (monoOrStereo != 2){
    printf("The input file is not stereo.\n");
    exit (1);
  }
  //printf("%d\n", monoOrStereo);
  
  //This section checks the size of each sample
  int sampleSize = 0;
  fseek (openFile, 34, SEEK_SET);
  fread (&sampleSize, 2, 1, openFile);
  //printf("%d\n", sampleSize);

  //Fiding data block size
  int fileSize = 0;
  fseek (openFile, 40, SEEK_SET);
  fread (&fileSize, 4, 1, openFile);
  //printf("%d\n", fileSize);
  
  fseek (openFile, 0, SEEK_SET);
  
  //Put code here to copy the 44 bytes header
  short *headerBytes;
  headerBytes = malloc (44);
  fread (headerBytes, 44, 1, openFile);
  fwrite (headerBytes, 44, 1, newFile);

  free (headerBytes);
  headerBytes = NULL;
  
  //Checking the placment of things
  //printf("%ld, %ld\n", ftell(openFile), ftell(newFile));
 
  //Put code here to read L and R channel
  /*Each sample is 16 bites == 2bytes
   *ie:
   *sample 1 channel 0
   *sample 1 channel 1*/
  short *read0, *read1, *noVocal;
  int sampleSize_bytes = sampleSize / 8;
  if ((read0 = malloc(sampleSize_bytes)) == NULL){
    perror("Can't allocate memmery for read0");
    exit (1);
  }
  
  
  if ((read1 = malloc(sampleSize_bytes)) == NULL){
    perror("Can't allocate memmery for read1");
    exit (1);
  }
  
  *read0 = 0;
  *read1 = 0;

  if ((noVocal = malloc(sampleSize_bytes)) == NULL) {
    perror("Can't allocate memmery for noVocal");
    exit (1);
  }
  
  while ((fread(read0, sampleSize_bytes, 1, openFile)) != 0) {
    
    //while ((ftell(openFile)) != (fileSize+44)) {
    //fread(read0, 1, 2, openFile);

    fread(read1, sampleSize_bytes, 1, openFile);
    
    // printf("%d\n", *read0);
    //printf("%d\n", *read1);

    *noVocal = (*read0 - *read1)/2;
    
    
    //printf("%d\n", *noVocal);
    fwrite(noVocal, sampleSize_bytes, 1, newFile);
    fwrite(noVocal, sampleSize_bytes, 1, newFile);

    //printf("%ld, %ld\n", ftell(openFile), ftell(newFile));
    }

  fclose (newFile);
  fclose (openFile);
  
  return 0;
}
