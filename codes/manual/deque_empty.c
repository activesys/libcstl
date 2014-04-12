/*
 * deque_empty.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq = create_deque(int);

    if (pdeq == NULL) {
        return -1;
    }

    deque_init(pdeq);
    if (deque_empty(pdeq)) {
        printf("The deque is empty!\n");
    } else {
        printf("The deque is not empty!\n");
    }

    deque_push_back(pdeq, 1);
    if (deque_empty(pdeq)) {
        printf("The deque is empty!\n");
    } else {
        printf("The deque is not empty!\n");
    }

    deque_destroy(pdeq);

    return 0;
}

