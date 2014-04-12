/*
 * deque_init_copy_range.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    deque_t*  pdeq = NULL;
    vector_t* pvec = NULL;
    int       an_array[] = {8, 0, 127, 909, 111, -174, 1233, 0, 65, 28};
    int       i = 0;

    pdeq = create_deque(int);
    if (pdeq == NULL) {
        return -1;
    }
    pvec = create_vector(int);
    if (pvec == NULL) {
        deque_destroy(pdeq);
        return -1;
    }

    vector_init_copy_array(pvec, an_array, 10);
    deque_init_copy_range(pdeq, iterator_next_n(vector_begin(pvec), 3), iterator_prev(vector_end(pvec)));
    printf("The deque: ");
    for (i = 0; i < deque_size(pdeq); ++i) {
        printf("%d ", *(int*)deque_at(pdeq, i));
    }
    printf("\n");

    deque_destroy(pdeq);
    vector_destroy(pvec);

    return 0;
}

