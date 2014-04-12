/*
 * deque_erase.c
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
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 50);

    printf("The initial deque is: ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    it = deque_erase(pdeq, deque_begin(pdeq));
    printf("The next element after erased is: %d\n", *(int*)iterator_get_pointer(it));

    printf("After erasing the first element, the deque becomes: ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq);

    return 0;
}

