/*
 * deque_pop_back.c
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq = create_deque(int);

    if (pdeq == NULL) {
        return -1;
    }

    deque_init(pdeq);

    deque_push_back(pdeq, 1);
    deque_push_back(pdeq, 2);

    printf("The first element is: %d\n", *(int*)deque_front(pdeq));
    printf("The last element is: %d\n", *(int*)deque_back(pdeq));

    deque_pop_back(pdeq);
    printf("After deleting the element at the end of the deque, the last element is %d\n",
        *(int*)deque_back(pdeq));

    deque_destroy(pdeq);

    return 0;
}

