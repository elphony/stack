#ifndef STACK_H
#define STACK_H

const int MEMORY_COEF = 2; 

typedef double StackElem_t;

enum CodeError {
    SIZE_ERROR = 1,
    VALUE_ERROR,
    PTR_STACK_ERROR,
    PTR_DATA_ERROR,
    NO_ERROR
};

struct Stack_t {
    StackElem_t* data;
    int size;
    int capacity;
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
void stack_dump(Stack_t* stk, const char* file, int line, const char* func);

// проверки 
CodeError stack_error(Stack_t* stk);

#endif // STACK_H