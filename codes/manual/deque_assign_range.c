/*
 * deque_assign_range.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    deque_t*            pdeq_dest = NULL;
    deque_t*            pdeq_src = NULL;
    set_t*              pset = NULL;
    deque_iterator_t    it;
    int                 i;

    if ((pdeq_dest = create_deque(int)) == NULL) {
        return -1;
    }
    if ((pdeq_src = create_deque(int)) == NULL) {
        deque_destroy(pdeq_dest);
        return -1;
    }
    if ((pset = create_set(int)) == NULL) {
        deque_destroy(pdeq_dest);
        deque_destroy(pdeq_src);
        return -1;
    }

    deque_init(pdeq_dest);
    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq_dest, i);
    }

    printf("pdeq = ");
    for (it = deque_begin(pdeq_dest);
         !iterator_equal(it, deque_end(pdeq_dest));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_init(pdeq_src);
    for (i = 100; i < 1000; i += 100) {
        deque_push_front(pdeq_src, i);
    }

    deque_assign_range(pdeq_dest, deque_begin(pdeq_src), deque_end(pdeq_src));

    printf("pdeq = ");
    for (it = deque_begin(pdeq_dest);
         !iterator_equal(it, deque_end(pdeq_dest));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    set_init(pset);
    for (i = -10; i < 11; ++i) {
        set_insert(pset, i);
    }

    deque_assign_range(pdeq_dest, set_begin(pset), set_end(pset));

    printf("pdeq = ");
    for (it = deque_begin(pdeq_dest);
         !iterator_equal(it, deque_end(pdeq_dest));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
    set_destroy(pset);

    return 0;
}

