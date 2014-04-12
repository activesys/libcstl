/*
 * deque_push_back.c
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
    if (deque_size(pdeq) != 0) {
        printf("Last element: %d\n", *(int*)deque_back(pdeq));
    }

    deque_push_back(pdeq, 2);
    if (deque_size(pdeq) != 0) {
        printf("New last element: %d\n", *(int*)deque_back(pdeq));
    }

    deque_destroy(pdeq);

    return 0;
}

