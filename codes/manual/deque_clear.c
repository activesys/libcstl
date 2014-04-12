/*
 * deque_clear.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq = create_deque(int);

    if (pdeq == NULL) {
        return -1;
    }

    deque_init_n(pdeq, 10);

    printf("The size of pdeq is initially %d\n", deque_size(pdeq));
    deque_clear(pdeq);
    printf("The size of pdeq after clear is %d\n", deque_size(pdeq));

    deque_destroy(pdeq);

    return 0;
}

