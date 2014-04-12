/*
 * deque_end.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it;

    if (pdeq == NULL) {
        return -1;
    }

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);

    it = deque_end(pdeq);
    it = iterator_prev(it);
    printf("The last integer of deq is %d\n", *(int*)iterator_get_pointer(it));

    it = iterator_prev(it);
    *(int*)iterator_get_pointer(it) = 400;
    printf("The new next-to-last integer of deq is %d\n", *(int*)iterator_get_pointer(it));

    printf("The deque is now:");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf(" %d", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}
