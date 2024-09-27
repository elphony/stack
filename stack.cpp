#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "text_color.h"

void stack_ctor(Stack_t* stk, int capacity) {

    stk->capacity = capacity;

    if (capacity == 0) {
        stk->data = nullptr;
    }
    else {
        stk->data = (StackElem_t*)calloc(stk->capacity, sizeof(StackElem_t));
    }

    stk->size = 0;
}

void stack_realloc(Stack_t* stk) {

    stk->data = (StackElem_t*)realloc(stk->data, MEMORY_COEF * stk->capacity * sizeof(StackElem_t));

    stk->capacity *= MEMORY_COEF;
}

void stack_back_realloc(Stack_t* stk) {

    stk->capacity /= 4;
    
    stk->data = (StackElem_t*)realloc(stk->data, (stk->capacity + 1) * sizeof(StackElem_t));

}

void stack_push(Stack_t* stk, StackElem_t elem) {

    if ((stk->capacity == 0) || (stk->capacity == stk->size + 1))
    {
        stack_realloc(stk);
    }

    stk->data[stk->size] = elem;
    stk->size++;
}

StackElem_t stack_pop(Stack_t* stk) {

    if ((stk->capacity >= 4) && (stk->size < ((stk->capacity) / 4)))
    {
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

void output(FILE* out, Stack_t* stk) {
    for (size_t i = 0; i < stk->size; ++i) {
        fprintf(out, "[%zu] = %lg ", i, stk->data[i]);
    }
    printf("\n");
}

void stack_dump(Stack_t* stk, const char* file, int line, const char* func) {
    if (stk) {
        printf("stk[%p]\n\tcalled from %s : %d (%s)\n\n\tcapacity = %d\n\tsize =     %d\n", stk, file, line, func, stk->capacity, stk->size);

        if (stk->data) {
            for (int i = 0; i < stk->size; ++i)
                printf("\t*[%d] = %g\n", i, stk->data[i]);
            
            for (int i = stk->size; i < stk->capacity; ++i)
                printf("\t [%d] = %g\n", i, stk->data[i]);
        }
    }
    printf("\n");
}

CodeError stack_error(Stack_t* stk) {
    if (!stk) {
        return PTR_STACK_ERROR;
    }
    if (!stk->data) {
        return PTR_DATA_ERROR;
    }
    if (stk->size < 0 || stk->capacity < 0) {
        return VALUE_ERROR;
    }
    if (stk->size > stk->capacity) {
        return SIZE_ERROR;
    }
    return NO_ERROR;
}