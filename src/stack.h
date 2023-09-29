#ifndef STACK
#define STACK

// #define HASH_PROTECT
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

#define STACK_ASS(stk)                                          \
    if (StackCheck(stk)) {                                      \
        StackDump(stk, StackCheck(stk), __FILE__, __LINE__);    \
        abort();                                                \
    }

#else
#define STACK_ASS(stk) ;
#endif

#define my_assert(expr) \
    if (!(expr)) {  \
        fprintf(stderr, "%s %s:%d: My assertion failed: \"" #expr "\"\n", __FILE__, __func__, __LINE__); \
        abort(); \
}

#define GETVNAME(var) (#var)

typedef unsigned long long Elem_t;
typedef unsigned long long Canary_t;

#define PRINTFFMT "%llu"

/**
 * @brief Holds stack
*/
typedef struct {
    Canary_t *lc;
    Elem_t *data;
    ssize_t size;
    ssize_t capacity;
    #ifdef HASH_PROTECT
    unsigned long long hash;
    #endif
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
    #ifdef HASH_PROTECT
    HASH_DEAD,
    #endif
    REALLOC_FAILED,
    POP_EMPTY,
    POP_VAL_NULL,
};

/**
 *
*/
StackErr StackCheck(const Stack *stk);

void StackDump(const Stack *stk, StackErr errcode, const char *file, int line);

const int INIT_CAP = 1;

Stack *StackCtor(Stack *stk);

void StackDtor(Stack *stk);

const size_t COEFF = 2; // StackRealloc multiplies capacity to this value

Stack *StackRealloc(Stack *stk, size_t newcap);

StackErr Push(Stack *stk, Elem_t value);

StackErr Pop(Stack *stk, Elem_t *value);

#ifdef HASH_PROTECT
unsigned long long HashFunc(const Stack *stk);
#endif

// void *Recalloc(void *ptr, size_t oldsize, size_t newsize);

#endif // STACK
