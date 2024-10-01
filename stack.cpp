#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "stack_error.h"

void stack_ctor(Stack_t* stk, int capacity) {

    stk->capacity = capacity;
    int size = 0

#ifdef CANARY
    size = stk->capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t);
#else
    size = stk->capacity * sizeof(StackElem_t);
#endif

    if (capacity == 0) {
        stk->data = nullptr;
    }
    else {
        stk->data = (StackElem_t*)calloc(size, 1);
    }

#ifdef CANARY
    stk->data = (StackElem_t*)((Canary_t*)stk->data + 1);

    *((Canary_t*)stk->data - 1) = CANARY_VALUE;
    *((Canary_t*)stk->data + stk->capacity) = CANARY_VALUE;

    stk->canary_start = CANARY_VALUE;
    stk->canary_end   = CANARY_VALUE;
#endif

    stk->size = 0;
}

void stack_realloc(Stack_t* stk) {

    size_t new_capacity = MEMORY_COEF * stk->capacity + 1; // нахуй здесь этот + 1 емое

    stk->data = (StackElem_t*)realloc(stk->data, new_capacity * sizeof(StackElem_t));

    stk->capacity *= MEMORY_COEF;

}

void stack_back_realloc(Stack_t* stk) {

    stk->capacity = stk->capacity / 4 + 1;
    
    stk->data = (StackElem_t*)realloc(stk->data, stk->capacity * sizeof(StackElem_t));

}

void stack_push(Stack_t* stk, StackElem_t elem) {

    if ((stk->capacity == 0) || (stk->capacity <= stk->size + 1))
    {
        stack_realloc(stk);
    }

    stk->data[stk->size] = elem;
    stk->size++;

}

StackElem_t stack_pop(Stack_t* stk) {

    if ((stk->capacity >= 4) && (stk->size < ((stk->capacity) / 4))) {
        stack_back_realloc(stk);
    }

    stk->size--;
    StackElem_t pop_elem = stk->data[stk->size];

    return pop_elem;
}

void stack_dtor(Stack_t* stk) {

    free(stk->data);

    stk->data     = nullptr;
    stk->size     = -1;
    stk->capacity = -1;
}

void stack_dump(Stack_t* stk, const char* name, const char* file, int line, const char* func) {
    if (stk) {
        printf("%s[%p]\n"
               "\tcalled from %s : %d (%s)\n"
               "\n\tcapacity = %d\n\tsize =     %d\n", name, stk, file, line, func, stk->capacity, stk->size);

        if (stk->data) {
            for (int i = 0; i < stk->size; ++i)
                printf("\t*[%d] = %g\n", i, stk->data[i]);

            for (int i = stk->size; i < stk->capacity; ++i)
                printf("\t [%d] = %g\n", i, stk->data[i]);
        }
        printf("\n");
    }
}

