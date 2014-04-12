/*
 * deque_size.c
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

    deque_push_back(pdeq, 1);
    printf("The deque length is %d\n", deque_size(pdeq));

    deque_push_back(pdeq, 2);
    printf("The deque length is now %d\n", deque_size(pdeq));

    deque_destroy(pdeq);

    return 0;
}

