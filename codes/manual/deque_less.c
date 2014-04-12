/*
 * deque_less.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_q1 = NULL;
    deque_t* pdeq_q2 = NULL;

    if ((pdeq_q1 = create_deque(int)) == NULL) {
        return -1;
    }
    if ((pdeq_q2 = create_deque(int)) == NULL) {
        deque_destroy(pdeq_q1);
        return -1;
    }

    deque_init(pdeq_q1);
    deque_init(pdeq_q2);

    deque_push_back(pdeq_q1, 1);
    deque_push_back(pdeq_q1, 2);
    deque_push_back(pdeq_q1, 4);

    deque_push_back(pdeq_q2, 1);
    deque_push_back(pdeq_q2, 3);

    if (deque_less(pdeq_q1, pdeq_q2)) {
        printf("Deque q1 is less than deque q2.\n");
    } else {
        printf("Deque q1 is not less than deque q2.\n");
    }

    deque_destroy(pdeq_q1);
    deque_destroy(pdeq_q2);

    return 0;
}

