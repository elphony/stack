#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_error.h"

void stack_ctor(Stack_t* stk, int capacity) {

    stk->capacity = capacity;
    int size = 0;

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

    *left_canary_ptr(stk) = CANARY_VALUE;
    *right_canary_ptr(stk) = CANARY_VALUE;

    stk->canary_start = CANARY_VALUE;
    stk->canary_end   = CANARY_VALUE;
#endif

#ifdef HASH
    stk->hash = sum_hash(stk);
#endif

    STACK_VERIF(stk);

    stk->size = 0;
}

void stack_realloc(Stack_t* stk) {

    STACK_VERIF(stk);

    size_t new_capacity = MEMORY_COEF * stk->capacity;

#ifdef CANARY
    Canary_t* new_ptr = (Canary_t*)realloc((Canary_t*)stk->data - 1, new_capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t));
    stk->data = (StackElem_t*)(new_ptr + 1);
    *right_canary_ptr(stk) = CANARY_VALUE;

    assert(stk->data != NULL);
#else
    stk->data = (StackElem_t*)realloc(stk->data, new_capacity * sizeof(StackElem_t));

    assert(stk->data != NULL);
#endif

    stk->capacity *= MEMORY_COEF;

    STACK_VERIF(stk);
}

void stack_back_realloc(Stack_t* stk) {

    STACK_VERIF(stk);

    stk->capacity = stk->capacity / 4 + 1;

#ifdef CANARY
    StackElem_t* new_ptr = (StackElem_t*)realloc((Canary_t*)stk->data - 1, stk->capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t));
    stk->data = (StackElem_t*)((Canary_t*)new_ptr + 1);

    *right_canary_ptr(stk) = CANARY_VALUE;
#else
    stk->data = (StackElem_t*)realloc(stk->data, stk->capacity * sizeof(StackElem_t));
#endif

    STACK_VERIF(stk);
}

void stack_push(Stack_t* stk, StackElem_t elem) {

    STACK_VERIF(stk);

    if ((stk->capacity == 0) || (stk->capacity <= stk->size)) {
        stack_realloc(stk);
    }

    stk->data[stk->size] = elem;
    stk->size++;

#ifdef HASH
    stk->hash = sum_hash(stk);
#endif

    STACK_VERIF(stk);
}

StackElem_t stack_pop(Stack_t* stk) {

    STACK_VERIF(stk);

    if ((stk->capacity >= 4) && (stk->size < ((stk->capacity) / 4))) {
        stack_back_realloc(stk);
    }

    stk->size--;
    StackElem_t pop_elem = stk->data[stk->size];

#ifdef HASH
    stk->hash = sum_hash(stk);
#endif

    STACK_VERIF(stk);

    return pop_elem;
}

void stack_dtor(Stack_t* stk) {

    STACK_VERIF(stk);

#ifdef CANARY
    free(left_canary_ptr(stk));
#else
    free(stk->data);
#endif

    stk->data     = nullptr;
    stk->size     = -1;
    stk->capacity = -1;
}

void stack_dump(FILE* out, Stack_t* stk, const char* name, const char* file, int line, const char* func) {

    assert(out != nullptr);

    if (stk) {
        fprintf(out, "%s[%p]\n"
               "\tcalled from %s : %d (%s)\n\n", name, stk, file, line, func);

#ifdef CANARY
        fprintf(out, "STRUCT CANARY_START = %04x\n", stk->canary_start);
#endif

        fprintf(out, "\tcapacity = %d\n"
                     "\tsize =     %d\n", stk->capacity, stk->size);

#ifdef HASH
        fprintf(out, "\nHASH HASH HASH = %llu\n", stk->hash);
#endif

#ifdef CANARY
        fprintf(out, "STRUCT CANARY_END = %04x\n\n", stk->canary_end);
        fprintf(out, "\nDATA CANARY LEFT  = %04x\n", *left_canary_ptr(stk));
#endif

        if (stk->data) {
            for (int i = 0; i < stk->size; ++i)
                fprintf(out, "\t*[%d] = %g\n", i, stk->data[i]);

            for (int i = stk->size; i < stk->capacity; ++i)
                fprintf(out, "\t [%d] = %g\n", i, stk->data[i]);
        }

#ifdef CANARY
    fprintf(out, "DATA CANARY RIGHT  = %04x\n", *right_canary_ptr(stk));
#endif

        fprintf(out, "\n");
    }
}

uint32_t sum_hash(Stack_t* stk) {

    uint32_t hash = 0x811C9DC5;

    for (int i = 0; i < stk->size * sizeof(StackElem_t); i++) {
        hash = (hash ^ (int)*((char*)stk->data + i)) * HASH_CONST;
    }

    return hash;
}

Canary_t* right_canary_ptr(Stack_t* stk) {
    return ((Canary_t*)stk->data + stk->capacity);
}

Canary_t* left_canary_ptr(Stack_t* stk) {
    return ((Canary_t*)stk->data - 1);
}