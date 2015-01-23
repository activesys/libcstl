/*
 * list_back.c
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
    list_push_back(plist, 20);

    pi = (int*)list_back(plist);

    printf("The last integer of l1 is %d\n", *pi);
    (*pi)++;

    pj = (int*)list_back(plist);
    printf("The modified last integer of l1 is %d\n", *pj);

    list_destroy(plist);

    return 0;
}
