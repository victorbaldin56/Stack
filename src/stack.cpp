#include "stack.h"

StackErr StackCheck(const Stack *stk) {
    if (!stk) {
        return STK_PTR_NULL;
    }

    if (stk->capacity < stk->size) {
        return STK_EXCEED;
    }

    if (stk->size < 0) {
        return STK_SIZE_NEGATIVE;
    }

    if (stk->capacity < 0) {
        return STK_CAPACITY_NEGATIVE;
    }

    if (*stk->lc != CAN_VAL) {
        return STK_LC_DEAD; // left canary protection
    }

    if (*stk->rc != CAN_VAL) {
        return STK_RC_DEAD; // right canary protection
    }

    return STACK_OK;
}

void StackDump(const Stack *stk, StackErr errcode) {
    FILE *lf = fopen("/home/victor/Dev/Stack/logs/stack.log", "w");

    assert(lf);
    assert(stk);
    fprintf(lf, "size = %zd\n"
                "capacity = %zd\n"
                "data[%p]:\n",
                 stk->size,
                 stk->capacity,
                 stk->data);

    fprintf(lf, "left canary = %x\n", *stk->lc);

    for (size_t i = 0; i < stk->size; i++) {
        fprintf(lf, "*[%zu] = %llu\n", i, stk->data[i]);
    }

    for (size_t i = stk->size; i < stk->capacity; i++) {
        fprintf(lf, "[%zu] = %llu\n", i, stk->data[i]);
    }

    fprintf(lf, "right canary = %x\n", stk->rc);
    fprintf(lf, "errcode = %d\n", errcode);

    fclose(lf);
    lf = NULL;
}

Stack *StackCtor(Stack *stk) {
    // STACK_ASS(stk); // checks if stack is not OK
    stk->capacity = INIT_CAP;
    stk->size = 0;
    stk->lc = (Canary_t *)calloc(2 * sizeof(Canary_t) + stk->capacity * sizeof(Elem_t), 1);

    if (!stk->lc) {
        return NULL;
    }

    stk->data = (Elem_t *)(stk->lc + 1);
    stk->rc = (Canary_t *)(stk->data + stk->capacity);

    // stk->rc = stk->data + stk->capacity;
    *stk->lc = *stk->rc = CAN_VAL;

    STACK_ASS(stk); // checks if stk is not OK

    return stk;
}

void StackDtor(Stack *stk) {
    STACK_ASS(stk);
    stk->size = stk->capacity = -1;
    free(stk->lc);
    stk->data = NULL;
    stk = NULL;
}
