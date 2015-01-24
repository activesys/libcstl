/*
 * list_front.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist = create_list(int);
    int*    pi = NULL;
    int*    pj = NULL;

    if (plist == NULL) {
        return -1;
    }

    list_init(plist);

    list_push_back(plist, 10);

    pi = (int*)list_front(plist);
    pj = (int*)list_front(plist);

    printf("The first integer of l1 is %d\n", *pi);
    (*pi)++;
    printf("The modified first integer of l1 is %d\n", *pj);

    list_destroy(plist);

    return 0;
}
