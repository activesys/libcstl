/*
 * deque_assign_elem.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t*            pdeq = create_deque(int);
    deque_iterator_t    it;

    if (pdeq == NULL) {
        return -1;
    }

    deque_init(pdeq);
    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 3);

    printf("deq = ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_assign_elem(pdeq, 10, -299);

    printf("deq = ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

