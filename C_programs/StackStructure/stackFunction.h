# ifndef STACK_FUNCTION_H
# define STACK_FUNCTION_H

// Here define micro
/******************************************************************** 
 This is the max size this program will let people to init
*******************************************************************/
# define MAX_SIZE 100000
# define MALLOC_SIZE 20
# define MAX_NUMBER 1000

// We are giving the type of element a generic name
typedef int stackElement;

// Here is the struc defintion
/**************************************************************
   The stackContent is the actual stack data
   The stackTop is how much element is in this data stack
   The size is the max siz of this stack defined from init
**********************************************************/
struct stack {
  stackElement *stackContent;
  int stackTop;
  int stackSize;
  int topCounter;
  int mallocTracker;
};

typedef struct stack stackStruct;

// Here list the function prtoype that might move to the header files
stackStruct *StackInit (int max_size);

void StackDestroy (stackStruct *stackStruct_1);

int StackMallocIncrease (stackStruct *stackStruct_1);

//int StackMallocDecrease (stackStruct *stackStruct_1);

int StackPush (stackStruct *stackStruct_1, stackElement elementToPush);

stackElement StackPop (stackStruct *stackStruct_1);

int StackIsEmty (stackStruct *stackStruct_1);

int StackIsFull (stackStruct *stackStruct_1);
 

# endif
