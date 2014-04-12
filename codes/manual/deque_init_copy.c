/*
 * deque_init_copy.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_dest = NULL;
    deque_t* pdeq_src = NULL;
    int      i = 0;

    pdeq_dest = create_deque(int);
    if (pdeq_dest == NULL) {
        return -1;
    }
    pdeq_src = create_deque(int);
    if (pdeq_src == NULL) {
        deque_destroy(pdeq_dest);
        return -1;
    }

    deque_init(pdeq_src);
    deque_push_back(pdeq_src, 19);
    deque_push_back(pdeq_src, 2);
    deque_push_back(pdeq_src, -923);
    deque_push_back(pdeq_src, 24);
    deque_push_back(pdeq_src, -21);

    deque_init_copy(pdeq_dest, pdeq_src);
    printf("The size of pdeq_dest is: %d\n", deque_size(pdeq_dest));

    printf("The pdeq_dest: ");
    for (i = 0; i < deque_size(pdeq_dest); ++i) {
        printf("%d ", *(int*)deque_at(pdeq_dest, i));
    }
    printf("\n");

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);

    return 0;
}

