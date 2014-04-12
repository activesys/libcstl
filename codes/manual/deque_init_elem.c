/*
 * deque_init_elem.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq = create_deque(int);
    int      i = 0;

    if (pdeq == NULL) {
        return -1;
    }

    deque_init_elem(pdeq, 10, 999);
    printf("The size of pdeq is %d\n", deque_size(pdeq));
    printf("The pdeq is ");
    for (i = 0; i < deque_size(pdeq); ++i) {
        printf("%d ", *(int*)deque_at(pdeq, i));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

