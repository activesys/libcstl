/*
 * deque_resize_elem.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t*         pdeq = create_deque(int);
    deque_iterator_t it;

    if (pdeq == NULL) {
        return -1;
    }

    deque_init_elem(pdeq, 10, 999);
    printf("The deque: ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_resize_elem(pdeq, 6, 111);
    printf("The deque after reduction: ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_resize_elem(pdeq, 15, -5);
    printf("The deque after expansion: ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

