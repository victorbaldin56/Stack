#include "stack.h"

int main() {
    printf("# A demo program for stack structure\n"
           "# (c) Victor Baldin, 2023\n\n");

    printf("Enter values to push; to stop input, press ctrl+D:\n");
    Stack stk = {};
    StackCtor(&stk);
    // StackCtor(&stk);
    // StackCtor(NULL);

    Elem_t value = 0;

    while (scanf(PRINTFFMT, &value) > 0) {
        Push(&stk, value);
    }

    while (Pop(&stk, &value) != POP_EMPTY) {
        printf("Pop: " PRINTFFMT "\n", value);
    }

    StackDtor(&stk);

//     Stack badstk = {};
//     StackCtor(&badstk);
//     badstk.size = -1;
//     STACK_ASS(&badstk);
//
    return 0;
}
