/*
 * deque_not_equal.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_q1 = NULL;
    deque_t* pdeq_q2 = NULL;
    deque_t* pdeq_q3 = NULL;

    if ((pdeq_q1 = create_deque(int)) == NULL) {
        return -1;
    }
    if ((pdeq_q2 = create_deque(int)) == NULL) {
        deque_destroy(pdeq_q1);
        return -1;
    }
    if ((pdeq_q3 = create_deque(int)) == NULL) {
        deque_destroy(pdeq_q1);
        deque_destroy(pdeq_q2);
        return -1;
    }

    deque_init(pdeq_q1);
    deque_init(pdeq_q2);
    deque_init_n(pdeq_q3, 10);

    if (deque_not_equal(pdeq_q1, pdeq_q2)) {
        printf("q1 != q2\n");
    } else {
        printf("q1 == q2\n");
    }

    if (deque_not_equal(pdeq_q1, pdeq_q3)) {
        printf("q1 != q3\n");
    } else {
        printf("q1 == q3\n");
    }

    deque_destroy(pdeq_q1);
    deque_destroy(pdeq_q2);
    deque_destroy(pdeq_q3);

    return 0;
}

