/*
 * deque_insert_range.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    deque_t*            pdeq = NULL;
    list_t*             plist = NULL;
    deque_iterator_t    it;

    if ((pdeq = create_deque(int)) == NULL) {
        return -1;
    }
    if ((plist = create_list(int)) == NULL) {
        deque_destroy(pdeq);
        return -1;
    }

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 20);
    deque_push_back(pdeq, 30);

    list_init(plist);
    list_push_back(plist, -10);
    list_push_back(plist, -20);
    list_push_back(plist, -30);

    printf("pdeq = ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_insert_range(pdeq, deque_begin(pdeq), list_begin(plist), list_end(plist));

    printf("pdeq = ");
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        printf("%d ", *(int*)iterator_get_pointer(it));
    }
    printf("\n");

    deque_destroy(pdeq);
    list_destroy(plist);

    return 0;
}

