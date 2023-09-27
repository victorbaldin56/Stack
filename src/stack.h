#ifndef STACK
#define STACK

// #define NDEBUG

#ifndef NDEBUG
#define ON_DEBUG(x) x

#else
#define ON_DEBUG(x) ;
#endif // NDEBUG

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef NDEBUG
#define STACK_ASS(stk)                      \
    if (StackCheck(stk)) {                  \
        StackDump(stk, StackCheck(stk));    \
        abort();                            \
    }

#else
#define STACK_ASS(stk) ;
#endif

#define GETVNAME(var) (#var)

typedef unsigned long long Elem_t;
typedef unsigned long long Canary_t;

/**
 * @brief Holds stack
*/
typedef struct {
    Canary_t *lc;
    Elem_t *data;
    ssize_t size;
    ssize_t capacity;
    unsigned long long hash;
    Canary_t *rc;
} Stack;

const Canary_t CAN_VAL = 0xDEDEDEDEDEDEDEDE;

enum StackErr {
    STACK_OK,
    BIG_SIZE,
    NULL_PTR,
    SIZE_NEGATIVE,
    CAP_NEGATIVE,
    LC_DEAD,
    RC_DEAD,
    HASH_DEAD,
    REALLOC_FAILED,
    POP_EMPTY,
    POP_VAL_NULL,
};

/**
 *
*/
StackErr StackCheck(const Stack *stk);

void StackDump(const Stack *stk, StackErr errcode);

const int INIT_CAP = 1;

Stack *StackCtor(Stack *stk);

void StackDtor(Stack *stk);

const size_t COEFF = 2; // StackRealloc multiplies capacity to this value

Stack *StackRealloc(Stack *stk, size_t newcap);

StackErr Push(Stack *stk, Elem_t value);

StackErr Pop(Stack *stk, Elem_t *value);

unsigned long long HashFunc(const Stack *stk);

// void *Recalloc(void *ptr, size_t oldsize, size_t newsize);

#endif // STACK
