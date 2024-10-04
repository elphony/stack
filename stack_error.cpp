#include <stdio.h>
#include <cstdlib>

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

#ifdef CANARY

    if (errors & STK_CANARY_LEFT_ERROR) {
        fprintf(stderr, "ERROR: incorrect value left canary in struct stack\n");
    }

    if (errors & STK_CANARY_RIGHT_ERROR) {
        fprintf(stderr, "ERROR: incorrect value right canary in struct stack\n");
    }

    if (errors & DATA_CANARY_LEFT_ERROR) {
        fprintf(stderr, "ERROR: incorrect value left canary in stack data\n");
    }

    if (errors & DATA_CANARY_RIGHT_ERROR) {
        fprintf(stderr, "ERROR: incorrect value right canary in stack data\n");
    }

#endif

#ifdef HASH

    if (errors & HASH_ERROR) {
        fprintf(stderr, "ERROR: incorrect value of stack hash\n");
    }

#endif
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

#ifdef CANARY

    if (stk->canary_start != CANARY_VALUE) {
        errors = errors | STK_CANARY_LEFT_ERROR;
    }
    if (stk->canary_end != CANARY_VALUE) {
        errors = errors | STK_CANARY_RIGHT_ERROR;
    }
    if (*((Canary_t*)stk->data - 1) != CANARY_VALUE) {
        errors = errors | DATA_CANARY_LEFT_ERROR;
    }
    if (*((Canary_t*)stk->data + stk->capacity) != CANARY_VALUE) {
        errors = errors | DATA_CANARY_RIGHT_ERROR;
    }

#endif

#ifdef HASH
    
    if (sum_hash(stk) != stk->hash) {
        errors = errors | HASH_ERROR;
    }

#endif

    if (errors > 0) {
        output_error(errors);
        abort();
    }

    return errors;
}

