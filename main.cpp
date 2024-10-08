#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    Stack_t stk = {};
    stack_ctor(&stk, -5);

    for (int i = 0; i < 50; ++i) {
        stack_push(&stk, i);
    }

    for (int i = 0; i < 40; ++i) {
        stack_pop(&stk);
    }

    stack_dtor(&stk);
}
