/*
 * deque_at.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t*    pdeq = create_deque(int);
    int         i = 0;

    if (pdeq == NULL) {
        return -1;
    }

    deque_init_n(pdeq, 10);

    printf("pdeq = ");
    for (i = 0; i < deque_size(pdeq); ++i) {
        printf("%d ", *(int*)deque_at(pdeq, i));
    }
    printf("\n");

    for (i = 0; i < deque_size(pdeq); ++i) {
        *(int*)deque_at(pdeq, i) += 100 * i;
    }

    printf("pdeq = ");
    for (i = 0; i < deque_size(pdeq); ++i) {
        printf("%d ", *(int*)deque_at(pdeq, i));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

