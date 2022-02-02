#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * You might want to declare some global variables to
 * help you maintain the stack, and the state of the stack.
 * Once you have implemented push and pop here and corresponding
 * parts in operate.c - we highly recommend checking out
 * tests/stack_test and running it to see if you are getting expected
 * output - to check basic stack functionality. You could write similar
 * tests for other functionalities.
 */

/* push a value to the stack */
void push(int val) {}

/* pop a value from the stack
 * return 0 if pop failed, else return 1 and set *v
 */
int pop(int* v) {}

/* print the entire stack */
void printstack() {}

/* the topmost entry becomes the lowest entry in the stack */
void rot() {}

/* returns the size of the stack */
unsigned int get_stack_size() {}

/* delete all entries in the stack, free all memory associated with it */
void delete_stack() {}
