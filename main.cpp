#include <stdio.h>
#include <stdlib.h>

typedef double StackElem_t;

enum CodeError {
    erererere = 1
};

struct Stack_t {
    StackElem_t* data;
    size_t size;
    size_t capacity;
    CodeError err;
};

// добавляет элемемент в стэк
void stack_push(Stack_t* stk, StackElem_t elem);

// удаляет элемент из стэка
StackElem_t stack_pop(Stack_t* stk);

// создает стэк и увеличивает его размер при необходимости
void stack_ctor(Stack_t* stk);

void stack_output(Stack_t* stk);

// удаляет стэк
//void stack_dtor(Stack_t* stk);

// дебажный вывод
//void stack_dump(Stack_t* stk);

// какая-то универсальная проверка на ошибка
//CodeError stack_error(Stack_t* stk);

int main() {
    Stack_t stk = {};

    stack_ctor(&stk);

    stack_push(&stk, 8);
    stack_output(&stk);
    stack_push(&stk, 16);
    stack_output(&stk);
    stack_push(&stk, 32);
    stack_output(&stk);
    stack_push(&stk, 64);
    stack_output(&stk);
    stack_push(&stk, 128);
    stack_output(&stk);
    stack_push(&stk, 256);
    stack_output(&stk);
    stack_push(&stk, 512);
    stack_output(&stk);
    stack_push(&stk, 1024);
    stack_output(&stk);
    stack_push(&stk, 2048);
    stack_output(&stk);
    stack_pop(&stk);
    stack_output(&stk);

    

    //StackElem_t x = stack_pop(&stk);

    //stack_dtor(&stk);
}

void stack_output(Stack_t* stk) {
    for (size_t i = 0; i < stk->size; ++i) {
        printf("%g ", stk->data[i]);
    }
    printf("\n");
}

void stack_ctor(Stack_t* stk) {
    printf("угабуга\n");
    if (stk->size <= 8) {
        stk->data = (StackElem_t*)realloc(stk->data, sizeof(StackElem_t) * 8);
        stk->capacity = 8;
    }
    else {
        while (stk->size > stk->capacity) {
            stk->data = (StackElem_t*)realloc(stk->data, sizeof(StackElem_t) * stk->capacity * 2);
            stk->capacity = stk->capacity * 2;
        }
    }
}

void stack_push(Stack_t* stk, StackElem_t elem) {
    if (stk->capacity >= (stk->size + 1)) {
        stk->data[stk->size] = elem;
        stk->size++;
        return;
    }
    else {
        stack_ctor(stk);
        stk->data[stk->size] = elem;
        stk->size++;
        return;
    }
}

StackElem_t stack_pop(Stack_t* stk) {
    StackElem_t elem = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;
    return elem;
}