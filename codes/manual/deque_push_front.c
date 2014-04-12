/*
 * deque_push_front.c
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

    deque_push_front(pdeq, 1);
    if (deque_size(pdeq) != 0) {
        printf("First element: %d\n", *(int*)deque_front(pdeq));
    }

    deque_push_front(pdeq, 2);
    if (deque_size(pdeq) != 0) {
        printf("New first element: %d\n", *(int*)deque_front(pdeq));
    }

    deque_destroy(pdeq);

    return 0;
}

