/*
 * deque_begin.c
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

    it = deque_begin(pdeq);
    printf("The first element in pdeq is %d\n", *(int*)iterator_get_pointer(it));
    *(int*)iterator_get_pointer(it) = 20;
    printf("The first element in pdeq is now %d\n", *(int*)iterator_get_pointer(it));

    deque_destroy(pdeq);

    return 0;
}

