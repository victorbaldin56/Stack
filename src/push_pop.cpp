#include "stack.h"

StackErr Push(Stack *stk, Elem_t value) {
    #ifdef HASH_PROTECT
    stk->hash = HashFunc(stk);
    #endif
    STACK_ASS(stk);

    if (stk->size == stk->capacity) {
        if (!StackRealloc(stk, stk->capacity * COEFF)) { // Extend stack
            return REALLOC_FAILED;
        }
    }

    stk->data[stk->size++] = value;
    return STACK_OK;
}

StackErr Pop(Stack *stk, Elem_t *value) {
    #ifdef HASH_PROTECT
    stk->hash = HashFunc(stk);
    #endif
    STACK_ASS(stk);

    if (!stk->size) {
        return POP_EMPTY;
    }

    if (!value) {
        return POP_VAL_NULL;
    }

    if (stk->size * COEFF * COEFF <= stk->capacity) {
        if (!StackRealloc(stk, stk->capacity / COEFF)) {
            return REALLOC_FAILED;
        }
    }

    *value = stk->data[--stk->size];
    stk->data[stk->size] = ULLONG_MAX; // poisoning
    return STACK_OK;
}
