/*
 * list_greater.c
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = NULL;
    list_t* plist_l2 = NULL;

    plist_l1 = create_list(int);
    if (plist_l1 == NULL) {
        return -1;
    }
    plist_l2 = create_list(int);
    if (plist_l2 == NULL) {
        list_destroy(plist_l1);
        return -1;
    }

    list_init(plist_l1);
    list_init(plist_l2);

    list_push_back(plist_l1, 1);
    list_push_back(plist_l1, 3);
    list_push_back(plist_l1, 1);

    list_push_back(plist_l2, 1);
    list_push_back(plist_l2, 2);
    list_push_back(plist_l2, 2);

    if (list_greater(plist_l1, plist_l2)) {
        printf("List l1 is greater than list l2.\n");
    } else {
        printf("The l1 is not greater than list l2.\n");
    }

    list_clear(plist_l1);
    list_clear(plist_l2);

    list_push_back(plist_l1, 1);
    list_push_back(plist_l1, 2);

    list_push_back(plist_l2, 1);
    list_push_back(plist_l2, 2);
    list_push_back(plist_l2, 0);

    if (list_greater(plist_l1, plist_l2)) {
        printf("List l1 is greater than list l2.\n");
    } else {
        printf("The l1 is not greater than list l2.\n");
    }

    list_destroy(plist_l1);
    list_destroy(plist_l2);

    return 0;
}
