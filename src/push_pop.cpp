#include "stack.h"

StackErr Push(Stack *stk, Elem_t value) {
    STACK_ASS(stk);

    if (stk->size == stk->capacity) {
        if (!StackRealloc(stk, stk->capacity * COEFF)) { // Extend stack
            return STK_REALLOC_FAILED;
        }
    }

    stk->data[stk->size++] = value;
    return STACK_OK;
}

StackErr Pop(Stack *stk, Elem_t *value) {
    STACK_ASS(stk);

    if (!stk->size) {
        return STK_POP_EMPTY;
    }

    if (!value) {
        return STK_POP_VAL_NULL;
    }

    if (stk->size * COEFF <= stk->capacity) {
        if (!StackRealloc(stk, stk->capacity / COEFF)) {
            return STK_REALLOC_FAILED;
        }
    }

    *value = stk->data[--stk->size];
    stk->data[stk->size] = ULLONG_MAX; // poisoning
    return STACK_OK;
}
