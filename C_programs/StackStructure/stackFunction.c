# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "stackFunction.h"
// Functions

// StackInit ()
/*** Initialize the stack memory space ***/
stackStruct *StackInit (int max_size) {
  //stackStruct->stackContent = malloc (sizeof (stackElement))
  if (max_size > MAX_SIZE) {
    printf ("The size of the init size is greater than the max size: %d\n", MAX_SIZE);
    return NULL;
  }
  stackStruct *stackStruct_1;
  stackStruct_1 = malloc (sizeof (stackStruct));
  // Marking the top as not existing
  stackStruct_1->stackTop = -1;
  stackStruct_1->stackSize = max_size;
  stackStruct_1->mallocTracker = 0;
  stackStruct_1->topCounter = MALLOC_SIZE;
  return stackStruct_1;
}

// StackMalloc ()
/*** Allocate MALLOC_SIZE (20) more space or up to stackSize ***/
int StackMallocIncrease (stackStruct *stackStruct_1) {
  int top = stackStruct_1->stackTop;

  if (stackStruct_1->stackSize > top + 20) {
    stackStruct_1->stackContent = realloc (stackStruct_1->stackContent, sizeof (stackElement) * (top + MALLOC_SIZE));
    stackStruct_1->mallocTracker += MALLOC_SIZE;
  }
  else {
    stackStruct_1->stackContent = realloc (stackStruct_1->stackContent, sizeof (stackElement) * stackStruct_1->stackSize );
    stackStruct_1->mallocTracker = stackStruct_1->stackSize;
  }
  
  return 0;
}

//int StackMallocDecrease (stackStruct *stackStruct_1);
  
// StackDestroy ()
/*** Freeing the stack ***/
/************************************************
    free the content, than free the stack struct
*******************************************/
void StackDestroy (stackStruct *stackStruct_1) {
  free (stackStruct_1->stackContent);
  free (stackStruct_1);
}

// StackPush ()
/*** Push element into the array ***/
int StackPush (stackStruct *stackStruct_1, stackElement elementToPush) {
  if (StackIsFull (stackStruct_1)) {
    return -1;
  }
  if (stackStruct_1->topCounter == MALLOC_SIZE) {
    StackMallocIncrease (stackStruct_1);
    stackStruct_1->topCounter = 0;
    printf ("Mallocate memory\n");
  }
  stackStruct_1->stackTop ++;
  stackStruct_1->topCounter ++;
  *(stackStruct_1->stackContent + stackStruct_1->stackTop) = elementToPush;
  return 0;
}
    
// StackPop ()
stackElement StackPop (stackStruct *stackStruct_1) {
  stackElement temp;
  temp = *(stackStruct_1->stackContent + stackStruct_1->stackTop);
  stackStruct_1->stackTop --;
  return temp;
}

// StackIsEmty ()
int StackIsEmty (stackStruct *stackStruct_1) {
  return stackStruct_1->stackTop < 0;
}

// StackIsFull ()
int StackIsFull (stackStruct *stackStruct_1) {
  return stackStruct_1->stackTop >= stackStruct_1->stackSize - 1;
}

