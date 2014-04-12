/*
 * deque_init_copy_array.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq = create_deque(int);
    int      an_array[] = {8, 55, -23, 4444, 1024};
    int      i = 0;

    if (pdeq == NULL) {
        return -1;
    }

    deque_init_copy_array(pdeq, an_array, 5);
    printf("The size of pdeq is %d.\n", deque_size(pdeq));
    printf("The pdeq = ");
    for (i = 0; i < deque_size(pdeq); ++i) {
        printf("%d ", *(int*)deque_at(pdeq, i));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

