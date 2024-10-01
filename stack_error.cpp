#include <stdio.h>

#include "stack.h"
#include "stack_error.h"

void output_error(int errors) {
    
    if (errors & PTR_STACK_ERROR) {
        fprintf(stderr, "ERROR: null pointer to the struct stack\n");
        return;
    }

    if (errors & PTR_DATA_ERROR) {
        fprintf(stderr, "ERROR: null pointer to the stack data\n");
    }

    if (errors & SIZE_ERROR) {
        fprintf(stderr, "ERROR: stack overflow\n");
    }

    if (errors & VALUE_ERROR) {
        fprintf(stderr, "ERROR: incorrect values size or capacity\n");
    }
}

int stack_error(Stack_t* stk) {

    int errors = 0;

    if (!stk) {
        errors = errors | PTR_STACK_ERROR;
        return errors;
    }
    if (!stk->data) {
        errors = errors | PTR_DATA_ERROR;
    }
    if (stk->size < 0 || stk->capacity < 0) {
        errors = errors | VALUE_ERROR;
    }
    if (stk->size > stk->capacity) {
        errors = errors | SIZE_ERROR;
    }

    if (errors > 0) {
        output_error(errors);
    }

    return errors;
}

