/* Implementation of a stack (of integers)
Alcryst/c_datastruc

Operations:

stack* stack_init(int len) - initializes an empty stack of length len
(allocates memory equal to sizeof(stack) + (sizeof(int) * len))
Returns pointer to the newly created stack.

int stack_destroy(stack* s) - frees the memory allocated to stack s during initialization
Returns 0 if s is freed, 1 if s is NULL

int stack_push(stack* s, int i) - pushes the item i to the top of the stack s
Returns 0 if successful; if a stack overflow would occur, returns 1 without altering the stack.

int stack_isEmpty(stack* s) - checks if the stack s is empty (i.e. has 0 items)
Returns 1 if empty, 0 if not empty

int stack_pop(stack* s) - pops the item i currently on top of stack s
Returns i if successful, -1 if the stack is empty (no items can be popped).
Checking if the stack is empty before attempting to use this method is best,
in order to avoid mistaking the error value -1 for a valid return value of -1.

*/

#include <stdio.h>
#include <stdlib.h>

struct stack {
	int top_pointer; // points to 1st empty space in array
	int max_len;
	int list[];
};

struct stack* stack_init(int len) {
	struct stack* s = (struct stack*) malloc(sizeof(struct stack) + (sizeof(int) * len));
	s->max_len = len;
	s->top_pointer = 0;
	return s;
}

int stack_destroy(struct stack* s) {
	if (s) {
		free(s);
		return(0);
	}
	return (1);
}

int stack_push(struct stack* s, int i) {
	if (s->max_len <= s->top_pointer) {
		return(1); // stack overflow!
	}
	else {
		s->list[s->top_pointer] = i;
		(s->top_pointer) = (s->top_pointer + 1);
	}
	return(0);
}

int stack_isEmpty(struct stack* s) {
	if (s->top_pointer == 0)
		return(1);
	else
		return(0);
}

int stack_pop(struct stack* s) {
	if (stack_isEmpty(s))
		return(-1); // this is an error lol
	else {
		s->top_pointer = s->top_pointer - 1;
		return(s->list[s->top_pointer]);
	}
}

// note: used for debugging
// int stack_getPointer(struct stack* s)
//	{ return(s->top_pointer); }

int main() { // example driver
	
	int len = 5;
	struct stack* myStack = stack_init(len);
	printf("Created stack of length %d at %p\n\n", len, (void*) myStack);
	int myVal;

	if(stack_push(myStack, 1)) {
		printf("Error pushing!");
	}
	stack_push(myStack, 2);
	myVal = stack_pop(myStack);
	printf("Got: %d\n", myVal);
	stack_push(myStack, 3);
	stack_push(myStack, 4);
	myVal = stack_pop(myStack);
	printf("Got: %d\n", myVal);
	stack_push(myStack, 5);

	while (! stack_isEmpty(myStack)) {
		myVal = stack_pop(myStack);

		printf("Got: %d\n", myVal);

	}
	printf("Stack is empty.\n");

	stack_destroy(myStack);
	printf("Stack destroyed.\n");

	printf("\nSuccessfully completed!\n");

}