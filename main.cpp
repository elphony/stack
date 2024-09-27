#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    Stack_t stk = {};
    stack_ctor(&stk, 1);

    for (int i = 0; i < 50; ++i) {
        stack_push(&stk, i);
    }

    // TODO __FILE__, __LINE__, __FUNCTION__
    stack_dump(&stk, "main.cpp", 14, "main");

    for (int i = 0; i < 40; ++i) {
        stack_pop(&stk);
    }

    stack_dump(&stk, "main.cpp", 20, "main");

    stack_dtor(&stk);
}
