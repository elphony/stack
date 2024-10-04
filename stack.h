#ifndef STACK_H
#define STACK_H

#include <cstdint>

#define STACK_DUMP(out, stk) stack_dump(out, stk, #stk, __FILE__, __LINE__, __FUNCTION__) 

#define CANARY
#define HASH

const int MEMORY_COEF = 2; 
const uint32_t HASH_CONST = 0x01000193;

typedef double StackElem_t;
typedef uint64_t Canary_t;

const Canary_t CANARY_VALUE = 0xAAAAAAAA;

#define STACK_VERIF(stk) {        \
        stack_error(stk);         \
        STACK_DUMP(stdout, stk);  \
}

enum CodeError {

    SIZE_ERROR              = 1,
    VALUE_ERROR             = 1 << 1,
    PTR_STACK_ERROR         = 1 << 2,
    PTR_DATA_ERROR          = 1 << 3,

#ifdef CANARY

    STK_CANARY_LEFT_ERROR   = 1 << 4,
    STK_CANARY_RIGHT_ERROR  = 1 << 5,
    DATA_CANARY_LEFT_ERROR  = 1 << 6,
    DATA_CANARY_RIGHT_ERROR = 1 << 7,

#endif

#ifdef HASH

    HASH_ERROR              = 1 << 8,

#endif

};

struct Stack_t {

#ifdef CANARY
    Canary_t canary_start;
#endif

    StackElem_t* data;
    int size;
    int capacity;

#ifdef HASH
    uint32_t hash;
#endif

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
void stack_dump(FILE* out, Stack_t* stk, const char* name, const char* file, int line, const char* func);

// считает хэш
uint32_t sum_hash(Stack_t* stk);

// возвращает указатель на правую канарейку
Canary_t* right_canary_ptr(Stack_t* stk);


// возвращает указатель на левую канарейку
Canary_t* left_canary_ptr(Stack_t* stk);

#endif // STACK_H