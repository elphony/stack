#include <stdio.h>
#include <stdlib.h>

const int MEMORY_COEF = 2; 

typedef double StackElem_t;

enum CodeError {
    erererere = 1
};

struct Stack_t {
    StackElem_t* data;
    size_t size;
    size_t capacity;
    CodeError error;
};

// добавляет элемемент в стэк
void stack_push(Stack_t* stk, StackElem_t elem);

// удаляет элемент из стэка
StackElem_t stack_pop(Stack_t* stk);

// создает стэк 
void stack_ctor(Stack_t* stk, int capacity);

// увеличивает стэк
void stack_realloc(Stack_t* stk);

// уменьшает стэк
void stack_back_realloc(Stack_t* stk);

// удаляет стэк
void stack_dtor(Stack_t* stk);

// вывод стэка
void output(FILE* out, Stack_t* stk);

// дебажный вывод
void stack_dump(Stack_t* stk);

int main() {
    Stack_t stk = {};
    stack_ctor(&stk, 1);

    for (int i = 0; i < 50; ++i) {
        stack_push(&stk, i);
    }

    stack_dump(&stk);

    for (int i = 0; i < 40; ++i) {
        stack_pop(&stk);
    }

    stack_dump(&stk);

    stack_dtor(&stk);

}

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
    stk->size     = 0;
    stk->capacity = 0;
}

void output(FILE* out, Stack_t* stk) {
    for (size_t i = 0; i < stk->size; ++i) {
        fprintf(out, "[%zu] = %lg ", i, stk->data[i]);
    }
    printf("\n");
}

void stack_dump(Stack_t* stk) {
    
    fprintf(stderr, "\nStack\n");

    fprintf(stderr, "\tsize = %zu\n\tcapacity = %zu\n", stk->size, stk->capacity);
    
    fprintf(stderr, "\tdata[%p]\n", stk->data);

    output(stderr, stk);
}