/*
 * deque_init.c
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
        printf("The pdeq is empty.\n");
    } else {
        printf("The pdeq is not empty.\n");
    }

    deque_destroy(pdeq);

    return 0;
}

