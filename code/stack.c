#include <stdlib.h>
#include "stack.h"

STACK *new_stack() {
    STACK *s = (STACK*)malloc(sizeof(STACK));
    s->stack = (STACK_Elem*)malloc(sizeof(STACK_Elem) * 100000);
    s->sp = 0;
    return s;
}

void push(STACK *s, STACK_Elem elem) {
    s->sp++;
    s->stack[s->sp] = elem;
}

STACK_Elem pop(STACK *s) { 
    STACK_Elem ret;
    if (s->sp > 0) {
        ret = s->stack[s->sp];
        s->sp--;
    }
    return ret;
}