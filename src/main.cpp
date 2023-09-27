#include "stack.h"

int main() {
    printf("# A demo program for stack structure\n"
           "# (c) Victor Baldin, 2023\n");

    Stack stk = {};
    StackCtor(&stk);

    Elem_t value = 0;

    while (scanf("%llu", &value) > 0) {
        Push(&stk, value);
    }

    while (Pop(&stk, &value) != POP_EMPTY) {
        printf("Stack: %llu\n", value);
    }

    StackDtor(&stk);

    return 0;
}
