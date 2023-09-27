#include "stack.h"

StackErr StackCheck(const Stack *stk) {
    if (!stk) {
        return NULL_PTR;
    }

    if (stk->capacity < stk->size) {
        return BIG_SIZE;
    }

    if (stk->size < 0) {
        return SIZE_NEGATIVE;
    }

    if (stk->capacity < 0) {
        return CAP_NEGATIVE;
    }

    if (*stk->lc != CAN_VAL) {
        return LC_DEAD; // left canary protection
    }

    if (*stk->rc != CAN_VAL) {
        return RC_DEAD; // right canary protection
    }

    // if (stk->hash != HashFunc(stk)) {
    //     return HASH_DEAD;
    // }

    return STACK_OK;
}

void StackDump(const Stack *stk, StackErr errcode) {
    FILE *lf = fopen("/home/victor/Dev/Stack/logs/stack.log", "w");

    if (!errcode) {
        fprintf(lf, "STK is OK\n");
    }

    else {
        fprintf(lf, "ERROR:\n");
    }

    assert(lf);
    assert(stk);
    fprintf(lf, "size = %zd\n"
                "capacity = %zd\n"
                "data[%p]:\n",
                 stk->size,
                 stk->capacity,
                 stk->data);

    fprintf(lf, "left canary = %llx\n", *stk->lc);

    for (ssize_t i = 0; i < stk->size; i++) {
        fprintf(lf, "*[%zd] = %llu\n", i, stk->data[i]);
    }

    for (ssize_t i = stk->size; i < stk->capacity; i++) {
        fprintf(lf, "[%zd] = %llu\n", i, stk->data[i]);
    }

    fprintf(lf, "right canary = %llx\n", *stk->rc);
    fprintf(lf, "errcode = %d\n (%s)", errcode, GETVNAME(errcode));

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
    stk->hash = 0;

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

unsigned long long HashFunc(const Stack *stk) {
    STACK_ASS(stk);

    unsigned long long hash = 0;
    for (size_t i = 0; i < sizeof(Elem_t) * stk->capacity; i++) {
        hash += ((char *)stk->data)[i];
    }

    return hash;
}
