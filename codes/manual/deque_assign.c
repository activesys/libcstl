/*
 * deque_assign.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t*            pdeq1 = NULL;
    deque_t*            pdeq2 = NULL;
    deque_iterator_t    it;

    if ((pdeq1 = create_deque(int)) == NULL) {
        return -1;
    }
    if ((pdeq2 = create_deque(int)) == NULL) {
        deque_destroy(pdeq1);
        return -1;
    }

    deque_init(pdeq1);
    deque_push_back(pdeq1, 10);
    deque_push_back(pdeq1, 20);
    deque_push_back(pdeq1, 30);

    deque_init(pdeq2);
    deque_push_back(pdeq2, 40);
    deque_push_back(pdeq2, 50);

    printf("deq1 = ");
    for (it = deque_begin(pdeq1);
         !iterator_equal(it, deque_end(pdeq1));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");
    
    printf("deq2 = ");
    for (it = deque_begin(pdeq2);
         !iterator_equal(it, deque_end(pdeq2));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_assign(pdeq1, pdeq2);

    printf("deq1 = ");
    for (it = deque_begin(pdeq1);
         !iterator_equal(it, deque_end(pdeq1));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");
    
    printf("deq2 = ");
    for (it = deque_begin(pdeq2);
         !iterator_equal(it, deque_end(pdeq2));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq1);
    deque_destroy(pdeq2);

    return 0;
}

