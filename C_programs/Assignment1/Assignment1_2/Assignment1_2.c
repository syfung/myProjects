// *Assignment 1 part 2, this program will take a .wav file
// *Take input: delay and volume_scale
// *Create a new file that has the original file and the delayed
// *volume_scaled echo mixed together

/***************************************************
  By Joshua Fung -- January 28th, 2015
****************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


int main (int argc, char **argv) {

  //This section of the code reads the inputs and check
  extern char *optarg;
  extern int optind, opterr, optopt;
  opterr = 0;
  char optflag, *optset = {"-d:-v:"}; 
  int delay = -1, volume_scale = -1;
  
  // It loop throught all in put except the last two, assumeing they are the input and output
  while ( optind < argc-2){
    optflag = getopt (argc, argv, optset);

    switch(optflag){

    case 'd':
      delay = strtol(optarg, NULL, 10);
      break;

    case 'v':
      volume_scale = strtol(optarg, NULL, 10);
      break;

    default:
      printf ("Unknow input\n");
      printf ("addecho [-d delay] [-v volume_scale] sourcewav destwav\n");
      exit(1);
      break;
    }
  }

  //Check delay and volume_scale if not provided or negative use default
  // delay = 8000, volume_scale = 4
  if (delay < 0){
    printf ("No delay argument inputed, use default: 8000\n");
    delay = 8000;
  }
  if (volume_scale < 0){
    printf ("No volume scale argument inputed, use default: 4\n");
    volume_scale = 4;
  }

  //Checking value of delay and volume_scale
  printf ("Delay: %d, Volume Scale: %d\n", delay, volume_scale);
	
  //Open file and check
  FILE *openFile, *newFile;
  if ((openFile = fopen(argv[argc-2], "r")) == NULL){
      perror ("Input file");
      printf ("addecho [-d delay] [-v volume_scale] sourcewav destwav\n");
      exit (1);
    }
  if ((newFile = fopen(argv[argc-1], "w")) == NULL){
      perror ("Output file");
      printf ("addecho [-d delay] [-v volume_scale] sourcewav destwav\n");
      exit (1);
    }

  //Fiding data block size
  int oldFileSize = 0;
  fseek (openFile, 4, SEEK_SET);
  fread (&oldFileSize, 4, 1, openFile);
  
  //Check if file is stereo
  int monoOrStereo = 0;
  fseek (openFile, 22, SEEK_SET);
  fread (&monoOrStereo, 2, 1, openFile);
  if (monoOrStereo != 1){
    printf("The input file is not mono.\n");
    exit (1);
  }
  
  //This section checks the size of each sample
  int sampleSize = 0;
  fseek (openFile, 34, SEEK_SET);
  fread (&sampleSize, 2, 1, openFile);
  
  int sampleSize_bytes;
  sampleSize_bytes = sampleSize / 8;
  printf("%d, %d\n", sampleSize, sampleSize_bytes);
  fseek (openFile, 0, SEEK_SET);

  //We will try to loop through the data set
  //Initializing and allocate memeory and check 
  short *delayBuffer, *reader, *sum;
  int i = 0, j = 0; 
  if ((delayBuffer = malloc (delay * 2)) == NULL){
    perror("Can't allocate memmery for Delay Buffer");
    exit (1);
  }
  if ((reader = malloc (sampleSize_bytes)) == NULL) {
    perror("Can't allocate memmery for Reader");
    exit (1);
  }
  if ((sum = malloc (sampleSize_bytes)) ==NULL) {
    perror("Can't allocate memmery for Sum");
    exit (1);
  }

  // Calculating the new size to put
  int newFileSize = (oldFileSize + (delay * 2));
  printf("%x, %d",newFileSize, newFileSize);
  // This doesn't really make sence
  unsigned int newDatablockSize = (oldFileSize + (delay * 2) - 36);
  printf(" %x,%d\n",newDatablockSize, newDatablockSize);

  // Loop thorught even two bytes of the file
  while ((fread(reader, 1, 2, openFile)) != 0) {
    
    if (ftell(openFile) == 6){
      printf("Write new file size to header:\n");
      fwrite (&newFileSize, 4, 1, newFile);
      fread(reader, 2, 1, openFile);
      printf("Finish at %ld, %ld\n", ftell(openFile), ftell(newFile));
    }
    else if (ftell(openFile) == 42){
      printf("Write new data block size to header:\n");
      fwrite (&newDatablockSize, 4, 1, newFile);
      fread(reader, 2, 1, openFile);
      printf("Finish at %ld, %ld\n", ftell(openFile), ftell(newFile));
    }
    else if (ftell(openFile) < 42){
      fwrite (reader, 2, 1, newFile);
      printf("Finish at %ld, %ld Writing info header\n", ftell(openFile), ftell(newFile));
    }
    else if (ftell(openFile) <= (delay * 2) + 44){
      printf ("Buffering the delay to element %d\n", i);
      *(delayBuffer + i) = *reader;
      fwrite (reader, 2, 1, newFile); 
      printf ("Finish at %ld, %ld Writing no echo data blocks\n", ftell(openFile), ftell(newFile));
      i ++;
    }
    else {
      printf ("Reading the delay element %d\n", j);
      printf ("Writing to delay element %d\n", j);
      *sum = *reader + *(delayBuffer + j) / (short) volume_scale;
      printf ("%x", *sum);
      *(delayBuffer + j) = (short) *reader;
      fwrite (sum, 2, 1, newFile);
      printf ("Finish at %ld, %ld Writing data blocks with echo\n", ftell(openFile), ftell(newFile));
      if (j == delay - 1){
	printf ("%d", j);
	j = 0;
      }
      else {
	j ++;
      }
    }
  }
  printf ("%d", j);
  
  int count;
  for (count = 0; count < delay; count++){
    //printf ("%d\n",*(delayBuffer + count));
    *(delayBuffer + count) = *(delayBuffer + count) / (short) volume_scale;
  }
    
  fwrite ((delayBuffer + j), 2, delay - j, newFile);
  fwrite (delayBuffer, 2, j, newFile);
  
  fclose(openFile);
  fclose(newFile);

  return 0;
}
