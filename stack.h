#ifndef STACK_H
#define STACK_H

#define STACK_DUMP(stk) stack_dump(stk, #stk, __FILE__, __LINE__, __FUNCTION__) 

#define CANARY

const int MEMORY_COEF = 2; 

typedef double StackElem_t;
typedef uint32_t Canary_t;

const Canary_t CANARY_VALUE = 0xDEDAADED;

#define STACK_VERIF(stk) {        \
    if (stack_error(stk) > 0) {   \
        STACK_DUMP(stk);          \
    }                             \
}

enum CodeError {
    SIZE_ERROR      = 1,
    VALUE_ERROR     = 1 << 1,
    PTR_STACK_ERROR = 1 << 2,
    PTR_DATA_ERROR  = 1 << 3,
};

struct Stack_t {

#ifdef CANARY
    Canary_t canary_start;
#endif

    StackElem_t* data;
    int size;
    int capacity;

#ifdef CANARY
    Canary_t canary_end;
#endif

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

// дебажный вывод
void stack_dump(Stack_t* stk, const char* name, const char* file, int line, const char* func);

#endif // STACK_H