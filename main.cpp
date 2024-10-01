#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    Stack_t stk = {};
    stack_ctor(&stk, -1);

    for (int i = 0; i < 50; ++i) {
        stack_push(&stk, i);
    }

    STACK_DUMP(&stk);

    for (int i = 0; i < 40; ++i) {
        stack_pop(&stk);
    }

    STACK_DUMP(&stk);

    stack_dtor(&stk);
}
