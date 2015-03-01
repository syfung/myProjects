#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define MAX_NUMBER 100

int main (int argc, char **argv) {
  initscr();
  cbreak(); 
  noecho();
  //fflush(stdin);
  srand (time(NULL));
  char c = 0;
  while (1) {
    //printf ("%c", c);
    if ( getch () == 'q')
      break;
    {    
      printw ("\r%d", (rand () % MAX_NUMBER +1));
      refresh ();
      //fflush (stdout);
      //usleep (1000000);
    }
  }
  endwin();
  return 0;
}
