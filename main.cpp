#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    open_log_file("LOG.log", "w");

    Stack_t stk = {};
    stack_ctor(&stk, 2);

    for (int i = 0; i < 5; ++i) {
        stack_push(&stk, i);
    }

    for (int i = 0; i < 5; ++i) {
        stack_pop(&stk);
    }

    stack_dtor(&stk);

    close_log_file();
}
