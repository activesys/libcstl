/*
 * deque_insert.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t*            pdeq = create_deque(int);
    deque_iterator_t    it;

    if  (pdeq == NULL) {
        return -1;
    }

    deque_init(pdeq);

    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);

    printf("pdeq = ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    it = deque_insert(pdeq, iterator_next(deque_begin(pdeq)), 100);
    printf("The inserted element is %d\n", *(int*)iterator_get_pointer(it));

    printf("pdeq = ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

