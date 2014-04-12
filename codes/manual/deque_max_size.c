/*
 * deque_max_size.c
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
    printf("The maxmum possible length of the deque is %lu\n", deque_max_size(pdeq));

    deque_destroy(pdeq);

    return 0;
}

