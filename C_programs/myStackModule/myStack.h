#ifndef MY_STACK_H

#define MY_STACK_H

typedef struct {
  int data;
  Node *next;
} Node;

static int stack_is_emty();
static int stack_is_full();
static void terminate();

void stack_push();
int stack_pop();


#endif /* MY_STACK_H */
