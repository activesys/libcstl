/*
 * deque_swap.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t*         pdeq_q1 = NULL;
    deque_t*         pdeq_q2 = NULL;
    deque_iterator_t it;

    if ((pdeq_q1 = create_deque(int)) == NULL) {
        return -1;
    }
    if ((pdeq_q2 = create_deque(int)) == NULL) {
        deque_destroy(pdeq_q1);
        return -1;
    }

    deque_init(pdeq_q1);
    deque_init(pdeq_q2);
    deque_push_back(pdeq_q1, 1);
    deque_push_back(pdeq_q1, 2);
    deque_push_back(pdeq_q1, 3);
    deque_push_back(pdeq_q2, 10);
    deque_push_back(pdeq_q2, 20);

    printf("The original deque q1 is:");
    for (it = deque_begin(pdeq_q1);
         !iterator_equal(it, deque_end(pdeq_q1));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");
    printf("The original deque q2 is:");
    for (it = deque_begin(pdeq_q2);
         !iterator_equal(it, deque_end(pdeq_q2));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_swap(pdeq_q1, pdeq_q2);

    printf("After swapping, deque q1 is:");
    for (it = deque_begin(pdeq_q1);
         !iterator_equal(it, deque_end(pdeq_q1));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");
    printf("After swapping, deque q2 is:");
    for (it = deque_begin(pdeq_q2);
         !iterator_equal(it, deque_end(pdeq_q2));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq_q1);
    deque_destroy(pdeq_q2);

    return 0;
}

